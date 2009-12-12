#ifndef EVENT_CUMU_H
#define EVENT_CUMU_H

#include "EventPub.h"

#undef EXT
#ifdef EVENT_CUMU_C
#define EXT
#else
#define EXT extern
#endif

#define ARRAY_DI_NUM 30

#define EVENT_REAL  0
#define EVENT_VIRTRUAL 1

#define NULL_EVENT_ID 0xFF

#define CUMU_LOSS_VOL_SIZE  (13 + 80)
#define CUMU_LOSS_CUR_SIZE  (13 + 80)
#define CUMU_NEG_CUR_SIZE   (13 + 80)
#define CUMU_BREAK_VOL_SIZE (13 + 80)

typedef struct
{
    INT8U DI_Num;
    PROTO_DI PDI[ARRAY_DI_NUM];
}S_DI_Array;

//对于事件的累加处理
typedef struct
{
    INT8U Event_ID;//事件 ID

    //事件的累计时间和次数需要特殊处理
    //STORA_DI Counts_DI;//次数累加DI,等同于通信协议DI
    //INT8U Counts_Start;
    //INT8U Counts_Len;

    //STORA_DI Mins_DI;//时间累加DI,等同于通信协议DI
    //INT8U Mins_Start;
    //INT8U Mins_Len;

    ///////////////////////上面部分是时间和次数的累加，标准规约里面都有的//////////////////////////////

    ///////////////////////下面部分是电能的总累加///////////////////////////
    STORA_DI Occur_Stora_DI;//发生时的电能数据存储DI
    STORA_DI Total_Stora_DI;//总的电能数据的DI,等同于协议DI

    S_DI_Array* pDI_Array;
    
    INT8U Clr_Flag;
}S_Event_Cumu_Data_Info;

