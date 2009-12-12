#ifndef __LCDMAIN__
#define __LCDMAIN__


#ifdef LCD_MAIN_C
#define LCD_MAIN_EXT volatile
#else
#define LCD_MAIN_EXT extern volatile
#endif


//#include "pub.h"
//#include "Pub_PUCK.h"




#define PROC_NONE   0
#define PROC_ADD    1
#define PROC_SUB    2
#define PROC_SWITCH 3


#define  NUMBMODEA  PDI_AUTO_CYCL_SCREEN_NUM   //自动循环显示屏数
#define  NUMBMODEB  PDI_KEY_CYCL_SCREEN_NUM   //按钮循环显示屏数

#ifdef DIS_ITEM_BYTE_4       //显示代码为4个字节，缩位
  #define  ITEMMODEA  PDI_AUTO_CYCL_SREEN_DATA   //自动循环第1屏显示项目
  #define  ITEMMODEB  PDI_KEY_CYCL_SREEN_DATA   //按钮循环第1屏显示项目
#else                       //显示代码为5个字节，国网扩展
  #define  ITEMMODEA  PDI_AUTO_CYCL_SREEN_DATA    //0x04040301               //自动循环显示第1屏显示数据项
  #define  ITEMMODEB  PDI_KEY_CYCL_SREEN_DATA     //0x04040401              //按键循环显示第1屏显示数据项
#endif


#define  VARHMODE1  PDI_REACTIVE_PORT_WORD_1       //无功组合特征字1
#define  VARHMODE2  PDI_REACTIVE_PORT_WORD_2       //无功组合特征字2
#define  ROLLCYCLE  PDI_SCREEN_SHOW_TIME    //循显时间

#define BYTE(x,byte)      (INT8U)(x>>(byte*8))

#define LCD_SLEEP_SEC 30


DECLARE_BUF_TYPE(INT8U,9,S_Buf_BIT8_LEN5);
#ifdef LCD_MAIN_C
  LCD_MAIN_EXT  S_Buf_BIT8_LEN5 Pub_Bit8_Len5_PUCK={CHK_BYTE,{0},CHK_BYTE};
#endif
LCD_MAIN_EXT S_Buf_BIT8_LEN5    Pub_Bit8_Len5_PUCK;
#define  rollcycle              Pub_Bit8_Len5_PUCK.Buf[0]
#define  dispmode               Pub_Bit8_Len5_PUCK.Buf[1]
#define  EnergDisBit            Pub_Bit8_Len5_PUCK.Buf[2]
#define  DemandDisBit           Pub_Bit8_Len5_PUCK.Buf[3]
#define  LcdDisTemp1            Pub_Bit8_Len5_PUCK.Buf[4]
#define  LcdDisTemp2            Pub_Bit8_Len5_PUCK.Buf[5]
#define  Light_Mode             Pub_Bit8_Len5_PUCK.Buf[6]   //当前是背光显示还是红外显示
#define  Beep_Disable           Pub_Bit8_Len5_PUCK.Buf[7]
#define  Relay_On_Key_Countr    Pub_Bit8_Len5_PUCK.Buf[8]

#define ENABLE_BEEP_ALARM Beep_Disable=0
#define DIS_BEEP_ALARM    Beep_Disable=1

DECLARE_BUF_TYPE(INT16S,2,S_Buf_BIT16_LEN4);
#ifdef LCD_MAIN_C
  LCD_MAIN_EXT S_Buf_BIT16_LEN4  Pub_Bit16_Len4_PUCK={CHK_BYTE,{0},CHK_BYTE};
#endif
LCD_MAIN_EXT S_Buf_BIT16_LEN4 Pub_Bit16_Len4_PUCK;
#define  MODE_A_NUM  Pub_Bit16_Len4_PUCK.Buf[0]
#define  MODE_B_NUM  Pub_Bit16_Len4_PUCK.Buf[1]


