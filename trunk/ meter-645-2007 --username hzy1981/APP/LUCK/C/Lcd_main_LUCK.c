
#define LCD_MAIN_C
#include "Pub_Puck.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "L2"
#endif
/********************************************************************************
PUCK:
函数功能：设置取参数修改DI，设置跳屏标志
入口：
返回：
********************************************************************************/
void Set_Para_Modi_DI(PROTO_DI Di)
{
#ifdef DIS_PARA_JUMP_EN  
  INT8U i;
  for(i=0;i<MAX_MODI_NUM;i++)
  {
    if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
       ASSERT_FAILED();     
    if(Para_Dis_Var.Para_Modi[i]==0)
    {
      Para_Dis_Var.Para_Modi[i]=Di;
      Para_Dis_Var.Flag=1;
      SET_STRUCT_SUM(Para_Dis_Var);
      return ;
    }     
  }
#endif
}
/********************************************************************************
PUCK:
函数功能：获取参数修改DI
入口：
返回：
********************************************************************************/
PROTO_DI Get_Para_Modi_DI(void)
{
  PROTO_DI  temp=0;
  
#ifdef DIS_PARA_JUMP_EN
  INT8U i; 
  
  if(Para_Dis_Var.Flag==0)
    return 0;
    
  for(i=0;i<MAX_MODI_NUM;i++)
  {
    if(Para_Dis_Var.Para_Modi[i]!=0)
    {
      if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
        ASSERT_FAILED();
      temp=Para_Dis_Var.Para_Modi[i];
      Para_Dis_Var.Para_Modi[i]=0;
      SET_STRUCT_SUM(Para_Dis_Var);      
      break;
    }  
  }  
#endif  
  return temp;
}
/********************************************************************************
PUCK:
函数功能：获取参数修改DI
入口：
返回：
********************************************************************************/
INT8U Get_Para_Modi_Flag(void)
{
#ifdef DIS_PARA_JUMP_EN
  if(Para_Dis_Var.Flag)
  {
    if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
      ASSERT_FAILED();
    Para_Dis_Var.Flag=0;
    SET_STRUCT_SUM(Para_Dis_Var);
    return 1;
  }
#endif
    return 0; 
}
/********************************************************************************
PUCK:
函数功能：
入口：
返回：
********************************************************************************/

void LCD_Task_Monitor(void)
{
  if(Get_Sys_Status()==SYS_SLEEP)//任务在睡眠的情况下，不做任何事情 
  {
    Task_Sleep();
  }
   
  if(Get_Sys_Status()==SYS_RESUME)
  {
    if((dispmode EQ modeA && Sleep_Sec_Countr.Var>MODE_A_NUM) ||   //循显模式
       (dispmode EQ modeB && (Sec_Timer_Pub-Sleep_Sec_Countr.Var>=30)) )   //键显模式
    {

        Debug_Print("Lcd Task Enter To Sleep!");            
        Task_Sleep();         
        //醒来了，重新初始化
        dispmode = modeA;
        dispoffset = -1;   
        START_LOOP_DIS;
        Refresh_Sleep_Countr(0);    
    
    
    }
  }  
}

/*
电能表在带电运行情况下，可采用按键、插卡等操作点亮背光，背光在没有按键、插卡等操作60秒后关闭。
电能表也可采用红外通信方式点亮背光，背光在电能表2个自动轮显周期后关闭。
电能表在停电状态下，不支持背光点亮。可通过按键和非按键方式（如红外、可见光变化）等方式唤醒LCD显示。
LCD显示的关闭时间为：无按键操作时，自动循显一个周期后关闭LCD:这个需要修改代码！！！！！！！！！
有按键操作时，自按键操作结束后30s后自动关闭LCD。
*/
/********************************************************************************
PUCK:
函数功能：
入口：
返回：
********************************************************************************/
void LCD_Init_PUCK(void)  //LCD显示初始化，满足速度需要
{
  FillAllScreen();
  if(Get_Sys_Status()==SYS_NORMAL)
  {
    Init_Event_Instant_Para();
    
     Check_Loss_Volt();
     Check_Loss_Curr();
     Check_Volt_Curr_Seq();
     Check_Loss_Parse();
     Check_Neg_Curr();
     Check_Cut_Curr();
  }
   //一旦进入，说明任务唤醒或者正常模式,正常上电或者按钮红外唤醒,液晶的初始化已经在Init_ExtDevice_PUCK()完成
  if((Get_Sys_Status()==SYS_NORMAL) || (Check_Resume_Source(IRAD_RESUME|KEY_RESUME)))
  {
    Initial();
    Refresh_Sleep_Countr(0);
  }
}
/********************************************************************************
PUCK:
函数功能：
入口：
返回：
********************************************************************************/

void LCD_Dis_Switch (void)  //10ms调度一次
{
  if(Get_self_Cal_Status()) //校表状态
  {
    Cal_Dis_Proc();   
  }
  else
  {
    if(Pause_Dis_Event())   //时间的暂停显示
    {
      Key_Fast_LCD_Proc();  //键显处理
      Loop_Dis_LCD_Proc();  //循显处理
    }
    /*
    Key_Fast_LCD_Proc();  //键显处理
    Loop_Dis_LCD_Proc();  //循显处理
    */
  }
}
/********************************************************************************
PUCK:
函数功能：
入口：
返回：
********************************************************************************/

void LCD_main_LUCK (void)  //10ms调度一次
{
  LCD_Task_Monitor();   //工作模式监控
  Dis_Jump_Para();      //跳屏显示  
  LCD_Dis_Switch();
  Init_LCD_Loop();
}

/*
停电显示
－停电后，液晶显示自动关闭；
－液晶显示关闭后，可用按键或其他方式唤醒液晶显示；唤醒后如无操作，自动循环显示一遍后关闭显示；
按键显示操作结束30秒后关闭显示。
【条文解释】
停电情况发生后，电能表由电池供电（具有辅助电源的电能表除外）；为降低功耗，此工况下液晶显示应
自动关闭，但可用按键或其他非接触方式（如在不打开表箱的情况下，可通过红外抄表器发送任意的一串字符）唤
醒液晶显示或进行抄表（不要求点亮背光）。电能表被唤醒后自动循环显示一遍后，或按键显示操作结束30秒后，
液晶显示应自动关闭。
*/