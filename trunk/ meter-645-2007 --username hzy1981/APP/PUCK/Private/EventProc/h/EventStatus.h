#ifndef EVENTSTATUS_VAR
#define EVENTSTATUS_VAR  


#ifndef EVENTSTATUS_C
#define EVENTSTATUS_C_EXT  extern
#else
#define EVENTSTATUS_C_EXT
#endif


#define KEEP_TIME_MIN   10  //ά��ʱ��

const INT16U Const_End_Time[]=
{
  14400,
  600,
  0
};

#define MAX_END_TIME_NUM (sizeof(Const_End_Time)/sizeof(INT16U))

typedef struct{
  INT8U  DoubleFlag:1;      //�¼�������ԣ�0-------���ɶ��¼�,���ⲿ����������߶�ʱǿ�����;1-------�ɶԳ��ֵ��¼�(�¼��ɶԳ���,���ܻ�ͳ�Ƹ�ʱ��ε������)
  INT8U  StartSave:1;       //�¼���ʼ�洢ʹ��
  INT8U  EndSave:1;         //�¼���ʼ�洢ʹ��
  INT8U  StartUnit:1;       //�¼���������������λ��0-----�룻1---------��
  INT8U  EndUnit:1;         //�¼���������������λ��0-----�룻1---------��
  INT8U  ForbitEnd:1;       //���ڳɶ��¼����¼������󣬰���EndCount��ֵ����һ��ʱ��ǿ�������
  INT8U  EndIndex:1;        //ǿ�н����¼�ʱ������
  INT8U  res:1;
  
  volatile INT8U  *JudgeTimeSec;       //ʱ���ж�ʱ��:��
 
  INT16U StartCount;         //�¼���������������λ����
  INT16U EndCount;           //�Գ��¼���0��ʾ�¼�һ������������Ͻ�������ʾ�¼����������������ڷǳɶ��¼�����ʱǿ���������������λ����
  void (* const GetInstStatus)(void);
  INT8U const *EventName;
}EventProperty;           //�¼��ͱ������Խṹ��


/*********************�����������ע��ļ�������*********************************************************
1�����ں����ж�ʧѹ��ʧ�����¼�������ʱ��>����ʱ�䣬�ҷ���ʱ��=1.5������ʱ��
2��

*********************************************************************************************************/
EVENTSTATUS_C_EXT const EventProperty EventPropertyVar[MAX_EVENT_NUM]={
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=0,.EndCount=0,.EventName="NONE"},
   
#ifdef ID_EVENT_A_LOSS_VOLT                               //A��ʧѹ------------------1
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.GetInstStatus=&Check_Loss_Volt,.EventName="A Loss Volt"},
#endif

#ifdef ID_EVENT_B_LOSS_VOLT                               //B��ʧѹ------------------2
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="B Loss Volt"},
#endif  

#ifdef ID_EVENT_C_LOSS_VOLT                             //C��ʧѹ------------------3
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="C Loss Volt"},
#endif
#ifdef ID_EVENT_A_LOSS_CURR                                //A��ʧ��--------------4
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossCurr_Time,.GetInstStatus=&Check_Loss_Curr,.EventName="A Loss Cur"},
  #endif  
  
#ifdef ID_EVENT_B_LOSS_CURR                               //B��ʧ��--------------5
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="B Loss Cur"},
  #endif
  
#ifdef ID_EVENT_C_LOSS_CURR                               //C��ʧ��--------------6
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.LossVolt_Time,.EventName="C Loss Cur"},
  #endif
  
#ifdef ID_EVENT_PRGKEY_ON
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_Prg_Key,.EventName="Prog Key"},    //��̼���-----------7--�˰�ť��Ҫ�ж�֧��
#endif 

#ifdef ID_EVENT_CUR_NEG_SEQ                               //����������-----------8
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Curr_NoEven_Time,.GetInstStatus=&Check_Volt_Curr_Seq,.EventName="Cur Neg Sequence"},
  #endif  
  
#ifdef ID_EVENT_VOLT_NEG_SEQ                              //��ѹ������-----------9
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Volt_NoEven_Time,.EventName="Volt Neg Sequence"},
  #endif  
  
  
#ifdef ID_EVENT_A_VOLT_LESS
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownVolt_Time,.GetInstStatus=&Check_Down_Volt,.EventName="A Volt Less"},    //A���ѹǷѹ--------10
  #endif  
  
