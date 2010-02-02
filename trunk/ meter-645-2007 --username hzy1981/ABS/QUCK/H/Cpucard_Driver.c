
#define CPUCARD_DRIVER_C_
#include "MyIncludesAll.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "Q2"
#endif

#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

   
/*"**************************************************************************"*/
INT8U Cpucard_Esamcard_Internal_Auth(void)  //�ڲ���֤//
{
    if(Check_Cpu_Card_Out())			
    {
        ASSERT_FAILED();   
        Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
        return ERR;
    } 
    CPU_ESAM_CARD_Control(ESAM );   
    // ��cpu���õ�8�ֽ������" );
    if( Read(0,Get_Challenge,0,0,8) != OK )
		return ERR;
    My_Memcpy(receive_send_buffer+50,receive_send_buffer,8);
     //������ɢ������Կ" );
    if(Internal_Auth(0x80,0xfa,0,1,8,(INT8U *)cpucard_number)){
        return ERR;
    }
    if( Judge_Return_Flag() )
	    return ERR;
    
    //����8�ֽ������ ���õ�k2" );
    Internal_Auth(0x80,0xfa,0,0,8,receive_send_buffer+50);
    if( Judge_Return_Flag() )
	    return ERR;   
    My_Memcpy( receive_send_buffer+60,receive_send_buffer,8 );
    
        
    CPU_ESAM_CARD_Control(CPU);
    //��8�ֽ���������� �õ�k1 " );
    if( Internal_Auth(0,0x88,0,1,8,receive_send_buffer+50) != OK )
	return ERR;

    //"�Ƚ�k1��k2" );
    if(My_Memcmp(receive_send_buffer+60,receive_send_buffer,8))  
        {
        Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr=1;
        ASSERT_FAILED();
        return ERR;      
        }  
      
  
    return OK; //�ڲ���֤����//
}

/*"**************************************************************************"*/
INT8U Cpucard_External_Auth(void)
{

    if(Check_Cpu_Card_Out())			
        {
         ASSERT_FAILED();
        Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
        return ERR;
        }
    CPU_ESAM_CARD_Control(CPU);    /*"����ͨ��CPU���� "*/  
    Debug_Print("��cpu���õ�8�ֽ������" );
    Read(0,Get_Challenge,0,0,8);  /*"ȡCPU���漴�� "*/ 
    if( Judge_Return_Flag() )
    {
     ASSERT_FAILED();  
     return ERR;
    }
	   
    
    My_Memcpy(receive_send_buffer+150,receive_send_buffer,8);  /*"ת������� "*/  
    CPU_ESAM_CARD_Control(ESAM);   /*"����ͨ��ESAM��"*/
    Debug_Print("esam ������ɢ ������Կ " );
    Internal_Auth(0x80,0xfa,0,2,8,(INT8U *)cpucard_number);      /*"����ESAM�����"*/
    if( Judge_Return_Flag() )
	    return ERR;
   Debug_Print("esam������Կ��������� �õ�k1 " );
    Internal_Auth(0x80,0xfa,0,0,8,receive_send_buffer+150);
    if( Judge_Return_Flag() )
	    return ERR;
   Debug_Print(" cpu�� ���� k1 ���ⲿ��֤��" );
    CPU_ESAM_CARD_Control(CPU);    /*"����ͨ��CPU��"*/
    My_Memcpy(receive_send_buffer+100,receive_send_buffer,8);     /*"ת�������"*/      

    if( External_Auth(2,8,receive_send_buffer+100) != OK )
    	{
        ASSERT_FAILED();  
	Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr=1;
	return ERR;
    	}
    if( Judge_Return_Flag() )
    {
      ASSERT_FAILED();
      return ERR;
    }
	    

    return OK;  /*"CPU���ⲿ��֤����"*/                                  
}
    
