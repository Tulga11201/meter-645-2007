#define VOLSTAT_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H23"
#endif

void Read_VolStat_Para_From_Rom()
{
  INT16U Len;
  INT8U Temp[12];

  Len = Read_Storage_Data(0x04000E03, Temp, Temp, sizeof(Temp));
  ASSERT(Len EQ 2);
  VolStat_Para.Qual_Upper_Limit = Bcd2Hex(Temp, 2);// * VOL_RATIO;

  Len = Read_Storage_Data(0x04000E04, Temp, Temp, sizeof(Temp));
  ASSERT(Len EQ 2);
  VolStat_Para.Qual_Lower_Limit = Bcd2Hex(Temp, 2);// * VOL_RATIO;

  Len = Read_Storage_Data(0x04090C01, Temp, Temp, sizeof(Temp));
  ASSERT(Len EQ 2);
  VolStat_Para.Exam_Upper_Limit = Bcd2Hex(Temp, 2);// * VOL_RATIO;

  Len = Read_Storage_Data(0x04090C02, Temp, Temp, sizeof(Temp));
  ASSERT(Len EQ 2);
  VolStat_Para.Exam_Lower_Limit = Bcd2Hex(Temp, 2);// * VOL_RATIO;  

  SET_STRUCT_SUM(VolStat_Para);
}

void VolStat_Min_Proc()
{
  INT8U i, Re;

  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};

  //MEASU_INSTANT* p;//电压是4位小数,VolStat_Para中的电压参数也已经转化为了4位小数

  TRACE();
    
  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(Re EQ 1);
  
  if(Min_Bak.Var EQ 0xFF)//第一次进入该函数，需要等1分钟后进入分钟计数
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];
  }

  //每分钟有个结算
  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];
    
    if(VolStat_Count.Sec < 30) //没有30s，不做处理
      return;
        
    DIS_PD_INT;//关掉电中断
    
    /*
    for(i = 0; i < 3; i ++)
    {
      if(VolStat_Count.Exam_Upper[i] EQ 0 && VolStat_Count.Exam_Lower[i] EQ 0)
    
    }
    */
    
    for(i = 0; i < 4; i++)//三相分别考核
    {
      if(i EQ 1 && Get_SysParse_Mode() != PARSE_341)//331情况下不对B相进行考核
      {
        //对B相统计情况清0
        Cur_VolStat.Total_Time[i] = 0;
        
        Cur_VolStat.Upper_Time[i] = 0;
        Cur_VolStat.Lower_Time[i] = 0;
        Cur_VolStat.Qual[i] = 0;

        continue;
      }
   
      //该分钟内电压都发生在考核范围内才进行统计
      if(VolStat_Count.Exam_Upper[i] EQ 0 && VolStat_Count.Exam_Lower[i] EQ 0)
      {
        //该分钟内没有发生一次电压超考核上限也没有发生一次电压超考核下限
        //这样才认为电压在考核范围内
        Cur_VolStat.Total_Time[i]++;//检测总时间
        //Total_VolStat.Total_Time[i]++;//总监测时间

        if(0 != VolStat_Count.Qual_Upper[i] || \
           0 != VolStat_Count.Qual_Lower[i])//电压不合格
        {
          if(VolStat_Count.Qual_Upper[i] > VolStat_Count.Qual_Lower[i])//电压超上
          {
            Cur_VolStat.Upper_Time[i]++;
          }
          else
          {
            Cur_VolStat.Lower_Time[i]++;
          }
        }
      }
      
      //计算分相当月电压合格率
      if(Cur_VolStat.Total_Time[i] != 0 && \
         Cur_VolStat.Total_Time[i] > Cur_VolStat.Upper_Time[i] + Cur_VolStat.Lower_Time[i])
        Cur_VolStat.Qual[i] = (Cur_VolStat.Total_Time[i] - Cur_VolStat.Upper_Time[i] - Cur_VolStat.Lower_Time[i]) * 10000 / Cur_VolStat.Total_Time[i];
      else
        Cur_VolStat.Qual[i] = 0;
      
      Cur_VolStat.Exam[i] = 10000 - Cur_VolStat.Qual[i];
    }


    SET_STRUCT_SUM(Cur_VolStat);
    //SET_STRUCT_SUM(Total_VolStat);
    //每分钟过去将该分钟内的统计数据清0
    Clear_VolStat_Count_Ram();
    EN_PD_INT;//开掉电中断
  } 
  
}

