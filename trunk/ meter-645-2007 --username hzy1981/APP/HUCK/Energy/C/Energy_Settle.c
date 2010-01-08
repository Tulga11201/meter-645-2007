#define ENERGY_SETTLE_C
#include "includes.h"

void Read_Settle_Para_From_Rom()
{
  INT8U i;
  INT16U Len;

  TRACE();

  for(i = 0; i < 3; i ++)
  {
    Len = Read_Storage_Data(SDI_MONTH_SETTLE_DAY1 + i, (void *) Settle_Time.Time_D_H[i], (void *) Settle_Time.Time_D_H[0], sizeof(Settle_Time.Time_D_H));//PDI_MONTH_SETTLE_DAY1
    ASSERT(Len EQ 2);
  }

  INIT_STRUCT_VAR(_Settle_Time);
  SET_STRUCT_SUM(Settle_Time);
}

//检查BCD的分和时数据格式是否正确?
//Time_D_H[0]表示分钟，BCD码
//Time_D_H[1]表示小时，BCD码
INT8U Check_Time_D_H(INT8U Time_D_H[])
{
  if(Check_BCD_Data(Time_D_H, 2))
  {
    if(Time_D_H[0] < 0x24 && Time_D_H[1] > 0 && Time_D_H[1] < 0x32)
    {
      return 1;
    }
  }
  //ASSERT_FAILED();
  return 0;
}


//获取pSrc时间点以前(<pSrc)的最近一个结算日到pDst
//如果有结算日则返回1，同时结算日填充到pDst
//如果没有结算日则返回0
INT8U Get_Last_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  INT32U Dec, Min = 0xFFFFFFFF;
  INT8U i, Index, Month_Flag = 0;
  INT32U Temp, Temp1;

  ASSERT((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + sizeof(S_HEX_Time) <= (INT8U *) pDst_Start + DstLen);
  Temp1 = (INT32U)((INT32U) (pSrc -> Time[T_HOUR]) + (INT32U) (pSrc -> Time[T_DATE]) * 24) * 60 + pSrc -> Time[T_MIN];
  for(i = 0; i < 3; i++)
  {
    if(Check_Time_D_H((INT8U *) Settle_Time.Time_D_H[i]))
    {
      Temp = (INT32U)((INT32U) Bcd2Hex_Byte(Settle_Time.Time_D_H[i][0]) + (INT32U) Bcd2Hex_Byte(Settle_Time.Time_D_H[i][1]) * 24) * 60;
      //计算pSrc代表的时间和每个结算日之间的差，最小的那个就是最近的结算日
      if(Temp >= Temp1)//结算日期在pSrc时间点后
        Dec = Temp1 + (INT32U)31 * 24 * 60 - Temp;
      else
        Dec = Temp1 - Temp;

      if(Dec < Min)
      {
        Min = Dec;
        Index = i;
        //Month_Flag=1表示需要跨月
        if(Temp >= Temp1)
          Month_Flag = 1;
        else
          Month_Flag = 0;
      }
    }
  }
  //Min!=0xFFFF表示找到了上个结算日
  if(Min != 0xFFFF)
  {
    mem_cpy(pDst, pSrc, sizeof(S_HEX_Time), pDst, sizeof(S_HEX_Time));
    pDst -> Time[T_MIN] = 0;
    pDst -> Time[T_HOUR] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][0]);
    pDst -> Time[T_DATE] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][1]);
    Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst -> CS));
    if(Month_Flag == 1)//必须向前推一个月
      Time_Dec(pDst, 1, UNIT_MON, pDst);
    return 1;
  }
  else
  {
    return 0;
  }
}

