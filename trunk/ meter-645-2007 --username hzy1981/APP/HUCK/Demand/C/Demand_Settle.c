#define DEMAND_SETTLE_C
#include "Includes.h"

//检查DI是否是一个存储需量数据的DI
INT8U Check_Demand_Stora_DI(STORA_DI SDI)
{
  TRACE();

  if(Get_Storage_Data_Len(SDI) EQ DEMAND_SAVE_SIZE)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//读取某个历史需量的冻结时间
//SDI表示历史数据的存储DI
//pDst表示目标缓冲区
//pDst_Start表示目标缓冲区的开始
//DstLen目标缓冲区的长度
INT8U Read_Demand_Time(STORA_DI SDI, S_HEX_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  INT8U Re;

  TRACE();

  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + DEMAND_TIME_DATA_SIZE <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  Re = Check_Demand_Stora_DI(SDI);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return 0;
  }

  Len = Read_Storage_Data_Fix_Len(SDI, DEMAND_TIME_DATA_OFF, DEMAND_TIME_DATA_SIZE, pDst, pDst_Start, DstLen); 
  if(DEMAND_TIME_DATA_SIZE EQ Len)
  {
    return DEMAND_TIME_DATA_SIZE;
  }
  else
  {
    return 0;
  }
}

//读取需量分相数据
INT16U Read_Demand_Phase_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  INT8U Re;

  TRACE();

  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + DEMAND_PHASE_DATA_SIZE <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  Re = Check_Demand_Stora_DI(SDI);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return 0;
  }

  Len = Read_Storage_Data_Fix_Len(SDI, DEMAND_PHASE_DATA_OFF, DEMAND_PHASE_DATA_SIZE, pDst, pDst_Start, DstLen); 
  if(DEMAND_PHASE_DATA_SIZE EQ Len)
  {
    return DEMAND_PHASE_DATA_SIZE;
  }
  else
  {
    return 0;
  }
}


//读取某个历史需量在某个费率的数据
//SDI表示需量的存储DI
//Rate表示费率,0表示总
//pDst目标缓冲区
//pDst_Start和DstLen一起限定pDst和返回数据的长度
INT16U Read_Demand_Rate_Data(STORA_DI SDI, INT8U Rate, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  INT8U Re;

  TRACE();

  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + sizeof(S_One_Demand) <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  Re = Check_Demand_Stora_DI(SDI);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return 0;
  }

  Len = Read_Storage_Data_Fix_Len(SDI, (INT16U) (DEMAND_RATE_DATA_OFF(Rate)), sizeof(S_One_Demand), pDst, pDst_Start, DstLen); 
  if(sizeof(S_One_Demand) EQ Len)
  {
    return Len;
  }
  else
  {
    return 0;
  }
}

//写需量数据的时间
//DI表示需量的存储DI
//pTime表示写入的时间
void Write_Demand_Time(STORA_DI SDI, S_HEX_Time* pTime)
{
  INT8U Re; 

  TRACE();

  //时间可能是全0，默认数据的情况
  if(memcmp(pTime->Time, Zero, sizeof(pTime->Time)) != 0)
  {
    Re = Check_HEX_Time(pTime);
    ASSERT(1 EQ Re);
  }


  Re = Check_Demand_Stora_DI(SDI);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return;
  }

  Re = Write_Storage_Data_Fix_Len(SDI, DEMAND_TIME_DATA_OFF, pTime, sizeof(S_HEX_Time)); 
  if(Re != 1)
  {
    ASSERT_FAILED();
  }
}

//写需量三相数据
//pSrc表示需量的三相数据
//SrcLen表示数据长度
void Write_Demand_Phase_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen)
{
  INT8U Re;

  TRACE();

  if(!(DEMAND_PHASE_DATA_SIZE EQ SrcLen))
  {
    ASSERT_FAILED();
    return;
  }

  Re = Check_Demand_Stora_DI(SDI);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return;
  }

  Re = Write_Storage_Data_Fix_Len(SDI, DEMAND_PHASE_DATA_OFF, pSrc, SrcLen); 
  if(Re != 1)
  {
    ASSERT_FAILED();
  }
}
//写需量某个费率的数据
//SDI表示需量数据存储DI
//Rate表示费率
//pSrc表示写数据的起始
//SrcLen表示源数据的长度
void Write_Demand_Rate_Data(STORA_DI SDI, INT8U Rate, void* pSrc, INT16U SrcLen)
{
  INT8U Re; 

  TRACE();

  if(!(sizeof(S_One_Demand) EQ SrcLen && Rate <= MAX_RATES))
  {
    ASSERT_FAILED();
    return;
  }

  Re = Check_Demand_Stora_DI(SDI);
  if(Re != 1)
  {
    ASSERT_FAILED();
    return;
  }

  Re = Write_Storage_Data_Fix_Len(SDI, (INT16U) DEMAND_RATE_DATA_OFF(Rate), pSrc, SrcLen); 
  if(Re != 1)
  {
    ASSERT_FAILED();
  }
}

