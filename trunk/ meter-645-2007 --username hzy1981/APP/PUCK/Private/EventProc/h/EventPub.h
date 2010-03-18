#ifndef EVENTPUB_VAR
#define EVENTPUB_VAR


#ifndef EVENTPUB_C
#define EVENTPUB_C_EXT  extern volatile
#else
#define EVENTPUB_C_EXT volatile
#endif



//�������¼�����ID,�������壬��Э���޹�,ע�⣺��֤�����¼�һ���������ģ����޸�ʱ��ע�⣡
#define ID_EVENT_NO_VALID           0  	                      //��Ч�¼�--------0
#define ID_EVENT_A_LOSS_VOLT        (ID_EVENT_NO_VALID+1)  	       //A��ʧѹ--------1
#define ID_EVENT_B_LOSS_VOLT        (ID_EVENT_A_LOSS_VOLT+1)  	      //B��ʧѹ--------2
#define ID_EVENT_C_LOSS_VOLT        (ID_EVENT_B_LOSS_VOLT+1)	      //C��ʧѹ--------3

#define ID_EVENT_A_LOSS_CURR        (ID_EVENT_C_LOSS_VOLT+1)         //A��ʧ��--------4
#define ID_EVENT_B_LOSS_CURR        (ID_EVENT_A_LOSS_CURR+1)  	      //B��ʧ��--------5
#define ID_EVENT_C_LOSS_CURR        (ID_EVENT_B_LOSS_CURR+1)	      //C��ʧ��--------6

#define ID_EVENT_PRGKEY_ON          (ID_EVENT_C_LOSS_CURR+1)         //��̼���--------7

#define ID_EVENT_CUR_NEG_SEQ        (ID_EVENT_PRGKEY_ON+1)           //����������--------8
#define ID_EVENT_VOLT_NEG_SEQ       (ID_EVENT_CUR_NEG_SEQ+1)        //��ѹ������--------9

#define ID_EVENT_A_VOLT_LESS        (ID_EVENT_VOLT_NEG_SEQ+1)        //A���ѹǷѹ--------10
#define ID_EVENT_B_VOLT_LESS        (ID_EVENT_A_VOLT_LESS+1)        //B���ѹǷѹ--------11
#define ID_EVENT_C_VOLT_LESS        (ID_EVENT_B_VOLT_LESS+1)	      //C���ѹǷѹ--------12

#define ID_EVENT_DEMAND_ALARM       (ID_EVENT_C_VOLT_LESS+1)         //����������--------13
//#define ID_EVENT_DEMAND_SWITCH      (ID_EVENT_DEMAND_ALARM+1)        //��������բ--------14
#define ID_EVENT_VOLT_NO_EVEN       (ID_EVENT_DEMAND_ALARM+1)      //��ѹ��ƽ��--------15
#define ID_EVENT_RESET              (ID_EVENT_VOLT_NO_EVEN+1)        //��λ--------16
#define ID_EVENT_CLR_DEMAND_COM     (ID_EVENT_RESET+1)             //ͨ��������--------17
#define ID_EVENT_CLR_DEMAND_MAN     (ID_EVENT_CLR_DEMAND_COM+1)    //�ֶ�������--------18
#define ID_EVENT_CLR_PROCESS        (ID_EVENT_CLR_DEMAND_MAN+1)    //�����--------19
//#define ID_EVENT_CLR_VOLT_PASS      (ID_EVENT_CLR_PROCESS+1)      //���ѹ�ϸ���--------20
#define ID_EVENT_SET_ENERG          (ID_EVENT_CLR_PROCESS+1)      //���ó�ʼ����--------21
#define ID_EVENT_UP_COVER_OPEN      (ID_EVENT_SET_ENERG+1)        //�����--------22
//#define ID_EVENT_LEAD_COVER_OPEN    (ID_EVENT_UP_COVER_OPEN+1)    //��Ǧ����--------23
#define ID_EVENT_RTC_BAT_LOW        (ID_EVENT_UP_COVER_OPEN+1)     //ʱ�ӵ��Ƿѹ--------24
#define ID_EVENT_LOWPWR_BAT_LOW     (ID_EVENT_RTC_BAT_LOW+1)     //�͹��ĵ��Ƿѹ--------25
#define ID_EVENT_ADJUST_TIME        (ID_EVENT_LOWPWR_BAT_LOW+1)   //Уʱ--------26
#define ID_EVENT_RTCERR_RUN         (ID_EVENT_ADJUST_TIME+1)      //����ʱ����--------27
#define ID_EVENT_RTCERR_PWRON       (ID_EVENT_RTCERR_RUN+1)      //�ϵ�ʱ����--------28
//#define ID_EVENT_EPPROM_FAULT       (ID_EVENT_RTCERR_PWRON+1)    //EEPROM��--------29
//#define ID_EVENT_ADJUST_MEASU       (ID_EVENT_EPPROM_FAULT+1)    //У��--------30
//#define ID_EVENT_MODI_ENERG         (ID_EVENT_EPPROM_FAULT+1)    //��������--------31

