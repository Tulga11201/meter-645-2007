#ifndef MEM_ABS_H
#define MEM_ABS_H



#ifndef MEM_ABS_PUCK
#define MEM_ABS_PUCK_EXT  extern volatile
#else
#define MEM_ABS_PUCK_EXT volatile
#endif


INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen);
INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen);

#endif
