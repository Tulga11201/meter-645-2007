#define DATA_PARA_C
#include "includes.h"

//#undef Debug_Print
//#define Debug_Print(...)
//#define Debug_Print _Debug_Print
/*
#define IMP_0    0x00 //��������
#define IMP_1    0x01 //��Ҫ����
#define IMP_2    0x02 //��Ҫ���ݵı���
#define IMP_3    0x03 //��ͨ����
#define IMP_4    0x04 //�¼��ۼ���Ϣ
#define IMP_5    0x05 //��0���¼�
#define IMP_6    0x06 //��1���¼�
#define IMP_5    0x07 //��2���¼�
#define IMP_8    0x08 //��Ҫ����
#define IMP_9    0x09 //��ͨ����
#define IMP_A    0x0A //���ɼ�¼
#define IMP_B    0x0B //����洢����
*/

//#define IMP_LOG_MEM 5//ÿ����Ҫ���ݴ洢���߼��洢������,���ֵ 

//����������ݵĴ洢�ֲ�
CONST S_Data_Mem_Map Data_Mem_Map[] =
{
  {IMP_FAC_PARA, {LOG_MEM0, LOG_MEM1, LOG_MEM2, LOG_MEM3, LOG_MEM4}}, //��������,5�ݴ洢
  {IMP_IMP_PARA, {LOG_MEM5, LOG_MEM6, LOG_MEM7, LOG_MEM8, LOG_MEM36}}, //��Ҫ����,5��
  //{IMP_NOR_PARA    , {LOG_MEM9, LOG_MEM10, LOG_MEM11, NULL_LOG_MEM, NULL_LOG_MEM}}, //��ͨ����,3��
  {IMP_IMP_DATA, {LOG_MEM12, LOG_MEM13, LOG_MEM14, LOG_MEM15, NULL_LOG_MEM}}, //��Ҫ����
  {IMP_IMP_BAK_DATA, {LOG_MEM16, LOG_MEM17, LOG_MEM18, NULL_LOG_MEM, NULL_LOG_MEM}}, //��Ҫ���ݵı���
  //{IMP_NOR_DATA    , {LOG_MEM19, LOG_MEM20, LOG_MEM21, NULL_LOG_MEM, NULL_LOG_MEM}}, //��ͨ����
  {IMP_HIS_DATA, {LOG_MEM22, LOG_MEM23, LOG_MEM24, NULL_LOG_MEM, NULL_LOG_MEM}}, //��ʷ����
  {IMP_EVENT_CUMU, {LOG_MEM25, LOG_MEM26, LOG_MEM27, NULL_LOG_MEM, NULL_LOG_MEM}}, //�¼��ۼ���Ϣ
  {IMP_EVENT0, {LOG_MEM28, LOG_MEM29, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //��0���¼�
  {IMP_EVENT1, {LOG_MEM30, LOG_MEM31, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //��1���¼�
  {IMP_EVENT2, {LOG_MEM32, LOG_MEM33, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //��2���¼�
  {IMP_LOAD_REC, {LOG_MEM34, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}}, //�¼���¼
  {IMP_PD_DATA, {LOG_MEM35, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM, NULL_LOG_MEM}} //��������

}; 

//���ݴ洢ӳ���
CONST S_Data_Para_Storage_Info Data_Para_Storage[] =
{
  {_SDI_BOOT_FLAG, IMP_IMP_PARA, 4, 1}, //������־�������Ƿ��ǵ�һ������
  //У����ز���,�����-----
  {_SDI_ADJ_METER_PUL_VOL_CUR_SPEC,IMP_FAC_PARA,3,1},//���塢��ѹ���������,3�ֽ�
  {_SDI_ADJ_METER_PARA_STATUS,IMP_FAC_PARA,1,1},//У�����״̬����
  {_SDI_ADJ_METER_A_POW,IMP_FAC_PARA,3,12},//ABC���๦�ʡ���λ����ѹ�������� 
  //---------------------------
  {_SDI_CUR_ENERGY_PD, IMP_PD_DATA, ENERGY_SAVE_SIZE, 1},//IMP_6,ENERGY_SAVE_SIZE,1},//��ǰ����,����洢,ƽʱҲ��ʱ�洢
  {_SDI_CUR_DEMAND_PD, IMP_PD_DATA, sizeof(S_Demand), 1},//����ֻ�����ܺ͵�ǰ������������S_Demand_
  {_SDI_CUR_VOLSTAT_PD, IMP_PD_DATA, sizeof(S_VolStat), 1},//��ǰ��ѹͳ������
  //{_SDI_TOTAL_VOLSTAT_PD, IMP_PD_DATA, sizeof(S_VolStat),1},//�ܵ�ѹ�������
  {_SDI_LOAD_DATA_INDEX_PD, IMP_PD_DATA, sizeof(S_LoadData_Index),1},//�ܵ�ѹ�������
  {_SDI_EVENT_DATA_PD, IMP_PD_DATA, sizeof(Event_Data), 1}, //����洢�¼�����
  {_SDI_SAVE_PD_DATA_TIME, IMP_PD_DATA, 4, 1},//����������̵�ʱ�䣬��λms
  //{_SDI_CUR_YEAR_DATE_SCHEME_PD, IMP_PD_DATA, sizeof(S_Cur_Year_Date_Scheme), 1},//��ǰ��ʱ������ʱ�η���
  
  {_SDI_LOAD_DATA_INDEX, IMP_IMP_DATA, sizeof(S_LoadData_Index), 1}, //���ɼ�¼��ǰ��¼λ��
  {_SDI_TIME_BAK, IMP_IMP_DATA, sizeof(S_BCD_Time), 1}, //��ǰʱ��ı���
  {_SDI_CUR_SCHEME, IMP_IMP_PARA, sizeof(S_Cur_Scheme), 1},//��ǰ��ʱ������ʱ�Ρ����ʷ���
  
  {_SDI_CUR_ENERGY, IMP_IMP_DATA, ENERGY_SAVE_SIZE, 1}, //��ǰ����  
  {_SDI_CUR_DEMAND, IMP_IMP_DATA, DEMAND_SAVE_SIZE, 1}, //��ǰ����  
  {_SDI_CUR_VOLSTAT, IMP_IMP_DATA, sizeof(S_VolStat), 1}, //��ǰ��ѹͳ��
  
  //{_SDI_TOTAL_VOLSTAT, IMP_IMP_DATA, sizeof(S_VolStat), 1}, //��ǰ�ܵ�ѹͳ��
  {_SDI_CUR_ENERGY_BAK0, IMP_IMP_BAK_DATA, ENERGY_SAVE_SIZE, 1}, //��������0
  {_SDI_CUR_DEMAND_BAK, IMP_IMP_BAK_DATA, DEMAND_SAVE_SIZE, 1},  //�������� 
  {_SDI_CUR_ENERGY_BAK1, IMP_IMP_BAK_DATA, ENERGY_SAVE_SIZE, 1},  //��������1
  {_SDI_CUR_VOLSTAT_BAK, IMP_IMP_BAK_DATA, sizeof(S_VolStat), 1}, //��ǰ��ѹͳ�Ʊ���
  {_SDI_CUR_ENERGY_BAK2, IMP_LOAD_REC, ENERGY_SAVE_SIZE, 1},  //��������2,�÷����ݴ洢������dataflash��ȥ
  
  //{_SDI_TOTAL_VOLSTAT_BAK, IMP_IMP_BAK_DATA, sizeof(S_VolStat), 1}, //��ǰ�ܵ�ѹͳ�Ʊ���
  {_SDI_LOAD_DATA_INDEX_BAK, IMP_IMP_DATA, sizeof(S_LoadData_Index), 1}, //���ɼ�¼λ�ñ���

  {_SDI_LAST_SETTLE_ENERGY_DI, IMP_IMP_PARA, 4, 1}, //��13�µ���
  {_SDI_LAST_SETTLE_DEMAND_DI, IMP_IMP_PARA, 4, 1}, //��13���������
  {_SDI_LAST_SETTLE_VOLSTAT_DI, IMP_IMP_PARA, 4, 1}, //��3���µ�ѹͳ������
  {_SDI_SETTLE_ENERGY_DATA, IMP_HIS_DATA, ENERGY_SAVE_SIZE, MAX_ENERGY_SETTLE_NUM}, //��13�µ���
  {_SDI_SETTLE_DEMAND_DATA, IMP_HIS_DATA, DEMAND_SAVE_SIZE, MAX_DEMAND_SETTLE_NUM}, //��13���������
  {_SDI_SETTLE_VOLSTAT_DATA, IMP_HIS_DATA, sizeof(S_VolStat), MAX_VOLSTAT_SETTLE_NUM}, //��3���µ�ѹͳ������
  {_SDI_LOAD_DATA_TIME_INDEX, IMP_LOAD_REC, 2, LOAD_DATA_TIME_INDEX_NUM},//��������Сʱ����
  {_SDI_LOAD_DATA_NEXT_INDEX, IMP_LOAD_REC, 2, LOAD_DATA_NUM}, //�������ݵ��������ݵ�����
  {_SDI_LOAD_DATA, IMP_LOAD_REC, LOAD_DATA_SIZE, LOAD_DATA_NUM}, //������������
  
  {_SDI_REMOTE_RELAY_STATUS, IMP_IMP_PARA, sizeof(S_Remote_Ctrl_Switch), 1},//Զ������բ״̬
  {_SDI_PREPAID_POWER_CTRL_RELAY_STATUS, IMP_IMP_PARA, sizeof(S_Pepaid_Power_Ctrl_Switch), 1},//Ԥ���Ѹ��ɿ�������բ״̬ 
  {_SDI_CTRL_STATUS_FLAG, IMP_IMP_PARA, sizeof(S_Ctrl_Status_Flag), 1}, //����״̬��һЩ��־
  
 //Ԥ��������ʱ����
  { _SDI_PREPAID_RUN_STATUS, IMP_IMP_PARA, 1, 1},// (0x0300|EXT_PARA_DATA)//����״̬ ���ݳ���Ϊ1
  { _SDI_DISCRETE_INFO, IMP_IMP_PARA, 8, 1}, //��ɢ���� ���ݳ���Ϊ8
  { _SDI_PREPAID_PARA_CARD_VER, IMP_IMP_PARA, 4, 1},// (0x0302|EXT_PARA_DATA)//�ֳ��������ÿ��汾�� ���ݳ���Ϊ4
  { _SDI_PREPAID_PSW_KIND, IMP_IMP_PARA, 1, 1}, // (0x0303|EXT_PARA_DATA)//��Կ�������ݳ���Ϊ1
  { _SDI_INVALID_CARD_COUNTS, IMP_IMP_PARA, 4, 1}, //�Ƿ����������
  { _SDI_INVALID_COUNTS_AllOW, IMP_IMP_PARA, 1, 1}, //
  { _SDI_FAR_AUTH_DAY_FOLLOW, IMP_IMP_PARA, 4, 1}, //Զ����֤������
  { _SDI_SINGLE_OR_COMPLEX_USER_KIND, IMP_IMP_PARA, 1, 1}, //�û����� 
  ///////////////////////////////////////////////////////////
  {SDI_BAT_RUN_TIME, IMP_IMP_PARA, 4, 1},  //0x0280000A  //��ع���ʱ�� 
  {SDI_DEMAND_PERIOD, IMP_IMP_PARA, 1, 1},  //0x04000103 //��������
  {SDI_DEMAND_SLID, IMP_IMP_PARA, 1, 1},  //0x04000104 //����ʱ��
  {SDI_ADJ_PULSE_WIDTH, IMP_IMP_PARA, 2, 1},     //0x04000105 //У��������
  {SDI_YEAR_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000106 //��ʱ���л�ʱ��
  {SDI_DATE_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000107 //��ʱ�α��л�ʱ��
  {SDI_RATE_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000108 //���ʷ����л�ʱ��
  {SDI_STEP_SCHE_CHG_TIME, IMP_IMP_PARA, 5, 1}, //0x04000109 //���ݷ����л�ʱ��
  {SDI_YEAR_PERIOD_NUM, IMP_IMP_PARA, 1, 1},     //0x04000201 //��ʱ����
  {SDI_DATE_TABLE_NUM, IMP_IMP_PARA, 1, 1},   //0x04000202 //��ʱ�α���
  {SDI_DATE_PERIOD_NUM, IMP_IMP_PARA, 1, 1},     //0x04000203 //��ʱ����
  {SDI_RATE_NUM, IMP_IMP_PARA, 1, 1},   //0x04000204 //������
  {SDI_HOLIDAY_NUM, IMP_IMP_PARA, 2, 1},     //0x04000205 //�����ڼ�����
  {SDI_HARMONIC_NUM, IMP_IMP_PARA, 1, 1},   //0x04000206 //г������
  {SDI_PREPAID_STEP_NUM, IMP_IMP_PARA, 1,1}, //0x04000207 //Ԥ���ѽ�����
  {SDI_AUTO_CYCL_SCREEN_NUM, IMP_IMP_PARA, 1, 1},  //0x04000301 //�Զ�ѭ����ʾ����
  {SDI_SCREEN_SHOW_TIME, IMP_IMP_PARA, 1, 1},    //0x04000302 //û����ʾʱ��
  {SDI_ENERGY_DECIMAL_NUM, IMP_IMP_PARA, 1, 1}, //0x04000303 //��ʾ����С��λ��
  {SDI_POWER_DECIMAL_NUM, IMP_IMP_PARA, 1, 1},   //0x04000304 //��ʾ����������С��λ��
  {SDI_KEY_CYCL_SCREEN_NUM, IMP_IMP_PARA, 1, 1},   //0x04000305 //����ѭ����ʾ����
  {SDI_CURR_TRANS_RATIO, IMP_IMP_PARA, 3, 1}, //0x04000306 //�������������
  {SDI_VOLT_TRANS_RATIO, IMP_IMP_PARA, 3, 1}, //0x04000307 //��ѹ���������
  
  {SDI_COMM_ADDR, IMP_IMP_PARA, 6, 1},  //0x04000401 //ͨ�ŵ�ַ
  {SDI_METER_ID, IMP_IMP_PARA, 6, 1},   //0x04000402 //���
  {SDI_ASSET_ID, IMP_IMP_PARA, 32, 1},  //0x04000403 //�ʲ��������
  {SDI_RATED_VOL, IMP_IMP_PARA, 6, 1},  //0x04000404 //���ѹ
  {SDI_RATED_CUR, IMP_IMP_PARA, 6, 1},  //0x04000405 //�����
  {SDI_MAX_CUR, IMP_IMP_PARA, 6, 1},      //0x04000406 //������
  {SDI_ACTIVE_ACCU, IMP_IMP_PARA, 4, 1},     //0x04000407 //�й�׼ȷ�ȼ�
  {SDI_REACTIVE_ACCU, IMP_IMP_PARA, 4, 1},  //0x04000408 //�޹�׼ȷ�ȼ�
  {SDI_ACTIVE_CONST, IMP_IMP_PARA, 3, 1},   //0x04000409 //����й�����
  {SDI_REACTIVE_CONST, IMP_IMP_PARA, 3, 1},   //0x0400040A //����޹�����
  {SDI_METER_TYPE, IMP_IMP_PARA, 10, 1},     //0x0400040B //����ͺ�
  {SDI_METER_MADE_TIME, IMP_IMP_PARA, 10, 1},    //0x0400040C //�����������
  {SDI_PROTOCOL_VER, IMP_IMP_PARA, 16, 1},  //0x0400040D //���Э��汾��
  {SDI_CUTOMER_ID, IMP_IMP_PARA, 6, 1}, //0x0400040E �ͻ����
  //{SDI_HARDWARE_VER, IMP_IMP_PARA, 16, 1},  //0x0400040F //Ӳ���汾��,δʹ��  
  
  {SDI_ACTIVE_COMB_WORD, IMP_IMP_PARA, 1, 1},    //0x04000601 //�й���Ϸ�ʽ������
  {SDI_REACTIVE_COMB_WORD_1, IMP_IMP_PARA, 1, 1},  //0x04000602 //�޹���Ϸ�ʽ������1
  {SDI_REACTIVE_COMB_WORD_2, IMP_IMP_PARA, 1, 1},  //0x04000603 //�޹���Ϸ�ʽ������2
  {SDI_FAR_IRAD_BAUD, IMP_IMP_PARA, 1, 1},  //0x04000701 //���ƺ���Զ�����ٶ�������
  {SDI_NEAR_IRAD_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000702 //�Ӵ�����������ٶ�������
  {SDI_COMM1_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000703 //ͨ�ſ�1�ٶ�
  {SDI_COMM2_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000704 //ͨ�ſ�2�ٶ�
  {SDI_COMM3_BAUD, IMP_IMP_PARA, 1, 1},   //0x04000705 //ͨ�ſ�3�ٶ�
  {SDI_WEEK_REST_DAY, IMP_IMP_PARA, 1, 1},  //0x04000801 //������������
  {SDI_WEEK_REST_DATE_TABLE, IMP_IMP_PARA, 1, 1},  //0x04000802 //��������ʱ�α��
  {SDI_LOAD_REC_WORD, IMP_IMP_PARA, 1, 1},  //0x04000901 //���ɼ�¼ģʽ��
  {SDI_FREEZE_REC_WORD, IMP_IMP_PARA, 1, 5},     //0x04000902 //�����¼ģʽ��
  {SDI_LOAD_REC_START_TIME, IMP_IMP_PARA, 4, 1},   //0x04000A01 //���ɼ�¼��ʼʱ��
  {SDI_LOAD_REC1_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A02 //��һ�ฺ�ɼ�¼���ʱ��
  {SDI_LOAD_REC2_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A03 //�ڶ��ฺ�ɼ�¼���ʱ��
  {SDI_LOAD_REC3_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A04 //�����ฺ�ɼ�¼���ʱ��
  {SDI_LOAD_REC4_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A05 //�����ฺ�ɼ�¼���ʱ��
  {SDI_LOAD_REC5_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A06 //�����ฺ�ɼ�¼���ʱ��
  {SDI_LOAD_REC6_INTER_TIME, IMP_IMP_PARA, 2, 1},  //0x04000A07 //�����ฺ�ɼ�¼���ʱ��
  {SDI_MONTH_SETTLE_DAY1, IMP_IMP_PARA, 2, 1},   //0x04000B01 //ÿ�µ�һ������
  {SDI_MONTH_SETTLE_DAY2, IMP_IMP_PARA, 2, 1},   //0x04000B02 //ÿ�µڶ�������   
  {SDI_MONTH_SETTLE_DAY3, IMP_IMP_PARA, 2, 1},   //0x04000B02 //ÿ�µ���������
  {SDI_PSW0, IMP_IMP_PARA, 3, 10},     //0x04000C01 //��0������
  //#define SDI_PSW1      0x04000C02 //��1������
  //#define SDI_PSW2      0x04000C03 //��2������
  //#define SDI_PSW3      0x04000C04 //��3������
  //#define SDI_PSW4      0x04000C05 //��4������
  //#define SDI_PSW5      0x04000C06 //��5������
  //#define SDI_PSW6      0x04000C07 //��6������
  //#define SDI_PSW7      0x04000C08 //��7������
  //#define SDI_PSW8      0x04000C09 //��8������
  //#define SDI_PSW9      0x04000C0A //��9������

  {SDI_PHASE_A_CONDUC, IMP_IMP_PARA, 2, 12},    //0x04000D01 //A��絼��
  //#define SDI_PHASE_A_SUSCEP   0x04000D02 //A�������
  //#define SDI_PHASE_A_RESIST   0x04000D03 //A�������
  //#define SDI_PHASE_B_CONDUC   0x04000D04 //B��絼��
  //#define SDI_PHASE_B_SUSCEP   0x04000D05 //B�������
  //#define SDI_PHASE_B_RESIST   0x04000D06 //B�������
  //#define SDI_PHASE_C_CONDUC   0x04000D07 //C��絼��
  //#define SDI_PHASE_C_SUSCEP   0x04000D08 //C�������
  //#define SDI_PHASE_C_RESIST   0x04000D09 //C�������

  {SDI_POS_ACTIVE_UP_LIMIT, IMP_IMP_PARA, 3, 1},  //0x04000E01 //�����й���������
  {SDI_NEG_ACTIVE_LOW_LIMIT, IMP_IMP_PARA, 3, 1},   //0x04000E02 //�����й���������
  {SDI_VOL_UP_LIMIT, IMP_IMP_PARA, 2, 1},   //0x04000E03 //��ѹ����ֵ
  {SDI_VOL_LOW_LIMIT, IMP_IMP_PARA, 2, 1},  //0x04000E04 //��ѹ����
  
  {SDI_PREPAID_WARN_ENG1, IMP_IMP_PARA, 4, 4}, //��������1
  //#define SDI_PREPAID_WARN_ENG2        0x04000F02 //��������2
  //#define SDI_PREPAID_HOARD_ENG_LIMIT  0x04000F03 //�ڻ������޶�
  //#define SDI_PREPAID_OVERDRAFT_ENG_LIMIT 0x04000F04 //͸֧�����޶�  
  {SDI_PREPAID_WARN_MONEY1, IMP_IMP_PARA, 4, 5}, //�������1
  //#define SDI_PREPAID_WARN_MONEY2      0x04001002 //�������2
  //#define SDI_PREPAID_OVERDRAFT_MONEY_LIMIT 0x04001003 //͸֧����޶�
  {SDI_METER_RUN_STATUS, IMP_IMP_PARA, 1, 1}, //�������״̬��
  
  {SDI_HOUR_FREEZE_START_TIME, IMP_IMP_PARA, 5, 1}, //���㶳����ʼʱ��
  {SDI_HOUR_FREEZE_PERIOD, IMP_IMP_PARA, 1, 1},//���㶳��ʱ����
  {SDI_DATE_FREEZE_TIME, IMP_IMP_PARA, 2, 1},//�ն���ʱ��

  {SDI_RELAY_OFF_DELAY, IMP_IMP_PARA, 2, 1},//��բ��ʱ
  //{SDI_POWER_PULSE, IMP_IMP_PARA, 3,1},         //0x0400E001 //���ʸ���������
  //{SDI_MAX_POWER_CALC_TIME, IMP_IMP_PARA, 1,1},  //0x0400E002 //��󸺺ɼ���ʱ��
  //{SDI_POWER_CTRL_RELAY_SWITCH_LIMIT, IMP_IMP_PARA, 1,1}, //0x0400E003 //��������բ��������

  {SDI_DISP_FEE_DIGS,IMP_IMP_PARA, 1,1},        //0x0400E101 //��ʾ���С��λ

  {SDI_PREPAID_MODEWORD_1,IMP_IMP_PARA, 1,1},   ///0x0400E201 //Ԥ����ģʽ��1
  {SDI_PREPAID_MODEWORD_2,IMP_IMP_PARA, 1,1},   //0x0400E202 //Ԥ����ģʽ��2
  {SDI_PREPAID_MODEWORD_3,IMP_IMP_PARA, 1,1},   //0x0400E203 //Ԥ����ģʽ��3
  
  {SDI_SCHE1_YEAR_TABLE, IMP_IMP_PARA, MAX_YEAR_PERIODS*3, 1},   //0x04010000 //��һ��ʱ����
  {SDI_SCHE1_DATE_TABLE1, IMP_IMP_PARA, MAX_DATE_PERIODS*3, MAX_DATE_TABLES},    //0x04010001 //��һ�׵�һ��ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE2    0x04010002 //��һ��ʱ����ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE3    0x04010003 //��һ��ʱ����ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE4    0x04010004 //��һ��ʱ����ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE5    0x04010005 //��һ��ʱ����ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE6    0x04010006 //��һ��ʱ����ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE7    0x04010007 //��һ��ʱ����ʱ�α�
  //#define SDI_SCHE1_DATE_TABLE8    0x04010008 //��һ��ʱ����ʱ�α�

  {SDI_SCHE2_YEAR_TABLE, IMP_IMP_PARA, MAX_YEAR_PERIODS*3, 1},  //0x04020000 //�ڶ���ʱ����
  {SDI_SCHE2_DATE_TABLE1, IMP_IMP_PARA, MAX_DATE_PERIODS*3, MAX_DATE_TABLES},   //0x04020001 //�ڶ��׵�һ��ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE2    0x04020002 //�ڶ���ʱ����ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE3    0x04020003 //�ڶ���ʱ����ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE4    0x04020004 //�ڶ���ʱ����ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE5    0x04020005 //�ڶ���ʱ����ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE6    0x04020006 //�ڶ���ʱ����ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE7    0x04020007 //�ڶ���ʱ����ʱ�α�
  //#define SDI_SCHE2_DATE_TABLE8    0x04020008 //�ڶ���ʱ����ʱ�α�

  {SDI_HOLIDAY_DATE_TABLE, IMP_IMP_PARA, 4, MAX_YEAR_HOLIDAYS}, //0x04030001 //�����ڼ��ռ���ʱ�α��
  {SDI_AUTO_CYCL_SREEN_DATA, IMP_IMP_PARA, SCREEN_ID_LEN, MAX_AUTO_SCREEN_NUM},  //0x04040101 //�Զ�ѭ������
  {SDI_KEY_CYCL_SREEN_DATA, IMP_IMP_PARA, SCREEN_ID_LEN, MAX_KEY_SCREEN_NUM},   //0x04040201 //����ѭ������
  
  {SDI_RATE_SCHEME0_0, IMP_IMP_PARA, 4, MAX_RATES},//       0x04050101 //��һ�׷��ʲ���
  {SDI_RATE_SCHEME1_0, IMP_IMP_PARA, 4, MAX_RATES},//       0x04050201 //�ڶ��׷��ʲ���

  {SDI_STEP_SCHEME0_ENG, IMP_IMP_PARA, 4, PREPAID_MAX_STEP},//     0x04060001 //��һ�׽��ݲ�������
  {SDI_STEP_SCHEME0_MONEY, IMP_IMP_PARA, 4, PREPAID_MAX_STEP + 1},//   0x04060101 //��һ�׽��ݲ������
  {SDI_STEP_SCHEME1_ENG, IMP_IMP_PARA, 4, PREPAID_MAX_STEP},//      0x04060201 //�ڶ��׽��ݲ�������
  {SDI_STEP_SCHEME1_MONEY, IMP_IMP_PARA, 4, PREPAID_MAX_STEP + 1},//   0x04060301 //�ڶ��׽��ݲ������  
 
  //{SDI_PREPAID_SEQ_NO, IMP_IMP_PARA, 6, 1},//       0x0400EB01 //ϵͳ���к�
  //{SDI_PREPAID_USER_NO, IMP_IMP_PARA, 6, 1},//      0x0400EB02 //�û���
  //{SDI_PREPAID_METER_NO, IMP_IMP_PARA, 6, 1},//     0x0400EB03 //���

  {0x04090101, IMP_IMP_PARA, 2, 2}, //ʧѹ��ѹ�����ͻָ�����
  {0x04090103, IMP_IMP_PARA, 3, 1}, //ʧѹ������������
  {0x04090104, IMP_IMP_PARA, 1, 1}, //ʧѹ�ж���ʱʱ��
  
  {0x04090201, IMP_IMP_PARA, 2, 1}, //Ƿѹ�¼���������
  {0x04090202, IMP_IMP_PARA, 1, 1}, //Ƿѹʱ���ж���ʱʱ��

  {0x04090301, IMP_IMP_PARA, 2, 1}, //��ѹ�¼���������
  {0x04090302, IMP_IMP_PARA, 1, 1}, //��ѹʱ���ж���ʱʱ��
 
  {0x04090401, IMP_IMP_PARA, 2, 1}, //�����¼���ѹ��������
  {0x04090402, IMP_IMP_PARA, 3, 1}, //�����¼�������������  
  {0x04090403, IMP_IMP_PARA, 1, 1}, //����ʱ���ж���ʱʱ��

  {0x04090501, IMP_IMP_PARA, 2, 1}, //��ѹ��ƽ����ֵ
  {0x04090502, IMP_IMP_PARA, 1, 1}, //��ѹ��ƽ���ж���ʱʱ��
  
  {0x04090601, IMP_IMP_PARA, 2, 1}, //������ƽ����ֵ
  {0x04090602, IMP_IMP_PARA, 1, 1}, //������ƽ���ж���ʱʱ��  
 
  {0x04090701, IMP_IMP_PARA, 2, 1}, //ʧ���¼���ѹ��������
  {0x04090702, IMP_IMP_PARA, 3, 2}, //ʧ���¼������������ޡ�����
  {0x04090704, IMP_IMP_PARA, 1, 1}, //ʧ���¼��ж���ʱʱ��  
  
  {0x04090801, IMP_IMP_PARA, 2, 1}, //�����¼�������������
  {0x04090802, IMP_IMP_PARA, 1, 1}, //�����¼��ж���ʱʱ��

  //{0x04090901, IMP_IMP_PARA, 2, 1}, //������ƽ����ֵ
 
  {0x04090901, IMP_IMP_PARA, 2, 1}, //�����¼���ѹ��������
  {0x04090902, IMP_IMP_PARA, 3, 1}, //�����¼�������������  
  {0x04090903, IMP_IMP_PARA, 1, 1}, //����ʱ���ж���ʱʱ��  

  {0x04090A01, IMP_IMP_PARA, 3, 1}, //���������¼��й����ʴ�������
  {0x04090A02, IMP_IMP_PARA, 1, 1}, //���������¼��ж���ʱʱ��

  {0x04090B01, IMP_IMP_PARA, 3, 1}, //�����¼��й����ʴ�������
  {0x04090B02, IMP_IMP_PARA, 1, 1}, //�����¼��ж���ʱʱ��

  {0x04090C01, IMP_IMP_PARA, 2, 2}, //��ѹ��������
  //{0x04090C02, IMP_IMP_PARA, 1, 1}, //��ѹ��������
  
  //{0x04090D01, IMP_IMP_PARA, 2, 3}, //��ѹ�����ϡ�����
  //{0x04090D02, IMP_IMP_PARA, 2, 1}, //��ѹ��������
  
  {0x04090D01, IMP_IMP_PARA, 3, 2}, //�С��޹����������¼�������������
  {0x04090D03, IMP_IMP_PARA, 1, 1}, //���������¼��ж���ʱʱ�� 

  {0x04090E01, IMP_IMP_PARA, 2, 1}, //�ܹ������س����޷�ֵ
  {0x04090E02, IMP_IMP_PARA, 1, 1}, //�ܹ��������������ж���ʱʱ��
  
  {0x04090F01, IMP_IMP_PARA, 2, 1}, //�������ز�ƽ����ֵ
  {0x04090F02, IMP_IMP_PARA, 1, 1}, //�������ز�ƽ�ⴥ����ʱʱ��
  
  {SDI_HARDWARE_VERSION, IMP_IMP_PARA, 32, 1}, //0x04080002,����Ӳ���汾��
 
  //-----------------------------------------------------------------------------------------------
  {SDI_MODEWORD_1, IMP_IMP_PARA, 1, 5}, //0x0E000001 //5��ģʽ��
  /*
  {0x0E000101, IMP_IMP_PARA, 2, 2},
  {0x0E000103, IMP_IMP_PARA, 4, 1},
  {0x0E000104, IMP_IMP_PARA, 1, 1},
  {0x0E000105, IMP_IMP_PARA, 3, 2},
  {0x0E000107, IMP_IMP_PARA, 1, 2},
  {0x0E000109, IMP_IMP_PARA, 3, 1},
  {0x0E00010A, IMP_IMP_PARA, 1, 1},
  {0x0E00010B, IMP_IMP_PARA, 2, 1},
  {0x0E00010C, IMP_IMP_PARA, 1, 3},
  {0x0E00010F, IMP_IMP_PARA, 3, 1},
  {0x0E000110, IMP_IMP_PARA, 3, 1},
  {0x0E000111, IMP_IMP_PARA, 1, 1},
  {0x0E000112, IMP_IMP_PARA, 3, 1},
  {0x0E000113, IMP_IMP_PARA, 1, 1},
  {0x0E000114, IMP_IMP_PARA, 2, 1},  
*/
  {0x0E000108, IMP_IMP_PARA, 1, 1},
  {0x0E000201, IMP_IMP_PARA, 1, 1},//������������������
  {0x0E000202, IMP_IMP_PARA, 2, 4},//����������ʱ�䡢������Чʱ�䡢����������ʣ��ʱ�䡢�����Чʱ��
  //{SDI_PROG_EN_TIME,IMP_IMP_PARA,2,1},//�����Чʱ��
  {SDI_OUTPUT_MODE, IMP_IMP_PARA, 1, 1},//����һ���״̬��ע1��
  {SDI_PERIOD_FREEZE_TIME, IMP_IMP_PARA, 4, 1},//���ڶ���ʱ��
  {SDI_ADJ_TIME_COUNTS, IMP_IMP_PARA, 1, 1}, //ÿ�չ㲥Уʱ����
/*  
  //-----------------------------------------------------------------------------------------------
  //{0x03010000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC��ʧѹ�ܴ��������ۼ�ʱ��
  {EC_DI(0x03010000), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//��ʧѹ����ʱ����
  {EC_DI(0x03010001), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//��ʧѹ������
  {EC_DI(0x03010100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A�෢��ʱ����
  {EC_DI(0x03010101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A��������
  {EC_DI(0x03010200), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x03010201), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x03010300), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x03010301), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  
  {ES_DI(0x03010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03010101), IMP_EVENT1, 131 + 1, LOSS_VOL_NUM}, //ǰ1-10��A��ʧѹ�ڼ��������
  {ES_DI(0x03010200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03010201), IMP_EVENT1, 131 + 1, LOSS_VOL_NUM}, //ǰ1-10��B��ʧѹ�ڼ��������
  {ES_DI(0x03010300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03010301), IMP_EVENT1, 131 + 1, LOSS_VOL_NUM}, //ǰ1-10��C��ʧѹ�ڼ��������
  //{0x03010401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB��ʧѹ�ڼ��������
  //{0x03010501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC��ʧѹ�ڼ��������
  //{0x03010601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC��ʧѹ�ڼ��������
  //{0x03010701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC��ʧѹ�ڼ��������
  //{0x03010801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫʧѹ�ڼ��������
*/
  {EC_DI(0x10000100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//��ʧѹ����ʱ����
  {EC_DI(0x10000101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//��ʧѹ������
  {EC_DI(0x10010100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A�෢��ʱ����
  {EC_DI(0x10010101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1},//A��������
  {EC_DI(0x10020100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x10020101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x10030100), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  {EC_DI(0x10030101), IMP_EVENT_CUMU, CUMU_LOSS_VOL_SIZE,1}, 
  
  {SDI_LAST_LOSS_VOL_OCCUR_TIME, IMP_EVENT1, 6,1}, //���һ��ʧѹ����ʱ��
  {SDI_LAST_LOSS_VOL_END_TIME, IMP_EVENT1, 6,1}, //���һ��ʧѹ����ʱ��
   
  {ES_DI(0x10010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x10010101), IMP_EVENT1, 195 + 1, LOSS_VOL_NUM}, //ǰ1-10��A��ʧѹ�ڼ��������
  {ES_DI(0x10020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x10020101), IMP_EVENT1, 195 + 1, LOSS_VOL_NUM}, //ǰ1-10��B��ʧѹ�ڼ��������
  {ES_DI(0x10030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x10030101), IMP_EVENT1, 195 + 1, LOSS_VOL_NUM}, //ǰ1-10��C��ʧѹ�ڼ��������
/*
  //-----------------------------------------------------------------------------------------------
  //{0x03020000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC��Ƿѹ�ܴ��������ۼ�ʱ��
  {EC_DI(0x03020100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020101), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020200), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020201), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020300), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x03020301), IMP_EVENT_CUMU, 13,1}, 
  
  {ES_DI(0x03020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03020101), IMP_EVENT1, 131 + 1, LOW_VOL_NUM}, //ǰ1-10��A��Ƿѹ�ڼ��������
  {ES_DI(0x03020200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03020201), IMP_EVENT1, 131 + 1, LOW_VOL_NUM}, //ǰ1-10��B��Ƿѹ�ڼ��������
  {ES_DI(0x03020300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03020301), IMP_EVENT1, 131 + 1, LOW_VOL_NUM}, //ǰ1-10��C��Ƿѹ�ڼ��������
  //{0x03020401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB��Ƿѹ�ڼ��������
  //{0x03020501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC��Ƿѹ�ڼ��������
  //{0x03020601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC��Ƿѹ�ڼ��������
  //{0x03020701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC��Ƿѹ�ڼ��������
  //{0x03020801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫǷѹ�ڼ��������
*/
  {EC_DI(0x11010100), IMP_EVENT_CUMU, 13,1}, //A��Ƿѹ����ʱ������
  {EC_DI(0x11010101), IMP_EVENT_CUMU, 13,1}, //A��Ƿѹ������
  {EC_DI(0x11020100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x11020101), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x11030100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x11030101), IMP_EVENT_CUMU, 13,1}, 
  
  {ES_DI(0x11010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x11010101), IMP_EVENT1, 195 + 1, LOW_VOL_NUM}, //ǰ1-10��A��Ƿѹ�ڼ��������
  {ES_DI(0x11020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x11020101), IMP_EVENT1, 195 + 1, LOW_VOL_NUM}, //ǰ1-10��B��Ƿѹ�ڼ��������
  {ES_DI(0x11030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x11030101), IMP_EVENT1, 195 + 1, LOW_VOL_NUM}, //ǰ1-10��C��Ƿѹ�ڼ��������
/*
  //-----------------------------------------------------------------------------------------------
  //{0x03030000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC����ѹ�ܴ��������ۼ�ʱ��
  {EC_DI(0x03030100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03030301), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x03030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03030101), IMP_EVENT1, 131 + 1, OVER_VOL_NUM}, //ǰ1-10��A���ѹ�ڼ��������
  {ES_DI(0x03030200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03030201), IMP_EVENT1, 131 + 1, OVER_VOL_NUM}, //ǰ1-10��B���ѹ�ڼ��������
  {ES_DI(0x03030300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03030301), IMP_EVENT1, 131 + 1, OVER_VOL_NUM}, //ǰ1-10��C���ѹ�ڼ��������
  //{0x03030401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB���ѹ�ڼ��������
  //{0x03030501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC���ѹ�ڼ��������
  //{0x03030601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC���ѹ�ڼ��������
  //{0x03030701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC���ѹ�ڼ��������
  //{0x03030801, IMP_EVENT1, 100, 10}, //ǰ1-10�ι�ѹ�ڼ��������
*/ 
  {EC_DI(0x12010100), IMP_EVENT_CUMU, 13,1}, //A���ѹ����ʱ������
  {EC_DI(0x12010101), IMP_EVENT_CUMU, 13,1}, //A���ѹ������
  {EC_DI(0x12020100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x12020101), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x12030100), IMP_EVENT_CUMU, 13,1}, 
  {EC_DI(0x12030101), IMP_EVENT_CUMU, 13,1}, 
  
  {ES_DI(0x12010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x12010101), IMP_EVENT1, 195 + 1, OVER_VOL_NUM}, //ǰ1-10��A���ѹ�ڼ��������
  {ES_DI(0x12020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x12020101), IMP_EVENT1, 195 + 1, OVER_VOL_NUM}, //ǰ1-10��B���ѹ�ڼ��������
  {ES_DI(0x12030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x12030101), IMP_EVENT1, 195 + 1, OVER_VOL_NUM}, //ǰ1-10��C���ѹ�ڼ��������
  //-----------------------------------------------------------------------------------------------
  /*
  //{0x03040000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC��ȫ�����ܴ��������ۼ�ʱ��
  {EC_DI(0x03040000), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1},//�ܶ��෢��ʱ����
  {EC_DI(0x03040001), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1},//�ܶ����ۼ�����
  {EC_DI(0x03040100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040200), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040201), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040300), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  {EC_DI(0x03040301), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE, 1}, 
  
  {ES_DI(0x03040100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03040101), IMP_EVENT1, 131 + 1, BREAK_VOL_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x03040200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03040201), IMP_EVENT1, 131 + 1, BREAK_VOL_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x03040300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03040301), IMP_EVENT1, 131 + 1, BREAK_VOL_NUM}, //ǰ1-10��C������ڼ��������
  //{0x03040401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB������ڼ��������
  //{0x03040501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC������ڼ��������
  //{0x03040601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC������ڼ��������
  //{0x03040701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC������ڼ��������
  //{0x03040801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫ�����ڼ��������
*/
  {EC_DI(0x13000100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //�ܶ��෢��ʱ������
  {EC_DI(0x13000101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //�ܶ���������
  {EC_DI(0x13010100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //A����෢��ʱ������
  {EC_DI(0x13010101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, //A�����������
  {EC_DI(0x13020100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  {EC_DI(0x13020101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  {EC_DI(0x13030100), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  {EC_DI(0x13030101), IMP_EVENT_CUMU, CUMU_BREAK_VOL_SIZE,1}, 
  
  {ES_DI(0x13010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x13010101), IMP_EVENT1, 195 + 1, BREAK_VOL_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x13020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x13020101), IMP_EVENT1, 195 + 1, BREAK_VOL_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x13030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x13030101), IMP_EVENT1, 195 + 1, BREAK_VOL_NUM}, //ǰ1-10��C������ڼ��������
//-----------------------------------------------------------------------------------------------
  //{0x03050000, IMP_EVENT_CUMU, 6, 1}, //ȫʧѹ�ܴ��������ۼ�ʱ��
  {EC_DI(0x03050000), IMP_EVENT_CUMU, 13, 1},
  {EC_DI(0x03050001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03050000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03050001), IMP_EVENT1, 15 + 1, ALL_LOSS_VOL_NUM}, //ȫʧѹ����ʱ�̡�����ֵ������ʱ��
  //-----------------------------------------------------------------------------------------------
  //{0x03060000, IMP_EVENT_CUMU, 6, 1}, //������Դʧ���ܴ��������ۼ�ʱ��
  {EC_DI(0x03060000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03060001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03060000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03060001), IMP_EVENT1, 12 + 1, AUX_POWER_DOWN_NUM}, //������Դʧ�緢��ʱ�̡�����ʱ��
/*  
  //-----------------------------------------------------------------------------------------------
  //{0x03070000, IMP_EVENT_CUMU, 6, 1}, //��ѹ�������ܴ������ۼ�ʱ��
  {EC_DI(0x03070000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03070001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03070000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03070001), IMP_EVENT1, 76 + 1, VOL_REV_SEQ_NUM}, //ǰ1-10�ε�ѹ�������¼
*/
  //-----------------------------------------------------------------------------------------------
  //{0x03070000, IMP_EVENT_CUMU, 6, 1}, //��ѹ�������ܴ������ۼ�ʱ��
  {EC_DI(0x14000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x14000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x14000100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x14000101), IMP_EVENT1, 140 + 1, VOL_REV_SEQ_NUM}, //ǰ1-10�ε�ѹ�������¼  
  //-----------------------------------------------------------------------------------------------
/*  
  //{0x03080000, IMP_EVENT_CUMU, 6, 1}, //�����������ܴ������ۼ�ʱ��
  {EC_DI(0x03080000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03080001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03080000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03080001), IMP_EVENT1, 76 + 1, CUR_REV_SEQ_NUM}, //ǰ1-10�ε����������¼
*/ 
  {EC_DI(0x15000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x15000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x15000100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x15000101), IMP_EVENT1, 140 + 1, CUR_REV_SEQ_NUM}, //ǰ1-10�ε����������¼
  //------------------------------------------------------------------------------------------------
/*
  //{0x03090000, IMP_EVENT_CUMU, 6, 1}, //��ѹ��ƽ��
  {EC_DI(0x03090000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03090001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x03090000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03090001), IMP_EVENT1, 78 + 1, VOL_UNBALANCE_NUM}, //ǰ1-10�ε�ѹ��ƽ��
*/  
  {EC_DI(0x16000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x16000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x16000100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x16000101), IMP_EVENT1, 143 + 1, VOL_UNBALANCE_NUM}, //ǰ1-10�ε�ѹ��ƽ��
  //-------------------------------------------------------------------------------------------------
/*
  //{0x030A0000, IMP_EVENT_CUMU, 6, 1}, //������ƽ��
  {EC_DI(0x030A0000), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030A0001), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x030A0000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030A0001), IMP_EVENT1, 78 + 1, CUR_UNBALANCE_NUM}, //ǰ1-10�ε�����ƽ��
*/
  {EC_DI(0x17000100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x17000101), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x17000100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x17000101), IMP_EVENT1, 143 + 1, CUR_UNBALANCE_NUM}, //ǰ1-10�ε�����ƽ��
  //------------------------------------------------------------------------------------------------
/*  
  //{0x030B0000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC��ʧ���ܴ��������ۼ�ʱ��
  {EC_DI(0x030B0000), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//��ʧ������ʱ����
  {EC_DI(0x030B0001), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//��ʧ���ۼ�������
  {EC_DI(0x030B0100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//Aʧ������ʱ����
  {EC_DI(0x030B0101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//Aʧ���ۼ������� 
  {EC_DI(0x030B0200), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x030B0201), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x030B0300), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  {EC_DI(0x030B0301), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  
  {ES_DI(0x030B0100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030B0101), IMP_EVENT1, 115 + 1, LOSS_CUR_NUM}, //ǰ1-10��A��ʧ���ڼ��������
  {ES_DI(0x030B0200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030B0201), IMP_EVENT1, 115 + 1, LOSS_CUR_NUM}, //ǰ1-10��B��ʧ���ڼ��������
  {ES_DI(0x030B0300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030B0301), IMP_EVENT1, 115 + 1, LOSS_CUR_NUM}, //ǰ1-10��C��ʧ���ڼ��������
  //{0x030B0401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB��ʧ���ڼ��������
  //{0x030B0501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC��ʧ���ڼ��������
  //{0x030B0601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC��ʧ���ڼ��������
  //{0x030B0701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC��ʧ���ڼ��������
  //{0x030B0801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫʧ���ڼ��������
*/
  {EC_DI(0x18000100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//��ʧ������ʱ����
  {EC_DI(0x18000101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//��ʧ���ۼ�������
  {EC_DI(0x18010100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//Aʧ������ʱ����
  {EC_DI(0x18010101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//Aʧ���ۼ������� 
  {EC_DI(0x18020100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x18020101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//B 
  {EC_DI(0x18030100), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  {EC_DI(0x18030101), IMP_EVENT_CUMU, CUMU_LOSS_CUR_SIZE, 1},//C 
  
  {ES_DI(0x18010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x18010101), IMP_EVENT1, 179 + 1, LOSS_CUR_NUM}, //ǰ1-10��A��ʧ���ڼ��������
  {ES_DI(0x18020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x18020101), IMP_EVENT1, 179 + 1, LOSS_CUR_NUM}, //ǰ1-10��B��ʧ���ڼ��������
  {ES_DI(0x18030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x18030101), IMP_EVENT1, 179 + 1, LOSS_CUR_NUM}, //ǰ1-10��C��ʧ���ڼ��������
/*
  //------------------------------------------------------------------------------------------------
  //{0x030C0000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC�������ܴ��������ۼ�ʱ��
  {EC_DI(0x030C0100), IMP_EVENT_CUMU, 13, 1}, //A����
  {EC_DI(0x030C0101), IMP_EVENT_CUMU, 13, 1},  
  {EC_DI(0x030C0200), IMP_EVENT_CUMU, 13, 1}, //B����
  {EC_DI(0x030C0201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030C0300), IMP_EVENT_CUMU, 13, 1}, //C����
  {EC_DI(0x030C0301), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x030C0100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030C0101), IMP_EVENT1, 115 + 1, OVER_CUR_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x030C0200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030C0201), IMP_EVENT1, 115 + 1, OVER_CUR_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x030C0300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030C0301), IMP_EVENT1, 115 + 1, OVER_CUR_NUM}, //ǰ1-10��C������ڼ��������
  //{0x030C0401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB������ڼ��������
  //{0x030C0501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC������ڼ��������
  //{0x030C0601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC������ڼ��������
  //{0x030C0701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC������ڼ��������
  //{0x030C0801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫ�����ڼ��������
*/
  {EC_DI(0x19010100), IMP_EVENT_CUMU, 13, 1}, //A����
  {EC_DI(0x19010101), IMP_EVENT_CUMU, 13, 1},  
  {EC_DI(0x19020100), IMP_EVENT_CUMU, 13, 1}, //B����
  {EC_DI(0x19020101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x19030100), IMP_EVENT_CUMU, 13, 1}, //C����
  {EC_DI(0x19030101), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x19010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x19010101), IMP_EVENT1, 179 + 1, OVER_CUR_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x19020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x19020101), IMP_EVENT1, 179 + 1, OVER_CUR_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x19030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x19030101), IMP_EVENT1, 179 + 1, OVER_CUR_NUM}, //ǰ1-10��C������ڼ��������
  //----------------------------------------------------------------------------------------------
/*
 //{0x030D0000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC�������ܴ��������ۼ�ʱ��
  {EC_DI(0x030D0100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030D0301), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x030D0100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030D0101), IMP_EVENT1, 115 + 1, BREAK_CUR_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x030D0200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030D0201), IMP_EVENT1, 115 + 1, BREAK_CUR_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x030D0300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030D0301), IMP_EVENT1, 115 + 1, BREAK_CUR_NUM}, //ǰ1-10��C������ڼ��������
  //{0x030D0401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB������ڼ��������
  //{0x030D0501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC������ڼ��������
  //{0x030D0601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC������ڼ��������
  //{0x030D0701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC������ڼ��������
  //{0x030D0801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫ�����ڼ��������
  //------------------------------------------------------------------------------------------------
*/
  {EC_DI(0x1A010100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A010101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A020100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A020101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A030100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1A030101), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x1A010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1A010101), IMP_EVENT1, 179 + 1, BREAK_CUR_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x1A020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1A020101), IMP_EVENT1, 179 + 1, BREAK_CUR_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x1A030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1A030101), IMP_EVENT1, 179 + 1, BREAK_CUR_NUM}, //ǰ1-10��C������ڼ��������
/*
  //{0x030E0000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC�����������ܴ��������ۼ�ʱ��
  {EC_DI(0x030E0000), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//�ܷ�����ʱ����
  {EC_DI(0x030E0001), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//�ܷ����ۼ�����
  {EC_DI(0x030E0100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0200), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0201), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0300), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x030E0301), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  
  {ES_DI(0x030E0100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030E0101), IMP_EVENT1, 76 + 1, TREND_REVERSE_NUM}, //ǰ1-10��A�ೱ�������ڼ��������
  {ES_DI(0x030E0200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030E0201), IMP_EVENT1, 76 + 1, TREND_REVERSE_NUM}, //ǰ1-10��B�ೱ�������ڼ��������
  {ES_DI(0x030E0300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030E0301), IMP_EVENT1, 76 + 1, TREND_REVERSE_NUM}, //ǰ1-10��C�ೱ�������ڼ��������
  //{0x030E0401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB�ೱ�������ڼ��������
  //{0x030E0501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC�ೱ�������ڼ��������
  //{0x030E0601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC�ೱ�������ڼ��������
  //{0x030E0701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC�ೱ�������ڼ��������
  //{0x030E0801, IMP_EVENT1, 100, 10}, //ǰ1-10��ȫ���������ڼ��������
*/
  {EC_DI(0x1B000100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//�ܷ�����ʱ����
  {EC_DI(0x1B000101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1},//�ܷ����ۼ�����
  {EC_DI(0x1B010100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B010101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B020100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B020101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B030100), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  {EC_DI(0x1B030101), IMP_EVENT_CUMU, CUMU_NEG_CUR_SIZE, 1}, 
  
  {ES_DI(0x1B010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1B010101), IMP_EVENT1, 140 + 1, TREND_REVERSE_NUM}, //ǰ1-10��A�ೱ�������ڼ��������
  {ES_DI(0x1B020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1B020101), IMP_EVENT1, 140 + 1, TREND_REVERSE_NUM}, //ǰ1-10��B�ೱ�������ڼ��������
  {ES_DI(0x1B030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1B030101), IMP_EVENT1, 140 + 1, TREND_REVERSE_NUM}, //ǰ1-10��C�ೱ�������ڼ��������
  //-----------------------------------------------------------------------------------------------
/*
 /// {0x030F0000, IMP_EVENT_CUMU, 18, 1}, //A��B��C��AB��AC��BC��ABC�������ܴ��������ۼ�ʱ��
  {EC_DI(0x030F0100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x030F0301), IMP_EVENT_CUMU, 13, 1}, 
  {ES_DI(0x030F0100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030F0101), IMP_EVENT1, 76 + 1, OVER_LOAD_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x030F0200), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030F0201), IMP_EVENT1, 76 + 1, OVER_LOAD_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x030F0300), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x030F0301), IMP_EVENT1, 76 + 1, OVER_LOAD_NUM}, //ǰ1-10��C������ڼ��������
  //{0x030F0401, IMP_EVENT1, 100, 10}, //ǰ1-10��AB������ڼ��������
  //{0x030F0501, IMP_EVENT1, 100, 10}, //ǰ1-10��AC������ڼ��������
  //{0x030F0601, IMP_EVENT1, 100, 10}, //ǰ1-10��BC������ڼ��������
  //{0x030F0701, IMP_EVENT1, 100, 10}, //ǰ1-10��ABC������ڼ��������
  //{0x030F0801, IMP_EVENT1, 100, 10}, //ǰ1-10�ι����ڼ��������
*/
  {EC_DI(0x1C010100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C010101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C020100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C020101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C030100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x1C030101), IMP_EVENT_CUMU, 13, 1}, 
  
  {ES_DI(0x1C010100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1C010101), IMP_EVENT1, 140 + 1, OVER_LOAD_NUM}, //ǰ1-10��A������ڼ��������
  {ES_DI(0x1C020100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1C020101), IMP_EVENT1, 140 + 1, OVER_LOAD_NUM}, //ǰ1-10��B������ڼ��������
  {ES_DI(0x1C030100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1C030101), IMP_EVENT1, 140 + 1, OVER_LOAD_NUM}, //ǰ1-10��C������ڼ��������
  //------------------------------------------------------------------------------------------------
  //{0x03310100, IMP_EVENT1, 3, 1}, //��բ�ܴ���
  {EC_DI(0x1D000100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x1D000101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x1D000100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1D000101), IMP_EVENT2, 34 + 1, RELAY_OFF_NUM}, //ǰ1-10����բ��¼
  //------------------------------------------------------------------------------------------------
  //{0x03310200, IMP_EVENT1, 3, 1}, //��բ�ܴ���
  {EC_DI(0x1E000100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x1E000101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x1E000100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1E000101), IMP_EVENT2, 34 + 1, RELAY_ON_NUM}, //ǰ1-10�κ�բ��¼  
  //------------------------------------------------------------------------------------------------
  //{0x03310200, IMP_EVENT1, 3, 1}, //�ܹ������س�����
  {EC_DI(0x1F000100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x1F000101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x1F000100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x1F000101), IMP_EVENT1, 44 + 1, FACTOR_LOW_NUM}, //ǰ1-10���ܹ������س�����  
  //-----------------------------------------------------------------------------------------------
  {0x03100000, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //��1-12�µ�ѹ�������
  {0x03100100, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //��1-12��A���ѹ�������
  {0x03100200, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //��1-12��B���ѹ�������
  {0x03100300, IMP_HIS_DATA, 27, MAX_VOLSTAT_SETTLE_NUM}, //��1-12��C���ѹ�������
  //-----------------------------------------------------------------------------------------------
  //{0x03110000, IMP_EVENT_CUMU, 3, 1}, //�����ܴ���
  {EC_DI(0x03110000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03110001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03110000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03110001), IMP_EVENT2, 12 + 1, POWER_DOWN_NUM}, //ǰ1-10�ε��緢���ͽ���ʱ��
  //-----------------------------------------------------------------------------------------------
  //{0x03120000, IMP_EVENT_CUMU, 18, 1}, //�������޴���
  {EC_DI(0x03120100), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120101), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120200), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120201), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120300), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120301), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120400), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120401), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120500), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120501), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120600), IMP_EVENT_CUMU, 13, 1}, 
  {EC_DI(0x03120601), IMP_EVENT_CUMU, 13, 1},
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x03120100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03120101), IMP_EVENT2, 20 + 1, POS_ACT_DEMAND_EXCEED_NUM}, //ǰ1-10�������й���������
  {ES_DI(0x03120200), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03120201), IMP_EVENT2, 20 + 1, NEG_ACT_DEMAND_EXCEED_NUM}, //ǰ1-10�η����й���������
  {ES_DI(0x03120300), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03120301), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //ǰ1-10�ε�һ�����޹���������
  {ES_DI(0x03120400), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03120401), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //ǰ1-10�εڶ������޹���������
  {ES_DI(0x03120500), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03120501), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //ǰ1-10�ε��������޹���������
  {ES_DI(0x03120600), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03120601), IMP_EVENT2, 20 + 1, REA_DEMAND_EXCEED_NUM}, //ǰ1-10�ε��������޹���������
  //-----------------------------------------------------------------------------------------------
  //{0x03300000, IMP_EVENT1, 18, 1}, //����ܴ���
  {EC_DI(0x03300000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300001), IMP_EVENT_CUMU, 13, 1},//������
  {ES_DI(0x03300000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300001), IMP_EVENT2, 50 + 1, PROG_NUM}, //ǰ1-10�α�̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300100, IMP_EVENT1, 3, 1}, //�����0�ܴ���
  {EC_DI(0x03300100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300101), IMP_EVENT_CUMU, 13, 1},//������
  {ES_DI(0x03300100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300101), IMP_EVENT2, 106 + 1, CLEAR_METER_NUM}, //ǰ1-10�ε����0��¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300200, IMP_EVENT1, 3, 1}, //������0�ܴ���
  {EC_DI(0x03300200), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300201), IMP_EVENT_CUMU, 13, 1},//������
  {ES_DI(0x03300200), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300201), IMP_EVENT2, 202 + 1, CLEAR_DEMAND_NUM}, //ǰ1-10��������0��¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300300, IMP_EVENT1, 3, 1}, //�¼���0�ܴ���
  {EC_DI(0x03300300), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300301), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300300), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300301), IMP_EVENT2, 14 + 1, CLEAR_EVENT_NUM}, //ǰ1-10���¼���0��¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300400, IMP_EVENT1, 3, 1}, //Уʱ�ܴ���
  {EC_DI(0x03300400), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300401), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300400), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300401), IMP_EVENT2, 16 + 1, ADJ_TIME_NUM}, //ǰ1-10��Уʱ0��¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300500, IMP_EVENT1, 3, 1}, //ʱ�α����ܴ���
  {EC_DI(0x03300500), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300501), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300500), IMP_LOAD_REC, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300501), IMP_LOAD_REC, 682 + 1, DATE_TABLE_PROG_NUM}, //ǰ1-10��ʱ�α��̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300600, IMP_EVENT1, 3, 1}, //ʱ�������ܴ���
  {EC_DI(0x03300600), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300601), IMP_EVENT_CUMU, 13, 1},//������
  {ES_DI(0x03300600), IMP_LOAD_REC, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300601), IMP_LOAD_REC, 94 + 1, YEAR_TABLE_PROG_NUM}, //ǰ1-10��ʱ�����̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300700, IMP_EVENT1, 3, 1}, //�����ձ���ܴ���
  {EC_DI(0x03300700), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300701), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300700), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300701), IMP_EVENT2, 11 + 1, WEEK_REST_PROG_NUM}, //ǰ1-10�������ձ�̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300800, IMP_EVENT1, 3, 1}, //�ڼ��ձ���ܴ���
  {EC_DI(0x03300800), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300801), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300800), IMP_LOAD_REC, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300801), IMP_LOAD_REC, (MAX_YEAR_HOLIDAYS*4) + 10 + 1, HOLIDAY_PROG_NUM}, //ǰ1-10�νڼ��ձ�̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300900, IMP_EVENT1, 3, 1}, //�й���ϱ���ܴ���
  {EC_DI(0x03300900), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300901), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300900), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300901), IMP_EVENT2, 11 + 1, ACTIVE_COMB_PROG_NUM}, //ǰ1-10���й���ϱ�̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300A00, IMP_EVENT1, 3, 1}, //�޹����1����ܴ���
  {EC_DI(0x03300A00), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300A01), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300A00), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300A01), IMP_EVENT2, 11 + 1, REACTIVE_COMB_PROG_NUM}, //ǰ1-10���޹����1��̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300B00, IMP_EVENT1, 3, 1}, //�޹����2����ܴ���
  {EC_DI(0x03300B00), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300B01), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300B00), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300B01), IMP_EVENT2, 11 + 1, REACTIVE_COMB_PROG_NUM}, //ǰ1-10���޹����2��̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300C00, IMP_EVENT1, 3, 1}, //�����ձ���ܴ���
  {EC_DI(0x03300C00), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300C01), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300C00), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300C01), IMP_EVENT2, 16 + 1, SETTLE_TIME_PROG_NUM}, //ǰ1-10�ν����ձ�̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300D00, IMP_EVENT1, 3, 1}, //�����ܴ���
  {EC_DI(0x03300D00), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300D01), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300D00), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300D01), IMP_EVENT1, 60 + 1, OPEN_METER_COVER_NUM}, //ǰ1-10�ο��Ǳ�̼�¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300E00, IMP_EVENT1, 3, 1}, //����ť�ܴ���
  {EC_DI(0x03300E00), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03300E01), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03300E00), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03300E01), IMP_EVENT1, 60 + 1, OPEN_BOTTOM_COVER_NUM}, //ǰ1-10�ο���ť��̼�¼

  //------------------------------------------------------------------------------------------------  
  //{0x03320100, IMP_EVENT1, 3, 1}, //�����͹���
  {EC_DI(0x03320100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03320101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03320100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03320101), IMP_EVENT2, 23 + 1, PREPAID_ENERGY_NUM}, //ǰ1-10�ι����¼
  //---------------------------------------------------------------------------------------------
  //{0x03330100, IMP_EVENT1, 3, 1}, //����͹���
  {EC_DI(0x03330100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03330101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03330100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03330101), IMP_EVENT2, 23 + 1, PREPAID_MONEY_NUM}, //ǰ1-10�ι����¼
  //-----------------------------------------------------------------------------------------------
  //{0x03300D00, IMP_EVENT1, 3, 1}, //�͹��ĵ��Ƿѹ
  {EC_DI(0x03410000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03410001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03410000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03410001), IMP_EVENT2, 12 + 1, LOWPWR_BAT_LOW_NUM}, //ǰ1-10�ε͹��ĵ��Ƿѹ  
  //-----------------------------------------------------------------------------------------------
  //{0x03300D00, IMP_EVENT1, 3, 1}, //ʱ�ӵ��Ƿѹ
  {EC_DI(0x03410100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03410101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03410100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03410101), IMP_EVENT2, 12 + 1, RTC_BAT_LOW_NUM}, //ǰ1-10��ʱ�ӵ��Ƿѹ 
  //-------------------------------------------------------------------------------------------------
  
  
  //-------------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)PERIOD_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)PERIOD_FREEZE_TYPE << 16), IMP_LOAD_REC, FREEZE_DATA_MAX_LEN + 1, PERIOD_FREEZE_NUM}, //��ʱ����,������̫�󣬴�ŵ�Flash��
  //------------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)INSTANT_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)INSTANT_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, INSTANT_FREEZE_NUM}, //˲ʱ����ʱ��
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)YEAR_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)YEAR_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, YEAR_TABLE_SWITCH_NUM}, //����ʱ�����л�
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)DATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)DATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, DATE_TABLE_SWITCH_NUM}, //����ʱ�����л�
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)STEP_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)STEP_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, STEP_SCH_SWITCH_NUM}, //����ʱ�����л�
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)RATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)RATE_SWITCH_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, RATE_SCH_SWITCH_NUM}, //�����ʷ����л�  
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)DATE_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)DATE_FREEZE_TYPE << 16), IMP_LOAD_REC, FREEZE_DATA_MAX_LEN + 1, DATE_FREEZE_NUM}, //�ն���
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)HOUR_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)HOUR_FREEZE_TYPE << 16), IMP_EVENT0, 5 + 8 + 1, HOUR_FREEZE_0_NUM}, //Сʱ���ᣬ������̫��
  //-----------------------------------------------------------------------------------------------
  {ES_DI(0x05000000) | ((INT32U)ENG_OVERTURN_FREEZE_TYPE << 16), IMP_EVENT0, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x05000001) | ((INT32U)ENG_OVERTURN_FREEZE_TYPE << 16), IMP_EVENT0, FREEZE_DATA_MAX_LEN + 1, ENERGY_OVERTRUN_NUM}, //������ת
  //-----------------------------------------------------------------------------------------------   
 
  //���ر���
  {EC_DI(0x03420000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03420001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03420000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03420001), IMP_EVENT1, 18 + 1, PWR_CTRL_ALARM_NUM}, //ǰ1-10�θ��ر���    
  //������բ
  {EC_DI(0x03420100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x03420101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x03420100), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x03420101), IMP_EVENT1, 12 + 1, PWR_CTRL_SWITCH_NUM}, //ǰ1-10�θ�����բ
  //��λ
  {EC_DI(0x0E180000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E180001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E180000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E180001), IMP_EVENT2, 6 + 1, RESET_NUM}, //ǰ1-10�θ�λ
  //ʱ����
  {EC_DI(0x0E190000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E190001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E190000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E190001), IMP_EVENT2, 11 + 1, RUN_CLOCK_ERR_NUM}, //ǰ1-10��ʱ����
  //EEROM��
  {EC_DI(0x0E1A0000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E1A0001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E1A0000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E1A0001), IMP_EVENT2, 5 + 1, EEROM_ERR_NUM}, //ǰ1-10��EEROM��
    /*
  //������ת
  {EC_DI(0x0E1B0000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E1B0001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E1B0000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E1B0001), IMP_EVENT1, 78 + 1, ENERGY_OVERFLOW_NUM}, //ǰ1-10�ε�����ת 
 */
  //�ϵ�ʱ����
  {EC_DI(0x0E1C0000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E1C0001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E1C0000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E1C0001), IMP_EVENT2, 11 + 1, POWER_ON_CLOCK_ERR_NUM}, //ǰ1-10���ϵ�ʱ����  
