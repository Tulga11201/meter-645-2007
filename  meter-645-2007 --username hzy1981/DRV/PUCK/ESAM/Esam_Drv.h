#ifndef ESAM_DRV_H
#define ESAM_DRV_H

#ifndef ESAM_DRV_C
#define ESAM_DRV_EXT extern volatile
#else
#define ESAM_DRV_EXT volatile
#endif




#define SET_IC_CARD_FAIL_DIR      PM3_bit.no0=1
#define SET_IC_CARD_IN_DIR        PM5_bit.no0=1
#define SET_IC_CARD_OUT_DIR       PM5_bit.no1=0
#define SET_IC_CARD_RST_DIR       PM5_bit.no2=0
#define SET_IC_CARD_SW_DIR        PM5_bit.no3=1
#define SET_IC_CARD_PWR_DIR       PM6_bit.no3=0 
#define SET_IC_CARD_CLK_DIR       PM8_bit.no7=0


#define IC_CARD_IN                (P5_bit.no0)   //输入
#define IC_CARD_OUT_0             P5_bit.no1=0   //输出
#define IC_CARD_OUT_1             P5_bit.no1=1   //输出
#define IC_CARD_RST_0             P5_bit.no2=0   //输出
#define IC_CARD_RST_1             P5_bit.no2=1   //输出
#define IC_CARD_SW                (P5_bit.no3)   //输入

#define IC_CARD_POWR_ON           P6_bit.no3=1   //输出
#define IC_CARD_POWR_OFF          P6_bit.no3=0   //输出


#define IC_CARD_CLK_0             P8_bit.no7=0  //输出
#define IC_CARD_CLK_1             P8_bit.no7=1  //输出

#define IC_CARD_FAIL              (P3_bit.no0)   //输入


void Read_Data_From_ICcard(INT16U Addr,INT8U *Dst,INT8U Len);
INT8U Write_Data_To_ICcard(INT16U Addr,INT8U *Src,INT8U Len);
#endif
