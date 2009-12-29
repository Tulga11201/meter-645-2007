#define ENERGY_PROTO_C
#include "Includes.h"

//��ȡ���޹����������
void Read_Energy_Comb_Word()
{
  INT16U Len;
  
  TRACE();
  //��ȡ�й����������
  Len = Read_Storage_Data(SDI_ACTIVE_COMB_WORD, (INT8U *) &Energy_Comb_Word.Active,\
						  (INT8U *) &Energy_Comb_Word.Active, sizeof(Energy_Comb_Word.Active)); 
  if(Len != 1)
  {
    ASSERT_FAILED();
    Energy_Comb_Word.Active = Def_04000601_3[0];
  }

  //��ȡ�޹����1������
  Len = Read_Storage_Data(SDI_REACTIVE_COMB_WORD_1, (INT8U *) &Energy_Comb_Word.Reactive[0],\
						  (INT8U *) &Energy_Comb_Word.Reactive[0], sizeof(Energy_Comb_Word.Reactive[0]));
  if(Len != 1)
  {
    ASSERT_FAILED();
    Energy_Comb_Word.Reactive[0] = Def_04000601_3[1];
  }

  //��ȡ�޹����2������
  Len = Read_Storage_Data(SDI_REACTIVE_COMB_WORD_2, (INT8U *) &Energy_Comb_Word.Reactive[1],\
						  (INT8U *) &Energy_Comb_Word.Reactive[1], sizeof(Energy_Comb_Word.Reactive[1]));
  if(Len != 1)
  {
    ASSERT_FAILED();
    Energy_Comb_Word.Reactive[1] = Def_04000601_3[2];
  }

  INIT_STRUCT_VAR(Energy_Comb_Word);
  SET_STRUCT_SUM(Energy_Comb_Word);
}

/*
typedef struct  
{
  //��������
  S_Energy Base;

  //���������
  INT32U Comb_Active[MAX_RATES+1];  //����й�

  INT32S Comb_Reactive1[MAX_RATES+1]; //����޹�1
  INT32S Comb_Reactive2[MAX_RATES+1]; //����޹�2

  INT32U Pos_Apparent[MAX_RATES+1]; //��������
  INT32U Neg_Apparent[MAX_RATES+1]; //��������

  //�����������
  INT32U Phase_Comb_Active[3][MAX_RATES+1];  //����й�

  INT32S Phase_Comb_Reactive1[3][MAX_RATES+1]; //����޹�1
  INT32S Phase_Comb_Reactive2[3][MAX_RATES+1]; //����޹�2

  INT32U Phase_Pos_Apparent[3][MAX_RATES+1]; //��������
  INT32U Phase_Neg_Apparent[3][MAX_RATES+1]; //��������
}S_Comb_Energy;//��ϵ��ܽṹ��

 */
