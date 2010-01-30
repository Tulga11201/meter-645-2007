
/**
 * @file config.h
 *     { comment block }
 * @brief
 *     { brief description @ref config.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:40
 * @note
 *     { paragraph where a note can be entered. }
 */

#ifndef __CONFIG__
#define __CONFIG__

#define  MAXCOUNT   (sizeof(table) / sizeof(scrn_t))
#define  DIVERS     DI_METER_SOFTWARE_VERSION
#define  MADDR0     DI_METER_ADDR0
#define  MADDR1     DI_METER_ADDR1



// screen element.
typedef struct {
    u32 total     : 1; ///< "总",
    u32 phase     : 4; ///< "A/B/C/N相",
    u32 voltage   : 1; ///< "电压",
    u32 current   : 1; ///< "电流",
    u32 positive  : 1; ///< mode4.bit4 ? "输入" : "正向";
    
    u32 negative  : 1; ///< mode4.bit4 ? "输出" : "反向";
    u32 reactive  : 1; ///< "无功",
    u32 active    : 1; ///< "有功",
    u32 power     : 1; ///< "功率",
    u32 factor    : 1; ///< "因数",
    u32 angle     : 1; ///< "相角",
    u32 energy    : 1; ///< "电量",
    u32 demand    : 1; ///< "需量",
    
    u32 time      : 1; ///< "时间",
    u32 charge    : 1; ///< "电费",
    u32 lostvolt  : 1; ///< "失压",
    u32 lostcurt  : 1; ///< "失流",
    u32 periods   : 1; ///< "时段",
    u32 feerate   : 1; ///< "费率",    
    u32 thismonth : 1; ///< "当前",
    u32 yuan      : 1; ///< "元",
    
    u32 shenyu    : 1; ///< "剩余", 
    u32 lastmonth : 1; ///< 显示"上XX月",
    u32 assemble  : 2; ///< "无功组合方式1 or 2", mode4.bit7 ? 象限"逆时针" : 象限"顺时针";    
    u32 jine      : 1; ///< "金额",
    u32 jieti     : 1; //阶梯
    u32 dianjia   : 1; //电价  
    u32 lasttime  : 1; ///< 显示"上XX次",  
    
    u16 quadrant  : 3; ///< "XX象限",    
    u16 tariff    : 4; ///< 显示"费率Tx",      
    u16 times     : 3; //XX
    u16 res       : 6; ///预留4 bits  上XX
    
} elem_t;

#define GROUP_NO            0
#define GROUP_TARIFF        1      //按费率排列
#define GROUP_SETTLE        2      //按结算排列
#define GROUP_PHASE         4      //按相别排列
#define GROUP_HARMO         8      //按谐波次数排列
#define GROUP_TIMES         16      //前 n 次
#define GROUP_DATE          32     //按公共假日等级排列
#define GROUP_LOAD_DATA     6      //负荷曲线类别

#define MAX_GROUP_NUM   8


#define MAX_TARIFF          63     //最大费率数
#define MAX_SETTLE          12     //最大结算日
#define MAX_PHASE           3      //最大相别
#define MAX_HARMO           21     //最大谐波次数
#define MAX_PASSW           9      //最大密码等级排列
#define MAX_DATE            254     //最大公共假日等级排列
#define MAX_LOAD_DATA       6     //最大负荷曲线类别



#define NO_BYTE_POS   0xff

typedef struct { 
    INT8U    GroupFlag;      //同组数据集合标识
    INT8U    BytePos;        //同组内标识偏移
}GroupTypeStr;

typedef struct {        /// screen element.
    //code_t      code;       //C模式下的显示全集代码，保留-----PUCK
    item_t      item;       //C模式下的命令代码------PUCK
    GroupTypeStr   GroupType[2];
    const char* frmt;    
    elem_t      elem;
} scrn_t;

