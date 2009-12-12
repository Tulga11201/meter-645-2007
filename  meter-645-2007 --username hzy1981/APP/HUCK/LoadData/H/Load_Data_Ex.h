#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#undef EXT
#ifdef LOAD_DATA_C
#define EXT
#else
#define EXT extern
#endif

#define NULL_LOAD_INDEX 0xFFFF

#define LOAD_DATA_HEAD_SIZE 7//负荷曲线头数据的大小包括2字节的0xA0和5个字节的时间
#define LOAD_DATA_TYPE_NUM 6//负荷曲线的6类数据

//定义符合曲线索引
typedef struct
{
    INT16U Start; //第一条的索引
    INT16U Last; //最后一条的索引

    INT16U Last_Read;
    INT16U Min_Index;
    
    INT16U Type_Start[LOAD_DATA_TYPE_NUM]; //6类负荷曲线数据，每类的起始和结束
    INT16U Type_Last[LOAD_DATA_TYPE_NUM];

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

#ifdef LOAD_DATA_C
CONST S_LoadData_Info LoadData_Info[] =
{
  //模式字bit0
  {0x02010100,2,1},//A电压
  {0x02010200,2,1},//B电压
  {0x02010300,2,1},//C电压
  {0x02020100,3,1},//A电流
  {0x02020200,3,1},//B电流
  {0x02020300,3,1},//C电流
  {0x02800002,2,1},//频率
  //模式字bit1
  //{DI_ACTIVE_DIRECT,1,1},//有功方向标识字
  //{DI_REACTIVE_DIRECT,1,1},//无功方向标识字
  {0x02030000,3,2},//总有功功率
  {0x02030100,3,2},//A有功功率
  {0x02030200,3,2},//B有功功率
  {0x02030300,3,2},//C有功功率
  {0x02040000,3,2},//总无功功率
  {0x02040100,3,2},//A无功功率
  {0x02040200,3,2},//B无功功率
  {0x02040300,3,2},//C无功功率
  //模式字bit2
  {0x02060000,2,3},//总无功功率
  {0x02060100,2,3},//A无功功率
  {0x02060200,2,3},//B无功功率
  {0x02060300,2,3},//C无功功率
  //模式字bit3
  {0x00010000,4,4},//正向有功总
  {0x00020000,4,4},//反向有功总
  {0x00030000,4,4},//正向无功总，(组合无功1总)
  {0x00040000,4,4},//反向无功总，(组合无功2总)
  //模式字bit4
  {0x00050000,4,5},//一象限无功总
  {0x00060000,4,5},//二象限无功总
  {0x00070000,4,5},//三象限无功总
  {0x00080000,4,5},//四象限无功总
  //模式字bit5 
  {0x02800004,3,6},//有功需量
  {0x02800005,3,6}//无功需量

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
