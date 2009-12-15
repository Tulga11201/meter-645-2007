#ifndef EVENTINSTANT_VAR
#define EVENTINSTANT_VAR


#ifndef EVENTINSTANT_C
#define EVENTINSTANT_C_EXT  extern volatile
#else
#define EVENTINSTANT_C_EXT volatile
#endif


#define    SEQ_ERR_CHK_GRID   Mode_Word.Mode[3].Bit.Bit6   //逆相序后检查电网状态；0-----检查；1-----不检查
#define    ALL_LOSS_CURR_VALUE          0.02   //全失流阀值：0.02*In
#define    VOLT_LESS_PER                0.7   //欠压系数

#define   PRG_KEY_TIME  240  //编程按钮维持时间


#define  DI_LOSSVOLT_U_UP     	  0X04090101      //失压事件电压触发上限
#define  DI_LOSSVOLT_U_DOWN   	  0X04090102      //失压事件电压恢复下限
#define  DI_LOSSVOLT_I_DOWN   	  0X04090103      //失压事件电流触发下限 
#define  DI_LOSSVOLT_TIME     	  0X04090104      //失压事件判定延时时间 
  
#define  DI_DOWNVOLT_U_UP    	  0X04090201      //欠压事件电压触发上限
#define  DI_DOWNVOLT_TIME    	  0X04090202      //欠压事件判定延时时间 
  
#define  DI_UPVOLT_U_DOWN         0X04090301      //过压事件电压触发下限
#define  DI_UPVOLT_U_TIME         0X04090302      //过压事件判定延时时间 
  
#define  DI_CUTPARSE_U_UP         0X04090401      //断相事件电压触发上限
#define  DI_CUTPARSE_I_UP         0X04090402      //断相事件电流触发上限 
#define  DI_CUTPARSE_TIME         0X04090403     //断相事件判定延时时间 
  
#define  DI_VOLT_NOEVEN_UP        0X04090501     //电压不平衡率限值  
#define  DI_VOLT_NOEVEN_TIME      0X04090502     //电压不平衡率判定延时时间 
  
#define  DI_CURR_NOEVEN_UP        0X04090601     //电流不平衡率限值  
#define  DI_CURR_NOEVEN_TIME      0X04090602     //电流不平衡率判定延时时间 

  
#define  DI_LOSSCURR_U_DOWN       0X04090701    //失流事件电压触发下限
#define  DI_LOSSCURR_I_UP         0X04090702    //失流事件电流触发上限 
#define  DI_LOSSCURR_I_DOWN       0X04090703     //失流事件电流触发下限 
#define  DI_LOSSCURR_TIME         0X04090704     //失流事件判定延时时间 
  
#define  DI_UPCURR_I_DOWN         0X04090801    //过流事件电流触发下限
#define  DI_UPCURR_TIME           0X04090802    //过流事件判定延时时间 
  
  
#define  DI_CUTCURRE_U_DOWN       0X04090901    //断流事件电压触发下限
#define  DI_CUTCURR_I_UP          0X04090902    //断流事件电流触发上限 
#define  DI_CUTCURR_TIME          0X04090903    //断流事件判定延时时间 
  
#define  DI_NEGCURR_ACPOW_DOWN    0X04090A01    //潮流反向事件有功功率触发下限
#define  DI_NEGCURR_TIME          0X04090A02    //潮流反向事件判定延时时间 
  
#define  DI_OVERLOAD_ACPOW_DOWN   0X04090B01    //过载事件有功功率触发下限
#define  DI_OVERLOAD_TIME         0X04090B02     //过载事件判定延时时间 
  
  
#define  DI_OVERDE_ACPOW_DOWN     0X04090D01     //有功需量超限事件需量触发下限
#define  DI_OVERDE_ACPOW_UP       0X04090D02      //无功需量超限事件需量触发下限 
#define  DI_OVERDE_TIME           0X04090D03      //需量超限事件判定延时时间 

#define  DI_DOWNPF_I_DOWN         0X04090E01     //总功率因数超下限阀值  
#define  DI_DOWNPF_TIME           0X04090E02     //总功率因数超下限判定延时时间
  
#define  DI_CURR_NO1EVEN_I_UP     0X04090F01     //电流严重不平衡限值  
#define  DI_CURR_NO1EVEN_TIME     0X04090F02     //电流严重不平衡触发延时时间 

#define JUDGE_IS_EVENT_PARA(a)  ((a>=DI_LOSSVOLT_U_UP) && (a<=DI_CURR_NO1EVEN_TIME))



#define  DI_START_VOLT        0x0E000108          //临界电压:1字节



