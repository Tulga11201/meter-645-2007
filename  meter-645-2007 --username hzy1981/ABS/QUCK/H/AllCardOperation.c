#define ALL_CARD_OPERATION_C_

#include "MyIncludesAll.h"

#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print
extern INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen);
//C_Pre_Payment_Para Pre_Payment_Para;
//ic卡 入口函数
//返回1 表示成功， 返回0 表示失败
INT8U ICcardMain(void) {
       
       INT32U Temp;
       char ret;

       //Prepaid_Set_Buy_Money_Counts(0,0); 
        if( JUDGE_CPU_INSERT)//卡存在
        {
          Debug_Print("-----------检测到卡插入--------- " );
        }else{//卡不存在
           Debug_Print("-----------没检测到卡插入--------- " );
           return  0;
        }        
        WhenCardInsertedInitPrePayData();//更新我管理的全局变量
	Card_Switch_On();//黄工的函数，好像是 处理，插卡时，允许合闸的
	if(Check_CPU_Occur()){
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return 0;
	}

        Clr_Card_Op_Info(); //  这个函数 黄工给的 具体什么工能不知道
        
        OS_Mutex_Pend(PUB_BUF_SEM_ID);//使用缓冲：Pub_Buf0
        OS_Mutex_Pend(PUB_BUF0_SEM_ID); //使用信号量，以便使用缓冲	
	ret=ICcardProcess();//Card Operate
        OS_Mutex_Post(PUB_BUF0_SEM_ID);
        OS_Mutex_Post(PUB_BUF_SEM_ID);
        
        Prepaid_Card_Op_Aft_Proc(); //处理卡处理的遗留操作，包括编程记录等
        Debug_Print("-------ret:%d---- ------ ",ret );
        //处理放回状态字
	if(ret!= OK){
		if(   Card_Error_State.CardErrorState.MeterIdErr EQ 1 //表号不匹配，计入非法卡插入次数 
                   || Card_Error_State.CardErrorState.CardIdErr EQ 1 // 用户编号错误 ,当表开户了后会出现 表未开户不会出现  
                   || Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr EQ 1 //外部认证错误
                   || Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr EQ 1// 内部认证， 即身份验证。计入非法卡插入次数
                   || Card_Error_State.CardErrorState.CARD_STATE_ERR EQ 1//未开户状态插入购电卡和补卡/
                   || Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR EQ 1// 购电卡卡类型错 补卡，开户卡。类型没找到以及开户卡状态 插入 开户卡
                   || Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR EQ 1//购电次数错误  计入非法卡插入次数
                   || Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err EQ 1 /// 离散因子错了， 计入非法卡插入次数
                  )
		{
                        //非法卡次数加1，写到e方中去
                        Read_Storage_Data(_SDI_INVALID_CARD_COUNTS, &Temp, &Temp, 4  );//    
                        ++Temp;
                        Write_Storage_Data(_SDI_INVALID_CARD_COUNTS ,&Temp,4);
		}
                //_Debug_Print("Operate Type=%d,Card Time=%ld Ms",CardType,Get_Pay_Ms_Time());
                PrintErrState();
                Debug_Print("卡 操作结束 ， ，返回0" );
                return 0;
	}else{
                   //_Debug_Print("Operate Type=%d,Card Time=%ld Ms",CardType,Get_Pay_Ms_Time());
                   PrintErrState();
                   Debug_Print("卡 操作结束 ，，返回1 " );
                   return 1;
       }

}
//卡处理
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
        //读写cpu卡二进制文件
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
        //文件总长度 
	length= receive_send_buffer[3];
	length+=6;
       
	if( Read(0,Read_Binary,0x80+1,0,length) != OK ){
		return ERR;
	}
        //对读取的二进制文件进行 检查：  头尾， 效验和 
	if( Frame_Judge(&receive_send_buffer[0],length)!= OK ){
               return ERR;
        }
        //读取的cpu卡指令信息文件内容无错误 
	My_Memcpy(Card_WR_Buff,receive_send_buffer,length);
       
	if( Cpucard_Esamcard_Internal_Auth() != OK ){
                Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr=1;
		return ERR;
	}
        //黄工的数据，更新esam 内部钱包文件
        if( Esam_Remain_Money_Dec() != OK )
        {
		Card_Error_State.CardErrorState.EsamUpdataErr=1;
                ASSERT_FAILED();
		return ERR;
        }
        Debug_Print("-----------根据卡的类型，进入相应的程序-------------" );
        Debug_Print("-------------------卡类型:%x------------------------ ",CardType );
	CPU_ESAM_CARD_Control(CPU);
	switch (CardType)
        {
		case GWFAR_USER_CARD:		//" 用户卡 "
			ret=Buy_Card();
			break;
		case GWFAR_MOD_PASSWORD_CARD:	//" 修改密钥卡 "
		case GWFAR_RES_PASSWORD_CARD: 	//" 恢复密钥卡 "
			ret=Password_Card();
			break;
		case GWFAR_PARA_SET_CARD:	//现场参数设置卡
			ret=Field_Para_Set_Card();
			break;
		case GWFAR_READ_ESAM_CARD:	//" ESAM数据回抄卡 "
			ret=Check_Card();
			break;
		case GWFAR_INIT_CARD:		//" 出厂设置卡  参数预置卡
			ret=Set_In_Card();
			break;	
		case GWFAR_MOD_METERID_CARD:	//" 表号设置卡 "
			ret=Modify_MeterID_Card();
			break;
		case GWFAR_ADDD_MONEY_CARD:	//" 增加电量卡 "
			ret = Add_Money_Card();
			break;
		case GWFAR_RELAY_TEST_CARD:	//" 继电器测试卡 "
			ret = Relay_TEST_Card();
			break;
		default: 			//"卡类型或状态不对"
                        ASSERT_FAILED(); 
			Card_Error_State.CardErrorState.CardKindErr=1; ////"卡类型或状态不对",购电卡，参数预置卡
			ret=1;
			break;
       }
       if(Check_Meter_Prog_Status())
       {
            CardProgrammeEvent();//编程按钮按下时 ，调用  z编程记录
       }
       
       return ret;     
}
 


