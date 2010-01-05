#ifndef ALL_CARD_OPERATION_DEF_H__
#define ALL_CARD_OPERATION_DEF_H__
//����Card_File.h�ļ�
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
/*" ÿ�ſ�������ļ����Լ�λ�ã���Կλ�� "*/
/*" ESAM�ļ����� "*/
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
/*" �û������� "*/
#define USER_CARD_PARA_INF_FILE			0x01
#define USER_CARD_MONEYBAG_FILE			0x02
#define USER_CARD_TRIFF_1_FILE			0x03
#define USER_CARD_TRIFF_2_FILE			0x04
#define USER_CARD_RUN_INF_FILE			0x05
/*" ��Կ��װ/�ָ������� "*/
#define PASSWORD_CARD_INF_FILE			0x01
#define PASSWORD_CARD_COUNTER_FILE		0x02
#define PASSWORD_CARD_PASS_FILE			0x03
/*" �ֳ��������ÿ����� "*/
#define PARA_SET_CARD_PARA_INF_FILE		0x01
#define PARA_SET_CARD_TRIFF_1_FILE		0x02
#define PARA_SET_CARD_TRIFF_2_FILE		0x03
#define PARA_SET_CARD_COUNTER_FILE		0x04
/*" ESAM���ݻس������� "*/
#define ESAM_BACK_ORDER_INF_FILE			0x01
#define ESAM_BACK_MONEYBAG_FILE				0x02
#define ESAM_BACK_PARA_INF_FILE				0x03
#define ESAM_BACK_TRIFF_1_FILE				0x04
#define ESAM_BACK_TRIFF_2_FILE				0x05
#define ESAM_BACK_PASSWORD_INF_FILE			0x06
#define ESAM_BACK_FAR_PASSWORD_INF_FILE		0x07
#define ESAM_BACK_RUN_INF_FILE				0x08
/*" Ԥ�ƿ������� "*/
#define INIT_CARD_PARA_INF_FILE				0x01
#define INIT_CARD_MONEYBAG_FILE				0x02
#define INIT_CARD_TRIFF_1_FILE				0x03
#define INIT_CARD_TRIFF_2_FILE				0x04
/*" ������ÿ����� "*/
#define METERID_CARD_ORDER_INF_FILE			0x01
#define METERID_CARD_RETURN_FILE				0x02
/*" ���ӵ�ѿ����� "*/
#define ADD_MONEY_CARD_ORDER_INF_FILE		0x01
/*" �̵������Կ����� "*/
#define RELAY_TEST_CARD_ORDER_INF_FILE		0x01
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ������Ϣ�ļ�1 "*/
struct Triff_Data
	{
	unsigned long Triff[63];
	};
#define LENGTH_TRIFF_DATA  sizeof(struct Triff_Data)
	#define TRIFF_CPU    4
/*" Ǯ����Ϣ���� "*/
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
/*" �������ù������ݽṹ���� "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ��������������1 "*/
struct Para_Table1
	{
	unsigned char Card_Kind;                 /*" �翨���� "*/
	unsigned char Client_ID[6];              /*" �ͻ���� "*/
	unsigned char Meter_ID[6];               /*" ��� "*/
	};
#define LENGTH_PARA_TABLE1  sizeof(struct Para_Table1)
/*" ��������������2 "*/
struct Para_Table2
	{
	unsigned char User_Kind;                  /*" �û����� "*/
	unsigned char Para_UpData_Flag;          /*" �������±�־λ "*/
	};
#define LENGTH_PARA_TABLE2  sizeof(struct Para_Table2)
/*" ��������������3 "*/
struct Para_Table3
	{
	unsigned long Remain_Money_Alarm1_Limit; /*" �������1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" �������2 "*/
	unsigned char Current_CT[3];             /*" ������������� "*/
	unsigned char Voltage_PT[3];             /*" ��ѹ��������� "*/
	};
#define LENGTH_PARA_TABLE3  sizeof(struct Para_Table3)
/*" ��������������4 "*/
struct Para_Table4
	{
	unsigned char Triff_Switch_Time[5];      /*" ���׷�ʱ�����л�ʱ�� "*/
	};
