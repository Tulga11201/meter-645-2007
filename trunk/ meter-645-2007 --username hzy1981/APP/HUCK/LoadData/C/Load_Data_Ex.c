#define LOAD_DATA_C
#include "Includes.h"

#define LOAD_DATA_SEARCH_NUM 16
/*****************************************
����ԭ�ͣ�INT8U Count_Mid_Index(INT8U Task_ID, INT16U Start, INT16U Last)
�������ܣ�����ĳ����������������м�����ֵ
��ڲ�����Start����ʼ��Index
Last, ��ֹIndex
Ratio�����ַ��ķֱ�
���ڲ������м�����
******************************************/
/*
INT16U Count_Mid_Index(INT8U Ratio, INT16U Start, INT16U Last)
{
  INT16U MidIndex; 
  
  if(ASSERT(Ratio != 0))//�ֱȲ���Ϊ0��������ͻ��0�ˣ�
  return 0; 
  
  if(Start <= Last)
  MidIndex = (Last + Start)/Ratio; 
  else//��ʱ�ǵ�׷����ʽ
  {
  MidIndex = (Last + LOAD_DATA_NUM + Start)/Ratio; //ΪʲôҪ�����㣿�Լ�����һ��
  if(MidIndex> = LOAD_DATA_NUM)
  MidIndex = MidIndex%LOAD_DATA_NUM; 
  }
  return MidIndex; 
}
*/

//��ȡ����ΪIndex�ĸ������ߵ�ʱ��
//Index��ʾ���������������ݵĴ洢Index����ֵΪ0 -> LOAD_DATA_NUM-1
//pTime, ������ʱ�����ݷŵ���ָ��ָ��Ļ�������
//����1��ʾ���������ݣ�0��ʾû�ж�������
INT8U Read_LoadData_Time(INT16U Index, S_HEX_Time* pTime)
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
    DEBUG_PRINT(HUCK, DEBUG_0, "Read LoadData Index = %d error", Index); 
    return 0;
  }
  //�ж����ݸ�ʽ
  if(Temp[0] EQ 0xA0 && Temp[1] EQ 0xA0)
  {
    mem_cpy(pTime -> Time, Temp + 2, 5, pTime, sizeof(S_HEX_Time)); 
    Set_STRUCT_Sum(pTime, sizeof(S_HEX_Time), pTime -> CS, sizeof(pTime -> CS)); 
    if(Check_HEX_Time(pTime) EQ 1)//ʱ���ʽ��ȷ
      return 1;
    else
    {
      ASSERT_FAILED(); 
      return 0;
    }
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
}

