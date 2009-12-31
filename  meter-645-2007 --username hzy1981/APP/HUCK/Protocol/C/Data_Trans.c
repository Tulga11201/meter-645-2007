#define DATA_TRANS_C
#include "Includes.h"


#define SOFTWARE_VERSION "09122803 V1.3 " //软件版本号


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
  
  //当前以及历史电量
  //当前总组合有功), 有符号
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
  //历史总组合有功), 有符号
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

  //当前总正反有功), 无符号
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
  //历史总正反有功), 无符号
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

  //当前总组合无功), 有符号
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
  //历史总组合无功), 有符号
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

  //当前总四象限无功、正反视在), 无符号
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
  //历史总四象限无功、正反视在), 无符号
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

  //当前结算周期组合有功总
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
  //上一结算周期组合有功总
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
  //当前A相正反有功), 无符号
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
  //历史A相正反有功), 无符号
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

  //当前A相组合无功), 有符号
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
  //历史A相组合无功), 有符号
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

  //当前A相四象限无功、正反视在), 无符号
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
  //历史A相四象限无功、正反视在), 无符号
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

  //当前B相正反有功), 无符号
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
  //历史B相正反有功), 无符号
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

  //当前B相组合无功), 有符号
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
  //历史B相组合无功), 有符号
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

  //当前B相四象限无功、正反视在), 无符号
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
  //历史B相四象限无功、正反视在), 无符号
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

  //当前C相正反有功), 无符号
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
  //历史C相正反有功), 无符号
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

  //当前C相组合无功), 有符号
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
  //历史C相组合无功), 有符号
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

  //当前C相四象限无功、正反视在), 无符号
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
  //历史C相四象限无功、正反视在), 无符号
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

  //剩余电量
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

  //透支电量
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
  
  //剩余金额
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

  //透支金额
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
  //谐波相关，暂时不用
  /*
  //当前总谐波电能
  {INIT(PDI, 0x00800000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //历史总谐波电能
  {INIT(PDI, 0x00800001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  //当前A谐波电能
  {INIT(PDI, 0x00940000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //历史A谐波电能
  {INIT(PDI, 0x00940001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  //当前B谐波电能
  {INIT(PDI, 0x00A80000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //历史B谐波电能
  {INIT(PDI, 0x00A80001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  //当前C谐波电能
  {INIT(PDI, 0x00BC0000), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 
  //历史C谐波电能
  {INIT(PDI, 0x00BC0001), INIT(DI_Set_Flag, 1), INIT(PSW_Flag, PSW_RD_ONLY), INIT(Storage, S_RAM), INIT(pSrc, (void *)0), //INIT(Src_Off, 0), INIT(Src_Len, 4), INIT(Src_Format, S_INTU), INIT(Dst_Start, 1), INIT(Dst_Len, 4), INIT(Num, 0x00070000 | ((MAX_RATES + 1)  <<  8) | (MAX_ENERGY_SETTLE_NUM + 1)), INIT(Spec_Flag, SPEC_ENERGY)}, 

  */

  //---------------------------------------
  //当前以及历史需量
  //当前总正反有功), 无符号
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
  //历史总正反有功), 无符号
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

  //当前总组合无功), 有符号
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
  //历史总组合无功), 有符号
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

  //当前总四象限无功、正反视在), 无符号
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
  //历史总四象限无功、正反视在), 无符号
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

