#include "MyIncludesAll.h"
#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//"�����Ƿ���±�־//
//"λ	  //
//"Bit0	���ʱ��һ�� //
//"Bit1	���ʱ�ڶ��� //
//"Bit2	���� //
//"Bit3	���� //
//"Bit4	���� //
//"Bit5	���� //
//"Bit6	���� //
//"Bit7	�������� //
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//" ������,���翨���ȽϺϷ���//  Buy_Count Ϊcpu���Ĺ������
unsigned char Judge_User_Card_OK(unsigned char BuyCard_Kind,unsigned long Buy_Count){
	unsigned long Money_Count_T;// �����Ƚ� 
        INT8U MeterIDTemp[6];
	struct Buy_Para_Inf_File file;// ������Ϣ�ļ��ṹ��
	//struct Moneybag_Data Moneybag_Data;//Ǯ���ļ��ṹ��  4+4���ֽ�
	//��esam ��ȡ Ǯ���ļ�,����������
	//Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data);
	//Pre_Payment_Para.Buy_CountΪ�ƹ�����ĵ�ǰ��������
        
	Money_Count_T = Pre_Payment_Para.Buy_Count+1;//�����Ƚϴ����Ƿ��1
         Debug_Print(" ��ʼִ�к�����Judge_User_Card_OK(unsigned char BuyCard_Kind,unsigned long Buy_Count) " );
        String2ParaFile(  &file,&Card_WR_Buff[4], sizeof(struct Buy_Para_Inf_File) );
         Debug_Print("//�ж��Ƿ񹺵翨���ʹ�// " );
	if( BuyCard_Kind !=GWFAR_USER_CARD_NEW && BuyCard_Kind !=GWFAR_USER_CARD_BUY && BuyCard_Kind !=GWFAR_USER_CARD_BACK)
		{
		Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR=1;
	 	return ERR;
		}
	 Debug_Print("//�жϱ�� // " );
        My_memcpyRev(MeterIDTemp,(unsigned char *)&Pre_Payment_Para.BcdMeterID[0],6);
	if( My_Memcmp(&(file.Meter_ID[0]),MeterIDTemp,6) ){
		Card_Error_State.CardErrorState.MeterIdErr=1;
		return ERR;
	}
         Debug_Print(" //ֻҪ���״̬Ϊ����״̬�������Ƚ��û���// " );
	if(  Pre_Payment_Para.Meter_Run_State  EQ MeterRunState_Run_3 ){
                Debug_Print(" // �ж��Ƿ��û���Ų���// " );
		if( My_Memcmp(Pre_Payment_Para.UserID,file.Client_ID,6) )
			{
			  Card_Error_State.CardErrorState.CardIdErr=1;
			  return ERR;
			}
                 Debug_Print( "//���������������ֱ�ӻ�д// " );
  
		if( My_Memcmp((unsigned char *)&Buy_Count, (unsigned char *)&Pre_Payment_Para.Buy_Count,4) ==0 ) {
			Dir_Return_Flag = 0xFF; Debug_Print("//��ʾ����������ʱֱ�� ��дcpu��   " );
			return OK;
		 }
                 Debug_Print("//���������״̬���� �������� ����Ƿ���������� " );
		if( BuyCard_Kind ==GWFAR_USER_CARD_NEW ){
			Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR=1;
			return ERR;
		 }
	} //����״̬�жϽ���
	else{
                Debug_Print("// �ж��Ƿ�δ����״̬���빺�翨������  " );
		if( BuyCard_Kind !=GWFAR_USER_CARD_NEW )
			{
			 Card_Error_State.CardErrorState.CARD_STATE_ERR=1;
			 return ERR;
			}
		else
			{
                         Debug_Print("�ж��Ƿ��Ѿ���д�����¿�����ô�����ظ�����// " );
                        //"�Ѿ���д�����¿������ظ�����//
			CPU_ESAM_CARD_Control(CPU);
			Read(0,Read_Binary,0x80+5,0,1);
			CPU_ESAM_CARD_Control(ESAM);
			if( receive_send_buffer[0] == 0x68 )
				{
				  Card_Error_State.CardErrorState.CPU_NEW_CARD_INI_ERR=1;
				  return ERR;
				}
			}
	}//��ʽ���кͷ���ʽ����״̬���жϽ���
         Debug_Print("// �ж��Ƿ񹺵������//   �������������ϣ�cpu���Ĺ������ �� esam �� +1�󹺵���� ��� " );
        
	if( My_Memcmp((unsigned char *)&Buy_Count,(unsigned char *)&Money_Count_T,4) !=0){
		Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR=1;
	 	return ERR;
	}
         Debug_Print(" //�ж��Ƿ���ɢ���Ӵ��� " );
	if( BuyCard_Kind == GWFAR_USER_CARD_BUY )
		{
		 if( My_Memcmp(Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom, cpucard_number, 8) ){
			   Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err=1 ;//��������ɢ���Ӵ���,�в�����������ɢ����
		 	   return ERR;
		}
	}
         Debug_Print(" ����ִ�к�����Judge_User_Card_OK(unsigned char BuyCard_Kind,unsigned long Buy_Count) " );
	return OK;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//"�жϱ��ι���Ķڻ�����//

unsigned char Judge_Remain_Money_Over(INT32U Curr_Buy_Money) {
	INT32U  Money_Count_T,Money_Count_T1;
        
        //�ж��Ƿ񹺵���ó���
	Money_Count_T = Pre_Payment_Para.Remain_Money;
	Money_Count_T+=Curr_Buy_Money;
        //
	Money_Count_T1 = Pre_Payment_Para.Remain_Money_Hoard_Limit;
        //Money_Count_T1 = (signed long)DataTemp;
	if( Money_Count_T1 != 0 ){
		if( Money_Count_T > Money_Count_T1 )
                {
                  return ERR;
                }	
	}
	//" ʣ���Ѵ���2ǧ��Ҳ��������� //
	if( Money_Count_T > 0x77359400 )  //��֪��Ҫ��Ҫ
        {
           return ERR;
        }
	return OK;
	}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//"������,���翨//
unsigned char Buy_Card(void){
	unsigned char Buy_Card_Kind;//�û������ͣ����翨�� �������� ����
        INT8U UserID[6];//�ͻ����
	struct Moneybag_Data Moneybag_Data;
	struct Buy_Para_Inf_File  file;
        
        String2ParaFile(&file,(&Card_WR_Buff[4]), sizeof(struct Buy_Para_Inf_File) )  ;//��ʼ��file����
        Debug_Print("//  ��CPU���е�ʣ���Ѻ͹������ //02  0 �����������ǻ�� cpu���е����ݷ�ת������λ�ڵ�λ��cpu��������ʱ����1 " );
	if( Remain_Money_Moneybag_Add(USER_CARD_MONEYBAG_FILE,REMAIN_MONEY_CPU_ESAM,(unsigned char *)&Moneybag_Data) != OK )
		return ERR;
         
	//file=(struct Buy_Para_Inf_File *)(&Card_WR_Buff[4]);
	
	if( Cpucard_External_Auth() != OK )
		return ERR;
        Debug_Print("//  ��ȷ  // " );
	Buy_Card_Kind = file.Card_Kind;//
	
	
	if( Judge_User_Card_OK( Buy_Card_Kind ,Moneybag_Data.Buy_Count) != OK )
		return ERR;
        Debug_Print("//   ���ĺϷ���������  // " );
       My_Memcpy(UserID,file.Client_ID,6);
       //���Ϊ�����������߱�̰�ť������ 
       //Meter_Ins_Flag = 0xFF;
       if( (Buy_Card_Kind == GWFAR_USER_CARD_NEW) || Check_Meter_Prog_Status() ){  
                        Debug_Print("  //���Ϊ���� f1�������߱�̰�ť������ ��ʼ������Ӧ���� " );
			Para_Updata_Flag = file.Para_UpData_Flag;
                        Debug_Print("//  ������Ϣ�ļ����� // " );
			if( Para_Updata_Flag & 0x80 ){
                                //��ȡcpu��������Ϣ�ļ�ǰ�������ֽ�
				if( Esam_File_Updata( USER_CARD_PARA_INF_FILE,//01
										ESAM_PARA_INF_FILE,//2
										BUY_PARA_INF_FILE_BUY_CARD,//4
										ESAM_PARA_INF_FILE_ESAM,//4
										2,
										Card_WR_Buff+BUY_PARA_INF_FILE_BUY_CARD) != OK )//+4
					return ERR;
                                Debug_Print(" //��ȡcpu��������Ϣ�ļ��ӱ������1�󲻰��������֤ʱЧ��  ȫ�����ݵ�esam��  " );
                               
				if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,//
										ESAM_PARA_INF_FILE,//
										REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD,//
										REMAIN_MONEY_ALARM1_LIMIT_ESAM,//
										27,
										Card_WR_Buff+REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD) != OK )
					return ERR;
			}
			if( Para_Updata_Flag & 0x02 ){
				if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,////1
										ESAM_PARA_INF_FILE,///2
										TRIFF_SWITCH_TIME_BUY_CARD,
										TRIFF_SWITCH_TIME_ESAM,
										5,
										Card_WR_Buff+TRIFF_SWITCH_TIME_BUY_CARD) != OK )
					return ERR;
			}
                        Debug_Print("����ط����������⣬ Ӧ�ðѴ�cpu���е����ݸ��߻ƹ�   " );
                        //
			//  ��һ�׷��ʱ��ļ� //
			if( Para_Updata_Flag & 0x01 ){
				if( Esam_File_Updata(USER_CARD_TRIFF_1_FILE,//3
										ESAM_TRIFF_1_FILE,//3
										0,
										0,
										240,
										Card_WR_Buff) !=OK )
					return ERR;
				if( Esam_File_Updata(USER_CARD_TRIFF_1_FILE,//3
										ESAM_TRIFF_1_FILE,//4
										240,
										240,
										18,
										Card_WR_Buff+240) !=OK )
					return ERR;
				Deal_Triff_Data(Card_WR_Buff+4,258-4,1);//����ط������д��󣬴�cpu��������������̫����
			}
                        Debug_Print("//  �ڶ��׷��ʱ��ļ� //   " );
			
			if( Para_Updata_Flag & 0x02 ){
				if( Esam_File_Updata(USER_CARD_TRIFF_2_FILE,//4
										ESAM_TRIFF_2_FILE,//4
										0,
										0,
										240,
										Card_WR_Buff) !=OK )
					return ERR;
				if( Esam_File_Updata(USER_CARD_TRIFF_2_FILE,
										ESAM_TRIFF_2_FILE,
										240,
										240,
										18,
										Card_WR_Buff+240) !=OK )
					return ERR;
				Deal_Triff_Data(Card_WR_Buff+4,258-4,2);// 129//����ط������д��󣬴�cpu��������������̫����
			}
          
	}  
       Debug_Print(" //����Ƿ��¿����� ���������ȣ�Dir_Return_Flag����ֵ0xff  " );
	if( Dir_Return_Flag==0 ){//����Ƿ��¿����� ���������ȣ�Dir_Return_Flag����ֵ0xff
		 Debug_Print("  // �жϱ��ι���Ķڻ�����  //  " );
                 // �жϱ��ι���Ķڻ�����  //
		if( Judge_Remain_Money_Over( Moneybag_Data.Remain_Money ) != OK ){//Moneybag_Data.Remain_Money����cpu��
			   Card_Error_State.CardErrorState.MoneyLimitErr=1;
			   return ERR;
		}
		//  ESAMǮ���ļ���ֵ  //�����¹��������������//2,0,0
                
		if(Remain_Money_Moneybag_Add(USER_CARD_MONEYBAG_FILE,REMAIN_MONEY_CPU_ESAM,0)!=OK)
		//	return ERR;
                test();//������Ӧ�ü��� ����esam ��������ĺ���
                Debug_Print("///���߻ƹ�����ֵ�ˣ����˶���Ǯ��ͬ�¸����Ҷ���ı���   " );
		//���߻ƹ�����ֵ�ˣ����˶���Ǯ��ͬ�¸����Ҷ���ı���
		Meter_Money_And_Count_Updata(Moneybag_Data.Remain_Money,Moneybag_Data.Buy_Count );
                Debug_Print(" // �¿������û��źͱ���������״̬ //  " ); 
		// �¿������û��źͱ���������״̬ //
		if( Buy_Card_Kind== GWFAR_USER_CARD_NEW ){
                        Debug_Print("  / �¿������û��źͱ���������״̬ // " );
			My_Memcpy(Pre_Payment_Para.UserID,UserID,6);
		    	Write_Storage_Data(SDI_CUTOMER_ID,&Pre_Payment_Para.UserID, 6);
                        
			Pre_Payment_Para.Meter_Run_State=MeterRunState_Run_3 ;
                        Write_Storage_Data(_SDI_PREPAID_RUN_STATUS,&Pre_Payment_Para.Meter_Run_State, 1);
		}
	} /*
        Meter_Ins_Flag = 0x00;
        //test();
        Debug_Print("����esam������Ϣ�ļ�  1 " ); 
	if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,//1
								ESAM_PARA_INF_FILE,//2
								CLIENT_ID_BUY_CARD,
								CLIENT_ID_ESAM,
								6,
								Card_WR_Buff+CLIENT_ID_BUY_CARD) != OK )
			return ERR;
         Debug_Print("  ����esam������Ϣ�ļ�2 " );
	if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,
								ESAM_PARA_INF_FILE,
								USER_KIND_BUY_CARD,
								USER_KIND_ESAM,
								2,
								Card_WR_Buff+USER_KIND_BUY_CARD) != OK )
			return ERR;
          Debug_Print(" ����esam������Ϣ�ļ� 3  " );
        */
	if( Buy_Card_Kind != GWFAR_USER_CARD_BUY )//�������� �Ͳ������� ��ɢ����
			{
                          Debug_Print("//�������� �Ͳ������� ��ɢ����   " );
			My_Memcpy(Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom, cpucard_number, 8);
                        
			 Write_Storage_Data(_SDI_DISCRETE_INFO ,&Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom,  8);
                        }
        
        // ��д�ļ����� //
        Debug_Print("  ��д�ļ����� //  " );
        test();//0x11�Ǹ�ɶ�ģ�
        //cpu����������Ϣ�ļ���esam��������Ϣ�ļ��ṹ��˳����һ�µģ�������������ļ��Ķ̱�ʾ�ǲ�һ���Ŀ��е�Ϊ5��esam�е�7
        //��esam �ķ�д��Ϣ�ļ���cpu����  ��ӦΪʵ�����Ƕ�esam��������Ϣ�ļ�֮ǰ�� �ȸ���esam������Ϣ�ļ�
	if( Updata_Esam_Return_File(0x11)!=OK )  
		return ERR;
        //����Ҳ����˵�Ƕ�esam ��������Ϣ�ļ���cpu����������Ϣ�ļ��� 
         Debug_Print("��esam �ķ�д��Ϣ�ļ���cpu���� �� �ȸ���esam������Ϣ�ļ�   " );       //5, 7
	if( Cpu_File_Updata(USER_CARD_RUN_INF_FILE,ESAM_RUN_INF_FILE,0,0,LENGTH_RUN_INF_DATA+6) != OK )
		return ERR;
        Debug_Print("���翨ִ�н���   " );
	return OK;
}

