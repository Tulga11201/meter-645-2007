
#include "Pub_PUCK.h"

/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSR0_vect
__interrupt void MD_INTSR0(void)
{     
  UCHAR	 rx_data;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
  
  EI();
  
  rx_data=RXD0;

#if SHELL_EN > 0    
 if((JUDGE_POWER_OFF EQ 0) &&(B_TEST_FAC_STATUS==0 || B_TEST_HARD_STATUS==0)) //�ǵ����£��������ߵ���ģʽ������
  {
    //DIS_UART0_REC;
    TXD0=rx_data;   //�����ַ�������
    //EN_UART0_REC;
  }
#endif
 
  if(Uart0_Rx_Count<UART0_RX_BUFF_MAXSIZE)
    Uart0_RecBuf[Uart0_Rx_Count++]=rx_data;
#ifdef CHANNEL_FAST_EN
  if((Uart0_Rx_Count>=MIN_FRAME_PROCO_SIZE) &&(0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart0_RecBuf,UART0_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif
}

/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSRE0_vect
__interrupt void MD_INTSRE0(void)
{
  UCHAR err_type;
  UCHAR	 rx_data;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
  
  EI();
  
  rx_data=RXD0;
   
#if SHELL_EN > 0  
  if((JUDGE_POWER_OFF EQ 0) &&(B_TEST_FAC_STATUS==0 || B_TEST_HARD_STATUS==0)) //�ǵ����£��������ߵ���ģʽ������
  {
    //DIS_UART0_REC;
    TXD0=rx_data;   //�����ַ�������
    //EN_UART0_REC;
  }
#endif
  
  if(Uart0_Rx_Count<UART0_RX_BUFF_MAXSIZE)
    Uart0_RecBuf[Uart0_Rx_Count++]=rx_data;  
  err_type = (UCHAR)(SSR01 & 0x0007);
  SIR01 = (USHORT)err_type;
  //CALL_UART0_Error(err_type);
#ifdef CHANNEL_FAST_EN
  if((Uart0_Rx_Count>=MIN_FRAME_PROCO_SIZE) &&(0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart0_RecBuf,UART0_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTST0_vect
__interrupt void MD_INTST0(void)
{
	/*if( gUart0TxCnt > 0 ){
		TXD0 = *gpUart0TxAddress;
		gpUart0TxAddress++;
		gUart0TxCnt--;
	}
	else{
		CALL_UART0_Send();
	}*/
}

/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART0_Send( void )
{
	/* Start user code. Do not edit comment generated here */

 // UART0_send_finish_flag=1;
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART0_Error( UCHAR err_type )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSR1_vect
__interrupt void MD_INTSR1(void)
{
#ifdef UART1
  UCHAR	 rx_data;
  rx_data=RXD1;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
  INT16U Len;
#endif
  
if(Uart1_Rx_Count<UART1_RX_BUFF_MAXSIZE)
  Uart1_RecBuf[Uart1_Rx_Count++]=rx_data;

#ifdef CHANNEL_FAST_EN
if((Uart1_Rx_Count>=MIN_FRAME_PROCO_SIZE) && (0x16==rx_data))
  {
    Len=Simple_Search_Frame((INT8U *)Uart1_RecBuf,UART1_RX_BUFF_MAXSIZE,&offset);//>=MIN_FRAME_PROCO_SIZE;
    if(Len)
    {
#if NET_METER EQ CARRIER_METER
      if(Phase_Get_Addr_Frame((INT8U *)Uart1_RecBuf+offset,Len))
      {
        Uart1_Rx_Count=0;//���������־
        memset((INT8U *)Uart1_RecBuf,0x00,sizeof(Uart1_RecBuf));        
        
      }
#else    
      
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
#endif
    }
  }
#endif
#endif
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSRE1_vect
__interrupt void MD_INTSRE1(void)
{
#ifdef UART1
  UCHAR err_type;
  UCHAR	 rx_data;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
  
  rx_data=RXD1;
  if(Uart1_Rx_Count<UART1_RX_BUFF_MAXSIZE)
    Uart1_RecBuf[Uart1_Rx_Count++]=rx_data; 
  err_type = (UCHAR)(SSR03 & 0x0007);
  SIR03 = (USHORT)err_type;
  //CALL_UART1_Error( err_type );
#ifdef CHANNEL_FAST_EN
  if((Uart1_Rx_Count>=MIN_FRAME_PROCO_SIZE) &&(0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart1_RecBuf,UART1_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif
#endif  
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTST1_vect
__interrupt void MD_INTST1(void)
{

}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART1_Send( void )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART1_Error( UCHAR err_type )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_IIC10_MasterError( MD_STATUS flag )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_IIC10_MasterReceiveEnd( void )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_IIC10_MasterSendEnd( void )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSR2_vect
__interrupt void MD_INTSR2(void)
{
  UCHAR	 rx_data;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
  rx_data=RXD2;
  if(Uart2_Rx_Count<UART2_RX_BUFF_MAXSIZE)
    Uart2_RecBuf[Uart2_Rx_Count++]=rx_data;
#ifdef CHANNEL_FAST_EN
  if((Uart2_Rx_Count>=MIN_FRAME_PROCO_SIZE) && (0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart2_RecBuf,UART2_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSRE2_vect
__interrupt void MD_INTSRE2(void)
{	
  UCHAR err_type;
  UCHAR	 rx_data;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
  
  rx_data=RXD2;
  if(Uart2_Rx_Count<UART2_RX_BUFF_MAXSIZE)
    Uart2_RecBuf[Uart2_Rx_Count++]=rx_data; 
  err_type = (UCHAR)(SSR11 & 0x0007);
  SIR11 = (USHORT)err_type;
  //CALL_UART2_Error( err_type );
#ifdef CHANNEL_FAST_EN
  if((Uart2_Rx_Count>=MIN_FRAME_PROCO_SIZE) && (0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart2_RecBuf,UART2_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif

}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTST2_vect
__interrupt void MD_INTST2(void)
{
  /*
	if( gUart2TxCnt > 0 ){
		TXD2 = *gpUart2TxAddress;
		gpUart2TxAddress++;
		gUart2TxCnt--;
	}
	else{
		CALL_UART2_Send();
	}*/
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART2_Send( void )
{
	/* Start user code. Do not edit comment generated here */
   //UART2_send_finish_flag=1;
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART2_Error( UCHAR err_type )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSR3_vect
__interrupt void MD_INTSR3(void)
{ 
   UCHAR rx_data;
    rx_data=RXD3;
  #ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
    
  if(Uart3_Rx_Count<UART3_RX_BUFF_MAXSIZE)
    Uart3_RecBuf[Uart3_Rx_Count++]=rx_data;
  
#ifdef CHANNEL_FAST_EN
  if((Uart3_Rx_Count>=MIN_FRAME_PROCO_SIZE) && (0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart3_RecBuf,UART3_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTSRE3_vect
__interrupt void MD_INTSRE3(void)
{  
  UCHAR err_type;
  UCHAR	 rx_data;
#ifdef CHANNEL_FAST_EN
  INT16U offset;
#endif
  
  rx_data=RXD3;
  if(Uart3_Rx_Count<UART3_RX_BUFF_MAXSIZE)
    Uart3_RecBuf[Uart3_Rx_Count++]=rx_data;  
  err_type = (UCHAR)(SSR13 & 0x0007);
  SIR13 = (USHORT)err_type;
  //CALL_UART3_Error( err_type );
  
#ifdef CHANNEL_FAST_EN
  if((Uart3_Rx_Count>=MIN_FRAME_PROCO_SIZE) && (0x16==rx_data))
  {
    if(Simple_Search_Frame((INT8U *)Uart3_RecBuf,UART3_RX_BUFF_MAXSIZE,&offset)>=MIN_FRAME_PROCO_SIZE)
      Rec_Frame_Status.RecFrameFlag=REC_FRAME_FLAG;
  }
#endif
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
#pragma vector = INTST3_vect
__interrupt void MD_INTST3(void)
{
/*	if( gUart3TxCnt > 0 ){
		TXD3 = *gpUart3TxAddress;
		gpUart3TxAddress++;
		gUart3TxCnt--;
	}
	else{
		CALL_UART3_Send();
	}*/
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART3_Send( void )
{
	/* Start user code. Do not edit comment generated here */
    //UART3_send_finish_flag=1;
	/* End user code. Do not edit comment generated here */
}
/********************************************************************************
PUCK:
��ڣ�
���أ�
********************************************************************************/
void CALL_UART3_Error( UCHAR err_type )
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