/*
  //Զ����բ
  {EC_DI(0x0E1D0000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E1D0001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E1D0000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E1D0001), IMP_EVENT1, 38 + 1, REMOTE_RELAY_SWITCH_NUM}, //ǰ1-10��Զ����բ  
  
   //Զ�̺�բ
  {EC_DI(0x0E1E0000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E1E0001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E1E0000), IMP_EVENT1, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E1E0001), IMP_EVENT1, 38 + 1, REMOTE_RELAY_SWITCH_NUM}, //ǰ1-10��Զ�̺�բ
*/  
  //У��
  {EC_DI(0x0E300000), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E300001), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E300000), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E300001), IMP_EVENT2, 6 + 1, ADJ_METER_NUM}, //ǰ1-10��У��

  //���ó�ʼ����
  {EC_DI(0x0E301100), IMP_EVENT_CUMU, 13, 1},//����ʱ����
  {EC_DI(0x0E301101), IMP_EVENT_CUMU, 13, 1},//������  
  {ES_DI(0x0E301100), IMP_EVENT2, 4, 1}, //���һ�δ洢DI
  {ES_DI(0x0E301101), IMP_EVENT2, 77 + 1, SET_ENERG_NUM}, //ǰ1-10�����ó�ʼ����
  
  //{SDI_LAST_LOSS_VOL_OCCUR_TIME, IMP_EVENT1, 6, 1},//���һ��ʧѹ����ʱ��
  //{SDI_LAST_LOSS_VOL_END_TIME, IMP_EVENT1, 6, 1}, //���һ��ʧѹ����ʱ��

