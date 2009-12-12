#ifndef CLOCK_H
#define CLOCK_H

#include "Pub_Time.h"

#undef EXT
#ifdef CLOCK_C
#define EXT
#else
#define EXT extern
#endif

#define GET_CLOCK_PERIOD 50//读取外部时钟周期，暂未用该宏

#define USE_EXT_RTC 0
#define USE_INTER_RTC 1

#define T_MIN 0
#define T_HOUR 1
#define T_DATE 2
#define T_MONTH 3
#define T_YEAR 4

/*
//当前时间定义,BCD格式
//Time[0]分
//Time[1]时
//Time[2]日
//Time[3]月
//Time[4]年
typedef struct
{
  INT8U Time[5];
  INT8U Week;//0表示周日,1-6分别表示周1->周6
  INT8U CS[CS_BYTES];
}S_HEX_Time;

//时间定义结构体
typedef struct
{
  INT8U Sec;
  INT8U Min;
  INT8U Hour;
  INT8U Week;//0表示周日,1-6分别表示周1->周6
  INT8U Date;
  INT8U Month;
  INT8U Year;
  
  INT8U CS[CS_BYTES];//校验和
}S_BCD_Time;
*/
typedef struct
{
  INT8U EXT_RTC_Err_Counts:6;  //外部时钟错误计数
  INT8U Set_INTER_RTC_Flag:1;//内部时钟被设置标志，1表示内部时钟曾被设置过,0表示自上电后内部时钟还没被设置过
  INT8U Clock_Ready_Flag:1;  //时钟数据就绪标志，1表示Cur_Time0和Cur_Time1等数据已经可用
  INT8U CS[CS_BYTES];        //校验和
}S_Clock_Info;

typedef struct
{
  INT8U Time[6];//秒、分、时、日、月、年
  INT8U CS[CS_BYTES];
}S_Event_Time;

typedef struct
{
  INT8U Max_Counts;
  INT8U CS[CS_BYTES];
}S_Adj_Time_Para;

EXT NO_INIT volatile S_HEX_Time Cur_Time0;             //当前时间0
EXT NO_INIT volatile S_Clock_Info Clock_Info;

EXT NO_INIT volatile S_BCD_Time Cur_Time1;             //当前时间1

EXT volatile S_Adj_Time_Para Adj_Time_Para;  //每日校时次数
EXT volatile INT8U RTC_Err_Time[5];//错误时间,用于记录事件记录时用
EXT volatile S_Event_Time Cur_Time2;
EXT NO_INIT volatile S_BCD_Time Cur_Time_Bak;          //Cur_Tim1的一个备份
EXT volatile S_Event_Time Adj_Bef_Time;  //校时前时间
EXT volatile S_Event_Time PD_Time; //前次掉电时间
EXT volatile S_Event_Time PO_Time; //前次上电时间
EXT volatile S_HEX_Time Hex_PD_Time; //掉电时间

#ifdef CLOCK_C
EXT S_Int32U Time_Modify_Flag = {CHK_BYTE, 0, CHK_BYTE};
EXT S_Int32U Adj_Time_Flag = {CHK_BYTE, 0, CHK_BYTE};
#endif
EXT S_Int32U Time_Modify_Flag;
EXT S_Int32U Adj_Time_Flag;

EXT INT8U _Check_BCD_Time(INT8U Time[]);
EXT INT8U _Check_HEX_Time(INT8U Time[]);

EXT INT8U Check_HEX_Time(S_HEX_Time *pTime);
EXT INT8U Check_BCD_Time(S_BCD_Time *pTime);

EXT void Set_BCD_Time(INT8U Time[],S_BCD_Time *pBCD_Time);

EXT INT8U Get_Time_From_EXT_RTC(S_BCD_Time *pBCD_Time);
//将时间设置到外部RTC
EXT INT8U Set_Time_To_EXT_RTC(S_BCD_Time *pBCD_Time);
//从内部RTC读取时间数据
EXT INT8U Get_Time_From_INTER_RTC(S_BCD_Time *pBCD_Time);
//将时间设置到内部RTC
EXT INT8U Set_Time_To_INTER_RTC(S_BCD_Time *pBCD_Time);

EXT INT8U Resume_Clock_Update();
EXT void Get_Timer_From_CPU_Inter(S_BCD_Time *pBCD_Time);

EXT void Save_PD_Time();
EXT void Save_Bak_PD_Time();
EXT void Init_Clock_Ram_Para();
EXT void Clock_Proc();
EXT void Clock_Update();
EXT INT8U Check_Time_Diff(S_BCD_Time *pTime0,S_BCD_Time *pTime1,INT8U Mins);
EXT INT8U Set_Time_EXT_INTER_Ram_RTC(S_BCD_Time * pBCD_Time);

EXT void Set_BCD_Array_Time(S_BCD_Time* pSrc, S_Event_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Set_Array_BCD_Time(S_Event_Time* pSrc, S_BCD_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Set_Err_Time(S_BCD_Time *pBCD_Time);

EXT INT8U Convert_BCD_2_HEX_Time(S_BCD_Time *pBCD_Time,S_HEX_Time *pHEX_Time);
EXT INT8U Convert_HEX_2_BCD_Time(S_HEX_Time *pHEX_Time,S_BCD_Time *pBCD_Time);

EXT void Wait_Clock_Ready();
EXT void Check_Clock_Data_Avail();
EXT void Simulate_Clock();
EXT void Init_Clock(INT32U Mode);
EXT INT8U Adj_Time(S_BCD_Time *pTime, INT8U Flag);
EXT INT8U Adjust_Time_Proc(INT8U* pSrc, INT8U SrcLen);
EXT void Read_Adj_Time_Para_From_Rom();
#endif
