#ifndef VOLSTAT_H
#define VOLSTAT_H

#undef EXT
#ifdef VOLSTAT_C
#define EXT
#else
#define EXT extern
#endif

#define VOL_RATIO 1000

#define EXAM_UPPER_VOL 2700000
#define EXAM_LOWER_VOL 1700000

typedef struct
{
    INT32U Qual_Upper_Limit;//�ϸ�����
    INT32U Qual_Lower_Limit;//�ϸ�����
    INT32U Exam_Upper_Limit;//��������
    INT32U Exam_Lower_Limit;//��������
    INT8U CS[CS_BYTES];
}S_VolStat_Para;


typedef struct
{
    INT8U Head;

    S_HEX_Time Time;

    INT8U Temp;//��֤�����Time����

    INT32U Total_Time[4];//��������ʱ��,3��ʾ��,0-2�ֱ��ʾA��B��C���࣬
    INT32U Upper_Time[4];//����ʱ��
    INT32U Lower_Time[4];//����ʱ��

    INT32U Qual[4];//����ϸ���
    INT32U Exam[4];//������

    INT32U Max_Vol[4];//��ߵ�ѹ
    INT8U Max_Vol_Time[4][5];//ʱ�䣬16������

    INT32U Min_Vol[4];//��͵�ѹ
    INT32U Min_Vol_Time[4][5];//ʱ�䣬16������

    INT32U Data_Ready_Flag;

    INT8U CS[CS_BYTES];

    INT8U Tail;
}S_VolStat;

typedef struct
{
    INT8U Head;
  
    INT8U Sec;
    
    INT8U Qual_Upper[4];
    INT8U Qual_Lower[4];//���ϸ����
    INT8U Exam_Upper[4];
    INT8U Exam_Lower[4];//�����˼���  
    
    INT8U CS[CS_BYTES];
    
    INT8U Tail;
}S_VolStat_Count;

EXT NO_INIT volatile S_VolStat Cur_VolStat;//���µ�ѹ�������
//EXT NO_INIT S_VolStat Total_VolStat;//��ѹ���������
EXT NO_INIT volatile S_VolStat_Para VolStat_Para;//��ѹͳ�Ʋ���
EXT volatile S_VolStat_Count VolStat_Count;//��ѹͳ�Ƽ���
//EXT S_Event_Vol_Cur Event_Vol_Cur;

EXT INT8U Check_VolStat_Data(S_VolStat* pVolStat);
EXT void Check_VolStat_Para_Avail();
EXT void Check_VolStat_Data_Avail();

EXT void Freeze_VolStat_Data(S_HEX_Time* pTime);
EXT void Save_Cur_VolStat_PD_Data();
EXT void Save_Cur_VolStat_Data();
EXT void Vol_Stat_Proc();
EXT void Set_Def_Cur_VolStat_Data();
EXT void Set_Def_VolStat_Data();
EXT void Read_VolStat_Data_From_Rom();
EXT void PowerDown_Save_VolStat_Data();
EXT void PowerOn_VolStat_Data_Freeze();
EXT void Read_VolStat_Para_From_Rom();
EXT void Clear_VolStat_Data();
EXT INT8U Clear_Proto_Phase_VolStat_Data(PROTO_DI PDI);
EXT void Clear_Cur_VolStat_Ram();
EXT void Clear_VolStat_Count_Ram();
EXT void VolStat_Proc();
EXT void Init_VolStat_Ram_Para();
#endif
