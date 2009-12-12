#ifndef CLOCK_H
#define CLOCK_H

#include "Pub_Time.h"

#undef EXT
#ifdef CLOCK_C
#define EXT
#else
#define EXT extern
#endif

#define GET_CLOCK_PERIOD 50//��ȡ�ⲿʱ�����ڣ���δ�øú�

#define USE_EXT_RTC 0
#define USE_INTER_RTC 1

#define T_MIN 0
#define T_HOUR 1
#define T_DATE 2
#define T_MONTH 3
#define T_YEAR 4

/*
//��ǰʱ�䶨��,BCD��ʽ
//Time[0]��
//Time[1]ʱ
//Time[2]��
//Time[3]��
//Time[4]��
typedef struct
{
  INT8U Time[5];
  INT8U Week;//0��ʾ����,1-6�ֱ��ʾ��1->��6
  INT8U CS[CS_BYTES];
}S_HEX_Time;

//ʱ�䶨��ṹ��
typedef struct
{
  INT8U Sec;
  INT8U Min;
  INT8U Hour;
  INT8U Week;//0��ʾ����,1-6�ֱ��ʾ��1->��6
  INT8U Date;
  INT8U Month;
  INT8U Year;
  
  INT8U CS[CS_BYTES];//У���
}S_BCD_Time;
*/
typedef struct
{
  INT8U EXT_RTC_Err_Counts:6;  //�ⲿʱ�Ӵ������
  INT8U Set_INTER_RTC_Flag:1;//�ڲ�ʱ�ӱ����ñ�־��1��ʾ�ڲ�ʱ���������ù�,0��ʾ���ϵ���ڲ�ʱ�ӻ�û�����ù�
  INT8U Clock_Ready_Flag:1;  //ʱ�����ݾ�����־��1��ʾCur_Time0��Cur_Time1�������Ѿ�����
  INT8U CS[CS_BYTES];        //У���
}S_Clock_Info;

typedef struct
{
  INT8U Time[6];//�롢�֡�ʱ���ա��¡���
  INT8U CS[CS_BYTES];
}S_Event_Time;

typedef struct
{
  INT8U Max_Counts;
  INT8U CS[CS_BYTES];
}S_Adj_Time_Para;

EXT NO_INIT volatile S_HEX_Time Cur_Time0;             //��ǰʱ��0
EXT NO_INIT volatile S_Clock_Info Clock_Info;

EXT NO_INIT volatile S_BCD_Time Cur_Time1;             //��ǰʱ��1

EXT volatile S_Adj_Time_Para Adj_Time_Para;  //ÿ��Уʱ����
EXT volatile INT8U RTC_Err_Time[5];//����ʱ��,���ڼ�¼�¼���¼ʱ��
EXT volatile S_Event_Time Cur_Time2;
EXT NO_INIT volatile S_BCD_Time Cur_Time_Bak;          //Cur_Tim1��һ������
EXT volatile S_Event_Time Adj_Bef_Time;  //Уʱǰʱ��
EXT volatile S_Event_Time PD_Time; //ǰ�ε���ʱ��
EXT volatile S_Event_Time PO_Time; //ǰ���ϵ�ʱ��
EXT volatile S_HEX_Time Hex_PD_Time; //����ʱ��

#ifdef CLOCK_C
EXT S_Int32U Time_Modify_Flag = {CHK_BYTE, 0, CHK_BYTE};
EXT S_Int32U Adj_Time_Flag = {CHK_BYTE, 0, CHK_BYTE};
#endif
EXT S_Int32U Time_Modify_Flag;
EXT S_Int32U Adj_Time_Flag;

EXT INT8U _Check_BCD_Time(INT8U Time[]);
EXT INT8U _Check_HEX_Time(INT8U Time[]);

EXT INT8U Check_HEX_Time(S_HEX_Time *pTime);
EXT INT8U Check_BCD_Time(S_BCD_Time *pTime);

EXT void Set_BCD_Time(INT8U Time[],S_BCD_Time *pBCD_Time);

EXT INT8U Get_Time_From_EXT_RTC(S_BCD_Time *pBCD_Time);
//��ʱ�����õ��ⲿRTC
EXT INT8U Set_Time_To_EXT_RTC(S_BCD_Time *pBCD_Time);
//���ڲ�RTC��ȡʱ������
EXT INT8U Get_Time_From_INTER_RTC(S_BCD_Time *pBCD_Time);
//��ʱ�����õ��ڲ�RTC
EXT INT8U Set_Time_To_INTER_RTC(S_BCD_Time *pBCD_Time);

EXT INT8U Resume_Clock_Update();
EXT void Get_Timer_From_CPU_Inter(S_BCD_Time *pBCD_Time);

EXT void Save_PD_Time();
EXT void Save_Bak_PD_Time();
EXT void Init_Clock_Ram_Para();
EXT void Clock_Proc();
EXT void Clock_Update();
EXT INT8U Check_Time_Diff(S_BCD_Time *pTime0,S_BCD_Time *pTime1,INT8U Mins);
EXT INT8U Set_Time_EXT_INTER_Ram_RTC(S_BCD_Time * pBCD_Time);

EXT void Set_BCD_Array_Time(S_BCD_Time* pSrc, S_Event_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Set_Array_BCD_Time(S_Event_Time* pSrc, S_BCD_Time* pDst, void* pDst_Start, INT16U DstLen);
EXT void Set_Err_Time(S_BCD_Time *pBCD_Time);

EXT INT8U Convert_BCD_2_HEX_Time(S_BCD_Time *pBCD_Time,S_HEX_Time *pHEX_Time);
EXT INT8U Convert_HEX_2_BCD_Time(S_HEX_Time *pHEX_Time,S_BCD_Time *pBCD_Time);

EXT void Wait_Clock_Ready();
EXT void Check_Clock_Data_Avail();
EXT void Simulate_Clock();
EXT void Init_Clock(INT32U Mode);
EXT INT8U Adj_Time(S_BCD_Time *pTime, INT8U Flag);
EXT INT8U Adjust_Time_Proc(INT8U* pSrc, INT8U SrcLen);
EXT void Read_Adj_Time_Para_From_Rom();
#endif
