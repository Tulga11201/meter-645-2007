#ifndef RTC_ABS_H
#define RTC_ABS_H



#ifndef RTC_ABS_PUCK
#define RTC_ABS_PUCK_EXT  extern volatile
#else
#define RTC_ABS_PUCK_EXT volatile
#endif


#define EXT_RTC_OK            0
#define EXT_RTC_FIRST_PWRON   1
#define EXT_RTC_COUNT_STOP    2
#define EXT_RTC_BUSY          4  //RTC æ
#define EXT_RTC_I2C_ERR       8  //RTC I2c��
#define EXT_RTC_BAT_LOW       16 //RTC ��ص�
#define EXT_RTC_PSEC_ERR      32 //RTC ʱ�ƴ���:12/24
#define EXT_RTC_PULSE_ERR     64 //RTC �������ô���


#define ID_EXT_RTC    0     //�ⲿӲ��ʱ��
#define ID_CPU_RTC    1     //CPU�ڲ�ʱ��
#define ID_RAM_RTC    2     //������SRAM��ʱ��
#define ID_SLEEP_RTC  3     //�͹����µ�sramʱ��


typedef struct
{
  INT8U Sec;
  INT8U Min;
  INT8U Hour;
  INT8U Week;//0��ʾ����,1-6�ֱ��ʾ��1->��6
  INT8U Date;
  INT8U Month;
  INT8U Year; 
  INT8U cS;  
}CPU_RTC;

//ʱ�䶨��ṹ��
typedef struct
{
  INT8U Head;
  CPU_RTC RTC;
  INT8U Tail;
}RTC_BCD_Time;
NO_INIT RTC_ABS_PUCK_EXT RTC_BCD_Time  CPU_RTC_Time;


INT8U Read_EXT_RTC_Buf(INT8U addr,INT8U Len,INT8U *Dst);
INT8U Write_EXT_RTC_Buf(INT8U addr,INT8U Len,INT8U *Src);
void Init_RTC_Pulse(INT8U Flag);
INT8U Read_Ext_RTC_Status(void);
INT8U Check_ExtRTC_Busy(void);

INT8U Write_ExtRTC_PUCK(INT8U *Src);
INT8U Read_ExtRTC_PUCK(INT8U *Dst,INT8U DstLen);
void Init_ExtRTC_PUCK(void);
INT8U Read_InterRTC_PUCK(INT8U *Dst,INT8U DstLen);
INT8U Write_InterRTC_PUCK(INT8U *Src);
void Init_ExtRTC_Pulse(INT8U Flag);
INT8U Read_Ext_RTC_Status(void);
void Refresh_CPU_RTC(void);
INT8U Get_Soft_RTC_PUCK(INT8U *Dst,INT8U DstLen);
void Set_Soft_RTC_PUCK(INT8U Flag);
void Beep_For_Para(void);
#endif
