#ifndef EVENTINSTANT_VAR
#define EVENTINSTANT_VAR


#ifndef EVENTINSTANT_C
#define EVENTINSTANT_C_EXT  extern volatile
#else
#define EVENTINSTANT_C_EXT volatile
#endif


#define    SEQ_ERR_CHK_GRID   Mode_Word.Mode[3].Bit.Bit6   //������������״̬��0-----��飻1-----�����
#define    ALL_LOSS_CURR_VALUE          0.02   //ȫʧ����ֵ��0.02*In
#define    VOLT_LESS_PER                0.7   //Ƿѹϵ��

#define   PRG_KEY_TIME  240  //��̰�ťά��ʱ��


#define  DI_LOSSVOLT_U_UP     	  0X04090101      //ʧѹ�¼���ѹ��������
#define  DI_LOSSVOLT_U_DOWN   	  0X04090102      //ʧѹ�¼���ѹ�ָ�����
#define  DI_LOSSVOLT_I_DOWN   	  0X04090103      //ʧѹ�¼������������� 
#define  DI_LOSSVOLT_TIME     	  0X04090104      //ʧѹ�¼��ж���ʱʱ�� 
  
#define  DI_DOWNVOLT_U_UP    	  0X04090201      //Ƿѹ�¼���ѹ��������
#define  DI_DOWNVOLT_TIME    	  0X04090202      //Ƿѹ�¼��ж���ʱʱ�� 
  
#define  DI_UPVOLT_U_DOWN         0X04090301      //��ѹ�¼���ѹ��������
#define  DI_UPVOLT_U_TIME         0X04090302      //��ѹ�¼��ж���ʱʱ�� 
  
#define  DI_CUTPARSE_U_UP         0X04090401      //�����¼���ѹ��������
#define  DI_CUTPARSE_I_UP         0X04090402      //�����¼������������� 
#define  DI_CUTPARSE_TIME         0X04090403     //�����¼��ж���ʱʱ�� 
  
#define  DI_VOLT_NOEVEN_UP        0X04090501     //��ѹ��ƽ������ֵ  
#define  DI_VOLT_NOEVEN_TIME      0X04090502     //��ѹ��ƽ�����ж���ʱʱ�� 
  
#define  DI_CURR_NOEVEN_UP        0X04090601     //������ƽ������ֵ  
#define  DI_CURR_NOEVEN_TIME      0X04090602     //������ƽ�����ж���ʱʱ�� 

  
#define  DI_LOSSCURR_U_DOWN       0X04090701    //ʧ���¼���ѹ��������
#define  DI_LOSSCURR_I_UP         0X04090702    //ʧ���¼������������� 
#define  DI_LOSSCURR_I_DOWN       0X04090703     //ʧ���¼������������� 
#define  DI_LOSSCURR_TIME         0X04090704     //ʧ���¼��ж���ʱʱ�� 
  
#define  DI_UPCURR_I_DOWN         0X04090801    //�����¼�������������
#define  DI_UPCURR_TIME           0X04090802    //�����¼��ж���ʱʱ�� 
  
  
#define  DI_CUTCURRE_U_DOWN       0X04090901    //�����¼���ѹ��������
#define  DI_CUTCURR_I_UP          0X04090902    //�����¼������������� 
#define  DI_CUTCURR_TIME          0X04090903    //�����¼��ж���ʱʱ�� 
  
#define  DI_NEGCURR_ACPOW_DOWN    0X04090A01    //���������¼��й����ʴ�������
#define  DI_NEGCURR_TIME          0X04090A02    //���������¼��ж���ʱʱ�� 
  
#define  DI_OVERLOAD_ACPOW_DOWN   0X04090B01    //�����¼��й����ʴ�������
#define  DI_OVERLOAD_TIME         0X04090B02     //�����¼��ж���ʱʱ�� 
  
  
#define  DI_OVERDE_ACPOW_DOWN     0X04090D01     //�й����������¼�������������
#define  DI_OVERDE_ACPOW_UP       0X04090D02      //�޹����������¼������������� 
#define  DI_OVERDE_TIME           0X04090D03      //���������¼��ж���ʱʱ�� 

#define  DI_DOWNPF_I_DOWN         0X04090E01     //�ܹ������������޷�ֵ  
#define  DI_DOWNPF_TIME           0X04090E02     //�ܹ��������������ж���ʱʱ��
  
