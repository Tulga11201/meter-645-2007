#define    AllLossMeasu_C
#include "Pub_PUCK.h"

extern const INT32U I_RATE_CONST[];

/***********************************************************************
函数功能：将全失压数据清零，调用条件：fx1晶振，在掉电存数中调用，为开始计全失压做准备
入口：无
出口：无
***********************************************************************/
void Clr_All_Loss_Data(void)
{
  INT8U i;
  mem_set((void *)(&All_Loss_Var),0,sizeof(All_Loss_Var),\
                   (void *)(&All_Loss_Var),sizeof(All_Loss_Var));
  All_Loss_Var.Status.First=1;
  SET_VAR_CS_PUCK(All_Loss_Var.Status); 
  for(i=0;i<ALL_LOSS_NUM;i++)
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[i]);
}

/***********************************************************************
函数功能：根据CS成立条件，清零全失压sram，调用条件：fx1晶振，程序复位后
入口：无
出口：无
***********************************************************************/
void Init_All_Loss_Sram(void)
{
  INT8U Flag,i;
  
  Flag=CHK_VAR_CS_PUCK(All_Loss_Var.Status);
  for(i=0;i<ALL_LOSS_NUM;i++)
    Flag&=CHK_VAR_CS_PUCK(All_Loss_Var.RecordTime[i]);
  
  if(!Flag)
  {
    ASSERT_FAILED();  
    mem_set((void *)(&All_Loss_Var),0,sizeof(All_Loss_Var),(void *)(&All_Loss_Var),sizeof(All_Loss_Var));
    All_Loss_Var.Status.First=1;
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    for(i=0;i<ALL_LOSS_NUM;i++)
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[i]); 
  }
}

/***********************************************************************
函数功能：存储全失压数据，调用条件：fx1晶振，事件任务已经开启，并且是主电源来电
入口：无
出口：无
***********************************************************************/
void Save_All_Loss_Data(void)
{
  INT8U i,temp,num;
  
  temp=CHK_VAR_CS_PUCK(All_Loss_Var.Status);
  if(0==temp)
    ASSERT_FAILED();  
  
  if((All_Loss_Var.Status.Nums==0)||(All_Loss_Var.Status.Mins==0))   //没有事件发生
  {
    Clr_All_Loss_Data();   //存完后清0
    return ;
  }
   
  if(All_Loss_Var.Status.start && All_Loss_Var.Status.Index<ALL_LOSS_NUM)  //有发生没有结束,且不越界
  {
    if((CHeck_Same_Byte((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime))))
    {
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[0]=Cur_Time1.Min;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[1]=Cur_Time1.Hour;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[2]=Cur_Time1.Date;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[3]=Cur_Time1.Month;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[4]=Cur_Time1.Year;  //取系统时钟
      SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);
    }
  }
  num=(All_Loss_Var.Status.Nums<=ALL_LOSS_NUM)?All_Loss_Var.Status.Nums:ALL_LOSS_NUM;
  if(All_Loss_Var.Status.Index<ALL_LOSS_NUM)   //index保证不越界
  {
     for(i=0;i<num;i++)  
     {
       if(num<=ALL_LOSS_NUM)  //没有翻转：按顺序依次写
         temp=i;   
       else                   //翻转：按老-->新依次写  
        temp=((All_Loss_Var.Status.Index+1)%ALL_LOSS_NUM+i)%ALL_LOSS_NUM;       
      All_Loss_Vol_Data_Proc((INT8U *)All_Loss_Var.RecordTime[temp].StartTime,(INT8U *)All_Loss_Var.RecordTime[temp].EndTime,All_Loss_Var.Curr[temp]);
     }
  }
  
  All_Loss_Vol_Counts_Time_Proc(All_Loss_Var.Status.Nums,All_Loss_Var.Status.Mins); 
  Clr_All_Loss_Data();   //存完后清0  
}
/***********************************************************************
函数功能：计算全失压数据，调用条件：fxt晶振，RTC闹铃。在RTC中断中调用！
入口：无
出口：无
***********************************************************************/
#ifdef ALL_LOSS_HARD_EN
void Count_All_Loss_Proc(void)
{ 
  if(All_Loss_Var.Status.Occur)
  {
    All_Loss_Var.Status.Occur=0;
    All_Loss_Var.Status.Exist=1;
  }
  else
    All_Loss_Var.Status.Exist=0;
  
  if(All_Loss_Var.Status.Exist==0 && All_Loss_Var.Status.start==0) //无失压发生，以最快的速度退出
  {
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    return  ;
  }
  
  if(All_Loss_Var.Status.Exist && All_Loss_Var.Status.start==0)  //全失压发生
  {

    //醒来了，根据唤醒源马上切换高速晶振-----------PUCK
   Switch_Main_Osc(RUN_MODE);
   Clear_CPU_Dog();

   
    All_Loss_Var.Status.start=1;
    if(All_Loss_Var.Status.First)
    {
      All_Loss_Var.Status.First=0;
      All_Loss_Var.Status.Index=0;
    }
    else
      All_Loss_Var.Status.Index=(All_Loss_Var.Status.Index+1)%ALL_LOSS_NUM;
    
    /*
    if(All_Loss_Var.Status.Index>ALL_LOSS_NUM)  //防止越界
      All_Loss_Var.Status.Index=0;
    */
    All_Loss_Var.Status.Nums++;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[0]=MIN;      //CPU_RTC_Time.RTC.Min;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[1]=HOUR;      //CPU_RTC_Time.RTC.Hour;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[2]=DAY;      //CPU_RTC_Time.RTC.Date;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[3]=MONTH;      //CPU_RTC_Time.RTC.Month;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[4]=YEAR;      //CPU_RTC_Time.RTC.Year;
    
    Get_AllLoss_Curr();
    
    memset((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,\
          sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime));     //死写，不用mem_set
    
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]); 
    return ;
  }
  
  if(All_Loss_Var.Status.Exist && All_Loss_Var.Status.start)    //全失压延续
  {
    All_Loss_Var.Status.Mins++;
    SET_VAR_CS_PUCK(All_Loss_Var.Status);
    return ;
  }
  
  if(All_Loss_Var.Status.Exist==0 && All_Loss_Var.Status.start) //全失压结束
  {
    All_Loss_Var.Status.Mins++;
    All_Loss_Var.Status.start=0;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[0]=MIN;      //CPU_RTC_Time.RTC.Min;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[1]=HOUR;     // CPU_RTC_Time.RTC.Hour;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[2]=DAY;      //CPU_RTC_Time.RTC.Date;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[3]=MONTH;    //  CPU_RTC_Time.RTC.Month;
    All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[4]=YEAR;     // CPU_RTC_Time.RTC.Year;
    
    Measu_Sign_InstantData_PUCK.Curr.A=0;
    Measu_Sign_InstantData_PUCK.Curr.B=0;
    Measu_Sign_InstantData_PUCK.Curr.C=0;
    
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]); 
    return ;    
  }
  
  SET_VAR_CS_PUCK(All_Loss_Var.Status); 
  SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);
}
#endif 

