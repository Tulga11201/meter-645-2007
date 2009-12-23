#ifndef DATA_PARA_H
#define DATA_PARA_H

//#include "Data_Trans.h"

#undef EXT
#ifdef DATA_PARA_C
#define EXT
#else
#define EXT extern
#endif

//定义存储在到eerom中的电量数据的大小
#define ENERGY_SAVE_SIZE sizeof(S_Energy)//(S_OFF(S_Energy,CS))

#define DEMAND_SAVE_SIZE (DEMAND_TIME_DATA_SIZE + ROM_CS_BYTES +\
    DEMAND_PHASE_DATA_SIZE + ROM_CS_BYTES +\
     (DEMAND_RATE_DATA_SIZE + ROM_CS_BYTES) * (INT32U)(MAX_RATES + 1))//计算某个费率的需量数据在整个需量存储区中的偏移

#define LOAD_DATA_TIME_INDEX_NUM ((INT32U)LOAD_DATA_INDEX_HOUR_NUM*24*12*31)//每15分钟一个索引数据,每小时4个索引




//---------------定义各种数据的存储标示-end-----------------------//


#define ADJ_METER_PARA_SIZE  256
#define LOAD_DATA_SIZE     32//每条负荷曲线数据的大小
//#define LOAD_DATA_INDEX_SIZE 5//每个小时索引数据的大小
//#define LOAD_DATA_INDEX_NUM  8544//负荷曲线的小时索引条数,每小时一条，可以存8544条

#define PSW0_DI      0x0001//0级密码标识符
#define PSW1_DI      0x0002//1级密码标识符
#define PSW2 DI      0x0003//2级密码标识符

#define NULL_IMP 0xFF //一个不存在的IMP标志

#define IMP_0 0//工厂参数       
#define IMP_1 1//重要参数      
#define IMP_2 2//普通参数      
#define IMP_3 3//重要数据
#define IMP_4 4//重要数据的备份      
#define IMP_5 5//普通数据     
#define IMP_6 6//历史数据     
#define IMP_7 7//事件累计信息        
#define IMP_8 8//第0类事件，不频繁，与数据混存       
#define IMP_9 9//第1类事件，数据量大且频繁，存独立EEROM      
#define IMP_A 10//第2类事件，数据量大，但是不频繁，一般存Flash       
#define IMP_B 11//负荷记录，存Flash      
#define IMP_C 12//掉电存储数据，存FRAM 

#define IMP_FAC_PARA  IMP_0 //工厂参数 
#define IMP_IMP_PARA  IMP_1 //重要参数       
#define IMP_NOR_PARA  IMP_2 //普通参数      
#define IMP_IMP_DATA  IMP_3 //重要数据       
#define IMP_IMP_BAK_DATA  IMP_4 //重要数据的备份    
#define IMP_NOR_DATA  IMP_5 //普通数据
#define IMP_HIS_DATA  IMP_6 //历史数据      
#define IMP_EVENT_CUMU    IMP_7 //事件累计信息       
#define IMP_EVENT0    IMP_8 //第0类事件，冻结类     
#define IMP_EVENT1    IMP_9 //第1类事件，电网或电表事件    
#define IMP_EVENT2    IMP_A //编程类           
#define IMP_LOAD_REC  IMP_B //负荷记录，存Flash     
#define IMP_PD_DATA   IMP_C //掉电存储数据，存FRAM 

//#define HIS_HEAD sizeof(S_HEX_Time) //存储历史电量需量数据时的头长度

#define IMP_LOG_MEM 5 //每个IMP类数据最多拥有的逻辑存储器个数

//存储的扩充DI编码原则:最高4位不能为0
//1表示扩充参数或者数据
//2表示历史或者结算数据
//3表示分次事件数据
//4表示累计事件数据
#define NULL_S_DI      0xFFFFFFFF

//最高3位用于配置扩展数据
#define EXT_PARA_DATA  (0x10000000<<1)
#define EXT_HIS_DATA   (0x20000000<<1)
#define EXT_SEPA_EVENT (0x30000000<<1)
#define EXT_CUMU_EVENT (0x40000000<<1)

