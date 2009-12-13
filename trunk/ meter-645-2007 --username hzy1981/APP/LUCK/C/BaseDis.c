
#include "Pub_PUCK.h"



const char* const_frmt[]=
{  
  "XX######|",                        //--------------------0
  "X#.####|kW",                       //�������й�
  "##.##.##.##:##|tm",                //ʱ��
  "X#########|",                     //----------------------3
  "##:##:##|",                      //-------------------4
  "##-##-##|",                      //-------------------5
  "-########-|",                     //��ʾδ����ʾ------------6
  "XXXXX#.####|kvar",                   //�������޹�---------------7
  "XXXXX#.####|kVA",                   //����������--------------8
  "########|",                 //��ʾ������ʾ---------------------9
  "XXXXX#|",                   //��������--------------------10
  "XXXXXXX#.##|",              //-----------------------------11
  "XXXXXXX#.##|kWh",           //--------------------12
  "XXXXXXX#|",                 //--------------------13
  "XXXXXXX#|Ah",                 //--------------------14
  "##-## ##|",                 //--------------------15:ʱ����ʼ���ڼ���ʱ�α��
  "##:## ##|",                 //--------------------16:ʱ����ʼʱ�估���ʺ�
  "XXXX####|",                 //--------------------17:��ʾ2λ
  "##-##-##|tm",        //--------------------18��ʱ��:������
  "##:##|tm",        //--------------------19��ʱ��:ʱ��
  "####|",        //--------------------20
  "##:##:##|tm",        //--------------------21��ʱ��:ʱ����
};


// ʮ������ת�ַ���
static const char hex2cha[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'b', 'C', 'd', 'E', 'F',
};


#define MAX_DIS_BYTE 30
// �й�������ʾ��λ
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

// �޹�������ʾ��λ
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

// ���ڵ�����ʾ��λ
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



// �й�����������ʾ��λ
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

// �޹�������ʾ��λ
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

