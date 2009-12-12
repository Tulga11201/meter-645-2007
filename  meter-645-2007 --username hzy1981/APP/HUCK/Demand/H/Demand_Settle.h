#ifndef DEMAND_SETTLE_H
#define DEMAND_SETTLE_H

#undef EXT
#ifndef DEMAND_SETTLE_C
#define EXT extern
#else
#define EXT
#endif

#define INC_DEMAND_SETTLE_DI(SDI) do{SDI ++;\
      if(SDI >= _SDI_SETTLE_DEMAND_DATA + MAX_DEMAND_SETTLE_NUM)\
      SDI = _SDI_SETTLE_DEMAND_DATA;}while(0)

EXT void Write_Demand_Time(STORA_DI SDI, S_HEX_Time* pTime);
EXT void Write_Demand_Rate_Data(STORA_DI SDI, INT8U Rate, void* pSrc, INT16U SrcLen);
EXT void Settle_Demand_Data(S_HEX_Time* pTime);
EXT void Write_Demand_Phase_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen);
EXT INT16U Read_His_Demand_Time_Data(INT8U Bef_Counts, S_HEX_Time * pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Read_His_Demand_Rate_Data(INT8U Bef_Counts, INT8U Rate, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Read_His_Demand_Phase_Data(INT8U Bef_Counts, void* pDst, void* pDst_Start, INT16U DstLen);
EXT void Reset_Demand_Rom_Data(STORA_DI SDI, S_HEX_Time* pTime);
EXT void Reset_Demand_Ram_Data();
EXT void Set_Demand_His_Invalid_Data(STORA_DI His_DI);
EXT void PowerOn_Settle_Demand_Data();
#endif
