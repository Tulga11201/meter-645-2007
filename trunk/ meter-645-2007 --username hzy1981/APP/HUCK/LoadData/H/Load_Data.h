#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#undef EXT
#ifdef LOAD_DATA_C
#define EXT
#else
#define EXT extern
#endif

#define NULL_LOAD_INDEX 0xFFFF

#define ALL_TYPE_DATA 0x0F //�������͵�����

#define LOAD_DATA_HEAD_SIZE 6//һ���ֽ�ͷ��5���ֽڵ�ʱ��
#define LOAD_DATA_TYPE_NUM 6//�������ߵ�6������

#define NO_CHK_TIME 0x80

//���������������
typedef struct
{
    INT16U Start; //��һ��������
    INT16U Last; //���һ��������

    INT16U Last_Read;
    INT32U Time_Index;
    
    INT16U All_Type_Start; //�����ݵ���ʼ
    INT16U All_Type_Last; //�����ݵĽ���
    
    INT16U Type_Start[LOAD_DATA_TYPE_NUM + 1]; //6�ฺ���������ݣ�ÿ�����ʼ�ͽ���
    INT16U Type_Last[LOAD_DATA_TYPE_NUM + 1];

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

//EXT volatile INT8U LoadData_Buf[150];
EXT NO_INIT volatile S_LoadData_Para LoadData_Para;
EXT NO_INIT volatile S_LoadData_Index LoadData_Index;
//EXT NO_INIT volatile S_LoadData_Index LoadData_Index_Bak;

EXT void Read_LoadData_Para_From_Rom();
EXT void Read_LoadData_Index_Data_From_Rom();
EXT INT8U Check_Load_Data_Time(S_HEX_Time *pTime, INT8U Type);
EXT INT16U Read_Load_Data_With_Time(INT8U Type, S_HEX_Time* pTime,INT8U Num, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Get_Load_Proto_Data(PROTO_DI PDI, INT8U Para[], INT8U ParaLen, void* pDst, void* pDst_Start, INT16U DstLen);
EXT void Set_Def_Load_Data_Index();
EXT void Clear_Load_Data();
EXT void Save_LoadData_Index();
EXT void Save_LoadData_Index_Bak();
EXT void Save_LoadData_PD_Data();
EXT INT8U Write_Load_Data(INT8U Type, INT8U Flag, INT8U* pSrc, INT16U SrcLen);
EXT void Check_LoadData_Index_Avail();
EXT void Check_LoadData_Para_Avail();
EXT INT32U Get_LoadData_Time_Index(INT8U Time[]);
EXT INT8U Check_LoadData_Index(S_LoadData_Index* pInfo);
EXT void Save_LoadData_PD_Data();
EXT INT16U Make_LoadData(INT8U Type, S_HEX_Time* pTime, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U Get_LoadData_All_Len();
EXT INT16U Get_LoadData_Type_Len(INT8U Type);
EXT void LoadData_Proc();

#endif
