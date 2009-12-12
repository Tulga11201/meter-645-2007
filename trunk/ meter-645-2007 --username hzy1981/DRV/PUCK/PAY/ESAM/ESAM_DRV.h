#ifndef ESAM_DRV_H
#define ESAM_DRV_H

#ifndef ESAM_DRV_C
#define ESAM_DRV_EXT extern volatile
#else
#define ESAM_DRV_EXT volatile
#endif

#define SET_ESAM_PWR_DIR       PM1_bit.no5=0  //输出:1-------开启电源，注意：三相智能此脚做为485 发送切换脚
#define SET_ESAM_RST_DIR       PM8_bit.no4=0  //输出:0-------复位有效
#define SET_ESAM_CLK_DIR       PM5_bit.no5=0  //输出:0-------使能时钟


#define SET_ESAM_POWER(a)      P1_bit.no5=a
#define SET_ESAM_RST(a)        P8_bit.no4=a
#define SET_ESAM_CLK(a)        P5_bit.no5=a


void Set_Esam_IO_Dir(void);
void Set_Esam_IO_Dir(void);
void Set_Esam_Pwr(INT8U Level);
void Set_Esam_Rst(INT8U Level);
void Set_Esam_Clk(INT8U Level);


#endif
