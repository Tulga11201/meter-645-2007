#define INTER_ABS_PUCK
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P2"
#endif


#ifdef LOW_COST_HARD_EN
  #define  CF1_PULSE_LVEL P4_bit.no7
#else
  #define  CF1_PULSE_LVEL P14_bit.no0
#endif



//遥控器:200hz以上(即:5ms有一个低脉冲)
//日光灯:100hz左右(即:10ms有1个低脉冲)
//手抄器:50～100 hz左右(即:20/10ms有一个低脉冲)

//江机硬件: IRDA_WAKE_UP_MS=25;     IRDA_WAKE_UP_NUM=1   
//IBE: IRDA_WAKE_UP_10US=18000;     IRDA_WAKE_UP_NUM=62
//待定： 200  11 25

#define IRDA_WAKE_UP_TIME 25L
#define IRDA_WAKE_MAX_TIME (IRDA_WAKE_UP_TIME*3)
#define IRDA_WAKE_MIN_NUM   11//7   //判定唤醒帧的最小脉冲数目：55hz以下
#define IRDA_WAKE_MAX_NUM   1//7   //判定唤醒帧的最大脉冲数目：320hz以上

#define PULSE_OUT_FLAG          0x36  
#define MAX_CLR_AC_NUM          30
#define MAX_CLR_REAC_NUM        30


//初始化中断相关变量
void Init_Interr_Sram(void)
{
  
  mem_set((void *)(&Key_Value_Pub),0,sizeof(Key_Value_Pub),\
               (void *)(&Key_Value_Pub),sizeof(Key_Value_Pub));   
  INIT_STRUCT_VAR(Key_Value_Pub);
  
  mem_set((void *)(&Irda_Wake_Ctrl),0,sizeof(Irda_Wake_Ctrl),\
               (void *)(&Irda_Wake_Ctrl),sizeof(Irda_Wake_Ctrl));   
  INIT_STRUCT_VAR(Irda_Wake_Ctrl);

#ifdef REMOTER_FUNC_EN  
    mem_set((void *)(&Irda_Decode_Ctrl),0,sizeof(Irda_Decode_Ctrl),\
          (void *)(&Irda_Decode_Ctrl),sizeof(Irda_Decode_Ctrl));
    INIT_STRUCT_VAR(Irda_Decode_Ctrl);
#endif
    
  mem_set((void *)(&Pulse_Num_Temp),0,sizeof(Pulse_Num_Temp),\
        (void *)(&Pulse_Num_Temp),sizeof(Pulse_Num_Temp));
  INIT_STRUCT_VAR(Pulse_Num_Temp); 
  
  Irda_WkUP_Ms_Timr=Ms_Timer_Pub;
  Key_WkUP_Ms_Timr=Ms_Timer_Pub;
  
  mem_set((void *)(&Curr_Media_Status),0,sizeof(Curr_Media_Status),\
        (void *)(&Curr_Media_Status),sizeof(Curr_Media_Status));
  SET_STRUCT_SUM(Curr_Media_Status);    
}



//有功脉冲计数,中断等级--------INTER_GRADE_LOWERST
void Inter_CF1(void)
{
  //static volatile S_Int32U Ac_Ms_Timer={CHK_BYTE,0x000000,CHK_BYTE};
  
  EI();
  
  if(CHECK_STRUCT_VAR(Pulse_Num_Temp))
  {
    if(Pri_MeasuStatVar.MeasuIntOk)
    {
      if(CF1_PULSE_LVEL) //脉冲输入 
      {
        Pulse_Num_Temp.Ac_Pulse_Num++; 
        if(Pulse_Num_Temp.Ac_Pulse_Num>=Sys_Pulse_Var.Ac_Pulse_Freq)
        {
          Pulse_Num_Temp.AcValid=PULSE_OUT_FLAG;
          A_OUT_0;
          MEASU_A_LED_0;
          Pulse_Num_Temp.Ac_Pulse_Num-=Sys_Pulse_Var.Ac_Pulse_Freq;          
          Pulse_Num_Temp.AcNum=0;
          //Ac_Ms_Timer.Var=Ms_Timer_Pub;
        }
      }
      else
      {
        //if(Ms_Timer_Pub-Ac_Ms_Timer.Var>=Sys_Pulse_Var.Pulse_Width)
        {
          Pulse_Num_Temp.AcValid=0;
          A_OUT_1;
          MEASU_A_LED_1;
        }
      }
    }
  }
  else                            //头尾不对
  {
    Pulse_Num_Temp.Ac_Pulse_Num=0;
    INIT_STRUCT_VAR(Pulse_Num_Temp);  //把头尾填齐
  }
}

