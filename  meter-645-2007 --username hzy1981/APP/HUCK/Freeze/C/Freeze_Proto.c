#define FREEZE_PROTO_C
#include "Includes.h"

/*
_PDI_CUR_TIME0
0x0001FF00,//正向有功电能
0x0002FF00,//反向有功电能
0x0003FF00, //当前组合无功1电能
0x0004FF00, //当前组合无功2电能
0x0005FF00, //当前一象限无功电能
0x0006FF00, //当前二象限无功电能
0x0007FF00, //当前三象限无功电能
0x0008FF00, //当前四象限无功电能
0x0101FF00, //正向有功需量及其发生时间
0x0102FF00, //反向有功需量及其发生时间
0x0203FF00, //有功功率
0x0204FF00  //无功功率
*/
INT16U Get_Freeze_Data_Off(INT8U Type, INT8U Index)
{
  TRACE();

  //小时冻结需要特殊处理，因为其只存储了正向和反向总!
  if(Type EQ HOUR_FREEZE_TYPE) //小时冻结
  {
    if(Index EQ 0) //时间
      return 0;
    else if(Index EQ 1) //正向有功总
      return 5;
    else if(Index EQ 2) //反向有功总
      return 9;
    else
      return 0;
  }
  
  if(Index EQ 0)
  {
    return 0;
  }
  else if(Index >= 1 && Index <= 8)
  {
    return 5 + ((INT16U) (Index - 1) * (MAX_RATES + 1) * 4);
  }
  else if(Index >= 9 && Index <= 10)
  {
    return 5 + (8 * (MAX_RATES + 1) * 4) + ((INT16U) (Index - 9) * (MAX_RATES + 1) * 8);
  }
  else if(Index == 0x10)
  {
    return 5 + (8 * (MAX_RATES + 1) * 4) + (2 * (MAX_RATES + 1) * 8);// + 24;
  }
  else
  {
    ASSERT_FAILED();
    return NULL_2BYTES;
  }
}

/*
冻结数据模式字
	
Bit0 正向有功电能
Bit1 反向有功电能
Bit2 组合无功1电能
Bit3 组合无功2电能
Bit4 四象限无功电能
Bit5 正向有功最大需量及发生时间
Bit6 反向有功最大需量及发生时间
Bit7 变量
*/
INT8U Get_Freeze_Data_Mode_En(INT8U Type, INT8U Index)
{
  //INT8U Type;
  INT8U i;
  
  //Type = (INT8U)((PDI & 0x00FF0000)>>16);
  if(Type EQ PERIOD_FREEZE_TYPE) //定时冻结
    i = 0;
  else if(Type EQ INSTANT_FREEZE_TYPE) //瞬时冻结
    i = 1;
  else if(Type EQ YEAR_SWITCH_FREEZE_TYPE ||\
          Type EQ DATE_SWITCH_FREEZE_TYPE ||\
          Type EQ STEP_SWITCH_FREEZE_TYPE ||\
          Type EQ RATE_SWITCH_FREEZE_TYPE ||\
          Type EQ ENG_OVERTURN_FREEZE_TYPE)//约定冻结
    i = 2;
  else if(Type EQ HOUR_FREEZE_TYPE)//小时冻结
    i = 3;
  else if(Type EQ DATE_FREEZE_TYPE) //日冻结
    i = 4;
  else
  {
    ASSERT_FAILED();
    return 0;
  }
  
  if(Index EQ 0) //时间
    return 1;
  
  else if(Index <= 4) //正向有功、反向有功、组合无功1、2
    return GET_BIT(Freeze_Para.Mode[i], Index - 1) ;
  else if(Index >= 5 && Index <= 8) //四象限无功
    return GET_BIT(Freeze_Para.Mode[i], 4);
  else if(Index EQ 9) //正向有功需量
    return GET_BIT(Freeze_Para.Mode[i], 5);
  else if(Index EQ 10) //反向有功需量
    return GET_BIT(Freeze_Para.Mode[i], 6);
  else if(Index EQ 0x10) //变量
    return GET_BIT(Freeze_Para.Mode[i], 7);
  
  return 0;
}

