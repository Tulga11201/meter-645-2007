#define  FAR_DEAL_CTRL_0X33_C_
 
#include "MyIncludesAll.h"
#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "Q1"
#endif


#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

//Զ����֤����ӿ�(������Ϊ03)
//pSrc��ʾԶ��֡�������� ����Ϊ645֡��L�ε�ֵ
//SrcLen��ʾ�����򳤶�
//pDst��ʾ��������󷵻ص�������  ��ŵĳ���Ϊ645Э�鶨���L�ε�ֵ�ĳ���
//*pLen��ʾ���ص����ݳ���
//pDst_Start��DstLenһ���޶�pDst�ͷ��ص����ݳ���
//1�ɹ��� 0ʧ�ܣ�
INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen){
        //����ֲ�����
        INT8U  ret;
        INT32U  Far_Auth_Day_Follow;
        INT8U DataTemp[4];
        INT32U Temp;
        OS_Mutex_Pend(PUB_BUF_SEM_ID);//ʹ�û��壺Pub_Buf0
        OS_Mutex_Pend(PUB_BUF0_SEM_ID); //ʹ���ź������Ա�ʹ�û���
        //ret=GetMoney();
        // �ж������֤��Чʱ���Ƿ���ˣ�������ˣ�ID_Ins_Counter�͸�ֵΪ0
        Far_Identity_Auth_Ok_Flag=!Chk_Pay_Time_Arrive();
        //��ʼ����FarPrePayment.ID_Ins_Counter
        Read_Storage_Data(_SDI_INVALID_COUNTS_AllOW ,(INT8U *)&FarPrePayment.ID_Ins_Counter,(INT8U *)&FarPrePayment.ID_Ins_Counter, 1) ;
        if(FarPrePayment.ID_Ins_Counter != 0 )//�ж��Ƿ���Ҫ����ID_Ins_Counter ��
        {//Cur_Time0.Date
          DataTemp[0 ]=Cur_Time1.Year;
          DataTemp[ 1]=Cur_Time1.Month;
          DataTemp[ 2]=Cur_Time1.Date;
          DataTemp[ 3]=Cur_Time1.Hour;
          Read_Storage_Data(_SDI_FAR_AUTH_DAY_FOLLOW ,(INT8U *)&Far_Auth_Day_Follow, (INT8U *)&Far_Auth_Day_Follow, 4) ;
          //Get_Array_Time(T_BCD, DataTemp,DataTemp, 5);//�ӻƹ�����õ�5���ֽڵĵ�ǰʱ��bcd���룬DataTemp[0]��ʼ�ֱ�Ϊ���֣�ʱ���գ����꣬û��Ҫ������
          if( memcmp( DataTemp,(INT8U *)&Far_Auth_Day_Follow,3 )   != 0 )//�ж�������û�б��,����Ϊ3������4�������4����ÿһСʱ1��
          {
            //Far_Auth_Day_Follow=Cur_Time1.Date;
            mem_cpy((INT8U *)&Far_Auth_Day_Follow,DataTemp,4,(INT8U *)&Far_Auth_Day_Follow,4);
            Write_Storage_Data(_SDI_FAR_AUTH_DAY_FOLLOW ,&Far_Auth_Day_Follow, 4);
            FarPrePayment.ID_Ins_Counter  =0;
	    Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, (INT8U *)&FarPrePayment.ID_Ins_Counter, 1);
          }
         }
        mem_cpy(&Temp,pSrc,4,&Temp,4);
        //�ж��Ƿ��Ѿ�ͨ�� �����֤���������ݱ�ʾΪ����ȫ��֤
	if( ( Far_Identity_Auth_Ok_Flag== 1 ) || ( Temp EQ 0x70000FF  && FarPrePayment.ID_Ins_Counter<15 ) )
        {
           ret=Far_Deal_Order_0x03(pSrc,SrcLen);//  ���ǽ��������֤
        }else{
                ASSERT_FAILED();
		ret=ERR;
                FarPrePayment.Far_Error_State.CpuCardInternlAuthenticationErr=1;
		IDENTITY_AUTH_ERR_DEFINE = 1; 
	}
        ///0x33���ͺ���ִ�гɹ� //// //����1�ɹ����ƽ����ݸ�huck
	if(ret  EQ OK){
                  mem_cpy(pDst,pSrc,4,pDst_Start,DstLen);// ��������ĺ���ģ� ��ζ���²�ĺ�����ֻҪ��N1N2---Nm   ����
	          mem_cpy(pDst+4, FarPaidBuff ,FarPrePayment.Far_SendLen,pDst,DstLen);
                  FarPrePayment.Far_SendLen+=4;//�����4 ��������ĺ���ģ� ��ζ���²�ĺ�����ֻҪ��N1N2---Nm �ĳ��ȼ���
                  *pLen = FarPrePayment.Far_SendLen;
                  OS_Mutex_Post(PUB_BUF0_SEM_ID);
                  OS_Mutex_Post(PUB_BUF_SEM_ID);
		  return  1;
	}
        //���粻�ɹ�/�жϲ������//����0ʧ�ܣ������ȫ�ֱ���ֵ���ƽ����ݸ�huck
        mem_set((INT8U *)&Far_Identity_Auth_Data,0x00,sizeof(struct Far_Identity_Authentication_Define),(INT8U *)&Far_Identity_Auth_Data,sizeof(struct Far_Identity_Authentication_Define) );
        //׼������ ��ȫ����״̬��//mem_set
	if(( Far_Security_Auth_Err_Info.intd & 0xFFFE ) != 0 )
        {
           Far_Security_Auth_Err_Info.intd &= 0xFFFE;
        }else{
            OTHER_ERR_DEFINE =1;
        }
	mem_cpy( pDst, (INT8U *)&Far_Security_Auth_Err_Info.intd, 2,pDst_Start,DstLen);
        FarPrePayment.Far_SendLen=2;
        pLen=(INT8U *)&FarPrePayment.Far_SendLen;
        
        OS_Mutex_Post(PUB_BUF0_SEM_ID);
        OS_Mutex_Post(PUB_BUF_SEM_ID);
        //����Һ����ʾ������룬 Ŀǰֻ��2��
        if(FarPrePayment.Far_Error_State.Password_Key_Updata_ERR)
        {
              ReNew_Err_Code(DIS_CUR_MODI_KEY_ERR);
              
        }
        
        if(FarPrePayment.Far_Error_State.CpuCardInternlAuthenticationErr)
        {
             ReNew_Err_Code(DIS_CERTI_ERR);
            
        }
  
	return  0;  
}
//////// 0x33���͵ĺ����������������ڲ������ݶ�Ϊ��ȥ���ݱ�ʾ�Ͳ����ߴ���� ������
//���ڶ�Ϊ��Ҳ��Ҫ�����ݱ�ʾ����ֱ�Ӵ����FarPaidBuff��ǰ4���ֽڹ涨Ϊ���ݱ�ʶ,���͵ĳ��ȷ��ڣ�FarPrePayment.Far_SendLen,���Ȳ�Ҫ�����ݱ�ʶ�ĳ���
  const struct Far_645_Frame_Flag_0x03  Far_645_Frame_Flag_0x03_List[]={
	0xFF,0x01,0x80,0x07,16,Far_Deal_078001FF,//���ݻس�
        
	0x01,0x02,0x81,0x07,8,Far_Deal_07810201,//״̬��ѯ�������ݣ�ʣ�����
	0xFF,0x02,0x81,0x07,8,Far_Deal_078102FF,//ͬ��

	0xFF,0x00,0x00,0x07,32,Far_Deal_070000FF,//�����֤ 

	0xFF,0x01,0x00,0x07,14,Far_Deal_070001FF,//�����֤ʱЧ����
	0x01,0x02,0x00,0x07,8,Far_Deal_07000201,//�����֤ʧЧ
	0xFF,0x02,0x00,0x07,8,Far_Deal_070002FF,//ͬ��
//
	0xFF,0x01,0x01,0x07,30,Far_Deal_070101FF,//����

	0xFF,0x02,0x01,0x07,30,Far_Deal_070102FF,//��ֵ

	0xFF,0x01,0x02,0x07,48,Far_Deal_070201FF,//������Կ����
	0xFF,0x02,0x02,0x07,48,Far_Deal_070202FF,//����������Կ���� 
	0xFF,0x03,0x02,0x07,48,Far_Deal_070203FF,//Զ�������֤��Կ����
        0xFF,0x04,0x02,0x07,48,Far_Deal_070204FF,//������Կ����
	};
