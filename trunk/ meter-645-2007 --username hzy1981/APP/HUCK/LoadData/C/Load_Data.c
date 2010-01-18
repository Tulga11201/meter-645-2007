#define LOAD_DATA_C
#include "Includes.h"

#define LOAD_DATA_SEARCH_NUM (60 / LOAD_DATA_INDEX_HOUR_NUM * LOAD_DATA_TYPE_NUM + 1) 

//#ifdef LOAD_DATA_C
CONST S_LoadData_Info LoadData_Info[] =
{
  //模式字bit0
  {0x02010100,2,0},//A电压
  {0x02010200,2,0},//B电压
  {0x02010300,2,0},//C电压
  {0x02020100,3,0},//A电流
  {0x02020200,3,0},//B电流
  {0x02020300,3,0},//C电流
  {0x02800002,2,0},//频率
  //模式字bit1
  //{DI_ACTIVE_DIRECT,1,1},//有功方向标识字
  //{DI_REACTIVE_DIRECT,1,1},//无功方向标识字
  {0x02030000,3,1},//总有功功率
  {0x02030100,3,1},//A有功功率
  {0x02030200,3,1},//B有功功率
  {0x02030300,3,1},//C有功功率
  {0x02040000,3,1},//总无功功率
  {0x02040100,3,1},//A无功功率
  {0x02040200,3,1},//B无功功率
  {0x02040300,3,1},//C无功功率
  //模式字bit2
  {0x02060000,2,2},//总无功功率
  {0x02060100,2,2},//A无功功率
  {0x02060200,2,2},//B无功功率
  {0x02060300,2,2},//C无功功率
  //模式字bit3
  {0x00010000,4,3},//正向有功总
  {0x00020000,4,3},//反向有功总
  {0x00030000,4,3},//正向无功总，(组合无功1总)
  {0x00040000,4,3},//反向无功总，(组合无功2总)
  //模式字bit4
  {0x00050000,4,4},//一象限无功总
  {0x00060000,4,4},//二象限无功总
  {0x00070000,4,4},//三象限无功总
  {0x00080000,4,4},//四象限无功总
  //模式字bit5 
  {0x02800004,3,5},//有功需量
  {0x02800005,3,5}//无功需量

};

//各类型的负荷曲线长度
CONST INT8U LoadData_Len[] = 
{
  17,//电压电流
  24,//有无功功率
  8, //功率因素
  16,//有无功总电能
  16,//四象限无功总电能
  6, //当前需量
  
};
//#endif

//读取索引为Index的负荷曲线的时间和类型
//Index表示这条负荷曲线数据的存储Index，其值为0 -> LOAD_DATA_NUM-1
//pTime, 读出的时间数据放到该指针指向的缓冲区中
//返回1表示读回了数据，0表示没有读回数据
INT8U Read_LoadData_Type_Time(INT16U Index, INT8U *pType, S_HEX_Time* pTime)
{
  INT8U Temp[7 + ROM_CS_BYTES]; 
  INT16U Len; 

    TRACE();
  //读取负荷曲线数据的起始处LOAD_DATA_HEAD_SIZE个字节
  //主要是起始字符和时间
  //前两个字节是0xA0和0xA0表示是负荷曲线, 后面5个字节是时间
  Len = Read_Storage_Data_Fix_Len(_SDI_LOAD_DATA + Index, \
        0, \
        LOAD_DATA_HEAD_SIZE, \
        Temp, \
        Temp, \
        sizeof(Temp)); 
 
  if(LOAD_DATA_HEAD_SIZE != Len)//读出的长度不对?见鬼(一般是内部校验和不对)
  {
    ASSERT_FAILED();
    return 0;
  }
  //判断数据格式
  if((Temp[0] & 0xF0) EQ 0xA0 && (Temp[0] & 0x0F) < LOAD_DATA_TYPE_NUM)
  {
    *pType = (Temp[0] & 0x0F); //低4位存储负荷曲线类型
      
    mem_cpy(pTime -> Time, Temp + 1, 5, pTime, sizeof(S_HEX_Time)); 
    Set_STRUCT_Sum(pTime, sizeof(S_HEX_Time), pTime -> CS, sizeof(pTime -> CS)); 
    if(Check_HEX_Time(pTime) EQ 1)//时间格式正确
      return 1;
  }

  ASSERT_FAILED(); 
  return 0;
}

/*****************************************
函数原型：NT16U Get_LoadData_Index(S_HEX_Time *pTime)
函数功能：获取某个时间点的数据的索引, 采用二分法查询负荷曲线数据存储区
入口参数：某个时间点
出口参数：索引值, 失败时返回NULL_LOAD_INDEX
******************************************/
INT16U Get_LoadData_Index(INT8U Type, S_HEX_Time* pTime)//获取某个时间点的数据的索引
{
  S_HEX_Time Time; 
  INT8U Temp[6], Count, Re; 
  INT32U Index; 
  INT8U Type1,Len;

  TRACE();
  Re = CHECK_STRUCT_SUM(LoadData_Index); 
  if(1 != Re)//ASSERT(Re EQ 1))//检查数据的校验和
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  Index = Get_LoadData_Time_Index(pTime -> Time); //先找出其时间索引位置
  Len = Read_Storage_Data(_SDI_LOAD_DATA_TIME_INDEX + Index, Temp, Temp, sizeof(Temp)); //读出该小时内第一个数据的存储位置
  if(2 EQ Len)
  {
    Index = 0; 
    mem_cpy(&Index, Temp, 2, &Index, sizeof(Index)); //Index = *(INT16U *)Temp; 
    Count = 0; 
    while(Count < LOAD_DATA_SEARCH_NUM)
    {
      Clear_All_Dog(); //清所有狗，防止复位
      if(Read_LoadData_Type_Time(Index, &Type1, &Time) != 0) //如果获得时间数据有效
      {
        if(Cmp_Time(&Time, pTime) EQ TIME_EQU)//两个时间相等，找到数据
        {
          if(Type EQ ALL_TYPE_DATA || Type EQ Type1) 
            break;
        }
      }
      Index ++;
      Count ++;
      OS_TimeDly_Ms(20);
    }

    if(Count != LOAD_DATA_SEARCH_NUM)
      return Index;
    else
      return NULL_2BYTES;
  }
  else
  {
    return NULL_2BYTES;
  }
}