//读取最近一条需量结算数据的存储SDI
STORA_DI Read_Last_Settle_Demand_DI()
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  Len = Read_Storage_Data(_SDI_LAST_SETTLE_DEMAND_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI)); 
  //读出的DI是否正确?
  if(sizeof(Last_SDI) != Len || \
     Last_SDI < _SDI_SETTLE_DEMAND_DATA || \
     Last_SDI >= _SDI_SETTLE_DEMAND_DATA + MAX_DEMAND_SETTLE_NUM)//读出数据有错
  {
    ASSERT_FAILED(); 
    Last_SDI = _SDI_SETTLE_DEMAND_DATA;
  }
  return Last_SDI;
}

//写最近一次需量结算数据的存储DI
void Write_Last_Settle_Demand_DI(STORA_DI SDI)
{
  INT8U Re;

  TRACE();

  if(!(SDI >= _SDI_SETTLE_DEMAND_DATA && SDI < _SDI_SETTLE_DEMAND_DATA + MAX_DEMAND_SETTLE_NUM))
  {
    ASSERT_FAILED();
    SDI = _SDI_SETTLE_DEMAND_DATA;
  } 

  Re = Write_Storage_Data(_SDI_LAST_SETTLE_DEMAND_DI, &SDI, sizeof(SDI));
  ASSERT(1 EQ Re);
}

//设置历史需量数据为全FF，无效数据，在非第一个结算日结算时需要这样做
void Set_Demand_His_Invalid_Data(STORA_DI His_DI)
{
  INT8U i;
  //INT16U Len; 

  TRACE();

  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 

  mem_set((INT8U *)Pub_Buf0, 0xFF, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
  Write_Demand_Phase_Data(His_DI, (INT8U *)Pub_Buf0, DEMAND_PHASE_DATA_SIZE);

  //写总以及分费率数据
  for(i = 0; i <= MAX_RATES; i ++)
  {
    Write_Demand_Rate_Data(His_DI, i, (INT8U *)Pub_Buf0, sizeof(S_One_Demand));
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);  
  
}

//将当前存储区的需量数据存储到历史数据His_DI中
void Save_Cur_Demand_To_His_Data(STORA_DI His_DI)
{
  INT8U i, Re;
  INT16U Len; 

  TRACE();

  Re = Check_Demand_Stora_DI(His_DI);
  ASSERT(Re EQ 1);

  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 

  //写三相需量数据 
  Len = Read_Demand_Phase_Data(_SDI_CUR_DEMAND, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)); 
  if(DEMAND_PHASE_DATA_SIZE != Len)
  {
    ASSERT_FAILED();
    Len = Read_Demand_Phase_Data(_SDI_CUR_DEMAND_BAK, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)); 
    if(DEMAND_PHASE_DATA_SIZE != Len)
    {
      mem_set((INT8U *)Pub_Buf0, 0, DEMAND_PHASE_DATA_SIZE, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
      ASSERT_FAILED();
    }
  }

  Write_Demand_Phase_Data(His_DI, (INT8U *)Pub_Buf0, DEMAND_PHASE_DATA_SIZE);

  //写总以及分费率数据
  for(i = 0; i <= MAX_RATES; i ++)
  {
    //先读取当前需量各个费率数据，然后存储到历史数据区
    Len = Read_Demand_Rate_Data(_SDI_CUR_DEMAND, i, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)); 
    if(sizeof(S_One_Demand) != Len)
    {
      ASSERT_FAILED();
      //读取备份区
      Len = Read_Demand_Rate_Data(_SDI_CUR_DEMAND_BAK, i, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)); 
      if(DEMAND_PHASE_DATA_SIZE != Len)
      {
        mem_set((INT8U *)Pub_Buf0, 0, sizeof(S_One_Demand), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
        ASSERT_FAILED();
      }
    }

    Write_Demand_Rate_Data(His_DI, i, (INT8U *)Pub_Buf0, sizeof(S_One_Demand));
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}

