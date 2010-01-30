#define PUB_PUCK_C
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "AD"
#endif

/**********************************************************************************
�������ܣ�ȡ3�����������
��ڣ�3��
���ڣ����
**********************************************************************************/
INT32U Get_Max_Num(INT32U a,INT32U b,INT32U c)
{
			
      if((a>=b)&&(a>=c))	return a;
      if((b>=a)&&(b>=c))	return b;
            
      return c;
}
/**********************************************************************************
�������ܣ�ȡ3�����������
��ڣ�3��
���ڣ����
**********************************************************************************/
INT32U Get_Min_Num(INT32U a,INT32U b,INT32U c)
{
			
      if((a<=b)&&(a<=c))	return a;
      if((b<=a)&&(b<=c))	return b;
      
      return c;
}
/********************************************************************************

INT8U Get_RemoteCtrlKey_PUCK(INT8U Id);
�������ܣ�ң�����ļ�ֵ��
��ڣ�Id -----ֻ����дLUCK��������Ч����
���أ�0~255�����������˵����
********************************************************************************/
INT8U Get_RemoteCtrlKey_PUCK(INT8U Id)
{
  return 1;  
}
/********************************************************************************
INT8U Get_Curr_ComType_PUCK(INT8U Id);
�������ܣ���ȡ��ǰ��ͨ��ͨ�����ͣ�
��ڣ�ID-----ֻ����дLUCK��������Ч��
���أ�
Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
1����ʾ��ͨ��������ͨ��;0����ʾ��ͨ��������ͨ��
����	����	����	ң����	GPRSģ��	��1·485ͨ��	��1·485ͨ��	����ͨ��
ע�⣺����������״̬��

********************************************************************************/
INT8U Get_Curr_ComType_PUCK(INT8U Id)
{  
  INT8U i;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
  {
    if(Chanel_Para[i].ExitFlag)
    {
      Chanel_Para[i].ExitFlag++;
      if(Chanel_Para[i].ExitFlag>=SECOND_2(3))
      {
        Chanel_Para[i].ExitFlag=0;  
      }
      if(i==CHANEL_IRDA)
      {
        START_LIGHT_ON;
        Light_Mode=LIGHT_ON_IRDA;
      }
      SET_STRUCT_SUM(Chanel_Para[i]);
      return (1<<i);
    }
  }      
  return 0;  
  
}
/**********************************************************************************************
��������:SFLOAT BCD_To_Real_Convert(INT8U Src[],INT8U Src_Len,INT8U Decimal_Digits,INT8U Sign)
��������:����������ת��Ϊ��ʵ����
��ڲ���:Src,ԭʼ�������ݻ�����,BCD��!!!!!!!!!!
Src_Len,ԭʼ���ݳ���
Decimal_Digits,С��λ��
Sign,1��ʾ���ɷ�����,0��ʾ�޷�����
���ڲ���:��

FP32S BCD_To_Real_Convert(INT8U Src[],INT8U Src_Len,INT8U Decimal_Digits,INT8U Sign)
{
  INT8U i,Temp;//i��ʾ��������Src�ĵ�i��4λ,j��ʾ��¼����Src�ĵ�j���ֽ�
  
  FP32S Integral,Decimal,Result;
  
  Integral=0; //��¼�������ֵ�ֵ
  Decimal=0; //��¼С�����ֵ�ֵ
  
  for(i=0;i<Decimal_Digits;i++)
  {
    Temp=Src[i/2]; //��һ����ʱ����
    
    if(Sign==1 && i/2==Src_Len-1 ) //����������һ���ֽ������ɷ�����,���λΪ����λ
      Temp=Temp&0x7F;//�Ƚ�����λȥ��
    
    if(i%2==1) //������Ǹ�4λ
      Temp=Temp>>4;
    
    Decimal=Decimal/10; //ÿ����һλ����10,�ȼ���С������λ
    Decimal+=(FP32S)(Temp&0x0F)/10; //ÿ��ѭ��ȡ����λ��ΪС������һλ   		
    
  }
  
  for(i=0;i<Src_Len*2-Decimal_Digits;i++)//������������
  {
    Temp=Src[Src_Len-1-i/2]; //��һ����ʱ����
    
    if(Sign==1 && i/2==0) //����������һ���ֽ������ɷ�����,���λΪ����λ
      Temp=Temp&0x7F;//�Ƚ�����λȥ��
    
    if(i%2==0) //������Ǹ�4λ
      Temp=Temp>>4;
    
    Integral=Integral*10; //ÿ����һλ����10,�ȼ���С������λ      		
    Integral+=(FP32S)(Temp&0x0F); //ÿ��ѭ��ȡ����λ��Ϊ��λ    	
    
  }  
  Result=Integral+Decimal;//����������С��������ӵõ������
  
  if(Sign==1 && (Src[Src_Len-1] & 0x80)!=0) //������з�����,�����λΪ1,��ʾ�Ǹ���
    Result=0-Result;
  return Result;	
}
*******************************************************************************/

/***********************************************************************
�������ܣ����Src��Len�������ݣ�ȫ��Byte��ȣ�
��ڣ���
���ڣ�1------Src���ݶ���Byte��0--------��ȫ��
***********************************************************************/
INT8U CHeck_Same_Byte(INT8U *Src,INT8U Byte,INT16U Len)
{
  INT16U i;
  
  for(i=0;i<Len;i++)
  {
    if(Src[i]!=Byte)
      return 0;    
  }  
  return 1;   
}
void SYS_TimeDly_Sec(INT32U n)
{
#ifndef OS_DEBG_EN
  Delayn10MS(n*100);
#else
  OS_TimeDly_Sec(1);
#endif  
}

void SYS_TimeDly_Ms(INT32U n)
{  
#ifndef OS_DEBG_EN
  if(n<10)
    Delayn10MS(1);
  else
    Delayn10MS(n/10);
#else
  OS_TimeDly_Ms(n);
#endif  
}