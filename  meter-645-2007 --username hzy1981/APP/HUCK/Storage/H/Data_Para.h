#ifndef DATA_PARA_H
#define DATA_PARA_H

//#include "Data_Trans.h"

#undef EXT
#ifdef DATA_PARA_C
#define EXT
#else
#define EXT extern
#endif

//����洢�ڵ�eerom�еĵ������ݵĴ�С
#define ENERGY_SAVE_SIZE sizeof(S_Energy)//(S_OFF(S_Energy,CS))

#define DEMAND_SAVE_SIZE (DEMAND_TIME_DATA_SIZE + ROM_CS_BYTES +\
    DEMAND_PHASE_DATA_SIZE + ROM_CS_BYTES +\
     (DEMAND_RATE_DATA_SIZE + ROM_CS_BYTES) * (INT32U)(MAX_RATES + 1))//����ĳ�����ʵ��������������������洢���е�ƫ��

#define LOAD_DATA_TIME_INDEX_NUM ((INT32U)LOAD_DATA_INDEX_HOUR_NUM*24*12*31)//ÿ15����һ����������,ÿСʱ4������




//---------------����������ݵĴ洢��ʾ-end-----------------------//


#define ADJ_METER_PARA_SIZE  256
#define LOAD_DATA_SIZE     32//ÿ�������������ݵĴ�С
//#define LOAD_DATA_INDEX_SIZE 5//ÿ��Сʱ�������ݵĴ�С
//#define LOAD_DATA_INDEX_NUM  8544//�������ߵ�Сʱ��������,ÿСʱһ�������Դ�8544��

#define PSW0_DI      0x0001//0�������ʶ��
#define PSW1_DI      0x0002//1�������ʶ��
#define PSW2 DI      0x0003//2�������ʶ��

#define NULL_IMP 0xFF //һ�������ڵ�IMP��־

#define IMP_0 0//��������       
#define IMP_1 1//��Ҫ����      
#define IMP_2 2//��ͨ����      
#define IMP_3 3//��Ҫ����
#define IMP_4 4//��Ҫ���ݵı���      
#define IMP_5 5//��ͨ����     
#define IMP_6 6//��ʷ����     
#define IMP_7 7//�¼��ۼ���Ϣ        
#define IMP_8 8//��0���¼�����Ƶ���������ݻ��       
#define IMP_9 9//��1���¼�������������Ƶ���������EEROM      
#define IMP_A 10//��2���¼����������󣬵��ǲ�Ƶ����һ���Flash       
#define IMP_B 11//���ɼ�¼����Flash      
#define IMP_C 12//����洢���ݣ���FRAM 

#define IMP_FAC_PARA  IMP_0 //�������� 
#define IMP_IMP_PARA  IMP_1 //��Ҫ����       
#define IMP_NOR_PARA  IMP_2 //��ͨ����      
#define IMP_IMP_DATA  IMP_3 //��Ҫ����       
#define IMP_IMP_BAK_DATA  IMP_4 //��Ҫ���ݵı���    
#define IMP_NOR_DATA  IMP_5 //��ͨ����
#define IMP_HIS_DATA  IMP_6 //��ʷ����      
#define IMP_EVENT_CUMU    IMP_7 //�¼��ۼ���Ϣ       
#define IMP_EVENT0    IMP_8 //��0���¼���������     
#define IMP_EVENT1    IMP_9 //��1���¼������������¼�    
#define IMP_EVENT2    IMP_A //�����           
#define IMP_LOAD_REC  IMP_B //���ɼ�¼����Flash     
#define IMP_PD_DATA   IMP_C //����洢���ݣ���FRAM 

//#define HIS_HEAD sizeof(S_HEX_Time) //�洢��ʷ������������ʱ��ͷ����

#define IMP_LOG_MEM 5 //ÿ��IMP���������ӵ�е��߼��洢������

//�洢������DI����ԭ��:���4λ����Ϊ0
//1��ʾ���������������
//2��ʾ��ʷ���߽�������
//3��ʾ�ִ��¼�����
//4��ʾ�ۼ��¼�����
#define NULL_S_DI      0xFFFFFFFF

//���3λ����������չ����
#define EXT_PARA_DATA  (0x10000000<<1)
#define EXT_HIS_DATA   (0x20000000<<1)
#define EXT_SEPA_EVENT (0x30000000<<1)
#define EXT_CUMU_EVENT (0x40000000<<1)

