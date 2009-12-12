#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include "InterrAbs.h"

#undef EXT
#ifndef EVENT_DATA_C
#define EXT extern
#else
#define EXT
#endif


typedef struct 
{
	INT8U Op_ID[4];//操作员ID
        INT8U Last_Op_ID[4];//前一次操作员ID
	INT8U CS[CS_BYTES];
}S_Operator_ID;

//某类数据编程标志 
typedef struct
{
  INT8U All_Flag:1; //总的记录 
  INT8U Date_Flag:1;
  INT8U Year_Flag:1;
  INT8U Week_Flag:1;
  INT8U Holiday_Flag:1;
  INT8U SettleDay_Flag:1;
  INT8U ActComm_Flag:1;
  INT8U ReacComm1_Flag:1;
  INT8U ReacComm2_Flag:1;
  
  //INT8U CS[CS_BYTES];
}S_Prog_Flag;

typedef struct  
{
	PROTO_DI PDI[10];
        INT8U Op_ID[4];
        INT8U Time[6]; //编程时间
	//INT8U Posi;
        //INT8U Mins;//从第一个编程起计数，10分钟内认为是一个编程记录
        //INT8U Event_Flag; //事件标志
        S_Prog_Flag Prog_Flag; //编程标志,在一个编程周期内是否有过编程的标志
        INT8U Prog_Status; //是否在编程状态
	INT8U CS[CS_BYTES];
}S_Prog_Record;

typedef struct
{
    INT32U Var;
    INT8U Time[6];//秒、分、时、日、月、年
}S_Event_Demand_Time;

typedef struct
{
    INT8U Pos_Active_Flag;//当前正有超限标志
    INT8U Neg_Active_Flag;//当前反有超限标志 
    INT8U Quad_Reac_Flag[4]; //当前四象限无功超限标志
    
    S_Event_Demand_Time Pos_Active;
    S_Event_Demand_Time Neg_Active;
    S_Event_Demand_Time Quad_Reactive[4];
	
    INT8U CS[CS_BYTES];
}S_Demand_Exceed_Limit;


typedef struct
{
    INT8U Head;
    INT8U Err_Counts;          //密码错误次数
    //INT16U Clr_Err_Counts_Mins; //清错误次数剩余时间
    INT16U Lock_Mins;          //锁定时间，就是解锁剩余时间
    INT8U Set_En_Mins;         //密码验证正确后允许设置时间
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_PSW_Err_Info;

typedef struct
{
  S_HEX_Time Hour_Freeze_Time;
  S_HEX_Time Date_Freeze_Time;
  INT8U CS[CS_BYTES];
}S_Last_Freeze_Time;

typedef struct
{
    INT32U Min_Timer;
    INT8U Temp0;
    
    INT8U PD_Flag; //是否发生过掉电?1表示确实发生了掉电，0表示没有
    INT8U Temp1;
    
    EVENT_INSTANT_STATUS Meter_Instant_Status;//事件状态信息
    INT8U Temp2;//不用保证上面的结构体对齐

    S_Demand_Exceed_Limit _Demand_Exceed_Limit;//需量越限记录
    INT8U Temp3;
    
    S_PSW_Err_Info _PSW_Err_Info;
    INT8U Temp4;
    
    S_Last_Freeze_Time _Last_Freeze_Time;//上次小时冻结和日冻结时间
    INT8U Temp5;
    
    S_BCD_Time _Last_Adj_Time;//前一次校表时间
    INT8U _Adj_Time_Counts; //校时次数
    INT8U Temp6;

    BAT_STATUS Bat_Work_Status;
    INT8U Temp7;
    
    S_Prog_Record _Prog_Record; //编程记录
    INT8U Temp8;
    
    NOT_EVEN_DATA Not_Even_Data;//不平衡率    
    INT8U Temp9;
    
    PRG_KEY_STATUS Prg_Key_Status; //编程状态
    INT8U Temp10;
//----------清事件时前面的可清掉，后面的不应该清---------
    PROTO_DI _Clear_Event_PDI; //清除事件的DI
    INT8U Temp11;

    S_Operator_ID _Operator_ID; //操作者ID
    INT8U Temp12;
    
    S_BCD_Time Time;
    
    INT8U Relay_Status;
    //INT8U Temp13;
 
    INT8U CS[CS_BYTES];
}S_Event_Data;

EXT volatile S_Event_Data Event_Data;

#define Operator_ID Event_Data._Operator_ID
#define Prog_Record Event_Data._Prog_Record
#define Demand_Exceed_Limit Event_Data._Demand_Exceed_Limit
#define PSW_Err_Info Event_Data._PSW_Err_Info
#define Last_Freeze_Time Event_Data._Last_Freeze_Time
#define Last_Adj_Time Event_Data._Last_Adj_Time //前一次校表时间
#define Adj_Time_Counts Event_Data._Adj_Time_Counts
#define Clear_Event_PDI Event_Data._Clear_Event_PDI


EXT void Check_Event_Data_Avail();
EXT INT8U Check_Event_Occuring(INT8U Event_ID);
EXT void Event_Data_Proc(INT8U Event_ID,INT8U Occur_Or_End);
EXT void All_Loss_Vol_Counts_Time_Proc(INT32U Counts,INT32U Mins);
EXT INT8U Get_Event_Total_Occuring_Singles(INT8U Event_ID);
EXT void All_Loss_Vol_Data_Proc(INT8U Start_Time[],INT8U End_Time[]);
EXT void Set_Event_PD_Time(S_HEX_Time *pTime);
EXT void Clear_Event_Data(PROTO_DI Clr_PDI);
EXT void Clear_Data_End();
EXT void Set_Def_Event_Data();
EXT void Save_Event_PD_Data();
EXT void PowerOn_Event_Proc();
EXT void Wait_Event_Data_Proc_End(INT8U Event_ID);
EXT void Set_Def_Event_PD_Data();
#endif

