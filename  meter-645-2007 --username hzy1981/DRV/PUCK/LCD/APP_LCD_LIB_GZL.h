#ifndef APP_BL_LIB_H
#define APP_BL_LIB_H

#ifndef BL_LCD_GZL_C
#define APP_BL_GZL_EXT extern
#else
#define APP_BL_GZL_EXT
#endif




#define MAX_SEG                 40                 //����SEG���:0~MAX_SEG
#define MAX_COL                 3                  //����COL���:0~MAX_COL



#define SEG(x)                  x                 //0~MAX_SEG
#define COM(y)                  y            //0~MAX_COL

#define Sx       1  
#define Dx       2  
#define Nx       3  


//��ʾ�豸��ʾ------Sx---------1~255
#define S_A                    1         //A
#define S_B                    2         //B
#define S_C                    3         //C
#define S_BEN                  4         //��
#define S_SHANG                5         //��
#define S_SHIYUE               6         //1
#define S_YUE                  7         //��
#define S_CI                   8         //��
#define S_ZHENG                9        //����
#define S_FAN                  10       //����

#define S_ZONG                 11        //��
#define S_JIAN2                12        //��
#define S_FENG2                13        //��
#define S_PING2                14        //ƽ
#define S_GU2                  15        //��

#define S_SU                   16       //��
#define S_QGD                  17       //��
#define S_YOU                  18        //�й�
#define S_SHENGYU              19        //ʣ��
#define S_QIAN                 20        //Ƿ

#define S_XU                   21        //��
#define S_DIAN                 22        //��
#define S_LIANG                23        //��
#define S_SHI1                 24        //ʧ
#define S_YA                   25        //ѹ
#define S_LIU                  26        //��
#define S_SHI                  27        //ʱ
#define S_JIAN                 28        //��
#define S_FEI                  29        //��
#define S_GONG                 30        //��
#define S_LV                   31        //��
#define S_YINSU                32        //����

#define S_FUHAO                34        //���ţ���
#define S_YUAN                 35        //Ԫ

#define S_KV                   36        //KV
#define S_VOLT_V               37        //V
#define S_CURR_A               38        //A
#define S_H                    39        //h����KW�����ʾ

#define S_CSQ1                 40     //�ź�1
#define S_CSQ2                 41     //�ź�2
#define S_CSQ3                 42     //�ź�3
#define S_CSQ4                 43     //�ź�4

#define S_LEFTARROW            44     //���ͷ
#define S_Ia_                  45     //-
#define S_Ia                   46     //Ia
#define S_Ib_                  47     //-
#define S_Ib                   48     //Ib
#define S_Ic_                  49     //-
#define S_Ic                   50     //Ic

#define S_1                    51        //��
#define S_JIAN1                52        //��
#define S_FENG                 53        //��
#define S_PING                 54        //ƽ
#define S_GU                   55        //��

#define S_1A1                  56        //A
#define S_1B1                  57        //B
#define S_1C1                  58        //C
#define S_NIXIANGXU            59        //������
#define S_Ua                   60        //Ua
#define S_Ub                   61        //Ub
#define S_Uc                   62        //Uc
#define S_2                    63        //��

#define S_BAT1                 64
#define S_BAT2                S_BAT1  

#define S_HONGWAI              65        //����


#define S_HOUSE                66       //����״̬
#define S_LOCK                 67       //�������
#define S_BUTTON               68       //���
#define S_LIGHT                69       //����
#define S_SHOT                 70     //�̽�


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
