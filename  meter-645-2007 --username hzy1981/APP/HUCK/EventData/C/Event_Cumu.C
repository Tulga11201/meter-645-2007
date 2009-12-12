#define EVENT_CUMU_C
#include "Includes.h"
/*
CONST S_DI_Array NULL_DI_ARRAY =
{
  0, {0}
};
*/

#define NULL_DI_ARRAY Zero

CONST S_DI_Array Event_DI_Array[] =
{
  //{.DI_Num=19,{0x9010,0x9110,0x9020,0x9120,0xE701,0xE704,0xE707,0xE70A,0xE702,0xE705,0xE708,0xE70B,0xE703,0xE706,0xE709,0xE70C,DI_A_AH,DI_B_AH,DI_C_AH}},//失压
  //{.DI_Num=16,{0x9010,0x9110,0x9020,0x9120,0xE701,0xE704,0xE707,0xE70A,0xE702,0xE705,0xE708,0xE70B,0xE703,0xE706,0xE709,0xE70C}},//失流
  //{.DI_Num=8,{0x9010,0x9020,0xE701,0xE707,0xE702,0xE708,0xE703,0xE709}},//反向
  //{.DI_Num=0,{0}}//全失压、全失流、断相只计次数和时间

  //失压、断相、失流，反向
  { 20,{
  0x00010000,   //正向有功总, 4
  0x00020000,   //反向有功总, 4
  0x00030000,   //组合无功1, 4
  0x00040000,   //组合无功2, 4

  0x00150000,   //A相正向有功总, 4
  0x00160000,   //A相反向有功总, 4
  0x00170000,   //A相组合无功1,  4
  0x00180000,   //A相组合无功2,  4

  0x00290000,   //B相正向有功总
  0x002A0000,   //B相反向有功总
  0x002B0000,   //B相组合无功1
  0x002C0000,   //B相组合无功2

  0x003D0000,   //C相正向有功总
  0x003E0000,   //C相反向有功总
  0x003F0000,   //C相组合无功1
  0x00400000,   //C相组合无功2

  _PDI_TOTAL_AH,
  _PDI_A_AH,
  _PDI_B_AH,
  _PDI_C_AH
  }
  }
  /*
  {16,
  {
  0x00010000,   //正向有功总, 4
  0x00020000,   //反向有功总, 4
  0x00030000,   //组合无功1, 4
  0x00040000,   //组合无功2, 4

  0x00150000,   //A相正向有功总, 4
  0x00160000,   //A相反向有功总, 4
  0x00170000,   //A相组合无功1,  4
  0x00180000,   //A相组合无功2,  4

  0x00290000,   //B相正向有功总
  0x002A0000,   //B相反向有功总
  0x002B0000,   //B相组合无功1
  0x002C0000,   //B相组合无功2

  0x003D0000,   //C相正向有功总
  0x003E0000,   //C相反向有功总
  0x003F0000,   //C相组合无功1
  0x00400000,   //C相组合无功2

  },
  }
  */
};
/*
//对于事件的累加处理
typedef struct{
  INT8U Event_ID;//事件 ID
  
  //事件的累计时间和次数需要特殊处理
  STORA_DI Counts_DI;//次数累加DI,等同于通信协议DI
  INT8U Counts_Start;
  INT8U Counts_Len;
  
  STORA_DI Mins_DI;//时间累加DI,等同于通信协议DI
  INT8U Mins_Start;
  INT8U Mins_Len;
  
  ///////////////////////上面部分是时间和次数的累加，标准规约里面都有的//////////////////////////////
  
  ///////////////////////下面部分是电能的总累加///////////////////////////
  STORA_DI Occur_Stora_DI;//发生时的电能数据存储DI
  STORA_DI Total_Stora_DI;//总的电能数据的DI,等同于协议DI
  
  INT8U DI_Num;//数据项的个数,不包括累计时间和次数，累计时间和次数是否进入用Counts_Mins_Proto_Flag定义
  //INT8U Counts_Mins_Proto_Flag;//次数和时间是否进入协议数据?
  
  PROTO_DI *pDI;//累加相关的数据项,与通信协议的数据项同
  
  }S_Event_Cumu_Data_Info;
*/
CONST S_Event_Cumu_Data_Info Event_Cumu_Data_Info[] =
{
  //总失压
  {INIT(Event_ID, ID_EVENT_TOTAL_LOSS_VOL),
  INIT(Occur_Stora_DI, EC_DI(0x10000100)),
  INIT(Total_Stora_DI, EC_DI(0x10000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A相失压
  {INIT(Event_ID, ID_EVENT_A_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x10010100)),
  INIT(Total_Stora_DI, EC_DI(0x10010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B相失压
  {INIT(Event_ID, ID_EVENT_B_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x10020100)),
  INIT(Total_Stora_DI, EC_DI(0x10020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C相失压
  {INIT(Event_ID, ID_EVENT_C_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x10030100)),
  INIT(Total_Stora_DI, EC_DI(0x10030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //A相欠压
  {INIT(Event_ID, ID_EVENT_A_VOLT_LESS),
  INIT(Occur_Stora_DI, EC_DI(0x11010100)),
  INIT(Total_Stora_DI, EC_DI(0x11010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B相欠压
  {INIT(Event_ID, ID_EVENT_B_VOLT_LESS),
  INIT(Occur_Stora_DI, EC_DI(0x11020100)),
  INIT(Total_Stora_DI, EC_DI(0x11020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C相欠压
  {INIT(Event_ID, ID_EVENT_C_VOLT_LESS),
  INIT(Occur_Stora_DI, EC_DI(0x11030100)),
  INIT(Total_Stora_DI, EC_DI(0x11030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //A相过压
  {INIT(Event_ID, ID_EVENT_A_VOLT_OVERLOAD),
  INIT(Occur_Stora_DI, EC_DI(0x12010100)),
  INIT(Total_Stora_DI, EC_DI(0x12010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B相过压
  {INIT(Event_ID, ID_EVENT_B_VOLT_OVERLOAD),
  INIT(Occur_Stora_DI, EC_DI(0x12020100)),
  INIT(Total_Stora_DI, EC_DI(0x12020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C相过压
  {INIT(Event_ID, ID_EVENT_C_VOLT_OVERLOAD),
  INIT(Occur_Stora_DI, EC_DI(0x12030100)),
  INIT(Total_Stora_DI, EC_DI(0x12030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //总断相
  {INIT(Event_ID, ID_EVENT_TOTAL_BREAK_VOL),
  INIT(Occur_Stora_DI, EC_DI(0x13000100)),
  INIT(Total_Stora_DI, EC_DI(0x13000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A相断相
  {INIT(Event_ID, ID_EVENT_A_LOSS_PARSE),
  INIT(Occur_Stora_DI, EC_DI(0x13010100)),
  INIT(Total_Stora_DI, EC_DI(0x13010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B相断相
  {INIT(Event_ID, ID_EVENT_B_LOSS_PARSE),
  INIT(Occur_Stora_DI, EC_DI(0x13020100)),
  INIT(Total_Stora_DI, EC_DI(0x13020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C相断相
  {INIT(Event_ID, ID_EVENT_C_LOSS_PARSE),
  INIT(Occur_Stora_DI, EC_DI(0x13030100)),
  INIT(Total_Stora_DI, EC_DI(0x13030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //全失压
  {INIT(Event_ID, ID_EVENT_ALL_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x03050000)),
  INIT(Total_Stora_DI, EC_DI(0x03050001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //辅助电源失电
  {INIT(Event_ID, ID_EVENT_AUX_POWER),
  INIT(Occur_Stora_DI, EC_DI(0x03060000)),
  INIT(Total_Stora_DI, EC_DI(0x03060001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
  //电压逆相序
  {INIT(Event_ID, ID_EVENT_VOLT_NEG_SEQ),
  INIT(Occur_Stora_DI, EC_DI(0x14000100)),
  INIT(Total_Stora_DI, EC_DI(0x14000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //电流逆相序
  {INIT(Event_ID, ID_EVENT_CUR_NEG_SEQ),
  INIT(Occur_Stora_DI, EC_DI(0x15000100)),
  INIT(Total_Stora_DI, EC_DI(0x15000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //电压不平衡
  {INIT(Event_ID, ID_EVENT_VOLT_NO_EVEN),
  INIT(Occur_Stora_DI, EC_DI(0x16000100)),
  INIT(Total_Stora_DI, EC_DI(0x16000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //电流不平衡
  {INIT(Event_ID, ID_EVENT_CURR_NO_EVEN),
  INIT(Occur_Stora_DI, EC_DI(0x17000100)),
  INIT(Total_Stora_DI, EC_DI(0x17000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //总失流
  {INIT(Event_ID, ID_EVENT_TOTAL_LOSS_CUR),
  INIT(Occur_Stora_DI, EC_DI(0x18000100)),
  INIT(Total_Stora_DI, EC_DI(0x18000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A相失流
  {INIT(Event_ID, ID_EVENT_A_LOSS_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x18010100)),
  INIT(Total_Stora_DI, EC_DI(0x18010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B相失流
  {INIT(Event_ID, ID_EVENT_B_LOSS_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x18020100)),
  INIT(Total_Stora_DI, EC_DI(0x18020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C相失流
  {INIT(Event_ID, ID_EVENT_C_LOSS_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x18030100)),
  INIT(Total_Stora_DI, EC_DI(0x18030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //A相过流
  {INIT(Event_ID, ID_EVENT_A_OVER_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x19010100)),
  INIT(Total_Stora_DI, EC_DI(0x19010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B相过流
  {INIT(Event_ID, ID_EVENT_B_OVER_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x19020100)),
  INIT(Total_Stora_DI, EC_DI(0x19020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C相过流
  {INIT(Event_ID, ID_EVENT_C_OVER_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x19030100)),
  INIT(Total_Stora_DI, EC_DI(0x19030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //A相断流
  {INIT(Event_ID, ID_EVENT_A_CUT_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1A010100)),
  INIT(Total_Stora_DI, EC_DI(0x1A010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B相断流
  {INIT(Event_ID, ID_EVENT_B_CUT_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1A020100)),
  INIT(Total_Stora_DI, EC_DI(0x1A020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C相断流
  {INIT(Event_ID, ID_EVENT_C_CUT_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1A030100)),
  INIT(Total_Stora_DI, EC_DI(0x1A030100)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},


  //总反向
  {INIT(Event_ID, ID_EVENT_TOTAL_NEG_CUR),
  INIT(Occur_Stora_DI, EC_DI(0x1B000100)),
  INIT(Total_Stora_DI, EC_DI(0x1B000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A相潮流反向
  {INIT(Event_ID, ID_EVENT_A_NEG_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1B010100)),
  INIT(Total_Stora_DI, EC_DI(0x1B010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B相潮流反向
  {INIT(Event_ID, ID_EVENT_B_NEG_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1B020100)),
  INIT(Total_Stora_DI, EC_DI(0x1B020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C相潮流反向
  {INIT(Event_ID, ID_EVENT_C_NEG_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1B030100)),
  INIT(Total_Stora_DI, EC_DI(0x1B030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //A相过载
  {INIT(Event_ID, ID_EVENT_A_POWER_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x1C010100)),
  INIT(Total_Stora_DI, EC_DI(0x1C010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B相过载
  {INIT(Event_ID, ID_EVENT_B_POWER_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x1C020100)),
  INIT(Total_Stora_DI, EC_DI(0x1C020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C相过载
  {INIT(Event_ID, ID_EVENT_C_POWER_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x1C030100)),
  INIT(Total_Stora_DI, EC_DI(0x1C030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //拉闸
  {INIT(Event_ID, ID_EVENT_RELAY_OFF),
  INIT(Occur_Stora_DI, EC_DI(0x1D000100)),
  INIT(Total_Stora_DI, EC_DI(0x1D000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)}, 
  //合闸
  {INIT(Event_ID, ID_EVENT_RELAY_ON),
  INIT(Occur_Stora_DI, EC_DI(0x1E000100)),
  INIT(Total_Stora_DI, EC_DI(0x1E000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //总功率因素超下限
  {INIT(Event_ID, ID_EVENT_ALL_FACTOR_LOW),
  INIT(Occur_Stora_DI, EC_DI(0x1F000100)),
  INIT(Total_Stora_DI, EC_DI(0x1F000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
  //掉电
  {INIT(Event_ID, ID_EVENT_POWER_OFF),
  INIT(Occur_Stora_DI, EC_DI(0x03110000)),
  INIT(Total_Stora_DI, EC_DI(0x03110001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //正向有功需量超限
  {INIT(Event_ID, ID_EVENT_POS_ACT_DEMAND_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x03120100)),
  INIT(Total_Stora_DI, EC_DI(0x03120101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //反向有功需量超限
  {INIT(Event_ID, ID_EVENT_NEG_ACT_DEMAND_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x03120200)),
  INIT(Total_Stora_DI, EC_DI(0x03120201)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //第一象限无功需量超限
  {INIT(Event_ID, ID_EVENT_Q1_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120300)),
  INIT(Total_Stora_DI, EC_DI(0x03120301)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //第二象限无功需量超限
  {INIT(Event_ID, ID_EVENT_Q2_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120400)),
  INIT(Total_Stora_DI, EC_DI(0x03120401)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //第三象限无功需量超限
  {INIT(Event_ID, ID_EVENT_Q3_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120500)),
  INIT(Total_Stora_DI, EC_DI(0x03120501)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //第四象限无功需量超限
  {INIT(Event_ID, ID_EVENT_Q4_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120600)),
  INIT(Total_Stora_DI, EC_DI(0x03120601)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //编程记录
  {INIT(Event_ID, ID_EVENT_PROG),
  INIT(Occur_Stora_DI, EC_DI(0x03300000)),
  INIT(Total_Stora_DI, EC_DI(0x03300001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //电表清零记录
  {INIT(Event_ID, ID_EVENT_CLR_ALL_DATA),
  INIT(Occur_Stora_DI, EC_DI(0x03300100)),
  INIT(Total_Stora_DI, EC_DI(0x03300101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,0)},

  //需量清零记录
  {INIT(Event_ID, ID_EVENT_CLR_DEMAND_COM),
  INIT(Occur_Stora_DI, EC_DI(0x03300200)),
  INIT(Total_Stora_DI, EC_DI(0x03300201)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //事件清零记录
  {INIT(Event_ID, ID_EVENT_CLR_PROCESS),
  INIT(Occur_Stora_DI, EC_DI(0x03300300)),
  INIT(Total_Stora_DI, EC_DI(0x03300301)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,0)},

  //校时记录
  {INIT(Event_ID, ID_EVENT_ADJUST_TIME),
  INIT(Occur_Stora_DI, EC_DI(0x03300400)),
  INIT(Total_Stora_DI, EC_DI(0x03300401)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //时段表编程
  {INIT(Event_ID, ID_EVENT_DATE),
  INIT(Occur_Stora_DI, EC_DI(0x03300500)),
  INIT(Total_Stora_DI, EC_DI(0x03300501)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //时区表编程
  {INIT(Event_ID, ID_EVENT_YEAR),
  INIT(Occur_Stora_DI, EC_DI(0x03300600)),
  INIT(Total_Stora_DI, EC_DI(0x03300601)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //周休日编程
  {INIT(Event_ID, ID_EVENT_WEEK),
  INIT(Occur_Stora_DI, EC_DI(0x03300700)),
  INIT(Total_Stora_DI, EC_DI(0x03300701)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //节假日编程
  {INIT(Event_ID, ID_EVENT_HOLIDAY),
  INIT(Occur_Stora_DI, EC_DI(0x03300800)),
  INIT(Total_Stora_DI, EC_DI(0x03300801)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //有功组合方式编程
  {INIT(Event_ID, ID_EVENT_ACPWR),
  INIT(Occur_Stora_DI, EC_DI(0x03300900)),
  INIT(Total_Stora_DI, EC_DI(0x03300901)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //无功组合方式1编程
  {INIT(Event_ID, ID_EVENT_REACPWR1),
  INIT(Occur_Stora_DI, EC_DI(0x03300A00)),
  INIT(Total_Stora_DI, EC_DI(0x03300A01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //无功组合方式2编程
  {INIT(Event_ID, ID_EVENT_REACPWR2),
  INIT(Occur_Stora_DI, EC_DI(0x03300B00)),
  INIT(Total_Stora_DI, EC_DI(0x03300B00)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //结算日编程
  {INIT(Event_ID, ID_EVENT_SETTLE_DATE),
  INIT(Occur_Stora_DI, EC_DI(0x03300C00)),
  INIT(Total_Stora_DI, EC_DI(0x03300C01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //开表盖
  {INIT(Event_ID, ID_EVENT_UP_COVER_OPEN),
  INIT(Occur_Stora_DI, EC_DI(0x03300D00)),
  INIT(Total_Stora_DI, EC_DI(0x03300D01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //开端钮盒
  {INIT(Event_ID, ID_EVENT_DOWN_COVER_OPEN),
  INIT(Occur_Stora_DI, EC_DI(0x03300E00)),
  INIT(Total_Stora_DI, EC_DI(0x03300E01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},


  //低功耗电池欠压
  {INIT(Event_ID, ID_EVENT_LOWPWR_BAT_LOW),
  INIT(Occur_Stora_DI, EC_DI(0x03410000)),
  INIT(Total_Stora_DI, EC_DI(0x03410001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //时钟电池欠压
  {INIT(Event_ID, ID_EVENT_RTC_BAT_LOW),
  INIT(Occur_Stora_DI, EC_DI(0x03410100)),
  INIT(Total_Stora_DI, EC_DI(0x03410101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //负控报警
  {INIT(Event_ID, ID_EVENT_DEMAND_ALARM),
  INIT(Occur_Stora_DI, EC_DI(0x03420000)),
  INIT(Total_Stora_DI, EC_DI(0x03420001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
/*
  //负控跳闸
  {INIT(Event_ID, ID_EVENT_DEMAND_SWITCH),
  INIT(Occur_Stora_DI, EC_DI(0x03420100)),
  INIT(Total_Stora_DI, EC_DI(0x03420101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
*/
  //复位
  {INIT(Event_ID, ID_EVENT_RESET),
  INIT(Occur_Stora_DI, EC_DI(0x0E180000)),
  INIT(Total_Stora_DI, EC_DI(0x0E180001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //运行时钟乱
  {INIT(Event_ID, ID_EVENT_RTCERR_RUN),
  INIT(Occur_Stora_DI, EC_DI(0x0E190000)),
  INIT(Total_Stora_DI, EC_DI(0x0E190001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //上电时钟乱
  {INIT(Event_ID, ID_EVENT_RTCERR_PWRON),
  INIT(Occur_Stora_DI, EC_DI(0x0E1C0000)),
  INIT(Total_Stora_DI, EC_DI(0x0E1C0001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
  
  //设置初始电量
  {INIT(Event_ID, ID_EVENT_SET_ENERG),
  INIT(Occur_Stora_DI, EC_DI(0x0E301100)),
  INIT(Total_Stora_DI, EC_DI(0x0E301101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,0)},

  EXTEND_EVENT_CUMU
}; 

//单事件与总事件的对应关系
CONST INT8U Single_Total_Event_Map[][2] =
{
  //失压
  {ID_EVENT_A_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  {ID_EVENT_B_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  {ID_EVENT_C_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_AB_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_AC_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_BC_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_ABC_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  {ID_EVENT_ALL_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL},
  //失流
  {ID_EVENT_A_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  {ID_EVENT_B_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  {ID_EVENT_C_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_AB_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_AC_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_BC_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_ALL_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //反向
  {ID_EVENT_A_NEG_CURR, ID_EVENT_TOTAL_NEG_CUR}, 
  {ID_EVENT_B_NEG_CURR, ID_EVENT_TOTAL_NEG_CUR}, 
  {ID_EVENT_C_NEG_CURR, ID_EVENT_TOTAL_NEG_CUR},
  //断相
  {ID_EVENT_A_LOSS_PARSE, ID_EVENT_TOTAL_BREAK_VOL},
  {ID_EVENT_B_LOSS_PARSE, ID_EVENT_TOTAL_BREAK_VOL}, 
  {ID_EVENT_C_LOSS_PARSE, ID_EVENT_TOTAL_BREAK_VOL}, 
};

//判断某个累计事件是否在发生，包括总一类事件
INT8U Check_Cumu_Event_Occuring(INT8U Event_ID)
{
  INT8U i;

  TRACE();
  for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
  {
    if(Single_Total_Event_Map[i][0] == Event_ID || \
       Single_Total_Event_Map[i][1] == Event_ID)
    {
      if(Read_Event_Status(Single_Total_Event_Map[i][0]))
      {
        return 1;
      }
    }
  }
  return 0;
}

//获取某一事件对应的总事件ID
INT8U Get_Total_Event_ID(INT8U Event_ID)
{
  INT8U i;

  TRACE();
  for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
  {
    if(Single_Total_Event_Map[i][0] == Event_ID || \
       Single_Total_Event_Map[i][1] == Event_ID)
    {
      return Single_Total_Event_Map[i][1];
    }
  }
  return NULL_EVENT_ID;
}

//检查某个事件ID是否是一个累计事件ID
INT8U Check_Total_Event_ID(INT8U Event_ID)
{
	INT8U i;

    TRACE();
	
	for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
	{
		if(Single_Total_Event_Map[i][1] EQ Event_ID)
		{
			return 1;
		}
	}
	return 0; 
}

//获取某个总事件对应的单独事件正在发生的个数
INT8U Get_Event_Total_Occuring_Singles(INT8U Event_ID)
{
	INT8U i;
	INT8U Counts;

    TRACE();	
	Counts = 0;
	for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
	{
		if(Single_Total_Event_Map[i][1] EQ Event_ID)//总事件
		{
			if(Read_Event_Status(Single_Total_Event_Map[i][0]))
				Counts ++;
		}
	}  
	return Counts;
}

//获取协议数据，专给事件提供，电量等有3位小数，防止误差产生.
//DI标识码
//DI_Num标识个数
//pDst目标缓冲区
//pDst_Start和DstLen一起限定目标缓冲区
INT16U Get_Multi_Proto_Data(PROTO_DI PDI[], INT8U DI_Num, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT8U i, Next_Flag;
  INT16U Len, TempLen;

  TRACE();

  Len = 0;

  if(!(pDst >= pDst_Start && pDst < pDst_Start + DstLen))
  {
	  ASSERT_FAILED();
	  return 0;
  }

  for(i = 0; i < DI_Num; i ++)
  {
    TempLen = _Get_DLT645_Data(PDI[i], (void *) 0, 0, pDst + Len, pDst_Start, DstLen, Data_Flag, &Next_Flag);  
    if(TempLen EQ 0)
      ASSERT_FAILED();
    Len += TempLen;
  }

  return Len;
}

//获取某个事件在Event_Cumu_Data_Info中的索引 
//Event_ID表示时间的ID
INT16U Get_Event_Cumu_Data_Index(INT8U Event_ID)
{
  INT16U i;

  TRACE();

  for(i = 0; i < S_NUM(Event_Cumu_Data_Info); i++)
  {
    if(Event_Cumu_Data_Info[i].Event_ID EQ Event_ID)
    {
      return i;
    }
  }

  return NULL_2BYTES;
}

//获取某个累计事件的累计数据在Event_Cumu_Data_Info中的索引
//PDI表示协议中的索引值
INT16U Get_Event_Cumu_Proto_Index(PROTO_DI PDI)
{
  INT16U i;

  TRACE();
  for(i = 0; i < S_NUM(Event_Cumu_Data_Info); i ++)
  {
    if(Event_Cumu_Data_Info[i].Total_Stora_DI EQ PDI)
    {
      return i;
    }
  }

  return NULL_2BYTES;
}
/*
//对事件累计次数的处理
//Index表示Event_Cumu_Data_Info中的索引
void Event_Cumu_Counts_Proc(INT16U Index, INT32U Counts, INT8U Flag)
{
  //INT32U Counts;
  INT16U Len, Len1;

  TRACE();

  if(Flag != EVENT_REAL)
  {
    return;
  }

  if(Event_Cumu_Data_Info[Index].Counts_DI EQ NULL_STORA_DI)//不需要计总数
  {
    return;
  }

  Len1 = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Counts_DI);
  mem_set(Pub_Buf0, 0, Len1, Pub_Buf0, sizeof(Pub_Buf0));
  //读取并且重写累计次数
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Counts_DI, Pub_Buf0, Pub_Buf0, sizeof(Pub_Buf0));
  ASSERT(Len1 EQ Len);

  if(!((INT16U) (Event_Cumu_Data_Info[Index].Counts_Start + Event_Cumu_Data_Info[Index].Counts_Len) <= Len))
  {
    mem_set(Pub_Buf0, 0, Len, Pub_Buf0, sizeof(Pub_Buf0));
    ASSERT_FAILED();
  }

  Hex2Bcd(Counts, Pub_Buf0 + Event_Cumu_Data_Info[Index].Counts_Start, Event_Cumu_Data_Info[Index].Counts_Len, Pub_Buf0, sizeof(Pub_Buf0));
  
  if(EVENT_REAL EQ Flag)
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Counts_DI, Pub_Buf0, Len1);

  return;
}

//对事件累计次数的处理
//Index表示Event_Cumu_Data_Info中的索引
void Event_Cumu_Mins_Proc(INT16U Index, INT32U Mins, INT8U Flag)
{
  //INT32U Counts;
  INT16U Len, Len1;

  TRACE();
  if(Flag != EVENT_REAL)
  {
    return;
  }

  if(Event_Cumu_Data_Info[Index].Mins_DI EQ NULL_STORA_DI)
  {
    return;
  }

  Len1 = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Mins_DI);
  mem_set(Pub_Buf0, 0, Len1, Pub_Buf0, sizeof(Pub_Buf0));
  //读取并且重写累计次数
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Mins_DI, Pub_Buf0, Pub_Buf0, sizeof(Pub_Buf0));
  ASSERT(Len1 EQ Len);

  if(!((INT16U) (Event_Cumu_Data_Info[Index].Mins_Start + Event_Cumu_Data_Info[Index].Mins_Len) <= Len))
  {
    mem_set(Pub_Buf0, 0, Len, Pub_Buf0, sizeof(Pub_Buf0));
    ASSERT_FAILED();
  }

  Hex2Bcd(Mins, Pub_Buf0 + Event_Cumu_Data_Info[Index].Mins_Start, Event_Cumu_Data_Info[Index].Mins_Len, Pub_Buf0, sizeof(Pub_Buf0));
  
  if(EVENT_REAL EQ Flag)
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Mins_DI, Pub_Buf0, Len1);

  return;
}
*/
//事件发生时的累计处理
//Index为事件在Event_Cumu_Data_Info数组中的索引
INT16U Event_Cumu_Start_Proc(INT16U Index, INT8U Flag)
{
  INT32U Counts, Mins;
  INT16U Len;
  //INT8U Err;
  TRACE();
  if(Event_Cumu_Data_Info[Index].Occur_Stora_DI EQ NULL_STORA_DI)
  {
    return 0;
  }

  //从发生时数据区读取次数和分钟计数
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len > 0)
  {
    Counts = 0;
    mem_cpy(&Counts, (INT8U *) Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));      
    Mins = 0;
    mem_cpy(&Mins, (INT8U *) Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));
  }
  else //没有读到则从总累计区读取
  {
    Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    if(Len > 0)
    {
      Counts = 0;
      mem_cpy(&Counts, (INT8U *) Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));   
      Mins = 0;
      mem_cpy(&Mins, (INT8U *) Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));
    }
    else
    {
      ASSERT_FAILED();
      Mins = 0;//实在是没有办法读到正确的次数数据了,则置0
      Counts = 0;
    }
  }
  Counts ++;

  Debug_Print("Event Occur Index=%d,Counts=%lu,Mins=%lu,Start_Min=%lu", Index, Counts, Mins, Event_Data.Min_Timer);
  
  //当前是总累加事件，且已经有独立事件发生了的，只对发生次数进行增加处理
  if(Check_Total_Event_ID(Event_Cumu_Data_Info[Index].Event_ID) &&\
     Get_Event_Total_Occuring_Singles(Event_Cumu_Data_Info[Index].Event_ID) != 0 &&\
     EVENT_REAL EQ Flag)//真实事件才存储
  {
    Debug_Print("Total_Event Occuring...");
    mem_cpy((INT8U *) Pub_Buf0 + 5, &Counts, 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));//4字节累计次数
    Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Occur_Stora_DI);    
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *)Pub_Buf0, Len);//将发生时的数据存入ROM)
    return Len;
  } 

  //Event_Cumu_Counts_Proc(Index, Counts, Flag);//事件次数单独处理

  Pub_Buf0[0] = EVENT_OCCUR;//1字节头，表示事件进入发生态
  mem_cpy((INT8U *) Pub_Buf0 + 1, (INT8U *) &Event_Data.Min_Timer, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));//4字节当前分计数
  mem_cpy((INT8U *) Pub_Buf0 + 5, &Counts, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));//4字节累计次数
  mem_cpy((INT8U *) Pub_Buf0 + 9, &Mins, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));//4字节累计分钟
  Len = 13;
  //除了次数和时间还需要记录其他的累加量，则需要在事件发生时存储瞬时量
  Len += Get_Multi_Proto_Data((PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array -> PDI, Event_Cumu_Data_Info[Index].pDI_Array -> DI_Num, (INT8U *) Pub_Buf0 + Len, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0), FOR_SRC | FOR_EVENT);  

  if(EVENT_REAL EQ Flag)//真实事件才存储
  {
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, Len);//将发生时的数据存入ROM
  }
  
  return Len;
}

//事件结束时的累计处理
//Flag:0表示真实的处理一次事件结束，1表示虚拟一次结束，但是不存储到EEROM中，而是将累计数据存储到Pub_Buf0开始的缓冲区中
INT16U Event_Cumu_End_Proc(INT16U Index, INT8U Flag)
{
  INT8U* p;
  INT16U Len, Len1;
  INT32U Counts, Mins;
  INT32U Timer;

  TRACE();
  //OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  //读取发生时存储的瞬时量
  if(Event_Cumu_Data_Info[Index].Occur_Stora_DI EQ NULL_STORA_DI)
  {
    return 0;
  }

  //当前是总累加事件，且该累加还有某些独立事件在发生，则不进行处理
  if(Check_Total_Event_ID(Event_Cumu_Data_Info[Index].Event_ID) &&\
     Get_Event_Total_Occuring_Singles(Event_Cumu_Data_Info[Index].Event_ID) > 1 &&\
     EVENT_REAL EQ Flag)//真实事件才存储
  {
    Debug_Print("Total_Event Occuring...");
    return 0;
  } 

  //先读取最近一次发生时的记录  
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len EQ 0 || Pub_Buf0[0] != EVENT_OCCUR)//没有事件发生记录
  {
    ASSERT_FAILED();
    if(Len EQ 0)
      Debug_Print("Read Event_Cumu_Data_Info error Len=0, Index=%d", Index);
    else
      Debug_Print("Read Event_Cumu_Data_Info Occcur_Flag=0x%x error ", Pub_Buf0[0]);

    return 0;
  }
  else//将档次累计数据存入总累计
  {
    //总的次数
    mem_cpy(&Counts, (INT8U *) Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));   
    //总的累计分钟
    mem_cpy(&Mins, (INT8U *) Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));
    //读取发生时的分钟计数,当前分钟计数 - 发生时的分钟计数 = 当次发生的分钟数
    mem_cpy(&Timer, (INT8U *) Pub_Buf0 + 1, 4, &Timer, sizeof(Timer));//发生时的分钟计数

    if(Event_Data.Min_Timer >= Timer && Timer != 0)
    {
      Mins += (Event_Data.Min_Timer > Timer) ? (Event_Data.Min_Timer - Timer) : 1;
      if(Mins >= 999999)
        Mins = 0;
    }
    else
      Mins = 0;

    Debug_Print("Event End Index=%d,Counts=%lu,Mins=%lu,Start_Min=%lu,End_Min=%lu", Index, Counts, Mins, Timer, Event_Data.Min_Timer);

    //Event_Cumu_Mins_Proc(Index, Mins, Flag);

    Pub_Buf0[0] = EVENT_END;//置事件结束标志
    mem_cpy((INT8U *) Pub_Buf0 + 5, &Counts, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    mem_cpy((INT8U *) Pub_Buf0 + 9, &Mins, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    Len = 13;

    p = (INT8U *) Pub_Buf0 + (sizeof(Pub_Buf0) / 2);

    //读取当前时刻的电量等数据, 放入p开始的缓冲区
    Get_Multi_Proto_Data((PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array ->PDI, Event_Cumu_Data_Info[Index].pDI_Array ->DI_Num, p,\
						  (INT8U *) Pub_Buf0, sizeof(Pub_Buf0), FOR_SRC);

    //将当前电量与事件发生时的电量相减,并将结果放入Pub_Buf0+13开始的目标缓冲区中
    Proto_Data_Add_Dec(FOR_SRC, DATA_DEC, (PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array ->PDI, Event_Cumu_Data_Info[Index].pDI_Array -> DI_Num, p, (INT8U *) Pub_Buf0 + 13,\
					   (INT8U *) Pub_Buf0 + 13, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));

    //至此所有的差值都计算完毕, 并放在了 Pub_Buf0+13 开始的缓冲区中

    //读出总的累计量到p 开始的buf,然后将当此的差量计入累加量
    Len1 = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, p, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    ASSERT(Len1 > 0);

    //将当次事件累加量计入总的累加量,放到Pub_Buf+13 开始的buf
    Len += Proto_Data_Add_Dec(FOR_SRC, DATA_ADD, (PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array ->PDI, Event_Cumu_Data_Info[Index].pDI_Array ->DI_Num, p + 13, (INT8U *) Pub_Buf0 + 13,
                             (INT8U *) Pub_Buf0 + Len, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));

    if(Flag EQ EVENT_REAL)//虚拟事件结束时不存储事件
    {
      Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, Len);//更新发生时的数据，发生时数据也应该存储累计次数和时间
      Write_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *) Pub_Buf0, Len);
    }
  }
  return Len;
}

//获取累计时间的次数和分钟数
void Get_Event_Cumu_Counts_Mins(INT8U Event_ID, INT32U *pCounts, INT32U *pMins)
{
  INT16U Index;
  INT16U Len;
  INT32U Timer;
  
  *pCounts = 0;
  *pMins = 0;
    
  Index = Get_Event_Cumu_Data_Index(Event_ID);//找到事件的索引
  if(NULL_2BYTES EQ Index)
    return ;
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len EQ 0)
    Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));

  if(Len > 0)
  {
    //总的次数
    mem_cpy(pCounts, (INT8U *) Pub_Buf0 + 5, 4, pCounts, 4);   
    //总的累计分钟
    mem_cpy(pMins, (INT8U *) Pub_Buf0 + 9, 4, pMins, 4);
  
    //当前事件在发生
    if(Check_Event_Occuring(Event_ID) && Pub_Buf0[0] EQ EVENT_OCCUR)
    {
      //读取发生时的分钟计数,当前分钟计数 - 发生时的分钟计数 = 当次发生的分钟数
      mem_cpy(&Timer, (INT8U *) Pub_Buf0 + 1, 4, &Timer, sizeof(Timer));//发生时的分钟计数
      
      if(Event_Data.Min_Timer >= Timer && Timer != 0)
      {
        *pMins += (Event_Data.Min_Timer > Timer) ? (Event_Data.Min_Timer - Timer) : 1;
        if(*pMins >= 999999)
          *pMins = 0;
      }
      else
        *pMins = 0;       
    }
  }
  
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}

//获取某事件的累计次数和累计时间，BCD码
//前3字节是累计次数
//后3字节是累计时间
void Get_Event_Cumu_BCD_Counts_Mins(INT8U Event_ID, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  INT32U Counts, Mins;
  
  Get_Event_Cumu_Counts_Mins(Event_ID, &Counts, &Mins);
  
  if(Event_ID EQ ID_EVENT_PROG && Prog_Record.Prog_Flag.All_Flag != 0)//当前处于一个编程的过程中，编程次数应该+1
     Counts ++;
     
  Hex2Bcd(Counts, pDst, 3, pDst_Start, DstLen);
  Hex2Bcd(Mins, pDst + 3, 3, pDst_Start, DstLen);   
}

INT16U Get_Cumu_Event_Num()
{
	  //TRACE();
  return S_NUM(Event_Cumu_Data_Info);
}

INT16U Event_Cumu_Data_Spec_Proc(INT8U Event_ID, INT8U Start_End_Flag)
{
  TRACE();
  return 0;
}

//事件分钟计数
void Event_Cumu_Mins_Accu()
{
  INT8U Re;
  static S_Int8U Min_Bak = {CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE,0xFF,CHK_BYTE}; 
    
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Min_Bak); 
  ASSERT(1 EQ Re);
  
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;
  
  Re = CHECK_STRUCT_SUM(Event_Data);
  ASSERT(1==Re);

  DIS_PD_INT;
  mem_cpy((void *)&Event_Data.Time, (void *)&Cur_Time1, sizeof(Cur_Time1), (void *)&Event_Data.Time, sizeof(Event_Data.Time));
  SET_STRUCT_SUM(Event_Data);
  
  if(Min_Bak.Var != Cur_Time1.Min)
  {
     Min_Bak.Var = Cur_Time1.Min;
     Event_Data.Min_Timer ++ ;
     SET_STRUCT_SUM(Event_Data);
     
     Accmu_RTC_BatTime_PerMin(); //电池工作时间分钟计数
  }
  EN_PD_INT;
}

//事件累加处理
//Event_ID表示事件ID
//Occur_Or_End,0表示发生,1表示结束
INT16U Event_Cumu_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag)
{
  INT8U Return_Flag;
  INT16U Index;
  INT16U Len;

  TRACE();
  
  Debug_Print("Event_Cumu_Proc ID:%d",Event_ID);
  
  Len = Extend_Event_Cumu_Proc(Event_ID, Occur_Or_End, Flag, &Return_Flag);
  if(Return_Flag EQ 1)
  {
    return Len;
  }

  //事件在Event_Cumu_Info结构体中的索引
  Index = Get_Event_Cumu_Data_Index(Event_ID);
  if(Index EQ NULL_2BYTES)
  {
    return 0;
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  
  if(Occur_Or_End EQ EVENT_OCCUR)//事件发生时,保存好事件发生时的某些瞬时量，待事件结束时，计算其累加量
  {
    Len = Event_Cumu_Start_Proc(Index, Flag);
  }
  else//事件结束时
  {
    Len = Event_Cumu_End_Proc(Index, Flag);
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  
  return Len;
}

//清楚某个独立事件的总累计数据
INT8U Clear_One_Event_Cumu_Data(INT8U Event_ID)
{
  INT16U Index;
  INT16U Len;
  
  
  Index = Get_Event_Cumu_Data_Index(Event_ID);
  if(Index EQ NULL_2BYTES)
    return 0;
  
  if(Event_Cumu_Data_Info[Index].Clr_Flag EQ 0)//Clr_Flag==0表示不清除该数据
    return 0;
  
  DISP_CLR_DATA_INFO;
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
  
  if(Event_Cumu_Data_Info[Index].Occur_Stora_DI != NULL_STORA_DI)
  {
    Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Occur_Stora_DI);
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *)Pub_Buf0, Len);
  }

  if(Event_Cumu_Data_Info[Index].Total_Stora_DI != NULL_STORA_DI)
  {
    Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Total_Stora_DI);
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *)Pub_Buf0, Len);
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);  
  return 1;
}

//设置默认的事件参数与数据
//请分次事件数据
//Clr_Flag 0表示只清Event_Cumu_Data_Info[i].Clr_Flag==1的数据
//Clr_Flag 1表示清楚所有的分次事件数据
void Clr_Event_Cumu_Data(INT8U Clr_Flag)
{
  INT16U i, Len;

  TRACE();
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
  for(i = 0; i < S_NUM(Event_Cumu_Data_Info); i ++)
  {
    if(Event_Cumu_Data_Info[i].Clr_Flag EQ 0 && Clr_Flag EQ 0)//Clr_Flag==0表示不清除该数据
      continue;
    
    if(Event_Cumu_Data_Info[i].Occur_Stora_DI != NULL_STORA_DI)
    {
      Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[i].Occur_Stora_DI);
      Write_Storage_Data(Event_Cumu_Data_Info[i].Occur_Stora_DI, (INT8U *)Pub_Buf0, Len);
    }

    if(Event_Cumu_Data_Info[i].Total_Stora_DI != NULL_STORA_DI)
    {
      Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[i].Total_Stora_DI);
      Write_Storage_Data(Event_Cumu_Data_Info[i].Total_Stora_DI, (INT8U *)Pub_Buf0, Len);
    }
  }
  
  //Write_Storage_Data(0x03050000, (INT8U *)Pub_Buf0, 6); //全失压累计次数和时间，单独清除
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  
  Clr_Event_PD_Data(); //清除掉电数据
}

//设置默认的累计事件数据,所有累计数据都清0
void Set_Def_Event_Cumu_Data()
{
  Clr_Event_Cumu_Data(1);  
}

//清除累计事件数据，注意：有些记录是永久记录的，永不清除
void Clear_Event_Cumu_Data()
{
  Clr_Event_Cumu_Data(0);  
}
#undef EVENT_CUMU_C

