#ifndef LOW_POWER_H
#define LOW_POWER_H

#undef EXT
#ifdef LOW_POWER_C
#define EXT
#else
#define EXT extern
#endif

#define POWER_ON_STATUS   0x55
#define POWER_DOWN_STATUS 0xAA

#define MAIN_INITING      0x5AAAA55A
#define MAIN_INITED       0

//#define MAIN_INIT_END     do{Main_Init_Flag.Var=MAIN_INITED;}while(0)

//һ���������뺯��
//�����жϻ���Դ,ÿ����ռһ��λ
#define IRAD_RESUME   0x01//���⻽��
#define KEY_RESUME    0x02//��������
#define ALL_LOSS_VOL_RESUME 0x04//ȫʧѹ����
//#define POWERON_RESUME  0x08//�ⲿ��Դ�ϵ�
//#define BATON_RESUME    0x10//����ϵ�
#define RTC_RESUME    0x20//���廽��
#define LASER_RESUME  0x40//���⻽��
#define ALL_RESUME    0x7F//���л���Դ����

//����ϵͳ״̬
#define SYS_NORMAL    0x55aa55aa//����״̬,���ⲿ��Դ����
#define SYS_SLEEP     0xaa55aa55//˯��״̬,��ع���
#define SYS_RESUME    0xa5a5a5a5//����״̬,��ع���,���жϻ���Դ
//#define SYS_NORMAL_TO_SLEEP 0x5a5a5a5a//������˯�ߵĹ���״̬������Ϊ�����˵���
//#define SYS_RESUME_TO_SLEEP 0x5555aaaa//���ѵ�˯�ߵĹ���״̬����Ϊ���Ѻ���ع����Ѿ���ɣ���˽���˯��
#define SYS_NULL    0x00FF00FF//���岻�洢�ڵ�ϵͳ״̬,������Ϊ���ⲿ��Դû�磬���Ҳû���״̬
// 
#define RESUME_SEC_COUNTS 120

#define PD_DATA_PROC() if(setjmp(PD_Proc_Env.Buf))\
       { Save_PD_Data();\
       Soft_Restart();}\
       else\
       { INIT_STRUCT_VAR(PD_Proc_Env);\
       SET_STRUCT_SUM(PD_Proc_Env);}

#define JMP_PD_PROC()   if(CHECK_STRUCT_VAR(PD_Proc_Env) && CHECK_STRUCT_SUM(PD_Proc_Env))\
        longjmp(PD_Proc_Env.Buf,1);\
      else\
      { Debug_Print("PD_Proc_Env sum error!");\
        Save_PD_Data();\
        Soft_Restart();}

//����ϵͳ״̬
typedef struct
{
    INT8U Head;
    INT32U Status;//ϵͳ״̬SYS_NORMAL��SYS_SLEEP��SYS_RESUME��
    INT32U Last_Status;//�ϴε�ϵͳ״̬
    //INT16U Resume_Sec_Counts;//���ѵ�ʱ�����
    OS_INT32U CS;
    INT8U Tail;
}S_Sys_Status;

//��������˯�߱�־
typedef struct
{
    INT8U Head;
    INT32U Sleep_Flag;//����˯�߱�־��ÿλ��ʾһ�����񣬵�0λ��ʾIDΪ0������,��ֵΪ1��ʾ�Ѿ�˯�ߣ�0��ʾ����״̬
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_Task_Status;

//���廽���ж�Դ���־
typedef struct
{
    INT8U Head;
    INT8U Src_Flag;//�ж�Դ��־��ÿλ����һ���ж�Դ
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_Resume_Src;

typedef struct
{
    INT32U Head;
    jmp_buf Buf;
    INT8U CS[CS_BYTES];
    INT32U Tail;
}S_PD_Proc_Env;

EXT S_PD_Proc_Env PD_Proc_Env;
EXT volatile S_Task_Status Task_Status;
EXT NO_INIT volatile S_Sys_Status Sys_Status;
EXT volatile S_Resume_Src Resume_Src;
EXT volatile INT8U Resume_Time_Flag;

#ifdef LOW_POWER_C
EXT volatile S_Int32U Main_Init_Flag={CHK_BYTE,MAIN_INITING,CHK_BYTE};
#endif
extern volatile S_Int32U Main_Init_Flag;

#ifdef LOW_POWER_C
EXT volatile S_Int32U PD_Chk_Ms =
{
  CHK_BYTE, 0, CHK_BYTE
};//�����������õ����⺯����ļ���
#else
extern volatile S_Int32U PD_Chk_Ms;
#endif

EXT INT8U PD_INT_EN_Flag;
//#define Power_Down_Check()//��ʱ���˺�������Ϊ�գ������жϴ����ķ�ʽ

#define CHECK_SYS_STATUS_SUM() ((Sys_Status.Status+Sys_Status.Last_Status==Sys_Status.CS)?1:0)
#define SET_SYS_STATUS_SUM() (Sys_Status.CS=Sys_Status.Status+Sys_Status.Last_Status)

EXT void Soft_Restart();
EXT void Power_Down_Int_Proc();
EXT void Power_Down_Check();
EXT void Save_PD_Data();
EXT INT8U Check_Task_Sleep(INT8U Task_ID);
EXT INT8U Check_Power_Status();
EXT void Init_Task_Status();
EXT INT32U Check_Sys_Status();
EXT INT32U Get_Sys_Status();
EXT void Check_Sys_Status_Avail();
EXT void Wait_Tasks_Sleep(INT32U Ms);
EXT void Set_Sys_Status(INT32U Status);
EXT void Set_Resume_Source(INT8U Src);
EXT INT8U Check_Resume_Source(INT8U Src);
EXT void Init_Low_Power_Proc();
EXT void Task_Sleep();
EXT void Resume_Tasks();
EXT INT8U Check_Tasks_Sleep_Done();
EXT void Init_Low_Power_Ram();
EXT void Init_Resume_Source();
EXT void Low_Power_Proc();
EXT void Check_Low_Power_Data_Avail();
EXT INT32U Get_Main_Init_Flag();
EXT void Clr_Main_Init_Flag();
EXT void Init_Sys_Status();
#endif

