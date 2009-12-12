
#include "DrvPub.h"

#if DRV_HARD_DS3231==1 && EXT_RTC_TYPE!=DRV_SIMU_DS3231   //硬件I2C开启,并且RTC不是用的软件I2C模拟.
/**********************************************************************************
函数功能：
入口：
出口：出口：1------------------读取成功；0----------读取失败
**********************************************************************************/   
INT8U Read_EXT_RTC_Buf(INT8U addr,INT8U Len,INT8U *Dst)
{
 INT8U i,OkFlag;
 
#ifdef HARD_I2C_ENV
   if(setjmp(Hard_I2c_Env.Env)==0)
   {
#endif 
     
    IICE0=1;               //打开II2C操作时钟，因有可能会关闭-----------PUCK
    OkFlag=I2cStartCondition();	
    OkFlag&=I2cPutAddress(0xd0);	
    OkFlag&=I2cPutData(addr);
    I2cStart();
    OkFlag&=I2cPutData(0xd1);	 //读操作
    for(i=0;i<Len-1;i++)
        OkFlag&=I2cGetDataAckSet(Dst+i);
    OkFlag&=I2cGetDataNackSet(Dst+Len-1);
    I2cStopCondition();
#ifdef HARD_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
   {
      Debug_Print("IIC_Error----->Reset I2c_Hard Device!");  
      I2cReset();
   }
  return OkFlag;
}
/**********************************************************************************
函数功能：
入口：
出口：出口：1------------------写入成功；0----------写入失败
**********************************************************************************/   
INT8U Write_EXT_RTC_Buf(INT8U Addr,INT8U Len,INT8U *Src)
{
  INT8U i,OkFlag;
  IICE0=1;               //打开II2C操作时钟，因有可能会关闭-----------PUCK
  OkFlag=I2cStartCondition();	
  OkFlag&=I2cPutAddress(0xd0);	
  OkFlag&=I2cPutData(Addr);
  for(i=0;i<Len;i++)
    OkFlag&=I2cPutData(Src[i]);
  I2cStopCondition();
  if(!OkFlag)
  {
    Debug_Print("IIC_Error----->Reset I2c_Hard Device!");  
    I2cReset();
  }
  return OkFlag;
}
#endif
