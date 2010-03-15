///预付费参数 ///
/// RAM ///
#ifndef PAY_DEF_H_
#define PAY_DEF_H_

#undef EXT
#ifdef ALL_CARD_OPERATION_C_
#define EXT   
#else
#define EXT extern   
#endif


//上电时从e方取的数据，下电后需要保存到 e方中取的 数据， ，具体见说明
typedef struct {
    INT8U	UserID[ 6 ];                          //用户编号 "// ，如果是运行态就从e方中取，如果为未开户态，取不取都无所谓
    INT8U	Cpucard_Number_old_BackUpInEerom[8];//离散因子，对表第一次上电值不作要求，当为开户卡，或补卡时修改，从e方取，无初始值
    INT8U  PassWord_Kind;                 //密钥类型"*/ //上电的时候要得到是 正式密钥状态，还是公开密钥状态
    INT32U Para_Card_Version;           //"现场参数设置卡版本号,上电初始化要请零"
    //当开户卡插入时修改
    INT8U Meter_Run_State;  //电表运行状态，00厂内/01安装/02运行 "表第一次上电值为0，被存在e方中，上电时从e方取，当是补卡或开户卡时修改
    INT8U   BcdMeterID[6];//表号，对表第一次上电值不作要求，被表号设置卡修改 和开户卡修改
    
    //INT32U Remain_Money; //剩余金额，插卡后，从黄工那里得到,购电后通知黄工更新
    //INT32U Remain_Money_Hoard_Limit;           //剩余电费囤积门限 0.01元   黄工已经有了，
    //INT32U Buy_Count;// 购电次数   插卡后 从黄工那里得到,购电后通知黄工更新该变量
    
    
    //一下参数使用了宏定义转换
    INT8U C_cpucard_number_WhemCardInsert[8];        //没当卡插入然后复位时得到的
    INT8U C_CommunicationPortMode;
    INT8U C_Meter_Ins_Flag ; //用来 变化 指令的， 没上面用
    INT8U C_Para_Updata_Flag;// 卡插进来时，从卡中得到，用来判断更新那个文件
    INT8U  C_CardType;// 卡类型，密钥恢复卡，还是用户卡，
    INT8U C_Dir_Return_Flag; //直接回写标志  当购电的次数相等时，使该变量为0xff，以便直接回写卡，不操作  
    INT8U CS[CS_BYTES];
    } C_Pre_Payment_Para ;

DECLARE_VAR_TYPE(C_Pre_Payment_Para, _C_Pre_Payment_Para);
EXT  volatile _C_Pre_Payment_Para  _Pre_Payment_Para;
#define  Pre_Payment_Para _Pre_Payment_Para.Var 
//EXT C_Pre_Payment_Para   Pre_Payment_Para;
//Pre_Payment_Para.BcdMeterID 
/*" 内部变量定义 "*/
#define LENGTH_USER_ID 6  // INT8U	UserID[ 6 ]; 
#define LENGTH_CARD_ID_BACKUP 8  //INT8U	Cpucard_Number_old_BackUpInEerom[8];
#define cpucard_number  (Pre_Payment_Para.C_cpucard_number_WhemCardInsert) //cpu卡号, 分散因子"  cpu卡 复位时得到
#define LENGTH_CARD_ID_WHEN_CARD_INSERT 8 //Pre_Payment_Para.C_cpucard_number_WhemCardInsert
#define CommunicationPortMode  (Pre_Payment_Para.C_CommunicationPortMode)
#define Meter_Ins_Flag   (Pre_Payment_Para.C_Meter_Ins_Flag) //找不到，不知道用来干嘛的，暂时自己定义
#define Para_Updata_Flag  (Pre_Payment_Para.C_Para_Updata_Flag)
#define CardType  (Pre_Payment_Para.C_CardType)
#define Dir_Return_Flag  (Pre_Payment_Para.C_Dir_Return_Flag)
 