/*
  #define IMP_FAC_PARA  IMP_0 //�������� 
  #define IMP_IMP_PARA  IMP_1 //��Ҫ����      
  #define IMP_NOR_PARA  IMP_2 //��ͨ����     
  #define IMP_IMP_DATA  IMP_3 //��Ҫ����      
  #define IMP_IMP_BAK_DATA  IMP_4 //��Ҫ���ݵı���   
  #define IMP_NOR_DATA  IMP_5 //��ͨ����
  #define IMP_HIS_DATA  IMP_6 //��ʷ����     
  #define IMP_EVENT_CUMU  IMP_7 //�¼��ۼ���Ϣ  
  #define IMP_EVENT0    IMP_8 //��0���¼�����Ƶ���������ݻ��       
  #define IMP_EVENT1    IMP_9 //��1���¼�������������Ƶ���������EEROM     
  #define IMP_EVENT0    IMP_A //��2���¼����������󣬵��ǲ�Ƶ����һ���Flash          
  #define IMP_LOAD_REC  IMP_B //���ɼ�¼����Flash      
  #define IMP_PD_DATA   IMP_C //����洢���ݣ���FRAM 
  */
  EXTEND_STORA
  //-----------------------------------------------------------------------------------------------
  {_SDI_CHK_IMP0, IMP_FAC_PARA, 1, 1},  //IMPÿ�����ݵĲ����� 
  {_SDI_CHK_IMP1, IMP_IMP_PARA, 1, 1}, 
  {_SDI_CHK_IMP2, IMP_IMP_PARA, 1, 1},//ʵ��δ��
  {_SDI_CHK_IMP3, IMP_IMP_DATA, 1, 1}, 
  {_SDI_CHK_IMP4, IMP_IMP_BAK_DATA, 1, 1}, 
  {_SDI_CHK_IMP5, IMP_IMP_PARA, 1, 1},//ʵ��δ��
  {_SDI_CHK_IMP6, IMP_HIS_DATA, 1, 1}, 
  {_SDI_CHK_IMP7, IMP_EVENT_CUMU, 1, 1}, 
  {_SDI_CHK_IMP8, IMP_EVENT0, 1, 1}, 
  {_SDI_CHK_IMP9, IMP_EVENT1, 1, 1}, 
  {_SDI_CHK_IMPA, IMP_EVENT2, 1, 1}, 
  {_SDI_CHK_IMPB, IMP_LOAD_REC, 1, 1}, 
  {_SDI_CHK_IMPC, IMP_PD_DATA, 1, 1},
  
  {_SDI_CHG_CS, IMP_LOAD_REC, 10, 1}  //���ڸı������洢���ݵ�CS,�ı��䳤�ȿɸı����CS���Ӷ��Զ������
}; 

