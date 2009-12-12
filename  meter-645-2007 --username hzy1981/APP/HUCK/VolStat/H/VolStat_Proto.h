#ifndef VOLSTAT_PROTO_H
#define VOLSTAT_PROTO_H

#undef EXT
#ifdef VOLSTAT_PROTO_C
#define EXT
#else
#define EXT extern
#endif

EXT INT16U Get_VolStat_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);

#endif