//无功脉冲计数,中断等级--------INTER_GRADE_LOWERST
void Inter_CF2(void)
{
 
  //static volatile S_Int32U Reac_Ms_Timer={CHK_BYTE,0x000000,CHK_BYTE};
  
  EI();
  if(CHECK_STRUCT_VAR(Pulse_Num_Temp))
  {
    if(Pri_MeasuStatVar.MeasuIntOk)
    {
     if(P12_bit.no0) //无功脉冲输入
     {
        Pulse_Num_Temp.Rea_Pulse_Num++; 
        if(Pulse_Num_Temp.Rea_Pulse_Num>=Sys_Pulse_Var.Reac_Pulse_Freq)
        {
          Pulse_Num_Temp.ReacValid=PULSE_OUT_FLAG;
          R_OUT_0;
          MEASU_R_LED_0;
          Pulse_Num_Temp.Rea_Pulse_Num-=Sys_Pulse_Var.Reac_Pulse_Freq;          
          Pulse_Num_Temp.ReacNum=0;
          //Reac_Ms_Timer.Var=Ms_Timer_Pub;
        }
      }
      else
      {
        //if(Ms_Timer_Pub-Reac_Ms_Timer.Var>=Sys_Pulse_Var.Pulse_Width)
        {
          Pulse_Num_Temp.ReacValid=0;
          R_OUT_1;
          MEASU_R_LED_1;
        }
      }
    }
  }
  else                            //头尾不对
  {
    Pulse_Num_Temp.Rea_Pulse_Num=0;
    INIT_STRUCT_VAR(Pulse_Num_Temp);  //把头尾填齐    
  }
}

//编程按钮,中断等级--------INTER_GRADE_LOWERST
void Inter_Prg_Key(void)  
{
  EI();
  Key_Value_Pub.Key.Bit.PrgKey=!Key_Value_Pub.Key.Bit.PrgKey;
}



//UP Key,中断等级--------INTER_GRADE_LOWERST
void Inter_Up_Key(void)
{
  EI();
  Resume_Src.Src_Flag|=KEY_RESUME;
  Key_WkUP_Ms_Timr=Ms_Timer_Pub;
  Key_Value_Pub.Key.Bit.UpKey=1;
}

//Down Key,中断等级--------INTER_GRADE_LOWERST
void Inter_Down_Key(void)
{ 
  EI();
  Key_Value_Pub.Key.Bit.DownKey=1;
}

//left key：实际是功能键,中断等级--------INTER_GRADE_LOWERST
void Inter_Left_Key(void)
{
#ifdef LEFT_KEY_EN 
  EI();
  Key_Value_Pub.Key.Bit.LeftKey=1;
#else     //左按钮不开放！
  Key_Value_Pub.Key.Bit.LeftKey=0;
#endif
}


//Right key,中断等级--------INTER_GRADE_LOWERST
void Inter_Right_Key(void)
{
#ifdef RIGHT_KEY_EN 
  EI();
  Key_Value_Pub.Key.Bit.RightKey=1;
#else     //右按钮不开放！
  Key_Value_Pub.Key.Bit.RightKey=0;
#endif  
}




/********************************************************************************
函数功能：获取当前表的键值；
入口：Id -----只能填写LUCK，其他无效！；
返回：
Bit7	Bit6    Bit5   Bit4	      Bit3	Bit2	Bit1	Bit0
0	0	0      AB间切换键	右	左	下	上
注意：读完后将清除此状态字
在非C模式下，左 右键，即是C模式切换键。
********************************************************************************/
INT8U Get_MeterKey_PUCK(INT8U Id)
{
  INT8U temp;
  if(Id!=LUCK)
    return 0;
  

  temp=Key_Value_Pub.Key.Byte&0x7f;  
  Key_Value_Pub.Key.Byte&=0x80;
  //if(Check_AB_Switch())
  //  SET_BIT(temp,4);   //AB模式切换

  return temp;
}


