#define EVENT_CUMU_C
#include "Includes.h"
/*
CONST S_DI_Array NULL_DI_ARRAY =
{
  0, {0}
};
*/

#define NULL_DI_ARRAY Zero

CONST S_DI_Array Event_DI_Array[] =
{
  //{.DI_Num=19,{0x9010,0x9110,0x9020,0x9120,0xE701,0xE704,0xE707,0xE70A,0xE702,0xE705,0xE708,0xE70B,0xE703,0xE706,0xE709,0xE70C,DI_A_AH,DI_B_AH,DI_C_AH}},//ʧѹ
  //{.DI_Num=16,{0x9010,0x9110,0x9020,0x9120,0xE701,0xE704,0xE707,0xE70A,0xE702,0xE705,0xE708,0xE70B,0xE703,0xE706,0xE709,0xE70C}},//ʧ��
  //{.DI_Num=8,{0x9010,0x9020,0xE701,0xE707,0xE702,0xE708,0xE703,0xE709}},//����
  //{.DI_Num=0,{0}}//ȫʧѹ��ȫʧ��������ֻ�ƴ�����ʱ��

  //ʧѹ�����ࡢʧ��������
  { 20,{
  0x00010000,   //�����й���, 4
  0x00020000,   //�����й���, 4
  0x00030000,   //����޹�1, 4
  0x00040000,   //����޹�2, 4

  0x00150000,   //A�������й���, 4
  0x00160000,   //A�෴���й���, 4
  0x00170000,   //A������޹�1,  4
  0x00180000,   //A������޹�2,  4

  0x00290000,   //B�������й���
  0x002A0000,   //B�෴���й���
  0x002B0000,   //B������޹�1
  0x002C0000,   //B������޹�2

  0x003D0000,   //C�������й���
  0x003E0000,   //C�෴���й���
  0x003F0000,   //C������޹�1
  0x00400000,   //C������޹�2

  _PDI_TOTAL_AH,
  _PDI_A_AH,
  _PDI_B_AH,
  _PDI_C_AH
  }
  }
  /*
  {16,
  {
  0x00010000,   //�����й���, 4
  0x00020000,   //�����й���, 4
  0x00030000,   //����޹�1, 4
  0x00040000,   //����޹�2, 4

  0x00150000,   //A�������й���, 4
  0x00160000,   //A�෴���й���, 4
  0x00170000,   //A������޹�1,  4
  0x00180000,   //A������޹�2,  4

  0x00290000,   //B�������й���
  0x002A0000,   //B�෴���й���
  0x002B0000,   //B������޹�1
  0x002C0000,   //B������޹�2

  0x003D0000,   //C�������й���
  0x003E0000,   //C�෴���й���
  0x003F0000,   //C������޹�1
  0x00400000,   //C������޹�2

  },
  }
  */
};
/*
//�����¼����ۼӴ���
typedef struct{
  INT8U Event_ID;//�¼� ID
  
  //�¼����ۼ�ʱ��ʹ�����Ҫ���⴦��
  STORA_DI Counts_DI;//�����ۼ�DI,��ͬ��ͨ��Э��DI
  INT8U Counts_Start;
  INT8U Counts_Len;
  
  STORA_DI Mins_DI;//ʱ���ۼ�DI,��ͬ��ͨ��Э��DI
  INT8U Mins_Start;
  INT8U Mins_Len;
  
  ///////////////////////���沿����ʱ��ʹ������ۼӣ���׼��Լ���涼�е�//////////////////////////////
  
  ///////////////////////���沿���ǵ��ܵ����ۼ�///////////////////////////
  STORA_DI Occur_Stora_DI;//����ʱ�ĵ������ݴ洢DI
  STORA_DI Total_Stora_DI;//�ܵĵ������ݵ�DI,��ͬ��Э��DI
  
  INT8U DI_Num;//������ĸ���,�������ۼ�ʱ��ʹ������ۼ�ʱ��ʹ����Ƿ������Counts_Mins_Proto_Flag����
  //INT8U Counts_Mins_Proto_Flag;//������ʱ���Ƿ����Э������?
  
  PROTO_DI *pDI;//�ۼ���ص�������,��ͨ��Э���������ͬ
  
  }S_Event_Cumu_Data_Info;
*/
CONST S_Event_Cumu_Data_Info Event_Cumu_Data_Info[] =
{
  //��ʧѹ
  {INIT(Event_ID, ID_EVENT_TOTAL_LOSS_VOL),
  INIT(Occur_Stora_DI, EC_DI(0x10000100)),
  INIT(Total_Stora_DI, EC_DI(0x10000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A��ʧѹ
  {INIT(Event_ID, ID_EVENT_A_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x10010100)),
  INIT(Total_Stora_DI, EC_DI(0x10010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B��ʧѹ
  {INIT(Event_ID, ID_EVENT_B_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x10020100)),
  INIT(Total_Stora_DI, EC_DI(0x10020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C��ʧѹ
  {INIT(Event_ID, ID_EVENT_C_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x10030100)),
  INIT(Total_Stora_DI, EC_DI(0x10030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //A��Ƿѹ
  {INIT(Event_ID, ID_EVENT_A_VOLT_LESS),
  INIT(Occur_Stora_DI, EC_DI(0x11010100)),
  INIT(Total_Stora_DI, EC_DI(0x11010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B��Ƿѹ
  {INIT(Event_ID, ID_EVENT_B_VOLT_LESS),
  INIT(Occur_Stora_DI, EC_DI(0x11020100)),
  INIT(Total_Stora_DI, EC_DI(0x11020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C��Ƿѹ
  {INIT(Event_ID, ID_EVENT_C_VOLT_LESS),
  INIT(Occur_Stora_DI, EC_DI(0x11030100)),
  INIT(Total_Stora_DI, EC_DI(0x11030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //A���ѹ
  {INIT(Event_ID, ID_EVENT_A_VOLT_OVERLOAD),
  INIT(Occur_Stora_DI, EC_DI(0x12010100)),
  INIT(Total_Stora_DI, EC_DI(0x12010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B���ѹ
  {INIT(Event_ID, ID_EVENT_B_VOLT_OVERLOAD),
  INIT(Occur_Stora_DI, EC_DI(0x12020100)),
  INIT(Total_Stora_DI, EC_DI(0x12020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C���ѹ
  {INIT(Event_ID, ID_EVENT_C_VOLT_OVERLOAD),
  INIT(Occur_Stora_DI, EC_DI(0x12030100)),
  INIT(Total_Stora_DI, EC_DI(0x12030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //�ܶ���
  {INIT(Event_ID, ID_EVENT_TOTAL_BREAK_VOL),
  INIT(Occur_Stora_DI, EC_DI(0x13000100)),
  INIT(Total_Stora_DI, EC_DI(0x13000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A�����
  {INIT(Event_ID, ID_EVENT_A_LOSS_PARSE),
  INIT(Occur_Stora_DI, EC_DI(0x13010100)),
  INIT(Total_Stora_DI, EC_DI(0x13010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B�����
  {INIT(Event_ID, ID_EVENT_B_LOSS_PARSE),
  INIT(Occur_Stora_DI, EC_DI(0x13020100)),
  INIT(Total_Stora_DI, EC_DI(0x13020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C�����
  {INIT(Event_ID, ID_EVENT_C_LOSS_PARSE),
  INIT(Occur_Stora_DI, EC_DI(0x13030100)),
  INIT(Total_Stora_DI, EC_DI(0x13030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //ȫʧѹ
  {INIT(Event_ID, ID_EVENT_ALL_LOSS_VOLT),
  INIT(Occur_Stora_DI, EC_DI(0x03050000)),
  INIT(Total_Stora_DI, EC_DI(0x03050001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //������Դʧ��
  {INIT(Event_ID, ID_EVENT_AUX_POWER),
  INIT(Occur_Stora_DI, EC_DI(0x03060000)),
  INIT(Total_Stora_DI, EC_DI(0x03060001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
  //��ѹ������
  {INIT(Event_ID, ID_EVENT_VOLT_NEG_SEQ),
  INIT(Occur_Stora_DI, EC_DI(0x14000100)),
  INIT(Total_Stora_DI, EC_DI(0x14000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //����������
  {INIT(Event_ID, ID_EVENT_CUR_NEG_SEQ),
  INIT(Occur_Stora_DI, EC_DI(0x15000100)),
  INIT(Total_Stora_DI, EC_DI(0x15000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //��ѹ��ƽ��
  {INIT(Event_ID, ID_EVENT_VOLT_NO_EVEN),
  INIT(Occur_Stora_DI, EC_DI(0x16000100)),
  INIT(Total_Stora_DI, EC_DI(0x16000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //������ƽ��
  {INIT(Event_ID, ID_EVENT_CURR_NO_EVEN),
  INIT(Occur_Stora_DI, EC_DI(0x17000100)),
  INIT(Total_Stora_DI, EC_DI(0x17000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //��ʧ��
  {INIT(Event_ID, ID_EVENT_TOTAL_LOSS_CUR),
  INIT(Occur_Stora_DI, EC_DI(0x18000100)),
  INIT(Total_Stora_DI, EC_DI(0x18000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A��ʧ��
  {INIT(Event_ID, ID_EVENT_A_LOSS_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x18010100)),
  INIT(Total_Stora_DI, EC_DI(0x18010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B��ʧ��
  {INIT(Event_ID, ID_EVENT_B_LOSS_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x18020100)),
  INIT(Total_Stora_DI, EC_DI(0x18020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C��ʧ��
  {INIT(Event_ID, ID_EVENT_C_LOSS_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x18030100)),
  INIT(Total_Stora_DI, EC_DI(0x18030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //A�����
  {INIT(Event_ID, ID_EVENT_A_OVER_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x19010100)),
  INIT(Total_Stora_DI, EC_DI(0x19010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B�����
  {INIT(Event_ID, ID_EVENT_B_OVER_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x19020100)),
  INIT(Total_Stora_DI, EC_DI(0x19020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C�����
  {INIT(Event_ID, ID_EVENT_C_OVER_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x19030100)),
  INIT(Total_Stora_DI, EC_DI(0x19030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //A�����
  {INIT(Event_ID, ID_EVENT_A_CUT_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1A010100)),
  INIT(Total_Stora_DI, EC_DI(0x1A010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B�����
  {INIT(Event_ID, ID_EVENT_B_CUT_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1A020100)),
  INIT(Total_Stora_DI, EC_DI(0x1A020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C�����
  {INIT(Event_ID, ID_EVENT_C_CUT_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1A030100)),
  INIT(Total_Stora_DI, EC_DI(0x1A030100)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},


  //�ܷ���
  {INIT(Event_ID, ID_EVENT_TOTAL_NEG_CUR),
  INIT(Occur_Stora_DI, EC_DI(0x1B000100)),
  INIT(Total_Stora_DI, EC_DI(0x1B000101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //A�ೱ������
  {INIT(Event_ID, ID_EVENT_A_NEG_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1B010100)),
  INIT(Total_Stora_DI, EC_DI(0x1B010101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //B�ೱ������
  {INIT(Event_ID, ID_EVENT_B_NEG_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1B020100)),
  INIT(Total_Stora_DI, EC_DI(0x1B020101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},
  //C�ೱ������
  {INIT(Event_ID, ID_EVENT_C_NEG_CURR),
  INIT(Occur_Stora_DI, EC_DI(0x1B030100)),
  INIT(Total_Stora_DI, EC_DI(0x1B030101)),
  (S_DI_Array*) &Event_DI_Array[0],
  INIT(Clr_Flag,1)},

  //A�����
  {INIT(Event_ID, ID_EVENT_A_POWER_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x1C010100)),
  INIT(Total_Stora_DI, EC_DI(0x1C010101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //B�����
  {INIT(Event_ID, ID_EVENT_B_POWER_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x1C020100)),
  INIT(Total_Stora_DI, EC_DI(0x1C020101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //C�����
  {INIT(Event_ID, ID_EVENT_C_POWER_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x1C030100)),
  INIT(Total_Stora_DI, EC_DI(0x1C030101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //��բ
  {INIT(Event_ID, ID_EVENT_RELAY_OFF),
  INIT(Occur_Stora_DI, EC_DI(0x1D000100)),
  INIT(Total_Stora_DI, EC_DI(0x1D000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)}, 
  //��բ
  {INIT(Event_ID, ID_EVENT_RELAY_ON),
  INIT(Occur_Stora_DI, EC_DI(0x1E000100)),
  INIT(Total_Stora_DI, EC_DI(0x1E000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�ܹ������س�����
  {INIT(Event_ID, ID_EVENT_ALL_FACTOR_LOW),
  INIT(Occur_Stora_DI, EC_DI(0x1F000100)),
  INIT(Total_Stora_DI, EC_DI(0x1F000101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
  //����
  {INIT(Event_ID, ID_EVENT_POWER_OFF),
  INIT(Occur_Stora_DI, EC_DI(0x03110000)),
  INIT(Total_Stora_DI, EC_DI(0x03110001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //�����й���������
  {INIT(Event_ID, ID_EVENT_POS_ACT_DEMAND_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x03120100)),
  INIT(Total_Stora_DI, EC_DI(0x03120101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�����й���������
  {INIT(Event_ID, ID_EVENT_NEG_ACT_DEMAND_EXCEED),
  INIT(Occur_Stora_DI, EC_DI(0x03120200)),
  INIT(Total_Stora_DI, EC_DI(0x03120201)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //��һ�����޹���������
  {INIT(Event_ID, ID_EVENT_Q1_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120300)),
  INIT(Total_Stora_DI, EC_DI(0x03120301)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�ڶ������޹���������
  {INIT(Event_ID, ID_EVENT_Q2_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120400)),
  INIT(Total_Stora_DI, EC_DI(0x03120401)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //���������޹���������
  {INIT(Event_ID, ID_EVENT_Q3_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120500)),
  INIT(Total_Stora_DI, EC_DI(0x03120501)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //���������޹���������
  {INIT(Event_ID, ID_EVENT_Q4_REAC_DEMAND_EXCEED ),
  INIT(Occur_Stora_DI, EC_DI(0x03120600)),
  INIT(Total_Stora_DI, EC_DI(0x03120601)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //��̼�¼
  {INIT(Event_ID, ID_EVENT_PROG),
  INIT(Occur_Stora_DI, EC_DI(0x03300000)),
  INIT(Total_Stora_DI, EC_DI(0x03300001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //��������¼
  {INIT(Event_ID, ID_EVENT_CLR_ALL_DATA),
  INIT(Occur_Stora_DI, EC_DI(0x03300100)),
  INIT(Total_Stora_DI, EC_DI(0x03300101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,0)},

  //���������¼
  {INIT(Event_ID, ID_EVENT_CLR_DEMAND_COM),
  INIT(Occur_Stora_DI, EC_DI(0x03300200)),
  INIT(Total_Stora_DI, EC_DI(0x03300201)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //�¼������¼
  {INIT(Event_ID, ID_EVENT_CLR_PROCESS),
  INIT(Occur_Stora_DI, EC_DI(0x03300300)),
  INIT(Total_Stora_DI, EC_DI(0x03300301)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,0)},

  //Уʱ��¼
  {INIT(Event_ID, ID_EVENT_ADJUST_TIME),
  INIT(Occur_Stora_DI, EC_DI(0x03300400)),
  INIT(Total_Stora_DI, EC_DI(0x03300401)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //ʱ�α����
  {INIT(Event_ID, ID_EVENT_DATE),
  INIT(Occur_Stora_DI, EC_DI(0x03300500)),
  INIT(Total_Stora_DI, EC_DI(0x03300501)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //ʱ�������
  {INIT(Event_ID, ID_EVENT_YEAR),
  INIT(Occur_Stora_DI, EC_DI(0x03300600)),
  INIT(Total_Stora_DI, EC_DI(0x03300601)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //�����ձ��
  {INIT(Event_ID, ID_EVENT_WEEK),
  INIT(Occur_Stora_DI, EC_DI(0x03300700)),
  INIT(Total_Stora_DI, EC_DI(0x03300701)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�ڼ��ձ��
  {INIT(Event_ID, ID_EVENT_HOLIDAY),
  INIT(Occur_Stora_DI, EC_DI(0x03300800)),
  INIT(Total_Stora_DI, EC_DI(0x03300801)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�й���Ϸ�ʽ���
  {INIT(Event_ID, ID_EVENT_ACPWR),
  INIT(Occur_Stora_DI, EC_DI(0x03300900)),
  INIT(Total_Stora_DI, EC_DI(0x03300901)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�޹���Ϸ�ʽ1���
  {INIT(Event_ID, ID_EVENT_REACPWR1),
  INIT(Occur_Stora_DI, EC_DI(0x03300A00)),
  INIT(Total_Stora_DI, EC_DI(0x03300A01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�޹���Ϸ�ʽ2���
  {INIT(Event_ID, ID_EVENT_REACPWR2),
  INIT(Occur_Stora_DI, EC_DI(0x03300B00)),
  INIT(Total_Stora_DI, EC_DI(0x03300B00)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //�����ձ��
  {INIT(Event_ID, ID_EVENT_SETTLE_DATE),
  INIT(Occur_Stora_DI, EC_DI(0x03300C00)),
  INIT(Total_Stora_DI, EC_DI(0x03300C01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //������
  {INIT(Event_ID, ID_EVENT_UP_COVER_OPEN),
  INIT(Occur_Stora_DI, EC_DI(0x03300D00)),
  INIT(Total_Stora_DI, EC_DI(0x03300D01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  //����ť��
  {INIT(Event_ID, ID_EVENT_DOWN_COVER_OPEN),
  INIT(Occur_Stora_DI, EC_DI(0x03300E00)),
  INIT(Total_Stora_DI, EC_DI(0x03300E01)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},


  //�͹��ĵ��Ƿѹ
  {INIT(Event_ID, ID_EVENT_LOWPWR_BAT_LOW),
  INIT(Occur_Stora_DI, EC_DI(0x03410000)),
  INIT(Total_Stora_DI, EC_DI(0x03410001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},

  //ʱ�ӵ��Ƿѹ
  {INIT(Event_ID, ID_EVENT_RTC_BAT_LOW),
  INIT(Occur_Stora_DI, EC_DI(0x03410100)),
  INIT(Total_Stora_DI, EC_DI(0x03410101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //���ر���
  {INIT(Event_ID, ID_EVENT_DEMAND_ALARM),
  INIT(Occur_Stora_DI, EC_DI(0x03420000)),
  INIT(Total_Stora_DI, EC_DI(0x03420001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
/*
  //������բ
  {INIT(Event_ID, ID_EVENT_DEMAND_SWITCH),
  INIT(Occur_Stora_DI, EC_DI(0x03420100)),
  INIT(Total_Stora_DI, EC_DI(0x03420101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
*/
  //��λ
  {INIT(Event_ID, ID_EVENT_RESET),
  INIT(Occur_Stora_DI, EC_DI(0x0E180000)),
  INIT(Total_Stora_DI, EC_DI(0x0E180001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //����ʱ����
  {INIT(Event_ID, ID_EVENT_RTCERR_RUN),
  INIT(Occur_Stora_DI, EC_DI(0x0E190000)),
  INIT(Total_Stora_DI, EC_DI(0x0E190001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},
  
  //�ϵ�ʱ����
  {INIT(Event_ID, ID_EVENT_RTCERR_PWRON),
  INIT(Occur_Stora_DI, EC_DI(0x0E1C0000)),
  INIT(Total_Stora_DI, EC_DI(0x0E1C0001)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,1)},  
  
  //���ó�ʼ����
  {INIT(Event_ID, ID_EVENT_SET_ENERG),
  INIT(Occur_Stora_DI, EC_DI(0x0E301100)),
  INIT(Total_Stora_DI, EC_DI(0x0E301101)),
  (S_DI_Array*) NULL_DI_ARRAY,
  INIT(Clr_Flag,0)},

  EXTEND_EVENT_CUMU
}; 

//���¼������¼��Ķ�Ӧ��ϵ
CONST INT8U Single_Total_Event_Map[][2] =
{
  //ʧѹ
  {ID_EVENT_A_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  {ID_EVENT_B_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  {ID_EVENT_C_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_AB_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_AC_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_BC_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  //{ID_EVENT_ABC_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL}, 
  {ID_EVENT_ALL_LOSS_VOLT, ID_EVENT_TOTAL_LOSS_VOL},
  //ʧ��
  {ID_EVENT_A_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  {ID_EVENT_B_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  {ID_EVENT_C_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_AB_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_AC_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_BC_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //{ID_EVENT_ALL_LOSS_CURR, ID_EVENT_TOTAL_LOSS_CUR}, 
  //����
  {ID_EVENT_A_NEG_CURR, ID_EVENT_TOTAL_NEG_CUR}, 
  {ID_EVENT_B_NEG_CURR, ID_EVENT_TOTAL_NEG_CUR}, 
  {ID_EVENT_C_NEG_CURR, ID_EVENT_TOTAL_NEG_CUR},
  //����
  {ID_EVENT_A_LOSS_PARSE, ID_EVENT_TOTAL_BREAK_VOL},
  {ID_EVENT_B_LOSS_PARSE, ID_EVENT_TOTAL_BREAK_VOL}, 
  {ID_EVENT_C_LOSS_PARSE, ID_EVENT_TOTAL_BREAK_VOL}, 
};

//�ж�ĳ���ۼ��¼��Ƿ��ڷ�����������һ���¼�
INT8U Check_Cumu_Event_Occuring(INT8U Event_ID)
{
  INT8U i;

  TRACE();
  for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
  {
    if(Single_Total_Event_Map[i][0] == Event_ID || \
       Single_Total_Event_Map[i][1] == Event_ID)
    {
      if(Read_Event_Status(Single_Total_Event_Map[i][0]))
      {
        return 1;
      }
    }
  }
  return 0;
}

//��ȡĳһ�¼���Ӧ�����¼�ID
INT8U Get_Total_Event_ID(INT8U Event_ID)
{
  INT8U i;

  TRACE();
  for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
  {
    if(Single_Total_Event_Map[i][0] == Event_ID || \
       Single_Total_Event_Map[i][1] == Event_ID)
    {
      return Single_Total_Event_Map[i][1];
    }
  }
  return NULL_EVENT_ID;
}

//���ĳ���¼�ID�Ƿ���һ���ۼ��¼�ID
INT8U Check_Total_Event_ID(INT8U Event_ID)
{
	INT8U i;

    TRACE();
	
	for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
	{
		if(Single_Total_Event_Map[i][1] EQ Event_ID)
		{
			return 1;
		}
	}
	return 0; 
}

//��ȡĳ�����¼���Ӧ�ĵ����¼����ڷ����ĸ���
INT8U Get_Event_Total_Occuring_Singles(INT8U Event_ID)
{
	INT8U i;
	INT8U Counts;

    TRACE();	
	Counts = 0;
	for(i = 0; i < S_NUM(Single_Total_Event_Map); i ++)
	{
		if(Single_Total_Event_Map[i][1] EQ Event_ID)//���¼�
		{
			if(Read_Event_Status(Single_Total_Event_Map[i][0]))
				Counts ++;
		}
	}  
	return Counts;
}

//��ȡЭ�����ݣ�ר���¼��ṩ����������3λС������ֹ������.
//DI��ʶ��
//DI_Num��ʶ����
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�Ŀ�껺����
INT16U Get_Multi_Proto_Data(PROTO_DI PDI[], INT8U DI_Num, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT8U i, Next_Flag;
  INT16U Len, TempLen;

  TRACE();

  Len = 0;

  if(!(pDst >= pDst_Start && pDst < pDst_Start + DstLen))
  {
	  ASSERT_FAILED();
	  return 0;
  }

  for(i = 0; i < DI_Num; i ++)
  {
    TempLen = _Get_DLT645_Data(PDI[i], (void *) 0, 0, pDst + Len, pDst_Start, DstLen, Data_Flag, &Next_Flag);  
    if(TempLen EQ 0)
      ASSERT_FAILED();
    Len += TempLen;
  }

  return Len;
}

//��ȡĳ���¼���Event_Cumu_Data_Info�е����� 
//Event_ID��ʾʱ���ID
INT16U Get_Event_Cumu_Data_Index(INT8U Event_ID)
{
  INT16U i;

  TRACE();

  for(i = 0; i < S_NUM(Event_Cumu_Data_Info); i++)
  {
    if(Event_Cumu_Data_Info[i].Event_ID EQ Event_ID)
    {
      return i;
    }
  }

  return NULL_2BYTES;
}

//��ȡĳ���ۼ��¼����ۼ�������Event_Cumu_Data_Info�е�����
//PDI��ʾЭ���е�����ֵ
INT16U Get_Event_Cumu_Proto_Index(PROTO_DI PDI)
{
  INT16U i;

  TRACE();
  for(i = 0; i < S_NUM(Event_Cumu_Data_Info); i ++)
  {
    if(Event_Cumu_Data_Info[i].Total_Stora_DI EQ PDI)
    {
      return i;
    }
  }

  return NULL_2BYTES;
}
/*
//���¼��ۼƴ����Ĵ���
//Index��ʾEvent_Cumu_Data_Info�е�����
void Event_Cumu_Counts_Proc(INT16U Index, INT32U Counts, INT8U Flag)
{
  //INT32U Counts;
  INT16U Len, Len1;

  TRACE();

  if(Flag != EVENT_REAL)
  {
    return;
  }

  if(Event_Cumu_Data_Info[Index].Counts_DI EQ NULL_STORA_DI)//����Ҫ������
  {
    return;
  }

  Len1 = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Counts_DI);
  mem_set(Pub_Buf0, 0, Len1, Pub_Buf0, sizeof(Pub_Buf0));
  //��ȡ������д�ۼƴ���
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Counts_DI, Pub_Buf0, Pub_Buf0, sizeof(Pub_Buf0));
  ASSERT(Len1 EQ Len);

  if(!((INT16U) (Event_Cumu_Data_Info[Index].Counts_Start + Event_Cumu_Data_Info[Index].Counts_Len) <= Len))
  {
    mem_set(Pub_Buf0, 0, Len, Pub_Buf0, sizeof(Pub_Buf0));
    ASSERT_FAILED();
  }

  Hex2Bcd(Counts, Pub_Buf0 + Event_Cumu_Data_Info[Index].Counts_Start, Event_Cumu_Data_Info[Index].Counts_Len, Pub_Buf0, sizeof(Pub_Buf0));
  
  if(EVENT_REAL EQ Flag)
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Counts_DI, Pub_Buf0, Len1);

  return;
}

//���¼��ۼƴ����Ĵ���
//Index��ʾEvent_Cumu_Data_Info�е�����
void Event_Cumu_Mins_Proc(INT16U Index, INT32U Mins, INT8U Flag)
{
  //INT32U Counts;
  INT16U Len, Len1;

  TRACE();
  if(Flag != EVENT_REAL)
  {
    return;
  }

  if(Event_Cumu_Data_Info[Index].Mins_DI EQ NULL_STORA_DI)
  {
    return;
  }

  Len1 = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Mins_DI);
  mem_set(Pub_Buf0, 0, Len1, Pub_Buf0, sizeof(Pub_Buf0));
  //��ȡ������д�ۼƴ���
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Mins_DI, Pub_Buf0, Pub_Buf0, sizeof(Pub_Buf0));
  ASSERT(Len1 EQ Len);

  if(!((INT16U) (Event_Cumu_Data_Info[Index].Mins_Start + Event_Cumu_Data_Info[Index].Mins_Len) <= Len))
  {
    mem_set(Pub_Buf0, 0, Len, Pub_Buf0, sizeof(Pub_Buf0));
    ASSERT_FAILED();
  }

  Hex2Bcd(Mins, Pub_Buf0 + Event_Cumu_Data_Info[Index].Mins_Start, Event_Cumu_Data_Info[Index].Mins_Len, Pub_Buf0, sizeof(Pub_Buf0));
  
  if(EVENT_REAL EQ Flag)
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Mins_DI, Pub_Buf0, Len1);

  return;
}
*/
//�¼�����ʱ���ۼƴ���
//IndexΪ�¼���Event_Cumu_Data_Info�����е�����
INT16U Event_Cumu_Start_Proc(INT16U Index, INT8U Flag)
{
  INT32U Counts, Mins;
  INT16U Len;
  //INT8U Err;
  TRACE();
  if(Event_Cumu_Data_Info[Index].Occur_Stora_DI EQ NULL_STORA_DI)
  {
    return 0;
  }

  //�ӷ���ʱ��������ȡ�����ͷ��Ӽ���
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len > 0)
  {
    Counts = 0;
    mem_cpy(&Counts, (INT8U *) Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));      
    Mins = 0;
    mem_cpy(&Mins, (INT8U *) Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));
  }
  else //û�ж���������ۼ�����ȡ
  {
    Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    if(Len > 0)
    {
      Counts = 0;
      mem_cpy(&Counts, (INT8U *) Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));   
      Mins = 0;
      mem_cpy(&Mins, (INT8U *) Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));
    }
    else
    {
      ASSERT_FAILED();
      Mins = 0;//ʵ����û�а취������ȷ�Ĵ���������,����0
      Counts = 0;
    }
  }
  Counts ++;

  Debug_Print("Event Occur Index=%d,Counts=%lu,Mins=%lu,Start_Min=%lu", Index, Counts, Mins, Event_Data.Min_Timer);
  
  //��ǰ�����ۼ��¼������Ѿ��ж����¼������˵ģ�ֻ�Է��������������Ӵ���
  if(Check_Total_Event_ID(Event_Cumu_Data_Info[Index].Event_ID) &&\
     Get_Event_Total_Occuring_Singles(Event_Cumu_Data_Info[Index].Event_ID) != 0 &&\
     EVENT_REAL EQ Flag)//��ʵ�¼��Ŵ洢
  {
    Debug_Print("Total_Event Occuring...");
    mem_cpy((INT8U *) Pub_Buf0 + 5, &Counts, 4, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));//4�ֽ��ۼƴ���
    Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Occur_Stora_DI);    
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *)Pub_Buf0, Len);//������ʱ�����ݴ���ROM)
    return Len;
  } 

  //Event_Cumu_Counts_Proc(Index, Counts, Flag);//�¼�������������

  Pub_Buf0[0] = EVENT_OCCUR;//1�ֽ�ͷ����ʾ�¼����뷢��̬
  mem_cpy((INT8U *) Pub_Buf0 + 1, (INT8U *) &Event_Data.Min_Timer, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));//4�ֽڵ�ǰ�ּ���
  mem_cpy((INT8U *) Pub_Buf0 + 5, &Counts, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));//4�ֽ��ۼƴ���
  mem_cpy((INT8U *) Pub_Buf0 + 9, &Mins, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));//4�ֽ��ۼƷ���
  Len = 13;
  //���˴�����ʱ�仹��Ҫ��¼�������ۼ���������Ҫ���¼�����ʱ�洢˲ʱ��
  Len += Get_Multi_Proto_Data((PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array -> PDI, Event_Cumu_Data_Info[Index].pDI_Array -> DI_Num, (INT8U *) Pub_Buf0 + Len, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0), FOR_SRC | FOR_EVENT);  

  if(EVENT_REAL EQ Flag)//��ʵ�¼��Ŵ洢
  {
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, Len);//������ʱ�����ݴ���ROM
  }
  
  return Len;
}

//�¼�����ʱ���ۼƴ���
//Flag:0��ʾ��ʵ�Ĵ���һ���¼�������1��ʾ����һ�ν��������ǲ��洢��EEROM�У����ǽ��ۼ����ݴ洢��Pub_Buf0��ʼ�Ļ�������
INT16U Event_Cumu_End_Proc(INT16U Index, INT8U Flag)
{
  INT8U* p;
  INT16U Len, Len1;
  INT32U Counts, Mins;
  INT32U Timer;

  TRACE();
  //OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  //��ȡ����ʱ�洢��˲ʱ��
  if(Event_Cumu_Data_Info[Index].Occur_Stora_DI EQ NULL_STORA_DI)
  {
    return 0;
  }

  //��ǰ�����ۼ��¼����Ҹ��ۼӻ���ĳЩ�����¼��ڷ������򲻽��д���
  if(Check_Total_Event_ID(Event_Cumu_Data_Info[Index].Event_ID) &&\
     Get_Event_Total_Occuring_Singles(Event_Cumu_Data_Info[Index].Event_ID) > 1 &&\
     EVENT_REAL EQ Flag)//��ʵ�¼��Ŵ洢
  {
    Debug_Print("Total_Event Occuring...");
    return 0;
  } 

  //�ȶ�ȡ���һ�η���ʱ�ļ�¼  
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len EQ 0 || Pub_Buf0[0] != EVENT_OCCUR)//û���¼�������¼
  {
    ASSERT_FAILED();
    if(Len EQ 0)
      Debug_Print("Read Event_Cumu_Data_Info error Len=0, Index=%d", Index);
    else
      Debug_Print("Read Event_Cumu_Data_Info Occcur_Flag=0x%x error ", Pub_Buf0[0]);

    return 0;
  }
  else//�������ۼ����ݴ������ۼ�
  {
    //�ܵĴ���
    mem_cpy(&Counts, (INT8U *) Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));   
    //�ܵ��ۼƷ���
    mem_cpy(&Mins, (INT8U *) Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));
    //��ȡ����ʱ�ķ��Ӽ���,��ǰ���Ӽ��� - ����ʱ�ķ��Ӽ��� = ���η����ķ�����
    mem_cpy(&Timer, (INT8U *) Pub_Buf0 + 1, 4, &Timer, sizeof(Timer));//����ʱ�ķ��Ӽ���

    if(Event_Data.Min_Timer >= Timer && Timer != 0)
    {
      Mins += (Event_Data.Min_Timer > Timer) ? (Event_Data.Min_Timer - Timer) : 1;
      if(Mins >= 999999)
        Mins = 0;
    }
    else
      Mins = 0;

    Debug_Print("Event End Index=%d,Counts=%lu,Mins=%lu,Start_Min=%lu,End_Min=%lu", Index, Counts, Mins, Timer, Event_Data.Min_Timer);

    //Event_Cumu_Mins_Proc(Index, Mins, Flag);

    Pub_Buf0[0] = EVENT_END;//���¼�������־
    mem_cpy((INT8U *) Pub_Buf0 + 5, &Counts, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    mem_cpy((INT8U *) Pub_Buf0 + 9, &Mins, 4, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    Len = 13;

    p = (INT8U *) Pub_Buf0 + (sizeof(Pub_Buf0) / 2);

    //��ȡ��ǰʱ�̵ĵ���������, ����p��ʼ�Ļ�����
    Get_Multi_Proto_Data((PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array ->PDI, Event_Cumu_Data_Info[Index].pDI_Array ->DI_Num, p,\
						  (INT8U *) Pub_Buf0, sizeof(Pub_Buf0), FOR_SRC);

    //����ǰ�������¼�����ʱ�ĵ������,�����������Pub_Buf0+13��ʼ��Ŀ�껺������
    Proto_Data_Add_Dec(FOR_SRC, DATA_DEC, (PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array ->PDI, Event_Cumu_Data_Info[Index].pDI_Array -> DI_Num, p, (INT8U *) Pub_Buf0 + 13,\
					   (INT8U *) Pub_Buf0 + 13, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));

    //�������еĲ�ֵ���������, �������� Pub_Buf0+13 ��ʼ�Ļ�������

    //�����ܵ��ۼ�����p ��ʼ��buf,Ȼ�󽫵��˵Ĳ��������ۼ���
    Len1 = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, p, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
    ASSERT(Len1 > 0);

    //�������¼��ۼ��������ܵ��ۼ���,�ŵ�Pub_Buf+13 ��ʼ��buf
    Len += Proto_Data_Add_Dec(FOR_SRC, DATA_ADD, (PROTO_DI *) Event_Cumu_Data_Info[Index].pDI_Array ->PDI, Event_Cumu_Data_Info[Index].pDI_Array ->DI_Num, p + 13, (INT8U *) Pub_Buf0 + 13,
                             (INT8U *) Pub_Buf0 + Len, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));

    if(Flag EQ EVENT_REAL)//�����¼�����ʱ���洢�¼�
    {
      Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, Len);//���·���ʱ�����ݣ�����ʱ����ҲӦ�ô洢�ۼƴ�����ʱ��
      Write_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *) Pub_Buf0, Len);
    }
  }
  return Len;
}

//��ȡ�ۼ�ʱ��Ĵ����ͷ�����
void Get_Event_Cumu_Counts_Mins(INT8U Event_ID, INT32U *pCounts, INT32U *pMins)
{
  INT16U Index;
  INT16U Len;
  INT32U Timer;
  
  *pCounts = 0;
  *pMins = 0;
    
  Index = Get_Event_Cumu_Data_Index(Event_ID);//�ҵ��¼�������
  if(NULL_2BYTES EQ Index)
    return ;
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  
  Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));
  if(Len EQ 0)
    Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *) Pub_Buf0, (INT8U *) Pub_Buf0, sizeof(Pub_Buf0));

  if(Len > 0)
  {
    //�ܵĴ���
    mem_cpy(pCounts, (INT8U *) Pub_Buf0 + 5, 4, pCounts, 4);   
    //�ܵ��ۼƷ���
    mem_cpy(pMins, (INT8U *) Pub_Buf0 + 9, 4, pMins, 4);
  
    //��ǰ�¼��ڷ���
    if(Check_Event_Occuring(Event_ID) && Pub_Buf0[0] EQ EVENT_OCCUR)
    {
      //��ȡ����ʱ�ķ��Ӽ���,��ǰ���Ӽ��� - ����ʱ�ķ��Ӽ��� = ���η����ķ�����
      mem_cpy(&Timer, (INT8U *) Pub_Buf0 + 1, 4, &Timer, sizeof(Timer));//����ʱ�ķ��Ӽ���
      
      if(Event_Data.Min_Timer >= Timer && Timer != 0)
      {
        *pMins += (Event_Data.Min_Timer > Timer) ? (Event_Data.Min_Timer - Timer) : 1;
        if(*pMins >= 999999)
          *pMins = 0;
      }
      else
        *pMins = 0;       
    }
  }
  
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}

//��ȡĳ�¼����ۼƴ������ۼ�ʱ�䣬BCD��
//ǰ3�ֽ����ۼƴ���
//��3�ֽ����ۼ�ʱ��
void Get_Event_Cumu_BCD_Counts_Mins(INT8U Event_ID, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  INT32U Counts, Mins;
  
  Get_Event_Cumu_Counts_Mins(Event_ID, &Counts, &Mins);
  
  if(Event_ID EQ ID_EVENT_PROG && Prog_Record.Prog_Flag.All_Flag != 0)//��ǰ����һ����̵Ĺ����У���̴���Ӧ��+1
     Counts ++;
     
  Hex2Bcd(Counts, pDst, 3, pDst_Start, DstLen);
  Hex2Bcd(Mins, pDst + 3, 3, pDst_Start, DstLen);   
}

INT16U Get_Cumu_Event_Num()
{
	  //TRACE();
  return S_NUM(Event_Cumu_Data_Info);
}

INT16U Event_Cumu_Data_Spec_Proc(INT8U Event_ID, INT8U Start_End_Flag)
{
  TRACE();
  return 0;
}

//�¼����Ӽ���
void Event_Cumu_Mins_Accu()
{
  INT8U Re;
  static S_Int8U Min_Bak = {CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE,0xFF,CHK_BYTE}; 
    
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Min_Bak); 
  ASSERT(1 EQ Re);
  
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;
  
  Re = CHECK_STRUCT_SUM(Event_Data);
  ASSERT(1==Re);

  DIS_PD_INT;
  mem_cpy((void *)&Event_Data.Time, (void *)&Cur_Time1, sizeof(Cur_Time1), (void *)&Event_Data.Time, sizeof(Event_Data.Time));
  SET_STRUCT_SUM(Event_Data);
  
  if(Min_Bak.Var != Cur_Time1.Min)
  {
     Min_Bak.Var = Cur_Time1.Min;
     Event_Data.Min_Timer ++ ;
     SET_STRUCT_SUM(Event_Data);
     
     Accmu_RTC_BatTime_PerMin(); //��ع���ʱ����Ӽ���
  }
  EN_PD_INT;
}

//�¼��ۼӴ���
//Event_ID��ʾ�¼�ID
//Occur_Or_End,0��ʾ����,1��ʾ����
INT16U Event_Cumu_Proc(INT8U Event_ID, INT8U Occur_Or_End, INT8U Flag)
{
  INT8U Return_Flag;
  INT16U Index;
  INT16U Len;

  TRACE();
  
  Debug_Print("Event_Cumu_Proc ID:%d",Event_ID);
  
  Len = Extend_Event_Cumu_Proc(Event_ID, Occur_Or_End, Flag, &Return_Flag);
  if(Return_Flag EQ 1)
  {
    return Len;
  }

  //�¼���Event_Cumu_Info�ṹ���е�����
  Index = Get_Event_Cumu_Data_Index(Event_ID);
  if(Index EQ NULL_2BYTES)
  {
    return 0;
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  
  if(Occur_Or_End EQ EVENT_OCCUR)//�¼�����ʱ,������¼�����ʱ��ĳЩ˲ʱ�������¼�����ʱ���������ۼ���
  {
    Len = Event_Cumu_Start_Proc(Index, Flag);
  }
  else//�¼�����ʱ
  {
    Len = Event_Cumu_End_Proc(Index, Flag);
  }
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  
  return Len;
}

//���ĳ�������¼������ۼ�����
INT8U Clear_One_Event_Cumu_Data(INT8U Event_ID)
{
  INT16U Index;
  INT16U Len;
  
  
  Index = Get_Event_Cumu_Data_Index(Event_ID);
  if(Index EQ NULL_2BYTES)
    return 0;
  
  if(Event_Cumu_Data_Info[Index].Clr_Flag EQ 0)//Clr_Flag==0��ʾ�����������
    return 0;
  
  DISP_CLR_DATA_INFO;
  
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
  
  if(Event_Cumu_Data_Info[Index].Occur_Stora_DI != NULL_STORA_DI)
  {
    Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Occur_Stora_DI);
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Occur_Stora_DI, (INT8U *)Pub_Buf0, Len);
  }

  if(Event_Cumu_Data_Info[Index].Total_Stora_DI != NULL_STORA_DI)
  {
    Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[Index].Total_Stora_DI);
    Write_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *)Pub_Buf0, Len);
  }

  OS_Mutex_Post(PUB_BUF0_SEM_ID);  
  return 1;
}

//����Ĭ�ϵ��¼�����������
//��ִ��¼�����
//Clr_Flag 0��ʾֻ��Event_Cumu_Data_Info[i].Clr_Flag==1������
//Clr_Flag 1��ʾ������еķִ��¼�����
void Clr_Event_Cumu_Data(INT8U Clr_Flag)
{
  INT16U i, Len;

  TRACE();
  OS_Mutex_Pend(PUB_BUF0_SEM_ID);
  mem_set((INT8U *)Pub_Buf0, 0, sizeof(Pub_Buf0), (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
  for(i = 0; i < S_NUM(Event_Cumu_Data_Info); i ++)
  {
    if(Event_Cumu_Data_Info[i].Clr_Flag EQ 0 && Clr_Flag EQ 0)//Clr_Flag==0��ʾ�����������
      continue;
    
    if(Event_Cumu_Data_Info[i].Occur_Stora_DI != NULL_STORA_DI)
    {
      Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[i].Occur_Stora_DI);
      Write_Storage_Data(Event_Cumu_Data_Info[i].Occur_Stora_DI, (INT8U *)Pub_Buf0, Len);
    }

    if(Event_Cumu_Data_Info[i].Total_Stora_DI != NULL_STORA_DI)
    {
      Len = Get_Storage_Data_Len(Event_Cumu_Data_Info[i].Total_Stora_DI);
      Write_Storage_Data(Event_Cumu_Data_Info[i].Total_Stora_DI, (INT8U *)Pub_Buf0, Len);
    }
  }
  
  //Write_Storage_Data(0x03050000, (INT8U *)Pub_Buf0, 6); //ȫʧѹ�ۼƴ�����ʱ�䣬�������
  OS_Mutex_Post(PUB_BUF0_SEM_ID);
  
  Clr_Event_PD_Data(); //�����������
}

//����Ĭ�ϵ��ۼ��¼�����,�����ۼ����ݶ���0
void Set_Def_Event_Cumu_Data()
{
  Clr_Event_Cumu_Data(1);  
}

//����ۼ��¼����ݣ�ע�⣺��Щ��¼�����ü�¼�ģ��������
void Clear_Event_Cumu_Data()
{
  Clr_Event_Cumu_Data(0);  
}
#undef EVENT_CUMU_C
