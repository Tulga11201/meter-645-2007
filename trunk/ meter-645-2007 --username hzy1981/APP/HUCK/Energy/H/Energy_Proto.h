#ifndef ENERGY_PROTO_H
#define ENERGY_PROTO_H

#undef EXT
#ifdef ENERGY_PROTO_C
#define EXT
#else
#define EXT extern
#endif
/*
//电量结构体
typedef struct 
{
  //INT8U Time[5];//冻结时间点,该时间在冻结时复制为冻结时间
  S_HEX_Time Time;//冻结时间点,该时间在冻结时复制为冻结时间
  
  INT32U  Pos_Active[MAX_RATES+1];//总以及分费率正向有功,三位小数,单位KWh，下同
  INT32U  Neg_Active[MAX_RATES+1];//总以及分费率反向有功
  
  INT32U  Quad_Reactive[4][MAX_RATES+1];//四象限分费率无功
  
  INT32U  Phase_Pos_Active[3];//三相正向有功
  INT32U  Phase_Neg_Active[3];//三相反向有功
  
  INT32U Phase_Quad_Reactive[3][4];//三相四象限无功
  
  INT32U  Phase_AH[3];//三相总AH
  
  INT32U  CopperLoss[4];//总ABC铜损
  INT32U  IronLoss[4];  //总ABC铁损
  INT32U  TransErr[4];  //总ABC互感器误差
  
  //INT32U  Phase_Reactive[3][4];//三相各四象限无功
  
  INT8U   CS[CS_BYTES];//后面的不需要保存到Flash中
  
  //以下部分是根据以上量计算得，不需要保存到Flash或EERom中
  //INT32U Pos_Reactive[MAX_RATES+1];//总以及分费率正向无功
  //INT32U Neg_Reactive[MAX_RATES+1];
  
}S_Energy;
*/
typedef struct
{
  INT8U Head;
  
  INT8U Active; 
  INT8U Reactive[2];

  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Comb_Word;

typedef struct
{
    //基本数据
    S_Energy Base;

    INT32S Comb_Month_Active; //一个结算周期组合有功,跨结算日会清零
    INT32S Comb_Last_Month_Active; //上一结算周期组合有功
    //总组合数据
    INT32S Comb_Active[MAX_RATES + 1];  //组合有功

    INT32S Comb_Reactive1[MAX_RATES + 1]; //组合无功1
    INT32S Comb_Reactive2[MAX_RATES + 1]; //组合无功2

    //分相组合数据
    INT32U Phase_Comb_Active[3];  //组合有功

    INT32S Phase_Comb_Reactive1[3]; //组合无功1
    INT32S Phase_Comb_Reactive2[3]; //组合无功2

}S_Comb_Energy;//组合电能结构体

EXT volatile S_Comb_Word Energy_Comb_Word;

EXT void Read_Energy_Comb_Word();
EXT INT16U Get_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Get_Prepaid_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Get_Rate_Info_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U Get_Prepaid_Event_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT8U Set_Energy_Start(PROTO_DI PDI,INT8U *pSrc, INT16U SrcLen);
EXT INT8U Clear_One_Event_Data(PROTO_DI PDI);
#endif
