#define ENERGY_TASK_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H26"
#endif

//��ʼ����������������
void PowerOn_Read_Data_From_Rom()
{
  INT8U Rst_Flag;

  TRACE();

  //��ȡ����ʱ�洢�ĵ�������,û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  Rst_Flag = Check_Rst_Flag();
  //��ʾ��һ����ǰ�Ѿ���ȡ���ܵ���
  if(Rst_Flag EQ POWER_ON_RST || Check_Energy_Data((S_Energy *) &Cur_Energy) EQ 0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    Debug_Print("PowerOn Read Energy Data");
    Read_Energy_Data_From_Rom();
  }
 ///������ʱ����
  //Cur_Energy.Prepaid_Info.Left_Money = 100000;
  //Cur_Energy.Prepaid_Info.Overdraft_Money = 0;
  //SET_STRUCT_SUM(Cur_Energy);
  
  //��ȡ����ʱ�洢���������ݣ�û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  if(Rst_Flag EQ POWER_ON_RST || Check_Demand_Data((S_Demand *) &Cur_Demand) EQ 0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    Debug_Print("PowerOn Read Demand Data");
    Read_Demand_Data_From_Rom();
  }

  //��ȡ����ʱ�洢������ʱ�����ݣ�û�ж�ȡ�ɹ����ȡ���ݴ洢������
  if(Rst_Flag EQ POWER_ON_RST || Check_VolStat_Data((S_VolStat *) &Cur_VolStat) EQ 0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    Debug_Print("PowerOn Read VolStat Data");
    Read_VolStat_Data_From_Rom();
  } 

  //��ȡ�������ߴ洢��Ϣ
  if(Rst_Flag EQ POWER_ON_RST || CHECK_STRUCT_SUM(LoadData_Index) EQ 0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    Debug_Print("PowerOn Read LoadData Index");
    Read_LoadData_Index_Data_From_Rom();
  }

  //if(Rst_FlagEQPOWER_ON_RST || CHECK_STRUCT_SUM(Event_Cumu)EQ0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е����� 
  {
    //Debug_Print("PowerOn Read Event_Cumu Data");
    //Read_Event_Cumu_Data_From_Rom();
  }
}

//�����в�ѯ��Ҫ���ݵ�У��Ͳ���ʱ�����ô˺���
void Check_Data_Avail()
{
  TRACE();

  Check_Energy_Data_Para_Avail();
}
//��������������������
void Main_Chk_Data_Avail()
{
  TRACE();
  
  if(Chk_Data_Flag.Chk_Flag EQ 1)
  {
    Check_Energy_Data_Para_Avail();
    Chk_Data_Flag.Chk_Flag = 0;
  }
}
//����������ݵĿ�����
void Check_Energy_Data_Para_Avail()
{
  INT8U Re;
  static S_Int8U Flag = {CHK_BYTE, 0, CHK_BYTE};

  TRACE();

  Re = CHECK_STRUCT_VAR(Flag);
  ASSERT(1 EQ Re);

  if(Flag.Var EQ 1)//��ֹ����ĺ��������ڵ���Check_Data_Avail(),�Ӷ�����Ƕ��
  {
    return;
  }

  Flag.Var = 1;
  //����ĺ�����ò�Ҫ�ٱ�������е��ã���ֹ����Ƕ�׵���
  ASSERT(PD_INT_EN_Flag EQ 1);
  ASSERT(CHECK_STRUCT_VAR(Trace_Info));

  Check_Energy_Data_Avail();//��鵱ǰ�������������Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Energy_Para_Avil();//��������ز����Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Demand_Data_Avail();//������������Ƿ�Ϸ�
  OS_TimeDly_Ms(20);
  Check_Demand_Para_Avail();//������������Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Clock_Data_Avail();//���ʱ�������Ƿ���Ч
  //OS_TimeDly_Ms(20);
  Check_LoadData_Index_Avail();//��鸺������������Ϣ�Ƿ�Ϸ�
  OS_TimeDly_Ms(20);
  Check_LoadData_Para_Avail();//��鸺�����߲����Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  Check_Ctrl_Para_Avail();//��������ز����Ƿ���ȷ
  Check_Ctrl_Data_Avail(); //��������������Ƿ���ȷ
  //OS_TimeDly_Ms(20);
  Check_Sys_Status_Avail();//��鵱ǰϵͳ״̬�Ƿ�Ϸ�
  OS_TimeDly_Ms(20);
  Check_Pub_Var_Avail();//���ȫ��buf���߱������Ƿ�Ϸ�
  //OS_TimeDly_Ms(20);
  //Check_Event_Cumu_Avail();//����¼��ۼ������Ƿ���ȷ
  //OS_TimeDly_Ms(20);
  //Check_Data_Trans_Data_Avail();//���Э�鴫����������Ƿ���ȷ
  OS_TimeDly_Ms(20);
  Check_Low_Power_Data_Avail();//���͹�����ر����Ƿ���ȷ
  //OS_TimeDly_Ms(20);
  Check_VolStat_Para_Avail();//����ѹͳ�Ʋ����ĺϷ���
  //OS_TimeDly_Ms(20);
  Check_VolStat_Data_Avail();//����ѹͳ�����ݵĺϷ���
  OS_TimeDly_Ms(20);
  Check_Event_Data_Avail();
  Flag.Var = 0;
  return;
}

