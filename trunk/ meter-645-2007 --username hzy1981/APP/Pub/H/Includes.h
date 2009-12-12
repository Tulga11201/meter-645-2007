#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <setjmp.h>

#include "Meter_Cfg.h"
#include "OS_Includes.h"

#include "Pub_Sem.h"
#include "Pub.h"
#include "Test_Pub.h"
//#include "HAL.h"

#include "Clock.h"
#include "Pub_Err.h"
#include "Pub_Time.h"
#include "Pub_Debug.h"
#include "Pub_Shell.h"

//#include "Pub_Puck.h"

#include "Mem_Cfg.h"

#ifdef COMPLIER_VC 
#include "HAL.h"
#endif

#include "Event_Separate.h"
#include "Event_Cumu.h"
#include "Clock_Proto.h"
#include "Event_Proto.h"
#include "Event_Data.h"
#include "Freeze_Proto.h"

#include "VolStat.h"
#include "Sys_Memory.h"

#include "Def_Para.h"
#include "Energy.h"
#include "Prepaid.h"
#include "Energy_Task.h"
#include "Demand.h"
#include "VolStat.h"
#include "Energy_Proto.h"
#include "Demand_Proto.h"
#include "VolStat_Proto.h"
#include "VolStat_Settle.h"
#include "Power_Ctrl.h"

#include "Authority.h"
#include "Data_Trans.h"
#include "Load_Data.h"

#include "Data_Para.h"

#include "Freeze_Data.h"



#include "Proto_DI.h"
#include "Authority.h"
#include "Event_Data.h"
//#include "His_Data.h"
#include "Sys_Monitor.h"
#include "Power_Ctrl.h"
#include "Low_Power.h"
#include "Pub_Puck.h"
#include "TaskProc.h"
#ifdef TEST_MODE
#include "Test_Pub.h"
//#include "Test_Event_Data.h"
#endif

//#include <string.h>
//#include <stdio.h>


#include "Extend.h"
#include "645_1997.h"
//#include "HIS_Data.h"
#include "Energy_Settle.h"
#include "Demand_Settle.h"
/*
#include "CpucardBase.h"
#include "AllCardOperation.h"
#include "AllCardOperationDef.h"

#include "BuyCard.h"
#include "pay_def.h"
#include "Cpucard_Driver.h"
*/
#include "MyIncludesAll.h"
//#endif
#endif
