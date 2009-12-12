#ifndef DEMAND_H
#define DEMAND_H

#include "Pub_Time.h"

#undef EXT
#ifdef DEMAND_C
#define EXT
#else
#define EXT extern
#endif
/*
需量数据存储的特点:
CUR_DEMAND总以及所有费率的数据
CUR_DEMAND_BAK存储格式和CUR_DEMAND一样
CUR_DEMAND_PD主要是掉电存储,只存储S_Demand结构体Cur_Demand
HIS_DEMAND主要存储前N个月的数据，每个数据项和CUR_DEMAND格式一样
*/

#define CUR_POS_ACT_DEMAND     Demand_Accu.Phase_Cur[0].Pos_Active       //当前正向有功需量
#define CUR_NEG_ACT_DEMAND     Demand_Accu.Phase_Cur[0].Neg_Active       //当前反向有功需量
#define CUR_QUAD1_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[0] //当前一象限需量
#define CUR_QUAD2_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[1] //当前二象限需量
#define CUR_QUAD3_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[2] //当前三象限需量
#define CUR_QUAD4_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[3] //当前四象限需量

#define MAX_PERIOD_SLIDE_RATIO 15//需量周期/滑差时间的最大值

#define POWER_DIRECT_N 0//定义功率方向正向
#define POWER_DIRECT_P 1//反向

#define POWER_DATA_RATIO 100

//需量时间数据的存储偏移，指在一个大的需量数据区中
#define DEMAND_TIME_DATA_OFF 0
#define DEMAND_TIME_DATA_SIZE sizeof(S_HEX_Time)

#define DEMAND_PHASE_DATA_OFF (DEMAND_TIME_DATA_SIZE + ROM_CS_BYTES)
#define DEMAND_PHASE_DATA_SIZE sizeof(Cur_Demand.Phase_Demand)

//某个费率需量数据在其需量存储区中的存储偏移
//需量存储区格式:
//时间:sizeof(S_HEX_Time)+ROM_CS_BYTES
//分相需量数据:sizeof(S_Phase_Demand)+ROM_CS_BYTES;
//总以及分费率需量:(DEMAND_RATE_DATA_SIZE + ROM_CS_BYTES)* MAX_RATES
#define DEMAND_RATE_DATA_SIZE sizeof(S_One_Demand)
#define DEMAND_RATE_DATA_OFF(x) (DEMAND_TIME_DATA_SIZE + ROM_CS_BYTES +\
     DEMAND_PHASE_DATA_SIZE + ROM_CS_BYTES +\
        (DEMAND_RATE_DATA_SIZE + ROM_CS_BYTES) * (INT32U)(x))//计算某个费率的需量数据在整个需量存储区中的偏移

#define POS_ACT_DEMAND_LIMIT   Power_Ctrl_Para.Pos_Act_Power_Limit//(INT32U)(Get_Un()*Get_In()*2*10)//单位为0.1W即 0.0001kw Get_Max_Power()
#define NEG_ACT_DEMAND_LIMIT  Power_Ctrl_Para.Neg_Act_Power_Limit//(INT32U)(Get_Un()*Get_In()*2*10)//Get_Max_Power()
#define QUAD_REA_DEMAND_LIMIT  Power_Ctrl_Para.Pos_Act_Power_Limit//(INT32U)(Get_Un()*Get_In()*2*10)//Get_Max_Power()

typedef struct
{
  INT32U Pos_Act_Demand_Limit; //正向有功需量上限
  INT32U Neg_Act_Demand_Limit; //反向有功需量上限
  INT32U Reac_Demand_Limit;    //无功需量上限
  
  INT8U CS[CS_BYTES];
}S_Demand_Limit_Para;

//需量相关参数
typedef struct
{
    INT8U Period;//最大需量时间
    INT8U Slide_Time;//滑差时间

    INT8U CS[CS_BYTES];
}S_Demand_Para;

//总以及分相需量累加单元
typedef struct
{
    INT32U Pos_Active[MAX_PERIOD_SLIDE_RATIO];//正向有功15个功率累加单元,单位0.0001kw
    INT32U Neg_Active[MAX_PERIOD_SLIDE_RATIO];//反向有功15个功率累加单元,单位0.0001kw

    INT32U Pos_Apparent[MAX_PERIOD_SLIDE_RATIO];//正向视在15个功率累加单元,单位0.0001kw
    INT32U Neg_Apparent[MAX_PERIOD_SLIDE_RATIO];//反向视在15个功率累加单元,单位0.0001kw    
    
    //INT32U Comb_Reactive1[MAX_PERIOD_SLIDE_RATIO];//正向无功15个功率累加单元,单位0.0001kvar
    //INT32U Comb_Reactive2[MAX_PERIOD_SLIDE_RATIO];//反向无功15个功率累加单元,单位0.0001kvar

    INT32U Quad_Reactive[4][MAX_PERIOD_SLIDE_RATIO];//四象限无功15个功率累加单元

    INT8U CS[CS_BYTES];
}S_Phase_Accu;

//总以及分相当前需量
typedef struct
{
    INT32U Pos_Active;//当前正有需量,单位0.0001kw
    INT32U Neg_Active;//当前反有需量,单位0.0001kw

    INT32U Pos_Apparent; //视在功率
    INT32U Neg_Apparent;
    
    INT32U Quad_Reactive[4];
    INT32S Comb_Reactive1;
    INT32S Comb_Reactive2;

    INT8U CS[CS_BYTES];
}S_Phase_Cur;

//需量统计信息,包括次数和累计时间
typedef struct
{
    INT16U Counts[MAX_PERIOD_SLIDE_RATIO];
    INT16U Mins[MAX_PERIOD_SLIDE_RATIO];

    INT8U CS[CS_BYTES];
}S_Accu_Stat;

