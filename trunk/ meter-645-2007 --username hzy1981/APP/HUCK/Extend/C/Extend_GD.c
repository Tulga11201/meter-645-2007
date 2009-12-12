#define EXTEND_GD_C
#include "Includes.h"

#if METER_PLACE == METER_GD
//�ִ��¼�������Ŀ����չ����
/*
U_Byte_Bit  GD_Meter_Stat;        //�㶫�����״̬��
U_Byte_Bit  GD_PwrDir_Stat;       //�㶫���й����ʷ���״̬��
U_Byte_Bit  GD_LossVolt_Stat;        //�㶫��ʧѹ״̬��
U_Byte_Bit  GD_LossCurr_Stat;        //�㶫��ʧ��״̬��
U_Byte_Bit  GD_Hard_Stat;        //�㶫��Ӳ��״̬��
U_Byte_Bit  GD_Prog_Stat;        //�㶫�����״̬��

*/
INT16U Extend_Event_MultiTimes_Proc(INT8U Event_ID,INT8U Occur_Or_End,INT8U Flag,INT8U *pReturn_Flag)
{
  INT16U Len = 0;
  INT8U Temp[5];
  
  S_Int8U Old_Loss_Vol_Status={CHK_BYTE,0,CHK_BYTE};
  S_Int8U Old_Loss_Cur_Status={CHK_BYTE,0,CHK_BYTE};
  S_Int8U Old_Neg_Cur_Status={CHK_BYTE,0,CHK_BYTE};
  
  *pReturn_Flag = 0;
  
  //-------------------------ʧѹ���⴦��----------------------------------
  if(Event_ID EQ ID_EVENT_A_LOSS_VOLT || Event_ID EQ ID_EVENT_B_LOSS_VOLT || Event_ID EQ ID_EVENT_C_LOSS_VOLT)
  {
    *pReturn_Flag = 1;
    
    if(Occur_Or_End EQ EVENT_END)//�¼�����
    {
      Len = Event_MultiTimes_Normal_Proc(ID_EVENT_LOSS_VOL, EVENT_END, Flag);
    } 
    else//�¼�����
    {
      if(Old_Loss_Vol_Status.Var != 0)//֮ǰ��ʧѹ�¼�,��Ҫ��֮ǰ���¼�����
        Event_MultiTimes_Normal_Proc(ID_EVENT_LOSS_VOL, EVENT_END, Flag);
      //���¼�����
      Len = Event_MultiTimes_Normal_Proc(ID_EVENT_LOSS_VOL, EVENT_OCCUR, Flag);
    }
    Old_Loss_Vol_Status.Var = 0; //GD_LossVolt_Stat.Byte; 
  }
  
  //------------------------ʧ�����⴦��-------------------------------
  if(Event_ID EQ ID_EVENT_A_LOSS_CURR || Event_ID EQ ID_EVENT_B_LOSS_CURR || Event_ID EQ ID_EVENT_C_LOSS_CURR)
  {
    *pReturn_Flag = 1;
    
    Temp[0] = Cur_Time1.Min;
    Temp[1] = Cur_Time1.Hour;
    Temp[2] = Cur_Time1.Date;
    Temp[3] = Cur_Time1.Month;
    Temp[4] = Cur_Time1.Year;
    
    if(Occur_Or_End EQ EVENT_END)//�¼�����
    {
      Len = Event_MultiTimes_Normal_Proc(ID_EVENT_LOSS_CUR, EVENT_END, Flag);
    } 
    else//�¼�����
    {
      if(Old_Loss_Cur_Status.Var != 0)//֮ǰ��ʧѹ�¼�,��Ҫ��֮ǰ���¼�����
        Event_MultiTimes_Normal_Proc(ID_EVENT_LOSS_CUR, EVENT_END, Flag);
      //���¼�����
      Len = Event_MultiTimes_Normal_Proc(ID_EVENT_LOSS_CUR, EVENT_OCCUR, Flag);     
    }
    Old_Loss_Cur_Status.Var = GD_LossCurr_Stat.Byte;
  }
  
  //--------------------------�������⴦��------------------------------------- 
  if(Event_ID EQ ID_EVENT_A_NEG_CURR || Event_ID EQ ID_EVENT_B_NEG_CURR || Event_ID EQ ID_EVENT_C_NEG_CURR)
  {
    *pReturn_Flag = 1;
    
    if(Occur_Or_End EQ EVENT_END)//�¼�����
    {
      Len = Event_MultiTimes_Normal_Proc(ID_EVENT_NEG_CUR, EVENT_END, Flag);
      
      if(Flag EQ EVENT_REAL)
      {
        if(Event_ID EQ ID_EVENT_A_NEG_CURR)//��¼����ʱ��
          Write_Storage_Data(0xE145,Temp,sizeof(Temp));
        else if(Event_ID EQ ID_EVENT_B_NEG_CURR)
          Write_Storage_Data(0xE149,Temp,sizeof(Temp));
        else 
          Write_Storage_Data(0xE14D,Temp,sizeof(Temp));
      }      
    } 
    else//�¼�����
    {
      if(Old_Neg_Cur_Status.Var != 0)//֮ǰ�з����¼�,��Ҫ��֮ǰ���¼�����
        Event_MultiTimes_Normal_Proc(ID_EVENT_NEG_CUR, EVENT_END, Flag);
      //���¼�����
      Len = Event_MultiTimes_Normal_Proc(ID_EVENT_NEG_CUR, EVENT_OCCUR, Flag);
      
      if(Flag EQ EVENT_REAL)
      {      
        if(Event_ID EQ ID_EVENT_A_NEG_CURR)//��¼��ʼʱ��
          Write_Storage_Data(0xE144,Temp,sizeof(Temp));
        else if(Event_ID EQ ID_EVENT_B_NEG_CURR)
          Write_Storage_Data(0xE148,Temp,sizeof(Temp));
        else 
          Write_Storage_Data(0xE14C,Temp,sizeof(Temp)); 
      }      
    }
    Old_Neg_Cur_Status.Var = GD_PwrDir_Stat.Byte;
  }    
  return Len;
}

