#include "MyIncludesAll.h"
#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//"更新是否更新标志//
//"位	  //
//"Bit0	费率表第一套 //
//"Bit1	费率表第二套 //
//"Bit2	保留 //
//"Bit3	保留 //
//"Bit4	保留 //
//"Bit5	保留 //
//"Bit6	保留 //
//"Bit7	其他参数 //
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//" 开户卡,购电卡，比较合法性//  Buy_Count 为cpu卡的购电次数
INT8U Judge_User_Card_OK(INT8U BuyCard_Kind,INT32U Buy_Count){
	INT32U Money_Count_T;// 用来比较 
        INT32U CurrMeter_MoneyCount;
        
       // INT8U MeterIDTemp[6];
	struct Buy_Para_Inf_File file;// 参数信息文件结构体
	//struct Moneybag_Data Moneybag_Data;//钱包文件结构体  4+4个字节
	//从esam 读取 钱包文件,读出来后反相
	//Read_Esam_Moneybag_File((INT8U *)&Moneybag_Data);
	//Pre_Payment_Para.Buy_Count为黄工管理的当前电表购电次数
        
	Money_Count_T = Get_Buy_Eng_Counts()+1;//用来比较次数是否大1
        // 开始执行函数：Judge_User_Card_OK(INT8U BuyCard_Kind,INT32U Buy_Count) " );
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
        // //只要表计状态为运行状态，则必须比较用户号// " );
	if(  Pre_Payment_Para.Meter_Run_State  EQ MeterRunState_Run_3 )
        {
               // // 判断是否用户编号不对// " );
		if( My_Memcmp((INT8U *)Pre_Payment_Para.UserID,file.Client_ID,LENGTH_USER_ID) )
		{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Client_Id_Err=1;
			  return ERR;
		}

                 //"//如果购电次数相等则直接回写// " );
                CurrMeter_MoneyCount=Get_Buy_Eng_Counts();
		
                if( My_Memcmp((INT8U *)&Buy_Count, (INT8U *)&(CurrMeter_MoneyCount),4) ==0 ) 
                {
			Dir_Return_Flag = 0xFF;////标示购电次数相等时直接 返写cpu卡   " );
			return OK;
		}
                ////如果是运行状态插入 开户卡 
                if( BuyCard_Kind ==GWFAR_USER_CARD_NEW )
                {
                        ASSERT_FAILED();
			Card_Error_State.CardErrorState.WhenInOperation_Insert_FirstUserCard_Err=1;
			return ERR;
		}                
                ////如果是运行状态插入 开户卡， 计入非法卡插入次数 " );
		/*if( BuyCard_Kind ==GWFAR_USER_CARD_NEW )
                {
                        ASSERT_FAILED();
			Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR=1;
			return ERR;
		} */
	} //运行状态判断结束
	else{
               //// 判断是否未开户状态插入购电卡，补卡  " );
		if( BuyCard_Kind !=GWFAR_USER_CARD_NEW )
			{
                         ASSERT_FAILED();
			 Card_Error_State.CardErrorState.WhenInTest_Insert_UserCard_Err=1;
			 return ERR;
			}
		else
			{
                        //判断是否已经回写过的新卡，那么不能重复开户// " );
                        //"已经回写过的新卡不能重复开户//
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
	}//正式运行和非正式运行状态的判断结束
       //"// 判断是否购电次数错//   购电次数必须符合：cpu卡的购电次数 与 esam 的 +1后购电次数 相等 " );
        
	if( My_Memcmp((INT8U *)&Buy_Count,(INT8U *)&Money_Count_T,4) !=0)
        {
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR=1;
	 	return ERR;
	}
        // //判断是否离散因子错了 " );
	if( BuyCard_Kind == GWFAR_USER_CARD_BUY )
	{
		 if( My_Memcmp((INT8U *)Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom, (INT8U *)cpucard_number, LENGTH_CARD_ID_WHEN_CARD_INSERT) )
                 {
                           ASSERT_FAILED();
			   Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err=1 ;//卡错误。离散因子错了,有补卡更新了离散因子
		 	   return ERR;
		 }
	}  
        return OK;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//"开户卡,购电卡//
INT8U Buy_Card(void){
	INT8U Buy_Card_Kind;//用户卡类型，购电卡， 开户卡， 补卡
        INT8U UserID[6];//客户编号
	struct Moneybag_Data Moneybag_Data;
	struct Buy_Para_Inf_File  file;
        
        String2ParaFile(&file,(&Card_WR_Buff[4]), sizeof(struct Buy_Para_Inf_File) )  ;//初始化file变量
        //  读CPU卡中的剩余电费和购电次数 //02  0 读出来，但是会把 cpu卡中的数据反转，即高位在低位，cpu卡中数据时反得1 " );
	if( Remain_Money_Moneybag_Add(USER_CARD_MONEYBAG_FILE,REMAIN_MONEY_CPU_ESAM,(INT8U *)&Moneybag_Data) != OK )
		return ERR;
 
	if( Cpucard_External_Auth() != OK )
		return ERR;
         
	Buy_Card_Kind = file.Card_Kind;//
	if( Judge_User_Card_OK( Buy_Card_Kind ,Moneybag_Data.Buy_Count) != OK )
		return ERR;
       //卡的合法条件满足  //  
       My_Memcpy(UserID,file.Client_ID,6);
       //如果为开户卡，或者编程按钮被按下 
       //Meter_Ins_Flag = 0xFF;
       if( (Buy_Card_Kind EQ GWFAR_USER_CARD_NEW)&&(Dir_Return_Flag !=0xff)) // || Check_Meter_Prog_Status() ){  
       {
                       //如果为开户卡,或者编程按钮被按下 开始进入相应流程 " );
			Para_Updata_Flag = file.Para_UpData_Flag;
                       //  参数信息文件处理 // " );
			if( Para_Updata_Flag & 0x80 )
                        {
                                //读取cpu卡参数信息文件前面两个字节
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
					
                               //读取cpu卡参数信息文件从报警金额1后不包含身份验证时效的  全部数据到esam卡  " );
                               
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
                        //这个地方肯能有问题， 应该把从cpu卡中的数据告诉黄工   " );
                        Deal_Buy_Para_Inf_File(Card_WR_Buff+4);
                        //
			//  第一套费率表文件 //
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
                       ////  第二套费率表文件 //   " );
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
					
				Deal_Triff_Data(Card_WR_Buff+4,258-4,2);// 129//这个地方可能有错误，从cpu卡读出来的数据太长了
			}
          
	}  
       Debug_Print(" //如果是非新卡，且 购电次数相等，Dir_Return_Flag被赋值0xff  " );
	if( Dir_Return_Flag EQ 0 )//如果是非新卡，且 购电次数相等，Dir_Return_Flag被赋值0xff
        {
		// 判断本次购电的囤积门限  //
		if( Check_Buy_Money_Exceed_Limit( Moneybag_Data.Remain_Money) ){//Moneybag_Data.Remain_Money来自cpu卡
                           ASSERT_FAILED();
			   Card_Error_State.CardErrorState.MoneyLimitErr=1;
			   return ERR;
		}
		//  ESAM钱包文件充值  //不更新购电次数？？？？//2,0,0
		if(Remain_Money_Moneybag_Add(USER_CARD_MONEYBAG_FILE,REMAIN_MONEY_CPU_ESAM,0)!=OK)
                {
                  ASSERT_FAILED();
                  return ERR;
                }
               /////告诉黄工，充值了，充了多少钱，同事更新我定义的变量   " );
		//告诉黄工，充值了，充了多少钱，同事更新我定义的变量
		Meter_Money_And_Count_Updata(Moneybag_Data.Remain_Money,Moneybag_Data.Buy_Count );
               // 新卡保存用户号和变更表计运行状态 //  " ); 
		if( Buy_Card_Kind== GWFAR_USER_CARD_NEW )
                {
                        // / 新卡保存用户号和变更表计运行状态 // " );
                        My_memcpyRev((INT8U *)Pre_Payment_Para.UserID,UserID,LENGTH_USER_ID);
		    	Write_Storage_Data(SDI_CUTOMER_ID, (INT8U *)Pre_Payment_Para.UserID, LENGTH_USER_ID);
                        Reverse_data(   (INT8U *)Pre_Payment_Para.UserID,LENGTH_USER_ID);
                        
			Pre_Payment_Para.Meter_Run_State=MeterRunState_Run_3 ;
                        Write_Storage_Data(_SDI_PREPAID_RUN_STATUS,(INT8U *)&Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State) );
		}
	} 
       // Meter_Ins_Flag = 0x00;
        //这里不是更新
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
			
        //这里不是更新
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
	if( (Buy_Card_Kind != GWFAR_USER_CARD_BUY)&&(Dir_Return_Flag !=0xff) )//开户卡， 和补卡更新 离散因子
	{
          //开户卡， 和补卡更新 离散因子   " );
	  My_Memcpy((INT8U *)Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom, (INT8U *)cpucard_number, LENGTH_CARD_ID_WHEN_CARD_INSERT);
	  Write_Storage_Data(_SDI_DISCRETE_INFO ,(INT8U *)&Pre_Payment_Para.Cpucard_Number_old_BackUpInEerom,LENGTH_CARD_ID_BACKUP);
        }
        
        // 回写文件处理 //
        //cpu卡的运行信息文件和esam的运行信息文件结构和顺序都是一致的，但是这个两个文件的短标示是不一样的卡中的为5，esam中的7
        //读esam 的返写信息文件到cpu卡中  ，应为实际上是读esam的运行信息文件之前， 先更新esam运行信息文件
	if( Updata_Esam_Return_File(0x11)!=OK )  
        {
          ASSERT_FAILED();
          return ERR;
        }
		
        //这里也可以说是读esam 的运行信息文件到cpu卡中运行信息文件中 5,7
	if( Cpu_File_Updata(USER_CARD_RUN_INF_FILE,ESAM_RUN_INF_FILE,0,0,LENGTH_RUN_INF_DATA-1+6) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
	return OK;
}

//费率文件更新:SrcLen值为：总文件长减去4(68到16结尾) 减去4，是因为传过来的地址为第一个费率 WhichTable:1表示第一套费率， 2表示第二套费率
void Deal_Triff_Data(INT8U * Source_Point,INT8U SrcLen,INT8U WhichTable){
        //  这个地方调黄工给我的函数  ,更新黄工的费率数据
        INT8U j;
	struct Triff_Data Triff_Data;
        INT32U Temp=SDI_RATE_SCHEME0_0;
        if(SrcLen<sizeof(struct Triff_Data))
        {
            ASSERT_FAILED();
        }
        mem_cpy(&Triff_Data,Source_Point,sizeof( struct Triff_Data),&Triff_Data,sizeof(struct Triff_Data) );
        //判断是那一套费率
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
        ////把费率反相后 写到e方中取， 由黄工解释 " );
        //把费率反相后 写到e方中取， 由黄工解释
        if(MAX_RATES <= ( sizeof(struct Triff_Data)/4 ) ){
        	for( j=0;j<MAX_RATES;j++ ){
		   Reverse_data((INT8U *)&(Triff_Data.Triff[j]),4);
                   Write_Storage_Data(Temp+j, (INT8U *)&(Triff_Data.Triff[j]), 4);
	        }
        }else{
             ASSERT_FAILED();
        }
        Card_Set_Para_Notice() ;//告诉黄工 修改了e方
}


//告诉黄工，充值了，充了多少钱，同事更新我定义的变量,/
//Curr_Buy_Money 当前充值费用,INT32U Curr_Buy_Money_Count 当前cpu卡中的
void Meter_Money_And_Count_Updata( INT32U Curr_Buy_Money,INT32U Curr_Buy_Money_Count )
	{
          
          //告诉黄工 充了多少电，
          Prepaid_Buy_Money_Proc (Curr_Buy_Money);
          //更新我管理的全局变量
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
 
