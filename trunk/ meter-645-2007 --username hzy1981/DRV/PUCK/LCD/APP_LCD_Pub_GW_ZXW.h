#ifndef HTLCDPUB_GW_ZXW_h
#define HTLCDPUB_GW_ZXW_h

#ifndef HTLCDPUB_GW_ZXW_C
#define HTLCDPUB_GW_ZXW_EXT extern
#else
#define HTLCDPUB_GW_ZXW_EXT
#endif




#define MAX_SEG                 32                 //最大的SEG序号:0~MAX_SEG
#define MAX_COL                 7                  //最大的COL序号:0~MAX_COL



#define SEG(x)                  x                 //0~MAX_SEG
#define COM(y)                  y            //0~MAX_COL

#define Sx       1  
#define Dx       2  
#define Nx       3  


//显示设备标示------Sx---------1~255
#define S_P_Q                  1        //无功方向箭头
#define S_XIANGXIAN1           2        //第1象限符号
#define S_XIANGXIAN2           3        //第2象限符号
#define S_XIANGXIAN3           4        //第3象限符号
#define S_XIANGXIAN4           5        //第4象限符号
#define S_DANGQIAN             6         //当前
#define S_SHANG                7         //上
#define S_SHIYUE               8         //1
#define S_YUE                  9         //月
#define S_ZUHE                 10        //组合
#define S_FAN                  11        //反
#define S_ZHENG                12        //正
#define S_XIANG                13        //向
#define S_WU                   14        //无
#define S_YOU                  15        //有
#define S_GONG                 16        //功
#define S_I2                   17        //II
#define S_I1                   18        //I:3象限有I和II组合即可
#define S_V                    19        //IV
#define S_ZONG                 20        //总
#define S_JIAN2                21        //尖
#define S_FENG2                 22        //峰
#define S_PING2                 23        //平
#define S_GU2                   24        //谷
//#define S_SHENGYU              25        //剩余
#define S_S_1                    25        //电价1
#define S_S_2                    26        //电价2
#define S_S_3                    27        //电价3
#define S_S_4                    28        //电价4
#define S_A                    29         //A
#define S_B                    30         //B
#define S_C                    31         //C
#define S_N                    32         //N
#define S_COS                  33        //
#define S_FAI                  34        //
#define S_JIETI                35        //阶梯
#define S_SHENGYU              36        //剩余
#define S_XU                   37        //需
#define S_DIAN                 38        //电
#define S_LIANG                39        //量
#define S_FEI                  40        //费
#define S_JIA                  41        //价
#define S_SHI1                 42        //失
#define S_YA                   43        //压
#define S_LIU                  44        //流
#define S_GONGLV               45        //功率
#define S_SHI                  46        //时
#define S_JIAN                 47        //间
#define S_DUAN                 48        //段
#define S_1                    49        //①
#define S_2                    50        //②

//#define S_JIING_E              49        //金额
#define S_JIAN1                51        //尖
#define S_FENG                 52        //峰
//#define S_1                    52        //①
#define S_FUHAO                53        //符号：－
#define S_PING                 54        //平
#define S_GU                   55        //谷
#define S_WAN                  56        //万
#define S_YUAN                 57        //元

//#define S_2                    56        //②
#define S_KV                   58        //KV
#define S_VOLT_V               59        //V
#define S_CURR_A               60        //A
#define S_H                    61        //h，与KW组合显示
#define S_KVAR                 62        //kvar
#define S_h                    63        //h，与S_KVAR组合显示

#define S_Ua                   64        //Ua
#define S_Ub                   65        //Ub
#define S_Uc                   66        //Uc
#define S_NIXIANGXU            67        //逆相序
#define S_Ia_                  68     //-
#define S_Ia                   69     //Ia
#define S_Ib_                  70     //-
#define S_Ib                   71     //Ib
#define S_Ic_                  72     //-
#define S_Ic                   73     //Ic
#define S_S1                   74     //1套时段
#define S_S2                   75     //2套时段
#define S_BAT1                 76    
#define S_BAT2                 77
#define S_TUNJI                78
#define S_CIRCLE               79     //基站
#define S_CSQ1                 80     //信号1
#define S_CSQ2                 81     //信号2
#define S_CSQ3                 82     //信号3
#define S_CSQ4                 83     //信号4
#define S_ZAIBO                84        //红外
#define S_HONGWAI              85        //红外
#define S_RS1                  86        //与RS组合显示
#define S_RS2                  87        //与RS组合显示
#define S_BUTTON               88       //编程
#define S_LOCK                 89       //电表上锁
#define S_HOUSE                90       //工厂状态
#define S_LIGHT                91       //报警

#define S_DUKA                 92       //读卡
#define S_ZHONG                93       //中
#define S_CHENGGONG            94       //成功
#define S_SHIBAI               95       //失败
#define S_QGD                  96       //请购电
#define S_TOUZHI               97       //透支
#define S_LAZHA                98       //拉闸




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
