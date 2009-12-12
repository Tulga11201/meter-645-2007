#ifndef EXTEND_GD_H
#define EXTEND_GD_H

#undef EXT
#ifdef EXTEND_C
#define EXT
#else
#define EXT extern
#endif

#if METER_PLACE == METER_GD
EXT U_Byte_Bit  GD_Meter_Stat;        //广东：电表状态字
EXT U_Byte_Bit  GD_PwrDir_Stat;       //广东：有功功率方向状态字
EXT U_Byte_Bit  GD_LossVolt_Stat;        //广东：失压状态字
EXT U_Byte_Bit  GD_LossCurr_Stat;        //广东：失流状态字
EXT U_Byte_Bit  GD_Hard_Stat;        //广东：硬件状态字
EXT U_Byte_Bit  GD_Prog_Stat;        //广东：编程状态字

//--------------------------扩展事件描述信息-----------------------------------
//分别对应失压和失流事件的描述
#define EVENT_MULTITIMES_DI_EXTEND {.Occur_Mask=0x3B,.End_Mask=0x3F,.Diff_Mask=0x38,.Data_Num=6,.Data_Len=23,.DI={DI_LOSS_VOL_STATUS,DI_CUR_TIME,DI_CUR_TIME,0x9010,0x9110,DI_CUR_AH}},\
                                   {.Occur_Mask=0x1B,.End_Mask=0x1F,.Diff_Mask=0x18,.Data_Num=5,.Data_Len=19,.DI={DI_LOSS_CUR_STATUS,DI_CUR_TIME,DI_CUR_TIME,0x9010,0x9110}},\
                                   {.Occur_Mask=0x1B,.End_Mask=0x1F,.Diff_Mask=0x18,.Data_Num=5,.Data_Len=19,.DI={DI_NEG_CUR_STATUS,DI_CUR_TIME,DI_CUR_TIME,0x9010,0x9110}},

//--------------------------扩展的分次事件、失压和失流事件---------------------
#define ID_EVENT_LOSS_VOL 0xE0    //失压事件ID
#define ID_EVENT_LOSS_CUR 0xE1    //失流事件ID
#define ID_EVENT_NEG_CUR  0xE3    //功率反向

#define EVENT_MULTITIMES_EXTEND {.Event_ID=ID_EVENT_LOSS_VOL,.Property=0,.pData=&Event_DI[MAX_MULTI_TIMES_DI_NUM],.Last_Storage_DI=SDI_S_LOSS_VOL,.Storage_DI=SDI_LOSS_VOL,.Storage_Num=5,.Clr_Flag=0},\
                                {.Event_ID=ID_EVENT_LOSS_CUR,.Property=0,.pData=&Event_DI[MAX_MULTI_TIMES_DI_NUM+1],.Last_Storage_DI=SDI_S_LOSS_CUR,.Storage_DI=SDI_LOSS_CUR,.Storage_Num=5,.Clr_Flag=0},\
                                {.Event_ID=ID_EVENT_NEG_CUR,.Property=0,.pData=&Event_DI[MAX_MULTI_TIMES_DI_NUM+1],.Last_Storage_DI=SDI_S_NEG_CUR,.Storage_DI=SDI_NEG_CUR,.Storage_Num=5,.Clr_Flag=0},   

//---------------------------扩展的失压状态字和失流状态字-----------------------
#define DI_LOSS_VOL_STATUS 0x0180 //失压状态字
#define DI_LOSS_CUR_STATUS 0x0181 //失流状态字
#define DI_NEG_CUR_STATUS  0x0182 //功率方向
#define DI_CUR_AH          0x0183 //当前安时,2位小数

