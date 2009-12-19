#define POWER_CTRL_C
#include "Includes.h"

#define SWITCH_POS_ACT_EN 1000

//初始化负荷控制相关内存变量
void Init_Ctrl_Ram()
{
  //负荷控制继电器状态
  mem_set((INT8U *)&Power_Ctrl_Switch, 0, sizeof(Power_Ctrl_Switch), (INT8U *)&(Power_Ctrl_Switch), sizeof(Power_Ctrl_Switch));  
  Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  SET_STRUCT_SUM(Power_Ctrl_Switch);

  //预付费负荷控制继电器状态--从Rom中读取
  //mem_set((INT8U *)&Prepaid_Power_Ctrl_Switch, 0, sizeof(Prepaid_Power_Ctrl_Switch), (INT8U *)&(Prepaid_Power_Ctrl_Switch), sizeof(Prepaid_Power_Ctrl_Switch));  
  //Prepaid_Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  //SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
  
  //预付费控制继电器状态
  mem_set((INT8U *)&Prepaid_Ctrl_Switch, 0, sizeof(Prepaid_Ctrl_Switch), (INT8U *)&(Prepaid_Ctrl_Switch), sizeof(Prepaid_Ctrl_Switch));  
  Prepaid_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  SET_STRUCT_SUM(Prepaid_Ctrl_Switch);

  //远程控制继电器状态
  //该变量从ROM中读取
}
/*
//读取预付费相关的负荷控制参数
void Read_Prepaid_Ctrl_Para_From_Rom()
{
  INT8U Temp[4];
  INT16U Len;
  
  TRACE();

  Len = Read_Storage_Data(0x0400E001, Temp, Temp, sizeof(Temp));//最大功率负荷脉冲数
  if(Len != 3)
    ASSERT_FAILED();
  
  Prepaid_Power_Ctrl_Para.Max_Power_Pulse = Bcd2Hex(Temp,3);
  
  Len = Read_Storage_Data(0x0400E002, Temp, Temp, sizeof(Temp));//最大负荷计算时间
  if(Len != 1)
    ASSERT_FAILED();
  
  Prepaid_Power_Ctrl_Para.Max_Power_Mins = Bcd2Hex_Byte(Temp[0]);
  
  Len = Read_Storage_Data(0x0400E003, Temp, Temp, sizeof(Temp));//过负荷跳闸次数门限
  if(Len != 1)
    ASSERT_FAILED();
  
  Prepaid_Power_Ctrl_Para.Max_Power_Switch_Off_Counts = Bcd2Hex_Byte(Temp[0]);
 
  SET_STRUCT_SUM(Prepaid_Power_Ctrl_Para);  
  
  Read_Storage_Data(_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, (INT8U *)&Prepaid_Power_Ctrl_Switch, \
                    (INT8U *)&Prepaid_Power_Ctrl_Switch, sizeof(Prepaid_Power_Ctrl_Switch)); 
  SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
}
*/
//读取电表运行特征字
void Read_Meter_Property_Word()
{
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_METER_RUN_STATUS, (INT8U *)&Meter_Property_Word.Word[0], \
                   (INT8U *)&Meter_Property_Word.Word[0], sizeof(Meter_Property_Word.Word[0]));
  if(Len != 1)
    ASSERT_FAILED();
  
  SET_STRUCT_SUM(Meter_Property_Word);  
}

//读取负荷控制参数
void Read_Power_Ctrl_Para_From_Rom()
{
  INT8U Temp[4];
  INT16U Len;
  
  if(0 EQ POWER_CTRL_EN) //没有负荷控制功能，则退出
    return;
  
  //读取负荷控制参数
  Len=Read_Storage_Data(0x04000E01, Temp, Temp, sizeof(Temp));//正向功率上限
  ASSERT(3 EQ Len);
  Power_Ctrl_Para.Pos_Act_Power_Limit = Bcd2Hex(Temp,3);
  
  Len=Read_Storage_Data(0x04000E02, Temp, Temp, sizeof(Temp));//反向功率上限
  ASSERT(3 EQ Len);
  Power_Ctrl_Para.Neg_Act_Power_Limit = Bcd2Hex(Temp,3);

/*  
  Len=Read_Storage_Data(0x04001402, Temp, Temp, sizeof(Temp));//合闸延时
  ASSERT(2 EQ Len);
  Relay_Delay_Para.Relay_On_Delay = (INT16U)Bcd2Hex(Temp[0], 2);
  
  Len=Read_Storage_Data(0x0E00010C, Temp, Temp, sizeof(Temp));//用户级别 
  ASSERT(1 EQ Len); 
  Power_Ctrl_Para.User_Level = Bcd2Hex_Byte(Temp[0]);
*/  
  SET_STRUCT_SUM(Power_Ctrl_Para);  
  
}

//读控制状态标志
void Read_Ctrl_Status_Flag_From_Rom()
{
  Read_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));  
  INIT_STRUCT_VAR(Ctrl_Status_Flag);
  SET_STRUCT_SUM(Ctrl_Status_Flag);
}

//读取远程控制参数
void Read_Remote_Ctrl_Para_From_Rom()
{
  //读取远程控制继电器状态
  Read_Storage_Data(_SDI_REMOTE_RELAY_STATUS, (INT8U *)&Remote_Ctrl_Switch, \
                    (INT8U *)&Remote_Ctrl_Switch,sizeof(Remote_Ctrl_Switch));
  SET_STRUCT_SUM(Remote_Ctrl_Switch);
 
  Check_Remote_Ctrl_Switch_Status();  
  
}