#define ES_DI(X) (X|EXT_SEPA_EVENT)//分次事件扩充DI
#define EC_DI(X) (X|EXT_CUMU_EVENT)//累计事件扩充DI

#define SCREEN_ID_LEN 5 //键盘显示和循环显示ID的数据长度

#define _SDI_BOOT_FLAG0    (0x00|EXT_PARA_DATA)  //IMP_CUR_DATA,4,1},//启动标志，表征是否是第一次启动
#define _SDI_BOOT_FLAG    (0x01|EXT_PARA_DATA)  //IMP_CUR_DATA,4,1},//启动标志，表征是否是第一次启动
//----------
//------------------
#define _SDI_CUR_ENERGY_PD    (0x02|EXT_PARA_DATA)//IMP6,ENERGY_SAVE_SIZE,1},//当前电量,掉电存储,平时也定时存储
#define _SDI_CUR_DEMAND_PD    (0x03|EXT_PARA_DATA)//IMP6,sizeof(S_Demand),1},//掉电只保存总和当前费率需量，即S_Demand_

#define _SDI_CUR_VOLSTAT_PD          (0x04|EXT_PARA_DATA)//IMP6,sizeof(S_VolStat),1},//当前电压统计数据
#define _SDI_TOTAL_VOLSTAT_PD        (0x05|EXT_PARA_DATA)//IMP6,sizeof(S_VolStat),1},//总电压检测数据
#define _SDI_SAVE_PD_DATA_TIME       (0x06|EXT_PARA_DATA)//IMP6,4,掉电存数花掉的时间
#define _SDI_EVENT_DATA_PD           (0x07|EXT_PARA_DATA)//IMP6,sizeof(Cur_Time1),1},//掉电存数
//#define _SDI_CUR_YEAR_DATE_SCHEME_PD (0x08|EXT_PARA_DATA)//IMP6,当前年时区日时段方案
#define _SDI_TIME_BAK                (0x09|EXT_PARA_DATA)

#define _SDI_CUR_SCHEME (0x0A|EXT_PARA_DATA) //当前年时区、日时段方案
#define _SDI_LOAD_DATA_INDEX_PD   (0x10|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_LoadData_Index),1},
//负荷曲线存储信息,每存储一条负荷曲线存储一次该数据,存储频繁，因此选择FRAM作为存储介质
#define _SDI_LOAD_DATA_INDEX  (0x11|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_LoadData_Index),1},
#define _SDI_CUR_ENERGY   (0x12|EXT_PARA_DATA)//IMP6,ENERGY_SAVE_SIZE,1},//当前电量
#define _SDI_CUR_DEMAND   (0x13|EXT_PARA_DATA)//IMP6,DEMAND_SAVE_SIZE,1},//当月最大需量


#define _SDI_CUR_VOLSTAT  (0x14|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//当前电压统计数据

#define _SDI_CUR_PREPAID  (0x15|EXT_PARA_DATA) //预付费相关信
//#define _SDI_TOTAL_VOLSTAT    (0x15|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//总电压检测数据
//#define EVENT_CUMU//IMP_CUR_DATA,sizeof(S_Event_Cumu),1},//事件累计数据

//#define _SDI_METER_ADDR0  (0x16|EXT_PARA_DATA)//IMP_CUR_DATA,6,1},//设备地址0
//#define _SDI_METER_ADDR1  (0x17|EXT_PARA_DATA)//IMP_CUR_DATA,6,1},//设备地址1
//#define _SDI_METER_ADDR2  (0x18|EXT_PARA_DATA)//IMP_CUR_DATA,6,1},//设备地址2

//#define _SDI_COMM_BAUD0   (0x20|EXT_PARA_DATA)//IMP_CUR_DATA,1,1},//第一路波特率
//#define _SDI_COMM_BAUD1   (0x21|EXT_PARA_DATA)//IMP_CUR_DATA,1,1},//第二路波特率
//#define _SDI_COMM_BAUD2   (0x22|EXT_PARA_DATA)//IMP_CUR_DATA,1,1},//第三路波特率

