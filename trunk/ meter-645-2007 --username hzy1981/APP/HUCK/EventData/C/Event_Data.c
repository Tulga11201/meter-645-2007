#define EVENT_DATA_C
#include <includes.h>

//检查当前事件是否在发生,Event_ID可以为总一类事件
INT8U Check_Event_Occuring(INT8U Event_ID)
{
  if(Check_Total_Event_ID(Event_ID))
  {
    if(Get_Event_Total_Occuring_Singles(Event_ID) != 0)
      return 1;
    else
      return 0;
  }
  else
  {
    if(Read_Event_Status(Event_ID) EQ 1)
      return 1;
    else
      return 0;
  }
}

#undef Debug_Print
#define Debug_Print _Debug_Print
//全失压次数和时间统计
//上电后调用该函数一次，Counts表示掉电期间失压总次数，Mins表示掉电期间失压总分钟数
void All_Loss_Vol_Counts_Time_Proc(INT32U Counts,INT32U Mins)
{
    //INT16U Re;
    //INT8U Temp[20];
    INT32U Counts0,Mins0;
    INT16U Len;

    TRACE();
    
    Debug_Print("All_Loss_Vol Counts:%ld, Mins:%ld", Counts, Mins);	
	
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = Read_Storage_Data(EC_DI(0x03050000), (void *)Pub_Buf0, (void *)Pub_Buf0, sizeof(Pub_Buf0));
    if(Len EQ 0)
    {
      ASSERT_FAILED();
      Len = Read_Storage_Data(EC_DI(0x03050001), (void *)Pub_Buf0, (void *)Pub_Buf0, sizeof(Pub_Buf0));
    }
    
    if(Len > 0)
    {
      mem_cpy(&Counts0, (INT8U *)Pub_Buf0 + 5, 4, &Counts0, sizeof(Counts0));
      mem_cpy(&Mins0, (INT8U *)Pub_Buf0 + 9, 4, &Mins0, sizeof(Mins0));
    }   
    else
    {
      Counts0 = 0;
      Mins0 = 0;
    }
    
    Counts0 += Counts;
    Mins0 += Mins;
    
    Debug_Print("Total_All_Loss_Vol Counts:%ld, Mins:%ld", Counts0, Mins0);
    
    mem_cpy((INT8U *)Pub_Buf0 + 5, &Counts0, 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
    mem_cpy((INT8U *)Pub_Buf0 + 9, &Mins0, 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
    
    Write_Storage_Data(EC_DI(0x03050000), (INT8U *)Pub_Buf0, 13);
    Write_Storage_Data(EC_DI(0x03050001), (INT8U *)Pub_Buf0, 13);
    
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
    
/*
    Re=Read_Storage_Data(0x03050000,Temp,Temp,sizeof(Temp));
    if(0 EQ Re)
    {
            ASSERT(0);
            Counts0 = Counts;
            Mins0 = Mins;
    }
    else
    {
            Counts0 = Bcd2Hex(Temp, 3);
            Mins0 = Bcd2Hex(Temp + 3, 3);

            Counts0 += Counts;//Bcd2Hex(Temp + 5, 4);
            Mins0 += Mins;//Bcd2Hex(Temp + 9, 4);
            
            Hex2Bcd(Counts0, Temp, 3, Temp, sizeof(Temp));
            Hex2Bcd(Mins0, Temp + 3, 3, Temp, sizeof(Temp));
    }
    
    
    Re=Write_Storage_Data(0x03050000, (void *)&Temp, 6);
    ASSERT(1 EQ Re);
*/	
	//----------------------------------
	//对总的失压次数和时间进行统计
	if(Get_Total_Event_ID(ID_EVENT_ALL_LOSS_VOLT) EQ ID_EVENT_TOTAL_LOSS_VOL)//全失压的时间和次数是否进入总失压和次数?
	{
		OS_Mutex_Pend(PUB_BUF0_SEM_ID);
		Len = Read_Storage_Data(EC_DI(0x10000101), (void *)Pub_Buf0, (void *)Pub_Buf0, sizeof(Pub_Buf0));
		if(Len > 0)
		{
			mem_cpy(&Counts0, (INT8U *)Pub_Buf0 + 5, 4, &Counts0, sizeof(Counts0));
			mem_cpy(&Mins0, (INT8U *)Pub_Buf0 + 9, 4, &Mins0, sizeof(Mins0));
			
			Counts0 += Counts;
			Mins0 += Mins;
			
			Debug_Print("Total_Loss_Vol Counts:%ld, Mins:%ld", Counts0, Mins0);
			
			mem_cpy((INT8U *)Pub_Buf0 + 5, &Counts0, 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
			mem_cpy((INT8U *)Pub_Buf0 + 9, &Mins0, 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
			
			Write_Storage_Data(EC_DI(0x10000101), (INT8U *)Pub_Buf0, Len);
		}
		OS_Mutex_Post(PUB_BUF0_SEM_ID);
	}
}

//全失压数据累加处理
//Start_Time表示起始时间,Start_Time[0]->Start_Time[4]表示分、时、日、月、年,BCD码
//End_Time表示终止时间,End_Time[0]->End_Time[4]表示分、时、日、月、年，BCD码
//上电后，对上电前的前N(N<=10)次全失压，调用该函数N次
void All_Loss_Vol_Data_Proc(INT8U Start_Time[],INT8U End_Time[])
{
    TRACE();

    Debug_Print("All_Loss_Vol Start_Time:%x-%x-%x %x:%x, End_Time:%x-%x-%x %x:%x",\
            Start_Time[4],Start_Time[3],Start_Time[2],Start_Time[1],Start_Time[0],\
            End_Time[4],End_Time[3],End_Time[2],End_Time[1],End_Time[0]);
    
    All_Loss_Vol_Time.Start_Time[0] = 0;
    All_Loss_Vol_Time.End_Time[0] = 0;
    mem_cpy((INT8U *)All_Loss_Vol_Time.Start_Time + 1, Start_Time, 5, (void *)All_Loss_Vol_Time.Start_Time,sizeof(All_Loss_Vol_Time.Start_Time));
    mem_cpy((INT8U *)All_Loss_Vol_Time.End_Time + 1, End_Time, 5, (void *)All_Loss_Vol_Time.End_Time,sizeof(All_Loss_Vol_Time.End_Time));

    SET_STRUCT_SUM(All_Loss_Vol_Time);
    
    Event_Separate_Proc(ID_EVENT_ALL_LOSS_VOLT, EVENT_OCCUR, EVENT_REAL);
    Event_Separate_Proc(ID_EVENT_ALL_LOSS_VOLT, EVENT_END, EVENT_REAL);
    
    Write_Storage_Data(SDI_LAST_LOSS_VOL_OCCUR_TIME, (void *)All_Loss_Vol_Time.Start_Time, 6);//最近一次全失压发生和结束时刻
    Write_Storage_Data(SDI_LAST_LOSS_VOL_END_TIME, (void *)All_Loss_Vol_Time.End_Time, 6);
}
#undef Debug_Print
#define Debug_Print(...)

void Store_Op_ID(INT8U *pDst, INT8U *pDst_Start, INT8U DstLen)
{
  DIS_PD_INT;
  mem_cpy(pDst, (void *)Operator_ID.Op_ID, sizeof(Operator_ID.Op_ID), pDst_Start, DstLen);
  mem_set((void *)Operator_ID.Op_ID, 0xFF, sizeof(Operator_ID.Op_ID), (void *)Operator_ID.Op_ID, sizeof(Operator_ID.Op_ID));
  SET_STRUCT_SUM(Event_Data._Operator_ID);
  SET_STRUCT_SUM(Event_Data);
  EN_PD_INT;  
}

void Restore_Op_ID(INT8U *pSrc)
{
  DIS_PD_INT;
  mem_cpy((void *)Operator_ID.Op_ID, pSrc, sizeof(Operator_ID.Op_ID), (void *)Operator_ID.Op_ID, sizeof(Operator_ID.Op_ID));
  SET_STRUCT_SUM(Event_Data._Operator_ID);
  SET_STRUCT_SUM(Event_Data);
  EN_PD_INT;
}

// 事件处理函数
//注意：该函数调用Read_Event_Status查询某个事件状态时，是该事件发生前的状态
//例如 某事件发生，调用该函数处理，则该函数内调用Read_Event_Status时返回0
// 相反，某事件结束，调用该函数处理，则该函数内调用Read_Event_Status时返回1
void Event_Data_Proc(INT8U Event_ID,INT8U Occur_Or_End)
{
  INT8U Total_Event_ID;
  INT8U Clr_Demand_Man_Flag;
  INT8U Op_ID[4];
  
  _Debug_Print("\r\n++++++++++Event Data Proc,ID:%d,%s++++++++++",Event_ID,(Occur_Or_End EQ EVENT_OCCUR)?"Occur":"End");
  
  Clr_Demand_Man_Flag = 0;
  if(Event_ID EQ ID_EVENT_CLR_DEMAND_MAN)//手动清需量转为通信清需量，同一事件ID处理,但是手动清需量的操作者ID为全FF
  {
    Clr_Demand_Man_Flag = 1;
    Event_ID = ID_EVENT_CLR_DEMAND_COM;
    //当前操作者id先备份
    Store_Op_ID(Op_ID, Op_ID, sizeof(Op_ID));
  }
  else if(Event_ID EQ ID_EVENT_RELAY_ON || Event_ID EQ ID_EVENT_RELAY_OFF) //拉合闸，本地拉合闸记录操作者代码为FF
  {
    if(Relay_Status.Switch_Cause EQ S_OFF_PREPAID) //前一次是本地拉闸
    {
      Store_Op_ID(Op_ID, Op_ID, sizeof(Op_ID));      
    }
  }
  
  Event_Cumu_Proc(Event_ID,Occur_Or_End,EVENT_REAL);
  
  Total_Event_ID = Get_Total_Event_ID(Event_ID);//本事件对应的总计数也要处理
  if(Total_Event_ID != NULL_EVENT_ID)
  {
    Debug_Print("Total Event Proc");
    Event_Cumu_Proc(Total_Event_ID,Occur_Or_End,EVENT_REAL);
  }
  Event_Separate_Proc(Event_ID,Occur_Or_End,EVENT_REAL);
 
  //恢复操作者ID
  if(Clr_Demand_Man_Flag EQ 1)
  {
    Restore_Op_ID(Op_ID);
  }
  else if(Event_ID EQ ID_EVENT_RELAY_ON || Event_ID EQ ID_EVENT_RELAY_OFF)
  {
    if(Relay_Status.Switch_Cause EQ S_OFF_PREPAID) //前一次是本地拉闸    
    {
      Restore_Op_ID(Op_ID);      
    }    
  }
  
  Debug_Print("++++++++++Event Data Proc:End++++++++++\r\n");
  OS_TimeDly_Ms(10); //延迟10ms
}


//清除事件
void Clear_Event_Data(PROTO_DI Clr_PDI)
{
  INT8U Re;

  Set_Clear_Data_Result(0);
  
  if(Check_Clear_Data_Authority() EQ 0)
    return;
  
  if(CLEAR_EVENT_FLAG!=Check_Clear_Data_Flag() &&
     CLEAR_ALL_FLAG!=Check_Clear_Data_Flag())
    return;
  Debug_Print("Clear_Event_Data, Clr_PDI = 0x%lx", Clr_PDI);
  
  if(Clr_PDI EQ 0xFFFFFFFF)
  {
    DISP_CLR_DATA_INFO;
    Clear_Event_Cumu_Data();
    Clear_Event_Separate_Data();
    Clear_VolStat_Data();
    Clr_All_Event_Sram(); //清除内存中的事件数据，重新开始判定事件
    Set_Clear_Data_Result(1);
  }
  else
  {
    Re = Clear_One_Event_Data((Clr_PDI & 0xFFFFFF00) | 0x01);
    if(Re EQ 0) //没有清除成功则将Clear_Event_PDI清零
    {
      SET_STRUCT_SUM(Event_Data);  
      Set_Clear_Data_Result(0);
    }
    else
      Set_Clear_Data_Result(1);
  }
}

//通知通信流程，清除操作完成
//内部将Clear_Flag.Flag置成CLEAR_END_FLAG
//从而使下次调用Check_Clear_Data_Flag返回CLEAR_END_FLAG
void Clear_Data_End()
{
  INT8U Re;
  Re=CHECK_STRUCT_SUM(Clear_Flag);
  ASSERT(1 EQ Re);
  Clear_Flag.Flag=CLEAR_END_FLAG;
  SET_STRUCT_SUM(Clear_Flag);
}

//设置默认的事件参数与数据
void Set_Def_Event_Data()
{
  Set_Def_Event_Cumu_Data();
  Set_Def_Event_Separate_Data();
}

//掉电保存事件数据
void Save_Event_PD_Data()
{
  TRACE();
  
  PwrOff_Proc_PUCK();
  if(CHECK_STRUCT_SUM(Event_Data))
  {
    mem_cpy((void *)&Event_Data.Meter_Instant_Status, (void *)&Meter_Instant_Status, sizeof(Meter_Instant_Status),\
            (void *)&Event_Data.Meter_Instant_Status, sizeof(Event_Data.Meter_Instant_Status));
    
    mem_cpy((void *)&Event_Data.Bat_Work_Status, (void *)&Bat_Work_Status, sizeof(Bat_Work_Status),\
            (void *)&Event_Data.Bat_Work_Status, sizeof(Event_Data.Bat_Work_Status));
        
    mem_cpy((void *)&Event_Data.Not_Even_Data, (void *)&Not_Even_Data_PUCK, sizeof(Not_Even_Data_PUCK),\
            (void *)&Event_Data.Not_Even_Data, sizeof(Event_Data.Not_Even_Data));
    
    mem_cpy((void *)&Event_Data.Prg_Key_Status, (void *)&Prg_Key_Status, sizeof(Prg_Key_Status),\
            (void *)&Event_Data.Prg_Key_Status, sizeof(Event_Data.Prg_Key_Status));
    
    if(Get_Meter_Hard_Mode()==MODE_TEST) //自检模式掉电合闸
      Event_Data.Relay_Status = SWITCH_ON;
    else  
      Event_Data.Relay_Status = Relay_Status.Switch_Status;
    
    Event_Data.PD_Flag = 1;
    SET_STRUCT_SUM(Event_Data);
    
    Write_Storage_Data(_SDI_EVENT_DATA_PD, (void *)&Event_Data, sizeof(Event_Data));
  }
  else
    Debug_Print("Save Event_PD_Data CS Error!!!");
}

//清除Event_Data内存数据，但是不清楚Clear_Event_PDI和Operator_ID
void Clr_Event_PD_Ram_Data()
{
  DIS_PD_INT;

  //因为操作者代码和清事件的DI等都是清完后事件记录 需要的，因此，需要保留
  mem_set((void *)&Event_Data, 0, S_OFF(S_Event_Data, _Clear_Event_PDI), (void *)&Event_Data, sizeof(Event_Data));
  
  SET_STRUCT_SUM(Event_Data.Meter_Instant_Status);
  SET_STRUCT_SUM(Event_Data.Bat_Work_Status);
  SET_STRUCT_SUM(Event_Data._Demand_Exceed_Limit);
  SET_STRUCT_SUM(Event_Data._Operator_ID);
  SET_STRUCT_SUM(Event_Data._PSW_Err_Info);
  SET_STRUCT_SUM(Event_Data._Last_Freeze_Time);
  SET_STRUCT_SUM(Event_Data._Last_Adj_Time);  
  mem_cpy((void *)&Event_Data.Time,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Event_Data.Time,sizeof(Event_Data.Time));
  
  Clr_Prog_Record_Ram();
  
  Event_Data.PD_Flag = 0;//没有发生过掉电  
  SET_STRUCT_SUM(Event_Data);

  EN_PD_INT;    
}

//清除掉电数据,数据全部置0
void Clr_Event_PD_Data()
{
  TRACE();
  
  Debug_Print("Clr_Event_PD_Data");

  Clr_Event_PD_Ram_Data();
  Write_Storage_Data(_SDI_EVENT_DATA_PD, (void *)&Event_Data, sizeof(Event_Data));
}

//检查事件数据的正确性
void Check_Event_Data_Avail()
{
  INT8U Re;
  
  Re = 1;
  Re &= CHECK_STRUCT_SUM(Event_Data);
  //ASSERT(Re EQ 1);
  Re &= CHECK_STRUCT_SUM(Event_Data._Prog_Record);
  //ASSERT(Re EQ 1);  
  Re &= CHECK_STRUCT_SUM(Event_Data._Operator_ID);
  //ASSERT(Re EQ 1);
  Re &= CHECK_STRUCT_SUM(Event_Data._Demand_Exceed_Limit);
  //ASSERT(Re EQ 1);
  Re &= CHECK_STRUCT_SUM(Event_Data._Last_Adj_Time);
  //ASSERT(Re EQ 1);
  Re &= CHECK_STRUCT_SUM(Event_Data._Last_Freeze_Time);  
  //ASSERT(Re EQ 1);
  Re &= CHECK_STRUCT_SUM(Event_Data.Time);
  ASSERT(Re EQ 1);
  
}

void Card_Clr_All_Data()
{
  INT32U Op_ID;
  
  Op_ID = 0xFFFFFFFF;
  Record_Op_ID(&Op_ID);
  Set_Clear_Data_Flag(CLEAR_ALL_FLAG);
}

//等待某事件处理结束
//该函数只用于等待某些特殊事件---只有发生或者只有结束的事件
//例如瞬时快速事件，例如编程、清电量、清需量、清过程等等
void Wait_Event_Data_Proc_End(INT8U Event_ID)
{
  TRACE();

  OS_Waitfor_Sec(Check_Event_End(Event_ID) EQ 1, 3);//等待5s还没有处理完则报断言错误
  if(Check_Event_End(Event_ID) EQ 0)
  {
    ASSERT_FAILED();
  }
  //OS_Waitfor(Check_Event_End(Event_ID) EQ 0);
}

void Set_Event_PD_Time(S_HEX_Time *pTime)
{
  //mem_cpy((INT8U *)&Event_Data.Time, pTime, sizeof(S_BCD_Time), 
  Convert_HEX_2_BCD_Time(pTime, (S_BCD_Time *)&Event_Data.Time);
}

//初始化前次的掉电和上电时间
void Init_PD_PO_Time()
{
    //获取掉电时间
    if(Check_BCD_Time((S_BCD_Time *)&Event_Data.Time))
    {
      Set_BCD_Array_Time((S_BCD_Time  *)&Event_Data.Time, (S_Event_Time *)&PD_Time, (S_Event_Time *)&PD_Time, sizeof(PD_Time));
      Convert_BCD_2_HEX_Time((S_BCD_Time  *)&Event_Data.Time, (S_HEX_Time *)&Hex_PD_Time);
    }
    else
    {
      mem_set((void *)PD_Time.Time, 0, sizeof(PD_Time.Time), (void *)PD_Time.Time, sizeof(PD_Time.Time));
      SET_STRUCT_SUM(PD_Time);
    }  
    //获取上电时间
    Set_BCD_Array_Time((S_BCD_Time  *)&Cur_Time1, (S_Event_Time *)&PO_Time, (S_Event_Time *)&PO_Time, sizeof(PO_Time));
}

//上电事件处理
//上电事件处理
void PowerOn_Event_Proc()
{
  //上电初始化过程中不需要关掉电中断，因为在此过程中掉电不会存数
  if(Get_Sys_Status() != SYS_NORMAL)
    return;
  
  Debug_Print("----------PowerOn Event Proc Start----------");
  
  //读出的掉电数据正确且确实发生了掉电
  if(Read_Storage_Data(_SDI_EVENT_DATA_PD,(void *)&Event_Data,(void *)&Event_Data,sizeof(Event_Data)) != sizeof(Event_Data))
  {
    Clr_Event_PD_Data();
  }
  else if(Event_Data.PD_Flag EQ 1)
  {
    mem_cpy((void *)&Meter_Instant_Status,(void *)&Event_Data.Meter_Instant_Status,sizeof(Event_Data.Meter_Instant_Status),\
            (void *)&Meter_Instant_Status,sizeof(Meter_Instant_Status));

    mem_cpy((void *)&Bat_Work_Status,(void *)&Event_Data.Bat_Work_Status,sizeof(Event_Data.Bat_Work_Status),\
            (void *)&Bat_Work_Status,sizeof(Bat_Work_Status));
    
    mem_cpy((void *)&Not_Even_Data_PUCK, (void *)&Event_Data.Not_Even_Data, sizeof(Event_Data.Not_Even_Data),\
            (void *)&Not_Even_Data_PUCK, sizeof(Not_Even_Data_PUCK));
    
    mem_cpy((void *)&Prg_Key_Status, (void *)&Event_Data.Prg_Key_Status, sizeof(Event_Data.Prg_Key_Status),\
            (void *)&Prg_Key_Status, sizeof(Prg_Key_Status));
    
    Relay_Status.Switch_Status = Event_Data.Relay_Status;
    //设置掉电前时间为当前时间，用于处理掉电前事件
    Set_BCD_Array_Time((S_BCD_Time  *)&Event_Data.Time, (S_Event_Time *)&Cur_Time2, (S_Event_Time *)&Cur_Time2, sizeof(Cur_Time2));

    Init_PD_PO_Time(); //初始化上电和掉电时间    
    Save_LastPwrOff_Data_PUCK();//上次掉电数据处理
    //重新覆盖Cur_Time1时间
    Set_BCD_Array_Time((S_BCD_Time  *)&Cur_Time1, (S_Event_Time *)&Cur_Time2, (S_Event_Time *)&Cur_Time2, sizeof(Cur_Time2));
/*
    //密码锁
    if(CHECK_STRUCT_SUM(Event_Data._PSW_Err_Info) EQ 0 || CHECK_STRUCT_VAR(Event_Data._PSW_Err_Info) EQ 0)
    {
      ASSERT_FAILED();
      mem_set((void *)&PSW_Err_Info, 0, sizeof(PSW_Err_Info),(void *)&PSW_Err_Info, sizeof(PSW_Err_Info));
      INIT_STRUCT_VAR(PSW_Err_Info);
      SET_STRUCT_SUM(PSW_Err_Info);
      SET_STRUCT_SUM(Event_Data);
    } 
   
    PSW_Err_Info.Set_En_Mins = 0; //设置有效时间应该清除
    SET_STRUCT_SUM(PSW_Err_Info);
*/  
    
    //前一次冻结时间
    if(CHECK_STRUCT_SUM(Event_Data._Last_Freeze_Time) EQ 0)
    {
      ASSERT_FAILED();    
      mem_set((void *)&Last_Freeze_Time, 0, sizeof(Last_Freeze_Time), (void *)&Last_Freeze_Time, sizeof(Last_Freeze_Time)); 
      SET_STRUCT_SUM(Last_Freeze_Time);
      SET_STRUCT_SUM(Event_Data);
    }
    
    //事件瞬态字
    mem_set((void *)&Event_Data.Meter_Instant_Status,0,sizeof(Event_Data.Meter_Instant_Status),\
            (void *)&Event_Data.Meter_Instant_Status,sizeof(Event_Data.Meter_Instant_Status)); 
    SET_STRUCT_SUM(Event_Data.Meter_Instant_Status);
    
    //编程记录
    if(CHECK_STRUCT_SUM(Prog_Record) EQ 0)
      Clr_Prog_Record_Ram();  
   
    //编程操作者代码
    mem_set((void *)&Event_Data._Operator_ID,0,sizeof(Event_Data._Operator_ID),\
            (void *)&Event_Data._Operator_ID,sizeof(Event_Data._Operator_ID));   
    SET_STRUCT_SUM(Event_Data._Operator_ID);
    
    //需量越限记录
    mem_set((void *)&Event_Data._Demand_Exceed_Limit,0,sizeof(Event_Data._Demand_Exceed_Limit),\
            (void *)&Event_Data._Demand_Exceed_Limit,sizeof(Event_Data._Demand_Exceed_Limit)); 
    SET_STRUCT_SUM(Event_Data._Demand_Exceed_Limit);
  
    //前一次校时时间
    /*
    mem_set((void *)&Event_Data._Last_Adj_Time,0,sizeof(Event_Data._Last_Adj_Time),\
            (void *)&Event_Data._Last_Adj_Time,sizeof(Event_Data._Last_Adj_Time)); 
    SET_STRUCT_SUM(Event_Data._Last_Adj_Time);
    */
    
    //当前时间
    mem_cpy((void *)&Event_Data.Time,(void *)&Cur_Time1,sizeof(Cur_Time1),(void *)&Event_Data.Time,sizeof(Event_Data.Time));
    
    Event_Data.PD_Flag = 0;
    SET_STRUCT_SUM(Event_Data);
    
    Write_Storage_Data(_SDI_EVENT_DATA_PD,(void *)&Event_Data,sizeof(Event_Data)); 
  }
  else
  {
    Debug_Print("PD_Flag != 1");
  }
  
  Debug_Print("----------PowerOn Event Proc End----------");   
}

//设置默认的掉电存储事件数据
void Set_Def_Event_PD_Data()
{
  mem_set((void *)&Event_Data, 0, sizeof(Event_Data), (void *)&Event_Data, sizeof(Event_Data));
  
  SET_STRUCT_SUM(Event_Data.Meter_Instant_Status);
  SET_STRUCT_SUM(Operator_ID);
  SET_STRUCT_SUM(Demand_Exceed_Limit); 
  SET_STRUCT_SUM(Last_Adj_Time);
  SET_STRUCT_SUM(PSW_Err_Info);
  SET_STRUCT_SUM(Last_Freeze_Time);
  SET_STRUCT_SUM(Prog_Record);
  Clr_Prog_Record_Ram();
  
  SET_STRUCT_SUM(Event_Data);
}
#undef EVENT_DATA_C


