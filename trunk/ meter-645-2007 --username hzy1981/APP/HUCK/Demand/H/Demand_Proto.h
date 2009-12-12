#ifndef DEMAND_PROTO_H
#define DEMAND_PROTO_H

#undef EXT
#ifdef DEMAND_PROTO_C
#define EXT
#else
#define EXT extern
#endif

EXT INT16U Get_Demand_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);

#endif