void VolStat_Sec_Proc()
{
  INT8U i, Re;
  INT32U Volt;

  static S_Int32U Sec_Bak = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};

  MEASU_INSTANT* p;//电压是4位小数,VolStat_Para中的电压参数也已经转化为了4位小数
  
  TRACE();
  
  Re = CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(Re EQ 1);

  //每秒比较一下当前电压值
  if(Sec_Bak.Var != Sec_Timer_Pub)
  {
    Re = CHECK_STRUCT_SUM(Cur_VolStat);
    if(Re EQ 0)
    {
      ASSERT_FAILED();
      Check_Data_Avail();
    }
    
    Re = CHECK_STRUCT_SUM(VolStat_Count);
    if(Re EQ 0)
    {
      ASSERT_FAILED();
      Clear_VolStat_Count_Ram();
    }
    
    Sec_Bak.Var = Sec_Timer_Pub;

    VolStat_Count.Sec ++;
    p = (MEASU_INSTANT *) &Measu_InstantData_ToPub_PUCK;//瞬时量数据
    
    for(i = 0; i < 3; i ++)
    {
      if(i EQ 0)
        Volt = p -> Volt.A/VOL_RATIO;  
      else if(i EQ 1)
      {
        //B相数据只有是三相四线才进行电压统计
        if(Get_SysParse_Mode() != PARSE_341)
          continue;
        
        Volt = p -> Volt.B/VOL_RATIO;
      }
      else
        Volt = p -> Volt.C/VOL_RATIO;
      
//-----------当前是否在考核范围内?不在则进行下一相处理-------------
      if(Volt > VolStat_Para.Exam_Upper_Limit)//电压越考核上限
      {
        VolStat_Count.Exam_Upper[i] ++;
        VolStat_Count.Exam_Upper[3] ++; //总越考核上限进行累加
        continue;             //不在考核范围内不进行下面的处理
      }
      else if(Volt < VolStat_Para.Exam_Lower_Limit)//电压越考核下限
      {
        VolStat_Count.Exam_Lower[i] ++;
        VolStat_Count.Exam_Lower[3] ++; //总越考核下限进行累加
        continue;            //不在考核范围内不进行下面的处理
      }
      
      if(Volt > VolStat_Para.Qual_Upper_Limit)//电压越合格上限
      {
        VolStat_Count.Qual_Upper[i] ++;
        VolStat_Count.Qual_Upper[3] ++; //总超合格上限累加
      }
      else if(Volt < VolStat_Para.Qual_Lower_Limit)//电压越合格下限
      {
        VolStat_Count.Qual_Lower[i] ++;
        VolStat_Count.Qual_Lower[3] ++; //总超合格下限累加
      }
      
//-----------------------------------------------------------------
      
      DIS_PD_INT;
      //////////判断最高与最低电压////////////////////////
      if(Volt > Cur_VolStat.Max_Vol[3])//总的最高电压
      {
        Cur_VolStat.Max_Vol[3] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Max_Vol_Time[3], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Max_Vol_Time[3], sizeof(Cur_VolStat.Max_Vol_Time[3]));
        SET_STRUCT_SUM(Cur_VolStat);
      }
      else if(Cur_VolStat.Min_Vol[3] EQ 0 || Volt < Cur_VolStat.Min_Vol[3])//总的最低电压
      {
        Cur_VolStat.Min_Vol[3] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Min_Vol_Time[3], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Min_Vol_Time[3], sizeof(Cur_VolStat.Min_Vol_Time[3]));
        SET_STRUCT_SUM(Cur_VolStat);      
      }
      
      if(Volt > Cur_VolStat.Max_Vol[i])//分相最高电压
      {
        Cur_VolStat.Max_Vol[i] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Max_Vol_Time[i], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Max_Vol_Time[i], sizeof(Cur_VolStat.Max_Vol_Time[i]));
        SET_STRUCT_SUM(Cur_VolStat);
      }
      else if(Cur_VolStat.Min_Vol[i] EQ 0 || Volt < Cur_VolStat.Min_Vol[i])//分相最低电压
      {
        Cur_VolStat.Min_Vol[i] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Min_Vol_Time[i], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Min_Vol_Time[i], sizeof(Cur_VolStat.Min_Vol_Time[3]));
        SET_STRUCT_SUM(Cur_VolStat);   
      }  
      EN_PD_INT;
    }
    
    SET_STRUCT_SUM(VolStat_Count);
  }
}