/*****************************************
����ԭ�ͣ�NT16U Get_LoadData_Index(S_HEX_Time *pTime)
�������ܣ���ȡĳ��ʱ�������ݵ�����, ���ö��ַ���ѯ�����������ݴ洢��
��ڲ�����ĳ��ʱ���
���ڲ���������ֵ, ʧ��ʱ����NULL_LOAD_INDEX
******************************************/
INT16U Get_LoadData_Index(S_HEX_Time* pTime)//��ȡĳ��ʱ�������ݵ�����
{
  S_HEX_Time Time; 
  INT8U Temp[6], Count, Re; 
  INT16U Index, Len; 

  TRACE();
  Re = CHECK_STRUCT_SUM(LoadData_Index); 
  if(1 != Re)//ASSERT(Re EQ 1))//������ݵ�У���
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  Index = Get_LoadData_Min_Index(pTime -> Time); //���ҳ���Сʱ����λ��
  Len = Read_Storage_Data(_SDI_LOAD_DATA_MIN_INDEX + Index, Temp, Temp, sizeof(Temp)); //������Сʱ�ڵ�һ�����ݵĴ洢λ��
  if(2 EQ Len)
  {
    Index = 0; 
    mem_cpy(&Index, Temp, 2, &Index, sizeof(Index)); //Index = *(INT16U *)Temp; 
    Count = 0; 
    while(Count < LOAD_DATA_SEARCH_NUM)
    {
      if(Read_LoadData_Time(Index, &Time) != 0) //������ʱ��������Ч
      {
        if(Cmp_Time(&Time, pTime) EQ TIME_EQU)//����ʱ����ȣ��ҵ�����
          break;
      }
      Index ++; 
      OS_TimeDly_Ms(10);
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
INT16U Read_Load_Data_With_Index(INT16U Index, INT8U Mode, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT16U Len, SrcPosi, DstPosi; 
  INT8U i, Re, Sum; 
  INT32U Mins;

  TRACE();

  Len = Read_Storage_Data(_SDI_LOAD_DATA + Index, pDst, pDst, DstLen); 
  if(Len EQ LOAD_DATA_LEN)//Get_LoadData_All_Len() EQ Len && Len > (2 + sizeof(S_HEX_Time)))//���ȺϷ�
  {
    if(pDst[0] EQ 0xA0 && pDst[1] >= 1 && pDst[1] <= LOAD_DATA_TYPE_NUM)//ͷ2�ֽ���ȷ
    {
	  Mins = Get_Time_Mins(pDst + 2);

      //�洢��ʱ��������HEX���ʽ, ת��ΪBCD��
      //Hex2Bcd_Buf(pDst + 2, 5, pDst + 2, pDst, DstLen); 
      SrcPosi = LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES; //��������ǰ�ƣ�ȥ��ROM_CS; 
      mem_cpy(pDst, pDst + SrcPosi, 9, pDst_Start, DstLen); 
      DstPosi = 9; 
      SrcPosi += 9; 
      //��6�ฺ���������ݣ��ֱ��ж����Ƿ���Ҫ����
      for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
      {
        Len = Get_LoadData_Type_Len(i); //��ȡ��i�����ݵĳ���
        if(GET_BIT(Mode, i) EQ 1 &&\
		   LoadData_Para.Period[i] != 0 &&\
          (Mins % LoadData_Para.Period[i])==0)//ģʽ��8��ʾ��ʾ�Ƿ��¼������
        {
			mem_cpy(pDst + DstPosi, pDst + SrcPosi, Len, pDst_Start, DstLen); 
			SrcPosi += Len; 
			DstPosi += Len;
        }
		else
        {
			*(pDst + DstPosi) = 0xAA;
			DstPosi ++;
			SrcPosi +=Len;
        }
      }

      *(pDst) =DstPosi / 256;
      *(pDst + 3) =DstPosi % 256;
      
      Sum = 0;
      for(i = 0; i < DstPosi; i ++)
		  Sum += *(pDst + i); 
      //����һ���ֽ�У���һ���ֽڽ�����   
      pDst[DstPosi++]=Sum;//�����
      pDst[DstPosi++]=0xE5;      
	  
      //*(pDst+DstPosi++)=*(pDst+SrcPosi++);
      //*(pDst+DstPosi++)=*(pDst+SrcPosi++);
	  
      /////�������һ�ζ�������ֵ

      /////�������һ�ζ�������ֵ
      Re = CHECK_STRUCT_SUM(LoadData_Index); 
      if(1 != Re)//ASSERT(1 EQ Re))
      {
        ASSERT_FAILED();
        mem_cpy((void *) &LoadData_Index, (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index, sizeof(LoadData_Index)); 
      }
      
      LoadData_Index.Last_Read = Index; //���һ�ζ�ȡ������
      SET_STRUCT_SUM(LoadData_Index); 
      ///////////////////////////
      return DstPosi;
    }
  }
  //*pErr = RD_LOAD_DATA_ERR; 
  return 0;
}

//����������
//pTime�������������ݵĴ洢ʱ��
//pSrcд���ݻ�����
//SrcLen���ݳ���
INT16U Read_Load_Data_With_Time(S_HEX_Time* pTime, INT8U Mode, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Index; 

    TRACE();
  Index = Get_LoadData_Index(pTime); //��ȡ�����ݵĴ洢����

  if(NULL_LOAD_INDEX != Index)
  {
    return Read_Load_Data_With_Index(Index, Mode, (INT8U *) pDst, (INT8U *) pDst_Start, DstLen);
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
  INT8U Type,Mode; 
  INT16U Len, Index, Start, Last; 
  S_HEX_Time TempTime; 

  TRACE();
  if(LoadData_Index.Start EQ 0 && LoadData_Index.Last EQ 0)
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "No Load_Data Now!"); 
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
      Start = LoadData_Index.Type_Start[Type - 1]; //�������ݵ���ʼ�ͽ�������
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
      Len = Read_Load_Data_With_Index(Start, Mode, pDst, pDst, DstLen); 
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
    Len = Read_Load_Data_With_Time(&TempTime, Mode, pDst, pDst_Start, DstLen);
    
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

    Len = Read_Load_Data_With_Index(Index, Mode, pDst, pDst, DstLen); 
    return Len;
  }
  else
  {
    return 0;
  }

  /*
  else if(0xD111 EQ DI)//����һ��
  {
    Index = LoadData_Index.Last_Read + 1; 
    
    if(Index> = LOAD_DATA_NUM)
    Index = 0; 
    
    if(Index EQ LoadData_Index.Last)//�Ѿ��������һ�������ˣ�û�����ݿɶ��ˣ�����
    {
    *pErr = RD_LOAD_DATA_ERR; 
    return 0; 
    }
    //��Index��ȡĳ��������������
    //Len = Read_Storage_Data(_SDI_LOAD_DATA + LoadData_Index.Last_Read, pDst, pDst, DstLen); 
    Len = Read_Load_Data_With_Index(Index, pDst, pDst, DstLen); 
    return Len; 
  }
  else if(0xD112 EQ DI)//��ȡ�����
  {
    Len = Read_Load_Data_With_Index(LoadData_Index.Start, pDst, pDst, DstLen); 
    return Len;     
  }
  else if(0xD113 EQ DI)//�������
  {
    //LoadData_Index.Last��ǰһ���������һ��Ŷ!
    if(LoadData_Index.Last EQ 0)
    Index = LOAD_DATA_NUM-1; 
    else
    Index = LoadData_Index.Last-1; 
    Len = Read_Load_Data_With_Index(Index, pDst, pDst, DstLen); 
    return Len;  
  }
  else if(0xD114 EQ DI)//�ض��ϴο�
  {
    Index = LoadData_Index.Last_Read; //(INT16U)Bcd2Hex(Para, 2); //(INT16U)Bcd2Hex_Byte(Para[0]) + (INT16U)Bcd2Hex_Byte(Para[1])*100; 
    if(Index> = LOAD_DATA_NUM)
    Index = 0; 
    
    Len = Read_Load_Data_With_Index(Index, pDst, pDst, DstLen); 
    return Len;  
  }
  else if(0xD115 EQ DI)//���ƶ�������, ������ڲ�����Ϊ����ֵ
  {
    Index = (INT16U)Bcd2Hex(Para, 2); //(INT16U)Bcd2Hex_Byte(Para[0]) + (INT16U)Bcd2Hex_Byte(Para[1])*100; 
    if(Index> = LOAD_DATA_NUM)
    Index = 0; 
    
    Len = Read_Load_Data_With_Index(Index, pDst, pDst, DstLen); 
    return Len;  
  }
  */
}

//����Ĭ�ϵĸ�����������
void Set_Def_Load_Data_Index()
{
    TRACE();

  mem_cpy((void *) &LoadData_Index, (void *) Def_LoadData_Index, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
  mem_cpy((void *) &LoadData_Index_Bak, (void *) Def_LoadData_Index, sizeof(LoadData_Index), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak));

  SET_STRUCT_SUM(LoadData_Index);
  SET_STRUCT_SUM(LoadData_Index_Bak);

  Save_LoadData_PD_Data();
  Save_LoadData_Index(); 
  Save_LoadData_Index_Bak();
}

void Save_LoadData_PD_Data()
{
	  TRACE();

	if(CHECK_STRUCT_SUM(LoadData_Index))
		Write_Storage_Data(_SDI_LOAD_DATA_INDEX_PD,(void *)&LoadData_Index,sizeof(LoadData_Index));
	else if(CHECK_STRUCT_SUM(LoadData_Index_Bak))
		Write_Storage_Data(_SDI_LOAD_DATA_INDEX_PD,(void *)&LoadData_Index_Bak,sizeof(LoadData_Index));
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
  ASSERT(NO_ERR EQ Re);
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
  ASSERT(NO_ERR EQ Re);
}


//��ȡ�������߲�������ROM��
void Read_LoadData_Para_From_Rom()
{
  INT8U i; 

  TRACE();
  
  //��ȡ���ɼ�¼ģʽ��
  if(Read_Storage_Data(SDI_LOAD_REC_WORD, (void *) &(LoadData_Para.Mode), (void *) &(LoadData_Para.Mode), sizeof(LoadData_Para.Mode)) != sizeof(LoadData_Para.Mode))
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "Read SDI_LOAD_REC_WORD Para Err");
  } 
  
  //��ȡ��ʼʱ��
  if(Read_Storage_Data(SDI_LOAD_REC_START_TIME, (void *) (LoadData_Para.Time), (void *) (LoadData_Para.Time), sizeof(LoadData_Para.Time)) != sizeof(LoadData_Para.Time))
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "Read SDI_LOAD_REC_START_TIME Para Err");
  }  
  Bcd2Hex_Buf((void *) LoadData_Para.Time, sizeof(LoadData_Para.Time), (void *) LoadData_Para.Time, (void *) LoadData_Para.Time, sizeof(LoadData_Para.Time)); 
  //��ȡʱ����
  for(i = 0; i < 6; i ++)
  {
    if(Read_Storage_Data(SDI_LOAD_REC1_INTER_TIME + i, (void *) (&LoadData_Para.Period[i]), (void *) (&LoadData_Para.Period[i]), 2) != 2)
      DEBUG_PRINT(HUCK, DEBUG_0, "Read 0x%lx Para Err", SDI_LOAD_REC1_INTER_TIME + i);  

    LoadData_Para.Period[i] = (INT16U) Bcd2Hex((INT8U *) (&LoadData_Para.Period[i]), 2);
  }
  SET_STRUCT_SUM(LoadData_Para);
}

