#ifndef EVENTPUB_VAR
#define EVENTPUB_VAR


#ifndef EVENTPUB_C
#define EVENTPUB_C_EXT  extern volatile
#else
#define EVENTPUB_C_EXT volatile
#endif



//以下是事件定义ID,单独定义，与协议无关,注意：保证所有事件一定是连续的，宏修改时需注意！
#define ID_EVENT_NO_VALID           0  	                      //无效事件--------0
#define ID_EVENT_A_LOSS_VOLT        (ID_EVENT_NO_VALID+1)  	       //A相失压--------1
#define ID_EVENT_B_LOSS_VOLT        (ID_EVENT_A_LOSS_VOLT+1)  	      //B相失压--------2
#define ID_EVENT_C_LOSS_VOLT        (ID_EVENT_B_LOSS_VOLT+1)	      //C相失压--------3

#define ID_EVENT_A_LOSS_CURR        (ID_EVENT_C_LOSS_VOLT+1)         //A相失流--------4
#define ID_EVENT_B_LOSS_CURR        (ID_EVENT_A_LOSS_CURR+1)  	      //B相失流--------5
#define ID_EVENT_C_LOSS_CURR        (ID_EVENT_B_LOSS_CURR+1)	      //C相失流--------6

#define ID_EVENT_PRGKEY_ON          (ID_EVENT_C_LOSS_CURR+1)         //编程键打开--------7

#define ID_EVENT_CUR_NEG_SEQ        (ID_EVENT_PRGKEY_ON+1)           //电流逆相序--------8
#define ID_EVENT_VOLT_NEG_SEQ       (ID_EVENT_CUR_NEG_SEQ+1)        //电压逆相序--------9

#define ID_EVENT_A_VOLT_LESS        (ID_EVENT_VOLT_NEG_SEQ+1)        //A相电压欠压--------10
#define ID_EVENT_B_VOLT_LESS        (ID_EVENT_A_VOLT_LESS+1)        //B相电压欠压--------11
#define ID_EVENT_C_VOLT_LESS        (ID_EVENT_B_VOLT_LESS+1)	      //C相电压欠压--------12

#define ID_EVENT_DEMAND_ALARM       (ID_EVENT_C_VOLT_LESS+1)         //超需量报警--------13
//#define ID_EVENT_DEMAND_SWITCH      (ID_EVENT_DEMAND_ALARM+1)        //超需量跳闸--------14
#define ID_EVENT_VOLT_NO_EVEN       (ID_EVENT_DEMAND_ALARM+1)      //电压不平衡--------15
#define ID_EVENT_RESET              (ID_EVENT_VOLT_NO_EVEN+1)        //复位--------16
#define ID_EVENT_CLR_DEMAND_COM     (ID_EVENT_RESET+1)             //通信清需量--------17
#define ID_EVENT_CLR_DEMAND_MAN     (ID_EVENT_CLR_DEMAND_COM+1)    //手动清需量--------18
#define ID_EVENT_CLR_PROCESS        (ID_EVENT_CLR_DEMAND_MAN+1)    //清过程--------19
//#define ID_EVENT_CLR_VOLT_PASS      (ID_EVENT_CLR_PROCESS+1)      //清电压合格率--------20
#define ID_EVENT_SET_ENERG          (ID_EVENT_CLR_PROCESS+1)      //设置初始电量--------21
#define ID_EVENT_UP_COVER_OPEN      (ID_EVENT_SET_ENERG+1)        //开大盖--------22
//#define ID_EVENT_LEAD_COVER_OPEN    (ID_EVENT_UP_COVER_OPEN+1)    //开铅封门--------23
#define ID_EVENT_RTC_BAT_LOW        (ID_EVENT_UP_COVER_OPEN+1)     //时钟电池欠压--------24
#define ID_EVENT_LOWPWR_BAT_LOW     (ID_EVENT_RTC_BAT_LOW+1)     //低功耗电池欠压--------25
#define ID_EVENT_ADJUST_TIME        (ID_EVENT_LOWPWR_BAT_LOW+1)   //校时--------26
#define ID_EVENT_RTCERR_RUN         (ID_EVENT_ADJUST_TIME+1)      //运行时钟乱--------27
#define ID_EVENT_RTCERR_PWRON       (ID_EVENT_RTCERR_RUN+1)      //上电时钟乱--------28
//#define ID_EVENT_EPPROM_FAULT       (ID_EVENT_RTCERR_PWRON+1)    //EEPROM坏--------29
//#define ID_EVENT_ADJUST_MEASU       (ID_EVENT_EPPROM_FAULT+1)    //校表--------30
//#define ID_EVENT_MODI_ENERG         (ID_EVENT_EPPROM_FAULT+1)    //电量纠错--------31

