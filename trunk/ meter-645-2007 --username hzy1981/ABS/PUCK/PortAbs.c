#define PORT_ABS_PUCK
#include "Pub_PUCK.h"


/********************************************************************************
void  Get_Meter_Hard_Mode(void)
�������ܣ���ȡ�������ģʽ
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Meter_Hard_Mode(void)
{
  if(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS)  //�����������ģʽ��
    return MODE_RUN;
  
  if(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS EQ 0)
    return MODE_DEBUG;
  
  if(B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS)
    return MODE_FAC;
  
  if(B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS EQ 0)  //����ģʽ����
    return MODE_TEST;  
  
  //�쳣��
  return MODE_RUN;
}


/********************************************************************************
********************************************************************************/

void PORT_ChangeP142Output_PUCK(INT8U Level)
{
  PORT_ChangeP142Output(0,Level);  
}


void PORT_Relay_On_PUCK(INT8U Level)
{
  LARGE_TOOGLE_OFF_SET;   //�����յĹر�
  
  if(Level)
    LARGE_TOOGLE_ON_SET;
  else
    LARGE_TOOGLE_ON_CLR;
}



void PORT_Relay_Off_PUCK(INT8U Level)
{
 LARGE_TOOGLE_ON_SET;   //�������Ĺر�
 
  if(Level)
    LARGE_TOOGLE_OFF_SET;
  else
    LARGE_TOOGLE_OFF_CLR;
}

//#pragma pack(1)
typedef struct
{
  INT8U NeedInit:1;                 //��Ҫ��ʼ����־
  INT8U InitLevel:1;                //���������£�����ʱ�ĵ�ƽֵ��
  INT8U SleepLevel:1;               //�͹�������£���Ҫ��ʼ�ĵ�ƽֵ��
  INT8U ValidLevel:1;               //��ƽģʽ�£������Ч�ĵ�ƽֵ��
  INT8U MultiFlag:1;                //�Ƿ��Ǹ��϶��ӱ�־����3��1��0-------���Ǹ��϶��ӣ�1------�Ǹ��϶��ӣ�2-------------
  INT8U LevelProprty:3;             //����ģʽ��LEVEL_MODE��PULSE_MODE��MULTI_MODE  
  void  (* const FuncPtr)(INT8U);
  INT8U (* const MultiPortEn)(void); //���һ����(MultiFlagΪ1ʱ)�����ݴ������ж����
  INT8U (* const GetOutMode)(void); //���ݲ����������������ʲô��ʽ   
}CONST_PORT_STATUS;

//���¶���������ڵĳ�����
CONST CONST_PORT_STATUS  Const_Port_Status[MAX_PORT_NUM]={
  {0},
  {0,1,0,0,0,LEVEL_MODE,&PORT_ChangeP64Output,0,0},    //�й��������------------------------------------------------------------1
  {0,1,0,0,0,LEVEL_MODE,&PORT_ChangeP65Output,0,0},    //�޹��������------------------------------------------------------------2
  {1,1,0,0,0,LEVEL_MODE,&PORT_ChangeP82Output,&Get_Sec_Out_En,0},    //������ʹ��------------------------------------------------3
  {1,0,0,1,0,LEVEL_MODE,&PORT_ChangeP131Output,0,0},    //��բָʾ��--------------------------------------------------------------4
  {1,0,0,1,0,LEVEL_MODE,&PORT_ChangeP157Output,0,0},    //����ָʾ��--------------------------------------------------------------5

  {1,0,0,1,0,MULTI_MODE,&PORT_ChangeP81Output,0,&Get_AuxPort_Out},    //�������ӱ������-----------------------------------------6(ע���ʼ��ƽ)
  {1,0,0,1,0,MULTI_MODE,&PORT_ChangeP80Output,0,&Get_Toogle_Out},     //��բ���-------------------------------------------------7(ע���ʼ��ƽ)
  
  
  //��բע�ⳣ�ճ������Գ���Ϊ�ο�
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP66Output,0,0},    //�й��������------------------------------------------------------------8
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP67Output,0,0},    //�޹��������------------------------------------------------------------9

  {1,1,0,0,1,PULSE_MODE,&PORT_ChangeP83Output,&Get_Demand_Out_En,0},    //�������ڵ����-----------------------------------------10
  {1,1,0,0,1,PULSE_MODE,&PORT_ChangeP83Output,&Get_Slipe_Out_En,0},     //�������ڵ����-----------------------------------------11
  {1,1,0,0,1,PULSE_MODE,&PORT_ChangeP83Output,&Get_Parse_Out_En,0},    //ʱ�����------------------------------------------------12
  
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP150Output,0,0},   //���й������-------------------------------------------------------------13
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP151Output,0,0},   //���޹������-------------------------------------------------------------14
  {1,0,0,1,0,PULSE_MODE,&PORT_ChangeP142Output_PUCK,0,0},  //���ȱ��� -------------------------------------------------------------15
  {1,0,0,0,0,PULSE_MODE,&PORT_Relay_On_PUCK,0,0},  //���崥��ʽ�̵�������--------------------------------------------------16
  {1,1,0,0,0,PULSE_MODE,&PORT_Relay_Off_PUCK,0,0}  //���崥��ʽ�̵����ر�--------------------------------------------------17

};

