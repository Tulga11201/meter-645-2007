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
�������ܣ�
��ڣ�
���ڣ�1------------------��ȡ�ɹ���0----------��ȡʧ��
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
�������ܣ�
��ڣ�
���ڣ����ڣ�1------------------д��ɹ���0----------д��ʧ��
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
�������ܣ���ʼ���ⲿRTC
��ڣ�
���ڣ�
**********************************************************************************/   
void Init_RTC_Pulse(INT8U Flag)
{
  INT8U temp[3]={0,0,0},i,Err=0;  

  //״̬�����󲻻���0
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
  
  if(i EQ 3)  //3�ζ�������
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
  
  
  if(Flag EQ 0 && (GET_BIT(temp[2],5) || GET_BIT(temp[2],5))) //��ֹ�������
  {
    CLR_BIT(temp[2],5);
    CLR_BIT(temp[2],6);
    Err=1;
  }
  
  
  if(Flag && (GET_BIT(temp[2],5) EQ 0 || GET_BIT(temp[2],5) EQ 0)) //�������
  {
    SET_BIT(temp[2],5);
    SET_BIT(temp[2],6);
    Err=1;
  }
  
  if(Err EQ 0)
    return ;
   
  for(i=0;i<3;i++)  //�������������ֻ��д 0x0E �Ĵ���
  {
    if(0==Write_EXT_RTC_Buf(0x0D,3,temp))
      ASSERT_FAILED();
    else
      break;
  }
}
/**********************************************************************************
�������ܣ���ȡ�ⲿʱ�ӵ�״̬0
**********************************************************************************/
INT8U Read_Ext_RTC_Status(void)
{
  INT8U temp[3]={0,0,0},Re,i;
  
  //���󲻻����㣡
  for(i=0;i<3;i++)
  {
    if(Read_EXT_RTC_Buf(0x0E,2,temp) EQ 0)
      ASSERT_FAILED();    
    else
      break;
  }
   if(3==i)  //3�ζ�������
    return EXT_RTC_I2C_ERR;
  
  Re=EXT_RTC_OK;
  if(GET_BIT(temp[0],5))    //�����������ò���
  {
    CLR_BIT(temp[0],5);
    Re|=EXT_RTC_PULSE_ERR;
    Debug_Print("Ext_RTC Error----->Period Err!");
  }
  
  
  if(GET_BIT(temp[1],0))    //�²�ֹͣ��
  {
    CLR_BIT(temp[1],0);
    Re|=EXT_RTC_PSEC_ERR;
    Debug_Print("Ext_RTC Error----->Temp Stop!");
  }
  
  if(GET_BIT(temp[1],1))    //��ѹ��
  {
    CLR_BIT(temp[1],1);
    Re|=EXT_RTC_BAT_LOW;
    Re|=EXT_RTC_COUNT_STOP;  //ͳһ HUCK�ӿ�
    Debug_Print("Ext_RTC Error----->Power Low!");
  }     
                
  if(Get_Sys_Status() EQ SYS_NORMAL)
  {
    if((INT8U)(temp[2]&0x60) !=0x60)  //���������
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]|=0x60;                 //ʹ��������,�趨����
    }
  }
  else
  {
    if((INT8U)(temp[0]&0x60) !=0x00)  //��ֹ����
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]&=0x9F;                 //��ֹ������
    }
  }
    
  
  if(Re EQ EXT_RTC_OK)  //û�д���
    return EXT_RTC_OK;
  
  for(i=0;i<3;i++)  //�д��󣬻�д 0x0D 0x0E  0x0F �Ĵ���
  {
    if(0==Write_EXT_RTC_Buf(0x0D,3,temp))
      ASSERT_FAILED();
    else
      break;
  }  

  return Re;
}
/**********************************************************************************
�������ܣ����ʱ���Ƿ�æ
��ڣ�
���ڣ�
**********************************************************************************/
INT8U Check_ExtRTC_Busy(void)
{
  return EXT_RTC_OK;
}
#endif
