
#define MeasuPulse_PUCK
#include "Pub_PUCK.h"



/**********************************************************************************
函数功能：判定脉冲规格的合法性
入口：CurPulse:当前的脉冲常数
出口：1------合法;0---------非法
**********************************************************************************/
INT8U Judge_Pulse_Legal(INT32U CurPulse)
{
  if(CurPulse EQ 0 ||(Get_Sys_Pulse()%CurPulse))
  {
    ASSERT_FAILED();
    return 0;
  }
  return 1;  
}

/**********************************************************************************
函数功能：判定脉冲规格的合法性
入口：Check_Pulse:当前的脉冲常数
出口：1------合法;0---------非法
**********************************************************************************/
INT8U Check_Pulse(void)
{
    if(Judge_Pulse_Legal(Sys_Pulse_Var.Ac_Pulse) && Judge_Pulse_Legal(Sys_Pulse_Var.Rea_Pulse))
      return 1;

    Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
    Port_Out_Pub(INTER_ID_ALARM_DIS,BEEP_MODE_100); 
    return 0;

}
/**********************************************************************************
函数功能：初始化与脉冲常数相关的变量
入口：无
出口：无
**********************************************************************************/
INT8U Get_Pulse_Para(void)
{
  INT8U Flag;
  INT8U temp[3];
    
  Flag=Read_Storage_Data_PUCK(DI_AC_PULSE,temp,3);      //有功脉冲常数---------PUCK
  Sys_Pulse_Var.Ac_Pulse=Bcd2Hex(temp,3);

#ifdef GD_VERSION
  Sys_Pulse_Var.Rea_Pulse=Sys_Pulse_Var.Ac_Pulse; //无功脉冲常数和无功的一样---------PUCK
#else
  Flag&=Read_Storage_Data_PUCK(DI_REAC_PULSE,temp,3);   //无功脉冲常数---------PUCK
  Sys_Pulse_Var.Rea_Pulse=Bcd2Hex(temp,3);
#endif
  
    
  Check_Pulse();
    
  Flag&=Read_Storage_Data_PUCK(DI_PULSE_WIDTH,temp,2);  //脉冲宽度常数---------PUCK
  Sys_Pulse_Var.Pulse_Width=Bcd2Hex(temp,2);  
  if(Sys_Pulse_Var.Ac_Pulse==0)  //有功脉冲常数不能为0
  {
    Sys_Pulse_Var.Ac_Pulse_Freq=1;
    Sys_Pulse_Var.Ac_Pulse=DEFAULT_AC_PULSE;   //设置默认的5000
    Debug_Print("Measure_Error----->Ac_Pulse Const Para Get Failed!"); 
  }
  else if(Sys_Pulse_Var.Ac_Pulse>Get_Sys_Pulse())
  {
    Sys_Pulse_Var.Ac_Pulse_Freq=1;
    Sys_Pulse_Var.Ac_Pulse=DEFAULT_AC_PULSE;   //设置默认的5000
    Debug_Print("Measure_Error----->Ac_Pulse Const Para>AC_Pulse Spec!"); 
  }
  else
    Sys_Pulse_Var.Ac_Pulse_Freq=(Get_Sys_Pulse())/(Sys_Pulse_Var.Ac_Pulse);
  
  
  if(Sys_Pulse_Var.Rea_Pulse==0) //无功脉冲常数不能为0
  {
    Sys_Pulse_Var.Reac_Pulse_Freq=1;
    Sys_Pulse_Var.Rea_Pulse=DEFAULT_REAC_PULSE;   //设置默认的2000
    Debug_Print("Measure_Error----->Reac_Pulse Const Para Get Failed!");
  }
  else if(Sys_Pulse_Var.Rea_Pulse>Get_Sys_Pulse())
  {
    Sys_Pulse_Var.Reac_Pulse_Freq=1;
    Sys_Pulse_Var.Rea_Pulse=DEFAULT_REAC_PULSE;   //设置默认的2000
    Debug_Print("Measure_Error----->Reac_Pulse Const Para>Reac_Pulse Spec!"); 
  }
  else
    Sys_Pulse_Var.Reac_Pulse_Freq=(Get_Sys_Pulse())/(Sys_Pulse_Var.Rea_Pulse);

  SET_STRUCT_SUM(Sys_Pulse_Var);
  
  return Flag;
}


/**********************************************************************************
函数功能：发总有功脉冲，正向有功脉冲，反向有功脉冲
入口：无
出口：无
**********************************************************************************/
void Send_Acpower_Pulse(void)
{
    //总有功脉冲
  A_OUT_0;
  MEASU_A_LED_0;
  
  Port_Pulse_Out(GERNAL_ID_ACPOWER,Sys_Pulse_Var.Pulse_Width);      
  Port_Pulse_Out(EXT_ID_ACPOWER,Sys_Pulse_Var.Pulse_Width);
  if(MeasuSysMode.T_FH==TF_MODE)
  {
    Port_Level_Out(EXT_ID_AP_DIR,PORT_START);
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir==0) //正有功脉冲:端口输出0
  {
    Port_Level_Out(EXT_ID_AP_DIR,PORT_START);
  }
  else   //反有功脉冲
  { 
    Port_Level_Out(EXT_ID_AP_DIR,PORT_END);     //反有功脉冲:端口输出1
  }     
   
}
/**********************************************************************************
函数功能：发总无功脉冲，正向无功脉冲，反向无功脉冲
入口：无
出口：无
**********************************************************************************/
void Send_Reacpower_Pulse(void)
{
   //总无功脉冲
  R_OUT_0;
  MEASU_R_LED_0;
  
  Port_Pulse_Out(GERNAL_ID_REACPOWER,Sys_Pulse_Var.Pulse_Width);      
  Port_Pulse_Out(EXT_ID_REACPOWER,Sys_Pulse_Var.Pulse_Width);
  if(MeasuSysMode.T_FH==TF_MODE)
  {
    Port_Level_Out(EXT_ID_RP_DIR,PORT_START);
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir==0) //正无功脉冲:端口输出0
  {
    Port_Level_Out(EXT_ID_RP_DIR,PORT_START); 
  }
  else   //反无功脉冲
  {
    Port_Level_Out(EXT_ID_RP_DIR,PORT_END);    //反有功脉冲:端口输出1
  }
}