//��ӡ����������Ϣ
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

  Init_Mutex();//��ʼ���ź���
  Init_Clock_Ram_Para();//��ʼ��ʼ���ڴ�
  Init_Energy_Demand_Ram_Para();//��ʼ��������������ڴ�
  Init_VolStat_Ram_Para();//��ѹͳ�Ʊ�����ʼ��
  Init_Data_Trans_Ram_Para();//���ݴ�����ر�����ʼ��  
  Init_Low_Power_Ram(); //�͹��Ĵ�����ر�����ʼ��
  Init_Ctrl_Ram(); //���ɿ�����ر�����ʼ��
}

extern INT8U Check_Imp_Data_Storage();
//����������������ĳ�ʼ��,�ó�ʼ��ֻ���������е��ã��ڸ������񴴽�ǰ����
void PowerOn_Read_Para_From_Rom()
{
  TRACE();
  
  //if(Check_Sys_Status() EQ SYS_NORMAL)//ϵͳ��Դ����������²Ž������ݶ������������
  {
    Read_Para_From_Rom();//��ȡ�洢��ROM�еĲ���,�˺���ǰ��Ҫ�ȶ�ȡ��ʱ��!
    Clock_Update();//���»�ȡʱ��,��Ϊǰ��Ķ��������õ��ܶ�ʱ��
  }
  //else
  {
    //Read_Energy_Para_From_Rom();//��ʼ�������ۼ���ز���
    //Read_Data_Trans_Para_From_Rom();//����ת����Ҫ����ز�����ʼ�� 
  }
}

//����������ݽ����־��1��ʾ�ɹ���0��ʾʧ��
void Set_Clear_Data_Result(INT8U Re)
{
  Clear_Flag.Result = Re;
  SET_STRUCT_SUM(Clear_Flag);
}

INT8U Get_Clear_Data_Result()
{
  return Clear_Flag.Result;
}

