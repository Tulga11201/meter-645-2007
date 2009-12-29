#define ENERGY_C
#include "Includes.h"

//extern void Event_Energy_Cumu(MEASU_ENERG *pEnergy);
volatile MEASU_ENERG Accu_Energy;
extern void Prepaid_Proc(MEASU_ENERG* pEnergy);
//表征内存是否掉过电，掉过返回POWER_ON否则返回RESET
//检查当前是上电还是复位, 实际上该函数是判断内存中的数据在复位后是否有变化，即是否发生了掉电之类
//上电返回POWER_ON, 复位返回RESET
//该函数检查Power_On_Flag.Flag[]是不是每个都是0x55
INT8U Check_Rst_Flag()
{
  INT8U i, Re;

  static S_Int32U Flag = {CHK_BYTE, 0x55, CHK_BYTE};//0x55表示第一次进入该函数, 0xAA表示不是第一次进入, 其他值表示错误, 记录是否是上电后第一次进入该函数
  static S_Int32U Power_Flag = {CHK_BYTE, SOFT_RST, CHK_BYTE};//复位或上电标志

  TRACE();
  Re = CHECK_STRUCT_VAR(Flag);
  ASSERT(1 EQ Re);

  if(0x55 EQ Flag.Var)//第一次进入该函数
  {
    Flag.Var = 0xAA;//置0xAA，以后再调用该函数就不会再进入该流程了
    Power_Flag.Var = SOFT_RST;//默认是复位
    for(i = 0; i < S_NUM(Power_On_Flag.Flag); i++)
    {
      if(Power_On_Flag.Flag[i] != 0x55)//有一个不是0x55说明是上电
      {
        Power_Flag.Var = POWER_ON_RST;
        break;
      }
    }
    //Power_Flag EQ RESET而且Power_On_Flag的校验和正确, 认为是软复位
    if(Power_Flag.Var EQ SOFT_RST && CHECK_STRUCT_SUM(Power_On_Flag))
      Power_Flag.Var = SOFT_RST;
    else
      Power_Flag.Var = POWER_ON_RST;

    //Power_On_Flag.Flag都置成0x55，下次复位或上电可查看该标志
    mem_set((void *) Power_On_Flag.Flag, 0x55, sizeof(Power_On_Flag.Flag), (void *) Power_On_Flag.Flag, sizeof(Power_On_Flag.Flag));
    SET_STRUCT_SUM(Power_On_Flag);

    return Power_Flag.Var;
  }
  else if(0xAA EQ Flag.Var)//已经不是第一次进入该函数
  {
    Re = CHECK_STRUCT_VAR(Power_Flag);
    ASSERT(1 EQ Re);

    if(Power_Flag.Var EQ SOFT_RST || Power_Flag.Var EQ POWER_ON_RST)
      return Power_Flag.Var;
    else
    {
      ASSERT_FAILED();
      return POWER_ON_RST;
    }
  }
  else
  {
    ASSERT_FAILED();
    return POWER_ON_RST;
  }
}

//检查电量参数的合法性
void Check_Energy_Para_Avil()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Mode_Word);
  Re &= CHECK_STRUCT_SUM(Mode_Word);
  
  Re &= CHECK_STRUCT_VAR(Energy_Comb_Word);
  Re &= CHECK_STRUCT_SUM(Energy_Comb_Word);
  Re &= CHECK_STRUCT_VAR(_Date_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Date_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_VAR(_Year_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Year_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_VAR(_Rate_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Rate_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_VAR(_Step_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Step_Scheme_Switch_Time);

  Re &= CHECK_STRUCT_VAR(Multi_Rate_Para);
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);
  Re &= CHECK_STRUCT_VAR(Year_Table);
  Re &= CHECK_STRUCT_SUM(Year_Table);
  Re &= CHECK_STRUCT_VAR(Date_Table);
  Re &= CHECK_STRUCT_SUM(Date_Table);

  Re &= CHECK_STRUCT_SUM(Cur_Scheme);
  Re &= CHECK_STRUCT_VAR(Cur_Scheme);
  
  Re &= CHECK_STRUCT_SUM(Prepaid_Para);
  Re &= CHECK_STRUCT_VAR(Prepaid_Para);
  Re &= CHECK_STRUCT_VAR(Rate_Scheme_Para);
  Re &= CHECK_STRUCT_SUM(Rate_Scheme_Para);
  Re &= CHECK_STRUCT_VAR(Step_Scheme_Para);
  Re &= CHECK_STRUCT_SUM(Step_Scheme_Para);
  
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Read_Energy_Para_From_Rom();
  }//重新读取电量参数!!

  //判断费率信息头，不要放上面，因为Read_Energy_Para不会置其头尾
  Re = CHECK_STRUCT_VAR(Cur_Rate_Info);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  Check_Multi_Rate_Para();//检查复费率参数的合法性
  Check_Prepaid_Para();
  Check_Cur_Scheme_Info();
}

//检查电量参数的逻辑性，并纠正之
void Check_Energy_Para()
{
	TRACE();
}

//读取当前方案
void Read_Cur_Scheme_From_Rom()
{
  INT8U Len;
  //INT8U Temp[5];
  
  TRACE();

  Len = Read_Storage_Data(_SDI_CUR_SCHEME, (void *) &Cur_Scheme, (void *) &Cur_Scheme, sizeof(Cur_Scheme));  
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    //mem_cpy(&Cur_Scheme, Def_Cur_Scheme, sizeof(Def_Cur_Scheme), &Cur_Scheme, sizeof(Cur_Scheme));
  }
  
  INIT_STRUCT_VAR(Cur_Scheme); 
  SET_STRUCT_SUM(Cur_Scheme);
  
  Check_Cur_Scheme_Info();
}


//从ROM空间中读取模式字
void Read_Mode_Word()
{

   INT8U i;
   INT16U Len;
   //STORA_DI SDI = SDI_MODEWORD_1;
   
   //读取模式字1-5
   for(i = 0; i < 5; i++)
   {
     //如果读取模式字失败了则采用默认的模式字
     Len = Read_Storage_Data(SDI_MODEWORD_1 + i, (INT8U *)&Mode_Word.Mode[i], (INT8U *) Mode_Word.Mode, sizeof(Mode_Word.Mode));
     ASSERT(1 EQ Len);
   }

  INIT_STRUCT_VAR(Mode_Word);
  SET_STRUCT_SUM(Mode_Word);
  
  Read_Energy_Comb_Word(); //读取有无功组合模式字
}

