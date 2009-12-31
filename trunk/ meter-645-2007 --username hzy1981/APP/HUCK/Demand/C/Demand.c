#define DEMAND_C
#include "Includes.h"

//#define Ex_Max_Demand PD_Save_Data.Exceed_Max_Demand

/*
需量和电压统计等月数据冻结的相关问题
1 冻结完成后，将当前数据存储区的数据全部写为0，表示当前数据区的数据为空，尚未写入当月（新的一月）的数据
2 冻结时间点，不自动存数，避免可能的数据乱(实际上应该不可能出问题)
3 如果在冻结后马上复位了，那么重启后，读取当前数据区全为0，不会补冻，如果不慎进入了补冻流程，由于可以读出前月历史数据，所以还是不会补冻
4 如果在冻结前一刻复位了，重启后，仍然会按照历史数据进行冻结。
5 如果在冻结的过程中复位了, 数据不能形成校验和, 当前数据也没有重置为0，所以上电后还是会补冻
*/

//初始化需量相关参数
void Read_Demand_Para_From_Rom()
{
  INT16U Len;

  TRACE();
  //读取需量周期
  Len = Read_Storage_Data(SDI_DEMAND_PERIOD, (INT8U *) &Demand_Para.Period, (INT8U *) &Demand_Para.Period, 1);
  ASSERT(1 EQ Len);
  Demand_Para.Period = Bcd2Hex_Byte(Demand_Para.Period);
  //读取需量滑差时间
  Len = Read_Storage_Data(SDI_DEMAND_SLID, (INT8U *) &Demand_Para.Slide_Time, (INT8U *) &Demand_Para.Slide_Time, 1);
  ASSERT(1 EQ Len);
  Demand_Para.Slide_Time = Bcd2Hex_Byte(Demand_Para.Slide_Time);

  SET_STRUCT_SUM(Demand_Para);
}

//检查需量参数是否合法
void Check_Demand_Para_Avail()
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Demand_Para);//需量参数
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Read_Demand_Para_From_Rom();
  }
}

/*
//获取INT24U数据
INT32U Get_INT24U_Data(S_INT24U *pData)
{
  INT32U Data;
  
  Data = 0;
  mem_cpy(&Data, pData -> Data, sizeof(pData -> Data), &Data, sizeof(Data));
  return Data;
}

//设置INT24U数据
void Set_INT24U_Data(S_INT24U *pData, INT32U Data)
{
  if((Data & 0xFF000000) != 0) 
  {
    ASSERT_FAILED();
    return;
  }
  
  mem_cpy(pData -> Data, &Data, sizeof(pData -> Data), pData -> Data, sizeof(pData -> Data));
  return;
}
*/

//清除某一个需量单元数据
void Clr_Demand_Unit(INT8U Index)
{
  INT8U i;

  TRACE();

  if(Index >= S_NUM(Demand_Accu.Phase_Accu[0].Pos_Active))
  {
    ASSERT_FAILED();
    return;
  }

  //清分相累加
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    /*
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Pos_Active[Index] , 0);//正向有功15个功率累加单元, 单位0.0001kw
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Neg_Active[Index] , 0);//反向有功15个功率累加单元, 单位0.0001kw
    
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Pos_Apparent[Index] , 0);//正向有功15个功率累加单元, 单位0.0001kw
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Neg_Apparent[Index] , 0);//反向有功15个功率累加单元, 单位0.0001kw
    
    //Demand_Accu.Phase_Accu[i].Comb_Reactive1[Index] = 0;//正向无功15个功率累加单元, 单位0.0001kvar
    //Demand_Accu.Phase_Accu[i].Comb_Reactive2[Index] = 0;//反向无功15个功率累加单元, 单位0.0001kvar
    
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[0][Index] , 0);//四象限无功15个功率累加单元
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[1][Index] , 0);//四象限无功15个功率累加单元
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[2][Index] , 0);//四象限无功15个功率累加单元
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[3][Index] , 0);//四象限无功15个功率累加单元
    */
    Demand_Accu.Phase_Accu[i].Pos_Active[Index] = 0;
    Demand_Accu.Phase_Accu[i].Neg_Active[Index] = 0;
    Demand_Accu.Phase_Accu[i].Pos_Apparent[Index] = 0;
    Demand_Accu.Phase_Accu[i].Neg_Apparent[Index] = 0;
    Demand_Accu.Phase_Accu[i].Quad_Reactive[0][Index] = 0; 
    Demand_Accu.Phase_Accu[i].Quad_Reactive[1][Index] = 0; 
    Demand_Accu.Phase_Accu[i].Quad_Reactive[2][Index] = 0; 
    Demand_Accu.Phase_Accu[i].Quad_Reactive[3][Index] = 0;     
    SET_STRUCT_SUM(Demand_Accu.Phase_Accu[i]);
  }

  //清次数和时间统计
  Demand_Accu.Accu_Stat.Counts[Index] = 0;
  Demand_Accu.Accu_Stat.Mins[Index] = 0;
  SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
}

//检查需量累加单元的正确性
void Check_Demand_Accu()
{
  INT8U i;

  TRACE();

  if(CHECK_STRUCT_SUM(Demand_Accu.Accu_Stat) EQ 0)//Counts或者Mins等如果发生错误, 则累加单元也应该清掉
  {
    ASSERT_FAILED();
    Clr_Demand_Accu();
  }
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    if(CHECK_STRUCT_SUM(Demand_Accu.Phase_Accu[i]) EQ 0)
    {
      ASSERT_FAILED();
      mem_set((void *) &Demand_Accu.Phase_Accu[i], 0, sizeof(Demand_Accu.Phase_Accu), (void *) &Demand_Accu, sizeof(Demand_Accu));
      SET_STRUCT_SUM(Demand_Accu.Phase_Accu[i]);
    }

    if(CHECK_STRUCT_SUM(Demand_Accu.Phase_Cur[i]) EQ 0)
    {
      ASSERT_FAILED();
      mem_set((void *) &Demand_Accu.Phase_Cur[i], 0, sizeof(Demand_Accu.Phase_Cur), (void *) &Demand_Accu, sizeof(Demand_Accu));
      SET_STRUCT_SUM(Demand_Accu.Phase_Cur[i]);
    }
  }
}

//清除整个功率累加单元
void Clr_Demand_Accu()
{
  INT8U i;
  
  TRACE();
  
  Debug_Print("Clear Demand Accu!!!");
  for(i = 0; i < MAX_PERIOD_SLIDE_RATIO; i ++)
    Clr_Demand_Unit(i);
  
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    mem_set((void *)&Demand_Accu.Phase_Cur[i], 0, sizeof(Demand_Accu.Phase_Cur[i]), \
            (void *)&Demand_Accu.Phase_Cur[0], sizeof(Demand_Accu.Phase_Cur));
    SET_STRUCT_SUM(Demand_Accu.Phase_Cur[i]);
  }
}

//检查功率是否反向 
void Check_Power_Reverse()
{
  INT8U Re;
  static S_Int8U Power_Direct = {CHK_BYTE, 0x00, CHK_BYTE};
  
  Re = CHECK_STRUCT_VAR(Power_Direct);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  if(Read_Event_Status(ID_EVENT_SUM_NEG_CURR) EQ 1) //当前反向了
  {
    if(Power_Direct.Var EQ 0) //之前 是 正向的
    {
      Power_Direct.Var = 1;
      Debug_Print("Power Direct changed, Neg!");
      Clr_Demand_Accu();
    }
  }
  else
  {
    if(Power_Direct.Var EQ 1)
    {
      Power_Direct.Var = 0;
      Debug_Print("Power Direct changed, Pos!");
      Clr_Demand_Accu();
    } 
  }
}