/////////0x33���ͺ�����תվ,  
INT8U Far_Deal_Order_0x03(INT8U * Data_Point ,INT8U Source_Length)
{
	INT8U i;

	for( i=0;i<S_NUM(Far_645_Frame_Flag_0x03_List);i++ )
        {
	   if(memcmp(Data_Point, (INT8U *)Far_645_Frame_Flag_0x03_List[i].Data_ID, 4) EQ 0) 
		break;
	}
	if( i EQ S_NUM(Far_645_Frame_Flag_0x03_List) )
        {
             ASSERT_FAILED();
             return ERR;
        }
       // ���Ȳ��� //
	if( Source_Length != Far_645_Frame_Flag_0x03_List[i].Source_Length )
        {
            ASSERT_FAILED();
            return ERR;		
        }	
	if( Far_645_Frame_Flag_0x03_List[i].Far_645_Order_0x03 !=0 )
        {
                //Data_Point+LENGTH_FAR_645_FRAME_0X03 Ϊ��ȥ���ݱ�ʾ�Ͳ����ߴ���� ������
		if( Far_645_Frame_Flag_0x03_List[i].Far_645_Order_0x03(Data_Point+8) EQ OK )
			return OK;
	}
        ASSERT_FAILED();
	return ERR;
}
 /*"**************************************************************************"*/