//电压统计处理过程
void VolStat_Proc()
{
  VolStat_Min_Proc();
  VolStat_Sec_Proc();
}

//请当月电压统计数据
void Set_Def_Cur_VolStat_Data()
{
  //将初始需量写入存储器中  
  Debug_Print("Set Def Cur VolStat Data");
  Clear_Cur_VolStat_Ram();


  Save_Cur_VolStat_Data();
  Save_Cur_VolStat_PD_Data();
}

//设置默认的电压统计数据
void Set_Def_VolStat_Data()
{
  INT8U i;

  Debug_Print("Set Def VolStat Data");
  
  Set_Def_Cur_VolStat_Data();

  for(i = 0; i < MAX_VOLSTAT_SETTLE_NUM; i ++)
  {
    Write_Storage_Data(_SDI_SETTLE_VOLSTAT_DATA + i, (void *) &Cur_VolStat, sizeof(Cur_VolStat));
  }
}

//保存当前电压统计数据
void Save_Cur_VolStat_Data()
{
  if(CHECK_STRUCT_SUM(Cur_VolStat))
  {
    Write_Storage_Data(_SDI_CUR_VOLSTAT, (void *) (&Cur_VolStat), sizeof(Cur_VolStat));
  }
  else
  {
    ASSERT_FAILED();
  }

  //OS_TimeDly_Ms(100);
}

//保存当前电压统计数据
void Save_Cur_VolStat_PD_Data()
{
  if(Check_VolStat_Data((S_VolStat *) &Cur_VolStat))
  {
    Write_Storage_Data(_SDI_CUR_VOLSTAT_PD, (void *) (&Cur_VolStat), sizeof(Cur_VolStat));
  }
  else
  {
    ASSERT_FAILED();
  }
}

//保存当前电压统计数据
//此函数因为是掉电存储，因此没有延时函数
void PowerDown_Save_VolStat_Data()
{
  Write_Storage_Data(_SDI_CUR_VOLSTAT, (void *) (&Cur_VolStat), sizeof(Cur_VolStat));
  //Write_Storage_Data(_SDI_TOTAL_VOLSTAT, (void *) (&Total_VolStat), sizeof(Total_VolStat));
}

//检查电压统计数据是否正确
INT8U Check_VolStat_Data(S_VolStat* pVolStat)
{
  INT8U Re;

  Re = 1;
  Re &= (pVolStat->Head EQ CHK_BYTE && pVolStat->Tail EQ CHK_BYTE) ? 1 : 0;  
  Re &= Check_STRUCT_Sum(pVolStat, sizeof(S_VolStat), pVolStat->CS, sizeof(pVolStat->CS));
  Re &= (pVolStat->Data_Ready_Flag EQ DATA_READY) ? 1 : 0;
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    return 0;
  }  
  return Re;
}

//从ROM中读取电压统计数据
void Read_VolStat_Data_From_Rom()
{
  S_VolStat* p;

  //先读取掉电存储区数据
  //再读普通数据
  //读当前电压检测数据
  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  p = (S_VolStat *) Pub_Buf0;

  if(Read_Storage_Data(_SDI_CUR_VOLSTAT_PD, p, p, sizeof(Pub_Buf0))\
     != sizeof(Cur_VolStat) || Check_VolStat_Data(p) != 1)
  {
    Debug_Print("Read _SDI_CUR_VOLSTAT_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(_SDI_CUR_VOLSTAT, p, p, sizeof(Pub_Buf0))\
       != sizeof(Cur_VolStat) || Check_VolStat_Data(p) != 1)//该参数有默认参数项,实际上不会进入下面的括号
    {
      Debug_Print("Read _SDI_CUR_VOLSTAT data error");
      //如果所有的备份区数据都没读出来则认为是第一次上电，电量清0
      mem_cpy(p, (void *) Def_VolStat, sizeof(Cur_VolStat), p, sizeof(Pub_Buf0));
    }
  }       

  DIS_PD_INT;
  
  mem_cpy((void *) &Cur_VolStat, p, sizeof(Cur_VolStat), (void *) &Cur_VolStat, sizeof(Cur_VolStat));
  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);
  SET_STRUCT_SUM(Cur_VolStat);
  
  EN_PD_INT;          

  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}

