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
unsigned int CardProgrammeEvent(void);
unsigned int ProgrammeEvent(unsigned long progman,unsigned long progdata);
// 判断文件数据结构的帧头帧尾和效验和是否合法 "
unsigned char Frame_Judge(unsigned char * Point,unsigned char length);
/*"计算累加效验和 "*/
unsigned char Cal_Add_CS(unsigned char * Point,unsigned char L);
unsigned char Check_Card(void);
unsigned char Field_Para_Set_Card(void);//现场参数设置卡
void Deal_Set_Para_Inf_File(unsigned char * Source_Point,unsigned char Mode);
unsigned char Relay_TEST_Card(void);
unsigned char Set_In_Card(void);
unsigned char Password_Card(void);
unsigned char Add_Money_Card(void);
unsigned char Modify_MeterID_Card(void);
 void Relay_Deal(unsigned char Flag);
void Deal_Init_Para_Inf_File(unsigned char * Source_Point,unsigned char Mode);
void Deal_Para_Table2(unsigned char * Source_Point );
void Deal_Para_Table4(unsigned char * Source_Point );
void Deal_Para_Table3(unsigned char * Source_Point );
///给黄工调用的函数， 定时扣款
void UpdataEsamMoneyBag(void);
//////
//ICcard.h
//------------------------------------------
 
 
 
/*" 国网远程预付费卡类型 "*/
#define GWFAR_USER_CARD                   0x01       /*" 用户卡 "*/
	#define  GWFAR_USER_CARD_NEW    	0x01	/*" 新卡 "*/
	#define  GWFAR_USER_CARD_BUY		0x02	/*" 购电卡 "*/
	#define  GWFAR_USER_CARD_BACK		0x03	/*" 补卡 "*/

#define GWFAR_MOD_PASSWORD_CARD           0x02       /*" 修改密钥卡 "*/
#define GWFAR_RES_PASSWORD_CARD           0x03       /*" 恢复密钥卡 "*/
#define GWFAR_PARA_SET_CARD               0x04       /*" 参数设置卡 "*/
#define GWFAR_READ_ESAM_CARD              0x05       /*" ESAM数据回抄卡 "*/
#define GWFAR_INIT_CARD                   0x06       /*" 出厂设置卡 "*/
#define GWFAR_MOD_METERID_CARD            0x07       /*" 表号设置卡 "*/
#define GWFAR_ADDD_MONEY_CARD            0x08       /*" 增加电费卡 "*/
#define GWFAR_RELAY_TEST_CARD            0x09       /*" 继电器测试卡 "*/

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
	unsigned int oldID;
	unsigned char newID;
};
#define CARDERRID_LENGTH  sizeof(struct CardErrId)
union Long_To_Char
    {
    unsigned long U_long;
    unsigned int U_int[2];
    unsigned char U_char[4];
    };
//-----------------------------------------------------
struct USECARD_INFOR_FILE
{
	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
	unsigned char syeID[2];
	unsigned char userID[5];
	unsigned char meterID[5];
	unsigned char cardID;
	unsigned long triff[4];
	unsigned long triffBottom[4];
	unsigned long moneyLimit[2];
	unsigned long moneyHoard;
	unsigned char overPowerPlusLimit[3];
	unsigned char powerPeriod;
	unsigned char overPowerSwTimeLimit;
	unsigned char overPowerOpenSwTime;
	unsigned char overPowerCloseSwTime;
	unsigned char buyTime[6];
	unsigned char triffSwitchDate[4];
	unsigned char	Cs;
	unsigned char End;
};

struct PARACARD_INFOR_FILE
{
  	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
	unsigned char sysID[2];
	unsigned char userID[5];
	unsigned char meterID[5];
	unsigned char cardID;
	unsigned long triff[4];
	unsigned long moneyLimit[2];
	unsigned long moneyHoard;
	unsigned char overPowerPlusLimit[3];
	unsigned char powerPeriod;
	unsigned char overPowerSwTimeLimit;
	unsigned char overPowerOpenSwTime;
	unsigned char overPowerCloseSwTime;
	unsigned char triffSwitchDate[4];
	unsigned char Cs;
	unsigned char End;
};

struct RIFFCARD_TIMEZONE_FILE
{
	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
	unsigned char yearSlotNumble;
	unsigned char yearTable[4][4];
	unsigned char dailySlotTableNumble;
	unsigned char dayTable[4][12][3];
	unsigned char holiday[13][3];
	unsigned char weekEndTable;
	unsigned char Cs;
	unsigned char End;
};

struct ADDCARD_COMMAND_FILE
{
	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
	unsigned char userID[5];
	long               buyMoney;
	unsigned int    buyCount;
	unsigned char Cs;
	unsigned char End;
};

struct CHANGE_INIT_FILE1
{
	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
	unsigned char userID[5];
	unsigned char oldMeterID[5];
	unsigned char newMeterID[5];
	unsigned char meterRunstate;
	unsigned char Cs;
	unsigned char End;
};

struct CHANGE_INIT_FILE2
{
	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
	unsigned char sysID[2];
	unsigned char userID[5];
	unsigned char meterID[5];
	unsigned char cardID;
	unsigned long triff[4];
	unsigned long moneyLimit[2];
	unsigned long moneyHoard;
	unsigned char overPowerPlusLimit[3];
	unsigned char powerPeriod;
	unsigned char overPowerSwTimeLimit;
	unsigned char overPowerOpenSwTime;
	unsigned char overPowerCloseSwTime;
	unsigned char triffSwitchDate[4];
	unsigned char Cs;
	unsigned char End;
};

struct CHANGE_INIT_FILE3
{
	unsigned char Start;
	unsigned char Command;
	unsigned char Len;
		signed long remainMoney;
	unsigned long totalBuyMoney;
	unsigned long buyMoney;
	unsigned int   	buyCount;
	unsigned long triffEnergy[5];
	unsigned long tickMoney;
	unsigned long lastMonthFreezeEnergy;
	unsigned long moneyLimit[2];
	unsigned long moneyHoard;
	unsigned char overPowerPlusLimit[3];
	unsigned char powerPeriod;
	unsigned char overPowerSwTime;
	unsigned char unlawfulCardCount;
	unsigned char Cs;
	unsigned char End;	  
};

//---back write---
struct User_Back_Infor
{
		signed long remainMoney;
	unsigned long totalBuyMoney;
	unsigned long lastBuyMoney;
	unsigned int 	buyCount;
	unsigned long triffEnergy[5];
	unsigned long overZeroMoney;
	unsigned long lastMonthFreezeEnergy;
	unsigned long moneyLimit[2];
	unsigned long moneyHoard;
	unsigned char overPowerPlusLimit[3];
	unsigned char powerPeriod;
	unsigned char overPowSwTime;
	unsigned char unlawfulCardCount;
};

struct Check_Back_Infor
{
	unsigned char sysID[2];
	unsigned char userID[5];
	unsigned char meterID[5];
		signed long remainMoney;
	unsigned long totalBuyMoney;
	unsigned long lastBuyMoney;
	unsigned int 	buyCount;
	unsigned long triffEnergy[5];
	unsigned long triff[4];
	unsigned long overZeroMoney;
	unsigned long lastMonthFreezeEnergy;
	unsigned long moneyLimit[2];
	unsigned long moneyHoard;
	unsigned char overPowerPlusLimit[3];
	unsigned char powerPeriod;
	unsigned char overPowSwTime;
	unsigned char unlawfulCardCount;
	unsigned char meterStatus;
	unsigned char writeBackTime[6];
};


#endif