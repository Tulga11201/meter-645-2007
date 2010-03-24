
#define DRV_TEST_C
#include "Pub_PUCK.h"

#ifdef DRV_TEST_EN


//#pragma optimize = none
//#pragma location = 0x00100
//static const INT8U EncryCode[10]={1,2,3,4,5,6,7,8,9,10};

//以下变量都来自 Lcd_main_LUCK.h ，避免变量重复使用
#define  KeyNum                 rollcycle             //借用变量，省空间
#define  Measu_Err_Code         dispmode              //借用变量，省空间
#define  ChkFlag                EnergDisBit           //借用变量，省空间
#define  counts                 DemandDisBit          //借用变量，省空间
#define  ToogleTimr             LcdDisTemp1           //借用变量，省空间
#define  ToogleMaxTime          LcdDisTemp2           //借用变量，省空间
#define  ThreeKeyStus           Light_Mode            //借用变量，省空间

#define  PD_Save_Data_Time      dispoffset            //借用变量，省空间

#define  Temp_Timer_Bak         Sleep_Sec_Countr.Var   //借用变量，省空间
#define  Sec_One_Timer          LCD_Loop_Ms10Timr.Var  //借用变量，省空间

//Drv_Test_Buf实际使用长度必须小于 Dis_GetData_Buf 长度
#define Drv_Test_Buf             Dis_GetData_Buf  //借用其他buf，省空间

#define TEST_MEM_BUF_LEN MEM_TEST_BYTES                   //MEM_TEST_BYTES必须小于 Temp_Buf_PUCK 长度
#define  Test_Mem_Buf          Temp_Buf_PUCK             //多一个字节，用于比较读出的数据超界：Test_Mem_Buf只用作 memroy测试时用


NO_INIT volatile INT8U  RstStatus;




CONST INT8U TEST_INFO[2][9]={"Failed ","Succeed"};


#define ID_TEST_EXT_U10 ID_MEM_IIC_U10      //0
#define ID_TEST_EXT_U11 ID_MEM_IIC_U11      //1
#define ID_TEST_EXT_U12 ID_MEM_IIC_U12      //2
#define ID_TEST_EXT_U14 ID_MEM_IIC_U14      //3


#ifdef ID_MEM_FM24C16                       
  #define ID_TEST_EXT_FM ID_MEM_FM24C16     //4
#else
  #define ID_TEST_EXT_FM ID_MEM_IIC_U15     //4
#endif

#define ID_TEST_EXT_U8  (ID_TEST_EXT_FM+1)  //5

#define ID_TEST_RTC_BAT (ID_TEST_EXT_U8+1)    //6

#define ID_TEST_MEASURE (ID_TEST_RTC_BAT+1)    //7
#define ID_TEST_EXT_RTC (ID_TEST_MEASURE+1)   //8
#define ID_TEST_INTER_RTC (ID_TEST_EXT_RTC+1)   //9
#define ID_TEST_EXT_DOG (ID_TEST_INTER_RTC+1)   //10
#define ID_TEST_PDSAVE_TIME (ID_TEST_EXT_DOG+1) //11

#if PREPAID_METER>0          //付费
  #if PREPAID_EN>0 
      #if (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE) //远程预付费
        #define ID_TEST_ESAM (ID_TEST_PDSAVE_TIME+1) //12
        #define MAX_ID_TEST  ID_TEST_ESAM
      #elif (PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)   //本地预付费
        #define ID_TEST_ESAM (ID_TEST_PDSAVE_TIME+1) //12
        #define ID_TEST_CPU  (ID_TEST_ESAM+1)       //13
        #define MAX_ID_TEST  ID_TEST_CPU
      #else
        
      #endif
  #endif 
#else
  #define MAX_ID_TEST ID_TEST_PDSAVE_TIME
#endif


#define MIN_ID_TEST ID_TEST_EXT_U10



#define MAX_ID_TEST_NUM (MAX_ID_TEST+1)

#define MAX_MEM_NUM (MAX_EPPROM_NUM+1)  //多了个flash


#define   EPPROM_TEST_NUM 10  //建议小于255次

INT16U const TEST_ADDR[MAX_EPPROM_NUM]={
  U10_SIZE-EPPROM_TEST_NUM,
  U11_SIZE-EPPROM_TEST_NUM,
  U12_SIZE-EPPROM_TEST_NUM,
  U14_SIZE-EPPROM_TEST_NUM,
  
#ifdef ID_MEM_FM24C16
 U16_SIZE-EPPROM_TEST_NUM,
#endif
#ifdef ID_MEM_IIC_U15
 U15_SIZE-EPPROM_TEST_NUM,
#endif
   
#ifdef ID_MEM_24C04
 U04_SIZE-EPPROM_TEST_NUM
#endif  
};

#define TEST_FLASH_ADDR  (INT32U)((INT32U)PAGE_SIZE*PAGE_NUMBER-EPPROM_TEST_NUM)

CONST INT8U Const_Drv_Test[MAX_ID_TEST_NUM][5]=
{
#ifdef ID_TEST_EXT_U10  //EPPROM---24C512
  "U11",
#endif

#ifdef ID_TEST_EXT_U11  //EPPROM---24C512
  "U12",
#endif

#ifdef ID_TEST_EXT_U12  //EPPROM---24C512
  "U14",
#endif

#ifdef ID_TEST_EXT_U14  //EPPROM---24C04
  "U17",
#endif

#ifdef ID_MEM_FM24C16  //铁电 24c16
  "U 6",
#else                  //铁电 24c64
  "U15",
#endif

#ifdef ID_TEST_EXT_U8  //Dataflash
  "U 5",
#endif

  "bAT",

#ifdef ID_TEST_MEASURE
  "7022",
#endif

#ifdef ID_TEST_EXT_RTC
  #if EXT_RTC_TYPE==DRV_SIMU_DS3231 || DRV_HARD_DS3231==1
  "3231",
  #elif EXT_RTC_TYPE==DRV_SIMU_RX8025
  "8025",
  #else
  "802T",
  #endif
#endif

#ifdef ID_TEST_INTER_RTC
  "o5C",
#endif
#ifdef ID_TEST_EXT_DOG
  "rST",
#endif
#ifdef ID_TEST_PDSAVE_TIME
  "PoEr",
#endif
    
#ifdef ID_TEST_ESAM
  "ESAM",
#endif

#ifdef ID_TEST_CPU
  "CARd"
#endif

};