//读取继电器跳闸合闸延时参数
void Read_Relay_Delay_Para_From_Rom()
{
  INT8U Temp[4];
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_RELAY_OFF_DELAY, Temp, Temp, sizeof(Temp));//跳闸延时
  ASSERT(2 EQ Len);
  Relay_Delay_Para.Relay_Off_Delay = (INT16U)Bcd2Hex(Temp, 2);
  
  Relay_Delay_Para.Relay_On_Delay = 0; //合闸延时固定为0，规约中未定义  
  SET_STRUCT_SUM(Relay_Delay_Para);
}

//读取负荷控制参数，从ROM中读取
void Read_Ctrl_Para_From_Rom()
{
  TRACE();
  
  //读取继电器跳闸合闸延时参数
  Read_Relay_Delay_Para_From_Rom();   
  //读取远程控制参数
  Read_Remote_Ctrl_Para_From_Rom();
  //读取预付费负荷控制参数
  //Read_Prepaid_Ctrl_Para_From_Rom();
  //读取负荷控制参数--该功能由POWER_CTRL_EN
  Read_Power_Ctrl_Para_From_Rom();
  //读控制状态标志
  Read_Ctrl_Status_Flag_From_Rom();
  //读取电表运行特征字
  Read_Meter_Property_Word();
}

//检查控制参数的合法性
void Check_Ctrl_Para_Avail()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Mode_Word);
  Re &= CHECK_STRUCT_SUM(Relay_Delay_Para);
  //Re &= CHECK_STRUCT_SUM(Prepaid_Power_Ctrl_Para);
  //远程控制和预付费负控的控制状态作为参数存储
  Re &= CHECK_STRUCT_SUM(Remote_Ctrl_Switch); 
  Re &= CHECK_STRUCT_SUM(Meter_Property_Word);
  
  if(POWER_CTRL_EN > 0)
    Re &= CHECK_STRUCT_SUM(Power_Ctrl_Para);
  
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Read_Ctrl_Para_From_Rom();
  }
}

//检查控制相关数据的合法性
void Check_Ctrl_Data_Avail()
{
  INT8U Re;
  
  Re = 1;

  if(POWER_CTRL_EN > 0)
  {
    Re &= CHECK_STRUCT_SUM(Power_Ctrl_Switch);
  }
  
  Re &= CHECK_STRUCT_SUM(Prepaid_Ctrl_Switch);
  Re &= CHECK_STRUCT_VAR(Relay_Status);
  Re &= CHECK_STRUCT_SUM(Ctrl_Status_Flag); 
  Re &= CHECK_STRUCT_VAR(Ctrl_Status_Flag);
  if(Re EQ 0)
    ASSERT_FAILED();
}

