#define DEVICE_ABS_PUCK
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P1"
#endif
/********************************************************************************
函数功能：各种模式下：CPU外围时钟初始化
入口：
返回：
    无
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
函数功能：复位后打印复位源
入口：
返回：
    无
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
函数功能：resume时，对CPU IO口的定义
入口：
返回：
1：resum下不用的IO口，IO复位后默认为输入
********************************************************************************/
void Init_All_IO_Resume(INT8U Status)
{
    P0=0;
    PU0=0;
    
    
    PM0_bit.no0=0;     //KEY6---------------------开端盖(后端盖)铅封
    PM0_bit.no1=0;     //KEY5---------------------开大盖(上端盖)
    PM0_bit.no2=0;     //------------------------TXD-GPRS
    PM0_bit.no3=0;     //-----------------------:RXD_GPRS(VCC供电,CPU收)
    PM0_bit.no4=0;     //-----------------------:事件指示脚：EVENT_GPRS(VCC供电)
    PM0_bit.no5=0;     //内卡电源控制--------------MEN_PWR
    PM0_bit.no6=0;     //-----------------------16-SDA:24C16数据线
    
    
    PM0|=PM0_DEFAULT;
    
    P1=0;
    PU1=0;
    PM1_bit.no0=0;   //远红外发送使能-------IR_FAR_EN
    PM1_bit.no1=0;   //串口1----------------RXD1
    PM1_bit.no2=0;   //串口1----------------TXD1
    PM1_bit.no3=0;   //串口2----------------TXD2
    PM1_bit.no4=0;   //串口2----------------RXD2
    PM1_bit.no5=0;   //485控制口------------RE/DE2,或者是 ESAM卡电源电源控制
    PM1_bit.no6=0;   //遥控器解码-----------RXD1
    PM1_bit.no7=1;   //PWM------------------PWM
    
    P2=0;
    PM2_bit.no0=0;    //计量RST---------7022_RST
    PM2_bit.no1=0;    //计量SIG---------7022_SIG
    PM2_bit.no2=0;    //计量SDO---------7022_SDO
    PM2_bit.no3=0;    //计量SDI ---------7022_SDI    
    PM2_bit.no4=0;    //计量SCK---------7022_SCK
    PM2_bit.no5=0;    //计量POWER-------PULSE_PWR
    PM2_bit.no6=1;    //RTC(VBB供电)--------------RTC1_SDA，先设为输入，在I2CSoft中会重新初始化
    PM2_bit.no7=1;    //RTC(VBB供电)--------------RTC1_SCL，先设为输入，在I2CSoft中会重新初始化

    
    P3=0;
    PU3=0; 
    PM3_bit.no0=1; //红外唤醒,外部中断计数-------Laser_WKP------新板子(2009-02-18):IC_FAIL
    PM3_bit.no1=1; //掉电检测-----------------------V_D1
    PM3|=PM3_DEFAULT;
    
    P4=0;
    PU4=0;
    PM4_bit.no0=1; //仿真调试口(VBB上拉)----------TOOL0
    PM4_bit.no1=0; //仿真调试口-------------------TOOL1
    PM4_bit.no2=0; //DataFlash片选----------------45DB161_/CS
    PM4_bit.no3=0; //DataFlash时钟----------------45DB161_SCK
    PM4_bit.no4=0; //DataFlash输出----------------45DB161_SO
    PM4_bit.no5=0; //DataFlash输入----------------45DB161_SI
    PM4_bit.no6=0; //全失压----------ALL_V_LOSS
    PM4_bit.no7=0; //DataFlash--------------------45DB161_RDY  
        
    P5=0;
    PU5=0;
    
    PM5_bit.no0=0;   //7022_PWR
    PM5_bit.no1=0;   //IC_OUT
    PM5_bit.no2=0;   //IC_RST
    PM5_bit.no3=0;   //IC_SW--------------
    PM5_bit.no4=1;   //喂狗信号----------------------------------设为输入，喂狗无效
    PM5_bit.no5=0;   //干簧管检测,悬空不用------------K1
    PM5_bit.no6=1;   //硬件自检测(VBB上拉)-----------------
    PM5_bit.no7=1;   //工厂模式(VBB上拉)--------
    
    P6=0;
    PU6=0;
    PM6_bit.no0=1;   //内卡硬件I2C SCLK-------MEM_SCL，先设为输入，在I2C中会重新初始化
    PM6_bit.no1=1;   //内卡硬件I2C SDA--------MEM_SDA，先设为输入，在I2C中会重新初始化
    PM6_bit.no2=1;   //内卡硬件I2C写保护------MEM_WP，先设为输入，在I2C中会重新初始化
    
#ifdef MEASU_BAKPWR_NEW_EN
    PM6_bit.no3=0;   //
#else
    PM6_bit.no3=1;   //
#endif
    
    PM6_bit.no4=0;   //无功方向---------------A_DIR
    PM6_bit.no5=0;   //无功方向---------------R_DIR
    PM6_bit.no6=0;   //有功输出---------------A_EOUT
    PM6_bit.no7=0;   //无功输出---------------R_EOUT
    
    P7=0;
    PU7=0;    
    PM7_bit.no0=0;   //-------------------16-SCL:24C16时钟线
    PM7_bit.no1=1;   //(VBB上拉)-------------------清需量
    PM7_bit.no2=1;   //(VBB上拉)-------------------选择(左键)
    PM7_bit.no3=1;   //UPKEY(VBB上拉)---------上翻
    PM7_bit.no4=1;   //UPKEY(VBB上拉)---------下翻
    PM7_bit.no5=0;   //--------------------24C16写保护信号线
    PM7_bit.no6=0;   //UPKEY(VCC上拉)---------编程
    PM7_bit.no7=1;   //红外唤醒(VBB上拉)------LASER_WAKEUP
    
   
    P8=0;
    PU8=0;
    PM8_bit.no0=0;   //跳闸输出-------------------SWITCH_TOGGLE
    PM8_bit.no1=0;   //报警端子排-----------------ALARM
    PM8_bit.no2=1;   //秒脉冲使能(和逻辑门连接，但和3231连接作为逻辑门)-----SECOND_/EN
    PM8_bit.no3=0;   //需量周期-------------------DEMAND
    PM8_bit.no4=0;   //时段输出-------------------TIME_SW
    PM8_bit.no5=0;   //低功耗电池检测-------------VB3_OK1
    PM8_bit.no6=0;   //远红外电源控制-------------IR_FAR_PWR
    PM8_bit.no7=0;   //总线扩展(EX7)--------------NC------新板子(2009-02-18):IC_SW
    
    P11=0;
    PM11_bit.no0=0;   //远红外/吸附红外切换----------IR_FAR_/SELECT
    PM11_bit.no1=0;   //时钟电池检测-----------VB1_OK
    PM11|=PM11_DEFAULT;
    
    P12=0;
    PU12=0;
    PM12_bit.no0=0;   //CF2输入-----------7022_CF2
    PM12_bit.no1=1;   //X1-----------------
    PM12_bit.no2=1;   //X2-----------------
    PM12_bit.no3=1;   //XT1----------------
    PM12_bit.no4=1;   //XT2----------------
    PM12|=PM12_DEFAULT;
    
    P13=0;
    PU13=0;    
    PM13_bit.no0=0;   //7022_CS
    PM13_bit.no1=0;   //预留-------------7022_341_331
    PM13|=PM13_DEFAULT;
    
    P14=0;
    PU14=0;
    PM14_bit.no0=0;   //CF1输入---------7022_CF1
    PM14_bit.no1=0;   //时钟秒脉冲(VCC上拉,与3231相连ECOND_PULSE
    PM14_bit.no2=0;   //蜂鸣器----------ALARM_SND
    PM14_bit.no3=0;   //串口0----------RXD0
    PM14_bit.no4=0;   //串口0----------TXD0
    PM14_bit.no5=0;   //485控制口--------RE/DE0
    PM14|=PM14_DEFAULT;

    if(Status EQ RESUME_STATUS_PUCK)  //已经唤醒并且初始化过了。
      P15=0x10;            //LCD POWER-----------------LCD_POWER
    else
      P15=0;
    
    PM15_bit.no0=0;   //有功脉冲指示灯-------------A-EOU1    
    PM15_bit.no1=0;   //无功脉冲指示灯-------------R-EOU1
    PM15_bit.no2=1;   //LCD背光改为输入，背光无效------Back_Light_On   
    PM15_bit.no3=0;   //LCD CS--------------------1623-/CS
    PM15_bit.no4=0;   //LCD POWER-----------------LCD_POWER
    PM15_bit.no5=0;   //LCD DATA------------------1623-DATA
    PM15_bit.no6=0;   //LCD WRITE-----------------1623-/WR
    PM15_bit.no7=0;   //预留----------------------NC
 }
