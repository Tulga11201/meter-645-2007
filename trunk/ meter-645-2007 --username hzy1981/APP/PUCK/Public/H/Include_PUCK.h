
#ifndef PUBLIC_C_F_S
#define PUBLIC_C_F_S

#ifndef PUB_PUCK_C
#define PUB_PUCK_EXT  extern volatile
#else
#define PUB_PUCK_EXT volatile
#endif



/**********************************�����Ǽ�����������**************************************/

//�����������״̬��
#define MEASU_NO_ERR      	0
#define MEASU_SIGN_ERR    	1  //SIG����
#define MEASU_RD3TIMES_ERR    	2  //�����ݴ�
#define MEASU_CAL_ERR    	3  //���������У�����У������
#define MEASU_PUL_SPEC_ERR     	4  //��������������
#define MEASU_FREQU_ERR   	5  //Ƶ�ʴ���
#define MEASU_VOLT_ERR  	6  //��ѹ����
#define MEASU_CURR_ERR  	7  //���������
#define MEASU_POWER_ERR  	8  //���ʳ���
#define MEASU_ACCU_FLOW_ERR   	9  //��������̫��
#define MEASU_ENR_REDUCE_ERR 	10  //���ܵ���
#define MEASU_ENR_LIMIT_ERR 	11  //������Χ����
#define MEASU_DATA_LOGIC_ERR 	12  //�߼�����
#define MEASU_RESET_ERR 	13  //��λ���̴���
#define MEASU_CS_ERR            14  //У��ʹ�
#define MEASU_ENERG_FLOW_ERR   	15  //�������ʱ����������̫��
#define MEASU_CREEP_ENERG_ADD  	16  //Ǳ��ʱ������������
#define MEASU_TEMP_GET_ERR  	17  //�¶Ȼ�ȡʧ��
#define MEASU_PULSE_ERR  	18  //���峣����

#define MAX_MEASU_ERR 	        MEASU_PULSE_ERR

#define NO_QUADRANT   0             //��Ч����
#define QUADRANT1     (NO_QUADRANT+1)
#define QUADRANT2     (QUADRANT1+1)
#define QUADRANT3     (QUADRANT2+1)
#define QUADRANT4     (QUADRANT3+1)



#ifdef MEASURE_ERROR_STATICS_EN
  #define MEASURE_ERR_NUM  (MAX_MEASU_ERR+1)
  typedef struct
  { 
    INT16U        ResetNum;
    INT8U         AcFlag;
    INT32U        LastValue;
    INT32U        CurrValue;
    INT32U        ChangeValue;
    INT8U         Num[MEASURE_ERR_NUM];
    INT8U CS[CS_BYTES]; 
  }MEASURE_ERROR;
NO_INIT PUB_PUCK_EXT MEASURE_ERROR Measure_Err_Info;  
#endif


typedef struct
{
  INT8U A_LossV:1;            //A��ʧѹ
  INT8U B_LossV:1;            //B��ʧѹ
  INT8U C_LossV:1;            //C��ʧѹ
  INT8U V_SeqErr:1;           //��ѹ�����
  INT8U I_SeqErr:1;           //���������
  INT8U A_Creep:1;            //AǱ��
  INT8U B_Creep:1;            //BǱ��
  INT8U C_Creep:1;            //CǱ��
  
  INT8U A_APwrDir:1;        //A�й����ʷ���0������1����
  INT8U B_APwrDir:1;        //B�й����ʷ���0������1����
  INT8U C_APwrDir:1;        //C�й����ʷ���0������1����
  INT8U SUM_APwrDir:1;      //�����й����ʷ���0������1����  
  INT8U A_RPwrDir:1;        //A�޹����ʷ���0������1����
  INT8U B_RPwrDir:1;        //B�޹����ʷ���0������1����
  INT8U C_RPwrDir:1;        //C�޹����ʷ���0������1����  
  INT8U SUM_RPwrDir:1;      //�����޹����ʷ���0������1���� 
  
  INT8U MeasuIntOk:1;       //����оƬ��ʼ�����
  INT8U PulseEn:1;          //�������ʹ��
  INT8U DataRecFlg:1;       //1�����յ��������ݱ�־��Ӧ�ò��ȡ���ݣ�0-----��û��׼���ü������ݣ���Ҫȡ
  INT8U CalStatus:2;        //У��״̬��0------��У��1------У���У�2------У����ɣ�
  INT8U Reserved:3;
  //����8bits���� 
  INT8U CS[CS_BYTES];
}MEASU_STATUS;              //����״̬��
PUB_PUCK_EXT MEASU_STATUS Pri_MeasuStatVar;    //MeasuIC״̬��

typedef struct
{ 
  INT8U Sync_Flag;
  INT8U ParseMode;                  //331����341��ʽ,�� V_Spec�����: PARSE_331-- 0;341-----1
  INT8U P_Spec;                    //���峣�����:
  INT8U V_Spec;                    //��ѹ���:
  INT8U I_Spec;                    //�������:  
  INT8U T_FH;                      //���ڿ�����
  INT8U CS[CS_BYTES];              //��Ҫ������SRAM��У���
}MEASU_SYSMODE;                   //MeasuICϵͳģʽ��
NO_INIT PUB_PUCK_EXT MEASU_SYSMODE MeasuSysMode;

