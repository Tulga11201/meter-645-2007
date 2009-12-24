#define ALL_CARD_OPERATION_C_

#include "MyIncludesAll.h"

#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print
extern INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen);
//C_Pre_Payment_Para Pre_Payment_Para;
//ic�� ��ں���
//����1 ��ʾ�ɹ��� ����0 ��ʾʧ��
INT8U ICcardMain(void) {
       
       INT32U Temp;
       char ret;

       //Prepaid_Set_Buy_Money_Counts(0,0); 
        if( JUDGE_CPU_INSERT)//������
        {
          Debug_Print("-----------��⵽������--------- " );
        }else{//��������
           Debug_Print("-----------û��⵽������--------- " );
           return  0;
        }        
        WhenCardInsertedInitPrePayData();//�����ҹ����ȫ�ֱ���
	Card_Switch_On();//�ƹ��ĺ����������� �����忨ʱ�������բ��
	if(Check_CPU_Occur()){
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return 0;
	}

        Clr_Card_Op_Info(); //  ������� �ƹ����� ����ʲô���ܲ�֪��
        
        OS_Mutex_Pend(PUB_BUF_SEM_ID);//ʹ�û��壺Pub_Buf0
        OS_Mutex_Pend(PUB_BUF0_SEM_ID); //ʹ���ź������Ա�ʹ�û���	
	ret=ICcardProcess();//Card Operate
        OS_Mutex_Post(PUB_BUF0_SEM_ID);
        OS_Mutex_Post(PUB_BUF_SEM_ID);
        
        Prepaid_Card_Op_Aft_Proc(); //�������������������������̼�¼��
        Debug_Print("-------ret:%d---- ------ ",ret );
        //����Ż�״̬��
	if(ret!= OK){
		if(   Card_Error_State.CardErrorState.MeterIdErr EQ 1 //��Ų�ƥ�䣬����Ƿ���������� 
                   || Card_Error_State.CardErrorState.CardIdErr EQ 1 // �û���Ŵ��� ,�������˺����� ��δ�����������  
                   || Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr EQ 1 //�ⲿ��֤����
                   || Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr EQ 1// �ڲ���֤�� �������֤������Ƿ����������
                   || Card_Error_State.CardErrorState.CARD_STATE_ERR EQ 1//δ����״̬���빺�翨�Ͳ���/
                   || Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR EQ 1// ���翨�����ʹ� ������������������û�ҵ��Լ�������״̬ ���� ������
                   || Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR EQ 1//�����������  ����Ƿ����������
                   || Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err EQ 1 /// ��ɢ���Ӵ��ˣ� ����Ƿ����������
                  )
		{
                        //�Ƿ���������1��д��e����ȥ
                        Read_Storage_Data(_SDI_INVALID_CARD_COUNTS, &Temp, &Temp, 4  );//    
                        ++Temp;
                        Write_Storage_Data(_SDI_INVALID_CARD_COUNTS ,&Temp,4);
		}
                //_Debug_Print("Operate Type=%d,Card Time=%ld Ms",CardType,Get_Pay_Ms_Time());
                PrintErrState();
                Debug_Print("�� �������� �� ������0" );
                return 0;
	}else{
                   //_Debug_Print("Operate Type=%d,Card Time=%ld Ms",CardType,Get_Pay_Ms_Time());
                   PrintErrState();
                   Debug_Print("�� �������� ��������1 " );
                   return 1;
       }

}
//������
INT8U ICcardProcess(){
        INT8U length,ret=0;
        //ESAM
	if( OK  !=Esamcard_Atr() )
        {
           ASSERT_FAILED();
           return ERR;
        }
		
	if( OK != Select_File(0,0x3F,00) )
        {
           return ERR;
        }
        //CPU
	if(  OK != Cpucard_Atr() )
        {
           ASSERT_FAILED();
           return ERR;
        }
	if( OK  !=Select_File(0,0xDF,1) )
		return ERR;
        //��дcpu���������ļ�
	if(OK  != Read(0,Read_Binary,0x80+1,0,4) ){
            ASSERT_FAILED();
            return ERR;
        }
	if(0x68!=receive_send_buffer[0]){
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_DATA_HEAD_ERR=1;
		return ERR;
	}
        
	CardType=receive_send_buffer[1];
	if (CardType EQ 0x00){
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_DATA_CHECK_ERR=1;
		return ERR;
	}
        //�ļ��ܳ��� 
	length= receive_send_buffer[3];
	length+=6;
       
	if( Read(0,Read_Binary,0x80+1,0,length) != OK ){
		return ERR;
	}
        //�Զ�ȡ�Ķ������ļ����� ��飺  ͷβ�� Ч��� 
	if( Frame_Judge(&receive_send_buffer[0],length)!= OK ){
               return ERR;
        }
        //��ȡ��cpu��ָ����Ϣ�ļ������޴��� 
	My_Memcpy(Card_WR_Buff,receive_send_buffer,length);
       
	if( Cpucard_Esamcard_Internal_Auth() != OK ){
                Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr=1;
		return ERR;
	}
        //�ƹ������ݣ�����esam �ڲ�Ǯ���ļ�
        if( Esam_Remain_Money_Dec() != OK )
        {
		Card_Error_State.CardErrorState.EsamUpdataErr=1;
                ASSERT_FAILED();
		return ERR;
        }
        Debug_Print("-----------���ݿ������ͣ�������Ӧ�ĳ���-------------" );
        Debug_Print("-------------------������:%x------------------------ ",CardType );
	CPU_ESAM_CARD_Control(CPU);
	switch (CardType)
        {
		case GWFAR_USER_CARD:		//" �û��� "
			ret=Buy_Card();
			break;
		case GWFAR_MOD_PASSWORD_CARD:	//" �޸���Կ�� "
		case GWFAR_RES_PASSWORD_CARD: 	//" �ָ���Կ�� "
			ret=Password_Card();
			break;
		case GWFAR_PARA_SET_CARD:	//�ֳ��������ÿ�
			ret=Field_Para_Set_Card();
			break;
		case GWFAR_READ_ESAM_CARD:	//" ESAM���ݻس��� "
			ret=Check_Card();
			break;
		case GWFAR_INIT_CARD:		//" �������ÿ�  ����Ԥ�ÿ�
			ret=Set_In_Card();
			break;	
		case GWFAR_MOD_METERID_CARD:	//" ������ÿ� "
			ret=Modify_MeterID_Card();
			break;
		case GWFAR_ADDD_MONEY_CARD:	//" ���ӵ����� "
			ret = Add_Money_Card();
			break;
		case GWFAR_RELAY_TEST_CARD:	//" �̵������Կ� "
			ret = Relay_TEST_Card();
			break;
		default: 			//"�����ͻ�״̬����"
                        ASSERT_FAILED(); 
			Card_Error_State.CardErrorState.CardKindErr=1; ////"�����ͻ�״̬����",���翨������Ԥ�ÿ�
			ret=1;
			break;
       }
       if(Check_Meter_Prog_Status())
       {
            CardProgrammeEvent();//��̰�ť����ʱ ������  z��̼�¼
       }
       
       return ret;     
}
 


