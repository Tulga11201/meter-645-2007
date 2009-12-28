#ifndef EVENTSTATUS_VAR
#define EVENTSTATUS_VAR  


#ifndef EVENTSTATUS_C
#define EVENTSTATUS_C_EXT  extern
#else
#define EVENTSTATUS_C_EXT
#endif


#define KEEP_TIME_MIN   10  //维持时间

const INT16U Const_End_Time[]=
{
  14400,
  600,
  0
};

#define MAX_END_TIME_NUM (sizeof(Const_End_Time)/sizeof(INT16U))

typedef struct{
  INT8U  DoubleFlag:1;      //事件清除属性，0-------不成对事件,由外部访问清除或者定时强制清除;1-------成对出现的事件(事件成对出现,可能会统计该时间段的相关量)
  INT8U  StartSave:1;       //事件起始存储使能
  INT8U  EndSave:1;         //事件起始存储使能
  INT8U  StartUnit:1;       //事件发生计数器，单位：0-----秒；1---------分
  INT8U  EndUnit:1;         //事件结束计数器，单位：0-----秒；1---------分
  INT8U  ForbitEnd:1;       //对于成对事件，事件发生后，按照EndCount的值，隔一段时间强行清除。
  INT8U  EndIndex:1;        //强行结束事件时间索引
  INT8U  res:1;
  
  volatile INT8U  *JudgeTimeSec;       //时间判定时间:秒
 
  INT16U StartCount;         //事件发生计数器，单位：秒
  INT16U EndCount;           //对成事件，0表示事件一旦发生后就马上结束，表示事件结束计数器；对于非成对事件，定时强制清除计数器，单位：秒
  void (* const GetInstStatus)(void);
  INT8U const *EventName;
}EventProperty;           //事件和报警属性结构体


/*********************表参数配置需注意的几个问题*********************************************************
1：对于合相判定失压、失流等事件，发生时间>结束时间，且发生时间=1.5×结束时间
2：

*********************************************************************************************************/
EVENTSTATUS_C_EXT const EventProperty EventPropertyVar[MAX_EVENT_NUM]={
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=0,.EndCount=0,.EventName="NONE"},
   
#ifdef ID_EVENT_A_LOSS_VOLT                               //A相失压------------------1
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.GetInstStatus=&Check_Loss_Volt,.EventName="A Loss Volt"},
#endif

#ifdef ID_EVENT_B_LOSS_VOLT                               //B相失压------------------2
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="B Loss Volt"},
#endif  

#ifdef ID_EVENT_C_LOSS_VOLT                             //C相失压------------------3
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="C Loss Volt"},
#endif
#ifdef ID_EVENT_A_LOSS_CURR                                //A相失流--------------4
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossCurr_Time,.GetInstStatus=&Check_Loss_Curr,.EventName="A Loss Cur"},
  #endif  
  
#ifdef ID_EVENT_B_LOSS_CURR                               //B相失流--------------5
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="B Loss Cur"},
  #endif
  
#ifdef ID_EVENT_C_LOSS_CURR                               //C相失流--------------6
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="C Loss Cur"},
  #endif
  
#ifdef ID_EVENT_PRGKEY_ON
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_Prg_Key,.EventName="Prog Key"},    //编程键打开-----------7--此按钮需要中断支持
#endif 

#ifdef ID_EVENT_CUR_NEG_SEQ                               //电流逆相序-----------8
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Curr_NoEven_Time,.GetInstStatus=&Check_Volt_Curr_Seq,.EventName="Cur Neg Sequence"},
  #endif  
  
#ifdef ID_EVENT_VOLT_NEG_SEQ                              //电压逆相序-----------9
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Volt_NoEven_Time,.EventName="Volt Neg Sequence"},
  #endif  
  
  
#ifdef ID_EVENT_A_VOLT_LESS
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownVolt_Time,.GetInstStatus=&Check_Down_Volt,.EventName="A Volt Less"},    //A相电压欠压--------10
  #endif  
  
#ifdef ID_EVENT_B_VOLT_LESS
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownVolt_Time,.EventName="B Volt Less"},    //B相电压欠压-------11
  #endif  
  
