
 
#ifndef  FAR_DEAL_CTRL_0X33_H_
#define FAR_DEAL_CTRL_0X33_H_


#undef EXT
#ifdef FAR_DEAL_CTRL_0X33_C_
#define EXT
#else
#define EXT extern
#endif 
INT16U GetSecurity_Auth_Err_Info(void);
 
INT8U Esam_Decrypt(INT8U *pSrc, INT16U SrcLen);//对外接口函数

//远程认证命令接口(控制码为03)
//pSrc表示远程帧的数据域， 长度为645帧中L段的值
//SrcLen表示数据域长度
//pDst表示经过处理后返回的数据域
//*pLen表示返回的数据长度
//pDst_Start和DstLen一起限定pDst和返回的数据长度
//1成功， 0失败，
INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen);//对外接口
unsigned char Far_Esamcard_Internal_Auth(unsigned char *Point);
///内部函数定义
unsigned char Far_Deal_078102FF(unsigned char * Data_Point );///数据回抄
unsigned char Far_Deal_07810201(unsigned char *Data_Point );//数据回抄
unsigned char Far_Deal_078001FF(unsigned char *Data_Point );//数据查询
unsigned char Far_Deal_070001FF(unsigned char * Data_Point );//
unsigned char Far_Deal_07000201(unsigned char * Data_Point );
unsigned char Far_Deal_070002FF(unsigned char * Data_Point );
unsigned char Far_Deal_070102FF(unsigned char * Data_Point );//充值
unsigned char Far_Deal_070101FF(unsigned char * Data_Point );//开户
unsigned char Far_PassWord_Updata(unsigned char * Data_Point,unsigned char PassWord_ID );//密钥更新
unsigned char Far_Deal_070202FF(unsigned char * Data_Point );
unsigned char Far_Deal_070203FF(unsigned char * Data_Point );
unsigned char Far_Deal_070201FF(unsigned char * Data_Point );//D

unsigned char Far_Read_Esam(unsigned char cla,unsigned char ins,unsigned char t_p1,
              unsigned char t_p2,unsigned char lc,unsigned char *address);
/*" 写ESAM卡 ，带MAC  写"*/
unsigned char Far_Write_Esam(unsigned char cla,unsigned char ins,unsigned char t_p1,
			unsigned char t_p2,unsigned char lc,unsigned char *address,unsigned char Flag );
unsigned char    Far_Read_Esam(unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char *);
unsigned char Far_Deal_Order_0x03(unsigned char *,unsigned char  );
 
///////////
//上电时从e方取的数据，下电后需要保存到 e方中取的 数据， ，具体见说明
typedef struct {
    INT8U  ID_Ins_Counter  ;//远程预付费用， 如果写esam错误次数超过3次，不允许写esam，如果写成功一次，该值清0，如果该
    INT8U Far_SendLen;//发送的数据域长度，645协议中定义的L字段值  //自己定义的
   // INT8U Far_Auth_Day_Follow;// 身份认证有效日 跟随日， 
    INT8U  c_esam_number[8];//可以局部变量代替，   扩展用
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  C_Far_Pre_Payment_Para ;

DECLARE_VAR_TYPE(C_Far_Pre_Payment_Para, _C_Far_Pre_Payment_Para);
EXT   _C_Far_Pre_Payment_Para   _Far_Pre_Payment_Para;
#define  FarPrePayment  _Far_Pre_Payment_Para.Var 

//EXT C_Pre_Payment_Para   Pre_Payment_Para;
//FarPrePayment.ID_Ins_Counter 
/*" 内部变量定义 "*/
 
#define esam_number  (FarPrePayment.c_esam_number) //cpu卡号, 分散因子"  cpu卡 复位时得到
/////
union SECURITY_AUTH_ERR_INFORMATION
{
    struct
      {  
	unsigned char FAR_OTHER_ERR:1;		/*"--其他错误----"*/
	unsigned char FAR_REPEAT_INCREASE_ERR:1;		/*"--重复充值----------------"*/
	unsigned char FAR_ESAM_AUTH_ERR:1;	/*"--ESAM验证失败-----------"*/
	unsigned char FAR_IDENTITY_AUTH_ERR:1;	/*"--身份认证失败---------"*/
	unsigned char FAR_CLIENT_ID_ERR:1;			/*"--客户编号不匹配-------"*/
	unsigned char FAR_BUY_COUNT_ERR:1;			/*"--购电次数错---"*/
	unsigned char FAR_BUY_MONEY_OVER_ERR:1;				/*"--电费超囤积---"*/
	unsigned char :1;			/*"--保留---"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
	unsigned char :1;						/*"--保留------------"*/
      }bit;
      unsigned int intd;  
}; 
EXT union  SECURITY_AUTH_ERR_INFORMATION Far_Security_Auth_Err_Info;	/*安全认证错误信息字*/

#define OTHER_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_OTHER_ERR
#define REPEAT_INCREASE_ERR_DEFINE				        Far_Security_Auth_Err_Info.bit.FAR_REPEAT_INCREASE_ERR
#define ESAM_AUTH_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_ESAM_AUTH_ERR
#define IDENTITY_AUTH_ERR_DEFINE					Far_Security_Auth_Err_Info.bit.FAR_IDENTITY_AUTH_ERR
#define CLIENT_ID_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_CLIENT_ID_ERR
#define BUY_COUNT_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_BUY_COUNT_ERR
#define BUY_MONEY_OVER_ERR_DEFINE				        Far_Security_Auth_Err_Info.bit.FAR_BUY_MONEY_OVER_ERR
 
union ID
{
        unsigned char d[4];
        unsigned int  i;
        unsigned int  new_i[2];//2008-7-9 17:54:13
        unsigned long l;
}; 
typedef struct  
{
INT8U  Ok_Flag ;
INT8U CS[CS_BYTES];
}C_Far_Identity_Auth_Ok_Flag ;
DECLARE_VAR_TYPE(C_Far_Identity_Auth_Ok_Flag ,_C_Far_Identity_Auth_Ok_Flag);
EXT _C_Far_Identity_Auth_Ok_Flag   _Far_Identity_Auth_Ok_Flag ;
#define   Far_Identity_Auth_Ok_Flag   _Far_Identity_Auth_Ok_Flag.Var.Ok_Flag 

//EXT INT8U  Far_Identity_Auth_Ok_Flag;						 		/*"远程身份认证成功标志"*/ 
//qEXT unsigned long  FarCloseTime=0;

//数据结构定义//
struct Authentication_Instruction
{
	unsigned char cryptograph1[8];								/*"密文1"*/
	unsigned char	random_number1[8];							/*"随机数1"*/
	unsigned char disperse_gene[8];							/*"分散因子"*/
};

struct Authentication_Responsion
{
	unsigned char	random_number2[4];							/*"随机数2"*/
	unsigned char	esam_serial_number[8];						/*"ESAM序列号"*/	
};

struct Far_Identity_Authentication_Define
{
	struct Authentication_Instruction Instruction;					/*"身份认证指令"*/
	struct Authentication_Responsion Responsion;					/*"应答并返回随机数2"*/
};
EXT struct Far_Identity_Authentication_Define Far_Identity_Auth_Data;	//该变量在远程身份认证函数Far_Esamcard_Internal_Auth中初始化
 
#endif