/**********************************************************************************
**********************************************************************************/
INT8U Judge_Test_Succeed(void)
{
  INT8U i;
    
  for(i=MIN_ID_TEST;i<=MAX_ID_TEST;i++)
  {
    if(Drv_Test_Buf[i]==0)
    {
      return 0;
    }
  }
  return 1;
}

/**********************************************************************************
蜂鸣器报警异常
**********************************************************************************/
INT8U Beep_For_Err_Item(INT8U item)
{  
  if(item>MAX_ID_TEST)
    return 0;
  
  if(Drv_Test_Buf[item]==0)
  {
      Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
      return 1;
  }
  return 0;
}
/**********************************************************************************
蜂鸣器报警异常
**********************************************************************************/
void Beep_For_Err(void)
{
  INT8U i;
    
  for(i=MIN_ID_TEST;i<=MAX_ID_TEST;i++)
  {
    if(Beep_For_Err_Item(i))
    {
      return ;
    }
  }
}
void Test_RST_Pin(void)
{
  INT32U Temp_Ms_Timer;
  if(RstStatus!=0x48)
  {     
      RstStatus=0x48;
      Temp_Ms_Timer=Ms_Timer_Pub;
      Debug_Print("Test Extern Dog ...........................");
      while(Ms_Timer_Pub-Temp_Ms_Timer<2400)     //3秒都不复位！
        Clear_CPU_Dog();    //清CPU内部看门狗
      
      if(Ms_Timer_Pub-Temp_Ms_Timer>=2400)  //怕误取错
      {
        Drv_Test_Buf[ID_TEST_EXT_DOG]=0; 
        //Debug_Print("|-----------------------Test Extern Dog-------------------------------|");
        //Debug_Print("|          Item                                               Result  |");
        //Debug_Print("| Exter_Rst_Pin                                               Failed  |"); 
        //Debug_Print("|---------------------------------------------------------------------|");         
        RstStatus=0;
      }
  }
  else
  {
    Drv_Test_Buf[ID_TEST_EXT_DOG]=1;    
    Debug_Print("|-----------------------Test Extern Dog-------------------------------|");
    //Debug_Print("|           Item                                              Result  |");
    //Debug_Print("| Extern_Rst_Pin                                             Succeed  |"); 
    //Debug_Print("|---------------------------------------------------------------------|");     
  }
  Beep_For_Err_Item(ID_TEST_EXT_DOG);
}
/**********************************************************************************
死延时10毫秒，并喂狗

***********************************************************************************/
/**********************************************************************************/
void Dlyn10MS_ClrDog(INT32U n)
{
  INT32U i;
  for(i=0;i<n;i++)
  {
    if(i%10==0)  //100ms喂狗一次
    {
      Clr_Ext_Inter_Dog();
    }
    WAITFOR_DRV_MS_TIMEOUT(10);
  }
}
/**********************************************************************************
测试1ms内的nop数
**********************************************************************************/
INT32U Get_Counts_1MS(void)
{
  INT32U i;  
  
  for(i=0,Temp_Timer_Bak=Ms_Timer_Pub=0;;i++)  //计算出1ms内的nop数目
  {
    if(Temp_Timer_Bak!=Ms_Timer_Pub)
      break;
  }
  
  i=i*15;
  Debug_Print("NOP Counts=%ld In 1MS",i);
  return i;
}

/**********************************************************************************
测试IO,每秒输出
**********************************************************************************/
void Test_CPU_Output_IO(void)
{

  ChkFlag=!ChkFlag;
  
  OPEN_MEASU_PWR;           //          计量芯片电源开启
  //置输出口
  SET_AC_POWER_OUT;
  SET_REAC_POWER_OUT;
  SET_AC_DIR_OUT;
  SET_REAC_DIR_OUT;
  SET_AC_LED_OUT;
  SET_REAC_LED_OUT;
  
  
  if(ChkFlag)
  {
    //Debug_Print("Trun On All Ext Ports");
    IRDA_NEAR_REC_EN;         //          B_ird_chose_1     //远红外关闭，吸附红外开启
    BAK_POWER_FOR_IRDA;       //        B_ird_pow_1       //远红外电源由低功耗电池供给;
    BAK_POWER_FOR_LCD;        //        LCD_POW_1         //LCD电源由低功耗电池供给;
    BAK_POWER_FOR_MEM;        //        EEPOWER_1         //内卡电源由低功耗电池供给;
    
    
    
    IRDA_SEND_EN;   //红外发送使能
    IRDA_SEND_DIS;  ///红外发送禁止
    IRDA_NEAR_REC_EN;//          B_ird_chose_1     //远红外关闭，吸附红外开启
    
    //端子排有无功脉冲输出指示
    //有功输出口关闭
    A_OUT_1;
    //无功输出口关闭
    R_OUT_1;
    //有功正向口打开
    A_DIR_0;
    //无功正向口打开
    R_DIR_0;    
    
    //有功脉冲 LED 输出口关闭
    MEASU_A_LED_1;  
   //无功脉冲 LED 输出口关闭    
    MEASU_R_LED_1;
    
    //LED报警指示灯关闭
    LED_ALARM_CLR;
    
    //跳闸指示关闭      
    LED_TOGGLE_CLR;
    
    //端子排报警关闭
    //EXT_ALARM_CLR;
      
    //秒脉冲禁止输出,和需量，时段共用端子排
    EXT_SECOUT_SET;
      
    //需量周期关闭
    EXT_DEMAND_SET;  

    //时段切换关闭
    //EXT_PARSE_SET;    
   
    if(Judge_Test_Succeed() EQ 0)
      LCD_BACK_LIGHT_0;
  }
  else
  {
    IRDA_FAR_REC_EN;         //          B_ird_chose_0      //远红外开启，吸附红外关闭
    MAIN_POWER_FOR_IRDA;      //       B_ird_pow_0       //远红外电源由主电源供给;
    MAIN_POWER_FOR_LCD;     //       LCD_POW_0         //LCD电源由主电源供给;
    MAIN_POWER_FOR_MEM;     //       EEPOWER_0         //内卡电源由主电源供给;
   
    
    IRDA_FAR_REC_EN;//          B_ird_chose_0      //远红外开启，吸附红外关闭
    
    //有功输出口打开
    A_OUT_0;
    //无功输出口打开
    R_OUT_0;
    //有功反向口打开
    A_DIR_0;
    //无功反向口打开
    R_DIR_0;
    
    //有功脉冲 LED 输出口打开
    MEASU_A_LED_0;
    //无功脉冲 LED 输出口打开    
    MEASU_R_LED_0;
    
    //LED报警指示灯
    LED_ALARM_SET;
    
    //跳闸指示打开      
    LED_TOGGLE_SET;
    
    //端子排报警打开
    //EXT_ALARM_SET;
    
    //秒脉冲禁止输出,和需量，时段共用端子排
    EXT_SECOUT_SET;
    
    //需量周期打开
    EXT_DEMAND_CLR;  
    
    //时段切换打开
    //EXT_PARSE_CLR;  
    
    if(Judge_Test_Succeed())
      LCD_BACK_LIGHT_1;
  }
}

