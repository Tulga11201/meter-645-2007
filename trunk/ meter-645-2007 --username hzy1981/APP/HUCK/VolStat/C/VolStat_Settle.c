#define VOLSTAT_SETTLE_C
#include <includes.h>

//计算历史电量、需量、和电压统计数据的存储DI
//因为一般都是存储上N月的数据，所以存储的索引是根据总月数生成的
STORA_DI Calc_His_VolStat_Data_DI(S_HEX_Time* pTime)
{
  INT8U Re;
  STORA_DI SDI;

  Re = Check_HEX_Time(pTime);
  if(1 != Re)//ASSERT(Re EQ 1))
  {
    ASSERT_FAILED();
    return NULL_4BYTES;
  }    


  SDI = _SDI_SETTLE_VOLSTAT_DATA + (pTime -> Time[T_MONTH] + (pTime -> Time[T_YEAR]) * 12) % MAX_VOLSTAT_SETTLE_NUM;  

  return SDI;
}

//获取前几个月的历史数据的DI
//Data_Flag数据标志
//HIS_ENERGY_DATA;
//HIS_DEMAND_DATA;
//HIS_VOLSTAT_DATA;
//Bef_Month前几个月
//返回数据的存储DI
STORA_DI Calc_His_VolStat_Data_DI_Bef_Month(INT8U Bef_Month)
{
  S_HEX_Time Temp_Time;
  Time_Dec((S_HEX_Time *) &Cur_Time0, Bef_Month, UNIT_MON, (S_HEX_Time *) &Temp_Time);//将时间向前推移Bef_Mon个月
  return Calc_His_VolStat_Data_DI(&Temp_Time);
}

//读取前几次的历史电能数据
//Bef_Counts, 表示是前几次, 0表示读取当前数据
//pDst表示目标缓冲区
//pDst_Start和DstLen一起限定pDst和返回长度的范围
//pErr返回0时表示用来表示错误原因
INT16U Read_His_VolStat_Data(INT8U Bef_Counts, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  STORA_DI Last_SDI;
  INT16U Len;

  if(Bef_Counts > 0)//读历史数据
  {
    Last_SDI = Read_Last_Settle_VolStat_DI();

    Last_SDI = Last_SDI - Bef_Counts + 1;//向前追溯Bef_Counts个结算点
    if(Last_SDI < _SDI_SETTLE_VOLSTAT_DATA)
      Last_SDI += MAX_VOLSTAT_SETTLE_NUM;

    Len = Read_Storage_Data(Last_SDI, pDst, pDst_Start, DstLen);
    if(Len != sizeof(Cur_VolStat))
    {
      ASSERT_FAILED();
      return 0;
    }
    Debug_Print("Read_His_VolStat_Data, Time:");
    Print_HEX_Time(& (((S_VolStat *)pDst) -> Time));
  }
  else//读当前数据
  {
    mem_cpy(pDst, (void *) &Cur_VolStat, sizeof(Cur_VolStat), pDst_Start, DstLen);
    //return sizeof(Cur_Energy);
  }
  return sizeof(Cur_VolStat);
}

//检查pTime是否是电压统计结算时间
INT8U Check_Volstat_Settle_Time(S_BCD_Time* pTime)
{
  /*
  if(pTime -> Hour EQ Settle_Time.Time_D_H[0][0] && \
     pTime -> Date EQ Settle_Time.Time_D_H[0][1] && \
     pTime -> Min EQ 0)
  {
    return 1;
  }

  return 0;
  */
  if(pTime -> Min EQ 0 && pTime -> Hour EQ 0 &&  pTime -> Date EQ 1)
    return 1;

  return 0;  
}

//写历史电量电压统计等数据,写需量历史数据是在Write_Demand_His_VolStat_Data函数中单独处理 
//pTime电量，电压统计等数据的存储时间
//pSrc写数据缓冲区
//SrcLen数据长度
//返回值
//返回NO_ERR表示写成功
INT8U Write_His_VolStat_Data(S_HEX_Time* pTime, void* pSrc, INT16U SrcLen)
{
  //INT8U Index;
  INT8U Re;
  INT16U Len;
  STORA_DI SDI;

  SDI = Calc_His_VolStat_Data_DI(pTime);
  if(NULL_4BYTES EQ SDI)//ASSERT(NULL_4BYTES != SDI))
  {
    ASSERT_FAILED();
    return 0;
  }

  Len = Get_Storage_Data_Len(SDI); //数据长度
  //数据长度必须满足在参数规定范围内
  if(Len != SrcLen)
  {
    ASSERT_FAILED();
    return 0;
  }

  //写存储数据
  Re = Write_Storage_Data(SDI, pSrc, Len);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return 0;
  }
  else
  {
    return 1;
  }
}

