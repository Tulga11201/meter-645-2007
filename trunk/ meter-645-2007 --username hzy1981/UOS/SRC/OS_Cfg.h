#ifndef OS_CFG_H
#define OS_CFG_H

#define OS_TASK_NUM       3 //����������,����ܳ���32
#define OS_EVENT_NUM      6 //����¼�����
//ע�⣺��ϵͳ���֧��32�������16���¼�,�����Ҫ֧�ָ����������Ҫ�޸�OS_Core.h�ļ��е�Tcb��OS_Event�еı���

#define OS_TICK_ISR_EN    1 //0��ʾʹ��OS_Check_Tick()��ѯ��ʱ���ķ�ʽ����ʱ����1��ʾʹ���ж�OS_Tick_ISR����ʱ��
#define OS_TICK_HOOK_EN   0 //Tick����ʹ��
#define OS_MS_PER_TICK    10 //ÿ��Tick�������ms

#define OS_TASK_NAME_EN   1 //0��ʾ�������������ֹ���,1��ʾ����
#define OS_TASK_NAME_SIZE 10 //�������ִ�С

#define OS_TASK_SWITCH_HOOK_EN 0

#define OS_TASK_SUSPEND_EN 0 //���������

#define OS_CS_EN      1 //����ϵͳ�Ƿ�����ڴ����CSУ��
#define OS_CS_BYTES       1 //У��ʹ�С
#define OS_CS_TYPE        CS_CRC16_1//���ú�У�鷽ʽ,�������ַ�ʽCS_SUM��CS_CRC16_0��CS_CRC16_1

#define OS_STK_GROWTH     1 //���ö�ջ��������1��ʾ�ɸߵ�ַ��͵�ַ�ݼ���0�෴

#define OS_TRACE_EN       0
#define OS_TRACE_CTRL_EN  1 //������ԵĿ��ع��ܣ�1��ʾ�����ء�0��ʾ�������أ�һֱ��
                              //�����Ҫ��ȡ�쳣��λǰ�ĵ���������Ϣ����Ҫ�ڸ�λ�����Ϲرն��ԡ�Ȼ���ڳ�ʼ��
                              //���Դ��ں����ϵ���OS_ASSERT_FAILED()���
#define OS_TRACE_NUM       1 //���Ժ������ٵĸ���
#define OS_TRACE_BUF_LEN   10 //ÿ�����Լ�¼���ݳ���
#define OS_TRACE_HOOK_EN    0 //���Ժ������Ƿ������Ӻ�����1��ʾ����

#define OS_ASSERT_EN      1 //1��ʾ���Թ��ܿ�����0��ʾ�ر�
#define OS_ASSERT_HOOK_EN 1

#define OS_MUTEX_EN      1  //ʹ�û����ź���
#define OS_MUTEX_LOCK_CHK_EN      1 //1��ʾ֧���¼�������飬0��ʾ��֧��,ֻ�л������ź������д˹���
#define OS_MUTEX_WAIT_WARN_TIME   1 //�����ź�����ʱʱ�䣬������ʱ����Ȼ���벻����������������,��λΪs

#define OS_MSG_EN        0  //ʹ����Ϣ
#define OS_MSG_WAIT_WARN_TIME 1 //��Ϣ�ȴ���ʱ����ʱ�䣬��λΪs

#define OS_MSG_Q_EN      0 //ʹ����Ϣ����
#define OS_MSG_Q_WAIT_WARN_TIME 1//��Ϣ���еȴ���ʱ����ʱ�䣬��λΪs

#define OS_SEM_EN        0  //ʹ����ͨ�ź���
#define OS_SEM_WAIT_WARN_TIME 1 //�ź����ȴ���ʱ����ʱ�䣬��λs

#define OS_MEM_EN        0  //ʹ�ö�̬�ڴ����
#define OS_MEM_WAIT_WARN_TIME 1 //���뵽���ڴ����ʹ��ʱ�䵥λΪs

#define OS_SHELL_EN      1

