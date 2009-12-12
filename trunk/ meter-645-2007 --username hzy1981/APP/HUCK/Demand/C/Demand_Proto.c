#define DEMAND_PROTO_C
#include "Includes.h"


//读取需量数据
//PDI表示协议DI
//pDst目标缓冲区
//pDst_Start目标缓冲区起始地址
//DstLen目标缓冲区最大长度
INT16U _Get_Demand_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT8U* p;//Index;
  INT8U Bef_Counts;
  INT16U Len;
  INT8U Rate;
  INT8U Temp, Src_Type;
  INT32U Off, U_Data;
  INT32S S_Data;

  TRACE();
  
  if(!(pDst >= pDst_Start && pDst + 8 <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  if(sizeof(Pub_Buf) < DEMAND_PHASE_DATA_SIZE || sizeof(Pub_Buf) < DEMAND_RATE_DATA_SIZE)
  {
    ASSERT_FAILED();
    return 0;
  }

  Bef_Counts = (INT8U) (PDI & 0x0000000F);//前几个结算日数据?
  Rate = (INT8U) ((PDI & 0x0000FF00) >> 8);//费率?
  if((Data_Flag & FOR_EVENT) != FOR_EVENT && Rate > Multi_Rate_Para.Rates)
    return 0;


  if((PDI & 0x00FF0000) EQ 0x00EE0000) //需量结算日信息
  {
    Read_His_Demand_Time_Data(Bef_Counts, (S_HEX_Time *)pDst, pDst_Start, DstLen);
    Hex2Bcd_Buf(pDst, 5, pDst, pDst_Start, DstLen);
    return 5;   
  }
  else if(((PDI & 0x00F00000) EQ 0x00000000) || \
         ((PDI & 0x00F00000) EQ 0x00800000))  //读总数据以及分费率
  {
    Len = Read_His_Demand_Rate_Data(Bef_Counts, Rate, (INT8U *) Pub_Buf, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    if(Len != DEMAND_RATE_DATA_SIZE)
    {
      mem_set((INT8U *) Pub_Buf, 0, DEMAND_RATE_DATA_SIZE, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
      //ASSERT_FAILED();
      //return 0;
    }
  }
  else //读分相数据
  {
    Len = Read_His_Demand_Phase_Data(Bef_Counts, (INT8U *) Pub_Buf, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    if(Len != DEMAND_PHASE_DATA_SIZE)
    {
      mem_set((INT8U *) Pub_Buf, 0, DEMAND_RATE_DATA_SIZE, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
      //ASSERT_FAILED();
      //return 0;
    }
  }

  //全FF数据，表示这是一个无效的结算日数据
  if(Pub_Buf[0] EQ 0xFF && Pub_Buf[1] EQ 0xFF && Pub_Buf[2] EQ 0xFF)
  {
    mem_set(pDst, 0xFF, 8, pDst_Start, DstLen);
    return 8;
  }
  
  p = (INT8U *)Pub_Buf;
  Off = 0;

  Temp = (INT8U) ((PDI & 0x00FF0000) >> 16);

  if(Temp EQ 1)    //正向有功
  {
    Off = S_OFF(S_One_Demand, Pos_Active);
  }
  else if(Temp EQ 2)    //反向有功
  {
    Off = S_OFF(S_One_Demand, Neg_Active);
  }
  else if(Temp EQ 3)    //组合无功1
  {
    Off = S_OFF(S_One_Demand, Comb_Reactive1);
  }
  else if(Temp EQ 4)    //组合无功2
  {
    Off = S_OFF(S_One_Demand, Comb_Reactive2);
  }
  else if((Temp >= 5) && (Temp <= 8))  //四象限无功
  {
    Off = S_OFF(S_One_Demand, Quad_Reactive[Temp - 5]);
  }
  else if(Temp EQ 9)    //正向视在
  {
    Off = S_OFF(S_One_Demand, Pos_Apparent);
  }
  else if(Temp EQ 0x0A) //反向视在
  {
    Off = S_OFF(S_One_Demand, Neg_Apparent);
  }
  else if(((Temp >= 0x15) && (Temp <= 0x1E)) || \
          ((Temp >= 0x29) && (Temp <= 0x32)) || \
          ((Temp >= 0x3D) && (Temp <= 0x46)))
  {
    if((Temp >= 0x15) && (Temp <= 0x1E)) //A相
    {
      //Index = 0;
      Temp = Temp - 0x15;
      Off = 0;
    }
    else if((Temp >= 0x29) && (Temp <= 0x32))//B相
    {
      //Index = 1;
      Temp = Temp - 0x29;
      Off = S_OFF(S_Demand, Phase_Demand[1]) - S_OFF(S_Demand, Phase_Demand[0]);
    }
    else  //C相
    {
      //Index = 2;
      Temp = Temp - 0x3D;
      Off = S_OFF(S_Demand, Phase_Demand[2]) - S_OFF(S_Demand, Phase_Demand[0]);
    }

    if(Temp EQ 0) //正向有功
      Off += S_OFF(S_One_Demand, Pos_Active);
    else if(Temp EQ 1) //反向有功
      Off += S_OFF(S_One_Demand, Neg_Active);
    else if(Temp EQ 2) //组合无功1
      Off += S_OFF(S_One_Demand, Comb_Reactive1);
    else if(Temp EQ 3) //组合无功2
      Off += S_OFF(S_One_Demand, Comb_Reactive2);
    else if((Temp >= 4) && (Temp <= 7)) //一象限无功
      Off += S_OFF(S_One_Demand, Quad_Reactive[Temp - 4]);
    else if(Temp EQ 8) //正向视在
      Off += S_OFF(S_One_Demand, Pos_Apparent);
    else if(Temp EQ 9) //反向视在
      Off += S_OFF(S_One_Demand, Neg_Apparent);
    else
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  
  p = p + Off; //+ S_OFF(S_Demand_Time, Var);

  Src_Type = Get_DLT645_Data_Src_Type(PDI);

  if(Src_Type EQ S_INTS)
  {
    S_Data = *(INT32S *) p;
    
    if((Data_Flag & FOR_DISP) EQ FOR_DISP)
    {
      if(DemandDisBit <= 4)
        S_Data = S_Data / (INT32S)Pow_10x(4 - DemandDisBit); 
    }
    //S_Data = S_Data / 10; //源数据是3位小数，协议数据是2位小数，因此需要/10
    S_Hex2Bcd(S_Data, pDst, 3, pDst_Start, DstLen);
  }
  else if(Src_Type EQ S_INTU)
  {
    U_Data = *(INT32U *) p;
    //U_Data = U_Data / 10; //源数据是3位小数，协议数据是2位小数，因此需要/10
    if((Data_Flag & FOR_DISP) EQ FOR_DISP)
    {
      if(DemandDisBit <= 4)
        U_Data = U_Data / Pow_10x(4 - DemandDisBit); 
    }
    
    Hex2Bcd(U_Data, pDst, 3, pDst_Start, DstLen);
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  //Hex2Bcd_Buf(p + S_OFF(S_Demand_Time, Time[0]), 5, (INT8U *) pDst + 3, pDst_Start, DstLen);
  mem_cpy(pDst + 3, p + S_OFF(S_Demand_Time, Time[0]), 5, pDst_Start, DstLen);
  return 8;
}

INT16U Get_Demand_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len; 
  
  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  Len = _Get_Demand_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
  OS_Mutex_Post(PUB_BUF_SEM_ID);
  
  return Len;
}
#undef DEMAND_PROTO_C
