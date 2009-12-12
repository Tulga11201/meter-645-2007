#ifndef PAY_PUB_DRV_H
#define PAY_PUB_DRV_H

#ifndef PAY_PUB_DRV_C
#define PAY_PUB_DRV_EXT extern volatile
#else
#define PAY_PUB_DRV_EXT volatile
#endif



INT8U Cpu_Esam_Hard_Operate(INT8U Type,INT8U Operate);
#endif
