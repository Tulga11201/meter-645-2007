
#ifndef APP_CFG_PUCK
#define APP_CFG_PUCK

#define TH_MODE     0   //双方向
#define TF_MODE     1   //单方向

#define PARSE_331    0
#define PARSE_341    1

#define PULSE_TYPE1  0
#define PULSE_TYPE2  1

#define VOLT_3100    0
#define VOLT_3220    1
#define VOLT_3577    2
#define VOLT_3380    3

#define CURR_1x5_6   0
#define CURR_1_2     1
#define CURR_5_10    2
#define CURR_10_40   3
#define CURR_0x3_1x2 4
#define CURR_5_6     5
#define CURR_15_60   6
#define CURR_20_80   7
#define CURR_5_20   8
#define CURR_30_100   9

#define CAL_MEASU_OVER   0x55 //MeasuIC校表完成标志

#define PARA_SRAM  0
#define PARA_FLASH 1

#define MEASU_PARA_START  (REG_W_START&0x7F)
#define MEASU_PARA_CURSTART  (REG_W_ISTART&0x7F)
#define MEASU_PARA_ISTART (REG_W_ISTART&0x7F)
#define MEASU_PARA_PULSE  (REG_W_PULSE&0x7F)
#define MEASU_PARA_ENMODE (REG_W_ENMODE&0x7F)
#define MEASU_PARA_VGAIN  (REG_W_VGAIN&0x7F)
#define MEASU_PARA_CS       0x40   //存放CS的位置



#define MEASURE_ERROR_STATICS_EN //开启，打开计量错误统计，同时开辟相应的 Sram资源和Flash资源
#define OS_DEBG_EN       //OS功能打开 ！

//#define MEASURE_VAR_BAK_EN       //开启，使能电能变量的备份
//#define MEASU_ANGLE_RD           //开启：角度由7022给出；关闭：由自己算出,建议关闭该宏，角度自己算
#define DRV_TEST_EN             //开启:使能驱动测试功能
//#define CONFLICT_TAB_CHKEN     //检查所有配置表是否冲突



//操作配置宏
#define CHANNEL_FAST_EN           //宏打开，通信通道快速响应


                   
#define LOSS_VOLT_ONLY           //判定依据：失压只判定电压，与电流无关
#define LOSS_CURR_ONLY           //判定依据：失流只判定电流，与电流平衡率无关
                             //通用版本
//#define MULTI_LOSS_VOLT_EN       //合相判定：宏打开，失压合相判定，宏关闭：分相判定
//#define MULTI_LOSS_CURR_EN       //合相判定：宏打开，失流合相判定(AB,AC,BC)，宏关闭：分相判定，注意：全失流/A /B/C失流为单独事件


//计量参数配置宏
#define DEFAULT_PULSE_SPEC  PULSE_TYPE2
#define DEFAULT_VOLT_SPEC   VOLT_3220
#define DEFAULT_CURR_SPEC   CURR_1x5_6
#define DEFAULT_TFH_SPEC    TH_MODE
#if DEFAULT_VOLT_SPEC==VOLT_3220 || DEFAULT_VOLT_SPEC==VOLT_3577
  #define DEFAULT_PARSE_SPEC  PARSE_341
#else
  #define DEFAULT_PARSE_SPEC  PARSE_331
#endif
#define DEFAULT_AC_PULSE        6400
#define DEFAULT_REAC_PULSE      6400


//LCD属性
#define LCD_NORMAL           0         //通用液晶
#define LCD_JS_ZXW           1         //江苏液晶---中显威
#define LCD_JS_JX            2         //江苏液晶---晶像
#define LCD_SD_ZXW           3         //山东液晶---中显威(国网前一版液晶)
#define LCD_GW_ZXW           4         //国网液晶---中显威
#define LCD_EASY_GZL         5         //简单液晶---高卓立


#define DRV_SIMU_DS3231    0//宏开启，打开DS3231的软件模拟功能，关闭，打开IIC的硬件功能
#define DRV_SIMU_RX8025    1
#define DRV_SIMU_RX8025T   2
#define DRV_SIMU_RV3029C2  3



#define MEASU_7028A        0
#define MEASU_7022B        1
#define MEASU_7022C        2



#define ALL_LOSS_SOFT              0  //全失压全部通过软件来实现
#define ALL_LOSS_HARD_SINGLE       1  //全失压通过硬件来触发，软件来实现
#define ALL_LOSS_HARD_MULTI        2  //全失压通过硬件来触发，硬件来实现

//----------------------------------------与硬件相关配置----------------------------------------------
//按钮配置
#undef  LEFT_KEY_EN                       //宏打开，使能左按钮
#undef  NEAR_IRDA_EN                      //宏打开，使能吸附红外
#undef  RIGHT_KEY_EN                      //宏打开，使能右按钮
#undef  DIS_PARA_JUMP_EN                  //宏打开，使能参数修改跳屏

#define MEASU_IC_TYPE       MEASU_7022B
#define LCD_PROPERTY        LCD_GW_ZXW

#define FM_ROM_FM16_EN                    //打开 FM16功能

#define DRV_HARD_DS3231    0              //1:3231硬件I2C开起;0:硬件I2C关闭 

#define MEASU_BAKPWR_NEW_EN                    //打开:使用新的7022后备电源方式

