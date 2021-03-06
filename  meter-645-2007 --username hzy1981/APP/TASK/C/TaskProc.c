#define TASKPRG_CFG_C
#include "TaskProc.h"
#include "Includes.h"
#include "pub.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "AE"
#endif

/**********************************************************************************
函数功能：清除内狗和外狗
入口：    
出口：    
**********************************************************************************/
void Clr_Ext_Inter_Dog(void)
{    
  Clear_CPU_Dog();    //清CPU内部看门狗
  Clear_Ext_Dog();    //清CPU外部看门狗
}
/**********************************************************************************
函数功能：清除所有看门狗
入口：    
出口：    
**********************************************************************************/
void Clear_All_Dog(void)
{    
  Clear_Task_Dog();   //清任务看门狗
  Clear_CPU_Dog();    //清CPU内部看门狗
  Clear_Ext_Dog();    //清CPU外部看门狗
}

void Creat_LCD_Task()
{
#ifdef TASK_LCD_LUCK_EN  
  OS_Create_Task(&AppLCDTask_LUCK,(OS_STK *)(&AppLCDTaskStk_LUCK[TASK_LCD_SIZE_LUCK-1]),sizeof(AppLCDTaskStk_LUCK),"AppLCDTask_LUCK");
#endif  
}

/**********************************************************************************
函数功能：创建所有子任务
入口：    
出口：    
**********************************************************************************/
void Creat_AllSub_Tasks(void)
{ 
#ifdef TASK_ENERGE_HUCK_EN  
  OS_Create_Task(&AppEnergeTask_HUCK,&AppEnergTaskStk_huck[TASK_ENERGE_SIZE_HUCK-1],sizeof(AppEnergTaskStk_huck),"AppEnergeTask_HUCK");
#endif  
  
#ifdef TASK_MEASU_PUCK_EN
  OS_Create_Task(&AppMeasuTask_PUCK,(OS_STK *)(&AppMeasuTaskStk_PUCK[TASK_MEASU_SIZE_PUCK-1]),sizeof(AppMeasuTaskStk_PUCK),"AppMeasuTask_PUCK");
#endif

#ifdef TASK_CHANNEL_PUCK_EN
  OS_Create_Task(&AppChannelTask_PUCK,(OS_STK *)(&AppChannelTaskStk_PUCK[TASK_CHANNEL_SIZE_PUCK-1]),sizeof(AppChannelTaskStk_PUCK),"AppChannelTask_PUCK");
 #endif
  
  
#ifdef TASK_EVENT_PUCK_EN 
  OS_Create_Task(&AppEventTask_PUCK,(OS_STK *)(&AppEventTaskStk_PUCK[TASK_EVENT_STK_SIZE_PUCK-1]),sizeof(AppEventTaskStk_PUCK),"AppEventTask_PUCK");
#endif
  
  
#ifdef TASK_FREEZ_HUCK_EN  
  OS_Create_Task(&AppFreezeTask_HUCK,(OS_STK *)(&AppFreezTaskStk_HUCK[TASK_FREEZ_SIZE_HUCK-1]),sizeof(AppFreezTaskStk_HUCK),"AppFreezeTask_HUCK");
#endif
  
  
#ifdef TEST_MODE  
  OS_Create_Task(&AppTestTask_HUCK,(OS_STK *)(&AppTestTaskStk_HUCK[TASK_TEST_SIZE_HUCK-1]),sizeof(AppTestTaskStk_HUCK),"AppTestTask_HUCK");
#endif
  
  Debug_Print("All Tasks Created Succeed!");
}

