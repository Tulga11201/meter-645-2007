#ifndef BUU_CARD_H_
#define BUY_CARD_H_
#define String2ParaFile(Dst,Src,Len)   mem_cpy( Dst, Src, Len, Dst, Len)

INT8U Judge_User_Card_OK(INT8U BuyCard_Kind,INT32U Buy_Count);
INT8U Buy_Card(void);
void Deal_Triff_Data(INT8U * Source_Point,INT8U SrcLen,INT8U WhichTable);
void  Meter_Money_And_Count_Updata( INT32U Curr_Buy_Money,INT32U Curr_Buy_Money_Count );
void Deal_Buy_Para_Inf_File(INT8U * Source_Point );
//void Test(void );
 

#endif