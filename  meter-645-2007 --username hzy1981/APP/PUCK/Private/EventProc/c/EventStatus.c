#define EVENTSTATUS_C
#include "Pub_PUCK.h"
#include "EventStatus.h"

/***********************************************************************
�������ܣ���ʼ���¼�״̬�Ȳ���
��ڣ�1------------ǿ������¼�˲̬�֣����¼��������״̬��sram��0-------����CSֵ�����
���ڣ���
***********************************************************************/
void Init_Event_Sram(INT8U Flag)
{
  INT8U i;
  
  if((CHECK_STRUCT_SUM(Meter_Run_Status)==0) || Flag)
     mem_set((void *)(&Meter_Run_Status),0,sizeof(Meter_Run_Status),\
                 (void *)(&Meter_Run_Status),sizeof(Meter_Run_Status));    
  SET_STRUCT_SUM(Meter_Run_Status);

  
  for(i=0;i<MAX_EVENT_NUM;i++)
  {
    if((CHECK_STRUCT_SUM(EventProcStatusVar[i])==0) || Flag)
      Clr_Event_Real_Status(i);      
  }
  
  if((CHECK_STRUCT_SUM(Meter_Run_Status)==0) || Flag)
   
    mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                 (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
  SET_STRUCT_SUM(Meter_Instant_Status); 

}

/***********************************************************************
�������ܣ���������¼�״̬
��ڣ�
���ڣ���
***********************************************************************/
void Clr_All_Event_Sram(void)
{  
  Init_Event_Sram(1);  
}
/***********************************************************************
�������ܣ���ʼ�������¼�״̬
��ڣ�
���ڣ���
***********************************************************************/
void Init_All_Event_Sram(void)
{  
  Init_Event_Sram(0);
  
  Clr_Demand_Key.Status=0;
  SET_STRUCT_SUM(Clr_Demand_Key);
  
    //���ϵ�״̬
  Power_Status.Power=POWER_ON;          
  SET_STRUCT_SUM(Power_Status);
  
  //��ƽ����
  mem_set((void *)(&Not_Even_Data_PUCK),0,sizeof(Not_Even_Data_PUCK),\
                   (void *)(&Not_Even_Data_PUCK),sizeof(Not_Even_Data_PUCK));
  SET_STRUCT_SUM(Not_Even_Data_PUCK);  
}


/***********************************************************************
�������ܣ���ȡʱ���ֵ
��ڣ�Temp_PD_Time-------------����ڵ�ǰ��ʱ�䣬BCD��
���ڣ�1-------------��ȡ�ɹ���0----------------ʧ��
***********************************************************************/
INT8U Get_Time_Diff(S_Event_Time Temp_PD_Time,INT32U *Diff)
{  
  INT32U LastTime,CurTime;  
  
  //��BCD��ת���� HEX��ʽ
  Bcd2Hex_Buf((INT8U *)PD_Time.Time, sizeof(PD_Time.Time), Temp_PD_Time.Time, Temp_PD_Time.Time, sizeof(Temp_PD_Time.Time));
  
  //�ϴε���ʱ��
  LastTime=mktime(((INT16U )Temp_PD_Time.Time[5]+2000),(INT16U )Temp_PD_Time.Time[4],(INT16U )Temp_PD_Time.Time[3],\
                  (INT16U )Temp_PD_Time.Time[2],(INT16U )Temp_PD_Time.Time[1],0);
  
  //��ǰʱ�����ʱ��
  CurTime=mktime(((INT16U )Cur_Time0.Time[4]+2000),(INT16U )Cur_Time0.Time[3],(INT16U )Cur_Time0.Time[2],\
                  (INT16U )Cur_Time0.Time[1],(INT16U )Cur_Time0.Time[0],0);
  
  if(CurTime>=LastTime)
  {
    *Diff=(CurTime-LastTime)/60;  //�õ�����
    return 1;
  }
  
  return 0;
}
/***********************************************************************
�������ܣ��洢��ع���ʱ������
��ڣ���
���ڣ���
ע�⣺�ϵ��Bat_Work_Status.BatRunTime�����ݣ�HUCK�Ѱ��Ҹ��·�д�ϴ��ۼ����ݣ�
      ֻ��HUCK����������̺󣬲ų�ʼ���˱�����
***********************************************************************/
void Get_Bat_Work_Time(void)
{
  INT32U temp32;
  
  temp32=0;
  
#if (BAT_RUN_TIME&BAT_RUN_TIME_PWROFF)   
  if(Get_Time_Diff(PD_Time,&temp32))
    ASSERT_FAILED();
#endif
  
  DIS_PD_INT;  //�ص����ж�
  
  if(CHECK_STRUCT_SUM(Bat_Work_Status))
    Bat_Work_Status.BatRunTime+=temp32;   //�ϵ�󣬴˱���HUCK�Ѿ���ʼ��ȡ��
  else
   Bat_Work_Status.BatRunTime=0;   //�ϵ�󣬴˱���HUCK�Ѿ���ʼ��ȡ��
  
  SET_STRUCT_SUM(Bat_Work_Status);
   
   EN_PD_INT; //�������ж�
}
/***********************************************************************
�������ܣ��ϵ�󣬻�ȡ�����ʱ��
��ڣ���
���ڣ���
ע�⣺Prg_Key_Status.PrgKeyTime�����ݣ�HUCK�Ѱ��Ҹ��·�д�ϴ��ۼ����ݣ�
      ֻ��HUCK����������̺󣬲ų�ʼ���˱�����
***********************************************************************/
void Get_Prog_Key_Time(void)
{
  INT32U DiffTime;
    
  DIS_PD_INT;  //�ص����ж�
  if(Prg_Key_Status.PrgKeyTime && CHECK_STRUCT_SUM(Prg_Key_Status))  //�ϵ�󣬴��ڱ��״̬���˱���HUCK�Ѿ���ʼ��ȡ��
  {
    if(Get_Time_Diff(PD_Time,&DiffTime))     //�ϴε����Ǳ��״̬���� InPrgPwroff��
    {
      if(DiffTime<=PRG_KEY_TIME)
      {
        Key_Value_Pub.Key.Bit.PrgKey=1;
        Prg_Key_Status.PrgKeyTime+=DiffTime;
      }
      else       //����ʱ�䳬����̰�ťά��ʱ�䣬�����̰�ť״̬
        Prg_Key_Status.PrgKeyTime=0;      
    }
    else                                      //�ϴε��粻�Ǳ��״̬
      Prg_Key_Status.PrgKeyTime=0;
  }
  else
    Prg_Key_Status.PrgKeyTime=0;   //�ϴε��粻�Ǳ��״̬
       
  SET_STRUCT_SUM(Prg_Key_Status);
  EN_PD_INT; //�������ж�
}
/***********************************************************************
�������ܣ��ϵ�����ʱ��ÿ���Ӷ�RTC��ع���ʱ���ۼ�
��ڣ���
���ڣ���
��HUCK��һ�����������Լ�
***********************************************************************/
void Accmu_RTC_BatTime_PerMin(void)
{
#if (BAT_RUN_TIME&BAT_RUN_TIME_PWRON)  //ͳ������Դ�����£�RTC������ʱ��
  INT32U temp32;
  INT8U temp;
  
  //if(Get_Sys_Status()!=SYS_NORMAL) //ֻ������Դ�����£��Ŵ���������,HUCK ��֤,���ٴ�����
  // return ;
  
  if(RTC_BAT_LOW EQ 0)  //���Ƿѹ����ͳ��
    return ;
  
  if(CHECK_STRUCT_SUM(Bat_Work_Status) EQ 0) //У��Ͳ���
  {
    temp=Read_Storage_Data(SDI_BAT_RUN_TIME,(INT8U *)(&temp32),(INT8U *)(&temp32),sizeof(temp32));
    
    if(temp EQ 0)
      ASSERT_FAILED();
    
    DIS_PD_INT;  //�ص����ж�
    Bat_Work_Status.BatRunTime=temp32;     
  }
  else
  {
    DIS_PD_INT;  //�ص����ж�
    Bat_Work_Status.BatRunTime++;
  }
  
  SET_STRUCT_SUM(Bat_Work_Status);
  EN_PD_INT; //�������ж�
#endif 
}
/***********************************************************************
�������ܣ�ÿ��һ��ʱ��洢�������ʱ��
��ڣ���
���ڣ���
***********************************************************************/
void Period_Save_RTC_BatTime(void)
{
#if (BAT_RUN_TIME&BAT_RUN_TIME_PWRON)  //ͳ������Դ�����£�RTC������ʱ��
  
 // if(Get_Sys_Status() != SYS_NORMAL)  //ֻ������Դ�����£��Ŵ���������,HUCK ��֤,���ٴ�����
 //  return ;
 
  if(CHECK_STRUCT_SUM(Bat_Work_Status) EQ 0) //У��Ͳ���,���ܴ�,�����洢������ sram ����
  {    
    Accmu_RTC_BatTime_PerMin();        
    return ;
  }

  Write_Storage_Data(SDI_BAT_RUN_TIME,(INT8U *)(&Bat_Work_Status.BatRunTime),sizeof(Bat_Work_Status.BatRunTime));
#endif 
}
/***********************************************************************
�������ܣ������ع���ʱ��
��ڣ���
���ڣ���
***********************************************************************/
void Clr_RTC_BatTime(void)
{
  DIS_PD_INT;  //�ص����ж�
  Bat_Work_Status.BatRunTime=0; 
  SET_STRUCT_SUM(Bat_Work_Status);
  EN_PD_INT; //�������ж�
}
/***********************************************************************
�������ܣ��ϵ�󣬴洢�ϴεĵ������ݣ��¼�
��ڣ���
���ڣ���
***********************************************************************/
void Save_LastPwrOff_Data_PUCK(void)
{
  Save_Event_Data();
  Get_Bat_Work_Time();
  Get_Prog_Key_Time();
}

/***********************************************************************
�������ܣ����ݷ������¼�Id��״̬��������Ӧ��״̬
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_Instant_Status(INT8U Id,INT8U Status)
{
  INT8U Byte,Bit;
  if(Id>=MAX_EVENT_NUM)
    return ;
  
  Byte=Id/8;
  Bit=Id%8;
  DIS_PD_INT;  //�ص����ж�
  if(Status)
    SET_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);
  else
    CLR_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);    
  SET_STRUCT_SUM(Meter_Instant_Status);
  EN_PD_INT; //�������ж�
}

/***********************************************************************
�������ܣ����ݷ������¼���������Ӧ��˲̬״̬��
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_Instant(INT8U Id)
{
  if(EventPropertyVar[Id].DoubleFlag==0)  //���ɶ��¼����������ԭ����ʵ״̬
    Clr_Event_Real_Status(Id);
  Set_Event_Instant_Status(Id,1);
}
/***********************************************************************
�������ܣ�����λ�����ֽڵ�λ�������Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************/
void Clr_Event_Instant(INT8U Id)
{
  Set_Event_Instant_Status(Id,0); 
}

/***********************************************************************
�������ܣ����¼�ģ��Ϊ�������״̬,Ϊ������׼��
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_Occur_Status(INT8U i)
{
  if(i>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+i),0xFF,sizeof(EventProcStatus),\
                 (void *)(EventProcStatusVar),sizeof(EventProcStatusVar));
  
  //�ý�����ʱ����λ������ֵ
  EventProcStatusVar[i].Mins=1;  
  EventProcStatusVar[i].EndCount=EventPropertyVar[i].EndCount+1;
  SET_STRUCT_SUM(EventProcStatusVar[i]); 
}
/***********************************************************************
�������ܣ����¼�ģ��Ϊ�������״̬,Ϊ������׼��
��ڣ���
���ڣ���
***********************************************************************/
void Set_Event_End_Status(INT8U i)
{
  if(i>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+i),0,sizeof(EventProcStatusVar+i),\
                 (void *)(EventProcStatusVar+i),sizeof(EventProcStatusVar+i));
  
  EventProcStatusVar[i].StartCount=EventPropertyVar[i].StartCount+1;
  SET_STRUCT_SUM(EventProcStatusVar[i]);    
}
/***********************************************************************
�������ܣ����¼�ǿ�з���,����������������Ϣ
��ڣ��¼�ID
���ڣ���
***********************************************************************/
void Force_Event_Occur_Status(INT8U i)
{
  Set_Event_End_Status(i);  
  Event_Judge_StartAndEnd(i,0,1);
}
/***********************************************************************
�������ܣ����¼�ǿ�н���,�����������������Ϣ
��ڣ��¼�ID
���ڣ���
***********************************************************************/
void Force_Event_End_Status(INT8U i)
{
  Set_Event_Occur_Status(i);  
  Event_Judge_StartAndEnd(i,0,1);  
}
/***********************************************************************
�������ܣ�����¼�����������״̬
��ڣ���
���ڣ���
***********************************************************************/
void Clr_Event_Real_Status(INT8U Id)
{
  if(Id>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+Id),0,sizeof(EventProcStatusVar+Id),\
                 (void *)(EventProcStatusVar+Id),sizeof(EventProcStatusVar+Id));
  SET_STRUCT_SUM(EventProcStatusVar[Id]);

}
/***********************************************************************
�������ܣ�����λ�����ֽڵ�λ����ȡ��Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
***********************************************************************/
INT8U Get_Event_Instant(INT8U Id)
{  
  INT8U Byte,Bit,temp;
  
  if(Id>=MAX_EVENT_NUM)
    return 0;
  
  Byte=Id/8;
  Bit=Id%8;
  
  temp=CHECK_STRUCT_SUM(Meter_Instant_Status); 
  if(0==temp)
  ASSERT_FAILED();  

  temp=GET_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);  
  return temp;    
}


