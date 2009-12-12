#ifndef EVENT_DATA_H
#define EVENT_DATA_H

#include "InterrAbs.h"

#undef EXT
#ifndef EVENT_DATA_C
#define EXT extern
#else
#define EXT
#endif


typedef struct 
{
	INT8U Op_ID[4];//����ԱID
        INT8U Last_Op_ID[4];//ǰһ�β���ԱID
	INT8U CS[CS_BYTES];
}S_Operator_ID;

//ĳ�����ݱ�̱�־ 
typedef struct
{
  INT8U All_Flag:1; //�ܵļ�¼ 
  INT8U Date_Flag:1;
  INT8U Year_Flag:1;
  INT8U Week_Flag:1;
  INT8U Holiday_Flag:1;
  INT8U SettleDay_Flag:1;
  INT8U ActComm_Flag:1;
  INT8U ReacComm1_Flag:1;
  INT8U ReacComm2_Flag:1;
  
  //INT8U CS[CS_BYTES];
}S_Prog_Flag;

typedef struct  
{
	PROTO_DI PDI[10];
        INT8U Op_ID[4];
        INT8U Time[6]; //���ʱ��
	//INT8U Posi;
        //INT8U Mins;//�ӵ�һ������������10��������Ϊ��һ����̼�¼
        //INT8U Event_Flag; //�¼���־
        S_Prog_Flag Prog_Flag; //��̱�־,��һ������������Ƿ��й���̵ı�־
        INT8U Prog_Status; //�Ƿ��ڱ��״̬
	INT8U CS[CS_BYTES];
}S_Prog_Record;

typedef struct
{
    INT32U Var;
    INT8U Time[6];//�롢�֡�ʱ���ա��¡���
}S_Event_Demand_Time;

typedef struct
{
    INT8U Pos_Active_Flag;//��ǰ���г��ޱ�־
    INT8U Neg_Active_Flag;//��ǰ���г��ޱ�־ 
    INT8U Quad_Reac_Flag[4]; //��ǰ�������޹����ޱ�־
    
    S_Event_Demand_Time Pos_Active;
    S_Event_Demand_Time Neg_Active;
    S_Event_Demand_Time Quad_Reactive[4];
	
    INT8U CS[CS_BYTES];
}S_Demand_Exceed_Limit;


typedef struct
{
    INT8U Head;
    INT8U Err_Counts;          //����������
    //INT16U Clr_Err_Counts_Mins; //��������ʣ��ʱ��
    INT16U Lock_Mins;          //����ʱ�䣬���ǽ���ʣ��ʱ��
    INT8U Set_En_Mins;         //������֤��ȷ����������ʱ��
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_PSW_Err_Info;

typedef struct
{
  S_HEX_Time Hour_Freeze_Time;
  S_HEX_Time Date_Freeze_Time;
  INT8U CS[CS_BYTES];
}S_Last_Freeze_Time;

typedef struct
{
    INT32U Min_Timer;
    INT8U Temp0;
    
    INT8U PD_Flag; //�Ƿ���������?1��ʾȷʵ�����˵��磬0��ʾû��
    INT8U Temp1;
    
    EVENT_INSTANT_STATUS Meter_Instant_Status;//�¼�״̬��Ϣ
    INT8U Temp2;//���ñ�֤����Ľṹ�����

    S_Demand_Exceed_Limit _Demand_Exceed_Limit;//����Խ�޼�¼
    INT8U Temp3;
    
    S_PSW_Err_Info _PSW_Err_Info;
    INT8U Temp4;
    
    S_Last_Freeze_Time _Last_Freeze_Time;//�ϴ�Сʱ������ն���ʱ��
    INT8U Temp5;
    
    S_BCD_Time _Last_Adj_Time;//ǰһ��У��ʱ��
    INT8U _Adj_Time_Counts; //Уʱ����
    INT8U Temp6;

    BAT_STATUS Bat_Work_Status;
    INT8U Temp7;
    
    S_Prog_Record _Prog_Record; //��̼�¼
    INT8U Temp8;
    
    NOT_EVEN_DATA Not_Even_Data;//��ƽ����    
    INT8U Temp9;
    
    PRG_KEY_STATUS Prg_Key_Status; //���״̬
    INT8U Temp10;
//----------���¼�ʱǰ��Ŀ����������Ĳ�Ӧ����---------
    PROTO_DI _Clear_Event_PDI; //����¼���DI
    INT8U Temp11;

    S_Operator_ID _Operator_ID; //������ID
    INT8U Temp12;
    
    S_BCD_Time Time;
    
    INT8U Relay_Status;
    //INT8U Temp13;
 
    INT8U CS[CS_BYTES];
}S_Event_Data;

EXT volatile S_Event_Data Event_Data;

#define Operator_ID Event_Data._Operator_ID
#define Prog_Record Event_Data._Prog_Record
#define Demand_Exceed_Limit Event_Data._Demand_Exceed_Limit
#define PSW_Err_Info Event_Data._PSW_Err_Info
#define Last_Freeze_Time Event_Data._Last_Freeze_Time
#define Last_Adj_Time Event_Data._Last_Adj_Time //ǰһ��У��ʱ��
#define Adj_Time_Counts Event_Data._Adj_Time_Counts
#define Clear_Event_PDI Event_Data._Clear_Event_PDI


EXT void Check_Event_Data_Avail();
EXT INT8U Check_Event_Occuring(INT8U Event_ID);
EXT void Event_Data_Proc(INT8U Event_ID,INT8U Occur_Or_End);
EXT void All_Loss_Vol_Counts_Time_Proc(INT32U Counts,INT32U Mins);
EXT INT8U Get_Event_Total_Occuring_Singles(INT8U Event_ID);
EXT void All_Loss_Vol_Data_Proc(INT8U Start_Time[],INT8U End_Time[]);
EXT void Set_Event_PD_Time(S_HEX_Time *pTime);
EXT void Clear_Event_Data(PROTO_DI Clr_PDI);
EXT void Clear_Data_End();
EXT void Set_Def_Event_Data();
EXT void Save_Event_PD_Data();
EXT void PowerOn_Event_Proc();
EXT void Wait_Event_Data_Proc_End(INT8U Event_ID);
EXT void Set_Def_Event_PD_Data();
#endif