typedef struct
{  
  INT32U A;
  INT32U B;
  INT32U C;
  INT32U Sum;
}MEASU_DATA;       //MeasuIC˲ʱ����������


typedef struct
{  
  INT8U A;
  INT8U B;
  INT8U C;
  INT8U Sum;
}MEASUFLAG;       //MeasuIC˲ʱ��״̬����


typedef struct
{  
  INT32S A;
  INT32S B;
  INT32S C;
  INT32S Sum;
}MEASU_DATA_SIGN;       //MeasuIC˲ʱ���������ݣ�������


/*
typedef struct
{
  INT8U Cal_Status[2];    //�ϱ�״̬�֣�˳��A/B/C�๦��,��A/B/C��λ,A/B/C���ѹ��A/B/C�����
  INT8U CS[CS_BYTES];
}CAL_STSTUS;
PUB_PUCK_EXT  CAL_STSTUS Cal_Status_Var;
*/

//������������ݵľ��ȣ�������С������
#define UNIT_KW_KAR   1000000    //0.000001kw�����޹�С���㱣��һ��

#define UNIT_V        10000      //��ѹ��λ��0.0001V
#define UNIT_A        10000      //������λ��0.0001A;���߰�ʱ��λ
#define UNIT_FACTOR   1000000    //����������λ
#define UNIT_HZ       1000000    //Ƶ�ʵ�λ
#define UNIT_DEGREE   100        //�Ƕȵ�λ

#define UNIT_KWH_KVAR 100000     //0.00001kwh=0.01wh�����޹�С���㱣��һ��

#define  UNIT_AS      10000                //��ʱ:��λ��  0.0001An.s
#define  UNIT_KA2S    10000                //ͭ��:��λ�� 0.0000001kA2s
#define  UNIT_MV2S    100                  //����:��λ��0.00000001MV2s
#define  UNIT_TGFAS   100                  //�ϳ�����λ��0.01kvars



#define TEMP_BUF_LEN    268
DECLARE_BUF_TYPE (INT8U,TEMP_BUF_LEN,S_Buf_Temp);

#ifdef PUB_PUCK_C
PUB_PUCK_EXT S_Buf_Temp S_Buf_PUCK={CHK_BYTE,{0},CHK_BYTE};
#endif
PUB_PUCK_EXT S_Buf_Temp S_Buf_PUCK;

#define  Temp_Buf_PUCK S_Buf_PUCK.Buf

typedef struct
{
 MEASU_DATA AcPower;       //�й�����:UNIT:0.000001kW
 MEASU_DATA ReacPower;     //�޹�����:UNIT:0.000001kvar
 MEASU_DATA AppPower;      //���ڹ���:UNIT:0.000001kva
 MEASU_DATA Volt;          //��ѹ��Чֵ���޺��� UNIT:0.0001V
 MEASU_DATA Curr;          //������Чֵ: UNIT:0.0001A	
 MEASU_DATA PFactor;       //��������: UNIT:0.000001
 MEASU_DATA Freq;          //Ƶ��:UNIT:0.000001Hz
 MEASUFLAG  Quadrant;      //�������ޣ�QUADRANT1��QUADRANT4����1��4���ޡ�
 MEASU_DATA Angle;         //��ѹ�����нǣ�UINT:0.01��
 INT16S    Temprate;       //�¶ȣ���λ��0.01�ȣ����ȣ�0.25��
 INT8U CS[CS_BYTES];
}MEASU_INSTANT;   //MeasuIC˲ʱ����������

PUB_PUCK_EXT MEASU_INSTANT Pri_TempIntantVar;

typedef struct
{
  INT32U Chang_Plus_AcEnerg[4];            //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
  INT32U Chang_Nega_AcEnerg[4];            //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
  
  //INT32U Chang_Plus_ReacEnerg[4];          //A/B/C/SUM��Ԫ�������޹�����(�޹����1):��λ:0.01warh  
  //INT32U Chang_Nega_ReacEnerg[4];          //A/B/C/SUM��Ԫ�������޹�����(�޹����2):��λ:0.01warh
  
  INT32U Chang_Quad_ReacEnerg[4][4];       //A/B/C/SUM��Ԫ���������޹�����,Chang_Quad_ReacEnerg[1][2]��ʾB��3�����޹�

#if APP_ENERG_EN >0 //��PQS���ڵ��ܱ�
  INT32U Chang_Plus_PQSEnerg[4];            //A/B/C/SUM��Ԫ��������������:��λ:0.01wh
  INT32U Chang_Nega_PQSEnerg[4];            //A/B/C/SUM��Ԫ��������������:��λ:0.01wh
#endif
  
  INT32U Add_AmpaHour[4];                 //A,B,C,sum��ʱ�ۼ�:0.0001A.s,�ۼ��� 
  INT32U Add_CopperLoss[4];		  //A,B,C,sumͭ��,��λΪ��0.0000001kA2s���ۼ���
  INT32U Add_IronLoss[4];		  //A,B,C,sum����,��λΪ 0.00000001MV2s���ۼ���
  INT32U Add_GenaralErr[4];		  //A,B,C,sum�ϳ����,��λ:0.01kvars���ۼ���
  INT8U CS[CS_BYTES];
}MEASU_ENERG;                             //�����ۼ����ݺ���������


/************************�������ṩ��Ӧ�ò�����ݽӿ�*************************************/
PUB_PUCK_EXT MEASU_STATUS      Measu_Status_Mode_ToPub_PUCK;   //��������״̬��(�Ѱ���331/341����)
PUB_PUCK_EXT  MEASU_INSTANT    Measu_InstantData_ToPub_PUCK;    //����˲ʱ����
PUB_PUCK_EXT MEASU_ENERG       Measu_Energ_ToPub_PUCK;       //�����ۼ�������

#ifdef MEASURE_VAR_BAK_EN
  PUB_PUCK_EXT MEASU_ENERG       Measu_Energ_ToPub_Bak;       //�����ۼ�������
#endif

#ifdef Measu_VOLTANGLE_EN
PUB_PUCK_EXT Measu_ANGLE   MeaVoltAngle_ToPub_PUCK;          //�ṩ��Ӧ�õ����ݽṹ��
#endif



typedef struct
{
 MEASU_DATA_SIGN AcPower;       //�й�����:UNIT:0.000001kW
 MEASU_DATA_SIGN ReacPower;     //�޹�����:UNIT:0.000001kvar
 MEASU_DATA_SIGN AppPower;      //���ڹ���:UNIT:0.000001kva
 MEASU_DATA_SIGN Curr;          //������Чֵ: UNIT:0.0001A	
 MEASU_DATA_SIGN PFactor;       //��������: UNIT:0.000001
 INT16S    Temprate;       //�¶ȣ���λ��0.01�ȣ����ȣ�0.25��
 INT8U CS[CS_BYTES];
}MEASU_INSTANT_SIGN;   //MeasuIC˲ʱ����������

PUB_PUCK_EXT  MEASU_INSTANT_SIGN    Measu_Sign_InstantData_PUCK;    //����˲ʱ����:������

/************************���º�������*************************************/
void Measu_Main_Puck(INT8U Flag);


INT16U Get_Measu_AcculateData_PUCK(INT8U ID,void *Dst,void *Dst_Start,INT16U DstLen,INT16U DstMaxLen);


INT8U Get_RemoteCtrlKey_PUCK(INT8U Id);
INT8U Get_MeterKey_PUCK(INT8U Id);
INT8U Get_Curr_ComType_PUCK(INT8U Id);


void Delayn10MS(INT32U n);
void SYS_TimeDly_Ms(INT32U n);
void SYS_TimeDly_Sec(INT32U n);

INT8U Get_Buf_MulitByte_Sum(INT8U *Src,INT16U SrcLen,INT8U ByteGroup,INT8U *Dst,INT8U DstLen);
INT8U CalibMeterProc_PUCK(INT16U Code,INT8U Para[],INT8U ParaLen);
void Retry_WritePara_To_IC(void);
INT8U Init_Pulse_Ram(void);
INT8U Check_Power_Grid_Event(INT8U IsVoltNeg);
FP32S Get_Un(void);
FP32S Get_In(void);
INT32U Get_Max_Power(void);
INT32U Get_Sys_Pulse(void);
INT8U GetSysModeProc(void);
void Load_Adj_OnePara_To_IC(PROTO_DI);
void Measure_Error_Statics(INT8U Code,INT8U RstFlag);
void Init_Measure_Ram(void);
INT8U Load_MeasureIC_Para(void);
INT8U Load_Spec_Para_To_IC(void);
//void Clr_All_Cal_Status(void);
INT32U Get_Istart_Const(void);
INT32U Get_HighPulse_Const(void);
INT32U Get_Volt_Adj_Rate(void);
INT32U GetEnergSumMode(void);
INT32U Get_App_Mode(void);
INT32U Get_Iregion4(void);
void Test_HardWare_PUCK(void);
void InitLcdAllRam(void);
INT32U Get_Min_Num(INT32U a,INT32U b,INT32U c);
void Chk_Table_Conflict(void);
void Init_Measu_PUCK(void);
INT8U Init_Para(void);
INT8U Judge_I_Start(void);
INT8U CHeck_Same_Byte(INT8U *Src,INT8U Byte,INT16U Len);
FP32S Get_Start_Current(void);
void Print_Measure_Err_Info(void);
void Clr_Energ_Accu(void);
void Measu_Event_Main(void);
void Emerg_Event_Proc(void);
INT8U Get_Cal_Exsit(void);
void Init_Measure_IC(void);
#endif
