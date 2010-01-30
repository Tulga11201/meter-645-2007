#define SYS_MEMORY_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H22"
#endif

//#undef Debug_Print
//#define Debug_Print(...)
//#define Debug_Print _Debug_Print

//读写存储函数中的喂狗
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
  
  if(OS_Get_Cur_Task_Num() EQ 1 || CLEAR_END_FLAG!=Clear_Flag.Flag)//当前只有一个任务，也就是只有主任务在进行初始化的情况下清狗
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
  else//所有任务都已经创建运行，此时判断一分钟内喂狗多少次?
  {
    if(Sec.Var!=Cur_Time1.Sec)//时间有变化，说明程序让出来了，给其他任务执行
    {
      Clr_Dog_Counts0.Var=0;
      Sec.Var=Cur_Time1.Sec;
    }
    
    Clr_Ext_Inter_Dog();    //清CPU外部看门狗 
    Clear_Task_Dog();  
    //一分钟以内连续读写超过1000次，说明已经锁死在读写函数中了,
    Clr_Dog_Counts0.Var++;

    if(Clr_Dog_Counts0.Var > MAX_INIT_CLR_DOG_COUTS)
    {
      ASSERT_FAILED();
      Debug_Print("WR_Memory_Clear_Dog Error,soft reset");
      Soft_Reset();
    }
  }
  
  //同一个任务内连续读写超过MAX_INIT_CLR_DOG_COUTS次，说明已经锁死了
  if(OS_Get_Cur_Task_ID()!=Task_ID.Var)//不同的任务执行读写操作，说明没有锁死
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

//物理存储器测试,对每个物理存储器读写一个字节进行测试
INT8U Check_PHY_Mem()
{
  INT8U Re, i, Test[5];
  INT8U Bak;

  TRACE();

  Debug_Print("----PHY_MEM Write & Read Check!----");
  Re = 1;
  for(i = 0; i < S_NUM(Sys_PHY_Mem); i++)
  {
    Read_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1, Test, 1);//先将原字节备份
    Bak = Test[0];
    Test[0] = 0x5A;
    Write_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1);//写入测试字节
    Test[0] = 0x00;
    Read_PHY_Mem(Sys_PHY_Mem[i].MemNo, 0, Test, 1, Test, 1);//读出测试字节
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

//检查内存分布是否合理,主要是检查逻辑存储器与物理存储器之间的映射
//1表示检查成功
//MEM_MAP_ERR表示检查失败
INT8U Check_LOG_Mem_Map()
{
  INT8U i, j, Re;
  INT32U Size;
  INT8U Imp_Flag;

  TRACE();

  Re = 1;

  Debug_Print("----PHY_LOG_MEM Map Check Start!----");
  //逐个物理内存遍历
  for(i = 0; i < S_NUM(Sys_PHY_Mem); i++)
  {
    Debug_Print("PHY Mem %d size=%ld", i, Sys_PHY_Mem[i].Mem_Size);
    Size = 0;
    //检查每个逻辑内存对应的物理内存分布是否合理
    for(j = 0; j < S_NUM(Sys_LOG_Mem); j++)
    {
      //第i个逻辑内存使用了该物理内存
      if(Sys_LOG_Mem[j].PHY_Mem_Info.MemNo EQ Sys_PHY_Mem[i].MemNo)
      {
        Imp_Flag = Get_LOG_Mem_ImpFlag( Sys_LOG_Mem[j].LOG_MemNo);
        
        Debug_Print("----LOG Mem %3d,Imp_%x,Size=%7ld,%7ld-->%7ld ", Sys_LOG_Mem[j].LOG_MemNo, Imp_Flag, Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size, \
                    Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr, Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr + Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size);

        //分配的物理内存起始地址应该在，已分配的空间外
        if(Sys_LOG_Mem[j].PHY_Mem_Info.MemNo != NULL_LOG_MEM && \
           Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Addr != Size)//起始地址不应在已经分配的范围内
        {
          //ASSERT_FAILED();
          Debug_Print("LOG Mem %d Map Error", Sys_LOG_Mem[j].LOG_MemNo);
          Re &= 0;
        }
        //计算该物理内存内已分配的空间总和
        Size += Sys_LOG_Mem[j].PHY_Mem_Info.Mem_Size;
      }
    }
    if(Size > Sys_PHY_Mem[i].Mem_Size)//总的大小不应该超过物理内存大小
    {
      Debug_Print("PHY Mem %d not enough space, All LOG_Mem size=%d", i, Size);
      Re &= 0;
    }
  }
  Debug_Print("----PHY_LOG_MEM Map Check End!----");
  return Re;
}

//获取某个逻辑存储器的大小
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

//获取某个物理存储器的大小
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

//从物理存储器读数据
//MemNo，物理存储器编号
//Offset,物理存储器内的偏移
//pDst, 写的源数据
//RD_Len,需要读取的数据长度 
//pDst_Start,目标缓冲区的界定起始地址
//DstLen，目标缓冲区的界定长度
//返回结果:1表示读取成功
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
        Head = *((INT8U *) pDst - 1);//先保存目标缓冲区的头和尾,读完后再判断头和尾是否发生变化,保证读不会产生溢出
        Tail = *((INT8U *) pDst + RD_Len);
        
        for(j = 0; j < MAX_IIC_ERR_RETRY; j ++) //连续读5次
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
          
          OS_TimeDly_Ms(200); //延时200ms
        }
        
        ReNew_Err_Code(DIS_MEM_ERR);    
      }
    }
  }
  ASSERT_FAILED();
  return 0;
}

//向物理存储器写数据
//MemNo，物理存储器编号
//Offset,物理存储器内的偏移
//pSrc, 写的源数据
//写的源数据长度
//返回结果:
//1表示写成功
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
        Head = *((INT8U *) pSrc);//先保存源缓冲区的头和尾,读完后再判断头和尾是否发生变化,保证写不会破坏源数据
        Tail = *((INT8U *) pSrc + SrcLen - 1);
        
        for(j = 0; j < MAX_IIC_ERR_RETRY; j ++) //连续写5次
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
  return 0;//物理存储器序号错
}

//从逻辑存储器读数据
//MemNo，逻辑存储器编号
//Offset,逻辑存储器内的偏移
//pSrc, 写的源数据
//写的源数据长度
//返回结果:1表示写成功，0表示写失败
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
        //读物理存储器中的数据
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
        return 0;//逻辑存储器地址错
      }
    }
  }
  ASSERT_FAILED();
  return 0;//逻辑存储器序号错
}

//向逻辑存储器写数据
//MemNo，逻辑存储器编号
//Offset,逻辑存储器内的偏移
//pSrc, 写的源数据
//写的源数据长度
//返回结果:Re表示写成功，其他表示写失败
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

//获取物理存储器和逻辑存储器信息的校验信息
INT32U Get_Sys_Mem_Info_CS()
{
  INT32U CS0,CS1;
  
  OS_Set_Sum((INT8U *)Sys_PHY_Mem, sizeof(Sys_PHY_Mem), &CS0, sizeof(CS0), &CS0, sizeof(CS0)); 
  OS_Set_Sum((INT8U *)Sys_LOG_Mem, sizeof(Sys_LOG_Mem), &CS1, sizeof(CS1), &CS1, sizeof(CS1)); 

  return CS0 + CS1; 
}
#undef SYS_MEMORY_C