//����Ƿ�����������Ҫ
//������ǰ��Ҫ����Set_Clear_Data_Flag������������
void Check_Clear_Data()
{
  INT32U Flag;

  TRACE();

  Flag = Check_Clear_Data_Flag();//CHECK_STRUCT_SUM(Clear_Flag);

  if(CLEAR_ALL_FLAG EQ Flag)//�����0
  {
    Set_Event_Instant(ID_EVENT_CLR_ALL_DATA); //�����0
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_ALL_DATA); 
    
    Clear_Energy_Data(); //��
    Clear_Demand_Data();
    Clear_VolStat_Data();
    Clear_Event_Data(0xFFFFFFFF);
    Clear_Clr_Event_Data(); //���¼������¼
    Clear_Load_Data();
    Clear_Data_End();//���������
    
    Clear_Authority_Flag();
    Clock_Update(); //������ʱ��̫��������ʱ��
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������    
  }
  //������
  else if(CLEAR_DEMAND_FLAG EQ Flag)
  {
    Set_Event_Instant(ID_EVENT_CLR_DEMAND_COM); //�������¼�
    Wait_Event_Data_Proc_End(ID_EVENT_CLR_DEMAND_COM); //�ȴ��¼��������
    
    Clear_Cur_Demand_Data();
    Clear_Data_End();//���������
    
    Clear_Authority_Flag();
    Clock_Update();    
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������ 
  }
  else if(CLEAR_EVENT_FLAG EQ Flag)
  {
    Set_Clear_Data_Result(0);
    
    Clear_Event_Data(Clear_Event_PDI); 
    Clear_Data_End();//���������
    
    if(Get_Clear_Data_Result() != 0)//�������ɹ� Clear_Event_PDI != 0
    {
      Set_Event_Instant(ID_EVENT_CLR_PROCESS); //�����
      Wait_Event_Data_Proc_End(ID_EVENT_CLR_PROCESS); //�ȴ��¼��������
    }    
    
    Clear_Authority_Flag();  
    Clock_Update();    
    OS_TimeDly_Ms(100);//�ó�CPU��ͨ������
  }
}
/*
void Energy_Task_Ram_Init()
{
  Init_Sem();//��ʼ���ź���
  Init_Clock_Ram_Para();//��ʼ��ʼ���ڴ�
  Init_Energy_Demand_Ram_Para();//��ʼ��������������ڴ�
  Init_VolStat_Ram_Para();//��ѹͳ�Ʊ�����ʼ��
  Init_Data_Trans_Ram_Para();//���ݴ�����ر�����ʼ��  
  Init_Low_Power_Ram();
}

extern INT8U Check_Imp_Data_Storage();
//����������������ĳ�ʼ��,�ó�ʼ��ֻ���������е��ã��ڸ������񴴽�ǰ����
void Energy_Demand_Task_Init()
{
  if(Check_Sys_Status()EQSYS_NORMAL)//ϵͳ��Դ����������²Ž������ݶ������������
  {
  //Check_Imp_Data_Storage();
  //Check_Sys_Storage();//�洢���Լ�
  //Check_Boot_On_Flag();//�ж��Ƿ��ǵ�һ���ϵ磬��������Ĭ�ϲ���
  //Init_Clock();//��ʼ��ʱ��
  Read_Para_From_Rom();//��ȡ�洢��ROM�еĲ���,�˺���ǰ��Ҫ�ȶ�ȡ��ʱ��!
  Clock_Update();//���»�ȡʱ��,��Ϊǰ��Ķ��������õ��ܶ�ʱ��
  }
  else
  {
  //�ڻ��ѵ������û�ж�ȡ�������������������������Ҫ��ȡ
  Read_Mode_Word();//ģʽ��
  Read_Data_Trans_Para_From_Rom();//����ת����ز���
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
//��ӡ����������Ϣ
void Print_Energy_Demand_Info()
{
  Debug_Print_Cur_Energy_Info(); 
  Debug_Print_Cur_Demand_Info();
}
*/

//���������
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

//��ʼ��������ز���
void Read_Para_From_Rom()
{
  TRACE();
  Read_Energy_Para_From_Rom();//��ʼ�������ۼ���ز���
  Read_Demand_Para_From_Rom();//��ʼ��������ز���
  Read_Data_Trans_Para_From_Rom();//����ת����Ҫ����ز�����ʼ�� 
  Read_VolStat_Para_From_Rom();//��ѹͳ����ز���
  Read_LoadData_Para_From_Rom();//����������ز���
  Read_Ctrl_Para_From_Rom();//��ȡ���ɿ��Ʋ���
  //Read_Settle_Para_From_Rom();//��ȡ������ز���
  Read_Freeze_Para_From_Rom(); //��ȡ������ز���
  Read_Adj_Time_Para_From_Rom();//��ȡУʱ��ز���
}

void Refresh_Para_From_Rom()
{
  TRACE();
  Read_Energy_Para_From_Rom();//��ʼ�������ۼ���ز���
  OS_TimeDly_Ms(100);
  Read_Demand_Para_From_Rom();//��ʼ��������ز���
  OS_TimeDly_Ms(100);
  Read_Data_Trans_Para_From_Rom();//����ת����Ҫ����ز�����ʼ��
  OS_TimeDly_Ms(100);
  Read_VolStat_Para_From_Rom();//��ѹͳ����ز���
  OS_TimeDly_Ms(100);
  Read_LoadData_Para_From_Rom();//����������ز���
  OS_TimeDly_Ms(100);
  Read_Ctrl_Para_From_Rom();//��ȡ���ɿ��Ʋ���
  //OS_TimeDly_Ms(100);
  //Read_Settle_Para_From_Rom(); //��ȡ������ز���
  OS_TimeDly_Ms(100);
  Read_Freeze_Para_From_Rom(); //��ȡ������ز���
  OS_TimeDly_Ms(100);
  Read_Adj_Time_Para_From_Rom();//��ȡУʱ��ز���
}

