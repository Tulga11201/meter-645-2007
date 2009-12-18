#ifndef BUU_CARD_H_
#define BUY_CARD_H_
#define String2ParaFile(Dst,Src,Len)   mem_cpy( Dst, Src, Len, Dst, Len)

unsigned char Judge_User_Card_OK(unsigned char BuyCard_Kind,unsigned long Buy_Count);
unsigned char Buy_Card(void);
void Deal_Triff_Data(unsigned char * Source_Point,unsigned char SrcLen,INT8U WhichTable);
void Meter_Money_And_Count_Updata( unsigned long Curr_Buy_Money,unsigned long Curr_Buy_Money_Count );
void Deal_Buy_Para_Inf_File(unsigned char * Source_Point );
//void Test(void );
 

#endif