/*"IC卡修改参数编程记录"*/ //会把离散因子后4位，参数更新标志位， 卡类型（购电卡，参会预置卡），密钥状态（公开，正式）
// 返回类型没用， 不会判断
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

//判断文件数据结构的帧头帧尾和效验和是否合法
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
//计算累加效验和
unsigned char Cal_Add_CS(unsigned char * Point,unsigned char L){
        unsigned char Cs,i;

	Cs = 0;
	for(i=0;i<L;i++){
            Cs+=*Point++;
        }
		
	return Cs;
}

//esam数据回抄卡
unsigned char Check_Card(void){
	
	/*" 钱包文件 "*/
	if(Remain_Money_Moneybag_To_Cpu())
		return ERR;

	
         Debug_Print("  参数信息文件   "  );//3
	if( Cpu_File_Updata(ESAM_BACK_PARA_INF_FILE,//03
					     ESAM_PARA_INF_FILE,//02
					     0,
					     0,
					     LENGTH_ESAM_PARA_INF_FILE+6-1) != OK )
        {
           ASSERT_FAILED();
           return ERR;
        }
		 
        Debug_Print(" 第一套费率表文件   "  );
	// 第一套费率表文件//
     
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
        Debug_Print("   第二套费率表文件   "  );
	 
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
        Debug_Print("  本地密钥信息文件 "  ); 
	//本地密钥信息文件//
	if( Cpu_File_Updata(ESAM_BACK_PASSWORD_INF_FILE,//06
					     ESAM_PASSWORD_INF_FILE,//5
					     0,
					     0,
					     4) != OK )
		return ERR;
       Debug_Print("远程密钥信息文件    "  );
	 /// 远程密钥信息文件//
	if( Cpu_File_Updata(ESAM_BACK_FAR_PASSWORD_INF_FILE,//07
					     ESAM_FAR_PASSWORD_INF_FILE,//06
					     0,
					     0,
					     4) != OK )
		return ERR; 
        Debug_Print( " //读取esam 运行信息文件前，先更新esam运行信息文件，数据来源于电能表   "  );
	
	if( Updata_Esam_Return_File(0x15) != OK )
		return ERR;
       
        Debug_Print( "  // 读取esam运行信息文件， 更新esam数据回抄卡   "  );
	if( Cpu_File_Updata(ESAM_BACK_RUN_INF_FILE,
					     ESAM_RUN_INF_FILE,
					     0,
					     0,
					     LENGTH_RUN_INF_DATA-1+6) != OK )
		return ERR;
 
	return OK;
}
unsigned char Field_Para_Set_Card(void){//现场参数设置卡
	unsigned long Version_Temp;
	unsigned long Count_Temp;
	if(!Check_Meter_Prog_Status())
		{
                  Debug_Print( "编程按钮没被按下  "  );
		  Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		  return ERR;
		}
        Debug_Print( "  //从cpu卡中得到 版本号 "  );
        //从cpu卡中得到 版本号
	if( Get_File_Data(CPU,PARA_SET_CARD_PARA_INF_FILE,PARA_CARD_VERSION_SET_CARD,4,( unsigned char * )&Version_Temp) != OK )
		return ERR;
        Debug_Print( "//从cpu卡中得打 计数器文件值  "  );
        //从cpu卡中得打 计数器文件值
	CPU_ESAM_CARD_Control(CPU);
	if( Read(0,0xB2,1,0x24,4) != OK)
		return ERR;
	My_memcpyRev( ( unsigned char * )&Count_Temp,receive_send_buffer,4 );
         Debug_Print( "// 比较cpu卡的版本号是否大于自己管理的版本号， 计数器文件的值是否为0  "  );
       // 比较cpu卡的版本号是否大于自己管理的版本号， 计数器文件的值是否为0
	if( Version_Temp<=Pre_Payment_Para.Para_Card_Version || Count_Temp ==0 )
		{
		  Card_Error_State.CardErrorState.CPU_Para_Card_Version_Err=1;  
		  return ERR;
		}
	Para_Updata_Flag = Card_WR_Buff[5];
	Debug_Print( " 参数信息文件处理 "  );
	/*" 参数信息文件处理 "*/
	Meter_Ins_Flag = 0xFF;//指令变化
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
        Debug_Print( " 把从 cpu卡得到 的 用户类型，费率切换时间， 保存到电能表中去 "  );
        //把从 cpu卡得到 的 用户类型，费率切换时间， 保存到电能表中去
	Deal_Set_Para_Inf_File(Card_WR_Buff+4,0x80);
	Debug_Print( "第一套费率表文件  "  );	
	// " 第一套费率表文件 " /
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
	Debug_Print( "第二套费率表文件  "  );
	// 第二套费率表文件  //
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
         Debug_Print( "更新cpu卡计数器文件更新  "  );
	 //更新cpu卡计数器文件更新 
	if( CPU_Counter_Dec(0x24,4) != OK ){
          Debug_Print( " 更新cpu卡计数器文件更新失败 "  );
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
        Debug_Print( "   //我管理的 ESAM版本号更新 "  );
		
        //我管理的 ESAM版本号更新  
	Pre_Payment_Para.Para_Card_Version = Version_Temp;
        if( 0 EQ Write_Storage_Data(_SDI_PREPAID_PARA_CARD_VER ,&Pre_Payment_Para.Para_Card_Version,  4) ){
            //假如写e方失败
          Debug_Print( " //假如写e方失败  "  );
            Card_Error_State.CardErrorState.ReadWriteE2romErr=1;
        }
        
        Debug_Print( "函数执行成功  "  );  
	return OK;  
}
// //把从 cpu卡得到 的 用户类型，费率切换时间， 保存到电能表中去
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
//参数预置卡
unsigned char Set_In_Card(void){///出厂预制卡"
          INT8U Order_Head[11];
          INT32U Temp;

	struct Moneybag_Data Moneybag_Data;
	
	if(!Check_Meter_Prog_Status()){
                 //编程按钮没被按下  "  );
		 Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		 return ERR;
	}
	Para_Updata_Flag = Card_WR_Buff[5];
       // 参数更新标志位为 :%x ",Para_Updata_Flag  );
        // 参数信息文件处理  "  );
	// 参数信息文件处理//
	if( Para_Updata_Flag & 0x80 ){
                // " ----------- 参数更新标志位与0x8为真，开始更新1用户类型，参数更新标志位-----------  "  );
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
               // ----------- 参数更新标志位与0x2为真，开始更新2------------  "  );
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
        //更新数据到esam后，更新电能表保存的数据 "  );	
	Deal_Init_Para_Inf_File(Card_WR_Buff+4,0x80);
	// 第一套费率表文件 "  );
	//  第一套费率表文件 //
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
        //"第二套费率表文件 "  );
	//  第二套费率表文件  //
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
        // // 钱包文件初始化 //读取cpu卡的钱包文件值设置esam中的钱包文件 "  );
	// 钱包文件初始化 //读取cpu卡的钱包文件值设置esam中的钱包文件
	if( Remain_Money_Moneybag_Init() != OK  ) {
            return ERR;
        }
        // 从esam 中读取被更新后的钱包文件，用他来更新到电表中 读出来后会反相
	Read_Esam_Moneybag_File( (INT8U * )&Moneybag_Data);

        // " 开始更新电表中的数据"  );
        //更新购电次数,更新剩余金额
        Prepaid_Set_Buy_Money_Counts(Moneybag_Data.Remain_Money, Moneybag_Data.Buy_Count);
        //表的运行状态
	Pre_Payment_Para.Meter_Run_State=0;
        Write_Storage_Data(_SDI_PREPAID_RUN_STATUS ,&Pre_Payment_Para.Meter_Run_State  , 1 );
        //清除远程非法攻击次数
        FarPrePayment.ID_Ins_Counter  =0;
	Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, &FarPrePayment.ID_Ins_Counter, 1);
        //本地非法卡插入次数清0
        Temp=0;
        Write_Storage_Data(_SDI_INVALID_CARD_COUNTS ,&Temp,4);
        //事件记录清0， 只是改全局变量， 真正的清0 ，在后面的任务中进行
        Card_Clr_All_Data(); 
               
	return OK;
}
///参数预置卡， 更改了esam中的参数后，改表中的
void Deal_Init_Para_Inf_File(unsigned char * Source_Point,unsigned char Mode)
{
    struct Init_Para_Inf_File   Init_Para_Inf_File;
    mem_cpy(&Init_Para_Inf_File,Source_Point,sizeof(struct Init_Para_Inf_File),&Init_Para_Inf_File,sizeof(struct Init_Para_Inf_File));
    //更新电表的德购电类型， 是单费率还是复费率
    Debug_Print("更新电表的德购电类型:%d",(Init_Para_Inf_File.User_Kind) ); 
    Deal_Para_Table2( (unsigned char *)&(Init_Para_Inf_File.User_Kind) );
    
    //现场参数设置卡版本号
    if( Para_Updata_Flag&0x80 ){
       My_memcpyRev((INT8U *)&Pre_Payment_Para.Para_Card_Version,(INT8U *)&Init_Para_Inf_File.Para_Card_Version,4  );
       Write_Storage_Data( _SDI_PREPAID_PARA_CARD_VER,&Pre_Payment_Para.Para_Card_Version  , 4 );
    }
    Debug_Print("// 更新电表的费率切换时间: ");  
    // 更新电表的费率切换时间
    Deal_Para_Table4((unsigned char *)&(Init_Para_Inf_File.Triff_Switch_Time));
     Debug_Print("//更新报警金额1和2， 以及电压，电流互感变化 ");  
    //更新报警金额1和2， 以及电压，电流互感变化
    Deal_Para_Table3((unsigned char *)&(Init_Para_Inf_File.Remain_Money_Alarm1_Limit));
    if(  (Para_Updata_Flag & 0x80 )||(Para_Updata_Flag & 0x02)  )
    {
          Card_Set_Para_Notice() ;
    }
    return ;    
}
///	 用户类型 : 单费率，还是复费率
void Deal_Para_Table2(unsigned char * Source_Point ){
         
        INT8U SingleKing_OrComplexKing;//这个数据标示目前没用到，扩展用
        SingleKing_OrComplexKing=*Source_Point;
	if( Para_Updata_Flag&0x80 ){
          Write_Storage_Data(_SDI_SINGLE_OR_COMPLEX_USER_KIND, &SingleKing_OrComplexKing,1);
	}
}
//" 两套分时费率切换时间  
void Deal_Para_Table4(unsigned char * Source_Point ){
        INT8U Temp[5];
        mem_cpy(Temp,Source_Point,5,Temp,5);
        //从cpu卡中读出来的数据，第一个字节为年，第二个月， 以此类推,我们定义的时间结构体，第一个为分，而威胜的第一个位年，所
        //以我们的要反， 他们的不要
        Debug_Print( "从cpu卡读出来的时间bcd码为： Temp[4]:%x Temp[3]:%x Temp[2]:%x Temp[1]:%x Temp[0]:%x  ",Temp[4],Temp[3],Temp[2],Temp[1],Temp[0]);
	if( Para_Updata_Flag&0x02 ){ 
          Reverse_data(Temp,5);//根据45协议，pDst【0】应该是软件上 最高位
          Write_Storage_Data(SDI_RATE_SCHE_CHG_TIME, Temp, 5 );
	} 
}
//	unsigned long Remain_Money_Alarm1_Limit;  报警金额1 "
//	unsigned long Remain_Money_Alarm2_Limit; 报警金额2 "
//	unsigned char Current_CT[3];             电流互感器变比 "
//	unsigned char Voltage_PT[3];             电压互感器变比 
void Deal_Para_Table3(unsigned char * Source_Point )
{
	struct Para_Table3 ParaTable3;
	mem_cpy(&ParaTable3,Source_Point,sizeof(struct Para_Table3),&ParaTable3,sizeof(struct Para_Table3) );
	if( Para_Updata_Flag&0x80 )
  {
		Reverse_data((unsigned char *)&(ParaTable3.Remain_Money_Alarm1_Limit),4);
                //从cpu卡读出来的报警金额1反相后为：Temp[3]:%x Temp[2]:%x Temp[1]:%x Temp[0]:%x  ",Temp[3],Temp[2],Temp[1],Temp[0]);
                Write_Storage_Data(SDI_PREPAID_WARN_MONEY1 , (unsigned char *)&(ParaTable3.Remain_Money_Alarm1_Limit) , 4)   ;
		
                Reverse_data((unsigned char *)&(ParaTable3.Remain_Money_Alarm2_Limit),4);
                //从cpu卡读出来的报警金额2反相后为:Temp[3]:%x Temp[2]:%x Temp[1]:%x Temp[0]:%x ",Temp[3],Temp[2],Temp[1],Temp[0]);
                Write_Storage_Data(SDI_PREPAID_WARN_MONEY2 ,(unsigned char *)&(ParaTable3.Remain_Money_Alarm2_Limit)  , 4)  ; 
		
                Reverse_data((unsigned char *)&(ParaTable3.Current_CT[0]),3);
                Write_Storage_Data(SDI_CURR_TRANS_RATIO , (unsigned char *)&(ParaTable3.Current_CT[0]) , 3) ;  

                Reverse_data((unsigned char *)&(ParaTable3.Voltage_PT[0]),3);
                //从cpu卡读出来的报警金额1反相后为:Temp[2]:%x Temp[1]:%x Temp[0]:%x ",Temp[2],Temp[1],Temp[0]);
                Write_Storage_Data(SDI_VOLT_TRANS_RATIO , (unsigned char *)&(ParaTable3.Voltage_PT[0]) , 3);  
	}
}
////
unsigned char Password_Card(void)//密钥下装卡/恢复卡
{
	struct Password_Inf_File  File_Point;//指令信息文件，没有去除头尾
	
	unsigned char Esam_Password_Info[4];
	unsigned char Cpu_Password_Info[4];
	unsigned long Temp;
	unsigned char PassWord_Kind;

	if( !Check_Meter_Prog_Status() ){
		Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		return ERR;
	}
        //读计数器文件 ，并判断是否计数器文件的值为0
	if( Read(0,0xB2,1,0x14,4) != OK)
		return ERR;
	Temp = 0;
	if( My_Memcmp( (INT8U *) &Temp, receive_send_buffer, 4)==0 ){
                 ASSERT_FAILED();
		 Card_Error_State.CardErrorState.Password_Count_Number_Is_Zero_Err=1;
		 return ERR;
	}
	My_memcpyRev((INT8U *)&Temp, receive_send_buffer, 4);
        //得到esam密钥信息文件 4个字节， 放到局部变量：Esam_Password_Info中
	Get_File_Data(ESAM,ESAM_PASSWORD_INF_FILE,0,4,Esam_Password_Info); 
        //得到cpu卡的指令信息文件的密钥信息，Card_WR_Buff在上面的函数中，文件数据被放到这个缓冲，文件结构已经为包括了开头和结尾标示
        mem_cpy( &File_Point,Card_WR_Buff,sizeof(struct Password_Inf_File),&File_Point,sizeof(struct Password_Inf_File) );
        mem_cpy(Cpu_Password_Info,File_Point.Password_Info,4, Cpu_Password_Info,4);
          
	PassWord_Kind = File_Point.Order_Byte; //密钥类型,密钥下装卡， 还是密钥恢复卡
       //判断cpu卡的值是否正确
	if( PassWord_Kind == GWFAR_MOD_PASSWORD_CARD )//如果为密钥下装卡
	{       //这样写没什么意义，因为下装后，再下装时，身份验证通不过
		if( File_Point.Password_Info[3] <= Esam_Password_Info[3] )//密钥下装卡中  密钥版本 
		{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Password_State_Err=1;
			  return ERR;
		}
	}
	else if(  PassWord_Kind== GWFAR_RES_PASSWORD_CARD )
        {
		if(  File_Point.Password_Info[3] != 0 )/// 如果 密钥修复卡中 密钥版本 不为0
		{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Password_State_Err=1;
			  return ERR;
		}
        }
        
        // // 密钥更新//// ");
       // 密钥更新////
	if( PassWord_Updata( File_Point.Order_Byte ) != OK )
		return ERR;
          //"//esam密钥状态更新// " );
         //esam密钥状态更新//
	if(Write(0,Update_Binary,0x80+ESAM_PASSWORD_INF_FILE,0,4,(unsigned char *) &Cpu_Password_Info[0])!=OK)
	{
		return ERR;
	}
         // " 计数器减1//");
        //"计数器减1//
	Temp--;
	My_memcpyRev(Card_WR_Buff,(unsigned char *)&Temp,  4);
	CPU_ESAM_CARD_Control(CPU);
	if(Write(0,Update_Record,0x01,0x14,0x04,Card_WR_Buff)!=OK)
	{
		return ERR;
	}
        //// 保存用的是 密钥恢复卡，还是密钥下装卡 ");
        // 保存用的是 密钥恢复卡，还是密钥下装卡//该变量只有在这里修改，是用来做编程记录的
	Pre_Payment_Para.PassWord_Kind=PassWord_Kind;////密钥类型,密钥下装卡， 还是密钥恢复卡
         if(Write_Storage_Data(_SDI_PREPAID_PSW_KIND , &Pre_Payment_Para.PassWord_Kind ,1) );
	return OK;
}
       
unsigned char Add_Money_Card(void){//增加电费卡
  
	struct Moneybag_Data Moneybag_Data;
	struct Add_Money_Para_Inf_File  File; //cpu卡 指令信息文件
        //读取esam钱包文件,并反相，
	Read_Esam_Moneybag_File( ( unsigned char * )&Moneybag_Data );
	Moneybag_Data.Buy_Count++;//使购电次数+1
        //保存cpu卡二进制信息文件
        mem_cpy(&File,Card_WR_Buff,sizeof( struct Add_Money_Para_Inf_File ) ,&File , sizeof( struct Add_Money_Para_Inf_File ));
	//更新cpu卡的购电次数
	My_memcpyRev((unsigned char *)&(File.Buy_Money_Count), (unsigned char *)&(Moneybag_Data.Buy_Count), 4);
	File.Add_CS=Cal_Add_CS(&File.Order_Byte,LENGTH_ADD_MONEY_PARA_INF_FILE-3);//修改效验和
	CPU_ESAM_CARD_Control(CPU);
	if(Write(0,Update_Binary,0x81,0,LENGTH_ADD_MONEY_PARA_INF_FILE,&File.Start_Byte)!=OK){//末尾标志 不变
		return ERR;
	}
        
	Reverse_data( (unsigned char *)&(File.Buy_Money),4 ); 
	Reverse_data( (unsigned char *)&(File.Buy_Money_Count),4 );//前面已经反相了这里为什么要反相， 这里可能 有问题
        // 判断本次购电的囤积门限  //
	if( Check_Buy_Money_Exceed_Limit( File.Buy_Money) ){//Moneybag_Data.Remain_Money来自cpu卡
                           ASSERT_FAILED();
			   Card_Error_State.CardErrorState.MoneyLimitErr=1;
			   return ERR;
	}
        // 1 , 4,0   把cpu卡的指令信息文件中，要充值的钱 加到esam中去
	if( Remain_Money_Moneybag_Add(ADD_MONEY_CARD_ORDER_INF_FILE,BUY_MONEY_CARD,0) != OK )
	{
		   Card_Error_State.CardErrorState.ESAM_DO_ERR=1;
		   return ERR;
	}
//告诉黄工， 充值了， 冲了多少钱
	Meter_Money_And_Count_Updata(File.Buy_Money,File.Buy_Money_Count );
	return OK;
}
//根据 和黄工的约定，存放在e方中表号pDst[0]应该为 开发套件软件上看到得表地址最右边的一个字节
unsigned char Modify_MeterID_Card(void){// 表号设置卡
  	unsigned char i,Msb,Ctrl;
	struct MeterID_Return_Inf_File MeterID_Return_Inf_File;//表号设置卡的返写信息文件,记录了当前要设置的表号
	struct MeterID_Para_Inf_File   File;//表号设置卡的指令信息文件，记录了表号设置的范围
	
	if( !Check_Meter_Prog_Status() ){ 
		Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err=1;  
		return ERR;
	}
        mem_cpy(&File,Card_WR_Buff,sizeof(struct MeterID_Para_Inf_File),&File,sizeof(struct MeterID_Para_Inf_File) );
        
        /*" 判断表号是否在合理范围内 "*/
        
	if( Read(0,Read_Binary,0x80+METERID_CARD_RETURN_FILE,0,LENGTH_METERID_RETURN_INF_FILE) != OK )
		return ERR;
	My_Memcpy((unsigned char *) &MeterID_Return_Inf_File, receive_send_buffer, LENGTH_METERID_RETURN_INF_FILE);
        //如果要设置的 表号，比最后一个表号大， 那么错误，函数结束 ,注意:BcdMeterID【0】为高位，BcdMeterID【5】为低位
	if( My_Memcmp(&(MeterID_Return_Inf_File.Next_Meter_ID[0]),&(File.End_Meter_ID[0]) ,6)  == 1 )
	{
                  ASSERT_FAILED();
		  Card_Error_State.CardErrorState.Meter_Id_Set_Card_Id_Is_FULL_Err=1;
		  return ERR;
	}  
        // 更新ESAM表号 //
	if( Esam_File_Updata(METERID_CARD_RETURN_FILE,
							ESAM_PARA_INF_FILE,
							NEXT_METER_ID_METERID,
							METER_ID_ESAM,
							6,
							0) != OK )
		return ERR;
        //  更新表计表号  //如果发卡软件中写的是010203040506，那么下面Pre_Payment_Para.BcdMeterID【0】就为01
         My_memcpyRev( Pre_Payment_Para.BcdMeterID,&(MeterID_Return_Inf_File.Next_Meter_ID[0]),6);
         Write_Storage_Data( SDI_METER_ID, Pre_Payment_Para.BcdMeterID , 6);
         Card_Set_Para_Notice() ;
/*" 更新卡回写文件 "*/
	Msb = 0;
        //表号+1
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
	MeterID_Return_Inf_File.Add_CS++;//效验和+1
	CPU_ESAM_CARD_Control(CPU);
        //更新cpu卡返写信息文件， 用来设置的表号变量 保存在该文件中，该变量已被减1 
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
    
//远程 和 本地  每隔60分钟对 esam 扣款 
void UpdataEsamMoneyBag(void)
{
  static S_Int8U Mins = {CHK_BYTE, 0xF0, CHK_BYTE};// 静态局部变量，这样写，不会总是被赋值
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U Re;
  //ASSERT_FAILED();
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Mins);
  Re &= CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(Re EQ 1);
  //假如 过了一分钟   继续
  if(Min_Bak.Var EQ Cur_Time1.Min)
    return;
  
  Min_Bak.Var = Cur_Time1.Min;
  ++Mins.Var;
  //每60分钟刷新一次Esam
  if(Mins.Var >= 60) 
  {
      Mins.Var = 0;
      
  }else{
    return ;
  }  
  

  //开始更新esam
  if(Chk_Pay_Time_Arrive())//假如远程身份认证时间 过了 ， 也就是，没有远程操作时 
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
       //预付费功能打开且是本地预付费表  预付费功能打开且是本地预付费表 

       Esam_Remain_Money_Dec();
       Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,receive_send_buffer,receive_send_buffer,Length_receive_send_buffer );
     }
  }else 
  {//假如是在 远程控制的时候 预付费功能打开且是本地预付费表 
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)//
    {
       Esam_Remain_Money_Dec();
    }  
  }
  return ;
}