#if OS_MEM_EN>0 //���嶯̬�ڴ��ÿ��Block�Ĵ�С
/*
#define MEM_BLOCK2_SIZE 200
#define MEM_BLOCK1_SIZE 400

#define MEM_BLOCK3_SIZE 600
#define MEM_BLOCK4_SIZE 800
#define MEM_BLOCK5_SIZE 1000
#define MEM_BLOCK6_SIZE 1200
#define MEM_BLOCK7_SIZE 1400
#define MEM_BLOCK8_SIZE 1600
#define MEM_BLOCK9_SIZE 1800
#define MEM_BLOCK10_SIZE 2000
#define MEM_BLOCK11_SIZE 2000
#define MEM_BLOCK12_SIZE 2000
#define MEM_BLOCK13_SIZE 2000
#define MEM_BLOCK14_SIZE 2000
#define MEM_BLOCK15_SIZE 2000
#define MEM_BLOCK16_SIZE 2000
#define MEM_BLOCK17_SIZE 2000
#define MEM_BLOCK18_SIZE 2000
#define MEM_BLOCK19_SIZE 2000
#define MEM_BLOCK20_SIZE 2000
#define MEM_BLOCK21_SIZE 2000
#define MEM_BLOCK22_SIZE 2000
#define MEM_BLOCK23_SIZE 2000
#define MEM_BLOCK24_SIZE 2000
#define MEM_BLOCK25_SIZE 2000
#define MEM_BLOCK26_SIZE 2000
#define MEM_BLOCK27_SIZE 2000
#define MEM_BLOCK28_SIZE 2000
#define MEM_BLOCK29_SIZE 2000
#define MEM_BLOCK30_SIZE 2000
*/
#endif

//#define OS_VERSION 106 //2008.03.29
//#define OS_VERSION 107 //2008.04.08
//#define OS_VERSION 108 //2008.04.19
//#define OS_VERSION 109 //2008.05.06
//#define OS_VERSION 110 //2008.06.12
//#define OS_VERSION 111 //2008.06.29
//#define OS_VERSION 112 //2008.07.25
//#define OS_VERSION 113 //2008.09.28
//#define OS_VERSION 114 //2008.10.12
//#define OS_VERSION 115 //2008.10.16
//#define OS_VERSION 116 //2008.10.23
//#define OS_VERSION 117 //2008.10.25

//#define OS_VERSION 118 
//2008.11.02 �������ź����������ķ����ͱ���,ͬʱ��ʱ��ģ�������OS_Time.c��OS_Time.h�����ļ�
//2008.11.03 �޸����ź������뺯���е�һ��bug(û��д����У����).

//#define OS_VERSION 119
//2008.11.04 �����˻����ź������ź�������Ϣ����

//#define OS_VERSION 120
//2008.11.05 ��������Ϣ�����еĵȴ���ϢΪ�պ��޵ȴ�������Ϣ��������

//#define OS_VERSION 121
//2008.11.13 �����˴�Head��Tail�Ľ�������Ͷ���

//#define OS_VERSION 122
//2008.11.14 �޸Ĵ�ӡ����������id�������������͵�

//#define OS_VERSION 123081123
//���Ӷ�̬�ڴ����ͬʱ������OS_Eventģ�飬�޸Ĳ��ֺ�

//#define OS_VERSION 124081124
//���Ʋ���ϸ��

//#define OS_VERSION 125081127
//���Ʋ���ϸ��

//#define OS_VERSION 126081209
//������Ϣ���й���

//#define OS_VERSION 127081211
//ȥ�����Եķ���ֵ����,���ӹ淶���Ե��÷����������ö��Եķ���ֵ

//#define OS_VERSION 128081211
//������Ԥ�ȶ��嶯̬�ڴ���С�ĺ�

//#define OS_VERSION 129081214
//�����˶�����Ϣ������Ϣ��ĺ�

//#define OS_VERSION 130081217
//�޸�����Ϣ������Ϣ��겻����VC�±���ͨ��������

//#define OS_VERSION 132081221
//����CRCУ���㷨

//#define OS_VERSION 133081222
//��CRC��������ŵ������ⲿ,��ֹռ�ö�ջ�ռ�

//#define OS_VERSION 134081224
//У����㷨����һ���볣�������,��ֹ����ȫΪ0�������У��ҲΪ0.�ͷ��ڴ�ʱ�����ڴ�����.

//#define OS_VERSION 135090204
//OS_Pub.c�еĶ��Ժ���������������������²Ž���
//�����˶����ڴ��ͷβ����
//�޸��˲��ֱ����ͺ���

//#define OS_VERSION 136090314
//�޸Ķ���Ϊ��¼�ļ������к���Ϊ�켣
//����ͷβ��������ĺ�

//#define OS_VERSION 138090323
//�����񻷾��л�����ŵ�OS_Port��

//#define OS_VERSION 139090408
//�������켣���ٹ��ܶ�������

//#define OS_VERSION 140090408
//�������켣���ٹ��ܶ�������--һЩ�Ľ�

//#define OS_VERSION 141090409
//һЩС�Ľ�

//#define OS_VERSION 142090415
//���Ӻ�OS_ASSERT_FAILED()���滻OS_ASSERT(0)���ɽ�ʡ����ռ�

//#define OS_VERSION 143090417
//�޸���Ϣ���ͺ������Լ�����ϵͳ�ĸ��������Ϣ�������

#define OS_VERSION 145090824
//��������Ĺ�����
#endif
