#ifndef SOFT_RV3029_H
#define SOFT_RV3029_H

#if EXT_RTC_TYPE==DRV_SIMU_RV3029C2     //宏开启，打开 RV3029C2 的软件模拟功能


#define SET_RV3029_SCLK_DIR(a)  PM2_bit.no7=a
#define SET_RV3029_SDA_DIR(a)   PM2_bit.no6=a


#define SET_RV3029_SCLK(a)       P2_bit.no7=a    //将SCL总线置---------PUCK
#define SET_RV3029_SDA(a)        P2_bit.no6=a     //将SDA总线置---------PUCK

#define GET_RV3029_SDA       (P2_bit.no6)


void Set_RV3029_Sclk_Dir(INT8U Dir);
void Set_RV3029_Sda_Dir(INT8U Dir);
void Set_RV3029_Sclk_Pin(INT8U Level);
void Set_RV3029_Sda_Pin(INT8U Level);
INT8U Get_RV3029_Sda_Pin(void);
#endif

#endif