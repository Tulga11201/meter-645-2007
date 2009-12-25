#define CLOCK_C
#include "Includes.h"
/*
INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen);
INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen);
INT8U Write_ExtRTC_PUCK(INT8U *Src);
INT8U Read_ExtRTC_PUCK(INT8U *Dst,INT8U DstLen);
*/
/*
void init_DS3231(void);
��ds3231ʱ�䣬���������ֵ��{�룬�֣�ʱ�����ڣ��գ��£���}
void Read_DS3231(unsigned char *src);
дds3231ʱ�䣬д�������ֵ��{�룬�֣�ʱ�����ڣ��գ��£���}
��ȷ����1��������err
unsigned char Write_DS3231(unsigned char *src);
*/
//����ô��ʾ?
CONST S_BCD_Time Def_BCD_Time={.Sec=0x00,.Min=0x00,.Hour=0x00,.Week=0x01,.Date=0x01,.Month=0x01,.Year=0x01,.CS={0}};

//��ȡУʱ����
void Read_Adj_Time_Para_From_Rom()
{
  INT16U Len;
  
  Len = Read_Storage_Data(SDI_ADJ_TIME_COUNTS, (INT8U *)&Adj_Time_Para.Max_Counts, (INT8U *)&Adj_Time_Para.Max_Counts, sizeof((INT8U *)&Adj_Time_Para.Max_Counts));
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    Adj_Time_Para.Max_Counts = 1;
  }
  SET_STRUCT_SUM(Adj_Time_Para);
}

//�ڻ��ѵ�����¸���ʱ��
INT8U Resume_Clock_Update()
{
  INT8U Re;
  S_BCD_Time Temp_Time;
  
  Re = CHECK_STRUCT_SUM(Clock_Info);
  ASSERT(1 EQ Re);
  
  Re = 0;
  
  if(Get_Time_From_EXT_RTC((S_BCD_Time *)&Temp_Time))
    Re=1;
  
  if((Read_Ext_RTC_Status() & EXT_RTC_COUNT_STOP) != 0)//�ⲿʱ���Ƿ�λ?
  {
    Debug_Print("Read_Ext_RTC_Status Error!");
    ASSERT_FAILED();
    Re=0;
  }
  
  if(Re EQ 0)//��ȡ�ⲿʱ�����ݴ�����߶�ȡ������������0���ȡ�ڲ�ʱ�ӻ����ڴ��е�ʱ������
  {
    Debug_Print("Get_Time_From_EXT_RTC error,Set_INTER_RTC_Flag=%d",Clock_Info.Set_INTER_RTC_Flag);
    
    Set_Err_Time((S_BCD_Time *)&Temp_Time);//Ĭ��ʱ����Ϊ����ǰʱ�䣬��Ϊ�����ⲿʱ�Ӷ�����������֪������ǰʱ��
    Event_Data_Proc(ID_EVENT_RTCERR_PWRON,EVENT_OCCUR);
    
    Get_Timer_From_CPU_Inter(&Temp_Time);
    Set_Time_To_EXT_RTC((S_BCD_Time *)&Temp_Time);//�����ⲿʱ��
  }
  
  Clock_Info.Set_INTER_RTC_Flag=1;//ͬ��һ���ڲ�RTC
  Set_Time_To_INTER_RTC((S_BCD_Time *)&Temp_Time);
 
 
  //����õ�ʱ�����ݸ��Ƶ�Cur_Time1,Cur_Time_Bak��Cur_Time0
  mem_cpy((void *)&Cur_Time1,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
  SET_STRUCT_SUM(Cur_Time1);
  
  mem_cpy((void *)&Cur_Time_Bak,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
  SET_STRUCT_SUM(Cur_Time_Bak); 
  
  Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
  
  Set_BCD_Array_Time((S_BCD_Time *) &Cur_Time1, (S_Event_Time *) &Cur_Time2, (S_Event_Time *) &Cur_Time2, sizeof(Cur_Time2));

  Clock_Info.Clock_Ready_Flag=1;
  SET_STRUCT_SUM(Clock_Info);//�������ڴ�����У��� 
  return Re;
}


//���ⲿRTC��ȡʱ������
INT8U Get_Time_From_EXT_RTC(S_BCD_Time *pBCD_Time)
{
  INT8U Re,i;
  INT8U Temp[10];
  
  for(i = 0; i < MAX_IIC_ERR_RETRY; i++)
  {
    Clear_All_Dog();
    
    Re=Read_ExtRTC_PUCK(Temp,7);
    Debug_Print("Get_EXT_Time:%x-%x-%x %x:%x:%x,Week:%x",Temp[6],Temp[5],Temp[4],Temp[2],Temp[1],Temp[0],Temp[3]);
    if(1 EQ Re)
    {
      if(Temp[3]>=7)//DLT645��DS3231���������ݸ�ʽ ��һ��
        Temp[3]=0;
      pBCD_Time->Sec=Temp[0];
      pBCD_Time->Min=Temp[1];
      pBCD_Time->Hour=Temp[2];
      pBCD_Time->Week=Temp[3];
      pBCD_Time->Date=Temp[4];
      pBCD_Time->Month=Temp[5];
      pBCD_Time->Year=Temp[6];
      Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));
      if(Check_BCD_Time(pBCD_Time))//������ݸ�ʽ?
        return 1;
    }
    else
      ASSERT_FAILED();//(1 EQ Re);
    
    OS_TimeDly_Ms(200);
  }
  
  ReNew_Err_Code(DIS_RTC_ERR);
  ASSERT_FAILED();  
  return 0;
}

