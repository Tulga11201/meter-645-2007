#ifndef ENERGY_H
#define ENERGY_H

#include "Pub_Time.h"

#undef EXT
#ifdef ENERGY_SETTLE_C
#define EXT
#else
#define EXT extern
#endif

#define POWER_ON_RST 0x5A
#define SOFT_RST 0xA5

//定义Cmp_Time函数返回值
#define TIME_EQU 0
#define TIME_AFT 1
#define TIME_BEF 2

//主副费率方案,Check_Year_Scheme()函数的返回
#define YEAR_SCHEME0 0x66
#define YEAR_SCHEME1 0x77

#define DATE_SCHEME0 0x88
#define DATE_SCHEME1 0x99

#define RATE_SCHEME0 0xAA
#define RATE_SCHEME1 0xBB

#define STEP_SCHEME0 0xCC
#define STEP_SCHEME1 0xDD

#define BEF_SWITCH_TIME 0x55
#define AFT_SWITCH_TIME 0xEE

#define CALC_RAM 0//计算费率或者费率方案时采用RAM中的参数
#define CALC_ROM 1//计算费率或者费率方案时采用ROM中的参数

//日标志定义，包括公共假日、周休日和一般日
#define HOLIDAY 0
#define WEEK_REST_DAY 1
#define NORMAL_DAY 2

//累加量的比率值,规约中的数据都定位2位小数，Cur_Energy中的数据都是3位小数
#define ENERGY_RATIO ((INT32U)100)//电能
#define COPPERLOSS_RATIO ((INT32U)3600*100000)//铜损
#define IRONLOSS_RATIO ((INT32U)3600*1000000)//铁损
#define TRANSERR_RATIO ((INT32U)3600)//互感器误差
#define AH_RATIO ((INT32U)3600*100)//该值待定
#define MONEY_RATIO ((INT32U)10000)//每秒临时金额是7位小数，总金额是3为小数，因此需要/10000

#define MAX_ACTIVE_INC 1000 //1000wh，每秒最多增加1度电，超过认为非法数据，丢弃
#define MAX_REACTIVE_INC 1000 //1000wh

#define MONEY_MODE  0 //电费型预付费
#define ENERGY_MODE 1 //电量型预付费

#define PREPAID_STEP_SCHEME ((Cur_Rate_Info.Step_Scheme EQ STEP_SCHEME0)?1:2)
#define PREPAID_STEP_NO     (Cur_Rate_Info.Step_No + 1)

//预付费金额或者电量状态宏定义
#define PREPAID_ENERGY_ENOUGH    0x01 //剩余电量充足
#define PREPAID_ENERGY_LEFT1     0x02 //低于限额1
#define PREPAID_ENERGY_LEFT2     0x03 //低于限额2
#define PREPAID_ENERGY_ZERO      0x04 //低于0
#define PREPAID_ENERGY_OVERDRAFT 0x05 //透支

#define PREPAID_MONEY_ENOUGH     0x06 //剩余金额充足
#define PREPAID_MONEY_LEFT1      0x07 //低于限额1
#define PREPAID_MONEY_LEFT2      0x08 //低于限额2
#define PREPAID_MONEY_ZERO       0x09 //低于0
#define PREPAID_MONEY_OVERDRAFT  0x0A //透支

#define PREPAID_MONEY_SWITCH_LIMIT 0x0B //低于允许合闸门限

//上电标志
typedef struct
{
    INT8U Flag[10];
    INT8U CS[CS_BYTES];
}S_Power_On_Flag;

//错误信息状态字
typedef struct
{
    INT8U ErrFlag;
    INT8U CS[CS_BYTES];
}S_Err_Info;


