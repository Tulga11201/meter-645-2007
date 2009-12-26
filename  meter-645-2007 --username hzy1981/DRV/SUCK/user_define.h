/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for 78K0R/Kx3
**  16-Bit Single-Chip Microcontrollers
**
**  Copyright(C) NEC Electronics Corporation 2002 - 2008
**  All rights reserved by NEC Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  NEC Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	user_define.h
**  Abstract :	This file includes user define.
**  APIlib :	Applilet2 for 78K0R/Kx3 V2.30 [18 Oct. 2007]
**
**  Device :	uPD78F1166_A0
**
**  Compiler :	IAR_C
**
**  Creation date:	2008-6-10
**  
*******************************************************************************
*/
#ifndef _MDUSER_DEF_
#define _MDUSER_DEF_

#include "macrodriver.h"
#include "port.h"
#include "data_flash.h"
#include "macrodriver.h"
#include "Port.h"
#include "Serial.h"
#include "TAU.h"
#include "Int.h"
#include "RTC.h"
#include "WatchdogTimer.h"
#include "System.h"
#include "Int.h"

/*

*******************************************************************************
**  Macro define
*******************************************************************************
*/
/* Start user code for definition. Do not edit comment generated here */
#define SUCESS 0;


#define  PORT_OUT_DIR 0
#define  PORT_IN_DIR  1


//-----------------------------------------------------------//        
#define DOWN_COVER_STATUS       (P0_bit.no0)        //���˸�(��˸�)Ǧ��
#define UP_COVER_STATUS         (P0_bit.no1)        //�����(�϶˸�)

#define EN_CARRIER_SET_ADDR     do{PM0_bit.no4=0; P0_bit.no4=0;}while(0)
#define DIS_CARRIER_SET_ADDR    do{PM0_bit.no4=0; P0_bit.no4=1;}while(0)

#define BAK_POWER_FOR_MEM        PORT_ChangeP05Output(1)           //�ڿ���Դ�ɵ͹��ĵ�ع���;
#define MAIN_POWER_FOR_MEM       PORT_ChangeP05Output(0)           //�ڿ���Դ������Դ����;
/*
P02/SO10/TXD1	                TXD-GPRS	GPRS���
P03/SI10/RXD1/SDA10	        RXD-GPRS	GPRS����
P04/SCK10/SCL10	EVENT-GPRS	GPRS�¼����
P06/\WAIT	16-SDA	24C16������
*/

//-----------------------------------------------------------// 
#define IRDA_SEND_EN            PORT_ChangeP10Output(1) 
#define IRDA_SEND_DIS           PORT_ChangeP10Output(0)

#if PREPAID_METER>0       //Ԥ���ѱ�
  #define B_2_485_0               
  #define B_2_485_1               
#else                     //��Ԥ���ѱ��˿���Ϊ485�л���
  #define B_2_485_0               PORT_ChangeP15Output(0)
  #define B_2_485_1               PORT_ChangeP15Output(1)
#endif

/*
P11/EX25/SI00/RXD0	RXD1	�������
P12/EX26/SO00/TXD0	TXD1	���ⷢ��
P13/EX27/TXD3	TXD2	�ڶ�·485����
P14/EX28/RXD3	RXD2	�ڶ�·485����
P16/EX30/TIO1/TO01/INTP5	RXD1	�������
P17/EX31/TI02/TO02	PWM	�������
*/
//-----------------------------------------------------------// 


#define B_7022_RST_0              PORT_ChangeP20Output(0)//RST         
#define B_7022_RST_1              PORT_ChangeP20Output(1) 
#define B_7022_SIG_STATUS         (P2_bit.no1)//SIG
#define B_7022_SDO_0              PORT_ChangeP22Output(0)//SDO     
#define B_7022_SDO_1              PORT_ChangeP22Output(1)//SDO     
#define B_7022_SDI_STATUS         (P2_bit.no3)//SDI
#define B_7022_SCK_0              PORT_ChangeP24Output(0)      //����������������
#define B_7022_SCK_1              PORT_ChangeP24Output(1)      //����������������
#define OPEN_MEASU_PWR            PORT_ChangeP25Output(1)      //����оƬ��Դ����
#define CLOSE_MEASU_PWR           PORT_ChangeP25Output(0)     //����оƬ��Դ�ر�
/*
P26/ANI6	RTC1_SDA	3231����
P27/ANI7	RTC1_SCL	3231ʱ��
*/

