
#ifndef PORT_ABS_H
#define PORT_ABS_H



#ifndef PORT_ABS_PUCK
#define PORT_ABS_PUCK_EXT  extern volatile
#else
#define PORT_ABS_PUCK_EXT volatile 
#endif



//输出模式
#define LEVEL_MODE        0x00   //电平输出模式
#define PULSE_MODE        0x01   //脉冲输出模式
#define MULTI_MODE        0x02   //可变输出

#define PORT_END   0
#define PORT_START 1


/****************************************以下是对辅助端子的配置*****************************************************/
#define AUX_PORT_PULSE_WD      80    //报警输出脉冲宽度：ms
#define TOOGLE_PORT_PULSE_WD   80   //跳闸输出脉冲宽度：ms

#define APP_TOOGLE_PORT_PULSE_WD      400 //跳闸脉冲宽度：ms
#define LARGE_RELAY_PULSE_WD           250 //大继电器跳闸脉冲宽度：ms
/***************************************************辅助端子配置完毕*****************************************************/




#define  DEMAND_OUT_MODE Mode_Word.Mode[2].Bit.Bit4 //模式字3 bit4:需量信号输出方式,1:按需量周期,0:按滑差时间


//喂狗信号
#ifdef RST_IC_7X6_EN
  #define Clear_Ext_Dog()       B_WTD_0
#else
  #define Clear_Ext_Dog()       {B_WTD_1;  B_WTD_0; B_WTD_0; B_WTD_1;}    //一个B_WTD_0大约 100ns
#endif

#define BEEP_MODE_50        50
#define BEEP_MODE_100       100
#define BEEP_MODE_150       150
#define BEEP_MODE_200       200
#define BEEP_MODE_300       300
#define BEEP_MODE_400       400
#define BEEP_MODE_500       500

//所有PORT设备ID
#define EXT_ID_NONE         0  //无效端子
//#define EXT_ID_AP_DIR             (EXT_ID_NONE+1)         //有功脉冲方向-------------------------------1
//#define EXT_ID_RP_DIR             (EXT_ID_AP_DIR+1)        //无功脉冲方向----------------------------2
#define EXT_ID_SEC_EN             (EXT_ID_NONE+1)        //秒脉冲使能------------------------------3
#define INTER_ID_TOGGLE_DIS        (EXT_ID_SEC_EN+1)       //跳闸指示灯---------------------------------4
#define INTER_ID_ALARM_DIS        (INTER_ID_TOGGLE_DIS+1)  //报警指示灯---------------------------------5

#define EXT_ID_AUX_ALARM          (INTER_ID_ALARM_DIS+1)  //辅助端子报警输出-----------------------------6
#define EXT_ID_TOGGLE             (EXT_ID_AUX_ALARM+1)     //跳闸输出-----------------------------------7

//#define EXT_ID_ACPOWER            (EXT_ID_TOGGLE+1)       //有功脉冲-----------------------------------8
//#define EXT_ID_REACPOWER          (EXT_ID_ACPOWER+1)      //无功脉冲-----------------------------------9
#define EXT_ID_DEMAND             (EXT_ID_TOGGLE+1)    //需量周期到输出--------------------------10
#define EXT_ID_SLIPE              (EXT_ID_DEMAND+1)       //滑差周期输出-------------------------------11
#define EXT_ID_PARSE              (EXT_ID_SLIPE+1)        //时段切换输出--------------------------------12
//#define GERNAL_ID_ACPOWER         (EXT_ID_PARSE+1)        //总有功脉冲---------------------------------13
//#define GERNAL_ID_REACPOWER       (GERNAL_ID_ACPOWER+1)   //总无功脉冲---------------------------------14
#define INTER_ID_ALARM_BEEP       (EXT_ID_PARSE+1) //报警喇叭------------------------------------15
#define INTER_ID_RELAY_ON        (INTER_ID_ALARM_BEEP+1)  //脉冲触发式继电器开启------------------------16
#define INTER_ID_RELAY_OFF       (INTER_ID_RELAY_ON+1)     //脉冲触发式继电器关闭-----------------------17
  

//最大的PORT设备ID数目
#define MIN_PORT_DI      (EXT_ID_NONE+1)
#define MAX_PORT_DI      (INTER_ID_RELAY_OFF)
#define MAX_PORT_NUM     (MAX_PORT_DI+1)


//最大的LEVEL_PORT设备ID数目
#define MIN_LEVEL_PORT_DI       (EXT_ID_NONE+1)
#define MAX_LEVEL_PORT_DI       EXT_ID_TOGGLE


//最大的PULSE_PORT设备ID数目
#define MIN_PULSE_PORT_DI      EXT_ID_AUX_ALARM
#define MAX_PULSE_PORT_DI      INTER_ID_RELAY_OFF

typedef struct
{ 
  INT8U InitFlag;           //端子初始化完成
  INT8U Status;             //状态：0表示无动作；1表示启动，2表示进行；3表示结束；
  INT16U CurCount;          //当前1ms计数，0表示执行动作结束，最大65536ms，某一轮回中的脉冲宽度
  INT16U CurCountBak;       //某一轮回中的脉冲宽度备份
  //INT16U LoopCount;         //轮回数，每一个轮回出一个脉冲
  INT8U CS[CS_BYTES];
}PORT_HANDER;
PORT_ABS_PUCK_EXT PORT_HANDER Ext_Port_Hander[MAX_PORT_NUM];


typedef struct{
  INT8U Head;
  INT8U Mode;            //三合一端子排模式字：上电后回复秒脉冲输出
  INT8U ReadMode;        //三合一端子排模式字
  INT8U Tail;
}MULIT_PORT_MODE;

PORT_ABS_PUCK_EXT MULIT_PORT_MODE  Multi_Port_Mode;//={CHK_BYTE, 0, 0, CHK_BYTE};

 //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。
#define SEC_OUT_PUT_EN        (Multi_Port_Mode.Mode==0)
#define DEMAND_OUT_PUT_EN     (Multi_Port_Mode.Mode==1)
#define SLIPE_OUT_PUT_EN      (Multi_Port_Mode.Mode==1)
#define PARSE_OUT_PUT_EN      (Multi_Port_Mode.Mode==2)



#define PORT_OUTPUT_MODE      Multi_Port_Mode.ReadMode

#define MODE_ERR     0     //未知模式
#define MODE_RUN     1     //现场运行模式，不输出调试信息，无权限
#define MODE_DEBUG   2     //调试模式，可输出调试信息，无权限
#define MODE_FAC     4     //工厂模式，可输出调试信息，具备最高权限
#define MODE_TEST    8     //自检模式，可输出调试信息，无权限


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