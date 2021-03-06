#ifndef AllLossProc_h
#define AllLossProc_h


#ifndef AllLossMeasu_C
#define AllLossMeasu_EXT  extern
#else
#define AllLossMeasu_EXT
#endif


#ifdef MEASU_BAKPWR_NEW_EN
  #define BAT_ON_7022       PM5_bit.no0=0,P5_bit.no0=1
  #define BAT_OFF_7022      PM5_bit.no0=0,P5_bit.no0=0
#else
  #define BAT_ON_7022       PM6_bit.no3=0,P6_bit.no3=1
  #define BAT_OFF_7022      PM6_bit.no3=0,P6_bit.no3=0
#endif


#define MEASU_CS_DIR        PM13_bit.no0
#define MEASU_CLK_DIR       PM2_bit.no4
#define MEASU_DOUT_DIR      PM2_bit.no2
#define MEASU_RST_DIR       PM2_bit.no0

#define MEASU_SIG_DIR       PM2_bit.no1
#define MEASU_DIN_DIR       PM2_bit.no3


#if ALL_LOSS_TYPE EQ ALL_LOSS_HARD_MULTI 
  #define ALL_LOSS_NUM 10   //记录全失压最大次数
#else
  #define ALL_LOSS_NUM 1   //记录全失压最大次数
#endif

typedef struct
{
  ALL_LOSS_STATUS   Status;
  RECORD_TIME       RecordTime[ALL_LOSS_NUM];  //单次全失压发生和结束记录
  INT32U Curr[ALL_LOSS_NUM];          //电流有效值: UNIT:0.0001A;
}ALL_LOSS_STRUC;
NO_INIT AllLossMeasu_EXT ALL_LOSS_STRUC All_Loss_Var;


typedef struct
{
  INT8U Head;
  INT32U Rate[3];
  INT8U Tail;
}CURR_RATE;
NO_INIT AllLossMeasu_EXT CURR_RATE Curr_Rate;

void Clr_All_Loss_Data(void);
void Save_All_Loss_Data(void);
void Init_All_Loss_Sram(void);
void Hard_All_Loss_Proc(void);
void Soft_All_Loss_Proc(void);
INT8U Get_AllLoss_Curr(void);
void Get_Hard_Curr_Rate(void);
void Get_Soft_Curr_Rate(void);
#endif
