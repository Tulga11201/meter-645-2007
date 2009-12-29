#define ENERGY_PROTO_C
#include "Includes.h"

//读取有无功组合特征字
void Read_Energy_Comb_Word()
{
  INT16U Len;
  
  TRACE();
  //读取有功组合特征字
  Len = Read_Storage_Data(SDI_ACTIVE_COMB_WORD, (INT8U *) &Energy_Comb_Word.Active,\
						  (INT8U *) &Energy_Comb_Word.Active, sizeof(Energy_Comb_Word.Active)); 
  if(Len != 1)
  {
    ASSERT_FAILED();
    Energy_Comb_Word.Active = Def_04000601_3[0];
  }

  //读取无功组合1特征字
  Len = Read_Storage_Data(SDI_REACTIVE_COMB_WORD_1, (INT8U *) &Energy_Comb_Word.Reactive[0],\
						  (INT8U *) &Energy_Comb_Word.Reactive[0], sizeof(Energy_Comb_Word.Reactive[0]));
  if(Len != 1)
  {
    ASSERT_FAILED();
    Energy_Comb_Word.Reactive[0] = Def_04000601_3[1];
  }

  //读取无功组合2特征字
  Len = Read_Storage_Data(SDI_REACTIVE_COMB_WORD_2, (INT8U *) &Energy_Comb_Word.Reactive[1],\
						  (INT8U *) &Energy_Comb_Word.Reactive[1], sizeof(Energy_Comb_Word.Reactive[1]));
  if(Len != 1)
  {
    ASSERT_FAILED();
    Energy_Comb_Word.Reactive[1] = Def_04000601_3[2];
  }

  INIT_STRUCT_VAR(Energy_Comb_Word);
  SET_STRUCT_SUM(Energy_Comb_Word);
}

/*
typedef struct  
{
  //基本数据
  S_Energy Base;

  //总组合数据
  INT32U Comb_Active[MAX_RATES+1];  //组合有功

  INT32S Comb_Reactive1[MAX_RATES+1]; //组合无功1
  INT32S Comb_Reactive2[MAX_RATES+1]; //组合无功2

  INT32U Pos_Apparent[MAX_RATES+1]; //正向视在
  INT32U Neg_Apparent[MAX_RATES+1]; //反向视在

  //分相组合数据
  INT32U Phase_Comb_Active[3][MAX_RATES+1];  //组合有功

  INT32S Phase_Comb_Reactive1[3][MAX_RATES+1]; //组合无功1
  INT32S Phase_Comb_Reactive2[3][MAX_RATES+1]; //组合无功2

  INT32U Phase_Pos_Apparent[3][MAX_RATES+1]; //正向视在
  INT32U Phase_Neg_Apparent[3][MAX_RATES+1]; //反向视在
}S_Comb_Energy;//组合电能结构体

 */
