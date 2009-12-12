#ifndef IIC_SOFT_H
#define IIC_SOFT_H


#ifdef  SOFT_I2C_C
#define EXT_SOFT_I2C
#else
#define EXT_SOFT_I2C extern
#endif




#define IIC_SOFT_ID0        0      //3231/8025/8025T
#define IIC_SOFT_ID1        1      //FM24C16
#define IIC_SOFT_ID2        2      //BL55076



#define IIC_SOFT_MIN_ID      IIC_SOFT_ID0
#define IIC_SOFT_MAX_ID      IIC_SOFT_ID2




#define SOFT_I2C_ENV //宏开启：使能setjmp绝对跳转
#ifdef SOFT_I2C_ENV
EXT_SOFT_I2C Enviornment Soft_I2c_Env;
#endif

void I2cSoft_Open(INT8U Id);
void I2cSoft_Close(INT8U Id);

INT8U I2cSoft_Start(INT8U Id);
INT8U I2cSoft_Stop(INT8U Id) ;
INT8U I2cSoft_Send_N_Ack(INT8U Id,INT8U Ack_Nack);
INT8U I2cSoft_Send_Byte(INT8U Id,INT8U sbyte);
INT8U I2cSoft_Read_Byte(INT8U Id,INT8U *Dst);
void I2cSoft_Reset(INT8U Id);
INT8U I2cSoft_EnWp(INT8U Id,INT8U Wp);
#endif