//#pragma pack()



/********************************************************************************
INT8U  Get_AuxPort_Out(void)
�������ܣ�
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_AuxPort_Out(void)
{
  return LEVEL_MODE;
}
/********************************************************************************
INT8U  Get_Toogle_Out(void)
�������ܣ�
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Toogle_Out(void)
{
  if(EXT_SWITCH_MODE EQ 0)
    return LEVEL_MODE;
  return PULSE_MODE;
}
/********************************************************************************
INT8U  Get_Sec_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ���������ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Sec_Out_En(void)
{
#if SEC_OUT_POWER_ON>0 //�ϵ�����������
  return SEC_OUT_PUT_EN;
#else
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x00)
     return 1;  
  }
  return 0;
#endif
}

/********************************************************************************
INT8U  Change_Sec_Out(void)
�������ܣ�����ģʽ�֣������й����У�ʹ��������
��ڣ�  
���أ�
    ��
********************************************************************************/
void Init_Sec_Pulse(void)
{
  
#if SEC_OUT_POWER_ON>0 //�ϵ�����������
   Read_Storage_Data_PUCK(SDI_OUTPUT_MODE,(INT8U *)(&Multi_Port_Mode.Mode),1);
   SET_STRUCT_SUM(Multi_Port_Mode);
#endif 
  
  
#if SEC_MULTI_PORT>0  //�������Ǹ��϶��� 
    if(Get_Sec_Out_En())   //���϶��ӣ���ǰ�����������
    {
      Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
  
  #if MULTI_3_PORT>=2   //�������϶��ӣ��������干�ã�
      Port_Out_Pub(EXT_ID_DEMAND,PORT_END);
      Port_Out_Pub(EXT_ID_SLIPE,PORT_END);
      Port_Out_Pub(EXT_ID_PARSE,PORT_END);
  #endif  
    }
    else                   //���϶��ӣ���ǰ�������������
    {
      Port_Out_Pub(EXT_ID_SEC_EN,PORT_END);
    }
#else           //�����岻�Ǹ��϶��� 
    Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
    //�������϶��ӹ��ã���������ζȻ���   
    if(Multi_Port_Mode.Mode EQ 0 || Multi_Port_Mode.Mode>2)   //��ǰ�������ǵ����ģ���ģʽ�����õĶ�������Ч��Ĭ��Ϊ��������
       Multi_Port_Mode.Mode=2;      //���ô���

#endif
}
/********************************************************************************
INT8U  Get_Parse_Out_En(void)
�������ܣ�����ģʽ�֣���ȡʱ�����ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Parse_Out_En(void)
{
#if MULTI_3_PORT EQ 0  //�����Ķ���
   return 1;  
#elif MULTI_3_PORT EQ 1    //�Ǹ��϶��ӣ����������岻����
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x02)
     return 1;  
  }  
  return 0;
  
#elif (MULTI_3_PORT EQ 2)&&(SEC_OUT_POWER_ON>0)  //���϶��ӣ����������干��    
    #if SEC_OUT_POWER_ON>0 //�ϵ�����������
      return DEMAND_OUT_PUT_EN;
    #else 
     INT8U Len;
     INT8U Temp;
      
     Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
     if(1 EQ Len)
     {
        if((Temp&0x03) EQ 0x02)
         return 1;  
     }  
     return 0;
     #endif
#endif   
}
/********************************************************************************
INT8U  Get_Demand_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ�������ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Demand_Out_En(void)
{
#if MULTI_3_PORT EQ 0  //�����Ķ���
   return 1;  
#elif MULTI_3_PORT EQ 1    //�Ǹ��϶��ӣ����������岻����
  INT8U Len;
  INT8U Temp;
  
  if(DEMAND_OUT_MODE EQ 0)   //���������
      return 0;
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x01)
     return 1;  
  }  
  return 0;
  
#elif (MULTI_3_PORT EQ 2)&&(SEC_OUT_POWER_ON>0)  //���϶��ӣ����������干��
    if(DEMAND_OUT_MODE EQ 0)   //������
      return 0;
    
    #if SEC_OUT_POWER_ON>0 //�ϵ�����������
      return DEMAND_OUT_PUT_EN;
    #else 
     INT8U Len;
      INT8U Temp;
      
      if(DEMAND_OUT_MODE EQ 0)   //���������
          return 0;
      Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
      if(1 EQ Len)
      {
        if((Temp&0x03) EQ 0x01)
         return 1;  
      }  
      return 0; 
      
    #endif
#endif                  
}
/********************************************************************************
INT8U  Get_Slipe_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ����ʱ�䵽���ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_Slipe_Out_En(void)
{
#if MULTI_3_PORT EQ 0  //�����Ķ���
   return 1;  
#elif MULTI_3_PORT EQ 1    //�Ǹ��϶��ӣ����������岻����
  INT8U Len;
  INT8U Temp;
  
  if(DEMAND_OUT_MODE EQ 1)   //����������
      return 0;
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x01)
     return 1;  
  }  
  return 0;
  
#elif (MULTI_3_PORT EQ 2)&&(SEC_OUT_POWER_ON>0)  //���϶��ӣ����������干��
    if(DEMAND_OUT_MODE EQ 1)   //����������
      return 0;
    
    #if SEC_OUT_POWER_ON>0 //�ϵ�����������
      return DEMAND_OUT_PUT_EN;
    #else 
     INT8U Len;
      INT8U Temp;
      
      if(DEMAND_OUT_MODE EQ 1)   //����������
          return 0;
      Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
      if(1 EQ Len)
      {
        if((Temp&0x03) EQ 0x01)
         return 1;  
      }  
      return 0; 
      
    #endif 
#endif     
}
/********************************************************************************
INT8U  Get_FeeAlarm_Out_En(void)
�������ܣ�����ģʽ�֣���ȡǷ�ѱ������ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_FeeAlarm_Out_En(void)
{
/*
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);  // //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�����������ź������ϵ��ָ��������������
  if(1 EQ Len)
  {
    if(Temp&0x03 EQ 0x03 && PREPAID_EN EQ 1)   //ģʽ��2 bit5��1��Ԥ���ѹ���
     return 1;  
  }  
 */
  return 0;
}
/********************************************************************************
INT8U  Get_GridAlarm_Out_En(void)
�������ܣ�����ģʽ�֣���ȡ����ʱ�䵽���ʹ��
��ڣ�  
���أ�
    ��
********************************************************************************/
INT8U Get_GridAlarm_Out_En(void)
{
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);  // //����һ���״̬:0-�����壻1-�������ڣ�2-ʱ���л�.��������ź������ϵ��ָ��������������
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x03 && POWER_CTRL_EN EQ 1)  //ģʽ��2 bit4��1�����ع��ܹ���
     return 1;  
  }  
  return 0;
}

