#define TIME_C
#include "string.h"
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H29"
#endif

CONST INT8U Month0[12] =
{
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};//ƽ��ÿ������

CONST INT8U Month1[12] =
{
  31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};//����ÿ������

//�ж�ĳ���Ƿ������꣬���򷵻�1�����򷵻�0
INT8U Check_Leep_Year(INT8U Year)
{
  INT16U Temp;

  Temp = 2000 + (INT16U) Year;
  if(((Temp % 4) EQ 0 && (Temp % 100) != 0) || ((Temp % 400) EQ 0))//����
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*-----------------------------------------------
����:����ʱ���ʽ֮���ת������Time�ĸ�ʽת����Time1��
���:
Timeʱ���ʽ
Time[0]��,Time[1]��,Time[2]��,Time[3]ʱ,Time[4]��
TIme1ʱ���ʽ
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Time_Pre_Format(INT8U Time[], INT8U Time1[])
{
  mem_cpy(Time1, Time, 5, Time1, 5);
}

void Time_Aft_Format(INT8U Time[], INT8U Time1[])
{
  mem_cpy(Time1, Time, 5, Time1, 5);
}
/*-----------------------------------------------
����:Timeʱ������ϼ��� Mins����
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Dec_Min(INT8U Time[], INT8U Mins)
{
  if(Mins >= 60)
    ASSERT_FAILED();

  if(Time[0] >= Mins) //����
  {
    Time[0] = Time[0] - Mins;
  }
  else
  {
    Time[0] = Time[0] + 60 - Mins;
    Dec_Hour(Time, 1);
  }
}
/*-----------------------------------------------
����:Timeʱ������ϼ��� HoursСʱ
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Dec_Hour(INT8U Time[], INT8U Hours)
{
  if(Hours >= 24)
    ASSERT_FAILED();

  if(Time[1] >= Hours)
  {
    Time[1] = Time[1] - Hours;
  }
  else
  {
    Time[1] = Time[1] + 24 - Hours;
    Dec_Day(Time, 1);
  }
} 
/*-----------------------------------------------
����:Timeʱ������ϼ��� Days��
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Dec_Day(INT8U Time[], INT8U Days)
{
  if(Days > 28)
    ASSERT_FAILED();

  if(Time[2] > Days)
  {
    Time[2] = Time[2] - Days;
  }
  else
  {
    Dec_Month(Time, 1);//ǰ׷1��
    //���¼�����
    if(Check_Leep_Year(Time[4]))//����
      Time[2] = Time[2] + Month1[Time[3] - 1] - Days;
    else
      Time[2] = Time[2] + Month0[Time[3] - 1] - Days;
  }
}
/*-----------------------------------------------
����:Timeʱ������ϼ��� Months��
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Dec_Month(INT8U Time[], INT8U Months)
{
  if(Months > 12)//��������ǰ��12��
    ASSERT_FAILED();
  
  if(Time[3] > Months)
  {
    Time[3] = Time[3] - Months;
  }
  else
  {
    Time[3] = 12 + Time[3] - Months;
    Dec_Year(Time, 1);
  }
}

/*-----------------------------------------------
����:Timeʱ������ϼ��� Years��
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Dec_Year(INT8U Time[], INT8U Years)
{
  //ASSERT(Time[4]>Years);

  if(Time[4] >= Years)
  {
    Time[4] = Time[4] - Years;
  }
  else
  {
    Time[4] = 100 - (Years - Time[4]);
  }
}
/*-----------------------------------------------
����:Timeʱ����������� Mins����
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Inc_Min(INT8U Time[], INT8U Mins)
{
  if(Mins >= 60)
    ASSERT_FAILED();

  if(Time[0] + Mins < 60) //����
  {
    Time[0] = Time[0] + Mins;
  }
  else
  {
    Time[0] = Mins + Time[0] - 60;
    Inc_Hour(Time, 1);
  }
}
/*-----------------------------------------------
����:Timeʱ����������� Hours Сʱ
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Inc_Hour(INT8U Time[], INT8U Hours)
{
  if(Hours >= 24)
    ASSERT_FAILED();

  if(Time[1] + Hours < 24)
  {
    Time[1] = Time[1] + Hours;
  }
  else
  {
    Time[1] = Time[1] + Hours - 24;
    Inc_Day(Time, 1);
  }
}
/*-----------------------------------------------
����:Timeʱ����������� Days��
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Inc_Day(INT8U Time[], INT8U Days)
{
  INT8U Month_Days;

  if(Days >= 31)
    ASSERT_FAILED();

  //���㵱������
  if(Check_Leep_Year(Time[4]))//����
  {
    Month_Days = Month1[Time[3] - 1];
  }
  else
  {
    Month_Days = Month0[Time[3] - 1];
  }

  if(Time[2] + Days <= Month_Days)
  {
    Time[2] = Time[2] + Days;
  }
  else
  {
    Time[2] = Time[2] + Days - Month_Days;
    Inc_Month(Time, 1);  
  }
}
/*-----------------------------------------------
����:Timeʱ����������� Months��
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Inc_Month(INT8U Time[], INT8U Months)
{
  if(Months > 12)
    ASSERT_FAILED();

  if(Time[3] + Months <= 12)
  {
    Time[3] = Time[3] + Months;
  }
  else
  {
    Time[3] = Time[3] + Months - 12;
    Inc_Year(Time, 1);
  }
}

/*-----------------------------------------------
����:Timeʱ����������� Years��
���:pCommonTask��ͨ����Ĳ���z
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
����:��
------------------------------------------------*/
void Inc_Year(INT8U Time[], INT8U Years)
{
  //if(Time[4] + Years >= 100) //��������ǰ��24�£����ǵ���ʷ���ݿ��ܳ���12����˳�����12
    //ASSERT_FAILED();
  
  if(Time[4] + Years < 100)
  {
    Time[4] += Years;
  }
  else
  {
    Time[4] = Time[4] + Years - 100;
  }
}
/*-----------------------------------------------
����:�� Interval ʱ��ת��Ϊ Time��UnitΪ Interval �ĵ�λ
���:
Time[0]��,Time[1]ʱ,Time[2]��,Time[3]��,Time[4]��
Interval,ʱ��ֵ
Unit��Interval��λ,02����,3Сʱ��4��,5��
����:��
------------------------------------------------*/
void ConvertTime(INT8U Time[], INT16U Interval, INT8U Unit)
{
  mem_set(Time, 0, 5, Time, 5);
  if(Unit EQ UNIT_MIN)
  {
    //Time[3]=Interval/1440/31;
    Time[2] = Interval / 1440;
    Time[1] = (Interval % 1440) / 60;
    Time[0] = Interval % 60;
  }
  else if(Unit EQ UNIT_HOU)
  {
    Time[2] = Interval / 24;
    Time[1] = Interval % 24;
  }
  else if(Unit EQ UNIT_DAY)
  {
    Time[3] = Interval / 31;
    Time[2] = Interval % 31;
  }
  else if(Unit EQ UNIT_MON)
  {
    Time[4] = Interval / 12;
    Time[3] = Interval % 12;
  }
}
/*-----------------------------------------------
����:Timeʱ����������� Interval ��ʱ��ֵ,Interval�ĵ�λ��Unit
���:
Time,��Ҫת����ʱ��ֵ��ͬʱת���õ�ʱ��ֵҲ����Time��
Time[0]��,Time[1]��,Time[2]��,Time[3]ʱ,Time[4]��
����:��
------------------------------------------------*/
void Time_Inc(S_HEX_Time* pTime0, INT16U Interval, INT8U Unit, S_HEX_Time* pTime1)
{
  INT8U Re, Temp[5], TempTime[5];

  Re = Check_HEX_Time(pTime0);
  if(Re EQ 0)
    ASSERT_FAILED();

  if(sizeof(pTime1->Time) != 5)
    ASSERT_FAILED();
  
  Time_Pre_Format(pTime0->Time, TempTime);

  ConvertTime(Temp, Interval, Unit);
  Inc_Min(TempTime, Temp[0]);
  Inc_Hour(TempTime, Temp[1]);
  Inc_Day(TempTime, Temp[2]);
  Inc_Month(TempTime, Temp[3]);
  Inc_Year(TempTime, Temp[4]);

  Time_Aft_Format(TempTime, pTime1->Time);
  Set_STRUCT_Sum(pTime1, sizeof(S_HEX_Time), pTime1->CS, sizeof(pTime1->CS));
}
/*-----------------------------------------------
����:Timeʱ������ϼ��� Interval ��ʱ��ֵ,Interval�ĵ�λ��Unit
���:
Time,��Ҫת����ʱ��ֵ��ͬʱת���õ�ʱ��ֵҲ����Time��
Time[0]��,Time[1]��,Time[2]��,Time[3]ʱ,Time[4]��
����:��
------------------------------------------------*/
void Time_Dec(S_HEX_Time* pTime0, INT16U Interval, INT8U Unit, S_HEX_Time* pTime1)
{
  INT8U Re, Temp[5], TempTime[5];

  Re = Check_HEX_Time(pTime0);
  if(Re EQ 0)
    ASSERT_FAILED();

  if(sizeof(pTime1->Time) != 5)
    ASSERT_FAILED();
  
  Time_Pre_Format(pTime0->Time, TempTime); 

  ConvertTime(Temp, Interval, Unit);
  Dec_Min(TempTime, Temp[0]);
  Dec_Hour(TempTime, Temp[1]);
  Dec_Day(TempTime, Temp[2]);
  Dec_Month(TempTime, Temp[3]);
  Dec_Year(TempTime, Temp[4]);

  Time_Aft_Format(TempTime, pTime1->Time);
  Set_STRUCT_Sum(pTime1, sizeof(S_HEX_Time), pTime1->CS, sizeof(pTime1->CS));
}
//�ж�ʱ�����ȷ��
INT8U _Check_HEX_Time(INT8U Time[])
{
  if(Time[T_MIN] < 60 && Time[T_HOUR] < 24 && \
     Time[T_DATE] > 0 && Time[T_DATE] < 32 && \
     Time[T_MONTH] > 0 && Time[T_MONTH] < 13 && \
     Time[T_YEAR] <= 99)
  {
    return 1;
  }
  else
  {
    //ASSERT(0);
    return 0;
  }
}

//�ж�ʱ�����ȷ��
INT8U _Check_BCD_Time(INT8U Time[])
{
  if(Check_BCD_Data(Time, 5) EQ 0)
  {
    return 0;
  }

  if(Time[T_MIN] < 0x60 && Time[T_HOUR] < 0x24 && \
     Time[T_DATE] > 0 && Time[T_DATE] < 0x32 && \
     Time[T_MONTH] > 0 && Time[T_MONTH] < 0x13 && \
     Time[T_YEAR] <= 0x99)
  {
    return 1;
  }
  else
  {
    //ASSERT(0);
    return 0;
  }
}

//���һ��S_HEX_Time�����Ƿ���ȷ
INT8U Check_HEX_Time(S_HEX_Time* pTime)
{
  if(Check_STRUCT_Sum(pTime, sizeof(S_HEX_Time), pTime->CS, sizeof(pTime->CS)))
  {
    if(_Check_HEX_Time(pTime->Time))
    {
      return 1;
    }
  }
  
  ASSERT_FAILED();
  return 0;
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
//���һ��S_BCD_Time�����Ƿ���ȷ
INT8U Check_BCD_Time(S_BCD_Time* pTime)
{
  if(Check_STRUCT_Sum(pTime, sizeof(S_BCD_Time), pTime->CS, sizeof(pTime->CS)) EQ 1 && Check_BCD_Data(pTime, S_OFF(S_BCD_Time, CS)) EQ 1)
  {
    if(pTime->Sec < 0x60 && pTime->Min < 0x60 && pTime->Hour < 0x24 && \
       pTime->Date > 0x00 && pTime->Date < 0x32 && \
       pTime->Month > 0x00 && pTime->Month < 0x13 && \
       pTime->Year <= 0x99 && pTime->Week < 7)
    {
      return 1;
    }
  }
  return 0;
}

//��ȡBCDʱ��
//Dst[0]��
//Dst[1]ʱ
//Dst[2]��
//Dst[3]��
//Dst[4]��
void Get_BCD_Time(S_BCD_Time* pSrc, INT8U Dst[], INT8U Dst_Start[], INT8U DstLen)
{
  if(!(Dst >= Dst_Start && Dst + 5 <= Dst_Start + DstLen))
    ASSERT_FAILED();

  Dst[T_MIN] = pSrc->Min;
  Dst[T_HOUR] = pSrc->Hour;
  Dst[T_DATE] = pSrc->Date;
  Dst[T_MONTH] = pSrc->Month;
  Dst[T_YEAR] = pSrc->Year;
}

//����ʱ��ıȽϣ�Time0��Time1��ʱ��ĳ���ΪLen
//ע��:������С��λ������ǰ,���λ�����ں�,�����롢�֡�ʱ���ա��¡��� 
INT8U Cmp_Array_Time(INT8U Time0[], INT8U Time1[], INT8U Len)
{
  INT8U i;
  
  if(Len > 6)
    ASSERT_FAILED();
   
  for(i = 0; i < Len; i++)
  {
    if(Time0[Len - 1 - i] > Time1[Len - 1 - i])
    {
      return TIME_AFT;
    }
    else if(Time0[Len - 1 - i] < Time1[Len - 1 - i])
    {
      return TIME_BEF;
    }
    else
    {
      continue;
    }
  }
  return TIME_EQU;
   
}

//ʱ��ȽϺ���,����TIME_EQU��ʾ��ʱ�����
//����TIME_AFT��ʾpTime1��pTime2֮��
//����TIME_BEF��ʾpTime1��pTime2֮ǰ
INT8U Cmp_Time(S_HEX_Time* pTime1, S_HEX_Time* pTime2)
{
  INT8U Re;

  Re = Check_HEX_Time(pTime1);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  Re = Check_HEX_Time(pTime2);
  if(Re EQ 0)
    ASSERT_FAILED();

  Re = Cmp_Array_Time(pTime1->Time, pTime2->Time, 5);
  return Re;
}

//û�ж��Ե�ʱ��ȽϺ����������ڷ��ʷ�����ʱ��Ƚ�
INT8U _Cmp_Time(S_HEX_Time* pTime1, S_HEX_Time* pTime2)
{
  return Cmp_Array_Time(pTime1->Time, pTime2->Time, 5);
}

//��ӡʮ������ʱ��
void Print_HEX_Time(S_HEX_Time* pTime)
{
  OS_Debug_Print("%d-%d-%d %d:%d",\
  pTime->Time[T_YEAR], pTime->Time[T_MONTH],\
  pTime->Time[T_DATE], pTime->Time[T_HOUR],\
  pTime->Time[T_MIN]);
}

//��ӡBCDʱ��
void Print_BCD_Time(S_BCD_Time* pTime)
{
  OS_Debug_Print("%x-%x-%x %x:%x",\
  pTime->Year, pTime->Month,\
  pTime->Date, pTime->Hour, pTime->Min);
}

/******************************************************************************************
*     1. imput: bcd-bcd data                *
*      output:hex data                  *
*******************************************************************************************/
INT8U OB_H(INT8U bcd)
{
  return ((bcd & 0xf0) >> 4) * 10 + (bcd & 0x0f);
}
/******************************************************************************************/

/******************************************************************************************
*     1. use year and month cal numbers of day              *
*     2.                      *
*******************************************************************************************/  
INT8U CalDay(INT8U year, INT8U month) //hex
{
  INT8U result;
  volatile INT8U secondmonth;

  result = 0x00;
  if(!(year % 4))
  {
    secondmonth = 29;
  }
  else
  {
    secondmonth = 28;
  }
  if(month > 12)
  {
    month -= 12;
  }
  switch(month)
  {
    case 0x01:
    case 0x03:
    case 0x05:
    case 0x07:
    case 0x08:
    case 0x0A:
    case 0x0C:
      result = 31; break;
    case 0x04:
    case 0x06:
    case 0x09:
    case 0x0B:
      result = 30; break;
    case 0x02:
      result = secondmonth; break;
  }
  return result;
}

/******************************************************************************************
*     1. cal two time diffenrce,1>2 [��]���¡�                 *
*     2. ruturn second                      *
*******************************************************************************************/

INT32S ComTime(INT8U* t1, INT8U* t2)
{
  INT8U i, j, flag;
  INT32S data1, data2;
  INT32S result;
  INT8U t11[6], t22[6];

  data1 = data2 = 0;
  if(*(t1 + 0) > *(t2 + 0))
  {
    flag = 0;
  }
  else if(*(t2 + 0) > *(t1 + 0))
  {
    flag = 0xff;
  }
  else if(*(t1 + 1) > *(t2 + 1))
  {
    flag = 0;
  }
  else if(*(t2 + 1) > *(t1 + 1))
  {
    flag = 0xff;
  }
  else if(*(t1 + 2) > *(t2 + 2))
  {
    flag = 0;
  }
  else if(*(t2 + 2) > *(t1 + 2))
  {
    flag = 0xff;
  }
  else if(*(t1 + 3) > *(t2 + 3))
  {
    flag = 0;
  }
  else if(*(t2 + 3) > *(t1 + 3))
  {
    flag = 0xff;
  }
  else if(*(t1 + 4) > *(t2 + 4))
  {
    flag = 0;
  }
  else if(*(t2 + 4) > *(t1 + 4))
  {
    flag = 0xff;
  }

  if(!flag)
  {
    for(i = 0; i < 6; i++)
    {
      *(t11 + i) = OB_H(*(t1 + i));
      *(t22 + i) = OB_H(*(t2 + i));
    }
  }
  else
  {
    for(i = 0; i < 6; i++)
    {
      *(t11 + i) = OB_H(*(t2 + i));
      *(t22 + i) = OB_H(*(t1 + i));
    }
  }

  for(i = 1; i < *(t22 + 1); i++)
  {
    data2 += CalDay(*(t22 + 0), i);
  }
  data2 += *(t22 + 2);

  for(i = *(t22 + 0); i < *(t11 + 0); i++)
  {
    for(j = 1; j <= 12; j++)
    {
      data1 += CalDay(i, j);
    }
  }

  for(i = 1; i < *(t11 + 1); i++)
  {
    data1 += CalDay(*(t11 + 0), i);
  }
  data1 += *(t11 + 2);

  if(!flag)
  {
    result = data1 - data2;
  }
  else
  {
    result = data2 - data1;
  }

  result = result * 86400l + OB_H(*(t1 + 3)) * 3600l - OB_H(*(t2 + 3)) * 3600l + OB_H(*(t1 + 4)) * 60l - OB_H(*(t2 + 4)) * 60l + OB_H(*(t1 + 5)) - OB_H(*(t2 + 5));
  return result;
}

CONST INT8U WeekTab[] =
{
  //���������ڱ�
  (3 << 5) + 31,//1��
  (6 << 5) + 29,//2��
  (0 << 5) + 31,//3��
  (3 << 5) + 30,//4��
  (5 << 5) + 31,//5��
  (1 << 5) + 30,//6��
  (3 << 5) + 31,//7��
  (6 << 5) + 31,//8��
  (1 << 5) + 30,//9��
  (4 << 5) + 31,//10��
  (0 << 5) + 30,//11��
  (2 << 5) + 31 //12��

};

/*------------------------------------------------------------------------------
----------
        2000��~2099�������㷨
--------------------------------------------------------------------------------
---------*/
INT8U Week(INT8U y, INT8U m, INT8U d)
{
  INT8U week, day;
  day = WeekTab[m - 1];//�±�
  week = day >> 5;//��������
  day &= 0x1f;//������
  if((m < 3) && (y & 0x03))
  {
    //ƽ��
    if(m EQ 2)
      day--;//ƽ��������
    week++;//ƽ���±�+1
  }
  y = y + (y >> 2);//��+��/4
  week = (week + y + d + 2) % 7;//(����=��+��/4+�±�+2��)%7
  //return (week << 5) | day;//�������ں�������
  return week;
}

/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
* Assumes input in normal date format, i.e. 1980-12-31 23:59:59
* => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
*
* [For the Julian calendar (which was used in Russia before 1917,
* Britain & colonies before 1752, anywhere else before 1582,
* and is still in use by some communities) leave out the
* -year/100+year/400 terms, and add 10.]
*
* This algorithm was first published by Gauss (I think).
*
* WARNING: this function will overflow on 2106-02-07 06:28:16 on
* machines were long is 32-bit! (However, as time_t is signed, we
* will already get problems at other places on 2038-01-19 03:14:08)
*/

INT32U mktime(const INT16U year0, const INT16U mon0, \
const INT16U day, const INT16U hour, \
const INT16U min, const INT16U sec)
{
  INT16U mon = mon0, year = year0;

  /* 1..12 -> 11,12,1..10 */
  if(0 >= (int) (mon -= 2))
  {
    mon += 12;    /* Puts Feb last since it has leap day */
    year -= 1;
  }

  return ((((INT32U) (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + day) + year * 365 - 719499) * 24 + hour /* now have hours */) * 60 + min /* now have minutes */) * 60 + sec; /* finally seconds */
}

/*
void main()
{
  //char wk[15]="��һ����������";
  int y,m,d,w;
  cin>>y>>m>>d;
  w=week(y,m,d);
  cout<<y<<"��"<<m<<"��"<<d<<"�� ����"<<wk[w*2]<<wk[w*2+1]<<endl;
}
*/
#undef TIME_C
