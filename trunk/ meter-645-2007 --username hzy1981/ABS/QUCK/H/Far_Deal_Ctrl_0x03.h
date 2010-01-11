
 
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
INT8U Far_Esamcard_Internal_Auth(INT8U *Point);
///�ڲ���������
INT8U Far_Deal_078102FF(INT8U * Data_Point );///���ݻس�
INT8U Far_Deal_07810201(INT8U *Data_Point );//���ݻس�
INT8U Far_Deal_078001FF(INT8U *Data_Point );//���ݲ�ѯ
INT8U Far_Deal_070001FF(INT8U * Data_Point );//
INT8U Far_Deal_07000201(INT8U * Data_Point );
INT8U Far_Deal_070002FF(INT8U * Data_Point );
INT8U Far_Deal_070102FF(INT8U * Data_Point );//��ֵ
INT8U Far_Deal_070101FF(INT8U * Data_Point );//����
INT8U Far_PassWord_Updata(INT8U * Data_Point,INT8U PassWord_ID );//��Կ����
INT8U Far_Deal_070202FF(INT8U * Data_Point );
INT8U Far_Deal_070203FF(INT8U * Data_Point );
INT8U Far_Deal_070201FF(INT8U * Data_Point );//D
INT8U Far_Deal_070204FF(INT8U * Data_Point );//D

INT8U Far_Read_Esam(INT8U cla,INT8U ins,INT8U t_p1,
              INT8U t_p2,INT8U lc,INT8U *address);
/*" дESAM�� ����MAC  д"*/
INT8U Far_Write_Esam(INT8U cla,INT8U ins,INT8U t_p1,
			INT8U t_p2,INT8U lc,INT8U *address,INT8U Flag );
INT8U    Far_Read_Esam(INT8U ,INT8U ,INT8U ,INT8U ,INT8U ,INT8U *);
INT8U Far_Deal_Order_0x03(INT8U *,INT8U  );
 
///////////
//�ϵ�ʱ��e��ȡ�����ݣ��µ����Ҫ���浽 e����ȡ�� ���ݣ� �������˵��
typedef struct {
    INT8U  ID_Ins_Counter  ;//Զ��Ԥ�����ã� ���дesam�����������3�Σ�������дesam�����д�ɹ�һ�Σ���ֵ��0�������
    INT8U Far_SendLen;//���͵������򳤶ȣ�645Э���ж����L�ֶ�ֵ  //�Լ������
   // INT8U Far_Auth_Day_Follow;// �����֤��Ч�� �����գ� 
    INT8U  c_esam_number[8];//���Ծֲ��������棬     ��չ��
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  C_Far_Pre_Payment_Para ;

DECLARE_VAR_TYPE(C_Far_Pre_Payment_Para, _C_Far_Pre_Payment_Para);
EXT  volatile _C_Far_Pre_Payment_Para   _Far_Pre_Payment_Para;
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
	INT8U FAR_OTHER_ERR:1;		/*"--��������----"*/
	INT8U FAR_REPEAT_INCREASE_ERR:1;		/*"--�ظ���ֵ----------------"*/
	INT8U FAR_ESAM_AUTH_ERR:1;	/*"--ESAM��֤ʧ��-----------"*/
	INT8U FAR_IDENTITY_AUTH_ERR:1;	/*"--�����֤ʧ��---------"*/
	INT8U FAR_CLIENT_ID_ERR:1;			/*"--�ͻ���Ų�ƥ��-------"*/
	INT8U FAR_BUY_COUNT_ERR:1;			/*"--���������---"*/
	INT8U FAR_BUY_MONEY_OVER_ERR:1;				/*"--��ѳ��ڻ�---"*/
	INT8U :1;			/*"--����---"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
	INT8U :1;						/*"--����------------"*/
      }bit;
      INT16U intd;  
}; 
EXT volatile union  SECURITY_AUTH_ERR_INFORMATION Far_Security_Auth_Err_Info;	/*��ȫ��֤������Ϣ��*/

#define OTHER_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_OTHER_ERR
#define REPEAT_INCREASE_ERR_DEFINE				        Far_Security_Auth_Err_Info.bit.FAR_REPEAT_INCREASE_ERR
#define ESAM_AUTH_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_ESAM_AUTH_ERR
#define IDENTITY_AUTH_ERR_DEFINE					Far_Security_Auth_Err_Info.bit.FAR_IDENTITY_AUTH_ERR
#define CLIENT_ID_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_CLIENT_ID_ERR
#define BUY_COUNT_ERR_DEFINE						Far_Security_Auth_Err_Info.bit.FAR_BUY_COUNT_ERR
#define BUY_MONEY_OVER_ERR_DEFINE				        Far_Security_Auth_Err_Info.bit.FAR_BUY_MONEY_OVER_ERR
 
union ID
{
        INT8U d[4];
        INT16U  i;
        INT16U  new_i[2];//2008-7-9 17:54:13
        INT32U l;
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
//qEXT INT32U  FarCloseTime=0;

//���ݽṹ����//
struct Authentication_Instruction
{
	INT8U cryptograph1[8];								/*"����1"*/
	INT8U	random_number1[8];							/*"�����1"*/
	INT8U disperse_gene[8];							/*"��ɢ����"*/
};

struct Authentication_Responsion
{
	INT8U	random_number2[4];							/*"�����2"*/
	INT8U	esam_serial_number[8];						/*"ESAM���к�"*/	
};

struct Far_Identity_Authentication_Define
{
	struct Authentication_Instruction Instruction;					/*"�����ָ֤��"*/
        //struct Authentication_Responsion Responsion;					////Ӧ�𲢷��������2//
};
EXT volatile struct Far_Identity_Authentication_Define Far_Identity_Auth_Data;	//�ñ�����Զ�������֤����Far_Esamcard_Internal_Auth�г�ʼ��
INT8U Check_Remote_Prog_Status();
#endif