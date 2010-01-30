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

  //MEASU_INSTANT* p;//��ѹ��4λС��,VolStat_Para�еĵ�ѹ����Ҳ�Ѿ�ת��Ϊ��4λС��

  TRACE();
    
  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(Re EQ 1);
  
  if(Min_Bak.Var EQ 0xFF)//��һ�ν���ú�������Ҫ��1���Ӻ������Ӽ���
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];
  }

  //ÿ�����и�����
  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];
    
    if(VolStat_Count.Sec < 30) //û��30s����������
      return;
        
    DIS_PD_INT;//�ص����ж�
    
    /*
    for(i = 0; i < 3; i ++)
    {
      if(VolStat_Count.Exam_Upper[i] EQ 0 && VolStat_Count.Exam_Lower[i] EQ 0)
    
    }
    */
    
    for(i = 0; i < 4; i++)//����ֱ𿼺�
    {
      if(i EQ 1 && Get_SysParse_Mode() != PARSE_341)//331����²���B����п���
      {
        //��B��ͳ�������0
        Cur_VolStat.Total_Time[i] = 0;
        
        Cur_VolStat.Upper_Time[i] = 0;
        Cur_VolStat.Lower_Time[i] = 0;
        Cur_VolStat.Qual[i] = 0;

        continue;
      }
   
      //�÷����ڵ�ѹ�������ڿ��˷�Χ�ڲŽ���ͳ��
      if(VolStat_Count.Exam_Upper[i] EQ 0 && VolStat_Count.Exam_Lower[i] EQ 0)
      {
        //�÷�����û�з���һ�ε�ѹ����������Ҳû�з���һ�ε�ѹ����������
        //��������Ϊ��ѹ�ڿ��˷�Χ��
        Cur_VolStat.Total_Time[i]++;//�����ʱ��
        //Total_VolStat.Total_Time[i]++;//�ܼ��ʱ��

        if(0 != VolStat_Count.Qual_Upper[i] || \
           0 != VolStat_Count.Qual_Lower[i])//��ѹ���ϸ�
        {
          if(VolStat_Count.Qual_Upper[i] > VolStat_Count.Qual_Lower[i])//��ѹ����
          {
            Cur_VolStat.Upper_Time[i]++;
          }
          else
          {
            Cur_VolStat.Lower_Time[i]++;
          }
        }
      }
      
      //������൱�µ�ѹ�ϸ���
      if(Cur_VolStat.Total_Time[i] != 0 && \
         Cur_VolStat.Total_Time[i] > Cur_VolStat.Upper_Time[i] + Cur_VolStat.Lower_Time[i])
        Cur_VolStat.Qual[i] = (Cur_VolStat.Total_Time[i] - Cur_VolStat.Upper_Time[i] - Cur_VolStat.Lower_Time[i]) * 10000 / Cur_VolStat.Total_Time[i];
      else
        Cur_VolStat.Qual[i] = 0;
      
      Cur_VolStat.Exam[i] = 10000 - Cur_VolStat.Qual[i];
    }


    SET_STRUCT_SUM(Cur_VolStat);
    //SET_STRUCT_SUM(Total_VolStat);
    //ÿ���ӹ�ȥ���÷����ڵ�ͳ��������0
    Clear_VolStat_Count_Ram();
    EN_PD_INT;//�������ж�
  } 
  
}

