#define PUB_C
#include "includes.h"
#include "OS_Port.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H26"
#endif

//���BCD���ݻ������������Ƿ���BCD��,��BCD�Ļ������򷵻�1�����򷵻�0
INT8U Check_BCD_Data(void* pBCD, INT16U Len)
{
  INT16U i;
  INT8U* p;

  p = (INT8U *) pBCD;

  for(i = 0; i < Len; i++)
  {
    if(!((p[i] & 0x0F) < 0x0A && (p[i] & 0xF0) < 0xA0))
    {
      return 0;
    }
  }
  return 1;
}

/*
//memcpy����
//pDst��ʾĿ�껺����
//pSrc��ʾԴ������
//SrcLen��ʾ��������
//pDst_Start��DstLenһ������pDst��SrcLen�ķ�Χ
//��������ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SrcLen<=(INT8U *)pDst_Start+DstLen);
void mem_cpy(void *pDst,void *pSrc,INT32U SrcLen,void *pDst_Start,INT32U DstLen)
{
  ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SrcLen<=(INT8U *)pDst_Start+DstLen);//pDst�������������
  memcpy(pDst,pSrc,SrcLen);
}

//memset����
//pDst��ʾĿ�껺����
//Value��ʾ��Ҫ���õ�ֵ
//SetLen��ʾ��������
//pDst_Start��DstLenһ������pDst��SetLen�ķ�Χ
//��������ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SetLen<=(INT8U *)pDst_Start+DstLen);
void mem_set(void *pDst, INT8U Value,INT32U SetLen,void *pDst_Start,INT32U DstLen)
{
  ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+SetLen<=(INT8U *)pDst_Start+DstLen);//pDst�������������
  memset(pDst,Value,SetLen);
}

//ͨ�ü��У��ͺ���
//pSrc��ʾ��Ҫ�������ݻ�����
//SrcLen��ʾ���ݻ���������
//pCS��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//ע�⣺�������Ҫ��Set_Sum�ɶ�ʹ�ã���Ϊ�ڲ����Ǽ���򵥵�У���
INT8U Check_Sum(void *pSrc,INT16U SrcLen,void *pCS,INT8U CS_Bytes)
{
  INT16U i;
  INT32U Sum=0;
  
  ASSERT(CS_Bytes==1 || CS_Bytes==2 || CS_Bytes==4);
  for(i=0;i<SrcLen;i++)
  {
  Sum+=*((INT8U *)pSrc+i); 
  }
  
  Sum=Sum^0xAAAAAAAA;//���м򵥱任,ĳЩλȡ��
  if(memcmp(&Sum,pCS,CS_Bytes)==0)
  return 1;
  else
  return 0;
}

//ͨ������У��ͺ���
//pSrc��ʾ��Ҫ����У��͵����ݻ�����
//SrcLen��ʾ���ݻ���������
//pDst��ʾУ��͵���ʼ��ַ
//CS_Bytes��ʾУ��ͳ���
//pDst_Start��pDst��Χ���޶�
//DstLen��pDst��Χ���޶�,
//��Ҫ����ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+CS_Bytes<=(INT8U *)pDst_Start+DstLen);
//�������Ҫ��Check_Sum�ɶ�ʹ�ã���Ϊ���ɵ�У�鲻�Ǽ򵥵�У��ͣ����ǽ����˼򵥵ı任
void Set_Sum(void *pSrc,INT16U SrcLen,void *pDst,INT8U CS_Bytes,void *pDst_Start,INT16U DstLen)
{
  INT16U i;
  INT32U Sum=0;
  
  ASSERT(CS_Bytes==1 || CS_Bytes==2 || CS_Bytes==4);
  ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+CS_Bytes<=(INT8U *)pDst_Start+DstLen);
  
  for(i=0;i<SrcLen;i++)
  {
  Sum+=*((INT8U *)pSrc+i); 
  }
  
  Sum=Sum^0xAAAAAAAA;//���м򵥱任,ĳЩλȡ��
  mem_cpy(pDst,&Sum,CS_Bytes,pDst_Start,DstLen);
}

//���ĳ���ṹ���У����Ƿ���ȷ,�ýṹ��Ķ�������������·�ʽ
//
//typedef struct{
//     ...
//     ...
//     INT8U CS[CS_BYTES];//���һ���������У��ͣ��ҳ���ΪCS_BYTES
//    }sturct_name;
//
//pSrcΪ�ṹ���������ʼָ��
//SrcLenΪ�ṹ���������
//CSΪ�ṹ�������У���,ע��ñ�������Ϊ�ṹ���е�һ����
//ע�⣺�������Ҫ��Set_STRUCT_Sum�ɶ�ʹ�ã���ΪУ������㷨һ��
INT8U Check_STRUCT_Sum(void *pSrc,INT16U SrcLen,INT8U CS[])
{
  INT32U Sum;
  INT16U i;
  
  Sum=0;
  i=0;
  ASSERT(CS>(INT8U *)pSrc && CS+CS_BYTES<=(INT8U *)pSrc+SrcLen);//�ж�CS��λ���Ƿ�Ϸ�
  while(((INT8U *)pSrc+i)!=CS)//����У���
  {
  Sum+=*((INT8U *)pSrc+i);
  i++;  
  }
  
  Sum=Sum^0xAAAAAAAA;//���м򵥱任,ĳЩλȡ��
  if(memcmp(&Sum,CS,CS_BYTES)==0)//�Ƚ�У���
  return SYS_TRUE;
  else
  return SYS_FALSE;
}

//���ýṹ�������У���,�ýṹ��Ķ�������������·�ʽ
//
//typedef struct{
//     ...
//     ...
//     INT8U CS[CS_BYTES];//���һ���������У��ͣ��ҳ���ΪCS_BYTES
//    }sturct_name;
//
//pSrcΪ�ṹ���������ʼָ��
//SrcLenΪ�ṹ���������
//CSΪ�ṹ�������У���,ע��ñ�������Ϊ�ṹ���е�һ����
//ע�⣺�������Ҫ��Check_STRUCT_Sum�ɶ�ʹ�ã���ΪУ������㷨һ��
void Set_STRUCT_Sum(void *pSrc,INT16U SrcLen,INT8U CS[])
{
  INT32U Sum;
  INT16U i;

  Sum=0;
  i=0;
  ASSERT(CS>(INT8U *)pSrc && CS+CS_BYTES<=(INT8U *)pSrc+SrcLen);//�ж�CS��λ���Ƿ�Ϸ�
  while(((INT8U *)pSrc+i)!=CS)//����У���
  {
  Sum+=*((INT8U *)pSrc+i);
  i++;  
  }
  
  Sum=Sum^0xAAAAAAAA;//���м򵥱任,ĳЩλȡ��
  mem_cpy(CS,&Sum,CS_BYTES,pSrc,SrcLen);
}
*/

