#define CPU_CARD_DRV_C
#include "Pub_PUCK.h"

#if PREPAID_METER>0


/**********************************************************************************/
/**********************************************************************************/ 
void Set_CpuCard_IO_Dir(void)
{
    SET_CPU_CARD_PWR_DIR;      //输出:1-----开启电源
    SET_CPU_CARD_RST_DIR;      //输出:0-------有效
    SET_CPU_CARD_CLK_DIR;      //输出:0-------使能时钟    
    SET_CPU_CARD_SW_DIR;       //输入
}
/**********************************************************************************
**********************************************************************************/ 
void Set_CpuCard_Pwr(INT8U Level)
{
  SET_CPU_CARD_PWR_DIR;        //输出:1-----开启电源
  SET_CPU_CARD_POWER(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_CpuCard_Rst(INT8U Level)
{
  SET_CPU_CARD_RST_DIR;        //输出:1-----开启电源
  SET_CPU_CARD_RST(Level);
}
/**********************************************************************************
**********************************************************************************/ 
void Set_CpuCard_Clk(INT8U Level)
{
#ifdef LOW_COST_HARD_EN           //Level：0表示开启soft时钟
  INIT_IC_CLK;
  if(Level)
    STOP_IC_CLK;
  else    
    START_IC_CLK;
#else  
  SET_CPU_CARD_CLK_DIR;        //输出:1-----开启电源
  SET_CPU_CARD_CLK(Level);
#endif  
}
#endif