//读取年时区表切换时刻
void Read_Year_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //读取年时区表切换时刻
  Len = Read_Storage_Data(SDI_YEAR_SCHE_CHG_TIME, (INT8U *) Year_Scheme_Switch_Time.Time, (INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  if(5 != Len)
  {
    ASSERT_FAILED();
    Debug_Print("Read Year_Scheme_Switch_Time Error"); 
    //默认切换时刻，全是0xFF
    mem_cpy((INT8U *) Year_Scheme_Switch_Time.Time, (void *) Def_04000106, 5,\
			(INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Year_Scheme_Switch_Time.Time, 5) EQ 1)//确实是BCD时间数据,否则可能是全FF(默认参数)
  {
    Bcd2Hex_Buf((INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time), (INT8U *) Year_Scheme_Switch_Time.Time, (INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  }
  else //默认切换时刻，全是0xFF
  {
    mem_cpy((INT8U *) Year_Scheme_Switch_Time.Time, (void *) Def_04000106, 5,\
			(INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  }

  INIT_STRUCT_VAR(_Year_Scheme_Switch_Time);
  SET_STRUCT_SUM(Year_Scheme_Switch_Time);
}

//读取日时段表切换时刻
void Read_Date_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //读取主副日时段表切换时刻
  Len = Read_Storage_Data(SDI_DATE_SCHE_CHG_TIME, (INT8U *) Date_Scheme_Switch_Time.Time, (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  if(5 != Len)//ASSERT(5 EQ Len))
  {
    ASSERT_FAILED();
    Debug_Print("Read Date_Scheme_Switch_Time Error");
    //使用默认的主负日时段表时刻,都是0xFF
    mem_cpy((INT8U *) Date_Scheme_Switch_Time.Time, (void *) Def_04000107, 5,\
	    (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Date_Scheme_Switch_Time.Time, 5) EQ 1)//确实是BCD时间数据, 否则可能是全FF(默认参数)
  {
    Bcd2Hex_Buf((INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time), (INT8U *) Date_Scheme_Switch_Time.Time, \
                (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  }
  else
  {
    mem_cpy((INT8U *) Date_Scheme_Switch_Time.Time, (void *) Def_04000107, 5,\
	    (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  }

  INIT_STRUCT_VAR(_Date_Scheme_Switch_Time);  
  SET_STRUCT_SUM(Date_Scheme_Switch_Time);
}

//读取费率方案切换时刻
void Read_Rate_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //读取主副费率方案切换时刻
  Len = Read_Storage_Data(SDI_RATE_SCHE_CHG_TIME, (INT8U *) Rate_Scheme_Switch_Time.Time, (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  if(5 != Len)//ASSERT(5 EQ Len))
  {
    ASSERT_FAILED();
    Debug_Print("Read Rate_Scheme_Switch_Time Error");
    //使用默认的主负费率切换时刻,都是0xFF
    mem_cpy((INT8U *) Rate_Scheme_Switch_Time.Time, (void *) Def_04000108, 5,\
	    (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Rate_Scheme_Switch_Time.Time, 5) EQ 1)//确实是BCD时间数据, 否则可能是全FF(默认参数)
  {
    Bcd2Hex_Buf((INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time), (INT8U *) Rate_Scheme_Switch_Time.Time, \
                (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  }
  else
  {
    mem_cpy((INT8U *) Rate_Scheme_Switch_Time.Time, (void *) Def_04000108, 5,\
	    (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  }
  
  INIT_STRUCT_VAR(_Rate_Scheme_Switch_Time);
  SET_STRUCT_SUM(Rate_Scheme_Switch_Time);
}

//读取阶梯方案切换时刻
void Read_Step_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //读取主副日时段表切换时刻
  Len = Read_Storage_Data(SDI_STEP_SCHE_CHG_TIME, (INT8U *) Step_Scheme_Switch_Time.Time, (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  if(5 != Len)//ASSERT(5 EQ Len))
  {
    ASSERT_FAILED();
    Debug_Print("Read Step_Scheme_Switch_Time Error");
    //使用默认的主负费率切换时刻,都是0xFF
    mem_cpy((INT8U *) Step_Scheme_Switch_Time.Time, (void *) Def_04000109, 5,\
	    (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Step_Scheme_Switch_Time.Time, 5) EQ 1)//确实是BCD时间数据, 否则可能是全FF(默认参数)
  {
    Bcd2Hex_Buf((INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time), (INT8U *) Step_Scheme_Switch_Time.Time, \
                (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  }
  else
  {
    mem_cpy((INT8U *) Step_Scheme_Switch_Time.Time, (void *) Def_04000109, 5,\
	    (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  }
  
  INIT_STRUCT_VAR(_Step_Scheme_Switch_Time);
  SET_STRUCT_SUM(Step_Scheme_Switch_Time);
}

#if SCHEME_SWITCH_MODE == 0
/*
//计算当前应该使用的费率方案, 如果Flag EQ CALC_ROM则重新从ROM中读取参数计算但前的费率方案
//同时如果费率方按发生了切换，则函数内部进行切换相关的处理
// 当前应该采用主费率方案则返回YEAR_SCHEME0, 否则返回YEAR_SCHEME1
//该函数的主要作用是判断是否产生费率切换
//费率方案切换的话调用Year_Scheme_Changed_Proc进行相关处理
INT8U Calc_Cur_Year_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  if(CALC_ROM EQ Flag)//表示从ROM中重新读取相关数据，进行计算
  {
    Read_Multi_Rate_Para(); //先读取费率相关参数 
    Read_Year_Scheme_Switch_Time();
  }

  //检查内存中相关变量的正确性
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//检查Cur_Time0时间
  Re &= CHECK_STRUCT_SUM(Mode_Word);//检查模式字是否允许费率切换
  Re &= CHECK_STRUCT_SUM(Year_Scheme_Switch_Time);//检查费率切换时间
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//检查当前费率信息
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(YEAR_TABLE_SWITCH_EN EQ 1)//是否允许切换费率方案?
  {
    if(_Check_HEX_Time((INT8U *) Year_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Year_Scheme_Switch_Time);//当前时间是否在费率切换时间之后?
      if(Re != TIME_BEF)//当前时间在费率方案切换时间之后
        Scheme = YEAR_SCHEME1;//当前应采用副费率方案
      else
        Scheme = YEAR_SCHEME0;
    }
    else//不允许的情况下，默认使用套费率方案0
    {
      Scheme = YEAR_SCHEME0;
    }
  }
  else
    Scheme = YEAR_SCHEME0; 

  //和当前使用的费率方案不一致，应该切换费率方案
  //使用ROM中参数计算费率方案时，强制认为发生了一次费率切换, 以免出错
  if(Cur_Rate_Info.Year_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Year_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Year_Scheme_Changed_Proc();//年时区方案切换处理
    
    Calc_Cur_Date_Scheme(CALC_ROM);
    
    if(Cur_Scheme.Year_Scheme != Scheme)
    {
      Debug_Print("Cur_Year_Scheme Changed!");
      Cur_Scheme.Year_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_YEAR_TABLE_SWITCH_FREEZE, EVENT_OCCUR);      
    }
  }
  return Scheme;
}

//计算当前日时段表方案
//Flag EQ CALC_ROM表示从ROM中读取参数强制判断一次当前套方案
//Flag EQ CALC_RAM表示使用内存中参数进行一次判断当前方案
INT8U Calc_Cur_Date_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //读取主副日时段表切换时刻
  if(CALC_ROM EQ Flag)//表示从ROM中重新读取相关数据，进行计算
  {
    Read_Date_Scheme_Switch_Time();
  }

  //检查内存中相关变量的正确性
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//检查Cur_Time0时间
  Re &= CHECK_STRUCT_SUM(Mode_Word);//检查模式字是否允许费率切换
  Re &= CHECK_STRUCT_SUM(Date_Scheme_Switch_Time);//检查两套日时段表切换时间
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//检查当前费率信息
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(DATE_TABLE_SWITCH_EN EQ 1)//是否允许切换日时段表方案?
  {
    if(_Check_HEX_Time((INT8U *) Date_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Date_Scheme_Switch_Time);//当前时间是否在费率切换时间之后?
      if(Re != TIME_BEF)//当前时间在费率方案切换时间之后
        Scheme = DATE_SCHEME1;//当前应采用副费率方案
      else
        Scheme = DATE_SCHEME0;
    }
    else//不允许的情况下，默认使用套费率方案0
    {
      Scheme = DATE_SCHEME0;
    }
  }
  else
    Scheme = DATE_SCHEME0;

  //和当前使用的费率方案不一致，应该切换费率方案
  //使用ROM中参数计算费率方案时，强制认为发生了一次费率切换, 以免出错
  if(Cur_Rate_Info.Date_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Date_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Date_Scheme_Changed_Proc();//费率方案切换处理
    
    if(Cur_Scheme.Date_Scheme != Scheme)
    {
      Debug_Print("Cur_Date_Scheme Changed!");
      Cur_Scheme.Date_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_DATE_TABLE_SWITCH_FREEZE, EVENT_OCCUR);      
    }
  }
  return Scheme;
}
*/
#else
//计算当前应该使用的费率方案, 如果Flag EQ CALC_ROM则重新从ROM中读取参数计算但前的费率方案
//同时如果费率方按发生了切换，则函数内部进行切换相关的处理
// 当前应该采用主费率方案则返回YEAR_SCHEME0, 否则返回YEAR_SCHEME1
//该函数的主要作用是判断是否产生费率切换
//费率方案切换的话调用Year_Scheme_Changed_Proc进行相关处理
INT8U Calc_Cur_Year_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  if(CALC_ROM EQ Flag)//表示从ROM中重新读取相关数据，进行计算
  {
    Read_Year_Scheme_Switch_Time(); //读取年时区切换时间
  }

  //检查内存中相关变量的正确性
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//检查Cur_Time0时间
  Re &= CHECK_STRUCT_SUM(Mode_Word);//检查模式字是否允许费率切换
  Re &= CHECK_STRUCT_SUM(Year_Scheme_Switch_Time);//检查费率切换时间
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//检查当前费率信息
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Year_Scheme;
  
  if(YEAR_TABLE_SWITCH_EN EQ 1)//是否允许切换年时区方案?
  {
    if(_Check_HEX_Time((INT8U *) Year_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Year_Scheme_Switch_Time);//当前时间是否在费率切换时间之后?
      if(Re != TIME_BEF)//当前时间在费率方案切换时间之后
      {
        if(Cur_Scheme.Year_Scheme_Time EQ BEF_SWITCH_TIME)//前一次的判断时间在切换时间以前,则必须发生一次切换
        {
          if(Cur_Scheme.Year_Scheme EQ YEAR_SCHEME1)
            Scheme = YEAR_SCHEME0;
          else
            Scheme = YEAR_SCHEME1;
          
          Cur_Scheme.Year_Scheme_Time = AFT_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //将年时区切换时间置0
          mem_set((INT8U *) Year_Scheme_Switch_Time.Time, 0, sizeof(Year_Scheme_Switch_Time.Time),\
                  (INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Year_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_YEAR_SCHE_CHG_TIME, (INT8U *)Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));          
        }
      }
      else
      {
        //切换时间往前调?
        if(Cur_Scheme.Year_Scheme_Time EQ AFT_SWITCH_TIME)//前一次的判断时间在切换时间以后,则必须发生一次切换
        {  
          Cur_Scheme.Year_Scheme_Time = BEF_SWITCH_TIME;//当前在切换时间以前了
          SET_STRUCT_SUM(Cur_Scheme); 
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
        }       
      }
    }
  }

  //和当前使用的费率方案不一致，应该切换费率方案
  //使用ROM中参数计算费率方案时，强制认为发生了一次费率切换, 以免出错
  if(Cur_Rate_Info.Year_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Year_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Year_Scheme_Changed_Proc();//年时区方案切换处理
    
    Calc_Cur_Date_Scheme(CALC_ROM);
    
    if(Cur_Scheme.Year_Scheme != Scheme)
    {
      Debug_Print("Cur_Year_Scheme Changed!");
      Cur_Scheme.Year_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_YEAR_TABLE_SWITCH_FREEZE, EVENT_OCCUR);      
    }    
  }
  return Scheme;
}

//计算当前日时段表方案
//Flag EQ CALC_ROM表示从ROM中读取参数强制判断一次当前套方案
//Flag EQ CALC_RAM表示使用内存中参数进行一次判断当前方案
INT8U Calc_Cur_Date_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //读取主副日时段表切换时刻
  if(CALC_ROM EQ Flag)//表示从ROM中重新读取相关数据，进行计算
  {
    Read_Date_Scheme_Switch_Time();
  }

  //检查内存中相关变量的正确性
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//检查Cur_Time0时间
  Re &= CHECK_STRUCT_SUM(Mode_Word);//检查模式字是否允许费率切换
  Re &= CHECK_STRUCT_SUM(Date_Scheme_Switch_Time);//检查两套日时段表切换时间
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//检查当前费率信息
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Date_Scheme;
  
  if(DATE_TABLE_SWITCH_EN EQ 1)//是否允许切换日时段表方案?
  {
    if(_Check_HEX_Time((INT8U *) Date_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Date_Scheme_Switch_Time);//当前时间是否在费率切换时间之后?
      if(Re != TIME_BEF)//当前时间在费率方案切换时间之后
      {
        if(Cur_Scheme.Date_Scheme_Time EQ BEF_SWITCH_TIME)//前一次的判断时间在切换时间以前,则必须发生一次切换
        {
          if(Cur_Scheme.Date_Scheme EQ DATE_SCHEME1)
            Scheme = DATE_SCHEME0;
          else
            Scheme = DATE_SCHEME1;
          
          Cur_Scheme.Date_Scheme_Time = AFT_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //将日时段表切换时间置0
          mem_set((INT8U *) Date_Scheme_Switch_Time.Time, 0, sizeof(Date_Scheme_Switch_Time.Time),\
                  (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Date_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_DATE_SCHE_CHG_TIME, (INT8U *)Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
        }
      }
      else
      {
        //切换时间往前调?
        if(Cur_Scheme.Date_Scheme_Time EQ AFT_SWITCH_TIME)//前一次的判断时间在切换时间以后,则必须发生一次切换
        {
          Cur_Scheme.Date_Scheme_Time = BEF_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));         
        }      
      }
    }
  }

  //和当前使用的费率方案不一致，应该切换费率方案
  //使用ROM中参数计算费率方案时，强制认为发生了一次费率切换, 以免出错
  if(Cur_Rate_Info.Date_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Date_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Date_Scheme_Changed_Proc();//费率方案切换处理
    
    if(Cur_Scheme.Date_Scheme != Scheme)
    {
      Debug_Print("Cur_Date_Scheme Changed!");
      Cur_Scheme.Date_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_DATE_TABLE_SWITCH_FREEZE, EVENT_OCCUR);
    }
  }
  return Scheme;
}

//计算当前费率方案
INT8U Calc_Cur_Rate_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //读取主副日时段表切换时刻
  if(CALC_ROM EQ Flag)//表示从ROM中重新读取相关数据，进行计算
  {
    Read_Rate_Scheme_Switch_Time();
  }

  //检查内存中相关变量的正确性
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//检查Cur_Time0时间
  Re &= CHECK_STRUCT_SUM(Mode_Word);//检查模式字是否允许费率切换
  Re &= CHECK_STRUCT_SUM(Rate_Scheme_Switch_Time);//检查两套日时段表切换时间
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//检查当前费率信息
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Rate_Scheme;
  
  if(RATE_SCH_SWITCH_EN EQ 1)//是否允许切换日时段表方案?
  {
    if(_Check_HEX_Time((INT8U *) Rate_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Rate_Scheme_Switch_Time);//当前时间是否在费率切换时间之后?
      if(Re != TIME_BEF)//当前时间在费率方案切换时间之后
      {
        if(Cur_Scheme.Rate_Scheme_Time EQ BEF_SWITCH_TIME)//前一次的判断时间在切换时间以前,则必须发生一次切换
        {
          if(Cur_Scheme.Rate_Scheme EQ RATE_SCHEME1)
            Scheme = RATE_SCHEME0;
          else
            Scheme = RATE_SCHEME1;
          
          Cur_Scheme.Rate_Scheme_Time = AFT_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //将费率方案切换时间置0
          mem_set((INT8U *) Rate_Scheme_Switch_Time.Time, 0, sizeof(Rate_Scheme_Switch_Time.Time),\
                  (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Rate_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_RATE_SCHE_CHG_TIME, (INT8U *)Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
          
        }
      }
      else
      {
        //切换时间往前调?
        if(Cur_Scheme.Rate_Scheme_Time EQ AFT_SWITCH_TIME)//前一次的判断时间在切换时间以后,则必须发生一次切换
        {
          Cur_Scheme.Rate_Scheme_Time = BEF_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));          
        }      
      }
    }
  }

  //和当前使用的费率方案不一致，应该切换费率方案
  //使用ROM中参数计算费率方案时，强制认为发生了一次费率切换, 以免出错
  if(Cur_Rate_Info.Rate_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Rate_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Rate_Scheme_Changed_Proc();//费率方案切换处理
    
    if(Cur_Scheme.Rate_Scheme != Scheme)
    {
      Debug_Print("Cur_Rate_Scheme Changed!");
      Cur_Scheme.Rate_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_RATE_SCH_SWITCH_FREEZE, EVENT_OCCUR);      
    }
  }
  return Scheme; 
}

//计算当前阶梯方案
INT8U Calc_Cur_Step_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //读取主副阶梯方案切换时刻
  if(CALC_ROM EQ Flag)//表示从ROM中重新读取相关数据，进行计算
  {
    Read_Step_Scheme_Switch_Time();
  }

  //检查内存中相关变量的正确性
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//检查Cur_Time0时间
  Re &= CHECK_STRUCT_SUM(Mode_Word);//检查模式字是否允许费率切换
  Re &= CHECK_STRUCT_SUM(Step_Scheme_Switch_Time);//检查两套阶梯切换时间
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//检查当前费率信息
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Step_Scheme;
  
  if(STEP_SCH_SWITCH_EN EQ 1)//是否允许切换日时段表方案?
  {
    if(_Check_HEX_Time((INT8U *) Step_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Step_Scheme_Switch_Time);//当前时间是否在费率切换时间之后?
      if(Re != TIME_BEF)//当前时间在费率方案切换时间之后
      {
        if(Cur_Scheme.Step_Scheme_Time EQ BEF_SWITCH_TIME)//前一次的判断时间在切换时间以前,则必须发生一次切换
        {
          if(Cur_Scheme.Step_Scheme EQ STEP_SCHEME1)
            Scheme = STEP_SCHEME0;
          else
            Scheme = STEP_SCHEME1;
          
          Cur_Scheme.Step_Scheme_Time = AFT_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //阶梯方案切换时间置0
          mem_set((INT8U *) Step_Scheme_Switch_Time.Time, 0, sizeof(Step_Scheme_Switch_Time.Time),\
                  (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Step_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_STEP_SCHE_CHG_TIME, (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
        }
      }
      else
      {
        //切换时间往前调?
        if(Cur_Scheme.Step_Scheme_Time EQ AFT_SWITCH_TIME)//前一次的判断时间在切换时间以后,则必须发生一次切换
        {
          Cur_Scheme.Step_Scheme_Time = BEF_SWITCH_TIME;//当前在切换时间以后了
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));          
        }      
      }
    }
  }

  //和当前使用的费率方案不一致，应该切换费率方案
  //使用ROM中参数计算费率方案时，强制认为发生了一次费率切换, 以免出错
  if(Cur_Rate_Info.Step_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Step_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Step_Scheme_Changed_Proc();//费率方案切换处理
    
    if(Cur_Scheme.Step_Scheme != Scheme)
    {
      Debug_Print("Cur_Step_Scheme Changed!");
      Cur_Scheme.Step_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_STEP_SCH_SWITCH_FREEZE, EVENT_OCCUR);
    }
  }
  return Scheme; 
}
#endif

extern CONST S_Cur_Scheme Def_SDI_CUR_SCHEME;

void Check_Cur_Scheme_Info()
{
  if((Cur_Scheme.Year_Scheme != YEAR_SCHEME0 && Cur_Scheme.Year_Scheme != YEAR_SCHEME1) ||\
     (Cur_Scheme.Date_Scheme != DATE_SCHEME0 && Cur_Scheme.Date_Scheme != DATE_SCHEME1) ||\
     (Cur_Scheme.Rate_Scheme != RATE_SCHEME0 && Cur_Scheme.Rate_Scheme != RATE_SCHEME1) ||\
     (Cur_Scheme.Step_Scheme != STEP_SCHEME0 && Cur_Scheme.Step_Scheme != STEP_SCHEME1) ||\
     (Cur_Scheme.Year_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Year_Scheme_Time != AFT_SWITCH_TIME) ||\
     (Cur_Scheme.Date_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Date_Scheme_Time != AFT_SWITCH_TIME) ||\
     (Cur_Scheme.Rate_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Rate_Scheme_Time != AFT_SWITCH_TIME) ||\
     (Cur_Scheme.Step_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Step_Scheme_Time != AFT_SWITCH_TIME))  
  {
    ASSERT_FAILED();
    mem_cpy((INT8U *)&Cur_Scheme, (INT8U *) &Def_SDI_CUR_SCHEME, sizeof(S_Cur_Scheme),\
            (INT8U *)&Cur_Scheme, sizeof(Cur_Scheme));
    INIT_STRUCT_VAR(Cur_Scheme);
    SET_STRUCT_SUM(Cur_Scheme); 
    Write_Storage_Data(_SDI_CUR_SCHEME, (void *) &Cur_Scheme, sizeof(Cur_Scheme));
  }
  
}

/*
typedef struct
{
  INT8U Year_Period; //年时区数
  INT8U Date_Table;  //日时段表数
  INT8U Date_Period; //日时段数
  INT8U Rates;    //费率数
  INT8U Holidays; //节假日数
  INT8U WeekRest_DataTable;//周休日使用的时段表号
  INT8U WeekRest_Status;  //周休日状态字
  
  INT8U CS[CS_BYTES];
}S_Multi_Rate_Para;//复费率参数
*/

//检查复费率参数
void Check_Multi_Rate_Para()
{
  TRACE();

  //费率数
  if(!(Multi_Rate_Para.Rates <= MAX_RATES && Multi_Rate_Para.Rates >0))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Rates = 4;
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //年时区数
  if(!(Multi_Rate_Para.Year_Period <= MAX_YEAR_PERIODS && Multi_Rate_Para.Year_Period > 0))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Year_Period = 1; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //日时段表数
  if(!(Multi_Rate_Para.Date_Table <= MAX_DATE_TABLES && Multi_Rate_Para.Date_Table > 0))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Date_Table = 1; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //日时段数
  if(!(Multi_Rate_Para.Date_Period <= MAX_DATE_PERIODS))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Date_Period = 4; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //节假日数
  if(!(Multi_Rate_Para.Holidays <= MAX_YEAR_HOLIDAYS))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Holidays = 0; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
}

//检查预付费参数合法性
void Check_Prepaid_Para()
{
  TRACE();

  if(Prepaid_Para.Step_Num > PREPAID_MAX_STEP)
  {
    ASSERT_FAILED();
    Prepaid_Para.Step_Num = PREPAID_MAX_STEP;
    SET_STRUCT_SUM(Prepaid_Para);
  }
  
  if(Prepaid_Para.PT_Ratio EQ 0)
  {
    Prepaid_Para.PT_Ratio = 1;
    SET_STRUCT_SUM(Prepaid_Para);
  }
  
  if(Prepaid_Para.CT_Ratio EQ 0)
  {
    Prepaid_Para.CT_Ratio = 1;
    SET_STRUCT_SUM(Prepaid_Para);
  }
}

//读取复费率相关参数
void Read_Multi_Rate_Para()
{
  INT16U Len;
  
  //套费率方案参数
  Len = S_OFF(S_Multi_Rate_Para, WeekRest_DataTable);
  Read_Multi_Storage_Data(SDI_YEAR_PERIOD_NUM, 6, (void *) &Multi_Rate_Para.Year_Period, (void *) &Multi_Rate_Para, Len);

  if(Read_Storage_Data(SDI_WEEK_REST_DAY, (void *) &Multi_Rate_Para.WeekRest_Status, (void *) &Multi_Rate_Para.WeekRest_Status, 1) != 1)
    ASSERT_FAILED();

  if(Read_Storage_Data(SDI_WEEK_REST_DATE_TABLE, (void *) &Multi_Rate_Para.WeekRest_DataTable, (void *) &Multi_Rate_Para.WeekRest_DataTable, 1) != 1)
    ASSERT_FAILED();
  
  Len = S_OFF(S_Multi_Rate_Para, WeekRest_Status);//周休日状态字前的数据要BCD->HEX
  Bcd2Hex_Buf((void *) &Multi_Rate_Para, S_OFF(S_Multi_Rate_Para, WeekRest_Status), (void *) &Multi_Rate_Para, (void *) &Multi_Rate_Para, sizeof(Multi_Rate_Para));
  
  INIT_STRUCT_VAR(Multi_Rate_Para);
  SET_STRUCT_SUM(Multi_Rate_Para);

  Check_Multi_Rate_Para();//检查复费率参数的合法性  
  
}

//获取多费率相关参数
//Year_Scheme表示费率方案号, 为YEAR_SCHEME0或者YEAR_SCHEME1
void Read_Year_Table_Para(INT8U Year_Scheme)
{
  INT16U Len;
  PROTO_DI SDI;

  TRACE();

  if(!(YEAR_SCHEME0 EQ Year_Scheme || YEAR_SCHEME1 EQ Year_Scheme))
  {
    ASSERT_FAILED();
    Year_Scheme = YEAR_SCHEME0;
  }
  
  if(YEAR_SCHEME0 EQ Year_Scheme)//使用第一套费率方案
  {
    SDI = SDI_SCHE1_YEAR_TABLE;
  }
  else//第二套
  {
    SDI = SDI_SCHE2_YEAR_TABLE;
  }

  //读取年时区表参数
  if(Read_Storage_Data(SDI, (void *) Year_Table.MDN, (void *) Year_Table.MDN, sizeof(Year_Table.MDN)) != MAX_YEAR_PERIODS * 3)
	ASSERT_FAILED();

  Len = S_OFF(S_Year_Table, CS);
  Bcd2Hex_Buf((void *) &Year_Table, Len, (void *) &Year_Table, (void *) &Year_Table, Len);
  
  INIT_STRUCT_VAR(Year_Table);
  SET_STRUCT_SUM(Year_Table);
}

//用于计算两个时间的时间差日数, 年时区时间差, 返回结果为日数
//用于计算年时区表中两项的时间差, Time0-Time1，该函数用于在年时区表中寻找当前时间的时段
//如果Time0本省在Time1之前，那么结果是Time0+12*31-Time1
//Time0[0]表示日, Time0[1]表示月, Time1表示方法与Time0相同
INT16U Year_Period_Dec(INT8U Time0[], INT8U Time1[])
{
  INT16U Days[2];

  TRACE();

  ASSERT((Time0[0] < 32 && Time0[0] > 0 && Time0[1] < 13 && Time0[1] > 0) &&\
	     (Time1[0] < 32 && Time1[0] > 0 && Time1[1] < 13 && Time1[1] > 0));//判断两个参数的格式

  Days[0] = (INT16U) (Time0[1]) * 31 + (INT16U) (Time0[0]);
  Days[1] = (INT16U) (Time1[1]) * 31 + (INT16U) (Time1[0]);

  if(Days[0] < Days[1])
  {
    return Days[0] + 12 * 31 - Days[1];
  }
  else
  {
    return Days[0] - Days[1];
  }
}

//日时段时间差, 返回为分钟数
//用于计算日时段表中两项的时间差, Time0-Time1, 如果Time0在Time1之前，那么结果是
//Time0+24*60-Time1
//Time0[0]表示分，Time0[1]表示时，Time1表示方法与Time0相同
INT16U Date_Period_Dec(INT8U Time0[], INT8U Time1[])
{
  INT16U Mins[2];

  TRACE();

  //分时数据必须合法
  ASSERT((Time0[0] < 60 && Time0[1] < 24) && (Time1[0] < 60 && Time1[1] < 24));//判断两个参数的格式

  Mins[0] = (INT16U) (Time0[1]) * 60 + (INT16U) (Time0[0]);
  Mins[1] = (INT16U) (Time1[1]) * 60 + (INT16U) (Time1[0]);

  if(Mins[0] < Mins[1])
  {
    return Mins[0] + 24 * 60 - Mins[1];
  }
  else
  {
    return Mins[0] - Mins[1];
  }
}

//检查当前是否是节假日
//该函数需要从内存中读出节假日表并进行比较, 一般每日调用该函数一次
//返回0表示不是节假日，返回>0表示是节假日，同时返回值代表是第多少个节假日，*pDate_Table_Index返回日时段表号
INT8U Check_Today_Holiday(INT8U* pDate_Table_Index)
{
  INT8U Num, Re, i;
  INT16U Len;
  INT8U Temp[10];

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(Multi_Rate_Para.Holidays > MAX_YEAR_HOLIDAYS)
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Holidays = MAX_YEAR_HOLIDAYS;
    SET_STRUCT_SUM(Multi_Rate_Para);
  }

  Num = Multi_Rate_Para.Holidays;

  for(i = 0; i < Num; i ++)
  {
    Len = Read_Storage_Data(0x04030001 + i, Temp, Temp, sizeof(Temp));
    if(Len EQ 4)
    {
      Bcd2Hex_Buf(Temp, Len, Temp, Temp, sizeof(Temp));
      if(Cur_Time0.Time[T_MONTH] EQ Temp[2] && \
         Cur_Time0.Time[T_DATE] EQ Temp[1])
      {
        *pDate_Table_Index = Temp[0];//节假日采用的日时段表号
        return i + 1;
      }
    }
  }
  return 0;
}

//计算当前应该使用的日时段表号, 如果Flag EQ CALC_ROM则强制判断一次当前的日时段表号
//如果日时段表号变化了，将当前日时段表读入Date_Table中
INT8U Cal_Cur_Date_Table(INT8U Flag)
{
  INT8U i, Re;//Data_Index为使用的日时段表号索引
  INT8U Date_Table_Flag;//1表示找到日时段表号
  INT16U Min = 0xFFFF;//最小值, 先置一个极大值
  INT16U Dec;//差
  static S_HEX_Time Last_Chk_Time = {{0, 0, 0, 0, 0}, 0, {0 ^ ((INT8U) CHK_CS_BYTES)}};
  static S_Int8U Date_Table_Index = {CHK_BYTE, 1, CHK_BYTE};

  TRACE();

  //在当前节假日中查找是否是节假日?
  //时间发生了变化，或者Flag标志为CALC_ROM表示强制判断一次
  //每天只进入这个流程一次, 或者CALC_ROM EQ Flag时进入该流程
  Re = CHECK_STRUCT_SUM(Last_Chk_Time);
  if(Last_Chk_Time.Time[T_DATE] != Cur_Time0.Time[T_DATE] || \
     Last_Chk_Time.Time[T_MONTH] != Cur_Time0.Time[T_MONTH] || \
     Last_Chk_Time.Time[T_YEAR] != Cur_Time0.Time[T_YEAR] || \
     CALC_ROM EQ Flag)//跨日或者CALC_ROM情况下重新判断当日是否节假日, 每天只判一次，或者CALC_ROM的情况下判断
  {
    Re = 1;
    Re &= CHECK_STRUCT_SUM(Cur_Time0);//当前时间
    Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);//当前复费率参数
    Re &= CHECK_STRUCT_SUM(Year_Table);//年时区表
    Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//当前费率信息

    if(1 != Re)//ASSERT(0 != Re))
    {
      ASSERT_FAILED();
      Check_Data_Avail();
    }
    
    Date_Table_Flag = 0;

    //本非当日时间，上面的判断保证每日只进入该函数一次
    mem_cpy(&Last_Chk_Time, (void *) &Cur_Time0, sizeof(Cur_Time0), &Last_Chk_Time, sizeof(Last_Chk_Time));

    //先判断当前是否是节假日
    Re = Check_Today_Holiday(&Date_Table_Index.Var);//返回>0标识表示是节假日
    if(Re > 0)//
    {
      Date_Table_Flag = 1;// EQ 1表示找到日时段表索引号了
      Cur_Rate_Info.Date_Flag = HOLIDAY;
      Cur_Rate_Info.Holiday_Index = Re;
    }

    //不是公共假日，是否是周休日?
    if(0 EQ Date_Table_Flag)
    {
      if(GET_BIT(Multi_Rate_Para.WeekRest_Status, Cur_Time0.Week) EQ 0)//为0表示该日是周休日
      {
        Date_Table_Index.Var = Multi_Rate_Para.WeekRest_DataTable;//周休日日时段表号
        Date_Table_Flag = 1;// EQ 1表示找到日时段表索引号了    
        Cur_Rate_Info.Date_Flag = WEEK_REST_DAY;
      }
    }

    //不是公共假日，也不是周休日，在年时区表中查找
    if(0 EQ Date_Table_Flag)
    {
      Cur_Rate_Info.Date_Flag = NORMAL_DAY;//这是一个平常的日子，既不是节假日，也不是周休日
      for(i = 0; i < Multi_Rate_Para.Year_Period && i < MAX_YEAR_PERIODS; i++)
      {
        //日、月数据正确
        if(Year_Table.MDN[i][1] >= 1 && Year_Table.MDN[i][1] <= 31 &&\
           Year_Table.MDN[i][2] >= 1 && Year_Table.MDN[i][2] <= 12)
        {
          Dec = Year_Period_Dec((INT8U *) &Cur_Time0.Time[T_DATE], (INT8U *) &Year_Table.MDN[i][1]);//计算当前时间和年时区表中某项时间的时间差
          if(Dec < Min)//寻找时间差最小的一个认为是当前年时区
          {
            Date_Table_Index.Var = Year_Table.MDN[i][0];//日时段表索引
            Date_Table_Flag = 1;
            Cur_Rate_Info.Year_Period = i + 1;//年时区号
            Min = Dec;
          }
        }
      }
    }

    //没有得到合适的日时段表号，则采用1时段表
    if(!(1 EQ Date_Table_Flag && \
      Date_Table_Index.Var > 0 && \
      Date_Table_Index.Var <= Multi_Rate_Para.Date_Table && \
      Date_Table_Index.Var <= MAX_DATE_TABLES))
    {
      ASSERT_FAILED();
      Date_Table_Index.Var = 1;
    }
    
    //判断时段表号是否发生变化, 变化了则重新读取时段表参数, 或者强制认为日时段发生了变化的话也重新读取
    if(Cur_Rate_Info.Date_Table != Date_Table_Index.Var || CALC_ROM EQ Flag)//当前时段表号发生变化？
    {
      Debug_Print("Date Table Changed, %d-->%d", Cur_Rate_Info.Date_Table, Date_Table_Index.Var);
      Cur_Rate_Info.Date_Table = Date_Table_Index.Var;//日时段表索引号
      SET_STRUCT_SUM(Cur_Rate_Info);    
      Read_Date_Table_Para(Cur_Rate_Info.Date_Scheme, Date_Table_Index.Var);//获取当前时段表参数到Date_Table中 
    }
  }
  return Cur_Rate_Info.Date_Table;//Date_Table_Index;
}

//读取Date_Scheme是日时段表方案的Date_Table_Index号时段表到Date_Table结构体变量中
void Read_Date_Table_Para(INT8U Date_Scheme, INT8U Date_Table_Index)
{
  INT8U Re;
  INT16U Len;

  TRACE();

  Re = CHECK_STRUCT_SUM(Date_Table);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(DATE_SCHEME0 != Date_Scheme && DATE_SCHEME1 != Date_Scheme)
  {
    ASSERT_FAILED();
    Date_Scheme = DATE_SCHEME0;
  }

  if(Date_Table_Index EQ 0 || Date_Table_Index > MAX_DATE_TABLES)
  {
    ASSERT_FAILED();
    Date_Table_Index = 1;
  }

  Len = 0;
  if(Date_Scheme EQ DATE_SCHEME0)
  {
    Len = Read_Storage_Data(SDI_SCHE1_DATE_TABLE1 + (Date_Table_Index - 1), (INT8U *) Date_Table.HMN, (INT8U *) Date_Table.HMN, sizeof(Date_Table.HMN));
  }
  else
  {
    Len = Read_Storage_Data(SDI_SCHE2_DATE_TABLE1 + (Date_Table_Index - 1), (INT8U *) Date_Table.HMN, (INT8U *) Date_Table.HMN, sizeof(Date_Table.HMN));
  }

  //日时段表数据转化为hex码
  Bcd2Hex_Buf((void *) &Date_Table, S_OFF(S_Date_Table, CS), (void *) &Date_Table, (void *) &Date_Table, S_OFF(S_Date_Table, CS));
  if(MAX_DATE_PERIODS * 3 != Len)
  {
    ASSERT_FAILED();
  }

  INIT_STRUCT_VAR(Date_Table);
  SET_STRUCT_SUM(Date_Table);
}

//读取费率方案参数,Scheme表示费率方案
void Read_Rate_Scheme_Para(INT8U Scheme)
{
  STORA_DI SDI;
  INT8U Re;
  INT8U i;
  
  if(Scheme EQ RATE_SCHEME0)
    SDI = SDI_RATE_SCHEME0_0;
  else if(Scheme EQ RATE_SCHEME1)
    SDI = SDI_RATE_SCHEME1_0;
  else
    ASSERT_FAILED();
  
  Re = CHECK_STRUCT_SUM(Multi_Rate_Para);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
  
  for(i = 0; i < MAX_RATES ; i++)
  {
    Read_Storage_Data(SDI + i, (INT8U *)&Rate_Scheme_Para.Fee[i], (INT8U *)&Rate_Scheme_Para, sizeof(Rate_Scheme_Para)); 
    Rate_Scheme_Para.Fee[i] = Bcd2Hex((INT8U *)&Rate_Scheme_Para.Fee[i], 4);
  }
  
  INIT_STRUCT_VAR(Rate_Scheme_Para);
  SET_STRUCT_SUM(Rate_Scheme_Para);
}

//读取阶梯电价方案
void Read_Step_Scheme_Para(INT8U Scheme)
{
  STORA_DI SDI0,SDI1;
  INT8U i;
  
  if(Scheme EQ STEP_SCHEME0)
  {
    SDI0 = SDI_STEP_SCHEME0_ENG;
    SDI1 = SDI_STEP_SCHEME0_MONEY;
  }
  else if(Scheme EQ STEP_SCHEME1)
  {
    SDI0 = SDI_STEP_SCHEME1_ENG;
    SDI1 = SDI_STEP_SCHEME1_MONEY;
  }
  else
    ASSERT_FAILED();
  
  //读取阶梯数
  
  for(i = 0; i <PREPAID_MAX_STEP ; i++)
  {
    Read_Storage_Data(SDI0 + i, (INT8U *)&Step_Scheme_Para.Step_Energy[i], (INT8U *)&Step_Scheme_Para, sizeof(Step_Scheme_Para)); 
    Step_Scheme_Para.Step_Energy[i] = Bcd2Hex((INT8U *)&Step_Scheme_Para.Step_Energy[i], 4);
  }
  
  for(i = 0; i <PREPAID_MAX_STEP + 1; i++)
  {
    Read_Storage_Data(SDI1 + i, (INT8U *)&Step_Scheme_Para.Step_Fee[i], (INT8U *)&Step_Scheme_Para, sizeof(Step_Scheme_Para)); 
    Step_Scheme_Para.Step_Fee[i] = Bcd2Hex((INT8U *)&Step_Scheme_Para.Step_Fee[i], 4);
  }  
  
  INIT_STRUCT_VAR(Step_Scheme_Para);
  SET_STRUCT_SUM(Step_Scheme_Para);  
  
}

//计算当前应该使用的费率编号
//主要是从当前日时段表中找到当前费率号
INT8U Calc_Cur_Rate(INT8U Flag)
{
  INT8U Rate, Re;//Data_Index为使用的日时段表号索引
  INT16U Min = 0xFFFF, i;
  INT16U Dec;
  INT8U Period;//日时段号

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Time0);
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);

  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }//检查数据的有效性

  Period = Cur_Rate_Info.Date_Period;
  //如果日时段表号发生变化，则重新读取到Date_Table变量中
  //套费率方按发生变化的时候，会强制切换Date_Table
  //平时计算费率的时候，只是每天计算一次Date_Table
  Cal_Cur_Date_Table(CALC_RAM);
  //此处没有用Flag，而用CALC_RAM，因为当Flag EQ CACL_ROM时，之前肯定调用了Calc_Cur_Year_Scheme(CACL_ROM)，这里面已经对日时段表进行了处理

  //在日时段表中找当前费率
  Rate = 0;
  Min = 0xFFFF;//置一个极大值
  for(i = 0; i < Multi_Rate_Para.Date_Period && i < MAX_DATE_PERIODS; i++)
  {
    if(Date_Table.HMN[i][1] < 60 && Date_Table.HMN[i][2] < 24)//时间数据必须正确才参与计算
    {
      Dec = Date_Period_Dec((INT8U *) &Cur_Time0.Time[T_MIN], (INT8U *) &Date_Table.HMN[i][1]);
      if(Dec < Min)
      {
        Rate = Date_Table.HMN[i][0];//费率
        Cur_Rate_Info.Date_Period = i + 1;//日时段号
        Min = Dec;
      }
    }
  }

  if(!(Rate <= MAX_RATES && Rate <= Multi_Rate_Para.Rates && Rate > 0))//费率号错，默认使用费率1
  {
    ASSERT_FAILED();
    Rate = 1;
  }

  if(Cur_Rate_Info.Rate != Rate || CALC_ROM EQ Flag)//需要切换费率了
  {
    Cur_Rate_Info.Rate = Rate;
    SET_STRUCT_SUM(Cur_Rate_Info);//下面函数会CHECK_STRUCT_SUM哦
    Rate_Changed_Proc();//费率切换相关处理
  }

  if(Period != Cur_Rate_Info.Date_Period)
  {
    Set_Event_Instant(ID_PARSE_SWITCH);
    Port_Out_Pub(EXT_ID_PARSE,85);
    Debug_Print("Date Period Switch!!!");    
  }//时段切换

  SET_STRUCT_SUM(Cur_Rate_Info);  
  return Rate;//返回费率号
}
/*
typedef struct
{
  INT32U Chang_Plus_AcEnerg[4];      //A/B/C/SUM各元件正向有功增量:单位:0.01wh
  INT32U Chang_Nega_AcEnerg[4];      //A/B/C/SUM各元件反向有功增量:单位:0.01wh
  
  //INT32U Chang_Plus_ReacEnerg[4];    //A/B/C/SUM各元件正向无功增量(无功组合1):单位:0.01warh  
  //INT32U Chang_Nega_ReacEnerg[4];    //A/B/C/SUM各元件反向无功增量(无功组合2):单位:0.01warh
  
  INT32U Chang_Quad_ReacEnerg[4][4];   //A/B/C/SUM各元件四象限无功增量, Chang_Quad_ReacEnerg[1][2]表示B向3象限无功
  
  INT32U Add_AmpaHour[3];       //AH累计:0.0001As, 累计量
  INT32U Add_CopperLoss[4];   //A, B, C, sum铜损, 单位为0.0000001kA2s, 累计量
  INT32U Add_IronLoss[4];     //A, B, C, sum铁损, 单位为0.0000001KV2s，累计量
  INT32U Add_GenaralErr[4];   //A, B, C, sum合成误差, 单位:0.01*tgFA*s, 累计量
  INT8U CS[CS_BYTES];
}MEASU_ENERG; 
*/
//检查累积电量数据是否正确
INT8U Check_Cumulative_Energy_Data(MEASU_ENERG* pEnergy)
{
  INT8U Re, i, j;

  TRACE();

  Re = Check_STRUCT_Sum(pEnergy, sizeof(MEASU_ENERG), pEnergy->CS, sizeof(pEnergy->CS));
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    return 0;
  }

  for(i = 0; i < 4; i++)
  {
    if(pEnergy->Chang_Plus_AcEnerg[i] >= (INT32U) MAX_ACTIVE_INC * ENERGY_RATIO || \
       pEnergy->Chang_Nega_AcEnerg[i] >= (INT32U) MAX_ACTIVE_INC * ENERGY_RATIO)
    {
      ASSERT_FAILED();
      return 0;
    }
    else
    {
      for(j = 0; j < 4; j++)
      {
        if(pEnergy->Chang_Quad_ReacEnerg[i][j] >= (INT32U) MAX_REACTIVE_INC * ENERGY_RATIO)
        {
          ASSERT_FAILED();
          return 0;
        }
      }
    }
  }

  return 1;
}

//检查电量增长是否正常
INT8U Check_Energy_Data_Inc()
{
  INT8U i;
  INT32U Temp;

  TRACE();

#if USE_ENERGY_RAM_BAK > 0  
  //正向有功电量
  if(Cur_Energy.Pos_Active[0] >= Cur_Energy_Bak.Pos_Active[0])
  {
    Temp = Cur_Energy.Pos_Active[0] - Cur_Energy_Bak.Pos_Active[0];
    if(Temp > MAX_ACTIVE_INC)//电量飞走
    {
      //Debug_Print("Pos Energy Data Inc too much:%ld", Temp);
      ASSERT_FAILED();
      return 0;
    }
  }
  else//电量倒走
  {
    ASSERT_FAILED();
    //Debug_Print("Pos Energy Data Dec!");
    return 0;
  }

  //反向有功电量
  if(Cur_Energy.Neg_Active[0] >= Cur_Energy_Bak.Neg_Active[0])
  {
    Temp = Cur_Energy.Neg_Active[0] - Cur_Energy_Bak.Neg_Active[0];
    if(Temp > MAX_ACTIVE_INC)//电量飞走
    {
      //Debug_Print("Neg Energy Data Inc too much:%ld", Temp);
      ASSERT_FAILED();
      return 0;
    }
  }
  else//电量倒走
  {
    ASSERT_FAILED();
    //Debug_Print("Neg Energy Data Dec!");
    return 0;
  }

  //四象限无功
  for(i = 0; i < 4; i++)
  {
    if(Cur_Energy.Quad_Reactive[i][0] >= Cur_Energy_Bak.Quad_Reactive[i][0])
    {
      Temp = Cur_Energy.Quad_Reactive[i][0] - Cur_Energy_Bak.Quad_Reactive[i][0];
      if(Temp > MAX_REACTIVE_INC)//电量飞走
      {
        //Debug_Print("Quad %d Reactive Energy Data Inc too much:%ld", i, Temp);
        ASSERT_FAILED();
        return 0;
      }
    }
    else//电量倒走
    {
      ASSERT_FAILED();
      //Debug_Print("Quad %d Reactive Energy Data Dec!", i);
      return 0;
    }

    //三相的正反有功 for (i = 0; i < 3; i++)

  }
  {
    //正向有功
    if(Cur_Energy.Phase_Pos_Active[i] >= Cur_Energy_Bak.Phase_Pos_Active[i])
    {
      Temp = Cur_Energy.Phase_Pos_Active[i] - Cur_Energy_Bak.Phase_Pos_Active[i];
      if(Temp > MAX_ACTIVE_INC)//电量飞走
      {
        //Debug_Print("Phase %c Pos_Active Energy Data Inc too much:%d", 'A' + i, Temp);
        ASSERT_FAILED();
        return 0;
      }
    }
    else//电量倒走
    {
      ASSERT_FAILED();
      //Debug_Print("Phase %c Pos_Active Energy Data Dec!", 'A' + i);
      return 0;
    }

    //反向有功
    if(Cur_Energy.Phase_Neg_Active[i] >= Cur_Energy_Bak.Phase_Neg_Active[i])
    {
      Temp = Cur_Energy.Phase_Neg_Active[i] - Cur_Energy_Bak.Phase_Neg_Active[i];
      if(Temp > MAX_REACTIVE_INC)//电量飞走
      {
        //Debug_Print("Phase %c Neg_Active Energy Data Inc too much:%ld", 'A' + i, Temp);
        ASSERT_FAILED();
        return 0;
      }
    }
    else//电量倒走
    {
      ASSERT_FAILED();
      //Debug_Print("Phase %c Neg_Active Energy Data Dec!", 'A' + i);
      return 0;
    }
  }
  return 1;
#else
  i=0;
  Temp=0;
  (void)i;
  (void)Temp;
  return 1;
#endif  
}

#pragma optimize=none
//当前电量累加
void Cur_Energy_Cumu(MEASU_ENERG* pEnergy)
{
  INT8U Rate;
  INT8U i, j;

  
  TRACE();

  Rate = Cur_Rate_Info.Rate;//Get_Using_Rate();//当前使用费率
  //保证当前费率数是正确的, 如果超过了最大费率数，则默认使用费率1
  if(!(Rate > 0 && Rate <= Multi_Rate_Para.Rates && Rate <= MAX_RATES))
  {
    ASSERT_FAILED();
    Rate = 1;
  }
  //正有有功累加  
  Cur_Energy.Pos_Active[0] += (pEnergy->Chang_Plus_AcEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Pos_Active[Rate] += (pEnergy->Chang_Plus_AcEnerg[3] / ENERGY_RATIO);

  //当前结算周期电量
  Cur_Energy.Prepaid_Info.Month_Pos_Act += (pEnergy->Chang_Plus_AcEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Prepaid_Info.Month_Neg_Act += (pEnergy->Chang_Nega_AcEnerg[3] / ENERGY_RATIO);
  
  //反有有功累加
  Cur_Energy.Neg_Active[0] += (pEnergy->Chang_Nega_AcEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Neg_Active[Rate] += (pEnergy->Chang_Nega_AcEnerg[3] / ENERGY_RATIO);

#if APP_ENERG_EN >0     
  //正有视在累加  
  Cur_Energy.Pos_Apparent[0] += (pEnergy->Chang_Plus_PQSEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Pos_Apparent[Rate] += (pEnergy->Chang_Plus_PQSEnerg[3] / ENERGY_RATIO);
  //反有视在累加
  Cur_Energy.Neg_Apparent[0] += (pEnergy->Chang_Nega_PQSEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Neg_Apparent[Rate] += (pEnergy->Chang_Nega_PQSEnerg[3] / ENERGY_RATIO);
#endif
  
  
  //四象限无功累加
  for(i = 0; i < 4; i++)
  {
    Cur_Energy.Quad_Reactive[i][0] += pEnergy->Chang_Quad_ReacEnerg[3][i] / ENERGY_RATIO;    
    Cur_Energy.Quad_Reactive[i][Rate] += pEnergy->Chang_Quad_ReacEnerg[3][i] / ENERGY_RATIO;
  }

  //三相有无功
  for(i = 0; i < 3; i++)
  {
    Cur_Energy.Phase_Pos_Active[i] += (pEnergy->Chang_Plus_AcEnerg[i] / ENERGY_RATIO);
    Cur_Energy.Phase_Neg_Active[i] += (pEnergy->Chang_Nega_AcEnerg[i] / ENERGY_RATIO);

#if APP_ENERG_EN >0     
    Cur_Energy.Phase_Pos_Apparent[i] += (pEnergy->Chang_Plus_PQSEnerg[i] / ENERGY_RATIO);
    Cur_Energy.Phase_Neg_Apparent[i] += (pEnergy->Chang_Nega_PQSEnerg[i] / ENERGY_RATIO);    
#endif
    
    for(j = 0; j < 4; j++)//三相四象限分别计算
      Cur_Energy.Phase_Quad_Reactive[i][j] += pEnergy->Chang_Quad_ReacEnerg[i][j] / ENERGY_RATIO;
  }

  //三相安培时
  for(i = 0; i < 3; i++)
  {
    Cur_Energy.Phase_AH[i + 1] += (pEnergy->Add_AmpaHour[i] / AH_RATIO);
    Cur_Energy.CopperLoss[i + 1] += (pEnergy->Add_CopperLoss[i] / COPPERLOSS_RATIO);    
    Cur_Energy.IronLoss[i + 1] += (pEnergy->Add_IronLoss[i] / IRONLOSS_RATIO);
    
    Cur_Energy.TransErr[i + 1] += (pEnergy->Add_GenaralErr[i] / TRANSERR_RATIO);
  }
  //总AH
  Cur_Energy.Phase_AH[0] += (pEnergy->Add_AmpaHour[3] / AH_RATIO); 
  //总铜损  
  Cur_Energy.CopperLoss[0] += (pEnergy->Add_CopperLoss[3] / COPPERLOSS_RATIO);
  //总铁损  
  Cur_Energy.IronLoss[0] += (pEnergy->Add_IronLoss[3] / IRONLOSS_RATIO);
  //总合成误差
  Cur_Energy.TransErr[0] += (pEnergy->Add_GenaralErr[3] / TRANSERR_RATIO);

  SET_STRUCT_SUM(Cur_Energy);
}
//累加电量
void Cumulative_Energy()
{
  static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  MEASU_ENERG* pEnergy;
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(1 EQ Re);

  //保证每秒才进入一次该函数
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
  {
    return;
  }
  else
  {
    Sec_Bak.Var = Sec_Timer_Pub;
  } 

  Re = 1;
  Re &= Check_Energy_Data((S_Energy *) &Cur_Energy);
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
/*
  OS_Mutex_Pend(TRANS_BUF_SEM_ID);

  Get_Measu_AcculateData_PUCK(HUCK, (void *) Trans_Temp_Buf, (void *) Trans_Temp_Buf, sizeof(MEASU_ENERG), sizeof(Trans_Temp_Buf));
  pEnergy = (MEASU_ENERG *) Trans_Temp_Buf;
  
  Re = CHECK_STRUCT_VAR(_Trans_Temp_Buf);
  ASSERT(1 EQ Re);
  
  Re = Check_Cumulative_Energy_Data(pEnergy);
  ASSERT(1 EQ Re);
  if(1 EQ Re)//pEnergy指向的数据合法
  {
    DIS_PD_INT;//关掉电中断
    Cur_Energy_Cumu(pEnergy); //当前电量累加 

    if(PREPAID_EN > 0)
      Prepaid_Proc(pEnergy); //预付费处理
    
    Energy_Cumu_Counts.Var++; //电量累加次数增加
    EN_PD_INT;//开掉电中断
  }
  
  OS_Mutex_Post(TRANS_BUF_SEM_ID);
*/
  Get_Measu_AcculateData_PUCK(HUCK, (void *) &Accu_Energy, (void *) &Accu_Energy, sizeof(Accu_Energy), sizeof(Accu_Energy));
  pEnergy = (MEASU_ENERG *) &Accu_Energy;
  
  Re = Check_Cumulative_Energy_Data(pEnergy);
  ASSERT(1 EQ Re);
  if(1 EQ Re)//pEnergy指向的数据合法
  {
    DIS_PD_INT;//关掉电中断
    
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)//本地预付费才进行预付费金酸
      Prepaid_Proc(pEnergy); //预付费处理    
    
    Cur_Energy_Cumu(pEnergy); //当前电量累加 
    
    Energy_Cumu_Counts.Var++; //电量累加次数增加
    EN_PD_INT;//开掉电中断
  }
  
  Check_Energy_Data_Inc();//检查电量增长是否合法

  #if USE_ENERGY_RAM_BAK > 0//将数据备份到Cur_Energy_Bak变量中
  mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy_Bak), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
  #endif
}

//检查复费率电量数据分费率电量和是否等于总电量
INT8U Check_Multi_Rate_Data(INT32U Data[])
{
  INT16U i;
  INT32U Sum;

  TRACE();

  Sum = 0;
  for(i = 1; i <= MAX_RATES; i++)
  {
    Sum += Data[i];
  }
  if(Sum EQ Data[0])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//检查电量数据是否合法正确
//返回1表示数据正确, 0表示数据有错
INT8U Check_Energy_Data(S_Energy* pEnergy)
{
  INT8U Re = 1;

  TRACE();

  Re &= (pEnergy->Head EQ CHK_BYTE && pEnergy->Tail EQ CHK_BYTE) ? 1 : 0;  
  Re &= Check_STRUCT_Sum(pEnergy, sizeof(S_Energy), pEnergy->CS, sizeof(pEnergy->CS));
  Re &= (pEnergy->Data_Ready_Flag EQ DATA_READY) ? 1 : 0;
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    return 0;
  }

  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Pos_Active));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Neg_Active));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Neg_Active));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[0]));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[1]));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[2]));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[3]));
  Re &= Check_STRUCT_Sum(pEnergy, sizeof(S_Energy), pEnergy->CS, sizeof(pEnergy->CS));  
  
  if(0 EQ Re)
  {
    ASSERT_FAILED();
  }
  return Re;
}

