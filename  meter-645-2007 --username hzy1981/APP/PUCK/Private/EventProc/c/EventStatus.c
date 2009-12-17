#define EVENTSTATUS_C
#include "Pub_PUCK.h"
#include "EventStatus.h"

/***********************************************************************
函数功能：初始化事件状态等参数
入口：1------------强行清除事件瞬态字，和事件发生结果状态字sram；0-------根据CS值来清除
出口：无
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
函数功能：清除所有事件状态
入口：
出口：无
***********************************************************************/
void Clr_All_Event_Sram(void)
{  
  Init_Event_Sram(1);  
}
/***********************************************************************
函数功能：初始化所有事件状态
入口：
出口：无
***********************************************************************/
void Init_All_Event_Sram(void)
{  
  Init_Event_Sram(0);
  
  Clr_Demand_Key.Status=0;
  SET_STRUCT_SUM(Clr_Demand_Key);
  
    //置上电状态
  Power_Status.Power=POWER_ON;          
  SET_STRUCT_SUM(Power_Status);
  
  //不平衡率
  mem_set((void *)(&Not_Even_Data_PUCK),0,sizeof(Not_Even_Data_PUCK),\
                   (void *)(&Not_Even_Data_PUCK),sizeof(Not_Even_Data_PUCK));
  SET_STRUCT_SUM(Not_Even_Data_PUCK);  
}


/***********************************************************************
函数功能：获取时间差值
入口：Temp_PD_Time-------------落后于当前的时间，BCD码
出口：1-------------获取成功，0----------------失败
***********************************************************************/
INT8U Get_Time_Diff(S_Event_Time Temp_PD_Time,INT32U *Diff)
{  
  INT32U LastTime,CurTime;  
  
  //将BCD码转换成 HEX格式
  Bcd2Hex_Buf((INT8U *)PD_Time.Time, sizeof(PD_Time.Time), Temp_PD_Time.Time, Temp_PD_Time.Time, sizeof(Temp_PD_Time.Time));
  
  //上次掉电时间
  LastTime=mktime(((INT16U )Temp_PD_Time.Time[5]+2000),(INT16U )Temp_PD_Time.Time[4],(INT16U )Temp_PD_Time.Time[3],\
                  (INT16U )Temp_PD_Time.Time[2],(INT16U )Temp_PD_Time.Time[1],0);
  
  //当前时间掉电时间
  CurTime=mktime(((INT16U )Cur_Time0.Time[4]+2000),(INT16U )Cur_Time0.Time[3],(INT16U )Cur_Time0.Time[2],\
                  (INT16U )Cur_Time0.Time[1],(INT16U )Cur_Time0.Time[0],0);
  
  if(CurTime>=LastTime)
  {
    *Diff=(CurTime-LastTime)/60;  //得到秒数
    return 1;
  }
  
  return 0;
}
/***********************************************************************
函数功能：存储电池工作时间数据
入口：无
出口：无
注意：上电后Bat_Work_Status.BatRunTime的数据，HUCK已帮我更新反写上次累计数据；
      只有HUCK进入掉电流程后，才初始化此变量。
***********************************************************************/
void Get_Bat_Work_Time(void)
{
  INT32U temp32;
  
  temp32=0;
  
#if (BAT_RUN_TIME&BAT_RUN_TIME_PWROFF)   
  if(Get_Time_Diff(PD_Time,&temp32))
    ASSERT_FAILED();
#endif
  
  DIS_PD_INT;  //关掉电中断
  
  if(CHECK_STRUCT_SUM(Bat_Work_Status))
    Bat_Work_Status.BatRunTime+=temp32;   //上电后，此变量HUCK已经初始化取出
  else
   Bat_Work_Status.BatRunTime=0;   //上电后，此变量HUCK已经初始化取出
  
  SET_STRUCT_SUM(Bat_Work_Status);
   
   EN_PD_INT; //开掉电中断
}
/***********************************************************************
函数功能：上电后，获取编程总时间
入口：无
出口：无
注意：Prg_Key_Status.PrgKeyTime的数据，HUCK已帮我更新反写上次累计数据；
      只有HUCK进入掉电流程后，才初始化此变量。
***********************************************************************/
void Get_Prog_Key_Time(void)
{
  INT32U DiffTime;
    
  DIS_PD_INT;  //关掉电中断
  if(Prg_Key_Status.PrgKeyTime && CHECK_STRUCT_SUM(Prg_Key_Status))  //上电后，处于编程状态，此变量HUCK已经初始化取出
  {
    if(Get_Time_Diff(PD_Time,&DiffTime))     //上次掉电是编程状态，将 InPrgPwroff置
    {
      if(DiffTime<=PRG_KEY_TIME)
      {
        Key_Value_Pub.Key.Bit.PrgKey=1;
        Prg_Key_Status.PrgKeyTime+=DiffTime;
      }
      else       //掉电时间超过编程按钮维持时间，清除编程按钮状态
        Prg_Key_Status.PrgKeyTime=0;      
    }
    else                                      //上次掉电不是编程状态
      Prg_Key_Status.PrgKeyTime=0;
  }
  else
    Prg_Key_Status.PrgKeyTime=0;   //上次掉电不是编程状态
       
  SET_STRUCT_SUM(Prg_Key_Status);
  EN_PD_INT; //开掉电中断
}
/***********************************************************************
函数功能：上电运行时，每分钟对RTC电池工作时间累加
入口：无
出口：无
在HUCK的一分钟任务中自加
***********************************************************************/
void Accmu_RTC_BatTime_PerMin(void)
{
#if (BAT_RUN_TIME&BAT_RUN_TIME_PWRON)  //统计主电源工作下，RTC的运行时间
  INT32U temp32;
  INT8U temp;
  
  //if(Get_Sys_Status()!=SYS_NORMAL) //只有主电源供电下，才存数此数据,HUCK 保证,减少代码量
  // return ;
  
  if(RTC_BAT_LOW EQ 0)  //电池欠压，不统计
    return ;
  
  if(CHECK_STRUCT_SUM(Bat_Work_Status) EQ 0) //校验和不对
  {
    temp=Read_Storage_Data(SDI_BAT_RUN_TIME,(INT8U *)(&temp32),(INT8U *)(&temp32),sizeof(temp32));
    
    if(temp EQ 0)
      ASSERT_FAILED();
    
    DIS_PD_INT;  //关掉电中断
    Bat_Work_Status.BatRunTime=temp32;     
  }
  else
  {
    DIS_PD_INT;  //关掉电中断
    Bat_Work_Status.BatRunTime++;
  }
  
  SET_STRUCT_SUM(Bat_Work_Status);
  EN_PD_INT; //开掉电中断
#endif 
}
/***********************************************************************
函数功能：每隔一段时间存储电池运行时间
入口：无
出口：无
***********************************************************************/
void Period_Save_RTC_BatTime(void)
{
#if (BAT_RUN_TIME&BAT_RUN_TIME_PWRON)  //统计主电源工作下，RTC的运行时间
  
 // if(Get_Sys_Status() != SYS_NORMAL)  //只有主电源供电下，才存数此数据,HUCK 保证,减少代码量
 //  return ;
 
  if(CHECK_STRUCT_SUM(Bat_Work_Status) EQ 0) //校验和不对,不能存,从主存储区更新 sram 数据
  {    
    Accmu_RTC_BatTime_PerMin();        
    return ;
  }

  Write_Storage_Data(SDI_BAT_RUN_TIME,(INT8U *)(&Bat_Work_Status.BatRunTime),sizeof(Bat_Work_Status.BatRunTime));
#endif 
}
/***********************************************************************
函数功能：清除电池工作时间
入口：无
出口：无
***********************************************************************/
void Clr_RTC_BatTime(void)
{
  DIS_PD_INT;  //关掉电中断
  Bat_Work_Status.BatRunTime=0; 
  SET_STRUCT_SUM(Bat_Work_Status);
  EN_PD_INT; //开掉电中断
}
/***********************************************************************
函数功能：上电后，存储上次的掉电数据：事件
入口：无
出口：无
***********************************************************************/
void Save_LastPwrOff_Data_PUCK(void)
{
  Save_Event_Data();
  Get_Bat_Work_Time();
  Get_Prog_Key_Time();
}