//����һ��S_Comb_Energy�ṹ������е�������޹�����
//����õ�������Ȼ���ڸû����������
void Calc_Comb_Energy(S_Comb_Energy* p)
{
  INT16U i, j;
  INT8U* p0;

  TRACE();

  i = 0;

  p0 = (INT8U *) p + sizeof(p -> Base);
  while((p0 + i) < ((INT8U *) p + sizeof(S_Comb_Energy)))
  {
    *(p0 + i) = 0;
    i ++;
  }
  
  ///////////��������й�//////////////////////
  if(GET_BIT(Energy_Comb_Word.Active, 0))//�����й�+
  {
    p -> Comb_Month_Active += p -> Base.Prepaid_Info.Month_Pos_Act;
    p -> Comb_Last_Month_Active += p -> Base.Prepaid_Info.Last_Month_Pos_Act;
    
    for(i = 0; i <= MAX_RATES; i ++)//�ַܷ���
      p->Comb_Active[i] += p->Base.Pos_Active[i];

    for(i = 0; i < 3; i ++) //����
      p->Phase_Comb_Active[i] += p->Base.Phase_Pos_Active[i];
  }
  else if(GET_BIT(Energy_Comb_Word.Active, 1))//�����й�-
  {
    p -> Comb_Month_Active -= p -> Base.Prepaid_Info.Month_Pos_Act; 
    p -> Comb_Last_Month_Active -= p -> Base.Prepaid_Info.Last_Month_Pos_Act; 
    
    for(i = 0; i <= MAX_RATES; i ++)//�ַܷ���
      p->Comb_Active[i] -= p->Base.Pos_Active[i]; 

    for(i = 0; i < 3; i ++) //����
      p->Phase_Comb_Active[i] -= p->Base.Phase_Pos_Active[i];
  }

  if(GET_BIT(Energy_Comb_Word.Active, 2))//�����й�+
  {
    p -> Comb_Month_Active += p -> Base.Prepaid_Info.Month_Neg_Act;
    p -> Comb_Last_Month_Active += p -> Base.Prepaid_Info.Last_Month_Neg_Act;
    
    for(i = 0; i <= MAX_RATES; i ++)//�ַܷ���
      p->Comb_Active[i] += p->Base.Neg_Active[i];

    for(i = 0; i < 3; i ++) //����
      p->Phase_Comb_Active[i] += p->Base.Phase_Neg_Active[i];
  }
  else if(GET_BIT(Energy_Comb_Word.Active, 3))//�����й�-
  {
    p -> Comb_Month_Active -= p -> Base.Prepaid_Info.Month_Neg_Act;
    p -> Comb_Last_Month_Active -= p -> Base.Prepaid_Info.Last_Month_Neg_Act;
    
    for(i = 0; i <= MAX_RATES; i ++)//�ַܷ���
      p->Comb_Active[i] -= p->Base.Neg_Active[i]; 

    for(i = 0; i < 3; i ++) //����
      p->Phase_Comb_Active[i] -= p->Base.Phase_Neg_Active[i];
  }
  ////////////��������޹�/////////////////////////
  for(i = 0; i < 4; i ++)//��4�����޹��ֱ����
  {
    ///////////����޹�1/////////////////
    if(GET_BIT(Energy_Comb_Word.Reactive[0], i * 2))//������+
    {
      for(j = 0; j <= MAX_RATES; j ++)//�ַܷ���
        p->Comb_Reactive1[j] += p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive1[j] += p->Base.Phase_Quad_Reactive[j][i];
    }
    else if(GET_BIT(Energy_Comb_Word.Reactive[0], i * 2 + 1))//������-
    {
      for(j = 0; j <= MAX_RATES; j ++)//�ַܷ���
        p->Comb_Reactive1[j] -= p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive1[j] -= p->Base.Phase_Quad_Reactive[j][i];
    }
    //////////////����޹�2//////////
    if(GET_BIT(Energy_Comb_Word.Reactive[1], i * 2))//������+
    {
      for(j = 0; j <= MAX_RATES; j ++)//�ַܷ���
        p->Comb_Reactive2[j] += p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive2[j] += p->Base.Phase_Quad_Reactive[j][i];
    }
    else if(GET_BIT(Energy_Comb_Word.Reactive[1], i * 2 + 1))//������-
    {
      for(j = 0; j <= MAX_RATES; j ++)//�ַܷ���
        p->Comb_Reactive2[j] -= p->Base.Quad_Reactive[i][j]; 

      for(j = 0; j < 3; j ++)
        p->Phase_Comb_Reactive2[j] -= p->Base.Phase_Quad_Reactive[j][i];
    }
  }
  
  //�����й������������򣬼���Ҫ��
  if(NEG_ADD_POS_ACT_EN > 0)
  {
    for(i = 0; i <= MAX_RATES; i ++)//�ַܷ���
      p->Base.Pos_Active[i] += p->Base.Neg_Active[i];
  }  
}

