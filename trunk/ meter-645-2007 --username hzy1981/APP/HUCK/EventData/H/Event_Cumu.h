#ifndef EVENT_CUMU_H
#define EVENT_CUMU_H

#include "EventPub.h"

#undef EXT
#ifdef EVENT_CUMU_C
#define EXT
#else
#define EXT extern
#endif

#define ARRAY_DI_NUM 30

#define EVENT_REAL  0
#define EVENT_VIRTRUAL 1

#define NULL_EVENT_ID 0xFF

#define CUMU_LOSS_VOL_SIZE  (13 + 80)
#define CUMU_LOSS_CUR_SIZE  (13 + 80)
#define CUMU_NEG_CUR_SIZE   (13 + 80)
#define CUMU_BREAK_VOL_SIZE (13 + 80)

typedef struct
{
    INT8U DI_Num;
    PROTO_DI PDI[ARRAY_DI_NUM];
}S_DI_Array;

//�����¼����ۼӴ���
typedef struct
{
    INT8U Event_ID;//�¼� ID

    //�¼����ۼ�ʱ��ʹ�����Ҫ���⴦��
    //STORA_DI Counts_DI;//�����ۼ�DI,��ͬ��ͨ��Э��DI
    //INT8U Counts_Start;
    //INT8U Counts_Len;

    //STORA_DI Mins_DI;//ʱ���ۼ�DI,��ͬ��ͨ��Э��DI
    //INT8U Mins_Start;
    //INT8U Mins_Len;

    ///////////////////////���沿����ʱ��ʹ������ۼӣ���׼��Լ���涼�е�//////////////////////////////

    ///////////////////////���沿���ǵ��ܵ����ۼ�///////////////////////////
    STORA_DI Occur_Stora_DI;//����ʱ�ĵ������ݴ洢DI
    STORA_DI Total_Stora_DI;//�ܵĵ������ݵ�DI,��ͬ��Э��DI

    S_DI_Array* pDI_Array;
    
    INT8U Clr_Flag;
}S_Event_Cumu_Data_Info;

