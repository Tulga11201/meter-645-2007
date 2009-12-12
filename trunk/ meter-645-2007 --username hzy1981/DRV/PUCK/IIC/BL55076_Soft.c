#include "DrvPub.h"
 
  

/**********************************************************************************/
/**********************************************************************************/ 
void Set_55076_Sclk_Dir(INT8U Dir)
{
  SET_55076_SCLK_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_55076_Sda_Dir(INT8U Dir)
{

   SET_55076_SDA_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_55076_Sclk_Pin(INT8U Level)
{
   SET_55076_SCLK(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_55076_Sda_Pin(INT8U Level)
{
  SET_55076_SDA(Level);
}
/**********************************************************************************
**********************************************************************************/ 
INT8U Get_55076_Sda_Pin(void)
{
  return (GET_55076_SDA);  
}
/**********************************************************************************
函数功能：
入口：
出口：出口：1------------------写入成功；0----------写入失败
**********************************************************************************/   
INT8U Write_55076_Cmd(INT8U Len,INT8U *Src)
{
  INT8U i,OkFlag;

#ifdef SOFT_I2C_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif     
    I2cSoft_Start(IIC_SOFT_ID2);
    OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID2,BL55076_SLAVE_ADDR);	
    OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID2,BL55076_DEVICE_ADDR);
    for(i=0;i<Len;i++)
      OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID2,Src[i]);
    OkFlag&=I2cSoft_Stop(IIC_SOFT_ID2);
#ifdef SOFT_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cSoft_Reset(IIC_SOFT_ID2);
      OkFlag=0;
    }
    return OkFlag;  
}
/**********************************************************************************
函数功能：
入口：
出口：出口：1------------------写入成功；0----------写入失败
**********************************************************************************/   
INT8U Write_55076_Data(INT8U Len,INT8U *Src)
{
  INT8U i,OkFlag;

#ifdef SOFT_I2C_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif     
    I2cSoft_Start(IIC_SOFT_ID2);
    OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID2,BL55076_SLAVE_ADDR);	
    OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID2,BL55076_DEVICE_ADDR);
    OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID2,0);     //起始地址
    for(i=0;i<Len;i++)
      OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID2,Src[i]);
    OkFlag&=I2cSoft_Stop(IIC_SOFT_ID2);
#ifdef SOFT_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cSoft_Reset(IIC_SOFT_ID2);
      OkFlag=0;
    }
    return OkFlag;  
}