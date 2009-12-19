#define POWER_CTRL_C
#include "Includes.h"

#define SWITCH_POS_ACT_EN 1000

//��ʼ�����ɿ�������ڴ����
void Init_Ctrl_Ram()
{
  //���ɿ��Ƽ̵���״̬
  mem_set((INT8U *)&Power_Ctrl_Switch, 0, sizeof(Power_Ctrl_Switch), (INT8U *)&(Power_Ctrl_Switch), sizeof(Power_Ctrl_Switch));  
  Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  SET_STRUCT_SUM(Power_Ctrl_Switch);

  //Ԥ���Ѹ��ɿ��Ƽ̵���״̬--��Rom�ж�ȡ
  //mem_set((INT8U *)&Prepaid_Power_Ctrl_Switch, 0, sizeof(Prepaid_Power_Ctrl_Switch), (INT8U *)&(Prepaid_Power_Ctrl_Switch), sizeof(Prepaid_Power_Ctrl_Switch));  
  //Prepaid_Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  //SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
  
  //Ԥ���ѿ��Ƽ̵���״̬
  mem_set((INT8U *)&Prepaid_Ctrl_Switch, 0, sizeof(Prepaid_Ctrl_Switch), (INT8U *)&(Prepaid_Ctrl_Switch), sizeof(Prepaid_Ctrl_Switch));  
  Prepaid_Ctrl_Switch.Switch_Flag = SWITCH_ON;
  SET_STRUCT_SUM(Prepaid_Ctrl_Switch);

  //Զ�̿��Ƽ̵���״̬
  //�ñ�����ROM�ж�ȡ
}
/*
//��ȡԤ������صĸ��ɿ��Ʋ���
void Read_Prepaid_Ctrl_Para_From_Rom()
{
  INT8U Temp[4];
  INT16U Len;
  
  TRACE();

  Len = Read_Storage_Data(0x0400E001, Temp, Temp, sizeof(Temp));//����ʸ���������
  if(Len != 3)
    ASSERT_FAILED();
  
  Prepaid_Power_Ctrl_Para.Max_Power_Pulse = Bcd2Hex(Temp,3);
  
  Len = Read_Storage_Data(0x0400E002, Temp, Temp, sizeof(Temp));//��󸺺ɼ���ʱ��
  if(Len != 1)
    ASSERT_FAILED();
  
  Prepaid_Power_Ctrl_Para.Max_Power_Mins = Bcd2Hex_Byte(Temp[0]);
  
  Len = Read_Storage_Data(0x0400E003, Temp, Temp, sizeof(Temp));//��������բ��������
  if(Len != 1)
    ASSERT_FAILED();
  
  Prepaid_Power_Ctrl_Para.Max_Power_Switch_Off_Counts = Bcd2Hex_Byte(Temp[0]);
 
  SET_STRUCT_SUM(Prepaid_Power_Ctrl_Para);  
  
  Read_Storage_Data(_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, (INT8U *)&Prepaid_Power_Ctrl_Switch, \
                    (INT8U *)&Prepaid_Power_Ctrl_Switch, sizeof(Prepaid_Power_Ctrl_Switch)); 
  SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
}
*/
//��ȡ�������������
void Read_Meter_Property_Word()
{
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_METER_RUN_STATUS, (INT8U *)&Meter_Property_Word.Word[0], \
                   (INT8U *)&Meter_Property_Word.Word[0], sizeof(Meter_Property_Word.Word[0]));
  if(Len != 1)
    ASSERT_FAILED();
  
  SET_STRUCT_SUM(Meter_Property_Word);  
}

//��ȡ���ɿ��Ʋ���
void Read_Power_Ctrl_Para_From_Rom()
{
  INT8U Temp[4];
  INT16U Len;
  
  if(0 EQ POWER_CTRL_EN) //û�и��ɿ��ƹ��ܣ����˳�
    return;
  
  //��ȡ���ɿ��Ʋ���
  Len=Read_Storage_Data(0x04000E01, Temp, Temp, sizeof(Temp));//����������
  ASSERT(3 EQ Len);
  Power_Ctrl_Para.Pos_Act_Power_Limit = Bcd2Hex(Temp,3);
  
  Len=Read_Storage_Data(0x04000E02, Temp, Temp, sizeof(Temp));//����������
  ASSERT(3 EQ Len);
  Power_Ctrl_Para.Neg_Act_Power_Limit = Bcd2Hex(Temp,3);

/*  
  Len=Read_Storage_Data(0x04001402, Temp, Temp, sizeof(Temp));//��բ��ʱ
  ASSERT(2 EQ Len);
  Relay_Delay_Para.Relay_On_Delay = (INT16U)Bcd2Hex(Temp[0], 2);
  
  Len=Read_Storage_Data(0x0E00010C, Temp, Temp, sizeof(Temp));//�û����� 
  ASSERT(1 EQ Len); 
  Power_Ctrl_Para.User_Level = Bcd2Hex_Byte(Temp[0]);
*/  
  SET_STRUCT_SUM(Power_Ctrl_Para);  
  
}

