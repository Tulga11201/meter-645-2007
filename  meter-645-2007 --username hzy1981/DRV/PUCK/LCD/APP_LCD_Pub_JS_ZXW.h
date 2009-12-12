#ifndef HTLCDPUB_JS_ZXW_h
#define HTLCDPUB_JS_ZXW_h

#ifndef HTLCDPUB_JS_ZXW_C
#define HTLCDPUB_JS_ZXW_EXT extern
#else
#define HTLCDPUB_JS_ZXW_EXT
#endif




#define MAX_SEG                 32                 //����SEG���:0~MAX_SEG
#define MAX_COL                 7                  //����COL���:0~MAX_COL



#define SEG(x)                  x                 //0~MAX_SEG
#define COM(y)                  y            //0~MAX_COL

#define Sx       1  
#define Dx       2  
#define Nx       3  


//��ʾ�豸��ʾ------Sx---------1~255
#define S_DANGQIAN             1         //��ǰ
#define S_SHANG                2         //��
#define S_SHIYUE               3         //1
#define S_YUE                  4         //��
#define S_CI                   5        //��
#define S_I1                   6        //I
#define S_I2                   7        //II
#define S_I3                   8        //III
#define S_V                    9        //IV
#define S_FAN                  10        //��
#define S_ZHENG                11        //��
#define S_XIANG                12        //��
#define S_WU                   13        //��
#define S_YOU                  14        //��
#define S_GONG                 15        //��
#define S_ZONG                 16        //��
#define S_FEIlLV               17        //����
#define S_XU                   18        //��
#define S_DIAN                 19        //��
#define S_LIANG                20        //��
#define S_XIANGXIAN2           21        //��2���޷���
#define S_XIANGXIAN1           22        //��1���޷���
#define S_XIANGXIAN4           23        //��4���޷���
#define S_XIANGXIAN3           24        //��3���޷���


#define S_COS                  25        //
#define S_FAI                  26        //
#define S_A                    27         //A
#define S_B                    28         //B
#define S_C                    29         //C
#define S_N                    30         //N
#define S_JIAN_DL             31        //�����
#define S_FENG_DL             32        //�����
#define S_PIN_DL             33        //ƽ����
#define S_GU_DL             34        //�ȵ���
#define S_RI_QI                35        //����
#define S_SHI1                 36        //ʧ
#define S_DIAN1                37        //��
#define S_YA                   38        //ѹ
#define S_LIU                  39        //��
#define S_SHIJIAN              40        //ʱ��
#define S_GONGLV               41        //����
#define S_DU                   42        //��
#define S_JIAN1                43        //��
#define S_FENG                 44        //��
#define S_PING                 45        //ƽ
#define S_GU                   46        //��
#define S_1                    47        //��
#define S_2                    48        //��
#define S_K1                   49        //��
#define S_K2                   50        //��
#define S_K3                   51        //��
#define S_TT                   52        //����
#define S_Ua_UP                53        //Ua������
#define S_Ub_UP                54        //Ub������

#define S_M_55                 55        //MVKWHz
#define S_M_56                 56        //MVKWH
#define S_M_57                 57        //MVKWHz
#define S_M_58                 58        //MVKWHz
#define S_M_59                 59        //MVKWHz
#define S_M_60                 60        //MVKWHz
#define S_M_61                 61        //MVKWHz
#define S_M_62                 62        //MVKWHz
#define S_M_63                 63        //MVKWHz
#define S_M_64                 64        //MVKWHz
#define S_M_65                 65        //MVKWHz
#define S_M_66                 66        //MVKWHz
#define S_M_67                 67        //MVKWHz
#define S_M_68                 68        //MVKWHz
#define S_M_69                 69        //MVKWHz

#define S_Uc_UP                70        //Uc������
#define S_UPCOVERP             71        //�϶˸�
#define S_DOWNCOVERP           72        //�¶˸�
#define S_RS1                  73        //
#define S_RS2                  74        //
#define S_HONGWAI              75        //����
#define S_NIXIANGXU            76        //������
#define S_Ua                   77        //Ua
#define S_Ua_DOWN              78        //Ua������
#define S_Ub                   79        //Ub
#define S_Ub_DOWN              80        //Ub������
#define S_Uc                   81         //Uc
#define S_Uc_DOWN              82        //Uc������
#define S_BUTTON               83       //���
#define S_LOCK                 84       //�������
#define S_LIGHT                85     //����
#define S_SHOT                 86     //�̽�
#define S_KEY                  87     //Կ��
#define S_HOUSE                88     //����״̬
#define S_BAT1                 89    
#define S_BAT2                 90
#define S_U_NOT_EVEN           91    //ƽ��
#define S_BASE_TOWER           92    //��վ
#define S_CSQ1                 93     //�ź�1
#define S_CSQ2                 94     //�ź�2
#define S_CSQ3                 95     //�ź�3
#define S_CSQ4                 96     //�ź�4
#define S_Ia_UP                97     //Ua������
#define S_Ia_                  98     //-
#define S_Ia                   99     //Ia
#define S_Ib_UP                100    //Ua������
#define S_Ib_                  101    //-
#define S_Ib                   102    //Ia
#define S_Ic_UP                103    //Ua������
#define S_Ic_                  104    //-
#define S_Ic                   105    //Ia



//��ʾ�豸��ʾ------Nx--------'8'-----256~511
#define N_LED(x)              x						//((x&0xff)|0x100)     //ĳһ��'8'��

//��ʾ�豸��ʾ------Dx--------'.',":"-----512~767
#define D_(x)                 x						//((x&0xff)|0x200)


void UpdataLcdShow(void);

//����3��������LCD�����ĺ���
INT8U SetOnDevice_PUCK(INT16U Device);       //Sx
INT8U ClrOnDevice_PUCK(INT16U Device);
INT8U SetOnDevice_D_PUCK(INT16U Device);      //Dx
INT8U SetOnLED8Device_PUCK(INT16U DeviceID,INT8U DisChar);    //Nx
void Main_Dis_Info(char *Str);
void Code_Dis_Info(char *Str);
#endif
