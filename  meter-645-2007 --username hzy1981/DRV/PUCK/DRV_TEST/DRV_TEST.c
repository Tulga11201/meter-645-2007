

#define DRV_TEST_C
#include "Pub_PUCK.h"

#ifdef DRV_TEST_EN


#define TEST_TEMP_LEN 20
INT8U Test_Temp_Buf[TEST_TEMP_LEN];
#define TEST_BUF_LEN 10

static INT8U KeyNum=0;
const INT8U TEST_INFO[2][9]={"Failed ","Succeed"};
static INT32U Temp_Timer_Bak=0;

#define ID_TEST_EXT_U10 ID_MEM_IIC_U10  //0
#define ID_TEST_EXT_U11 ID_MEM_IIC_U11
#define ID_TEST_EXT_U12 ID_MEM_IIC_U12
#define ID_TEST_EXT_U14 ID_MEM_IIC_U14
#define ID_TEST_EXT_U15 ID_MEM_IIC_U15
#define ID_TEST_EXT_U8  (ID_TEST_EXT_U15+1)
#define ID_TEST_MEASURE (ID_TEST_EXT_U8+1)
#define ID_TEST_EXT_RTC (ID_TEST_MEASURE+1)
#define ID_TEST_INTER_RTC (ID_TEST_EXT_RTC+1)
//#define ID_TEST_EXT_U27 (ID_TEST_EXT_U8+1)
#define MAX_ID_TEST_NUM (ID_TEST_INTER_RTC+1)

#define MAX_MEM_NUM (MAX_EPPROM_NUM+1)  //���˸�flash
INT16U const TEST_ADDR[5]={U10_SIZE-10,U12_SIZE-10,U12_SIZE-10,U14_SIZE-10,U15_SIZE-10};  

#define TEST_FLASH_ADDR  (0x100000-10)

INT8U const  *Const_Drv_Test[MAX_ID_TEST_NUM]=
{
#ifdef ID_TEST_EXT_U10
  "U10",    //�ⲿ�����ű������------0
#endif
#ifdef ID_TEST_EXT_U11
  "U11",
#endif
#ifdef ID_TEST_EXT_U12
  "U12",
#endif
#ifdef ID_TEST_EXT_U14
  "U14",
#endif
#ifdef ID_TEST_EXT_U15
  "U15",
#endif
#ifdef ID_TEST_EXT_U8
  "U 8",
#endif
#ifdef ID_TEST_MEASURE
  "7022",
#endif
#ifdef ID_TEST_EXT_RTC
  "3231",
#endif
#ifdef ID_TEST_INTER_RTC
  "F5Ub"
#endif
};

DECLARE_BUF_TYPE(INT8U,MAX_ID_TEST_NUM,S_Buf_TEST);
static S_Buf_TEST  S_Buf_Test={CHK_BYTE,{0},CHK_BYTE};
#define Drv_Test_Buf S_Buf_Test.Buf
  

/**********************************************************************************
����ʱ10���룬��ι��

***********************************************************************************/
/**********************************************************************************/
void Dlyn10MS_ClrDog(INT32U n)
{
  INT32U i;
  for(i=0;i<n;i++)
  {
    if(i%10==0)  //100msι��һ��
    {
      Clr_Ext_Inter_Dog();
    }
    WAITFOR_DRV_MS_TIMEOUT(10);
  }
}
/**********************************************************************************
����1ms�ڵ�nop��
**********************************************************************************/
INT32U Get_Counts_1MS(void)
{
  INT32U i;  
  
  for(i=0,Temp_Timer_Bak=Ms_Timer_Pub=0;;i++)  //�����1ms�ڵ�nop��Ŀ
  {
    if(Temp_Timer_Bak!=Ms_Timer_Pub)
      break;
  }
  
  i=i*15;
  DEBUG_PRINT(PUCK,1,"NOP Counts=%ld In 1MS",i);
  return i;
}

