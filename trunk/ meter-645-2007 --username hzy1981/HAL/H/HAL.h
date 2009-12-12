#ifndef HAL_H
#define HAL_H

#undef EXT
#ifdef HAL_C
#define EXT
#else
#define EXT extern
#endif

#define ROM0_SIZE 512L
#define ROM1_SIZE 32*1024L
#define ROM2_SIZE 32*1024L
#define ROM3_SIZE 32*1024L
#define ROM4_SIZE 8*1024L
#define ROM5_SIZE 2000*1024L

#define DEBUG_FILE_NAME "D:\\Debug_Info.txt"
EXT FILE *pDebug_File;

/////////////stub//////////////

#define CHANEL_IRDA     0           //红外通道数据---------UART0
#define CHANEL_485_1    1           //485通道数据---------UART2
#define CHANEL_485_2    2           //485通道数据---------UART3
#define CHANEL_MOUDEL   3

#define ID_EVENT_CLR_VOLT_PASS 0           //模块通道数据---------UART1
#define ID_EVENT_CLR_PROCESS   1
#define ID_EVENT_CLR_ALL_DATA  2
#define ID_EVENT_CLR_DEMAND_COM 3

#define EXT_RTC_OK 1
#define MODE_FAC 0
#define MODE_RUN 1

#define NO_QUADRANT   0             //无效象限
#define QUADRANT1     (NO_QUADRANT+1)
#define QUADRANT2     (QUADRANT1+1)
#define QUADRANT3     (QUADRANT2+1)
#define QUADRANT4     (QUADRANT3+1)

#define POWER_OFF_STATUS 1

//#define Set_Event_Instant(x)
#define DIS_PD_INT
#define EN_PD_INT
#define PARSE_341 0
#define Get_SysParse_Mode() 0
#define Check_Prog_Status() 1
#define Check_MeterAddr_Status() 1
#define Set_Soft_RTC_PUCK(x)
#define Read_Ext_RTC_Status() EXT_RTC_OK
#define Get_Soft_RTC_PUCK(x,y) 1
#define Init_DebugChanel_PUCK(X)
#define Print_Reset_Source()
#define Get_Meter_Hard_Mode() MODE_FAC
//#define Get_Measu_AcculateData_PUCK
#define Soft_Reset() 
#define PwrCtrl_ExtDevice_HigSpeed()
#define Init_CPU_PUCK(X)
#define Init_ExtDevice_PUCK(X)
#define Clear_Event_Data()
#define Clear_Data_End()
#define Clr_Screen_PUCK()  //上电后，强行清LCD显示
#define Test_HardWare_PUCK()
#define Init_Measure_Ram()
//#define PowerOn_Event_Proc()//上电后对前一次掉电前的事件处理
#define Init_Measu_PUCK()  //初始化计量，供液晶数据显示，供事件判定  
#define LCD_Init_PUCK()   //LCD显示初始化，满足速度需要

#define Set_Event_Instant(X)
#define Clr_Event_Instant(X)

#define Check_Event_Occuring(X) 0
#define Get_Buf_MulitByte_Sum(a,b,c,d,e)
//#define Clear_VolStat_Data()
///////////////////////////////

typedef struct
{
	INT8U A_LossV:1;            //A相失压
	INT8U B_LossV:1;            //B相失压
	INT8U C_LossV:1;            //C相失压
	INT8U V_SeqErr:1;           //电压相序错
	INT8U I_SeqErr:1;           //电流相序错
	INT8U A_Creep:1;            //A潜动
	INT8U B_Creep:1;            //B潜动
	INT8U C_Creep:1;            //C潜动
	
	INT8U A_APwrDir:1;        //A有功功率方向：0－正，1－负
	INT8U B_APwrDir:1;        //B有功功率方向：0－正，1－负
	INT8U C_APwrDir:1;        //C有功功率方向：0－正，1－负
	INT8U SUM_APwrDir:1;      //合相有功功率方向：0－正，1－负  
	INT8U A_RPwrDir:1;        //A无功功率方向：0－正，1－负
	INT8U B_RPwrDir:1;        //B无功功率方向：0－正，1－负
	INT8U C_RPwrDir:1;        //C无功功率方向：0－正，1－负  
	INT8U SUM_RPwrDir:1;      //合相无功功率方向：0－正，1－负 
	
	INT8U MeasuIntOk:1;       //计量芯片初始化完成
	INT8U PulseEn:1;          //脉冲输出使能
	INT8U DataRecFlg:1;       //1：接收到计量数据标志，应用层可取数据；0-----还没有准备好计量数据，不要取
	INT8U Reserved:5;
	//以上8bits对齐 
	INT8U CS[CS_BYTES];
}MEASU_STATUS;              //计量状态字

