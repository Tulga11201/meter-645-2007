#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#undef EXT
#ifdef LOAD_DATA_C
#define EXT
#else
#define EXT extern
#endif

#define NULL_LOAD_INDEX 0xFFFF

#define LOAD_DATA_HEAD_SIZE 7//��������ͷ���ݵĴ�С����2�ֽڵ�0xA0��5���ֽڵ�ʱ��
#define LOAD_DATA_TYPE_NUM 6//�������ߵ�6������

//���������������
typedef struct
{
    INT16U Start; //��һ��������
    INT16U Last; //���һ��������

    INT16U Last_Read;
    INT16U Min_Index;
    
    INT16U Type_Start[LOAD_DATA_TYPE_NUM]; //6�ฺ���������ݣ�ÿ�����ʼ�ͽ���
    INT16U Type_Last[LOAD_DATA_TYPE_NUM];

    INT8U CS[CS_BYTES];//У���
}S_LoadData_Index;

//�������ߴ洢�����Ϣ��������Ҫ�洢��������
typedef struct
{
    PROTO_DI PDI;
    INT16U Len;
    INT8U Type;
}S_LoadData_Info;

//�������߲���
typedef struct
{
    INT8U Time[4];
    INT16U Period[6];

    INT8U Mode; //ģʽ��
    INT8U CS[CS_BYTES];
}S_LoadData_Para;

#ifdef LOAD_DATA_C
CONST S_LoadData_Info LoadData_Info[] =
{
  //ģʽ��bit0
  {0x02010100,2,1},//A��ѹ
  {0x02010200,2,1},//B��ѹ
  {0x02010300,2,1},//C��ѹ
  {0x02020100,3,1},//A����
  {0x02020200,3,1},//B����
  {0x02020300,3,1},//C����
  {0x02800002,2,1},//Ƶ��
  //ģʽ��bit1
  //{DI_ACTIVE_DIRECT,1,1},//�й������ʶ��
  //{DI_REACTIVE_DIRECT,1,1},//�޹������ʶ��
  {0x02030000,3,2},//���й�����
  {0x02030100,3,2},//A�й�����
  {0x02030200,3,2},//B�й�����
  {0x02030300,3,2},//C�й�����
  {0x02040000,3,2},//���޹�����
  {0x02040100,3,2},//A�޹�����
  {0x02040200,3,2},//B�޹�����
  {0x02040300,3,2},//C�޹�����
  //ģʽ��bit2
  {0x02060000,2,3},//���޹�����
  {0x02060100,2,3},//A�޹�����
  {0x02060200,2,3},//B�޹�����
  {0x02060300,2,3},//C�޹�����
  //ģʽ��bit3
  {0x00010000,4,4},//�����й���
  {0x00020000,4,4},//�����й���
  {0x00030000,4,4},//�����޹��ܣ�(����޹�1��)
  {0x00040000,4,4},//�����޹��ܣ�(����޹�2��)
  //ģʽ��bit4
  {0x00050000,4,5},//һ�����޹���
  {0x00060000,4,5},//�������޹���
  {0x00070000,4,5},//�������޹���
  {0x00080000,4,5},//�������޹���
  //ģʽ��bit5 
  {0x02800004,3,6},//�й�����
  {0x02800005,3,6}//�޹�����

};
#endif

//EXT volatile INT8U LoadData_Buf[150];
EXT NO_INIT volatile S_LoadData_Para LoadData_Para;
EXT NO_INIT volatile S_LoadData_Index LoadData_Index;
EXT NO_INIT volatile S_LoadData_Index LoadData_Index_Bak;

EXT void Read_LoadData_Para_From_Rom();
EXT void Read_LoadData_Index_Data_From_Rom();
EXT INT16U Read_Load_Data_With_Time(S_HEX_Time* pTime, INT8U Mode, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Get_Load_Proto_Data(PROTO_DI PDI, INT8U Para[], INT8U ParaLen, void* pDst, void* pDst_Start, INT16U DstLen);
EXT void Set_Def_Load_Data_Index();
EXT void Save_LoadData_Index();
EXT void Save_LoadData_Index_Bak();
EXT void Save_LoadData_PD_Data();
EXT INT8U Write_Load_Data(INT8U Load_Data_Flag, INT8U* pSrc, INT16U SrcLen);
EXT void Check_LoadData_Index_Avail();
EXT void Check_LoadData_Para_Avail();
EXT INT16U Get_LoadData_Min_Index(INT8U Time[]);
EXT INT8U Check_LoadData_Index(S_LoadData_Index* pInfo);
EXT void Save_LoadData_PD_Data();
EXT INT16U Make_LoadData();
EXT INT16U Get_LoadData_All_Len();
EXT INT16U Get_LoadData_Type_Len(INT8U Type);
EXT void LoadData_Proc();

#endif