//读取历史分相需量数据
INT16U Read_His_Demand_Time_Data(INT8U Bef_Counts, S_HEX_Time * pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  if(Bef_Counts EQ 0)//读取当月数据
  {
    //mem_cpy(pDst, (void *) &Cur_Demand.Phase_Demand[0], DEMAND_PHASE_DATA_SIZE, pDst_Start, DstLen); 
    //return DEMAND_PHASE_DATA_SIZE;
    ASSERT_FAILED();
    return 0;
  }
  else//读取历史数据
  {
    Last_SDI = Read_Last_Settle_Demand_DI(); //读取最近一个结算点的存储DI

    Last_SDI = Last_SDI - Bef_Counts + 1; //向前追溯Bef_Counts个结算点
    if(Last_SDI < _SDI_SETTLE_DEMAND_DATA)
      Last_SDI += MAX_DEMAND_SETTLE_NUM; 

    Len = Read_Demand_Time(Last_SDI, pDst, pDst_Start, DstLen); 
    if(Len != DEMAND_TIME_DATA_SIZE)
    {
      ASSERT_FAILED();
      mem_set(pDst, 0, DEMAND_TIME_DATA_SIZE, pDst_Start, DstLen);
      //return 0;
    }
    Debug_Print("Read_His_Demand_Time: ");
    Print_HEX_Time(pDst);
  }
  return DEMAND_TIME_DATA_SIZE;
}

//读取历史分相需量数据
INT16U Read_His_Demand_Phase_Data(INT8U Bef_Counts, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  if(Bef_Counts EQ 0)//读取当月数据
  {
    mem_cpy(pDst, (void *) &Cur_Demand.Phase_Demand[0], DEMAND_PHASE_DATA_SIZE, pDst_Start, DstLen); 
    //return DEMAND_PHASE_DATA_SIZE;
  }
  else//读取历史数据
  {
    Last_SDI = Read_Last_Settle_Demand_DI(); //读取最近一个结算点的存储DI

    Last_SDI = Last_SDI - Bef_Counts + 1; //向前追溯Bef_Counts个结算点
    if(Last_SDI < _SDI_SETTLE_DEMAND_DATA)
      Last_SDI += MAX_DEMAND_SETTLE_NUM; 

    Len = Read_Demand_Phase_Data(Last_SDI, pDst, pDst_Start, DstLen); 
    if(Len != DEMAND_PHASE_DATA_SIZE)
    {
      ASSERT_FAILED();
      mem_set(pDst, 0, DEMAND_PHASE_DATA_SIZE, pDst_Start, DstLen);
      //return 0;
    }
    Debug_Print("Read_His_Demand_Phase_Data, Time:");
    Print_HEX_Time(&(((S_One_Demand *)pDst)->Time));
  }
  return DEMAND_PHASE_DATA_SIZE;
}


//读取前几月的某费率需量数据
//Bef_Counts表示前几个结算点数据, 0表示当前数据
//Rate表示费率
//pDst表示目标缓冲区
//pDst_Start和DstLen一起限制返回数据长度
INT16U Read_His_Demand_Rate_Data(INT8U Bef_Counts, INT8U Rate, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  if(Bef_Counts EQ 0)//读取当月数据
  {
    //总和当前费率的数据放在内存中
    if(Rate EQ 0)//0表示总
    {
      mem_cpy(pDst, (void *) &Cur_Demand.Demand[0], sizeof(S_One_Demand), pDst_Start, DstLen); 
    }
    else if(Rate EQ Cur_Demand.Rate)
    {
      mem_cpy(pDst, (void *) &Cur_Demand.Demand[1], sizeof(S_One_Demand), pDst_Start, DstLen); 
    }
    else
    {
      Len = Read_Storage_Data_Fix_Len(_SDI_CUR_DEMAND, (INT16U) DEMAND_RATE_DATA_OFF(Rate), sizeof(S_One_Demand), pDst, pDst_Start, DstLen); 
      if(sizeof(S_One_Demand) != Len)
      {
        ASSERT_FAILED(); 
        Len = Read_Storage_Data_Fix_Len(_SDI_CUR_DEMAND_BAK, (INT16U) DEMAND_RATE_DATA_OFF(Rate), sizeof(S_One_Demand), pDst, pDst_Start, DstLen); 
        if(sizeof(S_One_Demand) != Len)
        {
          ASSERT_FAILED(); 
          mem_set(pDst, 0, sizeof(S_One_Demand), pDst_Start, DstLen); 
        }
      }
    }
  }
  else//读取历史数据
  {
    Last_SDI = Read_Last_Settle_Demand_DI(); //读取最近一个结算点的存储DI

    Last_SDI = Last_SDI - Bef_Counts + 1; //向前追溯Bef_Counts个结算点
    if(Last_SDI < _SDI_SETTLE_DEMAND_DATA)
      Last_SDI += MAX_DEMAND_SETTLE_NUM; 

    Len = Read_Demand_Rate_Data(Last_SDI, Rate, pDst, pDst_Start, DstLen); 
    if(sizeof(S_One_Demand) != Len)
    {
      ASSERT_FAILED(); 
      mem_set(pDst, 0, sizeof(S_One_Demand), pDst_Start, DstLen); 
    }
    
    Debug_Print("Read_His_Demand_Rate_Data, Time:");
    Print_HEX_Time(&(((S_One_Demand *)pDst)->Time));    
  }

  return sizeof(S_One_Demand);
}