//检查全局公共buf是否合法
void Check_Pub_Var_Avail()
{
  INT8U Re;
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(_Pub_Buf);
  Re &= CHECK_STRUCT_VAR(_Pub_Buf0);
  Re &= CHECK_STRUCT_VAR(Pub_Timer);
  Re &= CHECK_STRUCT_VAR(_Trans_Temp_Buf);
  
  ASSERT(1 EQ Re);
}

//检查当前电量和需量数据, 并进行容错处理
void Check_Energy_Data_Avail()//检查当前电量与需量数据的正确性, 总 = 和
{
  INT8U Re;
  static S_Flag Energy_Err_Flag = {0, {0}};

  //Energy_Err_Flag用来记录电量数据是否发生过错误（分费率和！ = 总）, 如果已经发生过且没有纠错成功
  //则该标志置1，标识纠错不成功, 从而下次进入该函数后不再进行纠错了, 防止重复不断的纠错该数据

  //检查当前电量, 同时检查分费率是否等于总，以及校验和
  //检查分费率是否等于总时，如果内存中数据不对，则读取ROM中数据，如果读出的数据还不对
  //则默认该次的错误, 以后不再进行检查，此时Energy_Err_Flag EQ 1
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(0 EQ Re)
  {
    ASSERT_FAILED();
    #if USE_ENERGY_RAM_BAK > 0 //该宏为1表示定义了Cur_Energy_Bak变量作为Cur_Energy的内存备份
    Debug_Print("Cur_Energy Data Error, Copy from Cur_Energy_Bak Data");
    Re = Check_Energy_Data((S_Energy *) &Cur_Energy_Bak);//使用内存备份电量
    if(1 EQ Re)//Cur_Energy_Bak中的数据正确
    {
      Debug_Print("Copy Cur_Energy_Bak Data to Cur_Energy");//将Cur_Energy_Bak中的数据复制到Cur_Energy中
      mem_cpy((void *) &Cur_Energy, (void *) &Cur_Energy_Bak, sizeof(Cur_Energy), (void *) &Cur_Energy, sizeof(Cur_Energy));
    }
    else//Cur_Energy_Bak中数据不正确的情况下直接从rom中读取数据
    {
      Debug_Print("Cur_Energy_Bak Data Error, Read_Energy_Data_From_Rom");
      Read_Energy_Data_From_Rom(); 
      Re = Check_Energy_Data((S_Energy *) &Cur_Energy);//ROM中的数据也不对的话，完全没有办法了，默认这个错误, 将Energy_Err_Flag = 1
      if(0 EQ Re)
        Energy_Err_Flag.Flag = 1;//表示纠错没有成功
      SET_STRUCT_SUM(Energy_Err_Flag);//同时也可纠正上面的CHECK_STRUCT_SUM(Energy_Err_Flag) != 1
    }
    #else
    ASSERT_FAILED();
    Debug_Print("Cur_Energy Data Error, Read_Energy_Data_From_Rom");
    Read_Energy_Data_From_Rom(); 
    Re = Check_Energy_Data((S_Energy *) &Cur_Energy);//ROM中的数据也不对的话，完全没有办法了，默认这个错误, 将Energy_Err_Flag = 1
    if(0 EQ Re)
      Energy_Err_Flag.Flag = 1;//表示纠错没有成功
    SET_STRUCT_SUM(Energy_Err_Flag);//同时也可纠正上面的CHECK_STRUCT_SUM(Energy_Err_Flag) != 1
    #endif
  }
}

