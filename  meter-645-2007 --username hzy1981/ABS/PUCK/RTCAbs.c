#define RTC_ABS_PUCK
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P5"
#endif
/**********************************************************************************
�������ܣ���ʼ���ⲿ������
��ڣ�
      Flag----0��ʾ�ر��ⲿ�����壻1��ʾʹ���ⲿ������
���ڣ�
**********************************************************************************/
void Init_ExtRTC_Pulse(INT8U Flag)
{
  Init_RTC_Pulse(Flag);   
  
#if SEC_OUT_POWER_ON>0   //�ϵ����������壬�����ǲ��Ǹ��϶���
  if(Flag)
     Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
  
  Multi_Port_Mode.Mode=0;  //����һ���״̬:0-�����壻1-ʱ���л���2-�������ڡ�

#else 
  #if SEC_MULTI_PORT>0  //�������Ǹ��϶��� 
    if(Flag && Get_Sec_Out_En())  //���϶����£����������
      Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
  #else   
    if(Flag)            //���Ǹ��϶���
       Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
  #endif 
#endif    
}
/**********************************************************************************
�������ܣ����ⲿʵʱʱ��
��ڣ�
Dst---------------Ŀ�껺����,BCD��,˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
DstLen-------------Ŀ�껺��������
���ڣ�1---------��ȡ�ɹ���0--------��ȡʧ��
ע��:
1: ���������ݲ����BCD��ĺϷ���;
2: ���������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Read_ExtRTC_PUCK(INT8U *Dst,INT8U DstLen)
{
 INT8U Flag;
 
#if   EXT_RTC_TYPE==DRV_SIMU_RV3029C2
  INT8U temp;
#endif 
  
 if(DstLen!=7)
 {   
   Debug_Print("Ext_RTC Error----->Dst_Buf Length is Error!");
   return 0;
 }
 
 if(Check_ExtRTC_Busy()!=EXT_RTC_OK)
   return 0;
 
 #if   EXT_RTC_TYPE==DRV_SIMU_RV3029C2
  Flag=Read_EXT_RTC_Buf(0x08,7,Dst);   //ʵ��˳�� �롢�֡�ʱ���ա����ڡ��¡���
  if(!Flag)
    return 0;
  temp=Dst[3];Dst[3]=Dst[4];Dst[4]=temp;
 #else                                 //ʵ��˳�� �롢�֡�ʱ�����ڡ��ա��¡���
  Flag=Read_EXT_RTC_Buf(0,7,Dst);
 #endif 
 return Flag;
}
/**********************************************************************************
�������ܣ�д�ⲿʵʱʱ��
��ڣ�
Src---------------˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
���ڣ�1---------дʱ�ӳɹ���0--------дʱ��ʧ��
ע��:
1: д������ݲ����BCD��ĺϷ���;
2: д������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Write_ExtRTC_PUCK(INT8U *Src)
{
#if   EXT_RTC_TYPE==DRV_SIMU_RV3029C2
  INT8U temp[7],temp1;
#endif 
  
  INT8U Flag;  
  if(Check_ExtRTC_Busy()!=EXT_RTC_OK)
   return 0;
  
#if   EXT_RTC_TYPE==DRV_SIMU_RV3029C2
  mem_cpy(temp,Src,7,Src,sizeof(temp));
  temp1=temp[3];temp[3]=temp[4];temp[4]=temp1;
  
  Flag=Write_EXT_RTC_Buf(0,7,temp);
#else
  Flag=Write_EXT_RTC_Buf(0,7,Src);
#endif  
  return Flag;
}


/**********************************************************************************
�������ܣ����ⲿʵʱʱ��
��ڣ�
Dst---------------Ŀ�껺����,BCD��,˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
DstLen-------------Ŀ�껺��������
���ڣ�1---------��ȡ�ɹ���0--------��ȡʧ��
ע��:
1: ���������ݲ����BCD��ĺϷ���;
2: ���������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Read_InterRTC_PUCK(INT8U *Dst,INT8U DstLen)
{
  struct RTCCounterValue temp;
  INT8U Flag;
  
  if(DstLen!=7)
  {   
    Debug_Print("Inter_RTC Error----->Dst_Buf Length is Error!");
    return 0;
  }
  Flag=RTC_CounterGet( &temp );
  
  if(Flag!=MD_OK)
  {
    Debug_Print("Inter_RTC Error----->Return Value Not Equal MD_OK!");
    return 0;
  }
  
  Dst[0]=temp.Sec;
  Dst[1]=temp.Min;
  Dst[2]=temp.Hour;
  Dst[4]=temp.Day;
  Dst[3]=temp.Week;
  Dst[5]=temp.Month;
  Dst[6]=temp.Year; 
  return 1;
}
/**********************************************************************************
�������ܣ�д�ⲿʵʱʱ��
��ڣ�
Src---------------˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
���ڣ�1---------дʱ�ӳɹ���0--------дʱ��ʧ��
ע��:
1: д������ݲ����BCD��ĺϷ���;
2: д������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Write_InterRTC_PUCK(INT8U *Src)
{
 struct RTCCounterValue CwriteVal;
  CwriteVal.Sec = Src[0];
  CwriteVal.Min = Src[1];
  CwriteVal.Hour = Src[2];
  CwriteVal.Day = Src[4];
  CwriteVal.Week= Src[3];
  CwriteVal.Month = Src[5];
  CwriteVal.Year = Src[6]; 
  RTC_CounterEnable( );
  RTC_CounterSet(CwriteVal );     
  RTC_CounterEnable( );
  return 1;
}

/**********************************************************************************
�������ܣ���sleepģʽ�ڣ����پ����£���RTC(3���ݴ�)
��ڣ� Time:  �֡�ʱ���ա��¡���
���ڣ�1----------------�ɹ���0----------------ʧ��
**********************************************************************************/ 
void Refresh_CPU_RTC(void)
{
    INT8U i,times;
    
   for(times=0;times<3;times++)
   {
      RWAIT = 1;
      for(i = 0; i<(RTC_WAITTIME/8);i++ ) 
      {
        if(RWST)
          break;
      }
      Clear_CPU_Dog();
      
      if(i==(RTC_WAITTIME/8-1))
        continue;  
      
      CPU_RTC_Time.RTC.Sec=SEC;
      CPU_RTC_Time.RTC.Min=MIN;
      CPU_RTC_Time.RTC.Hour=HOUR;
      CPU_RTC_Time.RTC.Week=WEEK;
      CPU_RTC_Time.RTC.Date=DAY;
      CPU_RTC_Time.RTC.Month=MONTH;
      CPU_RTC_Time.RTC.Year=YEAR;
      SET_VAR_CS_PUCK(CPU_RTC_Time.RTC);
      RWAIT=0;
      for ( i = 0; i < RTC_WAITTIME/8; i++) 
      {
        if(RWST==0)
          return ;
      }
      Clear_CPU_Dog();
      
      if(i==(RTC_WAITTIME/8-1)) 
        continue;
    }
}