/*"IC���޸Ĳ�����̼�¼"*/ //�����ɢ���Ӻ�4λ���������±�־λ�� �����ͣ����翨���λ�Ԥ�ÿ�������Կ״̬����������ʽ��
// ��������û�ã� �����ж�
void CardProgrammeEvent(void)
{
         union Long_To_Char  progman,progdata;
	INT32U Temp;
	if( Para_Updata_Flag ==0 )
		return  ;
        
	My_memcpyRev(&progman.U_char[0], &cpucard_number[4], 4);
	progdata.U_char[0] = Para_Updata_Flag;
	progdata.U_char[1] = CardType;
	progdata.U_char[3]  = 0x99;
	if( Pre_Payment_Para.PassWord_Kind == GWFAR_MOD_PASSWORD_CARD )
		progdata.U_char[2]  = 0x98;
	else
		progdata.U_char[2]  = 0x99;
        
        mem_cpy((INT8U *)&Temp,(INT8U *)&progdata,sizeof(progdata),(INT8U *)&Temp, 4 );
        Prepaid_Prog_Record(Temp,(INT8U*)&progman);
	return  ;
}
////////////
unsigned int ProgrammeEvent(unsigned long progman,unsigned long progdata){
	
	 return 1;
}

//�ж��ļ����ݽṹ��֡ͷ֡β��Ч����Ƿ�Ϸ�
unsigned char Frame_Judge(unsigned char * Point,unsigned char length){
       unsigned char Cs;
	
	if(Point[0]!=0x68)
	{
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_DATA_HEAD_ERR=1;
		return ERR;
	}		
	if(Point[length-1]!=0x16)
	{
                 ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_DATA_END_ERR=1;
		return ERR;
	}
        
  	Cs=Cal_Add_CS(&Point[1],length-3);
	if( Cs!=Point[length-2] ) 
	{
                 ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_DATA_CHECK_ERR=1;
		return ERR;
	}
        
	return OK;
}
//�����ۼ�Ч���
unsigned char Cal_Add_CS(unsigned char * Point,unsigned char L){
        unsigned char Cs,i;

	Cs = 0;
	for(i=0;i<L;i++){
            Cs+=*Point++;
        }
		
	return Cs;
}

