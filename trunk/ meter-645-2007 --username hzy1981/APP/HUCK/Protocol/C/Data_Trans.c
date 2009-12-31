#define DATA_TRANS_C
#include "Includes.h"


#define SOFTWARE_VERSION "09122803 V1.3 " //����汾��


CONST INT32U All_Loss_Vol_Curr = 1000;

extern INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen);

CONST INT8U BROAD_ADDR_99[] =
{
  0x99, 0x99, 0x99, 0x99, 0x99, 0x99
};
CONST INT8U BROAD_ADDR_AA[] =
{
  0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA
};

//CONST INT8U Software_Version[] = SOFTWARE_VERSION;

CONST S_P_Data_Info P_Data_Info[] =
{
  {INIT(PDI, 0x000000FF),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x000B0000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  
  {INIT(PDI, 0x010100FF),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x000A0000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  
  //��ǰ�Լ���ʷ����
  //��ǰ������й�), �з���
  {INIT(PDI, 0x00000000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷ������й�), �з���
  {INIT(PDI, 0x00000001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000000 | ((MAX_RATES + 1) << 8) | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰ�������й�), �޷���
  {INIT(PDI, 0x00010000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷ�������й�), �޷���
  {INIT(PDI, 0x00010001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8) | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰ������޹�), �з���
  {INIT(PDI, 0x00030000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷ������޹�), �з���
  {INIT(PDI, 0x00030001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8) | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰ���������޹�����������), �޷���
  {INIT(PDI, 0x00050000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷ���������޹�����������), �޷���
  {INIT(PDI, 0x00050001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000 | ((MAX_RATES + 1) << 8) | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰ������������й���
  {INIT(PDI, 0x000B0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��һ������������й���
  /*
  {INIT(PDI, 0x000B0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, MAX_ENERGY_SETTLE_NUM),
  INIT(Spec_Flag, SPEC_ENERGY)},
  */
  //��ǰA�������й�), �޷���
  {INIT(PDI, 0x00150000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷA�������й�), �޷���
  {INIT(PDI, 0x00150001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰA������޹�), �з���
  {INIT(PDI, 0x00170000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷA������޹�), �з���
  {INIT(PDI, 0x00170001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰA���������޹�����������), �޷���
  {INIT(PDI, 0x00190000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷA���������޹�����������), �޷���
  {INIT(PDI, 0x00190001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰB�������й�), �޷���
  {INIT(PDI, 0x00290000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷB�������й�), �޷���
  {INIT(PDI, 0x00290001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰB������޹�), �з���
  {INIT(PDI, 0x002B0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷB������޹�), �з���
  {INIT(PDI, 0x002B0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰB���������޹�����������), �޷���
  {INIT(PDI, 0x002D0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷB���������޹�����������), �޷���
  {INIT(PDI, 0x002D0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰC�������й�), �޷���
  {INIT(PDI, 0x003D0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷC�������й�), �޷���
  {INIT(PDI, 0x003D0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰC������޹�), �з���
  {INIT(PDI, 0x003F0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷC������޹�), �з���
  {INIT(PDI, 0x003F0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00020000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰC���������޹�����������), �޷���
  {INIT(PDI, 0x00410000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷC���������޹�����������), �޷���
  {INIT(PDI, 0x00410001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00060000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 

  //ʣ�����
  {INIT(PDI, 0x00900100),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) &Cur_Energy.Prepaid_Info.Left_Energy),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_PREPAID_ENERGY)},

  //͸֧����
  {INIT(PDI, 0x00900101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) &Cur_Energy.Prepaid_Info.Overdraft_Energy),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_PREPAID_ENERGY)},
  
  //ʣ����
  {INIT(PDI, 0x00900200),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) &Cur_Energy.Prepaid_Info.Left_Money),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},  

  //͸֧���
  {INIT(PDI, 0x00900201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) &Cur_Energy.Prepaid_Info.Overdraft_Money),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //г����أ���ʱ����
  /*
  //��ǰ��г������
  {INIT(PDI, 0x00800000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷ��г������
  {INIT(PDI, 0x00800001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰAг������
  {INIT(PDI, 0x00940000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷAг������
  {INIT(PDI, 0x00940001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰBг������
  {INIT(PDI, 0x00A80000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷBг������
  {INIT(PDI, 0x00A80001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  //��ǰCг������
  {INIT(PDI, 0x00BC0000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //��ʷCг������
  {INIT(PDI, 0x00BC0001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  */

  //---------------------------------------
  //��ǰ�Լ���ʷ����
  //��ǰ�������й�), �޷���
  {INIT(PDI, 0x01010000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷ�������й�), �޷���
  {INIT(PDI, 0x01010001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8) | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰ������޹�), �з���
  {INIT(PDI, 0x01030000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷ������޹�), �з���
  {INIT(PDI, 0x01030001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | ((MAX_RATES + 1) << 8) | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰ���������޹�����������), �޷���
  {INIT(PDI, 0x01050000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000 | ((MAX_RATES + 1) << 8)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷ���������޹�����������), �޷���
  {INIT(PDI, 0x01050001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000 | ((MAX_RATES + 1) << 8) | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

#if DEMAND_ACCU_PHASE_NUM >0 //A��B��C�����Ƿ��й����ۼӵ�Ԫ?
  //��ǰA�������й�), �޷���
  {INIT(PDI, 0x01150000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷA�������й�), �޷���
  {INIT(PDI, 0x01150001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰA������޹�), �з���
  {INIT(PDI, 0x01170000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷA������޹�), �з���
  {INIT(PDI, 0x01170001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰA���������޹�����������), �޷���
  {INIT(PDI, 0x01190000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷA���������޹�����������), �޷���
  {INIT(PDI, 0x01190001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰB�������й�), �޷���
  {INIT(PDI, 0x01290000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷB�������й�), �޷���
  {INIT(PDI, 0x01290001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰB������޹�), �з���
  {INIT(PDI, 0x012B0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷB������޹�), �з���
  {INIT(PDI, 0x012B0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰB���������޹�����������), �޷���
  {INIT(PDI, 0x012D0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷB���������޹�����������), �޷���
  {INIT(PDI, 0x012D0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰC�������й�), �޷���
  {INIT(PDI, 0x013D0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷC�������й�), �޷���
  {INIT(PDI, 0x013D0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰC������޹�), �з���
  {INIT(PDI, 0x013F0000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷC������޹�), �з���
  {INIT(PDI, 0x013F0001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00020000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 

  //��ǰC���������޹�����������), �޷���
  {INIT(PDI, 0x01410000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
  //��ʷC���������޹�����������), �޷���
  {INIT(PDI, 0x01410001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 8),
  INIT(Num, 0x00060000 | (MAX_DEMAND_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_DEMAND)}, 
#endif

  /////˲ʱ������///----------------------------------------------------------------
  //A���ѹ 1λС��
  {INIT(PDI, 0x02010100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Volt.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //B���ѹ
  {INIT(PDI, 0x02010200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Volt.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //C���ѹ
  {INIT(PDI, 0x02010300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Volt.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  
  //A����� 3λС��
  {INIT(PDI, 0x02020100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.Curr.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //B�����
  {INIT(PDI, 0x02020200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.Curr.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�����
  {INIT(PDI, 0x02020300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.Curr.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //��˲ʱ�й�����
  {INIT(PDI, 0x02030000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AcPower.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //A��˲ʱ�й����� 3λС��
  {INIT(PDI, 0x02030100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AcPower.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B��˲ʱ�й�����
  {INIT(PDI, 0x02030200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AcPower.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C��˲ʱ�й�����
  {INIT(PDI, 0x02030300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AcPower.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //��˲ʱ�޹�����
  {INIT(PDI, 0x02040000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.ReacPower.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //A��˲ʱ�޹����� 3λС��
  {INIT(PDI, 0x02040100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.ReacPower.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B��˲ʱ�޹�����
  {INIT(PDI, 0x02040200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.ReacPower.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C��˲ʱ�޹�����
  {INIT(PDI, 0x02040300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.ReacPower.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�����ڹ���
  {INIT(PDI, 0x02050000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AppPower.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //A�����ڹ���
  {INIT(PDI, 0x02050100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AppPower.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B�����ڹ���
  {INIT(PDI, 0x02050200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AppPower.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�����ڹ���
  {INIT(PDI, 0x02050300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.AppPower.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�ܹ�������
  {INIT(PDI, 0x02060000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.PFactor.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //A�๦������
  {INIT(PDI, 0x02060100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.PFactor.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B�๦������
  {INIT(PDI, 0x02060200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.PFactor.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�๦������
  {INIT(PDI, 0x02060300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.PFactor.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 3),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�����
  //A�����
  {INIT(PDI, 0x02070100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B�����
  {INIT(PDI, 0x02070200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�����
  {INIT(PDI, 0x02070300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�ܵ�ѹ����ʧ���
  {INIT(PDI, 0x02080000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //A���ѹ����ʧ���
  {INIT(PDI, 0x02080100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B���ѹ����ʧ���
  {INIT(PDI, 0x02080200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C���ѹ����ʧ���
  {INIT(PDI, 0x02080300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�����
  {INIT(PDI, 0x02090000),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //A�����
  {INIT(PDI, 0x02090100),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B�����
  {INIT(PDI, 0x02090200),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�����
  {INIT(PDI, 0x02090300),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 

  //���ߵ���
  {INIT(PDI, 0x02800001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //����Ƶ��
  {INIT(PDI, 0x02800002),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Measu_InstantData_ToPub_PUCK.Freq),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 4),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //һ�����й���ƽ������
  {INIT(PDI, 0x02800003),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &AcPower_1Min_Aver.Aver_Power),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ǰ�й�����
  {INIT(PDI, 0x02800004),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Sign_Demand.Active),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ǰ�޹�����
  {INIT(PDI, 0x02800005),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Sign_Demand.Reactive),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ǰ��������
  {INIT(PDI, 0x02800006),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Sign_Demand.Apparent),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�����¶�
  {INIT(PDI, 0x02800007),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Measu_Sign_InstantData_PUCK.Temprate),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //ʱ�ӵ�ص�ѹ(�ڲ�)
  {INIT(PDI, 0x02800008),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //ͣ�糭���ص�ѹ
  {INIT(PDI, 0x02800009),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�ڲ���ع���ʱ��
  {INIT(PDI, 0x0280000A),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *)&Bat_Work_Status.BatRunTime),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ǰ���ݵ��
  {INIT(PDI, 0x0280000B),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_RATE_INFO)},
  //�¼���¼
  /*
  //ʧѹ�ۼƴ�����ʱ��
  {INIT(PDI, 0x03010000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03010101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | LOSS_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //Ƿѹ�ۼƴ�����ʱ��
  {INIT(PDI, 0x03020000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},
  
  {INIT(PDI, 0x03020101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | LOW_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //��ѹ
  //�ۼƴ�����ʱ��
  {INIT(PDI, 0x03030000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03030101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | OVER_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //����
  //�ۼƴ�����ʱ��
  {INIT(PDI, 0x03040000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03040101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | BREAK_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  */
  //ȫʧѹ
  {INIT(PDI, 0x03050000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03050001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | ALL_LOSS_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //������Դʧ��
  {INIT(PDI, 0x03060000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03060001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | AUX_POWER_DOWN_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  /*
  //��ѹ������
  {INIT(PDI, 0x03070000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03070001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | VOL_REV_SEQ_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //����������
  {INIT(PDI, 0x03080000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03080001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | CUR_REV_SEQ_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //��ѹ��ƽ��
  {INIT(PDI, 0x03090000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03090001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | VOL_UNBALANCE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //������ƽ��
  {INIT(PDI, 0x030A0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x030A0001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | CUR_UNBALANCE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //ʧ��
  {INIT(PDI, 0x030B0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x030B0101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | LOSS_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //����
  {INIT(PDI, 0x030C0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x030C0101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | OVER_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //����
  {INIT(PDI, 0x030D0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x030D0101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //��������
  {INIT(PDI, 0x030E0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x030E0101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | TREND_REVERSE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //����
  {INIT(PDI, 0x030F0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x030F0101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000300 | OVER_LOAD_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
*/
  //��ѹ�ϸ���
  {INIT(PDI, 0x03100000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x0000040D),
  INIT(Spec_Flag, SPEC_VOLSTAT)}, 

  //����
  {INIT(PDI, 0x03110000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03110001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | POWER_DOWN_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //��������
  {INIT(PDI, 0x03120000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  //�����й�������
  {INIT(PDI, 0x03120101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | POS_ACT_DEMAND_EXCEED_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�����й�������
  {INIT(PDI, 0x03120201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | NEG_ACT_DEMAND_EXCEED_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�������޹�������
   {INIT(PDI, 0x03120301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000400 | REA_DEMAND_EXCEED_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //�������¼���¼
  //���
  {INIT(PDI, 0x03300000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�����0
  {INIT(PDI, 0x03300100),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},
  
  {INIT(PDI, 0x03300101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | CLEAR_METER_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //������0
  {INIT(PDI, 0x03300200),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | CLEAR_DEMAND_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�¼���0
  {INIT(PDI, 0x03300300),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | CLEAR_EVENT_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //Уʱ
  {INIT(PDI, 0x03300400),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},
  
  {INIT(PDI, 0x03300401),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | ADJ_TIME_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //ʱ�α���
  {INIT(PDI, 0x03300500),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300501),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | DATE_TABLE_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //ʱ������
  {INIT(PDI, 0x03300600),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},
  
  {INIT(PDI, 0x03300601),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | YEAR_TABLE_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�����ձ��
  {INIT(PDI, 0x03300700),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300701),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | WEEK_REST_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�ڼ��ձ��
  {INIT(PDI, 0x03300800),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300801),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | HOLIDAY_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�й���Ϸ�ʽ���
  {INIT(PDI, 0x03300900),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300901),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | ACTIVE_COMB_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�޹���Ϸ�ʽ1���
  {INIT(PDI, 0x03300A00),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300A01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | REACTIVE_COMB_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�޹���Ϸ�ʽ2���
  {INIT(PDI, 0x03300B00),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},
  
  {INIT(PDI, 0x03300B01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | REACTIVE_COMB_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�����ձ��
  {INIT(PDI, 0x03300C00),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300C01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 |SETTLE_TIME_PROG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�����
  {INIT(PDI, 0x03300D00),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300D01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | OPEN_METER_COVER_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //����ť��
  {INIT(PDI, 0x03300E00),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03300E01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | OPEN_BOTTOM_COVER_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
/*
  //��բ
  {INIT(PDI, 0x03310000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03310101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | RELAY_OFF_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  //��բ
  {INIT(PDI, 0x03310201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000 | RELAY_ON_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
*/  
  //�����͹���
  {INIT(PDI, 0x03320101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 23),
  INIT(Num, 0x00000000 | 0x0600 | PREPAID_ENERGY_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�����͹���鳭��
  {INIT(PDI, 0x0332FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 23),
  INIT(Num, 0x00000000 | PREPAID_ENERGY_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  //����͹���
  {INIT(PDI, 0x03330101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 23),
  INIT(Num, 0x00000000 | 0x0600 | PREPAID_MONEY_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //����͹���
  {INIT(PDI, 0x0333FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 23),
  INIT(Num, 0x00000000 | PREPAID_MONEY_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  //�͹��ĵ��Ƿѹ
  {INIT(PDI, 0x03410000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03410001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 12),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 12),
  INIT(Num, 0x00000000 | LOWPWR_BAT_LOW_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  
  //ʱ�ӵ��Ƿѹ
  {INIT(PDI, 0x03410100),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03410101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 12),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 12),
  INIT(Num, 0x00000000 | RTC_BAT_LOW_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  

  //���ر���
  {INIT(PDI, 0x03420000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03420001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 18),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 18),
  INIT(Num, 0x00000000 | PWR_CTRL_ALARM_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  
  //������բ
  {INIT(PDI, 0x03420100),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x03420101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 12),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 12),
  INIT(Num, 0x00000000 | PWR_CTRL_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  
  
  /////////////////////��չ���¼���¼/////////////////////////
  //ʧѹ�ܴ������ۼ�ʱ��
  {INIT(PDI, 0x10000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  //���һ��ʧѹ�����ͽ���ʱ��
  {INIT(PDI, 0x10000101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000200),
  INIT(Spec_Flag, SPEC_NO)},   
  
  //A��B��C����ʧѹ���ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x10010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�������ʮ��ʧѹ�¼���¼
  {INIT(PDI, 0x10010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033500 | LOSS_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�������ʮ��ʧѹ�¼���¼��
  {INIT(PDI, 0x1001FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | LOSS_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  
  //A��B��C����Ƿѹ���ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x11010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C����Ƿѹ���ʮ���¼���¼
  {INIT(PDI, 0x11010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033500 | LOW_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //A��B��C����Ƿѹ���ʮ���¼���¼��
  {INIT(PDI, 0x1101FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | LOW_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  //A��B��C�����ѹ���ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x12010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�����ѹ���ʮ���¼���¼
  {INIT(PDI, 0x12010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033500 | OVER_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�����ѹ���ʮ���¼���¼��  
  {INIT(PDI, 0x1201FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | OVER_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  //A��B��C����������ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x13010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C����������ʮ���¼���¼
  {INIT(PDI, 0x13010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033500 | BREAK_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  {INIT(PDI, 0x1301FF01),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | BREAK_VOL_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  
  //��ѹ���������ۼƴ�����ʱ��
  {INIT(PDI, 0x14000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //��ѹ���������ʮ���¼���¼
  {INIT(PDI, 0x14000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00002200 | VOL_REV_SEQ_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
   //��ѹ���������ʮ���¼���¼��
  {INIT(PDI, 0x1400FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000 | VOL_REV_SEQ_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  
  //�������������ۼƴ�����ʱ��
  {INIT(PDI, 0x15000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //�������������ʮ���¼���¼
  {INIT(PDI, 0x15000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00002200 | CUR_REV_SEQ_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  
  //�������������ʮ���¼���¼��
  {INIT(PDI, 0x1500FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000 | CUR_REV_SEQ_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 

  //��ѹ��ƽ�����ۼƴ�����ʱ��
  {INIT(PDI, 0x16000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //��ѹ��ƽ�����ʮ���¼���¼
  {INIT(PDI, 0x16000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00002300 | VOL_UNBALANCE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  
  //��ѹ��ƽ�����ʮ���¼���¼��
  {INIT(PDI, 0x1600FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000 | VOL_UNBALANCE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 

  //������ƽ�����ۼƴ�����ʱ��
  {INIT(PDI, 0x17000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //������ƽ�����ʮ���¼���¼
  {INIT(PDI, 0x17000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00002300 | CUR_UNBALANCE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  
  //������ƽ�����ʮ���¼���¼��
  {INIT(PDI, 0x1700FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000 | CUR_UNBALANCE_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  
  //A��B��C����ʧ�����ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x18010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�������ʮ��ʧ���¼���¼
  {INIT(PDI, 0x18010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033100 | LOSS_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�������ʮ��ʧ���¼���¼��
  {INIT(PDI, 0x1801FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | LOSS_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  
  //A��B��C����������ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x19010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�������ʮ�ι����¼���¼
  {INIT(PDI, 0x19010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033100 | OVER_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�������ʮ�ι����¼���¼��
  {INIT(PDI, 0x1901FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | OVER_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  
  //A��B��C����������ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x1A010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�������ʮ�ζ����¼���¼
  {INIT(PDI, 0x1A010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00033100 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�������ʮ�ζ����¼���¼��
  {INIT(PDI, 0x1A01FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  

  //A��B��C���ೱ���������ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x1B010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�������ʮ�γ��������¼���¼
  {INIT(PDI, 0x1B010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00032200 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�������ʮ�γ��������¼���¼��
  {INIT(PDI, 0x1B01FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  //A��B��C����������ۼƴ��������ۼ�ʱ��
  {INIT(PDI, 0x1C010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00030002),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
  //A��B��C�������ʮ�ι����¼���¼
  {INIT(PDI, 0x1C010101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00032200 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //A��B��C�������ʮ�ι����¼���¼��
  {INIT(PDI, 0x1C01FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00030000 | BREAK_CUR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  //��բ����
  {INIT(PDI, 0x1D000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},   
  //���10����բ�¼���¼
  {INIT(PDI, 0x1D000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000800 | RELAY_OFF_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //��բ�¼���¼��
  {INIT(PDI, 0x1D00FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000 | RELAY_OFF_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  //��բ����
  {INIT(PDI, 0x1E000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)},   
  //���10�κ�բ�¼���¼
  {INIT(PDI, 0x1E000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000800 | RELAY_ON_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  //��բ�¼���¼��
  {INIT(PDI, 0x1E00FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000 | RELAY_ON_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  
  //�ܹ������س��������ۼƴ�����ʱ��
  {INIT(PDI, 0x1F000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_C_EVENT)},   
  //���10���ܹ������س������¼�
  {INIT(PDI, 0x1F000101),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000A00 | FACTOR_LOW_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  //�ܹ������س������¼���¼��
  {INIT(PDI, 0x1F00FF01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000 | FACTOR_LOW_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},   
  ////////////////////////////////////////////////////////////
  ////�α���
  //���ڼ�����
  {INIT(PDI, 0x04000101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_TIME),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000001),
  INIT(Spec_Flag, SPEC_TIME)}, 
  //ʱ��
  {INIT(PDI, 0x04000102),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_TIME),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000001),
  INIT(Spec_Flag, SPEC_TIME)}, 
  //����������ںͻ���ʱ��
  {INIT(PDI, 0x04000103),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 
  //У��������
  {INIT(PDI, 0x04000105),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000001),
  INIT(Spec_Flag, SPEC_NO)}, 
  //������ʱ������ʱ�α��л�ʱ������׷����л�ʱ��
  //���׷�ʱ�����л�ʱ�䡢���׽����л�ʱ��
  {INIT(PDI, 0x04000106),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00000004),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ʱ��������ʱ�α�������ʱ������������
  {INIT(PDI, 0x04000201),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000004),
  INIT(Spec_Flag, SPEC_NO)}, 
  //����������
  {INIT(PDI, 0x04000205),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //г����������
  {INIT(PDI, 0x04000206),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //Ԥ�����ݶ���
  {INIT(PDI, 0x04000207),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)},  
  //�Զ�ѭ����ʾ����
  //ÿ����ʾʱ��
  //��ʾ����С��λ��
  //��ʾ����(�������)С��λ��
  //����ѭ����ʾ����
  {INIT(PDI, 0x04000301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000005),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //��������ѹ���������
  {INIT(PDI, 0x04000306),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 

  //ͨ�ŵ�ַ
  {INIT(PDI, 0x04000401),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000001),
  INIT(Spec_Flag, SPEC_NO)}, 
 //���
  {INIT(PDI, 0x04000402),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000001),
  INIT(Spec_Flag, SPEC_METER_ID)},
  //�ʲ��������
  {INIT(PDI, 0x04000403),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 32),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 32),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //���ѹ(AsC�� �롵
  //�����/��������(AsCII��)
  //������(AsCII��)
  {INIT(PDI, 0x04000404),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000003),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�й�׼ȷ�ȵȼ�(AsCII��)
  //�޹�׼ȷ�ȵȼ�(AsCII��)
  {INIT(PDI, 0x04000407),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 
  //����й�����
  //����޹�����
  {INIT(PDI, 0x04000409),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 
  //����ͺ�(AsCII��)
  //��������(AsCII��)
  {INIT(PDI, 0x0400040B),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 10),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 10),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 
  //Э��汾��
  {INIT(PDI, 0x0400040D),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) 0),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 16),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 16),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_FAC_INFO)}, 
  //�ͻ����
  {INIT(PDI, 0x0400040E),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) 0),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)},  
  //�������״̬��1
  {INIT(PDI, 0x04000501),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat1.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������״̬��2
  {INIT(PDI, 0x04000502),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat2.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������״̬��3
  {INIT(PDI, 0x04000503),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat3.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������״̬��4
  {INIT(PDI, 0x04000504),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat4.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������״̬��5
  {INIT(PDI, 0x04000505),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat5.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������״̬��6
  {INIT(PDI, 0x04000506),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat6.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������״̬��7
  {INIT(PDI, 0x04000507),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.Meter_Stat7.Word),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�й����������
  //�޹����1������
  //�޹����2������
  {INIT(PDI, 0x04000601),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000003),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�����ͺ�����ͨ������������
  //�Ӵ�ʽ������ͨ������������
  //ͨ�ſ�1ͨ������������
  //ͨ�ſ�2ͨ������������
  //ͨ�ſ�3ͨ������������
  {INIT(PDI, 0x04000701),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000005),
  INIT(Spec_Flag, SPEC_NO)}, 
  //������������
  {INIT(PDI, 0x04000801),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //���ݿڲ��õ���ʱ�α��  
  {INIT(PDI, 0x04000802),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},   
  //���ɼ�¼ģʽ��
  //��������ģʽ��
  {INIT(PDI, 0x04000901),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00000006),
  INIT(Spec_Flag, SPEC_NO)}, 
  //���ɼ�¼��ʼʱ��
  {INIT(PDI, 0x04000A01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000001),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��1�ฺ�ɼ�¼���ʱ��
  //��2�ฺ�ɼ�¼���ʱ��
  //��3�ฺ�ɼ�¼���ʱ��
  //��4�ฺ�ɼ�¼���ʱ��
  //��5�ฺ�ɼ�¼���ʱ��
  //��6�ฺ�ɼ�¼���ʱ��
  {INIT(PDI, 0x04000A02),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000006),
  INIT(Spec_Flag, SPEC_NO)}, 
  //ÿ�µ�1������
  //ÿ����2������
  //ÿ�µ�3������
  {INIT(PDI, 0x04000B01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000003),
  INIT(Spec_Flag, SPEC_NO)}, 
  //0������
  //...
  //9������
  /*
  {INIT(PDI, 0x04000C01),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_SET_PSW0),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000009),
  INIT(Spec_Flag, SPEC_PSW)}, 
*/

  //A��絼ϵ��
  //A�����ϵ��
  //A�����ϵ��
  //A��翹ϵ��
  //B��絼ϵ��
  //B�����ϵ��
  //B�����ϵ��
  //B��翹ϵ��
  //C��絼ϵ��
  //C�����ϵ��
  //C�����ϵ��
  //c��翹ϵ��
  {INIT(PDI, 0x04000D01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x0000000C),
  INIT(Spec_Flag, SPEC_NO)},
  
  //�����й���������ֵ
  //�����й���������ֵ
  {INIT(PDI, 0x04000E01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ѹ����ֵ
  //��ѹ����ֵ
  {INIT(PDI, 0x04000E03),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)}, 

  //������Ԥ������ֵ
  {INIT(PDI, 0x04000F01), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000004),
  INIT(Spec_Flag, SPEC_NO)},

  //�����Ԥ������ֵ
  {INIT(PDI, 0x04001001), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00000005),
  INIT(Spec_Flag, SPEC_NO)},

  //�������״̬��
  {INIT(PDI, 0x04001101), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
 
  //���㶳�Ὺʼʱ��
  {INIT(PDI, 0x04001201), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //���㶳����ʱ��
  {INIT(PDI, 0x04001202), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
 
  //�ն���ʱ��
  {INIT(PDI, 0x04001203), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
 
  //��բ��ʱ
  {INIT(PDI, 0x04001401), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
 /* 
  //���ʸ���������
  {INIT(PDI, 0x0400E001), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  
  //��󸺺ɼ���ʱ�䣬��������բ��������
  {INIT(PDI, 0x0400E002), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)},
*/
 //��ʾ���С��λ��
  {INIT(PDI, 0x0400E101), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 3),
  INIT(Spec_Flag, SPEC_NO)},
  
 //Ԥ����ģʽ��
  {INIT(PDI, 0x0400E201), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 3),
  INIT(Spec_Flag, SPEC_NO)},
/*  
  //ϵͳ���кš��û��š����
  {INIT(PDI, 0x0400EB01), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 3),
  INIT(Spec_Flag, SPEC_NO)},
*/
  //��������բ����
  {INIT(PDI, 0x0400EA01), 
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *)&Prepaid_Power_Ctrl_Switch.Off_Counts),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
  //��һ��ʱ��������
  {INIT(PDI, 0x04010000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, MAX_YEAR_PERIODS*3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, MAX_YEAR_PERIODS*3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��һ�׵�1��ʱ�α�����:
  //...
  //��һ�׵�14��ʱ�α�����:
  {INIT(PDI, 0x04010001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, MAX_DATE_PERIODS*3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, MAX_DATE_PERIODS*3),
  INIT(Num, (0 | MAX_DATE_TABLES)),
  INIT(Spec_Flag, SPEC_NO)}, 

  //�ڶ���ʱ��������
  {INIT(PDI, 0x04020000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, MAX_YEAR_PERIODS*3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, MAX_YEAR_PERIODS*3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�ڶ��׵�1��ʱ�α�����:
  //...
  //�ڶ��׵�14��ʱ�α�����:
  {INIT(PDI, 0x04020001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, MAX_DATE_PERIODS*3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, MAX_DATE_PERIODS*3),
  INIT(Num, (0 | MAX_DATE_TABLES)),
  INIT(Spec_Flag, SPEC_NO)}, 

  //��������
  {INIT(PDI, 0x04030001),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, MAX_YEAR_HOLIDAYS),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�Զ�ѭ����ʾ��1����ʾ������
  {INIT(PDI, 0x04040101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, SCREEN_ID_LEN),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, SCREEN_ID_LEN),
  INIT(Num, MAX_AUTO_SCREEN_NUM),
  INIT(Spec_Flag, SPEC_NO)}, 
  //����ѭ����ʾ��1����ʾ������
  {INIT(PDI, 0x04040201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, SCREEN_ID_LEN),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, SCREEN_ID_LEN),
  INIT(Num, MAX_KEY_SCREEN_NUM),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��һ�׷�ʱ���ʲ���
  {INIT(PDI, 0x04050101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, MAX_RATES),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�ڶ��׷�ʱ���ʲ���
  {INIT(PDI, 0x04050201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, MAX_RATES),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��һ�׽��ݵ���
  {INIT(PDI, 0x04060001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, PREPAID_MAX_STEP),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��һ�׽��ݵ��
  {INIT(PDI, 0x04060101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, PREPAID_MAX_STEP + 1),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //�ڶ��׽��ݵ���
  {INIT(PDI, 0x04060201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, PREPAID_MAX_STEP),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�ڶ��׽��ݵ��
  {INIT(PDI, 0x04060301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, PREPAID_MAX_STEP + 1),
  INIT(Spec_Flag, SPEC_NO)},  
  
  //ʧѹ�¼���ѹ�����ϡ�����
  {INIT(PDI, 0x04090101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)},  
 
 //ʧѹ�¼�������������
  {INIT(PDI, 0x04090103),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 
 
 //ʧѹ�¼��ж���ʱ��
  {INIT(PDI, 0x04090104),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 
 
 //ʧѹ�¼��ж���ʱ��
  {INIT(PDI, 0x04090201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 

 //Ƿѹ�¼���ѹ��������
  {INIT(PDI, 0x04090201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 
  
 //Ƿѹ�¼��ж���ʱʱ��
  {INIT(PDI, 0x04090202),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},  


 //��ѹ�¼���ѹ��������
  {INIT(PDI, 0x04090301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 
  
 //��ѹ�¼��ж���ʱʱ��
  {INIT(PDI, 0x04090302),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 
 
 //�����¼���ѹ��������
  {INIT(PDI, 0x04090401),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
 
 //�����¼�������������
  {INIT(PDI, 0x04090402),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //�����¼�������������
  {INIT(PDI, 0x04090402),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
 //�����¼��ж���ʱʱ��
  {INIT(PDI, 0x04090403),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
 //��ѹ��ƽ����ֵ
  {INIT(PDI, 0x04090501),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //��ѹ��ƽ�����ж���ʱʱ��
  {INIT(PDI, 0x04090502),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
 //������ƽ����ֵ
  {INIT(PDI, 0x04090601),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //������ƽ�����ж���ʱʱ��
  {INIT(PDI, 0x04090602),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},  
  
 //ʧ���¼���ѹ��������
  {INIT(PDI, 0x04090701),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},    

 //ʧ���¼����������ϡ�����
  {INIT(PDI, 0x04090702),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)},    

 //ʧ���¼��ж���ʱʱ��
  {INIT(PDI, 0x04090704),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 

 //�����¼�������������
  {INIT(PDI, 0x04090801),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},    

 //�����¼��ж���ʱʱ��
  {INIT(PDI, 0x04090802),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)}, 
 
 //�����¼���ѹ��������
  {INIT(PDI, 0x04090901),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},    

 //�����¼�������������
  {INIT(PDI, 0x04090902),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
 
 //�����¼��ж���ʱʱ��
  {INIT(PDI, 0x04090903),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
 //���������¼��ж���ʱʱ��
  {INIT(PDI, 0x04090A01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //���������¼��ж���ʱʱ��
  {INIT(PDI, 0x04090A02),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //�����¼��й����ʴ�������
  {INIT(PDI, 0x04090B01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //�����¼��ж���ʱʱ��
  {INIT(PDI, 0x04090B02),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //��ѹ�����ϡ�����
  {INIT(PDI, 0x04090C01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)},
 
 //�С��޹����������¼�������������
  {INIT(PDI, 0x04090D01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)},
 
 //��������ʱ��ʱ���ж��ӳ�
  {INIT(PDI, 0x04090D03),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //�ܹ������س����޷�ֵ
  {INIT(PDI, 0x04090E01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //�ܹ������س������ж���ʱʱ��
  {INIT(PDI, 0x04090E02),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
 //�������ز�ƽ����ֵ
  {INIT(PDI, 0x04090F01),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},

 //�������ز�ƽ���ж���ʱʱ��
  {INIT(PDI, 0x04090F02),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
  
  //��������汾��(AsC�� ��)
  {INIT(PDI, 0x04800001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 32),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 32),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_FAC_INFO)}, 
  //����Ӳ���汾��(AsCII��)
  {INIT(PDI, 0x04800002),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 32),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 32),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //���ұ��(AsCII��)  
  {INIT(PDI, 0x04800003),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 32),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 32),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},  
  //��ʱ����,��ʱ�������ݵĴ���ͷִ��¼��Ĵ���һ��
  {INIT(PDI, 0x05000001 | ((PROTO_DI)PERIOD_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | PERIOD_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)PERIOD_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | PERIOD_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)PERIOD_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | PERIOD_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  
  
  //˲ʱ����,˲ʱ�������ݵĴ���ͷִ��¼��Ĵ���һ��
  {INIT(PDI, 0x05000001 | ((PROTO_DI)INSTANT_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | INSTANT_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)INSTANT_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | INSTANT_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)INSTANT_FREEZE_TYPE <<16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | INSTANT_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  
  
  //��ʱ�������л�����,��ʱ���л�����Ĵ���ͷִ��¼��Ĵ���һ��
  {INIT(PDI, 0x05000001 | ((PROTO_DI)YEAR_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | YEAR_TABLE_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)YEAR_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | YEAR_TABLE_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)YEAR_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | YEAR_TABLE_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  

  //��ʱ�η����л�����,�������ݵĴ���ͷִ��¼��Ĵ���һ��
  {INIT(PDI, 0x05000001 | ((PROTO_DI)DATE_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | DATE_TABLE_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)DATE_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | DATE_TABLE_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)DATE_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | DATE_TABLE_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  

  //���׽��ݷ����л�����
  {INIT(PDI, 0x05000001 | ((PROTO_DI)STEP_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | STEP_SCH_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)STEP_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | STEP_SCH_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)STEP_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | STEP_SCH_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  
  
  //���׷�ʱ���ʷ����л�����
  {INIT(PDI, 0x05000001 | ((PROTO_DI)RATE_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | RATE_SCH_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)RATE_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | RATE_SCH_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)RATE_SWITCH_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | RATE_SCH_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  
  
//�ն���
  {INIT(PDI, 0x05000001 | ((PROTO_DI)DATE_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | DATE_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)DATE_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | DATE_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)DATE_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | DATE_FREEZE_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  
  
  //Сʱ���߰�ʱ����
  {INIT(PDI, 0x05000001 | ((PROTO_DI)HOUR_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | HOUR_FREEZE_0_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)HOUR_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | HOUR_FREEZE_0_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)HOUR_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | HOUR_FREEZE_0_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},  

  //������ת����
  {INIT(PDI, 0x05000001 | ((PROTO_DI)ENG_OVERTURN_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000B00 | ENERGY_OVERTRUN_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)}, 
  
  {INIT(PDI, 0x05001001 | ((PROTO_DI)ENG_OVERTURN_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | ENERGY_OVERTRUN_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  {INIT(PDI, 0x0500FF01 | ((PROTO_DI)ENG_OVERTURN_FREEZE_TYPE << 16)),
  INIT(DI_Set_Flag, 1),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000100 | ENERGY_OVERTRUN_NUM),
  INIT(Spec_Flag, SPEC_FREEZE)},
  
  //���ɼ�¼��ȡ
  {INIT(PDI, 0x06000000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00070003),
  INIT(Spec_Flag, SPEC_LOAD)}, 

  /////////����//////////////////////////////////////  
  //��������ʱ��
  {INIT(PDI, 0x00EE0001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00000000 |(MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)},  

  //��������ʱ��
  {INIT(PDI, 0x01EE0001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00000000 | (MAX_ENERGY_SETTLE_NUM)),
  INIT(Spec_Flag, SPEC_ENERGY)}, 
  //-----------------------------------------------------
  //ģʽ��1-3
  {INIT(PDI, 0x0E000001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 3),
  INIT(Spec_Flag, SPEC_NO)}, 

  //ģʽ��4-5
  {INIT(PDI, 0x0E000004),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)}, 
/*  
  //��ѹ�������ޡ�����
  {INIT(PDI, 0x0E000101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00000002),
  INIT(Spec_Flag, SPEC_NO)},   

  //ʧѹ������ѹ������
  {INIT(PDI, 0x0E000103),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
 
   //ʧѹ�ж�ʱ��
  {INIT(PDI, 0x0E000104),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

   //ʧ��������������������
  {INIT(PDI, 0x0E000105),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 2),
  INIT(Spec_Flag, SPEC_NO)},
 
  //ʧ���ж�ʱ�䡢�ٽ��ѹ
  {INIT(PDI, 0x0E000107),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
*/
  //ʧ���ж�ʱ�䡢�ٽ��ѹ
  {INIT(PDI, 0x0E000108),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 1),
  INIT(Spec_Flag, SPEC_NO)},
/*
//������������
  {INIT(PDI, 0x0E000109),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
 
//�����ж�ʱ��
  {INIT(PDI, 0x0E00010A),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

//��ѹ�жϷ�ֵ
  {INIT(PDI, 0x0E00010B),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
 
//�û�������բ��ʱ����բ��ʱ
  {INIT(PDI, 0x0E00010C),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 3),
  INIT(Spec_Flag, SPEC_NO)},

//������ƽ������
  {INIT(PDI, 0x0E00010F),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
 
 //��ѹ��ƽ������
  {INIT(PDI, 0x0E000110),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

 //ʧѹ������ѹ
  {INIT(PDI, 0x0E000111),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

 //ʧѹ��������
  {INIT(PDI, 0x0E000112),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

 //ʧѹ�жϷ�ֵ
  {INIT(PDI, 0x0E000113),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

 //�����жϷ�ֵ
  {INIT(PDI, 0x0E000114),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

 //������ȷ����дʱ��
  {INIT(PDI, 0x0E000200),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) &PSW_Err_Info.Set_En_Mins),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  
 //������������������
  {INIT(PDI, 0x0E000201),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
 //����������ʱ��
  {INIT(PDI, 0x0E000202),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x02),
  INIT(Spec_Flag, SPEC_NO)},
*/  
 //����������ʣ�����
  {INIT(PDI, 0x0E000204),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &PSW_Err_Info.Err_Counts),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  
 //����������ʣ��ʱ��
  {INIT(PDI, 0x0E000205),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &PSW_Err_Info.Lock_Mins),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
/*  
 //���ʱ��
  {INIT(PDI, 0x0E000206),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},   
*/  
 //����һ���״̬
  {INIT(PDI, 0x0E000206),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  
 //���ڶ���ʱ��
  {INIT(PDI, 0x0E000207),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  
  //ÿ�չ㲥Уʱ����
  {INIT(PDI, 0x0E000208),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  
  //���ó�ʼ����
  {INIT(PDI, 0x0E000301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_CLR_ALL),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 36),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 36),
  INIT(Num, 0x08),
  INIT(Spec_Flag, SPEC_SET_ENG)}, 

  //����Ԥ���ѵ��������
  {INIT(PDI, 0x0E000400),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_CLR_ALL),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x03),
  INIT(Spec_Flag, SPEC_SET_ENG)}, 
 
  //�忨��־��Ԥ���Ѳ�����
  {INIT(PDI, 0x0E000403),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_CLR_ALL),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_SET_ENG)},
  
   //��ǰ��ʱ����������Ϣ
  {INIT(PDI, 0x0E010000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x13),
  INIT(Spec_Flag, SPEC_RATE_INFO)},

  //��ǰ�����й�����
  {INIT(PDI, 0x0E010301),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Pos_Active),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��ǰ�����й�����
  {INIT(PDI, 0x0E010302),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Neg_Active),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��ǰ����޹�1����
  {INIT(PDI, 0x0E010303),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Comb_Reactive1),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��ǰ����޹�2����
  {INIT(PDI, 0x0E010304),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Comb_Reactive2),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  //��ǰһ�����޹�����
  {INIT(PDI, 0x0E010305),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Quad_Reactive[0]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��ǰ�������޹�����
  {INIT(PDI, 0x0E010306),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Quad_Reactive[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��ǰ�������޹�����
  {INIT(PDI, 0x0E010307),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Quad_Reactive[2]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��ǰ�������޹�����
  {INIT(PDI, 0x0E010308),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Accu.Phase_Cur[0].Quad_Reactive[3]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  
  //��ǰ���ʵ��
  {INIT(PDI, PDI_CUR_RATE1_FEE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, MAX_RATES),
  INIT(Spec_Flag, SPEC_RATE_INFO)}, 
  //��ǰ���ݵ���
  {INIT(PDI, PDI_CUR_STEP1_ENG),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, PREPAID_MAX_STEP),
  INIT(Spec_Flag, SPEC_RATE_INFO)},  
  //��ǰ���ݵ��
  {INIT(PDI, PDI_CUR_STEP1_FEE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, PREPAID_MAX_STEP + 1),
  INIT(Spec_Flag, SPEC_RATE_INFO)},   
//----��չ�¼���¼-------------
  //��λ
  {INIT(PDI, 0x0E180000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x0E180001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00000000 | RESET_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},  

  //����ʱ����
  {INIT(PDI, 0x0E190000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x0E190001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 11),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 11),
  INIT(Num, 0x00000000 | POWER_ON_CLOCK_ERR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)},
  
  //�ϵ�ʱ����
  {INIT(PDI, 0x0E1C0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x0E1C0001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 11),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 11),
  INIT(Num, 0x00000000 | POWER_ON_CLOCK_ERR_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
/*  
  //Զ����բ�¼���¼
  {INIT(PDI, 0x0E1D0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 0),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 38),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x0E1D0001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 0),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 38),
  INIT(Num, 0x00000000 | REMOTE_RELAY_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 

  //Զ�̺�բ�¼���¼
  {INIT(PDI, 0x0E1E0000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x0E1E0001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 38),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 38),
  INIT(Num, 0x00000000 | REMOTE_RELAY_SWITCH_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
*/
  //���ʼ�����¼�
  {INIT(PDI, 0x0E301100),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00000000),
  INIT(Spec_Flag, SPEC_C_EVENT)}, 
  
  {INIT(PDI, 0x0E301101),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 38),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 38),
  INIT(Num, 0x00000000 | SET_ENERG_NUM),
  INIT(Spec_Flag, SPEC_S_EVENT)}, 
  
  //��չ���¼��ۼ����ݣ�����ʧѹ��ʧ�������ࡢ����
  {INIT(PDI, 0x0EA00000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x0404),
  INIT(Spec_Flag, SPEC_C_EVENT)},  
  
 //Զ��ͨ��״̬
  {INIT(PDI, 0x0EA20000),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_MODULE)},   
  
 //ģ��򿪵��дʹ��
  {INIT(PDI, 0x0EA20001),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_SET_PARA),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 0),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 0),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_MODULE)},   
  
  //--------------------------------------------------------------------------------------

  //A���ѹ 1λС��
  {INIT(PDI, _PDI_A_VOL),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Volt.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //B���ѹ
  {INIT(PDI, _PDI_B_VOL),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Volt.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //C���ѹ
  {INIT(PDI, _PDI_C_VOL),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Volt.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 2),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  
  //A����� 4λС��
  {INIT(PDI, _PDI_A_CUR),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.Curr.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //B�����
  {INIT(PDI, _PDI_B_CUR),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.Curr.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�����
  {INIT(PDI, _PDI_C_CUR),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_Sign_InstantData_PUCK.Curr.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTS),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //A�����
  {INIT(PDI, _PDI_A_ANGLE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.A),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B�����
  {INIT(PDI, _PDI_B_ANGLE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.B),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�����
  {INIT(PDI, _PDI_C_ANGLE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.C),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //�����
   {INIT(PDI, _PDI_SUM_ANGLE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, &Measu_InstantData_ToPub_PUCK.Angle.Sum),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},

  //Уʱǰʱ��
   {INIT(PDI, _PDI_ADJ_BEF_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, Adj_Bef_Time.Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)},
  //Уʱ��ʱ��
   {INIT(PDI, _PDI_ADJ_AFT_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, Adj_Aft_Time.Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0),
  INIT(Spec_Flag, SPEC_NO)}, 
  //��ǰ�޹�����
  {INIT(PDI, _PDI_CURRENT_QUADRANT),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Meter_Run_Status.NegCurr_Qudrant.Byte),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  
  //��ǰʱ�䣬����
  {INIT(PDI, _PDI_CUR_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) Cur_Time2.Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 

  //����ʱ��,�롢�֡�ʱ���ա��¡���
  {INIT(PDI, _PDI_PD_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) PD_Time.Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //�ϵ�ʱ��,�롢�֡�ʱ���ա��¡���
  {INIT(PDI, _PDI_PO_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) PO_Time.Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  
  //��ǰʱ��,������  
  {INIT(PDI, _PDI_CUR_TIME0),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Time2.Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
 
   //���ʱ��
  {INIT(PDI, _PDI_PROG_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Prog_Record.Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��AH
  {INIT(PDI, _PDI_TOTAL_AH),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Phase_AH[0]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //A�లʱ
  {INIT(PDI, _PDI_A_AH),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Phase_AH[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //B�లʱ
  {INIT(PDI, _PDI_B_AH),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Phase_AH[2]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //C�లʱ
  {INIT(PDI, _PDI_C_AH),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Phase_AH[3]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //ȫʧѹ����ʱ����
  {INIT(PDI, _PDI_ALL_LOSS_VOL_CUR),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) (INT8U *)&All_Loss_Vol_Time.Curr),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //����ѹ��ƽ����
  {INIT(PDI, _PDI_VOLT_MAX_UNBALANCE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Not_Even_Data_PUCK.Volt_Not_Even),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //��������ƽ����
  {INIT(PDI, _PDI_CURR_MAX_UNBALANCE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Not_Even_Data_PUCK.Curr_Not_Even),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 2),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  /*
  #define _PDI_POS_ACTIVE_DEMAND_TIME  0x80000005 //���������ڼ�����й�������ʱ��
  #define _PDI_NEG_ACTIVE_DEMAND_TIME  0x80000006
  #define _PDI_QUAD1_REACT_DEMAND_TIME 0x80000007
  #define _PDI_QUAD2_REACT_DEMAND_TIME 0x80000008
  #define _PDI_QUAD3_REACT_DEMAND_TIME 0x80000009
  #define _PDI_QUAD4_REACT_DEMAND_TIME 0x8000000A
  */
  //�����й������������
  {INIT(PDI, _PDI_POS_ACTIVE_DEMAND),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Pos_Active.Var),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�����й������������
  {INIT(PDI, _PDI_NEG_ACTIVE_DEMAND),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Neg_Active.Var),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //һ�����޹������������
  {INIT(PDI, _PDI_QUAD1_REACT_DEMAND),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[0].Var),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������޹������������
  {INIT(PDI, _PDI_QUAD2_REACT_DEMAND),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[1].Var),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������޹������������
  {INIT(PDI, _PDI_QUAD3_REACT_DEMAND),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[2].Var),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������޹������������
  {INIT(PDI, _PDI_QUAD4_REACT_DEMAND),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[3].Var),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�����й����������������ʱ��
  {INIT(PDI, _PDI_POS_ACTIVE_DEMAND_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Pos_Active.Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�����й����������������ʱ��
  {INIT(PDI, _PDI_NEG_ACTIVE_DEMAND_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Neg_Active.Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //һ�����޹���������ʱ��
  {INIT(PDI, _PDI_QUAD1_REACT_DEMAND_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[0].Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������޹���������ʱ��
  {INIT(PDI, _PDI_QUAD2_REACT_DEMAND_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[1].Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������޹���������ʱ��
  {INIT(PDI, _PDI_QUAD3_REACT_DEMAND_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[2].Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�������޹���������ʱ��
  {INIT(PDI, _PDI_QUAD4_REACT_DEMAND_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Demand_Exceed_Limit.Quad_Reactive[3].Time[1]),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�����ߴ���
  {INIT(PDI, _PDI_OPERATOR_ID),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*)Operator_ID.Op_ID),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //һ�α�̼�¼�Ĳ����ߴ���
  {INIT(PDI, _PDI_PROG_OP_ID),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*)Prog_Record.Op_ID),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},   
  //��̼�¼DI
  {INIT(PDI, _PDI_PROG_DI),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*)Prog_Record.PDI),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 40),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 40),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
  //�¼���0���ݱ�ʶ
  {INIT(PDI, _PDI_CLR_EVENT_DI),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Clear_Event_PDI),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
 
  //ȫʧѹ��ʼʱ��
  {INIT(PDI, _PDI_ALL_LOSS_VOL_START_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) All_Loss_Vol_Time.Start_Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  

  //ȫʧѹ����ʱ��
  {INIT(PDI, _PDI_ALL_LOSS_VOL_END_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) All_Loss_Vol_Time.End_Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 6),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 6),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},

  //RTC����ʱ��
  {INIT(PDI, _PDI_RTC_ERR_TIME),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) RTC_Err_Time),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 5),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 5),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},

  //�������ܴ���
  {INIT(PDI, _PDI_TOTAL_PREPAID_ENERGY_COUNTS),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //�ۼƹ�����
  {INIT(PDI, _PDI_TOTAL_PREPAID_ENERGY),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Prepaid_Info.Total_Prepaid_Energy),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_PREPAID_ENERGY)},  
  //���ι������
  {INIT(PDI, _PDI_CUR_PREPAID_ENERGY),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Prepaid.Energy),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_PREPAID_ENERGY)},
  //���ι���ǰ�ܵ���
  {INIT(PDI, _PDI_CUR_PREPAID_BEF_ENERGY),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Prepaid.Bef_Left_Energy),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_PREPAID_ENERGY)},  
  
  //������ܴ���
  {INIT(PDI, _PDI_TOTAL_PREPAID_MONEY_COUNTS),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 2),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},
  //�ۼƹ�����
  {INIT(PDI, _PDI_TOTAL_PREPAID_MONEY),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Energy.Prepaid_Info.Total_Prepaid_Money),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  //���ι�����
  {INIT(PDI, _PDI_CUR_PREPAID_MONEY),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Prepaid.Money),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  


  
  //���ι���ǰ�ܽ��
  {INIT(PDI, _PDI_CUR_PREPAID_BEF_MONEY),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void*) &Cur_Prepaid.Bef_Left_Money),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 4),
  INIT(Src_Format, S_INTU),
  INIT(Dst_Start, 1),
  INIT(Dst_Len, 4),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  
//----У��״̬------
  {INIT(PDI, _PDI_ADJ_METER_PARA_STATUS),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)},  
  //---У�����-----
  {INIT(PDI, _PDI_ADJ_METER_PUL_VOL_CUR_SPEC),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 3),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 3),
  INIT(Num, 13),
  INIT(Spec_Flag, SPEC_NO)}, 
  
  //---У������----
  {INIT(PDI, _PDI_ADJ_METER_CLR),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_ADJ)},  
  
  //---��ȡ�ڿ�����
  {INIT(PDI, _PDI_RD_ROM),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_RD_ROM)}, 

  //---У��˲ʱ���ݴ���
  {INIT(PDI, _PDI_ADJ_INSTANT_DATA),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_FAC_PARA),
  INIT(Storage, S_ROM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len,sizeof(CAL_DATA_PACK)),
  INIT(Src_Format, S_BIN),
  INIT(Dst_Start, 0),
  INIT(Dst_Len,sizeof(CAL_DATA_PACK)),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_ADJ)},

//----���õı�ʶ��------
  {INIT(PDI, _PDI_NULL_1BYTE),
  INIT(DI_Set_Flag, 0),
  INIT(PSW_Flag, PSW_RD_ONLY),
  INIT(Storage, S_RAM),
  INIT(pSrc, (void *) Zero),
  //INIT(Src_Off, 0),
  INIT(Src_Len, 1),
  INIT(Src_Format, S_BCD),
  INIT(Dst_Start, 0),
  INIT(Dst_Len, 1),
  INIT(Num, 0x00),
  INIT(Spec_Flag, SPEC_NO)}, 
}; 

//���Э�����ݵĴ洢��Protocol_Data��S_ROM���Ե�����Ӧ���ڴ洢�ж�������
INT8U Check_Protocol_Data_Storage()
{ 
  INT16U i;
  INT8U Re;
  
  Re = 1;
  Clear_Ext_Dog();
  for(i=0;i<S_NUM(P_Data_Info);i++)
  {
    if(S_ROM EQ P_Data_Info[i].Storage && P_Data_Info[i].Spec_Flag EQ SPEC_NO)
    {    
      if(Get_Storage_Data_Len(P_Data_Info[i].PDI) EQ 0)
      {
        Debug_Print("Protocol_Data %x Storage Err",P_Data_Info[i].PDI);
        Re = 0;//PROTOCOL_DATA_STORAGE_ERR;
      }
    }
  }
  return Re;
}

//��ȡ���ݴ�����ز���
void Read_Data_Trans_Para_From_Rom()
{
  INT8U i;
  
  TRACE();
  
  if(Read_Storage_Data(SDI_COMM_ADDR, (void *)Meter_Addr.Addr[0], (void *)Meter_Addr.Addr[0], sizeof(Meter_Addr.Addr[0])) EQ 0)
  {
     mem_set((void *)Meter_Addr.Addr[0], 0, sizeof(Meter_Addr.Addr[0]), (void *)Meter_Addr.Addr[0], sizeof(Meter_Addr.Addr[0]));  
  }
  
  Meter_Addr_Ready_Flag.Var = DATA_READY; //���ַ׼������
  INIT_STRUCT_VAR(Meter_Addr_Ready_Flag);
  
  SET_STRUCT_SUM(Meter_Addr);
  
  for(i = 0; i < 10; i ++)//��ȡ10������
  {
    Read_Storage_Data(SDI_PSW0 + i, (INT8U *)Cur_PSW.PSW[i], (INT8U *)Cur_PSW.PSW, sizeof(Cur_PSW.PSW)); 
    
  }
  
  SET_STRUCT_SUM(Cur_PSW);
}

//��ʼ�����ݴ�����ص��ڴ����
void Init_Data_Trans_Ram_Para()
{
  TRACE();

  //�����޸Ļ�����
  mem_set((void *) &Para_Modify, 0, sizeof(Para_Modify), (void *) &Para_Modify, sizeof(Para_Modify)); 
  INIT_STRUCT_VAR(Para_Modify); 
  SET_STRUCT_SUM(Para_Modify); 

  INIT_STRUCT_VAR(User_Authority_Flag); 
  User_Authority_Flag.Flag = 0; 
  SET_STRUCT_SUM(User_Authority_Flag); 

  INIT_STRUCT_VAR(Clear_Flag); 
  Clear_Flag.Flag = CLEAR_END_FLAG; 
  SET_STRUCT_SUM(Clear_Flag); 
  
  Module_Set_Meter_Status.Set_En_Mins = 0;
  SET_STRUCT_SUM(Module_Set_Meter_Status);

}


/*****************************************
��ԭ�ͣ�
void Set_Para_Modify(PROTO_DI PDI)
  �����ܣ�
  ĳ����������ʱ���øú���
��ڲ�����PDI, �����ı�ʾ��
 ��ڲ������?
******************************************/
void Set_Para_Modify(PROTO_DI PDI)
{
  INT8U i, Posi, Re; 
  INT8U Task_Num; 

  TRACE();

  Re = CHECK_STRUCT_SUM(Para_Modify); 
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }   

  Task_Num = OS_Get_Cur_Task_Num(); 

  for(i = 0; i < Task_Num && i < OS_TASK_NUM; i ++)
  {
    if(Para_Modify.Posi[i] >= CHK_PARA_NUM)
    {
      ASSERT_FAILED();
      Para_Modify.Posi[i] = 0;
    }

    Para_Modify.Posi[i] ++ ; //��0���ֽڼ�¼��ǰ�޸Ĳ�����ʾ��Ĵ��λ��
    if(Para_Modify.Posi[i] >= CHK_PARA_NUM)
      Para_Modify.Posi[i] = 0; 

    Posi = Para_Modify.Posi[i]; 
    if(0 != Para_Modify.Buf[i][Posi])//�ж��Ѿ��޸��˵Ĳ����Ƿ񱻶���ȥ��?
    {
      // Debug_Print("Waitfor Set_Para_Modify  % s Task ara_Modify.Buf[%d][%d] EQ %d", \
      // Tcb[i].Name, i, Posi, Para_Modify.Buf[i][Posi]); 
      SET_STRUCT_SUM(Para_Modify); 
      OS_Waitfor_Sec(0 EQ Para_Modify.Buf[i][Posi], 5); //�ȴ�5S��λ�ñ�Ϊ0

      if(0 != Para_Modify.Buf[i][Posi])
        Debug_Print("Para_Modify.Buf[%d][%d] EQ %d error", i, Posi, Para_Modify.Buf[i][Posi]);
    }
    Para_Modify.Buf[i][Posi] = PDI;
  }
  SET_STRUCT_SUM(Para_Modify); 
}

//���̵��ڴ��¼
void Clr_Prog_Record_Ram()
{
  DIS_PD_INT;
  
  mem_set((void *)&Prog_Record, 0, sizeof(Prog_Record), (void *)&Prog_Record, sizeof(Prog_Record));
  mem_set((void *)&Prog_Record.PDI, 0xFF, sizeof(Prog_Record.PDI), (void *)&Prog_Record.PDI, sizeof(Prog_Record.PDI));
  SET_STRUCT_SUM(Prog_Record); 
  SET_STRUCT_SUM(Event_Data);
  
  EN_PD_INT;
}
/*
//��̼�¼��10���Ӽ���
void Prog_Timer_Proc()
{
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  
  if(Min_Bak.Var EQ Cur_Time1.Min)
    return;
  
  Min_Bak.Var = Cur_Time1.Min;
  
  if(Prog_Record.Mins > 0)
  {
    Prog_Record.Mins --;
    
    SET_STRUCT_SUM(Prog_Record);
    SET_STRUCT_SUM(Event_Data);
    
    if(Prog_Record.Mins EQ 0)
    {
      Event_Data_Proc(ID_EVENT_PROG, EVENT_OCCUR);
      Clr_Prog_Record_Ram();
    }
  }
}
*/

//��̼�¼��10���Ӽ���
void Prog_Timer_Proc()
{
  INT8U Status;
  static S_Int8U Sec_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Counts = {CHK_BYTE, 0, CHK_BYTE};
  
  if(Check_Meter_Prog_Status() || Check_Meter_Factory_Status()) //���ڱ��״̬
    Status = 1;
  else
    Status = 0;
  
  if(PREPAID_EN > 0)
  {
    if(Check_Remote_Prog_Status())
      Status = 1;
  }
  
  if(Status != Prog_Record.Prog_Status) //���״̬�����˱仯
  {
    DIS_PD_INT;
    
    Prog_Record.Prog_Status = Status;
    if(Status EQ 0 && Prog_Record.Prog_Flag.All_Flag > 0) //�ɱ��״̬����Ǳ��״̬���ҷ�����������һ�α�̼�¼
    {
      Event_Data_Proc(ID_EVENT_PROG, EVENT_OCCUR);
      Clr_Prog_Record_Ram();       
    }
    
    SET_STRUCT_SUM(Prog_Record);
    SET_STRUCT_SUM(Event_Data);
  
    EN_PD_INT;
  }
  
  if(Adj_Time_Flag.Var EQ 0x55)
  {
    if(Sec_Bak.Var != Cur_Time1.Sec)
    {
      Counts.Var ++;
      Sec_Bak.Var = Cur_Time1.Sec;
    }
    
    if(Counts.Var > 2)
    {
      Adj_Time_Flag.Var = 0;
      Counts.Var = 0;
      //Event_Data_Proc(ID_EVENT_ADJUST_TIME, EVENT_OCCUR);
      Event_Cumu_Proc(ID_EVENT_ADJUST_TIME,EVENT_OCCUR,EVENT_REAL);
      OS_TimeDly_Ms(100);
      Event_Separate_Proc(ID_EVENT_ADJUST_TIME,EVENT_OCCUR,EVENT_REAL);
    
    }  
  }
}

//����Ƿ�У�����,�Ƿ���1�����򷵻�0
INT8U Check_Adj_Meter_Para(PROTO_DI PDI)
{
  if(PDI >= _SDI_ADJ_METER_PARA_STATUS && PDI <= _SDI_RD_ROM)
    return 1;
  else
    return 0;
  
}

//���PDI��ʶ�Ƿ���Ҫ��̼�¼��1��ʾ��Ҫ��0��ʾ����Ҫ
INT8U Check_PDI_Set_Prog_Record(PROTO_DI PDI)
{
  if(Check_Adj_Meter_Para(PDI))//У����Ҫ��¼�������
    return 0;
  return 1;
}

//��̼�¼Ԥ�����������ǰ����
//��Ϊ��Щ�����漰���¼�����ʱ��̫���������ȷ�Ӧ���ٴ����¼�
//pAck_FlagΪ1��ʾ�Ѿ�����Ӧ��0��ʾû��
void Set_Prog_Record_Pre_Porc(INT8U Ch, PROTO_DI PDI, INT8U *pAck_Flag)
{
  INT8U Event_ID;
  
  *pAck_Flag = 0;
  
  DIS_PD_INT;
 ///////////////////////////////////////////////////////////////
#if DATE_TABLE_PROG_NUM >0 //��ʱ�α���
  if(((PDI & 0xFFFFFF00) EQ 0x04010000 || (PDI & 0xFFFFFF00) EQ 0x04020000) &&
     (PDI & 0xFF) >0)
  {
    if(Prog_Record.Prog_Flag.Date_Flag EQ 0)//Read_Event_Status(ID_EVENT_DATE) EQ 0)
    {
      *pAck_Flag = 1;
      Prog_Record.Prog_Flag.Date_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);
      Set_Event_Instant(ID_EVENT_DATE);
      Event_ID = ID_EVENT_DATE;//Event_Data_Proc(ID_EVENT_DATE, EVENT_OCCUR);
    }
  }
#endif    
    
#if YEAR_TABLE_PROG_NUM >0  //ʱ������
  if(PDI EQ 0x04010000 || PDI EQ 0x04020000)
  {
    if(Prog_Record.Prog_Flag.Year_Flag EQ 0)//Read_Event_Status(ID_EVENT_YEAR) EQ 0)
    {
      *pAck_Flag = 1;
      Prog_Record.Prog_Flag.Year_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_YEAR);
      Event_ID = ID_EVENT_YEAR;//Event_Data_Proc(ID_EVENT_YEAR, EVENT_OCCUR);
    }

  }
#endif
    
#if WEEK_REST_PROG_NUM >0  //�����ձ��
  if(PDI EQ 0x04000802)
  {
    if(Prog_Record.Prog_Flag.Week_Flag EQ 0)//Read_Event_Status(ID_EVENT_WEEK) EQ 0)
    {
      *pAck_Flag = 1;    
      Prog_Record.Prog_Flag.Week_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_WEEK);
      Event_ID = ID_EVENT_WEEK;//Event_Data_Proc(ID_EVENT_WEEK, EVENT_OCCUR);
    }

  }
#endif
    
#if HOLIDAY_PROG_NUM >0  //�ڼ��ձ��
  if((PDI &0xFFFFFF00) EQ 0x04030000 && \
     (PDI &0xFF) >0  && (PDI &0xFF) < MAX_YEAR_HOLIDAYS)// || PDI EQ 0x04020000)
  {
    if(Prog_Record.Prog_Flag.Holiday_Flag EQ 0)//Read_Event_Status(ID_EVENT_HOLIDAY) EQ 0)
    {
      *pAck_Flag = 1; 
      Prog_Record.Prog_Flag.Holiday_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_HOLIDAY);
      Event_ID = ID_EVENT_HOLIDAY;//Event_Data_Proc(ID_EVENT_HOLIDAY, EVENT_OCCUR);
    }
  }
#endif
    
#if ACTIVE_COMB_PROG_NUM >0  //�й���ϱ��
  if(PDI EQ 0x04000601)
  {
    if(Prog_Record.Prog_Flag.ActComm_Flag EQ 0)//Read_Event_Status(ID_EVENT_ACPWR) EQ 0)
    {
      *pAck_Flag = 1;  
      Prog_Record.Prog_Flag.ActComm_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_ACPWR);
      Event_ID = ID_EVENT_ACPWR;//Event_Data_Proc(ID_EVENT_ACPWR, EVENT_OCCUR);
    }

  }
#endif
#if REACTIVE_COMB_PROG_NUM > 0  //�޹���ϱ��
  if(PDI EQ 0x04000602)
  {
    if(Prog_Record.Prog_Flag.ReacComm1_Flag EQ 0)//Read_Event_Status(ID_EVENT_REACPWR1) EQ 0)
    {
      *pAck_Flag = 1;
      Prog_Record.Prog_Flag.ReacComm1_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_REACPWR1);
      Event_ID = ID_EVENT_REACPWR1;//Event_Data_Proc(ID_EVENT_REACPWR1, EVENT_OCCUR);
    }
  }
  
  else if(PDI EQ 0x04000603)
  {
    if(Prog_Record.Prog_Flag.ReacComm2_Flag EQ 0)//Read_Event_Status(ID_EVENT_REACPWR2) EQ 0)
    {
      *pAck_Flag = 1;
      Prog_Record.Prog_Flag.ReacComm2_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_REACPWR2);
      Event_ID = ID_EVENT_REACPWR2;//Event_Data_Proc(ID_EVENT_REACPWR2, EVENT_OCCUR);
    }

  }  
#endif
    
#if SETTLE_TIME_PROG_NUM > 0  //�����ձ��   
  if(PDI EQ 0x04000B01 || PDI EQ 0x04000B02 || PDI EQ 0x04000B03)
  {
    if(Prog_Record.Prog_Flag.SettleDay_Flag EQ 0)//Read_Event_Status(ID_EVENT_SETTLE_DATE) EQ 0)
    {
      *pAck_Flag = 1; 
      Prog_Record.Prog_Flag.SettleDay_Flag = 1;
      Send_Set_Data_Ack_Frame(Ch);      
      Set_Event_Instant(ID_EVENT_SETTLE_DATE);
      Event_ID = ID_EVENT_SETTLE_DATE;//Event_Data_Proc(ID_EVENT_SETTLE_DATE, EVENT_OCCUR);
    }

  } 
#endif  

  if(*pAck_Flag EQ 1)
  {
    SET_STRUCT_SUM(Prog_Record);
    SET_STRUCT_SUM(Event_Data);
  }
  
  EN_PD_INT;
 ///////////////////////////////////////////////////////////////   
  if(*pAck_Flag EQ 1)  
    Event_Data_Proc(Event_ID, EVENT_OCCUR);  
}

//���ñ�̼�¼
void Set_Prog_Record(PROTO_DI PDI, INT8U Op_ID[])
{
    INT8U i;
    INT8U Re;
    INT8U Num;
    
    TRACE();
    
    if(Check_PDI_Set_Prog_Record(PDI) EQ 0)//0��ʾ����Ҫ��¼���
      return;
	
    Re = CHECK_STRUCT_SUM(Prog_Record);
    if(1 != Re)//ASSERT(1 EQ Re))
    {
      ASSERT_FAILED();
      Clr_Prog_Record_Ram();
    }

    //һ���µĲ���Ա,����ǰһ������Ա�й�����,��֮ǰ���ϲ���Ա�Ĳ����ý���
    if((Prog_Record.Prog_Flag.All_Flag != 0 && memcmp((INT8U *)Operator_ID.Op_ID, (INT8U *)Prog_Record.Op_ID, 4) !=0))
    {
      Event_Data_Proc(ID_EVENT_PROG, EVENT_OCCUR);  
    }
    
    DIS_PD_INT;   
    
    if((Prog_Record.Prog_Flag.All_Flag != 0 && memcmp((INT8U *)Op_ID, (INT8U *)Prog_Record.Op_ID, 4) !=0))
    {    
      //���¿�ʼ�µ�һ�ֱ��
      Prog_Record.Prog_Flag.All_Flag = 0;
      //�����̵ı�ʶ
      mem_set((void *)&Prog_Record.PDI, 0xFF, sizeof(Prog_Record.PDI), (void *)&Prog_Record.PDI, sizeof(Prog_Record.PDI));
    }

  
    //��ǰ�ı�ʶ˳��������
    Num = S_NUM(Prog_Record.PDI);
    for(i = 1; i < Num; i ++)
    {
      Prog_Record.PDI[Num - i] = Prog_Record.PDI[Num - i -1]; 
    }

    Prog_Record.PDI[0] = PDI;
    
    if(Prog_Record.Prog_Flag.All_Flag EQ 0)//��һ����̼�¼,��¼�³��α��ʱ��
    {
      mem_cpy((INT8U *)Prog_Record.Op_ID, (INT8U *)(INT8U *)Op_ID, sizeof(Op_ID),\
              (INT8U *)Prog_Record.Op_ID, sizeof(Prog_Record.Op_ID));
      //mem_cpy((INT8U *)Prog_Record.Time, (INT8U *)Cur_Time2.Time, sizeof(Cur_Time2.Time), (INT8U *)Prog_Record.Time, sizeof(Prog_Record.Time));
    }
    //���һ����ʱ����Ϊ��̿�ʼʱ��--ʵ���Ǳ�̽���ʱ��
    mem_cpy((INT8U *)Prog_Record.Time, (INT8U *)Cur_Time2.Time, sizeof(Cur_Time2.Time), (INT8U *)Prog_Record.Time, sizeof(Prog_Record.Time));
    
    Prog_Record.Prog_Flag.All_Flag = 1;
    
    SET_STRUCT_SUM(Prog_Record);
    SET_STRUCT_SUM(Event_Data);

    EN_PD_INT;
}

/*
//���ڱ�̼�¼��ʱ�䴦��
void Prog_Record_Time_Proc()
{
  static S_Int32U Sec = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int32U Prog_Ram_Posi = {CHK_BYTE, 0, CHK_BYTE};
  
  if(Sec.Var != Sec_Timer_Pub || Prog_Ram_Posi.Var != Prog_Record.Posi)
  {
    //if(Prog_Record.Posi >= 10)
      ///Event_Data_Proc();//��̼�¼
    
    
  
    //if
  }
  
}
*/
//��ȡ�޸ĵĲ�����ʶ
//����1��ʾ�в��������޸�,*pDIָ���޸Ĳ����ı�ʶ
//����0��ʾû�в��������޸�
INT8U Get_Para_Modify(PROTO_DI* pDI)
{
  INT8U i, Posi, Re, Cur_Task_ID; 
  INT8U Count = 0; 

  TRACE();

  Re = CHECK_STRUCT_SUM(Para_Modify); 
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  } 

  Cur_Task_ID = OS_Get_Cur_Task_ID(); 

  if(Cur_Task_ID >= OS_TASK_NUM)
  {
    ASSERT_FAILED(); 
    return 0;
  }

  Posi = Para_Modify.Posi[Cur_Task_ID]; //��������޸Ĳ����洢λ��
  if(Posi >= CHK_PARA_NUM)
  {
    ASSERT_FAILED();
    Posi = 0;
  }

  Count = 0; //��ѯ����������ÿ������ѯCHK_PARA_NUM������ 
  i = (Posi + 1) % CHK_PARA_NUM; //��Posi + 1��ʼ��ѯ��Posi
  while(Count <= CHK_PARA_NUM)
  {
    if(Para_Modify.Buf[Cur_Task_ID][i] != 0)// !=  0��ʾ�ò�����δ����
    {
      *pDI = Para_Modify.Buf[Cur_Task_ID][i]; 
      if(Cur_Task_ID < OS_TASK_NUM)
        Para_Modify.Buf[Cur_Task_ID][i] = 0; 

      SET_STRUCT_SUM(Para_Modify); 
      return 1;
    }
    Count ++ ; 
    i = (i + 1) % CHK_PARA_NUM;
  }
  SET_STRUCT_SUM(Para_Modify); 
  return 0; //û���ҵ��򷵻�0 
}

//��ȡĳ��DI�����Ĵ洢����, ����S_ROM����S_RAM
INT8U Get_DLT645_Data_Storage_Type(PROTO_DI PDI)
{
  INT16U i; 
  INT8U Spec_Flag; 

  TRACE();

  for(i = 0; i < S_NUM(P_Data_Info); i ++)
  {
    if(Check_P_Data_Single(i, PDI, FOR_COMM, &Spec_Flag))
    {
      return P_Data_Info[i].Storage;
    }
  }

  ASSERT_FAILED();
  return S_ROM;
}

//��ȡĳ��DI����Դ���ݵ�����
INT8U Get_DLT645_Data_Src_Type(PROTO_DI PDI)
{
  INT16U i; 
  INT8U Spec_Flag; 

  TRACE();
  
  for(i = 0; i < S_NUM(P_Data_Info); i ++)
  {
    if(Check_P_Data_Single(i, PDI, FOR_COMM, &Spec_Flag))
    {
      return P_Data_Info[i].Src_Format;
    }
  }

  ASSERT_FAILED();
  return S_INTU;
}

//��ȡЭ�����ݵ�����ȼ�
INT8U Get_P_Data_PSW_Level(PROTO_DI PDI)
{
  INT16U i; 
  INT8U Spec_Flag;

  TRACE();

  for(i = 0; i < S_NUM(P_Data_Info); i ++)
  {
    if(Check_P_Data_Single(i, PDI, FOR_COMM, &Spec_Flag))
    {
      return Get_PSW_Flag_Map_Level(P_Data_Info[i].PSW_Flag);
    }
  }
  ASSERT_FAILED(); 
  return PSW_NULL;
}

//DI�Ƿ���һ����DI?
//�����򷵻�0,���򷵻�>0������,��ֵ��ʾ��N��8λ��0xFFλ
INT8U Check_Block_DI(PROTO_DI PDI)
{
  TRACE();

  if((PDI & 0x0000FFFF) != 0x0000FFFF)
  {
    if((PDI & 0x000000FF) EQ 0x000000FF)
      return 1;
    else if((PDI & 0x0000FF00) EQ 0x0000FF00)
      return 2;
  }
  
  return 0;
}


//���P_Data_Info[Index]������������,�Ƿ��������ݿ�DI�е�һԱ
//Index��ʾP_Data_Info�е�һ������
//DI��ʾЭ��DI,��һ��Block���͵�DI
//Data_Flag����
INT8U Check_P_Data_In_Block(INT16U Index, PROTO_DI PDI)
{
  INT8U i;

  INT8U* pDI, * pNum, * p;

  TRACE();
  
  if(P_Data_Info[Index].DI_Set_Flag EQ 0)
    return 0;

  pDI = (INT8U *) &P_Data_Info[Index].PDI;
  pNum = (INT8U *) &P_Data_Info[Index].Num;
  p = (INT8U *) &PDI;

  for(i = 0; i < 4; i ++)
  {
    if((*p EQ 0xFF) || (*p EQ * pDI) || (*p >= *pDI && *p < *pDI + *pNum))
    {
      pDI ++;
      pNum ++;
      p ++;
    }
    else
    {
      break;
    }
  }

  if(i EQ 4) //4�ֽھ�����Ҫ��
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//���ĳ��PDI�Ƿ�Ӧ�÷���Ӧ��
//��Զ��Ԥ���ѵ�����£����ص�ѵ���Ϣ��Ӧ�𣬲���ʾ
INT8U Check_PDI_Answer_En(PROTO_DI PDI)
{
  if(PREPAID_EN EQ 0 || PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //Ԥ���ѹ���û�д򿪻��ߺ�Զ��Ԥ���ѱ������Ϣ����ʵ
  {
    if((PDI & 0xFFFFFF00) EQ 0x04000F00 && (PDI & 0x000000FF) <= 0x00000004) //�������������Ϣ
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x04001000 && (PDI & 0x000000FF) <= 0x00000005) //������������Ϣ
      return 0;
    
    if(PDI EQ 0x04000108)
      return 0;
    
    if(PDI EQ 0x0280000B) //��ǰ���ݵ��
      return 0;
    
    if((PDI & 0xFFFF0000) EQ 0x04060000 && (PDI & 0x0000FF00) <= 0x00000300) //���ݵ����ز���
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x04050100 || (PDI & 0xFFFFFF00) EQ 0x04050200) //��ʱ���
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x00900100) //ʣ�������͸֧����
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x00900200) //ʣ���͸֧���
      return 0;
  }
  
  return 1;
}


//��ȡĳ��������������
//Index��ʾDI��ʾ����P_Data_Info�е�����
//pPara��ʾ�������
//pDst��ʾĿ�껺������ʼ��ַ
//pDst_Start��DstLenһ���޶�pDst�ͷ������ݳ��� 
//Data_Flag, FOR_COMM��ʾ�����ṩ��ͨ��, FOR_DISP��ʾ�����ṩ����ʾ
//pErr, ����״̬������
//��ȡ�ɹ�������:���س���>0����1 EQ *pErr
INT16U Get_DLT645_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len; 
  INT8U Re,Spec_Flag;
  
  if(Check_PDI_Answer_En(PDI) EQ 0) //���������Ӧ��
    return 0;
  
  //�ҵ������������ڵ�P_Data_Info�е�����
  //������P_Data_Info�е�ĳ��DI�������Ӧ��DI_Equ
  Re = Check_P_Data_Single(Index, PDI, Data_Flag, &Spec_Flag);
  if(Re EQ 0)
  {
    return 0;
  }

  if(pDst + P_Data_Info[Index].Dst_Len > pDst_Start + DstLen)//�����Ƿ�����?
  {
    ASSERT_FAILED();  
    return 0;
  }
  
  if((Spec_Flag & 0x40) != 0)//�����������Ƕ�������
  {
    //ע�⣺Get_DLT645_Spec_Single_Data�����ڲ����ٵ���_Get_DLT645_Data����
    //��˴˺����ڲ����ܻ������ź���SEM_PUB_BUF0
    Len = Get_DLT645_Spec_Single_Data(PDI, Spec_Flag, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag); //�ȵ��������������ȡ
  }
  else
  {
    Len = Get_DLT645_Normal_Single_Data(Index, PDI, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag);  
  }
  
  return Len;
}

//10��a�η�
INT32U Pow_10x(INT8U a)
{
  INT8U i; 
  INT32U Val = 1; 

  for(i = 0; i < a; i ++)
  {
    Val = Val * 10;
  } 
  return Val;
}

//���һ��DI�Ƿ��Ƕ�������DI
INT8U Check_Freeze_Data_PDI(PROTO_DI PDI)
{
  if((PDI & 0xFF000000) EQ 0x05000000)
    return 1;
  else
    return 0;
}
//#pragma optimize =s high 
//�ж��Ƿ���Դ�P_Data_Info[Index]���DI����
//DIΪ�����ݼ������ݿ������
//*pSec_Flag���ڷ��ظ������ݵ������־
//����1��ʾ��P_Data_Info�е�������.DI�����2��ʾ��.DI_EQU���͵�������, 0��ʾ��P_Data_Info��û�����������
INT8U Check_P_Data_Single(INT16U Index, PROTO_DI PDI, INT8U Data_Flag, INT8U* pSpec_Flag)
{
  PROTO_DI Num; 
  //PROTO_DI TempDI;
  INT16U i; 
  INT8U* pDI, * p;
  INT8U* pNum;

  //TRACE();//�˴��򿪹켣���ٻᵼ��ʱ��ܳ����ɵ�֮

  *pSpec_Flag = P_Data_Info[Index].Spec_Flag;

  if(P_Data_Info[Index].Num EQ 0)
  {
    if(P_Data_Info[Index].PDI EQ PDI)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    Num = P_Data_Info[Index].Num; 

    //����������������Ϊ�ͷ�����أ���Ҫ���⴦��
    if(SPEC_ENERGY EQ P_Data_Info[Index].Spec_Flag || \
       SPEC_DEMAND EQ P_Data_Info[Index].Spec_Flag)//������ص����������ַ��ʵ��ܵ�
    {
      if(((P_Data_Info[Index].Num & 0x0000FF00) >> 8) EQ MAX_RATES)
        Num = (P_Data_Info[Index].Num & 0xFFFF00FF) + ((Multi_Rate_Para.Rates + 1) << 8);
    }

    pDI = (INT8U *) &P_Data_Info[Index].PDI + 3;
    pNum = (INT8U *) &Num + 3;//(INT8U *) &P_Data_Info[Index].Num;
    p = (INT8U *) &PDI + 3;

    for(i = 0; i < 4; i ++)
    {
      if((*p EQ *pDI) || (*p >= *pDI && *p < *pDI + *pNum))
      {
        pDI --;
        pNum --;
        p --;
      }
      else
        break;
    }

    if(i EQ 4)
      return 1;
    else
      return 0;
  }
}

//��ȡĳ��DI����P_Data_Info�е�Index
INT16U Get_P_Data_Index(PROTO_DI PDI)
{
  INT8U Spec_Flag; 
  INT16U i; 

  TRACE();
  
  Clear_Ext_Dog();
  
  for(i = 0; i < S_NUM(P_Data_Info); i ++)
  {
    if(Check_P_Data_Single(i, PDI, FOR_COMM, &Spec_Flag) != 0)
    {
      return i;
    }
  }  
  return NULL_2BYTES;
}

//Ѱ��Э��֡����ĳ��pSrc��ʼ��buf��
//Ѱ��һ��645֡
//pSrc�������Ļ�������ʼλ��
//SrcLen,����������
//pOffset,�ҵ���֡����ʼƫ�ƣ������SrcLen
//����ֵ:�ҵ���֡��
INT16U Search_Protocol_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset)
{
  INT16U i;
  INT16U Len;
  
  if(SrcLen<10)
    return 0;
  
  for(i=0;i<SrcLen-10;i++)
  {
    if(*(pSrc+i) EQ 0x68 &&*(pSrc+i+7) EQ 0x68)
    {
      Len=*(pSrc+i+9);//�����򳤶�
      Len+=12;//����֡ͷβ
      if((i+Len)<=SrcLen && Check_Frame_Format(pSrc+i,Len) EQ 1)//֡��ʽ��ȷ
      {
        *pOffset=i;
        return Len;       
      }
    }
  }
  return 0;
}

//Ѱ��Э��֡����ĳ��pSrc��ʼ��buf��
//Ѱ��һ��645֡
//pSrc�������Ļ�������ʼλ��
//SrcLen,����������
//pOffset,�ҵ���֡����ʼƫ�ƣ������SrcLen
//����ֵ:�ҵ���֡��
INT16U Simple_Search_Frame(INT8U *pSrc,INT16U SrcLen,INT16U *pOffset)
{
  INT16U i;
  INT16U Len;
  
  if(SrcLen<10)
    return 0;
  
  for(i=0;i<SrcLen-10;i++)
  {
    if(*(pSrc+i) EQ 0x68 &&*(pSrc+i+7) EQ 0x68)
    {
      Len=*(pSrc+i+9);//�����򳤶�
      Len+=12;//����֡ͷβ
      *pOffset = i;
      if(0x16 EQ *(pSrc+i+Len-1))//�ж�֡ͷ��֡β
      return Len;
    }
  }
  return 0;
}

//������ȡ��ַ��֡
//pSrcΪԴ֡��SrcLenΪ֡��
//pDstΪĿ�껺����
//����ΪӦ��֡��>0��ʾ�յ�һ����ȷ�Ķ���ַ֡
//�ú�����Ҫ�����ڲ���
INT8U Phase_Get_Addr_Frame(INT8U *pSrc, INT16U SrcLen)
{
  INT16U Len;
  INT8U *pDst;
  
  if(Get_Main_Init_Flag() !=  MAIN_INITING || Meter_Addr_Ready_Flag.Var != DATA_READY) //��ʼ��״̬�ŵ��ظú���
    return 0;
  
  if(*(pSrc + 8) != 0x13 || Check_Frame_Format(pSrc, SrcLen) EQ 0)  
   return 0;
  
  Len = 0;
  pDst = (INT8U *)Temp_Buf_PUCK;
  if(memcmp(pSrc + 1, (INT8U *)BROAD_ADDR_AA, 6) EQ 0) //��������0x13�����ҵ�ַ��ȫ0xAA
  {
     memcpy(pDst + 10, (INT8U *)Meter_Addr.Addr[0], 6);//, pDst, sizeof(Temp_Buf_PUCK)); 
     Len = 6;
     Len = DLT645_Data_Pack(0, 0x93, pDst + 10, Len, pDst, pDst, sizeof(Temp_Buf_PUCK));  
     UART1_SendData(pDst, Len);
     Debug_Print("Rcv Get_Addr Frame, Send:\r\n");
     DEBUG_BUF_PRINT(pDst, Len, PRINT_HEX, 0);
  }
  
  return Len;
}

//�ڻ���������645֡,������֮������Ӧ��֡
//Ch,��ʾ������Դͨ��
//pSrc,Դ������
//SrcLen,Դ����������
//pDst,Ŀ�껺��������
//pDst_Start,��DstLenһ���޶�Ӧ��֡����
//���س���,0��ʶû��Ӧ��֡��>0��Ӧ��֡����Ϊ֡��
INT16U Rcv_PROTOCOL_Frame_Proc(INT8U Ch,INT8U *pSrc,INT16U SrcLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen)
{
  INT16U Len;//Offset;
  
  //Len=Search_Protocol_Frame(pSrc,SrcLen,&Offset);
  //if(Len>0)
  //{
    Len=Rcv_DLT645_Data_Proc(Ch,pSrc,SrcLen,pDst,pDst_Start,DstLen);
    return Len;
  //}

  //return 0;
}

//Index��ʾDI��ʾ����P_Data_Info�е�����
//pPara��ʾ�������
//pDst��ʾĿ�껺������ʼ��ַ
//pDst_Start��DstLenһ���޶�pDst�ͷ������ݳ��� 
//Data_Flag, FOR_COMM��ʾ�����ṩ��ͨ��, FOR_DISP��ʾ�����ṩ����ʾ
//pErr, ����״̬������
//��ȡ�ɹ�������:���س���>0����1 EQ *pErr
INT16U _Get_DLT645_Normal_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT8U* pSrc; 
  //INT8U Re, Spec_Flag; 
  INT16U Len; //Bef_Mon; 
  INT32U U_Data;
  INT16S S16_Data;
  INT32S S_Data;

  TRACE();

  if(!(pDst >= pDst_Start && pDst < pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  //ȡ��Դ����
  if(!(Index < S_NUM(P_Data_Info)))
  {
    ASSERT_FAILED();
    return 0;
  }

  //��������������´���:
  if(S_RAM EQ P_Data_Info[Index].Storage)//���ݴ洢��RAM��
  {
    pSrc = (INT8U *) (P_Data_Info[Index].pSrc);// + P_Data_Info[Index].Src_Off; 
    pSrc += (PDI - P_Data_Info[Index].PDI) * P_Data_Info[Index].Src_Len;
  }
  else if(S_ROM EQ P_Data_Info[Index].Storage)//���ݴ洢��EEROM����Flash��
  {
    Len = 0; 
    //��EEROM����Flash�ж�ȡ���ݣ�ƫ���Ѿ��ڴ洢���γɣ���˲���Ҫpsrc��ֵʱȡƫ��
    Len = Read_Storage_Data(PDI, (void *) Pub_Buf, (void *) Pub_Buf, sizeof(Pub_Buf)); 
    if(Len EQ 0)
    {
      ASSERT_FAILED();
      return 0;
    }
    pSrc = (INT8U *) Pub_Buf;// + P_Data_Info[Index].Src_Off;
  }
  else
  {
    ASSERT_FAILED(); 
    return 0;
  }

  //��������ת��
  if(S_INTU EQ P_Data_Info[Index].Src_Format)//Դ���ݵ��������޷�������
  {
    U_Data = 0; 
    if(S_LEN4 EQ P_Data_Info[Index].Src_Len)
      mem_cpy(&U_Data, pSrc, 4, &U_Data, sizeof(U_Data)); //Data = *(INT32U *)(pSrc); 
    else if(S_LEN2 EQ P_Data_Info[Index].Src_Len)
      mem_cpy(&U_Data, pSrc, 2, &U_Data, sizeof(U_Data)); //Data = *(INT16U *)(pSrc); 
    else if(S_LEN1 EQ P_Data_Info[Index].Src_Len)
      mem_cpy(&U_Data, pSrc, 1, &U_Data, sizeof(U_Data)); //Data = *(INT8U *)(pSrc); 
    else
    {
      ASSERT_FAILED(); 
      return 0;
    }

    Len = P_Data_Info[Index].Dst_Len; //ת��������BCD���ݵĳ���

    if((Data_Flag & FOR_SRC) EQ 0)
    {
      U_Data = U_Data / Pow_10x(P_Data_Info[Index].Dst_Start); //Դ����/Dst_Start��ʾ��Ҫ��Ŀ������
      //���ʵ���ʾ��С��λ��
      if((Data_Flag & FOR_DISP) EQ FOR_DISP)
      {
        if((PDI & 0xFFFF0000) EQ 0x02030000 || (PDI & 0xFFFF0000) EQ 0x02040000 || (PDI & 0xFFFF0000) EQ 0x02050000)
        {
          if(DemandDisBit <= 4) //������ʾС��λ��
            U_Data = U_Data / Pow_10x(4 - DemandDisBit);
        }
      }
      
      Hex2Bcd(U_Data, (INT8U *) Pub_Buf, Len, (void *) Pub_Buf, sizeof(Pub_Buf)); //ת����BCD��
    }
    else
    {
      //if(!(P_Data_Info[Index].Dst_Len EQ 4 && P_Data_Info[Index].Dst_Len EQ P_Data_Info[Index].Src_Len))
        //ASSERT_FAILED();
      
      mem_cpy((INT8U *) Pub_Buf, &U_Data, Len, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    }
    mem_cpy(pDst, (INT8U *) Pub_Buf, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); //��ȡ���ݸ��Ƶ�Ŀ�껺����
    return P_Data_Info[Index].Dst_Len;
  }
  else if(S_BCD EQ P_Data_Info[Index].Src_Format || S_BIN EQ P_Data_Info[Index].Src_Format)//Դ����������BCD���ͣ���ʾ������и�ʽת��
  {
    mem_cpy(pDst, pSrc + P_Data_Info[Index].Dst_Start, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); //���Ƶ�Ŀ�껺����  
    return P_Data_Info[Index].Dst_Len;
  }
  else if(S_INTS EQ P_Data_Info[Index].Src_Format)//Դ�����������з�������
  {
    S_Data = 0; 
    if(S_LEN4 EQ P_Data_Info[Index].Src_Len)
      mem_cpy(&S_Data, pSrc, 4, &S_Data, sizeof(S_Data)); //Data = *(INT32U *)(pSrc); 
    else if(S_LEN2 EQ P_Data_Info[Index].Src_Len)
    {
      mem_cpy(&S16_Data, pSrc, 2, &S16_Data, sizeof(S16_Data)); //Data = *(INT32U *)(pSrc); 
      S_Data = (INT32S)S16_Data;
    }
    else
    {
      ASSERT_FAILED();
      return 0;
    }

    Len = P_Data_Info[Index].Dst_Len; //ת��������BCD���ݵĳ���

    if((Data_Flag & FOR_SRC) EQ 0)
    {
      S_Data = S_Data / (INT32S)Pow_10x(P_Data_Info[Index].Dst_Start); //Դ����/Dst_Start��ʾ��Ҫ��Ŀ������
      S_Hex2Bcd(S_Data, (INT8U *) Pub_Buf, Len, (void *) Pub_Buf, sizeof(Pub_Buf)); //ת����BCD��
    }
    else
    {
      ASSERT(P_Data_Info[Index].Dst_Len EQ 4 && P_Data_Info[Index].Dst_Len EQ P_Data_Info[Index].Src_Len);
      mem_cpy((INT8U *) Pub_Buf, &S_Data, Len, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    }

    mem_cpy(pDst, (INT8U *) Pub_Buf, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); //��ȡ���ݸ��Ƶ�Ŀ�껺����
    return P_Data_Info[Index].Dst_Len; 
    //Ŀǰ�޸����� 
  }

  ASSERT_FAILED(); 
  return 0;
}

//Index��ʾDI��ʾ����P_Data_Info�е�����
//pPara��ʾ�������
//pDst��ʾĿ�껺������ʼ��ַ
//pDst_Start��DstLenһ���޶�pDst�ͷ������ݳ��� 
//Data_Flag, FOR_COMM��ʾ�����ṩ��ͨ��, FOR_DISP��ʾ�����ṩ����ʾ
//pErr, ����״̬������
//��ȡ�ɹ�������:���س���>0����1 EQ *pErr
INT16U Get_DLT645_Normal_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len;
  
  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  Len = _Get_DLT645_Normal_Single_Data(Index, PDI, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag);
  OS_Mutex_Post(PUB_BUF_SEM_ID);
  
  return Len;
}

//��һ�����ݿ������, ����0x901F֮��, ��������0x90FF֮��ģ�������ֻ��DI[0]L = 0F
//DI��ʾ���ݱ�ʶ��, ��������DI[0]L = 0F; 
//pDst��ʾĿ�����ݻ�����
//pDst_Start��DstLenһ��綨Ŀ�����ݳ���
INT16U Get_DLT645_Block_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U i, j, k; 
  INT16U Len, TempLen; 
  PROTO_DI TempDI; 
  INT8U Re, Num;
  static S_Int8U Bak_i = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Bak_k = {CHK_BYTE, 0, CHK_BYTE};

  TRACE();

  if(!(pDst >= pDst_Start && pDst < pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  j = Check_Block_DI(PDI);
  if(j EQ 0)
  {
    ASSERT_FAILED();
    return 0;
  } 

  Len = 0;   
  
  //����������ʱ���û�к������ݣ������������ݶ�ȡ
  if((Frame_Ack_Info.Follow_Flag EQ 0) && (Frame_Ack_Info.Read_Follow_Flag EQ 1))
    Frame_Ack_Info.Read_Follow_Flag = 0;
  
  if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//����������
    i = Bak_i.Var;
  else
    i = 0;
      
  for(; i < S_NUM(P_Data_Info); i ++)
  {
    Re = Check_P_Data_In_Block(i, PDI); 
    if(0 < Re)
    {
      Num = (INT8U) (((P_Data_Info[i].Num >> ((j - 1) * 8))) & 0x000000FF);

      //��ʶ�ĵڶ����ֽ���0xFF�������������ߵ����������
      if((j EQ 2) && (P_Data_Info[i].Spec_Flag EQ SPEC_ENERGY || P_Data_Info[i].Spec_Flag EQ SPEC_DEMAND))
      {
        if((Data_Flag & FOR_EVENT) EQ FOR_EVENT) //�¼�Ӧ��ȡ���з�������
        {
          if(Num EQ (MAX_RATES + 1))
            Num = MAX_RATES + 1;
          else
            ASSERT_FAILED();
        }
        else
        {
          if(Num EQ (MAX_RATES + 1))
            Num = Multi_Rate_Para.Rates + 1;
          else
            ASSERT_FAILED();
        }
      }

      if(Num EQ 0) //0����������һ��
        Num = 1;
      
      TempDI = PDI & (~((INT32U)0xFF << ((j - 1) * 8)));
      TempDI = TempDI | (P_Data_Info[i].PDI & ((INT32U)0xFF << ((j - 1) * 8)));
      
      if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//����������
        k = (INT8U)Bak_k.Var;
      else
        k = 0;
        
      for(; k < Num; k ++)
      {
        OS_Mutex_Pend(TRANS_BUF_SEM_ID);
        TempLen = Get_DLT645_Single_Data(i, TempDI + (k << ((j - 1) * 8)), (void *) Zero, 0, (INT8U *)Trans_Temp_Buf, (INT8U *)Trans_Temp_Buf, sizeof(Trans_Temp_Buf), Data_Flag);
        OS_Mutex_Post(TRANS_BUF_SEM_ID);
        
        if(Len + TempLen >= 200)
          break;
        
        mem_cpy(pDst + Len, (INT8U *)Trans_Temp_Buf, TempLen, pDst_Start, DstLen);
        Len += TempLen;
        
        /*
        //����ǿ鳭�������ݣ�����Ҫ�ӿ�ָ���
        if(Check_Freeze_Data_PDI(TempDI + (k << ((j - 1) * 8))) EQ 1)
        {
          Len ++;
          *(pDst + Len -1) =0xAA;
        }
        */
      } 
      
      Bak_k.Var = 0;      
      
      if(k != Num)
        break;

    }
  }
  
  if(i != S_NUM(P_Data_Info))//�к�������,������ѭ������ i != SUM(P_Data_Info)
  {
    Bak_i.Var = i; //������ѭ����ʼ
    Bak_k.Var = k; //����Сѭ����ʼ
    Frame_Ack_Info.Follow_Flag = 1; //�к�������
  }
  else
  {
    Bak_i.Var = 0; //������ѭ����ʼ
    Bak_k.Var = 0; //����Сѭ����ʼ
    Frame_Ack_Info.Follow_Flag = 0; //�޺�������    
  }

  return Len;
}



//INT16U Get_Protocol_Single_Data_Index
//��ȡ645����
//DI, 645Э���ʶ
//pPara, ��ڲ���, ����֡��������
//pDst, Ŀ�����ݻ�����
//pDst_Start��DstLenһ���޶�pDst�Ͷ������ݳ��ȵķ�Χ
//DataFlag, FOR_DISP��ʾ��ȡ�������Ǹ���ʾ�ã�FOR_DISP��ʾ����ʾ��
//����ʱ��ȡ�������ݳ���
INT16U _Get_DLT645_Data(PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag, INT8U* pType)
{
  INT16U Len, Index;

  TRACE();

  *pType = S_BCD;//Ĭ����������
  
  Index = Get_P_Data_Index(PDI);
  if(Index != NULL_2BYTES)
  {
    Len = Get_DLT645_Single_Data(Index, PDI, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag);
    *pType = P_Data_Info[Index].Src_Format;
    return Len;
  }
  else if(Check_Block_DI(PDI) != 0)
  {
    Len = Get_DLT645_Block_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
    return Len;
  }
  ASSERT_FAILED();
  Debug_Print("_Get_DLT645_Data return len = 0, PDI = 0x%lx",PDI);
  return 0;
}

//��ȡ645���ݵļ򵥺���
INT16U Get_DLT645_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Type; 
  INT16U Len; 

  TRACE();

  Debug_Print("Get_DLT645_Data, PDI = 0x%lx", PDI);
  Len = _Get_DLT645_Data(PDI, (void *) Zero, 0, pDst, pDst_Start, DstLen, FOR_COMM, &Type); 
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    return 0;
  }
  else
  {
    return Len;
  }
}

//��ȡ645���ݵļ򵥺���, ר�ṩ����ʵ�������
INT16U Get_DLT645_Data_For_Disp(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U *pType)
{
  INT16U Len; 

  TRACE();
  Len = _Get_DLT645_Data(PDI, (void *) Zero, 0, pDst, pDst_Start, DstLen, FOR_DISP, pType); 
  return Len; 
  /*
  if(ASSERT(Len>0))
    return 0; 
  else
    return Len; 
  */
}

//��ȡ������Ϣ
INT16U Get_Factory_Info_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i;
  INT8U Temp[10];
  
   if(PDI EQ 0x04800001) //����汾��
   {
     if(PREPAID_METER > 0) //�ѿر�
     {
       Temp[0] = 'P'; //�ѿر�
       
       if(PREPAID_MODE EQ PREPAID_MONEY)
         Temp[1] = 'M'; //�����
       else
         Temp[1] = 'E'; //������
       
       if(PREPAID_MONEY_MODE EQ PREPAID_RATE)
         Temp[2] = 'T'; //��������
       else
         Temp[2] = 'S'; //������
       
       i = 3;
     }
     else
     {
       Temp[0] = 'M'; //�๦�ܱ�      
       i = 1;
     }
     
     if(NET_METER EQ CARRIER_METER) //�ز���
       Temp[i] = 'C';
     else if(NET_METER EQ GPRS_METER) //���߱�
       Temp[i] = 'W';
     else
       Temp[i] = ' ';
     i ++;
     Temp[i] = '\0';
     
     mem_set(pDst, ' ', 32, pDst_Start, DstLen);
     mem_cpy(pDst, (INT8U *)SOFTWARE_VERSION, sizeof(SOFTWARE_VERSION) - 1, pDst_Start, DstLen);
     mem_cpy(pDst + sizeof(SOFTWARE_VERSION) - 1, Temp, strlen((char *)Temp), pDst_Start, DstLen);
     Reverse_data(pDst, 32);
     return 32;
   }
   else if(PDI EQ 0x0400040D)//Э��汾��
   {
     for(i = 0; i < 16; i ++)
     {
       if(i <  sizeof(PROTOCOL_VERSION))
         pDst[15-i] = PROTOCOL_VERSION[i];
       else 
         pDst[15-i] = ' ';  
     } 
     return 16;
     
   }
   else
     return 0;
   
   //return 32;
}

//��ȡͨ��ģ��״̬
INT16U Get_Module_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  if(PDI EQ 0x0EA20000)
  {
    *pDst = Module_Comm_Status.Var;
    return 1;
  }
  
  return 0;
}

//��ȡROM�е�����
INT16U Get_Proto_Rom_Data(PROTO_DI PDI, INT8U *pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT32U Temp;
  INT16U Len;
  INT8U Re;

  if(PDI != _SDI_RD_ROM)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Temp = 0;
  mem_cpy(&Temp, (INT8U *)pPara + 1, 4, &Temp, sizeof(Temp));
  Len=0;
  mem_cpy(&Len, (INT8U *)pPara + 5, 2, &Len, sizeof(Len));
  if(Len > 200)
    Len = 200;
  
  if((INT8U *)pDst + Len <= (INT8U *)pDst_Start + DstLen)
  {
    if(*(INT8U *)pPara EQ 0)//MEM_ID EQ 0��ʾ��ȡ�ڴ�����
    {
      mem_cpy(pDst, (INT8U *)Temp, Len, pDst_Start, DstLen);
      Re = 1;
    }
    else
    {
      OS_Mutex_Pend(PUB_RW_ROM_ID);
      Re = Read_PHY_Mem_PUCK(*(INT8U *)pPara - 1, Temp, pDst, Len, pDst_Start, DstLen);
      OS_Mutex_Post(PUB_RW_ROM_ID);
    }
    return (Re EQ 1)?Len:0;
  }
  else
  {
    ASSERT_FAILED();
    return 0;
  }    
  
}
//��ȡ����������
INT16U Get_DLT645_Spec_Single_Data(PROTO_DI PDI, INT8U Spec_Flag, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  TRACE();

  if(!(pDst >= pDst_Start && pDst < pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  
  if(Spec_Flag EQ SPEC_ENERGY)
  {
    return Get_Energy_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
  }
  else if(Spec_Flag EQ SPEC_DEMAND)
  {
    return Get_Demand_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
  }
  else if(Spec_Flag EQ SPEC_S_EVENT)
  {
    return Get_Event_Separate_Proto_Data(PDI, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_C_EVENT)
  {
    return Get_Event_Cumu_Proto_Data(PDI, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_VOLSTAT)
  {
    return Get_VolStat_Proto_Data(PDI, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_LOAD)
  {
    return Get_Load_Proto_Data(PDI, pPara, ParaLen, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_FREEZE)
  {
    return Get_Freeze_Proto_Data(PDI, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_EXTEND)
  {
    return Extend_Get_Proto_Data(PDI, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_TIME)
  {
    return Get_Clock_Proto_Data(PDI, pDst, pDst_Start, DstLen); 
  }
  else if(Spec_Flag EQ SPEC_FAC_INFO)
  {
    return Get_Factory_Info_Proto_Data(PDI, pDst, pDst_Start, DstLen); 
  }
  else if(Spec_Flag EQ SPEC_RATE_INFO)
  {
    return Get_Rate_Info_Data(PDI, pDst, pDst_Start, DstLen); 
  }
  else if(Spec_Flag EQ SPEC_MODULE)
  {
    return Get_Module_Proto_Data(PDI, pDst, pDst_Start, DstLen); 
  }
  else if(Spec_Flag EQ SPEC_RD_ROM)
  {
    return Get_Proto_Rom_Data(PDI, pPara, ParaLen, pDst, pDst_Start, DstLen);
  }
  else if(Spec_Flag EQ SPEC_PREPAID_ENERGY)
  {
    return Get_Prepaid_Energy_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag);
  }
  else if(Spec_Flag EQ SPEC_PREPAID_EVENT)
  {
    return Get_Prepaid_Event_Proto_Data(PDI, pDst, pDst_Start, DstLen, Data_Flag); 
  }

  return 0;
}

//ת��Դ���ݵ�Э������
INT16U Convert_Src_2_Proto_Data(PROTO_DI PDI[], INT8U DI_Num, INT8U* pSrc, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i;
  INT16U Src_Len, Dst_Len;
  INT16U Index;
  INT32U U32_Data;
  INT32S S32_Data;
  INT16U S16_Data;

  TRACE();

  Src_Len = 0;
  Dst_Len = 0;
  for(i = 0; i < DI_Num; i ++)
  {
    Index = Get_P_Data_Index(PDI[i]);//ͨ��Index0��ȡԴ���ݸ�ʽ

    if(Index EQ NULL_2BYTES)
    {
      ASSERT_FAILED();
      return 0;
    }

    if(P_Data_Info[Index].Src_Format EQ S_INTU)
    {
      U32_Data = 0;
      mem_cpy(&U32_Data, pSrc + Src_Len, P_Data_Info[Index].Src_Len, &U32_Data, sizeof(U32_Data));

      if(P_Data_Info[Index].Dst_Start > 0)
        U32_Data = U32_Data / Pow_10x(P_Data_Info[Index].Dst_Start);  

      Hex2Bcd(U32_Data, pDst + Dst_Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
      Src_Len += P_Data_Info[Index].Src_Len;
      Dst_Len += P_Data_Info[Index].Dst_Len;
    }
    else if(P_Data_Info[Index].Src_Format EQ S_INTS)
    {
      if(P_Data_Info[Index].Src_Len EQ sizeof(INT16S))
      {
        S16_Data = 0;
        mem_cpy(&S16_Data, pSrc + Src_Len, P_Data_Info[Index].Src_Len, &S16_Data, sizeof(S16_Data));

        if(P_Data_Info[Index].Dst_Start > 0)
          S16_Data = S16_Data / (INT16S)Pow_10x(P_Data_Info[Index].Dst_Start);

        S_Hex2Bcd(S16_Data, pDst + Dst_Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
      }
      else if(P_Data_Info[Index].Src_Len EQ sizeof(INT32S))
      {
        S32_Data = 0;
        mem_cpy(&S32_Data, pSrc + Src_Len, P_Data_Info[Index].Src_Len, &S32_Data, sizeof(S32_Data));

        if(P_Data_Info[Index].Dst_Start > 0)
          S32_Data = S32_Data / (INT32S)Pow_10x(P_Data_Info[Index].Dst_Start);

        S_Hex2Bcd(S32_Data, pDst + Dst_Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
      }
      else
        ASSERT_FAILED();

      Src_Len += P_Data_Info[Index].Src_Len;
      Dst_Len += P_Data_Info[Index].Dst_Len;
    }
    else if(P_Data_Info[Index].Src_Format EQ S_BCD)
    {
      if(P_Data_Info[Index].Src_Len != P_Data_Info[Index].Dst_Len)
        ASSERT_FAILED();

      mem_cpy(pDst + Dst_Len, pSrc + Src_Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);

      Src_Len += P_Data_Info[Index].Src_Len;
      Dst_Len += P_Data_Info[Index].Dst_Len;
    }
    else
      ASSERT_FAILED();
  }
  return Dst_Len;
}

//void Convert_S_Proto_Data(INT32U Data, INT8U Div, INT8U *pDst, INT8U *pDst_Start, INT8U DstLen)
//void Convert_U_Proto_Data(INT32S Data, INT8U Div, INT8U *pDst, INT8U *pDst_Start, INT8U DstLen)
//Э�����ݵļӼ�
//DI���ݶ�Ӧ�ı�ʶ������
//DI_Num��ʶ�����
//pData0,ͨ��Get_DLT645_Data ��õ����ݣ�FOR_SRC��־
//pData1,,ͨ��Get_DLT645_Data ��õ����ݣ�FOR_SRC��־
//BCD����,Ҫ����ľ���pData0-pData1
//pDst,Ŀ�껺����,pDst_Start��DstLenһ���޶����س���
INT16U Proto_Data_Add_Dec(INT8U Data_Flag, INT8U Add_Or_Dec, PROTO_DI PDI[], INT8U DI_Num, INT8U* pData0, INT8U* pData1, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i;
  INT16U Index, Len;
  INT32U U32_Data0, U32_Data1;
  INT32S S32_Data0, S32_Data1;
  INT16U S16_Data0, S16_Data1;

  TRACE();

  Len = 0;
  for(i = 0; i < DI_Num; i ++)
  {
    Index = Get_P_Data_Index(PDI[i]);//ͨ��Index0��ȡԴ���ݸ�ʽ

    if(Index EQ NULL_2BYTES)
    {
      ASSERT_FAILED();
      return 0;
    }

    if(P_Data_Info[Index].Src_Len != P_Data_Info[Index].Dst_Len)
      ASSERT_FAILED();

    if(P_Data_Info[Index].Src_Format EQ S_INTU)
    {
      U32_Data0 = 0;
      U32_Data1 = 0;

      mem_cpy(&U32_Data0, pData0 + Len, P_Data_Info[Index].Src_Len, &U32_Data0, sizeof(U32_Data0));
      mem_cpy(&U32_Data1, pData1 + Len, P_Data_Info[Index].Src_Len, &U32_Data1, sizeof(U32_Data1));

      //Debug_Print("Proto_Data_Add_Dec:PDI=0x%lx,Data0=%lu,Data1=%lu,Len=%d",PDI[i],U32_Data0,U32_Data1,P_Data_Info[Index].Src_Len);

      if(Add_Or_Dec EQ DATA_ADD)
        U32_Data0 += U32_Data1;
      else
        U32_Data0 = (U32_Data0 > U32_Data1) ? (U32_Data0 - U32_Data1) : 0;

      if(Data_Flag EQ FOR_SRC)
        mem_cpy(pDst + Len, &U32_Data0, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
      else
      {
        U32_Data0 = U32_Data0 / Pow_10x(P_Data_Info[Index].Dst_Start);//�����
        Hex2Bcd(U32_Data0, pDst + Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
      } 

      Len += P_Data_Info[Index].Src_Len;
    }
    else if(P_Data_Info[Index].Src_Format EQ S_INTS)
    {
      if(P_Data_Info[Index].Src_Len EQ sizeof(INT16S))
      {
        S16_Data0 = 0;
        S16_Data1 = 0;

        mem_cpy(&S16_Data0, pData0 + Len, P_Data_Info[Index].Src_Len, &S16_Data0, sizeof(S16_Data0));
        mem_cpy(&S16_Data1, pData1 + Len, P_Data_Info[Index].Src_Len, &S16_Data1, sizeof(S16_Data1));
        
        //Debug_Print("Proto_Data_Add_Dec:PDI=0x%lx,S16_Data0=%d,S16_Data1=%d,Len=%d",PDI[i],S16_Data0,S16_Data1,P_Data_Info[Index].Src_Len);

        if(Add_Or_Dec  EQ  DATA_ADD)
          S16_Data0 += S16_Data1;
        else
          S16_Data0 = S16_Data0 - S16_Data1;

        if(Data_Flag EQ FOR_SRC)
          mem_cpy(pDst + Len, &S16_Data0, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
        else
        {
          S16_Data0 = S16_Data0 / (INT16S)Pow_10x(P_Data_Info[Index].Dst_Start);//�����    
          S_Hex2Bcd(S16_Data0, pDst + Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
        }

        Len += P_Data_Info[Index].Src_Len;
      }
      else if(P_Data_Info[Index].Src_Len EQ sizeof(INT32S))
      {
        S32_Data0 = 0;
        S32_Data1 = 0;

        mem_cpy(&S32_Data0, pData0 + Len, P_Data_Info[Index].Src_Len, &S32_Data0, sizeof(S32_Data0));
        mem_cpy(&S32_Data1, pData1 + Len, P_Data_Info[Index].Src_Len, &S32_Data1, sizeof(S32_Data1));

        //Debug_Print("Proto_Data_Add_Dec:PDI=0x%lx,S32_Data0=%ld,S32_Data1=%ld,Len=%d",PDI[i],S32_Data0,S32_Data1,P_Data_Info[Index].Src_Len);

        if(Add_Or_Dec  EQ  DATA_ADD)
          S32_Data0 += S32_Data1;
        else
          S32_Data0 = S32_Data0 - S32_Data1;

        if(Data_Flag EQ FOR_SRC)
          mem_cpy(pDst + Len, &S32_Data0, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
        else
        {
          S32_Data0 = S32_Data0 / (INT32S)Pow_10x(P_Data_Info[Index].Dst_Start);//�����
          S_Hex2Bcd(S32_Data0, pDst + Len, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen);
        }

        Len += P_Data_Info[Index].Src_Len;
      }
      else
        ASSERT_FAILED();
    }
    else
      ASSERT_FAILED();
  }
  return Len;
}

//����Ƿ���Ҫ�������
//����ֵ:
//CLEAR_END_FLAG��û��������Ҫ���
//CLEAR_ENERGY_FLAG,��Ҫ�������
//CLEAR_DEMAND_FLAG,��Ҫ�������
//CLEAR_VOSTAT_FLAG,��Ҫ�����ѹͳ��
//CLEAR_EVENT_FLAG,��Ҫ�����ѹͳ��
INT32U Check_Clear_Data_Flag()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Clear_Flag);
  Re &= CHECK_STRUCT_SUM(Clear_Flag);
  if(1 != Re)
  {
    ASSERT_FAILED();
    return CLEAR_END_FLAG;
  }
  else
  {
    return Clear_Flag.Flag;
  }
}

//���645֡��ʽ, pFrame��ʾ֡��ʼ��ַ, FrameLen��ʾ֡�ĳ���
INT8U Check_Frame_Format(INT8U* pFrame, INT8U FrameLen)
{
  INT8U Sum; 

  TRACE();

  if(!(0x68 EQ * pFrame && 0x68 EQ * (pFrame + 7) && 0x16 EQ * (pFrame + FrameLen - 1)))//�ж�֡ͷ��֡β
  {
    return 0;
  } 

  Sum = 0;
  Get_Buf_MulitByte_Sum(pFrame, FrameLen - 2, 1, &Sum, 1); //�ж�У���
  if(!(Sum EQ * (pFrame + FrameLen - 2)))
  {
    return 0;
  }  

  return 1;
}

//���645֡�еı��ַ�Ƿ���ȷ?
//Ch��֡����Դͨ��
//Addr��֡�еı��ַ
//Ctrl_Code��֡�еĿ�����
//*pAck_Flag��ʾ�Ƿ���ҪӦ��
INT8U Check_Frame_Meter_Addr(INT8U Ch, INT8U Addr[], INT8U Ctrl_Code,INT8U *pAck_Flag)
{
  INT8U i; 

  TRACE();

  *pAck_Flag = 1;//һ���������ҪӦ��
  
  if(memcmp(Addr, (void *) Meter_Addr.Addr[0], 6) EQ 0)//��ַ��ȷ
  {
    if(C_ADJUST_TIME != Ctrl_Code) //�㲥Уʱ�����ñ����ַ 
      return 1;
    else
      return 0;
  } 

  //֡�еı��ַ��Meter_Addr�����еı��ַ��һ��
  //���ж��Ƿ��ǹ㲥��ַ
  if(memcmp(Addr, BROAD_ADDR_99, 6) EQ 0)
  {
    //�㲥��ַ99�߱���Ȩ�ޣ��㲥Уʱ���㲥���ᡢ���ö๦�ܶ���
    //�㲥Уʱ�͹㲥���᲻��ҪӦ��
    if(C_FREEZE_DATA EQ Ctrl_Code ||\
       C_ADJUST_TIME EQ Ctrl_Code ||\
       C_PORT EQ Ctrl_Code)
    {
      //if(C_FREEZE_DATA EQ Ctrl_Code || C_ADJUST_TIME EQ Ctrl_Code)
      *pAck_Flag = 0;//�㲥����͹㲥Уʱ����ҪӦ��
      return 1;
    }
    else
      return 0;
  }
  else if(memcmp(Addr, (void *) BROAD_ADDR_AA, 6) EQ 0)//ȫAA��ַ, ֻ�ܾ߱���Ȩ��
  {
    //��ַAA�߱���Ȩ�ޣ������ݻ��߶�ͨ�ŵ�ַ��дͨ�ŵ�ַ
    if(C_READ_DATA EQ Ctrl_Code ||\
       C_READ_FOLLOW_DATA EQ Ctrl_Code ||\
       C_READ_ADDR EQ Ctrl_Code ||\
       C_SET_ADDR EQ Ctrl_Code)
    {
      return 1;
    }
    else if(C_SET_DATA EQ Ctrl_Code ||\
            C_CLR_DEMAND EQ Ctrl_Code ||\
            C_CLR_ALL EQ Ctrl_Code ||\
            C_CLR_EVENT EQ Ctrl_Code)
    {
      if(Check_Meter_Factory_Status()) //����״̬������AA��ַ�����������
        return 1;
    }

    return 0;
  }
  else //�Ƿ��ͨ�����ַ,ֻ�ж����ݵ�Ȩ��
  {
    //��λΪ0xAA, ��λΪ���ַ��ͬ���������ñ�����ȣ��͵�ַ����Ҫ��1�ֽ�ƥ��
    for(i = 0; i < 6; i ++)
    {
      if(Addr[5 - i] != 0xAA) //iΪAA����
      {
        if(memcmp(Addr, (void *) Meter_Addr.Addr[0], 6 - i) EQ 0)
        {
          if(C_READ_DATA EQ Ctrl_Code ||\
             C_READ_FOLLOW_DATA EQ Ctrl_Code)         
            return 1;
          else
            return 0;
        }
        else
          return 0;
      }
    }
  }
  return 0;
}

//���ݴ��
//Ch��ʾͨ����
//Ctrl_Code������
//pSrc��Ҫ�����������
//SrcLen�����򳤶�
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�pDst��֡��
INT16U DLT645_Data_Pack(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT16U SrcLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i;

  TRACE();

  if(!(pDst >= pDst_Start && pDst + SrcLen + 15 <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  Clear_Ext_Dog();

  *(pDst) = 0x68;
  //if(CH_RS485_1 EQ Ch || CH_IRAD EQ Ch)//���ݲ�ͬͨ����䲻ͬ�ı��ַ
  mem_cpy(pDst + 1, (void *) Meter_Addr.Addr[0], 6, pDst_Start, DstLen);
  //else
  //mem_cpy(pDst+1,(void *)Meter_Addr.Addr[1],6,pDst_Start,DstLen);

  *(pDst + 7) = 0x68;
  *(pDst + 8) = Ctrl_Code;//������
  *(pDst + 9) = (INT8U) SrcLen;
  mem_cpy(pDst + 10, pSrc, SrcLen, pDst_Start, DstLen);

  for(i = 0; i < SrcLen; i ++)//������+0x33
  {
    *(pDst + 10 + i) += 0x33;
  }
  Get_Buf_MulitByte_Sum(pDst, SrcLen + 10, 1, pDst + 10 + SrcLen, 1);
  *(pDst + SrcLen + 11) = 0x16;
  return SrcLen + 12;
}

/*
������Ϣ��ERR
Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
����	��������	��ʱ������	��ʱ������	ͨ�����ʲ��ܸ���	�����/δ��Ȩ	����������	��������
ע��	0��������Ӧ��������1������Ӧ����������Bit1��2��3��4��5��6����Ĵ������⣬�����������ΪBit0��������

#define OTHER_ERR              0x01//��������
#define NO_REQ_DATA_ERR        0x02//����������
#define AUTH_ERR               0x04//����-Ȩ�޴�
#define MODI_BAUD_ERR          0x08//�޸�ͨ���ٶȴ�
#define YEAR_PERIOD_EXCEED_ERR 0x10//��ʱ������
#define DATE_PERIOD_EXCEED_ERR 0x20//��ʱ������
#define RATE_EXCEED_ERR        0x40//��������
*/
//����������ݵĸ�ʽ����ȷ����1�����󷵻�0
INT8U Set_Data_Format_Check(INT16U Index, PROTO_DI PDI, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Re;
  INT8U Spec_Flag;
  //INT8U Temp[5];
  
  TRACE();

  //��P_Data_Info�в��ҵ�����
  //for(i=0;i<S_NUM(P_Data_Info);i++)
  Re = Check_P_Data_Single(Index, PDI, FOR_COMM, &Spec_Flag);
  if(1 EQ Re)
  {
    if(P_Data_Info[Index].Src_Format EQ S_BCD)//�ҵ�����Ҹ���Ҫ����BCD��ʽ
    {
      if(!Check_BCD_Data(pSrc, SrcLen))//��������������BCD?
      {
        SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
        return 0;
      }
    }
    
    if(P_Data_Info[Index].Dst_Len != SrcLen) //���ݳ��Ȳ���?
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      return 0;
    }
  }
  
  if(PDI EQ 0x04000201) //��ʱ������
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_YEAR_PERIODS)//��ʱ������
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, YEAR_PERIOD_EXCEED_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000202)//��ʱ�α�����
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_DATE_TABLES)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000203)//��ʱ������
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_DATE_PERIODS)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, DATE_PERIOD_EXCEED_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000204)//��������
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_RATES) 
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, RATE_EXCEED_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000205) //������������
  {
    if(Bcd2Hex(pSrc,2) > MAX_YEAR_HOLIDAYS)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      return 0;       
    }
  }
  else if(PDI EQ 0x04000207) //Ԥ�����ݶ���
  {
    if(Bcd2Hex(pSrc,1) > PREPAID_MAX_STEP)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);      
      return 0;
    }
  }
  else if(PDI EQ 0x04000409 || PDI EQ 0x0400040A)//���޹����峣��
  {
    if(Judge_Pulse_Legal(Bcd2Hex(pSrc,3)) EQ 0) //������峣���ĺϷ���
      return 0;
  }
  else if(PDI EQ 0x04000401) //дͨ�ŵ�ַ
  {
    if(Check_WR_Comm_Addr(pSrc) EQ 0)
      return 0;
  }

/*
  if(PDI EQ 0x04010000 || PDI EQ 0x04020000)//������ʱ����
  {
    for(i = 0; i < MAX_YEAR_PERIODS; i ++)
    {
      if(i < Multi_Rate_Para.Year_Period) //С�ڷ�������Χ��ÿ�����ݵĸ�ʽ��������ȷ
      {
        Bcd2Hex_Buf(pSrc + i*3, 3, Temp, Temp, sizeof(Temp));
        if(Temp[0] EQ 0 || Temp[0] > Multi_Rate_Para.Date_Table)
        {
          SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
          return 0;
        }
      }
    }
  }
  else if((PDI & 0xFFFFFF00) EQ 0x04010000 || (PDI & 0xFFFFFF00) EQ 0x04020000)
  {
     for(i = 0; i < Multi_Rate_Para.Date_Table; i ++)
     {
        Bcd2Hex_Buf(pSrc + i*3, 3, Temp, Temp, sizeof(Temp));
        if(Temp[0] > Multi_Rate_Para.Rates)//��������������
        {
          SET_BIT(Sys_Run_Flag.Err_Flag, RATE_EXCEED_ERR);
          return 0;
        } 
        else if(Temp[0] EQ 0 || Temp[1] > 60 || Temp[2] >24)
        {
          SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
          return 0;        
        }
     }
  }
*/
  return 1;
}

//�������óɹ��ĺ���
void Set_Para_Aft_Proc(PROTO_DI PDI, INT8U *pSrc)
{
  if(PDI EQ 0x04000103) //�������ڲ����޸ģ���Ҫ���¿�ʼһ���µ���������
  {
    //�������ڷ����޸�
    if(Bcd2Hex_Byte(*pSrc) != Demand_Para.Period)
    {
      Clr_Demand_Accu();
    }
  }  
}

//��������ߴ���
void Save_Op_ID(INT8U *pSrc)
{
  DIS_PD_INT;
  //mem_cpy((INT8U *)Operator_ID.Last_Op_ID, (INT8U *)Operator_ID.Op_ID, 4, (INT8U *)Operator_ID.Last_Op_ID, sizeof(Operator_ID.Last_Op_ID));
  //���˲���ԱID
  mem_cpy((INT8U *)Operator_ID.Op_ID, pSrc, 4, (INT8U *)Operator_ID.Op_ID, sizeof(Operator_ID.Op_ID));
  SET_STRUCT_SUM(Operator_ID);
  SET_STRUCT_SUM(Event_Data);
  EN_PD_INT;  
}

//�������ݴ���
//*pAck_Flag��ʾ�Ƿ��Ѿ�����Ӧ��1��ʾ�ں����ڲ��Ѿ�����Ӧ��0��ʾû�и�Ӧ��
INT8U Set_Data_Proc(INT8U Ch, INT8U* pSrc, INT8U SrcLen, INT8U *pAck_Flag)
{
  INT8U Re;
  PROTO_DI PDI;
  INT16U i;
  INT8U Single_Flag, Spec_Flag;

  TRACE();
  
  *pAck_Flag = 0;
  PDI = 0;
  mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));//DI=*(INT16U *)pSrc;
  
  if(Check_PDI_Answer_En(PDI) EQ 0)
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, NO_REQ_DATA_ERR);//�Ƿ�����
    return 0;//0;    
  }
  
  //���������ID
  //����ǰһ�β���ԱID
  Record_Op_ID(pSrc + 8);
  
  if(!(SrcLen >= 12))//������ʶ������������8�ֽ�
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);//�Ƿ�����
    return 0;//0;
  }

  Single_Flag = 0;//�Ƿ��Ǹ���������������������ݼ�֮��
  for(i = 0; i < S_NUM(P_Data_Info); i++)
  {
    if(Check_P_Data_Single(i, PDI, FOR_COMM, &Spec_Flag) > 0)
    {
      Single_Flag = 1;
      break;
    }
  }

  if(Single_Flag EQ 0)//����������������
  {
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);//���ݱ�ʶ��
    return 0;
  }

  Re = Set_Data_Format_Check(i, PDI, pSrc + 12, (INT8U) (SrcLen - 12));//������ݸ�ʽ��
  if(0 EQ Re)
  {
    ASSERT_FAILED();
    return 0;
  }


  Set_Prog_Record_Pre_Porc(Ch, PDI, pAck_Flag);
  //DI������֮����6�ֽڵ�����Ŷ  
  if((Spec_Flag & 0x80) != 0)
  {
    Re = Set_Spec_Data_Proc(PDI, Spec_Flag, pSrc + 12, (INT8U) (SrcLen - 12));    
  }//�����������
  else
  {
    Re = Set_DI_Data_Proc(i, PDI, pSrc + 12, (INT8U) (SrcLen - 12));
  }

  if(1 EQ Re)
  {
    Set_Para_Modify(PDI);//�����޸ļ�¼
    Set_Prog_Record(PDI, (INT8U *)Operator_ID.Op_ID);//��̼�¼
    Set_Para_Modi_DI(PDI);//����������־
    Set_Para_Aft_Proc(PDI, pSrc + 12); //���ò����ɹ��ĺ���
  }
  else
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);//�Ƿ�����
  }
  return Re;
}

//����ĳDI������
//DI,���ݱ�ʶ
//pSrc,Դ������ʼָ��
//SrcLen,Դ���ݳ���
INT8U Set_DI_Data_Proc(INT16U Index, PROTO_DI PDI, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Re;

  TRACE();


  //return 0;
  Re = 1;
  Re &= Write_Storage_Data(PDI, pSrc, SrcLen);
  
  return Re;
}

//��ģ��ͨ�ŵ���չ������
INT8U Set_Module_Proto_Data(PROTO_DI PDI, INT8U *pSrc, INT8U SrcLen)
{
  if(PDI EQ 0x0EA20000)//дģ��ͨ��״̬
  {
    Module_Comm_Status.Var = *pSrc;
    return 1;
  }
  else if(PDI EQ 0x0EA20001)//�򿪵��дʹ��
  {
    Module_Set_Meter_Status.Set_En_Mins = 10;
    SET_STRUCT_SUM(Module_Set_Meter_Status);
    return 1;
  }
  
  return 0;
}

//�ж��Ƿ�Ӧ�����⴦���������
INT8U Set_Spec_Data_Proc(PROTO_DI PDI, INT8U Spec_Flag, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Temp[4];
  //INT8U Re;
  
  TRACE();
  
  if(Spec_Flag EQ SPEC_TIME)//��ǰʱ��
  {
    return Set_Clock_Proto_Data(PDI, pSrc, SrcLen);
  }
  else if(Spec_Flag EQ SPEC_MODULE)//ģ��ͨ��״̬
  {
#if NET_METER != NONET_METER   
    return Set_Module_Proto_Data(PDI, pSrc, SrcLen);
#else
    return 0;
#endif    
  }
  else if(Spec_Flag EQ SPEC_ADJ) //У�������Լ�����˲ʱ����
  {
    if(PDI EQ _PDI_ADJ_METER_CLR)
    {
      if(*pSrc EQ 1)
       Set_Def_Adj_Para(); 
      else if(*pSrc EQ 2)
       Set_Def_Para_Except_Adj(); 
      else if(*pSrc EQ 3)
        Set_All_Def_Data();
      else
        return 0;
    }
    else if(PDI EQ _PDI_ADJ_INSTANT_DATA)
    {
      return Set_Cal_Com_Data(pSrc, SrcLen);
    }
    return 0; 
  }
  else if(Spec_Flag EQ SPEC_SET_ENG)
  {
    return Set_Energy_Start(PDI, pSrc, SrcLen); 
  }
  else if(Spec_Flag EQ SPEC_METER_ID)
  {
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL) //���طѿز���д���
      return 0;
    
    Read_Storage_Data(_SDI_FAR_PASSWORD_STATE, Temp, Temp, sizeof(Temp));
    if(Temp[0] EQ 0) //������Կ״̬
    {
      return Write_Storage_Data(SDI_METER_ID, pSrc, SrcLen); 
    }
  }
  return 0;
}

//�����������
INT8U Set_Freeze_Data_Peirod(INT8U *pSrc, INT8U SrcLen)
{
  INT8U Temp[4]= {0x99,0x99,0x99,0x99};
  INT16U Len;
  
  if(SrcLen != 0x04 || Check_BCD_Data(pSrc, 4)!=1)
    return 0;
  
  if(memcmp(pSrc, Temp, 4) EQ 0)//��ǰ��4��99
  {
    //��������
    Len = Event_Separate_Proc(ID_EVENT_INSTANT_FREEZE, EVENT_OCCUR, EVENT_REAL);
    if(Len > 0)
      return 1;
    else 
      return 0;
  }  
  
  mem_cpy((void *)Freeze_Para.Period_Freeze_Time, pSrc, 4, (void *)Freeze_Para.Period_Freeze_Time, sizeof(Freeze_Para.Period_Freeze_Time));
  SET_STRUCT_SUM(Freeze_Para);
  
  return Write_Storage_Data(SDI_PERIOD_FREEZE_TIME, pSrc, 4);
}

//������Ҫ������ݱ�־
//��ڲ���:
//CLEAR_END_FLAG��û��������Ҫ���
//CLEAR_ENERGY_FLAG,��Ҫ�������
//CLEAR_DEMAND_FLAG,��Ҫ�������
//CLEAR_VOSTAT_FLAG,��Ҫ�����ѹͳ��
void Set_Clear_Data_Flag(INT32U Flag)
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Clear_Flag);
  ASSERT(1 EQ Re);
  Clear_Flag.Flag = Flag;
  SET_STRUCT_SUM(Clear_Flag);
}

//��ͨ�Ų����ʴ���
INT8U Set_CommBaud_Proc(INT8U Ch, INT8U* pSrc, INT8U SrcLen)
{
  TRACE();

  if(Ch EQ CH_RS485_1)//��һ·485
  {
    Write_Storage_Data(SDI_COMM1_BAUD, pSrc, 1);
    Set_Para_Modify(SDI_COMM1_BAUD);
    Set_Para_Modi_DI(SDI_COMM1_BAUD);//����������־
    return 1;
  }
  else if(Ch EQ CH_RS485_2)//��2·485
  {
    Write_Storage_Data(SDI_COMM2_BAUD, pSrc, 1);
    Set_Para_Modify(SDI_COMM2_BAUD); 
    Set_Para_Modi_DI(SDI_COMM2_BAUD);//����������־    
    return 1;
  }
  return 0;
}

//�޸����봦��
INT8U Set_PSW_Proc(INT8U* pSrc, INT8U SrcLen)
{
  INT8U Level;
  INT8U Re;
  STORA_DI SDI;

  TRACE();

  Level = pSrc[8];//��������ļ���
  if(Level <= 0x09)
  {
    /*
              if(Level EQ 0)
                SDI=PASSWORD_0;
              else if(Level EQ 1)
                SDI=PASSWORD_1;
              else
                SDI=PASSWORD_2;
              */
    SDI = Level + SDI_PSW0; 

    mem_cpy((void *) Cur_PSW.PSW[Level], pSrc + 9, 3, (void *) Cur_PSW.PSW[Level], sizeof(Cur_PSW.PSW[Level]));
    SET_STRUCT_SUM(Cur_PSW);
    Re = Write_Storage_Data(SDI, (void *) Cur_PSW.PSW[Level], sizeof(Cur_PSW.PSW[Level]));

    if(1 EQ Re)
    {
      Set_Para_Modify(SDI);
      return 1;
    }
    else
      ASSERT_FAILED();
  }
  return 0;
}

//�ж�дͨ�ŵ�ַ�Ƿ�Ϸ�
INT8U Check_WR_Comm_Addr(INT8U Addr[])
{
  if(memcmp(Addr, (INT8U *)BROAD_ADDR_99, 6) EQ 0 ||\
     memcmp(Addr, (INT8U *)BROAD_ADDR_AA, 6) EQ 0)
    return 0;
  else 
    return 1;
}

//д�豸��ַ����
//Ch��ʾ���ݵ�ͨ��
//pSrc,������ʼ��ַ
//SrcLen,���ݳ���
INT8U Set_MeterAddr_Proc(INT8U Ch, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Re;

  TRACE();

  if(Check_Meter_Prog_Status() EQ 0)
  {
    return 0;
  }

  if(Check_WR_Comm_Addr(pSrc) EQ 0) //�жϱ��ַ�����Ƿ�Ϸ�
    return 0;
  
  Re = Write_Storage_Data(SDI_COMM_ADDR, pSrc, 6);
  if(1 EQ Re)
  {
    mem_cpy((INT8U *)Meter_Addr.Addr[0], pSrc, 6, (INT8U *)Meter_Addr.Addr[0], sizeof(Meter_Addr.Addr[0]));
    SET_STRUCT_SUM(Meter_Addr);
    
    Set_Para_Modify(SDI_COMM_ADDR);
  }

  return Re;
}

//��ȡP_Data_Info����ĳ�Ա����
INT16U Get_P_Data_Info_Num()
{
  return S_NUM(P_Data_Info);
}

//����յ���DLT645���ݵĳ����Ƿ�Ϸ�
INT8U Check_DLT645_Data_Len(INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen)
{
  TRACE();
  
  if(Ctrl_Code EQ C_READ_DATA && SrcLen>=4)//һ�������ǣ����ֽڵı�ʶ�����Ƕ�ȡ����ʱ���ĸ��������ǣ��ֽ�
    return 1;
  else if(Ctrl_Code EQ C_READ_FOLLOW_DATA)//����������
    return 1;
  if(Ctrl_Code EQ C_SET_DATA && SrcLen>=4) //д����
    return 1;
  else if(Ctrl_Code EQ C_ADJUST_TIME)
  {
  //if(Mode_Word.Mode[0].Bit.Bit4 EQ 1 && SrcLen EQ 0x0A)//�㲥Уʱ
      //return NO_ERR;
  if(SrcLen EQ 0x06)
      return 1;
  }
  else if(Ctrl_Code EQ C_SET_ADDR && SrcLen EQ 0x06)//дͨ�ŵ�ַ
    return 1;
  else if(Ctrl_Code EQ C_READ_ADDR && SrcLen EQ 0x00)//��ͨ�ŵ�ַ
    return 1;
  else if(Ctrl_Code EQ C_SET_COM_BAUD && SrcLen EQ 0x01)//����ͨ������
    return 1;
  else if(Ctrl_Code EQ C_SET_PSW && SrcLen EQ 0x0C)//�޸�����
    return 1;
  else if(Ctrl_Code EQ C_CLR_ALL && SrcLen EQ 0x08)//����������߶���
    return 1;
  else if(Ctrl_Code EQ C_CLR_DEMAND && SrcLen EQ 0x08)//������
    return 1;
  else if(Ctrl_Code EQ C_CLR_EVENT && SrcLen EQ 0x0C)//���¼�
    return 1;
  else if(Ctrl_Code EQ C_FREEZE_DATA && SrcLen EQ 0x04)//����
    return 1;
  else if(Ctrl_Code EQ C_CTRL && SrcLen EQ 0x10) //��������
    return 1;
  else if(Ctrl_Code EQ C_PORT && SrcLen EQ 0x01) //�๦�� �˿�����
    return 1;
  else if(Ctrl_Code EQ C_REMOTE_AUTH)
  return 1;
  return 0;
}

//��0x33
void Sub_33(INT8U *pSrc, INT8U SrcLen)
{
  INT8U i;
  
  for(i = 0; i < SrcLen; i ++)
    *(pSrc + i) = *(pSrc + i) - 0x33;
}

void Record_Op_ID(INT8U *pSrc)
{
  DIS_PD_INT;
  mem_cpy((void *)Operator_ID.Op_ID, pSrc, 4, (void *)Operator_ID.Op_ID, sizeof(Operator_ID.Op_ID));
  SET_STRUCT_SUM(Operator_ID);
  SET_STRUCT_SUM(Event_Data);
  EN_PD_INT;
}

void Record_Clear_Event_DI(INT8U *pSrc)
{
  DIS_PD_INT;
  mem_cpy((void *)&Clear_Event_PDI, pSrc, 4, (void *)&Clear_Event_PDI, sizeof(Clear_Event_PDI));
  SET_STRUCT_SUM(Event_Data);
  EN_PD_INT;  
}

//д���ݵ���ȷӦ��,������Ӧ����д���ݺʹ����¼���¼
void Send_Set_Data_Ack_Frame(INT8U Ch)
{
  INT8U Temp[15];
  INT16U Len;
  
  Len = DLT645_Data_Pack(Ch, (INT8U) (0x14 | 0x80), Temp, 0, Temp, Temp, sizeof(Temp)); 
  Send_HostData_Public_Puck(Ch,(INT8U *)Temp,Len);  
}

//645����֡�Ĵ���
//Ctrl_Code������
//pSrc, 645֡��ʼ
//SrcLen, ֡��
//pDst, Ŀ�껺����
//pDst_Start, Ŀ�껺������ʼ��ַ
//DstLen, Ŀ�껺��������
INT16U Rcv_DLT645_Data_Proc(INT8U Ch, INT8U* pFrame, INT8U FrameLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Type, Data_Type, Esam_Auth_Flag, Esam_Auth_Ok; 
  INT8U Data_PSW; //�޸�������Ҫ��Ȩ��
  INT8U User_PSW; //��ǰ�û�ӵ�е�Ȩ��
  INT8U Len1;
  INT8U Re, Ack_Flag, Set_Data_Ack_Flag; 
  static PROTO_DI PDI;
  PROTO_DI TempPDI;
  INT16U Len,Err_Flag; 
  INT8U Ctrl_Code, SrcLen; 
  INT8U* pSrc; 

  TRACE();
  
  //ErrFlag = 1; 
  Sys_Run_Flag.Err_Flag = 0; //������Ϣ������

  if(Check_Frame_Format(pFrame, FrameLen) EQ 0)
  {
    return 0;
  } 

  Ctrl_Code = *(pFrame + 8); 
  if(Check_Frame_Meter_Addr(Ch, pFrame + 1, Ctrl_Code, &Ack_Flag) EQ 0)
  {
    return 0;
  } 


  //�жϱ��ַ
  //ErrFlag = Err_Info.ErrFlag; 
  pSrc = pFrame + 10; //��������ʼ��ַ
  SrcLen = FrameLen - 12; //�����򳤶�

  //�������33
  Sub_33(pSrc, SrcLen);
  
  Esam_Auth_Flag = 0; //�Ƿ���Ҫ����Esam������֤
  Esam_Auth_Ok = 0; //Esam������֤�Ľ��

  if(PREPAID_EN > 0) //Ԥ���ѱ�
  {
    if(Ctrl_Code EQ C_SET_DATA) //���ò���
    {
      mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));
      Data_Type = Check_Data_Type(PDI);

      if(Data_Type EQ 1) //��һ������
      {
        Esam_Auth_Flag = 1;
        
        if(pSrc[4] != 0x99 || Set_Esam_Para(pSrc, SrcLen) EQ 0)//mac��֤ͨ��
          Esam_Auth_Ok = 0;
        else
        {
          Esam_Auth_Ok = 1;
          SrcLen = SrcLen - 4; //��������Ҫ��4 
        }
      }     
      else if(Data_Type EQ 2) //�ڶ�������
      {
        Esam_Auth_Flag = 1;
        
        Len1 = 0;
        if(pSrc[4] != 0x98 || Esam_Auth_Check(pSrc, SrcLen, &Len1) EQ 0)//mac��֤ͨ����ͬʱ����
        {
          Esam_Auth_Ok = 0;
          //��ʱ�������ʱ�α�Ҳ������02����������--�ͼ�Ҫ��!!
          //if(Check_Year_Date_Table_Data(PDI))
          {
            if(pSrc[4] EQ 0x02)
              Esam_Auth_Flag = 0;  
          }
        }
        else
        {
          Esam_Auth_Ok = 1;
          SrcLen = Len1;
        }
      }
    }
    else if(Ctrl_Code EQ C_CTRL) //��������
    {
      Esam_Auth_Flag = 1;
      
      if(pSrc[0] != 0x98 || Esam_Decrypt(pSrc, SrcLen) EQ 0)
        Esam_Auth_Ok = 0;
      else
      {
        Esam_Auth_Ok = 1;
        Reverse_data(pSrc + 8 + 2, 6);
        SrcLen = 16;
      }
    }
  }
  
  if(Check_Meter_Factory_Status()) //����״̬�²���Ҫ����Esam��֤Ҳ���������
  {
    if(Esam_Auth_Flag EQ 1 && pSrc[4] < 0x0A)  
      Esam_Auth_Flag = 0;  
  }
  
  if(Esam_Auth_Flag EQ 1)//��ʾ��ҪEsam��֤
  {
    if(Esam_Auth_Ok EQ 1)//��֤ͨ����
    {
      User_PSW = PSW_0;
      Data_PSW = PSW_1;      
    }
    else 
    {
      User_PSW = PSW_1;
      Data_PSW = PSW_0;      
    }

    if(Check_User_Authurity(User_PSW, Data_PSW) EQ 0)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, AUTH_ERR); //����Ȩ�޴�
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U)(Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);       
    }
  }

  Re = Check_DLT645_Data_Len(Ctrl_Code, pSrc, SrcLen); //�ж����ݳ���
  if(1 != Re)//���ݳ��Ȳ���
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR); //�Ƿ�����
    *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
    return DLT645_Data_Pack(Ch, (INT8U)(Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen); 
  }
  
  if(Esam_Auth_Flag EQ 0) //����Ҫ����Esam��֤���������������ݻ����Ƿ�Ԥ���ѵĶ๦�ܱ�
  {
    //��ȡִ�иò�����Ҫ��Ȩ�޼���
    Data_PSW = Get_P_Data_Info_Authority(Ch, Ctrl_Code, pSrc, SrcLen); 
    if(Data_PSW EQ PSW_NULL)//ASSERT())//û���ҵ������ݵ�������
    {
      ASSERT_FAILED();
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR); //�Ƿ�����
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);
    }
  
    //��ȡ��ǰ�û�ӵ�е�Ȩ�޼���
    User_PSW = Get_User_Authority(Ch, Ctrl_Code, pSrc, SrcLen); //��鵱ǰ�û�ӵ�е�Ȩ��
    if(User_PSW EQ PSW_NULL)//�����û�Ȩ�޲���
    {
      Debug_Print("User Authority Error"); 
      SET_BIT(Sys_Run_Flag.Err_Flag, AUTH_ERR); //Ȩ�޲���, Ҳ��Ϊ�������
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);
    }
  
    if(Check_User_Authurity(User_PSW, Data_PSW) EQ 0)//��ǰ�û�Ȩ�޸��ڻ���ڵ�ǰ����������Ҫ��Ȩ��, Ȩ�޲���!
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, AUTH_ERR); 
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);
    }
  }
  
  //Meter_Addr_Modify_Flag = 0; //���ַ���ñ�־  
  Cur_Comm_Ch.Ch = Ch; //���浱ǰͨ��ͨ��
  Set_Authority_Flag();	

  Clr_Ext_Inter_Dog();
  
  switch(Ctrl_Code)
  {
    case C_READ_DATA: //������
      Frame_Ack_Info.Read_Follow_Flag = 0;
      Frame_Ack_Info.Follow_Flag = 0;
      mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));  
      Len = _Get_DLT645_Data(PDI, pSrc + sizeof(PDI), (INT8U) (SrcLen - sizeof(PDI)), pDst + 14, pDst_Start, DstLen, FOR_COMM, &Type); 
      if(Len > 0 || Check_Load_Data_PDI(PDI)) //���ɼ�¼�����ڳ��������������Ӧ�÷�����ȷӦ��
      {
        Re = 1; 
        mem_cpy(pDst + 10, &PDI, sizeof(PDI), pDst_Start, DstLen); 
        Len += sizeof(PDI);
      }
      else
      {
        Re = 0;
        Len = 0;
        SET_BIT(Sys_Run_Flag.Err_Flag, NO_REQ_DATA_ERR);
      }
      break; 
    case C_READ_FOLLOW_DATA://����������
      if(Frame_Ack_Info.Follow_Flag EQ 0) //û�к������ݿ��Զ�ȡ
      {
        Re = 0;
        Len = 0;
        SET_BIT(Sys_Run_Flag.Err_Flag, NO_REQ_DATA_ERR);        
      }
      else
      {
        Frame_Ack_Info.Read_Follow_Flag = 1;
        Frame_Ack_Info.Frame_Seq = *(pSrc + sizeof(PDI));
        Len = _Get_DLT645_Data(PDI, pSrc + sizeof(PDI), (INT8U) (SrcLen - sizeof(PDI)), pDst + 14, pDst_Start, DstLen, FOR_COMM, &Type); 
        Re = (Len > 0)?1:0;
        mem_cpy(pDst + 10, &PDI, sizeof(PDI), pDst_Start, DstLen); 
        Len += sizeof(PDI); 
      }
      break; 
    case C_SET_DATA: //д����
      Re = Set_Data_Proc(Ch, pSrc, SrcLen, &Set_Data_Ack_Flag); 
      if(Set_Data_Ack_Flag) Ack_Flag = 0;
      //���⴦�������У���˲ʱ������Ӧ��,��Ϊ�ǹ㲥����
      mem_cpy(&TempPDI, pSrc, 4, &TempPDI, sizeof(TempPDI));
      if(TempPDI EQ _PDI_ADJ_INSTANT_DATA) Ack_Flag = 0;
      //----------------
      Len = 0; 
      break; 
    case C_FREEZE_DATA: //����
      Re = Set_Freeze_Data_Peirod(pSrc, SrcLen);
      if(memcmp(pFrame + 1, BROAD_ADDR_99, 6) EQ 0) //�㲥���᲻��ҪӦ��
        return 0;
      Len = 0;
      break;
    case C_ADJUST_TIME: //�㲥Уʱ
      Re = Adjust_Time_Proc(pSrc, SrcLen); 
      Len = 0; 
      return 0; //����ҪӦ��
    case C_SET_ADDR: //д���ַ
      Re = Set_MeterAddr_Proc(Ch, pSrc, SrcLen);
      if(Re EQ 1)
      {
        Len = 0;
        break;
      }
      else  //����ַʧ�ܲ�Ӧ��
        return 0; 
    case C_READ_ADDR://��ͨ�ŵ�ַ
      mem_cpy(pDst + 10, (INT8U *)Meter_Addr.Addr[0], 6, pDst_Start, DstLen); 
      Re = 1;
      Len = 6;
      break;
    case C_SET_COM_BAUD://��ͨ���ٶ�
      Re = Set_CommBaud_Proc(Ch, pSrc, SrcLen); 
      if(Re EQ 1)
      {
        *(pDst + 10) = *pSrc;
        Len = 1;
      }
      else
        Len = 0; 
      break; 
    case C_SET_PSW://�޸�����
      Re = Set_PSW_Proc(pSrc, SrcLen); 
      if(Re EQ 1)
      {
        mem_cpy(pDst + 10, pSrc + 8, 4, pDst_Start, DstLen); //ǰ4���ֽ�ΪDI0->DI3���仯
        Len = 4;
      }
      else
        Len = 0;      
      break; 
    case C_CLR_ALL://�����0

      if(METER_CLR_EN EQ 0)
      {
        Re = 0; 
        Len = 0; 
        break;         
      }
      
      Record_Op_ID(pSrc + 4);
      Set_Clear_Data_Flag(CLEAR_ALL_FLAG); 

      Re = 1; 
      Len = 0; 
      break; 
    case C_CLR_DEMAND://������0
      
      Record_Op_ID(pSrc + 4);
      Set_Clear_Data_Flag(CLEAR_DEMAND_FLAG);      

      Re = 1; 
      Len = 0; 
      break; 
    case C_CLR_EVENT://���¼�
      Re = CHECK_STRUCT_SUM(Event_Data);
      ASSERT(Re EQ 1);
      
      Record_Clear_Event_DI(pSrc + 8);  
      Record_Op_ID(pSrc + 4);

      if(Check_Event_Clr_PDI(Clear_Event_PDI) > 0)
      {
        Set_Clear_Data_Flag(CLEAR_EVENT_FLAG); 
        Re = 1;        
      }
      else
        Re = 0;
      Len = 0; 
      break; 
      
  case C_CTRL: //����
    Re = Remote_Protocol_Ctrl(pSrc + 8);
    if(Re EQ 1)
    {
      //��������ߴ���
      DIS_PD_INT;
      mem_cpy((INT8U *)Event_Data.Relay_Status.Op_ID, pSrc + 4, 4, (INT8U *)Event_Data.Relay_Status.Op_ID,sizeof(Event_Data.Relay_Status.Op_ID));
      SET_STRUCT_SUM(Event_Data);
      EN_PD_INT;
      //��¼�����ߴ���
      Record_Op_ID(pSrc + 4);
    }    
    Len = 0;
    break;
  case C_PORT: //�๦�ܶ���
    Re = Set_Port_Output_Ctrl(*pSrc);
    if(Re > 0)
    {
      *(pDst + 10) = *pSrc;
      Len = 1;      
    }

    break;
  case C_REMOTE_AUTH: //Զ����֤
    Len = 0;
    Re = Esam_Remote_Auth(pSrc, SrcLen, pDst + 10, (INT8U *)&Len, pDst_Start, DstLen);
    if(Re EQ 0) //��֤û��ͨ��
    {
      Err_Flag = GetSecurity_Auth_Err_Info();
      mem_cpy(pDst + 10, &Err_Flag, 2, pDst_Start, DstLen);
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 2, pDst, pDst_Start, DstLen);  
    }
    break;
  default:
    Re = 0; 
    Len = 0; 
    break;
  }
  
  if(Ack_Flag EQ 1)//��Ҫ����Ӧ��
  {
    if(Re EQ 1)
    {
      if(Frame_Ack_Info.Follow_Flag EQ 1)//�к������ݣ���Ҫ���ؿ�����0xA1
        Ctrl_Code = (Ctrl_Code | 0xA0);
      else
        Ctrl_Code = (Ctrl_Code | 0x80);    

      if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//��ǰ���յ���֡�Ƕ���������֡
      {
        *(pDst + 10 + Len) = Frame_Ack_Info.Frame_Seq;//����֡���
        Len ++;
      }
        
      Len = DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0x80), pDst + 10, Len, pDst, pDst_Start, DstLen); 
 
      //�жϱ��ַ�Ƿ������޸ģ�����Ѿ��޸ģ���Ҫ���¶�ȡ��Meter_Addr�����У���ȡֻ���ڴ��������
      //��ΪӦ��֡��Ȼ�����ϵı��ַ
 
  
      //ASSERT(1 EQ ErrFlag); 
      return Len;
    }
    else
    {
      //��Ӧ��������ʾ��
      if(0 EQ Sys_Run_Flag.Err_Flag)
      {
        SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      }
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      Len = 1; 
  
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, Len, pDst, pDst_Start, DstLen);
    }
  }
  else
    return 0;
}

//���ϵͳ��Э�����ݴ���
INT8U Check_Protocol_Data_Trans()
{
  INT32U i, j, k, l;
  INT16U Len;
  INT8U Re;
  PROTO_DI PDI;
  PROTO_DI Num;
  
  if(Check_Meter_Factory_Status() EQ 0)//����״̬�ż��
    return 0;
  
  Re = 1;
  
  OS_Mutex_Pend(TRANS_BUF_SEM_ID);
  
  for(i = 0; i < S_NUM(P_Data_Info); i ++)
  {
    Num = P_Data_Info[i].Num;
    if(P_Data_Info[i].Spec_Flag EQ SPEC_ENERGY || P_Data_Info[i].Spec_Flag EQ SPEC_DEMAND)
      Num = (P_Data_Info[i].Num & 0xFFFF00FF) + ((Multi_Rate_Para.Rates + 1) << 8);  
   
    for(j = 0; j < (Num & ((INT32U)0xFF << 2*8)) || j EQ 0; j = j + ((INT32U)0x01 << 2*8))
    {
       for(k = 0; k < (Num & ((INT32U)0xFF << 1*8)) || k EQ 0; k = k + ((INT32U)0x01 << 1*8))
       {
         for(l = 0; l < (Num & (INT32U)0xFF) || l EQ 0; l = l + 1)
         {
           PDI = P_Data_Info[i].PDI + j + k + l; 
           Len = Get_DLT645_Data(PDI, (INT8U *)Trans_Temp_Buf, (INT8U *)Trans_Temp_Buf, sizeof(Trans_Temp_Buf));
           
           if(Len EQ 0)
           {
             Re &= 0;
             ASSERT_FAILED();
             Debug_Print("Get_DLT645_Data Test Error, Return Len = 0, PDI = 0x%ld", PDI);
             Beep_For_Para();
           }
           
           if(CHECK_STRUCT_VAR(_Trans_Temp_Buf) EQ 0)
           {
             Re &= 0;            
             ASSERT_FAILED();
             Debug_Print("Get_DLT645_Data Test Error, Return buf overflowed = 0, PDI = 0x%ld, Len = %d", PDI, Len);
             Beep_For_Para();
           }             
         }         
         
       }
      
    }
  }
  OS_Mutex_Pend(TRANS_BUF_SEM_ID);  
  
  return Re;
}
#undef DATA_TRANS_C

