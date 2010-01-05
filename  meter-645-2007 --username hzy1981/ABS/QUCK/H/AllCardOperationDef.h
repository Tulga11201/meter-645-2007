#ifndef ALL_CARD_OPERATION_DEF_H__
#define ALL_CARD_OPERATION_DEF_H__
//来自Card_File.h文件
#undef EXT
#ifdef ALL_CARD_OPERATION_C__
#define EXT
#else
#define EXT extern
#endif
#define MeterRunState_Run_3  3
#define MeterRunState_Test_0  0
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 每张卡定义的文件名以及位置，密钥位置 "*/
/*" ESAM文件定义 "*/
#define ESAM_MONEYBAG_FILE		0x01
#define ESAM_PARA_INF_FILE		0x02
#define ESAM_TRIFF_1_FILE			0x03
#define ESAM_TRIFF_2_FILE			0x04
#define ESAM_PASSWORD_INF_FILE			0x05
#define ESAM_FAR_PASSWORD_INF_FILE		0x06
#define ESAM_RUN_INF_FILE			0x07
#define ESAM_CONTROL_ORDER_FILE			0x08
#define ESAM_PARA_UPDATA_FILE1			0x09
#define ESAM_PARA_UPDATA_FILE2			0x10
#define ESAM_PARA_UPDATA_FILE3			0x11
#define ESAM_PARA_UPDATA_FILE4			0x12
#define ESAM_PARA_UPDATA_FILE5			0x13
/*" 用户卡定义 "*/
#define USER_CARD_PARA_INF_FILE			0x01
#define USER_CARD_MONEYBAG_FILE			0x02
#define USER_CARD_TRIFF_1_FILE			0x03
#define USER_CARD_TRIFF_2_FILE			0x04
#define USER_CARD_RUN_INF_FILE			0x05
/*" 密钥下装/恢复卡定义 "*/
#define PASSWORD_CARD_INF_FILE			0x01
#define PASSWORD_CARD_COUNTER_FILE		0x02
#define PASSWORD_CARD_PASS_FILE			0x03
/*" 现场参数设置卡定义 "*/
#define PARA_SET_CARD_PARA_INF_FILE		0x01
#define PARA_SET_CARD_TRIFF_1_FILE		0x02
#define PARA_SET_CARD_TRIFF_2_FILE		0x03
#define PARA_SET_CARD_COUNTER_FILE		0x04
/*" ESAM数据回抄卡定义 "*/
#define ESAM_BACK_ORDER_INF_FILE			0x01
#define ESAM_BACK_MONEYBAG_FILE				0x02
#define ESAM_BACK_PARA_INF_FILE				0x03
#define ESAM_BACK_TRIFF_1_FILE				0x04
#define ESAM_BACK_TRIFF_2_FILE				0x05
#define ESAM_BACK_PASSWORD_INF_FILE			0x06
#define ESAM_BACK_FAR_PASSWORD_INF_FILE		0x07
#define ESAM_BACK_RUN_INF_FILE				0x08
/*" 预制卡卡定义 "*/
#define INIT_CARD_PARA_INF_FILE				0x01
#define INIT_CARD_MONEYBAG_FILE				0x02
#define INIT_CARD_TRIFF_1_FILE				0x03
#define INIT_CARD_TRIFF_2_FILE				0x04
/*" 表号设置卡定义 "*/
#define METERID_CARD_ORDER_INF_FILE			0x01
#define METERID_CARD_RETURN_FILE				0x02
/*" 增加电费卡定义 "*/
#define ADD_MONEY_CARD_ORDER_INF_FILE		0x01
/*" 继电器测试卡定义 "*/
#define RELAY_TEST_CARD_ORDER_INF_FILE		0x01
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 费率信息文件1 "*/
struct Triff_Data
	{
	unsigned long Triff[63];
	};
#define LENGTH_TRIFF_DATA  sizeof(struct Triff_Data)
	#define TRIFF_CPU    4
/*" 钱包信息数据 "*/
struct Moneybag_Data
	{
	unsigned long Remain_Money;
	unsigned long Buy_Count;
	};
#define LENGTH_MONEYBAG_DATA  sizeof(struct Moneybag_Data)
	#define REMAIN_MONEY_CPU_ESAM			0
	#define BUY_COUNT_CPU_ESAM				REMAIN_MONEY_CPU+4
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 参数设置共用数据结构集合 "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 参数卡共用数据1 "*/
struct Para_Table1
	{
	unsigned char Card_Kind;                 /*" 电卡类型 "*/
	unsigned char Client_ID[6];              /*" 客户编号 "*/
	unsigned char Meter_ID[6];               /*" 表号 "*/
	};
