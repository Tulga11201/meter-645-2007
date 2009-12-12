#ifndef EXTEND_H
#define EXTEND_H

#undef EXT
#ifdef EXTEND_C
#define EXT
#else
#define EXT extern
#endif

#define METER_GD 1 //定义表计算省份

#define METER_PLACE 0//METER_GD

#if METER_PLACE == METER_GD
#include "Extend_GD.h"
#endif

#if METER_PLACE == 0

#define EXTEND_EVENT_SEPARATE //分次事件DI的扩展
#define EXTEND_EVENT_CUMU //扩展的分次事件
#define EXTEND_DATA_TRANS     //扩展的传输数据
#define EXTEND_STORA  //存储的扩展
#define EXTEND_DEF_PARA

EXT void Extend_Init();
EXT INT8U Extend_Set_Data_Proc(PROTO_DI PDI, INT8U* pSrc, INT16U SrcLen);
EXT INT16U Extend_Event_Separate_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag, INT8U* pReturn_Flag);
EXT INT16U Extend_Event_Cumu_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag, INT8U* pReturn_Flag);
EXT INT16U Extend_Get_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U Extend_Get_Single_Proto_Data_Proc(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U* pErr);
#endif

#endif
