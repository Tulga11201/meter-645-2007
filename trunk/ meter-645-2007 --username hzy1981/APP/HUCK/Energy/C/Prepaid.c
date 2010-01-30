#define PREPAID_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H9"
#endif

//��ȡԤ���Ѳ���
void Read_Prepaid_Para_From_Rom()
{
  INT16U Len;
 
  //����Ԥ���Ѳ���
  Len = Read_Multi_Storage_Data(0x04000F01, 4,(INT8U *)&Prepaid_Para.Warn_Energy1, (INT8U *)&Prepaid_Para, sizeof(Prepaid_Para));
  ASSERT(Len EQ 16);
 
  //���Ԥ���Ѳ���
  Len = Read_Multi_Storage_Data(0x04001001, 5, (INT8U *)&Prepaid_Para.Warn_Money1, (INT8U *)&Prepaid_Para, sizeof(Prepaid_Para));
  ASSERT(Len EQ 20);

  //Ԥ����ģʽ��
  Len = Read_Multi_Storage_Data(SDI_PREPAID_MODEWORD_1, 3, (INT8U *)Prepaid_Para.Mode, (INT8U *)&Prepaid_Para, sizeof(Prepaid_Para));
  ASSERT(Len EQ 3);
  
  //�ݶ�ֵ
  if(PREPAID_EN > 0 && PREPAID_MONEY_MODE EQ PREPAID_STEP)
  {
    Len = Read_Storage_Data(0x04000207, (INT8U *)&Prepaid_Para.Step_Num, (INT8U *)&Prepaid_Para.Step_Num, sizeof(Prepaid_Para.Step_Num));
    ASSERT(Len EQ 1);
  }
  else
  {
    Prepaid_Para.Step_Num = 1;  
  }
  
  //�������������
  Prepaid_Para.CT_Ratio = 0;
  Len = Read_Storage_Data(0x04000306, (INT8U *)&Prepaid_Para.CT_Ratio, (INT8U *)&Prepaid_Para.CT_Ratio, sizeof(Prepaid_Para.CT_Ratio));
  ASSERT(Len EQ 3);
  
  //��ѹ���������
  Prepaid_Para.PT_Ratio = 0;  
  Len = Read_Storage_Data(0x04000307, (INT8U *)&Prepaid_Para.PT_Ratio, (INT8U *)&Prepaid_Para.PT_Ratio, sizeof(Prepaid_Para.PT_Ratio));
  ASSERT(Len EQ 3);
/*  
  //���ʸ���������
  Prepaid_Para.Power_Puls = 0;
  Len = Read_Storage_Data(0x0400E001, (INT8U *)&Prepaid_Para.Power_Puls, (INT8U *)&Prepaid_Para.Power_Puls, sizeof(Prepaid_Para.Power_Puls));
  ASSERT(Len EQ 3);

  //��󸺺ɼ���ʱ��
  Prepaid_Para.Power_Mins = 0;
  Len = Read_Storage_Data(0x0400E002, (INT8U *)&Prepaid_Para.Power_Mins, (INT8U *)&Prepaid_Para.Power_Mins, sizeof(Prepaid_Para.Power_Mins));
  ASSERT(Len EQ 1);

  //��������բ��������
  Prepaid_Para.Relay_Off_Counts_Limit = 0;
  Len = Read_Storage_Data(0x0400E003, (INT8U *)&Prepaid_Para.Relay_Off_Counts_Limit, (INT8U *)&Prepaid_Para.Relay_Off_Counts_Limit, sizeof(Prepaid_Para.Relay_Off_Counts_Limit));
  ASSERT(Len EQ 1);
 */ 
  Prepaid_Para.Warn_Energy1 = Bcd2Hex((INT8U *)&Prepaid_Para.Warn_Energy1, sizeof(Prepaid_Para.Warn_Energy1));
  Prepaid_Para.Warn_Energy2 = Bcd2Hex((INT8U *)&Prepaid_Para.Warn_Energy2, sizeof(Prepaid_Para.Warn_Energy2));

  Prepaid_Para.Hoard_Energy_Limit = Bcd2Hex((INT8U *)&Prepaid_Para.Hoard_Energy_Limit, sizeof(Prepaid_Para.Hoard_Energy_Limit));
  Prepaid_Para.Overdraft_Energy_Limit = Bcd2Hex((INT8U *)&Prepaid_Para.Overdraft_Energy_Limit, sizeof(Prepaid_Para.Overdraft_Energy_Limit));
  
  Prepaid_Para.Warn_Money1 = Bcd2Hex((INT8U *)&Prepaid_Para.Warn_Money1, sizeof(Prepaid_Para.Warn_Money1));
  Prepaid_Para.Warn_Money2 = Bcd2Hex((INT8U *)&Prepaid_Para.Warn_Money2, sizeof(Prepaid_Para.Warn_Money2));
  Prepaid_Para.Overdraft_Money_Limit = Bcd2Hex((INT8U *)&Prepaid_Para.Overdraft_Money_Limit, sizeof(Prepaid_Para.Overdraft_Money_Limit));
  Prepaid_Para.Hoard_Money_Limit = Bcd2Hex((INT8U *)&Prepaid_Para.Hoard_Money_Limit, sizeof(Prepaid_Para.Hoard_Money_Limit));  
  Prepaid_Para.Switch_On_Money_Limit = Bcd2Hex((INT8U *)&Prepaid_Para.Switch_On_Money_Limit, sizeof(Prepaid_Para.Switch_On_Money_Limit));  
  
  Prepaid_Para.Step_Num = Bcd2Hex_Byte(Prepaid_Para.Step_Num);
  
  Prepaid_Para.CT_Ratio = Bcd2Hex((INT8U *)&Prepaid_Para.CT_Ratio, sizeof(Prepaid_Para.CT_Ratio)); 
  Prepaid_Para.PT_Ratio = Bcd2Hex((INT8U *)&Prepaid_Para.PT_Ratio, sizeof(Prepaid_Para.PT_Ratio)); 
  
  if(Prepaid_Para.CT_Ratio EQ 0)
    Prepaid_Para.CT_Ratio = 1;
  
  if(Prepaid_Para.PT_Ratio EQ 0)
    Prepaid_Para.PT_Ratio = 1;
    
  //Prepaid_Para.Power_Puls = Bcd2Hex((INT8U *)&Prepaid_Para.Power_Puls, sizeof(Prepaid_Para.Power_Puls)); 
  //Prepaid_Para.Power_Mins = Bcd2Hex_Byte(Prepaid_Para.Power_Mins);
  //Prepaid_Para.Relay_Off_Counts_Limit = Bcd2Hex_Byte(Prepaid_Para.Relay_Off_Counts_Limit);  
  
  INIT_STRUCT_VAR(Prepaid_Para);
  SET_STRUCT_SUM(Prepaid_Para);

  //��ǰ������Ϣ��ʼ��
  mem_set((void *)&Cur_Prepaid, 0, sizeof(Cur_Prepaid), (void *)&Cur_Prepaid, sizeof(Cur_Prepaid)); 
  INIT_STRUCT_VAR(Cur_Prepaid);
  SET_STRUCT_SUM(Cur_Prepaid);  
}

