#include "DrvPub.h"

#if EXT_RTC_TYPE==DRV_SIMU_RV3029C2

/**********************************************************************************/
/**********************************************************************************/ 
void Set_RV3029_Sclk_Dir(INT8U Dir)
{
  SET_RV3029_SCLK_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_RV3029_Sda_Dir(INT8U Dir)
{

   SET_RV3029_SDA_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_RV3029_Sclk_Pin(INT8U Level)
{
   SET_RV3029_SCLK(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_RV3029_Sda_Pin(INT8U Level)
{
  SET_RV3029_SDA(Level);
}
/**********************************************************************************
**********************************************************************************/ 
INT8U Get_RV3029_Sda_Pin(void)
{
  return (GET_RV3029_SDA);  
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
   OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID0,0xAC);
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,addr);
   I2cSoft_Start(IIC_SOFT_ID0);
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,0xAD);   
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
    OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID0,0xAC);	
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
  INT8U temp[3]={0,0,0},i,Err=0;  

  //状态：读后不会清0
  for(i=0;i<3;i++)
  {
    if(0==Read_EXT_RTC_Buf(0x0D,3,temp))
      ASSERT_FAILED();
    else
    {
      Debug_Print("Ext_RTC Power On,Reg(0x0D)=0x%x,Reg(0x0E)=0x%x,Reg(0x0F)=0x%x!",temp[0],temp[1],temp[2]);
      break;
    }
  }
  
  if(i EQ 3)  //3次都读不出
   return ;
    
  if(GET_BIT(temp[0],5))
  {
    CLR_BIT(temp[0],5);
    Err=1;
  }
  
   
  if(GET_BIT(temp[1],5))
  {
    CLR_BIT(temp[1],5);
    Err=1;
  }
  
  
  if(Flag EQ 0 && (GET_BIT(temp[2],5) || GET_BIT(temp[2],5))) //禁止输出脉冲
  {
    CLR_BIT(temp[2],5);
    CLR_BIT(temp[2],6);
    Err=1;
  }
  
  
  if(Flag && (GET_BIT(temp[2],5) EQ 0 || GET_BIT(temp[2],5) EQ 0)) //输出脉冲
  {
    SET_BIT(temp[2],5);
    SET_BIT(temp[2],6);
    Err=1;
  }
  
  if(Err EQ 0)
    return ;
   
  for(i=0;i<3;i++)  //是脉冲输出错误，只回写 0x0E 寄存器
  {
    if(0==Write_EXT_RTC_Buf(0x0D,3,temp))
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
  INT8U temp[3]={0,0,0},Re,i;
  
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
  if(GET_BIT(temp[0],5))    //脉冲周期设置不对
  {
    CLR_BIT(temp[0],5);
    Re|=EXT_RTC_PULSE_ERR;
    Debug_Print("Ext_RTC Error----->Period Err!");
  }
  
  
  if(GET_BIT(temp[1],0))    //温补停止了
  {
    CLR_BIT(temp[1],0);
    Re|=EXT_RTC_PSEC_ERR;
    Debug_Print("Ext_RTC Error----->Temp Stop!");
  }
  
  if(GET_BIT(temp[1],1))    //电压低
  {
    CLR_BIT(temp[1],1);
    Re|=EXT_RTC_BAT_LOW;
    Re|=EXT_RTC_COUNT_STOP;  //统一 HUCK接口
    Debug_Print("Ext_RTC Error----->Power Low!");
  }     
                
  if(Get_Sys_Status() EQ SYS_NORMAL)
  {
    if((INT8U)(temp[2]&0x60) !=0x60)  //输出秒脉冲
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]|=0x60;                 //使能秒脉冲,设定周期
    }
  }
  else
  {
    if((INT8U)(temp[0]&0x60) !=0x00)  //禁止脉冲
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]&=0x9F;                 //禁止秒脉冲
    }
  }
    
  
  if(Re EQ EXT_RTC_OK)  //没有错误
    return EXT_RTC_OK;
  
  for(i=0;i<3;i++)  //有错误，回写 0x0D 0x0E  0x0F 寄存器
  {
    if(0==Write_EXT_RTC_Buf(0x0D,3,temp))
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
