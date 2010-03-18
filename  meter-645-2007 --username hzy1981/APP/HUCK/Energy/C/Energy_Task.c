#define ENERGY_TASK_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H26"
#endif

//初始化电量和需量数据
void PowerOn_Read_Data_From_Rom()
{
  INT8U Rst_Flag;

  TRACE();

  //读取掉电时存储的电量数据,没有读取成功则读取备份存储的数据 
  Rst_Flag = Check_Rst_Flag();
  //显示第一屏以前已经读取到总电量
  if(Rst_Flag EQ POWER_ON_RST || Check_Energy_Data((S_Energy *) &Cur_Energy) EQ 0)//电源上电或者校验和错误的情况下都必须读取ROM中的数据
  {
    Debug_Print("PowerOn Read Energy Data");
    Read_Energy_Data_From_Rom();
  }
 ///测试临时程序
  //Cur_Energy.Prepaid_Info.Left_Money = 100000;
  //Cur_Energy.Prepaid_Info.Overdraft_Money = 0;
  //SET_STRUCT_SUM(Cur_Energy);
  
  //读取掉电时存储的需量数据，没有读取成功则读取备份存储的数据 
  if(Rst_Flag EQ POWER_ON_RST || Check_Demand_Data((S_Demand *) &Cur_Demand) EQ 0)//电源上电或者校验和错误的情况下都必须读取ROM中的数据
  {
    Debug_Print("PowerOn Read Demand Data");
    Read_Demand_Data_From_Rom();
  }

  //读取掉电时存储的需量时间数据，没有读取成功则读取备份存储的数据
  if(Rst_Flag EQ POWER_ON_RST || Check_VolStat_Data((S_VolStat *) &Cur_VolStat) EQ 0)//电源上电或者校验和错误的情况下都必须读取ROM中的数据
  {
    Debug_Print("PowerOn Read VolStat Data");
    Read_VolStat_Data_From_Rom();
  } 

  //读取负荷曲线存储信息
  if(Rst_Flag EQ POWER_ON_RST || CHECK_STRUCT_SUM(LoadData_Index) EQ 0)//电源上电或者校验和错误的情况下都必须读取ROM中的数据
  {
    Debug_Print("PowerOn Read LoadData Index");
    Read_LoadData_Index_Data_From_Rom();
  }

  //if(Rst_FlagEQPOWER_ON_RST || CHECK_STRUCT_SUM(Event_Cumu)EQ0)//电源上电或者校验和错误的情况下都必须读取ROM中的数据 
  {
    //Debug_Print("PowerOn Read Event_Cumu Data");
    //Read_Event_Cumu_Data_From_Rom();
  }
}

