#ifndef OS_SHELL_H
#define OS_SHELL_H

#if OS_SHELL_EN > 0

#undef OS_EXT
#ifndef OS_SHELL_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

#define BG_PRINT_ON  0xAA
#define BG_PRINT_OFF 0xEE

#define SHELL_IN  0x33
#define SHELL_OUT 0x88

typedef struct{
  OS_INT8S *pName;
  OS_INT8U (*pCmdFunc)(OS_INT8U Argc,OS_INT8S **Argv);
}S_OS_Shell_Cmd;

//以下用于调试信息的输出控制
typedef struct
{
  OS_INT8U Head;
  
  OS_INT8U Bg_Print_Flag; //后台打印开关
  OS_INT8U Shell_Flag;    //当前是否在shell运行中
  OS_INT8U Shell_Task_ID; //当前运行shell的任务号
  
  OS_INT8U Tail;
}S_OS_Shell_Status;

OS_EXT volatile S_OS_Shell_Status OS_Shell_Status;

#ifdef OS_SHELL_C
OS_EXT volatile S_OS_Shell_Status OS_Shell_Status = {CHK_BYTE, BG_PRINT_ON, SHELL_OUT, 0, CHK_BYTE};
#endif

OS_EXT void OS_Shell_Init(OS_INT8U Bg_Print_Flag);
OS_EXT OS_INT8U OS_Check_Bg_Status(void);
OS_EXT OS_INT8U OS_Check_Bg_Print_En(void);
OS_EXT void OS_Set_Bg_Print_Flag(OS_INT8U Flag);
OS_EXT OS_INT8U OS_Cmd_Analys(CONST S_OS_Shell_Cmd Shell_Cmd[], OS_INT8U Num, OS_INT8S Cmd[], OS_INT8U Len);
#endif

#endif
