
#define EEPROM_PUCK
#include "Pub_PUCK.h"

/**********************************************************************************
�������ܣ�����buf������1/2/4�Լ���ѡ��ó�У���
��ڣ�
Src-------------Դbuf
SrcLen----------Դbuf���ֽڳ���
ByteGroup-------��1/2/4�Լ�Ϊ�������У���
Dst-------------Ŀ�껺����
DstLen-----------Ŀ�껺�������ֽڳ���
���ڣ�1---------���ɹ������Ƚ���ȷ;0--------��ʾʧ��
**********************************************************************************/
INT8U Get_Buf_MulitByte_Sum(INT8U *Src,INT16U SrcLen,INT8U ByteGroup,INT8U *Dst,INT8U DstLen)
{
  //INT8U Flag;
  INT8U temp1;
  INT16U i;
 
  /*
  Flag=ASSERT(A_WARNING,(ByteGroup==1)); 
  Flag|=ASSERT(A_WARNING,ByteGroup==DstLen);  
  Flag|=ASSERT(A_WARNING,(SrcLen%ByteGroup)==0);    
  */
  if(ByteGroup!=1 || ByteGroup!=DstLen || (SrcLen%ByteGroup)) //�����ֽ�
    Debug_Print("Get_Buf_MulitByte_Sum Function Error!");   

  
  temp1=0;
   for(i=0;i<SrcLen/ByteGroup;i++)
  {
    switch(ByteGroup)
    {
    case 1:
      temp1+=*(Src+i);
      break;
    case 2:
      break;
    case 4:
      break;
    }    
  }
  
  switch(ByteGroup)
  {
    case 1:
      *Dst=temp1;
      break;
    case 2:
      //mem_cpy(Dst,Dst,2,(INT8U *)(&temp2),2);
      break;
    case 4:
      //mem_cpy(Dst,Dst,4,(INT8U *)(&temp3),4);
      break;
  }    
  return 1;
}

/**********************************************************************************
�������ܣ���ȡ����
��ڣ�Flag-------1:��ʼ����0---------------������
���ڣ���
**********************************************************************************/	
INT8U Read_Storage_Data_PUCK(INT32U DI,void *pDst,INT16U RealLen)
{
  INT16U Len;
  
  Len=Read_Storage_Data(DI,pDst,pDst,RealLen);
  if((Len==0)||(Len!=RealLen))
  {
    Debug_Print("Get Data _Error----->0X%lx",DI); 
    ASSERT_FAILED();
    return 0;
  }
  
  mem_cpy(pDst,pDst,Len,pDst,Len);
  return 1;
}
/**********************************************************************************
�������ܣ����ICУ�������ʵ��ʹ�õ�У�����У����Ƿ���ȷ��
��ڣ���
���ڣ�
CS_IC_EPPROM_GEIFAILED---�ڿ�CS��IC��CS����ȡʧ��,CSҲ���,CS����
CS_IC_GET_FAILED---------����IC������ȡʧ�ܣ�CS��Ч��
CS_EPPROM_GET_FAILED-----�ڿ�������ȡʧ�ܣ�CS��Ч��
CS_IC_EPPROM_NO_EQUAL------CS����ȡ�ɹ�������2�߲����,���ڿ�Ϊ׼��
CS_IC_EPPROM_EQUAL-------�ڿ�CS��IC��CS����ȡ�ɹ�,CSҲ���
**********************************************************************************/
INT8U Chk_IC_User_ParaSum(void)
{
  INT8U Flag1,Flag2;
  INT32U CS_User,CS_IC;
  
  Flag1=Get_IC_ParaSum3(&CS_IC);
  Flag2=Get_User_All_ParaSum3(&CS_User);
  
  if((!Flag1)&&(!Flag2))
  {
    Debug_Print("Measure_Error----->IC Cs And Epprom Para Read Error");
    return CS_IC_EPPROM_GEIFAILED;
  }
  
  if((!Flag1)&&(Flag2))
  {
    Debug_Print("Measure_Error----->IC Cs Read Error!");
    return CS_IC_GET_FAILED;
  }
  
  if((Flag1)&&(!Flag2))
  {
    Debug_Print("Measure_Error----->IC Cs And Epprom Para Read Error");
    return CS_EPPROM_GET_FAILED;
  }
  
  if(CS_IC==CS_User)
  {
    MeasuPara_CS.IC_Cs=CS_IC;
    MeasuPara_CS.EppRom_Cs=CS_IC;
    SET_STRUCT_SUM(MeasuPara_CS);
    Debug_Print("Measure_Info----->IC Cs And Epprom Para Read All OK");
    return CS_IC_EPPROM_EQUAL;
  }
  
  Debug_Print("Measure_Error----->IC Cs And Epprom Cs Read OK,But Not Equal");
  return CS_IC_EPPROM_NO_EQUAL;
}