//保存当前电量和需量数据，主流程定时调用该函数保存电量等
void Save_Cur_Energy_Data()
{
  INT8U Re;
  
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//掉电时调用该函数保存电量需量等
void Save_Cur_Energy_PD_Data()
{
  INT8U Re;
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(0 EQ Re)//判断Cur_Energy中的数据是否正确，不正确则采用Cur_Energy_Bak中的数据，如果两个数据都不正确，则不存
  {
    ASSERT_FAILED();
    #if USE_ENERGY_RAM_BAK > 0
    Re = Check_Energy_Data((S_Energy *) &Cur_Energy_Bak);
    if(1 EQ Re)
      mem_cpy((S_Energy *) &Cur_Energy, (S_Energy *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak), (S_Energy *) &Cur_Energy, sizeof(Cur_Energy));
    else
    {
      ASSERT_FAILED();
      return;
    }
    #else
    return;
    #endif
  }
  Re = Write_Storage_Data(_SDI_CUR_ENERGY_PD, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
  if(1 != Re)
  {
    ASSERT_FAILED();
  }
}

//保存当前电量和需量数据，主流程定时调用该函数保存电量等
void Save_Cur_Energy_Bak0_Data()
{
  INT8U Re;

  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY_BAK0, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);  
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//保存当前电量和需量数据，主流程定时调用该函数保存电量等
void Save_Cur_Energy_Bak1_Data()
{
  INT8U Re;

  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY_BAK1, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);  
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//保存当前电量和需量数据，主流程定时调用该函数保存电量等
void Save_Cur_Energy_Bak2_Data()
{
  INT8U Re;
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY_BAK2, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);  
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//设置默认的购电次数和金额
void Set_Def_Prepaid_Buy_Counts_Money()
{
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts = 0;
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money = 0;

  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts = 0;
  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy = 0;  
}

//设置默认的电量数据
void Set_Def_Energy_Data()
{
  INT8U i;
  S_HEX_Time TempTime;
  STORA_DI SDI;
  INT32U Temp_Counts, Temp_Money;
  //本地卡bak_up
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  {
    if(PREPAID_MODE EQ PREPAID_MONEY) //电费型
    {
      Temp_Counts = Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts;
      Temp_Money = Cur_Energy.Prepaid_Info.Total_Prepaid_Money;
    }
    else
    {
      Temp_Counts = Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts;
      Temp_Money = Cur_Energy.Prepaid_Info.Total_Prepaid_Energy;      
    }
  }
  
  Debug_Print("Set Def Energy Data");
  mem_set((void *) &Cur_Energy, 0, sizeof(Cur_Energy), (void *) &Cur_Energy, sizeof(Cur_Energy));
  //SET_STRUCT_SUM(Cur_Energy);

  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  {
    if(PREPAID_MODE EQ PREPAID_MONEY) //电费型
    {
      Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts = Temp_Counts;
      Cur_Energy.Prepaid_Info.Total_Prepaid_Money = Temp_Money;
    }
    else
    {
      Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts = Temp_Counts;
      Cur_Energy.Prepaid_Info.Total_Prepaid_Energy =Temp_Money;      
    }
  }
  
  INIT_STRUCT_VAR(Cur_Energy);
  SET_DATA_READY_FLAG(Cur_Energy);
  SET_STRUCT_SUM(Cur_Energy);

  Prepaid_Clr_Month_Eng_Money((S_HEX_Time *) &Cur_Time0);
  
  #if USE_ENERGY_RAM_BAK EQ 1
  mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
  SET_STRUCT_SUM(Cur_Energy_Bak);
  #endif
  
  Save_Cur_Energy_PD_Data();
  Save_Cur_Energy_Data();
  Save_Cur_Energy_Bak0_Data();  
  Save_Cur_Energy_Bak1_Data();  
  Save_Cur_Energy_Bak2_Data();

  Get_N_Last_Settle_Time(MAX_ENERGY_SETTLE_NUM, (S_HEX_Time *) &Cur_Time0, &TempTime, &TempTime, sizeof(TempTime));
  SDI = _SDI_SETTLE_ENERGY_DATA;

  for(i = 0; i < MAX_ENERGY_SETTLE_NUM; i ++)
  {
    if(Cmp_Time(&TempTime, (S_HEX_Time *) &Cur_Time0) != TIME_AFT)
    {
      Debug_Print("Set Def Energy His Data, Time:");
      Print_HEX_Time((S_HEX_Time *) &TempTime);

      mem_cpy((void *) &Cur_Energy.Time, &TempTime, sizeof(TempTime), \
              (void *) &Cur_Energy.Time, sizeof(Cur_Energy.Time));
      SET_STRUCT_SUM(Cur_Energy);

      INC_ENERGY_SETTLE_DI(SDI);
      Write_Storage_Data(SDI, (void *) &Cur_Energy, sizeof(Cur_Energy));
    }
    Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
  }

  Write_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &SDI, sizeof(SDI));
  
  Settle_Energy_FF_Data(0);
//--------------------------------------送检专用，正式版需去掉-------------------
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL) //本地费控表才预置电量电费
  {
    if(Check_Meter_Factory_Status())
    {
      if(PREPAID_MODE EQ PREPAID_MONEY)
        Cur_Energy.Prepaid_Info.Left_Money = 200000; //置200元剩余金额
      else
        Cur_Energy.Prepaid_Info.Left_Energy = 200000; //置200度剩余电量
      SET_STRUCT_SUM(Cur_Energy);
     
      #if USE_ENERGY_RAM_BAK EQ 1
      mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
      SET_STRUCT_SUM(Cur_Energy_Bak);
      #endif
    
      Save_Cur_Energy_PD_Data();
      Save_Cur_Energy_Data();
    }
  }
//------------------------------------------------------------------  
}