//�����¼������ĳ�ʼ��
void Grid_Event_Counts_Init()
{
  INT16U Len;
  INT8U i,Err;
  
  mem_set((void *)&Grid_Event_Counts,0,sizeof(Grid_Event_Counts),(void *)&Grid_Event_Counts,sizeof(Grid_Event_Counts));
  SET_STRUCT_SUM(Grid_Event_Counts);
  
  //OS_Sem_Pend(PUB_BUF0_SEM_ID);
  //��ȡʧѹ�ۼƴ������ڴ�
  for(i = 0; i < 3; i++)
  {
    Len = Read_Storage_Data(TOTAL_A_LOSS_VOL + i,(INT8U *)Pub_Buf0,(INT8U *)Pub_Buf0,sizeof(Pub_Buf0),&Err);  
    if(Len > 0)
      mem_cpy((void *)&Grid_Event_Counts.Loss_Vol_Counts[i],(INT8U *)Pub_Buf0 + 5, 4, (void *)&Grid_Event_Counts, sizeof(Grid_Event_Counts));
  }
  //��ȡʧ���ۼƴ������ڴ�
  for(i = 0; i < 3; i++)
  {
    Len = Read_Storage_Data(TOTAL_A_LOSS_CUR + i,(INT8U *)Pub_Buf0,(INT8U *)Pub_Buf0,sizeof(Pub_Buf0),&Err);  
    if(Len > 0)
      mem_cpy((void *)&Grid_Event_Counts.Loss_Vol_Counts[i],(INT8U *)Pub_Buf0 + 5, 4, (void *)&Grid_Event_Counts, sizeof(Grid_Event_Counts));
  }
  //��ȡ�����ۼƴ������ڴ�
  for(i = 0; i < 3; i++)
  {
    Len = Read_Storage_Data(TOTAL_A_NEG_CUR + i,(INT8U *)Pub_Buf0,(INT8U *)Pub_Buf0,sizeof(Pub_Buf0),&Err);  
    if(Len > 0)
      mem_cpy((void *)&Grid_Event_Counts.Neg_Cur_Counts[i],(INT8U *)Pub_Buf0 + 5, 4, (void *)&Grid_Event_Counts, sizeof(Grid_Event_Counts));
  }  
  
  SET_STRUCT_SUM(Grid_Event_Counts);
  //OS_Sem_Post(PUB_BUF0_SEM_ID);
}

