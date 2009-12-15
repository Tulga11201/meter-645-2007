#ifndef POWER_CTRL_H
#define POWER_CTRL_H

#undef EXT
#ifdef POWER_CTRL_C
#define EXT
#else
#define EXT extern
#endif

#define CARD_TESTING 0x4D
#define CARD_TESTED  0x5B
#define CARD_TESTING_DELAY 5

#define SWITCH_OFF_DELAY ((Relay_Status.Off_Delay > 0)?1:0)

//#define RELAY_ON  0x1A //��բ
//#define RELAY_OFF 0x1B //��բ
#define SWITCH_ON     0x1B
#define SWITCH_OFF    0x1A

#define ALARM_ON  0x2A
#define ALARM_OFF 0x2B

#define MAINTAIN_ON   0x3A   //�����־
#define MAINTAIN_OFF 0x3B   //������

#define ALLOW_SWITCH_ON 0x4B //��բ״̬�������բ

#define NEED_HAND_SWITCH_ON_FLAG 0x0C //������0x0F

#define S_OFF_PWR_CTRL   0x00  //������բ
#define S_OFF_PREPAID    0x01  //Ԥ������բ
#define S_OFF_REMOTE_CMD 0x02  //Զ����բ
#define S_OFF_PREPAID_PWR_CTRL 0x03 //Ԥ���Ѹ�����բ
#define S_ON_MAINTAIN    0x04  //�����բ
#define S_ON_OTHER       0x05  //����բ��բ

#define REMOTE_SWITCH_RELAY_LIMIT_ACPOWER 70000 //7kw,��λ0.0001kw

#define REMOTE_CTRL_OK   0
#define REMOTE_CTRL_REDO 1
#define REMOTE_CTRL_ERR  2

#define DIS_ACT_PULSE_INT STOP_CF1  //���й������ж�
#define EN_ACT_PULSE_INT  START_CF1 //���й������ж�

#define PREPAID_POWER_CTRL_UNIT_NUM 15

#define EXT_SWITCH_MODE (Meter_Property_Word.Word[0].Bit.Bit0) //�ⲿ���ؿ��Ʒ�ʽ��0Ϊ��ƽ��1Ϊ���� 
#define INTER_SWITCH_MODE 1 //�ڲ����ؿ��Ʒ�ʽ, 0Ϊ��ƽ��1Ϊ����
//����������������
typedef struct
{
  U_Byte_Bit Word[1];  
  INT8U CS[CS_BYTES];
}S_Meter_Property_Word;

//�����й���������
typedef struct
{
  INT32U Pos_Act_Power_Limit;//�����й���������
  INT32U Neg_Act_Power_Limit; //�����й���������
  
  INT16U Relay_Off_Delay; //��բ��ʱ����λs
  INT16U Relay_On_Delay; //��բ��ʱ����λs
  
  INT8U User_Level;//�û�����
  INT8U CS[CS_BYTES];
}S_Power_Ctrl_Para;

typedef struct
{
  INT16U Relay_Off_Delay;
  INT16U Relay_On_Delay;
  INT8U CS[CS_BYTES];
}S_Relay_Delay_Para;

//Ԥ���Ѹ��ɿ�����ز���
typedef struct
{
   INT32U Max_Power_Pulse; //���ʸ��������� 
   INT8U Max_Power_Mins;   //��󸺺ɼ���ʱ��
   INT8U Max_Power_Switch_Off_Counts; //����������բ����
   
   INT8U CS[CS_BYTES];
}S_Prepaid_Power_Ctrl_Para;

//��¼ÿ�����������
typedef struct
{
  INT8U Head;
  
  INT32U  Pulse_Num[PREPAID_POWER_CTRL_UNIT_NUM]; //������
  INT8U Posi; //��ǰ��¼λ��
  
  INT8U Tail;
}S_Prepaid_Power_Ctrl_Pulse;

//���ɿ�������բ��ʱ
typedef struct
{
  INT8U Switch_Flag;
  INT8U On_Delay;
  INT8U Off_Delay;
   
  INT8U Switch_Status;
  
  INT8U CS[CS_BYTES];
}S_Power_Ctrl_Switch;

//Զ�̿�������բ
typedef struct
{
  INT8U Switch_Flag; //��բ��־--Ӧ�ý�Switch_Flag�ȽϺ���
  //INT8U Switch_Time[6]; //��բ�������ʱ��
  
  INT8U Alarm_Flag; //�����Ŀ��ر�־
  //INT8U Alarm_Time[6]; //��բ�������ʱ��

  INT8U Maintain_Flag; //�����־
  //INT8U Maintain_Time[6]; //�����������ʱ��
  
  INT8U Switch_Status;
  
  INT8U CS[CS_BYTES];
}S_Remote_Ctrl_Switch;

//Ԥ���ѿ�������բ
typedef struct
{
  INT8U Switch_Flag;
  INT8U Alarm_Flag;
  
  INT8U CS[CS_BYTES];
}S_Prepaid_Ctrl_Switch;

//Ԥ���Ѹ��ɿ���״̬����Ҫ�洢
typedef struct
{
  INT8U Switch_Flag;
  INT8U On_Delay;
  INT8U Off_Delay;
  INT8U Off_Counts;
  INT8U CS[CS_BYTES];
}S_Pepaid_Power_Ctrl_Switch;

