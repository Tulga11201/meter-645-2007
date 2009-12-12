#define LOW_POWER_C
#include "Includes.h"

//����Դ״̬������1
INT8U Check_Power_Status()
{
  TRACE();
  if(JUDGE_POWER_OFF)
  {
    return POWER_DOWN_STATUS;
  }
  else
  {
    return POWER_ON_STATUS;
  }
}

void Soft_Restart()
{
  Debug_Print("----Power_Down!Soft Reset!----");
  Soft_Reset();
}

//�����жϴ�����
void Power_Down_Proc()
{
  PwrCtrl_ExtDevice_HigSpeed();
  //Set_Sys_Status(SYS_SLEEP);
  //����ϵͳ״̬����Ҫ����Set_Sys_Status()��ӡ������Ϣ 
  Power_Down_Int_Proc();
  //Save_PD_Data();
  //Soft_Reset();
}

//�����жϴ�����
void Power_Down_Int_Proc()
{
  Trace_Info.Entry_Flag = 0;//��ֹ���뱨��

  Sys_Status.Last_Status = Sys_Status.Status;//�ȱ����ϴ�״̬
  Sys_Status.Status = SYS_SLEEP;
  SET_SYS_STATUS_SUM();

  JMP_PD_PROC();
  /*    
    if(CHECK_SYS_STATUS_SUM())//У�����ȷ
    {
    if(SYS_NORMAL!=Sys_Status.Status)//��ǰ��Ȼ������״̬
    ASSERT_FAILED();
    //{
    Sys_Status.Last_Status=Sys_Status.Status;//�ȱ����ϴ�״̬
    Sys_Status.Status=SYS_SLEEP;
    SET_SYS_STATUS_SUM();
    
    JMP_PD_PROC();
    //}
    //else
    
    //else ��ǰ�����ڵ�Դ��������£�˵��Ŀǰ�ǻ���״̬��
    }
    else//У��Ͳ���ȷ������£���Ϊ˯��״̬����λ
    {
    Sys_Status.Last_Status=Sys_Status.Status;//�ȱ����ϴ�״̬
    Sys_Status.Status=SYS_SLEEP;
    SET_SYS_STATUS_SUM();
    Soft_Restart();    
    }  
  */
}

//�����⺯��
#if 1
void Power_Down_Check()
{
  static S_Int8U PD_Flag={CHK_BYTE,0,CHK_BYTE};
  static volatile S_Int32U Ms_Timer={CHK_BYTE,0,CHK_BYTE};
  //INT32U Temp;
  
  if(CHECK_STRUCT_VAR(PD_Flag) EQ 0)
  ASSERT_FAILED();
  
  if(0x55 EQ PD_Flag.Var)//0x55��ʾ���������� 
  return;//ASSERT_FAILED();
  
  PD_Flag.Var=0x55;
  //�����˶��ҵ�ǰ������״̬�Ž��е����⴦��
  if(Check_Power_Status()!=POWER_ON_STATUS)
  {
    if(CHECK_SYS_STATUS_SUM())//У�����ȷ
    {
      if(SYS_NORMAL EQ Sys_Status.Status)//��ǰ��Ȼ������״̬
      {
        Sys_Status.Last_Status=Sys_Status.Status;//�ȱ����ϴ�״̬
        Sys_Status.Status=SYS_SLEEP;
        SET_SYS_STATUS_SUM();
        JMP_PD_PROC();
        //Save_PD_Data();
        //Soft_Restart();
      }
  //else ��ǰ�����ڵ�Դ��������£�˵��Ŀǰ�ǻ���״̬��
    }
    else//У��Ͳ���ȷ������£���Ϊ˯��״̬����λ
    {
      Sys_Status.Last_Status=Sys_Status.Status;//�ȱ����ϴ�״̬
      Sys_Status.Status=SYS_SLEEP;
      SET_SYS_STATUS_SUM();
      Soft_Restart();    
    }
  }
  //�����������μ�����֮���ʱ����
  /*
  do {Temp=Ms_Timer_Pub;}while(Temp!=Ms_Timer_Pub);
  if(Ms_Timer.Var<Temp)
  {
   if(Temp-Ms_Timer.Var>PD_Chk_Ms.Var)
   PD_Chk_Ms.Var=Temp-Ms_Timer.Var;
  }
  Ms_Timer.Var=Temp;
  */
  PD_Flag.Var=0;
}
#endif