#define LENGTH_PARA_TABLE4  sizeof(struct Para_Table4)
/*" ��������������5 "*/
struct Para_Table5
	{
	unsigned long Para_Card_Version;      /*" �ֳ��������ÿ��汾�� "*/
	};
#define LENGTH_PARA_TABLE5  sizeof(struct Para_Table5)
/*" ��������������6 "*/
struct Para_Table6
	{
	unsigned int  Identity_Auth_Time;       /*" �����֤ʱЧ "*/
	};
#define LENGTH_PARA_TABLE6  sizeof(struct Para_Table6)
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" �������� "*/
/*" ��д����,���û�����ESAM�� 1ss"*/
struct Run_Inf_Data
	{	
         unsigned char temp;	//�����ֽڶ��룬��ΪRemain_Money�������һ������λ�ã�
	unsigned char User_Kind;					/*" �û����� "*/
	unsigned char Current_CT[3];				/*" ������������� "*/
	unsigned char Voltage_PT[3];				/*" ��ѹ��������� "*/	
	unsigned char Meter_ID[6];					/*" ��� "*/
	unsigned char Client_ID[6];				/*" �ͻ���� "*/
	
        unsigned long Remain_Money;				/*" ʣ���� "*/
	unsigned long Buy_Count;					/*" ������� "*/
	unsigned long Low_Zero_Money;				/*" ������ "*/
	unsigned char Password_Info[4];			/*" 1��������״̬����ʽ���������汾 "*/
	unsigned char Unlawful_Card_Count[3];		/*" �Ƿ���������� "*/
	unsigned char Return_DT[5];				/*" ��д����ʱ�� "*/
	};
#define LENGTH_RUN_INF_DATA  sizeof(struct Run_Inf_Data)
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" �ļ���Ӧ���ݽṹ "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
// ESAM�ļ����ݽṹ ,Ҳָ����Ϣ�ļ����������Ϣ�ļ�
struct Esam_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" �û����� "*/
	unsigned char Para_UpData_Flag;          /*" �������±�־λ "*/
	unsigned long Para_Card_Version;      /*" �ֳ��������ÿ��汾�� "*/
	unsigned char Triff_Switch_Time[5];      /*" ���׷�ʱ�����л�ʱ�� "*/
	unsigned char No_Use;                      /*" ���� "*/
	unsigned long Remain_Money_Alarm1_Limit; /*" �������1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" �������2 "*/
	unsigned char Current_CT[3];             /*" ������������� "*/
	unsigned char Voltage_PT[3];             /*" ��ѹ��������� "*/
	unsigned char Meter_ID[6];               /*" ��� "*/
	unsigned char Client_ID[6];              /*" �ͻ���� "*/
	unsigned char Card_Kind;                 /*" �翨���� "*/
	unsigned int  Identity_Auth_Time;       /*" �����֤ʱЧ "*/
	};
#define LENGTH_ESAM_PARA_INF_FILE  sizeof(struct Esam_Para_Inf_File)
	#define  ESAM_PARA_INF_FILE_ESAM		4
	#define  USER_KIND_ESAM			ESAM_PARA_INF_FILE_ESAM	/*" �û����� "*/
	#define  PARA_UPDATA_FLAG_ESAM		USER_KIND_ESAM+1/*" �������±�־λ "*/
	#define  PARA_CARD_VERSION_ESAM		PARA_UPDATA_FLAG_ESAM+1	/*" �ֳ��������ÿ��汾�� "*/
	#define  TRIFF_SWITCH_TIME_ESAM		PARA_CARD_VERSION_ESAM+4/*" ���׷�ʱ�����л�ʱ�� "*/
	#define  NO_USE_ESAM				TRIFF_SWITCH_TIME_ESAM+5 /*" ���� "*/
	#define  REMAIN_MONEY_ALARM1_LIMIT_ESAM		NO_USE_ESAM+1	/*" �������1 "*/
	#define  REMAIN_MONEY_ALARM2_LIMIT_ESAM		REMAIN_MONEY_ALARM1_LIMIT_ESAM+4/*" �������2 "*/
	#define  CURRENT_CT_ESAM			REMAIN_MONEY_ALARM2_LIMIT_ESAM+4/*" ������������� "*/
	#define  VOLTAGE_PT_ESAM			CURRENT_CT_ESAM+3/*" ��ѹ��������� "*/
	#define  METER_ID_ESAM				VOLTAGE_PT_ESAM+3/*" ��� "*/
	#define  CLIENT_ID_ESAM				METER_ID_ESAM+6	/*" �ͻ���� "*/
	#define  CARD_KIND_ESAM				CLIENT_ID_ESAM+6/*" �翨���� "*/
	#define  IDENTITY_AUTH_TIME_ESAM		CARD_KIND_ESAM+1/*" �����֤ʱЧ "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ���翨�ļ����ݽṹ "*/
