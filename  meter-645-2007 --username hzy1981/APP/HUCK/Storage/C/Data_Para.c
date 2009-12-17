#define DATA_PARA_C
#include "includes.h"

//#undef Debug_Print
//#define Debug_Print(...)
//#define Debug_Print _Debug_Print
/*
#define IMP_0    0x00 //工厂参数
#define IMP_1    0x01 //重要数据
#define IMP_2    0x02 //重要数据的备份
#define IMP_3    0x03 //普通数据
#define IMP_4    0x04 //事件累计信息
#define IMP_5    0x05 //第0类事件
#define IMP_6    0x06 //第1类事件
#define IMP_5    0x07 //第2类事件
#define IMP_8    0x08 //重要参数
#define IMP_9    0x09 //普通参数
#define IMP_A    0x0A //负荷记录
#define IMP_B    0x0B //掉电存储数据
*/

//#define IMP_LOG_MEM 5//每类重要数据存储的逻辑存储器个数,最大值 

//定义各种数据的存储分布
CONST S_Data_Mem_Map Data_Mem_Map[] =
{
  {IMP_FAC_PARA, {LOG_MEM0, LOG_MEM1, LOG_MEM2, LOG_MEM3, LOG_MEM4}}, //工厂参数,5份存储
  {IMP_IMP_PARA, {LOG_MEM5, LOG_MEM6, LOG_MEM7, LOG_MEM8, LOG_MEM36}}, //重要参数,5份
  //{IMP_NOR_PARA    , {LOG_MEM9, LOG_MEM10, LOG_MEM11, NULL_LOG_MEM, NULL_LOG_MEM}}, //普通参数,3份
  {IMP_IMP_DATA, {LOG_MEM12, LOG_MEM13, LOG_MEM14, LOG_MEM15, NULL_LOG_MEM}}, //重要数据
  {IMP_IMP_BAK_DATA, {LOG_MEM16, LOG_MEM17, LOG_MEM18, NULL_LOG_MEM, NULL_LOG_MEM}}, //重要数据的备份
  //{IMP_NOR_DATA    , {LOG_MEM19, LOG_MEM20, LOG_MEM21, NULL_LOG_MEM, NULL_LOG_MEM}}, //普通数据
  {IMP_HIS_DATA, {LOG_MEM22, LOG_MEM23, LOG_MEM24, NULL_LOG_MEM, NULL_LOG_MEM}}, //历史数据
  {IMP_EVENT_CUMU, {LOG_MEM25, LOG_MEM26, LOG_MEM27, NULL_LOG_MEM, NULL_LOG_MEM}}, //事件累计信息
  {IMP_EVENT0, {LOG_MEM28, LOG_MEM29, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //第0类事件
  {IMP_EVENT1, {LOG_MEM30, LOG_MEM31, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //第1类事件
  {IMP_EVENT2, {LOG_MEM32, LOG_MEM33, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //第2类事件
  {IMP_LOAD_REC, {LOG_MEM34, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //事件记录
  {IMP_PD_DATA, {LOG_MEM35, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}} //掉电数据

}; 

//数据存储映射表
CONST S_Data_Para_Storage_Info Data_Para_Storage[] =
{
  {_SDI_BOOT_FLAG, IMP_IMP_PARA, 4, 1}, //启动标志，表征是否是第一次启动
  //校表相关参数,扩充的-----
  {_SDI_ADJ_METER_PUL_VOL_CUR_SPEC,IMP_FAC_PARA,3,1},//脉冲、电压、电流规格,3字节
  {_SDI_ADJ_METER_PARA_STATUS,IMP_FAC_PARA,1,1},//校表参数状态设置
  {_SDI_ADJ_METER_A_POW,IMP_FAC_PARA,3,12},//ABC三相功率、相位、电压、电流等 
  //---------------------------
  {_SDI_CUR_ENERGY_PD, IMP_PD_DATA, ENERGY_SAVE_SIZE, 1},//IMP_6,ENERGY_SAVE_SIZE,1},//当前电量,掉电存储,平时也定时存储
  {_SDI_CUR_DEMAND_PD, IMP_PD_DATA, sizeof(S_Demand), 1},//掉电只保存总和当前费率需量，即S_Demand_
  {_SDI_CUR_VOLSTAT_PD, IMP_PD_DATA, sizeof(S_VolStat), 1},//当前电压统计数据
  //{_SDI_TOTAL_VOLSTAT_PD, IMP_PD_DATA, sizeof(S_VolStat),1},//总电压检测数据
  {_SDI_LOAD_DATA_INDEX_PD, IMP_PD_DATA, sizeof(S_LoadData_Index),1},//总电压检测数据
  {_SDI_EVENT_DATA_PD, IMP_PD_DATA, sizeof(Event_Data), 1}, //掉电存储事件数据
  {_SDI_SAVE_PD_DATA_TIME, IMP_PD_DATA, 4, 1},//掉电存数过程的时间，单位ms
  //{_SDI_CUR_YEAR_DATE_SCHEME_PD, IMP_PD_DATA, sizeof(S_Cur_Year_Date_Scheme), 1},//当前年时区，日时段方案
  
  {_SDI_LOAD_DATA_INDEX, IMP_IMP_DATA, sizeof(S_LoadData_Index), 1}, //负荷记录当前记录位置
  {_SDI_TIME_BAK, IMP_IMP_DATA, sizeof(S_BCD_Time), 1}, //当前时间的备份
  {_SDI_CUR_SCHEME, IMP_IMP_PARA, sizeof(S_Cur_Scheme), 1},//当前年时区，日时段、费率方案
  
  {_SDI_CUR_ENERGY, IMP_IMP_DATA, ENERGY_SAVE_SIZE, 1}, //当前电量  
  {_SDI_CUR_DEMAND, IMP_IMP_DATA, DEMAND_SAVE_SIZE, 1}, //当前需量  
  {_SDI_CUR_VOLSTAT, IMP_IMP_DATA, sizeof(S_VolStat), 1}, //当前电压统计
  
  //{_SDI_TOTAL_VOLSTAT, IMP_IMP_DATA, sizeof(S_VolStat), 1}, //当前总电压统计
  {_SDI_CUR_ENERGY_BAK0, IMP_IMP_BAK_DATA, ENERGY_SAVE_SIZE, 1}, //电量备份0
  {_SDI_CUR_DEMAND_BAK, IMP_IMP_BAK_DATA, DEMAND_SAVE_SIZE, 1},  //需量备份 
  {_SDI_CUR_ENERGY_BAK1, IMP_IMP_BAK_DATA, ENERGY_SAVE_SIZE, 1},  //电量备份1
  {_SDI_CUR_VOLSTAT_BAK, IMP_IMP_BAK_DATA, sizeof(S_VolStat), 1}, //当前电压统计备份
  {_SDI_CUR_ENERGY_BAK2, IMP_LOAD_REC, ENERGY_SAVE_SIZE, 1},  //电量备份2,该份数据存储到符合dataflash中去
  
  //{_SDI_TOTAL_VOLSTAT_BAK, IMP_IMP_BAK_DATA, sizeof(S_VolStat), 1}, //当前总电压统计备份
  {_SDI_LOAD_DATA_INDEX_BAK, IMP_IMP_DATA, sizeof(S_LoadData_Index), 1}, //负荷记录位置备份

  {_SDI_LAST_SETTLE_ENERGY_DI, IMP_IMP_PARA, 4, 1}, //上13月电量
  {_SDI_LAST_SETTLE_DEMAND_DI, IMP_IMP_PARA, 4, 1}, //上13月最大需量
  {_SDI_LAST_SETTLE_VOLSTAT_DI, IMP_IMP_PARA, 4, 1}, //上3个月电压统计数据
  {_SDI_SETTLE_ENERGY_DATA, IMP_HIS_DATA, ENERGY_SAVE_SIZE, MAX_ENERGY_SETTLE_NUM}, //上13月电量
  {_SDI_SETTLE_DEMAND_DATA, IMP_HIS_DATA, DEMAND_SAVE_SIZE, MAX_DEMAND_SETTLE_NUM}, //上13月最大需量
  {_SDI_SETTLE_VOLSTAT_DATA, IMP_HIS_DATA, sizeof(S_VolStat), MAX_VOLSTAT_SETTLE_NUM}, //上3个月电压统计数据
  {_SDI_LOAD_DATA_TIME_INDEX, IMP_LOAD_REC, 2, LOAD_DATA_TIME_INDEX_NUM},//负荷曲线小时索引
  {_SDI_LOAD_DATA_NEXT_INDEX, IMP_LOAD_REC, 2, LOAD_DATA_NUM}, //负荷数据的下条数据的索引
  {_SDI_LOAD_DATA, IMP_LOAD_REC, LOAD_DATA_SIZE, LOAD_DATA_NUM}, //负荷曲线数据
  
  {_SDI_REMOTE_RELAY_STATUS, IMP_IMP_PARA, sizeof(S_Remote_Ctrl_Switch), 1},//远程拉合闸状态
  {_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, IMP_IMP_PARA, sizeof(S_Pepaid_Power_Ctrl_Switch), 1},//预付费负荷控制拉合闸状态 
  {_SDI_CTRL_STATUS_FLAG, IMP_IMP_PARA, sizeof(S_Ctrl_Status_Flag), 1}, //控制状态的一些标志
  
 //预付费运行时参数
  { _SDI_PREPAID_RUN_STATUS, IMP_IMP_PARA, 1, 1},// (0x0300|EXT_PARA_DATA)//运行状态 数据长度为1
  { _SDI_DISCRETE_INFO, IMP_IMP_PARA, 8, 1}, //离散因子 数据长度为8
  { _SDI_PREPAID_PARA_CARD_VER, IMP_IMP_PARA, 4, 1},// (0x0302|EXT_PARA_DATA)//现场参数设置卡版本号 数据长度为4
  { _SDI_PREPAID_PSW_KIND, IMP_IMP_PARA, 1, 1}, // (0x0303|EXT_PARA_DATA)//密钥类型数据长度为1
  { _SDI_INVALID_CARD_COUNTS, IMP_IMP_PARA, 4, 1}, //非法卡插入次数
  { _SDI_INVALID_COUNTS_AllOW, IMP_IMP_PARA, 1, 1}, //
  { _SDI_FAR_AUTH_DAY_FOLLOW, IMP_IMP_PARA, 4, 1}, //远程认证跟随日
  { _SDI_SINGLE_OR_COMPLEX_USER_KIND, IMP_IMP_PARA, 1, 1}, //用户类型 
  ///////////////////////////////////////////////////////////
  {SDI_BAT_RUN_TIME, IMP_IMP_PARA, 4, 1},  //0x0280000A  //电池工作时间 
  {SDI_DEMAND_PERIOD, IMP_IMP_PARA, 1, 1},  //0x04000103 //需量周期
  {SDI_DEMAND_SLID, IMP_IMP_PARA, 1, 1},  //0x04000104 //滑差时间
  {SDI_ADJ_PULSE_WIDTH, IMP_IMP_PARA, 2, 1},     //0x04000105 //校表脉冲宽度
  {SDI_YEAR_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000106 //年时区切换时间
  {SDI_DATE_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000107 //日时段表切换时间
  {SDI_RATE_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000108 //费率方案切换时间
  {SDI_STEP_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000109 //阶梯方案切换时间
  {SDI_YEAR_PERIOD_NUM, IMP_IMP_PARA, 1, 1},     //0x04000201 //年时区数
  {SDI_DATE_TABLE_NUM, IMP_IMP_PARA, 1, 1},   //0x04000202 //日时段表数
  {SDI_DATE_PERIOD_NUM, IMP_IMP_PARA, 1, 1},     //0x04000203 //日时段数
  {SDI_RATE_NUM, IMP_IMP_PARA, 1, 1},   //0x04000204 //费率数
  {SDI_HOLIDAY_NUM, IMP_IMP_PARA, 2, 1},     //0x04000205 //公共节假日数
  {SDI_HARMONIC_NUM, IMP_IMP_PARA, 1, 1},   //0x04000206 //谐波次数
  {SDI_PREPAID_STEP_NUM, IMP_IMP_PARA, 1,1}, //0x04000207 //预付费阶梯数
  {SDI_AUTO_CYCL_SCREEN_NUM, IMP_IMP_PARA, 1, 1},  //0x04000301 //自动循环显示屏数
  {SDI_SCREEN_SHOW_TIME, IMP_IMP_PARA, 1, 1},    //0x04000302 //没屏显示时间
  {SDI_ENERGY_DECIMAL_NUM, IMP_IMP_PARA, 1, 1}, //0x04000303 //显示电能小数位数
  {SDI_POWER_DECIMAL_NUM, IMP_IMP_PARA, 1, 1},   //0x04000304 //显示功率与需量小数位数
  {SDI_KEY_CYCL_SCREEN_NUM, IMP_IMP_PARA, 1, 1},   //0x04000305 //按键循环显示屏数
  {SDI_CURR_TRANS_RATIO, IMP_IMP_PARA, 3, 1}, //0x04000306 //电流互感器变比
  {SDI_VOLT_TRANS_RATIO, IMP_IMP_PARA, 3, 1}, //0x04000307 //电压互感器变比
  
  {SDI_COMM_ADDR, IMP_IMP_PARA, 6, 1},  //0x04000401 //通信地址
  {SDI_METER_ID, IMP_IMP_PARA, 6, 1},   //0x04000402 //表号
  {SDI_ASSET_ID, IMP_IMP_PARA, 32, 1},  //0x04000403 //资产管理编码
  {SDI_RATED_VOL, IMP_IMP_PARA, 6, 1},  //0x04000404 //额定电压
  {SDI_RATED_CUR, IMP_IMP_PARA, 6, 1},  //0x04000405 //额定电流
  {SDI_MAX_CUR, IMP_IMP_PARA, 6, 1},      //0x04000406 //最大电流
  {SDI_ACTIVE_ACCU, IMP_IMP_PARA, 4, 1},     //0x04000407 //有功准确等级
  {SDI_REACTIVE_ACCU, IMP_IMP_PARA, 4, 1},  //0x04000408 //无功准确等级
  {SDI_ACTIVE_CONST, IMP_IMP_PARA, 3, 1},   //0x04000409 //电表有功常数
  {SDI_REACTIVE_CONST, IMP_IMP_PARA, 3, 1},   //0x0400040A //电表无功常数
  {SDI_METER_TYPE, IMP_IMP_PARA, 10, 1},     //0x0400040B //电表型号
  {SDI_METER_MADE_TIME, IMP_IMP_PARA, 10, 1},    //0x0400040C //电表生产日期
  {SDI_PROTOCOL_VER, IMP_IMP_PARA, 16, 1},  //0x0400040D //电表协议版本号
  {SDI_CUTOMER_ID, IMP_IMP_PARA, 6, 1}, //0x0400040E 客户编号
  //{SDI_HARDWARE_VER, IMP_IMP_PARA, 16, 1},  //0x0400040F //硬件版本号,未使用  
  
  {SDI_ACTIVE_COMB_WORD, IMP_IMP_PARA, 1, 1},    //0x04000601 //有功组合方式特征字
  {SDI_REACTIVE_COMB_WORD_1, IMP_IMP_PARA, 1, 1},  //0x04000602 //无功组合方式特征字1
  {SDI_REACTIVE_COMB_WORD_2, IMP_IMP_PARA, 1, 1},  //0x04000603 //无功组合方式特征字2
  {SDI_FAR_IRAD_BAUD, IMP_IMP_PARA, 1, 1},  //0x04000701 //调制红外远红外速度特征字
  {SDI_NEAR_IRAD_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000702 //接触红外近红外速度特征字
  {SDI_COMM1_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000703 //通信口1速度
  {SDI_COMM2_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000704 //通信口2速度
  {SDI_COMM3_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000705 //通信口3速度
  {SDI_WEEK_REST_DAY, IMP_IMP_PARA, 1, 1},  //0x04000801 //周休日特征字
  {SDI_WEEK_REST_DATE_TABLE, IMP_IMP_PARA, 1, 1},  //0x04000802 //周休日日时段表号
  {SDI_LOAD_REC_WORD, IMP_IMP_PARA, 1, 1},  //0x04000901 //负荷记录模式字
  {SDI_FREEZE_REC_WORD, IMP_IMP_PARA, 1, 5},     //0x04000902 //冻结记录模式字
  {SDI_LOAD_REC_START_TIME, IMP_IMP_PARA, 4, 1},   //0x04000A01 //负荷记录起始时间
  {SDI_LOAD_REC1_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A02 //第一类负荷记录间隔时间
  {SDI_LOAD_REC2_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A03 //第二类负荷记录间隔时间
  {SDI_LOAD_REC3_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A04 //第三类负荷记录间隔时间
  {SDI_LOAD_REC4_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A05 //第四类负荷记录间隔时间
  {SDI_LOAD_REC5_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A06 //第五类负荷记录间隔时间
  {SDI_LOAD_REC6_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A07 //第六类负荷记录间隔时间
  {SDI_MONTH_SETTLE_DAY1, IMP_IMP_PARA, 2, 1},   //0x04000B01 //每月第一结算日
  {SDI_MONTH_SETTLE_DAY2, IMP_IMP_PARA, 2, 1},   //0x04000B02 //每月第二结算日   
  {SDI_MONTH_SETTLE_DAY3, IMP_IMP_PARA, 2, 1},   //0x04000B02 //每月第三结算日
  {SDI_PSW0, IMP_IMP_PARA, 3, 10},     //0x04000C01 //第0级密码
  //#define SDI_PSW1      0x04000C02 //第1级密码
  //#define SDI_PSW2      0x04000C03 //第2级密码
  //#define SDI_PSW3      0x04000C04 //第3级密码
  //#define SDI_PSW4      0x04000C05 //第4级密码
  //#define SDI_PSW5      0x04000C06 //第5级密码
  //#define SDI_PSW6      0x04000C07 //第6级密码
  //#define SDI_PSW7      0x04000C08 //第7级密码
  //#define SDI_PSW8      0x04000C09 //第8级密码
  //#define SDI_PSW9      0x04000C0A //第9级密码

  {SDI_PHASE_A_CONDUC, IMP_IMP_PARA, 2, 12},    //0x04000D01 //A相电导率
  //#define SDI_PHASE_A_SUSCEP   0x04000D02 //A相电纳率
  //#define SDI_PHASE_A_RESIST   0x04000D03 //A相电阻率
  //#define SDI_PHASE_B_CONDUC   0x04000D04 //B相电导率
  //#define SDI_PHASE_B_SUSCEP   0x04000D05 //B相电纳率
  //#define SDI_PHASE_B_RESIST   0x04000D06 //B相电阻率
  //#define SDI_PHASE_C_CONDUC   0x04000D07 //C相电导率
  //#define SDI_PHASE_C_SUSCEP   0x04000D08 //C相电纳率
  //#define SDI_PHASE_C_RESIST   0x04000D09 //C相电阻率

  {SDI_POS_ACTIVE_UP_LIMIT, IMP_IMP_PARA, 3, 1},  //0x04000E01 //正向有功功率上限
  {SDI_NEG_ACTIVE_LOW_LIMIT, IMP_IMP_PARA, 3, 1},   //0x04000E02 //反向有功功率上限
  {SDI_VOL_UP_LIMIT, IMP_IMP_PARA, 2, 1},   //0x04000E03 //电压上限值
  {SDI_VOL_LOW_LIMIT, IMP_IMP_PARA, 2, 1},  //0x04000E04 //电压下限
  
  {SDI_PREPAID_WARN_ENG1, IMP_IMP_PARA, 4, 4}, //报警电量1
  //#define SDI_PREPAID_WARN_ENG2        0x04000F02 //报警电量2
  //#define SDI_PREPAID_HOARD_ENG_LIMIT  0x04000F03 //囤积电量限额
  //#define SDI_PREPAID_OVERDRAFT_ENG_LIMIT 0x04000F04 //透支电量限额  
  {SDI_PREPAID_WARN_MONEY1, IMP_IMP_PARA, 4, 5}, //报警金额1
  //#define SDI_PREPAID_WARN_MONEY2      0x04001002 //报警金额2
  //#define SDI_PREPAID_OVERDRAFT_MONEY_LIMIT 0x04001003 //透支金额限额
  {SDI_METER_RUN_STATUS, IMP_IMP_PARA, 1, 1}, //电表运行状态字
  
  {SDI_HOUR_FREEZE_START_TIME, IMP_IMP_PARA, 5, 1}, //整点冻结起始时间
  {SDI_HOUR_FREEZE_PERIOD, IMP_IMP_PARA, 1, 1},//整点冻结时间间隔
  {SDI_DATE_FREEZE_TIME, IMP_IMP_PARA, 2, 1},//日冻结时间

  {SDI_RELAY_OFF_DELAY, IMP_IMP_PARA, 2, 1},//跳闸延时
  //{SDI_POWER_PULSE, IMP_IMP_PARA, 3,1},         //0x0400E001 //功率负荷脉冲数
  //{SDI_MAX_POWER_CALC_TIME, IMP_IMP_PARA, 1,1},  //0x0400E002 //最大负荷计算时间
  //{SDI_POWER_CTRL_RELAY_SWITCH_LIMIT, IMP_IMP_PARA, 1,1}, //0x0400E003 //过负荷跳闸次数门限

  {SDI_DISP_FEE_DIGS,IMP_IMP_PARA, 1,1},        //0x0400E101 //显示电费小数位

  {SDI_PREPAID_MODEWORD_1,IMP_IMP_PARA, 1,1},   ///0x0400E201 //预付费模式字1
  {SDI_PREPAID_MODEWORD_2,IMP_IMP_PARA, 1,1},   //0x0400E202 //预付费模式字2
  {SDI_PREPAID_MODEWORD_3,IMP_IMP_PARA, 1,1},   //0x0400E203 //预付费模式字3
  
  {SDI_SCHE1_YEAR_TABLE, IMP_IMP_PARA, MAX_YEAR_PERIODS*3, 1},   //0x04010000 //第一套时区表
  {SDI_SCHE1_DATE_TABLE1, IMP_IMP_PARA, MAX_DATE_PERIODS*3, MAX_DATE_TABLES},    //0x04010001 //第一套第一日时段表
  //#define SDI_SCHE1_DATE_TABLE2    0x04010002 //第一套时二日时段表
  //#define SDI_SCHE1_DATE_TABLE3    0x04010003 //第一套时三日时段表
  //#define SDI_SCHE1_DATE_TABLE4    0x04010004 //第一套时四日时段表
  //#define SDI_SCHE1_DATE_TABLE5    0x04010005 //第一套时五日时段表
  //#define SDI_SCHE1_DATE_TABLE6    0x04010006 //第一套时六日时段表
  //#define SDI_SCHE1_DATE_TABLE7    0x04010007 //第一套时七日时段表
  //#define SDI_SCHE1_DATE_TABLE8    0x04010008 //第一套时八日时段表

  {SDI_SCHE2_YEAR_TABLE, IMP_IMP_PARA, MAX_YEAR_PERIODS*3, 1},  //0x04020000 //第二套时区表
  {SDI_SCHE2_DATE_TABLE1, IMP_IMP_PARA, MAX_DATE_PERIODS*3, MAX_DATE_TABLES},   //0x04020001 //第二套第一日时段表
  //#define SDI_SCHE2_DATE_TABLE2    0x04020002 //第二套时二日时段表
  //#define SDI_SCHE2_DATE_TABLE3    0x04020003 //第二套时三日时段表
  //#define SDI_SCHE2_DATE_TABLE4    0x04020004 //第二套时四日时段表
  //#define SDI_SCHE2_DATE_TABLE5    0x04020005 //第二套时五日时段表
  //#define SDI_SCHE2_DATE_TABLE6    0x04020006 //第二套时六日时段表
  //#define SDI_SCHE2_DATE_TABLE7    0x04020007 //第二套时七日时段表
  //#define SDI_SCHE2_DATE_TABLE8    0x04020008 //第二套时八日时段表

  {SDI_HOLIDAY_DATE_TABLE, IMP_IMP_PARA, 4, MAX_YEAR_HOLIDAYS}, //0x04030001 //公共节假日及日时段表号
  {SDI_AUTO_CYCL_SREEN_DATA, IMP_IMP_PARA, SCREEN_ID_LEN, MAX_AUTO_SCREEN_NUM},  //0x04040101 //自动循显数据
  {SDI_KEY_CYCL_SREEN_DATA, IMP_IMP_PARA, SCREEN_ID_LEN, MAX_KEY_SCREEN_NUM},   //0x04040201 //按键循显数据
  
  {SDI_RATE_SCHEME0_0, IMP_IMP_PARA, 4, MAX_RATES},//       0x04050101 //第一套费率参数
  {SDI_RATE_SCHEME1_0, IMP_IMP_PARA, 4, MAX_RATES},//       0x04050201 //第二套费率参数

  {SDI_STEP_SCHEME0_ENG, IMP_IMP_PARA, 4, PREPAID_MAX_STEP},//     0x04060001 //第一套阶梯参数电量
  {SDI_STEP_SCHEME0_MONEY, IMP_IMP_PARA, 4, PREPAID_MAX_STEP + 1},//   0x04060101 //第一套阶梯参数电价
  {SDI_STEP_SCHEME1_ENG, IMP_IMP_PARA, 4, PREPAID_MAX_STEP},//      0x04060201 //第二套阶梯参数电量
  {SDI_STEP_SCHEME1_MONEY, IMP_IMP_PARA, 4, PREPAID_MAX_STEP + 1},//   0x04060301 //第二套阶梯参数电价  
 
  //{SDI_PREPAID_SEQ_NO, IMP_IMP_PARA, 6, 1},//       0x0400EB01 //系统序列号
  //{SDI_PREPAID_USER_NO, IMP_IMP_PARA, 6, 1},//      0x0400EB02 //用户号
  //{SDI_PREPAID_METER_NO, IMP_IMP_PARA, 6, 1},//     0x0400EB03 //表号

  {0x04090101, IMP_IMP_PARA, 2, 2}, //失压电压触发和恢复参数
  {0x04090103, IMP_IMP_PARA, 3, 1}, //失压电流触发参数
  {0x04090104, IMP_IMP_PARA, 1, 1}, //失压判定延时时间
  
  {0x04090201, IMP_IMP_PARA, 2, 1}, //欠压事件触发上限
  {0x04090202, IMP_IMP_PARA, 1, 1}, //欠压时间判定延时时间

  {0x04090301, IMP_IMP_PARA, 2, 1}, //过压事件触发上限
  {0x04090302, IMP_IMP_PARA, 1, 1}, //过压时间判定延时时间
 
  {0x04090401, IMP_IMP_PARA, 2, 1}, //断相事件电压触发上限
  {0x04090402, IMP_IMP_PARA, 3, 1}, //断相事件电流触发上限  
  {0x04090403, IMP_IMP_PARA, 1, 1}, //断相时间判定延时时间

  {0x04090501, IMP_IMP_PARA, 2, 1}, //电压不平衡限值
  {0x04090502, IMP_IMP_PARA, 1, 1}, //电压不平衡判定延时时间
  
  {0x04090601, IMP_IMP_PARA, 2, 1}, //电流不平衡限值
  {0x04090602, IMP_IMP_PARA, 1, 1}, //电流不平衡判定延时时间  
 
  {0x04090701, IMP_IMP_PARA, 2, 1}, //失流事件电压触发下限
  {0x04090702, IMP_IMP_PARA, 3, 2}, //失流事件电流触发上限、下限
  {0x04090704, IMP_IMP_PARA, 1, 1}, //失流事件判定延时时间  
  
  {0x04090801, IMP_IMP_PARA, 2, 1}, //过流事件电流触发下限
  {0x04090802, IMP_IMP_PARA, 1, 1}, //过流事件判定延时时间

  //{0x04090901, IMP_IMP_PARA, 2, 1}, //电流不平衡限值
 
  {0x04090901, IMP_IMP_PARA, 2, 1}, //断流事件电压触发下限
  {0x04090902, IMP_IMP_PARA, 3, 1}, //断流事件电流触发上限  
  {0x04090903, IMP_IMP_PARA, 1, 1}, //断流时间判定延时时间  

  {0x04090A01, IMP_IMP_PARA, 3, 1}, //潮流反向事件有功功率触发下限
  {0x04090A02, IMP_IMP_PARA, 1, 1}, //潮流反向事件判定延时时间

  {0x04090B01, IMP_IMP_PARA, 3, 1}, //过载事件有功功率触发下限
  {0x04090B02, IMP_IMP_PARA, 1, 1}, //过载事件判定延时时间

  {0x04090C01, IMP_IMP_PARA, 2, 2}, //电压考核上限
  //{0x04090C02, IMP_IMP_PARA, 1, 1}, //电压考核下限
  
  //{0x04090D01, IMP_IMP_PARA, 2, 3}, //电压考核上、下限
  //{0x04090D02, IMP_IMP_PARA, 2, 1}, //电压考核下限
  
  {0x04090D01, IMP_IMP_PARA, 3, 2}, //有、无功需量超限事件需量触发下限
  {0x04090D03, IMP_IMP_PARA, 1, 1}, //需量超限事件判定延时时间 

  {0x04090E01, IMP_IMP_PARA, 2, 1}, //总功率因素超下限阀值
  {0x04090E02, IMP_IMP_PARA, 1, 1}, //总功率因数超下限判定延时时间
  
  {0x04090F01, IMP_IMP_PARA, 2, 1}, //电流严重不平衡限值
  {0x04090F02, IMP_IMP_PARA, 1, 1}, //电流严重不平衡触发延时时间
  
  {SDI_HARDWARE_VERSION, IMP_IMP_PARA, 32, 1}, //0x04080002,厂家硬件版本号
 
  //-----------------------------------------------------------------------------------------------
  {SDI_MODEWORD_1, IMP_IMP_PARA, 1, 5}, //0x0E000001 //5个模式字
  /*
  {0x0E000101, IMP_IMP_PARA, 2, 2},
  {0x0E000103, IMP_IMP_PARA, 4, 1},
  {0x0E000104, IMP_IMP_PARA, 1, 1},
  {0x0E000105, IMP_IMP_PARA, 3, 2},
  {0x0E000107, IMP_IMP_PARA, 1, 2},
  {0x0E000109, IMP_IMP_PARA, 3, 1},
  {0x0E00010A, IMP_IMP_PARA, 1, 1},
  {0x0E00010B, IMP_IMP_PARA, 2, 1},
  {0x0E00010C, IMP_IMP_PARA, 1, 3},
  {0x0E00010F, IMP_IMP_PARA, 3, 1},
  {0x0E000110, IMP_IMP_PARA, 3, 1},
  {0x0E000111, IMP_IMP_PARA, 1, 1},
  {0x0E000112, IMP_IMP_PARA, 3, 1},
  {0x0E000113, IMP_IMP_PARA, 1, 1},
  {0x0E000114, IMP_IMP_PARA, 2, 1},  
*/
  {0x0E000108, IMP_IMP_PARA, 1, 1},
  {0x0E000201, IMP_IMP_PARA, 1, 1},//密码错误闭锁次数上限
  {0x0E000202, IMP_IMP_PARA, 2, 4},//密码错误闭锁时间、密码有效时间、密码错误解锁剩余时间、编程有效时间
  //{SDI_PROG_EN_TIME,IMP_IMP_PARA,2,1},//编程有效时间
  {SDI_OUTPUT_MODE, IMP_IMP_PARA, 1, 1},//三合一输出状态（注1）
  {SDI_PERIOD_FREEZE_TIME, IMP_IMP_PARA, 4, 1},//周期冻结时间
  {SDI_ADJ_TIME_COUNTS, IMP_IMP_PARA, 1, 1}, //每日广播校时次数
/*  
  //-----------------------------------------------------------------------------------------------
  //{0x03010000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、失压总次数，总累计时间
  {EC_DI(0x03010000), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//总失压发生时数据
  {EC_DI(0x03010001), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//总失压总数据
  {EC_DI(0x03010100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A相发生时数据
  {EC_DI(0x03010101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A相总数据
  {EC_DI(0x03010200), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x03010201), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x03010300), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x03010301), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  
  {ES_DI(0x03010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03010101), IMP_EVENT1, 131 + 1, LOSS_VOL_NUM}, //前1-10次A相失压期间电能增量
  {ES_DI(0x03010200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03010201), IMP_EVENT1, 131 + 1, LOSS_VOL_NUM}, //前1-10次B相失压期间电能增量
  {ES_DI(0x03010300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03010301), IMP_EVENT1, 131 + 1, LOSS_VOL_NUM}, //前1-10次C相失压期间电能增量
  //{0x03010401, IMP_EVENT1, 100, 10}, //前1-10次AB相失压期间电能增量
  //{0x03010501, IMP_EVENT1, 100, 10}, //前1-10次AC相失压期间电能增量
  //{0x03010601, IMP_EVENT1, 100, 10}, //前1-10次BC相失压期间电能增量
  //{0x03010701, IMP_EVENT1, 100, 10}, //前1-10次ABC相失压期间电能增量
  //{0x03010801, IMP_EVENT1, 100, 10}, //前1-10次全失压期间电能增量
*/
  {EC_DI(0x10000100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//总失压发生时数据
  {EC_DI(0x10000101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//总失压总数据
  {EC_DI(0x10010100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A相发生时数据
  {EC_DI(0x10010101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A相总数据
  {EC_DI(0x10020100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x10020101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x10030100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x10030101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  
  {SDI_LAST_LOSS_VOL_OCCUR_TIME, IMP_EVENT1, 6,1}, //最近一次失压发生时刻
  {SDI_LAST_LOSS_VOL_END_TIME, IMP_EVENT1, 6,1}, //最近一次失压结束时刻
   
  {ES_DI(0x10010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x10010101), IMP_EVENT1, 195 + 1, LOSS_VOL_NUM}, //前1-10次A相失压期间电能增量
  {ES_DI(0x10020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x10020101), IMP_EVENT1, 195 + 1, LOSS_VOL_NUM}, //前1-10次B相失压期间电能增量
  {ES_DI(0x10030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x10030101), IMP_EVENT1, 195 + 1, LOSS_VOL_NUM}, //前1-10次C相失压期间电能增量
/*
  //-----------------------------------------------------------------------------------------------
  //{0x03020000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、欠压总次数，总累计时间
  {EC_DI(0x03020100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020101), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020200), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020201), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020300), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020301), IMP_EVENT_CUMU, 13,1}, 
  
  {ES_DI(0x03020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03020101), IMP_EVENT1, 131 + 1, LOW_VOL_NUM}, //前1-10次A相欠压期间电能增量
  {ES_DI(0x03020200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03020201), IMP_EVENT1, 131 + 1, LOW_VOL_NUM}, //前1-10次B相欠压期间电能增量
  {ES_DI(0x03020300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03020301), IMP_EVENT1, 131 + 1, LOW_VOL_NUM}, //前1-10次C相欠压期间电能增量
  //{0x03020401, IMP_EVENT1, 100, 10}, //前1-10次AB相欠压期间电能增量
  //{0x03020501, IMP_EVENT1, 100, 10}, //前1-10次AC相欠压期间电能增量
  //{0x03020601, IMP_EVENT1, 100, 10}, //前1-10次BC相欠压期间电能增量
  //{0x03020701, IMP_EVENT1, 100, 10}, //前1-10次ABC相欠压期间电能增量
  //{0x03020801, IMP_EVENT1, 100, 10}, //前1-10次全欠压期间电能增量
*/
  {EC_DI(0x11010100), IMP_EVENT_CUMU, 13,1}, //A相欠压发生时总数据
  {EC_DI(0x11010101), IMP_EVENT_CUMU, 13,1}, //A相欠压总数据
  {EC_DI(0x11020100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x11020101), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x11030100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x11030101), IMP_EVENT_CUMU, 13,1}, 
  
  {ES_DI(0x11010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x11010101), IMP_EVENT1, 195 + 1, LOW_VOL_NUM}, //前1-10次A相欠压期间电能增量
  {ES_DI(0x11020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x11020101), IMP_EVENT1, 195 + 1, LOW_VOL_NUM}, //前1-10次B相欠压期间电能增量
  {ES_DI(0x11030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x11030101), IMP_EVENT1, 195 + 1, LOW_VOL_NUM}, //前1-10次C相欠压期间电能增量
/*
  //-----------------------------------------------------------------------------------------------
  //{0x03030000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、过压总次数，总累计时间
  {EC_DI(0x03030100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030301), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x03030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03030101), IMP_EVENT1, 131 + 1, OVER_VOL_NUM}, //前1-10次A相过压期间电能增量
  {ES_DI(0x03030200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03030201), IMP_EVENT1, 131 + 1, OVER_VOL_NUM}, //前1-10次B相过压期间电能增量
  {ES_DI(0x03030300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03030301), IMP_EVENT1, 131 + 1, OVER_VOL_NUM}, //前1-10次C相过压期间电能增量
  //{0x03030401, IMP_EVENT1, 100, 10}, //前1-10次AB相过压期间电能增量
  //{0x03030501, IMP_EVENT1, 100, 10}, //前1-10次AC相过压期间电能增量
  //{0x03030601, IMP_EVENT1, 100, 10}, //前1-10次BC相过压期间电能增量
  //{0x03030701, IMP_EVENT1, 100, 10}, //前1-10次ABC相过压期间电能增量
  //{0x03030801, IMP_EVENT1, 100, 10}, //前1-10次过压期间电能增量
*/ 
  {EC_DI(0x12010100), IMP_EVENT_CUMU, 13,1}, //A相过压发生时总数据
  {EC_DI(0x12010101), IMP_EVENT_CUMU, 13,1}, //A相过压总数据
  {EC_DI(0x12020100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x12020101), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x12030100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x12030101), IMP_EVENT_CUMU, 13,1}, 
  
  {ES_DI(0x12010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x12010101), IMP_EVENT1, 195 + 1, OVER_VOL_NUM}, //前1-10次A相过压期间电能增量
  {ES_DI(0x12020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x12020101), IMP_EVENT1, 195 + 1, OVER_VOL_NUM}, //前1-10次B相过压期间电能增量
  {ES_DI(0x12030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x12030101), IMP_EVENT1, 195 + 1, OVER_VOL_NUM}, //前1-10次C相过压期间电能增量
  //-----------------------------------------------------------------------------------------------
  /*
  //{0x03040000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、全断相总次数，总累计时间
  {EC_DI(0x03040000), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1},//总断相发生时数据
  {EC_DI(0x03040001), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1},//总断相累计数据
  {EC_DI(0x03040100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040200), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040201), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040300), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040301), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  
  {ES_DI(0x03040100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03040101), IMP_EVENT1, 131 + 1, BREAK_VOL_NUM}, //前1-10次A相断相期间电能增量
  {ES_DI(0x03040200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03040201), IMP_EVENT1, 131 + 1, BREAK_VOL_NUM}, //前1-10次B相断相期间电能增量
  {ES_DI(0x03040300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03040301), IMP_EVENT1, 131 + 1, BREAK_VOL_NUM}, //前1-10次C相断相期间电能增量
  //{0x03040401, IMP_EVENT1, 100, 10}, //前1-10次AB相断相期间电能增量
  //{0x03040501, IMP_EVENT1, 100, 10}, //前1-10次AC相断相期间电能增量
  //{0x03040601, IMP_EVENT1, 100, 10}, //前1-10次BC相断相期间电能增量
  //{0x03040701, IMP_EVENT1, 100, 10}, //前1-10次ABC相断相期间电能增量
  //{0x03040801, IMP_EVENT1, 100, 10}, //前1-10次全断相期间电能增量
*/
  {EC_DI(0x13000100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //总断相发生时总数据
  {EC_DI(0x13000101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //总断相总数据
  {EC_DI(0x13010100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //A相断相发生时总数据
  {EC_DI(0x13010101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //A相断相总数据
  {EC_DI(0x13020100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  {EC_DI(0x13020101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  {EC_DI(0x13030100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  {EC_DI(0x13030101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  
  {ES_DI(0x13010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x13010101), IMP_EVENT1, 195 + 1, BREAK_VOL_NUM}, //前1-10次A相断相期间电能增量
  {ES_DI(0x13020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x13020101), IMP_EVENT1, 195 + 1, BREAK_VOL_NUM}, //前1-10次B相断相期间电能增量
  {ES_DI(0x13030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x13030101), IMP_EVENT1, 195 + 1, BREAK_VOL_NUM}, //前1-10次C相断相期间电能增量
//-----------------------------------------------------------------------------------------------
  //{0x03050000, IMP_EVENT_CUMU, 6, 1}, //全失压总次数，总累计时间
  {EC_DI(0x03050000), IMP_EVENT_CUMU, 13, 1},
  {EC_DI(0x03050001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03050000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03050001), IMP_EVENT1, 15 + 1, ALL_LOSS_VOL_NUM}, //全失压发生时刻、电流值、结束时刻
  //-----------------------------------------------------------------------------------------------
  //{0x03060000, IMP_EVENT_CUMU, 6, 1}, //辅助电源失电总次数、总累计时间
  {EC_DI(0x03060000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03060001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03060000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03060001), IMP_EVENT1, 12 + 1, AUX_POWER_DOWN_NUM}, //辅助电源失电发生时刻、结束时刻
/*  
  //-----------------------------------------------------------------------------------------------
  //{0x03070000, IMP_EVENT_CUMU, 6, 1}, //电压逆相序总次数、累计时间
  {EC_DI(0x03070000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03070001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03070000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03070001), IMP_EVENT1, 76 + 1, VOL_REV_SEQ_NUM}, //前1-10次电压逆相序记录
*/
  //-----------------------------------------------------------------------------------------------
  //{0x03070000, IMP_EVENT_CUMU, 6, 1}, //电压逆相序总次数、累计时间
  {EC_DI(0x14000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x14000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x14000100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x14000101), IMP_EVENT1, 140 + 1, VOL_REV_SEQ_NUM}, //前1-10次电压逆相序记录  
  //-----------------------------------------------------------------------------------------------
/*  
  //{0x03080000, IMP_EVENT_CUMU, 6, 1}, //电流逆相序总次数、累计时间
  {EC_DI(0x03080000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03080001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03080000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03080001), IMP_EVENT1, 76 + 1, CUR_REV_SEQ_NUM}, //前1-10次电流逆相序记录
*/ 
  {EC_DI(0x15000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x15000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x15000100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x15000101), IMP_EVENT1, 140 + 1, CUR_REV_SEQ_NUM}, //前1-10次电流逆相序记录
  //------------------------------------------------------------------------------------------------
/*
  //{0x03090000, IMP_EVENT_CUMU, 6, 1}, //电压不平衡
  {EC_DI(0x03090000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03090001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03090000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03090001), IMP_EVENT1, 78 + 1, VOL_UNBALANCE_NUM}, //前1-10次电压不平衡
*/  
  {EC_DI(0x16000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x16000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x16000100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x16000101), IMP_EVENT1, 143 + 1, VOL_UNBALANCE_NUM}, //前1-10次电压不平衡
  //-------------------------------------------------------------------------------------------------
/*
  //{0x030A0000, IMP_EVENT_CUMU, 6, 1}, //电流不平衡
  {EC_DI(0x030A0000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030A0001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x030A0000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030A0001), IMP_EVENT1, 78 + 1, CUR_UNBALANCE_NUM}, //前1-10次电流不平衡
*/
  {EC_DI(0x17000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x17000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x17000100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x17000101), IMP_EVENT1, 143 + 1, CUR_UNBALANCE_NUM}, //前1-10次电流不平衡
  //------------------------------------------------------------------------------------------------
/*  
  //{0x030B0000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、失流总次数，总累计时间
  {EC_DI(0x030B0000), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//总失流发生时数据
  {EC_DI(0x030B0001), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//总失流累计总数据
  {EC_DI(0x030B0100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//A失流发生时数据
  {EC_DI(0x030B0101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//A失流累计总数据 
  {EC_DI(0x030B0200), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x030B0201), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x030B0300), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  {EC_DI(0x030B0301), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  
  {ES_DI(0x030B0100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030B0101), IMP_EVENT1, 115 + 1, LOSS_CUR_NUM}, //前1-10次A相失流期间电能增量
  {ES_DI(0x030B0200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030B0201), IMP_EVENT1, 115 + 1, LOSS_CUR_NUM}, //前1-10次B相失流期间电能增量
  {ES_DI(0x030B0300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030B0301), IMP_EVENT1, 115 + 1, LOSS_CUR_NUM}, //前1-10次C相失流期间电能增量
  //{0x030B0401, IMP_EVENT1, 100, 10}, //前1-10次AB相失流期间电能增量
  //{0x030B0501, IMP_EVENT1, 100, 10}, //前1-10次AC相失流期间电能增量
  //{0x030B0601, IMP_EVENT1, 100, 10}, //前1-10次BC相失流期间电能增量
  //{0x030B0701, IMP_EVENT1, 100, 10}, //前1-10次ABC相失流期间电能增量
  //{0x030B0801, IMP_EVENT1, 100, 10}, //前1-10次全失流期间电能增量
*/
  {EC_DI(0x18000100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//总失流发生时数据
  {EC_DI(0x18000101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//总失流累计总数据
  {EC_DI(0x18010100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//A失流发生时数据
  {EC_DI(0x18010101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//A失流累计总数据 
  {EC_DI(0x18020100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x18020101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x18030100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  {EC_DI(0x18030101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  
  {ES_DI(0x18010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x18010101), IMP_EVENT1, 179 + 1, LOSS_CUR_NUM}, //前1-10次A相失流期间电能增量
  {ES_DI(0x18020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x18020101), IMP_EVENT1, 179 + 1, LOSS_CUR_NUM}, //前1-10次B相失流期间电能增量
  {ES_DI(0x18030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x18030101), IMP_EVENT1, 179 + 1, LOSS_CUR_NUM}, //前1-10次C相失流期间电能增量
/*
  //------------------------------------------------------------------------------------------------
  //{0x030C0000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、过流总次数，总累计时间
  {EC_DI(0x030C0100), IMP_EVENT_CUMU, 13, 1}, //A过流
  {EC_DI(0x030C0101), IMP_EVENT_CUMU, 13, 1},  
  {EC_DI(0x030C0200), IMP_EVENT_CUMU, 13, 1}, //B过流
  {EC_DI(0x030C0201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030C0300), IMP_EVENT_CUMU, 13, 1}, //C过流
  {EC_DI(0x030C0301), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x030C0100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030C0101), IMP_EVENT1, 115 + 1, OVER_CUR_NUM}, //前1-10次A相过流期间电能增量
  {ES_DI(0x030C0200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030C0201), IMP_EVENT1, 115 + 1, OVER_CUR_NUM}, //前1-10次B相过流期间电能增量
  {ES_DI(0x030C0300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030C0301), IMP_EVENT1, 115 + 1, OVER_CUR_NUM}, //前1-10次C相过流期间电能增量
  //{0x030C0401, IMP_EVENT1, 100, 10}, //前1-10次AB相过流期间电能增量
  //{0x030C0501, IMP_EVENT1, 100, 10}, //前1-10次AC相过流期间电能增量
  //{0x030C0601, IMP_EVENT1, 100, 10}, //前1-10次BC相过流期间电能增量
  //{0x030C0701, IMP_EVENT1, 100, 10}, //前1-10次ABC相过流期间电能增量
  //{0x030C0801, IMP_EVENT1, 100, 10}, //前1-10次全过流期间电能增量
*/
  {EC_DI(0x19010100), IMP_EVENT_CUMU, 13, 1}, //A过流
  {EC_DI(0x19010101), IMP_EVENT_CUMU, 13, 1},  
  {EC_DI(0x19020100), IMP_EVENT_CUMU, 13, 1}, //B过流
  {EC_DI(0x19020101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x19030100), IMP_EVENT_CUMU, 13, 1}, //C过流
  {EC_DI(0x19030101), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x19010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x19010101), IMP_EVENT1, 179 + 1, OVER_CUR_NUM}, //前1-10次A相过流期间电能增量
  {ES_DI(0x19020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x19020101), IMP_EVENT1, 179 + 1, OVER_CUR_NUM}, //前1-10次B相过流期间电能增量
  {ES_DI(0x19030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x19030101), IMP_EVENT1, 179 + 1, OVER_CUR_NUM}, //前1-10次C相过流期间电能增量
  //----------------------------------------------------------------------------------------------
/*
 //{0x030D0000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、断流总次数，总累计时间
  {EC_DI(0x030D0100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0301), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x030D0100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030D0101), IMP_EVENT1, 115 + 1, BREAK_CUR_NUM}, //前1-10次A相断流期间电能增量
  {ES_DI(0x030D0200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030D0201), IMP_EVENT1, 115 + 1, BREAK_CUR_NUM}, //前1-10次B相断流期间电能增量
  {ES_DI(0x030D0300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030D0301), IMP_EVENT1, 115 + 1, BREAK_CUR_NUM}, //前1-10次C相断流期间电能增量
  //{0x030D0401, IMP_EVENT1, 100, 10}, //前1-10次AB相断流期间电能增量
  //{0x030D0501, IMP_EVENT1, 100, 10}, //前1-10次AC相断流期间电能增量
  //{0x030D0601, IMP_EVENT1, 100, 10}, //前1-10次BC相断流期间电能增量
  //{0x030D0701, IMP_EVENT1, 100, 10}, //前1-10次ABC相断流期间电能增量
  //{0x030D0801, IMP_EVENT1, 100, 10}, //前1-10次全断流期间电能增量
  //------------------------------------------------------------------------------------------------
*/
  {EC_DI(0x1A010100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A010101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A020100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A020101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A030100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A030101), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x1A010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1A010101), IMP_EVENT1, 179 + 1, BREAK_CUR_NUM}, //前1-10次A相断流期间电能增量
  {ES_DI(0x1A020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1A020101), IMP_EVENT1, 179 + 1, BREAK_CUR_NUM}, //前1-10次B相断流期间电能增量
  {ES_DI(0x1A030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1A030101), IMP_EVENT1, 179 + 1, BREAK_CUR_NUM}, //前1-10次C相断流期间电能增量
/*
  //{0x030E0000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、潮流反向总次数，总累计时间
  {EC_DI(0x030E0000), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//总反向发生时数据
  {EC_DI(0x030E0001), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//总反向累计数据
  {EC_DI(0x030E0100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0200), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0201), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0300), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0301), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  
  {ES_DI(0x030E0100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030E0101), IMP_EVENT1, 76 + 1, TREND_REVERSE_NUM}, //前1-10次A相潮流反向期间电能增量
  {ES_DI(0x030E0200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030E0201), IMP_EVENT1, 76 + 1, TREND_REVERSE_NUM}, //前1-10次B相潮流反向期间电能增量
  {ES_DI(0x030E0300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030E0301), IMP_EVENT1, 76 + 1, TREND_REVERSE_NUM}, //前1-10次C相潮流反向期间电能增量
  //{0x030E0401, IMP_EVENT1, 100, 10}, //前1-10次AB相潮流反向期间电能增量
  //{0x030E0501, IMP_EVENT1, 100, 10}, //前1-10次AC相潮流反向期间电能增量
  //{0x030E0601, IMP_EVENT1, 100, 10}, //前1-10次BC相潮流反向期间电能增量
  //{0x030E0701, IMP_EVENT1, 100, 10}, //前1-10次ABC相潮流反向期间电能增量
  //{0x030E0801, IMP_EVENT1, 100, 10}, //前1-10次全潮流反向期间电能增量
*/
  {EC_DI(0x1B000100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//总反向发生时数据
  {EC_DI(0x1B000101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//总反向累计数据
  {EC_DI(0x1B010100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B010101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B020100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B020101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B030100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B030101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  
  {ES_DI(0x1B010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1B010101), IMP_EVENT1, 140 + 1, TREND_REVERSE_NUM}, //前1-10次A相潮流反向期间电能增量
  {ES_DI(0x1B020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1B020101), IMP_EVENT1, 140 + 1, TREND_REVERSE_NUM}, //前1-10次B相潮流反向期间电能增量
  {ES_DI(0x1B030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1B030101), IMP_EVENT1, 140 + 1, TREND_REVERSE_NUM}, //前1-10次C相潮流反向期间电能增量
  //-----------------------------------------------------------------------------------------------
/*
 /// {0x030F0000, IMP_EVENT_CUMU, 18, 1}, //A、B、C、AB、AC、BC、ABC、过载总次数，总累计时间
  {EC_DI(0x030F0100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0301), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x030F0100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030F0101), IMP_EVENT1, 76 + 1, OVER_LOAD_NUM}, //前1-10次A相过载期间电能增量
  {ES_DI(0x030F0200), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030F0201), IMP_EVENT1, 76 + 1, OVER_LOAD_NUM}, //前1-10次B相过载期间电能增量
  {ES_DI(0x030F0300), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x030F0301), IMP_EVENT1, 76 + 1, OVER_LOAD_NUM}, //前1-10次C相过载期间电能增量
  //{0x030F0401, IMP_EVENT1, 100, 10}, //前1-10次AB相过载期间电能增量
  //{0x030F0501, IMP_EVENT1, 100, 10}, //前1-10次AC相过载期间电能增量
  //{0x030F0601, IMP_EVENT1, 100, 10}, //前1-10次BC相过载期间电能增量
  //{0x030F0701, IMP_EVENT1, 100, 10}, //前1-10次ABC相过载期间电能增量
  //{0x030F0801, IMP_EVENT1, 100, 10}, //前1-10次过载期间电能增量
*/
  {EC_DI(0x1C010100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C010101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C020100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C020101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C030100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C030101), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x1C010100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1C010101), IMP_EVENT1, 140 + 1, OVER_LOAD_NUM}, //前1-10次A相过载期间电能增量
  {ES_DI(0x1C020100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1C020101), IMP_EVENT1, 140 + 1, OVER_LOAD_NUM}, //前1-10次B相过载期间电能增量
  {ES_DI(0x1C030100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1C030101), IMP_EVENT1, 140 + 1, OVER_LOAD_NUM}, //前1-10次C相过载期间电能增量
  //------------------------------------------------------------------------------------------------
  //{0x03310100, IMP_EVENT1, 3, 1}, //拉闸总次数
  {EC_DI(0x1D000100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x1D000101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x1D000100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x1D000101), IMP_EVENT2, 34 + 1, RELAY_OFF_NUM}, //前1-10次拉闸记录
  //------------------------------------------------------------------------------------------------
  //{0x03310200, IMP_EVENT1, 3, 1}, //合闸总次数
  {EC_DI(0x1E000100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x1E000101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x1E000100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x1E000101), IMP_EVENT2, 34 + 1, RELAY_ON_NUM}, //前1-10次合闸记录  
  //------------------------------------------------------------------------------------------------
  //{0x03310200, IMP_EVENT1, 3, 1}, //总功率因素超下限
  {EC_DI(0x1F000100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x1F000101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x1F000100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x1F000101), IMP_EVENT1, 44 + 1, FACTOR_LOW_NUM}, //前1-10次总功率因素超下限  
  //-----------------------------------------------------------------------------------------------
  {0x03100000, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //上1-12月电压检测数据
  {0x03100100, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //上1-12月A相电压检测数据
  {0x03100200, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //上1-12月B相电压检测数据
  {0x03100300, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //上1-12月C相电压检测数据
  //-----------------------------------------------------------------------------------------------
  //{0x03110000, IMP_EVENT_CUMU, 3, 1}, //掉电总次数
  {EC_DI(0x03110000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03110001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03110000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03110001), IMP_EVENT2, 12 + 1, POWER_DOWN_NUM}, //前1-10次掉电发生和结束时刻
  //-----------------------------------------------------------------------------------------------
  //{0x03120000, IMP_EVENT_CUMU, 18, 1}, //需量超限次数
  {EC_DI(0x03120100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120301), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120400), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120401), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120500), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120501), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120600), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120601), IMP_EVENT_CUMU, 13, 1},
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x03120100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03120101), IMP_EVENT2, 20 + 1, POS_ACT_DEMAND_EXCEED_NUM}, //前1-10次正向有功需量超限
  {ES_DI(0x03120200), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03120201), IMP_EVENT2, 20 + 1, NEG_ACT_DEMAND_EXCEED_NUM}, //前1-10次反向有功需量超限
  {ES_DI(0x03120300), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03120301), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //前1-10次第一象限无功需量超限
  {ES_DI(0x03120400), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03120401), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //前1-10次第二象限无功需量超限
  {ES_DI(0x03120500), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03120501), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //前1-10次第三象限无功需量超限
  {ES_DI(0x03120600), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03120601), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //前1-10次第四象限无功需量超限
  //-----------------------------------------------------------------------------------------------
  //{0x03300000, IMP_EVENT1, 18, 1}, //编程总次数
  {EC_DI(0x03300000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300001), IMP_EVENT_CUMU, 13, 1},//总数据
  {ES_DI(0x03300000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300001), IMP_EVENT2, 50 + 1, PROG_NUM}, //前1-10次编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300100, IMP_EVENT1, 3, 1}, //电表清0总次数
  {EC_DI(0x03300100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300101), IMP_EVENT_CUMU, 13, 1},//总数据
  {ES_DI(0x03300100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300101), IMP_EVENT2, 106 + 1, CLEAR_METER_NUM}, //前1-10次电表清0记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300200, IMP_EVENT1, 3, 1}, //需量清0总次数
  {EC_DI(0x03300200), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300201), IMP_EVENT_CUMU, 13, 1},//总数据
  {ES_DI(0x03300200), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300201), IMP_EVENT2, 202 + 1, CLEAR_DEMAND_NUM}, //前1-10次需量清0记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300300, IMP_EVENT1, 3, 1}, //事件清0总次数
  {EC_DI(0x03300300), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300301), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300300), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300301), IMP_EVENT2, 14 + 1, CLEAR_EVENT_NUM}, //前1-10次事件清0记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300400, IMP_EVENT1, 3, 1}, //校时总次数
  {EC_DI(0x03300400), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300401), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300400), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300401), IMP_EVENT2, 16 + 1, ADJ_TIME_NUM}, //前1-10次校时0记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300500, IMP_EVENT1, 3, 1}, //时段表编程总次数
  {EC_DI(0x03300500), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300501), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300500), IMP_LOAD_REC, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300501), IMP_LOAD_REC, 682 + 1, DATE_TABLE_PROG_NUM}, //前1-10次时段表编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300600, IMP_EVENT1, 3, 1}, //时区表编程总次数
  {EC_DI(0x03300600), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300601), IMP_EVENT_CUMU, 13, 1},//总数据
  {ES_DI(0x03300600), IMP_LOAD_REC, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300601), IMP_LOAD_REC, 94 + 1, YEAR_TABLE_PROG_NUM}, //前1-10次时区表编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300700, IMP_EVENT1, 3, 1}, //周休日编程总次数
  {EC_DI(0x03300700), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300701), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300700), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300701), IMP_EVENT2, 11 + 1, WEEK_REST_PROG_NUM}, //前1-10次周休日编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300800, IMP_EVENT1, 3, 1}, //节假日编程总次数
  {EC_DI(0x03300800), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300801), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300800), IMP_LOAD_REC, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300801), IMP_LOAD_REC, (MAX_YEAR_HOLIDAYS*4) + 10 + 1, HOLIDAY_PROG_NUM}, //前1-10次节假日编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300900, IMP_EVENT1, 3, 1}, //有功组合编程总次数
  {EC_DI(0x03300900), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300901), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300900), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300901), IMP_EVENT2, 11 + 1, ACTIVE_COMB_PROG_NUM}, //前1-10次有功组合编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300A00, IMP_EVENT1, 3, 1}, //无功组合1编程总次数
  {EC_DI(0x03300A00), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300A01), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300A00), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300A01), IMP_EVENT2, 11 + 1, REACTIVE_COMB_PROG_NUM}, //前1-10次无功组合1编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300B00, IMP_EVENT1, 3, 1}, //无功组合2编程总次数
  {EC_DI(0x03300B00), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300B01), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300B00), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300B01), IMP_EVENT2, 11 + 1, REACTIVE_COMB_PROG_NUM}, //前1-10次无功组合2编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300C00, IMP_EVENT1, 3, 1}, //结算日编程总次数
  {EC_DI(0x03300C00), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300C01), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300C00), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300C01), IMP_EVENT2, 16 + 1, SETTLE_TIME_PROG_NUM}, //前1-10次结算日编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300D00, IMP_EVENT1, 3, 1}, //开盖总次数
  {EC_DI(0x03300D00), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300D01), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300D00), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300D01), IMP_EVENT1, 60 + 1, OPEN_METER_COVER_NUM}, //前1-10次开盖编程记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300E00, IMP_EVENT1, 3, 1}, //开端钮总次数
  {EC_DI(0x03300E00), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03300E01), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03300E00), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03300E01), IMP_EVENT1, 60 + 1, OPEN_BOTTOM_COVER_NUM}, //前1-10次开端钮编程记录

  //------------------------------------------------------------------------------------------------  
  //{0x03320100, IMP_EVENT1, 3, 1}, //电量型购电
  {EC_DI(0x03320100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03320101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03320100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03320101), IMP_EVENT2, 23 + 1, PREPAID_ENERGY_NUM}, //前1-10次购电记录
  //---------------------------------------------------------------------------------------------
  //{0x03330100, IMP_EVENT1, 3, 1}, //电费型购电
  {EC_DI(0x03330100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03330101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03330100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03330101), IMP_EVENT2, 23 + 1, PREPAID_MONEY_NUM}, //前1-10次购电记录
  //-----------------------------------------------------------------------------------------------
  //{0x03300D00, IMP_EVENT1, 3, 1}, //低功耗电池欠压
  {EC_DI(0x03410000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03410001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03410000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03410001), IMP_EVENT2, 12 + 1, LOWPWR_BAT_LOW_NUM}, //前1-10次低功耗电池欠压  
  //-----------------------------------------------------------------------------------------------
  //{0x03300D00, IMP_EVENT1, 3, 1}, //时钟电池欠压
  {EC_DI(0x03410100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03410101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03410100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x03410101), IMP_EVENT2, 12 + 1, RTC_BAT_LOW_NUM}, //前1-10次时钟电池欠压 
  //-------------------------------------------------------------------------------------------------
  
  
  //-------------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)PERIOD_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)PERIOD_FREEZE_TYPE << 16), IMP_LOAD_REC, FREEZE_DATA_MAX_LEN + 1, PERIOD_FREEZE_NUM}, //定时冻结,数据量太大，存放到Flash中
  //------------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)INSTANT_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)INSTANT_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, INSTANT_FREEZE_NUM}, //瞬时冻结时间
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)YEAR_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)YEAR_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, YEAR_TABLE_SWITCH_NUM}, //两条时区表切换
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)DATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)DATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, DATE_TABLE_SWITCH_NUM}, //两条时区表切换
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)STEP_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)STEP_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, STEP_SCH_SWITCH_NUM}, //两条时区表切换
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)RATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)RATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, RATE_SCH_SWITCH_NUM}, //两费率方案切换  
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)DATE_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)DATE_FREEZE_TYPE << 16), IMP_LOAD_REC, FREEZE_DATA_MAX_LEN + 1, DATE_FREEZE_NUM}, //日冻结
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)HOUR_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)HOUR_FREEZE_TYPE << 16), IMP_EVENT0, 5 + 8 + 1, HOUR_FREEZE_0_NUM}, //小时冻结，数据量太大
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)ENG_OVERTURN_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //最近一次存储DI
  {ES_DI(0x05000001) | ((INT32U)ENG_OVERTURN_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, ENERGY_OVERTRUN_NUM}, //电量翻转
  //-----------------------------------------------------------------------------------------------   
 
  //负控报警
  {EC_DI(0x03420000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03420001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03420000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03420001), IMP_EVENT1, 18 + 1, PWR_CTRL_ALARM_NUM}, //前1-10次负控报警    
  //负控跳闸
  {EC_DI(0x03420100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x03420101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x03420100), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x03420101), IMP_EVENT1, 12 + 1, PWR_CTRL_SWITCH_NUM}, //前1-10次负控跳闸
  //复位
  {EC_DI(0x0E180000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E180001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E180000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E180001), IMP_EVENT2, 6 + 1, RESET_NUM}, //前1-10次复位
  //时钟乱
  {EC_DI(0x0E190000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E190001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E190000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E190001), IMP_EVENT2, 11 + 1, RUN_CLOCK_ERR_NUM}, //前1-10次时钟乱
  //EEROM错
  {EC_DI(0x0E1A0000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E1A0001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E1A0000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E1A0001), IMP_EVENT2, 5 + 1, EEROM_ERR_NUM}, //前1-10次EEROM错
    /*
  //电量翻转
  {EC_DI(0x0E1B0000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E1B0001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E1B0000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E1B0001), IMP_EVENT1, 78 + 1, ENERGY_OVERFLOW_NUM}, //前1-10次电量翻转 
 */
  //上电时钟乱
  {EC_DI(0x0E1C0000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E1C0001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E1C0000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E1C0001), IMP_EVENT2, 11 + 1, POWER_ON_CLOCK_ERR_NUM}, //前1-10次上电时钟乱  