void VolStat_Sec_Proc()
{
  INT8U i, Re;
  INT32U Volt;

  static S_Int32U Sec_Bak = {CHK_BYTE, 0xFFFFFFFF, CHK_BYTE};

  MEASU_INSTANT* p;//��ѹ��4λС��,VolStat_Para�еĵ�ѹ����Ҳ�Ѿ�ת��Ϊ��4λС��
  
  TRACE();
  
  Re = CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(Re EQ 1);

  //ÿ��Ƚ�һ�µ�ǰ��ѹֵ
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
    p = (MEASU_INSTANT *) &Measu_InstantData_ToPub_PUCK;//˲ʱ������
    
    for(i = 0; i < 3; i ++)
    {
      if(i EQ 0)
        Volt = p -> Volt.A/VOL_RATIO;  
      else if(i EQ 1)
      {
        //B������ֻ�����������߲Ž��е�ѹͳ��
        if(Get_SysParse_Mode() != PARSE_341)
          continue;
        
        Volt = p -> Volt.B/VOL_RATIO;
      }
      else
        Volt = p -> Volt.C/VOL_RATIO;
      
//-----------��ǰ�Ƿ��ڿ��˷�Χ��?�����������һ�ദ��-------------
      if(Volt > VolStat_Para.Exam_Upper_Limit)//��ѹԽ��������
      {
        VolStat_Count.Exam_Upper[i] ++;
        VolStat_Count.Exam_Upper[3] ++; //��Խ�������޽����ۼ�
        continue;             //���ڿ��˷�Χ�ڲ���������Ĵ���
      }
      else if(Volt < VolStat_Para.Exam_Lower_Limit)//��ѹԽ��������
      {
        VolStat_Count.Exam_Lower[i] ++;
        VolStat_Count.Exam_Lower[3] ++; //��Խ�������޽����ۼ�
        continue;            //���ڿ��˷�Χ�ڲ���������Ĵ���
      }
      
      if(Volt > VolStat_Para.Qual_Upper_Limit)//��ѹԽ�ϸ�����
      {
        VolStat_Count.Qual_Upper[i] ++;
        VolStat_Count.Qual_Upper[3] ++; //�ܳ��ϸ������ۼ�
      }
      else if(Volt < VolStat_Para.Qual_Lower_Limit)//��ѹԽ�ϸ�����
      {
        VolStat_Count.Qual_Lower[i] ++;
        VolStat_Count.Qual_Lower[3] ++; //�ܳ��ϸ������ۼ�
      }
      
//-----------------------------------------------------------------
      
      DIS_PD_INT;
      //////////�ж��������͵�ѹ////////////////////////
      if(Volt > Cur_VolStat.Max_Vol[3])//�ܵ���ߵ�ѹ
      {
        Cur_VolStat.Max_Vol[3] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Max_Vol_Time[3], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Max_Vol_Time[3], sizeof(Cur_VolStat.Max_Vol_Time[3]));
        SET_STRUCT_SUM(Cur_VolStat);
      }
      else if(Cur_VolStat.Min_Vol[3] EQ 0 || Volt < Cur_VolStat.Min_Vol[3])//�ܵ���͵�ѹ
      {
        Cur_VolStat.Min_Vol[3] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Min_Vol_Time[3], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Min_Vol_Time[3], sizeof(Cur_VolStat.Min_Vol_Time[3]));
        SET_STRUCT_SUM(Cur_VolStat);      
      }
      
      if(Volt > Cur_VolStat.Max_Vol[i])//������ߵ�ѹ
      {
        Cur_VolStat.Max_Vol[i] = Volt;
        mem_cpy((INT8U *)Cur_VolStat.Max_Vol_Time[i], (INT8U *)&Cur_Time0.Time, 5,\
                 (INT8U *)Cur_VolStat.Max_Vol_Time[i], sizeof(Cur_VolStat.Max_Vol_Time[i]));
        SET_STRUCT_SUM(Cur_VolStat);
      }
      else if(Cur_VolStat.Min_Vol[i] EQ 0 || Volt < Cur_VolStat.Min_Vol[i])//������͵�ѹ
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

//��ѹͳ�ƴ������
void VolStat_Proc()
{
  VolStat_Min_Proc();
  VolStat_Sec_Proc();
}

//�뵱�µ�ѹͳ������
void Set_Def_Cur_VolStat_Data()
{
  //����ʼ����д��洢����  
  Debug_Print("Set Def Cur VolStat Data");
  Clear_Cur_VolStat_Ram();


  Save_Cur_VolStat_Data();
  Save_Cur_VolStat_PD_Data();
}

