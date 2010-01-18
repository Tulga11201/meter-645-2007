#define LOAD_DATA_C
#include "Includes.h"

#define LOAD_DATA_SEARCH_NUM (60 / LOAD_DATA_INDEX_HOUR_NUM * LOAD_DATA_TYPE_NUM + 1) 

//#ifdef LOAD_DATA_C
CONST S_LoadData_Info LoadData_Info[] =
{
  //ģʽ��bit0
  {0x02010100,2,0},//A��ѹ
  {0x02010200,2,0},//B��ѹ
  {0x02010300,2,0},//C��ѹ
  {0x02020100,3,0},//A����
  {0x02020200,3,0},//B����
  {0x02020300,3,0},//C����
  {0x02800002,2,0},//Ƶ��
  //ģʽ��bit1
  //{DI_ACTIVE_DIRECT,1,1},//�й������ʶ��
  //{DI_REACTIVE_DIRECT,1,1},//�޹������ʶ��
  {0x02030000,3,1},//���й�����
  {0x02030100,3,1},//A�й�����
  {0x02030200,3,1},//B�й�����
  {0x02030300,3,1},//C�й�����
  {0x02040000,3,1},//���޹�����
  {0x02040100,3,1},//A�޹�����
  {0x02040200,3,1},//B�޹�����
  {0x02040300,3,1},//C�޹�����
  //ģʽ��bit2
  {0x02060000,2,2},//���޹�����
  {0x02060100,2,2},//A�޹�����
  {0x02060200,2,2},//B�޹�����
  {0x02060300,2,2},//C�޹�����
  //ģʽ��bit3
  {0x00010000,4,3},//�����й���
  {0x00020000,4,3},//�����й���
  {0x00030000,4,3},//�����޹��ܣ�(����޹�1��)
  {0x00040000,4,3},//�����޹��ܣ�(����޹�2��)
  //ģʽ��bit4
  {0x00050000,4,4},//һ�����޹���
  {0x00060000,4,4},//�������޹���
  {0x00070000,4,4},//�������޹���
  {0x00080000,4,4},//�������޹���
  //ģʽ��bit5 
  {0x02800004,3,5},//�й�����
  {0x02800005,3,5}//�޹�����

};

//�����͵ĸ������߳���
CONST INT8U LoadData_Len[] = 
{
  17,//��ѹ����
  24,//���޹�����
  8, //��������
  16,//���޹��ܵ���
  16,//�������޹��ܵ���
  6, //��ǰ����
  
};
//#endif

//��ȡ����ΪIndex�ĸ������ߵ�ʱ�������
//Index��ʾ���������������ݵĴ洢Index����ֵΪ0 -> LOAD_DATA_NUM-1
//pTime, ������ʱ�����ݷŵ���ָ��ָ��Ļ�������
//����1��ʾ���������ݣ�0��ʾû�ж�������
INT8U Read_LoadData_Type_Time(INT16U Index, INT8U *pType, S_HEX_Time* pTime)
{
  INT8U Temp[7 + ROM_CS_BYTES]; 
  INT16U Len; 

    TRACE();
  //��ȡ�����������ݵ���ʼ��LOAD_DATA_HEAD_SIZE���ֽ�
  //��Ҫ����ʼ�ַ���ʱ��
  //ǰ�����ֽ���0xA0��0xA0��ʾ�Ǹ�������, ����5���ֽ���ʱ��
  Len = Read_Storage_Data_Fix_Len(_SDI_LOAD_DATA + Index, \
        0, \
        LOAD_DATA_HEAD_SIZE, \
        Temp, \
        Temp, \
        sizeof(Temp)); 
 
  if(LOAD_DATA_HEAD_SIZE != Len)//�����ĳ��Ȳ���?����(һ�����ڲ�У��Ͳ���)
  {
    ASSERT_FAILED();
    return 0;
  }
  //�ж����ݸ�ʽ
  if((Temp[0] & 0xF0) EQ 0xA0 && (Temp[0] & 0x0F) < LOAD_DATA_TYPE_NUM)
  {
    *pType = (Temp[0] & 0x0F); //��4λ�洢������������
      
    mem_cpy(pTime -> Time, Temp + 1, 5, pTime, sizeof(S_HEX_Time)); 
    Set_STRUCT_Sum(pTime, sizeof(S_HEX_Time), pTime -> CS, sizeof(pTime -> CS)); 
    if(Check_HEX_Time(pTime) EQ 1)//ʱ���ʽ��ȷ
      return 1;
  }

  ASSERT_FAILED(); 
  return 0;
}

