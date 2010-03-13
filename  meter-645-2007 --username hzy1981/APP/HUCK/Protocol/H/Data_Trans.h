#ifndef DATA_TRANS_H
#define DATA_TRANS_H

//#include "Authority.h"
//#include "Demand.h"

#undef EXT
#ifdef DATA_TRANS_C
#define EXT
#else
#define EXT extern
#endif

#define CH_RS485_1  CHANEL_485_1//0//第一路485
#define CH_RS485_2  CHANEL_485_2//1//第二路485
#define CH_MODULE   2//网络模块
#define CH_IRAD   CHANEL_IRDA//3//红外

#define PROG_PERIOD 10 //编程周期为10分钟

#define DATA_ADD 0
#define DATA_DEC 1

#define FOR_SRC   0x01
#define FOR_COMM  0x02
#define FOR_DISP  0x04
#define FOR_EVENT 0x08

#define AUTHORITY_FLAG 0x55aa55aa  //权限标志

//定义错误信息状态字
#define OTHER_ERR              0x00//其他错误
#define NO_REQ_DATA_ERR        0x01//无请求数据
#define AUTH_ERR               0x02//密码-权限错
#define MODI_BAUD_ERR          0x03//修改通信速度错
#define YEAR_PERIOD_EXCEED_ERR 0x04//年时区数超
#define DATE_PERIOD_EXCEED_ERR 0x05//日时段数超
#define RATE_EXCEED_ERR        0x06//费率数超

#define CLEAR_ALL_FLAG     0x05AA5ABC//总清标志
#define CLEAR_ENERGY_FLAG  0x0055AABB//清电量标志 
#define CLEAR_DEMAND_FLAG  0xAABBCCDD//清需量标志
#define CLEAR_VOLSTAT_FLAG 0x11223344//清电压统计标志
#define CLEAR_EVENT_FLAG   0x33445566//清事件标志
#define CLEAR_END_FLAG     0x00000000//无数据清除标志



//定义规约种类
#define PROTOCOL_DLT645 0 

typedef struct
{
    INT8U Energy_Digs;
    INT8U Power_Digs;
    INT8U CS[CS_BYTES];
}S_Disp_Digs;//定义功率和电能的显示位数

typedef struct
{
    INT8U Addr[1][6];
    INT8U CS[CS_BYTES];
}S_Meter_Addr;

typedef struct
{
    INT8U Head;
    INT8U Ch;
    INT8U Tail;
}S_Cur_Comm_Ch;