void Main_Init_Print()
{
  Trace_Info.Entry_Flag=0;//防止函数重入报错
  INIT_STRUCT_VAR(Trace_Info);
  OS_Trace_Ctrl(0xFF);//前8个任务全部打开断言  
  
  if(JUDGE_POWER_OFF==0)  //主电源供电下，才打调试信息
  {
    Init_DebugChanel_PUCK(1);     //初始化调试串口，需判定工厂状态
    _OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //上电后强制打印复位信息
    _OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //上电后强制打印复位信息
    _OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //上电后强制打印复位信息
    //OS_Debug_Print("\r\n----------Version:%s----------",COMM_PROTO_VERSION);      //上电后强制打印复位信息  
    Print_Reset_Source();     
    ASSERT(0);//显示复位前的函数调用轨迹    
    Close_DebugChanel_PUCK(1);   //关闭调试串口，需判定工厂状态
  }
}
INT8U GetParseEnergChangeValue_PUCK(void);
/**********************************************************************************
函数功能：主任务
入口：    
出口：    
**********************************************************************************/
void  Main_Task_PUB(void *p_arg)
{
  //PROTO_DI DI;
  
  PD_DATA_PROC();//掉电存数处理
  Monitor_Init();//系统检测初始化
  
  //Clr_Screen_PUCK();  //上电后，强行清LCD显示
  GetParseEnergChangeValue_PUCK();
  Main_Init_Print();  
  
  Energy_Proc_Ram_Init();
  Init_Measure_Ram();  //初始化相关sram
  
  Test_HardWare_PUCK();  //需等相关的sram初始化后，才能调用，如信号量初始化
  Soft_All_Loss_Proc();
  
  Init_Low_Power_Proc();
  //PD_INT_EN_Flag= 1;
  
  Check_Boot_On_Flag();//在工厂状态下，检查是否是第一次上电
  //Read_Energy_Data_Para_For_Show();//此处读取电量以便让液晶显示

  Init_Measu_PUCK();  //初始化计量，供液晶数据显示，供事件判定  
  LCD_Init_PUCK();   //LCD显示初始化，满足速度需要

  PowerOn_Read_Para_From_Rom();   //参数初始化
  PowerOn_Read_Data_From_Rom();//数据初始化
  
  Extend_Init();
  
#ifdef TEST_MODE
  Test_Unit();
#endif

  Init_Check_Code_License(); //检查代码License是否正确
  PowerOn_Data_Proc(); //上电数据处理
  
  Creat_LCD_Task(); //初始化液晶任务,保证通信和显示先运行起来
  PowerOn_Event_Proc();//上电后对前一次掉电前的事件处理 
  Creat_AllSub_Tasks(); //创建其他子任务
  //PowerOn_Wait_Measure_Inited(); //等待计量数据OK！
  
  //Check_Protocol_Data_Trans();  //检查协议传输。函数放在此处是因为要等其他所有数据、参数都准备好
  Clr_Main_Init_Flag(); //初始化完成！  
  for(;;)
  {
    Low_Power_Proc();
    //Main_Chk_Data_Avail();
    Task_Monitor_Proc();
    //Clear_Task_Dog();   //清任务看门狗
    //Clear_CPU_Dog();    //清CPU内部看门狗
    Clear_All_Dog();
    //Get_Para_Modify(&DI);  //读取参数，每个任务都需要从参数修改队列中读取出来
    Power_Down_Check();
    
    Energy_Proc();
    OS_TimeDly_Ms(100);   //100ms睡眠
   }
}
/**********************************************************************************
函数功能：计量任务
入口：    
出口：    
**********************************************************************************/
#ifdef TASK_MEASU_PUCK_EN
void  AppMeasuTask_PUCK (void *p_arg)
{
       
    (void)p_arg;
     //Measu_Main_Puck(1);
    Print_Measure_Err_Info();
    
#ifndef TASK_EVENT_PUCK_EN   //计量和事件，合二为一
    Event_main_PUCK(1);
#endif  
for(;;)	
  {
    Task_Monitor_Proc();
    Measu_Event_Main();
    Emerg_Event_Proc();     //对突发事件的每10ms处理，必须与Channel_Data_Proc_PUCKStatus）同步
    Clear_Task_Dog();   //清任务看门狗
    OS_TimeDly_Ms(100);//100Ms睡眠
  }
}
#endif


/**********************************************************************************
函数功能：通道维护任务
入口：    
出口：    
**********************************************************************************/
#ifdef TASK_EVENT_PUCK_EN
void  AppEventTask_PUCK(void *p_arg)
{

    (void)p_arg;
    Event_main_PUCK(1);
    
for(;;)	
  { 
      Event_main_PUCK(0);      
      Clear_Task_Dog();   //清任务看门狗
      OS_TimeDly_Ms(100);//100ms睡眠
  }
}
#endif
/**********************************************************************************
函数功能：冻结任务
入口：    
出口：    
**********************************************************************************/
#ifdef TASK_FREEZ_HUCK_EN
void  AppFreezeTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
for(;;)	
  {  
      Clear_Task_Dog();   //清任务看门狗
      OS_TimeDly_Sec(1);//1s睡眠
  }
}
#endif

/**********************************************************************************
函数功能：电能处理任务:分时/费率,需量处理
入口：    
出口：    
**********************************************************************************/
#ifdef TASK_ENERGE_HUCK_EN
void  AppEnergeTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
    Energy_Proc();
for(;;)	
  {  
      Energy_Proc();
      Clear_Task_Dog();   //清任务看门狗
      OS_TimeDly_Ms(100);//100ms睡眠
  }
}
#endif

/**********************************************************************************
函数功能：电能处理任务:分时/费率,需量处理
入口：    
出口：    
**********************************************************************************/
#ifdef TASK_LCD_LUCK_EN
void  AppLCDTask_LUCK (void *p_arg)
{
       
    (void)p_arg;
    Channel_Main_PUCK(1);
    //LCD_main_LUCK();   
for(;;)	
  {
      Task_Monitor_Proc();
      Channel_Main_PUCK(0);
      LCD_main_LUCK();
      CPU_Card_Main_Proc();
      Clear_Ext_Dog();    //最快的任务：清CPU外部看门狗
      Clear_Task_Dog();   //清任务看门狗
      Shell_Proc();       //shell界面
#ifdef CHANNEL_FAST_EN
      OS_Waitfor_Ms(REC_FRAME_CONDITION,10);
      CLR_REC_FRAME;
#else
      OS_TimeDly_Ms(10);
#endif
  }
}
#endif

#ifdef TEST_MODE
void  AppTestTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
    
    Test_Proc(1);

  for(;;)	
  {        
      Test_Proc(0);
      Clear_Task_Dog();
      //OS_TimeDly_Min(5);//UPDATETIMEms睡眠
  }
}
#endif