/***********************************************************************
函数功能：根据发生的事件Id和状态，设置相应的状态
入口：无
出口：无
***********************************************************************/
void Set_Event_Instant_Status(INT8U Id,INT8U Status)
{
  INT8U Byte,Bit;
  if(Id>=MAX_EVENT_NUM)
    return ;
  
  Byte=Id/8;
  Bit=Id%8;
  DIS_PD_INT;  //关掉电中断
  if(Status)
    SET_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);
  else
    CLR_BIT(Meter_Instant_Status.Instant_Event[Byte],Bit);    
  SET_STRUCT_SUM(Meter_Instant_Status);
  EN_PD_INT; //开掉电中断
}

/***********************************************************************
函数功能：根据发生的事件，设置相应的瞬态状态字
入口：无
出口：无
***********************************************************************/
void Set_Event_Instant(INT8U Id)
{
  if(EventPropertyVar[Id].DoubleFlag==0)  //不成对事件，马上清除原有真实状态
    Clr_Event_Real_Status(Id);
  Set_Event_Instant_Status(Id,1);
}
/***********************************************************************
函数功能：根据位或者字节单位，清除对应的位信息或字节信息
入口：无
出口：无
***********************************************************************/
void Clr_Event_Instant(INT8U Id)
{
  Set_Event_Instant_Status(Id,0); 
}

