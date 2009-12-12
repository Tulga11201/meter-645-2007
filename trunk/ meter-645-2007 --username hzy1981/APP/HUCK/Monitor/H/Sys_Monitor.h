#ifndef SYS_MONITOR_H
#define SYS_MONITOR_H

#undef EXT
#ifdef SYS_MONITOR_C
#define EXT
#else
#define EXT extern
#endif

#define TASK_DOG_SEC 15 //每个连续15s没有喂任务狗，复位

typedef struct
{
    INT8U Counts[OS_TASK_NUM];
    INT8U CS[CS_BYTES];
}S_Task_Monitor;

EXT volatile S_Task_Monitor Task_Monitor;

EXT void Monitor_Init();
EXT void Task_Monitor_Proc();
EXT void Clear_Task_Dog();
#endif
