#define    AllLossMeasu_C
#include "Pub_PUCK.h"

extern const INT32U I_RATE_CONST[];

/***********************************************************************
�������ܣ���ȫʧѹ�������㣬����������fx1�����ڵ�������е��ã�Ϊ��ʼ��ȫʧѹ��׼��
��ڣ���
���ڣ���
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
�������ܣ�����CS��������������ȫʧѹsram������������fx1���񣬳���λ��
��ڣ���
���ڣ���
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
�������ܣ��洢ȫʧѹ���ݣ�����������fx1�����¼������Ѿ�����������������Դ����
��ڣ���
���ڣ���
***********************************************************************/
void Save_All_Loss_Data(void)
{
  INT8U i,temp,num;
  
  temp=CHK_VAR_CS_PUCK(All_Loss_Var.Status);
  if(0==temp)
    ASSERT_FAILED();  
  
  if((All_Loss_Var.Status.Nums==0)||(All_Loss_Var.Status.Mins==0))   //û���¼�����
  {
    Clr_All_Loss_Data();   //�������0
    return ;
  }
   
  if(All_Loss_Var.Status.start && All_Loss_Var.Status.Index<ALL_LOSS_NUM)  //�з���û�н���,�Ҳ�Խ��
  {
    if((CHeck_Same_Byte((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime))))
    {
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[0]=Cur_Time1.Min;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[1]=Cur_Time1.Hour;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[2]=Cur_Time1.Date;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[3]=Cur_Time1.Month;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime[4]=Cur_Time1.Year;  //ȡϵͳʱ��
      SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);
    }
  }
  num=(All_Loss_Var.Status.Nums<=ALL_LOSS_NUM)?All_Loss_Var.Status.Nums:ALL_LOSS_NUM;
  if(All_Loss_Var.Status.Index<ALL_LOSS_NUM)   //index��֤��Խ��
  {
     for(i=0;i<num;i++)  
     {
       if(num<=ALL_LOSS_NUM)  //û�з�ת����˳������д
         temp=i;   
       else                   //��ת������-->������д  
        temp=((All_Loss_Var.Status.Index+1)%ALL_LOSS_NUM+i)%ALL_LOSS_NUM;       
      All_Loss_Vol_Data_Proc((INT8U *)All_Loss_Var.RecordTime[temp].StartTime,(INT8U *)All_Loss_Var.RecordTime[temp].EndTime,All_Loss_Var.Curr[temp]);
     }
  }
  
  All_Loss_Vol_Counts_Time_Proc(All_Loss_Var.Status.Nums,All_Loss_Var.Status.Mins); 
  Clr_All_Loss_Data();   //�������0  
}
/***********************************************************************
�������ܣ�����ȫʧѹ���ݣ�����������fxt����RTC���塣��RTC�ж��е��ã�
��ڣ���
���ڣ���
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
  
  if(All_Loss_Var.Status.Exist==0 && All_Loss_Var.Status.start==0) //��ʧѹ�������������ٶ��˳�
  {
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    return  ;
  }
  
  if(All_Loss_Var.Status.Exist && All_Loss_Var.Status.start==0)  //ȫʧѹ����
  {

    //�����ˣ����ݻ���Դ�����л����پ���-----------PUCK
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
    if(All_Loss_Var.Status.Index>ALL_LOSS_NUM)  //��ֹԽ��
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
          sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime));     //��д������mem_set
    
    SET_VAR_CS_PUCK(All_Loss_Var.Status); 
    SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]); 
    return ;
  }
  
  if(All_Loss_Var.Status.Exist && All_Loss_Var.Status.start)    //ȫʧѹ����
  {
    All_Loss_Var.Status.Mins++;
    SET_VAR_CS_PUCK(All_Loss_Var.Status);
    return ;
  }
  
  if(All_Loss_Var.Status.Exist==0 && All_Loss_Var.Status.start) //ȫʧѹ����
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
�������ܣ�����ȫʧѹ���ݣ�����������fxt����RTC���塣��RTC�ж��е��ã�
��ڣ���
���ڣ���
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
        *(&(Measu_Sign_InstantData_PUCK.Curr.A)+i)=(INT32S)Temp;  //���¹��е������ݣ�������ʾ
        Loss_Volt_Flag=1;
      }
   }
   if(i>=3)
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/3);   
   else       
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/(i+1));
   
   //ȫʧѹ����
   if(Loss_Volt_Flag)
   {         
      All_Loss_Var.Status.Index=0;
      All_Loss_Var.Status.start=1;   //�з���û�н���
      All_Loss_Var.Status.Nums=1;
      All_Loss_Var.Status.Mins=1;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[0]=MIN;      //CPU_RTC_Time.RTC.Min;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[1]=HOUR;      //CPU_RTC_Time.RTC.Hour;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[2]=DAY;      //CPU_RTC_Time.RTC.Date;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[3]=MONTH;      //CPU_RTC_Time.RTC.Month;
      All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].StartTime[4]=YEAR;      //CPU_RTC_Time.RTC.Year;    
      
      memset((INT8U*)All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime,0x00,\
            sizeof(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index].EndTime));     //��д������mem_set    
      SET_VAR_CS_PUCK(All_Loss_Var.Status); 
      SET_VAR_CS_PUCK(All_Loss_Var.RecordTime[All_Loss_Var.Status.Index]);  
   }
   
   
   P13_bit.no0=0;   //7022_CS
   P2_bit.no0=0;    //����RST---------7022_RST   
   P2_bit.no2=0;    //����SDO---------7022_SDO     
   P2_bit.no4=0;    //����SCK---------7022_SCK
   
   PM2_bit.no1=0;    //����SIG---------7022_SIG   
   PM2_bit.no3=0;    //����SDI ---------7022_SDI
   P2_bit.no1=0;    //����SIG---------7022_SIG   
   P2_bit.no3=0;    //����SDI ---------7022_SDI   
   
   BAT_OFF_7022;   //�رպ󱸵��
}
#endif
/***********************************************************************
�������ܣ���ȡ�����������
��ڣ���
���ڣ���
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
�������ܣ�����ȫʧѹ�µĵ���ֵ
��ڣ���
���ڣ���
***********************************************************************/
#ifdef  ALL_LOSS_HARD_EN
void Get_AllLoss_Curr(void)
{

  INT8U i,Flag;
  INT32U RdData;
  FP32S  ResultData,Temp;
  
   BAT_ON_7022;     //�򿪺󱸵��
   
   PM13_bit.no0=0;   //7022_CS
   PM2_bit.no0=0;    //����RST---------7022_RST   
   PM2_bit.no2=0;    //����SDO---------7022_SDO     
   PM2_bit.no4=0;    //����SCK---------7022_SCK
   
   PM2_bit.no1=1;    //����SIG---------7022_SIG   
   PM2_bit.no3=3;    //����SDI ---------7022_SDI  

   Clear_CPU_Dog();   
   
   
  WAITFOR_DRV_MS_TIMEOUT(10)
  MEASU_RST_0;
  WAITFOR_DRV_MS_TIMEOUT(10)
  MEASU_RST_1;
  
     //��ʱ300ms
   for(i=0;i<30;i++)
      WAITFOR_DRV_MS_TIMEOUT(10)
   Clear_CPU_Dog();
   

   EnMeasuCal();  
   //��ʼ����ʱ�򣬾���Ҫ��ȡ������񣬵����������
   for(i=0;i<3;i++)
   {
      Flag=Measu_WrAndCompData(REG_W_IGAIN_A+i,Curr_Rate.Rate[i]);
      if(!Flag)
        Clear_CPU_Dog();
   }   
   DisMeasuCal();
    //��ʱ500ms
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
      *(&(Measu_Sign_InstantData_PUCK.Curr.A)+i)=(INT32S)Temp;  //���¹��е������ݣ�������ʾ
      //ResultData+=((FP32S)RdData*(FP32S)UNIT_A/pow(2,13))/(FP32S)I_RATE_CONST[Get_SysCurr_Mode()];
   }
   if(i>=3)
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/3);   
   else       
      All_Loss_Var.Curr[All_Loss_Var.Status.Index]=(INT32U)(ResultData/(i+1));
   
   P13_bit.no0=0;   //7022_CS
   P2_bit.no0=0;    //����RST---------7022_RST   
   P2_bit.no2=0;    //����SDO---------7022_SDO     
   P2_bit.no4=0;    //����SCK---------7022_SCK
   
   PM2_bit.no1=0;    //����SIG---------7022_SIG   
   PM2_bit.no3=0;    //����SDI ---------7022_SDI
   P2_bit.no1=0;    //����SIG---------7022_SIG   
   P2_bit.no3=0;    //����SDI ---------7022_SDI   
   
   BAT_OFF_7022;   //�رպ󱸵��
}
#endif

