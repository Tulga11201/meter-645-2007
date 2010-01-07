#ifndef CPU_ESAM_ABS_H
#define CPU_ESAM_ABS_H

#ifndef CPU_ESAM_ABS_C
#define CPU_ESAM_ABS_EXT extern volatile
#else
#define CPU_ESAM_ABS_EXT volatile
#endif



//判断当前操作是不是对 CPU/ESAM的操作
#define IS_CPU_ESAM_CPU_ESAM_DRV(a) ((a==PAY_CPU_CARD) ||(a==PAY_ESAM))

//判断当前CPU卡是否已经插入:1------插入;0----------没有插入
#define JUDGE_CPU_INSERT   (CPU_CARD_INSERT==1)
#define JUDGE_CPU_OUTPUT   (CPU_CARD_INSERT==0)




//当前操作的预付费介质类型
#define PAY_NONE         0 
#define PAY_CPU_CARD     1
#define PAY_ESAM         2
#define PAY_CARRIER      3
#define PAY_FAR          4

#define MAX_CPU_ESAM_TYPE PAY_ESAM    
    
//当前操作的预付费介质的驱动动作
#define CPU_ESAM_DRV_NONE          0  //无操作
#define CPU_ESAM_DRV_RST_COOL      1  //冷复位
#define CPU_ESAM_DRV_RST_HOT       2  //热复位
#define CPU_ESAM_DRV_POWER_ON      3  //上电
#define CPU_ESAM_DRV_POWER_OFF     4  //掉电

//CPU ESAM驱动层错误代码
#define CPU_ESAM_DRV_OK               0x00               //无错误
#define CPU_ESAM_DRV_FUZZY_ERR        0x01               //未知或者非法的操作类型
#define CPU_ESAM_DRV_LOSS_ERR         0x02               //无卡,不存在此卡
#define CPU_ESAM_DRV_OUT_ERR          0x03               //提前拔卡
#define CPU_ESAM_DRV_RST_ERR          0x04               //复位错
#define CPU_ESAM_DRV_RECLEN_ERR       0x05               //接收数据长度错
#define CPU_ESAM_DRV_DATA_ERR         0x06               //接收数据内容错



#define PAY_UART            CHANEL_485_2
#define Pay_Uart_Rec_Len    Uart3_Rx_Count
#define Pay_Uart_Rec_Buf    Uart3_RecBuf
#define Uart_Pay_Ready      UART3_RecData_pre_PUCK

#define WRITE_CPU_ESAM      0
#define READ_CPU_ESAM       1

typedef struct
{
  INT8U Uart_Type;               //当前操作的串口类型:PAY_NONE,PAY_CPU_CARD,PAY_ESAM
  INT8U Media_Type;              //当前介质类型:PAY_NONE,PAY_CPU_CARD
  INT8U CS[CS_BYTES];            //校验和
}PAY_CPU_ESAM_DRV;
CPU_ESAM_ABS_EXT PAY_CPU_ESAM_DRV Curr_Media_Status;


#ifdef CPU_ESAM_ABS_C
CPU_ESAM_ABS_EXT S_Int32U Pay_Sec_Timer={CHK_BYTE,0x00,CHK_BYTE};
CPU_ESAM_ABS_EXT S_Int32U Pay_Ms_Timer={CHK_BYTE,0x00,CHK_BYTE};
CPU_ESAM_ABS_EXT S_Int32U Want_Pay_Sec_Time={CHK_BYTE,0x00,CHK_BYTE};
#endif
CPU_ESAM_ABS_EXT S_Int32U Pay_Sec_Timer;
CPU_ESAM_ABS_EXT S_Int32U Pay_Ms_Timer;
CPU_ESAM_ABS_EXT S_Int32U Want_Pay_Sec_Time;


//功能：串口切换到CPU卡/ESAM
#define Switch_Uart_To_Pay(Type) do{ PM5_bit.no1=0; \
                                     if(Type EQ PAY_CPU_CARD) P5_bit.no1=1; \
                                     if(Type EQ PAY_ESAM)     P5_bit.no1=0; \
                                   }while(0)


//功能：重置CPU/ESAM定时器
#define Reset_Pay_Timer(Sec_Time) do{Pay_Sec_Timer.Var=Sec_Timer_Pub;\
                                    Want_Pay_Sec_Time.Var=Sec_Time; \
                                    Pay_Ms_Timer.Var=Pub_Timer.Ms_Timer;\
                                    }while(0)

//功能：查询是否已经到时：1---------时间已经超过了 Reset_Pay_Timer()中规定的时间；0------------时间没有到
#define Chk_Pay_Time_Arrive() ((Sec_Timer_Pub-Pay_Sec_Timer.Var>=Want_Pay_Sec_Time.Var)?1:0)
                                      

//功能：查询定时后，走了多长毫秒
#define Get_Pay_Ms_Time() (Pub_Timer.Ms_Timer-Pay_Ms_Timer.Var)                                    

INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
INT8U Cpu_Esam_Comm_Proc(INT8U Type,INT8U *Srcbuf,INT16U SrcLen,INT8U RdOrWr,INT8U RdDstLen,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
void CPU_Card_Main_Proc(void);
#endif