extern void Power_Down_Proc();
//掉电,中断等级--------INTER_GRADE_LOW
void POWER_DOWN(void)
{
  EI();
  Power_Down_Proc();
}


//激光点亮,中断等级--------INTER_GRADE_LOWERST
void laser_up(void)
{
  EI();
  START_LIGHT_ON;
}

//全失压,中断等级--------INTER_GRADE_LOWERST默认(等级：INTTM05_vect)
void Inter_ALL_LOSS(void) //正常模式下，此中断关闭，只有在sleep下中断打开
{
#if ALL_LOSS_TYPE EQ ALL_LOSS_HARD_SINGLE 
  EI();
  STOP_ALL_LOSS;   //关闭全失压
  Clear_CPU_Dog();
  All_Loss_Var.Status.Occur=1;
  
  //醒来了，根据唤醒源马上切换高速晶振-----------PUCK
  Switch_Main_Osc(RUN_MODE);
  Count_All_Loss_Proc();
  Clear_CPU_Dog();
  Switch_Main_Osc(HALT_MODE);
  
  STOP_ALL_LOSS;   //关闭全失压
#endif 
  
#if ALL_LOSS_TYPE EQ ALL_LOSS_HARD_MULTI 
  EI();
  Clear_CPU_Dog();
  All_Loss_Var.Status.Occur=1; //全失压置位，RTC闹铃中清零
  SET_VAR_CS_PUCK(All_Loss_Var.Status); 
  Clear_CPU_Dog();
#endif 
}



//红外唤醒,中断等级--------INTER_GRADE_LOW(默认：INTP3_vect) 
void Irda_Wake_Up(void)  //正常模式下，此中断关闭，只有在sleep和resume下中断打开
{
  INT8U Flag=0;
  
  EI();
  if(CHECK_STRUCT_VAR(Irda_Wake_Ctrl)==0)//头尾不对
  {
    //Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_400);  beep无供电，故去掉
    Irda_Wake_Ctrl.Start=0;
    Irda_Wake_Ctrl.WakeUp=0;
    Irda_Wake_Ctrl.PulseNum=0;    
    INIT_STRUCT_VAR(Irda_Wake_Ctrl);  //把头尾填齐
    STOP_FAST_TIMER;
    return ;
  }
  if(1==Irda_Wake_Ctrl.WakeUp)  //已经唤醒
  {
    STOP_IRDA_WAKE;           //确定已经唤醒，以后关闭唤醒脚的中断 
    return ;
  }
  
  if(0==Irda_Wake_Ctrl.Start)  //红外唤醒检测开始
  {
    Irda_Wake_Ctrl.Start=1;
    Irda_Wake_Ctrl.PulseNum=0;
    Fast_Timer_Reg=0;
    START_TIMER_1mS;
    return ;
  } 
  
  if(1==Irda_Wake_Ctrl.Start)  //红外唤醒检测继续
  {
    Irda_Wake_Ctrl.PulseNum++;
  }
   
  
  if((Fast_Timer_Reg<=IRDA_WAKE_UP_TIME) && (Irda_Wake_Ctrl.PulseNum>=IRDA_WAKE_MAX_NUM))  //高频信号
  {
    Flag=1;    
  }
  
  if((Fast_Timer_Reg >IRDA_WAKE_UP_TIME) && (Irda_Wake_Ctrl.PulseNum<=IRDA_WAKE_MIN_NUM))  //低频信号
  {
    Flag=1;    
  }
  
  if(Flag)  //限定带宽
  {
    Irda_Wake_Ctrl.Start=0;
    Irda_Wake_Ctrl.PulseNum=0;
    Irda_Wake_Ctrl.WakeUp=1;

    STOP_FAST_TIMER;              
    STOP_IRDA_WAKE;           //确定已经唤醒，以后关闭唤醒脚的中断
    Fast_Timer_Reg=0;
    Resume_Src.Src_Flag|=IRAD_RESUME;
    Irda_WkUP_Ms_Timr=Ms_Timer_Pub;
  }
}