/*****************************************
����ԭ�ͣ�NT16U Get_LoadData_Index(S_HEX_Time *pTime)
�������ܣ���ȡĳ��ʱ�������ݵ�����, ���ö��ַ���ѯ�����������ݴ洢��
��ڲ�����ĳ��ʱ���
���ڲ���������ֵ, ʧ��ʱ����NULL_LOAD_INDEX
******************************************/
INT16U Get_LoadData_Index(INT8U Type, S_HEX_Time* pTime)//��ȡĳ��ʱ�������ݵ�����
{
  S_HEX_Time Time; 
  INT8U Temp[6], Count, Re; 
  INT32U Index; 
  INT8U Type1,Len;

  TRACE();
  Re = CHECK_STRUCT_SUM(LoadData_Index); 
  if(1 != Re)//ASSERT(Re EQ 1))//������ݵ�У���
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  Index = Get_LoadData_Time_Index(pTime -> Time); //���ҳ���ʱ������λ��
  Len = Read_Storage_Data(_SDI_LOAD_DATA_TIME_INDEX + Index, Temp, Temp, sizeof(Temp)); //������Сʱ�ڵ�һ�����ݵĴ洢λ��
  if(2 EQ Len)
  {
    Index = 0; 
    mem_cpy(&Index, Temp, 2, &Index, sizeof(Index)); //Index = *(INT16U *)Temp; 
    Count = 0; 
    while(Count < LOAD_DATA_SEARCH_NUM)
    {
      Clear_All_Dog(); //�����й�����ֹ��λ
      if(Read_LoadData_Type_Time(Index, &Type1, &Time) != 0) //������ʱ��������Ч
      {
        if(Cmp_Time(&Time, pTime) EQ TIME_EQU)//����ʱ����ȣ��ҵ�����
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

//��ȡĳһʱ��ķ�����
INT32U Get_Time_Mins(INT8U Time[])
{
  TRACE();
  
  return (INT32U)Time[0] + (INT32U)Time[1]*60 + (INT32U)(Time[2]-1)*1440;
	
}

//��ȡ�ƶ�����λ�õ����ݿ�, �ú�����Ҫ��Ϊ���޳���S_HEX_TIme�е�CS��, ����ʱ��תBCD��
//Index, ����ֵ, 0-LOAD_DATA_NUM-1
//Mode��ʾģʽ�֣��Ƿ����ĳ������
//pDst, Ŀ�껺����
//pDst_Start, 
//��ʽ:0xA0, 2�ֽ�
//Cur_Time0, sizeof(S_HEX_Time)
//����
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
  DstLen = 3; //Ԥ��һ���ֽ���Ϊ����
  
  if(Type != ALL_TYPE_DATA)//����Ƕ�ȡĳһ�ض����͵�����,��ǰ��ͺ�������Ͷ�Ҫ��Ϊ0xAA
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
    Len = Read_LoadData_Type_Time(Index, &Type, &TempTime); //��ȡ����һ�����ݵ�ʱ��
    if(Len > 0)//���ȺϷ�
    {
      Hex2Bcd_Buf(TempTime.Time, 5, pDst + 3, pDst_Start, Dst_Len);
      DstLen += 5;
      
      Type1 = 0xFF; //��ʾ����Ӧ�ö��������ݵ����� Type1 ++ == 0
      //����ȡ6������
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
        
        i = (Pub_Buf0[0] & 0x0F); //�������ݵ����ͣ�Ӧ�ñ�ǰ�ζ���������ֵ��
        if(i > Type1 && i < LOAD_DATA_TYPE_NUM)
        {
          mem_set(pDst + DstLen, 0xAA, i - Type1, pDst_Start, Dst_Len); 
          DstLen += i - Type1;
        }
        else if(i != Type1)//�������������Ͳ���ȷ��������߱�ǰ�ζ��������ͻ�С��
          break;
        
        Re = memcmp((INT8U *)Pub_Buf0 + 1, TempTime.Time, 5);
        if(Re EQ 0) //������ͬһ��ʱ���
        {
          Type1 = (Pub_Buf0[0] & 0x0F); //��ǰ��ȡ����������
          mem_cpy(pDst + DstLen, (INT8U *)Pub_Buf0 + LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES, LoadData_Len[Type1],\
                  pDst_Start, Dst_Len);
          DstLen += LoadData_Len[Type1];
          
          *(pDst + DstLen) = 0xAA; //���ӿ�ָ��
          DstLen ++;
          
          *pLast_Index = Index;
        }
        else //���ݵ�ʱ�䲻����ʼ���ݵ��Ǹ�ʱ����ˣ�
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
  pDst[2] = DstLen - 3; //���ݿ鳤��
  
  Sum = 0;
  for(i = 0; i < DstLen; i ++)
    Sum += pDst[i];
  
  pDst[DstLen ++] = Sum;  //У���
  pDst[DstLen ++] = 0xE5; //�������

  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  return DstLen;
}

//��ȡĳһ���͵�����ΪIndex�������ߵ���һ������
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

//д����ΪIndex�����ݵ���һ����������
INT8U Write_LoadData_Next_Index(INT16U Index, INT16U Next_Index)
{
   return Write_Storage_Data(_SDI_LOAD_DATA_NEXT_INDEX + Index, &Next_Index, sizeof(Next_Index));
  
}

//���ĳ���͵�����ude���ͺ������Ƿ���ȷ
INT8U Check_Load_Data_Type_Index(INT8U Type, INT16U Index)
{
  INT16U Start, Last;
  
  if(Index EQ NULL_2BYTES)
    return 0;

  if(Check_Meter_Factory_Status())//�ڹ���״̬�����Index�ĺϷ���!��ֹ��ΪIndex�Ҷ����¶��������ݵ����
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

//���ض������ĸ�������
//Mode��ʾ��¼ģʽ����NλΪ0��ʾ����ȡ�������ݣ������ڲ����жϸ�Index��ʱ����Ƿ�Ӧ�ü�¼ĳ�����ݣ������Ӧ�ü�¼
//�򲻻᷵�ظ����������Mode���NO_CHK_TIME��־�����ˣ��򲻼��ʱ�䡣��ȫ����Mode������ȡ���ݣ��������ÿ������ʱ��
//Num��ʾ������ȡ������?
//pDst,pDst_Start,DstLen��ʾ��ȡ��Ŀ�껺������Ϣ
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
  
  if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//����������?
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
      Frame_Ack_Info.Follow_Flag = 1;//�к���֡
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
  
  Frame_Ack_Info.Follow_Flag = 0;//û����֡
  Last_Read_Index.Var = 0;
  Last_Read_Num.Var = 0;
  Last_Read_i.Var = 0;  
  
  return Len;
}

//����ĳʱ�������ڸ��³��߳���ʱ��
INT32U Calc_Mins(S_HEX_Time *pTime)
{
  //return (INT32U) (pTime -> Time[T_DATE] - 1) * 24 * 60 + (INT32U) (pTime -> Time[T_HOUR]) * 60 + pTime -> Time[T_MIN];  
  return Get_Time_Mins(pTime -> Time);
}

//���Type�ฺ������������pTimeʱ����Ƿ�Ӧ��������
INT8U Check_Load_Data_Time(S_HEX_Time *pTime, INT8U Type)
{
  INT32U Mins;
  //���㵱ǰ�߹��ķ�
  Mins = Calc_Mins(pTime);//(INT32U) (pTime -> Time[T_DATE] - 1) * 24 * 60 + (INT32U) (pTime -> Time[T_HOUR] - 1) * 60 + pTime -> Time[T_MIN]; 
  //�Ƚ�ÿ�����ݣ����������ݵ�ʱ���Ƿ�
  //for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
  //{
    //ĳ�����ݵĴ洢ʱ��㵽�ˣ���洢��������
  if(GET_BIT(LoadData_Para.Mode, Type)!=0 &&\
     LoadData_Para.Period[Type] != 0 && \
     Mins % (LoadData_Para.Period[Type]) EQ 0) 
    return 1;
  else
    return 0;
}

//����������
//pTime�������������ݵĴ洢ʱ��
//pSrcд���ݻ�����
//SrcLen���ݳ���
INT16U Read_Load_Data_With_Time(INT8U Type, S_HEX_Time* pTime, INT8U Num, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Index; 
  //INT8U i;

  TRACE();
  
  if(Frame_Ack_Info.Read_Follow_Flag EQ 0) //���Ƕ�������������Ҫ��ȡʱ������
    Index = Get_LoadData_Index(Type, pTime); //��ȡ�����ݵĴ洢����
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

//����DI�õ������ฺ������
INT8U Get_Load_Data_Type(PROTO_DI PDI)
{
  return (INT8U) ((PDI & 0x00FF0000) >> 16);
}
//��������������
//DI, ���ݱ�ʾ, ��Ҫ��0x06XXXXXX
//Para��D110ʱ��ʾ��Ҫ��ȡ�ĸ������ߵ�ʱ��
//pDstĿ�껺����
//pDst_StartĿ�����ʼ��ַ����DstLenһ���޶�pDst�ͷ������ݳ���
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
  //��ȡ��������?
  Type = Get_Load_Data_Type(PDI);
  if(Type EQ 0) //�ܵ�����
  {
    Type = ALL_TYPE_DATA;
    Start = LoadData_Index.All_Type_Start; //�����ݵ���ʼ�ͽ�������
    Last =  LoadData_Index.All_Type_Last;// + LOAD_DATA_NUM - 1)%LOAD_DATA_NUM;
  }
  else if(Type >= 1 && Type <= 6) //��һ�ൽ����������
  {
    Type = Type - 1;
    Start = LoadData_Index.Type_Start[Type];//LoadData_Index.Type_Start[Type - 1]; //�������ݵ���ʼ�ͽ�������
    Last =  LoadData_Index.Type_Last[Type];// + LOAD_DATA_NUM - 1)%LOAD_DATA_NUM;   
  }
  else
    return 0;
///////////////////////////////////////////////////////////////////////////////////
  if(Start EQ Last)//�������ݻ�û�п�ʼ��¼
    return 0;
    
  //��ȡ��󣿸���ʱ�䣿���?
  if((0x000000FF & PDI) EQ 0x00)//��ȡ�����¼��
  {
    //if(Start EQ 0 && Last EQ 0) //��û�п�ʼ��¼����
     // return 0;
    if(Frame_Ack_Info.Read_Follow_Flag EQ 0)
    {
      if(ParaLen > 0)
        Num = Bcd2Hex_Byte(Para[0]); //�����ٸ���?
      else //�����Ƕ���������
        Num = 1;
    }
    else
      Num = 0;
    
    Len = Read_Load_Data_With_Index(Type, Start, Num, pDst, pDst, DstLen); 
    return Len;
  }
  else if((0x000000FF & PDI) EQ 0x01)//��ȡ����ʱ�����ݿ�
  {
    //if(Start EQ Last) //��û�п�ʼ��¼����
      //return 0;
    if(Frame_Ack_Info.Read_Follow_Flag EQ 0)
    {
      if(ParaLen >= 6)
      {
        Num = Bcd2Hex_Byte(Para[0]); //�����ٸ���?
        if(Num EQ 0)
          Num = 1;
        
        mem_cpy(TempTime.Time, &Para[1], 5, TempTime.Time, sizeof(TempTime.Time));
        Bcd2Hex_Buf(TempTime.Time, 5, TempTime.Time, TempTime.Time, sizeof(TempTime.Time));
        SET_STRUCT_SUM(TempTime);
        
        if(Check_HEX_Time(&TempTime) EQ 0) //ʱ�����ݱ�����ȷ
          return 0;
      }
      else
        return 0;
    }
    else //�����Ƕ���������
     Num = 1;
    
    Len = Read_Load_Data_With_Time(Type, &TempTime, Num, (INT8U *)pDst, (INT8U *)pDst_Start, DstLen);
    return Len;
  }
  else if((0x000000FF & PDI) EQ 0x02)//��ȡ�����¼��
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

//�ж�һ��PDI�Ƿ��Ǹ��ɼ�¼��PDI
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
//�ɶ�ȡ�����ĸ��ɼ�¼����
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

  //��ȡ��������?
  Type = Get_Load_Data_Type(PDI);
  if(Type EQ 0) //�ܵ�����
  {
    Mode = LoadData_Para.Mode; //ģʽ��
    Start = LoadData_Index.Start; //�����ݵ���ʼ�ͽ�������
    Last = LoadData_Index.Last;
  }
  else if(Type >= 1 && Type <= 6) //��һ�ൽ����������
  {
    if(GET_BIT(LoadData_Para.Mode, (Type -1))) //ģʽ�����Ƿ��и�������
    {
      Mode = (0x01 << (Type-1));
      Start = LoadData_Index.Start;//LoadData_Index.Type_Start[Type - 1]; //�������ݵ���ʼ�ͽ�������
      Last = LoadData_Index.Type_Last[Type - 1];   
    }
    else
      return 0;
  }
  else
    return 0;

  if((0x000000FF & PDI) EQ 0x00)//��ȡ�����¼��
  {
    if(Start EQ Last) //��û�п�ʼ��¼����
      return 0;
    else
    {
      Len = Read_Load_Data_With_Index(Start, Mode, Num, pDst, pDst, DstLen); 
      return Len;
    }
  }
  else if((0x000000FF & PDI) EQ 0x01)//��ȡ����ʱ�����ݿ�
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
  else if((0x000000FF & PDI) EQ 0x02)//��ȡ�����¼��
  {
    if(Start EQ Last)//�������ݻ�û�п�ʼ��¼
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

//����Ĭ�ϵĸ�����������
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

//�洢����������Ϣ�ı���, �ú���ÿСʱ����һ��
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

//�洢����������Ϣ�ı���, �ú���ÿСʱ����һ��
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


//��ȡ�������߲�������ROM��
void Read_LoadData_Para_From_Rom()
{
  INT8U i; 

  TRACE();
  
  //��ȡ���ɼ�¼ģʽ��
  if(Read_Storage_Data(SDI_LOAD_REC_WORD, (void *) &(LoadData_Para.Mode), (void *) &(LoadData_Para.Mode), sizeof(LoadData_Para.Mode)) != sizeof(LoadData_Para.Mode))
  {
    Debug_Print("Read SDI_LOAD_REC_WORD Para Err");
  } 
  
  //��ȡ��ʼʱ��
  if(Read_Storage_Data(SDI_LOAD_REC_START_TIME, (void *) (LoadData_Para.Time), (void *) (LoadData_Para.Time), sizeof(LoadData_Para.Time)) != sizeof(LoadData_Para.Time))
  {
    Debug_Print("Read SDI_LOAD_REC_START_TIME Para Err");
  }  
  Bcd2Hex_Buf((void *) LoadData_Para.Time, sizeof(LoadData_Para.Time), (void *) LoadData_Para.Time, (void *) LoadData_Para.Time, sizeof(LoadData_Para.Time)); 
  //��ȡʱ����
  for(i = 0; i < 6; i ++)
  {
    if(Read_Storage_Data(SDI_LOAD_REC1_INTER_TIME + i, (void *) (&LoadData_Para.Period[i]), (void *) (&LoadData_Para.Period[i]), 2) != 2)
      Debug_Print("Read 0x%lx Para Err", SDI_LOAD_REC1_INTER_TIME + i);  

    LoadData_Para.Period[i] = (INT16U) Bcd2Hex((INT8U *) (&LoadData_Para.Period[i]), 2);
  }
  SET_STRUCT_SUM(LoadData_Para);
}

//��Rom�ж�ȡLoadData_Index
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

//���S_LoadData_Index�����Ƿ�Ϸ�
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

//��������������ݵĺϷ���
void Check_LoadData_Index_Avail()
{
  INT8U Re = 1; 

    TRACE();
  //�ȶ��������ݣ�У��Ͳ������ȡ����������
  Re = Check_LoadData_Index((S_LoadData_Index *) &LoadData_Index); 
  if(Re EQ 0)
  {
    //Re = Check_LoadData_Index((S_LoadData_Index *) &LoadData_Index_Bak); 
    //if(Re EQ 0)
      Read_LoadData_Index_Data_From_Rom(); //��ROM�ж�ȡ�ò���
    //else
      //mem_cpy((void *) &LoadData_Index, (void *) &LoadData_Index_Bak, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
  }
}

//��鸺��������ز����ĺϷ���
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

//��ȡ��������������ĳ��ʱ����Сʱ������ͨ��Сʱ�������Զ�����Сʱ�ĵ�һ�����ݵĴ洢����
INT32U Get_LoadData_Time_Index(INT8U Time[])
{
  TRACE();
	ASSERT(Time[T_MIN]<60 && Time[T_HOUR]<24 &&\
		Time[T_DATE]>0 && Time[T_DATE]<32 &&\
		Time[T_MONTH]>0 && Time[T_MONTH]<13);
	
	//�޸�Ϊ15���ӵ�����������±��ʽ*4
	//��ʾ�߹��˶��ٸ�15����
	return (INT32U)Time[T_MIN]/(60/LOAD_DATA_INDEX_HOUR_NUM)+((INT32U)Time[T_HOUR]+((INT32U)Time[T_DATE]-1)*24+((INT32U)Time[T_MONTH]-1)*31*24)*LOAD_DATA_INDEX_HOUR_NUM;//%LOAD_DATA_MIN_INDEX_NUM;
}

//д��������
//pSrcд���ݻ�����
//pSrc��ʽ��������:��һ�����ֽڷֱ���0xA0��0xA0, ��ʾ�Ǹ������ߣ��������һ��S_HEX_Time���͵�ʱ������
//Flag��ʾ�Ƿ���һ���µ�ʱ�������,0��ʾ���ǣ�1��ʾ��
//��ʾ���������������ݵ�ʱ��
//SrcLen��ʾ���ݳ���
//����NO_ERR��ʾд�ɹ���������ʾдʧ��
INT8U Write_Load_Data(INT8U Type, INT8U Flag, INT8U* pSrc, INT16U SrcLen)
{
  INT8U Re; 
  INT16U Index, Next_Index, Last;
  INT32U Time_Index;
  INT8U Type1;
  S_HEX_Time TempTime;

  TRACE();
  if(0xA0 EQ (*pSrc & 0xF0) && (*pSrc & 0x0F) < LOAD_DATA_TYPE_NUM)//�洢��ǰ�����ֽ�һ��Ҫ������0xA0
  {
    Re = CHECK_STRUCT_SUM(LoadData_Index); //�������LoadData_Index��У�����ȷ
    if(1 != Re)
    {
      ASSERT_FAILED();
      Check_Data_Avail(); 
    }
    
    if(LoadData_Index.Last >= LOAD_DATA_NUM)//Index���ԣ������ܰɣ�
    {
      ASSERT_FAILED();
      LoadData_Index.Last = 0; 
    }
    
    Index = LoadData_Index.Last; //��ǰд������
    
    if((Index + 1) % LOAD_DATA_NUM EQ LoadData_Index.Start)
    {
      if(Read_LoadData_Type_Time(Index, &Type1, &TempTime) > 0 && Type1 EQ Type)
        Next_Index = Read_LoadData_Next_Index(Index); //��ǰҪ���ǵ��������ݣ����һ�����Ǹ����͵��µ���ʼ!
      else
        Next_Index = NULL_2BYTES;
    }
    
    Write_Storage_Data(_SDI_LOAD_DATA + Index, pSrc, SrcLen); //ֱ��������д�����ˣ�
    Write_LoadData_Next_Index(Index, NULL_2BYTES); //��ǰ���ݵ�����Ϊ�� 
    //ǰһ�����ݵ�����Ϊ��ǰ����
    Last = (LoadData_Index.Type_Last[Type] + LOAD_DATA_NUM - 1)%LOAD_DATA_NUM; 
    Write_LoadData_Next_Index(Last, Index); 

    //���¸�����������¼
    DIS_PD_INT;

    //����дλ�õ���ʼ�ͽ���������
    LoadData_Index.Last = (LoadData_Index.Last + 1) % LOAD_DATA_NUM;
    //д�����ͷִ����͵���ʼ�ͽ���
    Re = 0;
    if(LoadData_Index.Last EQ LoadData_Index.Start)//Last EQ Start��ʾ���һ�������Ѿ�׷���˵�һ������
    {
      LoadData_Index.Start = (LoadData_Index.Start + 1) % LOAD_DATA_NUM; //���ӵ�һ�����ݵ�����
      Re = 1;
    }
    
    //�������ݵ���ʼ�ͽ�������
    if(Re EQ 1) //���дβ׷������ʼλ��
      LoadData_Index.Type_Start[Type] = Next_Index;
    else if(LoadData_Index.Type_Start[Type] EQ 0 &&\
            LoadData_Index.Type_Last[Type] EQ 0)//��ʾ�������ݻ�û�п�ʼд��
    {
      LoadData_Index.Type_Start[Type] = Index;
    }
    LoadData_Index.Type_Last[Type] = LoadData_Index.Last;
    
    //�����͵���ʼ�ͽ�������
    LoadData_Index.All_Type_Start = LoadData_Index.Start;
    if(Flag EQ 1)//һ���µ�ʱ���
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
    SET_STRUCT_SUM(LoadData_Index); //����У���
    
    EN_PD_INT;
    //��Index���ݱ��ݵ�Bak��ȥ

    Time_Index = Get_LoadData_Time_Index(pSrc + 1); //ʱ������
    //��ǰСʱ���������˱仯�򱣴��ϵģ�������LoadData_Index.Min_Index
    if(Time_Index != LoadData_Index.Time_Index)//һ���µ�ʱ�����������ߵ��˵�Сʱ���������ϴβ�ͬ
    {
      DIS_PD_INT;
      LoadData_Index.Time_Index = Time_Index; 
      SET_STRUCT_SUM(LoadData_Index);
      EN_PD_INT;
      
      Debug_Print("Write_Load_Data Time_Index = 0x%lx, Index = %x", Time_Index, Index);
      Write_Storage_Data(_SDI_LOAD_DATA_TIME_INDEX + Time_Index, &Index, 2); //����ǰ�洢λ�ô洢Сʱ������
    }
    //mem_cpy((void *) &LoadData_Index_Bak, (void *) &LoadData_Index, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak)); 

    return 1;
  }
  
  return 0;
}

//���ɸ�����������
//�����ʽ:
/*
0:0xA0
1:0xA0
2:Time[0]��(Hex)
3:Time[1]ʱ
4:Time[2]��
5:Time[3]��
6:Time[4]��
ROM_CS_BYTES:У���

11:��ѹ����Ƶ�ʵ�
   0xAA
   ���޹����ʵ�
   0xAA
   ......
*/
INT16U Make_LoadData(INT8U Type, S_HEX_Time* pTime, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i; 
  INT16U Len, TempLen; 

  TRACE();

  pDst[0] = (0xA0 | Type); //����ͷ��0xA0|������
  Len = 1; 
  //��ǰʱ�临��, �֡�ʱ���ա��¡�������ֽ�
  mem_cpy(pDst + Len, &(pTime -> Time[T_MIN]), 5, pDst_Start, DstLen); 
  //����ǰ6���ֽڵ�У���
  Set_Sum(pDst, LOAD_DATA_HEAD_SIZE, pDst + LOAD_DATA_HEAD_SIZE, ROM_CS_BYTES, pDst_Start, DstLen); 
  Len = LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES; 

  //��������ʵ������������
  //Len ++; //Ԥ��һ���ֽ���Ϊ���ݳ��ȵĸ�λ
  //pDst[Len ++] = 0xA0; //����ͷ������0xA0
  //pDst[Len ++] = 0xA0; 
  //Len ++; 
  //��������ʱ��

  //�ֱ��ȡLoadData_Info�ж����ÿ��������Ŀ
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

//�������ߵĴ洢��������
void LoadData_Proc()
{
  INT8U Re, i, Flag;  
  INT32U Mins; 
  INT16U Len;
  S_HEX_Time TempTime; 
  INT8U Time[5]; 
    
  static S_Int8U Min_Bak =  {CHK_BYTE, 0xFF, CHK_BYTE}; 

  if(Min_Bak.Var EQ Cur_Time0.Time[T_MIN])//ÿ���ӲŽ���һ�θú���
  {
    return;
  } 

  TRACE();

  Min_Bak.Var = Cur_Time0.Time[T_MIN]; 

  Re = CHECK_STRUCT_SUM(LoadData_Para); //�������߲����Է�
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  mem_cpy(Time, (INT8U *)LoadData_Para.Time, sizeof(LoadData_Para.Time), Time, sizeof(Time));
  Time[T_YEAR] = Cur_Time0.Time[T_YEAR];
  //��ǰʱ���ڸ��ɼ�¼��ʼʱ��֮��
  if(_Check_HEX_Time(Time) && Cmp_Array_Time((INT8U *)Cur_Time0.Time, Time,  sizeof(Time)) != TIME_BEF)
  {
    mem_cpy(&TempTime, (S_HEX_Time *) &Cur_Time0, sizeof(Cur_Time0), &TempTime, sizeof(TempTime)); 
    //���㵱ǰ�߹��ķ�
    Mins = Calc_Mins(&TempTime);//(INT32U) (TempTime.Time[T_DATE] - 1) * 24 * 60 + (INT32U) (TempTime.Time[T_HOUR] - 1) * 60 + TempTime.Time[T_MIN]; 
    
    Flag = 1;
    //�Ƚ�ÿ�����ݣ����������ݵ�ʱ���Ƿ�
    for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
    {
      //ĳ�����ݵĴ洢ʱ��㵽�ˣ���洢��������
      
      if(GET_BIT(LoadData_Para.Mode, i) > 0 &&\
         LoadData_Para.Period[i] != 0 && \
         Mins % (LoadData_Para.Period[i]) EQ 0)
      {
        Debug_Print("Load Data %dth type data save now!", i);   
  
        OS_Mutex_Pend(PUB_BUF0_SEM_ID); //ʹ��Pub_Buf0�������ɸ�����������
        Len = Make_LoadData(i, &TempTime, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0)); //���ɸ������ߣ��������䳤��
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
