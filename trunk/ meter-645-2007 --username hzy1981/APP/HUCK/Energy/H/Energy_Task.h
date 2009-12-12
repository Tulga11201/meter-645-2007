#ifndef ENERGY_TASK_H
#define ENERGY_TASK_H

#include "Demand.h"

#undef EXT
#ifdef ENERGY_TASK_C
#define EXT
#else
#define EXT extern
#endif

typedef struct
{
    INT32U Chk_Flag;
    INT8U CS[CS_BYTES];
}S_Chk_Data_Flag;

typedef struct
{
    S_HEX_Time PD_Time; //掉电时间 
    //S_Demand_Exceed_Limit Demand_Exceed_Limit;//需量越限
}S_PD_Save_Data;

EXT volatile S_Chk_Data_Flag Chk_Data_Flag;

EXT void PowerOn_Wait_Measure_Inited();
EXT void PowerOn_Data_Proc();
EXT void PowerOn_Read_Data_From_Rom();
EXT void PowerOn_Read_Para_From_Rom();
EXT void PD_Save_Data_Proc();
EXT void Init_Mutex();
EXT void Set_Clear_Data_Result(INT8U Re);
EXT INT8U Get_Clear_Data_Result();
#endif