//��ʱ�����õ��ⲿRTC
INT8U Set_Time_To_EXT_RTC(S_BCD_Time *pBCD_Time)
{
  INT8U i;
  INT8U Re;
  INT8U Temp[10];
  
  Re=Check_BCD_Time(pBCD_Time);
  if(1!=Re)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  for(i = 0; i < MAX_IIC_ERR_RETRY; i++)
  {
    Clear_All_Dog();
    
    Temp[0]=pBCD_Time->Sec;
    Temp[1]=pBCD_Time->Min;
    Temp[2]=pBCD_Time->Hour;
    Temp[3]=pBCD_Time->Week;
    Temp[4]=pBCD_Time->Date;
    Temp[5]=pBCD_Time->Month;
    Temp[6]=pBCD_Time->Year;
    if(Temp[3] EQ 0 || Temp[3]>7)//DLT645��DS3231���������ݸ�ʽ ��һ��
      Temp[3]=7;
    
    Debug_Print("Set_EXT_Time:%x-%x-%x %x:%x:%x,Week:%x",Temp[6],Temp[5],Temp[4],Temp[2],Temp[1],Temp[0],Temp[3]);
    
    if(Write_ExtRTC_PUCK(Temp))
      return 1;
    else
      ASSERT_FAILED();
      
    OS_TimeDly_Ms(200);
  }
  
  ReNew_Err_Code(DIS_RTC_ERR);  
  ASSERT_FAILED();
  return 0;
}

//��Time�������õ�pBCD_Time������
//Time���ݵĸ�ʽ��--sec,min,hour,week,date,month,year
void Set_BCD_Time(INT8U Time[],S_BCD_Time *pBCD_Time)
{
  if(Time[3]>=7)//DLT645��DS3231���������ݸ�ʽ ��һ��
    Time[3]=0;
  pBCD_Time->Sec=Time[0];
  pBCD_Time->Min=Time[1];
  pBCD_Time->Hour=Time[2];
  pBCD_Time->Week=Time[3];
  pBCD_Time->Date=Time[4];
  pBCD_Time->Month=Time[5];
  pBCD_Time->Year=Time[6];  
  Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));  
}

//���ڲ�RTC��ȡʱ������
INT8U Get_Time_From_INTER_RTC(S_BCD_Time *pBCD_Time)
{
  INT8U Re;
  INT8U Temp[10];
  
  Re=Read_InterRTC_PUCK(Temp,7);
  ASSERT(1 EQ Re);
  //Debug_Print("Get_INTER_Time:%x-%x-%x %x:%x:%x,Week:%x",Temp[6],Temp[5],Temp[4],Temp[2],Temp[1],Temp[0],Temp[3]);
  if(1 EQ Re)
  {/*
    if(Temp[3]>=7)//DLT645��DS3231���������ݸ�ʽ ��һ��
      Temp[3]=0;
    pBCD_Time->Sec=Temp[0];
    pBCD_Time->Min=Temp[1];
    pBCD_Time->Hour=Temp[2];
    pBCD_Time->Week=Temp[3];
    pBCD_Time->Date=Temp[4];
    pBCD_Time->Month=Temp[5];
    pBCD_Time->Year=Temp[6];
    Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));    
    */
    Set_BCD_Time(Temp,pBCD_Time);

    Re=Check_BCD_Time(pBCD_Time);//������ݸ�ʽ?
    if(1!=Re)//ASSERT(1 EQ Re))
    {
      ASSERT_FAILED();
      return 0;
    }
    else 
      return 1;
  }
  else
    return 0;
}

//��ʱ�����õ��ڲ�RTC
INT8U Set_Time_To_INTER_RTC(S_BCD_Time *pBCD_Time)
{ 
  INT8U Re;
  INT8U Temp[10];
  
  Re=Check_BCD_Time(pBCD_Time);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    return 0;
  }
  Temp[0]=pBCD_Time->Sec;
  Temp[1]=pBCD_Time->Min;
  Temp[2]=pBCD_Time->Hour;
  Temp[3]=pBCD_Time->Week;
  Temp[4]=pBCD_Time->Date;
  Temp[5]=pBCD_Time->Month;
  Temp[6]=pBCD_Time->Year;
  if(Temp[3] EQ 0 || Temp[3]>7)//DLT645��DS3231���������ݸ�ʽ ��һ��
    Temp[3]=7;
  
  Re=Write_InterRTC_PUCK(Temp);
  return Re;
}

/*
  INT8U Sec;
  INT8U Min;
  INT8U Hour;
  INT8U Week;
  INT8U Date;
  INT8U Month;
  INT8U Year;

*/

INT8U Set_Time_EXT_INTER_Ram_RTC(S_BCD_Time * pBCD_Time)
{
  TRACE();
  
  if(Set_Time_To_EXT_RTC(pBCD_Time))
  {
    if(Set_Time_To_INTER_RTC(pBCD_Time))
    {
      //mem_cpy((S_BCD_Time *)&Cur_Time1,&TempTime,sizeof(TempTime),(S_BCD_Time *)&Cur_Time1,sizeof());
      Get_Time_From_INTER_RTC((S_BCD_Time *)&Cur_Time1);
      Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
      Set_BCD_Array_Time((S_BCD_Time *) &Cur_Time1, (S_Event_Time *) &Cur_Time2, (S_Event_Time *) &Cur_Time2, sizeof(Cur_Time2));
      
      return 1;
    }
  } 
  ASSERT_FAILED();
  return 0;
}

