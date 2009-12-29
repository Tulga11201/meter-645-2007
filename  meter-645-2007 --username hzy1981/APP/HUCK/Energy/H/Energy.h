#ifndef ENERGY_H
#define ENERGY_H

#include "Pub_Time.h"

#undef EXT
#ifdef ENERGY_SETTLE_C
#define EXT
#else
#define EXT extern
#endif

#define POWER_ON_RST 0x5A
#define SOFT_RST 0xA5

//����Cmp_Time��������ֵ
#define TIME_EQU 0
#define TIME_AFT 1
#define TIME_BEF 2

//�������ʷ���,Check_Year_Scheme()�����ķ���
#define YEAR_SCHEME0 0x66
#define YEAR_SCHEME1 0x77

#define DATE_SCHEME0 0x88
#define DATE_SCHEME1 0x99

#define RATE_SCHEME0 0xAA
#define RATE_SCHEME1 0xBB

#define STEP_SCHEME0 0xCC
#define STEP_SCHEME1 0xDD

#define BEF_SWITCH_TIME 0x55
#define AFT_SWITCH_TIME 0xEE

#define CALC_RAM 0//������ʻ��߷��ʷ���ʱ����RAM�еĲ���
#define CALC_ROM 1//������ʻ��߷��ʷ���ʱ����ROM�еĲ���

//�ձ�־���壬�����������ա������պ�һ����
#define HOLIDAY 0
#define WEEK_REST_DAY 1
#define NORMAL_DAY 2

//�ۼ����ı���ֵ,��Լ�е����ݶ���λ2λС����Cur_Energy�е����ݶ���3λС��
#define ENERGY_RATIO ((INT32U)100)//����
#define COPPERLOSS_RATIO ((INT32U)3600*100000)//ͭ��
#define IRONLOSS_RATIO ((INT32U)3600*1000000)//����
#define TRANSERR_RATIO ((INT32U)3600)//���������
#define AH_RATIO ((INT32U)3600*100)//��ֵ����
#define MONEY_RATIO ((INT32U)10000)//ÿ����ʱ�����7λС�����ܽ����3ΪС���������Ҫ/10000

#define MAX_ACTIVE_INC 1000 //1000wh��ÿ���������1�ȵ磬������Ϊ�Ƿ����ݣ�����
#define MAX_REACTIVE_INC 1000 //1000wh

#define MONEY_MODE  0 //�����Ԥ����
#define ENERGY_MODE 1 //������Ԥ����

#define PREPAID_STEP_SCHEME ((Cur_Rate_Info.Step_Scheme EQ STEP_SCHEME0)?1:2)
#define PREPAID_STEP_NO     (Cur_Rate_Info.Step_No + 1)

//Ԥ���ѽ����ߵ���״̬�궨��
#define PREPAID_ENERGY_ENOUGH    0x01 //ʣ���������
#define PREPAID_ENERGY_LEFT1     0x02 //�����޶�1
#define PREPAID_ENERGY_LEFT2     0x03 //�����޶�2
#define PREPAID_ENERGY_ZERO      0x04 //����0
#define PREPAID_ENERGY_OVERDRAFT 0x05 //͸֧

#define PREPAID_MONEY_ENOUGH     0x06 //ʣ�������
#define PREPAID_MONEY_LEFT1      0x07 //�����޶�1
#define PREPAID_MONEY_LEFT2      0x08 //�����޶�2
#define PREPAID_MONEY_ZERO       0x09 //����0
#define PREPAID_MONEY_OVERDRAFT  0x0A //͸֧

#define PREPAID_MONEY_SWITCH_LIMIT 0x0B //���������բ����

//�ϵ��־
typedef struct
{
    INT8U Flag[10];
    INT8U CS[CS_BYTES];
}S_Power_On_Flag;

//������Ϣ״̬��
typedef struct
{
    INT8U ErrFlag;
    INT8U CS[CS_BYTES];
}S_Err_Info;


