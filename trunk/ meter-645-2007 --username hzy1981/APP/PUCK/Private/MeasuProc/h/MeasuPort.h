#ifndef MEASU_PORT_H
#define MEASU_PORT_H


#ifndef MEASU_PORT_C
#define MEASU_PORT_EXT extern volatile
#else
#define MEASU_PORT_EXT volatile
#endif

//�й��������������---P66
#define SET_AC_POWER_OUT       PM6_bit.no6=0,P6_bit.no6=1
#define SET_AC_POWER_IN        PM6_bit.no6=1

//�޹��������������---P676
#define SET_REAC_POWER_OUT     PM6_bit.no7=0,P6_bit.no7=1
#define SET_REAC_POWER_IN      PM6_bit.no7=1

//�й�����---P64
#define SET_AC_DIR_OUT         PM6_bit.no4=0,P6_bit.no4=1
#define SET_AC_DIR_IN          PM6_bit.no4=1

//�޹�����---P65
#define SET_REAC_DIR_OUT       PM6_bit.no5=0,P6_bit.no5=1
#define SET_REAC_DIR_IN        PM6_bit.no5=1

//���й�����LED���---P150
#define SET_AC_LED_OUT         PM15_bit.no0=0,P15_bit.no0=1
#define SET_AC_LED_IN          PM15_bit.no0=1

//���޹�����LED���---P151
#define SET_REAC_LED_OUT       PM15_bit.no1=0,P15_bit.no1=1
#define SET_REAC_LED_IN        PM15_bit.no1=1


void Init_Pulse_Port(INT8U);

#endif