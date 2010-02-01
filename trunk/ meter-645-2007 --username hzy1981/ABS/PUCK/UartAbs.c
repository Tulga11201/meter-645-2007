#define UART_ABS_PUCK
#include "Pub_PUCK.h"



#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P6"
#endif


/*���ܱ�         UART0-----����,UART2-----485_1,UART3-----485_2(�л���---P15),
  �ز�/GPRS�ѿر�UART0-----����,UART2-----485_1,UART3-----ESAM/CPU��UART1-----�ز�/GPRSģ��,(EVENT-GPRS---P04��EVENT-PLC---P04)
  Զ�̷ѿر�     UART0-----����,UART2-----485_1,UART3-----ESAM/CPU��UART1-----485_2(�л���---P04)
*/
typedef struct
{ 
  INT16U MaxBufLen;
  INT16U *CurRecLen;
  INT8U  *RecBufPtr;
  void (* const Init_Uart)(INT32U,INT16U);
  void (* const Start_Uart)(void);
  void (* const Stop_Uart)(void);
  INT8U (* const Ready_Uart)(void);
  INT8U (* const Send_Uart)(INT8U *,USHORT);
}CONST_UART_ATTRIB;


//���°�channel.h�ж����ͨ��˳��������UART��Ӧ��
const CONST_UART_ATTRIB  Const_Uart_Attib[MAX_UART_NUM]={
  {UART0_RX_BUFF_MAXSIZE,(INT16U *)(&Uart0_Rx_Count),(INT8U *)Uart0_RecBuf,&UART0_Init_PUCK,\
    &UART0_Start,&UART0_Stop,&UART0_RecData_pre_PUCK,&UART0_SendData_PUCK},
   
  {UART2_RX_BUFF_MAXSIZE,(INT16U *)(&Uart2_Rx_Count),(INT8U *)Uart2_RecBuf,&UART2_Init_PUCK,\
    &UART2_Start,&UART2_Stop,&UART2_RecData_pre_PUCK,&UART2_SendData_PUCK},
    
  {UART3_RX_BUFF_MAXSIZE,(INT16U *)(&Uart3_Rx_Count),(INT8U *)Uart3_RecBuf,&UART3_Init_PUCK,\
    &UART3_Start,&UART3_Stop,&UART3_RecData_pre_PUCK,&UART3_SendData_PUCK},
    
#ifdef UART1    
  {UART1_RX_BUFF_MAXSIZE,(INT16U *)(&Uart1_Rx_Count),(INT8U *)Uart1_RecBuf,&UART1_Init_PUCK,\
    &UART1_Start,&UART1_Stop,&UART1_RecData_pre_PUCK,&UART1_SendData_PUCK},
#endif 
};


/********************************************************************************
����ԭ�ͣ�void IRDA_Rec_Enable(void)
���ܣ����ݸɻɹ�״̬,ʹ����Ӧ�ĺ��⹦��
Enable---0:��ֹ��Ӧ�ĺ�����չ���
ע�⣺�ڵ͹�������£��ɻɹܵ�״̬�ж�״̬ǰ�ᣬ�����Ǻ���ĵ�Դ�����µ��ô˺������������У�
*********************************************************************************/
void IRDA_Rec_Enable(void)
{  
#ifdef NEAR_IRDA_EN
  if(GUMB_STATUS)  //Ŀǰ��Զ����
  {
     IRDA_FAR_REC_EN;
  }
  else             //Ŀǰ����������
  {
     IRDA_NEAR_REC_EN;
  }
#else
  EN_UART0_REC;
#endif 
}
/********************************************************************************
����ԭ�ͣ�void IRDA_Rec_Disable(void)
���ܣ����ݸɻɹ�״̬,��ֹ��Ӧ�ĺ��⹦��
Enable---0:��ֹ��Ӧ�ĺ�����չ���
*********************************************************************************/
void IRDA_Rec_Disable(void)
{
#ifdef NEAR_IRDA_EN
  if(GUMB_STATUS)  //Ŀǰ��Զ����
  {
     IRDA_NEAR_REC_EN;
  }
  else             //Ŀǰ����������
  {
     IRDA_FAR_REC_EN;
  }
#else
  DIS_UART0_REC;
#endif 
}
/**********************************************************************************
�������ܣ��򿪱������ͨ��
��ڣ�
Type-------------ͨ�����ͣ���Pub_PUCK.h����
Baurd----------������
���ڣ�1---------�ɹ���0--------ʧ��
**********************************************************************************/
INT8U Open_Channel_PUCK(INT8U Type,INT32U Baurd,INT16U Checkbit )
{
  if(Type>CHANEL_MAX)
    return 0;
  
  Const_Uart_Attib[Type].Init_Uart(Baurd,Checkbit);
  Const_Uart_Attib[Type].Start_Uart();
  Const_Uart_Attib[Type].Ready_Uart();
  if(Type==CHANEL_IRDA)
    IRDA_Rec_Enable();   //���ݲ�ͬ���ѡ��ͬ�ĺ�������
  return 1;
}
/**********************************************************************************
�������ܣ��رձ������ͨ��
��ڣ�
Type-------------ͨ�����ͣ���Pub_PUCK.h����
Baurd----------������
���ڣ�1---------�ɹ���0--------ʧ��
**********************************************************************************/
INT8U Close_Channel_PUCK(INT8U Type)
{
   if(Type>CHANEL_MAX)  
    return 0;
  
  Const_Uart_Attib[Type].Stop_Uart();
  if(Type==CHANEL_IRDA)
    IRDA_Rec_Disable();   //���ݲ�ͬ����ֹ��ͬ�ĺ�������
  return 1;
}
/**********************************************************************************
�������ܣ���ĳͨ����������
��ڣ�
Type-------------ͨ�����ͣ���Pub_PUCK.h����
DataSrc-------------����
DataLen----------���ݳ���
���ڣ�1---------���ͳɹ���0--------����ʧ��
**********************************************************************************/
INT8U Channel_DataSend_PUCK(INT8U Type,INT8U *DataSrc,INT16U DataLen)
{
    if(Type>CHANEL_MAX)  
      return 0;
    if(Type==CHANEL_IRDA)
    {      
      IRDA_Rec_Disable();  //ֻҪ�Ǻ���ڣ�����ǰ���رս���
      if((CHANEL_IRDA!=CHANEL_DEBG)||Check_Debug_En()==0)  //�Ǻ���ڣ����������Կڣ����߲��������������Ϣ
      {
        IRDA_SEND_EN;       //���������� 
        START_PMW;
      }
      else             //���Կڲ��Ǻ���ڣ����߲��ǹ���״̬
      {
        IRDA_SEND_DIS;
      }
      Const_Uart_Attib[Type].Send_Uart(DataSrc,DataLen);
      if((CHANEL_IRDA!=CHANEL_DEBG)||Check_Debug_En()==0) //�Ǻ���ڣ����������Կڣ����߲��������������Ϣ
      {
        IRDA_SEND_DIS;    //�����ֹ����
        STOP_PMW;
      }      
      IRDA_Rec_Enable();   //���ݵ�ǰ��״̬���򿪲�ͬ�ĺ���ͨ��      
      return 1;
    }    
    Const_Uart_Attib[Type].Send_Uart(DataSrc,DataLen);
    return 1;
}

