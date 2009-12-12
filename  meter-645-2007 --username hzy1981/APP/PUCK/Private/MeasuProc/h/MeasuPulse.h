#ifndef Pulse_h
#define Pulse_h


//#undef MeasuProc_PUCK_EXT
#ifndef MeasuPulse_PUCK
#define MeasuPulse_PUCK_EXT  extern volatile
#else
#define MeasuPulse_PUCK_EXT volatile
#endif



#define DI_AC_PULSE     PDI_ACTIVE_CONST    //有功脉冲常数
#define DI_REAC_PULSE   PDI_REACTIVE_CONST    //无功脉冲常数
#define DI_PULSE_WIDTH   PDI_ADJ_PULSE_WIDTH    //输出脉冲宽度：毫秒


typedef struct
{ 
  INT32U Ac_Pulse;               //有功脉冲
  INT32U Rea_Pulse;               //无功脉冲
  INT8U Ac_Pulse_Freq;           //有功脉冲分频系数
  INT8U Reac_Pulse_Freq;         //无功脉冲分频系数
  INT16U Pulse_Width;             //输出脉冲宽度：毫秒,有无功一致。
  INT8U CS[CS_BYTES];            //重要参数，SRAM加校验和
}PULSE_STRUC;                    //MeasuIC系统模式字


MeasuPulse_PUCK_EXT PULSE_STRUC Sys_Pulse_Var;

INT8U Get_Pulse_Para(void);
void Send_Acpower_Pulse(void);
void Send_Reacpower_Pulse(void);
INT8U Judge_Pulse_Legal(INT32U CurPulse);
INT8U Check_Pulse(void);
#endif

