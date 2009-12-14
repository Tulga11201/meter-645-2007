
#ifndef CPUCARD_BASE_H__
#define CPUCARD_BASE_H__
/**********************************************************************************
�������ܣ��� CPU��,ESAM�ĵײ����,����OPERATE_RST_COOL��.
��ڣ�
          Type------------CPU��,ESAM������;
          Operate---------��� CPU��,ESAM�Ĳ�����������,�� OPERATE_RST_COOL ��;
          pDst------------�� CPU��,ESAM�Ĳ�����,��ȡ���������ݷ��û�����; 
                          ���� PAY_CPU_CARD���临λ������8�ֽڵ���ɢ���ӡ�
                          �����������ʵ��������Ͳ��������޷������ݣ����ڰ������ӡ�
          pDstStart-------�� CPU��,ESAM�Ĳ�����,��ȡ���������ݷ��û�����ͷ��ַ,��pDst,MaxDstLenһ���޶�Խ��. 
          MaxDstLen-------pDstStartĿ�껺������������󳤶�.
���ڣ� CPU,ESAM������.
**********************************************************************************/ 
//INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
 void PrintErrState(void );
void My_Memcpy(INT8U *pDst,INT8U *pSrc,INT8U length);
/*"��ԭ����ǰ���õظ��Ƶ�Ŀ������"*/
void My_memcpyRev(unsigned char *to,unsigned char *from,unsigned char len);
/*"������ǰ����"*/
void Reverse_data(unsigned char *data, unsigned int len);
unsigned char Judge_Return_Flag(void);
unsigned char My_Memcmp(unsigned char *to,unsigned char *from,unsigned char lc);// if(My_Memcmp(receive_send_buffer+110,receive_send_buffer,8))  
void CPU_ESAM_CARD_Control(INT8U Direct);//����ѡ�� �Ƿ���esam����cpu��

unsigned char Internal_Auth(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char *);
                                               /*" �ڲ���������� "*/
unsigned char External_Auth(unsigned char ,unsigned char ,unsigned char *);
                                               /*" �ڲ���������� "*/
unsigned char Select_File(unsigned char ,unsigned char ,unsigned char );
                                               /*" �ļ�ѡ���������ѡ��ESAM��CPU���е�ĳ���ļ� "*/
                                               /*" �����д����� "*/
unsigned char Read(unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char );
                                               /*" �ڲ���������� "*/
unsigned char Write(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char *);
                                               /*" �ڲ���������� "*/

/*"**************************************************************************"*/
/*" ���ܣ�CPU���ײ��д���� "*/
/*" �ļ�����CPU_Card_Driver "*/
/*" Order_Head������ͷ�� "*/
/*" ������CLA  INS  P1  P2  "*/
/*" Length_LC��д���ݳ���   "*/
/*" W_Data��д���� "*/
/*" Length_LE: �����ݳ��� "*/
/*" Change_Door: ��дͨ�� ESAM����CPU "*/
/*" Spec_Length_LE: ����� ��������֡����,0:��ʾ�����ⳤ�ȣ�ֱ��ȡ61 XX,"*/
/*" ��0��ʾΪ�����������֡����ȡ61 XX "*/
INT8U  CPU_Card_Driver(const unsigned char *Order_Head,
						     unsigned char Length_LC,
			                             unsigned char *W_Data,
			                             unsigned char Length_LE,
			                             unsigned char Change_Door,
			                             unsigned char Spec_Length_LE);
/*"**************************************************************************"*/
/*" �жϿ��Ƿ��� "*/
INT8U Check_CPU_Occur(void);
/*"**********************************************************************************"*/

/*"**************************************************************************"*/
/*" ���ա��ж�CPU����λӦ���ź� "*/
unsigned char Cpucard_Atr(void);
	
/*"**************************************************************************"*/
/*"���ա��ж�SAM����λӦ���ź�"*/                                                                  
unsigned char Esamcard_Atr(void);

INT8U  WhenCardInsertedInitPrePayData(void);//�ϵ��e����ȡ���ݵ�ȫ�ֱ���
INT16U C_Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen);
   

#endif