//����BCDʱ�䵽����ʱ��
void Set_BCD_Array_Time(S_BCD_Time* pSrc, S_Event_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  TRACE();

  if(!((INT8U *)pDst >= (INT8U *)pDst_Start && (INT8U *)pDst + sizeof(S_Event_Time) <= (INT8U *)pDst_Start + DstLen))
    ASSERT_FAILED();
  
  pDst -> Time[0] = pSrc -> Sec;
  pDst -> Time[1] = pSrc -> Min;
  pDst -> Time[2] = pSrc -> Hour;
  pDst -> Time[3] = pSrc -> Date;
  pDst -> Time[4] = pSrc -> Month;
  pDst -> Time[5] = pSrc -> Year;

  Set_STRUCT_Sum(pDst, sizeof(S_Event_Time), pDst -> CS, sizeof(pDst -> CS));
}

//��������ʱ�䵽BCDʱ��
void Set_Array_BCD_Time(S_Event_Time* pSrc, S_BCD_Time* pDst, void* pDst_Start, INT16U DstLen)
{
  TRACE();

  if(!((INT8U *)pDst >= (INT8U *)pDst_Start && (INT8U *)pDst + sizeof(S_BCD_Time) <= (INT8U *)pDst_Start + DstLen))
    ASSERT_FAILED();
  
  pDst -> Sec = pSrc -> Time[0];
  pDst -> Min = pSrc -> Time[1] ;
  pDst -> Hour = pSrc -> Time[2];
  pDst -> Date = pSrc -> Time[3];
  pDst -> Month = pSrc -> Time[4];
  pDst -> Year = pSrc -> Time[5];

  Set_STRUCT_Sum(pDst, sizeof(S_BCD_Time), pDst -> CS, sizeof(pDst -> CS));  
  
}

//ʱ�Ӵ���
//ÿ��GET_CLOCK_PERIOD��ˢ��һ��ʱ��
void Clock_Proc()
{
  INT8U Re;
  S_BCD_Time TempTime;

  static S_Int32U Sec_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
  static S_Int8U Sec={CHK_BYTE,0xFF,CHK_BYTE};
  
  TRACE();
  //��ʱˢ��ʱ�ӣ���ģ����ʱ��
  Re=CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(1 EQ Re);
  
  if(Sec_Bak.Var!=Sec_Timer_Pub)//ʱ�����һ��
  {
    Sec_Bak.Var=Sec_Timer_Pub;
    
    Re=Check_BCD_Time((S_BCD_Time *)&Cur_Time1);
    if(1!=Re)//ASSERT(1 EQ Re))//ʱ�䲻����ˢ��ʱ��
    {
      ASSERT_FAILED();
      Clock_Update();
    }
    Set_Soft_RTC_PUCK(ID_RAM_RTC);//����ʱ�䵽PUCK��ʱ������
    
    Get_Time_From_INTER_RTC((S_BCD_Time *)&TempTime);//��ȡ�ڲ�ʱ��
    if(Check_Time_Diff(&TempTime,(S_BCD_Time *)&Cur_Time1,5) EQ 0)//�ڴ��е��������ڲ�RTC����ʱ����5����,��Ϊ����
    {
      ASSERT_FAILED();
      Clock_Update();
      Get_Time_From_INTER_RTC((S_BCD_Time *)&TempTime);//���¶�ȡ�ڲ�ʱ��
    }
    
    mem_cpy((void *)&Cur_Time1,&TempTime,sizeof(TempTime),(void *)&Cur_Time1,sizeof(Cur_Time1));
    
    Sec.Var++; //��ʱ��+1
    if(Sec.Var>60 ||\
       Bcd2Hex_Byte(Cur_Time1.Min)!=Cur_Time0.Time[T_MIN])//һ����֮���ض�һ��Ӳʱ��
    {
      Clock_Update();
      Sec.Var=Bcd2Hex_Byte(Cur_Time1.Sec);
    }
    
    Set_BCD_Array_Time((S_BCD_Time *) &Cur_Time1, (S_Event_Time *) &Cur_Time2, (S_Event_Time *) &Cur_Time2, sizeof(Cur_Time2));
  }
}

