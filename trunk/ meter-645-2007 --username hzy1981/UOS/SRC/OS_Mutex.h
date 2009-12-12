#ifndef OS_MUTEX_H
#define OS_MUTEX_H

#if OS_MUTEX_EN>0

#undef OS_EXT
#ifndef OS_MUTEX_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

OS_EXT OS_INT8U OS_Mutex_Init(OS_INT8U ID,OS_INT8U Val);
OS_EXT OS_INT8U OS_Mutex_Post(OS_INT8U ID);
OS_EXT OS_INT8U OS_Mutex_Pend(OS_INT8U ID);
OS_EXT void OS_Mutex_Info_Print();
#endif

#endif