//获取pSrc时间点以后(>pSrc)的最近一个结算日到pDst
//如果获取到则返回1，并将时间结果填入pDst指向的时间中
//如果没有获取到则返回0
INT8U Get_Next_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  INT32U Dec, Min = 0xFFFFFFFF;
  INT8U i, Index, Month_Flag = 0;
  INT32U Temp, Temp1;

  ASSERT((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + sizeof(S_HEX_Time) <= (INT8U *) pDst_Start + DstLen);
  Temp1 = (INT32U)((INT32U) (pSrc -> Time[T_HOUR]) + (INT32U) (pSrc -> Time[T_DATE]) * 24) * 60 + pSrc -> Time[T_MIN];
  for(i = 0; i < 3; i++)
  {
    if(Check_Time_D_H((INT8U *) Settle_Time.Time_D_H[i]))
    {
      Temp = (INT32U)((INT32U) Bcd2Hex_Byte(Settle_Time.Time_D_H[i][0]) + (INT32U) Bcd2Hex_Byte(Settle_Time.Time_D_H[i][1]) * 24) * 60;
      //计算pSrc代表的时间和每个结算日之间的差，最小的那个就是最近的结算日
      if(Temp <= Temp1)//结算日期在pSrc时间点前
        Dec = Temp + (INT32U)31 * 24 * 60 - Temp1;
      else
        Dec = Temp - Temp1;

      if(Dec < Min)
      {
        Min = Dec;
        Index = i;
        //Month_Flag=1表示需要跨月
        if(Temp <= Temp1)
          Month_Flag = 1;
        else
          Month_Flag = 0;
      }
    }
  }
  //Min!=0xFFFF表示找到了下个结算日
  if(Min != 0xFFFF)
  {
    mem_cpy(pDst, pSrc, sizeof(S_HEX_Time), pDst, sizeof(S_HEX_Time));
    pDst -> Time[T_MIN] = 0;
    pDst -> Time[T_HOUR] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][0]);
    pDst -> Time[T_DATE] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][1]);
    Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst -> CS));
    if(Month_Flag == 1)//必须向前推一个月
      Time_Inc(pDst, 1, UNIT_MON, pDst);
    return 1;
  }
  else
  {
    return 0;
  }
}