#ifdef ID_EVENT_C_VOLT_LESS
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownVolt_Time,.EventName="C Volt Less"},    //C相电压欠压--------12
  #endif  
  
#ifdef ID_EVENT_DEMAND_ALARM
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Exceed Demand Alarm"},    //超需量报警-----------13----HUCK  done
  #endif  
  
#ifdef ID_EVENT_DEMAND_SWITCH
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Exceed Demand Toggle"},    //超需量跳闸-----------14----HUCK  done
  #endif
  
#ifdef ID_EVENT_VOLT_NO_EVEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Volt_NoEven,.EventName="Volt Not Even"},      //电压不平衡--------15
  #endif
  
#ifdef ID_EVENT_RESET
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Meter Reset"},      //复位-----------------16----需要增加函数----PUCK
  #endif 
  
#ifdef ID_EVENT_CLR_DEMAND_COM
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Clr Demand(COM)"},    //通信清需量-----------17----HUCK Will do
  #endif  
#ifdef ID_EVENT_CLR_DEMAND_MAN
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Clr Demand(Man)"},    //手动清需量-----------18----HUCK Will do,PUCK do:09-06-30
  #endif  
  
#ifdef ID_EVENT_CLR_PROCESS
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Clr Process"},    //清过程---------------19----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_CLR_VOLT_PASS
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Clr Volt Rate"},    //清电压合格率---------20----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_SET_ENERG
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Set Init Energ"},    //设置初始电量---------21----HUCK not do
  #endif  
  
#ifdef ID_EVENT_UP_COVER_OPEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=5,.EndCount=5,.GetInstStatus=&Check_UpCover,.EventName="Up Cover Opened"},    //开大盖(前端盖)--------22
  #endif  
  
#ifdef ID_EVENT_LEAD_COVER_OPEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_LeadCover,.EventName="Lead Door Opened"},    //开铅封门-------------23  
  #endif  
  
#ifdef ID_EVENT_RTC_BAT_LOW                   //时钟电池欠压---------24
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_RTCBat_Low,.EventName="RTC Bat Low"},
  #endif  
  
#ifdef ID_EVENT_LOWPWR_BAT_LOW                    //低功耗电池欠压-------25
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_LPWBat_Low,.EventName="Low_Power Bat Low"},
  #endif  
  
#ifdef ID_EVENT_ADJUST_TIME
  {.DoubleFlag=0,.StartSave=0,.EndSave=1,.StartCount=1,.EndCount=3,.EventName="Adjust RTC"},    //校时-----------------26----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_RTCERR_RUN                          //运行时钟乱-----------27----HUCK Will do
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=15,.EventName="RTC Err Running"},
#endif  
  
#ifdef ID_EVENT_RTCERR_PWRON                        //上电时钟乱-----------28----HUCK Will do
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=5,.EventName="RTC Err Power On"},
#endif

#ifdef ID_EVENT_EPPROM_FAULT                //EEPROM坏-------------29----HUCK Will do(只是上电时候查)
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=20,.EndCount=0,.EventName="Inter Memory Err"},
#endif 

#ifdef ID_EVENT_ADJUST_MEASU
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Adjust Measure"},          //校表-----------------30----PUCK Will do
#endif

#ifdef ID_EVENT_MODI_ENERG  
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=20,.EndCount=0,.EventName="Remedy Energ Error"},           //电量纠错-------------31----HUCK Will do
#endif

#ifdef ID_EVENT_A_VOLT_OVERLOAD                     //A相电压过压----------32
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpwnVolt_Time,.GetInstStatus=&Check_Up_Volt,.EventName="Volt A Overload"},
#endif

#ifdef ID_EVENT_B_VOLT_OVERLOAD                     //B相电压过压----------33
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpwnVolt_Time,.EventName="Volt B Overload"},
#endif

#ifdef ID_EVENT_C_VOLT_OVERLOAD                     //C相电压过压----------34
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpwnVolt_Time,.EventName="Volt C Overload"},
#endif

