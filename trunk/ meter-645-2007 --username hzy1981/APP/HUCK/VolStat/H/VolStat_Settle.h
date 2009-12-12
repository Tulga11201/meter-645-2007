#ifndef VOLSTAT_SETTLE_H
#define VOLSTAT_SETTLE_H

#undef EXT
#ifdef VOLSTAT_SETTL_C
#define EXT
#else
#define EXT extern
#endif

#define INC_VOLSTAT_SETTLE_DI(SDI) do{SDI ++;\
      if(SDI >= _SDI_SETTLE_VOLSTAT_DATA + MAX_VOLSTAT_SETTLE_NUM)\
      SDI = _SDI_SETTLE_VOLSTAT_DATA;}while(0)

EXT STORA_DI Read_Last_Settle_VolStat_DI();
EXT INT16U Read_His_VolStat_Data(INT8U Bef_Counts, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT void Get_Last_VolStat_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Get_N_Last_VolStat_Settle_Time(INT8U N, S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Settle_VolStat_Data(S_HEX_Time* pTime);
EXT INT8U Check_Volstat_Settle_Time(S_BCD_Time* pTime);
EXT INT8U Write_His_VolStat_Data(S_HEX_Time* pTime, void* pSrc, INT16U SrcLen);
EXT void PowerOn_Settle_VolStat_Data();
#endif