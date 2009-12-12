#ifndef HAL_H
#define HAL_H

#undef EXT
#ifdef HAL_C
#define EXT
#else
#define EXT extern
#endif

#define ROM0_SIZE 512L
#define ROM1_SIZE 32*1024L
#define ROM2_SIZE 32*1024L
#define ROM3_SIZE 32*1024L
#define ROM4_SIZE 8*1024L
#define ROM5_SIZE 2000*1024L

#define DEBUG_FILE_NAME "D:\\Debug_Info.txt"
EXT FILE *pDebug_File;

/////////////stub//////////////

#define CHANEL_IRDA     0           //����ͨ������---------UART0
#define CHANEL_485_1    1           //485ͨ������---------UART2
#define CHANEL_485_2    2           //485ͨ������---------UART3
#define CHANEL_MOUDEL   3

#define ID_EVENT_CLR_VOLT_PASS 0           //ģ��ͨ������---------UART1
#define ID_EVENT_CLR_PROCESS   1
#define ID_EVENT_CLR_ALL_DATA  2
#define ID_EVENT_CLR_DEMAND_COM 3

#define EXT_RTC_OK 1
#define MODE_FAC 0
#define MODE_RUN 1

#define NO_QUADRANT   0             //��Ч����
#define QUADRANT1     (NO_QUADRANT+1)
#define QUADRANT2     (QUADRANT1+1)
#define QUADRANT3     (QUADRANT2+1)
#define QUADRANT4     (QUADRANT3+1)

#define POWER_OFF_STATUS 1

//#define Set_Event_Instant(x)
#define DIS_PD_INT
#define EN_PD_INT
#define PARSE_341 0
#define Get_SysParse_Mode() 0
#define Check_Prog_Status() 1
#define Check_MeterAddr_Status() 1
#define Set_Soft_RTC_PUCK(x)
#define Read_Ext_RTC_Status() EXT_RTC_OK
#define Get_Soft_RTC_PUCK(x,y) 1
#define Init_DebugChanel_PUCK(X)
#define Print_Reset_Source()
#define Get_Meter_Hard_Mode() MODE_FAC
//#define Get_Measu_AcculateData_PUCK
#define Soft_Reset() 
#define PwrCtrl_ExtDevice_HigSpeed()
#define Init_CPU_PUCK(X)
#define Init_ExtDevice_PUCK(X)
#define Clear_Event_Data()
#define Clear_Data_End()
#define Clr_Screen_PUCK()  //�ϵ��ǿ����LCD��ʾ
#define Test_HardWare_PUCK()
#define Init_Measure_Ram()
//#define PowerOn_Event_Proc()//�ϵ���ǰһ�ε���ǰ���¼�����
#define Init_Measu_PUCK()  //��ʼ����������Һ��������ʾ�����¼��ж�  
#define LCD_Init_PUCK()   //LCD��ʾ��ʼ���������ٶ���Ҫ

#define Set_Event_Instant(X)
#define Clr_Event_Instant(X)

#define Check_Event_Occuring(X) 0
#define Get_Buf_MulitByte_Sum(a,b,c,d,e)
//#define Clear_VolStat_Data()
///////////////////////////////

typedef struct
{
	INT8U A_LossV:1;            //A��ʧѹ
	INT8U B_LossV:1;            //B��ʧѹ
	INT8U C_LossV:1;            //C��ʧѹ
	INT8U V_SeqErr:1;           //��ѹ�����
	INT8U I_SeqErr:1;           //���������
	INT8U A_Creep:1;            //AǱ��
	INT8U B_Creep:1;            //BǱ��
	INT8U C_Creep:1;            //CǱ��
	
	INT8U A_APwrDir:1;        //A�й����ʷ���0������1����
	INT8U B_APwrDir:1;        //B�й����ʷ���0������1����
	INT8U C_APwrDir:1;        //C�й����ʷ���0������1����
	INT8U SUM_APwrDir:1;      //�����й����ʷ���0������1����  
	INT8U A_RPwrDir:1;        //A�޹����ʷ���0������1����
	INT8U B_RPwrDir:1;        //B�޹����ʷ���0������1����
	INT8U C_RPwrDir:1;        //C�޹����ʷ���0������1����  
	INT8U SUM_RPwrDir:1;      //�����޹����ʷ���0������1���� 
	
	INT8U MeasuIntOk:1;       //����оƬ��ʼ�����
	INT8U PulseEn:1;          //�������ʹ��
	INT8U DataRecFlg:1;       //1�����յ��������ݱ�־��Ӧ�ò��ȡ���ݣ�0-----��û��׼���ü������ݣ���Ҫȡ
	INT8U Reserved:5;
	//����8bits���� 
	INT8U CS[CS_BYTES];
}MEASU_STATUS;              //����״̬��

typedef struct
{  
	INT32U A;
	INT32U B;
	INT32U C;
	INT32U Sum;
}MEASU_DATA;       //MeasuIC˲ʱ����������

typedef struct
{  
	INT8U A;
	INT8U B;
	INT8U C;
	INT8U Sum;
}MEASUFLAG;       //MeasuIC˲ʱ��״̬����

typedef struct
{
	MEASU_DATA AcPower;       //�й�����:UNIT:0.000001kW
	MEASU_DATA ReacPower;     //�޹�����:UNIT:0.000001kvar
	MEASU_DATA AppPower;      //���ڹ���:UNIT:0.000001kva
	MEASU_DATA Volt;          //��ѹ��Чֵ���޺��� UNIT:0.0001V
	MEASU_DATA Curr;          //������Чֵ: UNIT:0.0001A	
	MEASU_DATA PFactor;       //��������: UNIT:0.000001
	MEASU_DATA Freq;          //Ƶ��:UNIT:0.000001Hz
	MEASUFLAG  Quadrant;      //�������ޣ�QUADRANT1��QUADRANT4����1��4���ޡ�
	MEASU_DATA Angle;         //��ѹ�����нǣ�UINT:0.01��
	INT32U     Temprate;      //�¶�
	INT8U CS[CS_BYTES];
}MEASU_INSTANT;   //MeasuIC˲ʱ����������


typedef struct
{
	INT32U Chang_Plus_AcEnerg[4];            //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
	INT32U Chang_Nega_AcEnerg[4];            //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
	
	//INT32U Chang_Plus_ReacEnerg[4];          //A/B/C/SUM��Ԫ�������޹�����(�޹����1):��λ:0.01warh  
	//INT32U Chang_Nega_ReacEnerg[4];          //A/B/C/SUM��Ԫ�������޹�����(�޹����2):��λ:0.01warh
	
	INT32U Chang_Quad_ReacEnerg[4][4];       //A/B/C/SUM��Ԫ���������޹�����,Chang_Quad_ReacEnerg[1][2]��ʾB��3�����޹�
	
	INT32U Add_AmpaHour[3];                 //AH�ۼ�:0.0001As,�ۼ���
	INT32U Add_CopperLoss[4];		  //A,B,C,sumͭ��,��λΪ0.0000001kA2s,�ۼ���
	INT32U Add_IronLoss[4];		  //A,B,C,sum����,��λΪ0.0000001KV2s���ۼ���
	INT32U Add_GenaralErr[4];		  //A,B,C,sum�ϳ����,��λ:0.01*tgFA*s,�ۼ���
	INT8U CS[CS_BYTES];
}MEASU_ENERG;                             //�����ۼ����ݺ���������


EXT volatile MEASU_STATUS      Measu_Status_Mode_ToPub_PUCK;   //��������״̬��(�Ѱ���331/341����)

EXT volatile MEASU_INSTANT    Measu_InstantData_ToPub_PUCK;    //����˲ʱ����
EXT volatile MEASU_ENERG       Measu_Energ_ToPub_PUCK;       //�����ۼ�������

EXT INT8U Temp_Buf[1000];

EXT void Put_Char(OS_INT8U Chr);
EXT INT8U Debug_Out_Public_Puck(OS_INT8U *Srcbuf,OS_INT16U Src_Len);
EXT void Clear_CPU_Dog();    //��CPU�ڲ����Ź�
EXT void  Clear_Ext_Dog();    //��CPU�ⲿ���Ź�

EXT INT8U Check_Meter_Factory_Status();
EXT INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen);
EXT INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen);

EXT INT8U Read_ExtRTC_PUCK(INT8U Dst[],INT8U Len);
EXT INT8U Write_ExtRTC_PUCK(INT8U Src[]);
EXT INT8U Read_InterRTC_PUCK(INT8U Dst[],INT8U Len);
EXT INT8U Write_InterRTC_PUCK(INT8U Src[]);
EXT INT8U Check_Protocol_Data_Storage();
EXT void Check_Data_Avail();
EXT INT16U Get_Measu_AcculateData_PUCK(INT8U ID,void *DstReal,void *Dst_Start,INT16U DstLen,INT16U DstMaxLen);
EXT void HAL_Init();
EXT void count_1ms(void);
EXT INT8U Check_Event_End(INT8U Event_ID);
#endif
