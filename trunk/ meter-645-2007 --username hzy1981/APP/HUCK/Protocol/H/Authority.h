#ifndef AUTHORITY_H
#define AUTHORITY_H

#undef EXT
#ifdef AUTHORITY_C
#define EXT 
#else
#define EXT extern 
#endif

#define MAX_AUTHU_ERR_COUNTS 3   //最大密码错误次数
#define AUTHU_ERR_LOCK_MINS 1440 //密码错误锁定时间
#define SET_EN_MINS    0       //密码正确使能写时间

#define C_REMOTE_AUTH 0x03 //远程认证
#define C_ADJUST_TIME      0x08//001000//广播校时
#define C_READ_DATA    0x11//0lO001//读数据
#define C_READ_FOLLOW_DATA 0x12//10010//读后续数据
#define C_READ_ADDR    0x13//100l1//读通信地址
#define C_SET_DATA     0x14//10100//写数据
#define C_SET_ADDR     0x15//10101//写通信地址
#define C_FREEZE_DATA      0x16//10110//冻结命令
#define C_SET_COM_BAUD     0x17//10111//更改通信速率
#define C_SET_PSW      0x18//11000//修改密码
#define C_CLR_DEMAND   0x19//11001//最大需量清零
#define C_CLR_ALL      0x1A//11010//电表清零
#define C_CLR_EVENT    0x1B//110ll//事件清零
#define C_CTRL         0x1C //控制命令
#define C_PORT         0x1D //多功能端子输出

//数据的密码标志
#define PSW_NULL  0xFF//没有密码类型,或者只读
#define PSW_FACTORY 0//超级表内跳线跳上才能设置的参数
#define PSW_0 1  //0级密码
#define PSW_1 2  //1级密码
#define PSW_2 3  //2级密码
#define PSW_3 4  //3级密码，协议中暂未用
#define PSW_4 5
#define PSW_5 6
#define PSW_6 7
#define PSW_7 8
#define PSW_8 9
#define PSW_9 10
#define PSW_10 11


//根据密码重要级别不一样而进行的数据分类
#define PSW_NULL_FLAG 0xFF

#define PSW_FAC_PARA  0   //工厂参数
#define PSW_RD_ONLY   1   //只读参数，没有写权限
#define PSW_SET_PSW0  2   //0级密码权限
#define PSW_SET_PSW1  3   //1级密码权限
#define PSW_SET_PSW2  4   //2级密码权限
#define PSW_SET_PSW3  5   //3级密码权限
#define PSW_SET_PSW4  6   //4级密码权限
#define PSW_SET_PSW5  7   //5级密码权限
#define PSW_SET_PSW6  8   //6级密码权限
#define PSW_SET_PSW7  9   //7级密码权限
#define PSW_SET_PSW8  10   //8级密码权限
#define PSW_SET_PSW9  11   //9级密码权限

#define PSW_ADJ_TIME  12   //广播校时
#define PSW_SET_DATE  13   //设置日期
#define PSW_SET_TIME  14   //设置时间
#define PSW_CLR_ALL   15   //数据总清,就是电表清0
#define PSW_CLR_DATA  16   //清需量、过程、电压合格率
#define PSW_SET_ENSTART 17   //设置底度数
#define PSW_SET_PARA    18   //设置普通参数(其他参数)

//用户权限标志字
typedef struct
{
    INT8U Head;
    INT32U Flag; 
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_User_Authority_Flag;

//用户权限控制字
typedef struct
{
    INT16U PSW[3];
    INT8U CS[CS_BYTES];//校验和  
}S_User_Authority_Ctrl;//用户权限控制字

//定义密码Flag到在用户权限控制字中的位置的映射表

typedef struct 
{
	INT8U PSW_Flag;  //数据的密码标志
	INT8U PSW_Level; //数据的密码等级
}S_PSW_Map;

//定义密码权限状态
typedef struct
{
    INT8U Head;
    INT8U PSW[10][3];//当前的10级密码，每级密码3个字节
    INT8U CS[CS_BYTES];//校验和
    INT8U Tail;
}S_PSW_Status;

typedef struct
{
  INT8U Set_En_Mins;
  INT8U CS[CS_BYTES];  
}S_Module_Set_Meter_Status;

EXT volatile S_User_Authority_Ctrl User_Authority_Ctrl;//用户权限控制字
EXT volatile S_PSW_Status Cur_PSW;
EXT volatile S_Module_Set_Meter_Status Module_Set_Meter_Status;
EXT volatile S_User_Authority_Flag User_Authority_Flag;

EXT INT8U Get_PSW_Flag_Map_Level(INT8U PSW_Flag);
EXT INT8U Check_Debug_En();
EXT INT8U Check_Set_ADDR_Key();
EXT INT8U Check_Clear_Data_Authority();
EXT INT8U Check_Meter_Factory_Status();
EXT INT8U Check_Meter_Prog_Status();
EXT INT8U Get_User_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen);
EXT INT8U Get_P_Data_Info_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen);
EXT void Clear_PSW_Err_Info();
EXT INT8U Check_PSW_Lock();
EXT void PSW_Lock_Proc();
EXT void PSW_Timer_Proc();
EXT INT8U Check_User_Authurity(INT8U User_PSW, INT8U Data_PSW);
EXT void Set_Authority_Flag();
EXT void Clear_Authority_Flag();
EXT INT8U Check_Data_Type(PROTO_DI PDI);
#endif