//获得pSrc时间点之前的最近一个电压统计结算时间点,认为每月的1日0时0分为结算时间
void Get_Last_VolStat_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  S_HEX_Time TempTime;

  mem_cpy(&TempTime, pSrc, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));

  TempTime.Time[T_DATE] = 0x01;
  TempTime.Time[T_HOUR] = 0x00;
  TempTime.Time[T_MIN] = 0x00;

  SET_STRUCT_SUM(TempTime);

  if(Cmp_Time(pSrc, &TempTime) EQ TIME_EQU)
  {
    Time_Dec(&TempTime, 1, UNIT_MON, pDst);
  }
  else
  {
    mem_cpy(pDst, &TempTime, sizeof(TempTime), pDst_Start, DstLen);
  }
  //Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst -> CS));

} 

void Get_N_Last_VolStat_Settle_Time(INT8U N, S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  INT8U i;
  S_HEX_Time TempTime;

  mem_cpy(&TempTime, pSrc, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
  for(i = 0; i < N; i ++)
  {
    Get_Last_VolStat_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
  }
  mem_cpy(pDst, &TempTime, sizeof(TempTime), pDst_Start, DstLen);
}
//获得pSrc时间点之后的最近一个电压统计结算时间点,认为每月的1日0时0分为结算时间
void Get_Next_VolStat_Settle_Time(S_HEX_Time* pSrc, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  Time_Inc(pSrc, 1, UNIT_MON, pDst);

  pDst -> Time[T_DATE] = 0x01;
  pDst -> Time[T_HOUR] = 0x00;
  pDst -> Time[T_MIN] = 0x00;
  Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst -> CS));
}

STORA_DI Read_Last_Settle_VolStat_DI()
{
  INT16U Len;
  STORA_DI Last_SDI;

  Len = Read_Storage_Data(_SDI_LAST_SETTLE_VOLSTAT_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI));
  //读出的DI是否正确?
  if(sizeof(Last_SDI) != Len || \
     Last_SDI < _SDI_SETTLE_VOLSTAT_DATA || \
     Last_SDI >= _SDI_SETTLE_VOLSTAT_DATA + MAX_VOLSTAT_SETTLE_NUM)//读出数据有错
  {
    ASSERT_FAILED();
    Last_SDI = _SDI_SETTLE_VOLSTAT_DATA;
  }
  return Last_SDI;
}

//将当前电压统计数据冻结，pTime传入冻结时刻，一般就是当前时间
void Settle_VolStat_Data(S_HEX_Time* pTime)
{
  STORA_DI Last_SDI; 
  //INT16U Len;
  //S_HEX_Time TempTime; 
  //S_HEX_Time Last_Data_Time, Cur_Data_Time; 


  TRACE();

  Debug_Print("----------Settle VolStat Data----------");
  
  Debug_Print("Settle Time:");
  Print_HEX_Time(pTime);
  
  if(!(Settle_Time.Time_D_H[0][0] EQ Cur_Time1.Hour && Settle_Time.Time_D_H[0][1] EQ Cur_Time1.Date))
  {
    Debug_Print("Not the first settle day");
    return;
  }  
  
  //读取最后一次结算数据的存储DI
  Last_SDI = Read_Last_Settle_VolStat_DI();

  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  //前一次如果结算了，则不再结算，防止结算后马上掉电上电
  Read_Storage_Data(Last_SDI, (INT8U *)Pub_Buf, (INT8U *)Pub_Buf,sizeof(Pub_Buf));
  if(memcmp(pTime, &(((S_VolStat *)Pub_Buf) -> Time), sizeof(S_HEX_Time)) != 0)
  {
    //是第一个结算日，则进行正常结算
    mem_cpy((INT8U *)&Cur_VolStat.Time, pTime, sizeof(S_HEX_Time), (INT8U *)&Cur_VolStat.Time, sizeof(Cur_VolStat.Time));
    SET_STRUCT_SUM(Cur_VolStat);
    
    INC_VOLSTAT_SETTLE_DI(Last_SDI);     
    Write_Storage_Data(Last_SDI, (void *) &Cur_VolStat, sizeof(Cur_VolStat));
    Write_Storage_Data(_SDI_LAST_SETTLE_VOLSTAT_DI, &Last_SDI, sizeof(Last_SDI));
      
    mem_set((void *) &Cur_VolStat, 0, sizeof(Cur_VolStat), \
            (void *) &Cur_VolStat, sizeof(Cur_VolStat));//将数据全部清0存入当前存储区，下次读出全0数据，表示尚未生成新数据
    
    INIT_STRUCT_VAR(Cur_VolStat);
    SET_DATA_READY_FLAG(Cur_VolStat);   
    SET_STRUCT_SUM(Cur_VolStat);    
    //更新存储区数据  
    Save_Cur_VolStat_PD_Data();
    Save_Cur_VolStat_Data();
  }
  else
  {
    Debug_Print("Same as Last settle time!");      
  }
  
  OS_Mutex_Post(PUB_BUF_SEM_ID);   
 
}

//上电补冻电压统计数据
void PowerOn_Settle_VolStat_Data()
{
  Settle_VolStat_Data((S_HEX_Time *) &Cur_Time0);
}
#undef VOLSTAT_SETTLE_C