/*
跳闸接口：
Switch_Ctrl(INT8U SwitchFlag)
SwitchFlag非0；合闸
0-------------拉闸断电

*/
/*
void Remote_Ctrl_Proc()//远程控制
{
  //INT8U Re;
  
  TRACE();
  
  Check_Remote_Ctrl_Switch_Status();
  
  if(Remote_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF) //拉闸
  {
    if(Remote_Ctrl_Switch.Switch_Status != SWITCH_OFF)
    {
      Remote_Ctrl_Switch.Switch_Status = SWITCH_OFF;
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
    }
  }
  else
  {
    if(Remote_Ctrl_Switch.Switch_Status != SWITCH_ON)
    {
      Remote_Ctrl_Switch.Switch_Status = SWITCH_ON;
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
    }
  }
}
*/
//脉冲输出中断Hook函数,用于统计脉冲输出个数,用于预付费的负荷控制
void Prepaid_Power_Ctrl_Pulse_Hook()
{/*
  INT8U Posi;
  
  Posi = Prepaid_Power_Ctrl_Pulse.Posi;
  if(Posi >= PREPAID_POWER_CTRL_UNIT_NUM)
    return;
  
  Prepaid_Power_Ctrl_Pulse.Pulse_Num[Posi] ++;
  */
}
/*
//清除预付费的负荷控制数据
void Clr_Prepaid_Power_Ctrl_Pulse_Data()
{
  DIS_ACT_PULSE_INT;
  
  mem_set((void *)&Prepaid_Power_Ctrl_Pulse, 0, sizeof(Prepaid_Power_Ctrl_Pulse),\
          (void *)&Prepaid_Power_Ctrl_Pulse, sizeof(Prepaid_Power_Ctrl_Pulse));
  INIT_STRUCT_VAR(Prepaid_Power_Ctrl_Pulse);
  
  EN_ACT_PULSE_INT;
}*/
/*
//预付费负荷控制合继电器,根据合闸判断是否清除跳闸次数
//Flag为0表示合闸，并清除跳闸次数
//非0表示在跳闸次数超限的情况下不合闸，否则合闸,不清清除跳闸次数
INT8U Prepaid_Power_Ctrl_Switch_On(INT8U Flag)
{
  if(Flag EQ 0) //不清除总跳闸次数,且在跳闸次数超限的情况下不合闸
    Prepaid_Power_Ctrl_Switch.Off_Counts = 0;
  else
  {
    if(Prepaid_Power_Ctrl_Switch.Off_Counts > Prepaid_Power_Ctrl_Para.Max_Power_Switch_Off_Counts)
    {
      Debug_Print("Prepaid Power Ctrl Switch off counts exceed!");  
      return 0;
    }     
  }

  Prepaid_Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  Prepaid_Power_Ctrl_Switch.On_Delay = 0;  
  Prepaid_Power_Ctrl_Switch.Off_Delay = 0; 
  SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
  //保存控制状态
  Write_Storage_Data(_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, (void *)&Prepaid_Power_Ctrl_Switch, sizeof(Prepaid_Power_Ctrl_Switch));
  return 1;
}

//预付费的负荷控制处理
void Prepaid_Power_Ctrl_Proc()
{
  static S_Int8U Min_Bak = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT8U i, Posi;
  INT32U Pulse_Sum = 0;

  if(Sec_Bak.Var EQ Sec_Timer_Pub) //每秒进入一次该函数
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;
  
  if(Prepaid_Power_Ctrl_Switch.Off_Delay > 0) //跳闸延时
  {
    Prepaid_Power_Ctrl_Switch.Off_Delay --;
    SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
    
    if(Prepaid_Power_Ctrl_Switch.Off_Delay EQ 0)
    {
      Prepaid_Power_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
      Prepaid_Power_Ctrl_Switch.Off_Counts ++;      
      SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);     
      //保存预付费负荷控制状态!
      Write_Storage_Data(_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, (void *)&Prepaid_Power_Ctrl_Switch, sizeof(Prepaid_Power_Ctrl_Switch));      
    }
  }
  
  //每分钟统计最大负荷脉冲时间内的脉冲数,并判断是否负荷超限
  if(Min_Bak.Var != Cur_Time1.Min)
  {  
    Min_Bak.Var = Cur_Time1.Min;
    
    DIS_ACT_PULSE_INT; //关正向脉冲输出中断
    
    Posi = Prepaid_Power_Ctrl_Pulse.Posi;  
    Prepaid_Power_Ctrl_Pulse.Posi ++;
    
    if(Prepaid_Power_Ctrl_Pulse.Posi >= PREPAID_POWER_CTRL_UNIT_NUM)
      Prepaid_Power_Ctrl_Pulse.Posi = 0;
    
    Prepaid_Power_Ctrl_Pulse.Pulse_Num[Prepaid_Power_Ctrl_Pulse.Posi] = 0;
    
    EN_ACT_PULSE_INT; //开正向脉冲输出中断
  
    if(Posi >= PREPAID_POWER_CTRL_UNIT_NUM)
    {
      ASSERT_FAILED();
      Posi = 0;
    }
    
    Pulse_Sum = 0;  
    for(i = 0; i < Prepaid_Power_Ctrl_Para.Max_Power_Mins; i ++)
    {
      Pulse_Sum += Prepaid_Power_Ctrl_Pulse.Pulse_Num[Posi];
      if(Posi EQ 0)
        Posi = PREPAID_POWER_CTRL_UNIT_NUM - 1;
      else
        Posi = Posi - 1;
    }
    
    if(Pulse_Sum >= Prepaid_Power_Ctrl_Para.Max_Power_Pulse) //超过最大负荷脉冲数
    {
       //跳闸延时处理
       if(Prepaid_Power_Ctrl_Switch.Switch_Flag != SWITCH_OFF  && Prepaid_Power_Ctrl_Switch.Off_Delay EQ 0)
       {
         Debug_Print("Prepaid Power Ctrl Relay Switch off Delay");           
         Prepaid_Power_Ctrl_Switch.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
         SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
       }  
    }
  }
}
*/
//负荷控制处理(超需量处理)---该函数应该将延时处理去掉！！！，有待进一步处理
void Power_Ctrl_Proc()
{
  static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re, i;
  INT32U Power, Demand_Limit;
  INT16U Relay_Flag, Alarm_Flag;

  if(0 EQ POWER_CTRL_EN)//模式字2的bit4表示是否有负控功能
    return;
  
  TRACE();
  
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;//每秒检查一次远程控制

  Re = CHECK_STRUCT_SUM(Mode_Word);
  if(Re EQ 0)
  {
   ASSERT_FAILED();
   Check_Data_Avail(); 
  }
  
  Re = CHECK_STRUCT_SUM(Power_Ctrl_Switch);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    mem_set((INT8U *)&Power_Ctrl_Switch, 0, sizeof(Power_Ctrl_Switch), (INT8U *)&Power_Ctrl_Switch, sizeof(Power_Ctrl_Switch)); 
    Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
    SET_STRUCT_SUM(Power_Ctrl_Switch);
  }
  
  //跳闸合闸延时处理
  if(Power_Ctrl_Switch.Off_Delay > 0)
  {
    Power_Ctrl_Switch.Off_Delay --;
    if(Power_Ctrl_Switch.Off_Delay EQ 0)
    {
      Set_Event_Instant(ID_EVENT_RELAY_OFF);//超需量跳闸事件发生
      Power_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
    }
    SET_STRUCT_SUM(Power_Ctrl_Switch);
  }
  else if(Power_Ctrl_Switch.On_Delay > 0)
  {
    Power_Ctrl_Switch.On_Delay --;
    if(Power_Ctrl_Switch.On_Delay EQ 0)
    {
      Clr_Event_Instant(ID_EVENT_RELAY_OFF);//超需量跳闸事件结束
      Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
    }
    SET_STRUCT_SUM(Power_Ctrl_Switch); 
  }
  
  Relay_Flag = SWITCH_ON;
  Alarm_Flag = ALARM_OFF;
  
  //当前正向有功需量超!
  for(i = 0; i < 2; i ++)
  {
   if(i EQ 0)
   {
     Demand_Limit = POS_ACT_DEMAND_LIMIT;
     Power = Demand_Accu.Phase_Cur[0].Pos_Active;
   }
   else
   {
     Demand_Limit = NEG_ACT_DEMAND_LIMIT;
     Power = Demand_Accu.Phase_Cur[0].Neg_Active;
   }  
   //正向有功需量超限
   if(Power > Demand_Limit)//有功需量超上限发生
   {
     if(2 EQ Power_Ctrl_Para.User_Level)//1级用户不报警不跳闸，2级用户只报警不跳闸，3级用户既报警又跳闸
     {
       Alarm_Flag = ALARM_ON;
     }
     else if(3 EQ Power_Ctrl_Para.User_Level)//用户级别2或者3才有
     {
       Alarm_Flag = ALARM_ON;
       Relay_Flag = SWITCH_OFF; //跳闸标志
     }
   }
   else//超需量恢复
   {
     if(2 EQ Power_Ctrl_Para.User_Level)//1级用户不报警不跳闸，2级用户只报警不跳闸，3级用户既报警又跳闸
     {
       //Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//报警
     }
     else if(3 EQ Power_Ctrl_Para.User_Level)//用户级别2或者3才有
     {
       //Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//报警
  
     }
   }
  }
  
  if(Relay_Flag EQ SWITCH_OFF)//当前应该跳闸
  {
    //跳闸延时处理
    if(Power_Ctrl_Switch.Switch_Flag != SWITCH_OFF  && Power_Ctrl_Switch.Off_Delay EQ 0)
    {
      Debug_Print("Prepaid Relay Switch off Delay");           
      Power_Ctrl_Switch.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
      SET_STRUCT_SUM(Power_Ctrl_Switch);
    }   
  }
  else
  {
    //合闸延时处理
    if(Power_Ctrl_Switch.Switch_Flag != SWITCH_ON  && Power_Ctrl_Switch.On_Delay EQ 0)
    {  
      Debug_Print("Prepaid Relay Switch on Delay");            
      Power_Ctrl_Switch.On_Delay = Relay_Delay_Para.Relay_On_Delay;
      SET_STRUCT_SUM(Power_Ctrl_Switch);  
    }
  }
  
  if(Alarm_Flag EQ ALARM_ON)
    Set_Event_Instant(ID_EVENT_DEMAND_ALARM);//报警 
  else
    Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//报警清除
    
}

