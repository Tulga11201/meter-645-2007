#define VOLSTAT_PROTO_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H24"
#endif

//��ȡ��ѹͳ������
INT16U _Get_VolStat_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U i, Bef_Mon;
  S_VolStat* p;
  //S_HEX_Time TempTime;
  INT16U Len;

  i = (INT8U) ((PDI & 0x0000FF00) >> 8);//�ܡ�A��B��C--0��1��2��3
  if(i EQ 0)
  {
    i = 3;
  }
  else
  {
    i --;
  }

  Bef_Mon = (INT8U) (PDI & 0x000000FF);

  Len = Read_His_VolStat_Data(Bef_Mon, (INT8U *) Pub_Buf, (INT8U *) Pub_Buf, sizeof(Pub_Buf)); 
  if(Len != sizeof(S_VolStat))
  {
    mem_set((INT8U *) Pub_Buf, 0, sizeof(S_VolStat), (INT8U *) Pub_Buf, sizeof(Pub_Buf));
    //ASSERT(0);
    //return 0;
  }
  p = (S_VolStat *) Pub_Buf;


  //����pָ��һ��S_VolStat��������
  Hex2Bcd(p ->Total_Time[i], pDst, 3, pDst_Start, DstLen);//���ʱ��
  Hex2Bcd(p ->Qual[i], pDst + 3, 3, pDst_Start, DstLen);  //�ϸ��� 
  Hex2Bcd(p ->Exam[i], pDst + 6, 3, pDst_Start, DstLen);  //������
  Hex2Bcd(p ->Upper_Time[i], pDst + 9, 3, pDst_Start, DstLen);  //������ʱ��
  Hex2Bcd(p ->Lower_Time[i], pDst + 12, 3, pDst_Start, DstLen);   //������ʱ��
  Hex2Bcd(p ->Max_Vol[i], pDst + 15, 2, pDst_Start, DstLen);    //��ߵ�ѹ
  Hex2Bcd_Buf(p ->Max_Vol_Time[i], 4, pDst + 17, pDst_Start, DstLen);//��ߵ�ѹ����ʱ�� 
  Hex2Bcd(p ->Min_Vol[i], pDst + 21, 2, pDst_Start, DstLen);    //��͵�ѹ
  Hex2Bcd_Buf(p ->Min_Vol_Time[i], 4, pDst + 23, pDst_Start, DstLen);//��͵�ѹ����ʱ�� 
  return 27;
}

INT16U Get_VolStat_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
   INT16U Len;
   
   OS_Mutex_Pend(PUB_BUF_SEM_ID);
   Len = _Get_VolStat_Proto_Data(PDI, pDst, pDst_Start, DstLen);
   OS_Mutex_Post(PUB_BUF_SEM_ID);
   
   return Len;
}
#undef VOLSTAT_PROTO_C