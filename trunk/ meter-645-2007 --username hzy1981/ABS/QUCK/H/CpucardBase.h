
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
INT8U Convert_Dis_Code(void);
INT8U GetCardKind(void);
#define GetCardKind() (CardType)
//INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
 void PrintErrState(void );
void My_Memcpy(INT8U *pDst,INT8U *pSrc,INT8U length);
/*"��ԭ����ǰ���õظ��Ƶ�Ŀ������"*/
void My_memcpyRev(INT8U *to,INT8U *from,INT8U len);
/*"������ǰ����"*/
void Reverse_data(INT8U *data, INT16U len);
INT8U Judge_Return_Flag(void);
INT8U My_Memcmp(INT8U *to,INT8U *from,INT8U lc);// if(My_Memcmp(receive_send_buffer+110,receive_send_buffer,8))  
void CPU_ESAM_CARD_Control(INT8U Direct);//����ѡ�� �Ƿ���esam����cpu��

INT8U Internal_Auth(INT8U,INT8U,INT8U,INT8U,INT8U,INT8U *);
                                               /*" �ڲ���������� "*/
INT8U External_Auth(INT8U ,INT8U ,INT8U *);
                                               /*" �ڲ���������� "*/
INT8U Select_File(INT8U ,INT8U ,INT8U );
                                               /*" �ļ�ѡ���������ѡ��ESAM��CPU���е�ĳ���ļ� "*/
                                               /*" �����д����� "*/
INT8U Read(INT8U ,INT8U ,INT8U ,INT8U ,INT8U );
                                               /*" �ڲ���������� "*/
INT8U Write(INT8U,INT8U,INT8U,INT8U,INT8U,INT8U *);
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
INT8U  CPU_Card_Driver(const INT8U *Order_Head,
						     INT8U Length_LC,
			                             INT8U *W_Data,
			                             INT8U Length_LE,
			                             INT8U Change_Door,
			                             INT8U Spec_Length_LE);
/*"**************************************************************************"*/
/*" �жϿ��Ƿ��� "*/
#define Check_Cpu_Card_Out() ((JUDGE_CPU_INSERT)?(OK):(ERR))
/*"**********************************************************************************"*/

/*"**************************************************************************"*/
/*" ���ա��ж�CPU����λӦ���ź� "*/
INT8U Cpucard_Reset(void);
	
/*"**************************************************************************"*/
/*"���ա��ж�SAM����λӦ���ź�"*/                                                                  
INT8U Esamcard_Reset(void);

INT8U  WhenCardInsertedInitPrePayData(void);//�ϵ��e����ȡ���ݵ�ȫ�ֱ���
 

#endif