/*"  �����֤ "*/
/*"  ֧��070000FF  "*/
/*" Data_Point:��:8+8+8��Data_Point�� ��������Ϊ��"����1  �����1 ��ɢ����*/
/*"            ��:4+8 ����FarPaidBuff��"*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
INT8U Far_Deal_070000FF(INT8U * Data_Point )
{     
      
        INT16U ValidTimeTemp;
        //����״̬����0��
        Far_Security_Auth_Err_Info.intd=0;
        Card_Error_State.CardErrorState_INT32U=0;
        mem_set((INT8U *)&FarPrePayment.Far_Error_State,0x00,sizeof(FarPrePayment.Far_Error_State),(INT8U *)&FarPrePayment.Far_Error_State,sizeof(FarPrePayment.Far_Error_State));
		
        ///esam��λ
        if( (Esamcard_Reset() )!=OK )
        { 
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;
        } 
        mem_cpy((INT8U *)esam_number,receive_send_buffer+5,8,(INT8U *)esam_number,8);
        CPU_ESAM_CARD_Control(ESAM);
        if( Select_Directry(0,0x3F,00) != OK )
        {
                ASSERT_FAILED();
                Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;
        }	
	///��ʼԶ�������֤
	if(Far_Esamcard_Internal_Auth(Data_Point)==OK)
        {
		if( Read(0,Get_Challenge,0,0,4) != OK )
                {
                        ASSERT_FAILED();
			OTHER_ERR_DEFINE =1;
			return ERR;
		}
                //��װҪ���͵�����
		My_memcpyRev(FarPaidBuff,receive_send_buffer,4);    //ת�������2//
		 //My_Memcpy(FarPaidBuff,receive_send_buffer,4);    //ת�������2//
		
                My_memcpyRev(FarPaidBuff+4,(INT8U *)esam_number,8);     //ת��ESAM���к�//
		FarPrePayment.Far_SendLen=12;//��Ҫ�����ݱ�ʾ�ĳ��ȣ���������Զ���4
                //FarPrePayment.Far_SendLen=0;//��Ҫ�����ݱ�ʾ�ĳ��ȣ���������Զ���4
                //�����֤��Чʱ����ʼ�� 
		Far_Identity_Auth_Ok_Flag=1;	
		if(Far_Read_Esam(04,Read_Binary,0x80+ESAM_PARA_INF_FILE,IDENTITY_AUTH_TIME_ESAM, 2, 0)!=OK)
                {
                   ASSERT_FAILED();
                   return ERR;
                }
                Reverse_data((INT8U *) &receive_send_buffer[0],2);
                //ValidTimeTemp=Bcd2Hex((INT8U *)&ValidTimeTemp , 2);
                ValidTimeTemp=Bcd2Hex((INT8U *) &receive_send_buffer[0], 2);
                if(ValidTimeTemp EQ 0 )
                {
                   ValidTimeTemp=5;
                }
                Reset_Pay_Timer(ValidTimeTemp*60);// 

                return OK;
	}
        FarPrePayment.Far_Error_State.CpuCardInternlAuthenticationErr=1;
        ASSERT_FAILED();
	IDENTITY_AUTH_ERR_DEFINE = 1;
	return ERR;
}
///
INT8U Far_Read_Esam(INT8U cla,INT8U ins,INT8U t_p1,
              INT8U t_p2,INT8U lc,INT8U *address)
{
	INT8U Order_Head[4];

	My_memcpyRev( Card_WR_Buff, (INT8U *)&Far_Identity_Auth_Data.Instruction.random_number1[4], 4);
        //
	*(Card_WR_Buff+4)=0x04;
	*(Card_WR_Buff+5)=0xd6;
	*(Card_WR_Buff+6)=0x86;	//guding
	if( ins == Read_Record )
		*(Card_WR_Buff+7)=0;		//guding
	else
		*(Card_WR_Buff+7)=t_p2;
	Card_WR_Buff[8]=lc+12;	//data+mac+disperse_gene
	//Card_WR_Buff[8]=lc+4;	//data+mac+disperse_gene
        My_memcpyRev(Card_WR_Buff+9, (INT8U *)&Far_Identity_Auth_Data.Instruction.disperse_gene[0], 8);
        //����+mac+��ɢ��
	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver((const INT8U *)Order_Head,0x11,Card_WR_Buff,0,CommunicationPortMode,lc+4)!= OK )
	{
                  ASSERT_FAILED();
		  OTHER_ERR_DEFINE =1;
	          return ERR;
	}

	return OK;
}
///
/*"**************************************************************************"*/
/*" дESAM�� ����MAC  д"*/
INT8U Far_Write_Esam(INT8U cla,INT8U ins,INT8U t_p1,
			INT8U t_p2,INT8U lc,INT8U *address,INT8U Flag )
{
	INT8U i;   
	INT8U Order_Head[4];
       // INT8U  MyMac[4];
 
	CPU_ESAM_CARD_Control(ESAM);

	if( Flag )
	{        //�����Կ��Ϣ���ݣ�ǰ��4���ֽ�Ϊmac ��4��Ϊ���� ��    
                  //Ȼ������վ��Ϣ���˺�д����ʱ��Ҫ��תmac�����ݣ���Ҫ��mac�����ݵ�λ�ý��������
		My_memcpyRev( Card_WR_Buff , address,lc+4);
	}
	else
	{
                //һ������£�ǰ��Ϊ���ݣ� ����Ϊmac  
		My_memcpyRev( Card_WR_Buff, address,lc);
		My_memcpyRev(Card_WR_Buff+lc, address+lc,4);
        }

	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver((const INT8U *)Order_Head,lc+4,Card_WR_Buff,0,CommunicationPortMode,0)!= OK ){
          
                FarPrePayment.Far_Error_State.CpuCardInternlAuthenticationErr=1;//Һ����ʾ�����֤����
		ESAM_AUTH_ERR_DEFINE =1;
		FarPrePayment.ID_Ins_Counter++;
                Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, (INT8U *)&FarPrePayment.ID_Ins_Counter, 1);
		if((FarPrePayment.ID_Ins_Counter %3)==0 ||  FarPrePayment.ID_Ins_Counter >=15){
                        Reset_Pay_Timer(0);
			Far_Identity_Auth_Ok_Flag=0;
	                Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,receive_send_buffer,receive_send_buffer,Length_receive_send_buffer );

		}
                ASSERT_FAILED();
		return ERR;
	}
        FarPrePayment.ID_Ins_Counter  =0;
	Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, (INT8U *)&FarPrePayment.ID_Ins_Counter, 1);
	return OK;
}
INT8U Far_Esamcard_Internal_Auth(INT8U *Point)   //Զ��ϵͳ�����֤//
	{
	My_memcpyRev(Card_WR_Buff+110, Point, 8);       //"ת������1//  
	My_memcpyRev(Card_WR_Buff+100, Point+8, 8);    //"ת�������1//   
	My_memcpyRev(Card_WR_Buff+1, Point+16, 8);     //ת��ɢ����1//  

	CPU_ESAM_CARD_Control(ESAM);      //"����ͨ��ESAM��"//
	Internal_Auth(0x80,0xfa,0,3,8,Card_WR_Buff+1); //��ɢ//
	if( Judge_Return_Flag() )
        {
          ASSERT_FAILED();
           return ERR;
        }
		

	Internal_Auth(0x80,0xfa,0,0,8,Card_WR_Buff+100); //�õ�ESAM��������� //
	if( Judge_Return_Flag() )
        {
           ASSERT_FAILED();
           return ERR;
        }
		

	if(My_Memcmp(Card_WR_Buff+110,receive_send_buffer,8))  {
                ASSERT_FAILED();
		return ERR;      
	}
        //������Far_Identity_Auth_Data���г�ʼ���������ǲ��֣�ʹ��ʱ��Ҫ����
	My_Memcpy((INT8U *)&Far_Identity_Auth_Data.Instruction.cryptograph1[0], Point, sizeof(struct Authentication_Instruction));
	return OK;  /*"�ڲ���֤����"*/  
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*"**************************************************************************"*/
/*" ���ݻس�"*/
/*" ֧��07800101,078001FF "*/
/*" Data_Point:��:8�ֽ����ݻس���ʶ "*/
/*"            ��:8�ֽ����ݻس���ʶ+�س�������+MAC "*/
/*"**************************************************************************"*/
struct Far_Read_078001FF_Format
	{
	INT16U	Data_Length;
	INT16U	Data_Start_Addr;
	INT16U	File;
	INT16U	Name;
	};

INT8U Far_Deal_078001FF(INT8U *Data_Point )
{
	struct Far_Read_078001FF_Format	 Far_Read_078001FF_Format;
	INT8U Offset;
        mem_cpy(&Far_Read_078001FF_Format,Data_Point,sizeof(struct Far_Read_078001FF_Format),&Far_Read_078001FF_Format,sizeof(Far_Read_078001FF_Format));
        
        if( (INT8U)(Far_Read_078001FF_Format.File) == 0x01 ){
		if(Far_Read_Esam(                                       0x04,Read_Record,0x01,
							                                    0x0C,
					                                                      4 , 
						              			 Data_Point)!=OK)
                {
                    ASSERT_FAILED();
                    return ERR;  
                }
                mem_cpy(FarPaidBuff,Data_Point,8,FarPaidBuff,Length_FarPaidBuff);//8�ֽ����ݻس���ʶ
	        My_memcpyRev( FarPaidBuff+8,receive_send_buffer,4 );
                My_memcpyRev( FarPaidBuff+8+4,receive_send_buffer+4,4 );
                ///  
		if(Far_Read_Esam(                                       0x04,Read_Record,0x03,
							                                    0x0C,
					                                                      4 , 
						              			 Data_Point)!=OK)
                {
                    ASSERT_FAILED();
                    return ERR;  
                }
                
                My_memcpyRev( FarPaidBuff+8+8,receive_send_buffer,4 );
                My_memcpyRev( FarPaidBuff+8+8+4,receive_send_buffer+4,4 );
                FarPrePayment.Far_SendLen = 8+8+8;
	}
        /*
        ///
	if( (INT8U)(Far_Read_078001FF_Format.File) == 0x01 ){
		if( (INT8U)(Far_Read_078001FF_Format.Data_Start_Addr )== 0x00 )
			Offset = 0x01;
		else
			Offset = 0x03;
		if(Far_Read_Esam(                                       0x04,Read_Record,Offset,
							                                    0x0C,
					   (INT8U)(Far_Read_078001FF_Format.Data_Length), 
						              			 Data_Point)!=OK)
                {
                    ASSERT_FAILED();
                    return ERR;  
                }
        mem_cpy(FarPaidBuff,Data_Point,8,FarPaidBuff,Length_FarPaidBuff);//8�ֽ����ݻس���ʶ
	My_memcpyRev( FarPaidBuff+8,receive_send_buffer,(( INT8U)(Far_Read_078001FF_Format.Data_Length)) );
	My_memcpyRev( FarPaidBuff+8+((INT8U )(Far_Read_078001FF_Format.Data_Length)),receive_send_buffer+((INT8U)(Far_Read_078001FF_Format.Data_Length)), 4);
	FarPrePayment.Far_SendLen = 8+((INT8U)(Far_Read_078001FF_Format.Data_Length))+4;
        }
        */
	else{
/*"04b082��83��84��86��+ P2(ƫ�Ƶ�ַ)��11+4�ֽ������1+04d686+00+LC+8�ֽڷ�ɢ���ӡ�
LC����Ҫ��ȡ���������ݣ�MAC+��ɢ���ӵ��ܳ��ȣ�����1�ֽڵ�ʮ����������"*/

		if(Far_Read_Esam(0x04,Read_Binary,0x80+(INT8U)(Far_Read_078001FF_Format.File),
											 (INT8U)(Far_Read_078001FF_Format.Data_Start_Addr),
											 (INT8U)(Far_Read_078001FF_Format.Data_Length), 
											 Data_Point)!=OK)
                {
                   ASSERT_FAILED();
                   return ERR;
                }
			
	
        //��װ���͵������򣬲������ݱ�ʾ��/////////0x33���ͺ�����תվ, 0x33���͵ĺ����������������ڲ������ݶ�Ϊ��ȥ���ݱ�ʾ�Ͳ����ߴ���� ������
//���ڶ�Ϊ��Ҳ��Ҫ�����ݱ�ʾ����ֱ�Ӵ����FarPaidBuff
        mem_cpy(FarPaidBuff,Data_Point,8,FarPaidBuff,Length_FarPaidBuff);//8�ֽ����ݻس���ʶ
	My_memcpyRev( FarPaidBuff+8,receive_send_buffer,(( INT8U)(Far_Read_078001FF_Format.Data_Length)) );
	My_memcpyRev( FarPaidBuff+8+((INT8U )(Far_Read_078001FF_Format.Data_Length)),receive_send_buffer+((INT8U)(Far_Read_078001FF_Format.Data_Length)), 4);
        //My_Memcpy( FarPaidBuff+8+((INT8U )(Far_Read_078001FF_Format.Data_Length)),receive_send_buffer+((INT8U)(Far_Read_078001FF_Format.Data_Length)), 4);
	
        FarPrePayment.Far_SendLen = 8+((INT8U)(Far_Read_078001FF_Format.Data_Length))+4;
        }
	
//	My_memcpyRev( far_data_p+14,receive_send_buffer,((INT8U)(Far_Read_078001FF_Format->Data_Length)) );
//	My_memcpyRev( far_data_p+14+((INT8U)(Far_Read_078001FF_Format->Data_Length)),receive_send_buffer+((INT8U)(Far_Read_078001FF_Format->Data_Length)), 4);
//	Co.c.len = ((INT8U)(Far_Read_078001FF_Format->Data_Length))+4;
	return OK;
}

/*"**************************************************************************"*/
/*" ��ѯ״̬"*/
/*" ֧��07810201 "*AppointTrasfPortBuff*/
/*" Data_Point:��:�� "*/
/*"            ��:���ݸ�ʽ���� FarPaidBuff,FarPrePayment.Far_SendLen"*/
/*"**************************************************************************"*/
struct Far_Read_07810201_Format
	{
	INT32U	Remain_Money;
	INT8U	Remain_Money_Mac[4];
	INT32U	Buy_Count;
	INT8U	Buy_Count_MAC[4];
	INT8U Client_ID[6];
	INT8U Password_Info[4];
	};
#define LENGTH_FAR_READ_07810201_FORMAT  sizeof( struct Far_Read_07810201_Format )
//-----------------------------------------------------------------------------
INT8U Far_Deal_07810201(INT8U *Data_Point )
{
	struct Far_Read_07810201_Format	 Far_Read_07810201_Format;
        //mem_cpy(&Far_Read_07810201_Format,Data_Point,sizeof(Far_Read_07810201_Format),&Far_Read_07810201_Format,sizeof(Far_Read_07810201_Format));
	//Esam_Remain_Money_Dec();
        //��װʣ�����ļ�
	if(Far_Read_Esam(0x04,Read_Record,1,0x0c,4,0)!=OK)
        {
          ASSERT_FAILED();
          return ERR;
        }
		
	My_memcpyRev((INT8U *)&(Far_Read_07810201_Format.Remain_Money), receive_send_buffer,4);
	My_memcpyRev((INT8U *)&(Far_Read_07810201_Format.Remain_Money_Mac[0]), receive_send_buffer+4,4);
	//��װ�������
	if(Far_Read_Esam(0x04,Read_Record,3,0x0c,4,0)!=OK)
		return ERR;
	My_memcpyRev((INT8U *)&(Far_Read_07810201_Format.Buy_Count), receive_send_buffer,4);
	My_memcpyRev((INT8U *)&(Far_Read_07810201_Format.Buy_Count_MAC[0]), receive_send_buffer+4,4);
        //My_Memcpy((INT8U *)&(Far_Read_07810201_Format.Buy_Count_MAC[0]), receive_send_buffer+4,4);
        //��װ�ͻ����
	if( Get_File_Data(ESAM,ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,6,(INT8U *)&(Far_Read_07810201_Format.Client_ID[0])) != OK )
		return ERR;

	Reverse_data((INT8U *)&(Far_Read_07810201_Format.Client_ID[0]),6);
	//��װԶ����Կ��Ϣ
	if( Get_File_Data(ESAM,ESAM_FAR_PASSWORD_INF_FILE,0,4,(INT8U *)&(Far_Read_07810201_Format.Password_Info[0])) != OK )
		return ERR;

	Reverse_data((INT8U *)&(Far_Read_07810201_Format.Password_Info[0]),4); 
        
        mem_cpy(FarPaidBuff,(INT8U *)&Far_Read_07810201_Format,sizeof(struct Far_Read_07810201_Format),FarPaidBuff,Length_FarPaidBuff);
	FarPrePayment.Far_SendLen= LENGTH_FAR_READ_07810201_FORMAT;
	
	return OK;
}
/*"**************************************************************************"*/
/*" ��ѯ״̬"*/
/*" ֧��078102FF "*/
/*" Data_Point:��:�� "*/
/*"            ��:���ݸ�ʽ���� "*/
/*"**************************************************************************"*/
INT8U Far_Deal_078102FF(INT8U * Data_Point )
	{
	return Far_Deal_07810201(Data_Point);
	}
/*"**************************************************************************"*/
/*" �����֤ʱЧ����"*/
/*" ֧��070001FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��:0�ֽ� "*/ 
struct Far_Deal_070001FF_format
	{
	INT16U Identity_Limit;
	INT8U Identity_Limit_Mac[4];
	};
#define LENGTH_FAR_DEAL_070001FF_FORMAT      sizeof(struct Far_Deal_070001FF_format)
//-----------------------------------------------------------------------------
INT8U Far_Deal_070001FF(INT8U * Data_Point ){
        INT16U ValidTimeTemp;
        INT8U Temp;
	struct Far_Deal_070001FF_format   Far_Deal_070001FF_format;
        //�ж��Ƿ��� ������Կ״̬
        Read_Storage_Data(_SDI_FAR_PASSWORD_STATE ,&Temp,&Temp, 1);
        if(Temp != 0)
        {
           return ERR;
        }
        
	mem_cpy(&Far_Deal_070001FF_format,Data_Point,sizeof(Far_Deal_070001FF_format),&Far_Deal_070001FF_format,sizeof(Far_Deal_070001FF_format));

	if( Far_Deal_070001FF_format.Identity_Limit == 0 )
        {
            return ERR;
        }
	//�� ����վ��������֤ʱЧֵ д��esam��ȥ
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_PARA_INF_FILE,IDENTITY_AUTH_TIME_ESAM,0x02,Data_Point,0)!=OK)
        {
                ASSERT_FAILED();
		return ERR;
	}//
        //��ȡesam�е���֤ʱЧֵ��
	if(Far_Read_Esam(04,Read_Binary,0x80+ESAM_PARA_INF_FILE,IDENTITY_AUTH_TIME_ESAM, 2, 0)!=OK)
        {
           ASSERT_FAILED();
           return ERR;
        }
        Reverse_data((INT8U *) &receive_send_buffer[0],2);	
        
        ValidTimeTemp=Bcd2Hex((INT8U *) &receive_send_buffer[0], 2);
        if(ValidTimeTemp EQ 0 )
        { 
            ValidTimeTemp=5;
        }
        //���� ��֤ʱЧ
        Reset_Pay_Timer(ValidTimeTemp*60);
	FarPrePayment.Far_SendLen  = 0;
	
	return OK;
}//
///////////////
/*"**************************************************************************"*/
/*" �����֤ʧЧ"*/
/*" ֧��07000201 "*/
/*" Data_Point:��:������"*/
/*"            ��:���ݸ�ʽ���� "FarPaidBuff,FarPrePayment.Far_SendLen*/
//-----------------------------------------------------------------------------
struct Far_Deal_07000201_format
	{
	INT8U Client_ID[6];
	INT32U	Remain_Money;
	INT32U	Buy_Count;
	INT8U Password_Info[4];
	};