#ifdef ID_EVENT_ENERG_FREEZ    //电量冻结-------------35----HUCK Will do
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Energ Freeze"},
#endif

#ifdef ID_EVENT_POWER_ALARM    //超功率-----------36-同超需量、超功率（HUCK)
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="Overlimted Power Alarm"},
#endif

#ifdef ID_EVENT_POWER_SWITCH    //超功率跳闸-----------37  
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="Overlimted Power Switch Toggle"}, 
#endif

#ifdef ID_EVENT_A_LOSS_PARSE                               //A相断相--------------38  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutParse_Time,.GetInstStatus=&Check_Loss_Parse,.EventName="A Loss Parse"},
#endif

#ifdef ID_EVENT_B_LOSS_PARSE                                //B相断相--------------39  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutParse_Time,.EventName="B Loss Parse"},
#endif

#ifdef ID_EVENT_C_LOSS_PARSE                           //C相断相--------------40  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutParse_Time,.EventName="C Loss Parse"},
#endif

#ifdef ID_EVENT_A_NEG_CURR                        //A相电流反向----------41 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.NegCurr_Time,.GetInstStatus=&Check_Neg_Curr,.EventName="A Cur Neg Direction"},
#endif

#ifdef ID_EVENT_B_NEG_CURR               //B相电流反向----------42  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.NegCurr_Time,.EventName="B Cur Neg Direction"},
#endif

#ifdef ID_EVENT_C_NEG_CURR                  //C相电流反向----------43 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.NegCurr_Time,.EventName="C Cur Neg Direction"},
#endif 

#ifdef ID_EVENT_SUM_NEG_CURR                //总电流反向（有功功率反相）-----------44 
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="Sum Cur Neg Direction"},    
#endif 

#ifdef ID_EVENT_CMD_ALARM   //命令报警(通过命令，强行报警)--------45
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Cmd Alarm"},    
#endif 

 

#ifdef ID_EVENT_ERR_PASSWD   //密码错---------------46----HUCK Will do
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Password Err"},    
#endif  


#ifdef ID_EVENT_METER_LOCK  //对电表编程(设置重要参数)时，若密码连续出错次数大于等于5次后--------47
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=2,.EndCount=2,.EventName="Prg Meter Event"},     
#endif  

#ifdef ID_EVENT_AB_FUNC_KEY   //功能键识别，AB模式切换按钮--------48
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=3,.EndCount=1,.GetInstStatus=&Check_AB_Func_Key,.EventName="Func AB Mode Switch Key"},    
#endif    

#ifdef ID_EVENT_POWER_OFF                                    //上电事件--------49----PUCK 
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Meter Power On"},
#endif    

#ifdef ID_DEMAND_ARRIVE                                    //需量到--------50----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Demand Time Expired!"},
#endif  
  
#ifdef ID_OVER_LOAD                                    //负荷控制报警--------51-同超需量、超功率（HUCK)
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=20,.EndCount=0,.EventName="OverLoad Ctrol Alarm"},
#endif  
  
#ifdef ID_PAY_ALARM                                   //预付费报警--------52----HUCK Will do 
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Fees Not Enough"},
#endif

#ifdef ID_PARSE_SWITCH                                 //时段切换--------53-----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Time Prase Switch"},
#endif

#ifdef ID_MEASURE_ERROR                               //计量错误(瞬态字)--------54
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=15,.EventName="Measure Error Event"},
#endif

#ifdef ID_METER_ADDR_EN                         //设置表地址按钮----------55 
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_MeterAddr_Key,.EventName="Set Meter Addr Key"},    
#endif

#ifdef ID_EVENT_ALL_LOSS_VOLT                           //全失压--------56
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="All Loss Volt"},
#endif  

#ifdef ID_EVENT_AB_LOSS_VOLT                               //AB失压------------------57
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_B Loss Volt"},
#endif

#ifdef ID_EVENT_AC_LOSS_VOLT                               //AC失压------------------58
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_C Loss Volt"},
#endif

#ifdef ID_EVENT_BC_LOSS_VOLT                               //BC失压------------------59
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="B_C Loss Volt"},
#endif