/***********************************************************************
函数功能：将事件模拟为发生后的状态,为结束做准备
入口：无
出口：无
***********************************************************************/
void Set_Event_Occur_Status(INT8U i)
{
  if(i>MAX_ID_EVENT)
    return ;
  
  mem_set((void *)(EventProcStatusVar+i),0xFF,sizeof(EventProcStatus),\
                 (void *)(EventProcStatusVar),sizeof(EventProcStatusVar));
  
  //置结束计时器单位及计数值
  EventProcStatusVar[i].Mins=1;  
  EventProcStatusVar[i].EndCount=EventPropertyVar[i].EndCount+1;
  SET_STRUCT_SUM(EventProcStatusVar[i]); 
}
/***********************************************************************
函数功能：将事件模拟为结束后的状态,为发生做准备
入口：无
出口：无
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
函数功能：将事件强行发生,并处理发生后的相关信息
入口：事件ID
出口：无
***********************************************************************/
void Force_Event_Occur_Status(INT8U i)
{
  Set_Event_End_Status(i);  
  Event_Judge_StartAndEnd(i,0,1);
}
/***********************************************************************
函数功能：将事件强行结束,并处理结束后的相关信息
入口：事件ID
出口：无
***********************************************************************/
void Force_Event_End_Status(INT8U i)
{
  Set_Event_Occur_Status(i);  
  Event_Judge_StartAndEnd(i,0,1);  
}
/***********************************************************************
函数功能：清除事件发生的真正状态
入口：无
出口：无
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
函数功能：根据位或者字节单位，获取对应的位信息或字节信息
入口：无
出口：无
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
函数原型：void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode)
函数功能：检查事件(成对)发生
CountMode:0----------表示设定次数判定为0，非零-------------按照事件表格时间判定
SaveMode:0----------表示不存储，非零-------------表示存储
*********************************************************************************/
void Event_Judge_StartAndEnd(INT8U Id,INT8U CountMode,INT8U SaveMode)
{
  INT16U ConStartcounts,ConEndcounts;
  INT16U RamStartcounts,RamEndcounts;
  
  if(Id<MIN_ID_EVENT || Id>MAX_ID_EVENT) //保护一下
    return ;
  
  if(CHECK_STRUCT_SUM(EventProcStatusVar[Id])==0)  //校验和不对，防止事件乱存乱搞，清除之
  {
    ASSERT_FAILED();
    Clr_Event_Real_Status(Id);
    return ;
  }
  
  if((0 EQ CountMode)||(Check_Sys_Status()!=SYS_NORMAL))  //非正常模式下，发生和结束只判定一次
  {
    ConStartcounts=1;
    ConEndcounts=1; 
  }
  
  if(Check_Sys_Status()==SYS_NORMAL) //正常模式下，连续判定时间，由表格决定
  {
    if(EventPropertyVar[Id].JudgeTimeSec)  //判定时间,由参数决定
    {
      if(*EventPropertyVar[Id].JudgeTimeSec EQ 0)  //参数取不出，或者读不出
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
    else                                   //判定时间,由表格决定
    {
        ConStartcounts=(EventPropertyVar[Id].StartUnit==0)?\
                    EventPropertyVar[Id].StartCount:((INT16U)EventPropertyVar[Id].StartCount*60);
        ConEndcounts=(EventPropertyVar[Id].EndUnit==0)?\
                    EventPropertyVar[Id].EndCount:((INT16U)EventPropertyVar[Id].EndCount*60);
    }
  }
  
  if(EventProcStatusVar[Id].Occur==0)   //未发生该事件
  {
    if(Get_Event_Instant(Id))  //当前瞬时状态指示了事件的发生
      EventProcStatusVar[Id].StartCount++;
    else                                 //不是连续发生，清计数器
      EventProcStatusVar[Id].StartCount=0;
    
    if(EventProcStatusVar[Id].StartCount>=60)  //分钟计数
    {
      EventProcStatusVar[Id].Mins++;
      EventProcStatusVar[Id].StartCount=0;
    }
      
    RamStartcounts=EventProcStatusVar[Id].Mins*60+(INT16U)EventProcStatusVar[Id].StartCount;
    if(RamStartcounts>=ConStartcounts)  //事件连续发生
    {       
        Debug_Print("Event_Occur----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[Id].EventName,Id,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec);  
     
      if((EventPropertyVar[Id].StartSave)&&(0!=SaveMode))
      {
        //现将系统状态字置位，为Event_Data_Proc()服务
        EventProcStatusVar[Id].Status=1;
        Get_Meter_Run_Status();
        //将系统状态字清0，作为Event_Data_Proc()某些判定的条件
        EventProcStatusVar[Id].Status=0;
        
        Event_Data_Proc(Id,EVENT_OCCUR);  //调用事件发生存储函数
        Debug_Print("Write Event_Occur----->%s(%d)",EventPropertyVar[Id].EventName,Id);
        //OS_TimeDly_Ms(10);  
      }
      EventProcStatusVar[Id].Occur=1; EventProcStatusVar[Id].Status=1;  
      EventProcStatusVar[Id].Status1=1; EventProcStatusVar[Id].Status2=1; 
      EventProcStatusVar[Id].Status3=1; EventProcStatusVar[Id].Status4=1; 
      EventProcStatusVar[Id].StartCount=0;EventProcStatusVar[Id].EndCount=0;  
      EventProcStatusVar[Id].Mins=0;

      if(EventPropertyVar[Id].DoubleFlag==0)  //对于不成对的事件，马上清除发生瞬态字
      {
          Clr_Event_Instant(Id); //清除对应瞬时状态字，用于对紧急时候的事件回应
          //Debug_Print("Emergece Event End,Clear Instant---------->%s",EventPropertyVar[Id].EventName);
      }
      if(EventPropertyVar[Id].DoubleFlag &&ConEndcounts==0)  //成对的事件，需要马上清除发生瞬态字
         Clr_Event_Instant(Id);
    }
  }
  else                         //已经发生了该事件,清除计数器开始计数
  {
    if(EventPropertyVar[Id].DoubleFlag==1)  //成对事件
    {
      if(EventProcStatusVar[Id].Status==1)  //成对事件发生后,判结束事件
      {
        if(Get_Event_Instant(Id)==0)  //在结束进行时
          EventProcStatusVar[Id].EndCount++;
        else                          
        {
          if(EventPropertyVar[Id].ForbitEnd==0)       //不需要强行结束
            EventProcStatusVar[Id].EndCount=0;         //不是连续结束，清计数器
          else                                    //需要强行结束,但需延时,计数器更新
          {
            Clr_Event_Instant(Id); //强行清除对应瞬时状态字
            EventProcStatusVar[Id].EndCount++;
            if(EventPropertyVar[Id].EndIndex<MAX_END_TIME_NUM)
              ConEndcounts=Const_End_Time[EventPropertyVar[Id].EndIndex]; 
            else
              ASSERT_FAILED();
          }
        }          
      }
    }
    else                                //不是成对事件：发生后立即启动清除计数器计数
    {
      Clr_Event_Instant(Id); //强行清除对应瞬时状态字-------PUCK!!!!!!!!!
      EventProcStatusVar[Id].EndCount++;
    }
    
    if(EventProcStatusVar[Id].EndCount>=60)  //分钟计数
    {
      EventProcStatusVar[Id].Mins++;
      EventProcStatusVar[Id].EndCount=0;
    }
    RamEndcounts=EventProcStatusVar[Id].Mins*60+(INT16U)EventProcStatusVar[Id].EndCount; 
    if(RamEndcounts>=ConEndcounts)  //事件结束/恢复
    {
       Debug_Print("Event_End----->%s(%d)(%x-%x-%x %x:%x:%x)",EventPropertyVar[Id].EventName,Id,\
                        Cur_Time1.Year,Cur_Time1.Month,Cur_Time1.Date,Cur_Time1.Hour,Cur_Time1.Min,Cur_Time1.Sec); 
       if((EventPropertyVar[Id].EndSave)&&(0!=SaveMode))
       {
         //现将系统状态字清0，为Event_Data_Proc()服务
        EventProcStatusVar[Id].Status=0;
        Get_Meter_Run_Status();
        //将系统状态字还原，作为Event_Data_Proc()某些判定的条件
        EventProcStatusVar[Id].Status=1;
        
         Event_Data_Proc(Id,EVENT_END);  //调用事件发生存储函数
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
函数原型：void Get_Meter_Instant_Status(void)
函数功能：获取表计瞬态字,通过函数指针调用相应函数实现
*********************************************************************************/
void Get_Meter_Instant_Status(void)
{
  INT8U i;
  
  if(Check_Power_Grid_Event(0))
  {
    Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT);  //A电压失压清除
    Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT);  //B电压失压清除
    Clr_Event_Instant(ID_EVENT_C_LOSS_VOLT);  //C电压失压清除    
   
    Clr_Event_Instant(ID_EVENT_A_VOLT_LESS);  //A电压欠压清除
    Clr_Event_Instant(ID_EVENT_B_VOLT_LESS);  //B电压欠压清除
    Clr_Event_Instant(ID_EVENT_C_VOLT_LESS);  //C电压欠压清除
    
    Clr_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);  //A电压过压清除
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  //B电压过压清除
    Clr_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);  //C电压过压清除
    
    
    Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE);  //A相没有断相
    Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  //B相没有断相
    Clr_Event_Instant(ID_EVENT_C_LOSS_PARSE);  //C相没有断相
    
    
    Clr_Event_Instant(ID_EVENT_VOLT_NO_EVEN);  //没有电压不平衡
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //没有电流不平衡
    
    Clr_Event_Instant(ID_EVENT_A_LOSS_CURR);  //A相没有失流
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR);  //B相没有失流
    Clr_Event_Instant(ID_EVENT_C_LOSS_CURR);  //C相没有失流
    //Clr_Event_Instant(ID_EVENT_AB_LOSS_CURR);  //AB相没有失流
    //Clr_Event_Instant(ID_EVENT_AC_LOSS_CURR);  //AC相没有失流
    //Clr_Event_Instant(ID_EVENT_BC_LOSS_CURR);  //BC相没有失流
    //Clr_Event_Instant(ID_EVENT_ALL_LOSS_CURR);  //ABC相没有失流    
    
    Clr_Event_Instant(ID_EVENT_A_NEG_CURR); //A电流反向
    Clr_Event_Instant(ID_EVENT_B_NEG_CURR);  //B电流反向
    Clr_Event_Instant(ID_EVENT_C_NEG_CURR);  //C电流反向
    Clr_Event_Instant(ID_EVENT_SUM_NEG_CURR);  //有功功率反相
    
    Clr_Event_Instant(ID_EVENT_A_OVER_CURR);  //A过流清除
    Clr_Event_Instant(ID_EVENT_B_OVER_CURR);  //B过流清除
    Clr_Event_Instant(ID_EVENT_C_OVER_CURR);  //C过流清除
    
    return ;
  }
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if(EventPropertyVar[i].GetInstStatus)
      EventPropertyVar[i].GetInstStatus();
  }
}
/********************************************************************************
函数原型：void Event_Judge_Save_Alarm(INT8U Flag)
函数功能：所有事件发生/结束判定，,同时对外报警
*********************************************************************************/
void Event_Judge_Save_Alarm(INT8U CountMode,INT8U SaveMode)
{
  INT8U i;  
    
  if(Get_Cal_Exsit())     //校表状态下，不跑事件
    return ;
  
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    Clear_All_Dog();
    /*
    if(Get_Main_Init_Flag() !=  MAIN_INITING)  //任务初始化状态
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
函数原型：void Read_Event_Status_Perone(INT8U PersonID,INT8U EventId)
函数功能：用于内部个人检查是否发生,读后清除
入口：    PersonID--------个人ID
          EventId---------事件ID
出口：0---------无此事件产生；1---------此事件发生；
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
函数原型：void Read_Event_Status(INT8U EventId)
函数功能：外部(如485接口)检查事件是否发生
          注意：若事件是成对发生，读后不清除，状态一直存在；若不是成对发生，此事件会在一定的时间自动清除
入口：    EventId---------事件ID
出口：0---------无此事件产生；1---------此事件发生；
*********************************************************************************/
INT8U Read_Event_Status(INT8U Id)
{
  if(Id>MAX_EVENT_NUM)
    return 0;

  return  (EventProcStatusVar[Id].Status);
}
/********************************************************************************
函数原型：void Check_Event_End(INT8U EventId)
函数功能：判断紧急事件是否结束，对于事件是否真正发生和结束，需要调用Read_Event_Status()函数
入口：    EventId---------事件ID
出口：1---------此事件已经结束；0---------此事件发生；
*********************************************************************************/
INT8U Check_Event_End(INT8U Id)
{
  if(Id>MAX_EVENT_NUM)
    return 0;
  
  if(EventPropertyVar[Id].DoubleFlag==1)    //判断是否是紧急事件    
    ASSERT_FAILED();  
  if(Get_Event_Instant(Id)==0)
    return 1;
  
  return  0;
}
/***********************************************************************
函数功能：获取电表运行状态字,按照协议格式组帧
入口：无
出口：无
***********************************************************************/
void Get_Meter_Run_Status(void)
{

  INT8U temp[12];
  if(CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK)==0)
  ASSERT_FAILED();  
  
  //电表运行状态字1
  Meter_Run_Status.Meter_Stat1.Word=0; 
  Meter_Run_Status.Meter_Stat1.Bit.Bit1=Get_Demand_Run_Mode();                        //需量积算方式:(0滑差，1区间)
  Meter_Run_Status.Meter_Stat1.Bit.Bit2=Read_Event_Status(ID_EVENT_RTC_BAT_LOW);    //内部电池欠压：0--正常；1----欠压；
  Meter_Run_Status.Meter_Stat1.Bit.Bit3=Read_Event_Status(ID_EVENT_LOWPWR_BAT_LOW);  //低功耗电池电压：0--正常；1----欠压；
  Meter_Run_Status.Meter_Stat1.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir; //总有功方向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat1.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir; //总无功方向：0--正向；1----反向；

  
  //电表运行状态字2
  Meter_Run_Status.Meter_Stat2.Word=0; 
  Meter_Run_Status.Meter_Stat2.Bit.Bit0=Measu_Status_Mode_ToPub_PUCK.A_APwrDir;   //A有功方向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat2.Bit.Bit1=Measu_Status_Mode_ToPub_PUCK.B_APwrDir;   //B有功方向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat2.Bit.Bit2=Measu_Status_Mode_ToPub_PUCK.C_APwrDir;   //C有功方向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat2.Bit.Bit4=Measu_Status_Mode_ToPub_PUCK.A_RPwrDir;   //无功方向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat2.Bit.Bit5=Measu_Status_Mode_ToPub_PUCK.B_RPwrDir;   //无功方向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat2.Bit.Bit6=Measu_Status_Mode_ToPub_PUCK.C_RPwrDir;   //无功方向：0--正向；1----反向；

  
  
  //电表运行状态字3 PDI_CUR_DATE_TABLE_SCHEME
  Meter_Run_Status.Meter_Stat3.Word=0; 
  Get_Cur_Rate_Info(temp,temp,sizeof(temp));
  Meter_Run_Status.Meter_Stat3.Bit.Bit0=(INT8U)(temp[2]&0x01);    //当前运行时段：0第一套，1第二套
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit1=0;    //供电方式(bit2/bit1):00主电源，01辅助电源，10电池供电
  if(JUDGE_POWER_OFF)
    Meter_Run_Status.Meter_Stat3.Bit.Bit2=1;
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit3=Read_Event_Status(ID_EVENT_PRGKEY_ON);     //编程键打开(允许)  
  Meter_Run_Status.Meter_Stat3.Bit.Bit5=(INT8U)(temp[0]&0x01);   //当前运行时区 (0第一套，1第二套)  
  
  Meter_Run_Status.Meter_Stat3.Bit.Bit8=GET_BIT(temp[9],0);    // Bit9/Bit8:电表类型(00非预付费,0x01电量型预付费表,0x10电费型预付费表)
  Meter_Run_Status.Meter_Stat3.Bit.Bit9=GET_BIT(temp[9],1);    // Bit9/Bit8:电表类型(00非预付费,0x01电量型预付费表,0x10电费型预付费表)
  Meter_Run_Status.Meter_Stat3.Bit.Bit10=GET_BIT(temp[6],0);    //当前运行分时费率(0第一套，1第二套)
  Meter_Run_Status.Meter_Stat3.Bit.Bit11=GET_BIT(temp[7],0);    //当前阶梯（0第一套，1第二套）

  temp[0]=Get_Alarm_Relay_Status();
  Meter_Run_Status.Meter_Stat3.Bit.Bit4=GET_BIT(temp[0],4);     //继电器状态:0通，1断
  Meter_Run_Status.Meter_Stat3.Bit.Bit6=GET_BIT(temp[0],6);     //继电器命令状态(0通，1断)
  Meter_Run_Status.Meter_Stat3.Bit.Bit7=GET_BIT(temp[0],7);     //预跳闸报警状态(0无，1有)
  
  
  //电表运行状态字4
  Meter_Run_Status.Meter_Stat4.Word=0; 
  Meter_Run_Status.Meter_Stat4.Bit.Bit0=Read_Event_Status(ID_EVENT_A_LOSS_VOLT);
                                        //Read_Event_Status(ID_EVENT_AB_LOSS_VOLT)|\
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_VOLT)|\
                                        //Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//A相失压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat4.Bit.Bit1=Read_Event_Status(ID_EVENT_A_VOLT_LESS);   //A相欠压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat4.Bit.Bit2=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);   //A相过压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat4.Bit.Bit3=Read_Event_Status(ID_EVENT_A_LOSS_CURR);
                                        //Read_Event_Status(ID_EVENT_AB_LOSS_CURR)|\
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_CURR)|\
                                        //Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //A相失流：0--不失流；1----失流;
  Meter_Run_Status.Meter_Stat4.Bit.Bit4=Read_Event_Status(ID_EVENT_A_OVER_CURR);    //A相过流：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat4.Bit.Bit5=Read_Event_Status(ID_EVENT_A_POWER_EXCEED);    //A相过载：0--没发生；1----发生；
  
  Meter_Run_Status.Meter_Stat4.Bit.Bit6=Read_Event_Status(ID_EVENT_A_NEG_CURR);     //A反向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat4.Bit.Bit7=Read_Event_Status(ID_EVENT_A_LOSS_PARSE);   //A断相：0--正向；1----反向；
  
  
  //电表运行状态字5
  Meter_Run_Status.Meter_Stat5.Word=0; 
  Meter_Run_Status.Meter_Stat5.Bit.Bit0=Read_Event_Status(ID_EVENT_B_LOSS_VOLT);
                                       // Read_Event_Status(ID_EVENT_AB_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//B相失压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat5.Bit.Bit1=Read_Event_Status(ID_EVENT_B_VOLT_LESS);   //B相欠压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat5.Bit.Bit2=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);   //B相过压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat5.Bit.Bit3=Read_Event_Status(ID_EVENT_B_LOSS_CURR);
                                        //Read_Event_Status(ID_EVENT_AB_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //B相失流：0--不失流；1----失流;
  Meter_Run_Status.Meter_Stat5.Bit.Bit4=Read_Event_Status(ID_EVENT_B_OVER_CURR);    //B相过流：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat5.Bit.Bit5=Read_Event_Status(ID_EVENT_B_POWER_EXCEED);    //B相过载：0--没发生；1----发生；
  
  Meter_Run_Status.Meter_Stat5.Bit.Bit6=Read_Event_Status(ID_EVENT_B_NEG_CURR);     //B相反向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat5.Bit.Bit7=Read_Event_Status(ID_EVENT_B_LOSS_PARSE);   //B相断相：0--正向；1----反向；
  
  //电表运行状态字6
  Meter_Run_Status.Meter_Stat6.Word=0; 
  Meter_Run_Status.Meter_Stat6.Bit.Bit0=Read_Event_Status(ID_EVENT_C_LOSS_VOLT);
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_VOLT)|\
                                        Read_Event_Status(ID_EVENT_ABC_LOSS_VOLT);//C相失压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat6.Bit.Bit1=Read_Event_Status(ID_EVENT_C_VOLT_LESS);   //C相欠压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat6.Bit.Bit2=Read_Event_Status(ID_EVENT_A_VOLT_OVERLOAD);   //C相过压：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat6.Bit.Bit3=Read_Event_Status(ID_EVENT_C_LOSS_CURR);
                                        //Read_Event_Status(ID_EVENT_AC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_BC_LOSS_CURR)|\
                                        Read_Event_Status(ID_EVENT_ALL_LOSS_CURR);  //C相失流：0--不失流；1----失流;
  Meter_Run_Status.Meter_Stat6.Bit.Bit4=Read_Event_Status(ID_EVENT_C_OVER_CURR);    //C相过流：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat6.Bit.Bit5=Read_Event_Status(ID_EVENT_C_POWER_EXCEED);    //C相过载：0--没发生；1----发生；
  
  Meter_Run_Status.Meter_Stat6.Bit.Bit6=Read_Event_Status(ID_EVENT_C_NEG_CURR);      //C相反向：0--正向；1----反向；
  Meter_Run_Status.Meter_Stat6.Bit.Bit7=Read_Event_Status(ID_EVENT_C_LOSS_PARSE);   //C相断相：0--正向；1----反向；
  
  
  //电表运行状态字7
  Meter_Run_Status.Meter_Stat7.Word=0; 
  Meter_Run_Status.Meter_Stat7.Bit.Bit0=Read_Event_Status(ID_EVENT_VOLT_NEG_SEQ);  //电压逆相序：0--正相序；1----逆相序；
  Meter_Run_Status.Meter_Stat7.Bit.Bit1=Read_Event_Status(ID_EVENT_CUR_NEG_SEQ);   //电流逆相序：0--正相序；1----逆相序；
  Meter_Run_Status.Meter_Stat7.Bit.Bit2=Read_Event_Status(ID_EVENT_VOLT_NO_EVEN);   //电压不平衡：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat7.Bit.Bit3=Read_Event_Status(ID_EVENT_CURR_NO_EVEN);   //电流不平衡：0--没发生；1----发生；
  Meter_Run_Status.Meter_Stat7.Bit.Bit4=Read_Event_Status(ID_EVENT_AUX_POWER);      //辅助电源失电
  Meter_Run_Status.Meter_Stat7.Bit.Bit5=JUDGE_POWER_OFF;                            //掉电
  Meter_Run_Status.Meter_Stat7.Bit.Bit6=Read_Event_Status(ID_EVENT_POS_ACT_DEMAND_EXCEED)|\
                                        Read_Event_Status(ID_EVENT_NEG_ACT_DEMAND_EXCEED);      //需量超限
  Meter_Run_Status.Meter_Stat7.Bit.Bit7=Read_Event_Status(ID_EVENT_ALL_FACTOR_LOW);      //总功率因数超下限
  Meter_Run_Status.Meter_Stat7.Bit.Bit8=Read_Event_Status(ID_EVENT_CURR_NO_EVEN);       //电流严重不平衡
  
  
  //电表运行状态字8
  Meter_Run_Status.Meter_Stat8.Word=0; 
  Meter_Run_Status.Meter_Stat8.Bit.Bit0=0;                                         //拉合闸命令状态（0合闸，1拉闸）
  Meter_Run_Status.Meter_Stat8.Bit.Bit1=(Get_Switch_Status() EQ SWITCH_OFF);       //拉合闸实际状态（0合闸，1拉闸）
  Meter_Run_Status.Meter_Stat8.Bit.Bit2=0;                                         //当前拉合闸方式（0电平，1连续脉冲）
  Meter_Run_Status.Meter_Stat8.Bit.Bit8=0;                                         //报警命令状态（0不报警，1报警）
  Meter_Run_Status.Meter_Stat8.Bit.Bit9=0;                                         //报警实际状态（0不报警，1报警）

  /*
  //安全认证错误信息字
  Meter_Run_Status.SERR.Word=0; 
  Meter_Run_Status.SERR.Bit.Bit2=Card_Error_State.CardErrorState.;              //ESAM验证失败
  Meter_Run_Status.SERR.Bit.Bit3=Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr | \
                                 Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr;              //身份认证失败
  Meter_Run_Status.SERR.Bit.Bit4=Card_Error_State.CardErrorState.CardIdErr;              //客户编号不匹配
  Meter_Run_Status.SERR.Bit.Bit5=Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR;              //充值次数错误
  Meter_Run_Status.SERR.Bit.Bit6=Card_Error_State.CardErrorState.MoneyLimitErr;              //购电超囤积
*/
  
  //电流反极性/象限
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=0;  //电表工作象限1：
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=0;  //电表工作象限2:
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=0;  //电表工作象限3：
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=0;  //电表工作象限4：
  
  if(Judge_I_Start())  //电流都大于启动电流
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
    
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit4=Read_Event_Status(ID_EVENT_A_NEG_CURR);    //A相电流反极性：0--正常；1----反;
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit5=Read_Event_Status(ID_EVENT_B_NEG_CURR);    //B相电流反极性：0--正常；1----反；
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit6=Read_Event_Status(ID_EVENT_C_NEG_CURR);    //C相电流反极性：0--正常；1----反；
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit7=0;                                          //保留：0
  
  //程键打开/跳线短接/需量复位/电表上锁
  Meter_Run_Status.Key_Event.Bit.Bit0=0;                                       //保留：0
  Meter_Run_Status.Key_Event.Bit.Bit1=(B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS);      //工厂模式
  Meter_Run_Status.Key_Event.Bit.Bit2=Read_Event_Status(ID_EVENT_CLR_DEMAND_MAN)|Read_Event_Status(ID_EVENT_CLR_DEMAND_COM) |Read_Event_Status(ID_EVENT_CLR_ALL_DATA); //需量复位
  Meter_Run_Status.Key_Event.Bit.Bit3=Read_Event_Status(ID_EVENT_METER_LOCK);   //电表上锁
  Meter_Run_Status.Key_Event.Bit.Bit4=Read_Event_Status(ID_ALARM_OUT);            //表是否存在报警指示
  Meter_Run_Status.Key_Event.Bit.Bit5=(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS EQ 0);  //调试模式
  Meter_Run_Status.Key_Event.Bit.Bit6=Get_Cal_Exsit();          //校表状态或者系统参数未设置
  Meter_Run_Status.Key_Event.Bit.Bit7=0;                                       //保留：0
  
  //通信状态字
  Meter_Run_Status.Comm_Status.Bit.Bit0=GET_BIT(Module_Comm_Status.Var,5);    //在线，??????????
  Meter_Run_Status.Comm_Status.Bit.Bit1=GET_BIT(Module_Comm_Status.Var,0);        //场强0，??????????
  Meter_Run_Status.Comm_Status.Bit.Bit2=GET_BIT(Module_Comm_Status.Var,1);         //场强1，??????????
  Meter_Run_Status.Comm_Status.Bit.Bit3=GET_BIT(Module_Comm_Status.Var,2);        //场强2，??????????
  Meter_Run_Status.Comm_Status.Bit.Bit4=0;                                       //保留：0
  Meter_Run_Status.Comm_Status.Bit.Bit5=0;                                       //保留：0
  Meter_Run_Status.Comm_Status.Bit.Bit6=0;                                       //保留：0
  Meter_Run_Status.Comm_Status.Bit.Bit7=0;                                       //保留：0 
  
      
  //过载
  if(Meter_Run_Status.Meter_Stat4.Bit.Bit5 ||Meter_Run_Status.Meter_Stat5.Bit.Bit5 ||Meter_Run_Status.Meter_Stat6.Bit.Bit5)
    ReNew_Err_Code(DIS_POWER_EXCEED_ERR);  
  else
    Clr_Err_Code(DIS_POWER_EXCEED_ERR);  
  
  //电流严重不平衡
  if(Meter_Run_Status.Meter_Stat7.Bit.Bit8 )
    ReNew_Err_Code(DIS_CUR_VERY_NOEVEN_ERR); 
  else
    Clr_Err_Code(DIS_CUR_VERY_NOEVEN_ERR);  
  
  //过压 
  if(Meter_Run_Status.Meter_Stat4.Bit.Bit2 ||Meter_Run_Status.Meter_Stat5.Bit.Bit2 ||Meter_Run_Status.Meter_Stat6.Bit.Bit2)
    ReNew_Err_Code(DIS_VOLT_EXCEED_ERR);  
  else
    Clr_Err_Code(DIS_VOLT_EXCEED_ERR); 
  
  
  //功率因数超限
   if(Meter_Run_Status.Meter_Stat7.Bit.Bit7 )
    ReNew_Err_Code(DIS_PF_EXCEED_ERR); 
   else
    Clr_Err_Code(DIS_PF_EXCEED_ERR); 
  
   //超有功需量报警事件
   if(Meter_Run_Status.Meter_Stat7.Bit.Bit6)
    ReNew_Err_Code(DIS_DEMAND_EXCEED_ERR); 
   else
    Clr_Err_Code(DIS_DEMAND_EXCEED_ERR); 
   
   
   //内部电池欠压
   if(Meter_Run_Status.Meter_Stat1.Bit.Bit2)
    ReNew_Err_Code(DIS_RTCBAT_LOW); 
   else
    Clr_Err_Code(DIS_RTCBAT_LOW); 
   
   
     
  SET_STRUCT_SUM(Meter_Run_Status);
}
/********************************************************************************
函数原型：void Check_Prog_Status(void)
函数功能：检查是否处于编程状态
入口： 
出口：0---------不是编程状态；1---------是编程状态；
*********************************************************************************/
INT8U Check_Prog_Status(void)
{
  return (Read_Event_Status(ID_EVENT_PRGKEY_ON));  
  
}
/********************************************************************************
函数原型：void Check_MeterAddr_Status(void)
函数功能：检查设置表地址按钮是否开启
入口： 
出口：0---------表地址按钮没有按下；1---------表地址按钮按下了；
*********************************************************************************/
INT8U Check_MeterAddr_Status(void)
{
  return (Read_Event_Status(ID_METER_ADDR_EN));  
  
}