#define LENGTH_FAR_DEAL_07000201_FORMAT      sizeof(struct Far_Deal_07000201_format)
INT8U Far_Deal_07000201(INT8U * Data_Point ){
	struct Far_Deal_07000201_format   Far_Deal_07000201_format;

	//mem_cpy(&Far_Deal_07000201_format,Data_Point,sizeof(Far_Deal_07000201_format),&Far_Deal_07000201_format,sizeof(Far_Deal_07000201_format));
	// ��esamȡ��ʣ��������
	if(Far_Read_Esam(0x04,Read_Record,1,0x0c,4,0)!=OK)
		return ERR;
	My_memcpyRev((INT8U *)&(Far_Deal_07000201_format.Remain_Money), receive_send_buffer,4);
	//��esam��ȡ�������������
	if(Far_Read_Esam(0x04,Read_Record,3,0x0c,4,0)!=OK)
		return ERR;
	My_memcpyRev((INT8U *)&(Far_Deal_07000201_format.Buy_Count), receive_send_buffer,4);
        //�õ��ͻ��������
	if( Get_File_Data(ESAM,ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,6,(INT8U *)&(Far_Deal_07000201_format.Client_ID[0])) != OK )
		return ERR;
 
	Reverse_data((INT8U *)&(Far_Deal_07000201_format.Client_ID[0]),6);
	//�õ���Կ��Ϣ
	if( Get_File_Data(ESAM,ESAM_FAR_PASSWORD_INF_FILE,0,4,(INT8U *)&(Far_Deal_07000201_format.Password_Info[0])) != OK )
		return ERR;

	Reverse_data((INT8U *)&(Far_Deal_07000201_format.Password_Info[0]),4);
        //�� �����֤ʱЧ��0 �� �����֤��־λ��0
	Far_Identity_Auth_Ok_Flag=0;
        Reset_Pay_Timer(0);
        mem_cpy(FarPaidBuff,&Far_Deal_07000201_format,sizeof(Far_Deal_07000201_format),FarPaidBuff,Length_FarPaidBuff);
        //esam�µ�
	Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,receive_send_buffer,receive_send_buffer,Length_receive_send_buffer );
