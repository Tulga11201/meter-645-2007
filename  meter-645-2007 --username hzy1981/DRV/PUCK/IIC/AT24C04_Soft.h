#ifndef SOFT_AT24C04
#define SOFT_AT24C04


#ifdef ID_MEM_24C04     //宏开启，打开校表口的模拟 I2C功能
    #define SET_04_SCLK_OUTPUT  PM0_bit.no2=0
    #define SET_04_SCLK_INPUT   PM0_bit.no2=1
    
    #define SET_04_SDA_OUTPUT   PM0_bit.no1=0
    #define SET_04_SDA_INPUT    PM0_bit.no1=1
    
    #define CLR_04_SCLK_0       P0_bit.no2=0    //将SCL总线置0---------PUCK   
    #define SET_04_SCLK_1       P0_bit.no2=1    //将SCL总线置1---------PUCK
    
    #define CLR_04_SDA_0        P0_bit.no1=0     //将SDA总线置0---------PUCK
    #define SET_04_SDA_1        P0_bit.no1=1     //将SDA总线置1---------PUCK
    
    #define GET_04_STATUS       (P0_bit.no1)
    
    void Set_04_Sclk_Dir(INT8U Dir);
    void Set_04_Sda_Dir(INT8U Dir);
    void Set_04_Sclk_Pin(INT8U Level);
    void Set_04_Sda_Pin(INT8U Level);
    INT8U Get_04_Sda_Pin(void);
#endif
    
#endif
