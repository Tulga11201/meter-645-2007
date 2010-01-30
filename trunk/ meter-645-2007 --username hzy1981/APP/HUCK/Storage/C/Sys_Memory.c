#define SYS_MEMORY_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H22"
#endif

//#undef Debug_Print
//#define Debug_Print(...)
//#define Debug_Print _Debug_Print

//��д�洢�����е�ι��
void WR_Memory_Clear_Dog()
{
  INT8U Re; 
  static S_Int16U Clr_Dog_Counts={CHK_BYTE,0,CHK_BYTE};  
  static S_Int32U Clr_Dog_Counts0={CHK_BYTE,0,CHK_BYTE};
  static S_Int32U Clr_Dog_Counts1={CHK_BYTE,0,CHK_BYTE};
  static S_Int8U Sec={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int8U Task_ID={CHK_BYTE,0xFF,CHK_BYTE};
  
  Re=1;
  Re &= CHECK_STRUCT_VAR(Clr_Dog_Counts);
  Re &= CHECK_STRUCT_VAR(Clr_Dog_Counts0);
  Re &= CHECK_STRUCT_VAR(Clr_Dog_Counts1);
  Re &= CHECK_STRUCT_VAR(Sec);
  Re &= CHECK_STRUCT_VAR(Task_ID);
  
  if(Re!=1)
    ASSERT_FAILED();
  
  if(OS_Get_Cur_Task_Num() EQ 1 || CLEAR_END_FLAG!=Clear_Flag.Flag)//��ǰֻ��һ������Ҳ����ֻ���������ڽ��г�ʼ����������幷
  {
    if(Clr_Dog_Counts.Var<=MAX_INIT_CLR_DOG_COUTS)
    {
      Clr_Ext_Inter_Dog();
      Clr_Dog_Counts.Var++;
    }
    else
    {
      ASSERT_FAILED();
      Soft_Reset();
    }
  }
  else//���������Ѿ��������У���ʱ�ж�һ������ι�����ٴ�?
  {
    if(Sec.Var!=Cur_Time1.Sec)//ʱ���б仯��˵�������ó����ˣ�����������ִ��
    {
      Clr_Dog_Counts0.Var=0;
      Sec.Var=Cur_Time1.Sec;
    }
    
    Clr_Ext_Inter_Dog();    //��CPU�ⲿ���Ź� 
    Clear_Task_Dog();  
    //һ��������������д����1000�Σ�˵���Ѿ������ڶ�д��������,
    Clr_Dog_Counts0.Var++;

    if(Clr_Dog_Counts0.Var > MAX_INIT_CLR_DOG_COUTS)
    {
      ASSERT_FAILED();
      Debug_Print("WR_Memory_Clear_Dog Error,soft reset");
      Soft_Reset();
    }
  }
  
  //ͬһ��������������д����MAX_INIT_CLR_DOG_COUTS�Σ�˵���Ѿ�������
  if(OS_Get_Cur_Task_ID()!=Task_ID.Var)//��ͬ������ִ�ж�д������˵��û������
  {
    Task_ID.Var=OS_Get_Cur_Task_ID();
    Clr_Dog_Counts1.Var=0;
  }
  else
  {
    Clr_Dog_Counts1.Var++;
    if(Clr_Dog_Counts1.Var > MAX_INIT_CLR_DOG_COUTS)
    {
      ASSERT_FAILED();
      Soft_Reset();
    }
  }
}

//����洢������,��ÿ������洢����дһ���ֽڽ��в���
INT8U Check_PHY_Mem()
{
  INT8U Re, i, Test[5];
  INT8U Bak;

  TRACE();

  Debug_Print("----PHY_MEM Write & Read Check!----");
  Re = 1;
  for(i = 0; i < S_NUM(Sys_PHY_Mem); i++)
  {
    Read_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1, Test, 1);//�Ƚ�ԭ�ֽڱ���
    Bak = Test[0];
    Test[0] = 0x5A;
    Write_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1);//д������ֽ�
    Test[0] = 0x00;
    Read_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1, Test, 1);//���������ֽ�
    if(Test[0] != 0x5A)
    {
      Debug_Print("PHY Mem%d write && read SelfCheck failed!", Sys_PHY_Mem[i].MemNo);
      Test[0] = Bak;
      Write_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1);
      Re &= 0;
    }
    Test[0] = Bak;
    Write_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1);
  }
  return Re;
}