typedef struct
{
    INT8U Head;
    INT32U Flag; //清除标志
    
    INT8U Result; //清除结果 
    
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_Clear_Flag;

//定义源数据存储类型
#define S_RAM 0x00
#define S_ROM 0x01

///定义源数据类型,通过645设数据时，可根据一下类型判断,S_BCD类型的数据要求一定是BCD类数据
//必须进行BCD类型检查
#define S_INTS 0x00//是否有符号INT类型
#define S_INTU 0x01//是否无符号INT类型
#define S_BCD  0x02//是否为BCD类型,这种情况下源数据->目标数据无需进行格式转换
#define S_BIN  0x03//二进制状态字之类的

//定义源数据长度 
#define S_LEN8 0x08
#define S_LEN7 0x07
#define S_LEN6 0x06
#define S_LEN5 0x05
#define S_LEN4 0x04
#define S_LEN3 0x03
#define S_LEN2 0x02
#define S_LEN1 0x01

//定义目标数据在取数时的起始字节
#define D_START4 0x04
#define D_START3 0x03
#define D_START2 0x02
#define D_START1 0x01
#define D_START0 0x00

//定义目标数据的长度
#define D_LEN19 0x04
#define D_LEN18 0x03
#define D_LEN17 0x02
#define D_LEN16 0x01
#define D_LEN15 0x00
#define D_LEN14 0x04
#define D_LEN13 0x03
#define D_LEN12 0x02
#define D_LEN11 0x01
#define D_LEN10 0x00
#define D_LEN9 0x04
#define D_LEN8 0x03
#define D_LEN7 0x02
#define D_LEN6 0x01
#define D_LEN5 0x00
#define D_LEN4 0x04
#define D_LEN3 0x03
#define D_LEN2 0x02
#define D_LEN1 0x01
#define D_LEN0 0x00


//#define D_S_SAME 0x80

#define DI_EQU_NULL 0

//定义当前通信通道
#ifdef DATA_TRANS_C
EXT S_Cur_Comm_Ch Cur_Comm_Ch = {CHK_BYTE, 0, CHK_BYTE};
//EXT S_Int32U Prog_Event_Flag = {CHK_BYTE, 0, CHK_BYTE};
#endif
extern S_Cur_Comm_Ch Cur_Comm_Ch;
//extern S_Int32U Prog_Event_Flag; //编程事件记录


typedef struct
{
    PROTO_DI PDI;   //645协议的ID,该ID也是存储ID
    //PROTO_DI PDI_Equ;//与其DI完全等效的标示符，用于扩充协议于标准645协议对应

    INT8U DI_Set_Flag : 1;//DI数据项是否进入数据集中
    //INT8U DI_Equ_Set_Flag:1;//DI_Equ是否进入数据集中?

    INT8U PSW_Flag : 4;    //修改的密码等级

    INT8U Storage : 2;    //源存储属性,S_ROM或者S_RAM
    //INT16U Storage_DI;  //如果存储在Rom中，Storage_DI表示存储的编号

    volatile void* pSrc; //最终源数据的指针
    INT16U Src_Off;    //从pSrc中取源数据的偏移

    INT8U Src_Len;    //源数据长度,当源数据为S_INTU或S_INTS时可根据该长度得知数据具体类型 
    INT8U Src_Format;     //源数据的格式

    INT8U Dst_Start;  //目标数据在源数据的BCD缓冲中取数据的起始位置,如果源
    //数据是S_INTU数据类型,则目标数据的应该是源数据/Dst_Start后转化为BCD码
    INT8U Dst_Len;    //目标数据的提取长度,如果是S_BCD类型,则直接从源数据的Dst_Start字节处开始取数

    PROTO_DI Num;     //与此数据类似的数据项个数

    INT8U Spec_Flag;  //是否特殊数据项？如果是 Num域则是作为特殊项的一个参数
    //INT8U WR_Spec_Flag;
}S_Protocol_Data_Info;




#define CHK_PARA_NUM 5
typedef struct
{
    INT8U Head;
    INT8U Posi[OS_TASK_NUM];
    PROTO_DI Buf[OS_TASK_NUM][CHK_PARA_NUM];
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_Para_Modify;


EXT volatile S_Para_Modify Para_Modify;
//EXT volatile S_Operator_ID Operator_ID; //操作者ID
//EXT volatile S_Prog_Record Prog_Record;  //最近10个编程ID

////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////
#define SPEC_NO   0x00 //非特殊数据

//读特殊数据
#define SPEC_ENERGY   0x41 //电量
#define SPEC_DEMAND   0x42 //需量数据
#define SPEC_C_EVENT  0x43 //累加事件
#define SPEC_S_EVENT  0x44 //分次事件
#define SPEC_VOLSTAT  0x45 //电压统计数据
#define SPEC_FREEZE   0x46 //冻结数据

#define SPEC_FAC_INFO 0x47 //工厂信息
#define SPEC_LOAD     0x48 //负荷曲线
#define SPEC_RATE_INFO 0x49 //费率信息
#define SPEC_PSW       0x4A //密码信息
#define SPEC_RD_ROM    0x4B //读内卡参数
//#define SPEC_MODULE     0x0E //模块通信
//#define SPEC_SET_ENG  0x0F //设置初始电量
#define SPEC_PREPAID_ENERGY 0x4C //预付费相关电量 
#define SPEC_PREPAID_EVENT 0x4D //预付费事件记录，特殊处理
#define SPEC_EXTEND   0x4E //扩展数据

//写特殊数据
#define SPEC_METER_ID   0x81 //设置表号
#define SPEC_SET_ENG  0x82 //设置初始电量
//#define SPEC_ADJ_CLR  0x83 //校表清0
#define SPEC_MODULE   0x83 //模块通信
#define SPEC_ADJ      0x84 //校表
#define SPEC_METER_SPEC 0x85 //电表规格
//读和写都特殊
#define SPEC_TIME     0xC1 //时间和日期

//------------------定义扩展的通信DI--------------------//
#define _PDI_CUR_TIME      0x80000000   //当前时间，6字节，包含秒
#define _PDI_ALL_LOSS_VOL_CUR  0x80000001 //全失压发生时电流
#define _PDI_VOLT_MAX_UNBALANCE   0x80000002 //最大电压不平衡率
#define _PDI_CURR_MAX_UNBALANCE   0x80000003 //最大电流不平衡率
#define _PDI_CUR_TIME0     0x80000004 //当前时间，5字节，没有秒
#define _PDI_PD_TIME       0x80000005 //前次掉电时间
#define _PDI_PO_TIME       0x80000006 //当此上电时间
#define _PDI_PROG_TIME     0x80000007 //编程时间
#define _PDI_SET_METER_SPEC 0x80000008 //电表规格

#define _PDI_POS_ACTIVE_DEMAND  0x80000010 //需量超限期间最大有功需量及时间
#define _PDI_NEG_ACTIVE_DEMAND  0x80000011
#define _PDI_QUAD1_REACT_DEMAND 0x80000012
#define _PDI_QUAD2_REACT_DEMAND 0x80000013
#define _PDI_QUAD3_REACT_DEMAND 0x80000014
#define _PDI_QUAD4_REACT_DEMAND 0x80000015

#define _PDI_POS_ACTIVE_DEMAND_TIME  0x80000016 //需量超限期间最大有功需量及时间
#define _PDI_NEG_ACTIVE_DEMAND_TIME  0x80000017
#define _PDI_QUAD1_REACT_DEMAND_TIME 0x80000018
#define _PDI_QUAD2_REACT_DEMAND_TIME 0x80000019
#define _PDI_QUAD3_REACT_DEMAND_TIME 0x8000001A
#define _PDI_QUAD4_REACT_DEMAND_TIME 0x8000001B

#define _PDI_OPERATOR_ID  0x80000020  //当前操作者ID
#define _PDI_PROG_OP_ID   0x80000021  //一次编程记录的操作者ID
#define _PDI_PROG_DI      0x80000022 //编程标识
#define _PDI_CLR_EVENT_DI 0x80000023 //事件清零数据标识码

#define _PDI_TOTAL_AH 0x80000030
#define _PDI_A_AH     0x80000031
#define _PDI_B_AH     0x80000032
#define _PDI_C_AH     0x80000033

#define _PDI_ALL_LOSS_VOL_START_TIME 0x80000040 //全失压开始时间
#define _PDI_ALL_LOSS_VOL_END_TIME 0x80000041 //全失压结束时间
//------------------------------------------
//EXT volatile S_Prog_Flag Prog_Flag;//编程标识字
////定义扩充的DI,扩充的数据标识都以0x01开始,如果该数据存储在ROM中，则Data_Para_Storage中也定义该数据项//
//以下数据全部从当前ram里面取，以免和读取存储数据冲突
#define _PDI_REG_CKC                 0x80000042
#define _PDI_REG_CSC                 0x80000043

#define _PDI_LOW_VOL                 0x80000044
#define _PDI_CURRENT_QUADRANT        0x80000045
#define _PDI_METER_PERIPHERY         0x80000046
#define _PDI_MODULE_STATUS           0x80000047
#define _PDI_POWER_DOWN_TIME         0x80000048

#define _PDI_METER_ADDR0             0x80000050//第一路表地址,和METER_ADDR0一样
#define _PDI_METER_ADDR1             0x80000051//第二路表地址
#define _PDI_METER_ADDR2             0x80000052//第三路表地址

#define _PDI_COMM_BAUD0              0x80000053//第一路波特率,和COMM_BAUD0一样
#define _PDI_COMM_BAUD1              0x80000054//第二路波特率
#define _PDI_COMM_BAUD2              0x80000055//第三路波特率

#define _PDI_METER_SOFTWARE_VERSION  0x80000060//软件版本号
#define _PDI_METER_SPECIFI           0x80000081//电表规格

///一下数据是为负荷曲线增加,不要再此范围增加其他数据
#define _PDI_ACTIVE_DIRECT           0x80000062//有功方向
#define _PDI_REACTIVE_DIRECT         0x80000063//无功方向

//#define _DI_ACTIVE_DIRECT          0x0122//有功方向，包括总
//#define _DI_REACTIVE_DIRECT        0x0123//无功方向，包括总

//#define _PDI_REACTIVE_ALL            0x80000064//总无功功率
//#define _PDI_REACTIVE_A              0x80000065//A、B、C三项无功功率
//#define _PDI_REACTIVE_B              0x80000066
//#define _PDI_REACTIVE_C              0x80000067

//#define _PDI_CUR_TIME                0x80000043//当前BCD时间 年月日时分

#define _PDI_ACTIVE_DEMAND           0x80000068//有功需量
#define _PDI_REACTIVE_DEMAND         0x80000069//无功需量

//#define _PDI_TOTAL_AH                0x80000043//总AH,两位小数
//#define _PDI_A_AH                    0x80000043//A相总AH
//#define _PDI_B_AH                    0x80000043//B相总AH
//#define _PDI_C_AH                    0x80000043//C相总AH

//#define DI_TOTAL_AH                0x0151//总AH
//#define DI_A_AH                    0x0152//A相总AH
//#define DI_B_AH                    0x0153//B相总AH
//#define DI_C_AH                    0x0154//C相总AH

#define _PDI_A_VOL                   0x80000070//A相电压,2位小数,3字节
#define _PDI_B_VOL                   0x80000071//B相电压,2位小数
#define _PDI_C_VOL                   0x80000072//C相电压,2位小数

#define _PDI_A_CUR                   0x80000073//A相电流,4位小数,4字节
#define _PDI_B_CUR                   0x80000074//B相电流,4位小数
#define _PDI_C_CUR                   0x80000075//C相电流,4位小数

#define _PDI_A_ANGLE                 0x80000076//A相相角,2位小数,3字节
#define _PDI_B_ANGLE                 0x80000077//B相相角,2位小数,3字节
#define _PDI_C_ANGLE                 0x80000078//C相相角,2位小数,3字节
#define _PDI_SUM_ANGLE               0x80000079//总相角,2位小数,3字节

//#define _PDI_PROG_FLAG0              0x80000043//编程标识字1
//#define _PDI_PROG_FLAG1              0x80000043//编程标识字2

#define _PDI_ERR_TIME                0x80000080//错误的时钟数据
#define _PDI_ERR_ROM                 0x80000081//EEROM错误标识字

#define _PDI_CUR_DEMAND              0x80000082//当前需量

#define _PDI_TOTAL_PREPAID_ENERGY_COUNTS 0x80000083//累计购电次数
#define _PDI_TOTAL_PREPAID_ENERGY        0x80000084//累计购电量
#define _PDI_CUR_PREPAID_ENERGY          0x80000085//当此购电电量
#define _PDI_CUR_PREPAID_BEF_ENERGY      0x80000086//当前购电前总电量


#define _PDI_TOTAL_PREPAID_MONEY_COUNTS  0x80000087//累计购电次数
#define _PDI_TOTAL_PREPAID_MONEY         0x80000088//累计购电金额
#define _PDI_CUR_PREPAID_MONEY           0x80000089//当此购点金额
#define _PDI_CUR_PREPAID_BEF_MONEY       0x8000008A//当次购电前总金额

//#define _PDI_CLR_DEMAND_WAY          0x80000043//清需量方式
//#define _PDI_ADJ_FLAG                0x80000043//校表标识字

#define _PDI_ADJ_BEF_TIME            0x800000A0//校时前时间
#define _PDI_ADJ_AFT_TIME            0x800000A1//校时后时间

#define _PDI_RTC_ERR_TIME           0x800000A2 //硬件错误时钟

#define _PDI_NULL_1BYTE              0x800000EE//无意义的标识字 

///校表相关参数
#define _PDI_ADJ_METER_PARA_STATUS       _SDI_ADJ_METER_PARA_STATUS
#define _PDI_ADJ_METER_PUL_VOL_CUR_SPEC  _SDI_ADJ_METER_PUL_VOL_CUR_SPEC
#define _PDI_ADJ_METER_A_POW             _SDI_ADJ_METER_A_POW           
#define _PDI_ADJ_METER_B_POW             _SDI_ADJ_METER_B_POW           
#define _PDI_ADJ_METER_C_POW             _SDI_ADJ_METER_C_POW           
#define _PDI_ADJ_METER_A_PHASE           _SDI_ADJ_METER_A_PHASE         
#define _PDI_ADJ_METER_B_PHASE           _SDI_ADJ_METER_B_PHASE         
#define _PDI_ADJ_METER_C_PHASE           _SDI_ADJ_METER_C_PHASE         
#define _PDI_ADJ_METER_A_VOL             _SDI_ADJ_METER_A_VOL           
#define _PDI_ADJ_METER_B_VOL             _SDI_ADJ_METER_B_VOL           
#define _PDI_ADJ_METER_C_VOL             _SDI_ADJ_METER_C_VOL           
#define _PDI_ADJ_METER_A_CUR             _SDI_ADJ_METER_A_CUR           
#define _PDI_ADJ_METER_B_CUR             _SDI_ADJ_METER_B_CUR           
#define _PDI_ADJ_METER_C_CUR             _SDI_ADJ_METER_C_CUR
#define _PDI_ADJ_METER_CLR               _SDI_ADJ_METER_CLR
#define _PDI_RD_ROM                      _SDI_RD_ROM
#define _PDI_ADJ_INSTANT_DATA            0x10000211            //校表瞬时量数据打打包
//---------------------------------------------------------------------

//#define _PDI_EVENT_VOL               0x80000043//电压超限或者过压时的电压值

//#define _PDI_ALL_LOSS_VOL_START_TIME 0x80000043//全失压起始时间
//#define _PDI_ALL_LOSS_VOL_END_TIME   0x80000043//全失压结束时间

//#define _PDI_EVENT_TIME              0x80000043//事件发生时间

//#define _PDI_A_VOL_1                 0x80000084//A相电压,1位小数,3字节
//#define _PDI_B_VOL_1                 0x80000085//B相电压,1位小数
//#define _PDI_C_VOL_1                 0x80000086//C相电压,1位小数

//#define _PDI_A_CUR_3                 0x80000087//A相电流,3位小数,3字节
//#define _PDI_B_CUR_3                 0x80000088//B相电流,3位小数
//#define _PDI_C_CUR_3                 0x80000089//C相电流,3位小数

//#define _PDI_BROAD_ADJ_TIME          0x80000043 //定义广播校时DI,协议传输中暂时未用


//#define _PDI_EXTNED_START            0x80000043//扩充的DI的起始
//--------------------------------------------------------------//

////////////////////定义与通信兼容的存储DI///////////////
#define PDI_DEMAND_PERIOD      0x04000103 //需量周期
#define PDI_DEMAND_SLID    0x04000104 //滑差时间
#define PDI_ADJ_PULSE_WIDTH    0x04000105 //校表脉冲宽度
#define PDI_YEAR_SCHE_CHG_TIME   0x04000106 //年时区切换时间
#define PDI_DATE_SCHE_CHG_TIME   0x04000107 //日时段表切换时间

#define PDI_YEAR_PERIOD_NUM    0x04000201 //年时区数
#define PDI_DATE_TABLE_NUM     0x04000202 //日时段表数
#define PDI_DATE_PERIOD_NUM    0x04000203 //日时段数
#define PDI_RATE_NUM   0x04000204 //费率数
#define PDI_HOLIDAY_NUM    0x04000205 //公共节假日数
#define PDI_HARMONIC_NUM   0x04000206 //谐波次数

#define PDI_AUTO_CYCL_SCREEN_NUM 0x04000301 //自动循环显示屏数
#define PDI_SCREEN_SHOW_TIME   0x04000302 //没屏显示时间
#define PDI_ENERGY_DECIMAL_NUM   0x04000303 //显示电能小数位数
#define PDI_POWER_DECIMAL_NUM    0x04000304 //显示功率与需量小数位数
#define PDI_KEY_CYCL_SCREEN_NUM  0x04000305 //按键循环显示屏数

#define PDI_COMM_ADDR      0x04000401 //通信地址
#define PDI_METER_ID   0x04000402 //表号
#define PDI_ASSET_ID   0x04000403 //资产管理编码
#define PDI_RATED_VOL      0x04000404 //额定电压
#define PDI_RATED_CUR      0x04000405 //额定电流
#define PDI_MAX_CUR    0x04000406 //最大电流
#define PDI_ACTIVE_ACCU    0x04000407 //有功准确等级
#define PDI_REACTIVE_ACCU      0x04000408 //无功准确等级
#define PDI_ACTIVE_CONST   0x04000409 //电表有功常数
#define PDI_REACTIVE_CONST     0x0400040A //电表无功常数
#define PDI_METER_TYPE     0x0400040B //电表型号
#define PDI_METER_MADE_TIME    0x0400040C //电表生产日期
#define PDI_PROTOCOL_VER   0x0400040D //电表协议版本号

#define PDI_ACTIVE_PORT_WORD   0x04000601 //有功组合方式特征字
#define PDI_REACTIVE_PORT_WORD_1 0x04000602 //无功组合方式特征字1
#define PDI_REACTIVE_PORT_WORD_2 0x04000603 //无功组合方式特征字2

#define PDI_FAR_IRAD_BAUD      0x04000701 //调制红外远红外速度特征字
#define PDI_NEAR_IRAD_BAUD     0x04000702 //接触红外近红外速度特征字
#define PDI_COMM1_BAUD     0x04000703 //通信口1速度
#define PDI_COMM2_BAUD     0x04000704 //通信口2速度
#define PDI_COMM3_BAUD     0x04000705 //通信口3速度

#define PDI_WEEK_REST_DAY      0x04000801 //周休日特征字
#define PDI_WEEK_REST_DATE_TABLE 0x04000802 //周休日日时段表号

#define PDI_LOAD_REC_WORD      0x04000901 //负荷记录模式字
#define PDI_FREEZE_REC_WORD    0x04000902 //冻结记录模式字

#define PDI_LOAD_REC_START_TIME  0x04000A01 //负荷记录起始时间
#define PDI_LOAD_REC1_INTER_TIME 0x04000A02 //第一类负荷记录间隔时间
#define PDI_LOAD_REC2_INTER_TIME 0x04000A03 //第二类负荷记录间隔时间
#define PDI_LOAD_REC3_INTER_TIME 0x04000A04 //第三类负荷记录间隔时间
#define PDI_LOAD_REC4_INTER_TIME 0x04000A05 //第四类负荷记录间隔时间
#define PDI_LOAD_REC5_INTER_TIME 0x04000A06 //第五类负荷记录间隔时间
#define PDI_LOAD_REC6_INTER_TIME 0x04000A07 //第六类负荷记录间隔时间

#define PDI_MONTH_SETTLE_DAY1    0x04000B01 //每月第一结算日
#define PDI_MONTH_SETTLE_DAY2    0x04000B02 //每月第二结算日   
#define PDI_MONTH_SETTLE_DAY3    0x04000B03 //每月第三结算日

#define PDI_PSW0     0x04000C01 //第0级密码
#define PDI_PSW1     0x04000C02 //第1级密码
#define PDI_PSW2     0x04000C03 //第2级密码
#define PDI_PSW3     0x04000C04 //第3级密码
#define PDI_PSW4     0x04000C05 //第4级密码
#define PDI_PSW5     0x04000C06 //第5级密码
#define PDI_PSW6     0x04000C07 //第6级密码
#define PDI_PSW7     0x04000C08 //第7级密码
#define PDI_PSW8     0x04000C09 //第8级密码
#define PDI_PSW9     0x04000C0A //第9级密码

#define PDI_PHASE_A_CONDUC     0x04000D01 //A相电导率
#define PDI_PHASE_A_SUSCEP     0x04000D02 //A相电纳率
#define PDI_PHASE_A_RESIST     0x04000D03 //A相电阻率
#define PDI_PHASE_B_CONDUC     0x04000D04 //B相电导率
#define PDI_PHASE_B_SUSCEP     0x04000D05 //B相电纳率
#define PDI_PHASE_B_RESIST     0x04000D06 //B相电阻率
#define PDI_PHASE_C_CONDUC     0x04000D07 //C相电导率
#define PDI_PHASE_C_SUSCEP     0x04000D08 //C相电纳率
#define PDI_PHASE_C_RESIST     0x04000D09 //C相电阻率

#define PDI_POS_ACTIVE_UP_LIMIT  0x04000E01 //正向有功功率上限
#define PDI_NEG_ACTIVE_LOW_LIMIT 0x04000E02 //反向有功功率上限
#define PDI_VOL_UP_LIMIT   0x04000E03 //电压上限值
#define PDI_VOL_LOW_LIMIT      0x04000E04 //电压下限

#define PDI_SCHE1_YEAR_TABLE   0x04010000 //第一套时区表
#define PDI_SCHE1_DATE_TABLE1    0x04010001 //第一套第一日时段表
#define PDI_SCHE1_DATE_TABLE2    0x04010002 //第一套时二日时段表
#define PDI_SCHE1_DATE_TABLE3    0x04010003 //第一套时三日时段表
#define PDI_SCHE1_DATE_TABLE4    0x04010004 //第一套时四日时段表
#define PDI_SCHE1_DATE_TABLE5    0x04010005 //第一套时五日时段表
#define PDI_SCHE1_DATE_TABLE6    0x04010006 //第一套时六日时段表
#define PDI_SCHE1_DATE_TABLE7    0x04010007 //第一套时七日时段表
#define PDI_SCHE1_DATE_TABLE8    0x04010008 //第一套时八日时段表

#define PDI_SCHE2_YEAR_TABLE   0x04020000 //第二套时区表
#define PDI_SCHE2_DATE_TABLE1    0x04020001 //第二套第一日时段表
#define PDI_SCHE2_DATE_TABLE2    0x04020002 //第二套时二日时段表
#define PDI_SCHE2_DATE_TABLE3    0x04020003 //第二套时三日时段表
#define PDI_SCHE2_DATE_TABLE4    0x04020004 //第二套时四日时段表
#define PDI_SCHE2_DATE_TABLE5    0x04020005 //第二套时五日时段表
#define PDI_SCHE2_DATE_TABLE6    0x04020006 //第二套时六日时段表
#define PDI_SCHE2_DATE_TABLE7    0x04020007 //第二套时七日时段表
#define PDI_SCHE2_DATE_TABLE8    0x04020008 //第二套时八日时段表

#define PDI_HOLIDAY_DATE_TABLE   0x04030001 //公共节假日及日时段表号
#define PDI_AUTO_CYCL_SREEN_DATA 0x04040101 //自动循环显示屏号
#define PDI_KEY_CYCL_SREEN_DATA  0x04040201 //按键循环显示屏号


#define PDI_CUR_RATE_SCHEME         0x0E010000//当前年时区方案
#define PDI_CUR_YEAR_PERIOD         0x0E010001//当前年时区号
#define PDI_CUR_DATE_TABLE_SCHEME   0x0E010002 //当前日时段表方案
#define PDI_CUR_DATE_TABLE          0x0E010003 //当前日时段表号
#define PDI_CUR_DATE_PERIOD         0x0E010004 //当前日时段号
#define PDI_CUR_RATE                0x0E010005 //当前费率

#define PDI_CUR_POS_ACTIVE_DEMAND   0x0E010301 //当前正向有功需量
#define PDI_CUR_NEG_ACTIVE_DEMAND   0x0E010302 //当前反向有功需量
#define PDI_CUR_COMB1_REAC_DEMAND   0x0E010303 //当前组合无功1需量
#define PDI_CUR_COMB2_REAC_DEMAND   0x0E010304 //当前组合无功2需量
#define PDI_CUR_QUAD1_REAC_DEMAND   0x0E010305 //当前一象限无功需量
#define PDI_CUR_QUAD2_REAC_DEMAND   0x0E010306 //当前二象限无功需量
#define PDI_CUR_QUAD3_REAC_DEMAND   0x0E010307 //当前三象限无功需量
#define PDI_CUR_QUAD4_REAC_DEMAND   0x0E010308 //当前四象限无功需量

#define PDI_CUR_RATE1_FEE  0x0E020001  //当前费率电价
#define PDI_CUR_RATE2_FEE  0x0E020002
#define PDI_CUR_RATE3_FEE  0x0E020003
#define PDI_CUR_RATE4_FEE  0x0E020004

#define PDI_CUR_STEP1_ENG    0x0E020101  //当前阶梯1电量
#define PDI_CUR_STEP2_ENG    0x0E020102
#define PDI_CUR_STEP3_ENG    0x0E020103
#define PDI_CUR_STEP4_ENG    0x0E020104

#define PDI_CUR_STEP1_FEE  0x0E020201 //当前阶梯1电价
#define PDI_CUR_STEP2_FEE  0x0E020202
#define PDI_CUR_STEP3_FEE  0x0E020203
#define PDI_CUR_STEP4_FEE  0x0E020204
#define PDI_CUR_STEP5_FEE  0x0E020205

typedef struct
{
    INT8U Head;

    INT8U Err_Flag;//错误标志
    INT8U Tail;
}S_Sys_Run_Flag;

typedef struct
{
    PROTO_DI PDI;   //645协议的ID,该ID也是存储ID
    //PROTO_DI PDI_Equ;//与其DI完全等效的标示符，用于扩充协议于标准645协议对应

    INT8U DI_Set_Flag : 1;//DI数据项是否进入数据集中
    //INT8U DI_Equ_Set_Flag:1;//DI_Equ是否进入数据集中?

    INT8U PSW_Flag : 5;    //修改的密码等级

    INT8U Storage : 2;    //源存储属性,S_ROM或者S_RAM
    //INT16U Storage_DI;  //如果存储在Rom中，Storage_DI表示存储的编号

    volatile void* pSrc; //最终源数据的指针
    //INT16U Src_Off;    //从pSrc中取源数据的偏移

    INT8U Src_Len;    //源数据长度,当源数据为S_INTU或S_INTS时可根据该长度得知数据具体类型 
    INT8U Src_Format:3;     //源数据的格式

    INT8U Dst_Start:5;  //目标数据在源数据的BCD缓冲中取数据的起始位置,如果源
    //数据是S_INTU数据类型,则目标数据的应该是源数据/Dst_Start后转化为BCD码
    INT8U Dst_Len;    //目标数据的提取长度,如果是S_BCD类型,则直接从源数据的Dst_Start字节处开始取数

    PROTO_DI Num;     //与此数据类似的数据项个数

    INT8U Spec_Flag;  //是否特殊数据项？如果是 Num域则是作为特殊项的一个参数
}S_P_Data_Info;

typedef struct
{
  INT8U Head;
  
  INT8U Read_Follow_Flag;//读后续帧标志
  INT8U Read_Seq;
  
  //INT8U Multi_Single_Flag;//单或者多帧标志
  INT8U Follow_Flag; //有无后续帧标志
  INT8U Frame_Seq; //前次帧序列号
  
  //INT16U Bak_0;
  //INT16U Bak_1;
  
  INT8U Tail;
}S_Frame_Ack_Info;

extern CONST S_P_Data_Info P_Data_Info[];

DECLARE_BUF_TYPE(INT8U, 200, S_Trans_Temp_Buf);

EXT volatile S_Int32U Meter_Addr_Ready_Flag;
EXT volatile S_Meter_Addr Meter_Addr;
EXT volatile S_Frame_Ack_Info Frame_Ack_Info;
EXT volatile S_Clear_Flag Clear_Flag;
EXT volatile S_Sys_Run_Flag Sys_Run_Flag;

#ifdef DATA_TRANS_C
EXT volatile S_Int8U Module_Comm_Status = {CHK_BYTE, 0, CHK_BYTE};
#else
EXT volatile S_Int8U Module_Comm_Status;
#endif

#ifdef DATA_TRANS_C
EXT volatile S_Trans_Temp_Buf _Trans_Temp_Buf = {CHK_BYTE, {0}, CHK_BYTE};
#else
EXT volatile S_Trans_Temp_Buf _Trans_Temp_Buf;
#endif

#define Trans_Temp_Buf _Trans_Temp_Buf.Buf

EXT void Set_Prog_Record(PROTO_DI PDI, INT8U Op_ID[]);
EXT void Set_Para_Modify(PROTO_DI PDI);
EXT INT8U Get_Para_Modify(PROTO_DI* pDI);
EXT INT8U Check_P_Data_Single(INT16U Index, PROTO_DI PDI, INT8U Data_Flag, INT8U* pSpec_Flag);
EXT INT8U Check_Protocol_Data_Storage();
EXT INT8U Get_DLT645_Data_Storage_Type(PROTO_DI PDI);
EXT INT8U Get_DLT645_Data_Src_Type(PROTO_DI PDI);
EXT INT8U Get_P_Data_PSW_Level(PROTO_DI PDI);
EXT INT8U Check_Block_DI(PROTO_DI PDI);
EXT INT8U Check_P_Data_In_Block(INT16U Index, PROTO_DI PDI);
EXT INT16U Get_DLT645_Spec_Single_Data(PROTO_DI PDI, INT8U Spec_Flag, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Get_DLT645_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U DLT645_Data_Pack(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT16U SrcLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT32U Pow_10x(INT8U a);
EXT INT8U Check_P_Data_Single(INT16U Index, PROTO_DI PDI, INT8U Data_Flag, INT8U* pSpec_Flag);
EXT INT16U Get_P_Data_Index(PROTO_DI PDI);
EXT INT16U Get_P_Data_Info_Num();

EXT INT8U Phase_Get_Addr_Frame(INT8U *pSrc, INT16U SrcLen);
EXT INT16U Search_Protocol_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset);
EXT INT16U Simple_Search_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset);
EXT INT8U Check_Frame_Format(INT8U *pFrame,INT8U FrameLen);
EXT INT8U Check_WR_Comm_Addr(INT8U Addr[]);

EXT INT16U Get_DLT645_Normal_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Rcv_PROTOCOL_Frame_Proc(INT8U Ch,INT8U *pSrc,INT16U SrcLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen);
EXT INT16U Rcv_DLT645_Data_Proc(INT8U Ch, INT8U* pFrame, INT8U FrameLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT void Send_Set_Data_Ack_Frame(INT8U Ch);

EXT INT8U Set_Data_Format_Check(INT8U* pSrc, INT8U SrcLen, INT16U *pIndex);
EXT INT8U Set_DI_Data_Proc(INT16U Index, PROTO_DI PDI, INT8U* pSrc, INT8U SrcLen);
EXT INT8U Set_Spec_Data_Proc(PROTO_DI PDI, INT8U Spec_Flag, INT8U* pSrc, INT8U SrcLen);

EXT void Prog_Timer_Proc();
EXT void Clr_Prog_Record_Ram();
EXT void Read_Data_Trans_Para_From_Rom();
EXT void Init_Data_Trans_Ram_Para();
EXT void Record_Op_ID(INT8U *pSrc);
EXT void Set_Clear_Data_Flag(INT32U Flag);
EXT INT16U _Get_DLT645_Data(PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag, INT8U* pType);
EXT INT16U Get_DLT645_Data_For_Disp(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U *pType);
EXT INT16U Get_DLT645_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U Get_DLT645_Block_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag);
EXT INT16U Convert_Src_2_Proto_Data(PROTO_DI PDI[], INT8U DI_Num, INT8U* pSrc, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U Proto_Data_Add_Dec(INT8U Data_Flag, INT8U Add_Or_Dec, PROTO_DI PDI[], INT8U DI_Num, INT8U* pData0, INT8U* pData1, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT32U Check_Clear_Data_Flag();
EXT INT8U Check_Protocol_Data_Trans();
#endif