//esam���ݻس���
unsigned char Check_Card(void){
	
	/*" Ǯ���ļ� "*/
	if(Remain_Money_Moneybag_To_Cpu())
		return ERR;

	
         Debug_Print("  ������Ϣ�ļ�   "  );//3
	if( Cpu_File_Updata(ESAM_BACK_PARA_INF_FILE,//03
					     ESAM_PARA_INF_FILE,//02
					     0,
					     0,
					     LENGTH_ESAM_PARA_INF_FILE+6-1) != OK )
        {
           ASSERT_FAILED();
           return ERR;
        }
		 
        Debug_Print(" ��һ�׷��ʱ��ļ�   "  );
	// ��һ�׷��ʱ��ļ�//
     
	if( Cpu_File_Updata(ESAM_BACK_TRIFF_1_FILE,  //04
					     ESAM_TRIFF_1_FILE,//03
					     0,
					     0,
					     240)!= OK )
        {
           ASSERT_FAILED();
           return ERR;
        }
	Debug_Print("   Cpu_File_Updata(ESAM_BACK_TRIFF_1_FILE, "  );	
	if( Cpu_File_Updata(ESAM_BACK_TRIFF_1_FILE,
					     ESAM_TRIFF_1_FILE,
					     240,
					     240,
					     18)!= OK )
        {
           return ERR;
        }
        Debug_Print("   �ڶ��׷��ʱ��ļ�   "  );
	 
	if( Cpu_File_Updata(ESAM_BACK_TRIFF_2_FILE,//5
					     ESAM_TRIFF_2_FILE,//4
					     0,
					     0,
					     240)!= OK )
		return ERR;
        Debug_Print("ESAM_BACK_TRIFF_2_FILE,   "  );
	if( Cpu_File_Updata(ESAM_BACK_TRIFF_2_FILE,
					     ESAM_TRIFF_2_FILE,
					     240,
					     240,
					     18)!= OK )
		return ERR;
        Debug_Print("  ������Կ��Ϣ�ļ� "  ); 
	//������Կ��Ϣ�ļ�//
	if( Cpu_File_Updata(ESAM_BACK_PASSWORD_INF_FILE,//06
					     ESAM_PASSWORD_INF_FILE,//5
					     0,
					     0,
					     4) != OK )
		return ERR;
       Debug_Print("Զ����Կ��Ϣ�ļ�    "  );
	 /// Զ����Կ��Ϣ�ļ�//
	if( Cpu_File_Updata(ESAM_BACK_FAR_PASSWORD_INF_FILE,//07
					     ESAM_FAR_PASSWORD_INF_FILE,//06
					     0,
					     0,
					     4) != OK )
		return ERR; 
        Debug_Print( " //��ȡesam ������Ϣ�ļ�ǰ���ȸ���esam������Ϣ�ļ���������Դ�ڵ��ܱ�   "  );
	
	if( Updata_Esam_Return_File(0x15) != OK )
		return ERR;
       
        Debug_Print( "  // ��ȡesam������Ϣ�ļ��� ����esam���ݻس���   "  );
	if( Cpu_File_Updata(ESAM_BACK_RUN_INF_FILE,
					     ESAM_RUN_INF_FILE,
					     0,
					     0,
					     LENGTH_RUN_INF_DATA-1+6) != OK )
		return ERR;
 
	return OK;
}
unsigned char Field_Para_Set_Card(void){//�ֳ��������ÿ�
	unsigned long Version_Temp;
	unsigned long Count_Temp;
	if(!Check_Meter_Prog_Status())
		{
                  Debug_Print( "��̰�ťû������  "  );
		  Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		  return ERR;
		}
        Debug_Print( "  //��cpu���еõ� �汾�� "  );
        //��cpu���еõ� �汾��
	if( Get_File_Data(CPU,PARA_SET_CARD_PARA_INF_FILE,PARA_CARD_VERSION_SET_CARD,4,( unsigned char * )&Version_Temp) != OK )
		return ERR;
        Debug_Print( "//��cpu���еô� �������ļ�ֵ  "  );
        //��cpu���еô� �������ļ�ֵ
	CPU_ESAM_CARD_Control(CPU);
	if( Read(0,0xB2,1,0x24,4) != OK)
		return ERR;
	My_memcpyRev( ( unsigned char * )&Count_Temp,receive_send_buffer,4 );
         Debug_Print( "// �Ƚ�cpu���İ汾���Ƿ�����Լ�����İ汾�ţ� �������ļ���ֵ�Ƿ�Ϊ0  "  );
       // �Ƚ�cpu���İ汾���Ƿ�����Լ�����İ汾�ţ� �������ļ���ֵ�Ƿ�Ϊ0
	if( Version_Temp<=Pre_Payment_Para.Para_Card_Version || Count_Temp ==0 )
		{
		  Card_Error_State.CardErrorState.CPU_Para_Card_Version_Err=1;  
		  return ERR;
		}
	Para_Updata_Flag = Card_WR_Buff[5];
	Debug_Print( " ������Ϣ�ļ����� "  );
	/*" ������Ϣ�ļ����� "*/
	Meter_Ins_Flag = 0xFF;//ָ��仯
	if( Para_Updata_Flag & 0x80 )
		{
		if( Esam_File_Updata(PARA_SET_CARD_PARA_INF_FILE,
								ESAM_PARA_INF_FILE,
								USER_KIND_SET_CARD,
								USER_KIND_ESAM,
								2,
								Card_WR_Buff+USER_KIND_SET_CARD) != OK )
                                        {
                                                      ASSERT_FAILED();
                                                      return ERR;
                                         }
			
                
		}
	if( Para_Updata_Flag & 0x02 )
		{
		if( Esam_File_Updata(PARA_SET_CARD_PARA_INF_FILE,
								ESAM_PARA_INF_FILE,
								TRIFF_SWITCH_TIME_SET_CARD,
								TRIFF_SWITCH_TIME_ESAM,
								5,
								Card_WR_Buff+TRIFF_SWITCH_TIME_SET_CARD) != OK )
                            {
                                                          ASSERT_FAILED();
                                                          return ERR;
                            }
			
		}
        Debug_Print( " �Ѵ� cpu���õ� �� �û����ͣ������л�ʱ�䣬 ���浽���ܱ���ȥ "  );
        //�Ѵ� cpu���õ� �� �û����ͣ������л�ʱ�䣬 ���浽���ܱ���ȥ
	Deal_Set_Para_Inf_File(Card_WR_Buff+4,0x80);
	Debug_Print( "��һ�׷��ʱ��ļ�  "  );	
	// " ��һ�׷��ʱ��ļ� " /
	if( Para_Updata_Flag & 0x01 )
		{
		if( Esam_File_Updata(PARA_SET_CARD_TRIFF_1_FILE,
								ESAM_TRIFF_1_FILE,
								0,
								0,
								240,
								Card_WR_Buff) !=OK ){
                                                                Debug_Print( " Esam_File_Updata 11 "  );
                                                                return ERR;
                                                                }
			
		if( Esam_File_Updata(PARA_SET_CARD_TRIFF_1_FILE,
								ESAM_TRIFF_1_FILE,
								240,
								240,
								18,
								Card_WR_Buff+240) !=OK ){
                                                                Debug_Print( " Esam_File_Updata 22 "  );
                                                                return ERR;
                                                                }
			
		Deal_Triff_Data(Card_WR_Buff+4,258-4,1);
		}
	Debug_Print( "�ڶ��׷��ʱ��ļ�  "  );
	// �ڶ��׷��ʱ��ļ�  //
	if( Para_Updata_Flag & 0x02 )
		{
		if( Esam_File_Updata(PARA_SET_CARD_TRIFF_2_FILE,
								ESAM_TRIFF_2_FILE,
								0,
								0,
								240,
								Card_WR_Buff) !=OK ){
                                                                Debug_Print( "Esam_File_Updata 33 "  );
                                                                return ERR;
                                                                }
			
		if( Esam_File_Updata(PARA_SET_CARD_TRIFF_2_FILE,
								ESAM_TRIFF_2_FILE,
								240,
								240,
								18,
								Card_WR_Buff+240) !=OK ){
                                                                
                                                                 Debug_Print( " Esam_File_Updata  44 "  ); 
                                                                  return ERR;
                                                                }
			
		Deal_Triff_Data(Card_WR_Buff+4,258-4,2);
		}
         Debug_Print( "����cpu���������ļ�����  "  );
	 //����cpu���������ļ����� 
	if( CPU_Counter_Dec(0x24,4) != OK ){
          Debug_Print( " ����cpu���������ļ�����ʧ�� "  );
          return ERR;
        }
		
	
	if( Esam_File_Updata(PARA_SET_CARD_PARA_INF_FILE,
							ESAM_PARA_INF_FILE,
							PARA_CARD_VERSION_SET_CARD,
							PARA_CARD_VERSION_ESAM,
							4,
							0) != OK )
                  {
                                      Debug_Print( " Esam_File_Updata  55 "  );
                                      return ERR;
                  }
        Debug_Print( "   //�ҹ���� ESAM�汾�Ÿ��� "  );
		
        //�ҹ���� ESAM�汾�Ÿ���  
	Pre_Payment_Para.Para_Card_Version = Version_Temp;
        if( 0 EQ Write_Storage_Data(_SDI_PREPAID_PARA_CARD_VER ,&Pre_Payment_Para.Para_Card_Version,  4) ){
            //����дe��ʧ��
          Debug_Print( " //����дe��ʧ��  "  );
            Card_Error_State.CardErrorState.ReadWriteE2romErr=1;
        }
        
        Debug_Print( "����ִ�гɹ�  "  );  
	return OK;  
}
// //�Ѵ� cpu���õ� �� �û����ͣ������л�ʱ�䣬 ���浽���ܱ���ȥ
void Deal_Set_Para_Inf_File(unsigned char * Source_Point,unsigned char Mode )
{
	unsigned char i;
	struct Set_Para_Inf_File  Set_Para_Inf_File;
  
	//Set_Para_Inf_File = (struct Set_Para_Inf_File *)Source_Point;
        mem_cpy( &Set_Para_Inf_File,Source_Point,sizeof(Set_Para_Inf_File),&Set_Para_Inf_File,sizeof(Set_Para_Inf_File) );
	Deal_Para_Table2((unsigned char *)&(Set_Para_Inf_File.User_Kind)  );
        Deal_Para_Table4((unsigned char *)&(Set_Para_Inf_File.Triff_Switch_Time) );
        if(  (Para_Updata_Flag & 0x80 )||(Para_Updata_Flag & 0x02)  )
        {
          Card_Set_Para_Notice() ;
        }
        return ;
}
//����Ԥ�ÿ�
unsigned char Set_In_Card(void){///����Ԥ�ƿ�"
          INT8U Order_Head[11];
          INT32U Temp;

	struct Moneybag_Data Moneybag_Data;
	
	if(!Check_Meter_Prog_Status()){
                 //��̰�ťû������  "  );
		 Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		 return ERR;
	}
	Para_Updata_Flag = Card_WR_Buff[5];
       // �������±�־λΪ :%x ",Para_Updata_Flag  );
        // ������Ϣ�ļ�����  "  );
	// ������Ϣ�ļ�����//
	if( Para_Updata_Flag & 0x80 ){
                // " ----------- �������±�־λ��0x8Ϊ�棬��ʼ����1�û����ͣ��������±�־λ-----------  "  );
		if( Esam_File_Updata(INIT_CARD_PARA_INF_FILE,//1
								ESAM_PARA_INF_FILE,//2
								USER_KIND_INIT_CARD,
								USER_KIND_ESAM,
								6,
								Card_WR_Buff+USER_KIND_INIT_CARD) != OK )
                        {
                              ASSERT_FAILED();
                              return ERR;
                        }
		//"Esam_File_Updata  1   "  );
		if( Esam_File_Updata(INIT_CARD_PARA_INF_FILE,
								ESAM_PARA_INF_FILE,
								REMAIN_MONEY_ALARM1_LIMIT_INIT_CARD,
								REMAIN_MONEY_ALARM1_LIMIT_ESAM,
								14,
								Card_WR_Buff+REMAIN_MONEY_ALARM1_LIMIT_INIT_CARD) != OK )
                {
                    ASSERT_FAILED();
                    return ERR; 
                }
		// Esam_File_Updata 2  "  );

	}
	if( Para_Updata_Flag & 0x02 ){
               // ----------- �������±�־λ��0x2Ϊ�棬��ʼ����2------------  "  );
		if( Esam_File_Updata(INIT_CARD_PARA_INF_FILE,
								ESAM_PARA_INF_FILE,
								TRIFF_SWITCH_TIME_INIT_CARD,
								TRIFF_SWITCH_TIME_ESAM,
								5,
								Card_WR_Buff+TRIFF_SWITCH_TIME_INIT_CARD) != OK )
                {
                  ASSERT_FAILED();
                  return ERR;
                }
		// Esam_File_Updata 3  "  );	
	}
        //�������ݵ�esam�󣬸��µ��ܱ�������� "  );	
	Deal_Init_Para_Inf_File(Card_WR_Buff+4,0x80);
	// ��һ�׷��ʱ��ļ� "  );
	//  ��һ�׷��ʱ��ļ� //
	if( Para_Updata_Flag & 0x01 ){
		if( Esam_File_Updata(INIT_CARD_TRIFF_1_FILE,
								ESAM_TRIFF_1_FILE,
								0,
								0,
								240,
								Card_WR_Buff) !=OK )
                {
                  ASSERT_FAILED(); 
                  return ERR;
                }
		// Esam_File_Updata  4  "  );	
		if( Esam_File_Updata(INIT_CARD_TRIFF_1_FILE,
								ESAM_TRIFF_1_FILE,
								240,
								240,
								18,
								Card_WR_Buff+240) !=OK )
                {
                   ASSERT_FAILED();
                   return ERR;
                }
			
		Deal_Triff_Data(Card_WR_Buff+4,258-4,1);
	}
        //"�ڶ��׷��ʱ��ļ� "  );
	//  �ڶ��׷��ʱ��ļ�  //
	if( Para_Updata_Flag & 0x02 ){
		if( Esam_File_Updata(INIT_CARD_TRIFF_2_FILE,
								ESAM_TRIFF_2_FILE,
								0,
								0,
								240,
								Card_WR_Buff) !=OK )
                {
                 // "Esam_File_Updata 6   "  );
                   return ERR;
                }
			
		if( Esam_File_Updata(INIT_CARD_TRIFF_2_FILE,
								ESAM_TRIFF_2_FILE,
								240,
								240,
								18,
								Card_WR_Buff+240) !=OK )
                {
                   return ERR;
                }
			
		Deal_Triff_Data(Card_WR_Buff+4,258-4,2);
	}
        // // Ǯ���ļ���ʼ�� //��ȡcpu����Ǯ���ļ�ֵ����esam�е�Ǯ���ļ� "  );
	// Ǯ���ļ���ʼ�� //��ȡcpu����Ǯ���ļ�ֵ����esam�е�Ǯ���ļ�
	if( Remain_Money_Moneybag_Init() != OK  ) {
            return ERR;
        }
        // ��esam �ж�ȡ�����º��Ǯ���ļ������������µ������ ��������ᷴ��
	Read_Esam_Moneybag_File( (INT8U * )&Moneybag_Data);

        // " ��ʼ���µ���е�����"  );
        //���¹������,����ʣ����
        Prepaid_Set_Buy_Money_Counts(Moneybag_Data.Remain_Money, Moneybag_Data.Buy_Count);
        //�������״̬
	Pre_Payment_Para.Meter_Run_State=0;
        Write_Storage_Data(_SDI_PREPAID_RUN_STATUS ,&Pre_Payment_Para.Meter_Run_State  , 1 );
        //���Զ�̷Ƿ���������
        FarPrePayment.ID_Ins_Counter  =0;
	Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, &FarPrePayment.ID_Ins_Counter, 1);
        //���طǷ������������0
        Temp=0;
        Write_Storage_Data(_SDI_INVALID_CARD_COUNTS ,&Temp,4);
        //�¼���¼��0�� ֻ�Ǹ�ȫ�ֱ����� ��������0 ���ں���������н���
        Card_Clr_All_Data(); 
               
	return OK;
}
///����Ԥ�ÿ��� ������esam�еĲ����󣬸ı��е�
void Deal_Init_Para_Inf_File(unsigned char * Source_Point,unsigned char Mode)
{
    struct Init_Para_Inf_File   Init_Para_Inf_File;
    mem_cpy(&Init_Para_Inf_File,Source_Point,sizeof(struct Init_Para_Inf_File),&Init_Para_Inf_File,sizeof(struct Init_Para_Inf_File));
    //���µ��ĵ¹������ͣ� �ǵ����ʻ��Ǹ�����
    Debug_Print("���µ��ĵ¹�������:%d",(Init_Para_Inf_File.User_Kind) ); 
    Deal_Para_Table2( (unsigned char *)&(Init_Para_Inf_File.User_Kind) );
    
    //�ֳ��������ÿ��汾��
    if( Para_Updata_Flag&0x80 ){
       My_memcpyRev((INT8U *)&Pre_Payment_Para.Para_Card_Version,(INT8U *)&Init_Para_Inf_File.Para_Card_Version,4  );
       Write_Storage_Data( _SDI_PREPAID_PARA_CARD_VER,&Pre_Payment_Para.Para_Card_Version  , 4 );
    }
    Debug_Print("// ���µ��ķ����л�ʱ��: ");  
    // ���µ��ķ����л�ʱ��
    Deal_Para_Table4((unsigned char *)&(Init_Para_Inf_File.Triff_Switch_Time));
     Debug_Print("//���±������1��2�� �Լ���ѹ���������б仯 ");  
    //���±������1��2�� �Լ���ѹ���������б仯
    Deal_Para_Table3((unsigned char *)&(Init_Para_Inf_File.Remain_Money_Alarm1_Limit));
    if(  (Para_Updata_Flag & 0x80 )||(Para_Updata_Flag & 0x02)  )
    {
          Card_Set_Para_Notice() ;
    }
    return ;    
}
///	 �û����� : �����ʣ����Ǹ�����
void Deal_Para_Table2(unsigned char * Source_Point ){
         
        INT8U SingleKing_OrComplexKing;//������ݱ�ʾĿǰû�õ�����չ��
        SingleKing_OrComplexKing=*Source_Point;
	if( Para_Updata_Flag&0x80 ){
          Write_Storage_Data(_SDI_SINGLE_OR_COMPLEX_USER_KIND, &SingleKing_OrComplexKing,1);
	}
}
//" ���׷�ʱ�����л�ʱ��  
void Deal_Para_Table4(unsigned char * Source_Point ){
        INT8U Temp[5];
        mem_cpy(Temp,Source_Point,5,Temp,5);
        //��cpu���ж����������ݣ���һ���ֽ�Ϊ�꣬�ڶ����£� �Դ�����,���Ƕ����ʱ��ṹ�壬��һ��Ϊ�֣�����ʤ�ĵ�һ��λ�꣬��
        //�����ǵ�Ҫ���� ���ǵĲ�Ҫ
        Debug_Print( "��cpu����������ʱ��bcd��Ϊ�� Temp[4]:%x Temp[3]:%x Temp[2]:%x Temp[1]:%x Temp[0]:%x  ",Temp[4],Temp[3],Temp[2],Temp[1],Temp[0]);
	if( Para_Updata_Flag&0x02 ){ 
          Reverse_data(Temp,5);//����45Э�飬pDst��0��Ӧ��������� ���λ
          Write_Storage_Data(SDI_RATE_SCHE_CHG_TIME, Temp, 5 );
	} 
}
//	unsigned long Remain_Money_Alarm1_Limit;  �������1 "
//	unsigned long Remain_Money_Alarm2_Limit; �������2 "
//	unsigned char Current_CT[3];             ������������� "
//	unsigned char Voltage_PT[3];             ��ѹ��������� 
void Deal_Para_Table3(unsigned char * Source_Point )
{
	struct Para_Table3 ParaTable3;
	mem_cpy(&ParaTable3,Source_Point,sizeof(struct Para_Table3),&ParaTable3,sizeof(struct Para_Table3) );
	if( Para_Updata_Flag&0x80 )
  {
		Reverse_data((unsigned char *)&(ParaTable3.Remain_Money_Alarm1_Limit),4);
                //��cpu���������ı������1�����Ϊ��Temp[3]:%x Temp[2]:%x Temp[1]:%x Temp[0]:%x  ",Temp[3],Temp[2],Temp[1],Temp[0]);
                Write_Storage_Data(SDI_PREPAID_WARN_MONEY1 , (unsigned char *)&(ParaTable3.Remain_Money_Alarm1_Limit) , 4)   ;
		
                Reverse_data((unsigned char *)&(ParaTable3.Remain_Money_Alarm2_Limit),4);
                //��cpu���������ı������2�����Ϊ:Temp[3]:%x Temp[2]:%x Temp[1]:%x Temp[0]:%x ",Temp[3],Temp[2],Temp[1],Temp[0]);
                Write_Storage_Data(SDI_PREPAID_WARN_MONEY2 ,(unsigned char *)&(ParaTable3.Remain_Money_Alarm2_Limit)  , 4)  ; 
		
                Reverse_data((unsigned char *)&(ParaTable3.Current_CT[0]),3);
                Write_Storage_Data(SDI_CURR_TRANS_RATIO , (unsigned char *)&(ParaTable3.Current_CT[0]) , 3) ;  

                Reverse_data((unsigned char *)&(ParaTable3.Voltage_PT[0]),3);
                //��cpu���������ı������1�����Ϊ:Temp[2]:%x Temp[1]:%x Temp[0]:%x ",Temp[2],Temp[1],Temp[0]);
                Write_Storage_Data(SDI_VOLT_TRANS_RATIO , (unsigned char *)&(ParaTable3.Voltage_PT[0]) , 3);  
	}
}
////
unsigned char Password_Card(void)//��Կ��װ��/�ָ���
{
	struct Password_Inf_File  File_Point;//ָ����Ϣ�ļ���û��ȥ��ͷβ
	
	unsigned char Esam_Password_Info[4];
	unsigned char Cpu_Password_Info[4];
	unsigned long Temp;
	unsigned char PassWord_Kind;

	if( !Check_Meter_Prog_Status() ){
		Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		return ERR;
	}
        //���������ļ� �����ж��Ƿ�������ļ���ֵΪ0
	if( Read(0,0xB2,1,0x14,4) != OK)
		return ERR;
	Temp = 0;
	if( My_Memcmp( (INT8U *) &Temp, receive_send_buffer, 4)==0 ){
                 ASSERT_FAILED();
		 Card_Error_State.CardErrorState.Password_Count_Number_Is_Zero_Err=1;
		 return ERR;
	}
	My_memcpyRev((INT8U *)&Temp, receive_send_buffer, 4);
        //�õ�esam��Կ��Ϣ�ļ� 4���ֽڣ� �ŵ��ֲ�������Esam_Password_Info��
	Get_File_Data(ESAM,ESAM_PASSWORD_INF_FILE,0,4,Esam_Password_Info); 
        //�õ�cpu����ָ����Ϣ�ļ�����Կ��Ϣ��Card_WR_Buff������ĺ����У��ļ����ݱ��ŵ�������壬�ļ��ṹ�Ѿ�Ϊ�����˿�ͷ�ͽ�β��ʾ
        mem_cpy( &File_Point,Card_WR_Buff,sizeof(struct Password_Inf_File),&File_Point,sizeof(struct Password_Inf_File) );
        mem_cpy(Cpu_Password_Info,File_Point.Password_Info,4, Cpu_Password_Info,4);
          
	PassWord_Kind = File_Point.Order_Byte; //��Կ����,��Կ��װ���� ������Կ�ָ���
       //�ж�cpu����ֵ�Ƿ���ȷ
	if( PassWord_Kind == GWFAR_MOD_PASSWORD_CARD )//���Ϊ��Կ��װ��
	{       //����дûʲô���壬��Ϊ��װ������װʱ�������֤ͨ����
		if( File_Point.Password_Info[3] <= Esam_Password_Info[3] )//��Կ��װ����  ��Կ�汾 
		{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Password_State_Err=1;
			  return ERR;
		}
	}
	else if(  PassWord_Kind== GWFAR_RES_PASSWORD_CARD )
        {
		if(  File_Point.Password_Info[3] != 0 )/// ��� ��Կ�޸����� ��Կ�汾 ��Ϊ0
		{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Password_State_Err=1;
			  return ERR;
		}
        }
        
        // // ��Կ����//// ");
       // ��Կ����////
	if( PassWord_Updata( File_Point.Order_Byte ) != OK )
		return ERR;
          //"//esam��Կ״̬����// " );
         //esam��Կ״̬����//
	if(Write(0,Update_Binary,0x80+ESAM_PASSWORD_INF_FILE,0,4,(unsigned char *) &Cpu_Password_Info[0])!=OK)
	{
		return ERR;
	}
         // " ��������1//");
        //"��������1//
	Temp--;
	My_memcpyRev(Card_WR_Buff,(unsigned char *)&Temp,  4);
	CPU_ESAM_CARD_Control(CPU);
	if(Write(0,Update_Record,0x01,0x14,0x04,Card_WR_Buff)!=OK)
	{
		return ERR;
	}
        //// �����õ��� ��Կ�ָ�����������Կ��װ�� ");
        // �����õ��� ��Կ�ָ�����������Կ��װ��//�ñ���ֻ���������޸ģ�����������̼�¼��
	Pre_Payment_Para.PassWord_Kind=PassWord_Kind;////��Կ����,��Կ��װ���� ������Կ�ָ���
         if(Write_Storage_Data(_SDI_PREPAID_PSW_KIND , &Pre_Payment_Para.PassWord_Kind ,1) );
	return OK;
}
       