//����ڴ�ֲ��Ƿ����,��Ҫ�Ǽ���߼��洢��������洢��֮���ӳ��
//1��ʾ���ɹ�
//MEM_MAP_ERR��ʾ���ʧ��
INT8U Check_LOG_Mem_Map()
{
  INT8U i, j, Re;
  INT32U Size;
  INT8U Imp_Flag;

  TRACE();

  Re = 1;

  Debug_Print("----PHY_LOG_MEM Map Check Start!----");
  //��������ڴ����
  for(i = 0; i < S_NUM(Sys_PHY_Mem); i++)
  {
    Debug_Print("PHY Mem %d size=%ld", i, Sys_PHY_Mem[i].Mem_Size);
    Size = 0;
    //���ÿ���߼��ڴ��Ӧ�������ڴ�ֲ��Ƿ����
    for(j = 0; j < S_NUM(Sys_LOG_Mem); j++)
    {
      //��i���߼��ڴ�ʹ���˸������ڴ�
      if(Sys_LOG_Mem[j].PHY_Mem_Info.MemNo EQ Sys_PHY_Mem[i].MemNo)
      {
        Imp_Flag = Get_LOG_Mem_ImpFlag( Sys_LOG_Mem[j].LOG_MemNo);
        
        Debug_Print("----LOG Mem %3d,Imp_%x,Size=%7ld,%7ld-->%7ld ", Sys_LOG_Mem[j].LOG_MemNo, Imp_Flag, Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size, \
                    Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr, Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr + Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size);

        //����������ڴ���ʼ��ַӦ���ڣ��ѷ���Ŀռ���
        if(Sys_LOG_Mem[j].PHY_Mem_Info.MemNo != NULL_LOG_MEM && \
           Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr != Size)//��ʼ��ַ��Ӧ���Ѿ�����ķ�Χ��
        {
          //ASSERT_FAILED();
          Debug_Print("LOG Mem %d Map Error", Sys_LOG_Mem[j].LOG_MemNo);
          Re &= 0;
        }
        //����������ڴ����ѷ���Ŀռ��ܺ�
        Size += Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size;
      }
    }
    if(Size > Sys_PHY_Mem[i].Mem_Size)//�ܵĴ�С��Ӧ�ó��������ڴ��С
    {
      Debug_Print("PHY Mem %d not enough space, All LOG_Mem size=%d", i, Size);
      Re &= 0;
    }
  }
  Debug_Print("----PHY_LOG_MEM Map Check End!----");
  return Re;
}

//��ȡĳ���߼��洢���Ĵ�С
INT32U Get_LOG_Mem_Size(INT8U MemNo)
{
  INT8U i;

  TRACE();

  for(i = 0; i < S_NUM(Sys_LOG_Mem); i++)
  {
    if(Sys_LOG_Mem[i].LOG_MemNo EQ MemNo)
    {
      return Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Size;
    }
  }
  ASSERT_FAILED();
  return 0;
}

//��ȡĳ������洢���Ĵ�С
INT32U Get_PHY_MEM_Size(INT8U MemNo)
{
  INT8U i;

  TRACE();

  for(i = 0; i < sizeof(Sys_PHY_Mem) / sizeof(S_PHY_Mem_Info); i++)
  {
    if(Sys_PHY_Mem[i].MemNo EQ MemNo)
    {
      return Sys_PHY_Mem[i].Mem_Size;
    }
  }
  ASSERT_FAILED();
  return 0;
}

//������洢��������
//MemNo������洢�����
//Offset,����洢���ڵ�ƫ��
//pDst, д��Դ����
//RD_Len,��Ҫ��ȡ�����ݳ��� 
//pDst_Start,Ŀ�껺�����Ľ綨��ʼ��ַ
//DstLen��Ŀ�껺�����Ľ綨����
//���ؽ��:1��ʾ��ȡ�ɹ�
INT8U Read_PHY_Mem(INT8U MemNo, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen)
{
  INT8U i, j;
  INT8U Re;
  INT8U Head, Tail;

  TRACE();

  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst_Start + RD_Len <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  for(i = 0; i < S_NUM(Sys_PHY_Mem); i++)
  {
    if(Sys_PHY_Mem[i].MemNo EQ MemNo)
    {
      if(Offset + RD_Len <= Sys_PHY_Mem[i].Mem_Size)
      {
        Head = *((INT8U *) pDst - 1);//�ȱ���Ŀ�껺������ͷ��β,��������ж�ͷ��β�Ƿ����仯,��֤������������
        Tail = *((INT8U *) pDst + RD_Len);
        
        for(j = 0; j < MAX_IIC_ERR_RETRY; j ++) //������5��
        {
          Clear_All_Dog();
          
          Re = Read_PHY_Mem_PUCK(MemNo, Offset, pDst, RD_Len, pDst_Start, DstLen);
          if(Head != *((INT8U *) pDst - 1) || Tail != *((INT8U *) pDst + RD_Len))
          {
            ASSERT_FAILED();
            Debug_Print("Read_PHY_Mem Error!");
          }
          if(1 EQ Re)
            return 1;
          
          OS_TimeDly_Ms(200); //��ʱ200ms
        }
        
        ReNew_Err_Code(DIS_MEM_ERR);    
      }
    }
  }
  ASSERT_FAILED();
  return 0;
}