#ifdef ID_EVENT_B_VOLT_LESS
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownVolt_Time,.EventName="B Volt Less"},    //B���ѹǷѹ-------11
  #endif  
  
#ifdef ID_EVENT_C_VOLT_LESS
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownVolt_Time,.EventName="C Volt Less"},    //C���ѹǷѹ--------12
  #endif  
  
#ifdef ID_EVENT_DEMAND_ALARM
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Exceed Demand Alarm"},    //����������-----------13----HUCK  done
  #endif  
  
#ifdef ID_EVENT_DEMAND_SWITCH
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Exceed Demand Toggle"},    //��������բ-----------14----HUCK  done
  #endif
  
#ifdef ID_EVENT_VOLT_NO_EVEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.GetInstStatus=&Check_Volt_NoEven,.EventName="Volt Not Even"},      //��ѹ��ƽ��--------15
  #endif
  
#ifdef ID_EVENT_RESET
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Meter Reset"},      //��λ-----------------16----��Ҫ���Ӻ���----PUCK
  #endif 
  
#ifdef ID_EVENT_CLR_DEMAND_COM
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Clr Demand(COM)"},    //ͨ��������-----------17----HUCK Will do
  #endif  
#ifdef ID_EVENT_CLR_DEMAND_MAN
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Clr Demand(Man)"},    //�ֶ�������-----------18----HUCK Will do,PUCK do:09-06-30
  #endif  
  
#ifdef ID_EVENT_CLR_PROCESS
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Clr Process"},    //�����---------------19----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_CLR_VOLT_PASS
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Clr Volt Rate"},    //���ѹ�ϸ���---------20----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_SET_ENERG
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Set Init Energ"},    //���ó�ʼ����---------21----HUCK not do
  #endif  
  
#ifdef ID_EVENT_UP_COVER_OPEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=5,.EndCount=5,.GetInstStatus=&Check_UpCover,.EventName="Up Cover Opened"},    //�����(ǰ�˸�)--------22
  #endif  
  
#ifdef ID_EVENT_LEAD_COVER_OPEN
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=3,.EndCount=3,.GetInstStatus=&Check_LeadCover,.EventName="Lead Door Opened"},    //��Ǧ����-------------23  
  #endif  
  
#ifdef ID_EVENT_RTC_BAT_LOW                   //ʱ�ӵ��Ƿѹ---------24
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_RTCBat_Low,.EventName="RTC Bat Low"},
  #endif  
  
#ifdef ID_EVENT_LOWPWR_BAT_LOW                    //�͹��ĵ��Ƿѹ-------25
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_LPWBat_Low,.EventName="Low_Power Bat Low"},
  #endif  
  
#ifdef ID_EVENT_ADJUST_TIME
  {.DoubleFlag=0,.StartSave=0,.EndSave=1,.StartCount=1,.EndCount=3,.EventName="Adjust RTC"},    //Уʱ-----------------26----HUCK Will do
  #endif  
  
#ifdef ID_EVENT_RTCERR_RUN                          //����ʱ����-----------27----HUCK Will do
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=15,.EventName="RTC Err Running"},
#endif  
  
#ifdef ID_EVENT_RTCERR_PWRON                        //�ϵ�ʱ����-----------28----HUCK Will do
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=5,.EventName="RTC Err Power On"},
#endif

#ifdef ID_EVENT_EPPROM_FAULT                //EEPROM��-------------29----HUCK Will do(ֻ���ϵ�ʱ���)
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=20,.EndCount=0,.EventName="Inter Memory Err"},
#endif 

#ifdef ID_EVENT_ADJUST_MEASU
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Adjust Measure"},          //У��-----------------30----PUCK Will do
#endif

#ifdef ID_EVENT_MODI_ENERG  
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=20,.EndCount=0,.EventName="Remedy Energ Error"},           //��������-------------31----HUCK Will do
#endif

#ifdef ID_EVENT_A_VOLT_OVERLOAD                     //A���ѹ��ѹ----------32
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpwnVolt_Time,.GetInstStatus=&Check_Up_Volt,.EventName="Volt A Overload"},
#endif

#ifdef ID_EVENT_B_VOLT_OVERLOAD                     //B���ѹ��ѹ----------33
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpwnVolt_Time,.EventName="Volt B Overload"},
#endif

#ifdef ID_EVENT_C_VOLT_OVERLOAD                     //C���ѹ��ѹ----------34
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpwnVolt_Time,.EventName="Volt C Overload"},
#endif