//������Ԥ���Ѵ���
//Eng�ĵ�λ��0.01kwh
INT8U Prepaid_Buy_Energy_Proc(INT32U Eng)
{
  INT8U Re;
  
  if(PREPAID_MODE != PREPAID_ENG)
    return 0;
  
  Check_Energy_Data_Avail(); //�ȼ����������Ƿ�Ϸ�
  
  Re = CHECK_STRUCT_SUM(Cur_Prepaid);
  ASSERT(1 EQ Re);
  
  Eng = Eng * 10;
  
  //���ι����� + ʣ����� > �ڻ�������ֵ ������
  if(Cur_Energy.Prepaid_Info.Left_Energy + Eng > Prepaid_Para.Hoard_Energy_Limit * 10 + Cur_Energy.Prepaid_Info.Overdraft_Energy)
  {
    Main_Dis_Info("FULL");
    return 0; 
  }
  
  Cur_Prepaid.Energy = Eng; //���ι�����
  Cur_Prepaid.Bef_Left_Energy = Cur_Energy.Prepaid_Info.Left_Energy; //���˹���Ǯʣ�����
  SET_STRUCT_SUM(Cur_Prepaid);
  
  DIS_PD_INT;
  
  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts ++; //�ܹ������
  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy += Eng;
  
  if(Cur_Energy.Prepaid_Info.Left_Energy + Eng > Cur_Energy.Prepaid_Info.Overdraft_Energy)
  {
    Cur_Energy.Prepaid_Info.Left_Energy = Cur_Energy.Prepaid_Info.Left_Energy + Eng - Cur_Energy.Prepaid_Info.Overdraft_Energy;
    Cur_Energy.Prepaid_Info.Overdraft_Energy = 0;
  }
  else
  {
    Cur_Energy.Prepaid_Info.Overdraft_Energy = Cur_Energy.Prepaid_Info.Overdraft_Energy - Eng;
    Cur_Energy.Prepaid_Info.Left_Energy = 0;
  }
  
  if((Cur_Energy.Prepaid_Info.Left_Energy / 10) < Prepaid_Para.Warn_Energy2) //�ڱ�������2�ڣ���Ϊ�ֶ���բ��
    Ctrl_Status_Flag.Card_Switch_On_Flag = 1; //����ɹ�������忨��־
  else
    Ctrl_Status_Flag.Card_Switch_On_Flag = 0; //����ɹ�������忨��־
  SET_STRUCT_SUM(Ctrl_Status_Flag);
  
  SET_STRUCT_SUM(Cur_Energy);
  
  EN_PD_INT;
  Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));  
  Save_Cur_Energy_PD_Data(); //���浱ǰ��������
  Save_Cur_Energy_Data();
  //Event_Data_Proc(ID_EVENT_PREPAID_ENERGY, EVENT_OCCUR);
  Card_Op_Info.Buy_Eng_Flag = BUY_ENG;
  SET_STRUCT_SUM(Card_Op_Info);
  
  ENABLE_BEEP_ALARM;
  return 1;
}