//����Ĭ�ϵĵ�ѹͳ������
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

//���浱ǰ��ѹͳ������
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

//���浱ǰ��ѹͳ������
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

//���浱ǰ��ѹͳ������
//�˺�����Ϊ�ǵ���洢�����û����ʱ����
void PowerDown_Save_VolStat_Data()
{
  Write_Storage_Data(_SDI_CUR_VOLSTAT, (void *) (&Cur_VolStat), sizeof(Cur_VolStat));
  //Write_Storage_Data(_SDI_TOTAL_VOLSTAT, (void *) (&Total_VolStat), sizeof(Total_VolStat));
}

//����ѹͳ�������Ƿ���ȷ
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

//��ROM�ж�ȡ��ѹͳ������
void Read_VolStat_Data_From_Rom()
{
  S_VolStat* p;

  //�ȶ�ȡ����洢������
  //�ٶ���ͨ����
  //����ǰ��ѹ�������
  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  p = (S_VolStat *) Pub_Buf0;

  if(Read_Storage_Data(_SDI_CUR_VOLSTAT_PD, p, p, sizeof(Pub_Buf0))\
     != sizeof(Cur_VolStat) || Check_VolStat_Data(p) != 1)
  {
    Debug_Print("Read _SDI_CUR_VOLSTAT_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(_SDI_CUR_VOLSTAT, p, p, sizeof(Pub_Buf0))\
       != sizeof(Cur_VolStat) || Check_VolStat_Data(p) != 1)//�ò�����Ĭ�ϲ�����,ʵ���ϲ���������������
    {
      Debug_Print("Read _SDI_CUR_VOLSTAT data error");
      //������еı��������ݶ�û����������Ϊ�ǵ�һ���ϵ磬������0
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

//����ѹͳ����ز����ĺϷ���
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

//����ѹͳ��������ݵĺϷ���
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


//���ѹͳ������
void Clear_VolStat_Data()
{
  Debug_Print("Clear_VolStat_Data!!!");  
  Set_Def_Cur_VolStat_Data();
}

//���VolStat_Count���ڴ�����
void Clear_VolStat_Count_Ram()
{
  mem_set((void *) &VolStat_Count, 0, sizeof(VolStat_Count), (void *) &VolStat_Count, sizeof(VolStat_Count));
  INIT_STRUCT_VAR(VolStat_Count);
  SET_STRUCT_SUM(VolStat_Count);
}

//��ĳ��ĵ�ѹͳ������
INT8U Clear_Phase_VolStat_Data(S_VolStat *p, INT8U Phase)
{
  if(Phase > 3)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  p -> Total_Time[Phase] = 0;//��������ʱ��,3��ʾ��,0-2�ֱ��ʾA��B��C���࣬
  p -> Upper_Time[Phase] = 0;//����ʱ��
  p -> Lower_Time[Phase] = 0;//����ʱ��
  
  p -> Qual[Phase] = 0;//����ϸ���
  p -> Exam[Phase] = 0;//������
  
  p -> Max_Vol[Phase] = 0;//��ߵ�ѹ
  mem_set((void *)(p -> Max_Vol_Time[Phase]), 0, sizeof(p -> Max_Vol_Time[Phase]),\
        (void *)(p -> Max_Vol_Time[Phase]), sizeof(p -> Max_Vol_Time[Phase]));//ʱ�䣬16������
  
  p -> Min_Vol[Phase] = 0;//��͵�ѹ
  mem_set((void *)(p -> Min_Vol_Time[Phase]), 0, sizeof(p -> Min_Vol_Time[Phase]), \
        (void *)(p -> Min_Vol_Time[Phase]), sizeof(p -> Min_Vol_Time[Phase])); //ʱ�䣬16������
  
  //SET_STRUCT_SUM(Cur_VolStat);  
  OS_Set_STRUCT_Sum(p, sizeof(S_VolStat), p -> CS, sizeof(p -> CS));
  
  return 1;
}

//���ܻ�ĳ���ѹͳ������
INT8U Clear_Proto_Phase_VolStat_Data(PROTO_DI PDI)
{
  INT16U Len;
  STORA_DI SDI;
  INT8U i, j;
  S_VolStat *p;

  if(((PDI >> 8) & 0xFF) EQ 0)
    i = 3; //��
  else //1-3�ֱ��ʾA��B��C����
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

//�����ǰ��ѹͳ���ڴ�����
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


//����ǰ��ѹͳ�����ݶ��ᣬpTime���붳��ʱ�̣�һ����ǵ�ǰʱ��
void Settle_VolStat_Data(S_HEX_Time *pTime)
{
  INT8U Re;
  S_HEX_Time TempTime;
  INT8U Err;
  
  Debug_Print("----------Freeze VolStat Data %d-%d-%d %d:%d----------",\
  pTime->Time[T_YEAR],pTime->Time[T_MONTH],pTime->Time[T_DATE],pTime->Time[T_HOUR],pTime->Time[T_MIN]);
  
  //Cur_VolStat����ʱ���ʽ����ȷ�Ļ������ж���
  if((Cur_VolStat.Time.Time[T_YEAR]==0 && Cur_VolStat.Time.Time[T_MONTH]==0) ||\
  Check_HEX_Time((S_HEX_Time *)&(Cur_VolStat.Time))==0)
  {
  Debug_Print("----------Freeze VolStat Data End----------");
  return;
  }
  //<=pTime�����һ������ʱ���
  Get_Last_Freeze_Time(pTime,&TempTime);//pTime��ǰ�����һ������ʱ���,����pTime����
  //����TempTime�������һ�εĶ���ʱ���
  Re=Cmp_Time(&(Cur_VolStat.Time),&TempTime);//�Ƚ����ݶ���ʱ��������һ�ζ���ʱ���
  if(TIME_AFT==Re)//����ʱ��������һ�ν���ʱ���֮����һ����ǰ���ݣ�����Ҫ���浽��ʷ������
  {
  Debug_Print("----------Freeze VolStat Data End----------");
  return;
  }
  //��һ����ʷ����
  //>=p->Time�����һ������ʱ���
  Get_Next_Freeze_Time(&(Cur_VolStat.Time),&TempTime);//��ʷ���ݵĶ���ʱ��� 
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);//����Pub_Buf0�ź���
  //����û�ж�����������ж���
  if(Read_HIS_Data(HIS_VOLSTAT_DATA,&TempTime,(void *)Pub_Buf0,(void *)Pub_Buf0,sizeof(Pub_Buf0),&Err)==0)
  {
  Write_HIS_Data(HIS_VOLSTAT_DATA,(S_HEX_Time *)&(Cur_VolStat.Time),(void *)&Cur_VolStat,sizeof(Cur_VolStat));
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);//�ͷ�Pub_Buf0�ź���  
  //��Ϊ����ʷ���ݣ�������Ҫ���ñ�Ϊ��������
  //�嵱�µ�ѹͳ������
  mem_set((void *)&Cur_VolStat,0,sizeof(Cur_VolStat),(void *)&Cur_VolStat,sizeof(Cur_VolStat));//������ȫ����0���뵱ǰ�洢�����´ζ���ȫ0���ݣ���ʾ��δ����������
  
  INIT_STRUCT_VAR(Cur_VolStat);
  SET_DATA_READY_FLAG(Cur_VolStat);   
  SET_STRUCT_SUM(Cur_VolStat);
  
  //���´洢������  
  Save_Cur_VolStat_PD_Data();
  Save_Cur_VolStat_Data();
  Debug_Print("----------Freeze VolStat Data End----------");
}
*/

//��ʼ����ѹͳ�Ʋ���
void Init_VolStat_Ram_Para()
{
  Clear_VolStat_Count_Ram();
}
#undef VOLSTAT_C