//获取预付费控制继电器状态
INT16U Get_Prepaid_Relay_Status()
{
  return Prepaid_Ctrl_Switch.Switch_Flag;  
}

//预付费控制继电器
void Prepaid_Switch_Ctrl(INT16U Switch_Flag)
{
  //合闸
  if(Switch_Flag EQ SWITCH_ON)
  {
    if(Prepaid_Ctrl_Switch.Switch_Flag != SWITCH_ON)
    {
      Prepaid_Ctrl_Switch.Switch_Flag = SWITCH_ON;
      SET_STRUCT_SUM(Prepaid_Ctrl_Switch);
      
      //Clr_Event_Instant(ID_EVENT_RELAY_OFF);//拉闸事件结束
      //Set_Event_Instant(ID_EVENT_RELAY_ON); //合闸事件发生      
    }
  }
  else if(Switch_Flag EQ SWITCH_OFF)
  {
    if(Prepaid_Ctrl_Switch.Switch_Flag != SWITCH_OFF)
    {
      Prepaid_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
      SET_STRUCT_SUM(Prepaid_Ctrl_Switch);
      
      //Clr_Event_Instant(ID_EVENT_RELAY_ON);//拉闸事件发生
      //Set_Event_Instant(ID_EVENT_RELAY_OFF); //合闸事件结束      
    }     
  }
  else
    ASSERT_FAILED();
}

