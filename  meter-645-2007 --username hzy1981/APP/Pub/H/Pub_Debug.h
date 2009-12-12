#ifndef PUB_DEBUG_H
#define PUB_DEBUG_H

#include "Pub.h"

#undef EXT
#ifdef PUB_DEBUG_C
#define EXT
#else
#define EXT extern
#endif

//定义调试信息输出方式
#define PRINT_NULL  0 //不输出
#define PRINT_STDIO 1 //标准I/O输出
#define PRINT_UART  2 //串口输出

#define PRINT_TYPE PRINT_STDIO //暂定为标准IO输出

//定义打印缓冲时的打印格式
#define PRINT_HEX 0 //16进制打印
#define PRINT_DEC 1 //10进制打印

//定义调试信息的重要等级
#define DEBUG_0 0
#define DEBUG_1 1
#define DEBUG_2 2
#define DEBUG_3 3 

//定义调试信息输出者ID,修改此处时请注意修改PARA_ID_NUM
#define ASSERT_ID 0
#define TEST 1
#define HUCK 2
#define SUCK 3
#define PUCK 4
#define LUCK 5

#define A_RST 0 //表示断言中的条件不成立的话，复位
#define A_WARNING 1//表示断言中条件不成立的话，只输出调试信息，然后返回1

#define PRINT_DEBUG_ON  0xAA
#define PRINT_DEBUG_OFF 0xEE

#define Debug_Print(...)
//#define Debug_Print _Debug_Print

EXT void _Debug_Print(char* format, ...);
EXT void DEBUG_BUF_PRINT(INT8U Src[], INT16U SrcLen, INT8U Flag, INT8U Num);
EXT void OS_Put_Char(INT8S c);
EXT void Trace(CONST INT8S File[], INT16U Line);
EXT void Assert(OS_BOOL Condition,CONST OS_INT8S File[],OS_INT16U Line);
EXT void Assert_Failed(CONST OS_INT8S File[],OS_INT16U Line);
EXT void Code_License_Stop_Proc(void);
EXT void Get_Code_ID();
EXT void Init_Check_Code_License(void);
EXT void Debug_Print_Debug_Run_Info();
#endif