typedef struct
{
  INT32U Left_Energy; //剩余电量,单位0.001kwh
  INT32U Overdraft_Energy; //透支电量,单位0.001kwh  
  INT32U Total_Prepaid_Energy_Counts; //总购电次数  
  INT32U Total_Prepaid_Energy; //总购电电量,单位0.01kwh

  INT32U Left_Money; //剩余金额,单位0.001元
  INT32U Overdraft_Money;  //透支金额,单位0.001元
  INT32U Total_Prepaid_Money_Counts; //总购电次数
  INT32U Total_Prepaid_Money;  //总购电金额,单位0.001元

  INT32U Temp_Cumu_Energy;
  INT32U Temp_Cumu_Money; //金额的临时累加,3位电能*4位电价 =0.0000001元
 
  INT32U Month_Pos_Act; //当前结算周期正向有功电量 单位0.001kwh 
  INT32U Month_Neg_Act; //当前结算周期反向有功
  
  INT32U Last_Month_Pos_Act; //上一结算周期的正向有功
  INT32U Last_Month_Neg_Act; //上一结算周期的反向有功
  
  S_HEX_Time Time;//前一次月电量清零时间，一个结算周期清零一次
  
  //INT8U Clr_Alarm_Flag:1;  //手动清除报警标志,0表示没有手动清除，1表示手动清除
  //INT8U Card_Switch_On_Flag :1; //插卡合闸标志，在跳闸情况下未到透支门限情况下插卡合闸标志
  //INT8U Buy_Money_Switch_Limit_Flag :1; //充值是否低于合闸门限标志，1表示低于，不能合闸，0表示高于
  //INT8U Hand_Switch_On_Flag:4; //1表示需要手动合闸，0表示已经手动合闸, 该标志置为NEED_HAND_SWITCH_ON_FLAG表示需要手动合闸
                               //0表示已经手动合闸

  INT8U Eng_Money_Status;  //当前金额或者电量的状态
  
  ////////////////////用于后付费///////////////////
  INT32U All_Money; //总用电金额 单位0.001
  INT32U Month_Money; //当月用电金额, 单位0.001
  
  INT8U CS[CS_BYTES];
}S_Prepaid_Info;