//	cpucard_serial_release();
	FarPrePayment.Far_SendLen= sizeof(struct Far_Deal_07000201_format);
	//Co.c.len = LENGTH_FAR_DEAL_07000201_FORMAT;
	return OK;
}
/*"**************************************************************************"*/
/*" �����֤ʧЧ"*/
/*" ֧��07000201 "*/
/*" Data_Point:��:wu"*/
/*"            ��:���ݸ�ʽ���� "*/
//-----------------------------------------------------------------------------
INT8U Far_Deal_070002FF(INT8U * Data_Point )
	{
	return Far_Deal_07000201(Data_Point);
	}


/*"**************************************************************************"*/
/*" ����"*/
/*" ֧��070101FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��:������"FarPrePayment.Far_SendLen*/
//-----------------------------------------------------------------------------
struct Far_Deal_070101FF_format
	{
	INT32U	Remain_Money;//����˳��ģ��ж�ʱ��Ҫ��ת
	INT32U	Buy_Count;//����˳���
	INT8U BagMoney_Mac[4];//����˳���
	INT8U Client_ID[6];//  ��Ϊ���������Ƿ���˳���   ��һ  ֱ�����������˳��
	INT8U Client_ID_Mac[4];//
	};
#define LENGTH_FAR_DEAL_070101FF_FORMAT      sizeof(struct Far_Deal_070101FF_format)
INT8U Far_Deal_070101FF(INT8U * Data_Point )
{
	struct Far_Deal_070101FF_format  Far_Deal_070101FF_format;
	struct Moneybag_Data Moneybag_Data;

	mem_cpy(&Far_Deal_070101FF_format,Data_Point,sizeof(Far_Deal_070101FF_format),&Far_Deal_070101FF_format,sizeof(Far_Deal_070101FF_format));
	
        Read_Storage_Data( _SDI_PREPAID_RUN_STATUS, (INT8U *)&Pre_Payment_Para.Meter_Run_State ,  (INT8U *)&Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State)  );    
     	if( Pre_Payment_Para.Meter_Run_State!=MeterRunState_Test_0 )
		return ERR;
        //��Ǯ���ļ�������
	if( Read_Esam_Moneybag_File((INT8U *)&Moneybag_Data) != OK )
		return ERR;
        // �жϹ������
	if( Far_Deal_070101FF_format.Buy_Count != (Moneybag_Data.Buy_Count+1))
	{
		BUY_COUNT_ERR_DEFINE=1 ;
		return ERR;
	}
        //��� �������Զ���������Ȼ��д��esam���������ݱ����ᷴת
	CPU_ESAM_CARD_Control(ESAM);
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,0x06,(Far_Deal_070101FF_format.Client_ID),0)!=OK)
        {
           ASSERT_FAILED();
           return ERR;
        }
	//�жϱ��ι���Ķڻ����ޡ���//
	if( Check_Buy_Money_Exceed_Limit(Far_Deal_070101FF_format.Remain_Money) )
	{
                ASSERT_FAILED();
		BUY_MONEY_OVER_ERR_DEFINE=1;
		return ERR;
	}

	Reverse_data((INT8U *)&(Far_Deal_070101FF_format.Remain_Money),4);
	Reverse_data((INT8U *)&(Far_Deal_070101FF_format.Buy_Count),4);
	Reverse_data((INT8U *)&(Far_Deal_070101FF_format.BagMoney_Mac[0]),4);
	if( Write(0x84,Increase,0x01,0x0C,0x0C,((INT8U *)&Far_Deal_070101FF_format.Remain_Money))!=OK)
	{
            ASSERT_FAILED();  
	    return ERR;
	}
	Reverse_data((INT8U *)&(Far_Deal_070101FF_format.Remain_Money),4);
	Reverse_data((INT8U *)&(Far_Deal_070101FF_format.Buy_Count),4);
        //ʣ������뱣�� ���£� ����������ں���Ŀۿ��л��õ�
        //mem_cpy((INT8U*)&Moneybag_Data.Remain_Money,(INT8U *)&(Far_Deal_070101FF_format.Remain_Money),4,(INT8U)&Moneybag_Data.Remain_Money,4);
        //Meter_Money_And_Count_Updata(Far_Deal_070101FF_format.Remain_Money,Far_Deal_070101FF_format.Buy_Count );
	Prepaid_Buy_Money_Proc(Far_Deal_070101FF_format.Remain_Money);
        //���¿ͻ����
	My_Memcpy((INT8U *)Pre_Payment_Para.UserID,Far_Deal_070101FF_format.Client_ID,LENGTH_USER_ID);
	Write_Storage_Data(SDI_CUTOMER_ID , (INT8U *)Pre_Payment_Para.UserID , LENGTH_USER_ID);
	Pre_Payment_Para.Meter_Run_State=MeterRunState_Run_3;
	Write_Storage_Data(_SDI_PREPAID_RUN_STATUS  ,(INT8U *)&Pre_Payment_Para.Meter_Run_State , sizeof(Pre_Payment_Para.Meter_Run_State));
        //���߻ƹ����޸��� ����
        Card_Set_Para_Notice();
        FarPrePayment.Far_SendLen=0;            
	return OK;
}
///////////
/*"**************************************************************************"*/
/*" ��ֵ"*/
/*" ֧��070102FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��: 0 "FarPrePayment.Far_SendLen*/
//-----------------------------------------------------------------------------

