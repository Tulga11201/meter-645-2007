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

//#define RELAY_ON  0x1A //合闸
//#define RELAY_OFF 0x1B //跳闸
#define SWITCH_ON     0x1B
#define SWITCH_OFF    0x1A

#define ALARM_ON  0x2A
#define ALARM_OFF 0x2B

#define MAINTAIN_ON   0x3A   //保电标志
#define MAINTAIN_OFF 0x3B   //保电解除

#define ALLOW_SWITCH_ON 0x4B //拉闸状态下允许合闸

#define NEED_HAND_SWITCH_ON_FLAG 0x0C //不超过0x0F

#define S_OFF_PWR_CTRL   0x00  //负控拉闸
#define S_OFF_PREPAID    0x01  //预付费拉闸
#define S_OFF_REMOTE_CMD 0x02  //远程拉闸
#define S_OFF_PREPAID_PWR_CTRL 0x03 //预付费负控拉闸
#define S_ON_MAINTAIN    0x04  //保电合闸
#define S_ON_OTHER       0x05  //无拉闸合闸

#define REMOTE_SWITCH_RELAY_LIMIT_ACPOWER 70000 //7kw,单位0.0001kw

#define REMOTE_CTRL_OK   0
#define REMOTE_CTRL_REDO 1
#define REMOTE_CTRL_ERR  2

#define DIS_ACT_PULSE_INT STOP_CF1  //关有功脉冲中断
#define EN_ACT_PULSE_INT  START_CF1 //开有功脉冲中断

#define PREPAID_POWER_CTRL_UNIT_NUM 15

#define EXT_SWITCH_MODE (Meter_Property_Word.Word[0].Bit.Bit0) //外部开关控制方式，0为电平，1为脉冲 
#define INTER_SWITCH_MODE 1 //内部开关控制方式, 0为电平，1为脉冲
//定义电表运行特征字
typedef struct
{
  U_Byte_Bit Word[1];  
  INT8U CS[CS_BYTES];
}S_Meter_Property_Word;

//定义有功功率上限
typedef struct
{
  INT32U Pos_Act_Power_Limit;//正向有功需量上限
  INT32U Neg_Act_Power_Limit; //反向有功需量上限
  
  INT16U Relay_Off_Delay; //跳闸延时，单位s
  INT16U Relay_On_Delay; //合闸延时，单位s
  
  INT8U User_Level;//用户级别
  INT8U CS[CS_BYTES];
}S_Power_Ctrl_Para;

typedef struct
{
  INT16U Relay_Off_Delay;
  INT16U Relay_On_Delay;
  INT8U CS[CS_BYTES];
}S_Relay_Delay_Para;

//预付费负荷控制相关参数
typedef struct
{
   INT32U Max_Power_Pulse; //功率负荷脉冲数 
   INT8U Max_Power_Mins;   //最大负荷计算时间
   INT8U Max_Power_Switch_Off_Counts; //最大过负荷跳闸次数
   
   INT8U CS[CS_BYTES];
}S_Prepaid_Power_Ctrl_Para;

//记录每分钟脉冲个数
typedef struct
{
  INT8U Head;
  
  INT32U  Pulse_Num[PREPAID_POWER_CTRL_UNIT_NUM]; //脉冲数
  INT8U Posi; //当前记录位置
  
  INT8U Tail;
}S_Prepaid_Power_Ctrl_Pulse;

//负荷控制跳合闸延时
typedef struct
{
  INT8U Switch_Flag;
  INT8U On_Delay;
  INT8U Off_Delay;
   
  INT8U Switch_Status;
  
  INT8U CS[CS_BYTES];
}S_Power_Ctrl_Switch;

//远程控制拉合闸
typedef struct
{
  INT8U Switch_Flag; //跳闸标志--应该叫Switch_Flag比较合适
  //INT8U Switch_Time[6]; //跳闸命令截至时间
  
  INT8U Alarm_Flag; //报警的开关标志
  //INT8U Alarm_Time[6]; //跳闸命令截至时间

  INT8U Maintain_Flag; //保电标志
  //INT8U Maintain_Time[6]; //保电命令截至时间
  
  INT8U Switch_Status;
  
  INT8U CS[CS_BYTES];
}S_Remote_Ctrl_Switch;

//预付费控制拉合闸
typedef struct
{
  INT8U Switch_Flag;
  INT8U Alarm_Flag;
  
  INT8U CS[CS_BYTES];
}S_Prepaid_Ctrl_Switch;

//预付费负荷控制状态，需要存储
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
  INT16U On_Delay;   //当前合闸延时
  INT16U Off_Delay; //当前跳闸延时
  
  INT8U Switch_Status; //当前拉合闸状态
  INT8U Switch_Cause;   //当前拉合闸原因
  INT8U Tail;
}S_Relay_Status;

typedef struct
{
  INT8U Head;
  //INT8U Clr_Alarm_Flag:1;  //手动清除报警标志,0表示没有手动清除，1表示手动清除
  INT8U Card_Switch_On_Flag :1; //插卡合闸标志，在跳闸情况下未到透支门限情况下插卡合闸标志
  INT8U Buy_Money_Switch_Limit_Flag :1; //充值是否低于合闸门限标志，1表示低于，不能合闸，0表示高于
  INT8U Hand_Switch_On_Flag:4; //1表示需要手动合闸，0表示已经手动合闸, 该标志置为NEED_HAND_SWITCH_ON_FLAG表示需要手动合闸
                               //0表示已经手动合闸

    //插卡合闸标志，用来在剩余金额低于报警门限2的情况下，插入卡合闸的情况
  //手动合闸表示，表示在合闸允许的情况下，需要手动按3s按键或者插入购电卡买电动的情况下，才真正进入合闸状态
  //所有合闸情况都必须建立在手动合闸成立的基础上。插卡合闸也一样。
  
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

EXT volatile S_Meter_Property_Word Meter_Property_Word; //电表运行特征字
EXT volatile S_Power_Ctrl_Para Power_Ctrl_Para; //负荷控制参数
EXT volatile S_Relay_Delay_Para Relay_Delay_Para; //继电器跳合闸延时参数
EXT volatile S_Prepaid_Power_Ctrl_Para Prepaid_Power_Ctrl_Para; //预付费负荷控制参数
EXT volatile S_Power_Ctrl_Switch Power_Ctrl_Switch;//跳合闸延时
EXT volatile S_Pepaid_Power_Ctrl_Switch Prepaid_Power_Ctrl_Switch; //预付费负荷控制跳合闸
EXT volatile S_Remote_Ctrl_Switch Remote_Ctrl_Switch; //远程条合闸控制
EXT volatile S_Prepaid_Ctrl_Switch Prepaid_Ctrl_Switch; //预付费控制拉合闸
EXT volatile S_Relay_Status Relay_Status; //继电器状态
EXT volatile S_Ctrl_Status_Flag Ctrl_Status_Flag;  //控制状态
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