//每隔一段时间自动保存当前电量、需量、需量时间等数据
void Period_Save_Cur_Data()
{
  DECLARE_BUF_TYPE(INT8U, 6, S_Bak_Hour);
  static S_Bak_Hour Bak_Hour =  {CHK_BYTE, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, CHK_BYTE};
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U Re;

  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(1 EQ Re);

  Re = CHECK_STRUCT_SUM(Cur_Time0);
  if(0 EQ Re)
  {
    ASSERT_FAILED();
  }

  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])//每分钟判断一次
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];

    if(Min_Bak.Var EQ 0)//分钟为0的情况下不存数!因为这个时刻可能是月冻结时刻，此时不应该存数，以免引起混乱
      return;

    Re = CHECK_STRUCT_VAR(Bak_Hour);
    ASSERT(1 EQ Re);

    SET_STRUCT_TIME(Cur_Energy, Cur_Time0);
    SET_STRUCT_TIME(Cur_Demand.Demand[0], Cur_Time0);
    SET_STRUCT_TIME(Cur_Demand.Demand[1], Cur_Time0);
    SET_STRUCT_SUM(Cur_Demand);
    SET_STRUCT_TIME(Cur_VolStat, Cur_Time0);

    //每半小时保存掉电数据, 该数据存放在铁电中
    if(Cur_Time0.Time[T_MIN] EQ 17 || Cur_Time0.Time[T_MIN] EQ 47)
    {
      Debug_Print("Every 30 Mins Save_Cur_Energy_Demand_PD_Data");
      Save_Cur_Energy_PD_Data();
      Save_Cur_Demand_PD_Data();
    }

    //每2小时保存数据, 该数据存放在EEROM中
    if(Cur_Time0.Time[T_HOUR] % 2 EQ 1 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[0])
    {
      Debug_Print("Every 2 Hour Save_Cur_Energy_Demand_Data");
      Bak_Hour.Buf[0] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Data();
      Save_Cur_Demand_Data();
    }

    //每6小时保存一次电量需量数据到备份的DI中, 该数据存放在EEROM中
    if(Cur_Time0.Time[T_HOUR] % 6 EQ 0 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[1])
    {
      Debug_Print("Every 2 Hours Save_Cur_Energy_Bak0_Data && Save_Cur_Demand_Bak_Data");
      Bak_Hour.Buf[1] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak0_Data();
      Save_Cur_Demand_Bak_Data();
    }

    //每8小时保存一次电量需量数据到备份的DI中, 该数据存放在EEROM中
    if(Cur_Time0.Time[T_HOUR] % 8 EQ 1 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[2])
    {
      Debug_Print("Every 8 Hours Save_Cur_Energy_Bak1_Data && Period_Save_RTC_BatTime");
      Bak_Hour.Buf[2] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak1_Data();
      Period_Save_RTC_BatTime(); //时钟电池工作时间
    }

    //每12小时保存一次电量需量数据到备份的DI中, 因为该数据在DataFlash中, 因此12小时存一次
    if(Cur_Time0.Time[T_HOUR] % 12 EQ 2 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[3])
    {
      Debug_Print("Every 12 hours Save_Cur_Energy_Bak2_Data");
      Bak_Hour.Buf[3] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak2_Data();
    }

    //每3小时保存电压统计掉电数据, 该数据存放在铁电中
    if(Cur_Time0.Time[T_HOUR] % 3 EQ 0 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[4])
    {
      Debug_Print("Every 3 hours Save_Cur_VolStat_PD_Data && Save_LoadData_Index");
      Bak_Hour.Buf[4] = Cur_Time0.Time[T_HOUR];    
      Save_Cur_VolStat_PD_Data();
      Save_LoadData_Index();
    }

    //每4小时保存电压统计数据, 以及负荷曲线索引参数, 该数据存放在EEROM中
    if(Cur_Time0.Time[T_HOUR] % 4 EQ 0 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[5])
    {
      Debug_Print("Every 4 hours Save_Cur_VolStat_Data && Save_LoadData_Index_Bak");
      Bak_Hour.Buf[5] = Cur_Time0.Time[T_HOUR];    
      Save_Cur_VolStat_Data();
      Save_LoadData_Index_Bak();
    }
  }
}

