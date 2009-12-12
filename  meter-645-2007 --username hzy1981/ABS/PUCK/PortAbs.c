#define PORT_ABS_PUCK
#include "Pub_PUCK.h"


/********************************************************************************
void  Get_Meter_Hard_Mode(void)
函数功能：获取表计跳线模式
入口：  
返回：
    无
********************************************************************************/
INT8U Get_Meter_Hard_Mode(void)
{
  if(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS)  //大多数是这种模式，
    return MODE_RUN;
  
  if(B_TEST_FAC_STATUS && B_TEST_HARD_STATUS EQ 0)
    return MODE_DEBUG;
  
  if(B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS)
    return MODE_FAC;
  
  if(B_TEST_FAC_STATUS EQ 0 && B_TEST_HARD_STATUS EQ 0)  //这种模式最少
    return MODE_TEST;  
  
  //异常！
  return MODE_RUN;
}


/********************************************************************************
********************************************************************************/

void PORT_ChangeP142Output_PUCK(INT8U Level)
{
  PORT_ChangeP142Output(0,Level);  
}


void PORT_Relay_On_PUCK(INT8U Level)
{
  LARGE_TOOGLE_OFF_SET;   //将常闭的关闭
  
  if(Level)
    LARGE_TOOGLE_ON_SET;
  else
    LARGE_TOOGLE_ON_CLR;
}



void PORT_Relay_Off_PUCK(INT8U Level)
{
 LARGE_TOOGLE_ON_SET;   //将开启的关闭
 
  if(Level)
    LARGE_TOOGLE_OFF_SET;
  else
    LARGE_TOOGLE_OFF_CLR;
}

//#pragma pack(1)
typedef struct
{
  INT8U NeedInit:1;                 //需要初始化标志
  INT8U InitLevel:1;                //正常工作下，闲置时的电平值；
  INT8U SleepLevel:1;               //低功耗情况下，需要初始的电平值；
  INT8U ValidLevel:1;               //电平模式下，输出有效的电平值；
  INT8U MultiFlag:1;                //是否是复合端子标志：如3合1，0-------不是复合端子；1------是复合端子；2-------------
  INT8U LevelProprty:3;             //端子模式，LEVEL_MODE，PULSE_MODE，MULTI_MODE  
  void  (* const FuncPtr)(INT8U);
  INT8U (* const MultiPortEn)(void); //多合一端子(MultiFlag为1时)，根据此条件判定输出
  INT8U (* const GetOutMode)(void); //根据参数决定，到底输出什么方式   
}CONST_PORT_STATUS;

//以下对所有输出口的抽象定义
CONST CONST_PORT_STATUS  Const_Port_Status[MAX_PORT_NUM]={
  {0},
  {0,1,0,0,0,LEVEL_MODE,&PORT_ChangeP64Output,0,0},    //有功方向输出------------------------------------------------------------1
  {0,1,0,0,0,LEVEL_MODE,&PORT_ChangeP65Output,0,0},    //无功方向输出------------------------------------------------------------2
  {1,1,0,0,0,LEVEL_MODE,&PORT_ChangeP82Output,&Get_Sec_Out_En,0},    //秒脉冲使能------------------------------------------------3
  {1,0,0,1,0,LEVEL_MODE,&PORT_ChangeP131Output,0,0},    //跳闸指示灯--------------------------------------------------------------4
  {1,0,0,1,0,LEVEL_MODE,&PORT_ChangeP157Output,0,0},    //报警指示灯--------------------------------------------------------------5

  {1,0,0,1,0,MULTI_MODE,&PORT_ChangeP81Output,0,&Get_AuxPort_Out},    //辅助端子报警输出-----------------------------------------6(注意初始电平)
  {1,0,0,1,0,MULTI_MODE,&PORT_ChangeP80Output,0,&Get_Toogle_Out},     //跳闸输出-------------------------------------------------7(注意初始电平)
  
  
  //跳闸注意常闭常开，以常闭为参考
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP66Output,0,0},    //有功脉冲输出------------------------------------------------------------8
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP67Output,0,0},    //无功脉冲输出------------------------------------------------------------9

  {1,1,0,0,1,PULSE_MODE,&PORT_ChangeP83Output,&Get_Demand_Out_En,0},    //需量周期到输出-----------------------------------------10
  {1,1,0,0,1,PULSE_MODE,&PORT_ChangeP83Output,&Get_Slipe_Out_En,0},     //滑差周期到输出-----------------------------------------11
  {1,1,0,0,1,PULSE_MODE,&PORT_ChangeP83Output,&Get_Parse_Out_En,0},    //时段输出------------------------------------------------12
  
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP150Output,0,0},   //总有功脉冲灯-------------------------------------------------------------13
  {0,1,0,0,0,PULSE_MODE,&PORT_ChangeP151Output,0,0},   //总无功脉冲灯-------------------------------------------------------------14
  {1,0,0,1,0,PULSE_MODE,&PORT_ChangeP142Output_PUCK,0,0},  //喇叭报警 -------------------------------------------------------------15
  {1,0,0,0,0,PULSE_MODE,&PORT_Relay_On_PUCK,0,0},  //脉冲触发式继电器开启--------------------------------------------------16
  {1,1,0,0,0,PULSE_MODE,&PORT_Relay_Off_PUCK,0,0}  //脉冲触发式继电器关闭--------------------------------------------------17

};

