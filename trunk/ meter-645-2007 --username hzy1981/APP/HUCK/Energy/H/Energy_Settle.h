#ifndef ENERGY_SETTLE_H
#define ENERGY_SETTLE_H

#undef EXT
#ifdef ENERGY_SETTLE_C
#define EXT
#else
#define EXT extern
#endif

//定义结算时间,三个结算日
typedef struct
{
    INT8U Time_D_H[3][2];
    INT8U CS[CS_BYTES];
}S_Settle_Time;

DECLARE_VAR_TYPE(S_Settle_Time, _S_Settle_Time);
EXT volatile _S_Settle_Time _Settle_Time;
#define Settle_Time _Settle_Time.Var 

#define INC_ENERGY_SETTLE_DI(SDI) do{SDI ++;\
      if(SDI >= _SDI_SETTLE_ENERGY_DATA + MAX_ENERGY_SETTLE_NUM)\
      SDI = _SDI_SETTLE_ENERGY_DATA;}while(0)

EXT void Read_Settle_Para_From_Rom();
EXT INT8U Get_Last_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Get_Next_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Get_N_Last_Settle_Time(INT8U N, S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Get_N_Next_Settle_Time(INT8U N, S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Read_His_Energy_Data(INT8U Bef_Counts, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT void Settle_Energy_Data(S_HEX_Time* pTime);
EXT void Settle_Energy_FF_Data(INT8U Flag);
EXT void PowerOn_Settle_Energy_Data();
#endif
