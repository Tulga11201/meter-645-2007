#ifndef DEMAND_H
#define DEMAND_H

#include "Pub_Time.h"

#undef EXT
#ifdef DEMAND_C
#define EXT
#else
#define EXT extern
#endif
/*
�������ݴ洢���ص�:
CUR_DEMAND���Լ����з��ʵ�����
CUR_DEMAND_BAK�洢��ʽ��CUR_DEMANDһ��
CUR_DEMAND_PD��Ҫ�ǵ���洢,ֻ�洢S_Demand�ṹ��Cur_Demand
HIS_DEMAND��Ҫ�洢ǰN���µ����ݣ�ÿ���������CUR_DEMAND��ʽһ��
*/

#define CUR_POS_ACT_DEMAND     Demand_Accu.Phase_Cur[0].Pos_Active       //��ǰ�����й�����
#define CUR_NEG_ACT_DEMAND     Demand_Accu.Phase_Cur[0].Neg_Active       //��ǰ�����й�����
#define CUR_QUAD1_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[0] //��ǰһ��������
#define CUR_QUAD2_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[1] //��ǰ����������
#define CUR_QUAD3_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[2] //��ǰ����������
#define CUR_QUAD4_REACT_DEMAND Demand_Accu.Phase_Cur[0].Quad_Reactive[3] //��ǰ����������

#define MAX_PERIOD_SLIDE_RATIO 15//��������/����ʱ������ֵ

#define POWER_DIRECT_N 0//���幦�ʷ�������
#define POWER_DIRECT_P 1//����

#define POWER_DATA_RATIO 100

//����ʱ�����ݵĴ洢ƫ�ƣ�ָ��һ�����������������
#define DEMAND_TIME_DATA_OFF 0
#define DEMAND_TIME_DATA_SIZE sizeof(S_HEX_Time)

#define DEMAND_PHASE_DATA_OFF (DEMAND_TIME_DATA_SIZE + ROM_CS_BYTES)
#define DEMAND_PHASE_DATA_SIZE sizeof(Cur_Demand.Phase_Demand)

//ĳ�����������������������洢���еĴ洢ƫ��
//�����洢����ʽ:
//ʱ��:sizeof(S_HEX_Time)+ROM_CS_BYTES
//������������:sizeof(S_Phase_Demand)+ROM_CS_BYTES;
//���Լ��ַ�������:(DEMAND_RATE_DATA_SIZE + ROM_CS_BYTES)* MAX_RATES
#define DEMAND_RATE_DATA_SIZE sizeof(S_One_Demand)
#define DEMAND_RATE_DATA_OFF(x) (DEMAND_TIME_DATA_SIZE + ROM_CS_BYTES +\
     DEMAND_PHASE_DATA_SIZE + ROM_CS_BYTES +\
        (DEMAND_RATE_DATA_SIZE + ROM_CS_BYTES) * (INT32U)(x))//����ĳ�����ʵ��������������������洢���е�ƫ��

#define POS_ACT_DEMAND_LIMIT   Power_Ctrl_Para.Pos_Act_Power_Limit//(INT32U)(Get_Un()*Get_In()*2*10)//��λΪ0.1W�� 0.0001kw Get_Max_Power()
#define NEG_ACT_DEMAND_LIMIT  Power_Ctrl_Para.Neg_Act_Power_Limit//(INT32U)(Get_Un()*Get_In()*2*10)//Get_Max_Power()
#define QUAD_REA_DEMAND_LIMIT  Power_Ctrl_Para.Pos_Act_Power_Limit//(INT32U)(Get_Un()*Get_In()*2*10)//Get_Max_Power()

typedef struct
{
  INT32U Pos_Act_Demand_Limit; //�����й���������
  INT32U Neg_Act_Demand_Limit; //�����й���������
  INT32U Reac_Demand_Limit;    //�޹���������
  
  INT8U CS[CS_BYTES];
}S_Demand_Limit_Para;

