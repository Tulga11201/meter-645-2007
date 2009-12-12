#ifndef Pulse_h
#define Pulse_h


//#undef MeasuProc_PUCK_EXT
#ifndef MeasuPulse_PUCK
#define MeasuPulse_PUCK_EXT  extern volatile
#else
#define MeasuPulse_PUCK_EXT volatile
#endif



#define DI_AC_PULSE     PDI_ACTIVE_CONST    //�й����峣��
#define DI_REAC_PULSE   PDI_REACTIVE_CONST    //�޹����峣��
#define DI_PULSE_WIDTH   PDI_ADJ_PULSE_WIDTH    //��������ȣ�����


typedef struct
{ 
  INT32U Ac_Pulse;               //�й�����
  INT32U Rea_Pulse;               //�޹�����
  INT8U Ac_Pulse_Freq;           //�й������Ƶϵ��
  INT8U Reac_Pulse_Freq;         //�޹������Ƶϵ��
  INT16U Pulse_Width;             //��������ȣ�����,���޹�һ�¡�
  INT8U CS[CS_BYTES];            //��Ҫ������SRAM��У���
}PULSE_STRUC;                    //MeasuICϵͳģʽ��


MeasuPulse_PUCK_EXT PULSE_STRUC Sys_Pulse_Var;

INT8U Get_Pulse_Para(void);
void Send_Acpower_Pulse(void);
void Send_Reacpower_Pulse(void);
INT8U Judge_Pulse_Legal(INT32U CurPulse);
INT8U Check_Pulse(void);
#endif