///////////////////////////////////////////////
/*
#define PHASE_A   0x01
#define PHASE_B   0x02
#define PHASE_C   0x04
#define PHASE_AB  0x03
#define PHASE_AC  0x05
#define PHASE_BC  0x06
#define PHASE_ABC 0x07
#define PHASE_ALL 0x08

//��������¼��ۼ���Ϣ
typedef struct
{
  INT32U Counts;//ʧѹ���� 
  INT32U Time;//ʧѹ�ۼ�ʱ��
  
  INT8U CS[CS_BYTES];
}S_Phase_Cumu;

//ʧѹ�ۼ�����
typedef struct
{
  INT32U Counts;//ʧѹ���� 
  INT32U Time;//ʧѹ�ۼ�ʱ��
  
  INT32U Phase_Pos_Active[4];//�ܡ�A��B��C���ۼ��й�����
  INT32S Phase_Pos_Reactive[4];//�ܡ�A��B��C���������޹�������޹�1
  INT32U Phase_Neg_Active[4];//�ܡ�A��B��C���෴���й�
  INT32S Phase_Neg_Reactive[4];//�ܡ�A��B��C���෴���޹�������޹�2
  INT32U Phase_AH[3];//A��B��C���ల��ʱ��
  
  INT8U CS[CS_BYTES]; 
}S_Loss_Vol_Cumu;


//ʧ���ۼ�����
typedef struct
{
  INT32U Counts;//ʧѹ���� 
  INT32U Time;//ʧѹ�ۼ�ʱ��
  
  INT32U Phase_Pos_Active[4];//�ܡ�A��B��C���ۼ��й�����
  INT32S Phase_Pos_Reactive[4];//�ܡ�A��B��C���������޹�������޹�1
  INT32U Phase_Neg_Active[4];//�ܡ�A��B��C���෴���й�
  INT32S Phase_Neg_Reactive[4];//�ܡ�A��B��C���෴���޹�������޹�2
  //INT32U Phase_AH[3];//A��B��C���ల��ʱ��
  
  INT8U CS[CS_BYTES]; 
}S_Loss_Cur_Cumu;

//�����ڼ��ۼ�����
typedef struct
{
  INT32U Counts;
  INT32U Time;
  
  INT32U Phase_Pos_Active[4];//�ܡ�A��B��C���ۼ��й�����
  INT32U Phase_Neg_Active[4];//�ܡ�A��B��C���෴���й�
  INT8U CS[CS_BYTES];
}S_Reverse_Cumu;//


//ȫʧѹ��ȫʧ���������ۼ�����
typedef struct
{
  INT32U Counts;
  INT32U Time;
  INT8U CS[CS_BYTES];
}S_Phase_Break_Cumu;

//�ܵ��¼��ۼ���
typedef struct
{
  INT8U Loss_Vol_Flag;    //ʧѹ��־
  INT8U Loss_Cur_Flag;    //ʧ����־
  INT8U Phase_Reverse_Flag; //�����־
  INT8U Phase_Break_Flag;   //�����־
  
  S_Phase_Cumu Phase_Loss_Vol[9];//�ܡ�A��B��C��AB��AC��BC��ABC��ȫʧѹ��
  S_Phase_Cumu Phase_Loss_Cur[8];//�ܡ�A��B��C��AB��AC��BC��ȫʧ��
  S_Phase_Cumu Phase_Break[4];//�������(������AB,BC,AC,ABC�����)�ܡ�A��B��C
  S_Reverse_Cumu Phase_Reverse[4];//���෴��(������AB,BC,AC,ABC�����)�ܡ�A��B��C

  
  S_Loss_Vol_Cumu Loss_Vol;//ʧѹ�ڼ��ۼƵ��ܵ�,���뿼�Ǻ�������
  S_Loss_Cur_Cumu Loss_Cur;//ʧ���ڼ��ۼƵ��ܵ�

  
  INT8U CS[CS_BYTES];
}S_Event_Cumu;

typedef struct
{
  INT32S Pos_Reactive[4];//�ܡ�A��B��C�����޹�  
  INT32U Neg_Reactive[4];//�ܡ�A��B��C�����޹�
}S_Phase_Reactive;

typedef struct
{
  INT8U Start_Time[5];
  INT8U End_Time[5];
  INT8U CS[CS_BYTES];  
}S_All_Loss_Vol_Time;

EXT volatile S_All_Loss_Vol_Time All_Loss_Vol_Time;//���һ��ȫʧѹ�ķ����ͽ��ʱ��,��������Э������
EXT NO_INIT volatile S_Event_Cumu Event_Cumu;     //�¼��ۼ�����
EXT volatile S_Phase_Reactive Cumu_Phase_Reactive; //��������޹��ۼ�����

EXT INT8U Check_Phase_Event(INT8U Flag,INT8U Phase);
EXT void Event_Cumu_Proc(INT8U Event_ID,INT8U Occur_Or_End);
EXT void Read_Event_Cumu_Data_From_Rom();
EXT void Save_Event_Cumu_PD_Data();
EXT INT8U Check_Event_Occuring(INT8U Event_ID);
EXT void Save_Event_Cumu_Bak_Data();
EXT void Set_Def_Event_Cumu_Data();
*/
EXT CONST S_Event_Cumu_Data_Info Event_Cumu_Data_Info[];

EXT INT8U Check_Cumu_Event_Occuring(INT8U Event_ID);
EXT INT8U Check_Total_Event_ID(INT8U Event_ID);
EXT INT8U Get_Total_Event_ID(INT8U Event_ID);
EXT INT16U Event_Cumu_End_Proc(INT16U Index, INT8U Flag);
EXT INT16U Event_Cumu_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag);
EXT INT16U Get_Event_Cumu_Proto_Index(PROTO_DI DI);
EXT void Get_Event_Cumu_Counts_Mins(INT8U Event_ID, INT32U *pCounts, INT32U *pMins);
EXT void Get_Event_Cumu_BCD_Counts_Mins(INT8U Event_ID, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT16U Get_Cumu_Event_Num();
EXT void Event_Data_Proc(INT8U Event_ID, INT8U Occur_Or_End);
EXT void Event_Cumu_Mins_Accu();
EXT void Set_Def_Event_Cumu_Data();
EXT void Clear_Event_Cumu_Data();
EXT INT8U Clear_One_Event_Cumu_Data(INT8U Event_ID);
EXT void Clr_Event_PD_Data();
EXT void Save_Event_PD_Data();
#endif
