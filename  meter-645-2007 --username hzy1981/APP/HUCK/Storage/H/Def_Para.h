#ifndef DEF_PARA_H
#define DEF_PARA_H

#undef EXT
#ifdef DEF_PARA_C
#define EXT
#else
#define EXT extern
#endif

#define FIRST_BOOT_ON_FLAG 0xAA5555AA
#define BYTE_0(x) (INT8U)((INT32U)(x)&0xFF)
#define BYTE_1(x) (INT8U)(((INT32U)(x)&0x0000FF00)>>8)
#define BYTE_2(x) (INT8U)(((INT32U)(x)&0x00FF0000)>>16)

#define DISP_CLR_DATA_INFO Main_Dis_Info("CLr dATA")

#define E_VOL 0x01
#define E_CUR 0x02
#define E_POW 0x03
#define E_MAX_POW 0x04

#define E_VOL_S 0x05
#define E_CUR_S 0x06
#define E_POW_S 0x07
#define E_POW_MAX_S 0x08

//#define FIRST_BOOT_ON_FLAG 0x55AAA55A

typedef struct
{
    STORA_DI SDI;
    INT8U Num;
    CONST INT8U* pPara;
}S_Def_Para_Info;

typedef struct
{
  STORA_DI SDI;
  INT16U Ratio;
  INT8U Type;  
}S_Def_Event_Para_Info;

extern CONST S_Def_Para_Info Def_Para[];

extern CONST INT8U Zero[];

#define Def_VolStat Zero
#define Def_LoadData_Index Zero

extern CONST INT8U Def_04000106[];
extern CONST INT8U Def_04000107[];
extern CONST INT8U Def_04000108[];
extern CONST INT8U Def_04000109[];

extern CONST INT8U Def_04000601_3[];//有无功组合模式字


EXT void Write_Def_Para();
EXT void Write_One_Def_Para(STORA_DI SDI);
EXT INT8U Check_Def_Para(STORA_DI SDI);
EXT void Set_Def_Adj_Para();
EXT void Set_Def_Para_Except_Adj();
EXT void Set_All_Def_Data();
EXT INT32U Get_Def_Para_Info_CS();
EXT void Check_Boot_On_Flag();
EXT INT16U Read_Def_Para(STORA_DI SDI, void* pDst, INT16U Len, void* pDst_Start, INT16U DstLen);
#endif
