#ifndef APP_BL_LIB_H
#define APP_BL_LIB_H

#ifndef BL_LCD_GZL_C
#define APP_BL_GZL_EXT extern
#else
#define APP_BL_GZL_EXT
#endif




#define MAX_SEG                 40                 //最大的SEG序号:0~MAX_SEG
#define MAX_COL                 3                  //最大的COL序号:0~MAX_COL



#define SEG(x)                  x                 //0~MAX_SEG
#define COM(y)                  y            //0~MAX_COL

#define Sx       1  
#define Dx       2  
#define Nx       3  


//显示设备标示------Sx---------1~255
#define S_A                    1         //A
#define S_B                    2         //B
#define S_C                    3         //C
#define S_BEN                  4         //本
#define S_SHANG                5         //上
#define S_SHIYUE               6         //1
#define S_YUE                  7         //月
#define S_CI                   8         //次
#define S_ZHENG                9        //正向
#define S_FAN                  10       //反向

#define S_ZONG                 11        //总
#define S_JIAN2                12        //尖
#define S_FENG2                13        //峰
#define S_PING2                14        //平
#define S_GU2                  15        //谷

#define S_SU                   16       //速
#define S_QGD                  17       //购
#define S_YOU                  18        //有功
#define S_SHENGYU              19        //剩余
#define S_QIAN                 20        //欠

#define S_XU                   21        //需
#define S_DIAN                 22        //电
#define S_LIANG                23        //量
#define S_SHI1                 24        //失
#define S_YA                   25        //压
#define S_LIU                  26        //流
#define S_SHI                  27        //时
#define S_JIAN                 28        //间
#define S_FEI                  29        //费
#define S_GONG                 30        //功
#define S_LV                   31        //率
#define S_YINSU                32        //因数

#define S_FUHAO                34        //符号：－
#define S_YUAN                 35        //元

#define S_KV                   36        //KV
#define S_VOLT_V               37        //V
#define S_CURR_A               38        //A
#define S_H                    39        //h，与KW组合显示

#define S_CSQ1                 40     //信号1
#define S_CSQ2                 41     //信号2
#define S_CSQ3                 42     //信号3
#define S_CSQ4                 43     //信号4

#define S_LEFTARROW            44     //左箭头
#define S_Ia_                  45     //-
#define S_Ia                   46     //Ia
#define S_Ib_                  47     //-
#define S_Ib                   48     //Ib
#define S_Ic_                  49     //-
#define S_Ic                   50     //Ic

#define S_1                    51        //①
#define S_JIAN1                52        //尖
#define S_FENG                 53        //峰
#define S_PING                 54        //平
#define S_GU                   55        //谷

#define S_1A1                  56        //A
#define S_1B1                  57        //B
#define S_1C1                  58        //C
#define S_NIXIANGXU            59        //逆相序
#define S_Ua                   60        //Ua
#define S_Ub                   61        //Ub
#define S_Uc                   62        //Uc
#define S_2                    63        //②

#define S_BAT1                 64
#define S_BAT2                S_BAT1  

#define S_HONGWAI              65        //红外


#define S_HOUSE                66       //工厂状态
#define S_LOCK                 67       //电表上锁
#define S_BUTTON               68       //编程
#define S_LIGHT                69       //报警
#define S_SHOT                 70     //短接


//显示设备标示------Nx--------'8'-----256~511
#define N_LED(x)              x						//((x&0xff)|0x100)     //某一个'8'字

//显示设备标示------Dx--------'.',":"-----512~767
#define D_(x)                 x						//((x&0xff)|0x200)


void UpdataLcdShow(void);

//以下3个函数是LCD抽象后的函数
INT8U SetOnDevice_PUCK(INT16U Device);       //Sx
INT8U ClrOnDevice_PUCK(INT16U Device);
INT8U SetOnDevice_D_PUCK(INT16U Device);      //Dx
INT8U SetOnLED8Device_PUCK(INT16U DeviceID,INT8U DisChar);    //Nx
void Main_Dis_Info(char *Str);
void Code_Dis_Info(char *Str);
#endif
