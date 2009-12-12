#ifndef DRV_CFG_H
#define DRV_CFG_H



#ifndef DRV_TEST_C
#define DRV_TEST_EXT  extern volatile
#else
#define DRV_TEST_EXT  volatile
#endif


INT8U Beep_For_Err_Item(INT8U item);

#endif