////////////�����ļ�����:SrcLenֵΪ�����ļ�����ȥ4(68��16��β)  WhichTable:1��ʾ��һ�׷��ʣ� 2��ʾ�ڶ��׷���
void Deal_Triff_Data(unsigned char * Source_Point,unsigned char SrcLen,INT8U WhichTable){
        Debug_Print("����ط����ƹ����ҵĺ���  ,���»ƹ��ķ������� " );
        //  ����ط����ƹ����ҵĺ���  ,���»ƹ��ķ�������
        INT8U j;
	struct Triff_Data Triff_Data;
        INT32U Temp=SDI_RATE_SCHEME0_0;
        if(SrcLen<sizeof(struct Triff_Data))
        {
            ASSERT_FAILED();
        }
        mem_cpy(&Triff_Data,Source_Point,sizeof( struct Triff_Data),&Triff_Data,sizeof(struct Triff_Data) );
        //�ж�����һ�׷���
        Debug_Print("�ж�����һ�׷��� " );
        if(1 EQ WhichTable){
              Temp=SDI_RATE_SCHEME0_0;
        }else if(2 EQ WhichTable){
              Temp=SDI_RATE_SCHEME1_0;
        }else{
             ASSERT_FAILED();
        }
        Debug_Print("//�ѷ��ʷ���� д��e����ȡ�� �ɻƹ����� " );
        //�ѷ��ʷ���� д��e����ȡ�� �ɻƹ�����
        if(MAX_RATES <= ( sizeof(struct Triff_Data)/4 ) ){
        	for( j=0;j<MAX_RATES;j++ ){
		   Reverse_data((unsigned char *)&(Triff_Data.Triff[j]),4);
                   Write_Storage_Data(Temp+j, (unsigned char *)&(Triff_Data.Triff[j]), 4);
	        }
        }else{
             ASSERT_FAILED();
        }
}