/**********************************************************************************
测试IO
**********************************************************************************/
//#define TOGGLE_ON 1   //刀铡开时间：秒
//#define TOGGLE_OFF 1   //刀铡关时间：秒

#define MAX_TOGGLE_TIME 15   //刀铡周期最长时间：秒


void Test_All_Port(void)
{
  if((Inter_Up_Key_STATUS EQ 0) &&(Inter_Down_Key_STATUS EQ 0))
    ToogleMaxTime=MAX_TOGGLE_TIME;
    
  if(Sec_Timer_Pub!=Sec_One_Timer)  
  {
    counts++;
    Test_CPU_Output_IO();    //端子排输出        
    if(counts<=(ToogleTimr+1))            //刀铡开
    {    
      EXT_SWITCH_SET;            //端子排跳闸 
      EXT_ALARM_SET;
      
     Port_Out_Pub(INTER_ID_RELAY_ON,LARGE_RELAY_PULSE_WD);
    }
    if(counts>(ToogleTimr+1) && counts<=(ToogleTimr+1)*2)  //刀铡关
    {
      EXT_SWITCH_CLR;           //端子排跳闸   
      EXT_ALARM_CLR;
      
      Port_Out_Pub(INTER_ID_RELAY_OFF,LARGE_RELAY_PULSE_WD);      
    }
    
    if(counts>=(ToogleTimr+1)*2)
    {
      counts=0;
      ToogleTimr++;
    }
    
    if(ToogleTimr>ToogleMaxTime)
    {
      ToogleTimr=0;
    }
    Sec_One_Timer=Sec_Timer_Pub;
  }    
}
/**********************************************************************************
测试UART
**********************************************************************************/
void Test_UART(void)
{
  INT8U i;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)  //注意，内涵调试口的重复初始化！
  {
    Open_Channel_PUCK(i,4800,SAU_PARITY_NONE); 
    Channel_DataSend_PUCK(i,"123456ABCDEF",12);
  }
  Init_DebugChanel_PUCK(1);
}
/**********************************************************************************
测试液晶
**********************************************************************************/
void Test_Lcd(void)
{
  INT8U i;
  
 //Debug_Print("Test LCD，Please Watch LCD and Judge Result!"); 
  
  mem_set((INT8U *)Temp_Buf_PUCK,0x00,sizeof(Temp_Buf_PUCK),(INT8U *)Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  
#ifdef LCD_MIN_8
  strcpy((char *)Temp_Buf_PUCK,"SELFTEST");
#else 
  strcpy((char *)Temp_Buf_PUCK,"SELF  TEST");
#endif   
  
  //BAK_POWER_FOR_LCD;//        LCD_POW_1         //LCD电源由低功耗电池供给;
  MAIN_POWER_FOR_LCD;//       LCD_POW_0         //LCD电源由主电源供给;
  
  InitLcdAllRam();
  Init_LCD_Mode(SYS_NORMAL,Ext_Device_Stat.Status);
  Turn_Light_On();
  
#ifdef LCD_MIN_8
  for(i=0;i<=7;i++)
    SetOnLED8Device_PUCK(N_LED(i+2),Temp_Buf_PUCK[i]);
#else 
  for(i=0;i<=9;i++)
     SetOnLED8Device_PUCK(N_LED(i+3),Temp_Buf_PUCK[i]);
 #endif 
  UpdataLcdShow();    
}


/**********************************************************************************/
void Test_All_Bat(void)
{  
    Drv_Test_Buf[ID_TEST_RTC_BAT]=RTC_BAT_LOW;
    Drv_Test_Buf[ID_TEST_RTC_BAT]&=LOWCOST_BAT_LOW;
}


/**********************************************************************************
测试计量
**********************************************************************************/
#define MEASU_TEST_NUM 3

#define MEASU_MODE_ERR    0x01  //模式脚与模式字不一致
#define MEASU_SIG_ERR     0x02  //SIG信号不对
#define MEASU_RW_ERR      0x04  //读写错误
#define MEASU_LOGIC_ERR   0x08  //数据逻辑错

void Test_Measure(void)
{
  INT32U temp[3],Cs;
  INT8U i,Flag;
  
  GetSysModeProc();           //计量相关参数初始化
  
  OPEN_MEASU_PWR;//       LCD_POW_0         //LCD电源由主电源供给;
  Dlyn10MS_ClrDog(1);
  MEASU_RST_0;
  Dlyn10MS_ClrDog(1);
  MEASU_RST_1;
  Dlyn10MS_ClrDog(100);  //for Cs Refresh
  
  //检测341参数配置与计量芯片是否一致
  Flag=Measu_RdAndCompData_3Times(REG_R_SUM,(INT8U *)&Cs);     //读7022中校表参数的校验和
  if(Flag)
  {
    if((Get_SysParse_Mode()==PARSE_341) && (Cs!=CHKSUM_INIT_341))  //不是上电时候的CS
    {
      Debug_Print("Measure_Info----->Measure_IC Para Data(341) !=Default Value!");
      Flag=0;
      Measu_Err_Code|=MEASU_MODE_ERR;
    }
    
    if((Get_SysParse_Mode()==PARSE_331) && (Cs!=CHKSUM_INIT_331)) //不是上电时候的CS
    {
      Debug_Print("Measure_Info----->Measure_IC Para Data(331) !=Default Value!");
      Flag=0;
      Measu_Err_Code|=MEASU_MODE_ERR;
    } 
    
    EnMeasuCal();
    ClrMeasuCal();     //将校表数据寄存器的内容恢复到上电初始值
    temp[0]=0;
    for(i=REG_W_UGAIN_A;i<=REG_W_UGAIN_C;i++)
      Flag&=Measu_WrAndCompData_3Times(i,temp[0]);
    DisMeasuCal();
    
    Dlyn10MS_ClrDog(10);
    
    Clr_Cal_Requst();
    
    for(i=0;i<3;i++)
    {
      Flag&=Measu_RdAndCompData_3Times(REG_R_A_U+i,(INT8U *)&temp[i]);
      temp[i]/=UNIT_V;
      
      /*  由于没有设定参数，规格未知，判断数据逻辑错没有根据，屏蔽此代码-----09-12-23  PUCK
      if(((FP32S)temp[i]>Get_Un()*0.2 && (FP32S)temp[i]<Get_Un()*0.5) ||((FP32S)temp[i]>Get_Un()*1.35))
      {
        Flag=0;
        Measu_Err_Code|=MEASU_LOGIC_ERR;
      }
      */
      if(!MEASU_SIG_STAT)      //异常
      {
         Flag=0;
         Measu_Err_Code|=MEASU_SIG_ERR;
      }
      *(&Measu_InstantData_ToPub_PUCK.Volt.A+i)=temp[i];
    }    
  }
  else
   Measu_Err_Code|=MEASU_RW_ERR;  
  
  SET_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
    
  Drv_Test_Buf[ID_TEST_MEASURE]=Flag;  
  Debug_Print("|-----------------------Test Measure IC-------------------------------|");
  //Debug_Print("| Total Times    Volt_A(V)       Volt_B(V)    Volt_C(V)     Result    |");
  //Debug_Print("|         %3d          %3ld             %3ld          %3ld     %s   |",
  //                        MEASU_TEST_NUM,temp[0],temp[1],temp[2],TEST_INFO[Drv_Test_Buf[ID_TEST_MEASURE]]); 
  //Debug_Print("|---------------------------------------------------------------------|"); 
  Beep_For_Err_Item(ID_TEST_MEASURE);
}
/**********************************************************************************
RtcFlag:1----------------外部RTC；0--------------内部RTC
测试外部RTC
测试结论：读写测试65536次，实验花费时间为142460ms，即读和写一次，所花时间为2.17ms
**********************************************************************************/
#define RTC_TEST_NUM 10
void Test_All_RTC(INT8U RtcFlag)
{
  INT8U Temp[7],TempSec;
  INT16U i,RdWrErr=0,CompErr=0;
  //INT32U timr;
  INT8U Flag=0;
  
  if(!((RtcFlag==ID_TEST_EXT_RTC)||(RtcFlag==ID_TEST_INTER_RTC)))
  {
    Debug_Print("Test RTC ID Error!");
    return ;
  }
  
  if(RtcFlag==ID_TEST_EXT_RTC)   //外部时钟
  {
    //Init_DS3231_IIC_Soft();
    Init_ExtRTC_Pulse(1);   //输出秒脉冲 
    //Temp[6]=0x09;Temp[5]=0x09;Temp[4]=0x11;Temp[3]=0x05;Temp[2]=0x17;Temp[1]=0x58;
    //Write_ExtRTC_PUCK(Temp);
  }

  Temp_Timer_Bak=Ms_Timer_Pub; //用来查看花费的时间
  //读写测试65535次，实验花费时间为Ms10_Timer_Pub=142460ms，即读和写一次，所花时间为2.17ms---------PUCK
  for(i=0;i<RTC_TEST_NUM-1;i++)
  {
    mem_set(Temp,0,sizeof(Temp),Temp,sizeof(Temp));
    if(RtcFlag==ID_TEST_EXT_RTC)
      Flag=!Read_ExtRTC_PUCK(Temp,7);
    else
      Flag=!Read_InterRTC_PUCK(Temp,7);
    
    Flag|=!Check_BCD_Data(Temp,7);//检查数据格式?
    RdWrErr+=Flag; 
    //if(Flag)
    //  Debug_Print("Current Time(Yea-Mon-Dat_Day_Hou:Min:Sec):%2x-%2x-%2x_%2x_%2x:%2x:%2x       |",\
    //                      Temp[6],Temp[5],Temp[4],Temp[3],Temp[2],Temp[1],Temp[0]);
    
    if(0==i) //记下第一次读出的秒
    {
      TempSec=Temp[0];
      Dlyn10MS_ClrDog(180);  //延时2秒，等时钟秒更新
    }
  }
  //timr=Ms_Timer_Pub-Temp_Timer_Bak;  
  if(TempSec==Temp[0])    //秒没更新
    CompErr=1;  

   Drv_Test_Buf[RtcFlag]=!(RdWrErr|CompErr);

  if(RtcFlag==ID_TEST_EXT_RTC)
  {
     Beep_For_Err_Item(ID_TEST_EXT_RTC);
    Debug_Print("|-----------------------Test Extern RTC-------------------------------|");
  }
  else
  {
    if(CSC!=0x01 ||CKC!=0x38)
      Drv_Test_Buf[RtcFlag]=0;    
    
    Beep_For_Err_Item(ID_TEST_INTER_RTC);
    Debug_Print("|------------------------Test Internal RTC----------------------------|");
  }
  //Debug_Print("| Total Times    Run Time(MS)      RdWr_Err    Compa_Err    Result    |");
  //Debug_Print("|         %3d      %9ld            %3d          %3d    %s   |",
  //                        RTC_TEST_NUM,timr,RdWrErr,CompErr,TEST_INFO[Drv_Test_Buf[RtcFlag]]); 
  //Debug_Print("|Current Time(Yea-Mon-Dat_Day_Hou:Min:Sec):%2x-%2x-%2x_%2x_%2x:%2x:%2x       |",
  //                        Temp[6],Temp[5],Temp[4],Temp[3],Temp[2],Temp[1],Temp[0]);
  //Debug_Print("|---------------------------------------------------------------------|"); 
 
}
/**********************************************************************************
测试EPPROM
对特定的存储器检测！
**********************************************************************************/
/**********************************************************************************
#define BUMP_MEM_ADDR 513
#define BUMP_MEM_SIZE 513

void Buf_Mem_Test(void)
{
  INT16U i,err;
     
  for(i=0;i<BUMP_MEM_SIZE;i++)
  Pub_Buf[i]=254-(INT8U)i;
  
  
  for(i=0,err=0;i<EPPROM_TEST_NUM;i++)
  {
    //Write_PHY_Mem_PUCK(PHY_MEM0,0,(void *)Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));    
    //Read_PHY_Mem_PUCK(PHY_MEM0,0,(void *)Dis_GetData_Buf,sizeof(Dis_GetData_Buf),(void *)Dis_GetData_Buf,sizeof(Dis_GetData_Buf)); 
    
    //Write_PHY_Mem_PUCK(55,0,(void *)Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));    
    //Read_PHY_Mem_PUCK(55,0,(void *)Dis_GetData_Buf,sizeof(Dis_GetData_Buf),(void *)Dis_GetData_Buf,sizeof(Dis_GetData_Buf));
    //Write_PHY_Mem_PUCK(55,0,(void *)Temp_Buf_PUCK,1);    
    //Read_PHY_Mem_PUCK(55,0,(void *)Dis_GetData_Buf,1,(void *)Dis_GetData_Buf,1);
    
    Write_EEPROM_Dvice_PUCK(ID_MEM_FM24C16,BUMP_MEM_ADDR,BUMP_MEM_SIZE,(INT8U *)Pub_Buf);
    
    mem_set((INT8U *)Pub_Buf0,0x00,sizeof(Pub_Buf0),(INT8U *)Pub_Buf0,sizeof(Pub_Buf0));    
    Read_EEPROM_Dvice_PUCK(ID_MEM_FM24C16,BUMP_MEM_ADDR,BUMP_MEM_SIZE,(INT8U *)Pub_Buf0); 
    
      
    if(memcmp((INT8U *)Pub_Buf,(INT8U *)Pub_Buf0,sizeof(Temp_Buf_PUCK)))
      err++;
   Clr_Ext_Inter_Dog();   
  }
  
  if(err)
    Debug_Print("Bump Mem Buf Test Failed:ErrTimes=%d",err);
  else
    Debug_Print("Bump Mem Buf Test Succeed!");
  
  while(1)
    Clr_Ext_Inter_Dog();
  
}
**********************************************************************************/
/**********************************************************************************
测试EPPROM
**********************************************************************************/
void Test_Memory(void)
{
  INT8U j,Flag,RandBuf[TEST_MEM_BUF_LEN];
  INT16U i;
  //INT32U timr;  
  INT8U RdErr[MAX_MEM_NUM],WrErr[MAX_MEM_NUM],CompareErr[MAX_MEM_NUM];
    
  mem_set(RdErr,0x00,sizeof(RdErr),RdErr,sizeof(RdErr));
  mem_set(WrErr,0x00,sizeof(WrErr),WrErr,sizeof(WrErr));
  mem_set(CompareErr,0x00,sizeof(CompareErr),CompareErr,sizeof(CompareErr));
  
  mem_set((INT8U *)(Drv_Test_Buf+ID_TEST_EXT_U10),0x01,MAX_MEM_NUM,(INT8U *)(Drv_Test_Buf+ID_TEST_EXT_U10),MAX_MEM_NUM);
  Temp_Timer_Bak=Ms_Timer_Pub; //用来查看花费的时间
  for(i=0;i<EPPROM_TEST_NUM;i++)  //测试次数
  {
    mem_set(RandBuf,0x55+i,sizeof(RandBuf),RandBuf,sizeof(RandBuf));
    for(j=ID_TEST_EXT_U10;j<ID_TEST_EXT_U8;j++)
    {  
      Flag=!Write_EEPROM_Dvice_PUCK(j,TEST_ADDR[j],TEST_MEM_BUF_LEN,RandBuf);
      WrErr[j]+=Flag;
  
      mem_set((INT8U *)Test_Mem_Buf,0x33,sizeof(Test_Mem_Buf),(INT8U *)Test_Mem_Buf,sizeof(Test_Mem_Buf));
      Flag=!Read_EEPROM_Dvice_PUCK(j,TEST_ADDR[j],TEST_MEM_BUF_LEN,(INT8U *)Test_Mem_Buf);
      RdErr[j]+=Flag;
     
      if((memcmp((INT8U *)Test_Mem_Buf,RandBuf,TEST_MEM_BUF_LEN)!=0)||(Test_Mem_Buf[TEST_MEM_BUF_LEN]!=0x33))//比较相等，但底层不能多写造成越界！
       CompareErr[j]++;
      
     if(RdErr[j]|WrErr[j]|CompareErr[j])   //有其中一个错误发生，置标志失败标志
      Drv_Test_Buf[j]=0;
    }
    
    Flag=!flash_writ_abs(TEST_FLASH_ADDR,RandBuf,TEST_MEM_BUF_LEN);
    WrErr[j]+=Flag;

    Clr_Ext_Inter_Dog();
    
    mem_set((INT8U *)Test_Mem_Buf,0x33,sizeof(Test_Mem_Buf),(INT8U *)Test_Mem_Buf,sizeof(Test_Mem_Buf));
    Flag=!flash_read_abs(TEST_FLASH_ADDR,(INT8U *)Test_Mem_Buf,TEST_MEM_BUF_LEN);
    RdErr[j]+=Flag;
   
    if((memcmp((INT8U *)Test_Mem_Buf,RandBuf,TEST_MEM_BUF_LEN)!=0)||(Test_Mem_Buf[TEST_MEM_BUF_LEN]!=0x33))//比较相等，但底层不能多写造成越界！//比较
    CompareErr[j]++; 
     
   if(RdErr[ID_TEST_EXT_U8]|WrErr[ID_TEST_EXT_U8]|CompareErr[ID_TEST_EXT_U8])  //有其中一个错误发生，置标志失败
    Drv_Test_Buf[ID_TEST_EXT_U8]=0;
   
   Clr_Ext_Inter_Dog();
   //注： flash_writ_abs()失败一次，需要花费776ms，里面没有确定的超时保护机制。flash_writ_abs()和flash_read_abs()分别失败一次的话，需要1.7s，导致CPU复位！
  }

  //timr=Ms_Timer_Pub-Temp_Timer_Bak;
  Debug_Print("|-----------------------Test Memory-----------------------------------|");
  /*Debug_Print("| Total_Times      Read_Err        Write_Err   Compare_Err  Result    |");
  
  for(j=ID_TEST_EXT_U10;j<=ID_TEST_EXT_U8;j++)
  {
    Beep_For_Err_Item(j);
    Debug_Print("|%s      %3d           %3d              %3d           %3d  %s   |",\
                          Const_Drv_Test[j],EPPROM_TEST_NUM,RdErr[j],WrErr[j],CompareErr[j],TEST_INFO[Drv_Test_Buf[j]]);
    
  }
 
  Debug_Print("|       All Run Time=%9ldMS                                      |",timr); 
  Debug_Print("|---------------------------------------------------------------------|"); */
}


/**********************************************************************************
**********************************************************************************/

void Get_Power_Save_Time(void)
{
  INT32U temp;
  INT8U Flag;
  
  Flag=Read_Storage_Data_PUCK(_SDI_SAVE_PD_DATA_TIME,&temp,4);  //掉电存数时间
  Debug_Print("Power_Save_Time=%ld",temp);
  if(Flag && (temp>10 &&temp<600))
  {
    PD_Save_Data_Time=(INT16U)temp;
    temp=0xfefe;
    Write_Storage_Data(_SDI_SAVE_PD_DATA_TIME,&temp,4);
    Drv_Test_Buf[ID_TEST_PDSAVE_TIME]=1;
    return ;
  } 
  PD_Save_Data_Time=9999;  
  Drv_Test_Buf[ID_TEST_PDSAVE_TIME]=0;
  Beep_For_Err_Item(ID_TEST_PDSAVE_TIME);
}
/**********************************************************************************
**********************************************************************************/

void Check_Card_Esam(void)
{
#ifdef ID_TEST_ESAM
  INT8U temp[30];   
  INT8U SendBuf[8],i;
  
  
  Drv_Test_Buf[ID_TEST_ESAM]=0;
 
#ifdef ID_TEST_CPU
  Drv_Test_Buf[ID_TEST_CPU]=0;
#endif
  
   Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,temp,temp,sizeof(temp) );
  //冷复位 ESAM 测试
  for(i=0;i<3;i++)
  {
    if(Cpu_Esam_All_Operate(PAY_ESAM,CPU_ESAM_DRV_RST_COOL,temp,temp,sizeof(temp)) EQ CPU_ESAM_DRV_OK)
    {
      Drv_Test_Buf[ID_TEST_ESAM]=1; 
      break;
    }
   
    Clr_Ext_Inter_Dog(); 
  }

#ifdef ID_TEST_CPU  
  //冷复位 CPU 测试
  if(Cpu_Esam_All_Operate(PAY_CPU_CARD,CPU_ESAM_DRV_RST_COOL,temp,temp,sizeof(temp)) EQ CPU_ESAM_DRV_OK)
      Drv_Test_Buf[ID_TEST_CPU]=1;
#endif
  
  Clr_Ext_Inter_Dog(); 
  
  //发送接收 ESAM 测试
  mem_set(SendBuf,0x00,sizeof(SendBuf),SendBuf,sizeof(SendBuf));
  SendBuf[1]=0x84;SendBuf[4]=0x08;  //从ESAM取8字节随机数:00 84 00 00 08,返回：84+Rand8 + 9000
  if(Cpu_Esam_Comm_Proc(PAY_ESAM,SendBuf,5,READ_CPU_ESAM,11,temp,temp,sizeof(temp)) EQ CPU_ESAM_DRV_OK)
  {      
      if((temp[0] != 0x84) || (temp[9] != 0x90)&&(temp[10] != 0x00))
        Drv_Test_Buf[ID_TEST_ESAM]=0;
  }
  else
    Drv_Test_Buf[ID_TEST_ESAM]=0;
  Clr_Ext_Inter_Dog();   
  
#ifdef ID_TEST_CPU  
  //发送接收 CPU卡 测试
  mem_set(SendBuf,0x00,sizeof(SendBuf),SendBuf,sizeof(SendBuf));
  SendBuf[1]=0xA4;SendBuf[4]=0x02;  //选择用户卡应用目录:00 A4 00 00 02，接收0xA4
  if(Cpu_Esam_Comm_Proc(PAY_CPU_CARD,SendBuf,5,READ_CPU_ESAM,1,temp,temp,sizeof(temp)) EQ CPU_ESAM_DRV_OK)  //选择用户卡应用目录
  {
    if(temp[0] != 0xA4)
      Drv_Test_Buf[ID_TEST_CPU]=0;
  }
#endif
  
  Clr_Ext_Inter_Dog(); 
#endif
}