//��Rom�ж�ȡLoadData_Index
void Read_LoadData_Index_Data_From_Rom()
{
  TRACE();

  if(Read_Storage_Data(_SDI_LOAD_DATA_INDEX, (void *) &LoadData_Index, (void *) &LoadData_Index, sizeof(LoadData_Index)) != sizeof(LoadData_Index))
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "Read LOAD_DATA_INDEX data error"); 
    OS_TimeDly_Ms(100); 
    if(Read_Storage_Data(_SDI_LOAD_DATA_INDEX_BAK, (void *) &LoadData_Index, (void *) &LoadData_Index, sizeof(LoadData_Index)) != sizeof(LoadData_Index))
    {
      DEBUG_PRINT(HUCK, DEBUG_0, "Read LOAD_DATA_INDEX_BAK data error"); 
      OS_TimeDly_Ms(100); 
      mem_cpy((void *) &LoadData_Index, (void *) &Def_LoadData_Index, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
    }
  }
  SET_STRUCT_SUM(LoadData_Index); 
  mem_cpy((void *) &LoadData_Index_Bak, (void *) &LoadData_Index, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak));
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
    Re = Check_LoadData_Index((S_LoadData_Index *) &LoadData_Index_Bak); 
    if(Re EQ 0)
      Read_LoadData_Index_Data_From_Rom(); //��ROM�ж�ȡ�ò���
    else
      mem_cpy((void *) &LoadData_Index, (void *) &LoadData_Index_Bak, sizeof(LoadData_Index), (void *) &LoadData_Index, sizeof(LoadData_Index));
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
INT16U Get_LoadData_Min_Index(INT8U Time[])
{
  TRACE();
	ASSERT(Time[T_MIN]<60 && Time[T_HOUR]<24 &&\
		Time[T_DATE]>0 && Time[T_DATE]<32 &&\
		Time[T_MONTH]>0 && Time[T_MONTH]<13);
	
	//�޸�Ϊ15���ӵ�����������±��ʽ*4
	//��ʾ�߹��˶��ٸ�15����
	return (INT16U)Time[T_MIN]/15+((INT16U)Time[T_HOUR]+((INT16U)Time[T_DATE]-1)*24+((INT16U)Time[T_MONTH]-1)*31*24)*4;//%LOAD_DATA_MIN_INDEX_NUM;
}

