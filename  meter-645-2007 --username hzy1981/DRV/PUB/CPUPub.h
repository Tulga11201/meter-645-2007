#ifndef CPU_CFG_H
#define CPU_CFG_H



#ifndef CPU_PUB_C
#define CPU_PUB_EXT  extern volatile
#else
#define CPU_PUB_EXT volatile
#endif




#define RUN_MODE        0    //CPU������Դ��ȫ������
#define HALT_MODE       1    //CPU˯��ģʽ
#define FX1_RUN_MODE    2    //CPU�ں󱸵�Դ�£���fxʱ��ȫ������
#define FXT_RUN_MODE    3    //CPU�ں󱸵�Դ�£���fxtʱ����������


INT8U  Switch_Main_Osc(INT8U  Mode);
#endif
