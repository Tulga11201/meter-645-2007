#ifndef REMOTE_H
#define REMOTE_H



#ifndef REMOTE_PUCK
#define REMOTE_PUCK_EXT  extern volatile
#else
#define REMOTE_PUCK_EXT volatile
#endif



#define CODE_NUM 4
#pragma pack(1)
typedef struct
{
  INT8U Head;
  INT8U Start:1;              //������ʼ�ź�
  INT8U Done:1;              //����bit������
  INT8U Index:6;              //��ȡ��bit��������
  INT8U TrigTimer;
  INT8U CodeBuf[CODE_NUM];    //�Ƿ���������
  INT8U Tail;
}IRDA_DECODE;
REMOTE_PUCK_EXT IRDA_DECODE Irda_Decode_Ctrl;
#pragma pack()

void Remote_Key_Proc(void);
#endif