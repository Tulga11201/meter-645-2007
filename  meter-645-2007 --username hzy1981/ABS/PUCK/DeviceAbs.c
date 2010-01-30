#define DEVICE_ABS_PUCK
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P1"
#endif
/********************************************************************************
�������ܣ�����ģʽ�£�CPU��Χʱ�ӳ�ʼ��
��ڣ�
���أ�
    ��
********************************************************************************/
void Init_CPUDevice_Clock(INT32U Mode)
{
   switch(Mode)
   {
     case SYS_NORMAL:
       break;       
     case SYS_RESUME:
       TAU0EN=1;
       SAU0EN=1;
       SAU1EN=0;
       IIC0EN=1;
       ADCEN=0;
       DACEN=0;
       RTCEN=1;
       
       EXBEN=0;  //PER1
       break;
     case SYS_SLEEP:
       TAU0EN=1;
       SAU0EN=0;
       SAU1EN=0;
       IIC0EN=0;
       ADCEN=0;
       DACEN=0;
       RTCEN=1;
       
       EXBEN=0;  //PER1
       break;
   }   
}    
/********************************************************************************
�������ܣ���λ���ӡ��λԴ
��ڣ�
���أ�
    ��
********************************************************************************/
void Print_Reset_Source(void)
{ 
    INT8U resetflag = RESF;
    
    if(!resetflag)
      Debug_Print("Reset Source:External Reset Signal Or POC!");
    
    if(resetflag&0x01)
      Debug_Print("Reset Source:Low Voltage Reset Detect!");
    
    if(resetflag&0x10)
      Debug_Print("Reset Source:CPU Internal WatchDog!");
    
    if(resetflag&0x80)
      Debug_Print("Reset Source:Illegal Instrucion!");
    
}