//�жϹ������Ƿ���,����0��ʾû�г���1��ʾ��
//Money��λΪ0.01Ԫ
INT8U Check_Buy_Money_Exceed_Limit(INT32U Money)
{
  if(Cur_Energy.Prepaid_Info.Left_Money  + Money * 10 > Prepaid_Para.Hoard_Money_Limit * 10 + Cur_Energy.Prepaid_Info.Overdraft_Money) //�����ڻ��������
  {
    ASSERT_FAILED();
    return 1; 
  }  
  else
    return 0;
}

//��ȡ�������ÿ���Ҫ���õķ��ʲ����Ĵ洢DI
//���÷���1������1��ʾ��ǰ�ף�2��ʾ������
//Scheme 1��ʾ���µ�ǰ�ײ���,2��ʾ�����ײ���
//������Ҫ�洢��DI
STORA_DI Get_Card_Set_Rate_Scheme_SDI(INT8U Scheme)
{
  if(Scheme EQ 1) //��ǰ����
  {
     if(Cur_Scheme.Rate_Scheme EQ RATE_SCHEME0)
       return SDI_RATE_SCHEME0_0;
     else
       return SDI_RATE_SCHEME1_0;
  }
  else
  {
    if(Scheme != 2)
      ASSERT_FAILED();
    
    if(Cur_Scheme.Rate_Scheme EQ RATE_SCHEME0)
      return SDI_RATE_SCHEME1_0;
    else
      return SDI_RATE_SCHEME0_0;
  }  
}

//�����Ԥ���Ѵ���
//Money��λʱ0.01Ԫ
INT8U Prepaid_Buy_Money_Proc(INT32U Money)
{
  INT8U Re;

  if(PREPAID_MODE != PREPAID_MONEY)
    return 0;
  
  Check_Energy_Data_Avail(); //�ȼ����������Ƿ�Ϸ�
  
  Re = CHECK_STRUCT_SUM(Cur_Prepaid);
  ASSERT(1 EQ Re);
  
  if(Check_Buy_Money_Exceed_Limit(Money))
    return 0;
  
  Money = Money * 10;
    
  Cur_Prepaid.Money = Money; //���ι�����
  Cur_Prepaid.Bef_Left_Money = Cur_Energy.Prepaid_Info.Left_Money; //���˹���Ǯʣ�����
  SET_STRUCT_SUM(Cur_Prepaid);
  
  DIS_PD_INT;
  
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts ++; //�ܹ������
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money += Money; 
  
  if(Cur_Energy.Prepaid_Info.Left_Money + Money > Cur_Energy.Prepaid_Info.Overdraft_Money)
  {
    Cur_Energy.Prepaid_Info.Left_Money = Cur_Energy.Prepaid_Info.Left_Money + Money - Cur_Energy.Prepaid_Info.Overdraft_Money;
    Cur_Energy.Prepaid_Info.Overdraft_Money = 0;
  }
  else
  {
    Cur_Energy.Prepaid_Info.Overdraft_Money = Cur_Energy.Prepaid_Info.Overdraft_Money - Money;
    Cur_Energy.Prepaid_Info.Left_Money = 0;
  }
  
  if(Cur_Energy.Prepaid_Info.Left_Money >= Prepaid_Para.Switch_On_Money_Limit * 10) //�ﵽ��բ��������?
    Ctrl_Status_Flag.Buy_Money_Switch_Limit_Flag = 0;
  else
    Ctrl_Status_Flag.Buy_Money_Switch_Limit_Flag = 1;
  
  if((Cur_Energy.Prepaid_Info.Left_Money / 10) < Prepaid_Para.Warn_Money2) //�ڱ�������2�ڣ���Ϊ�ֶ���բ��
    Ctrl_Status_Flag.Card_Switch_On_Flag = 1; //����ɹ�������忨��־
  else
    Ctrl_Status_Flag.Card_Switch_On_Flag = 0; //����ɹ�������忨��־
  
  Ctrl_Status_Flag.Hand_Switch_On_Flag = 0; //�忨����ɹ���Ϊ�����ֶ���բһ��
  
  SET_STRUCT_SUM(Ctrl_Status_Flag);
  SET_STRUCT_SUM(Cur_Energy);
  
  EN_PD_INT;
  Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));
  Save_Cur_Energy_PD_Data(); //���浱ǰ��������
  Save_Cur_Energy_Data();  
  
  Card_Op_Info.Buy_Eng_Flag = BUY_MONEY;
  SET_STRUCT_SUM(Card_Op_Info);
  
  ENABLE_BEEP_ALARM;
  return 1;
  
}



