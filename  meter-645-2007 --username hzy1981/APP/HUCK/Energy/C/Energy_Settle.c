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

//���BCD�ķֺ�ʱ���ݸ�ʽ�Ƿ���ȷ?
//Time_D_H[0]��ʾ���ӣ�BCD��
//Time_D_H[1]��ʾСʱ��BCD��
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


//��ȡpSrcʱ�����ǰ(<pSrc)�����һ�������յ�pDst
//����н������򷵻�1��ͬʱ��������䵽pDst
//���û�н������򷵻�0
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
      //����pSrc�����ʱ���ÿ��������֮��Ĳ��С���Ǹ���������Ľ�����
      if(Temp >= Temp1)//����������pSrcʱ����
        Dec = Temp1 + (INT32U)31 * 24 * 60 - Temp;
      else
        Dec = Temp1 - Temp;

      if(Dec < Min)
      {
        Min = Dec;
        Index = i;
        //Month_Flag=1��ʾ��Ҫ����
        if(Temp >= Temp1)
          Month_Flag = 1;
        else
          Month_Flag = 0;
      }
    }
  }
  //Min!=0xFFFF��ʾ�ҵ����ϸ�������
  if(Min != 0xFFFF)
  {
    mem_cpy(pDst, pSrc, sizeof(S_HEX_Time), pDst, sizeof(S_HEX_Time));
    pDst -> Time[T_MIN] = 0;
    pDst -> Time[T_HOUR] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][0]);
    pDst -> Time[T_DATE] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][1]);
    Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst -> CS));
    if(Month_Flag == 1)//������ǰ��һ����
      Time_Dec(pDst, 1, UNIT_MON, pDst);
    return 1;
  }
  else
  {
    return 0;
  }
}

//��ȡpSrcʱ����Ժ�(>pSrc)�����һ�������յ�pDst
//�����ȡ���򷵻�1������ʱ��������pDstָ���ʱ����
//���û�л�ȡ���򷵻�0
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
      //����pSrc�����ʱ���ÿ��������֮��Ĳ��С���Ǹ���������Ľ�����
      if(Temp <= Temp1)//����������pSrcʱ���ǰ
        Dec = Temp + (INT32U)31 * 24 * 60 - Temp1;
      else
        Dec = Temp - Temp1;

      if(Dec < Min)
      {
        Min = Dec;
        Index = i;
        //Month_Flag=1��ʾ��Ҫ����
        if(Temp <= Temp1)
          Month_Flag = 1;
        else
          Month_Flag = 0;
      }
    }
  }
  //Min!=0xFFFF��ʾ�ҵ����¸�������
  if(Min != 0xFFFF)
  {
    mem_cpy(pDst, pSrc, sizeof(S_HEX_Time), pDst, sizeof(S_HEX_Time));
    pDst -> Time[T_MIN] = 0;
    pDst -> Time[T_HOUR] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][0]);
    pDst -> Time[T_DATE] = Bcd2Hex_Byte(Settle_Time.Time_D_H[Index][1]);
    Set_STRUCT_Sum(pDst, sizeof(S_HEX_Time), pDst -> CS, sizeof(pDst -> CS));
    if(Month_Flag == 1)//������ǰ��һ����
      Time_Inc(pDst, 1, UNIT_MON, pDst);
    return 1;
  }
  else
  {
    return 0;
  }
}


//��ȡpSrcʱ����ĵ�N��������ʱ��� 
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

//��ȡpSrcʱ����ĵ�N��������ʱ��� 
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
//�����ṹ��
typedef struct 
{
  //INT8U Time[5];//����ʱ���, ��ʱ���ڶ���ʱ����Ϊ����ʱ��
  S_HEX_Time Time;//����ʱ���, ��ʱ���ڶ���ʱ����Ϊ����ʱ��
  
  INT32U  Pos_Active[MAX_RATES+1];//���Լ��ַ��������й�, ��λС��, ��λKWh����ͬ
  INT32U  Neg_Active[MAX_RATES+1];//���Լ��ַ��ʷ����й�
  
  INT32U  Quad_Reactive[4][MAX_RATES+1];//�����޷ַ����޹�
  
  INT32U  Phase_Pos_Active[3];//���������й�
  INT32U  Phase_Neg_Active[3];//���෴���й�
  
  INT32U Phase_Quad_Reactive[3][4];
  
  INT32U  Phase_AH[3];//������AH
  
  INT32U  CopperLoss[4];//��ABCͭ��
  INT32U  IronLoss[4];  //��ABC����
  INT32U  TransErr[4];  //��ABC���������
  
  //INT32U  Phase_Reactive[3][4];//������������޹�
  
  INT8U   CS[CS_BYTES];//����Ĳ���Ҫ���浽Flash��
  
  //���²����Ǹ�������������ã�����Ҫ���浽Flash��EERom��
  //INT32U Pos_Reactive[MAX_RATES+1];//���Լ��ַ��������޹�
  //INT32U Neg_Reactive[MAX_RATES+1];
  
}S_Energy;

