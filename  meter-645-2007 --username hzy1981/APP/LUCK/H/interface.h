
/**                                                                                                
 * @file interface.h                                                                                    
 *     { comment block }
 * @brief                                                                                           
 *     { brief description @ref interface.cpp }                                                                              
 * @author li.yao (nardoo@sohu.com)                                                                                  
 * @version v1.00                                                                               
 * @date 05/29/2008 08:40                                                                                   
 * @note 
 *     { paragraph where a note can be entered. }                                                   
 */                                                                                                 


#ifndef __INTERFACE__
#define __INTERFACE__

#define  MAXDLEN  32  //显示数据最大字符数目

#define  MODE_A_B_BITS        (-1)          //A/B模式下光标提示
#define  MINBITS              0             //C模式下的最小显示光标，及子屏显示




#if LCD_PROPERTY==LCD_SD_ZXW  ||  LCD_PROPERTY==LCD_GW_ZXW 
  #define  SET_HIGH_CODE_BIT         //显示代码最高位控制,空语句
  #define  MAXBITS              8             //C模式下的最大显示光标
#else
  #define  SET_HIGH_CODE_BIT   dispcode.bit7=0    //显示代买最高位控制
  #define  MAXBITS              7             //C模式下的最大显示光标
#endif


#define  LEFTBITS             (MAXBITS-1)   //C模式下的最小显示光标
#define  RIGHTBITS            (MINBITS+1)    //C模式下的最大显示光标



typedef signed   char      s8;  ///< unsigned  8 bit quantity.
typedef unsigned char      u8;  ///< unsigned  8 bit quantity.
typedef unsigned short     u16; ///< unsigned 16 bit quantity.
typedef signed   short     s16; ///< signed   16 bit quantity.
typedef unsigned long      u32; ///< unsigned 32 bit quantity.
typedef signed   long      s32; ///< signed   32 bit quantity.
//typedef _ULonglong         u64; ///< unsigned 64 bit quantity.
//typedef _Longlong          s64; ///< signed   64 bit quantity.

#define TRUE 1
#define FALSE 0
typedef  u8 bool;



/// mode element.
typedef struct {
    u8 bit0 : 1; ///< mode2.bit0 ? "停电时间" : "当前时间";
    u8 bit1 : 1; ///< mode4.bit1 ? "告警显示" : "告警关闭";
    u8 bit2 : 1; ///< mode3.bit2 ? 失压标志"闪烁" : "消失";
    u8 bit3 : 1; ///< mode4.bit3 ? "高位补0" : "高位不补0";
    u8 bit4 : 1; ///< mode4.bit4 ? "输入", "输出" : "正向", "反向";
    u8 bit5 : 1; ///< mode4.bit5 ? "上月", "上上月" : "上1月", "上2月";
    u8 bit6 : 1; ///< mode8.bit6 ? 需量不带年 : 需量带年
    u8 bit7 : 1; ///< mode4.bit7 ? "逆时针" : "顺时针";
} mode_t;

/// status element.
typedef union 
{
    struct 
    {
        u32 loss_volt_a   : 1; ///< 失压 A 闪烁
        u32 loss_volt_b   : 1; ///< 失压 B 闪烁
        u32 loss_volt_c   : 1; ///< 失压 C 闪烁        
        u32 cut_volt_a    : 1; ///< 断相A: 消失
        u32 cut_volt_b    : 1; ///< 断相A: 消失
        u32 cut_volt_c    : 1; ///< 断相A: 消失        
        u32 over_volt_a   : 1; ///< 过压(Ua)
        u32 over_volt_b   : 1; ///< 过压(Ub)
        
        u32 over_volt_c   : 1; ///< 过压(Uc)        
        u32 down_volt_a   : 1; ///< 欠压(Ua)
        u32 down_volt_b   : 1; ///< 欠压(Ub)
        u32 down_volt_c   : 1; ///< 欠压(Uc)        
        u32 loss_cur_a    : 1; ///< 失流 A
        u32 loss_cur_b    : 1; ///< 失流 B
        u32 loss_cur_c    : 1; ///< 失流 C        
        u32 loss_cut_a    : 1; ///< 断流 A：小于启动电流
        
        u32 loss_cut_b    : 1; ///< 断流 B：小于启动电流
        u32 loss_cut_c    : 1; ///< 断流 C：小于启动电流        
        u32 cur_rers_a    : 1; ///< 电流反极性 A
        u32 cur_rers_b    : 1; ///< 电流反极性 B
        u32 cur_rers_c    : 1; ///< 电流反极性 C          
        u32 cell_low1     : 1; ///< 时钟电池低电压
        u32 cell_low2     : 1; ///< 低功耗电池低电压
        u32 cell_low3     : 1; ///< 预留
        
        u32 stat_communi  : 4; ///< 通信状态(RS1,RS2,红外)(常亮)        
        u32 volt_reverse  : 1; ///< 电压"逆相序"(闪烁)
        u32 curr_reverse  : 1; ///< 电流"逆相序"(闪烁)
        u32 event_warning : 1; ///< 事件告警(闪烁)
        u32 switch_opened : 1; ///< 编程键打开(常亮)
        
        
        u32 fac_status    : 1; ///< 工厂(常亮)
        u32 jumper_short  : 1; ///< 跳线短接(常亮)
        u32 reset_demand  : 1; ///< 需量复位(常亮)        
        u32 signal_scale  : 3; ///< 通讯模块信号强度指示(常亮)
        u32  num_tariff   : 2; //显示主副时段1：主时段；2：副时段，其他：不显示
        
        u32 status_tariff : 4; ///< 显示当前费率，"尖, 峰, 平, 谷, T5, ...Tx", 
        u32  SetpRate     : 2; //电价：1～4 
        u32  SetpScheme   : 2; //电价方案：1～2
        
        u32 meter_locked  : 1; ///< 电表上锁(常亮)
        u32 status_online : 1; ///< 通讯模块在线指示(常亮)        
        u32  BuyFee       : 1; //请购电 
        u32  CalMeter     : 1; //校表事件       
        u32  TouZhi       : 1; //透支
        u32  RelayOff     : 2; //拉闸------1（闪烁）：2---------常亮
        u32  reserved     : 9; //预留        
    };
    struct 
    {
        u32 bit1maps; //< 事件状态位图
        u32 bit2maps; //< 事件状态位图
    };    
} stat_t;