#define ES_DI(X) (X|EXT_SEPA_EVENT)//�ִ��¼�����DI
#define EC_DI(X) (X|EXT_CUMU_EVENT)//�ۼ��¼�����DI

#define SCREEN_ID_LEN 5 //������ʾ��ѭ����ʾID�����ݳ���

#define _SDI_BOOT_FLAG0    (0x00|EXT_PARA_DATA)  //IMP_CUR_DATA,4,1},//������־�������Ƿ��ǵ�һ������
#define _SDI_BOOT_FLAG    (0x01|EXT_PARA_DATA)  //IMP_CUR_DATA,4,1},//������־�������Ƿ��ǵ�һ������
//----------
//------------------
#define _SDI_CUR_ENERGY_PD    (0x02|EXT_PARA_DATA)//IMP6,ENERGY_SAVE_SIZE,1},//��ǰ����,����洢,ƽʱҲ��ʱ�洢
#define _SDI_CUR_DEMAND_PD    (0x03|EXT_PARA_DATA)//IMP6,sizeof(S_Demand),1},//����ֻ�����ܺ͵�ǰ������������S_Demand_

#define _SDI_CUR_VOLSTAT_PD          (0x04|EXT_PARA_DATA)//IMP6,sizeof(S_VolStat),1},//��ǰ��ѹͳ������
#define _SDI_TOTAL_VOLSTAT_PD        (0x05|EXT_PARA_DATA)//IMP6,sizeof(S_VolStat),1},//�ܵ�ѹ�������
#define _SDI_SAVE_PD_DATA_TIME       (0x06|EXT_PARA_DATA)//IMP6,4,�������������ʱ��
#define _SDI_EVENT_DATA_PD           (0x07|EXT_PARA_DATA)//IMP6,sizeof(Cur_Time1),1},//�������
//#define _SDI_CUR_YEAR_DATE_SCHEME_PD (0x08|EXT_PARA_DATA)//IMP6,��ǰ��ʱ����ʱ�η���
#define _SDI_TIME_BAK                (0x09|EXT_PARA_DATA)

#define _SDI_CUR_SCHEME (0x0A|EXT_PARA_DATA) //��ǰ��ʱ������ʱ�η���
#define _SDI_LOAD_DATA_INDEX_PD   (0x10|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_LoadData_Index),1},
//�������ߴ洢��Ϣ,ÿ�洢һ���������ߴ洢һ�θ�����,�洢Ƶ�������ѡ��FRAM��Ϊ�洢����
#define _SDI_LOAD_DATA_INDEX  (0x11|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_LoadData_Index),1},
#define _SDI_CUR_ENERGY   (0x12|EXT_PARA_DATA)//IMP6,ENERGY_SAVE_SIZE,1},//��ǰ����
#define _SDI_CUR_DEMAND   (0x13|EXT_PARA_DATA)//IMP6,DEMAND_SAVE_SIZE,1},//�����������


#define _SDI_CUR_VOLSTAT  (0x14|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//��ǰ��ѹͳ������

#define _SDI_CUR_PREPAID  (0x15|EXT_PARA_DATA) //Ԥ���������
//#define _SDI_TOTAL_VOLSTAT    (0x15|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//�ܵ�ѹ�������
//#define EVENT_CUMU//IMP_CUR_DATA,sizeof(S_Event_Cumu),1},//�¼��ۼ�����

//#define _SDI_METER_ADDR0  (0x16|EXT_PARA_DATA)//IMP_CUR_DATA,6,1},//�豸��ַ0
//#define _SDI_METER_ADDR1  (0x17|EXT_PARA_DATA)//IMP_CUR_DATA,6,1},//�豸��ַ1
//#define _SDI_METER_ADDR2  (0x18|EXT_PARA_DATA)//IMP_CUR_DATA,6,1},//�豸��ַ2

//#define _SDI_COMM_BAUD0   (0x20|EXT_PARA_DATA)//IMP_CUR_DATA,1,1},//��һ·������
//#define _SDI_COMM_BAUD1   (0x21|EXT_PARA_DATA)//IMP_CUR_DATA,1,1},//�ڶ�·������
//#define _SDI_COMM_BAUD2   (0x22|EXT_PARA_DATA)//IMP_CUR_DATA,1,1},//����·������

//#define _SDI_PASSWORD_0   (0x23|EXT_PARA_DATA)//IMP_CUR_DATA,3,1},//0������
//#define _SDI_PASSWORD_1   (0x24|EXT_PARA_DATA)//IMP_CUR_DATA,3,1},//1������
//#define _SDI_PASSWORD_2   (0x25|EXT_PARA_DATA)//IMP_CUR_DATA,3,1},//2������

#define _SDI_CUR_ENERGY_BAK0  (0x26|EXT_PARA_DATA)//IMP_CUR_DATA,ENERGY_SAVE_SIZE,1},//��ǰ��������,ƽʱ��ʱ�洢
#define _SDI_CUR_ENERGY_BAK1  (0x27|EXT_PARA_DATA)//IMP_CUR_DATA,ENERGY_SAVE_SIZE,1},//��ǰ��������,ƽʱ��ʱ�洢
#define _SDI_CUR_ENERGY_BAK2  (0x28|EXT_PARA_DATA)//IMP_HIS_DATA,ENERGY_SAVE_SIZE,1},//��ǰ��������,ƽʱ��ʱ�洢
#define _SDI_CUR_DEMAND_BAK   (0x29|EXT_PARA_DATA)//IMP_CUR_DATA,DEMAND_SAVE_SIZE,1},//��������������䷢��ʱ��
#define _SDI_CUR_VOLSTAT_BAK  (0x2A|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//��ǰ��ѹͳ�����ݱ���
//#define _SDI_TOTAL_VOLSTAT_BAK  (0x2B|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_VolStat),1},//�ܵ�ѹ������ݱ���

#define _SDI_ENERGY_FREEZE_TIME   (0x2C|EXT_PARA_DATA)//IMP_CUR_DATA,2,1},//���ڶ���ʱ��
#define _SDI_REACTIVE_FREEZE_TIME (0x2D|EXT_PARA_DATA)//IMP_CUR_DATA,2,1},//���ڶ���ʱ��

#define _SDI_PROG_RECORD  (0x2E|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(Prog_Record),1},//��̼�¼
#define _SDI_CLR_DEMAND_RECORD    (0x30|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(Clr_Demand_Record),1},//��������¼

#define _SDI_LOAD_DATA_INDEX_BAK  (0x31|EXT_PARA_DATA)//IMP_CUR_DATA,sizeof(S_LoadData_Index),1},//�������ߴ洢�������ݵ�

#define _SDI_LAST_SETTLE_ENERGY_DI (0x40|EXT_PARA_DATA) //�ϴν���������ݵĴ洢����
#define _SDI_SETTLE_ENERGY_DATA    (0x41|EXT_PARA_DATA) //�洢��������

#define _SDI_LAST_SETTLE_DEMAND_DI (0x50|EXT_PARA_DATA) //�ϴν����������ݵĴ洢����
#define _SDI_SETTLE_DEMAND_DATA    (0x51|EXT_PARA_DATA)

#define _SDI_LAST_SETTLE_VOLSTAT_DI (0x60|EXT_PARA_DATA)//�ϴν����ѹͳ�����ݵĴ洢����
#define _SDI_SETTLE_VOLSTAT_DATA  (0x61|EXT_PARA_DATA)

#define _SDI_REMOTE_RELAY_STATUS (0x70|EXT_PARA_DATA) //Զ�̿��Ƽ̵���״̬,ֵΪRELAY_ON����RELAY_OFF
#define _SDI_PREPAID_POWER_CTRL_RELAY_STATUS (0x71|EXT_PARA_DATA) //Ԥ���Ѹ��ɿ��Ƽ̵���״̬

#define _SDI_CTRL_STATUS_FLAG (0x72|EXT_PARA_DATA) //���Ʊ�־

#define _SDI_CHK_IMP0       (0x0100|EXT_PARA_DATA)
#define _SDI_CHK_IMP1       (0x0101|EXT_PARA_DATA)
#define _SDI_CHK_IMP2       (0x0102|EXT_PARA_DATA)
#define _SDI_CHK_IMP3       (0x0103|EXT_PARA_DATA)
#define _SDI_CHK_IMP4       (0x0104|EXT_PARA_DATA)
#define _SDI_CHK_IMP5       (0x0105|EXT_PARA_DATA)
#define _SDI_CHK_IMP6       (0x0106|EXT_PARA_DATA)
#define _SDI_CHK_IMP7       (0x0107|EXT_PARA_DATA)
#define _SDI_CHK_IMP8       (0x0108|EXT_PARA_DATA)
#define _SDI_CHK_IMP9       (0x0109|EXT_PARA_DATA)
#define _SDI_CHK_IMPA       (0x010A|EXT_PARA_DATA)
#define _SDI_CHK_IMPB       (0x010B|EXT_PARA_DATA)
#define _SDI_CHK_IMPC       (0x010C|EXT_PARA_DATA)