/**********************************************************************************
�������ܣ���ѯͨ�����ݵĽ���
��ڣ�
Type------------��ǰ������ͨ������

**********************************************************************************/
void Channel_DataReceive_PUCK(INT8U Type,INT32U Status)
{

  INT16U MaxRecLen,Len,offset;
  INT8U *RecBufPtr;
  
  if(Type>CHANEL_MAX)
    return ;
 
  if(Status!=SYS_NORMAL)   //resumeģʽ��
  {
    if(Type!=CHANEL_IRDA)
      return ;
    
    if(IRDA_READ_METER_EN==0)  //����ģʽ�£����Ⳮ���ֹ
      return ;
    
  }
    
  RecBufPtr=Const_Uart_Attib[Type].RecBufPtr;
  MaxRecLen=Const_Uart_Attib[Type].MaxBufLen;
  
  Len=Search_Protocol_Frame(RecBufPtr,MaxRecLen,&offset);
  if((Len>=MIN_FRAME_PROCO_SIZE)&&(Len<=MAX_UART_REC_SIZE)&&(offset<=MaxRecLen))  //ȷʵ��645����,645���ٳ���Ϊ12�ֽ�
  {
    Debug_Print("<---------Receive Data,Channel_Id=%d,Len=%d",Type,Len);
    //DEBUG_BUF_PRINT(RecBufPtr,Len+offset,PRINT_HEX,30);  //������֡ǰ��Ҳ�����
    Len=Rcv_PROTOCOL_Frame_Proc(Type,RecBufPtr+offset,Len,(void *)Temp_Buf_PUCK, (void *)Temp_Buf_PUCK, TEMP_BUF_LEN);
    
     if(Len)   //��ҪӦ��
      Send_HostData_Public_Puck(Type,(INT8U *)Temp_Buf_PUCK,Len);  //1200bps,160�ֽڷ��Ͳ�ι��������������
    Const_Uart_Attib[Type].Ready_Uart();    //�������ý�����
#ifdef CHANNEL_FAST_EN
    if(CHECK_STRUCT_VAR(Rec_Frame_Status)==0 || REC_FRAME_CONDITION)
    {
      CLR_REC_FRAME;  
    }
#endif
    //�ȷ��ͺ��ӡ������Ϣ��ȷ���ٶ�
    Debug_Print("--------->Send Data,Channel_Id=%d,Len=%d",Type,Len);
    //DEBUG_BUF_PRINT((INT8U *)Temp_Buf_PUCK,Len,PRINT_HEX,30);
    
    Chanel_Para[Type].ExitFlag=1;
#if (NET_METER EQ NONET_METER) &&(PREPAID_EN >0) && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE)  //Զ�̷ѿر�������ʾ �ڶ�·485
    if(Type EQ UART1)
    {
      Chanel_Para[Type].ExitFlag=0;
      Chanel_Para[CHANEL_485_2].ExitFlag=1;
    }      
#endif
    
    SET_STRUCT_SUM(Chanel_Para[Type]);

    if(CHECK_STRUCT_VAR(S_Buf_PUCK)==0)  //���ͷβ������Խ��
      ASSERT_FAILED(); 
    Refresh_Sleep_Countr(0);   //������Ѻ������
  }
  else
  {
      Len=*Const_Uart_Attib[Type].CurRecLen;
      if(Len>=(MaxRecLen-10))  //���볤�Ƚӽ�����������
        Const_Uart_Attib[Type].Ready_Uart();  //���ý�����
  }
}