/***********************************************************************
函数功能：计算全失压数据，调用条件：fxt晶振，RTC闹铃。在RTC中断中调用！
入口：无
出口：无
***********************************************************************/
#ifndef ALL_LOSS_HARD_EN
void Count_All_Loss_Proc(void)
{

  INT8U i,Flag,Loss_Volt_Flag=0;
  INT32U RdData;
  FP32S  ResultData,Temp;    

   
   ResultData=0;
   for(i=0;i<3;i++)
   {
      Flag=Measu_RdAndCompData(REG_R_A_I+i,(INT8U *)(&RdData));      
      if(!Flag || RdData>=0x00800000)
      {
        break ;
      }
      Temp=((FP32S)RdData*(FP32S)UNIT_A/8192)/(FP32S)I_RATE_CONST[Get_SysCurr_Mode()];
      ResultData+=Temp;
      if(Temp/UNIT_A>=Get_In())
      {
        *(&(Measu_Sign_InstantData_PUCK.Curr.A)+i)=(INT32S)Temp;  //更新公有电流数据，用于显示
        Loss_Volt_Flag=1;
      }
   }
   if(i>=3)
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/3);   
   else       
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/(i+1));
   
   //全失压发生
   if(Loss_Volt_Flag)
   {         
      All_Loss_Var.Status.Index=0;
      All_Loss_Var.Status.start=1;   //有发生没有结束
      All_Loss_Var.Status.Nums=1;
      All_Loss_Var.Status.Mins=1;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[0]=MIN;      //CPU_RTC_Time.RTC.Min;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[1]=HOUR;      //CPU_RTC_Time.RTC.Hour;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[2]=DAY;      //CPU_RTC_Time.RTC.Date;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[3]=MONTH;      //CPU_RTC_Time.RTC.Month;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[4]=YEAR;      //CPU_RTC_Time.RTC.Year;    
      
      memset((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,\
            sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime));     //死写，不用mem_set    
      SET_VAR_CS_PUCK(All_Loss_Var.Status); 
      SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);  
   }
   
   
   P13_bit.no0=0;   //7022_CS
   P2_bit.no0=0;    //计量RST---------7022_RST   
   P2_bit.no2=0;    //计量SDO---------7022_SDO     
   P2_bit.no4=0;    //计量SCK---------7022_SCK
   
   PM2_bit.no1=0;    //计量SIG---------7022_SIG   
   PM2_bit.no3=0;    //计量SDI ---------7022_SDI
   P2_bit.no1=0;    //计量SIG---------7022_SIG   
   P2_bit.no3=0;    //计量SDI ---------7022_SDI   
   
   BAT_OFF_7022;   //关闭后备电池
}
#endif
/***********************************************************************
函数功能：获取电流增益参数
入口：无
出口：无
***********************************************************************/
void Get_Curr_Rate(void)
{
#ifdef  ALL_LOSS_HARD_EN
  INT8U i,Rdflag,temp[3];
  
  for(i=0;i<3;i++)
  {
    INIT_STRUCT_VAR(Curr_Rate);
    Rdflag=Read_Storage_Data_PUCK(DI_I_GAIN_A+i,temp,3);
    if(Rdflag)
    {
      Curr_Rate.Rate[i]=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);      
    }    
  }  
