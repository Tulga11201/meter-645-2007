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
INT8U Judge_User_Card_OK(INT8U BuyCard_Kind,INT32U Buy_Count){
	INT32U Money_Count_T;// �����Ƚ� 
        INT32U CurrMeter_MoneyCount;
        
       // INT8U MeterIDTemp[6];
	struct Buy_Para_Inf_File file;// ������Ϣ�ļ��ṹ��
	//struct Moneybag_Data Moneybag_Data;//Ǯ���ļ��ṹ��  4+4���ֽ�
	//��esam ��ȡ Ǯ���ļ�,����������
	//Read_Esam_Moneybag_File((INT8U *)&Moneybag_Data);
	//Pre_Payment_Para.Buy_CountΪ�ƹ�����ĵ�ǰ��������
        
	Money_Count_T = Get_Buy_Eng_Counts()+1;//�����Ƚϴ����Ƿ��1
        // ��ʼִ�к�����Judge_User_Card_OK(INT8U BuyCard_Kind,INT32U Buy_Count) " );
        String2ParaFile(  &file,&Card_WR_Buff[4], sizeof(struct Buy_Para_Inf_File) );
        
	if( (BuyCard_Kind !=GWFAR_USER_CARD_NEW) && (BuyCard_Kind !=GWFAR_USER_CARD_BUY) && (BuyCard_Kind !=GWFAR_USER_CARD_BACK))
	{
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR=1;
	 	return ERR;
	}
        
	if( My_Memcmp(&(file.Meter_ID[0]),(INT8U *)&Pre_Payment_Para.BcdMeterID[0],sizeof(Pre_Payment_Para.BcdMeterID)) )
        {
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.MeterIdErr=1;
		return ERR;
	}
        // //ֻҪ���״̬Ϊ����״̬�������Ƚ��û���// " );
	if(  Pre_Payment_Para.Meter_Run_State  EQ MeterRunState_Run_3 )
        {
               // // �ж��Ƿ��û���Ų���// " );
		if( My_Memcmp((INT8U *)Pre_Payment_Para.UserID,file.Client_ID,LENGTH_USER_ID) )
		{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Client_Id_Err=1;
			  return ERR;
		}

                 //"//���������������ֱ�ӻ�д// " );
                CurrMeter_MoneyCount=Get_Buy_Eng_Counts();
		
                if( My_Memcmp((INT8U *)&Buy_Count, (INT8U *)&(CurrMeter_MoneyCount),4) ==0 ) 
                {
			Dir_Return_Flag = 0xFF;////��ʾ����������ʱֱ�� ��дcpu��   " );
			return OK;
		}
                ////���������״̬���� ������ 
                if( BuyCard_Kind ==GWFAR_USER_CARD_NEW )
                {
                        ASSERT_FAILED();
			Card_Error_State.CardErrorState.WhenInOperation_Insert_FirstUserCard_Err=1;
			return ERR;
		}                
                ////���������״̬���� �������� ����Ƿ���������� " );
		/*if( BuyCard_Kind ==GWFAR_USER_CARD_NEW )
                {
                        ASSERT_FAILED();
			Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR=1;
			return ERR;
		} */
	} //����״̬�жϽ���
	else{
               //// �ж��Ƿ�δ����״̬���빺�翨������  " );
		if( BuyCard_Kind !=GWFAR_USER_CARD_NEW )
			{
                         ASSERT_FAILED();
			 Card_Error_State.CardErrorState.WhenInTest_Insert_UserCard_Err=1;
			 return ERR;
			}
		else
			{
                        //�ж��Ƿ��Ѿ���д�����¿�����ô�����ظ�����// " );
                        //"�Ѿ���д�����¿������ظ�����//
			CPU_ESAM_CARD_Control(CPU);
			Read(0,Read_Binary,0x80+5,0,1);
			CPU_ESAM_CARD_Control(ESAM);
			if( receive_send_buffer[0] == 0x68 )
				{
                                  ASSERT_FAILED();
				  Card_Error_State.CardErrorState.CPU_NEW_CARD_INI_ERR=1;
				  return ERR;
				}
			}
	}//��ʽ���кͷ���ʽ����״̬���жϽ���
       //"// �ж��Ƿ񹺵������//   �������������ϣ�cpu���Ĺ������ �� esam �� +1�󹺵���� ��� " );
        
	if( My_Memcmp((INT8U *)&Buy_Count,(INT8U *)&Money_Count_T,4) !=0)
        {
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR=1;
	 	return ERR;
	}
        // //�ж��Ƿ���ɢ���Ӵ��� " );
	if( BuyCard_Kind == GWFAR_USER_CARD_BUY )
	{
		 if( My_Memcmp((INT8U *)Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom, (INT8U *)cpucard_number, LENGTH_CARD_ID_WHEN_CARD_INSERT) )
                 {
                           ASSERT_FAILED();
			   Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err=1 ;//��������ɢ���Ӵ���,�в�����������ɢ����
		 	   return ERR;
		 }
	}  
        return OK;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//"������,���翨//
INT8U Buy_Card(void){
	INT8U Buy_Card_Kind;//�û������ͣ����翨�� �������� ����
        INT8U UserID[6];//�ͻ����
	struct Moneybag_Data Moneybag_Data;
	struct Buy_Para_Inf_File  file;
        
        String2ParaFile(&file,(&Card_WR_Buff[4]), sizeof(struct Buy_Para_Inf_File) )  ;//��ʼ��file����
        //  ��CPU���е�ʣ���Ѻ͹������ //02  0 �����������ǻ�� cpu���е����ݷ�ת������λ�ڵ�λ��cpu��������ʱ����1 " );
	if( Remain_Money_Moneybag_Add(USER_CARD_MONEYBAG_FILE,REMAIN_MONEY_CPU_ESAM,(INT8U *)&Moneybag_Data) != OK )
		return ERR;
 
	if( Cpucard_External_Auth() != OK )
		return ERR;
         
	Buy_Card_Kind = file.Card_Kind;//
	if( Judge_User_Card_OK( Buy_Card_Kind ,Moneybag_Data.Buy_Count) != OK )
		return ERR;
       //���ĺϷ���������  //  
       My_Memcpy(UserID,file.Client_ID,6);
       //���Ϊ�����������߱�̰�ť������ 
       //Meter_Ins_Flag = 0xFF;
       if( (Buy_Card_Kind EQ GWFAR_USER_CARD_NEW)&&(Dir_Return_Flag !=0xff)) // || Check_Meter_Prog_Status() ){  
       {
                       //���Ϊ������,���߱�̰�ť������ ��ʼ������Ӧ���� " );
			Para_Updata_Flag = file.Para_UpData_Flag;
                       //  ������Ϣ�ļ����� // " );
			if( Para_Updata_Flag & 0x80 )
                        {
                                //��ȡcpu��������Ϣ�ļ�ǰ�������ֽ�
				if( Esam_File_Updata( USER_CARD_PARA_INF_FILE,//01
										ESAM_PARA_INF_FILE,//2
										BUY_PARA_INF_FILE_BUY_CARD,//4
										ESAM_PARA_INF_FILE_ESAM,//4
										2,
										Card_WR_Buff+BUY_PARA_INF_FILE_BUY_CARD) != OK )//+4
                                {
                                  ASSERT_FAILED();
                                  return ERR;
                                }
					
                               //��ȡcpu��������Ϣ�ļ��ӱ������1�󲻰��������֤ʱЧ��  ȫ�����ݵ�esam��  " );
                               
				if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,//
										ESAM_PARA_INF_FILE,//
										REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD,//
										REMAIN_MONEY_ALARM1_LIMIT_ESAM,//
										27,
										Card_WR_Buff+REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD) != OK )
                                {
                                
                                  ASSERT_FAILED();
                                  return ERR;
                                }
					
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
                        //����ط����������⣬ Ӧ�ðѴ�cpu���е����ݸ��߻ƹ�   " );
                        Deal_Buy_Para_Inf_File(Card_WR_Buff+4);
                        //
			//  ��һ�׷��ʱ��ļ� //
			if( Para_Updata_Flag & 0x01 ){
				if( Esam_File_Updata(USER_CARD_TRIFF_1_FILE,//3
										ESAM_TRIFF_1_FILE,//3
										0,
										0,
										240,
										Card_WR_Buff) !=OK )
                                {
                                  
                                  ASSERT_FAILED();
                                  return ERR;
                                }
					
				if( Esam_File_Updata(USER_CARD_TRIFF_1_FILE,//3
										ESAM_TRIFF_1_FILE,//4
										240,
										240,
										18,
										Card_WR_Buff+240) !=OK )
					return ERR;
				Deal_Triff_Data(Card_WR_Buff+4,258-4,1);
			}
                       ////  �ڶ��׷��ʱ��ļ� //   " );
			if( Para_Updata_Flag & 0x02 ){
				if( Esam_File_Updata(USER_CARD_TRIFF_2_FILE,//4
										ESAM_TRIFF_2_FILE,//4
										0,
										0,
										240,
										Card_WR_Buff) !=OK )
                                {
                                   ASSERT_FAILED();
                                   return ERR;
                                }
					
				if( Esam_File_Updata(USER_CARD_TRIFF_2_FILE,
										ESAM_TRIFF_2_FILE,
										240,
										240,
										18,
										Card_WR_Buff+240) !=OK )
                                {
                                
                                  ASSERT_FAILED();
                                  return ERR;
                                
                                }
					
				Deal_Triff_Data(Card_WR_Buff+4,258-4,2);// 129//����ط������д��󣬴�cpu��������������̫����
			}
          
	}  
       Debug_Print(" //����Ƿ��¿����� ���������ȣ�Dir_Return_Flag����ֵ0xff  " );
	if( Dir_Return_Flag EQ 0 )//����Ƿ��¿����� ���������ȣ�Dir_Return_Flag����ֵ0xff
        {
		// �жϱ��ι���Ķڻ�����  //
		if( Check_Buy_Money_Exceed_Limit( Moneybag_Data.Remain_Money) ){//Moneybag_Data.Remain_Money����cpu��
                           ASSERT_FAILED();
			   Card_Error_State.CardErrorState.MoneyLimitErr=1;
			   return ERR;
		}
		//  ESAMǮ���ļ���ֵ  //�����¹��������������//2,0,0
		if(Remain_Money_Moneybag_Add(USER_CARD_MONEYBAG_FILE,REMAIN_MONEY_CPU_ESAM,0)!=OK)
                {
                  ASSERT_FAILED();
                  return ERR;
                }
               /////���߻ƹ�����ֵ�ˣ����˶���Ǯ��ͬ�¸����Ҷ���ı���   " );
		//���߻ƹ�����ֵ�ˣ����˶���Ǯ��ͬ�¸����Ҷ���ı���
		Meter_Money_And_Count_Updata(Moneybag_Data.Remain_Money,Moneybag_Data.Buy_Count );
               // �¿������û��źͱ���������״̬ //  " ); 
		if( Buy_Card_Kind== GWFAR_USER_CARD_NEW )
                {
                        // / �¿������û��źͱ���������״̬ // " );
                        My_memcpyRev((INT8U *)Pre_Payment_Para.UserID,UserID,LENGTH_USER_ID);
		    	Write_Storage_Data(SDI_CUTOMER_ID, (INT8U *)Pre_Payment_Para.UserID, LENGTH_USER_ID);
                        Reverse_data(   (INT8U *)Pre_Payment_Para.UserID,LENGTH_USER_ID);
                        
			Pre_Payment_Para.Meter_Run_State=MeterRunState_Run_3 ;
                        Write_Storage_Data(_SDI_PREPAID_RUN_STATUS,(INT8U *)&Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State) );
		}
	} 
       // Meter_Ins_Flag = 0x00;
        //���ﲻ�Ǹ���
	if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,//1
								ESAM_PARA_INF_FILE,//2
								CLIENT_ID_BUY_CARD,
								CLIENT_ID_ESAM,
								6,
								Card_WR_Buff+CLIENT_ID_BUY_CARD) != OK )
        {
        
           ASSERT_FAILED();
           return ERR;
        }
			
        //���ﲻ�Ǹ���
	if( Esam_File_Updata(USER_CARD_PARA_INF_FILE,
								ESAM_PARA_INF_FILE,
								USER_KIND_BUY_CARD,
								USER_KIND_ESAM,
								2,
								Card_WR_Buff+USER_KIND_BUY_CARD) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
        //
	if( (Buy_Card_Kind != GWFAR_USER_CARD_BUY)&&(Dir_Return_Flag !=0xff) )//�������� �Ͳ������� ��ɢ����
	{
          //�������� �Ͳ������� ��ɢ����   " );
	  My_Memcpy((INT8U *)Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom, (INT8U *)cpucard_number, LENGTH_CARD_ID_WHEN_CARD_INSERT);
	  Write_Storage_Data(_SDI_DISCRETE_INFO ,(INT8U *)&Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom,LENGTH_CARD_ID_BACKUP);
        }
        
        // ��д�ļ����� //
        //cpu����������Ϣ�ļ���esam��������Ϣ�ļ��ṹ��˳����һ�µģ�������������ļ��Ķ̱�ʾ�ǲ�һ���Ŀ��е�Ϊ5��esam�е�7
        //��esam �ķ�д��Ϣ�ļ���cpu����  ��ӦΪʵ�����Ƕ�esam��������Ϣ�ļ�֮ǰ�� �ȸ���esam������Ϣ�ļ�
	if( Updata_Esam_Return_File(0x11)!=OK )  
        {
          ASSERT_FAILED();
          return ERR;
        }
		
        //����Ҳ����˵�Ƕ�esam ��������Ϣ�ļ���cpu����������Ϣ�ļ��� 5,7
	if( Cpu_File_Updata(USER_CARD_RUN_INF_FILE,ESAM_RUN_INF_FILE,0,0,LENGTH_RUN_INF_DATA-1+6) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
	return OK;
}

//�����ļ�����:SrcLenֵΪ�����ļ�����ȥ4(68��16��β) ��ȥ4������Ϊ�������ĵ�ַΪ��һ������ WhichTable:1��ʾ��һ�׷��ʣ� 2��ʾ�ڶ��׷���
void Deal_Triff_Data(INT8U * Source_Point,INT8U SrcLen,INT8U WhichTable){
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
        /*if(1 EQ WhichTable){
              Temp=SDI_RATE_SCHEME0_0;
        }else if(2 EQ WhichTable){
              Temp=SDI_RATE_SCHEME1_0;
        }else{
             ASSERT_FAILED();
        }*/
        if((WhichTable !=1)
          &&(WhichTable != 2))
        {
           ASSERT_FAILED();
        }
        Temp=Get_Card_Set_Rate_Scheme_SDI(WhichTable);
        ////�ѷ��ʷ���� д��e����ȡ�� �ɻƹ����� " );
        //�ѷ��ʷ���� д��e����ȡ�� �ɻƹ�����
        if(MAX_RATES <= ( sizeof(struct Triff_Data)/4 ) ){
        	for( j=0;j<MAX_RATES;j++ ){
		   Reverse_data((INT8U *)&(Triff_Data.Triff[j]),4);
                   Write_Storage_Data(Temp+j, (INT8U *)&(Triff_Data.Triff[j]), 4);
	        }
        }else{
             ASSERT_FAILED();
        }
        Card_Set_Para_Notice() ;//���߻ƹ� �޸���e��
}


//���߻ƹ�����ֵ�ˣ����˶���Ǯ��ͬ�¸����Ҷ���ı���,/
//Curr_Buy_Money ��ǰ��ֵ����,INT32U Curr_Buy_Money_Count ��ǰcpu���е�
void Meter_Money_And_Count_Updata( INT32U Curr_Buy_Money,INT32U Curr_Buy_Money_Count )
	{
          
          //���߻ƹ� ���˶��ٵ磬
          Prepaid_Buy_Money_Proc (Curr_Buy_Money);
          //�����ҹ����ȫ�ֱ���
        }
//////////////
void Deal_Buy_Para_Inf_File(INT8U * Source_Point ){
	//INT8U i;
	struct Buy_Para_Inf_File Buy_Para_Inf_File;
        mem_cpy((INT8U *)&Buy_Para_Inf_File , Source_Point,sizeof(Buy_Para_Inf_File),(INT8U *)&Buy_Para_Inf_File,sizeof(Buy_Para_Inf_File));

	Deal_Para_Table2( (INT8U *)&(Buy_Para_Inf_File.User_Kind) );
	Deal_Para_Table4( (INT8U *)&(Buy_Para_Inf_File.Triff_Switch_Time)  );
	Deal_Para_Table3( (INT8U *)&(Buy_Para_Inf_File.Remain_Money_Alarm1_Limit)  );
	//Deal_Para_Table1((INT8U *)&(Buy_Para_Inf_File->Meter_ID),Mode);
        if(  (Para_Updata_Flag & 0x80 )||(Para_Updata_Flag & 0x02)  )
        {
          Card_Set_Para_Notice() ;
        }
        return ;
}

        //SDI_RATE_SCHE_CHG_TIME
///////////
 