/********************************************************************************
����ԭ�ͣ�void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode)
�������ܣ�����¼�(�ɶ�)����
CountMode:0----------��ʾ�趨�����ж�Ϊ0������-------------�����¼����ʱ���ж�
SaveMode:0----------��ʾ���洢������-------------��ʾ�洢
*********************************************************************************/
void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode)
{
  INT16U ConStartcounts,ConEndcounts;
  INT16U RamStartcounts,RamEndcounts;
  
  if(Id<MIN_ID_EVENT || Id>MAX_ID_EVENT) //����һ��
    return ;
  
  if(CHECK_STRUCT_SUM(EventProcStatusVar[Id])==0)  //У��Ͳ��ԣ���ֹ�¼��Ҵ��Ҹ㣬���֮
  {
    ASSERT_FAILED();
    Clr_Event_Real_Status(Id);
    return ;
  }
  
  if((0 EQ CountMode)||(Check_Sys_Status()!=SYS_NORMAL))  //������ģʽ�£������ͽ���ֻ�ж�һ��
  {
    ConStartcounts=1;
    ConEndcounts=1; 
  }
  
  if(Check_Sys_Status()==SYS_NORMAL) //����ģʽ�£������ж�ʱ�䣬�ɱ�����
  {
    if(EventPropertyVar[Id].JudgeTimeSec)  //�ж�ʱ��,�ɲ�������
    {
      if(*EventPropertyVar[Id].JudgeTimeSec EQ 0)  //����ȡ���������߶�����
      {
        ConStartcounts=60;
        ConEndcounts=36;
      }
      else
      {
        ConStartcounts=*EventPropertyVar[Id].JudgeTimeSec;
        ConEndcounts=*EventPropertyVar[Id].JudgeTimeSec/5*3;
      }
     } 
    else                                   //�ж�ʱ��,�ɱ�����
    {
        ConStartcounts=(EventPropertyVar[Id].StartUnit==0)?\
                    EventPropertyVar[Id].StartCount:((INT16U)EventPropertyVar[Id].StartCount*60);
        ConEndcounts=(EventPropertyVar[Id].EndUnit==0)?\
                    EventPropertyVar[Id].EndCount:((INT16U)EventPropertyVar[Id].EndCount*60);
    }
  }
  
  if(EventProcStatusVar[Id].Occur==0)   //δ�������¼�
  {
    if(Get_Event_Instant(Id))  //��ǰ˲ʱ״ָ̬ʾ���¼��ķ���
      EventProcStatusVar[Id].StartCount++;
    else                                 //���������������������
      EventProcStatusVar[Id].StartCount=0;
    
    if(EventProcStatusVar[Id].StartCount>=60)  //���Ӽ���
    {
      EventProcStatusVar[Id].Mins++;
      EventProcStatusVar[Id].StartCount=0;
    }
      
    RamStartcounts=EventProcStatusVar[Id].Mins*60+(INT16U)EventProcStatusVar[Id].StartCount;
    if(RamStartcounts>=ConStartcounts)  //�¼���������
    {       
        Debug_Print("Event_Occur----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[Id].EventName,Id,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec);  
     
      if((EventPropertyVar[Id].StartSave)&&(0!=SaveMode))
      {
        //�ֽ�ϵͳ״̬����λ��ΪEvent_Data_Proc()����
        EventProcStatusVar[Id].Status=1;
        Get_Meter_Run_Status();
        //��ϵͳ״̬����0����ΪEvent_Data_Proc()ĳЩ�ж�������
        EventProcStatusVar[Id].Status=0;
        
        Event_Data_Proc(Id,EVENT_OCCUR);  //�����¼������洢����
        Debug_Print("Write Event_Occur----->%s(%d)",EventPropertyVar[Id].EventName,Id);
        //OS_TimeDly_Ms(10);  
      }
      EventProcStatusVar[Id].Occur=1; EventProcStatusVar[Id].Status=1;  
      EventProcStatusVar[Id].Status1=1; EventProcStatusVar[Id].Status2=1; 
      EventProcStatusVar[Id].Status3=1; EventProcStatusVar[Id].Status4=1; 
      EventProcStatusVar[Id].StartCount=0;EventProcStatusVar[Id].EndCount=0;  
      EventProcStatusVar[Id].Mins=0;

      if(EventPropertyVar[Id].DoubleFlag==0)  //���ڲ��ɶԵ��¼��������������˲̬��
      {
          Clr_Event_Instant(Id); //�����Ӧ˲ʱ״̬�֣����ڶԽ���ʱ����¼���Ӧ
          //Debug_Print("Emergece Event End,Clear Instant---------->%s",EventPropertyVar[Id].EventName);
      }
      if(EventPropertyVar[Id].DoubleFlag &&ConEndcounts==0)  //�ɶԵ��¼�����Ҫ�����������˲̬��
         Clr_Event_Instant(Id);
    }
  }
  else                         //�Ѿ������˸��¼�,�����������ʼ����
  {
    if(EventPropertyVar[Id].DoubleFlag==1)  //�ɶ��¼�
    {
      if(EventProcStatusVar[Id].Status==1)  //�ɶ��¼�������,�н����¼�
      {
        if(Get_Event_Instant(Id)==0)  //�ڽ�������ʱ
          EventProcStatusVar[Id].EndCount++;
        else                          
        {
          if(EventPropertyVar[Id].ForbitEnd==0)       //����Ҫǿ�н���
            EventProcStatusVar[Id].EndCount=0;         //���������������������
          else                                    //��Ҫǿ�н���,������ʱ,����������
          {
            Clr_Event_Instant(Id); //ǿ�������Ӧ˲ʱ״̬��
            EventProcStatusVar[Id].EndCount++;
            if(EventPropertyVar[Id].EndIndex<MAX_END_TIME_NUM)
              ConEndcounts=Const_End_Time[EventPropertyVar[Id].EndIndex]; 
            else
              ASSERT_FAILED();
          }
        }          
      }
    }
    else                                //���ǳɶ��¼������������������������������
    {
      Clr_Event_Instant(Id); //ǿ�������Ӧ˲ʱ״̬��-------PUCK!!!!!!!!!
      EventProcStatusVar[Id].EndCount++;
    }
    
    if(EventProcStatusVar[Id].EndCount>=60)  //���Ӽ���
    {
      EventProcStatusVar[Id].Mins++;
      EventProcStatusVar[Id].EndCount=0;
    }
    RamEndcounts=EventProcStatusVar[Id].Mins*60+(INT16U)EventProcStatusVar[Id].EndCount; 
    if(RamEndcounts>=ConEndcounts)  //�¼�����/�ָ�
    {
       Debug_Print("Event_End----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[Id].EventName,Id,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec); 
       if((EventPropertyVar[Id].EndSave)&&(0!=SaveMode))
       {
         //�ֽ�ϵͳ״̬����0��ΪEvent_Data_Proc()����
        EventProcStatusVar[Id].Status=0;
        Get_Meter_Run_Status();
        //��ϵͳ״̬�ֻ�ԭ����ΪEvent_Data_Proc()ĳЩ�ж�������
        EventProcStatusVar[Id].Status=1;
        
         Event_Data_Proc(Id,EVENT_END);  //�����¼������洢����
         Debug_Print("Write Event_End----->%s(%d)",EventPropertyVar[Id].EventName,Id);
         //OS_TimeDly_Ms(10);  
       }
       EventProcStatusVar[Id].Occur=0;    EventProcStatusVar[Id].Status=0;
       EventProcStatusVar[Id].Status1=0;  EventProcStatusVar[Id].Status2=0;
       EventProcStatusVar[Id].Status3=0;   EventProcStatusVar[Id].Status4=0;
       EventProcStatusVar[Id].StartCount=0;EventProcStatusVar[Id].EndCount=0; 
       EventProcStatusVar[Id].Mins=0;
    }
  }
    SET_STRUCT_SUM(EventProcStatusVar[Id]);  
}
/********************************************************************************
����ԭ�ͣ�void Get_Meter_Instant_Status(void)
�������ܣ���ȡ���˲̬��,ͨ������ָ�������Ӧ����ʵ��
*********************************************************************************/
void Get_Meter_Instant_Status(void)
{
  INT8U i;
  
  if(Check_Power_Grid_Event(0))
  {
    Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B��ѹʧѹ���
    Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C��ѹʧѹ���    
   
    Clr_Event_Instant(ID_EVENT_A_VOLT_LESS);  //A��ѹǷѹ���
    Clr_Event_Instant(ID_EVENT_B_VOLT_LESS);  //B��ѹǷѹ���
    Clr_Event_Instant(ID_EVENT_C_VOLT_LESS);  //C��ѹǷѹ���
    
    Clr_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);  //A��ѹ��ѹ���
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  //B��ѹ��ѹ���
    Clr_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);  //C��ѹ��ѹ���
    
    
    Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE);  //A��û�ж���
    Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B��û�ж���
    Clr_Event_Instant(ID_EVENT_C_LOSS_PARSE);  //C��û�ж���
    
    
    Clr_Event_Instant(ID_EVENT_VOLT_NO_EVEN);  //û�е�ѹ��ƽ��
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //û�е�����ƽ��
    
    Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A��û��ʧ��
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B��û��ʧ��
    Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C��û��ʧ��
    //Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB��û��ʧ��
    //Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC��û��ʧ��
    //Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC��û��ʧ��
    //Clr_Event_Instant(ID_EVENT_ALL_LOSS_CURR);  //ABC��û��ʧ��    
    
    Clr_Event_Instant(ID_EVENT_A_NEG_CURR); //A��������
    Clr_Event_Instant(ID_EVENT_B_NEG_CURR);  //B��������
    Clr_Event_Instant(ID_EVENT_C_NEG_CURR);  //C��������
    Clr_Event_Instant(ID_EVENT_SUM_NEG_CURR);  //�й����ʷ���
    
    Clr_Event_Instant(ID_EVENT_A_OVER_CURR);  //A�������
    Clr_Event_Instant(ID_EVENT_B_OVER_CURR);  //B�������
    Clr_Event_Instant(ID_EVENT_C_OVER_CURR);  //C�������
    
    return ;
  }
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if(EventPropertyVar[i].GetInstStatus)
      EventPropertyVar[i].GetInstStatus();
  }
}
/********************************************************************************
����ԭ�ͣ�void Event_Judge_Save_Alarm(INT8U Flag)
�������ܣ������¼�����/�����ж���,ͬʱ���ⱨ��
*********************************************************************************/
void Event_Judge_Save_Alarm(INT8U CountMode,INT8U SaveMode)
{
  INT8U i;  
    
  if(Get_Cal_Exsit())     //У��״̬�£������¼�
    return ;
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    Clear_All_Dog();
    /*
    if(Get_Main_Init_Flag() !=  MAIN_INITING)  //�����ʼ��״̬
    {      
      {
          OS_TimeDly_Ms(10);  
      }
    }
    */
    Event_Judge_StartAndEnd(i,CountMode,SaveMode);
    //if(i EQ (MAX_ID_EVENT/2))   OS_TimeDly_Ms(10);
  }
}
/********************************************************************************
����ԭ�ͣ�void Read_Event_Status_Perone(INT8U PersonID,INT8U EventId)
�������ܣ������ڲ����˼���Ƿ���,�������
��ڣ�    PersonID--------����ID
          EventId---------�¼�ID
���ڣ�0---------�޴��¼�������1---------���¼�������
*********************************************************************************/
INT8U Read_Event_Status_Perone(INT8U PersonID,INT8U EventId)
{
  INT8U temp;  
 
  if(EventId>MAX_EVENT_NUM)
    return 0;
  
  temp=0;   
  switch(PersonID)
  {
  case HUCK:
    temp=EventProcStatusVar[EventId].Status1;
    EventProcStatusVar[EventId].Status1=0;
    break;
    
   case SUCK:
    temp=EventProcStatusVar[EventId].Status2;
    EventProcStatusVar[EventId].Status2=0;
    break;
      
   case PUCK:
    temp=EventProcStatusVar[EventId].Status3;
    EventProcStatusVar[EventId].Status3=0;
    break;
      
    
    case LUCK:
    temp=EventProcStatusVar[EventId].Status4;
    EventProcStatusVar[EventId].Status4=0;
    break;
  }
  SET_STRUCT_SUM(EventProcStatusVar[EventId]);  
  return  temp;
}
/********************************************************************************
����ԭ�ͣ�void Read_Event_Status(INT8U EventId)
�������ܣ��ⲿ(��485�ӿ�)����¼��Ƿ���
          ע�⣺���¼��ǳɶԷ��������������״̬һֱ���ڣ������ǳɶԷ��������¼�����һ����ʱ���Զ����
��ڣ�    EventId---------�¼�ID
���ڣ�0---------�޴��¼�������1---------���¼�������
*********************************************************************************/
INT8U Read_Event_Status(INT8U Id)
{
  if(Id>MAX_EVENT_NUM)
    return 0;

  return  (EventProcStatusVar[Id].Status);
}
/********************************************************************************
����ԭ�ͣ�void Check_Event_End(INT8U EventId)
�������ܣ��жϽ����¼��Ƿ�����������¼��Ƿ����������ͽ�������Ҫ����Read_Event_Status()����
��ڣ�    EventId---------�¼�ID
���ڣ�1---------���¼��Ѿ�������0---------���¼�������
*********************************************************************************/
INT8U Check_Event_End(INT8U Id)
{
  if(Id>MAX_EVENT_NUM)
    return 0;
  
  if(EventPropertyVar[Id].DoubleFlag==1)    //�ж��Ƿ��ǽ����¼�    
    ASSERT_FAILED();  
  if(Get_Event_Instant(Id)==0)
    return 1;
  
  return  0;
}
/***********************************************************************
�������ܣ���ȡ�������״̬��,����Э���ʽ��֡
��ڣ���
���ڣ���
***********************************************************************/
void Get_Meter_Run_Status(void)
{

  INT8U temp[12];
  if(CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK)==0)
  ASSERT_FAILED();  
  
  //�������״̬��1
  Meter_Run_Status.Meter_Stat1.Word=0; 
  Meter_Run_Status.Meter_Stat1.Bit.Bit1=Get_Demand_Run_Mode();                        //�������㷽ʽ:(0���1����)
  Meter_Run_Status.Meter_Stat1.Bit.Bit2=Read_Event_Status(ID_EVENT_RTC_BAT_LOW);    //�ڲ����Ƿѹ��0--������1----Ƿѹ��
  Meter_Run_Status.Meter_Stat1.Bit.Bit3=Read_Event_Status(ID_EVENT_LOWPWR_BAT_LOW);  //�͹��ĵ�ص�ѹ��0--������1----Ƿѹ��
  Meter_Run_Status.Meter_Stat1.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir; //���й�����0--����1----����
  Meter_Run_Status.Meter_Stat1.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir; //���޹�����0--����1----����

  
  //�������״̬��2
  Meter_Run_Status.Meter_Stat2.Word=0; 
  Meter_Run_Status.Meter_Stat2.Bit.Bit0=Measu_Status_Mode_ToPub_PUCK.A_APwrDir;   //A�й�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit1=Measu_Status_Mode_ToPub_PUCK.B_APwrDir;   //B�й�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit2=Measu_Status_Mode_ToPub_PUCK.C_APwrDir;   //C�й�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.A_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.B_RPwrDir;   //�޹�����0--����1----����
  Meter_Run_Status.Meter_Stat2.Bit.Bit6=Measu_Status_Mode_ToPub_PUCK.C_RPwrDir;   //�޹�����0--����1----����

  
  
  //�������״̬��3 PDI_CUR_DATE_TABLE_SCHEME
  Meter_Run_Status.Meter_Stat3.Word=0; 
  Get_Cur_Rate_Info(temp,temp,sizeof(temp));
  Meter_Run_Status.Meter_Stat3.Bit.Bit0=(INT8U)(temp[2]&0x01);    //��ǰ����ʱ�Σ�0��һ�ף�1�ڶ���
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit1=0;    //���緽ʽ(bit2/bit1):00����Դ��01������Դ��10��ع���
  if(JUDGE_POWER_OFF)
    Meter_Run_Status.Meter_Stat3.Bit.Bit2=1;
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit3=Read_Event_Status(ID_EVENT_PRGKEY_ON);     //��̼���(����)  
  Meter_Run_Status.Meter_Stat3.Bit.Bit5=(INT8U)(temp[0]&0x01);   //��ǰ����ʱ�� (0��һ�ף�1�ڶ���)  
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit8=GET_BIT(temp[9],0);    // Bit9/Bit8:�������(00��Ԥ����,0x01������Ԥ���ѱ�,0x10�����Ԥ���ѱ�)
  Meter_Run_Status.Meter_Stat3.Bit.Bit9=GET_BIT(temp[9],1);    // Bit9/Bit8:�������(00��Ԥ����,0x01������Ԥ���ѱ�,0x10�����Ԥ���ѱ�)
  Meter_Run_Status.Meter_Stat3.Bit.Bit10=GET_BIT(temp[6],0);    //��ǰ���з�ʱ����(0��һ�ף�1�ڶ���)
  Meter_Run_Status.Meter_Stat3.Bit.Bit11=GET_BIT(temp[7],0);    //��ǰ���ݣ�0��һ�ף�1�ڶ��ף�

  temp[0]=Get_Alarm_Relay_Status();
  Meter_Run_Status.Meter_Stat3.Bit.Bit4=GET_BIT(temp[0],4);     //�̵���״̬:0ͨ��1��
  Meter_Run_Status.Meter_Stat3.Bit.Bit6=GET_BIT(temp[0],6);     //�̵�������״̬(0ͨ��1��)
  Meter_Run_Status.Meter_Stat3.Bit.Bit7=GET_BIT(temp[0],7);     //Ԥ��բ����״̬(0�ޣ�1��)
  
  
  //�������״̬��4
  Meter_Run_Status.Meter_Stat4.Word=0; 
  Meter_Run_Status.Meter_Stat4.Bit.Bit0=Read_Event_Status(ID_EVENT_A_LOSS_VOLT);
                                        //Read_Event_Status(ID_EVENT_AB_LOSS_VOLT)|\
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_VOLT)|\
                                        //Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//A��ʧѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat4.Bit.Bit1=Read_Event_Status(ID_EVENT_A_VOLT_LESS);   //A��Ƿѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat4.Bit.Bit2=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);   //A���ѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat4.Bit.Bit3=Read_Event_Status(ID_EVENT_A_LOSS_CURR);
                                        //Read_Event_Status(ID_EVENT_AB_LOSS_CURR)|\
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_CURR)|\
                                        //Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //A��ʧ����0--��ʧ����1----ʧ��;
  Meter_Run_Status.Meter_Stat4.Bit.Bit4=Read_Event_Status(ID_EVENT_A_OVER_CURR);    //A�������0--û������1----������
  Meter_Run_Status.Meter_Stat4.Bit.Bit5=Read_Event_Status(ID_EVENT_A_POWER_EXCEED);    //A����أ�0--û������1----������
  
  Meter_Run_Status.Meter_Stat4.Bit.Bit6=Read_Event_Status(ID_EVENT_A_NEG_CURR);     //A����0--����1----����
  Meter_Run_Status.Meter_Stat4.Bit.Bit7=Read_Event_Status(ID_EVENT_A_LOSS_PARSE);   //A���ࣺ0--����1----����
  
  
  //�������״̬��5
  Meter_Run_Status.Meter_Stat5.Word=0; 
  Meter_Run_Status.Meter_Stat5.Bit.Bit0=Read_Event_Status(ID_EVENT_B_LOSS_VOLT);
                                       // Read_Event_Status(ID_EVENT_AB_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//B��ʧѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat5.Bit.Bit1=Read_Event_Status(ID_EVENT_B_VOLT_LESS);   //B��Ƿѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat5.Bit.Bit2=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);   //B���ѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat5.Bit.Bit3=Read_Event_Status(ID_EVENT_B_LOSS_CURR);
                                        //Read_Event_Status(ID_EVENT_AB_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //B��ʧ����0--��ʧ����1----ʧ��;
  Meter_Run_Status.Meter_Stat5.Bit.Bit4=Read_Event_Status(ID_EVENT_B_OVER_CURR);    //B�������0--û������1----������
  Meter_Run_Status.Meter_Stat5.Bit.Bit5=Read_Event_Status(ID_EVENT_B_POWER_EXCEED);    //B����أ�0--û������1----������
  
  Meter_Run_Status.Meter_Stat5.Bit.Bit6=Read_Event_Status(ID_EVENT_B_NEG_CURR);     //B�෴��0--����1----����
  Meter_Run_Status.Meter_Stat5.Bit.Bit7=Read_Event_Status(ID_EVENT_B_LOSS_PARSE);   //B����ࣺ0--����1----����
  
  //�������״̬��6
  Meter_Run_Status.Meter_Stat6.Word=0; 
  Meter_Run_Status.Meter_Stat6.Bit.Bit0=Read_Event_Status(ID_EVENT_C_LOSS_VOLT);
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//C��ʧѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat6.Bit.Bit1=Read_Event_Status(ID_EVENT_C_VOLT_LESS);   //C��Ƿѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat6.Bit.Bit2=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);   //C���ѹ��0--û������1----������
  Meter_Run_Status.Meter_Stat6.Bit.Bit3=Read_Event_Status(ID_EVENT_C_LOSS_CURR);
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //C��ʧ����0--��ʧ����1----ʧ��;
  Meter_Run_Status.Meter_Stat6.Bit.Bit4=Read_Event_Status(ID_EVENT_C_OVER_CURR);    //C�������0--û������1----������
  Meter_Run_Status.Meter_Stat6.Bit.Bit5=Read_Event_Status(ID_EVENT_C_POWER_EXCEED);    //C����أ�0--û������1----������
  
  Meter_Run_Status.Meter_Stat6.Bit.Bit6=Read_Event_Status(ID_EVENT_C_NEG_CURR);      //C�෴��0--����1----����
  Meter_Run_Status.Meter_Stat6.Bit.Bit7=Read_Event_Status(ID_EVENT_C_LOSS_PARSE);   //C����ࣺ0--����1----����
  
  
  //�������״̬��7
  Meter_Run_Status.Meter_Stat7.Word=0; 
  Meter_Run_Status.Meter_Stat7.Bit.Bit0=Read_Event_Status(ID_EVENT_VOLT_NEG_SEQ);  //��ѹ������0--������1----������
  Meter_Run_Status.Meter_Stat7.Bit.Bit1=Read_Event_Status(ID_EVENT_CUR_NEG_SEQ);   //����������0--������1----������
  Meter_Run_Status.Meter_Stat7.Bit.Bit2=Read_Event_Status(ID_EVENT_VOLT_NO_EVEN);   //��ѹ��ƽ�⣺0--û������1----������
  Meter_Run_Status.Meter_Stat7.Bit.Bit3=Read_Event_Status(ID_EVENT_CURR_NO_EVEN);   //������ƽ�⣺0--û������1----������
  Meter_Run_Status.Meter_Stat7.Bit.Bit4=Read_Event_Status(ID_EVENT_AUX_POWER);      //������Դʧ��
  Meter_Run_Status.Meter_Stat7.Bit.Bit5=JUDGE_POWER_OFF;                            //����
  Meter_Run_Status.Meter_Stat7.Bit.Bit6=Read_Event_Status(ID_EVENT_POS_ACT_DEMAND_EXCEED)|\
                                        Read_Event_Status(ID_EVENT_NEG_ACT_DEMAND_EXCEED);      //��������
  Meter_Run_Status.Meter_Stat7.Bit.Bit7=Read_Event_Status(ID_EVENT_ALL_FACTOR_LOW);      //�ܹ�������������
  Meter_Run_Status.Meter_Stat7.Bit.Bit8=Read_Event_Status(ID_EVENT_CURR_NO_EVEN);       //�������ز�ƽ��
  
  
  //�������״̬��8
  Meter_Run_Status.Meter_Stat8.Word=0; 
  Meter_Run_Status.Meter_Stat8.Bit.Bit0=0;                                         //����բ����״̬��0��բ��1��բ��
  Meter_Run_Status.Meter_Stat8.Bit.Bit1=(Get_Switch_Status() EQ SWITCH_OFF);       //����բʵ��״̬��0��բ��1��բ��
  Meter_Run_Status.Meter_Stat8.Bit.Bit2=0;                                         //��ǰ����բ��ʽ��0��ƽ��1�������壩
  Meter_Run_Status.Meter_Stat8.Bit.Bit8=0;                                         //��������״̬��0��������1������
  Meter_Run_Status.Meter_Stat8.Bit.Bit9=0;                                         //����ʵ��״̬��0��������1������

  /*
  //��ȫ��֤������Ϣ��
  Meter_Run_Status.SERR.Word=0; 
  Meter_Run_Status.SERR.Bit.Bit2=Card_Error_State.CardErrorState.;              //ESAM��֤ʧ��
  Meter_Run_Status.SERR.Bit.Bit3=Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr | \
                                 Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr;              //�����֤ʧ��
  Meter_Run_Status.SERR.Bit.Bit4=Card_Error_State.CardErrorState.CardIdErr;              //�ͻ���Ų�ƥ��
  Meter_Run_Status.SERR.Bit.Bit5=Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR;              //��ֵ��������
  Meter_Run_Status.SERR.Bit.Bit6=Card_Error_State.CardErrorState.MoneyLimitErr;              //���糬�ڻ�
*/
  
  //����������/����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=0;  //���������1��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=0;  //���������2:
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=0;  //���������3��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=0;  //���������4��
  
  if(Judge_I_Start())  //������������������
  {
    switch(Measu_InstantData_ToPub_PUCK.Quadrant.Sum)
    {
    case QUADRANT1:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=1;
      break;
    case QUADRANT2:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=1;
      break;
    case QUADRANT3:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=1;
      break;
    case QUADRANT4:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=1;
      break;
    }
  }
  else
    Meter_Run_Status.NegCurr_Qudrant.Byte&=0xf0;
    
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit4=Read_Event_Status(ID_EVENT_A_NEG_CURR);    //A����������ԣ�0--������1----��;
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit5=Read_Event_Status(ID_EVENT_B_NEG_CURR);    //B����������ԣ�0--������1----����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit6=Read_Event_Status(ID_EVENT_C_NEG_CURR);    //C����������ԣ�0--������1----����
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit7=0;                                          //������0
  
  //�̼���/���߶̽�/������λ/�������
  Meter_Run_Status.Key_Event.Bit.Bit0=0;                                       //������0
  Meter_Run_Status.Key_Event.Bit.Bit1=(B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS);      //����ģʽ
  Meter_Run_Status.Key_Event.Bit.Bit2=Read_Event_Status(ID_EVENT_CLR_DEMAND_MAN)|Read_Event_Status(ID_EVENT_CLR_DEMAND_COM) |Read_Event_Status(ID_EVENT_CLR_ALL_DATA); //������λ
  Meter_Run_Status.Key_Event.Bit.Bit3=Read_Event_Status(ID_EVENT_METER_LOCK);   //�������
  Meter_Run_Status.Key_Event.Bit.Bit4=Read_Event_Status(ID_ALARM_OUT);            //���Ƿ���ڱ���ָʾ
  Meter_Run_Status.Key_Event.Bit.Bit5=(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS EQ 0);  //����ģʽ
  Meter_Run_Status.Key_Event.Bit.Bit6=Get_Cal_Exsit();          //У��״̬����ϵͳ����δ����
  Meter_Run_Status.Key_Event.Bit.Bit7=0;                                       //������0
  
  //ͨ��״̬��
  Meter_Run_Status.Comm_Status.Bit.Bit0=GET_BIT(Module_Comm_Status.Var,5);    //���ߣ�??????????
  Meter_Run_Status.Comm_Status.Bit.Bit1=GET_BIT(Module_Comm_Status.Var,0);        //��ǿ0��??????????
  Meter_Run_Status.Comm_Status.Bit.Bit2=GET_BIT(Module_Comm_Status.Var,1);         //��ǿ1��??????????
  Meter_Run_Status.Comm_Status.Bit.Bit3=GET_BIT(Module_Comm_Status.Var,2);        //��ǿ2��??????????
  Meter_Run_Status.Comm_Status.Bit.Bit4=0;                                       //������0
  Meter_Run_Status.Comm_Status.Bit.Bit5=0;                                       //������0
  Meter_Run_Status.Comm_Status.Bit.Bit6=0;                                       //������0
  Meter_Run_Status.Comm_Status.Bit.Bit7=0;                                       //������0 
  
      
  //����
  if(Meter_Run_Status.Meter_Stat4.Bit.Bit5 ||Meter_Run_Status.Meter_Stat5.Bit.Bit5 ||Meter_Run_Status.Meter_Stat6.Bit.Bit5)
    ReNew_Err_Code(DIS_POWER_EXCEED_ERR);  
  else
    Clr_Err_Code(DIS_POWER_EXCEED_ERR);  
  
  //�������ز�ƽ��
  if(Meter_Run_Status.Meter_Stat7.Bit.Bit8 )
    ReNew_Err_Code(DIS_CUR_VERY_NOEVEN_ERR); 
  else
    Clr_Err_Code(DIS_CUR_VERY_NOEVEN_ERR);  
  
  //��ѹ 
  if(Meter_Run_Status.Meter_Stat4.Bit.Bit2 ||Meter_Run_Status.Meter_Stat5.Bit.Bit2 ||Meter_Run_Status.Meter_Stat6.Bit.Bit2)
    ReNew_Err_Code(DIS_VOLT_EXCEED_ERR);  
  else
    Clr_Err_Code(DIS_VOLT_EXCEED_ERR); 
  
  
  //������������
   if(Meter_Run_Status.Meter_Stat7.Bit.Bit7 )
    ReNew_Err_Code(DIS_PF_EXCEED_ERR); 
   else
    Clr_Err_Code(DIS_PF_EXCEED_ERR); 
  
   //���й����������¼�
   if(Meter_Run_Status.Meter_Stat7.Bit.Bit6)
    ReNew_Err_Code(DIS_DEMAND_EXCEED_ERR); 
   else
    Clr_Err_Code(DIS_DEMAND_EXCEED_ERR); 
   
   
   //�ڲ����Ƿѹ
   if(Meter_Run_Status.Meter_Stat1.Bit.Bit2)
    ReNew_Err_Code(DIS_RTCBAT_LOW); 
   else
    Clr_Err_Code(DIS_RTCBAT_LOW); 
   
   
     
  SET_STRUCT_SUM(Meter_Run_Status);
}
/********************************************************************************
����ԭ�ͣ�void Check_Prog_Status(void)
�������ܣ�����Ƿ��ڱ��״̬
��ڣ� 
���ڣ�0---------���Ǳ��״̬��1---------�Ǳ��״̬��
*********************************************************************************/
INT8U Check_Prog_Status(void)
{
  return (Read_Event_Status(ID_EVENT_PRGKEY_ON));  
  
}
/********************************************************************************
����ԭ�ͣ�void Check_MeterAddr_Status(void)
�������ܣ�������ñ��ַ��ť�Ƿ���
��ڣ� 
���ڣ�0---------���ַ��ťû�а��£�1---------���ַ��ť�����ˣ�
*********************************************************************************/
INT8U Check_MeterAddr_Status(void)
{
  return (Read_Event_Status(ID_METER_ADDR_EN));  
  
}