//��ȡϵͳ��ʼ����־��������������ʼ�������з���MAIN_INITING;���򷵻�0
INT32U Get_Main_Init_Flag()
{
  INT8U Re;
  
  Re = CHECK_STRUCT_VAR(Main_Init_Flag);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    INIT_STRUCT_VAR(Main_Init_Flag);
    Main_Init_Flag.Var = 0;
  }
  
  return Main_Init_Flag.Var;
}

//����ϵͳ�������ʼ����־
void Set_Main_Init_Flag()
{
  Main_Init_Flag.Var = MAIN_INITING;
}

//����������ʼ����־
void Clr_Main_Init_Flag()
{
  Main_Init_Flag.Var = 0; 
}

//д��������
void Save_PD_Data()
{
  INT32U Temp_Timer;

  TRACE();
  //OS_Debug_Print("\r\n----------Save_PD_Data Start----------");
  Ms_Timer_Pub = 0;
  if(Get_Main_Init_Flag() EQ MAIN_INITING)
  {
    Debug_Print("Main Initing....save no PD data"); 
    return;
  }
  
  //OS_CLR_BIT(OS_Sem.Sem,PUB_RW_ROM_ID);//ǿ���ͷŶ�д�洢�����ź���
  //SET_STRUCT_SUM(OS_Sem);
  //OS_Event[PUB_RW_ROM_ID].Value = 1;
  OS_Mutex_Init(PUB_RW_ROM_ID, 1);
  
  Save_Cur_Energy_PD_Data();//��������
  Save_Cur_Demand_PD_Data();//��������
  Save_Cur_VolStat_PD_Data();//��ѹͳ������
  Save_LoadData_PD_Data();
  Save_Event_PD_Data();//�����¼�����
  //Save_PD_Time();//�������ʱ��
  
  STOP_1MS;  
  Temp_Timer=Ms_Timer_Pub;
  START_1MS;
  
  Write_Storage_Data(_SDI_SAVE_PD_DATA_TIME,(void *)&Temp_Timer,4);
  Init_DebugChanel_PUCK(0);//��ʼ�����Դ��ڣ������ж�����״̬
  _OS_Debug_Print("\r\n--------Save_PD_Data End,Time:%ld ms----------",Ms_Timer_Pub);
}

//����ĳ��������˵����ĵ͹������̣���������:
//ͨ������Check_Sys_Status()���û�õ�ǰ��״̬ 
//SYS_NORMAL��ʾ����״̬,�õ���״̬,������������
//SYS_RESUME��ʾ����״̬,�õ���״̬,������������,ͨ������Get_Resume_Source()��û���Դ
//  ���ݲ�ͬ�Ļ���Դִ�в�ͬ�Ĳ�����ִ��������Task_Sleep()����˯��
//����Ļ���Դ�����Ե���Get_Resume_Source()���
//Get_Resume_Source()�ķ�����:
//�������:
//IRAD_RESUME     0x01//���⻽��
//KEY_RESUME  0x02//��������
//ALL_LOSS_VOL_RESUME 0x04//ȫʧѹ����
//BATON_RESUME    0x10//����ϵ�

//ע��:
//�ϵ�󣬶�ȡCheck_Sys_Status(),ϵͳ���ܴ�������״̬:Ӧ�ø���������״̬���в�ͬ��ʼ��
//a SYS_SLEEP״̬����ʾ�����˵��磬������״̬��λ������������Ӧ������ƺ���Ȼ��Task_Sleep()˯��
//
//b SYS_NORMAL״̬����ʾ�ⲿ��Դ�����������������ߡ�������������¼�������ϵͳ״̬ΪSYS_SLEEP״̬
//       �����Ͻ��������λ
//      
//c SYS_RESUME״̬������״̬����ʾû���ⲿ��Դ���õ���ϵ��״̬,��ʱ��ȡ����ԴΪBATON_RESUME
//
//
//
//
//
//��ʼ������״̬Ϊ��˯��״̬
void Init_Task_Status()
{
  TRACE();

  mem_set((void *) &Task_Status, 0, sizeof(Task_Status), (void *) &Task_Status, sizeof(Task_Status));
  INIT_STRUCT_VAR(Task_Status);
  SET_STRUCT_SUM(Task_Status);
}