//获取冻结数据长度
INT16U Get_Freeze_Data_Len(INT8U Type, INT8U Index)
{
  TRACE();

  //小时冻结需要特殊处理，因为其只存储了正向和反向总!
  if(Type EQ HOUR_FREEZE_TYPE) //小时冻结
  {
    if(Index EQ 0) //时间
      return 5;
    else if(Index EQ 1) //正向有功总
      return 4;
    else if(Index EQ 2) //反向有功总
      return 4;
    else
      return 0;
  }
  //-----------------------------------------------
  
  if(Index EQ 0) //时间
  {
    return 5;
  }
  else if(Index >= 1 && Index <= 8)
  {
    return (MAX_RATES + 1) * 4;
  }//return 5 + ((INT16U)(Index -1)  * (MAX_RATES +1) * 4);
  else if(Index >= 9 && Index <= 10)
  {
    return (MAX_RATES + 1) * 8;
  }//return 5 + (8 * (MAX_RATES + 1) * 4) + ((INT16U)(Index - 9) * (MAX_RATES + 1) * 8);
  else if(Index EQ 0x10)
  {
    return 24;
  }//return 5 + (8 * (MAX_RATES + 1) * 4) + (2 * (MAX_RATES + 1) * 8) + ((INT16U)(Index - 11) * 12);
  else
  {
    ASSERT_FAILED();
    return 0;//return NULL_2BYTES;
  }
}

//获取冻结数据对应的事件ID
INT8U Get_Freeze_Data_Event_ID(PROTO_DI PDI, INT8U *pEvent_ID)
{
  INT8U Index;
  
  ASSERT((PDI & 0xFF000000) EQ 0x05000000);
  
  Index = (INT8U)((PDI & 0x00FF0000) >> 16);
  if(Index EQ PERIOD_FREEZE_TYPE) //定时冻结
  {
    *pEvent_ID = ID_EVENT_PERIOD_FREEZE;
  }
  else if(Index EQ INSTANT_FREEZE_TYPE) //瞬时冻结
  {
    *pEvent_ID = ID_EVENT_INSTANT_FREEZE;
  }
  else if(Index EQ YEAR_SWITCH_FREEZE_TYPE) //两套年时区表切换
  {
    *pEvent_ID = ID_EVENT_YEAR_TABLE_SWITCH_FREEZE;
  }
  else if(Index EQ DATE_SWITCH_FREEZE_TYPE) //两套日时段表切换
  {
    *pEvent_ID = ID_EVENT_DATE_TABLE_SWITCH_FREEZE;
  }
  else if(Index EQ STEP_SWITCH_FREEZE_TYPE) //两套梯度切换
  {
    *pEvent_ID = ID_EVENT_STEP_SCH_SWITCH_FREEZE;
  }
  else if(Index EQ RATE_SWITCH_FREEZE_TYPE)//两套分时费率方案切换
  {
    *pEvent_ID = ID_EVENT_RATE_SCH_SWITCH_FREEZE; 
  }
  else if(Index EQ DATE_FREEZE_TYPE)//日冻结
  {
    *pEvent_ID = ID_EVENT_DATE_FREEZ; 
  }
  else if(Index EQ HOUR_FREEZE_TYPE)//小时冻结
  {
    *pEvent_ID = ID_EVENT_HOUR_FREEZ;  
  }
  else if(Index EQ ENG_OVERTURN_FREEZE_TYPE)//电量翻转 
  {
    *pEvent_ID = ID_EVENT_ENERGY_OVERTURN_FREEZE; 
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }  
  
  return 1;
}
//CONST INT16U Freeze_Data_Off[]={0,4*MAX_RATES}
//获取
INT16U Get_Freeze_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Re, Type, Spec_Flag;
  INT16U Len, TempLen;
  INT16U Index;
  static S_Int8U Bak_Index = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Event_ID;
  INT16U Off;

  TRACE();

  Len = 0;
  Re = 1;
  
  if(Get_Freeze_Data_Event_ID(PDI, &Event_ID) EQ 0) 
    return 0;
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  //注意：下面的Get_Event_Separate_Proto_Data函数内可能需要用到Pub_Buf0缓冲区
  //但是在此处不会用到，因此不会造成冲突
  Len = _Get_Event_Separate_Proto_Data((PDI & 0xFFFF00FF), (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0), &Spec_Flag);
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    Re = 0;
  }

  Index = Get_Event_Separate_Data_Index(Event_ID);
  if(Index EQ NULL_2BYTES)
  {
    ASSERT_FAILED();
    Re = 0;
  }

  TempLen = 0;
  Len = 0;
  
  if(Re EQ 1)
  {
    Type = (INT8U)((PDI & 0x00FF0000) >> 16);
    Index = (INT8U) ((PDI & 0x0000FF00) >> 8);//(INT8U)Bcd2Hex_Byte((INT8U)((DI & 0x0000FF00) >> 8));
    if(Index != 0xFF)
    {
      Off = Get_Freeze_Data_Off(Type, (INT8U) Index);
      
      if(Get_Freeze_Data_Mode_En(Type, (INT8U) Index) != 0) //模式字是否允许
        Len = Get_Freeze_Data_Len(Type, (INT8U) Index);
      else
        Len = 0;
           
      mem_cpy(pDst, (INT8U *) Pub_Buf0 + Off, Len, pDst_Start, DstLen);
    }
    else
    {
      if((Frame_Ack_Info.Follow_Flag EQ 0) && (Frame_Ack_Info.Read_Follow_Flag EQ 1))
        Frame_Ack_Info.Read_Follow_Flag = 0;      
      
      if(Frame_Ack_Info.Read_Follow_Flag EQ 0) //不是读后续数据
        Bak_Index.Var = 0;
        
      for(Index = Bak_Index.Var; Index <= 0x10;)
      {
        Off = Get_Freeze_Data_Off(Type, (INT8U) Index);
        
        if(Get_Freeze_Data_Mode_En(Type, (INT8U) Index) != 0) //模式字是否允许
          TempLen = Get_Freeze_Data_Len(Type, (INT8U) Index);
        else
          TempLen = 0;
             
        if(Len + TempLen > 200) //与后续帧
          break;
        
        mem_cpy(pDst + Len, (INT8U *) Pub_Buf0 + Off, TempLen, pDst_Start, DstLen);
        Len += TempLen;        
        *(pDst + Len) = 0xAA;
        Len ++;
        
        Index ++;
        if(Index EQ 0x0B)
          Index = 0x10;     
      }
      
      if(Index != 0x11)
      {
        Bak_Index.Var = Index;
        Frame_Ack_Info.Follow_Flag = 1; //有后续数据     
      }
      else
      {
        Bak_Index.Var = 0;
        Frame_Ack_Info.Follow_Flag = 0; //无后续数据      
      }      
    }
  }
  
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  
  return Len;
}