#define ID_EVENT_A_VOLT_OVERLOAD    (ID_EVENT_RTCERR_PWRON+1)        //A���ѹ��ѹ--------32
#define ID_EVENT_B_VOLT_OVERLOAD    (ID_EVENT_A_VOLT_OVERLOAD+1)   //B���ѹ��ѹ--------33
#define ID_EVENT_C_VOLT_OVERLOAD    (ID_EVENT_B_VOLT_OVERLOAD+1)   //C���ѹ��ѹ--------34
//#define ID_EVENT_ENERG_FREEZ        (ID_EVENT_C_VOLT_OVERLOAD+1)   //��������--------35


//#define ID_EVENT_POWER_ALARM        (ID_EVENT_C_VOLT_OVERLOAD+1)      //������-------------36
//#define ID_EVENT_POWER_SWITCH       (ID_EVENT_POWER_ALARM+1)       //��������բ--------37


#define ID_EVENT_A_LOSS_PARSE       (ID_EVENT_C_VOLT_OVERLOAD+1)     //A�����--------38
#define ID_EVENT_B_LOSS_PARSE       (ID_EVENT_A_LOSS_PARSE+1)         //B�����--------39
#define ID_EVENT_C_LOSS_PARSE       (ID_EVENT_B_LOSS_PARSE+1)         //C�����--------40

#define ID_EVENT_A_NEG_CURR         (ID_EVENT_C_LOSS_PARSE+1)        //A���������--------41
#define ID_EVENT_B_NEG_CURR         (ID_EVENT_A_NEG_CURR+1)          //B���������--------42
#define ID_EVENT_C_NEG_CURR         (ID_EVENT_B_NEG_CURR+1)          //C���������--------43
#define ID_EVENT_SUM_NEG_CURR       (ID_EVENT_C_NEG_CURR+1)         //�ܵ��������й����ʷ��ࣩ--------44
#define ID_EVENT_CMD_ALARM          (ID_EVENT_SUM_NEG_CURR+1)     //�����(ͨ�����ǿ�б���)--------45
#define ID_EVENT_ERR_PASSWD         (ID_EVENT_CMD_ALARM+1)         //�����--------46

#define ID_EVENT_METER_LOCK         (ID_EVENT_ERR_PASSWD+1)       //�Ե����(������Ҫ����)ʱ����������������������ڵ���5�κ�--------47

#if METER_DEBUG_EN
  #define ID_EVENT_AB_FUNC_KEY        (ID_EVENT_METER_LOCK+1)         //AB�л����ܼ�ʶ��--------48
  #define ID_EVENT_POWER_OFF          (ID_EVENT_AB_FUNC_KEY+1)        //�����¼�--------49----PUCK 
#else
  //#define ID_EVENT_AB_FUNC_KEY        (ID_EVENT_METER_LOCK+1)         //AB�л����ܼ�ʶ��--------48
  #define ID_EVENT_POWER_OFF          (ID_EVENT_METER_LOCK+1)        //�����¼�--------49----PUCK 