//������洢��д����
//MemNo������洢�����
//Offset,����洢���ڵ�ƫ��
//pSrc, д��Դ����
//д��Դ���ݳ���
//���ؽ��:
//1��ʾд�ɹ�
INT8U Write_PHY_Mem(INT8U MemNo, INT32U Offset, void* pSrc, INT16U SrcLen)
{
  INT8U i, j;
  INT8U Re;
  INT8U Head, Tail;

  TRACE();

  for(i = 0; i < S_NUM(Sys_PHY_Mem); i++)
  {
    if(Sys_PHY_Mem[i].MemNo EQ MemNo)
    {
      if(Offset + SrcLen <= Sys_PHY_Mem[i].Mem_Size)
      {
        Head = *((INT8U *) pSrc);//�ȱ���Դ��������ͷ��β,��������ж�ͷ��β�Ƿ����仯,��֤д�����ƻ�Դ����
        Tail = *((INT8U *) pSrc + SrcLen - 1);
        
        for(j = 0; j < MAX_IIC_ERR_RETRY; j ++) //����д5��
        {    
          Clear_All_Dog();
          
          Re = Write_PHY_Mem_PUCK(MemNo, Offset, pSrc, SrcLen);
          if(Head != *((INT8U *) pSrc) || Tail != *((INT8U *) pSrc + SrcLen - 1))
          {
            ASSERT_FAILED();
            Debug_Print("Write_PHY_Mem Error!");
          }
          if(1 EQ Re)
            return 1;
          
          OS_TimeDly_Ms(200); 
        }
        
        ReNew_Err_Code(DIS_MEM_ERR);         
      }
    }
  }
  ASSERT_FAILED();
  return 0;//����洢����Ŵ�
}

//���߼��洢��������
//MemNo���߼��洢�����
//Offset,�߼��洢���ڵ�ƫ��
//pSrc, д��Դ����
//д��Դ���ݳ���
//���ؽ��:1��ʾд�ɹ���0��ʾдʧ��
INT8U Read_LOG_Mem(INT8U MemNo, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen)
{
  INT8U i, Re;

  TRACE();

  Clr_Ext_Inter_Dog();//WR_Memory_Clear_Dog();
    
  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst_Start + RD_Len <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  for(i = 0; i < sizeof(Sys_LOG_Mem) / sizeof(S_LOG_Mem_Info); i++)
  {
    if(Sys_LOG_Mem[i].LOG_MemNo EQ MemNo)
    {
      if(Offset + RD_Len <= Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Size)
      {
        //������洢���е�����
        Re = Read_PHY_Mem(Sys_LOG_Mem[i].PHY_Mem_Info.MemNo,\
        Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Addr + Offset,\
        pDst,\
        RD_Len,\
        pDst_Start,\
        DstLen);
        if(Re EQ 1)
          return Re;
        else
        {
          ASSERT_FAILED();
          return 0;
        }
      }
      else
      {
        ASSERT_FAILED();
        return 0;//�߼��洢����ַ��
      }
    }
  }
  ASSERT_FAILED();
  return 0;//�߼��洢����Ŵ�
}

//���߼��洢��д����
//MemNo���߼��洢�����
//Offset,�߼��洢���ڵ�ƫ��
//pSrc, д��Դ����
//д��Դ���ݳ���
//���ؽ��:Re��ʾд�ɹ���������ʾдʧ��
INT8U Write_LOG_Mem(INT8U MemNo, INT32U Offset, void* pSrc, INT16U SrcLen)
{
  INT8U i, Re;

  TRACE();

  Clr_Ext_Inter_Dog();//WR_Memory_Clear_Dog();
    
  for(i = 0; i < S_NUM(Sys_LOG_Mem); i++)
  {
    if(Sys_LOG_Mem[i].LOG_MemNo EQ MemNo)
    {
      if(Offset + SrcLen < Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Size)
      {
        Re = Write_PHY_Mem(Sys_LOG_Mem[i].PHY_Mem_Info.MemNo,\
        Sys_LOG_Mem[i].PHY_Mem_Info.Mem_Addr + Offset,\
        pSrc,\
        SrcLen);
        if(Re EQ 1)
          return Re;
        else
        {
          ASSERT_FAILED();
          return 1;
        }
      }
      else
      {
        ASSERT_FAILED();
        return 0;
      }
    }
  }
  return 0;
}

//��ȡ����洢�����߼��洢����Ϣ��У����Ϣ
INT32U Get_Sys_Mem_Info_CS()
{
  INT32U CS0,CS1;
  
  OS_Set_Sum((INT8U *)Sys_PHY_Mem, sizeof(Sys_PHY_Mem), &CS0, sizeof(CS0), &CS0, sizeof(CS0)); 
  OS_Set_Sum((INT8U *)Sys_LOG_Mem, sizeof(Sys_LOG_Mem), &CS1, sizeof(CS1), &CS1, sizeof(CS1)); 

  return CS0 + CS1; 
}
#undef SYS_MEMORY_C

