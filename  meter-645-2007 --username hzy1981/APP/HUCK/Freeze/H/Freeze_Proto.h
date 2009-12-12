#ifndef FREEZE_PROTO_H
#define FREEZE_PROTO_H

#undef EXT
#ifdef FREEZE_PROTO_C
#define EXT
#else
#define EXT extern
#endif

#define PERIOD_FREEZE_TYPE          0x00  //定时冻结
#define INSTANT_FREEZE_TYPE         0x01  //瞬时冻结
#define YEAR_SWITCH_FREEZE_TYPE     0x02  //年时区切换冻结
#define DATE_SWITCH_FREEZE_TYPE     0x03  //日时段表切换冻结
#define HOUR_FREEZE_TYPE            0x04  //整点冻结
#define RATE_SWITCH_FREEZE_TYPE     0x05  //分时费率切换冻结
#define DATE_FREEZE_TYPE            0x06  //日冻结
#define STEP_SWITCH_FREEZE_TYPE     0x07  //阶梯方案切换冻结
#define ENG_OVERTURN_FREEZE_TYPE    0x08  //电量翻转冻结


EXT INT16U Get_Freeze_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);


#endif