//需量累加计算, 每秒调用一次该函数
//该函数对每个功率累加单元进行累加，并根据当前时间决定是否产生一次需量
void Demand_Accumu()
{
  INT8U i, j, k, Quad, Re;
  INT32U Active,React, Apparent;

  TRACE();

  Re = CHECK_STRUCT_SUM(Demand_Para);
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Check_Demand_Accu();

  if(Demand_Para.Slide_Time EQ 0)//保证Demand_Accu.Slide_Time != 0
  {
    ASSERT_FAILED();
    Demand_Para.Slide_Time = 1;
    SET_STRUCT_SUM(Demand_Para);
  }

  //判断需量周期和滑差时间必须满足的条件
  if(!((Demand_Para.Period % Demand_Para.Slide_Time EQ 0 && \
  Demand_Para.Period / Demand_Para.Slide_Time >= 1 && \
  Demand_Para.Period / Demand_Para.Slide_Time <= MAX_PERIOD_SLIDE_RATIO)))
  {
    //如果条件不成立，默认为1分钟滑差时间和15分钟需量周期
    ASSERT_FAILED();
    Debug_Print("Demand_Para error");
    Demand_Para.Slide_Time = 1;
    Demand_Para.Period = MAX_PERIOD_SLIDE_RATIO; 
    SET_STRUCT_SUM(Demand_Para);
  }

  Check_Power_Reverse(); //检查功率是否发生换向，换向则清需量累加单元
  
  Re = 1;
  Re &= CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);
  Re &= CHECK_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  ASSERT(1 EQ Re);
  if(1 EQ Re)
  {
    //对每个滑动窗口(功率累加单元)进行累加
    for(i = 0; i < MAX_PERIOD_SLIDE_RATIO && i < Demand_Para.Period / Demand_Para.Slide_Time; i++)
    {
      for(j = 0; j < DEMAND_ACCU_PHASE_NUM; j ++)//分别对总、A、B、C进行累加计算
      {
        if(j EQ 0)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.Sum;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.Sum / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.Sum / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.Sum / POWER_DATA_RATIO;
        }
        else if(j EQ 1)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.A;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.A / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.A / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.A / POWER_DATA_RATIO;
        }
        else if(j EQ 2)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.B;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.B / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.B / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.B / POWER_DATA_RATIO;
        }
        else if(j EQ 3)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.C;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.C / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.C / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.C / POWER_DATA_RATIO;
        }

      //有功 
      if(Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir EQ POWER_DIRECT_N)//正向有功功率
      {
        /*
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Active[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Active[i], Data + Active); //正向有功
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Apparent[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Apparent[i], Data + Apparent); //正向视在
        */
        Demand_Accu.Phase_Accu[j].Pos_Active[i] += Active;
        Demand_Accu.Phase_Accu[j].Pos_Apparent[i] += Apparent; 
      }
      else//反向有功
      {
        /*
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Active[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Active[i],Data + Active); //反向有功
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Apparent[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Apparent[i], Data + Apparent); //反向视在
        */
        Demand_Accu.Phase_Accu[j].Neg_Active[i] += Active;
        Demand_Accu.Phase_Accu[j].Neg_Apparent[i] += Apparent;
        
      }

//必须保证 QUADRANT1->QUADRANT4按序递增!!!!        
#if QUADRANT2!=QUADRANT1+1 || QUADRANT3!=QUADRANT2+1 || QUADRANT4!=QUADRANT3+1
#error "QUADRANT macro define error!"
#endif     
      for(k = 0; k < 4; k ++)
      {
        if(Quad EQ (QUADRANT1 + k)) //当前是在第几象限?
        {
          /*
          Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i]);
          Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i], Data + React); //反向视在
          */
          Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] += React;
          break;
        }
      }
      
      if(k EQ 4 && NO_QUADRANT != Quad)
        ASSERT_FAILED();      
        //------------------计算组合无功需量，四象限无功-------------
      /*
        for(k = 0; k < 4; k ++)
        {
          if(Quad EQ (QUADRANT1 + k)) //当前是在第几象限?
          {
            Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] += React;
            //组合无功1
            if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2))//加？
              Demand_Accu.Phase_Accu[j].Comb_Reactive1[i] += React;
            else if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2 + 1))//减？
              Demand_Accu.Phase_Accu[j].Comb_Reactive1[i] += React;
          
            //组合无功2        
            if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2))//加？
              Demand_Accu.Phase_Accu[j].Comb_Reactive2[i] += React;
            else if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2 + 1))//减？
              Demand_Accu.Phase_Accu[j].Comb_Reactive2[i] += React;  
            
            break;
          }    
        }
        
        if(k EQ 4 && NO_QUADRANT != Quad)
          ASSERT_FAILED();
        */
      
        SET_STRUCT_SUM(Demand_Accu.Phase_Accu[j]);
      }


      Demand_Accu.Accu_Stat.Counts[i] ++;
      SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
    }
  }


}

//当前需量数据的生成
void Demand_Generate()//生成需量
{
  INT8U Re;
  INT16U Counts,Mins;
  static S_Int8U Min_Bak =  {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U i,j,k;
  
  //每分钟判下是否到了出需量时间
  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(1 EQ Re);
  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];  
    Mins = (INT16U) Cur_Time0.Time[T_HOUR] * 60 + (INT16U) Cur_Time0.Time[T_MIN];

    if(Demand_Para.Period != 0 && (Mins % Demand_Para.Period) EQ 0)//需量周期到
    {
      Set_Event_Instant(ID_DEMAND_ARRIVE);//需量周期
      Port_Out_Pub(EXT_ID_DEMAND,85);
      Debug_Print("Demand Period Arrived!!!");
    }

    //每过一个滑差时间出一次需量, 如果不是滑差周期，则清除一个最大功率单元，保证不会技术
    Counts = 0;
    i = 0;

    //滑差时间！=0
    if(Demand_Para.Slide_Time EQ 0)
    {
      ASSERT_FAILED();
      Demand_Para.Slide_Time = 1;
    }

    for(j = 0; j < MAX_PERIOD_SLIDE_RATIO && j < (Demand_Para.Period / Demand_Para.Slide_Time); j ++)
    {
      if(Demand_Accu.Accu_Stat.Counts[j] >= 30) //起码走过了30s,才认为可增加1分钟
        Demand_Accu.Accu_Stat.Mins[j]++;//分钟计数
      
      if(Counts < Demand_Accu.Accu_Stat.Counts[j])//找到当前需量计数最大的那个单元来出需量
      {
        i = j;
        Counts = Demand_Accu.Accu_Stat.Counts[j];
      }
    }

    if(Demand_Para.Slide_Time != 0 && (Mins % Demand_Para.Slide_Time) EQ 0)//滑差周期到, 出需量时间到
    {
      if(Counts != 0)
      {
        //计算平均值，也就是需量
        //if(Counts>=(INT32U)Demand_Para.Period*(60-10))//防止内部秒计数器的偏差故减去10S
        if(Demand_Accu.Accu_Stat.Mins[i] >= (INT32U) Demand_Para.Period)
        {
          Set_Event_Instant(ID_SLIP_ARRIVE);//滑差周期
          Port_Out_Pub(EXT_ID_SLIPE,85);      
          Debug_Print("Demand Slide Arrived!!!, Unit %d,Mins=%d,Counts=%d",i,Demand_Accu.Accu_Stat.Mins[i],Counts);
      
          for(j = 0; j < DEMAND_ACCU_PHASE_NUM; j ++)
          {
            //正反向有功需量
            Demand_Accu.Phase_Cur[j].Pos_Active = Demand_Accu.Phase_Accu[j].Pos_Active[i] / Counts;
            Demand_Accu.Phase_Cur[j].Neg_Active = Demand_Accu.Phase_Accu[j].Neg_Active[i] / Counts; 
            //正反向视在需量
            Demand_Accu.Phase_Cur[j].Pos_Apparent = Demand_Accu.Phase_Accu[j].Pos_Apparent[i] / Counts;
            Demand_Accu.Phase_Cur[j].Neg_Apparent = Demand_Accu.Phase_Accu[j].Neg_Apparent[i] / Counts;
            //组合无功1，2需量
            //Demand_Accu.Phase_Cur[j].Comb_Reactive1 = Demand_Accu.Phase_Accu[j].Comb_Reactive1[i] / Counts;
            //Demand_Accu.Phase_Cur[j].Comb_Reactive2 = Demand_Accu.Phase_Accu[j].Comb_Reactive2[i] / Counts;
            //四象限无功需量
            for(k = 0; k < 4; k ++)
              Demand_Accu.Phase_Cur[j].Quad_Reactive[k] = Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] / Counts;

            Demand_Accu.Phase_Cur[j].Comb_Reactive1 = 0;
            Demand_Accu.Phase_Cur[j].Comb_Reactive2 = 0;
            for(k = 0; k < 4; k ++)
            {
              //if(Quad EQ (QUADRANT1 + k)) //当前是在第几象限?
              //{
                //Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] += React;
                //组合无功1
                if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2))//加？
                  Demand_Accu.Phase_Cur[j].Comb_Reactive1 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];
                else if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2 + 1))//减？
                  Demand_Accu.Phase_Cur[j].Comb_Reactive1 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];
              
                //组合无功2        
                if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2))//加？
                  Demand_Accu.Phase_Cur[j].Comb_Reactive2 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];
                else if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2 + 1))//减？
                  Demand_Accu.Phase_Cur[j].Comb_Reactive2 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];  
              //}    
            }
        
            SET_STRUCT_SUM(Demand_Accu.Phase_Cur[j]);
          }
  
          Mins = Demand_Accu.Accu_Stat.Mins[i];
  
          //将该功率累加单元清0      
          Clr_Demand_Unit(i);
          
          //打印需量相关调试信息
          Debug_Print("------Demand Update-----");
          Debug_Print("The  %dth Unit make demand, Mins= %d, Counts= %d", i, Mins, Counts);
          Debug_Print("Demand:Pos_Act= %ld", Demand_Accu.Phase_Cur[0].Pos_Active);
          Debug_Print("Demand:Neg_Act= %ld", Demand_Accu.Phase_Cur[0].Neg_Active);
          Debug_Print("Demand:Pos_App= %ld", Demand_Accu.Phase_Cur[0].Pos_Apparent);
          Debug_Print("Demand:Neg_App= %ld", Demand_Accu.Phase_Cur[0].Neg_Apparent); 
          Debug_Print("Demand:Quad1= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[0]);
          Debug_Print("Demand:Quad2= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[1]);
          Debug_Print("Demand:Quad3= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[2]);
          Debug_Print("Demand:Quad4= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[3]);          
          Debug_Print("Demand:Comb_Reactive1= %ld", Demand_Accu.Phase_Cur[0].Comb_Reactive1);
          Debug_Print("Demand:Comb_Reactive2= %ld", Demand_Accu.Phase_Cur[0].Comb_Reactive2);
        }
        else
          Clr_Demand_Unit(i);//此时应该是刚上电阶段
      }
    }
    
    //for(j = 0; j < MAX_PERIOD_SLIDE_RATIO && j < (Demand_Para.Period / Demand_Para.Slide_Time); j ++)
      //Demand_Accu.Accu_Stat.Mins[j]++;//分钟计数
    
    SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
  }  
  
}