#define LENGTH_PARA_TABLE1  sizeof(struct Para_Table1)
/*" 参数卡共用数据2 "*/
struct Para_Table2
	{
	unsigned char User_Kind;                  /*" 用户类型 "*/
	unsigned char Para_UpData_Flag;          /*" 参数更新标志位 "*/
	};
#define LENGTH_PARA_TABLE2  sizeof(struct Para_Table2)
/*" 参数卡共用数据3 "*/
struct Para_Table3
	{
	unsigned long Remain_Money_Alarm1_Limit; /*" 报警金额1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" 报警金额2 "*/
	unsigned char Current_CT[3];             /*" 电流互感器变比 "*/
	unsigned char Voltage_PT[3];             /*" 电压互感器变比 "*/
	};
#define LENGTH_PARA_TABLE3  sizeof(struct Para_Table3)
/*" 参数卡共用数据4 "*/
struct Para_Table4
	{
	unsigned char Triff_Switch_Time[5];      /*" 两套分时费率切换时间 "*/
	};
#define LENGTH_PARA_TABLE4  sizeof(struct Para_Table4)
/*" 参数卡共用数据5 "*/
struct Para_Table5
	{
	unsigned long Para_Card_Version;      /*" 现场参数设置卡版本号 "*/
	};
#define LENGTH_PARA_TABLE5  sizeof(struct Para_Table5)
/*" 参数卡共用数据6 "*/
struct Para_Table6
	{
	unsigned int  Identity_Auth_Time;       /*" 身份认证时效 "*/
	};
#define LENGTH_PARA_TABLE6  sizeof(struct Para_Table6)
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 运行数据 "*/
/*" 回写数据,给用户卡，ESAM用 1ss"*/
struct Run_Inf_Data
	{	
         unsigned char temp;	//用来字节对齐，因为Remain_Money必须放在一个额数位置，
	unsigned char User_Kind;					/*" 用户类型 "*/
	unsigned char Current_CT[3];				/*" 电流互感器变比 "*/
	unsigned char Voltage_PT[3];				/*" 电压互感器变比 "*/	
	unsigned char Meter_ID[6];					/*" 表号 "*/
	unsigned char Client_ID[6];				/*" 客户编号 "*/
	
        unsigned long Remain_Money;				/*" 剩余金额 "*/
	unsigned long Buy_Count;					/*" 购电次数 "*/
	unsigned long Low_Zero_Money;				/*" 过零金额 "*/
	unsigned char Password_Info[4];			/*" 1，包括：状态，方式，条数，版本 "*/
	unsigned char Unlawful_Card_Count[3];		/*" 非法卡插入次数 "*/
	unsigned char Return_DT[5];				/*" 返写日期时间 "*/
	};
#define LENGTH_RUN_INF_DATA  sizeof(struct Run_Inf_Data)
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 文件对应数据结构 "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
// ESAM文件数据结构 ,也指令信息文件或则参数信息文件
struct Esam_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" 用户类型 "*/
	unsigned char Para_UpData_Flag;          /*" 参数更新标志位 "*/
	unsigned long Para_Card_Version;      /*" 现场参数设置卡版本号 "*/
	unsigned char Triff_Switch_Time[5];      /*" 两套分时费率切换时间 "*/
	unsigned char No_Use;                      /*" 保留 "*/
	unsigned long Remain_Money_Alarm1_Limit; /*" 报警金额1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" 报警金额2 "*/
	unsigned char Current_CT[3];             /*" 电流互感器变比 "*/
	unsigned char Voltage_PT[3];             /*" 电压互感器变比 "*/
	unsigned char Meter_ID[6];               /*" 表号 "*/
	unsigned char Client_ID[6];              /*" 客户编号 "*/
	unsigned char Card_Kind;                 /*" 电卡类型 "*/
	unsigned int  Identity_Auth_Time;       /*" 身份认证时效 "*/
	};
#define LENGTH_ESAM_PARA_INF_FILE  sizeof(struct Esam_Para_Inf_File)
	#define  ESAM_PARA_INF_FILE_ESAM		4
	#define  USER_KIND_ESAM			ESAM_PARA_INF_FILE_ESAM	/*" 用户类型 "*/
	#define  PARA_UPDATA_FLAG_ESAM		USER_KIND_ESAM+1/*" 参数更新标志位 "*/
	#define  PARA_CARD_VERSION_ESAM		PARA_UPDATA_FLAG_ESAM+1	/*" 现场参数设置卡版本号 "*/
	#define  TRIFF_SWITCH_TIME_ESAM		PARA_CARD_VERSION_ESAM+4/*" 两套分时费率切换时间 "*/
	#define  NO_USE_ESAM				TRIFF_SWITCH_TIME_ESAM+5 /*" 保留 "*/
	#define  REMAIN_MONEY_ALARM1_LIMIT_ESAM		NO_USE_ESAM+1	/*" 报警金额1 "*/
	#define  REMAIN_MONEY_ALARM2_LIMIT_ESAM		REMAIN_MONEY_ALARM1_LIMIT_ESAM+4/*" 报警金额2 "*/
	#define  CURRENT_CT_ESAM			REMAIN_MONEY_ALARM2_LIMIT_ESAM+4/*" 电流互感器变比 "*/
	#define  VOLTAGE_PT_ESAM			CURRENT_CT_ESAM+3/*" 电压互感器变比 "*/
	#define  METER_ID_ESAM				VOLTAGE_PT_ESAM+3/*" 表号 "*/
	#define  CLIENT_ID_ESAM				METER_ID_ESAM+6	/*" 客户编号 "*/
	#define  CARD_KIND_ESAM				CLIENT_ID_ESAM+6/*" 电卡类型 "*/
	#define  IDENTITY_AUTH_TIME_ESAM		CARD_KIND_ESAM+1/*" 身份认证时效 "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 购电卡文件数据结构 "*/
