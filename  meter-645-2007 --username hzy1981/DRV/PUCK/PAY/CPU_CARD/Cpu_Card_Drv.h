#ifndef CPU_CARD_DRV_H
#define CPU_CARD_DRV_H

#ifndef CPU_CARD_DRV_C
#define CPU_CARD_DRV_EXT extern volatile
#else
#define CPU_CARD_DRV_EXT volatile
#endif


#define SET_CPU_CARD_PWR_DIR       PM3_bit.no0=0  //输出:0-------开启电源
#define SET_CPU_CARD_RST_DIR       PM5_bit.no2=0  //输出:1-------复位有效
#define SET_CPU_CARD_CLK_DIR       PM8_bit.no7=0  //输出:0-------使能时钟

#define SET_CPU_CARD_SW_DIR        PM5_bit.no3=1  //输入




#define SET_CPU_CARD_POWER(a)       P3_bit.no0=a
#define SET_CPU_CARD_RST(a)         P5_bit.no2=a
#define SET_CPU_CARD_CLK(a)         P8_bit.no7=a


#define CPU_CARD_INSERT             P5_bit.no3   //卡插入检测：1-------卡插入；0------卡未插入



void Set_CpuCard_IO_Dir(void);
void Set_CpuCard_IO_Dir(void);
void Set_CpuCard_Pwr(INT8U Level);
void Set_CpuCard_Rst(INT8U Level);
void Set_CpuCard_Clk(INT8U Level);



#endif