/**********************************************************************************
LCD显示每屏结果
**********************************************************************************/
void Dis_Per_Item(INT8U Item)
{
  INT8U i;
  INT16U temp;
  
  if(Item>MAX_ID_TEST)
    return ;
  
  if(Drv_Test_Buf[Item]>1)  //只允许0/1
    return ;
  
  mem_set((INT8U *)Temp_Buf_PUCK,0x00,sizeof(Temp_Buf_PUCK),(INT8U *)Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  strcpy((char *)Temp_Buf_PUCK,(char*)Const_Drv_Test[Item]);
   
  
#ifdef LCD_MIN_8
  if(Drv_Test_Buf[Item]==0)
    strcpy((char *)Temp_Buf_PUCK+4," bAd");
  else
    strcpy((char *)Temp_Buf_PUCK+4,"6ood");
  
  for(i=2;i<=9;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-2]);
#else
  if(Drv_Test_Buf[Item]==0)
    strcpy((char *)Temp_Buf_PUCK+5,"  bAd");
  else
    strcpy((char *)Temp_Buf_PUCK+5," 6ood");
  
  for(i=3;i<=12;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-3]);
 
#endif


  mem_set((INT8U *)Temp_Buf_PUCK,0x00,sizeof(Temp_Buf_PUCK),(INT8U *)Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  
  //显示屏号
  Temp_Buf_PUCK[6]=(Item+1)/10+'0';
  Temp_Buf_PUCK[7]=(Item+1)%10+'0';
  
  //显示掉电时间
  if(ID_TEST_PDSAVE_TIME==Item)
  {
    temp=PD_Save_Data_Time; 
    for(i=0;(i<3) && (temp!=0);i++)
    {
      Temp_Buf_PUCK[2-i]=(temp%10)+'0';
      temp=(temp-(temp%10))/10;
    }
  }
  
  //显示计量错误状态字
  if(ID_TEST_MEASURE==Item && Drv_Test_Buf[ID_TEST_MEASURE]==0)
  {
    temp=Measu_Err_Code; 
    for(i=0;i<2;i++)
    {
      Temp_Buf_PUCK[1-i]=(temp%10)+'0';
      temp=(temp-(temp%10))/10;
    }
  }
  

   // GUMB_STATUS  UP_COVER_STATUS  DOWN_COVER_STATUS  B_PRG_KEY_STATUS
  
#if LCD_PROPERTY==LCD_NORMAL || LCD_PROPERTY==LCD_JS_ZXW   
  if(GUMB_STATUS)
    SetOnDevice_PUCK(S_KEY);
#endif
  
#if LCD_PROPERTY==LCD_NORMAL 
  if(UP_COVER_STATUS)
    SetOnDevice_PUCK(S_HOUSE);
  if(DOWN_COVER_STATUS)
    SetOnDevice_PUCK(S_SHOT);
#endif
 
#if LCD_PROPERTY==LCD_JS_ZXW 
  if(UP_COVER_STATUS)
    SetOnDevice_PUCK(S_UPCOVERP);
  if(DOWN_COVER_STATUS)
    SetOnDevice_PUCK(S_DOWNCOVERP);
#endif

  if(B_PRG_KEY_STATUS==0)
    SetOnDevice_PUCK(S_BUTTON);
  
  if(RTC_BAT_LOW==0)
    SetOnDevice_PUCK(S_BAT1);
  
  if(LOWCOST_BAT_LOW==0)
    SetOnDevice_PUCK(S_BAT2);
  
#if LCD_PROPERTY==LCD_SD_ZXW ||  LCD_PROPERTY==LCD_GW_ZXW 
  for(i=10;i<=17;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-10]);