#if DEMAND_ACCU_PHASE_NUM >0 //A、B、C三相是否有功率累加单元?
  //当前A相正反有功), 无符号
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
  //历史A相正反有功), 无符号
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

  //当前A相组合无功), 有符号
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
  //历史A相组合无功), 有符号
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

  //当前A相四象限无功、正反视在), 无符号
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
  //历史A相四象限无功、正反视在), 无符号
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

  //当前B相正反有功), 无符号
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
  //历史B相正反有功), 无符号
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

  //当前B相组合无功), 有符号
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
  //历史B相组合无功), 有符号
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

  //当前B相四象限无功、正反视在), 无符号
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
  //历史B相四象限无功、正反视在), 无符号
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

  //当前C相正反有功), 无符号
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
  //历史C相正反有功), 无符号
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

  //当前C相组合无功), 有符号
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
  //历史C相组合无功), 有符号
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

  //当前C相四象限无功、正反视在), 无符号
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
  //历史C相四象限无功、正反视在), 无符号
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

  /////瞬时量数据///----------------------------------------------------------------
  //A相电压 1位小数
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
  //B相电压
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
  //C相电压
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
  
  //A相电流 3位小数
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
  //B相电流
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
  //C相电流
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

  //总瞬时有功功率
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
  //A相瞬时有功功率 3位小数
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
  //B相瞬时有功功率
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
  //C相瞬时有功功率
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

  //总瞬时无功功率
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
  //A相瞬时无功功率 3位小数
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
  //B相瞬时无功功率
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
  //C相瞬时无功功率
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

  //总视在功率
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
  //A相视在功率
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
  //B相视在功率
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
  //C相视在功率
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

  //总功率因素
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
  //A相功率因素
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
  //B相功率因素
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
  //C相功率因素
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

  //总相角
  //A相相角
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
  //B相相角
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
  //C相相角
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

  //总电压波形失真度
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
  //A相电压波形失真度
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
  //B相电压波形失真度
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
  //C相电压波形失真度
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

  //总相角
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
  //A相相角
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
  //B相相角
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
  //C相相角
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

  //零线电流
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
  //电网频率
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
  //一分钟有功总平均功率
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
  //当前有功需量
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
  //当前无功需量
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
  //当前视在需量
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
  //表内温度
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
  //时钟电池电压(内部)
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
  //停电抄表电池电压
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
  //内部电池工作时间
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
  //当前阶梯电价
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
  //事件记录
  /*
  //失压累计次数和时间
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
  //欠压累计次数和时间
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
  //过压
  //累计次数和时间
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
  //断相
  //累计次数和时间
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
  //全失压
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
  //辅助电源失电
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
  //电压逆相序
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
  //电流逆相序
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
  //电压不平衡
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
  //电流不平衡
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
  //失流
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
  //过流
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
  //断流
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
  //潮流反向
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
  //过载
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
  //电压合格率
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

  //掉电
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
  //需量超限
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
  //正向有功需量超
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
  //反向有功需量超
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
  //四象限无功需量超
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
  //操作类事件记录
  //编程
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
  //电表清0
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
  //需量清0
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
  //事件清0
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
  //校时
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
  //时段表编程
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
  //时区表编程
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
  //周休日编程
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
  //节假日编程
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
  //有功组合方式编程
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
  //无功组合方式1编程
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
  //无功组合方式2编程
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
  //结算日编程
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
  //开表盖
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
  //开端钮盒
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
  //拉闸
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
  
  //合闸
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
  //电量型购电
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
  //电量型购电块抄读
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
  
  //电费型购电
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
  //电费型购电
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
  //低功耗电池欠压
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
  
  //时钟电池欠压
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

  //负控报警
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
  
  //负控跳闸
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
  
  
  /////////////////////扩展的事件记录/////////////////////////
  //失压总次数和累计时间
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
  
  //最近一次失压发生和结束时刻
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
  
  //A、B、C三相失压总累计次数和总累计时间
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
  
  //A、B、C三相最近十次失压事件记录
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
  //A、B、C三相最近十次失压事件记录块
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
  
  //A、B、C三相欠压总累计次数和总累计时间
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
  
  //A、B、C三相欠压最近十次事件记录
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
  //A、B、C三相欠压最近十次事件记录块
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
  
  //A、B、C三相过压总累计次数和总累计时间
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
  
  //A、B、C三相过压最近十次事件记录
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
  //A、B、C三相过压最近十次事件记录块  
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
  
  //A、B、C三相断相总累计次数和总累计时间
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
  
  //A、B、C三相断相最近十次事件记录
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
  
  //电压逆相序总累计次数和时间
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
  
  //电压逆相序最近十次事件记录
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
  
   //电压逆相序最近十次事件记录块
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
  
  //电流逆相序总累计次数和时间
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
  
  //电流逆相序最近十次事件记录
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
  
  //电流逆相序最近十次事件记录块
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

  //电压不平衡总累计次数和时间
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
  
  //电压不平衡最近十次事件记录
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
  
  //电压不平衡最近十次事件记录块
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

  //电流不平衡总累计次数和时间
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
  
  //电流不平衡最近十次事件记录
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
  
  //电流不平衡最近十次事件记录块
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
  
  //A、B、C三相失流总累计次数和总累计时间
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
  
  //A、B、C三相最近十次失流事件记录
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
  //A、B、C三相最近十次失流事件记录块
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
  
  //A、B、C三相过流总累计次数和总累计时间
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
  
  //A、B、C三相最近十次过流事件记录
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
  //A、B、C三相最近十次过流事件记录块
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
  
  //A、B、C三相断流总累计次数和总累计时间
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
  
  //A、B、C三相最近十次断流事件记录
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
  //A、B、C三相最近十次断流事件记录块
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

  //A、B、C三相潮流反向总累计次数和总累计时间
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
  
  //A、B、C三相最近十次潮流反向事件记录
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
  //A、B、C三相最近十次潮流反向事件记录块
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
  
  //A、B、C三相过载总累计次数和总累计时间
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
  
  //A、B、C三相最近十次过载事件记录
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
  //A、B、C三相最近十次过载事件记录块
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
  //跳闸次数
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
  //最近10次跳闸事件记录
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
  //跳闸事件记录块
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
  //合闸次数
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
  //最近10次合闸事件记录
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
  //合闸事件记录块
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
  //总功率因素超下限总累计次数和时间
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
  //最近10次总功率因素超下限事件
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
  //总功率因素超下限事件记录块
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
  ////参变量
  //日期及星期
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
  //时间
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
  //最大需量周期和滑差时间
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
  //校表脉冲宽度
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
  //两套年时区和日时段表切换时间和两套费率切换时间
  //两套分时费率切换时间、两套阶梯切换时间
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
  //年时区数，日时段表数，日时段数，费率数
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
  //公共假日数
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
  //谐波分析次数
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
  //预付费梯度数
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
  //自动循环显示屏数
  //每屏显示时间
  //显示电能小数位数
  //显示功率(最大需量)小数位数
  //按键循环显示屏数
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
  
  //电流、电压互感器变比
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

  //通信地址
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
 //表号
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
  //资产管理编码
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
  //额定电压(AsCⅡ 码〉
  //额定电流/基本电流(AsCII码)
  //最大电流(AsCII码)
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
  //有功准确度等级(AsCII码)
  //无功准确度等级(AsCII码)
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
  //电表有功常数
  //电表无功常数
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
  //电表型号(AsCII码)
  //生产日期(AsCII码)
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
  //协议版本号
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
  //客户编号
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
  //电表运行状态字1
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
  //电表运行状态字2
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
  //电表运行状态字3
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
  //电表运行状态字4
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
  //电表运行状态字5
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
  //电表运行状态字6
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
  //电表运行状态字7
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

  //有功组合特征字
  //无功组合1特征字
  //无功组合2特征字
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

  //调制型红外光口通信速率特征字
  //接触式红外光口通信速率特征字
  //通信口1通信速率特征字
  //通信口2通信速率特征字
  //通信口3通信速率特征字
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
  //周休日特征字
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
  //周休口采用的日时段表号  
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
  //负荷记录模式字
  //冻结数据模式字
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
  //负荷记录起始时间
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
  //第1类负荷记录间隔时问
  //第2类负荷记录间隔时问
  //第3类负荷记录间隔时间
  //第4类负荷记录间隔时间
  //第5类负荷记录间隔时问
  //第6类负荷记录间隔时间
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
  //每月第1结算日
  //每月笫2结算日
  //每月第3结算日
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
  //0级密码
  //...
  //9级密码
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

  //A相电导系数
  //A相电纳系数
  //A相电阻系数
  //A相电抗系数
  //B相电导系数
  //B相电纳系数
  //B相电阻系数
  //B相电抗系数
  //C相电导系数
  //C相电纳系数
  //C相电阻系数
  //c相电抗系数
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
  
  //正向有功功率上限值
  //反向有功功率上限值
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
  //电压上限值
  //电压下限值
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

  //电量型预付费限值
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

  //电费型预付费限值
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

  //电费运行状态字
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
 
  //整点冻结开始时间
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
  
  //整点冻结间隔时间
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
 
  //日冻结时间
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
 
  //跳闸延时
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
  //功率负荷脉冲数
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
  
  //最大负荷计算时间，过负荷跳闸次数门限
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
 //显示电费小数位数
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
  
 //预付费模式字
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
  //系统序列号、用户号、表号
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
  //超负荷跳闸次数
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
  
  //第一套时区表数据
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
  //第一套第1日时段表数据:
  //...
  //第一套第14日时段表数据:
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

  //第二套时区表数据
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
  //第二套第1日时段表数据:
  //...
  //第二套第14日时段表数据:
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

  //公共假日
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
  //自动循环显示第1屏显示数据项
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
  //按键循环显示第1屏显示数据项
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
  //第一套分时费率参数
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
  //第二套分时费率参数
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
  //第一套阶梯电能
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
  //第一套阶梯电价
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
  
  //第二套阶梯电能
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
  //第二套阶梯电价
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
  
  //失压事件电压触发上、下限
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
 
 //失压事件电流触发下限
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
 
 //失压事件判定延时间
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
 
 //失压事件判定延时间
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

 //欠压事件电压触发上限
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
  
 //欠压事件判定延时时间
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


 //过压事件电压触发上限
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
  
 //过压事件判定延时时间
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
 
 //断相事件电压触发上限
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
 
 //断相事件电流触发上限
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

 //断相事件电流触发上限
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
  
 //断相事件判定延时时间
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
  
 //电压不平衡限值
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

 //电压不平衡率判定延时时间
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
  
 //电流不平衡限值
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

 //电流不平衡率判定延时时间
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
  
 //失流事件电压触发下限
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

 //失流事件电流触发上、下限
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

 //失流事件判定延时时间
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

 //过流事件电流触发下限
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

 //过流事件判定延时时间
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
 
 //断流事件电压触发下限
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

 //断流事件电流触发上限
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
 
 //断流事件判定延时时间
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
  
 //潮流反向事件判定延时时间
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

 //潮流反向事件判定延时时间
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

 //过载事件有功功率触发下限
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

 //过载事件判定延时时间
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

 //电压考核上、下限
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
 
 //有、无功需量超限事件需量触发下限
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
 
 //需量超限时间时间判定延迟
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

 //总功率因素超下限阀值
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

 //总功率因素超下限判定延时时间
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
  
 //电流严重不平衡限值
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

 //电流严重不平衡判定延时时间
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
  
  //厂家软件版本号(AsCⅡ 码)
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
  //厂家硬件版本号(AsCII码)
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
  //厂家编号(AsCII码)  
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
  //定时冻结,定时冻结数据的处理和分次事件的处理一致
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
  
  //瞬时冻结,瞬时冻结数据的处理和分次事件的处理一致
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
  
  //年时区方案切换冻结,年时区切换冻结的处理和分次事件的处理一致
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

  //日时段方案切换冻结,冻结数据的处理和分次事件的处理一致
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

  //两套阶梯方案切换冻结
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
  
  //两套分时费率方案切换冻结
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
  
//日冻结
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
  
  //小时或者半时冻结
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

  //电量翻转冻结
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
  
  //负荷记录读取
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

  /////////扩充//////////////////////////////////////  
  //电量结算时间
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

  //需量结算时间
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
  //模式字1-3
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

  //模式字4-5
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
  //电压考核上限、下限
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

  //失压启动电压、电流
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
 
   //失压判断时间
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

   //失流启动电流、结束电流
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
 
  //失流判断时间、临界电压
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
  //失流判断时间、临界电压
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
//断相启动电流
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
 
//断相判断时间
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

//过压判断阀值
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
 
//用户级别、跳闸延时、合闸延时
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

//电流不平衡上限
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
 
 //电压不平衡上限
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

 //失压启动电压
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

 //失压启动电流
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

 //失压判断阀值
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

 //过流判断阀值
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

 //密码正确开放写时间
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
  
 //密码错误闭锁次数上限
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
 //密码错误闭锁时间
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
 //密码错误解锁剩余次数
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
  
 //密码错误解锁剩余时间
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
 //编程时间
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
 //三合一输出状态
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
  
 //周期冻结时间
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
  
  //每日广播校时次数
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
  
  //设置初始电量
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

  //设置预付费电量、电费
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
 
  //插卡标志，预付费测试用
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
  
   //当前年时区方案等信息
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

  //当前正向有功需量
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
  //当前反向有功需量
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
  //当前组合无功1需量
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
  //当前组合无功2需量
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
  //当前一象限无功需量
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
  //当前二象限无功需量
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
  //当前三象限无功需量
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
  //当前四象限无功需量
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
  
  //当前费率电价
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
  //当前阶梯电量
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
  //当前阶梯电价
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
//----扩展事件记录-------------
  //复位
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

  //运行时钟乱
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
  
  //上电时钟乱
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
  //远程拉闸事件记录
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

  //远程合闸事件记录
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
  //设初始电量事件
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
  
  //扩展的事件累加数据，包括失压、失流、断相、反向
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
  
 //远程通信状态
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
  
 //模块打开电表写使能
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

  //A相电压 1位小数
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
  //B相电压
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
  //C相电压
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
  
  //A相电流 4位小数
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
  //B相电流
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
  //C相电流
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
  
  //A相相角
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
  //B相相角
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
  //C相相角
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
  
  //总相角
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

  //校时前时间
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
  //校时后时间
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
  //当前无功象限
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
  
  //当前时间，带秒
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

  //掉电时间,秒、分、时、日、月、年
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
  
  //上电时间,秒、分、时、日、月、年
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
  
  //当前时间,不带秒  
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
 
   //编程时间
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
  //总AH
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
  
  //A相安时
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
  //B相安时
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
  //C相安时
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
  //全失压发生时电流
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
  //最大电压不平衡率
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
  //最大电流不平衡率
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
  #define _PDI_POS_ACTIVE_DEMAND_TIME  0x80000005 //需量超限期间最大有功需量及时间
  #define _PDI_NEG_ACTIVE_DEMAND_TIME  0x80000006
  #define _PDI_QUAD1_REACT_DEMAND_TIME 0x80000007
  #define _PDI_QUAD2_REACT_DEMAND_TIME 0x80000008
  #define _PDI_QUAD3_REACT_DEMAND_TIME 0x80000009
  #define _PDI_QUAD4_REACT_DEMAND_TIME 0x8000000A
  */
  //正向有功超限最大需量
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
  //反向有功超限最大需量
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
  //一象限无功超限最大需量
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
  //二象限无功超限最大需量
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
  //三象限无功超限最大需量
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
  //四象限无功超限最大需量
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
  //正向有功超限最大需量发生时间
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
  //反向有功超限最大需量发生时间
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
  //一象限无功需量超限时间
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
  //二象限无功需量超限时间
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
  //三象限无功需量超限时间
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
  //四象限无功需量超限时间
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
  //操作者代码
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
  //一次编程记录的操作者代码
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
  //编程记录DI
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
  //事件清0数据标识
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
 
  //全失压开始时间
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

  //全失压结束时间
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

  //RTC错误时间
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

  //购电量总次数
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
  //累计购电量
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
  //当次购电电量
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
  //当次购电前总电量
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
  
  //购电费总次数
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
  //累计购电金额
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
  //当次购电金额
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


  
  //当次购电前总金额
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
  
