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

#define CH_RS485_1  CHANEL_485_1//0//��һ·485
#define CH_RS485_2  CHANEL_485_2//1//�ڶ�·485
#define CH_MODULE   2//����ģ��
#define CH_IRAD   CHANEL_IRDA//3//����

#define PROG_PERIOD 10 //�������Ϊ10����

#define DATA_ADD 0
#define DATA_DEC 1

#define FOR_SRC   0x01
#define FOR_COMM  0x02
#define FOR_DISP  0x04
#define FOR_EVENT 0x08

#define AUTHORITY_FLAG 0x55aa55aa  //Ȩ�ޱ�־

//���������Ϣ״̬��
#define OTHER_ERR              0x00//��������
#define NO_REQ_DATA_ERR        0x01//����������
#define AUTH_ERR               0x02//����-Ȩ�޴�
#define MODI_BAUD_ERR          0x03//�޸�ͨ���ٶȴ�
#define YEAR_PERIOD_EXCEED_ERR 0x04//��ʱ������
#define DATE_PERIOD_EXCEED_ERR 0x05//��ʱ������
#define RATE_EXCEED_ERR        0x06//��������

#define CLEAR_ALL_FLAG     0x05AA5ABC//�����־
#define CLEAR_ENERGY_FLAG  0x0055AABB//�������־ 
#define CLEAR_DEMAND_FLAG  0xAABBCCDD//��������־
#define CLEAR_VOLSTAT_FLAG 0x11223344//���ѹͳ�Ʊ�־
#define CLEAR_EVENT_FLAG   0x33445566//���¼���־
#define CLEAR_END_FLAG     0x00000000//�����������־



//�����Լ����
#define PROTOCOL_DLT645 0 

typedef struct
{
    INT8U Energy_Digs;
    INT8U Power_Digs;
    INT8U CS[CS_BYTES];
}S_Disp_Digs;//���幦�ʺ͵��ܵ���ʾλ��

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
    INT32U Flag; //�����־
    
    INT8U Result; //������ 
    
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_Clear_Flag;

//����Դ���ݴ洢����
#define S_RAM 0x00
#define S_ROM 0x01

///����Դ��������,ͨ��645������ʱ���ɸ���һ�������ж�,S_BCD���͵�����Ҫ��һ����BCD������
//�������BCD���ͼ��
#define S_INTS 0x00//�Ƿ��з���INT����
#define S_INTU 0x01//�Ƿ��޷���INT����
#define S_BCD  0x02//�Ƿ�ΪBCD����,���������Դ����->Ŀ������������и�ʽת��
#define S_BIN  0x03//������״̬��֮���

//����Դ���ݳ��� 
#define S_LEN8 0x08
#define S_LEN7 0x07
#define S_LEN6 0x06
#define S_LEN5 0x05
#define S_LEN4 0x04
#define S_LEN3 0x03
#define S_LEN2 0x02
#define S_LEN1 0x01

//����Ŀ��������ȡ��ʱ����ʼ�ֽ�
#define D_START4 0x04
#define D_START3 0x03
#define D_START2 0x02
#define D_START1 0x01
#define D_START0 0x00

//����Ŀ�����ݵĳ���
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

//���嵱ǰͨ��ͨ��
#ifdef DATA_TRANS_C
EXT S_Cur_Comm_Ch Cur_Comm_Ch = {CHK_BYTE, 0, CHK_BYTE};
//EXT S_Int32U Prog_Event_Flag = {CHK_BYTE, 0, CHK_BYTE};
#endif
extern S_Cur_Comm_Ch Cur_Comm_Ch;
//extern S_Int32U Prog_Event_Flag; //����¼���¼


