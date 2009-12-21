#define DEF_PARA_C
#include "Includes.h"

#define UB (INT32U)220 //额定电压
#define IB (INT32U)500 //1.50,两位小数 
#define PB (UB*IB) //额定功率
#define PMAX (UB*IB*4) //最大功率

#define HEX2BCD_4B(X) ((INT32U)(X)%10 + ((((INT32U)(X)/10)%10) << 4) + \
                       ((((INT32U)(X)/100)%10) << 8) + ((((INT32U)(X)/1000)%10) << 12) + \
                       ((((INT32U)(X)/10000)%10) << 16) + ((((INT32U)(X)/100000)%10) << 20) + \
                       ((((INT32U)(X)/1000000)%10) << 24) + ((((INT32U)(X)/10000000)%10) << 24) + \
                       ((((INT32U)(X)/100000000)%10) << 28) + ((((INT32U)(X)/1000000000)%10) << 28))
CONST INT8U Zero[200] =
{
  0
};

//默认校表参数
CONST INT8U Def_SDI_ADJ_METER_PUL_VOL_CUR_SPEC[]={0x00,0x01,0x00};
CONST INT8U Def_SDI_ADJ_METER_PARA_STATUS[]={0x00};
/*
CONST INT8U Def_ADJ_METER_A_POW[36]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
                                     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
CONST INT8U Def_MeterAddr0[]={0x00,0x00,0x00,0x00,0x00,0x00};
CONST INT8U Def_MeterAddr1[]={0x00,0x00,0x00,0x00,0x00,0x00};
*/
CONST INT8U Def_SDI_ADJ_METER_A_POW[]= 
{
BYTE_0(0x000C491E),BYTE_1(0x000C491E),BYTE_2(0x000C491E),
BYTE_0(0x000D08FA),BYTE_1(0x000D08FA),BYTE_2(0x000D08FA),
BYTE_0(0x000C3D32),BYTE_1(0x000C3D32),BYTE_2(0x000C3D32),
          
BYTE_0(0x00000000),BYTE_1(0x00000000),BYTE_2(0x00000000),
BYTE_0(0x00000000),BYTE_1(0x00000000),BYTE_2(0x00000000),
BYTE_0(0x00000000),BYTE_1(0x00000000),BYTE_2(0x00000000),
          
BYTE_0(0x000020CD),BYTE_1(0x000020CD),BYTE_2(0x000020CD),
BYTE_0(0x0001665E),BYTE_1(0x0001665E),BYTE_2(0x0001665E),
BYTE_0(0x00011A6E),BYTE_1(0x00011A6E),BYTE_2(0x00011A6E),
          
BYTE_0(0x00450100),BYTE_1(0x00450100),BYTE_2(0x00450100),
BYTE_0(0x00442897),BYTE_1(0x00442897),BYTE_2(0x00442897),
BYTE_0(0x00439E74),BYTE_1(0x00439E74),BYTE_2(0x00439E74),
  
};

//--当前使用的年时区表号和日时段表号,以及当前所处的方案时间
CONST S_Cur_Scheme Def_SDI_CUR_SCHEME =
{
  .Head = CHK_BYTE,
  .Year_Scheme = YEAR_SCHEME0,
  .Date_Scheme = DATE_SCHEME0,
  .Rate_Scheme = RATE_SCHEME0,
  .Step_Scheme = STEP_SCHEME0,
  
  .Year_Scheme_Time = BEF_SWITCH_TIME,
  .Date_Scheme_Time = BEF_SWITCH_TIME,
  .Rate_Scheme_Time = BEF_SWITCH_TIME,
  .Step_Scheme_Time = BEF_SWITCH_TIME,
  
  .CS = {0},
  .Tail = CHK_BYTE
};

//-------------------------5个模式字
CONST INT8U Def_SDI_MODEWORD_1_5[] =
{
  0x03,
  0x02,
  0x00,
  0x02,
  0x06,
  0x03,
};

//---电压考核上下限---
CONST INT8U Def_0E000101_2[]=
{
  0x20,0x26,//电压考核上限 262
  0x80,0x17,//电压考核下限 178V  
};

//失压启动电压电流
CONST INT8U Def_0E000103[]=
{
  0x78,0x00,0x10,0x00  
};

//失压判断时间
CONST INT8U Def_0E000104[]=
{
  0x10  
};

//失流启动电流、结束电流
CONST INT8U Def_0E000105_2[]=
{
  0x30,0x00,0x00,//启动电流
  0x30,0x00,0x00 //结束电流 
};

//失流判断时间
CONST INT8U Def_0E000107[]=
{
  0x10,//失流判断时间
};

CONST INT8U Def_0E000108[] =
{
  0x60 //临界电压
};

//断相启动电流
CONST INT8U Def_0E000109[]=
{
  0x75,0x00,0x00//断相启动电流
};

//断相判断时间
CONST INT8U Def_0E00010A[]=
{
  0x60//断相判断时间
};

//过压判断阀值
CONST INT8U Def_0E00010B[]=
{
  0x20,0x01//过压判断阀值 %
};

//用户级别、跳闸延时、合闸延时
CONST INT8U Def_0E00010C_3[]=
{
  0x01,0x02,0x02
};

//电流不平衡上限
CONST INT8U Def_0E00010F[]=
{
  0x00,0x50,0x01//电流不平衡上限
};

//电压不平衡上限
CONST INT8U Def_0E000110[]=
{
  0x00,0x50,0x01//电压不平衡上限   
};

//失压启动电压
CONST INT8U Def_0E000111[]=
{
  0x78//%78   
};

//失压启动电流
CONST INT8U Def_0E000112[]=
{
 0x00,0x10,0x00 
};

//欠压判断阀值
CONST INT8U Def_0E000113[]=
{
  0x60// 
};

//过流判断阀值
CONST INT8U Def_0E000114[]=
{
 0x00,0x03//%
};

//每日广播校时允许次数
CONST INT8U Def_SDI_ADJ_TIME_COUNTS[]=
{
  0x01
};
/*
  {0x0E000101, IMP_IMP_PARA, 2, 2},
  {0x0E000103, IMP_IMP_PARA, 4, 1},
  {0x0E000104, IMP_IMP_PARA, 1, 1},
  {0x0E000105, IMP_IMP_PARA, 3, 2},
  {0x0E000107, IMP_IMP_PARA, 1, 2},
  {0x0E000109, IMP_IMP_PARA, 3, 1},
  {0x0E00010A, IMP_IMP_PARA, 1, 1},
  {0x0E00010B, IMP_IMP_PARA, 2, 1},
  {0x0E00010C, IMP_IMP_PARA, 1, 2},
  {0x0E00010E, IMP_IMP_PARA, 1, 1},
  {0x0E00010F, IMP_IMP_PARA, 3, 1},
  {0x0E000110, IMP_IMP_PARA, 3, 1},
  {0x0E000111, IMP_IMP_PARA, 1, 1},
  {0x0E000112, IMP_IMP_PARA, 3, 1},
  {0x0E000113, IMP_IMP_PARA, 1, 1},
  {0x0E000114, IMP_IMP_PARA, 2, 1},  
*/
//---------------------------
CONST INT32U Def_SDI_LAST_SETTLE_ENERGY_DI[] =
{
  _SDI_SETTLE_ENERGY_DATA
};

CONST INT32U Def_SDI_LAST_SETTLE_DEMAND_DI[] =
{
  _SDI_SETTLE_DEMAND_DATA
};

CONST INT32U Def_SDI_LAST_SETTLE_VOLSTAT_DI[] =
{
  _SDI_SETTLE_VOLSTAT_DATA
};

//需量周期和滑差时间
CONST INT8U Def_04000103_2[] =
{
  0x15, 0x01, 
};

//校表脉冲宽度
CONST INT8U Def_04000105[] =
{
  0x80, 0x00, 
};

//两套时区表切换时间
CONST INT8U Def_04000106[] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

//两套日时段表切换时间
CONST INT8U Def_04000107[] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

//两套费率方案切换时间
CONST INT8U Def_04000108[] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