#define ID_EVENT_A_VOLT_OVERLOAD    (ID_EVENT_RTCERR_PWRON+1)        //A相电压过压--------32
#define ID_EVENT_B_VOLT_OVERLOAD    (ID_EVENT_A_VOLT_OVERLOAD+1)   //B相电压过压--------33
#define ID_EVENT_C_VOLT_OVERLOAD    (ID_EVENT_B_VOLT_OVERLOAD+1)   //C相电压过压--------34
//#define ID_EVENT_ENERG_FREEZ        (ID_EVENT_C_VOLT_OVERLOAD+1)   //电量冻结--------35


//#define ID_EVENT_POWER_ALARM        (ID_EVENT_C_VOLT_OVERLOAD+1)      //超功率-------------36
//#define ID_EVENT_POWER_SWITCH       (ID_EVENT_POWER_ALARM+1)       //超功率跳闸--------37


#define ID_EVENT_A_LOSS_PARSE       (ID_EVENT_C_VOLT_OVERLOAD+1)     //A相断相--------38
#define ID_EVENT_B_LOSS_PARSE       (ID_EVENT_A_LOSS_PARSE+1)         //B相断相--------39
#define ID_EVENT_C_LOSS_PARSE       (ID_EVENT_B_LOSS_PARSE+1)         //C相断相--------40

#define ID_EVENT_A_NEG_CURR         (ID_EVENT_C_LOSS_PARSE+1)        //A相电流反向--------41
#define ID_EVENT_B_NEG_CURR         (ID_EVENT_A_NEG_CURR+1)          //B相电流反向--------42
#define ID_EVENT_C_NEG_CURR         (ID_EVENT_B_NEG_CURR+1)          //C相电流反向--------43
#define ID_EVENT_SUM_NEG_CURR       (ID_EVENT_C_NEG_CURR+1)         //总电流反向（有功功率反相）--------44
#define ID_EVENT_CMD_ALARM          (ID_EVENT_SUM_NEG_CURR+1)     //命令报警(通过命令，强行报警)--------45
#define ID_EVENT_ERR_PASSWD         (ID_EVENT_CMD_ALARM+1)         //密码错--------46

#define ID_EVENT_METER_LOCK         (ID_EVENT_ERR_PASSWD+1)       //对电表编程(设置重要参数)时，若密码连续出错次数大于等于5次后--------47

#if METER_DEBUG_EN
  #define ID_EVENT_AB_FUNC_KEY        (ID_EVENT_METER_LOCK+1)         //AB切换功能键识别--------48
  #define ID_EVENT_POWER_OFF          (ID_EVENT_AB_FUNC_KEY+1)        //掉电事件--------49----PUCK 
#else
  //#define ID_EVENT_AB_FUNC_KEY        (ID_EVENT_METER_LOCK+1)         //AB切换功能键识别--------48
  #define ID_EVENT_POWER_OFF          (ID_EVENT_METER_LOCK+1)        //掉电事件--------49----PUCK 
#endif

#define ID_DEMAND_ARRIVE            (ID_EVENT_POWER_OFF+1)          //需量周期到--------50
//#define ID_OVER_LOAD                (ID_DEMAND_ARRIVE+1)            //负荷控制报警--------51
#define ID_PAY_ALARM                (ID_DEMAND_ARRIVE+1)              //预付费报警--------52
#define ID_PARSE_SWITCH             (ID_PAY_ALARM+1)             //时段切换--------53
//#define ID_MEASURE_ERROR            (ID_PARSE_SWITCH+1)           //计量错误--------54
#define ID_METER_ADDR_EN            (ID_PARSE_SWITCH+1)          //设置表地址按钮-------55
#define ID_EVENT_ALL_LOSS_VOLT      (ID_METER_ADDR_EN+1)        //全失压-------56

