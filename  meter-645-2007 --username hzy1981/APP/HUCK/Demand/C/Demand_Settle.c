#define DEMAND_SETTLE_C
#include "Includes.h"

//���DI�Ƿ���һ���洢�������ݵ�DI
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

//��ȡĳ����ʷ�����Ķ���ʱ��
//SDI��ʾ��ʷ���ݵĴ洢DI
//pDst��ʾĿ�껺����
//pDst_Start��ʾĿ�껺�����Ŀ�ʼ
//DstLenĿ�껺�����ĳ���
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

//��ȡ������������
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


//��ȡĳ����ʷ������ĳ�����ʵ�����
//SDI��ʾ�����Ĵ洢DI
//Rate��ʾ����,0��ʾ��
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ������ݵĳ���
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

//д�������ݵ�ʱ��
//DI��ʾ�����Ĵ洢DI
//pTime��ʾд���ʱ��
void Write_Demand_Time(STORA_DI SDI, S_HEX_Time* pTime)
{
  INT8U Re; 

  TRACE();

  //ʱ�������ȫ0��Ĭ�����ݵ����
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

//д������������
//pSrc��ʾ��������������
//SrcLen��ʾ���ݳ���
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
//д����ĳ�����ʵ�����
//SDI��ʾ�������ݴ洢DI
//Rate��ʾ����
//pSrc��ʾд���ݵ���ʼ
//SrcLen��ʾԴ���ݵĳ���
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

//��ȡ���һ�������������ݵĴ洢SDI
STORA_DI Read_Last_Settle_Demand_DI()
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  Len = Read_Storage_Data(_SDI_LAST_SETTLE_DEMAND_DI, &Last_SDI, &Last_SDI, sizeof(Last_SDI)); 
  //������DI�Ƿ���ȷ?
  if(sizeof(Last_SDI) != Len || \
     Last_SDI < _SDI_SETTLE_DEMAND_DATA || \
     Last_SDI >= _SDI_SETTLE_DEMAND_DATA + MAX_DEMAND_SETTLE_NUM)//���������д�
  {
    ASSERT_FAILED(); 
    Last_SDI = _SDI_SETTLE_DEMAND_DATA;
  }
  return Last_SDI;
}

//д���һ�������������ݵĴ洢DI
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