#elif LCD_PROPERTY==LCD_EASY_GZL
  if((Drv_Test_Buf[Item]==0) && (ID_TEST_PDSAVE_TIME EQ Item || ID_TEST_PDSAVE_TIME EQ Item))  //自检错误的项目：显示掉电时间，计量错误状态字
  {
    for(i=10;i<=12;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-10]);   //Temp_Buf_PUCK[0~2]
  }
  else      
  {
    for(i=11;i<=12;i++)
      SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-5]);   //Temp_Buf_PUCK[6] Temp_Buf_PUCK[7]
  }
  
#else
  for(i=14;i<=21;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-14]);
#endif
  
  
  UpdataLcdShow();
}



/**********************************************************************************
LCD显示输出结果
**********************************************************************************/
void LCD_Dis_Result(void)
{
  INT8U KeyValue;

#ifdef DOWN_COVER_ERR  //硬件的设计逻辑错误  
  if(DOWN_COVER_STATUS EQ 1 || UP_COVER_STATUS EQ 0 || B_PRG_KEY_STATUS EQ 0)     //开端盖(后端盖)铅封
#else
  if(DOWN_COVER_STATUS EQ 0 || UP_COVER_STATUS EQ 0 || B_PRG_KEY_STATUS EQ 0)     //开端盖(后端盖)铅封
#endif    
  {
    FillAllScreen();   //用于显示液晶是否缺笔
    ThreeKeyStus=0x34;
    return ;
  }
  
  if(ThreeKeyStus EQ 0x34)
  {
    Temp_Timer_Bak=0;   //立即刷新
    ThreeKeyStus=0x00;
  }
    
  
  

  KeyValue=Key_Value_Pub.Key.Byte;
  Key_Value_Pub.Key.Byte=0;
  
   switch(KeyValue)    //以下获取具体的现实元素信息------------PUCK
  {
        case UP_KEY_VALUE :
        case RIGHT_KEY_VALUE:
            if(Judge_Test_Succeed()) //自检成功
              Turn_Light_On();
            KeyNum++;
            
            if(KeyNum>MAX_ID_TEST)
              KeyNum=0;
            Dis_Per_Item(KeyNum);
            Temp_Timer_Bak=Sec_Timer_Pub;
            
              break;
 
        case DOWN_KEY_VALUE:
        case LEFT_KEY_VALUE:
            if(Judge_Test_Succeed()) //自检成功
              Turn_Light_On();
            
            KeyNum--;
            if(KeyNum>MAX_ID_TEST)
              KeyNum=MAX_ID_TEST;           
            Dis_Per_Item(KeyNum);
            Temp_Timer_Bak=Sec_Timer_Pub;
            
             break;
        default:
          if(Sec_Timer_Pub-Temp_Timer_Bak>3)  //3秒循环显示
          {
            KeyNum++;
            if(KeyNum>MAX_ID_TEST)
              KeyNum=0;
            
            if(Judge_Test_Succeed() EQ 0) //自检失败
            {
              Main_Dis_Info(" FAILED");           
            }
            else                        //自检成功
            {     
              Main_Dis_Info("SUCCEED ");       
            }
           Temp_Timer_Bak=Sec_Timer_Pub;
           Beep_For_Err();            
          }                  
          break;            
   }  
}
/**********************************************************************************
LCD显示输出结果
**********************************************************************************/
void Test_Sleep(void)
{
  /* while(1)
   {
      //Clear_CPU_Dog();    //清CPU内部看门狗
      Clear_Ext_Dog();    //清CPU外部看门狗
      
   }*/
   
  
  /*TAU_Init();
  START_IRDA;
  START_ALL_LOSS;
  Init_ExtRTC_Pulse(1);        //使能秒脉冲----PUCK
  START_1HZ;
  while(1)
  Debug_Print("Enter Into Halt Mode!");
  Init_All_UART(SYS_SLEEP);       //睡眠模式下的串口初始化,打印调试信息的方便
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
    //Debug_Print("Wake Up From Halt Mode!");
    while(1)
    {
      Clear_CPU_Dog();    //清CPU内部看门狗
      //Clear_Ext_Dog();    //清CPU外部看门狗
      
    }
    START_1MS;
    START_PMW;
  };*/
}
#endif