//���߻ƹ�����ֵ�ˣ����˶���Ǯ��ͬ�¸����Ҷ���ı���
//Curr_Buy_Money ��ǰ��ֵ����,unsigned long Curr_Buy_Money_Count ��ǰcpu���е�
void Meter_Money_And_Count_Updata( unsigned long Curr_Buy_Money,unsigned long Curr_Buy_Money_Count )
	{
          
          //���߻ƹ� ���˶��ٵ磬
          Prepaid_Buy_Money_Proc (Curr_Buy_Money);
          //�����ҹ����ȫ�ֱ���
        }
//////////////
void Deal_Buy_Para_Inf_File(unsigned char * Source_Point ){
	/*unsigned char i;
	struct Buy_Para_Inf_File *Buy_Para_Inf_File;
  
	Buy_Para_Inf_File = (struct Buy_Para_Inf_File *)Source_Point;
        
	//Deal_Para_Table2((unsigned char *)&(Buy_Para_Inf_File->User_Kind),Mode);
	//Deal_Para_Table4((unsigned char *)&(Buy_Para_Inf_File->Triff_Switch_Time),Mode);
	//Deal_Para_Table3((unsigned char *)&(Buy_Para_Inf_File->Remain_Money_Alarm1_Limit),Mode);
	//Deal_Para_Table1((unsigned char *)&(Buy_Para_Inf_File->Meter_ID),Mode);
	*/

}

        //SDI_RATE_SCHE_CHG_TIME
///////////
INT8U test(void){return 1;}