//检查电压统计相关参数的合法性
void Check_VolStat_Para_Avail()
{
  INT8U Re;

  Re = CHECK_STRUCT_SUM(VolStat_Para);  
  if(0 EQ Re)
  {
    ASSERT_FAILED(); 
    Read_VolStat_Para_From_Rom();
  }
}

//检查电压统计相关数据的合法性
void Check_VolStat_Data_Avail()
{
  INT8U Re;

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Cur_VolStat);
  Re &= CHECK_STRUCT_SUM(Cur_VolStat);
  //Re &= CHECK_STRUCT_SUM(Total_VolStat);
  if(0 EQ Re)
  {
    ASSERT_FAILED();
    Read_VolStat_Data_From_Rom();
  }
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(VolStat_Count);
  Re &= CHECK_STRUCT_SUM(VolStat_Count);
  
  if(0 EQ Re)
  {
    ASSERT_FAILED();
    Clear_VolStat_Count_Ram();
    
  }
}


//清电压统计数据
void Clear_VolStat_Data()
{
  Debug_Print("Clear_VolStat_Data!!!");  
  Set_Def_Cur_VolStat_Data();
}

//清除VolStat_Count的内存数据
void Clear_VolStat_Count_Ram()
{
  mem_set((void *) &VolStat_Count, 0, sizeof(VolStat_Count), (void *) &VolStat_Count, sizeof(VolStat_Count));
  INIT_STRUCT_VAR(VolStat_Count);
  SET_STRUCT_SUM(VolStat_Count);
}

//清某相的电压统计数据
INT8U Clear_Phase_VolStat_Data(S_VolStat *p, INT8U Phase)
{
  if(Phase > 3)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  p -> Total_Time[Phase] = 0;//三相监测总时间,3表示总,0-2分别表示A、B、C三相，
  p -> Upper_Time[Phase] = 0;//超上时间
  p -> Lower_Time[Phase] = 0;//超下时间
  
  p -> Qual[Phase] = 0;//三相合格率
  p -> Exam[Phase] = 0;//超限率
  
  p -> Max_Vol[Phase] = 0;//最高电压
  mem_set((void *)(p -> Max_Vol_Time[Phase]), 0, sizeof(p -> Max_Vol_Time[Phase]),\
        (void *)(p -> Max_Vol_Time[Phase]), sizeof(p -> Max_Vol_Time[Phase]));//时间，16进制数
  
  p -> Min_Vol[Phase] = 0;//最低电压
  mem_set((void *)(p -> Min_Vol_Time[Phase]), 0, sizeof(p -> Min_Vol_Time[Phase]), \
        (void *)(p -> Min_Vol_Time[Phase]), sizeof(p -> Min_Vol_Time[Phase])); //时间，16进制数
  
  //SET_STRUCT_SUM(Cur_VolStat);  
  OS_Set_STRUCT_Sum(p, sizeof(S_VolStat), p -> CS, sizeof(p -> CS));
  
  return 1;
}

//清总或某相电压统计数据
INT8U Clear_Proto_Phase_VolStat_Data(PROTO_DI PDI)
{
  INT16U Len;
  STORA_DI SDI;
  INT8U i, j;
  S_VolStat *p;

  if(((PDI >> 8) & 0xFF) EQ 0)
    i = 3; //总
  else //1-3分别表示A、B、C三相
    i = ((PDI >> 8) & 0xFF) - 1;
  
  if(i <= 3)
  {
    DISP_CLR_DATA_INFO;
    
    Clear_Phase_VolStat_Data((S_VolStat *)&Cur_VolStat, i);
    Save_Cur_VolStat_Data();
    Save_Cur_VolStat_PD_Data();
    
    SDI = (PDI & 0xFFFFFF00);
    
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    mem_set((void *)Pub_Buf0, 0, sizeof(Pub_Buf0), (void *)Pub_Buf0, sizeof(Pub_Buf0));
    p = (S_VolStat *)Pub_Buf0;    
    for(j = 1; j <=MAX_VOLSTAT_SETTLE_NUM; j ++)
    {
      //Len = Get_Storage_Data_Len(SDI + i);
      Len = Read_Storage_Data(SDI + j, p, (void *)Pub_Buf0, sizeof(Pub_Buf0));
      if(Len EQ sizeof(S_VolStat))
      {
      Clear_Phase_VolStat_Data(p, i);
      Write_Storage_Data(SDI + j, (void *)p, Len);
      }
    }
    OS_Mutex_Post(PUB_BUF0_SEM_ID); 
    
    return 1;
  }
  else
    return 0;
}