//重置内存中的需量数据
void Reset_Demand_Ram_Data()
{
  INT8U i;
  
  //将初始需量写入存储器中  
  Debug_Print("Set Def Demand Data");
  
  DIS_PD_INT;
  mem_set((void *) &Cur_Demand, 0, sizeof(Cur_Demand), (void *) &Cur_Demand, sizeof(Cur_Demand));

  //mem_cpy((void *)&Cur_Demand.Demand[0].Time, (void *)&Cur_Time0,  sizeof(Cur_Time0), 
  //(void *)&Cur_Demand.Demand[0].Time,  sizeof(Cur_Demand.Demand[0].Time));

  //mem_cpy((void *)&Cur_Demand.Demand[1].Time, (void *)&Cur_Time0,  sizeof(Cur_Time0), 
  //(void *)&Cur_Demand.Demand[1].Time,  sizeof(Cur_Demand.Demand[1].Time));
  for(i = 0; i < 2; i ++)
  {
    SET_STRUCT_SUM(Cur_Demand.Demand[i].Time);
    SET_STRUCT_SUM(Cur_Demand.Demand[i]);
  }
  
  for(i = 0; i < 3; i ++)
  {
    SET_STRUCT_SUM(Cur_Demand.Phase_Demand[i].Time);
    SET_STRUCT_SUM(Cur_Demand.Phase_Demand[i]);
  }
  
  Cur_Demand.Rate = 1;//Cur_Rate_Info.Rate; //当前需量费率,Cur_Rate_Info可能还没有初始化好
  
  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);

  SET_STRUCT_SUM(Cur_Demand);
  EN_PD_INT;
  
  Clr_Demand_Accu(); //清需量累加单元
  
  //Clear_Cur_Demand_Ram_Data();
  /*
  INT8U i;
  
  TRACE();

  mem_set((void *) &Cur_Demand, 0, sizeof(Cur_Demand), (void *) &Cur_Demand, sizeof(Cur_Demand));
  
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);
  
  for(i = 0; i < 3; i ++)
    SET_STRUCT_SUM(Cur_Demand.Phase_Demand[i]);
    
  SET_STRUCT_SUM(Cur_Demand);
  */
}

//重置ROM中的需量数据
void Reset_Demand_Rom_Data(STORA_DI SDI, S_HEX_Time* pTime)//清空当前需量区数据
{
  //S_HEX_Time TempTime;
  INT8U Re, i;


  TRACE();

  Re = Check_HEX_Time(pTime);
  ASSERT(Re EQ 1);

  //先清空时间域,时间域清成0,这样在清数据域的过程中,如果发生异常复位,不会导致将请0后数据结算
  /*
  mem_set(&TempTime, 0, sizeof(TempTime), &TempTime, sizeof(TempTime));

  Re = Write_Storage_Data_Fix_Len(SDI, DEMAND_TIME_DATA_OFF, &TempTime, sizeof(S_HEX_Time)); 
  if(Re != 1)
  {
    ASSERT_FAILED();
  }
*/
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);

  mem_set((INT8U *) Pub_Buf0, 0, sizeof(S_Demand), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));

  //写分相数据
  Write_Demand_Phase_Data(SDI, (INT8U *)Pub_Buf0, DEMAND_PHASE_DATA_SIZE);

  //写总以及分费率数据
  for(i = 0; i <= MAX_RATES; i ++)
  {
    Write_Demand_Rate_Data(SDI, i, (INT8U *)Pub_Buf0, sizeof(S_One_Demand));
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);

  //重写时间域
  Re = Write_Storage_Data_Fix_Len(SDI, DEMAND_TIME_DATA_OFF, pTime, sizeof(S_HEX_Time)); 
  if(Re != 1)
  {
    ASSERT_FAILED();
  }
}