//两套阶梯方案切换时间
CONST INT8U Def_04000109[] =
{
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

//年时区数等
CONST INT8U Def_04000201_4[] =
{
  0x02, //年时区数
  0x02, //日时段表数
  0x08, //日时段数
  0x04, //费率数

};

//公共假日数
CONST INT8U Def_04000205[] =
{
  0x00, 0x00, 
};

//谐波分析次数
CONST INT8U Def_04000206[] =
{
  0x00
};

//预付费阶数
CONST INT8U Def_04000207[]=
{
  0x01 
};

//电流互感器变比
CONST INT8U Def_04000306[] = 
{
  0x01,0x00,0x00 
};

//电压互感器变比
CONST INT8U Def_04000307[] =
{
  0x01,0x00,0x00
};

//电量预付费相关参数
CONST INT32U Def_04000F01_4[] = 
{
  0x00001000, //报警电量1
  0x00000500, //报警电量2
  0x10000000, //囤积电量限值
  0x00002000  //透支电量限值
};

//电费预付费相关参数
CONST INT32U Def_04001001_5[] =
{
  0x0001000, //报警金额1
  0x0000500, //报警金额2
  0x0002000, //透支金额限值
  0x9999999, //囤积金额限值
  0x0000000, //合闸允许金额限值
};

//电表运行特征字
CONST INT8U Def_04001101[] =
{
  0x00
};

//跳闸延时
CONST INT8U Def_SDI_RELAY_OFF_DELAY[] =
{
  0x01, 0x00
};

//功率负荷脉冲数
CONST INT32U Def_0400E001[] =
{
   0x00050000
};

//最大负荷计算时间,过负荷跳闸次数门限
CONST INT8U Def_0400E002_2[] =
{
  0x10,
  0x05
};

//电费显示小数位数
CONST INT8U Def_0400E101[] =
{
  0x03
};

//预付费模式字
CONST INT8U Def_0400E201_3[] =
{
  0x00,
  0x00,
  0x00
};

//通信地址
CONST INT8U Def_04000401[] =
{
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11
};

//表号
CONST INT8U Def_04000402[] =
{
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

//资产管理编号
#define Def_04000403 "00000000000000000000000000000000"

//额定电压
CONST INT8U Def_04000404[] =
{
  "   022"
};
//额定电流
CONST INT8U Def_04000405[] =
{
  "  0.01"
};
//最大电流
CONST INT8U Def_04000406[] =
{
  "  0.04"
};
//有功准确度等级
CONST INT8U Def_04000407[] =
{
  " 0.1"
};
//无功准确度等级
CONST INT8U Def_04000408[] =
{
  " 0.2"
};

//有无功脉冲常数
CONST INT8U Def_04000409_2[] =
{
  0x00, 0x04, 0x00, 
  0x00, 0x04, 0x00
};

//电表型号
CONST INT8U Def_0400040B[] =
{
  "     001RD"
};
//生产日期
CONST INT8U Def_0400040C[] =
{
  "6061807090"
};

//协议版本号
/*
CONST INT8U Def_0400040D[] =
{
  "DLT645-2007"
};

//软件版本号
CONST INT8U Def_0400040E[] =
{
  
}
*/

//硬件版本号
CONST INT8U Def_04800002[] = "                             001";// Hardware_Version

//有无功组合方式特征字
CONST INT8U Def_04000601_3[] =
{
  0x05,//有功
  0x05,//无功组合1
  0x50,//无功组合2

};

//各通信口波特率特征字
CONST INT8U Def_04000701_5[] =
{
  0x04,//调制红外
  0x04,//接触红外
  0x08,//通信口1
  0x08,//通信口2
  0x40 //通信口3

};

//周休日特征字等
CONST INT8U Def_04000801_2[] =
{
  0x7F,//周休日特征字
  0x01 //周休日采用的日时段表号

};

//负荷记录模式字
CONST INT8U Def_04000901_6[] =
{
  0x3F,//负荷记录模式字
  0xFF,//定时冻结数据模式字
  0xFF,//瞬时冻结数据模式字
  0xFF,//约定冻结数据模式字
  0x03,//整点冻结数据模式字
  0xFF,//日冻结数据模式字
};

//负荷记录起始时间
CONST INT8U Def_04000A01[] =
{
  0x00, 0x00, 0x01, 0x01//分、时、日、月

};

//负荷记录间隔时间
CONST INT8U Def_04000A02_6[] =
{
  0x30, 0x00,//第一类负荷记录
  0x30, 0x00,//第二类
  0x30, 0x00,//第三类
  0x30, 0x00,//第四类
  0x30, 0x00,//第五类
  0x30, 0x00,//第六类

};

//每月结算时间
CONST INT8U Def_04000B01_3[] =
{
  0x00, 0x01,//每月第一结算日
  0xFF, 0xFF,//每月第二结算日
  0xFF, 0xFF,//每月第三结算日

};

#define NO_USE_PSW 0x00,0x00,0x00
//9级密码
CONST INT8U Def_04000C01_10[] =
{
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00, 
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00,
  0x11, 0x11, 0x11,
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00,
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00, 
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00,
  NO_USE_PSW,//0x00, 0x00, 0x00, 0x00, 
  NO_USE_PSW //0x00, 0x00, 0x00, 0x00,  
};

//正反向有功功率上限
CONST INT8U Def_04000E01_2[] =
{
  0x00, 0x00, 0x20,//正向有功功率上限
  0x00, 0x00, 0x20//反向有功功率上限

};

//电压上下限
CONST INT8U Def_04000E03_2[] =
{
  0x00, 0x24,//电压上限
  0x00, 0x20 //电压下限

};

//整点冻结起始时间, 分、时、日、月、年
CONST INT8U Def_04001001[] = 
{
  0x00, 0x00, 0x00, 0x00, 0x00
};

//整点冻结间隔时间
CONST INT8U Def_04001002[] =
{
  0x60 
};

//日冻结时间,分、时
CONST INT8U Def_04001003[] =
{
  0x00, 0x00
};

//第一套年时区表,第二套默认参数同第一套
CONST INT8U Def_04010000[] =
{
  1, 1, 1,
  1, 1, 1,
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1, 
  1, 1, 1,
  1, 1, 1  
};

//第一套第一日时段表,第2-8日时段表同第一日时段表
//第二套默认参数同第一套
CONST INT8U Def_04010001[] =
{
 0x01, 0x00,  0x00,
 0x02, 0x00,  0x03,
 0x03, 0x00,  0x06,
 0x04, 0x00,  0x09,
 0x01, 0x00,  0x12,
 0x02, 0x00,  0x15,
 0x03, 0x00,  0x18,
 0x04, 0x00,  0x21,
 0x04, 0x00,  0x21,
 0x04, 0x00,  0x21,
 0x04, 0x00,  0x21,
 0x04, 0x00,  0x21,
 0x04, 0x00,  0x21,
 0x04, 0x00,  0x21
};

//公共节假日,默认没有公共节假日
#define Def_04030001 Zero

#pragma pack(1)

typedef struct
{
  INT8U Sub_ID;
  INT32U Main_ID;
}S_Disp_Item;

#if PREPAID_METER > 0 && PREPAID_LOCAL_REMOTE == PREPAID_LOCAL//费控电能表的显示项目
//自动循环显示数据项
CONST S_Disp_Item Def_04040101_13[] =
{
{0x00,0x04000101},//显示当前日期              
{0x00,0x04000102},//显示当前时间              
{0x00,0x00900200},//当前剩余金额              
{0x00,0x00000000},//显示当前组合有功总电量    
{0x00,0x00010000},//显示当前正向有功总电量    
{0x00,0x00010100},//显示当前正向有功尖电量    
{0x00,0x00010200},//显示当前正向有功峰电量    
{0x00,0x00010300},//显示当前正向有功平电量    
{0x00,0x00010400},//显示当前正向有功谷电量    
{0x00,0x01010000},//显示当前正向有功总最大需量
//{0x00,0x00030000},//显示当前组合无功1总电量   
//{0x00,0x00040000},//显示当前组合无功2总电量   
{0x00,0x00050000},//显示当前Ⅰ象限无功电量    
{0x00,0x00060000},//显示当前Ⅱ象限无功电量    
{0x00,0x00070000},//显示当前Ⅲ象限无功电量    
{0x00,0x00080000},//显示当前Ⅳ象限无功电量    
{0x00,0x00020000},//显示当前反向有功总电量    
{0x00,0x00020100},//显示当前反向有功尖电量    
{0x00,0x00020200},//显示当前反向有功峰电量    
{0x00,0x00020300},//显示当前反向有功平电量    
{0x00,0x00020400} //显示当前反向有功谷电量    

};


//按键循环显示数据项
CONST S_Disp_Item Def_04040201_20[] =
{
{0x00,0x04000101},//当前日期                             
{0x00,0x04000102},//当前时间                             
{0x00,0x00900200},//当前剩余金额                         
{0x00,0x00000000},//当前组合有功总电量                   
{0x00,0x00010000},//当前正向有功总电量                   
{0x00,0x00010100},//当前正向有功尖电量                   
{0x00,0x00010200},//当前正向有功峰电量                   
{0x00,0x00010300},//当前正向有功平电量                   
{0x00,0x00010400},//当前正向有功谷电量                   
{0x00,0x01010000},//当前正向有功总最大需量               
{0x01,0x01010000},//当前正向有功总最大需量发生日期       
{0x02,0x01010000},//当前正向有功总最大需量发生时间       
{0x00,0x00020000},//当前反向有功总电量                   
{0x00,0x00020100},//当前反向有功尖电量                   
{0x00,0x00020200},//当前反向有功峰电量                   
{0x00,0x00020300},//当前反向有功平电量                   
{0x00,0x00020400},//当前反向有功谷电量                   
{0x00,0x01020000},//当前反向有功总最大需量               
{0x01,0x01020000},//当前反向有功总最大需量发生日期       
{0x02,0x01020000},//当前反向有功总最大需量发生时间       
//{0x00,0x00030000},//当前组合无功总电量1                  
//{0x00,0x00040000},//当前组合无功总电量2                  
{0x00,0x00050000},//当前Ⅰ象限无功总电量                 
{0x00,0x00060000},//当前Ⅱ象限无功总电量                 
{0x00,0x00070000},//当前Ⅲ象限无功总电量                 
{0x00,0x00080000},//当前Ⅳ象限无功总电量                 
{0x00,0x00010001},//上1月正向有功总电量                  
{0x00,0x00010101},//上1月正向有功尖电量                  
{0x00,0x00010201},//上1月正向有功峰电量                  
{0x00,0x00010301},//上1月正向有功平电量                  
{0x00,0x00010401},//上1月正向有功谷电量                  
{0x00,0x01010001},//上1月正向有功总最大需量              
{0x01,0x01010001},//上1月正向有功总最大需量发生日期      
{0x02,0x01010001},//上1月正向有功总最大需量发生时间      
{0x00,0x00020001},//上1月反向有功总电量                  
{0x00,0x00020101},//上1月反向有功尖电量                  
{0x00,0x00020201},//上1月反向有功峰电量                  
{0x00,0x00020301},//上1月反向有功平电量                  
{0x00,0x00020401},//上1月反向有功谷电量                  
{0x00,0x01020001},//上1月反向有功总最大需量              
{0x01,0x01020001},//上1月反向有功总最大需量发生日期      
{0x02,0x01020001},//上1月反向有功总最大需量发生时间      
{0x00,0x00050001},//上1月Ⅰ象限无功总电量                
{0x00,0x00060001},//上1月Ⅱ象限无功总电量                
{0x00,0x00070001},//上1月Ⅲ象限无功总电量                
{0x00,0x00080001},//上1月Ⅳ象限无功总电量                
{0x01,0x04000401},//电能表通信地址（表号）低8位          
{0x00,0x04000401},//电能表通信地址（表号）高4位          
{0x00,0x04000703},//通信波特率（RS485-1）                
{0x00,0x04000409},//有功脉冲常数                         
{0x00,0x0400040a},//无功脉冲常数                         
{0x00,0x0280000a},//时钟电池使用时间                     
{0x01,0x03300001},//最近一次编程日期                     
{0x00,0x03300001},//最近一次编程时间                     
{0x00,0x10000001},//总失压次数                           
{0x00,0x10000002},//总失压累计时间                       
{0x01,0x10000101},//最近一次失压起始日期                 
{0x00,0x10000101},//最近一次失压起始时间                 
{0x01,0x10000201},//最近一次失压结束日期                 
{0x00,0x10000201},//最近一次失压结束时间                 
{0x00,0x10010201},//最近一次A相失压起始时刻正向有功总电量
{0x00,0x10012601},//最近一次A相失压结束时刻正向有功总电量
{0x00,0x10010301},//最近一次A相失压起始时刻反向有功总电量
{0x00,0x10012701},//最近一次A相失压结束时刻反向有功总电量
{0x00,0x10020201},//最近一次B相失压起始时刻正向有功总电量
{0x00,0x10022601},//最近一次B相失压结束时刻正向有功总电量
{0x00,0x10020301},//最近一次B相失压起始时刻反向有功总电量
{0x00,0x10022701},//最近一次B相失压结束时刻反向有功总电量
{0x00,0x10030201},//最近一次C相失压起始时刻正向有功总电量
{0x00,0x10032601},//最近一次C相失压结束时刻正向有功总电量
{0x00,0x10030301},//最近一次C相失压起始时刻反向有功总电量
{0x00,0x10032701},//最近一次C相失压结束时刻反向有功总电量
{0x00,0x02010100},//A相电压                              
{0x00,0x02010200},//B相电压                              
{0x00,0x02010300},//C相电压                              
{0x00,0x02020100},//A相电流                              
{0x00,0x02020200},//B相电流                              
{0x00,0x02020300},//C相电流                              
{0x00,0x02030000},//瞬时总有功功率                       
{0x00,0x02030100},//瞬时A相有功功率                      
{0x00,0x02030200},//瞬时B相有功功率                      
{0x00,0x02030300},//瞬时C相有功功率                      
{0x00,0x02060000},//瞬时总功率因数                       
{0x00,0x02060100},//瞬时A相功率因数                      
{0x00,0x02060200},//瞬时B相功率因数                      
{0x00,0x02060300},//瞬时C相功率因数     
#if PREPAID_MONEY_MODE EQ PREPAID_RATE
{0x00,PDI_CUR_RATE1_FEE},//当前尖费率电价                       
{0x00,PDI_CUR_RATE2_FEE},//当前峰费率电价                       
{0x00,PDI_CUR_RATE3_FEE},//当前平费率电价                       
{0x00,PDI_CUR_RATE4_FEE},//当前谷费率电价
#else
{0x00,PDI_CUR_STEP1_ENG},//阶梯1电量                            
{0x00,PDI_CUR_STEP2_ENG},//阶梯2电量                            
{0x00,PDI_CUR_STEP3_ENG},//阶梯3电量                            
{0x00,PDI_CUR_STEP4_ENG},//阶梯4电量                            
{0x00,PDI_CUR_STEP1_FEE},//阶梯1电价                            
{0x00,PDI_CUR_STEP2_FEE},//阶梯2电价                            
{0x00,PDI_CUR_STEP3_FEE},//阶梯3电价                            
{0x00,PDI_CUR_STEP4_FEE},//阶梯4电价                            
{0x00,PDI_CUR_STEP5_FEE},//阶梯5电价
#endif
{0x00,0x04001001},//报警金额1                            
{0x00,0x04001002},//报警金额2                            
{0x00,0x00900201},//透支金额                             
{0x00,0x04000b01},//结算日         
};
#else //多功能表-非费控
//自动循环显示数据项
CONST S_Disp_Item Def_04040101_13[] =
{
{0x00,0x04000101},//显示当前日期              
{0x00,0x04000102},//显示当前时间              
//{0x00,0x00900200},//当前剩余金额              
{0x00,0x00000000},//显示当前组合有功总电量    
{0x00,0x00010000},//显示当前正向有功总电量    
{0x00,0x00010100},//显示当前正向有功尖电量    
{0x00,0x00010200},//显示当前正向有功峰电量    
{0x00,0x00010300},//显示当前正向有功平电量    
{0x00,0x00010400},//显示当前正向有功谷电量    
{0x00,0x01010000},//显示当前正向有功总最大需量
{0x00,0x00030000},//显示当前组合无功1总电量   
{0x00,0x00040000},//显示当前组合无功2总电量   
{0x00,0x00050000},//显示当前Ⅰ象限无功电量    
{0x00,0x00060000},//显示当前Ⅱ象限无功电量    
{0x00,0x00070000},//显示当前Ⅲ象限无功电量    
{0x00,0x00080000},//显示当前Ⅳ象限无功电量    
{0x00,0x00020000},//显示当前反向有功总电量    
{0x00,0x00020100},//显示当前反向有功尖电量    
{0x00,0x00020200},//显示当前反向有功峰电量    
{0x00,0x00020300},//显示当前反向有功平电量    
{0x00,0x00020400} //显示当前反向有功谷电量    

};


//按键循环显示数据项
CONST S_Disp_Item Def_04040201_20[] =
{
{0x00,0x04000101},//当前日期                             
{0x00,0x04000102},//当前时间                             
//{0x00,0x00900200},//当前剩余金额                         
{0x00,0x00000000},//当前组合有功总电量                   
{0x00,0x00010000},//当前正向有功总电量                   
{0x00,0x00010100},//当前正向有功尖电量                   
{0x00,0x00010200},//当前正向有功峰电量                   
{0x00,0x00010300},//当前正向有功平电量                   
{0x00,0x00010400},//当前正向有功谷电量                   
{0x00,0x01010000},//当前正向有功总最大需量               
{0x01,0x01010000},//当前正向有功总最大需量发生日期       
{0x02,0x01010000},//当前正向有功总最大需量发生时间       
{0x00,0x00020000},//当前反向有功总电量                   
{0x00,0x00020100},//当前反向有功尖电量                   
{0x00,0x00020200},//当前反向有功峰电量                   
{0x00,0x00020300},//当前反向有功平电量                   
{0x00,0x00020400},//当前反向有功谷电量                   
{0x00,0x01020000},//当前反向有功总最大需量               
{0x01,0x01020000},//当前反向有功总最大需量发生日期       
{0x02,0x01020000},//当前反向有功总最大需量发生时间       
{0x00,0x00030000},//当前组合无功总电量1                  
{0x00,0x00040000},//当前组合无功总电量2                  
{0x00,0x00050000},//当前Ⅰ象限无功总电量                 
{0x00,0x00060000},//当前Ⅱ象限无功总电量                 
{0x00,0x00070000},//当前Ⅲ象限无功总电量                 
{0x00,0x00080000},//当前Ⅳ象限无功总电量                 
{0x00,0x00010001},//上1月正向有功总电量                  
{0x00,0x00010101},//上1月正向有功尖电量                  
{0x00,0x00010201},//上1月正向有功峰电量                  
{0x00,0x00010301},//上1月正向有功平电量                  
{0x00,0x00010401},//上1月正向有功谷电量                  
{0x00,0x01010001},//上1月正向有功总最大需量              
{0x01,0x01010001},//上1月正向有功总最大需量发生日期      
{0x02,0x01010001},//上1月正向有功总最大需量发生时间      
{0x00,0x00020001},//上1月反向有功总电量                  
{0x00,0x00020101},//上1月反向有功尖电量                  
{0x00,0x00020201},//上1月反向有功峰电量                  
{0x00,0x00020301},//上1月反向有功平电量                  
{0x00,0x00020401},//上1月反向有功谷电量                  
{0x00,0x01020001},//上1月反向有功总最大需量              
{0x01,0x01020001},//上1月反向有功总最大需量发生日期      
{0x02,0x01020001},//上1月反向有功总最大需量发生时间      
{0x00,0x00050001},//上1月Ⅰ象限无功总电量                
{0x00,0x00060001},//上1月Ⅱ象限无功总电量                
{0x00,0x00070001},//上1月Ⅲ象限无功总电量                
{0x00,0x00080001},//上1月Ⅳ象限无功总电量                
{0x01,0x04000401},//电能表通信地址（表号）低8位          
{0x00,0x04000401},//电能表通信地址（表号）高4位          
{0x00,0x04000703},//通信波特率（RS485-1）                
{0x00,0x04000409},//有功脉冲常数                         
{0x00,0x0400040a},//无功脉冲常数                         
{0x00,0x0280000a},//时钟电池使用时间                     
{0x01,0x03300001},//最近一次编程日期                     
{0x00,0x03300001},//最近一次编程时间                     
{0x00,0x10000001},//总失压次数                           
{0x00,0x10000002},//总失压累计时间                       
{0x01,0x10000101},//最近一次失压起始日期                 
{0x00,0x10000101},//最近一次失压起始时间                 
{0x01,0x10000201},//最近一次失压结束日期                 
{0x00,0x10000201},//最近一次失压结束时间                 
{0x00,0x10010201},//最近一次A相失压起始时刻正向有功总电量
{0x00,0x10012601},//最近一次A相失压结束时刻正向有功总电量
{0x00,0x10010301},//最近一次A相失压起始时刻反向有功总电量
{0x00,0x10012701},//最近一次A相失压结束时刻反向有功总电量
{0x00,0x10020201},//最近一次B相失压起始时刻正向有功总电量
{0x00,0x10022601},//最近一次B相失压结束时刻正向有功总电量
{0x00,0x10020301},//最近一次B相失压起始时刻反向有功总电量
{0x00,0x10022701},//最近一次B相失压结束时刻反向有功总电量
{0x00,0x10030201},//最近一次C相失压起始时刻正向有功总电量
{0x00,0x10032601},//最近一次C相失压结束时刻正向有功总电量
{0x00,0x10030301},//最近一次C相失压起始时刻反向有功总电量
{0x00,0x10032701},//最近一次C相失压结束时刻反向有功总电量
{0x00,0x02010100},//A相电压                              
{0x00,0x02010200},//B相电压                              
{0x00,0x02010300},//C相电压                              
{0x00,0x02020100},//A相电流                              
{0x00,0x02020200},//B相电流                              
{0x00,0x02020300},//C相电流                              
{0x00,0x02030000},//瞬时总有功功率                       
{0x00,0x02030100},//瞬时A相有功功率                      
{0x00,0x02030200},//瞬时B相有功功率                      
{0x00,0x02030300},//瞬时C相有功功率                      
{0x00,0x02060000},//瞬时总功率因数                       
{0x00,0x02060100},//瞬时A相功率因数                      
{0x00,0x02060200},//瞬时B相功率因数                      
{0x00,0x02060300},//瞬时C相功率因数                      
//{0x00,PDI_CUR_RATE1_FEE},//当前尖费率电价                       
//{0x00,PDI_CUR_RATE2_FEE},//当前峰费率电价                       
//{0x00,PDI_CUR_RATE3_FEE},//当前平费率电价                       
//{0x00,PDI_CUR_RATE4_FEE},//当前谷费率电价                       
//{0x00,PDI_CUR_STEP1_ENG},//阶梯1电量                            
//{0x00,PDI_CUR_STEP2_ENG},//阶梯2电量                            
//{0x00,PDI_CUR_STEP3_ENG},//阶梯3电量                            
//{0x00,PDI_CUR_STEP4_ENG},//阶梯4电量                            
//{0x00,PDI_CUR_STEP1_FEE},//阶梯1电价                            
//{0x00,PDI_CUR_STEP2_FEE},//阶梯2电价                            
//{0x00,PDI_CUR_STEP3_FEE},//阶梯3电价                            
//{0x00,PDI_CUR_STEP4_FEE},//阶梯4电价                            
//{0x00,PDI_CUR_STEP1_FEE},//阶梯5电价                            
//{0x00,0x04001001},//报警金额1                            
//{0x00,0x04001002},//报警金额2                            
//{0x00,0x00900201},//透支金额                             
{0x00,0x04000b01},//结算日         
};
#endif



#pragma pack()

#define HEX2BCD(X) ((X)/10*16 + (X)%10)
//显示相关参数
CONST INT8U Def_04000301_5[] =
{
  HEX2BCD(S_NUM(Def_04040101_13)),//0x06, //自动循环显示屏数
  0x05, //每屏显示时间
  0x02, //显示电能小数位
  0x04, //显示功率小数位
  HEX2BCD(S_NUM(Def_04040201_20))//0x22, //按键循环显示屏数

};

//定时冻结时间
CONST INT8U Def_Period_Freeze_Time[] =
{
  0x00, 0x00, 0x99, 0x99
};

//00秒脉冲
//01需量周期
//02时段切换 
CONST INT8U Def_SDI_OUTPUT_MODE[] =
{
  0x01  
};

//远程控制继电器状态
CONST S_Remote_Ctrl_Switch Def_SDI_REMOTE_RELAY_STATUS =
{
  .Switch_Flag = SWITCH_ON, //合闸标志
  //.Switch_Time = {0},
  .Alarm_Flag = ALARM_OFF, //报警解除
  //.Alarm_Time = {0},  
  .Maintain_Flag = MAINTAIN_OFF, //保电解除
  //.Maintain_Time = {0},
  .Switch_Status = SWITCH_ON, //合闸
  .CS = {0}
};

//控制状态标志
CONST S_Ctrl_Status_Flag Def_SDI_CTRL_STATUS_FLAG =
{
  .Head = CHK_BYTE,
  .Card_Switch_On_Flag = 0,
  .Buy_Money_Switch_Limit_Flag = 0,
  .Hand_Switch_On_Flag = 0,
 .Tail = CHK_BYTE
};

//预付费负荷控制继电器状态
CONST S_Pepaid_Power_Ctrl_Switch Def_SDI_PREPAID_POWER_CTRL_RELAY_STATUS =
{
  .Switch_Flag = SWITCH_ON,
  .On_Delay = 0,
  .Off_Delay = 0,
  .Off_Counts = 0,
  .CS = {0}
};

//第一套费率参数
CONST INT32U Def_04050101_8[] = 
{
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,
  0x00010000,  
};

//第一套阶梯电量
CONST INT32U Def_04060001_3[] = 
{
  0x00100000,
  0x00200000,
  0x00300000,
  0x00400000,
  0x00500000,
};

//第一套阶梯电价
CONST INT32U Def_04060101_4[]=
{
  0x00010000,
  0x00015000,
  0x00020000,
  0x00025000,
  0x00030000,
  0x00035000,
  0x00040000
};

//失压事件电压触发上限、电压恢复下限
CONST INT8U Def_04090101_2[]=
{
  BYTE_0(HEX2BCD_4B(UB*78/10)),BYTE_1(HEX2BCD_4B(UB*78/10)),//0x16,0x17, //171.6
  BYTE_0(HEX2BCD_4B(UB*85/10)),BYTE_1(HEX2BCD_4B(UB*85/10)),//0x70,0x18  //187.0
};

//失压事件电流触发下限
CONST INT8U Def_04090103[]=
{
  BYTE_0(HEX2BCD_4B(IB*5/10)), BYTE_1(HEX2BCD_4B(IB*5/10)),BYTE_2(HEX2BCD_4B(IB*5/10))//0x75,0x00,0x00 0.5%IB
};

//失压时间判定延时时间
CONST INT8U Def_04090104[]=
{
  0x60
};

//欠压事件电压触发上限
CONST INT8U Def_04090201[]=
{
  BYTE_0(HEX2BCD_4B(UB*90/10)),BYTE_1(HEX2BCD_4B(UB*90/10))//0x80,0x19 //198.0V
};

//欠压事件判定延时时间
CONST INT8U Def_04090202[]=
{
  0x30 
};

//过压事件电压触发下限
CONST INT8U Def_04090301[]=
{
  BYTE_0(HEX2BCD_4B(UB*120/10)),BYTE_1(HEX2BCD_4B(UB*120/10)),//0x40,0x26 //264.0V，120%
};

//过压事件判定延时时间 
CONST INT8U Def_04090302[]=
{
  0x30
};

//断相事件电压触发上限 
CONST INT8U Def_04090401[]=
{
  BYTE_0(HEX2BCD_4B(UB*60/10)), BYTE_1(HEX2BCD_4B(UB*60/10)),//132.0V
};

//断相事件电流触发上限
CONST INT8U Def_04090402[]=
{
  BYTE_0(HEX2BCD_4B(IB*5/10)), BYTE_1(HEX2BCD_4B(IB*5/10)),BYTE_2(HEX2BCD_4B(IB*5/10))//0x75,0x00,0x00 //0.0075A，额定电流的千分之5
};

//断相事件判定延时时间
CONST INT8U Def_04090403[]=
{
  0x60
};

//电压不平衡判定限值
CONST INT8U Def_04090501[]=
{
  0x00,0x30 //30%
};
//电压不平衡判定延时时间
CONST INT8U Def_04090502[]=
{
  0x30 //30s
};

//电流不平衡判定限值
CONST INT8U Def_04090601[]=
{
  0x00,0x30 //30%
};
//电流不平衡判定延时时间
CONST INT8U Def_04090602[]=
{
  0x30 //30s
};

//失流事件电压触发下限
CONST INT8U Def_04090701[]=
{
  BYTE_0(HEX2BCD_4B(UB*60/10)),BYTE_1(HEX2BCD_4B(UB*60/10))//0x20,0x13 //132V,UB*60%
};

//失流事件电流触发上、下限
CONST INT8U Def_04090702_2[]=
{
  BYTE_0(HEX2BCD_4B(IB*5/10)), BYTE_1(HEX2BCD_4B(IB*5/10)),BYTE_2(HEX2BCD_4B(IB*5/10)),//0x75,0x00,0x00 //0.0075A，额定电流的千分之5
  BYTE_0(HEX2BCD_4B(IB*5)), BYTE_1(HEX2BCD_4B(IB*5)),BYTE_2(HEX2BCD_4B(IB*5))//0x50,0x07,0x00  //0.0750A
  
};

//失流不平衡判定延时时间
CONST INT8U Def_04090704[]=
{
  0x60
};

//过流事件电流触发下限
CONST INT8U Def_04090801[]=
{
  BYTE_0(HEX2BCD_4B(IB*4/10)), BYTE_1(HEX2BCD_4B(IB*4/10))//0x60,0x00，6.0A,%400额定电流
};

//过流事件判定延时时间
CONST INT8U Def_04090802[]=
{
  0x30
};

//断流事件电压触发下限 
CONST INT8U Def_04090901[]=
{
  BYTE_0(HEX2BCD_4B(UB*90/10)),BYTE_1(HEX2BCD_4B(UB*90/10))//0x80,0x19 //198.0V，90%UB
};

//断流事件电流触发上限
CONST INT8U Def_04090902[]=
{
  BYTE_0(HEX2BCD_4B(IB/10)), BYTE_1(HEX2BCD_4B(IB/10)), BYTE_2(HEX2BCD_4B(IB/10))//0x15,0x00,0x00 //0.0015A,0.1%IB
};

//断流事件判定延时时间
CONST INT8U Def_04090903[]=
{
  0x30
};

//潮流反向事件有功功率触发下限
CONST INT8U Def_04090A01[]=
{
  BYTE_0(HEX2BCD_4B(PB/100)), BYTE_1(HEX2BCD_4B(PB/100)),BYTE_2(HEX2BCD_4B(PB/100)),//0x30,0x03,0x00 //0.033kw,10%PB
};

//潮流反向事件判定延时时间
CONST INT8U Def_04090A02[]=
{
  0x60
};

//过载事件有功功率触发下限
CONST INT8U Def_04090B01[]=
{
  BYTE_0(HEX2BCD_4B(PMAX*12/100)), BYTE_1(HEX2BCD_4B(PMAX*12/100)),BYTE_2(HEX2BCD_4B(PMAX*12/100))//0x40,0x58,0x01 //1.584kw,120%PMAX
};

//过载事件判定延时时间
CONST INT8U Def_04090B02[]=
{
  0x30
};

//电压考核上下限
CONST INT8U Def_04090C01_2[]=
{
  BYTE_0(HEX2BCD_4B(UB*12)),BYTE_1(HEX2BCD_4B(UB*12)),//0x40,0x26, //264V
  BYTE_0(HEX2BCD_4B(UB*9)),BYTE_1(HEX2BCD_4B(UB*9))//0x80,0x19 //198V
};

//有、无功需量超下限
CONST INT8U Def_04090D01_2[]=
{
  BYTE_0(HEX2BCD_4B(PMAX*30/100)), BYTE_1(HEX2BCD_4B(PMAX*30/100)),BYTE_2(HEX2BCD_4B(PMAX*30/100)),//0x00,0x96,0x03, //3.96kw
  BYTE_0(HEX2BCD_4B(PMAX*30/100)), BYTE_1(HEX2BCD_4B(PMAX*30/100)),BYTE_2(HEX2BCD_4B(PMAX*30/100))//0x00,0x90,0x03 //3.90kw
};

//有、无功需量超限判定延迟时间
CONST INT8U Def_04090D03[]=
{
  0x30
};

//总功率因素超下限阀值
CONST INT8U Def_04090E01[]=
{
  0x00,0x05 //0.5
};

//总功率因素超下限判定延时时间
CONST INT8U Def_04090E02[]=
{
  0x30
};


//电流严重不平衡限值
CONST INT8U Def_04090F01[]=
{
  0x00,0x40 //%40
};

//电流严重不平衡判定延时时间
CONST INT8U Def_04090F02[]=
{
  0x30
};

//中间数字表示数据项个数
CONST S_Def_Para_Info Def_Para[] =
{
  //{SDI_PROG_EN_TIME, 1, Zero},//         0x0E000206 //编程有效时间
  {SDI_OUTPUT_MODE,1,Def_SDI_OUTPUT_MODE},          //0x0E000207 //三合一输出模式字
  {SDI_PERIOD_FREEZE_TIME,1,Def_Period_Freeze_Time},//周期冻结时间点
  {_SDI_LAST_SETTLE_ENERGY_DI,1,(INT8U*) Def_SDI_LAST_SETTLE_ENERGY_DI}, 
  {_SDI_LAST_SETTLE_DEMAND_DI,1,(INT8U*) Def_SDI_LAST_SETTLE_DEMAND_DI}, 
  {_SDI_LAST_SETTLE_VOLSTAT_DI,1,(INT8U*) Def_SDI_LAST_SETTLE_VOLSTAT_DI}, 
  {_SDI_CUR_SCHEME,1,(INT8U *) &Def_SDI_CUR_SCHEME},
  {_SDI_REMOTE_RELAY_STATUS,1,(INT8U *) &Def_SDI_REMOTE_RELAY_STATUS}, //远程控制继电器状态
  {_SDI_PREPAID_POWER_CTRL_RELAY_STATUS,1,(INT8U *)&Def_SDI_PREPAID_POWER_CTRL_RELAY_STATUS},//预付费负荷控制继电器状态
  {_SDI_CTRL_STATUS_FLAG, 1, (INT8U *)&Def_SDI_CTRL_STATUS_FLAG}, //控制状态标志
  {SDI_BAT_RUN_TIME,1,Zero},//内部电池工作时间(时钟电池)
  {SDI_DEMAND_PERIOD,2,Def_04000103_2},//需量周期和滑差时间
  //默认校表参数
  {_SDI_ADJ_METER_PUL_VOL_CUR_SPEC,1,Def_SDI_ADJ_METER_PUL_VOL_CUR_SPEC},//脉冲、电压、电流规格
  {_SDI_ADJ_METER_PARA_STATUS,1,Def_SDI_ADJ_METER_PARA_STATUS},//校表参数状态设置
  {_SDI_ADJ_METER_A_POW,12,Def_SDI_ADJ_METER_A_POW},//功率、相位、电压、电流设置参数一共有12项目
  
  { _SDI_PREPAID_RUN_STATUS, 1, (INT8U *)Zero},// (0x0300|EXT_PARA_DATA)//运行状态 数据长度为1
  { _SDI_DISCRETE_INFO, 1, (INT8U *)Zero}, //离散因子 数据长度为8
  { _SDI_PREPAID_PARA_CARD_VER, 1, (INT8U *)Zero},// (0x0302|EXT_PARA_DATA)//现场参数设置卡版本号 数据长度为4
  { _SDI_PREPAID_PSW_KIND, 1, (INT8U *)Zero}, // (0x0303|EXT_PARA_DATA)//密钥类型数据长度为1
  { _SDI_INVALID_CARD_COUNTS, 1, (INT8U *)Zero}, //非法卡插入次数
  { _SDI_INVALID_COUNTS_AllOW, 1, (INT8U *)Zero}, //非法卡插入次数
  { _SDI_FAR_AUTH_DAY_FOLLOW, 1, (INT8U *)Zero},//身份认证跟随日
  { _SDI_SINGLE_OR_COMPLEX_USER_KIND, 1, (INT8U *)Zero}, //用户类型
  { _SDI_FAR_PASSWORD_STATE, 1, (INT8U *)Zero}, //远程密钥类型
  
  {SDI_RELAY_OFF_DELAY, 1, Def_SDI_RELAY_OFF_DELAY}, //跳闸延时
  {SDI_CUTOMER_ID, 1, (INT8U *)Zero}, //客户编号
  {0x04090101, 2, Def_04090101_2}, //失压判定电压触发上限、恢复下限
  {0x04090103, 1, Def_04090103}, //失压事件电流触发下限
  {0x04090104, 1, Def_04090104}, //失压事件电压触发上限
  
  {0x04090201, 1, Def_04090201}, //欠压判定电压触发上限
  {0x04090202, 1, Def_04090202}, //欠压事件判定延迟时间

  {0x04090301, 1, Def_04090301}, //过压事件电压触发下限
  {0x04090302, 1, Def_04090302}, //过压事件判定延迟时间 

  {0x04090401, 1, Def_04090401}, //断相事件电压触发上限
  {0x04090402, 1, Def_04090402}, //断相事件电流触发上限 
  {0x04090403, 1, Def_04090403}, //断相事件判定延迟时间 
 
  {0x04090501, 1, Def_04090501}, //电压不平衡限值
  {0x04090502, 1, Def_04090502}, //电压不平衡判定延迟时间 

  {0x04090601, 1, Def_04090601}, //电流不平衡限值
  {0x04090602, 1, Def_04090602}, //电流不平衡判定延迟时间 
 
  {0x04090701, 1, Def_04090701}, //失流事件电压触发下限
  {0x04090702, 2, Def_04090702_2}, //失流事件电流触发上、下限
  {0x04090704, 1, Def_04090704}, //失流事件判定延迟时间

  {0x04090801, 1, Def_04090801}, //过流电流触发下限
  {0x04090802, 1, Def_04090802}, //过流判定延迟时间 
  
  {0x04090901, 1, Def_04090901}, //断流事件电压触发下限     198   90％
  {0x04090902, 1, Def_04090902}, //断流事件电流触发上限      0.5
  {0x04090903, 1, Def_04090903}, //断流事件判定延时时间      30
 
  {0x04090A01, 1, Def_04090A01},//潮流反向事件有功功率触发下限   0.66
  {0x04090A02, 1, Def_04090A02},//潮流反向事件判定延时时间      30
 
  {0x04090B01, 1, Def_04090B01},//过载事件有功功率触发下限      3.96
  {0x04090B02, 1, Def_04090B02},//过载事件判定延时时间         30

  {0x04090C01, 2, Def_04090C01_2},//电压考核上、下限                 264  120％

  {0x04090D01, 2, Def_04090D01_2},//有功需量超限事件需量触发下限
  {0x04090D03, 1, Def_04090D03}, //需量超限事件判定延时时间 
  
  {0x04090E01, 1, Def_04090E01},//总功率因数超下限阀值        0.500
  {0x04090E02, 1, Def_04090E02}, //总功率因数超下限判定延时时间    30
  
  {0x04090F01, 1, Def_04090F01},//电流严重不平衡限值             40
  {0x04090F02, 1, Def_04090F02},//电流严重不平衡触发延时时间     30
  
  {0x10000101, 1, Zero}, //最近一次失压发生和结束时刻
  {0x10000201, 1, Zero},
  
  {SDI_MODEWORD_1,5,Def_SDI_MODEWORD_1_5},//5个模式字
  
  //{0x0E000101, 2, Def_0E000101_2},
  //{0x0E000103, 1, Def_0E000103},
  //{0x0E000104, 1, Def_0E000104},
  //{0x0E000105, 2, Def_0E000105_2},
  //{0x0E000107, 1, Def_0E000107},
  {0x0E000108, 1, Def_0E000108},
  {SDI_ADJ_TIME_COUNTS,1,Def_SDI_ADJ_TIME_COUNTS}, //广播校时次数
  //{0x0E000109, 1, Def_0E000109},
  //{0x0E00010A, 1, Def_0E00010A},
  //{0x0E00010B, 1, Def_0E00010B},
  //{0x0E00010C, 3, Def_0E00010C_3},
  //{0x0E00010F, 1, Def_0E00010F},
  //{0x0E000110, 1, Def_0E000110},
  //{0x0E000111, 1, Def_0E000111},
  //{0x0E000112, 1, Def_0E000112},
  //{0x0E000113, 1, Def_0E000113},
  //{0x0E000114, 1, Def_0E000114},
  
  {SDI_LAST_LOSS_VOL_OCCUR_TIME, 1, Zero}, //0x0EA10000 //最近一次失压发生时刻
  {SDI_LAST_LOSS_VOL_END_TIME, 1, Zero},//0x0EA10001 //最近一次失压结束时刻
  
  {SDI_ADJ_PULSE_WIDTH,1,Def_04000105},//校表脉冲宽度
  {SDI_YEAR_SCHE_CHG_TIME,1,Def_04000106},//两套年时区表切换时间
  {SDI_DATE_SCHE_CHG_TIME,1,Def_04000107},//两套日时段表切换时间
  {SDI_RATE_SCHE_CHG_TIME,1,Def_04000108},//两套费率方案切换时间
  {SDI_STEP_SCHE_CHG_TIME,1,Def_04000109},//两套阶梯方案切换时间
  {SDI_YEAR_PERIOD_NUM,4,Def_04000201_4},//年时区数
  {SDI_HOLIDAY_NUM,1,Def_04000205},//公共假日数
  {SDI_HARMONIC_NUM,1,Def_04000206},//谐波分析次数
  {SDI_PREPAID_STEP_NUM,1,Def_04000207}, //预付费梯度数
  {SDI_AUTO_CYCL_SCREEN_NUM,5,Def_04000301_5},//自动循环显示屏数等显示相关参数
  {SDI_CURR_TRANS_RATIO, 1, Def_04000306}, //电流互感器变比
  {SDI_VOLT_TRANS_RATIO, 1, Def_04000307}, //电压互感器变比
  {SDI_PREPAID_WARN_ENG1, 4, (INT8U CONST *)Def_04000F01_4}, //电量预付费参数
  {SDI_PREPAID_WARN_MONEY1, 5, (INT8U CONST *)Def_04001001_5}, //电费预付费参数
  {SDI_METER_RUN_STATUS, 1, Def_04001101}, //电表运行状态字
  //{SDI_POWER_PULSE, 1, (INT8U CONST *)Def_0400E001}, //功率负荷脉冲数
  //{SDI_MAX_POWER_CALC_TIME, 2, Def_0400E002_2}, //最大负荷计算时间
  //{SDI_POWER_CTRL_RELAY_SWITCH_LIMIT, 1, Def_0400E003}, //过负荷跳闸次数门限
  {SDI_DISP_FEE_DIGS, 1, Def_0400E101}, //显示电费小数位
  {SDI_PREPAID_MODEWORD_1, 3, Def_0400E201_3}, //预付费模式字1-3
  
  {SDI_COMM_ADDR,1,Def_04000401},//通信地址
  {SDI_METER_ID,1,Def_04000402},//表号
  {SDI_ASSET_ID,1,Def_04000403},//资产管理编码
  
  {SDI_RATED_VOL,1,Def_04000404},//   0x04000404 //额定电压
  {SDI_RATED_CUR,1,Def_04000405},//   0x04000405 //额定电流
  {SDI_MAX_CUR,1,Def_04000406},//0x04000406 //最大电流
  {SDI_ACTIVE_ACCU,1,Def_04000407},//  0x04000407 //有功准确等级
  {SDI_REACTIVE_ACCU,1,Def_04000408},//     0x04000408 //无功准确等级
  //{SDI_ACTIVE_CONST,1,Def_04000409_2},// 0x04000409 //电表有功常数
  //{SDI_REACTIVE_CONST,1,Def_0400040A},//     0x0400040A //电表无功常数
  {SDI_METER_TYPE,1,Def_0400040B},//     0x0400040B //电表型号
  {SDI_METER_MADE_TIME,1,Def_0400040C},//    0x0400040C //电表生产日期
  //{SDI_PROTOCOL_VER,1,Def_0400040D},//   0x0400040D //电表协议版本号 
  //软件版本号
  {SDI_HARDWARE_VERSION,1,Def_04800002},//硬件版本号
  
  {SDI_ACTIVE_CONST,2,Def_04000409_2},//有无功脉冲常数
  {SDI_ACTIVE_COMB_WORD,3,Def_04000601_3},//有无功组合特征字
  {SDI_FAR_IRAD_BAUD,5,Def_04000701_5},//各通信口通信状态字
  {SDI_WEEK_REST_DAY,2,Def_04000801_2},//周休日特征字
  {SDI_LOAD_REC_WORD,6,Def_04000901_6},//负荷记录模式字和冻结模式字
  {SDI_LOAD_REC_START_TIME,1,Def_04000A01},//负荷记录起始时间
  {SDI_LOAD_REC1_INTER_TIME,6,Def_04000A02_6},//负荷记录间隔时间
  {SDI_MONTH_SETTLE_DAY1,3,Def_04000B01_3},//每月三个结算日 
  {SDI_PSW0,10,Def_04000C01_10},//10级密码
  {SDI_POS_ACTIVE_UP_LIMIT,2,Def_04000E01_2},//正反向有功功率上限
  {SDI_VOL_UP_LIMIT,2,Def_04000E03_2},//电压上下限
  {SDI_SCHE1_YEAR_TABLE,1,Def_04010000},//第一套年时区表
  {SDI_SCHE1_DATE_TABLE1,1,Def_04010001},//第一套第一日时段表
  {SDI_SCHE1_DATE_TABLE2,1,Def_04010001},//第一套第二日时段表
  {SDI_SCHE1_DATE_TABLE3,1,Def_04010001},//第一套第三日时段表
  {SDI_SCHE1_DATE_TABLE4,1,Def_04010001},//第一套第四日时段表
  {SDI_SCHE1_DATE_TABLE5,1,Def_04010001},//第一套第五日时段表
  {SDI_SCHE1_DATE_TABLE6,1,Def_04010001},//第一套第六日时段表
  {SDI_SCHE1_DATE_TABLE7,1,Def_04010001},//第一套第七日时段表
  {SDI_SCHE1_DATE_TABLE8,1,Def_04010001},//第一套第八日时段表
  {SDI_SCHE2_YEAR_TABLE,1,Def_04010000},//第二套年时区表
  {SDI_SCHE2_DATE_TABLE1,1,Def_04010001},//第二套第一日时段表
  {SDI_SCHE2_DATE_TABLE2,1,Def_04010001},//第二套第二日时段表
  {SDI_SCHE2_DATE_TABLE3,1,Def_04010001},//第二套第三日时段表
  {SDI_SCHE2_DATE_TABLE4,1,Def_04010001},//第二套第四日时段表
  {SDI_SCHE2_DATE_TABLE5,1,Def_04010001},//第二套第五日时段表
  {SDI_SCHE2_DATE_TABLE6,1,Def_04010001},//第二套第六日时段表
  {SDI_SCHE2_DATE_TABLE7,1,Def_04010001},//第二套第七日时段表
  {SDI_SCHE2_DATE_TABLE8,1,Def_04010001},//第二套第八日时段表
  
  {SDI_HOUR_FREEZE_START_TIME, 1, Def_04001001}, //整点冻结起始时间
  {SDI_HOUR_FREEZE_PERIOD, 1, Def_04001002},//整点冻结时间间隔
  {SDI_DATE_FREEZE_TIME, 1, Def_04001003},//日冻结时间
  
  {SDI_HOLIDAY_DATE_TABLE, MAX_YEAR_HOLIDAYS, Def_04030001},//公共节假日
  {SDI_AUTO_CYCL_SREEN_DATA, MAX_AUTO_SCREEN_NUM, (INT8U *)Def_04040101_13},//自动循环显示屏号
  {SDI_KEY_CYCL_SREEN_DATA, MAX_KEY_SCREEN_NUM, (INT8U *)Def_04040201_20},//按键循环显示
  {SDI_RATE_SCHEME0_0, MAX_RATES, (INT8U *)Def_04050101_8},
  {SDI_RATE_SCHEME1_0, MAX_RATES, (INT8U *)Def_04050101_8},
  
  {SDI_STEP_SCHEME0_ENG, PREPAID_MAX_STEP, (INT8U *)Def_04060001_3},//     0x04060001 //第一套阶梯参数电量
  {SDI_STEP_SCHEME0_MONEY, PREPAID_MAX_STEP + 1, (INT8U *)Def_04060101_4},//   0x04060101 //第一套阶梯参数电价
  {SDI_STEP_SCHEME1_ENG, PREPAID_MAX_STEP, (INT8U *)Def_04060001_3},//      0x04060201 //第二套阶梯参数电量
  {SDI_STEP_SCHEME1_MONEY, PREPAID_MAX_STEP + 1, (INT8U *)Def_04060101_4},//   0x04060301 //第二套阶梯参数电价    
  EXTEND_DEF_PARA
};


//写一条默认参数，参数标识为DI
void Write_One_Def_Para(STORA_DI SDI)
{
  INT16U i;
  INT16U Len;

  TRACE();

  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
  {
    Debug_Print("Write Def Para failed! not in factory status!");
    return;
  }

  for(i = 0; i < S_NUM(Def_Para); i++)
  {
    if(SDI >= Def_Para[i].SDI && SDI < Def_Para[i].SDI + Def_Para[i].Num)
    {
      if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
        return;
      Len = Get_Storage_Data_Len(Def_Para[i].SDI);
      Write_Storage_Data(SDI, (void *) (Def_Para[i].pPara + (SDI - Def_Para[i].SDI) * Len), Len);
      return;
    }
  }
}
//设置默认的校表参数,设为全0
void Set_Def_Adj_Para()
{
  STORA_DI SDI;
  INT8U Temp[4];

  TRACE();
  
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
    return;
  
  Main_Dis_Info("SET PArA");  
  
  mem_set(Temp, 0, sizeof(Temp), Temp, sizeof(Temp));
  for(SDI = _SDI_ADJ_METER_A_POW; SDI <= _SDI_ADJ_METER_C_CUR; SDI++)
  {
    Write_Storage_Data(SDI, Temp, 3);
    //Write_One_Def_Para(DI);
  }
}


//设置除校表参数意外的所有参数
//校表参数如果无法读出，也会置成默认参数
void Set_Def_Para_Except_Adj()
{
  INT16U i,j,Len;
  INT8U Temp[10];
  
  Main_Dis_Info("SET PArA");
  for(i=0;i<S_NUM(Def_Para);i++)
  {
    if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
      return;
    
    Len=Get_Storage_Data_Len(Def_Para[i].SDI);
    
    for(j=0;j<Def_Para[i].Num;j++)
    {
      if(Check_Meter_Factory_Status() EQ 0)
        return;  
  
      //如果是校表参数则不置默认
      if(!((Def_Para[i].SDI + j >= _SDI_ADJ_METER_PARA_STATUS && Def_Para[i].SDI + j <= _SDI_ADJ_METER_C_CUR) || \
            Def_Para[i].SDI + j EQ SDI_ACTIVE_CONST || Def_Para[i].SDI + j EQ SDI_REACTIVE_CONST))
        Write_Storage_Data(Def_Para[i].SDI + j,(void *)(Def_Para[i].pPara + j*Len),Len);
      else
      {
        //校表参数，先看能否读出，不能读出则置默认
        if(Read_Storage_Data_Fix_Len(Def_Para[i].SDI + j, 0, Len, Temp, Temp, sizeof(Temp)) EQ 0)
          Write_Storage_Data(Def_Para[i].SDI + j, (void *)(Def_Para[i].pPara + j*Len),Len);      
      }
    }
  }  
}

//读数据项DI的默认参数
INT16U Read_Def_Para(STORA_DI SDI, void* pDst, INT16U Len, void* pDst_Start, INT16U DstLen)
{
  INT16U i;

  TRACE();

  for(i = 0; i < S_NUM(Def_Para); i++)
  {
    if(SDI EQ Def_Para[i].SDI || \
       (SDI > Def_Para[i].SDI && SDI < Def_Para[i].SDI + Def_Para[i].Num))
    {
      mem_cpy(pDst, (INT8U *) Def_Para[i].pPara + (SDI - Def_Para[i].SDI) * Len, Len, pDst_Start, DstLen);
      return Len;
    }
  }
  return 0;
}

//设置所有默认数据
void Set_All_Def_Data()
{
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
    return;

  Read_Settle_Para_From_Rom(); //读取结算时间;下面设置默认参数需要该参数
  
  DISP_CLR_DATA_INFO;
  
  Set_Def_Energy_Data();//设置默认的电量数据
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
  {
    return;
  }
  Set_Def_Demand_Data();//设置默认的需量数据
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
  {
    return;
  }
  Set_Def_VolStat_Data();//设置默认的电压统计数据
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
  {
    return;
  }
  Set_Def_Load_Data_Index();//设置默认的负荷曲线索引

  //Set_Def_Freeze_Data();//设置默认的冻结数据
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
  {
    return;
  }
  Set_Def_Event_Separate_Data();//设置默认的事件数据 
  Set_Def_Event_Cumu_Data();
    
  Clr_RTC_BatTime(); //清除电池工作时间
}

//写默认参数到存储器中,该函数必须在工厂状态下才能执行
void Write_Def_Para()
{
  //INT8U Temp[10];
  //INT16U Len;
  
  TRACE();

  //判断是否需要重写校表参数,能够读出C相电流参数设置，说明已经置过默认参数了，就不置了
  /*
  Len = Get_Storage_Data_Len(_SDI_ADJ_METER_C_CUR);
  if(Read_Storage_Data_Fix_Len(_SDI_ADJ_METER_C_CUR, 0, Len, Temp, Temp, sizeof(Temp)) EQ 0) //读不出来校表参数？？重写之
  {
    Debug_Print("Write Def Adj Para");
    Set_Def_Adj_Para(); 
  }
  */
  Turn_Light_On(); //打开背光
  Set_Def_Para_Except_Adj();  
  /*
  for(i = 0; i < S_NUM(Def_Para); i++)
  {
    if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
      return;

    Len = Get_Storage_Data_Len(Def_Para[i].SDI);

    for(j = 0; j < Def_Para[i].Num; j++)
    {
      if(Check_Meter_Factory_Status() EQ 0)
        return;   
      //if(!(Def_Para[i].SDI+j>=0xCEE0 && Def_Para[i].SDI+j<=0xCEED))//test
      Write_Storage_Data(Def_Para[i].SDI + j, (void *) (Def_Para[i].pPara + j * Len), Len);
    }
  }
  */
  Set_All_Def_Data();
  Turn_Light_Off(); //关闭背光
  Debug_Print("--------------Set Def Para End!------------");
}

//检查某个参数项是否有默认参数,有则返回1，否则返回0
INT8U Check_Def_Para(STORA_DI SDI)
{
  INT16U i;

  TRACE();

  for(i = 0; i < S_NUM(Def_Para); i++)
  {
    if(SDI >= Def_Para[i].SDI && SDI < Def_Para[i].SDI + Def_Para[i].Num)
    {
      return 1;
    }
  }  
  return 0;
}

//计算默认参数的校验和，该校验和只取每项的SDI和NUM
//因此修改默认参数的内容不会导致CS变化，增加或者减少默认参数则会导致CS变化
INT32U Get_Def_Para_Info_CS()
{
  INT16U i, Len;
  INT32U CS;
   
  CS = 0;
  for(i = 0; i < S_NUM(Def_Para); i ++)
  {
    CS += Def_Para[i].SDI + Def_Para[i].Num;
    Len = Get_Storage_Data_Len(Def_Para[i].SDI); 
    CS += Sum_4Bytes((INT8U *)Def_Para[i].pPara, Len * Def_Para[i].Num);
  }
  //OS_Set_Sum((INT8U *)Def_Para, sizeof(Def_Para), &CS, sizeof(CS), &CS, sizeof(CS)); 
  return CS;
}

//检查是否需要设置默认参数
void Check_Boot_On_Flag()
{
  INT32U Boot_Flag;
  INT32U Chk_Flag;
  INT8U i, Set_Def_Para_Flag = 0;
  
  TRACE();

  //检查存储系统映射是否发生修改，如果发生了修改，则需要在工厂状态下重置默认参数!!!
  Chk_Flag = Get_Storage_Info_CS(); //获取整个存储系统的校验信息，如果发生修改则整个校验信息会发生改变
  
  if(Read_Storage_Data(_SDI_BOOT_FLAG, &Boot_Flag, &Boot_Flag, sizeof(Boot_Flag)) != sizeof(Boot_Flag) || \
   Chk_Flag != Boot_Flag)
  {
    Debug_Print("Sys Storage Map Modified or first time boot!!! Flag0 = %lx, Flag1 = %lx", Chk_Flag, Boot_Flag);
    //没有设置默认参数则显示No Para
    if(Check_Meter_Factory_Status() EQ 0)//非工厂状态下,在工厂状态下面会直接设参数
    {
      for(i = 0; i < 10; i ++)
      {
        Clear_All_Dog();
        Beep_For_Para();
        Main_Dis_Info("NO PArA");
        OS_TimeDly_Ms(300);
      }
    }
    
    Set_Def_Para_Flag = 1; //需要重置默认参数
  }
        
  if(Check_Meter_Factory_Status() EQ 1)//只有在工厂状态才能设置默认参数
  {
    if(Check_Sys_Status() EQ SYS_NORMAL)//系统电源正常的情况下才进行数据冻结和需量处理
    {
      //Check_Sys_Storage();//存储器自检
      
      if(Set_Def_Para_Flag EQ 1)
      {
        Read_Ext_RTC_Status();//第一次上电读取一下外部时钟！震荡器停止状态位清除,避免报警

        Write_Def_Para();
        Boot_Flag = Chk_Flag;
        Write_Storage_Data(_SDI_BOOT_FLAG, &Boot_Flag, sizeof(Boot_Flag));
        
        Init_All_Channel();//重新初始化各通道
      }
    }
  }
}

#undef DEF_PARA_C