/*
//����忨��־
void Clear_Prepaid_Insert_Card_Flag()
{
  Ctrl_Status_Flag.Card_Switch_On_Flag = 0;
  SET_STRUCT_SUM(Ctrl_Status_Flag);
 
}
*/
//����Ԥ���ѵ�ǰ���ܡ����״̬
void Prepaid_Status_Proc(INT8U Status)
{
  if(Status != Cur_Energy.Prepaid_Info.Eng_Money_Status)
  {
    Cur_Energy.Prepaid_Info.Eng_Money_Status = Status;
    //Cur_Energy.Prepaid_Info.Card_Switch_On_Flag = 0;
  }
}

//Ԥ���ѵ��µ������½������--�ú����ڲ���رմ򿪵����ж�!
void Prepaid_Clr_Month_Eng_Money(S_HEX_Time *pTime)
{
  INT8U Re;
  
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
  
  DIS_PD_INT;
  mem_cpy((INT8U *)&Cur_Energy.Prepaid_Info.Time, pTime, sizeof(S_HEX_Time),\
          (INT8U *)&Cur_Energy.Prepaid_Info.Time, sizeof(Cur_Energy.Prepaid_Info.Time));
  
  //��һ�������ڵ�
  Cur_Energy.Prepaid_Info.Last_Month_Pos_Act = Cur_Energy.Prepaid_Info.Month_Pos_Act;
  Cur_Energy.Prepaid_Info.Last_Month_Neg_Act = Cur_Energy.Prepaid_Info.Month_Neg_Act;  
  
  //�µ����������й��ͷ����й������һλӦ����һ�£���Ϊ���ݼƷ��Ǵ��ܵ����������ϼ��ģ����������һ��
  //���ܴ���ʾ�ϼ��㾫�ȣ����ܳ����������Χ
  Cur_Energy.Prepaid_Info.Month_Pos_Act = Cur_Energy.Pos_Active[0] % 10;
  Cur_Energy.Prepaid_Info.Month_Neg_Act = Cur_Energy.Neg_Active[0] % 10;  
  Cur_Energy.Prepaid_Info.Month_Money = 0;
  SET_STRUCT_SUM(Cur_Energy);
  
  EN_PD_INT;
}

//
void Settle_Prepaid_Month_Eng(S_HEX_Time *pTime)
{
  //S_HEX_Time TempTime;
  
  if(Check_HEX_Time(pTime) EQ 0)
    return;
  
  if(memcmp(pTime, (S_HEX_Time *)&Cur_Energy.Prepaid_Info.Time, sizeof(S_HEX_Time)) != 0)  //��ֹ�ظ����µ���
  {
    //_Debug_Print("Clr Prepaid Eng");
    //Print_HEX_Time(pTime);
    //Print_HEX_Time(&TempTime);
    //_Debug_Print("Cur_Month Active:%ld", Cur_Energy.Prepaid_Info.Month_Pos_Act);
    Prepaid_Clr_Month_Eng_Money(pTime);
  }  
}

