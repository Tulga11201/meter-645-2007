#ifndef CAL_DIS_VAR
#define CAL_DIS_VAR


#ifndef CAL_DIS_C
#define CAL_DIS_EXT  extern volatile
#else
#define CAL_DIS_EXT volatile
#endif



void Cal_Dis_Proc(void);

#endif
