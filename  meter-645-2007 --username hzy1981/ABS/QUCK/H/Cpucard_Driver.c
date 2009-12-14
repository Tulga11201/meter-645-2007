
#define CPUCARD_DRIVER_C_
#include "MyIncludesAll.h"


#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

   
/*"**************************************************************************"*/
unsigned char Cpucard_Esamcard_Internal_Auth(void)   /*"�ڲ���֤"*/
    {
    
    if(Check_CPU_Occur())			
    {
        ASSERT_FAILED();   
        Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
        return ERR;
    } 
    CPU_ESAM_CARD_Control(CPU);
    //
    Debug_Print(" ��cpu���õ�8�ֽ������" );
    if( Read(0,Get_Challenge,0,0,8) != OK )
		return ERR;

    My_Memcpy(receive_send_buffer+50,receive_send_buffer,8);

    Debug_Print("��8�ֽ���������� �õ�k1 " );
    if( Internal_Auth(0,0x88,0,1,8,receive_send_buffer+50) != OK )
	return ERR;
    
    My_Memcpy( receive_send_buffer+60,receive_send_buffer,8 );
    Debug_Print("������ɢ������Կ" );
    CPU_ESAM_CARD_Control(ESAM);
    if(Internal_Auth(0x80,0xfa,0,1,8,cpucard_number)){
        return ERR;
    }
    if( Judge_Return_Flag() )
	    return ERR;
    Debug_Print("����8�ֽ������ ���õ�k2" );
    Internal_Auth(0x80,0xfa,0,0,8,receive_send_buffer+50);
    if( Judge_Return_Flag() )
	    return ERR;

    CPU_ESAM_CARD_Control(CPU);
    Debug_Print("�Ƚ�k1��k2" );
    if(My_Memcmp(receive_send_buffer+60,receive_send_buffer,8))  
        {
        Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr=1;
        ASSERT_FAILED();
        return ERR;      
        }  
    return OK;  /*"�ڲ���֤����"*/  
    }

/*"**************************************************************************"*/
unsigned char Cpucard_External_Auth(void)
    {

    if(Check_CPU_Occur())			
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
    Internal_Auth(0x80,0xfa,0,2,8,cpucard_number);      /*"����ESAM�����"*/
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
        ASSERT_FAILED();  test();
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
unsigned char Esamcard_External_Auth(void)
	{                  
	if(Check_CPU_Occur())			
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

	My_Memcpy(receive_send_buffer+108,cpucard_number,8);

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
unsigned char Remain_Money_Moneybag_To_Cpu_Step(unsigned char Rec_Addr,unsigned char Rec_Offset)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];

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

	My_Memcpy(temp_buffer_2+9,cpucard_number,8);
	CPU_ESAM_CARD_Control(ESAM);
         Debug_Print(" ���� + mac  + ��ɢ�� ��esam  ���� Ǯ����mac " );//00000000573A712C9000
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB2;
	Order_Head[2] = Rec_Addr;//1,3
	Order_Head[3] = 0x0C;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x11,temp_buffer_2,0,CommunicationPortMode,0x08)!= OK )/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/
		return ERR;
         //04D6820008 +XX
	CPU_ESAM_CARD_Control(CPU);
	My_Memcpy(temp_buffer_2,receive_send_buffer,0x08);/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/
         Debug_Print(" ���� + mac дcpu��  " );
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x82;
	Order_Head[3] = Rec_Offset;//0,4
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x08,temp_buffer_2,0,CommunicationPortMode,0)!= OK )/*" 6�ֽ�Ϊ0x0A,4�ֽ�Ϊ0x08 "*/
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
unsigned char Remain_Money_Moneybag_Step(unsigned char Rec_Addr,unsigned char Rec_Offset)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];
	
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
	if( CPU_Card_Driver((const unsigned char *)Order_Head,9,temp_buffer_2,0,CommunicationPortMode,0x08)!= OK )
		return ERR;

	CPU_ESAM_CARD_Control(ESAM);