//当前有无功需量，生成带符号的数据
void Sign_Demand_Generate()
{
  INT8U i;
  
  if(Measu_Sign_InstantData_PUCK.Curr.Sum >0)//当前电流为正
  {
    Sign_Demand.Active = (INT32S)Demand_Accu.Phase_Cur[0].Pos_Active;
    Sign_Demand.Apparent = (INT32S)Demand_Accu.Phase_Cur[0].Pos_Apparent;    
  }
  else
  {
    Sign_Demand.Active = 0 - (INT32S)Demand_Accu.Phase_Cur[0].Neg_Active;
    Sign_Demand.Apparent = 0 - (INT32S)Demand_Accu.Phase_Cur[0].Neg_Apparent;  
  }
  
  //当前象限
  i = Measu_InstantData_ToPub_PUCK.Quadrant.Sum;
  if(i EQ QUADRANT1)
    i = 0;
  else if(i EQ QUADRANT2)
    i = 1;
  else if(i EQ QUADRANT3)
    i = 2;
  else
    i = 3;
  
  if(GET_BIT(Energy_Comb_Word.Reactive[0],i*2) ||\
     GET_BIT(Energy_Comb_Word.Reactive[0],i*2 + 1))//当前运行在组合无功1，正向无功?
    Sign_Demand.Reactive = (INT32S)Demand_Accu.Phase_Cur[0].Comb_Reactive1;
  else if(GET_BIT(Energy_Comb_Word.Reactive[1],i*2) ||\
          GET_BIT(Energy_Comb_Word.Reactive[1],i*2 + 1))//当前运行在组合无功2，反向无功?
    Sign_Demand.Reactive = 0 - (INT32S)Demand_Accu.Phase_Cur[0].Comb_Reactive2;
  else
    Sign_Demand.Reactive = 0;
}

/*
//需量数据清0处理, 在复位时调用该函数
//跨月时需要清需量累加中间单元？暂定为不清
void Demand_Accu_Clear()
{
  INT8U i;

  TRACE();

  mem_set((void *) &Demand_Accu, 0, sizeof(Demand_Accu), (void *) &Demand_Accu, sizeof(Demand_Accu));
  INIT_STRUCT_VAR(Demand_Accu);
  
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    SET_STRUCT_SUM(Demand_Accu.Phase_Accu[i]);
    SET_STRUCT_SUM(Demand_Accu.Phase_Cur[i]);
  }

  SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
}

//需量清0，入口参数pTime表示清除的时间点, 一般是当前时间
//清需量后要根据该时间点计算下次需量数据冻结的时间
void Demand_Clear(S_HEX_Time* pTime)
{
  //Demand_Accu_Clear();//清累加, 跨月的情况下一定要清累加?
  TRACE();

  mem_set((void *) &Cur_Demand, 0, sizeof(Cur_Demand), (void *) &Cur_Demand, sizeof(Cur_Demand));//清需量
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);
  SET_STRUCT_SUM(Cur_Demand);
}
*/

//需量上电时的处理，主要是当表计睡眠时间少于一个需量周期时的处理
//初次上电时调用该函数，可以将Sleep_Secs值放入一个最大值
//待改
void PowerOn_Demand_Proc()
{
  /*
  if(Check_Rst_Flag() EQ SOFT_RST)//如果是软件复位，则不清楚中间累加单元
    Demand_Accu_Init(0);
  else
  {
    //此处需要获得睡眠时间的秒计数, 并作为Demand_Accu_Init的入口参数
    Demand_Accu_Init(0xFFFFFFFF);//上电则清除累加单元
  }
  */
  TRACE();

  Clr_Demand_Accu();
}

//功率累加单元初始化
//Sleep_Secs表示距离上一次需量累加已经走过了多长时间
/*
void Demand_Accu_Init(INT32U Sleep_Secs)
{
  INT32U Period;
  INT8U Re, i;
   
  Re=CHECK_STRUCT_SUM(Demand_Para);
  if(ASSERT(Re>0))
  Check_Data_Avail();
  
  Period=(INT32U)(Demand_Para.Period)*60;//计算需量周期
  
  if(Sleep_Secs>=Period)//掉电时间超过一个需量周期，则要将需量数据清0
  {
  Demand_Accu_Clear();
  }
  else
  {   
  Re=CHECK_STRUCT_SUM(Mode_Word);
  //模式字校验和是否正确
  if(ASSERT(0 != Re))
  Check_Data_Avail();

  //掉电需量不连续的话，请需量累加单元
  if(Mode_Word.Mode[2].Bit.Bit3 EQ 0)//掉电需量不连续
  {
  Demand_Accu_Clear();//清中间累加
  }
  else
  {
  Re=Check_Demand_Accu();
  if(ASSERT(0 != Re))
   Demand_Accu_Clear();
  else
  {
  Re=CHECK_STRUCT_SUM(Demand_Para);
  if(ASSERT(1 EQ Re))
    Check_Data_Avail();
    
  for(i=0;i<MAX_PERIOD_SLIDE_RATIO;i++)//此处有待改，主要是看休眠情况下程序是否在跑
  {
    Demand_Accu.Accu_Stat.Counts[i] += Sleep_Secs;
    
    //比较每个中间单元的计数，如果该计数超过了一个需量周期的时间，则认为
    //在停电期间，该中间单元会出需量一次
    //+2是为了防止出现掉电和上电正好在一个单元的出需量周期内, 上电时间靠近出需量时刻
    //0-------------------------15
    //    |pd    |po
    //这种情况很容易出现判断错误, 因此增加2分钟, 确定在掉电期间出过一次需量
    if(Demand_Accu.Accu_Stat.Counts[i]>=((INT32U)Demand_Para.Period+2)*60)//掉电期间肯定出过一次需量
    {
    Demand_Accu.Accu_Stat.Counts[i]=Demand_Accu.Accu_Stat.Counts[i]-(INT32U)Demand_Para.Period*60;
    Demand_Accu.Phase_Accu[0].Pos_Active[i]=0;//清中间单元
    Demand_Accu.Phase_Accu[0].Neg_Active[i]=0;
    Demand_Accu.Phase_Accu[0].Comb_Reactive1[i]=0;
    Demand_Accu.Phase_Accu[0].Comb_Reactive2[i]=0;
    //Demand_Accu.Init_Flag[i]=1;//初始化标志
    }
  }
  SET_STRUCT_SUM(Demand_Accu);
  }
  }
  }
}
*/

//需量周期的累加
void Demand_Counts_Init()
{
  INT8U i;

  TRACE();

  for(i = 0; i < MAX_PERIOD_SLIDE_RATIO; i++)
  {
    Demand_Accu.Accu_Stat.Counts[i] = (INT16U) Demand_Para.Slide_Time * 60 * i;//每个需量累加中间单元的个数累加 
  }
}