unsigned char Add_Money_Card(void){//���ӵ�ѿ�
  
	struct Moneybag_Data Moneybag_Data;
	struct Add_Money_Para_Inf_File  File; //cpu�� ָ����Ϣ�ļ�
        //��ȡesamǮ���ļ�,�����࣬
	Read_Esam_Moneybag_File( ( unsigned char * )&Moneybag_Data );
	Moneybag_Data.Buy_Count++;//ʹ�������+1
        //����cpu����������Ϣ�ļ�
        mem_cpy(&File,Card_WR_Buff,sizeof( struct Add_Money_Para_Inf_File ) ,&File , sizeof( struct Add_Money_Para_Inf_File ));
	//����cpu���Ĺ������
	My_memcpyRev((unsigned char *)&(File.Buy_Money_Count), (unsigned char *)&(Moneybag_Data.Buy_Count), 4);
	File.Add_CS=Cal_Add_CS(&File.Order_Byte,LENGTH_ADD_MONEY_PARA_INF_FILE-3);//�޸�Ч���
	CPU_ESAM_CARD_Control(CPU);
	if(Write(0,Update_Binary,0x81,0,LENGTH_ADD_MONEY_PARA_INF_FILE,&File.Start_Byte)!=OK){//ĩβ��־ ����
		return ERR;
	}
        
	Reverse_data( (unsigned char *)&(File.Buy_Money),4 ); 
	Reverse_data( (unsigned char *)&(File.Buy_Money_Count),4 );//ǰ���Ѿ�����������ΪʲôҪ���࣬ ������� ������
        // �жϱ��ι���Ķڻ�����  //
	if( Check_Buy_Money_Exceed_Limit( File.Buy_Money) ){//Moneybag_Data.Remain_Money����cpu��
                           ASSERT_FAILED();
			   Card_Error_State.CardErrorState.MoneyLimitErr=1;
			   return ERR;
	}
        // 1 , 4,0   ��cpu����ָ����Ϣ�ļ��У�Ҫ��ֵ��Ǯ �ӵ�esam��ȥ
	if( Remain_Money_Moneybag_Add(ADD_MONEY_CARD_ORDER_INF_FILE,BUY_MONEY_CARD,0) != OK )
	{
		   Card_Error_State.CardErrorState.ESAM_DO_ERR=1;
		   return ERR;
	}
//���߻ƹ��� ��ֵ�ˣ� ���˶���Ǯ
	Meter_Money_And_Count_Updata(File.Buy_Money,File.Buy_Money_Count );
	return OK;
}
//���� �ͻƹ���Լ���������e���б��pDst[0]Ӧ��Ϊ �����׼�����Ͽ����ñ��ַ���ұߵ�һ���ֽ�
unsigned char Modify_MeterID_Card(void){// ������ÿ�
  	unsigned char i,Msb,Ctrl;
	struct MeterID_Return_Inf_File MeterID_Return_Inf_File;//������ÿ��ķ�д��Ϣ�ļ�,��¼�˵�ǰҪ���õı��
	struct MeterID_Para_Inf_File   File;//������ÿ���ָ����Ϣ�ļ�����¼�˱�����õķ�Χ
	
	if( !Check_Meter_Prog_Status() ){ 
		Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		return ERR;
	}
        mem_cpy(&File,Card_WR_Buff,sizeof(struct MeterID_Para_Inf_File),&File,sizeof(struct MeterID_Para_Inf_File) );
        
        /*" �жϱ���Ƿ��ں���Χ�� "*/
        
	if( Read(0,Read_Binary,0x80+METERID_CARD_RETURN_FILE,0,LENGTH_METERID_RETURN_INF_FILE) != OK )
		return ERR;
	My_Memcpy((unsigned char *) &MeterID_Return_Inf_File, receive_send_buffer, LENGTH_METERID_RETURN_INF_FILE);
        //���Ҫ���õ� ��ţ������һ����Ŵ� ��ô���󣬺������� ,ע��:BcdMeterID��0��Ϊ��λ��BcdMeterID��5��Ϊ��λ
	if( My_Memcmp(&(MeterID_Return_Inf_File.Next_Meter_ID[0]),&(File.End_Meter_ID[0]) ,6)  == 1 )
	{
                  ASSERT_FAILED();
		  Card_Error_State.CardErrorState.Meter_Id_Set_Card_Id_Is_FULL_Err=1;
		  return ERR;
	}  
        // ����ESAM��� //
	if( Esam_File_Updata(METERID_CARD_RETURN_FILE,
							ESAM_PARA_INF_FILE,
							NEXT_METER_ID_METERID,
							METER_ID_ESAM,
							6,
							0) != OK )
		return ERR;
        //  ���±�Ʊ��  //������������д����010203040506����ô����Pre_Payment_Para.BcdMeterID��0����Ϊ01
         My_memcpyRev( Pre_Payment_Para.BcdMeterID,&(MeterID_Return_Inf_File.Next_Meter_ID[0]),6);
         Write_Storage_Data( SDI_METER_ID, Pre_Payment_Para.BcdMeterID , 6);
         Card_Set_Para_Notice() ;
/*" ���¿���д�ļ� "*/
	Msb = 0;
        //���+1
	for( i=0;i<6;i++ )
	{
		Ctrl = MeterID_Return_Inf_File.Next_Meter_ID[5-i];
		if( i==0 )
			Ctrl++;
		Ctrl+=Msb;
		if( (Ctrl&0x0F)>0x09 )
			{
			Ctrl += 0x10;
			Ctrl &=0xF0;
			} 
		if( (Ctrl&0xF0)>0x90 )
			{
			Ctrl &=0x0F;
			Msb = 1;
			}
		else
			Msb = 0;
		 MeterID_Return_Inf_File.Next_Meter_ID[5-i] = Ctrl;
	}
	MeterID_Return_Inf_File.Add_CS++;//Ч���+1
	CPU_ESAM_CARD_Control(CPU);
        //����cpu����д��Ϣ�ļ��� �������õı�ű��� �����ڸ��ļ��У��ñ����ѱ���1 
	if(Write(0,Update_Binary,0x80+METERID_CARD_RETURN_FILE,0,LENGTH_METERID_RETURN_INF_FILE,(unsigned char *) &MeterID_Return_Inf_File)!=OK)
		{
		return ERR;
		}
        
	return OK;
}
unsigned char Relay_TEST_Card()
{
  	Card_Test_Relay();  
	return OK;
}

 void Relay_Deal(unsigned char Flag)
 {
 
}       
    
