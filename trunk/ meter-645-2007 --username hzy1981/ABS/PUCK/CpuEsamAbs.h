#ifndef CPU_ESAM_ABS_H
#define CPU_ESAM_ABS_H

#ifndef CPU_ESAM_ABS_C
#define CPU_ESAM_ABS_EXT extern volatile
#else
#define CPU_ESAM_ABS_EXT volatile
#endif



//�жϵ�ǰ�����ǲ��Ƕ� CPU/ESAM�Ĳ���
#define IS_CPU_ESAM_CPU_ESAM_DRV(a) ((a==PAY_CPU_CARD) ||(a==PAY_ESAM))

//�жϵ�ǰCPU���Ƿ��Ѿ�����:1------����;0----------û�в���
#define JUDGE_CPU_INSERT   (CPU_CARD_INSERT==1)
#define JUDGE_CPU_OUTPUT   (CPU_CARD_INSERT==0)




//��ǰ������Ԥ���ѽ�������
#define PAY_NONE         0 
#define PAY_CPU_CARD     1
#define PAY_ESAM         2
#define PAY_CARRIER      3
#define PAY_FAR          4

#define MAX_CPU_ESAM_TYPE PAY_ESAM    
    
//��ǰ������Ԥ���ѽ��ʵ���������
#define CPU_ESAM_DRV_NONE          0  //�޲���
#define CPU_ESAM_DRV_RST_COOL      1  //�临λ
#define CPU_ESAM_DRV_RST_HOT       2  //�ȸ�λ
#define CPU_ESAM_DRV_POWER_ON      3  //�ϵ�
#define CPU_ESAM_DRV_POWER_OFF     4  //����

//CPU ESAM������������
#define CPU_ESAM_DRV_OK               0x00               //�޴���
#define CPU_ESAM_DRV_FUZZY_ERR        0x01               //δ֪���߷Ƿ��Ĳ�������
#define CPU_ESAM_DRV_LOSS_ERR         0x02               //�޿�,�����ڴ˿�
#define CPU_ESAM_DRV_OUT_ERR          0x03               //��ǰ�ο�
#define CPU_ESAM_DRV_RST_ERR          0x04               //��λ��
#define CPU_ESAM_DRV_RECLEN_ERR       0x05               //�������ݳ��ȴ�
#define CPU_ESAM_DRV_DATA_ERR         0x06               //�����������ݴ�



#define PAY_UART            CHANEL_485_2
#define Pay_Uart_Rec_Len    Uart3_Rx_Count
#define Pay_Uart_Rec_Buf    Uart3_RecBuf
#define Uart_Pay_Ready      UART3_RecData_pre_PUCK

#define WRITE_CPU_ESAM      0
#define READ_CPU_ESAM       1

typedef struct
{
  INT8U Uart_Type;               //��ǰ�����Ĵ�������:PAY_NONE,PAY_CPU_CARD,PAY_ESAM
  INT8U Media_Type;              //��ǰ��������:PAY_NONE,PAY_CPU_CARD
  INT8U CS[CS_BYTES];            //У���
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


//���ܣ������л���CPU��/ESAM
#define Switch_Uart_To_Pay(Type) do{ PM5_bit.no1=0; \
                                     if(Type EQ PAY_CPU_CARD) P5_bit.no1=1; \
                                     if(Type EQ PAY_ESAM)     P5_bit.no1=0; \
                                   }while(0)


//���ܣ�����CPU/ESAM��ʱ��
#define Reset_Pay_Timer(Sec_Time) do{Pay_Sec_Timer.Var=Sec_Timer_Pub;\
                                    Want_Pay_Sec_Time.Var=Sec_Time; \
                                    Pay_Ms_Timer.Var=Pub_Timer.Ms_Timer;\
                                    }while(0)

//���ܣ���ѯ�Ƿ��Ѿ���ʱ��1---------ʱ���Ѿ������� Reset_Pay_Timer()�й涨��ʱ�䣻0------------ʱ��û�е�
#define Chk_Pay_Time_Arrive() ((Sec_Timer_Pub-Pay_Sec_Timer.Var>=Want_Pay_Sec_Time.Var)?1:0)
                                      

//���ܣ���ѯ��ʱ�����˶೤����
#define Get_Pay_Ms_Time() (Pub_Timer.Ms_Timer-Pay_Ms_Timer.Var)                                    

INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
INT8U Cpu_Esam_Comm_Proc(INT8U Type,INT8U *Srcbuf,INT16U SrcLen,INT8U RdOrWr,INT8U RdDstLen,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
void CPU_Card_Main_Proc(void);
#endif
