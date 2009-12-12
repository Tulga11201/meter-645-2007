#ifndef HTLCDPUB_SD_ZXW_h
#define HTLCDPUB_SD_ZXW_h

#ifndef HTLCDPUB_SD_ZXW_C
#define HTLCDPUB_SD_ZXW_EXT extern
#else
#define HTLCDPUB_SD_ZXW_EXT
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
#define S_SHENGYU              25        //ʣ��
#define S_S_1                    26        //���1
#define S_S_2                    27        //���2
#define S_S_3                    28        //���3
#define S_S_4                    29        //���4
#define S_A                    30         //A
#define S_B                    31         //B
#define S_C                    32         //C
#define S_N                    33         //N
#define S_COS                  34        //
#define S_FAI                  35        //
#define S_JIETI                36        //����
#define S_SHEQIAN              37        //��Ƿ
#define S_XU                   38        //��
#define S_DIAN                 39        //��
#define S_LIANG                40        //��
#define S_JIA                  41        //��
#define S_SHI1                 42        //ʧ
#define S_YA                   43        //ѹ
#define S_LIU                  44        //��
#define S_GONGLV               45        //����
#define S_SHI                  46        //ʱ
#define S_JIAN                 47        //��
#define S_DUAN                 48        //��
#define S_JIING_E              49        //���
#define S_JIAN1                50        //��
#define S_FENG                 51        //��
#define S_1                    52        //��
#define S_FUHAO                53        //���ţ���
#define S_PING                 54        //ƽ
#define S_GU                   55        //��
#define S_2                    56        //��
#define S_KW                   57        //KW
#define S_H                    58        //h����KW�����ʾ
#define S_WAN                  59        //��
#define S_YUAN                 60        //Ԫ
#define S_KVAR                 61        //kvar
#define S_h                    62        //h����S_KVAR�����ʾ
#define S_VOLT_V               63        //V
#define S_CURR_A               64        //A
#define S_Ua                   65        //Ua
#define S_Ub                   66        //Ub
#define S_Uc                   67        //Uc
#define S_NIXIANGXU            68        //������
#define S_Ia_                  69     //-
#define S_Ia                   70     //Ia
#define S_Ib_                  71     //-
#define S_Ib                   72     //Ib
#define S_Ic_                  73     //-
#define S_Ic                   74     //Ic
#define S_S1                   75     //1��ʱ��
#define S_S2                   76     //2��ʱ��
#define S_BAT1                 77    
#define S_BAT2                 78
#define S_CHANGSHU             79    
#define S_BIAOHAO              80
#define S_CIRCLE               81     //��վ
#define S_CSQ1                 82     //�ź�1
#define S_CSQ2                 83     //�ź�2
#define S_CSQ3                 84     //�ź�3
#define S_CSQ4                 85     //�ź�4
#define S_HONGWAI              86        //����
#define S_RS                   87        //
#define S_RS1                  88        //��RS�����ʾ
#define S_RS2                  89        //��RS�����ʾ
#define S_BUTTON               90       //���
#define S_LOCK                 91       //�������
#define S_HOUSE                92       //����״̬
#define S_LIGHT                93       //����

#define S_DUKA                 94       //����
#define S_ZHONG                95       //��
#define S_CHENGGONG            96       //�ɹ�
#define S_SHIBAI               97       //ʧ��
#define S_QGD                  98       //�빺��
#define S_TOUZHI               99       //͸֧
#define S_LAZHA                100       //��բ
#define S_TUNJI                101       //�ڻ�



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