//	My_Memcpy(temp_buffer_2,cpucard_number,8);
//	My_Memcpy(temp_buffer_2+8,receive_send_buffer,0x08);
	My_Memcpy(temp_buffer_2,receive_send_buffer,0x08);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xDC;
	Order_Head[2] = Rec_Addr;
	Order_Head[3] = 0x0C;
//	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x10,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x08,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;
	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ�Ǯ���ļ���ʼ�� "*/
/*" Length_LE: �����ݳ��� "*/
unsigned char Remain_Money_Moneybag_Init(void)
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
unsigned char Remain_Money_Moneybag_To_Cpu()
	{
	if( Remain_Money_Moneybag_To_Cpu_Step(1,0) !=OK )
		return ERR;
	if( Remain_Money_Moneybag_To_Cpu_Step(3,4) != OK )
		return ERR;
	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ���ESAMǮ���ļ�ʣ���Ѻ͹������ "*/
unsigned char Read_Esam_Moneybag_File(unsigned char * Moneybag_Data_Point)
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
//unsigned long Reamin_Money_ESAM;
unsigned long Reamin_Money_ESAM_Dec_Time;
void Esam_Remain_Money_Do(unsigned char Flag)
	{
	}

/*"**************************************************************************"*/
/*" ���ܣ�Ǯ���ļ�ʣ�����ۼ� "*/
/*" �¿��͹��翨�� "*/               // 2,0,0 ,           1,4,0
unsigned char Remain_Money_Moneybag_Add(unsigned char File_Name,unsigned char Offset,
		unsigned char * Remain_Money_Point)
	{
	unsigned char  temp_buffer_2[30],Order_Head[4];

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
	if( CPU_Card_Driver((const unsigned char *)Order_Head,9,temp_buffer_2,0,CommunicationPortMode,0x0C)!= OK )
		return ERR;
        
	if( Remain_Money_Point != 0 )//�ж�Ҫ��Ҫ�Ѵ�cpu��������������������壬��Ϊ�����ʹ�����Է���
		{
		My_memcpyRev(Remain_Money_Point,receive_send_buffer,4);
		My_memcpyRev(Remain_Money_Point+4,receive_send_buffer+4,4);
		}
	else{//esamǮ���ļ���ֵ   ����+mac  ��ֵ
                  
		CPU_ESAM_CARD_Control(ESAM);
		My_Memcpy(temp_buffer_2,receive_send_buffer,0x0C);
		Order_Head[0] = 0x84;
		Order_Head[1] = 0x32;
		Order_Head[2] = 0x01;
		Order_Head[3] = 0x0C;
		if( CPU_Card_Driver((const unsigned char *)Order_Head,0x0C,temp_buffer_2,0,CommunicationPortMode,0)!= OK )/*" 6�ֽ�Ϊ0x18,4�ֽ�Ϊ0x14 "*/
			return ERR;
	}
           return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ��õ�Esam��CPU�ļ�����Ϣ "*/
/*" ���ݰݷ�˳��Ϊ��λ�ڵ��ֽ� "*/
unsigned char Get_File_Data(unsigned char Door,unsigned char File,unsigned char Offset,
							unsigned char Length,unsigned char * Point)
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
unsigned char Esam_File_Updata(unsigned char Cpu_File_Name,
									unsigned char Esam_File_Name,
							   		unsigned char Cpu_Start_Addr,
							   		unsigned char Esam_Start_Addr,
							   		unsigned char Updata_Data_L,
							   		unsigned char * Data_Output_Point)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];
	unsigned char Head_Length;

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
		My_Memcpy(&temp_buffer_2[11], Pre_Payment_Para.BcdMeterID,6);
	}
	else
		Head_Length = 0x09;
	
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+Cpu_File_Name;//1
	Order_Head[3] = Cpu_Start_Addr;//4
	if( CPU_Card_Driver( (const unsigned char *)Order_Head,Head_Length,temp_buffer_2,0,CommunicationPortMode,Updata_Data_L+4)!= OK )
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
	if( CPU_Card_Driver((const unsigned char *)Order_Head,Updata_Data_L+4, AppleBuffer,0,CommunicationPortMode,0)!= OK )
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
unsigned char Cpu_File_Updata(unsigned char Cpu_File_Name,
								    unsigned char Esam_File_Name,
							   		unsigned char Cpu_Start_Addr,
							   		unsigned char Esam_Start_Addr,
							   		unsigned char Updata_Data_L)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];

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
	My_Memcpy(temp_buffer_2+9,cpucard_number,8);
         Debug_Print("  // ����+ mac +��ɢ  ��ȡesam  �������ļ�     "  );//
	CPU_ESAM_CARD_Control(ESAM);
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+Esam_File_Name;//2
	Order_Head[3] = Esam_Start_Addr;
	if( CPU_Card_Driver( (const unsigned char *)Order_Head,0x11,temp_buffer_2,0,CommunicationPortMode,Updata_Data_L+4)!= OK )
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
	if( CPU_Card_Driver((const unsigned char *)Order_Head,Updata_Data_L+4,AppleBuffer,0,CommunicationPortMode,0)!= OK )
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
unsigned char CPU_Counter_Dec(unsigned char CPU_File_Name,unsigned char CPU_Counter_Length)
	{
	unsigned char Order_Head[4];
	
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
unsigned char Esam_Safe_Password_Updata(unsigned char Password_Addr,
											    unsigned char Password_Off,
											    unsigned char Card_ID)
	{
	unsigned char Order_Head[4],temp_buffer_2[32];
	unsigned char i;

	CPU_ESAM_CARD_Control(CPU);
	Order_Head[0] = 0x80;
	Order_Head[1] = 0x1A;
	Order_Head[2] = 0x1E;
	Order_Head[3] = Password_Addr;
	temp_buffer_2[0] = 0;
	temp_buffer_2[1] = 0;//
	My_Memcpy(temp_buffer_2+2,Pre_Payment_Para.BcdMeterID  ,6); 
	if( Card_ID==GWFAR_RES_PASSWORD_CARD )
		{
		for( i=0;i<8;i++ )
			temp_buffer_2[i] = 0;
		temp_buffer_2[7] = 1;
		}
	if( CPU_Card_Driver((const unsigned char *)Order_Head,8,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	Order_Head[0] = 0xBF;
	Order_Head[1] = 0xE6;
	Order_Head[2] = 0x00;
	Order_Head[3] = 0x02;

	temp_buffer_2[0] = 0x01;
	temp_buffer_2[1] = Password_Off;
	temp_buffer_2[2] = 0x00;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,3,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	My_Memcpy(temp_buffer_2,receive_send_buffer,0x20); 

	CPU_ESAM_CARD_Control(ESAM);
	Order_Head[0] = 0x84;
	Order_Head[1] = 0xD4;
	Order_Head[2] = 0x01;
	Order_Head[3] = 0xFF;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x20,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	return OK;
	}
/*"**************************************************************************"*/
/*" ���ܣ���Կ���� "*/
unsigned char PassWord_Updata(unsigned char Card_ID)
	{
	unsigned char i;
	
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
unsigned char Updata_Esam_Return_File(unsigned char Order_Kind)
{
        //������0�� ��Ϊ�������е����� ������������в����Ḳ�ǣ�  ��������Ҫ����Ϊ0
        mem_set(Card_WR_Buff,0x00,sizeof(LENGTH_RUN_INF_DATA)+6,Card_WR_Buff,Length_Card_WR_Buff);
	
	Card_WR_Buff[0] = 0x68;
	Card_WR_Buff[1] = Order_Kind;//������
	Card_WR_Buff[2] = 0;
	Card_WR_Buff[3] = LENGTH_RUN_INF_DATA;//����ط���ȥ1 ����Ϊ �ֽڶ������⣬�ڸýṹ��ǰ������һ�����õ��ֽ�
        //��esam �Լ����ܱ��ж�ȡ����  
	Deal_Run_Inf_Data(Card_WR_Buff+4,0x80);//��4 ����Ϊ �����ĵ�ַ Ϊ ��ȥ 0x68ͷ�� �������ͶΣ����ȶ�  �ĵ�ַ
	//LENGTH_RUN_INF_DATA+4-1 ����Ϊ �õ�ַΪ Ч��ͶΣ� Cal_Add_CSΪ����Ч��ͺ�������һ����ַΪ�����Ͷε�ַ�����ڶ���Ϊ��ȥͷβ��Ч��Ͷγ��� �ټ�ȥ ����������ֽ�
	Card_WR_Buff[LENGTH_RUN_INF_DATA+4-1] = Cal_Add_CS(Card_WR_Buff+1,LENGTH_RUN_INF_DATA-1+3);//�������һ��ΪЧ��λ
	Card_WR_Buff[LENGTH_RUN_INF_DATA+5-1] = 0x16;//������־// ��ȥ�� ����Ϊ����һ�������ֽ�
	
	CPU_ESAM_CARD_Control(ESAM);
        //дesam  
	if( Write(0,Update_Binary,0x80+ESAM_RUN_INF_FILE,0,LENGTH_RUN_INF_DATA+6,Card_WR_Buff) != OK )
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
//	unsigned char User_Kind;					/*" �û����� "*/
//	unsigned char Current_CT[3];				/*" ������������� "*/
//	unsigned char Voltage_PT[3];				/*" ��ѹ��������� "*/	
//	unsigned char Meter_ID[6];					/*" ��� "*/
//	unsigned char Client_ID[6];				/*" �ͻ���� "*/
//	unsigned long Remain_Money;				/*" ʣ���� "*/
//	unsigned long Buy_Count;					/*" ������� "*/
//	unsigned long Low_Zero_Money;				/*" ������ "*/
//	unsigned char Password_Info[4];			/*" ��Կ��Ϣ��������״̬����ʽ���������汾 "*/
//	unsigned char Unlawful_Card_Count[3];		/*" �Ƿ���������� "*/
//	unsigned char Return_DT[5];				/*" ��д����ʱ�� "*/
//	};
//#define LENGTH_RUN_INF_DATA  sizeof(struct Run_Inf_Data)
//��Ϊesam�س���ʱ �� �û��� ʱʹ��
void Deal_Run_Inf_Data(unsigned char * Source_Point,unsigned char Mode)
{
	struct Run_Inf_Data  Run_Inf_Data;
        INT32U CurrMeter_MoneyCount;
        
        INT32U Temp ;
        INT8U  DataTemp[5];
	//Run_Inf_Data = (struct Run_Inf_Data *)Source_Point;
        mem_cpy(&Run_Inf_Data,Source_Point, sizeof(struct Run_Inf_Data),&Run_Inf_Data, sizeof(struct Run_Inf_Data));
          
//" �û���ţ���ţ��û�����"
        
        My_memcpyRev(&Run_Inf_Data.Client_ID[0],Pre_Payment_Para.UserID,6);
        My_memcpyRev(&Run_Inf_Data.Meter_ID[0],Pre_Payment_Para.BcdMeterID,6);
        Run_Inf_Data.User_Kind=CardType;
 ///ʣ����  //����ط�Ҫ��
        CurrMeter_MoneyCount=Get_Left_Money();
 	My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Remain_Money),(INT8U *)&(CurrMeter_MoneyCount),4);
// ������� //����ط�Ҫ��
        CurrMeter_MoneyCount=Get_Buy_Eng_Counts();
	My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Buy_Count),(unsigned char *)&(CurrMeter_MoneyCount),4);
//  ������//����ط����ܻ������
        Temp=Get_Overdraft_Money();
        Hex2Bcd(Temp, DataTemp,4,DataTemp,4);//�ӻƹ�����õ�INT32U��hex�͵� ͸֧����ת��Ϊ4���ֽڵ�BCD��
 	My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Low_Zero_Money),DataTemp,4);