#ifdef ID_EVENT_ENERG_FREEZ    //��������-------------35----HUCK Will do
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Energ Freeze"},
#endif

#ifdef ID_EVENT_POWER_ALARM    //������-----------36-ͬ�������������ʣ�HUCK)
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="Overlimted Power Alarm"},
#endif

#ifdef ID_EVENT_POWER_SWITCH    //��������բ-----------37  
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="Overlimted Power Switch Toggle"}, 
#endif

#ifdef ID_EVENT_A_LOSS_PARSE                               //A�����--------------38  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutParse_Time,.GetInstStatus=&Check_Loss_Parse,.EventName="A Loss Parse"},
#endif

#ifdef ID_EVENT_B_LOSS_PARSE                                //B�����--------------39  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutParse_Time,.EventName="B Loss Parse"},
#endif

#ifdef ID_EVENT_C_LOSS_PARSE                           //C�����--------------40  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutParse_Time,.EventName="C Loss Parse"},
#endif

#ifdef ID_EVENT_A_NEG_CURR                        //A���������----------41 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.NegCurr_Time,.GetInstStatus=&Check_Neg_Curr,.EventName="A Cur Neg Direction"},
#endif

#ifdef ID_EVENT_B_NEG_CURR               //B���������----------42  
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.NegCurr_Time,.EventName="B Cur Neg Direction"},
#endif

#ifdef ID_EVENT_C_NEG_CURR                  //C���������----------43 
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.NegCurr_Time,.EventName="C Cur Neg Direction"},
#endif 

#ifdef ID_EVENT_SUM_NEG_CURR                //�ܵ��������й����ʷ��ࣩ-----------44 
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="Sum Cur Neg Direction"},    
#endif 

#ifdef ID_EVENT_CMD_ALARM   //�����(ͨ�����ǿ�б���)--------45
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Cmd Alarm"},    
#endif 

 

#ifdef ID_EVENT_ERR_PASSWD   //�����---------------46----HUCK Will do
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Password Err"},    
#endif  


#ifdef ID_EVENT_METER_LOCK  //�Ե����(������Ҫ����)ʱ����������������������ڵ���5�κ�--------47
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=2,.EndCount=2,.EventName="Prg Meter Event"},     
#endif  

#ifdef ID_EVENT_AB_FUNC_KEY   //���ܼ�ʶ��ABģʽ�л���ť--------48
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=3,.EndCount=1,.GetInstStatus=&Check_AB_Func_Key,.EventName="Func AB Mode Switch Key"},    
#endif    

#ifdef ID_EVENT_POWER_OFF                                    //�ϵ��¼�--------49----PUCK 
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Meter Power On"},
#endif    

#ifdef ID_DEMAND_ARRIVE                                    //������--------50----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Demand Time Expired!"},
#endif  
  
#ifdef ID_OVER_LOAD                                    //���ɿ��Ʊ���--------51-ͬ�������������ʣ�HUCK)
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=20,.EndCount=0,.EventName="OverLoad Ctrol Alarm"},
#endif  
  
#ifdef ID_PAY_ALARM                                   //Ԥ���ѱ���--------52----HUCK Will do 
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Fees Not Enough"},
#endif

#ifdef ID_PARSE_SWITCH                                 //ʱ���л�--------53-----HUCK Will do 
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Time Prase Switch"},
#endif

#ifdef ID_MEASURE_ERROR                               //��������(˲̬��)--------54
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=15,.EventName="Measure Error Event"},
#endif

#ifdef ID_METER_ADDR_EN                         //���ñ��ַ��ť----------55 
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=1,.GetInstStatus=&Check_MeterAddr_Key,.EventName="Set Meter Addr Key"},    
#endif

#ifdef ID_EVENT_ALL_LOSS_VOLT                           //ȫʧѹ--------56
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=30,.EndCount=20,.EventName="All Loss Volt"},
#endif  

#ifdef ID_EVENT_AB_LOSS_VOLT                               //ABʧѹ------------------57
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_B Loss Volt"},
#endif

#ifdef ID_EVENT_AC_LOSS_VOLT                               //ACʧѹ------------------58
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_C Loss Volt"},
#endif

#ifdef ID_EVENT_BC_LOSS_VOLT                               //BCʧѹ------------------59
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="B_C Loss Volt"},
#endif

#ifdef ID_EVENT_ABC_LOSS_VOLT                               //ABCʧѹ------------------60
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_B_C Loss Volt"},
#endif