struct Far_Deal_070102FF_format
	{
	INT32U	Remain_Money;//��������Ϊ����˳�� �Ƚ�ʵ����Ҫ����
	INT32U	Buy_Count;//��������Ϊ����˳�� �Ƚ�ʵ����Ҫ����
	INT8U BagMoney_Mac[4];//��������Ϊ����˳�� �Ƚ�ʵ����Ҫ����
	INT8U Client_ID[6];//��������Ϊ����˳�� �Ƚ�ʵ�� Ҫ���࣬��Ϊ�����б���ķ���, ���淴����
	INT8U Client_ID_Mac[4];//��������Ϊ����˳�� �Ƚ�ʵ�� Ҫ����
	};
#define LENGTH_FAR_DEAL_070102FF_FORMAT      sizeof(struct Far_Deal_070102FF_format)
INT8U Far_Deal_070102FF(INT8U * Data_Point )
{
	struct Far_Deal_070102FF_format    Far_Deal_070102FF_format;
	struct Moneybag_Data Moneybag_Data;
        
        Read_Storage_Data( _SDI_PREPAID_RUN_STATUS, (INT8U *)&Pre_Payment_Para.Meter_Run_State ,  (INT8U *)&Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State)  ); 
	if( Pre_Payment_Para.Meter_Run_State!=MeterRunState_Run_3 ) 	
        {
           ASSERT_FAILED();
           return ERR;
        }
		
        // ��ESAMǮ���ļ�ʣ���Ѻ͹������ ������
	if( Read_Esam_Moneybag_File((INT8U *)&Moneybag_Data) != OK )
        {
           ASSERT_FAILED();
           return ERR;
        }
	mem_cpy(&Far_Deal_070102FF_format,Data_Point,sizeof(Far_Deal_070102FF_format),&Far_Deal_070102FF_format,sizeof(Far_Deal_070102FF_format));
	
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Client_ID[0]),6);
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Client_ID_Mac[0]),4);
        // �ȽϿͻ���ţ� ��e���� 
        Read_Storage_Data( SDI_CUTOMER_ID, (INT8U *)Pre_Payment_Para.UserID,  (INT8U *)Pre_Payment_Para.UserID,LENGTH_USER_ID ); 
        Reverse_data((INT8U *)Pre_Payment_Para.UserID,LENGTH_USER_ID);
	if( My_Memcmp((INT8U *)Pre_Payment_Para.UserID,&Far_Deal_070102FF_format.Client_ID[0],LENGTH_USER_ID) != 0 )
        {
                ASSERT_FAILED();
		CLIENT_ID_ERR_DEFINE = 1;
		return ERR;
	}

	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Client_ID[0]),6);
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Client_ID_Mac[0]),4);
         
	CPU_ESAM_CARD_Control(ESAM);
        // ���� ���Ǹ���esam���������жϣ�O(��_��)O~
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,0x06,(Far_Deal_070102FF_format.Client_ID),0)!=OK)
        {
          ASSERT_FAILED();
          return ERR;
        }
		
 
	if( Far_Deal_070102FF_format.Buy_Count == Moneybag_Data.Buy_Count)
        {
                ASSERT_FAILED();
		REPEAT_INCREASE_ERR_DEFINE = 1;
		return ERR;
	}
	
	if( Far_Deal_070102FF_format.Buy_Count != (Moneybag_Data.Buy_Count+1))
        {
                ASSERT_FAILED();
		BUY_COUNT_ERR_DEFINE = 1;
		return ERR;
	}

	//�жϱ��ι���Ķڻ����� //
	if( Check_Buy_Money_Exceed_Limit(Far_Deal_070102FF_format.Remain_Money) )
        {
                ASSERT_FAILED();
		BUY_MONEY_OVER_ERR_DEFINE=1;
		return ERR;
	}

	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Remain_Money),4);
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Buy_Count),4);
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.BagMoney_Mac[0]),4);
        //�ж���ϣ���ʼ��ʽ��ֵ
	if( Write(0x84,Increase,0x01,0x0C,0x0C,((INT8U *)&Far_Deal_070102FF_format.Remain_Money))!=OK)
        {
                ASSERT_FAILED();
		return ERR;
	}
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Remain_Money),4);
	Reverse_data((INT8U *)&(Far_Deal_070102FF_format.Buy_Count),4);
	//Meter_Money_And_Count_Updata(Far_Deal_070102FF_format.Remain_Money,Far_Deal_070102FF_format.Buy_Count );
        Prepaid_Buy_Money_Proc(Far_Deal_070102FF_format.Remain_Money);
