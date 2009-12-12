#define CPU_CARD_DRV_C
#include "Pub_PUCK.h"

#if PREPAID_METER>0

typedef struct
{ 
  INT8U Pwr_Valid:1;
  INT8U Rst_Valid:1;
  INT8U Clk_Valid:1;
  INT8U Reserved:5;
  
  void (* const Set_All_Io_Dir)(void);   //���õ�ǰ�������͵�IO�ڷ���
  void (* const Set_Io_Pwr)(INT8U);      //���õ�ǰPwr_IO�ڵ�����
  void (* const Set_Io_Rst)(INT8U);      //���õ�ǰRst_IO�ڵ�����
  void (* const Set_Io_Clk)(INT8U);     //���õ�ǰclk_IO�ڵ�����
}CONST_PAY_IO_TYPE;


CONST CONST_PAY_IO_TYPE  CONST_PAY_IO[]=
{
  {0},
  {0,1,0,0,&Set_CpuCard_IO_Dir,&Set_CpuCard_Pwr,&Set_CpuCard_Rst,&Set_CpuCard_Clk},
  {1,0,0,0,&Set_Esam_IO_Dir,   &Set_Esam_Pwr,   &Set_Esam_Rst,   &Set_Esam_Clk}
};


/**********************************************************************************/
/**********************************************************************************/ 
INT8U Cpu_Esam_Hard_Operate(INT8U Type,INT8U Operate)  //8U pDstLen,INT8U *pDst,INT8U *pDstStart)
{
  if(Type >MAX_CPU_ESAM_TYPE)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  switch(Operate)
  {
    case CPU_ESAM_DRV_RST_COOL:
      if(Type EQ PAY_ESAM)
      {
        CONST_PAY_IO[Type].Set_Io_Pwr(CONST_PAY_IO[Type].Pwr_Valid);  
        WAITFOR_DRV_CYCLE_TIMEOUT(6000)
      }
      CONST_PAY_IO[Type].Set_Io_Rst(CONST_PAY_IO[Type].Rst_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)
      CONST_PAY_IO[Type].Set_Io_Clk(!CONST_PAY_IO[Type].Clk_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)      
      if(Type EQ PAY_CPU_CARD)
      {
        CONST_PAY_IO[Type].Set_Io_Pwr(CONST_PAY_IO[Type].Pwr_Valid);  
        WAITFOR_DRV_CYCLE_TIMEOUT(6000)
      }
      
      CONST_PAY_IO[Type].Set_Io_Clk(CONST_PAY_IO[Type].Clk_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)
      CONST_PAY_IO[Type].Set_Io_Rst(!CONST_PAY_IO[Type].Rst_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)
      Clear_All_Dog();
        //CPU���临λ,��Ҫ�õ� ���źͷ�ɢ����
      return 1;
      
    case CPU_ESAM_DRV_RST_HOT:
      CONST_PAY_IO[Type].Set_Io_Rst(CONST_PAY_IO[Type].Rst_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200) 
      CONST_PAY_IO[Type].Set_Io_Rst(!CONST_PAY_IO[Type].Rst_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)
      Clear_All_Dog();
      return 1;
      
    case CPU_ESAM_DRV_POWER_OFF:
      CONST_PAY_IO[Type].Set_Io_Rst(CONST_PAY_IO[Type].Rst_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)
      CONST_PAY_IO[Type].Set_Io_Clk(!CONST_PAY_IO[Type].Clk_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(1200)
      CONST_PAY_IO[Type].Set_Io_Pwr(!CONST_PAY_IO[Type].Pwr_Valid);
      WAITFOR_DRV_CYCLE_TIMEOUT(6000)
      Clear_All_Dog();
      return 1;
  }
  return 0;
}

#endif