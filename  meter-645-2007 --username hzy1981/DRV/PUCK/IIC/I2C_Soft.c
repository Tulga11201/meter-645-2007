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
函数功能：初始化模拟IIC口
入口：
出口：
**********************************************************************************/ 
void I2cSoft_Open(INT8U Id)   //将总线置为空闲状态
{
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
  {
    ASSERT_FAILED();
    return ;
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);             //改为输出为1
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);              //改为输出为1
  if(CONST_I2C_PORT[Id].Set_Wp_Pin)
    CONST_I2C_PORT[Id].Set_Wp_Pin(1);   //写保护
}
/**********************************************************************************
函数功能：关闭模拟IIC口
入口：
出口：
**********************************************************************************/ 
void I2cSoft_Close(INT8U Id)   //将总线置为空闲状态
{
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
  {
    ASSERT_FAILED();
    return ;
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Dir(DIR_INPUT);
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);         //改为输出为1
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);           //改为输出为1
  
}

/**********************************************************************************
函数功能：启动软件模拟I2C口,11.0592下，测试SCLK频率为73.5k
入口：
出口：
**********************************************************************************/ 
INT8U I2cSoft_Start(INT8U Id)
{
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
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

  CONST_I2C_PORT[Id].Set_Sda_Pin(0);        //SDA在SCLK为高时，产生一个下降沿,起始条件产生---------PUCK
  return 1;
}
/**********************************************************************************
函数功能：停止3231
入口：
出口：
**********************************************************************************/ 
INT8U I2cSoft_Stop(INT8U Id)    //在SCLK为高的情况下，SDA产生一个上升沿，作为停止条件
{
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
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
函数功能：使能写保护
入口： Wp：0-------写保护关闭;1----------写保护打开
出口：
**********************************************************************************/ 
INT8U I2cSoft_EnWp(INT8U Id,INT8U Wp)
{
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
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
函数功能：回应ACK或者NACK
入口：
出口：
**********************************************************************************/ 
INT8U I2cSoft_Send_N_Ack(INT8U Id,INT8U Ack_Nack)
{
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);  //清0，握住总线-----------------PUCK
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
  CONST_I2C_PORT[Id].Set_Sda_Pin(Ack_Nack);  //Ack_Nack为0表示ACK，为1表示NACK    
  
  CONST_I2C_PORT[Id].Set_Sclk_Pin(1);  //SCLK为高时，SDA为低，表示发送ACK
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  return 1;
}
/**********************************************************************************
函数功能：检测是否有ACK信号
入口：
出口：1-------------成功；0----------失败
**********************************************************************************/ 
INT8U I2cSoft_Check_Ack(INT8U Id)
{
  INT8U count;
    
  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif 
  }

  if(Id!=IIC_SOFT_ID1)
  {
    CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //设置SDA,释放总线-------------PUCK
    CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);    
    CONST_I2C_PORT[Id].Set_Sclk_Pin(1);     //握总线，查询ACK
    for(count=0;count<100;count++)
    {
      if(CONST_I2C_PORT[Id].Get_Sda_Pin()==0)  //ACK回应,为0，表示是ACK
      {
        CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
        return 1;
      }    
    } 
  }
  else  //16片子
  {    
    SET_16_SDA(1);    //CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //设置SDA,释放总线-------------PUCK
    SET_16_SDA_DIR(DIR_INPUT);  //CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);    
    SET_16_SCLK(1);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(1);     //握总线，查询ACK  
    for(count=0;count<100;count++)
    {
      if(GET_16_STATUS EQ 0)  //ACK回应,为0，表示是ACK
      {
        SET_16_SCLK(0);         //CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        SET_16_SDA_DIR(DIR_OUTPUT);  //CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
        return 1;
      }    
    } 
  }
  
   
  CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_OUTPUT);
    
   ASSERT_FAILED();   //直接断言，可能影响速度！----------PUCK
  
#ifdef SOFT_I2C_ENV    
    longjmp(Soft_I2c_Env.Env,1);
#endif 
    return 0;
}

/**********************************************************************************
函数功能：iic总线上发数据:8bits
入口：
出口：1-------------成功；0----------失败
**********************************************************************************/ 
INT8U I2cSoft_Send_Byte(INT8U Id,INT8U sbyte)
{	
  INT8U i;

  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
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
        CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL变高，锁存数据
        CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
        sbyte <<=1;
    }
  }
  else  //16片子
  {
    for (i=0;i<8;i++)
    {
        if(sbyte&0x80)
            SET_16_SDA(1);  //CONST_I2C_PORT[Id].Set_Sda_Pin(1);
        else
            SET_16_SDA(0);  //CONST_I2C_PORT[Id].Set_Sda_Pin(0);
        SET_16_SCLK(1);  //CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL变高，锁存数据
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
  CONST_I2C_PORT[Id].Set_Sda_Pin(1);  //SDA置1,SCL脉冲，释放总线
  for(i=0;i<=9;i++)
  { 
    CONST_I2C_PORT[Id].Set_Sclk_Pin(1);    //SCL变高，锁存数据
    CONST_I2C_PORT[Id].Set_Sclk_Pin(0);
  }  
  I2cSoft_Start(Id);
  I2cSoft_Stop(Id);
  I2cSoft_Open(Id);
} 
/**********************************************************************************
函数功能：iic总线上读数据:8bits
入口：
出口：1-------------成功；0----------失败
**********************************************************************************/ 
INT8U I2cSoft_Read_Byte(INT8U Id,INT8U *Dst)
{
  INT8U i;
  INT8U temp;

  if(Id>IIC_SOFT_MAX_ID)  //直接断言，可能影响速度！----------PUCK
  {
#ifdef SOFT_I2C_ENV
    longjmp(Soft_I2c_Env.Env,1);
#else
    return 0;
#endif     
  }
  
  if(Id!=IIC_SOFT_ID1)
  {
    CONST_I2C_PORT[Id].Set_Sda_Pin(1);        //设置SDA,释放总线-------------PUCK
    CONST_I2C_PORT[Id].Set_Sda_Dir(DIR_INPUT);
  }
  else //16片子
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
  else //16片子
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