//获取某一时间的分钟数
INT32U Get_Time_Mins(INT8U Time[])
{
  TRACE();
  
  return (INT32U)Time[0] + (INT32U)Time[1]*60 + (INT32U)(Time[2]-1)*1440;
	
}

//读取制定索引位置的数据块, 该函数主要是为了剔除掉S_HEX_TIme中的CS域, 并将时间转BCD马
//Index, 索引值, 0-LOAD_DATA_NUM-1
//Mode表示模式字，是否读出某类数据
//pDst, 目标缓冲区
//pDst_Start, 
//格式:0xA0, 2字节
//Cur_Time0, sizeof(S_HEX_Time)
//数据
INT16U Read_One_Load_Data_With_Index(INT8U Type, INT16U Index, INT8U* pDst, INT8U* pDst_Start, INT16U Dst_Len, INT16U *pLast_Index)
{
  INT16U Len, DstLen; 
  INT8U Re, Type1;
  INT8U i, Sum;
  S_HEX_Time TempTime;

  TRACE();
  
  if(Type != ALL_TYPE_DATA && Type >= LOAD_DATA_TYPE_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
 
  pDst[0] = 0xA0;
  pDst[1] = 0xA0;
  DstLen = 3; //预留一个字节作为长度
  
  if(Type != ALL_TYPE_DATA)//如果是读取某一特定类型的数据,则前面和后面的类型都要置为0xAA
  {
    DstLen += 5;
    mem_set(pDst + DstLen, 0xAA, Type, pDst_Start, Dst_Len);
    DstLen += Type;
    *pLast_Index = Index;
    Len = Read_Storage_Data(_SDI_LOAD_DATA + Index, (INT8U *)Pub_Buf0, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0)); 
    if(Len > 0 && (Pub_Buf0[0] & 0x0F) EQ Type)
    {
      Hex2Bcd_Buf((INT8U *)Pub_Buf0 + 1, 5, pDst + 3, pDst_Start, Dst_Len);

      mem_cpy(pDst + DstLen, (INT8U *)Pub_Buf0 + LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES, LoadData_Len[Type],\
              pDst_Start, Dst_Len);
      DstLen += LoadData_Len[Type];
      *(pDst + DstLen) = 0xAA;
      DstLen ++;       
    }
    else
    {
      *(pDst + DstLen) = 0xAA;
      DstLen ++;           
    }
    
    mem_set(pDst + DstLen, 0xAA, LOAD_DATA_TYPE_NUM - 1 - Type, pDst_Start, Dst_Len);
    DstLen += LOAD_DATA_TYPE_NUM - 1 - Type;        
  }  
  else
  {
    Len = Read_LoadData_Type_Time(Index, &Type, &TempTime); //读取到第一条数据的时间
    if(Len > 0)//长度合法
    {
      Hex2Bcd_Buf(TempTime.Time, 5, pDst + 3, pDst_Start, Dst_Len);
      DstLen += 5;
      
      Type1 = 0xFF; //表示当此应该读到的数据的类型 Type1 ++ == 0
      //最多读取6条数据
      for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
      {
        Type1 ++;
        if(Type1 >= LOAD_DATA_TYPE_NUM)
          break;
        
        Len = Read_Storage_Data(_SDI_LOAD_DATA + Index, (INT8U *)Pub_Buf0, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0)); 
        if(Len EQ 0)
        {
          *(pDst + DstLen) = 0xAA;
          DstLen ++;
          continue;
        }
        
        i = (Pub_Buf0[0] & 0x0F); //读出数据的类型，应该比前次读出的类型值大
        if(i > Type1 && i < LOAD_DATA_TYPE_NUM)
        {
          mem_set(pDst + DstLen, 0xAA, i - Type1, pDst_Start, Dst_Len); 
          DstLen += i - Type1;
        }
        else if(i != Type1)//读出的数据类型不正确，过大或者比前次读出的类型还小！
          break;
        
        Re = memcmp((INT8U *)Pub_Buf0 + 1, TempTime.Time, 5);
        if(Re EQ 0) //必须是同一个时间点
        {
          Type1 = (Pub_Buf0[0] & 0x0F); //当前读取的数据类型
          mem_cpy(pDst + DstLen, (INT8U *)Pub_Buf0 + LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES, LoadData_Len[Type1],\
                  pDst_Start, Dst_Len);
          DstLen += LoadData_Len[Type1];
          
          *(pDst + DstLen) = 0xAA; //增加块分割符
          DstLen ++;
          
          *pLast_Index = Index;
        }
        else //数据的时间不是起始数据的那个时间点了！
          break;
        
        Index ++;
        if(Index >= LOAD_DATA_NUM)
          Index = 0;
      }
      
      if(Type1 < LOAD_DATA_TYPE_NUM - 1)
      {
        mem_set(pDst + DstLen, 0xAA, LOAD_DATA_TYPE_NUM - 1 - Type1, pDst_Start, Dst_Len);
        DstLen += LOAD_DATA_TYPE_NUM - 1 - Type1;
      } 
      else if(Type >= LOAD_DATA_TYPE_NUM)
        ASSERT_FAILED();
    }
  }
  pDst[2] = DstLen - 3; //数据块长度
  
  Sum = 0;
  for(i = 0; i < DstLen; i ++)
    Sum += pDst[i];
  
  pDst[DstLen ++] = Sum;  //校验和
  pDst[DstLen ++] = 0xE5; //块结束符

  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  return DstLen;
}

