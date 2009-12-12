#ifndef EVENT_Separate_H
#define EVENT_Separate_H

//#include "Include_PUCK.h"

#undef EXT
#ifndef EVENT_SEPARATE_C
#define EXT extern
#else
#define EXT
#endif

#define MAX_EVENT_Separate_NUM 30

#define NULL_EVENT_STORA_DI 0xFF00FF00

#define FREEZE_DATA_MAX_LEN (5 + 4 * (MAX_RATES + 1) * 8 + 8 * (MAX_RATES + 1) * 2 + 24)

#define ONE_RECORD_EVENT 0
#define MULTI_RECORD_EVENT 1

#define EVENT_OCCUR 0x5A//表示事件发生,该数据
#define EVENT_END 0xA5//表示事件的结束，这两个宏主要是针对CONTIN_EVENT类型的事件

#define ID_EVENT_TOTAL_LOSS_VOL   0xD0//总失压事件
#define ID_EVENT_TOTAL_LOSS_CUR   0xD1//总失流事件
#define ID_EVENT_TOTAL_NEG_CUR    0xD2//总反向事件
#define ID_EVENT_TOTAL_BREAK_VOL  0xD3//总断相事件
#define ID_EVENT_PERIOD_FREEZE      0xD4 //周期冻结
#define ID_EVENT_INSTANT_FREEZE     0xD5 //瞬时冻结

#define ID_EVENT_YEAR_TABLE_SWITCH_FREEZE     0xD6 //年时区表切换 
#define ID_EVENT_DATE_TABLE_SWITCH_FREEZE     0xD7 //日时段表切换
#define ID_EVENT_RATE_SCH_SWITCH_FREEZE       0xD8 //费率方案切换
#define ID_EVENT_STEP_SCH_SWITCH_FREEZE          0xD9 //两套梯度切换

#define ID_EVENT_DATE_FREEZ         0xDA//(ID_EVENT_Q4_REAC_DEMAND_EXCEED+1)         //日冻结--------97
#define ID_EVENT_HOUR_FREEZ         0xDB//(ID_DATE_FREEZ+1)                        //小时冻结--------98

#define ID_EVENT_ENERGY_OVERTURN_FREEZE 0xDC //电量翻转冻结

#define ID_EVENT_PREPAID_ENERGY     0xDD //购电事件--电量型
#define ID_EVENT_PREPAID_MONEY      0xDE //购电事件--电费型

//#define ID_EVENT_FACTOR_LOW         0xDF //总功率因素超下限

#define ID_EVENT_A_LOW_VOLT        0xE0 //A相欠压
#define ID_EVENT_B_LOW_VOLT        0xE1 //B相欠压
#define ID_EVENT_C_LOW_VOLT        0xE2 //C相欠压

//#define ID_EVENT_REMOTE_RELAY_ON  0xDB //远程合闸
//#define ID_EVENT_REMOTE_RELAY_OFF 0xDC //远程拉闸
//#define ID_VOL_STAT           0xDD//电压统计，实际并无此事件，只是为了统一处理清事件记录

/*
#define ID_EVENT_POS_ACT_DEMAND_EXCEED 0xD8//正向有功需量超限
#define ID_EVENT_NEG_ACT_DEMAND_EXCEED 0xD9//反向有功需量超限
#define ID_EVENT_Q1_REAC_DEMAND_EXCEED 0xDA//一象限无功需量超
#define ID_EVENT_Q2_REAC_DEMAND_EXCEED 0xDB//二象限无功需量超
#define ID_EVENT_Q3_REAC_DEMAND_EXCEED 0xDC//三象限无功需量超
#define ID_EVENT_Q4_REAC_DEMAND_EXCEED 0xDD//四象限无功需量超
*/
#define MAX_EVENT_DATA_NUM 56

typedef struct
{
    INT8U Occur_Mask[MAX_EVENT_DATA_NUM/8]; //事件发生数据项屏蔽字,某位为1表示采用某数据项,下同
    INT8U End_Mask[MAX_EVENT_DATA_NUM/8];  //事件结束数据项屏蔽字
    INT8U Diff_Mask[MAX_EVENT_DATA_NUM/8];  //虚拟结束时需要记录的数据项目
    INT8U Data_Num;  //需要记录的数据项个数
    INT16U Data_Len; //报警数据长度
    PROTO_DI const *PDI;//PDI[53]; //需要记录的数据项
}S_Event_DI;

typedef struct
{
	INT32U Mins;
	INT8U Start_Time[6];//秒、分、时、日、月、年
	INT8U End_Time[6];//同上
	INT8U CS[CS_BYTES];  
}S_All_Loss_Vol_Time;

typedef struct
{
    INT8U Event_ID;    //事件记录的ID
    //定义数据生成相关信息
    //INT8U Property;    //事件记录属性

    S_Event_DI const *pData;

    //PROTO_DI Proto_DI;//最近一次该事件发生的协议DI
    // 当事件为OCCUR_AND_END_EVENT类事件时，因为发生和结束都在一个协议DI里面，所以
    // 只需用该DI表示该事件的DI
    //PROTO_DI End_DI;  //最近一次该事件结束的协议DI,当事件为OCCUR_AND_END_EVENT类事件时该DI没有作用
    // 当时间为OCCUR_OR_END_EVENT类事件时该DI表示事件结束的协议DI

    // 定义存储相关的信息
    STORA_DI Last_SDI;
    //存储最近一次事件的存储DI,其存储的内容为 Start_DI->Start_DI+Num
    STORA_DI SDI;
    INT16U Storage_Num;//该事件共存储多少条记录

    INT8U Clr_Flag; //0表示不允许清除该事件，1表示允许清除
}S_Event_Separate_Data_Info;

typedef struct  
{
	INT8U Head;

	INT8U Time[6];
	INT8U Tail;
}S_PD_Time;

//extern CONST S_Event_Separate_Data_Info Event_Data_Info[];
extern CONST S_Event_Separate_Data_Info Event_Separate_Data_Info[];

EXT volatile S_All_Loss_Vol_Time All_Loss_Vol_Time;//最近一次全失压的发生和结婚时间,用于生成协议数据


EXT INT16U Get_Event_Data_Index(INT8U Event_ID);
EXT INT16U Get_Event_Data_Index_From_DI(PROTO_DI PDI);
EXT STORA_DI Read_Last_Event_Storage_DI(INT8U Event_ID);
EXT INT16U Get_Event_Separate_Data_Index(INT8U Event_ID);
EXT INT16U Read_Last_Event_Data(INT8U Event_ID, STORA_DI Storage_DI, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT16U Event_Separate_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag);
EXT INT16U Get_Separate_Event_Num();
EXT INT16U Get_Event_Separate_Proto_Index(PROTO_DI PDI);
//EXT void Clear_Event_Data();
EXT void Set_Def_Event_Separate_Data();
EXT void Clear_Event_Separate_Data();
EXT INT8U Clear_One_Event_Separate_Data(INT8U Event_ID);
EXT INT8U Check_Event_Clr_PDI(PROTO_DI PDI);
#endif

