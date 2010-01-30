
#ifndef CHANNEL_CVS
#define CHANNEL_CVS

#ifndef CHANNEL_C
#define CHANNEL_EXT  extern volatile
#else
#define CHANNEL_EXT  volatile
#endif


#define MIN_FRAME_PROCO_SIZE  11  //协议最小字节数
#define MAX_UART_REC_SIZE UART3_RX_BUFF_MAXSIZE

 //获取通道参数的ID
#define DI_CHANEL_IRDA1      0x04000701    //调制型红外光口
#define DI_CHANEL_IRDA2      0x04000702    //接触式红外光口
#define DI_CHANEL_485_1      0x04000703    //第一路485
#define DI_CHANEL_485_2      0x04000704    //第二路485
#define DI_CHANEL_485_3      0x04000705    //第三路485


//以下通道定义，与Const_Uart_Attib[MAX_UART_NUM] 相对应
#define CHANEL_IRDA     UART0           //红外通道数据---------UART0
#define CHANEL_485_1    UART2           //485通道数据---------UART2
#define CHANEL_485_2    UART3           //485通道数据---------UART3
#ifdef UART1
#define CHANEL_MOUDEL   UART1           //模块通道数据---------UART1
#endif

#define  CHANEL_MIN CHANEL_IRDA
#define  CHANEL_MAX (MAX_UART_NUM-1)

#define BAUD_IRDA    1200            //红外口波特率,
#define CHANEL_DEBG  CHANEL_IRDA    //调试口通道号
#define BAUD_DEBG    115200         //调试口波特率,
#define BAUD_CPU_ESAM    9600         //CPU_ESAM波特率




#if NET_METER EQ CARRIER_METER   //载波表
  #define BAUD_MOUDLE  2400          //载波口波特率
#elif  NET_METER EQ GPRS_METER   // GPRS网络表
  #define BAUD_MOUDLE  19200          //GPRS模块口波特率
#else
  #define BAUD_MOUDLE  0         //其他:表示此口的波特率不是取自宏，取自参数
#endif

#define BAUD_IRDA_DEFAULT 1200            //默认的波特率
#define BAUD_485_DEFAULT  2400            //默认的波特率



#define SHELL_REC_MAX_LEN UART0_RX_BUFF_MAXSIZE   // shell buf 最大长度
#define SHELL_REC_CUR_LEN Uart0_Rx_Count          //当前 shell buf 收到的字节长度
#define SHELL_REC_BUF Uart0_RecBuf                //当前 shell的 buf
#define SHELL_CLR_BUF UART0_RecData_pre_PUCK     //清shell 缓冲接收过程


typedef struct
{  
  INT32U  Baud;
  INT8U ExitFlag;  
  INT8U CS[CS_BYTES]; 
}CHANEL_PARA;
CHANNEL_EXT  CHANEL_PARA Chanel_Para[CHANEL_MAX+1];

//CHANNEL_EXT  INT32U Com_Delay_Count;

INT8U Get_Buf_MulitByte_Sum(INT8U *Src,INT16U SrcLen,INT8U ByteGroup,INT8U *Dst,INT8U DstLen);
INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U Src_Len);
INT16U  Get_HostData_Public_Puck(INT8U *Channl);

INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len);
INT8U  Debug_Out_Puts_Puck(INT8S *Srcbuf);
void Init_DebugChanel_PUCK(INT8U);
void Close_DebugChanel_PUCK(INT8U FacFlag);
void Init_Debug_Uart(void);
void Init_All_UART(INT32U Mode);
void Channel_Switch_PUCK(INT32U Mode);
void Init_Channel_Sram(void);
void Channel_Data_Proc_PUCK(INT32U Status);
void Init_All_Channel(void);
#endif