//计算一个S_Comb_Energy结构体变量中的组合有无功数据
//计算好的数据仍然放在该机构体变量中
void Calc_Comb_Energy(S_Comb_Energy* p)
{
  INT16U i, j;
  INT8U* p0;

  TRACE();

  i = 0;

  p0 = (INT8U *) p + sizeof(p -> Base);
  while((p0 + i) < ((INT8U *) p + sizeof(S_Comb_Energy)))
  {
    *(p0 + i) = 0;
    i ++;
  }
  
  ///////////计算组合有功//////////////////////
  if(GET_BIT(Energy_Comb_Word.Active, 0))//正向有功+
  {
    p -> Comb_Month_Active += p -> Base.Prepaid_Info.Month_Pos_Act;
    p -> Comb_Last_Month_Active += p -> Base.Prepaid_Info.Last_Month_Pos_Act;
    
    for(i = 0; i <= MAX_RATES; i ++)//总分费率
      p->Comb_Active[i] += p->Base.Pos_Active[i];

    for(i = 0; i < 3; i ++) //三相
      p->Phase_Comb_Active[i] += p->Base.Phase_Pos_Active[i];
  }
  else if(GET_BIT(Energy_Comb_Word.Active, 1))//正向有功-
  {
    p -> Comb_Month_Active -= p -> Base.Prepaid_Info.Month_Pos_Act; 
    p -> Comb_Last_Month_Active -= p -> Base.Prepaid_Info.Last_Month_Pos_Act; 
    
    for(i = 0; i <= MAX_RATES; i ++)//总分费率
      p->Comb_Active[i] -= p->Base.Pos_Active[i]; 

    for(i = 0; i < 3; i ++) //三相
      p->Phase_Comb_Active[i] -= p->Base.Phase_Pos_Active[i];
  }

  if(GET_BIT(Energy_Comb_Word.Active, 2))//反向有功+
  {
    p -> Comb_Month_Active += p -> Base.Prepaid_Info.Month_Neg_Act;
    p -> Comb_Last_Month_Active += p -> Base.Prepaid_Info.Last_Month_Neg_Act;
    
    for(i = 0; i <= MAX_RATES; i ++)//总分费率
      p->Comb_Active[i] += p->Base.Neg_Active[i];

    for(i = 0; i < 3; i ++) //三相
      p->Phase_Comb_Active[i] += p->Base.Phase_Neg_Active[i];
  }
  else if(GET_BIT(Energy_Comb_Word.Active, 3))//反向有功-
  {
    p -> Comb_Month_Active -= p -> Base.Prepaid_Info.Month_Neg_Act;
    p -> Comb_Last_Month_Active -= p -> Base.Prepaid_Info.Last_Month_Neg_Act;
    
    for(i = 0; i <= MAX_RATES; i ++)//总分费率
      p->Comb_Active[i] -= p->Base.Neg_Active[i]; 

    for(i = 0; i < 3; i ++) //三相
      p->Phase_Comb_Active[i] -= p->Base.Phase_Neg_Active[i];
  }
  ////////////计算组合无功/////////////////////////
  for(i = 0; i < 4; i ++)//对4象限无功分别计算
  {
    ///////////组合无功1/////////////////
    if(GET_BIT(Energy_Comb_Word.Reactive[0], i * 2))//该象限+
    {
      for(j = 0; j <= MAX_RATES; j ++)//总分费率
        p->Comb_Reactive1[j] += p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive1[j] += p->Base.Phase_Quad_Reactive[j][i];
    }
    else if(GET_BIT(Energy_Comb_Word.Reactive[0], i * 2 + 1))//该象限-
    {
      for(j = 0; j <= MAX_RATES; j ++)//总分费率
        p->Comb_Reactive1[j] -= p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive1[j] -= p->Base.Phase_Quad_Reactive[j][i];
    }
    //////////////组合无功2//////////
    if(GET_BIT(Energy_Comb_Word.Reactive[1], i * 2))//该象限+
    {
      for(j = 0; j <= MAX_RATES; j ++)//总分费率
        p->Comb_Reactive2[j] += p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive2[j] += p->Base.Phase_Quad_Reactive[j][i];
    }
    else if(GET_BIT(Energy_Comb_Word.Reactive[1], i * 2 + 1))//该象限-
    {
      for(j = 0; j <= MAX_RATES; j ++)//总分费率
        p->Comb_Reactive2[j] -= p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive2[j] -= p->Base.Phase_Quad_Reactive[j][i];
    }
  }
  
  //反向有功电量计入正向，吉林要求
  if(NEG_ADD_POS_ACT_EN > 0)
  {
    for(i = 0; i <= MAX_RATES; i ++)//总分费率
      p->Base.Pos_Active[i] += p->Base.Neg_Active[i];
  }  
}