*/
//��ȡ���һ�������������ݵĴ洢DI
STORA_DI Read_Last_Settle_Energy_DI()
{
  INT16U Len;
  STORA_DI Last_SDI;

  Len = Read_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI));
  //������DI�Ƿ���ȷ?
  if(sizeof(Last_SDI) != Len || \
     Last_SDI < _SDI_SETTLE_ENERGY_DATA || \
     Last_SDI >= _SDI_SETTLE_ENERGY_DATA + MAX_ENERGY_SETTLE_NUM)//���������д�
  {
    ASSERT_FAILED();
    Last_SDI = _SDI_SETTLE_ENERGY_DATA;
  }
  return Last_SDI;
}
//��ȡǰ���ε���ʷ��������
//Bef_Counts, ��ʾ��ǰ����, 0��ʾ��ȡ��ǰ����
//pDst��ʾĿ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س��ȵķ�Χ
//pErr����0ʱ��ʾ������ʾ����ԭ��
INT16U Read_His_Energy_Data(INT8U Bef_Counts, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  STORA_DI Last_SDI;
  INT16U Len;

  if(Bef_Counts > 0)//����ʷ����
  {
    Last_SDI = Read_Last_Settle_Energy_DI();

    Last_SDI = Last_SDI - Bef_Counts + 1;//��ǰ׷��Bef_Counts�������
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
  else//����ǰ����
  {
    mem_cpy(pDst, (void *) &Cur_Energy, sizeof(Cur_Energy), pDst_Start, DstLen);
    //return sizeof(Cur_Energy);
  }
  return sizeof(Cur_Energy);
}
/*---------����������ϵ粹�����-----------
//�ϵ綳���������
//pTimeΪ����ʱ���ĵ�һ������ʱ����ߵ�ǰ����ʱ��,��pTime��ʼ������
//������ϵ����øú������ʾ�ϵ�ʱ��, ����ǽ����յ�����Ϊ��ǰ����ʱ���
void Settle_Energy_Data(S_HEX_Time* pTime)
{
  //INT16U Len;
  INT8U i;
  S_HEX_Time TempTime;
  //S_HEX_Time Settle_From_Time;
  STORA_DI Last_SDI, Bak_DI;

  Debug_Print("----------Settle Energy Data----------");

  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  //�ȶ�ȡ���һ�εĵ�����������
  Last_SDI = Read_Last_Settle_Energy_DI();
  Bak_DI = Last_SDI;
     
  if(Check_HEX_Time(pTime))
  {
    Debug_Print("Settle From Time:");
    Print_HEX_Time(pTime); 
    
    //��ǰʱ����ǰ��MAX_ENERGY_SETTLE_NUM��������
    Get_N_Last_Settle_Time(MAX_ENERGY_SETTLE_NUM, (S_HEX_Time *)(&Cur_Time0), &TempTime, &TempTime, sizeof(TempTime));
    //����TempTime���ڵ�ǰʱ���ǰMAX_ENERGY_SETTLE_NUM��������

    //pEnergy = (S_Energy *) Pub_Buf;
    //����ʱ����TempTime��ǰ��˵�����һ�����ݵ�ʱ�����ڵ�ǰʱ���ǰMAX_ENERGY_SETTLE_NUM����������ǰ
    //ȫ0��ʾĬ������

    //�����ʼ����ʱ����ǰ12����������ǰ,�򲻲�����
    if(Cmp_Time(pTime, &TempTime) EQ  TIME_BEF)
    {
      Debug_Print("Time Aft 12 Settle Days, No Settle");
      //Get_Last_Settle_Time((S_HEX_Time *)&Cur_Time0, &TempTime, &TempTime, sizeof(TempTime));
      //Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));  
      //TempTime��>=pTime�ĵ�һ������ʱ���,��������������н���
    }
    else
    {
      //�ϴν����ʱ����������һ�������һ�����տ�ʼ����,��ֹ��������ϵ����ϵ��ظ�����
      Read_Storage_Data(Last_SDI, (INT8U *) Pub_Buf, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
      if(memcmp(pTime, &(((S_Energy *)Pub_Buf) -> Time), sizeof(S_HEX_Time)) EQ 0)
      {
        Debug_Print("Same as Last settle time!");
        Get_Next_Settle_Time(pTime, &TempTime, &TempTime, sizeof(TempTime));
      }
      else
        mem_cpy((void *)&TempTime, (void *)pTime, sizeof(S_HEX_Time), (void *)&TempTime, sizeof(TempTime));
      
      //���pTime�ǵ���ʱ�䣬����Ҫ�������´����ҵ�>pTime�ĵ�һ������ʱ��
      //���pTime������ǽ���ʱ�䣬��ת����TempTime��������
      //Get_Last_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
      //Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
      
      //����TempTime����Ҫ��ʼ������Ŀ�ʼʱ���
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
  else//���һ�������������ݶ���������, ֱ�Ӱ�Last_DI�����
  {
    ASSERT_FAILED();
    //INC_ENERGY_SETTLE_DI(Last_SDI);
    //Write_Storage_Data(Last_SDI, (void *) &Cur_Energy, sizeof(Cur_Energy));
  }

  if(Bak_DI != Last_SDI)
  {
    Write_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &Last_SDI, sizeof(Last_SDI));
  }//�������һ�ε�DI
  
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

//Flagλ0��ʾ��0��1��ʾ����
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

//�ϵ綳���������----��������!!!!
//pTimeΪ����ʱ���ĵ�һ������ʱ����ߵ�ǰ����ʱ��,��pTime��ʼ������
//������ϵ����øú������ʾ�ϵ�ʱ��, ����ǽ����յ�����Ϊ��ǰ����ʱ���
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
  //�ȶ�ȡ���һ�εĵ�����������
  Last_SDI = Read_Last_Settle_Energy_DI();
  Settle_Flag = 0;   
  if(Check_HEX_Time(pTime))
  {
    Debug_Print("Settle Time:");
    Print_HEX_Time(pTime); 

    //�ϴν����ʱ����������һ�������һ�����տ�ʼ����,��ֹ��������ϵ����ϵ��ظ�����
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
//�ϵ�������ݵĶ��ᣬǰ��HIS_ENERGY_DATA_MONTHS����
void PowerOn_Settle_Energy_Data()
{
  S_HEX_Time TempTime;
  //���Hex_PD_Time�����ǽ���ʱ��㣬��Ӧ��ʹָ֮����һ�������
  if(Check_HEX_Time((S_HEX_Time *) &Hex_PD_Time))
  {
    Get_Next_Settle_Time((S_HEX_Time *) &Hex_PD_Time, &TempTime, &TempTime, sizeof(TempTime));
    Settle_Energy_Data((S_HEX_Time *) &TempTime);
  }
}
/*
//��ȡ��ʷ��������
//Bef_Counts��ʾǰ���ٴεĽ�������
//pDst��ʾĿ�껺����
//���ض�ȡ�������ݳ���
INT16U Get_Settle_Energy_Data(INT8U Bef_Counts, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  STORA_DI Last_SDI;
  INT8U Err;
  INT16U Len;
  
  Len=Read_Storage_Data(_DI_LAST_SETTLE_ENERGY_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI), &Err);
  //������DI�Ƿ���ȷ?
  if(sizeof(Last_SDI)!=Len ||\
  Last_SDI<_DI_SETTLE_ENERGY_DATA ||\
  Last_SDI>=_DI_SETTLE_ENERGY_DATA+MAX_ENERGY_SETTLE_NUM)//���������д�
  {
  ASSERT_FAILED();
  Last_SDI=_DI_SETTLE_ENERGY_DATA-1;
  }
  //Last_DI��ʱ��ʾ�ϸ����������ݴ洢��DI
  Last_SDI=(Last_SDI+MAX_ENERGY_SETTLE_NUM-Bef_Counts-1)%MAX_ENERGY_SETTLE_NUM;
  return Read_Storage_Data(Last_SDI, pDst, pDst_Start, DstLen, &Err);
}
*/
/*
//�����������, ����ǰ�������ݴ洢��������ʷ������
void Settle_Energy_Data()
{
   STORA_DI Last_SDI;
   INT8U Err;
   INT16U Len;

   Len=Read_Storage_Data(_DI_LAST_SETTLE_ENERGY_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI), &Err);
   //������DI�Ƿ���ȷ?
   if(sizeof(Last_SDI)!=Len ||\
   Last_SDI<_DI_SETTLE_ENERGY_DATA ||\
   Last_SDI>=_DI_SETTLE_ENERGY_DATA+MAX_ENERGY_SETTLE_NUM)//���������д�
   {
   ASSERT_FAILED();
   Last_SDI=_DI_SETTLE_ENERGY_DATA-1;
   }
   //Last_DI�Ǳ��ν�������Ӧ�ô洢��DI
   Last_SDI++;
   if(Last_SDI>=_DI_SETTLE_ENERGY_DATA+MAX_ENERGY_SETTLE_NUM)
   Last_SDI=_DI_SETTLE_ENERGY_DATA;

   Write_Storage_Data(Last_SDI, (void *)&Cur_Energy, sizeof(Cur_Energy));
   Write_Storage_Data(_DI_LAST_SETTLE_ENERGY_DI, &Last_SDI, sizeof(Last_SDI));
}
*/
#undef ENERGY_SETTLE_C