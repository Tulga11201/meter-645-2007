#ifndef EVENT_PROTO_H
#define EVENT_PROTO_H


#define MAX_DATA_LEN_NUM  54//该宏不能小，至少比最长的数组的个数大1，即len数组最后一个一定留一个为0做标示
typedef struct
{
  INT8U Num;//数据个数
  INT16U Len[MAX_DATA_LEN_NUM];//每个数据的长度，单位:字节
}S_Event_Info_Quck;

typedef struct
{
  PROTO_DI PDI;//事件的id，也就是PROTO_DI的前两个字节，
  CONST INT16U *pSub_Len;//事件信息，
  INT8U Num;
}S_Event_PDI_Info_Quck;

/*
//#include "Data_Para.h"
typedef struct
{
  PROTO_DI PDI; //累计数据的协议DI
  INT8U Data_Num; //累计数据项个数
  
  
}S_Event_Cumu_Proto
*/
EXT PROTO_DI Get_Event_Separate_Start_PDI(PROTO_DI PDI);
EXT INT16U Get_Event_Cumu_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U _Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U *pSpec_Flag);
EXT INT16U Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
#endif