//读取某一类型的索引为Index负荷曲线的下一类数据
INT16U Read_LoadData_Next_Index(INT16U Index)
{
  INT16U Next_Index;
  INT16U Len;
  
  Len = Read_Storage_Data(_SDI_LOAD_DATA_NEXT_INDEX + Index, &Next_Index, &Next_Index, sizeof(Next_Index));   
  if(Len > 0)
    return Next_Index;
  else
    return NULL_2BYTES;
}

//写索引为Index的数据的下一条数据索引
INT8U Write_LoadData_Next_Index(INT16U Index, INT16U Next_Index)
{
   return Write_Storage_Data(_SDI_LOAD_DATA_NEXT_INDEX + Index, &Next_Index, sizeof(Next_Index));
  
}

//检查某类型的数据ude类型和索引是否正确
INT8U Check_Load_Data_Type_Index(INT8U Type, INT16U Index)
{
  INT16U Start, Last;
  
  if(Index EQ NULL_2BYTES)
    return 0;

  if(Check_Meter_Factory_Status())//在工厂状态不检查Index的合法性!防止因为Index乱而导致读不到数据的情况
    return 1;
  
  if(Type EQ ALL_TYPE_DATA)
  {
    Start = LoadData_Index.All_Type_Start;
    Last = LoadData_Index.All_Type_Last;
  }
  else if(Type < LOAD_DATA_TYPE_NUM)
  {
    Start = LoadData_Index.Type_Start[Type];
    Last = LoadData_Index.Type_Last[Type];
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }
  
   if(Last > Start && Index >= Start && Index < Last)
     return 1;
   else if(Last < Start && (Index < Last || Index >= Start))
     return 1;

  return 0;
}

//读特定索引的负荷曲线
//Mode表示记录模式，第N位为0表示不读取该类数据，函数内部会判断该Index的时间点是否应该记录某类数据，如果不应该记录
//则不会返回该类数据如果Mode标记NO_CHK_TIME标志置上了，则不检查时间。完全按照Mode参数读取数据，否则会检查每类数据时间
//Num表示连续读取多少条?
//pDst,pDst_Start,DstLen表示读取到目标缓冲区信息
INT16U Read_Load_Data_With_Index(INT8U Type, INT16U Index, INT8U Num, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i,Re;
  INT16U Len,TempLen;
  INT16U Last_Index;
  static S_Int16U Last_Read_Index = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Last_Read_Num = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int16U Last_Read_i = {CHK_BYTE, 0, CHK_BYTE};
  
  Len = 0;
  TempLen = 0;
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Last_Read_Index);
  Re &= CHECK_STRUCT_VAR(Last_Read_Num);
  Re &= CHECK_STRUCT_VAR(Last_Read_i);
  
  ASSERT(Re EQ 1);
  
  if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//读后续数据?
  {
    i = Last_Read_i.Var;
    Num = Last_Read_Num.Var;
    Index = Last_Read_Index.Var;
  }
  else
  {
    i = 0; 
  }
  
  for(; i < Num; i ++)
  {
    if(Check_Load_Data_Type_Index(Type, Index) EQ 0)//Index EQ LoadData_Index.Last)
      break;  
    
    OS_Mutex_Pend(TRANS_BUF_SEM_ID);
    TempLen = Read_One_Load_Data_With_Index(Type, Index, (INT8U *)Trans_Temp_Buf, (INT8U *)Trans_Temp_Buf, sizeof(Trans_Temp_Buf), &Last_Index);
    OS_Mutex_Post(TRANS_BUF_SEM_ID);  
    
    if(pDst + Len + TempLen >= pDst_Start + DstLen || Len + TempLen >= 200)
    {
      Frame_Ack_Info.Follow_Flag = 1;//有后续帧
      Last_Read_Index.Var = Index;
      Last_Read_Num.Var = Num;
      Last_Read_i.Var = i;
      
      return Len;
    }
   
    mem_cpy(pDst + Len, (INT8U *)Trans_Temp_Buf, TempLen, pDst_Start, DstLen);
    Len += TempLen;

    if(Type != ALL_TYPE_DATA)
    {
      Index = Read_LoadData_Next_Index(Index);
      if(Index != NULL_2BYTES && Index >= LOAD_DATA_NUM)
        Index = 0;
    }
    else
      Index = (Last_Index + 1) % LOAD_DATA_NUM;
    
    //if(Check_Load_Data_Type_Index(Type, Index) EQ 0)//Index EQ LoadData_Index.Last)
      //break;    
  }
  
  Frame_Ack_Info.Follow_Flag = 0;//没后续帧
  Last_Read_Index.Var = 0;
  Last_Read_Num.Var = 0;
  Last_Read_i.Var = 0;  
  
  return Len;
}