/********************************************************************************
void void Init_All_Device_Port(INT8U Mode)
�������ܣ���ʼ�����ж˿�,
��ڣ�   ���ݲ�ͬ״̬���趨�˿�״̬
���أ�
    ��
********************************************************************************/
void Init_All_Port(INT32U Mode)
{
   INT8U i;
   
  for(i=MIN_PORT_DI;i<=MAX_PORT_DI;i++)
  {
    if(0 EQ Const_Port_Status[i].NeedInit)
    {
      Ext_Port_Hander[i].InitFlag=1;
      continue;
    }
    
    if(SYS_NORMAL EQ Mode)
    {
      if(Const_Port_Status[i].FuncPtr)
        Const_Port_Status[i].FuncPtr(Const_Port_Status[i].InitLevel);    //����ģʽ�������Ϊ��Чλ
    }
    //����ģʽ���Ѿ���Init_All_IO_XX()��������    
    Ext_Port_Hander[i].InitFlag=1;
  }
}
/********************************************************************************
INT8U Port_Level_Out(INT8U Id,INT16U StartOrEnd)
�������ܣ����ⲿ�����ŵĵ�ƽ�����������
��ڣ�
    Id -------�ⲿ���ӹ���Id����
    StartOrEnd---------����ߵ�ƽ���ǵ͵�
���أ�
    ��
ע�⣺������ڲ�����Port_Pulse_Out����һ�£�
********************************************************************************/
INT8U Port_Level_Out(INT8U Id,INT8U Level)
{
  if(Id<MIN_LEVEL_PORT_DI || Id>MAX_LEVEL_PORT_DI)
    return 0;
 
  if(Const_Port_Status[Id].LevelProprty EQ PULSE_MODE)
    return 0;
  
  if(Const_Port_Status[Id].LevelProprty EQ MULTI_MODE) //�ɱ�ģʽ����
  {
    if(Const_Port_Status[Id].GetOutMode EQ 0) //�պ���
     return 0;
    
    if(Const_Port_Status[Id].GetOutMode() EQ PULSE_MODE) //�ɱ�ģʽΪ����
      return 0;    
  }
  
  //��ƽģʽ���,ֱ�ӶԶ˿������ƽ
  if(Const_Port_Status[Id].FuncPtr)
  {
    if(PORT_END EQ Level)
      Const_Port_Status[Id].FuncPtr(!Const_Port_Status[Id].ValidLevel);
    else
      Const_Port_Status[Id].FuncPtr(Const_Port_Status[Id].ValidLevel);
    return 1;
  }
  
  return 0;}