//#define _SDI_PASSWORD_0   (0x23|EXT_PARA_DATA)//IMP_CUR_DATA,3,1},//0级密码
//#define _SDI_PASSWORD_1   (0x24|EXT_PARA_DATA)//IMP_CUR_DATA,3,1},//1级密码
//#define _SDI_PASSWORD_2   (0x25|EXT_PARA_DATA)//IMP_CUR_DATA,3,1},//2级密码

#define _SDI_CUR_ENERGY_BAK0  (0x26|EXT_PARA_DATA)//IMP_CUR_DATA,ENERGY_SAVE_SIZE,1},//当前电量备份,平时定时存储
#define _SDI_CUR_ENERGY_BAK1  (0x27|EXT_PARA_DATA)//IMP_CUR_DATA,ENERGY_SAVE_SIZE,1},//当前电量备份,平时定时存储
#define _SDI_CUR_ENERGY_BAK2  (0x28|EXT_PARA_DATA)//IMP_HIS_DATA,ENERGY_SAVE_SIZE,1},//当前电量备份,平时定时存储
#define _SDI_CUR_DEMAND_BAK   (0x29|EXT_PARA_DATA)//IMP_CUR_DATA,DEMAND_SAVE_SIZE,1},//当月最大需量及其发生时间
#define _SDI_CUR_VOLSTAT_BAK  (0x2A|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//当前电压统计数据备份
//#define _SDI_TOTAL_VOLSTAT_BAK  (0x2B|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//总电压检测数据备份

#define _SDI_ENERGY_FREEZE_TIME   (0x2C|EXT_PARA_DATA)//IMP_CUR_DATA,2,1},//周期冻结时间
#define _SDI_REACTIVE_FREEZE_TIME (0x2D|EXT_PARA_DATA)//IMP_CUR_DATA,2,1},//周期冻结时间

#define _SDI_PROG_RECORD  (0x2E|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(Prog_Record),1},//编程记录
#define _SDI_CLR_DEMAND_RECORD    (0x30|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(Clr_Demand_Record),1},//清需量记录

#define _SDI_LOAD_DATA_INDEX_BAK  (0x31|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_LoadData_Index),1},//负荷曲线存储索引备份等

#define _SDI_LAST_SETTLE_ENERGY_DI (0x40|EXT_PARA_DATA) //上次结算电量数据的存储索引
#define _SDI_SETTLE_ENERGY_DATA    (0x41|EXT_PARA_DATA) //存储结算数据

#define _SDI_LAST_SETTLE_DEMAND_DI (0x50|EXT_PARA_DATA) //上次结算需量数据的存储索引
#define _SDI_SETTLE_DEMAND_DATA    (0x51|EXT_PARA_DATA)

#define _SDI_LAST_SETTLE_VOLSTAT_DI (0x60|EXT_PARA_DATA)//上次结算电压统计数据的存储索引
#define _SDI_SETTLE_VOLSTAT_DATA  (0x61|EXT_PARA_DATA)

#define _SDI_REMOTE_RELAY_STATUS (0x70|EXT_PARA_DATA) //远程控制继电器状态,值为RELAY_ON或者RELAY_OFF
#define _SDI_PREPAID_POWER_CTRL_RELAY_STATUS (0x71|EXT_PARA_DATA) //预付费负荷控制继电器状态

#define _SDI_CTRL_STATUS_FLAG (0x72|EXT_PARA_DATA) //控制标志

#define _SDI_CHK_IMP0       (0x0100|EXT_PARA_DATA)
#define _SDI_CHK_IMP1       (0x0101|EXT_PARA_DATA)
#define _SDI_CHK_IMP2       (0x0102|EXT_PARA_DATA)
#define _SDI_CHK_IMP3       (0x0103|EXT_PARA_DATA)
#define _SDI_CHK_IMP4       (0x0104|EXT_PARA_DATA)
#define _SDI_CHK_IMP5       (0x0105|EXT_PARA_DATA)
#define _SDI_CHK_IMP6       (0x0106|EXT_PARA_DATA)
#define _SDI_CHK_IMP7       (0x0107|EXT_PARA_DATA)
#define _SDI_CHK_IMP8       (0x0108|EXT_PARA_DATA)
#define _SDI_CHK_IMP9       (0x0109|EXT_PARA_DATA)
#define _SDI_CHK_IMPA       (0x010A|EXT_PARA_DATA)
#define _SDI_CHK_IMPB       (0x010B|EXT_PARA_DATA)
#define _SDI_CHK_IMPC       (0x010C|EXT_PARA_DATA)