//----校表状态------
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
  //---校表参数-----
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
  
  //---校表清零----
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
  
  //---读取内卡数据
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

  //---校表瞬时数据打大包
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

//----无用的标识字------
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

//检查协议数据的存储，Protocol_Data中S_ROM属性的数据应该在存储中都有数据
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

//读取数据传输相关参数
void Read_Data_Trans_Para_From_Rom()
{
  INT8U i;
  
  TRACE();
  
  if(Read_Storage_Data(SDI_COMM_ADDR, (void *)Meter_Addr.Addr[0], (void *)Meter_Addr.Addr[0], sizeof(Meter_Addr.Addr[0])) EQ 0)
  {
     mem_set((void *)Meter_Addr.Addr[0], 0, sizeof(Meter_Addr.Addr[0]), (void *)Meter_Addr.Addr[0], sizeof(Meter_Addr.Addr[0]));  
  }
  
  Meter_Addr_Ready_Flag.Var = DATA_READY; //表地址准备好了
  INIT_STRUCT_VAR(Meter_Addr_Ready_Flag);
  
  SET_STRUCT_SUM(Meter_Addr);
  
  for(i = 0; i < 10; i ++)//读取10级密码
  {
    Read_Storage_Data(SDI_PSW0 + i, (INT8U *)Cur_PSW.PSW[i], (INT8U *)Cur_PSW.PSW, sizeof(Cur_PSW.PSW)); 
    
  }
  
  SET_STRUCT_SUM(Cur_PSW);
}

//初始化数据传输相关的内存变量
void Init_Data_Trans_Ram_Para()
{
  TRACE();

  //参数修改缓冲区
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
数原型：
void Set_Para_Modify(PROTO_DI PDI)
  数功能：
  某参数被设置时调用该函数
入口参数：PDI, 参数的标示码
 隹诓问何?
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

    Para_Modify.Posi[i] ++ ; //第0个字节记录当前修改参数标示码的存放位置
    if(Para_Modify.Posi[i] >= CHK_PARA_NUM)
      Para_Modify.Posi[i] = 0; 

    Posi = Para_Modify.Posi[i]; 
    if(0 != Para_Modify.Buf[i][Posi])//判断已经修改了的参数是否被读出去了?
    {
      // Debug_Print("Waitfor Set_Para_Modify  % s Task ara_Modify.Buf[%d][%d] EQ %d", \
      // Tcb[i].Name, i, Posi, Para_Modify.Buf[i][Posi]); 
      SET_STRUCT_SUM(Para_Modify); 
      OS_Waitfor_Sec(0 EQ Para_Modify.Buf[i][Posi], 5); //等待5S该位置变为0

      if(0 != Para_Modify.Buf[i][Posi])
        Debug_Print("Para_Modify.Buf[%d][%d] EQ %d error", i, Posi, Para_Modify.Buf[i][Posi]);
    }
    Para_Modify.Buf[i][Posi] = PDI;
  }
  SET_STRUCT_SUM(Para_Modify); 
}

//清编程的内存记录
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
//编程记录的10分钟计数
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

//编程记录的10分钟计数
void Prog_Timer_Proc()
{
  INT8U Status;
  static S_Int8U Sec_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Counts = {CHK_BYTE, 0, CHK_BYTE};
  
  if(Check_Meter_Prog_Status() || Check_Meter_Factory_Status()) //处于编程状态
    Status = 1;
  else
    Status = 0;
  
  if(PREPAID_EN > 0)
  {
    if(Check_Remote_Prog_Status())
      Status = 1;
  }
  
  if(Status != Prog_Record.Prog_Status) //编程状态发生了变化
  {
    DIS_PD_INT;
    
    Prog_Record.Prog_Status = Status;
    if(Status EQ 0 && Prog_Record.Prog_Flag.All_Flag > 0) //由编程状态进入非编程状态，且发生过编程则记一次编程记录
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

//检查是否校表参数,是返回1，否则返回0
INT8U Check_Adj_Meter_Para(PROTO_DI PDI)
{
  if(PDI >= _SDI_ADJ_METER_PARA_STATUS && PDI <= _SDI_RD_ROM)
    return 1;
  else
    return 0;
  
}

//检查PDI标识是否需要编程记录，1表示需要，0表示不需要
INT8U Check_PDI_Set_Prog_Record(PROTO_DI PDI)
{
  if(Check_Adj_Meter_Para(PDI))//校表不需要记录编程事项
    return 0;
  return 1;
}

//编程记录预处理，在设参数前处理
//因为有些操作涉及到事件处理，时间太长，必须先发应答再处理事件
//pAck_Flag为1表示已经给过应答，0表示没有
void Set_Prog_Record_Pre_Porc(INT8U Ch, PROTO_DI PDI, INT8U *pAck_Flag)
{
  INT8U Event_ID;
  
  *pAck_Flag = 0;
  
  DIS_PD_INT;
 ///////////////////////////////////////////////////////////////
#if DATE_TABLE_PROG_NUM >0 //日时段表编程
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
    
#if YEAR_TABLE_PROG_NUM >0  //时区表编程
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
    
#if WEEK_REST_PROG_NUM >0  //周休日编程
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
    
#if HOLIDAY_PROG_NUM >0  //节假日编程
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
    
#if ACTIVE_COMB_PROG_NUM >0  //有功组合编程
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
#if REACTIVE_COMB_PROG_NUM > 0  //无功组合编程
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
    
#if SETTLE_TIME_PROG_NUM > 0  //结算日编程   
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

//设置编程记录
void Set_Prog_Record(PROTO_DI PDI, INT8U Op_ID[])
{
    INT8U i;
    INT8U Re;
    INT8U Num;
    
    TRACE();
    
    if(Check_PDI_Set_Prog_Record(PDI) EQ 0)//0表示不需要记录编程
      return;
	
    Re = CHECK_STRUCT_SUM(Prog_Record);
    if(1 != Re)//ASSERT(1 EQ Re))
    {
      ASSERT_FAILED();
      Clr_Prog_Record_Ram();
    }

    //一个新的操作员,并且前一个操作员有过操作,则将之前的老操作员的操作置结束
    if((Prog_Record.Prog_Flag.All_Flag != 0 && memcmp((INT8U *)Operator_ID.Op_ID, (INT8U *)Prog_Record.Op_ID, 4) !=0))
    {
      Event_Data_Proc(ID_EVENT_PROG, EVENT_OCCUR);  
    }
    
    DIS_PD_INT;   
    
    if((Prog_Record.Prog_Flag.All_Flag != 0 && memcmp((INT8U *)Op_ID, (INT8U *)Prog_Record.Op_ID, 4) !=0))
    {    
      //重新开始新的一轮编程
      Prog_Record.Prog_Flag.All_Flag = 0;
      //清除编程的标识
      mem_set((void *)&Prog_Record.PDI, 0xFF, sizeof(Prog_Record.PDI), (void *)&Prog_Record.PDI, sizeof(Prog_Record.PDI));
    }

  
    //以前的标识顺序往后移
    Num = S_NUM(Prog_Record.PDI);
    for(i = 1; i < Num; i ++)
    {
      Prog_Record.PDI[Num - i] = Prog_Record.PDI[Num - i -1]; 
    }

    Prog_Record.PDI[0] = PDI;
    
    if(Prog_Record.Prog_Flag.All_Flag EQ 0)//第一条编程记录,记录下初次编程时间
    {
      mem_cpy((INT8U *)Prog_Record.Op_ID, (INT8U *)(INT8U *)Op_ID, sizeof(Op_ID),\
              (INT8U *)Prog_Record.Op_ID, sizeof(Prog_Record.Op_ID));
      //mem_cpy((INT8U *)Prog_Record.Time, (INT8U *)Cur_Time2.Time, sizeof(Cur_Time2.Time), (INT8U *)Prog_Record.Time, sizeof(Prog_Record.Time));
    }
    //最后一条的时间作为编程开始时间--实际是编程结束时间
    mem_cpy((INT8U *)Prog_Record.Time, (INT8U *)Cur_Time2.Time, sizeof(Cur_Time2.Time), (INT8U *)Prog_Record.Time, sizeof(Prog_Record.Time));
    
    Prog_Record.Prog_Flag.All_Flag = 1;
    
    SET_STRUCT_SUM(Prog_Record);
    SET_STRUCT_SUM(Event_Data);

    EN_PD_INT;
}

/*
//对于编程记录的时间处理
void Prog_Record_Time_Proc()
{
  static S_Int32U Sec = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int32U Prog_Ram_Posi = {CHK_BYTE, 0, CHK_BYTE};
  
  if(Sec.Var != Sec_Timer_Pub || Prog_Ram_Posi.Var != Prog_Record.Posi)
  {
    //if(Prog_Record.Posi >= 10)
      ///Event_Data_Proc();//编程记录
    
    
  
    //if
  }
  
}
*/
//获取修改的参数标识
//返回1表示有参数发生修改,*pDI指向修改参数的标识
//返回0表示没有参数发生修改
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

  Posi = Para_Modify.Posi[Cur_Task_ID]; //该任务的修改参数存储位置
  if(Posi >= CHK_PARA_NUM)
  {
    ASSERT_FAILED();
    Posi = 0;
  }

  Count = 0; //查询次数计数，每次最多查询CHK_PARA_NUM个参数 
  i = (Posi + 1) % CHK_PARA_NUM; //从Posi + 1开始查询到Posi
  while(Count <= CHK_PARA_NUM)
  {
    if(Para_Modify.Buf[Cur_Task_ID][i] != 0)// !=  0表示该参数还未读出
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
  return 0; //没有找到则返回0 
}

//获取某个DI参数的存储属性, 返回S_ROM或者S_RAM
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

//获取某个DI数据源数据的类型
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

//获取协议数据的密码等级
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

//DI是否是一个块DI?
//不是则返回0,是则返回>0的数据,数值表示第N个8位是0xFF位
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


//检查P_Data_Info[Index]描述的数据项,是否属于数据块DI中的一员
//Index表示P_Data_Info中的一个索引
//DI表示协议DI,是一个Block类型的DI
//Data_Flag无用
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

  if(i EQ 4) //4字节均满足要求
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//检查某个PDI是否应该返回应答，
//在远程预付费的情况下，本地电费等信息不应答，不显示
INT8U Check_PDI_Answer_En(PROTO_DI PDI)
{
  if(PREPAID_EN EQ 0 || PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //预付费功能没有打开或者和远程预付费表，电费信息不现实
  {
    if((PDI & 0xFFFFFF00) EQ 0x04000F00 && (PDI & 0x000000FF) <= 0x00000004) //报警电量相关信息
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x04001000 && (PDI & 0x000000FF) <= 0x00000005) //报警电费相关信息
      return 0;
    
    if(PDI EQ 0x04000108)
      return 0;
    
    if(PDI EQ 0x0280000B) //当前阶梯电价
      return 0;
    
    if((PDI & 0xFFFF0000) EQ 0x04060000 && (PDI & 0x0000FF00) <= 0x00000300) //阶梯电价相关参数
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x04050100 || (PDI & 0xFFFFFF00) EQ 0x04050200) //分时电价
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x00900100) //剩余电量、透支电量
      return 0;
    
    if((PDI & 0xFFFFFF00) EQ 0x00900200) //剩余金额、透支金额
      return 0;
  }
  
  return 1;
}


//读取某条独立的数据项
//Index表示DI标示符在P_Data_Info中的索引
//pPara表示输入参数
//pDst表示目标缓冲区起始地址
//pDst_Start和DstLen一起限定pDst和返回数据长度 
//Data_Flag, FOR_COMM表示数据提供给通信, FOR_DISP表示数据提供给显示
//pErr, 错误状态返回字
//读取成功的条件:返回长度>0，且1 EQ *pErr
INT16U Get_DLT645_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len; 
  INT8U Re,Spec_Flag;
  
  if(Check_PDI_Answer_En(PDI) EQ 0) //该数据项不予应答
    return 0;
  
  //找到该数据项所在的P_Data_Info中的索引
  //必须是P_Data_Info中的某项DI或者其对应的DI_Equ
  Re = Check_P_Data_Single(Index, PDI, Data_Flag, &Spec_Flag);
  if(Re EQ 0)
  {
    return 0;
  }

  if(pDst + P_Data_Info[Index].Dst_Len > pDst_Start + DstLen)//数据是否会溢出?
  {
    ASSERT_FAILED();  
    return 0;
  }
  
  if((Spec_Flag & 0x40) != 0)//是特殊项且是读特殊项
  {
    //注意：Get_DLT645_Spec_Single_Data函数内部会再调用_Get_DLT645_Data函数
    //因此此函数内部可能会申请信号量SEM_PUB_BUF0
    Len = Get_DLT645_Spec_Single_Data(PDI, Spec_Flag, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag); //先当作特殊数据项读取
  }
  else
  {
    Len = Get_DLT645_Normal_Single_Data(Index, PDI, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag);  
  }
  
  return Len;
}