//预付费报警处理
void Prepaid_Alarm_Proc(INT8U Type)
{
  if(PREPAID_EN EQ 0)
    return;
  
  if(PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //如果是远程预付费，不跳闸也不报警
    return;
  
  if(Type EQ ALARM_ON) //预付费报警
    Prepaid_Ctrl_Switch.Alarm_Flag = ALARM_ON;
  else if(Type EQ ALARM_OFF)
    Prepaid_Ctrl_Switch.Alarm_Flag = ALARM_OFF;
  else
    ASSERT_FAILED();
  
  SET_STRUCT_SUM(Prepaid_Ctrl_Switch);
  
}

//预付费的报警和跳闸处理
void Prepaid_Ctrl_Proc(INT8U Type)
{
  INT8U Card_Switch_On_Flag;
  
  if(PREPAID_EN EQ 0)
    return;

  if(PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //如果是远程预付费，不跳闸也不报警
    return;
  
  Card_Switch_On_Flag = Get_Card_Switch_On_Flag();
  switch(Type)
  {
  case PREPAID_ENERGY_ENOUGH:
  case PREPAID_MONEY_ENOUGH:
    Prepaid_Alarm_Proc(ALARM_OFF);
    Prepaid_Switch_Ctrl(SWITCH_ON);
    break;
  //剩余电费、电量小于门限1
  case PREPAID_ENERGY_LEFT1:
  case PREPAID_MONEY_LEFT1:
   if(PREPAID_WARN_EN) //声报警打开
   {
     if(PREPAID_LIMIT1_WARN_EN) //低于门限1
       Prepaid_Alarm_Proc(ALARM_ON);
     else
       Prepaid_Alarm_Proc(ALARM_OFF);//Clr_Event_Instant(ID_PAY_ALARM);
   }
   Prepaid_Switch_Ctrl(SWITCH_ON);
   break;
  //剩余电量、电费小于门限2
  case PREPAID_ENERGY_LEFT2:
  case PREPAID_MONEY_LEFT2:
   if(PREPAID_WARN_EN) //声报警打开
   {
     if(PREPAID_LIMIT2_WARN_EN  && Card_Switch_On_Flag EQ 0) //低于门限2
       Prepaid_Alarm_Proc(ALARM_ON);//Set_Event_Instant(ID_PAY_ALARM);
     else
       Prepaid_Alarm_Proc(ALARM_OFF);//Clr_Event_Instant(ID_PAY_ALARM);
   }
  
   //跳闸控制
   if(PREPAID_LIMIT2_SWITCH_EN && Card_Switch_On_Flag EQ 0) //低于门限2
   {
     Prepaid_Alarm_Proc(ALARM_OFF); //跳闸则应该关掉报警
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   }
   else
     Prepaid_Switch_Ctrl(SWITCH_ON);
   break;
  //剩余电量、电费小于0
  case PREPAID_ENERGY_ZERO:
  case PREPAID_MONEY_ZERO:
   if(PREPAID_WARN_EN) //声报警打开
   {
     if(PREPAID_ZERO_WARN_EN  && Card_Switch_On_Flag EQ 0) //低于0
       Prepaid_Alarm_Proc(ALARM_ON);//Set_Event_Instant(ID_PAY_ALARM);
     else
       Prepaid_Alarm_Proc(ALARM_OFF);//Clr_Event_Instant(ID_PAY_ALARM);
   }
  
   if(PREPAID_ZERO_SWITCH_EN && Card_Switch_On_Flag EQ 0) //低于0
   {
     Prepaid_Alarm_Proc(ALARM_OFF); //跳闸则应该关掉报警
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   }
   else
     Prepaid_Switch_Ctrl(SWITCH_ON);
    break;
    
  //超透支电量、电费
  case PREPAID_ENERGY_OVERDRAFT:
  case PREPAID_MONEY_OVERDRAFT:
     Prepaid_Alarm_Proc(ALARM_ON);  //关掉报警，直接跳闸
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   break;     
  case PREPAID_MONEY_SWITCH_LIMIT://购电金额低于合闸门限
     Prepaid_Alarm_Proc(ALARM_OFF);  //关掉报警，直接跳闸
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   break;   
  }
}

//保存远程控制报警和跳闸的命令状态
void Save_Remote_Ctrl_Switch_Flag()
{
   Write_Storage_Data(_SDI_REMOTE_RELAY_STATUS, (INT8U *)&Remote_Ctrl_Switch, sizeof(Remote_Ctrl_Switch));   
}

INT8U Set_Port_Output_Ctrl(INT8U Ctrl)
{
  INT8U Re;
  
  if(Ctrl EQ 0x00 || Ctrl EQ 0x01 || Ctrl EQ 0x02)
  {  
    Re = Write_Storage_Data(SDI_OUTPUT_MODE, &Ctrl, 1); 
    Set_Para_Modify(SDI_OUTPUT_MODE);
    return Re;
  }
  else
    return 0;
  
}

//检查是否有手动合闸
void Check_Hand_Switch_On()
{
  if(Relay_Status.Switch_Status EQ SWITCH_OFF)
  {
    if(Judge_RelayOn_Key())
    {
      Set_Hand_Switch_On_Flag(0);  //设置手动合闸标志
    }
  }
}

//手动插卡合闸
void Card_Switch_On()
{
  if(Relay_Status.Switch_Status EQ SWITCH_OFF) //当前在预付费跳闸状态(欠费或者超负荷)
  {
    if(Ctrl_Status_Flag.Card_Switch_On_Flag != 1 || Ctrl_Status_Flag.Hand_Switch_On_Flag != 0)
    {
      Ctrl_Status_Flag.Card_Switch_On_Flag = 1;
      Ctrl_Status_Flag.Hand_Switch_On_Flag = 0;//是手动合闸状态
      
      SET_STRUCT_SUM(Ctrl_Status_Flag);
      Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));
    }  
  }
}

//远程控制继电器
INT8U Remote_Protocol_Ctrl(INT8U *pData)
{
  INT8U Switch_Flag;
  INT8U Temp[6];
  
  Temp[0] = Cur_Time1.Sec;
  Temp[1] = Cur_Time1.Min;
  Temp[2] = Cur_Time1.Hour;
  Temp[3] = Cur_Time1.Date;
  Temp[4] = Cur_Time1.Month;
  Temp[5] = Cur_Time1.Year;
  
  Switch_Flag = *pData;
  //当前时间在命令截至时间之后
  if(Cmp_Array_Time(pData + 2, Temp, sizeof(Temp)) EQ TIME_AFT)
  {
    if(Switch_Flag EQ SWITCH_ON) //允许合闸
    {
      Remote_Ctrl_Switch.Switch_Flag = SWITCH_ON; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Switch On!");
      
      Save_Remote_Ctrl_Switch_Flag(); 
      
      return 1;
    }
    else if(Switch_Flag EQ SWITCH_OFF) //跳闸
    {
      if(Remote_Ctrl_Switch.Maintain_Flag EQ MAINTAIN_ON) //需要先解除保电状态
        return 0;
      
      Remote_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
       
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Switch Off!");
      
      Save_Remote_Ctrl_Switch_Flag();
/*      
  /////////////收到脉冲跳闸命令,而且当前已经是跳闸状态，则重新发一个跳闸脉冲,电平方式不需要这样------------------------------
  /////////////如果当前不是命令跳闸状态，则跳闸处理流程会处理跳闸，不需要再这里发脉冲      
      if(EXT_SWITCH_MODE EQ 1 && Relay_Status.Switch_Status EQ SWITCH_OFF)
      {
        Excute_Toogle(0);  //输出一个跳闸脉冲  
      }
  //////////////////////////////////////////  
*/          
      return 1;
    }
    else if(Switch_Flag EQ MAINTAIN_ON) //保电
    {
      Set_Hand_Switch_On_Flag(0); //设置手动合闸标志
      Remote_Ctrl_Switch.Maintain_Flag = MAINTAIN_ON; 
      Remote_Ctrl_Switch.Switch_Flag = SWITCH_ON;    //允许合闸
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Maintain On!");
      
      Save_Remote_Ctrl_Switch_Flag();     
      return 1;
    }
    else if(Switch_Flag EQ MAINTAIN_OFF) //保电解除
    {
      Remote_Ctrl_Switch.Maintain_Flag = MAINTAIN_OFF; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Maintain Off!");
      
      Save_Remote_Ctrl_Switch_Flag();     
      return 1;
    }
    else if(Switch_Flag EQ ALARM_ON) //报警
    {
      Remote_Ctrl_Switch.Alarm_Flag = ALARM_ON; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Save_Remote_Ctrl_Switch_Flag();
      return 1;       
    }
    else if(Switch_Flag EQ ALARM_OFF) //报警解除
    {
      Remote_Ctrl_Switch.Alarm_Flag = ALARM_OFF; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch); 
      Save_Remote_Ctrl_Switch_Flag();
      return 1;       
    } 
  }
    
  SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);  
  return 0;
  
}

