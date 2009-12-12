#ifndef MEMORY_H
#define MEMORY_H

#undef EXT
#ifdef MEMORY_C
#define EXT
#else
#define EXT extern
#endif

#define MAX_INIT_CLR_DOG_COUTS 20000
#define MAX_IIC_ERR_RETRY  5

EXT volatile INT8U Rom_Err_Flag;//������ʶ�ĸ�ROM�����˴���

EXT INT8U Check_PHY_Mem();
EXT INT8U Check_LOG_Mem_Map();
EXT INT32U Get_LOG_Mem_Size(INT8U MemNo);
EXT INT32U Get_PHY_MEM_Size(INT8U MemNo);
EXT INT8U Read_PHY_Mem(INT8U MemNo, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_PHY_Mem(INT8U MemNo, INT32U Offset, void* pSrc, INT16U SrcLen);
EXT INT8U Read_LOG_Mem(INT8U MemNo, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_LOG_Mem(INT8U MemNo, INT32U Offset, void* pSrc, INT16U SrcLen);
EXT INT32U Get_Sys_Mem_Info_CS();
#endif