//费率方案切换处理, 主要是重新读取部分参数
//New_Scheme, 表示切换到该费率方案
//New_Scheme EQ YEAR_SCHEME0或者New_Scheme EQ YEAR_SCHEME1
//该函数的主要作用是更新套费率方案相关参数
void Year_Scheme_Changed_Proc()
{
  INT8U Re;

  Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(!(Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0 || Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME1))
  {
    ASSERT_FAILED();
    Cur_Rate_Info.Year_Scheme = YEAR_SCHEME0;//默认使用主费率方案
    SET_STRUCT_SUM(Cur_Rate_Info);
  }
  Debug_Print("Year_Scheme Changed! Use Scheme:%s", (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?"0":"1");

  Read_Year_Table_Para(Cur_Rate_Info.Year_Scheme);//从存储器中读取当前费率方案相关的参数 
}

//两套日时段方案发生切换时的处理
void Date_Scheme_Changed_Proc()
{
  Cal_Cur_Date_Table(CALC_ROM);//重新计算时段表号, 并且重新读取日时段表参数到Date_Table中 
}

//费率方案切换处理，用于预付费
void Rate_Scheme_Changed_Proc()
{ 
  Read_Rate_Scheme_Para(Cur_Rate_Info.Rate_Scheme);
}

//两套阶梯方案切换
void Step_Scheme_Changed_Proc()
{
  Read_Step_Scheme_Para(Cur_Rate_Info.Step_Scheme);  
}

//费率切换处理
void Rate_Changed_Proc()
{
  INT8U Re;

  Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Debug_Print("Rate Changed! Use %dth Rate", Cur_Rate_Info.Rate);
}

//计算当前费率方案和费率，以及是否发生费率切换，如果发生费率切换
//就重新从rom中读取相关参数等
void Check_Cur_Rate()
{
  S_Int32U static Sec = {CHK_BYTE, 0, CHK_BYTE};
  S_Int8U  static Min = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;  

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Time_Modify_Flag);
  ASSERT(1 EQ Re);
  
  //时间每走过1S才运行程序继续执行
  if(Sec.Var EQ Sec_Timer_Pub)
  {
    return;
  }
  else
  {
    Sec.Var = Sec_Timer_Pub;
  }

  if(Min.Var != Cur_Time0.Time[T_MIN] || Time_Modify_Flag.Var EQ 1)//每隔一分钟进入一次下面的流程
  {
    Time_Modify_Flag.Var = 0;
    Min.Var = Cur_Time0.Time[T_MIN];
    //检查当前费率信息
    Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
    if(1 != Re)//ASSERT(0 != Re))
    {
      ASSERT_FAILED();
      Check_Data_Avail();
    }
    
    //计算当前应该使用的费率方案, 判断当前套费率方案，如果方案发生了切换，则更新复费率参数Multi_Rate_Para, 以及更新当前日时段表   

    Calc_Cur_Year_Scheme(CALC_RAM);//计算当前年时区方案
    Calc_Cur_Date_Scheme(CALC_RAM);//计算当前日时段表方案
    Calc_Cur_Rate(CALC_RAM);//计算当前应该使用的费率
    Calc_Cur_Rate_Scheme(CALC_RAM); //计算当前分时费率方案(预付费)
    Calc_Cur_Step_Scheme(CALC_RAM); //计算当前阶梯方案(预付费)
  }
}
/*
//清除当月用电量,预付费用计算阶梯电价时用
void Clear_Prepaid_Month_Eng()
{
 // if(pTime -> Time[T_DATE] EQ Bcd2Hex_Byte(Settle_Time.Time_D_H[0][1]) &&\
  //   pTime -> Time[T_HOUR] EQ Bcd2Hex_Byte(Settle_Time.Time_D_H[0][0]))
  {
    Cur_Energy.Prepaid_Info.Month_Pos_Act = 0;  
    SET_STRUCT_SUM(Cur_Energy);
  }
}
*/
/*
//每月抄表日冻结处理
void Month_Data_Freeze()
{
  INT8U Re;
  static S_Int8U Hour_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  S_HEX_Time TempTime;
  
  //保证每小时只进来一次
  Re = CHECK_STRUCT_VAR(Hour_Bak);
  ASSERT(1 EQ Re);
  
  if(Hour_Bak.Var EQ Cur_Time0.Time[T_HOUR])
  return;
  else
  Hour_Bak.Var = Cur_Time0.Time[T_HOUR];
  
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *)&Cur_Time0);
  Re &= CHECK_STRUCT_SUM(Data_Freeze_Time);
  if(ASSERT(1 EQ Re))
  Check_Data_Avail();
  
  //时间数据不是BCD码
  //Re = C((INT8U *)(Data_Freeze_Time.DDHH), 2);
  //Re = CHECK_STRUCT_SUM(Data_Freeze_Time);
  //if(ASSERT(1 EQ Re))
  //Check_Data_Avail();
  
  //如果自动抄表时间设置错误
  if(ASSERT(Data_Freeze_Time.DDHH[0] <= 23))
  {
  Data_Freeze_Time.DDHH[0] = 0;
  SET_STRUCT_SUM(Data_Freeze_Time);
  }
  if(ASSERT(Data_Freeze_Time.DDHH[1] >= 1 &&\
      Data_Freeze_Time.DDHH[1] <= 31))
  {
  Data_Freeze_Time.DDHH[1] = 1;
  SET_STRUCT_SUM(Data_Freeze_Time);
  }
  
  //判断冻结日时间是否到了
  if(Cur_Time0.Time[T_HOUR] EQ Data_Freeze_Time.DDHH[0] &&\
   Cur_Time0.Time[T_DATE] EQ Data_Freeze_Time.DDHH[1])
  {
  Debug_Print("----------Month Data Freeze Start!----------");
  //获取当月冻结时间点
  Get_NowMonth_Freeze_Time((S_HEX_Time *)&Cur_Time0, &TempTime);//防止直接使用Cur_Time0产生的分钟误差

  //将需要冻结的数据的时间域置为冻结时间点
  SET_STRUCT_TIME(Cur_Energy, TempTime);
  SET_STRUCT_TIME(Cur_Demand.Demand[0], TempTime);
  SET_STRUCT_TIME(Cur_Demand.Demand[1], TempTime);
  SET_STRUCT_SUM(Cur_Demand);
  SET_STRUCT_TIME(Cur_VolStat, TempTime);
  
  Settle_Energy_Data(&TempTime);//冻结电量数据
  Settle_Demand_Data(&TempTime);//冻结需量数据
  Settle_VolStat_Data(&TempTime);//冻结电压统计数据

  }
}
*/

