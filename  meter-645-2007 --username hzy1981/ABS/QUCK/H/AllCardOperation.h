#ifndef ALL_CARD_OPERATION_H__
#define ALL_CARD_OPERATION_H__

#undef EXT
#ifdef ALL_CARD_OPERATION_C_
#define EXT
#else
#define EXT extern
#endif

//来自 ICcard.h
INT8U ICcardMain(void);
INT8U ICcardProcess(void);
void CardProgrammeEvent(void);
INT16U ProgrammeEvent(INT32U progman,INT32U progdata);
// 判断文件数据结构的帧头帧尾和效验和是否合法 "
INT8U Frame_Judge(INT8U * Point,INT8U length);
/*"计算累加效验和 "*/
INT8U Cal_Add_CS(INT8U * Point,INT8U L);
INT8U Check_Card(void);
INT8U Field_Para_Set_Card(void);//现场参数设置卡
void Deal_Set_Para_Inf_File(INT8U * Source_Point,INT8U Mode);
INT8U Relay_TEST_Card(void);
INT8U Set_In_Card(void);
INT8U Password_Card(void);
INT8U Add_Money_Card(void);
INT8U Modify_MeterID_Card(void);
 void Relay_Deal(INT8U Flag);
void Deal_Init_Para_Inf_File(INT8U * Source_Point,INT8U Mode);
void Deal_Para_Table2(INT8U * Source_Point );
void Deal_Para_Table4(INT8U * Source_Point );
void Deal_Para_Table3(INT8U * Source_Point );
///给黄工调用的函数， 定时扣款
void UpdataEsamMoneyBag(void);
//////
//ICcard.h
//------------------------------------------
 
 
 
/*" 国网远程预付费卡类型 "*/
#define GWFAR_USER_CARD                   0x01       // 用户卡  
	#define  GWFAR_USER_CARD_NEW    	0x01	// 新卡  
	#define  GWFAR_USER_CARD_BUY		0x02	// 购电卡  
	#define  GWFAR_USER_CARD_BACK		0x03	//补卡  

#define GWFAR_MOD_PASSWORD_CARD           0x02       //密钥下装卡 
#define GWFAR_RES_PASSWORD_CARD           0x03       // 密钥恢复卡   
#define GWFAR_PARA_SET_CARD               0x04       //现场参数设置卡  
#define GWFAR_READ_ESAM_CARD              0x05       //ESAM数据回抄卡  
#define GWFAR_INIT_CARD                   0x06       // 参数预置卡
#define GWFAR_MOD_METERID_CARD            0x07       /// 表号设置卡  
#define GWFAR_ADDD_MONEY_CARD            0x08      //增加电费卡  
#define GWFAR_RELAY_TEST_CARD            0x09       // 继电器测试卡  

//---
#define UN_TYPE_CARD 				0x00
#define NEW_CARD 						0x01
#define BUY_CARD 						0x02
#define FILL_CARD 						0x03  
#define USER_CHANGE_CARD 	0x04
#define DELUSE_CARD 				0x05
#define CHECK_CARD 					0x06
#define TRIFF_CARD 					0x07
#define RELAY_CARD 					0x08
#define SET_IN_CARD					0x09
#define PASSWORD_CARD 			0x10
#define CHANGE_CARD 				0x11
#define ADD_MONEY_CARD 		0x12
#define MOD_METERID_CARD	0X13

#define Card_Display_Card    	0x00
#define Card_Display_Good   	0x01
#define Card_Display_Err      	0x02
#define Card_Display_Money 	0x03

#define SEL_ESAM						ESAM
#define SEL_CPU							CPU
//#define GOOD 								CPU_CARD_SUCCESS	//0x00EE
#define PRE_DISP_LIMIT			10000000000

#define CARD_BACK_USER_SEL			1
#define CARD_BACK_CHECK_SEL		2
#define CARD_BACK_CHANGE_SEL	3
//#define CARD_BACK_USER_LEN		18
//#define CARD_BACK_CHECK_LEN		27
//#define CARD_BACK_CHANGE_LEN	17

