#ifndef EVENT_PROTO_H
#define EVENT_PROTO_H


#define MAX_DATA_LEN_NUM  54//�ú겻��С�����ٱ��������ĸ�����1����len�������һ��һ����һ��Ϊ0����ʾ
typedef struct
{
  INT8U Num;//���ݸ���
  INT16U Len[MAX_DATA_LEN_NUM];//ÿ�����ݵĳ��ȣ���λ:�ֽ�
}S_Event_Info_Quck;

typedef struct
{
  PROTO_DI PDI;//�¼���id��Ҳ����PROTO_DI��ǰ�����ֽڣ�
  CONST INT16U *pSub_Len;//�¼���Ϣ��
  INT8U Num;
}S_Event_PDI_Info_Quck;

/*
//#include "Data_Para.h"
typedef struct
{
  PROTO_DI PDI; //�ۼ����ݵ�Э��DI
  INT8U Data_Num; //�ۼ����������
  
  
}S_Event_Cumu_Proto
*/
EXT PROTO_DI Get_Event_Separate_Start_PDI(PROTO_DI PDI);
EXT INT16U Get_Event_Cumu_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
EXT INT16U _Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U *pSpec_Flag);
EXT INT16U Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen);
#endif

