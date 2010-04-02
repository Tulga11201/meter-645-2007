#define TASKPRG_CFG_C
#include "TaskProc.h"
#include "Includes.h"
#include "pub.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "AE"
#endif

/**********************************************************************************
�������ܣ�����ڹ����⹷
��ڣ�    
���ڣ�    
**********************************************************************************/
void Clr_Ext_Inter_Dog(void)
{    
  Clear_CPU_Dog();    //��CPU�ڲ����Ź�
  Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
}
/**********************************************************************************
�������ܣ�������п��Ź�
��ڣ�    
���ڣ�    
**********************************************************************************/
void Clear_All_Dog(void)
{    
  Clear_Task_Dog();   //�������Ź�
  Clear_CPU_Dog();    //��CPU�ڲ����Ź�
  Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
}

void Creat_LCD_Task()
{
#ifdef TASK_LCD_LUCK_EN  
  OS_Create_Task(&AppLCDTask_LUCK,(OS_STK *)(&AppLCDTaskStk_LUCK[TASK_LCD_SIZE_LUCK-1]),sizeof(AppLCDTaskStk_LUCK),"AppLCDTask_LUCK");
#endif  
}

/**********************************************************************************
�������ܣ���������������
��ڣ�    
���ڣ�    
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
  Trace_Info.Entry_Flag=0;//��ֹ�������뱨��
  INIT_STRUCT_VAR(Trace_Info);
  OS_Trace_Ctrl(0xFF);//ǰ8������ȫ���򿪶���  
  
  if(JUDGE_POWER_OFF==0)  //����Դ�����£��Ŵ������Ϣ
  {
    Init_DebugChanel_PUCK(1);     //��ʼ�����Դ��ڣ����ж�����״̬
    _OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ
    _OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ
    _OS_Debug_Print("\r\n---------------SYSTEM START----------------");      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ
    //OS_Debug_Print("\r\n----------Version:%s----------",COMM_PROTO_VERSION);      //�ϵ��ǿ�ƴ�ӡ��λ��Ϣ  
    Print_Reset_Source();     
    ASSERT(0);//��ʾ��λǰ�ĺ������ù켣    
    Close_DebugChanel_PUCK(1);   //�رյ��Դ��ڣ����ж�����״̬
  }
}
INT8U GetParseEnergChangeValue_PUCK(void);
/**********************************************************************************
�������ܣ�������
��ڣ�    
���ڣ�    
**********************************************************************************/
void  Main_Task_PUB(void *p_arg)
{
  //PROTO_DI DI;
  
  PD_DATA_PROC();//�����������
  Monitor_Init();//ϵͳ����ʼ��
  
  //Clr_Screen_PUCK();  //�ϵ��ǿ����LCD��ʾ
  GetParseEnergChangeValue_PUCK();
  Main_Init_Print();  
  
  Energy_Proc_Ram_Init();
  Init_Measure_Ram();  //��ʼ�����sram
  
  Test_HardWare_PUCK();  //�����ص�sram��ʼ���󣬲��ܵ��ã����ź�����ʼ��
  Soft_All_Loss_Proc();
  
  Init_Low_Power_Proc();
  //PD_INT_EN_Flag= 1;
  
  Check_Boot_On_Flag();//�ڹ���״̬�£�����Ƿ��ǵ�һ���ϵ�
  //Read_Energy_Data_Para_For_Show();//�˴���ȡ�����Ա���Һ����ʾ

  Init_Measu_PUCK();  //��ʼ����������Һ��������ʾ�����¼��ж�  
  LCD_Init_PUCK();   //LCD��ʾ��ʼ���������ٶ���Ҫ

  PowerOn_Read_Para_From_Rom();   //������ʼ��
  PowerOn_Read_Data_From_Rom();//���ݳ�ʼ��
  
  Extend_Init();
  
#ifdef TEST_MODE
  Test_Unit();
#endif

  Init_Check_Code_License(); //������License�Ƿ���ȷ
  PowerOn_Data_Proc(); //�ϵ����ݴ���
  
  Creat_LCD_Task(); //��ʼ��Һ������,��֤ͨ�ź���ʾ����������
  PowerOn_Event_Proc();//�ϵ���ǰһ�ε���ǰ���¼����� 
  Creat_AllSub_Tasks(); //��������������
  //PowerOn_Wait_Measure_Inited(); //�ȴ���������OK��
  
  //Check_Protocol_Data_Trans();  //���Э�鴫�䡣�������ڴ˴�����ΪҪ�������������ݡ�������׼����
  Clr_Main_Init_Flag(); //��ʼ����ɣ�  
  for(;;)
  {
    Low_Power_Proc();
    //Main_Chk_Data_Avail();
    Task_Monitor_Proc();
    //Clear_Task_Dog();   //�������Ź�
    //Clear_CPU_Dog();    //��CPU�ڲ����Ź�
    Clear_All_Dog();
    //Get_Para_Modify(&DI);  //��ȡ������ÿ��������Ҫ�Ӳ����޸Ķ����ж�ȡ����
    Power_Down_Check();
    
    Energy_Proc();
    OS_TimeDly_Ms(100);   //100ms˯��
   }
}
/**********************************************************************************
�������ܣ���������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_MEASU_PUCK_EN
void  AppMeasuTask_PUCK (void *p_arg)
{
       
    (void)p_arg;
     //Measu_Main_Puck(1);
    Print_Measure_Err_Info();
    
#ifndef TASK_EVENT_PUCK_EN   //�������¼����϶�Ϊһ
    Event_main_PUCK(1);
#endif  
for(;;)	
  {
    Task_Monitor_Proc();
    Measu_Event_Main();
    Emerg_Event_Proc();     //��ͻ���¼���ÿ10ms����������Channel_Data_Proc_PUCKStatus��ͬ��
    Clear_Task_Dog();   //�������Ź�
    OS_TimeDly_Ms(100);//100Ms˯��
  }
}
#endif


/**********************************************************************************
�������ܣ�ͨ��ά������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_EVENT_PUCK_EN
void  AppEventTask_PUCK(void *p_arg)
{

    (void)p_arg;
    Event_main_PUCK(1);
    
for(;;)	
  { 
      Event_main_PUCK(0);      
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Ms(100);//100ms˯��
  }
}
#endif
/**********************************************************************************
�������ܣ���������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_FREEZ_HUCK_EN
void  AppFreezeTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
for(;;)	
  {  
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Sec(1);//1s˯��
  }
}
#endif

/**********************************************************************************
�������ܣ����ܴ�������:��ʱ/����,��������
��ڣ�    
���ڣ�    
**********************************************************************************/
#ifdef TASK_ENERGE_HUCK_EN
void  AppEnergeTask_HUCK (void *p_arg)
{
       
    (void)p_arg;
    Energy_Proc();
for(;;)	
  {  
      Energy_Proc();
      Clear_Task_Dog();   //�������Ź�
      OS_TimeDly_Ms(100);//100ms˯��
  }
}
#endif

/**********************************************************************************
�������ܣ����ܴ�������:��ʱ/����,��������
��ڣ�    
���ڣ�    
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
      Clear_Ext_Dog();    //����������CPU�ⲿ���Ź�
      Clear_Task_Dog();   //�������Ź�
      Shell_Proc();       //shell����
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
      //OS_TimeDly_Min(5);//UPDATETIMEms˯��
  }
}
#endif