#ifdef ID_EVENT_ABC_LOSS_VOLT                               //ABC失压------------------60
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_B_C Loss Volt"},
#endif

#ifdef ID_EVENT_PROG                                      //编程事件：设置参数-----------61
  {.DoubleFlag=0,.StartSave=0,.EndSave=1,.EndUnit=1,.StartCount=1,.EndCount=14400,.EventName="Prog Data Event"},
#endif


#ifdef ID_EVENT_CLR_ALL_DATA                                   //数据总清-----------62
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=5,.EventName="All Data Clear Event"},
#endif


#ifdef ID_EVENT_POS_ACT_DEMAND_EXCEED                                   //正向有功需量超限--------63(HUCK需求) 
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.GetInstStatus=&Check_Demand_Exceed,.EventName="Pos Demand Exceed",\
 },
#endif

#ifdef ID_EVENT_NEG_ACT_DEMAND_EXCEED                                   //反向有功需量超限------------64(HUCK需求) 
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Neg Demand Exceed"},  
#endif 


#ifdef ID_EVENT_Q1_REAC_DEMAND_EXCEED                            //一象限无功需量超限--------65(HUCK需求)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q1 Demand Alarm"},
#endif


#ifdef ID_EVENT_Q2_REAC_DEMAND_EXCEED                               //二象限无功需量超限--------66(HUCK需求)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q2 Demand Alarm"},
#endif


#ifdef ID_EVENT_Q3_REAC_DEMAND_EXCEED                                //三象限无功需量超限---------67(HUCK需求)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q3 Demand Alarm"},
#endif

#ifdef ID_EVENT_Q4_REAC_DEMAND_EXCEED                               //四象限无功需量超限---------68(HUCK需求)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q4 Demand Alarm"},
#endif



#ifdef ID_EVENT_AB_LOSS_CURR                                //AB相失流--------------69
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_B Loss Cur"},
#endif
  
#ifdef ID_EVENT_AC_LOSS_CURR                                //AC相失流--------------70
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_C Loss Cur"},
#endif  
  
#ifdef ID_EVENT_BC_LOSS_CURR                                //BC相失流--------------71
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="B_C Loss Cur"},
#endif  

#ifdef ID_EVENT_ALL_LOSS_CURR                                //全失流--------72
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="Loss All Cur",\
 },
#endif 

#ifdef ID_EVENT_DOWN_COVER_OPEN                           //开端盖(后端盖)--------73
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=5,.EndCount=5,.GetInstStatus=&Check_DownCover,.EventName="Down Cover Opened"},
#endif



#ifdef ID_EVENT_DOOR_OPEN                                  //开计量装置门--------74
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=5,.EndCount=5,.EventName="Door Opened"},
#endif


  
#ifdef ID_SLIP_ARRIVE                                 //滑差到--------75
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Slipe Time Arrived"},
#endif 

#ifdef ID_ALARM_OUT               //是否有报警事件输出：如声音报警，LCD_LED报警，端子排报警--------76
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=3,.EndCount=1,.GetInstStatus=&Sound_LED_LCD_Port_Alarm,.EventName="Event Alarm Exist"},
#endif

#ifdef ID_CLR_DEMAND_KEY    //手动清需量按钮--------77
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.EndUnit=1,.StartCount=5,.EndCount=10,.GetInstStatus=&Check_ClrDemand_Key,.EventName="Clr Demand Key Press"},
#endif
  
#ifdef ID_EVENT_EXT_PROG     //编程事件：设置参数--------78(同 ID_EVENT_PROG,应HUCKGD需求增加)
  {.DoubleFlag=0,.StartSave=1,.EndSave=1,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Extern Prog Data Event"},
#endif


#ifdef ID_EVENT_OSC_ERR      //单片机时钟系统故障--------79
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Monitor_Meter_System_Osc,.EventName="MCU Osc System Error"},                
#endif  


#ifdef ID_EVENT_A_OVER_CURR     //A相过流：--------80
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpCurr_Time,.GetInstStatus=&Check_Up_Curr,.EventName="A Over Cur"},
#endif

