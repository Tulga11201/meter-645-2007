
#define MeasuPulse_PUCK
#include "Pub_PUCK.h"



/**********************************************************************************
�������ܣ��ж�������ĺϷ���
��ڣ�CurPulse:��ǰ�����峣��
���ڣ�1------�Ϸ�;0---------�Ƿ�
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
�������ܣ��ж�������ĺϷ���
��ڣ�Check_Pulse:��ǰ�����峣��
���ڣ�1------�Ϸ�;0---------�Ƿ�
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
�������ܣ���ʼ�������峣����صı���
��ڣ���
���ڣ���
**********************************************************************************/
INT8U Get_Pulse_Para(void)
{
  INT8U Flag;
  INT8U temp[3];
    
  Flag=Read_Storage_Data_PUCK(DI_AC_PULSE,temp,3);      //�й����峣��---------PUCK
  Sys_Pulse_Var.Ac_Pulse=Bcd2Hex(temp,3);

#ifdef GD_VERSION
  Sys_Pulse_Var.Rea_Pulse=Sys_Pulse_Var.Ac_Pulse; //�޹����峣�����޹���һ��---------PUCK
#else
  Flag&=Read_Storage_Data_PUCK(DI_REAC_PULSE,temp,3);   //�޹����峣��---------PUCK
  Sys_Pulse_Var.Rea_Pulse=Bcd2Hex(temp,3);
#endif
  
    
  Check_Pulse();
    
  Flag&=Read_Storage_Data_PUCK(DI_PULSE_WIDTH,temp,2);  //�����ȳ���---------PUCK
  Sys_Pulse_Var.Pulse_Width=Bcd2Hex(temp,2);  
  if(Sys_Pulse_Var.Ac_Pulse==0)  //�й����峣������Ϊ0
  {
    Sys_Pulse_Var.Ac_Pulse_Freq=1;
    Sys_Pulse_Var.Ac_Pulse=DEFAULT_AC_PULSE;   //����Ĭ�ϵ�5000
    Debug_Print("Measure_Error----->Ac_Pulse Const Para Get Failed!"); 
  }
  else if(Sys_Pulse_Var.Ac_Pulse>Get_Sys_Pulse())
  {
    Sys_Pulse_Var.Ac_Pulse_Freq=1;
    Sys_Pulse_Var.Ac_Pulse=DEFAULT_AC_PULSE;   //����Ĭ�ϵ�5000
    Debug_Print("Measure_Error----->Ac_Pulse Const Para>AC_Pulse Spec!"); 
  }
  else
    Sys_Pulse_Var.Ac_Pulse_Freq=(Get_Sys_Pulse())/(Sys_Pulse_Var.Ac_Pulse);
  
  
  if(Sys_Pulse_Var.Rea_Pulse==0) //�޹����峣������Ϊ0
  {
    Sys_Pulse_Var.Reac_Pulse_Freq=1;
    Sys_Pulse_Var.Rea_Pulse=DEFAULT_REAC_PULSE;   //����Ĭ�ϵ�2000
    Debug_Print("Measure_Error----->Reac_Pulse Const Para Get Failed!");
  }
  else if(Sys_Pulse_Var.Rea_Pulse>Get_Sys_Pulse())
  {
    Sys_Pulse_Var.Reac_Pulse_Freq=1;
    Sys_Pulse_Var.Rea_Pulse=DEFAULT_REAC_PULSE;   //����Ĭ�ϵ�2000
    Debug_Print("Measure_Error----->Reac_Pulse Const Para>Reac_Pulse Spec!"); 
  }
  else
    Sys_Pulse_Var.Reac_Pulse_Freq=(Get_Sys_Pulse())/(Sys_Pulse_Var.Rea_Pulse);

  SET_STRUCT_SUM(Sys_Pulse_Var);
  
  return Flag;
}


/**********************************************************************************
�������ܣ������й����壬�����й����壬�����й�����
��ڣ���
���ڣ���
**********************************************************************************/
void Send_Acpower_Pulse(void)
{
    //���й�����
  A_OUT_0;
  MEASU_A_LED_0;
  
  Port_Pulse_Out(GERNAL_ID_ACPOWER,Sys_Pulse_Var.Pulse_Width);      
  Port_Pulse_Out(EXT_ID_ACPOWER,Sys_Pulse_Var.Pulse_Width);
  if(MeasuSysMode.T_FH==TF_MODE)
  {
    Port_Level_Out(EXT_ID_AP_DIR,PORT_START);
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir==0) //���й�����:�˿����0
  {
    Port_Level_Out(EXT_ID_AP_DIR,PORT_START);
  }
  else   //���й�����
  { 
    Port_Level_Out(EXT_ID_AP_DIR,PORT_END);     //���й�����:�˿����1
  }     
   
}
/**********************************************************************************
�������ܣ������޹����壬�����޹����壬�����޹�����
��ڣ���
���ڣ���
**********************************************************************************/
void Send_Reacpower_Pulse(void)
{
   //���޹�����
  R_OUT_0;
  MEASU_R_LED_0;
  
  Port_Pulse_Out(GERNAL_ID_REACPOWER,Sys_Pulse_Var.Pulse_Width);      
  Port_Pulse_Out(EXT_ID_REACPOWER,Sys_Pulse_Var.Pulse_Width);
  if(MeasuSysMode.T_FH==TF_MODE)
  {
    Port_Level_Out(EXT_ID_RP_DIR,PORT_START);
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir==0) //���޹�����:�˿����0
  {
    Port_Level_Out(EXT_ID_RP_DIR,PORT_START); 
  }
  else   //���޹�����
  {
    Port_Level_Out(EXT_ID_RP_DIR,PORT_END);    //���й�����:�˿����1
  }
}
