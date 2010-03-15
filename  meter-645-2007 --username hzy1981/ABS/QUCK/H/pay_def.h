///Ԥ���Ѳ��� ///
/// RAM ///
#ifndef PAY_DEF_H_
#define PAY_DEF_H_

#undef EXT
#ifdef ALL_CARD_OPERATION_C_
#define EXT   
#else
#define EXT extern   
#endif


//�ϵ�ʱ��e��ȡ�����ݣ��µ����Ҫ���浽 e����ȡ�� ���ݣ� �������˵��
typedef struct {
    INT8U	UserID[ 6 ];                          //�û���� "// �����������̬�ʹ�e����ȡ�����Ϊδ����̬��ȡ��ȡ������ν
    INT8U	Cpucard_Number_old_BackUpInEerom[8];//��ɢ���ӣ��Ա��һ���ϵ�ֵ����Ҫ�󣬵�Ϊ���������򲹿�ʱ�޸ģ���e��ȡ���޳�ʼֵ
    INT8U  PassWord_Kind;                 //��Կ����"*/ //�ϵ��ʱ��Ҫ�õ��� ��ʽ��Կ״̬�����ǹ�����Կ״̬
    INT32U Para_Card_Version;           //"�ֳ��������ÿ��汾��,�ϵ��ʼ��Ҫ����"
    //������������ʱ�޸�
    INT8U Meter_Run_State;  //�������״̬��00����/01��װ/02���� "���һ���ϵ�ֵΪ0��������e���У��ϵ�ʱ��e��ȡ�����ǲ����򿪻���ʱ�޸�
    INT8U   BcdMeterID[6];//��ţ��Ա��һ���ϵ�ֵ����Ҫ�󣬱�������ÿ��޸� �Ϳ������޸�
    
    //INT32U Remain_Money; //ʣ����忨�󣬴ӻƹ�����õ�,�����֪ͨ�ƹ�����
    //INT32U Remain_Money_Hoard_Limit;           //ʣ���Ѷڻ����� 0.01Ԫ   �ƹ��Ѿ����ˣ�
    //INT32U Buy_Count;// �������   �忨�� �ӻƹ�����õ�,�����֪ͨ�ƹ����¸ñ���
    
    
    //һ�²���ʹ���˺궨��ת��
    INT8U C_cpucard_number_WhemCardInsert[8];        //û��������Ȼ��λʱ�õ���
    INT8U C_CommunicationPortMode;
    INT8U C_Meter_Ins_Flag ; //���� �仯 ָ��ģ� û������
    INT8U C_Para_Updata_Flag;// �������ʱ���ӿ��еõ��������жϸ����Ǹ��ļ�
    INT8U  C_CardType;// �����ͣ���Կ�ָ����������û�����
    INT8U C_Dir_Return_Flag; //ֱ�ӻ�д��־  ������Ĵ������ʱ��ʹ�ñ���Ϊ0xff���Ա�ֱ�ӻ�д����������  
    INT8U CS[CS_BYTES];
    } C_Pre_Payment_Para ;

DECLARE_VAR_TYPE(C_Pre_Payment_Para, _C_Pre_Payment_Para);
EXT  volatile _C_Pre_Payment_Para  _Pre_Payment_Para;
#define  Pre_Payment_Para _Pre_Payment_Para.Var 
//EXT C_Pre_Payment_Para   Pre_Payment_Para;
//Pre_Payment_Para.BcdMeterID 
/*" �ڲ��������� "*/
#define LENGTH_USER_ID 6  // INT8U	UserID[ 6 ]; 
#define LENGTH_CARD_ID_BACKUP 8  //INT8U	Cpucard_Number_old_BackUpInEerom[8];
#define cpucard_number  (Pre_Payment_Para.C_cpucard_number_WhemCardInsert) //cpu����, ��ɢ����"  cpu�� ��λʱ�õ�
#define LENGTH_CARD_ID_WHEN_CARD_INSERT 8 //Pre_Payment_Para.C_cpucard_number_WhemCardInsert
#define CommunicationPortMode  (Pre_Payment_Para.C_CommunicationPortMode)
#define Meter_Ins_Flag   (Pre_Payment_Para.C_Meter_Ins_Flag) //�Ҳ�������֪����������ģ���ʱ�Լ�����
#define Para_Updata_Flag  (Pre_Payment_Para.C_Para_Updata_Flag)
#define CardType  (Pre_Payment_Para.C_CardType)
#define Dir_Return_Flag  (Pre_Payment_Para.C_Dir_Return_Flag)
 