/**********************************************************************************
�������ܣ���ȡCPU Sram ��RTC
��ڣ�
Dst---------------Ŀ�껺����,BCD��,˳��Ϊ�ӵ͵���:��/��/ʱ/����/��/��/��
DstLen-------------Ŀ�껺��������
���ڣ�1---------��ȡ�ɹ���0--------��ȡʧ��
ע��:
1: ���������ݲ����BCD��ĺϷ���;
2: ���������ݲ������/��/��/����/ʱ/��/��ĺϷ���;
**********************************************************************************/
INT8U Get_Soft_RTC_PUCK(INT8U *Dst,INT8U DstLen)
{
  if(DstLen!=7)
    return 0;
  
  if(CHECK_STRUCT_VAR(CPU_RTC_Time)==0)   //���ͷβ
  {
    ASSERT_FAILED();
    return 0;
  }
  
  if(CHK_VAR_CS_PUCK(CPU_RTC_Time.RTC)==0)          //���У���
  {
    ASSERT_FAILED();
    return 0;
  }
  if(Check_BCD_Data((void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1)==0)
    return 0;
  
  mem_cpy(Dst,(void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1,Dst,sizeof(CPU_RTC_Time.RTC)-1);
  return 1;
}

/***********************************************************************
�������ܣ�����sleep�µ���ʱ�ӣ�3������
��ڣ�Flag:ID_EXT_RTC�Ⱥ�
���ڣ���
***********************************************************************/
void Set_Soft_RTC_PUCK(INT8U Flag)
{   
 INT8U i;
 static INT8U Entry=0;
 
 if(0x51==Entry)
 {
  if(CHECK_STRUCT_VAR(CPU_RTC_Time)==0 || CHK_VAR_CS_PUCK(CPU_RTC_Time.RTC)==0)   //���ͷβ ,���У���
  {
    ASSERT_FAILED();
  }   
 }
 
 Entry=0x51;
 for(i=0;i<3;i++)
 {
     switch(Flag)
     {
       case ID_EXT_RTC:
         Read_ExtRTC_PUCK((INT8U *)(&CPU_RTC_Time.RTC),7);
       break;
         
       case ID_CPU_RTC:
         Read_InterRTC_PUCK((INT8U *)(&CPU_RTC_Time.RTC),7);
       break;
       
        case ID_RAM_RTC:
          mem_cpy((void *)(&CPU_RTC_Time.RTC),(void *)(&Cur_Time1),sizeof(CPU_RTC_Time.RTC)-1,\
                  (void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1);
       break;         
     }
    
     if(Check_BCD_Data((void *)(&CPU_RTC_Time.RTC),sizeof(CPU_RTC_Time.RTC)-1)==0)
     {
       Debug_Print("Sleep RTC Get Error(Src=%d):----->%x-%x-%x (%x) %x:%x:%x",Flag,CPU_RTC_Time.RTC.Year,CPU_RTC_Time.RTC.Month,\
       CPU_RTC_Time.RTC.Date,CPU_RTC_Time.RTC.Week,CPU_RTC_Time.RTC.Hour,CPU_RTC_Time.RTC.Min,CPU_RTC_Time.RTC.Sec);
     }
     else
     {
       INIT_STRUCT_VAR(CPU_RTC_Time);    //����ͷβ
       SET_VAR_CS_PUCK(CPU_RTC_Time.RTC);  //����У���
       return ;
     }       
  }   
  Debug_Print("CPU Soft RTC Got Failed!");
  INIT_STRUCT_VAR(CPU_RTC_Time);           //����ͷβ
  SET_VAR_CS_PUCK(CPU_RTC_Time.RTC);       //����У���
}
