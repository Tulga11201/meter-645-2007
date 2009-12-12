#ifndef FREEZE_PROTO_H
#define FREEZE_PROTO_H

#undef EXT
#ifdef FREEZE_PROTO_C
#define EXT
#else
#define EXT extern
#endif

#define PERIOD_FREEZE_TYPE          0x00  //��ʱ����
#define INSTANT_FREEZE_TYPE         0x01  //˲ʱ����
#define YEAR_SWITCH_FREEZE_TYPE     0x02  //��ʱ���л�����
#define DATE_SWITCH_FREEZE_TYPE     0x03  //��ʱ�α��л�����
#define HOUR_FREEZE_TYPE            0x04  //���㶳��
#define RATE_SWITCH_FREEZE_TYPE     0x05  //��ʱ�����л�����
#define DATE_FREEZE_TYPE            0x06  //�ն���
#define STEP_SWITCH_FREEZE_TYPE     0x07  //���ݷ����л�����
#define ENG_OVERTURN_FREEZE_TYPE    0x08  //������ת����


EXT INT16U Get_Freeze_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);


#endif