//���ڴ���ȡ��һ����ȷ��ʱ������
INT8U Get_Time_From_Ram_Rom(S_BCD_Time *pBCD_Time)
{
  INT8U Re;//Err;
  //INT8U i;
  TRACE();
  
  Re=0;
  if(1 EQ CHECK_STRUCT_SUM(Cur_Time1) &&\
     1 EQ Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
  {
     mem_cpy(pBCD_Time,(void *)&Cur_Time1,sizeof(Cur_Time1),pBCD_Time,sizeof(S_BCD_Time));
     Re=1;
  }
  else if(1 EQ CHECK_STRUCT_SUM(Cur_Time_Bak) &&\
          1 EQ Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak))
  {
     mem_cpy(pBCD_Time,(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak),pBCD_Time,sizeof(S_BCD_Time));
     Re=1;
  }
  else if(1 EQ CHECK_STRUCT_SUM(Cur_Time0) &&\
          1 EQ Check_HEX_Time((S_HEX_Time *)&Cur_Time0))
  {
    Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,pBCD_Time);
    Re=1;
  }
  else if(Read_Storage_Data(_SDI_EVENT_DATA_PD,(void *)&Event_Data,(void *)&Event_Data,sizeof(Event_Data)))//��ȡ�洢ʱ��
  {
    mem_cpy(pBCD_Time, (void *)&Event_Data.Time, sizeof(Event_Data.Time), pBCD_Time, sizeof(S_BCD_Time));
    Re = 1;
  }
  else if(Read_Storage_Data(_SDI_TIME_BAK,pBCD_Time,pBCD_Time,sizeof(S_BCD_Time)))//��ȡ�洢����ʱ��
  {
    Re = 1; 
  }
  else//û���κ�ʱ����������ȷ�ģ�����������~~
  {
    /*
    for(i=0; i<3; i++)//���´�Rom�ж�ȡʱ�����ݣ���3�Σ���ֹ����ԭ���¶�ȡ����
    {
      if(Read_Storage_Data(TIME_PD,pBCD_Time,pBCD_Time,sizeof(S_BCD_Time),&Err))//��ȡ�洢ʱ��
      {
        Re = 1;
        break;
      }
      OS_TimeDly_Ms(100);//��ʱ100ms
      if(Read_Storage_Data(TIME_BAK_PD,pBCD_Time,pBCD_Time,sizeof(pBCD_Time),&Err))//��ȡ�洢����ʱ��
      {
        Re = 1;
        break;
      } 
      OS_TimeDly_Ms(100);//��ʱ100ms
    } 
    */
    if(Re  EQ  0)
    {
      Debug_Print("No Correct Time Find,Use Def start Time");
      mem_cpy(pBCD_Time,(void *)&Def_BCD_Time,sizeof(Def_BCD_Time),pBCD_Time,sizeof(S_BCD_Time));
      Re=0;
    }
  }
  
  Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));  
  return Re;
}

//��CPU�ڲ���ȡʱ������
void Get_Timer_From_CPU_Inter(S_BCD_Time *pBCD_Time)
{
    TRACE();
    
    if(1 EQ Clock_Info.Set_INTER_RTC_Flag &&\
       1 EQ Get_Time_From_INTER_RTC(pBCD_Time) &&\
       1 EQ Check_BCD_Time(pBCD_Time))
    {
      return;
    }
    else Get_Time_From_Ram_Rom(pBCD_Time);
  
}

//�������ʱ������֮��Ĳ��Ƿ�����?�Ƿ���Mins����֮��?
INT8U Check_Time_Diff(S_BCD_Time *pTime0,S_BCD_Time *pTime1,INT8U Mins)
{
  S_HEX_Time TempTime;//��̬��������ռ�ö�ջ
  S_HEX_Time Time0,Time1;
 
  TRACE();
    
  Convert_BCD_2_HEX_Time(pTime0,&Time0);
  Convert_BCD_2_HEX_Time(pTime1,&Time1);
  
  if(Cmp_Time(&Time0,&Time1) EQ TIME_AFT)
  {
    Time_Dec(&Time0,Mins,UNIT_MIN,&TempTime);
    if(Cmp_Time(&TempTime,&Time1) EQ TIME_BEF)
      return 1;
  }
  else
  {
    Time_Inc(&Time0,Mins,UNIT_MIN,&TempTime);
    if(Cmp_Time(&TempTime,&Time1) EQ TIME_AFT)
      return 1; 
  }
  return 0;
  /*
  INT32U Sec0,Sec1;
  Sec0=mktime((INT16U)Bcd2Hex_Byte(pTime0->Year)+2000,\
              Bcd2Hex_Byte(pTime0->Month),\
              Bcd2Hex_Byte(pTime0->Date),\
              Bcd2Hex_Byte(pTime0->Hour),\
              Bcd2Hex_Byte(pTime0->Min),\
              0);
  Sec1=mktime((INT16U)Bcd2Hex_Byte(pTime1->Year)+2000,\
              Bcd2Hex_Byte(pTime1->Month),\
              Bcd2Hex_Byte(pTime1->Date),\
              Bcd2Hex_Byte(pTime1->Hour),\
              Bcd2Hex_Byte(pTime1->Min),\
              0);
  if((Sec0>Sec1 && Sec0-Sec1>180) ||\
    (Sec0<Sec1 && Sec1-Sec0>180))
      return 0;
  else
    return 1;
  */
}