/*---该函数为修改需量不不结算，以及非第一结算日置FF之前的函数
//冻结需量数据, pTime就是冻结时间点
//pTime为掉电时间后的第一个结算时间或者当前结算时间
void Settle_Demand_Data(S_HEX_Time* pTime)
{
  STORA_DI Last_SDI; 
  INT8U i; 
  S_HEX_Time TempTime; 
  //S_HEX_Time Last_Data_Time, Cur_Data_Time; 


  TRACE();

  Debug_Print("----------Settle Demand Data----------");
  
  Debug_Print("Settle From Time:");
  Print_HEX_Time(pTime);
    
  //读取最后一次结算数据的存储DI
  Last_SDI = Read_Last_Settle_Demand_DI();
  
  //获取当前需量数据的结算时间点
  //Get_Last_Settle_Time(pTime, &TempTime, &TempTime, sizeof(TempTime));   
  //Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime)); 
  //结算时间点在当前时间点以后,则说明当前需量数据的结算时间点未到,不需结算
  if(Cmp_Time(pTime, (S_HEX_Time *)&Cur_Time0) EQ TIME_AFT)
  {
    Debug_Print("Cur Demand Time, no settle");
    return;
  }
   
  //前一次如果结算了，则不再结算，防止结算后马上掉电上电
  Read_Demand_Time(Last_SDI, &TempTime, &TempTime,sizeof(TempTime));
  if(memcmp(&TempTime, pTime, sizeof(TempTime)) EQ 0)
  {
    Debug_Print("Same as Last settle time!");    
    return;
  }
 
  Get_N_Last_Settle_Time(MAX_ENERGY_SETTLE_NUM, (S_HEX_Time *)(&Cur_Time0), &TempTime, &TempTime, sizeof(TempTime));
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
  //--------------------------  
    Save_Cur_Demand_Data();//将内存中的需量数据保存到 ROM中的当前需量区
    mem_cpy(&TempTime, pTime, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
    //这则需量数据时间
    INC_DEMAND_SETTLE_DI(Last_SDI);  
    Write_Demand_Time(Last_SDI, &TempTime); 
    Save_Cur_Demand_To_His_Data(Last_SDI);//将当前需量数据区的数据存储到Last_DI存储区
    Write_Last_Settle_Demand_DI(Last_SDI);//保存Last_DI到_SDI_LAST_SETTLE_DEMAND_DI
  
    for(i = 0; i < MAX_DEMAND_SETTLE_NUM; i ++)
    {
      INC_DEMAND_SETTLE_DI(Last_SDI);//增加Last_DI
  
      Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime)); 
      
      Debug_Print("Settle Reset Demand Data, Time:");
      Print_HEX_Time((S_HEX_Time *) &TempTime);
      
      if(Cmp_Time(&TempTime, (S_HEX_Time *)&Cur_Time0) != TIME_AFT)
      {
        Debug_Print("--not the settle SDI, reset rom--");
        Reset_Demand_Rom_Data(Last_SDI, &TempTime);
        Write_Last_Settle_Demand_DI(Last_SDI);//保存Last_DI到_SDI_LAST_SETTLE_DEMAND_DI
      }
      else
        break;
    }
  }
  
  //更新当前需量数据区数据,同时需量数据区时间为当前分钟
  mem_cpy(&TempTime, (S_HEX_Time *)&Cur_Time0, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
  Set_Def_Cur_Demand_Data(&TempTime); //结算完后清需量  
}
*/
extern void _mem_cpy(INT8U *pDst, INT8U *pSrc, INT16U SrcLen, INT8U *pDst_Start, INT16U DstLen);
//Flag位0表示清0，1表示正常结算
void Settle_Demand_FF_Data(INT8U Flag)
{
  INT8U i,j,k, Type;
  INT16U Len;
  PROTO_DI PDI;

  Len = 0;  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  for(i =0; i <= 9; i ++)
  { 
    if(Flag > 0)
    {
      Len = Read_Storage_Data(EH_DI(0x01010000) + i, (INT8U *)Pub_Buf0, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));  
      if(Len EQ 0)
        mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
      
      for(j = 0; j <= MAX_RATES; j ++)
      {
        _mem_cpy((INT8U *)Pub_Buf0 + (INT16U)j*MAX_DEMAND_SETTLE_NUM*8 + 8, (INT8U *)Pub_Buf0 + (INT16U)j*MAX_DEMAND_SETTLE_NUM*8,\
                  MAX_DEMAND_SETTLE_NUM*8 - 8, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
        
        PDI = 0x01010000 + ((INT32U)i << 16) + ((INT32U)j << 8);
       
        if(Flag EQ 1)
          Len =_Get_DLT645_Data(PDI, (void *) Zero, 0, (INT8U *)Pub_Buf0 + (INT16U)j*MAX_DEMAND_SETTLE_NUM*8, \
                               (INT8U *)Pub_Buf0, sizeof(Pub_Buf0), FOR_EVENT, &Type); 
        else //if(Flag > 1) //非第一结算日，数据置成FF
          mem_set((INT8U *)Pub_Buf0 + (INT16U)j*MAX_DEMAND_SETTLE_NUM*8, 0xFF, 8, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0)); 
      }
    }
    else
      mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
      
    Len = Get_Storage_Data_Len(EH_DI(0x01010000) + i);
    Write_Storage_Data(EH_DI(0x01010000) + i, (INT8U *)Pub_Buf0, Len);   
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}

