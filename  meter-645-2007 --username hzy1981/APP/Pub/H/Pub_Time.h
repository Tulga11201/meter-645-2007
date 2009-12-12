#ifndef TIME_H
#define TIME_H

//#include "Energy.h"

#undef EXT
#ifndef TIME_C
#define EXT extern
#else
#define EXT
#endif

#define UNIT_MIN 2
#define UNIT_HOU 3
#define UNIT_DAY 4
#define UNIT_MON 5

#define T_MIN 0
#define T_HOUR 1
#define T_DATE 2
#define T_MONTH 3
#define T_YEAR 4

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

typedef struct
{
  INT8U Head;

  S_HEX_Time Time;
  INT8U Tail;
}_S_HEX_Time;

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

EXT void Dec_Min(INT8U Time[], INT8U Mins);
EXT void Dec_Hour(INT8U Time[], INT8U Hours);
EXT void Dec_Day(INT8U Time[], INT8U Days);
EXT void Dec_Month(INT8U Time[], INT8U Months);
EXT void Dec_Year(INT8U Time[], INT8U Years);

EXT void Inc_Min(INT8U Time[], INT8U Mins);
EXT void Inc_Hour(INT8U Time[], INT8U Hours);
EXT void Inc_Day(INT8U Time[], INT8U Days);
EXT void Inc_Month(INT8U Time[], INT8U Months);
EXT void Inc_Year(INT8U Time[], INT8U Years);

EXT INT8U _Check_BCD_Time(INT8U Time[]);
EXT INT8U _Check_HEX_Time(INT8U Time[]);

EXT INT8U Check_HEX_Time(S_HEX_Time* pTime);
EXT INT8U Check_BCD_Time(S_BCD_Time* pTime);
EXT void Get_BCD_Time(S_BCD_Time* pSrc, INT8U Dst[], INT8U Dst_Start[], INT8U DstLen);

EXT void Print_HEX_Time(S_HEX_Time* pTime);
EXT void Print_BCD_Time(S_BCD_Time* pTime);

EXT void ConvertTime(INT8U Time[], INT16U Interval, INT8U Unit);
EXT INT8U Cmp_Array_Time(INT8U Time0[], INT8U Time1[], INT8U Len);
EXT INT8U Cmp_Time(S_HEX_Time* pTime1, S_HEX_Time* pTime2);
EXT INT8U _Cmp_Time(S_HEX_Time* pTime1, S_HEX_Time* pTime2);

EXT void Time_Inc(S_HEX_Time* pTime0, INT16U Interval, INT8U Unit, S_HEX_Time* pTime1);
EXT void Time_Dec(S_HEX_Time* pTime0, INT16U Interval, INT8U Unit, S_HEX_Time* pTime1);

EXT INT8U Week(INT8U y, INT8U m, INT8U d);
EXT INT32U mktime(const INT16U year0, const INT16U mon0, const INT16U day, const INT16U hour, const INT16U min, const INT16U sec);
#endif