void Set_Err_Time(S_BCD_Time *pBCD_Time)
{
  RTC_Err_Time[0]=pBCD_Time->Min;
  RTC_Err_Time[1]=pBCD_Time->Hour;
  RTC_Err_Time[2]=pBCD_Time->Date;
  RTC_Err_Time[3]=pBCD_Time->Month;
  RTC_Err_Time[4]=pBCD_Time->Year;  
}
//ʱ�ӵ�ˢ��
void Clock_Update()
{
  INT8U i;
  INT8U Re,EXT_RTC_Status_Err_Flag;
  S_BCD_Time Temp_Time;
  S_BCD_Time Temp_Time0;
  S_BCD_Time Temp_Time1;
  
  TRACE();
    
  EXT_RTC_Status_Err_Flag=0;
  Re=CHECK_STRUCT_SUM(Clock_Info);
  if(1!=Re)//ASSERT(1 EQ Re))//У����ȷ
  {
    ASSERT_FAILED();
    mem_set((void *)&Clock_Info,0,sizeof(Clock_Info),(void *)&Clock_Info,sizeof(Clock_Info));
    SET_STRUCT_SUM(Clock_Info);
  }

  //�ȶ�ȡ�ⲿRTC�����ܷ������ȷ����,����ȷ�Ļ���������3��
  Re=0;//��ȡ��һ����ȷ��ʱ������
  if(Get_Time_From_EXT_RTC((S_BCD_Time *)&Temp_Time))
    Re=1;
  
  if((Read_Ext_RTC_Status() & EXT_RTC_COUNT_STOP) != 0)//�ⲿʱ��ͣ���?
  {
    Debug_Print("Read_Ext_RTC_Status Error!");
    ASSERT_FAILED();
    
    if(Re EQ 1)//���ܹ������ⲿʱ�����ݵ�����²���ʱ�Ӵ�����һ���ⲿʱ����Ӳ����������ܵ���1����дһ���¼���¼
    {
      Set_Err_Time((S_BCD_Time *)&Temp_Time);
      Event_Data_Proc(ID_EVENT_RTCERR_RUN, EVENT_OCCUR); //����ʱ�����¼���
    }
    
    Re=0;    
    EXT_RTC_Status_Err_Flag=1;//��ȡ�ⲿRTC״̬����!
  }
  
  if(Re EQ 1)
    Clock_Info.EXT_RTC_Err_Counts=0; 
  else
    Clock_Info.EXT_RTC_Err_Counts++;//�ⲿRTC�������  
  
  if(Re EQ 0)//��ȡ�ⲿʱ�����ݴ�����߶�ȡ������������0���ȡ�ڲ�ʱ�ӻ����ڴ��е�ʱ������
  {
    Debug_Print("Get_Time_From_EXT_RTC error,Set_INTER_RTC_Flag=%d",Clock_Info.Set_INTER_RTC_Flag);
    Get_Timer_From_CPU_Inter(&Temp_Time);
  }

  //����ʱ���֮���ʱ���̫���ˣ�������10���ӣ�����������ȡ3�ν����һ��
  for(i=0;i<3;i++)
  {
    if(Check_Time_Diff(&Temp_Time,(S_BCD_Time *)&Cur_Time1,10) EQ 0)//����ⲿʱ�����ڲ�ʱ�Ӳ��10����,���ض���ʱ�ӣ���ֹ����
    {
      OS_TimeDly_Ms(200);
      Get_Time_From_EXT_RTC(&Temp_Time);
    }
    else
      break;
  }
  
  if(Check_Time_Diff(&Temp_Time,(S_BCD_Time *)&Cur_Time1,10) EQ 0)//����ⲿʱ�����ڲ�ʱ�Ӳ��10���ӣ�
  {
    if(Clock_Info.Set_INTER_RTC_Flag EQ 1)//�ڲ�ʱ�����������ù�
    {
      Get_Time_From_INTER_RTC((S_BCD_Time *)&Temp_Time0);
      Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,(S_BCD_Time *)&Temp_Time1);
      //CPU��4��ʱ�����ݶ�û�г���5���ӵĲ��Ϊ�ڲ�ʱ����ȷ
      if(Check_Time_Diff((S_BCD_Time *)&Temp_Time0,(S_BCD_Time *)&Cur_Time1,5) EQ 1 &&\
         Check_Time_Diff((S_BCD_Time *)&Temp_Time0,(S_BCD_Time *)&Cur_Time_Bak,5) EQ 1 &&\
         Check_Time_Diff((S_BCD_Time *)&Temp_Time0,(S_BCD_Time *)&Temp_Time1,5) EQ 1)
      {
        //Set_Err_Time(&Temp_Time);
        //Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
        mem_cpy(&Temp_Time,(S_BCD_Time *)&Temp_Time0,sizeof(Temp_Time0),(S_BCD_Time *)&Temp_Time,sizeof(Temp_Time));
        EXT_RTC_Status_Err_Flag=1; 
      }
    }
  }
  
  Clock_Info.Set_INTER_RTC_Flag=1;//ͬ��һ���ڲ�RTC
  Set_Time_To_INTER_RTC((S_BCD_Time *)&Temp_Time);
  
  //������Ϊ0����������ζ�RTC����,�������ⲿRTC
  if(Clock_Info.EXT_RTC_Err_Counts>5 || EXT_RTC_Status_Err_Flag EQ 1)//�ⲿʱ����������5��,�����ⲿʱ��
  {
    Debug_Print("Reset EXT RTC!!!!!!!!!!!!");
    Set_Time_To_EXT_RTC((S_BCD_Time *)&Temp_Time);//�����ⲿʱ��
    //Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
    Clock_Info.EXT_RTC_Err_Counts=0;
  }   
 
  //����õ�ʱ�����ݸ��Ƶ�Cur_Time1,Cur_Time_Bak��Cur_Time0
  mem_cpy((void *)&Cur_Time1,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
  SET_STRUCT_SUM(Cur_Time1);
  
  mem_cpy((void *)&Cur_Time_Bak,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
  SET_STRUCT_SUM(Cur_Time_Bak); 
  
  Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
  
  Clock_Info.Clock_Ready_Flag=1;
  SET_STRUCT_SUM(Clock_Info);//�������ڴ�����У���
}


//S_BCD_Timeת��ΪS_HEX_Time
//ת���ɹ�����1��ʧ�ܷ���0,ʧ��������ԭ���ݸ�ʽ����У��Ͳ���
INT8U Convert_BCD_2_HEX_Time(S_BCD_Time *pBCD_Time,S_HEX_Time *pHEX_Time)
{
  INT8U Re;

  TRACE();
    
  Re = Check_BCD_Time(pBCD_Time);
  ASSERT(1 EQ Re);

  pHEX_Time->Time[T_MIN]=Bcd2Hex_Byte(pBCD_Time->Min);
  pHEX_Time->Time[T_HOUR]=Bcd2Hex_Byte(pBCD_Time->Hour);
  pHEX_Time->Time[T_DATE]=Bcd2Hex_Byte(pBCD_Time->Date);
  pHEX_Time->Time[T_MONTH]=Bcd2Hex_Byte(pBCD_Time->Month); 
  pHEX_Time->Time[T_YEAR]=Bcd2Hex_Byte(pBCD_Time->Year);
  pHEX_Time->Week=Bcd2Hex_Byte(pBCD_Time->Week);
  Set_STRUCT_Sum(pHEX_Time,sizeof(S_HEX_Time),pHEX_Time->CS,sizeof(pHEX_Time->CS));

  return Re;
}

//S_HEX_Timeת��ΪS_BCD_Time
//1��ʾת���ɹ���0��ʾʧ��,ʧ��������ԭ���ݸ�ʽ����У��Ͳ���
INT8U Convert_HEX_2_BCD_Time(S_HEX_Time *pHEX_Time,S_BCD_Time *pBCD_Time)
{
  INT8U Re;

  TRACE();
    
  Re = Check_HEX_Time(pHEX_Time);
  ASSERT(1 EQ Re);

  pBCD_Time->Min=Hex2Bcd_Byte(pHEX_Time->Time[T_MIN]);
  pBCD_Time->Hour=Hex2Bcd_Byte(pHEX_Time->Time[T_HOUR]);
  pBCD_Time->Date=Hex2Bcd_Byte(pHEX_Time->Time[T_DATE]);
  pBCD_Time->Month=Hex2Bcd_Byte(pHEX_Time->Time[T_MONTH]); 
  pBCD_Time->Year=Hex2Bcd_Byte(pHEX_Time->Time[T_YEAR]);
  pBCD_Time->Week=Hex2Bcd_Byte(pHEX_Time->Week);
  Set_STRUCT_Sum(pBCD_Time,sizeof(S_BCD_Time),pBCD_Time->CS,sizeof(pBCD_Time->CS));

  return Re;
}
//��ʼ��ʱ����ز���
void Init_Clock_Ram_Para()
{
  mem_set((void *)&Clock_Info,0,sizeof(Clock_Info),(void *)&Clock_Info,sizeof(Clock_Info));
  SET_STRUCT_SUM(Clock_Info);
}


//���ʱ�����ݵ���Ч��
void Check_Clock_Data_Avail()
{
  INT8U Re;
   
  //Cur_Time0,Cur_Time1��Cur_Time_Bak֮�以��������౸��
  //������ݶ����ˣ��ܲ���ֻ�����¶�ȡ�ⲿʱ����
  Re=Check_HEX_Time((S_HEX_Time *)&Cur_Time0);
  if(1!=Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
      Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
    else if(Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak))
      Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time_Bak,(S_HEX_Time *)&Cur_Time0);
    else 
      Clock_Update();
  }
  
  Re=Check_BCD_Time((S_BCD_Time *)&Cur_Time1);
  if(1!=Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    if(Check_HEX_Time((S_HEX_Time *)&Cur_Time0))
      Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,(S_BCD_Time *)&Cur_Time1);
    else if(Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak))
      mem_cpy((void *)&Cur_Time1,(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak),(void *)&Cur_Time1,sizeof(Cur_Time1));
    else 
      Clock_Update();
  }
  
  Re=Check_BCD_Time((S_BCD_Time *)&Cur_Time_Bak);
  if(1!=Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    if(Check_HEX_Time((S_HEX_Time *)&Cur_Time0))
      Convert_HEX_2_BCD_Time((S_HEX_Time *)&Cur_Time0,(S_BCD_Time *)&Cur_Time_Bak);
    else if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
      mem_cpy((void *)&Cur_Time_Bak,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
    else 
      Clock_Update();
  }
}
/*
//����ʱ�������ʱ��
void Save_PD_Time()
{
  if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
  {
    Write_Storage_Data(TIME_PD,(void *)&Cur_Time1,sizeof(Cur_Time1));   
    
  }
}

void Save_Bak_PD_Time()
{
  if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1))
  {
    Write_Storage_Data(TIME_BAK_PD,(void *)&Cur_Time1,sizeof(Cur_Time1));   
    
  }  
}
*/
//�ȴ�ʼ��׼����,��Ҫʱ�ӵ�������Ҫ�����������ǰ���øú���
void Wait_Clock_Ready()
{
  OS_Waitfor(1 EQ Clock_Info.Clock_Ready_Flag);
}

