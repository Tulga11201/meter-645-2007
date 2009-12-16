#define FREEZE_DATA_C
#include "includes.h"

#define HOUR_FREEZE_MIN_PERIOD 1

//��鶳�����
void Check_Freeze_Para()
{
	TRACE();
  //if(CHECK_STRUCT_SUM(Period_Freeze_Time))==1)
  {
    if(Freeze_Para.Period_Freeze_Time[0] != 0x99 && Freeze_Para.Period_Freeze_Time[0] >= 0x60)//��
    {
      ASSERT_FAILED();
      Freeze_Para.Period_Freeze_Time[0] = 0;
      SET_STRUCT_SUM(Freeze_Para);
    }
    if(Freeze_Para.Period_Freeze_Time[1] != 0x99 && Freeze_Para.Period_Freeze_Time[1] >= 0x24)//ʱ
    {
      ASSERT_FAILED();
      Freeze_Para.Period_Freeze_Time[1] = 0;
      SET_STRUCT_SUM(Freeze_Para);
    }
    if(Freeze_Para.Period_Freeze_Time[2] != 0x99 && (Freeze_Para.Period_Freeze_Time[2] > 0x31 || Freeze_Para.Period_Freeze_Time[2] EQ 0))//��
    {
      ASSERT_FAILED();
      Freeze_Para.Period_Freeze_Time[2] = 1;
      SET_STRUCT_SUM(Freeze_Para);
    }
  }
}

//��ROM�ж�ȡ�������
void Read_Freeze_Para_From_Rom()
{
  INT16U Len;
  INT8U i;
  
  TRACE();
  //���ڶ���ʱ��
  Len = Read_Storage_Data(SDI_PERIOD_FREEZE_TIME, (void *) Freeze_Para.Period_Freeze_Time, (void *) Freeze_Para.Period_Freeze_Time, sizeof(Freeze_Para.Period_Freeze_Time));
  ASSERT(Len EQ 4);//��Ĭ�ϲ���
  //���㶳����ʼʱ��
  Len = Read_Storage_Data(SDI_HOUR_FREEZE_START_TIME, (void *)Freeze_Para.Hour_Freeze_Start_Time, \
                          (void *)Freeze_Para.Hour_Freeze_Start_Time, sizeof(Freeze_Para.Hour_Freeze_Start_Time));
  //BCD_2_HEX
  Bcd2Hex_Buf((INT8U *)Freeze_Para.Hour_Freeze_Start_Time, sizeof((INT8U *)Freeze_Para.Hour_Freeze_Start_Time),
              (INT8U *)Freeze_Para.Hour_Freeze_Start_Time,(INT8U *)Freeze_Para.Hour_Freeze_Start_Time, sizeof(Freeze_Para.Hour_Freeze_Start_Time));
  ASSERT(Len EQ 5);
  //���㶳������
  Len = Read_Storage_Data(SDI_HOUR_FREEZE_PERIOD, (void *) &Freeze_Para.Hour_Freeze_Period, \
                          (void *)&Freeze_Para.Hour_Freeze_Period, sizeof(Freeze_Para.Hour_Freeze_Period));
  Freeze_Para.Hour_Freeze_Period = Bcd2Hex_Byte(Freeze_Para.Hour_Freeze_Period);
  ASSERT(Len EQ 1);
  //�ն���ʱ��
  Len = Read_Storage_Data(SDI_DATE_FREEZE_TIME, (void *)Freeze_Para.Date_Freeze_Time, \
                          (void *)Freeze_Para.Date_Freeze_Time, sizeof(Freeze_Para.Date_Freeze_Time));
  ASSERT(Len EQ 2);  
  SET_STRUCT_SUM(Freeze_Para);
  
  //��ȡ5������ģʽ��
  for(i = 0; i < 5; i ++)
  {
    Len = Read_Storage_Data(SDI_FREEZE_REC_WORD + i, (void *) &Freeze_Para.Mode[i], (void *)&Freeze_Para.Mode, sizeof(Freeze_Para.Mode));
    ASSERT(Len EQ 1);
  }
  
  //���㶳��ģʽ��ֻ�����2λ��Ч
  Freeze_Para.Mode[3] = (Freeze_Para.Mode[3] & 0x03);
  SET_STRUCT_SUM(Freeze_Para);

  Check_Freeze_Para();
}

//��鶳������ĺϷ���
void Check_Freeze_Para_Avail()
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Freeze_Para);
  if(1 != Re)//ASSERT(Re EQ 1))
  {
    ASSERT_FAILED();
    Read_Freeze_Para_From_Rom();
  }

  Check_Freeze_Para();
}