//清除当前电压统计内存数据
void Clear_Cur_VolStat_Ram()
{
  DIS_PD_INT;
  
  mem_set((void *) &Cur_VolStat, 0, sizeof(Cur_VolStat), (void *) &Cur_VolStat, sizeof(Cur_VolStat));
  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);
  SET_STRUCT_SUM(Cur_VolStat);
  
  EN_PD_INT;
  
  Clear_VolStat_Count_Ram();
}
/*
void Get_Last_VolStat_Settle_Time(S_HEX_Time *pSrc, S_HEX_Time *pDst, void *pDst_Start, INT16U DstLen)
{
  mem_cpy(pDst, pSrc, sizeof(S_HEX_Time), pDst_Start, DstLen);
  pDst->Time[T_DATE] = 1;
  Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst - > CS));
  
}

void Get_Next_VolStat_Settle_Time(S_HEX_Time *pSrc, S_HEX_Time *pDst, void *pDst_Start, INT16U DstLen)
{
  mem_cpy(pDst, pSrc, sizeof(S_HEX_Time), pDst_Start, DstLen);
  pDst->Time[T_DATE] = 1;
  Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst - > CS));
}


//将当前电压统计数据冻结，pTime传入冻结时刻，一般就是当前时间
void Settle_VolStat_Data(S_HEX_Time *pTime)
{
  INT8U Re;
  S_HEX_Time TempTime;
  INT8U Err;
  
  Debug_Print("----------Freeze VolStat Data %d-%d-%d %d:%d----------",\
  pTime->Time[T_YEAR],pTime->Time[T_MONTH],pTime->Time[T_DATE],pTime->Time[T_HOUR],pTime->Time[T_MIN]);
  
  //Cur_VolStat本身时间格式不正确的话不进行冻结
  if((Cur_VolStat.Time.Time[T_YEAR]==0 && Cur_VolStat.Time.Time[T_MONTH]==0) ||\
  Check_HEX_Time((S_HEX_Time *)&(Cur_VolStat.Time))==0)
  {
  Debug_Print("----------Freeze VolStat Data End----------");
  return;
  }
  //<=pTime的最近一个冻结时间点
  Get_Last_Freeze_Time(pTime,&TempTime);//pTime以前的最近一个冻结时间点,包括pTime本身
  //现在TempTime就是最近一次的冻结时间点
  Re=Cmp_Time(&(Cur_VolStat.Time),&TempTime);//比较数据冻结时间点与最近一次冻结时间点
  if(TIME_AFT==Re)//需量时间点在最近一次结算时间点之后，是一条当前数据，不需要补存到历史数据中
  {
  Debug_Print("----------Freeze VolStat Data End----------");
  return;
  }
  //是一条历史数据
  //>=p->Time的最近一个冻结时间点
  Get_Next_Freeze_Time(&(Cur_VolStat.Time),&TempTime);//历史数据的冻结时间点 
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);//申请Pub_Buf0信号量
  //该月没有冻结数据则进行冻结
  if(Read_HIS_Data(HIS_VOLSTAT_DATA,&TempTime,(void *)Pub_Buf0,(void *)Pub_Buf0,sizeof(Pub_Buf0),&Err)==0)
  {
  Write_HIS_Data(HIS_VOLSTAT_DATA,(S_HEX_Time *)&(Cur_VolStat.Time),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);//释放Pub_Buf0信号量  
  //因为是历史数据，所以需要重置变为当月数据
  //清当月电压统计数据
  mem_set((void *)&Cur_VolStat,0,sizeof(Cur_VolStat),(void *)&Cur_VolStat,sizeof(Cur_VolStat));//将数据全部清0存入当前存储区，下次读出全0数据，表示尚未生成新数据
  
  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);   
  SET_STRUCT_SUM(Cur_VolStat);
  
  //更新存储区数据  
  Save_Cur_VolStat_PD_Data();
  Save_Cur_VolStat_Data();
  Debug_Print("----------Freeze VolStat Data End----------");
}
*/

//初始化电压统计参数
void Init_VolStat_Ram_Para()
{
  Clear_VolStat_Count_Ram();
}
#undef VOLSTAT_C