struct Buy_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" �û����� "*/
	unsigned char Para_UpData_Flag;          /*" �������±�־λ "*/
	unsigned char No_Use0[4];      /*" ���� "*/
	unsigned char Triff_Switch_Time[5];      /*" ���׷�ʱ�����л�ʱ�� "*/
	unsigned char No_Use1;                      /*" ���� "*/
	unsigned long Remain_Money_Alarm1_Limit; /*" �������1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" �������2 "*/
	unsigned char Current_CT[3];             /*" ������������� "*/
	unsigned char Voltage_PT[3];             /*" ��ѹ��������� "*/
	unsigned char Meter_ID[6];               /*" ��� "*/
	unsigned char Client_ID[6];              /*" �ͻ���� "*/
	unsigned char Card_Kind;                 /*" �翨���� "*/
	};
#define LENGTH_BUY_PARA_INF_FILE  sizeof(struct Buy_Para_Inf_File)
	#define BUY_PARA_INF_FILE_BUY_CARD					4
	#define USER_KIND_BUY_CARD                			BUY_PARA_INF_FILE_BUY_CARD /*" �û����� "*/
	#define PARA_UPDATA_FLAG_BUY_CARD         			USER_KIND_BUY_CARD+1 /*" �������±�־λ "*/
	#define NO_USE0_BUY_CARD      							PARA_UPDATA_FLAG_BUY_CARD+1/*" ���� "*/
	#define TRIFF_SWITCH_TIME_BUY_CARD     				NO_USE0_BUY_CARD+4 /*" ���׷�ʱ�����л�ʱ�� "*/
	#define NO_USE1_BUY_CARD               				TRIFF_SWITCH_TIME_BUY_CARD+5       /*" ���� "*/
	#define REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD 			NO_USE1_BUY_CARD+1/*" �������1 "*/
	#define REMAIN_MONEY_ALARM2_LIMIT_BUY_CARD 			REMAIN_MONEY_ALARM1_LIMIT_BUY_CARD+4/*" �������2 "*/
	#define CURRENT_CT_BUY_CARD             				REMAIN_MONEY_ALARM2_LIMIT_BUY_CARD+4/*" ������������� "*/
	#define VOLTAGE_PT_BUY_CARD          					CURRENT_CT_BUY_CARD+3   /*" ��ѹ��������� "*/
	#define METER_ID_BUY_CARD         						VOLTAGE_PT_BUY_CARD+3      /*" ��� "*/
	#define CLIENT_ID_BUY_CARD      	 					METER_ID_BUY_CARD+6       /*" �ͻ���� "*/
	#define CARD_KIND_BUY_CARD         					CLIENT_ID_BUY_CARD+6        /*" �翨���� "*/


//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ��Կ��װ/�ָ��� "*/
/*" ��Կ��Ϣ�ļ� "*/
struct Password_Inf_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;//������ 05 ��װ���� 
	unsigned int 	File_Length;
	unsigned char Password_Info[4];          /*" ��Կ��Ϣ��������״̬����ʽ���������汾 "*/
	unsigned char Add_CS;
	unsigned char End_Byte;
	};
/*" ��Կ�ļ� "*/
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
/*" �ֳ��������ÿ� "*/
struct Set_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" �û����� "*/
	unsigned char Para_UpData_Flag;          /*" �������±�־λ "*/
	unsigned long Para_Card_Version;      /*" �ֳ��������ÿ��汾�� "*/
	unsigned char Triff_Switch_Time[5];      /*" ���׷�ʱ�����л�ʱ�� "*/
	unsigned char No_Use1;                      /*" ���� "*/
	};