#ifdef LCD_MAIN_C
LCD_MAIN_EXT S_Int32U Sleep_Sec_Countr={CHK_BYTE,0x00,CHK_BYTE};   //循显下，计显示轮次；键显下，计时间
LCD_MAIN_EXT S_Int8U LCD_Loop_Num={CHK_BYTE,0x00,CHK_BYTE};
LCD_MAIN_EXT S_Int32U LCD_Loop_Ms10Timr={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
#endif
LCD_MAIN_EXT S_Int32U Sleep_Sec_Countr;
LCD_MAIN_EXT S_Int8U LCD_Loop_Num;
LCD_MAIN_EXT S_Int32U LCD_Loop_Ms10Timr;

LCD_MAIN_EXT INT32U  LCDLoopSecTimer;
LCD_MAIN_EXT INT32U  LCDLightSecTimer;

#define IRDA_LIGHT_ON_TIME    60
#define KEY_LIGHT_ON_TIME     (2*CYCLE)   //120

#define START_LIGHT_ON          {LCDLightSecTimer=Sec_Timer_Pub;}
#define CLR_LIGHT_ON            {LCDLightSecTimer=Sec_Timer_Pub-1;}
#define TURN_OFF_LIGHT          {LCDLightSecTimer=Sec_Timer_Pub-0xFFFF;}
#define LIGHT_SEC_TIMER_DIFF    (Sec_Timer_Pub-LCDLightSecTimer)

#define START_LOOP_DIS       {LCDLoopSecTimer=Sec_Timer_Pub;}
#define LOOP_SEC_TIMER_DIFF  (Sec_Timer_Pub-LCDLoopSecTimer)

#ifdef DIS_PARA_JUMP_EN
  #define MAX_MODI_NUM 5
  typedef struct
  {
   INT8U Flag;
   PROTO_DI Para_Modi[MAX_MODI_NUM];
   INT8U CS[CS_BYTES];
  }PARA_MODI_DIS;
  
  LCD_MAIN_EXT PARA_MODI_DIS Para_Dis_Var;
#endif

LCD_MAIN_EXT  INT16S dispoffset;

#define DIS_BUF_LEN  268
DECLARE_BUF_TYPE(INT8U,DIS_BUF_LEN,S_Buf_Dis);
#ifdef LCD_MAIN_C
  LCD_MAIN_EXT S_Buf_Dis  _Dis_GetData_Buf={CHK_BYTE,{0},CHK_BYTE};
#endif
LCD_MAIN_EXT S_Buf_Dis _Dis_GetData_Buf;
#define  Dis_GetData_Buf  _Dis_GetData_Buf.Buf


#define MULIT_EXSIT 0x54
// 子屏显示信息
typedef struct {
  //INT32U  lastid;
  //INT32U  Currid;
  INT8U   exist;  
  //INT8U   lastproc;
  INT8U   len;
  INT8U   subindex;  //屏号，0~MAX-1 ------------------目前屏号
  INT8U   fmtindex;
  INT16U  offset;
} Mult_List;

LCD_MAIN_EXT Mult_List Sub_Vlist; 

typedef INT32U  code_t; ///< display code type.


typedef INT32U  item_t; ///< dataitem type.

typedef INT16U  offs_t; ///< dataitem numbers.
typedef signed   char   curs_t; ///< cursor position.




typedef union 
{
    struct {
        INT32U bit0 : 4;
        INT32U bit1 : 4;
        INT32U bit2 : 4;
        INT32U bit3 : 4;
        INT32U bit4 : 4;
        INT32U bit5 : 4;
        INT32U bit6 : 4;
        INT32U bit7 : 4;
        
    };
    INT32U code;
} disp_t;


LCD_MAIN_EXT curs_t dispcursor;
//static volatileoffs_t dispoffset;
LCD_MAIN_EXT disp_t dispcode;




//打开背光显示的操作类型
#define LIGHT_ON_NONE      0
#define LIGHT_ON_KEY       1
#define LIGHT_ON_IRDA      2
#define LIGHT_ON_CARD      3
#define LIGHT_ON_MONEY     4   //剩余金额<报警金额

//显示的出错代码
//故障代码
#define DIS_N0_ERR                        0
#define DIS_CTRL_LOOP_ERR                 1  //控制回路错误
#define DIS_ESAM_ERR                      2   //ESAM错误
#define DIS_MEM_ERR                       3  //内卡初始化错误
#define DIS_RTCBAT_LOW                    4   //时钟电池电压低
#define DIS_RTC_ERR                       8  //时钟故障

//费控故障代码
#define DIS_CERTI_ERR                     10 //认证错误
#define DIS_CUR_VERY_NOEVEN               11 //ESAM验证失败
#define DIS_GUEST_ID_ERR                  12 //客户编号不匹配
#define DIS_CHARGE_NUM_ERR                13 //充值次数错误
#define DIS_BUY_TOO_ENOUGH                14 //购电超囤积
#define DIS_CUR_PARA_CARD_INVALID         15 //现场参数设置卡对本表已经失效
#define DIS_CUR_MODI_KEY_ERR              16 //修改密钥错误
#define DIS_NO_LEAD_KEY_ERR               17 //未按铅封键
#define DIS_CPU_CARD_LOSE_ERR             18 //提前拔卡
#define DIS_CUR_MODI_METER_ERR            19 //修改表号卡满（该卡无空余表号分配）
#define DIS_CUR_KEY_CARD0_ERR             20 //修改密钥卡次数为0
#define DIS_METER_REGISTERD_ERR           21 //表计已开户（开户卡插入已经开过户的表计）
#define DIS_METER_NO_REGIST_ERR           22//表计未开户（用户卡插入还未开过户的表计）
#define DIS_NOKNOWED_CARD_ERR             23//卡损坏或不明类型卡（如反插卡，插铁片等）
#define DIS_LOW_VOLT_ERR                  24 //表计电压过低（此时表计操作IC卡可能会导致表计复位或损害IC卡）
#define DIS_CARD_FILED_FORMAT_ERR         25 //卡文件格式不合法（包括帧头错，帧尾错，效验错）
#define DIS_CARD_TYPE_ERR                 26 //卡类型错
#define DIS_CARD_REGISTERD_ERR            27 //已经开过户的新开户卡（新开户卡回写区有数据）
#define DIS_OTHER_ERR                     28 //其他错误（卡片选择文件错，读文件错，些文件错等）

//事件代码
#define DIS_POWER_EXCEED_ERR              51//过载
#define DIS_CUR_VERY_NOEVEN_ERR           52//电流严重不平衡
#define DIS_VOLT_EXCEED_ERR               53 //过压 
#define DIS_PF_EXCEED_ERR                 54 //功率因数超限
#define DIS_DEMAND_EXCEED_ERR             55 //超有功需量报警事件

/*
#define DIS_MIN_ERR_CODE DIS_CTRL_LOOP_ERR
#define DIS_MAX_ERR_CODE DIS_RTCBAT_LOW

#define DIS_MIN_EVENT_CODE DIS_POWER_EXCEED_ERR
#define DIS_MAX_EVENT_CODE DIS_DEMAND_EXCEED_ERR
#define DIS_ERR_NUM   (DIS_MAX_ERR_CODE+DIS_MAX_EVENT_CODE+2-DIS_MIN_ERR_CODE-DIS_MIN_EVENT_CODE)
*/


#define DIS_ERR_NUM           (DIS_DEMAND_EXCEED_ERR+1)

#if SYS_ERR_DIS_EN >0
  typedef struct
  {
    INT8U Head;    
    INT8U LoopDis:1;
    INT8U DisIndex:7;                    //出错显示 
    INT8U ErrNum;     
    INT8U ErrCode[DIS_ERR_NUM/8+1];      //出错信息代码
    INT8U Tail;
  }SYS_ERR_INFO;
  LCD_MAIN_EXT SYS_ERR_INFO Sys_Err_Info;

#endif

void LCD_main_LUCK (void);
void Dis_Jump_Para(void);
void Set_Para_Modi_DI(PROTO_DI Di);
PROTO_DI Get_Para_Modi_DI(void);
INT8U Get_Para_Modi_Flag(void);
void Check_LCDVar_Cs(void);
void Key_Fast_LCD_Proc(void);
void Loop_Dis_LCD_Proc(void);
void LCD_Init_PUCK(void);
void Set_C_Mode_DisCode(INT8U dval);
void Modi_DisOff_AB_SubIndex(INT32U item,INT8U proc) ;
INT8U Judge_Modi_Sub_Screen(INT32U item,INT8U proc);
void Refresh_Curr_Offset(void);
void Judge_Modi_C_Offset(INT8U pos,INT8U proc);
void dispnext(void);
void dispback(void);
void ReNew_Err_Code(INT8U ErrCode);
void Clr_Err_Code(INT8U ErrCode);
void  lcd_Pre_Pay    (INT8U shenyu,INT8U jine);
void Refresh_Sleep_Countr(INT8U);
#endif