//检查功率是否越限
void Demand_Check_Exceed_Limit()
{
  INT8U i;
  INT8U Re;
  INT8U Exceed_Flag, Event_ID;
  //INT32U Demand_Limit;

   
  Re = CHECK_STRUCT_SUM(Demand_Exceed_Limit);
  
  DIS_PD_INT;
  
  if(1 != Re)//ASSERT(1  EQ  Re))
  {
    ASSERT_FAILED();

    mem_set((void *) &Demand_Exceed_Limit, 0, sizeof(Demand_Exceed_Limit), (void *) &Demand_Exceed_Limit, sizeof(Demand_Exceed_Limit));
    SET_STRUCT_SUM(Demand_Exceed_Limit);
    SET_STRUCT_SUM(Event_Data);  
  }
  
  Exceed_Flag = 0;
  //Demand_Limit = POS_ACT_DEMAND_LIMIT;
  //正向有功需量超限
  //if(Demand_Accu.Phase_Cur[0].Pos_Active > Demand_Limit)//有功需量超上限发生
  if(Read_Event_Status(ID_EVENT_POS_ACT_DEMAND_EXCEED))
  {
    if(Demand_Exceed_Limit.Pos_Active_Flag EQ 0)
    {
      Debug_Print("Pos_Active Demand Exceed Occur: %ld", Demand_Accu.Phase_Cur[0].Pos_Active);
      //Set_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);//事件发生标志

      Demand_Exceed_Limit.Pos_Active.Var = 0;//Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_set((INT8U *) Demand_Exceed_Limit.Pos_Active.Time, 0, sizeof(Demand_Exceed_Limit.Pos_Active.Time),\
              (INT8U *) Demand_Exceed_Limit.Pos_Active.Time, sizeof(Demand_Exceed_Limit.Pos_Active.Time)); 
      
      Demand_Exceed_Limit.Pos_Active_Flag = 1;
      Exceed_Flag = 1;      
    }
      
    if(Demand_Accu.Phase_Cur[0].Pos_Active > Demand_Exceed_Limit.Pos_Active.Var)
    {
      Demand_Exceed_Limit.Pos_Active.Var = Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_cpy((INT8U *) Demand_Exceed_Limit.Pos_Active.Time, (INT8U *) Cur_Time2.Time, sizeof(Cur_Time2.Time),\
              (INT8U *) Demand_Exceed_Limit.Pos_Active.Time, sizeof(Demand_Exceed_Limit.Pos_Active.Time));
      
      Exceed_Flag = 1;
    }
  }
  else //有功需量越上限恢复
  {
    if(Demand_Exceed_Limit.Pos_Active_Flag EQ 1)
    {
      //设置事件结束
      Debug_Print("Pos_Active Demand Exceed End: %ld", Demand_Accu.Phase_Cur[0].Pos_Active);
      
      //Clr_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);//事件发生标志
     
      Demand_Exceed_Limit.Pos_Active_Flag = 0;
      Exceed_Flag = 1;
    }
  }

  //Demand_Limit = NEG_ACT_DEMAND_LIMIT;
  //反向有功需量超上限
  if(Read_Event_Status(ID_EVENT_NEG_ACT_DEMAND_EXCEED))//反向有功需量超上限发生
  {
    if(Demand_Exceed_Limit.Neg_Active_Flag EQ 0)
    {
      Debug_Print("Neg_Active Demand Exceed Occur: %ld", Demand_Accu.Phase_Cur[0].Neg_Active);
      //Set_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);//事件发生标志;//事件发生标志

      Demand_Exceed_Limit.Neg_Active.Var = 0;//Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_set((INT8U *) Demand_Exceed_Limit.Neg_Active.Time, 0, sizeof(Demand_Exceed_Limit.Neg_Active.Time),\
              (INT8U *) Demand_Exceed_Limit.Neg_Active.Time, sizeof(Demand_Exceed_Limit.Neg_Active.Time));
      
      Demand_Exceed_Limit.Neg_Active_Flag = 1;      
      Exceed_Flag = 1;      
    }
    
    if(Demand_Accu.Phase_Cur[0].Neg_Active > Demand_Exceed_Limit.Neg_Active.Var)
    {
      Demand_Exceed_Limit.Neg_Active.Var = Demand_Accu.Phase_Cur[0].Neg_Active;
      mem_cpy((INT8U *) Demand_Exceed_Limit.Neg_Active.Time, (INT8U *) Cur_Time2.Time, sizeof(Cur_Time2.Time),\
              (INT8U *) Demand_Exceed_Limit.Neg_Active.Time, sizeof(Demand_Exceed_Limit.Neg_Active.Time));
     
      Exceed_Flag = 1;    
    }
  } 
  else //反向有功需量越上限恢复
  {
    if(Demand_Exceed_Limit.Neg_Active_Flag EQ 1)
    {
      Debug_Print("Neg_Active Demand Exceed End: %ld", Demand_Accu.Phase_Cur[0].Neg_Active);
      
      //Clr_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);//事件发生标志;//事件发生标志

      Demand_Exceed_Limit.Neg_Active_Flag = 0;
      Exceed_Flag = 1;     
    }
  }

  //Demand_Limit = QUAD_REA_DEMAND_LIMIT;
  //四象限无功需量越限
  for(i = 0; i < 4; i ++)
  {    
    if(i EQ 0)//事件发生标志
      Event_ID = ID_EVENT_Q1_REAC_DEMAND_EXCEED;
    else if(i EQ 1)
      Event_ID = ID_EVENT_Q2_REAC_DEMAND_EXCEED;
    else if(i EQ 2)
      Event_ID = ID_EVENT_Q3_REAC_DEMAND_EXCEED;
    else
      Event_ID = ID_EVENT_Q4_REAC_DEMAND_EXCEED;

    if(Read_Event_Status(Event_ID))//无功需量超上限发生
    {
      if(Demand_Exceed_Limit.Quad_Reac_Flag[i] EQ 0)
      {
        Debug_Print("Quad%d_Reactive Demand Exceed End: %ld", i + 1, Demand_Accu.Phase_Cur[0].Quad_Reactive[i]);

        Demand_Exceed_Limit.Quad_Reactive[i].Var = 0;//Demand_Accu.Phase_Cur[0].Pos_Active;
        mem_set((INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, 0, sizeof(Demand_Exceed_Limit.Quad_Reactive[i].Time),\
                (INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, sizeof(Demand_Exceed_Limit.Quad_Reactive[i].Time));
        
        Demand_Exceed_Limit.Quad_Reac_Flag[i] = 1;
        Exceed_Flag = 1;
      }
        
      if(Demand_Accu.Phase_Cur[0].Quad_Reactive[i] > Demand_Exceed_Limit.Quad_Reactive[i].Var)
      {
        Demand_Exceed_Limit.Quad_Reactive[i].Var = Demand_Accu.Phase_Cur[0].Quad_Reactive[i];
        mem_cpy((INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, (INT8U *) Cur_Time2.Time, sizeof(Cur_Time2.Time),\
                (INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, sizeof(Demand_Exceed_Limit.Quad_Reactive[i].Time));

        Exceed_Flag = 1;
      }
    }
    else //无功需量越上限恢复
    {
      if(Demand_Exceed_Limit.Quad_Reac_Flag[i] EQ 1)
      {
        Debug_Print("Quad%d_Reactive Demand Exceed End: %ld", i + 1, Demand_Accu.Phase_Cur[0].Quad_Reactive[i]);
/*        
        if(i EQ 0)//事件发生标志
          Clr_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED);
        else if(i EQ 1)
          Clr_Event_Instant(ID_EVENT_Q2_REAC_DEMAND_EXCEED);
        else if(i EQ 2)
          Clr_Event_Instant(ID_EVENT_Q3_REAC_DEMAND_EXCEED);
        else if(i EQ 3)
          Clr_Event_Instant(ID_EVENT_Q4_REAC_DEMAND_EXCEED);
*/
            
        Demand_Exceed_Limit.Quad_Reac_Flag[i] = 0;
        
        Exceed_Flag = 1;
      }   
    }
  }

  if(Exceed_Flag EQ 1)
  {
    SET_STRUCT_SUM(Demand_Exceed_Limit);
    SET_STRUCT_SUM(Event_Data);
  }
  
  EN_PD_INT;
}

//检查当前需量是否是最大需量
void Demand_Check_Max()
{
  INT8U i,j,Re, Max_Flag;
  INT8U TempTime[5];
  
  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Time0);//检查当前需量累加单元
  Re &= CHECK_STRUCT_SUM(Cur_Demand);//检查当前需量
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//当前费率相关信息 
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);//检查复费率相关参数

  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
  
  Re = CHECK_STRUCT_VAR(Demand_Rate_Mins);
  if(Re EQ 0)
    ASSERT_FAILED();

  Check_Demand_Accu();//检查当前需量累加单元
  
  if(Demand_Rate_Mins.Min_Bak != Cur_Time0.Time[T_MIN])
  {
    Demand_Rate_Mins.Min_Bak = Cur_Time0.Time[T_MIN];
    Demand_Rate_Mins.Mins ++; //在当前费率内走的分钟数
    if(Demand_Rate_Mins.Rate_Bak != Cur_Rate_Info.Rate) //发生了费率切换
    {
      Demand_Rate_Mins.Rate_Bak = Cur_Rate_Info.Rate; 
      Demand_Rate_Mins.Mins = 0;
    }
  }
  
  Max_Flag = 0;//该标志为1表示产生了一次最大需量

  //正向有功总最大需量以其发生时间
  DIS_PD_INT;//更新需量数据时关掉电中断
  for(i = 0; i < 2; i++)
  {
    if(i EQ 1) //计算当前费率的最大需量，需要在当前费率基础上走起码一个需量周期
    {
      if(Demand_Rate_Mins.Mins < Demand_Para.Period)
        break;
    }
    
    //得到当前BCD时间
    //Hex2Bcd_Buf((void *)Cur_Time0.Time, sizeof(Cur_Time0.Time), TempTime, TempTime, sizeof(TempTime));
    mem_cpy(TempTime, (INT8U *) &Cur_Time2.Time[1], 5, TempTime, sizeof(TempTime));
    //当前需量比各费率最大需量大
    //正向有功总需量及其发生时间
    if(Demand_Accu.Phase_Cur[0].Pos_Active > Cur_Demand.Demand[i].Pos_Active.Var)
    {
      Cur_Demand.Demand[i].Pos_Active.Var = Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_cpy((void *) Cur_Demand.Demand[i].Pos_Active.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //反向有功总最大需量及其发生时间  
    if(Demand_Accu.Phase_Cur[0].Neg_Active > Cur_Demand.Demand[i].Neg_Active.Var)
    {
      Cur_Demand.Demand[i].Neg_Active.Var = Demand_Accu.Phase_Cur[0].Neg_Active;
      mem_cpy((void *) Cur_Demand.Demand[i].Neg_Active.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }

    //正向视在总需量及其发生时间
    if(Demand_Accu.Phase_Cur[0].Pos_Apparent > Cur_Demand.Demand[i].Pos_Apparent.Var)
    {
      Cur_Demand.Demand[i].Pos_Apparent.Var = Demand_Accu.Phase_Cur[0].Pos_Apparent;
      mem_cpy((void *) Cur_Demand.Demand[i].Pos_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //反向视在总最大需量及其发生时间  
    if(Demand_Accu.Phase_Cur[0].Neg_Apparent > Cur_Demand.Demand[i].Neg_Apparent.Var)
    {
      Cur_Demand.Demand[i].Neg_Apparent.Var = Demand_Accu.Phase_Cur[0].Neg_Apparent;
      mem_cpy((void *) Cur_Demand.Demand[i].Neg_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    
    //四象限无功需量
    for(j = 0; j < 4; j ++)
    {
      if(Demand_Accu.Phase_Cur[0].Quad_Reactive[j] > Cur_Demand.Demand[i].Quad_Reactive[j].Var)
      {
        Cur_Demand.Demand[i].Quad_Reactive[j].Var = Demand_Accu.Phase_Cur[0].Quad_Reactive[j];
        mem_cpy((void *) Cur_Demand.Demand[i].Quad_Reactive[j].Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
        SET_STRUCT_SUM(Cur_Demand);
        Max_Flag = 1;
      }      
    }
    
    //正向无功总最大需量及其发生时间  
    if(Demand_Accu.Phase_Cur[0].Comb_Reactive1 > Cur_Demand.Demand[i].Comb_Reactive1.Var)
    {
      Cur_Demand.Demand[i].Comb_Reactive1.Var = Demand_Accu.Phase_Cur[0].Comb_Reactive1;
      mem_cpy((void *) Cur_Demand.Demand[i].Comb_Reactive1.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    } 
    //反向无功总最大需量及其发生时间 
    if(Demand_Accu.Phase_Cur[0].Comb_Reactive2 > Cur_Demand.Demand[i].Comb_Reactive2.Var)
    {
      Cur_Demand.Demand[i].Comb_Reactive2.Var = Demand_Accu.Phase_Cur[0].Comb_Reactive2;
      mem_cpy((void *) Cur_Demand.Demand[i].Comb_Reactive2.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
  }       
   EN_PD_INT;//开掉电中断

  //生成了一个最大需量数据
  if(Max_Flag EQ 1)
  {
    Debug_Print("Demand max data generated");
    //Save_Cur_Demand_PD_Data(); 
  }
}

//分相需量数据的最大检查
void Phase_Demand_Check_Max()
{
#if  DEMAND_ACCU_PHASE_NUM > 1
  
  INT8U i, j, Re, Max_Flag;
  INT8U TempTime[5];

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Time0);//检查当前需量累加单元
  Re &= CHECK_STRUCT_SUM(Cur_Demand);//检查当前需量
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//当前费率相关信息 
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);//检查复费率相关参数

  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Check_Demand_Accu();//检查当前需量累加单元

  Max_Flag = 0;//该标志为1表示产生了一次最大需量

  //正向有功总最大需量以其发生时间
  mem_cpy(TempTime, (INT8U *) &Cur_Time2.Time[1], 5, TempTime, sizeof(TempTime));
    
  DIS_PD_INT;//更新需量数据时关掉电中断
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM-1; i++)
  {
    //得到当前BCD时间
    //当前需量比各费率最大需量大
    //正向有功总需量及其发生时间
    if(Demand_Accu.Phase_Cur[i+1].Pos_Active > Cur_Demand.Phase_Demand[i].Pos_Active.Var)
    {
      Cur_Demand.Phase_Demand[i].Pos_Active.Var = Demand_Accu.Phase_Cur[i+1].Pos_Active;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Pos_Active.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //反向有功总最大需量及其发生时间  
    if(Demand_Accu.Phase_Cur[i+1].Neg_Active > Cur_Demand.Phase_Demand[i].Neg_Active.Var)
    {
      Cur_Demand.Phase_Demand[i].Neg_Active.Var = Demand_Accu.Phase_Cur[i+1].Neg_Active;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Neg_Active.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }

    //正向视在总需量及其发生时间
    if(Demand_Accu.Phase_Cur[i+1].Pos_Apparent > Cur_Demand.Phase_Demand[i].Pos_Apparent.Var)
    {
      Cur_Demand.Phase_Demand[i].Pos_Apparent.Var = Demand_Accu.Phase_Cur[i+1].Pos_Apparent;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Pos_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //反向视在总最大需量及其发生时间  
    if(Demand_Accu.Phase_Cur[i+1].Neg_Apparent > Cur_Demand.Phase_Demand[i].Neg_Apparent.Var)
    {
      Cur_Demand.Phase_Demand[i].Neg_Apparent.Var = Demand_Accu.Phase_Cur[i+1].Neg_Apparent;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Neg_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }    
    //四象限无功需量
    for(j = 0; j < 4; j ++)
    {
      if(Demand_Accu.Phase_Cur[i+1].Quad_Reactive[j] > Cur_Demand.Phase_Demand[i].Quad_Reactive[j].Var)
      {
        Cur_Demand.Phase_Demand[i].Quad_Reactive[j].Var = Demand_Accu.Phase_Cur[i+1].Quad_Reactive[j];
        mem_cpy((void *) Cur_Demand.Phase_Demand[i].Quad_Reactive[j].Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
        SET_STRUCT_SUM(Cur_Demand);
        Max_Flag = 1;
      }      
    }
    
    //正向无功总最大需量及其发生时间  
    if(Demand_Accu.Phase_Cur[i+1].Comb_Reactive1 > Cur_Demand.Phase_Demand[i].Comb_Reactive1.Var)
    {
      Cur_Demand.Phase_Demand[i].Comb_Reactive1.Var = Demand_Accu.Phase_Cur[i+1].Comb_Reactive1;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Comb_Reactive1.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    } 
    //反向无功总最大需量及其发生时间 
    if(Demand_Accu.Phase_Cur[i+1].Comb_Reactive2 > Cur_Demand.Phase_Demand[i].Comb_Reactive2.Var)
    {
      Cur_Demand.Phase_Demand[i].Comb_Reactive2.Var = Demand_Accu.Phase_Cur[i+1].Comb_Reactive2;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Comb_Reactive2.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
  }       
   EN_PD_INT;//开掉电中断

  //生成了一个最大需量数据
  if(Max_Flag EQ 1)
  {
    Debug_Print("Phase_Demand max data generated");
    //Save_Cur_Demand_PD_Data(); 
  }  
#endif  
}

//需量处理, 包括每秒累加需量单元，以及与当前最大需量比较，生成最大值 
void Demand_Proc()
{
  INT8U Re;
  static S_Int32U Sec_Timer = {CHK_BYTE, 0x00, CHK_BYTE};

  Re = CHECK_STRUCT_VAR(Sec_Timer);
  ASSERT(1 EQ Re);

  if(Sec_Timer_Pub EQ Sec_Timer.Var)//时间还没有走过1S，该函数只允许1S进入一次下面的流程
    return;

  Sec_Timer.Var = Sec_Timer_Pub;//更新秒计数器

  Demand_Accumu();//每秒的需量累加以及每分钟的当前需量计算, 以及每个滑差周期到后出需量 
  Demand_Generate();//生成需量
  Sign_Demand_Generate();//当前需量生成，有符号类型当前需量
  Demand_Check_Rate_Change();//检查当前费率是否发生了修改，如果修改了则要重新读取当前费率的需量数据
  Demand_Check_Max();//检查当前需量是否是最大需量
  Phase_Demand_Check_Max();//分相需量检测最大值
  Demand_Check_Exceed_Limit();//检查是否有需量越限
  Calc_1Min_Aver_AcPower();//计算一分钟平均功率
  Clr_Demand_Manul_Chk();//手动清需量的检查
}

//保存当前需量数据
void Save_Cur_Demand_Data()
{
  INT8U Re;

  Debug_Print("Save Cur Demand Data!");
  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 EQ Re)
  {
    //保存分相需量数据
    Write_Demand_Phase_Data(_SDI_CUR_DEMAND, (void *) &Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
    //保存总需量数据
    Write_Demand_Rate_Data(_SDI_CUR_DEMAND, 0, (void *) &Cur_Demand.Demand[0], sizeof(Cur_Demand.Demand[0]));
    //保存分费率需量
    if(Cur_Demand.Rate != 0)
      Write_Demand_Rate_Data(_SDI_CUR_DEMAND, Cur_Demand.Rate, (void *) &Cur_Demand.Demand[1], sizeof(Cur_Demand.Demand[1]));
    else
      ASSERT_FAILED();
  }
  else
  {
    ASSERT_FAILED();
  }
}

//保存当前需量备份数据
void Save_Cur_Demand_Bak_Data()
{
  INT8U Re;

  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 EQ Re)
  {
    Write_Demand_Phase_Data(_SDI_CUR_DEMAND_BAK, (void *) &Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
    Write_Demand_Rate_Data(_SDI_CUR_DEMAND_BAK, 0, (void *) &Cur_Demand.Demand[0], sizeof(Cur_Demand.Demand[0]));
    Write_Demand_Rate_Data(_SDI_CUR_DEMAND_BAK, Cur_Demand.Rate, (void *) &Cur_Demand.Demand[1], sizeof(Cur_Demand.Demand[1]));
  }
  else
  {
    ASSERT_FAILED();
  }
}

//保存当前需量掉电数据
void Save_Cur_Demand_PD_Data()
{
  INT8U Re;

  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 EQ Re)//检查需量数据的校验和，校验和错误则重新从ROM中读取
  {
    //mem_cpy((void *)Cur_Demand.Time, (void *)Cur_Time0.Time, sizeof(Cur_Time0.Time), (void *)Cur_Demand.Time, sizeof(Cur_Demand.Time));
    Re = Write_Storage_Data(_SDI_CUR_DEMAND_PD, (void *) &Cur_Demand, sizeof(S_Demand));
    ASSERT(1 EQ Re);
  }
  else
  {
    ASSERT_FAILED();
  }
}

/*
//将当前需量数据设置到SDI指向的需量存储空间
void Save_Cur_Demand_Data_To(STORA_DI SDI)
{
  INT8U i;

  Write_Demand_Time(SDI, (void *) &Cur_Demand.Demand[0].Time);
  //Write_Demand_Time(_SDI_CUR_DEMAND_BAK, (void *)&Cur_Demand.Demand[0].Time);

  Write_Demand_Phase_Data(SDI, (void *) &Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
  //Write_Demand_Phase_Data(_SDI_CUR_DEMAND_BAK, (void *)&Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
  //将各个费率的需量数据清0
  for(i = 0; i <= MAX_RATES; i ++)
  {
    Cur_Demand.Rate = i;
    SET_STRUCT_SUM(Cur_Demand);

    Write_Demand_Rate_Data(SDI, i, (void *) &Cur_Demand.Demand[0], sizeof(Cur_Demand.Demand[0]));
  }

  //mem_set((void *)&Cur_Demand, 0, sizeof(Cur_Demand), (void *)&Cur_Demand, sizeof(Cur_Demand)); 
  Cur_Demand.Rate = 0;
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);

  //INIT_STRUCT_VAR(Cur_Demand);
  //SET_DATA_READY_FLAG(Cur_Demand);

  SET_STRUCT_SUM(Cur_Demand);  
  //Save_Cur_Demand_PD_Data();  
}
*/

//设置当前默认需量
//并将数据时间设置为pTime
void Set_Def_Cur_Demand_Data(S_HEX_Time *pTime)
{
  //S_HEX_Time TempTime;
  
  Debug_Print("Set Def Cur Demand Data, Time:");
  Print_HEX_Time(pTime);
  //mem_set(&TempTime, 0, sizeof(TempTime), &TempTime, sizeof(TempTime));
  //SET_STRUCT_SUM(TempTime);
  //mem_cpy(&TempTime, (void *)&Cur_Time0, sizeof(Cur_Time0), &TempTime, sizeof(TempTime));
  
  Reset_Demand_Ram_Data();
  //当前需量存储区的时间设置为0，结算时认为当前需量数据还没有生成
  Reset_Demand_Rom_Data(_SDI_CUR_DEMAND, pTime);
  Reset_Demand_Rom_Data(_SDI_CUR_DEMAND_BAK, pTime);

  Save_Cur_Demand_PD_Data();
}

//手动清当前需量
void Manul_Clr_Demand_Data()
{
  DISP_CLR_DATA_INFO;
  Set_Def_Cur_Demand_Data((S_HEX_Time *)&Cur_Time0);
}

//设置默认的需量数据
void Set_Def_Demand_Data()
{
  INT8U i;
  S_HEX_Time TempTime;
  STORA_DI SDI;

  //Clear_Cur_Demand_Ram_Data();

  //设置当前需量数据
  //Save_Cur_Demand_Data_To(_SDI_CUR_DEMAND);
  //Save_Cur_Demand_Data_To(_SDI_CUR_DEMAND_BAK);
  Set_Def_Cur_Demand_Data((S_HEX_Time *)&Cur_Time0);

  //mem_set(&TempTime, 0, sizeof(TempTime), &TempTime, sizeof(TempTime));
  //SET_STRUCT_SUM(TempTime);

  Get_N_Last_Settle_Time(MAX_DEMAND_SETTLE_NUM, (S_HEX_Time *) &Cur_Time0, &TempTime, &TempTime, sizeof(TempTime));
  SDI = _SDI_SETTLE_DEMAND_DATA;  
  //设置历史需量数据
  for(i = 0; i < MAX_DEMAND_SETTLE_NUM; i ++)
  {
    if(Cmp_Time(&TempTime, (S_HEX_Time *) &Cur_Time0) != TIME_AFT)
    {
      Debug_Print("Set Def Demand His Data, Time:");
      Print_HEX_Time((S_HEX_Time *) &TempTime);  
     
      INC_DEMAND_SETTLE_DI(SDI);
      Reset_Demand_Rom_Data(SDI, &TempTime); 
    }
    Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
  }
  Write_Storage_Data(_SDI_LAST_SETTLE_DEMAND_DI, &SDI, sizeof(SDI));
  Settle_Demand_FF_Data(0);
}

//读取存在当前需量存储区中的总或分费率需量数据
//Rate:需要读取的需量的费率, 0表示总
//pDst:目标缓冲区
//pDst_Start和DstLen一起限定pDst和返回长度的范围
//返回值:读取数据长度, 读取失败返回0，成功返回sizeof(S_One_Demand)
INT16U Read_Cur_Demand_Rate_Data(INT8U Rate, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Off;

  Off = DEMAND_RATE_DATA_OFF(Rate);
  //先读取当前存储区
  if(Read_Storage_Data_Fix_Len(_SDI_CUR_DEMAND, Off, sizeof(S_One_Demand), pDst, pDst_Start, DstLen) != sizeof(S_One_Demand))
  {
    Debug_Print("Read _SDI_CUR_DEMAND CurRate data error");
    //再读取备份存储区
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data_Fix_Len(_SDI_CUR_DEMAND_BAK, Off, sizeof(S_One_Demand), pDst, pDst_Start, DstLen) != sizeof(S_One_Demand))
    {
      //该参数有默认参数项, 实际上不会进入下面的括号
      Debug_Print("Read _SDI_CUR_DEMAND_BAK Rate  % d data Error", Rate);
      //如果所有的备份区数据都没读出来则认为是第一次上电，需量清0
      return 0;
    }
  }
  return sizeof(S_One_Demand);
}

//检查需量数据是否合法
INT8U Check_Demand_Data(S_Demand* pDemand)
{
  INT8U i, Re;
  //INT8U Temp[5] = {0, 0, 0, 0, 0};

  Re = 1;
  Re &= ((pDemand -> Head EQ CHK_BYTE && pDemand -> Tail EQ CHK_BYTE) ? 1 : 0);  
  Re &= Check_STRUCT_Sum(pDemand, sizeof(S_Demand), pDemand -> CS, sizeof(pDemand -> CS));
  Re &= (pDemand -> Data_Ready_Flag EQ DATA_READY) ? 1 : 0;  
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    return 0;
  }

  if(pDemand->Rate EQ 0 || pDemand->Rate > MAX_RATES)
  {
    ASSERT_FAILED();
    return 0;
  }

  for(i = 0; i < 2; i ++)
  {
    if(Check_BCD_Data(pDemand->Demand[i].Pos_Apparent.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Neg_Apparent.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Pos_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Neg_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Comb_Reactive1.Time, 5) != 1 ||\
       Check_BCD_Data(pDemand->Demand[i].Comb_Reactive2.Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[0].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[1].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[2].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[3].Time, 5) !=1) 
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  //
  for(i = 0; i < 3; i ++)
  {
    if(Check_BCD_Data(pDemand->Phase_Demand[i].Pos_Apparent.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Phase_Demand[i].Neg_Apparent.Time, 5) != 1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Pos_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Phase_Demand[i].Neg_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Phase_Demand[i].Comb_Reactive1.Time, 5) != 1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Comb_Reactive2.Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[0].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[1].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[2].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[3].Time, 5) !=1) 
    {
      ASSERT_FAILED();
      return 0;
    }
  }       
       
  return 1;
}

//从ROM中读出当前需量数据
void Read_Demand_Data_From_Rom()
{
  INT8U Re, Rate, i;
  S_Demand* p;

  //先读取掉电存储区数据
  //再读普通数据
  //最后读备份区数据
  Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  p = (S_Demand *) Pub_Buf0;
  if(Read_Storage_Data(_SDI_CUR_DEMAND_PD, p, p, sizeof(Pub_Buf0)) != sizeof(Cur_Demand) || \
     Check_Demand_Data((S_Demand *) p) EQ 0)
  {
    Debug_Print("Read _SDI_CUR_DEMAND_PD data error");
    OS_TimeDly_Ms(500);
    //读取总和当前费率需量
    for(i = 0; i < 2; i ++)
    {
      if(i EQ 0)
        Rate = 0;//读总需量时偏移为0
      else
        Rate = Cur_Rate_Info.Rate;//非总时根据费率计算偏移

      p -> Rate = Cur_Rate_Info.Rate;
      //从当前数据区读取当前和总费率的需量数据
      if(Read_Cur_Demand_Rate_Data(Rate, (void *) &p->Demand[i], (void *) &p->Demand[i], sizeof(S_One_Demand)) != sizeof(S_One_Demand))
      {
        Debug_Print("Read _SDI_CUR_DEMAND Rate  % d data error", Rate);
        mem_set((void *) &p->Demand[i], 0, sizeof(p->Demand[i]), (void *) &p->Demand[i], sizeof(p->Demand[i]));
      }
    }
  }


  if(Check_Demand_Data((S_Demand *) p) EQ 0)
  {
    ASSERT_FAILED();
    mem_set(p, 0, sizeof(Cur_Demand), p, sizeof(Pub_Buf0));
  }       

  DIS_PD_INT;//更新Cur_Demand数据前关掉电中断
  mem_cpy((void *) &Cur_Demand, p, sizeof(Cur_Demand), (void *) &Cur_Demand, sizeof(Cur_Demand));
  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);
  SET_STRUCT_SUM(Cur_Demand);              
  EN_PD_INT;

  OS_Mutex_Post(PUB_BUF0_SEM_ID);  
  //SET_STRUCT_SUM(Cur_Demand); 
  //更新当前存储区和备份存储区，补冻函数可能要用到这两个区，因此要保证这两个区的数据更新
  if(Check_Sys_Status() EQ SYS_NORMAL) //电压正常情况下才进行写操作
  {
    Save_Cur_Demand_Data();
    Save_Cur_Demand_Bak_Data();
  }
}


//设置某条需量数据的时间域
void Set_One_Demand_Time(S_One_Demand* pSrc, S_HEX_Time* pTime)
{
  mem_cpy(&(pSrc->Time), pTime, sizeof(S_HEX_Time), &(pSrc->Time), sizeof(pSrc->Time));
  Set_STRUCT_Sum(pSrc, sizeof(S_One_Demand), pSrc->CS, sizeof(pSrc->CS));
}

//需量检查当前费率是否发生了变化，如果变化了，则读出当前费率的最大需量值
void Demand_Check_Rate_Change()
{
  INT8U Re;

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re &= Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(Cur_Rate_Info.Rate != Cur_Demand.Rate)//费率已经发生变化了
  {
    Debug_Print("Rate_Changed! %d->%d,Save Old Rate Demand && Read New Rate Demand",\
                                Cur_Demand.Rate, Cur_Rate_Info.Rate);
    Save_Cur_Demand_Data();//先将Cur_Demand数据保存起来
    Save_Cur_Demand_Bak_Data();

    //重新根据当前费率读取需量数据

    
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    //读出该分费率数据
    if(Read_Cur_Demand_Rate_Data(Cur_Rate_Info.Rate, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)) != sizeof(S_One_Demand))
    {
      mem_set((void *) Pub_Buf0, 0, sizeof(S_One_Demand), (void *) Pub_Buf0, sizeof(Pub_Buf0));
    }
    
    DIS_PD_INT;
    mem_cpy((void *) &Cur_Demand.Demand[1], (void *)Pub_Buf0, sizeof(S_One_Demand),(void *) &Cur_Demand.Demand[1], sizeof(Cur_Demand.Demand[1])); 
    SET_STRUCT_SUM(Cur_Demand.Demand[1]);
    Cur_Demand.Rate = Cur_Rate_Info.Rate;
    SET_STRUCT_SUM(Cur_Demand);
    EN_PD_INT;
    
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
    
    Save_Cur_Demand_PD_Data();//更新掉电存储区的需量数据
    //Clr_Demand_Accu();//清需量累加单元
  }
}

//检查当前需量数据的有效性
void Check_Demand_Data_Avail()
{
  INT8U Re;

  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 != Re)//ASSERT(1 EQ Re))//检查需量数据的校验和，校验和错误则重新从ROM中读取
  {
    ASSERT_FAILED();
    Read_Demand_Data_From_Rom();
  }

  Check_Demand_Accu();
}

//清最大需量及其发生时间, 清需量只清当月需量
void Clear_Cur_Demand_Data()
{
  Set_Clear_Data_Result(0);
  if(Check_Clear_Data_Authority() EQ 0)
    return;

  if(CLEAR_DEMAND_FLAG != Check_Clear_Data_Flag())
    return;

  Debug_Print("Clear_Cur_Demand_Data!!!"); 
  
  DISP_CLR_DATA_INFO;
  Set_Def_Cur_Demand_Data((S_HEX_Time *)&Cur_Time0);
  
  Set_Clear_Data_Result(1);
}

//清所有的需量数据, 包括当月和前HIS_ENERGY_DATA_MONTHS个月
void Clear_Demand_Data()
{
  if(Check_Clear_Data_Authority() EQ 0)
  {
    return;
  }

  Debug_Print("Clear_Demand_Data!!!"); 
  if(CLEAR_DEMAND_FLAG != Check_Clear_Data_Flag() && CLEAR_ALL_FLAG != Check_Clear_Data_Flag())
  {
    return;
  }
  DISP_CLR_DATA_INFO;
  
  Set_Def_Demand_Data();
  /*
  INT8U i, j;
  INT8U Re;
  INT32U Off;
  //将前0-HIS_ENERGY_DATA_MONTHS月的数据全部清0
  //检查编程状态、用户权限状态
  if(Check_Meter_Prog_Status() EQ 0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag) EQ 0 ||\
     User_Authority_Flag.Flag != AUTHORITY_FLAG)
    return;
  //检查清除标志
  Re=1;
  Re&=CHECK_STRUCT_SUM(User_Authority_Flag);
  Re&=CHECK_STRUCT_SUM(Clear_Flag);
  if(ASSERT(1 EQ Re))
    Check_Data_Avail();
  mem_set((void *)&Cur_Demand, 0, sizeof(Cur_Demand), (void *)&Cur_Demand, sizeof(Cur_Demand));
  //清前0-HIS_ENERGY_DATA_MONTHS月的需量
  for(i=0;i<=HIS_DEMAND_DATA_MONTHS;i++)
  {
    //Debug_Print("Clear Freeze Demand Data, Time: % d- % d- % d  % d: % d", Time.Time[T_YEAR], Time.Time[T_MONTH], Time.Time[T_DATE], Time.Time[T_HOUR], Time.Time[T_MIN]);
    //严格判断，防止程序乱跑到这里
    if(Check_Meter_Prog_Status() EQ 0 || 1 != Re ||\
     AUTHORITY_FLAG != User_Authority_Flag.Flag ||\
     CLEAR_DEMAND_FLAG != Clear_Flag.Flag)
    return;
    for(j=0;j<MAX_RATES;j++)
    {
    Off=DEMAND_RATE_DATA_OFF(i);//直接写历史数据存储缓冲区
    Write_Storage_Data_Fix_Len(_SDI_SETTLE_DEMAND_DATA+i, Off, (void *)&Cur_Demand.Demand[0], sizeof(S_One_Demand));
    }
  }
  Clear_Demand_Data();//先清当月需量
  */
}



//掉电存储需量数据
void PowerDown_Save_Demand_Data()
{
  Save_Cur_Demand_PD_Data();
}

//打印时间
void Debug_Print_Time(INT8U Time[])
{
  INT8U i;

  OS_Debug_Print("  ");
  for(i = 0; i < 5; i++)
  {
    if(Time[4 - i] < 10)
      OS_Debug_Print("0");

    OS_Debug_Print("%x", Time[4 - i]);
    if(i EQ 0 || i EQ 1)
      OS_Debug_Print("-");
    else if(i EQ 2)
      OS_Debug_Print(" ");
    else if(i EQ 3)
      OS_Debug_Print(":");
  }
  //OS_Debug_Print(" "); 
}

void Get_Print_Name(INT8U Dst[], INT8U Dst_Start, INT16U DstLen)
{
}

//返回需量运算模式0，滑差，1，区间
INT8U Get_Demand_Run_Mode()
{
  if(Demand_Para.Period EQ Demand_Para.Slide_Time)
    return 1;
  else
    return 0;
}

//输出当前需量信息
void Debug_Print_Cur_Demand_Info()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Counts ={CHK_BYTE, 0, CHK_BYTE};
  INT8U i, Re, Temp[5];
  S_One_Demand* p;

  if(Check_Debug_En() EQ 0)//非工厂状态不打印
    return;

  if(Cur_Time0.Time[T_MIN] EQ Min.Var)//每分钟执行一次该函数
    return;

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  //ASSERT(1 EQ Re);
  Re &= CHECK_STRUCT_VAR(Counts);
  ASSERT(1 EQ Re);

  Min.Var = Cur_Time0.Time[T_MIN];
  Counts.Var++;
  if(Counts.Var >= 5)//每隔5分钟打印一次当前电能值
  {
    Counts.Var = 0;

    Clr_Ext_Inter_Dog();
    Debug_Print("|----------------------------------------Max_Demand------------------------------------|"); 
    Debug_Print("| Rate Pos_Act Neg_Act Pos_Rea Neg_Rea Quad0_R Quad1_R Quad2_R Quad3_R Pos_App Neg_App |");

    for(i = 0; i < 5; i ++)
    {
      if(i EQ 0 || i EQ 1)
      {
        if(i EQ 0)
        {
          Temp[0] = ' ';//0x30 + i/10;
          Temp[1] = '0';
        }
        else
        {
          if(Cur_Demand.Rate >= 10)
            Temp[0] = '0' + Cur_Demand.Rate / 10;
          else
            Temp[0] = ' ';

          Temp[1] = '0' + Cur_Demand.Rate % 10;
        }
        p = (S_One_Demand *) &Cur_Demand.Demand[i];
      }
      else
      {
        Temp[0] = ' ';
        Temp[1] = 'A' + i - 2; 
        p = (S_One_Demand *) &Cur_Demand.Phase_Demand[i - 2];
      }

      Temp[2] = 0;
      Debug_Print("|   %s %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld |",\
            Temp, p->Pos_Active.Var, p->Neg_Active.Var, p->Comb_Reactive1.Var, p->Comb_Reactive2.Var,\
            p->Quad_Reactive[0].Var, p->Quad_Reactive[1].Var, p->Quad_Reactive[2].Var, p->Quad_Reactive[3].Var,\
            p->Pos_Apparent.Var, p->Neg_Apparent.Var);
    }
    Debug_Print("|--------------------------------------------------------------------------------------|");

    OS_TimeDly_Ms(50);
    Clr_Ext_Inter_Dog();
    Debug_Print("|---------------------------------------------Demand_Time_0--------------------------------------------|"); 
    Debug_Print("| Rate      Pos_Active      Neg_Active      Pos_Reacti      Neg_Reacti      Pos_Appare      Neg_Appare |");

    for(i = 0; i < 5; i ++)
    {
      if(i EQ 0 || i EQ 1)
      {
        if(i EQ 0)
        {
          Temp[0] = ' ';//0x30 + i/10;
          Temp[1] = '0';
        }
        else
        {
          if(Cur_Demand.Rate >= 10)
            Temp[0] = '0' + Cur_Demand.Rate / 10;
          else
            Temp[0] = ' ';

          Temp[1] = '0' + Cur_Demand.Rate % 10;
        }
        p = (S_One_Demand *) &Cur_Demand.Demand[i];
      }
      else
      {
        Temp[0] = ' ';
        Temp[1] = 'A' + i - 2; 
        p = (S_One_Demand *) &Cur_Demand.Phase_Demand[i - 2];
      }

      Temp[2] = 0;
      Debug_Print("|   %s", Temp);
      Debug_Print_Time((INT8U *) p->Pos_Active.Time);
      Debug_Print_Time((INT8U *) p->Neg_Active.Time);
      Debug_Print_Time((INT8U *) p->Comb_Reactive2.Time);
      Debug_Print_Time((INT8U *) p->Comb_Reactive2.Time);
      Debug_Print_Time((INT8U *) p->Pos_Apparent.Time);
      Debug_Print_Time((INT8U *) p->Neg_Apparent.Time);
      OS_Debug_Print(" |");
    }
    Debug_Print("|------------------------------------------------------------------------------------------------------|");


    Clr_Ext_Inter_Dog();
    Debug_Print("|------------------------------Demand_Time_1---------------------------|"); 
    Debug_Print("| Rate     Quad0_Reati     Quad1_Reati     Quad2_Reati     Quad3_Reati |");

    for(i = 0; i < 5; i ++)
    {
      if(i EQ 0 || i EQ 1)
      {
        if(i EQ 0)
        {
          Temp[0] = ' ';//0x30 + i/10;
          Temp[1] = '0';
        }
        else
        {
          if(Cur_Demand.Rate >= 10)
            Temp[0] = '0' + Cur_Demand.Rate / 10;
          else
            Temp[0] = ' ';

          Temp[1] = '0' + Cur_Demand.Rate % 10;
        }
        p = (S_One_Demand *) &Cur_Demand.Demand[i];
      }
      else
      {
        Temp[0] = ' ';
        Temp[1] = 'A' + i - 2; 
        p = (S_One_Demand *) &Cur_Demand.Phase_Demand[i - 2];
      }

      Debug_Print("|   %s", Temp);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[0].Time);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[1].Time);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[2].Time);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[3].Time);
      OS_Debug_Print(" |");
    }    
    Debug_Print("|----------------------------------------------------------------------|");
  }
}

//计算一分钟平均有功功率
void Calc_1Min_Aver_AcPower()
{
  //static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Min_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;
  
  Re = 1;
  //Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Min_Bak);
  Re &= CHECK_STRUCT_VAR(AcPower_1Min_Aver);
  
  ASSERT(Re EQ 1);
  
  if(Min_Bak.Var EQ Cur_Time1.Min)
  {
    AcPower_1Min_Aver.Accu_Power += Measu_InstantData_ToPub_PUCK.AcPower.Sum;
    AcPower_1Min_Aver.Counts ++;
  }
  else
  {
    Min_Bak.Var = Cur_Time1.Min;
    
    if(AcPower_1Min_Aver.Counts > 50)
      AcPower_1Min_Aver.Aver_Power = ((AcPower_1Min_Aver.Accu_Power /100) / AcPower_1Min_Aver.Counts); 
    
    AcPower_1Min_Aver.Accu_Power = 0;
    AcPower_1Min_Aver.Counts = 0;
  }
  
}

//获取一分钟平均有功功率
INT32U Get_One_Min_AcPower_Aver()
{
  
 return  AcPower_1Min_Aver.Aver_Power;
}

void Clr_Demand_Manul_Chk()
{
  //static S_Int8U Clr_Flag = {CHK_BYTE, 0, CHK_BYTE};
  
  //手动清需量事件发生了?
  if(Check_Demand_Key_Press() EQ 1)
  {
    //if(Clr_Flag.Var EQ 0)
    {      
      Debug_Print("Clr_Demand_Manul!");
      Set_Event_Instant(ID_EVENT_CLR_DEMAND_MAN);
      Wait_Event_Data_Proc_End(ID_EVENT_CLR_DEMAND_MAN);
      Manul_Clr_Demand_Data(); //手动清当前需量  
    }
  }
  //else
    //Clr_Flag.Var = 0;
}

/*
//需量超限处理
void Demand_Exceed_Limit_Proc()
{
  INT8U i;

  if(0)//正向有功需量超限制
  {
  if(Demand_Accu.Phase_Cur[0].Pos_Active > Ex_Max_Demand.Pos_Active.Var)
  {
  Ex_Max_Demand.Pos_Active.Var = Demand_Accu.Phase_Cur[0].Pos_Active;
  Get_BCD_Time((S_BCD_Time *)&Cur_Time1,  (INT8U *)Ex_Max_Demand.Pos_Active.Time,  \
  (INT8U *)Ex_Max_Demand.Pos_Active.Time,  sizeof(Ex_Max_Demand.Pos_Active.Time));
  }
  }
  else
  {
  mem_set((void *)&Ex_Max_Demand.Pos_Active,  \
  0, \
  sizeof(Ex_Max_Demand.Pos_Active), \
  (void *)&Ex_Max_Demand.Pos_Active, \
  sizeof(Ex_Max_Demand.Pos_Active));
  }

  if(0)//反向有功需量超限
  {
  if(Demand_Accu.Phase_Cur[0].Neg_Active > Ex_Max_Demand.Neg_Active.Var)
  {
  Ex_Max_Demand.Neg_Active.Var = Demand_Accu.Phase_Cur[0].Neg_Active;
  Get_BCD_Time((S_BCD_Time *)&Cur_Time1,  (INT8U *)Ex_Max_Demand.Neg_Active.Time,  \
  (INT8U *)Ex_Max_Demand.Neg_Active.Time,  sizeof(Ex_Max_Demand.Neg_Active.Time));
  }
  }
  else
  {
  mem_set((void *)&Ex_Max_Demand.Neg_Active,  \
  0, \
  sizeof(Ex_Max_Demand.Neg_Active), \
  (void *)&Ex_Max_Demand.Neg_Active, \
  sizeof(Ex_Max_Demand.Neg_Active));
  }

  //四象限无功需量超限
  for(i = 0; i < 4; i ++)
  {
  
  if(0)//
  {
  if(Demand_Accu.Phase_Cur[0].Quad_Reactive[i] > Ex_Max_Demand.Quad_Reactive[i].Var)
  {
  Ex_Max_Demand.Quad_Reactive[i].Var = Demand_Accu.Phase_Cur[0].Quad_Reactive[i];
  Get_BCD_Time((S_BCD_Time *)&Cur_Time1,  (INT8U *)Ex_Max_Demand.Quad_Reactive[i].Time,  \
    (INT8U *)Ex_Max_Demand.Quad_Reactive[i].Time,  sizeof(Ex_Max_Demand.Quad_Reactive[i].Time));
  }
  }
  else
  {
  mem_set((void *)&Ex_Max_Demand.Quad_Reactive[i],  \
  0, \
  sizeof(Ex_Max_Demand.Quad_Reactive[i]), \
  (void *)&Ex_Max_Demand.Quad_Reactive[i], \
  sizeof(Ex_Max_Demand.Quad_Reactive[i]));
  }
  }
}
*/
/*
INT8U OS_Assert_Hook()
{
   INT8U Re;

  Assert_Info.On_Off_Flag =0;
   if(Check_Demand_Data((S_Demand *)&Cur_Demand) EQ 0)
   Re =0;
   else
   Re =1;
  Assert_Info.On_Off_Flag =0xFF;
  return Re;
}
*/
#undef DEMAND_C