//读取电量数据
//PDI表示协议DI
//pDst目标缓冲区
//pDst_Start目标缓冲区起始地址
//DstLen目标缓冲区最大长度
INT16U _Get_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT8U* p, Index;
  INT8U Bef_Counts, Data_Len, Rate;
  INT16U Len;
  INT8U Temp, Src_Type;
  INT32U Off, U_Data;
  INT32S S_Data;
  INT8U FF_Flag;
  
  TRACE();

  if(!(pDst >= pDst_Start && pDst + 4 <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  
  FF_Flag = 0;
  if((PDI & 0xFF) EQ 0xFF && BYTE_2(PDI) <= 0x0A) //读取上N个结算日数据块
  {
    FF_Flag = 1;
    PDI = PDI & 0xFFFFFF00;
  }
  
  Bef_Counts = (INT8U) (PDI & 0x0000000F);//前几个结算日数据?  
  
  Temp = (INT8U) ((PDI & 0x00FF0000) >> 16);
  if(Temp EQ 0x0B) //读取的是当前和上一结算周期的组合有功总累计用电量
  {
    mem_cpy((INT8U *)Pub_Buf, (INT8U *)&Cur_Energy, sizeof(Cur_Energy), (INT8U *)Pub_Buf, sizeof(Pub_Buf));
  }
  else
  {
    Len = Read_His_Energy_Data(Bef_Counts, (INT8U *)Pub_Buf, (INT8U *)Pub_Buf, sizeof(Pub_Buf));
    if(Len != sizeof(S_Energy))
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  
  p = (INT8U *)Pub_Buf;

  ASSERT(sizeof(Pub_Buf) > sizeof(S_Comb_Energy));
  Calc_Comb_Energy((S_Comb_Energy *) p); //计算其组合电能

  Off = 0;

  if(Temp EQ 0)    //组合有功
  {
    Off = S_OFF(S_Comb_Energy, Comb_Active[0]);
  }
  else if(Temp EQ 1)    //正向有功
  {
    Off = S_OFF(S_Comb_Energy, Base.Pos_Active[0]);
  }
  else if(Temp EQ 2)    //反向有功
  {
    Off = S_OFF(S_Comb_Energy, Base.Neg_Active[0]);
  }
  else if(Temp EQ 3)    //组合无功1
  {
    Off = S_OFF(S_Comb_Energy, Comb_Reactive1[0]);
  }
  else if(Temp EQ 4)    //组合无功2
  {
    Off = S_OFF(S_Comb_Energy, Comb_Reactive2[0]);
  }
  else if((Temp >= 5) && (Temp <= 8))  //四象限无功
  {
    Off = S_OFF(S_Comb_Energy, Base.Quad_Reactive[Temp - 5][0]);
  }
  else if(Temp EQ 9)    //正向视在
  {
    Off = S_OFF(S_Comb_Energy, Base.Pos_Apparent[0]);
  }
  else if(Temp EQ 0x0A) //反向视在
  {
    Off = S_OFF(S_Comb_Energy, Base.Neg_Apparent[0]);
  }
  else if(Temp EQ 0x0B)
  {
    if(Bef_Counts EQ 0)
      Off = S_OFF(S_Comb_Energy, Comb_Month_Active);
    else
      Off = S_OFF(S_Comb_Energy, Comb_Last_Month_Active);
  }
  else if(((Temp >= 0x15) && (Temp <= 0x1E)) || \
          ((Temp >= 0x29) && (Temp <= 0x32)) || \
          ((Temp >= 0x3D) && (Temp <= 0x46)))
  {
    if((Temp >= 0x15) && (Temp <= 0x1E)) //A相
    {
      Index = 0;
      Temp = Temp - 0x15;
    }
    else if((Temp >= 0x29) && (Temp <= 0x32))//B相
    {
      Index = 1;
      Temp = Temp - 0x29;
    }
    else  //C相
    {
      Index = 2;
      Temp = Temp - 0x3D;
    }

    if(Temp EQ 0) //正向有功
      Off = S_OFF(S_Comb_Energy, Base.Phase_Pos_Active[Index]);
    else if(Temp EQ 1) //反向有功
      Off = S_OFF(S_Comb_Energy, Base.Phase_Neg_Active[Index]);
    else if(Temp EQ 2) //组合无功1
      Off = S_OFF(S_Comb_Energy, Phase_Comb_Reactive1[Index]);
    else if(Temp EQ 3) //组合无功2
      Off = S_OFF(S_Comb_Energy, Phase_Comb_Reactive2[Index]);
    else if((Temp >= 4) && (Temp <= 7)) //一象限无功
      Off = S_OFF(S_Comb_Energy, Base.Phase_Quad_Reactive[Index][Temp - 4]);
    else if(Temp EQ 8) //正向视在
      Off = S_OFF(S_Comb_Energy, Base.Phase_Pos_Apparent[Index]);
    else if(Temp EQ 9) //反向视在
      Off = S_OFF(S_Comb_Energy, Base.Phase_Neg_Apparent[Index]);
    else
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  else if(Temp EQ 0xEE) //电量结算时间
  {
    Hex2Bcd_Buf((INT8U *)&(((S_Comb_Energy *) p) -> Base.Time), 5, pDst, pDst_Start, DstLen);
    return 5;
  }

  Rate = (INT8U)((PDI & 0x0000FF00) >> 8);
  if((Data_Flag & FOR_EVENT) != FOR_EVENT && Rate > Multi_Rate_Para.Rates)
    return 0;
  
  Off += Rate * 4; //费率偏移
  p += Off;

  Src_Type = Get_DLT645_Data_Src_Type(PDI);

  if((Data_Flag & FOR_DISP) EQ FOR_DISP)//数据是用来显示的话，5个字节
    Data_Len = 5;
  else
    Data_Len = 4;

  if(Src_Type EQ S_INTS)
  {
    S_Data = *(INT32S *) p;

    if((Data_Flag & FOR_SRC) EQ FOR_SRC)//获取源数据
      mem_cpy(pDst, &S_Data, 4, pDst_Start, DstLen);
    else//获取BCD数据
    {
      if((Data_Flag & FOR_DISP) != FOR_DISP)//数据用于显示的话，不需要/10
        S_Data = S_Data / 10; //源数据是3位小数，协议数据是2位小数，因此需要/10 
      else //用于显示
      {
        if(EnergDisBit EQ 4)
          S_Data = S_Data * 10 / (INT32S)Pow_10x(4 - EnergDisBit);
        else if(EnergDisBit <= 3) //避免因显示小数位除法产生的误差
          S_Data = S_Data / (INT32S)(Pow_10x(4 - EnergDisBit) / 10);
        else
        {
          S_Data = S_Data / 10;
          ASSERT_FAILED();
        }
      }
      S_Hex2Bcd(S_Data, pDst, Data_Len, pDst_Start, DstLen);
    }
  }
  else if(Src_Type EQ S_INTU)
  {
    U_Data = *(INT32U *) p;

    if((Data_Flag & FOR_SRC) EQ FOR_SRC)//获取源数据
      mem_cpy(pDst, &U_Data, 4, pDst_Start, DstLen);
    else//获取BCD数据
    {
      if((Data_Flag & FOR_DISP) != FOR_DISP)//数据用于显示的话，不需要/10
        U_Data = U_Data / 10; //源数据是3位小数，协议数据是2位小数，因此需要/10  
      else //用于显示
      {
        if(EnergDisBit EQ 4)
          U_Data = U_Data * 10 / Pow_10x(4 - EnergDisBit);
        else if(EnergDisBit <= 3) //避免因显示小数位除法产生的误差
          U_Data = U_Data /(Pow_10x(4 - EnergDisBit) / 10);
        else
        {
          U_Data = U_Data / 10;
          ASSERT_FAILED();
        }
      }      
      Hex2Bcd(U_Data, pDst, Data_Len, pDst_Start, DstLen);
    }
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }
  
  if(FF_Flag EQ 1)//
  {
    //PDI = EH_DI(0x00000000) + BYTE_2(PDI);
    Len = Read_Storage_Data(EH_DI(0x00000000) + BYTE_2(PDI), (INT8U *)Pub_Buf, (INT8U *)Pub_Buf, sizeof(Pub_Buf)); 
    if(Len > 0)
    {
      mem_cpy(pDst + 4, (INT8U *)Pub_Buf + ((INT32U)BYTE_1(PDI))*MAX_ENERGY_SETTLE_NUM*4, \
              MAX_ENERGY_SETTLE_NUM*4, pDst_Start, DstLen);
      return (MAX_ENERGY_SETTLE_NUM + 1) * 4;
    }
    else
      return 0;
  }  
  
  return Data_Len;
}

//获取电量的协议数据
INT16U Get_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len;
  
  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  Len = _Get_Energy_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
  OS_Mutex_Post(PUB_BUF_SEM_ID);
  
  return Len;
}

//获取预付费数据
INT16U Get_Prepaid_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT32U U_Data;
  INT8U Data_Len;
  INT16U Index;
  
  Index = Get_P_Data_Index(PDI);
  if(Index EQ NULL_2BYTES)
    return 0;
  
  U_Data = 0;
  mem_cpy(&U_Data, (INT8U *)P_Data_Info[Index].pSrc, 4, &U_Data, sizeof(U_Data));
  //U_Data = P_Data_Info[Index].; //剩余电量

  if((Data_Flag & FOR_DISP) EQ FOR_DISP)//数据是用来显示的话，5个字节
    Data_Len = 5;
  else
    Data_Len = 4;
  
  if((Data_Flag & FOR_SRC) EQ FOR_SRC)//获取源数据
    mem_cpy(pDst, &U_Data, 4, pDst_Start, DstLen);
  else//获取BCD数据
  {
    if((Data_Flag & FOR_DISP) != FOR_DISP)//数据用于显示的话，不需要/10
      U_Data = U_Data / 10; //源数据是3位小数，协议数据是2位小数，因此需要/10  
    else //用于显示
    {
      if(EnergDisBit EQ 4)
        U_Data = U_Data * 10 / Pow_10x(4 - EnergDisBit);
      else if(EnergDisBit <= 3) //避免因显示小数位除法产生的误差
        U_Data = U_Data /(Pow_10x(4 - EnergDisBit) / 10);
      else
      {
        U_Data = U_Data / 10;
        ASSERT_FAILED();
      }
    }      
    Hex2Bcd(U_Data, pDst, Data_Len, pDst_Start, DstLen);
  }  
  
  return Data_Len;
}

//获取费率数据
INT16U Get_Rate_Info_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT16U Len;
/*
#define PDI_CUR_RATE_SCHEME         0x0E010000//当前年时区方案
#define PDI_CUR_YEAR_PERIOD         0x0E010001//当前年时区号
#define PDI_CUR_DATE_TABLE_SCHEME   0x0E010002 //当前日时段表方案
#define PDI_CUR_DATE_TABLE          0x0E010003 //当前日时段表号
#define PDI_CUR_DATE_PERIOD         0x0E010004 //当前日时段号
#define PDI_CUR_RATE                0x0E010005 //当前费率
*/  
  Len = 1;
  if(PDI EQ 0x0E010000)
    *pDst = (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?1:2;
  else if(PDI EQ 0x0E010001)
    Hex2Bcd(Cur_Rate_Info.Year_Period, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010002)
    *pDst = (Cur_Rate_Info.Date_Scheme EQ DATE_SCHEME0)?1:2;
  else if(PDI EQ 0x0E010003)
    Hex2Bcd(Cur_Rate_Info.Date_Table, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010004)
    Hex2Bcd(Cur_Rate_Info.Date_Period, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010005)
    Hex2Bcd(Cur_Rate_Info.Rate, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010006)
  {
    if(Cur_Rate_Info.Date_Flag EQ NORMAL_DAY)
      *pDst = 0;
    else if(Cur_Rate_Info.Date_Flag EQ WEEK_REST_DAY)
      *pDst = 1;
    else if(Cur_Rate_Info.Date_Flag EQ HOLIDAY)
      *pDst = 2;
  }
  else if(PDI EQ 0x0E010007) //当前预付费方式,电量型为0，电费型为1
    *pDst = (PREPAID_MODE EQ ENERGY_MODE)?0:1;
  else if(PDI EQ 0x0E010008) //当前扣费方式,分时为0，阶梯为1
    *pDst = (PREPAID_MONEY_MODE EQ PREPAID_RATE)?0:1;
  else if(PDI EQ 0x0E010009) //当前分时费率方案
    *pDst = (Cur_Rate_Info.Rate_Scheme EQ RATE_SCHEME0)?1:2;
  else if(PDI EQ 0x0E01000A) //当前分时电价
  {
    Hex2Bcd(Rate_Scheme_Para.Fee[Cur_Rate_Info.Rate - 1], pDst, 4, pDst_Start, DstLen);
    Len = 4;
  }
  else if(PDI EQ 0x0E01000B) //当前阶梯方案
    *pDst = PREPAID_STEP_SCHEME;
  else if(PDI EQ 0x0E01000C) //当前阶梯号
    Hex2Bcd(PREPAID_STEP_NO, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E01000D) //当前阶梯电能
  {
    if(Cur_Rate_Info.Step_No EQ 0)
      Hex2Bcd(0, pDst, 4, pDst_Start, DstLen);
    else
      Hex2Bcd(Step_Scheme_Para.Step_Energy[Cur_Rate_Info.Step_No - 1], pDst, 4, pDst_Start, DstLen);
    
    Len = 4;    
  }
  else if(PDI EQ 0x0E01000E || PDI EQ 0x0280000B) //当前阶梯电价
  {
    Hex2Bcd(Step_Scheme_Para.Step_Fee[Cur_Rate_Info.Step_No], pDst, 4, pDst_Start, DstLen);
    Len = 4;    
  }  
  else if(PDI EQ 0x0E01000F) //当月阶梯总电能
  {
    Hex2Bcd(Cur_Energy.Prepaid_Info.Month_Pos_Act / 10, pDst, 4, pDst_Start, DstLen);
    Len = 4;
  }
  else if(PDI EQ 0x0E010010) //预付费跳闸重插卡标志,0表示没有插，1表示有插
  {
    *pDst = Get_Card_Switch_On_Flag(); 
    Len = 1;    
  }
  else if(PDI EQ 0x0E010011) //拉合闸状态、原因
  {
    *pDst = Relay_Status.Switch_Cause; 
    *(pDst + 1) = Relay_Status.Switch_Status;
    Len = 2;
  }
  else if(PDI EQ 0x0E010012)//远程控制命令的状态
  {
    mem_cpy(pDst, (INT8U *)&Remote_Ctrl_Switch, 21, pDst_Start, DstLen);
    Len = 21;
  }
  else if(PDI >= PDI_CUR_RATE1_FEE && PDI < PDI_CUR_RATE1_FEE + MAX_RATES) //当前费率电价
  {
    Hex2Bcd(Rate_Scheme_Para.Fee[PDI - PDI_CUR_RATE1_FEE], pDst, 4, pDst_Start, DstLen);
    Len = 4;
  }
  else if(PDI >= PDI_CUR_STEP1_ENG && PDI < PDI_CUR_STEP1_ENG + PREPAID_MAX_STEP) //当前阶梯电量
  {
    Hex2Bcd(Step_Scheme_Para.Step_Energy[PDI - PDI_CUR_STEP1_ENG], pDst, 4, pDst_Start, DstLen);
    Len = 4;    
  }
  else if(PDI >= PDI_CUR_STEP1_FEE && PDI < PDI_CUR_STEP1_FEE + PREPAID_MAX_STEP + 1) //当前阶梯电价
  {
    Hex2Bcd(Step_Scheme_Para.Step_Fee[PDI - PDI_CUR_STEP1_FEE], pDst, 4, pDst_Start, DstLen);
    Len = 4;     
  }
  else 
    Len = 0;
  
  return Len;
}

//获取预付费事件记录数据
INT16U Get_Prepaid_Event_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len;
  INT8U Index;

  INT16U Off;

  TRACE();

  Index = (INT8U)((PDI & 0x00FF00) >> 8);
  
  if(Index EQ 1)
  {
    Off = 0;
    Len = 5;
  }
  else if(Index EQ 2)
  {
    Off = 5;
    Len = 2;
  }
  else if(Index EQ 3)
  {
    Off = 7;
    Len = 4;
  }
  else if(Index EQ 4)
  {
    Off = 11;
    Len = 4;
  }
  else if(Index EQ 5)
  {
    Off = 15;
    Len = 4;
  }
  else if(Index EQ 6)
  {
    Off = 19;
    Len = 4;
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  //注意：下面的Get_Event_Separate_Proto_Data函数内可能需要用到Pub_Buf0缓冲区
  //但是在此处不会用到，因此不会造成冲突
  Len = Get_Event_Separate_Proto_Data((PDI & 0xFFFF00FF) | 0x0100, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    return 0;
  }

  mem_cpy(pDst, (INT8U *) Pub_Buf0 + Off, Len, pDst_Start, DstLen);
  
  return Len;  
}
                                     
//设置初始电量
INT8U Set_Energy_Start(PROTO_DI PDI,INT8U *pSrc, INT16U SrcLen)
{
  INT32U *p;
  INT8U i;
  INT32U Sum;
  INT32U Data;
  
  if(Check_Meter_Factory_Status() EQ 0) //非工厂状态不允许设置初始电量等
    return 0;
  
  if(SET_ENERGY_EN EQ 0)//不允许设置初始电量
    return 0;
  else
  {
    //if(SrcLen != (MAX_RATES + 1)*4)
      //return 0;
    
    if(PDI EQ 0x0E000301)
      p = (INT32U *)Cur_Energy.Pos_Active;
    else if(PDI EQ 0x0E000302)
      p = (INT32U *)Cur_Energy.Neg_Active;
    else if(PDI EQ 0x0E000303)
      p = (INT32U *)Cur_Energy.Quad_Reactive[0];
    else if(PDI EQ 0x0E000304)
      p = (INT32U *)Cur_Energy.Quad_Reactive[1];
    else if(PDI EQ 0x0E000305)
      p = (INT32U *)Cur_Energy.Quad_Reactive[2];
    else if(PDI EQ 0x0E000306)
      p = (INT32U *)Cur_Energy.Quad_Reactive[3];
    else if(PDI EQ 0x0E000307)
      p = (INT32U *)Cur_Energy.Pos_Apparent;
    else if(PDI EQ 0x0E000308)
      p = (INT32U *)Cur_Energy.Neg_Apparent;
    else if(PDI EQ 0x0E000400) //设置预付费电量,用于测试
    {
      Data = Bcd2Hex(pSrc, 4);
      return Prepaid_Buy_Energy_Proc(Data);
    }
    else if(PDI EQ 0x0E000401) //设置预付费电费,用于测试
    {
      Data = Bcd2Hex(pSrc, 4);
      return Prepaid_Buy_Money_Proc(Data);
    }
    else if(PDI EQ 0x0E000402) //设置当月走过电量,用于测试
    {
       Cur_Energy.Prepaid_Info.Month_Pos_Act = Bcd2Hex(pSrc, 4)*10;
       SET_STRUCT_SUM(Cur_Energy);
       return 1;
    }
    else if(PDI EQ 0x0E000403) //跳闸情况下插卡
    { 
       return Prepaid_Insert_Card(*pSrc); //用于用户卡临时插卡合闸
    }
    else
    {
      ASSERT_FAILED();
      return 0;
    }
    
    Sum = 0;
    for(i = 1; i <= MAX_RATES; i ++)
    {
      Sum += Bcd2Hex(pSrc + i*4, 4)*10;
    }
  
    if(Sum != Bcd2Hex(pSrc, 4)*10)
      return 0;
    
    //SET_STRUCT_SUM(Cur_Energy);
    //if(Check_Energy_Data((S_Energy *)&Cur_Energy))
    //{
    Debug_Print("Set Start Energy------!!!!,PDI = 0x%lx, SrcLen = %d",PDI,SrcLen);
  
    Set_Event_Instant(ID_EVENT_SET_ENERG);
    //Wait_Event_Data_Proc_End(ID_EVENT_SET_ENERG);
    OS_Waitfor_Sec(Read_Event_Status(ID_EVENT_SET_ENERG) EQ 1, 3);//等待3s还没有处理完则报断言错误
    if(Read_Event_Status(ID_EVENT_SET_ENERG) EQ 0)
    {
      ASSERT_FAILED();
    }
    
    for(i = 0; i <= MAX_RATES; i ++)
    {
      *(p + i) = Bcd2Hex(pSrc + i*4, 4)*10;
    }
  
    SET_STRUCT_SUM(Cur_Energy);
    
    mem_cpy((void *)&Cur_Energy_Bak, (void *)&Cur_Energy, sizeof(Cur_Energy),\
            (void *)&Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
    Clr_Event_Instant(ID_EVENT_SET_ENERG);
    
    Save_Cur_Energy_PD_Data();
    Save_Cur_Energy_Data();
    Save_Cur_Energy_Bak0_Data();
    Save_Cur_Energy_Bak1_Data();
    Save_Cur_Energy_Bak2_Data();
    return 1;
  }
  //}

  //return 0;
}
#undef ENERGY_PROTO_C