#ifdef ID_EVENT_B_OVER_CURR     //B相过流：--------81
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpCurr_Time,.EventName="B Over Cur"}, 
#endif
  
#ifdef ID_EVENT_C_OVER_CURR       //C相过流：--------82
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpCurr_Time,.EventName="C Over Cur"},
#endif
 

#ifdef ID_EVENT_DATE                                      //时段表编程：--------83
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Date Prog"},
#endif

#ifdef ID_EVENT_YEAR                                      //时区表编程：--------84
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Year Prog"},
#endif

#ifdef ID_EVENT_WEEK                                      //周休日编程：--------85
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Week Prog"},
#endif

#ifdef ID_EVENT_HOLIDAY                                      //节假日编程：--------86
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Holiday Prog"},
#endif

#ifdef ID_EVENT_ACPWR                                        //有功组合方式编程：--------87
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="AcPower Group Prog"},
#endif

#ifdef ID_EVENT_REACPWR1                                       //无功组合方式1编程：--------88
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Reacpower Group1 Prog"},
#endif

#ifdef ID_EVENT_REACPWR2                                      //无功组合方式2编程：--------89
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Reacpower Group2 Prog"},
#endif

#ifdef ID_EVENT_SETTLE_DATE                                       //结算日编程：--------90
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Settle Date Prog"},
#endif


#ifdef ID_EVENT_REMOTE_RELAY_ON                                //远程合闸,瞬态字由 HUCK 负责--------91
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Switch On Toggle"},
#endif

#ifdef ID_EVENT_REMOTE_RELAY_OFF                               //远程拉闸,瞬态字由 HUCK 负责--------92
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Switch Off Toggle"},
#endif

#ifdef ID_EVENT_RELAY_ON                                        ///合闸--------93
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Relay On"},
#endif

#ifdef ID_EVENT_RELAY_OFF                                        //拉闸--------94
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Relay Off",\
},
#endif
 
#ifdef ID_PAY_SWITCH                                        //预付费拉着--------95
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Pay Relay Off",\
},
#endif


#ifdef ID_EVENT_CURR_NO_EVEN                                       //电流不平衡--------96
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Curr_No1Even_Time,.GetInstStatus=&Check_Curr_NoEven,.EventName="Cur No Even",\
},
#endif


#ifdef ID_EVENT_ALL_FACTOR_LOW                                       //总功率因数超下限--------97  
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownPf_Time,.GetInstStatus=&Check_Sum_Factor_Low,.EventName="PF low",\
},
#endif


#ifdef ID_EVENT_A_POWER_EXCEED                                       //超功率A(过载A)-------------98
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverLoad_Time,.GetInstStatus=&Check_Power_Exceed,.EventName="A Power Exceed",\
},
#endif

#ifdef ID_EVENT_B_POWER_EXCEED                                       //超功率B(过载B)-------------99
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverLoad_Time,.EventName="B Power Exceed",\
},
#endif


#ifdef ID_EVENT_C_POWER_EXCEED                                       //超功率C(过载C)-------------100
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverLoad_Time,.EventName="C Power Exceed",\
},
#endif

#ifdef ID_EVENT_A_CUT_CURR                                        ///断流 A-------------101
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.GetInstStatus=&Check_Cut_Curr,.EventName="A Cut Curr",\
},
#endif

#ifdef ID_EVENT_B_CUT_CURR                                        ///断流 B-------------102
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.EventName="B Cut Curr",\
},
#endif

#ifdef ID_EVENT_C_CUT_CURR                                        ///断流 C-------------103
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.EventName="C Cut Curr",\
},
#endif

#ifdef ID_EVENT_AUX_POWER                                        //辅助电源掉电-------------104
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.EventName="Aux Power Off",\
},
#endif

#ifdef ID_CUR_VERY_NOEVEN                                        //电流严重不平衡-------------105
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Curr_No1Even_Time,.GetInstStatus=&Check_Cur_Very_Noeven,.EventName="Curr Very No Even",\
}
#endif

};
#endif