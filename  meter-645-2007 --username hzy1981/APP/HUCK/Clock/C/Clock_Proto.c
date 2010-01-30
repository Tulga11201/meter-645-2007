#define CLOCK_PROTO_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H1"
#endif

INT16U Get_Clock_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  S_BCD_Time TempTime;
  
  Get_Time_From_INTER_RTC((S_BCD_Time *)&TempTime);
  
  if(0x04000101 EQ PDI)//日期及星期
  {
    mem_cpy(pDst,(void *)&TempTime.Week,4,pDst_Start,DstLen);
    return 4;
  }
  else if(0x04000102 EQ PDI)//时间
  {
    mem_cpy(pDst,(void *)&TempTime.Sec,3,pDst_Start,DstLen);
    return 3;
  }  
  ASSERT_FAILED();
  return 0;
}

//设置当前
INT8U Set_Clock_Proto_Data(PROTO_DI PDI, INT8U *pSrc, INT16U SrcLen)
{
  S_BCD_Time TempTime;
  
  if(0x04000101 EQ PDI)//日期以及星期
  {
    mem_cpy(&TempTime,(void *)&Cur_Time1,sizeof(Cur_Time1),&TempTime,sizeof(TempTime));
    TempTime.Week=*pSrc;
    TempTime.Date=*(pSrc+1);
    TempTime.Month=*(pSrc+2);
    TempTime.Year=*(pSrc+3);
    SET_STRUCT_SUM(TempTime);
   
    return Adj_Time(&TempTime, 1); //校时，并记录校时记录 
  }
  else if(0x04000102 EQ PDI)//时间
  {
    mem_cpy(&TempTime,(void *)&Cur_Time1,sizeof(Cur_Time1),&TempTime,sizeof(TempTime));
    TempTime.Sec=*pSrc;
    TempTime.Min=*(pSrc+1);
    TempTime.Hour=*(pSrc+2);
    SET_STRUCT_SUM(TempTime);
    
    return Adj_Time(&TempTime, 1); //校时，并记录校时记录
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }
}

#undef CLOCK_PROTO_C