//��ʼ������Դ
void Init_Resume_Source()
{
  TRACE();

  Resume_Src.Src_Flag = 0;
  //mem_set((void *)&Resume_Src,0,sizeof(Resume_Src),(void *)&Resume_Src,sizeof(Resume_Src));
  INIT_STRUCT_VAR(Resume_Src);
  //SET_STRUCT_SUM(Resume_Src);  
}

//���ϵͳ״̬�ĺϷ���,�˺���Ҫ��Sys_Status_Proc��������֮����ܹ�����
void Check_Sys_Status_Avail()
{
  //TRACE();
  Check_Sys_Status();
}

INT8U Get_Power_Status()
{
  INT8U i;

  TRACE();

  for(i = 0; i < 20; i++)
  {
    if(Check_Power_Status() != POWER_ON_STATUS)//��ѹ���������
      break;
    OS_TimeDly_Ms(20);
  }
  //����400ms�ж���ѹ���ȶ���
  if(i EQ 20)
  {
    return POWER_ON_STATUS;
  }
  else
  {
    return POWER_DOWN_STATUS;
  }
}

//��ȡϵͳ��ǰ��״̬,�����ϵ緵��SYS_NULL
INT32U Get_Sys_Status()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sys_Status);
  Re &= CHECK_SYS_STATUS_SUM();
  if(1 EQ Re && (SYS_NORMAL EQ Sys_Status.Status || \
   SYS_SLEEP EQ Sys_Status.Status || \
   SYS_RESUME EQ Sys_Status.Status))
  {
    return Sys_Status.Status;
  }
  else//��У��ͻ���ϵͳ״̬����ȷ������£���Ҫֱ�Ӳ�ѯ����io�ڵ�ƽ

  if(Check_Power_Status() EQ POWER_ON_STATUS)
  {
    Sys_Status.Status = SYS_NORMAL;
    SET_SYS_STATUS_SUM();
    return SYS_NORMAL;
  }
  else//ʹ�õ�س����ϵ�,����Ϊ����״̬����Ϊ�ǵ���ϵ�
  {
    Sys_Status.Status = SYS_RESUME;
    SET_SYS_STATUS_SUM();
    return SYS_RESUME;
  }
}

//��ȡϵͳ��ǰ��״̬
INT32U Get_Sys_Last_Status()
{
  INT8U Re;

  TRACE();

  Re = CHECK_SYS_STATUS_SUM();
  if(1 EQ Re && (SYS_NORMAL EQ Sys_Status.Last_Status || \
   SYS_SLEEP EQ Sys_Status.Last_Status || \
   SYS_RESUME EQ Sys_Status.Last_Status))
  {
    return Sys_Status.Last_Status;
  }
  else
  {
    Sys_Status.Last_Status = SYS_NULL;
    return SYS_NULL;
  }
}

//�ú�����ͬ��Get_Sys_Status
INT32U Check_Sys_Status()
{
  return Get_Sys_Status();
}

//���û���Դ
void Set_Resume_Source(INT8U Src)
{
  Resume_Src.Src_Flag |= Src;
}

