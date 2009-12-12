#define EXTEND_C
#include "Includes.h"

#if METER_PLACE == 0
//分次事件数据项目的扩展处理
INT16U Extend_Event_Separate_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag, INT8U* pReturn_Flag)
{
  Event_ID = Event_ID;
  Occur_Or_End = Occur_Or_End;
  Flag = Flag;
  *pReturn_Flag = 0;
  return 0;
}

INT16U Extend_Event_Cumu_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag, INT8U* pReturn_Flag)
{
  Event_ID = Event_ID;
  Occur_Or_End = Occur_Or_End;
  Flag = Flag;
  *pReturn_Flag = 0;
  return 0;
}

void Extend_Init()
{
}

INT8U Extend_Set_Data_Proc(PROTO_DI PDI, INT8U* pSrc, INT16U SrcLen)
{
  /*
   INT32U *p;
   INT8U i;
   
   if(DI EQ 0xC91F)
     p = (INT32U *)Cur_Energy.Pos_Active;
   else if(DI EQ 0xC92F)
     p = (INT32U *)Cur_Energy.Neg_Active;
   else if(DI EQ 0xC93F)
     p = (INT32U *)Cur_Energy.Quad_Reactive[0];
   else if(DI EQ 0xC94F)
     p = (INT32U *)Cur_Energy.Quad_Reactive[1];
   else if(DI EQ 0xC95F)
     p = (INT32U *)Cur_Energy.Quad_Reactive[2];
   else if(DI EQ 0xC96F)
     p = (INT32U *)Cur_Energy.Quad_Reactive[3];
   else
     return PROTOCOL_DI_ERR;
   
   for(i = 0; i <= MAX_RATES; i ++)
   {
     //mem_cpy(&Data, pSrc + i*4, 4, &Data, sizeof(Data)); 
     
     *(p + i) = Bcd2Hex(pSrc + i*4, 4);
   }
   
   SET_STRUCT_SUM(Cur_Energy);
   */
  return 1;//PROTOCOL_DI_ERR;  
}

//读取扩展的数据项目
INT16U Extend_Get_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  //*pErr=PROTOCOL_DI_ERR;
  return 0;
}

INT16U Extend_Get_Single_Proto_Data_Proc(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U* pErr)
{
  *pErr = 0;
  return 0;
}

#endif
#undef EXTEND_C