//д��������
//pSrcд���ݻ�����
//pSrc��ʽ��������:��һ�����ֽڷֱ���0xA0��0xA0, ��ʾ�Ǹ������ߣ��������һ��S_HEX_Time���͵�ʱ������
//��ʾ���������������ݵ�ʱ��
//SrcLen��ʾ���ݳ���
//����NO_ERR��ʾд�ɹ���������ʾдʧ��
INT8U Write_Load_Data(INT8U* pSrc, INT16U SrcLen)
{
  INT8U Re, i, Type;
  INT16U Index, Min_Index; 
  //static INT16U Old_Index = NULL_2BYTES; 
  TRACE();
  
  Type = *(pSrc + 1);
  
  if(0xA0 EQ * pSrc && Type >= 1 && Type <= LOAD_DATA_TYPE_NUM)//����ͷ�͸�����������
  {
    Re = CHECK_STRUCT_SUM(LoadData_Index); //�������LoadData_Index��У�����ȷ
    if(1 != Re)//ASSERT(1 EQ Re))
    {
      ASSERT_FAILED();
      Check_Data_Avail(); 
    }
    
    Re = _Check_HEX_Time(pSrc + 2);   
    if(1 != Re)//ASSERT(1 EQ Re))//ʱ�䲻�Դ���
    {
      ASSERT_FAILED();
      return 0; 
    }
    
    Index = LoadData_Index.Last; //Index���ǵ���Ӧ��д�������
    if(!(Index < LOAD_DATA_NUM))//Index���ԣ������ܰɣ�
    {
      ASSERT_FAILED();
      Index = 0; 
    }
    
    Re = Write_Storage_Data(_SDI_LOAD_DATA + Index, pSrc, SrcLen); //ֱ��������д�����ˣ�
    if(1 != Re)
    {
      ASSERT_FAILED(); 
      DEBUG_PRINT(HUCK, DEBUG_0, "Write_Load_Data Error");
    }

    Re = CHECK_STRUCT_SUM(LoadData_Index); //���У���
    if(1 != Re)//ASSERT(1 EQ Re))
    {
      ASSERT_FAILED();
      Check_Data_Avail(); 
    }
    
    LoadData_Index.Last ++; //����Last����
    if(LOAD_DATA_NUM <= LoadData_Index.Last)
      LoadData_Index.Last = 0; 

    if(LoadData_Index.Last EQ LoadData_Index.Start)//Last EQ Start��ʾ���һ�������Ѿ�׷���˵�һ������
      LoadData_Index.Start ++; //���ӵ�һ�����ݵ�����

    if(LOAD_DATA_NUM <= LoadData_Index.Start)//LoadData_Index.Start�ķ�ΧҲ��0 -> LOAD_DATA_NUM-1֮��
      LoadData_Index.Start = 0; 

    //6�ฺ���������ݵ��������ĩ��¼
    LoadData_Index.Type_Last[Type - 1] = LoadData_Index.Last;

    
    SET_STRUCT_SUM(LoadData_Index); //����У���
    //��Index���ݱ��ݵ�Bak��ȥ
    mem_cpy((void *) &LoadData_Index_Bak, (void *) &LoadData_Index, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak)); 

    Min_Index = Get_LoadData_Min_Index(pSrc + 2); //Сʱ����
    //��ǰСʱ���������˱仯�򱣴��ϵģ�������LoadData_Index.Min_Index
    if(Min_Index != LoadData_Index.Min_Index)//һ���µ�Сʱ�����ߵ��˵�Сʱ���������ϴβ�ͬ
    {
      LoadData_Index.Min_Index = Min_Index; 
      SET_STRUCT_SUM(LoadData_Index); 
      mem_cpy((void *) &LoadData_Index_Bak, (void *) &LoadData_Index, sizeof(LoadData_Index_Bak), (void *) &LoadData_Index_Bak, sizeof(LoadData_Index_Bak)); 

      Re = Write_Storage_Data(_SDI_LOAD_DATA_MIN_INDEX + Min_Index, &Index, 2); //����ǰ�洢λ�ô洢Сʱ������
      ASSERT(1 EQ Re);
    }
    return 1;
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
}

