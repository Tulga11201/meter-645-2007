#ifndef CLOCK_PROTO_H
#define CLOCK_PROTO_H

#undef EXT
#ifdef CLOCK_PROTO_C
#define EXT
#else
#define EXT extern
#endif

EXT INT16U Get_Clock_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT8U Set_Clock_Proto_Data(PROTO_DI PDI, INT8U *pSrc, INT16U SrcLen);
#endif
