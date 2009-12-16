#define VOLSTAT_SETTLE_C
#include <includes.h>

//������ʷ�������������͵�ѹͳ�����ݵĴ洢DI
//��Ϊһ�㶼�Ǵ洢��N�µ����ݣ����Դ洢�������Ǹ������������ɵ�
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

//��ȡǰ�����µ���ʷ���ݵ�DI
//Data_Flag���ݱ�־
//HIS_ENERGY_DATA;
//HIS_DEMAND_DATA;
//HIS_VOLSTAT_DATA;
//Bef_Monthǰ������
//�������ݵĴ洢DI
STORA_DI Calc_His_VolStat_Data_DI_Bef_Month(INT8U Bef_Month)
{
  S_HEX_Time Temp_Time;
  Time_Dec((S_HEX_Time *) &Cur_Time0, Bef_Month, UNIT_MON, (S_HEX_Time *) &Temp_Time);//��ʱ����ǰ����Bef_Mon����
  return Calc_His_VolStat_Data_DI(&Temp_Time);
}

//��ȡǰ���ε���ʷ��������
//Bef_Counts, ��ʾ��ǰ����, 0��ʾ��ȡ��ǰ����
//pDst��ʾĿ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س��ȵķ�Χ
//pErr����0ʱ��ʾ������ʾ����ԭ��
INT16U Read_His_VolStat_Data(INT8U Bef_Counts, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  STORA_DI Last_SDI;
  INT16U Len;

  if(Bef_Counts > 0)//����ʷ����
  {
    Last_SDI = Read_Last_Settle_VolStat_DI();

    Last_SDI = Last_SDI - Bef_Counts + 1;//��ǰ׷��Bef_Counts�������
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
  else//����ǰ����
  {
    mem_cpy(pDst, (void *) &Cur_VolStat, sizeof(Cur_VolStat), pDst_Start, DstLen);
    //return sizeof(Cur_Energy);
  }
  return sizeof(Cur_VolStat);
}

//���pTime�Ƿ��ǵ�ѹͳ�ƽ���ʱ��
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

//д��ʷ������ѹͳ�Ƶ�����,д������ʷ��������Write_Demand_His_VolStat_Data�����е������� 
//pTime��������ѹͳ�Ƶ����ݵĴ洢ʱ��
//pSrcд���ݻ�����
//SrcLen���ݳ���
//����ֵ
//����NO_ERR��ʾд�ɹ�
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

  Len = Get_Storage_Data_Len(SDI); //���ݳ���
  //���ݳ��ȱ��������ڲ����涨��Χ��
  if(Len != SrcLen)
  {
    ASSERT_FAILED();
    return 0;
  }

  //д�洢����
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

//���pSrcʱ���֮ǰ�����һ����ѹͳ�ƽ���ʱ���,��Ϊÿ�µ�1��0ʱ0��Ϊ����ʱ��
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
//���pSrcʱ���֮������һ����ѹͳ�ƽ���ʱ���,��Ϊÿ�µ�1��0ʱ0��Ϊ����ʱ��
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
  //������DI�Ƿ���ȷ?
  if(sizeof(Last_SDI) != Len || \
     Last_SDI < _SDI_SETTLE_VOLSTAT_DATA || \
     Last_SDI >= _SDI_SETTLE_VOLSTAT_DATA + MAX_VOLSTAT_SETTLE_NUM)//���������д�
  {
    ASSERT_FAILED();
    Last_SDI = _SDI_SETTLE_VOLSTAT_DATA;
  }
  return Last_SDI;
}

//����ǰ��ѹͳ�����ݶ��ᣬpTime���붳��ʱ�̣�һ����ǵ�ǰʱ��
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
  
  //��ȡ���һ�ν������ݵĴ洢DI
  Last_SDI = Read_Last_Settle_VolStat_DI();

  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  //ǰһ����������ˣ����ٽ��㣬��ֹ��������ϵ����ϵ�
  Read_Storage_Data(Last_SDI, (INT8U *)Pub_Buf, (INT8U *)Pub_Buf,sizeof(Pub_Buf));
  if(memcmp(pTime, &(((S_VolStat *)Pub_Buf) -> Time), sizeof(S_HEX_Time)) != 0)
  {
    //�ǵ�һ�������գ��������������
    mem_cpy((INT8U *)&Cur_VolStat.Time, pTime, sizeof(S_HEX_Time), (INT8U *)&Cur_VolStat.Time, sizeof(Cur_VolStat.Time));
    SET_STRUCT_SUM(Cur_VolStat);
    
    INC_VOLSTAT_SETTLE_DI(Last_SDI);     
    Write_Storage_Data(Last_SDI, (void *) &Cur_VolStat, sizeof(Cur_VolStat));
    Write_Storage_Data(_SDI_LAST_SETTLE_VOLSTAT_DI, &Last_SDI, sizeof(Last_SDI));
      
    mem_set((void *) &Cur_VolStat, 0, sizeof(Cur_VolStat), \
            (void *) &Cur_VolStat, sizeof(Cur_VolStat));//������ȫ����0���뵱ǰ�洢�����´ζ���ȫ0���ݣ���ʾ��δ����������
    
    INIT_STRUCT_VAR(Cur_VolStat);
    SET_DATA_READY_FLAG(Cur_VolStat);   
    SET_STRUCT_SUM(Cur_VolStat);    
    //���´洢������  
    Save_Cur_VolStat_PD_Data();
    Save_Cur_VolStat_Data();
  }
  else
  {
    Debug_Print("Same as Last settle time!");      
  }
  
  OS_Mutex_Post(PUB_BUF_SEM_ID);   
 
}

//�ϵ粹����ѹͳ������
void PowerOn_Settle_VolStat_Data()
{
  Settle_VolStat_Data((S_HEX_Time *) &Cur_Time0);
}
#undef VOLSTAT_SETTLE_C