typedef struct {

   INT32U CardKindErr   : 1; ///�����ʹ����翨�� ����Ԥ�ÿ�����������Ƿ����������
   INT32U MeterIdErr  : 1; /// ��Ų�ƥ�䣬����Ƿ���������� 
   INT32U Client_Id_Err    : 1; ///<�û�������󵱱����˺����� ��δ�����������  �û���Ŵ���  ����Ƿ����������
   INT32U CpuCardExternlAuthenticationErr  : 1; /// �ⲿ��֤��  ����Ƿ����������
   INT32U CpuCardInternlAuthenticationErr  :1; /// �ڲ���֤�� �������֤������Ƿ����������
  
   INT32U WhenInTest_Insert_UserCard_Err   : 1; //δ����״̬���빺�翨������/
   INT32U BUY_CARD_KIND_ERR      : 1; // ���翨�����ʹ� ������������������û�ҵ��Լ�.����״̬ ���� �������� ����Ƿ����������
   INT32U CARD_BUY_COUNT_ERR : 1; //�����������  ����Ƿ����������
   INT32U Cpu_Card_Li_San_Yin_Zi_Err   : 1; /// ��ɢ���Ӵ��ˣ� ����Ƿ����������
   INT32U MoneyLimitErr     : 1; ///<ʣ���� + ��ֵ��Ѵ��� ʣ�� �������
   
   INT32U EsamUpdataErr    : 1;//esam���´���
   INT32U OperationTimeOutErr   : 1;//������ ����Ԥ��ʱ���� 
   INT32U CPU_CARD_CARD_ATR_ERR     : 1; //��Ƭ��λ�� //�������� ���𻵣� 
   INT32U CPU_CARD_ESAM_ATR_ERR    : 1; //ESAM��λ��
   INT32U CPU_CARD_LOSE     : 1; ///< ��ǰ�ο�
   
   INT32U CPU_CARD_DATA_HEAD_ERR    : 1; //������68ͷ��
   INT32U CPU_CARD_DATA_END_ERR    : 1; ///<  ������16β��
   INT32U CPU_CARD_DATA_CHECK_ERR      : 1; //������Ч���
   INT32U CPU_CARD_COMM_DELAY_ERR  : 1; //CPU�����մ� Ҳ����˵����ǰ�ο�
   INT32U Password_Key_Updata_ERR  : 1; ///  ��Կ���´� 
   
   INT32U Meter_Not_Prog_Status_Err   : 1;// ��δ����̼�  
   INT32U Meter_Id_Set_Card_Id_Is_FULL_Err    : 1; ///������ÿ����������  
   INT32U Password_Count_Number_Is_Zero_Err   : 1; //��Կ���޸Ĵ���Ϊ�����       ��û�õ�
   INT32U Password_Version_Err : 1; //��Կ���汾����    
   INT32U ESAM_DO_ERR  : 1; //ESAM��������     ��û�õ�
           
   INT32U CPU_Para_Card_Version_Err      : 1; //�������ÿ��汾��������������  
   INT32U CPU_NEW_CARD_INI_ERR  : 1; //�Ѿ������Ŀ������ظ���δ��ǰδ������
   INT32U ReadWriteE2romErr    : 1; ///<  ��дe2rom����     
   INT32U Esam_Extern_Auth_Err     : 1; ///<  esam �ⲿ��֤ ����
   INT32U WhenInOperation_Insert_FirstUserCard_Err    : 1; // ����״̬���� ������
   
   INT32U InsertBadCard_Err   : 1; //    
   INT32U re_erved  : 1; ///Ԥ��  bits
   
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