#endif

#define ID_DEMAND_ARRIVE            (ID_EVENT_POWER_OFF+1)          //�������ڵ�--------50
//#define ID_OVER_LOAD                (ID_DEMAND_ARRIVE+1)            //���ɿ��Ʊ���--------51
#define ID_PAY_ALARM                (ID_DEMAND_ARRIVE+1)              //Ԥ���ѱ���--------52
#define ID_PARSE_SWITCH             (ID_PAY_ALARM+1)             //ʱ���л�--------53
//#define ID_MEASURE_ERROR            (ID_PARSE_SWITCH+1)           //��������--------54
#define ID_METER_ADDR_EN            (ID_PARSE_SWITCH+1)          //���ñ��ַ��ť-------55
#define ID_EVENT_ALL_LOSS_VOLT      (ID_METER_ADDR_EN+1)        //ȫʧѹ-------56

/*
#define ID_EVENT_AB_LOSS_VOLT       (ID_EVENT_ALL_LOSS_VOLT+1)   //ABʧѹ------------------57
#define ID_EVENT_AC_LOSS_VOLT       (ID_EVENT_AB_LOSS_VOLT+1)    //ACʧѹ------------------58
#define ID_EVENT_BC_LOSS_VOLT       (ID_EVENT_AC_LOSS_VOLT+1)   //BCʧѹ------------------59
#define ID_EVENT_ABC_LOSS_VOLT      (ID_EVENT_BC_LOSS_VOLT+1)   //ABCʧѹ------------------60
*/

#define ID_EVENT_PROG               (ID_EVENT_ALL_LOSS_VOLT+1)  //����¼������ò���-----------61
#define ID_EVENT_CLR_ALL_DATA       (ID_EVENT_PROG+1)           //��������-----------62
#define ID_EVENT_POS_ACT_DEMAND_EXCEED  (ID_EVENT_CLR_ALL_DATA+1)          //�����й���������--------63(HUCK����) 
#define ID_EVENT_NEG_ACT_DEMAND_EXCEED (ID_EVENT_POS_ACT_DEMAND_EXCEED+1)   //�����й���������------------64(HUCK����)  
#define ID_EVENT_Q1_REAC_DEMAND_EXCEED   (ID_EVENT_NEG_ACT_DEMAND_EXCEED+1)          //һ�����޹���������--------65
#define ID_EVENT_Q2_REAC_DEMAND_EXCEED   (ID_EVENT_Q1_REAC_DEMAND_EXCEED+1)                //�������޹���������--------66
#define ID_EVENT_Q3_REAC_DEMAND_EXCEED   (ID_EVENT_Q2_REAC_DEMAND_EXCEED+1)         //�������޹���������--------67
#define ID_EVENT_Q4_REAC_DEMAND_EXCEED   (ID_EVENT_Q3_REAC_DEMAND_EXCEED+1)    //�������޹���������--------68

/*
#define ID_EVENT_AB_LOSS_CURR       (ID_EVENT_Q4_REAC_DEMAND_EXCEED+1)   //ABʧ��------------------69
#define ID_EVENT_AC_LOSS_CURR       (ID_EVENT_AB_LOSS_CURR+1)    //ACʧ��------------------70
#define ID_EVENT_BC_LOSS_CURR       (ID_EVENT_AC_LOSS_CURR+1)   //BCʧ��------------------71
#define ID_EVENT_ALL_LOSS_CURR      (ID_EVENT_BC_LOSS_CURR+1)   //ȫʧ��-------------72
*/


#define ID_EVENT_DOWN_COVER_OPEN   (ID_EVENT_Q4_REAC_DEMAND_EXCEED+1)          //���˸�--------73


//#define ID_EVENT_DOOR_OPEN          (ID_EVENT_DOWN_COVER_OPEN+1)        //������װ����--------74

