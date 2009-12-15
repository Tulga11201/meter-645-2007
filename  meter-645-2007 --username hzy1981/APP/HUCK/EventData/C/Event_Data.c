#define EVENT_DATA_C
#include <includes.h>

//��鵱ǰ�¼��Ƿ��ڷ���,Event_ID����Ϊ��һ���¼�
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
//ȫʧѹ������ʱ��ͳ��
//�ϵ����øú���һ�Σ�Counts��ʾ�����ڼ�ʧѹ�ܴ�����Mins��ʾ�����ڼ�ʧѹ�ܷ�����
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
	//���ܵ�ʧѹ������ʱ�����ͳ��
	if(Get_Total_Event_ID(ID_EVENT_ALL_LOSS_VOLT) EQ ID_EVENT_TOTAL_LOSS_VOL)//ȫʧѹ��ʱ��ʹ����Ƿ������ʧѹ�ʹ���?
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

//ȫʧѹ�����ۼӴ���
//Start_Time��ʾ��ʼʱ��,Start_Time[0]->Start_Time[4]��ʾ�֡�ʱ���ա��¡���,BCD��
//End_Time��ʾ��ֹʱ��,End_Time[0]->End_Time[4]��ʾ�֡�ʱ���ա��¡��꣬BCD��
//�ϵ�󣬶��ϵ�ǰ��ǰN(N<=10)��ȫʧѹ�����øú���N��
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
    
    Write_Storage_Data(SDI_LAST_LOSS_VOL_OCCUR_TIME, (void *)All_Loss_Vol_Time.Start_Time, 6);//���һ��ȫʧѹ�����ͽ���ʱ��
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

// �¼�������
//ע�⣺�ú�������Read_Event_Status��ѯĳ���¼�״̬ʱ���Ǹ��¼�����ǰ��״̬
//���� ĳ�¼����������øú���������ú����ڵ���Read_Event_Statusʱ����0
// �෴��ĳ�¼����������øú���������ú����ڵ���Read_Event_Statusʱ����1
void Event_Data_Proc(INT8U Event_ID,INT8U Occur_Or_End)
{
  INT8U Total_Event_ID;
  INT8U Clr_Demand_Man_Flag;
  INT8U Op_ID[4];
  
  _Debug_Print("\r\n++++++++++Event Data Proc,ID:%d,%s++++++++++",Event_ID,(Occur_Or_End EQ EVENT_OCCUR)?"Occur":"End");
  
  Clr_Demand_Man_Flag = 0;
  if(Event_ID EQ ID_EVENT_CLR_DEMAND_MAN)//�ֶ�������תΪͨ����������ͬһ�¼�ID����,�����ֶ��������Ĳ�����IDΪȫFF
  {
    Clr_Demand_Man_Flag = 1;
    Event_ID = ID_EVENT_CLR_DEMAND_COM;
    //��ǰ������id�ȱ���
    Store_Op_ID(Op_ID, Op_ID, sizeof(Op_ID));
  }
  else if(Event_ID EQ ID_EVENT_RELAY_ON || Event_ID EQ ID_EVENT_RELAY_OFF) //����բ����������բ��¼�����ߴ���ΪFF
  {
    if(Relay_Status.Switch_Cause EQ S_OFF_PREPAID) //ǰһ���Ǳ�����բ
    {
      Store_Op_ID(Op_ID, Op_ID, sizeof(Op_ID));      
    }
  }
  
  Event_Cumu_Proc(Event_ID,Occur_Or_End,EVENT_REAL);
  
  Total_Event_ID = Get_Total_Event_ID(Event_ID);//���¼���Ӧ���ܼ���ҲҪ����
  if(Total_Event_ID != NULL_EVENT_ID)
  {
    Debug_Print("Total Event Proc");
    Event_Cumu_Proc(Total_Event_ID,Occur_Or_End,EVENT_REAL);
  }
  Event_Separate_Proc(Event_ID,Occur_Or_End,EVENT_REAL);
 
  //�ָ�������ID
  if(Clr_Demand_Man_Flag EQ 1)
  {
    Restore_Op_ID(Op_ID);
  }
  else if(Event_ID EQ ID_EVENT_RELAY_ON || Event_ID EQ ID_EVENT_RELAY_OFF)
  {
    if(Relay_Status.Switch_Cause EQ S_OFF_PREPAID) //ǰһ���Ǳ�����բ    
    {
      Restore_Op_ID(Op_ID);      
    }    
  }
  
  Debug_Print("++++++++++Event Data Proc:End++++++++++\r\n");
  OS_TimeDly_Ms(10); //�ӳ�10ms
}


