#define PUB_SHELL_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H28"
#endif

#define MAX_RD_MEM_LEN 300

extern INT8U Shell_Read_Mem(INT8U argc, INT8S **argv);
extern INT8U Shell_OS_Info(INT8U argc, INT8S **argv);
extern INT8U Shell_Read_Proto_Data(INT8U argc,INT8S **argv);
extern INT8U Shell_Vitrual_Event(INT8U argc, INT8S **argv);

CONST S_OS_Shell_Cmd Shell_Cmd[] =
{
  {.pName = "echo", .pCmdFunc = &Shell_Bg_Print_Switch},
  {.pName = "mem", .pCmdFunc = &Shell_Read_Mem},
  {.pName = "osinfo", .pCmdFunc = &Shell_OS_Info},
  {.pName = "rd", .pCmdFunc = &Shell_Read_Proto_Data},
  {.pName = "event", .pCmdFunc = &Shell_Vitrual_Event}
};

//后台打印开关echo 0表示关后台打印,echo 1表示打开后台打印，echo ?表示后台打印开关状态
INT8U Shell_Bg_Print_Switch(INT8U argc, INT8S **argv)
{
  if(*(argv[0]) EQ '0')
     OS_Set_Bg_Print_Flag(0);
  else if(*(argv[0]) EQ '1')
     OS_Set_Bg_Print_Flag(1);
  else if(*(argv[0]) EQ '?')
  {
    OS_Debug_Print("echo status %s",\
      (OS_Check_Bg_Print_En() > 0)?"On":"Off"); 
  }
  else
  {
    OS_Debug_Print("Cmd format error!"); 
  }
  return 1;
}

//打印操作系统信息
INT8U Shell_OS_Info(INT8U argc, INT8S **argv)
{
  OS_Info_Print();
  return 1;
}

//打印数据
void Shell_Print_Data(INT32U Addr, INT8U *p, INT16U Len)
{
  INT16U i;
  
  for(i = 0; i < Len && i < MAX_RD_MEM_LEN; i ++)
  {
    if((i % 16) EQ 0)
      OS_Debug_Print("\r\n%8lx:", Addr + i);
    
    if(*p < 0x10)
      OS_Debug_Print("0");
    OS_Debug_Print("%x ",*p);
    p ++;
  }  
  
}

//通过shell读取内存和rom数据,argv[0]表示内存ID，0表示ram，0以上表示rom
//argv[1]表示地址
//argv[2]表示长度
INT8U Shell_Read_Mem(INT8U argc, INT8S **argv)
{
  INT32U Mem_No, Addr, Len;
  INT8U *p, Re;
  
  if(argc != 3)
  {
    OS_Debug_Print("Cmd format error!");
    return 0;
  }
  
  Mem_No = atoi(argv[0]);
  Addr = atol(argv[1]);
  Len = atol(argv[2]);
  
  OS_Debug_Print("\r\nMem_No:%lu, Addr:%lu, Len:%lu\r\n", Mem_No, Addr, Len);

  if(Len > MAX_RD_MEM_LEN)
    Len = MAX_RD_MEM_LEN;
    
  if(Mem_No EQ 0)
    p = (INT8U *)Addr;
  else
  {
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    
    Re = Read_PHY_Mem_PUCK(Mem_No - 1, Addr, (INT8U *)Pub_Buf0, Len, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
    if(Re EQ 0)
      Len = 0;
    
    p = (INT8U *)Pub_Buf0;
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
  }
  
  Shell_Print_Data(Addr, p, Len);
  
  return 1;
}

//通过shell读取协议数据，argv[0]表示协议ID，字符串
INT8U Shell_Read_Proto_Data(INT8U argc, INT8S **argv)
{
  INT8S *p;
  INT16U Len;
  INT32S PDI;
  
  if(argc != 1)
  {
    OS_Debug_Print("Cmd format error"); 
    return 0;
  }
  
  PDI = strtol(argv[0], &p, 16);
  //Hex2Bcd(PDI, (INT8U *)&PDI, 4, (INT8U *)&PDI, sizeof(PDI));
  Len = Get_DLT645_Data((INT32U)PDI, (INT8U *)Temp_Buf_PUCK, (INT8U *)Temp_Buf_PUCK, sizeof(Temp_Buf_PUCK));
  
  OS_Debug_Print("\r\n\r\nLen = %d\r\n", Len);  
  if(Len > 0)
    Shell_Print_Data(0, (INT8U *)Temp_Buf_PUCK, Len);
  else
    OS_Debug_Print("Read data error");
  return 1;
  
}

//虚拟时间的发生，用于调试
INT8U Shell_Vitrual_Event(INT8U argc, INT8S **argv)
{
  INT8U Event_ID;
  INT8U Occur_Flag;
  
  if(argc != 2)
  {
    OS_Debug_Print("Cmd format error");
    return 0;
  }
  
  Event_ID = atoi(argv[0]);
  Occur_Flag = (atoi(argv[1]) EQ 0)?EVENT_OCCUR:EVENT_END;
  Event_Data_Proc(Event_ID, Occur_Flag);
  return 1;
  
}

/*
#define SHELL_REC_MAX_LEN UART0_RX_BUFF_MAXSIZE   // shell buf 最大长度
#define SHELL_REC_CUR_LEN Uart0_Rx_Count          //当前 shell buf 收到的字节长度
#define SHELL_REC_BUF Uart0_RecBuf                //当前 shell的 buf
*/
void Shell_Proc()
{
#if SHELL_EN > 0
  INT8U Re;
  
  if(Check_Debug_En() EQ 0)
    return;
  
  Re = OS_Cmd_Analys(Shell_Cmd, S_NUM(Shell_Cmd), (INT8S *)SHELL_REC_BUF, (20 < SHELL_REC_MAX_LEN)?20:SHELL_REC_MAX_LEN);
  if(Re EQ 1)
  {
    SHELL_CLR_BUF();
  }
#endif
}
#undef PUB_SHELL_C