// ���ڵ�����ʾ��λ
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
  
  
  //������ʾλ��
  if(EnergDisBit != 2 && DI_IS_ENERG(item))  //������ʾС����,���2λ�������ڲ�����ʾ2λ,�޸���Ӧ����ʾ��ʽ
  {
    if(strstr((const INT8S *)Unit, "kWh"))  //������ʾλ�������2λ
    {  
      strcpy(Unit,AC_ENERG_DIS_UNIT[EnergDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kvarh"))  //������ʾλ�������2λ
    {  
      strcpy(Unit,REAC_ENERG_DIS_UNIT[EnergDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kVAh"))  //������ʾλ�������2λ
    {  
      strcpy(Unit,APP_ENERG_DIS_UNIT[EnergDisBit]);
      return ;
    }
  } 
  
  //������ʾλ��
  if(DemandDisBit != 4 &&(DI_IS_DEMAND(item) || DI_IS_INSTANT(item)))  //����������
  {
    if(strstr((const INT8S *)Unit, "kW"))  //������ʾλ�������2λ
    {  
      strcpy(Unit,AC_POWER_DIS_UNIT[DemandDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kvar"))  //������ʾλ�������2λ
    {  
      strcpy(Unit,REAC_POWER_DIS_UNIT[DemandDisBit]);
      return ;
    }
    if(strstr((const INT8S *)Unit, "kVA"))  //������ʾλ�������2λ
    {  
      strcpy(Unit,APP_POWER_DIS_UNIT[DemandDisBit]);
      return ;
    }
  }  
}

// ��ʾ����������
void lcd_update (void) 
{
  UpdataLcdShow();
}

//�� hex ת���� ascii ��
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
  if(CHECK_STRUCT_VAR(Pub_Bit8_Len5_PUCK)==0)//ͷβ����
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Pub_Bit16_Len4_PUCK)==0)//ͷβ����
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Sleep_Sec_Countr)==0)//ͷβ����
  ASSERT_FAILED();
  
  if(CHECK_STRUCT_VAR(Key_Value_Pub)==0)//ͷβ����
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
    //��ѹ
    case 0x02010100:
      *Dst=_PDI_A_VOL;
      return 1;
      
    case 0x02010200:
      *Dst=_PDI_B_VOL;
      return 1;
      
    case 0x02010300:
      *Dst=_PDI_C_VOL;
      return 1;
    
    //����
    case 0x02020100:
       *Dst=_PDI_A_CUR;
      return 1;
      
    case 0x02020200:
       *Dst=_PDI_B_CUR;
      return 1;
      
    case 0x02020300:
       *Dst=_PDI_C_CUR;
       return 1;
    
    //���
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

// ��ȡЭ����������
s16 getdata (item_t item, void* dst, void* dststart, s16 maxlen) 
{ 
  s16 nlen = 0;
  u8  sign=S_INTU;
  u8  temp[6];
  
  if(maxlen>DIS_BUF_LEN)  //Խ�籣��
    return 0;
  
  if (item == DI_CHANEL_IRDA1 || item == DI_CHANEL_IRDA2)   //��һ·ͨ�Ų���
  {
      u32 type = Chanel_Para[CHANEL_IRDA].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  }
  else if (item == DI_CHANEL_485_1)   //��һ·ͨ�Ų���
  {
      u32 type = Chanel_Para[CHANEL_485_1].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  }
  else if (item == DI_CHANEL_485_2)   //�ڶ�·ͨ�Ų���
  {
      u32 type = Chanel_Para[CHANEL_485_2].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  } 

#ifdef CHANEL_MOUDEL 
  else if (item == DI_CHANEL_485_3)   //����·ͨ�Ų���
  {
      u32 type = Chanel_Para[CHANEL_MOUDEL].Baud;
      Hex2Bcd(type, (u8*)dst, sizeof(type), dststart, maxlen);
      nlen = sizeof(u32);
  }
#endif
  /*
  else if((item&0xFFFF00FF)EQ DI_AC_POWER_SUM)  //�й�����,������
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
  else if((item&0xFFFF00FF)EQ DI_REAC_POWER_SUM) //�޹�����,������
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
  else if(item EQ PDI_COMM_ADDR || item EQ PDI_METER_ID) //ͨ�ŵ�ַ
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      
      mem_cpy(temp, (u8 *)dst+4, 2, temp, sizeof(temp));
      mem_cpy(temp+2, dst, 4, temp, sizeof(temp));      
      
      mem_cpy(dst, temp, 6, dststart, sizeof(temp));
  }
  else if((item>=0x04000106) && (item <=0x04000109))//����ʱ�����л�ʱ��/������ʱ�α��л�ʱ�䣺YYMMDDhhmm
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      
      mem_cpy(temp, (u8 *)dst+2, 3, temp, sizeof(temp));      
      mem_cpy(temp+3, dst, 2, temp, sizeof(temp));      
      mem_cpy(dst, temp, 5, dststart, sizeof(temp));
  }
  else if((item EQ 0x10000101)||(item EQ 0x10000201))//���1��ʧѹ����ʱ��/���1��ʧѹ����ʱ��:YYMMDDhhmmsshhmm
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);
      
      mem_cpy(temp, (u8 *)dst+3, 3, temp, sizeof(temp));      
      mem_cpy(temp+3, dst, 3, temp, sizeof(temp));      
      mem_cpy(dst, temp, 6, dststart, sizeof(temp));
  }
  else if(DI_IS_DEMAND(item)) //����
  {
      nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, maxlen ,&sign);  
   
      mem_cpy(temp, (u8 *)dst+5, 3, temp, sizeof(temp));
      mem_cpy(temp+3, (u8 *)dst+3, 2, temp, sizeof(temp));       
      mem_cpy((u8 *)dst+3, temp, 5, dststart, 8);   //8:Ŀ����󳤶�
  }  
  else
  {
    nlen = Get_DLT645_Data_For_Disp(item,(u8*)dst,(u8*)dststart, DIS_BUF_LEN ,&sign);
  }
  nlen=(nlen>maxlen)?maxlen:nlen;
  //mem_cpy(dst, start, nlen, dststart, maxlen);
  mem_set((u8*)dst + nlen, 0, maxlen - nlen, dststart, maxlen);
  
  if(CHECK_STRUCT_VAR(_Dis_GetData_Buf)==0 || nlen==0) //���ͷβ������Խ��
     ASSERT_FAILED();
  
  if(sign!=S_INTS)  //�з���
    return nlen;
  
   
  //�������з������ݴ���
  //�������λ
  if(GET_BIT(*((u8*)dst+nlen-1),7))
  {
    CLR_BIT(*((u8*)dst+nlen-1),7);
    return (-1);
  }
  
  return nlen;  
}

// �ж��Ƿ�ͣ��
bool poweroff (void) 
{
  return (Get_Sys_Status() != SYS_NORMAL);
}

// �ж��Ƿ�Ϊʵʱ����
bool rtvalue (item_t item) 
{
  if(DI_CHANEL_485_1 EQ item || CHANEL_485_2 EQ item)
     return 1;
     
  return (S_RAM == Get_DLT645_Data_Storage_Type(item));
}

/********************************************************************************
PUCK:
�������ܣ��ڿ�����������sram��������ʼ��
��ڣ�
���أ�
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
      temp8=20;  //���������Ѳ������
    }        
    rollcycle=(u8)Bcd2Hex((u8*)&temp8, 1);
      
    
    numb=0;
    temp=Read_Storage_Data(NUMBMODEA,&numb, &numb, sizeof(numb)); 
    if((!temp) ||(!numb))
      numb=0x13;   //BCD��,1�ֽ�------PUCK_LCD
    //numb=0x20;
    MODE_A_NUM = (s16)Bcd2Hex((u8*)&numb, 1);
    
    numb=0;
    temp=Read_Storage_Data(NUMBMODEB,&numb, &numb, sizeof(numb)); 
     if((!temp)||(!numb))
      numb=0x14;   //BCD�룬2�ֽ�------PUCK_LCD
    MODE_B_NUM = (s16)Bcd2Hex((u8*)&numb, 2);
    
    
    temp8=0;
    temp=Read_Storage_Data(PDI_ENERGY_DECIMAL_NUM,&temp8, &temp8, sizeof(temp8)); 
     if((!temp)||(temp8>MAX_DIS_ENERG_BIT))
      temp8=DEFAULT_DIS_ENERG_BIT;   //Ĭ�ϵ�����ʾ3λ,��Χ��0��4
    EnergDisBit = (u8)Bcd2Hex((u8*)&temp8, 1);
    
    
    temp8=0;
    temp=Read_Storage_Data(PDI_POWER_DECIMAL_NUM,&temp8, &temp8, sizeof(temp8)); 
     if((!temp)||(temp8>MAX_DIS_POWER_BIT))
      temp8=DEFAULT_DIS_POWER_BIT;   //����������ʾ4λ,��Χ��0��4
    DemandDisBit = (u8)Bcd2Hex((u8*)&temp8, 1);
    
}

// ѭ��ʱ�䣺��
s16 rolltime () {
    return (rollcycle);
}

// ����Һ������
void lcdlight (u8 stat) {
    if (stat > 0) {
        Turn_Light_On();
    } else {
        Turn_Light_Off();
    }
}


/********************************************************************************
����ԭ�ͣ�void Init_Event_DIS_PUCK(stat_t *stat )
�������ܣ���ʼ���¼�
���ڣ�
*********************************************************************************/
void Init_Event_DIS_PUCK(stat_t *stat)
{  
  INT8U temp;
  //-------------------------����-------------------------  
  stat->cut_volt_a=Get_Event_Instant(ID_EVENT_A_LOSS_PARSE);//A����ࣺ0--û������1----������
  stat->cut_volt_b=Get_Event_Instant(ID_EVENT_B_LOSS_PARSE);//B����ࣺ0--û������1----������
  stat->cut_volt_c=Get_Event_Instant(ID_EVENT_C_LOSS_PARSE);//C����ࣺ0--û������1----������
    
  
  //-------------------------��ѹ-------------------------
  stat->over_volt_a=Get_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD);//A���ѹ��0--û������1----������
  stat->over_volt_b=Get_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);//B���ѹ��0--û������1----������
  stat->over_volt_c=Get_Event_Instant(ID_EVENT_C_VOLT_OVERLOAD);//C���ѹ��0--û������1----������
  
   
    
  //-------------------------ʧ��-------------------------
  stat->loss_cur_a=Get_Event_Instant(ID_EVENT_A_LOSS_CURR);//A��ʧ����0--û������1----������
  stat->loss_cur_b=Get_Event_Instant(ID_EVENT_B_LOSS_CURR);//B��ʧ����0--û������1----������
  stat->loss_cur_c=Get_Event_Instant(ID_EVENT_C_LOSS_CURR);//C��ʧ����0--û������1----������
  

  //-------------------------��������-------------------------
  stat->cur_rers_a=Get_Event_Instant(ID_EVENT_A_NEG_CURR);//A��������ࣺ0--û������1----������
  stat->cur_rers_b=Get_Event_Instant(ID_EVENT_B_NEG_CURR);//B��������ࣺ0--û������1----������
  stat->cur_rers_c=Get_Event_Instant(ID_EVENT_C_NEG_CURR);//C��������ࣺ0--û������1----������
  
  
  //-------------------------����-------------------------
  //����
  stat->loss_cut_a  =  Read_Event_Status(ID_EVENT_A_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.A<=(Get_Start_Current()*UNIT_A));   //A�������С����������;
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
  
  
  //����  
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit0=0;  //���������1��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit1=0;  //���������2:
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit2=0;  //���������3��
  Meter_Run_Status.NegCurr_Qudrant.Bit.Bit3=0;  //���������4��
      
  if((FP32S)Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B\
                       ,Measu_InstantData_ToPub_PUCK.Curr.C)>(Get_Start_Current()*UNIT_A))  //������������������
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


  stat->jumper_short  = (B_TEST_FAC_STATUS && (B_TEST_HARD_STATUS EQ 0));     //����ģʽ
  stat->fac_status    = ((B_TEST_FAC_STATUS EQ 0) && B_TEST_HARD_STATUS);      //����ģʽ
  stat->switch_opened =  Key_Value_Pub.Key.Bit.PrgKey;
    
  
  temp=Get_Prepaid_Status();  //���طѿأ�����ʾ���������Ϣ;Զ�̷ѿأ��˺������᷵�����������Ϣ
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

// ��ȡ״̬��
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

  //����
    stat.cut_volt_a  = 1;
    stat.cut_volt_b  = 1;
    stat.cut_volt_c  = 1;
    
    stat.loss_cut_a  =  1;
    stat.loss_cut_b  =  1;
    stat.loss_cut_c  =  1;    
    stat.fac_status    = ((B_TEST_FAC_STATUS EQ 0) && B_TEST_HARD_STATUS);         //����ģʽ
    stat.jumper_short  = ((B_TEST_FAC_STATUS EQ 0) || (B_TEST_HARD_STATUS EQ 0));   //�͹����£���ʾ���߿�
    stat.num_tariff    =3;  //��ʾ����ʱ��1����ʱ�Σ�2����ʱ�Σ�����������ʾ
    //��բ
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
    else if(disflag==1 &&Sec_Timer_Pub-SecTimerBak<65)  //�¼��ж����ƻ�û������
    {
       Init_Event_DIS_PUCK(&stat); 
       return stat;
    }
    else
      disflag=2;
  }
  //ʧѹ
  stat.loss_volt_a  = Meter_Run_Status.Meter_Stat4.Bit.Bit0;
  stat.loss_volt_b  = Meter_Run_Status.Meter_Stat5.Bit.Bit0;
  stat.loss_volt_c  = Meter_Run_Status.Meter_Stat6.Bit.Bit0;

  //����
  stat.cut_volt_a  = Meter_Run_Status.Meter_Stat4.Bit.Bit7;
  stat.cut_volt_b  = Meter_Run_Status.Meter_Stat5.Bit.Bit7;
  stat.cut_volt_c  = Meter_Run_Status.Meter_Stat6.Bit.Bit7;
        
    
  //��ѹ
  stat.over_volt_a  = Meter_Run_Status.Meter_Stat4.Bit.Bit2;
  stat.over_volt_b  = Meter_Run_Status.Meter_Stat5.Bit.Bit2;
  stat.over_volt_c  = Meter_Run_Status.Meter_Stat6.Bit.Bit2;
  data = 0;
     
  //getdata(0xC042, &data, &data, sizeof(data));            //12ms
  
  //ʧ��
  stat.loss_cur_a  =  Meter_Run_Status.Meter_Stat4.Bit.Bit3;
  stat.loss_cur_b  =  Meter_Run_Status.Meter_Stat5.Bit.Bit3;
  stat.loss_cur_c  =  Meter_Run_Status.Meter_Stat6.Bit.Bit3;
  

  //����
  stat.loss_cut_a  =  Read_Event_Status(ID_EVENT_A_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.A<=(Get_Start_Current()*UNIT_A));   //A�������С����������;
  stat.loss_cut_b  =  Read_Event_Status(ID_EVENT_B_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.B<=(Get_Start_Current()*UNIT_A)); ;
  stat.loss_cut_c  =  Read_Event_Status(ID_EVENT_C_CUT_CURR)|(Measu_InstantData_ToPub_PUCK.Curr.C<=(Get_Start_Current()*UNIT_A)); ;
  
  //����������
  stat.cur_rers_a  =  Meter_Run_Status.Meter_Stat4.Bit.Bit6;
  stat.cur_rers_b  =  Meter_Run_Status.Meter_Stat5.Bit.Bit6;
  stat.cur_rers_c  =  Meter_Run_Status.Meter_Stat6.Bit.Bit6;

  stat.volt_reverse  = Meter_Run_Status.Meter_Stat7.Bit.Bit0; ///< ��ѹ"������"(��˸)
  stat.curr_reverse  = Meter_Run_Status.Meter_Stat7.Bit.Bit1; ///< ����"������"(��˸)

  
  //ͨ��״ָ̬ʾ
  stat.stat_communi  = Get_Curr_ComType_PUCK(LUCK);  //< ͨ��״̬(RS1,RS2,����)(����)
  
  //���Ƿѹ
  stat.cell_low1  = Meter_Run_Status.Meter_Stat1.Bit.Bit2;
  stat.cell_low2  = Meter_Run_Status.Meter_Stat1.Bit.Bit3;
  stat.cell_low3  = 0;
  

  //��ť����ʾ
  stat.switch_opened = Read_Event_Status(ID_EVENT_PRGKEY_ON); //Meter_Run_Status.Meter_Stat3.Bit.Bit3;     ///< ��̼���(����)
  stat.fac_status    = (B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS);      //����ģʽ Meter_Run_Status.Key_Event.Bit.Bit1;       // ����ģʽ(����)
  stat.reset_demand  = Meter_Run_Status.Key_Event.Bit.Bit2;       //< ������λ(����)
  stat.meter_locked  = Meter_Run_Status.Key_Event.Bit.Bit3;       //< �������(����)
  stat.event_warning = Meter_Run_Status.Key_Event.Bit.Bit4;       //< �¼��澯(��˸)
  stat.jumper_short  = (B_TEST_FAC_STATUS && (B_TEST_HARD_STATUS EQ 0));  //����ģʽ Meter_Run_Status.Key_Event.Bit.Bit5;       // ���߶̽�(��˸)
  stat.CalMeter      =Meter_Run_Status.Key_Event.Bit.Bit6;
  
  data = 0;
  //getdata(DI_MODULE_STATUS, &data, &data, sizeof(data));
  data=Meter_Run_Status.Comm_Status.Byte;
  stat.status_online = (data &  0x1); ///< ͨѶģ������ָʾ(����)
  stat.signal_scale  = (data >> 0x1); ///< ͨѶģ���ź�ǿ��ָʾ(����)
  data = 0;
  
  //< ��ʾ��ǰ���ʣ�"��, ��, ƽ, ��, T5, ...Tx",
  Get_Cur_Rate_Info(temp,temp,sizeof(temp));
  stat.status_tariff =temp[5]; 
  stat.num_tariff =temp[2]; ///��ǰ����ʱ�Σ�0��һ�ף�1�ڶ��� 
 
  stat.SetpScheme =PREPAID_STEP_SCHEME;                //��۷�����1��2
  stat.SetpRate   =PREPAID_STEP_NO;                    //��ۣ�1��4 

  
  stat.switch_opened =Key_Value_Pub.Key.Bit.PrgKey;
  
  temp[0]=Get_Prepaid_Status();  //���طѿأ�����ʾ���������Ϣ;Զ�̷ѿأ��˺������᷵�����������Ϣ
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
  
  //��բ
  if(Get_Relay_Status() EQ SWITCH_OFF)
    stat.RelayOff=1;
  
  return (stat);
}



char dshift (dval_t* val) {
	  u8 bits = val->low % 16;
	  val->low = (val->high << 28) | (val->low >> 4);    //���°��ֽ�---------PUCK
	  val->high >>= 4;
		return hex2cha[bits];
}

//bit��ʾ��ʽ
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
  
  if((ptr[0]&0x0f) EQ 0)  //��Ͱ�λ�ֽ�Ϊ0����ʾ���λΪ0
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
�������ܣ������ʾ���ݵ�����
��ڣ�
     type-----ģʽ����;curs-----���λ��
���أ�
********************************************************************************/
// �����ʾ���ݵ�����
// mode4.bit3 1 "��λ��0" : Ϊ0��"��λ����0";
// ����[Э�����ʾ]С��λ[��Χ: 2��3]
// ����&����[��ʾ]С��λ[��Χ: 2��3��4; Э��̶�Ϊ4]
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
    //��ʾ��Ŀ�����ı�;�ϴλ�ȡ����ȷ����Ҫ�ٴλ�ȡ;��SRAM���ݣ����������޸�-------------��ʱ��ȡ��ʾ����
    //if((_item!= item)||(_dlen == 0)||rtvalue(item)||Get_Para_Modi_Flag())
    if((_item!= item)||rtvalue(item)||Get_Para_Modi_Flag())  //ֻ��һ�Σ����������´β�����
    { 
        _dlen = getdata(item, (INT8U *)Dis_GetData_Buf, (INT8U *)Dis_GetData_Buf, sizeof(Dis_GetData_Buf));     //��ȡ��Ҫ��ʾ�ı�������
       // _dlen = getdata(item, &_dval, &_dval, sizeof(_dval));     //��ȡ��Ҫ��ʾ�ı�������
        _item = item;
    }
    if (_dlen == 0) {
        lcd_value("rEAd Err|");
        return;
    }
   
    //�ϴ��Ѿ���ȡ������
    if(Sub_Vlist.exist EQ MULIT_EXSIT)  //��������
    {
      mem_cpy(&_dval, (INT8U *)(Dis_GetData_Buf+Sub_Vlist.offset), sizeof(_dval), &_dval, sizeof(_dval));    //����ʾ��ʽ������buff---------PUCK
    }
    else
    {
      mem_cpy(&_dval, (INT8U *)Dis_GetData_Buf, sizeof(_dval), &_dval, sizeof(_dval));    //����ʾ��ʽ������buff---------PUCK
    }
    
    if(Sub_Vlist.exist EQ MULIT_EXSIT)   //���¸�ʽ����ʾ���볤��
    {
      strcpy(frmt,const_frmt[Sub_Vlist.fmtindex]);
      _dlen=Sub_Vlist.len;
    }
    
    /*
    if(_dlen>0 && singpos==4)  //��������
    {
      if(_dval.high&0x00000080)         //���λλ����λ
      {
        _dlen=-1;
        _dval.high=_dval.high&0xffffff7f;         //ȥ�����λλ����λ    
      }      
    }
    */
    
    Modi_Dis_Unit(item,frmt,sizeof(frmt));
    


    
    char   buff[MAXDLEN] = {0};
    size_t nlen = strlen(frmt);
    dval_t dval = _dval;
    mem_cpy(buff, (char*)frmt, nlen, buff, sizeof(buff));    //����ʾ��ʽ������buff---------PUCK
    
    if(Judge_Ascii_Item(item))
    {
      //mem_cpy(buff+1, Dis_GetData_Buf+Sub_Vlist.offset, Sub_Vlist.len, buff+1, sizeof(buff)-2);    //����ʾ��ʽ������buff---------PUCK
      mem_set((void *)(buff),' ',sizeof(buff),(void *)(buff),sizeof(buff));   
      if(_dlen<8) //����
        Hex_To_Ascii((INT8U *)(Dis_GetData_Buf+_dlen-1),(INT8U *)buff,_dlen,sizeof(buff));
      else          
        Hex_To_Ascii((INT8U *)(Dis_GetData_Buf+_dlen-1),(INT8U *)buff,8,sizeof(buff));
    }
    else
    {        
      for (char* next = buff + nlen; next >= buff; --next)   //�������
      {
          switch (*next) 
          {
              case 'X':    //���λ��ʶ
                  if (isnull(&dval))     //��λ����0���ҵ�ǰ��������0�ˣ��ÿո����-----PUCK
                  {
                    if(-1==_dlen&& 1==NegFlag)   //��ʾ����
                    {
                      *next = '-';
                      NegFlag=0;
                    }
                    else
                      *next = ' ';
                  } 
                  else    //��λ�貹0������ʵ����д 
                  {
                      *next = dshift(&dval);  //��ȡ��ʾ�İ���ַ����������buff--------PUCK
                  }
                  break;
              case '#': 
                  *next = dshift(&dval);      //��ȡ��ʾ�İ���ַ����������buff--------PUCK
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
    lcd_value(buff); //��ʱbuff�����ݸ�ʽ��-12.3:-4|��λ
}
