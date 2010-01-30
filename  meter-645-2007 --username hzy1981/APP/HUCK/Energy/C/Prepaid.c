#define PREPAID_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H9"
#endif

//读取预付费参数
void Read_Prepaid_Para_From_Rom()
{
  INT16U Len;
 
  //电量预付费参数
  Len = Read_Multi_Storage_Data(0x04000F01, 4,(INT8U *)&Prepaid_Para.Warn_Energy1, (INT8U *)&Prepaid_Para, sizeof(Prepaid_Para));
  ASSERT(Len EQ 16);
 
  //电费预付费参数
  Len = Read_Multi_Storage_Data(0x04001001, 5, (INT8U *)&Prepaid_Para.Warn_Money1, (INT8U *)&Prepaid_Para, sizeof(Prepaid_Para));
  ASSERT(Len EQ 20);

  //预付费模式字
  Len = Read_Multi_Storage_Data(SDI_PREPAID_MODEWORD_1, 3, (INT8U *)Prepaid_Para.Mode, (INT8U *)&Prepaid_Para, sizeof(Prepaid_Para));
  ASSERT(Len EQ 3);
  
  //梯度值
  if(PREPAID_EN > 0 && PREPAID_MONEY_MODE EQ PREPAID_STEP)
  {
    Len = Read_Storage_Data(0x04000207, (INT8U *)&Prepaid_Para.Step_Num, (INT8U *)&Prepaid_Para.Step_Num, sizeof(Prepaid_Para.Step_Num));
    ASSERT(Len EQ 1);
  }
  else
  {
    Prepaid_Para.Step_Num = 1;  
  }
  
  //电流互感器变比
  Prepaid_Para.CT_Ratio = 0;
  Len = Read_Storage_Data(0x04000306, (INT8U *)&Prepaid_Para.CT_Ratio, (INT8U *)&Prepaid_Para.CT_Ratio, sizeof(Prepaid_Para.CT_Ratio));
  ASSERT(Len EQ 3);
  
  //电压互感器变比
  Prepaid_Para.PT_Ratio = 0;  
  Len = Read_Storage_Data(0x04000307, (INT8U *)&Prepaid_Para.PT_Ratio, (INT8U *)&Prepaid_Para.PT_Ratio, sizeof(Prepaid_Para.PT_Ratio));
  ASSERT(Len EQ 3);
/*  
  //功率负荷脉冲数
  Prepaid_Para.Power_Puls = 0;
  Len = Read_Storage_Data(0x0400E001, (INT8U *)&Prepaid_Para.Power_Puls, (INT8U *)&Prepaid_Para.Power_Puls, sizeof(Prepaid_Para.Power_Puls));
  ASSERT(Len EQ 3);

  //最大负荷计算时间
  Prepaid_Para.Power_Mins = 0;
  Len = Read_Storage_Data(0x0400E002, (INT8U *)&Prepaid_Para.Power_Mins, (INT8U *)&Prepaid_Para.Power_Mins, sizeof(Prepaid_Para.Power_Mins));
  ASSERT(Len EQ 1);

  //过负荷跳闸次数门限
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

  //当前购电信息初始化
  mem_set((void *)&Cur_Prepaid, 0, sizeof(Cur_Prepaid), (void *)&Cur_Prepaid, sizeof(Cur_Prepaid)); 
  INIT_STRUCT_VAR(Cur_Prepaid);
  SET_STRUCT_SUM(Cur_Prepaid);  
}

//电量型预付费处理
//Eng的单位是0.01kwh
INT8U Prepaid_Buy_Energy_Proc(INT32U Eng)
{
  INT8U Re;
  
  if(PREPAID_MODE != PREPAID_ENG)
    return 0;
  
  Check_Energy_Data_Avail(); //先检查电量数据是否合法
  
  Re = CHECK_STRUCT_SUM(Cur_Prepaid);
  ASSERT(1 EQ Re);
  
  Eng = Eng * 10;
  
  //当次购电量 + 剩余电量 > 囤积电量限值 则不允许
  if(Cur_Energy.Prepaid_Info.Left_Energy + Eng > Prepaid_Para.Hoard_Energy_Limit * 10 + Cur_Energy.Prepaid_Info.Overdraft_Energy)
  {
    Main_Dis_Info("FULL");
    return 0; 
  }
  
  Cur_Prepaid.Energy = Eng; //当次购电量
  Cur_Prepaid.Bef_Left_Energy = Cur_Energy.Prepaid_Info.Left_Energy; //当此购电钱剩余电量
  SET_STRUCT_SUM(Cur_Prepaid);
  
  DIS_PD_INT;
  
  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts ++; //总购电次数
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
  
  if((Cur_Energy.Prepaid_Info.Left_Energy / 10) < Prepaid_Para.Warn_Energy2) //在报警门限2内，认为手动合闸了
    Ctrl_Status_Flag.Card_Switch_On_Flag = 1; //购电成功后清除插卡标志
  else
    Ctrl_Status_Flag.Card_Switch_On_Flag = 0; //购电成功后清除插卡标志
  SET_STRUCT_SUM(Ctrl_Status_Flag);
  
  SET_STRUCT_SUM(Cur_Energy);
  
  EN_PD_INT;
  Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));  
  Save_Cur_Energy_PD_Data(); //保存当前电量数据
  Save_Cur_Energy_Data();
  //Event_Data_Proc(ID_EVENT_PREPAID_ENERGY, EVENT_OCCUR);
  Card_Op_Info.Buy_Eng_Flag = BUY_ENG;
  SET_STRUCT_SUM(Card_Op_Info);
  
  ENABLE_BEEP_ALARM;
  return 1;
}

//判断购电金额是否超限,返回0表示没有超，1表示超
//Money单位为0.01元
INT8U Check_Buy_Money_Exceed_Limit(INT32U Money)
{
  if(Cur_Energy.Prepaid_Info.Left_Money  + Money * 10 > Prepaid_Para.Hoard_Money_Limit * 10 + Cur_Energy.Prepaid_Info.Overdraft_Money) //超过囤积金额上限
  {
    ASSERT_FAILED();
    return 1; 
  }  
  else
    return 0;
}

//获取参数设置卡需要设置的费率参数的存储DI
//设置方案1参数，1表示当前套，2表示备用套
//Scheme 1表示更新当前套参数,2表示备用套参数
//返回需要存储的DI
STORA_DI Get_Card_Set_Rate_Scheme_SDI(INT8U Scheme)
{
  if(Scheme EQ 1) //当前费率
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

//电费型预付费处理
//Money单位时0.01元
INT8U Prepaid_Buy_Money_Proc(INT32U Money)
{
  INT8U Re;

  if(PREPAID_MODE != PREPAID_MONEY)
    return 0;
  
  Check_Energy_Data_Avail(); //先检查电量数据是否合法
  
  Re = CHECK_STRUCT_SUM(Cur_Prepaid);
  ASSERT(1 EQ Re);
  
  if(Check_Buy_Money_Exceed_Limit(Money))
    return 0;
  
  Money = Money * 10;
    
  Cur_Prepaid.Money = Money; //当次购电量
  Cur_Prepaid.Bef_Left_Money = Cur_Energy.Prepaid_Info.Left_Money; //当此购电钱剩余电量
  SET_STRUCT_SUM(Cur_Prepaid);
  
  DIS_PD_INT;
  
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts ++; //总购电次数
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
  
  if(Cur_Energy.Prepaid_Info.Left_Money >= Prepaid_Para.Switch_On_Money_Limit * 10) //达到合闸允许金额了?
    Ctrl_Status_Flag.Buy_Money_Switch_Limit_Flag = 0;
  else
    Ctrl_Status_Flag.Buy_Money_Switch_Limit_Flag = 1;
  
  if((Cur_Energy.Prepaid_Info.Left_Money / 10) < Prepaid_Para.Warn_Money2) //在报警门限2内，认为手动合闸了
    Ctrl_Status_Flag.Card_Switch_On_Flag = 1; //购电成功后清除插卡标志
  else
    Ctrl_Status_Flag.Card_Switch_On_Flag = 0; //购电成功后清除插卡标志
  
  Ctrl_Status_Flag.Hand_Switch_On_Flag = 0; //插卡购电成功认为就是手动合闸一次
  
  SET_STRUCT_SUM(Ctrl_Status_Flag);
  SET_STRUCT_SUM(Cur_Energy);
  
  EN_PD_INT;
  Write_Storage_Data(_SDI_CTRL_STATUS_FLAG, (INT8U *)&Ctrl_Status_Flag, sizeof(Ctrl_Status_Flag));
  Save_Cur_Energy_PD_Data(); //保存当前电量数据
  Save_Cur_Energy_Data();  
  
  Card_Op_Info.Buy_Eng_Flag = BUY_MONEY;
  SET_STRUCT_SUM(Card_Op_Info);
  
  ENABLE_BEEP_ALARM;
  return 1;
  
}



/*
//清除插卡标志
void Clear_Prepaid_Insert_Card_Flag()
{
  Ctrl_Status_Flag.Card_Switch_On_Flag = 0;
  SET_STRUCT_SUM(Ctrl_Status_Flag);
 
}
*/
//设置预付费当前电能、电费状态
void Prepaid_Status_Proc(INT8U Status)
{
  if(Status != Cur_Energy.Prepaid_Info.Eng_Money_Status)
  {
    Cur_Energy.Prepaid_Info.Eng_Money_Status = Status;
    //Cur_Energy.Prepaid_Info.Card_Switch_On_Flag = 0;
  }
}

//预付费的月电量和月金额清零--该函数内部会关闭打开掉电中断!
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
  
  //上一结算周期的
  Cur_Energy.Prepaid_Info.Last_Month_Pos_Act = Cur_Energy.Prepaid_Info.Month_Pos_Act;
  Cur_Energy.Prepaid_Info.Last_Month_Neg_Act = Cur_Energy.Prepaid_Info.Month_Neg_Act;  
  
  //月电量的正向有功和反向有功的最后一位应保持一致，因为阶梯计费是从总电量的增加上减的，如果不保持一致
  //可能从显示上计算精度，可能超过误差允许范围
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
  
  if(memcmp(pTime, (S_HEX_Time *)&Cur_Energy.Prepaid_Info.Time, sizeof(S_HEX_Time)) != 0)  //防止重复清月电量
  {
    //_Debug_Print("Clr Prepaid Eng");
    //Print_HEX_Time(pTime);
    //Print_HEX_Time(&TempTime);
    //_Debug_Print("Cur_Month Active:%ld", Cur_Energy.Prepaid_Info.Month_Pos_Act);
    Prepaid_Clr_Month_Eng_Money(pTime);
  }  
}

