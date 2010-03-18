#define PUB_DEBUG_C
#include "includes.h"
#include "OS_Port.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H27"
#endif

extern void OS_vsPrintf(CONST OS_INT8S* format, va_list ap);
extern INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len);

//检查是否允许打印调试信息
INT8U OS_Debug_Print_En()
{
  if(Check_Debug_En() EQ 0)//不是工厂或者调试状态状态不打印
    return 0;
  
  if(OS_Check_Bg_Status() EQ 1 &&\
     OS_Check_Bg_Print_En() EQ 0)
    return 0;
  else 
    return 1;
}
//断言
//x条件不成立时返回1，成立时返回0
//这样可以方便函数中做这样的判断:
//
// if(ASSERT(A_WARNING,x))
//   return 0;
//

//调试信息输出
/*****************************************
函数原型：
INT8U DEBUG_BUF_PRINT(INT8U Src[],INT16U SrcLen,INT8U Flag)
函数功能：
打印调试信息，可以将Src缓冲区中的变量打print出来
入口参数：
Src,源数据缓冲区
SrcLen,源数据长度
Flag,0表示按十六进制方式打印,1表示按十进制方式打印
Num,没Num个数字打一个换行符
出口参数：打印信息长度
******************************************/
void DEBUG_BUF_PRINT(INT8U Src[], INT16U SrcLen, INT8U Flag, INT8U Num)
{
  INT16U i;

  //if(Check_Debug_En() EQ 0)//不是工厂状态不打印
    //return;

  if(OS_Debug_Print_En() EQ 0)
    return;
  
  i = 0;
  if(Flag EQ PRINT_HEX) //hex打印
  {
    for(i = 0; i < SrcLen; i++)
    {
      if(Num != 0 && i % Num EQ 0)
        OS_Debug_Print("\r\n");

      OS_Debug_Print("%2x ", Src[i]);
    }
  }
  else//%d
  {
    for(i = 0; i < SrcLen; i++)
    {
      if(Num != 0 && i % Num EQ 0)
        OS_Debug_Print("\r\n");

      OS_Debug_Print("%3d ", Src[i]);
    }
  }
  return;
}

/*****************************************
函数原型：
INT16U DEBUG_PRINT(char *format,...)
函数功能：
打印调试信息，可以将调试信息打印到串口或IAR的i/o窗口中
入口参数：参数列表
出口参数：打印信息长度
******************************************/
void _Debug_Print(char* format, ...)
{
  va_list ap;
  INT8U Task_ID;

  //if(Check_Debug_En() EQ 0)//不是工厂状态不打印
    //return;

  if(OS_Debug_Print_En() EQ 0)
    return;
  
  if(OS_Get_Cur_Task_Num() EQ 0)
  {
    OS_Debug_Print("\r\nMAIN:");
  }
  else
  {
    Task_ID = OS_Get_Cur_Task_ID();
    OS_Debug_Print("\r\n%s:", OS_Get_Task_Name(Task_ID));
  }


  va_start(ap, format);
  OS_vsPrintf(format, ap);
  va_end(ap);
  return;
}

void OS_Put_Char(INT8S c) 
{
  Debug_Out_Public_Puck((INT8U *)&c,1);
}

//时钟Tick钩子函数
void OS_Tick_Hook()
{

}

void Trace(CONST INT8S File[], INT16U Line)
{
  OS_Trace(File,"FUNC",Line); 
}

void Assert(OS_BOOL Condition,CONST OS_INT8S File[],OS_INT16U Line)
{
  OS_Assert(Condition, File, "Func", Line);
}

void Assert_Failed(CONST OS_INT8S File[], OS_INT16U Line)
{
  OS_Assert_Failed(File, "Func", Line); 
}

void OS_Assert_Hook(CONST OS_INT8S File[],CONST OS_INT8S Function[],OS_INT16U Line)
{
  
}

//代码校验错误处理
void Code_License_Err_Proc(const char *pInfo)
{
  Main_Dis_Info((char *)pInfo);
  Beep_For_Para();
}

void Get_Code_ID()
{
  static INT32U Code_ID;
  
  //OS_Debug_Print_Version_Date(); //打印操作系统的时间和版本号
  OS_Get_Code_ID((INT8U *)&Code_ID, (INT8U *)&Code_ID, sizeof(Code_ID));
  
  //Debug_Print("Code_ID: %lx", Code_ID);
}

//初始化过程中检测代码校验是否正确
void Init_Check_Code_License(void)
{
  INT8U i;
  INT32U Code_ID;
  INT8U Mode;
  
  OS_Debug_Print_Version_Date(); //打印操作系统的时间和版本号
  OS_Get_Code_ID((INT8U *)&Code_ID, (INT8U *)&Code_ID, sizeof(Code_ID));
  
  Debug_Print("Code_ID: %lx", Code_ID);
  
  if(OS_Get_Code_License_Flag() EQ CODE_LICENSE_ERR)
  {
    Debug_Print("License_Key Error, System run in debug mode!!!");
  
    for(i = 0; i < 4; i ++)
    {
      Code_License_Err_Proc("DEBUG");
      Clear_All_Dog();
      OS_TimeDly_Ms(200);
    }
  }
  else
  {
    Debug_Print("License_Key correct!!!");    
  }
  
  if(METER_DEBUG_EN > 0) //外部测试版本--可发给客户的测试版本
  {
    Mode = Get_Meter_Hard_Mode();
    if(Mode EQ MODE_FAC || Mode EQ MODE_DEBUG) //工厂或者调试模式
    {
      for(i = 0; i < 4; i ++)
      {
        Code_License_Err_Proc("DEBUG-1");
        Clear_All_Dog();
        OS_TimeDly_Ms(200);
      }
    }
  } 
}

//获得当前表示版本运行信息的办公室
void Debug_Print_Debug_Run_Info()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Counts ={CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;
  INT32U Mins;

  if(Check_Debug_En() EQ 0)//非工厂状态不打印
    return;

  if(Cur_Time0.Time[T_MIN] EQ Min.Var)//每分钟执行一次该函数
    return;

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Counts);
  ASSERT(1 EQ Re);

  Min.Var = Cur_Time0.Time[T_MIN];
  Counts.Var++;
  if(Counts.Var >= 5)//每隔5分钟打印一次当前调试运行时间
  {
    Counts.Var = 0;
    if(OS_Get_Code_License_Flag() EQ CODE_LICENSE_ERR)
    {
      Mins = OS_Get_Debug_Run_Times();
      Debug_Print("This is a Debug Version, Run Mins: %ld", Mins); 
    }
  }
}

#undef PUB_DEBUG_C

