#ifndef PUB_ERR_H
#define PUB_ERR_H




/*
#define NO_ERR 1

#define PROTOCOL_PSW_ERR (NO_ERR+0x01)    //Э�������
#define PROTOCOL_AUTH_ERR (PROTOCOL_PSW_ERR+0x01)   //Э��Ȩ�޴�
#define PROTOCOL_DATA_ERR (PROTOCOL_AUTH_ERR+0x01)   //Э��Ƿ�����
#define PROTOCOL_DI_ERR (PROTOCOL_DATA_ERR+0x01)   //Э�����ݱ�ʶ��

//#define YEAR_PERIOD_ERR 0x05     //��ʱ������
#define PHY_MEM_ERR (PROTOCOL_DI_ERR+0x01)
#define LOG_MEM_MAP_ERR (PHY_MEM_ERR+0x01)     //�ڴ�ӳ���
#define IMP_DATA_STORAGE_ERR (LOG_MEM_MAP_ERR+1)   //IMP���ݴ洢����
#define PROTOCOL_DATA_STORAGE_ERR (IMP_DATA_STORAGE_ERR+1) //Э�����ݵĴ洢����

#define LOG_MEM_ADDR_ERR (PROTOCOL_DATA_STORAGE_ERR+0x01) //�߼��洢����ַ��
#define PHY_MEM_ADDR_ERR (LOG_MEM_ADDR_ERR+0x01)  //����洢����ַ��

//#define RD_LOG_MEM_ERR (PHY_MEM_ADDR_ERR+0x01)
//#define WR_LOG_MEM_ERR (RD_LOG_MEM_ERR+0x01)

//#define RD_PHY_MEM_ERR (WR_LOG_MEM_ERR+0x01)
//#define WR_PHY_MEM_ERR (RD_PHY_MEM_ERR+0x01)

#define LOG_MEM_NO_ERR   (PHY_MEM_ADDR_ERR+0x01)  //�߼��洢����Ŵ�
#define PHY_MEM_NO_ERR   (LOG_MEM_NO_ERR+0x01)    //����洢����Ŵ�

#define RD_IMP_DATA_CS_ERR  (PHY_MEM_NO_ERR+0x01)    //���洢������У��ʹ�
#define RD_IMP_DATA_ERR  (RD_IMP_DATA_CS_ERR+0x01)     //��ȡIMP����ʧ��,�κ�һ��logmem��û�гɹ�����������
#define WR_IMP_DATA_ERR  (RD_IMP_DATA_ERR+0x01)    //дIMPʧ�ܣ��κ�һ��logmem��û��д�ɹ�������

#define RD_FIX_DATA_ERR (WR_IMP_DATA_ERR+0x01) //��ȡ�̶����ݳ��ȴ���
#define WR_FIX_DATA_ERR (RD_FIX_DATA_ERR+0x01) //д�̶����ݳ��ȴ���

#define RD_HIS_DATA_LEN_ERR (WR_FIX_DATA_ERR+0x01)  //��ȡ��ʷ�����ǵĴ���
#define RD_HIS_DATA_DI_ERR  (RD_HIS_DATA_LEN_ERR+0x01)     
#define RD_HIS_DATA_TIME_ERR (RD_HIS_DATA_DI_ERR+0x01)
#define RD_HIS_DATA_DATA_ERR (RD_HIS_DATA_TIME_ERR+0x01)

#define WR_HIS_DATA_LEN_ERR (RD_HIS_DATA_DATA_ERR+0x01) //д��ʷ����ʱ�Ĵ���
#define WR_HIS_DATA_DI_ERR  (WR_HIS_DATA_LEN_ERR+0x01)
#define WR_HIS_DATA_TIME_ERR (WR_HIS_DATA_DI_ERR+0x01)

#define RD_STORAGE_DATA_DI_ERR (WR_HIS_DATA_TIME_ERR+0x01) //���洢����ʱ�Ĵ���
#define WR_STORAGE_DATA_DI_ERR (RD_STORAGE_DATA_DI_ERR+0x01) //д�洢����ʱ�Ĵ���
#define WR_STORAGE_DATA_LEN_ERR (WR_STORAGE_DATA_DI_ERR+0x01)
#define WR_STORAGE_DATA_AUTH_ERR (WR_STORAGE_DATA_LEN_ERR+0x01)//д����Ȩ�޴���

#define WR_LOAD_DATA_ERR (WR_STORAGE_DATA_AUTH_ERR+0x01) //д�����������ݸ�ʽ����
#define RD_LOAD_DATA_ERR (WR_LOAD_DATA_ERR+0x01)

#define EVENT_ID_ERR (RD_LOAD_DATA_ERR+0x01)//�¼���ID����
#define EVENT_DATA_ERR (EVENT_ID_ERR+0x01)

#define ADJ_TIME_ERR (EVENT_DATA_ERR+1)
*/
#endif