/**********************************************************************************
����Һ��
**********************************************************************************/
void Test_CPU_Output_IO(void)
{
  static INT8U ChkFlag=0;
  
  ChkFlag=!ChkFlag;
  if(ChkFlag)
  {
    DEBUG_PRINT(PUCK,1,"Trun On All IO,IO=1");
    IRDA_NEAR_REC_EN;         //          B_ird_chose_1     //Զ����رգ��������⿪��
    BAK_POWER_FOR_IRDA;       //        B_ird_pow_1       //Զ�����Դ�ɵ͹��ĵ�ع���;
    BAK_POWER_FOR_LCD;        //        LCD_POW_1         //LCD��Դ�ɵ͹��ĵ�ع���;
    BAK_POWER_FOR_MEM;        //        EEPOWER_1         //�ڿ���Դ�ɵ͹��ĵ�ع���;
    OPEN_MEASU_PWR;           //          ����оƬ��Դ����
    
    EXT_ALARM_SET;            //�����ű���
    EXT_SWITCH_SET;
    IRDA_SEND_EN;   //���ⷢ��ʹ��
    IRDA_SEND_DIS;  ///���ⷢ�ͽ�ֹ
    IRDA_NEAR_REC_EN;//          B_ird_chose_1     //Զ����رգ��������⿪��
     //���������޹��������ָʾ
    A_DIR_1;
    R_DIR_1;
    A_OUT_1;    
    R_OUT_1;
    
    //�й����������
    MEASU_A_DIR_1;  
   //�޹����������    
    MEASU_R_DIR_1;
    
    DEBUG_PRINT(PUCK,1,"Trun Off All IO,IO=0");
    IRDA_FAR_REC_EN;         //          B_ird_chose_0      //Զ���⿪������������ر�
    MAIN_POWER_FOR_IRDA;      //       B_ird_pow_0       //Զ�����Դ������Դ����;
    MAIN_POWER_FOR_LCD;     //       LCD_POW_0         //LCD��Դ������Դ����;
    MAIN_POWER_FOR_MEM;     //       EEPOWER_0         //�ڿ���Դ������Դ����;
    CLOSE_MEASU_PWR;
   
    EXT_ALARM_CLR;
    EXT_SWITCH_CLR;
    IRDA_FAR_REC_EN;//          B_ird_chose_0      //Զ���⿪������������ر�
    
    A_DIR_0;
    R_DIR_0;
    A_OUT_0;
    R_OUT_0;
    
    
    MEASU_A_DIR_0;
    MEASU_R_DIR_0;
  }
}