//检查是否需要清除当前月电量
void Prepaid_Clr_Month_Eng_Chk(S_HEX_Time *pTime)
{
  S_HEX_Time TempTime;
  
  if(Check_HEX_Time(pTime) EQ 0)
    return;
  
  //当前时间和前一次清零时间如果超过了一个结算周期，则需要清零
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

//检查当前的阶梯
void Check_Cur_Step()
{
  INT8U Step, i;
  INT32U Min, Temp_Energy;
  
  //计算当前在哪个预付费阶梯
  Min = 0xFFFFFFFF;
  Step = Prepaid_Para.Step_Num;

  //计算当前电量处于哪一个阶梯范围
  for(i = 0; i < Prepaid_Para.Step_Num && i < PREPAID_MAX_STEP; i ++)
  {
    Temp_Energy = Step_Scheme_Para.Step_Energy[i] * 10; //当月电能单位是0.001kwh,Step单位是0.01kwh，因此×10
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

//预付费处理
void Prepaid_Proc(MEASU_ENERG* pEnergy)
{
  INT32U Pos_Act_Energy, Temp_Energy;
  INT32U Money;
  INT8U Step, Rate;
  static INT32U Eng = 0;
  //DIS_PD_INT;
  
  if(PREPAID_MODE EQ ENERGY_MODE)
  {
    //电量型预付费,电量单位0.001kwh
    Pos_Act_Energy = (pEnergy->Chang_Plus_AcEnerg[3] + pEnergy->Chang_Nega_AcEnerg[3]) / ENERGY_RATIO;
    
    //计算剩余电量
    if(Cur_Energy.Prepaid_Info.Left_Energy > Pos_Act_Energy)
    {
      Cur_Energy.Prepaid_Info.Left_Energy -= Pos_Act_Energy;  
      if(Cur_Energy.Prepaid_Info.Left_Energy / 10 <= Prepaid_Para.Warn_Energy2) //低于门限二
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_LEFT2);
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT2);
      }
      else if(Cur_Energy.Prepaid_Info.Left_Energy / 10 <= Prepaid_Para.Warn_Energy1) //低于门限一
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_LEFT1);        
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT1);
      }
      else //电能足够的情况
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_ENOUGH);          
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_ENOUGH);
      }
    }
    else //剩余电量不足累加透支电量
    {
      Cur_Energy.Prepaid_Info.Overdraft_Energy += Pos_Act_Energy - Cur_Energy.Prepaid_Info.Left_Energy;
      Cur_Energy.Prepaid_Info.Left_Energy = 0;
      
      if(Cur_Energy.Prepaid_Info.Overdraft_Energy / 10 >= Prepaid_Para.Overdraft_Energy_Limit) //超过透支门限
      {
        Prepaid_Status_Proc(PREPAID_ENERGY_OVERDRAFT);
        Prepaid_Ctrl_Proc(PREPAID_ENERGY_OVERDRAFT);
      }
      else //低于0但没超过透支门限
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
        if(Prepaid_Para.Warn_Energy2 != 0) //报警门限2为0时不报警、不跳闸
        {
          Prepaid_Status_Proc(PREPAID_ENERGY_LEFT2);      
          Prepaid_Ctrl_Proc(PREPAID_ENERGY_LEFT2);          
        }
      }
    }
  }
  else
  {
    //电费型预付费
    Check_Prepaid_Para();
    //电费型预付费走过的电量应该×PT×CT
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
    
    //累计金额按照0.01kwh的整数倍进行
    Pos_Act_Energy = Temp_Energy + (Cur_Energy.Pos_Active[Rate] + Cur_Energy.Neg_Active[Rate]) % 10;
    Pos_Act_Energy = Pos_Act_Energy - Pos_Act_Energy % 10;
    
    Eng += Pos_Act_Energy;
    
    if(PREPAID_MONEY_MODE EQ PREPAID_RATE) //分时计费方式
    {   
      Cur_Energy.Prepaid_Info.Temp_Cumu_Money += Pos_Act_Energy * Rate_Scheme_Para.Fee[Cur_Rate_Info.Rate - 1];
      Money = Cur_Energy.Prepaid_Info.Temp_Cumu_Money / MONEY_RATIO;
      Cur_Energy.Prepaid_Info.Temp_Cumu_Money = Cur_Energy.Prepaid_Info.Temp_Cumu_Money % MONEY_RATIO;
    }
    else  //阶梯计费方式
    {
      Check_Cur_Step(); //检查当前阶梯值
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

    //////后付费、计算总用电金额///////////////
    Cur_Energy.Prepaid_Info.All_Money += Money; //总金额
    Cur_Energy.Prepaid_Info.Month_Money += Money; //当月金额
    //////////////////////////////////////////
    
    //Money = Money * Prepaid_Para.CT_Ratio * Prepaid_Para.PT_Ratio;    
    //计算剩余金额
    if(Cur_Energy.Prepaid_Info.Left_Money > Money) 
    {
      Cur_Energy.Prepaid_Info.Left_Money -= Money;
      
      if(Ctrl_Status_Flag.Buy_Money_Switch_Limit_Flag &&\
         (Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Switch_On_Money_Limit)//充值金额低于合闸门限
      {
        Prepaid_Status_Proc(PREPAID_MONEY_SWITCH_LIMIT);
        Prepaid_Ctrl_Proc(PREPAID_MONEY_SWITCH_LIMIT);        
      }
      else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money2) //低于门限2
      {
        Prepaid_Status_Proc(PREPAID_MONEY_LEFT2);
        Prepaid_Ctrl_Proc(PREPAID_MONEY_LEFT2);
      }
      else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money1) //低于门限1
      {
        Prepaid_Status_Proc(PREPAID_MONEY_LEFT1);        
        Prepaid_Ctrl_Proc(PREPAID_MONEY_LEFT1);     
      }
      else //金额足够
      {
        Prepaid_Status_Proc(PREPAID_MONEY_ENOUGH);        
        Prepaid_Ctrl_Proc(PREPAID_MONEY_ENOUGH);
      }
    } 
    else  //计算透支金额
    {
      Cur_Energy.Prepaid_Info.Overdraft_Money += Money - Cur_Energy.Prepaid_Info.Left_Money; 
      Cur_Energy.Prepaid_Info.Left_Money = 0;
      
      if((Cur_Energy.Prepaid_Info.Overdraft_Money / 10) >= Prepaid_Para.Overdraft_Money_Limit) //超过透支上限
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
        
        if(Prepaid_Para.Warn_Money2 != 0) //报警门限2为0时不报警，不跳闸
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

//返回
//PREPAID_MONEY_LEFT1表示低于门限1
//PREPAID_MONEY_LEFT2表示低于门限2
//PREPAID_MONEY_ZERO表示透支
//PREPAID_MONEY_OVERDRAFT表示超透支门限
//PREPAID_MONEY_ENOUGH表示没有低于门限，剩余金额充足
//该函数用于PUCK调用用于液晶显示，因此将电量型的显示也统一到一起来
INT8U Get_Prepaid_Status()
{
  if(PREPAID_EN EQ 0 || PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE)
    return PREPAID_MONEY_ENOUGH;
      
  if(PREPAID_MODE EQ PREPAID_MONEY)
  {
    if((Cur_Energy.Prepaid_Info.Overdraft_Money / 10) >= Prepaid_Para.Overdraft_Money_Limit)
    {
      return PREPAID_MONEY_OVERDRAFT; //超透支门限
    }
    else if((Cur_Energy.Prepaid_Info.Overdraft_Money / 10) > 0)
    {
      return PREPAID_MONEY_ZERO; //透支      
    }
    else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money2)
    {
      return PREPAID_MONEY_LEFT2; //低于门限1
    }
    else if((Cur_Energy.Prepaid_Info.Left_Money / 10) <= Prepaid_Para.Warn_Money1)
    {
      return PREPAID_MONEY_LEFT1; //低于门限2
    }
    else
      return PREPAID_MONEY_ENOUGH;
  }
  else
  {
    if((Cur_Energy.Prepaid_Info.Overdraft_Energy / 10) >= Prepaid_Para.Overdraft_Energy_Limit)
    {
      return PREPAID_MONEY_OVERDRAFT; //超透支门限
    }
    else if((Cur_Energy.Prepaid_Info.Overdraft_Energy / 10) > 0)
    {
      return PREPAID_MONEY_ZERO; //透支      
    }  
    else if((Cur_Energy.Prepaid_Info.Left_Energy / 10) <= Prepaid_Para.Warn_Energy2)
    {
      return PREPAID_MONEY_LEFT2; //低于门限1
    }
    else if((Cur_Energy.Prepaid_Info.Left_Energy / 10) <= Prepaid_Para.Warn_Energy1)
    {
      return PREPAID_MONEY_LEFT1; //低于门限2
    }
    else
      return PREPAID_MONEY_ENOUGH;    
  }
  
  //return PREPAID_MONEY_ENOUGH; 
}

INT32U Get_Money_Hoard_Limit() //获取剩余金额囤积门限，单位0.01元
{
  return Prepaid_Para.Hoard_Money_Limit;
}

INT32U Get_Left_Money() //获取剩余金额,单位0.01元
{
  return Cur_Energy.Prepaid_Info.Left_Money / 10;
}

INT32U Get_Overdraft_Money() //获取透支金额,单位0.01元
{
  return Cur_Energy.Prepaid_Info.Overdraft_Money / 10;
}

INT32U Get_Buy_Eng_Counts() //获取购电次数
{
  if(PREPAID_MODE EQ PREPAID_MONEY) //电费型
    return Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts;
  else
    return Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts;
}


//预付费的编程记录,插卡设参数时定义
void Prepaid_Prog_Record(PROTO_DI PDI, INT8U Op_ID[])
{
  Card_Op_Info.Set_Para_Flag = 1;
  Card_Op_Info.Prog_PDI = PDI;
  mem_cpy((INT8U *)Card_Op_Info.Op_ID, Op_ID, sizeof(Card_Op_Info.Op_ID), (INT8U *)Card_Op_Info.Op_ID, sizeof(Card_Op_Info.Op_ID));
  SET_STRUCT_SUM(Card_Op_Info);
}

//插卡的前处理
void Prepaid_Card_Op_Bef_Proc()
{
  Card_Switch_On(); //插卡合闸
  Clr_Card_Op_Info(); //操作者代码等信息的清除
}

//插卡的后处理
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
  
  if(Card_Op_Info.Set_Para_Flag > 0) //有编程操作
  {
    Set_Prog_Record(Card_Op_Info.Prog_PDI, (INT8U *)Card_Op_Info.Op_ID);
  }
  
  if(Card_Op_Info.Buy_Eng_Flag EQ BUY_ENG) //电量型购电
    Event_Data_Proc(ID_EVENT_PREPAID_ENERGY, EVENT_OCCUR);
  else if(Card_Op_Info.Buy_Eng_Flag EQ BUY_MONEY) //电费型购电
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

//设置剩余金额和购电次数
//剩余金额是两位小数
void Prepaid_Set_Buy_Money_Counts(INT32U Money, INT32U Counts)
{
  if(PREPAID_MODE EQ PREPAID_MONEY) //电费型
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

//获取数据类型时间，Type为T_BCD表示需要BCD类数据,T_HEX表示Hex类型数据
//pDst放置转换后的数据
//pDst[0]表示分
//pDst[1]表示时
//pDst[2]表示日
//pDst[3]表示月
//pDst[4]表示年
//返回值表示时间数据长度
INT8U Get_Array_Time(INT8U Type, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  mem_cpy(pDst, (INT8U *)Cur_Time0.Time, sizeof(Cur_Time0.Time), pDst_Start, DstLen);    
  
  if(Type EQ T_BCD)
  {
    Hex2Bcd_Buf(pDst, sizeof(Cur_Time0.Time), pDst, pDst_Start, DstLen);
  }
  
  return sizeof(Cur_Time0.Time);
}

//预付费插卡修改参数
void Card_Set_Para_Notice()
{
  Set_Para_Modify(0x04000201); //随便设一个标识，通知其他任务参数修改
}

//void Prepaid_Card_Para_Set(INT8U *pSrc, INT
#undef PREPAID_C
