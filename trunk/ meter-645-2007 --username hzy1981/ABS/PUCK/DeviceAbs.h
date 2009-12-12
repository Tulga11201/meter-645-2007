
#ifndef DEVICE_ABS_H
#define DEVICE_ABS_H



#ifndef DEVICE_ABS_PUCK
#define DEVICE_ABS_PUCK_EXT  extern volatile
#else
#define DEVICE_ABS_PUCK_EXT  volatile
#endif



#define INTER_EN		0
#define INTER_DIS		1

#define INTER_GRADE_HIGH        0
#define INTER_GRADE_LOW    	1
#define INTER_GRADE_LOWER       2
#define INTER_GRADE_LOWERST     3






#define INTER_WAKEUP_EN  	  ((PMK11==0)?1:0)  //��ѯ���⻽���Ƿ�����
#define CTRL_IRDA_SWITCH(a)     PMK11 = a
#define CTRL_IRDA_GRADE(a)	  {PPR111=(a&0x02)>>1;PPR011=a&0x01;PIF11 = 0;}
#define START_IRDA_WAKE         {CTRL_IRDA_GRADE(INTER_GRADE_LOW); CTRL_IRDA_SWITCH(INTER_EN);}
#define STOP_IRDA_WAKE          CTRL_IRDA_SWITCH(INTER_DIS)

#define START_LASER_UP          //Ŀǰ�޴˹��ܣ��ÿ�������
#define STOP_LASER_UP           //Ŀǰ�޴˹��ܣ��ÿ�������


#define CTRL_INTER_SWITCH_LEFTTKEY(a) 	{KRMK = a;}
#define CTRL_INTER_GRADE_LEFTKEY(a)	{KRPR1=(a&0x02)>>1;KRPR0=a&0x01;KRIF=0;}    
#define START_UP_KEY                  {CTRL_INTER_GRADE_LEFTKEY(INTER_GRADE_LOWERST); CTRL_INTER_SWITCH_LEFTTKEY(INTER_EN);}
#define STOP_UP_KEY                   {CTRL_INTER_SWITCH_LEFTTKEY(INTER_DIS);}

#define START_LEFT_KEY            START_UP_KEY
#define STOP_LEFT_KEY             STOP_UP_KEY

#define START_RIGHT_KEY           START_UP_KEY
#define STOP_RIGHT_KEY            STOP_UP_KEY

#define CTRL_INTER_SWITCH_UPTKEY(a) 	{PMK10 = a;}
#define CTRL_INTER_GRADE_UPKEY(a)	{PPR110=(a&0x02)>>1;PPR010=a&0x01;PIF10 = 0;}       
#define START_PRG_KEY                    {CTRL_INTER_GRADE_UPKEY(INTER_GRADE_LOWERST); CTRL_INTER_SWITCH_UPTKEY(INTER_EN);}
#define STOP_PRG_KEY                     {CTRL_INTER_SWITCH_UPTKEY(INTER_DIS);}



#define CTRL_INTER_SWITCH_CF1(a) 	{PMK6 = a;}
#define CTRL_INTER_GRADE_CF1(a)		{PPR16=(a&0x02)>>1;PPR06=a&0x01;PIF6 = 0;}
#define START_CF1                       {CTRL_INTER_GRADE_CF1(INTER_GRADE_LOWERST); CTRL_INTER_SWITCH_CF1(INTER_EN);}
#define STOP_CF1                        {CTRL_INTER_SWITCH_CF1(INTER_DIS);}


#define CTRL_INTER_SWITCH_CF2(a) 	{PMK0 = a;}
#define CTRL_INTER_GRADE_CF2(a)		{PPR10=(a&0x02)>>1;PPR00=a&0x01;PIF0 = 0;}
#define START_CF2                       {CTRL_INTER_GRADE_CF2(INTER_GRADE_LOWERST); CTRL_INTER_SWITCH_CF2(INTER_EN);}
#define STOP_CF2                        {CTRL_INTER_SWITCH_CF2(INTER_DIS);}