/*
  //远程拉闸
  {EC_DI(0x0E1D0000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E1D0001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E1D0000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E1D0001), IMP_EVENT1, 38 + 1, REMOTE_RELAY_SWITCH_NUM}, //前1-10次远程拉闸  
  
   //远程合闸
  {EC_DI(0x0E1E0000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E1E0001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E1E0000), IMP_EVENT1, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E1E0001), IMP_EVENT1, 38 + 1, REMOTE_RELAY_SWITCH_NUM}, //前1-10次远程合闸
*/  
  //校表
  {EC_DI(0x0E300000), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E300001), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E300000), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E300001), IMP_EVENT2, 6 + 1, ADJ_METER_NUM}, //前1-10次校表

  //设置初始电量
  {EC_DI(0x0E301100), IMP_EVENT_CUMU, 13, 1},//发生时数据
  {EC_DI(0x0E301101), IMP_EVENT_CUMU, 13, 1},//总数据  
  {ES_DI(0x0E301100), IMP_EVENT2, 4, 1}, //最近一次存储DI
  {ES_DI(0x0E301101), IMP_EVENT2, 77 + 1, SET_ENERG_NUM}, //前1-10次设置初始电量
  
  //{SDI_LAST_LOSS_VOL_OCCUR_TIME, IMP_EVENT1, 6, 1},//最近一次失压发生时刻
  //{SDI_LAST_LOSS_VOL_END_TIME, IMP_EVENT1, 6, 1}, //最近一次失压结束时刻