//-----------校表相关------------
#define _SDI_ADJ_METER_PARA_STATUS      (0x0200|EXT_PARA_DATA)//校表参数状态设置,1字节
#define _SDI_ADJ_METER_PUL_VOL_CUR_SPEC (0x0201|EXT_PARA_DATA)//脉冲、电压、电流规格,3字节
#define _SDI_ADJ_METER_A_POW            (0x0202|EXT_PARA_DATA)//A相功率增益参数设置,3字节
#define _SDI_ADJ_METER_B_POW            (0x0203|EXT_PARA_DATA)//B相功率增益参数设置,3字节
#define _SDI_ADJ_METER_C_POW            (0x0204|EXT_PARA_DATA)//C相功率增益参数设置,3字节
#define _SDI_ADJ_METER_A_PHASE          (0x0205|EXT_PARA_DATA)//A相相位增益参数设置,3字节
#define _SDI_ADJ_METER_B_PHASE          (0x0206|EXT_PARA_DATA)//B相相位增益参数设置,3字节
#define _SDI_ADJ_METER_C_PHASE          (0x0207|EXT_PARA_DATA)//B相相位增益参数设置,3字节
#define _SDI_ADJ_METER_A_VOL            (0x0208|EXT_PARA_DATA)//A相电压参数设置,3字节
#define _SDI_ADJ_METER_B_VOL            (0x0209|EXT_PARA_DATA)//B相电压参数设置,3字节
#define _SDI_ADJ_METER_C_VOL            (0x020A|EXT_PARA_DATA)//C相电压参数设置,3字节
#define _SDI_ADJ_METER_A_CUR            (0x020B|EXT_PARA_DATA)//A相电流参数设置,3字节
#define _SDI_ADJ_METER_B_CUR            (0x020C|EXT_PARA_DATA)//B相电流参数设置,3字节
#define _SDI_ADJ_METER_C_CUR            (0x020D|EXT_PARA_DATA)//C相电流参数设置,3字节
#define _SDI_ADJ_METER_CLR              (0x020E|EXT_PARA_DATA)//校表清0,并不分配空间
#define _SDI_RD_ROM                     (0x0210|EXT_PARA_DATA)//读取ROM中数据标识，并不分配空间
//-------------------------------------

#define _SDI_PREPAID_RUN_STATUS (0x0300|EXT_PARA_DATA)//运行状态 数据长度为1
#define _SDI_DISCRETE_INFO (0x0301|EXT_PARA_DATA)//离散因子 数据长度为8
#define _SDI_PREPAID_PARA_CARD_VER (0x0302|EXT_PARA_DATA)//现场参数设置卡版本号 数据长度为4
#define _SDI_PREPAID_PSW_KIND (0x0303|EXT_PARA_DATA)//密钥类型数据长度为1
#define _SDI_INVALID_CARD_COUNTS (0x0304|EXT_PARA_DATA)//非法卡插入次数
#define _SDI_INVALID_COUNTS_AllOW (0x0305|EXT_PARA_DATA)
#define _SDI_FAR_AUTH_DAY_FOLLOW (0x0306|EXT_PARA_DATA) //远程身份认证跟随日
#define _SDI_SINGLE_OR_COMPLEX_USER_KIND (0x0307|EXT_PARA_DATA) //单或者复费率
#define _SDI_FAR_PASSWORD_STATE (0x0308|EXT_PARA_DATA) //远程表密钥类型

#define _SDI_LOAD_DATA_TIME_INDEX (0x100000|EXT_PARA_DATA)//IMP5,2,LOAD_DATA_TIME_INDEX_NUM},//定义负荷曲线小时索引,LOAD_DATA_TIME_INDEX_NUM条
#define _SDI_LOAD_DATA    (0x200000|EXT_PARA_DATA)//IMP5,LOAD_DATA_SIZE,LOAD_DATA_NUM},//定义负荷曲线,LOAD_DATA_NUM条//IMP_CUR_DATA,4,1},//启动标志，表征是否是第一次启动
#define _SDI_LOAD_DATA_NEXT_INDEX (0x300000|EXT_PARA_DATA)

