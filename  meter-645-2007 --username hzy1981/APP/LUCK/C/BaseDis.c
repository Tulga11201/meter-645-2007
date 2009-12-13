
#include "Pub_PUCK.h"



const char* const_frmt[]=
{  
  "XX######|",                        //--------------------0
  "X#.####|kW",                       //需量：有功
  "##.##.##.##:##|tm",                //时间
  "X#########|",                     //----------------------3
  "##:##:##|",                      //-------------------4
  "##-##-##|",                      //-------------------5
  "-########-|",                     //显示未完提示------------6
  "XXXXX#.####|kvar",                   //需量：无功---------------7
  "XXXXX#.####|kVA",                   //需量：视在--------------8
  "########|",                 //显示结束提示---------------------9
  "XXXXX#|",                   //次数，分--------------------10
  "XXXXXXX#.##|",              //-----------------------------11
  "XXXXXXX#.##|kWh",           //--------------------12
  "XXXXXXX#|",                 //--------------------13
  "XXXXXXX#|Ah",                 //--------------------14
  "##-## ##|",                 //--------------------15:时区起始日期及日时段表号
  "##:## ##|",                 //--------------------16:时段起始时间及费率号
  "XXXX####|",                 //--------------------17:显示2位
  "##-##-##|tm",        //--------------------18：时间:年月日
  "##:##|tm",        //--------------------19：时间:时分
  "####|",        //--------------------20
  "##:##:##|tm",        //--------------------21：时间:时分秒
};


// 十六进制转字符串
static const char hex2cha[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'b', 'C', 'd', 'E', 'F',
};


#define MAX_DIS_BYTE 30
// 有功电能显示单位
const char AC_ENERG_DIS_UNIT[][20] = 
{
  {"XXXXXXXXX#|kWh"},
  
#ifdef LCD_MIN_8 
  {"XXXXXXXX#.#|kWh"},
#else
  {"XXXXXXXX#.# |kWh"},
#endif

  {"XXXXXXX#.##|kWh"},
  {"XXXXXX#.###|kWh"},
  {"XXXXX#.####|kWh"}
};

// 无功电能显示单位
const char REAC_ENERG_DIS_UNIT[][20] = 
{
  {"XXXXXXXXX#|kvarh"},
  
#ifdef LCD_MIN_8 
  {"XXXXXXXX#.#|kvarh"},
#else
  {"XXXXXXXX#.# |kvarh"},
#endif

  {"XXXXXXX#.##|kvarh"},
  {"XXXXXX#.###|kvarh"},
  {"XXXXX#.####|kvarh"}
};

// 视在电能显示单位
const char APP_ENERG_DIS_UNIT[][20] = 
{
  {"XXXXXXXXX#|kVAh"},  
  
#ifdef LCD_MIN_8 
  {"XXXXXXXX#.#|kVAh"},
#else
  {"XXXXXXXX#.# |kVAh"},
#endif

  {"XXXXXXX#.##|kVAh"},
  {"XXXXXX#.###|kVAh"},
  {"XXXXX#.####|kVAh"}
};



// 有功功率需量显示单位
const char AC_POWER_DIS_UNIT[][20] = 
{
  {"XXXXXXXXX#|kW"},  
  
#ifdef LCD_MIN_8 
  {"XXXXXXXX#.#|kW"},
#else
  {"XXXXXXXX#.# |kW"},
#endif

  {"XXXXXXX#.##|kW"},
  {"XXXXXX#.###|kW"},
  {"XXXXX#.####|kW"}
};

// 无功电能显示单位
const char REAC_POWER_DIS_UNIT[][20] = 
{
  {"XXXXXXXXX#|kvar"},  
  
#ifdef LCD_MIN_8 
  {"XXXXXXXX#.#|kvar"},
#else
  {"XXXXXXXX#.# |kvar"},
#endif

  {"XXXXXXX#.##|kvar"},
  {"XXXXXX#.###|kvar"},
  {"XXXXX#.####|kvar"}
};

// 视在电能显示单位
const char APP_POWER_DIS_UNIT[][20] = 
{
  {"XXXXXXXXX#|kVA"},  
  
#ifdef LCD_MIN_8 
  {"XXXXXXXX#.#|kVA"},
#else
  {"XXXXXXXX#.# |kVA"},
#endif

  {"XXXXXXX#.##|kVA"},
  {"XXXXXX#.###|kVA"},
  {"XXXXX#.####|kVA"}
};


