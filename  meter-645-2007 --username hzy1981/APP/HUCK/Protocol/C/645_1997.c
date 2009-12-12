#define DLT645_1997_C
#include "Includes.h"

CONST S_Proto_Trans Proto_Trans[] =
{
  {0xB210,0x00, 0x03300001,0x00, 1,4},//���һ�α��ʱ��
  {0xB211,0x00, 0x03300201,0x00, 1,4},//���һ�����������0ʱ��
  {0xB212,0x00, 0x03300000,0x00, 0,2},//��̴���
  {0xB213,0x00, 0x03300200,0x00, 0,3},//���������0����

};

//��ȡ��645����
INT16U Get_DLT645_97_Data(INT16U DI_97, void* pDst, void* pDst_Start, INT16U DstLen)
{
  //INT8U Bef_Mon;
  PROTO_DI DI;

  TRACK();

  DI = 0;
  //����������ʱ��?
  if(((DI_97 & 0xF000) >> 8) EQ 0x90 || ((DI_97 & 0xF000) >> 8) EQ 0xA0 || ((DI_97 & 0xF000) EQ 0xB0))
  {
    switch((INT8U) ((DI & 0x0F00) >> 8))
    {
      case 0:
      case 1:
        DI |= 0;
        break;
      case 4:
      case 5:
        DI |= 0x01;
        break;
      case 8:
      case 9:
        DI |= 0x02;
        break;
      default:
        return 0;
    }

    switch((INT8U) ((DI_97 & 0xF000) >> 12))//����
    {
      case 0x09:
        DI |= 0;
        break;
      case 0x0A:
      case 0x0B:
        DI |= 0x01000000;
        break;
      default:
        return 0;
    }

    //��������������
    switch((INT8U) ((DI_97 & 0x0FF0) >> 4))
    {
      case 0x01:
        //�����й�
        DI |= 0x00010000;
        break;
      case 0x02:
        //�����й�
        DI |= 0x00020000;
        break;
      case 0x11:
        //����޹�1
        DI |= 0x00030000;
        break;
      case 0x12:
        //����޹�2
        DI |= 0x00040000;
        break;
      case 0x13:
        //һ����
        DI |= 0x00050000;
        break;
      case 0x14:
        //������
        DI |= 0x00080000;
        break;
      case 0x15:
        //������
        DI |= 0x00060000;
        break;
      case 0x16:
        //������
        DI |= 0x00070000;
        break;
      default:
        return 0;
    }

    DI |= (((PROTO_DI) (DI_97 & 0x0F)) << 8);
    return Get_DLT645_Data(DI, pDst, pDst_Start, DstLen);
  }
  return 0;
}

#undef DLT645_1997_C