#define _SDI_CHG_CS  (0xFFFFFF | EXT_PARA_DATA)
//////////////////////////////////////////////////////

////////////////////定义与通信兼容的存储DI///////////////
#define SDI_BAT_RUN_TIME 0x0280000A  //电池工作时间

#define SDI_DEMAND_PERIOD      0x04000103 //需量周期
#define SDI_DEMAND_SLID    0x04000104 //滑差时间
#define SDI_ADJ_PULSE_WIDTH    0x04000105 //校表脉冲宽度
#define SDI_YEAR_SCHE_CHG_TIME   0x04000106 //年时区切换时间
#define SDI_DATE_SCHE_CHG_TIME   0x04000107 //日时段表切换时间
#define SDI_RATE_SCHE_CHG_TIME   0x04000108 //两套费率切换时间
#define SDI_STEP_SCHE_CHG_TIME   0x04000109 //两套阶梯方案切换时间

#define SDI_YEAR_PERIOD_NUM    0x04000201 //年时区数
#define SDI_DATE_TABLE_NUM     0x04000202 //日时段表数
#define SDI_DATE_PERIOD_NUM    0x04000203 //日时段数
#define SDI_RATE_NUM   0x04000204 //费率数
#define SDI_HOLIDAY_NUM    0x04000205 //公共节假日数
#define SDI_HARMONIC_NUM   0x04000206 //谐波次数
#define SDI_PREPAID_STEP_NUM 0x04000207 //预付费阶梯电价阶梯数

#define SDI_AUTO_CYCL_SCREEN_NUM 0x04000301 //自动循环显示屏数
#define SDI_SCREEN_SHOW_TIME   0x04000302 //没屏显示时间
#define SDI_ENERGY_DECIMAL_NUM   0x04000303 //显示电能小数位数
#define SDI_POWER_DECIMAL_NUM    0x04000304 //显示功率与需量小数位数
#define SDI_KEY_CYCL_SCREEN_NUM  0x04000305 //按键循环显示屏数
#define SDI_CURR_TRANS_RATIO     0x04000306 //电流互感器变比
#define SDI_VOLT_TRANS_RATIO     0x04000307 //电压互感器变比


#define SDI_COMM_ADDR      0x04000401 //通信地址
#define SDI_METER_ID   0x04000402 //表号
#define SDI_ASSET_ID   0x04000403 //资产管理编码
#define SDI_RATED_VOL      0x04000404 //额定电压
#define SDI_RATED_CUR      0x04000405 //额定电流
#define SDI_MAX_CUR    0x04000406 //最大电流
#define SDI_ACTIVE_ACCU    0x04000407 //有功准确等级
#define SDI_REACTIVE_ACCU      0x04000408 //无功准确等级
#define SDI_ACTIVE_CONST   0x04000409 //电表有功常数
#define SDI_REACTIVE_CONST     0x0400040A //电表无功常数
#define SDI_METER_TYPE     0x0400040B //电表型号
#define SDI_METER_MADE_TIME    0x0400040C //电表生产日期
#define SDI_PROTOCOL_VER   0x0400040D //电表协议版本号
#define SDI_CUTOMER_ID     0x0400040E //客户编号
//#define SDI_HARDWARE_VER   0x0400040F //硬件版本号,该定义未用

#define SDI_ACTIVE_COMB_WORD   0x04000601 //有功组合方式特征字
#define SDI_REACTIVE_COMB_WORD_1 0x04000602 //无功组合方式特征字1
#define SDI_REACTIVE_COMB_WORD_2 0x04000603 //无功组合方式特征字2

#define SDI_FAR_IRAD_BAUD      0x04000701 //调制红外远红外速度特征字
#define SDI_NEAR_IRAD_BAUD     0x04000702 //接触红外近红外速度特征字
#define SDI_COMM1_BAUD     0x04000703 //通信口1速度
#define SDI_COMM2_BAUD     0x04000704 //通信口2速度
#define SDI_COMM3_BAUD     0x04000705 //通信口3速度