//��ʼ��ʱ��
void Init_Clock(INT32U Mode)
{
  //INT16U Len;
  //S_BCD_Time Temp_Time;
  //INT8U Temp[7];
  //INT8U Re,Err;
  
  Clock_Info.Set_INTER_RTC_Flag=0;
  SET_STRUCT_SUM(Clock_Info);
   
  Debug_Print("Init Clock!!");
  Resume_Clock_Update();// EQ 0)//�ⲿʱ�ӳ��������£��γ�һ���¼���¼
  //{
    //Event_Data_Proc(ID_EVENT_RTCERR_PWRON,EVENT_OCCUR);
  //}
/*  
  if(SYS_SLEEP EQ Mode)//��ǰΪ˯��̬,��������̬���縴λ������Ϊ��ʡ�磬���ڴ���ȡʱ���������õ��ڲ�RTC
  {
     if(Get_Time_From_Ram_Rom(&Temp_Time) EQ 0)//���������ڲ�ʱ�ӣ���Ϊ��λ���ڲ�ʱ����0
       Get_Time_From_EXT_RTC(&Temp_Time);

     Set_Time_To_INTER_RTC((S_BCD_Time *)&Temp_Time);
     Clock_Info.Set_INTER_RTC_Flag=1;
     SET_STRUCT_SUM(Clock_Info);
  }
  else  //������˯��ģʽ����Ҫ��ȡ�ⲿRTC,�������߻���ģʽ
  {
    Re=Get_Time_From_EXT_RTC((S_BCD_Time *)&Temp_Time);
    if(Read_Ext_RTC_Status()!=EXT_RTC_OK)
    {
      Debug_Print("Read_Ext_RTC_Status Error!");
      ASSERT_FAILED();
      Re=0;
    }
    
    if(0 EQ Re)//û�д��ⲿRTCȡ����ȷ����
    {
      Debug_Print("RTC Err,Reset EXT RTC!!!!!!!!!!!!");
      
      Set_Err_Time(&Temp_Time);
      Set_Event_Instant(ID_EVENT_RTCERR_RUN);//ʱ�����¼���¼
      
      //���ڴ���ȡһ����ȷ��ʱ��������䵽Cur_Time1
      if(Get_Soft_RTC_PUCK(Temp,sizeof(Temp)))//�ϵ�ǰ�����ǵ͹���״̬,��Ҫ���͹���ʱ���������赽�ڲ�RTC��
      {
        Set_BCD_Time(Temp,(S_BCD_Time *)&Temp_Time);
        if(Check_BCD_Time(&Temp_Time))
          mem_cpy((void *)&Cur_Time1,&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
        else
          Get_Time_From_Ram_Rom((S_BCD_Time *)&Cur_Time1);
      }
      else
      {
        Len=Read_Storage_Data(TIME_PD,&Temp_Time,&Temp_Time,sizeof(Temp_Time),&Err); 
        if(Len>0 && Check_BCD_Time(&Temp_Time))
        {
          mem_cpy((void *)&(Cur_Time1),&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
          Debug_Print("No correct time,use TIME_PD Data!");
        }
        else
        {
          Len=Read_Storage_Data(TIME_BAK_PD,&Temp_Time,&Temp_Time,sizeof(Temp_Time),&Err); 
          if(Len>0 && Check_BCD_Time(&Temp_Time))
          {
            mem_cpy((void *)&(Cur_Time1),&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
            Debug_Print("No correct time,use TIME_BAK_PD Data!");
          } 
        }
      }
      
      if(Check_BCD_Time((S_BCD_Time *)&Cur_Time1) EQ 0)//���ڴ���ȡһ��ʱ�����ݣ����õ��ⲿRTC
      {
        Debug_Print("Reset EXT RTC 01-01-01 00:00!!!!!!!!!!!!");
        mem_cpy((void *)&Cur_Time1,(void *)&Def_BCD_Time,sizeof(Def_BCD_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
        SET_STRUCT_SUM(Cur_Time1);
      }
      //��ʱCur_Time1��һ����ȷ���ݣ������������õ��ⲿRTC
      Set_Time_To_EXT_RTC((S_BCD_Time *)&Cur_Time1);
    }
    else
      mem_cpy((void *)&Cur_Time1,(void *)&Temp_Time,sizeof(Temp_Time),(void *)&Cur_Time1,sizeof(Cur_Time1));
   
    Convert_BCD_2_HEX_Time((S_BCD_Time *)&Cur_Time1,(S_HEX_Time *)&Cur_Time0);
    
    Set_Time_To_INTER_RTC((S_BCD_Time *)&Cur_Time1);
    mem_cpy((void *)&Cur_Time_Bak,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Cur_Time_Bak,sizeof(Cur_Time_Bak));
    Clock_Info.Set_INTER_RTC_Flag=1;
    SET_STRUCT_SUM(Clock_Info);       
  }
  */
}