void  Modi_Dis_Unit(item_t item,char Unit[],u16 UnitLen)
{
  if(UnitLen>MAX_DIS_BYTE)
    ASSERT_FAILED();
  
  if(EnergDisBit>MAX_DIS_ENERG_BIT)
    ASSERT_FAILED();
  
  if(DemandDisBit>MAX_DIS_POWER_BIT)
    ASSERT_FAILED();  
  
  
  //电能显示位数
  if(EnergDisBit != 2 && DI_IS_ENERG(item))  //电能显示小数点,表格按2位，但现在不是显示2位,修改相应的显示格式
  {
    if(strstr((const INT8S *)Unit, "kWh"))  //电能显示位数，表格按2位
    {  
      strcpy(Unit,AC_ENERG_DIS_UNIT[EnergDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kvarh"))  //电能显示位数，表格按2位
    {  
      strcpy(Unit,REAC_ENERG_DIS_UNIT[EnergDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kVAh"))  //电能显示位数，表格按2位
    {  
      strcpy(Unit,APP_ENERG_DIS_UNIT[EnergDisBit]);
      return ;
    }
  } 
  
  //功率显示位数
  if(DemandDisBit != 4 &&(DI_IS_DEMAND(item) || DI_IS_INSTANT(item)))  //需量，功率
  {
    if(strstr((const INT8S *)Unit, "kW"))  //电能显示位数，表格按2位
    {  
      strcpy(Unit,AC_POWER_DIS_UNIT[DemandDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kvar"))  //电能显示位数，表格按2位
    {  
      strcpy(Unit,REAC_POWER_DIS_UNIT[DemandDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kVA"))  //电能显示位数，表格按2位
    {  
      strcpy(Unit,APP_POWER_DIS_UNIT[DemandDisBit]);
      return ;
    }
  }  
}

// 显示缓冲区内容
void lcd_update (void) 
{
  UpdataLcdShow();
}

//将 hex 转换成 ascii 码
INT16U  Hex_To_Ascii(INT8U *Src,INT8U *Dst, INT16U SrcLen,INT16U DstMaxLen)
{
  INT16U len;
  INT16S i;
  
  if(SrcLen>DstMaxLen)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  for(i=0,len=0;i<SrcLen && Src[-1*i]!=0;i++)
  {  
    if(Src[-1*i]>='0' && Src[-1*i]<='9')
      Dst[len++]=Src[-1*i];  
    
    if(Src[-1*i]>='A' && Src[-1*i]<='Z')
       Dst[len++]=Src[-1*i];  
    
    if(Src[-1*i]>='a' && Src[-1*i]<='z')
       Dst[len++]=Src[-1*i];  
    
    if(Src[-1*i] EQ '.')
       Dst[len++]=Src[-1*i];  
  }
  
  Dst[SrcLen]='|';
  return len;
  
}


void Check_LCDVar_Cs(void)
{
  if(CHECK_STRUCT_VAR(Pub_Bit8_Len5_PUCK)==0)//头尾不对
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Pub_Bit16_Len4_PUCK)==0)//头尾不对
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Sleep_Sec_Countr)==0)//头尾不对
  ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Key_Value_Pub)==0)//头尾不对
  {
    mem_set((void *)(&Key_Value_Pub),0,sizeof(Key_Value_Pub),\
                 (void *)(&Key_Value_Pub),sizeof(Key_Value_Pub));   
    ASSERT_FAILED();
  }  
}

u8 Modi_Item(item_t item,item_t *Dst)
{
  switch(item)
  {
    //电压
    case 0x02010100:
      *Dst=_PDI_A_VOL;
      return 1;
      
    case 0x02010200:
      *Dst=_PDI_B_VOL;
      return 1;
      
    case 0x02010300:
      *Dst=_PDI_C_VOL;
      return 1;
    
    //电流
    case 0x02020100:
       *Dst=_PDI_A_CUR;
      return 1;
      
    case 0x02020200:
       *Dst=_PDI_B_CUR;
      return 1;
      
    case 0x02020300:
       *Dst=_PDI_C_CUR;
       return 1;
    
    //相角
    case 0x02070100:
      *Dst=_PDI_A_ANGLE;
       return 1;
       
    case 0x02070200:
      *Dst=_PDI_B_ANGLE;
       return 1;
      
    case 0x02070300:
      *Dst=_PDI_C_ANGLE;
       return 1;
  }
  
  return 0;  
}

// 获取协议数据内容
s16 getdata (item_t item, void* dst, void* dststart, s16 maxlen) 
{ 
  s16 nlen = 0;
  u8  sign=S_INTU;
  u8  temp[6];
  
  if(maxlen>DIS_BUF_LEN)  //越界保护
    return 0;
  
  if (item == DI_CHANEL_IRDA1 || item == DI_CHANEL_IRDA2)   //第一路通信参数
  {
      u32 type = Chanel_Para[CHANEL_IRDA].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  }
  else if (item == DI_CHANEL_485_1)   //第一路通信参数
  {
      u32 type = Chanel_Para[CHANEL_485_1].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  }
  else if (item == DI_CHANEL_485_2)   //第二路通信参数
  {
      u32 type = Chanel_Para[CHANEL_485_2].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  } 

#ifdef CHANEL_MOUDEL 
  else if (item == DI_CHANEL_485_3)   //第三路通信参数
  {
      u32 type = Chanel_Para[CHANEL_MOUDEL].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  }
#endif
  /*
  else if((item&0xFFFF00FF)EQ DI_AC_POWER_SUM)  //有功功率,带符号
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      if(item EQ DI_AC_POWER_SUM&& Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir)
        sign=-1;
      if(item EQ DI_AC_POWER_A&& Measu_Status_Mode_ToPub_PUCK.A_APwrDir)
        sign=-1;        
      if(item EQ DI_AC_POWER_B&& Measu_Status_Mode_ToPub_PUCK.B_APwrDir)
        sign=-1;        
      if(item EQ DI_AC_POWER_C&& Measu_Status_Mode_ToPub_PUCK.C_APwrDir)
        sign=-1;
  }
  else if((item&0xFFFF00FF)EQ DI_REAC_POWER_SUM) //无功功率,带符号
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      if(item EQ DI_REAC_POWER_SUM&& Measu_Status_Mode_ToPub_PUCK.SUM_RPwrDir)
        sign=-1;
      if(item EQ DI_REAC_POWER_A&& Measu_Status_Mode_ToPub_PUCK.A_RPwrDir)
        sign=-1;        
      if(item EQ DI_REAC_POWER_B&& Measu_Status_Mode_ToPub_PUCK.B_RPwrDir)
        sign=-1;        
      if(item EQ DI_REAC_POWER_C&& Measu_Status_Mode_ToPub_PUCK.C_RPwrDir)
        sign=-1;
  }
  */
  else if(item EQ PDI_COMM_ADDR || item EQ PDI_METER_ID) //通信地址
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      
      mem_cpy(temp, (u8 *)dst+4, 2, temp, sizeof(temp));
      mem_cpy(temp+2, dst, 4, temp, sizeof(temp));      
      
      mem_cpy(dst, temp, 6, dststart, sizeof(temp));
  }
  else if((item>=0x04000106) && (item <=0x04000109))//两套时区表切换时间/两套日时段表切换时间：YYMMDDhhmm
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      
      mem_cpy(temp, (u8 *)dst+2, 3, temp, sizeof(temp));      
      mem_cpy(temp+3, dst, 2, temp, sizeof(temp));      
      mem_cpy(dst, temp, 5, dststart, sizeof(temp));
  }
  else if((item EQ 0x10000101)||(item EQ 0x10000201))//最近1次失压发生时刻/最近1次失压结束时刻:YYMMDDhhmmsshhmm
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      
      mem_cpy(temp, (u8 *)dst+3, 3, temp, sizeof(temp));      
      mem_cpy(temp+3, dst, 3, temp, sizeof(temp));      
      mem_cpy(dst, temp, 6, dststart, sizeof(temp));
  }
  else if(DI_IS_DEMAND(item)) //需量
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);  
   
      mem_cpy(temp, (u8 *)dst+5, 3, temp, sizeof(temp));
      mem_cpy(temp+3, (u8 *)dst+3, 2, temp, sizeof(temp));       
      mem_cpy((u8 *)dst+3, temp, 5, dststart, 8);   //8:目标最大长度
  }  
  else
  {
    nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, DIS_BUF_LEN ,&sign);
  }
  nlen=(nlen>maxlen)?maxlen:nlen;
  //mem_cpy(dst, start, nlen, dststart, maxlen);
  mem_set((u8*)dst + nlen, 0, maxlen - nlen, dststart, maxlen);
  
  if(CHECK_STRUCT_VAR(_Dis_GetData_Buf)==0 || nlen==0) //检查头尾，避免越界
     ASSERT_FAILED();
  
  if(sign!=S_INTS)  //有符号
    return nlen;
  
   
  //以下是有符号数据处理
  //处理符号位
  if(GET_BIT(*((u8*)dst+nlen-1),7))
  {
    CLR_BIT(*((u8*)dst+nlen-1),7);
    return (-1);
  }
  
  return nlen;  
}