//-----------------------------------------------------------// 
#define JUDGE_POWER_OFF           (P3_bit.no1 ==0)    //������״̬--------------PUCK���ӣ�08-10-10,����OK
/*
#define IC_CARD_FAIL              (P3_bit.no0)   //����
*/
//-----------------------------------------------------------// 

/*
P47/INTP2	45DB161_RDY	Flash�洢��׼���ź�
P46/INTP1/TI05/TO05	ALL_V_LOSS	ȫʧѹ�ź�
P45/SO01	45DB161_SI	Flash�洢����������
P44/SI01	45DB161_SO	Flash�洢���������
P43/SCK01	45DB161_SCK	Flash�洢��ʱ���ź�
P42/TI04/TO04	45DB161_/CS	Flash�洢��Ƭѡ�ź�
P41/TOOL1	TOOL1	
P40/TOOL0	TOOL0
*/

//-----------------------------------------------------------// 
#define B_WTD_0                   P5_bit.no4=0   //OUT WTD  
#define B_WTD_1                   P5_bit.no4=1   //OUT WTD 
#define GUMB_STATUS               (P5_bit.no5)   //�ɻʹ�---K1
#define B_TEST_HARD_STATUS        (P5_bit.no6)   //�Լ�---K2
#define B_TEST_FAC_STATUS         (P5_bit.no7)      //����״̬-----------PUCK
/*
#define IC_CARD_IN                (P5_bit.no0)   //����
#define IC_CARD_OUT_0             P5_bit.no1=0   //���
#define IC_CARD_OUT_1             P5_bit.no1=1   //���
#define IC_CARD_RST_0             P5_bit.no2=0   //���
#define IC_CARD_RST_1             P5_bit.no2=1   //���
#define IC_CARD_SW                (P5_bit.no3)   //����
*/
//-----------------------------------------------------------// 
#define A_DIR_1                   PORT_ChangeP64Output(1)  //�й��������
#define A_DIR_0                   PORT_ChangeP64Output(0)
#define R_DIR_1                   PORT_ChangeP65Output(1)  //�޹��������
#define R_DIR_0                   PORT_ChangeP65Output(0)
#define A_OUT_1                   P6_bit.no6=1          //�й����
#define A_OUT_0                   P6_bit.no6=0
#define R_OUT_1                   P6_bit.no7=1   //�޹����  
#define R_OUT_0                   P6_bit.no7=0
/*
#define IC_CARD_POWR_ON           P6_bit.no3=1   //���
#define IC_CARD_POWR_OFF          P6_bit.no3=0   //���
P60/SCL0	MEM_SCL	�ڿ�I2C����ʱ����
P61/SDA0	MEM_SDA	�ڿ�I2C����������
*/

//-----------------------------------------------------------// 
#define CLR_DEMAND_KEY_STATUS     (P7_bit.no1)    //��������ť
#define Inter_Left_Key_STATUS     (P7_bit.no2)

#define LARGE_TOOGLE_ON_SET      do{PM7_bit.no1=0; P7_bit.no1=1;}while(0)     //�����̵������� P7_bit.no1: 1 0 1
#define LARGE_TOOGLE_ON_CLR      do{PM7_bit.no1=0; P7_bit.no1=0;}while(0)     //

#define LARGE_TOOGLE_OFF_SET      do{PM7_bit.no2=0; P7_bit.no2=1;}while(0)     //
#define LARGE_TOOGLE_OFF_CLR      do{PM7_bit.no2=0; P7_bit.no2=0;}while(0)     //���ռ̵����ر� P7_bit.no2: 1 0 1




#define Inter_Left_Key_STATUS     (P7_bit.no2)