#endif
}
/***********************************************************************
函数功能：计算全失压下的电流值
入口：无
出口：无
***********************************************************************/
#ifdef  ALL_LOSS_HARD_EN
void Get_AllLoss_Curr(void)
{

  INT8U i,Flag;
  INT32U RdData;
  FP32S  ResultData,Temp;
  
   BAT_ON_7022;     //打开后备电池
   
   PM13_bit.no0=0;   //7022_CS
   PM2_bit.no0=0;    //计量RST---------7022_RST   
   PM2_bit.no2=0;    //计量SDO---------7022_SDO     
   PM2_bit.no4=0;    //计量SCK---------7022_SCK
   
   PM2_bit.no1=1;    //计量SIG---------7022_SIG   
   PM2_bit.no3=3;    //计量SDI ---------7022_SDI  

   Clear_CPU_Dog();   
   
   
  WAITFOR_DRV_MS_TIMEOUT(10)
  MEASU_RST_0;
  WAITFOR_DRV_MS_TIMEOUT(10)
  MEASU_RST_1;
  
     //延时300ms
   for(i=0;i<30;i++)
      WAITFOR_DRV_MS_TIMEOUT(10)
   Clear_CPU_Dog();
   

   EnMeasuCal();  
   //初始化的时候，就需要获取电流规格，电流增益参数
   for(i=0;i<3;i++)
   {
      Flag=Measu_WrAndCompData(REG_W_IGAIN_A+i,Curr_Rate.Rate[i]);
      if(!Flag)
        Clear_CPU_Dog();
   }   
   DisMeasuCal();
    //延时500ms
   for(i=0;i<50;i++)
      WAITFOR_DRV_MS_TIMEOUT(10)
   Clear_CPU_Dog();
   
   ResultData=0;
   for(i=0;i<3;i++)
   {
      Flag=Measu_RdAndCompData(REG_R_A_I+i,(INT8U *)(&RdData));      
      if(!Flag || RdData>=0x00800000)
      {
        break ;
      }
      Temp=((FP32S)RdData*(FP32S)UNIT_A/8192)/(FP32S)I_RATE_CONST[Get_SysCurr_Mode()];
      ResultData+=Temp;
      *(&(Measu_Sign_InstantData_PUCK.Curr.A)+i)=(INT32S)Temp;  //更新公有电流数据，用于显示
      //ResultData+=((FP32S)RdData*(FP32S)UNIT_A/pow(2,13))/(FP32S)I_RATE_CONST[Get_SysCurr_Mode()];
   }
   if(i>=3)
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/3);   
   else       
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/(i+1));
   
   P13_bit.no0=0;   //7022_CS
   P2_bit.no0=0;    //计量RST---------7022_RST   
   P2_bit.no2=0;    //计量SDO---------7022_SDO     
   P2_bit.no4=0;    //计量SCK---------7022_SCK
   
   PM2_bit.no1=0;    //计量SIG---------7022_SIG   
   PM2_bit.no3=0;    //计量SDI ---------7022_SDI
   P2_bit.no1=0;    //计量SIG---------7022_SIG   
   P2_bit.no3=0;    //计量SDI ---------7022_SDI   
   
   BAT_OFF_7022;   //关闭后备电池
}
#endif