/*
typedef enum {
    none = 0x00, 
    key1 = 0x01, 
    key2 = 0x02, 
    key3 = 0x04,
    key4 = 0x08,
    key5 = 0x10,
} pkey_t;
*/
typedef enum {
    modeA, modeB, modeC,
} type_t;

// 获取按键值
u8 getpkey (void);

// 判断是否停电
#define poweroff()   (Get_Sys_Status() != SYS_NORMAL)

// 判断是否为实时数据
bool rtvalue (item_t item);

// 参数初始化
void lcdinit (void);

// 获取协议数据内容
s16 getdata (item_t id, void* buff, void* start, s16 maxlen);
// id    : 对应数据的标识码
// buff  : 输入缓冲的首地址
// start : 数据输入起始地址
// maxlen: 输入缓冲的最大长度
// return: 返回写入的实际长度

// 常量显示元素，仅仅显示，不需要闪烁。
void lcd_total     (u8 flg); ///< "总",
void lcd_phase     (u8 flg); ///< "A/B/C相",
void lcd_voltage   (u8 flg); ///< "电压",
void lcd_current   (u8 flg); ///< "电流",
void lcd_positive  (u8 flg); ///< mode4.bit4 ? "输入" : "正向";
void lcd_negative  (u8 flg); ///< mode4.bit4 ? "输出" : "反向";
void lcd_reactive  (u8 flg); ///< "无功",
void lcd_active    (u8 flg); ///< "有功",
void lcd_power     (u8 flg); ///< "功率",
void lcd_factor    (u8 flg); ///< "因数",
void lcd_angle     (u8 flg); ///< "相角",
void lcd_energy    (u8 flg); ///< "电量",
void lcd_demand    (u8 flg); ///< "需量",
void lcd_time      (u8 flg); ///< "时间",
void lcd_charge    (u8 flg); ///< "电费",
void lcd_lostvolt  (u8 flg); ///< "失压",
void lcd_lostcurt  (u8 flg); ///< "失流",
void lcd_periods   (u8 flg); ///< "时段",
void lcd_feerate   (u8 flg); ///< "费率", 
void lcd_thismonth (u8 flg); ///< "本月",
void lcd_lastmonth (u8 flg); ///< mode4.bit5 ? "上月", "上上月" : "上1月", "上2月";
void lcd_lasttime (u8 flg); ///< 上xx次
void lcd_times     (u8 flg); ///< 上xx
void lcd_assemble  (u8 flg); ///< "无功组合方式1 or 2",
void lcd_quadrant  (u8 flg); ///< "XX象限",
void lcd_tariff    (u8 flg); ///< 显示"费率Tx",
void lcd_times     (u8 flg); ///< 显示"上XX次",
void lcd_jieti     (u8 flg); ///< 阶梯
void lcd_dianjia   (u8 flg); ///电价
void lcd_value (const char* s);

// 输出显示数据的内容
void lcd_data (item_t item, const char* frmt,Mult_List list);

// 输出显示代码的内容
void lcd_code (code_t user, code_t code, curs_t curs,u8 SubCurs,u8 changeFlag,code_t changecode);

// 输出显示方案的内容
void lcd_mode (u8 type);

// 显示缓冲区内容
void lcd_update (void);

// 输出显示事件状态
void lcd_events (void);

u8 Modi_Item(item_t item,item_t *Dst);


#endif