#define  DI_CURR_NO1EVEN_I_UP     0X04090F01     //�������ز�ƽ����ֵ  
#define  DI_CURR_NO1EVEN_TIME     0X04090F02     //�������ز�ƽ�ⴥ����ʱʱ�� 

#define JUDGE_IS_EVENT_PARA(a)  ((a>=DI_LOSSVOLT_U_UP) && (a<=DI_CURR_NO1EVEN_TIME))



#define  DI_START_VOLT        0x0E000108          //�ٽ��ѹ:1�ֽ�



//ȫʧ����ֵ�����ʧ��������ֵС
typedef struct{
/* 
  FP32S  LossVolt_Per;         //ʧѹ��ѹ��ֵ,%-----DI_LOSS_VOLT_START_VOLT,ȡֵ���100:0.0~1.0��Ĭ�ϣ�0.78
  FP32S  LossVolt_I;           //ʧѹ�����ж�ֵ:A��------DI_LOSS_VOLT_START_IĬ�ϣ�0.1
  
  FP32S  LossCurr_Start_I;      //ʧ����������: ---------------DI_LOSS_CURR_START_I,NN.NNNN
  FP32S  LossCurr_End_I;       //ʧ����������: ---------------DI_LOSS_CURR_END_I,NN.NNNN
  
  FP32S  SartVolt_Per;        //�ٽ��ѹ,%-----DI_START_VOLT,ȡֵ���100:0.0~1.0��Ĭ�ϣ�0.60
  
  FP32S  OverVolt_Per;        //��ѹ�жϷ�ֵ,%-----DI_OVER_VOLT��2�ֽ�
  FP32S  OverCur_Per;        //�����жϷ�ֵ,%-----DI_OVER_CURR��2�ֽ�
  
  FP32S  CurNoEvenUp_Per;        //������ƽ������,DI_CURR_NOTEVEN_UP NNNN.NN %
  FP32S  VoltNoEvenUp_Per;        //��ѹ��ƽ������,DI_VOLT_NOTEVEN_UP NNNN.NN %
*/
  //---------------------------------------------------------
  INT16U  LossVolt_U_Up;       //ʧѹ�¼���ѹ��������
  INT16U  LossVolt_U_Down;     //ʧѹ�¼���ѹ�ָ�����
  INT32U  LossVolt_I_Down;     //ʧѹ�¼������������� 
  INT8U   LossVolt_Time;       //ʧѹ�¼��ж���ʱʱ�� 
  
  INT16U  DownVolt_U_Up;       //Ƿѹ�¼���ѹ��������
  INT8U   DownVolt_Time;      //Ƿѹ�¼��ж���ʱʱ�� 
  
  INT16U  UpVolt_U_Down;       //��ѹ�¼���ѹ��������
  INT8U   UpwnVolt_Time;      //��ѹ�¼��ж���ʱʱ�� 
  
  INT16U  CutParse_U_Up;       //�����¼���ѹ��������
  INT32U  CutParse_I_Up;       //�����¼������������� 
  INT8U   CutParse_Time;       //�����¼��ж���ʱʱ�� 
  
  INT16U  Volt_NoEven_Up;       //��ѹ��ƽ������ֵ  
  INT8U   Volt_NoEven_Time;       //��ѹ��ƽ�����ж���ʱʱ�� 
  
  INT16U  Curr_NoEven_Up;       //������ƽ������ֵ  
  INT8U   Curr_NoEven_Time;       //������ƽ�����ж���ʱʱ�� 

  
  INT16U  LossCurr_U_Down;       //ʧ���¼���ѹ��������
  INT32U  LossCurr_I_Up;         //ʧ���¼������������� 
  INT32U  LossCurr_I_Down;     //ʧ���¼������������� 
  INT8U   LossCurr_Time;       //ʧ���¼��ж���ʱʱ�� 
  
  INT16U  UpCurr_I_Down;        //�����¼�������������
  INT8U   UpCurr_Time;       //�����¼��ж���ʱʱ�� 
  
  
  INT16U  CutCurre_U_Down;     //�����¼���ѹ��������
  INT32U  CutCurr_I_Up;       //�����¼������������� 
  INT8U  CutCurr_Time;       //�����¼��ж���ʱʱ�� 
  
  INT16U  NegCurr_Acpow_Down;       //���������¼��й����ʴ�������
  INT8U   NegCurr_Time;      //���������¼��ж���ʱʱ�� 
  
  INT32U OverLoad_AcPow_Down;       //�����¼��й����ʴ�������
  INT8U  OverLoad_Time;      //�����¼��ж���ʱʱ�� 
  
  
  INT32U  OverDe_Acpow_Down;       //�й����������¼�������������
  INT32U  OverDe_Reacpow_Down;        //�޹����������¼������������� 
  INT8U   OverDe_Time;       //���������¼��ж���ʱʱ�� 

  INT16U  DownPf_I_Down;       //�ܹ������������޷�ֵ  
  INT8U   DownPf_Time;          //�ܹ��������������ж���ʱʱ��
  
  INT16U  Curr_No1Even_I_Up;    //�������ز�ƽ����ֵ  
  INT8U   Curr_No1Even_Time;    //�������ز�ƽ�ⴥ����ʱʱ�� 
  
  
  INT8U   Start_Volt;          //�ٽ�
  
  
  INT8U CS[CS_BYTES];
}EventInsPara;         //�¼�����״̬

     