//extern void Clear_CPU_Dog(void); 
//extern void Clear_Ext_Dog(void); 

//��鳬������������Ƿ������ˣ����Ϸ���1�����򷵻�0
INT8U Check_SuperPSW_Jump()
{
  return 1;
}

//���Imp_Flag��־�ĺϷ��ԣ���ȷ����1�����򷵻�0
INT8U Check_Imp_Flag(INT8U Imp_Flag)
{
  if(Imp_Flag <= IMP_C)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//extern CONST S_Data_Mem_Map Data_Mem_Map[];
//��ȡ�߼��洢����Imp��־
//Mem_No��ʾ�߼��洢�����
INT8U Get_LOG_Mem_ImpFlag(INT8U Mem_No)
{
  INT8U i, j;
  
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    for(j = 0; j < IMP_LOG_MEM; j ++)
    {
      if(Mem_No EQ Data_Mem_Map[i].LOG_Mem[j])
        return Data_Mem_Map[i].Imp_Flag;
    }   
  }
  return 0xFF;
}

//��ȡĳ���洢��������������Ҫ��־
INT8U Get_Storage_Data_ImpFlag(STORA_DI SDI)
{
  INT16U i; 

  TRACE();

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].SDI EQ SDI || \
       (Data_Para_Storage[i].Num > 1 && Data_Para_Storage[i].SDI < SDI && SDI < Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num))
    {
      return Data_Para_Storage[i].Imp_Flag;
    }
  }
  ASSERT_FAILED(); 
  return NULL_IMP;
}

