#include "DrvPub.h"

#if EXT_RTC_TYPE==DRV_SIMU_DS3231

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "B5"
#endif



/**********************************************************************************/
/**********************************************************************************/ 
void Set_3231_Sclk_Dir(INT8U Dir)
{
  SET_3231_SCLK_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_3231_Sda_Dir(INT8U Dir)
{

   SET_3231_SDA_DIR(Dir);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_3231_Sclk_Pin(INT8U Level)
{
   SET_3231_SCLK(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_3231_Sda_Pin(INT8U Level)
{
  SET_3231_SDA(Level);
}
/**********************************************************************************
**********************************************************************************/ 
INT8U Get_3231_Sda_Pin(void)
{
  return (GET_3231_SDA);  
}

/**********************************************************************************
**********************************************************************************/ 
void Init_DS3231_IIC_Soft(void)
{
  I2cSoft_Open(IIC_SOFT_ID0);
}
/**********************************************************************************
**********************************************************************************/ 
void Close_DS3231_IIC_Soft(void)
{
  I2cSoft_Close(IIC_SOFT_ID0);  
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
   OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID0,0xd0);
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,addr);
   I2cSoft_Start(IIC_SOFT_ID0);
   OkFlag&=I2cSoft_Send_Byte(IIC_SOFT_ID0,0xd1);   
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
    OkFlag=I2cSoft_Send_Byte(IIC_SOFT_ID0,0xd0);	
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


/**********************************************************************************
�������ܣ���ʼ���ⲿRTC
��ڣ�
���ڣ�
**********************************************************************************/   
void Init_RTC_Pulse(INT8U Flag)
{

  INT8U temp[2]={0,0},i,Err=0;  
   
                   
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
  
  if(i EQ 3)  //3�ζ�������
   return ;
  
  if(GET_BIT(temp[1],3))
  {
    Debug_Print("Ext_RTC Error----->32kHZ Out,NoChange Bit!");
    Err=1;    
  }
  if(GET_BIT(temp[1],7))
  {
    Debug_Print("Ext_RTC Error----->OSC Stop,NoChange Bit!");
    Err=1;    
  }
  
  if((Flag != 0) &&(temp[0] !=0x40))  //�������
  {
    Err=2;    
    temp[0]=0x40; 
  }
  
  if((Flag EQ 0) &&(temp[0] !=0x04))  //��ֹ����
  {
    Err=2;    
    temp[0]=0x04;
  }
  
  
  if(Err<=1)  //�����������ģʽ�ִ���
    return ;
  
  for(i=0;i<3;i++)  //�д���ֻ��д 0x0E �Ĵ���
  {
    if(0==Write_EXT_RTC_Buf(0x0E,1,temp))
      ASSERT_FAILED();
    else
      break;
  }
}

/**********************************************************************************
�������ܣ���ȡ�ⲿʱ�ӵ�״̬
**********************************************************************************/
INT8U Read_Ext_RTC_Status(void)
{
  INT8U temp[2]={0,0},Re,i;
  
  for(i=0;i<3;i++)
  {
    if(0==Read_EXT_RTC_Buf(0x0E,2,temp))
      ASSERT_FAILED();
    else
      break;
  }

  if(3==i)  //3�ζ�������
    return EXT_RTC_I2C_ERR;
  
  Re=EXT_RTC_OK;
  if(GET_BIT(temp[1],7))    //OSFֹͣ
  {
    CLR_BIT(temp[1],7);
    Re|=EXT_RTC_COUNT_STOP;    
    Debug_Print("Ext_RTC Error----->Found EXT RTC Osc Stop!");
  }
  
  if(Get_Sys_Status() EQ SYS_NORMAL)
  {
    if(temp[0] !=0x40)  //���������
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]=0x40;                  //ʹ��������
    }
  }
  else
  {
    if(temp[0] !=0x04)  //��ֹ����
    {
      Re|=EXT_RTC_PULSE_ERR;
      temp[0]=0x04;                  //��ֹ������
    }
  }
 
  if(Re EQ EXT_RTC_OK)  //û�д���
    return EXT_RTC_OK;
  
  for(i=0;i<3;i++)  //�д��󣬻�д 0x0E  0x0F �Ĵ���
  {
    if(0==Write_EXT_RTC_Buf(0x0E,2,temp))
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
  INT8U temp,Re,i;  
  for(i=0;i<3;i++)
  {
    if(Read_EXT_RTC_Buf(0xf,1,&temp) EQ 0)
      ASSERT_FAILED();
    else
      break;
  }
  if(3==i)  //3�ζ�������
    return EXT_RTC_I2C_ERR;
  
  Re=EXT_RTC_OK;  
  if(GET_BIT(temp,2))
  {
    Re|=EXT_RTC_BUSY;
    Debug_Print("Ext_RTC Error----->Found EXT RTC BUSY!");    
  }   
  return Re;
}
#endif