//����Ƿ���Ҫ�����ǰ�µ���
void Prepaid_Clr_Month_Eng_Chk(S_HEX_Time *pTime)
{
  S_HEX_Time TempTime;
  
  if(Check_HEX_Time(pTime) EQ 0)
    return;
  
  //��ǰʱ���ǰһ������ʱ�����������һ���������ڣ�����Ҫ����
  if(Get_Next_Settle_Time((S_HEX_Time *)&Cur_Energy.Prepaid_Info.Time, &TempTime, &TempTime, sizeof(TempTime)) >0 &&\
    Cmp_Time(pTime, (S_HEX_Time *)&TempTime) != TIME_BEF)
  {
    //_Debug_Print("Clr Prepaid Eng");
    //Print_HEX_Time(pTime);
    //Print_HEX_Time(&TempTime);
    //_Debug_Print("Cur_Month Active:%ld", Cur_Energy.Prepaid_Info.Month_Pos_Act);
    Prepaid_Clr_Month_Eng_Money(pTime);
  }    
}

//��鵱ǰ�Ľ���
void Check_Cur_Step()
{
  INT8U Step, i;
  INT32U Min, Temp_Energy;
  
  //���㵱ǰ���ĸ�Ԥ���ѽ���
  Min = 0xFFFFFFFF;
  Step = Prepaid_Para.Step_Num;

  //���㵱ǰ����������һ�����ݷ�Χ
  for(i = 0; i < Prepaid_Para.Step_Num && i < PREPAID_MAX_STEP; i ++)
  {
    Temp_Energy = Step_Scheme_Para.Step_Energy[i] * 10; //���µ��ܵ�λ��0.001kwh,Step��λ��0.01kwh����ˡ�10
    if(Temp_Energy > (Cur_Energy.Prepaid_Info.Month_Pos_Act + Cur_Energy.Prepaid_Info.Month_Neg_Act) &&
       Temp_Energy - (Cur_Energy.Prepaid_Info.Month_Pos_Act + Cur_Energy.Prepaid_Info.Month_Neg_Act) < Min)
    {
      Min = Temp_Energy - (Cur_Energy.Prepaid_Info.Month_Pos_Act + Cur_Energy.Prepaid_Info.Month_Neg_Act);
      Step = i;
    }
  }

  Cur_Rate_Info.Step_No = Step;
  SET_STRUCT_SUM(Cur_Rate_Info);  
}