//任务中查询重要数据的校验和不对时，调用此函数
void Check_Data_Avail()
{
  TRACE();

  Check_Energy_Data_Para_Avail();
}
//检查数据与参数的主流程
void Main_Chk_Data_Avail()
{
  TRACE();
  
  if(Chk_Data_Flag.Chk_Flag EQ 1)
  {
    Check_Energy_Data_Para_Avail();
    Chk_Data_Flag.Chk_Flag = 0;
  }
}
//检查所有数据的可用性
void Check_Energy_Data_Para_Avail()
{
  INT8U Re;
  static S_Int8U Flag = {CHK_BYTE, 0, CHK_BYTE};

  TRACE();

  Re = CHECK_STRUCT_VAR(Flag);
  ASSERT(1 EQ Re);

  if(Flag.Var EQ 1)//防止下面的函数里面在调用Check_Data_Avail(),从而导致嵌套
  {
    return;
  }

  Flag.Var = 1;
  //下面的函数最好不要再别的流程中调用，防止发生嵌套调用
  ASSERT(PD_INT_EN_Flag EQ 1);
  ASSERT(CHECK_STRUCT_VAR(Trace_Info));

  Check_Energy_Data_Avail();//检查当前电量需量数据是否合法
  //OS_TimeDly_Ms(20);
  Check_Energy_Para_Avil();//检查电量相关参数是否合法
  //OS_TimeDly_Ms(20);
  Check_Demand_Data_Avail();//检查需量数据是否合法
  OS_TimeDly_Ms(20);
  Check_Demand_Para_Avail();//检查需量参数是否合法
  //OS_TimeDly_Ms(20);
  Check_Clock_Data_Avail();//检查时钟数据是否有效
  //OS_TimeDly_Ms(20);
  Check_LoadData_Index_Avail();//检查负荷曲线索引信息是否合法
  OS_TimeDly_Ms(20);
  Check_LoadData_Para_Avail();//检查负荷曲线参数是否合法
  //OS_TimeDly_Ms(20);
  Check_Ctrl_Para_Avail();//检查控制相关参数是否正确
  Check_Ctrl_Data_Avail(); //检查控制相关数据是否正确
  //OS_TimeDly_Ms(20);
  Check_Sys_Status_Avail();//检查当前系统状态是否合法
  OS_TimeDly_Ms(20);
  Check_Pub_Var_Avail();//检查全局buf或者变量的是否合法
  //OS_TimeDly_Ms(20);
  //Check_Event_Cumu_Avail();//检查事件累加数据是否正确
  //OS_TimeDly_Ms(20);
  //Check_Data_Trans_Data_Avail();//检查协议传输相关数据是否正确
  OS_TimeDly_Ms(20);
  Check_Low_Power_Data_Avail();//检查低功耗相关变量是否正确
  //OS_TimeDly_Ms(20);
  Check_VolStat_Para_Avail();//检查电压统计参数的合法性
  //OS_TimeDly_Ms(20);
  Check_VolStat_Data_Avail();//检查电压统计数据的合法性
  OS_TimeDly_Ms(20);
  Check_Event_Data_Avail();
  Flag.Var = 0;
  return;
}

//打印电量需量信息
void Print_Energy_Demand_Info()
{
  TRACE();

  //Debug_Print_Cur_Energy_Info(); 
  //Debug_Print_Cur_Demand_Info();
  //Debug_Print_Debug_Run_Info();
}


void Energy_Proc_Ram_Init()
{
  TRACE();

  Init_Mutex();//初始化信号量
  Init_Clock_Ram_Para();//初始化始终内存
  Init_Energy_Demand_Ram_Para();//初始化电量需量相关内存
  Init_VolStat_Ram_Para();//电压统计变量初始化
  Init_Data_Trans_Ram_Para();//数据传输相关变量初始化  
  Init_Low_Power_Ram(); //低功耗处理相关变量初始化
  Init_Ctrl_Ram(); //负荷控制相关变量初始化
}

extern INT8U Check_Imp_Data_Storage();
//电量和需量的任务的初始化,该初始化只在主任务中调用，在各自任务创建前调用
void PowerOn_Read_Para_From_Rom()
{
  TRACE();
  
  //if(Check_Sys_Status() EQ SYS_NORMAL)//系统电源正常的情况下才进行数据冻结和需量处理
  {
    Read_Para_From_Rom();//读取存储在ROM中的参数,此函数前需要先读取到时钟!
    Clock_Update();//重新获取时间,因为前面的读函数会用掉很多时间
  }
  //else
  {
    //Read_Energy_Para_From_Rom();//初始化电能累计相关参数
    //Read_Data_Trans_Para_From_Rom();//数据转换需要的相关参数初始化 
  }
}

//设置清除数据结果标志，1表示成功，0表示失败
void Set_Clear_Data_Result(INT8U Re)
{
  Clear_Flag.Result = Re;
  SET_STRUCT_SUM(Clear_Flag);
}

INT8U Get_Clear_Data_Result()
{
  return Clear_Flag.Result;
}