#define SDI_WEEK_REST_DAY      0x04000801 //周休日特征字
#define SDI_WEEK_REST_DATE_TABLE 0x04000802 //周休日日时段表号

#define SDI_LOAD_REC_WORD      0x04000901 //负荷记录模式字
#define SDI_FREEZE_REC_WORD    0x04000902 //冻结记录模式字

#define SDI_LOAD_REC_START_TIME  0x04000A01 //负荷记录起始时间
#define SDI_LOAD_REC1_INTER_TIME 0x04000A02 //第一类负荷记录间隔时间
#define SDI_LOAD_REC2_INTER_TIME 0x04000A03 //第二类负荷记录间隔时间
#define SDI_LOAD_REC3_INTER_TIME 0x04000A04 //第三类负荷记录间隔时间
#define SDI_LOAD_REC4_INTER_TIME 0x04000A05 //第四类负荷记录间隔时间
#define SDI_LOAD_REC5_INTER_TIME 0x04000A06 //第五类负荷记录间隔时间
#define SDI_LOAD_REC6_INTER_TIME 0x04000A07 //第六类负荷记录间隔时间

#define SDI_MONTH_SETTLE_DAY1    0x04000B01 //每月第一结算日
#define SDI_MONTH_SETTLE_DAY2    0x04000B02 //每月第二结算日   
#define SDI_MONTH_SETTLE_DAY3    0x04000B03 //每月第三结算日

#define SDI_PSW0     0x04000C01 //第0级密码
#define SDI_PSW1     0x04000C02 //第1级密码
#define SDI_PSW2     0x04000C03 //第2级密码
#define SDI_PSW3     0x04000C04 //第3级密码
#define SDI_PSW4     0x04000C05 //第4级密码
#define SDI_PSW5     0x04000C06 //第5级密码
#define SDI_PSW6     0x04000C07 //第6级密码
#define SDI_PSW7     0x04000C08 //第7级密码
#define SDI_PSW8     0x04000C09 //第8级密码
#define SDI_PSW9     0x04000C0A //第9级密码

#define SDI_PHASE_A_CONDUC     0x04000D01 //A相电导率
#define SDI_PHASE_A_SUSCEP     0x04000D02 //A相电纳率
#define SDI_PHASE_A_RESIST     0x04000D03 //A相电阻率
#define SDI_PHASE_B_CONDUC     0x04000D04 //B相电导率
#define SDI_PHASE_B_SUSCEP     0x04000D05 //B相电纳率
#define SDI_PHASE_B_RESIST     0x04000D06 //B相电阻率
#define SDI_PHASE_C_CONDUC     0x04000D07 //C相电导率
#define SDI_PHASE_C_SUSCEP     0x04000D08 //C相电纳率
#define SDI_PHASE_C_RESIST     0x04000D09 //C相电阻率

#define SDI_POS_ACTIVE_UP_LIMIT  0x04000E01 //正向有功功率上限
#define SDI_NEG_ACTIVE_LOW_LIMIT 0x04000E02 //反向有功功率上限
#define SDI_VOL_UP_LIMIT   0x04000E03 //电压上限值
#define SDI_VOL_LOW_LIMIT      0x04000E04 //电压下限

#define SDI_PREPAID_WARN_ENG1        0x04000F01 //报警电量1
#define SDI_PREPAID_WARN_ENG2        0x04000F02 //报警电量2
#define SDI_PREPAID_HOARD_ENG_LIMIT  0x04000F03 //囤积电量限额
#define SDI_PREPAID_OVERDRAFT_ENG_LIMIT 0x04000F04 //透支电量限额

#define SDI_PREPAID_WARN_MONEY1           0x04001001 //报警金额1
#define SDI_PREPAID_WARN_MONEY2           0x04001002 //报警金额2
#define SDI_PREPAID_OVERDRAFT_MONEY_LIMIT 0x04001003 //透支金额限额
#define SDI_PREPAID_HOARD_MONEY_LIMIT     0x04001004 //囤积金额限额
#define SDI_PREPAID_RELAY_ON_MONEY_LIMIT  0x04001005 //合闸允许金额限值

#define SDI_METER_RUN_STATUS  0x04001101 //电表运行状态字

