#define SOFT_I2C_C
#include "DrvPub.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "B1"
#endif


typedef struct
{ 
  void (* const Set_Sclk_Dir)(INT8U);
  void (* const Set_Sda_Dir)(INT8U);
  void (* const Set_Sclk_Pin)(INT8U);
  void (* const Set_Sda_Pin)(INT8U);
  INT8U (* const Get_Sda_Pin)(void);
  void (* const Set_Wp_Pin)(INT8U);
}CONST_SOFT_IIC;

CONST CONST_SOFT_IIC  CONST_I2C_PORT[IIC_SOFT_MAX_ID+1]=
{
#if   EXT_RTC_TYPE==DRV_SIMU_DS3231
  {&Set_3231_Sclk_Dir,&Set_3231_Sda_Dir,&Set_3231_Sclk_Pin,&Set_3231_Sda_Pin,&Get_3231_Sda_Pin,0},    //----------------0
#elif EXT_RTC_TYPE==DRV_SIMU_RX8025
  {&Set_8025_Sclk_Dir,&Set_8025_Sda_Dir,&Set_8025_Sclk_Pin,&Set_8025_Sda_Pin,&Get_8025_Sda_Pin,0},    //----------------0
#else
  {&Set_8025T_Sclk_Dir,&Set_8025T_Sda_Dir,&Set_8025T_Sclk_Pin,&Set_8025T_Sda_Pin,&Get_8025T_Sda_Pin,0},    //----------------0
#endif

#ifdef IIC_SOFT_ID1
  {&Set_16_Sclk_Dir,&Set_16_Sda_Dir,&Set_16_Sclk_Pin,&Set_16_Sda_Pin,&Get_16_Sda_Pin,&Set_16_Wp_Pin},    //----------------0
#endif

#ifdef IIC_SOFT_ID2 
  {&Set_55076_Sclk_Dir,&Set_55076_Sda_Dir,&Set_55076_Sclk_Pin,&Set_55076_Sda_Pin,&Get_55076_Sda_Pin,0}    //----------------0
#endif

};

/**********************************************************************************
�������ܣ���ʼ��ģ��IIC��
��ڣ�
���ڣ�
**********************************************************************************/ 
void I2cSoft_Open(INT8U Id)   //��������Ϊ����״̬
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
    ASSERT_FAILED();
    return ;
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);             //��Ϊ���Ϊ1
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);              //��Ϊ���Ϊ1
  if(CONST_I2C_PORT[Id].Set_Wp_Pin)
    CONST_I2C_PORT[Id].Set_Wp_Pin(1);   //д����
}
/**********************************************************************************
�������ܣ��ر�ģ��IIC��
��ڣ�
���ڣ�
**********************************************************************************/ 
void I2cSoft_Close(INT8U Id)   //��������Ϊ����״̬
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
    ASSERT_FAILED();
    return ;
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Dir(DIR_INPUT);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);         //��Ϊ���Ϊ1
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);           //��Ϊ���Ϊ1
  
}

