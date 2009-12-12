#ifndef BL55076_Soft
#define BL55076_Soft

 

#define		BL55076_SLAVE_ADDR		0x70	//SA0=0,write
#define		BL55076_DEVICE_ADDR		0xE0


#define		BL55076_NORMAL_DIS		0x40	//normal mode,1/3 bias,1/4 duty,disabe
#define		BL55076_NORMAL_EN		0x48	//normal mode,1/3 bias,1/4 duty,enabe
#define		BL55076_LOWPOWR_DIS	        0x50	//power saving mode,1/3 bias,1/4 duty,disabe
#define		BL55076_LOWPOWR_EN	        0x58	//power saving mode,1/3 bias,1/4 duty,enabe
#define		BL55076_BLINK_OFF		0x70	//blink off



#define SET_55076_SCLK_DIR(a)  PM15_bit.no6=a
#define SET_55076_SDA_DIR(a)   PM15_bit.no5=a


#define SET_55076_SCLK(a)       P15_bit.no6=a    //将SCL总线置---------PUCK
#define SET_55076_SDA(a)        P15_bit.no5=a     //将SDA总线置---------PUCK

#define GET_55076_SDA       (P15_bit.no5)


void Set_55076_Sclk_Dir(INT8U Dir);
void Set_55076_Sda_Dir(INT8U Dir);
void Set_55076_Sclk_Pin(INT8U Level);
void Set_55076_Sda_Pin(INT8U Level);
INT8U Get_55076_Sda_Pin(void);

INT8U Write_55076_Cmd(INT8U Len,INT8U *Src);
INT8U Write_55076_Data(INT8U Len,INT8U *Src);

#endif