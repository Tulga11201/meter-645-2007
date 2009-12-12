#ifndef FREEZE_DATA_H
#define FREEZE_DATA_H

#undef EXT
#ifdef FREEZE_DATA_C
#define EXT
#else
#define EXT extern
#endif

//���嶨ʱ����ʱ��
typedef struct
{
  INT8U Mode[5];
  
  INT8U Period_Freeze_Time[4];    //���ڶ���ʱ��

  INT8U Hour_Freeze_Start_Time[5]; //���㶳����ʼʱ��,�֡�ʱ���ա��¡���
  INT8U Hour_Freeze_Period;  //���㶳����

  INT8U Date_Freeze_Time[2]; //�ն���ʱ��
  INT8U CS[CS_BYTES];
}S_Freeze_Para;

//EXT volatile S_Freeze_Time Freeze_Time;//�书���ڶ���ʱ��
EXT volatile S_Freeze_Para Freeze_Para;

EXT void Read_Freeze_Para_From_Rom();
EXT void Check_Freeze_Para_Avail();
EXT void Freeze_Proc();
#endif