/********************************************************************************
函数功能：进入睡眠前，对CPU IO口输出为0
入口：
返回：
1：原有输入脚还是输入脚，不变；
2：未用的输入脚，已用的输出脚，强制输出为0；
3：双向IO，
4：注意的几个脚：IC_PWR，SECOND_PULSE，PWM，K1(干皇管)
********************************************************************************/
void Init_All_IO_Sleep(void)
{    

    P0=0;
    PU0=0;
    
    

    PM0_bit.no0=0;     //---------------------开端盖(后端盖)铅封
    PM0_bit.no1=0;     //---------------------开大盖(上端盖)
    PM0_bit.no2=0;     //------------------------TXD-GPRS
    PM0_bit.no3=0;     //-----------------------:RXD_GPRS(VCC供电,CPU收)
    PM0_bit.no4=0;     //-----------------------:事件指示脚：EVENT_GPRS(VCC供电)
    PM0_bit.no5=0;     //内卡电源控制--------------MEN_PWR
    PM0_bit.no6=0;     //-----------------------16-SDA:24C16数据线
    
    PM0|=PM0_DEFAULT;
    
    P1=0;
    PU1=0;
    PM1_bit.no0=0;   //远红外发送使能-------IR_FAR_EN
    PM1_bit.no1=0;   //串口1----------------RXD1
    PM1_bit.no2=0;   //串口1----------------TXD1
    PM1_bit.no3=0;   //串口2----------------TXD2
    PM1_bit.no4=0;   //串口2----------------RXD2
    PM1_bit.no5=0;   //485控制口------------RE/DE2,或者是 ESAM卡电源电源控制
    PM1_bit.no6=0;   //遥控器解码-----------RXD1
    PM1_bit.no7=1;   //PWM------------------PWM
    
    P2=0;
    PM2_bit.no0=0;    //计量RST---------7022_RST
    PM2_bit.no1=0;    //计量SIG---------7022_SIG
    PM2_bit.no2=0;    //计量SDO---------7022_SDO
    PM2_bit.no3=0;    //计量SDI ---------7022_SDI    
    PM2_bit.no4=0;    //计量SCK---------7022_SCK
    PM2_bit.no5=0;    //计量POWER-------PULSE_PWR
    PM2_bit.no6=1;    //RTC(VBB供电)--------------RTC1_SDA
    PM2_bit.no7=1;    //RTC(VBB供电)--------------RTC1_SCL

    
    
    P3=0;
    PU3=0; 
    PM3_bit.no0=1; //红外唤醒,外部中断计数-------Laser_WKP------新板子(2009-02-18):IC_FAIL
    PM3_bit.no1=1; //掉电检测-----------------------V_D1
    PM3|=PM3_DEFAULT;
    
    P4=0;
    PU4=0;
    PM4_bit.no0=1; //仿真调试口(VBB上拉)----------TOOL0
    PM4_bit.no1=0; //仿真调试口-------------------TOOL1
    PM4_bit.no2=0; //DataFlash片选----------------45DB161_/CS
    PM4_bit.no3=0; //DataFlash时钟----------------45DB161_SCK
    PM4_bit.no4=0; //DataFlash输出----------------45DB161_SO
    PM4_bit.no5=0; //DataFlash输入----------------45DB161_SI
    PM4_bit.no6=1; //------新板子(2009-02-18):全失压----------ALL_V_LOSS
    PM4_bit.no7=0; //DataFlash--------------------45DB161_RDY  
        
    P5=0;
    PU5=0;
    PM5_bit.no0=0;   //7022_PWR
    PM5_bit.no1=0;   //IC_OUT
    PM5_bit.no2=0;   //IC_RST
    PM5_bit.no3=0;   //IC_SW--------------
    PM5_bit.no4=0;   //喂狗信号----------------------------------
    PM5_bit.no5=0;   //干簧管检测,悬空不用------------K1
    PM5_bit.no6=1;   //硬件自检测(VBB上拉)-----------------
    PM5_bit.no7=1;   //工厂模式(VBB上拉)----------
    
    P6=0;
    PU6=0;
    PM6_bit.no0=0;   //内卡硬件I2C SCLK-------MEM_SCL
    PM6_bit.no1=0;   //内卡硬件I2C SDA--------MEM_SDA
    PM6_bit.no2=0;   //内卡硬件I2C写保护------MEM_WP
    
#ifdef MEASU_BAKPWR_NEW_EN
    PM6_bit.no3=0;   //
#else
    PM6_bit.no3=1;   //
#endif
    
    PM6_bit.no4=0;   //无功方向---------------A_DIR
    PM6_bit.no5=0;   //无功方向---------------R_DIR
    PM6_bit.no6=0;   //有功输出---------------A_EOUT
    PM6_bit.no7=0;   //无功输出---------------R_EOUT
    
    P7=0;
    PU7=0;
    PM7_bit.no0=0;   //-------------------16-SCL:24C16时钟线
    PM7_bit.no1=1;   //(VBB上拉)-------------------清需量
    PM7_bit.no2=1;   //(VBB上拉)-------------------选择(左键)
    PM7_bit.no3=1;   //上翻(VBB上拉)---------KEY4
    PM7_bit.no4=1;   //下翻(VBB上拉)---------KEY2
    PM7_bit.no5=0;   //--------------------24C16写保护信号线  
    PM7_bit.no6=0;   //UPKEY(VCC上拉)---------编程
    PM7_bit.no7=1;   //红外唤醒(VBB上拉)------LASER_WAKEUP
    
    
    P8=0;
    PU8=0;
    PM8_bit.no0=0;   //跳闸输出-------------------SWITCH_TOGGLE
    PM8_bit.no1=0;   //报警端子排-----------------ALARM
    PM8_bit.no2=0;   //秒脉冲使能(和逻辑门连接，但和3231连接作为逻辑门)-----SECOND_/EN
    PM8_bit.no3=0;   //需量周期-------------------DEMAND
    PM8_bit.no4=0;   //时段输出-------------------TIME_SW
    PM8_bit.no5=0;   //低功耗电池检测-------------VB3_OK1
    PM8_bit.no6=0;   //远红外电源控制-------------IR_FAR_PWR
    PM8_bit.no7=0;   //总线扩展(EX7)--------------NC------新板子(2009-02-18):IC_SW
    
    P11=0;
    PM11_bit.no0=0;   //远红外/吸附红外切换----------IR_FAR_/SELECT
    PM11_bit.no1=0;   //时钟电池检测-----------VB1_OK
    PM11|=PM11_DEFAULT;
    
    P12=0;
    PU12=0;
    PM12_bit.no0=0;   //CF2输入-----------7022_CF2
    PM12_bit.no1=1;   //X1-----------------
    PM12_bit.no2=1;   //X2-----------------
    PM12_bit.no3=1;   //XT1----------------
    PM12_bit.no4=1;   //XT2----------------
    PM12|=PM12_DEFAULT;
    
    P13=0;
    PU13=0;    
    PM13_bit.no0=0;   //7022_CS
    PM13_bit.no1=0;   //预留-------------7022_341_331
    PM13|=PM13_DEFAULT;
    
    P14=0;
    PU14=0;
    PM14_bit.no0=0;   //CF1输入口----------7022_CF1
    PM14_bit.no1=0;   //时钟秒脉冲(VCC上拉,与3231相连ECOND_PULSE
    PM14_bit.no2=0;   //蜂鸣器----------ALARM_SND
    PM14_bit.no3=0;   //串口0----------RXD0
    PM14_bit.no4=0;   //串口0----------TXD0
    PM14_bit.no5=0;   //485控制口--------RE/DE0
    PM14|=PM14_DEFAULT;
    
    P15=0;
    PM15_bit.no0=0;   //有功脉冲指示灯-------------A-EOU1    
    PM15_bit.no1=0;   //无功脉冲指示灯-------------R-EOU1
    PM15_bit.no2=0;   //LCD背光--------------------Back_Light_On   
    PM15_bit.no3=0;   //LCD CS--------------------1623-/CS
    PM15_bit.no4=0;   //LCD POWER-----------------LCD电源
    PM15_bit.no5=0;   //LCD DATA------------------1623-DATA
    PM15_bit.no6=0;   //LCD WRITE-----------------1623-/WR
    PM15_bit.no7=0;   //预留----------------------NC------新板子(2009-02-18):LED报警指示
}
/********************************************************************************
函数功能：复位后对CPU的初始化
入口：
返回：
    无
********************************************************************************/
void Init_Hard_PUCK(void)
{
  hdwinit(SYS_NORMAL);
  Clr_Ext_Inter_Dog();
  START_1MS;    //打开毫秒中断，为OS提供tick
  START_RTC_COUNTER; 
  
  START_POWR_DOWN;   //将掉电中断打开，应HUCK需求，防止进入 PD_DATA_PROC 以后的流程
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
  STOP_ALL_LOSS;         //关闭全失压
}
/********************************************************************************
函数功能：睡眠前切换只sub时钟，关闭主时钟振荡,进入halt模式
入口：
返回：
    无
********************************************************************************/
void Goto_Sleep_PUCK(void)
{
   if(Switch_Main_Osc(HALT_MODE)) 
   {
     Clear_CPU_Dog();  //睡前喂狗
     while(1)   //对RTC闹铃和全失压的处理------PUCK
     {
       //CG_SelectPowerSaveMode(PSHALT);
       //STOP();
       HALT();
       //..........................................
       Clear_CPU_Dog();
       if((Resume_Src.Src_Flag&(IRAD_RESUME|KEY_RESUME)))  //不是全失压或者RTC闹铃，退出睡眠
         break;       
     } 
   }
   //醒来了，根据唤醒源马上切换高速晶振-----------PUCK 
   Switch_Main_Osc(RUN_MODE);
   Clear_CPU_Dog(); 
}  
/********************************************************************************
函数功能：对睡眠做了次数限制
入口：
返回：
    无
********************************************************************************/
#define WAKE_UP_TIMES 60  //红外和全失压唤醒总次数
void Cpu_Sleep_Proc(void)
{
  static S_Int8U Counts={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Last_Date={CHK_BYTE,0xFF,CHK_BYTE};
  
  while(1)
  {
    Goto_Sleep_PUCK();
    if((Resume_Src.Src_Flag&(IRAD_RESUME|KEY_RESUME)))
    {
      Counts.Var=0;   //按钮/红外唤醒,无限制,唤醒次数清0
      Last_Date.Var=Cur_Time1.Date;
      break;
    }
      
    if(DAY!=Last_Date.Var)
    {
      Counts.Var=0;   //跨天，唤醒次数清0
      Last_Date.Var=Cur_Time1.Date;
    }
    else
      Counts.Var++;
    
    Clear_CPU_Dog(); 
    
    if(Counts.Var<WAKE_UP_TIMES)
      break;
    
    //当天唤醒次数超过，清除本次按钮和红外唤醒源
    if(Counts.Var==254)  //避免翻转
      Counts.Var=WAKE_UP_TIMES;
    Resume_Src.Src_Flag&=(INT8U)(~(IRAD_RESUME|KEY_RESUME));  //清除按钮和红外唤醒源
  }
}
/********************************************************************************
函数功能：根据不同的工作模式，设置相应的中断及中断等级
入口：
返回：
    无
********************************************************************************/
void Init_Inter_Abs(INT32U Mode)
{  
  switch(Mode)//以下需要区分唤醒源---------PUCK
  {
    case SYS_NORMAL:   // SYS_NORMAL模式下，不必判定唤醒源      
        START_1MS;    //打开毫秒中断，为OS提供tick
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
        STOP_ALL_LOSS;         //关闭全失压
    break;
    
    case SYS_RESUME:  //SYS_RESUME模式下，根据唤醒源开启中断
        STOP_CF1;
        STOP_CF2;
        STOP_1HZ;
        STOP_POWR_DOWN;
        STOP_LEFT_KEY;
        STOP_RIGHT_KEY;
        STOP_LASER_UP;
        STOP_PRG_KEY;
        
        if(Resume_Src.Src_Flag&IRAD_RESUME)  //是在sleep模式下的红外唤醒，停止唤醒
        {
          STOP_IRDA_WAKE;        //与 START_IR_DECODE 互斥
          if(RESUME_REMOTER_EN)   //遥控器打开              
            START_IR_DECODE;       //唤醒下，可以使用红外遥控器

        }
        else
        { 
          START_IRDA_WAKE; 
          STOP_IR_DECODE;       //与 START_IR_DECODE 互斥
        }
        
        START_1MS;          //启动1ms中断-----PUCK
        START_UP_KEY;
        START_DOWN_KEY;
        
        
        START_RTC_COUNTER; 
        START_MIN_ALARM;
        
#if    ALL_LOSS_TYPE!=ALL_LOSS_SOFT
        if((All_Loss_Var.Status.Nums==0)||(All_Loss_Var.Status.Mins==0))   //没有事件发生
        START_ALL_LOSS;       //打开全失压
#else   //软件实现全失压
        STOP_ALL_LOSS;       
#endif
       
    break;
    
    case SYS_SLEEP:  //SYS_SLEEP模式下，不必判定唤醒源
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
        STOP_FAST_TIMER;  //关闭快速时钟，避免进入halt时，还在继续执行！
        
        START_RTC_COUNTER;
        START_MIN_ALARM;        
        START_UP_KEY;
        
        PIF11 = 0;
        STOP_IRDA_WAKE;
        START_IRDA_WAKE;
        
#if    ALL_LOSS_TYPE!=ALL_LOSS_SOFT 
        START_ALL_LOSS;       //打开全失压
#else       //软件实现全失压
        STOP_ALL_LOSS;       
#endif
        
        break;
  }  
}               
/********************************************************************************
void void Init_ExtDevice_PUCK(void)
函数功能：不同状态下对外设的初始化工作
入口： Mode--------工作模式，表示对此模式下设备的初始化
返回：
    无
模式宏定义：SYS_NORMAL、SYS_SLEEP、SYS_RESUME
********************************************************************************/
void Init_ExtDevice_PUCK(INT32U Mode)
{
  Clear_CPU_Dog();
    
  switch(Mode)
  {
    case SYS_NORMAL:      //SYS_NORMAL模式下，不判定唤醒源----------PUCK
        Debug_Print("Initial SYS_NORMAL Ext Device.......");     
        MAIN_POWER_FOR_MEM;             //内卡电源由主电源供给;
        MAIN_POWER_FOR_IRDA;            //远红外电源由主电源供给;              
        IRDA_SEND_EN;                   //红外发送使能
        Init_LCD_Mode(SYS_NORMAL,Ext_Device_Stat.Status);    //工作模式下初始化LCD  
        OPEN_MEASU_PWR;                 //计量芯片电源开启
        Init_ExtRTC_Pulse(1);            //使能秒脉冲初始化----PUCK 
        Ext_Device_Stat.Status=NORMAL_STATUS_PUCK;
    break;
    
    case SYS_RESUME:     //SYS_RESUME模式下，根据唤醒源设定相应的外设----------PUCK
        Debug_Print("Initial SYS_RESUME Ext Device,Wakup Source=%d",Resume_Src.Src_Flag);  
        IRDA_SEND_DIS;                  //红外发送禁止
        
        if(Resume_Src.Src_Flag&IRAD_RESUME)//----------是红外唤醒，打开红外后备电源
          BAK_POWER_FOR_IRDA;             //远红外电源由低功耗电池供给;
        else
          MAIN_POWER_FOR_IRDA;              //远红外电源由主电源供给      
        
        Init_LCD_Mode(SYS_RESUME,Ext_Device_Stat.Status);   //唤醒模式下初始化LCD 
        CLOSE_MEASU_PWR;                //计量芯片电源关闭
        Init_ExtRTC_Pulse(0);            //使能秒脉冲初始化----PUCK
        Ext_Device_Stat.Status=RESUME_STATUS_PUCK;
    break;
    
    case SYS_SLEEP:            //SYS_SLEEP模式下，不判定唤醒源----------PUCK
        Debug_Print("Initial SYS_SLEEP Ext Device......"); 
        IRDA_SEND_DIS;                  //红外发送禁止
        MAIN_POWER_FOR_IRDA;            //远红外电源由主电源供给，关闭远红外电路电源;
        Init_LCD_Mode(SYS_SLEEP,Ext_Device_Stat.Status);   //唤醒模式下初始化LCD 
        MAIN_POWER_FOR_LCD;       //低功耗模式下初始化LCD，关LCD后备电源
        MAIN_POWER_FOR_MEM;             //内卡电源由主电源供给;
        CLOSE_MEASU_PWR;                //计量芯片电源关闭
        Init_ExtRTC_Pulse(0);            //使能秒脉冲初始化----PUCK 
        Ext_Device_Stat.Status=SLEEP_STATUS_PUCK;
    break;    
  }  
}
/********************************************************************************
void void Init_CPU_PUCK(INT32U Mode)
函数功能：不同状态下对CPU初始化工作
入口： Mode--------工作模式，表示对此模式下设备的初始化
返回：
    无
模式宏定义：SYS_NORMAL、SYS_SLEEP、SYS_RESUME
********************************************************************************/
void Init_CPU_PUCK(INT32U Mode)
{
  Clear_CPU_Dog();
 
 switch(Mode) //以下需要区分唤醒源---------PUCK
 {
    case SYS_NORMAL:
        hdwinit(SYS_NORMAL);                     //硬件底层初始化
        Init_Inter_Abs(SYS_NORMAL);    //中断初始化------PUCK
        Init_All_UART(SYS_NORMAL);      //正常模式下的串口初始化  
        LVI_Start();
        Init_All_Port(SYS_NORMAL);      //正常情况下对所有端口的电平设置
    break;
    
    case SYS_RESUME:
        //红外、按钮,需要初始化较多的设备
        hdwinit(SYS_RESUME);                    //硬件底层初始化
        BAK_POWER_FOR_MEM;             //内卡电源最先开启，因后面就要读参数
        Init_Inter_Abs(SYS_RESUME);        
        Init_All_UART(SYS_RESUME);      //正常模式下的串口初始化  
        LVI_Start();
        Init_All_Port(SYS_RESUME);    //唤醒情况下对所有端口的电平设置
    break;
    
    case SYS_SLEEP:
        Init_Resume_Source();//清除所有唤醒源
        Init_Interr_Sram();
        Init_All_UART(SYS_SLEEP);       //睡眠模式下的串口初始化
        Init_Inter_Abs(SYS_SLEEP);
        Init_All_IO_Sleep();  //设IO
        Init_CPUDevice_Clock(SYS_SLEEP);        
        Cpu_Sleep_Proc();           //睡眠，并限制唤醒次数
        Key_Value_Pub.Key.Byte=0;
    break;    
 }  
}
/********************************************************************************
void PwrCtrl_ExtDevice_HigSpeed(void)
函数功能：在主电源掉电情况下，快速控制外围设备,注意，此函数是为中断里面调用！
入口：
返回：
    无
********************************************************************************/
void PwrCtrl_ExtDevice_HigSpeed(void)
{
  INT32U Temp_Timer;
  INT16U i;
    
  if((Ext_Device_Stat.Status EQ TEST_STATUS_PUCK) &&(Get_Main_Init_Flag() EQ  MAIN_INITING))  //主任务初始化未完成),以最快的速度执行
  {
     LARGE_TOOGLE_OFF_SET;   //将常闭的关闭 
     LARGE_TOOGLE_ON_CLR;
  }

#if ALL_LOSS_TYPE EQ ALL_LOSS_SOFT   //软件实现全失压
  BAT_ON_7022;
#endif
  
  CLOSE_MEASU_PWR;           //计量芯片电源关闭
  Init_Pulse_Port(0);       
  DIS_ALL_HARD_I2C_WP;           //关闭所有硬件II2硬件写
  DIS_ALL_HARD_I2C_WP;           //关闭所有软件II2硬件写
  BAK_POWER_FOR_MEM;         //内卡电源由低功耗电池供给;
  BAK_POWER_FOR_LCD;         //LCD电源由低功耗电池供给;
  IRDA_SEND_DIS;             //红外发送禁止
  //关闭系列中断
  STOP_IR_DECODE;
  STOP_FAST_TIMER;
  STOP_IRDA_WAKE;
  STOP_ALL_LOSS;
  
  IRDA_Rec_Disable();         //红接收关闭
  MAIN_POWER_FOR_IRDA;       //远红外电源由主电源供给;实际是关闭红外电源！
  
  if((Ext_Device_Stat.Status EQ TEST_STATUS_PUCK) &&(Get_Main_Init_Flag() EQ  MAIN_INITING))  //主任务初始化未完成),以最快的速度执行
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
