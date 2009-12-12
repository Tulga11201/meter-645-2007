#ifndef PUB_H
#define PUB_H

#include "OS_Port.h"

#undef EXT
#ifdef PUB_C
#define EXT
#else
#define EXT extern
#endif

#define SYS_TRUE 1
#define SYS_FALSE 0

#define EQ ==

#define CONST const   //定义Flash变量
//#define NO_INIT //定义非初始化变量
//定义类型

#define INT32U OS_INT32U
#define INT32S OS_INT32S
#define INT16U OS_INT16U
#define INT16S OS_INT16S
#define INT8U  OS_INT8U
#define INT8S  OS_INT8S
typedef float FP32S;                      
//typedef unsigned long int bool;


#define PROTO_DI OS_INT32U
#define STORA_DI OS_INT32U
//#define NO_INIT //__no_init

//定义结构体数据按字节对齐的开始和结束宏
//使用如下:
//
//DATA_PACKED_BEGIN//从这里开始定义的结构体都是字节对齐的 
//
//...定义需要字节对齐的结构体
//
//DATA_PACKED_END//从下面开始的结构体都恢复原有的对齐方式
//
#define INIT(X,Y) .X=Y//__VA_ARGS__

#define DATA_PACKED_BEGIN
#define DATA_PACKED_END

#define CONST const

#define NULL_1BYTES 0xFF
#define NULL_2BYTES 0xFFFF
#define NULL_4BYTES 0xFFFFFFFF

#define NULL_STORA_DI 0xFFFFFFFF
#define NULL_PROTO_DI 0xFFFFFFFF

//定义某结构体成员相对该结构体起始位置的偏移
#define S_OFF(X,Y) ((INT32U)(&(((X *)0)->Y)))//获得一个结构体的偏移

//取得一个结构体数组变量的成员个数,X为结构体变量名称
#define S_NUM(X) (sizeof(X)/sizeof(X[0]))

//定义设置某个变量的宏方法
#define SET_VAR(X,Y,X_START,X_LEN) do{ASSERT(&(X)>=X_START && &(X)<X_START+X_LEN);X=Y;}while(0)

//定义除法x=y/z,宏内部判断Z!=0
#define DIV(x,y,z) do{ASSERT(z!=0);x=y/z;}while(0)

//head和tail定义为INT16U型是为了确保Buf的首地址处于偶数地址上
#define DECLARE_BUF_TYPE(Type,Len,Name) typedef struct{\
            INT16U Head;\
            Type Buf[Len];\
            INT16U Tail;\
            }Name

#define DECLARE_VAR_TYPE(Type,Name) typedef struct{\
          INT8U Head;\
          Type Var;\
          INT8U Tail;\
          }Name;

//定义各种应用需要的函数
#define ASSERT(x) Assert(x,__FILE__,__LINE__)//OS_ASSERT(x)//
#define ASSERT_FAILED() Assert_Failed(__FILE__,__LINE__)//OS_ASSERT_FAILED()//
#define TRACE() //Trace(__FILE__,__LINE__)

#define SET_BIT(x,y) ((x)|=0x01<<(y))
#define CLR_BIT(x,y) ((x)&=~(0x01<<(y)))
#define GET_BIT(x,y) (((x)>>(y))&0x01)

//对某个变量赋值,必须保证该变量在合法的范围
//对某个带变量下标的数组或者指针赋值,要采用如下宏,以避免对缓冲区的写溢出
//例如通过指针对Test_Buf写数据
//for(i=0;i<100;i++)
// Set_Var(Test_Buf[i],0xaa,Test_Buf,sizeof(Test_Buf))//等同于Test_Buf[i]=0xaa;
#define Set_Var(x,value,start_addr,x_len)\
do\
{  ASSERT((OS_INT8U *)&(x)>=(OS_INT8U *)(start_addr) && (OS_INT8U *)&(x)+sizeof(value)<=(OS_INT8U *)(start_addr)+x_len);\
   x=value;\
}while(0)

//定义除法x=y/z,宏内部判断Z!=0
//#define DIV(x,y,z) do{ASSERT(z!=0);x=y/z;}while(0)

//对内存相关的操作，请采用如下函数，以保证不会产生写溢出
//内存相关函数
#define mem_set OS_memset
#define mem_cpy OS_memcpy

//校验相关函数
#define Check_Sum OS_Check_Sum
#define Set_Sum OS_Set_Sum

//全局变量请全部采用结构体的定义方式，并且该结构体带CS域名,举例:
//typedef struct
//{
//  INT8U a;
//  ...
//  INT8U CS[CS_BYTES];
//}S_test;
//在读取结构体变量前，使用结构体检验函数，检查该结构体是否合法
//修改完该结构体数据后，使用设置检验和函数设置CS域
//对结构体的校验相关函数
#define DATA_READY 0x5AA56734
#define SET_DATA_READY_FLAG(Var) do{Var.Data_Ready_Flag=DATA_READY;}while(0)
#define RESET_DATA_READY_FLAG(Var) do{Var.Data_Ready_Flag=0;}while(0)

#define Check_STRUCT_Sum OS_Check_STRUCT_Sum
#define Set_STRUCT_Sum OS_Set_STRUCT_Sum

