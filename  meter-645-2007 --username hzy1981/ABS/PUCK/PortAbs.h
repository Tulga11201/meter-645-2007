
#ifndef PORT_ABS_H
#define PORT_ABS_H



#ifndef PORT_ABS_PUCK
#define PORT_ABS_PUCK_EXT  extern volatile
#else
#define PORT_ABS_PUCK_EXT volatile 
#endif



//���ģʽ
#define LEVEL_MODE        0x00   //��ƽ���ģʽ
#define PULSE_MODE        0x01   //�������ģʽ
#define MULTI_MODE        0x02   //�ɱ����

#define PORT_END   0
#define PORT_START 1


/****************************************�����ǶԸ������ӵ�����*****************************************************/
#define AUX_PORT_PULSE_WD      80    //������������ȣ�ms
#define TOOGLE_PORT_PULSE_WD   80   //��բ��������ȣ�ms

#define APP_TOOGLE_PORT_PULSE_WD      400 //��բ�����ȣ�ms
#define LARGE_RELAY_PULSE_WD           250 //��̵�����բ�����ȣ�ms
/***************************************************���������������*****************************************************/




#define  DEMAND_OUT_MODE Mode_Word.Mode[2].Bit.Bit4 //ģʽ��3 bit4:�����ź������ʽ,1:����������,0:������ʱ��


//ι���ź�
#ifdef RST_IC_7X6_EN
  #define Clear_Ext_Dog()       B_WTD_0
#else
  #define Clear_Ext_Dog()       {B_WTD_1;  B_WTD_0; B_WTD_0; B_WTD_1;}    //һ��B_WTD_0��Լ 100ns
#endif

#define BEEP_MODE_50        50
#define BEEP_MODE_100       100
#define BEEP_MODE_150       150
#define BEEP_MODE_200       200
#define BEEP_MODE_300       300
#define BEEP_MODE_400       400
#define BEEP_MODE_500       500

//����PORT�豸ID
#define EXT_ID_NONE         0  //��Ч����
//#define EXT_ID_AP_DIR             (EXT_ID_NONE+1)         //�й����巽��-------------------------------1
//#define EXT_ID_RP_DIR             (EXT_ID_AP_DIR+1)        //�޹����巽��----------------------------2
#define EXT_ID_SEC_EN             (EXT_ID_NONE+1)        //������ʹ��------------------------------3
#define INTER_ID_TOGGLE_DIS        (EXT_ID_SEC_EN+1)       //��բָʾ��---------------------------------4
#define INTER_ID_ALARM_DIS        (INTER_ID_TOGGLE_DIS+1)  //����ָʾ��---------------------------------5

#define EXT_ID_AUX_ALARM          (INTER_ID_ALARM_DIS+1)  //�������ӱ������-----------------------------6
#define EXT_ID_TOGGLE             (EXT_ID_AUX_ALARM+1)     //��բ���-----------------------------------7

//#define EXT_ID_ACPOWER            (EXT_ID_TOGGLE+1)       //�й�����-----------------------------------8
//#define EXT_ID_REACPOWER          (EXT_ID_ACPOWER+1)      //�޹�����-----------------------------------9
#define EXT_ID_DEMAND             (EXT_ID_TOGGLE+1)    //�������ڵ����--------------------------10
#define EXT_ID_SLIPE              (EXT_ID_DEMAND+1)       //�����������-------------------------------11
#define EXT_ID_PARSE              (EXT_ID_SLIPE+1)        //ʱ���л����--------------------------------12
//#define GERNAL_ID_ACPOWER         (EXT_ID_PARSE+1)        //���й�����---------------------------------13
//#define GERNAL_ID_REACPOWER       (GERNAL_ID_ACPOWER+1)   //���޹�����---------------------------------14
#define INTER_ID_ALARM_BEEP       (EXT_ID_PARSE+1) //��������------------------------------------15
#define INTER_ID_RELAY_ON        (INTER_ID_ALARM_BEEP+1)  //���崥��ʽ�̵�������------------------------16
#define INTER_ID_RELAY_OFF       (INTER_ID_RELAY_ON+1)     //���崥��ʽ�̵����ر�-----------------------17
  

