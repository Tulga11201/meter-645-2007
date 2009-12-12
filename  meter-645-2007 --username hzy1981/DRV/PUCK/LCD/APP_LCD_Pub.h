#ifndef HTLCDPUB_h
#define HTLCDPUB_h

#ifndef HTLCDPUB_C
#define HTLCDPUB_EXT extern
#else
#define HTLCDPUB_EXT
#endif




#define MAX_SEG                 32                 //����SEG���:0~MAX_SEG
#define MAX_COL                 7                  //����COL���:0~MAX_COL



#define SEG(x)                  x                 //0~MAX_SEG
#define COM(y)                  y            //0~MAX_COL

#define Sx       1  
#define Dx       2  
#define Nx       3  


//��ʾ�豸��ʾ------Sx---------1~255
#define S_A                    1         //A
#define S_B                    2         //B
#define S_C                    3         //C
#define S_N                    4         //N
#define S_SHANG                5         //��
#define S_BEN                  6         //��
#define S_SHANG1               7         //��
#define S_SHIYUE               8         //1
#define S_YUE                  9         //��
#define S_CI                   10        //��
#define S_SHURU                11        //����
#define S_FAN                  12        //��
#define S_ZHENG                13        //��
#define S_XIANG                14        //��
#define S_XU                   15        //��
#define S_DIAN                 16        //��
#define S_LIANG                17        //��
#define S_SHI                  18        //ʱ
#define S_JIAN                 19        //��
#define S_FEI                  20        //��
#define S_XIANGXIAN1           21        //��1���޷���
#define S_XIANGXIAN2           22        //��2���޷���
#define S_XIANGXIAN3           23        //��3���޷���
#define S_XIANGXIAN4           24        //��4���޷���

#define S_COS                  25        //
#define S_FAI                  26        //
#define S_I1                   27        //I
#define S_I2                   28        //II
#define S_I3                   29        //III
#define S_V                    30        //IV
#define S_ZONG                 103       //��
#define S_T                    31        //T
#define S_GUO                  32        //��
#define S_SHUCHU               33        //���
#define S_WU                   34        //��
#define S_YOU                  35        //��
#define S_GONG0                36        //��
#define S_SHI1                  37        //ʧ
#define S_YA                   38        //ѹ
#define S_LIU                  39        //��
#define S_DUAN                 40        //��
#define S_GONG                 41        //��
#define S_LV                   42        //��
#define S_DU                   43        //��
#define S_JIAN1                44        //��
#define S_FENG                 45        //��
#define S_PING                 46        //ƽ
#define S_GU                   47        //��
#define S_1                    48        //��
#define S_2                    49        //��
#define S_3                    50        //��
#define S_4                    51        //��

#define S_1A1                  52        //A
#define S_1B1                  53        //B

#define S_1C1                  54        //C


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

#define S_CUOFENG              70        //���

#define S_QIANFEI              71        //Ƿ��
#define S_DONG                 72        //��
#define S_RS1                  73        //Ƿ��
#define S_RS2                  74        //Ƿ��
#define S_HONGWAI              75        //����
#define S_NIXIANGXU            76        //������

#define S_BAT1                 77 
#define S_BAT2                 78
#define S_BAT3                 79

#define S_Ua                   80     //Ua
#define S_Ub                   81     //Ub
#define S_Uc                   82     //Uc

#define S_CIRCLE               83     //Բ��

#define S_ARROW_LEFT           84     //���ͷ
#define S_CSQ4                 85     //�ź�4
#define S_CSQ3                 86     //�ź�3
#define S_CSQ2                 87     //�ź�2

#define S_CSQ1                 88     //�ź�1
#define S_ARROW_RIGHT          89     //���ͷ


#define S_Ia_                 90     //-
#define S_Ia                  91     //Ia
#define S_Ib_                 92     //-
#define S_Ib                  93     //Ib
#define S_Ic_                 94     //-
#define S_Ic                  95     //Ic

#define S_TT                  96     //����
#define S_BUTTON              97     //���
#define S_HOUSE               98     //����״̬
#define S_KEY                 99     //Կ��
#define S_LOCK                100     //�������
#define S_LIGHT               101     //����
#define S_SHOT                102     //�̽�


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