#define LENGTH_SET_PARA_INF_FILE  sizeof(struct Set_Para_Inf_File)
	#define SET_PARA_INF_FILE_SET_CARD			4
	#define USER_KIND_SET_CARD                 	SET_PARA_INF_FILE_SET_CARD		/*" �û����� "*/
	#define PARA_UPDATA_FLAG_SET_CARD          	USER_KIND_SET_CARD+1			/*" �������±�־λ "*/
	#define PARA_CARD_VERSION_SET_CARD      		PARA_UPDATA_FLAG_SET_CARD+1		/*" �ֳ��������ÿ��汾�� "*/
	#define TRIFF_SWITCH_TIME_SET_CARD      		PARA_CARD_VERSION_SET_CARD+4	/*" ���׷�ʱ�����л�ʱ�� "*/
	#define NO_USE1_SET_CARD                    	TRIFF_SWITCH_TIME_SET_CARD+5  	/*" ���� "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ESAM���ݻس��� "*/
/*" ������ "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ����Ԥ�ÿ� "*/
struct Init_Para_Inf_File
	{
	unsigned char User_Kind;                 /*" �û����� "*/
	unsigned char Para_UpData_Flag;          /*" �������±�־λ "*/
	unsigned long Para_Card_Version;      /*" �ֳ��������ÿ��汾�� "*/
	unsigned char Triff_Switch_Time[5];      /*" ���׷�ʱ�����л�ʱ�� "*/
	unsigned char No_Use1;                      /*" ���� "*/
	unsigned long Remain_Money_Alarm1_Limit; /*" �������1 "*/
	unsigned long Remain_Money_Alarm2_Limit; /*" �������2 "*/
	unsigned char Current_CT[3];             /*" ������������� "*/
	unsigned char Voltage_PT[3];             /*" ��ѹ��������� "*/
	};
#define LENGTH_INIT_PARA_INF_FILE  sizeof(struct Init_Para_Inf_File)
	#define INIT_PARA_INF_FILE_INIT_CARD		4
	#define USER_KIND_INIT_CARD               	INIT_PARA_INF_FILE_INIT_CARD  /*" �û����� "*/
	#define PARA_UPDATA_FLAG_INIT_CARD        	USER_KIND_INIT_CARD+1  /*" �������±�־λ "*/
	#define PARA_CARD_VERSION_INIT_CARD      		PARA_UPDATA_FLAG_INIT_CARD+1/*" �ֳ��������ÿ��汾�� "*/
	#define TRIFF_SWITCH_TIME_INIT_CARD    			PARA_CARD_VERSION_INIT_CARD+4  /*" ���׷�ʱ�����л�ʱ�� "*/
	#define NO_USE1_INIT_CARD                 	TRIFF_SWITCH_TIME_INIT_CARD+5     /*" ���� "*/
	#define REMAIN_MONEY_ALARM1_LIMIT_INIT_CARD NO_USE1_INIT_CARD+1/*" �������1 "*/
	#define REMAIN_MONEY_ALARM2_LIMIT_INIT_CARD REMAIN_MONEY_ALARM1_LIMIT_INIT_CARD+4/*" �������2 "*/
	#define CURRENT_CT_INIT_CARD         		    REMAIN_MONEY_ALARM2_LIMIT_INIT_CARD+4/*" ������������� "*/
	#define VOLTAGE_PT_INIT_CARD             		CURRENT_CT_INIT_CARD+3/*" ��ѹ��������� "*/
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ������ÿ� "*/
/*" ָ����Ϣ�ļ� "*/
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
/*" ��д��Ϣ�ļ� "*/
struct MeterID_Return_Inf_File
	{
	unsigned char Start_Byte;
	unsigned char Order_Byte;
	unsigned int 	File_Length;
	unsigned char NO_Use[26];
	unsigned char Next_Meter_ID[6];//��ǰҪ���õı��
	unsigned char Add_CS;
	unsigned char End_Byte;
	};
#define LENGTH_METERID_RETURN_INF_FILE  sizeof(struct MeterID_Return_Inf_File)
	#define  NO_USE_METERID					4
	#define  NEXT_METER_ID_METERID			NO_USE_METERID+26
//------------------------------------------------------------------
//------------------------------------------------------------------
/*" ���ӵ����� "*/
/*" ָ����Ϣ�ļ� "*/
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