//����PORT�豸ID��Ŀ
#define MIN_PORT_DI      (EXT_ID_NONE+1)
#define MAX_PORT_DI      (INTER_ID_RELAY_OFF)
#define MAX_PORT_NUM     (MAX_PORT_DI+1)


//����LEVEL_PORT�豸ID��Ŀ
#define MIN_LEVEL_PORT_DI       (EXT_ID_NONE+1)
#define MAX_LEVEL_PORT_DI       EXT_ID_TOGGLE


//����PULSE_PORT�豸ID��Ŀ
#define MIN_PULSE_PORT_DI      EXT_ID_AUX_ALARM
#define MAX_PULSE_PORT_DI      INTER_ID_RELAY_OFF

typedef struct
{ 
  INT8U InitFlag;           //���ӳ�ʼ�����
  INT8U Status;             //״̬��0��ʾ�޶�����1��ʾ������2��ʾ���У�3��ʾ������
  INT16U CurCount;          //��ǰ1ms������0��ʾִ�ж������������65536ms��ĳһ�ֻ��е�������
  INT16U CurCountBak;       //ĳһ�ֻ��е������ȱ���
  //INT16U LoopCount;         //�ֻ�����ÿһ���ֻس�һ������
  INT8U CS[CS_BYTES];
}PORT_HANDER;
PORT_ABS_PUCK_EXT PORT_HANDER Ext_Port_Hander[MAX_PORT_NUM];


typedef struct{
  INT8U Head;
  INT8U Mode;            //����һ������ģʽ�֣��ϵ��ظ����������
  INT8U ReadMode;        //����һ������ģʽ��
  INT8U Tail;
}MULIT_PORT_MODE;

PORT_ABS_PUCK_EXT MULIT_PORT_MODE  Multi_Port_Mode;//={CHK_BYTE, 0, 0, CHK_BYTE};

 //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л���
#define SEC_OUT_PUT_EN        (Multi_Port_Mode.Mode==0)
#define DEMAND_OUT_PUT_EN     (Multi_Port_Mode.Mode==1)
#define SLIPE_OUT_PUT_EN      (Multi_Port_Mode.Mode==1)
#define PARSE_OUT_PUT_EN      (Multi_Port_Mode.Mode==2)



#define PORT_OUTPUT_MODE      Multi_Port_Mode.ReadMode

#define MODE_ERR     0     //δ֪ģʽ
#define MODE_RUN     1     //�ֳ�����ģʽ�������������Ϣ����Ȩ��
#define MODE_DEBUG   2     //����ģʽ�������������Ϣ����Ȩ��
#define MODE_FAC     4     //����ģʽ�������������Ϣ���߱����Ȩ��
#define MODE_TEST    8     //�Լ�ģʽ�������������Ϣ����Ȩ��


void Beep_For_Measu_Alarm_PUCK(INT8U ErrInfo);
void Beep_Only_Alarm_PUCK(void);
void ExtPort_xMs_Hook(void);
void Init_All_Port(INT32U Mode);
void Port_Out_Pub(INT8U Id,INT16U Para);
INT8U Get_Meter_Hard_Mode(void);

INT8U Get_Sec_Out_En(void);
INT8U Get_Parse_Out_En(void);
INT8U Get_Demand_Out_En(void);
INT8U Get_Slipe_Out_En(void);
INT8U Get_FeeAlarm_Out_En(void);
INT8U Get_GridAlarm_Out_En(void);
void Init_Sec_Pulse(void);
INT8U Get_AuxPort_Out(void);
INT8U Get_Toogle_Out(void);
void Wait_For_Power_On(void);
INT8U Port_Pulse_Out(INT8U Id,INT16U PulseWidth);
INT8U Port_Level_Out(INT8U Id,INT8U Level);
void Get_Port_Out_Mode(void);
#endif