#define PUB_DEBUG_C
#include "includes.h"
#include "OS_Port.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H27"
#endif

extern void OS_vsPrintf(CONST OS_INT8S* format, va_list ap);
extern INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len);

//����Ƿ������ӡ������Ϣ
INT8U OS_Debug_Print_En()
{
  if(Check_Debug_En() EQ 0)//���ǹ������ߵ���״̬״̬����ӡ
    return 0;
  
  if(OS_Check_Bg_Status() EQ 1 &&\
     OS_Check_Bg_Print_En() EQ 0)
    return 0;
  else 
    return 1;
}
//����
//x����������ʱ����1������ʱ����0
//�������Է��㺯�������������ж�:
//
// if(ASSERT(A_WARNING,x))
//   return 0;
//

//������Ϣ���
/*****************************************
����ԭ�ͣ�
INT8U DEBUG_BUF_PRINT(INT8U Src[],INT16U SrcLen,INT8U Flag)
�������ܣ�
��ӡ������Ϣ�����Խ�Src�������еı�����print����
��ڲ�����
Src,Դ���ݻ�����
SrcLen,Դ���ݳ���
Flag,0��ʾ��ʮ�����Ʒ�ʽ��ӡ,1��ʾ��ʮ���Ʒ�ʽ��ӡ
Num,ûNum�����ִ�һ�����з�
���ڲ�������ӡ��Ϣ����
******************************************/
void DEBUG_BUF_PRINT(INT8U Src[], INT16U SrcLen, INT8U Flag, INT8U Num)
{
  INT16U i;

  //if(Check_Debug_En() EQ 0)//���ǹ���״̬����ӡ
    //return;

  if(OS_Debug_Print_En() EQ 0)
    return;
  
  i = 0;
  if(Flag EQ PRINT_HEX) //hex��ӡ
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
����ԭ�ͣ�
INT16U DEBUG_PRINT(char *format,...)
�������ܣ�
��ӡ������Ϣ�����Խ�������Ϣ��ӡ�����ڻ�IAR��i/o������
��ڲ����������б�
���ڲ�������ӡ��Ϣ����
******************************************/
void _Debug_Print(char* format, ...)
{
  va_list ap;
  INT8U Task_ID;

  //if(Check_Debug_En() EQ 0)//���ǹ���״̬����ӡ
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

//ʱ��Tick���Ӻ���
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

//����У�������
void Code_License_Err_Proc(const char *pInfo)
{
  Main_Dis_Info((char *)pInfo);
  Beep_For_Para();
}

void Get_Code_ID()
{
  static INT32U Code_ID;
  
  //OS_Debug_Print_Version_Date(); //��ӡ����ϵͳ��ʱ��Ͱ汾��
  OS_Get_Code_ID((INT8U *)&Code_ID, (INT8U *)&Code_ID, sizeof(Code_ID));
  
  //Debug_Print("Code_ID: %lx", Code_ID);
}

//��ʼ�������м�����У���Ƿ���ȷ
void Init_Check_Code_License(void)
{
  INT8U i;
  INT32U Code_ID;
  INT8U Mode;
  
  OS_Debug_Print_Version_Date(); //��ӡ����ϵͳ��ʱ��Ͱ汾��
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
  
  if(METER_DEBUG_EN > 0) //�ⲿ���԰汾--�ɷ����ͻ��Ĳ��԰汾
  {
    Mode = Get_Meter_Hard_Mode();
    if(Mode EQ MODE_FAC || Mode EQ MODE_DEBUG) //�������ߵ���ģʽ
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

//��õ�ǰ��ʾ�汾������Ϣ�İ칫��
void Debug_Print_Debug_Run_Info()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Counts ={CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;
  INT32U Mins;

  if(Check_Debug_En() EQ 0)//�ǹ���״̬����ӡ
    return;

  if(Cur_Time0.Time[T_MIN] EQ Min.Var)//ÿ����ִ��һ�θú���
    return;

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Counts);
  ASSERT(1 EQ Re);

  Min.Var = Cur_Time0.Time[T_MIN];
  Counts.Var++;
  if(Counts.Var >= 5)//ÿ��5���Ӵ�ӡһ�ε�ǰ��������ʱ��
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