//	if( Far_Write_Esam(0x04,Update_Binary,0x82,0x05,0x06,(Far_Deal_070102FF_format->Client_ID))!=OK)
//		{
//		return ERR;
//		}
	FarPrePayment.Far_SendLen = 0;
	return OK;
}
///////////
/*"**************************************************************************"*/
/*" ��Կ����"*/
/*" ֧��070201FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��:�ޣ�  FarPrePayment.Far_SendLen=0"*/
//-----------------------------------------------------------------------------
struct Far_Deal_070201FF_format
	{
	INT8U PassWord_Inf[8];//4���ֽ���Կ��Ϣ�� 4���ֽ�mac
//	INT8U PassWord_Inf_Mac[4];
	INT8U PassWord[32];
	};
#define LENGTH_FAR_DEAL_070201FF_FORMAT      sizeof(struct Far_Deal_070201FF_format)
INT8U Far_PassWord_Updata(INT8U * Data_Point,INT8U PassWord_ID )
{       
        INT8U  Temp;
	struct Far_Deal_070201FF_format   Far_Deal_070201FF_format;
	INT8U PassWord_Inf[4];//���ص�esam��Զ����Կ��Ϣ�ļ�
        
	mem_cpy(&Far_Deal_070201FF_format,Data_Point,sizeof(Far_Deal_070201FF_format),&Far_Deal_070201FF_format,sizeof(Far_Deal_070201FF_format)); 
	if(OK != Get_File_Data(ESAM,ESAM_FAR_PASSWORD_INF_FILE,0,4,&PassWord_Inf[0]))
        {
            ASSERT_FAILED();
            return ERR;
        }
	Reverse_data(Far_Deal_070201FF_format.PassWord_Inf,8);
        //����Ҫ���µ���Կ��Ϊ ������Կ��  ��վ��������������Կ��Ϣǰ4���ֽڲ�Ϊ0 
	if( PassWord_ID!=2 ||  ( Far_Deal_070201FF_format.PassWord_Inf[0] !=0 || Far_Deal_070201FF_format.PassWord_Inf[1] !=0 ||
		Far_Deal_070201FF_format.PassWord_Inf[2] !=0 || Far_Deal_070201FF_format.PassWord_Inf[3] !=0 ) )
	{
                //��Կ��ʾҪ�ԣ� ��Կ���·�ʽҪΪԶ�̣� ��Կ�汾Ӧ�ñ�esam�еĴ�
		if( Far_Deal_070201FF_format.PassWord_Inf[2] !=PassWord_ID || 
			 Far_Deal_070201FF_format.PassWord_Inf[1] != 1 ||
			 Far_Deal_070201FF_format.PassWord_Inf[3] <= PassWord_Inf[3] )
                {
                  ASSERT_FAILED();
                  return ERR;
                }
	}
	Reverse_data(Far_Deal_070201FF_format.PassWord_Inf,8);
	
	CPU_ESAM_CARD_Control(ESAM);
	Reverse_data((INT8U *)&(Far_Deal_070201FF_format.PassWord[0]),32);
        //����Ǹ�����������Կ��
        if(PassWord_ID EQ 4)
        {
	  if( Write(0x84,Write_Key,0x01,0x00,0x20,(Far_Deal_070201FF_format.PassWord))!=OK)
	  {
                FarPrePayment.Far_Error_State.Password_Key_Updata_ERR=1;
                ASSERT_FAILED();  
		return ERR;
	  }           
        }
        else//����Ǹ���������Կ
        {
	  if( Write(0x84,Write_Key,0x01,0xFF,0x20,(Far_Deal_070201FF_format.PassWord))!=OK)
	  {
                FarPrePayment.Far_Error_State.Password_Key_Updata_ERR=1;
                ASSERT_FAILED();  
		return ERR;
	  }        
        }
        //д��Կ��Ϣ��
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_FAR_PASSWORD_INF_FILE,0x00,0x04,(Far_Deal_070201FF_format.PassWord_Inf),0xFF)!=OK)  
        {      
                FarPrePayment.Far_Error_State.Password_Key_Updata_ERR=1;
                ASSERT_FAILED();
		return ERR;
	}
        //
        Reverse_data(Far_Deal_070201FF_format.PassWord_Inf,8);
        Read_Storage_Data(_SDI_FAR_PASSWORD_STATE ,&Temp,&Temp, 1);
        if( Far_Deal_070201FF_format.PassWord_Inf[0] != Temp )
        {
            Write_Storage_Data(_SDI_FAR_PASSWORD_STATE ,&Far_Deal_070201FF_format.PassWord_Inf[0],1);
        }
	FarPrePayment.Far_SendLen=0;
	return OK;
}
/*"**************************************************************************"*/
/*" ����������Կ���� "*/
/*" ֧��070202FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��:���ݸ�ʽ���� "*/
//-----------------------------------------------------------------------------
INT8U Far_Deal_070201FF(INT8U * Data_Point )
	{
	return Far_PassWord_Updata(Data_Point,2);
	}
