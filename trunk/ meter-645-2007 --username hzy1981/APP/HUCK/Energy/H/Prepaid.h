#ifndef PREPAID_H
#define PREPAID_H

#undef EXT
#ifdef PREPAID_C
#define EXT
#else
#define EXT extern
#endif

#define T_BCD 0
#define T_HEX 1

typedef struct
{
  INT8U Head;
  
  INT8U Buy_Eng_Flag:4; //购电标志
  INT8U Set_Para_Flag:1; //参数更新标志
  
  PROTO_DI Prog_PDI; //编程标识 
  INT8U Op_ID[4];  //编程ID
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Card_Op_Info;

#define BUY_ENG   0x0B //电量型购电
#define BUY_MONEY 0x0C //电费型购电

EXT volatile S_Card_Op_Info Card_Op_Info;

EXT void Check_Cur_Step();
EXT void Read_Prepaid_Para_From_Rom();
EXT void Settle_Prepaid_Month_Eng(S_HEX_Time *pTime);
EXT void Prepaid_Clr_Month_Eng_Money(S_HEX_Time *pTime);
EXT void Prepaid_Clr_Month_Eng_Chk(S_HEX_Time *pTime);
EXT INT8U Prepaid_Buy_Energy_Proc(INT32U Eng);
EXT INT8U Prepaid_Buy_Money_Proc(INT32U Money);
EXT INT8U Check_Buy_Money_Exceed_Limit(INT32U Money);
EXT INT32U Get_Money_Hoard_Limit(); //获取剩余金额囤积门限，单位0.01元
EXT INT32U Get_Left_Money(); //获取剩余金额,单位0.01元
EXT INT32U Get_Overdraft_Money(); //获取透支金额,单位0.01元
EXT INT32U Get_Buy_Eng_Counts(); //获取购电次数
EXT void Prepaid_Set_Buy_Money_Counts(INT32U Money, INT32U Counts);
EXT INT8U Get_Array_Time(INT8U Type,INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT8U UpdataUnlawCardInsetEvent();
EXT INT8U Get_Prepaid_Status();
EXT void Prepaid_Prog_Record(PROTO_DI PDI, INT8U Op_ID[]);
EXT void Prepaid_Card_Op_Bef_Proc();
EXT void Prepaid_Card_Op_Aft_Proc();
EXT void Card_Set_Para_Notice();
EXT STORA_DI Get_Card_Set_Rate_Scheme_SDI(INT8U Scheme);
EXT void Clr_Card_Op_Info();
#endif