#define ID_SLIP_ARRIVE              (ID_EVENT_DOWN_COVER_OPEN+1)          //���--------75
#define ID_ALARM_OUT                (ID_SLIP_ARRIVE+1)             //�Ƿ��б����¼������������������LCD_LED�����������ű���--------76
#define ID_CLR_DEMAND_KEY           (ID_ALARM_OUT+1)             //�ֶ���������ť--------77
#define ID_EVENT_EXT_PROG           (ID_CLR_DEMAND_KEY+1)         //����¼������ò���--------78(ͬ ID_EVENT_PROG,ӦHUCKGD��������)

//#define ID_EVENT_OSC_ERR            (ID_EVENT_EXT_PROG+1)        //��Ƭ��ʱ��ϵͳ����--------79

#define ID_EVENT_A_OVER_CURR        (ID_EVENT_EXT_PROG+1)        //A�������--------80
#define ID_EVENT_B_OVER_CURR        (ID_EVENT_A_OVER_CURR+1)        //B�������--------81
#define ID_EVENT_C_OVER_CURR        (ID_EVENT_B_OVER_CURR+1)        //C�������--------82

#define ID_EVENT_DATE               (ID_EVENT_C_OVER_CURR+1)           //ʱ�α��̣�--------83
#define ID_EVENT_YEAR               (ID_EVENT_DATE+1)        //ʱ�����̣�--------84
#define ID_EVENT_WEEK               (ID_EVENT_YEAR+1)        //�����ձ�̣�--------85
#define ID_EVENT_HOLIDAY            (ID_EVENT_WEEK+1)         //�ڼ��ձ�̣�--------86
#define ID_EVENT_ACPWR              (ID_EVENT_HOLIDAY+1)        //�й���Ϸ�ʽ��̣�--------87
#define ID_EVENT_REACPWR1           (ID_EVENT_ACPWR+1)        //�޹���Ϸ�ʽ1��̣�--------88
#define ID_EVENT_REACPWR2           (ID_EVENT_REACPWR1+1)        //�޹���Ϸ�ʽ2��̣�--------89
#define ID_EVENT_SETTLE_DATE        (ID_EVENT_REACPWR2+1)        //�����ձ�̣�--------90


//#define ID_EVENT_REMOTE_RELAY_ON    (ID_EVENT_SETTLE_DATE+1)         //Զ�̺�բ--------91
//#define ID_EVENT_REMOTE_RELAY_OFF   (ID_EVENT_REMOTE_RELAY_ON+1)    //Զ����բ--------92

#define ID_EVENT_RELAY_ON           (ID_EVENT_SETTLE_DATE+1)    //��բ--------93
#define ID_EVENT_RELAY_OFF          (ID_EVENT_RELAY_ON+1)    //��բ--------94

//#define ID_PAY_SWITCH               (ID_EVENT_RELAY_OFF+1)     //Ԥ��������--------95

#define ID_EVENT_CURR_NO_EVEN       (ID_EVENT_RELAY_OFF+1)              //������ƽ��--------96

#define ID_EVENT_ALL_FACTOR_LOW         (ID_EVENT_CURR_NO_EVEN+1)     //�ܹ�������������--------97  
#define ID_EVENT_A_POWER_EXCEED       (ID_EVENT_ALL_FACTOR_LOW+1)       //������A(����A)-------------98
#define ID_EVENT_B_POWER_EXCEED       (ID_EVENT_A_POWER_EXCEED+1)       //������B(����B)-------------99
#define ID_EVENT_C_POWER_EXCEED       (ID_EVENT_B_POWER_EXCEED+1)       //������C(����C)-------------100

#define ID_EVENT_A_CUT_CURR           (ID_EVENT_C_POWER_EXCEED+1)       //���� A-------------101
#define ID_EVENT_B_CUT_CURR         (ID_EVENT_A_CUT_CURR+1)             //���� B-------------102
#define ID_EVENT_C_CUT_CURR          (ID_EVENT_B_CUT_CURR+1)             //���� C-------------103