/*
//读取结算日参数
void Read_Settle_Para_From_Rom()
{
  INT8U i;
  INT16U Len;

  for(i = 0; i < 3; i ++)
  {
  Len = Read_Storage_Data(0x04000B01 + i, (INT8U *)Settle_Time.Time_D_H[i], (INT8U *)Settle_Time.Time_D_H, sizeof(Settle_Time.Time_D_H));
  ASSERT(Len EQ 2);
  }
}
*/

//检查pTime是否为电量和需量结算时间
INT8U Check_Eng_Settle_Time(S_BCD_Time *pTime)
{
  INT8U i;
  //每月电量和需量的结算
  for(i = 0; i < 3 ; i ++)
  {
    if(pTime -> Hour EQ Settle_Time.Time_D_H[i][0] && \
       pTime -> Date EQ Settle_Time.Time_D_H[i][1] && \
       pTime -> Min EQ 0)
    {
      return 1;
    }
  }

  return 0;
}

void Settle_Data()
{
  INT8U Re;
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  S_HEX_Time TempTime;

  //保证每小时只进来一次
  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(1 EQ Re);

  if(Min_Bak.Var EQ Cur_Time1.Min)
  {
    return;
  }
  else
  {
    Min_Bak.Var = Cur_Time1.Min;
  }

  Re = 1;
  Re &= Check_BCD_Time((S_BCD_Time *) &Cur_Time1);
  Re &= CHECK_STRUCT_SUM(Settle_Time);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  //电压统计数据的结算在每月1日0时
  Convert_BCD_2_HEX_Time((S_BCD_Time *) &Cur_Time1, &TempTime);//当前HEX时间

  if(Check_Eng_Settle_Time((S_BCD_Time *) &Cur_Time1))
  {
    Settle_Prepaid_Month_Eng(&TempTime); 
    Settle_Energy_Data(&TempTime);
    Settle_Demand_Data(&TempTime);
    Settle_VolStat_Data(&TempTime);
  }
}