/*
  #define IMP_FAC_PARA  IMP_0 //工厂参数 
  #define IMP_IMP_PARA  IMP_1 //重要参数      
  #define IMP_NOR_PARA  IMP_2 //普通参数     
  #define IMP_IMP_DATA  IMP_3 //重要数据      
  #define IMP_IMP_BAK_DATA  IMP_4 //重要数据的备份   
  #define IMP_NOR_DATA  IMP_5 //普通数据
  #define IMP_HIS_DATA  IMP_6 //历史数据     
  #define IMP_EVENT_CUMU  IMP_7 //事件累计信息  
  #define IMP_EVENT0    IMP_8 //第0类事件，不频繁，与数据混存       
  #define IMP_EVENT1    IMP_9 //第1类事件，数据量大且频繁，存独立EEROM     
  #define IMP_EVENT0    IMP_A //第2类事件，数据量大，但是不频繁，一般存Flash          
  #define IMP_LOAD_REC  IMP_B //负荷记录，存Flash      
  #define IMP_PD_DATA   IMP_C //掉电存储数据，存FRAM 
  */
  EXTEND_STORA
  //-----------------------------------------------------------------------------------------------
  {_SDI_CHK_IMP0, IMP_FAC_PARA, 1, 1},  //IMP每类数据的测试字 
  {_SDI_CHK_IMP1, IMP_IMP_PARA, 1, 1}, 
  {_SDI_CHK_IMP2, IMP_IMP_PARA, 1, 1},//实际未用
  {_SDI_CHK_IMP3, IMP_IMP_DATA, 1, 1}, 
  {_SDI_CHK_IMP4, IMP_IMP_BAK_DATA, 1, 1}, 
  {_SDI_CHK_IMP5, IMP_IMP_PARA, 1, 1},//实际未用
  {_SDI_CHK_IMP6, IMP_HIS_DATA, 1, 1}, 
  {_SDI_CHK_IMP7, IMP_EVENT_CUMU, 1, 1}, 
  {_SDI_CHK_IMP8, IMP_EVENT0, 1, 1}, 
  {_SDI_CHK_IMP9, IMP_EVENT1, 1, 1}, 
  {_SDI_CHK_IMPA, IMP_EVENT2, 1, 1}, 
  {_SDI_CHK_IMPB, IMP_LOAD_REC, 1, 1}, 
  {_SDI_CHK_IMPC, IMP_PD_DATA, 1, 1},
  
  {_SDI_CHG_CS, IMP_LOAD_REC, 10, 1}  //用于改变整个存储数据的CS,改变其长度可改变这个CS，从而自动设参数
}; 