//10的a次方
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

//检查一个DI是否是冻结数据DI
INT8U Check_Freeze_Data_PDI(PROTO_DI PDI)
{
  if((PDI & 0xFF000000) EQ 0x05000000)
    return 1;
  else
    return 0;
}
//#pragma optimize =s high 
//判断是否可以从P_Data_Info[Index]获得DI数据
//DI为非数据集和数据块的数据
//*pSec_Flag用于返回该项数据的特殊标志
//返回1表示是P_Data_Info中的数据项.DI数据项，2表示是.DI_EQU类型的数据项, 0表示在P_Data_Info中没有这个数据项
INT8U Check_P_Data_Single(INT16U Index, PROTO_DI PDI, INT8U Data_Flag, INT8U* pSpec_Flag)
{
  PROTO_DI Num; 
  //PROTO_DI TempDI;
  INT16U i; 
  INT8U* pDI, * p;
  INT8U* pNum;

  //TRACE();//此处打开轨迹跟踪会导致时间很长，干掉之

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

    //电量或需量数据因为和费率相关，需要特殊处理
    if(SPEC_ENERGY EQ P_Data_Info[Index].Spec_Flag || \
       SPEC_DEMAND EQ P_Data_Info[Index].Spec_Flag)//费率相关的特殊项，例如分费率电能等
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

//获取某个DI的在P_Data_Info中的Index
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

//寻找协议帧，在某个pSrc开始的buf中
//寻找一条645帧
//pSrc，搜索的缓冲区起始位置
//SrcLen,缓冲区长度
//pOffset,找到的帧的起始偏移，相对于SrcLen
//返回值:找到的帧长
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
      Len=*(pSrc+i+9);//数据域长度
      Len+=12;//加上帧头尾
      if((i+Len)<=SrcLen && Check_Frame_Format(pSrc+i,Len) EQ 1)//帧格式正确
      {
        *pOffset=i;
        return Len;       
      }
    }
  }
  return 0;
}

//寻找协议帧，在某个pSrc开始的buf中
//寻找一条645帧
//pSrc，搜索的缓冲区起始位置
//SrcLen,缓冲区长度
//pOffset,找到的帧的起始偏移，相对于SrcLen
//返回值:找到的帧长
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
      Len=*(pSrc+i+9);//数据域长度
      Len+=12;//加上帧头尾
      *pOffset = i;
      if(0x16 EQ *(pSrc+i+Len-1))//判断帧头和帧尾
      return Len;
    }
  }
  return 0;
}

