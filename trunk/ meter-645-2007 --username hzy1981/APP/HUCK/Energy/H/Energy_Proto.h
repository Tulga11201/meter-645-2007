#ifndef ENERGY_PROTO_H
#define ENERGY_PROTO_H

#undef EXT
#ifdef ENERGY_PROTO_C
#define EXT
#else
#define EXT extern
#endif
/*
//�����ṹ��
typedef struct 
{
  //INT8U Time[5];//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��
  S_HEX_Time Time;//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��
  
  INT32U  Pos_Active[MAX_RATES+1];//���Լ��ַ��������й�,��λС��,��λKWh����ͬ
  INT32U  Neg_Active[MAX_RATES+1];//���Լ��ַ��ʷ����й�
  
  INT32U  Quad_Reactive[4][MAX_RATES+1];//�����޷ַ����޹�
  
  INT32U  Phase_Pos_Active[3];//���������й�
  INT32U  Phase_Neg_Active[3];//���෴���й�
  
  INT32U Phase_Quad_Reactive[3][4];//�����������޹�
  
  INT32U  Phase_AH[3];//������AH
  
  INT32U  CopperLoss[4];//��ABCͭ��
  INT32U  IronLoss[4];  //��ABC����
  INT32U  TransErr[4];  //��ABC���������
  
  //INT32U  Phase_Reactive[3][4];//������������޹�
  
  INT8U   CS[CS_BYTES];//����Ĳ���Ҫ���浽Flash��
  
  //���²����Ǹ�������������ã�����Ҫ���浽Flash��EERom��
  //INT32U Pos_Reactive[MAX_RATES+1];//���Լ��ַ��������޹�
  //INT32U Neg_Reactive[MAX_RATES+1];
  
}S_Energy;
*/
typedef struct
{
  INT8U Head;
  
  INT8U Active; 
  INT8U Reactive[2];

  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Comb_Word;

typedef struct
{
    //��������
    S_Energy Base;

    INT32S Comb_Month_Active; //һ��������������й�,������ջ�����
    INT32S Comb_Last_Month_Active; //��һ������������й�
    //���������
    INT32S Comb_Active[MAX_RATES + 1];  //����й�

    INT32S Comb_Reactive1[MAX_RATES + 1]; //����޹�1
    INT32S Comb_Reactive2[MAX_RATES + 1]; //����޹�2

    //�����������
    INT32U Phase_Comb_Active[3];  //����й�

    INT32S Phase_Comb_Reactive1[3]; //����޹�1
    INT32S Phase_Comb_Reactive2[3]; //����޹�2

}S_Comb_Energy;//��ϵ��ܽṹ��

EXT volatile S_Comb_Word Energy_Comb_Word;

EXT void Read_Energy_Comb_Word();
EXT INT16U Get_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Get_Prepaid_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Get_Rate_Info_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U Get_Prepaid_Event_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT8U Set_Energy_Start(PROTO_DI PDI,INT8U *pSrc, INT16U SrcLen);
EXT INT8U Clear_One_Event_Data(PROTO_DI PDI);
#endif