//��ȡĳ���洢��������Ĵ洢ƫ�ƣ���ƫ�Ʊ�ʾ����������ͬImp_Flag�����еĴ洢Ʒƫ��
//Ҳ��ʾ���߼��洢���е�����ƫ��
INT32U Get_Storage_Data_Off(STORA_DI SDI)
{
  INT16U i; 
  INT32U Offset = 0; 
  INT8U Imp_Flag, Re; 

  TRACE();

  Imp_Flag = Get_Storage_Data_ImpFlag(SDI); 
  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(0 != Re); 

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].SDI EQ SDI)
    {
      return Offset;
    }
    else if(Data_Para_Storage[i].Num > 1 && Data_Para_Storage[i].SDI < SDI && SDI < Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num)
    {
      Offset += (Data_Para_Storage[i].Len + ROM_CS_BYTES) * (SDI - Data_Para_Storage[i].SDI); 
      return Offset;
    }
    else if(Data_Para_Storage[i].Imp_Flag EQ Imp_Flag)//����ƫ��
    {
      //if(Data_Para_Storage[i].Num EQ 1)
      // Offset += Data_Para_Storage[i].Len + ROM_CS_BYTES;  
      //else
      Offset += (Data_Para_Storage[i].Len + ROM_CS_BYTES) * Data_Para_Storage[i].Num;
    }
  }

  Debug_Print("Get_Storage_Data_Off Error, Data 0x%lx Not Found\r\n", SDI); 
  return NULL_4BYTES;
}