//-----------У�����------------
#define _SDI_ADJ_METER_PARA_STATUS      (0x0200|EXT_PARA_DATA)//У�����״̬����,1�ֽ�
#define _SDI_ADJ_METER_PUL_VOL_CUR_SPEC (0x0201|EXT_PARA_DATA)//���塢��ѹ���������,3�ֽ�
#define _SDI_ADJ_METER_A_POW            (0x0202|EXT_PARA_DATA)//A�๦�������������,3�ֽ�
#define _SDI_ADJ_METER_B_POW            (0x0203|EXT_PARA_DATA)//B�๦�������������,3�ֽ�
#define _SDI_ADJ_METER_C_POW            (0x0204|EXT_PARA_DATA)//C�๦�������������,3�ֽ�
#define _SDI_ADJ_METER_A_PHASE          (0x0205|EXT_PARA_DATA)//A����λ�����������,3�ֽ�
#define _SDI_ADJ_METER_B_PHASE          (0x0206|EXT_PARA_DATA)//B����λ�����������,3�ֽ�
#define _SDI_ADJ_METER_C_PHASE          (0x0207|EXT_PARA_DATA)//B����λ�����������,3�ֽ�
#define _SDI_ADJ_METER_A_VOL            (0x0208|EXT_PARA_DATA)//A���ѹ��������,3�ֽ�
#define _SDI_ADJ_METER_B_VOL            (0x0209|EXT_PARA_DATA)//B���ѹ��������,3�ֽ�
#define _SDI_ADJ_METER_C_VOL            (0x020A|EXT_PARA_DATA)//C���ѹ��������,3�ֽ�
#define _SDI_ADJ_METER_A_CUR            (0x020B|EXT_PARA_DATA)//A�������������,3�ֽ�
#define _SDI_ADJ_METER_B_CUR            (0x020C|EXT_PARA_DATA)//B�������������,3�ֽ�
#define _SDI_ADJ_METER_C_CUR            (0x020D|EXT_PARA_DATA)//C�������������,3�ֽ�
#define _SDI_ADJ_METER_CLR              (0x020E|EXT_PARA_DATA)//У����0,��������ռ�
#define _SDI_RD_ROM                     (0x0210|EXT_PARA_DATA)//��ȡROM�����ݱ�ʶ����������ռ�
//-------------------------------------

#define _SDI_PREPAID_RUN_STATUS (0x0300|EXT_PARA_DATA)//����״̬ ���ݳ���Ϊ1
#define _SDI_DISCRETE_INFO (0x0301|EXT_PARA_DATA)//��ɢ���� ���ݳ���Ϊ8
#define _SDI_PREPAID_PARA_CARD_VER (0x0302|EXT_PARA_DATA)//�ֳ��������ÿ��汾�� ���ݳ���Ϊ4
#define _SDI_PREPAID_PSW_KIND (0x0303|EXT_PARA_DATA)//��Կ�������ݳ���Ϊ1
#define _SDI_INVALID_CARD_COUNTS (0x0304|EXT_PARA_DATA)//�Ƿ����������
#define _SDI_INVALID_COUNTS_AllOW (0x0305|EXT_PARA_DATA)
#define _SDI_FAR_AUTH_DAY_FOLLOW (0x0306|EXT_PARA_DATA) //Զ�������֤������
#define _SDI_SINGLE_OR_COMPLEX_USER_KIND (0x0307|EXT_PARA_DATA) //�����߸�����
#define _SDI_FAR_PASSWORD_STATE (0x0308|EXT_PARA_DATA) //Զ�̱���Կ����

#define _SDI_LOAD_DATA_TIME_INDEX (0x100000|EXT_PARA_DATA)//IMP5,2,LOAD_DATA_TIME_INDEX_NUM},//���帺������Сʱ����,LOAD_DATA_TIME_INDEX_NUM��
#define _SDI_LOAD_DATA    (0x200000|EXT_PARA_DATA)//IMP5,LOAD_DATA_SIZE,LOAD_DATA_NUM},//���帺������,LOAD_DATA_NUM��//IMP_CUR_DATA,4,1},//������־�������Ƿ��ǵ�һ������
#define _SDI_LOAD_DATA_NEXT_INDEX (0x300000|EXT_PARA_DATA)

#define _SDI_CHG_CS  (0xFFFFFF | EXT_PARA_DATA)
//////////////////////////////////////////////////////

////////////////////������ͨ�ż��ݵĴ洢DI///////////////
#define SDI_BAT_RUN_TIME 0x0280000A  //��ع���ʱ��

#define SDI_DEMAND_PERIOD      0x04000103 //��������
#define SDI_DEMAND_SLID    0x04000104 //����ʱ��
#define SDI_ADJ_PULSE_WIDTH    0x04000105 //У��������
#define SDI_YEAR_SCHE_CHG_TIME   0x04000106 //��ʱ���л�ʱ��
#define SDI_DATE_SCHE_CHG_TIME   0x04000107 //��ʱ�α��л�ʱ��
#define SDI_RATE_SCHE_CHG_TIME   0x04000108 //���׷����л�ʱ��
#define SDI_STEP_SCHE_CHG_TIME   0x04000109 //���׽��ݷ����л�ʱ��

#define SDI_YEAR_PERIOD_NUM    0x04000201 //��ʱ����
#define SDI_DATE_TABLE_NUM     0x04000202 //��ʱ�α���
#define SDI_DATE_PERIOD_NUM    0x04000203 //��ʱ����
#define SDI_RATE_NUM   0x04000204 //������
#define SDI_HOLIDAY_NUM    0x04000205 //�����ڼ�����
#define SDI_HARMONIC_NUM   0x04000206 //г������
#define SDI_PREPAID_STEP_NUM 0x04000207 //Ԥ���ѽ��ݵ�۽�����

#define SDI_AUTO_CYCL_SCREEN_NUM 0x04000301 //�Զ�ѭ����ʾ����
#define SDI_SCREEN_SHOW_TIME   0x04000302 //û����ʾʱ��
#define SDI_ENERGY_DECIMAL_NUM   0x04000303 //��ʾ����С��λ��
#define SDI_POWER_DECIMAL_NUM    0x04000304 //��ʾ����������С��λ��
#define SDI_KEY_CYCL_SCREEN_NUM  0x04000305 //����ѭ����ʾ����
#define SDI_CURR_TRANS_RATIO     0x04000306 //�������������
#define SDI_VOLT_TRANS_RATIO     0x04000307 //��ѹ���������


#define SDI_COMM_ADDR      0x04000401 //ͨ�ŵ�ַ
#define SDI_METER_ID   0x04000402 //���
#define SDI_ASSET_ID   0x04000403 //�ʲ��������
#define SDI_RATED_VOL      0x04000404 //���ѹ
#define SDI_RATED_CUR      0x04000405 //�����
#define SDI_MAX_CUR    0x04000406 //������
#define SDI_ACTIVE_ACCU    0x04000407 //�й�׼ȷ�ȼ�
#define SDI_REACTIVE_ACCU      0x04000408 //�޹�׼ȷ�ȼ�
#define SDI_ACTIVE_CONST   0x04000409 //����й�����
#define SDI_REACTIVE_CONST     0x0400040A //����޹�����
#define SDI_METER_TYPE     0x0400040B //����ͺ�
#define SDI_METER_MADE_TIME    0x0400040C //�����������
#define SDI_PROTOCOL_VER   0x0400040D //���Э��汾��
#define SDI_CUTOMER_ID     0x0400040E //�ͻ����
//#define SDI_HARDWARE_VER   0x0400040F //Ӳ���汾��,�ö���δ��

#define SDI_ACTIVE_COMB_WORD   0x04000601 //�й���Ϸ�ʽ������
#define SDI_REACTIVE_COMB_WORD_1 0x04000602 //�޹���Ϸ�ʽ������1
#define SDI_REACTIVE_COMB_WORD_2 0x04000603 //�޹���Ϸ�ʽ������2

#define SDI_FAR_IRAD_BAUD      0x04000701 //���ƺ���Զ�����ٶ�������
#define SDI_NEAR_IRAD_BAUD     0x04000702 //�Ӵ�����������ٶ�������
#define SDI_COMM1_BAUD     0x04000703 //ͨ�ſ�1�ٶ�
#define SDI_COMM2_BAUD     0x04000704 //ͨ�ſ�2�ٶ�
#define SDI_COMM3_BAUD     0x04000705 //ͨ�ſ�3�ٶ�

#define SDI_WEEK_REST_DAY      0x04000801 //������������
#define SDI_WEEK_REST_DATE_TABLE 0x04000802 //��������ʱ�α��

#define SDI_LOAD_REC_WORD      0x04000901 //���ɼ�¼ģʽ��
#define SDI_FREEZE_REC_WORD    0x04000902 //�����¼ģʽ��

#define SDI_LOAD_REC_START_TIME  0x04000A01 //���ɼ�¼��ʼʱ��
#define SDI_LOAD_REC1_INTER_TIME 0x04000A02 //��һ�ฺ�ɼ�¼���ʱ��
#define SDI_LOAD_REC2_INTER_TIME 0x04000A03 //�ڶ��ฺ�ɼ�¼���ʱ��
#define SDI_LOAD_REC3_INTER_TIME 0x04000A04 //�����ฺ�ɼ�¼���ʱ��
#define SDI_LOAD_REC4_INTER_TIME 0x04000A05 //�����ฺ�ɼ�¼���ʱ��
#define SDI_LOAD_REC5_INTER_TIME 0x04000A06 //�����ฺ�ɼ�¼���ʱ��
#define SDI_LOAD_REC6_INTER_TIME 0x04000A07 //�����ฺ�ɼ�¼���ʱ��

#define SDI_MONTH_SETTLE_DAY1    0x04000B01 //ÿ�µ�һ������
#define SDI_MONTH_SETTLE_DAY2    0x04000B02 //ÿ�µڶ�������   
#define SDI_MONTH_SETTLE_DAY3    0x04000B03 //ÿ�µ���������

#define SDI_PSW0     0x04000C01 //��0������
#define SDI_PSW1     0x04000C02 //��1������
#define SDI_PSW2     0x04000C03 //��2������
#define SDI_PSW3     0x04000C04 //��3������
#define SDI_PSW4     0x04000C05 //��4������
#define SDI_PSW5     0x04000C06 //��5������
#define SDI_PSW6     0x04000C07 //��6������
#define SDI_PSW7     0x04000C08 //��7������
#define SDI_PSW8     0x04000C09 //��8������
#define SDI_PSW9     0x04000C0A //��9������

#define SDI_PHASE_A_CONDUC     0x04000D01 //A��絼��
#define SDI_PHASE_A_SUSCEP     0x04000D02 //A�������
#define SDI_PHASE_A_RESIST     0x04000D03 //A�������
#define SDI_PHASE_B_CONDUC     0x04000D04 //B��絼��
#define SDI_PHASE_B_SUSCEP     0x04000D05 //B�������
#define SDI_PHASE_B_RESIST     0x04000D06 //B�������
#define SDI_PHASE_C_CONDUC     0x04000D07 //C��絼��
#define SDI_PHASE_C_SUSCEP     0x04000D08 //C�������
#define SDI_PHASE_C_RESIST     0x04000D09 //C�������

#define SDI_POS_ACTIVE_UP_LIMIT  0x04000E01 //�����й���������
#define SDI_NEG_ACTIVE_LOW_LIMIT 0x04000E02 //�����й���������
#define SDI_VOL_UP_LIMIT   0x04000E03 //��ѹ����ֵ
#define SDI_VOL_LOW_LIMIT      0x04000E04 //��ѹ����

#define SDI_PREPAID_WARN_ENG1        0x04000F01 //��������1
#define SDI_PREPAID_WARN_ENG2        0x04000F02 //��������2
#define SDI_PREPAID_HOARD_ENG_LIMIT  0x04000F03 //�ڻ������޶�
#define SDI_PREPAID_OVERDRAFT_ENG_LIMIT 0x04000F04 //͸֧�����޶�

#define SDI_PREPAID_WARN_MONEY1           0x04001001 //�������1
#define SDI_PREPAID_WARN_MONEY2           0x04001002 //�������2
#define SDI_PREPAID_OVERDRAFT_MONEY_LIMIT 0x04001003 //͸֧����޶�
#define SDI_PREPAID_HOARD_MONEY_LIMIT     0x04001004 //�ڻ�����޶�
#define SDI_PREPAID_RELAY_ON_MONEY_LIMIT  0x04001005 //��բ��������ֵ

#define SDI_METER_RUN_STATUS  0x04001101 //�������״̬��

#define SDI_HOUR_FREEZE_START_TIME 0x04001201 //���㶳����ʼʱ��
#define SDI_HOUR_FREEZE_PERIOD     0x04001202 //���㶳����ʱ��
#define SDI_DATE_FREEZE_TIME       0x04001203 //�ն���ʱ��

#define SDI_RELAY_OFF_DELAY      0x04001401 //��բ��ʱ

#define SDI_POWER_PULSE          0x0400E001 //���ʸ���������
#define SDI_MAX_POWER_CALC_TIME  0x0400E002 //��󸺺ɼ���ʱ��
#define SDI_POWER_CTRL_RELAY_SWITCH_LIMIT 0x0400E003 //��������բ��������

#define SDI_DISP_FEE_DIGS        0x0400E101 //��ʾ���С��λ

#define SDI_PREPAID_MODEWORD_1   0x0400E201 //Ԥ����ģʽ��1
#define SDI_PREPAID_MODEWORD_2   0x0400E202 //Ԥ����ģʽ��2
#define SDI_PREPAID_MODEWORD_3   0x0400E203 //Ԥ����ģʽ��3

#define SDI_PREPAID_SEQ_NO       0x0400EB01 //ϵͳ���к�
#define SDI_PREPAID_USER_NO      0x0400EB02 //�û���
#define SDI_PREPAID_METER_NO     0x0400EB03 //���

#define SDI_SCHE1_YEAR_TABLE   0x04010000 //��һ��ʱ����
#define SDI_SCHE1_DATE_TABLE1    0x04010001 //��һ�׵�һ��ʱ�α�
#define SDI_SCHE1_DATE_TABLE2    0x04010002 //��һ��ʱ����ʱ�α�
#define SDI_SCHE1_DATE_TABLE3    0x04010003 //��һ��ʱ����ʱ�α�
#define SDI_SCHE1_DATE_TABLE4    0x04010004 //��һ��ʱ����ʱ�α�
#define SDI_SCHE1_DATE_TABLE5    0x04010005 //��һ��ʱ����ʱ�α�
#define SDI_SCHE1_DATE_TABLE6    0x04010006 //��һ��ʱ����ʱ�α�
#define SDI_SCHE1_DATE_TABLE7    0x04010007 //��һ��ʱ����ʱ�α�
#define SDI_SCHE1_DATE_TABLE8    0x04010008 //��һ��ʱ����ʱ�α�

#define SDI_SCHE2_YEAR_TABLE   0x04020000 //�ڶ���ʱ����
#define SDI_SCHE2_DATE_TABLE1    0x04020001 //�ڶ��׵�һ��ʱ�α�
#define SDI_SCHE2_DATE_TABLE2    0x04020002 //�ڶ���ʱ����ʱ�α�
#define SDI_SCHE2_DATE_TABLE3    0x04020003 //�ڶ���ʱ����ʱ�α�
#define SDI_SCHE2_DATE_TABLE4    0x04020004 //�ڶ���ʱ����ʱ�α�
#define SDI_SCHE2_DATE_TABLE5    0x04020005 //�ڶ���ʱ����ʱ�α�
#define SDI_SCHE2_DATE_TABLE6    0x04020006 //�ڶ���ʱ����ʱ�α�
#define SDI_SCHE2_DATE_TABLE7    0x04020007 //�ڶ���ʱ����ʱ�α�
#define SDI_SCHE2_DATE_TABLE8    0x04020008 //�ڶ���ʱ����ʱ�α�

#define SDI_HOLIDAY_DATE_TABLE   0x04030001 //�����ڼ��ռ���ʱ�α��
#define SDI_AUTO_CYCL_SREEN_DATA 0x04040101 //�Զ�ѭ����ʾ����
#define SDI_KEY_CYCL_SREEN_DATA  0x04040201 //����ѭ����ʾ����

#define SDI_RATE_SCHEME0_0       0x04050101 //��һ�׷��ʲ���
#define SDI_RATE_SCHEME1_0       0x04050201 //�ڶ��׷��ʲ���

#define SDI_STEP_SCHEME0_ENG     0x04060001 //��һ�׽��ݲ�������
#define SDI_STEP_SCHEME0_MONEY   0x04060101 //��һ�׽��ݲ������
#define SDI_STEP_SCHEME1_ENG     0x04060201 //�ڶ��׽��ݲ�������
#define SDI_STEP_SCHEME1_MONEY   0x04060301 //�ڶ��׽��ݲ������

#define SDI_HARDWARE_VERSION     0x04800002 //Ӳ���汾��
#define SDI_FAC_NO               0x04800003 //�����汾��

#define SDI_MODEWORD_1           0x0E000001 //ģʽ��1
#define SDI_MODEWORD_2           0x0E000002 //ģʽ��2
#define SDI_MODEWORD_3           0x0E000003
#define SDI_MODEWORD_4           0x0E000004
#define SDI_MODEWORD_5           0x0E000005

//#define SDI_PROG_EN_TIME         0x0E000206 //�����Чʱ��
#define SDI_OUTPUT_MODE          0x0E000206 //����һ���ģʽ��
#define SDI_PERIOD_FREEZE_TIME   0x0E000207//����ʱ��

#define SDI_ADJ_TIME_COUNTS      0x0E000208 //ÿ�չ㲥Уʱ����

#define SDI_LAST_LOSS_VOL_OCCUR_TIME 0x10000101 //���һ��ʧѹ����ʱ��
#define SDI_LAST_LOSS_VOL_END_TIME   0x10000201 //���һ��ʧѹ����ʱ��

///////////////////////
/*
#define IMP_ADJ   0x00 //��Ҫ����,У�������ģʽ��
#define IMP_ENERGY   0x01
#define IMP_HIS    0x02
#define IMP_EVENT    0x03
#define IMP_LOAD   0x04
#define IMP_POWD   0x05
*/
//������Ҫ���ø�����
/*
typedef struct
{
  INT8U Loss_Vol_Flag[4];
  INT32U Loss_Vol_Counts[4];//�ܡ�A��B��Cʧѹ���� 
  INT32U Loss_Vol_Time[4];//��ʧѹ�ۼ�ʱ��
  
  INT8U Loss_Cur_Flag[4];
  INT32U Loss_Cur_Counts[4];//��ʧ������
  INT32U Loss_Cur_Time[4];//��ʧ��ʱ��
  
  INT8U CS[CS_BYTES];
}S_Event_Cumu;
*/

typedef struct
{
    INT8U Imp_Flag;//���ݱ�־
    INT8U LOG_Mem[IMP_LOG_MEM];//��洢���߼��洢������һ����ԭʼ���ݣ��������Ǳ��ݣ�NULL_MEM��ʾû��
}S_Data_Mem_Map;

//#define RD_WR 0//�ɶ���д
#define WR 1   //ֻ��д
#define RD 2   //�ɶ�
/*
typedef struct
{
    INT8U Imp_Flag;
    INT32U Offset;
}S_Data_Para_Info;
*/

typedef struct
{
    //INT8U Stora_Property;//�洢����,0��ʾ��ʶ�����Զ���ģ�1��ʾ��ʶ����Э�����
    STORA_DI SDI; 
    //������ʶ,��DLT645���ݣ�ͬʱ�����䡣
    //INT8U RW_Flag;
    //������д��־����READ��ʾ�ɶ�����WRITE ��ʾ��д,READ|WRITE��ʾ�ɶ���д
    //INT8U PSW_Flag;
    //��������ȼ���־,PSW_N��ʾ��N���������ϲſ��޸ĸò���(N=0,1,2)
    INT8U Imp_Flag;
    //��Ҫ�ȼ���־ ��IMP_FACTORY_PARA��ʾ����Ҫ IMP_CUR_DATA->IMP5��Ҫ�����εݼ�
    INT16U Len; //���ݻ��������
    //�ɷ��ǼӶ�д��������������ɼ�ǿIMP��ͬ�Ĳ������ݴ�������
    INT32U Num;
    //�����ڴ���ĸ���
}S_Data_Para_Storage_Info;



EXT INT8U Check_SuperPSW_Jump();
EXT INT8U Check_Imp_Flag(INT8U Imp_Flag);
EXT INT8U Get_Storage_Data_ImpFlag(STORA_DI SDI);
EXT INT32U Get_Storage_Data_Off(STORA_DI SDI);
EXT INT16U Get_Storage_Data_Len(STORA_DI SDI);
EXT INT32U Get_Imp_Data_Size(INT8U Imp_Flag);
EXT INT32U Get_Imp_Mem_Size(INT8U Imp_Flag);
EXT INT8U Read_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pDst, INT16U RD_Len, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Imp_Data(INT8U Imp_Flag, INT32U Offset, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, INT16U Len, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Storage_Data_Fix_Len(STORA_DI SDI, INT16U Offset, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen);
EXT INT8U Write_Storage_Data(STORA_DI SDI, void* pSrc, INT16U SrcLen);

EXT INT16U Read_Multi_Storage_Data(STORA_DI SDI, INT16U Num, void *pDst, void *pDst_Start, INT16U DstLen);

//EXT INT16U Read_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr);
//EXT INT8U Write_HIS_Data(INT8U Data_Flag,S_HEX_Time *pTime,void *pSrc,INT16U SrcLen);
EXT INT8U Get_LOG_Mem_ImpFlag(INT8U Mem_No);
EXT void Check_Data_Storage();
EXT void Debug_Print_Data_Storage();
EXT void Check_Sys_Storage();
EXT INT32U Get_Storage_Info_CS();
#endif