// 判断是否停电
bool poweroff (void) 
{
  return (Get_Sys_Status() != SYS_NORMAL);
}

// 判断是否为实时数据
bool rtvalue (item_t item) 
{
  if(DI_CHANEL_485_1 EQ item || CHANEL_485_2 EQ item)
     return 1;
     
  return (S_RAM == Get_DLT645_Data_Storage_Type(item));
}

/********************************************************************************
PUCK:
函数功能：内卡参数读出置sram，参数初始化
入口：
返回：
********************************************************************************/
void lcdinit (void) {
    u8     temp8;
    s16    temp;
    offs_t numb;

   
    temp8 = 0;
    temp=Read_Storage_Data(ROLLCYCLE,&temp8, &temp8, sizeof(temp8)); 
    if(!temp ||(temp8<5) )
    {
      temp8=5;
    }
    
    if(!temp ||(temp8<5))
    {
      temp8=20;  //国网的最大巡显周期
    }        
    rollcycle=(u8)Bcd2Hex((u8*)&temp8, 1);
      
    
    numb=0;
    temp=Read_Storage_Data(NUMBMODEA,&numb, &numb, sizeof(numb)); 
    if((!temp) ||(!numb))
      numb=0x13;   //BCD码,1字节------PUCK_LCD
    //numb=0x20;
    MODE_A_NUM = (s16)Bcd2Hex((u8*)&numb, 1);
    
    numb=0;
    temp=Read_Storage_Data(NUMBMODEB,&numb, &numb, sizeof(numb)); 
     if((!temp)||(!numb))
      numb=0x14;   //BCD码，2字节------PUCK_LCD
    MODE_B_NUM = (s16)Bcd2Hex((u8*)&numb, 2);
    
    
    temp8=0;
    temp=Read_Storage_Data(PDI_ENERGY_DECIMAL_NUM,&temp8, &temp8, sizeof(temp8)); 
     if((!temp)||(temp8>MAX_DIS_ENERG_BIT))
      temp8=DEFAULT_DIS_ENERG_BIT;   //默认电能显示3位,范围：0～4
    EnergDisBit = (u8)Bcd2Hex((u8*)&temp8, 1);
    
    
    temp8=0;
    temp=Read_Storage_Data(PDI_POWER_DECIMAL_NUM,&temp8, &temp8, sizeof(temp8)); 
     if((!temp)||(temp8>MAX_DIS_POWER_BIT))
      temp8=DEFAULT_DIS_POWER_BIT;   //功率需量显示4位,范围：0～4
    DemandDisBit = (u8)Bcd2Hex((u8*)&temp8, 1);
    
}

