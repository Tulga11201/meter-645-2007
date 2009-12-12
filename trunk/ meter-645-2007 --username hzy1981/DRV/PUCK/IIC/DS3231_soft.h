#ifndef SOFT_DS3231_H
#define SOFT_DS3231_H

#if EXT_RTC_TYPE==DRV_SIMU_DS3231     //�꿪������DS3231�����ģ�⹦��


#define SET_3231_SCLK_DIR(a)  PM2_bit.no7=a
#define SET_3231_SDA_DIR(a)   PM2_bit.no6=a


#define SET_3231_SCLK(a)       P2_bit.no7=a    //��SCL������---------PUCK
#define SET_3231_SDA(a)        P2_bit.no6=a     //��SDA������---------PUCK

#define GET_3231_SDA       (P2_bit.no6)


void Set_3231_Sclk_Dir(INT8U Dir);
void Set_3231_Sda_Dir(INT8U Dir);
void Set_3231_Sclk_Pin(INT8U Level);
void Set_3231_Sda_Pin(INT8U Level);
INT8U Get_3231_Sda_Pin(void);
#endif

#endif