//��ȡ���������ܳ�
//ÿ�����ݿ������һ��0xAAŶ
INT16U Get_LoadData_All_Len()
{
  INT8U i; 
  INT16U Len; 

  TRACE();
  //Len = 2 + sizeof(S_HEX_Time); //2�ֽ�0xAA��һ��Cur_Time0
  Len = LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES + 4 + 5; //2�ֽ�A0 + 5�ֽ�ʱ�� + ROM_CS_BYTESУ���, ��������AA��һ�����ֽ���, ����ʱ��
  for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)//��6��������Ŷ, �ֱ���0-5��ʾ
  {
    Len += Get_LoadData_Type_Len(i); //pDst + Len, pDst, DstLen, &Err); ������һ��AA
  }
  return Len + 2; //����2���ֽڵĿ��ۼ�У��ͺͿ������������ֽڵ�ͷ�����п��ֽ���
}

//��ȡĳ�ฺ���������ݵĳ��� 
//Type:��𣬴�0-5�ֱ��ʾ6�����ݣ�����Ӧ�ÿ�LoadData_Info[i].Type�Ķ���
INT16U Get_LoadData_Type_Len(INT8U Type)
{
  INT16U Len = 0; 
  INT8U i; 

  TRACE();
  for(i = 0; i < S_NUM(LoadData_Info); i ++)
  {
    if(LoadData_Info[i].Type EQ Type)
    {
      Len += LoadData_Info[i].Len;
    }
  }
  if(Len != 0)
  {
    return Len + 1;
  } //����һ��0xAA
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
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
  INT8U i, Sum; 
  INT16U Len, TempLen; 

  TRACE();
  
  if(!(Type >= 1 && Type != LOAD_DATA_TYPE_NUM)
  {
    ASSERT_FAILED();
    return 0;
  }

  pDst[0] = 0xA0; //����ͷ��0xA0
  pDst[1] = Type //������������; 
  Len = 2; 
  //��ǰʱ�临��, �֡�ʱ���ա��¡�������ֽ�
  mem_cpy(pDst + Len, &(pTime -> Time[T_MIN]), 5, pDst_Start, DstLen); 
  //����ǰ7���ֽڵ�У���
  Set_Sum(pDst, LOAD_DATA_HEAD_SIZE, pDst + LOAD_DATA_HEAD_SIZE, ROM_CS_BYTES, pDst_Start, DstLen); 
  Len = LOAD_DATA_HEAD_SIZE + ROM_CS_BYTES; 

  //�ֱ��ȡLoadData_Info�ж����ÿ��������Ŀ
  for(i = 0; i < S_NUM(LoadData_Info); i ++)
  {
    if(LoadData_Info[i].Type EQ Type - 1)
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
  INT8U Re, i; 
  INT16U Len; 
  INT32U Mins; 
  INT8U LoadData_Flag; //�Ƿ���Ҫ��¼������������, 1��ʾ��Ҫ, 0��ʾ����Ҫ
  S_HEX_Time TempTime; 
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

  LoadData_Flag = 0; 
  mem_cpy(&TempTime, (S_HEX_Time *) &Cur_Time0, sizeof(Cur_Time0), &TempTime, sizeof(TempTime)); 
  //���㵱ǰ�߹��ķ�
  Mins = (INT32U) (TempTime.Time[T_DATE] - 1) * 24 * 60 + (INT32U) (TempTime.Time[T_HOUR] - 1) * 60 + TempTime.Time[T_MIN]; 
  //�Ƚ�ÿ�����ݣ����������ݵ�ʱ���Ƿ�
  for(i = 0; i < LOAD_DATA_TYPE_NUM; i ++)
  {
    //ĳ�����ݵĴ洢ʱ��㵽�ˣ���洢��������
    if(LoadData_Para.Period[i] != 0 && \
       Mins % (LoadData_Para.Period[i]) EQ 0)
    {
      DEBUG_PRINT(HUCK, DEBUG_0, "Load Data %dth type data save now!", i); 
      LoadData_Flag |= (0x01 << i) ;  
      //break;
    }
  }

  //��Ҫ���ɲ��洢��������
  if(LoadData_Flag != 0)
  {
    DEBUG_PRINT(HUCK, DEBUG_0, "Load Data Time!"); 
    OS_Mutex_Pend(PUB_BUF0_SEM_ID); //ʹ��Pub_Buf0�������ɸ�����������
    Len = Make_LoadData(&TempTime, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0)); //���ɸ������ߣ��������䳤��
    if(Get_LoadData_All_Len() != Len)//զ���£����Ȳ���?ֻ���ڳ�����ȷ������²Ŵ洢Ŷ
    {
      ASSERT_FAILED(); 
      DEBUG_PRINT(HUCK, DEBUG_0, "Make_LoadData Len error");
    }
    else
    {
      DEBUG_PRINT(HUCK, DEBUG_0, "Write Load Data!"); 
      Re = Write_Load_Data(LoadData_Flag, (INT8U *) Pub_Buf0, Len); 
      ASSERT(NO_ERR EQ Re);
    }
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
  }
}
#undef LOAD_DATA_C