//��չ�¼��ۼƴ���
INT16U Extend_Event_Cumu_Proc(INT8U Event_ID,INT8U Occur_Or_End,INT8U Flag,INT8U *pReturn_Flag)
{
  *pReturn_Flag=0;
    
  if(Flag EQ EVENT_REAL && Occur_Or_End EQ EVENT_OCCUR)
  {
    if(CHECK_STRUCT_SUM(Grid_Event_Counts) EQ 0)
    {
      ASSERT(A_WARNING,0);
      Grid_Event_Counts_Init();
    }
    
    if(Event_ID EQ ID_EVENT_A_LOSS_VOLT)//��¼����ʱ��
     Grid_Event_Counts.Loss_Vol_Counts[0]++;
    else if(Event_ID EQ ID_EVENT_B_LOSS_VOLT)
      Grid_Event_Counts.Loss_Vol_Counts[1]++;
    else if(Event_ID EQ ID_EVENT_C_LOSS_VOLT)
      Grid_Event_Counts.Loss_Vol_Counts[2]++;
    else if(Event_ID EQ ID_EVENT_A_LOSS_CURR)
      Grid_Event_Counts.Loss_Cur_Counts[0]++;
    else if(Event_ID EQ ID_EVENT_B_LOSS_CURR)
      Grid_Event_Counts.Loss_Cur_Counts[1]++;
    else if(Event_ID EQ ID_EVENT_C_LOSS_CURR)
      Grid_Event_Counts.Loss_Cur_Counts[2]++;
    else if(Event_ID EQ ID_EVENT_A_NEG_CURR)
      Grid_Event_Counts.Neg_Cur_Counts[0]++;
    else if(Event_ID EQ ID_EVENT_B_NEG_CURR)
      Grid_Event_Counts.Neg_Cur_Counts[1]++;
    else if(Event_ID EQ ID_EVENT_C_NEG_CURR)
      Grid_Event_Counts.Neg_Cur_Counts[2]++;
    else
      return 0;
    
    SET_STRUCT_SUM(Grid_Event_Counts);
  }
  return 0;    
  
}

//��ȡ��չ��������Ŀ
INT16U Extend_Get_Proto_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start, INT16U DstLen,INT8U *pErr)
{
  STORA_DI S_DI;
  INT16U Len;
  INT8U Err, i;
  
  *pErr=NO_ERR;
  
  if(DI EQ 0xE120 || DI EQ 0xE122 || DI EQ 0xE124 || DI EQ 0xE126)//�ܡ�A��B��Cʧ������
  {
    S_DI = TOTAL_TOTAL_LOSS_CUR + (DI - 0xE120)/2;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      mem_cpy(pDst, pDst + 4, 2, pDst_Start, DstLen);
      return 2;
    }
  }
  else if(DI EQ 0xE121 || DI EQ 0xE123 || DI EQ 0xE125 || DI EQ 0xE127)//�ܡ�A��B��Cʧ��ʱ��
  {
    S_DI = TOTAL_TOTAL_LOSS_CUR + (DI - 0xE121)/2;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      //mem_cpy(pDst, pDst + 4, 2, pDst_Start, DstLen);
      return 3;
    }
  } 
  else if(DI EQ 0xE130 || DI EQ 0xE133 || DI EQ 0xE136 || DI EQ 0xE139)//�ܡ�A��B��Cʧѹ����
  {
    S_DI = TOTAL_TOTAL_LOSS_VOL + (DI - 0xE130)/3;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      mem_cpy(pDst, pDst + 4, 2, pDst_Start, DstLen);
      return 2;
    }
  }
  else if(DI EQ 0xE131 || DI EQ 0xE134 || DI EQ 0xE137 || DI EQ 0xE13A)//�ܡ�A��B��Cʧѹʱ��
  {
    S_DI = TOTAL_TOTAL_LOSS_VOL + (DI - 0xE131)/3;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      return 3;			
    }
  }
  else if(DI EQ 0xE132 || DI EQ 0xE135 || DI EQ 0xE138 || DI EQ 0xE13B)//�ܡ�A��B��Cʧѹ�ڼ��ۼƵ���
  {
    S_DI = TOTAL_TOTAL_LOSS_VOL + (DI - 0xE132)/3;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      mem_cpy(pDst, pDst + 8, 4, pDst_Start, DstLen);
      return 4;
    }
  }
  else if(DI EQ 0xE140 || DI EQ 0xE142 || DI EQ 0xE144 || DI EQ 0xE146)//�ܡ�A��B��C�������
  {
    S_DI = TOTAL_TOTAL_NEG_CUR + (DI - 0xE140)/2;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      mem_cpy(pDst, pDst + 4, 2, pDst_Start, DstLen);
      return 2;
    }
  }
  else if(DI EQ 0xE141 || DI EQ 0xE143 || DI EQ 0xE145 || DI EQ 0xE147)//�ܡ�A��B��C����ʱ��
  {
    S_DI = TOTAL_TOTAL_NEG_CUR + (DI - 0xE141)/2;
    Len = Get_Event_Cumu_Proto_Data(S_DI, pDst, pDst_Start, DstLen);
    if(Len >= 8)
    {
      //mem_cpy(pDst, pDst + 4, 2, pDst_Start, DstLen);
      return 3;
    }
  }
  else if(DI EQ 0xE211)//���һ�α��ʱ��ʹ���
  {
    if(Read_Storage_Data(0xB210,pDst,pDst_Start,DstLen,&Err)==0)
      mem_set(pDst, 0, 4, pDst_Start, DstLen);
    if(Read_Storage_Data(0xB212,pDst+4,pDst_Start,DstLen,&Err)==0)
      mem_set(pDst + 4, 0, 2, pDst_Start, DstLen);
    
    return 6;
  }
  else if(DI EQ 0xE212)
  {
    Len = 0;
    //ʧѹ����
    for(i = 0; i < 3; i ++)
    {
      Hex2Bcd(Grid_Event_Counts.Loss_Vol_Counts[i], pDst + Len,2,pDst_Start,DstLen);
      Len += 2;
    }
    //ʧ������
    for(i = 0; i < 3; i ++)
    {
      Hex2Bcd(Grid_Event_Counts.Loss_Cur_Counts[i], pDst + Len,2,pDst_Start,DstLen);
      Len += 2;
    }
    //��������
    for(i = 0; i < 3; i ++)
    {
      Hex2Bcd(Grid_Event_Counts.Neg_Cur_Counts[i], pDst + Len,2,pDst_Start,DstLen);
      Len += 2;
    }    
    return Len;
  }
  else if(DI EQ 0xC119)//��������������
  {
    return 0; 
  }
  else 
    *pErr=PROTOCOL_DI_ERR;
  
  return 0;
}