struct Buy_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" 用户类型 "*/
	unsigned char Para_UpData_Flag;          /*" 参数更新标志位 "*/
	unsigned char No_Use0[4];      /*" 保留 "*/
	unsigned char Triff_Switch_Time[5];      /*" 两套分时费率切换时间 "*/
	unsigned char No_Use1;                      /*" 保留 "*/
	unsigned long Remain_Money_Alarm1_Limit; /*" 报警金额1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" 报警金额2 "*/
	unsigned char Current_CT[3];             /*" 电流互感器变比 "*/
	unsigned char Voltage_PT[3];             /*" 电压互感器变比 "*/
	unsigned char Meter_ID[6];               /*" 表号 "*/
	unsigned char Client_ID[6];              /*" 客户编号 "*/
	unsigned char Card_Kind;                 /*" 电卡类型 "*/
	};
#define LENGTH_BUY_PARA_INF_FILE  sizeof(struct Buy_Para_Inf_File)
	#define BUY_PARA_INF_FILE_BUY_CARD					4
	#define USER_KIND_BUY_CARD                			BUY_PARA_INF_FILE_BUY_CARD /*" 用户类型 "*/
	#define PARA_UPDATA_FLAG_BUY_CARD         			USER_KIND_BUY_CARD+1 /*" 参数更新标志位 "*/
	#define NO_USE0_BUY_CARD      							PARA_UPDATA_FLAG_BUY_CARD+1/*" 保留 "*/
	#define TRIFF_SWITCH_TIME_BUY_CARD     				NO_USE0_BUY_CARD+4 /*" 两套分时费率切换时间 "*/
	#define NO_USE1_BUY_CARD               				TRIFF_SWITCH_TIME_BUY_CARD+5       /*" 保留 "*/
	#define REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD 			NO_USE1_BUY_CARD+1/*" 报警金额1 "*/
	#define REMAIN_MONEY_ALARM2_LIMIT_BUY_CARD 			REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD+4/*" 报警金额2 "*/
	#define CURRENT_CT_BUY_CARD             				REMAIN_MONEY_ALARM2_LIMIT_BUY_CARD+4/*" 电流互感器变比 "*/
	#define VOLTAGE_PT_BUY_CARD          					CURRENT_CT_BUY_CARD+3   /*" 电压互感器变比 "*/
	#define METER_ID_BUY_CARD         						VOLTAGE_PT_BUY_CARD+3      /*" 表号 "*/
	#define CLIENT_ID_BUY_CARD      	 					METER_ID_BUY_CARD+6       /*" 客户编号 "*/
	#define CARD_KIND_BUY_CARD         					CLIENT_ID_BUY_CARD+6        /*" 电卡类型 "*/


//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 密钥下装/恢复卡 "*/
/*" 密钥信息文件 "*/
struct Password_Inf_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;//卡类型 05 下装卡， 
	unsigned int 	File_Length;
	unsigned char Password_Info[4];          /*" 密钥信息，包括：状态，方式，条数，版本 "*/
	unsigned char Add_CS;
	unsigned char End_Byte;
	};
/*" 密钥文件 "*/
struct Password_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;
	unsigned int 	File_Length;
	unsigned char New_Password[4][32];
	unsigned char Add_CS;
	unsigned char End_Byte;
	};	
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 现场参数设置卡 "*/
struct Set_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" 用户类型 "*/
	unsigned char Para_UpData_Flag;          /*" 参数更新标志位 "*/
	unsigned long Para_Card_Version;      /*" 现场参数设置卡版本号 "*/
	unsigned char Triff_Switch_Time[5];      /*" 两套分时费率切换时间 "*/
	unsigned char No_Use1;                      /*" 保留 "*/
	};
