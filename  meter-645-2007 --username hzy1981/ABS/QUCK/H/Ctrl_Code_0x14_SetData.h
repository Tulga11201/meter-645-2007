
#ifndef CTRL_CODE_0X14_SETDATA_H_
#define CTRL_CODE_0X14_SETDATA_H_
 
//写数据时的esam权限判断和密文解密
//Type为1、2，分别表示1类数据和2类数据
//pSrc表示通信协议中的数据域 N1-Nm + 4字节MAC，详见协议描述
//SrcLen表示源数据长度
//pDst表示解密后的数据缓冲区，当Type为1时不需要解密，因此此时该参数无意义
//pDst_Start目标缓冲起始地址
//DstLen 目标缓冲区的长度
//返回值 权限正确且解密成功返回1，否则返回0
//注意：该函数传入的pSrc和pDst可能是同一地址。
INT8U  Esam_Auth_Check(  INT8U *pSrc, INT16U SrcLen, INT8U * DstLen);
 INT8U Set_Esam_Para( INT8U *pSrc, INT8U SrcLen); 


#endif