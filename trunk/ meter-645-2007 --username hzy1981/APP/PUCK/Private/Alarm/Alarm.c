#define ALARM_C
#include "Pub_PUCK.h"
#include "Alarm.h"
/***********************************************************************
�������ܣ�����λ�����ֽڵ�λ����ȡ��Ӧ��λ��Ϣ���ֽ���Ϣ
��ڣ���
���ڣ���
���ܱ��ڼ�⵽�쳣��ʱ�ӵ��Ƿѹ���й����ܷ���ı䣨˫��������⣩��ʧѹ�����࣬
�Լ���ѹ����ѹ������ʧ����������ƽ�⡢���������򡢹������������ޡ����صȣ�ʱ
����ѭ����ʾ���쳣���������н���ָʾ�⣬����ָʾ��ҲӦͬʱ������
***********************************************************************/
// LED��LCD�϶�����������������ģ������������1������������ Get_Prepaid_Status() PREPAID_MONEY_LEFT1
void Sound_LED_LCD_Port_Alarm(void)
{
  INT8U i;
  static S_Int8U LastSatus={CHK_BYTE,0x00,CHK_BYTE};
  
   for(i=0;i<ALARM_EVENT_NUM;i++)
   {
      if(Read_Event_Status(Alarm_Event_Property[i]))  //���¼�����
      {         
        Port_Out_Pub(INTER_ID_ALARM_DIS,300);
        Port_Out_Pub(EXT_ID_AUX_ALARM,AUX_PORT_PULSE_WD);         
        Set_Event_Instant(ID_ALARM_OUT);
        LastSatus.Var=0x05;
         break;      
      }
   }
   if(i>=ALARM_EVENT_NUM)
   {
     Clr_Event_Instant(ID_ALARM_OUT);
     if(LastSatus.Var EQ 0x05)
     {
       Port_Out_Pub(INTER_ID_ALARM_DIS,PORT_END);   //��ƽ��ʽ���Զ��رգ����巽ʽ���������
       Port_Out_Pub(EXT_ID_AUX_ALARM,PORT_END);  
       LastSatus.Var=0;
     }
   }
   
   if(SWITCH_OFF_DELAY) //��բ��ʱ����������
      Port_Out_Pub(INTER_ID_ALARM_BEEP,300);

   if(Get_Prepaid_Status() EQ PREPAID_MONEY_OVERDRAFT) //͸֧����������
   { 
     if(Beep_Disable EQ 0)
       Port_Out_Pub(INTER_ID_ALARM_BEEP,300);    
   }
}
/***********************************************************************
void Sound_LED_LCD_Port_Alarm(void)
{
  INT8U  i,j,flag[ALARM_MODE_NUM]={0},flag1,flag2;
   static INT8U num=0;
  
   for(i=0;i<ALARM_EVENT_NUM;i++)
   {
     if(Alarm_Event_Property[i].ModeEn EQ 0 && Read_Event_Status(Alarm_Event_Property[i].EventID))  //�����ģʽ���޹أ�ǿ������������¼����������ж�
     {
       for(j=0;j<ALARM_MODE_NUM;j++)  //����������LED�����������ű���
       {
         Port_Out_Pub(Alarm_Mode_Property[j].PortID,Alarm_Mode_Property[j].AlarmWidth);
         Set_Event_Instant(ID_ALARM_OUT);
         flag[j]=1;        
       }
       flag2=1;
       num=ALARM_MODE_NUM;
       break;
     }
     else                                   //�����ģʽ���й�
     {
       if(GET_BIT(*(Alarm_Event_Property[i].EventEn),Alarm_Event_Property[i].EventBit))   //�Ƿ������¼��������
       {
         if(Read_Event_Status(Alarm_Event_Property[i].EventID))  //ȷ�ϸ��¼�����
         {
           for(j=0;j<ALARM_MODE_NUM;j++)  //����������LED�����������ű���
           {
             if(GET_BIT(*(Alarm_Mode_Property[j].AlarmEn),Alarm_Mode_Property[j].AlarmBit))  //�Ƿ����������
             {
               Port_Out_Pub(Alarm_Mode_Property[j].PortID,Alarm_Mode_Property[j].AlarmWidth);
               Set_Event_Instant(ID_ALARM_OUT);               
               flag[j]=1;
             }           
           }
           num++;
         }     
       } 
     }  
     
     flag2=0;
     flag1=1;
     for(j=0;j<ALARM_MODE_NUM;j++)  //����������LED�����������ű���
     {
       if(flag[j] EQ 0)  //��ǰ������ʽû�����.����
         flag1=0;
       else           //��ǰ�����¼�����     
         flag2=1;
     }
     if(flag1)   //���������ʽ�������
     {
       num=ALARM_MODE_NUM;
       break;
     }
   }
   
   if(0==flag2)  //���¼�����
   {
      Clr_Event_Instant(ID_ALARM_OUT);
      if(num>=ALARM_MODE_NUM)  //ԭ�����¼������ڽ�����
      {
        num=0;
        for(j=0;j<ALARM_MODE_NUM;j++)  //�ر�����������LED�����������ű���
          Port_Out_Pub(Alarm_Mode_Property[j].PortID,PORT_END);     
      }
   }
}
***********************************************************************/