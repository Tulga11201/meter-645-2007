#ifndef SOFT_FM24C16
#define SOFT_FM24C16


#define SET_16_SCLK_DIR(a)  PM7_bit.no0=a    
#define SET_16_SDA_DIR(a)    PM0_bit.no6=a
#define SET_16_WP_OUTPUT    PM7_bit.no5=0

#define SET_16_SCLK(a)       P7_bit.no0=a    //将SCL总线置---------PUCK    
#define SET_16_SDA(a)        P0_bit.no6=a     //将SDA总线置---------PUCK   
#define SET_16_WP(a)         P7_bit.no5=a    //将WP置---------PUCK

#define GET_16_STATUS       (P0_bit.no6)



void Set_16_Sclk_Dir(INT8U Dir);
void Set_16_Sda_Dir(INT8U Dir);
void Set_16_Sclk_Pin(INT8U Level);
void Set_16_Sda_Pin(INT8U Level);
INT8U Get_16_Sda_Pin(void);
void Set_16_Wp_Pin(INT8U Flag);

#endif