//Flag������ʾ�Ƿ��¼Уʱʱ���¼��1��ʾ��¼��0��ʾ����¼
INT8U Adj_Time(S_BCD_Time *pTime, INT8U Flag)
{
    //�����¼�ʱ��
  
    //����Уʱǰʱ��  
    mem_cpy((void *)&Adj_Bef_Time, (void *)&Cur_Time2, sizeof(Cur_Time2),\
            (void *)&Adj_Bef_Time, sizeof(Adj_Bef_Time));
            
    if(Set_Time_EXT_INTER_Ram_RTC(pTime))
    {
      //Set_Event_Instant(ID_EVENT_ADJUST_TIME);//Уʱ��ʼ
      //OS_Waitfor_Sec(Read_Event_Status(ID_EVENT_ADJUST_TIME) EQ 1,5);//�ȴ�5s��û�д������򱨶��Դ���
      //if(Read_Event_Status(ID_EVENT_ADJUST_TIME)!=1)
        //ASSERT(A_WARNING,0);
      //Event_MultiTimes_Proc(ID_EVENT_ADJUST_TIME,EVENT_OCCUR,EVENT_REAL);
      /*
      if(Flag EQ 1)
      {
        OS_Waitfor_Sec(Read_Event_Status(ID_EVENT_ADJUST_TIME) EQ 1,5);//�ȴ�5s��û�д������򱨶��Դ���
        if(Read_Event_Status(ID_EVENT_ADJUST_TIME)!=1)
          ASSERT(A_WARNING,0);      
        Set_Event_Instant(ID_EVENT_ADJUST_TIME);//Уʱ����
        
      }
      */
      
      if(Flag EQ 1) //��¼Уʱ��¼��������Event_Data_Proc,ִ�и���
      {
        Event_Cumu_Proc(ID_EVENT_ADJUST_TIME,EVENT_OCCUR,EVENT_REAL);
        Event_Separate_Proc(ID_EVENT_ADJUST_TIME,EVENT_OCCUR,EVENT_REAL);
      }
      
      //Event_MultiTimes_Proc(ID_EVENT_ADJUST_TIME,EVENT_END,EVENT_REAL);
      Clr_Demand_Accu();//�����ۼӵ�Ԫ��0
      
      Time_Modify_Flag.Var = 1;
      return 1;
    }
    
    return 0;
  
}