//初始化电量数据
void Read_Energy_Data_From_Rom()
{
  //INT8U Err = NO_ERR;
  S_Energy* p;

  //先读取掉电存储区数据
  //再读普通数据
  //最后读备份区数据
  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  p = (S_Energy *) Pub_Buf0;

  if(Read_Storage_Data(_SDI_CUR_ENERGY_PD, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
     Check_Energy_Data((S_Energy *) p) != 1)
  {
    //需要保证存储的校验和正确且数据本身正确才认为读取成功
    Debug_Print("Read _SDI_CUR_ENERGY_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(_SDI_CUR_ENERGY, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
       Check_Energy_Data((S_Energy *) p) != 1)
    {
      Debug_Print("Read _SDI_CUR_ENERGY data error");
      OS_TimeDly_Ms(500);
      if(Read_Storage_Data(_SDI_CUR_ENERGY_BAK0, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
         Check_Energy_Data((S_Energy *) p) != 1)
      {
        Debug_Print("Read _SDI_CUR_ENERGY_BAK0 data error");
        OS_TimeDly_Ms(500);
        if(Read_Storage_Data(_SDI_CUR_ENERGY_BAK1, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
           Check_Energy_Data((S_Energy *) p) != 1)
        {
          Debug_Print("Read _SDI_CUR_ENERGY_BAK1 data error");
          if(Read_Storage_Data(_SDI_CUR_ENERGY_BAK2, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
             Check_Energy_Data((S_Energy *) p) != 1)
          {
            Debug_Print("Read _SDI_CUR_ENERGY_BAK2 data error");
            mem_set(p, 0, sizeof(Cur_Energy), p, sizeof(Pub_Buf0));
            Write_Storage_Data(_SDI_CUR_ENERGY_BAK2, p, ENERGY_SAVE_SIZE);
          }
          Write_Storage_Data(_SDI_CUR_ENERGY_BAK1, p, ENERGY_SAVE_SIZE);
        }
        Write_Storage_Data(_SDI_CUR_ENERGY_BAK0, p, ENERGY_SAVE_SIZE);
      }  
      Write_Storage_Data(_SDI_CUR_ENERGY, p, ENERGY_SAVE_SIZE);
    }
    Write_Storage_Data(_SDI_CUR_ENERGY_PD, p, ENERGY_SAVE_SIZE);
  }       

   DIS_PD_INT;
  mem_cpy((void *) &Cur_Energy, p, sizeof(Cur_Energy), (void *) &Cur_Energy, sizeof(Cur_Energy));
  INIT_STRUCT_VAR(Cur_Energy);  
  SET_DATA_READY_FLAG(Cur_Energy);
  SET_STRUCT_SUM(Cur_Energy);

  #if USE_ENERGY_RAM_BAK > 0
  mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy_Bak), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak)); 
  #endif
            
   EN_PD_INT;

  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}
//该函数主要是为液晶显示第一屏准备参数和数据
//后面的流程还会重新读这些数据
void Read_Energy_Data_Para_For_Show()
{
  INT8U Rst_Flag;  

  //读取掉电时存储的电量数据, 没有读取成功则读取备份存储的数据 
  Rst_Flag = Check_Rst_Flag();
  if(Rst_Flag EQ POWER_ON_RST || Check_Energy_Data((S_Energy *) &Cur_Energy) EQ 0)//电源上电或者校验和错误的情况下都必须读取ROM中的数据
  {
    Debug_Print("PowerOn Read Energy Data");
    Read_Energy_Data_From_Rom();
  }

  Read_Mode_Word();//读取模式字，用于计算正向有功的模式字
  //电能显示小数位数
  /*
  if(Read_Storage_Data(0xC115, (void *)(&Disp_Digs.Energy_Digs), (void *)(&Disp_Digs.Energy_Digs), 1) != 1 || Err != NO_ERR)
    Debug_Print("Read 0xC125 Para Err");    
  Disp_Digs.Energy_Digs = Bcd2Hex_Byte(Disp_Digs.Energy_Digs);
  SET_STRUCT_SUM(Disp_Digs);
  */
}



//掉电保存电量和需量数据等
//此函数因为是掉电存储，因此没有延时函数
void PowerDown_Save_Energy_Data()
{
  //保存掉电时存储的电量数据, 没有读取成功则读取备份存储的数据 
  Write_Storage_Data(_SDI_CUR_ENERGY_PD, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
}

//掉电存数
void PowerDown_Save_Data()
{
  PowerDown_Save_Energy_Data();//保存电量数据
  PowerDown_Save_Demand_Data();//保存需量数据
  PowerDown_Save_VolStat_Data(); //保存电压统计数据
}

#pragma optimize = none
//将当前费率信息等打印出来
void Debug_Print_Cur_Energy_Info()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Counts = {CHK_BYTE, 0, CHK_BYTE};
  INT8U i, Re;

  if(Check_Debug_En() EQ 0)//非工厂状态不打印
    return;

  if(Cur_Time0.Time[T_MIN] EQ Min.Var)//每分钟执行一次该函数
  {
    return;
  }

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Counts);
  ASSERT(1 EQ Re);

  Min.Var = Cur_Time0.Time[T_MIN];

  Clr_Ext_Inter_Dog();
  Debug_Print("----------Cur_Rate_Info-----------");
  Debug_Print("Cur_Time:%d-%d-%d %d:%d, Week:%d", Cur_Time0.Time[T_YEAR], Cur_Time0.Time[T_MONTH],\
    Cur_Time0.Time[T_DATE], Cur_Time0.Time[T_HOUR], Cur_Time0.Time[T_MIN], Cur_Time0.Week);
  Debug_Print("Cur Year Scheme:%s", (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?"0":"1");
  Debug_Print("Cur Date Scheme:%s", (Cur_Rate_Info.Date_Scheme EQ DATE_SCHEME0)?"0":"1");
  Debug_Print("Cur Rate:%d", Cur_Rate_Info.Rate);

  if(Cur_Rate_Info.Date_Flag EQ HOLIDAY)
  {
    Debug_Print("Today is Holiday, Holiday_Index = %d", Cur_Rate_Info.Holiday_Index);
  }
  else if(Cur_Rate_Info.Date_Flag EQ WEEK_REST_DAY)
  {
    Debug_Print("Today is Week_Rest_Day");
  }
  else if(Cur_Rate_Info.Date_Flag EQ NORMAL_DAY)
  {
    Debug_Print("Today is Normal_Day, Year_Peirod = %d", Cur_Rate_Info.Year_Period);
  }
  else
  {
    Debug_Print("Today Date_Flag Err");
  }

  //当前日时段表号和当前日时段
  Debug_Print("Cur Date_Table:%d Date_Period:%d", \
  Cur_Rate_Info.Date_Table, Cur_Rate_Info.Date_Period);
  //当前正向有功总
  Debug_Print("Cur_Pos_Active:%ld", Cur_Energy.Pos_Active[0]);

  Counts.Var++;
  if(Counts.Var >= 5)//每隔5分钟打印一次当前电能值
  {
    Counts.Var = 0;

    Clr_Ext_Inter_Dog();
    Debug_Print("|-----------------------------Total_Energy-------------------------|"); 
    Debug_Print("| Rate Pos_Activ Neg_Activ Quad0_Rea Quad1_Rea Quad2_Rea Quad3_Rea |");
    for(i = 0; i <= Multi_Rate_Para.Rates; i++)
    {
      Debug_Print("|   %2d %9ld %9ld %9ld %9ld %9ld %9ld |", i, Cur_Energy.Pos_Active[i], Cur_Energy.Neg_Active[i],\
                   Cur_Energy.Quad_Reactive[0][i], Cur_Energy.Quad_Reactive[1][i], Cur_Energy.Quad_Reactive[2][i], Cur_Energy.Quad_Reactive[3][i]);
    }

    //打印三相电能
    Debug_Print("|------------------------------------------------------------------|"); 

    OS_TimeDly_Ms(50);

    Clr_Ext_Inter_Dog();  
    Debug_Print("|-----------------------------Phase_Energy-------------------------|"); 
    Debug_Print("| Phas Pos_Activ Neg_Activ Quad0_Rea Quad1_Rea Quad2_Rea Quad3_Rea |");

    for(i = 0; i < 3; i++)
    {
      Debug_Print("|    %c %9ld %9ld %9ld %9ld %9ld %9ld |", (INT8S) ('A' + i), Cur_Energy.Phase_Pos_Active[i], Cur_Energy.Phase_Neg_Active[i],\
                  Cur_Energy.Phase_Quad_Reactive[i][0], Cur_Energy.Phase_Quad_Reactive[i][1],\
                  Cur_Energy.Phase_Quad_Reactive[i][2], Cur_Energy.Phase_Quad_Reactive[i][3]);
    }
    Debug_Print("|------------------------------------------------------------------|");
  }
}

//初始化电量和需量相关参数
void Read_Energy_Para_From_Rom()
{
  Read_Mode_Word();//读取模式字
  
  Read_Settle_Para_From_Rom(); //读取结算时间 
  Read_Cur_Scheme_From_Rom(); //读取之前的年时区表和日时段表号
  Read_Multi_Rate_Para(); //先读取费率相关参数 
  Read_Prepaid_Para_From_Rom(); //读取预付费参数
  
  //Read_Scheme_Rate_Para();//
  //以下部分读取套费率相关参数, 读取了Multi_Rate_Para, Year_Table，Holiday_Table

  Calc_Cur_Year_Scheme(CALC_ROM);//计算当前年时区方案, CALC_ROM标志表示从ROM中读取参数重新判断
  OS_TimeDly_Ms(100);
  //Calc_Cur_Year_Scheme(CALC_ROM)内部会调用Calc_Cur_Date_Scheme(CALC_ROM),因此此处不需要
  //Calc_Cur_Date_Scheme(CALC_ROM);//计算当前使用的日时段表方案
  //OS_TimeDly_Ms(100);
  Calc_Cur_Rate(CALC_ROM);//计算当前应该使用的费率
  OS_TimeDly_Ms(100);
  Calc_Cur_Rate_Scheme(CALC_ROM); //计算当前费率方案（预付费用）
  OS_TimeDly_Ms(100);
  Calc_Cur_Step_Scheme(CALC_ROM); //计算当前梯度(预付费用)
}


void Clear_All_Data()
{
  DISP_CLR_DATA_INFO;
  
  Set_Def_Energy_Data();
  Set_Def_Demand_Data();
}

//获取当前费率信息
//返回到pDst中
//pDst[0] 当前运行时区方案 0为第一套，1为第二套
//pDst[1] 当前年时区
//pDst[2] 当前运行日时段方案,0为第一套，1为第二套
//pDst[3] 当钱日时段表号
//pDst[4] 当前日时段号
//pDst[5] 当前费率
//pDst[6] 当前费率方案,0表示第一套,1为第二套
//pDst[7] 当前阶梯方案,0为第一套，1为第二套
//pDst[8] 当前阶梯号, 从1开始计
//pDst[9] 当前表类型-电表类型(00非预付费,01电量型预付费表,02电费型预付费表)
//pDst[10] 当前为分时计费或者本地计费? 0表示分时，1表示阶梯, 2表示混合电价
//pDst[11] 当前为本地或者远程预付费 0表示本地，1表示远程
//以上数据都是BCD码
//返回值表示返回数据长度
INT8U Get_Cur_Rate_Info(INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  //TRACE();
  
  if(!(pDst >= pDst_Start && pDst + 12 <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  
  *pDst = (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?0:1; //当前年时区方案
  Hex2Bcd(Cur_Rate_Info.Year_Period, pDst + 1, 1, pDst_Start, DstLen); //当前年时区号
  *(pDst + 2) = (Cur_Rate_Info.Date_Scheme EQ DATE_SCHEME0)?0:1; //当前日时段表方案
  Hex2Bcd(Cur_Rate_Info.Date_Table, pDst + 3, 1, pDst_Start, DstLen); //当前日时段表号
  Hex2Bcd(Cur_Rate_Info.Date_Period, pDst + 4, 1, pDst_Start, DstLen); //当前日时段号
  Hex2Bcd(Cur_Rate_Info.Rate, pDst + 5, 1, pDst_Start, DstLen); //当前费率
  *(pDst + 6) = (Cur_Rate_Info.Rate_Scheme EQ RATE_SCHEME0)?0:1; //当前费率方案(预付费)
  *(pDst + 7) = (Cur_Rate_Info.Step_Scheme EQ STEP_SCHEME0)?0:1; //当前阶梯方案(预付费)
  *(pDst + 8) = PREPAID_STEP_NO; //当前阶梯号
  
  if(PREPAID_EN EQ 0) //非预付费表
    *(pDst + 9) = 0x00;
  else if(PREPAID_MODE EQ ENERGY_MODE) //电量型预付费
    *(pDst + 9) = 0x01;
  else
    *(pDst + 9) = 0x02; //电费型预付费
  
  //分时计费或者本地计费? 0表示分时，1表示阶梯, 2表示混合电价
  *(pDst + 10) = PREPAID_MONEY_MODE;
  //本地或者远程预付费 0表示本地，1表示远程
  *(pDst + 11) = PREPAID_LOCAL_REMOTE;
  
  return 12;
}

//检查某参数是否是电能任务相关参数
INT8U Check_Energy_Proc_Para(PROTO_DI PDI)
{
  if((PDI & 0xFFFFFF00) EQ 0x10000200)//校表参数
    return 0;
  else if(PDI EQ 0x0EA20000 || PDI EQ 0x0EA20001 || PDI EQ 0x0EA20002)//模块参数设置
    return 0;
  
  return 1;
}

/*
typedef struct
{
  INT32U Energy;  //当此购电电量
  INT32U Money;   //当此购点金额
  
  INT32U Bef_Buy_Energy; //当此购电钱电量
  INT32U Bef_Buy_Money;  //当此购电钱金额
}S_Cur_Prepaid; //当此购电信息
*/



//检查参数是否发生修改
void Check_Energy_Para_Modified()
{
  PROTO_DI PDI;
  INT8U Re;
  static S_Int32U Sec_Bak0 = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Count = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Init_Para_Flag = {CHK_BYTE, 0, CHK_BYTE};

  if(Sec_Bak0.Var EQ Sec_Timer_Pub)//每秒才进来查一次
  {
    return;
  }

  Sec_Bak0.Var = Sec_Timer_Pub;
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Count);
  Re &= CHECK_STRUCT_VAR(Init_Para_Flag);
  ASSERT(1 EQ Re);

  OS_TimeDly_Ms(20);
  //对设置过的参数逐个处理  
  while(Get_Para_Modify(&PDI) EQ 1)
  {
    if(Check_Energy_Proc_Para(PDI))//如果是当前任务相关的参数则需要重新初始化参数
    {
      Init_Para_Flag.Var = 1;//需要重新初始化参数 
      Sec_Bak.Var = Sec_Timer_Pub;//秒计时器    
      Count.Var = 0;//重新开始计数, 10S后仍无参数设置则，重新初始化电量相关参数
    }
  }

  //是否需要重新初始化?
  if(1 EQ Init_Para_Flag.Var && Sec_Bak.Var != Sec_Timer_Pub)
  {
    Sec_Bak.Var = Sec_Timer_Pub;
    Count.Var++;//秒计数
  }

  //修改当前任务相关参数后10S，重新初始化参数
  if(Count.Var >= 2 && 1 EQ Init_Para_Flag.Var)
  {
    //设置了电量相关参数
    Init_Para_Flag.Var = 0;
    Count.Var = 0;
    Refresh_Para_From_Rom();//重新将
  }
}

//初始化电量和需量相关的参数
void Init_Energy_Demand_Ram_Para()
{
  //初始化信号量

  //初始化费率信息
  mem_set((void *) &Cur_Rate_Info, 0, sizeof(Cur_Rate_Info), (void *) &Cur_Rate_Info, sizeof(Cur_Rate_Info));
  INIT_STRUCT_VAR(Cur_Rate_Info);
  SET_STRUCT_SUM(Cur_Rate_Info);//费率信息
  //初始化日时段表
  mem_set((void *) &Date_Table, 0, sizeof(Date_Table), (void *) &Date_Table, sizeof(Date_Table));
  SET_STRUCT_SUM(Date_Table);//日时段表

  //初始化参数修改标志
  //Clear_Flag.Flag = CLEAR_END_FLAG;//清除标志, 清电量需量等的标志
  //SET_STRUCT_SUM(Clear_Flag);

  //两个全局缓冲区的头尾检验字节
  INIT_STRUCT_VAR(_Pub_Buf);
  INIT_STRUCT_VAR(_Pub_Buf0);
  INIT_STRUCT_VAR(Pub_Timer);
  Energy_Cumu_Counts.Var = 0; //电量累加次数, 供测试程序用
  INIT_STRUCT_VAR(Energy_Cumu_Counts);

  Chk_Data_Flag.Chk_Flag = 0;
  SET_STRUCT_SUM(Chk_Data_Flag);
}

//获取当前正向有功总电能
INT32U Get_Pos_Act_Eng()
{
  return Cur_Energy.Pos_Active[0]; 
}


#undef ENERGY_C
