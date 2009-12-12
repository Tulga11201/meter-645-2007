
 
#ifndef  FAR_DEAL_CTRL_0X33_H_
#define FAR_DEAL_CTRL_0X33_H_


#undef EXT
#ifdef FAR_DEAL_CTRL_0X33_C_
#define EXT
#else
#define EXT extern
#endif 
INT16U GetSecurity_Auth_Err_Info(void);
 
INT8U Esam_Decrypt(INT8U *pSrc, INT16U SrcLen);//����ӿں���

//Զ����֤����ӿ�(������Ϊ03)
//pSrc��ʾԶ��֡�������� ����Ϊ645֡��L�ε�ֵ
//SrcLen��ʾ�����򳤶�
//pDst��ʾ��������󷵻ص�������
//*pLen��ʾ���ص����ݳ���
//pDst_Start��DstLenһ���޶�pDst�ͷ��ص����ݳ���
//1�ɹ��� 0ʧ�ܣ�
INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen);//����ӿ�
unsigned char Far_Esamcard_Internal_Auth(unsigned char *Point);
///�ڲ���������
unsigned char Far_Deal_078102FF(unsigned char * Data_Point );///���ݻس�
unsigned char Far_Deal_07810201(unsigned char *Data_Point );//���ݻس�
unsigned char Far_Deal_078001FF(unsigned char *Data_Point );//���ݲ�ѯ
unsigned char Far_Deal_070001FF(unsigned char * Data_Point );//
unsigned char Far_Deal_07000201(unsigned char * Data_Point );
unsigned char Far_Deal_070002FF(unsigned char * Data_Point );
unsigned char Far_Deal_070102FF(unsigned char * Data_Point );//��ֵ
unsigned char Far_Deal_070101FF(unsigned char * Data_Point );//����
unsigned char Far_PassWord_Updata(unsigned char * Data_Point,unsigned char PassWord_ID );//��Կ����
unsigned char Far_Deal_070202FF(unsigned char * Data_Point );
unsigned char Far_Deal_070203FF(unsigned char * Data_Point );
unsigned char Far_Deal_070201FF(unsigned char * Data_Point );//D

unsigned char Far_Read_Esam(unsigned char cla,unsigned char ins,unsigned char t_p1,
              unsigned char t_p2,unsigned char lc,unsigned char *address);
/*" дESAM�� ����MAC  д"*/
unsigned char Far_Write_Esam(unsigned char cla,unsigned char ins,unsigned char t_p1,
			unsigned char t_p2,unsigned char lc,unsigned char *address,unsigned char Flag );
unsigned char    Far_Read_Esam(unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char *);
unsigned char Far_Deal_Order_0x03(unsigned char *,unsigned char  );
 
///////////
//�ϵ�ʱ��e��ȡ�����ݣ��µ����Ҫ���浽 e����ȡ�� ���ݣ� �������˵��
typedef struct {
    INT8U  ID_Ins_Counter  ;//Զ��Ԥ�����ã� ���дesam�����������3�Σ�������дesam�����д�ɹ�һ�Σ���ֵ��0�������
    INT8U Far_SendLen;//���͵������򳤶ȣ�645Э���ж����L�ֶ�ֵ  //�Լ������
   // INT8U Far_Auth_Day_Follow;// �����֤��Ч�� �����գ� 
    INT8U  c_esam_number[8];//���Ծֲ��������棬   ��չ��
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  C_Far_Pre_Payment_Para ;

DECLARE_VAR_TYPE(C_Far_Pre_Payment_Para, _C_Far_Pre_Payment_Para);
EXT   _C_Far_Pre_Payment_Para   _Far_Pre_Payment_Para;
#define  FarPrePayment  _Far_Pre_Payment_Para.Var 

//EXT C_Pre_Payment_Para   Pre_Payment_Para;
//FarPrePayment.ID_Ins_Counter 
/*" �ڲ��������� "*/
 
#define esam_number  (FarPrePayment.c_esam_number) //cpu����, ��ɢ����"  cpu�� ��λʱ�õ�
/////
union SECURITY_AUTH_ERR_INFORMATION
{
    struct
      {  
	unsigned char FAR_OTHER_ERR:1;		/*"--��������----"*/
	unsigned char FAR_REPEAT_INCREASE_ERR:1;		/*"--�ظ���ֵ----------------"*/
	unsigned char FAR_ESAM_AUTH_ERR:1;	/*"--ESAM��֤ʧ��-----------"*/
	unsigned char FAR_IDENTITY_AUTH_ERR:1;	/*"--�����֤ʧ��---------"*/
	unsigned char FAR_CLIENT_ID_ERR:1;			/*"--�ͻ���Ų�ƥ��-------"*/
	unsigned char FAR_BUY_COUNT_ERR:1;			/*"--���������---"*/
	unsigned char FAR_BUY_MONEY_OVER_ERR:1;				/*"--��ѳ��ڻ�---"*/
	unsigned char :1;			/*"--����---"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
	unsigned char :1;						/*"--����------------"*/
      }bit;
      unsigned int intd;  
}; 
EXT union  SECURITY_AUTH_ERR_INFORMATION Far_Security_Auth_Err_Info;	/*��ȫ��֤������Ϣ��*/

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

//EXT INT8U  Far_Identity_Auth_Ok_Flag;						 		/*"Զ�������֤�ɹ���־"*/ 
//qEXT unsigned long  FarCloseTime=0;

//���ݽṹ����//
struct Authentication_Instruction
{
	unsigned char cryptograph1[8];								/*"����1"*/
	unsigned char	random_number1[8];							/*"�����1"*/
	unsigned char disperse_gene[8];							/*"��ɢ����"*/
};

struct Authentication_Responsion
{
	unsigned char	random_number2[4];							/*"�����2"*/
	unsigned char	esam_serial_number[8];						/*"ESAM���к�"*/	
};

struct Far_Identity_Authentication_Define
{
	struct Authentication_Instruction Instruction;					/*"�����ָ֤��"*/
	struct Authentication_Responsion Responsion;					/*"Ӧ�𲢷��������2"*/
};
EXT struct Far_Identity_Authentication_Define Far_Identity_Auth_Data;	//�ñ�����Զ�������֤����Far_Esamcard_Internal_Auth�г�ʼ��
 
#endif