#define LOW_COST_HARD_EN                         //打开：低成本硬件：ESAM_CLOCK,CPU_CLOCK,CF1,红外唤醒硬件

#ifdef LOW_COST_HARD_EN
  #define RST_IC_7X6_EN
  #define EXT_RTC_TYPE       DRV_SIMU_RX8025T  //DRV_SIMU_DS3231 DRV_SIMU_RX8025T  DRV_SIMU_RV3029C2
  #define ALL_LOSS_TYPE      ALL_LOSS_SOFT       //宏打开，打开 硬件的全失压方法。关闭，通过软件全失压
  #undef  DOWN_COVER_ERR                         //打开:后端子该错误
#else
  #undef RST_IC_7X6_EN
  #define EXT_RTC_TYPE       DRV_SIMU_DS3231  //DRV_SIMU_DS3231 DRV_SIMU_RX8025T  DRV_SIMU_RV3029C2
  #define ALL_LOSS_TYPE      ALL_LOSS_HARD_SINGLE       //宏打开，打开 硬件的全失压方法。关闭，通过软件全失压
  #define DOWN_COVER_ERR                         //打开:后端子该错误
#endif

//----------------------------------------与功能相关配置----------------------------------------------
//#define ALL_LOSS_DIS_U                    //打开 :全失压发生，唤醒后闪烁电压
//#define REMOTER_FUNC_EN                       //打开遥控器功能
#define I_ORDER_CHK_EN             0         //1:电流逆相序使能；0：电流逆向相序禁止
#define DIS_METER_FAULT_EN         1         //1:电表故障显示使能；0：电表故障不显示



//多合一端子排配置：秒脉冲、时段、需量、滑差
//1:配置以下宏，与Const_Port_Status[]中的MultiFlag为0还是1含义不一样；
//2：配置 Const_Port_Status[]中的 MultiFlag为0还是1
//3:对于秒脉冲与其他3合一端子共用，秒脉冲使能配置：MultiFlag＝0(为1，Port_Out_Pub函数中，则不能 END！)；SEC_MULTI_PORT＝1；
#define SEC_MULTI_PORT 1          //0：秒脉冲不是复合端子；1：秒脉冲是复合端子(共用）
#define MULTI_3_PORT   2          //0：不是复合端子；1：是复合端子，但与秒脉冲不共用；2是复合端子，且与秒脉冲共用；
#define SEC_OUT_POWER_ON   1      //1:上电后就输出秒脉冲；0：上电后根据模式字决定是否输出秒脉冲

//显示表记系统出错代码
#define SYS_ERR_DIS_EN          1 //0----------表计系统出错代码关闭；1----------表计系统出错代码打开
#define HARD_ERR_BEEP           0 //1宏打开，硬件蜂鸣器和led报错：如计量，晶振错位，自检时候报警,0关闭

//---------------------------------------------------------------------------------------------------
#define HT1623    0
#define BL55076   1

#if LCD_PROPERTY==LCD_NORMAL
    #define LCD_DRV_CHIP HT1623   
    #include "APP_LCD_Pub.h"
#endif

#if LCD_PROPERTY==LCD_JS_ZXW
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_JS_ZXW.h"
#endif

#if LCD_PROPERTY==LCD_JS_JX
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_JS_JX.h"
#endif

#if LCD_PROPERTY==LCD_SD_ZXW
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_SD_ZXW.h"
#endif

#if LCD_PROPERTY==LCD_GW_ZXW
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_GW_ZXW.h"
#endif

#if LCD_PROPERTY==LCD_EASY_GZL
    #define LCD_DRV_CHIP BL55076    
    #include "APP_LCD_LIB_GZL.h"
#endif


//液晶主窗口的 8 字符个数配置
#if LCD_PROPERTY >= LCD_SD_ZXW  //只有8个8的液晶     
   #define LCD_MIN_8              // 宏开启：显示窗口为8个LED_8的 LCD片。
   #undef  DIS_ITEM_BYTE_4        //宏开启：显示项目按照4字节配置，否则按照5字节配置
#else
   #undef LCD_MIN_8              // 宏开启：显示窗口为8个LED_8的 LCD片。
   #undef DIS_ITEM_BYTE_4       //宏开启：显示项目按照4字节配置，否则按照5字节配置
#endif



//串口属性
#if ((NET_METER EQ CARRIER_METER)||(NET_METER EQ GPRS_METER))//载波表，GPRS表，
  #define UART1_EN 
#elif (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE)) //非模块表：远程费控表
  #define UART1_EN 
#else
  #undef  UART1_EN
#endif

//内部时钟电池工作时间配置
#define BAT_RUN_TIME_PWROFF       1   //统计掉电后RTC工作时间
#define BAT_RUN_TIME_PWRON        2   //统计上电运行RTC工作时间

#define BAT_RUN_TIME     (BAT_RUN_TIME_PWROFF | BAT_RUN_TIME_PWRON)         //统计RTC工作时间

#define COMPUTER_CAL_TYPE       1  //支持主台软件校表
#define SELF_CAL_TYPE           2  //表计自动校表
#define ALL_CAL_TYPE            3  //支持2种校表

#define CAL_METER_TYPE ALL_CAL_TYPE


#endif