//#pragma pack()



/********************************************************************************
INT8U  Get_AuxPort_Out(void)
函数功能：
入口：  
返回：
    无
********************************************************************************/
INT8U Get_AuxPort_Out(void)
{
  return LEVEL_MODE;
}
/********************************************************************************
INT8U  Get_Toogle_Out(void)
函数功能：
入口：  
返回：
    无
********************************************************************************/
INT8U Get_Toogle_Out(void)
{
  if(EXT_SWITCH_MODE EQ 0)
    return LEVEL_MODE;
  return PULSE_MODE;
}
/********************************************************************************
INT8U  Get_Sec_Out_En(void)
函数功能：根据模式字，获取秒脉冲输出使能
入口：  
返回：
    无
********************************************************************************/
INT8U Get_Sec_Out_En(void)
{
#if SEC_OUT_POWER_ON>0 //上电就输出秒脉冲
  return SEC_OUT_PUT_EN;
#else
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x00)
     return 1;  
  }
  return 0;
#endif
}

/********************************************************************************
INT8U  Change_Sec_Out(void)
函数功能：根据模式字，在运行过程中，使能秒脉冲
入口：  
返回：
    无
********************************************************************************/
void Init_Sec_Pulse(void)
{
  
#if SEC_OUT_POWER_ON>0 //上电就输出秒脉冲
   Read_Storage_Data_PUCK(SDI_OUTPUT_MODE,(INT8U *)(&Multi_Port_Mode.Mode),1);
   SET_STRUCT_SUM(Multi_Port_Mode);
#endif 
  
  
#if SEC_MULTI_PORT>0  //秒脉冲是复合端子 
    if(Get_Sec_Out_En())   //复合端子：当前是秒脉冲端子
    {
      Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
  
  #if MULTI_3_PORT>=2   //其他复合端子，与秒脉冲共用；
      Port_Out_Pub(EXT_ID_DEMAND,PORT_END);
      Port_Out_Pub(EXT_ID_SLIPE,PORT_END);
      Port_Out_Pub(EXT_ID_PARSE,PORT_END);
  #endif  
    }
    else                   //复合端子：当前不是秒脉冲端子
    {
      Port_Out_Pub(EXT_ID_SEC_EN,PORT_END);
    }
#else           //秒脉冲不是复合端子 
    Port_Out_Pub(EXT_ID_SEC_EN,PORT_START);
    //其他复合端子共用，将秒脉冲段度划开   
    if(Multi_Port_Mode.Mode EQ 0 || Multi_Port_Mode.Mode>2)   //当前秒脉冲是单独的，但模式字设置的端子排无效，默认为需量周期
       Multi_Port_Mode.Mode=2;      //设置错误！

#endif
}
/********************************************************************************
INT8U  Get_Parse_Out_En(void)
函数功能：根据模式字，获取时段输出使能
入口：  
返回：
    无
********************************************************************************/
INT8U Get_Parse_Out_En(void)
{
#if MULTI_3_PORT EQ 0  //单独的端子
   return 1;  
#elif MULTI_3_PORT EQ 1    //是复合端子，但与秒脉冲不共用
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x02)
     return 1;  
  }  
  return 0;
  
#elif (MULTI_3_PORT EQ 2)&&(SEC_OUT_POWER_ON>0)  //复合端子，且与秒脉冲共用    
    #if SEC_OUT_POWER_ON>0 //上电就输出秒脉冲
      return DEMAND_OUT_PUT_EN;
    #else 
     INT8U Len;
     INT8U Temp;
      
     Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
     if(1 EQ Len)
     {
        if((Temp&0x03) EQ 0x02)
         return 1;  
     }  
     return 0;
     #endif