//������ز���
typedef struct
{
    INT8U Period;//�������ʱ��
    INT8U Slide_Time;//����ʱ��

    INT8U CS[CS_BYTES];
}S_Demand_Para;

//���Լ����������ۼӵ�Ԫ
typedef struct
{
    INT32U Pos_Active[MAX_PERIOD_SLIDE_RATIO];//�����й�15�������ۼӵ�Ԫ,��λ0.0001kw
    INT32U Neg_Active[MAX_PERIOD_SLIDE_RATIO];//�����й�15�������ۼӵ�Ԫ,��λ0.0001kw

    INT32U Pos_Apparent[MAX_PERIOD_SLIDE_RATIO];//��������15�������ۼӵ�Ԫ,��λ0.0001kw
    INT32U Neg_Apparent[MAX_PERIOD_SLIDE_RATIO];//��������15�������ۼӵ�Ԫ,��λ0.0001kw    
    
    //INT32U Comb_Reactive1[MAX_PERIOD_SLIDE_RATIO];//�����޹�15�������ۼӵ�Ԫ,��λ0.0001kvar
    //INT32U Comb_Reactive2[MAX_PERIOD_SLIDE_RATIO];//�����޹�15�������ۼӵ�Ԫ,��λ0.0001kvar

    INT32U Quad_Reactive[4][MAX_PERIOD_SLIDE_RATIO];//�������޹�15�������ۼӵ�Ԫ

    INT8U CS[CS_BYTES];
}S_Phase_Accu;

//���Լ����൱ǰ����
typedef struct
{
    INT32U Pos_Active;//��ǰ��������,��λ0.0001kw
    INT32U Neg_Active;//��ǰ��������,��λ0.0001kw

    INT32U Pos_Apparent; //���ڹ���
    INT32U Neg_Apparent;
    
    INT32U Quad_Reactive[4];
    INT32S Comb_Reactive1;
    INT32S Comb_Reactive2;

    INT8U CS[CS_BYTES];
}S_Phase_Cur;

//����ͳ����Ϣ,�����������ۼ�ʱ��
typedef struct
{
    INT16U Counts[MAX_PERIOD_SLIDE_RATIO];
    INT16U Mins[MAX_PERIOD_SLIDE_RATIO];

    INT8U CS[CS_BYTES];
}S_Accu_Stat;

//����
typedef struct
{
    INT8U Head;
    /////////////
    S_Phase_Accu Phase_Accu[DEMAND_ACCU_PHASE_NUM]; //���Լ����������ۼӵ�Ԫ,4λС��
    S_Phase_Cur Phase_Cur[DEMAND_ACCU_PHASE_NUM];  //���Լ����൱ǰ����,4λС��
    S_Accu_Stat Accu_Stat;
    
    INT8U Tail;
}S_Demand_Accu;//�����ۼ�


//S_Demand_Time��S_Comb_Demand_Time�ĸ�ʽӦ�û���һ��
//��Ϊ��ȡ�������ݵĴ����мٶ����������ṹ����ڴ沼��һ��
typedef struct
{
    INT32U Var;
    INT8U Time[5];//�֡�ʱ���ա��¡���
}S_Demand_Time;

//����޹�����
typedef struct
{
    INT32S Var;
    INT8U Time[6];
}S_Comb_Demand_Time;

typedef struct
{
  INT8U Head;
  INT8U Rate_Bak;
  INT8U Min_Bak;
  INT32U Mins;
  INT8U Tail;
}S_Demand_Rate_Mins;

//����һ����������������ݽṹͨ����������ĳ�����ʻ��ܵ�������������
typedef struct
{
    S_HEX_Time Time;

    S_Demand_Time Pos_Active; //�����й�
    S_Demand_Time Neg_Active; //�����й�

    S_Demand_Time Quad_Reactive[4]; //�������޹�

    S_Comb_Demand_Time Comb_Reactive1; //����޹�1
    S_Comb_Demand_Time Comb_Reactive2; //����޹�2

    S_Demand_Time Pos_Apparent; //��������
    S_Demand_Time Neg_Apparent; //��������

    //����У���
    INT8U CS[CS_BYTES];
}S_One_Demand;