//全失流阀值必须比失流电流阀值小
typedef struct{
/* 
  FP32S  LossVolt_Per;         //失压电压阀值,%-----DI_LOSS_VOLT_START_VOLT,取值后除100:0.0~1.0，默认：0.78
  FP32S  LossVolt_I;           //失压电流判定值:A，------DI_LOSS_VOLT_START_I默认：0.1
  
  FP32S  LossCurr_Start_I;      //失流启动电流: ---------------DI_LOSS_CURR_START_I,NN.NNNN
  FP32S  LossCurr_End_I;       //失流结束电流: ---------------DI_LOSS_CURR_END_I,NN.NNNN
  
  FP32S  SartVolt_Per;        //临界电压,%-----DI_START_VOLT,取值后除100:0.0~1.0，默认：0.60
  
  FP32S  OverVolt_Per;        //过压判断阀值,%-----DI_OVER_VOLT，2字节
  FP32S  OverCur_Per;        //过流判断阀值,%-----DI_OVER_CURR，2字节
  
  FP32S  CurNoEvenUp_Per;        //电流不平衡上限,DI_CURR_NOTEVEN_UP NNNN.NN %
  FP32S  VoltNoEvenUp_Per;        //电压不平衡上限,DI_VOLT_NOTEVEN_UP NNNN.NN %
*/
  //---------------------------------------------------------
  INT16U  LossVolt_U_Up;       //失压事件电压触发上限
  INT16U  LossVolt_U_Down;     //失压事件电压恢复下限
  INT32U  LossVolt_I_Down;     //失压事件电流触发下限 
  INT8U   LossVolt_Time;       //失压事件判定延时时间 
  
  INT16U  DownVolt_U_Up;       //欠压事件电压触发上限
  INT8U   DownVolt_Time;      //欠压事件判定延时时间 
  
  INT16U  UpVolt_U_Down;       //过压事件电压触发下限
  INT8U   UpwnVolt_Time;      //过压事件判定延时时间 
  
  INT16U  CutParse_U_Up;       //断相事件电压触发上限
  INT32U  CutParse_I_Up;       //断相事件电流触发上限 
  INT8U   CutParse_Time;       //断相事件判定延时时间 
  
  INT16U  Volt_NoEven_Up;       //电压不平衡率限值  
  INT8U   Volt_NoEven_Time;       //电压不平衡率判定延时时间 
  
  INT16U  Curr_NoEven_Up;       //电流不平衡率限值  
  INT8U   Curr_NoEven_Time;       //电流不平衡率判定延时时间 

  
  INT16U  LossCurr_U_Down;       //失流事件电压触发下限
  INT32U  LossCurr_I_Up;         //失流事件电流触发上限 
  INT32U  LossCurr_I_Down;     //失流事件电流触发下限 
  INT8U   LossCurr_Time;       //失流事件判定延时时间 
  
  INT16U  UpCurr_I_Down;        //过流事件电流触发下限
  INT8U   UpCurr_Time;       //过流事件判定延时时间 
  
  
  INT16U  CutCurre_U_Down;     //断流事件电压触发下限
  INT32U  CutCurr_I_Up;       //断流事件电流触发上限 
  INT8U  CutCurr_Time;       //断流事件判定延时时间 
  
  INT16U  NegCurr_Acpow_Down;       //潮流反向事件有功功率触发下限
  INT8U   NegCurr_Time;      //潮流反向事件判定延时时间 
  
  INT32U OverLoad_AcPow_Down;       //过载事件有功功率触发下限
  INT8U  OverLoad_Time;      //过载事件判定延时时间 
  
  
  INT32U  OverDe_Acpow_Down;       //有功需量超限事件需量触发下限
  INT32U  OverDe_Reacpow_Down;        //无功需量超限事件需量触发下限 
  INT8U   OverDe_Time;       //需量超限事件判定延时时间 

  INT16U  DownPf_I_Down;       //总功率因数超下限阀值  
  INT8U   DownPf_Time;          //总功率因数超下限判定延时时间
  
  INT16U  Curr_No1Even_I_Up;    //电流严重不平衡限值  
  INT8U   Curr_No1Even_Time;    //电流严重不平衡触发延时时间 
  
  
  INT8U   Start_Volt;          //临界
  
  
  INT8U CS[CS_BYTES];
}EventInsPara;         //事件处理状态

     


EVENTINSTANT_C_EXT EventInsPara EventInsParaVar;

#define  CLR_DEMD_KEY_PRESS 0x35
typedef struct{
  INT8U Status;            //编程
  INT8U CS[CS_BYTES];
}KeyStatus;

EVENTINSTANT_C_EXT KeyStatus  Clr_Demand_Key;


/*
#define KEY_INIT_STATUS  0x35
typedef struct{
  INT8U Prg;            //编程
  INT8U CS[CS_BYTES];
}KeyStatus;         //事件处理状态

EVENTINSTANT_C_EXT KeyStatus  KeyInitStatus;
*/

/*
#define MAX_CHANGE_SEC    8     //变位判断时间
typedef struct
{ 
  INT8U Head;
  INT8U OldStatus;           //旧状态
  INT8U NewStatus;           //新状态
  INT8U Counts;             //计数器
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