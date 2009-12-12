#ifndef OS_EVENT_H
#define OS_EVENT_H

#if (OS_MUTEX_EN>0) || (OS_SEM_EN>0) || (OS_MSG_EN>0) || (OS_MSG_Q_EN>0)

#undef OS_EXT
#ifndef OS_EVENT_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

#define OS_MUTEX 1
#define OS_SEM   2
#define OS_MSG   3
#define OS_MSG_Q 4

OS_EXT void OS_Event_Init();

#if OS_MUTEX_LOCK_CHK_EN>0
OS_EXT void OS_Task_Event_Init();
#endif

OS_EXT OS_INT8U OS_Check_Task_Event_Lock(OS_INT8U Task_ID);
OS_EXT void OS_Event_Check();
#endif

#endif