/**********************************************************************************
�������ܣ��������ģ��I2C��,11.0592�£�����SCLKƵ��Ϊ73.5k
��ڣ�
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_Start(INT8U Id)
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
    ASSERT_FAILED();
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);

  CONST_I2C_PORT[Id].Set_Sda_Pin(0);        //SDA��SCLKΪ��ʱ������һ���½���,��ʼ��������---------PUCK
  return 1;
}
/**********************************************************************************
�������ܣ�ֹͣ3231
��ڣ�
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_Stop(INT8U Id)    //��SCLKΪ�ߵ�����£�SDA����һ�������أ���Ϊֹͣ����
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(0);  

  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);
  return 1;
}
/**********************************************************************************
�������ܣ�ʹ��д����
��ڣ� Wp��0-------д�����ر�;1----------д������
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_EnWp(INT8U Id,INT8U Wp)
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef SOFT_I2C_ENV
      longjmp(Soft_I2c_Env.Env,1);
#else
      return 0;
#endif 
  }
  
  if(CONST_I2C_PORT[Id].Set_Wp_Pin)
    CONST_I2C_PORT[Id].Set_Wp_Pin(Wp);  
  return 1;
}

/**********************************************************************************
�������ܣ���ӦACK����NACK
��ڣ�
���ڣ�
**********************************************************************************/ 
INT8U I2cSoft_Send_N_Ack(INT8U Id,INT8U Ack_Nack)
{
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);  //��0����ס����-----------------PUCK
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(Ack_Nack);  //Ack_NackΪ0��ʾACK��Ϊ1��ʾNACK    
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);  //SCLKΪ��ʱ��SDAΪ�ͣ���ʾ����ACK
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  return 1;
}
/**********************************************************************************
�������ܣ�����Ƿ���ACK�ź�
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Check_Ack(INT8U Id)
{
  INT8U count;
    
  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }

  if(Id!=IIC_SOFT_ID1)
  {
    CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //����SDA,�ͷ�����-------------PUCK
    CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);    
    CONST_I2C_PORT[Id].Set_Sclk_Pin(1);     //�����ߣ���ѯACK
    for(count=0;count<100;count++)
    {
      if(CONST_I2C_PORT[Id].Get_Sda_Pin()==0)  //ACK��Ӧ,Ϊ0����ʾ��ACK
      {
        CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
        return 1;
      }    
    } 
  }
  else  //16Ƭ��
  {    
    SET_16_SDA(1);    //CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //����SDA,�ͷ�����-------------PUCK
    SET_16_SDA_DIR(DIR_INPUT);  //CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);    
    SET_16_SCLK(1);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(1);     //�����ߣ���ѯACK  
    for(count=0;count<100;count++)
    {
      if(GET_16_STATUS EQ 0)  //ACK��Ӧ,Ϊ0����ʾ��ACK
      {
        SET_16_SCLK(0);         //CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        SET_16_SDA_DIR(DIR_OUTPUT);  //CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
        return 1;
      }    
    } 
  }
  
   
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
    
   ASSERT_FAILED();   //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  
#ifdef SOFT_I2C_ENV    
    longjmp(Soft_I2c_Env.Env,1);
#endif 
    return 0;
}

/**********************************************************************************
�������ܣ�iic�����Ϸ�����:8bits
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Send_Byte(INT8U Id,INT8U sbyte)
{	
  INT8U i;

  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  
  
  if(Id!=IIC_SOFT_ID1)
  {
    for (i=0;i<8;i++)
    {
        if(sbyte&0x80)
            CONST_I2C_PORT[Id].Set_Sda_Pin(1);
        else
            CONST_I2C_PORT[Id].Set_Sda_Pin(0);
        CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL��ߣ���������
        CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        sbyte <<=1;
    }
  }
  else  //16Ƭ��
  {
    for (i=0;i<8;i++)
    {
        if(sbyte&0x80)
            SET_16_SDA(1);  //CONST_I2C_PORT[Id].Set_Sda_Pin(1);
        else
            SET_16_SDA(0);  //CONST_I2C_PORT[Id].Set_Sda_Pin(0);
        SET_16_SCLK(1);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL��ߣ���������
        SET_16_SCLK(0);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        sbyte <<=1;
    }    
  }
  return(I2cSoft_Check_Ack(Id));	 	    
}
/********************************************************************************
********************************************************************************/
void I2cSoft_Reset(INT8U Id)
{
  INT8U i;
  
  Debug_Print("IIC_Error----->Reset I2c_Soft Device,Id=%d!",Id); 
  ASSERT_FAILED();
  I2cSoft_Start(Id);
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);  //SDA��1,SCL���壬�ͷ�����
  for(i=0;i<=9;i++)
  { 
    CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL��ߣ���������
    CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  }  
  I2cSoft_Start(Id);
  I2cSoft_Stop(Id);
  I2cSoft_Open(Id);
} 
/**********************************************************************************
�������ܣ�iic�����϶�����:8bits
��ڣ�
���ڣ�1-------------�ɹ���0----------ʧ��
**********************************************************************************/ 
INT8U I2cSoft_Read_Byte(INT8U Id,INT8U *Dst)
{
  INT8U i;
  INT8U temp;

  if(Id>IIC_SOFT_MAX_ID)  //ֱ�Ӷ��ԣ�����Ӱ���ٶȣ�----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif     
  }
  
  if(Id!=IIC_SOFT_ID1)
  {
    CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //����SDA,�ͷ�����-------------PUCK
    CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  }
  else //16Ƭ��
  {
    SET_16_SDA(1);                //CONST_I2C_PORT[Id].Set_Sda_Pin(1);
    SET_16_SDA_DIR(DIR_INPUT);    //CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  }
  
  if(Id!=IIC_SOFT_ID1)
  {
    for(i=0,temp=0;i<8;i++)
    {
        temp<<=1;
        CONST_I2C_PORT[Id].Set_Sclk_Pin(1);
        if(CONST_I2C_PORT[Id].Get_Sda_Pin())
          temp|=1;
        CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
    }
  }
  else //16Ƭ��
  {
    for(i=0,temp=0;i<8;i++)
    {
        temp<<=1;
        SET_16_SCLK(1);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(1);
        if(GET_16_STATUS)
          temp|=1;
        SET_16_SCLK(0);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
    }
  }
  
  *Dst=temp;
  return  1;
}