//������״̬��־
void Read_Ctrl_Status_Flag_From_Rom()
{
  Read_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));  
  INIT_STRUCT_VAR(Ctrl_Status_Flag);
  SET_STRUCT_SUM(Ctrl_Status_Flag);
}

//��ȡԶ�̿��Ʋ���
void Read_Remote_Ctrl_Para_From_Rom()
{
  //��ȡԶ�̿��Ƽ̵���״̬
  Read_Storage_Data(_SDI_REMOTE_RELAY_STATUS, (INT8U *)&Remote_Ctrl_Switch, \
                    (INT8U *)&Remote_Ctrl_Switch,sizeof(Remote_Ctrl_Switch));
  SET_STRUCT_SUM(Remote_Ctrl_Switch);
 
  Check_Remote_Ctrl_Switch_Status();  
  
}

//��ȡ�̵�����բ��բ��ʱ����
void Read_Relay_Delay_Para_From_Rom()
{
  INT8U Temp[4];
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_RELAY_OFF_DELAY, Temp, Temp, sizeof(Temp));//��բ��ʱ
  ASSERT(2 EQ Len);
  Relay_Delay_Para.Relay_Off_Delay = (INT16U)Bcd2Hex(Temp, 2);
  
  Relay_Delay_Para.Relay_On_Delay = 0; //��բ��ʱ�̶�Ϊ0����Լ��δ����  
  SET_STRUCT_SUM(Relay_Delay_Para);
}

//��ȡ���ɿ��Ʋ�������ROM�ж�ȡ
void Read_Ctrl_Para_From_Rom()
{
  TRACE();
  
  //��ȡ�̵�����բ��բ��ʱ����
  Read_Relay_Delay_Para_From_Rom();   
  //��ȡԶ�̿��Ʋ���
  Read_Remote_Ctrl_Para_From_Rom();
  //��ȡԤ���Ѹ��ɿ��Ʋ���
  //Read_Prepaid_Ctrl_Para_From_Rom();
  //��ȡ���ɿ��Ʋ���--�ù�����POWER_CTRL_EN
  Read_Power_Ctrl_Para_From_Rom();
  //������״̬��־
  Read_Ctrl_Status_Flag_From_Rom();
  //��ȡ�������������
  Read_Meter_Property_Word();
}

//�����Ʋ����ĺϷ���
void Check_Ctrl_Para_Avail()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Mode_Word);
  Re &= CHECK_STRUCT_SUM(Relay_Delay_Para);
  //Re &= CHECK_STRUCT_SUM(Prepaid_Power_Ctrl_Para);
  //Զ�̿��ƺ�Ԥ���Ѹ��صĿ���״̬��Ϊ�����洢
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

//������������ݵĺϷ���
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
��բ�ӿڣ�
Switch_Ctrl(INT8U SwitchFlag)
SwitchFlag��0����բ
0-------------��բ�ϵ�

*/
/*
void Remote_Ctrl_Proc()//Զ�̿���
{
  //INT8U Re;
  
  TRACE();
  
  Check_Remote_Ctrl_Switch_Status();
  
  if(Remote_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF) //��բ
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
//��������ж�Hook����,����ͳ�������������,����Ԥ���ѵĸ��ɿ���
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
//���Ԥ���ѵĸ��ɿ�������
void Clr_Prepaid_Power_Ctrl_Pulse_Data()
{
  DIS_ACT_PULSE_INT;
  
  mem_set((void *)&Prepaid_Power_Ctrl_Pulse, 0, sizeof(Prepaid_Power_Ctrl_Pulse),\
          (void *)&Prepaid_Power_Ctrl_Pulse, sizeof(Prepaid_Power_Ctrl_Pulse));
  INIT_STRUCT_VAR(Prepaid_Power_Ctrl_Pulse);
  
  EN_ACT_PULSE_INT;
}*/
/*
//Ԥ���Ѹ��ɿ��ƺϼ̵���,���ݺ�բ�ж��Ƿ������բ����
//FlagΪ0��ʾ��բ���������բ����
//��0��ʾ����բ�������޵�����²���բ�������բ,���������բ����
INT8U Prepaid_Power_Ctrl_Switch_On(INT8U Flag)
{
  if(Flag EQ 0) //���������բ����,������բ�������޵�����²���բ
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
  //�������״̬
  Write_Storage_Data(_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, (void *)&Prepaid_Power_Ctrl_Switch, sizeof(Prepaid_Power_Ctrl_Switch));
  return 1;
}

//Ԥ���ѵĸ��ɿ��ƴ���
void Prepaid_Power_Ctrl_Proc()
{
  static S_Int8U Min_Bak = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT8U i, Posi;
  INT32U Pulse_Sum = 0;

  if(Sec_Bak.Var EQ Sec_Timer_Pub) //ÿ�����һ�θú���
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;
  
  if(Prepaid_Power_Ctrl_Switch.Off_Delay > 0) //��բ��ʱ
  {
    Prepaid_Power_Ctrl_Switch.Off_Delay --;
    SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);
    
    if(Prepaid_Power_Ctrl_Switch.Off_Delay EQ 0)
    {
      Prepaid_Power_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
      Prepaid_Power_Ctrl_Switch.Off_Counts ++;      
      SET_STRUCT_SUM(Prepaid_Power_Ctrl_Switch);     
      //����Ԥ���Ѹ��ɿ���״̬!
      Write_Storage_Data(_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, (void *)&Prepaid_Power_Ctrl_Switch, sizeof(Prepaid_Power_Ctrl_Switch));      
    }
  }
  
  //ÿ����ͳ����󸺺�����ʱ���ڵ�������,���ж��Ƿ񸺺ɳ���
  if(Min_Bak.Var != Cur_Time1.Min)
  {  
    Min_Bak.Var = Cur_Time1.Min;
    
    DIS_ACT_PULSE_INT; //��������������ж�
    
    Posi = Prepaid_Power_Ctrl_Pulse.Posi;  
    Prepaid_Power_Ctrl_Pulse.Posi ++;
    
    if(Prepaid_Power_Ctrl_Pulse.Posi >= PREPAID_POWER_CTRL_UNIT_NUM)
      Prepaid_Power_Ctrl_Pulse.Posi = 0;
    
    Prepaid_Power_Ctrl_Pulse.Pulse_Num[Prepaid_Power_Ctrl_Pulse.Posi] = 0;
    
    EN_ACT_PULSE_INT; //��������������ж�
  
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
    
    if(Pulse_Sum >= Prepaid_Power_Ctrl_Para.Max_Power_Pulse) //������󸺺�������
    {
       //��բ��ʱ����
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
//���ɿ��ƴ���(����������)---�ú���Ӧ�ý���ʱ����ȥ�����������д���һ������
void Power_Ctrl_Proc()
{
  static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re, i;
  INT32U Power, Demand_Limit;
  INT16U Relay_Flag, Alarm_Flag;

  if(0 EQ POWER_CTRL_EN)//ģʽ��2��bit4��ʾ�Ƿ��и��ع���
    return;
  
  TRACE();
  
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;//ÿ����һ��Զ�̿���

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
  
  //��բ��բ��ʱ����
  if(Power_Ctrl_Switch.Off_Delay > 0)
  {
    Power_Ctrl_Switch.Off_Delay --;
    if(Power_Ctrl_Switch.Off_Delay EQ 0)
    {
      Set_Event_Instant(ID_EVENT_RELAY_OFF);//��������բ�¼�����
      Power_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
    }
    SET_STRUCT_SUM(Power_Ctrl_Switch);
  }
  else if(Power_Ctrl_Switch.On_Delay > 0)
  {
    Power_Ctrl_Switch.On_Delay --;
    if(Power_Ctrl_Switch.On_Delay EQ 0)
    {
      Clr_Event_Instant(ID_EVENT_RELAY_OFF);//��������բ�¼�����
      Power_Ctrl_Switch.Switch_Flag = SWITCH_ON;
    }
    SET_STRUCT_SUM(Power_Ctrl_Switch); 
  }
  
  Relay_Flag = SWITCH_ON;
  Alarm_Flag = ALARM_OFF;
  
  //��ǰ�����й�������!
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
   //�����й���������
   if(Power > Demand_Limit)//�й����������޷���
   {
     if(2 EQ Power_Ctrl_Para.User_Level)//1���û�����������բ��2���û�ֻ��������բ��3���û��ȱ�������բ
     {
       Alarm_Flag = ALARM_ON;
     }
     else if(3 EQ Power_Ctrl_Para.User_Level)//�û�����2����3����
     {
       Alarm_Flag = ALARM_ON;
       Relay_Flag = SWITCH_OFF; //��բ��־
     }
   }
   else//�������ָ�
   {
     if(2 EQ Power_Ctrl_Para.User_Level)//1���û�����������բ��2���û�ֻ��������բ��3���û��ȱ�������բ
     {
       //Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//����
     }
     else if(3 EQ Power_Ctrl_Para.User_Level)//�û�����2����3����
     {
       //Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//����
  
     }
   }
  }
  
  if(Relay_Flag EQ SWITCH_OFF)//��ǰӦ����բ
  {
    //��բ��ʱ����
    if(Power_Ctrl_Switch.Switch_Flag != SWITCH_OFF  && Power_Ctrl_Switch.Off_Delay EQ 0)
    {
      Debug_Print("Prepaid Relay Switch off Delay");           
      Power_Ctrl_Switch.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
      SET_STRUCT_SUM(Power_Ctrl_Switch);
    }   
  }
  else
  {
    //��բ��ʱ����
    if(Power_Ctrl_Switch.Switch_Flag != SWITCH_ON  && Power_Ctrl_Switch.On_Delay EQ 0)
    {  
      Debug_Print("Prepaid Relay Switch on Delay");            
      Power_Ctrl_Switch.On_Delay = Relay_Delay_Para.Relay_On_Delay;
      SET_STRUCT_SUM(Power_Ctrl_Switch);  
    }
  }
  
  if(Alarm_Flag EQ ALARM_ON)
    Set_Event_Instant(ID_EVENT_DEMAND_ALARM);//���� 
  else
    Clr_Event_Instant(ID_EVENT_DEMAND_ALARM);//�������
    
}

//��ȡԤ���ѿ��Ƽ̵���״̬
INT16U Get_Prepaid_Relay_Status()
{
  return Prepaid_Ctrl_Switch.Switch_Flag;  
}

//Ԥ���ѿ��Ƽ̵���
void Prepaid_Switch_Ctrl(INT16U Switch_Flag)
{
  //��բ
  if(Switch_Flag EQ SWITCH_ON)
  {
    if(Prepaid_Ctrl_Switch.Switch_Flag != SWITCH_ON)
    {
      Prepaid_Ctrl_Switch.Switch_Flag = SWITCH_ON;
      SET_STRUCT_SUM(Prepaid_Ctrl_Switch);
      
      //Clr_Event_Instant(ID_EVENT_RELAY_OFF);//��բ�¼�����
      //Set_Event_Instant(ID_EVENT_RELAY_ON); //��բ�¼�����      
    }
  }
  else if(Switch_Flag EQ SWITCH_OFF)
  {
    if(Prepaid_Ctrl_Switch.Switch_Flag != SWITCH_OFF)
    {
      Prepaid_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
      SET_STRUCT_SUM(Prepaid_Ctrl_Switch);
      
      //Clr_Event_Instant(ID_EVENT_RELAY_ON);//��բ�¼�����
      //Set_Event_Instant(ID_EVENT_RELAY_OFF); //��բ�¼�����      
    }     
  }
  else
    ASSERT_FAILED();
}

//Ԥ���ѱ�������
void Prepaid_Alarm_Proc(INT8U Type)
{
  if(PREPAID_EN EQ 0)
    return;
  
  if(PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //�����Զ��Ԥ���ѣ�����բҲ������
    return;
  
  if(Type EQ ALARM_ON) //Ԥ���ѱ���
    Prepaid_Ctrl_Switch.Alarm_Flag = ALARM_ON;
  else if(Type EQ ALARM_OFF)
    Prepaid_Ctrl_Switch.Alarm_Flag = ALARM_OFF;
  else
    ASSERT_FAILED();
  
  SET_STRUCT_SUM(Prepaid_Ctrl_Switch);
  
}

//Ԥ���ѵı�������բ����
void Prepaid_Ctrl_Proc(INT8U Type)
{
  INT8U Card_Switch_On_Flag;
  
  if(PREPAID_EN EQ 0)
    return;

  if(PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //�����Զ��Ԥ���ѣ�����բҲ������
    return;
  
  Card_Switch_On_Flag = Get_Card_Switch_On_Flag();
  switch(Type)
  {
  case PREPAID_ENERGY_ENOUGH:
  case PREPAID_MONEY_ENOUGH:
    Prepaid_Alarm_Proc(ALARM_OFF);
    Prepaid_Switch_Ctrl(SWITCH_ON);
    break;
  //ʣ���ѡ�����С������1
  case PREPAID_ENERGY_LEFT1:
  case PREPAID_MONEY_LEFT1:
   if(PREPAID_WARN_EN) //��������
   {
     if(PREPAID_LIMIT1_WARN_EN) //��������1
       Prepaid_Alarm_Proc(ALARM_ON);
     else
       Prepaid_Alarm_Proc(ALARM_OFF);//Clr_Event_Instant(ID_PAY_ALARM);
   }
   Prepaid_Switch_Ctrl(SWITCH_ON);
   break;
  //ʣ����������С������2
  case PREPAID_ENERGY_LEFT2:
  case PREPAID_MONEY_LEFT2:
   if(PREPAID_WARN_EN) //��������
   {
     if(PREPAID_LIMIT2_WARN_EN  && Card_Switch_On_Flag EQ 0) //��������2
       Prepaid_Alarm_Proc(ALARM_ON);//Set_Event_Instant(ID_PAY_ALARM);
     else
       Prepaid_Alarm_Proc(ALARM_OFF);//Clr_Event_Instant(ID_PAY_ALARM);
   }
  
   //��բ����
   if(PREPAID_LIMIT2_SWITCH_EN && Card_Switch_On_Flag EQ 0) //��������2
   {
     Prepaid_Alarm_Proc(ALARM_OFF); //��բ��Ӧ�ùص�����
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   }
   else
     Prepaid_Switch_Ctrl(SWITCH_ON);
   break;
  //ʣ����������С��0
  case PREPAID_ENERGY_ZERO:
  case PREPAID_MONEY_ZERO:
   if(PREPAID_WARN_EN) //��������
   {
     if(PREPAID_ZERO_WARN_EN  && Card_Switch_On_Flag EQ 0) //����0
       Prepaid_Alarm_Proc(ALARM_ON);//Set_Event_Instant(ID_PAY_ALARM);
     else
       Prepaid_Alarm_Proc(ALARM_OFF);//Clr_Event_Instant(ID_PAY_ALARM);
   }
  
   if(PREPAID_ZERO_SWITCH_EN && Card_Switch_On_Flag EQ 0) //����0
   {
     Prepaid_Alarm_Proc(ALARM_OFF); //��բ��Ӧ�ùص�����
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   }
   else
     Prepaid_Switch_Ctrl(SWITCH_ON);
    break;
    
  //��͸֧���������
  case PREPAID_ENERGY_OVERDRAFT:
  case PREPAID_MONEY_OVERDRAFT:
     Prepaid_Alarm_Proc(ALARM_ON);  //�ص�������ֱ����բ
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   break;     
  case PREPAID_MONEY_SWITCH_LIMIT://��������ں�բ����
     Prepaid_Alarm_Proc(ALARM_OFF);  //�ص�������ֱ����բ
     Prepaid_Switch_Ctrl(SWITCH_OFF);
   break;   
  }
}

//����Զ�̿��Ʊ�������բ������״̬
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

//����Ƿ����ֶ���բ
void Check_Hand_Switch_On()
{
  if(Relay_Status.Switch_Status EQ SWITCH_OFF)
  {
    if(Judge_RelayOn_Key())
    {
      Set_Hand_Switch_On_Flag(0);  //�����ֶ���բ��־
    }
  }
}

//�ֶ��忨��բ
void Card_Switch_On()
{
  if(Relay_Status.Switch_Status EQ SWITCH_OFF) //��ǰ��Ԥ������բ״̬(Ƿ�ѻ��߳�����)
  {
    if(Ctrl_Status_Flag.Card_Switch_On_Flag != 1 || Ctrl_Status_Flag.Hand_Switch_On_Flag != 0)
    {
      Ctrl_Status_Flag.Card_Switch_On_Flag = 1;
      Ctrl_Status_Flag.Hand_Switch_On_Flag = 0;//���ֶ���բ״̬
      
      SET_STRUCT_SUM(Ctrl_Status_Flag);
      Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));
    }  
  }
}

//Զ�̿��Ƽ̵���
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
  //��ǰʱ�����������ʱ��֮��
  if(Cmp_Array_Time(pData + 2, Temp, sizeof(Temp)) EQ TIME_AFT)
  {
    if(Switch_Flag EQ SWITCH_ON) //�����բ
    {
      Remote_Ctrl_Switch.Switch_Flag = SWITCH_ON; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Switch On!");
      
      Save_Remote_Ctrl_Switch_Flag(); 
      
      return 1;
    }
    else if(Switch_Flag EQ SWITCH_OFF) //��բ
    {
      if(Remote_Ctrl_Switch.Maintain_Flag EQ MAINTAIN_ON) //��Ҫ�Ƚ������״̬
        return 0;
      
      Remote_Ctrl_Switch.Switch_Flag = SWITCH_OFF;
       
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Switch Off!");
      
      Save_Remote_Ctrl_Switch_Flag();
/*      
  /////////////�յ�������բ����,���ҵ�ǰ�Ѿ�����բ״̬�������·�һ����բ����,��ƽ��ʽ����Ҫ����------------------------------
  /////////////�����ǰ����������բ״̬������բ�������̻ᴦ����բ������Ҫ�����﷢����      
      if(EXT_SWITCH_MODE EQ 1 && Relay_Status.Switch_Status EQ SWITCH_OFF)
      {
        Excute_Toogle(0);  //���һ����բ����  
      }
  //////////////////////////////////////////  
*/          
      return 1;
    }
    else if(Switch_Flag EQ MAINTAIN_ON) //����
    {
      Set_Hand_Switch_On_Flag(0); //�����ֶ���բ��־
      Remote_Ctrl_Switch.Maintain_Flag = MAINTAIN_ON; 
      Remote_Ctrl_Switch.Switch_Flag = SWITCH_ON;    //�����բ
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Maintain On!");
      
      Save_Remote_Ctrl_Switch_Flag();     
      return 1;
    }
    else if(Switch_Flag EQ MAINTAIN_OFF) //������
    {
      Remote_Ctrl_Switch.Maintain_Flag = MAINTAIN_OFF; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Debug_Print("Remote Ctrl Maintain Off!");
      
      Save_Remote_Ctrl_Switch_Flag();     
      return 1;
    }
    else if(Switch_Flag EQ ALARM_ON) //����
    {
      Remote_Ctrl_Switch.Alarm_Flag = ALARM_ON; 
      SET_STRUCT_SUM(Remote_Ctrl_Switch);
      Save_Remote_Ctrl_Switch_Flag();
      return 1;       
    }
    else if(Switch_Flag EQ ALARM_OFF) //�������
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