//检查是否有清数据需要
//清数据前需要调用Set_Clear_Data_Flag函数进行设置
void Check_Clear_Data()
{
  INT32U Flag;

  TRACE();

  Flag = Check_Clear_Data_Flag();//CHECK_STRUCT_SUM(Clear_Flag);

  if(CLEAR_ALL_FLAG EQ Flag)//电表清0
  {
    Set_Event_Instant(ID_EVENT_CLR_ALL_DATA); //电表清0
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_ALL_DATA); 
    
    Clear_Energy_Data(); //清
    Clear_Demand_Data();
    Clear_VolStat_Data();
    Clear_Event_Data(0xFFFFFFFF);
    Clear_Clr_Event_Data(); //清事件清零记录
    Clear_Load_Data();
    Clear_Data_End();//清数据完成
    
    Clear_Authority_Flag();
    Clock_Update(); //清数据时间太长，更新时钟
    OS_TimeDly_Ms(100);//让出CPU给通信任务    
  }
  //清需量
  else if(CLEAR_DEMAND_FLAG EQ Flag)
  {
    Set_Event_Instant(ID_EVENT_CLR_DEMAND_COM); //清需量事件
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_DEMAND_COM); //等待事件处理完成
    
    Clear_Cur_Demand_Data();
    Clear_Data_End();//清数据完成
    
    Clear_Authority_Flag();
    Clock_Update();    
    OS_TimeDly_Ms(100);//让出CPU给通信任务 
  }
  else if(CLEAR_EVENT_FLAG EQ Flag)
  {
    Set_Clear_Data_Result(0);
    
    Clear_Event_Data(Clear_Event_PDI); 
    Clear_Data_End();//清数据完成
    
    if(Get_Clear_Data_Result() != 0)//如果清除成功 Clear_Event_PDI != 0
    {
      Set_Event_Instant(ID_EVENT_CLR_PROCESS); //清过程
      Wait_Event_Data_Proc_End(ID_EVENT_CLR_PROCESS); //等待事件处理完成
    }    
    
    Clear_Authority_Flag();  
    Clock_Update();    
    OS_TimeDly_Ms(100);//让出CPU给通信任务
  }
}
/*
void Energy_Task_Ram_Init()
{
  Init_Sem();//初始化信号量
  Init_Clock_Ram_Para();//初始化始终内存
  Init_Energy_Demand_Ram_Para();//初始化电量需量相关内存
  Init_VolStat_Ram_Para();//电压统计变量初始化
  Init_Data_Trans_Ram_Para();//数据传输相关变量初始化  
  Init_Low_Power_Ram();
}

extern INT8U Check_Imp_Data_Storage();
//电量和需量的任务的初始化,该初始化只在主任务中调用，在各自任务创建前调用
void Energy_Demand_Task_Init()
{
  if(Check_Sys_Status()EQSYS_NORMAL)//系统电源正常的情况下才进行数据冻结和需量处理
  {
  //Check_Imp_Data_Storage();
  //Check_Sys_Storage();//存储器自检
  //Check_Boot_On_Flag();//判断是否是第一次上电，是则设置默认参数
  //Init_Clock();//初始化时钟
  Read_Para_From_Rom();//读取存储在ROM中的参数,此函数前需要先读取到时钟!
  Clock_Update();//重新获取时间,因为前面的读函数会用掉很多时间
  }
  else
  {
  //在唤醒的情况下没有读取参数，但是有如下两类参数需要读取
  Read_Mode_Word();//模式字
  Read_Data_Trans_Para_From_Rom();//数据转换相关参数
  }
}
*/
void Task_Switch_Hook()
{
  static INT32U Ms10_Timer = 0;
  static INT32U Max = 0;
  static INT32U Temp = 1000;

  //TRACE();

  if(Ms10_Timer_Pub > Ms10_Timer && Ms10_Timer_Pub - Ms10_Timer > Max)
  {
    Max = Ms10_Timer_Pub - Ms10_Timer;
  }

  if(Max > Temp)
  {
    Max = Max;
  }
  Ms10_Timer = Ms10_Timer_Pub;
}

