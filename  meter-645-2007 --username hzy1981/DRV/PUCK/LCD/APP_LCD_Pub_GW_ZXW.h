#ifndef HTLCDPUB_GW_ZXW_h
#define HTLCDPUB_GW_ZXW_h

#ifndef HTLCDPUB_GW_ZXW_C
#define HTLCDPUB_GW_ZXW_EXT extern
#else
#define HTLCDPUB_GW_ZXW_EXT
#endif




#define MAX_SEG                 32                 //����SEG���:0~MAX_SEG
#define MAX_COL                 7                  //����COL���:0~MAX_COL



#define SEG(x)                  x                 //0~MAX_SEG
#define COM(y)                  y            //0~MAX_COL

#define Sx       1  
#define Dx       2  
#define Nx       3  


//��ʾ�豸��ʾ------Sx---------1~255
#define S_P_Q                  1        //�޹������ͷ
#define S_XIANGXIAN1           2        //��1���޷���
#define S_XIANGXIAN2           3        //��2���޷���
#define S_XIANGXIAN3           4        //��3���޷���
#define S_XIANGXIAN4           5        //��4���޷���
#define S_DANGQIAN             6         //��ǰ
#define S_SHANG                7         //��
#define S_SHIYUE               8         //1
#define S_YUE                  9         //��
#define S_ZUHE                 10        //���
#define S_FAN                  11        //��
#define S_ZHENG                12        //��
#define S_XIANG                13        //��
#define S_WU                   14        //��
#define S_YOU                  15        //��
#define S_GONG                 16        //��
#define S_I2                   17        //II
#define S_I1                   18        //I:3������I��II��ϼ���
#define S_V                    19        //IV
#define S_ZONG                 20        //��
#define S_JIAN2                21        //��
#define S_FENG2                 22        //��
#define S_PING2                 23        //ƽ
#define S_GU2                   24        //��
//#define S_SHENGYU              25        //ʣ��
#define S_S_1                    25        //���1
#define S_S_2                    26        //���2
#define S_S_3                    27        //���3
#define S_S_4                    28        //���4
#define S_A                    29         //A
#define S_B                    30         //B
#define S_C                    31         //C
#define S_N                    32         //N
#define S_COS                  33        //
#define S_FAI                  34        //
#define S_JIETI                35        //����
#define S_SHENGYU              36        //ʣ��
#define S_XU                   37        //��
#define S_DIAN                 38        //��
#define S_LIANG                39        //��
#define S_FEI                  40        //��
#define S_JIA                  41        //��
#define S_SHI1                 42        //ʧ
#define S_YA                   43        //ѹ
#define S_LIU                  44        //��
#define S_GONGLV               45        //����
#define S_SHI                  46        //ʱ
#define S_JIAN                 47        //��
#define S_DUAN                 48        //��
#define S_1                    49        //��
#define S_2                    50        //��

//#define S_JIING_E              49        //���
#define S_JIAN1                51        //��
#define S_FENG                 52        //��
//#define S_1                    52        //��
#define S_FUHAO                53        //���ţ���
#define S_PING                 54        //ƽ
#define S_GU                   55        //��
#define S_WAN                  56        //��
#define S_YUAN                 57        //Ԫ

//#define S_2                    56        //��
#define S_KV                   58        //KV
#define S_VOLT_V               59        //V
#define S_CURR_A               60        //A
#define S_H                    61        //h����KW�����ʾ
#define S_KVAR                 62        //kvar
#define S_h                    63        //h����S_KVAR�����ʾ

#define S_Ua                   64        //Ua
#define S_Ub                   65        //Ub
#define S_Uc                   66        //Uc
#define S_NIXIANGXU            67        //������
#define S_Ia_                  68     //-
#define S_Ia                   69     //Ia
#define S_Ib_                  70     //-
#define S_Ib                   71     //Ib
#define S_Ic_                  72     //-
#define S_Ic                   73     //Ic
#define S_S1                   74     //1��ʱ��
#define S_S2                   75     //2��ʱ��
#define S_BAT1                 76    
#define S_BAT2                 77
#define S_TUNJI                78
#define S_CIRCLE               79     //��վ
#define S_CSQ1                 80     //�ź�1
#define S_CSQ2                 81     //�ź�2
#define S_CSQ3                 82     //�ź�3
#define S_CSQ4                 83     //�ź�4
#define S_ZAIBO                84        //����
#define S_HONGWAI              85        //����
#define S_RS1                  86        //��RS�����ʾ
#define S_RS2                  87        //��RS�����ʾ
#define S_BUTTON               88       //���
#define S_LOCK                 89       //�������
#define S_HOUSE                90       //����״̬
#define S_LIGHT                91       //����

#define S_DUKA                 92       //����
#define S_ZHONG                93       //��
#define S_CHENGGONG            94       //�ɹ�
#define S_SHIBAI               95       //ʧ��
#define S_QGD                  96       //�빺��
#define S_TOUZHI               97       //͸֧
#define S_LAZHA                98       //��բ




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
