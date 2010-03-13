#include "DrvPub.h"

#if EXT_RTC_TYPE==DRV_SIMU_RX8025

/**********************************************************************************/
/**********************************************************************************/ 
void Set_8025_Sclk_Dir(INT8U Dir)
{
  SET_8025_SCLK_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_8025_Sda_Dir(INT8U Dir)
{

   SET_8025_SDA_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_8025_Sclk_Pin(INT8U Level)
{
   SET_8025_SCLK(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_8025_Sda_Pin(INT8U Level)
{
  SET_8025_SDA(Level);
}
/**********************************************************************************
**********************************************************************************/ 
INT8U Get_8025_Sda_Pin(void)
{
  return (GET_8025_SDA);  
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
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,addr<<4);
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
    OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,addr<<4);
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
  INT8U temp[2]={0,0},i,Err=0;  

  //状态：读后不会清0
  for(i=0;i<3;i++)
  {
    if(0==Read_EXT_RTC_Buf(0x0E,2,temp))
      ASSERT_FAILED();
    else
    {
      Debug_Print("Ext_RTC Power On,Reg(0x0E)=0x%x,Reg(0x0F)=0x%x!",temp[0],temp[1]);
      break;
    }
  }
  
   if(i EQ 3)  //3次都读不出
   return ;
  
  if(GET_BIT(temp[0],5) EQ 0)    //12/24时钟制错误
  {
    Err=1;
    Debug_Print("Ext_RTC Error----->12/24 error,Res bit!");
  }
  
  if(GET_BIT(temp[1],6))    //电源电压低
  {
    Err=1;
    Debug_Print("Ext_RTC Error----->Bat Lowr,Res bit!");
  }
  
  if(GET_BIT(temp[1],5) EQ 0)    //停振
  {
    Err=1;
    Debug_Print("Ext_RTC Error----->OSC Stop,Res bit!");
  }
  
  if(GET_BIT(temp[1],4))    //电源复位
  {
    Err=1;
    Debug_Print("Ext_RTC Error----->Power Rst,Res bit!");
  }
  
  
  if(Flag &&((INT8U)(temp[0]&0x03) !=0x03))  //输出脉冲
  {
    Err=2;
    temp[0]|=0x03;                 //使能秒脉冲
  }
  
  if((Flag EQ 0) && ((INT8U)(temp[0]&0x03) !=0x00))  //禁止脉冲
  {
    Err=2;
    temp[0]&=0xFC;                 //禁止秒脉冲
  }
  
  if(Err<=1)  //不是脉冲输出模式字错误
    return ;
  
  for(i=0;i<3;i++)  //是脉冲输出错误，只回写 0x0E 寄存器
  {
    if(0==Write_EXT_RTC_Buf(0x0E,1,temp))
      ASSERT_FAILED();
    else
      break;
  }

}
/**********************************************************************************
函数功能：获取外部时钟的状态0
**********************************************************************************/
INT8U Read_Ext_RTC_Status(void)
{
  INT8U temp[2]={0,0},Re,i;
  
  //读后不会清零！
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
  {
    SET_BIT(temp[0],5);
    Re|=EXT_RTC_PSEC_ERR;
    Debug_Print("Ext_RTC Error----->12/24 error,Clr bit!");
  }
  
  if(GET_BIT(temp[1],6))    //电源电压低
  {
    CLR_BIT(temp[1],6);
    Re|=EXT_RTC_BAT_LOW;
    Re|=EXT_RTC_COUNT_STOP;  //统一 HUCK接口
    Debug_Print("Ext_RTC Error----->Bat Lowr,Clr bit!");
  }
  
  if(GET_BIT(temp[1],5) EQ 0)    //停振
  {
    SET_BIT(temp[1],5);
    Re|=EXT_RTC_COUNT_STOP;
    Debug_Print("Ext_RTC Error----->OSC Stop,Clr bit!");
  }
  
  if(GET_BIT(temp[1],4))    //电源复位
  {
    CLR_BIT(temp[1],4);
    Re|=EXT_RTC_FIRST_PWRON;
    Re|=EXT_RTC_COUNT_STOP;  //统一 HUCK接口
    Debug_Print("Ext_RTC Error----->Power Rst,Clr bit!");
  }
  
  if(Get_Sys_Status() EQ SYS_NORMAL)
  {
    if((INT8U)(temp[0]&0x03) !=0x03)  //输出秒脉冲
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]|=0x03;                 //使能秒脉冲
    }
  }
  else
  {
    if((INT8U)(temp[0]&0x03) !=0x00)  //禁止脉冲
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]&=0xFC;                 //禁止秒脉冲
    }
  }
    
  
  if(Re EQ EXT_RTC_OK)  //没有错误
    return EXT_RTC_OK;
  
  for(i=0;i<3;i++)  //有错误，回写 0x0E  0x0F 寄存器
  {
    if(0==Write_EXT_RTC_Buf(0x0E,2,temp))
      ASSERT_FAILED();
    else
      break;
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