/*
//打印电量需量信息
void Print_Energy_Demand_Info()
{
  Debug_Print_Cur_Energy_Info(); 
  Debug_Print_Cur_Demand_Info();
}
*/

//清电量数据
void Clear_Energy_Data()
{
  TRACE();
 
  TRACE();
  
  Set_Clear_Data_Result(0);
  
  if(Check_Clear_Data_Authority() EQ 0)
    return;

  if(CLEAR_ENERGY_FLAG != Check_Clear_Data_Flag() && CLEAR_ALL_FLAG != Check_Clear_Data_Flag())
    return;

  DISP_CLR_DATA_INFO;
  Debug_Print("Clear_Energy_Data!!!");   
  Set_Def_Energy_Data();
  Set_Clear_Data_Result(1);
}

//初始化电量相关参数
void Read_Para_From_Rom()
{
  TRACE();
  Read_Energy_Para_From_Rom();//初始化电能累计相关参数
  Read_Demand_Para_From_Rom();//初始化需量相关参数
  Read_Data_Trans_Para_From_Rom();//数据转换需要的相关参数初始化 
  Read_VolStat_Para_From_Rom();//电压统计相关参数
  Read_LoadData_Para_From_Rom();//负荷曲线相关参数
  Read_Ctrl_Para_From_Rom();//读取负荷控制参数
  //Read_Settle_Para_From_Rom();//读取结算相关参数
  Read_Freeze_Para_From_Rom(); //读取冻结相关参数
  Read_Adj_Time_Para_From_Rom();//读取校时相关参数
}

void Refresh_Para_From_Rom()
{
  TRACE();
  Read_Energy_Para_From_Rom();//初始化电能累计相关参数
  OS_TimeDly_Ms(100);
  Read_Demand_Para_From_Rom();//初始化需量相关参数
  OS_TimeDly_Ms(100);
  Read_Data_Trans_Para_From_Rom();//数据转换需要的相关参数初始化
  OS_TimeDly_Ms(100);
  Read_VolStat_Para_From_Rom();//电压统计相关参数
  OS_TimeDly_Ms(100);
  Read_LoadData_Para_From_Rom();//负荷曲线相关参数
  OS_TimeDly_Ms(100);
  Read_Ctrl_Para_From_Rom();//读取负荷控制参数
  //OS_TimeDly_Ms(100);
  //Read_Settle_Para_From_Rom(); //读取结算相关参数
  OS_TimeDly_Ms(100);
  Read_Freeze_Para_From_Rom(); //读取冻结相关参数
  OS_TimeDly_Ms(100);
  Read_Adj_Time_Para_From_Rom();//读取校时相关参数
}

void Init_Mutex()
{
  //初始化信号量
  OS_Event_Init();
  OS_Mutex_Init(PUB_BUF_SEM_ID, 1);//初始化Pub_Buf公共信号量
  OS_Mutex_Init(PUB_BUF0_SEM_ID, 1);//初始化Pub_Buf公共信号量  
  OS_Mutex_Init(PUB_RW_ROM_ID, 1);//初始化读写ROM的信号量 
  OS_Mutex_Init(TRANS_BUF_SEM_ID,1);
}
//上电补结算(补冻)数据
void PowerOn_Settle_Data()
{
  TRACE();

  //PowerOn_Settle_Energy_Data();//电量数据---技术条件修改为上电不补结算
  //PowerOn_Settle_Demand_Data();//需量数据---上电不补结算
  //PowerOn_Settle_VolStat_Data();//电压统计数据
}

//上电等待计量数据c初始化
void PowerOn_Wait_Measure_Inited()
{
  if(Check_Sys_Status() != SYS_NORMAL)
    return;
  
  OS_Waitfor_Sec(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg, 5);//等待计量数据准备好！
  if(1 != Measu_Status_Mode_ToPub_PUCK.DataRecFlg)
  {
    ASSERT_FAILED();
    OS_Waitfor(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg);
  }
}