/********************************************************************************
�������ܣ�resumeʱ����CPU IO�ڵĶ���
��ڣ�
���أ�
1��resum�²��õ�IO�ڣ�IO��λ��Ĭ��Ϊ����
********************************************************************************/
void Init_All_IO_Resume(INT8U Status)
{
    P0=0;
    PU0=0;
    
    
    PM0_bit.no0=0;     //KEY6---------------------���˸�(��˸�)Ǧ��
    PM0_bit.no1=0;     //KEY5---------------------�����(�϶˸�)
    PM0_bit.no2=0;     //------------------------TXD-GPRS
    PM0_bit.no3=0;     //-----------------------:RXD_GPRS(VCC����,CPU��)
    PM0_bit.no4=0;     //-----------------------:�¼�ָʾ�ţ�EVENT_GPRS(VCC����)
    PM0_bit.no5=0;     //�ڿ���Դ����--------------MEN_PWR
    PM0_bit.no6=0;     //-----------------------16-SDA:24C16������
    
    
    PM0|=PM0_DEFAULT;
    
    P1=0;
    PU1=0;
    PM1_bit.no0=0;   //Զ���ⷢ��ʹ��-------IR_FAR_EN
    PM1_bit.no1=0;   //����1----------------RXD1
    PM1_bit.no2=0;   //����1----------------TXD1
    PM1_bit.no3=0;   //����2----------------TXD2
    PM1_bit.no4=0;   //����2----------------RXD2
    PM1_bit.no5=0;   //485���ƿ�------------RE/DE2,������ ESAM����Դ��Դ����
    PM1_bit.no6=0;   //ң��������-----------RXD1
    PM1_bit.no7=1;   //PWM------------------PWM
    
    P2=0;
    PM2_bit.no0=0;    //����RST---------7022_RST
    PM2_bit.no1=0;    //����SIG---------7022_SIG
    PM2_bit.no2=0;    //����SDO---------7022_SDO
    PM2_bit.no3=0;    //����SDI ---------7022_SDI    
    PM2_bit.no4=0;    //����SCK---------7022_SCK
    PM2_bit.no5=0;    //����POWER-------PULSE_PWR
    PM2_bit.no6=1;    //RTC(VBB����)--------------RTC1_SDA������Ϊ���룬��I2CSoft�л����³�ʼ��
    PM2_bit.no7=1;    //RTC(VBB����)--------------RTC1_SCL������Ϊ���룬��I2CSoft�л����³�ʼ��

    
    P3=0;
    PU3=0; 
    PM3_bit.no0=1; //���⻽��,�ⲿ�жϼ���-------Laser_WKP------�°���(2009-02-18):IC_FAIL
    PM3_bit.no1=1; //������-----------------------V_D1
    PM3|=PM3_DEFAULT;
    
    P4=0;
    PU4=0;
    PM4_bit.no0=1; //������Կ�(VBB����)----------TOOL0
    PM4_bit.no1=0; //������Կ�-------------------TOOL1
    PM4_bit.no2=0; //DataFlashƬѡ----------------45DB161_/CS
    PM4_bit.no3=0; //DataFlashʱ��----------------45DB161_SCK
    PM4_bit.no4=0; //DataFlash���----------------45DB161_SO
    PM4_bit.no5=0; //DataFlash����----------------45DB161_SI
    PM4_bit.no6=0; //ȫʧѹ----------ALL_V_LOSS
    PM4_bit.no7=0; //DataFlash--------------------45DB161_RDY  
        
    P5=0;
    PU5=0;
    
    PM5_bit.no0=0;   //7022_PWR
    PM5_bit.no1=0;   //IC_OUT
    PM5_bit.no2=0;   //IC_RST
    PM5_bit.no3=0;   //IC_SW--------------
    PM5_bit.no4=1;   //ι���ź�----------------------------------��Ϊ���룬ι����Ч
    PM5_bit.no5=0;   //�ɻɹܼ��,���ղ���------------K1
    PM5_bit.no6=1;   //Ӳ���Լ��(VBB����)-----------------
    PM5_bit.no7=1;   //����ģʽ(VBB����)--------
    
    P6=0;
    PU6=0;
    PM6_bit.no0=1;   //�ڿ�Ӳ��I2C SCLK-------MEM_SCL������Ϊ���룬��I2C�л����³�ʼ��
    PM6_bit.no1=1;   //�ڿ�Ӳ��I2C SDA--------MEM_SDA������Ϊ���룬��I2C�л����³�ʼ��
    PM6_bit.no2=1;   //�ڿ�Ӳ��I2Cд����------MEM_WP������Ϊ���룬��I2C�л����³�ʼ��
    
#ifdef MEASU_BAKPWR_NEW_EN
    PM6_bit.no3=0;   //
#else
    PM6_bit.no3=1;   //
#endif
    
    PM6_bit.no4=0;   //�޹�����---------------A_DIR
    PM6_bit.no5=0;   //�޹�����---------------R_DIR
    PM6_bit.no6=0;   //�й����---------------A_EOUT
    PM6_bit.no7=0;   //�޹����---------------R_EOUT
    
    P7=0;
    PU7=0;    
    PM7_bit.no0=0;   //-------------------16-SCL:24C16ʱ����
    PM7_bit.no1=1;   //(VBB����)-------------------������
    PM7_bit.no2=1;   //(VBB����)-------------------ѡ��(���)
    PM7_bit.no3=1;   //UPKEY(VBB����)---------�Ϸ�
    PM7_bit.no4=1;   //UPKEY(VBB����)---------�·�
    PM7_bit.no5=0;   //--------------------24C16д�����ź���
    PM7_bit.no6=0;   //UPKEY(VCC����)---------���
    PM7_bit.no7=1;   //���⻽��(VBB����)------LASER_WAKEUP
    
   
    P8=0;
    PU8=0;
    PM8_bit.no0=0;   //��բ���-------------------SWITCH_TOGGLE
    PM8_bit.no1=0;   //����������-----------------ALARM
    PM8_bit.no2=1;   //������ʹ��(���߼������ӣ�����3231������Ϊ�߼���)-----SECOND_/EN
    PM8_bit.no3=0;   //��������-------------------DEMAND
    PM8_bit.no4=0;   //ʱ�����-------------------TIME_SW
    PM8_bit.no5=0;   //�͹��ĵ�ؼ��-------------VB3_OK1
    PM8_bit.no6=0;   //Զ�����Դ����-------------IR_FAR_PWR
    PM8_bit.no7=0;   //������չ(EX7)--------------NC------�°���(2009-02-18):IC_SW
    
    P11=0;
    PM11_bit.no0=0;   //Զ����/���������л�----------IR_FAR_/SELECT
    PM11_bit.no1=0;   //ʱ�ӵ�ؼ��-----------VB1_OK
    PM11|=PM11_DEFAULT;
    
    P12=0;
    PU12=0;
    PM12_bit.no0=0;   //CF2����-----------7022_CF2
    PM12_bit.no1=1;   //X1-----------------
    PM12_bit.no2=1;   //X2-----------------
    PM12_bit.no3=1;   //XT1----------------
    PM12_bit.no4=1;   //XT2----------------
    PM12|=PM12_DEFAULT;
    
    P13=0;
    PU13=0;    
    PM13_bit.no0=0;   //7022_CS
    PM13_bit.no1=0;   //Ԥ��-------------7022_341_331
    PM13|=PM13_DEFAULT;
    
    P14=0;
    PU14=0;
    PM14_bit.no0=0;   //CF1����---------7022_CF1
    PM14_bit.no1=0;   //ʱ��������(VCC����,��3231����ECOND_PULSE
    PM14_bit.no2=0;   //������----------ALARM_SND
    PM14_bit.no3=0;   //����0----------RXD0
    PM14_bit.no4=0;   //����0----------TXD0
    PM14_bit.no5=0;   //485���ƿ�--------RE/DE0
    PM14|=PM14_DEFAULT;

    if(Status EQ RESUME_STATUS_PUCK)  //�Ѿ����Ѳ��ҳ�ʼ�����ˡ�
      P15=0x10;            //LCD POWER-----------------LCD_POWER
    else
      P15=0;
    
    PM15_bit.no0=0;   //�й�����ָʾ��-------------A-EOU1    
    PM15_bit.no1=0;   //�޹�����ָʾ��-------------R-EOU1
    PM15_bit.no2=1;   //LCD�����Ϊ���룬������Ч------Back_Light_On   
    PM15_bit.no3=0;   //LCD CS--------------------1623-/CS
    PM15_bit.no4=0;   //LCD POWER-----------------LCD_POWER
    PM15_bit.no5=0;   //LCD DATA------------------1623-DATA
    PM15_bit.no6=0;   //LCD WRITE-----------------1623-/WR
    PM15_bit.no7=0;   //Ԥ��----------------------NC
 }