//Զ�� �� ����  ÿ��60���Ӷ� esam �ۿ� 
void UpdataEsamMoneyBag(void)
{
  static S_Int8U Mins = {CHK_BYTE, 0xF0, CHK_BYTE};// ��̬�ֲ�����������д���������Ǳ���ֵ
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U Re;
  //ASSERT_FAILED();
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Mins);
  Re &= CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(Re EQ 1);
  //���� ����һ����   ����
  if(Min_Bak.Var EQ Cur_Time1.Min)
    return;
  
  Min_Bak.Var = Cur_Time1.Min;
  ++Mins.Var;
  //ÿ60����ˢ��һ��Esam
  if(Mins.Var >= 60) 
  {
      Mins.Var = 0;
      
  }else{
    return ;
  }  
  

  //��ʼ����esam
  if(Chk_Pay_Time_Arrive())//����Զ�������֤ʱ�� ���� �� Ҳ���ǣ�û��Զ�̲���ʱ 
  {   
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
    {
     if(Esamcard_Atr() != OK)
      {
       return ;
      }
     if( OK != Select_File(0,0x3F,00) )
      {
         return  ; 
      }
       //Ԥ���ѹ��ܴ����Ǳ���Ԥ���ѱ�  Ԥ���ѹ��ܴ����Ǳ���Ԥ���ѱ� 

       Esam_Remain_Money_Dec();
       Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,receive_send_buffer,receive_send_buffer,Length_receive_send_buffer );
     }
  }else 
  {//�������� Զ�̿��Ƶ�ʱ�� Ԥ���ѹ��ܴ����Ǳ���Ԥ���ѱ� 
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)//
    {
       Esam_Remain_Money_Dec();
    }  
  }
  return ;
}