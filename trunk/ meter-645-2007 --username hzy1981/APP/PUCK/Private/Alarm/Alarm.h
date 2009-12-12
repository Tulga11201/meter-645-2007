#ifndef ALARM_VAR
#define ALARM_VAR


#ifndef ALARM_C
#define ALARM_C_EXT  extern
#else
#define ALARM_C_EXT
#endif


/*
typedef struct
{
  INT8U  PortID;
  INT8U  AlarmBit;
  const  INT8U *AlarmEn;      //声音报警,LCD_LED报警，端子排报警
  INT16U  AlarmWidth;          //输出脉冲宽度：ms
}ALARM_OUT_EN;


CONST ALARM_C_EXT ALARM_OUT_EN Alarm_Mode_Property[]=
{
  INTER_ID_ALARM_BEEP,2, (INT8U *)(&(Mode_Word.Mode[3])),300,     //声音报警允许模式字
  INTER_ID_ALARM_DIS,1, (INT8U *)(&(Mode_Word.Mode[3])),300,      //LED报警模式字
  EXT_ID_AUX_ALARM,0, (INT8U *)(&(Mode_Word.Mode[3])),AUX_PORT_PULSE_WD              //电表及电网状态报警模式字
};

#define ALARM_MODE_NUM (sizeof(Alarm_Mode_Property)/sizeof(ALARM_OUT_EN))

typedef struct
{
  INT8U  EventID;
  const  INT8U *EventEn;      //报警输出使能
  INT8U  EventBit:7;       //bit偏移
  INT8U  ModeEn:1;       //与模式字相关位
}ALARM_OUT_EVENT;

CONST ALARM_C_EXT ALARM_OUT_EVENT Alarm_Event_Property[]={

#ifdef ID_EVENT_A_NEG_CURR
{ID_EVENT_A_NEG_CURR,(INT8U *)(&(Mode_Word.Mode[4])),6,1},
#endif

#ifdef ID_EVENT_B_NEG_CURR
{ID_EVENT_B_NEG_CURR,(INT8U *)(&(Mode_Word.Mode[4])),6,1},
#endif

#ifdef ID_EVENT_C_NEG_CURR
{ID_EVENT_C_NEG_CURR,(INT8U *)(&(Mode_Word.Mode[4])),6,1},
#endif
    
#ifdef ID_EVENT_VOLT_NEG_SEQ
{ID_EVENT_VOLT_NEG_SEQ,(INT8U *)(&(Mode_Word.Mode[4])),5,1},
#endif   
 
#ifdef ID_EVENT_A_LOSS_CURR
{ID_EVENT_A_LOSS_CURR,(INT8U *)(&(Mode_Word.Mode[4])),4,1},
#endif   

#ifdef ID_EVENT_B_LOSS_CURR
{ID_EVENT_B_LOSS_CURR,(INT8U *)(&(Mode_Word.Mode[4])),4,1},
#endif

#ifdef ID_EVENT_C_LOSS_CURR
{ID_EVENT_C_LOSS_CURR,(INT8U *)(&(Mode_Word.Mode[4])),4,1},
#endif

#ifdef ID_EVENT_AB_LOSS_CURR
{ID_EVENT_A_LOSS_CURR,(INT8U *)(&(Mode_Word.Mode[4])),4,1},
#endif   

#ifdef ID_EVENT_BC_LOSS_CURR
{ID_EVENT_B_LOSS_CURR,(INT8U *)(&(Mode_Word.Mode[4])),4,1},
#endif

#ifdef ID_EVENT_AC_LOSS_CURR
{ID_EVENT_C_LOSS_CURR,(INT8U *)(&(Mode_Word.Mode[4])),4,1},
#endif


#ifdef ID_EVENT_A_LOSS_VOLT
{ID_EVENT_A_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_B_LOSS_VOLT
{ID_EVENT_B_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_C_LOSS_VOLT
{ID_EVENT_C_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_AB_LOSS_VOLT
{ID_EVENT_AB_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_BC_LOSS_VOLT
   {ID_EVENT_BC_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_AC_LOSS_VOLT
   {ID_EVENT_AC_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif


#ifdef ID_EVENT_ABC_LOSS_VOLT
   {ID_EVENT_ABC_LOSS_VOLT,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif


#ifdef ID_EVENT_A_LOSS_PARSE
   {ID_EVENT_A_LOSS_PARSE,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif


#ifdef ID_EVENT_B_LOSS_PARSE
   {ID_EVENT_B_LOSS_PARSE,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif


#ifdef ID_EVENT_C_LOSS_PARSE
   {ID_EVENT_C_LOSS_PARSE,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_A_VOLT_OVERLOAD
   {ID_EVENT_A_VOLT_OVERLOAD,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_B_VOLT_OVERLOAD
   {ID_EVENT_B_VOLT_OVERLOAD,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif

#ifdef ID_EVENT_C_VOLT_OVERLOAD
   {ID_EVENT_C_VOLT_OVERLOAD,(INT8U *)(&(Mode_Word.Mode[4])),3,1},
#endif


#ifdef ID_EVENT_RTCERR_RUN
{ID_EVENT_RTCERR_RUN,(INT8U *)(&(Mode_Word.Mode[4])),2,1},
#endif


#ifdef ID_EVENT_EPPROM_FAULT
{ID_EVENT_EPPROM_FAULT,(INT8U *)(&(Mode_Word.Mode[4])),1,1},
#endif

#ifdef ID_EVENT_RTC_BAT_LOW
{ID_EVENT_RTC_BAT_LOW,(INT8U *)(&(Mode_Word.Mode[4])),0,1},
#endif

#ifdef ID_EVENT_LOWPWR_BAT_LOW
{ID_EVENT_LOWPWR_BAT_LOW,(INT8U *)(&(Mode_Word.Mode[4])),0,1},
#endif


#ifdef ID_EVENT_CURR_NO_EVEN    //电流不平衡
{ID_EVENT_CURR_NO_EVEN,(INT8U *)(&(Mode_Word.Mode[4])),7,1},
#endif


#ifdef ID_EVENT_DEMAND_ALARM     //超需量报警
{ID_EVENT_DEMAND_ALARM,0,0,0},
#endif


#ifdef ID_PAY_ALARM             //预付费报警
{ID_PAY_ALARM,0,0,0},
#endif

#ifdef ID_EVENT_CMD_ALARM        //命令报警(通过命令，强行报警)
{ID_EVENT_CMD_ALARM,0,0,0}
#endif


};

#define ALARM_EVENT_NUM (sizeof(Alarm_Event_Property)/sizeof(ALARM_OUT_EVENT))
*/