static const scrn_t table[] = {
/***********************************当前/结算总电能---与费率和结算日相关：总/费率xx****************************************************/
   {0x00000000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{   // 组合有功总电能
                                         .active    = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .energy    = 1,}},
                                         
                                           
   {0x00010000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",   {    // 正向有功总电能
                                         .positive  = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .active    = 1,
                                         .energy    = 1,}},                                      
    
    
   {0x00020000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",   {    // 反向有功总电能
                                         .negative  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}},
                                           
   {0x00030000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // 正向无功(组合1)电量总
                                         .positive  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .assemble  = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
    
    {0x00040000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // 正向无功(组合2)电量总
                                         .negative  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .assemble  = 2,
                                         .reactive  = 1,
                                         .energy    = 1,}},
                                           
    {0x00050000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // I象限无功电量
                                         .quadrant  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
    
    {0x00060000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // II象限无功电量
                                         .quadrant  = 2,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
                                           
    {0x00070000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // III象限无功电量
                                         .quadrant  = 3,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
    
    {0x00080000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // IV象限无功电量
                                         .quadrant  = 4,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},                                          
                                           
    {0x00090000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {    // 正向视在总电量
                                         .positive  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .energy    = 1,}},
    
    {0x000A0000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {    // 反向视在总电量
                                          .negative  = 1,
                                          .total     = 1,
                                          .thismonth = 1,
                                          .energy    = 1,}}, 
    /*
    {0x00800000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 关联总电量
                                        .negative  = 1,
                                        .total     = 1,
                                        .energy    = 1,}}, 
    
    {0x00810000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 正向有功基波总电量
                                         .positive  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}}, 
                                               
    {0x00820000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 反向有功基波总电量
                                         .negative  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}}, 
    
    {0x00830000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 正向有功谐波总电量
                                         .positive  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}}, 
                                               
    {0x00840000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 反向有功谐波总电量
                                         .negative  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}},                                            
                                          
    {0x00850000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 铜损有功总电能补偿量
                                         .negative  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}}, 
    {0x00860000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 铁损有功总电能补偿量
                                         .negative  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}},
                                                                                            
 */                                                                                          
/***********************************A相当前/上结算日电能---与结算日相关：当前/上x次结算日****************************************************/
    {0x00150000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // 当前/上x结算日正向有功电量
                                         .phase     = 1,
                                         .positive  = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}},

    {0x00160000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // 当前/上x结算日反向有功电量
                                           .phase     = 1,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},                                           

    {0x00170000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日组合无功1电量
                                           .phase     = 1,
                                           .assemble  = 1,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},
     
    {0x00180000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {  // 当前/上x结算日组合无功2电量
                                           .phase     = 1,
                                           .assemble  = 2,
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 

    {0x00190000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日1象限无功电量
                                           .phase     = 1,
                                           .thismonth = 1,
                                           .quadrant  = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},                                           


    {0x001A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日2象限无功电量
                                           .phase     = 1, 
                                           .quadrant  = 2,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},   
 
    {0x001B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日3象限无功电量
                                           .phase     = 1, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 
                                           
    {0x001C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日4象限无功电量
                                           .phase     = 1, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},      
     
     
    {0x001D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // 当前/上x结算日正向视在电能
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x001E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // 当前/上x结算日反向视在电能
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},       
    /* 
    {0x00940000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 当前/上x关联总电能
                                           .phase  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},  
                                           
    {0x00950000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 当前/上x正向有功基波总电量
                                           .phase     = 1, 
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .energy    = 1,}}, 
     
    {0x00960000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {   // 当前/上x反向有功基波总电量
                                           .phase     = 1, 
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .energy    = 1,}}, 
    
    {0x00970000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x正向有功谐波总电量
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                               
    {0x00980000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x反向有功谐波总电量
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
        
     
    {0x00990000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x铜损有功总电能补偿量
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x009A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x铁损有功总电能补偿量
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},     
*/
/***********************************B相电能---与结算日相关：当前/上x次结算日****************************************************/
    {0x00290000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // 当前/上x结算日正向有功电量
                                           .phase     = 2,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},

    {0x002A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // 当前/上x结算日反向有功电量
                                           .phase     = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},                                           

    {0x002B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日组合无功1电量
                                           .phase     = 2,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},
     
    {0x002C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {  // 当前/上x结算日组合无功2电量
                                           .phase     = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 

    {0x002D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日1象限无功电量
                                           .phase     = 2, 
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},                                           


    {0x002E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日2象限无功电量
                                           .phase     = 2, 
                                           .quadrant  = 2,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},   
 
    {0x002F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日3象限无功电量
                                           .phase     = 2, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00300000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日4象限无功电量
                                           .phase     = 2, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},      
     
     
    {0x00310000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // 当前/上x结算日正向视在电能
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00320000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // 当前/上x结算日反向视在电能
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},       
    /* 
    {0x00A80000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 当前/上x关联总电能
                                           .phase  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},  
                                           
    {0x00A90000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 当前/上x正向有功基波总电量
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
     
    {0x00AA0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {   // 当前/上x反向有功基波总电量
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
    
    {0x00AB0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // 当前/上x正向有功谐波总电量
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                               
    {0x00AC0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x反向有功谐波总电量
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
    
    
    
    {0x00AD0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x铜损有功总电能补偿量
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00AE0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // 当前/上x铁损有功总电能补偿量
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},     
     
   */  
/***********************************C相电能---与结算日相关：当前/上x次结算日****************************************************/
    {0x003D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // 当前/上x结算日正向有功电量
                                           .phase     = 3,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},

    {0x003E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // 当前/上x结算日反向有功电量
                                           .phase     = 3,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},                                           

    {0x003F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日组合无功1电量
                                           .phase     = 3,
                                           .assemble  = 1,
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},
     
    {0x00400000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {  // 当前/上x结算日组合无功2电量
                                           .phase     = 3,
                                           .assemble  = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 

    {0x00410000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日1象限无功电量
                                           .phase     = 3, 
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},                                           


    {0x00420000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日2象限无功电量
                                           .phase     = 3, 
                                           .quadrant  = 2,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},   
 
    {0x00430000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日3象限无功电量
                                           .phase     = 3, 
                                           .quadrant  = 3,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00440000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // 当前/上x结算日4象限无功电量
                                           .phase     = 3, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},      
     
     
    {0x00450000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // 当前/上x结算日正向视在电能
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00460000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // 当前/上x结算日反向视在电能
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},       
     
    /*
    {0x00BC0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 当前/上x关联总电能
                                           .phase  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},  
                                           
    {0x00BD0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // 当前/上x正向有功基波总电量
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
     
    {0x00BE0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{   // 当前/上x反向有功基波总电量
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
    
    {0x00BF0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // 当前/上x正向有功谐波总电量
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                               
    {0x00C00000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // 当前/上x反向有功谐波总电量
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
    
    
    {0x00C10000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // 当前/上x铜损有功总电能补偿量
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00C20000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // 当前/上x铁损有功总电能补偿量
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
                                           
     */           
/***********************************当前/结算有功需量及发生时间---与费率和结算日相关：总/费率xx****************************************************/
    {0x01010000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // 正向有功最大需量及时间
                                           .positive  = 1,
                                           .active    = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
    {0x01020000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // 反向有功最大需量及时间
                                           .negative  = 1,
                                           .thismonth = 1,
                                            .total     = 1,
                                           .active    = 1,
                                           .demand    = 1,}},
                                           
    {0x01030000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // 组合无功1最大需量及时间
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .total     = 1,
                                           .assemble  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
                                           
    {0x01040000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // 组合无功2最大需量及时间
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .total     = 1,
                                           .assemble  = 2,                                           
                                           .reactive  = 1,
                                           .demand    = 1,}},

    {0x01050000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // I象限无功最大需量及时间
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .total     = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
    
    {0x01060000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // II象限无功最大需量及时间
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
    {0x01070000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // III象限无功最大需量及时间
                                           .quadrant  = 3,
                                           .reactive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
    
    {0x01080000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // IV象限无功最大需量及时间
                                           .quadrant  = 4,
                                           .reactive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},  
                                           
    {0x01090000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // 正向视在总最大需量及时间
                                           .positive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
    
    {0x010A0000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // 反向视在总最大需量及时间
                                           .negative  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 


/***********************************A相当前/上结算日最大需量及发生时间---与结算日相关：当前/上x次结算日****************************************************
    {0x01150000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日正向有功最大需量及发生时间
                                           .phase     = 1,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},

    {0x01160000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日反向有功最大需量及发生时间
                                           .phase     = 1,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},                                           

    {0x01170000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日组合无功1最大需量及发生时间
                                           .phase     = 1,
                                           .assemble  = 1,
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
     
    {0x01180000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // 当前/上x结算日组合无功2最大需量及发生时间
                                           .phase     = 1,
                                           .assemble  = 2,
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 

    {0x01190000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日1象限无功最大需量及发生时间
                                           .phase     = 1, 
                                           .quadrant  = 1,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},                                           


    {0x011A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日2象限无功最大需量及发生时间
                                           .phase     = 1, 
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},   
 
    {0x011B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日3象限无功最大需量及发生时间
                                           .phase     = 1, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 
                                           
    {0x011C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日4象限无功最大需量及发生时间
                                           .phase     = 1, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},      
     
     
    {0x011D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // 当前/上x结算日正向视在最大需量及发生时间
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
                                           
    {0x011E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // 当前/上x结算日反向视在最大需量及发生时间
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
***********************************B相当前/上结算日最大需量及发生时间---与结算日相关：当前/上x次结算日****************************************************
    {0x01290000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日正向有功最大需量及发生时间
                                           .phase     = 2,
                                           .positive  = 1,
                                           .active    = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},

    {0x012A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日反向有功最大需量及发生时间
                                           .phase     = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},                                           

    {0x012B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日组合无功1最大需量及发生时间
                                           .phase     = 2,
                                           .assemble  = 1,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
     
    {0x012C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // 当前/上x结算日组合无功2最大需量及发生时间
                                           .phase     = 2,
                                           .assemble  = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 

    {0x012D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日1象限无功最大需量及发生时间
                                           .phase     = 2, 
                                           .quadrant  = 1,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},                                           


    {0x012E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日2象限无功最大需量及发生时间
                                           .phase     = 2, 
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},   
 
    {0x012F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日3象限无功最大需量及发生时间
                                           .phase     = 2, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01300000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日4象限无功最大需量及发生时间
                                           .phase     = 2, 
                                           .quadrant  = 4,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},      
     
     
    {0x01310000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // 当前/上x结算日正向视在最大需量及发生时间
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01320000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // 当前/上x结算日反向视在最大需量及发生时间
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},                                                         


                                           
***********************************C相当前/上结算日最大需量及发生时间---与结算日相关：当前/上x次结算日****************************************************
    {0x013D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日正向有功最大需量及发生时间
                                           .phase     = 3,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},

    {0x013E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日反向有功最大需量及发生时间
                                           .phase     = 3,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},                                           

    {0x013F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日组合无功1最大需量及发生时间
                                           .phase     = 3,
                                           .assemble  = 1,
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
     
    {0x01400000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // 当前/上x结算日组合无功2最大需量及发生时间
                                           .phase     = 3,
                                           .assemble  = 2,
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 

    {0x01410000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日1象限无功最大需量及发生时间
                                           .phase     = 3, 
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},                                           


    {0x01420000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日2象限无功最大需量及发生时间
                                           .phase     = 3, 
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},   
 
    {0x01430000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日3象限无功最大需量及发生时间
                                           .phase     = 3, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01440000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // 当前/上x结算日4象限无功最大需量及发生时间
                                           .phase     = 3, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},      
     
     
    {0x01450000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // 当前/上x结算日正向视在最大需量及发生时间
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01460000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // 当前/上x结算日反向视在最大需量及发生时间
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
***************************************************/  

/***********************************************************变量****************************************************/                                         
                                           
    {_PDI_A_VOL, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.##|V",      {    // A相电压，2位小数，3个字节,HUCK扩充
                                           .phase     = 1, 
                                           .voltage   = 1,}},
    
    {_PDI_B_VOL, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.##|V",      {    // B相电压，2位小数，3个字节,HUCK扩充
                                           .phase     = 2, 
                                           .voltage   = 1,}},
                                           
    {_PDI_C_VOL, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.##|V",      {    // C相电压，2位小数，3个字节,HUCK扩充
                                           .phase     = 3, 
                                           .voltage   = 1,}},                                              

    {_PDI_A_CUR, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|A",    {    // A相电流，4位小数，4个字节,HUCK扩充
                                           .phase     = 1, 
                                           .current   = 1,}},

    {_PDI_B_CUR, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|A",    {    // B相电流，4位小数，4个字节,HUCK扩充
                                           .phase     = 2,    
                                           .current   = 1,}},
                                           
    {_PDI_C_CUR, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|A",    {    // C相电流，4位小数，4个字节,HUCK扩充
                                           .phase     = 3, 
                                           .current   = 1,}},
                                           
    {0x02030000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "XXX#.####|kW",  {    // 有功功率
                                           .active    = 1,
                                           .total     = 1,
                                           .power     = 1,}},
    
    {0x02040000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "XXX#.####|kvar",  {   //无功功率
                                           .reactive  = 1,
                                           .total     = 1,
                                           .power     = 1,}},
    
    {0x02050000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "XXX#.####|kVA",   {   // 视在功率
                                           .total     = 1, 
                                           .power     = 1,}},
    
    {0x02060000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "X#.###|",          {    // 功率因数总
                                           .total     = 1,
                                           .factor    = 1,}},
    
    {_PDI_A_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // A 相角，2位小数，3个字节,HUCK扩充
                                           .phase     = 1, 
                                           .angle     = 1,}},
  

    {_PDI_B_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // B 相角，2位小数，3个字节,HUCK扩充
                                           .phase     = 2, 
                                           .angle     = 1,}},
                                           
    {_PDI_C_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // C 相角，2位小数，3个字节,HUCK扩充
                                           .phase     = 3, 
                                           .angle     = 1,}},
                                           
    {_PDI_SUM_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // 总相角
                                           .total     = 1, 
                                           .angle     = 1,}},                                           
    /*                                       
    {0x02080100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // 电压波形失真度
                                           .phase     = 1,}},
    {0x02080200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // 电压波形失真度
                                           .phase     = 2,}},
    {0x02080300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // 电压波形失真度
                                           .phase     = 3,}},
    
    {0x02090100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // 电流波形失真度
                                           .phase     = 1,}},                                                       
                                           
    {0x02090200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // 电流波形失真度
                                           .phase     = 2,}},                
                                           
    {0x02090300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // 电流波形失真度
                                           .phase     = 3,}},                    
                                                                  
    {0x160000, 0x020A0100, {{.GroupFlag=GROUP_HARMO,.BytePos=0},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "X#.##|",        {    // 电压谐波含量
                                           .voltage     = 1,}},
    
    {0x160000, 0x020B0100, {{.GroupFlag=GROUP_HARMO,.BytePos=0},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "X#.##|",        {    // 电流谐波含量
                                           .current     = 1,}},   
    
    
    {0x02800001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",    {    // 零线电流
                                           .current   = 1,}}, 
                                           
    */
    {0x02800002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|Hz",     {.total     = 0,}}, // 当前频率
    
    {0x02800003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",    {.total     = 1,    // 一分钟有功总平均功率
                                           .active    = 1, 
                                           .power     = 1,}},
                                           
    {0x02800004, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",    {.thismonth     = 1,    // 当前有功需量
                                           .active    = 1, 
                                           .demand     = 1,}},
   
    {0x02800005, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kvar",    {.thismonth    = 1,    // 当前无功需量
                                           .reactive    = 1, 
                                           .demand     = 1,}},
  
    {0x02800006, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kVA",    {.thismonth    = 1,    // 当前视在需量
                                           .demand     = 1,}},
  
    //{0x02800007, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|",    {.total     =0}},     //表内温度
  
    {0x02800008, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|V",   {.total     =0}},   //时钟电池电压(内部)

  
    {0x02800009, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|V",   {.total     =0}},    //抄表电池电压(外部)
  
    {0x0280000A, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXXXX#|",  {.total     =0}},   // 内部电池工作时间
    
    
    

/*                                        
    {0x03020000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x03030000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 过压总次数，总累计时间
                                           .total     = 0,}},
    {0x03040000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相断相总次数，总累计时间
                                           .total     = 0,}},
    {0x03050000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //全失压总次数，总累计时间
                                           .total     = 0,}},
    
*/  
    {0x03060000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //辅助电源失电总次数，总累计时间
                                           .total     = 0,}},
                                           
/*                                      
    {0x03070000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x03080000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x03090000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},                                       
    {0x030A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x030B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x030C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},                                       
    {0x030D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x030E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x030F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},                                      
                                           
*/                                         

    {0x03110000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",       {    //掉电总次数，3字节
                                           .total     = 0,}},
                                           
    {0x03110001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",      {    //上n次掉电发生时刻，结束时刻
                                           .total     = 0,}},
                                           
    {0x03300000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //编程总次数,，3字节
                                           .total     = 0,}},
   
    {0x03300001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",      {    //（上1次）编程记录：
                                           .total     = 0,}},
                                           
                                           
    {0x03300100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //电表清零总次数,，3字节
                                           .total     = 0,}},
                                           
    {0x03300200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //需量清零总次数,，3字节
                                           .total     = 0,}},

    {0x03300300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //事件清零总次数(包括总清及分项清),，3字节
                                           .total     = 0,}},
                                           
    
    {0x03300400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    // 校时总次数,，3字节
                                           .total     = 0,}},                                        
                                           
    {0x03300500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //时段表编程总次数，3字节
                                           .total     = 0,}},
    {0x03300600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //时区表编程总次数，3字节
                                           .total     = 0,}},
    {0x03300700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //周休日编程总次数，3字节
                                           .total     = 0,}},
    {0x03300800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //节假日编程总次数，3字节
                                           .total     = 0,}},
    {0x03300900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //有功组合方式编程总次数，3字节
                                           .total     = 0,}},
    {0x03300A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //无功组合方式1编程总次数，3字节
                                           .total     = 0,}},                                       
    {0x03300B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //无功组合方式2编程总次数，3字节
                                           .total     = 0,}},
    {0x03300C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //结算日编程总次数，3字节
                                           .total     = 0,}},