#ifdef ID_EVENT_PROG                                      //����¼������ò���-----------61
  {.DoubleFlag=0,.StartSave=0,.EndSave=1,.EndUnit=1,.StartCount=1,.EndCount=14400,.EventName="Prog Data Event"},
#endif


#ifdef ID_EVENT_CLR_ALL_DATA                                   //��������-----------62
  {.DoubleFlag=0,.StartSave=1,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=5,.EventName="All Data Clear Event"},
#endif


#ifdef ID_EVENT_POS_ACT_DEMAND_EXCEED                                   //�����й���������--------63(HUCK����) 
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.GetInstStatus=&Check_Demand_Exceed,.EventName="Pos Demand Exceed",\
 },
#endif

#ifdef ID_EVENT_NEG_ACT_DEMAND_EXCEED                                   //�����й���������------------64(HUCK����) 
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Neg Demand Exceed"},  
#endif 


#ifdef ID_EVENT_Q1_REAC_DEMAND_EXCEED                            //һ�����޹���������--------65(HUCK����)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q1 Demand Alarm"},
#endif


#ifdef ID_EVENT_Q2_REAC_DEMAND_EXCEED                               //�������޹���������--------66(HUCK����)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q2 Demand Alarm"},
#endif


#ifdef ID_EVENT_Q3_REAC_DEMAND_EXCEED                                //�������޹���������---------67(HUCK����)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q3 Demand Alarm"},
#endif

#ifdef ID_EVENT_Q4_REAC_DEMAND_EXCEED                               //�������޹���������---------68(HUCK����)
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverDe_Time,.EventName="Q4 Demand Alarm"},
#endif



#ifdef ID_EVENT_AB_LOSS_CURR                                //AB��ʧ��--------------69
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_B Loss Cur"},
#endif
  
#ifdef ID_EVENT_AC_LOSS_CURR                                //AC��ʧ��--------------70
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="A_C Loss Cur"},
#endif  
  
#ifdef ID_EVENT_BC_LOSS_CURR                                //BC��ʧ��--------------71
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="B_C Loss Cur"},
#endif  

#ifdef ID_EVENT_ALL_LOSS_CURR                                //ȫʧ��--------72
 {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=30,.EndCount=20,.EventName="Loss All Cur",\
 },
#endif 

#ifdef ID_EVENT_DOWN_COVER_OPEN                           //���˸�(��˸�)--------73
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=5,.EndCount=5,.GetInstStatus=&Check_DownCover,.EventName="Down Cover Opened"},
#endif



#ifdef ID_EVENT_DOOR_OPEN                                  //������װ����--------74
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=5,.EndCount=5,.EventName="Door Opened"},
#endif


  
#ifdef ID_SLIP_ARRIVE                                 //���--------75
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.StartCount=1,.EndCount=0,.EventName="Slipe Time Arrived"},
#endif 

#ifdef ID_ALARM_OUT               //�Ƿ��б����¼������������������LCD_LED�����������ű���--------76
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.StartCount=3,.EndCount=1,.GetInstStatus=&Sound_LED_LCD_Port_Alarm,.EventName="Event Alarm Exist"},
#endif

#ifdef ID_CLR_DEMAND_KEY    //�ֶ���������ť--------77
  {.DoubleFlag=1,.StartSave=0,.EndSave=0,.EndUnit=1,.StartCount=5,.EndCount=10,.GetInstStatus=&Check_ClrDemand_Key,.EventName="Clr Demand Key Press"},
#endif
  
#ifdef ID_EVENT_EXT_PROG     //����¼������ò���--------78(ͬ ID_EVENT_PROG,ӦHUCKGD��������)
  {.DoubleFlag=0,.StartSave=1,.EndSave=1,.EndUnit=1,.StartCount=1,.EndCount=10,.EventName="Extern Prog Data Event"},
#endif


#ifdef ID_EVENT_OSC_ERR      //��Ƭ��ʱ��ϵͳ����--------79
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.GetInstStatus=&Monitor_Meter_System_Osc,.EventName="MCU Osc System Error"},                
#endif  


#ifdef ID_EVENT_A_OVER_CURR     //A�������--------80
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpCurr_Time,.GetInstStatus=&Check_Up_Curr,.EventName="A Over Cur"},
#endif

#ifdef ID_EVENT_B_OVER_CURR     //B�������--------81
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpCurr_Time,.EventName="B Over Cur"}, 
#endif
  