void PowerOn_Data_Proc()
{
  Prepaid_Clr_Month_Eng_Chk((S_HEX_Time *)&Cur_Time0); //是否需要重新开始一个新的结算周期  
  //PowerOn_Read_Data_From_Rom();//电量数据读取初始化
  if(Check_Sys_Status() EQ SYS_NORMAL)//系统电源正常的情况下才进行数据冻结和需量处理
  {
    PowerOn_Settle_Data();//进行月数据结算，前HIS_ENERGY_ENERGY_DATA_MONTHS个月的数据  
    PowerOn_Demand_Proc(); //上电后的需量计算
    /*
    OS_Waitfor_Sec(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg, 5);//等待计量数据准备好！
    if(1 != Measu_Status_Mode_ToPub_PUCK.DataRecFlg)
    {
      ASSERT_FAILED();
      OS_Waitfor(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg);
    }
    */
  }
  
  return;
}

//刷新钱包文件
void Update_Esam_Remain_Money()
{
  static S_Int8U Mins = {CHK_BYTE, 0xF0, CHK_BYTE};
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U Re;
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Mins);
  Re &= CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(Re EQ 1);
  
  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];
    
    Mins.Var ++;
    if(Mins.Var >= 60) //每60分钟刷新一次Esam
    {
      Mins.Var = 0;
      UpdataEsamMoneyBag();
    }
  }
}

//检查电表是否调试版本
void Check_Meter_Debug_En()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int32U Counts = {CHK_BYTE, 0, CHK_BYTE};
  
  if(METER_DEBUG_EN > 0)
  {
    if(Counts.Var % 60 EQ 0)
      _Debug_Print("Meter debug version 120 days");
    
    if(Min.Var != Cur_Time1.Min)
    {
       Min.Var = Cur_Time1.Min;
       Counts.Var ++;
    }
    
    if(Counts.Var >= (INT32U)1440*120) //120天锁死
    {
      while(1)
      {
        Disp_Info("db 120"); 
        Clear_All_Dog();
      }
    }
  }
}

//电量需量任务
//其实除了计算电量、需量等还做了电压统计、负荷曲线、时钟处理等工作
void Energy_Proc()
{
  //return;
  TRACE();

  {
    Clear_Task_Dog();//清任务软狗

    Check_Meter_Debug_En(); //检查是否是调试版本
    
    Clock_Proc();//时钟处理，定时刷新时钟
    Check_Energy_Para_Modified();//检查参数是否发生修改

    PSW_Timer_Proc();//密码锁定计时
    Prog_Timer_Proc();//编程计时

    Check_Energy_Data_Para_Avail();//检查本任务所用数据的合法性
    Check_Cur_Rate();//检查当前费率
    //Check_Cur_Step();//检查当前阶梯

    Cumulative_Energy();//每秒累加电量
    UpdataEsamMoneyBag(); //定时更新esam的钱包文件
    
    VolStat_Proc();//电压统计处理  
    
    Settle_Data();//每月自动抄表结算
    Period_Save_Cur_Data();//定期自动保存当前数据

    Demand_Proc();//需量数据处理

    LoadData_Proc();//负荷曲线处理
    Freeze_Proc();//冻结数据
    Check_Clear_Data();//检查是否清除电量需量数据

    //Prepaid_Power_Ctrl_Proc(); //预付费的负荷控制处理(超脉冲)
    Power_Ctrl_Proc();//负荷控制处理(超需量)
    Switch_Ctrl_Proc();//对继电器的最终控制
    
    Event_Cumu_Mins_Accu();
    
    //Debug_Print_Cur_Energy_Info();//将当前费率信息输出到调试口
    Print_Energy_Demand_Info();
  }
}
#undef ENERGY_TASK_C