typedef struct {

   INT32U CardKindErr   : 1; ///卡类型错（购电卡， 参数预置卡。。）计入非法卡插入次数
   INT32U MeterIdErr  : 1; /// 表号不匹配，计入非法卡插入次数 
   INT32U Client_Id_Err    : 1; ///<用户号码错误当表开户了后会出现 表未开户不会出现  用户编号错误  计入非法卡插入次数
   INT32U CpuCardExternlAuthenticationErr  : 1; /// 外部认证错  计入非法卡插入次数
   INT32U CpuCardInternlAuthenticationErr  :1; /// 内部认证， 即身份验证。计入非法卡插入次数
  
   INT32U WhenInTest_Insert_UserCard_Err   : 1; //未开户状态插入购电卡，补卡/
   INT32U BUY_CARD_KIND_ERR      : 1; // 购电卡卡类型错 补卡，开户卡。类型没找到以及.卡户状态 插入 开户卡， 计入非法卡插入次数
   INT32U CARD_BUY_COUNT_ERR : 1; //购电次数错误  计入非法卡插入次数
   INT32U Cpu_Card_Li_San_Yin_Zi_Err   : 1; /// 离散因子错了， 计入非法卡插入次数
   INT32U MoneyLimitErr     : 1; ///<剩余电费 + 充值电费大于 剩余 金额门限
   
   INT32U EsamUpdataErr    : 1;//esam更新错误
   INT32U OperationTimeOutErr   : 1;//卡操作 超过预定时间了 
   INT32U CPU_CARD_CARD_ATR_ERR     : 1; //卡片复位错 //不明卡， 卡损坏， 
   INT32U CPU_CARD_ESAM_ATR_ERR    : 1; //ESAM复位错
   INT32U CPU_CARD_LOSE     : 1; ///< 提前拔卡
   
   INT32U CPU_CARD_DATA_HEAD_ERR    : 1; //数据区68头错
   INT32U CPU_CARD_DATA_END_ERR    : 1; ///<  数据区16尾错
   INT32U CPU_CARD_DATA_CHECK_ERR      : 1; //数据区效验错
   INT32U CPU_CARD_COMM_DELAY_ERR  : 1; //CPU卡接收错 也可以说是提前拔卡
   INT32U Password_Key_Updata_ERR  : 1; ///  密钥更新错 
   
   INT32U Meter_Not_Prog_Status_Err   : 1;// ，未按编程键  
   INT32U Meter_Id_Set_Card_Id_Is_FULL_Err    : 1; ///表号设置卡表号满错误  
   INT32U Password_Count_Number_Is_Zero_Err   : 1; //密钥卡修改次数为零错误       还没用到
   INT32U Password_Version_Err : 1; //密钥卡版本错了    
   INT32U ESAM_DO_ERR  : 1; //ESAM操作错误     还没用到
           
   INT32U CPU_Para_Card_Version_Err      : 1; //参数设置卡版本错误或计数器到零  
   INT32U CPU_NEW_CARD_INI_ERR  : 1; //已经插过表的开户卡重复插未当前未开户表
   INT32U ReadWriteE2romErr    : 1; ///<  读写e2rom错误     
   INT32U Esam_Extern_Auth_Err     : 1; ///<  esam 外部认证 错误
   INT32U WhenInOperation_Insert_FirstUserCard_Err    : 1; // 运行状态插入 开户卡
   
   INT32U InsertBadCard_Err   : 1; //    
   INT32U re_erved  : 1; ///预留  bits
   
} C_CardErrorState;
//Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR
typedef union {
  
        C_CardErrorState  CardErrorState;
        INT32U   CardErrorState_INT32U;
        
}C_C_CardErrorState;
//EXT volatile  C_C_CardErrorState Card_Error_State;

DECLARE_VAR_TYPE(C_C_CardErrorState, _C_C_CardErrorState);
EXT volatile  _C_C_CardErrorState  c_Card_Error_State;
#define Card_Error_State  c_Card_Error_State.Var
//Far_Secure_Error_State.CPU_CARD_ESAM_ATR_ERR
 //Card_Error_State.CardErrorState_INT32U
#endif