typedef struct
{
  INT8U Head;
  INT16U On_Delay;   //��ǰ��բ��ʱ
  INT16U Off_Delay; //��ǰ��բ��ʱ
  
  INT8U Switch_Status; //��ǰ����բ״̬
  INT8U Switch_Cause;   //��ǰ����բԭ��
  INT8U Tail;
}S_Relay_Status;

typedef struct
{
  INT8U Head;
  //INT8U Clr_Alarm_Flag:1;  //�ֶ����������־,0��ʾû���ֶ������1��ʾ�ֶ����
  INT8U Card_Switch_On_Flag :1; //�忨��բ��־������բ�����δ��͸֧��������²忨��բ��־
  INT8U Buy_Money_Switch_Limit_Flag :1; //��ֵ�Ƿ���ں�բ���ޱ�־��1��ʾ���ڣ����ܺ�բ��0��ʾ����
  INT8U Hand_Switch_On_Flag:4; //1��ʾ��Ҫ�ֶ���բ��0��ʾ�Ѿ��ֶ���բ, �ñ�־��ΪNEED_HAND_SWITCH_ON_FLAG��ʾ��Ҫ�ֶ���բ
                               //0��ʾ�Ѿ��ֶ���բ

    //�忨��բ��־��������ʣ������ڱ�������2������£����뿨��բ�����
  //�ֶ���բ��ʾ����ʾ�ں�բ���������£���Ҫ�ֶ���3s�������߲��빺�翨��綯������£������������բ״̬
  //���к�բ��������뽨�����ֶ���բ�����Ļ����ϡ��忨��բҲһ����
  
  INT8U CS[CS_BYTES];  
  INT8U Tail;
}S_Ctrl_Status_Flag;

typedef struct
{
  INT8U Head;
  INT8U Flag;
  INT8U Delay;
  INT8U Tail;
}S_Card_Test_Relay_Status;

EXT volatile S_Meter_Property_Word Meter_Property_Word; //�������������
EXT volatile S_Power_Ctrl_Para Power_Ctrl_Para; //���ɿ��Ʋ���
EXT volatile S_Relay_Delay_Para Relay_Delay_Para; //�̵�������բ��ʱ����
EXT volatile S_Prepaid_Power_Ctrl_Para Prepaid_Power_Ctrl_Para; //Ԥ���Ѹ��ɿ��Ʋ���
EXT volatile S_Power_Ctrl_Switch Power_Ctrl_Switch;//����բ��ʱ
EXT volatile S_Pepaid_Power_Ctrl_Switch Prepaid_Power_Ctrl_Switch; //Ԥ���Ѹ��ɿ�������բ
EXT volatile S_Remote_Ctrl_Switch Remote_Ctrl_Switch; //Զ������բ����
EXT volatile S_Prepaid_Ctrl_Switch Prepaid_Ctrl_Switch; //Ԥ���ѿ�������բ
EXT volatile S_Relay_Status Relay_Status; //�̵���״̬
EXT volatile S_Ctrl_Status_Flag Ctrl_Status_Flag;  //����״̬
EXT volatile S_Prepaid_Power_Ctrl_Pulse Prepaid_Power_Ctrl_Pulse;
EXT volatile S_Card_Test_Relay_Status Card_Test_Relay_Status;

#ifdef POWER_CTRL_C
volatile S_Relay_Status Relay_Status = {CHK_BYTE, 0, 0, SWITCH_ON, 0, CHK_BYTE};
volatile S_Prepaid_Power_Ctrl_Pulse Prepaid_Power_Ctrl_Pulse = {CHK_BYTE, {0}, 0, CHK_BYTE};
volatile S_Card_Test_Relay_Status Card_Test_Relay_Status = {CHK_BYTE, 0, 0, CHK_BYTE};
#endif

EXT void Init_Ctrl_Ram();
EXT INT8U Get_Alarm_Relay_Status();
EXT void Read_Ctrl_Para_From_Rom();
EXT void Read_Meter_Property_Word();
EXT void Check_Ctrl_Para_Avail();
EXT void Check_Ctrl_Data_Avail();
EXT INT8U Remote_Protocol_Ctrl(INT8U *pFlag);
EXT void Prepaid_Switch_Ctrl(INT16U Switch_Flag);
EXT void Prepaid_Power_Ctrl_Pulse_Hook();
EXT INT8U Prepaid_Power_Ctrl_Switch_On(INT8U Flag);
EXT void Prepaid_Power_Ctrl_Proc();
EXT void Clr_Prepaid_Power_Ctrl_Pulse_Data();
EXT void Power_Ctrl_Proc();
EXT INT16U Get_Prepaid_Relay_Status();
EXT INT8U Get_Switch_Status();
EXT INT8U Get_Relay_Status();
EXT INT8U Check_Switch_Status(INT8U *pCause);
EXT void Card_Test_Relay();
EXT void Switch_Ctrl_Proc();
EXT INT8U Set_Port_Output_Ctrl(INT8U Ctrl);
EXT void Prepaid_Ctrl_Proc(INT8U Type);
EXT void Check_Remote_Ctrl_Switch_Status();
EXT INT8U Prepaid_Insert_Card(INT8U Card_Type);
EXT INT8U Get_Card_Switch_On_Flag();
EXT INT8U Get_Hand_Switch_On_Flag();
EXT void Set_Hand_Switch_On_Flag(INT8U Flag);
#endif