/* 
    {0x03300D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //开表盖总次数，3字节
                                           .total     = 0,}},
    {0x03300E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //开端钮盒总次数，3字节
                                           .total     = 0,}}, 
*/

  /*************************************************************参变量*******************************************************************/ 

#if LCD_PROPERTY==LCD_SD_ZXW  ||  LCD_PROPERTY==LCD_GW_ZXW 
    {0x04000101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "###### ?#|",    {.time      = 1,}}, // 当前日期周次(年:月:日 周)
#else
    {0x04000101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "#20###### ?#|",    {.time      = 1,}}, // 当前日期周次(年:月:日 周)
#endif

    {0x04000102, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##:##|",         {.time      = 1,}}, // 时间(时:分:秒)
    {0x04000103, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",               {.total     = 0,}}, // 最大需量周期
    {0x04000104, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",               {.total     = 0,}}, // 滑差时间
    {0x04000105, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",             {.total     = 0,}}, // 脉冲宽度
    {0x04000106, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 1,}}, // 两套时区表切换时间(年：月：日：时：分)
    {0x04000107, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 1,}}, // 两套日时区表切换时间(年：月：日：时：分)
    
    //预付费扩展： 04000108
    {0x04000108, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 0,}}, // 两套费率电价切换时间(年：月：日：时：分)
    {0x04000109, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 0,}}, // 两套阶梯切换时间(年：月：日：时：分)
    
    
    {0x04000201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, //年时区数
    {0x04000202, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, //日时段表数
    {0x04000203, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // 日时段数
    {0x04000204, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // 费率数
    {0x04000205, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",    {.total   = 0,}}, // 公共假日数
    //{0x04000206, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // 谐波数目
    {0x04000207, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // 阶梯数
   
    {0x04000301, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //自动循环显示屏数
    {0x04000302, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //自动循环显示时间
    {0x04000303, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //显示电能小数位
    {0x04000304, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, // 显示功率(最大需量)小数位
    {0x04000305, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //按键循环显示屏数
    {0x04000306, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {.total     = 0,}}, // 电流互感器变比
    {0x04000307, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {.total     = 0,}}, //电压互感器变比
    
    {0x04000401, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //通信地址
    {0x04000402, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //表号
    
    {0x04000403, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //资产管理编码(ASCII码)
    {0x04000404, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //额定电压(ASCII码)
    {0x04000405, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //额定电流(ASCII码)
    {0x04000406, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //最大电流(ASCII码)
    {0x04000407, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",  {.total      = 0,}}, //有功准确度等级(ASCII码)
    {0x04000408, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",  {.total      = 0,}}, //无功准确度等级(ASCII码)
    
    {0x04000409, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",    {.total      = 0,}}, //电表有功常数
    {0x0400040A, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",    {.total      = 0,}}, //电表无功常数
    
    {0x0400040B, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //电表型号(ASCII码)
    {0x0400040C, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //生产日期(ASCII码)
    {0x0400040D, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //协议版本号(ASCII码)
    {0x0400040E, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //客户编号

/*
    {0x04000501, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字1
    {0x04000502, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字2
    {0x04000503, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字3
    {0x04000504, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字4
    {0x04000505, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字5
    {0x04000506, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字6
    {0x04000507, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //电表运行状态字7
 
    {0x04000601, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}}, //有功组合方式特征字
    {0x04000602, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}}, //无功组合方式1特征字
    {0x04000603, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}}, //无功组合方式2特征字
    
    
    
*/    
   
    {0x04000701, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //远红外波特率
    {0x04000702, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //吸附红外波特率
    {0x04000703, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //通信口1波特率
    {0x04000704, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //通信口2波特率
    {0x04000705, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //通信口3波特率
    
    {0x04000801, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //周休日特征字
    {0x04000802, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //周休日采用的日时段表号
    
    {0x04000901, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //负荷曲线模式字
    {0x04000902, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //定时冻结数据模式字
    {0x04000903, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //瞬时冻结数据模式字
    {0x04000904, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //约定冻结数据模式字
    {0x04000905, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //整点冻结数据模式字
    {0x04000906, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //日冻结数据模式字
    
    
   
    {0x04000A01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##:##:##|tm",   {.total      = 0,}}, //负荷曲线记录起始时间
    {0x04000A02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //第1类负荷曲线记录间隔时间
    {0x04000A03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //第2类负荷曲线记录间隔时间
    {0x04000A04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //第3类负荷曲线记录间隔时间
    {0x04000A05, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //第4类负荷曲线记录间隔时间
    {0x04000A06, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //第5类负荷曲线记录间隔时间
    {0x04000A07, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //第6类负荷曲线记录间隔时间
    
    {0x04000B01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|tm",   {.total      = 0,}}, //每月第1结算日
    {0x04000B02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|tm",   {.total      = 0,}}, //每月第2结算日
    {0x04000B03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|tm",   {.total      = 0,}}, //每月第3结算日
 
 /*
    {0x04000D01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A相电压铁损系数
                             .phase     = 1, 
                            .total      = 0,}}, 
    {0x04000D02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A相电流铁损系数
                             .phase     = 1, 
                            .total      = 0,}}, 
    {0x04000D03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A相电压铜损系数
                             .phase     = 1, 
                            .total      = 0,}}, 
    {0x04000D04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A相电流铜损系数
                             .phase     = 1, 
                            .total      = 0,}}, 
                            
    {0x04000D05, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B相电压铁损系数
                             .phase     = 2, 
                            .total      = 0,}}, 
    {0x04000D06, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B相电流铁损系数
                             .phase     = 2, 
                            .total      = 0,}}, 
    {0x04000D07, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B相电压铜损系数
                             .phase     = 2, 
                            .total      = 0,}}, 
    {0x04000D08, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B相电流铜损系数
                             .phase     = 2, 
                            .total      = 0,}},   
    {0x04000D09, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C相电压铁损系数
                             .phase     = 3, 
                            .total      = 0,}}, 
    {0x04000D0A, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C相电流铁损系数
                             .phase     = 3, 
                            .total      = 0,}}, 
    {0x04000D0B, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C相电压铜损系数
                             .phase     = 3, 
                            .total      = 0,}}, 
    {0x04000D0C, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C相电流铜损系数
                             .phase     = 3, 
                            .total      = 0,}},                        

*/
    {0x04000E01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",  {.total    = 0,}},  //正向有功功率上限
    {0x04000E02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW", {.total    = 0,}},  //反向有功功率上限		
    {0x04000E03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#0|V",   {.total      = 0,}}, //电压上限
    {0x04000E04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#0|V",   {.total      = 0,}}, //电压下限
    
    {0x04000F01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //报警电量1限值
    {0x04000F02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //报警电量2限值
    {0x04000F03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //囤积电量限值
    {0x04000F04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //透支电量限值
    
    {0x04001001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //报警金额1限值
    {0x04001002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //报警金额2限值
    {0x04001003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //透支金额限值
    {0x04001004, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //囤积金额限值
    {0x04001005, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //合闸允许金额限值
    
    {0x04001101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.voltage      = 0,}}, //电表运行特征字1
    {0x04001201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|",   {.total      = 0,}}, //整点冻结起始时间
    {0x04001202, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}},  //整点冻结时间间隔
    {0x04001203, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|",   {.total      = 0,}}, //日冻结时间
    
    {0x04001301, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}},  //无线通信在线及信号强弱指示
    
    {0x04001401, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}},  //跳闸延时时间（NNNN为跳闸前告警时间）
    {0x04001402, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}},  //合闸延时时间（NNNN为合闸通电前告警时间）

    {0x04010000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}},              "|",   {.total      = 0,}},  //第1套时区表数据
    {0x04010001, {{.GroupFlag=GROUP_DATE,.BytePos=0},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //第1套第n日时段表数据：
    
    {0x04020000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}},              "|",   {.total      = 0,}}, //第2套时区表数据
    {0x04020001, {{.GroupFlag=GROUP_DATE,.BytePos=0},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //第2套第n日时段表数据：
    
    {0x04030001, {{.GroupFlag=GROUP_DATE,.BytePos=0},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}},  //第1公共假日日期及日时段表号

    {0x04050101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //第一套费率电价1~63
    {0x04050201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //第二套费率电价1~63
    
    
    {0x04060101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //第一套第1阶梯值
    {0x04060201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //第一套阶梯电价1
    {0x04060101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //第二套第1阶梯值
    {0x04060201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //第二套阶梯电价1
    
    {0x04800001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //厂家软件版本号(ASCII码)
    {0x04800002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //厂家硬件版本号(ASCII码)
    {0x04800003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //厂家编号(ASCII码)
    
    {0x04090101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //失压事件电压触发上限
    {0x04090102, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //失压事件电压触发下限
    {0x04090103, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",   {.total      = 0,}}, //失压事件电流触发下限
    {0x04090104, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //失压事件判定延时时间
    
    {0x04090201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //欠压事件电压触发上限
    {0x04090202, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //欠压事件判定延时时间
    
    {0x04090301, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //过压事件电压触发上限
    {0x04090302, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //过压事件判定延时时间
    
    {0x04090401, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //断相事件电压触发上限
    {0x04090402, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //断相事件电压触发下限
    {0x04090403, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //断相事件判定延时时间
    
    {0x04090501, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",   {.total      = 0,}}, //电压不平衡率限值
    {0x04090502, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //电压不平衡率判定延时时间
    
    
    {0x04090601, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|V",   {.total      = 0,}}, //电流不平衡率限值
    {0x04090602, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //电流不平衡率判定延时时间



    {0x04090701, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //失流事件电压触发上限
    {0x04090702, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",   {.total      = 0,}}, //失流事件电压触发下限
    {0x04090703, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",   {.total      = 0,}}, //失流事件电流触发下限
    {0x04090704, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //失流事件判定延时时间

    {0x04090801, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X##.#|A",   {.total      = 0,}}, //过流事件电流触发下限
    {0x04090802, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}},  //过流事件判定延时时间

    {0x04090901, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //断流事件电压触发下限
    {0x04090902, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //断流事件电流触发上限
    {0x04090903, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //断流事件判定延时时间
    
    {0x04090A01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",   {.total      = 0,}}, //潮流反向事件有功功率触发下限
    {0x04090A02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}},  //潮流反向事件判定延时时间
    
    {0x04090B01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",   {.total      = 0,}}, //过载事件有功功率触发下限
    {0x04090B02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}},  //过载事件判定延时时间
    
    
    {0x04090C01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //电压考核上限
    {0x04090C02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //电压考核下限
    
    
    {0x04090D01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",   {.total      = 0,}}, //有功需量超限事件需量触发下限
    {0x04090D02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kvar",   {.total      = 0,}}, //无功需量超限事件需量触发下限
    {0x04090D03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //需量超限事件判定延时时间
    
    {0x04090E01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.###|",   {.total      = 0,}}, //总功率因数超下限阀值
    {0x04090E02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //总功率因数超下限判定延时时间
    
    
    {0x04090F01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",   {.total      = 0,}}, //电流严重不平衡限值
    {0x04090F02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //电流严重不平衡触发延时时间
    
    
    {DI_START_VOLT, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#|",   {.total      = 0,}}, //临界电压 ％
    
    
/*************************************************************冻结数据标识编码表*******************************************************************/ 
/*
    {0x05000001, {{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //上n次定时冻结时间,YYMMDDhhmm,5字节
    {0x05010001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //上1次定时冻结时间,YYMMDDhhmm,5字节
    {0x05010002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //上2次定时冻结时间,YYMMDDhhmm,5字节
    {0x05010003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //上3次定时冻结时间,YYMMDDhhmm,5字节
    {0x05020001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //两套时区表切换时间,YYMMDDhhmm,5字节
    {0x05030001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //上1次两套日时段表切换时间,YYMMDDhhmm,5字节
    {0x05030002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //上2次两套日时段表切换时间,YYMMDDhhmm,5字节
*/   
 
/*************************************************************扩展数据编码**************************************************************************/
  /*
    {PDI_CUR_RATE_SCHEME,        {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //当前年时区方案
    {PDI_CUR_YEAR_PERIOD,        {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //当前年时区号
    {PDI_CUR_DATE_TABLE_SCHEME,  {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //当前日时段表方案
    {PDI_CUR_DATE_TABLE,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //当前日时段表号
    {PDI_CUR_DATE_PERIOD,        {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //当前日时段号
    {PDI_CUR_RATE,               {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},          //当前费率
   
    {SDI_MODEWORD_1,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //扩展模式字1
    {SDI_MODEWORD_2,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //扩展模式字2
    {SDI_MODEWORD_3,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //扩展模式字3
    {SDI_MODEWORD_4,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //扩展模式字4
    {SDI_MODEWORD_5,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //扩展模式字5
*/

    {_SDI_ADJ_METER_PARA_STATUS,      {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}},       //参数状态控制命令
    {DI_P_U_I_SPEC,      {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "######|",   {.total      = 0,}},               //脉冲常数规格、电压规格、电流规格




    {PDI_CUR_POS_ACTIVE_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kW",    {.thismonth     = 1,    // 当前正向有功需量
                                           .positive  = 1,
                                           .active    = 1, 
                                           .demand    = 1,}},

    {PDI_CUR_NEG_ACTIVE_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kW",    {.thismonth     = 1,    // 当前反向有功需量
                                           .negative  = 1,
                                           .active    = 1, 
                                           .demand    = 1,}},
                                           
    {PDI_CUR_COMB1_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //当前组合无功1需量
                                           .positive  = 1,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                           
   
    {PDI_CUR_COMB2_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //当前组合无功2需量
                                           .negative  = 1,
                                           .reactive  = 1, 
                                           .demand    = 1,}},
   
    {PDI_CUR_QUAD1_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //当前第一象限无功需量
                                           .quadrant  = 1,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        


    {PDI_CUR_QUAD2_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //当前第二象限无功需量
                                           .quadrant  = 2,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        
                                           
    {PDI_CUR_QUAD3_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //当前第三象限无功需量
                                           .quadrant  = 3,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        
                                                                                      
    {PDI_CUR_QUAD4_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //当前第四象限无功需量
                                           .quadrant  = 4,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        
                                                                                     
                                           
/*************************************************************扩展数据编码:预付费**********************************************************************/
    
   {0x00900100,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //当前）剩余电量
                                         .thismonth  = 1,
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x00900101,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //当前）透支电量
                                         .thismonth  = 1,
                                         .energy     = 1,}},
   {0x00900200,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{      //当前）剩余金额
                                         .thismonth  = 1,
                                         .shenyu     = 1,
                                         .jine     = 1,}},
   {0x00900201,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{      //当前）透支金额
                                         .thismonth  = 1,
                                         .jine     = 1,}},
                                         
   {0x000B0000,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //当前结算周期组合有功总累计用电量
                                         .thismonth  = 0,}},
                                         
   {0x000B0001,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //上1结算周期组合有功总累计用电量
                                         .thismonth  = 0,}},
                                                                        
   {0x0280000B,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{      //当前阶梯电价
                                         .thismonth  = 1,
                                         .jieti     = 1,
                                         .dianjia   = 1,}},
                                         
                                         
   {0x03320101,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",{      //上1～10次购电日期
                                         .lasttime  = 1}},   
   {0x03320201,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXX#|",{          //上1～10次次购电后总购电次数
                                         .lasttime  = 1}},                                       
   {0x03320301,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //上1～10次购电量
                                         .lasttime      = 1,  
                                         .energy     = 1,}},
   
   {0x03320401,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //上1～10次购电前剩余电量
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x03320501,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //上1～10次购电后剩余电量
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x03320601,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //上1～10次购电后累计购电量
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .energy     = 1,}},
                                         
                                         
   {0x03330101,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",{      //上1～10次购电日期
                                         .lasttime      = 1}},                                          
     
   {0x03330201,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXX#|",{          //上1～10次次购电后总购电次数
                                          .lasttime      = 1,  
                                          .thismonth  = 1}},   
                                         
   {0x03330301,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //上1～10次购电金额
                                         .lasttime      = 1,  
                                         .jine     = 1,}},   
   
   {0x03330401,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //上1～10次购电前剩余金额
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .jine     = 1,}},                                          
   {0x03330501,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //上1～10次购电后剩余金额
                                         .lasttime      = 1,   
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x03330601,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //上1～10次购电后累计购电金额
                                         .lasttime      = 1,     
                                         .shenyu     = 1,
                                         .energy     = 1,}},      
                                         
   {0x00900200,{{.GroupFlag=GROUP_NO,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //当前剩余金额
                                         .lasttime      = 1,     
                                         .shenyu     = 1,
                                         .jine     = 1,}},  
                                         
   
   {PDI_CUR_RATE1_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前尖费率电价
                                         .thismonth    = 1,  
                                         .tariff       = 1,  
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},  
   {PDI_CUR_RATE2_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前峰费率电价
                                         .thismonth    = 1,  
                                         .tariff       = 2,                                          
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},                                       
   {PDI_CUR_RATE3_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前平费率电价
                                         .thismonth    = 1,  
                                         .tariff       = 3,                                         
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},       
   {PDI_CUR_RATE4_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前谷费率电价
                                         .thismonth    = 1,  
                                         .tariff       = 4, 
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},       
                                         
   {PDI_CUR_STEP1_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前阶梯1电价
                                         .thismonth  = 1,                                    
                                         .jieti      = 1, 
                                         .times      = 1, 
                                         .dianjia     = 1,}},  
   {PDI_CUR_STEP2_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前阶梯2电价
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 2, 
                                         .dianjia     = 1,}},                                        
   {PDI_CUR_STEP3_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前阶梯3电价
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 3, 
                                         .dianjia     = 1,}},  
   {PDI_CUR_STEP4_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前阶梯4电价
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 4, 
                                         .dianjia     = 1,}},
    
   {PDI_CUR_STEP5_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //当前阶梯5电价
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 5, 
                                         .dianjia     = 1,}},
                                         
   {PDI_CUR_STEP1_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //当前阶梯1电量
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,  
                                         .times      = 1, 
                                         .energy     = 1,}},  
   {PDI_CUR_STEP2_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //当前阶梯2电量
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,  
                                         .times      = 2, 
                                         .energy     = 1,}},                                        
   {PDI_CUR_STEP3_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //当前阶梯3电量
                                         .thismonth  = 1,       
                                         .jieti      = 1,   
                                         .times      = 3, 
                                         .energy     = 1,}},  
   {PDI_CUR_STEP4_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //当前阶梯4电量
                                         .thismonth  = 1,       
                                         .jieti      = 1,   
                                         .times      = 4, 
                                         .energy     = 1,}},                                      
                                         
                                         
 //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------- 事件记录：失压数据块-----------------------------------------------------------
    
    
    {0x10000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相失压总次数，总累计时间
                                           .total     = 0,}},
    {0x10000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相失压总累计时间
                                           .total     = 0,}},    
                 
    {0x10000101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",      {    //最近1次失压发生时刻
                                           .total     = 0,}},
    {0x10000201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",      {    //最近1次失压结束时刻
                                           .total     = 0,}},                                            
  
    {0x10000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相失压发生时刻
                                           .lasttime     = 1}}, 
    {0x10000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相失压发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},
    {0x10000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},

/*
    {0x10000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x10000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x10000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x10000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x10000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相失压发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x10000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相失压发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x10000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相失压发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x10000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x10000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相失压发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x10000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x10001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x10001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相失压发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x10001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相失压发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x10001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相失压发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x10001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x10001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相失压发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x10001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x10001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失压发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x10001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相失压发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x10001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相失压发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x10001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相失压发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x10001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x10002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相失压发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x10002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相失压期间总安时数
                                           .lasttime     = 1}}, 
                                           
    {0x10002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相失压期间A相安时数
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x10002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相失压期间B相安时数
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x10002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相失压期间C相安时数
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
*/    
    {0x10002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相失压结束时刻
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                        
    {0x10002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x10002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},  
/*
    {0x10002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x10002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x10002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x10002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x10002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x10002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x10002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x10002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x10003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x10003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失压结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失压时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
                                   
//----------------------------------------------------------- 事件记录：欠压数据块-----------------------------------------------------------
                                          
    {0x11000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C相欠压总次数
                                          .total     = 0,}},
                                          
    {0x11000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C相欠压总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x11000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相欠压发生时刻
                                           .lasttime     = 1}}, 
    {0x11000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相欠压发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                        
    {0x11000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x11000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x11000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x11000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x11000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相欠压发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x11000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相欠压发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x11000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相欠压发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x11000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x11000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相欠压发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x11000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x11001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x11001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相欠压发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x11001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相欠压发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x11001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相欠压发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x11001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x11001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相欠压发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x11001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x11001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相欠压发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x11001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相欠压发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x11001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相欠压发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x11001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相欠压发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x11001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x11002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相欠压发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x11002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相欠压期间总安时数
                                           .lasttime     = 1}}, 
                                           
    {0x11002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相欠压期间A相安时数
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x11002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相欠压期间B相安时数
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x11002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相欠压期间C相安时数
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
    {0x11002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相欠压结束时刻
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                           
    {0x11002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻正向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x11002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻反向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x11002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x11002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x11002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x11002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x11002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x11002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x11002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x11002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x11003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x11003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相欠压结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相欠压时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
                                          
//----------------------------------------------------------- 事件记录：过压数据块-----------------------------------------------------------
                                          
    {0x12000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C相过压总次数
                                          .total     = 0,}},
                                          
    {0x12000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C相过压总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x12000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相过压发生时刻
                                           .lasttime     = 1}}, 
    {0x12000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相过压发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x12000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x12000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x12000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相过压发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x12000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相过压发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x12000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相过压发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x12000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x12000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相过压发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x12000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x12001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相过压发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x12001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相过压发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x12001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相过压发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x12001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x12001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相过压发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x12001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x12001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过压发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相过压发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x12001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相过压发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x12001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相过压发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x12001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x12002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相过压发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x12002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相过压期间总安时数
                                           .lasttime     = 1}}, 
                                           
    {0x12002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相过压期间A相安时数
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x12002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相过压期间B相安时数
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x12002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相过压期间C相安时数
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
    {0x12002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相过压结束时刻
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                           
    {0x12002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻正向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x12002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻反向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x12002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x12002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x12002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x12002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x12002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x12002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x12002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x12002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x12003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x12003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过压结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过压时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
                                       
 //----------------------------------------------------------- 事件记录：断相数据块-----------------------------------------------------------
                                          
    {0x13000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C相断相总次数
                                          .total     = 0,}},
                                          
    {0x13000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C相断相总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x13000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相断相发生时刻
                                           .lasttime     = 1}}, 
    {0x13000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相断相发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x13000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x13000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x13000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相断相发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x13000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相断相发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x13000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相断相发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x13000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x13000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相断相发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x13000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x13001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相断相发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x13001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相断相发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x13001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相断相发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x13001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x13001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相断相发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x13001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x13001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断相发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相断相发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x13001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相断相发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x13001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相断相发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x13001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x13002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相断相发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x12002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相过压期间总安时数
                                           .lasttime     = 1}}, 
                                           
    {0x13002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相断相期间A相安时数
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x13002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相断相期间B相安时数
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x13002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//上1～10次 A/B/C相断相期间C相安时数
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
    {0x13002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相断相结束时刻
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                           
    {0x13002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻正向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x13002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻反向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x13002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x13002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x13002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x13002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x13002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x13002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x13002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x13002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x13003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x13003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断相结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断相时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                          
  //----------------------------------------------------------- 事件记录：电压逆相序-----------------------------------------------------------
                                          
    {0x14000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电压逆相序总次数
                                          .total     = 0,}},
                                          
    {0x14000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电压逆相序总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x14000100, {{.GroupFlag=GROUP_NO,.BytePos=0},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电压逆相序发生时刻
                                           .lasttime     = 1}}, 
    {0x14000200, {{.GroupFlag=GROUP_NO,.BytePos=0},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻正向有功总电能
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻反向有功总电能
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x14000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x14000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x14000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
   {0x14000A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14000C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x14000E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14001000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x14001200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电压逆相序结束时刻
                                           .lasttime     = 1}}, 
    {0x14001300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x14001500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x14001600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x14001700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14001900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x14001B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14001D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x14001F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14002000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压逆相序结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14002100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14002200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压逆相序结束时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                    
    //-----------------------------------------------------------  事件记录：电流逆相序----------------------------------------------------------- 
                                          
    {0x15000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电流逆相序总次数
                                          .total     = 0,}},
                                          
    {0x15000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电流逆相序总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x15000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电流逆相序发生时刻
                                           .lasttime     = 1}}, 
    {0x15000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x15000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x15000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x15000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x15000A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15000C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x15000E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15001000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x15001200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电流逆相序结束时刻
                                           .lasttime     = 1}}, 
    {0x15001300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x15001500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x15001600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x15001700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15001900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
   {0x15001B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15001D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x15001F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15002000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流逆相序结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15002100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15002200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流逆相序结束时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
   //-----------------------------------------------------------  事件记录：电压不平衡----------------------------------------------------------- 
                                          
    {0x16000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电压不平衡总次数
                                          .total     = 0,}},
                                          
    {0x16000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电压不平衡总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x16000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电压不平衡发生时刻
                                           .lasttime     = 1}}, 
    {0x16000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x16000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x16000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x16000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x16001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.##",  {//上1～10次 电压不平衡最大不平衡率
                                           .lasttime     = 1}}, 
    
    {0x16001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电压不平衡结束时刻
                                           .lasttime     = 1}}, 
                                           
    {0x16001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x16001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x16001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x16002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电压不平衡结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电压不平衡结束时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},


//-----------------------------------------------------------  事件记录：电流不平衡----------------------------------------------------------- 
                                          
    {0x17000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电流不平衡总次数
                                          .total     = 0,}},
                                          
    {0x17000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//电流不平衡总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x17000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电流不平衡发生时刻
                                           .lasttime     = 1}}, 
    {0x17000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x17000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x17000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x17000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
   {0x17000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x17000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x17001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.##",  {//上1～10次 电流不平衡最大不平衡率
                                           .lasttime     = 1}}, 
    
    {0x17001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 电流不平衡结束时刻
                                           .lasttime     = 1}}, 
                                           
    {0x17001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x17001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x17001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x17001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x17001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x17002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 电流不平衡结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 电流不平衡结束时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},



  //----------------------------------------------------------- 事件记录：失流数据块-----------------------------------------------------------
    {0x18000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相失流总次数，总累计时间
                                           .total     = 0,}},
    {0x18000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相失流总累计时间
                                           .total     = 0,}},    
                 
                                          
     
    {0x18000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相失流发生时刻
                                           .lasttime     = 1}}, 
    {0x18000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相失流发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x18000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x18000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x18000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相失流发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x18000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相失流发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x18000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相失流发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x18000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x18000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相失流发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x18000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x18001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相失流发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x18001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相失流发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x18001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相失流发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x18001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x18001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相失流发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x18001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x18001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相失流发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相失流发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x18001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相失流发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x18001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相失流发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x18001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x18002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相失流发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
    
    {0x18002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相失流结束时刻
                                           .lasttime     = 1}}, 
                                                                                  
                                           
    {0x18002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻正向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x18002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻反向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x18002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x18002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x18002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x18002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x18002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x18002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x18002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x18002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相失流结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x18003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x18003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相失流时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    
  //----------------------------------------------------------- 事件记录：过流数据块-----------------------------------------------------------
    {0x19000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相过流总次数，总累计时间
                                           .total     = 0,}},
    {0x19000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相过流总累计时间
                                           .total     = 0,}},    
                 
                                          
     
    {0x19000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相过流发生时刻
                                           .lasttime     = 1}}, 
    {0x19000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相过流发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x19000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x19000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x19000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相过流发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x19000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相过流发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x19000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相过流发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x19000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x19000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相过流发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x19000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x19001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相过流发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x19001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相过流发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x19001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相过流发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x19001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x19001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相过流发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x19001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x19001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相过流发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相过流发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x19001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相过流发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x19001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相过流发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x19001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x19002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相过流发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
    
    {0x19002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相过流结束时刻
                                           .lasttime     = 1}}, 
                                                                                  
                                           
    {0x19002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻正向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x19002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻反向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x19002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x19002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x19002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x19002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x19002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x19002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x19002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x19002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相过流结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x19003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x19003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相过流时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                        
                                          
                                          
    
  //----------------------------------------------------------- 事件记录：断流数据块-----------------------------------------------------------
    {0x1A000101, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相断流总次数，总累计时间
                                           .total     = 0,}},
    {0x1A000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //总/A/B/C 相断流总累计时间
                                           .total     = 0,}},    
                 
                                          
     
    {0x1A000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相断流发生时刻
                                           .lasttime     = 1}}, 
    {0x1A000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相A相断流发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1A000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1A000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1A000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相断流发生时刻A相电压
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x1A000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相断流发生时刻A相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x1A000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相断流发生时刻A相有功功率
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x1A000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流发生时刻A相无功功率
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x1A000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相断流发生时刻A相功率因数
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x1A000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1A001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相断流发生时刻B相电压
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x1A001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相断流发生时刻B相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x1A001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相断流发生时刻B相有功功率
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x1A001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流发生时刻B相无功功率
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x1A001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相断流发生时刻B相功率因数
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x1A001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1A001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 A/B/C相断流发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//上1～10次 A/B/C相断流发生时刻C相电压
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x1A001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//上1～10次 A/B/C相断流发生时刻C相电流
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x1A001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//上1～10次 A/B/C相断流发生时刻C相有功功率
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x1A001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流发生时刻C相无功功率
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x1A002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//上1～10次 A/B/C相断流发生时刻C相功率因数
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
    
    {0x1A002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 A/B/C相断流结束时刻
                                           .lasttime     = 1}}, 
                                                                                  
                                           
    {0x1A002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻正向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x1A002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻反向有功总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x1A002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流结束时刻组合无功1总电能
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x1A002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流结束时刻组合无功2总电能
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x1A002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x1A002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流时刻A相组合无功1电能
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流时刻A相组合无功2电能
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x1A002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x1A002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流时刻B相组合无功1电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流时刻B相组合无功2电能
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x1A002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x1A002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 A/B/C相断流结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流时刻C相组合无功1电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//上1～10次 A/B/C相断流时刻C相组合无功2电能
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                        
                                          
                                          
   //----------------------------------------------------------- 事件记录：潮流反向-----------------------------------------------------------
                                          
    {0x1B000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//潮流反向总次数
                                          .total     = 0,}},
                                          
    {0x1B000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//潮流反向总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x1B000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 潮流反向发生时刻
                                           .lasttime     = 1}}, 
    {0x1B000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1B000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1B000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1B000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x1B001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 潮流反向结束时刻
                                           .lasttime     = 1}}, 
    {0x1B001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1B001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1B001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1B001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 潮流反向结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 潮流反向结束时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
   //----------------------------------------------------------- 事件记录：过载-----------------------------------------------------------
                                          
    {0x1C000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//过载总次数
                                          .total     = 0,}},
                                          
    {0x1C000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//过载总累计时间
                                          .total     = 0,}},                                         
   
   
   
    {0x1C000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 过载发生时刻
                                           .lasttime     = 1}}, 
    {0x1C000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1C000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1C000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1C000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载发生时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载发生时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x1C001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 过载结束时刻
                                           .lasttime     = 1}}, 
    {0x1C001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻正向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻反向有功总电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻组合无功1总电能
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1C001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻组合无功2总电能
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1C001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻A相正向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻A相反向有功电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻A相组合无功1电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻A相组合无功2电能
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻B相正向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻B相反向有功电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻B相组合无功1电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻B相组合无功2电能
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1C001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻C相正向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 过载结束时刻C相反向有功电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻C相组合无功1电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 过载结束时刻C相组合无功2电能
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},                                       
                                          
                                          
                                          
                                          
   //----------------------------------------------------------- 事件记录：跳闸-----------------------------------------------------------
                                          
    {0x1D000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//跳闸总次数
                                          .total     = 0,}},
                                          
       
    {0x1D000100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 跳闸发生时刻
                                           .lasttime     = 1}}, 
                                           
    {0x1D000200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "########|",  {//上1～10次 跳闸发生时操作者代码
                                           .lasttime     = 1}},   
                                                                               
    {0x1D000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 跳闸发生时刻正向有功总电能
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1D000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 跳闸发生时刻反向有功总电能
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1D000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 跳闸发生时刻第1象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1D000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 跳闸发生时刻第2象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 2,}}, 
                                                                             
       
    {0x1D000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 跳闸发生时刻第3象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 3,}}, 
                                           
    {0x1D000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 跳闸发生时刻第4象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 1,}},                                         
   
   //----------------------------------------------------------- 事件记录：合闸-----------------------------------------------------------
                                          
    {0x1E000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//合闸总次数
                                          .total     = 0,}},
                                          
       
    {0x1E000100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 合闸发生时刻
                                           .lasttime     = 1}}, 
                                           
    {0x1E000200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "########|",  {//上1～10次 合闸发生时操作者代码
                                           .lasttime     = 1}},   
                                                                               
    {0x1E000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 合闸发生时刻正向有功总电能
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1E000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 合闸发生时刻反向有功总电能
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1E000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 合闸发生时刻第1象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1E000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 合闸发生时刻第2象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 2,}}, 
                                                                             
       
    {0x1E000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 合闸发生时刻第3象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 3,}}, 
                                           
    {0x1E000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 合闸发生时刻第4象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                           
   //----------------------------------------------------------- 事件记录：总功率因数超下限-----------------------------------------------------------
                                          
    {0x1F000000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//总功率因数超下限总次数
                                          .total     = 0,}},
                                          
    {0x1F000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//总功率因数超下限总累计时间
                                          .total     = 0,}},
                                          
    {0x1F000100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 总功率因数超下限发生时刻
                                           .lasttime     = 1}}, 
                                           
                                                                               
    {0x1F000200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 总功率因数超下限发生时刻正向有功总电能
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1F000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 总功率因数超下限发生时刻反向有功总电能
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1F000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 总功率因数超下限发生时刻第1象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1F000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 总功率因数超下限发生时刻第2象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 2,}}, 
    
    {0x1F000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//上1～10次 总功率因数超下限结束时刻
                                           .lasttime     = 1}}, 
                                           
       
    {0x1F000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 总功率因数超下限结束时刻正向有功总电能
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1F000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//上1～10次 总功率因数超下限结束时刻反向有功总电能
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1F000900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 总功率因数超下限结束时刻第1象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1F000A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//上1～10次 总功率因数超下限结束时刻第2象限无功总
                                           .lasttime    = 1,
                                           .quadrant = 2,}},   

   */
};

#endif