//����¼�
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
    Clr_All_Event_Sram(); //����ڴ��е��¼����ݣ����¿�ʼ�ж��¼�
    Set_Clear_Data_Result(1);
  }
  else
  {
    Re = Clear_One_Event_Data((Clr_PDI & 0xFFFFFF00) | 0x01);
    if(Re EQ 0) //û������ɹ���Clear_Event_PDI����
    {
      SET_STRUCT_SUM(Event_Data);  
      Set_Clear_Data_Result(0);
    }
    else
      Set_Clear_Data_Result(1);
  }
}

//֪ͨͨ�����̣�����������
//�ڲ���Clear_Flag.Flag�ó�CLEAR_END_FLAG
//�Ӷ�ʹ�´ε���Check_Clear_Data_Flag����CLEAR_END_FLAG
void Clear_Data_End()
{
  INT8U Re;
  Re=CHECK_STRUCT_SUM(Clear_Flag);
  ASSERT(1 EQ Re);
  Clear_Flag.Flag=CLEAR_END_FLAG;
  SET_STRUCT_SUM(Clear_Flag);
}

//����Ĭ�ϵ��¼�����������
void Set_Def_Event_Data()
{
  Set_Def_Event_Cumu_Data();
  Set_Def_Event_Separate_Data();
}

//���籣���¼�����
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
    
    if(Get_Meter_Hard_Mode()==MODE_TEST) //�Լ�ģʽ�����բ
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

//���Event_Data�ڴ����ݣ����ǲ����Clear_Event_PDI��Operator_ID
void Clr_Event_PD_Ram_Data()
{
  DIS_PD_INT;

  //��Ϊ�����ߴ�������¼���DI�ȶ���������¼���¼ ��Ҫ�ģ���ˣ���Ҫ����
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
  
  Event_Data.PD_Flag = 0;//û�з���������  
  SET_STRUCT_SUM(Event_Data);

  EN_PD_INT;    
}

//�����������,����ȫ����0
void Clr_Event_PD_Data()
{
  TRACE();
  
  Debug_Print("Clr_Event_PD_Data");

  Clr_Event_PD_Ram_Data();
  Write_Storage_Data(_SDI_EVENT_DATA_PD, (void *)&Event_Data, sizeof(Event_Data));
}

//����¼����ݵ���ȷ��
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