//extern void Clear_CPU_Dog(void); 
//extern void Clear_Ext_Dog(void); 

//检查超级密码的跳线是否跳上了，跳上返回1，否则返回0
INT8U Check_SuperPSW_Jump()
{
  return 1;
}

//检查Imp_Flag标志的合法性，正确返回1，否则返回0
INT8U Check_Imp_Flag(INT8U Imp_Flag)
{
  if(Imp_Flag <= IMP_C)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//extern CONST S_Data_Mem_Map Data_Mem_Map[];
//获取逻辑存储器的Imp标志
//Mem_No表示逻辑存储器编号
INT8U Get_LOG_Mem_ImpFlag(INT8U Mem_No)
{
  INT8U i, j;
  
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    for(j = 0; j < IMP_LOG_MEM; j ++)
    {
      if(Mem_No EQ Data_Mem_Map[i].LOG_Mem[j])
        return Data_Mem_Map[i].Imp_Flag;
    }   
  }
  return 0xFF;
}

//获取某个存储的数据项数据重要标志
INT8U Get_Storage_Data_ImpFlag(STORA_DI SDI)
{
  INT16U i; 

  TRACE();

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].SDI EQ SDI || \
       (Data_Para_Storage[i].Num > 1 && Data_Para_Storage[i].SDI < SDI && SDI < Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num))
    {
      return Data_Para_Storage[i].Imp_Flag;
    }
  }
  ASSERT_FAILED(); 
  return NULL_IMP;
}