/**********************************************************************************
����Һ��
**********************************************************************************/
void Test_CPU_Input_IO(void)
{
 
   DEBUG_PRINT(PUCK,1,"GUMB IO=%d",GUMB_STATUS);
   DEBUG_PRINT(PUCK,1,"Power_Down IO=%d",POWER_OFF_STATUS); 
}
/**********************************************************************************
����UART
**********************************************************************************/
void Test_UART(void)
{
  INT8U i;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)  //ע�⣬�ں����Կڵ��ظ���ʼ����
  {
    Open_Channel_PUCK(i,4800,SAU_PARITY_NONE); 
    Channel_DataSend_PUCK(i,"123456ABCDEF",12);
  }
  Init_DebugChanel_PUCK(1);
  Init_DebugChanel_PUCK(1);
}
/**********************************************************************************
����Һ��
**********************************************************************************/
void Test_Lcd(void)
{
  INT8U i;
  
 //DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Test LCD��Please Watch LCD and Judge Result!"); 
  
  mem_set(Temp_Buf_PUCK,0x00,sizeof(Temp_Buf_PUCK),Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  strcpy((char *)Temp_Buf_PUCK,"dEbU6-----");
  
  //BAK_POWER_FOR_LCD;//        LCD_POW_1         //LCD��Դ�ɵ͹��ĵ�ع���;
  MAIN_POWER_FOR_LCD;//       LCD_POW_0         //LCD��Դ������Դ����;
  
  InitLcdAllRam();
  Init_HTLCD_Mode(SYS_NORMAL);
  Turn_Light_On();
  
  for(i=0;i<=9;i++)
     SetOnLED8Device_PUCK(N_LED(i+3),Temp_Buf_PUCK[i]);
  UpdataLcdShow();    
}
/**********************************************************************************
���Լ���
**********************************************************************************/
#define MEASU_TEST_NUM 3
void Test_Measure(void)
{
  INT32U temp[3];
  INT8U i,Flag=1;
  
  
  OPEN_MEASU_PWR;//       LCD_POW_0         //LCD��Դ������Դ����;
  Dlyn10MS_ClrDog(1);
  MEASU_RST_0;
  Dlyn10MS_ClrDog(1);
  MEASU_RST_1;
  Dlyn10MS_ClrDog(100);
  
 
  
  for(i=0;i<3;i++)
  {
    Flag&=Measu_RdAndCompData_3Times(REG_R_A_U+i,(INT8U *)&temp[i]);
    temp[i]/=UNIT_V;
  }
  
  Drv_Test_Buf[ID_TEST_MEASURE]=Flag;
  
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|-----------------------Test Measure IC-------------------------------|");
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"| Total Times    Volt_A(V)       Volt_B(V)    Volt_C(V)     Result    |");
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|         %3d          %3ld             %3ld          %3ld     %s   |",\
                          MEASU_TEST_NUM,temp[0],temp[1],temp[2],TEST_INFO[Drv_Test_Buf[ID_TEST_MEASURE]]); 
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|---------------------------------------------------------------------|"); 
}
/**********************************************************************************
RtcFlag:1----------------�ⲿRTC��0--------------�ڲ�RTC
�����ⲿRTC
���Խ��ۣ���д����65536�Σ�ʵ�黨��ʱ��Ϊ142460ms��������дһ�Σ�����ʱ��Ϊ2.17ms
**********************************************************************************/
#define RTC_TEST_NUM 20
void Test_All_RTC(INT8U RtcFlag)
{
  INT8U Temp[7],Flag;
  INT16U i,RdWrErr=0,CompErr=0;
  INT32U timr;
  
  if(!((RtcFlag==ID_TEST_EXT_RTC)||(RtcFlag==ID_TEST_INTER_RTC)))
  {
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"Test RTC ID Error!");
    return ;
  }
  
  if(RtcFlag==ID_TEST_EXT_RTC)
  {
    Init_DS3231_IIC_Soft();
    DS3231_SecPulse_Ctrl(1);   //���������
    Flag=Read_ExtRTC_PUCK(Temp,7);
    Flag&=Check_BCD_Data(Temp,7);//������ݸ�ʽ?
    if(!Flag)     //�������ԣ�дһ����ʱʱ��
    {
      Temp[6]=0x08;Temp[6]=0x08;Temp[6]=0x08;Temp[6]=0x01;Temp[6]=0x08;Temp[6]=0x13;Temp[6]=0x04;
      Write_InterRTC_PUCK(Temp);      
    }
  }
  else
  {
    if(Drv_Test_Buf[ID_TEST_EXT_RTC]==0)  //�ⲿRTC����
    {
      Temp[6]=0x08;Temp[6]=0x08;Temp[6]=0x08;Temp[6]=0x01;Temp[6]=0x08;Temp[6]=0x13;Temp[6]=0x00;
    }
    else
    {
      Read_ExtRTC_PUCK(Temp,7);
      Temp[1]=0x13;
    }
    Write_InterRTC_PUCK(Temp);    
  }
  Temp_Timer_Bak=Ms_Timer_Pub; //�����鿴���ѵ�ʱ��
  //��д����65535�Σ�ʵ�黨��ʱ��ΪMs10_Timer_Pub=142460ms��������дһ�Σ�����ʱ��Ϊ2.17ms---------PUCK
  for(i=0;i<RTC_TEST_NUM-1;i++)
  //while(1)
  {
    mem_set(Temp,0,sizeof(Temp),Temp,sizeof(Temp));
    if(RtcFlag==ID_TEST_EXT_RTC)
      Flag=!Read_ExtRTC_PUCK(Temp,7);
    else
      Flag=!Read_InterRTC_PUCK(Temp,7);
    Flag|=!Check_BCD_Data(Temp,7);//������ݸ�ʽ?
    RdWrErr+=Flag;
    
    Temp[0]=0x23;
    if(RtcFlag==ID_TEST_EXT_RTC)
      Flag=!Write_ExtRTC_PUCK(Temp);
    else
      Flag=!Write_InterRTC_PUCK(Temp); 
    RdWrErr+=Flag;
  }
  timr=Ms_Timer_Pub-Temp_Timer_Bak;
  
  Dlyn10MS_ClrDog(300);
  if(RtcFlag==ID_TEST_EXT_RTC)
    Flag=!Read_ExtRTC_PUCK(Temp,7);
  else
    Flag=!Read_InterRTC_PUCK(Temp,7);
  Flag|=!Check_BCD_Data(Temp,7);//������ݸ�ʽ?
  if(!((Temp[0]>0x24)&&(Temp[0]<0x28)))
    Flag=1;
  CompErr+=Flag;  //�Աȴ���

   Drv_Test_Buf[RtcFlag]=!(RdWrErr|CompErr);

  if(RtcFlag==ID_TEST_EXT_RTC)
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|-----------------------Test Extern RTC-------------------------------|");
  else
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|------------------------Test Internal RTC----------------------------|");
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"| Total Times    Run Time(MS)      RdWr_Err    Compa_Err    Result    |");
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|         %3d      %9ld            %3d          %3d    %s   |",\
                          RTC_TEST_NUM,timr,RdWrErr,CompErr,TEST_INFO[Drv_Test_Buf[RtcFlag]]); 
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|Current Time(Yea-Mon-Dat_Day_Hou:Min:Sec):%2x-%2x-%2x_%2x_%2x:%2x:%2x       |",\
                          Temp[6],Temp[5],Temp[4],Temp[3],Temp[2],Temp[1],Temp[0]);
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|---------------------------------------------------------------------|"); 
}
/**********************************************************************************
����EPPROM
**********************************************************************************/
#define   EPPROM_TEST_NUM 10
void Test_Memory(void)
{
  INT8U j,Flag,RandBuf[TEST_BUF_LEN];
  INT16U i;
  INT32U timr;  
  static INT16U RdErr[MAX_MEM_NUM],WrErr[MAX_MEM_NUM],CompareErr[MAX_MEM_NUM];
    
  mem_set(Drv_Test_Buf+ID_TEST_EXT_U10,0x01,MAX_MEM_NUM,Drv_Test_Buf+ID_TEST_EXT_U10,MAX_MEM_NUM);
  Temp_Timer_Bak=Ms_Timer_Pub; //�����鿴���ѵ�ʱ��
  for(i=0;i<EPPROM_TEST_NUM;i++)
  {
    mem_set(RandBuf,0x55+i,sizeof(RandBuf),RandBuf,sizeof(RandBuf));
    for(j=ID_TEST_EXT_U10;j<=ID_MEM_IIC_U15;j++)
    {  
      Flag=!Write_EEPROM_Dvice_PUCK(j,TEST_ADDR[j],TEST_BUF_LEN,RandBuf);
      WrErr[j]+=Flag;
  
      mem_set(Test_Temp_Buf,0x33,sizeof(Test_Temp_Buf),Test_Temp_Buf,sizeof(Test_Temp_Buf));
      Flag=!Read_EEPROM_Dvice_PUCK(j,TEST_ADDR[j],TEST_BUF_LEN,Test_Temp_Buf);
      RdErr[j]+=Flag;
     
      if((memcmp(Test_Temp_Buf,RandBuf,TEST_BUF_LEN)!=0)||(Test_Temp_Buf[TEST_BUF_LEN]!=0x33))//�Ƚ���ȣ����ײ㲻�ܶ�д���Խ�磡
       CompareErr[j]++;
      
     if(RdErr[j]|WrErr[j]|CompareErr[j])   //������һ�����������ñ�־ʧ�ܱ�־
      Drv_Test_Buf[j]=0;
    }
    
    Flag=!flash_writ_abs(TEST_FLASH_ADDR,RandBuf,TEST_BUF_LEN);
    WrErr[j]+=Flag;

    mem_set(Test_Temp_Buf,0x33,sizeof(Test_Temp_Buf),Test_Temp_Buf,sizeof(Test_Temp_Buf));
    Flag=!flash_read_abs(TEST_FLASH_ADDR,Test_Temp_Buf,TEST_BUF_LEN);
    RdErr[j]+=Flag;
   
    if((memcmp(Test_Temp_Buf,RandBuf,TEST_BUF_LEN)!=0)||(Test_Temp_Buf[TEST_BUF_LEN]!=0x33))//�Ƚ���ȣ����ײ㲻�ܶ�д���Խ�磡//�Ƚ�
    CompareErr[j]++; 
     
   if(RdErr[ID_TEST_EXT_U8]|WrErr[ID_TEST_EXT_U8]|CompareErr[ID_TEST_EXT_U8])  //������һ�����������ñ�־ʧ��
    Drv_Test_Buf[ID_TEST_EXT_U8]=0;
  }

  timr=Ms_Timer_Pub-Temp_Timer_Bak;
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|-----------------------Test Memory-----------------------------------|");
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"| Total_Times      Read_Err        Write_Err   Compare_Err  Result    |");
  
  for(j=ID_TEST_EXT_U10;j<=ID_TEST_EXT_U8;j++)
    DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|%s      %3d           %3d              %3d           %3d  %s   |",\
                          Const_Drv_Test[j],EPPROM_TEST_NUM,RdErr[j],WrErr[j],CompareErr[j],TEST_INFO[Drv_Test_Buf[j]]);
 
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|       All Run Time=%9ldMS                                      |",timr); 
  DEBUG_PRINT(PUCK,PRINT_PUCK_MEA_EN,"|---------------------------------------------------------------------|"); 
}