//���Զ�̿��Ƽ̵���״̬
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

//���忪�ؿ���
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
  
  if(Switch_Flag EQ SWITCH_OFF) //��բ
  {
    Pos_Act_Eng = Get_Pos_Act_Eng();
    
    if(Last_Switch_Status.Var != SWITCH_OFF) //״̬�����˱仯
    {
      Last_Switch_Status.Var = Switch_Flag;
      Debug_Print("Pulse_Switch_Off");
      Pos_Act_Bak.Var = Pos_Act_Eng; //��ȡ��ǰ�����й��ܵ���
      Excute_Toogle(0);  //���һ����բ����
    }  
    
    //��բ��Ϊ�˷�ֹ��բû�гɹ���ÿ��1kwh�ĵ磬��բһ��
    if(Pos_Act_Eng > Pos_Act_Bak.Var &&\
      (Pos_Act_Eng - Pos_Act_Bak.Var) >= SWITCH_POS_ACT_EN)
    {
      Debug_Print("Pulse_Switch_Off again");
      Pos_Act_Bak.Var = Pos_Act_Eng;  
      Excute_Toogle(0);  //���һ����բ����         
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

//��ȡ��Ԥ��բ����״̬��̵�������״̬�Լ��̵���״̬
//��7λ��ʾԤ��բ����״̬
//��6λ��ʾ�̵�������״̬
//��4λ��ʾ�̵���״̬
INT8U Get_Alarm_Relay_Status()
{
  INT8U Byte;
  
  Byte = 0;
  
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  {
     if((PREPAID_MODE EQ PREPAID_MONEY && Cur_Energy.Prepaid_Info.Left_Energy / 10 < Prepaid_Para.Warn_Money1) ||\
        (PREPAID_MODE EQ PREPAID_ENG && Cur_Energy.Prepaid_Info.Left_Energy / 10 < Prepaid_Para.Warn_Energy1))
     {
       SET_BIT(Byte, 7); //Ԥ��բ����
     }
  }
  
  if(Relay_Status.Off_Delay > 0 || Relay_Status.Switch_Status EQ SWITCH_OFF)
  {
    SET_BIT(Byte, 6); //�̵�������״̬
  }
  
  if(Relay_Status.Switch_Status EQ SWITCH_OFF)
  {
    SET_BIT(Byte, 4); //�̵���״̬ 
  }
  
  return Byte;
}

//���̵���״̬
//ALLOW_SWITCH_ON //��բ״̬�������բ
//SWITCH_DELAY //��բ��ʱ�׶�
//SWITCH_OFF ��բ�Ҳ������բ
//SWITCH_ON ��բ״̬
INT8U Get_Relay_Status()
{
  INT8U Cause;
  INT8U Re;

  if(Relay_Status.Off_Delay > 0) //��բ��ʱ�׶�
  {
    return SWITCH_DELAY; 
  }  
  else if(Relay_Status.Switch_Status EQ SWITCH_OFF)//��բ״̬
  {
    Re = Check_Switch_Status(&Cause);
    if(Re EQ SWITCH_ON)
      return ALLOW_SWITCH_ON;
    else
    {
      if(PREPAID_EN > 0)
      {
        if(Cause EQ S_OFF_PREPAID) //�����Ԥ������բ
        {
          Re = Get_Prepaid_Status();
          if(Re EQ PREPAID_MONEY_LEFT2 || Re EQ PREPAID_MONEY_ZERO) //��û�г�͸֧���޵�����£��ڱ�������2�����ֶ���բ
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

void Card_Test_Relay() //�忨���Լ̵���״̬����Heguoquan����
{
  Card_Test_Relay_Status.Flag = CARD_TESTING;
  Card_Test_Relay_Status.Delay = CARD_TESTING_DELAY; 
}

//�̵�������
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
//��բֱ�ӿ���
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
  
  if(Card_Test_Relay_Status.Flag EQ CARD_TESTING) //��ǰ�ڼ̵�������״̬
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
  if(Flag.Var EQ 0xFF) //��һ�ν���
  {
    Flag.Var = 0;
    if(Status EQ SWITCH_OFF) //�ϵ�������������բ״̬,˵��ǰһ�ε���ǰ���Ѿ���Ƿ��״̬
    {
      Relay_Status.Switch_Status = SWITCH_OFF;
      Relay_Status.Switch_Cause = Cause;
      Clr_Event_Instant(ID_EVENT_RELAY_ON); //��բ�¼�����      
      Set_Event_Instant(ID_EVENT_RELAY_OFF);//��բ�¼�����      
    }
  }
 */
  
  if(Switch_Flag EQ SWITCH_OFF) //��բ!
  {
    Set_Hand_Switch_On_Flag(NEED_HAND_SWITCH_ON_FLAG); //��Ҫ�ֶ���բ 
    if(Relay_Status.Switch_Status != SWITCH_OFF && Relay_Status.Off_Delay EQ 0)
    {
      if(Cause EQ S_OFF_PREPAID)
        Relay_Status.Off_Delay = 0;
      else
        Relay_Status.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
        
      Counts.Var = 0;
      //Relay_Status.On_Delay = 0;
      if(Relay_Status.Off_Delay EQ 0) //����趨��ʱΪ0��������բ
      {       
        //Relay_Status.Switch_Status = SWITCH_OFF;
        //Relay_Status.Switch_Cause = Cause;
        Set_Relay_Status(SWITCH_OFF, Cause);
        //Clr_Event_Instant(ID_EVENT_RELAY_ON); //��բ�¼�����      
        //Set_Event_Instant(ID_EVENT_RELAY_OFF);//��բ�¼�����  
      } 
    }
  }
  else //�����բ
  {
    if(Get_Hand_Switch_On_Flag() != NEED_HAND_SWITCH_ON_FLAG) //�Ѿ��ֶ���բ?
    {
      Relay_Status.Off_Delay = 0;
      //Relay_Status.Switch_Status = SWITCH_ON;
      //Relay_Status.Switch_Cause = Cause;
      Set_Relay_Status(SWITCH_ON, Cause);
      //Clr_Event_Instant(ID_EVENT_RELAY_OFF);//��բ�¼�����
      //Set_Event_Instant(ID_EVENT_RELAY_ON); //��բ�¼�����      
    }
    else //��û���ֶ���բ�򱣳���բ״̬
    {
      if(Relay_Status.Switch_Status != SWITCH_OFF && Relay_Status.Off_Delay EQ 0)
      {
        if(Cause EQ S_OFF_PREPAID)
          Relay_Status.Off_Delay = 0;
        else
          Relay_Status.Off_Delay = Relay_Delay_Para.Relay_Off_Delay;
        
        Counts.Var = 0;

        if(Relay_Status.Off_Delay EQ 0) //����趨��ʱΪ0��������բ
        {       
          Set_Relay_Status(SWITCH_OFF, Cause);
          //Clr_Event_Instant(ID_EVENT_RELAY_ON); //��բ�¼�����      
          //Set_Event_Instant(ID_EVENT_RELAY_OFF);//��բ�¼�����  
        } 
      }      
    }
  }
  
  if(Sec_Bak.Var != Sec_Timer_Pub)
  {
    Counts.Var ++;
    Sec_Bak.Var = Sec_Timer_Pub;
  }
  
  if(Counts.Var >= 60) //ʱ�䰴����һ����
  {
    Counts.Var = 0;
    
    if(Relay_Status.Off_Delay > 0) //��բ
    {
      Relay_Status.Off_Delay--;
      if(Relay_Status.Off_Delay EQ 0)
      {
        //Relay_Status.Switch_Status = SWITCH_OFF;
        //Relay_Status.Switch_Cause = Cause;
        Set_Relay_Status(SWITCH_OFF, Cause);
        //Clr_Event_Instant(ID_EVENT_RELAY_ON); //��բ�¼�����      
        //Set_Event_Instant(ID_EVENT_RELAY_OFF);//��բ�¼�����
        
        Set_Hand_Switch_On_Flag(NEED_HAND_SWITCH_ON_FLAG); //��Ҫ�ֶ���բ        
      }
    }
    
  }
  
  //if(EXT_SWITCH_MODE EQ 0) //��ƽ��ʽ����
  //{
    if(SWITCH_ON EQ Relay_Status.Switch_Status) //��բ 
      Excute_Toogle(1);//EXT_SWITCH_MODE
    else //��բ
    {
      if(Relay_Status.Switch_Status != SWITCH_OFF)
        ASSERT_FAILED();
      
      Excute_Toogle(0);
    }
  //}
    /*
  else //���巽ʽ
  {
    Pulse_Switch_Ctrl(Relay_Status.Switch_Status);
  }*/

}

//��ȡ��ǰ��բ״̬
INT8U Get_Switch_Status()
{
 return Relay_Status.Switch_Status;  
}

//��鵱ǰӦ�õ�����բ״̬,��������բ״̬��
//*pCause��ʾ����բԭ��
INT8U Check_Switch_Status(INT8U *pCause)
{
  if(Remote_Ctrl_Switch.Maintain_Flag EQ MAINTAIN_ON) //���磡���ȼ����
  {
    //��������Чʱ����ǰ���б���
    *pCause = S_ON_MAINTAIN; //��բԭ��
    return SWITCH_ON;
  }
  
  //����Ԥ������Ԥ������բ��ʾΪ��բ
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL &&  Prepaid_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF)
  {
    //if(PREPAID_EN > 0)
    {
      *pCause = S_OFF_PREPAID; //��բԭ��
      return SWITCH_OFF;
    }
  }
  else if(Remote_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF) //Զ�̿���
  {
    *pCause = S_OFF_REMOTE_CMD;    
    return SWITCH_OFF;
  }
  else if(POWER_CTRL_EN > 0 && Power_Ctrl_Switch.Switch_Flag EQ SWITCH_OFF) //���ɿ���
  {
    //if(POWER_CTRL_EN>0)
    {
      *pCause = S_OFF_PWR_CTRL;      
      return SWITCH_OFF;
    }
  }

  //else //��բ
  //{      
    *pCause = Relay_Status.Switch_Cause;//S_ON_OTHER;
    return SWITCH_ON;   
  //} 
    
}

INT8U Check_Alarm_Status()
{
  //Զ�̱������� 
  if(Remote_Ctrl_Switch.Alarm_Flag EQ ALARM_ON)
    return ALARM_ON;
  
  if(Relay_Status.Off_Delay > 0) //��բ��ʱ�׶�
    return ALARM_ON;
  
  //��ǰ���ڱ���״̬�����Ǳ���Ԥ���ѡ�Ԥ���ѱ������򱨾�
  if(Remote_Ctrl_Switch.Maintain_Flag != MAINTAIN_ON &&\
    PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL &&\
    Prepaid_Ctrl_Switch.Alarm_Flag EQ ALARM_ON)
    return ALARM_ON; 
  
  return ALARM_OFF;
}

//�����ֶ���բ��־
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

//��ȡԤ������բ���Ƿ�忨��־,�������˷���1�����򷵻�0���忨���Ա����õ絽͸֧����
INT8U Get_Card_Switch_On_Flag()
{
  return Ctrl_Status_Flag.Card_Switch_On_Flag;  
}

//�����ֶ������բ��־,����0��ʾ�Ѿ��ֶ���բ��1��ʾ��û���ֶ���բ
INT8U Get_Hand_Switch_On_Flag()
{
  return Ctrl_Status_Flag.Hand_Switch_On_Flag; 
}

//����բ����£����²忨�ɻָ�����
//Card_TypeΪ0��ʾ��Ȩ�޵Ŀ�����������բ��ͬʱ�����������բ����
//Card_TypeΪ1��ʾ�û������ڸ�����բ�������޵�����²��ܺ�բ
INT8U Prepaid_Insert_Card(INT8U Card_Type)
{
  //INT8U Cause;
  
  if(Card_Type EQ 0)// || Card_Type EQ 1)
  {
    if(Relay_Status.Switch_Status EQ SWITCH_OFF) //��ǰ��Ԥ������բ״̬(Ƿ�ѻ��߳�����)
    {
      Card_Switch_On();
      return 1;
    }
  }
  else
  {
    if(Relay_Status.Switch_Status EQ SWITCH_OFF)
    {
      Set_Hand_Switch_On_Flag(0);  //�����ֶ���բ��־
      return 1;
    }
  }
  
  return 0;
}

//�������ܿ���
void Alarm_Ctrl(INT8U Status)
{
  if(Status EQ ALARM_ON)
    Set_Event_Instant(ID_PAY_ALARM); //��բ�¼����� 
  else
    Clr_Event_Instant(ID_PAY_ALARM);//��բ�¼�����    
}

//��բ�̵����ܵĿ���
void Switch_Ctrl_Proc()
{
  //INT8U Re;
  INT8U Status;
  INT8U Cause;

  Check_Hand_Switch_On(); //����ֶ���բ��־,�忨��բ�Ĵ����ڲ忨ʱ����
  
  //�����բ״̬,�õ���ǰӦ�õ���բ״̬��ԭ��
  Status = Check_Switch_Status((INT8U *)&Cause);
  //����բ��բ�Ƚ�����ʱ����
  Switch_Ctrl(Status,Cause);
  
  //�����ܿ���
  Status = Check_Alarm_Status();
  Alarm_Ctrl(Status);
}
#undef POWER_CTRL_C