CONST ALARM_C_EXT INT8U Alarm_Event_Property[]=
{
  ID_EVENT_RTC_BAT_LOW,           //时钟电池欠压
  
  ID_EVENT_A_LOSS_VOLT,
  ID_EVENT_B_LOSS_VOLT,
  ID_EVENT_C_LOSS_VOLT,//失压
  
  ID_EVENT_A_LOSS_PARSE,
  ID_EVENT_B_LOSS_PARSE,
  ID_EVENT_C_LOSS_PARSE,//断相
  
  ID_EVENT_A_VOLT_OVERLOAD,
  ID_EVENT_B_VOLT_OVERLOAD,
  ID_EVENT_C_VOLT_OVERLOAD,//过压
  
  ID_EVENT_VOLT_NEG_SEQ,//电压逆相序
  ID_EVENT_A_LOSS_CURR,
  
  ID_EVENT_B_LOSS_CURR,
  ID_EVENT_C_LOSS_CURR,//失流
  ID_EVENT_CURR_NO_EVEN,//电流不平衡
  ID_EVENT_CUR_NEG_SEQ, //电流逆相序
  
  ID_EVENT_A_OVER_CURR,
  ID_EVENT_B_OVER_CURR,
  ID_EVENT_C_OVER_CURR, //过流
  
  ID_EVENT_POS_ACT_DEMAND_EXCEED,
  ID_EVENT_NEG_ACT_DEMAND_EXCEED,
  ID_EVENT_Q1_REAC_DEMAND_EXCEED,
  ID_EVENT_Q2_REAC_DEMAND_EXCEED,
  ID_EVENT_Q3_REAC_DEMAND_EXCEED,
  ID_EVENT_Q4_REAC_DEMAND_EXCEED,//需量超限
  
  ID_EVENT_A_POWER_EXCEED,
  ID_EVENT_B_POWER_EXCEED,
  ID_EVENT_C_POWER_EXCEED,//过载
  ID_PAY_ALARM
};

#define ALARM_EVENT_NUM (sizeof(Alarm_Event_Property)/sizeof(INT8U))

#endif