/*"**************************************************************************"*/
INT8U Esamcard_External_Auth(void)
	{                  
	if(Check_Cpu_Card_Out())			
		{
                ASSERT_FAILED();   
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return ERR;
		}


	CPU_ESAM_CARD_Control(ESAM);   /*"����ͨ��ESAM��"*/
  
	Read(0,Get_Challenge,0,0,8);
	if( Judge_Return_Flag() )
        {
          ASSERT_FAILED();
          return ERR;
        }
		
  
	CPU_ESAM_CARD_Control(CPU);   /*"����ͨ��CPU��"*/
	My_Memcpy(receive_send_buffer+100,receive_send_buffer,8);     /*"ת�������"*/  
    
	Internal_Auth(0,0x88,0,2,8,receive_send_buffer+100);
	if( Judge_Return_Flag() )
		return ERR;
  
	CPU_ESAM_CARD_Control(ESAM);   /*"����ͨ��ESAM��"*/
	My_Memcpy(receive_send_buffer+100,receive_send_buffer,8);     /*"ת�������"*/  

	My_Memcpy(receive_send_buffer+108,(INT8U *)cpucard_number,LENGTH_CARD_ID_WHEN_CARD_INSERT);

	if( External_Auth(1,0x10,receive_send_buffer+100) != OK )
		{
                ASSERT_FAILED();  
		Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr=1;
		return ERR;
		}
	if( Judge_Return_Flag() )
        {
          ASSERT_FAILED();
          return ERR;
        }
	return OK;  /*"ESAM���ⲿ��֤����"*/        
	}

/*"**************************************************************************"*/
/*" ���ܣ�Ǯ���ļ�ʣ���Ѷ�����CPU�� "*///1,0   3,4
INT8U Remain_Money_Moneybag_To_Cpu_Step(INT8U Rec_Addr,INT8U Rec_Offset)
{
	INT8U temp_buffer_2[30],Order_Head[4];

	  Debug_Print("��cpu���õ�4�ֽ������  " );//821C48C29000
	CPU_ESAM_CARD_Control(CPU);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
        {
          ASSERT_FAILED();
          return ERR;
        }
		
       //04B2010C11 + RAND +04D6820008 1ED01F5FEAF7B53C
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xD6;
	temp_buffer_2[6]=0x82;
	temp_buffer_2[7]=Rec_Offset;//0,4
	temp_buffer_2[8]=0x08;/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/

	My_Memcpy(temp_buffer_2+9,(INT8U *)cpucard_number,LENGTH_CARD_ID_WHEN_CARD_INSERT);
	CPU_ESAM_CARD_Control(ESAM);
         Debug_Print(" ���� + mac  + ��ɢ�� ��esam  ���� Ǯ����mac " );//00000000573A712C9000
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB2;
	Order_Head[2] = Rec_Addr;//1,3
	Order_Head[3] = 0x0C;
	if( CPU_Card_Driver((const INT8U *)Order_Head,0x11,temp_buffer_2,0,CommunicationPortMode,0x08)!= OK )/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/
		return ERR;
         //04D6820008 +XX
	CPU_ESAM_CARD_Control(CPU);
	My_Memcpy(temp_buffer_2,receive_send_buffer,0x08);/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/
         Debug_Print(" ���� + mac дcpu��  " );
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x82;
	Order_Head[3] = Rec_Offset;//0,4
	if( CPU_Card_Driver((const INT8U *)Order_Head,0x08,temp_buffer_2,0,CommunicationPortMode,0)!= OK )/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/
        {
          Debug_Print(" ���� + mac дcpu��  дʧ�� " );
          ASSERT_FAILED();
          return ERR;
        }
		

    return OK;
}