EVENTINSTANT_C_EXT EventInsPara EventInsParaVar;

#define  CLR_DEMD_KEY_PRESS 0x35
typedef struct{
  INT8U Status;            //���
  INT8U CS[CS_BYTES];
}KeyStatus;

EVENTINSTANT_C_EXT KeyStatus  Clr_Demand_Key;


/*
#define KEY_INIT_STATUS  0x35
typedef struct{
  INT8U Prg;            //���
  INT8U CS[CS_BYTES];
}KeyStatus;         //�¼�����״̬

EVENTINSTANT_C_EXT KeyStatus  KeyInitStatus;
*/

/*
#define MAX_CHANGE_SEC    8     //��λ�ж�ʱ��
typedef struct
{ 
  INT8U Head;
  INT8U OldStatus;           //��״̬
  INT8U NewStatus;           //��״̬
  INT8U Counts;             //������
  INT8U Tail;
}EVENT_CHANGE;
EVENTINSTANT_C_EXT volatile EVENT_CHANGE Loss_Volt_Change;
EVENTINSTANT_C_EXT volatile EVENT_CHANGE Loss_Curr_Change;
EVENTINSTANT_C_EXT volatile EVENT_CHANGE Curr_Neg_Change;
*/


//EVENTINSTANT_C_EXT S_Relay_Status Remote_Ctrl_Status;


INT8U Get_Event_Instant(INT8U Id);
void Check_Volt_Curr_Seq(void);
void  Check_Down_Up_Volt(void);
void  Check_Loss_Curr(void);
void  Check_Loss_Parse(void);
void Check_Loss_Volt(void);
void Check_RTCBat_Low(void);
void Check_LPWBat_Low(void);
void Check_Prg_Key(void);
void Check_Fac_Status(void);
void Init_Event_Instant_Para(void);
void Check_Neg_Curr(void);
void Check_UpCover(void);
void Check_DownCover(void);
void Check_AB_Func_Key(void);
void Check_MeterAddr_Key(void);
void Set_Cal_Event(void);
void Event_Para_Modi(void);
void Check_ClrDemand_Key(void);
void Get_Loss_Volt_Change(void);
void Get_Loss_Curr_Change(void);
void Get_Curr_Neg_Change(void);
void Monitor_Meter_System_Osc(void);
void Excute_Toogle(INT8U SwitchFlag);
void Init_Toggle_Status(void);
void Check_LeadCover(void);
INT8U Check_Demand_Key_Press(void);
void Check_Overload_Curr(void);
void Check_Volt_NoEven(void);
void Check_Curr_NoEven(void);
void Init_One_Event_Para(INT32U Data_DI);
void Check_Sum_Factor_Low(void);
void Check_Power_Exceed(void);
void Check_Cut_Curr(void);
void Check_Up_Curr(void);
void Check_Up_Volt(void);
void Check_Down_Volt(void);
void Check_Demand_Exceed(void);
void Check_Cur_Very_Noeven(void);
void Get_Meter_Instant_Status(void);
INT8U Get_Time_Diff(S_Event_Time Temp_PD_Time,INT32U *Diff);
void Get_Prog_Key_Time(void);
INT8U Check_Max_Volt_Below(FP32S BelowValue);
void Check_RelayOn_Key(void);
INT8U Judge_RelayOn_Key(void);
#endif