//1000us/10us中断脉冲,中断等级--------INTER_GRADE_LOW(默认：INTTM06_vect)
void Fast_Timer(void)
{
  EI();
  if(TDR06==0x07)   //单位：976.5625us,程序慢速晶振跑
  {
    Fast_Timer_Reg++;
    
    if(1==Irda_Wake_Ctrl.WakeUp)  //已经唤醒
    {
      STOP_IRDA_WAKE;           //确定已经唤醒，以后关闭唤醒脚的中断 
      STOP_FAST_TIMER;
      Fast_Timer_Reg=0;
      return ;
    }
  
    if(Fast_Timer_Reg>=IRDA_WAKE_MAX_TIME)   //时间超限,关闭定时器，由唤醒脚来启动
    {
      Fast_Timer_Reg=0;
      STOP_FAST_TIMER;
      Irda_Wake_Ctrl.Start=0;
      Irda_Wake_Ctrl.WakeUp=0;
      Irda_Wake_Ctrl.PulseNum=0;
      return ;
    }
  }

#ifdef REMOTER_FUNC_EN  
  if(TDR06==0x6d || TDR06==0x36)   //单位：9.94647us,程序快速晶振跑
  {
    Fast_Timer_Reg++;
    if(Fast_Timer_Reg>=9000 || (0==INTER_DECODE_EN))  //时间超限，或者解码中断已经关闭！
    {
      Fast_Timer_Reg=0;
      STOP_FAST_TIMER;
      
      Irda_Decode_Ctrl.Start=0;
      Irda_Decode_Ctrl.Done=0;
      Irda_Decode_Ctrl.Index=0;
      Irda_Decode_Ctrl.TrigTimer=0;
    }
  }
#endif
}
//遥控器解码:所有碼接收时间 64.02ms左右,中断等级--------INTER_GRADE_LOW(默认：INTP5_vect)
void IR_Decode_Proc(void)
{
#ifdef REMOTER_FUNC_EN 
  EI();
  if(Irda_Decode_Ctrl.Done)
   return ;
  if(Irda_Decode_Ctrl.Start==0 && Irda_Decode_Ctrl.TrigTimer==0)  //启动快速Timer
  {
    START_TIMER_10uS;
    Fast_Timer_Reg=0;
    
    Irda_Decode_Ctrl.TrigTimer=1;
    Irda_Decode_Ctrl.Done=0;
    Irda_Decode_Ctrl.Index=0; 
    return ;
  }

  if(Irda_Decode_Ctrl.TrigTimer && TMMK06)  //意外将Timer关闭，又不能开启
  {
    Irda_Decode_Ctrl.Start=0;
    Irda_Decode_Ctrl.Done=0;
    Irda_Decode_Ctrl.Index=0;
    Irda_Decode_Ctrl.TrigTimer=0;
    return ;
  }
  if(Irda_Decode_Ctrl.Start==0)
  {
    if(Fast_Timer_Reg>=1250 && Fast_Timer_Reg<=1450)
    {
      Irda_Decode_Ctrl.Start=1;
      Fast_Timer_Reg=0;
    }
  }
  else   //已经发现启动信号
  {
    if(Fast_Timer_Reg>=185 && Fast_Timer_Reg<=240)
    {
        if(Irda_Decode_Ctrl.Index<CODE_NUM*8)
        {
          SET_BIT(Irda_Decode_Ctrl.CodeBuf[Irda_Decode_Ctrl.Index/8],Irda_Decode_Ctrl.Index%8);
          Irda_Decode_Ctrl.Index++;
          Fast_Timer_Reg=0;
        }
    }
    else if(Fast_Timer_Reg>=70&&Fast_Timer_Reg<=130)
    {
        if(Irda_Decode_Ctrl.Index<CODE_NUM*8)
        {
          CLR_BIT(Irda_Decode_Ctrl.CodeBuf[Irda_Decode_Ctrl.Index/8],Irda_Decode_Ctrl.Index%8);
          Irda_Decode_Ctrl.Index++;
          Fast_Timer_Reg=0;
        }
     } 
    else  //乱码，解码出错了
    {
      Irda_Decode_Ctrl.Start=0;
      Irda_Decode_Ctrl.Done=0;
      Irda_Decode_Ctrl.Index=0;
      Irda_Decode_Ctrl.TrigTimer=0;
      STOP_FAST_TIMER;
      Fast_Timer_Reg=0;
    }
    if(Irda_Decode_Ctrl.Index>=CODE_NUM*8)	
    {
      Irda_Decode_Ctrl.Start=0;
      Irda_Decode_Ctrl.TrigTimer=0;
      Irda_Decode_Ctrl.Done=1;
      STOP_FAST_TIMER;
      Fast_Timer_Reg=0;
    } 
  }
#endif
}
//1秒脉冲,中断等级--------INTER_GRADE_LOWERST
void INT_1HZ(void)
{
  EI();
  ;//Port_Out_Pub(EXT_ID_SEC_EN,Sys_Pulse_Var.Pulse_Width);
}