/********************************************************************************
void Ext_Port_Out(INT8U Id,INT16U MsCounts)
�������ܣ����ⲿ�����ŵĳ��������������
��ڣ�
    Id -------�ⲿ���ӹ���Id����
    PulseWidth ---�ⲿ����Ϊ�������ʱ�������ȣ���λms����ƽ���ʱ���˲�����Ч
���أ�
    ��
********************************************************************************/
INT8U Port_Pulse_Out(INT8U Id,INT16U PulseWidth)
{
  if(Id<MIN_PULSE_PORT_DI || Id>MAX_PULSE_PORT_DI)
    return 0;
  
  //ע�⣬���ﲻ�ж��Ǻ��������ʽ�ˣ�
  
  //����ģʽ������˿������ExtPort_xMs_Hook�е��á�  
  if(PulseWidth EQ 0)  //������ӵ���ʱ���
  {
    Ext_Port_Hander[Id].Status=0;
    Ext_Port_Hander[Id].CurCount=0;
    Ext_Port_Hander[Id].CurCountBak=0;
    //Ext_Port_Hander[Id].LoopCount=0;
    return 0;
  }
  
  //Ext_Port_Hander[Id].LoopCount=1;  
  Ext_Port_Hander[Id].CurCountBak=PulseWidth/MS_HOOK_NUM;   //ÿ�ζ�����һ��
  //if(Ext_Port_Hander[Id].LoopCount EQ 1)   //�״�����
  //{    
    Ext_Port_Hander[Id].Status=1;
  //}
  return 1;
}
/********************************************************************************
void Port_Out_Pub(INT8U Id,INT16U Para)
��ڣ�
    Id -------���ӹ���Id����
    Para -------���ڵ�ƽ���壬PORT_START ��ʾ������Ч��ƽ��PORT_END Ϊ��Ч��ƽ�����������������ʾ������
���أ�
    ��
********************************************************************************/
void Port_Out_Pub(INT8U Id,INT16U Para)
{
  if(Id<MIN_PORT_DI || Id>MAX_PORT_DI)
    return ;
  
  if(Const_Port_Status[Id].MultiFlag) //�Ǹ��϶���
  {
    if(Const_Port_Status[Id].MultiPortEn EQ 0)
      return ;
    
    if(Const_Port_Status[Id].MultiPortEn() EQ 0)  //�Ǹ��϶��ӣ���������ö�������������ڵ�ƽ��ʽ
      return ;     
  }
    
  //��ƽ��ʽ
  if(Port_Level_Out(Id,Para))  //�����ķ�ʽ�˳�
     return ;
  
 //���巽ʽ
  Port_Pulse_Out(Id,Para);  
 
}
/********************************************************************************
void Beep_For_Measu_Alarm_PUCK(void)
�������ܣ���������������
��ڣ�
���أ�
    ��
********************************************************************************/
void Beep_For_Measu_Alarm_PUCK(INT8U ErrInfo)
{ 

  //ReNew_Err_Code(DIS_MEAS_ERR);
#if HARD_ERR_BEEP
  Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
  Port_Out_Pub(INTER_ID_ALARM_DIS,150); 
#endif
  //���У��¼����¼���¼�ж���������
 
}
/********************************************************************************
void Beep_For_Para(void)
�������ܣ�����������:Ĭ�ϲ���û������
��ڣ�
���أ�
    ��
********************************************************************************/
void Beep_For_Para(void)
{
  Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
  //Port_Out_Pub(INTER_ID_ALARM_DIS,BEEP_MODE_100); 
}
/********************************************************************************
void Beep_Only_Alarm_PUCK(void)
�������ܣ���������������
��ڣ�
���أ�
    ��
********************************************************************************/
void Beep_Only_Alarm_PUCK(void)
{
#if HARD_ERR_BEEP
 Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_150); 
