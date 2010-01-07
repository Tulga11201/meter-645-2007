#ifndef METER_CFG_H
#define METER_CFG_H

#undef EXT
#ifdef METER_CFG_C
#define EXT
#else
#define EXT extern
#endif

//#define METER_DEBUG

//---�����Ļ�����̬----
#define NONET_METER  0x01//�������
#define CARRIER_METER  0x02//�ز������
#define GPRS_METER     0x04//GPRS�����

#define NOPREPAID_METER 0x10
#define CPU_CARD_METER  0x11
#define IIC_CARD_METER  0x12
#define ESAM_CARD_METER 0x13

#define PREPAID_LOCAL   0x00 //����Ԥ����
#define PREPAID_REMOTE  0x01 //Զ��Ԥ����

#define PREPAID_MONEY   0x00 //�����Ԥ����
#define PREPAID_ENG     0x01 //������Ԥ����

#define PREPAID_RATE    0x00 //��ʱԤ����
#define PREPAID_STEP    0x01 //����Ԥ����

#define SWITCH_INTER    0x00 //���ÿ��ط�ʽ
#define SWITCH_EXT      0x01 //�ⲿ���ط�ʽ

#define CS_BYTES    1//�ڴ�����Ҫ���ݽṹ���CS�ֽ���  
#define ROM_CS_BYTES  2//ROM�д洢���ݵ�У����ֽ���
#define MAX_RATES     4///��������

#define NET_METER     NONET_METER//CARRIER_METER//�Ƿ����������Ļ���������NOT_NET_METER��CARRIER_METER����GPRS_METER
#define PREPAID_METER 0 //�Ƿ���Ԥ���ѱ�? 0��ʾ���ǣ�1��ʾ��

#define SHELL_EN      0//shellʹ��

#define SET_ENERGY_EN 0//Mode_Word.Mode[0].Bit.Bit3 //�Ƿ��������ó�ʼ����

#define METER_CLR_EN        1 //Mode_Word.Mode[0].Bit.Bit1 //�Ƿ���������������?
#define NEG_ADD_POS_ACT_EN  0 //Mode_Word.Mode[0].Bit.Bit0 //�����й��Ƿ��������

#define POWER_CTRL_EN        0//Mode_Word.Mode[1].Bit.Bit3 //�Ƿ��и��ع���
#define RESUME_REMOTER_EN    0//Mode_Word.Mode[3].Bit.Bit4 //���⻽�Ѻ�ң���������Ƿ��,1�򿪣�0�ر�

#define YEAR_TABLE_SWITCH_EN 1//Mode_Word.Mode[2].Bit.Bit5 //�Ƿ�����������ʱ�����л�?
#define DATE_TABLE_SWITCH_EN 1//Mode_Word.Mode[2].Bit.Bit6 //�Ƿ�����������ʱ�α��л�?
#define RATE_SCH_SWITCH_EN   1 //Mode_Word.Mode[2].Bit.Bit7 //�Ƿ��������׷����л�?
#define STEP_SCH_SWITCH_EN   1 //�Ƿ������л����׽��ݷ���

#define PREPAID_EN            ((PREPAID_METER > 0)?1:0)//((PREPAID_METER > 0)?Mode_Word.Mode[1].Bit.Bit5:0) //Ԥ����ʹ��
#define PREPAID_MODE          PREPAID_MONEY//Mode_Word.Mode[1].Bit.Bit4////Ԥ����ģʽ��PREPAID_MONEY��ʾ����ͣ�PREPAID_ENG��ʾ������, ENERGY_TYPE
#define PREPAID_MONEY_MODE    PREPAID_RATE//Prepaid_Para.Mode[1].Bit.Bit4//PREPAID_RATE��ʾ��ʱ�Ʒѣ�PREPAID_STEP��ʾ���ݼƷ�
#define PREPAID_LOCAL_REMOTE  PREPAID_LOCAL//Prepaid_Para.Mode[1].Bit.Bit3//PREPAID_LOCAL��ʾ���أ�PREPAID_REMOTE��ʾԶ��

#define SWITCH_EXT_INTER   SWITCH_INTER //SWITCH_INTER��ʾ���ÿ��ط�ʽ,SWITCH_EXT��ʾ���ÿ��ط�ʽ

#define PREPAID_WARN_EN 1//Prepaid_Para.Mode[2].Bit.Bit7 //Ԥ�����������Ƿ��?
#define PREPAID_LIMIT1_WARN_EN    1//Prepaid_Para.Mode[2].Bit.Bit6 //��������1����ʹ��     
#define PREPAID_LIMIT2_WARN_EN    0//Prepaid_Para.Mode[2].Bit.Bit5//��������2����ʹ��
#define PREPAID_ZERO_WARN_EN  0//Prepaid_Para.Mode[2].Bit.Bit4 //����0����ʹ��
#define PREPAID_LIMIT2_SWITCH_EN 1//Prepaid_Para.Mode[0].Bit.Bit1//��������2��բʹ��
#define PREPAID_ZERO_SWITCH_EN  1//Prepaid_Para.Mode[2].Bit.Bit4//��������բʹ��

#define PREPAID_MAX_STEP      4 //����Ԥ��������ݶ�ֵ

#define SCHEME_SWITCH_MODE 1 //��ʱ������ʱ���л���ʽ,0��ʾ�л�ʱ����ǰ�����������л�ʱ����ø�������
                                //1��ʾֻҪ���л�ʱ��͸ı䷽��
#define LOAD_DATA_NUM      43000//�洢�ĸ�����������
#define LOAD_DATA_INDEX_HOUR_NUM 12 //ÿСʱ��������

#define DEMAND_ACCU_PHASE_NUM 1//(sizeof(Demand_Accu.Phase_Accu)/sizeof(Demand_Accu.Phase_Accu[0]))
#define APP_ENERG_EN   1      //�Ƿ������ڵ���
#define USE_ENERGY_RAM_BAK   1//�Ƿ����ڴ���ʹ��һ�ݵ������ݵı���

#define MAX_YEAR_PERIODS   14//�����ʱ����,��ʱ����ʾ��һ���Ϊ����ʱ���
#define MAX_DATE_TABLES   8//�����ʱ�α���,��ʱ�α�ʾ��һ��ֳɼ���ʱ���
#define MAX_DATE_PERIODS   14//ÿ��ʱ�α����ʱ����
#define MAX_YEAR_HOLIDAYS  40//ÿ����ʱ�����Ӧ�����ڼ�����,Ӧ��Ϊ15�ı���

#define MAX_AUTO_SCREEN_NUM 50  //�Զ�ѭ���������
#define MAX_KEY_SCREEN_NUM 100 //ѭ����ʾ�������

#define MAX_ENERGY_SETTLE_NUM 12 //��������������
#define MAX_DEMAND_SETTLE_NUM 12 //��������������
#define MAX_VOLSTAT_SETTLE_NUM 12 //��ѹͳ������������

#define PERIOD_FREEZE_NUM   12 //��ʱ�������
#define INSTANT_FREEZE_NUM  3 //˲ʱ�������

#define YEAR_TABLE_SWITCH_NUM 2 //��ʱ���л���¼����
#define DATE_TABLE_SWITCH_NUM 2 //��ʱ�α��л���¼����
#define RATE_SCH_SWITCH_NUM   2 //��ʱ�����л���¼����
#define STEP_SCH_SWITCH_NUM      2 //�ݶ��л���¼����

#define DATE_FREEZE_NUM 62 //�ն�����
#define HOUR_FREEZE_0_NUM 254 //Сʱ������,ֻ���ܵ���
//#define HOUR_FREEZE_1_NUM 168 //Сʱ��������

#define ENERGY_OVERTRUN_NUM 3 //������ת����

/////////////�¼���¼����///////////////////
#define LOSS_VOL_NUM   10 //ʧѹ��¼����
#define LOW_VOL_NUM    10 //Ƿѹ��¼����
#define OVER_VOL_NUM   10 //��ѹ��¼����
#define BREAK_VOL_NUM    10 //�����¼����

#define ALL_LOSS_VOL_NUM 10 //ȫʧѹ

#define AUX_POWER_DOWN_NUM   10 //������Դʧ��
#define VOL_REV_SEQ_NUM  10 //��ѹ������
#define CUR_REV_SEQ_NUM  10 //����������

#define VOL_UNBALANCE_NUM 10 //��ѹ��ƽ��
#define CUR_UNBALANCE_NUM 10 //������ƽ��

#define LOSS_CUR_NUM   10 //ʧ����¼����
#define OVER_CUR_NUM   10 //������¼����
#define BREAK_CUR_NUM    10 //������¼����
#define TREND_REVERSE_NUM  10 //���������¼����
#define OVER_LOAD_NUM    10 //���ؼ�¼����

#define POWER_DOWN_NUM   10 //����

#define POS_ACT_DEMAND_EXCEED_NUM   10  //�����й���������
#define NEG_ACT_DEMAND_EXCEED_NUM   10  //�����й���������
#define REA_DEMAND_EXCEED_NUM   10  //�޹���������



#define PROG_NUM   10 //���
#define CLEAR_METER_NUM  10 //�����0
#define CLEAR_DEMAND_NUM 10 //������0
#define CLEAR_EVENT_NUM  10 //�¼���0
#define ADJ_TIME_NUM   10 //Уʱ

#define DATE_TABLE_PROG_NUM   10  //ʱ�α���
#define YEAR_TABLE_PROG_NUM   10  //ʱ������
#define WEEK_REST_PROG_NUM    10  //�����ձ��
#define HOLIDAY_PROG_NUM      10  //�ڼ��ձ��
#define ACTIVE_COMB_PROG_NUM  10  //�й���ϱ��
#define REACTIVE_COMB_PROG_NUM 10  //�޹���ϱ��

#define SETTLE_TIME_PROG_NUM  10  //�����ձ��
#define OPEN_METER_COVER_NUM  10  //�����
#define OPEN_BOTTOM_COVER_NUM   10  //����ť��
#define PREPAID_ENERGY_NUM 10 //�����͹���
#define PREPAID_MONEY_NUM  10 //����͹���

#define RELAY_OFF_NUM 10 //��բ����
#define RELAY_ON_NUM  10 //��բ����

#define FACTOR_LOW_NUM 10 //�ܹ������س�����
//-------�����¼���¼------
#define LOWPWR_BAT_LOW_NUM 10 //�͹��ĵ��Ƿѹ
#define RTC_BAT_LOW_NUM 10 //ʱ�ӵ��Ƿѹ
#define PWR_CTRL_ALARM_NUM  0 //����������
#define PWR_CTRL_SWITCH_NUM 0 //��������բ
#define RESET_NUM       10 //��λ
#define RUN_CLOCK_ERR_NUM   10 //����ʱ����
#define EEROM_ERR_NUM   10 //EEROM��  

#define ADJ_METER_NUM   10 //У���¼
#define POWER_ON_CLOCK_ERR_NUM 10 //�ϵ�ʱ����
#define REMOTE_RELAY_SWITCH_NUM 10 //Զ������բ
#define SET_ENERG_NUM 0 //���ó�ʼ����



#define FAC_INFO "SZJJ"  //������Ϣ,���ڽ���
#define PROTOCOL_VERSION "DLT64507" //Э��汾��
#endif