//�������ݽṹ�壬��ʾÿ�����ʵ�������Ϣ
typedef struct
{
    INT8U Head;

    INT8U Rate;//��ǰ����

    //���Լ���ǰ��������
    S_One_Demand Demand[2];//�����ܺ͵�ǰ���ʵ��������� 

    INT8U Temp0;//����

    S_One_Demand Phase_Demand[3];//������������

    INT8U Temp1;//����

    INT32U Data_Ready_Flag;

    INT8U CS[CS_BYTES];

    INT8U Tail;
}S_Demand;//

typedef struct
{
  INT8U Head;
  
  INT32S Active;   //�й�����
  INT32S Apparent; //��������
  INT32S Reactive; //�޹�����
  
  INT8U Tail;//INT8U CS[CS_BYTES];
}S_Sign_Demand;

typedef struct
{
  INT8U Head;
  
  INT32U Accu_Power;
  INT32U Aver_Power; //4λС������λ0.0001kw
  INT16U Counts;
  
  INT8U Tail;
  //INT8U CS[CS_BYTES];
}S_Aver_Power;

EXT volatile S_Aver_Power AcPower_1Min_Aver; //�й�һ����ƽ������

#ifdef DEMAND_C
volatile S_Aver_Power AcPower_1Min_Aver = {CHK_BYTE, 0, 0, 0, CHK_BYTE};
#endif

EXT volatile S_Demand_Limit_Para Demand_Limit_Para; //����Խ�޲���
EXT volatile S_Demand_Para Demand_Para;
EXT volatile S_Demand_Accu Demand_Accu;
EXT NO_INIT volatile S_Demand Cur_Demand;     //��ǰ����������ݽṹ��
EXT volatile S_Sign_Demand Sign_Demand;   //�з��ŵĵ�ǰ��������Ҫ����Э�鳭��

#ifdef DEMAND_C
volatile S_Sign_Demand Sign_Demand = {CHK_BYTE, 0, 0, 0, CHK_BYTE};   //�з��ŵĵ�ǰ��������Ҫ����Э�鳭��
#endif
EXT volatile INT8U Clear_Demand_Way;//��������ʽ

EXT INT8U Check_Demand_Data(S_Demand* pDemand);

EXT void Read_Demand_Para_From_Rom();
EXT void Read_Demand_Data_From_Rom();
EXT void Save_Cur_Demand_Data();
EXT void Save_Cur_Demand_PD_Data();
EXT void Save_Cur_Demand_Bak_Data();
EXT void Set_Def_Cur_Demand_Data(S_HEX_Time *pTime);
EXT void Set_Def_Demand_Data();
EXT void Freeze_Demand_Data(S_HEX_Time* pTime);
EXT void Demand_Check_Rate_Change();
EXT void Check_Demand_Para_Avail();
EXT void Demand_Accumu();
EXT void Demand_Generate();
EXT void Demand_Accu_Clear();
EXT void Demand_Clear(S_HEX_Time* pTime);
EXT void Demand_Proc();
EXT void Calc_1Min_Aver_AcPower();
//EXT void Demand_Accu_Init(INT32U Sleep_Secs);
EXT void PowerOn_Demand_Proc();
EXT void Check_Demand_Data_Avail();
EXT void Clear_Cur_Demand_Data();
EXT void Clear_Demand_Data();
EXT void Clr_Demand_Accu();
EXT void Manul_Clr_Demand_Data();
EXT void Clr_Demand_Manul_Chk();

EXT INT32U Get_One_Min_AcPower_Aver();
EXT INT8U Get_Demand_Run_Mode();
EXT void Set_One_Demand_Time(S_One_Demand* pSrc, S_HEX_Time* pTime);
EXT void PowerOn_Demand_Data_Freeze();
EXT void PowerDown_Save_Demand_Data();
EXT void Debug_Print_Cur_Demand_Info();
#endif