#ifdef ID_EVENT_C_OVER_CURR       //C�������--------82
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.UpCurr_Time,.EventName="C Over Cur"},
#endif
 

#ifdef ID_EVENT_DATE                                      //ʱ�α��̣�--------83
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Date Prog"},
#endif

#ifdef ID_EVENT_YEAR                                      //ʱ�����̣�--------84
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Year Prog"},
#endif

#ifdef ID_EVENT_WEEK                                      //�����ձ�̣�--------85
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Week Prog"},
#endif

#ifdef ID_EVENT_HOLIDAY                                      //�ڼ��ձ�̣�--------86
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Holiday Prog"},
#endif

#ifdef ID_EVENT_ACPWR                                        //�й���Ϸ�ʽ��̣�--------87
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="AcPower Group Prog"},
#endif

#ifdef ID_EVENT_REACPWR1                                       //�޹���Ϸ�ʽ1��̣�--------88
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Reacpower Group1 Prog"},
#endif

#ifdef ID_EVENT_REACPWR2                                      //�޹���Ϸ�ʽ2��̣�--------89
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Reacpower Group2 Prog"},
#endif

#ifdef ID_EVENT_SETTLE_DATE                                       //�����ձ�̣�--------90
  {.DoubleFlag=0,.StartSave=0,.EndSave=0,.EndUnit=1,.ForbitEnd=1,.StartCount=1,.EndCount=KEEP_TIME_MIN,.EventName="Settle Date Prog"},
#endif


#ifdef ID_EVENT_REMOTE_RELAY_ON                                //Զ�̺�բ,˲̬���� HUCK ����--------91
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Switch On Toggle"},
#endif

#ifdef ID_EVENT_REMOTE_RELAY_OFF                               //Զ����բ,˲̬���� HUCK ����--------92
  {.DoubleFlag=1,.StartSave=1,.EndSave=0,.StartCount=1,.EndCount=1,.EventName="Switch Off Toggle"},
#endif

#ifdef ID_EVENT_RELAY_ON                                        ///��բ--------93
  {.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Relay On"},
#endif

#ifdef ID_EVENT_RELAY_OFF                                        //��բ--------94
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Relay Off",\
},
#endif
 
#ifdef ID_PAY_SWITCH                                        //Ԥ��������--------95
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.StartCount=1,.EndCount=1,.EventName="Pay Relay Off",\
},
#endif


#ifdef ID_EVENT_CURR_NO_EVEN                                       //������ƽ��--------96
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Curr_No1Even_Time,.GetInstStatus=&Check_Curr_NoEven,.EventName="Cur No Even",\
},
#endif


#ifdef ID_EVENT_ALL_FACTOR_LOW                                       //�ܹ�������������--------97  
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.DownPf_Time,.GetInstStatus=&Check_Sum_Factor_Low,.EventName="PF low",\
},
#endif


#ifdef ID_EVENT_A_POWER_EXCEED                                       //������A(����A)-------------98
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverLoad_Time,.GetInstStatus=&Check_Power_Exceed,.EventName="A Power Exceed",\
},
#endif

#ifdef ID_EVENT_B_POWER_EXCEED                                       //������B(����B)-------------99
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverLoad_Time,.EventName="B Power Exceed",\
},
#endif


#ifdef ID_EVENT_C_POWER_EXCEED                                       //������C(����C)-------------100
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.OverLoad_Time,.EventName="C Power Exceed",\
},
#endif

#ifdef ID_EVENT_A_CUT_CURR                                        ///���� A-------------101
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.GetInstStatus=&Check_Cut_Curr,.EventName="A Cut Curr",\
},
#endif

#ifdef ID_EVENT_B_CUT_CURR                                        ///���� B-------------102
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.EventName="B Cut Curr",\
},
#endif

#ifdef ID_EVENT_C_CUT_CURR                                        ///���� C-------------103
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.EventName="C Cut Curr",\
},
#endif

#ifdef ID_EVENT_AUX_POWER                                        //������Դ����-------------104
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.CutCurr_Time,.EventName="Aux Power Off",\
},
#endif

#ifdef ID_CUR_VERY_NOEVEN                                        //�������ز�ƽ��-------------105
{.DoubleFlag=1,.StartSave=1,.EndSave=1,.JudgeTimeSec=&EventInsParaVar.Curr_No1Even_Time,.GetInstStatus=&Check_Cur_Very_Noeven,.EventName="Curr Very No Even",\
}
#endif

};
#endif