/*
//�������ݴ���
INT16U Get_Period_Freeze_Data(S_Freeze_Data *pData,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT8U i,FollowFlag,Err;
  INT16U Len,Len1;
  
  Len=0;
  for(i=0;i<pData->Data_Num;i++)
  {
  Len1=_Get_DLT645_Data(pData->Freeze_DI[i],(void *)0,0,(INT8U *)pDst+Len,(INT8U *)pDst,DstLen,FOR_EVENT,&FollowFlag,&Err); 
  if(ASSERT(A_WARNING,Len1>0 && NO_ERR==Err))
  {
  return 0; 
  }
  else
  {
  Len+=Len1; 
  }
  }
  Len1=Get_Storage_Data_Len(pData->DI);
  if(ASSERT(A_WARNING,Len==Len1))
  return 0;
  else
  return Len;
}

//���ڶ������ݴ���
void Period_Freeze_Data_Proc()
{
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
 
  if(Min_Bak.Var!=Cur_Time0.Time[T_MIN])
  {
  Min_Bak.Var=Cur_Time0.Time[T_MIN];
  //ÿ�ն���ʱ��㵽��
  //�����ܵ���
  if(Energy_Freeze_Time.Min==Cur_Time0.Time[T_MIN] &&
   Energy_Freeze_Time.Hour==Cur_Time0.Time[T_HOUR])
  {
  Debug_Print("----------Period Freeze Data!----------");
  //��Freeze_Data�ж����ÿ����������ж���
  Freeze_Right_Now(0);
  }
  //�����޹�����
  if(Reactive_Freeze_Time.Min==Cur_Time0.Time[T_MIN] &&
   Reactive_Freeze_Time.Hour==Cur_Time0.Time[T_HOUR])
  {
  Debug_Print("----------Period Freeze Data!----------");
  //��Freeze_Data�ж����ÿ����������ж���
  Freeze_Right_Now(1);
  
  }
  }
}

//�������ᣬ������Ӧ������������
void Freeze_Right_Now(INT8U Index)
{
  INT16U Len;
  
 // for(i=0;i<S_NUM(Freeze_Data)-1;i++)
  {
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  Len=Get_Period_Freeze_Data((S_Freeze_Data *)&Freeze_Data[Index],(INT8U *)Pub_Buf0,(INT8U *)Pub_Buf0,sizeof(Pub_Buf0));
  Write_Storage_Data(Freeze_Data[Index].DI,(INT8U *)Pub_Buf0,Len);
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  }  
}

//�յ���������֡����
INT8U Protocol_Freeze_Data(INT8U Flag)
{
  INT8U Re;
  Re=0;
  if(Flag==0x03)
  {
   Freeze_Right_Now(0);//˲ʱ���͵�������
   Re=1;
  }
  else if(Flag==0x13)//�ܵ�����������
  {
   Freeze_Right_Now(1);
   Re=1;  
  }
  return Re;
}

//�ö������ݵ�Ĭ������
void Set_Def_Freeze_Data()//��Ĭ�ϵĶ�������
{
  INT8U i;
  INT16U Len;
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  mem_set((INT8U *)Pub_Buf0,0,sizeof(Pub_Buf0),(INT8U *)Pub_Buf0,sizeof(Pub_Buf0));
  
  for(i=0;i<S_NUM(Freeze_Data);i++)
  {
  Len=Get_Storage_Data_Len(Freeze_Data[i].DI);
  Write_Storage_Data(Freeze_Data[i].DI,(INT8U *)Pub_Buf0,Len);
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}
*/