//�ж�ĳ��Դ�Ƿ����ж�Դ,SrcΪ�ж�Դ����
//��ĳ���ж�Դ����ȡ����Ϊ�������룬���жϸ�Դ���������Դ�Ƿ���һ���ǵ�ǰ�ж�Դ
INT8U Check_Resume_Source(INT8U Src)
{
  if((Resume_Src.Src_Flag & Src) != 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
//����ϵͳ��ǰ��״̬
void Set_Sys_Status(INT32U Status)
{
  TRACE();

  if(SYS_SLEEP EQ Status)
  {
    Debug_Print("..........System Sleep..........");
  }
  else if(SYS_RESUME EQ Status)
  {
    Debug_Print("..........System Resume..........");
  }
  else if(SYS_NORMAL EQ Status)
  {
    Debug_Print("..........System Normal..........");
  }

  Sys_Status.Status = Status;
  SET_SYS_STATUS_SUM();

  if(SYS_RESUME EQ Status || SYS_NORMAL EQ Status)
  {
    Init_CPU_PUCK(Status);
    Init_ExtDevice_PUCK(Status);
  }
  else if(SYS_SLEEP EQ Status)
  {
    Init_ExtDevice_PUCK(Status);//�ر��ⲿ�豸
    Init_CPU_PUCK(Status);//�ر��ڲ��豸����CPU����˯��״̬,�廽��Դ����Ҳ�ڸú�����ִ��
  }
}

//�ȴ���������˯��,Ms����
void Wait_Tasks_Sleep(INT32U Ms)
{
  INT32U Counts;

  TRACE();

  Counts = 0;
  while(1)//��ʱ�������Ѿ�����,�ȴ�����������ɻ��Ѵ������̺����˯��
  {
    if(Check_Tasks_Sleep_Done() || Counts >= Ms)//�������˯�߻���˯�ߴ�����̳�ʱ
      break;

    Task_Monitor_Proc();//��������ִ��

    Clear_Task_Dog();   //�������Ź�,�͹���ģʽ�²�Ҫ���ⲿ���Ź�
    Clear_CPU_Dog();  //��CPU�ڲ����Ź�

    OS_TimeDly_Ms(100);
    Counts += 100;
  }

  if(Counts >= Ms)
  {
    Debug_Print("Wait_Tasks_Sleep TimeOut");
  }
}

void Init_Low_Power_Ram()
{
  TRACE();

  PD_INT_EN_Flag = 1;//��ʼ��ʱ�����ж�ʱ�򿪵�
  Resume_Src.Src_Flag = 0;
  INIT_STRUCT_VAR(Resume_Src);
}

/*
//������������ĵ����뻽�Ѵ�������
if(Get_Sys_Status() EQ SYS_SLEEP)//�����˵��磬���˯��ǰ���ƺ���
{
  ����ƺ���;
  Task_Sleep();//������˯��,Ȼ����������CPU˯��,����л��ѣ��������Ӹú������ؼ���ִ�� 
  ;�˴������񱻻��ѣ����ڴ˴�ֱ�ӽ��л�����ز���,Ҳ�ɰ�����������ж��Ƿ񱻻���
}

if(Get_Sys_Status() EQ SYS_RESUME)//�������ˣ���ɻ�����صĹ���
{
  ��ɻ�����ز���;
  Task_Sleep();//������˯��,�ȴ����������,����л��ѣ��������Ӹú������ؼ���ִ��
}
*/
//�ġ���ʼ�����̲��������⴦���������ݵ�����ͣ���ϵ�״̬��Ӧ�ö�������
void Init_Low_Power_Proc()
{
  INT32U Status;

  TRACE();

  Init_Task_Status();//������������Ϊ��˯��״̬��˯��״ֻ̬���ڵ͹�����Task_Sleep
  Init_Resume_Source();//��ʼ������Դ 

  if(Get_Power_Status() EQ POWER_ON_STATUS)//��ѹ���������,����ϵͳ״̬Ϊ����
  {
    INIT_STRUCT_VAR(Sys_Status);
    Sys_Status.Status = SYS_NORMAL;
    SET_SYS_STATUS_SUM();
  }

  Status = Check_Sys_Status();
  if(SYS_NORMAL EQ Status && Get_Power_Status() EQ POWER_ON_STATUS)//��ǰ��Դ����
  {
    //���õ�ǰ״̬Ϊ����״̬,ͬʱ�ϴε�״̬���Ա�����Last_Status��  
    //����ͨ������Get_Sys_Last_Status()���
    Set_Sys_Status(SYS_NORMAL);
    Init_Clock(SYS_NORMAL);
  }
  else
  {
    Set_Sys_Status(SYS_RESUME);//����ϵͳ״̬Ϊ˯��̬
    Init_Clock(SYS_RESUME);//��ػ��ѵ��������Ҫ��ʼ����ʱ��

    //HUCK����,����ϵͳ״̬Ϊ˯��״̬,�жϻ��ѳ����ͨ����ѯGet_Sys_Status֪����ǰ�Ǵ����߻��������ϵ�����»��ѵ�
    Set_Sys_Status(SYS_SLEEP);//����ϵͳ״̬Ϊ˯��̬
    Set_Sys_Status(SYS_RESUME);//����ϵͳ״̬Ϊ˯��̬
  }
}

//����˯��
void Task_Sleep()
{
  INT8U Re, Cur_Task_ID;

  TRACE();

  Re = CHECK_STRUCT_SUM(Task_Status);
  if(1 != Re)
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  //Check_Task_Para();//����������
  Cur_Task_ID = OS_Get_Cur_Task_ID();  
  SET_BIT(Task_Status.Sleep_Flag, Cur_Task_ID);
  SET_STRUCT_SUM(Task_Status);
  OS_Waitfor(GET_BIT(Task_Status.Sleep_Flag, Cur_Task_ID) EQ 0);//�ȴ�����
}

//��������˯�ߵ�����
void Resume_Tasks()
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Task_Status);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  mem_set((void *) &Task_Status, 0, sizeof(Task_Status), (void *) &Task_Status, sizeof(Task_Status));
  SET_STRUCT_SUM(Task_Status);
}