//  CT  //
        Read_Storage_Data(SDI_CURR_TRANS_RATIO, DataTemp, DataTemp, 4);//   �ӻƹ�����������������  
	My_memcpyRev( ( unsigned char *)&(Run_Inf_Data.Current_CT),(unsigned char *)DataTemp,3);//ֻҪ3���ֽ���Ϊesam��Ϊ3���ֽ�
    //  PT  //��ѹ���б仯
        Read_Storage_Data(SDI_VOLT_TRANS_RATIO, DataTemp, DataTemp, 4);//  �ӻƹ������ѹ���б仯
	My_memcpyRev((unsigned char *)&(Run_Inf_Data.Voltage_PT),(unsigned char *)DataTemp,3);
         //" ��esam�еõ���Կ��Ϣ // 
	Get_File_Data(ESAM,ESAM_PASSWORD_INF_FILE,0,4,Run_Inf_Data.Password_Info);
        // �Ƿ���������� "//
        Read_Storage_Data (  _SDI_INVALID_CARD_COUNTS, &Temp, &Temp, 4  );//     
        
        Hex2Bcd(Temp, DataTemp,3,DataTemp,3);//
        My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Unlawful_Card_Count[0]),(unsigned char *)DataTemp,3);
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
unsigned char Esam_Remain_Money_Dec(void)
{
	unsigned char Order_Head[4];
	struct Moneybag_Data Moneybag_Data;
        INT32U MeterRemainMoney;
        MeterRemainMoney=Get_Left_Money();
       // Debug_Print("//��esam ��ȡ Ǯ���ļ� ��4�ֽڣ� �����࣬  " );
  	Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data);
        //����е� Ǯ����� �Ƚϣ� ����� �õ����
	if( MeterRemainMoney>0 )
        {
		if( MeterRemainMoney<=Moneybag_Data.Remain_Money )
			Moneybag_Data.Remain_Money -= MeterRemainMoney;
		else
			Moneybag_Data.Remain_Money = 0;
			
	}
        
        if(Moneybag_Data.Remain_Money EQ 0)
        {
           return OK;
        }
        //mem_cpy(Order_Head,(INT8U *)&Moneybag_Data.Remain_Money,4,Order_Head,4);
        //Debug_Print(" ��esam���пۿ�������ۿ�ֵΪ�� %x  %x  %x  %x", Order_Head[ 3], Order_Head[ 2], Order_Head[1 ], Order_Head[0 ]  );
        //Debug_Print(" // ��esam���пۿ����  ����ǰ �� ���� " );
   
	if(Moneybag_Data.Remain_Money>0)
        {
		Reverse_data((unsigned char *)&Moneybag_Data.Remain_Money,4);
             //    Debug_Print(" ��esam�õ��Ĺ�������Ϊ��%lx",Moneybag_Data.Remain_Money );
		Order_Head[0] = 0x80;
		Order_Head[1] = 0x30;
		Order_Head[2] = 0x00;
		Order_Head[3] = 0x0C;
		if( CPU_Card_Driver((const unsigned char *)&Order_Head[0],4,(unsigned char *)&Moneybag_Data.Remain_Money,0,CommunicationPortMode,0)!= OK )
                {
                   ASSERT_FAILED();
                   return ERR;
                }
			
	}
        //Debug_Print("//�鿴�ۿ���esam ��ȡ Ǯ���ļ� ��4�ֽڣ� �����࣬  " );
  	//Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data);
        //mem_cpy(Order_Head,(INT8U *)&Moneybag_Data,4,Order_Head,4);
        //Debug_Print(" ��esam���õ��Ĺ�����Ϊ�� %x  %x  %x  %x", Order_Head[ 3], Order_Head[ 2], Order_Head[1 ], Order_Head[0 ]  );
	
         return OK;
}