#define SDI_HOUR_FREEZE_START_TIME 0x04001201 //整点冻结起始时间
#define SDI_HOUR_FREEZE_PERIOD     0x04001202 //整点冻结间隔时间
#define SDI_DATE_FREEZE_TIME       0x04001203 //日冻结时间

#define SDI_RELAY_OFF_DELAY      0x04001401 //跳闸延时

#define SDI_POWER_PULSE          0x0400E001 //功率负荷脉冲数
#define SDI_MAX_POWER_CALC_TIME  0x0400E002 //最大负荷计算时间
#define SDI_POWER_CTRL_RELAY_SWITCH_LIMIT 0x0400E003 //过负荷跳闸次数门限

#define SDI_DISP_FEE_DIGS        0x0400E101 //显示电费小数位

#define SDI_PREPAID_MODEWORD_1   0x0400E201 //预付费模式字1
#define SDI_PREPAID_MODEWORD_2   0x0400E202 //预付费模式字2
#define SDI_PREPAID_MODEWORD_3   0x0400E203 //预付费模式字3

#define SDI_PREPAID_SEQ_NO       0x0400EB01 //系统序列号
#define SDI_PREPAID_USER_NO      0x0400EB02 //用户号
#define SDI_PREPAID_METER_NO     0x0400EB03 //表号

#define SDI_SCHE1_YEAR_TABLE   0x04010000 //第一套时区表
#define SDI_SCHE1_DATE_TABLE1    0x04010001 //第一套第一日时段表
#define SDI_SCHE1_DATE_TABLE2    0x04010002 //第一套时二日时段表
#define SDI_SCHE1_DATE_TABLE3    0x04010003 //第一套时三日时段表
#define SDI_SCHE1_DATE_TABLE4    0x04010004 //第一套时四日时段表
#define SDI_SCHE1_DATE_TABLE5    0x04010005 //第一套时五日时段表
#define SDI_SCHE1_DATE_TABLE6    0x04010006 //第一套时六日时段表
#define SDI_SCHE1_DATE_TABLE7    0x04010007 //第一套时七日时段表
#define SDI_SCHE1_DATE_TABLE8    0x04010008 //第一套时八日时段表

#define SDI_SCHE2_YEAR_TABLE   0x04020000 //第二套时区表
#define SDI_SCHE2_DATE_TABLE1    0x04020001 //第二套第一日时段表
#define SDI_SCHE2_DATE_TABLE2    0x04020002 //第二套时二日时段表
#define SDI_SCHE2_DATE_TABLE3    0x04020003 //第二套时三日时段表
#define SDI_SCHE2_DATE_TABLE4    0x04020004 //第二套时四日时段表
#define SDI_SCHE2_DATE_TABLE5    0x04020005 //第二套时五日时段表
#define SDI_SCHE2_DATE_TABLE6    0x04020006 //第二套时六日时段表
#define SDI_SCHE2_DATE_TABLE7    0x04020007 //第二套时七日时段表
#define SDI_SCHE2_DATE_TABLE8    0x04020008 //第二套时八日时段表

#define SDI_HOLIDAY_DATE_TABLE   0x04030001 //公共节假日及日时段表号
#define SDI_AUTO_CYCL_SREEN_DATA 0x04040101 //自动循环显示屏号
#define SDI_KEY_CYCL_SREEN_DATA  0x04040201 //按键循环显示屏号

#define SDI_RATE_SCHEME0_0       0x04050101 //第一套费率参数
#define SDI_RATE_SCHEME1_0       0x04050201 //第二套费率参数

#define SDI_STEP_SCHEME0_ENG     0x04060001 //第一套阶梯参数电量
#define SDI_STEP_SCHEME0_MONEY   0x04060101 //第一套阶梯参数电价
#define SDI_STEP_SCHEME1_ENG     0x04060201 //第二套阶梯参数电量
#define SDI_STEP_SCHEME1_MONEY   0x04060301 //第二套阶梯参数电价

#define SDI_HARDWARE_VERSION     0x04800002 //硬件版本号
#define SDI_FAC_NO               0x04800003 //工厂版本号