//��ȡĳ���洢��������ĳ���, DIֻ����Data_Para_Storage�ж��������
INT16U Get_Storage_Data_Len(STORA_DI SDI)
{
  INT16U i; 

  TRACE();

  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if((Data_Para_Storage[i].Num > 0 && Data_Para_Storage[i].SDI EQ SDI) || \
       (Data_Para_Storage[i].Num > 1 && \
	  Data_Para_Storage[i].SDI < SDI && \
	  Data_Para_Storage[i].SDI + Data_Para_Storage[i].Num> SDI))
    {
      return Data_Para_Storage[i].Len;
    }
  }
  _Debug_Print("Get_Storage_Data_Len Err, SDI = 0x%lx",SDI);
  ASSERT_FAILED(); 
  return 0;
}

//��ȡĳ��Imp_Flag��Ҫ�ȼ����ݵ��������ݳ���Get_Imp_Data_Size�ķ���ֵӦ�� <= Get_Imp_Mem_Size
INT32U Get_Imp_Data_Size(INT8U Imp_Flag)
{
  INT8U Re; 
  INT16U i; 
  INT32U Size = 0; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 
  for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
  {
    if(Data_Para_Storage[i].Imp_Flag EQ Imp_Flag)
    {
      Size += ((INT32U) Data_Para_Storage[i].Len + ROM_CS_BYTES) * Data_Para_Storage[i].Num;
    }
  }
  //ASSERT(Size != 0); 
  return Size;
}