//计算某时间点相对于该月初走出的时间
INT32U Calc_Mins(S_HEX_Time *pTime)
{
  //return (INT32U) (pTime -> Time[T_DATE] - 1) * 24 * 60 + (INT32U) (pTime -> Time[T_HOUR]) * 60 + pTime -> Time[T_MIN];  
  return Get_Time_Mins(pTime -> Time);
}

//检查Type类负荷曲线数据在pTime时间点是否应该有数据
INT8U Check_Load_Data_Time(S_HEX_Time *pTime, INT8U Type)
{
  INT32U Mins;
  //计算当前走过的分
  Mins = Calc_Mins(pTime);//(INT32U) (pTime -> Time[T_DATE] - 1) * 24 * 60 + (INT32U) (pTime -> Time[T_HOUR] - 1) * 60 + pTime -> Time[T_MIN]; 
  //比较每类数据，看该类数据的时间是否到
  //for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
  //{
    //某类数据的存储时间点到了，则存储整个数据
  if(GET_BIT(LoadData_Para.Mode, Type)!=0 &&\
     LoadData_Para.Period[Type] != 0 && \
     Mins % (LoadData_Para.Period[Type]) EQ 0) 
    return 1;
  else
    return 0;
}

//读负荷曲线
//pTime电量，需量数据的存储时间
//pSrc写数据缓冲区
//SrcLen数据长度
INT16U Read_Load_Data_With_Time(INT8U Type, S_HEX_Time* pTime, INT8U Num, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Index; 
  //INT8U i;

  TRACE();
  
  if(Frame_Ack_Info.Read_Follow_Flag EQ 0) //不是读后续数据则需要获取时间索引
    Index = Get_LoadData_Index(Type, pTime); //获取该数据的存储索引
  else
    Index = 0;
  
  if(NULL_LOAD_INDEX != Index)
  {
    return Read_Load_Data_With_Index(Type, Index, Num, (INT8U *) pDst, (INT8U *) pDst_Start, DstLen);
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
}

//根据DI得到是哪类负荷数据
INT8U Get_Load_Data_Type(PROTO_DI PDI)
{
  return (INT8U) ((PDI & 0x00FF0000) >> 16);
}
//读负荷曲线数据
//DI, 数据标示, 主要是0x06XXXXXX
//Para，D110时表示需要读取的负荷曲线的时间
//pDst目标缓冲区
//pDst_Start目标的起始地址，和DstLen一起限定pDst和返回数据长度
INT16U Get_Load_Proto_Data(PROTO_DI PDI, INT8U Para[], INT8U ParaLen, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT8U Type; 
  INT16U Len, Index, Start, Last; 
  S_HEX_Time TempTime; 
  INT8U Num;

  TRACE();
  
  if(LoadData_Index.Start EQ 0 && LoadData_Index.Last EQ 0)
  {
    Debug_Print("No Load_Data Now!"); 
    return 0;
  }

  //Mode = 0;
  Num = 0;
  //读取哪类数据?
  Type = Get_Load_Data_Type(PDI);
  if(Type EQ 0) //总的数据
  {
    Type = ALL_TYPE_DATA;
    Start = LoadData_Index.All_Type_Start; //总数据的起始和结束索引
    Last =  LoadData_Index.All_Type_Last;// + LOAD_DATA_NUM - 1)%LOAD_DATA_NUM;
  }
  else if(Type >= 1 && Type <= 6) //第一类到第六类数据
  {
    Type = Type - 1;
    Start = LoadData_Index.Type_Start[Type];//LoadData_Index.Type_Start[Type - 1]; //该类数据的起始和结束索引
    Last =  LoadData_Index.Type_Last[Type];// + LOAD_DATA_NUM - 1)%LOAD_DATA_NUM;   
  }
  else
    return 0;
///////////////////////////////////////////////////////////////////////////////////
  if(Start EQ Last)//该类数据还没有开始记录
    return 0;
    
  //读取最后？给定时间？最近?
  if((0x000000FF & PDI) EQ 0x00)//读取最早记录块
  {
    //if(Start EQ 0 && Last EQ 0) //还没有开始记录数据
     // return 0;
    if(Frame_Ack_Info.Read_Follow_Flag EQ 0)
    {
      if(ParaLen > 0)
        Num = Bcd2Hex_Byte(Para[0]); //读多少个点?
      else //可能是读后续数据
        Num = 1;
    }
    else
      Num = 0;
    
    Len = Read_Load_Data_With_Index(Type, Start, Num, pDst, pDst, DstLen); 
    return Len;
  }
  else if((0x000000FF & PDI) EQ 0x01)//读取给定时间数据块
  {
    //if(Start EQ Last) //还没有开始记录数据
      //return 0;
    if(Frame_Ack_Info.Read_Follow_Flag EQ 0)
    {
      if(ParaLen >= 6)
      {
        Num = Bcd2Hex_Byte(Para[0]); //读多少个点?
        if(Num EQ 0)
          Num = 1;
        
        mem_cpy(TempTime.Time, &Para[1], 5, TempTime.Time, sizeof(TempTime.Time));
        Bcd2Hex_Buf(TempTime.Time, 5, TempTime.Time, TempTime.Time, sizeof(TempTime.Time));
        SET_STRUCT_SUM(TempTime);
        
        if(Check_HEX_Time(&TempTime) EQ 0) //时间数据必须正确
          return 0;
      }
      else
        return 0;
    }
    else //可能是读后续数据
     Num = 1;
    
    Len = Read_Load_Data_With_Time(Type, &TempTime, Num, (INT8U *)pDst, (INT8U *)pDst_Start, DstLen);
    return Len;
  }
  else if((0x000000FF & PDI) EQ 0x02)//读取最近记录块
  {
    if(Last EQ 0)
      Index = LOAD_DATA_NUM - 1;
    else
      Index = Last - 1; 

    Num = 1;
    Len = Read_Load_Data_With_Index(Type, Index, Num, pDst, pDst, DstLen); 
    return Len;
  }
  else
    return 0;
}

//判断一个PDI是否是负荷记录的PDI
INT8U Check_Load_Data_PDI(PROTO_DI PDI)
{
  if((PDI & 0xFF00FF00) EQ 0x06000000 && \
     (PDI & 0x00FF0000) <= 0x00060000 && \
     (PDI & 0x000000FF) <= 0x00000002)
     return 1;
  else
    return 0;
}

/*
//可读取多条的负荷记录处理
INT16U _Get_Load_Proto_Data(PROTO_DI PDI, INT8U Para[], INT8U ParaLen, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT8U Type,Mode; 
  INT16U Len, Index, Start, Last; 
  S_HEX_Time TempTime; 

  TRACE();
  if(LoadData_Index.Start EQ 0 && LoadData_Index.Last EQ 0)
  {
    Debug_Print("No Load_Data Now!"); 
    return 0;
  }

  //读取哪类数据?
  Type = Get_Load_Data_Type(PDI);
  if(Type EQ 0) //总的数据
  {
    Mode = LoadData_Para.Mode; //模式字
    Start = LoadData_Index.Start; //总数据的起始和结束索引
    Last = LoadData_Index.Last;
  }
  else if(Type >= 1 && Type <= 6) //第一类到第六类数据
  {
    if(GET_BIT(LoadData_Para.Mode, (Type -1))) //模式字中是否有该类数据
    {
      Mode = (0x01 << (Type-1));
      Start = LoadData_Index.Start;//LoadData_Index.Type_Start[Type - 1]; //该类数据的起始和结束索引
      Last = LoadData_Index.Type_Last[Type - 1];   
    }
    else
      return 0;
  }
  else
    return 0;

  if((0x000000FF & PDI) EQ 0x00)//读取最早记录块
  {
    if(Start EQ Last) //还没有开始记录数据
      return 0;
    else
    {
      Len = Read_Load_Data_With_Index(Start, Mode, Num, pDst, pDst, DstLen); 
      return Len;
    }
  }
  else if((0x000000FF & PDI) EQ 0x01)//读取给定时间数据块
  {
    Index = 0; 
    TempTime.Time[T_MIN] = Bcd2Hex_Byte(Para[Index]); 
    TempTime.Time[T_HOUR] = Bcd2Hex_Byte(Para[Index + 1]); 
    TempTime.Time[T_DATE] = Bcd2Hex_Byte(Para[Index + 2]); 
    TempTime.Time[T_MONTH] = Bcd2Hex_Byte(Para[Index + 3]); 
    TempTime.Time[T_YEAR] = Bcd2Hex_Byte(Para[Index + 4]); 
    SET_STRUCT_SUM(TempTime); 
    Len = Read_Load_Data_With_Time(&TempTime, Mode, Num, pDst, pDst_Start, DstLen);
    
    return Len;
  }
  else if((0x000000FF & PDI) EQ 0x02)//读取最近记录块
  {
    if(Start EQ Last)//该类数据还没有开始记录
      return 0;
    
    if(Last EQ 0)
      Index = LOAD_DATA_NUM - 1;
    else
      Index = Last - 1; 

    Len = Read_Load_Data_With_Index(Index, Mode, Num, pDst, pDst, DstLen); 
    return Len;
  }
  else
  {
    return 0;
  }
}
*/

//设置默认的负荷曲线索引
void Set_Def_Load_Data_Index()
{
    TRACE();

  mem_cpy((void *) &LoadData_Index, (void *) Def_LoadData_Index, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
  //mem_cpy((void *) &LoadData_Index_Bak, (void *) Def_LoadData_Index, sizeof(LoadData_Index), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak));

  SET_STRUCT_SUM(LoadData_Index);
  //SET_STRUCT_SUM(LoadData_Index_Bak);

  Save_LoadData_PD_Data();
  Save_LoadData_Index(); 
  Save_LoadData_Index_Bak();
}

void Clear_Load_Data()
{
  Set_Def_Load_Data_Index();
}

void Save_LoadData_PD_Data()
{
  TRACE();
  
  if(CHECK_STRUCT_SUM(LoadData_Index))
    Write_Storage_Data(_SDI_LOAD_DATA_INDEX_PD,(void *)&LoadData_Index,sizeof(LoadData_Index));
  //else if(CHECK_STRUCT_SUM(LoadData_Index_Bak))
    //Write_Storage_Data(_SDI_LOAD_DATA_INDEX_PD,(void *)&LoadData_Index_Bak,sizeof(LoadData_Index));
  else
    ASSERT_FAILED();
}

//存储负荷曲线信息的备份, 该函数每小时调用一次
void Save_LoadData_Index()
{
  INT8U Re; 

  TRACE();
  Re = CHECK_STRUCT_SUM(LoadData_Index); 
  if(1 != Re)//ASSERT(Re != 0))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  Re = Write_Storage_Data(_SDI_LOAD_DATA_INDEX, (void *) &LoadData_Index, sizeof(LoadData_Index)); 
  ASSERT(1 EQ Re);
}

//存储负荷曲线信息的备份, 该函数每小时调用一次
void Save_LoadData_Index_Bak()
{
  INT8U Re; 

  TRACE();
  Re = CHECK_STRUCT_SUM(LoadData_Index); 
  if(1 != Re)//ASSERT(Re != 0))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  Re = Write_Storage_Data(_SDI_LOAD_DATA_INDEX_BAK, (void *) &LoadData_Index, sizeof(LoadData_Index)); 
  ASSERT(1 EQ Re);
}


//读取负荷曲线参数，从ROM中
void Read_LoadData_Para_From_Rom()
{
  INT8U i; 

  TRACE();
  
  //读取负荷记录模式字
  if(Read_Storage_Data(SDI_LOAD_REC_WORD, (void *) &(LoadData_Para.Mode), (void *) &(LoadData_Para.Mode), sizeof(LoadData_Para.Mode)) != sizeof(LoadData_Para.Mode))
  {
    Debug_Print("Read SDI_LOAD_REC_WORD Para Err");
  } 
  
  //读取起始时间
  if(Read_Storage_Data(SDI_LOAD_REC_START_TIME, (void *) (LoadData_Para.Time), (void *) (LoadData_Para.Time), sizeof(LoadData_Para.Time)) != sizeof(LoadData_Para.Time))
  {
    Debug_Print("Read SDI_LOAD_REC_START_TIME Para Err");
  }  
  Bcd2Hex_Buf((void *) LoadData_Para.Time, sizeof(LoadData_Para.Time), (void *) LoadData_Para.Time, (void *) LoadData_Para.Time, sizeof(LoadData_Para.Time)); 
  //读取时间间隔
  for(i = 0; i < 6; i ++)
  {
    if(Read_Storage_Data(SDI_LOAD_REC1_INTER_TIME + i, (void *) (&LoadData_Para.Period[i]), (void *) (&LoadData_Para.Period[i]), 2) != 2)
      Debug_Print("Read 0x%lx Para Err", SDI_LOAD_REC1_INTER_TIME + i);  

    LoadData_Para.Period[i] = (INT16U) Bcd2Hex((INT8U *) (&LoadData_Para.Period[i]), 2);
  }
  SET_STRUCT_SUM(LoadData_Para);
}

//从Rom中读取LoadData_Index
void Read_LoadData_Index_Data_From_Rom()
{
  TRACE();

  if(Read_Storage_Data(_SDI_LOAD_DATA_INDEX_PD, (void *) &LoadData_Index, (void *) &LoadData_Index, sizeof(LoadData_Index)) != sizeof(LoadData_Index))
  {
    Debug_Print("Read LOAD_DATA_INDEX_PD data error"); 
    OS_TimeDly_Ms(100); 
    if(Read_Storage_Data(_SDI_LOAD_DATA_INDEX, (void *) &LoadData_Index, (void *) &LoadData_Index, sizeof(LoadData_Index)) != sizeof(LoadData_Index))
    {
      Debug_Print("Read LOAD_DATA_INDEX data error"); 
      OS_TimeDly_Ms(100); 
      if(Read_Storage_Data(_SDI_LOAD_DATA_INDEX_BAK, (void *) &LoadData_Index, (void *) &LoadData_Index, sizeof(LoadData_Index)) != sizeof(LoadData_Index))
      {
        Debug_Print("Read LOAD_DATA_INDEX_BAK data error"); 
        OS_TimeDly_Ms(100); 
        mem_cpy((void *) &LoadData_Index, (void *) &Def_LoadData_Index, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
      }      
    }
  }
  SET_STRUCT_SUM(LoadData_Index); 
  //mem_cpy((void *) &LoadData_Index_Bak, (void *) &LoadData_Index, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak));
}

//检查S_LoadData_Index变量是否合法
INT8U Check_LoadData_Index(S_LoadData_Index* pInfo)
{
  INT8U Re; 

  TRACE();

  Re = Check_STRUCT_Sum(pInfo, sizeof(S_LoadData_Index), pInfo -> CS, sizeof(pInfo -> CS)); 
  if(Re != 0)
  {
    if(pInfo -> Last < LOAD_DATA_NUM && \
       pInfo -> Start < LOAD_DATA_NUM)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

//检查许亮索引数据的合法性
void Check_LoadData_Index_Avail()
{
  INT8U Re = 1; 

    TRACE();
  //先读主区数据，校验和不对则读取备份区数据
  Re = Check_LoadData_Index((S_LoadData_Index *) &LoadData_Index); 
  if(Re EQ 0)
  {
    //Re = Check_LoadData_Index((S_LoadData_Index *) &LoadData_Index_Bak); 
    //if(Re EQ 0)
      Read_LoadData_Index_Data_From_Rom(); //从ROM中读取该参数
    //else
      //mem_cpy((void *) &LoadData_Index, (void *) &LoadData_Index_Bak, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
  }
}

//检查负荷曲线相关参数的合法性
void Check_LoadData_Para_Avail()
{
  INT8U Re; 

   TRACE();

  Re = CHECK_STRUCT_SUM(LoadData_Para); 
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Read_LoadData_Para_From_Rom();
  }
}

//获取负荷曲线数据在某个时间点的小时索引，通过小时索引可以读出该小时的第一个数据的存储索引
INT32U Get_LoadData_Time_Index(INT8U Time[])
{
  TRACE();
	ASSERT(Time[T_MIN]<60 && Time[T_HOUR]<24 &&\
		Time[T_DATE]>0 && Time[T_DATE]<32 &&\
		Time[T_MONTH]>0 && Time[T_MONTH]<13);
	
	//修改为15分钟的索引，因此下表达式*4
	//表示走过了多少个15分钟
	return (INT32U)Time[T_MIN]/(60/LOAD_DATA_INDEX_HOUR_NUM)+((INT32U)Time[T_HOUR]+((INT32U)Time[T_DATE]-1)*24+((INT32U)Time[T_MONTH]-1)*31*24)*LOAD_DATA_INDEX_HOUR_NUM;//%LOAD_DATA_MIN_INDEX_NUM;
}

//写负荷曲线
//pSrc写数据缓冲区
//pSrc格式必须满足:第一二个字节分别是0xA0和0xA0, 表示是负荷曲线，后面紧跟一条S_HEX_Time类型的时间数据
//Flag表示是否是一个新的时间点数据,0表示不是，1表示是
//表示这条负荷曲线数据的时间
//SrcLen表示数据长度
//返回NO_ERR表示写成功，其他表示写失败
INT8U Write_Load_Data(INT8U Type, INT8U Flag, INT8U* pSrc, INT16U SrcLen)
{
  INT8U Re; 
  INT16U Index, Next_Index, Last;
  INT32U Time_Index;
  INT8U Type1;
  S_HEX_Time TempTime;

  TRACE();
  if(0xA0 EQ (*pSrc & 0xF0) && (*pSrc & 0x0F) < LOAD_DATA_TYPE_NUM)//存储的前两个字节一定要是两个0xA0
  {
    Re = CHECK_STRUCT_SUM(LoadData_Index); //检查索引LoadData_Index的校验和正确
    if(1 != Re)
    {
      ASSERT_FAILED();
      Check_Data_Avail(); 
    }
    
    if(LoadData_Index.Last >= LOAD_DATA_NUM)//Index不对？不可能吧？
    {
      ASSERT_FAILED();
      LoadData_Index.Last = 0; 
    }
    
    Index = LoadData_Index.Last; //当前写的索引
    
    if((Index + 1) % LOAD_DATA_NUM EQ LoadData_Index.Start)
    {
      if(Read_LoadData_Type_Time(Index, &Type1, &TempTime) > 0 && Type1 EQ Type)
        Next_Index = Read_LoadData_Next_Index(Index); //当前要覆盖的这条数据，其后一条就是改类型的新的起始!
      else
        Next_Index = NULL_2BYTES;
    }
    
    Write_Storage_Data(_SDI_LOAD_DATA + Index, pSrc, SrcLen); //直接往里面写数据了！
    Write_LoadData_Next_Index(Index, NULL_2BYTES); //当前数据的下条为空 
    //前一条数据的下条为当前这条
    Last = (LoadData_Index.Type_Last[Type] + LOAD_DATA_NUM - 1)%LOAD_DATA_NUM; 
    Write_LoadData_Next_Index(Last, Index); 

    //更新负荷曲索引记录
    DIS_PD_INT;

    //整个写位置的起始和结束，更新
    LoadData_Index.Last = (LoadData_Index.Last + 1) % LOAD_DATA_NUM;
    //写索引和分次类型的起始和结束
    Re = 0;
    if(LoadData_Index.Last EQ LoadData_Index.Start)//Last EQ Start表示最后一条数据已经追上了第一条数据
    {
      LoadData_Index.Start = (LoadData_Index.Start + 1) % LOAD_DATA_NUM; //增加第一条数据的索引
      Re = 1;
    }
    
    //分类数据的起始和结束更新
    if(Re EQ 1) //如果写尾追上了起始位置
      LoadData_Index.Type_Start[Type] = Next_Index;
    else if(LoadData_Index.Type_Start[Type] EQ 0 &&\
            LoadData_Index.Type_Last[Type] EQ 0)//表示该类数据还没有开始写过
    {
      LoadData_Index.Type_Start[Type] = Index;
    }
    LoadData_Index.Type_Last[Type] = LoadData_Index.Last;
    
    //总类型的起始和结束更新
    LoadData_Index.All_Type_Start = LoadData_Index.Start;
    if(Flag EQ 1)//一个新的时间点
      LoadData_Index.All_Type_Last = LoadData_Index.Last;    
/*
    if(LoadData_Index.Type_Start[Type] >= LOAD_DATA_NUM)
    {
      LoadData_Index.Type_Start[Type] = LoadData_Index.Start;
      ASSERT_FAILED();
    }
    if(LoadData_Index.Type_Last[Type] >= LOAD_DATA_NUM)
    {
      LoadData_Index.Type_Last[Type] = LoadData_Index.Last;
      ASSERT_FAILED();
    }
*/    
    SET_STRUCT_SUM(LoadData_Index); //重设校验和
    
    EN_PD_INT;
    //将Index数据备份到Bak中去

    Time_Index = Get_LoadData_Time_Index(pSrc + 1); //时间索引
    //当前小时索引发生了变化则保存老的，并更新LoadData_Index.Min_Index
    if(Time_Index != LoadData_Index.Time_Index)//一个新的时间索引，或者当此的小时或者日与上次不同
    {
      DIS_PD_INT;
      LoadData_Index.Time_Index = Time_Index; 
      SET_STRUCT_SUM(LoadData_Index);
      EN_PD_INT;
      
      Debug_Print("Write_Load_Data Time_Index = 0x%lx, Index = %x", Time_Index, Index);
      Write_Storage_Data(_SDI_LOAD_DATA_TIME_INDEX + Time_Index, &Index, 2); //将当前存储位置存储小时索引中
    }
    //mem_cpy((void *) &LoadData_Index_Bak, (void *) &LoadData_Index, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak)); 

    return 1;
  }
  
  return 0;
}

//生成负荷曲线数据
//具体格式:
/*
0:0xA0
1:0xA0
2:Time[0]分(Hex)
3:Time[1]时
4:Time[2]日
5:Time[3]月
6:Time[4]年
ROM_CS_BYTES:校验和

11:电压电流频率等
   0xAA
   有无功功率等
   0xAA
   ......
*/
INT16U Make_LoadData(INT8U Type, S_HEX_Time* pTime, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i; 
  INT16U Len, TempLen; 

  TRACE();

  pDst[0] = (0xA0 | Type); //数据头是0xA0|数据类
  Len = 1; 
  //当前时间复制, 分、时、日、月、年五个字节
  mem_cpy(pDst + Len, &(pTime -> Time[T_MIN]), 5, pDst_Start, DstLen); 
  //生成前6个字节的校验和
  Set_Sum(pDst, LOAD_DATA_HEAD_SIZE, pDst + LOAD_DATA_HEAD_SIZE, ROM_CS_BYTES, pDst_Start, DstLen); 
  Len = LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES; 

  //以下是真实负荷曲线数据
  //Len ++; //预留一个字节作为数据长度的高位
  //pDst[Len ++] = 0xA0; //数据头是两个0xA0
  //pDst[Len ++] = 0xA0; 
  //Len ++; 
  //负荷曲线时间

  //分别获取LoadData_Info中定义的每个数据项目
  for(i = 0; i < S_NUM(LoadData_Info); i ++)
  {
    if(LoadData_Info[i].Type EQ Type)
    {
      TempLen = Get_DLT645_Data(LoadData_Info[i].PDI, pDst + Len, pDst_Start, DstLen); 
      ASSERT(LoadData_Info[i].Len EQ TempLen); 
      Len += TempLen;
    }
  }

  return Len;
}

//负荷曲线的存储处理流程
void LoadData_Proc()
{
  INT8U Re, i, Flag;  
  INT32U Mins; 
  INT16U Len;
  S_HEX_Time TempTime; 
  INT8U Time[5]; 
    
  static S_Int8U Min_Bak =  {CHK_BYTE, 0xFF, CHK_BYTE}; 

  if(Min_Bak.Var EQ Cur_Time0.Time[T_MIN])//每分钟才进入一次该函数
  {
    return;
  } 

  TRACE();

  Min_Bak.Var = Cur_Time0.Time[T_MIN]; 

  Re = CHECK_STRUCT_SUM(LoadData_Para); //负荷曲线参数对否
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  mem_cpy(Time, (INT8U *)LoadData_Para.Time, sizeof(LoadData_Para.Time), Time, sizeof(Time));
  Time[T_YEAR] = Cur_Time0.Time[T_YEAR];
  //当前时间在负荷记录起始时间之后
  if(_Check_HEX_Time(Time) && Cmp_Array_Time((INT8U *)Cur_Time0.Time, Time,  sizeof(Time)) != TIME_BEF)
  {
    mem_cpy(&TempTime, (S_HEX_Time *) &Cur_Time0, sizeof(Cur_Time0), &TempTime, sizeof(TempTime)); 
    //计算当前走过的分
    Mins = Calc_Mins(&TempTime);//(INT32U) (TempTime.Time[T_DATE] - 1) * 24 * 60 + (INT32U) (TempTime.Time[T_HOUR] - 1) * 60 + TempTime.Time[T_MIN]; 
    
    Flag = 1;
    //比较每类数据，看该类数据的时间是否到
    for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
    {
      //某类数据的存储时间点到了，则存储整个数据
      
      if(GET_BIT(LoadData_Para.Mode, i) > 0 &&\
         LoadData_Para.Period[i] != 0 && \
         Mins % (LoadData_Para.Period[i]) EQ 0)
      {
        Debug_Print("Load Data %dth type data save now!", i);   
  
        OS_Mutex_Pend(PUB_BUF0_SEM_ID); //使用Pub_Buf0用于生成负荷曲线数据
        Len = Make_LoadData(i, &TempTime, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0)); //生成负荷曲线，并返回其长度
        if(Len > LOAD_DATA_SIZE)
        {
          ASSERT_FAILED();
          Debug_Print("Load_Data_Size =%d, exceed", Len);
        }
        
        Write_Load_Data(i, Flag, (INT8U *) Pub_Buf0, LOAD_DATA_SIZE); 
        Flag = 0;
        
        OS_Mutex_Post(PUB_BUF0_SEM_ID);
      }
    }
  }
}
#undef LOAD_DATA_C
