
#ifndef CTRL_CODE_0X14_SETDATA_H_
#define CTRL_CODE_0X14_SETDATA_H_
 
//д����ʱ��esamȨ���жϺ����Ľ���
//TypeΪ1��2���ֱ��ʾ1�����ݺ�2������
//pSrc��ʾͨ��Э���е������� N1-Nm + 4�ֽ�MAC�����Э������
//SrcLen��ʾԴ���ݳ���
//pDst��ʾ���ܺ�����ݻ���������TypeΪ1ʱ����Ҫ���ܣ���˴�ʱ�ò���������
//pDst_StartĿ�껺����ʼ��ַ
//DstLen Ŀ�껺�����ĳ���
//����ֵ Ȩ����ȷ�ҽ��ܳɹ�����1�����򷵻�0
//ע�⣺�ú��������pSrc��pDst������ͬһ��ַ��
INT8U  Esam_Auth_Check(  INT8U *pSrc, INT16U SrcLen, INT8U * DstLen);
 INT8U Set_Esam_Para( INT8U *pSrc, INT8U SrcLen); 


#endif