//�ж������ΪTask_ID�������״̬�Ƿ�˯�� 
//����1��ʾ�Ѿ�˯��,0��ʾ��û��˯��
INT8U Check_Task_Sleep(INT8U Task_ID)
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Task_Status);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }  

  if(GET_BIT(Task_Status.Sleep_Flag, Task_ID) EQ 0)//��i������û��˯��
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//������������Ƿ��Ѿ���˯��,1��ʾ���˱����������ⶼ�Ѿ�˯��,0��ʾ�����Լ���������û��˯��
//�ú����ṩ������������
INT8U Check_Tasks_Sleep_Done()
{
  INT8U Re;
  INT8U i, Cur_Task_ID, Cur_Task_Num;

  TRACE();

  Re = CHECK_STRUCT_SUM(Task_Status);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Cur_Task_ID = OS_Get_Cur_Task_ID();
  Cur_Task_Num = OS_Get_Cur_Task_Num();  
  for(i = 0; i < Cur_Task_Num; i++)//����ǰ������������������Ѿ�˯��?
  {
    if(i != Cur_Task_ID)//��ǰ�����Ǽ�����񣬲��ж�
    {
      if(GET_BIT(Task_Status.Sleep_Flag, i) EQ 0)//��i������û��˯��
      {
        return 0;
      }
    }
  }
  return 1;//���������Ѿ�˯����
}

//����������ĵ����뻽�Ѵ�������
void Low_Power_Proc()
{
  TRACE();

  if(Check_Power_Status() EQ POWER_DOWN_STATUS)//�ú�����PUCK����suck�ײ㺯����ɣ���ѯ��ʽ��ӦΪ����㺯��
  {
    while(1)//��While(1)�����˳���ֻ��CPU��λ�����˳���ѭ��
    {
      //��ǰ���ж�Դֻ��ȫʧѹ�����˯��,����Ӧ�û��Ѹ�����ִ��
      Set_Sys_Status(SYS_RESUME);//HUCK����,����ϵͳ״̬Ϊ����״̬,���������ͨ��Get_Sys_Status()�����õ���ǰ״̬   
      Resume_Tasks();//HUCK���,���Ѹ���������
      Wait_Tasks_Sleep(300000);//���ȴ�300s
      Set_Sys_Status(SYS_SLEEP);//����ϵͳ״̬Ϊ˯��̬
    }
  }
}

//���͹�����������Ƿ�Ϸ�
void Check_Low_Power_Data_Avail()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sys_Status);
  Re &= CHECK_SYS_STATUS_SUM();
  //ASSERT(1 EQ Re);

  //Re = 1;
  Re &= CHECK_STRUCT_VAR(Task_Status);
  Re &= CHECK_STRUCT_SUM(Task_Status);
  //ASSERT(1 EQ Re);

  //Re = 1;
  Re &= CHECK_STRUCT_VAR(Resume_Src);
  ASSERT(1 EQ Re);
}

//��ʼ��ϵͳ״̬������ͷ��β
void Init_Sys_Status()
{
  TRACE();

  INIT_STRUCT_VAR(Sys_Status);
}
#undef LOW_POWER_C