//获取某个存储的数据项的存储偏移，该偏移表示该数据项在同Imp_Flag数据中的存储品偏移
//也表示在逻辑存储器中的整体偏移
INT32U Get_Storage_Data_Off(STORA_DI SDI)
{
  INT16U i; 
  INT32U Offset = 0; 
  INT8U Imp_Flag, Re; 

  TRACE();

  Imp_Flag = Get_Storage_Data_ImpFlag(SDI); 
  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(0 != Re); 

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].SDI EQ SDI)
    {
      return Offset;
    }
    else if(Data_Para_Storage[i].Num > 1 && Data_Para_Storage[i].SDI < SDI && SDI < Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num)
    {
      Offset += (Data_Para_Storage[i].Len + ROM_CS_BYTES) * (SDI - Data_Para_Storage[i].SDI); 
      return Offset;
    }
    else if(Data_Para_Storage[i].Imp_Flag EQ Imp_Flag)//增加偏移
    {
      //if(Data_Para_Storage[i].Num EQ 1)
      // Offset += Data_Para_Storage[i].Len + ROM_CS_BYTES;  
      //else
      Offset += (Data_Para_Storage[i].Len + ROM_CS_BYTES) * Data_Para_Storage[i].Num;
    }
  }

  Debug_Print("Get_Storage_Data_Off Error, Data 0x%lx Not Found\r\n", SDI); 
  return NULL_4BYTES;
}