//Сʱ���ᴦ��
void Hour_Freeze_Proc()
{
  INT16U Mins;
  INT8U Period;
  
  if(_Check_HEX_Time((INT8U *)Freeze_Para.Hour_Freeze_Start_Time) EQ 0)
    return;
  
  //��ǰʱ������ʼʱ����ǰ��������
  if(Cmp_Array_Time((INT8U *)Cur_Time0.Time, (INT8U *)Freeze_Para.Hour_Freeze_Start_Time, sizeof(Cur_Time0.Time)) EQ TIME_BEF)
    return;
  
  Mins = (INT16U)Cur_Time0.Time[0] + (INT16U)Cur_Time0.Time[1] * 60;
  Period = Freeze_Para.Hour_Freeze_Period;

  if(Period > 0 && Period < HOUR_FREEZE_MIN_PERIOD) //С��15������0���޸�Ϊ15
    Period = HOUR_FREEZE_MIN_PERIOD;

  if(Period != 0 && (Mins % Period) EQ 0 &&\
    memcmp((INT8U *)&Last_Freeze_Time.Hour_Freeze_Time.Time, (INT8U *)&Cur_Time0.Time,5) != 0)
  {
    Debug_Print("Hour Freeze Data!");
    
    DIS_PD_INT;
    mem_cpy((INT8U *)Last_Freeze_Time.Hour_Freeze_Time.Time, (INT8U *)&Cur_Time0.Time, sizeof(Cur_Time0.Time),\
            (INT8U *)Last_Freeze_Time.Hour_Freeze_Time.Time, sizeof(Last_Freeze_Time.Hour_Freeze_Time.Time));
    
    SET_STRUCT_SUM(Event_Data._Last_Freeze_Time);
    SET_STRUCT_SUM(Event_Data);
    EN_PD_INT;
    
    Event_Separate_Proc(ID_EVENT_HOUR_FREEZ, EVENT_OCCUR, EVENT_REAL);//Сʱ����!!  
  }  
  
}


void Date_Freeze_Proc()
{
  if(Cur_Time1.Min EQ Freeze_Para.Date_Freeze_Time[0] &&\
     Cur_Time1.Hour EQ Freeze_Para.Date_Freeze_Time[1] &&\
     memcmp((INT8U *)&Last_Freeze_Time.Date_Freeze_Time.Time[T_DATE], (INT8U *)&Cur_Time0.Time[T_DATE],3) != 0)
  {
    Debug_Print("Date Freeze Data!");
    
    DIS_PD_INT;
    mem_cpy((INT8U *)Last_Freeze_Time.Date_Freeze_Time.Time, (INT8U *)&Cur_Time0.Time, sizeof(Cur_Time0.Time),\
            (INT8U *)Last_Freeze_Time.Date_Freeze_Time.Time, sizeof(Last_Freeze_Time.Date_Freeze_Time.Time));
    
    SET_STRUCT_SUM(Event_Data._Last_Freeze_Time);
    SET_STRUCT_SUM(Event_Data);
    EN_PD_INT;
   
    Event_Separate_Proc(ID_EVENT_DATE_FREEZ, EVENT_OCCUR, EVENT_REAL);//�ն���!
  }
}

void Period_Freeze_Proc()
{
  INT8U i, j;
  INT8U Temp[5];
  
  //��ʱ����
  //�ҵ���һ��0x99
  for(i = 0; i < 4; i ++)
  {
    if(Freeze_Para.Period_Freeze_Time[i] EQ 0x99)
    {
      break;
    }
  }
  
  if(i EQ 0) //��һ������0x99(����ʱ������һ����������)
    return;

  //0x99֮ǰ��ʱ���Ƿ����?
  Get_BCD_Time((S_BCD_Time *) &Cur_Time1, Temp, Temp, sizeof(Temp));
  for(j = 0; j < i; j ++)
  {
    if(Freeze_Para.Period_Freeze_Time[j] != Temp[j])
    {
      return;
    }
  }

  Debug_Print("Period_Freeze_Data Now");
  Event_Separate_Proc(ID_EVENT_PERIOD_FREEZE, EVENT_OCCUR, EVENT_REAL);//��ʱ����!!!  
  
}

//���ڶ�������
void Freeze_Proc()
{
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  //static S_Int8U Hour_Bak = {CHEK_BYTE, 0xFF, CHK_BYTE};
  //static S_Int8U Date_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U Re;
  //INT8U Temp[5];

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min_Bak);
  Re &= CHECK_STRUCT_SUM(Event_Data._Last_Freeze_Time);
  //Re = CHECK_STRUCT_VAR(Hour_Bak);
  //Re = CHECK_STRUCT_VAR(Date_Bak);
  if(Re EQ 0)
    ASSERT_FAILED();

  if(Min_Bak.Var EQ Cur_Time0.Time[T_MIN])
  {
    return;
  }

  TRACE();

  Min_Bak.Var = Cur_Time0.Time[T_MIN];
/*  
  if(Cur_Time0.Time[T_MIN] EQ 0 || Cur_Time0.Time[T_MIN] EQ 30)//0�ֺ�30�ֶ���
  {  
    Event_Separate_Proc(ID_EVENT_HOUR_FREEZ, EVENT_OCCUR, EVENT_REAL);//Сʱ����!!
  }
 */

  Hour_Freeze_Proc();
  Date_Freeze_Proc();
  Period_Freeze_Proc();


  
 
}

#undef FREEZE_DATA_C