//---
#define NEW_CARD_CODE						0xFFFFFF80+NEW_CARD
#define BUY_CARD_CODE						0xFFFFFF80+BUY_CARD
#define FILL_CARD_CODE 						0xFFFFFF80+FILL_CARD  
#define DELUSE_CARD_CODE 				0xFFFFFF80+DELUSE_CARD
#define USER_CHANGE_CARD_CODE 	0xFFFFFF80+USER_CHANGE_CARD
#define TRIFF_CARD_CODE 					0xFFFFFF80+TRIFF_CARD
#define SET_IN_CARD_CODE					0xFFFFFF80+SET_IN_CARD
#define CHANGE_CARD_CODE 				0xFFFFFF80+CHANGE_CARD
#define BASE_MONEY_ID									0x04000401	//
#define HIRE_MONEY_ID									0x04000402	//
#define REMAIN_MONEY_ALARM1_LIMIT_ID	0x04001001
#define REMAIN_MONEY_ALARM2_LIMIT_ID	0x04001002
#define REMAIN_MONEY_TICK_LIMIT_ID		0x04001003
#define REMAIN_MONEY_HOARD_LIMIT_ID	0x04001004
#define OVERPOWER_PLUS_LIMIT_ID				0x04001010
#define POWER_PERIOD_ID								0x04001011
#define OVERPOWER_TIME_LIMIT_ID				0x04001012
#define TRIFF1_ID												0x04050101
#define TRIFF2_ID												0x04050201
#define C_T_ID														0x04000306
#define P_T_ID														0x04000307
#define SYSID_ID													0x04000501	//
#define USERID_ID												0x04000502	//
#define METERID_ID											0x04000503	//
#define CARDID_ID												0x04000504	//
#define TRIFFSWITCHDATE_ID							0x04000108
#define STEPSWITCHDATE_ID							0x04000109
#define METER_RUN_STATE_ID						0x04000601	//
#define MONEY_POINT_ID									0x04000701	//
#define BUY_COUNT_ID										0x04000602	//
#define STEP_NUM_ID											0x04000207
#define ENERGY_STEP1_ID								0x04060001
#define ENERGY_STEP2_ID								0x04060101
#define TRIFF_STEP1_ID									0x04060201
#define TRIFF_STEP2_ID									0x04060301
#define PAY_FOR_USERS_FLAG1_ID				0x04000810
#define PAY_FOR_USERS_FLAG2_ID				0x04000811
#define PAY_FOR_USERS_FLAG3_ID				0x04000812
#define PAY_FOR_USERS_FLAG4_ID				0x04000813
#define PAY_FOR_USERS_FLAG5_ID				0x04000814
#define PAY_FOR_USERS_FLAG11_ID				0x04000803
#define PAY_FOR_USERS_FLAG12_ID				0x04000815
#define TRIFF_TABLE1_ID									0x04050001
#define ENERGY_STEP_TABLE1_ID					0x04050102
#define ENERGY_STEP_TABLE2_ID					0x04060102
#define TRIFF_STEP_TABLE1_ID						0x04050101
#define TRIFF_STEP_TABLE2_ID						0x04060101
#define OPENSWITCHDELAYTIME_ID				0x0E00010D
#define CLOSESWITCHDELAYTIME_ID				0x0E00010E
#define YEARSLOTNUMBLE_ID							0x04000201
#define DAILYSLOTTABLENUMBLE_ID				0x04000202
#define DAILYSLOTNUMBLE_ID							0x04000203
#define WEEKENDTABLE_ID								0x04000802
#define YEARTABLE_ID										0x04010000
#define DAYTABLE_ID											0x04010001
#define HOLIDAY_ID											0x04030001
#define YEARSLOTNUMBLE2_ID							0x0E000211
#define DAILYSLOTTABLENUMBLE2_ID			0x0E000212
#define DAILYSLOTNUMBLE2_ID						0x0E000213
#define WEEKENDTABLE2_ID								0x0E000216
#define YEARTABLE2_ID										0X04020000
#define DAYTABLE2_ID										0X04020001

//----
#define IC_GET_PLUS_REMAIN					0x01
#define IC_GET_NEGA_REMAIN				0x02
#define IC_GET_PLUS_ACTIVE					0x03
#define IC_GET_ENERGY_RECORD			0x04
#define IC_GET_ALARM_LIMIT					0x05
#define IC_GET_ZERO									0x10

//#define PRE_MONEY_POINT			Pre_Payment_Para.Money_Point
//#define TRIFF_P					Pre_Payment_Para.Curr_Triff_Point
//#define TRIFF_BAK_P			((Pre_Payment_Para.Curr_Triff_Point+1)&0x01)

#ifndef activem
#define activem		Meter_Parameter.MeterMode[1].bit.b2  /*"有功正加反模式字"*/
#endif

 
#define DISP_SIGN_FLAG_DEFINE  		ICcard_Flag1.bit.DISP_SIGN_FLAG
#define DISP_MONEY_FLAG_DEFINE  		ICcard_Flag1.bit.DISP_MONEY_FLAG
#define DISP_PLUS_FLAG_DEFINE  		ICcard_Flag1.bit.DISP_PLUS_FLAG
#define DISP_NEGA_FLAG_DEFINE  		ICcard_Flag1.bit.DISP_NEGA_FLAG
#define DISP_MYRIAD_FLAG_DEFINE  	ICcard_Flag1.bit.DISP_MYRIAD_FLAG
//#define 
//#define 
//#define 

struct CardErrId
{
	INT16U oldID;
	INT8U newID;
};
#define CARDERRID_LENGTH  sizeof(struct CardErrId)
union Long_To_Char
    {
    INT32U U_long;
    INT16U U_int[2];
    INT8U U_char[4];
    };