/*"**************************************************************************"*/
/*" ���ܣ�Ǯ���ļ�ʣ���ѻ򹺵������ʼ�� "*/
/*" Length_LE: �����ݳ��� "*/
INT8U Remain_Money_Moneybag_Step(INT8U Rec_Addr,INT8U Rec_Offset)
	{
	INT8U temp_buffer_2[30],Order_Head[4];
	
	CPU_ESAM_CARD_Control(ESAM);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
       return ERR;

	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xDC;
	temp_buffer_2[6]=Rec_Addr;
	temp_buffer_2[7]=0x0C;
//	temp_buffer_2[8]=0x10;
	temp_buffer_2[8]=0x08;
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x82;
	Order_Head[3] = Rec_Offset;
	if( CPU_Card_Driver((const INT8U *)Order_Head,9,temp_buffer_2,0,CommunicationPortMode,0x08)!= OK )
		return ERR;

	CPU_ESAM_CARD_Control(ESAM);
//	My_Memcpy(temp_buffer_2,cpucard_number,8);
//	My_Memcpy(temp_buffer_2+8,receive_send_buffer,0x08);
	My_Memcpy(temp_buffer_2,receive_send_buffer,0x08);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xDC;
	Order_Head[2] = Rec_Addr;
	Order_Head[3] = 0x0C;
//	if( CPU_Card_Driver((const INT8U *)Order_Head,0x10,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
	if( CPU_Card_Driver((const INT8U *)Order_Head,0x08,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;
	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ�Ǯ���ļ���ʼ�� "*/
/*" Length_LE: �����ݳ��� "*/
INT8U Remain_Money_Moneybag_Init(void)
	{
        //��ȡcpu��Ǯ���ļ��� ����esam��Ǯ���ļ�
	if( Remain_Money_Moneybag_Step(1,0) !=OK )
		return ERR;
       
	if( Remain_Money_Moneybag_Step(3,4) != OK )
		return ERR;
    return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ�ʣ����Ǯ���ļ�����ESAM���ݻس��� "*/
INT8U Remain_Money_Moneybag_To_Cpu()
	{
	if( Remain_Money_Moneybag_To_Cpu_Step(1,0) !=OK )
		return ERR;
	if( Remain_Money_Moneybag_To_Cpu_Step(3,4) != OK )
		return ERR;
	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ���ESAMǮ���ļ�ʣ���Ѻ͹������ "*/
INT8U Read_Esam_Moneybag_File(INT8U * Moneybag_Data_Point)
	{	
  
	CPU_ESAM_CARD_Control(ESAM);
        
	if(Read(0,0xb2,0x01,0x0C,0x04)!=OK) 
		return ERR; 
	My_memcpyRev(Moneybag_Data_Point,receive_send_buffer,4);
	if(Read(0,0xb2,0x03,0x0c,0x04)!=OK)
       	return ERR; 
	My_memcpyRev(Moneybag_Data_Point+4,receive_send_buffer,4);
	return OK;  
	}

/*"**************************************************************************"*/
/*" ���ܣ�ESAMǮ���ļ�ʣ���ѿ۳����� "*/
/*" �������ֵ�ʱ���� "*/
/*" Flag=0���ֵ�ʱ����ã�Flag��1�ϵ������ʱ����� "*/
//INT32U Reamin_Money_ESAM;
INT32U Reamin_Money_ESAM_Dec_Time;
void Esam_Remain_Money_Do(INT8U Flag)
	{
	}

/*"**************************************************************************"*/
/*" ���ܣ�Ǯ���ļ�ʣ�����ۼ� "*/
/*" �¿��͹��翨�� "*/               // 2,0,0 ,           1,4,0
INT8U Remain_Money_Moneybag_Add(INT8U File_Name,INT8U Offset,
		INT8U * Remain_Money_Point)
	{
	INT8U  temp_buffer_2[30],Order_Head[4];

	//��esam�õ�4byte�����
	CPU_ESAM_CARD_Control(ESAM);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
		return ERR;
        ///����+mac�� cpu���ļ� ������mac 
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x84;
	temp_buffer_2[5]=0x32;
	temp_buffer_2[6]=0x01;
	temp_buffer_2[7]=0x0c;
	temp_buffer_2[8]=0x0C;
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+File_Name;
	Order_Head[3] = Offset;
	if( CPU_Card_Driver((const INT8U *)Order_Head,9,temp_buffer_2,0,CommunicationPortMode,0x0C)!= OK )
		return ERR;
        
	if( Remain_Money_Point != 0 )//�ж�Ҫ��Ҫ�Ѵ�cpu��������������������壬��Ϊ�����ʹ�����Է���
	{
		My_memcpyRev(Remain_Money_Point,receive_send_buffer,4);
		My_memcpyRev(Remain_Money_Point+4,receive_send_buffer+4,4);
	}
	else
        {//esamǮ���ļ���ֵ   ����+mac  ��ֵ
		CPU_ESAM_CARD_Control(ESAM);
		My_Memcpy(temp_buffer_2,receive_send_buffer,0x0C);
		Order_Head[0] = 0x84;
		Order_Head[1] = 0x32;
		Order_Head[2] = 0x01;
		Order_Head[3] = 0x0C;
		if( CPU_Card_Driver((const INT8U *)Order_Head,0x0C,temp_buffer_2,0,CommunicationPortMode,0)!= OK )/*" 6�ֽ�Ϊ0x18,4�ֽ�Ϊ0x14 "*/
			return ERR;
	}
           return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ��õ�Esam��CPU�ļ�����Ϣ "*/
/*" ���ݰݷ�˳��Ϊ��λ�ڵ��ֽ� "*/
INT8U Get_File_Data(INT8U Door,INT8U File,INT8U Offset,
							INT8U Length,INT8U * Point)
	{
	CPU_ESAM_CARD_Control(Door);
	if( Read(0,Read_Binary,0x80+File,Offset,Length) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
		
	if( Door==ESAM )
		My_Memcpy(Point,receive_send_buffer,Length);
	else
		My_memcpyRev(Point,receive_send_buffer,Length);
	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ�Esam�����ļ����� "*/
/*" Cpu_File_Name: "*/
/*" Esam_File_Name: "*/
/*" Cpu_Start_Addr: "*/
/*" Esam_Start_Addr: "*/
/*" Updata_Data_L: "*///01  02   0404 02//01 02 0a 0a 05
INT8U Esam_File_Updata(INT8U Cpu_File_Name,
									INT8U Esam_File_Name,
							   		INT8U Cpu_Start_Addr,
							   		INT8U Esam_Start_Addr,
							   		INT8U Updata_Data_L,
							   		INT8U * Data_Output_Point)
	{
	INT8U temp_buffer_2[30],Order_Head[4];
	INT8U Head_Length;

	//�õ������
         Debug_Print("/�õ������ "  );
	CPU_ESAM_CARD_Control(ESAM);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
		return ERR;
        //����+mac��cpu���������ļ�
         Debug_Print("/����+mac��cpu���������ļ� "  );
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xD6;
	temp_buffer_2[6]=0x80+Esam_File_Name;//2
	temp_buffer_2[7]=Esam_Start_Addr;//4
	temp_buffer_2[8]=Updata_Data_L+4;// ����涨�˴�cpu���������ֽڣ�ΪʲôҪ��4,����Ϊдesam��ʱ��Ҫ����4�ֽ�mac��
	if( Meter_Ins_Flag == 0xFF ){
		Head_Length = 0x11;
		temp_buffer_2[9] = 0x00;
		temp_buffer_2[10] = 0x00;
		My_Memcpy(&temp_buffer_2[11], (INT8U *)Pre_Payment_Para.BcdMeterID,6);
	}
	else
		Head_Length = 0x09;
	
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+Cpu_File_Name;//1
	Order_Head[3] = Cpu_Start_Addr;//4
	if( CPU_Card_Driver( (const INT8U *)Order_Head,Head_Length,temp_buffer_2,0,CommunicationPortMode,Updata_Data_L+4)!= OK )
		return ERR;
        //��Ϊ+mac  дesam �������ļ� 
         Debug_Print("��Ϊ+mac  дesam �������ļ� "  );
	CPU_ESAM_CARD_Control(ESAM);
        //��������Ĳ���� �����receive_send_buffer ��������ݳ���Ϊ��Updata_Data_L+4������Ϊ����CPU_Card_Driver������ʱ��
        //����CPU_Card_Driver�����Ĳ���W_Data ��receive_send_buffer  ����Ϊͬһ�����壬Ҫ��һ������������CPU_Card_Driver
        //����Ҫ��һ����Ļ��嵫�ǲ�����temp_buffer_2����̫С�ˣ�����Card_WR_Buff������������б�Data_Output_Point
        //����������� �����Ի�Ҫһ���Ƚϴ�Ļ��壬(INT8U *)Pub_Buf0 
        mem_cpy( AppleBuffer,receive_send_buffer,Updata_Data_L+4,AppleBuffer,Length_AppleBuffer);
	if( Data_Output_Point!=0 )
		My_Memcpy(Data_Output_Point,receive_send_buffer,Updata_Data_L);
        
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x80+Esam_File_Name;//2
	Order_Head[3] = Esam_Start_Addr;//4
	if( CPU_Card_Driver((const INT8U *)Order_Head,Updata_Data_L+4, AppleBuffer,0,CommunicationPortMode,0)!= OK )
		return ERR;
        
	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ�CPU�������ļ����� "*/
/*" Cpu_File_Name: "*/
/*" Esam_File_Name: "*/
/*" Cpu_Start_Addr: "*/
/*" Esam_Start_Addr: "*/
/*" Updata_Data_L: "*///04,03,0,0,240 ����1�ļ����� 
INT8U Cpu_File_Updata(INT8U Cpu_File_Name,
								    INT8U Esam_File_Name,
							   		INT8U Cpu_Start_Addr,
							   		INT8U Esam_Start_Addr,
							   		INT8U Updata_Data_L)
{

	INT8U temp_buffer_2[30],Order_Head[4];
	Debug_Print(" ��ʼcpu���ļ����� cpu���ļ���ʾ��%d esam�ļ���ʾ:%d    ",Cpu_File_Name,Esam_File_Name  );
         Debug_Print("  //�õ������    "  );//0084000004 B72B44369000  Debug_Print(" "  );
	CPU_ESAM_CARD_Control(CPU);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
		return ERR;
       
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xD6;
	temp_buffer_2[6]=0x80+Cpu_File_Name;
	temp_buffer_2[7]=Cpu_Start_Addr;
	temp_buffer_2[8]=Updata_Data_L+4;//����涨�˴�cpu���������ֽڣ�ΪʲôҪ��4,����Ϊдesam��ʱ��Ҫ����4�ֽ�mac��
        //04B0830011 71DDD3FD +  04D68200+changdu 1ED01F5FEAF7B53C
	My_Memcpy(temp_buffer_2+9,(INT8U *)cpucard_number,LENGTH_CARD_ID_WHEN_CARD_INSERT);
         Debug_Print("  // ����+ mac +��ɢ  ��ȡesam  �������ļ�     "  );//
	CPU_ESAM_CARD_Control(ESAM);
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+Esam_File_Name;//2
	Order_Head[3] = Esam_Start_Addr;
	if( CPU_Card_Driver( (const INT8U *)Order_Head,0x11,temp_buffer_2,0,CommunicationPortMode,Updata_Data_L+4)!= OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
        //04D68300 changdu +shuju
        Debug_Print("   ����+macд cpu��  Updata_Data_L+4:%d ",Updata_Data_L+4  );
       //��������Ĳ���� �����receive_send_buffer ��������ݳ���Ϊ��Updata_Data_L+4������Ϊ����CPU_Card_Driver������ʱ��
        //����CPU_Card_Driver�����Ĳ���W_Data ��receive_send_buffer  ����Ϊͬһ�����壬Ҫ��һ������������CPU_Card_Driver
        //����Ҫ��һ����Ļ��嵫�ǲ�����temp_buffer_2����̫С�ˣ�����Card_WR_Buff������������б�Data_Output_Point
        //����������� �����Ի�Ҫһ���Ƚϴ�Ļ��壬:(INT8U *)Pub_Buf0
	CPU_ESAM_CARD_Control(CPU);
        mem_cpy( AppleBuffer,receive_send_buffer,Updata_Data_L+4, AppleBuffer,700);
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x80+Cpu_File_Name;//3
	Order_Head[3] = Cpu_Start_Addr;//
	if( CPU_Card_Driver((const INT8U *)Order_Head,Updata_Data_L+4,AppleBuffer,0,CommunicationPortMode,0)!= OK )
        {
          ASSERT_FAILED();
          return ERR; 
        }

	return OK;
}
/*"**************************************************************************"*/
/*" ���ܣ�CPU���������ļ����� "*/
/*" CPU_File_Name: "*/
/*" CPU_Counter_Length: "*/
/*"��������һ8030001404+00000001 "*/
INT8U CPU_Counter_Dec(INT8U CPU_File_Name,INT8U CPU_Counter_Length)
	{
	INT8U Order_Head[4];
	
	CPU_ESAM_CARD_Control(CPU);
	Order_Head[0] = 0;
	Order_Head[1] = 0;
	Order_Head[2] = 0;
	Order_Head[3] = 1;
	if(Write(0x80,0x30,00,CPU_File_Name,CPU_Counter_Length,Order_Head)!=OK)
        {
        
          ASSERT_FAILED();
          return ERR;
        }
		

	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ���Կ���� "*/
/*"801a1e0108+0000+ ��� "*/
/*"801a1e0208+0000+���"*/
/*"801a1e0608+0000+���"*/
/*"801a1e0708+0000+���"*/
/*"bfe6000203010300"*/               
/*"bfe6000203010500"*/
/*"bfe6000203010900"*/
/*"bfe6000203010a00"*/
/*"84d401ff20+ DATA"*/               
/*"84d401ff20+ DATA"*/
/*"84d401ff20+ DATA"*/
/*"84d401ff20+ DATA"*/
INT8U Esam_Safe_Password_Updata(INT8U Password_Addr,
											    INT8U Password_Off,
											    INT8U Card_ID)
	{
	INT8U Order_Head[4],temp_buffer_2[32];
	INT8U i;

	CPU_ESAM_CARD_Control(CPU);
	Order_Head[0] = 0x80;
	Order_Head[1] = 0x1A;
	Order_Head[2] = 0x1E;
	Order_Head[3] = Password_Addr;
	temp_buffer_2[0] = 0;
	temp_buffer_2[1] = 0;//
	My_Memcpy(temp_buffer_2+2,(INT8U *)Pre_Payment_Para.BcdMeterID  ,6); 
	if( Card_ID==GWFAR_RES_PASSWORD_CARD )
		{
		for( i=0;i<8;i++ )
			temp_buffer_2[i] = 0;
		temp_buffer_2[7] = 1;
		}
	if( CPU_Card_Driver((const INT8U *)Order_Head,8,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	Order_Head[0] = 0xBF;
	Order_Head[1] = 0xE6;
	Order_Head[2] = 0x00;
	Order_Head[3] = 0x02;

	temp_buffer_2[0] = 0x01;
	temp_buffer_2[1] = Password_Off;
	temp_buffer_2[2] = 0x00;
	if( CPU_Card_Driver((const INT8U *)Order_Head,3,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	My_Memcpy(temp_buffer_2,receive_send_buffer,0x20); 

	CPU_ESAM_CARD_Control(ESAM);
	Order_Head[0] = 0x84;
	Order_Head[1] = 0xD4;
	Order_Head[2] = 0x01;
	Order_Head[3] = 0xFF;
	if( CPU_Card_Driver((const INT8U *)Order_Head,0x20,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ���Կ���� "*/
INT8U PassWord_Updata(INT8U Card_ID)
	{
	INT8U i;
	
	if( Esam_Safe_Password_Updata(1,3,Card_ID) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
		
	if( Esam_Safe_Password_Updata(2,5,Card_ID) != OK )
		return ERR;
	if( Esam_Safe_Password_Updata(6,9,Card_ID) != OK )
		return ERR;
	if( Esam_Safe_Password_Updata(7,0x0A,Card_ID) != OK )
		return ERR;

	CPU_ESAM_CARD_Control(CPU);
	if( Read(0x00,Read_Binary,0x83,0x04,0x80 ) != OK )
		return ERR;

	My_Memcpy(Card_WR_Buff,receive_send_buffer,0x80); 
	
	CPU_ESAM_CARD_Control(ESAM);
	for(i=0;i<3;i++)
		{
		if(Write(0x84,0xd4,1,0xff,0x20,&Card_WR_Buff[32*i])!=OK)
			{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Password_Key_Updata_ERR=1;
			  return ERR; 
			}
		} 
	
	for(i=3;i<4;i++)
		{
		if(Write(0x84,0xd4,1,0x00,0x20,&Card_WR_Buff[32*i])!=OK)
			{ 
                         ASSERT_FAILED(); 
			 Card_Error_State.CardErrorState.Password_Key_Updata_ERR=1;
			 return ERR; 
			}
		} 
	return OK;
	}


//-----------------------------------------------------------------
//���ݵ����Ϣ������esam��д�ļ� "
INT8U Updata_Esam_Return_File(INT8U Order_Kind)
{
 
	Card_WR_Buff[0] = 0x68;
	Card_WR_Buff[1] = Order_Kind;//������
	Card_WR_Buff[2] = 0;
	Card_WR_Buff[3] = LENGTH_RUN_INF_DATA-1;//����ط���ȥ1 ����Ϊ �ֽڶ������⣬�ڸýṹ��ǰ������һ�����õ��ֽ�
        //��esam �Լ����ܱ��ж�ȡ����  
	Deal_Run_Inf_Data(Card_WR_Buff+4,0x80);//��4 ����Ϊ �����ĵ�ַ Ϊ ��ȥ 0x68ͷ�� �������ͶΣ����ȶ�  �ĵ�ַ
	//LENGTH_RUN_INF_DATA+4-1 ����Ϊ �õ�ַΪ Ч��ͶΣ� Cal_Add_CSΪ����Ч��ͺ�������һ����ַΪ�����Ͷε�ַ�����ڶ���Ϊ��ȥͷβ��Ч��Ͷγ��� �ټ�ȥ ����������ֽ�
	Card_WR_Buff[LENGTH_RUN_INF_DATA+4-1] = Cal_Add_CS(Card_WR_Buff+1,LENGTH_RUN_INF_DATA-1+3);//�������һ��ΪЧ��λ
	Card_WR_Buff[LENGTH_RUN_INF_DATA+5-1] = 0x16;//������־// ��ȥ�� ����Ϊ����һ�������ֽ�
	
	CPU_ESAM_CARD_Control(ESAM);
        //дesam          
	if( Write(0,Update_Binary,0x80+ESAM_RUN_INF_FILE,0,LENGTH_RUN_INF_DATA-1+6,Card_WR_Buff) != OK )
		return ERR;
	return OK;
}
//------------------------------------------------------------------
/*"Mode:��������ģʽ��1��д���ã�0�������� "*/
/*"BIT7 :1��д���ã�0�������� "*/
/*"BIT0~BIT6 ��ʾ���µڼ��ݶ� "*/
/*"Source_Point��д����ģʽ�£�Ϊ������Դ�� "*/
/*"������ģʽ�£�Ϊ����ȥ�� "*/
/*"�����������ݽṹ�е����� "*/
/*"��Ҫʹ��receive_send_buffer������ "*/
// ��д����,���û�����ESAM�� //
//struct Run_Inf_Data
//	{	
//      INT8U    temp;
//	INT8U User_Kind;					/*" �û����� "*/
//	INT8U Current_CT[3];				/*" ������������� "*/
//	INT8U Voltage_PT[3];				/*" ��ѹ��������� "*/	
//	INT8U Meter_ID[6];					/*" ��� "*/
//	INT8U Client_ID[6];				/*" �ͻ���� "*/
//	INT32U Remain_Money;				/*" ʣ���� "*/
//	INT32U Buy_Count;					/*" ������� "*/
//	INT32U Low_Zero_Money;				/*" ������ "*/
//	INT8U Password_Info[4];			/*" ��Կ��Ϣ��������״̬����ʽ���������汾 "*/
//	INT8U Unlawful_Card_Count[3];		/*" �Ƿ���������� "*/
//	INT8U Return_DT[5];				/*" ��д����ʱ�� "*/
//	};
//#define LENGTH_RUN_INF_DATA  sizeof(struct Run_Inf_Data)
//��Ϊesam�س���ʱ �� �û��� ʱʹ��
void Deal_Run_Inf_Data(INT8U * Source_Point,INT8U Mode)
{
	struct Run_Inf_Data  Run_Inf_Data;
        INT32U CurrMeter_MoneyCount;
        
        INT32U Temp ;
        INT8U  DataTemp[5];
  
        //" �û���ţ���ţ��û�����"
        mem_cpy(&Run_Inf_Data.Client_ID[0],(INT8U *)Pre_Payment_Para.UserID,6,&Run_Inf_Data.Client_ID[0],LENGTH_USER_ID);
        mem_cpy(&Run_Inf_Data.Meter_ID[0],(INT8U *)Pre_Payment_Para.BcdMeterID,6,&Run_Inf_Data.Meter_ID[0],6);
        //Run_Inf_Data.User_Kind=CardType;
        //Write_Storage_Data(_SDI_SINGLE_OR_COMPLEX_USER_KIND, &SingleKing_OrComplexKing,1);
        Read_Storage_Data(_SDI_SINGLE_OR_COMPLEX_USER_KIND, DataTemp, DataTemp, 4);
        Run_Inf_Data.User_Kind=DataTemp[0];
        ///ʣ����  
        CurrMeter_MoneyCount=Get_Left_Money();
 	My_memcpyRev( (INT8U *)&(Run_Inf_Data.Remain_Money),(INT8U *)&(CurrMeter_MoneyCount),4);
        // ������� 
        CurrMeter_MoneyCount=Get_Buy_Eng_Counts();
	My_memcpyRev( (INT8U *)&(Run_Inf_Data.Buy_Count),(INT8U *)&(CurrMeter_MoneyCount),4);
        //  ������//����ط����ܻ������
        Temp=Get_Overdraft_Money();
        Hex2Bcd(Temp, DataTemp,4,DataTemp,4);//�ӻƹ�����õ�INT32U��hex�͵� ͸֧����ת��Ϊ4���ֽڵ�BCD��
 	My_memcpyRev( (INT8U *)&(Run_Inf_Data.Low_Zero_Money),DataTemp,4);
        //  CT  //
        Read_Storage_Data(SDI_CURR_TRANS_RATIO, DataTemp, DataTemp, 4);//   �ӻƹ�����������������  
	My_memcpyRev( ( INT8U *)&(Run_Inf_Data.Current_CT),(INT8U *)DataTemp,3);//ֻҪ3���ֽ���Ϊesam��Ϊ3���ֽ�
        //  PT  //��ѹ���б仯
        Read_Storage_Data(SDI_VOLT_TRANS_RATIO, DataTemp, DataTemp, 4);//  �ӻƹ������ѹ���б仯
	My_memcpyRev((INT8U *)&(Run_Inf_Data.Voltage_PT),(INT8U *)DataTemp,3);
        //" ��esam�еõ�������Կ��Ϣ // 
	Get_File_Data(ESAM,ESAM_PASSWORD_INF_FILE,0,4,Run_Inf_Data.Password_Info);
        // �Ƿ���������� "//
        Read_Storage_Data (  _SDI_INVALID_CARD_COUNTS, &Temp, &Temp, 4  );//     
        Hex2Bcd(Temp, DataTemp,3,DataTemp,3);//
        My_memcpyRev( (INT8U *)&(Run_Inf_Data.Unlawful_Card_Count[0]),(INT8U *)DataTemp,3);
        //" ��д����ʱ�� "//
        DataTemp[0 ]=Cur_Time1.Year;
        DataTemp[ 1]=Cur_Time1.Month;
        DataTemp[ 2]=Cur_Time1.Date;
        DataTemp[ 3]=Cur_Time1.Hour;
        DataTemp[ 4]=Cur_Time1.Min;        
        mem_cpy(  &Run_Inf_Data.Return_DT[0] ,DataTemp,5, &Run_Inf_Data.Return_DT[0],5 );
        //�Ѹ����˵�  ���� ���Ƶ� ����ʵ����(INT8U *)&Run_Inf_Data + 1 ��ӦΪ���ǵ��ýṹ����ֽڶ������⣬���������һ��������� 
        mem_cpy( Source_Point,((INT8U *)&Run_Inf_Data) + 1, sizeof(struct Run_Inf_Data) - 1,Source_Point, Length_Card_WR_Buff-4 );   
}
INT8U Esam_Remain_Money_Dec(void)
{
	INT8U Order_Head[4];
	struct Moneybag_Data Moneybag_Data;
        INT32U MeterRemainMoney;
        MeterRemainMoney=Get_Left_Money();
       // Debug_Print("//��esam ��ȡ Ǯ���ļ� ��4�ֽڣ� �����࣬  " );
  	Read_Esam_Moneybag_File((INT8U *)&Moneybag_Data);
        //����е� Ǯ����� �Ƚϣ� ����� �õ����
	if( MeterRemainMoney>0 )
        {
		if( MeterRemainMoney<=Moneybag_Data.Remain_Money )
			Moneybag_Data.Remain_Money -= MeterRemainMoney;
		else
			Moneybag_Data.Remain_Money = 0;
			
	}
        //
	if(Moneybag_Data.Remain_Money>0)
        {
		Reverse_data((INT8U *)&Moneybag_Data.Remain_Money,4);
             //    Debug_Print(" ��esam�õ��Ĺ�������Ϊ��%lx",Moneybag_Data.Remain_Money );
		Order_Head[0] = 0x80;
		Order_Head[1] = 0x30;
		Order_Head[2] = 0x00;
		Order_Head[3] = 0x0C;
		if( CPU_Card_Driver((const INT8U *)&Order_Head[0],4,(INT8U *)&Moneybag_Data.Remain_Money,0,CommunicationPortMode,0)!= OK )
                {
                   ASSERT_FAILED();
                   return ERR;
                }
			
	}
        //Debug_Print("//�鿴�ۿ���esam ��ȡ Ǯ���ļ� ��4�ֽڣ� �����࣬  " );
  	//Read_Esam_Moneybag_File((INT8U *)&Moneybag_Data);
        //mem_cpy(Order_Head,(INT8U *)&Moneybag_Data,4,Order_Head,4);
        //Debug_Print(" ��esam���õ��Ĺ�����Ϊ�� %x  %x  %x  %x", Order_Head[ 3], Order_Head[ 2], Order_Head[1 ], Order_Head[0 ]  );
	
         return OK;
}
