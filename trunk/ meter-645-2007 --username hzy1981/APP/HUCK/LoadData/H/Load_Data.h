#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#undef EXT
#ifdef LOAD_DATA_C
#define EXT
#else
#define EXT extern
#endif

#define NULL_LOAD_INDEX 0xFFFF

#define ALL_TYPE_DATA 0x0F //所有类型的数据

#define LOAD_DATA_HEAD_SIZE 6//一个字节头和5个字节的时间
#define LOAD_DATA_TYPE_NUM 6//负荷曲线的6类数据

#define NO_CHK_TIME 0x80

//定义符合曲线索引
typedef struct
{
    INT16U Start; //第一条的索引
    INT16U Last; //最后一条的索引

    INT16U Last_Read;
    INT32U Time_Index;
    
    INT16U All_Type_Start; //总数据的起始
    INT16U All_Type_Last; //总数据的结束
    
    INT16U Type_Start[LOAD_DATA_TYPE_NUM + 1]; //6类负荷曲线数据，每类的起始和结束
    INT16U Type_Last[LOAD_DATA_TYPE_NUM + 1];

    INT8U CS[CS_BYTES];//校验和
}S_LoadData_Index;

//负荷曲线存储相关信息，定义需要存储的数据项
typedef struct
{
    PROTO_DI PDI;
    INT16U Len;
    INT8U Type;
}S_LoadData_Info;

//负荷曲线参数
typedef struct
{
    INT8U Time[4];
    INT16U Period[6];

    INT8U Mode; //模式字
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