//解析获取地址的帧
//pSrc为源帧，SrcLen为帧长
//pDst为目标缓冲区
//返回为应答帧长>0表示收到一条正确的读地址帧
//该函数主要用于在波表
INT8U Phase_Get_Addr_Frame(INT8U *pSrc, INT16U SrcLen)
{
  INT16U Len;
  INT8U *pDst;
  
  if(Get_Main_Init_Flag() !=  MAIN_INITING || Meter_Addr_Ready_Flag.Var != DATA_READY) //初始化状态才调回该函数
    return 0;
  
  if(*(pSrc + 8) != 0x13 || Check_Frame_Format(pSrc, SrcLen) EQ 0)  
   return 0;
  
  Len = 0;
  pDst = (INT8U *)Temp_Buf_PUCK;
  if(memcmp(pSrc + 1, (INT8U *)BROAD_ADDR_AA, 6) EQ 0) //控制码是0x13，而且地址是全0xAA
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

//在缓冲区中找645帧,并处理之，生成应答帧
//Ch,表示数据来源通道
//pSrc,源缓冲区
//SrcLen,源缓冲区长度
//pDst,目标缓冲区长度
//pDst_Start,和DstLen一起限定应答帧长度
//返回长度,0标识没有应答帧，>0有应答帧，且为帧长
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

//Index表示DI标示符在P_Data_Info中的索引
//pPara表示输入参数
//pDst表示目标缓冲区起始地址
//pDst_Start和DstLen一起限定pDst和返回数据长度 
//Data_Flag, FOR_COMM表示数据提供给通信, FOR_DISP表示数据提供给显示
//pErr, 错误状态返回字
//读取成功的条件:返回长度>0，且1 EQ *pErr
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

  //取出源数据
  if(!(Index < S_NUM(P_Data_Info)))
  {
    ASSERT_FAILED();
    return 0;
  }

  //非特殊数据项，如下处理:
  if(S_RAM EQ P_Data_Info[Index].Storage)//数据存储在RAM中
  {
    pSrc = (INT8U *) (P_Data_Info[Index].pSrc);// + P_Data_Info[Index].Src_Off; 
    pSrc += (PDI - P_Data_Info[Index].PDI) * P_Data_Info[Index].Src_Len;
  }
  else if(S_ROM EQ P_Data_Info[Index].Storage)//数据存储在EEROM或者Flash中
  {
    Len = 0; 
    //从EEROM或者Flash中读取数据，偏移已经在存储中形成，因此不需要psrc赋值时取偏移
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

  //进行数据转换
  if(S_INTU EQ P_Data_Info[Index].Src_Format)//源数据的类型是无符号整形
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

    Len = P_Data_Info[Index].Dst_Len; //转换出来的BCD数据的长度

    if((Data_Flag & FOR_SRC) EQ 0)
    {
      U_Data = U_Data / Pow_10x(P_Data_Info[Index].Dst_Start); //源数据/Dst_Start表示需要的目标数据
      //功率的显示，小数位数
      if((Data_Flag & FOR_DISP) EQ FOR_DISP)
      {
        if((PDI & 0xFFFF0000) EQ 0x02030000 || (PDI & 0xFFFF0000) EQ 0x02040000 || (PDI & 0xFFFF0000) EQ 0x02050000)
        {
          if(DemandDisBit <= 4) //功率显示小数位数
            U_Data = U_Data / Pow_10x(4 - DemandDisBit);
        }
      }
      
      Hex2Bcd(U_Data, (INT8U *) Pub_Buf, Len, (void *) Pub_Buf, sizeof(Pub_Buf)); //转换出BCD数
    }
    else
    {
      //if(!(P_Data_Info[Index].Dst_Len EQ 4 && P_Data_Info[Index].Dst_Len EQ P_Data_Info[Index].Src_Len))
        //ASSERT_FAILED();
      
      mem_cpy((INT8U *) Pub_Buf, &U_Data, Len, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    }
    mem_cpy(pDst, (INT8U *) Pub_Buf, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); //提取数据复制到目标缓冲区
    return P_Data_Info[Index].Dst_Len;
  }
  else if(S_BCD EQ P_Data_Info[Index].Src_Format || S_BIN EQ P_Data_Info[Index].Src_Format)//源数据类型是BCD类型，表示无需进行格式转换
  {
    mem_cpy(pDst, pSrc + P_Data_Info[Index].Dst_Start, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); //复制到目标缓冲区  
    return P_Data_Info[Index].Dst_Len;
  }
  else if(S_INTS EQ P_Data_Info[Index].Src_Format)//源数据类型是有符号整型
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

    Len = P_Data_Info[Index].Dst_Len; //转换出来的BCD数据的长度

    if((Data_Flag & FOR_SRC) EQ 0)
    {
      S_Data = S_Data / (INT32S)Pow_10x(P_Data_Info[Index].Dst_Start); //源数据/Dst_Start表示需要的目标数据
      S_Hex2Bcd(S_Data, (INT8U *) Pub_Buf, Len, (void *) Pub_Buf, sizeof(Pub_Buf)); //转换出BCD数
    }
    else
    {
      ASSERT(P_Data_Info[Index].Dst_Len EQ 4 && P_Data_Info[Index].Dst_Len EQ P_Data_Info[Index].Src_Len);
      mem_cpy((INT8U *) Pub_Buf, &S_Data, Len, (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    }

    mem_cpy(pDst, (INT8U *) Pub_Buf, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); //提取数据复制到目标缓冲区
    return P_Data_Info[Index].Dst_Len; 
    //目前无该类型 
  }

  ASSERT_FAILED(); 
  return 0;
}

//Index表示DI标示符在P_Data_Info中的索引
//pPara表示输入参数
//pDst表示目标缓冲区起始地址
//pDst_Start和DstLen一起限定pDst和返回数据长度 
//Data_Flag, FOR_COMM表示数据提供给通信, FOR_DISP表示数据提供给显示
//pErr, 错误状态返回字
//读取成功的条件:返回长度>0，且1 EQ *pErr
INT16U Get_DLT645_Normal_Single_Data(INT16U Index, PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag)
{
  INT16U Len;
  
  OS_Mutex_Pend(PUB_BUF_SEM_ID);
  Len = _Get_DLT645_Normal_Single_Data(Index, PDI, pPara, ParaLen, pDst, pDst_Start, DstLen, Data_Flag);
  OS_Mutex_Post(PUB_BUF_SEM_ID);
  
  return Len;
}

//读一个数据块的数据, 例如0x901F之类, 但不能是0x90FF之类的，必须且只能DI[0]L = 0F
//DI表示数据标识符, 必须满足DI[0]L = 0F; 
//pDst表示目标数据缓冲区
//pDst_Start和DstLen一起界定目标数据长度
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
  
  //读后续数据时如果没有后续数据，按照正常数据读取
  if((Frame_Ack_Info.Follow_Flag EQ 0) && (Frame_Ack_Info.Read_Follow_Flag EQ 1))
    Frame_Ack_Info.Read_Follow_Flag = 0;
  
  if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//读后续数据
    i = Bak_i.Var;
  else
    i = 0;
      
  for(; i < S_NUM(P_Data_Info); i ++)
  {
    Re = Check_P_Data_In_Block(i, PDI); 
    if(0 < Re)
    {
      Num = (INT8U) (((P_Data_Info[i].Num >> ((j - 1) * 8))) & 0x000000FF);

      //标识的第二个字节是0xFF，且是需量或者电量相关数据
      if((j EQ 2) && (P_Data_Info[i].Spec_Flag EQ SPEC_ENERGY || P_Data_Info[i].Spec_Flag EQ SPEC_DEMAND))
      {
        if((Data_Flag & FOR_EVENT) EQ FOR_EVENT) //事件应该取所有费率数据
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

      if(Num EQ 0) //0代表起码有一项
        Num = 1;
      
      TempDI = PDI & (~((INT32U)0xFF << ((j - 1) * 8)));
      TempDI = TempDI | (P_Data_Info[i].PDI & ((INT32U)0xFF << ((j - 1) * 8)));
      
      if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//读后续数据
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
        //如果是块抄冻结数据，还需要加块分隔符
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
  
  if(i != S_NUM(P_Data_Info))//有后续数据,跳出了循环导致 i != SUM(P_Data_Info)
  {
    Bak_i.Var = i; //保留大循环起始
    Bak_k.Var = k; //保留小循环起始
    Frame_Ack_Info.Follow_Flag = 1; //有后续数据
  }
  else
  {
    Bak_i.Var = 0; //保留大循环起始
    Bak_k.Var = 0; //保留小循环起始
    Frame_Ack_Info.Follow_Flag = 0; //无后续数据    
  }

  return Len;
}



//INT16U Get_Protocol_Single_Data_Index
//读取645数据
//DI, 645协议标识
//pPara, 入口参数, 接收帧的数据域
//pDst, 目标数据缓冲区
//pDst_Start和DstLen一起限定pDst和读回数据长度的范围
//DataFlag, FOR_DISP表示读取的数据是给显示用，FOR_DISP表示做显示用
//返回时读取到的数据长度
INT16U _Get_DLT645_Data(PROTO_DI PDI, void* pPara, INT8U ParaLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U Data_Flag, INT8U* pType)
{
  INT16U Len, Index;

  TRACE();

  *pType = S_BCD;//默认数据类型
  
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

//获取645数据的简单函数
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

//获取645数据的简单函数, 专提供给现实任务调用
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

//获取工厂信息
INT16U Get_Factory_Info_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i;
  INT8U Temp[10];
  
   if(PDI EQ 0x04800001) //软件版本号
   {
     if(PREPAID_METER > 0) //费控表
     {
       Temp[0] = 'P'; //费控表
       
       if(PREPAID_MODE EQ PREPAID_MONEY)
         Temp[1] = 'M'; //电费型
       else
         Temp[1] = 'E'; //电量型
       
       if(PREPAID_MONEY_MODE EQ PREPAID_RATE)
         Temp[2] = 'T'; //复费率型
       else
         Temp[2] = 'S'; //阶梯型
       
       i = 3;
     }
     else
     {
       Temp[0] = 'M'; //多功能表      
       i = 1;
     }
     
     if(NET_METER EQ CARRIER_METER) //载波表
       Temp[i] = 'C';
     else if(NET_METER EQ GPRS_METER) //无线表
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
   else if(PDI EQ 0x0400040D)//协议版本号
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

//获取通信模块状态
INT16U Get_Module_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  if(PDI EQ 0x0EA20000)
  {
    *pDst = Module_Comm_Status.Var;
    return 1;
  }
  
  return 0;
}

//读取ROM中的数据
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
    if(*(INT8U *)pPara EQ 0)//MEM_ID EQ 0表示读取内存数据
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
//读取特殊数据项
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

//转换源数据到协议数据
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
    Index = Get_P_Data_Index(PDI[i]);//通过Index0获取源数据格式

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
//协议数据的加减
//DI数据对应的标识码数组
//DI_Num标识码个数
//pData0,通过Get_DLT645_Data 获得的数据，FOR_SRC标志
//pData1,,通过Get_DLT645_Data 获得的数据，FOR_SRC标志
//BCD数据,要计算的就是pData0-pData1
//pDst,目标缓冲区,pDst_Start和DstLen一起限定返回长度
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
    Index = Get_P_Data_Index(PDI[i]);//通过Index0获取源数据格式

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
        U32_Data0 = U32_Data0 / Pow_10x(P_Data_Info[Index].Dst_Start);//计算差
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
          S16_Data0 = S16_Data0 / (INT16S)Pow_10x(P_Data_Info[Index].Dst_Start);//计算差    
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
          S32_Data0 = S32_Data0 / (INT32S)Pow_10x(P_Data_Info[Index].Dst_Start);//计算差
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

//检查是否需要清除数据
//返回值:
//CLEAR_END_FLAG，没有数据需要清除
//CLEAR_ENERGY_FLAG,需要清除电量
//CLEAR_DEMAND_FLAG,需要清除需量
//CLEAR_VOSTAT_FLAG,需要清楚电压统计
//CLEAR_EVENT_FLAG,需要清楚电压统计
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

//检查645帧格式, pFrame表示帧起始地址, FrameLen表示帧的长度
INT8U Check_Frame_Format(INT8U* pFrame, INT8U FrameLen)
{
  INT8U Sum; 

  TRACE();

  if(!(0x68 EQ * pFrame && 0x68 EQ * (pFrame + 7) && 0x16 EQ * (pFrame + FrameLen - 1)))//判断帧头和帧尾
  {
    return 0;
  } 

  Sum = 0;
  Get_Buf_MulitByte_Sum(pFrame, FrameLen - 2, 1, &Sum, 1); //判断校验和
  if(!(Sum EQ * (pFrame + FrameLen - 2)))
  {
    return 0;
  }  

  return 1;
}

//检查645帧中的表地址是否正确?
//Ch是帧的来源通道
//Addr是帧中的表地址
//Ctrl_Code是帧中的控制码
//*pAck_Flag表示是否需要应答
INT8U Check_Frame_Meter_Addr(INT8U Ch, INT8U Addr[], INT8U Ctrl_Code,INT8U *pAck_Flag)
{
  INT8U i; 

  TRACE();

  *pAck_Flag = 1;//一般情况下需要应答
  
  if(memcmp(Addr, (void *) Meter_Addr.Addr[0], 6) EQ 0)//地址正确
  {
    if(C_ADJUST_TIME != Ctrl_Code) //广播校时不能用本身地址 
      return 1;
    else
      return 0;
  } 

  //帧中的表地址和Meter_Addr参数中的表地址不一致
  //先判断是否是广播地址
  if(memcmp(Addr, BROAD_ADDR_99, 6) EQ 0)
  {
    //广播地址99具备的权限：广播校时、广播冻结、设置多功能端子
    //广播校时和广播冻结不需要应答
    if(C_FREEZE_DATA EQ Ctrl_Code ||\
       C_ADJUST_TIME EQ Ctrl_Code ||\
       C_PORT EQ Ctrl_Code)
    {
      //if(C_FREEZE_DATA EQ Ctrl_Code || C_ADJUST_TIME EQ Ctrl_Code)
      *pAck_Flag = 0;//广播冻结和广播校时不需要应答
      return 1;
    }
    else
      return 0;
  }
  else if(memcmp(Addr, (void *) BROAD_ADDR_AA, 6) EQ 0)//全AA地址, 只能具备读权限
  {
    //地址AA具备的权限：读数据或者读通信地址、写通信地址
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
      if(Check_Meter_Factory_Status()) //工厂状态允许用AA地址设参数和清零
        return 1;
    }

    return 0;
  }
  else //是否带通配符地址,只有读数据的权限
  {
    //高位为0xAA, 低位为表地址，同样可以设置表参数等，低地址至少要有1字节匹配
    for(i = 0; i < 6; i ++)
    {
      if(Addr[5 - i] != 0xAA) //i为AA个数
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

//数据打包
//Ch表示通道号
//Ctrl_Code控制码
//pSrc需要打包的数据域
//SrcLen数据域长度
//pDst目标缓冲区
//pDst_Start和DstLen一起限定pDst和帧长
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
  //if(CH_RS485_1 EQ Ch || CH_IRAD EQ Ch)//根据不同通道填充不同的表地址
  mem_cpy(pDst + 1, (void *) Meter_Addr.Addr[0], 6, pDst_Start, DstLen);
  //else
  //mem_cpy(pDst+1,(void *)Meter_Addr.Addr[1],6,pDst_Start,DstLen);

  *(pDst + 7) = 0x68;
  *(pDst + 8) = Ctrl_Code;//控制码
  *(pDst + 9) = (INT8U) SrcLen;
  mem_cpy(pDst + 10, pSrc, SrcLen, pDst_Start, DstLen);

  for(i = 0; i < SrcLen; i ++)//数据域+0x33
  {
    *(pDst + 10 + i) += 0x33;
  }
  Get_Buf_MulitByte_Sum(pDst, SrcLen + 10, 1, pDst + 10 + SrcLen, 1);
  *(pDst + SrcLen + 11) = 0x16;
  return SrcLen + 12;
}

/*
错误信息字ERR
Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
保留	费率数超	日时段数超	年时区数超	通信速率不能更改	密码错/未授权	无请求数据	其他错误
注：	0代表无相应错误发生，1代表相应错误发生。除Bit1、2、3、4、5、6定义的错误以外，其他情况都归为Bit0其他错误

#define OTHER_ERR              0x01//其他错误
#define NO_REQ_DATA_ERR        0x02//无请求数据
#define AUTH_ERR               0x04//密码-权限错
#define MODI_BAUD_ERR          0x08//修改通信速度错
#define YEAR_PERIOD_EXCEED_ERR 0x10//年时区数超
#define DATE_PERIOD_EXCEED_ERR 0x20//日时段数超
#define RATE_EXCEED_ERR        0x40//费率数超
*/
//检查设置数据的格式，正确返回1，错误返回0
INT8U Set_Data_Format_Check(INT16U Index, PROTO_DI PDI, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Re;
  INT8U Spec_Flag;
  //INT8U Temp[5];
  
  TRACE();

  //在P_Data_Info中查找到该项
  //for(i=0;i<S_NUM(P_Data_Info);i++)
  Re = Check_P_Data_Single(Index, PDI, FOR_COMM, &Spec_Flag);
  if(1 EQ Re)
  {
    if(P_Data_Info[Index].Src_Format EQ S_BCD)//找到该项，且该项要求是BCD格式
    {
      if(!Check_BCD_Data(pSrc, SrcLen))//发送来的数据是BCD?
      {
        SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
        return 0;
      }
    }
    
    if(P_Data_Info[Index].Dst_Len != SrcLen) //数据长度不对?
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      return 0;
    }
  }
  
  if(PDI EQ 0x04000201) //年时区数超
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_YEAR_PERIODS)//年时区数超
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, YEAR_PERIOD_EXCEED_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000202)//日时段表数超
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_DATE_TABLES)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000203)//日时段数超
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_DATE_PERIODS)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, DATE_PERIOD_EXCEED_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000204)//费率数超
  {
    Re = Bcd2Hex(pSrc,1);
    if(Re EQ 0 || Re > MAX_RATES) 
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, RATE_EXCEED_ERR);
      return 0;
    }
  }
  else if(PDI EQ 0x04000205) //公共假日数超
  {
    if(Bcd2Hex(pSrc,2) > MAX_YEAR_HOLIDAYS)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);
      return 0;       
    }
  }
  else if(PDI EQ 0x04000207) //预付费梯度数
  {
    if(Bcd2Hex(pSrc,1) > PREPAID_MAX_STEP)
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);      
      return 0;
    }
  }
  else if(PDI EQ 0x04000409 || PDI EQ 0x0400040A)//有无功脉冲常数
  {
    if(Judge_Pulse_Legal(Bcd2Hex(pSrc,3)) EQ 0) //检查脉冲常数的合法性
      return 0;
  }
  else if(PDI EQ 0x04000401) //写通信地址
  {
    if(Check_WR_Comm_Addr(pSrc) EQ 0)
      return 0;
  }

