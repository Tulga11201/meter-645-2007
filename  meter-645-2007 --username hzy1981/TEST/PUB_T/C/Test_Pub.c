#define TEST_PUB_C
#include "Includes.h"
#ifdef TEST_MODE

extern INT8U Test_Get_Next_Settle_Time();
extern INT8U Test_Settle_Settle_Data();
extern INT8U Test_Get_DLT645_Data();
extern void Init_EEROM();

void Test_Func(INT8U (*pFunc)(),INT8U Func_Name[])
{
  DEBUG_PRINT(TEST,DEBUG_0,"%s Test Start!",Func_Name);
  if((*pFunc)()!=0)
    DEBUG_PRINT(TEST,DEBUG_0,"%s Test OK!",Func_Name);
  else
    DEBUG_PRINT(TEST,DEBUG_0,"%s Test Failed!",Func_Name);
  
}

void Test_Unit()
{
	Init_EEROM();
	//TEST_FUNC(&Test_Get_Next_Settle_Time);
	//TEST_FUNC(&Test_Settle_Settle_Data);
	TEST_FUNC(&Test_Get_DLT645_Data);
}

void Test_Proc(INT8U Flag)
{
  if(Flag==1)
    return;
  
  //while(1)
  {
    //TEST_FUNC(&Test_A_Loss_Vol); 
    //TEST_FUNC(&Test_Freeze_Energy_Data);
    OS_TimeDly_Ms(100);
  }
  
}
#endif
#undef TEST_PUB_C