#define Inter_Up_Key_STATUS       (P7_bit.no3)
#define Inter_Down_Key_STATUS     (P7_bit.no4)
#define Inter_Right_Key_STATUS    (P7_bit.no5)
#define B_PRG_KEY_STATUS          (P7_bit.no6)         //��̿���
#define LEAD_COVER_STATUS         1     //(P0_bit.no0)  //��Ǧ��

/*
P70/EX16/KR0	16-SCL	24C16ʱ����
P77/EX23/KR7/INTP11	IRD_WKP	���⻽��
*/
//-----------------------------------------------------------// 

//��բ
#define EXT_SWITCH_CLR            PORT_ChangeP80Output(0) //��բ����    
#define EXT_SWITCH_SET            PORT_ChangeP80Output(1)
#define EXT_ALARM_CLR             PORT_ChangeP81Output(0)     //�����ű���
#define EXT_ALARM_SET             PORT_ChangeP81Output(1)
#define EXT_SECOUT_CLR            PORT_ChangeP82Output(0)     //������ʹ��
#define EXT_SECOUT_SET            PORT_ChangeP82Output(1)
#define EXT_DEMAND_CLR            PORT_ChangeP83Output(0)    //��������
#define EXT_DEMAND_SET            PORT_ChangeP83Output(1)
#define EXT_PARSE_CLR             PORT_ChangeP84Output(0)     //ʱ���л�
#define EXT_PARSE_SET             PORT_ChangeP84Output(1)
#define LOWCOST_BAT_LOW           (P8_bit.no5)//�͹��ĵ��
#define BAK_POWER_FOR_IRDA        PORT_ChangeP86Output(1)        //Զ�����Դ�ɵ͹��ĵ�ع���;
#define MAIN_POWER_FOR_IRDA       PORT_ChangeP86Output(0)       //Զ�����Դ������Դ����;

/*
P82/EX2	SECOND_/EN	������ʹ��
#define IC_CARD_CLK_0             P8_bit.no7=0  //���
#define IC_CARD_CLK_1             P8_bit.no7=1  //���
*/

//-----------------------------------------------------------// 
#define IRDA_FAR_REC_EN           PORT_ChangeP110Output(0) 
#define IRDA_NEAR_REC_EN          PORT_ChangeP110Output(1)
#define RTC_BAT_LOW               (P11_bit.no1)//ʱ�ӵ�ص�



//-----------------------------------------------------------// 
#define B_7022_CS_0               PORT_ChangeP130Output(0)//CS         
#define B_7022_CS_1               PORT_ChangeP130Output(1) 
#define LED_TOGGLE_CLR            P13_bit.no1=0   //PORT_ChangeP131Output(0)//��բָʾ      
#define LED_TOGGLE_SET            P13_bit.no1=1   //PORT_ChangeP131Output(1) 

//-----------------------------------------------------------// 
#define B_1_485_0                 PORT_ChangeP145Output( 0 )//ѡ��  
#define B_1_485_1                 PORT_ChangeP145Output( 1 ) 
#define ALL_V_LOSS_STATUS         (P14_bit.no1)  //ȫʧѹ�µ�IO��״̬��ѯ,����OK

//-----------------------------------------------------------//
//�й����� LED �����
#define MEASU_A_LED_0             P15_bit.no0=0  
#define MEASU_A_LED_1             P15_bit.no0=1
//�޹����� LED �������
#define MEASU_R_LED_0             P15_bit.no1=0     //�޹�����ָʾ
#define MEASU_R_LED_1             P15_bit.no1=1  

#define LCD_BACK_LIGHT_0          PORT_ChangeP152Output( 0 )//Һ������        
#define LCD_BACK_LIGHT_1          PORT_ChangeP152Output( 1 ) 
         
#define LCD_CS_0                  PORT_ChangeP153Output( 0 )//Һ����CS         
#define LCD_CS_1                  PORT_ChangeP153Output( 1 ) 

#define BAK_POWER_FOR_LCD         P15_bit.no4=1          //LCD��Դ�ɵ͹��ĵ�ع���;
#define MAIN_POWER_FOR_LCD        P15_bit.no4=0          //LCD��Դ������Դ����;
         
#define LCD_DATA_0                PORT_ChangeP155Output( 0 )//Һ����DATA         
#define LCD_DATA_1                PORT_ChangeP155Output( 1 ) 
         
