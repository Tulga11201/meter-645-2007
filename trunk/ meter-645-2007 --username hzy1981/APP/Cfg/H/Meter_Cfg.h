#ifndef METER_CFG_H
#define METER_CFG_H

#undef EXT
#ifdef METER_CFG_C
#define EXT
#else
#define EXT extern
#endif

//#define METER_DEBUG

//---定义表的基本形态----
#define NONET_METER  0x01//非网络表
#define CARRIER_METER  0x02//载波网络表
#define GPRS_METER     0x04//GPRS网络表

#define NOPREPAID_METER 0x10
#define CPU_CARD_METER  0x11
#define IIC_CARD_METER  0x12
#define ESAM_CARD_METER 0x13

#define PREPAID_LOCAL   0x00 //本地预付费
#define PREPAID_REMOTE  0x01 //远程预付费

#define PREPAID_MONEY   0x00 //电费型预付费
#define PREPAID_ENG     0x01 //电量型预付费

#define PREPAID_RATE    0x00 //分时预付费
#define PREPAID_STEP    0x01 //阶梯预付费

#define SWITCH_INTER    0x00 //内置开关方式
#define SWITCH_EXT      0x01 //外部开关方式

#define CS_BYTES    1//内存中重要数据结构体的CS字节数  
#define ROM_CS_BYTES  2//ROM中存储数据的校验和字节数
#define MAX_RATES     4///最大费率数

#define NET_METER     NONET_METER//CARRIER_METER//是否用于网络表的基表，可以是NOT_NET_METER或CARRIER_METER或者GPRS_METER
#define PREPAID_METER 0 //是否是预付费表? 0表示不是，1表示是

#define SHELL_EN      0//shell使能

#define SET_ENERGY_EN 0//Mode_Word.Mode[0].Bit.Bit3 //是否允许设置初始电量

#define METER_CLR_EN        1 //Mode_Word.Mode[0].Bit.Bit1 //是否允许出厂电表清零?
#define NEG_ADD_POS_ACT_EN  0 //Mode_Word.Mode[0].Bit.Bit0 //反向有功是否计入正向

#define POWER_CTRL_EN        0//Mode_Word.Mode[1].Bit.Bit3 //是否有负控功能
#define RESUME_REMOTER_EN    0//Mode_Word.Mode[3].Bit.Bit4 //红外唤醒后遥控器功能是否打开,1打开，0关闭

#define YEAR_TABLE_SWITCH_EN 1//Mode_Word.Mode[2].Bit.Bit5 //是否允许两套年时区表切换?
#define DATE_TABLE_SWITCH_EN 1//Mode_Word.Mode[2].Bit.Bit6 //是否允许两套日时段表切换?
#define RATE_SCH_SWITCH_EN   1 //Mode_Word.Mode[2].Bit.Bit7 //是否允许两套费率切换?
#define STEP_SCH_SWITCH_EN   1 //是否允许切换两套阶梯方案

#define PREPAID_EN            ((PREPAID_METER > 0)?1:0)//((PREPAID_METER > 0)?Mode_Word.Mode[1].Bit.Bit5:0) //预付费使能
#define PREPAID_MODE          PREPAID_MONEY//Mode_Word.Mode[1].Bit.Bit4////预付费模式，PREPAID_MONEY表示电费型，PREPAID_ENG表示电量型, ENERGY_TYPE
#define PREPAID_MONEY_MODE    PREPAID_RATE//Prepaid_Para.Mode[1].Bit.Bit4//PREPAID_RATE表示分时计费，PREPAID_STEP表示阶梯计费
#define PREPAID_LOCAL_REMOTE  PREPAID_LOCAL//Prepaid_Para.Mode[1].Bit.Bit3//PREPAID_LOCAL表示本地，PREPAID_REMOTE表示远程

#define SWITCH_EXT_INTER   SWITCH_INTER //SWITCH_INTER表示内置开关方式,SWITCH_EXT表示外置开关方式

#define PREPAID_WARN_EN 1//Prepaid_Para.Mode[2].Bit.Bit7 //预付费声报警是否打开?
#define PREPAID_LIMIT1_WARN_EN    1//Prepaid_Para.Mode[2].Bit.Bit6 //低于门限1报警使能     
#define PREPAID_LIMIT2_WARN_EN    0//Prepaid_Para.Mode[2].Bit.Bit5//低于门限2报警使能
#define PREPAID_ZERO_WARN_EN  0//Prepaid_Para.Mode[2].Bit.Bit4 //低于0报警使能
#define PREPAID_LIMIT2_SWITCH_EN 1//Prepaid_Para.Mode[0].Bit.Bit1//低于门限2跳闸使能
#define PREPAID_ZERO_SWITCH_EN  1//Prepaid_Para.Mode[2].Bit.Bit4//低于零跳闸使能

#define PREPAID_MAX_STEP      4 //阶梯预付费最大梯度值

#define SCHEME_SWITCH_MODE 1 //年时区和日时段切换方式,0表示切换时间以前用主方案，切换时间后用副方案，
                                //1表示只要跨切换时间就改变方案
#define LOAD_DATA_NUM      43000//存储的负荷曲线条数
#define LOAD_DATA_INDEX_HOUR_NUM 12 //每小时索引个数

