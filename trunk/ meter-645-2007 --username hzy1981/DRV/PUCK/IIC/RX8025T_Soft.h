#ifndef SOFT_8025T_H
#define SOFT_8025T_H

#if EXT_RTC_TYPE==DRV_SIMU_RX8025T     //宏开启，打开DS8025T的软件模拟功能


#define SET_8025T_SCLK_DIR(a)  PM2_bit.no7=a
#define SET_8025T_SDA_DIR(a)   PM2_bit.no6=a


#define SET_8025T_SCLK(a)       P2_bit.no7=a    //将SCL总线置---------PUCK
#define SET_8025T_SDA(a)        P2_bit.no6=a     //将SDA总线置---------PUCK

#define GET_8025T_SDA       (P2_bit.no6)


void Set_8025T_Sclk_Dir(INT8U Dir);
void Set_8025T_Sda_Dir(INT8U Dir);
void Set_8025T_Sclk_Pin(INT8U Level);
void Set_8025T_Sda_Pin(INT8U Level);
INT8U Get_8025T_Sda_Pin(void);
#endif

#endif