//��ȡ��������
//PDI��ʾЭ��DI
//pDstĿ�껺����
//pDst_StartĿ�껺������ʼ��ַ
//DstLenĿ�껺������󳤶�
INT16U _Get_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT8U* p, Index;
  INT8U Bef_Counts, Data_Len, Rate;
  INT16U Len;
  INT8U Temp, Src_Type;
  INT32U Off, U_Data;
  INT32S S_Data;
  INT8U FF_Flag;
  
  TRACE();

  if(!(pDst >= pDst_Start && pDst + 4 <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  
  FF_Flag = 0;
  if((PDI & 0xFF) EQ 0xFF && BYTE_2(PDI) <= 0x0A) //��ȡ��N�����������ݿ�
  {
    FF_Flag = 1;
    PDI = PDI & 0xFFFFFF00;
  }
  
  Bef_Counts = (INT8U) (PDI & 0x0000000F);//ǰ��������������?  
  
  Temp = (INT8U) ((PDI & 0x00FF0000) >> 16);
  if(Temp EQ 0x0B) //��ȡ���ǵ�ǰ����һ�������ڵ�����й����ۼ��õ���
  {
    mem_cpy((INT8U *)Pub_Buf, (INT8U *)&Cur_Energy, sizeof(Cur_Energy), (INT8U *)Pub_Buf, sizeof(Pub_Buf));
  }
  else
  {
    Len = Read_His_Energy_Data(Bef_Counts, (INT8U *)Pub_Buf, (INT8U *)Pub_Buf, sizeof(Pub_Buf));
    if(Len != sizeof(S_Energy))
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  
  p = (INT8U *)Pub_Buf;

  ASSERT(sizeof(Pub_Buf) > sizeof(S_Comb_Energy));
  Calc_Comb_Energy((S_Comb_Energy *) p); //��������ϵ���

  Off = 0;

  if(Temp EQ 0)    //����й�
  {
    Off = S_OFF(S_Comb_Energy, Comb_Active[0]);
  }
  else if(Temp EQ 1)    //�����й�
  {
    Off = S_OFF(S_Comb_Energy, Base.Pos_Active[0]);
  }
  else if(Temp EQ 2)    //�����й�
  {
    Off = S_OFF(S_Comb_Energy, Base.Neg_Active[0]);
  }
  else if(Temp EQ 3)    //����޹�1
  {
    Off = S_OFF(S_Comb_Energy, Comb_Reactive1[0]);
  }
  else if(Temp EQ 4)    //����޹�2
  {
    Off = S_OFF(S_Comb_Energy, Comb_Reactive2[0]);
  }
  else if((Temp >= 5) && (Temp <= 8))  //�������޹�
  {
    Off = S_OFF(S_Comb_Energy, Base.Quad_Reactive[Temp - 5][0]);
  }
  else if(Temp EQ 9)    //��������
  {
    Off = S_OFF(S_Comb_Energy, Base.Pos_Apparent[0]);
  }
  else if(Temp EQ 0x0A) //��������
  {
    Off = S_OFF(S_Comb_Energy, Base.Neg_Apparent[0]);
  }
  else if(Temp EQ 0x0B)
  {
    if(Bef_Counts EQ 0)
      Off = S_OFF(S_Comb_Energy, Comb_Month_Active);
    else
      Off = S_OFF(S_Comb_Energy, Comb_Last_Month_Active);
  }
  else if(((Temp >= 0x15) && (Temp <= 0x1E)) || \
          ((Temp >= 0x29) && (Temp <= 0x32)) || \
          ((Temp >= 0x3D) && (Temp <= 0x46)))
  {
    if((Temp >= 0x15) && (Temp <= 0x1E)) //A��
    {
      Index = 0;
      Temp = Temp - 0x15;
    }
    else if((Temp >= 0x29) && (Temp <= 0x32))//B��
    {
      Index = 1;
      Temp = Temp - 0x29;
    }
    else  //C��
    {
      Index = 2;
      Temp = Temp - 0x3D;
    }

    if(Temp EQ 0) //�����й�
      Off = S_OFF(S_Comb_Energy, Base.Phase_Pos_Active[Index]);
    else if(Temp EQ 1) //�����й�
      Off = S_OFF(S_Comb_Energy, Base.Phase_Neg_Active[Index]);
    else if(Temp EQ 2) //����޹�1
      Off = S_OFF(S_Comb_Energy, Phase_Comb_Reactive1[Index]);
    else if(Temp EQ 3) //����޹�2
      Off = S_OFF(S_Comb_Energy, Phase_Comb_Reactive2[Index]);
    else if((Temp >= 4) && (Temp <= 7)) //һ�����޹�
      Off = S_OFF(S_Comb_Energy, Base.Phase_Quad_Reactive[Index][Temp - 4]);
    else if(Temp EQ 8) //��������
      Off = S_OFF(S_Comb_Energy, Base.Phase_Pos_Apparent[Index]);
    else if(Temp EQ 9) //��������
      Off = S_OFF(S_Comb_Energy, Base.Phase_Neg_Apparent[Index]);
    else
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  else if(Temp EQ 0xEE) //��������ʱ��
  {
    Hex2Bcd_Buf((INT8U *)&(((S_Comb_Energy *) p) -> Base.Time), 5, pDst, pDst_Start, DstLen);
    return 5;
  }

  Rate = (INT8U)((PDI & 0x0000FF00) >> 8);
  if((Data_Flag & FOR_EVENT) != FOR_EVENT && Rate > Multi_Rate_Para.Rates)
    return 0;
  
  Off += Rate * 4; //����ƫ��
  p += Off;

  Src_Type = Get_DLT645_Data_Src_Type(PDI);

  if((Data_Flag & FOR_DISP) EQ FOR_DISP)//������������ʾ�Ļ���5���ֽ�
    Data_Len = 5;
  else
    Data_Len = 4;

  if(Src_Type EQ S_INTS)
  {
    S_Data = *(INT32S *) p;

    if((Data_Flag & FOR_SRC) EQ FOR_SRC)//��ȡԴ����
      mem_cpy(pDst, &S_Data, 4, pDst_Start, DstLen);
    else//��ȡBCD����
    {
      if((Data_Flag & FOR_DISP) != FOR_DISP)//����������ʾ�Ļ�������Ҫ/10
        S_Data = S_Data / 10; //Դ������3λС����Э��������2λС���������Ҫ/10 
      else //������ʾ
      {
        if(EnergDisBit EQ 4)
          S_Data = S_Data * 10 / (INT32S)Pow_10x(4 - EnergDisBit);
        else if(EnergDisBit <= 3) //��������ʾС��λ�������������
          S_Data = S_Data / (INT32S)(Pow_10x(4 - EnergDisBit) / 10);
        else
        {
          S_Data = S_Data / 10;
          ASSERT_FAILED();
        }
      }
      S_Hex2Bcd(S_Data, pDst, Data_Len, pDst_Start, DstLen);
    }
  }
  else if(Src_Type EQ S_INTU)
  {
    U_Data = *(INT32U *) p;

    if((Data_Flag & FOR_SRC) EQ FOR_SRC)//��ȡԴ����
      mem_cpy(pDst, &U_Data, 4, pDst_Start, DstLen);
    else//��ȡBCD����
    {
      if((Data_Flag & FOR_DISP) != FOR_DISP)//����������ʾ�Ļ�������Ҫ/10
        U_Data = U_Data / 10; //Դ������3λС����Э��������2λС���������Ҫ/10  
      else //������ʾ
      {
        if(EnergDisBit EQ 4)
          U_Data = U_Data * 10 / Pow_10x(4 - EnergDisBit);
        else if(EnergDisBit <= 3) //��������ʾС��λ�������������
          U_Data = U_Data /(Pow_10x(4 - EnergDisBit) / 10);
        else
        {
          U_Data = U_Data / 10;
          ASSERT_FAILED();
        }
      }      
      Hex2Bcd(U_Data, pDst, Data_Len, pDst_Start, DstLen);
    }
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }
  
  if(FF_Flag EQ 1)//
  {
    //PDI = EH_DI(0x00000000) + BYTE_2(PDI);
    Len = Read_Storage_Data(EH_DI(0x00000000) + BYTE_2(PDI), (INT8U *)Pub_Buf, (INT8U *)Pub_Buf, sizeof(Pub_Buf)); 
    if(Len > 0)
    {
      mem_cpy(pDst + 4, (INT8U *)Pub_Buf + ((INT32U)BYTE_1(PDI))*MAX_ENERGY_SETTLE_NUM*4, \
              MAX_ENERGY_SETTLE_NUM*4, pDst_Start, DstLen);
      return (MAX_ENERGY_SETTLE_NUM + 1) * 4;
    }
    else
      return 0;
  }  
  
  return Data_Len;
}

//��ȡ������Э������
INT16U Get_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len;
  
  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  Len = _Get_Energy_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
  OS_Mutex_Post(PUB_BUF_SEM_ID);
  
  return Len;
}

//��ȡԤ��������
INT16U Get_Prepaid_Energy_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT32U U_Data;
  INT8U Data_Len;
  INT16U Index;
  
  Index = Get_P_Data_Index(PDI);
  if(Index EQ NULL_2BYTES)
    return 0;
  
  U_Data = 0;
  mem_cpy(&U_Data, (INT8U *)P_Data_Info[Index].pSrc, 4, &U_Data, sizeof(U_Data));
  //U_Data = P_Data_Info[Index].; //ʣ�����

  if((Data_Flag & FOR_DISP) EQ FOR_DISP)//������������ʾ�Ļ���5���ֽ�
    Data_Len = 5;
  else
    Data_Len = 4;
  
  if((Data_Flag & FOR_SRC) EQ FOR_SRC)//��ȡԴ����
    mem_cpy(pDst, &U_Data, 4, pDst_Start, DstLen);
  else//��ȡBCD����
  {
    if((Data_Flag & FOR_DISP) != FOR_DISP)//����������ʾ�Ļ�������Ҫ/10
      U_Data = U_Data / 10; //Դ������3λС����Э��������2λС���������Ҫ/10  
    else //������ʾ
    {
      if(EnergDisBit EQ 4)
        U_Data = U_Data * 10 / Pow_10x(4 - EnergDisBit);
      else if(EnergDisBit <= 3) //��������ʾС��λ�������������
        U_Data = U_Data /(Pow_10x(4 - EnergDisBit) / 10);
      else
      {
        U_Data = U_Data / 10;
        ASSERT_FAILED();
      }
    }      
    Hex2Bcd(U_Data, pDst, Data_Len, pDst_Start, DstLen);
  }  
  
  return Data_Len;
}

//��ȡ��������
INT16U Get_Rate_Info_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT16U Len;
/*
#define PDI_CUR_RATE_SCHEME         0x0E010000//��ǰ��ʱ������
#define PDI_CUR_YEAR_PERIOD         0x0E010001//��ǰ��ʱ����
#define PDI_CUR_DATE_TABLE_SCHEME   0x0E010002 //��ǰ��ʱ�α���
#define PDI_CUR_DATE_TABLE          0x0E010003 //��ǰ��ʱ�α��
#define PDI_CUR_DATE_PERIOD         0x0E010004 //��ǰ��ʱ�κ�
#define PDI_CUR_RATE                0x0E010005 //��ǰ����
*/  
  Len = 1;
  if(PDI EQ 0x0E010000)
    *pDst = (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?1:2;
  else if(PDI EQ 0x0E010001)
    Hex2Bcd(Cur_Rate_Info.Year_Period, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010002)
    *pDst = (Cur_Rate_Info.Date_Scheme EQ DATE_SCHEME0)?1:2;
  else if(PDI EQ 0x0E010003)
    Hex2Bcd(Cur_Rate_Info.Date_Table, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010004)
    Hex2Bcd(Cur_Rate_Info.Date_Period, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010005)
    Hex2Bcd(Cur_Rate_Info.Rate, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E010006)
  {
    if(Cur_Rate_Info.Date_Flag EQ NORMAL_DAY)
      *pDst = 0;
    else if(Cur_Rate_Info.Date_Flag EQ WEEK_REST_DAY)
      *pDst = 1;
    else if(Cur_Rate_Info.Date_Flag EQ HOLIDAY)
      *pDst = 2;
  }
  else if(PDI EQ 0x0E010007) //��ǰԤ���ѷ�ʽ,������Ϊ0�������Ϊ1
    *pDst = (PREPAID_MODE EQ ENERGY_MODE)?0:1;
  else if(PDI EQ 0x0E010008) //��ǰ�۷ѷ�ʽ,��ʱΪ0������Ϊ1
    *pDst = (PREPAID_MONEY_MODE EQ PREPAID_RATE)?0:1;
  else if(PDI EQ 0x0E010009) //��ǰ��ʱ���ʷ���
    *pDst = (Cur_Rate_Info.Rate_Scheme EQ RATE_SCHEME0)?1:2;
  else if(PDI EQ 0x0E01000A) //��ǰ��ʱ���
  {
    Hex2Bcd(Rate_Scheme_Para.Fee[Cur_Rate_Info.Rate - 1], pDst, 4, pDst_Start, DstLen);
    Len = 4;
  }
  else if(PDI EQ 0x0E01000B) //��ǰ���ݷ���
    *pDst = PREPAID_STEP_SCHEME;
  else if(PDI EQ 0x0E01000C) //��ǰ���ݺ�
    Hex2Bcd(PREPAID_STEP_NO, pDst, 1, pDst_Start, DstLen);
  else if(PDI EQ 0x0E01000D) //��ǰ���ݵ���
  {
    if(Cur_Rate_Info.Step_No EQ 0)
      Hex2Bcd(0, pDst, 4, pDst_Start, DstLen);
    else
      Hex2Bcd(Step_Scheme_Para.Step_Energy[Cur_Rate_Info.Step_No - 1], pDst, 4, pDst_Start, DstLen);
    
    Len = 4;    
  }
  else if(PDI EQ 0x0E01000E || PDI EQ 0x0280000B) //��ǰ���ݵ��
  {
    Hex2Bcd(Step_Scheme_Para.Step_Fee[Cur_Rate_Info.Step_No], pDst, 4, pDst_Start, DstLen);
    Len = 4;    
  }  
  else if(PDI EQ 0x0E01000F) //���½����ܵ���
  {
    Hex2Bcd(Cur_Energy.Prepaid_Info.Month_Pos_Act / 10, pDst, 4, pDst_Start, DstLen);
    Len = 4;
  }
  else if(PDI EQ 0x0E010010) //Ԥ������բ�ز忨��־,0��ʾû�в壬1��ʾ�в�
  {
    *pDst = Get_Card_Switch_On_Flag(); 
    Len = 1;    
  }
  else if(PDI EQ 0x0E010011) //����բ״̬��ԭ��
  {
    *pDst = Relay_Status.Switch_Cause; 
    *(pDst + 1) = Relay_Status.Switch_Status;
    Len = 2;
  }
  else if(PDI EQ 0x0E010012)//Զ�̿��������״̬
  {
    mem_cpy(pDst, (INT8U *)&Remote_Ctrl_Switch, 21, pDst_Start, DstLen);
    Len = 21;
  }
  else if(PDI >= PDI_CUR_RATE1_FEE && PDI < PDI_CUR_RATE1_FEE + MAX_RATES) //��ǰ���ʵ��
  {
    Hex2Bcd(Rate_Scheme_Para.Fee[PDI - PDI_CUR_RATE1_FEE], pDst, 4, pDst_Start, DstLen);
    Len = 4;
  }
  else if(PDI >= PDI_CUR_STEP1_ENG && PDI < PDI_CUR_STEP1_ENG + PREPAID_MAX_STEP) //��ǰ���ݵ���
  {
    Hex2Bcd(Step_Scheme_Para.Step_Energy[PDI - PDI_CUR_STEP1_ENG], pDst, 4, pDst_Start, DstLen);
    Len = 4;    
  }
  else if(PDI >= PDI_CUR_STEP1_FEE && PDI < PDI_CUR_STEP1_FEE + PREPAID_MAX_STEP + 1) //��ǰ���ݵ��
  {
    Hex2Bcd(Step_Scheme_Para.Step_Fee[PDI - PDI_CUR_STEP1_FEE], pDst, 4, pDst_Start, DstLen);
    Len = 4;     
  }
  else 
    Len = 0;
  
  return Len;
}

//��ȡԤ�����¼���¼����
INT16U Get_Prepaid_Event_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len;
  INT8U Index;

  INT16U Off;

  TRACE();

  Index = (INT8U)((PDI & 0x00FF00) >> 8);
  
  if(Index EQ 1)
  {
    Off = 0;
    Len = 5;
  }
  else if(Index EQ 2)
  {
    Off = 5;
    Len = 2;
  }
  else if(Index EQ 3)
  {
    Off = 7;
    Len = 4;
  }
  else if(Index EQ 4)
  {
    Off = 11;
    Len = 4;
  }
  else if(Index EQ 5)
  {
    Off = 15;
    Len = 4;
  }
  else if(Index EQ 6)
  {
    Off = 19;
    Len = 4;
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  //ע�⣺�����Get_Event_Separate_Proto_Data�����ڿ�����Ҫ�õ�Pub_Buf0������
  //�����ڴ˴������õ�����˲�����ɳ�ͻ
  Len = Get_Event_Separate_Proto_Data((PDI & 0xFFFF00FF) | 0x0100, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    return 0;
  }

  mem_cpy(pDst, (INT8U *) Pub_Buf0 + Off, Len, pDst_Start, DstLen);
  
  return Len;  
}
                                     
//���ó�ʼ����
INT8U Set_Energy_Start(PROTO_DI PDI,INT8U *pSrc, INT16U SrcLen)
{
  INT32U *p;
  INT8U i;
  INT32U Sum;
  INT32U Data;
  
  if(Check_Meter_Factory_Status() EQ 0) //�ǹ���״̬���������ó�ʼ������
    return 0;
  
  if(SET_ENERGY_EN EQ 0)//���������ó�ʼ����
    return 0;
  else
  {
    //if(SrcLen != (MAX_RATES + 1)*4)
      //return 0;
    
    if(PDI EQ 0x0E000301)
      p = (INT32U *)Cur_Energy.Pos_Active;
    else if(PDI EQ 0x0E000302)
      p = (INT32U *)Cur_Energy.Neg_Active;
    else if(PDI EQ 0x0E000303)
      p = (INT32U *)Cur_Energy.Quad_Reactive[0];
    else if(PDI EQ 0x0E000304)
      p = (INT32U *)Cur_Energy.Quad_Reactive[1];
    else if(PDI EQ 0x0E000305)
      p = (INT32U *)Cur_Energy.Quad_Reactive[2];
    else if(PDI EQ 0x0E000306)
      p = (INT32U *)Cur_Energy.Quad_Reactive[3];
    else if(PDI EQ 0x0E000307)
      p = (INT32U *)Cur_Energy.Pos_Apparent;
    else if(PDI EQ 0x0E000308)
      p = (INT32U *)Cur_Energy.Neg_Apparent;
    else if(PDI EQ 0x0E000400) //����Ԥ���ѵ���,���ڲ���
    {
      Data = Bcd2Hex(pSrc, 4);
      return Prepaid_Buy_Energy_Proc(Data);
    }
    else if(PDI EQ 0x0E000401) //����Ԥ���ѵ��,���ڲ���
    {
      Data = Bcd2Hex(pSrc, 4);
      return Prepaid_Buy_Money_Proc(Data);
    }
    else if(PDI EQ 0x0E000402) //���õ����߹�����,���ڲ���
    {
       Cur_Energy.Prepaid_Info.Month_Pos_Act = Bcd2Hex(pSrc, 4)*10;
       SET_STRUCT_SUM(Cur_Energy);
       return 1;
    }
    else if(PDI EQ 0x0E000403) //��բ����²忨
    { 
       return Prepaid_Insert_Card(*pSrc); //�����û�����ʱ�忨��բ
    }
    else
    {
      ASSERT_FAILED();
      return 0;
    }
    
    Sum = 0;
    for(i = 1; i <= MAX_RATES; i ++)
    {
      Sum += Bcd2Hex(pSrc + i*4, 4)*10;
    }
  
    if(Sum != Bcd2Hex(pSrc, 4)*10)
      return 0;
    
    //SET_STRUCT_SUM(Cur_Energy);
    //if(Check_Energy_Data((S_Energy *)&Cur_Energy))
    //{
    Debug_Print("Set Start Energy------!!!!,PDI = 0x%lx, SrcLen = %d",PDI,SrcLen);
  
    Set_Event_Instant(ID_EVENT_SET_ENERG);
    //Wait_Event_Data_Proc_End(ID_EVENT_SET_ENERG);
    OS_Waitfor_Sec(Read_Event_Status(ID_EVENT_SET_ENERG) EQ 1, 3);//�ȴ�3s��û�д������򱨶��Դ���
    if(Read_Event_Status(ID_EVENT_SET_ENERG) EQ 0)
    {
      ASSERT_FAILED();
    }
    
    for(i = 0; i <= MAX_RATES; i ++)
    {
      *(p + i) = Bcd2Hex(pSrc + i*4, 4)*10;
    }
  
    SET_STRUCT_SUM(Cur_Energy);
    
    mem_cpy((void *)&Cur_Energy_Bak, (void *)&Cur_Energy, sizeof(Cur_Energy),\
            (void *)&Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
    Clr_Event_Instant(ID_EVENT_SET_ENERG);
    
    Save_Cur_Energy_PD_Data();
    Save_Cur_Energy_Data();
    Save_Cur_Energy_Bak0_Data();
    Save_Cur_Energy_Bak1_Data();
    Save_Cur_Energy_Bak2_Data();
    return 1;
  }
  //}

  //return 0;
}
#undef ENERGY_PROTO_C