//�޷�������Hex��BCD��ת��
//Data��ʾԴ����
//pDst��ʾĿ�����ݻ�����
//Len��ʾ��Ҫת������BCD���ֽ���
//pDst_Start��DstLenһ������pDst��Len�ķ�Χ��������:
//ASSERT(pDst>=pDst_Start && pDst+Len<=pDst_Start+DstLen);
void Hex2Bcd(INT32U Data, INT8U* pDst, INT16U Len, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Temp, i;

  if(!(pDst >= pDst_Start && pDst + Len <= pDst_Start + DstLen))//�ж��ڴ�����ĺϷ���
  {
    ASSERT_FAILED();
    return;
  }
  
  i = 0;
  mem_set(pDst, 0, Len, pDst_Start, DstLen);//�û�����Ϊ0
  while(Data != 0 && i < Len)
  {
    Temp = (INT8U) (Data % 10);
    pDst[i] |= Temp;
    Temp = (INT8U) ((Data / 10) % 10);
    pDst[i] |= (Temp << 4);
    Data = Data / 100;
    i++;
  }
}

//�з�������Hex��BCD��ת��
//Data��ʾԴ����
//pDst��ʾĿ�����ݻ�����
//Len��ʾ��Ҫת������BCD���ֽ���
//pDst_Start��DstLenһ������pDst��Len�ķ�Χ��������:
//ASSERT(pDst>=pDst_Start && pDst+Len<=pDst_Start+DstLen);
void S_Hex2Bcd(INT32S Data, INT8U* pDst, INT16U Len, INT8U* pDst_Start, INT16U DstLen)
{
  INT8U Temp, i;
  INT8U S_Flag = 0;

  if(!(pDst >= pDst_Start && pDst + Len <= pDst_Start + DstLen))//�ж��ڴ�����ĺϷ���
  {
    ASSERT_FAILED();
    return;
  }
  
  i = 0;
  if(Data < 0)
  {
    Data = 0 - Data;
    S_Flag = 1;//Դ�����Ǹ���
  }

  mem_set(pDst, 0, Len, pDst_Start, DstLen);//�û�����Ϊ0
  while(Data != 0 && i < Len)
  {
    Temp = Data % 10;
    pDst[i] |= Temp;
    Temp = (Data / 10) % 10;
    pDst[i] |= (Temp << 4);
    Data = Data / 100;
    i++;
  }
  if(1 EQ S_Flag)
  {
    *(pDst + Len - 1) |= 0x80;
  }//���λ��1��ʾ�Ǹ���
}

//BCDת��Ϊ�з����������λΪ����λ
INT32S S_Bcd2Hex(INT8U Src[], INT8U SrcLen)
{
  INT32S S_Data;
  INT8U Sign = 0, Temp;

  Temp = Src[SrcLen - 1];
  if((Src[SrcLen - 1] & 0x80) != 0)//�Ƿ��Ǹ���?
  {
    Sign = 1;
  }

  Src[SrcLen - 1] = Src[SrcLen - 1] & 0x7F;//�����λ��Ϊ0

  S_Data = (INT32S) Bcd2Hex(Src, SrcLen);
  if(Sign EQ 1)
  {
    S_Data = 0 - S_Data;
  }
  Src[SrcLen - 1] = Temp;

  return S_Data;
}