/**********************************************************************************
����EPPROM
**********************************************************************************/
void Test_Epprom_Err(void)
{  
  INT8U Err;  
  mem_set(Temp_Buf_PUCK,0xa5,sizeof(Temp_Buf_PUCK),Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  I2cReset();
  Read_Storage_Data(0x10003,Temp_Buf_PUCK,Temp_Buf_PUCK,180,&Err);
  
}
/**********************************************************************************
LCD��ʾÿ�����
**********************************************************************************/
void Dis_Per_Item(INT8U Item)
{
  INT8U i;
    
  if(Item>=MAX_ID_TEST_NUM)
    return ;
  
  if(Drv_Test_Buf[Item]>1)
    return ;
  
  mem_set(Temp_Buf_PUCK,0x00,sizeof(Temp_Buf_PUCK),Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  strcpy((char *)Temp_Buf_PUCK,(char*)Const_Drv_Test[Item]);
  
  if(Drv_Test_Buf[Item]==0)
   strcpy((char *)Temp_Buf_PUCK+5,"Error");
  else
   strcpy((char *)Temp_Buf_PUCK+5," 6ood");
  
  for(i=3;i<=12;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-3]);
  
  SetOnLED8Device_PUCK(N_LED(20),Item/10+'0');
  SetOnLED8Device_PUCK(N_LED(21),Item%10+'0');
  UpdataLcdShow();
}
/**********************************************************************************
LCD��ʾ������
**********************************************************************************/
void LCD_Dis_Result(void)
{  
  INT8U KeyValue;
  
  KeyValue=Get_MeterKey_PUCK(LUCK);
  switch(KeyValue)    //���»�ȡ�������ʵԪ����Ϣ------------PUCK
  {
        case UP_KEY_VALUE :
        case RIGHT_KEY_VALUE:
            Turn_Light_On();
            KeyNum++;
            if(KeyNum>=MAX_ID_TEST_NUM)
              KeyNum=0;
            Dis_Per_Item(KeyNum);
            Temp_Timer_Bak=Sec_Timer_Pub;
              break;
 
        case DOWN_KEY_VALUE:
        case LEFT_KEY_VALUE:
            Turn_Light_On();
            if(KeyNum==0)
              KeyNum=MAX_ID_TEST_NUM-1;
            KeyNum--;
            Dis_Per_Item(KeyNum);
            Temp_Timer_Bak=Sec_Timer_Pub;
             break;
        default:
          if(Sec_Timer_Pub-Temp_Timer_Bak>3)
          {
            if(KeyNum>=MAX_ID_TEST_NUM)
              KeyNum=0;
            KeyNum++;
            if(KeyNum%2)
              Turn_Light_Off();
            else
              Turn_Light_On();
              
            Dis_Per_Item(KeyNum);
            Temp_Timer_Bak=Sec_Timer_Pub;
            Test_CPU_Output_IO();
            Test_CPU_Input_IO();
          }
          break;            
   }
  
}
/**********************************************************************************
LCD��ʾ������
**********************************************************************************/
void Test_Sleep(void)
{
  /* while(1)
   {
      //Clear_CPU_Dog();    //��CPU�ڲ����Ź�
      Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
      
   }*/
   
  
  /*TAU_Init();
  START_IRDA;
  START_ALL_LOSS;
  DS3231_SecPulse_Ctrl(1);        //ʹ��������----PUCK
  START_1HZ;
  while(1)
  DEBUG_PRINT(PUCK,1,"Enter Into Halt Mode!");
  Init_All_UART(SYS_SLEEP);       //˯��ģʽ�µĴ��ڳ�ʼ��,��ӡ������Ϣ�ķ���
  Init_Inter_Abs(SYS_SLEEP);
  STOP_ALL_LOSS;
  STOPT_RTC_COUNTER; STOP_RTC_ALARM;
  STOP_IRDA;
  Clr_Ext_Inter_Dog();
  //Init_All_IO_Sleep();
  Goto_Sleep_PUCK();
  //P5|=0x08;
  //PM5|=0x08;
  if(Switch_Main_Osc(RUN_MODE))  
  {
    
    //Init_All_UART(SYS_NORMAL);
    //DEBUG_PRINT(PUCK,1,"Wake Up From Halt Mode!");
    while(1)
    {
      Clear_CPU_Dog();    //��CPU�ڲ����Ź�
      //Clear_Ext_Dog();    //��CPU�ⲿ���Ź�
      
    }
    START_1MS;
    START_PMW;
  };*/
}
#endif
/**********************************************************************************
����EPPROM
**********************************************************************************/
void Test_HardWare_PUCK(void)
{  
#ifdef DRV_TEST_EN

  /*while(1)
    Clr_Ext_Inter_Dog();
  */
  if(B_TEST_FAC_STATUS||B_TEST_HARD_STATUS)
    return ;
  
  if(POWER_OFF_STATUS==0)  //������
    return ;

  
  Test_Lcd();
  Clr_Ext_Inter_Dog();
  
  Test_Measure();
  Clr_Ext_Inter_Dog();
  
  Test_All_RTC(ID_TEST_EXT_RTC); 
  Clr_Ext_Inter_Dog();
  
  Test_Memory();  
  Clr_Ext_Inter_Dog();
  
  Test_All_RTC(ID_TEST_INTER_RTC);
  Test_CPU_Output_IO();
  
  Clr_Ext_Inter_Dog();    
  Chk_Table_Conflict();
  //Test_UART();
  START_ALL_LOSS;         //��ȫʧѹ
  while((B_TEST_FAC_STATUS==0)&&(B_TEST_HARD_STATUS==0))  //2������һ��û�в��ϣ��˳�����ģʽ��
  {
    //Test_Sleep();
    //Test_Epprom_Err();
    LCD_Dis_Result();
    Clr_Ext_Inter_Dog();    
  }
#endif
}