#endif   
}
/********************************************************************************
INT8U  Get_Demand_Out_En(void)
函数功能：根据模式字，获取需量输出使能
入口：  
返回：
    无
********************************************************************************/
INT8U Get_Demand_Out_En(void)
{
#if MULTI_3_PORT EQ 0  //单独的端子
   return 1;  
#elif MULTI_3_PORT EQ 1    //是复合端子，但与秒脉冲不共用
  INT8U Len;
  INT8U Temp;
  
  if(DEMAND_OUT_MODE EQ 0)   //按滑差输出
      return 0;
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x01)
     return 1;  
  }  
  return 0;
  
#elif (MULTI_3_PORT EQ 2)&&(SEC_OUT_POWER_ON>0)  //复合端子，且与秒脉冲共用
    if(DEMAND_OUT_MODE EQ 0)   //按滑差
      return 0;
    
    #if SEC_OUT_POWER_ON>0 //上电就输出秒脉冲
      return DEMAND_OUT_PUT_EN;
    #else 
     INT8U Len;
      INT8U Temp;
      
      if(DEMAND_OUT_MODE EQ 0)   //按滑差输出
          return 0;
      Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
      if(1 EQ Len)
      {
        if((Temp&0x03) EQ 0x01)
         return 1;  
      }  
      return 0; 
      
    #endif
#endif                  
}
/********************************************************************************
INT8U  Get_Slipe_Out_En(void)
函数功能：根据模式字，获取滑差时间到输出使能
入口：  
返回：
    无
********************************************************************************/
INT8U Get_Slipe_Out_En(void)
{
#if MULTI_3_PORT EQ 0  //单独的端子
   return 1;  
#elif MULTI_3_PORT EQ 1    //是复合端子，但与秒脉冲不共用
  INT8U Len;
  INT8U Temp;
  
  if(DEMAND_OUT_MODE EQ 1)   //按需量周期
      return 0;
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x01)
     return 1;  
  }  
  return 0;
  
#elif (MULTI_3_PORT EQ 2)&&(SEC_OUT_POWER_ON>0)  //复合端子，且与秒脉冲共用
    if(DEMAND_OUT_MODE EQ 1)   //按需量周期
      return 0;
    
    #if SEC_OUT_POWER_ON>0 //上电就输出秒脉冲
      return DEMAND_OUT_PUT_EN;
    #else 
     INT8U Len;
      INT8U Temp;
      
      if(DEMAND_OUT_MODE EQ 1)   //按需量周期
          return 0;
      Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);      //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
      if(1 EQ Len)
      {
        if((Temp&0x03) EQ 0x01)
         return 1;  
      }  
      return 0; 
      
    #endif 
#endif     
}
/********************************************************************************
INT8U  Get_FeeAlarm_Out_En(void)
函数功能：根据模式字，获取欠费报警输出使能
入口：  
返回：
    无
********************************************************************************/
INT8U Get_FeeAlarm_Out_En(void)
{
/*
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);  // //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换。输出报警信号重新上电后恢复到秒脉冲输出。
  if(1 EQ Len)
  {
    if(Temp&0x03 EQ 0x03 && PREPAID_EN EQ 1)   //模式字2 bit5＝1，预付费功能
     return 1;  
  }  
 */
  return 0;
}
/********************************************************************************
INT8U  Get_GridAlarm_Out_En(void)
函数功能：根据模式字，获取滑差时间到输出使能
入口：  
返回：
    无
********************************************************************************/
INT8U Get_GridAlarm_Out_En(void)
{
  INT8U Len;
  INT8U Temp;
  
  Len=Read_Storage_Data(SDI_OUTPUT_MODE,&Temp,&Temp,1);  // //三合一输出状态:0-秒脉冲；1-需量周期；2-时段切换.输出报警信号重新上电后恢复到秒脉冲输出。
  if(1 EQ Len)
  {
    if((Temp&0x03) EQ 0x03 && POWER_CTRL_EN EQ 1)  //模式字2 bit4＝1，负控功能功能
     return 1;  
  }  
  return 0;
}