typedef struct
{
  INT8U Head;
  
  INT32U Energy;  //当此购电电量
  INT32U Money;   //当此购点金额
  
  INT32U Bef_Left_Energy; //当此购电前剩余电量
  INT32U Bef_Left_Money;  //当此购电前剩余金额
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Cur_Prepaid; //当此购电信息

//电量结构体
typedef struct
{
    INT8U Head;

    //INT8U Time[5];//冻结时间点,该时间在冻结时复制为冻结时间
    S_HEX_Time Time;//冻结时间点,该时间在冻结时复制为冻结时间

    INT8U Temp;//保证上面的Time对齐


    //INT32U Month_Pos_Act; //当前结算周期正向有功总
    //INT32U Month_Neg_Act; //当前结算周期反向有功总
    
    INT32U Pos_Active[MAX_RATES + 1];//总以及分费率正向有功,三位小数,单位KWh，下同
    INT32U Neg_Active[MAX_RATES + 1];//总以及分费率反向有功
    
    INT32U Quad_Reactive[4][MAX_RATES + 1];//四象限分费率无功
    
    INT32U Pos_Apparent[MAX_RATES + 1]; //正向视在
    INT32U Neg_Apparent[MAX_RATES + 1]; //反向视在
    
    INT32U Phase_Pos_Active[3];//三相正向有功
    INT32U Phase_Neg_Active[3];//三相反向有功
    
    INT32U Phase_Quad_Reactive[3][4];//三相四象限无功

    INT32U Phase_Pos_Apparent[3]; //正向视在
    INT32U Phase_Neg_Apparent[3]; //反向视在
    
    INT32U Phase_AH[4];//总ABC安时

    INT32U CopperLoss[4];//总ABC铜损
    INT32U IronLoss[4];  //总ABC铁损
    INT32U TransErr[4];  //总ABC互感器误差

    //INT32U  Phase_Reactive[3][4];//三相各四象限无功
    S_Prepaid_Info Prepaid_Info; //预付费信息
      
    INT32U Data_Ready_Flag;

    INT8U CS[CS_BYTES];//后面的不需要保存到Flash中

    //以下部分是根据以上量计算得，不需要保存到Flash或EERom中
    //INT32U Pos_Reactive[MAX_RATES+1];//总以及分费率正向无功
    //INT32U Neg_Reactive[MAX_RATES+1];
    INT8U Tail;
}S_Energy;

DATA_PACKED_BEGIN
//周休日状态字
typedef struct
{
  INT8U Head;
  
  INT8U Status;
  INT8U CS[CS_BYTES];

  INT8U Tail;  
}S_WeekRest_Status;

//复费率相关参数
typedef struct
{
  INT8U Head;
  
  INT8U Year_Period; //年时区数
  INT8U Date_Table;  //日时段表数
  INT8U Date_Period; //日时段数
  INT8U Rates;  //费率数
  INT8U Holidays; //公共假日数
  INT8U Holidays_1; //公共假日数高位，不用

  INT8U Harmonic; //谐波次数

  //注意：一下两个变量的顺序不能变换
  INT8U WeekRest_DataTable;//周休日使用的时段表号
  INT8U WeekRest_Status;  //周休日特征字

  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Multi_Rate_Para;//复费率参数

//年时区表
typedef struct
{
  INT8U Head;
  
  /*"年时区结构体"*/
  INT8U MDN[MAX_YEAR_PERIODS][3];
  INT8U CS[CS_BYTES];
    
  INT8U Tail;  
}S_Year_Table;
//日时段表
typedef struct
{
  INT8U Head;
  /*"日时段表结构体"*/
  INT8U HMN[MAX_DATE_PERIODS][3];

  //INT8U Year_Scheme;//当前套费率方案
  //INT8U Index;//当前时段表索引号
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Date_Table;

typedef struct
{
  INT8U Index;
  INT8U CS[CS_BYTES];
}S_Cur_Date_Table;
//-------------300 byte-----------------------
//节假日结构体
typedef struct
{
  INT8U Head;
  /*"节假日结构体"*/
  //INT8U WeekRest_DataTable;//节假日采用的日时段表号 
  INT8U MDN[MAX_YEAR_HOLIDAYS][3];
  INT8U CS[CS_BYTES];
  INT8U Tail; 
}S_Holiday_Table;

//负荷曲线相关参数
typedef struct
{
  INT8U Head;
  
  INT8U Mode;//负荷曲线模式字

  INT8U Start_Time[4];//记录的起始时间
  INT8U Rec_Period[6][2];//6类数据的记录周期
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Load_Data_Para;
//无功模式字
typedef struct
{
  INT8U Head;
  
  INT8U Mode[2];
  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Reactive_Com_Mode;

//当前模式字
typedef struct
{
  INT8U Head;
  
  U_Byte_Bit Mode[5];
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Mode_Word;

/*
//自动抄表日参数,DDHH[0]表示小时,DDHH[1]表示日
typedef struct
{
    INT8U DDHH[2];
    INT8U CS[CS_BYTES];
}S_Data_Freeze_Time;
*/
//当前费率相关信息，主要用于打印输出
typedef struct
{
  INT8U Head;
  
  INT8U Year_Scheme;//当前使用的套费率方案
  INT8U Date_Scheme;//日时段表方案
  INT8U Rate_Scheme; //当前费率方案
  INT8U Step_Scheme; //当前阶梯方案
  INT8U Step_No;     //当前阶梯号

  INT8U Date_Flag;//HOLIDAY,WeekRest,NORMAL_DAY

  INT8U Holiday_Index; //第多少个假日
  INT8U Year_Period;  //年时区号

  INT8U Date_Table;//日时段表号
  INT8U Date_Period; //日时段号
  INT8U Rate; //当前费率
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;  
}S_Cur_Rate_Info;


DATA_PACKED_END

typedef struct
{
    INT8U Flag;
    INT8U CS[CS_BYTES];
}S_Flag;

//连续4字节，格式定义不要修改
typedef struct
{
  INT8U Head;
  
  INT8U Year_Scheme; //当前年时区方案--相对顺序不动！！！！
  INT8U Date_Scheme; //当前日时段方案
  INT8U Rate_Scheme; //当前费率方案
  INT8U Step_Scheme; //阶梯方案
  
  INT8U Year_Scheme_Time; //当前年时区，BEF_SWITCH_TIME表示切换时间以前，AFT_SWITCH_TIME表示切换时间以后
  INT8U Date_Scheme_Time; //当前日时段，BEF_SWITCH_TIME表示切换时间以前，AFT_SWITCH_TIME表示切换时间以后
  INT8U Rate_Scheme_Time; //当前费率方案，BEF_SWITCH_TIME表示切换时间以前，AFT_SWITCH_TIME表示切换时间以后
  INT8U Step_Scheme_Time; //阶梯电价方案 
    
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Cur_Scheme;

//分时电费参数
typedef struct
{
  INT8U Head;
  
  INT32U Fee[MAX_RATES]; 
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Rate_Scheme_Para;

typedef struct
{
  INT8U Head;
  
  //INT8U Step_Num;
  
  INT32U Step_Energy[PREPAID_MAX_STEP]; //阶梯电量, Step_Energy[0]固定为0
  INT32U Step_Fee[PREPAID_MAX_STEP + 1];
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Step_Scheme_Para;

//----------结构体内数据顺序不要修改-------------!!!
typedef struct
{
  INT8U Head;
  
  INT32U Warn_Energy1; //报警电量1
  INT32U Warn_Energy2; //报警电量2
  
  INT32U Hoard_Energy_Limit; //囤积电量限值
  INT32U Overdraft_Energy_Limit; //透支电量限值
  
  INT32U Warn_Money1; //报警金额1
  INT32U Warn_Money2; //报警金额2

  INT32U Overdraft_Money_Limit; //透支金额限值  
  INT32U Hoard_Money_Limit; //囤积金额限值 
  INT32U Switch_On_Money_Limit; //合闸允许金额限值 
    
  INT32U CT_Ratio; //电流互感器变比
  INT32U PT_Ratio; //电压互感器变比
  
  INT8U Step_Num; //梯度数
  
  U_Byte_Bit Mode[3]; //预付费模式字

  //INT32U Power_Puls; //负荷脉冲数
  //INT8U Power_Mins;  //最大负荷计算时间
  //INT8U Relay_Off_Counts_Limit; //过负荷跳闸次数门限
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Prepaid_Para;

EXT volatile INT8U Rst_Flag;

//EXT S_Err_Info Err_Info;  //错误信息状态字

EXT NO_INIT volatile S_Power_On_Flag Power_On_Flag;   //上电或复位标志

EXT volatile S_Mode_Word Mode_Word;    //当前无功模式字

EXT volatile _S_HEX_Time _Year_Scheme_Switch_Time;   //年时区方案切换时刻
EXT volatile _S_HEX_Time _Date_Scheme_Switch_Time; //日时段表方案切换时间
EXT volatile _S_HEX_Time _Rate_Scheme_Switch_Time;    //费率方案切换时间
EXT volatile _S_HEX_Time _Step_Scheme_Switch_Time;    //阶梯电价方案切换时间

#define Year_Scheme_Switch_Time _Year_Scheme_Switch_Time.Time
#define Date_Scheme_Switch_Time _Date_Scheme_Switch_Time.Time
#define Rate_Scheme_Switch_Time _Rate_Scheme_Switch_Time.Time
#define Step_Scheme_Switch_Time _Step_Scheme_Switch_Time.Time

EXT volatile S_Multi_Rate_Para Multi_Rate_Para;//当前费率方案参数
EXT volatile S_Year_Table Year_Table;      //当前年时区表
EXT volatile S_Date_Table Date_Table;      //当前日时段表
//EXT volatile S_Holiday_Table Holiday_Table;    //当前节假日表

//EXT volatile S_Data_Freeze_Time Data_Freeze_Time;//自动抄表日参数
//EXT volatile S_WeekRest_Status WeekRest_Status; //周休日状态字

EXT volatile S_Cur_Date_Table Cur_Date_Table;//当前日时段表索引号

EXT NO_INIT volatile S_Energy Cur_Energy;     //当前电量数据结构体

#if USE_ENERGY_RAM_BAK > 0
EXT NO_INIT volatile S_Energy Cur_Energy_Bak;     //当前电量数据结构体
#endif

EXT volatile S_Cur_Prepaid Cur_Prepaid;  //当次购电信息

EXT volatile S_Cur_Rate_Info Cur_Rate_Info;//当前费率相关信息,主要是供调试用
EXT volatile S_Int32U Energy_Cumu_Counts;
EXT volatile S_Cur_Scheme Cur_Scheme; //当前年时区、日时段、费率方案
EXT volatile S_Rate_Scheme_Para Rate_Scheme_Para; //分费率参数，预付费用
EXT volatile S_Step_Scheme_Para Step_Scheme_Para; //阶梯电价参数，预付费用 
EXT volatile S_Prepaid_Para Prepaid_Para; //预付费参数, 预付费用

EXT INT8U Check_Rst_Flag();

EXT void Check_Pub_Var_Avail();
EXT void Check_Cur_Energy_Data();
//EXT INT8U Get_Using_Rate();
EXT void Read_Mode_Word();

EXT void Read_Multi_Rate_Para();
EXT void Read_Energy_Para_From_Rom();
EXT void Read_Energy_Data_From_Rom();
EXT void Read_Energy_Data_Para_For_Show();

EXT void Calc_Pos_Neg_Reactive(S_Energy* pEnergy);
EXT void Read_Date_Table_Para(INT8U Date_Scheme, INT8U Date_Table_Index);

EXT void Read_Year_Scheme_Switch_Time();
EXT void Read_Date_Scheme_Switch_Time();
EXT void Read_Rate_Scheme_Switch_Time();
EXT void Read_Step_Scheme_Switch_Time();

EXT INT8U Calc_Cur_Date_Scheme(INT8U Flag);
EXT void Year_Scheme_Changed_Proc();
EXT void Date_Scheme_Changed_Proc();
EXT void Rate_Scheme_Changed_Proc();
EXT void Step_Scheme_Changed_Proc();
EXT void Rate_Changed_Proc();
EXT INT8U Get_Cur_Rate_Info(INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT32U Get_Pos_Act_Eng();

EXT void Read_Rate_Scheme_Para(INT8U Scheme);

EXT INT8U Check_Energy_Data(S_Energy* pEnergy);
EXT void Check_Cur_Year_Date_Scheme_Info();
EXT void Check_Energy_Para_Avil();
EXT void Check_Energy_Data_Avail();
EXT void Check_Prepaid_Para();
EXT void Check_Data_Avail();
EXT void Main_Chk_Data_Avail();
EXT void Check_Energy_Data_Para_Avail();
EXT void Check_Cur_Scheme_Info();

EXT void Debug_Print_Cur_Energy_Info();
EXT void Init_Energy_Demand_Ram_Para();
EXT void Save_Cur_Energy_Data();
EXT void Save_Cur_Energy_Bak0_Data();
EXT void Save_Cur_Energy_Bak1_Data();
EXT void Save_Cur_Energy_Bak2_Data();
EXT void Save_Cur_Energy_PD_Data();
EXT void Clear_Energy_Data();
EXT void Set_Def_Prepaid_Buy_Counts_Money();
EXT void Set_Def_Energy_Data();

EXT void Energy_Proc_Ram_Init();
EXT void Read_Para_From_Rom();

EXT void Check_Cur_Rate();
EXT void Period_Save_Cur_Data();
EXT void Cumulative_Energy();

EXT void Clear_Prepaid_Month_Eng();
EXT void PowerOn_Settle_Energy_Data();
EXT void Check_Energy_Para_Modified();

EXT void Refresh_Para_From_Rom();
EXT void Energy_Proc();
EXT void Last_Power_Down_Proc();
EXT void Check_Multi_Rate_Para();
EXT INT8U Check_Eng_Settle_Time(S_BCD_Time *pTime);
EXT void Settle_Data();

#endif