/*
#define ID_EVENT_AB_LOSS_VOLT       (ID_EVENT_ALL_LOSS_VOLT+1)   //AB失压------------------57
#define ID_EVENT_AC_LOSS_VOLT       (ID_EVENT_AB_LOSS_VOLT+1)    //AC失压------------------58
#define ID_EVENT_BC_LOSS_VOLT       (ID_EVENT_AC_LOSS_VOLT+1)   //BC失压------------------59
#define ID_EVENT_ABC_LOSS_VOLT      (ID_EVENT_BC_LOSS_VOLT+1)   //ABC失压------------------60
*/

#define ID_EVENT_PROG               (ID_EVENT_ALL_LOSS_VOLT+1)  //编程事件：设置参数-----------61
#define ID_EVENT_CLR_ALL_DATA       (ID_EVENT_PROG+1)           //数据总清-----------62
#define ID_EVENT_POS_ACT_DEMAND_EXCEED  (ID_EVENT_CLR_ALL_DATA+1)          //正向有功需量超限--------63(HUCK需求) 
#define ID_EVENT_NEG_ACT_DEMAND_EXCEED (ID_EVENT_POS_ACT_DEMAND_EXCEED+1)   //反向有功需量超限------------64(HUCK需求)  
#define ID_EVENT_Q1_REAC_DEMAND_EXCEED   (ID_EVENT_NEG_ACT_DEMAND_EXCEED+1)          //一象限无功需量超限--------65
#define ID_EVENT_Q2_REAC_DEMAND_EXCEED   (ID_EVENT_Q1_REAC_DEMAND_EXCEED+1)                //二象限无功需量超限--------66
#define ID_EVENT_Q3_REAC_DEMAND_EXCEED   (ID_EVENT_Q2_REAC_DEMAND_EXCEED+1)         //三象限无功需量超限--------67
#define ID_EVENT_Q4_REAC_DEMAND_EXCEED   (ID_EVENT_Q3_REAC_DEMAND_EXCEED+1)    //四象限无功需量超限--------68

/*
#define ID_EVENT_AB_LOSS_CURR       (ID_EVENT_Q4_REAC_DEMAND_EXCEED+1)   //AB失流------------------69
#define ID_EVENT_AC_LOSS_CURR       (ID_EVENT_AB_LOSS_CURR+1)    //AC失流------------------70
#define ID_EVENT_BC_LOSS_CURR       (ID_EVENT_AC_LOSS_CURR+1)   //BC失流------------------71
#define ID_EVENT_ALL_LOSS_CURR      (ID_EVENT_BC_LOSS_CURR+1)   //全失流-------------72
*/


#define ID_EVENT_DOWN_COVER_OPEN   (ID_EVENT_Q4_REAC_DEMAND_EXCEED+1)          //开端盖--------73


//#define ID_EVENT_DOOR_OPEN          (ID_EVENT_DOWN_COVER_OPEN+1)        //开计量装置门--------74

#define ID_SLIP_ARRIVE              (ID_EVENT_DOWN_COVER_OPEN+1)          //滑差到--------75
#define ID_ALARM_OUT                (ID_SLIP_ARRIVE+1)             //是否有报警事件输出：如声音报警，LCD_LED报警，端子排报警--------76
#define ID_CLR_DEMAND_KEY           (ID_ALARM_OUT+1)             //手动清需量按钮--------77
#define ID_EVENT_EXT_PROG           (ID_CLR_DEMAND_KEY+1)         //编程事件：设置参数--------78(同 ID_EVENT_PROG,应HUCKGD需求增加)

//#define ID_EVENT_OSC_ERR            (ID_EVENT_EXT_PROG+1)        //单片机时钟系统故障--------79

#define ID_EVENT_A_OVER_CURR        (ID_EVENT_EXT_PROG+1)        //A相过流：--------80
#define ID_EVENT_B_OVER_CURR        (ID_EVENT_A_OVER_CURR+1)        //B相过流：--------81
#define ID_EVENT_C_OVER_CURR        (ID_EVENT_B_OVER_CURR+1)        //C相过流：--------82

#define ID_EVENT_DATE               (ID_EVENT_C_OVER_CURR+1)           //时段表编程：--------83
#define ID_EVENT_YEAR               (ID_EVENT_DATE+1)        //时区表编程：--------84
#define ID_EVENT_WEEK               (ID_EVENT_YEAR+1)        //周休日编程：--------85
#define ID_EVENT_HOLIDAY            (ID_EVENT_WEEK+1)         //节假日编程：--------86
#define ID_EVENT_ACPWR              (ID_EVENT_HOLIDAY+1)        //有功组合方式编程：--------87
#define ID_EVENT_REACPWR1           (ID_EVENT_ACPWR+1)        //无功组合方式1编程：--------88
#define ID_EVENT_REACPWR2           (ID_EVENT_REACPWR1+1)        //无功组合方式2编程：--------89
#define ID_EVENT_SETTLE_DATE        (ID_EVENT_REACPWR2+1)        //结算日编程：--------90