//Ԥ���Ѵ���
void Prepaid_Proc(MEASU_ENERG* pEnergy)
{
  INT32U Pos_Act_Energy, Temp_Energy;
  INT32U Money;
  INT8U Step, Rate;
  static INT32U Eng = 0;
  //DIS_PD_INT;
  
  if(PREPAID_MODE EQ ENERGY_MODE)
  {
    //������Ԥ����,������λ0.001kwh
    Pos_Act_Energy = (pEnergy->Chang_Plus_AcEnerg[3] + pEnergy->Chang_Nega_AcEnerg[3]) / ENERGY_RATIO;
    
    //����ʣ�����
    if(Cur_Energy.Prepaid_Info.Left_Energy > Pos_Act_Energy)
    {
      Cur_Energy.Prepaid_Info.Left_Energy -= Pos_Act_Energy;  
      if(Cur_Energy.Prepaid_Info.Left_Energy / 10 <= Prepaid_Para.Warn_Energy2) //�������޶�
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_LEFT2);
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT2);
      }
      else if(Cur_Energy.Prepaid_Info.Left_Energy / 10 <= Prepaid_Para.Warn_Energy1) //��������һ
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_LEFT1);        
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT1);
      }
      else //�����㹻�����
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_ENOUGH);          
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_ENOUGH);
      }
    }
    else //ʣ����������ۼ�͸֧����
    {
      Cur_Energy.Prepaid_Info.Overdraft_Energy += Pos_Act_Energy - Cur_Energy.Prepaid_Info.Left_Energy;
      Cur_Energy.Prepaid_Info.Left_Energy = 0;
      
      if(Cur_Energy.Prepaid_Info.Overdraft_Energy / 10 >= Prepaid_Para.Overdraft_Energy_Limit) //����͸֧����
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_OVERDRAFT);
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_OVERDRAFT);
      }
      else //����0��û����͸֧����
      {
        /*
        if(PREPAID_ZERO_SWITCH_EN > 0)
        {        
          Prepaid_Status_Proc(PREPAID_ENERGY_ZERO);      
          Prepaid_Ctrl_Proc(PREPAID_ENERGY_ZERO);
        }
        else
        {
          Prepaid_Status_Proc(PREPAID_ENERGY_LEFT2);      
          Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT2);          
        }
        */
        if(Prepaid_Para.Warn_Energy2 != 0) //��������2Ϊ0ʱ������������բ
        {
          Prepaid_Status_Proc(PREPAID_ENERGY_LEFT2);      
          Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT2);          
        }
      }
    }
  }
  else
  {
    //�����Ԥ����
    Check_Prepaid_Para();
    //�����Ԥ�����߹��ĵ���Ӧ�á�PT��CT
    Temp_Energy = ((pEnergy->Chang_Plus_AcEnerg[3] + pEnergy->Chang_Nega_AcEnerg[3]) / ENERGY_RATIO) * Prepaid_Para.CT_Ratio * Prepaid_Para.PT_Ratio;    
    
    if(PREPAID_MONEY_MODE EQ PREPAID_RATE)
      Rate = Cur_Rate_Info.Rate;      
    else
      Rate = 0;    
    
    if(Rate > Multi_Rate_Para.Rates || Rate > MAX_RATES)
    {
      ASSERT_FAILED();
      Rate = 0;
    }
    
    //�ۼƽ���0.01kwh������������
    Pos_Act_Energy = Temp_Energy + (Cur_Energy.Pos_Active[Rate] + Cur_Energy.Neg_Active[Rate]) % 10;
    Pos_Act_Energy = Pos_Act_Energy - Pos_Act_Energy % 10;
    
    Eng += Pos_Act_Energy;
    
    if(PREPAID_MONEY_MODE EQ PREPAID_RATE) //��ʱ�Ʒѷ�ʽ
    {   
      Cur_Energy.Prepaid_Info.Temp_Cumu_Money += Pos_Act_Energy * Rate_Scheme_Para.Fee[Cur_Rate_Info.Rate - 1];
      Money = Cur_Energy.Prepaid_Info.Temp_Cumu_Money / MONEY_RATIO;
      Cur_Energy.Prepaid_Info.Temp_Cumu_Money = Cur_Energy.Prepaid_Info.Temp_Cumu_Money % MONEY_RATIO;
    }
    else  //���ݼƷѷ�ʽ
    {
      Check_Cur_Step(); //��鵱ǰ����ֵ
      Step = Cur_Rate_Info.Step_No;
      if(Step > Prepaid_Para.Step_Num || Step > PREPAID_MAX_STEP)
      {
        ASSERT_FAILED();
        Step = 0;
      }
      
      Cur_Energy.Prepaid_Info.Temp_Cumu_Money += Pos_Act_Energy * Step_Scheme_Para.Step_Fee[Step];
      Money = Cur_Energy.Prepaid_Info.Temp_Cumu_Money / MONEY_RATIO;
      Cur_Energy.Prepaid_Info.Temp_Cumu_Money = Cur_Energy.Prepaid_Info.Temp_Cumu_Money % MONEY_RATIO;
    }

    //////�󸶷ѡ��������õ���///////////////
    Cur_Energy.Prepaid_Info.All_Money += Money; //�ܽ��
    Cur_Energy.Prepaid_Info.Month_Money += Money; //���½��
    //////////////////////////////////////////
    
    //Money = Money * Prepaid_Para.CT_Ratio * Prepaid_Para.PT_Ratio;    
    //����ʣ����
    if(Cur_Energy.Prepaid_Info.Left_Money > Money) 
    {
      Cur_Energy.Prepaid_Info.Left_Money -= Money;
      
      if(Ctrl_Status_Flag.Buy_Money_Switch_Limit_Flag &&\
         (Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Switch_On_Money_Limit)//��ֵ�����ں�բ����
      {
        Prepaid_Status_Proc(PREPAID_MONEY_SWITCH_LIMIT);
        Prepaid_Ctrl_Proc(PREPAID_MONEY_SWITCH_LIMIT);        
      }
      else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money2) //��������2
      {
        Prepaid_Status_Proc(PREPAID_MONEY_LEFT2);
        Prepaid_Ctrl_Proc(PREPAID_MONEY_LEFT2);
      }
      else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money1) //��������1
      {
        Prepaid_Status_Proc(PREPAID_MONEY_LEFT1);        
        Prepaid_Ctrl_Proc(PREPAID_MONEY_LEFT1);     
      }
      else //����㹻
      {
        Prepaid_Status_Proc(PREPAID_MONEY_ENOUGH);        
        Prepaid_Ctrl_Proc(PREPAID_MONEY_ENOUGH);
      }
    } 
    else  //����͸֧���
    {
      Cur_Energy.Prepaid_Info.Overdraft_Money += Money - Cur_Energy.Prepaid_Info.Left_Money; 
      Cur_Energy.Prepaid_Info.Left_Money = 0;
      
      if((Cur_Energy.Prepaid_Info.Overdraft_Money / 10) >= Prepaid_Para.Overdraft_Money_Limit) //����͸֧����
      {
        Prepaid_Status_Proc(PREPAID_MONEY_OVERDRAFT);         
        Prepaid_Ctrl_Proc(PREPAID_MONEY_OVERDRAFT);
      }
      else
      {
        /*
        if(PREPAID_ZERO_SWITCH_EN > 0)
        {
          Prepaid_Status_Proc(PREPAID_MONEY_ZERO);   
          Prepaid_Ctrl_Proc(PREPAID_MONEY_ZERO);
        }
        else
        {
          Prepaid_Status_Proc(PREPAID_MONEY_LEFT2);   
          Prepaid_Ctrl_Proc(PREPAID_MONEY_LEFT2);          
        }
        */
        
        if(Prepaid_Para.Warn_Money2 != 0) //��������2Ϊ0ʱ������������բ
        {
          Prepaid_Status_Proc(PREPAID_MONEY_LEFT2);   
          Prepaid_Ctrl_Proc(PREPAID_MONEY_LEFT2);          
        }
      }
    }
  }

  SET_STRUCT_SUM(Cur_Energy);
  //EN_PD_INT;
}