//检查远程控制继电器状态
void Check_Remote_Ctrl_Switch_Status()
{
  if((Remote_Ctrl_Switch.Switch_Flag != SWITCH_ON &&
      Remote_Ctrl_Switch.Switch_Flag != SWITCH_OFF) ||\
      CHECK_STRUCT_SUM(Remote_Ctrl_Switch) EQ 0)
  {
    ASSERT_FAILED();
    Remote_Ctrl_Switch.Switch_Flag = SWITCH_ON;
    SET_STRUCT_SUM(Remote_Ctrl_Switch);
  }
  
}

//脉冲开关控制
void Pulse_Switch_Ctrl(INT8U Switch_Flag)
{
  static S_Int8U Last_Switch_Status = {CHK_BYTE, SWITCH_ON, CHK_BYTE};
  static S_Int32U Pos_Act_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT32U Pos_Act_Eng;
  INT8U Re;

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Last_Switch_Status);
  Re &= CHECK_STRUCT_VAR(Pos_Act_Bak);
 
  if(Re EQ 0)
    ASSERT_FAILED();  
  
  if(Switch_Flag EQ SWITCH_OFF) //跳闸
  {
    Pos_Act_Eng = Get_Pos_Act_Eng();
    
    if(Last_Switch_Status.Var != SWITCH_OFF) //状态发生了变化
    {
      Last_Switch_Status.Var = Switch_Flag;
      Debug_Print("Pulse_Switch_Off");
      Pos_Act_Bak.Var = Pos_Act_Eng; //获取当前正向有功总电能
      Excute_Toogle(0);  //输出一个跳闸脉冲
    }  
    
    //跳闸后为了防止跳闸没有成功，每走1kwh的电，跳闸一次
    if(Pos_Act_Eng > Pos_Act_Bak.Var &&\
      (Pos_Act_Eng - Pos_Act_Bak.Var) >= SWITCH_POS_ACT_EN)
    {
      Debug_Print("Pulse_Switch_Off again");
      Pos_Act_Bak.Var = Pos_Act_Eng;  
      Excute_Toogle(0);  //输出一个跳闸脉冲         
    }
  }  
  Last_Switch_Status.Var = Switch_Flag;
  /*
  static INT8U Sec = 0;
  
  Sec++;
  if(Sec >=3)
  {
    Sec = 0;
    Excute_Toogle(0);
  }
  */
}

//读取与预跳闸报警状态与继电器命令状态以及继电器状态
//第7位表示预跳闸报警状态
//第6位表示继电器命令状态
//第4位表示继电器状态
INT8U Get_Alarm_Relay_Status()
{
  INT8U Byte;
  
  Byte = 0;
  
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  {
     if((PREPAID_MODE EQ PREPAID_MONEY && Cur_Energy.Prepaid_Info.Left_Energy / 10 < Prepaid_Para.Warn_Money1) ||\
        (PREPAID_MODE EQ PREPAID_ENG && Cur_Energy.Prepaid_Info.Left_Energy / 10 < Prepaid_Para.Warn_Energy1))
     {
       SET_BIT(Byte, 7); //预跳闸报警
     }
  }
  
  if(Relay_Status.Off_Delay > 0 || Relay_Status.Switch_Status EQ SWITCH_OFF)
  {
    SET_BIT(Byte, 6); //继电器命令状态
  }
  
  if(Relay_Status.Switch_Status EQ SWITCH_OFF)
  {
    SET_BIT(Byte, 4); //继电器状态 
  }
  
  return Byte;
}

//检查继电器状态
//ALLOW_SWITCH_ON //拉闸状态下允许合闸
//SWITCH_DELAY //拉闸延时阶段
//SWITCH_OFF 拉闸且不允许合闸
//SWITCH_ON 合闸状态
INT8U Get_Relay_Status()
{
  INT8U Cause;
  INT8U Re;

  if(Relay_Status.Off_Delay > 0) //跳闸延时阶段
  {
    return SWITCH_DELAY; 
  }  
  else if(Relay_Status.Switch_Status EQ SWITCH_OFF)//拉闸状态
  {
    Re = Check_Switch_Status(&Cause);
    if(Re EQ SWITCH_ON)
      return ALLOW_SWITCH_ON;
    else
    {
      if(PREPAID_EN > 0)
      {
        if(Cause EQ S_OFF_PREPAID) //如果是预付费跳闸
        {
          Re = Get_Prepaid_Status();
          if(Re EQ PREPAID_MONEY_LEFT2 || Re EQ PREPAID_MONEY_ZERO) //在没有超透支门限的情况下，在报警门限2可以手动合闸
            return ALLOW_SWITCH_ON;
        }
      }
      return SWITCH_OFF;
    }
  }
  else
    return SWITCH_ON;
}

void Set_Relay_Status(INT8U Status, INT8U Cause)
{
  if(Relay_Status.Switch_Status != Status)
  {
    DIS_PD_INT;
    Relay_Status.Switch_Status = Status;
    Relay_Status.Switch_Cause = Cause;
    EN_PD_INT;
    
    if(Status EQ SWITCH_ON)
      Event_Data_Proc(ID_EVENT_RELAY_ON, EVENT_OCCUR);
    else
      Event_Data_Proc(ID_EVENT_RELAY_OFF, EVENT_OCCUR);
  }
  
  DIS_PD_INT;
  Relay_Status.Switch_Cause = Cause; 
  EN_PD_INT;
}