//获取pSrc时间点后的第N个结算日时间点 
void Get_N_Last_Settle_Time(INT8U N, S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  INT8U i;
  S_HEX_Time TempTime;

  mem_cpy(&TempTime, pSrc, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
  for(i = 0; i < N; i++)
  {
    Get_Last_Settle_Time(&TempTime, pDst, pDst_Start, DstLen);
    mem_cpy(&TempTime, pDst, sizeof(TempTime), &TempTime, sizeof(TempTime));
  }
}

//获取pSrc时间点后的第N个结算日时间点 
void Get_N_Next_Settle_Time(INT8U N, S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  INT8U i;
  S_HEX_Time TempTime;

  mem_cpy(&TempTime, pSrc, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
  for(i = 0; i < N; i++)
  {
    Get_Next_Settle_Time(&TempTime, pDst, pDst_Start, DstLen);
    mem_cpy(&TempTime, pDst, sizeof(TempTime), &TempTime, sizeof(TempTime));
  }
}
/*
//电量结构体
typedef struct 
{
  //INT8U Time[5];//冻结时间点, 该时间在冻结时复制为冻结时间
  S_HEX_Time Time;//冻结时间点, 该时间在冻结时复制为冻结时间
  
  INT32U  Pos_Active[MAX_RATES+1];//总以及分费率正向有功, 三位小数, 单位KWh，下同
  INT32U  Neg_Active[MAX_RATES+1];//总以及分费率反向有功
  
  INT32U  Quad_Reactive[4][MAX_RATES+1];//四象限分费率无功
  
  INT32U  Phase_Pos_Active[3];//三相正向有功
  INT32U  Phase_Neg_Active[3];//三相反向有功
  
  INT32U Phase_Quad_Reactive[3][4];
  
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
//读取最近一条需量结算数据的存储DI
STORA_DI Read_Last_Settle_Energy_DI()
{
  INT16U Len;
  STORA_DI Last_SDI;

  Len = Read_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI));
  //读出的DI是否正确?
  if(sizeof(Last_SDI) != Len || \
     Last_SDI < _SDI_SETTLE_ENERGY_DATA || \
     Last_SDI >= _SDI_SETTLE_ENERGY_DATA + MAX_ENERGY_SETTLE_NUM)//读出数据有错
  {
    ASSERT_FAILED();
    Last_SDI = _SDI_SETTLE_ENERGY_DATA;
  }
  return Last_SDI;
}
//读取前几次的历史电能数据
//Bef_Counts, 表示是前几次, 0表示读取当前数据
//pDst表示目标缓冲区
//pDst_Start和DstLen一起限定pDst和返回长度的范围
//pErr返回0时表示用来表示错误原因
INT16U Read_His_Energy_Data(INT8U Bef_Counts, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  STORA_DI Last_SDI;
  INT16U Len;

  if(Bef_Counts > 0)//读历史数据
  {
    Last_SDI = Read_Last_Settle_Energy_DI();

    Last_SDI = Last_SDI - Bef_Counts + 1;//向前追溯Bef_Counts个结算点
    if(Last_SDI < _SDI_SETTLE_ENERGY_DATA)
      Last_SDI += MAX_ENERGY_SETTLE_NUM;

    Len = Read_Storage_Data(Last_SDI, pDst, pDst_Start, DstLen);
    if(Len != sizeof(Cur_Energy))
    {
      ASSERT_FAILED();
      return 0;
    }
    Debug_Print("Read_His_Energy_Data, Time:");
    Print_HEX_Time(& (((S_Energy *)pDst) -> Time));
  }
  else//读当前数据
  {
    mem_cpy(pDst, (void *) &Cur_Energy, sizeof(Cur_Energy), pDst_Start, DstLen);
    //return sizeof(Cur_Energy);
  }
  return sizeof(Cur_Energy);
}
/*---------这个函数是上电补结算的-----------
//上电冻结电量数据
//pTime为掉电时间后的第一个结算时间或者当前结算时间,从pTime开始补结算
//如果是上电后调用该函数则表示上电时刻, 如果是结算日调用则为当前结算时间点
void Settle_Energy_Data(S_HEX_Time* pTime)
{
  //INT16U Len;
  INT8U i;
  S_HEX_Time TempTime;
  //S_HEX_Time Settle_From_Time;
  STORA_DI Last_SDI, Bak_DI;

  Debug_Print("----------Settle Energy Data----------");

  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  //先读取最近一次的电量结算数据
  Last_SDI = Read_Last_Settle_Energy_DI();
  Bak_DI = Last_SDI;
     
  if(Check_HEX_Time(pTime))
  {
    Debug_Print("Settle From Time:");
    Print_HEX_Time(pTime); 
    
    //当前时间向前推MAX_ENERGY_SETTLE_NUM个结算日
    Get_N_Last_Settle_Time(MAX_ENERGY_SETTLE_NUM, (S_HEX_Time *)(&Cur_Time0), &TempTime, &TempTime, sizeof(TempTime));
    //现在TempTime是在当前时间的前MAX_ENERGY_SETTLE_NUM个结算日

    //pEnergy = (S_Energy *) Pub_Buf;
    //数据时间在TempTime以前，说明最后一个数据的时间是在当前时间的前MAX_ENERGY_SETTLE_NUM个结算日以前
    //全0表示默认数据

    //如果起始结算时间在前12个结算日以前,则不补结算
    if(Cmp_Time(pTime, &TempTime) EQ  TIME_BEF)
    {
      Debug_Print("Time Aft 12 Settle Days, No Settle");
      //Get_Last_Settle_Time((S_HEX_Time *)&Cur_Time0, &TempTime, &TempTime, sizeof(TempTime));
      //Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));  
      //TempTime是>=pTime的第一个结算时间点,如果两者相等则进行结算
    }
    else
    {
      //上次结算的时间如果和这次一致则从下一结算日开始结算,防止结算后马上掉电上电重复结算
      Read_Storage_Data(Last_SDI, (INT8U *) Pub_Buf, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
      if(memcmp(pTime, &(((S_Energy *)Pub_Buf) -> Time), sizeof(S_HEX_Time)) EQ 0)
      {
        Debug_Print("Same as Last settle time!");
        Get_Next_Settle_Time(pTime, &TempTime, &TempTime, sizeof(TempTime));
      }
      else
        mem_cpy((void *)&TempTime, (void *)pTime, sizeof(S_HEX_Time), (void *)&TempTime, sizeof(TempTime));
      
      //如果pTime是掉电时间，则需要进行如下处理，找到>pTime的第一个结算时间
      //如果pTime本身就是结算时间，则转换后TempTime还是自身
      //Get_Last_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
      //Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
      
      //现在TempTime就是要开始补结算的开始时间点
      for(i = 0; i < MAX_ENERGY_SETTLE_NUM; i ++)
      {
        if(Cmp_Time(&TempTime, (S_HEX_Time *)&Cur_Time0) != TIME_AFT)
        {
          Debug_Print("Settle Energy Data, Time:");
          Print_HEX_Time((S_HEX_Time *) &TempTime);
      
          mem_cpy((void *) &Cur_Energy.Time, &TempTime, sizeof(TempTime),(void *) &Cur_Energy.Time, sizeof(Cur_Energy.Time));
          SET_STRUCT_SUM(Cur_Energy);
      
          INC_ENERGY_SETTLE_DI(Last_SDI);
          Write_Storage_Data(Last_SDI, (void *) &Cur_Energy, sizeof(Cur_Energy));
        }
        else
          break;
      
        Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
      }
    }
  }
  else//最近一条电量结算数据读不出来！, 直接按Last_DI往后存
  {
    ASSERT_FAILED();
    //INC_ENERGY_SETTLE_DI(Last_SDI);
    //Write_Storage_Data(Last_SDI, (void *) &Cur_Energy, sizeof(Cur_Energy));
  }

  if(Bak_DI != Last_SDI)
  {
    Write_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &Last_SDI, sizeof(Last_SDI));
  }//保存最近一次的DI
  
  OS_Mutex_Post(PUB_BUF_SEM_ID);
}
*/
void _mem_cpy(INT8U *pDst, INT8U *pSrc, INT16U SrcLen, INT8U *pDst_Start, INT16U DstLen)
{
  INT16U i;
  
  if(!(pDst >= pDst_Start && pDst + SrcLen <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return;
  }
  
  for(i = 0; i < SrcLen; i ++)
  {
    *(pDst + SrcLen -1 - i) = *(pSrc + SrcLen -1 -i); 
  }
}

//Flag位0表示清0，1表示结算
void Settle_Energy_FF_Data(INT8U Flag)
{
  INT8U i,j,Type;
  INT16U Len;
  PROTO_DI PDI;
  
  if(BLOCK_DATA_SETTLE_EN EQ 0)
    return;
  
  Len = 0;
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  for(i =0; i <= 10; i ++)
  { 
    //Len = 0;
    if(Flag > 0)
    {
      Len = Read_Storage_Data(EH_DI(0x00000000) + i, (INT8U *)Pub_Buf0, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));  
      if(Len EQ 0)
        mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
      
      for(j = 0; j <= MAX_RATES; j ++)
      {
        _mem_cpy((INT8U *)Pub_Buf0 + (INT16U)j*MAX_ENERGY_SETTLE_NUM*4 + 4, (INT8U *)Pub_Buf0 + (INT16U)j*MAX_ENERGY_SETTLE_NUM*4,\
                  MAX_ENERGY_SETTLE_NUM*4 - 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
        
        PDI = 0x00000000 + ((INT32U)i << 16) + ((INT32U)j << 8);
        Len =_Get_DLT645_Data(PDI, (void *) Zero, 0, (INT8U *)(INT8U *)Pub_Buf0 + (INT16U)j*MAX_ENERGY_SETTLE_NUM*4, \
                             (INT8U *)Pub_Buf0, sizeof(Pub_Buf0), FOR_EVENT, &Type);  
      }
    }
    else
      mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
      
    Len = Get_Storage_Data_Len(EH_DI(0x00000000) + i);
    Write_Storage_Data(EH_DI(0x00000000) + i, (INT8U *)Pub_Buf0, Len);   
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}

//上电冻结电量数据----不补结算!!!!
//pTime为掉电时间后的第一个结算时间或者当前结算时间,从pTime开始补结算
//如果是上电后调用该函数则表示上电时刻, 如果是结算日调用则为当前结算时间点
void Settle_Energy_Data(S_HEX_Time* pTime)
{
  //INT16U Len;
  //INT8U i;
  //S_HEX_Time TempTime;
  //S_HEX_Time Settle_From_Time;
  STORA_DI Last_SDI;
  INT8U Settle_Flag;

  Debug_Print("----------Settle Energy Data----------");

  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  //先读取最近一次的电量结算数据
  Last_SDI = Read_Last_Settle_Energy_DI();
  Settle_Flag = 0;   
  if(Check_HEX_Time(pTime))
  {
    Debug_Print("Settle Time:");
    Print_HEX_Time(pTime); 

    //上次结算的时间如果和这次一致则从下一结算日开始结算,防止结算后马上掉电上电重复结算
    Read_Storage_Data(Last_SDI, (INT8U *) Pub_Buf, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    if(memcmp(pTime, &(((S_Energy *)Pub_Buf) -> Time), sizeof(S_HEX_Time)) != 0)
    {
      mem_cpy((INT8U *)&Cur_Energy.Time, pTime, sizeof(S_HEX_Time), (INT8U *)&Cur_Energy.Time, sizeof(Cur_Energy.Time));
      SET_STRUCT_SUM(Cur_Energy);
      
      INC_ENERGY_SETTLE_DI(Last_SDI);
      Write_Storage_Data(Last_SDI, (void *) &Cur_Energy, sizeof(Cur_Energy));
      Write_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &Last_SDI, sizeof(Last_SDI));     
      Settle_Flag = 1;
      //Prepaid_Clr_Month_Eng_Chk(pTime);      
    }
    else
      Debug_Print("Same as Last settle time!");
  }
  else
    ASSERT_FAILED();
  
  OS_Mutex_Post(PUB_BUF_SEM_ID);
  
  if(Settle_Flag EQ 1)
     Settle_Energy_FF_Data(1);
}
//上电后月数据的冻结，前溯HIS_ENERGY_DATA_MONTHS个月
void PowerOn_Settle_Energy_Data()
{
  S_HEX_Time TempTime;
  //如果Hex_PD_Time本身是结算时间点，则应该使之指向下一个结算点
  if(Check_HEX_Time((S_HEX_Time *) &Hex_PD_Time))
  {
    Get_Next_Settle_Time((S_HEX_Time *) &Hex_PD_Time, &TempTime, &TempTime, sizeof(TempTime));
    Settle_Energy_Data((S_HEX_Time *) &TempTime);
  }
}
/*
//读取历史电量数据
//Bef_Counts表示前多少次的结算数据
//pDst表示目标缓冲区
//返回读取到的数据长度
INT16U Get_Settle_Energy_Data(INT8U Bef_Counts, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  STORA_DI Last_SDI;
  INT8U Err;
  INT16U Len;
  
  Len=Read_Storage_Data(_DI_LAST_SETTLE_ENERGY_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI), &Err);
  //读出的DI是否正确?
  if(sizeof(Last_SDI)!=Len ||\
  Last_SDI<_DI_SETTLE_ENERGY_DATA ||\
  Last_SDI>=_DI_SETTLE_ENERGY_DATA+MAX_ENERGY_SETTLE_NUM)//读出数据有错
  {
  ASSERT_FAILED();
  Last_SDI=_DI_SETTLE_ENERGY_DATA-1;
  }
  //Last_DI此时表示上个结算日数据存储的DI
  Last_SDI=(Last_SDI+MAX_ENERGY_SETTLE_NUM-Bef_Counts-1)%MAX_ENERGY_SETTLE_NUM;
  return Read_Storage_Data(Last_SDI, pDst, pDst_Start, DstLen, &Err);
}
*/
/*
//冻结电量数据, 将当前电量数据存储到电量历史数据区
void Settle_Energy_Data()
{
   STORA_DI Last_SDI;
   INT8U Err;
   INT16U Len;

   Len=Read_Storage_Data(_DI_LAST_SETTLE_ENERGY_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI), &Err);
   //读出的DI是否正确?
   if(sizeof(Last_SDI)!=Len ||\
   Last_SDI<_DI_SETTLE_ENERGY_DATA ||\
   Last_SDI>=_DI_SETTLE_ENERGY_DATA+MAX_ENERGY_SETTLE_NUM)//读出数据有错
   {
   ASSERT_FAILED();
   Last_SDI=_DI_SETTLE_ENERGY_DATA-1;
   }
   //Last_DI是本次结算数据应该存储的DI
   Last_SDI++;
   if(Last_SDI>=_DI_SETTLE_ENERGY_DATA+MAX_ENERGY_SETTLE_NUM)
   Last_SDI=_DI_SETTLE_ENERGY_DATA;

   Write_Storage_Data(Last_SDI, (void *)&Cur_Energy, sizeof(Cur_Energy));
   Write_Storage_Data(_DI_LAST_SETTLE_ENERGY_DI, &Last_SDI, sizeof(Last_SDI));
}
*/
#undef ENERGY_SETTLE_C