//获取某个存储的数据项的长度, DI只能是Data_Para_Storage中定义的数据
INT16U Get_Storage_Data_Len(STORA_DI SDI)
{
  INT16U i; 

  TRACE();

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if((Data_Para_Storage[i].Num > 0 && Data_Para_Storage[i].SDI EQ SDI) || \
       (Data_Para_Storage[i].Num > 1 && \
	  Data_Para_Storage[i].SDI < SDI && \
	  Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num> SDI))
    {
      return Data_Para_Storage[i].Len;
    }
  }
  _Debug_Print("Get_Storage_Data_Len Err, SDI = 0x%lx",SDI);
  ASSERT_FAILED(); 
  return 0;
}

//获取某个Imp_Flag重要等级数据的整个数据长度Get_Imp_Data_Size的返回值应该 <= Get_Imp_Mem_Size
INT32U Get_Imp_Data_Size(INT8U Imp_Flag)
{
  INT8U Re; 
  INT16U i; 
  INT32U Size = 0; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 
  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].Imp_Flag EQ Imp_Flag)
    {
      Size += ((INT32U) Data_Para_Storage[i].Len + ROM_CS_BYTES) * Data_Para_Storage[i].Num;
    }
  }
  //ASSERT(Size != 0); 
  return Size;
}

//获得分配给某个Imp_Flag等级的数据的存储空间大小
INT32U Get_Imp_Mem_Size(INT8U Imp_Flag)
{
  INT16U i, j; 
  INT32U Size = 0; //定义一个不存在的size
  INT8U Re; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 

  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    if(Data_Mem_Map[i].Imp_Flag EQ Imp_Flag)//先找到数据内存映射表中的对应项
    {
      Size = 0xFFFFFFFF; //先置一个极大值
      for(j = 0; j < IMP_LOG_MEM; j ++)
      {
        if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
        {
          //找出最小的一个Log_Mem就是分配个数据的存储空间大小
          if(Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]) < Size)
            Size = Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]);
        }
      }
      break;
    }
  }
  //ASSERT(Size != 0 && Size != 0xFFFFFFFF); 
  if(0 EQ Size || 0xFFFFFFFF EQ Size)
  {
    Debug_Print("Imp%d Data Mem_map error", Imp_Flag);
  } 
  return Size;
}