/********************************************************************************
void void Init_All_Device_Port(INT8U Mode)
函数功能：初始化所有端口,
入口：   根据不同状态，设定端口状态
返回：
    无
********************************************************************************/
void Init_All_Port(INT32U Mode)
{
   INT8U i;
   
  for(i=MIN_PORT_DI;i<=MAX_PORT_DI;i++)
  {
    if(0 EQ Const_Port_Status[i].NeedInit)
    {
      Ext_Port_Hander[i].InitFlag=1;
      continue;
    }
    
    if(SYS_NORMAL EQ Mode)
    {
      if(Const_Port_Status[i].FuncPtr)
        Const_Port_Status[i].FuncPtr(Const_Port_Status[i].InitLevel);    //正常模式：置输出为无效位
    }
    //其他模式，已经在Init_All_IO_XX()函数处理。    
    Ext_Port_Hander[i].InitFlag=1;
  }
}
/********************************************************************************
INT8U Port_Level_Out(INT8U Id,INT16U StartOrEnd)
函数功能：对外部端子排的电平输出操作函数
入口：
    Id -------外部端子功能Id号码
    StartOrEnd---------输出高电平还是低电
返回：
    无
注意：函数入口参数和Port_Pulse_Out保持一致！
********************************************************************************/
INT8U Port_Level_Out(INT8U Id,INT8U Level)
{
  if(Id<MIN_LEVEL_PORT_DI || Id>MAX_LEVEL_PORT_DI)
    return 0;
 
  if(Const_Port_Status[Id].LevelProprty EQ PULSE_MODE)
    return 0;
  
  if(Const_Port_Status[Id].LevelProprty EQ MULTI_MODE) //可变模式端子
  {
    if(Const_Port_Status[Id].GetOutMode EQ 0) //空函数
     return 0;
    
    if(Const_Port_Status[Id].GetOutMode() EQ PULSE_MODE) //可变模式为脉冲
      return 0;    
  }
  
  //电平模式输出,直接对端口输出电平
  if(Const_Port_Status[Id].FuncPtr)
  {
    if(PORT_END EQ Level)
      Const_Port_Status[Id].FuncPtr(!Const_Port_Status[Id].ValidLevel);
    else
      Const_Port_Status[Id].FuncPtr(Const_Port_Status[Id].ValidLevel);
    return 1;
  }
  
  return 0;}

