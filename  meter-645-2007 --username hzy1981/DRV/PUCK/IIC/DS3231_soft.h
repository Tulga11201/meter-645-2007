#ifndef SOFT_DS3231_H
#define SOFT_DS3231_H

#if EXT_RTC_TYPE==DRV_SIMU_DS3231     //宏开启，打开DS3231的软件模拟功能


#define SET_3231_SCLK_DIR(a)  PM2_bit.no7=a
#define SET_3231_SDA_DIR(a)   PM2_bit.no6=a


#define SET_3231_SCLK(a)       P2_bit.no7=a    //将SCL总线置---------PUCK
#define SET_3231_SDA(a)        P2_bit.no6=a     //将SDA总线置---------PUCK

#define GET_3231_SDA       (P2_bit.no6)


void Set_3231_Sclk_Dir(INT8U Dir);
void Set_3231_Sda_Dir(INT8U Dir);
void Set_3231_Sclk_Pin(INT8U Level);
void Set_3231_Sda_Pin(INT8U Level);
INT8U Get_3231_Sda_Pin(void);
#endif

#endif