//从存储器中读取某个重要等级的数据
//Imp_Flag，表示数据的重要等级标志
//Offset, 表示数据在存储器中的偏移
//pDst，表示数据读取后的目标指针
//RD_Len，表示需要读取的数据的长度
//pDst_Start和DstLeny一起对pDst和RD_Len的范围进行约束
//返回1表示成功
INT8U Read_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen)
{
  INT16U i, j; 
  INT32U Sum; 
  INT8U Re; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 
  ASSERT((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + RD_Len <= (INT8U *) pDst_Start + DstLen); 

  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    if(Data_Mem_Map[i].Imp_Flag EQ Imp_Flag)//找到数据内存映射表中的对应项
    {
      for(j = 0; j < IMP_LOG_MEM; j ++)//读取存储的逻辑存储器
      {
        if(j != 0)//前一次读取没有成功 ，则延时一下，防止因为总线干扰出问题
          OS_TimeDly_Ms(10); 

        if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)//找到一个存储该数据的逻辑存储器
        {
          //读该逻辑存储器中的数据
          Re = Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset, pDst, RD_Len, pDst_Start, DstLen); 
          if(1!=Re)//ASSERT(1 EQ Re)) //确保返回正确
          {
            ASSERT_FAILED();
            continue;
          }
          
          //读校验和
          Re = Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset + RD_Len, &Sum, ROM_CS_BYTES, &Sum, sizeof(Sum)); 
          if(1!=Re)//ASSERT(1 EQ Re))
          {
            ASSERT_FAILED();
            continue;
          }
          //检查校验和是否正确
          if(Check_Sum(pDst, RD_Len, &Sum, ROM_CS_BYTES))//校验和正确则直接返回1，否则继续读取下个LOG_MEM
            return 1;
          else
            continue;
        }
      }
      ASSERT_FAILED(); 
      return 0;
    }
  }
  ASSERT_FAILED(); 
  return 0;
}

//将某个重要标志的数据写入到存储器中
//Imp_Flag，表示数据的重要等级标志
//Offset, 表示数据在存储器中的偏移
//pSrc，表示数据的起始指针
//SrcLen，表示数据的长度
//返回1表示写成功
//返回WR_IMP_DATA_ERR表示写数据失败
INT8U Write_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pSrc, INT16U SrcLen)
{
  INT8U i, j; 
  INT8U Re; 
  INT32U Sum; 
  INT8U Err_Flag = 0; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 
  Set_Sum(pSrc, SrcLen, &Sum, ROM_CS_BYTES, &Sum, sizeof(Sum)); //生成校验和

  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    if(Data_Mem_Map[i].Imp_Flag EQ Imp_Flag)
    {
      Err_Flag = 0; //只要成功了一次就 Err_Flag |= 1; 
      for(j = 0; j < IMP_LOG_MEM; j ++)
      {
        if(j != 0 && Err_Flag EQ 0)//前一次没有写成功，则延时一下再写
          OS_TimeDly_Ms(10); 

        if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
        {
          Re = Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset, pSrc, SrcLen); //写数据
          ASSERT(1 EQ Re); 
          if(1 EQ Re)
          {
            Re = Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset + SrcLen, &Sum, ROM_CS_BYTES); //写校验和
            ASSERT(1 EQ Re); 
            if(1 EQ Re)
              Err_Flag |= 1;
          }
        }
      }
      if(Err_Flag != 0)//至少写成功了一次
        return 1;
      else
        return 0;
    }
  }
  ASSERT_FAILED(); 
  return 0;
}

//读取存储器中的某项数据的固定长度，DI的值可参考Data_Para_Storage的定义
//DI, 需要读取的数据项标识
//Offset, 读取DI数据的起始偏移
//Len, 需要读取的数据长度
//pDst表示读取参数后放到该缓冲区
//pDst_Start和DstLen一起界定目标缓冲区的范围
//*pErr表示读取失败时的原因, 1表示读取成功, 其他错误原因参见Pub_Err.h
//返回值：读取的数据长度, 读取失败时返回0
INT16U Read_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT32U Off; 
  INT8U Imp_Flag, Err; 

  TRACE();

  _Debug_Print("Read Storage Data:0x%lx, Off = %d, Len = %d", SDI, Offset, Len); 

  Imp_Flag = Get_Storage_Data_ImpFlag(SDI); //获取该数据的重要标志 
  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + Len <= (INT8U *) pDst_Start + DstLen)) 
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Off = Get_Storage_Data_Off(SDI); //获取数据偏移
  if(NULL_4BYTES EQ Off)//ASSERT(NULL_4BYTES != Off))
  {
    ASSERT_FAILED();
    //*pErr = RD_STORAGE_DATA_DI_ERR; 
    return 0;
  }

  Off += Offset; // + 内部偏移

  OS_Mutex_Pend(PUB_RW_ROM_ID); //申请写ROM的信号量ID
  //if(Check_Power_Status() EQ POWER_ON_STATUS)
  Err = Read_Imp_Data(Imp_Flag, Off, pDst, Len, pDst_Start, DstLen); 
  //else
  //*pErr = PD_Read_Imp_Data(Imp_Flag, Off, pDst, Len, pDst_Start, DstLen); 
  OS_Mutex_Post(PUB_RW_ROM_ID); //释放写ROM的信号量ID
  if(1 EQ Err)
  {
    return Len;
  }
  else//读存储失败则读取默认参数
  {
    //*pErr = RD_FIX_DATA_ERR; 
    return 0;
  }
  //return 0;   

}