void Init_Mutex()
{
  //��ʼ���ź���
  OS_Event_Init();
  OS_Mutex_Init(PUB_BUF_SEM_ID, 1);//��ʼ��Pub_Buf�����ź���
  OS_Mutex_Init(PUB_BUF0_SEM_ID, 1);//��ʼ��Pub_Buf�����ź���  
  OS_Mutex_Init(PUB_RW_ROM_ID, 1);//��ʼ����дROM���ź��� 
  OS_Mutex_Init(TRANS_BUF_SEM_ID,1);
}
//�ϵ粹����(����)����
void PowerOn_Settle_Data()
{
  TRACE();

  //PowerOn_Settle_Energy_Data();//��������---���������޸�Ϊ�ϵ粻������
  //PowerOn_Settle_Demand_Data();//��������---�ϵ粻������
  //PowerOn_Settle_VolStat_Data();//��ѹͳ������
}

//�ϵ�ȴ���������c��ʼ��
void PowerOn_Wait_Measure_Inited()
{
  if(Check_Sys_Status() != SYS_NORMAL)
    return;
  
  OS_Waitfor_Sec(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg, 5);//�ȴ���������׼���ã�
  if(1 != Measu_Status_Mode_ToPub_PUCK.DataRecFlg)
  {
    ASSERT_FAILED();
    OS_Waitfor(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg);
  }
}

void PowerOn_Data_Proc()
{
  Prepaid_Clr_Month_Eng_Chk((S_HEX_Time *)&Cur_Time0); //�Ƿ���Ҫ���¿�ʼһ���µĽ�������  
  //PowerOn_Read_Data_From_Rom();//�������ݶ�ȡ��ʼ��
  if(Check_Sys_Status() EQ SYS_NORMAL)//ϵͳ��Դ����������²Ž������ݶ������������
  {
    PowerOn_Settle_Data();//���������ݽ��㣬ǰHIS_ENERGY_ENERGY_DATA_MONTHS���µ�����  
    PowerOn_Demand_Proc(); //�ϵ�����������
    /*
    OS_Waitfor_Sec(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg, 5);//�ȴ���������׼���ã�
    if(1 != Measu_Status_Mode_ToPub_PUCK.DataRecFlg)
    {
      ASSERT_FAILED();
      OS_Waitfor(1 EQ Measu_Status_Mode_ToPub_PUCK.DataRecFlg);
    }
    */
  }
  
  return;
}

//ˢ��Ǯ���ļ�
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
    if(Mins.Var >= 60) //ÿ60����ˢ��һ��Esam
    {
      Mins.Var = 0;
      UpdataEsamMoneyBag();
    }
  }
}

//������Ƿ���԰汾
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
    
    if(Counts.Var >= (INT32U)1440*120) //120������
    {
      while(1)
      {
        Disp_Info("db 120"); 
        Clear_All_Dog();
      }
    }
  }
}

//������������
//��ʵ���˼�������������Ȼ����˵�ѹͳ�ơ��������ߡ�ʱ�Ӵ���ȹ���
void Energy_Proc()
{
  //return;
  TRACE();

  {
    Clear_Task_Dog();//��������

    Check_Meter_Debug_En(); //����Ƿ��ǵ��԰汾
    
    Clock_Proc();//ʱ�Ӵ�����ʱˢ��ʱ��
    Check_Energy_Para_Modified();//�������Ƿ����޸�

    PSW_Timer_Proc();//����������ʱ
    Prog_Timer_Proc();//��̼�ʱ

    Check_Energy_Data_Para_Avail();//��鱾�����������ݵĺϷ���
    Check_Cur_Rate();//��鵱ǰ����
    //Check_Cur_Step();//��鵱ǰ����

    Cumulative_Energy();//ÿ���ۼӵ���
    UpdataEsamMoneyBag(); //��ʱ����esam��Ǯ���ļ�
    
    VolStat_Proc();//��ѹͳ�ƴ���  
    
    Settle_Data();//ÿ���Զ��������
    Period_Save_Cur_Data();//�����Զ����浱ǰ����

    Demand_Proc();//�������ݴ���

    LoadData_Proc();//�������ߴ���
    Freeze_Proc();//��������
    Check_Clear_Data();//����Ƿ����������������

    //Prepaid_Power_Ctrl_Proc(); //Ԥ���ѵĸ��ɿ��ƴ���(������)
    Power_Ctrl_Proc();//���ɿ��ƴ���(������)
    Switch_Ctrl_Proc();//�Լ̵��������տ���
    
    Event_Cumu_Mins_Accu();
    
    //Debug_Print_Cur_Energy_Info();//����ǰ������Ϣ��������Կ�
    Print_Energy_Demand_Info();
  }
}
#undef ENERGY_TASK_C