// 循显时间：秒
s16 rolltime () {
    return (rollcycle);
}

// 开关液晶背光
void lcdlight (u8 stat) {
    if (stat > 0) {
        Turn_Light_On();
    } else {
        Turn_Light_Off();
    }
}


/********************************************************************************
函数原型：void Init_Event_DIS_PUCK(stat_t *stat )
函数功能：初始化事件
出口：
*********************************************************************************/
void Init_Event_DIS_PUCK(stat_t *stat)
{  
  INT8U temp;
  //-------------------------断相-------------------------  
  stat->cut_volt_a=Get_Event_Instant(ID_EVENT_A_LOSS_PARSE);//A相断相：0--没发生；1----发生；
  stat->cut_volt_b=Get_Event_Instant(ID_EVENT_B_LOSS_PARSE);//B相断相：0--没发生；1----发生；
  stat->cut_volt_c=Get_Event_Instant(ID_EVENT_C_LOSS_PARSE);//C相断相：0--没发生；1----发生；
    
  
  //-------------------------过压-------------------------
  stat->over_volt_a=Get_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);//A相过压：0--没发生；1----发生；
  stat->over_volt_b=Get_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);//B相过压：0--没发生；1----发生；
  stat->over_volt_c=Get_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);//C相过压：0--没发生；1----发生；
  
   
    
  //-------------------------失流-------------------------
  stat->loss_cur_a=Get_Event_Instant(ID_EVENT_A_LOSS_CURR);//A相失流：0--没发生；1----发生；
  stat->loss_cur_b=Get_Event_Instant(ID_EVENT_B_LOSS_CURR);//B相失流：0--没发生；1----发生；
  stat->loss_cur_c=Get_Event_Instant(ID_EVENT_C_LOSS_CURR);//C相失流：0--没发生；1----发生；
  

  //-------------------------电流反相-------------------------
  stat->cur_rers_a=Get_Event_Instant(ID_EVENT_A_NEG_CURR);//A相电流反相：0--没发生；1----发生；
  stat->cur_rers_b=Get_Event_Instant(ID_EVENT_B_NEG_CURR);//B相电流反相：0--没发生；1----发生；
  stat->cur_rers_c=Get_Event_Instant(ID_EVENT_C_NEG_CURR);//C相电流反相：0--没发生；1----发生；
  
  
  //-------------------------断流-------------------------
  //断流
  stat->loss_cut_a  =  Read_Event_Status(ID_EVENT_A_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.A<=(Get_Start_Current()*UNIT_A));   //A分相电流小于启动电流;
  stat->loss_cut_b  =  Read_Event_Status(ID_EVENT_B_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.B<=(Get_Start_Current()*UNIT_A)); ;
  stat->loss_cut_c  =  Read_Event_Status(ID_EVENT_C_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.C<=(Get_Start_Current()*UNIT_A)); ;
  
  if(Get_SysParse_Mode()!=PARSE_341)
  {
    stat->cut_volt_b=0;
    stat->over_volt_b=0;
    stat->loss_cur_b=0;
    stat->cur_rers_b=0;    
    stat->loss_cut_b=0;
  }
  
  
  //象限  
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=0;  //电表工作象限1：
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=0;  //电表工作象限2:
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=0;  //电表工作象限3：
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=0;  //电表工作象限4：
      
  if((FP32S)Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B\
                       ,Measu_InstantData_ToPub_PUCK.Curr.C)>(Get_Start_Current()*UNIT_A))  //电流都大于启动电流
  {
    switch(Measu_InstantData_ToPub_PUCK.Quadrant.Sum)
    {
    case QUADRANT1:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=1;
      break;
    case QUADRANT2:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=1;
      break;
    case QUADRANT3:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=1;
      break;
    case QUADRANT4:
        Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=1;
      break;
    }
  }
  else
    Meter_Run_Status.NegCurr_Qudrant.Byte&=0xf0;


  stat->jumper_short  = (B_TEST_FAC_STATUS && (B_TEST_HARD_STATUS EQ 0));     //调试模式
  stat->fac_status    = ((B_TEST_FAC_STATUS EQ 0) && B_TEST_HARD_STATUS);      //工厂模式
  stat->switch_opened =  Key_Value_Pub.Key.Bit.PrgKey;
    
  
  temp=Get_Prepaid_Status();  //本地费控，才显示与电费相关信息;远程费控：此函数不会返回与电费相关信息
  if(temp != PREPAID_MONEY_ENOUGH)
  {
    stat->BuyFee =1;
    if(Light_Mode!= LIGHT_ON_MONEY)
    {
      START_LIGHT_ON;
      Light_Mode=LIGHT_ON_MONEY;
    }
  }
  
  if(temp EQ PREPAID_MONEY_OVERDRAFT  || PREPAID_MONEY_ZERO EQ temp)
  {
    stat->TouZhi =1;
    if(Light_Mode!= LIGHT_ON_MONEY)
    {
      START_LIGHT_ON;
      Light_Mode=LIGHT_ON_MONEY;
    } 
  }
  
  SET_STRUCT_SUM(Meter_Run_Status);  
}