//冻结需量数据, pTime就是冻结时间点
//pTime为掉电时间后的第一个结算时间或者当前结算时间
void Settle_Demand_Data(S_HEX_Time* pTime)
{
  STORA_DI Last_SDI; 
  //INT8U Flag;
  S_HEX_Time TempTime; 
  //S_HEX_Time Last_Data_Time, Cur_Data_Time; 


  TRACE();

  Debug_Print("----------Settle Demand Data----------");
  
  Debug_Print("Settle Time:");
  Print_HEX_Time(pTime);
    
  //读取最后一次结算数据的存储DI
  Last_SDI = Read_Last_Settle_Demand_DI();

  //前一次如果结算了，则不再结算，防止结算后马上掉电上电
  Read_Demand_Time(Last_SDI, &TempTime, &TempTime,sizeof(TempTime));
  if(memcmp(&TempTime, pTime, sizeof(TempTime)) EQ 0)
  {
    Debug_Print("Same as Last settle time!");    
    return;
  }
 
  //是第一个结算日，则进行正常结算
  if(Settle_Time.Time_D_H[0][0] EQ Cur_Time1.Hour && Settle_Time.Time_D_H[0][1] EQ Cur_Time1.Date)
  {
    //--------------------------  
    Save_Cur_Demand_Data();//将内存中的需量数据保存到 ROM中的当前需量区
    Settle_Demand_FF_Data(0x01);
    //这则需量数据时间
    INC_DEMAND_SETTLE_DI(Last_SDI);  
    Write_Demand_Time(Last_SDI, pTime); 
    Save_Cur_Demand_To_His_Data(Last_SDI);//将当前需量数据区的数据存储到Last_DI存储区
    
    //更新当前需量数据区数据,同时需量数据区时间为当前分钟
    //mem_cpy(&TempTime, (S_HEX_Time *)&Cur_Time0, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
    Set_Def_Cur_Demand_Data(pTime); //结算完后清需量
    //Flag = 0x01;
  }
  else //不是第一结算日，则置数据为FF
  {
    Settle_Demand_FF_Data(0x02);
    Debug_Print("Not the first settle day!");
    INC_DEMAND_SETTLE_DI(Last_SDI);     
    Set_Demand_His_Invalid_Data(Last_SDI);
    //Flag = 0x02;
  }
  
  Write_Last_Settle_Demand_DI(Last_SDI);//保存Last_DI到_SDI_LAST_SETTLE_DEMAND_DI 
  
}

//上电补冻需量数据
void PowerOn_Settle_Demand_Data()
{
  S_HEX_Time TempTime;
  
  TRACE();

  //如果Hex_PD_Time本身是结算时间点，则应该使之指向下一个结算点
  if(Check_HEX_Time((S_HEX_Time *) &Hex_PD_Time))
  {  
    Get_Next_Settle_Time((S_HEX_Time *) &Hex_PD_Time, &TempTime, &TempTime, sizeof(TempTime));
    Settle_Demand_Data((S_HEX_Time *) &TempTime);
  }
}
#undef DEMAND_SETTLE_C