#define DATA_TRANS_EXTEND        {DI_LOSS_VOL_STATUS,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(void *)&GD_LossVolt_Stat.Byte,0,1,S_BCD,0,1,1,SPEC_NO},\
                                 {DI_LOSS_CUR_STATUS,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(void *)&GD_LossCurr_Stat.Byte,0,1,S_BCD,0,1,1,SPEC_NO},\
                                 {DI_NEG_CUR_STATUS,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,(void *)&GD_PwrDir_Stat.Byte,0,1,S_BCD,0,1,1,SPEC_NO},\
                                 {DI_CUR_AH,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_RAM,&Cur_Energy.Phase_AH[0],0,4,S_INTU,0,4,0,SPEC_NO},\
                                {0xE144,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,5,S_BIN,0,5,1,SPEC_NO},\
                                {0xE145,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,5,S_BCD,0,5,1,SPEC_NO},\
                                {0xE148,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,5,S_BCD,0,5,1,SPEC_NO},\
                                {0xE149,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,5,S_BCD,0,5,1,SPEC_NO},\
                                {0xE14C,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,5,S_BCD,0,5,1,SPEC_NO},\
                                {0xE14D,DI_EQU_NULL,0,0,PSW_RD_ONLY,S_ROM,(void *)0,0,5,S_BIN,0,5,1,SPEC_NO},\
                                {0xC119,DI_EQU_NULL,0,0,PSW_SET_ENSTART,S_ROM,(INT8U *)Zero,0,4,S_BIN,0,4,SPEC_EXTEND},

//-----------------------------扩展存储，用于分次失压和失流事件-----------------
#define SDI_S_LOSS_VOL 0x01F100
#define SDI_LOSS_VOL   0x01F101
#define SDI_S_LOSS_CUR 0x01F200
#define SDI_LOSS_CUR   0x01F201
#define SDI_S_NEG_CUR  0x01F300
#define SDI_NEG_CUR    0x01F301

#define SDI_CLR_ENG_COUNTS 0x01F400 //记录电量清0次数

#define STORA_EXTEND  { SDI_S_LOSS_VOL, IMP7,4,1},\
                      { SDI_S_LOSS_CUR, IMP7,4,1},\
                      { SDI_S_NEG_CUR, IMP7, 4,1},\
                      { SDI_LOSS_VOL,IMP7, 23,5},\
                      { SDI_LOSS_CUR,IMP7, 19,5},\
                      { SDI_NEG_CUR,IMP7, 19,5},\
                      { 0xE144, IMP7, 5, 1},\
                      { 0xE145, IMP7, 5, 1},\
                      { 0xE148, IMP7, 5, 1},\
                      { 0xE149, IMP7, 5, 1},\
                      { 0xE14C, IMP7, 5, 1},\
                      { 0xE14D, IMP7, 5, 1},\
                      {SDI_CLR_ENG_COUNTS, IMP4, 1,1},
//------------------------------默认参数的扩展--------------------------
#define DEF_PARA_EXTEND     {0xE144,1,Zero},\
                            {0xE145,1,Zero},\
                            {0xE148,1,Zero},\
                            {0xE149,1,Zero},\
                            {0xE14C,1,Zero},\
                            {0xE14D,1,Zero},\
                            {SDI_CLR_ENG_COUNTS, 1, Zero}  

//定义失压、失流、反向总次数
typedef struct
{
  INT16U Loss_Vol_Counts[3];//A、B、C三相
  INT16U Loss_Cur_Counts[3];
  INT16U Neg_Cur_Counts[3];
  
  INT8U CS[CS_BYTES];
}S_Grid_Event_Counts;

EXT S_Grid_Event_Counts Grid_Event_Counts;

EXT void Extend_Init();
EXT INT8U Extend_Set_Data_Proc(PROTO_DI DI, INT8U *pSrc, INT16U SrcLen);
EXT INT16U Extend_Event_MultiTimes_Proc(INT8U Event_ID,INT8U Occur_Or_End,INT8U Flag,INT8U *pReturn_Flag);
EXT INT16U Extend_Event_Cumu_Proc(INT8U Event_ID,INT8U Occur_Or_End,INT8U Flag,INT8U *pReturn_Flag);
EXT INT16U Extend_Get_Proto_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start, INT16U DstLen,INT8U *pErr);
EXT INT16U Extend_Get_Single_Proto_Data_Proc(PROTO_DI DI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen, INT8U *pErr);
#endif
#endif