//分相
typedef struct
{
    INT8U Head;
    /////////////
    S_Phase_Accu Phase_Accu[DEMAND_ACCU_PHASE_NUM]; //总以及分相需量累加单元,4位小数
    S_Phase_Cur Phase_Cur[DEMAND_ACCU_PHASE_NUM];  //总以及分相当前需量,4位小数
    S_Accu_Stat Accu_Stat;
    
    INT8U Tail;
}S_Demand_Accu;//功率累加


//S_Demand_Time和S_Comb_Demand_Time的格式应该基本一致
//因为获取需量数据的处理中假定了这两个结构体的内存布局一致
typedef struct
{
    INT32U Var;
    INT8U Time[5];//分、时、日、月、年
}S_Demand_Time;

//组合无功需量
typedef struct
{
    INT32S Var;
    INT8U Time[6];
}S_Comb_Demand_Time;

typedef struct
{
  INT8U Head;
  INT8U Rate_Bak;
  INT8U Min_Bak;
  INT32U Mins;
  INT8U Tail;
}S_Demand_Rate_Mins;

//定义一条需量数据项，该数据结构通常用来定义某个费率或总的所有需量数据
typedef struct
{
    S_HEX_Time Time;

    S_Demand_Time Pos_Active; //正向有功
    S_Demand_Time Neg_Active; //反向有功

    S_Demand_Time Quad_Reactive[4]; //四象限无功

    S_Comb_Demand_Time Comb_Reactive1; //组合无功1
    S_Comb_Demand_Time Comb_Reactive2; //组合无功2

    S_Demand_Time Pos_Apparent; //正向视在
    S_Demand_Time Neg_Apparent; //反向视在

    //定义校验和
    INT8U CS[CS_BYTES];
}S_One_Demand;


//需量数据结构体，表示每个费率的需量信息
typedef struct
{
    INT8U Head;

    INT8U Rate;//当前费率

    //总以及当前费率数据
    S_One_Demand Demand[2];//定义总和当前费率的需量数据 

    INT8U Temp0;//对齐

    S_One_Demand Phase_Demand[3];//定义三相需量

    INT8U Temp1;//对齐

    INT32U Data_Ready_Flag;

    INT8U CS[CS_BYTES];

    INT8U Tail;
}S_Demand;//

typedef struct
{
  INT8U Head;
  
  INT32S Active;   //有功需量
  INT32S Apparent; //视在需量
  INT32S Reactive; //无功需量
  
  INT8U Tail;//INT8U CS[CS_BYTES];
}S_Sign_Demand;

typedef struct
{
  INT8U Head;
  
  INT32U Accu_Power;
  INT32U Aver_Power; //4位小数，单位0.0001kw
  INT16U Counts;
  
  INT8U Tail;
  //INT8U CS[CS_BYTES];
}S_Aver_Power;

EXT volatile S_Aver_Power AcPower_1Min_Aver; //有功一分钟平均功率

#ifdef DEMAND_C
volatile S_Aver_Power AcPower_1Min_Aver = {CHK_BYTE, 0, 0, 0, CHK_BYTE};
#endif

EXT volatile S_Demand_Limit_Para Demand_Limit_Para; //需量越限参数
EXT volatile S_Demand_Para Demand_Para;
EXT volatile S_Demand_Accu Demand_Accu;
EXT NO_INIT volatile S_Demand Cur_Demand;     //当前最大需量数据结构体
EXT volatile S_Sign_Demand Sign_Demand;   //有符号的当前需量，主要用于协议抄读

#ifdef DEMAND_C
volatile S_Sign_Demand Sign_Demand = {CHK_BYTE, 0, 0, 0, CHK_BYTE};   //有符号的当前需量，主要用于协议抄读
#endif
EXT volatile INT8U Clear_Demand_Way;//请需量方式

EXT INT8U Check_Demand_Data(S_Demand* pDemand);

EXT void Read_Demand_Para_From_Rom();
EXT void Read_Demand_Data_From_Rom();
EXT void Save_Cur_Demand_Data();
EXT void Save_Cur_Demand_PD_Data();
EXT void Save_Cur_Demand_Bak_Data();
EXT void Set_Def_Cur_Demand_Data(S_HEX_Time *pTime);
EXT void Set_Def_Demand_Data();
EXT void Freeze_Demand_Data(S_HEX_Time* pTime);
EXT void Demand_Check_Rate_Change();
EXT void Check_Demand_Para_Avail();
EXT void Demand_Accumu();
EXT void Demand_Generate();
EXT void Demand_Accu_Clear();
EXT void Demand_Clear(S_HEX_Time* pTime);
EXT void Demand_Proc();
EXT void Calc_1Min_Aver_AcPower();
//EXT void Demand_Accu_Init(INT32U Sleep_Secs);
EXT void PowerOn_Demand_Proc();
EXT void Check_Demand_Data_Avail();
EXT void Clear_Cur_Demand_Data();
EXT void Clear_Demand_Data();
EXT void Clr_Demand_Accu();
EXT void Manul_Clr_Demand_Data();
EXT void Clr_Demand_Manul_Chk();

EXT INT32U Get_One_Min_AcPower_Aver();
EXT INT8U Get_Demand_Run_Mode();
EXT void Set_One_Demand_Time(S_One_Demand* pSrc, S_HEX_Time* pTime);
EXT void PowerOn_Demand_Data_Freeze();
EXT void PowerDown_Save_Demand_Data();
EXT void Debug_Print_Cur_Demand_Info();
#endif