//�㲥Уʱ����
INT8U Adjust_Time_Proc(INT8U* pSrc, INT8U SrcLen)
{
  S_BCD_Time TempTime;
  S_HEX_Time TempTime1, Temp_Cur_Time;
  INT8U y, m, d;//���ڼ�������
  //INT8U Re;
  
  TRACE();

  TempTime.Sec = *pSrc;
  TempTime.Min = *(pSrc + 1);
  TempTime.Hour = *(pSrc + 2);
  TempTime.Date = *(pSrc + 3);
  TempTime.Month = *(pSrc + 4);
  TempTime.Year = *(pSrc + 5);
  y = Bcd2Hex_Byte(TempTime.Year); 
  m = Bcd2Hex_Byte(TempTime.Month);
  d = Bcd2Hex_Byte(TempTime.Date);
  TempTime.Week = Week(y, m, d);
  SET_STRUCT_SUM(TempTime);
  if(Check_BCD_Time(&TempTime))
  {
    Convert_BCD_2_HEX_Time(&TempTime, &TempTime1);

    
    //�����������Уʱ,Ҳ������ʱ��У����ʱ
    if((Cur_Time0.Time[T_HOUR] EQ 0 && Cur_Time0.Time[T_MIN] EQ 0) ||
       (TempTime1.Time[T_HOUR] EQ 0 && TempTime1.Time[T_MIN] EQ 0))
    {
      ASSERT_FAILED();
      return 0;
    }
    
    if((Cur_Time0.Time[T_HOUR] EQ 23 && Cur_Time0.Time[T_MIN] >= 55) ||
       (Cur_Time0.Time[T_HOUR] EQ 0 && TempTime1.Time[T_MIN] <= 5))
    {
      ASSERT_FAILED();
      return 0;
    }
        
    //��ǰʱ�䳬����ǰʱ�������5���ӣ��򷵻�ʧ��
    Time_Inc((S_HEX_Time *) &Cur_Time0, 5, UNIT_MIN, &Temp_Cur_Time);//��ǰʱ�������5����    
    if(Cmp_Time(&TempTime1, &Temp_Cur_Time) EQ TIME_AFT)
    {
      ASSERT_FAILED();
      return 0;
    }
    
    Time_Dec((S_HEX_Time *) &Cur_Time0, 5, UNIT_MIN, &Temp_Cur_Time);
    if(Cmp_Time(&TempTime1, &Temp_Cur_Time) EQ TIME_BEF)
    {
      ASSERT_FAILED();
      return 0;
    }

    //ͬһ��ֻ׼�㲥Уʱһ��
    if(TempTime.Year EQ Last_Adj_Time.Year && 
       TempTime.Month EQ Last_Adj_Time.Month &&
       TempTime.Date EQ Last_Adj_Time.Date)
    {
      if(Adj_Time_Para.Max_Counts EQ 0)
        Adj_Time_Para.Max_Counts = 1;
      
      if(Adj_Time_Counts >= Adj_Time_Para.Max_Counts) //����ͬһ�����Уʱ����
      {
        ASSERT_FAILED();
        return 0;
      }
    }
    else
    {
      DIS_PD_INT;
      Adj_Time_Counts = 0;
      SET_STRUCT_SUM(Event_Data);
      EN_PD_INT;      
    }
    
   //�㲥Уʱ����¼�¼���¼
    if(Adj_Time(&TempTime, 0))
    {
      DIS_PD_INT;
      //�����¼�ʱ��
      mem_cpy((void *)&Last_Adj_Time, &TempTime, sizeof(TempTime), (void *)&Last_Adj_Time, sizeof(Last_Adj_Time));
      Adj_Time_Counts ++;
      //SET_STRUCT_SUM(Last_Adj_Time);
      SET_STRUCT_SUM(Event_Data);
      EN_PD_INT;
      
      Debug_Print("Adjust_Time_Proc Successful!!!");
      return 1;
    }
  }

  return 0;
}
#undef CLOCK_C