///////////////////////////////////////////////
/*
#define PHASE_A   0x01
#define PHASE_B   0x02
#define PHASE_C   0x04
#define PHASE_AB  0x03
#define PHASE_AC  0x05
#define PHASE_BC  0x06
#define PHASE_ABC 0x07
#define PHASE_ALL 0x08

//定义分相事件累加信息
typedef struct
{
  INT32U Counts;//失压次数 
  INT32U Time;//失压累计时间
  
  INT8U CS[CS_BYTES];
}S_Phase_Cumu;

//失压累计数据
typedef struct
{
  INT32U Counts;//失压次数 
  INT32U Time;//失压累计时间
  
  INT32U Phase_Pos_Active[4];//总、A、B、C相累计有功电量
  INT32S Phase_Pos_Reactive[4];//总、A、B、C三相正向无功，组合无功1
  INT32U Phase_Neg_Active[4];//总、A、B、C三相反向有功
  INT32S Phase_Neg_Reactive[4];//总、A、B、C三相反向无功，组合无功2
  INT32U Phase_AH[3];//A、B、C三相安培时间
  
  INT8U CS[CS_BYTES]; 
}S_Loss_Vol_Cumu;


//失流累计数据
typedef struct
{
  INT32U Counts;//失压次数 
  INT32U Time;//失压累计时间
  
  INT32U Phase_Pos_Active[4];//总、A、B、C相累计有功电量
  INT32S Phase_Pos_Reactive[4];//总、A、B、C三相正向无功，组合无功1
  INT32U Phase_Neg_Active[4];//总、A、B、C三相反向有功
  INT32S Phase_Neg_Reactive[4];//总、A、B、C三相反向无功，组合无功2
  //INT32U Phase_AH[3];//A、B、C三相安培时间
  
  INT8U CS[CS_BYTES]; 
}S_Loss_Cur_Cumu;

//反向期间累计数据
typedef struct
{
  INT32U Counts;
  INT32U Time;
  
  INT32U Phase_Pos_Active[4];//总、A、B、C相累计有功电量
  INT32U Phase_Neg_Active[4];//总、A、B、C三相反向有功
  INT8U CS[CS_BYTES];
}S_Reverse_Cumu;//


//全失压，全失流、断相累计数据
typedef struct
{
  INT32U Counts;
  INT32U Time;
  INT8U CS[CS_BYTES];
}S_Phase_Break_Cumu;

//总的事件累加量
typedef struct
{
  INT8U Loss_Vol_Flag;    //失压标志
  INT8U Loss_Cur_Flag;    //失流标志
  INT8U Phase_Reverse_Flag; //反向标志
  INT8U Phase_Break_Flag;   //断相标志
  
  S_Phase_Cumu Phase_Loss_Vol[9];//总、A、B、C和AB、AC、BC、ABC、全失压、
  S_Phase_Cumu Phase_Loss_Cur[8];//总、A、B、C和AB、AC、BC、全失流
  S_Phase_Cumu Phase_Break[4];//三相断相(不考虑AB,BC,AC,ABC的情况)总、A、B、C
  S_Reverse_Cumu Phase_Reverse[4];//三相反向(不考虑AB,BC,AC,ABC的情况)总、A、B、C

  
  S_Loss_Vol_Cumu Loss_Vol;//失压期间累计电能等,必须考虑合相的情况
  S_Loss_Cur_Cumu Loss_Cur;//失流期间累计电能等

  
  INT8U CS[CS_BYTES];
}S_Event_Cumu;

typedef struct
{
  INT32S Pos_Reactive[4];//总、A、B、C正向无功  
  INT32U Neg_Reactive[4];//总、A、B、C反向无功
}S_Phase_Reactive;

typedef struct
{
  INT8U Start_Time[5];
  INT8U End_Time[5];
  INT8U CS[CS_BYTES];  
}S_All_Loss_Vol_Time;

EXT volatile S_All_Loss_Vol_Time All_Loss_Vol_Time;//最近一次全失压的发生和结婚时间,用于生成协议数据
EXT NO_INIT volatile S_Event_Cumu Event_Cumu;     //事件累加数据
EXT volatile S_Phase_Reactive Cumu_Phase_Reactive; //分相组合无功累加数据

EXT INT8U Check_Phase_Event(INT8U Flag,INT8U Phase);
EXT void Event_Cumu_Proc(INT8U Event_ID,INT8U Occur_Or_End);
EXT void Read_Event_Cumu_Data_From_Rom();
EXT void Save_Event_Cumu_PD_Data();
EXT INT8U Check_Event_Occuring(INT8U Event_ID);
EXT void Save_Event_Cumu_Bak_Data();
EXT void Set_Def_Event_Cumu_Data();
*/
EXT CONST S_Event_Cumu_Data_Info Event_Cumu_Data_Info[];

EXT INT8U Check_Cumu_Event_Occuring(INT8U Event_ID);
EXT INT8U Check_Total_Event_ID(INT8U Event_ID);
EXT INT8U Get_Total_Event_ID(INT8U Event_ID);
EXT INT16U Event_Cumu_End_Proc(INT16U Index, INT8U Flag);
EXT INT16U Event_Cumu_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag);
EXT INT16U Get_Event_Cumu_Proto_Index(PROTO_DI DI);
EXT void Get_Event_Cumu_Counts_Mins(INT8U Event_ID, INT32U *pCounts, INT32U *pMins);
EXT void Get_Event_Cumu_BCD_Counts_Mins(INT8U Event_ID, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT16U Get_Cumu_Event_Num();
EXT void Event_Data_Proc(INT8U Event_ID, INT8U Occur_Or_End);
EXT void Event_Cumu_Mins_Accu();
EXT void Set_Def_Event_Cumu_Data();
EXT void Clear_Event_Cumu_Data();
EXT INT8U Clear_One_Event_Cumu_Data(INT8U Event_ID);
EXT void Clr_Event_PD_Data();
EXT void Save_Event_PD_Data();
#endif
