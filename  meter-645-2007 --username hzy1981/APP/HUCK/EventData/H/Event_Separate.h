#ifndef EVENT_Separate_H
#define EVENT_Separate_H

//#include "Include_PUCK.h"

#undef EXT
#ifndef EVENT_SEPARATE_C
#define EXT extern
#else
#define EXT
#endif

#define MAX_EVENT_Separate_NUM 30

#define NULL_EVENT_STORA_DI 0xFF00FF00

#define FREEZE_DATA_MAX_LEN (5 + 4 * (MAX_RATES + 1) * 8 + 8 * (MAX_RATES + 1) * 2 + 24)

#define ONE_RECORD_EVENT 0
#define MULTI_RECORD_EVENT 1

#define EVENT_OCCUR 0x5A//��ʾ�¼�����,������
#define EVENT_END 0xA5//��ʾ�¼��Ľ���������������Ҫ�����CONTIN_EVENT���͵��¼�

#define ID_EVENT_TOTAL_LOSS_VOL   0xD0//��ʧѹ�¼�
#define ID_EVENT_TOTAL_LOSS_CUR   0xD1//��ʧ���¼�
#define ID_EVENT_TOTAL_NEG_CUR    0xD2//�ܷ����¼�
#define ID_EVENT_TOTAL_BREAK_VOL  0xD3//�ܶ����¼�
#define ID_EVENT_PERIOD_FREEZE      0xD4 //���ڶ���
#define ID_EVENT_INSTANT_FREEZE     0xD5 //˲ʱ����

#define ID_EVENT_YEAR_TABLE_SWITCH_FREEZE     0xD6 //��ʱ�����л� 
#define ID_EVENT_DATE_TABLE_SWITCH_FREEZE     0xD7 //��ʱ�α��л�
#define ID_EVENT_RATE_SCH_SWITCH_FREEZE       0xD8 //���ʷ����л�
#define ID_EVENT_STEP_SCH_SWITCH_FREEZE          0xD9 //�����ݶ��л�

#define ID_EVENT_DATE_FREEZ         0xDA//(ID_EVENT_Q4_REAC_DEMAND_EXCEED+1)         //�ն���--------97
#define ID_EVENT_HOUR_FREEZ         0xDB//(ID_DATE_FREEZ+1)                        //Сʱ����--------98

#define ID_EVENT_ENERGY_OVERTURN_FREEZE 0xDC //������ת����

#define ID_EVENT_PREPAID_ENERGY     0xDD //�����¼�--������
#define ID_EVENT_PREPAID_MONEY      0xDE //�����¼�--�����

//#define ID_EVENT_FACTOR_LOW         0xDF //�ܹ������س�����

#define ID_EVENT_A_LOW_VOLT        0xE0 //A��Ƿѹ
#define ID_EVENT_B_LOW_VOLT        0xE1 //B��Ƿѹ
#define ID_EVENT_C_LOW_VOLT        0xE2 //C��Ƿѹ

//#define ID_EVENT_REMOTE_RELAY_ON  0xDB //Զ�̺�բ
//#define ID_EVENT_REMOTE_RELAY_OFF 0xDC //Զ����բ
//#define ID_VOL_STAT           0xDD//��ѹͳ�ƣ�ʵ�ʲ��޴��¼���ֻ��Ϊ��ͳһ�������¼���¼

/*
#define ID_EVENT_POS_ACT_DEMAND_EXCEED 0xD8//�����й���������
#define ID_EVENT_NEG_ACT_DEMAND_EXCEED 0xD9//�����й���������
#define ID_EVENT_Q1_REAC_DEMAND_EXCEED 0xDA//һ�����޹�������
#define ID_EVENT_Q2_REAC_DEMAND_EXCEED 0xDB//�������޹�������
#define ID_EVENT_Q3_REAC_DEMAND_EXCEED 0xDC//�������޹�������
#define ID_EVENT_Q4_REAC_DEMAND_EXCEED 0xDD//�������޹�������
*/
#define MAX_EVENT_DATA_NUM 56

typedef struct
{
    INT8U Occur_Mask[MAX_EVENT_DATA_NUM/8]; //�¼�����������������,ĳλΪ1��ʾ����ĳ������,��ͬ
    INT8U End_Mask[MAX_EVENT_DATA_NUM/8];  //�¼�����������������
    INT8U Diff_Mask[MAX_EVENT_DATA_NUM/8];  //�������ʱ��Ҫ��¼��������Ŀ
    INT8U Data_Num;  //��Ҫ��¼�����������
    INT16U Data_Len; //�������ݳ���
    PROTO_DI const *PDI;//PDI[53]; //��Ҫ��¼��������
}S_Event_DI;

typedef struct
{
	INT32U Mins;
	INT8U Start_Time[6];//�롢�֡�ʱ���ա��¡���
	INT8U End_Time[6];//ͬ��
	INT8U CS[CS_BYTES];  
}S_All_Loss_Vol_Time;

typedef struct
{
    INT8U Event_ID;    //�¼���¼��ID
    //�����������������Ϣ
    //INT8U Property;    //�¼���¼����

    S_Event_DI const *pData;

    //PROTO_DI Proto_DI;//���һ�θ��¼�������Э��DI
    // ���¼�ΪOCCUR_AND_END_EVENT���¼�ʱ����Ϊ�����ͽ�������һ��Э��DI���棬����
    // ֻ���ø�DI��ʾ���¼���DI
    //PROTO_DI End_DI;  //���һ�θ��¼�������Э��DI,���¼�ΪOCCUR_AND_END_EVENT���¼�ʱ��DIû������
    // ��ʱ��ΪOCCUR_OR_END_EVENT���¼�ʱ��DI��ʾ�¼�������Э��DI

    // ����洢��ص���Ϣ
    STORA_DI Last_SDI;
    //�洢���һ���¼��Ĵ洢DI,��洢������Ϊ Start_DI->Start_DI+Num
    STORA_DI SDI;
    INT16U Storage_Num;//���¼����洢��������¼

    INT8U Clr_Flag; //0��ʾ������������¼���1��ʾ�������
}S_Event_Separate_Data_Info;

typedef struct  
{
	INT8U Head;

	INT8U Time[6];
	INT8U Tail;
}S_PD_Time;

//extern CONST S_Event_Separate_Data_Info Event_Data_Info[];
extern CONST S_Event_Separate_Data_Info Event_Separate_Data_Info[];

EXT volatile S_All_Loss_Vol_Time All_Loss_Vol_Time;//���һ��ȫʧѹ�ķ����ͽ��ʱ��,��������Э������


EXT INT16U Get_Event_Data_Index(INT8U Event_ID);
EXT INT16U Get_Event_Data_Index_From_DI(PROTO_DI PDI);
EXT STORA_DI Read_Last_Event_Storage_DI(INT8U Event_ID);
EXT INT16U Get_Event_Separate_Data_Index(INT8U Event_ID);
EXT INT16U Read_Last_Event_Data(INT8U Event_ID, STORA_DI Storage_DI, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Event_Separate_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag);
EXT INT16U Get_Separate_Event_Num();
EXT INT16U Get_Event_Separate_Proto_Index(PROTO_DI PDI);
//EXT void Clear_Event_Data();
EXT void Set_Def_Event_Separate_Data();
EXT void Clear_Event_Separate_Data();
EXT INT8U Clear_One_Event_Separate_Data(INT8U Event_ID);
EXT INT8U Check_Event_Clr_PDI(PROTO_DI PDI);
#endif