/********************************************************************************
�������ܣ�����˯��ǰ����CPU IO�����Ϊ0
��ڣ�
���أ�
1��ԭ������Ż�������ţ����䣻
2��δ�õ�����ţ����õ�����ţ�ǿ�����Ϊ0��
3��˫��IO��
4��ע��ļ����ţ�IC_PWR��SECOND_PULSE��PWM��K1(�ɻʹ�)
********************************************************************************/
void Init_All_IO_Sleep(void)
{    

    P0=0;
    PU0=0;
    
    

    PM0_bit.no0=0;     //---------------------���˸�(��˸�)Ǧ��
    PM0_bit.no1=0;     //---------------------�����(�϶˸�)
    PM0_bit.no2=0;     //------------------------TXD-GPRS
    PM0_bit.no3=0;     //-----------------------:RXD_GPRS(VCC����,CPU��)
    PM0_bit.no4=0;     //-----------------------:�¼�ָʾ�ţ�EVENT_GPRS(VCC����)
    PM0_bit.no5=0;     //�ڿ���Դ����--------------MEN_PWR
    PM0_bit.no6=0;     //-----------------------16-SDA:24C16������
    
    PM0|=PM0_DEFAULT;
    
    P1=0;
    PU1=0;
    PM1_bit.no0=0;   //Զ���ⷢ��ʹ��-------IR_FAR_EN
    PM1_bit.no1=0;   //����1----------------RXD1
    PM1_bit.no2=0;   //����1----------------TXD1
    PM1_bit.no3=0;   //����2----------------TXD2
    PM1_bit.no4=0;   //����2----------------RXD2
    PM1_bit.no5=0;   //485���ƿ�------------RE/DE2,������ ESAM����Դ��Դ����
    PM1_bit.no6=0;   //ң��������-----------RXD1
    PM1_bit.no7=1;   //PWM------------------PWM
    
    P2=0;
    PM2_bit.no0=0;    //����RST---------7022_RST
    PM2_bit.no1=0;    //����SIG---------7022_SIG
    PM2_bit.no2=0;    //����SDO---------7022_SDO
    PM2_bit.no3=0;    //����SDI ---------7022_SDI    
    PM2_bit.no4=0;    //����SCK---------7022_SCK
    PM2_bit.no5=0;    //����POWER-------PULSE_PWR
    PM2_bit.no6=1;    //RTC(VBB����)--------------RTC1_SDA
    PM2_bit.no7=1;    //RTC(VBB����)--------------RTC1_SCL

    
    
    P3=0;
    PU3=0; 
    PM3_bit.no0=1; //���⻽��,�ⲿ�жϼ���-------Laser_WKP------�°���(2009-02-18):IC_FAIL
    PM3_bit.no1=1; //������-----------------------V_D1
    PM3|=PM3_DEFAULT;
    
    P4=0;
    PU4=0;
    PM4_bit.no0=1; //������Կ�(VBB����)----------TOOL0
    PM4_bit.no1=0; //������Կ�-------------------TOOL1
    PM4_bit.no2=0; //DataFlashƬѡ----------------45DB161_/CS
    PM4_bit.no3=0; //DataFlashʱ��----------------45DB161_SCK
    PM4_bit.no4=0; //DataFlash���----------------45DB161_SO
    PM4_bit.no5=0; //DataFlash����----------------45DB161_SI
    PM4_bit.no6=1; //------�°���(2009-02-18):ȫʧѹ----------ALL_V_LOSS
    PM4_bit.no7=0; //DataFlash--------------------45DB161_RDY  
        
    P5=0;
    PU5=0;
    PM5_bit.no0=0;   //7022_PWR
    PM5_bit.no1=0;   //IC_OUT
    PM5_bit.no2=0;   //IC_RST
    PM5_bit.no3=0;   //IC_SW--------------
    PM5_bit.no4=0;   //ι���ź�----------------------------------
    PM5_bit.no5=0;   //�ɻɹܼ��,���ղ���------------K1
    PM5_bit.no6=1;   //Ӳ���Լ��(VBB����)-----------------
    PM5_bit.no7=1;   //����ģʽ(VBB����)----------
    
    P6=0;
    PU6=0;
    PM6_bit.no0=0;   //�ڿ�Ӳ��I2C SCLK-------MEM_SCL
    PM6_bit.no1=0;   //�ڿ�Ӳ��I2C SDA--------MEM_SDA
    PM6_bit.no2=0;   //�ڿ�Ӳ��I2Cд����------MEM_WP
    
#ifdef MEASU_BAKPWR_NEW_EN
    PM6_bit.no3=0;   //
#else
    PM6_bit.no3=1;   //
#endif
    
    PM6_bit.no4=0;   //�޹�����---------------A_DIR
    PM6_bit.no5=0;   //�޹�����---------------R_DIR
    PM6_bit.no6=0;   //�й����---------------A_EOUT
    PM6_bit.no7=0;   //�޹����---------------R_EOUT
    
    P7=0;
    PU7=0;
    PM7_bit.no0=0;   //-------------------16-SCL:24C16ʱ����
    PM7_bit.no1=1;   //(VBB����)-------------------������
    PM7_bit.no2=1;   //(VBB����)-------------------ѡ��(���)
    PM7_bit.no3=1;   //�Ϸ�(VBB����)---------KEY4
    PM7_bit.no4=1;   //�·�(VBB����)---------KEY2
    PM7_bit.no5=0;   //--------------------24C16д�����ź���  
    PM7_bit.no6=0;   //UPKEY(VCC����)---------���
    PM7_bit.no7=1;   //���⻽��(VBB����)------LASER_WAKEUP
    
    
    P8=0;
    PU8=0;
    PM8_bit.no0=0;   //��բ���-------------------SWITCH_TOGGLE
    PM8_bit.no1=0;   //����������-----------------ALARM
    PM8_bit.no2=0;   //������ʹ��(���߼������ӣ�����3231������Ϊ�߼���)-----SECOND_/EN
    PM8_bit.no3=0;   //��������-------------------DEMAND
    PM8_bit.no4=0;   //ʱ�����-------------------TIME_SW
    PM8_bit.no5=0;   //�͹��ĵ�ؼ��-------------VB3_OK1
    PM8_bit.no6=0;   //Զ�����Դ����-------------IR_FAR_PWR
    PM8_bit.no7=0;   //������չ(EX7)--------------NC------�°���(2009-02-18):IC_SW
    
    P11=0;
    PM11_bit.no0=0;   //Զ����/���������л�----------IR_FAR_/SELECT
    PM11_bit.no1=0;   //ʱ�ӵ�ؼ��-----------VB1_OK
    PM11|=PM11_DEFAULT;
    
    P12=0;
    PU12=0;
    PM12_bit.no0=0;   //CF2����-----------7022_CF2
    PM12_bit.no1=1;   //X1-----------------
    PM12_bit.no2=1;   //X2-----------------
    PM12_bit.no3=1;   //XT1----------------
    PM12_bit.no4=1;   //XT2----------------
    PM12|=PM12_DEFAULT;
    
    P13=0;
    PU13=0;    
    PM13_bit.no0=0;   //7022_CS
    PM13_bit.no1=0;   //Ԥ��-------------7022_341_331
    PM13|=PM13_DEFAULT;
    
    P14=0;
    PU14=0;
    PM14_bit.no0=0;   //CF1�����----------7022_CF1
    PM14_bit.no1=0;   //ʱ��������(VCC����,��3231����ECOND_PULSE
    PM14_bit.no2=0;   //������----------ALARM_SND
    PM14_bit.no3=0;   //����0----------RXD0
    PM14_bit.no4=0;   //����0----------TXD0
    PM14_bit.no5=0;   //485���ƿ�--------RE/DE0
    PM14|=PM14_DEFAULT;
    
    P15=0;
    PM15_bit.no0=0;   //�й�����ָʾ��-------------A-EOU1    
    PM15_bit.no1=0;   //�޹�����ָʾ��-------------R-EOU1
    PM15_bit.no2=0;   //LCD����--------------------Back_Light_On   
    PM15_bit.no3=0;   //LCD CS--------------------1623-/CS
    PM15_bit.no4=0;   //LCD POWER-----------------LCD��Դ
    PM15_bit.no5=0;   //LCD DATA------------------1623-DATA
    PM15_bit.no6=0;   //LCD WRITE-----------------1623-/WR
    PM15_bit.no7=0;   //Ԥ��----------------------NC------�°���(2009-02-18):LED����ָʾ
}
/********************************************************************************
�������ܣ���λ���CPU�ĳ�ʼ��
��ڣ�
���أ�
    ��
********************************************************************************/
void Init_Hard_PUCK(void)
{
  hdwinit(SYS_NORMAL);
  Clr_Ext_Inter_Dog();
  START_1MS;    //�򿪺����жϣ�ΪOS�ṩtick
  START_RTC_COUNTER; 
  
  START_POWR_DOWN;   //�������жϴ򿪣�ӦHUCK���󣬷�ֹ���� PD_DATA_PROC �Ժ������
  STOP_CF1;
  STOP_CF2;  
  
  STOP_UP_KEY;
  STOP_DOWN_KEY;
  STOP_LEFT_KEY;
  STOP_RIGHT_KEY;  
  STOP_PRG_KEY; 
  STOP_LASER_UP;
  STOP_IR_DECODE;
  
  STOP_RTC_ALARM;   
  STOP_IRDA_WAKE;
  STOP_1HZ;        
  STOP_ALL_LOSS;         //�ر�ȫʧѹ
}
/********************************************************************************
�������ܣ�˯��ǰ�л�ֻsubʱ�ӣ��ر���ʱ����,����haltģʽ
��ڣ�
���أ�
    ��
********************************************************************************/
void Goto_Sleep_PUCK(void)
{
   if(Switch_Main_Osc(HALT_MODE)) 
   {
     Clear_CPU_Dog();  //˯ǰι��
     while(1)   //��RTC�����ȫʧѹ�Ĵ���------PUCK
     {
       //CG_SelectPowerSaveMode(PSHALT);
       //STOP();
       HALT();
       //..........................................
       Clear_CPU_Dog();
       if((Resume_Src.Src_Flag&(IRAD_RESUME|KEY_RESUME)))  //����ȫʧѹ����RTC���壬�˳�˯��
         break;       
     } 
   }
   //�����ˣ����ݻ���Դ�����л����پ���-----------PUCK 
   Switch_Main_Osc(RUN_MODE);
   Clear_CPU_Dog(); 
}  
/********************************************************************************
�������ܣ���˯�����˴�������
��ڣ�
���أ�
    ��
********************************************************************************/
#define WAKE_UP_TIMES 60  //�����ȫʧѹ�����ܴ���
void Cpu_Sleep_Proc(void)
{
  static S_Int8U Counts={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Last_Date={CHK_BYTE,0xFF,CHK_BYTE};
  
  while(1)
  {
    Goto_Sleep_PUCK();
    if((Resume_Src.Src_Flag&(IRAD_RESUME|KEY_RESUME)))
    {
      Counts.Var=0;   //��ť/���⻽��,������,���Ѵ�����0
      Last_Date.Var=Cur_Time1.Date;
      break;
    }
      
    if(DAY!=Last_Date.Var)
    {
      Counts.Var=0;   //���죬���Ѵ�����0
      Last_Date.Var=Cur_Time1.Date;
    }
    else
      Counts.Var++;
    
    Clear_CPU_Dog(); 
    
    if(Counts.Var<WAKE_UP_TIMES)
      break;
    
    //���컽�Ѵ���������������ΰ�ť�ͺ��⻽��Դ
    if(Counts.Var==254)  //���ⷭת
      Counts.Var=WAKE_UP_TIMES;
    Resume_Src.Src_Flag&=(INT8U)(~(IRAD_RESUME|KEY_RESUME));  //�����ť�ͺ��⻽��Դ
  }
}
/********************************************************************************
�������ܣ����ݲ�ͬ�Ĺ���ģʽ��������Ӧ���жϼ��жϵȼ�
��ڣ�
���أ�
    ��
********************************************************************************/
void Init_Inter_Abs(INT32U Mode)
{  
  switch(Mode)//������Ҫ���ֻ���Դ---------PUCK
  {
    case SYS_NORMAL:   // SYS_NORMALģʽ�£������ж�����Դ      
        START_1MS;    //�򿪺����жϣ�ΪOS�ṩtick
        STOP_CF1;
        STOP_CF2;
        START_POWR_DOWN;
        START_UP_KEY;
        START_DOWN_KEY;
        START_LEFT_KEY;
        START_RIGHT_KEY;
        START_PRG_KEY;
        START_RTC_COUNTER; 
        START_LASER_UP;
        START_IR_DECODE;
        
        STOP_RTC_ALARM;   
        STOP_IRDA_WAKE;
        STOP_1HZ;        
        STOP_ALL_LOSS;         //�ر�ȫʧѹ
    break;
    
    case SYS_RESUME:  //SYS_RESUMEģʽ�£����ݻ���Դ�����ж�
        STOP_CF1;
        STOP_CF2;
        STOP_1HZ;
        STOP_POWR_DOWN;
        STOP_LEFT_KEY;
        STOP_RIGHT_KEY;
        STOP_LASER_UP;
        STOP_PRG_KEY;
        
        if(Resume_Src.Src_Flag&IRAD_RESUME)  //����sleepģʽ�µĺ��⻽�ѣ�ֹͣ����
        {
          STOP_IRDA_WAKE;        //�� START_IR_DECODE ����
          if(RESUME_REMOTER_EN)   //ң������              
            START_IR_DECODE;       //�����£�����ʹ�ú���ң����

        }
        else
        { 
          START_IRDA_WAKE; 
          STOP_IR_DECODE;       //�� START_IR_DECODE ����
        }
        
        START_1MS;          //����1ms�ж�-----PUCK
        START_UP_KEY;
        START_DOWN_KEY;
        
        
        START_RTC_COUNTER; 
        START_MIN_ALARM;
        
#if    ALL_LOSS_TYPE!=ALL_LOSS_SOFT
        if((All_Loss_Var.Status.Nums==0)||(All_Loss_Var.Status.Mins==0))   //û���¼�����
        START_ALL_LOSS;       //��ȫʧѹ
#else   //���ʵ��ȫʧѹ
        STOP_ALL_LOSS;       
#endif
       
    break;
    
    case SYS_SLEEP:  //SYS_SLEEPģʽ�£������ж�����Դ
        STOP_CF1;
        STOP_CF2;
        STOP_1HZ;
        STOP_POWR_DOWN;
        STOP_DOWN_KEY;
        STOP_LEFT_KEY;
        STOP_RIGHT_KEY;
        STOP_PRG_KEY;
        STOP_LASER_UP;
        STOP_1MS;
        STOP_PMW;
        STOP_IR_DECODE;
        STOP_FAST_TIMER;  //�رտ���ʱ�ӣ��������haltʱ�����ڼ���ִ�У�
        
        START_RTC_COUNTER;
        START_MIN_ALARM;        
        START_UP_KEY;
        
        PIF11 = 0;
        STOP_IRDA_WAKE;
        START_IRDA_WAKE;
        
#if    ALL_LOSS_TYPE!=ALL_LOSS_SOFT 
        START_ALL_LOSS;       //��ȫʧѹ
#else       //���ʵ��ȫʧѹ
        STOP_ALL_LOSS;       
#endif
        
        break;
  }  
}               
/********************************************************************************
void void Init_ExtDevice_PUCK(void)
�������ܣ���ͬ״̬�¶�����ĳ�ʼ������
��ڣ� Mode--------����ģʽ����ʾ�Դ�ģʽ���豸�ĳ�ʼ��
���أ�
    ��
ģʽ�궨�壺SYS_NORMAL��SYS_SLEEP��SYS_RESUME
********************************************************************************/
void Init_ExtDevice_PUCK(INT32U Mode)
{
  Clear_CPU_Dog();
    
  switch(Mode)
  {
    case SYS_NORMAL:      //SYS_NORMALģʽ�£����ж�����Դ----------PUCK
        Debug_Print("Initial SYS_NORMAL Ext Device.......");     
        MAIN_POWER_FOR_MEM;             //�ڿ���Դ������Դ����;
        MAIN_POWER_FOR_IRDA;            //Զ�����Դ������Դ����;              
        IRDA_SEND_EN;                   //���ⷢ��ʹ��
        Init_LCD_Mode(SYS_NORMAL,Ext_Device_Stat.Status);    //����ģʽ�³�ʼ��LCD  
        OPEN_MEASU_PWR;                 //����оƬ��Դ����
        Init_ExtRTC_Pulse(1);            //ʹ���������ʼ��----PUCK 
        Ext_Device_Stat.Status=NORMAL_STATUS_PUCK;
    break;
    
    case SYS_RESUME:     //SYS_RESUMEģʽ�£����ݻ���Դ�趨��Ӧ������----------PUCK
        Debug_Print("Initial SYS_RESUME Ext Device,Wakup Source=%d",Resume_Src.Src_Flag);  
        IRDA_SEND_DIS;                  //���ⷢ�ͽ�ֹ
        
        if(Resume_Src.Src_Flag&IRAD_RESUME)//----------�Ǻ��⻽�ѣ��򿪺���󱸵�Դ
          BAK_POWER_FOR_IRDA;             //Զ�����Դ�ɵ͹��ĵ�ع���;
        else
          MAIN_POWER_FOR_IRDA;              //Զ�����Դ������Դ����      
        
        Init_LCD_Mode(SYS_RESUME,Ext_Device_Stat.Status);   //����ģʽ�³�ʼ��LCD 
        CLOSE_MEASU_PWR;                //����оƬ��Դ�ر�
        Init_ExtRTC_Pulse(0);            //ʹ���������ʼ��----PUCK
        Ext_Device_Stat.Status=RESUME_STATUS_PUCK;
    break;
    
    case SYS_SLEEP:            //SYS_SLEEPģʽ�£����ж�����Դ----------PUCK
        Debug_Print("Initial SYS_SLEEP Ext Device......"); 
        IRDA_SEND_DIS;                  //���ⷢ�ͽ�ֹ
        MAIN_POWER_FOR_IRDA;            //Զ�����Դ������Դ�������ر�Զ�����·��Դ;
        Init_LCD_Mode(SYS_SLEEP,Ext_Device_Stat.Status);   //����ģʽ�³�ʼ��LCD 
        MAIN_POWER_FOR_LCD;       //�͹���ģʽ�³�ʼ��LCD����LCD�󱸵�Դ
        MAIN_POWER_FOR_MEM;             //�ڿ���Դ������Դ����;
        CLOSE_MEASU_PWR;                //����оƬ��Դ�ر�
        Init_ExtRTC_Pulse(0);            //ʹ���������ʼ��----PUCK 
        Ext_Device_Stat.Status=SLEEP_STATUS_PUCK;
    break;    
  }  
}
/********************************************************************************
void void Init_CPU_PUCK(INT32U Mode)
�������ܣ���ͬ״̬�¶�CPU��ʼ������
��ڣ� Mode--------����ģʽ����ʾ�Դ�ģʽ���豸�ĳ�ʼ��
���أ�
    ��
ģʽ�궨�壺SYS_NORMAL��SYS_SLEEP��SYS_RESUME
********************************************************************************/
void Init_CPU_PUCK(INT32U Mode)
{
  Clear_CPU_Dog();
 
 switch(Mode) //������Ҫ���ֻ���Դ---------PUCK
 {
    case SYS_NORMAL:
        hdwinit(SYS_NORMAL);                     //Ӳ���ײ��ʼ��
        Init_Inter_Abs(SYS_NORMAL);    //�жϳ�ʼ��------PUCK
        Init_All_UART(SYS_NORMAL);      //����ģʽ�µĴ��ڳ�ʼ��  
        LVI_Start();
        Init_All_Port(SYS_NORMAL);      //��������¶����ж˿ڵĵ�ƽ����
    break;
    
    case SYS_RESUME:
        //���⡢��ť,��Ҫ��ʼ���϶���豸
        hdwinit(SYS_RESUME);                    //Ӳ���ײ��ʼ��
        BAK_POWER_FOR_MEM;             //�ڿ���Դ���ȿ�����������Ҫ������
        Init_Inter_Abs(SYS_RESUME);        
        Init_All_UART(SYS_RESUME);      //����ģʽ�µĴ��ڳ�ʼ��  
        LVI_Start();
        Init_All_Port(SYS_RESUME);    //��������¶����ж˿ڵĵ�ƽ����
    break;
    
    case SYS_SLEEP:
        Init_Resume_Source();//������л���Դ
        Init_Interr_Sram();
        Init_All_UART(SYS_SLEEP);       //˯��ģʽ�µĴ��ڳ�ʼ��
        Init_Inter_Abs(SYS_SLEEP);
        Init_All_IO_Sleep();  //��IO
        Init_CPUDevice_Clock(SYS_SLEEP);        
        Cpu_Sleep_Proc();           //˯�ߣ������ƻ��Ѵ���
        Key_Value_Pub.Key.Byte=0;
    break;    
 }  
}
/********************************************************************************
void PwrCtrl_ExtDevice_HigSpeed(void)
�������ܣ�������Դ��������£����ٿ�����Χ�豸,ע�⣬�˺�����Ϊ�ж�������ã�
��ڣ�
���أ�
    ��
********************************************************************************/
void PwrCtrl_ExtDevice_HigSpeed(void)
{
  INT32U Temp_Timer;
  INT16U i;
    
  if((Ext_Device_Stat.Status EQ TEST_STATUS_PUCK) &&(Get_Main_Init_Flag() EQ  MAIN_INITING))  //�������ʼ��δ���),�������ٶ�ִ��
  {
     LARGE_TOOGLE_OFF_SET;   //�����յĹر� 
     LARGE_TOOGLE_ON_CLR;
  }

#if ALL_LOSS_TYPE EQ ALL_LOSS_SOFT   //���ʵ��ȫʧѹ
  BAT_ON_7022;
#endif
  
  CLOSE_MEASU_PWR;           //����оƬ��Դ�ر�
  Init_Pulse_Port(0);       
  DIS_ALL_HARD_I2C_WP;           //�ر�����Ӳ��II2Ӳ��д
  DIS_ALL_HARD_I2C_WP;           //�ر��������II2Ӳ��д
  BAK_POWER_FOR_MEM;         //�ڿ���Դ�ɵ͹��ĵ�ع���;
  BAK_POWER_FOR_LCD;         //LCD��Դ�ɵ͹��ĵ�ع���;
  IRDA_SEND_DIS;             //���ⷢ�ͽ�ֹ
  //�ر�ϵ���ж�
  STOP_IR_DECODE;
  STOP_FAST_TIMER;
  STOP_IRDA_WAKE;
  STOP_ALL_LOSS;
  
  IRDA_Rec_Disable();         //����չر�
  MAIN_POWER_FOR_IRDA;       //Զ�����Դ������Դ����;ʵ���ǹرպ����Դ��
  
  if((Ext_Device_Stat.Status EQ TEST_STATUS_PUCK) &&(Get_Main_Init_Flag() EQ  MAIN_INITING))  //�������ʼ��δ���),�������ٶ�ִ��
  {
    Ms_Timer_Pub = 0;    
    for(i=0;i<22;i++)
      WAITFOR_DRV_MS_TIMEOUT(10)
        
    STOP_1MS;  
    Temp_Timer=Ms_Timer_Pub;
    START_1MS;
    
    Write_Storage_Data(_SDI_SAVE_PD_DATA_TIME,(void *)&Temp_Timer,4);  
  }
}