// 获取状态字
stat_t getstat (void) 
{
  static u8 disflag;
  static INT32U SecTimerBak=0;
  u8 temp[13];
  
  u16 data;
  stat_t stat;
  stat.bit1maps = 0;
  stat.bit2maps = 0;
  
  data = 0;
  
  if(poweroff())
  {
    stat.loss_volt_a  = 1;
    stat.loss_volt_b  = 1;
    stat.loss_volt_c  = 1;

  //断相
    stat.cut_volt_a  = 1;
    stat.cut_volt_b  = 1;
    stat.cut_volt_c  = 1;
    
    stat.loss_cut_a  =  1;
    stat.loss_cut_b  =  1;
    stat.loss_cut_c  =  1;    
    stat.fac_status    = ((B_TEST_FAC_STATUS EQ 0) && B_TEST_HARD_STATUS);         //工厂模式
    stat.jumper_short  = ((B_TEST_FAC_STATUS EQ 0) || (B_TEST_HARD_STATUS EQ 0));   //低功耗下，提示跳线块
    stat.num_tariff    =3;  //显示主副时段1：主时段；2：副时段，其他：不显示
    //拉闸
    if(Get_Relay_Status() EQ SWITCH_OFF)
    stat.RelayOff=1;
  
    return (stat);
    
  }
  else
  {
    if(0==disflag)
    {
      SecTimerBak=Sec_Timer_Pub;
      disflag=1;
      Init_Event_DIS_PUCK(&stat); 
      return stat;
    }
    else if(disflag==1 &&Sec_Timer_Pub-SecTimerBak<65)  //事件判定机制还没有走完
    {
       Init_Event_DIS_PUCK(&stat); 
       return stat;
    }
    else
      disflag=2;
  }
  //失压
  stat.loss_volt_a  = Meter_Run_Status.Meter_Stat4.Bit.Bit0;
  stat.loss_volt_b  = Meter_Run_Status.Meter_Stat5.Bit.Bit0;
  stat.loss_volt_c  = Meter_Run_Status.Meter_Stat6.Bit.Bit0;

  //断相
  stat.cut_volt_a  = Meter_Run_Status.Meter_Stat4.Bit.Bit7;
  stat.cut_volt_b  = Meter_Run_Status.Meter_Stat5.Bit.Bit7;
  stat.cut_volt_c  = Meter_Run_Status.Meter_Stat6.Bit.Bit7;
        
    
  //过压
  stat.over_volt_a  = Meter_Run_Status.Meter_Stat4.Bit.Bit2;
  stat.over_volt_b  = Meter_Run_Status.Meter_Stat5.Bit.Bit2;
  stat.over_volt_c  = Meter_Run_Status.Meter_Stat6.Bit.Bit2;
  data = 0;
     
  //getdata(0xC042, &data, &data, sizeof(data));            //12ms
  
  //失流
  stat.loss_cur_a  =  Meter_Run_Status.Meter_Stat4.Bit.Bit3;
  stat.loss_cur_b  =  Meter_Run_Status.Meter_Stat5.Bit.Bit3;
  stat.loss_cur_c  =  Meter_Run_Status.Meter_Stat6.Bit.Bit3;
  

  //断流
  stat.loss_cut_a  =  Read_Event_Status(ID_EVENT_A_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.A<=(Get_Start_Current()*UNIT_A));   //A分相电流小于启动电流;
  stat.loss_cut_b  =  Read_Event_Status(ID_EVENT_B_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.B<=(Get_Start_Current()*UNIT_A)); ;
  stat.loss_cut_c  =  Read_Event_Status(ID_EVENT_C_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.C<=(Get_Start_Current()*UNIT_A)); ;
  
  //电流反极性
  stat.cur_rers_a  =  Meter_Run_Status.Meter_Stat4.Bit.Bit6;
  stat.cur_rers_b  =  Meter_Run_Status.Meter_Stat5.Bit.Bit6;
  stat.cur_rers_c  =  Meter_Run_Status.Meter_Stat6.Bit.Bit6;

  stat.volt_reverse  = Meter_Run_Status.Meter_Stat7.Bit.Bit0; ///< 电压"逆相序"(闪烁)
  stat.curr_reverse  = Meter_Run_Status.Meter_Stat7.Bit.Bit1; ///< 电流"逆相序"(闪烁)

  
  //通信状态指示
  stat.stat_communi  = Get_Curr_ComType_PUCK(LUCK);  //< 通信状态(RS1,RS2,红外)(常亮)
  
  //电池欠压
  stat.cell_low1  = Meter_Run_Status.Meter_Stat1.Bit.Bit2;
  stat.cell_low2  = Meter_Run_Status.Meter_Stat1.Bit.Bit3;
  stat.cell_low3  = 0;
  

  //按钮等提示
  stat.switch_opened = Read_Event_Status(ID_EVENT_PRGKEY_ON); //Meter_Run_Status.Meter_Stat3.Bit.Bit3;     ///< 编程键打开(允许)
  stat.fac_status    = (B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS);      //工厂模式 Meter_Run_Status.Key_Event.Bit.Bit1;       // 工厂模式(常亮)
  stat.reset_demand  = Meter_Run_Status.Key_Event.Bit.Bit2;       //< 需量复位(常亮)
  stat.meter_locked  = Meter_Run_Status.Key_Event.Bit.Bit3;       //< 电表上锁(常亮)
  stat.event_warning = Meter_Run_Status.Key_Event.Bit.Bit4;       //< 事件告警(闪烁)
  stat.jumper_short  = (B_TEST_FAC_STATUS && (B_TEST_HARD_STATUS EQ 0));  //调试模式 Meter_Run_Status.Key_Event.Bit.Bit5;       // 跳线短接(闪烁)
  stat.CalMeter      =Meter_Run_Status.Key_Event.Bit.Bit6;
  
  data = 0;
  //getdata(DI_MODULE_STATUS, &data, &data, sizeof(data));
  data=Meter_Run_Status.Comm_Status.Byte;
  stat.status_online = (data &  0x1); ///< 通讯模块在线指示(常亮)
  stat.signal_scale  = (data >> 0x1); ///< 通讯模块信号强度指示(常亮)
  data = 0;
  
  //< 显示当前费率，"尖, 峰, 平, 谷, T5, ...Tx",
  Get_Cur_Rate_Info(temp,temp,sizeof(temp));
  stat.status_tariff =temp[5]; 
  stat.num_tariff =temp[2]; ///当前运行时段：0第一套，1第二套 
 
  stat.SetpScheme =PREPAID_STEP_SCHEME;                //电价方案：1～2
  stat.SetpRate   =PREPAID_STEP_NO;                    //电价：1～4 

  
  stat.switch_opened =Key_Value_Pub.Key.Bit.PrgKey;
  
  temp[0]=Get_Prepaid_Status();  //本地费控，才显示与电费相关信息;远程费控：此函数不会返回与电费相关信息
  if(temp[0] != PREPAID_MONEY_ENOUGH)
  {
    stat.BuyFee =1;
    if(Light_Mode!= LIGHT_ON_MONEY)
    {
      START_LIGHT_ON;
      Light_Mode=LIGHT_ON_MONEY;
    }
  }
  
  if(temp[0] EQ PREPAID_MONEY_OVERDRAFT  || PREPAID_MONEY_ZERO EQ temp[0])
  {
    stat.TouZhi =1;
    if(Light_Mode!= LIGHT_ON_MONEY)
    {
      START_LIGHT_ON;
      Light_Mode=LIGHT_ON_MONEY;
    } 
  }
  
  //拉闸
  if(Get_Relay_Status() EQ SWITCH_OFF)
    stat.RelayOff=1;
  
  return (stat);
}