#define LENGTH_SET_PARA_INF_FILE  sizeof(struct Set_Para_Inf_File)
	#define SET_PARA_INF_FILE_SET_CARD			4
	#define USER_KIND_SET_CARD                 	SET_PARA_INF_FILE_SET_CARD		/*" 用户类型 "*/
	#define PARA_UPDATA_FLAG_SET_CARD          	USER_KIND_SET_CARD+1			/*" 参数更新标志位 "*/
	#define PARA_CARD_VERSION_SET_CARD      		PARA_UPDATA_FLAG_SET_CARD+1		/*" 现场参数设置卡版本号 "*/
	#define TRIFF_SWITCH_TIME_SET_CARD      		PARA_CARD_VERSION_SET_CARD+4	/*" 两套分时费率切换时间 "*/
	#define NO_USE1_SET_CARD                    	TRIFF_SWITCH_TIME_SET_CARD+5  	/*" 保留 "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ESAM数据回抄卡 "*/
/*" 无特殊 "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 参数预置卡 "*/
struct Init_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" 用户类型 "*/
	unsigned char Para_UpData_Flag;          /*" 参数更新标志位 "*/
	unsigned long Para_Card_Version;      /*" 现场参数设置卡版本号 "*/
	unsigned char Triff_Switch_Time[5];      /*" 两套分时费率切换时间 "*/
	unsigned char No_Use1;                      /*" 保留 "*/
	unsigned long Remain_Money_Alarm1_Limit; /*" 报警金额1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" 报警金额2 "*/
	unsigned char Current_CT[3];             /*" 电流互感器变比 "*/
	unsigned char Voltage_PT[3];             /*" 电压互感器变比 "*/
	};
#define LENGTH_INIT_PARA_INF_FILE  sizeof(struct Init_Para_Inf_File)
	#define INIT_PARA_INF_FILE_INIT_CARD		4
	#define USER_KIND_INIT_CARD               	INIT_PARA_INF_FILE_INIT_CARD  /*" 用户类型 "*/
	#define PARA_UPDATA_FLAG_INIT_CARD        	USER_KIND_INIT_CARD+1  /*" 参数更新标志位 "*/
	#define PARA_CARD_VERSION_INIT_CARD      		PARA_UPDATA_FLAG_INIT_CARD+1/*" 现场参数设置卡版本号 "*/
	#define TRIFF_SWITCH_TIME_INIT_CARD    			PARA_CARD_VERSION_INIT_CARD+4  /*" 两套分时费率切换时间 "*/
	#define NO_USE1_INIT_CARD                 	TRIFF_SWITCH_TIME_INIT_CARD+5     /*" 保留 "*/
	#define REMAIN_MONEY_ALARM1_LIMIT_INIT_CARD NO_USE1_INIT_CARD+1/*" 报警金额1 "*/
	#define REMAIN_MONEY_ALARM2_LIMIT_INIT_CARD REMAIN_MONEY_ALARM1_LIMIT_INIT_CARD+4/*" 报警金额2 "*/
	#define CURRENT_CT_INIT_CARD         		    REMAIN_MONEY_ALARM2_LIMIT_INIT_CARD+4/*" 电流互感器变比 "*/
	#define VOLTAGE_PT_INIT_CARD             		CURRENT_CT_INIT_CARD+3/*" 电压互感器变比 "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 表号设置卡 "*/
/*" 指令信息文件 "*/
struct MeterID_Para_Inf_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;
	unsigned int 	File_Length;
	unsigned char Start_Meter_ID[6];
	unsigned char End_Meter_ID[6];	
	unsigned char Add_CS;
	unsigned char End_Byte;
	};
/*" 返写信息文件 "*/
struct MeterID_Return_Inf_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;
	unsigned int 	File_Length;
	unsigned char NO_Use[26];
	unsigned char Next_Meter_ID[6];//当前要设置的表号
	unsigned char Add_CS;
	unsigned char End_Byte;
	};
#define LENGTH_METERID_RETURN_INF_FILE  sizeof(struct MeterID_Return_Inf_File)
	#define  NO_USE_METERID					4
	#define  NEXT_METER_ID_METERID			NO_USE_METERID+26
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" 增加电量卡 "*/
/*" 指令信息文件 "*/
struct Add_Money_Para_Inf_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;
	unsigned int  File_Length;
	unsigned long Buy_Money;
	unsigned long Buy_Money_Count;	
	unsigned char Add_CS;
	unsigned char End_Byte;
	};
#define LENGTH_ADD_MONEY_PARA_INF_FILE  sizeof(struct Add_Money_Para_Inf_File)
	#define BUY_MONEY_CARD					4
	#define BUY_MONEY_COUNT_CARD		BUY_MONEY_CARD+4
//------------------------------------------------------------------
//------------------------------------------------------------------	
// end	
//------------------------------------------------------------------
//------------------------------------------------------------------
#endif