//-----------------------------------------------------
struct USECARD_INFOR_FILE
{
	INT8U Start;
	INT8U Command;
	INT8U Len;
	INT8U syeID[2];
	INT8U userID[5];
	INT8U meterID[5];
	INT8U cardID;
	INT32U triff[4];
	INT32U triffBottom[4];
	INT32U moneyLimit[2];
	INT32U moneyHoard;
	INT8U overPowerPlusLimit[3];
	INT8U powerPeriod;
	INT8U overPowerSwTimeLimit;
	INT8U overPowerOpenSwTime;
	INT8U overPowerCloseSwTime;
	INT8U buyTime[6];
	INT8U triffSwitchDate[4];
	INT8U	Cs;
	INT8U End;
};

struct PARACARD_INFOR_FILE
{
  	INT8U Start;
	INT8U Command;
	INT8U Len;
	INT8U sysID[2];
	INT8U userID[5];
	INT8U meterID[5];
	INT8U cardID;
	INT32U triff[4];
	INT32U moneyLimit[2];
	INT32U moneyHoard;
	INT8U overPowerPlusLimit[3];
	INT8U powerPeriod;
	INT8U overPowerSwTimeLimit;
	INT8U overPowerOpenSwTime;
	INT8U overPowerCloseSwTime;
	INT8U triffSwitchDate[4];
	INT8U Cs;
	INT8U End;
};

struct RIFFCARD_TIMEZONE_FILE
{
	INT8U Start;
	INT8U Command;
	INT8U Len;
	INT8U yearSlotNumble;
	INT8U yearTable[4][4];
	INT8U dailySlotTableNumble;
	INT8U dayTable[4][12][3];
	INT8U holiday[13][3];
	INT8U weekEndTable;
	INT8U Cs;
	INT8U End;
};

struct ADDCARD_COMMAND_FILE
{
	INT8U Start;
	INT8U Command;
	INT8U Len;
	INT8U userID[5];
	INT32S               buyMoney;
	INT16U    buyCount;
	INT8U Cs;
	INT8U End;
};

struct CHANGE_INIT_FILE1
{
	INT8U Start;
	INT8U Command;
	INT8U Len;
	INT8U userID[5];
	INT8U oldMeterID[5];
	INT8U newMeterID[5];
	INT8U meterRunstate;
	INT8U Cs;
	INT8U End;
};

struct CHANGE_INIT_FILE2
{
	INT8U Start;
	INT8U Command;
	INT8U Len;
	INT8U sysID[2];
	INT8U userID[5];
	INT8U meterID[5];
	INT8U cardID;
	INT32U triff[4];
	INT32U moneyLimit[2];
	INT32U moneyHoard;
	INT8U overPowerPlusLimit[3];
	INT8U powerPeriod;
	INT8U overPowerSwTimeLimit;
	INT8U overPowerOpenSwTime;
	INT8U overPowerCloseSwTime;
	INT8U triffSwitchDate[4];
	INT8U Cs;
	INT8U End;
};

struct CHANGE_INIT_FILE3
{
	INT8U Start;
	INT8U Command;
	INT8U Len;
		INT32S remainMoney;
	INT32U totalBuyMoney;
	INT32U buyMoney;
	INT16U   	buyCount;
	INT32U triffEnergy[5];
	INT32U tickMoney;
	INT32U lastMonthFreezeEnergy;
	INT32U moneyLimit[2];
	INT32U moneyHoard;
	INT8U overPowerPlusLimit[3];
	INT8U powerPeriod;
	INT8U overPowerSwTime;
	INT8U unlawfulCardCount;
	INT8U Cs;
	INT8U End;	  
};

//---back write---
struct User_Back_Infor
{
		INT32S remainMoney;
	INT32U totalBuyMoney;
	INT32U lastBuyMoney;
	INT16U 	buyCount;
	INT32U triffEnergy[5];
	INT32U overZeroMoney;
	INT32U lastMonthFreezeEnergy;
	INT32U moneyLimit[2];
	INT32U moneyHoard;
	INT8U overPowerPlusLimit[3];
	INT8U powerPeriod;
	INT8U overPowSwTime;
	INT8U unlawfulCardCount;
};

struct Check_Back_Infor
{
	INT8U sysID[2];
	INT8U userID[5];
	INT8U meterID[5];
		INT32S remainMoney;
	INT32U totalBuyMoney;
	INT32U lastBuyMoney;
	INT16U 	buyCount;
	INT32U triffEnergy[5];
	INT32U triff[4];
	INT32U overZeroMoney;
	INT32U lastMonthFreezeEnergy;
	INT32U moneyLimit[2];
	INT32U moneyHoard;
	INT8U overPowerPlusLimit[3];
	INT8U powerPeriod;
	INT8U overPowSwTime;
	INT8U unlawfulCardCount;
	INT8U meterStatus;
	INT8U writeBackTime[6];
};


#endif