//��÷����ĳ��Imp_Flag�ȼ������ݵĴ洢�ռ��С
INT32U Get_Imp_Mem_Size(INT8U Imp_Flag)
{
  INT16U i, j; 
  INT32U Size = 0; //����һ�������ڵ�size
  INT8U Re; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 

  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    if(Data_Mem_Map[i].Imp_Flag EQ Imp_Flag)//���ҵ������ڴ�ӳ����еĶ�Ӧ��
    {
      Size = 0xFFFFFFFF; //����һ������ֵ
      for(j = 0; j < IMP_LOG_MEM; j ++)
      {
        if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
        {
          //�ҳ���С��һ��Log_Mem���Ƿ�������ݵĴ洢�ռ��С
          if(Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]) < Size)
            Size = Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]);
        }
      }
      break;
    }
  }
  //ASSERT(Size != 0 && Size != 0xFFFFFFFF); 
  if(0 EQ Size || 0xFFFFFFFF EQ Size)
  {
    Debug_Print("Imp%d Data Mem_map error", Imp_Flag);
  } 
  return Size;
}

//�Ӵ洢���ж�ȡĳ����Ҫ�ȼ�������
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset, ��ʾ�����ڴ洢���е�ƫ��
//pDst����ʾ���ݶ�ȡ���Ŀ��ָ��
//RD_Len����ʾ��Ҫ��ȡ�����ݵĳ���
//pDst_Start��DstLenyһ���pDst��RD_Len�ķ�Χ����Լ��
//����1��ʾ�ɹ�
INT8U Read_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen)
{
  INT16U i, j; 
  INT32U Sum; 
  INT8U Re; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 
  ASSERT((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + RD_Len <= (INT8U *) pDst_Start + DstLen); 

  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    if(Data_Mem_Map[i].Imp_Flag EQ Imp_Flag)//�ҵ������ڴ�ӳ����еĶ�Ӧ��
    {
      for(j = 0; j < IMP_LOG_MEM; j ++)//��ȡ�洢���߼��洢��
      {
        if(j != 0)//ǰһ�ζ�ȡû�гɹ� ������ʱһ�£���ֹ��Ϊ���߸��ų�����
          OS_TimeDly_Ms(10); 

        if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)//�ҵ�һ���洢�����ݵ��߼��洢��
        {
          //�����߼��洢���е�����
          Re = Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset, pDst, RD_Len, pDst_Start, DstLen); 
          if(1!=Re)//ASSERT(1 EQ Re)) //ȷ��������ȷ
          {
            ASSERT_FAILED();
            continue;
          }
          
          //��У���
          Re = Read_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset + RD_Len, &Sum, ROM_CS_BYTES, &Sum, sizeof(Sum)); 
          if(1!=Re)//ASSERT(1 EQ Re))
          {
            ASSERT_FAILED();
            continue;
          }
          //���У����Ƿ���ȷ
          if(Check_Sum(pDst, RD_Len, &Sum, ROM_CS_BYTES))//У�����ȷ��ֱ�ӷ���1�����������ȡ�¸�LOG_MEM
            return 1;
          else
            continue;
        }
      }
      ASSERT_FAILED(); 
      return 0;
    }
  }
  ASSERT_FAILED(); 
  return 0;
}

//��ĳ����Ҫ��־������д�뵽�洢����
//Imp_Flag����ʾ���ݵ���Ҫ�ȼ���־
//Offset, ��ʾ�����ڴ洢���е�ƫ��
//pSrc����ʾ���ݵ���ʼָ��
//SrcLen����ʾ���ݵĳ���
//����1��ʾд�ɹ�
//����WR_IMP_DATA_ERR��ʾд����ʧ��
INT8U Write_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pSrc, INT16U SrcLen)
{
  INT8U i, j; 
  INT8U Re; 
  INT32U Sum; 
  INT8U Err_Flag = 0; 

  TRACE();

  Re = Check_Imp_Flag(Imp_Flag); 
  ASSERT(Re != 0); 
  Set_Sum(pSrc, SrcLen, &Sum, ROM_CS_BYTES, &Sum, sizeof(Sum)); //����У���

  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    if(Data_Mem_Map[i].Imp_Flag EQ Imp_Flag)
    {
      Err_Flag = 0; //ֻҪ�ɹ���һ�ξ� Err_Flag |= 1; 
      for(j = 0; j < IMP_LOG_MEM; j ++)
      {
        if(j != 0 && Err_Flag EQ 0)//ǰһ��û��д�ɹ�������ʱһ����д
          OS_TimeDly_Ms(10); 

        if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
        {
          Re = Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset, pSrc, SrcLen); //д����
          ASSERT(1 EQ Re); 
          if(1 EQ Re)
          {
            Re = Write_LOG_Mem(Data_Mem_Map[i].LOG_Mem[j], Offset + SrcLen, &Sum, ROM_CS_BYTES); //дУ���
            ASSERT(1 EQ Re); 
            if(1 EQ Re)
              Err_Flag |= 1;
          }
        }
      }
      if(Err_Flag != 0)//����д�ɹ���һ��
        return 1;
      else
        return 0;
    }
  }
  ASSERT_FAILED(); 
  return 0;
}

//��ȡ�洢���е�ĳ�����ݵĹ̶����ȣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫ��ȡ���������ʶ
//Offset, ��ȡDI���ݵ���ʼƫ��
//Len, ��Ҫ��ȡ�����ݳ���
//pDst��ʾ��ȡ������ŵ��û�����
//pDst_Start��DstLenһ��綨Ŀ�껺�����ķ�Χ
//*pErr��ʾ��ȡʧ��ʱ��ԭ��, 1��ʾ��ȡ�ɹ�, ��������ԭ��μ�Pub_Err.h
//����ֵ����ȡ�����ݳ���, ��ȡʧ��ʱ����0
INT16U Read_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT32U Off; 
  INT8U Imp_Flag, Err; 

  TRACE();

  _Debug_Print("Read Storage Data:0x%lx, Off = %d, Len = %d", SDI, Offset, Len); 

  Imp_Flag = Get_Storage_Data_ImpFlag(SDI); //��ȡ�����ݵ���Ҫ��־ 
  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + Len <= (INT8U *) pDst_Start + DstLen)) 
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Off = Get_Storage_Data_Off(SDI); //��ȡ����ƫ��
  if(NULL_4BYTES EQ Off)//ASSERT(NULL_4BYTES != Off))
  {
    ASSERT_FAILED();
    //*pErr = RD_STORAGE_DATA_DI_ERR; 
    return 0;
  }

  Off += Offset; // + �ڲ�ƫ��

  OS_Mutex_Pend(PUB_RW_ROM_ID); //����дROM���ź���ID
  //if(Check_Power_Status() EQ POWER_ON_STATUS)
  Err = Read_Imp_Data(Imp_Flag, Off, pDst, Len, pDst_Start, DstLen); 
  //else
  //*pErr = PD_Read_Imp_Data(Imp_Flag, Off, pDst, Len, pDst_Start, DstLen); 
  OS_Mutex_Post(PUB_RW_ROM_ID); //�ͷ�дROM���ź���ID
  if(1 EQ Err)
  {
    return Len;
  }
  else//���洢ʧ�����ȡĬ�ϲ���
  {
    //*pErr = RD_FIX_DATA_ERR; 
    return 0;
  }
  //return 0;   

}

//д�洢���е�ĳ�����ݵĹ̶����ȣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫд���������ʶ
//Offset, дDI���ݵ���ʼƫ��
//SrcLen, ��Ҫд�����ݳ���
//pSrc��ʾд��Դ���ݻ�����
//SrcLen��ʾԴ���ݵĳ���
//����1��ʾ�ɹ���������ʾʧ��
INT8U Write_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, void* pSrc, INT16U SrcLen)
{
  INT32U Off; 
  INT8U Imp_Flag, Re; 

  TRACE();

  _Debug_Print("Write Storage Data:0x%lx, Off = %d, Len = %d", SDI, Offset, SrcLen); 

  Imp_Flag = Get_Storage_Data_ImpFlag(SDI); //��ȡ�����ݵ���Ҫ��־ 

  Off = Get_Storage_Data_Off(SDI); //��ȡ����ƫ��
  if(NULL_4BYTES EQ Off)
  {
    ASSERT_FAILED();
    return 0;
  }

  Off += Offset; // + �ڲ�ƫ��
  OS_Mutex_Pend(PUB_RW_ROM_ID);  
  //if(Check_Power_Status() EQ POWER_ON_STATUS)
  Re = Write_Imp_Data(Imp_Flag, Off, pSrc, SrcLen); 
  //else
  //Re = PD_Write_Imp_Data(Imp_Flag, Off, pSrc, SrcLen);     
  OS_Mutex_Post(PUB_RW_ROM_ID); 

  //OS_TimeDly_Ms(20); //��ʱ20ms

  if(1 EQ Re)
  {
    return 1;
  }
  else//���洢ʧ�����ȡĬ�ϲ���
  {
    return 0;
  }
}