/********************************************************************************
函数原型：INT8U Check_Man_ClrDemd_En(void)
函数功能：检查设置清需量按钮是否开启
入口： 
出口：0---------不允许手动清需量；1---------允许手动清需量
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
函数原型：void Check_AB_Switch(void)
函数功能：
入口： 
出口：0---------不是AB显示模式切换状态；1---------是AB显示模式切换状态；
*********************************************************************************/
#ifdef ID_EVENT_AB_FUNC_KEY
INT8U Check_AB_Switch(void)
{
  static INT8U KeyStatus=0;
  
  if(Get_Sys_Status()==SYS_NORMAL)
    return (Read_Event_Status_Perone(PUCK,ID_EVENT_AB_FUNC_KEY)); 
  if(Get_Sys_Status()==SYS_RESUME)  //10ms查询一次
  {
    if((Inter_Up_Key_STATUS==1)&&(Inter_Down_Key_STATUS==1))  //没有按钮按下
      KeyStatus=0;
    else    //有一个按钮按下了
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
函数原型：void Check_Event_StruCS(void)
函数功能：检查与事件相关的所有结构体的校验和
入口： 
出口：
*********************************************************************************/
void Check_Event_StruCS(void)
{
  INT8U i,Flag;
  ASSERT(1);  //留下该函数的轨迹
    
  for(i=0;i<MAX_EVENT_NUM;i++)
  {
    Flag=CHECK_STRUCT_SUM(EventProcStatusVar[i]);
    if(!Flag)
      ASSERT_FAILED();  
  }
  
  Flag=CHECK_STRUCT_SUM(Meter_Instant_Status);
  if(Flag==0)  //Sram错误，清除事件瞬态字
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
  if(Flag==0)  //Sram错误，清除事件瞬态字
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
函数原型：void Test_Interr_IO_Status(void)
函数功能：查询中断引脚的IO口状态
入口： 
出口：
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
函数原型：void ReNew_PwrOff_Status(void)
函数功能：设置掉电后的相关瞬时状态字
*********************************************************************************/
void ReNew_PwrOff_Status(void)
{   
  INT8U i;
  if(CHECK_STRUCT_SUM(Meter_Instant_Status)==0)  //掉电前事件的状态，校验和错，不允许存数
  {
    ASSERT_FAILED();
     mem_set((void *)(&Meter_Instant_Status),0,sizeof(Meter_Instant_Status),\
                   (void *)(&Meter_Instant_Status),sizeof(Meter_Instant_Status));
    SET_STRUCT_SUM(Meter_Instant_Status); 
    return ;
  }
  else
  {
    for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)   //根据掉电时，事件发生的真实状态，来初始化瞬态字，供掉电存储
    {
      if(Read_Event_Status(i))
        Set_Event_Instant(i);
      else
        Clr_Event_Instant(i);
    }    
  }
}
/********************************************************************************
函数原型：void Set_Power_Or_Reset_Ststus(void)
函数功能：复位前，设置正常复位标志
*********************************************************************************/
void Set_PwrOrRst_Status(void)
{
  Set_Event_Instant(ID_EVENT_POWER_OFF);  //掉电事件发生
  Power_Status.Power=POWER_OFF;          //掉电事件标志
  SET_STRUCT_SUM(Power_Status);
  
  if((Key_Value_Pub.Key.Bit.PrgKey EQ 0)&&(Prg_Key_Status.PrgKeyTime))  //不是编程状态
  {
    Prg_Key_Status.PrgKeyTime=0;  //清楚掉电前编程状态
    SET_STRUCT_SUM(Prg_Key_Status);
  }
}
/********************************************************************************
函数原型：void Save_Event_Data(void)
函数功能：上电后，对掉电的事件数据存储
*********************************************************************************/
void Save_Event_Data(void)
{
  INT8U Flag,i;
  
  Flag=CHECK_STRUCT_SUM(Power_Status);  
  if(Flag)    //上次复位前的状态,sram状态正确
  {
    if(Get_Sys_Status()==SYS_NORMAL)
    {
      if(POWER_OFF!=Power_Status.Power)     //前次没有捕获掉电信息
      {
        Power_Status.Power=ABNORMAL_RESET;      //置为复位状态，为上电事件判定做准备，避免作为上电事件而存储
      }
    } 
  }
  else
    Power_Status.Power=POWER_ON;       //上电事件置位，为判定做准备      
  
  if(ABNORMAL_RESET EQ Power_Status.Power)     //复位事件
    Set_Event_Instant(ID_EVENT_RESET); 
  
    
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)  //根据上次掉电的瞬态字，强行设置事件的发生
  {
    if(Get_Event_Instant(i))   //此状态实际是从 内卡 取出的状态，不是 sram状态
    {
      if(ID_EVENT_POWER_OFF EQ i || ID_EVENT_RESET EQ i)        //掉电或复位
        Force_Event_Occur_Status(i);     //掉电发生事件
      else
        Set_Event_Occur_Status(i);     //事件发生了，等待结束！
    }
    else
        Clr_Event_Real_Status(i);
  }
  
  Power_Status.Power=POWER_ON;     //置上电状态     
  SET_STRUCT_SUM(Power_Status);    
  Event_Judge_Save_Alarm(0,1);    //根据强行设置的瞬态字，模拟一次结束    
  Clr_All_Event_Sram();     //清除报警相关字
  
}
/********************************************************************************
函数原型：void Afer_PwrOff_Proc(void)
函数功能：掉电存事件数据
*********************************************************************************/
void PwrOff_Proc_PUCK(void)
{ 
  Clr_All_Loss_Data();         //清零全失压Sram数据
  Set_Soft_RTC_PUCK(ID_CPU_RTC);        //初始化软时钟
  ReNew_PwrOff_Status();       //掉电存瞬时状态字
  Set_PwrOrRst_Status();
}
/********************************************************************************
函数原型：void Event_Proc_Sec(void)
函数功能：每秒对事件的处理及其判定机制
*********************************************************************************/
void Event_Proc_Sec(void)
{
  static volatile S_Int32U Sec_Timer_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
    
  if(Sec_Timer_Bak.Var!=Sec_Timer_Pub)
  {
    //Event_Para_Modi();    事件与计量同一任务
    Check_Event_StruCS();  
    Get_Meter_Instant_Status();  //获取表计瞬态字
    Event_Judge_Save_Alarm(1,1);    //通过瞬态字，获取表计所有事件真实状态,存储事件信息,同时对外报警
   //Test_Interr_IO_Status();
  
    Get_Meter_Run_Status(); 
    Check_RelayOn_Key();   //每秒判定继电器按钮合闸允许按钮状态
    Sec_Timer_Bak.Var=Sec_Timer_Pub;
  }
}
/********************************************************************************
函数原型：void Emerg_Event_Proc(void)
函数功能：对突发事件的份额处理
出口：0---------无此事件产生；1---------此事件发生；
*********************************************************************************/
void Emerg_Event_Proc(void)
{
  INT8U i;
  for(i=MIN_ID_EVENT;i<=MAX_ID_EVENT;i++)
  {
    if((EventPropertyVar[i].DoubleFlag==0)&&(Get_Event_Instant(i)))  //不成对事件发生了瞬态字设置
    {
      if(REC_FRAME_CONDITION)
      {
        OS_TimeDly_Ms(10);  
      }
      
      Event_Judge_StartAndEnd(i,1,1);
      
      /*
      Get_Meter_Instant_Status();     
      Event_Judge_Save_Alarm(1,1);    //通过瞬态字，获取表计所有事件真实状态,存储事件信息,同时对外报警
      */
      return ;
    }    
  }
}
/***********************************************************************
函数功能：判断继电器合闸允许状态
入口：无
出口：无
事件发生判据：
***********************************************************************/
#define RELAY_ON_KEY_SEC 3
void Check_RelayOn_Key(void)
{
 
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Relay_On_Key_Countr=0;
    return ;
  }
  
  if(Inter_Up_Key_STATUS EQ Inter_Down_Key_STATUS)  //同时按下或者同时没按下
  {
    Relay_On_Key_Countr=0;
    return ;
  }
  
  Relay_On_Key_Countr++;
  if(Relay_On_Key_Countr>=0xff)   //防止翻转
    Relay_On_Key_Countr=RELAY_ON_KEY_SEC;
}
/***********************************************************************
函数功能：判断继电器合闸允许状态
入口：无
出口：1-------------------合闸按钮
事件发生判据：
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
  if(Get_Sys_Status()!=SYS_NORMAL)  //只有在主电源供电情况下，此任务才执行
  {
    while(1)
     Task_Sleep();    
  }
  
  if(Get_Sys_Status()!=SYS_NORMAL) //只有在正常模式下，才有事件的处理
    return ;
  
  if(Flag)
  { 
    Init_All_Event_Sram();
    Save_All_Loss_Data();
    Accmu_RTC_BatTime_PerMin();   //初始化电池工作时间变量：没有进入掉电流程，调用此函数
    //Init_Toggle_Status();
    OS_TimeDly_Sec(1);
    return ;
  }
  //以下每秒调用一次
  //Emerg_Event_Proc();     //对突发事件的每10ms处理，必须与Channel_Data_Proc_PUCKStatus）同步
  Event_Proc_Sec();       //对所有事件的每秒处理
 }  