typedef struct
{  
	INT32U A;
	INT32U B;
	INT32U C;
	INT32U Sum;
}MEASU_DATA;       //MeasuIC瞬时量计量数据

typedef struct
{  
	INT8U A;
	INT8U B;
	INT8U C;
	INT8U Sum;
}MEASUFLAG;       //MeasuIC瞬时量状态数据

typedef struct
{
	MEASU_DATA AcPower;       //有功功率:UNIT:0.000001kW
	MEASU_DATA ReacPower;     //无功功率:UNIT:0.000001kvar
	MEASU_DATA AppPower;      //视在功率:UNIT:0.000001kva
	MEASU_DATA Volt;          //电压有效值：无合相 UNIT:0.0001V
	MEASU_DATA Curr;          //电流有效值: UNIT:0.0001A	
	MEASU_DATA PFactor;       //功率因数: UNIT:0.000001
	MEASU_DATA Freq;          //频率:UNIT:0.000001Hz
	MEASUFLAG  Quadrant;      //各相象限：QUADRANT1～QUADRANT4代表1～4象限。
	MEASU_DATA Angle;         //电压电流夹角：UINT:0.01度
	INT32U     Temprate;      //温度
	INT8U CS[CS_BYTES];
}MEASU_INSTANT;   //MeasuIC瞬时量计量数据


typedef struct
{
	INT32U Chang_Plus_AcEnerg[4];            //A/B/C/SUM各元件正向有功增量:单位:0.01wh
	INT32U Chang_Nega_AcEnerg[4];            //A/B/C/SUM各元件反向有功增量:单位:0.01wh
	
	//INT32U Chang_Plus_ReacEnerg[4];          //A/B/C/SUM各元件正向无功增量(无功组合1):单位:0.01warh  
	//INT32U Chang_Nega_ReacEnerg[4];          //A/B/C/SUM各元件反向无功增量(无功组合2):单位:0.01warh
	
	INT32U Chang_Quad_ReacEnerg[4][4];       //A/B/C/SUM各元件四象限无功增量,Chang_Quad_ReacEnerg[1][2]表示B向3象限无功
	
	INT32U Add_AmpaHour[3];                 //AH累计:0.0001As,累计量
	INT32U Add_CopperLoss[4];		  //A,B,C,sum铜损,单位为0.0000001kA2s,累计量
	INT32U Add_IronLoss[4];		  //A,B,C,sum铁损,单位为0.0000001KV2s，累计量
	INT32U Add_GenaralErr[4];		  //A,B,C,sum合成误差,单位:0.01*tgFA*s,累计量
	INT8U CS[CS_BYTES];
}MEASU_ENERG;                             //计量累计数据和增量数据


EXT volatile MEASU_STATUS      Measu_Status_Mode_ToPub_PUCK;   //计量基本状态字(已按照331/341处理)

EXT volatile MEASU_INSTANT    Measu_InstantData_ToPub_PUCK;    //计量瞬时数据
EXT volatile MEASU_ENERG       Measu_Energ_ToPub_PUCK;       //计量累计量数据

EXT INT8U Temp_Buf[1000];

EXT void Put_Char(OS_INT8U Chr);
EXT INT8U Debug_Out_Public_Puck(OS_INT8U *Srcbuf,OS_INT16U Src_Len);
EXT void Clear_CPU_Dog();    //清CPU内部看门狗
EXT void  Clear_Ext_Dog();    //清CPU外部看门狗

EXT INT8U Check_Meter_Factory_Status();
EXT INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen);
EXT INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen);

EXT INT8U Read_ExtRTC_PUCK(INT8U Dst[],INT8U Len);
EXT INT8U Write_ExtRTC_PUCK(INT8U Src[]);
EXT INT8U Read_InterRTC_PUCK(INT8U Dst[],INT8U Len);
EXT INT8U Write_InterRTC_PUCK(INT8U Src[]);
EXT INT8U Check_Protocol_Data_Storage();
EXT void Check_Data_Avail();
EXT INT16U Get_Measu_AcculateData_PUCK(INT8U ID,void *DstReal,void *Dst_Start,INT16U DstLen,INT16U DstMaxLen);
EXT void HAL_Init();
EXT void count_1ms(void);
EXT INT8U Check_Event_End(INT8U Event_ID);
#endif