void Enable_Key(void)
{
  START_UP_KEY;
  START_DOWN_KEY;
  START_LEFT_KEY;
  START_RIGHT_KEY;
  START_IR_DECODE  //检测遥控解码，实际也是检测红外的收
}

/**********************************************************************************
测试EPPROM
**********************************************************************************/
void Test_HardWare_PUCK(void)
{  
#ifdef DRV_TEST_EN

   //PM14_bit.no2=1;   //蜂鸣器
   
  //START_MIN_ALARM;
  /*Init_CPU_PUCK(SYS_RESUME);
  Init_ExtDevice_PUCK(SYS_RESUME);
  while(1)
  {
    Clr_Ext_Inter_Dog(); 
  }
  */
  if(JUDGE_POWER_OFF)  //掉电了。先调此函数，保证最快速度返回
    return ;
  
  if(Get_Meter_Hard_Mode()!=MODE_TEST)
    return ;   
  /*
  INIT_ESAM_CLK;
  START_ESAM_CLK;
  
  INIT_IC_CLK;
  START_IC_CLK;
  */
  

  Ext_Device_Stat.Status=TEST_STATUS_PUCK;  //置自检模式
  
  Init_DebugChanel_PUCK(0);
  //Test_Sumi_I2c_Epprom();

  Debug_Print(">>>>>>>>>>>>>>>>>>>> Self Test Mode <<<<<<<<<<<<<<<<<<<<< ");
  Init_All_Port(SYS_NORMAL);      //正常模式下的端口初始化  
  
  Test_RST_Pin();
  Clr_Ext_Inter_Dog();
  
  Init_All_UART(SYS_NORMAL);      //正常模式下的串口初始化  
  Clr_Ext_Inter_Dog();
  
  //Buf_Mem_Test();   //此函数是对存储器的 大数据频繁读写，一般不要打开！
   
  Test_Lcd();
  Clr_Ext_Inter_Dog();
    
  Test_Measure();
  Clr_Ext_Inter_Dog();
  
  Test_All_RTC(ID_TEST_EXT_RTC); 
  Clr_Ext_Inter_Dog();
  
    
  Test_Memory();  
  Clr_Ext_Inter_Dog();
  
  Test_All_RTC(ID_TEST_INTER_RTC);

  Clr_Ext_Inter_Dog();   
  Get_Power_Save_Time();
  
  Check_Card_Esam();
  
  Test_All_Bat();
  
  Chk_Table_Conflict();
  //Test_UART();
  //START_ALL_LOSS;         //打开全失压
  //START_FAST_FX_TIMER;
  //START_IRDA_WAKE;
  Enable_Key();   //使能按钮检测和遥控器接收检测
  
  while(1)
  {
    if(Get_Meter_Hard_Mode()==MODE_TEST)    //&&(JUDGE_POWER_OFF EQ 0)) //自检模式，喂狗，否则等看门狗复位！
    {
      LCD_Dis_Result();  //液晶显示测试结果
      Test_All_Port();
      Clr_Ext_Inter_Dog();
      Channel_Data_Proc_PUCK(SYS_NORMAL);
      //Read_Ext_RTC_Status();
    }
  }
#endif
}