//�޷��ŵ�BCD��HEX��ת��
//SrcΪBCD������
//SrcLen��ʾBCD�������ĳ���,SrcLen����<=5��Ҳ����BCD���ݱ���С��0x9999999999
//����ֵ��ʾת�����HEXֵ
INT32U Bcd2Hex(INT8U Src[], INT8U SrcLen)
{
  INT32U Data, i;
  INT8U Re;

  if(SrcLen > 5)//�ж�SrcLen�ĺϷ���
    ASSERT_FAILED();
  Re = Check_BCD_Data(Src, SrcLen);
  if(Re EQ 0)//���BCD���ݵĺϷ���
    ASSERT_FAILED();
    
  Data = 0;
  i = 0;
  while(i < SrcLen)
  {
    Data = Data * 100;
    Data += (Src[SrcLen - i - 1] & 0x0F) + ((Src[SrcLen - i - 1] & 0xF0) >> 4) * 10;
    i++;
  }
  return Data;
}

//�ֽ�Hex2Bcdת��
INT8U Hex2Bcd_Byte(INT8U Byte)
{
  if(Byte >= 100)
    ASSERT_FAILED();
  
  return (Byte % 10) + ((Byte / 10) << 4);
}

//�ֽ�Hex2Bcdת��
INT8U Bcd2Hex_Byte(INT8U Byte)
{
  INT8U Re;
  Re = Check_BCD_Data(&Byte, 1);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  return (Byte & 0x0F) + ((Byte & 0xF0) >> 4) * 10;
}

//��������Hex2Bcdת��
void Hex2Bcd_Buf(void* pSrc, INT16U SrcLen, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U i;
  
  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + SrcLen <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return;
  }
  
  for(i = 0; i < SrcLen; i++)
  {
    *((INT8U *) pDst + i) = Hex2Bcd_Byte(*((INT8U *) pSrc + i));
  }
}

//��������Hex2Bcdת��
void Bcd2Hex_Buf(void* pSrc, INT16U SrcLen, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U i;

  if(!((INT8U *) pDst >= (INT8U *) pDst_Start && (INT8U *) pDst + SrcLen <= (INT8U *) pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return;
  }
  
  for(i = 0; i < SrcLen; i++)
  {
    *((INT8U *) pDst + i) = Bcd2Hex_Byte(*((INT8U *) pSrc + i));
  }
}

//����BCD����
//pData0ָ���һ��BCD���Ļ�����
//pData1ָ��ڶ���BCD���Ļ�����
//pDstָ��Ŀ�껺����,���pData0-pData1=pDst
//Len��ʾBCD����ֽ���
//pDst_Start��DstLenһ���޶�pDst��Len�ķ�Χ
void Bcd_Dec(INT8U Type, INT8U* pData0, INT8U* pData1, INT8U Len, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT32U Data0, Data1;
  INT32S S_Data0, S_Data1;

  if(Type EQ S_INTU)
  {
    Data0 = Bcd2Hex(pData0, Len);
    Data1 = Bcd2Hex(pData1, Len);

    if(Data0 >= Data1)//
    {
      Hex2Bcd(Data0 - Data1, pDst, Len, pDst_Start, DstLen);
    }
    else
    {
      ASSERT_FAILED();
      Hex2Bcd(0, pDst, Len, pDst_Start, DstLen);
    }
  }
  else if(Type EQ S_INTS)
  {
    S_Data0 = S_Bcd2Hex(pData0, Len);
    S_Data1 = S_Bcd2Hex(pData1, Len);

    S_Hex2Bcd(S_Data0 - S_Data1, pDst, Len, pDst_Start, DstLen);
  }
  else
  {
    ASSERT_FAILED();
  }
}

INT8U Get_Array_Bit(INT8U Src[], INT8U Bit)
{
  return GET_BIT(Src[Bit / 8], Bit % 8);
}

/*****************************************
����ԭ�ͣ�INT8U GetBufSum_Pub(INT8U Src[],INT16U Src_Len)
�������ܣ���ȡbuf �ĵ��ֽ��ۼӺ�
��ڲ�����Src,Դ��������ʼָ��
   Src_Len,Դ���ݵĳ���
���ڲ�����0��У��ʹ���1��У�����ȷ
******************************************/
INT8U GetBufSum_Pub(INT8U Src[], INT16U Src_Len)
{
  INT8U ResultSum;
  INT16U i;

  for(ResultSum = 0,i = 0; i < Src_Len; i++)
  {
    ResultSum += Src[i];
  }  

  return ResultSum;
}

INT32U Sum_4Bytes(INT8U Src[], INT16U SrcLen)
{
  INT32U CS = 0;
  INT16U i;

  for(i = 0; i < SrcLen; i ++)
  {
    CS += Src[i]; 
  }
  return CS;
}

OS_INT8U _Check_STRUCT_Sum(void *pSrc,OS_INT8U *pCS)
{
  
  return 1;
}

void _Set_STRUCT_Sum(void *pSrc,OS_INT8U *pCS)
{
  
  
}

#undef PUB_C
