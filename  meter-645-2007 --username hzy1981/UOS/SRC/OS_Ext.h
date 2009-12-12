#ifndef OS_EXT_H
#define OS_EXT_H

#undef OS_EXT
#ifndef OS_EXT_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

#define VERIFY_CODE 0x4DA55DFA

OS_EXT OS_INT8U OS_Check_Task_Stk(OS_INT8U Task_ID);
OS_EXT OS_INT16U OS_Get_Task_Stk_Left(OS_INT8U Task_ID);
OS_EXT OS_INT8U OS_Get_Cur_Task_ID();
OS_EXT OS_INT8U OS_Get_Cur_Task_Num();

#if OS_TASK_NAME_EN>0
OS_EXT OS_INT8S * OS_Get_Task_Name(OS_INT8U Task_ID);
#endif

OS_EXT void OS_Check_Task_Env();
OS_EXT void OS_Task_Info_Check();
OS_EXT void OS_Task_Info_Print();
OS_EXT OS_INT32U OS_Get_Version();

OS_EXT OS_INT32U OS_Get_Debug_Run_Times(void);
OS_EXT void OS_Get_Code_ID(OS_INT8U *pDst, OS_INT8U *pDst_Start, OS_INT16U DstLen);
OS_EXT void OS_Check_Debug_Version(OS_INT32U Verify_Code);
OS_EXT OS_INT8U OS_Check_Code_License();
OS_EXT OS_INT32U OS_Get_Code_License_Flag(void);
OS_EXT void Clr_Ext_Inter_Dog(void);
OS_EXT void OS_Debug_Print_Version_Date();
#endif