typedef struct
{
  INT32U Left_Energy; //ʣ�����,��λ0.001kwh
  INT32U Overdraft_Energy; //͸֧����,��λ0.001kwh  
  INT32U Total_Prepaid_Energy_Counts; //�ܹ������  
  INT32U Total_Prepaid_Energy; //�ܹ������,��λ0.01kwh

  INT32U Left_Money; //ʣ����,��λ0.001Ԫ
  INT32U Overdraft_Money;  //͸֧���,��λ0.001Ԫ
  INT32U Total_Prepaid_Money_Counts; //�ܹ������
  INT32U Total_Prepaid_Money;  //�ܹ�����,��λ0.001Ԫ

  INT32U Temp_Cumu_Energy;
  INT32U Temp_Cumu_Money; //������ʱ�ۼ�,3λ����*4λ��� =0.0000001Ԫ
 
  INT32U Month_Pos_Act; //��ǰ�������������й����� ��λ0.001kwh 
  INT32U Month_Neg_Act; //��ǰ�������ڷ����й�
  
  INT32U Last_Month_Pos_Act; //��һ�������ڵ������й�
  INT32U Last_Month_Neg_Act; //��һ�������ڵķ����й�
  
  S_HEX_Time Time;//ǰһ���µ�������ʱ�䣬һ��������������һ��
  
  //INT8U Clr_Alarm_Flag:1;  //�ֶ����������־,0��ʾû���ֶ������1��ʾ�ֶ����
  //INT8U Card_Switch_On_Flag :1; //�忨��բ��־������բ�����δ��͸֧��������²忨��բ��־
  //INT8U Buy_Money_Switch_Limit_Flag :1; //��ֵ�Ƿ���ں�բ���ޱ�־��1��ʾ���ڣ����ܺ�բ��0��ʾ����
  //INT8U Hand_Switch_On_Flag:4; //1��ʾ��Ҫ�ֶ���բ��0��ʾ�Ѿ��ֶ���բ, �ñ�־��ΪNEED_HAND_SWITCH_ON_FLAG��ʾ��Ҫ�ֶ���բ
                               //0��ʾ�Ѿ��ֶ���բ

  INT8U Eng_Money_Status;  //��ǰ�����ߵ�����״̬
  
  ////////////////////���ں󸶷�///////////////////
  INT32U All_Money; //���õ��� ��λ0.001
  INT32U Month_Money; //�����õ���, ��λ0.001
  
  INT8U CS[CS_BYTES];
}S_Prepaid_Info;


