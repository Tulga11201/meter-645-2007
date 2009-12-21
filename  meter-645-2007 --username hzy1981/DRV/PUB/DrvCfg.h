#ifndef DRV_PUB_H
#define DRV_PUB_H



#ifndef DRV_CFG
#define DRV_CFG_EXT  extern volatile
#else
#define DRV_CFG_EXT  volatile
#endif

//#define RESUME_REMOTER_EN     RESUME_REMOTER_EN       //1�����⻽�Ѻ�ң�������ܴ򿪣�0�����⻽�Ѻ�ң�������ܹرա�
#define RSUME_CLOCK_DIV         CG_CPUCLK_MAIN0        //CG_CPUCLK_MAIN0       //����ģʽ�£��ⲿ����ķ�Ƶϵ��,Ŀǰֻ���� CG_CPUCLK_MAIN0��CG_CPUCLK_MAIN1

#define LVI_DETECT_EN        //�꿪������LVI����


  #define ID_MEM_IIC_U10 0     //�꿪�����򿪸�EPPROM�Ķ�д����:
  #define ID_MEM_IIC_U11 1     //�꿪�����򿪸�EPPROM�Ķ�д����
  #define ID_MEM_IIC_U12 2     //�꿪�����򿪸�EPPROM�Ķ�д����
  #define ID_MEM_IIC_U14 3     //�꿪�����򿪸�EPPROM�Ķ�д����
#ifdef FM_ROM_FM16_EN          //ģ�� FM16
  #define ID_MEM_FM24C16 4     //�꿪�����򿪸�EPPROM�Ķ�д����
#else                          //ģ�� FM64
  #define ID_MEM_IIC_U15 4     //�꿪�����򿪸�EPPROM�Ķ�д���ܣ�ע�⣬�˿���ģ���
#endif
//#define ID_MEM_24C04 5     //�꿪�����򿪸�EPPROM�Ķ�д���ܣ�ע�⣬�˿���ģ���


#ifdef ID_MEM_FM24C16
#define  MAX_EPPROM_NUM (ID_MEM_FM24C16+1)
#else
#define  MAX_EPPROM_NUM (ID_MEM_IIC_U15+1)
#endif



#define I2C_SOFT_EPP_EN    //�꿪������I2C�����ģ�⹦��


//�������ڿ����ñ�
enum EPP_ROM_TYPE{   
  M2401,M2402,M2404,M2408,M2416,M2432,M2464,M24128,M24256,M24512
//128�� 256�� 512�� 1024��2048, 4096, 8192, 16384, 32768, 65536
};

#define EPP_2401_SIZE 128
#define EPP_2402_SIZE 256
#define EPP_2404_SIZE 512
#define EPP_2408_SIZE 1024
#define EPP_24016_SIZE 2048
#define EPP_24032_SIZE 4096
#define EPP_24064_SIZE 8192
#define EPP_240128_SIZE 16384
#define EPP_240256_SIZE 32768
#define EPP_240512_SIZE 65536


#ifdef ID_MEM_IIC_U10       //24LC256I/SM SOIC8 -40�桫85��
#define U10_TYPE            M24512
#define U10_SIZE            EPP_240512_SIZE
#define U10_Slvadr          0xa2
#endif

#ifdef ID_MEM_IIC_U11      //24LC256I/SM SOIC8 -40�桫85��
#define U11_TYPE            M24512
#define U11_SIZE            EPP_240512_SIZE
#define U11_Slvadr          0xa4
#endif

#ifdef ID_MEM_IIC_U12      //24LC256I/SM SOIC8 -40�桫85��
#define U12_TYPE            M24512
#define U12_SIZE            EPP_240512_SIZE
#define U12_Slvadr          0xa6
#endif

#ifdef ID_MEM_IIC_U14      //M24C04 SOP8 -40�桫85��,Oxac,��256�ֽڣ�0xae,��256�ֽڣ�
#define U14_TYPE            M2404
#define U14_SIZE            EPP_2404_SIZE
#define U14_Slvadr          0xac
#endif

#ifdef ID_MEM_IIC_U15      //FM24C64-S SOP8 -40�桫85��
#define U15_TYPE            M2464
#define U15_SIZE            EPP_24064_SIZE
#define U15_Slvadr          0xa8
#endif


#ifdef  ID_MEM_FM24C16       //M24C016 SOP8 -40�桫85��,Oxa0,��256�ֽڣ�0xa2,��256�ֽڣ�
#define U16_TYPE            M2416
#define U16_SIZE            EPP_24016_SIZE
#define U16_Slvadr          0xa0
#endif

#ifdef  ID_MEM_24C04       //M24C04 SOP8 -40�桫85��,Oxa0,��256�ֽڣ�0xa2,��256�ֽڣ�
#define U04_TYPE            M2404
#define U04_SIZE            EPP_2404_SIZE
#define U04_Slvadr          0xa0
#endif



#endif
