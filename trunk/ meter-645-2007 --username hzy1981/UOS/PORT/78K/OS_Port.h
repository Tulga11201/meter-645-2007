#ifndef OS_PORT_H
#define OS_PORT_H

#undef OS_EXT
#ifndef OS_PORT_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

#include "setjmp.h"

//iar 编译器支持
#define CONST const       //定义Flash变量
#define NO_INIT __no_init //定义非初始化变量

typedef unsigned long int OS_INT32U;
typedef long int OS_INT32S;
typedef unsigned int OS_INT16U;
typedef int OS_INT16S;
typedef unsigned char OS_INT8U;
typedef char OS_INT8S;
typedef unsigned long int OS_STK;
typedef unsigned long int OS_SP;
typedef unsigned char OS_BOOL;
typedef unsigned int OS_ALIGN_TYPE;

///!!!!!!!!!!注意：如果对堆栈指针的操作需要两条以上指令，请关中断在操作堆栈指针，否则可能出错!!!!!!!!!!!!!!!

#define OS_Task_Env jmp_buf
#define OS_Save_Env(x) setjmp(x)
#define OS_Restore_Env(x) longjmp(x,1) 

//使用内嵌汇编，IAR编译器手册明确说明，请勿打开任何优化选项!
//将SP保存到Old_SP
#define SAVE_TASK_SP()  {asm("MOVW AX,SP");\
                         asm("MOVW Old_SP,AX");}

//将New_SP保存到SP
#define RESTORE_TASK_SP()  {asm("MOVW AX,New_SP");\
                            asm("MOVW SP,AX");}

OS_EXT OS_INT8U OS_Check_Tick();

#endif