typedef struct
{
  INT8U Head;
  
  INT32U Energy;  //���˹������
  INT32U Money;   //���˹�����
  
  INT32U Bef_Left_Energy; //���˹���ǰʣ�����
  INT32U Bef_Left_Money;  //���˹���ǰʣ����
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Cur_Prepaid; //���˹�����Ϣ

//�����ṹ��
typedef struct
{
    INT8U Head;

    //INT8U Time[5];//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��
    S_HEX_Time Time;//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��

    INT8U Temp;//��֤�����Time����


    //INT32U Month_Pos_Act; //��ǰ�������������й���
    //INT32U Month_Neg_Act; //��ǰ�������ڷ����й���
    
    INT32U Pos_Active[MAX_RATES + 1];//���Լ��ַ��������й�,��λС��,��λKWh����ͬ
    INT32U Neg_Active[MAX_RATES + 1];//���Լ��ַ��ʷ����й�
    
    INT32U Quad_Reactive[4][MAX_RATES + 1];//�����޷ַ����޹�
    
    INT32U Pos_Apparent[MAX_RATES + 1]; //��������
    INT32U Neg_Apparent[MAX_RATES + 1]; //��������
    
    INT32U Phase_Pos_Active[3];//���������й�
    INT32U Phase_Neg_Active[3];//���෴���й�
    
    INT32U Phase_Quad_Reactive[3][4];//�����������޹�

    INT32U Phase_Pos_Apparent[3]; //��������
    INT32U Phase_Neg_Apparent[3]; //��������
    
    INT32U Phase_AH[4];//��ABC��ʱ

    INT32U CopperLoss[4];//��ABCͭ��
    INT32U IronLoss[4];  //��ABC����
    INT32U TransErr[4];  //��ABC���������

    //INT32U  Phase_Reactive[3][4];//������������޹�
    S_Prepaid_Info Prepaid_Info; //Ԥ������Ϣ
      
    INT32U Data_Ready_Flag;

    INT8U CS[CS_BYTES];//����Ĳ���Ҫ���浽Flash��

    //���²����Ǹ�������������ã�����Ҫ���浽Flash��EERom��
    //INT32U Pos_Reactive[MAX_RATES+1];//���Լ��ַ��������޹�
    //INT32U Neg_Reactive[MAX_RATES+1];
    INT8U Tail;
}S_Energy;

DATA_PACKED_BEGIN
//������״̬��
typedef struct
{
  INT8U Head;
  
  INT8U Status;
  INT8U CS[CS_BYTES];

  INT8U Tail;  
}S_WeekRest_Status;

//��������ز���
typedef struct
{
  INT8U Head;
  
  INT8U Year_Period; //��ʱ����
  INT8U Date_Table;  //��ʱ�α���
  INT8U Date_Period; //��ʱ����
  INT8U Rates;  //������
  INT8U Holidays; //����������
  INT8U Holidays_1; //������������λ������

  INT8U Harmonic; //г������

  //ע�⣺һ������������˳���ܱ任
  INT8U WeekRest_DataTable;//������ʹ�õ�ʱ�α��
  INT8U WeekRest_Status;  //������������

  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Multi_Rate_Para;//�����ʲ���

//��ʱ����
typedef struct
{
  INT8U Head;
  
  /*"��ʱ���ṹ��"*/
  INT8U MDN[MAX_YEAR_PERIODS][3];
  INT8U CS[CS_BYTES];
    
  INT8U Tail;  
}S_Year_Table;
//��ʱ�α�
typedef struct
{
  INT8U Head;
  /*"��ʱ�α�ṹ��"*/
  INT8U HMN[MAX_DATE_PERIODS][3];

  //INT8U Year_Scheme;//��ǰ�׷��ʷ���
  //INT8U Index;//��ǰʱ�α�������
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Date_Table;

typedef struct
{
  INT8U Index;
  INT8U CS[CS_BYTES];
}S_Cur_Date_Table;
//-------------300 byte-----------------------
//�ڼ��սṹ��
typedef struct
{
  INT8U Head;
  /*"�ڼ��սṹ��"*/
  //INT8U WeekRest_DataTable;//�ڼ��ղ��õ���ʱ�α�� 
  INT8U MDN[MAX_YEAR_HOLIDAYS][3];
  INT8U CS[CS_BYTES];
  INT8U Tail; 
}S_Holiday_Table;

//����������ز���
typedef struct
{
  INT8U Head;
  
  INT8U Mode;//��������ģʽ��

  INT8U Start_Time[4];//��¼����ʼʱ��
  INT8U Rec_Period[6][2];//6�����ݵļ�¼����
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Load_Data_Para;
//�޹�ģʽ��
typedef struct
{
  INT8U Head;
  
  INT8U Mode[2];
  INT8U CS[CS_BYTES];

  INT8U Tail;
}S_Reactive_Com_Mode;

//��ǰģʽ��
typedef struct
{
  INT8U Head;
  
  U_Byte_Bit Mode[5];
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Mode_Word;

/*
//�Զ������ղ���,DDHH[0]��ʾСʱ,DDHH[1]��ʾ��
typedef struct
{
    INT8U DDHH[2];
    INT8U CS[CS_BYTES];
}S_Data_Freeze_Time;
*/
//��ǰ���������Ϣ����Ҫ���ڴ�ӡ���
typedef struct
{
  INT8U Head;
  
  INT8U Year_Scheme;//��ǰʹ�õ��׷��ʷ���
  INT8U Date_Scheme;//��ʱ�α���
  INT8U Rate_Scheme; //��ǰ���ʷ���
  INT8U Step_Scheme; //��ǰ���ݷ���
  INT8U Step_No;     //��ǰ���ݺ�

  INT8U Date_Flag;//HOLIDAY,WeekRest,NORMAL_DAY

  INT8U Holiday_Index; //�ڶ��ٸ�����
  INT8U Year_Period;  //��ʱ����

  INT8U Date_Table;//��ʱ�α��
  INT8U Date_Period; //��ʱ�κ�
  INT8U Rate; //��ǰ����
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;  
}S_Cur_Rate_Info;


DATA_PACKED_END

typedef struct
{
    INT8U Flag;
    INT8U CS[CS_BYTES];
}S_Flag;

//����4�ֽڣ���ʽ���岻Ҫ�޸�
typedef struct
{
  INT8U Head;
  
  INT8U Year_Scheme; //��ǰ��ʱ������--���˳�򲻶���������
  INT8U Date_Scheme; //��ǰ��ʱ�η���
  INT8U Rate_Scheme; //��ǰ���ʷ���
  INT8U Step_Scheme; //���ݷ���
  
  INT8U Year_Scheme_Time; //��ǰ��ʱ����BEF_SWITCH_TIME��ʾ�л�ʱ����ǰ��AFT_SWITCH_TIME��ʾ�л�ʱ���Ժ�
  INT8U Date_Scheme_Time; //��ǰ��ʱ�Σ�BEF_SWITCH_TIME��ʾ�л�ʱ����ǰ��AFT_SWITCH_TIME��ʾ�л�ʱ���Ժ�
  INT8U Rate_Scheme_Time; //��ǰ���ʷ�����BEF_SWITCH_TIME��ʾ�л�ʱ����ǰ��AFT_SWITCH_TIME��ʾ�л�ʱ���Ժ�
  INT8U Step_Scheme_Time; //���ݵ�۷��� 
    
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Cur_Scheme;

//��ʱ��Ѳ���
typedef struct
{
  INT8U Head;
  
  INT32U Fee[MAX_RATES]; 
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Rate_Scheme_Para;

typedef struct
{
  INT8U Head;
  
  //INT8U Step_Num;
  
  INT32U Step_Energy[PREPAID_MAX_STEP]; //���ݵ���, Step_Energy[0]�̶�Ϊ0
  INT32U Step_Fee[PREPAID_MAX_STEP + 1];
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Step_Scheme_Para;

//----------�ṹ��������˳��Ҫ�޸�-------------!!!
typedef struct
{
  INT8U Head;
  
  INT32U Warn_Energy1; //��������1
  INT32U Warn_Energy2; //��������2
  
  INT32U Hoard_Energy_Limit; //�ڻ�������ֵ
  INT32U Overdraft_Energy_Limit; //͸֧������ֵ
  
  INT32U Warn_Money1; //�������1
  INT32U Warn_Money2; //�������2

  INT32U Overdraft_Money_Limit; //͸֧�����ֵ  
  INT32U Hoard_Money_Limit; //�ڻ������ֵ 
  INT32U Switch_On_Money_Limit; //��բ��������ֵ 
    
  INT32U CT_Ratio; //�������������
  INT32U PT_Ratio; //��ѹ���������
  
  INT8U Step_Num; //�ݶ���
  
  U_Byte_Bit Mode[3]; //Ԥ����ģʽ��

  //INT32U Power_Puls; //����������
  //INT8U Power_Mins;  //��󸺺ɼ���ʱ��
  //INT8U Relay_Off_Counts_Limit; //��������բ��������
  
  INT8U CS[CS_BYTES];
  
  INT8U Tail;
}S_Prepaid_Para;

EXT volatile INT8U Rst_Flag;

//EXT S_Err_Info Err_Info;  //������Ϣ״̬��

EXT NO_INIT volatile S_Power_On_Flag Power_On_Flag;   //�ϵ��λ��־

EXT volatile S_Mode_Word Mode_Word;    //��ǰ�޹�ģʽ��

EXT volatile _S_HEX_Time _Year_Scheme_Switch_Time;   //��ʱ�������л�ʱ��
EXT volatile _S_HEX_Time _Date_Scheme_Switch_Time; //��ʱ�α����л�ʱ��
EXT volatile _S_HEX_Time _Rate_Scheme_Switch_Time;    //���ʷ����л�ʱ��
EXT volatile _S_HEX_Time _Step_Scheme_Switch_Time;    //���ݵ�۷����л�ʱ��

#define Year_Scheme_Switch_Time _Year_Scheme_Switch_Time.Time
#define Date_Scheme_Switch_Time _Date_Scheme_Switch_Time.Time
#define Rate_Scheme_Switch_Time _Rate_Scheme_Switch_Time.Time
#define Step_Scheme_Switch_Time _Step_Scheme_Switch_Time.Time

EXT volatile S_Multi_Rate_Para Multi_Rate_Para;//��ǰ���ʷ�������
EXT volatile S_Year_Table Year_Table;      //��ǰ��ʱ����
EXT volatile S_Date_Table Date_Table;      //��ǰ��ʱ�α�
//EXT volatile S_Holiday_Table Holiday_Table;    //��ǰ�ڼ��ձ�

//EXT volatile S_Data_Freeze_Time Data_Freeze_Time;//�Զ������ղ���
//EXT volatile S_WeekRest_Status WeekRest_Status; //������״̬��

EXT volatile S_Cur_Date_Table Cur_Date_Table;//��ǰ��ʱ�α�������

EXT NO_INIT volatile S_Energy Cur_Energy;     //��ǰ�������ݽṹ��

#if USE_ENERGY_RAM_BAK > 0
EXT NO_INIT volatile S_Energy Cur_Energy_Bak;     //��ǰ�������ݽṹ��
#endif

EXT volatile S_Cur_Prepaid Cur_Prepaid;  //���ι�����Ϣ

EXT volatile S_Cur_Rate_Info Cur_Rate_Info;//��ǰ���������Ϣ,��Ҫ�ǹ�������
EXT volatile S_Int32U Energy_Cumu_Counts;
EXT volatile S_Cur_Scheme Cur_Scheme; //��ǰ��ʱ������ʱ�Ρ����ʷ���
EXT volatile S_Rate_Scheme_Para Rate_Scheme_Para; //�ַ��ʲ�����Ԥ������
EXT volatile S_Step_Scheme_Para Step_Scheme_Para; //���ݵ�۲�����Ԥ������ 
EXT volatile S_Prepaid_Para Prepaid_Para; //Ԥ���Ѳ���, Ԥ������

EXT INT8U Check_Rst_Flag();

EXT void Check_Pub_Var_Avail();
EXT void Check_Cur_Energy_Data();
//EXT INT8U Get_Using_Rate();
EXT void Read_Mode_Word();

EXT void Read_Multi_Rate_Para();
EXT void Read_Energy_Para_From_Rom();
EXT void Read_Energy_Data_From_Rom();
EXT void Read_Energy_Data_Para_For_Show();

EXT void Calc_Pos_Neg_Reactive(S_Energy* pEnergy);
EXT void Read_Date_Table_Para(INT8U Date_Scheme, INT8U Date_Table_Index);

EXT void Read_Year_Scheme_Switch_Time();
EXT void Read_Date_Scheme_Switch_Time();
EXT void Read_Rate_Scheme_Switch_Time();
EXT void Read_Step_Scheme_Switch_Time();

EXT INT8U Calc_Cur_Date_Scheme(INT8U Flag);
EXT void Year_Scheme_Changed_Proc();
EXT void Date_Scheme_Changed_Proc();
EXT void Rate_Scheme_Changed_Proc();
EXT void Step_Scheme_Changed_Proc();
EXT void Rate_Changed_Proc();
EXT INT8U Get_Cur_Rate_Info(INT8U *pDst, INT8U *pDst_Start, INT16U DstLen);
EXT INT32U Get_Pos_Act_Eng();

EXT void Read_Rate_Scheme_Para(INT8U Scheme);

EXT INT8U Check_Energy_Data(S_Energy* pEnergy);
EXT void Check_Cur_Year_Date_Scheme_Info();
EXT void Check_Energy_Para_Avil();
EXT void Check_Energy_Data_Avail();
EXT void Check_Prepaid_Para();
EXT void Check_Data_Avail();
EXT void Main_Chk_Data_Avail();
EXT void Check_Energy_Data_Para_Avail();
EXT void Check_Cur_Scheme_Info();

EXT void Debug_Print_Cur_Energy_Info();
EXT void Init_Energy_Demand_Ram_Para();
EXT void Save_Cur_Energy_Data();
EXT void Save_Cur_Energy_Bak0_Data();
EXT void Save_Cur_Energy_Bak1_Data();
EXT void Save_Cur_Energy_Bak2_Data();
EXT void Save_Cur_Energy_PD_Data();
EXT void Clear_Energy_Data();
EXT void Set_Def_Prepaid_Buy_Counts_Money();
EXT void Set_Def_Energy_Data();

EXT void Energy_Proc_Ram_Init();
EXT void Read_Para_From_Rom();

EXT void Check_Cur_Rate();
EXT void Period_Save_Cur_Data();
EXT void Cumulative_Energy();

EXT void Clear_Prepaid_Month_Eng();
EXT void PowerOn_Settle_Energy_Data();
EXT void Check_Energy_Para_Modified();

EXT void Refresh_Para_From_Rom();
EXT void Energy_Proc();
EXT void Last_Power_Down_Proc();
EXT void Check_Multi_Rate_Para();
EXT INT8U Check_Eng_Settle_Time(S_BCD_Time *pTime);
EXT void Settle_Data();

#endif