//������ʷ��������ΪȫFF����Ч���ݣ��ڷǵ�һ�������ս���ʱ��Ҫ������
void Set_Demand_His_Invalid_Data(STORA_DI His_DI)
{
  INT8U i;
  //INT16U Len; 

  TRACE();

  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 

  mem_set((INT8U *)Pub_Buf0, 0xFF, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
  Write_Demand_Phase_Data(His_DI, (INT8U *)Pub_Buf0, DEMAND_PHASE_DATA_SIZE);

  //д���Լ��ַ�������
  for(i = 0; i <= MAX_RATES; i ++)
  {
    Write_Demand_Rate_Data(His_DI, i, (INT8U *)Pub_Buf0, sizeof(S_One_Demand));
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);  
  
}

//����ǰ�洢�����������ݴ洢����ʷ����His_DI��
void Save_Cur_Demand_To_His_Data(STORA_DI His_DI)
{
  INT8U i, Re;
  INT16U Len; 

  TRACE();

  Re = Check_Demand_Stora_DI(His_DI);
  ASSERT(Re EQ 1);

  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 

  //д������������ 
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

  //д���Լ��ַ�������
  for(i = 0; i <= MAX_RATES; i ++)
  {
    //�ȶ�ȡ��ǰ���������������ݣ�Ȼ��洢����ʷ������
    Len = Read_Demand_Rate_Data(_SDI_CUR_DEMAND, i, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)); 
    if(sizeof(S_One_Demand) != Len)
    {
      ASSERT_FAILED();
      //��ȡ������
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

//��ȡ��ʷ������������
INT16U Read_His_Demand_Time_Data(INT8U Bef_Counts, S_HEX_Time * pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  if(Bef_Counts EQ 0)//��ȡ��������
  {
    //mem_cpy(pDst, (void *) &Cur_Demand.Phase_Demand[0], DEMAND_PHASE_DATA_SIZE, pDst_Start, DstLen); 
    //return DEMAND_PHASE_DATA_SIZE;
    ASSERT_FAILED();
    return 0;
  }
  else//��ȡ��ʷ����
  {
    Last_SDI = Read_Last_Settle_Demand_DI(); //��ȡ���һ�������Ĵ洢DI

    Last_SDI = Last_SDI - Bef_Counts + 1; //��ǰ׷��Bef_Counts�������
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

//��ȡ��ʷ������������
INT16U Read_His_Demand_Phase_Data(INT8U Bef_Counts, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  if(Bef_Counts EQ 0)//��ȡ��������
  {
    mem_cpy(pDst, (void *) &Cur_Demand.Phase_Demand[0], DEMAND_PHASE_DATA_SIZE, pDst_Start, DstLen); 
    //return DEMAND_PHASE_DATA_SIZE;
  }
  else//��ȡ��ʷ����
  {
    Last_SDI = Read_Last_Settle_Demand_DI(); //��ȡ���һ�������Ĵ洢DI

    Last_SDI = Last_SDI - Bef_Counts + 1; //��ǰ׷��Bef_Counts�������
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


//��ȡǰ���µ�ĳ������������
//Bef_Counts��ʾǰ�������������, 0��ʾ��ǰ����
//Rate��ʾ����
//pDst��ʾĿ�껺����
//pDst_Start��DstLenһ�����Ʒ������ݳ���
INT16U Read_His_Demand_Rate_Data(INT8U Bef_Counts, INT8U Rate, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len; 
  STORA_DI Last_SDI; 

  TRACE();

  if(Bef_Counts EQ 0)//��ȡ��������
  {
    //�ܺ͵�ǰ���ʵ����ݷ����ڴ���
    if(Rate EQ 0)//0��ʾ��
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
  else//��ȡ��ʷ����
  {
    Last_SDI = Read_Last_Settle_Demand_DI(); //��ȡ���һ�������Ĵ洢DI

    Last_SDI = Last_SDI - Bef_Counts + 1; //��ǰ׷��Bef_Counts�������
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


//�����ڴ��е���������
void Reset_Demand_Ram_Data()
{
  INT8U i;
  
  //����ʼ����д��洢����  
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
  
  Cur_Demand.Rate = 1;//Cur_Rate_Info.Rate; //��ǰ��������,Cur_Rate_Info���ܻ�û�г�ʼ����
  
  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);

  SET_STRUCT_SUM(Cur_Demand);
  EN_PD_INT;
  
  Clr_Demand_Accu(); //�������ۼӵ�Ԫ
  
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

//����ROM�е���������
void Reset_Demand_Rom_Data(STORA_DI SDI, S_HEX_Time* pTime)//��յ�ǰ����������
{
  //S_HEX_Time TempTime;
  INT8U Re, i;


  TRACE();

  Re = Check_HEX_Time(pTime);
  ASSERT(Re EQ 1);

  //�����ʱ����,ʱ�������0,��������������Ĺ�����,��������쳣��λ,���ᵼ�½���0�����ݽ���
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

  //д��������
  Write_Demand_Phase_Data(SDI, (INT8U *)Pub_Buf0, DEMAND_PHASE_DATA_SIZE);

  //д���Լ��ַ�������
  for(i = 0; i <= MAX_RATES; i ++)
  {
    Write_Demand_Rate_Data(SDI, i, (INT8U *)Pub_Buf0, sizeof(S_One_Demand));
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);

  //��дʱ����
  Re = Write_Storage_Data_Fix_Len(SDI, DEMAND_TIME_DATA_OFF, pTime, sizeof(S_HEX_Time)); 
  if(Re != 1)
  {
    ASSERT_FAILED();
  }
}

/*---�ú���Ϊ�޸������������㣬�Լ��ǵ�һ��������FF֮ǰ�ĺ���
//������������, pTime���Ƕ���ʱ���
//pTimeΪ����ʱ���ĵ�һ������ʱ����ߵ�ǰ����ʱ��
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
    
  //��ȡ���һ�ν������ݵĴ洢DI
  Last_SDI = Read_Last_Settle_Demand_DI();
  
  //��ȡ��ǰ�������ݵĽ���ʱ���
  //Get_Last_Settle_Time(pTime, &TempTime, &TempTime, sizeof(TempTime));   
  //Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime)); 
  //����ʱ����ڵ�ǰʱ����Ժ�,��˵����ǰ�������ݵĽ���ʱ���δ��,�������
  if(Cmp_Time(pTime, (S_HEX_Time *)&Cur_Time0) EQ TIME_AFT)
  {
    Debug_Print("Cur Demand Time, no settle");
    return;
  }
   
  //ǰһ����������ˣ����ٽ��㣬��ֹ��������ϵ����ϵ�
  Read_Demand_Time(Last_SDI, &TempTime, &TempTime,sizeof(TempTime));
  if(memcmp(&TempTime, pTime, sizeof(TempTime)) EQ 0)
  {
    Debug_Print("Same as Last settle time!");    
    return;
  }
 
  Get_N_Last_Settle_Time(MAX_ENERGY_SETTLE_NUM, (S_HEX_Time *)(&Cur_Time0), &TempTime, &TempTime, sizeof(TempTime));
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
  //--------------------------  
    Save_Cur_Demand_Data();//���ڴ��е��������ݱ��浽 ROM�еĵ�ǰ������
    mem_cpy(&TempTime, pTime, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
    //������������ʱ��
    INC_DEMAND_SETTLE_DI(Last_SDI);  
    Write_Demand_Time(Last_SDI, &TempTime); 
    Save_Cur_Demand_To_His_Data(Last_SDI);//����ǰ���������������ݴ洢��Last_DI�洢��
    Write_Last_Settle_Demand_DI(Last_SDI);//����Last_DI��_SDI_LAST_SETTLE_DEMAND_DI
  
    for(i = 0; i < MAX_DEMAND_SETTLE_NUM; i ++)
    {
      INC_DEMAND_SETTLE_DI(Last_SDI);//����Last_DI
  
      Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime)); 
      
      Debug_Print("Settle Reset Demand Data, Time:");
      Print_HEX_Time((S_HEX_Time *) &TempTime);
      
      if(Cmp_Time(&TempTime, (S_HEX_Time *)&Cur_Time0) != TIME_AFT)
      {
        Debug_Print("--not the settle SDI, reset rom--");
        Reset_Demand_Rom_Data(Last_SDI, &TempTime);
        Write_Last_Settle_Demand_DI(Last_SDI);//����Last_DI��_SDI_LAST_SETTLE_DEMAND_DI
      }
      else
        break;
    }
  }
  
  //���µ�ǰ��������������,ͬʱ����������ʱ��Ϊ��ǰ����
  mem_cpy(&TempTime, (S_HEX_Time *)&Cur_Time0, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
  Set_Def_Cur_Demand_Data(&TempTime); //�������������  
}
*/
extern void _mem_cpy(INT8U *pDst, INT8U *pSrc, INT16U SrcLen, INT8U *pDst_Start, INT16U DstLen);
//Flagλ0��ʾ��0��1��ʾ��������
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
        else //if(Flag > 1) //�ǵ�һ�����գ������ó�FF
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

//������������, pTime���Ƕ���ʱ���
//pTimeΪ����ʱ���ĵ�һ������ʱ����ߵ�ǰ����ʱ��
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
    
  //��ȡ���һ�ν������ݵĴ洢DI
  Last_SDI = Read_Last_Settle_Demand_DI();

  //ǰһ����������ˣ����ٽ��㣬��ֹ��������ϵ����ϵ�
  Read_Demand_Time(Last_SDI, &TempTime, &TempTime,sizeof(TempTime));
  if(memcmp(&TempTime, pTime, sizeof(TempTime)) EQ 0)
  {
    Debug_Print("Same as Last settle time!");    
    return;
  }
 
  //�ǵ�һ�������գ��������������
  if(Settle_Time.Time_D_H[0][0] EQ Cur_Time1.Hour && Settle_Time.Time_D_H[0][1] EQ Cur_Time1.Date)
  {
    //--------------------------  
    Save_Cur_Demand_Data();//���ڴ��е��������ݱ��浽 ROM�еĵ�ǰ������
    Settle_Demand_FF_Data(0x01);
    //������������ʱ��
    INC_DEMAND_SETTLE_DI(Last_SDI);  
    Write_Demand_Time(Last_SDI, pTime); 
    Save_Cur_Demand_To_His_Data(Last_SDI);//����ǰ���������������ݴ洢��Last_DI�洢��
    
    //���µ�ǰ��������������,ͬʱ����������ʱ��Ϊ��ǰ����
    //mem_cpy(&TempTime, (S_HEX_Time *)&Cur_Time0, sizeof(S_HEX_Time), &TempTime, sizeof(TempTime));
    Set_Def_Cur_Demand_Data(pTime); //�������������
    //Flag = 0x01;
  }
  else //���ǵ�һ�����գ���������ΪFF
  {
    Settle_Demand_FF_Data(0x02);
    Debug_Print("Not the first settle day!");
    INC_DEMAND_SETTLE_DI(Last_SDI);     
    Set_Demand_His_Invalid_Data(Last_SDI);
    //Flag = 0x02;
  }
  
  Write_Last_Settle_Demand_DI(Last_SDI);//����Last_DI��_SDI_LAST_SETTLE_DEMAND_DI 
  
}

//�ϵ粹����������
void PowerOn_Settle_Demand_Data()
{
  S_HEX_Time TempTime;
  
  TRACE();

  //���Hex_PD_Time�����ǽ���ʱ��㣬��Ӧ��ʹָ֮����һ�������
  if(Check_HEX_Time((S_HEX_Time *) &Hex_PD_Time))
  {  
    Get_Next_Settle_Time((S_HEX_Time *) &Hex_PD_Time, &TempTime, &TempTime, sizeof(TempTime));
    Settle_Demand_Data((S_HEX_Time *) &TempTime);
  }
}
#undef DEMAND_SETTLE_C
