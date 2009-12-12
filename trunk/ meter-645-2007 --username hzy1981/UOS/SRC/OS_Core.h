#ifndef OS_CORE_H
#define OS_CORE_H

#undef OS_EXT
#ifndef OS_CORE_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

//�����ջ�����
#define CHK_STK_BYTE (OS_INT8U)0x5A

#define OS_TASK_WAITING 0x00//�ȴ�״̬
#define OS_TASK_SUSPEND 0x11//����״̬
#define OS_TASK_RUNNING 0x22//����״̬

//��������λ������
#define OS_SET_BIT(x,y) ((x)|=0x01<<(y))
#define OS_CLR_BIT(x,y) ((x)&=~(0x01<<(y)))
#define OS_GET_BIT(x,y) (((x)>>(y))&0x01)

#define CODE_LICENSE_OK (OS_INT32U)0xAAAA5555
#define CODE_LICENSE_ERR (OS_INT32U)0x00000000

//�����ȴ�,ע��Condition�е�ȫ�ֱ���������Volatile����
#define OS_Core_Wait(Condition)\
do{ while(!(Condition))\
      OS_Task_Switch_Proc();\
  }while(0)

OS_EXT void OS_Init();
OS_EXT void OS_Change_Cur_Task_ID();
OS_EXT void OS_Task_Switch_Proc();
OS_EXT OS_INT8U OS_Create_Task(void(*pEntry)(),OS_STK *pStk,OS_INT16U Stk_Size,OS_INT8U Name[]);
OS_EXT void OS_Task_Suspend(OS_INT8U Task_ID);
OS_EXT void OS_Task_Unsuspend(OS_INT8U Task_ID);
OS_EXT void OS_Start();

#if OS_TICK_ISR_EN>0
OS_EXT void OS_Tick_ISR();//����ʱ���жϷ���
#endif

#endif