#define CHECK_STRUCT_SUM(Var) OS_Check_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)(Var.CS),sizeof(Var.CS))//_Check_STRUCT_Sum((void *)&(Var),(OS_INT8U *)(Var.CS))//
#define SET_STRUCT_SUM(Var) OS_Set_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)(Var.CS),sizeof(Var.CS))//_Set_STRUCT_Sum((void *)&(Var),(OS_INT8U *)(Var.CS))//
//设置某个结构体变量的时间域
#define SET_STRUCT_TIME(Var,Tim)  do{ASSERT(sizeof(Tim)==sizeof(S_HEX_Time));\
          mem_cpy((void *)&(Var.Time),(void *)&(Tim),sizeof(Tim),(void *)&(Var.Time),sizeof(Var.Time));\
          SET_STRUCT_SUM(Var);}while(0)

#define CHECK_STRUCT_VAR(Var) ((CHK_BYTE==Var.Head  && CHK_BYTE==Var.Tail)?1:0)
#define INIT_STRUCT_VAR(Var)  do{Var.Head=CHK_BYTE;Var.Tail=CHK_BYTE;}while(0)


//定义可位寻址的字节类型
typedef struct
{
    INT8U Bit0 : 1;
    INT8U Bit1 : 1;
    INT8U Bit2 : 1;
    INT8U Bit3 : 1;
    INT8U Bit4 : 1;
    INT8U Bit5 : 1;
    INT8U Bit6 : 1;
    INT8U Bit7 : 1;
}S_Bit8;

typedef struct
{
    INT8U Bit0 : 1;
    INT8U Bit1 : 1;
    INT8U Bit2 : 1;
    INT8U Bit3 : 1;
    INT8U Bit4 : 1;
    INT8U Bit5 : 1;
    INT8U Bit6 : 1;
    INT8U Bit7 : 1;
    
    INT8U Bit8 : 1;
    INT8U Bit9 : 1;
    INT8U Bit10 : 1;
    INT8U Bit11 : 1;
    INT8U Bit12 : 1;
    INT8U Bit13 : 1;
    INT8U Bit14 : 1;
    INT8U Bit15 : 1;   
}S_Bit16;

//定义字节与位变量的联合
typedef union
{
    S_Bit8 Bit;
    INT8U Byte;
}U_Byte_Bit;

typedef union
{
    S_Bit16 Bit;
    INT16U Word;
}U_Word_Bit;

//DECLARE_BUF_TYPE(INT8U, 1000, S_Pub_Buf0);
//DECLARE_VAR_TYPE(INT8U, S_Int8U);
//DECLARE_VAR_TYPE(INT16U, S_Int16U);
//DECLARE_VAR_TYPE(INT32U, S_Int32U);

typedef struct
{
    INT8U Head;
    INT32U Sec_Timer;
    INT32U Ms10_Timer;
    INT32U Ms_Timer;
    INT32U Min_Timer;
    INT8U Tail;
}S_Pub_Timer;

EXT volatile S_Pub_Timer Pub_Timer;


#define PUB_BUF_LEN 680//(sizeof(S_Comb_Energy)+100)


DECLARE_BUF_TYPE(INT8U, PUB_BUF_LEN, S_Pub_Buf);
//EXT volatile INT16U Pub_Buf[PUB_BUF_LEN];//从ROM中读取数据时使用该buf
EXT volatile S_Pub_Buf _Pub_Buf;
#define Pub_Buf _Pub_Buf.Buf


#define PUB_BUF0_LEN 700 //起码要有700字节，时段表编程事件记录有680多字节


DECLARE_BUF_TYPE(INT8U, PUB_BUF0_LEN, S_Pub_Buf0);
EXT volatile S_Pub_Buf0 _Pub_Buf0;
#define Pub_Buf0 _Pub_Buf0.Buf

#define Sec_Timer_Pub Pub_Timer.Sec_Timer
#define Ms10_Timer_Pub Pub_Timer.Ms10_Timer
#define Ms_Timer_Pub Pub_Timer.Ms_Timer
#define Min_Timer_Pub Pub_Timer.Min_Timer
/*
EXT volatile INT32U Sec_Timer_Pub;
EXT volatile INT32U Ms10_Timer_Pub;
EXT volatile INT32U Ms_Timer_Pub;
*/
#define MAX_SIZE(a,b,c) ((a)>(b)?(a):(b))>(c)?((a)>(b)?(a):(b)):(c)


//EXT volatile INT16U Pub_Buf0[200];//其他需要大buf的地方使用该buf

EXT INT8U Check_BCD_Data(void* pBCD, INT16U Len);

EXT INT8U GetBufSum_Pub(INT8U Src[], INT16U Src_Len);

EXT void Hex2Bcd(INT32U Data, INT8U* pDst, INT16U Len, INT8U* pDst_Start, INT16U DstLen);
EXT void S_Hex2Bcd(INT32S Data, INT8U* pDst, INT16U Len, INT8U* pDst_Start, INT16U DstLen);
EXT INT32U Bcd2Hex(INT8U Src[], INT8U SrcLen);
EXT INT8U Bcd2Hex_Byte(INT8U Byte);
EXT INT8U Hex2Bcd_Byte(INT8U Byte);
EXT void Bcd_Dec(INT8U Type, INT8U* pData0, INT8U* pData1, INT8U Len, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT void Hex2Bcd_Buf(void* pSrc, INT16U SrcLen, void* pDst, void* pDst_Start, INT16U DstLen);
EXT void Bcd2Hex_Buf(void* pSrc, INT16U SrcLen, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Get_Array_Bit(INT8U Src[], INT8U Bit);
EXT OS_INT8U _Check_STRUCT_Sum(void *pSrc,OS_INT8U *pCS);
EXT void _Set_STRUCT_Sum(void *pSrc,OS_INT8U *pCS);
#endif
