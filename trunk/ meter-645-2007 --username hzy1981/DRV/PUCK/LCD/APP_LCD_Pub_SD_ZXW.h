#ifndef HTLCDPUB_SD_ZXW_h
#define HTLCDPUB_SD_ZXW_h

#ifndef HTLCDPUB_SD_ZXW_C
#define HTLCDPUB_SD_ZXW_EXT extern
#else
#define HTLCDPUB_SD_ZXW_EXT
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
#define S_SHENGYU              25        //剩余
#define S_S_1                    26        //电价1
#define S_S_2                    27        //电价2
#define S_S_3                    28        //电价3
#define S_S_4                    29        //电价4
#define S_A                    30         //A
#define S_B                    31         //B
#define S_C                    32         //C
#define S_N                    33         //N
#define S_COS                  34        //
#define S_FAI                  35        //
#define S_JIETI                36        //阶梯
#define S_SHEQIAN              37        //赊欠
#define S_XU                   38        //需
#define S_DIAN                 39        //电
#define S_LIANG                40        //量
#define S_JIA                  41        //价
#define S_SHI1                 42        //失
#define S_YA                   43        //压
#define S_LIU                  44        //流
#define S_GONGLV               45        //功率
#define S_SHI                  46        //时
#define S_JIAN                 47        //间
#define S_DUAN                 48        //段
#define S_JIING_E              49        //金额
#define S_JIAN1                50        //尖
#define S_FENG                 51        //峰
#define S_1                    52        //①
#define S_FUHAO                53        //符号：－
#define S_PING                 54        //平
#define S_GU                   55        //谷
#define S_2                    56        //②
#define S_KW                   57        //KW
#define S_H                    58        //h，与KW组合显示
#define S_WAN                  59        //万
#define S_YUAN                 60        //元
#define S_KVAR                 61        //kvar
#define S_h                    62        //h，与S_KVAR组合显示
#define S_VOLT_V               63        //V
#define S_CURR_A               64        //A
#define S_Ua                   65        //Ua
#define S_Ub                   66        //Ub
#define S_Uc                   67        //Uc
#define S_NIXIANGXU            68        //逆相序
#define S_Ia_                  69     //-
#define S_Ia                   70     //Ia
#define S_Ib_                  71     //-
#define S_Ib                   72     //Ib
#define S_Ic_                  73     //-
#define S_Ic                   74     //Ic
#define S_S1                   75     //1套时段
#define S_S2                   76     //2套时段
#define S_BAT1                 77    
#define S_BAT2                 78
#define S_CHANGSHU             79    
#define S_BIAOHAO              80
#define S_CIRCLE               81     //基站
#define S_CSQ1                 82     //信号1
#define S_CSQ2                 83     //信号2
#define S_CSQ3                 84     //信号3
#define S_CSQ4                 85     //信号4
#define S_HONGWAI              86        //红外
#define S_RS                   87        //
#define S_RS1                  88        //与RS组合显示
#define S_RS2                  89        //与RS组合显示
#define S_BUTTON               90       //编程
#define S_LOCK                 91       //电表上锁
#define S_HOUSE                92       //工厂状态
#define S_LIGHT                93       //报警

#define S_DUKA                 94       //读卡
#define S_ZHONG                95       //中
#define S_CHENGGONG            96       //成功
#define S_SHIBAI               97       //失败
#define S_QGD                  98       //请购电
#define S_TOUZHI               99       //透支
#define S_LAZHA                100       //拉闸
#define S_TUNJI                101       //囤积



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