//����
//PREPAID_MONEY_LEFT1��ʾ��������1
//PREPAID_MONEY_LEFT2��ʾ��������2
//PREPAID_MONEY_ZERO��ʾ͸֧
//PREPAID_MONEY_OVERDRAFT��ʾ��͸֧����
//PREPAID_MONEY_ENOUGH��ʾû�е������ޣ�ʣ�������
//�ú�������PUCK��������Һ����ʾ����˽������͵���ʾҲͳһ��һ����
INT8U Get_Prepaid_Status()
{
  if(PREPAID_EN EQ 0 || PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE)
    return PREPAID_MONEY_ENOUGH;
      
  if(PREPAID_MODE EQ PREPAID_MONEY)
  {
    if((Cur_Energy.Prepaid_Info.Overdraft_Money / 10) >= Prepaid_Para.Overdraft_Money_Limit)
    {
      return PREPAID_MONEY_OVERDRAFT; //��͸֧����
    }
    else if((Cur_Energy.Prepaid_Info.Overdraft_Money / 10) > 0)
    {
      return PREPAID_MONEY_ZERO; //͸֧      
    }
    else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money2)
    {
      return PREPAID_MONEY_LEFT2; //��������1
    }
    else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money1)
    {
      return PREPAID_MONEY_LEFT1; //��������2
    }
    else
      return PREPAID_MONEY_ENOUGH;
  }
  else
  {
    if((Cur_Energy.Prepaid_Info.Overdraft_Energy / 10) >= Prepaid_Para.Overdraft_Energy_Limit)
    {
      return PREPAID_MONEY_OVERDRAFT; //��͸֧����
    }
    else if((Cur_Energy.Prepaid_Info.Overdraft_Energy / 10) > 0)
    {
      return PREPAID_MONEY_ZERO; //͸֧      
    }  
    else if((Cur_Energy.Prepaid_Info.Left_Energy / 10) <= Prepaid_Para.Warn_Energy2)
    {
      return PREPAID_MONEY_LEFT2; //��������1
    }
    else if((Cur_Energy.Prepaid_Info.Left_Energy / 10) <= Prepaid_Para.Warn_Energy1)
    {
      return PREPAID_MONEY_LEFT1; //��������2
    }
    else
      return PREPAID_MONEY_ENOUGH;    
  }
  
  //return PREPAID_MONEY_ENOUGH; 
}

INT32U Get_Money_Hoard_Limit() //��ȡʣ����ڻ����ޣ���λ0.01Ԫ
{
  return Prepaid_Para.Hoard_Money_Limit;
}

INT32U Get_Left_Money() //��ȡʣ����,��λ0.01Ԫ
{
  return Cur_Energy.Prepaid_Info.Left_Money / 10;
}

INT32U Get_Overdraft_Money() //��ȡ͸֧���,��λ0.01Ԫ
{
  return Cur_Energy.Prepaid_Info.Overdraft_Money / 10;
}