INT8U Extend_Set_Data_Proc(PROTO_DI DI, INT8U *pSrc, INT16U SrcLen)
{
  INT8U Temp[5];
  INT8U Err;
  INT16U Len;
  INT32U *p;
  INT8U i;
  
  if(DI EQ 0xC119)
  {
    Len = Read_Storage_Data(SDI_CLR_ENG_COUNTS, Temp, Temp, sizeof(Temp), &Err);
    if(Len EQ 1)
    {
      if(Temp[0]>=5)//����5�β�������0
        return PROTOCOL_DATA_ERR;
    }
    
    if(Cur_Energy.Pos_Active[0]>=10000)//��������10KWH��������0
    {
      return PROTOCOL_DATA_ERR;
    }
    
    Set_Def_Energy_Data();//������0
    Temp[0]++;
    Write_Storage_Data(SDI_CLR_ENG_COUNTS, Temp, 1);//����д�������0����
    return NO_ERR;
  }
  else
  {
    if(DI EQ 0xC91F)
      p = (INT32U *)Cur_Energy.Pos_Active;
    else if(DI EQ 0xC92F)
      p = (INT32U *)Cur_Energy.Neg_Active;
    else if(DI EQ 0xC93F)
      p = (INT32U *)Cur_Energy.Quad_Reactive[0];
    else if(DI EQ 0xC94F)
      p = (INT32U *)Cur_Energy.Quad_Reactive[1];
    else if(DI EQ 0xC95F)
      p = (INT32U *)Cur_Energy.Quad_Reactive[2];
    else if(DI EQ 0xC96F)
      p = (INT32U *)Cur_Energy.Quad_Reactive[3];
    else
      return PROTOCOL_DI_ERR;
    
    for(i = 0; i <= MAX_RATES; i ++)
    {
      *(p + i) = Bcd2Hex(pSrc + i*4, 4);
    }
    
    SET_STRUCT_SUM(Cur_Energy);
    return NO_ERR;//PROTOCOL_DI_ERR;
  }
  
  return PROTOCOL_DATA_ERR;
}

INT16U Extend_Get_Single_Proto_Data_Proc(PROTO_DI DI,INT8U *pDst, INT8U *pDst_Start, INT16U DstLen, INT8U *pErr)
{
  *pErr = PROTOCOL_DI_ERR;
  return 0;    
  
}

void Extend_Init()
{
  Grid_Event_Counts_Init();  
}
#endif
#undef EXTEND_GD_C