//内部RTC闹铃,中断等级--------INTER_GRADE_LOWERST (默认：INTRTC_vect)
void CPU_RTC_Interrupt(void)
{
#if ALL_LOSS_TYPE EQ ALL_LOSS_HARD_SINGLE 
  EI();
#endif
  
#if ALL_LOSS_TYPE EQ ALL_LOSS_HARD_MULTI 
  EI();
  Clear_CPU_Dog();
  //醒来了，根据唤醒源马上切换高速晶振-----------PUCK
  Switch_Main_Osc(RUN_MODE);
  Count_All_Loss_Proc();  
  Switch_Main_Osc(HALT_MODE);
  Clear_CPU_Dog();  
#endif 
}

//系统1ms的Tick,中断等级--------INTER_GRADE_LOWERST(默认：INTTM07_vect)
void count_1ms(void)
{ 
  EI();
  static volatile S_Int8U Num={CHK_BYTE,0,CHK_BYTE};
  static volatile S_Int8U Num1={CHK_BYTE,0,CHK_BYTE};
  static volatile S_Int8U Ms_Timer={CHK_BYTE,0,CHK_BYTE}; 
  static volatile S_Int16U Sec_Timr_Temp={CHK_BYTE,0,CHK_BYTE};
  
#ifdef RST_IC_7X6_EN 
  static volatile S_Int8U Num2={CHK_BYTE,0,CHK_BYTE};
#endif
  
  Ms_Timer_Pub++;    //公有毫秒定时器更新
  Ms_Timer.Var++;
  
  if(Ms_Timer.Var>=OS_MS_PER_TICK)
  {
    Ms_Timer.Var=0;    
    OS_Tick_ISR();
  }
  
  Num1.Var++;
  if(Num1.Var>=10)
  {
    Ms10_Timer_Pub++;
    Num1.Var=0;
  }
  
#ifdef RST_IC_7X6_EN
  Num2.Var++;
  if(Num2.Var>=2)
  {
    B_WTD_1;
    Num2.Var=0;
  }
#endif
  
  
  Sec_Timr_Temp.Var++;
  if(Sec_Timr_Temp.Var>=1000)
  {
    Sec_Timr_Temp.Var=0;
    Sec_Timer_Pub++;
  }

  if(JUDGE_POWER_OFF EQ 0)  //无掉电情况下，才开启端口功能
  {
    Num.Var++;
    if(Num.Var>=MS_HOOK_NUM)
    {
      ExtPort_xMs_Hook();
      
      if(Pulse_Num_Temp.AcValid EQ PULSE_OUT_FLAG)  //脉冲清除
      {     
        Pulse_Num_Temp.AcNum++;
        if(Pulse_Num_Temp.AcNum>MAX_CLR_AC_NUM)
        {
          A_OUT_1;
          MEASU_A_LED_1;
          Pulse_Num_Temp.AcNum=0;
        }        
      }
      
      if(Pulse_Num_Temp.ReacValid EQ PULSE_OUT_FLAG)
      {        
        Pulse_Num_Temp.ReacNum++;
        if(Pulse_Num_Temp.ReacNum>MAX_CLR_REAC_NUM)
        {
          R_OUT_1;
          MEASU_R_LED_1;
          Pulse_Num_Temp.ReacNum=0;
        }
        
      }    
      Num.Var=0;
    } 
  }
}