/*"**************************************************************************"*/
/*"������Կ����"*/
/*" ֧��070202FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��:���ݸ�ʽ���� "*/
//-----------------------------------------------------------------------------
INT8U Far_Deal_070202FF(INT8U * Data_Point )
	{
	return Far_PassWord_Updata(Data_Point,1);
	}
/*"**************************************************************************"*/
/*"Զ�������֤��Կ����"*/
/*" ֧��070203FF "*/
/*" Data_Point:��:���ݸ�ʽ���� "*/
/*"            ��:���ݸ�ʽ���� "*/
//-----------------------------------------------------------------------------
INT8U Far_Deal_070203FF(INT8U * Data_Point )
	{
	return Far_PassWord_Updata(Data_Point,3);
	}
/*
   Զ��������Կ���£�
   ֧��070204ff
   Data_Point���룺 mac +   4�ֽ���Կ  +32�ֽ�����
               ������
   Far_Deal_070204FF

*/
INT8U Far_Deal_070204FF(INT8U * Data_Point )
{
   return Far_PassWord_Updata(Data_Point,4);

}
//����������ܣ� 645֡��L�ֶ� �̶�����Ϊ 28 �� ���ܺ��ʵ�� ���ݳ���Ϊ8�� �ⲿ��ȫ���ɻƹ��ܣ���ֻ�ܽ���
INT8U Esam_Decrypt(INT8U *pSrc, INT16U SrcLen)
{
  //�鿴 �����֤��Чʱ����û�е�
  Far_Identity_Auth_Ok_Flag=!Chk_Pay_Time_Arrive();
  if(Far_Identity_Auth_Ok_Flag != 1)
  {
           Reset_Pay_Timer(0);
           ASSERT_FAILED();
           return 0;
  }  
  
  CPU_ESAM_CARD_Control(ESAM);
  if( Select_Directry(0,0x3F,0) != OK )
  {
      ASSERT_FAILED();
      Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
      return 0;
  }

  if(28 !=  (SrcLen) )
  {
     ASSERT_FAILED();
     return 0;
  }  
  Reverse_data( pSrc+8,20);       
  if( Write(0x04,0xD6,0x88,0x00,0x14,pSrc+8 )==OK){
           if( Read(0,Read_Binary,0x88,0,8) == OK ){
		My_Memcpy(pSrc + 8,receive_send_buffer, 8);
	   }else{
              FarPrePayment.Far_Error_State.CpuCardInternlAuthenticationErr=1; //����ĸ�ֵû���κ�����
              ReNew_Err_Code(DIS_CERTI_ERR);
              return 0;
           }
  }else
  {
        ASSERT_FAILED();
        FarPrePayment.Far_Error_State.CpuCardInternlAuthenticationErr=1;//���ݲ�©�ļ�������Ҫ�������֤���󣬵�������ĸ�ֵҲ��û���κ�����//d
        ReNew_Err_Code(DIS_CERTI_ERR);
	//ESAM_AUTH_ERR_DEFINE=1;
        OTHER_ERR_DEFINE=1;
        return 0;
  }
  return 1;
}
//
INT16U GetSecurity_Auth_Err_Info(void)
{
  
      INT16U Temp;
      if(( Far_Security_Auth_Err_Info.intd & 0xFFFE ) != 0 )
		Far_Security_Auth_Err_Info.intd &= 0xFFFE;
      else{
            OTHER_ERR_DEFINE =1;
      }
      Temp=Far_Security_Auth_Err_Info.intd;
      return Temp;
    
}
//�ж��Ƿ� Զ�������Ч�� �����˵�
//����1  ���ڣ�  0 ������
INT8U Check_Remote_Prog_Status()
{
  if(Chk_Pay_Time_Arrive())
  {
     return 0;
  }else{
     return 1;
  }

}
////////////////
 