void Card_Test_Relay() //插卡测试继电器状态，工Heguoquan调用
{
  Card_Test_Relay_Status.Flag = CARD_TESTING;
  Card_Test_Relay_Status.Delay = CARD_TESTING_DELAY; 
}

//继电器反向
void Relay_Reverse()
{
  if(Relay_Status.Switch_Status EQ SWITCH_ON)
  {
    Set_Relay_Status(SWITCH_OFF, S_OFF_PREPAID);
    Excute_Toogle(0);
  }
  else
  {
    Set_Relay_Status(SWITCH_ON, S_OFF_PREPAID);
    Excute_Toogle(1);          
  }  
  
}

//#pragma optimize=none
//跳闸直接控制
void Switch_Ctrl(INT8U Switch_Flag, INT8U Cause)
{
  //static S_Int8U Flag = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};
  static S_Int32U Sec_Bak0 = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};  
  static S_Int8U Counts = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Sec_Bak0);  
  Re &= CHECK_STRUCT_VAR(Counts);
  Re &= CHECK_STRUCT_VAR(Relay_Status);
  Re &= CHECK_STRUCT_VAR(Card_Test_Relay_Status);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  if(Card_Test_Relay_Status.Flag EQ CARD_TESTING) //当前在继电器测试状态
  {
    if(Sec_Bak.Var EQ Sec_Timer_Pub)
      return;

    Sec_Bak.Var = Sec_Timer_Pub;
    if(Card_Test_Relay_Status.Delay EQ CARD_TESTING_DELAY)
    {
      Card_Test_Relay_Status.Delay --;
      Relay_Reverse();
      return;
    }
    else if(Card_Test_Relay_Status.Delay > 0)
    {
      Card_Test_Relay_Status.Delay --;
      return;
    }
    else
    {
      Card_Test_Relay_Status.Flag = CARD_TESTED;
      Relay_Reverse();
      return;        
    }
  }
/*  
  if(Flag.Var EQ 0xFF) //第一次进入
  {
    Flag.Var = 0;
    if(Status EQ SWITCH_OFF) //上电后就立即进入跳闸状态,说明前一次掉电前就已经是欠费状态
    {
      Relay_Status.Switch_Status = SWITCH_OFF;
      Relay_Status.Switch_Cause = Cause;
      Clr_Event_Instant(ID_EVENT_RELAY_ON); //合闸事件结束      
      Set_Event_Instant(ID_EVENT_RELAY_OFF);//拉闸事件发生      
    }
  }
 */
  
  if(Switch_Flag EQ SWITCH_OFF) //拉闸!
  {
    Set_Hand_Switch_On_Flag(NEED_HAND_SWITCH_ON_FLAG); //需要手动合闸 
    if(Relay_Status.Switch_Status != SWITCH_OFF && Relay_Status.Off_Delay EQ 0)
    {
      if(Cause EQ S_OFF_PREPAID)
        Relay_Status.Off_Delay = 0;
      else
        Relay_Status.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
        
      Counts.Var = 0;
      //Relay_Status.On_Delay = 0;
      if(Relay_Status.Off_Delay EQ 0) //如果设定延时为0，马上拉闸
      {       
        //Relay_Status.Switch_Status = SWITCH_OFF;
        //Relay_Status.Switch_Cause = Cause;
        Set_Relay_Status(SWITCH_OFF, Cause);
        //Clr_Event_Instant(ID_EVENT_RELAY_ON); //合闸事件结束      
        //Set_Event_Instant(ID_EVENT_RELAY_OFF);//拉闸事件发生  
      } 
    }
  }
  else //允许合闸
  {
    if(Get_Hand_Switch_On_Flag() != NEED_HAND_SWITCH_ON_FLAG) //已经手动合闸?
    {
      Relay_Status.Off_Delay = 0;
      //Relay_Status.Switch_Status = SWITCH_ON;
      //Relay_Status.Switch_Cause = Cause;
      Set_Relay_Status(SWITCH_ON, Cause);
      //Clr_Event_Instant(ID_EVENT_RELAY_OFF);//拉闸事件结束
      //Set_Event_Instant(ID_EVENT_RELAY_ON); //合闸事件发生      
    }
    else //还没有手动合闸则保持拉闸状态
    {
      if(Relay_Status.Switch_Status != SWITCH_OFF && Relay_Status.Off_Delay EQ 0)
      {
        if(Cause EQ S_OFF_PREPAID)
          Relay_Status.Off_Delay = 0;
        else
          Relay_Status.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
        
        Counts.Var = 0;

        if(Relay_Status.Off_Delay EQ 0) //如果设定延时为0，马上拉闸
        {       
          Set_Relay_Status(SWITCH_OFF, Cause);
          //Clr_Event_Instant(ID_EVENT_RELAY_ON); //合闸事件结束      
          //Set_Event_Instant(ID_EVENT_RELAY_OFF);//拉闸事件发生  
        } 
      }      
    }
  }
  
  if(Sec_Bak.Var != Sec_Timer_Pub)
  {
    Counts.Var ++;
    Sec_Bak.Var = Sec_Timer_Pub;
  }
  
  if(Counts.Var >= 60) //时间按跨了一份钟
  {
    Counts.Var = 0;
    
    if(Relay_Status.Off_Delay > 0) //跳闸
    {
      Relay_Status.Off_Delay--;
      if(Relay_Status.Off_Delay EQ 0)
      {
        //Relay_Status.Switch_Status = SWITCH_OFF;
        //Relay_Status.Switch_Cause = Cause;
        Set_Relay_Status(SWITCH_OFF, Cause);
        //Clr_Event_Instant(ID_EVENT_RELAY_ON); //合闸事件结束      
        //Set_Event_Instant(ID_EVENT_RELAY_OFF);//拉闸事件发生
        
        Set_Hand_Switch_On_Flag(NEED_HAND_SWITCH_ON_FLAG); //需要手动合闸        
      }
    }
    
  }
  
  //if(EXT_SWITCH_MODE EQ 0) //电平方式控制
  //{
    if(SWITCH_ON EQ Relay_Status.Switch_Status) //合闸 
      Excute_Toogle(1);//EXT_SWITCH_MODE
    else //拉闸
    {
      if(Relay_Status.Switch_Status != SWITCH_OFF)
        ASSERT_FAILED();
      
      Excute_Toogle(0);
    }
  //}
    /*
  else //脉冲方式
  {
    Pulse_Switch_Ctrl(Relay_Status.Switch_Status);
  }*/

}