#define LCD_WR_0                  PORT_ChangeP156Output( 0 )//Һ����WR         
#define LCD_WR_1                  PORT_ChangeP156Output( 1 ) 


//LED����ָʾ��
#define LED_ALARM_CLR        P15_bit.no7=0   //������    
#define LED_ALARM_SET        P15_bit.no7=1    




#ifndef USER_DEFINE_C
#define USER_EXT extern volatile
#else
#define USER_EXT volatile
#endif



#define UART0_RX_BUFF_MAXSIZE 80
USER_EXT INT16U Uart0_Rx_Count; //��ǰ�����յ������ݳ���----PUCK
USER_EXT INT8U Uart0_RecBuf[UART0_RX_BUFF_MAXSIZE];

#ifdef UART1
  #define UART1_RX_BUFF_MAXSIZE 100
  USER_EXT INT16U Uart1_Rx_Count; //��ǰ�����յ������ݳ���----PUCK
  USER_EXT INT8U Uart1_RecBuf[UART1_RX_BUFF_MAXSIZE];
#endif
  
#define UART2_RX_BUFF_MAXSIZE 160
USER_EXT INT16U Uart2_Rx_Count;   //��ǰ�����յ������ݳ���----PUCK
USER_EXT INT8U Uart2_RecBuf[UART2_RX_BUFF_MAXSIZE];

#define UART3_RX_BUFF_MAXSIZE 270
USER_EXT INT16U Uart3_Rx_Count;  //��ǰ�����յ������ݳ���----PUCK
USER_EXT INT8U Uart3_RecBuf[UART3_RX_BUFF_MAXSIZE];


void UART0_Init_PUCK(ULONG baud_rate,INT16U CheckBit);
INT8U UART0_RecData_pre_PUCK(void);
INT8U UART0_SendData_PUCK(UCHAR* txbuf, USHORT txnum);

void UART1_Init_PUCK(ULONG baud_rate,INT16U CheckBit);
INT8U UART1_SendData_PUCK(UCHAR* txbuf, USHORT txnum);
INT8U UART1_RecData_pre_PUCK(void);


void UART2_Init_PUCK(ULONG baud_rate,INT16U CheckBit);
INT8U UART2_SendData_PUCK(UCHAR* txbuf, USHORT txnum);
INT8U UART2_RecData_pre_PUCK(void);


void UART3_Init_PUCK(ULONG baud_rate,INT16U CheckBit);
INT8U UART3_SendData_PUCK(UCHAR* txbuf, USHORT txnum);
INT8U UART3_RecData_pre_PUCK(void);



//#define START_IR_DECODE  TAU_Channel1_Start()
//#define STOP_IR_DECODE   TAU_Channel1_Stop()

#define START_PMW       TAU_Channel2_Start()
#define STOP_PMW        TAU_Channel2_Stop()

#define START_ALL_LOSS  TAU_Channel5_Start()
#define STOP_ALL_LOSS   TAU_Channel5_Stop()

#define START_TIMER_10uS    {TAU_Channel6_Stop();Set_Fast_Timer(RUN_MODE);TAU_Channel6_Start();}
#define START_TIMER_1mS  {TAU_Channel6_Stop();Set_Fast_Timer(FXT_RUN_MODE);TAU_Channel6_Start();}

#define STOP_FAST_TIMER        TAU_Channel6_Stop()

#define START_1MS TAU_Channel7_Start()
#define STOP_1MS  TAU_Channel7_Stop()

#define START_RTC_COUNTER RTC_CounterEnable()
#define STOPT_RTC_COUNTER RTC_CounterDisable()

#define START_SEC_ALARM RTC_ConstPeriodInterruptEnable(ONESEC)
#define START_MIN_ALARM RTC_ConstPeriodInterruptEnable(ONEMIN)
#define STOP_RTC_ALARM  RTC_ConstPeriodInterruptDisable()




void hdwinit(INT32U Mode);
void count_1ms(void);
MD_STATUS CG_ChangeClockMode( enum ClockMode mode );
/* End user code for definition. Do not edit comment generated here */
#endif