#define SDI_MODEWORD_1           0x0E000001 //模式字1
#define SDI_MODEWORD_2           0x0E000002 //模式字2
#define SDI_MODEWORD_3           0x0E000003
#define SDI_MODEWORD_4           0x0E000004
#define SDI_MODEWORD_5           0x0E000005

//#define SDI_PROG_EN_TIME         0x0E000206 //编程有效时间
#define SDI_OUTPUT_MODE          0x0E000206 //三合一输出模式字
#define SDI_PERIOD_FREEZE_TIME   0x0E000207//冻结时间

#define SDI_ADJ_TIME_COUNTS      0x0E000208 //每日广播校时次数

#define SDI_LAST_LOSS_VOL_OCCUR_TIME 0x10000101 //最近一次失压发生时刻
#define SDI_LAST_LOSS_VOL_END_TIME   0x10000201 //最近一次失压结束时刻

///////////////////////
/*
#define IMP_ADJ   0x00 //重要数据,校表参数和模式字
#define IMP_ENERGY   0x01
#define IMP_HIS    0x02
#define IMP_EVENT    0x03
#define IMP_LOAD   0x04
#define IMP_POWD   0x05
*/
//下面需要引用该类型
/*
typedef struct
{
  INT8U Loss_Vol_Flag[4];
  INT32U Loss_Vol_Counts[4];//总、A、B、C失压次数 
  INT32U Loss_Vol_Time[4];//总失压累计时间
  
  INT8U Loss_Cur_Flag[4];
  INT32U Loss_Cur_Counts[4];//总失流次数
  INT32U Loss_Cur_Time[4];//总失流时间
  
  INT8U CS[CS_BYTES];
}S_Event_Cumu;
*/

typedef struct
{
    INT8U Imp_Flag;//数据标志
    INT8U LOG_Mem[IMP_LOG_MEM];//其存储的逻辑存储器，第一个是原始数据，后三个是备份，NULL_MEM表示没有
}S_Data_Mem_Map;

//#define RD_WR 0//可读可写
#define WR 1   //只可写
#define RD 2   //可读
/*
typedef struct
{
    INT8U Imp_Flag;
    INT32U Offset;
}S_Data_Para_Info;
*/

typedef struct
{
    //INT8U Stora_Property;//存储属性,0表示标识符是自定义的，1表示标识符与协议兼容
    STORA_DI SDI; 
    //参数标识,与DLT645兼容，同时可扩充。
    //INT8U RW_Flag;
    //参数读写标志，宏READ表示可读，宏WRITE 表示可写,READ|WRITE表示可读可写
    //INT8U PSW_Flag;
    //参数密码等级标志,PSW_N表示在N级密码以上才可修改该参数(N=0,1,2)
    INT8U Imp_Flag;
    //重要等级标志 宏IMP_FACTORY_PARA表示最重要 IMP_CUR_DATA->IMP5重要性依次递减
    INT16U Len; //数据或参数长度
    //可否考虑加读写错误次数？这样可加强IMP不同的参数的容错能力。
    INT32U Num;
    //类似于此项的个数
}S_Data_Para_Storage_Info;



EXT INT8U Check_SuperPSW_Jump();
EXT INT8U Check_Imp_Flag(INT8U Imp_Flag);
EXT INT8U Get_Storage_Data_ImpFlag(STORA_DI SDI);
EXT INT32U Get_Storage_Data_Off(STORA_DI SDI);
EXT INT16U Get_Storage_Data_Len(STORA_DI SDI);
EXT INT32U Get_Imp_Data_Size(INT8U Imp_Flag);
EXT INT32U Get_Imp_Mem_Size(INT8U Imp_Flag);
EXT INT8U Read_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Storage_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Multi_Storage_Data(STORA_DI SDI, INT16U Num, void *pDst, void *pDst_Start, INT16U DstLen);

//EXT INT16U Read_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
//EXT INT8U Write_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pSrc,INT16U SrcLen);
EXT INT8U Get_LOG_Mem_ImpFlag(INT8U Mem_No);
EXT void Check_Data_Storage();
EXT void Debug_Print_Data_Storage();
EXT void Check_Sys_Storage();
EXT INT32U Get_Storage_Info_CS();
#endif