#define CTRL_INTER_SWITCH_1HZ(a) 	{PMK7 = a;}
#define CTRL_INTER_GRADE_1HZ(a)	        {PPR17=(a&0x02)>>1;PPR07=a&0x01;PIF7 = 0;}
#define START_1HZ                       {CTRL_INTER_GRADE_1HZ(INTER_GRADE_LOWERST); CTRL_INTER_SWITCH_1HZ(INTER_EN);}
#define STOP_1HZ                        {CTRL_INTER_SWITCH_1HZ(INTER_DIS);}


#define CTRL_INTER_SWITCH_PWRDOWN(a) 	{PMK4 = a;}
#define CTRL_INTER_GRADE_PWRDOWN(a)	{PPR14=(a&0x02)>>1;PPR04=a&0x01;PIF4 = 0;}
#define START_POWR_DOWN                 {CTRL_INTER_GRADE_PWRDOWN(INTER_GRADE_LOW); CTRL_INTER_SWITCH_PWRDOWN(INTER_EN);}
#define STOP_POWR_DOWN                  {CTRL_INTER_SWITCH_PWRDOWN(INTER_DIS);}


#define INTER_DECODE_EN  	        ((PMK5==0)?1:0)  //��ѯң���������ж��Ƿ�ʹ��
#define CTRL_INTER_SWITCH_DECODE(a) 	{PMK5 = a;}
#define CTRL_INTER_GRADE_PDECODE(a)	{PPR15=(a&0x02)>>1;PPR05=a&0x01;PIF5 = 0;}
#define START_IR_DECODE                 {CTRL_INTER_SWITCH_DECODE(INTER_GRADE_LOW); CTRL_INTER_SWITCH_DECODE(INTER_EN);}
#define STOP_IR_DECODE                  {CTRL_INTER_SWITCH_DECODE(INTER_DIS);}


#define DIS_PD_INT {STOP_POWR_DOWN;PD_INT_EN_Flag=0;}//�ص����ж�
#define EN_PD_INT {START_POWR_DOWN;PD_INT_EN_Flag=1;}//�������ж�




#define CTRL_INTER_SWITCH_DOWNKEY(a) 	{PMK8 = a;}
#define CTRL_INTER_GRADE_DOWNKEY(a)	{PPR18=(a&0x02)>>1;PPR08=a&0x01;PIF8 = 0;}
#define START_DOWN_KEY                  {CTRL_INTER_GRADE_DOWNKEY(INTER_GRADE_LOWERST); CTRL_INTER_SWITCH_DOWNKEY(INTER_EN);}
#define STOP_DOWN_KEY                   {CTRL_INTER_SWITCH_DOWNKEY(INTER_DIS);}


#define Soft_Reset()    WDTE = 0x00 	// restart watch dog timer



#define  NORMAL_STATUS_PUCK 0x23
#define  RESUME_STATUS_PUCK 0xe5
#define  SLEEP_STATUS_PUCK  0x32

typedef struct{
  INT8U Head;
  INT8U Status;
  INT8U Tail;
}RESUMECTRL;
DEVICE_ABS_PUCK_EXT RESUMECTRL Ext_Device_Stat;

#ifdef DEVICE_ABS_PUCK
DEVICE_ABS_PUCK_EXT RESUMECTRL Ext_Device_Stat={.Head =CHK_BYTE, NORMAL_STATUS_PUCK, .Tail = CHK_BYTE};
#endif

void Init_ExtRTC_Pulse(INT8U Flag);
void Init_ExtDevice_PUCK(INT32U Mode);
void Init_CPU_PUCK(INT32U Mode);

void PwrCtrl_ExtDevice_HigSpeed(void);
void Init_Inter_Abs(INT32U Mode);
void Init_Hard_PUCK(void);
void Print_Reset_Source(void);
void Goto_Sleep_PUCK(void);
void Init_All_IO_Sleep(void);
void Init_All_IO_Resume(INT8U Status);
void Cpu_Sleep_Proc(void);
#endif