/********************************************************************************
void Ext_Port_Out(INT8U Id,INT16U MsCounts)
函数功能：对外部端子排的冲输出操作函数脉
入口：
    Id -------外部端子功能Id号码
    PulseWidth ---外部端子为脉冲输出时，脉冲宽度，单位ms，电平输出时，此参数无效
返回：
    无
********************************************************************************/
INT8U Port_Pulse_Out(INT8U Id,INT16U PulseWidth)
{
  if(Id<MIN_PULSE_PORT_DI || Id>MAX_PULSE_PORT_DI)
    return 0;
  
  //注意，这里不判定是何种输出方式了！
  
  //脉冲模式输出，端口输出在ExtPort_xMs_Hook中调用。  
  if(PulseWidth EQ 0)  //清除端子的临时输出
  {
    Ext_Port_Hander[Id].Status=0;
    Ext_Port_Hander[Id].CurCount=0;
    Ext_Port_Hander[Id].CurCountBak=0;
    //Ext_Port_Hander[Id].LoopCount=0;
    return 0;
  }
  
  //Ext_Port_Hander[Id].LoopCount=1;  
  Ext_Port_Hander[Id].CurCountBak=PulseWidth/MS_HOOK_NUM;   //每次都更新一下
  //if(Ext_Port_Hander[Id].LoopCount EQ 1)   //首次启动
  //{    
    Ext_Port_Hander[Id].Status=1;
  //}
  return 1;
}
/********************************************************************************
void Port_Out_Pub(INT8U Id,INT16U Para)
入口：
    Id -------端子功能Id号码
    Para -------对于电平脉冲，PORT_START 表示激活有效电平；PORT_END 为无效电平；对于脉冲输出，表示脉冲宽度
返回：
    无
********************************************************************************/
void Port_Out_Pub(INT8U Id,INT16U Para)
{
  if(Id<MIN_PORT_DI || Id>MAX_PORT_DI)
    return ;
  
  if(Const_Port_Status[Id].MultiFlag) //是复合端子
  {
    if(Const_Port_Status[Id].MultiPortEn EQ 0)
      return ;
    
    if(Const_Port_Status[Id].MultiPortEn() EQ 0)  //是复合端子，但不允许该端子输出，仅对于电平方式
      return ;     
  }
    
  //电平方式
  if(Port_Level_Out(Id,Para))  //以最快的方式退出
     return ;
  
 //脉冲方式
  Port_Pulse_Out(Id,Para);  
 
}
/********************************************************************************
void Beep_For_Measu_Alarm_PUCK(void)
函数功能：蜂鸣器报警函数
入口：
返回：
    无
********************************************************************************/
void Beep_For_Measu_Alarm_PUCK(INT8U ErrInfo)
{ 

  //ReNew_Err_Code(DIS_MEAS_ERR);
#if HARD_ERR_BEEP
  Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
  Port_Out_Pub(INTER_ID_ALARM_DIS,150); 
#endif
  //不叫，事件在事件记录中读出供分析
 
}
/********************************************************************************
void Beep_For_Para(void)
函数功能：蜂鸣器报警:默认参数没有设置
入口：
返回：
    无
********************************************************************************/
void Beep_For_Para(void)
{
  Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_100);
  //Port_Out_Pub(INTER_ID_ALARM_DIS,BEEP_MODE_100); 
}
/********************************************************************************
void Beep_Only_Alarm_PUCK(void)
函数功能：蜂鸣器报警函数
入口：
返回：
    无
********************************************************************************/
void Beep_Only_Alarm_PUCK(void)
{
#if HARD_ERR_BEEP
 Port_Out_Pub(INTER_ID_ALARM_BEEP,BEEP_MODE_150); 
#endif
}
/********************************************************************************
void ExtPort_xMs_Hook(void)
函数功能：1ms对外部IO口的钩子函数
入口：
返回：
    无
********************************************************************************/
//ms端口钩子函数,毫秒级单位：MS_HOOK_NUM
void ExtPort_xMs_Hook(void)
{
  INT8U i;
  
  for(i=MIN_PULSE_PORT_DI;i<=MAX_PULSE_PORT_DI;i++)
  {
    
    //if(Const_Port_Status[i].LevelProprty EQ LEVEL_MODE) //电平模式
    //  continue ;
       
    //if(Const_Port_Status[i].NeedInit && (0 EQ Ext_Port_Hander[i].InitFlag))
    //  continue ;
    
    if(Const_Port_Status[i].LevelProprty EQ MULTI_MODE) //可变模式端子
    {
      if(Const_Port_Status[i].GetOutMode EQ 0) //空函数
       continue ;
      
      if(Const_Port_Status[i].GetOutMode() EQ LEVEL_MODE) //可变模式为电平
        continue ;
    }
   /**/
    
    //if(Ext_Port_Hander[i].LoopCount)
    //{
      switch(Ext_Port_Hander[i].Status)
      {
      case 0:   //无动作
        break;
      case 1:                                 //轮回启动
        //调用端口操作函数，电平是PULSE_OUT
        if(Const_Port_Status[i].FuncPtr)
          Const_Port_Status[i].FuncPtr(Const_Port_Status[i].ValidLevel);
        Ext_Port_Hander[i].Status=2;
        break;
      case 2:  //进行中
        if(Ext_Port_Hander[i].CurCount>=Ext_Port_Hander[i].CurCountBak-1)  //进入下一轮回
        {
            //Ext_Port_Hander[i].CurCount=0;
            //Ext_Port_Hander[i].Status=1;
            //Ext_Port_Hander[i].LoopCount--;   
            if(Const_Port_Status[i].FuncPtr)
              Const_Port_Status[i].FuncPtr(!Const_Port_Status[i].ValidLevel);
            //if(Ext_Port_Hander[i].LoopCount EQ 0) //结束
            { 
              Ext_Port_Hander[i].Status=0;     //结束
              Ext_Port_Hander[i].CurCount=0;
              Ext_Port_Hander[i].CurCountBak=0;   //
            }
         }
         else                               //当前轮回
         {  
           Ext_Port_Hander[i].CurCount++;         
         }
        break;
      }
    //}
  }
}
/********************************************************************************
void Wait_For_Power_On(void)
函数功能：蜂鸣器报警函数
入口：
返回：
    无
********************************************************************************/
#define WAIT_FOR_POWER_SEC 2

void Wait_For_Power_On(void)
{
  volatile INT32U SecTimr;
  INT8U SecNum;
  
  SecTimr=Sec_Timer_Pub;
  SecNum=0;
  
  while(1)
  {
    if(SecNum>=WAIT_FOR_POWER_SEC)
      return ;
    
    Clr_Ext_Inter_Dog();
    if(SecTimr!=Sec_Timer_Pub)
    {
      SecNum++;
      SecTimr=Sec_Timer_Pub;
    }
  }   
}