#define ID_EVENT_AUX_POWER           (ID_EVENT_C_CUT_CURR+1)             //������Դ����-------------104
#define ID_CUR_VERY_NOEVEN           (ID_EVENT_AUX_POWER+1)             //�������ز�ƽ��-------------105


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
  //U_Byte_Bit  SERR;               //��ȫ��֤������Ϣ��
  
  U_Byte_Bit  Volt_LossMiss;      //����ʧѹ/���࣬DI:DI_LOW_VOL
  U_Byte_Bit  NegCurr_Qudrant;    //�������������/��������ޣ�DI_CURRENT_QUADRANT
  U_Byte_Bit  Key_Event;          //�����̼���/���߶̽�/������λ/���������DI:DI_METER_PERIPHERY
  U_Byte_Bit  Comm_Status;        //����ͨ��״̬�֣�DI:DI_MODULE_STATUS
  
  /*
  //��չ�����ݵĹ��ʷ���״̬��
  U_Byte_Bit  Ext_Ac_Power_Dir;        //�й������־�ֽڣ�1�ֽڣ�0-3λΪ�ܡ�a��b��cԪ������4�ֽ�Ϊ0��
  U_Byte_Bit  Ext_Reac_Power_Dir;        //�޹������־�ֽڣ�1�ֽڣ�0-3λΪ�ܡ�a��b��cԪ������4�ֽ�Ϊ0��
  
  U_Byte_Bit  GD_Meter_Stat;        //�㶫�����״̬��
  U_Byte_Bit  GD_PwrDir_Stat;       //�㶫���й����ʷ���״̬��
  U_Byte_Bit  GD_LossVolt_Stat;        //�㶫��ʧѹ״̬��
  U_Byte_Bit  GD_LossCurr_Stat;        //�㶫��ʧ��״̬��
  U_Byte_Bit  GD_Hard_Stat;        //�㶫��Ӳ��״̬��
  //U_Byte_Bit  GD_Prog_Stat;        //�㶫�����״̬��(HUCK)
  */
  INT8U CS[CS_BYTES];
}POWER_STATS;


EVENTPUB_C_EXT POWER_STATS Meter_Run_Status;

typedef struct{
  INT8U  Occur:1;         //�¼�������־�����������
  
  INT8U  Status:1;        //�¼�������״̬λ���ⲿ���ʣ����ʺ󣬸�λ����������Ƿ�Ӧ���¼��ķ�����0-------���¼�������1-------�¼�������  
  INT8U  Status1:1;       //�¼�������־���ݣ��ⲿ����1�����ʺ󣬸�λ���
  INT8U  Status2:1;       //�¼�������־���ݣ��ⲿ����2�����ʺ󣬸�λ���
  INT8U  Status3:1;       //�¼�������־���ݣ��ⲿ����3�����ʺ󣬸�λ���
  INT8U  Status4:1;       //�¼�������־���ݣ��ⲿ����4�����ʺ󣬸�λ���  
  INT8U  Reserved:2;      //Ԥ��
  INT8U  Mins;           //�ּ�����
  INT8U  StartCount;      //�¼�����������
  INT8U  EndCount;        //�¼�����������  
  INT8U  CS[CS_BYTES];
}EventProcStatus;         //�¼�����״̬


EVENTPUB_C_EXT EventProcStatus EventProcStatusVar[MAX_EVENT_NUM]; 



#define POWER_OFF        0x37   //����
#define POWER_ON         0xF6   //�ϵ�
#define ABNORMAL_RESET   0xE8   //�쳣��λ



typedef struct{
  INT8U  Power;
  INT8U  CS[CS_BYTES];
}POWER_STATUS;         //�ϵ紦��״̬

NO_INIT EVENTPUB_C_EXT POWER_STATUS Power_Status;

typedef struct{
  INT16U  Volt_Not_Even;    //2λС��
  INT16U  Curr_Not_Even;    //2λС��
  INT8U  CS[CS_BYTES];
}NOT_EVEN_DATA;         //��ƽ����

EVENTPUB_C_EXT NOT_EVEN_DATA Not_Even_Data_PUCK;    //��ƽ����

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