typedef struct
{
    PROTO_DI PDI;   //645Э���ID,��IDҲ�Ǵ洢ID
    //PROTO_DI PDI_Equ;//����DI��ȫ��Ч�ı�ʾ������������Э���ڱ�׼645Э���Ӧ

    INT8U DI_Set_Flag : 1;//DI�������Ƿ�������ݼ���
    //INT8U DI_Equ_Set_Flag:1;//DI_Equ�Ƿ�������ݼ���?

    INT8U PSW_Flag : 4;    //�޸ĵ�����ȼ�

    INT8U Storage : 2;    //Դ�洢����,S_ROM����S_RAM
    //INT16U Storage_DI;  //����洢��Rom�У�Storage_DI��ʾ�洢�ı��

    volatile void* pSrc; //����Դ���ݵ�ָ��
    INT16U Src_Off;    //��pSrc��ȡԴ���ݵ�ƫ��

    INT8U Src_Len;    //Դ���ݳ���,��Դ����ΪS_INTU��S_INTSʱ�ɸ��ݸó��ȵ�֪���ݾ������� 
    INT8U Src_Format;     //Դ���ݵĸ�ʽ

    INT8U Dst_Start;  //Ŀ��������Դ���ݵ�BCD������ȡ���ݵ���ʼλ��,���Դ
    //������S_INTU��������,��Ŀ�����ݵ�Ӧ����Դ����/Dst_Start��ת��ΪBCD��
    INT8U Dst_Len;    //Ŀ�����ݵ���ȡ����,�����S_BCD����,��ֱ�Ӵ�Դ���ݵ�Dst_Start�ֽڴ���ʼȡ��

    PROTO_DI Num;     //����������Ƶ����������

    INT8U Spec_Flag;  //�Ƿ��������������� Num��������Ϊ�������һ������
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
//EXT volatile S_Operator_ID Operator_ID; //������ID
//EXT volatile S_Prog_Record Prog_Record;  //���10�����ID

////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////
#define SPEC_NO   0x00 //����������

//����������
#define SPEC_ENERGY   0x41 //����
#define SPEC_DEMAND   0x42 //��������
#define SPEC_C_EVENT  0x43 //�ۼ��¼�
#define SPEC_S_EVENT  0x44 //�ִ��¼�
#define SPEC_VOLSTAT  0x45 //��ѹͳ������
#define SPEC_FREEZE   0x46 //��������

#define SPEC_FAC_INFO 0x47 //������Ϣ
#define SPEC_LOAD     0x48 //��������
#define SPEC_RATE_INFO 0x49 //������Ϣ
#define SPEC_PSW       0x4A //������Ϣ
#define SPEC_RD_ROM    0x4B //���ڿ�����
//#define SPEC_MODULE     0x0E //ģ��ͨ��
//#define SPEC_SET_ENG  0x0F //���ó�ʼ����
#define SPEC_PREPAID_ENERGY 0x4C //Ԥ������ص��� 
#define SPEC_PREPAID_EVENT 0x4D //Ԥ�����¼���¼�����⴦��
#define SPEC_EXTEND   0x4E //��չ����

//д��������
#define SPEC_METER_ID   0x81 //���ñ��
#define SPEC_SET_ENG  0x82 //���ó�ʼ����
//#define SPEC_ADJ_CLR  0x83 //У����0
#define SPEC_MODULE   0x83 //ģ��ͨ��
#define SPEC_ADJ      0x84 //У��
#define SPEC_METER_SPEC 0x85 //�����
//����д������
#define SPEC_TIME     0xC1 //ʱ�������

//------------------������չ��ͨ��DI--------------------//
#define _PDI_CUR_TIME      0x80000000   //��ǰʱ�䣬6�ֽڣ�������
#define _PDI_ALL_LOSS_VOL_CUR  0x80000001 //ȫʧѹ����ʱ����
#define _PDI_VOLT_MAX_UNBALANCE   0x80000002 //����ѹ��ƽ����
#define _PDI_CURR_MAX_UNBALANCE   0x80000003 //��������ƽ����
#define _PDI_CUR_TIME0     0x80000004 //��ǰʱ�䣬5�ֽڣ�û����
#define _PDI_PD_TIME       0x80000005 //ǰ�ε���ʱ��
#define _PDI_PO_TIME       0x80000006 //�����ϵ�ʱ��
#define _PDI_PROG_TIME     0x80000007 //���ʱ��
#define _PDI_SET_METER_SPEC 0x80000008 //�����

#define _PDI_POS_ACTIVE_DEMAND  0x80000010 //���������ڼ�����й�������ʱ��
#define _PDI_NEG_ACTIVE_DEMAND  0x80000011
#define _PDI_QUAD1_REACT_DEMAND 0x80000012
#define _PDI_QUAD2_REACT_DEMAND 0x80000013
#define _PDI_QUAD3_REACT_DEMAND 0x80000014
#define _PDI_QUAD4_REACT_DEMAND 0x80000015

#define _PDI_POS_ACTIVE_DEMAND_TIME  0x80000016 //���������ڼ�����й�������ʱ��
#define _PDI_NEG_ACTIVE_DEMAND_TIME  0x80000017
#define _PDI_QUAD1_REACT_DEMAND_TIME 0x80000018
#define _PDI_QUAD2_REACT_DEMAND_TIME 0x80000019
#define _PDI_QUAD3_REACT_DEMAND_TIME 0x8000001A
#define _PDI_QUAD4_REACT_DEMAND_TIME 0x8000001B

#define _PDI_OPERATOR_ID  0x80000020  //��ǰ������ID
#define _PDI_PROG_OP_ID   0x80000021  //һ�α�̼�¼�Ĳ�����ID
#define _PDI_PROG_DI      0x80000022 //��̱�ʶ
#define _PDI_CLR_EVENT_DI 0x80000023 //�¼��������ݱ�ʶ��

#define _PDI_TOTAL_AH 0x80000030
#define _PDI_A_AH     0x80000031
#define _PDI_B_AH     0x80000032
#define _PDI_C_AH     0x80000033

#define _PDI_ALL_LOSS_VOL_START_TIME 0x80000040 //ȫʧѹ��ʼʱ��
#define _PDI_ALL_LOSS_VOL_END_TIME 0x80000041 //ȫʧѹ����ʱ��
//------------------------------------------
//EXT volatile S_Prog_Flag Prog_Flag;//��̱�ʶ��
////���������DI,��������ݱ�ʶ����0x01��ʼ,��������ݴ洢��ROM�У���Data_Para_Storage��Ҳ�����������//
//��������ȫ���ӵ�ǰram����ȡ������Ͷ�ȡ�洢���ݳ�ͻ
#define _PDI_REG_CKC                 0x80000042
#define _PDI_REG_CSC                 0x80000043

#define _PDI_LOW_VOL                 0x80000044
#define _PDI_CURRENT_QUADRANT        0x80000045
#define _PDI_METER_PERIPHERY         0x80000046
#define _PDI_MODULE_STATUS           0x80000047
#define _PDI_POWER_DOWN_TIME         0x80000048

#define _PDI_METER_ADDR0             0x80000050//��һ·���ַ,��METER_ADDR0һ��
#define _PDI_METER_ADDR1             0x80000051//�ڶ�·���ַ
#define _PDI_METER_ADDR2             0x80000052//����·���ַ

#define _PDI_COMM_BAUD0              0x80000053//��һ·������,��COMM_BAUD0һ��
#define _PDI_COMM_BAUD1              0x80000054//�ڶ�·������
#define _PDI_COMM_BAUD2              0x80000055//����·������

#define _PDI_METER_SOFTWARE_VERSION  0x80000060//����汾��
#define _PDI_METER_SPECIFI           0x80000081//�����

///һ��������Ϊ������������,��Ҫ�ٴ˷�Χ������������
#define _PDI_ACTIVE_DIRECT           0x80000062//�й�����
#define _PDI_REACTIVE_DIRECT         0x80000063//�޹�����

//#define _DI_ACTIVE_DIRECT          0x0122//�й����򣬰�����
//#define _DI_REACTIVE_DIRECT        0x0123//�޹����򣬰�����

//#define _PDI_REACTIVE_ALL            0x80000064//���޹�����
//#define _PDI_REACTIVE_A              0x80000065//A��B��C�����޹�����
//#define _PDI_REACTIVE_B              0x80000066
//#define _PDI_REACTIVE_C              0x80000067

//#define _PDI_CUR_TIME                0x80000043//��ǰBCDʱ�� ������ʱ��

#define _PDI_ACTIVE_DEMAND           0x80000068//�й�����
#define _PDI_REACTIVE_DEMAND         0x80000069//�޹�����

//#define _PDI_TOTAL_AH                0x80000043//��AH,��λС��
//#define _PDI_A_AH                    0x80000043//A����AH
//#define _PDI_B_AH                    0x80000043//B����AH
//#define _PDI_C_AH                    0x80000043//C����AH

//#define DI_TOTAL_AH                0x0151//��AH
//#define DI_A_AH                    0x0152//A����AH
//#define DI_B_AH                    0x0153//B����AH
//#define DI_C_AH                    0x0154//C����AH

#define _PDI_A_VOL                   0x80000070//A���ѹ,2λС��,3�ֽ�
#define _PDI_B_VOL                   0x80000071//B���ѹ,2λС��
#define _PDI_C_VOL                   0x80000072//C���ѹ,2λС��

#define _PDI_A_CUR                   0x80000073//A�����,4λС��,4�ֽ�
#define _PDI_B_CUR                   0x80000074//B�����,4λС��
#define _PDI_C_CUR                   0x80000075//C�����,4λС��

#define _PDI_A_ANGLE                 0x80000076//A�����,2λС��,3�ֽ�
#define _PDI_B_ANGLE                 0x80000077//B�����,2λС��,3�ֽ�
#define _PDI_C_ANGLE                 0x80000078//C�����,2λС��,3�ֽ�
#define _PDI_SUM_ANGLE               0x80000079//�����,2λС��,3�ֽ�

//#define _PDI_PROG_FLAG0              0x80000043//��̱�ʶ��1
//#define _PDI_PROG_FLAG1              0x80000043//��̱�ʶ��2

#define _PDI_ERR_TIME                0x80000080//�����ʱ������
#define _PDI_ERR_ROM                 0x80000081//EEROM�����ʶ��

#define _PDI_CUR_DEMAND              0x80000082//��ǰ����

#define _PDI_TOTAL_PREPAID_ENERGY_COUNTS 0x80000083//�ۼƹ������
#define _PDI_TOTAL_PREPAID_ENERGY        0x80000084//�ۼƹ�����
#define _PDI_CUR_PREPAID_ENERGY          0x80000085//���˹������
#define _PDI_CUR_PREPAID_BEF_ENERGY      0x80000086//��ǰ����ǰ�ܵ���


#define _PDI_TOTAL_PREPAID_MONEY_COUNTS  0x80000087//�ۼƹ������
#define _PDI_TOTAL_PREPAID_MONEY         0x80000088//�ۼƹ�����
#define _PDI_CUR_PREPAID_MONEY           0x80000089//���˹�����
#define _PDI_CUR_PREPAID_BEF_MONEY       0x8000008A//���ι���ǰ�ܽ��

//#define _PDI_CLR_DEMAND_WAY          0x80000043//��������ʽ
//#define _PDI_ADJ_FLAG                0x80000043//У���ʶ��

#define _PDI_ADJ_BEF_TIME            0x800000A0//Уʱǰʱ��
#define _PDI_ADJ_AFT_TIME            0x800000A1//Уʱ��ʱ��

#define _PDI_RTC_ERR_TIME           0x800000A2 //Ӳ������ʱ��

#define _PDI_NULL_1BYTE              0x800000EE//������ı�ʶ�� 

///У����ز���
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
#define _PDI_ADJ_INSTANT_DATA            0x10000211            //У��˲ʱ�����ݴ���
//---------------------------------------------------------------------

//#define _PDI_EVENT_VOL               0x80000043//��ѹ���޻��߹�ѹʱ�ĵ�ѹֵ

//#define _PDI_ALL_LOSS_VOL_START_TIME 0x80000043//ȫʧѹ��ʼʱ��
//#define _PDI_ALL_LOSS_VOL_END_TIME   0x80000043//ȫʧѹ����ʱ��

//#define _PDI_EVENT_TIME              0x80000043//�¼�����ʱ��

//#define _PDI_A_VOL_1                 0x80000084//A���ѹ,1λС��,3�ֽ�
//#define _PDI_B_VOL_1                 0x80000085//B���ѹ,1λС��
//#define _PDI_C_VOL_1                 0x80000086//C���ѹ,1λС��

//#define _PDI_A_CUR_3                 0x80000087//A�����,3λС��,3�ֽ�
//#define _PDI_B_CUR_3                 0x80000088//B�����,3λС��
//#define _PDI_C_CUR_3                 0x80000089//C�����,3λС��

//#define _PDI_BROAD_ADJ_TIME          0x80000043 //����㲥УʱDI,Э�鴫������ʱδ��


//#define _PDI_EXTNED_START            0x80000043//�����DI����ʼ
//--------------------------------------------------------------//

////////////////////������ͨ�ż��ݵĴ洢DI///////////////
#define PDI_DEMAND_PERIOD      0x04000103 //��������
#define PDI_DEMAND_SLID    0x04000104 //����ʱ��
#define PDI_ADJ_PULSE_WIDTH    0x04000105 //У��������
#define PDI_YEAR_SCHE_CHG_TIME   0x04000106 //��ʱ���л�ʱ��
#define PDI_DATE_SCHE_CHG_TIME   0x04000107 //��ʱ�α��л�ʱ��

#define PDI_YEAR_PERIOD_NUM    0x04000201 //��ʱ����
#define PDI_DATE_TABLE_NUM     0x04000202 //��ʱ�α���
#define PDI_DATE_PERIOD_NUM    0x04000203 //��ʱ����
#define PDI_RATE_NUM   0x04000204 //������
#define PDI_HOLIDAY_NUM    0x04000205 //�����ڼ�����
#define PDI_HARMONIC_NUM   0x04000206 //г������

#define PDI_AUTO_CYCL_SCREEN_NUM 0x04000301 //�Զ�ѭ����ʾ����
#define PDI_SCREEN_SHOW_TIME   0x04000302 //û����ʾʱ��
#define PDI_ENERGY_DECIMAL_NUM   0x04000303 //��ʾ����С��λ��
#define PDI_POWER_DECIMAL_NUM    0x04000304 //��ʾ����������С��λ��
#define PDI_KEY_CYCL_SCREEN_NUM  0x04000305 //����ѭ����ʾ����

#define PDI_COMM_ADDR      0x04000401 //ͨ�ŵ�ַ
#define PDI_METER_ID   0x04000402 //���
#define PDI_ASSET_ID   0x04000403 //�ʲ��������
#define PDI_RATED_VOL      0x04000404 //���ѹ
#define PDI_RATED_CUR      0x04000405 //�����
#define PDI_MAX_CUR    0x04000406 //������
#define PDI_ACTIVE_ACCU    0x04000407 //�й�׼ȷ�ȼ�
#define PDI_REACTIVE_ACCU      0x04000408 //�޹�׼ȷ�ȼ�
#define PDI_ACTIVE_CONST   0x04000409 //����й�����
#define PDI_REACTIVE_CONST     0x0400040A //����޹�����
#define PDI_METER_TYPE     0x0400040B //����ͺ�
#define PDI_METER_MADE_TIME    0x0400040C //�����������
#define PDI_PROTOCOL_VER   0x0400040D //���Э��汾��

#define PDI_ACTIVE_PORT_WORD   0x04000601 //�й���Ϸ�ʽ������
#define PDI_REACTIVE_PORT_WORD_1 0x04000602 //�޹���Ϸ�ʽ������1
#define PDI_REACTIVE_PORT_WORD_2 0x04000603 //�޹���Ϸ�ʽ������2

#define PDI_FAR_IRAD_BAUD      0x04000701 //���ƺ���Զ�����ٶ�������
#define PDI_NEAR_IRAD_BAUD     0x04000702 //�Ӵ�����������ٶ�������
#define PDI_COMM1_BAUD     0x04000703 //ͨ�ſ�1�ٶ�
#define PDI_COMM2_BAUD     0x04000704 //ͨ�ſ�2�ٶ�
#define PDI_COMM3_BAUD     0x04000705 //ͨ�ſ�3�ٶ�

#define PDI_WEEK_REST_DAY      0x04000801 //������������
#define PDI_WEEK_REST_DATE_TABLE 0x04000802 //��������ʱ�α��

#define PDI_LOAD_REC_WORD      0x04000901 //���ɼ�¼ģʽ��
#define PDI_FREEZE_REC_WORD    0x04000902 //�����¼ģʽ��

#define PDI_LOAD_REC_START_TIME  0x04000A01 //���ɼ�¼��ʼʱ��
#define PDI_LOAD_REC1_INTER_TIME 0x04000A02 //��һ�ฺ�ɼ�¼���ʱ��
#define PDI_LOAD_REC2_INTER_TIME 0x04000A03 //�ڶ��ฺ�ɼ�¼���ʱ��
#define PDI_LOAD_REC3_INTER_TIME 0x04000A04 //�����ฺ�ɼ�¼���ʱ��
#define PDI_LOAD_REC4_INTER_TIME 0x04000A05 //�����ฺ�ɼ�¼���ʱ��
#define PDI_LOAD_REC5_INTER_TIME 0x04000A06 //�����ฺ�ɼ�¼���ʱ��
#define PDI_LOAD_REC6_INTER_TIME 0x04000A07 //�����ฺ�ɼ�¼���ʱ��

#define PDI_MONTH_SETTLE_DAY1    0x04000B01 //ÿ�µ�һ������
#define PDI_MONTH_SETTLE_DAY2    0x04000B02 //ÿ�µڶ�������   
#define PDI_MONTH_SETTLE_DAY3    0x04000B03 //ÿ�µ���������

#define PDI_PSW0     0x04000C01 //��0������
#define PDI_PSW1     0x04000C02 //��1������
#define PDI_PSW2     0x04000C03 //��2������
#define PDI_PSW3     0x04000C04 //��3������
#define PDI_PSW4     0x04000C05 //��4������
#define PDI_PSW5     0x04000C06 //��5������
#define PDI_PSW6     0x04000C07 //��6������
#define PDI_PSW7     0x04000C08 //��7������
#define PDI_PSW8     0x04000C09 //��8������
#define PDI_PSW9     0x04000C0A //��9������

#define PDI_PHASE_A_CONDUC     0x04000D01 //A��絼��
#define PDI_PHASE_A_SUSCEP     0x04000D02 //A�������
#define PDI_PHASE_A_RESIST     0x04000D03 //A�������
#define PDI_PHASE_B_CONDUC     0x04000D04 //B��絼��
#define PDI_PHASE_B_SUSCEP     0x04000D05 //B�������
#define PDI_PHASE_B_RESIST     0x04000D06 //B�������
#define PDI_PHASE_C_CONDUC     0x04000D07 //C��絼��
#define PDI_PHASE_C_SUSCEP     0x04000D08 //C�������
#define PDI_PHASE_C_RESIST     0x04000D09 //C�������

#define PDI_POS_ACTIVE_UP_LIMIT  0x04000E01 //�����й���������
#define PDI_NEG_ACTIVE_LOW_LIMIT 0x04000E02 //�����й���������
#define PDI_VOL_UP_LIMIT   0x04000E03 //��ѹ����ֵ
#define PDI_VOL_LOW_LIMIT      0x04000E04 //��ѹ����

#define PDI_SCHE1_YEAR_TABLE   0x04010000 //��һ��ʱ����
#define PDI_SCHE1_DATE_TABLE1    0x04010001 //��һ�׵�һ��ʱ�α�
#define PDI_SCHE1_DATE_TABLE2    0x04010002 //��һ��ʱ����ʱ�α�
#define PDI_SCHE1_DATE_TABLE3    0x04010003 //��һ��ʱ����ʱ�α�
#define PDI_SCHE1_DATE_TABLE4    0x04010004 //��һ��ʱ����ʱ�α�
#define PDI_SCHE1_DATE_TABLE5    0x04010005 //��һ��ʱ����ʱ�α�
#define PDI_SCHE1_DATE_TABLE6    0x04010006 //��һ��ʱ����ʱ�α�
#define PDI_SCHE1_DATE_TABLE7    0x04010007 //��һ��ʱ����ʱ�α�
#define PDI_SCHE1_DATE_TABLE8    0x04010008 //��һ��ʱ����ʱ�α�

#define PDI_SCHE2_YEAR_TABLE   0x04020000 //�ڶ���ʱ����
#define PDI_SCHE2_DATE_TABLE1    0x04020001 //�ڶ��׵�һ��ʱ�α�
#define PDI_SCHE2_DATE_TABLE2    0x04020002 //�ڶ���ʱ����ʱ�α�
#define PDI_SCHE2_DATE_TABLE3    0x04020003 //�ڶ���ʱ����ʱ�α�
#define PDI_SCHE2_DATE_TABLE4    0x04020004 //�ڶ���ʱ����ʱ�α�
#define PDI_SCHE2_DATE_TABLE5    0x04020005 //�ڶ���ʱ����ʱ�α�
#define PDI_SCHE2_DATE_TABLE6    0x04020006 //�ڶ���ʱ����ʱ�α�
#define PDI_SCHE2_DATE_TABLE7    0x04020007 //�ڶ���ʱ����ʱ�α�
#define PDI_SCHE2_DATE_TABLE8    0x04020008 //�ڶ���ʱ����ʱ�α�

#define PDI_HOLIDAY_DATE_TABLE   0x04030001 //�����ڼ��ռ���ʱ�α��
#define PDI_AUTO_CYCL_SREEN_DATA 0x04040101 //�Զ�ѭ����ʾ����
#define PDI_KEY_CYCL_SREEN_DATA  0x04040201 //����ѭ����ʾ����


#define PDI_CUR_RATE_SCHEME         0x0E010000//��ǰ��ʱ������
#define PDI_CUR_YEAR_PERIOD         0x0E010001//��ǰ��ʱ����
#define PDI_CUR_DATE_TABLE_SCHEME   0x0E010002 //��ǰ��ʱ�α���
#define PDI_CUR_DATE_TABLE          0x0E010003 //��ǰ��ʱ�α��
#define PDI_CUR_DATE_PERIOD         0x0E010004 //��ǰ��ʱ�κ�
#define PDI_CUR_RATE                0x0E010005 //��ǰ����

#define PDI_CUR_POS_ACTIVE_DEMAND   0x0E010301 //��ǰ�����й�����
#define PDI_CUR_NEG_ACTIVE_DEMAND   0x0E010302 //��ǰ�����й�����
#define PDI_CUR_COMB1_REAC_DEMAND   0x0E010303 //��ǰ����޹�1����
#define PDI_CUR_COMB2_REAC_DEMAND   0x0E010304 //��ǰ����޹�2����
#define PDI_CUR_QUAD1_REAC_DEMAND   0x0E010305 //��ǰһ�����޹�����
#define PDI_CUR_QUAD2_REAC_DEMAND   0x0E010306 //��ǰ�������޹�����
#define PDI_CUR_QUAD3_REAC_DEMAND   0x0E010307 //��ǰ�������޹�����
#define PDI_CUR_QUAD4_REAC_DEMAND   0x0E010308 //��ǰ�������޹�����

#define PDI_CUR_RATE1_FEE  0x0E020001  //��ǰ���ʵ��
#define PDI_CUR_RATE2_FEE  0x0E020002
#define PDI_CUR_RATE3_FEE  0x0E020003
#define PDI_CUR_RATE4_FEE  0x0E020004

#define PDI_CUR_STEP1_ENG    0x0E020101  //��ǰ����1����
#define PDI_CUR_STEP2_ENG    0x0E020102
#define PDI_CUR_STEP3_ENG    0x0E020103
#define PDI_CUR_STEP4_ENG    0x0E020104

#define PDI_CUR_STEP1_FEE  0x0E020201 //��ǰ����1���
#define PDI_CUR_STEP2_FEE  0x0E020202
#define PDI_CUR_STEP3_FEE  0x0E020203
#define PDI_CUR_STEP4_FEE  0x0E020204
#define PDI_CUR_STEP5_FEE  0x0E020205

typedef struct
{
    INT8U Head;

    INT8U Err_Flag;//�����־
    INT8U Tail;
}S_Sys_Run_Flag;

typedef struct
{
    PROTO_DI PDI;   //645Э���ID,��IDҲ�Ǵ洢ID
    //PROTO_DI PDI_Equ;//����DI��ȫ��Ч�ı�ʾ������������Э���ڱ�׼645Э���Ӧ

    INT8U DI_Set_Flag : 1;//DI�������Ƿ�������ݼ���
    //INT8U DI_Equ_Set_Flag:1;//DI_Equ�Ƿ�������ݼ���?

    INT8U PSW_Flag : 5;    //�޸ĵ�����ȼ�

    INT8U Storage : 2;    //Դ�洢����,S_ROM����S_RAM
    //INT16U Storage_DI;  //����洢��Rom�У�Storage_DI��ʾ�洢�ı��

    volatile void* pSrc; //����Դ���ݵ�ָ��
    //INT16U Src_Off;    //��pSrc��ȡԴ���ݵ�ƫ��

    INT8U Src_Len;    //Դ���ݳ���,��Դ����ΪS_INTU��S_INTSʱ�ɸ��ݸó��ȵ�֪���ݾ������� 
    INT8U Src_Format:3;     //Դ���ݵĸ�ʽ

    INT8U Dst_Start:5;  //Ŀ��������Դ���ݵ�BCD������ȡ���ݵ���ʼλ��,���Դ
    //������S_INTU��������,��Ŀ�����ݵ�Ӧ����Դ����/Dst_Start��ת��ΪBCD��
    INT8U Dst_Len;    //Ŀ�����ݵ���ȡ����,�����S_BCD����,��ֱ�Ӵ�Դ���ݵ�Dst_Start�ֽڴ���ʼȡ��

    PROTO_DI Num;     //����������Ƶ����������

    INT8U Spec_Flag;  //�Ƿ��������������� Num��������Ϊ�������һ������
}S_P_Data_Info;

typedef struct
{
  INT8U Head;
  
  INT8U Read_Follow_Flag;//������֡��־
  INT8U Read_Seq;
  
  //INT8U Multi_Single_Flag;//�����߶�֡��־
  INT8U Follow_Flag; //���޺���֡��־
  INT8U Frame_Seq; //ǰ��֡���к�
  
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