//#define ID_EVENT_REMOTE_RELAY_ON    (ID_EVENT_SETTLE_DATE+1)         //远程合闸--------91
//#define ID_EVENT_REMOTE_RELAY_OFF   (ID_EVENT_REMOTE_RELAY_ON+1)    //远程拉闸--------92

#define ID_EVENT_RELAY_ON           (ID_EVENT_SETTLE_DATE+1)    //合闸--------93
#define ID_EVENT_RELAY_OFF          (ID_EVENT_RELAY_ON+1)    //拉闸--------94

//#define ID_PAY_SWITCH               (ID_EVENT_RELAY_OFF+1)     //预付费拉着--------95

#define ID_EVENT_CURR_NO_EVEN       (ID_EVENT_RELAY_OFF+1)              //电流不平衡--------96

#define ID_EVENT_ALL_FACTOR_LOW         (ID_EVENT_CURR_NO_EVEN+1)     //总功率因数超下限--------97  
#define ID_EVENT_A_POWER_EXCEED       (ID_EVENT_ALL_FACTOR_LOW+1)       //超功率A(过载A)-------------98
#define ID_EVENT_B_POWER_EXCEED       (ID_EVENT_A_POWER_EXCEED+1)       //超功率B(过载B)-------------99
#define ID_EVENT_C_POWER_EXCEED       (ID_EVENT_B_POWER_EXCEED+1)       //超功率C(过载C)-------------100

#define ID_EVENT_A_CUT_CURR           (ID_EVENT_C_POWER_EXCEED+1)       //断流 A-------------101
#define ID_EVENT_B_CUT_CURR         (ID_EVENT_A_CUT_CURR+1)             //断流 B-------------102
#define ID_EVENT_C_CUT_CURR          (ID_EVENT_B_CUT_CURR+1)             //断流 C-------------103

#define ID_EVENT_AUX_POWER           (ID_EVENT_C_CUT_CURR+1)             //辅助电源掉电-------------104
#define ID_CUR_VERY_NOEVEN           (ID_EVENT_AUX_POWER+1)             //电流严重不平衡-------------105


#define MIN_ID_EVENT          ID_EVENT_A_LOSS_VOLT
#define MAX_ID_EVENT          ID_CUR_VERY_NOEVEN

#define MAX_EVENT_NUM          (MAX_ID_EVENT+1)





#define ID_EVENT_LOSS_VOL 0
#define ID_EVENT_LOSS_CUR 0
#define ID_EVENT_NEG_CUR  0
typedef struct
{
  INT8U Instant_Event[MAX_EVENT_NUM/8+1];
  INT8U CS[CS_BYTES];
}EVENT_INSTANT_STATUS;
NO_INIT EVENTPUB_C_EXT  EVENT_INSTANT_STATUS Meter_Instant_Status;

typedef struct
{
  U_Word_Bit  Meter_Stat1;        //0x04000501
  U_Word_Bit  Meter_Stat2;        //0x04000502
  U_Word_Bit  Meter_Stat3;        //0x04000503
  U_Word_Bit  Meter_Stat4;        //0x04000504
  U_Word_Bit  Meter_Stat5;        //0x04000505
  U_Word_Bit  Meter_Stat6;        //0x04000506
  U_Word_Bit  Meter_Stat7;        //0x04000507
  U_Word_Bit  Meter_Stat8;        //
  //U_Byte_Bit  SERR;               //安全认证错误信息字
  
  U_Byte_Bit  Volt_LossMiss;      //扩充失压/断相，DI:DI_LOW_VOL
  U_Byte_Bit  NegCurr_Qudrant;    //扩充电流反极性/电表工作象限，DI_CURRENT_QUADRANT
  U_Byte_Bit  Key_Event;          //扩充编程键打开/跳线短接/需量复位/电表上锁，DI:DI_METER_PERIPHERY
  U_Byte_Bit  Comm_Status;        //扩充通信状态字，DI:DI_MODULE_STATUS
  
  /*
  //扩展不兼容的功率方向状态字
  U_Byte_Bit  Ext_Ac_Power_Dir;        //有功方向标志字节（1字节，0-3位为总、a、b、c元件，高4字节为0）
  U_Byte_Bit  Ext_Reac_Power_Dir;        //无功方向标志字节（1字节，0-3位为总、a、b、c元件，高4字节为0）
  
  U_Byte_Bit  GD_Meter_Stat;        //广东：电表状态字
  U_Byte_Bit  GD_PwrDir_Stat;       //广东：有功功率方向状态字
  U_Byte_Bit  GD_LossVolt_Stat;        //广东：失压状态字
  U_Byte_Bit  GD_LossCurr_Stat;        //广东：失流状态字
  U_Byte_Bit  GD_Hard_Stat;        //广东：硬件状态字
  //U_Byte_Bit  GD_Prog_Stat;        //广东：编程状态字(HUCK)
  */
  INT8U CS[CS_BYTES];
}POWER_STATS;