char dshift (dval_t* val) {
	  u8 bits = val->low % 16;
	  val->low = (val->high << 28) | (val->low >> 4);    //更新半字节---------PUCK
	  val->high >>= 4;
		return hex2cha[bits];
}

//bit显示方式
char bshift (dval_t* val) 
{
  u8 bits=val->low&0x01;
  val->low=(val->low)>>1;
  return hex2cha[bits];
}

bool isnull (dval_t* val) 
{
  if(Sub_Vlist.exist !=MULIT_EXSIT)
    return ((val->low == 0) && (val->high == 0)&& (val->higher == 0));
  
  u8 *ptr;
  ptr=(u8 *)(val);
  
  if((ptr[0]&0x0f) EQ 0)  //最低半位字节为0，表示最高位为0
    return 1;
 
  return 0;
}



u8 Judge_Ascii_Item(item_t item)
{
  
  if(item>=0x04000403 &&  item<=0x04000408)
    return 1;
  
  if(item>=0x0400040B &&  item<=0x0400040D)
    return 1;
  
  if(item>=0x04800001 &&  item<=0x04800003)
    return 1;
  
  return 0;  
  
}


/********************************************************************************
PUCK:
函数功能：输出显示数据的内容
入口：
     type-----模式参数;curs-----光标位置
返回：
********************************************************************************/
// 输出显示数据的内容
// mode4.bit3 1 "高位补0" : 为0，"高位不补0";
// 电能[协议和显示]小数位[范围: 2或3]
// 功率&需量[显示]小数位[范围: 2或3或4; 协议固定为4]
void lcd_data (item_t item, const char* s) 
{
  INT8S frmt[MAX_DIS_BYTE];

  if(strlen(s)<=sizeof(frmt))
    strcpy(frmt,(INT8S *)s);
  else
  {
    ASSERT_FAILED();
    return ;
  }

 
    
    u8   NegFlag=1;
    static s16    _dlen = 0;
    static item_t _item = 0;
    static dval_t _dval = {0,0,0};
    //显示项目发生改变;上次获取不正确，需要再次获取;是SRAM数据；参数发生修改-------------及时获取显示数据
    //if((_item!= item)||(_dlen == 0)||rtvalue(item)||Get_Para_Modi_Flag())
    if((_item!= item)||rtvalue(item)||Get_Para_Modi_Flag())  //只读一次，读不出，下次不读了
    { 
        _dlen = getdata(item, (INT8U *)Dis_GetData_Buf, (INT8U *)Dis_GetData_Buf, sizeof(Dis_GetData_Buf));     //获取需要显示的变量数据
       // _dlen = getdata(item, &_dval, &_dval, sizeof(_dval));     //获取需要显示的变量数据
        _item = item;
    }
    if (_dlen == 0) {
        lcd_value("rEAd Err|");
        return;
    }
   
    //上次已经获取了数据
    if(Sub_Vlist.exist EQ MULIT_EXSIT)  //更新数据
    {
      mem_cpy(&_dval, (INT8U *)(Dis_GetData_Buf+Sub_Vlist.offset), sizeof(_dval), &_dval, sizeof(_dval));    //将显示格式拷贝到buff---------PUCK
    }
    else
    {
      mem_cpy(&_dval, (INT8U *)Dis_GetData_Buf, sizeof(_dval), &_dval, sizeof(_dval));    //将显示格式拷贝到buff---------PUCK
    }
    
    if(Sub_Vlist.exist EQ MULIT_EXSIT)   //更新格式和显示代码长度
    {
      strcpy(frmt,const_frmt[Sub_Vlist.fmtindex]);
      _dlen=Sub_Vlist.len;
    }
    
    /*
    if(_dlen>0 && singpos==4)  //负数处理
    {
      if(_dval.high&0x00000080)         //最高位位符号位
      {
        _dlen=-1;
        _dval.high=_dval.high&0xffffff7f;         //去掉最高位位符号位    
      }      
    }
    */
    
    Modi_Dis_Unit(item,frmt,sizeof(frmt));
    


    
    char   buff[MAXDLEN] = {0};
    size_t nlen = strlen(frmt);
    dval_t dval = _dval;
    mem_cpy(buff, (char*)frmt, nlen, buff, sizeof(buff));    //将显示格式拷贝到buff---------PUCK
    
    if(Judge_Ascii_Item(item))
    {
      //mem_cpy(buff+1, Dis_GetData_Buf+Sub_Vlist.offset, Sub_Vlist.len, buff+1, sizeof(buff)-2);    //将显示格式拷贝到buff---------PUCK
      mem_set((void *)(buff),' ',sizeof(buff),(void *)(buff),sizeof(buff));   
      if(_dlen<8) //单屏
        Hex_To_Ascii((INT8U *)(Dis_GetData_Buf+_dlen-1),(INT8U *)buff,_dlen,sizeof(buff));
      else          
        Hex_To_Ascii((INT8U *)(Dis_GetData_Buf+_dlen-1),(INT8U *)buff,8,sizeof(buff));
    }
    else
    {        
      for (char* next = buff + nlen; next >= buff; --next)   //反向查找
      {
          switch (*next) 
          {
              case 'X':    //最高位标识
                  if (isnull(&dval))     //高位不补0，且当前数据已是0了，用空格替代-----PUCK
                  {
                    if(-1==_dlen&& 1==NegFlag)   //显示符号
                    {
                      *next = '-';
                      NegFlag=0;
                    }
                    else
                      *next = ' ';
                  } 
                  else    //高位需补0，按照实际填写 
                  {
                      *next = dshift(&dval);  //获取显示的半个字符，逆序放入buff--------PUCK
                  }
                  break;
              case '#': 
                  *next = dshift(&dval);      //获取显示的半个字符，逆序放入buff--------PUCK
                  break;
                 
              case 'B':
                  *next=  bshift(&dval);
                  break;
              case '?': 
                  dshift(&dval);
                   break;
          }
      }
    }
    lcd_value(buff); //此时buff的数据格式：-12.3:-4|单位
}