/*
  if(PDI EQ 0x04010000 || PDI EQ 0x04020000)//设置年时区表
  {
    for(i = 0; i < MAX_YEAR_PERIODS; i ++)
    {
      if(i < Multi_Rate_Para.Year_Period) //小于费率数范围内每个数据的格式都必须正确
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
        if(Temp[0] > Multi_Rate_Para.Rates)//费率数超！！！
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

//参数设置成功的后处理
void Set_Para_Aft_Proc(PROTO_DI PDI, INT8U *pSrc)
{
  if(PDI EQ 0x04000103) //需量周期参数修改，需要重新开始一次新的需量周期
  {
    //需量周期发生修改
    if(Bcd2Hex_Byte(*pSrc) != Demand_Para.Period)
    {
      Clr_Demand_Accu();
    }
  }  
}

//保存操作者代码
void Save_Op_ID(INT8U *pSrc)
{
  DIS_PD_INT;
  //mem_cpy((INT8U *)Operator_ID.Last_Op_ID, (INT8U *)Operator_ID.Op_ID, 4, (INT8U *)Operator_ID.Last_Op_ID, sizeof(Operator_ID.Last_Op_ID));
  //当此操作员ID
  mem_cpy((INT8U *)Operator_ID.Op_ID, pSrc, 4, (INT8U *)Operator_ID.Op_ID, sizeof(Operator_ID.Op_ID));
  SET_STRUCT_SUM(Operator_ID);
  SET_STRUCT_SUM(Event_Data);
  EN_PD_INT;  
}

//设置数据处理
//*pAck_Flag表示是否已经给过应答，1表示在函数内部已经给过应答，0表示没有给应答
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
    SET_BIT(Sys_Run_Flag.Err_Flag, NO_REQ_DATA_ERR);//非法数据
    return 0;//0;    
  }
  
  //保存操作者ID
  //备份前一次操作员ID
  Record_Op_ID(pSrc + 8);
  
  if(!(SrcLen >= 12))//包括标识和密码起码有8字节
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);//非法数据
    return 0;//0;
  }

  Single_Flag = 0;//是否是个独立的数据项，而不是数据集之类
  for(i = 0; i < S_NUM(P_Data_Info); i++)
  {
    if(Check_P_Data_Single(i, PDI, FOR_COMM, &Spec_Flag) > 0)
    {
      Single_Flag = 1;
      break;
    }
  }

  if(Single_Flag EQ 0)//不是条独立数据项
  {
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);//数据标识错
    return 0;
  }

  Re = Set_Data_Format_Check(i, PDI, pSrc + 12, (INT8U) (SrcLen - 12));//检查数据格式等
  if(0 EQ Re)
  {
    ASSERT_FAILED();
    return 0;
  }


  Set_Prog_Record_Pre_Porc(Ch, PDI, pAck_Flag);
  //DI到数据之间有6字节的密码哦  
  if((Spec_Flag & 0x80) != 0)
  {
    Re = Set_Spec_Data_Proc(PDI, Spec_Flag, pSrc + 12, (INT8U) (SrcLen - 12));    
  }//正常项的设置
  else
  {
    Re = Set_DI_Data_Proc(i, PDI, pSrc + 12, (INT8U) (SrcLen - 12));
  }

  if(1 EQ Re)
  {
    Set_Para_Modify(PDI);//参数修改记录
    Set_Prog_Record(PDI, (INT8U *)Operator_ID.Op_ID);//编程记录
    Set_Para_Modi_DI(PDI);//设置跳屏标志
    Set_Para_Aft_Proc(PDI, pSrc + 12); //设置参数成功的后处理
  }
  else
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR);//非法数据
  }
  return Re;
}

//设置某DI项数据
//DI,数据标识
//pSrc,源数据起始指针
//SrcLen,源数据长度
INT8U Set_DI_Data_Proc(INT16U Index, PROTO_DI PDI, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Re;

  TRACE();


  //return 0;
  Re = 1;
  Re &= Write_Storage_Data(PDI, pSrc, SrcLen);
  
  return Re;
}

//和模块通信的扩展设置项
INT8U Set_Module_Proto_Data(PROTO_DI PDI, INT8U *pSrc, INT8U SrcLen)
{
  if(PDI EQ 0x0EA20000)//写模块通信状态
  {
    Module_Comm_Status.Var = *pSrc;
    return 1;
  }
  else if(PDI EQ 0x0EA20001)//打开电表写使能
  {
    Module_Set_Meter_Status.Set_En_Mins = 10;
    SET_STRUCT_SUM(Module_Set_Meter_Status);
    return 1;
  }
  
  return 0;
}

//判断是否应该特殊处理的数据项
INT8U Set_Spec_Data_Proc(PROTO_DI PDI, INT8U Spec_Flag, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Temp[4];
  //INT8U Re;
  
  TRACE();
  
  if(Spec_Flag EQ SPEC_TIME)//当前时间
  {
    return Set_Clock_Proto_Data(PDI, pSrc, SrcLen);
  }
  else if(Spec_Flag EQ SPEC_MODULE)//模块通信状态
  {
#if NET_METER != NONET_METER   
    return Set_Module_Proto_Data(PDI, pSrc, SrcLen);
#else
    return 0;
#endif    
  }
  else if(Spec_Flag EQ SPEC_ADJ) //校表清零以及设置瞬时数据
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
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL) //本地费控不能写表号
      return 0;
    
    Read_Storage_Data(_SDI_FAR_PASSWORD_STATE, Temp, Temp, sizeof(Temp));
    if(Temp[0] EQ 0) //公开密钥状态
    {
      return Write_Storage_Data(SDI_METER_ID, pSrc, SrcLen); 
    }
  }
  return 0;
}

//冻结命令解析
INT8U Set_Freeze_Data_Peirod(INT8U *pSrc, INT8U SrcLen)
{
  INT8U Temp[4]= {0x99,0x99,0x99,0x99};
  INT16U Len;
  
  if(SrcLen != 0x04 || Check_BCD_Data(pSrc, 4)!=1)
    return 0;
  
  if(memcmp(pSrc, Temp, 4) EQ 0)//当前是4个99
  {
    //立即冻结
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

//设置需要清除数据标志
//入口参数:
//CLEAR_END_FLAG，没有数据需要清除
//CLEAR_ENERGY_FLAG,需要清除电量
//CLEAR_DEMAND_FLAG,需要清除需量
//CLEAR_VOSTAT_FLAG,需要清楚电压统计
void Set_Clear_Data_Flag(INT32U Flag)
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Clear_Flag);
  ASSERT(1 EQ Re);
  Clear_Flag.Flag = Flag;
  SET_STRUCT_SUM(Clear_Flag);
}

//设通信波特率处理
INT8U Set_CommBaud_Proc(INT8U Ch, INT8U* pSrc, INT8U SrcLen)
{
  TRACE();

  if(Ch EQ CH_RS485_1)//第一路485
  {
    Write_Storage_Data(SDI_COMM1_BAUD, pSrc, 1);
    Set_Para_Modify(SDI_COMM1_BAUD);
    Set_Para_Modi_DI(SDI_COMM1_BAUD);//设置跳屏标志
    return 1;
  }
  else if(Ch EQ CH_RS485_2)//第2路485
  {
    Write_Storage_Data(SDI_COMM2_BAUD, pSrc, 1);
    Set_Para_Modify(SDI_COMM2_BAUD); 
    Set_Para_Modi_DI(SDI_COMM2_BAUD);//设置跳屏标志    
    return 1;
  }
  return 0;
}

//修改密码处理
INT8U Set_PSW_Proc(INT8U* pSrc, INT8U SrcLen)
{
  INT8U Level;
  INT8U Re;
  STORA_DI SDI;

  TRACE();

  Level = pSrc[8];//新设密码的级别
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

//判断写通信地址是否合法
INT8U Check_WR_Comm_Addr(INT8U Addr[])
{
  if(memcmp(Addr, (INT8U *)BROAD_ADDR_99, 6) EQ 0 ||\
     memcmp(Addr, (INT8U *)BROAD_ADDR_AA, 6) EQ 0)
    return 0;
  else 
    return 1;
}

//写设备地址处理
//Ch表示数据的通道
//pSrc,数据起始地址
//SrcLen,数据长度
INT8U Set_MeterAddr_Proc(INT8U Ch, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Re;

  TRACE();

  if(Check_Meter_Prog_Status() EQ 0)
  {
    return 0;
  }

  if(Check_WR_Comm_Addr(pSrc) EQ 0) //判断表地址数据是否合法
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

//获取P_Data_Info数组的成员个数
INT16U Get_P_Data_Info_Num()
{
  return S_NUM(P_Data_Info);
}

//检查收到的DLT645数据的长度是否合法
INT8U Check_DLT645_Data_Len(INT8U Ctrl_Code,INT8U *pSrc,INT8U SrcLen)
{
  TRACE();
  
  if(Ctrl_Code EQ C_READ_DATA && SrcLen>=4)//一般数据是２个字节的标识，但是读取给定时间块的负荷曲线是７字节
    return 1;
  else if(Ctrl_Code EQ C_READ_FOLLOW_DATA)//读后续数据
    return 1;
  if(Ctrl_Code EQ C_SET_DATA && SrcLen>=4) //写数据
    return 1;
  else if(Ctrl_Code EQ C_ADJUST_TIME)
  {
  //if(Mode_Word.Mode[0].Bit.Bit4 EQ 1 && SrcLen EQ 0x0A)//广播校时
      //return NO_ERR;
  if(SrcLen EQ 0x06)
      return 1;
  }
  else if(Ctrl_Code EQ C_SET_ADDR && SrcLen EQ 0x06)//写通信地址
    return 1;
  else if(Ctrl_Code EQ C_READ_ADDR && SrcLen EQ 0x00)//读通信地址
    return 1;
  else if(Ctrl_Code EQ C_SET_COM_BAUD && SrcLen EQ 0x01)//更改通信速率
    return 1;
  else if(Ctrl_Code EQ C_SET_PSW && SrcLen EQ 0x0C)//修改密码
    return 1;
  else if(Ctrl_Code EQ C_CLR_ALL && SrcLen EQ 0x08)//数据总清或者冻结
    return 1;
  else if(Ctrl_Code EQ C_CLR_DEMAND && SrcLen EQ 0x08)//清需量
    return 1;
  else if(Ctrl_Code EQ C_CLR_EVENT && SrcLen EQ 0x0C)//清事件
    return 1;
  else if(Ctrl_Code EQ C_FREEZE_DATA && SrcLen EQ 0x04)//冻结
    return 1;
  else if(Ctrl_Code EQ C_CTRL && SrcLen EQ 0x10) //控制命令
    return 1;
  else if(Ctrl_Code EQ C_PORT && SrcLen EQ 0x01) //多功能 端口设置
    return 1;
  else if(Ctrl_Code EQ C_REMOTE_AUTH)
  return 1;
  return 0;
}

//减0x33
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

//写数据的正确应答,用于先应答再写数据和处理事件记录
void Send_Set_Data_Ack_Frame(INT8U Ch)
{
  INT8U Temp[15];
  INT16U Len;
  
  Len = DLT645_Data_Pack(Ch, (INT8U) (0x14 | 0x80), Temp, 0, Temp, Temp, sizeof(Temp)); 
  Send_HostData_Public_Puck(Ch,(INT8U *)Temp,Len);  
}

//645数据帧的处理
//Ctrl_Code控制码
//pSrc, 645帧起始
//SrcLen, 帧长
//pDst, 目标缓冲区
//pDst_Start, 目标缓冲区起始地址
//DstLen, 目标缓冲区长度
INT16U Rcv_DLT645_Data_Proc(INT8U Ch, INT8U* pFrame, INT8U FrameLen, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Type, Data_Type, Esam_Auth_Flag, Esam_Auth_Ok; 
  INT8U Data_PSW; //修改数据需要的权限
  INT8U User_PSW; //当前用户拥有的权限
  INT8U Len1;
  INT8U Re, Ack_Flag, Set_Data_Ack_Flag; 
  static PROTO_DI PDI;
  PROTO_DI TempPDI;
  INT16U Len,Err_Flag; 
  INT8U Ctrl_Code, SrcLen; 
  INT8U* pSrc; 

  TRACE();
  
  //ErrFlag = 1; 
  Sys_Run_Flag.Err_Flag = 0; //错误信息字清零

  if(Check_Frame_Format(pFrame, FrameLen) EQ 0)
  {
    return 0;
  } 

  Ctrl_Code = *(pFrame + 8); 
  if(Check_Frame_Meter_Addr(Ch, pFrame + 1, Ctrl_Code, &Ack_Flag) EQ 0)
  {
    return 0;
  } 


  //判断表地址
  //ErrFlag = Err_Info.ErrFlag; 
  pSrc = pFrame + 10; //数据域起始地址
  SrcLen = FrameLen - 12; //数据域长度

  //数据域减33
  Sub_33(pSrc, SrcLen);
  
  Esam_Auth_Flag = 0; //是否需要经过Esam密码认证
  Esam_Auth_Ok = 0; //Esam密码认证的结果

  if(PREPAID_EN > 0) //预付费表
  {
    if(Ctrl_Code EQ C_SET_DATA) //设置参数
    {
      mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));
      Data_Type = Check_Data_Type(PDI);

      if(Data_Type EQ 1) //第一类数据
      {
        Esam_Auth_Flag = 1;
        
        if(pSrc[4] != 0x99 || Set_Esam_Para(pSrc, SrcLen) EQ 0)//mac验证通过
          Esam_Auth_Ok = 0;
        else
        {
          Esam_Auth_Ok = 1;
          SrcLen = SrcLen - 4; //数据域需要减4 
        }
      }     
      else if(Data_Type EQ 2) //第二类数据
      {
        Esam_Auth_Flag = 1;
        
        Len1 = 0;
        if(pSrc[4] != 0x98 || Esam_Auth_Check(pSrc, SrcLen, &Len1) EQ 0)//mac验证通过，同时解密
        {
          Esam_Auth_Ok = 0;
          //年时区表和日时段表也可以用02级密码设置--送检要求!!
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
    else if(Ctrl_Code EQ C_CTRL) //控制命令
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
  
  if(Check_Meter_Factory_Status()) //工厂状态下不需要经过Esam验证也可以设参数
  {
    if(Esam_Auth_Flag EQ 1 && pSrc[4] < 0x0A)  
      Esam_Auth_Flag = 0;  
  }
  
  if(Esam_Auth_Flag EQ 1)//表示需要Esam认证
  {
    if(Esam_Auth_Ok EQ 1)//认证通过了
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
      SET_BIT(Sys_Run_Flag.Err_Flag, AUTH_ERR); //密码权限错
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U)(Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);       
    }
  }

  Re = Check_DLT645_Data_Len(Ctrl_Code, pSrc, SrcLen); //判断数据长度
  if(1 != Re)//数据长度不对
  {
    ASSERT_FAILED();
    SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR); //非法数据
    *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
    return DLT645_Data_Pack(Ch, (INT8U)(Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen); 
  }
  
  if(Esam_Auth_Flag EQ 0) //不需要经过Esam认证，表明是三类数据或者是非预付费的多功能表
  {
    //获取执行该操作需要的权限级别
    Data_PSW = Get_P_Data_Info_Authority(Ch, Ctrl_Code, pSrc, SrcLen); 
    if(Data_PSW EQ PSW_NULL)//ASSERT())//没有找到该数据的密码标记
    {
      ASSERT_FAILED();
      SET_BIT(Sys_Run_Flag.Err_Flag, OTHER_ERR); //非法数据
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);
    }
  
    //获取当前用户拥有的权限级别
    User_PSW = Get_User_Authority(Ch, Ctrl_Code, pSrc, SrcLen); //检查当前用户拥有的权限
    if(User_PSW EQ PSW_NULL)//返回用户权限不够
    {
      Debug_Print("User Authority Error"); 
      SET_BIT(Sys_Run_Flag.Err_Flag, AUTH_ERR); //权限不够, 也认为是密码错
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);
    }
  
    if(Check_User_Authurity(User_PSW, Data_PSW) EQ 0)//当前用户权限高于或等于当前数据设置需要的权限, 权限不够!
    {
      SET_BIT(Sys_Run_Flag.Err_Flag, AUTH_ERR); 
      *(pDst + 10) = Sys_Run_Flag.Err_Flag; 
      return DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0xC0), pDst + 10, 1, pDst, pDst_Start, DstLen);
    }
  }
  
  //Meter_Addr_Modify_Flag = 0; //表地址设置标志  
  Cur_Comm_Ch.Ch = Ch; //保存当前通信通道
  Set_Authority_Flag();	

  Clr_Ext_Inter_Dog();
  
  switch(Ctrl_Code)
  {
    case C_READ_DATA: //读数据
      Frame_Ack_Info.Read_Follow_Flag = 0;
      Frame_Ack_Info.Follow_Flag = 0;
      mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));  
      Len = _Get_DLT645_Data(PDI, pSrc + sizeof(PDI), (INT8U) (SrcLen - sizeof(PDI)), pDst + 14, pDst_Start, DstLen, FOR_COMM, &Type); 
      if(Len > 0 || Check_Load_Data_PDI(PDI)) //负荷记录数据在抄读不到的情况下应该返回正确应答
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
    case C_READ_FOLLOW_DATA://读后续数据
      if(Frame_Ack_Info.Follow_Flag EQ 0) //没有后续数据可以读取
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
    case C_SET_DATA: //写数据
      Re = Set_Data_Proc(Ch, pSrc, SrcLen, &Set_Data_Ack_Flag); 
      if(Set_Data_Ack_Flag) Ack_Flag = 0;
      //特殊处理，如果是校表的瞬时数据则不应答,因为是广播命令
      mem_cpy(&TempPDI, pSrc, 4, &TempPDI, sizeof(TempPDI));
      if(TempPDI EQ _PDI_ADJ_INSTANT_DATA) Ack_Flag = 0;
      //----------------
      Len = 0; 
      break; 
    case C_FREEZE_DATA: //冻结
      Re = Set_Freeze_Data_Peirod(pSrc, SrcLen);
      if(memcmp(pFrame + 1, BROAD_ADDR_99, 6) EQ 0) //广播冻结不需要应答
        return 0;
      Len = 0;
      break;
    case C_ADJUST_TIME: //广播校时
      Re = Adjust_Time_Proc(pSrc, SrcLen); 
      Len = 0; 
      return 0; //不需要应答
    case C_SET_ADDR: //写表地址
      Re = Set_MeterAddr_Proc(Ch, pSrc, SrcLen);
      if(Re EQ 1)
      {
        Len = 0;
        break;
      }
      else  //设表地址失败不应答
        return 0; 
    case C_READ_ADDR://读通信地址
      mem_cpy(pDst + 10, (INT8U *)Meter_Addr.Addr[0], 6, pDst_Start, DstLen); 
      Re = 1;
      Len = 6;
      break;
    case C_SET_COM_BAUD://设通信速度
      Re = Set_CommBaud_Proc(Ch, pSrc, SrcLen); 
      if(Re EQ 1)
      {
        *(pDst + 10) = *pSrc;
        Len = 1;
      }
      else
        Len = 0; 
      break; 
    case C_SET_PSW://修改密码
      Re = Set_PSW_Proc(pSrc, SrcLen); 
      if(Re EQ 1)
      {
        mem_cpy(pDst + 10, pSrc + 8, 4, pDst_Start, DstLen); //前4个字节为DI0->DI3不变化
        Len = 4;
      }
      else
        Len = 0;      
      break; 
    case C_CLR_ALL://电表清0

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
    case C_CLR_DEMAND://需量清0
      
      Record_Op_ID(pSrc + 4);
      Set_Clear_Data_Flag(CLEAR_DEMAND_FLAG);      

      Re = 1; 
      Len = 0; 
      break; 
    case C_CLR_EVENT://清事件
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
      
  case C_CTRL: //控制
    Re = Remote_Protocol_Ctrl(pSrc + 8);
    if(Re EQ 1)
    {
      //保存操作者代码
      DIS_PD_INT;
      mem_cpy((INT8U *)Event_Data.Relay_Status.Op_ID, pSrc + 4, 4, (INT8U *)Event_Data.Relay_Status.Op_ID,sizeof(Event_Data.Relay_Status.Op_ID));
      SET_STRUCT_SUM(Event_Data);
      EN_PD_INT;
      //记录操作者代码
      Record_Op_ID(pSrc + 4);
    }    
    Len = 0;
    break;
  case C_PORT: //多功能端子
    Re = Set_Port_Output_Ctrl(*pSrc);
    if(Re > 0)
    {
      *(pDst + 10) = *pSrc;
      Len = 1;      
    }

    break;
  case C_REMOTE_AUTH: //远程认证
    Len = 0;
    Re = Esam_Remote_Auth(pSrc, SrcLen, pDst + 10, (INT8U *)&Len, pDst_Start, DstLen);
    if(Re EQ 0) //验证没有通过
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
  
  if(Ack_Flag EQ 1)//需要发送应答
  {
    if(Re EQ 1)
    {
      if(Frame_Ack_Info.Follow_Flag EQ 1)//有后续数据，需要返回控制码0xA1
        Ctrl_Code = (Ctrl_Code | 0xA0);
      else
        Ctrl_Code = (Ctrl_Code | 0x80);    

      if(Frame_Ack_Info.Read_Follow_Flag EQ 1)//当前接收到的帧是读后续数据帧
      {
        *(pDst + 10 + Len) = Frame_Ack_Info.Frame_Seq;//增加帧序号
        Len ++;
      }
        
      Len = DLT645_Data_Pack(Ch, (INT8U) (Ctrl_Code | 0x80), pDst + 10, Len, pDst, pDst_Start, DstLen); 
 
      //判断表地址是否发生了修改，如果已经修改，则要重新读取到Meter_Addr变量中，读取只能在打包函数后
      //因为应答帧仍然采用老的表地址
 
  
      //ASSERT(1 EQ ErrFlag); 
      return Len;
    }
    else
    {
      //否定应答设错误标示字
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

//检查系统的协议数据传输
INT8U Check_Protocol_Data_Trans()
{
  INT32U i, j, k, l;
  INT16U Len;
  INT8U Re;
  PROTO_DI PDI;
  PROTO_DI Num;
  
  if(Check_Meter_Factory_Status() EQ 0)//工厂状态才检查
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

