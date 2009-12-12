#include "DrvPub.h"

#if EXT_RTC_TYPE==DRV_SIMU_RX8025T

/**********************************************************************************/
/**********************************************************************************/ 
void Set_8025T_Sclk_Dir(INT8U Dir)
{
  SET_8025T_SCLK_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_8025T_Sda_Dir(INT8U Dir)
{

   SET_8025T_SDA_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_8025T_Sclk_Pin(INT8U Level)
{
   SET_8025T_SCLK(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_8025T_Sda_Pin(INT8U Level)
{
  SET_8025T_SDA(Level);
}
/**********************************************************************************
**********************************************************************************/ 
INT8U Get_8025T_Sda_Pin(void)
{
  return (GET_8025T_SDA);  
}


/**********************************************************************************
函数功能：
入口：
出口：1------------------读取成功；0----------读取失败
**********************************************************************************/   
INT8U Read_EXT_RTC_Buf(INT8U addr,INT8U Len,INT8U *Dst)
{
  INT8U OkFlag;

#ifdef SOFT_I2C_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif  

   I2cSoft_Start(IIC_SOFT_ID0);
   OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID0,0x64);
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,addr);
   I2cSoft_Start(IIC_SOFT_ID0);
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,0x65);   
   OkFlag&=I2cSoft_Read_nByteS(IIC_SOFT_ID0,Len,Dst);
   OkFlag&=I2cSoft_Stop(IIC_SOFT_ID0);
#ifdef SOFT_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cSoft_Reset(IIC_SOFT_ID0);
      OkFlag=0;
    }
    return OkFlag;
}
/**********************************************************************************
函数功能：
入口：
出口：出口：1------------------写入成功；0----------写入失败
**********************************************************************************/   
INT8U Write_EXT_RTC_Buf(INT8U addr,INT8U Len,INT8U *Src)
{
  INT8U i,OkFlag;

#ifdef SOFT_I2C_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif     
    I2cSoft_Start(IIC_SOFT_ID0);
    OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID0,0x64);	
    OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,addr);
    for(i=0;i<Len;i++)
      OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,Src[i]);
    OkFlag&=I2cSoft_Stop(IIC_SOFT_ID0);
#ifdef SOFT_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cSoft_Reset(IIC_SOFT_ID0);
      OkFlag=0;
    }
    return OkFlag;  
}

#pragma optimize=none
/**********************************************************************************
函数功能：初始化外部RTC
入口：
出口：
**********************************************************************************/   
void Init_RTC_Pulse(INT8U Flag)
{  
  INT8U temp[2],i;  

  temp[1]=0XA0; 
  temp[0]=0X20;
  if(Flag)
   temp[0]=0X23;
  
  for(i=0;i<3;i++)
  {
    if(Write_EXT_RTC_Buf(0x0e,2,temp) EQ 0)
      ASSERT_FAILED();
    else
      break;
  }
  
  /* 
 if(Read_EXT_RTC_Buf(0x0e,7,temp)  EQ 0)
    ASSERT_FAILED();
  
   if(GET_BIT(temp[1],7) EQ 0 || GET_BIT(temp[1],5) EQ 0)  //1.3V电压检测/停振
    ASSERT_FAILED();
  
  if(Flag)
  {
    if(temp[0]!=0x23) 
      ASSERT_FAILED();
  }
  else
  {
    if(temp[0]!=0x20) 
      ASSERT_FAILED();    
  }
  */
}
/**********************************************************************************
函数功能：获取外部时钟的状态
**********************************************************************************/
INT8U Read_Ext_RTC_Status(void)
{
  INT8U temp[2],Re,i;
  
  for(i=0;i<3;i++)
  {
    if(Read_EXT_RTC_Buf(0x0E,2,temp) EQ 0)
      ASSERT_FAILED();    
    else
      break;
  }
   if(3==i)  //3次都读不出
    return EXT_RTC_I2C_ERR;
  
  Re=EXT_RTC_OK;
  if(GET_BIT(temp[0],5) EQ 0)    //12/24时钟制错误
    Re|=EXT_RTC_PSEC_ERR;
  
  if(GET_BIT(temp[1],6))    //电源电压低
    Re|=EXT_RTC_BAT_LOW;
  
  if(GET_BIT(temp[1],5) EQ 0)    //停振
    Re|=EXT_RTC_COUNT_STOP;
  
  if(GET_BIT(temp[1],4))    //电源电压低
    Re|=EXT_RTC_FIRST_PWRON;
  
  if(Re!=EXT_RTC_OK)  //0x10:power_on reset flag PON bit=1; 0x20:oscillation stop flag /XST=0;  0x40: Power drop is detected. (Vdd<1.3V)
  {
    Debug_Print("Ext_RTC Error----->Reg(0X0E/0x0F)=0x%x/0x%x",temp[0],temp[1]);
  }
  return Re;
}
/**********************************************************************************
函数功能：检查时钟是否忙
入口：
出口：
**********************************************************************************/
INT8U Check_ExtRTC_Busy(void)
{
  return EXT_RTC_OK;

}
#endif