//写存储器中的某项数据的固定长度，DI的值可参考Data_Para_Storage的定义
//DI, 需要写的数据项标识
//Offset, 写DI数据的起始偏移
//SrcLen, 需要写的数据长度
//pSrc表示写的源数据缓冲区
//SrcLen表示源数据的长度
//返回1表示成功，其他表示失败
INT8U Write_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, void* pSrc, INT16U SrcLen)
{
  INT32U Off; 
  INT8U Imp_Flag, Re; 

  TRACE();

  _Debug_Print("Write Storage Data:0x%lx, Off = %d, Len = %d", SDI, Offset, SrcLen); 

  Imp_Flag = Get_Storage_Data_ImpFlag(SDI); //获取该数据的重要标志 

  Off = Get_Storage_Data_Off(SDI); //获取数据偏移
  if(NULL_4BYTES EQ Off)
  {
    ASSERT_FAILED();
    return 0;
  }

  Off += Offset; // + 内部偏移
  OS_Mutex_Pend(PUB_RW_ROM_ID);  
  //if(Check_Power_Status() EQ POWER_ON_STATUS)
  Re = Write_Imp_Data(Imp_Flag, Off, pSrc, SrcLen); 
  //else
  //Re = PD_Write_Imp_Data(Imp_Flag, Off, pSrc, SrcLen);     
  OS_Mutex_Post(PUB_RW_ROM_ID); 

  //OS_TimeDly_Ms(20); //延时20ms

  if(1 EQ Re)
  {
    return 1;
  }
  else//读存储失败则读取默认参数
  {
    return 0;
  }
}


//读取存储器中的某项数据，DI的值可参考Data_Para_Storage的定义
//DI, 需要读取的数据项标识
//pPara，在读取某些参数或数据时需要的参数，例如HIS_ENERGY, HIS_DEMAND, HIS_DEMAND_TIME时需要加入时间参数
//时间参数的格式定义如下pPara[0]-pPara[4]分别是分、时、日、月、年, 其他情况下该参数无意义
//pDst表示读取参数后放到该缓冲区
//pDst_Start和DstLen一起界定目标缓冲区的范围
//*pErr表示读取失败时的原因, 1表示读取成功, 其他错误原因参见Pub_Err.h
//返回值：读取的数据长度, 读取失败时返回0
INT16U Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len, Len1; 

  TRACE();

  //Clear_CPU_Dog();     //清CPU内部看门狗
  //Clear_Ext_Dog();     //清CPU外部看门狗

  //Cur_Task_ID = Get_Cur_Task_ID(); 
  //Debug_Print("Read Storage Data:0x%lx", DI, Tcb[Cur_Task_ID].Name); 
  Len = Get_Storage_Data_Len(SDI); 
  if(Len > 0)
  {
    //OS_TimeDly_Ms(20); //延时给其他任务，防止某任务连续读多个参数占用CPU
    Len1 = Read_Storage_Data_Fix_Len(SDI, 0, Len, pDst, pDst_Start, DstLen); 
    if(Len != Len1)
    {
      ASSERT_FAILED();
      Len1 = Read_Def_Para(SDI, pDst, Len, pDst_Start, DstLen); 
      if(Len != Len1)//ASSERT(Len1 EQ Len))
      {
        ASSERT_FAILED();
        return 0;
      }
      else
        return Len;
    }
    else
      return Len;
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
}

//读取连续DI的多条存储数据
INT16U Read_Multi_Storage_Data(STORA_DI SDI, INT16U Num, void *pDst, void *pDst_Start, INT16U DstLen)
{
  INT16U i;
  INT16U Len;
  
  Len = 0;
  for(i = 0; i < Num; i ++)
  {
    Len += Read_Storage_Data(SDI + i, (INT8U *)pDst + Len, (INT8U *)pDst_Start, DstLen); 
  }
  
  return Len;
}

//向存储器中写某项数据，DI的值可参考Data_Para_Storage的定义
//DI, 需要写的数据项标识
//pPara，在写某些参数或数据时需要的参数，例如HIS_ENERGY, HIS_DEMAND, HIS_DEMAND_TIME时需要加入时间参数
//时间参数的格式定义如下pPara[0]-pPara[4]分别是分、时、日、月、年, 其他情况下该参数无意义
//pSrc表示写数据的源缓冲区
//返回值：1表示成功，其他表示失败
INT8U Write_Storage_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen)
{
  INT16U Len; 
  INT8U Re; 

  TRACE();

  //Cur_Task_ID = Get_Cur_Task_ID(); 
  //Debug_Print("Write Storage Data:0x%lx", DI, Tcb[Cur_Task_ID].Name); 
  //获取并比较数据长度
  Len = Get_Storage_Data_Len(SDI); 
  if(Len != SrcLen)//ASSERT(Len EQ SrcLen))
  {
    ASSERT_FAILED();
    Debug_Print("WR_Len Err, SDI = 0x%lx Len = %d, SrcLen = %d", SDI, Len, SrcLen);
    return 0;
  } 

  //写Imp数据
  //OS_Mutex_Pend(PUB_RW_ROM_ID); //申请写ROM的信号量ID
  Re = Write_Storage_Data_Fix_Len(SDI, 0, pSrc, SrcLen); 
  //OS_Mutex_Post(PUB_RW_ROM_ID); //释放该信号量
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    return 0;
  } 
  return 1;
}

//检查存储映射是否合理, 主要是检查
void Check_Storage_Map()
{
  INT8U i, j, Count; 
  INT32U Size; 

  TRACE();
  //Re = Check_Mem_Map(); 
  //ASSERT(1 EQ Re); //检查内存区间分配的映射是否正确
  //Get_Imp_Data_Size(IMP_0); 
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    Count = 0; 
    Size = Get_Imp_Data_Size(Data_Mem_Map[i].Imp_Flag); 
    for(j = 0; j < IMP_LOG_MEM; j ++)
    {
      if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
      {
        if(Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]) >= Size)
          Count ++ ;
        else
          ASSERT_FAILED();
      }
    }
    ASSERT((Data_Mem_Map[i].Imp_Flag EQ IMP_5 && Count >= 1) || \
       (Data_Mem_Map[i].Imp_Flag != IMP_5 && Count >= 2)); //每种数据起码有2个存储空间, 即至少一个备份, 除负荷曲线相关数据
  }
}

//检查参数的存储等
INT8U Check_Imp_Data_Storage()
{
  INT8U i, j, Count, Test, Re;
  INT16U Re1; 
  INT32U DataSize, MemSize; 

  TRACE();

  Debug_Print("----Imp_LOG_MEM Map Check----");
  Re = 1;
  //先检查分配给每个Imp_Flag类数据的逻辑存储器的大小和个数是否合法
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    Count = 0; 
    DataSize = Get_Imp_Data_Size(Data_Mem_Map[i].Imp_Flag); 

    Debug_Print("Imp%d Data size=%ld", Data_Mem_Map[i].Imp_Flag, DataSize);

    for(j = 0; j < IMP_LOG_MEM; j ++)
    {
      if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
      {
        MemSize = Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]);

        Debug_Print("--Log_Mem%d size=%ld", Data_Mem_Map[i].LOG_Mem[j], MemSize); 

        if(MemSize >= DataSize)
          Count ++ ;
        else
        {
          Debug_Print("!!!!Imp%d Data size not enough space!!!!", Data_Mem_Map[i].Imp_Flag); 
          Re &= 0;
        }
      }
    }
    /*
                if((Count EQ 0))
                {
                Debug_Print("Imp%d Data do not have enough LOG Mems", Data_Mem_Map[i].Imp_Flag); 
                Re &= 0; 
                }
              */
  }
  /*  
    DataSize = 0; 
    MemSize = 0; 
    for(j = 0; j < S_NUM(Data_Mem_Map); j ++ )
    {
    i = Data_Mem_Map[j].Imp_Flag; 
    DataSize = Get_Imp_Data_Size(i); 
    MemSize = Get_Imp_Mem_Size(i); 
    Debug_Print("IMP%d Data_size = %ld, Mem_Size = %ld", i, DataSize, MemSize); 
    if(DataSize >= MemSize)
    {
    Debug_Print("IMP%d Data Mem not enough space!",i); 
    Re &= 0; 
    }
    }
  */ 
  if(JUDGE_POWER_OFF) //掉电的情况下不进行存储器读写自检
    return Re;
  
  //对每个IMP类数据进行一次读和写操作，测试
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    Test = 0x5A; 
    Re = Write_Storage_Data(_SDI_CHK_IMP0 + i, &Test, 1); 
    if(1 EQ Re)
    {
      Test = 0; 
      Re1 = Read_Storage_Data(_SDI_CHK_IMP0 + i, &Test, &Test, sizeof(Test)); 
      if(0 != Re1 && 0x5A EQ Test)
        continue;
    }
    Debug_Print("IMP%d Data write && read test error", i); 
    Re &= 0;
  }
  return Re;
}

//打印调试信息，将数据的存储地址和长度打印出来
void Debug_Print_Data_Storage()
{
  INT8U Imp_Flag; 
  INT16U i, j; 
  INT16U Num; 
  INT16U Addr, Len; 

  TRACE();

  Debug_Print("PRINT Data_Para_Storage Info-------------"); 
  for(Imp_Flag = IMP_0; Imp_Flag < IMP_5; Imp_Flag ++)
  {
    for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
    {
      if(Data_Para_Storage[i].Imp_Flag EQ Imp_Flag)
      {
        if(Data_Para_Storage[i].Num EQ 0)
          Num = 1; //Data_Para_Storage[i].Num + 1; 
        else
          Num = Data_Para_Storage[i].Num; 

        for(j = 0; j < Num; j ++)
        {
          Addr = Get_Storage_Data_Off(Data_Para_Storage[i].SDI + j); 
          Len = Data_Para_Storage[i].Len; 
          Debug_Print("SDI:0x%lx, Addr:%d, Len:%d", \
           Data_Para_Storage[i].SDI + j, \
           Addr, \
           Len);
        }
      }
    }
  }
}

//检查整个存储系统是否正确
void Check_Sys_Storage()
{
  INT8U Re;

  TRACE();

  if(Check_Meter_Factory_Status())
  {
    Debug_Print("------System Storage_SelfCheck Start!-----"); 
    //物理存储器读写检查
    //检查逻辑与物理存储器之间的映射
    //检查IMP类数据的存储映射
    //检查Protocol_Data的存储映射
    Re = 1;
    //Re &= Check_PHY_Mem();
    Re &= Check_LOG_Mem_Map();
    Re &= Check_Imp_Data_Storage();
    Re &= Check_Protocol_Data_Storage();
    
    if(Re EQ 1)
    {
      Debug_Print("------System Storage_SelfCheck Succeeded!-----");
    }
    else
    {
      _Debug_Print("------System Storage_SelfCheck failed!-----");
      Beep_For_Para();
    }
  }
}

//获取整个存储系统的校验信息，以判断真格存储配置是否发生过修改
INT32U Get_Storage_Info_CS()
{
  INT32U CS0, CS1, CS2, CS3;
   
  CS0 = Get_Sys_Mem_Info_CS();
  CS1 = Get_Def_Para_Info_CS();
  OS_Set_Sum((INT8U *)Data_Mem_Map, sizeof(Data_Mem_Map), &CS2, sizeof(CS2), &CS2, sizeof(CS2));
  OS_Set_Sum((INT8U *)Data_Para_Storage, sizeof(Data_Para_Storage), &CS3, sizeof(CS3), &CS3, sizeof(CS3));
 /* 
  Debug_Print("Sys_Mem_Info_CS = %lx", CS0);
  Debug_Print("Def_Para_Info_CS = %lx", CS1);
  Debug_Print("Data_Mem_Map CS = %lx", CS2);
  Debug_Print("Data_Para_Storage_CS = %lx", CS3);
  Debug_Print("All_CS = %lx", CS0 + CS1 + CS2 + CS3);
  */
  return CS0 + CS1 + CS2 + CS3;
}
#undef DATA_PARA_C