EVENTPUB_C_EXT POWER_STATS Meter_Run_Status;

typedef struct{
  INT8U  Occur:1;         //事件发生标志，不对外访问
  
  INT8U  Status:1;        //事件发生的状态位，外部访问，访问后，该位不清除，还是反应该事件的发生：0-------无事件发生；1-------事件发生；  
  INT8U  Status1:1;       //事件发生标志备份，外部访问1，访问后，该位清除
  INT8U  Status2:1;       //事件发生标志备份，外部访问2，访问后，该位清除
  INT8U  Status3:1;       //事件发生标志备份，外部访问3，访问后，该位清除
  INT8U  Status4:1;       //事件发生标志备份，外部访问4，访问后，该位清除  
  INT8U  Reserved:2;      //预留
  INT8U  Mins;           //分计数器
  INT8U  StartCount;      //事件发生计数器
  INT8U  EndCount;        //事件结束计数器  
  INT8U  CS[CS_BYTES];
}EventProcStatus;         //事件处理状态


EVENTPUB_C_EXT EventProcStatus EventProcStatusVar[MAX_EVENT_NUM]; 



#define POWER_OFF        0x37   //掉电
#define POWER_ON         0xF6   //上电
#define ABNORMAL_RESET   0xE8   //异常复位



typedef struct{
  INT8U  Power;
  INT8U  CS[CS_BYTES];
}POWER_STATUS;         //上电处理状态

NO_INIT EVENTPUB_C_EXT POWER_STATUS Power_Status;

typedef struct{
  INT16U  Volt_Not_Even;    //2位小数
  INT16U  Curr_Not_Even;    //2位小数
  INT8U  CS[CS_BYTES];
}NOT_EVEN_DATA;         //不平衡率

EVENTPUB_C_EXT NOT_EVEN_DATA Not_Even_Data_PUCK;    //不平衡率

void Get_Meter_Status(void);
void Event_Main_PUCK(INT8U Flag);


INT8U Read_Event_Ststus(INT8U PersonID,INT8U EventId);
void Set_Event_Instant(INT8U Id);
void Clr_Event_Instant(INT8U Id);

INT8U Check_Prog_Status(void);
void Save_Event_Data(void);
void Save_LastPwrOff_Data_PUCK(void);
INT8U Check_AB_Switch(void);
INT8U Check_C_Switch(void);
INT8U Check_MeterAddr_Status(void);
INT8U Read_Event_Status(INT8U Id);
void Init_Event_Sram(INT8U);

//void Emerg_Event_Proc(void);
void Event_Proc_Sec(void);
INT8U Check_Event_End(INT8U Id);


INT8U RTC_Read_Fxt(volatile INT8U Time[]);
void PwrOff_Proc_PUCK(void);
void Sound_LED_LCD_Port_Alarm(void);
INT8U Check_Man_ClrDemd_En(void);
void Get_Meter_Run_Status(void);
void Set_Event_Occur_Status(INT8U i);
void Set_Event_End_Status(INT8U i);
void Clr_Event_Real_Status(INT8U i);
void Clr_All_Event_Sram(void);
void Init_All_Event_Sram(void);
void Force_Event_Occur_Status(INT8U i);
void Force_Event_End_Status(INT8U i);
void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode);
void Period_Save_RTC_BatTime(void);
void Accmu_RTC_BatTime_PerMin(void);
void Clr_RTC_BatTime(void);
#endif