//�ȴ�ĳ�¼��������
//�ú���ֻ���ڵȴ�ĳЩ�����¼�---ֻ�з�������ֻ�н������¼�
//����˲ʱ�����¼��������̡��������������������̵ȵ�
void Wait_Event_Data_Proc_End(INT8U Event_ID)
{
  TRACE();

  OS_Waitfor_Sec(Check_Event_End(Event_ID) EQ 1, 3);//�ȴ�5s��û�д������򱨶��Դ���
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

//��ʼ��ǰ�εĵ�����ϵ�ʱ��
void Init_PD_PO_Time()
{
    //��ȡ����ʱ��
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
    //��ȡ�ϵ�ʱ��
    Set_BCD_Array_Time((S_BCD_Time  *)&Cur_Time1, (S_Event_Time *)&PO_Time, (S_Event_Time *)&PO_Time, sizeof(PO_Time));
}

//�ϵ��¼�����
//�ϵ��¼�����
void PowerOn_Event_Proc()
{
  //�ϵ��ʼ�������в���Ҫ�ص����жϣ���Ϊ�ڴ˹����е��粻�����
  if(Get_Sys_Status() != SYS_NORMAL)
    return;
  
  Debug_Print("----------PowerOn Event Proc Start----------");
  
  //�����ĵ���������ȷ��ȷʵ�����˵���
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
    //���õ���ǰʱ��Ϊ��ǰʱ�䣬���ڴ������ǰ�¼�
    Set_BCD_Array_Time((S_BCD_Time  *)&Event_Data.Time, (S_Event_Time *)&Cur_Time2, (S_Event_Time *)&Cur_Time2, sizeof(Cur_Time2));

    Init_PD_PO_Time(); //��ʼ���ϵ�͵���ʱ��    
    Save_LastPwrOff_Data_PUCK();//�ϴε������ݴ���
    //���¸���Cur_Time1ʱ��
    Set_BCD_Array_Time((S_BCD_Time  *)&Cur_Time1, (S_Event_Time *)&Cur_Time2, (S_Event_Time *)&Cur_Time2, sizeof(Cur_Time2));
/*
    //������
    if(CHECK_STRUCT_SUM(Event_Data._PSW_Err_Info) EQ 0 || CHECK_STRUCT_VAR(Event_Data._PSW_Err_Info) EQ 0)
    {
      ASSERT_FAILED();
      mem_set((void *)&PSW_Err_Info, 0, sizeof(PSW_Err_Info),(void *)&PSW_Err_Info, sizeof(PSW_Err_Info));
      INIT_STRUCT_VAR(PSW_Err_Info);
      SET_STRUCT_SUM(PSW_Err_Info);
      SET_STRUCT_SUM(Event_Data);
    } 
   
    PSW_Err_Info.Set_En_Mins = 0; //������Чʱ��Ӧ�����
    SET_STRUCT_SUM(PSW_Err_Info);
*/  
    
    //ǰһ�ζ���ʱ��
    if(CHECK_STRUCT_SUM(Event_Data._Last_Freeze_Time) EQ 0)
    {
      ASSERT_FAILED();    
      mem_set((void *)&Last_Freeze_Time, 0, sizeof(Last_Freeze_Time), (void *)&Last_Freeze_Time, sizeof(Last_Freeze_Time)); 
      SET_STRUCT_SUM(Last_Freeze_Time);
      SET_STRUCT_SUM(Event_Data);
    }
    
    //�¼�˲̬��
    mem_set((void *)&Event_Data.Meter_Instant_Status,0,sizeof(Event_Data.Meter_Instant_Status),\
            (void *)&Event_Data.Meter_Instant_Status,sizeof(Event_Data.Meter_Instant_Status)); 
    SET_STRUCT_SUM(Event_Data.Meter_Instant_Status);
    
    //��̼�¼
    if(CHECK_STRUCT_SUM(Prog_Record) EQ 0)
      Clr_Prog_Record_Ram();  
   
    //��̲����ߴ���
    mem_set((void *)&Event_Data._Operator_ID,0,sizeof(Event_Data._Operator_ID),\
            (void *)&Event_Data._Operator_ID,sizeof(Event_Data._Operator_ID));   
    SET_STRUCT_SUM(Event_Data._Operator_ID);
    
    //����Խ�޼�¼
    mem_set((void *)&Event_Data._Demand_Exceed_Limit,0,sizeof(Event_Data._Demand_Exceed_Limit),\
            (void *)&Event_Data._Demand_Exceed_Limit,sizeof(Event_Data._Demand_Exceed_Limit)); 
    SET_STRUCT_SUM(Event_Data._Demand_Exceed_Limit);
  
    //ǰһ��Уʱʱ��
    /*
    mem_set((void *)&Event_Data._Last_Adj_Time,0,sizeof(Event_Data._Last_Adj_Time),\
            (void *)&Event_Data._Last_Adj_Time,sizeof(Event_Data._Last_Adj_Time)); 
    SET_STRUCT_SUM(Event_Data._Last_Adj_Time);
    */
    
    //��ǰʱ��
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

//����Ĭ�ϵĵ���洢�¼�����
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