INT32U Get_Buy_Eng_Counts() //��ȡ�������
{
  if(PREPAID_MODE EQ PREPAID_MONEY) //�����
    return Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts;
  else
    return Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts;
}


//Ԥ���ѵı�̼�¼,�忨�����ʱ����
void Prepaid_Prog_Record(PROTO_DI PDI, INT8U Op_ID[])
{
  Card_Op_Info.Set_Para_Flag = 1;
  Card_Op_Info.Prog_PDI = PDI;
  mem_cpy((INT8U *)Card_Op_Info.Op_ID, Op_ID, sizeof(Card_Op_Info.Op_ID), (INT8U *)Card_Op_Info.Op_ID, sizeof(Card_Op_Info.Op_ID));
  SET_STRUCT_SUM(Card_Op_Info);
}

//�忨��ǰ����
void Prepaid_Card_Op_Bef_Proc()
{
  Card_Switch_On(); //�忨��բ
  Clr_Card_Op_Info(); //�����ߴ������Ϣ�����
}

//�忨�ĺ���
void Prepaid_Card_Op_Aft_Proc()
{
  INT8U Re;
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Card_Op_Info);
  Re &= CHECK_STRUCT_SUM(Card_Op_Info);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    return;
  }   
  
  if(Card_Op_Info.Set_Para_Flag > 0) //�б�̲���
  {
    Set_Prog_Record(Card_Op_Info.Prog_PDI, (INT8U *)Card_Op_Info.Op_ID);
  }
  
  if(Card_Op_Info.Buy_Eng_Flag EQ BUY_ENG) //�����͹���
    Event_Data_Proc(ID_EVENT_PREPAID_ENERGY, EVENT_OCCUR);
  else if(Card_Op_Info.Buy_Eng_Flag EQ BUY_MONEY) //����͹���
    Event_Data_Proc(ID_EVENT_PREPAID_MONEY, EVENT_OCCUR);    
  else if(Card_Op_Info.Buy_Eng_Flag > 0) 
    ASSERT_FAILED();
  
  //mem_set()
}

void Clr_Card_Op_Info()
{
  mem_set((INT8U *)&Card_Op_Info, 0, sizeof(Card_Op_Info), (INT8U *)&Card_Op_Info, sizeof(Card_Op_Info));
  INIT_STRUCT_VAR(Card_Op_Info); 
  SET_STRUCT_SUM(Card_Op_Info);
}

//����ʣ����͹������
//ʣ��������λС��
void Prepaid_Set_Buy_Money_Counts(INT32U Money, INT32U Counts)
{
  if(PREPAID_MODE EQ PREPAID_MONEY) //�����
  {
    Cur_Energy.Prepaid_Info.Left_Money = Money * 10;
    Cur_Energy.Prepaid_Info.Overdraft_Money = 0;
    Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts = Counts;
  }
  else
  {
    Cur_Energy.Prepaid_Info.Left_Energy = Money * 10;
    Cur_Energy.Prepaid_Info.Overdraft_Energy = 0;    
    Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts = Counts; 
  }
  
  //_Debug_Print("Set_Left_Money:%ld, Counts:%ld", Money, Counts);
  SET_STRUCT_SUM(Cur_Energy);
  
  Save_Cur_Energy_PD_Data();
  Save_Cur_Energy_Data();
}

//��ȡ��������ʱ�䣬TypeΪT_BCD��ʾ��ҪBCD������,T_HEX��ʾHex��������
//pDst����ת���������
//pDst[0]��ʾ��
//pDst[1]��ʾʱ
//pDst[2]��ʾ��
//pDst[3]��ʾ��
//pDst[4]��ʾ��
//����ֵ��ʾʱ�����ݳ���
INT8U Get_Array_Time(INT8U Type, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  mem_cpy(pDst, (INT8U *)Cur_Time0.Time, sizeof(Cur_Time0.Time), pDst_Start, DstLen);    
  
  if(Type EQ T_BCD)
  {
    Hex2Bcd_Buf(pDst, sizeof(Cur_Time0.Time), pDst, pDst_Start, DstLen);
  }
  
  return sizeof(Cur_Time0.Time);
}

//Ԥ���Ѳ忨�޸Ĳ���
void Card_Set_Para_Notice()
{
  Set_Para_Modify(0x04000201); //�����һ����ʶ��֪ͨ������������޸�
}

//void Prepaid_Card_Para_Set(INT8U *pSrc, INT
#undef PREPAID_C
