#ifndef VOLSTAT_H
#define VOLSTAT_H

#undef EXT
#ifdef VOLSTAT_C
#define EXT
#else
#define EXT extern
#endif

#define VOL_RATIO 1000

#define EXAM_UPPER_VOL 2700000
#define EXAM_LOWER_VOL 1700000

typedef struct
{
    INT32U Qual_Upper_Limit;//合格上限
    INT32U Qual_Lower_Limit;//合格下限
    INT32U Exam_Upper_Limit;//考核上限
    INT32U Exam_Lower_Limit;//考核下限
    INT8U CS[CS_BYTES];
}S_VolStat_Para;


typedef struct
{
    INT8U Head;

    S_HEX_Time Time;

    INT8U Temp;//保证上面的Time对齐

    INT32U Total_Time[4];//三相监测总时间,3表示总,0-2分别表示A、B、C三相，
    INT32U Upper_Time[4];//超上时间
    INT32U Lower_Time[4];//超下时间

    INT32U Qual[4];//三相合格率
    INT32U Exam[4];//超限率

    INT32U Max_Vol[4];//最高电压
    INT8U Max_Vol_Time[4][5];//时间，16进制数

    INT32U Min_Vol[4];//最低电压
    INT32U Min_Vol_Time[4][5];//时间，16进制数

    INT32U Data_Ready_Flag;

    INT8U CS[CS_BYTES];

    INT8U Tail;
}S_VolStat;

typedef struct
{
    INT8U Head;
  
    INT8U Sec;
    
    INT8U Qual_Upper[4];
    INT8U Qual_Lower[4];//超合格计数
    INT8U Exam_Upper[4];
    INT8U Exam_Lower[4];//超考核计数  
    
    INT8U CS[CS_BYTES];
    
    INT8U Tail;
}S_VolStat_Count;

EXT NO_INIT volatile S_VolStat Cur_VolStat;//当月电压检测数据
//EXT NO_INIT S_VolStat Total_VolStat;//电压检测总数据
EXT NO_INIT volatile S_VolStat_Para VolStat_Para;//电压统计参数
EXT volatile S_VolStat_Count VolStat_Count;//电压统计计数
//EXT S_Event_Vol_Cur Event_Vol_Cur;

EXT INT8U Check_VolStat_Data(S_VolStat* pVolStat);
EXT void Check_VolStat_Para_Avail();
EXT void Check_VolStat_Data_Avail();

EXT void Freeze_VolStat_Data(S_HEX_Time* pTime);
EXT void Save_Cur_VolStat_PD_Data();
EXT void Save_Cur_VolStat_Data();
EXT void Vol_Stat_Proc();
EXT void Set_Def_Cur_VolStat_Data();
EXT void Set_Def_VolStat_Data();
EXT void Read_VolStat_Data_From_Rom();
EXT void PowerDown_Save_VolStat_Data();
EXT void PowerOn_VolStat_Data_Freeze();
EXT void Read_VolStat_Para_From_Rom();
EXT void Clear_VolStat_Data();
EXT INT8U Clear_Proto_Phase_VolStat_Data(PROTO_DI PDI);
EXT void Clear_Cur_VolStat_Ram();
EXT void Clear_VolStat_Count_Ram();
EXT void VolStat_Proc();
EXT void Init_VolStat_Ram_Para();
#endif