#endif
}
/********************************************************************************
void ExtPort_xMs_Hook(void)
�������ܣ�1ms���ⲿIO�ڵĹ��Ӻ���
��ڣ�
���أ�
    ��
********************************************************************************/
//ms�˿ڹ��Ӻ���,���뼶��λ��MS_HOOK_NUM
void ExtPort_xMs_Hook(void)
{
  INT8U i;
  
  for(i=MIN_PULSE_PORT_DI;i<=MAX_PULSE_PORT_DI;i++)
  {
    
    //if(Const_Port_Status[i].LevelProprty EQ LEVEL_MODE) //��ƽģʽ
    //  continue ;
       
    //if(Const_Port_Status[i].NeedInit && (0 EQ Ext_Port_Hander[i].InitFlag))
    //  continue ;
    
    if(Const_Port_Status[i].LevelProprty EQ MULTI_MODE) //�ɱ�ģʽ����
    {
      if(Const_Port_Status[i].GetOutMode EQ 0) //�պ���
       continue ;
      
      if(Const_Port_Status[i].GetOutMode() EQ LEVEL_MODE) //�ɱ�ģʽΪ��ƽ
        continue ;
    }
   /**/
    
    //if(Ext_Port_Hander[i].LoopCount)
    //{
      switch(Ext_Port_Hander[i].Status)
      {
      case 0:   //�޶���
        break;
      case 1:                                 //�ֻ�����
        //���ö˿ڲ�����������ƽ��PULSE_OUT
        if(Const_Port_Status[i].FuncPtr)
          Const_Port_Status[i].FuncPtr(Const_Port_Status[i].ValidLevel);
        Ext_Port_Hander[i].Status=2;
        break;
      case 2:  //������
        if(Ext_Port_Hander[i].CurCount>=Ext_Port_Hander[i].CurCountBak-1)  //������һ�ֻ�
        {
            //Ext_Port_Hander[i].CurCount=0;
            //Ext_Port_Hander[i].Status=1;
            //Ext_Port_Hander[i].LoopCount--;   
            if(Const_Port_Status[i].FuncPtr)
              Const_Port_Status[i].FuncPtr(!Const_Port_Status[i].ValidLevel);
            //if(Ext_Port_Hander[i].LoopCount EQ 0) //����
            { 
              Ext_Port_Hander[i].Status=0;     //����
              Ext_Port_Hander[i].CurCount=0;
              Ext_Port_Hander[i].CurCountBak=0;   //
            }
         }
         else                               //��ǰ�ֻ�
         {  
           Ext_Port_Hander[i].CurCount++;         
         }
        break;
      }
    //}
  }
}
/********************************************************************************
void Wait_For_Power_On(void)
�������ܣ���������������
��ڣ�
���أ�
    ��
********************************************************************************/
#define WAIT_FOR_POWER_SEC 2

void Wait_For_Power_On(void)
{
  volatile INT32U SecTimr;
  INT8U SecNum;
  
  SecTimr=Sec_Timer_Pub;
  SecNum=0;
  
  while(1)
  {
    if(SecNum>=WAIT_FOR_POWER_SEC)
      return ;
    
    Clr_Ext_Inter_Dog();
    if(SecTimr!=Sec_Timer_Pub)
    {
      SecNum++;
      SecTimr=Sec_Timer_Pub;
    }
  }   
}