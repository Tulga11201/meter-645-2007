#ifndef OS_TIME_H
#define OS_TIME_H

#undef OS_EXT
#ifndef OS_TIME_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

//4个独立的延时宏,方便调用
#define OS_TimeDly_Ms(x) OS_TimeDly(0,0,0,x)
#define OS_TimeDly_Sec(x) OS_TimeDly(0,0,x,0)
#define OS_TimeDly_Min(x) OS_TimeDly(0,x,0,0)
#define OS_TimeDly_Hou(x) OS_TimeDly(x,0,0,0)

//带超时的条件等待,注意Condition中的全局变量必须是Volatile类型
#define OS_Core_Wait_HMSM(Condition,Hour,Min,Sec,m_Sec)\
do{OS_Set_Task_TimeDly(Hour,Min,Sec,m_Sec);\
   OS_Core_Wait((Condition) || OS_Check_Task_TimeDly()==0);\
   OS_Set_Task_TimeDly(0,0,0,0);\
  }while(0)

//四个独立的带超时的条件等待,方便调用,注意Condition中的全局变量必须是Volatile类型
#define OS_Core_Wait_Hou(Condition,Hou) OS_Core_Wait_HMSM(Condition,Hou,0,0,0) 
#define OS_Core_Wait_Min(Condition,Min) OS_Core_Wait_HMSM(Condition,0,Min,0,0)
#define OS_Core_Wait_Sec(Condition,Sec) OS_Core_Wait_HMSM(Condition,0,0,Sec,0)
#define OS_Core_Wait_Ms(Condition,Ms) OS_Core_Wait_HMSM(Condition,0,0,0,Ms)

OS_EXT OS_INT8U OS_Check_Sys_Tick();
OS_EXT void OS_TaskDly_Proc();
OS_EXT void OS_Set_Task_TimeDly(OS_INT16U Hour,OS_INT16U Min,OS_INT16U Sec,OS_INT16U m_Sec);
OS_EXT void OS_TimeDly(OS_INT16U Hour,OS_INT16U Min,OS_INT16U Sec,OS_INT16U m_Sec);
OS_EXT OS_INT8U OS_Check_Task_TimeDly();
#endif