//��ȡ�洢���е�ĳ�����ݣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫ��ȡ���������ʶ
//pPara���ڶ�ȡĳЩ����������ʱ��Ҫ�Ĳ���������HIS_ENERGY, HIS_DEMAND, HIS_DEMAND_TIMEʱ��Ҫ����ʱ�����
//ʱ������ĸ�ʽ��������pPara[0]-pPara[4]�ֱ��Ƿ֡�ʱ���ա��¡���, ��������¸ò���������
//pDst��ʾ��ȡ������ŵ��û�����
//pDst_Start��DstLenһ��綨Ŀ�껺�����ķ�Χ
//*pErr��ʾ��ȡʧ��ʱ��ԭ��, 1��ʾ��ȡ�ɹ�, ��������ԭ��μ�Pub_Err.h
//����ֵ����ȡ�����ݳ���, ��ȡʧ��ʱ����0
INT16U Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Len, Len1; 

  TRACE();

  //Clear_CPU_Dog();     //��CPU�ڲ����Ź�
  //Clear_Ext_Dog();     //��CPU�ⲿ���Ź�

  //Cur_Task_ID = Get_Cur_Task_ID(); 
  //Debug_Print("Read Storage Data:0x%lx", DI, Tcb[Cur_Task_ID].Name); 
  Len = Get_Storage_Data_Len(SDI); 
  if(Len > 0)
  {
    //OS_TimeDly_Ms(20); //��ʱ���������񣬷�ֹĳ�����������������ռ��CPU
    Len1 = Read_Storage_Data_Fix_Len(SDI, 0, Len, pDst, pDst_Start, DstLen); 
    if(Len != Len1)
    {
      ASSERT_FAILED();
      Len1 = Read_Def_Para(SDI, pDst, Len, pDst_Start, DstLen); 
      if(Len != Len1)//ASSERT(Len1 EQ Len))
      {
        ASSERT_FAILED();
        return 0;
      }
      else
        return Len;
    }
    else
      return Len;
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }
}

//��ȡ����DI�Ķ����洢����
INT16U Read_Multi_Storage_Data(STORA_DI SDI, INT16U Num, void *pDst, void *pDst_Start, INT16U DstLen)
{
  INT16U i;
  INT16U Len;
  
  Len = 0;
  for(i = 0; i < Num; i ++)
  {
    Len += Read_Storage_Data(SDI + i, (INT8U *)pDst + Len, (INT8U *)pDst_Start, DstLen); 
  }
  
  return Len;
}

//��洢����дĳ�����ݣ�DI��ֵ�ɲο�Data_Para_Storage�Ķ���
//DI, ��Ҫд���������ʶ
//pPara����дĳЩ����������ʱ��Ҫ�Ĳ���������HIS_ENERGY, HIS_DEMAND, HIS_DEMAND_TIMEʱ��Ҫ����ʱ�����
//ʱ������ĸ�ʽ��������pPara[0]-pPara[4]�ֱ��Ƿ֡�ʱ���ա��¡���, ��������¸ò���������
//pSrc��ʾд���ݵ�Դ������
//����ֵ��1��ʾ�ɹ���������ʾʧ��
INT8U Write_Storage_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen)
{
  INT16U Len; 
  INT8U Re; 

  TRACE();

  //Cur_Task_ID = Get_Cur_Task_ID(); 
  //Debug_Print("Write Storage Data:0x%lx", DI, Tcb[Cur_Task_ID].Name); 
  //��ȡ���Ƚ����ݳ���
  Len = Get_Storage_Data_Len(SDI); 
  if(Len != SrcLen)//ASSERT(Len EQ SrcLen))
  {
    ASSERT_FAILED();
    Debug_Print("WR_Len Err, SDI = 0x%lx Len = %d, SrcLen = %d", SDI, Len, SrcLen);
    return 0;
  } 

  //дImp����
  //OS_Mutex_Pend(PUB_RW_ROM_ID); //����дROM���ź���ID
  Re = Write_Storage_Data_Fix_Len(SDI, 0, pSrc, SrcLen); 
  //OS_Mutex_Post(PUB_RW_ROM_ID); //�ͷŸ��ź���
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    return 0;
  } 
  return 1;
}

//���洢ӳ���Ƿ����, ��Ҫ�Ǽ��
void Check_Storage_Map()
{
  INT8U i, j, Count; 
  INT32U Size; 

  TRACE();
  //Re = Check_Mem_Map(); 
  //ASSERT(1 EQ Re); //����ڴ���������ӳ���Ƿ���ȷ
  //Get_Imp_Data_Size(IMP_0); 
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    Count = 0; 
    Size = Get_Imp_Data_Size(Data_Mem_Map[i].Imp_Flag); 
    for(j = 0; j < IMP_LOG_MEM; j ++)
    {
      if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
      {
        if(Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]) >= Size)
          Count ++ ;
        else
          ASSERT_FAILED();
      }
    }
    ASSERT((Data_Mem_Map[i].Imp_Flag EQ IMP_5 && Count >= 1) || \
       (Data_Mem_Map[i].Imp_Flag != IMP_5 && Count >= 2)); //ÿ������������2���洢�ռ�, ������һ������, �����������������
  }
}

//�������Ĵ洢��
INT8U Check_Imp_Data_Storage()
{
  INT8U i, j, Count, Test, Re;
  INT16U Re1; 
  INT32U DataSize, MemSize; 

  TRACE();

  Debug_Print("----Imp_LOG_MEM Map Check----");
  Re = 1;
  //�ȼ������ÿ��Imp_Flag�����ݵ��߼��洢���Ĵ�С�͸����Ƿ�Ϸ�
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    Count = 0; 
    DataSize = Get_Imp_Data_Size(Data_Mem_Map[i].Imp_Flag); 

    Debug_Print("Imp%d Data size=%ld", Data_Mem_Map[i].Imp_Flag, DataSize);

    for(j = 0; j < IMP_LOG_MEM; j ++)
    {
      if(Data_Mem_Map[i].LOG_Mem[j] != NULL_LOG_MEM)
      {
        MemSize = Get_LOG_Mem_Size(Data_Mem_Map[i].LOG_Mem[j]);

        Debug_Print("--Log_Mem%d size=%ld", Data_Mem_Map[i].LOG_Mem[j], MemSize); 

        if(MemSize >= DataSize)
          Count ++ ;
        else
        {
          Debug_Print("!!!!Imp%d Data size not enough space!!!!", Data_Mem_Map[i].Imp_Flag); 
          Re &= 0;
        }
      }
    }
    /*
                if((Count EQ 0))
                {
                Debug_Print("Imp%d Data do not have enough LOG Mems", Data_Mem_Map[i].Imp_Flag); 
                Re &= 0; 
                }
              */
  }
  /*  
    DataSize = 0; 
    MemSize = 0; 
    for(j = 0; j < S_NUM(Data_Mem_Map); j ++ )
    {
    i = Data_Mem_Map[j].Imp_Flag; 
    DataSize = Get_Imp_Data_Size(i); 
    MemSize = Get_Imp_Mem_Size(i); 
    Debug_Print("IMP%d Data_size = %ld, Mem_Size = %ld", i, DataSize, MemSize); 
    if(DataSize >= MemSize)
    {
    Debug_Print("IMP%d Data Mem not enough space!",i); 
    Re &= 0; 
    }
    }
  */ 
  if(JUDGE_POWER_OFF) //���������²����д洢����д�Լ�
    return Re;
  
  //��ÿ��IMP�����ݽ���һ�ζ���д����������
  for(i = 0; i < S_NUM(Data_Mem_Map); i ++)
  {
    Test = 0x5A; 
    Re = Write_Storage_Data(_SDI_CHK_IMP0 + i, &Test, 1); 
    if(1 EQ Re)
    {
      Test = 0; 
      Re1 = Read_Storage_Data(_SDI_CHK_IMP0 + i, &Test, &Test, sizeof(Test)); 
      if(0 != Re1 && 0x5A EQ Test)
        continue;
    }
    Debug_Print("IMP%d Data write && read test error", i); 
    Re &= 0;
  }
  return Re;
}

//��ӡ������Ϣ�������ݵĴ洢��ַ�ͳ��ȴ�ӡ����
void Debug_Print_Data_Storage()
{
  INT8U Imp_Flag; 
  INT16U i, j; 
  INT16U Num; 
  INT16U Addr, Len; 

  TRACE();

  Debug_Print("PRINT Data_Para_Storage Info-------------"); 
  for(Imp_Flag = IMP_0; Imp_Flag < IMP_5; Imp_Flag ++)
  {
    for(i = 0; i < S_NUM(Data_Para_Storage); i ++)
    {
      if(Data_Para_Storage[i].Imp_Flag EQ Imp_Flag)
      {
        if(Data_Para_Storage[i].Num EQ 0)
          Num = 1; //Data_Para_Storage[i].Num + 1; 
        else
          Num = Data_Para_Storage[i].Num; 

        for(j = 0; j < Num; j ++)
        {
          Addr = Get_Storage_Data_Off(Data_Para_Storage[i].SDI + j); 
          Len = Data_Para_Storage[i].Len; 
          Debug_Print("SDI:0x%lx, Addr:%d, Len:%d", \
           Data_Para_Storage[i].SDI + j, \
           Addr, \
           Len);
        }
      }
    }
  }
}

//��������洢ϵͳ�Ƿ���ȷ
void Check_Sys_Storage()
{
  INT8U Re;

  TRACE();

  if(Check_Meter_Factory_Status())
  {
    Debug_Print("------System Storage_SelfCheck Start!-----"); 
    //����洢����д���
    //����߼�������洢��֮���ӳ��
    //���IMP�����ݵĴ洢ӳ��
    //���Protocol_Data�Ĵ洢ӳ��
    Re = 1;
    //Re &= Check_PHY_Mem();
    Re &= Check_LOG_Mem_Map();
    Re &= Check_Imp_Data_Storage();
    Re &= Check_Protocol_Data_Storage();
    
    if(Re EQ 1)
    {
      Debug_Print("------System Storage_SelfCheck Succeeded!-----");
    }
    else
    {
      _Debug_Print("------System Storage_SelfCheck failed!-----");
      Beep_For_Para();
    }
  }
}

//��ȡ�����洢ϵͳ��У����Ϣ�����ж����洢�����Ƿ������޸�
INT32U Get_Storage_Info_CS()
{
  INT32U CS0, CS1, CS2, CS3;
   
  CS0 = Get_Sys_Mem_Info_CS();
  CS1 = Get_Def_Para_Info_CS();
  OS_Set_Sum((INT8U *)Data_Mem_Map, sizeof(Data_Mem_Map), &CS2, sizeof(CS2), &CS2, sizeof(CS2));
  OS_Set_Sum((INT8U *)Data_Para_Storage, sizeof(Data_Para_Storage), &CS3, sizeof(CS3), &CS3, sizeof(CS3));
 /* 
  Debug_Print("Sys_Mem_Info_CS = %lx", CS0);
  Debug_Print("Def_Para_Info_CS = %lx", CS1);
  Debug_Print("Data_Mem_Map CS = %lx", CS2);
  Debug_Print("Data_Para_Storage_CS = %lx", CS3);
  Debug_Print("All_CS = %lx", CS0 + CS1 + CS2 + CS3);
  */
  return CS0 + CS1 + CS2 + CS3;
}
#undef DATA_PARA_C