//获取当前跳闸状态
INT8U Get_Switch_Status()
{
 return Relay_Status.Switch_Status;  
}

//检查当前应该的拉合闸状态,返回拉合闸状态，
//*pCause表示拉合闸原因
INT8U Check_Switch_Status(INT8U *pCause)
{
  if(Remote_Ctrl_Switch.Maintain_Flag EQ MAINTAIN_ON) //保电！优先级最高
  {
    //在命令有效时间以前进行保电
    *pCause = S_ON_MAINTAIN; //合闸原因
    return SWITCH_ON;
  }
  
  //本地预付费且预付费跳闸表示为跳闸
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL &&  Prepaid_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF)
  {
    //if(PREPAID_EN > 0)
    {
      *pCause = S_OFF_PREPAID; //拉闸原因
      return SWITCH_OFF;
    }
  }
  else if(Remote_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF) //远程控制
  {
    *pCause = S_OFF_REMOTE_CMD;    
    return SWITCH_OFF;
  }
  else if(POWER_CTRL_EN > 0 && Power_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF) //负荷控制
  {
    //if(POWER_CTRL_EN>0)
    {
      *pCause = S_OFF_PWR_CTRL;      
      return SWITCH_OFF;
    }
  }

  //else //合闸
  //{      
    *pCause = Relay_Status.Switch_Cause;//S_ON_OTHER;
    return SWITCH_ON;   
  //} 
    
}

INT8U Check_Alarm_Status()
{
  //远程报警处理 
  if(Remote_Ctrl_Switch.Alarm_Flag EQ ALARM_ON)
    return ALARM_ON;
  
  if(Relay_Status.Off_Delay > 0) //跳闸延时阶段
    return ALARM_ON;
  
  //当前不在保电状态，且是本地预付费、预付费报警，则报警
  if(Remote_Ctrl_Switch.Maintain_Flag != MAINTAIN_ON &&\
    PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL &&\
    Prepaid_Ctrl_Switch.Alarm_Flag EQ ALARM_ON)
    return ALARM_ON; 
  
  return ALARM_OFF;
}

//设置手动合闸标志
void Set_Hand_Switch_On_Flag(INT8U Flag)
{
  INT8U Re;
  
  Re = CHECK_STRUCT_SUM(Ctrl_Status_Flag);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
    
  if(Flag != Get_Hand_Switch_On_Flag())
  { 
    Ctrl_Status_Flag.Hand_Switch_On_Flag = Flag;
    SET_STRUCT_SUM(Ctrl_Status_Flag);
    
    Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));
  }
}

//读取预付费跳闸后是否插卡标志,如果插过了返回1，否则返回0，插卡可以保持用电到透支电量
INT8U Get_Card_Switch_On_Flag()
{
  return Ctrl_Status_Flag.Card_Switch_On_Flag;  
}

//设置手动允许合闸标志,返回0表示已经手动合闸，1表示还没有手动合闸
INT8U Get_Hand_Switch_On_Flag()
{
  return Ctrl_Status_Flag.Hand_Switch_On_Flag; 
}

//在跳闸情况下，重新插卡可恢复供电
//Card_Type为0表示高权限的卡，可用来合闸，同时可清除负控拉闸次数
//Card_Type为1表示用户卡，在负荷跳闸次数超限的情况下不能合闸
INT8U Prepaid_Insert_Card(INT8U Card_Type)
{
  //INT8U Cause;
  
  if(Card_Type EQ 0)// || Card_Type EQ 1)
  {
    if(Relay_Status.Switch_Status EQ SWITCH_OFF) //当前在预付费跳闸状态(欠费或者超负荷)
    {
      Card_Switch_On();
      return 1;
    }
  }
  else
  {
    if(Relay_Status.Switch_Status EQ SWITCH_OFF)
    {
      Set_Hand_Switch_On_Flag(0);  //设置手动合闸标志
      return 1;
    }
  }
  
  return 0;
}

//报警的总控制
void Alarm_Ctrl(INT8U Status)
{
  if(Status EQ ALARM_ON)
    Set_Event_Instant(ID_PAY_ALARM); //合闸事件发生 
  else
    Clr_Event_Instant(ID_PAY_ALARM);//拉闸事件结束    
}

//跳闸继电器总的控制
void Switch_Ctrl_Proc()
{
  //INT8U Re;
  INT8U Status;
  INT8U Cause;

  Check_Hand_Switch_On(); //检查手动合闸标志,插卡合闸的处理在插卡时调用
  
  //检查跳闸状态,得到当前应该的跳闸状态和原因
  Status = Check_Switch_Status((INT8U *)&Cause);
  //对跳闸合闸等进行延时处理
  Switch_Ctrl(Status,Cause);
  
  //报警总控制
  Status = Check_Alarm_Status();
  Alarm_Ctrl(Status);
}
#undef POWER_CTRL_C
