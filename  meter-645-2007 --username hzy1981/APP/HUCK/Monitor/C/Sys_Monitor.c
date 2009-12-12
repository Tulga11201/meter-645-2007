#define SYS_MONITOR_C
#include "Includes.h"

void Monitor_Init()
{
  mem_set((void *) &Task_Monitor, 0, sizeof(Task_Monitor), (void *) &Task_Monitor, sizeof(Task_Monitor));
  SET_STRUCT_SUM(Task_Monitor);
}

//������,�ǵ���OS_Tick_Task������ҲҪ�幷
void Clear_Task_Dog()
{
  INT8U Re, Cur_Task_ID;

  //Re = CHECK_STRUCT_VAR(Task_Info);
  //ASSERT(1 == Re);

  Cur_Task_ID = OS_Get_Cur_Task_ID();
  if(Cur_Task_ID >= OS_TASK_NUM)
  {
    ASSERT_FAILED();
    return;
  }

  Re = CHECK_STRUCT_SUM(Task_Monitor);
  if(1 != Re)//ASSERT(1 == Re))
  {
    ASSERT_FAILED();
    return;
  }

  Task_Monitor.Counts[Cur_Task_ID] = 0;
  SET_STRUCT_SUM(Task_Monitor);
}

//�����ش���
void Task_Monitor_Proc()
{
  static S_Int32U Sec_Bak = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};
  static S_Int8U Counts = {CHK_BYTE, 0, CHK_BYTE};  
  INT8U i, Task_Num, Re;

  //ÿ���ӲŽ���һ�����������
  if(Sec_Bak.Var != Sec_Timer_Pub)
  {
    Re = 1;
    Re &= CHECK_STRUCT_VAR(Counts);
    Re &= CHECK_STRUCT_VAR(Sec_Bak);
    if(Re EQ 0)
      ASSERT_FAILED();
    
    Counts.Var ++;
    if(Counts.Var >= 60)//ÿ���Ӵ�ӡһ�ζ�ջ��ʹ�����
    {
      Counts.Var = 0;
      OS_Task_Info_Print();
    }

    Sec_Bak.Var = Sec_Timer_Pub;

    Task_Num = OS_Get_Cur_Task_Num();
    for(i = 0; i < OS_TASK_NUM && i < Task_Num; i++)
    {
      //����û��˯�߶��� ����ļ������������Ϊ��ʱ
      if(Task_Monitor.Counts[i] > TASK_DOG_SEC)
      {
        //ĳ�����Ѿ�˯����,�ҵ�ǰ�����ڵ�Դ����״̬��,���ô������������
        if(Check_Task_Sleep(i) == 1 && Check_Sys_Status() != SYS_NORMAL)
        {
          Task_Monitor.Counts[i] = 0;
        }
        else
        {
          Debug_Print("Task %d, Name:%s dog overflowed", i, OS_Get_Task_Name(i));
          Soft_Reset();
        }
      }
      Task_Monitor.Counts[i]++;
    }
    SET_STRUCT_SUM(Task_Monitor);
  }
}
#undef MONITOR_C
