#ifndef OS_PORT_H
#define OS_PORT_H

#undef OS_EXT
#ifndef OS_PORT_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

#include "setjmp.h"

//iar ������֧��
#define CONST const       //����Flash����
#define NO_INIT __no_init //����ǳ�ʼ������

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

///!!!!!!!!!!ע�⣺����Զ�ջָ��Ĳ�����Ҫ��������ָ�����ж��ڲ�����ջָ�룬������ܳ���!!!!!!!!!!!!!!!

#define OS_Task_Env jmp_buf
#define OS_Save_Env(x) setjmp(x)
#define OS_Restore_Env(x) longjmp(x,1) 

//ʹ����Ƕ��࣬IAR�������ֲ���ȷ˵����������κ��Ż�ѡ��!
//��SP���浽Old_SP
#define SAVE_TASK_SP()  {asm("MOVW AX,SP");\
                         asm("MOVW Old_SP,AX");}

//��New_SP���浽SP
#define RESTORE_TASK_SP()  {asm("MOVW AX,New_SP");\
                            asm("MOVW SP,AX");}

OS_EXT OS_INT8U OS_Check_Tick();

#endif