/********************************************************************************
����ԭ�ͣ�INT8U Check_Man_ClrDemd_En(void)
�������ܣ����������������ť�Ƿ���
��ڣ� 
���ڣ�0---------�������ֶ���������1---------�����ֶ�������
*********************************************************************************/
/********************************************************************************
INT8U Check_Man_ClrDemd_En(void)
{
#ifdef MAN_CLR_DEMAND_EN
  return (Read_Event_Status(ID_CLR_DEMAND_KEY)); 
#else
  return 0;
#endif
}
*********************************************************************************/

/********************************************************************************
����ԭ�ͣ�void Check_AB_Switch(void)
�������ܣ�
��ڣ� 
���ڣ�0---------����AB��ʾģʽ�л�״̬��1---------��AB��ʾģʽ�л�״̬��
*********************************************************************************/
#ifdef ID_EVENT_AB_FUNC_KEY
INT8U Check_AB_Switch(void)
{
  static INT8U KeyStatus=0;
  
  if(Get_Sys_Status()==SYS_NORMAL)
    return (Read_Event_Status_Perone(PUCK,ID_EVENT_AB_FUNC_KEY)); 
  if(Get_Sys_Status()==SYS_RESUME)  //10ms��ѯһ��
  {
    if((Inter_Up_Key_STATUS==1)&&(Inter_Down_Key_STATUS==1))  //û�а�ť����
      KeyStatus=0;
    else    //��һ����ť������
      KeyStatus++;
  }
  if(KeyStatus>=80)
  {
    KeyStatus=0;
    return 1;
  }
  return 0;
}
#endif
/********************************************************************************
����ԭ�ͣ�void Check_Event_StruCS(void)
�������ܣ�������¼���ص����нṹ���У���
��ڣ� 
���ڣ�
*********************************************************************************/
void Check_Event_StruCS(void)
{
  INT8U i,Flag;
  ASSERT(1);  //���¸ú����Ĺ켣
    
  for(i=0;i<MAX_EVENT_NUM;i++)
  {
    Flag=CHECK_STRUCT_SUM(EventProcStatusVar[i]);
    if(!Flag)
      ASSERT_FAILED();  
  }
  
  Flag=CHECK_STRUCT_SUM(Meter_Instant_Status);
  if(Flag==0)  //Sram��������¼�˲̬��
  {
    ASSERT_FAILED();
    mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                   (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
    SET_STRUCT_SUM(Meter_Instant_Status);  
  }
  
  Flag=CHECK_STRUCT_SUM(EventInsParaVar);
  if(Flag==0)
  {
    ASSERT_FAILED();
    Init_Event_Instant_Para(); 
  }
  
  Flag=CHECK_STRUCT_SUM(Meter_Run_Status);
  if(Flag==0)  //Sram��������¼�˲̬��
  {
    ASSERT_FAILED();
    mem_set((void *)(&Meter_Run_Status),0,sizeof(Meter_Run_Status),\
                   (void *)(&Meter_Run_Status),sizeof(Meter_Run_Status));
    SET_STRUCT_SUM(Meter_Run_Status);  
  }
  
  Flag=CHECK_STRUCT_SUM(Power_Status);
  Flag&=CHECK_STRUCT_SUM(Not_Even_Data_PUCK);
  //Flag&=CHECK_STRUCT_SUM(Relay_Ctrl_Status);
  Flag&=CHECK_STRUCT_SUM(Clr_Demand_Key);

  
  if(Flag EQ 0)
    ASSERT_FAILED();
 

    
  /*
  if(CHECK_STRUCT_VAR(Loss_Volt_Change)==0)
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Loss_Curr_Change)==0)
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Curr_Neg_Change)==0)
    ASSERT_FAILED();
  */
}
/********************************************************************************
����ԭ�ͣ�void Test_Interr_IO_Status(void)
�������ܣ���ѯ�ж����ŵ�IO��״̬
��ڣ� 
���ڣ�
*********************************************************************************/
void Test_Interr_IO_Status(void)
{    
    if(Inter_Up_Key_STATUS==0)
      Debug_Print("Check Up_Key_Pin IO==0");  
    if(Inter_Down_Key_STATUS==0)
      Debug_Print("Check Down_Key_Pin IO==0"); 
    if(Inter_Left_Key_STATUS==0)
      Debug_Print("Check Left_Key_Pin IO==0"); 
    if(Inter_Right_Key_STATUS==0)
      Debug_Print("Check Right_Key_Pin IO==0"); 
    if(JUDGE_POWER_OFF)
      Debug_Print("Check PowerOff_Pin IO==0"); 
    //if(ALL_V_LOSS_STATUS==0)
    //  Debug_Print("Check LossVolt_Pin IO==0"); 
    
}
/********************************************************************************
����ԭ�ͣ�void ReNew_PwrOff_Status(void)
�������ܣ����õ��������˲ʱ״̬��
*********************************************************************************/
void ReNew_PwrOff_Status(void)
{   
  INT8U i;
  if(CHECK_STRUCT_SUM(Meter_Instant_Status)==0)  //����ǰ�¼���״̬��У��ʹ����������
  {
    ASSERT_FAILED();
     mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                   (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
    SET_STRUCT_SUM(Meter_Instant_Status); 
    return ;
  }
  else
  {
    for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)   //���ݵ���ʱ���¼���������ʵ״̬������ʼ��˲̬�֣�������洢
    {
      if(Read_Event_Status(i))
        Set_Event_Instant(i);
      else
        Clr_Event_Instant(i);
    }    
  }
}
/********************************************************************************
����ԭ�ͣ�void Set_Power_Or_Reset_Ststus(void)
�������ܣ���λǰ������������λ��־
*********************************************************************************/
void Set_PwrOrRst_Status(void)
{
  Set_Event_Instant(ID_EVENT_POWER_OFF);  //�����¼�����
  Power_Status.Power=POWER_OFF;          //�����¼���־
  SET_STRUCT_SUM(Power_Status);
  
  if((Key_Value_Pub.Key.Bit.PrgKey EQ 0)&&(Prg_Key_Status.PrgKeyTime))  //���Ǳ��״̬
  {
    Prg_Key_Status.PrgKeyTime=0;  //�������ǰ���״̬
    SET_STRUCT_SUM(Prg_Key_Status);
  }
}
/********************************************************************************
����ԭ�ͣ�void Save_Event_Data(void)
�������ܣ��ϵ�󣬶Ե�����¼����ݴ洢
*********************************************************************************/
void Save_Event_Data(void)
{
  INT8U Flag,i;
  
  Flag=CHECK_STRUCT_SUM(Power_Status);  
  if(Flag)    //�ϴθ�λǰ��״̬,sram״̬��ȷ
  {
    if(Get_Sys_Status()==SYS_NORMAL)
    {
      if(POWER_OFF!=Power_Status.Power)     //ǰ��û�в��������Ϣ
      {
        Power_Status.Power=ABNORMAL_RESET;      //��Ϊ��λ״̬��Ϊ�ϵ��¼��ж���׼����������Ϊ�ϵ��¼����洢
      }
    } 
  }
  else
    Power_Status.Power=POWER_ON;       //�ϵ��¼���λ��Ϊ�ж���׼��      
  
  if(ABNORMAL_RESET EQ Power_Status.Power)     //��λ�¼�
    Set_Event_Instant(ID_EVENT_RESET); 
  
    
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)  //�����ϴε����˲̬�֣�ǿ�������¼��ķ���
  {
    if(Get_Event_Instant(i))   //��״̬ʵ���Ǵ� �ڿ� ȡ����״̬������ sram״̬
    {
      if(ID_EVENT_POWER_OFF EQ i || ID_EVENT_RESET EQ i)        //�����λ
        Force_Event_Occur_Status(i);     //���緢���¼�
      else
        Set_Event_Occur_Status(i);     //�¼������ˣ��ȴ�������
    }
    else
        Clr_Event_Real_Status(i);
  }
  
  Power_Status.Power=POWER_ON;     //���ϵ�״̬     
  SET_STRUCT_SUM(Power_Status);    
  Event_Judge_Save_Alarm(0,1);    //����ǿ�����õ�˲̬�֣�ģ��һ�ν���    
  Clr_All_Event_Sram();     //������������
  
}
/********************************************************************************
����ԭ�ͣ�void Afer_PwrOff_Proc(void)
�������ܣ�������¼�����
*********************************************************************************/
void PwrOff_Proc_PUCK(void)
{ 
  Clr_All_Loss_Data();         //����ȫʧѹSram����
  Set_Soft_RTC_PUCK(ID_CPU_RTC);        //��ʼ����ʱ��
  ReNew_PwrOff_Status();       //�����˲ʱ״̬��
  Set_PwrOrRst_Status();
}
/********************************************************************************
����ԭ�ͣ�void Event_Proc_Sec(void)
�������ܣ�ÿ����¼��Ĵ������ж�����
*********************************************************************************/
void Event_Proc_Sec(void)
{
  static volatile S_Int32U Sec_Timer_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
    
  if(Sec_Timer_Bak.Var!=Sec_Timer_Pub)
  {
    //Event_Para_Modi();    �¼������ͬһ����
    Check_Event_StruCS();  
    Get_Meter_Instant_Status();  //��ȡ���˲̬��
    Event_Judge_Save_Alarm(1,1);    //ͨ��˲̬�֣���ȡ��������¼���ʵ״̬,�洢�¼���Ϣ,ͬʱ���ⱨ��
   //Test_Interr_IO_Status();
  
    Get_Meter_Run_Status(); 
    Check_RelayOn_Key();   //ÿ���ж��̵�����ť��բ����ť״̬
    Sec_Timer_Bak.Var=Sec_Timer_Pub;
  }
}
/********************************************************************************
����ԭ�ͣ�void Emerg_Event_Proc(void)
�������ܣ���ͻ���¼��ķݶ��
���ڣ�0---------�޴��¼�������1---------���¼�������
*********************************************************************************/
void Emerg_Event_Proc(void)
{
  INT8U i;
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if((EventPropertyVar[i].DoubleFlag==0)&&(Get_Event_Instant(i)))  //���ɶ��¼�������˲̬������
    {
      if(REC_FRAME_CONDITION)
      {
        OS_TimeDly_Ms(10);  
      }
      
      Event_Judge_StartAndEnd(i,1,1);
      
      /*
      Get_Meter_Instant_Status();     
      Event_Judge_Save_Alarm(1,1);    //ͨ��˲̬�֣���ȡ��������¼���ʵ״̬,�洢�¼���Ϣ,ͬʱ���ⱨ��
      */
      return ;
    }    
  }
}
/***********************************************************************
�������ܣ��жϼ̵�����բ����״̬
��ڣ���
���ڣ���
�¼������оݣ�
***********************************************************************/
#define RELAY_ON_KEY_SEC 3
void Check_RelayOn_Key(void)
{
 
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Relay_On_Key_Countr=0;
    return ;
  }
  
  if(Inter_Up_Key_STATUS EQ Inter_Down_Key_STATUS)  //ͬʱ���»���ͬʱû����
  {
    Relay_On_Key_Countr=0;
    return ;
  }
  
  Relay_On_Key_Countr++;
  if(Relay_On_Key_Countr>=0xff)   //��ֹ��ת
    Relay_On_Key_Countr=RELAY_ON_KEY_SEC;
}
/***********************************************************************
�������ܣ��жϼ̵�����բ����״̬
��ڣ���
���ڣ�1-------------------��բ��ť
�¼������оݣ�
***********************************************************************/
INT8U Judge_RelayOn_Key(void)
{  
  if(Relay_On_Key_Countr>=RELAY_ON_KEY_SEC)
  {
    Relay_On_Key_Countr=0;
    return 1;
  }
  return 0;
}
/********************************************************************************

*********************************************************************************/
void Event_main_PUCK(INT8U Flag)
{
  if(Get_Sys_Status()!=SYS_NORMAL)  //ֻ��������Դ��������£��������ִ��
  {
    while(1)
     Task_Sleep();    
  }
  
  if(Get_Sys_Status()!=SYS_NORMAL) //ֻ��������ģʽ�£������¼��Ĵ���
    return ;
  
  if(Flag)
  { 
    Init_All_Event_Sram();
    Save_All_Loss_Data();
    Accmu_RTC_BatTime_PerMin();   //��ʼ����ع���ʱ�������û�н���������̣����ô˺���
    //Init_Toggle_Status();
    OS_TimeDly_Sec(1);
    return ;
  }
  //����ÿ�����һ��
  //Emerg_Event_Proc();     //��ͻ���¼���ÿ10ms����������Channel_Data_Proc_PUCKStatus��ͬ��
  Event_Proc_Sec();       //�������¼���ÿ�봦��
 }  