
#define CPU_PUB_C
#include "DrvPub.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "B0"
#endif
/**************************************************************
���ݲ�ͬ�Ĺ���ģʽ���л���ʱ��ϵͳ���ر���Ӧ����
**************************************************************/
INT8U  Switch_Main_Osc(INT8U  Mode)
{
  switch(Mode)
  {
    case RUN_MODE:
      if(CG_ChangeClockMode(SYSX1CLK)==MD_OK)
      {/*
        HIOSTOP=1;      //�ر�fih
        XTSTOP=0;       //����fxt*/
        return 1;
      }
      break;
    case FX1_RUN_MODE:
      if(CG_ChangeClockMode(HIOCLK)==MD_OK)
      {/*
        HIOSTOP=1;      //�ر�fih
        XTSTOP=0;       //����fxt*/
        return 1;
      }
      break;
      
    case HALT_MODE:
      if(CG_ChangeClockMode(SUBCLK)==MD_OK)
      {
        MSTOP=1;           //�ر�fx
        HIOSTOP=1;         //�ر�fih
        /*
        XTSTOP=1;       //�ر�fxt
        */
       return 1;        
      }
      break;
    case FXT_RUN_MODE:
     if(CG_ChangeClockMode(SUBCLK)==MD_OK)
     {
       MSTOP=1;           //�ر�fx
       return 1;
     }
     break;
  }
  return 0;
}