#define DEMAND_ACCU_PHASE_NUM 1//(sizeof(Demand_Accu.Phase_Accu)/sizeof(Demand_Accu.Phase_Accu[0]))
#define APP_ENERG_EN   1      //是否保留视在电能
#define USE_ENERGY_RAM_BAK   1//是否在内存中使用一份电量数据的备份

#define MAX_YEAR_PERIODS   14//最大年时区数,年时区表示将一年分为几个时间段
#define MAX_DATE_TABLES   8//最大日时段表数,日时段表示将一天分成几个时间段
#define MAX_DATE_PERIODS   14//每个时段表最大时段数
#define MAX_YEAR_HOLIDAYS  40//每个年时区表对应的最多节假日数,应该为15的倍数

#define MAX_AUTO_SCREEN_NUM 50  //自动循显最大屏数
#define MAX_KEY_SCREEN_NUM 100 //循环显示最大屏数

#define MAX_ENERGY_SETTLE_NUM 12 //电量最大结算条数
#define MAX_DEMAND_SETTLE_NUM 12 //需量最大结算条数
#define MAX_VOLSTAT_SETTLE_NUM 12 //电压统计最大结算条数

#define PERIOD_FREEZE_NUM   12 //定时冻结个数
#define INSTANT_FREEZE_NUM  3 //瞬时冻结个数

#define YEAR_TABLE_SWITCH_NUM 2 //年时表切换记录个数
#define DATE_TABLE_SWITCH_NUM 2 //日时段表切换记录个数
#define RATE_SCH_SWITCH_NUM   2 //分时费率切换记录个数
#define STEP_SCH_SWITCH_NUM      2 //梯度切换记录个数

#define DATE_FREEZE_NUM 62 //日冻结数
#define HOUR_FREEZE_0_NUM 254 //小时冻结数,只冻总电能
//#define HOUR_FREEZE_1_NUM 168 //小时冻结数，

#define ENERGY_OVERTRUN_NUM 3 //电量翻转冻结

/////////////事件记录配置///////////////////
#define LOSS_VOL_NUM   10 //失压记录条数
#define LOW_VOL_NUM    10 //欠压记录条数
#define OVER_VOL_NUM   10 //过压记录条数
#define BREAK_VOL_NUM    10 //断相记录条数

#define ALL_LOSS_VOL_NUM 10 //全失压

#define AUX_POWER_DOWN_NUM   10 //辅助电源失电
#define VOL_REV_SEQ_NUM  10 //电压逆相序
#define CUR_REV_SEQ_NUM  10 //电流逆相序

#define VOL_UNBALANCE_NUM 10 //电压不平衡
#define CUR_UNBALANCE_NUM 10 //电流不平衡

#define LOSS_CUR_NUM   10 //失流记录条数
#define OVER_CUR_NUM   10 //过流记录条数
#define BREAK_CUR_NUM    10 //断流记录条数
#define TREND_REVERSE_NUM  10 //潮流反向记录条数
#define OVER_LOAD_NUM    10 //过载记录条数

#define POWER_DOWN_NUM   10 //掉电

#define POS_ACT_DEMAND_EXCEED_NUM   10  //正向有功需量超限
#define NEG_ACT_DEMAND_EXCEED_NUM   10  //反向有功需量超限
#define REA_DEMAND_EXCEED_NUM   10  //无功需量超限



#define PROG_NUM   10 //编程
#define CLEAR_METER_NUM  10 //电表清0
#define CLEAR_DEMAND_NUM 10 //需量清0
#define CLEAR_EVENT_NUM  10 //事件清0
#define ADJ_TIME_NUM   10 //校时

#define DATE_TABLE_PROG_NUM   10  //时段表编程
#define YEAR_TABLE_PROG_NUM   10  //时区表编程
#define WEEK_REST_PROG_NUM    10  //周休日编程
#define HOLIDAY_PROG_NUM      10  //节假日编程
#define ACTIVE_COMB_PROG_NUM  10  //有功组合编程
#define REACTIVE_COMB_PROG_NUM 10  //无功组合编程

#define SETTLE_TIME_PROG_NUM  10  //结算日编程
#define OPEN_METER_COVER_NUM  10  //开表盖
#define OPEN_BOTTOM_COVER_NUM   10  //开端钮盒
#define PREPAID_ENERGY_NUM 10 //电量型购电
#define PREPAID_MONEY_NUM  10 //电费型购电

#define RELAY_OFF_NUM 10 //拉闸次数
#define RELAY_ON_NUM  10 //合闸次数

#define FACTOR_LOW_NUM 10 //总功率因素超下限
//-------扩充事件记录------
#define LOWPWR_BAT_LOW_NUM 10 //低功耗电池欠压
#define RTC_BAT_LOW_NUM 10 //时钟电池欠压
#define PWR_CTRL_ALARM_NUM  0 //超需量报警
#define PWR_CTRL_SWITCH_NUM 0 //超需量跳闸
#define RESET_NUM       10 //复位
#define RUN_CLOCK_ERR_NUM   10 //运行时钟乱
#define EEROM_ERR_NUM   10 //EEROM乱  

#define ADJ_METER_NUM   10 //校表记录
#define POWER_ON_CLOCK_ERR_NUM 10 //上电时钟乱
#define REMOTE_RELAY_SWITCH_NUM 10 //远程拉合闸
#define SET_ENERG_NUM 0 //设置初始电量



#define FAC_INFO "SZJJ"  //工厂信息,深圳江机
#define PROTOCOL_VERSION "DLT64507" //协议版本号
#endif