/*
INT16U Get_Freeze_Proto_Block_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Re;
  INT16U Len, DstLen;
  INT16U Index;

  INT8U Flag;
  INT16U Off;

  TRACE();

  Len = 0;
  Re = 1;
  
  ASSERT((PDI & 0xFF000000) EQ 0x05000000);

  if((PDI & 0xFFFF0000) EQ 0x05000000) //定时冻结
  {
    Flag = ID_EVENT_PERIOD_FREEZE;
  }
  else if((PDI & 0xFFFF0000) EQ 0x05010000) //瞬时冻结
  {
    Flag = ID_EVENT_INSTANT_FREEZE;
  }
  else if((PDI & 0xFFFF0000) EQ 0x05020000) //两套年时区表切换
  {
    Flag = ID_EVENT_YEAR_TABLE_SWITCH_FREEZE;
  }
  else if((PDI & 0xFFFF0000) EQ 0x05030000) //两套日时段表切换
  {
    Flag = ID_EVENT_DATE_TABLE_SWITCH_FREEZE;
  }
  else if((PDI & 0xFFFF0000) EQ 0x05040000) //两套梯度切换
  {
    Flag = ID_EVENT_STEP_SCH_SWITCH_FREEZE;
  }
  else if((PDI & 0xFFFF0000) EQ 0x05050000)//两套分时费率方案切换
  {
    Flag = ID_EVENT_RATE_SCH_SWITCH_FREEZE; 
  }
  else if((PDI & 0xFFFF0000) EQ 0x05100000)//日冻结
  {
    Flag = ID_EVENT_DATE_FREEZ; 
  }
  else if((PDI & 0xFFFF0000) EQ 0x05110000)//小时冻结
  {
    Flag = ID_EVENT_HOUR_FREEZ;  
  }
  else if((PDI & 0xFFFF0000) EQ 0x05120000)//电量翻转 
  {
    Flag = ID_EVENT_ENERGY_OVERTURN_FREEZE; 
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  //注意：下面的Get_Event_Separate_Proto_Data函数内可能需要用到Pub_Buf0缓冲区
  //但是在此处不会用到，因此不会造成冲突
  Len = Get_Event_Separate_Proto_Data((PDI & 0xFFFF00FF), (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    Re = 0;
  }


  Index = Get_Event_Separate_Data_Index(Flag);
  if(Index EQ NULL_2BYTES)
  {
    ASSERT_FAILED();
    Re = 0;
  }
  
  DstLen = 0;
  for(Index = 0; Index <= 0x10; )
  {  
    if(Re EQ 1)
    {
      Index = (INT8U) ((PDI & 0x0000FF00) >> 8);//(INT8U)Bcd2Hex_Byte((INT8U)((DI & 0x0000FF00) >> 8));
      Off = Get_Freeze_Data_Off((INT8U) Index);
      
      if(Get_Freeze_Data_Mode_En((INT8U) Index) != 0) //模式字是否允许
        Len = Get_Freeze_Data_Len((INT8U) Index);
      else
        Len = 0;
      
      mem_cpy(pDst + DstLen, (INT8U *) Pub_Buf0 + Off, Len, pDst_Start, DstLen);
      DstLen += Len;
      *(pDst + DstLen) = 0xAA;
      DstLen ++;
    }
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  
  return Len;  
  
}*/

#undef FREEZE_PROTO_C

