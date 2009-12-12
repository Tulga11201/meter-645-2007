#ifndef FREEZE_DATA_H
#define FREEZE_DATA_H

#undef EXT
#ifdef FREEZE_DATA_C
#define EXT
#else
#define EXT extern
#endif

//定义定时冻结时间
typedef struct
{
  INT8U Mode[5];
  
  INT8U Period_Freeze_Time[4];    //周期冻结时间

  INT8U Hour_Freeze_Start_Time[5]; //整点冻结起始时间,分、时、日、月、年
  INT8U Hour_Freeze_Period;  //整点冻结间隔

  INT8U Date_Freeze_Time[2]; //日冻结时间
  INT8U CS[CS_BYTES];
}S_Freeze_Para;

//EXT volatile S_Freeze_Time Freeze_Time;//武功周期冻结时间
EXT volatile S_Freeze_Para Freeze_Para;

EXT void Read_Freeze_Para_From_Rom();
EXT void Check_Freeze_Para_Avail();
EXT void Freeze_Proc();
#endif
