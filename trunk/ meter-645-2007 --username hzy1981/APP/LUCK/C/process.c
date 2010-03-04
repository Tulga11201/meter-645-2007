
/**
 * @file process.c
 *     { comment block }
 * @brief
 *     { brief description @ref process.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/28/2008 14:14
 * @note
 *     { paragraph where a note can be entered. }
 */

#include "Pub_PUCK.h"


#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "L3"
#endif

extern PROTO_DI Set_ParaModi_Proc(PROTO_DI ModiDI);
extern unsigned char Ser_Support_Code(item_t code);

/*
1:对于电能表故障类异常提示，异常一旦发生需将自动循环显示功能暂停，液晶屏固定显示该故障异常代码。当故障类异常只有一个发生时，液晶屏固定显示该故障类异常代码。当故障类异常有几个同时发生时，按照故障类异常代码递增顺序循环显示，显示间隔为循显时间，可以按任一键跳出故障异常代码显示。按键循环显示情况下无按键时间60S后，返回故障类异常代码自动循环显示。
2:对于事件类异常提示，一旦发生需要在循环显示的第一屏插入事件类异常代码。当事件类异常代码只有一个发生时，在循环显示的第一屏插入该事件类异常代码。当事件类异常代码有几个同时发生时，在循环显示的第一屏前按照递增顺序插入全部发生的事件类异常代码，显示间隔为循显时间。通过按键可以按显发生的全部异常代码。
3:对于CUP卡异常提示，在CPU卡处理过程中发生的异常需要在CPU卡处理结束后进行提示，抽出CPU卡后返回自动循环显示。（本地费控表具有该功能）
4:远程费控：err10，err16显示处理。
*/

#if DIS_METER_FAULT_EN >0
  CONST INT8U CONST_DIS_FAULT_ITEM[]=
  {DIS_CTRL_LOOP_ERR,DIS_ESAM_ERR,DIS_MEM_ERR,DIS_RTCBAT_LOW,DIS_RTC_ERR  
  };
  #define MAX_DIS_METER_FAULT_NUM (sizeof(CONST_DIS_FAULT_ITEM)/sizeof(INT8U))
  #define DIS_FAULT_SEC_TIME CYCLE
  #define DIS_FAULT_SJMP_SEC 60
#endif

  
  
  
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //远程费控表
  CONST INT8U CONST_DIS_DELAY_ITEM[]=
  {DIS_CERTI_ERR,DIS_CUR_MODI_KEY_ERR};
  
  #define MAX_DIS_METER_DELAYE_NUM (sizeof(CONST_DIS_DELAY_ITEM)/sizeof(INT8U))
  #define DIS_DELAY_SEC_TIME 10
#endif  
void Refresh_Curr_Offset(void)
{  
  if(modeA==dispmode)
  {
    if(dispoffset>=MODE_A_NUM)
      dispoffset=0;  
    else if(dispoffset<0)
      dispoffset=MODE_A_NUM-1;    
    return ;
  }
  
  if(modeB==dispmode)
  {
    if(dispoffset>=MODE_B_NUM)
      dispoffset=0;  
    else if(dispoffset<0)
      dispoffset=MODE_B_NUM-1;    
    return ;
  }
}

bool modeBorA () {
    if (dispmode != modeA) {
        dispmode = modeA;
    } else {
        dispmode = modeB;
    }
    dispcursor = MODE_A_B_BITS;
    dispoffset = 0;
    lcdshow(dispmode, dispoffset);
    return(TRUE);
}

bool modeBtoA () 
{
    if (dispmode != modeB) 
    {
        return (FALSE);
    }
    dispmode = modeA;
    dispcursor = MODE_A_B_BITS;
    dispoffset = 0;
    lcdshow(dispmode, dispoffset);
    return(TRUE);
}

bool modeCtoA () {
    if (dispmode != modeC) {
        return (FALSE);
    }
    dispmode = modeA;
    dispcursor = MODE_A_B_BITS;
    dispoffset = 0;
    lcdshow(dispmode, dispoffset);
    return(TRUE);
}

/********************************************************************************
PUCK:
函数功能：判断是否处于循显模式
入口：
返回：
    A模式
bool ModeABLoop(void)
{
  if((dispmode== modeA)||(dispmode==modeB))
    return LoopFlag;
  
  return 0;  
}
********************************************************************************/
/********************************************************************************
PUCK:
函数功能：A模式下的翻屏(其他模式下不具备自动翻屏功能)
入口：
返回：
    A模式
********************************************************************************/
bool disproll(void) 
{
    if (dispmode != modeA) 
    {
        return (FALSE);
    }
    dispcursor = MODE_A_B_BITS;
    dispoffset++;
    Refresh_Curr_Offset();
    lcdshow(dispmode,dispoffset);  //获取A模式下，对应显示屏的具体显示元素信息-----------PUCK
    return(TRUE);
}

/********************************************************************************
PUCK:右移，只针对C模式有效
函数功能：右移，更新 dispcursor(C模式)
入口：
返回：
********************************************************************************/
void dispright(void) 
{
  if (dispmode != modeC) //切换至C模式，相关状态初始化---------PUCK
  {
      dispcursor = RIGHTBITS;
      dispmode = modeC;
      dispcode.code = 0;
      Sub_Vlist.subindex=0;
      Sub_Vlist.exist=0;
  }
  if (dispcursor > MINBITS)  //光标右移，减1，因为显示是从右到左-------------PUCK
  {
      --dispcursor;
  } 
  else 
  {
      dispcursor = MAXBITS;
  }
  SET_HIGH_CODE_BIT;
  Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);
  display(dispmode, dispcode.code);
}
/********************************************************************************
PUCK:左移，只针对C模式有效
函数功能：左移，更新 dispcursor(C模式)
入口：
返回：
********************************************************************************/
void displeft(void) 
{
  if (dispmode != modeC)  //切换至C模式，相关状态初始化---------PUCK
  {
      dispcursor = LEFTBITS;
      dispmode = modeC;
      dispcode.code = 0;
      Sub_Vlist.subindex=0;
      Sub_Vlist.exist=0;
  }
  if (dispcursor < MAXBITS) //光标左移，加1，因为显示是从右到左-------------PUCK
  {
      ++dispcursor;
  } 
  else 
  {
      dispcursor = MINBITS;
  }
  SET_HIGH_CODE_BIT;
  Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);
  display(dispmode, dispcode.code);
}





// 根据红外接收的按键值进行处理。
/*
void Process (ikey_t key) {
    static u8 flg = 0;
    switch (key) {
        case 0x01 :
        case 0x02 :
        case 0x03 :
        case 0x04 :
        case 0x05 :
        case 0x06 :
        case 0x07 :
        case 0x08 :
        case 0x09 :
        case 0x0A :
        case 0x0B :
        case 0x0C :
        case 0x0D :
        case 0x0E :
        case 0x0F :
            setbits(key);
            break;
        case 0x1A :
            Key_Fast_LCD_Proc(DOWN_KEY_VALUE);
            break;
        case 0x19 :
            Key_Fast_LCD_Proc(UP_KEY_VALUE);
            break;
        case 0x14 :
            Key_Fast_LCD_Proc(LEFT_KEY_VALUE);
            break;
        case 0x1D :
            Key_Fast_LCD_Proc(RIGHT_KEY_VALUE);
            break;
        case 0x10 :
        case 0x1F :
            Key_Fast_LCD_Proc(AB_KEY_VALUE);  //0x10：进入A套显示；0x1F：进入B套显示
            break;
        case 0x18 :
            lcdlight(flg ^= 1);
            flg ^= 1;
            if(flg)
              Turn_Light_On();
            else
              Turn_Light_Off();
            break;
    }
}
*/
void Initial (void) 
{
     lcdinit();  //显示参数初始化----------PUCK
    //显示sram变量初始化----------PUCK
    dispoffset = -1;
    dispcursor = MODE_A_B_BITS;
    dispmode = modeA;
    dispcode.code = 0;    
    START_LOOP_DIS;
    
#ifdef DIS_PARA_JUMP_EN
    mem_set((void *)(&Para_Dis_Var),0x00,sizeof(Para_Dis_Var),(void *)(&Para_Dis_Var),sizeof(Para_Dis_Var));
    SET_STRUCT_SUM(Para_Dis_Var);
#endif    
    /*
    Init_DisItem();
    START_LOOP_DIS;
    screen(modeA, -1);
    */
#if SYS_ERR_DIS_EN >0
    mem_set((void *)(&Sys_Err_Info),0x00,sizeof(Sys_Err_Info),(void *)(&Sys_Err_Info),sizeof(Sys_Err_Info));
    Sys_Err_Info.LastFault=0xff;
    INIT_STRUCT_VAR(Sys_Err_Info);  //把头尾填齐
#endif   
}
/********************************************************************************
函数功能：检查是否关闭背光
入口：
返回：
********************************************************************************/
INT8U Chk_Light_Condition(void)
{
  FP32S temp;  
  temp=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C);
  temp/=UNIT_V;
  if(temp<Get_Un()*(FP32S)0.75)  //说明三相电压均低于75%Un
    return 1;  
  return 0;
}
/********************************************************************************
函数功能：更新低功耗下计数器
入口：
返回：Flag-----0：清除；1-------更新计数器
********************************************************************************/
void Refresh_Sleep_Countr(INT8U Flag)
{         
  if(Get_Sys_Status()==SYS_RESUME)
  {
    if(dispmode EQ modeA) //循显模式
    {
      if(Flag)
        Sleep_Sec_Countr.Var++; 
      else
        Sleep_Sec_Countr.Var=0;
      return ;
    }  
    
    if(dispmode EQ modeB) //键显模式
    { 
      Sleep_Sec_Countr.Var=Sec_Timer_Pub;  
    }
  }
  else
  {
    if(dispmode EQ modeA) //循显模式
      Sleep_Sec_Countr.Var=0;
    
    if(dispmode EQ modeB) //键显模式
      Sleep_Sec_Countr.Var=Sec_Timer_Pub;
  }
}

INT8U Judge_Mask_Dis(void)
{
  //全屏显示20秒内:138年翻转1次
  if(Sec_Timer_Pub<=20 && (Get_Sys_Status()==SYS_NORMAL))  //正常模式下，20秒内全屏显示
    return 1;
  
  if(poweroff())  //掉电情况下
    return 1;
  
  if((Key_Value_Pub.Key.Bit.UpKey)||(Key_Value_Pub.Key.Bit.DownKey))
    return 1;  
  
  return 0;  
}

/********************************************************************************
函数功能：电表故障信息:只能通过按钮才能消除
入口：
返回：1-----------------有电表故障显示；0---------------无电表故障显示。
********************************************************************************/
INT8U Dis_Meter_Fault(void) 
{
#if DIS_METER_FAULT_EN EQ 0   //不显示电表故障
  return 0;
#else
  char temp[10]={0};
  INT8U id,i,flag;
  
  //if(UP_COVER_STATUS EQ 0)
  //  ReNew_Err_Code(DIS_CTRL_LOOP_ERR);
  
  if(DOWN_COVER_STATUS)
    ReNew_Err_Code(DIS_MEM_ERR);
  
   //全屏显示20秒内:138年翻转1次
  
  if(Sys_Err_Info.FaultDis EQ 0)
    return 0;
  
  if(Judge_Mask_Dis())
    return 0;
    
  if((Sys_Err_Info.FaultCtrl EQ 0) && (Sec_Timer_Pub-Sec_Timer_Default.Var<DIS_FAULT_SJMP_SEC))
    return 0;
  
  if((Sys_Err_Info.FaultCtrl) && (Sec_Timer_Pub-Sec_Timer_Default.Var<CYCLE))       //故障模式下的循显
    return 1;
  
  if((Sys_Err_Info.FaultCtrl EQ 0) && (Sec_Timer_Pub-Sec_Timer_Default.Var>=DIS_FAULT_SJMP_SEC)) //按钮后，切换到故障模式
  {
    Sys_Err_Info.FaultCtrl=1;
  }
  
  flag=0;
  for(i=0;i<MAX_DIS_METER_FAULT_NUM;i++)
  {
    id=CONST_DIS_FAULT_ITEM[i];
    if(GET_BIT(Sys_Err_Info.ErrCode[id/8],id%8))  //找到显示的错误代码了
    {
      if(Sys_Err_Info.LastFault EQ id)
      {
        flag=1;
        continue ;
      }
      
      Sys_Err_Info.LastFault=id;
      strcpy(temp,"ERR-");
      temp[4]=id/10+'0';
      temp[5]=id%10+'0';
      Main_Dis_Info(temp);
      INIT_DIS_FAULT_TIMR;
      Turn_Light_Off();
      return 1;      
    }
  }
  return flag;
#endif 
}
/********************************************************************************
函数功能：电表故障或者事件显示:通过按钮消除，或者定时消除
入口：
返回：1-----------------有电表故障显示；0---------------无电表故障显示。
********************************************************************************/
INT8U Dis_Meter_Delay(void) 
{
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //远程费控表
  char temp[10]={0};
  INT8U id,i;
  
  /*
  if(UP_COVER_STATUS EQ 0)
    ReNew_Err_Code(DIS_CERTI_ERR);
  
  if(DOWN_COVER_STATUS)
    ReNew_Err_Code(DIS_CUR_MODI_KEY_ERR);
  */
  
  if(Sys_Err_Info.DelayDis EQ 0)
    return 0;
  
  if(Judge_Mask_Dis())
    return 0;
  
  for(i=0;i<MAX_DIS_METER_DELAYE_NUM;i++)
  {
    id=CONST_DIS_DELAY_ITEM[i];
    if(GET_BIT(Sys_Err_Info.ErrCode[id/8],id%8))  //找到显示的错误代码了
    {
      if(Sec_Timer_Pub-Sec_Timer_Delay.Var<=DIS_DELAY_SEC_TIME)
      {
        strcpy(temp,"ERR-");
        temp[4]=id/10+'0';
        temp[5]=id%10+'0';
        Main_Dis_Info(temp);
        return 1;
      }
      else
      {
        Sys_Err_Info.DelayDis=0; 
        CLR_BIT(Sys_Err_Info.ErrCode[id/8],id%8);
      }
    }
  }  
#endif
  
  return 0;
}
/********************************************************************************
函数功能：按钮清除故障显示代码
入口：
返回：
********************************************************************************/
void  Clr_Dis_Err_Key(void)
{
  
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //远程费控表  
  INT8U i;
 
  for(i=0;i<MAX_DIS_METER_DELAYE_NUM;i++)
  {
    Clr_Err_Code(CONST_DIS_DELAY_ITEM[i]);
  }
#endif
  
  Sys_Err_Info.LastFault=0xff;
  Sys_Err_Info.FaultCtrl=0;
  INIT_DIS_FAULT_TIMR;
  
}
/********************************************************************************
PUCK:更新显示内容,周期是 UPDATETIME ms
函数功能：按钮等快速响应的LCD处理
入口：
返回：
********************************************************************************/
void Key_Fast_LCD_Proc(void) 
{
  INT8U KeyValue;
  KeyValue=Get_MeterKey_PUCK(LUCK);
  
  if((KeyValue<MIN_KEY_VALUE)||(KeyValue>MAX_KEY_VALUE))
    return ;
  
  Light_Mode=LIGHT_ON_KEY;   //当前显示模式为按钮显示
  
  switch(KeyValue)    //以下获取具体的显示元素信息------------PUCK
  {
        case UP_KEY_VALUE :
            //本地费控，才显示与电费相关信息;远程费控：此函数不会返回与电费相关信息
            if(Get_Prepaid_Status() EQ PREPAID_MONEY_OVERDRAFT)
              DIS_BEEP_ALARM;
          
            dispnext();  //下翻---------------PUCK
            Refresh_Sleep_Countr(1);
            Clr_Dis_Err_Key();
            break;
        case DOWN_KEY_VALUE:
            //本地费控，才显示与电费相关信息;远程费控：此函数不会返回与电费相关信息
            if(Get_Prepaid_Status() EQ PREPAID_MONEY_OVERDRAFT)
              DIS_BEEP_ALARM;
          
            dispback();  //上翻---------------PUCK
            Refresh_Sleep_Countr(1);
            Clr_Dis_Err_Key();
            break;
            
        case LEFT_KEY_VALUE :
            //Debug_Print("LeftKey Pressed!");
            if(poweroff())  //掉电情况下，此键不起作用
              break;
            displeft();  //左移---------------PUCK
            break;
        case RIGHT_KEY_VALUE :
            //Debug_Print("RightKey Pressed!");
            if(poweroff()) //掉电情况下，此键不起作用
              break;
            dispright();  //右移----------------PUCK
            break;
        
        case AB_KEY_VALUE :   //AB模式切换----------------PUCK
            //Debug_Print("AB Mode Switch Key Pressed!");
            modeBorA();
            break;
              
        case A_KEY_VALUE :   //模式切换到A----------------PUCK
            //09-02-09 PUCK Add: modeAtoB
            dispmode = modeA;
            dispcursor = MODE_A_B_BITS;
            dispoffset = 0;
            lcdshow(dispmode, dispoffset);
            break;
            
        case B_KEY_VALUE :   //模式切换到B----------------PUCK
           //09-02-09 PUCK Add: modeAtoB
            dispmode = modeB;
            dispcursor = MODE_A_B_BITS;
            dispoffset = 0;
            lcdshow(dispmode, dispoffset);
            break;
   
       default:
        return ;
  }
  START_LIGHT_ON;
  screen(dispmode, dispcursor);  //刷屏----------PUCK
  LCD_Loop_Ms10Timr.Var=Ms10_Timer_Pub;
  LCD_Loop_Num.Var=0;
  RESET_LOOP_DIS;
  
#if SYS_ERR_DIS_EN >0
  Sys_Err_Info.LoopDis=1;  
#endif   
}

/********************************************************************************
PUCK:更新显示内容,周期是 UPDATETIME ms
函数功能：循显等慢速显示处理
入口：
返回：
********************************************************************************/
INT8U Dis_Meter_System_Err(void)
{
 #if SYS_ERR_DIS_EN >0
  char temp[10]={0};
  INT8U i,Flag;
  
  if(poweroff())  //掉电情况下
    return 0;
  
  //Sys_Err_Info.ErrNum=3;  Sys_Err_Info.ErrCode[0]=4;  Sys_Err_Info.ErrCode[1]=1;  Sys_Err_Info.ErrCode[4]=1;
    
  if(CHECK_STRUCT_VAR(Sys_Err_Info) EQ 0 || Sys_Err_Info.ErrNum>DIS_ERR_NUM)
   ASSERT_FAILED();
  
  if(Sys_Err_Info.ErrNum && Sys_Err_Info.LoopDis EQ 0)  //有错误且不是巡显才显示
  {
    dispoffset=-1;    //此显示是在第一屏插入的
    if(LOOP_SEC_TIMER_DIFF>=CYCLE)     //巡显错误代码和信息
    {  
      Flag=0;
      for(i=Sys_Err_Info.DisIndex+1;i<DIS_ERR_NUM;i++)
      {
        if(GET_BIT(Sys_Err_Info.ErrCode[i/8],i%8))  //找到显示的错误代码了
        {
          Sys_Err_Info.DisIndex=i;  
          Flag=1;
          break; 
        }
      }
      
      if(!Flag)   //当前显示的已经是最大项了,进入循显模式
      {
        Sys_Err_Info.DisIndex=0;
        Sys_Err_Info.LoopDis=1;
        disproll();
        RESET_LOOP_DIS;
        return 0;
      }      

      if(Flag)
      {
        strcpy(temp,"ERR: ");
        temp[5]=Sys_Err_Info.DisIndex/10+'0';
        temp[6]=Sys_Err_Info.DisIndex%10+'0';
        Main_Dis_Info(temp); 
      }
      
      if(Sys_Err_Info.DisIndex>=DIS_ERR_NUM)
        Sys_Err_Info.DisIndex=0;
      RESET_LOOP_DIS;      
    }
    return 1;
  }
#endif 
  return 0;
}
/********************************************************************************
PUCK:循显示表计
函数功能：
入口：
返回：
********************************************************************************/
void Dis_Meter_Loop(void)
{
  
#if SYS_ERR_DIS_EN >0      //已经显示的最大项了，进入自检错误显示
   if(Sys_Err_Info.ErrNum && dispoffset EQ MODE_A_NUM-1)  //循显完了，进入错误代码显示
   {
     Sys_Err_Info.LoopDis=0;
     return ;
   }
#endif 
     
   if((LOOP_SEC_TIMER_DIFF>CYCLE)&&disproll()) // A模式下，在1个周期后，没有按键按下，获取A模式下的显示信息--------PUCK
   {
     RESET_LOOP_DIS;
     Refresh_Sleep_Countr(1);
   }
   
   //if((LOOP_SEC_TIMER_DIFF>2*CYCLE)&& (poweroff() EQ 0) && modeBtoA())// B模式下，在2个循显周期后，没有按键按下，进入A模式，获取A模式下的信息--------PUCK
   if((LOOP_SEC_TIMER_DIFF>=KEY_JUMP_LOOP_TIME)&& (poweroff() EQ 0) && modeBtoA())// B模式下，在2个循显周期后，没有按键按下，进入A模式，获取A模式下的信息--------PUCK
      RESET_LOOP_DIS;
  
   if((LOOP_SEC_TIMER_DIFF>ALL_JUMP_LOOP_TIME)&&modeCtoA())   // C模式下，在2分钟后无按键按下，进入A模式，获取A模式下的信息--------PUCK
      RESET_LOOP_DIS;

   
   if (LIGHT_SEC_TIMER_DIFF== 0) 
   {
     if(poweroff()||Chk_Light_Condition())      //掉电或者三相电压都低于75%Un时，关闭背光
        Turn_Light_Off();
     else                   //非掉电情况下，打开背光
        Turn_Light_On();
   }
   
   if(LIGHT_SEC_TIMER_DIFF!=0)
   {
      //红外/剩余金额 < 报警金额 显示模式显示模式
     if((Light_Mode EQ LIGHT_ON_IRDA ||  Light_Mode EQ LIGHT_ON_MONEY)&& LIGHT_SEC_TIMER_DIFF>IRDA_LIGHT_ON_TIME) 
     {
       //Light_Mode=LIGHT_ON_NONE;
       CLR_LIGHT_ON;     
       Turn_Light_Off();
     }
     
     //按钮/插卡
     if((Light_Mode EQ LIGHT_ON_CARD || Light_Mode EQ LIGHT_ON_KEY) && (LIGHT_SEC_TIMER_DIFF>KEY_LIGHT_ON_TIME))
     {
#if SYS_ERR_DIS_EN >0
       //Sys_Err_Info.LoopDis=0;
#endif  
       //Light_Mode=LIGHT_ON_NONE;
       CLR_LIGHT_ON;
       Turn_Light_Off();
     }
   }
   
  if(Get_Sys_Status()==SYS_RESUME)
  {
    if((dispmode EQ modeA && Sleep_Sec_Countr.Var>MODE_A_NUM) && dispoffset EQ 0)   //循显模式
      return ;
  }
   
   screen(dispmode, dispcursor);  //刷屏----------PUCK
}
/********************************************************************************
PUCK:更新显示内容,周期是 UPDATETIME ms
函数功能：循显等慢速显示处理
入口：
返回：
********************************************************************************/
void Loop_Dis_LCD_Proc(void) 
{
  if(LCD_Loop_Ms10Timr.Var!=Ms10_Timer_Pub)
  {
    LCD_Loop_Num.Var+=(Ms10_Timer_Pub-LCD_Loop_Ms10Timr.Var);
    LCD_Loop_Ms10Timr.Var=Ms10_Timer_Pub;
    if(LCD_Loop_Num.Var<UPDATETIME/10)
      return ;
    LCD_Loop_Num.Var=TASK_RUN_TIME/10;
  }
  
  //全屏显示20秒内:138年翻转1次
  if(Sec_Timer_Pub<=20 && (Get_Sys_Status()==SYS_NORMAL))  //正常模式下，20秒内全屏显示
    return ;
  
  if(Dis_Meter_System_Err() EQ 0)
    Dis_Meter_Loop();   
}

/********************************************************************************
PUCK:更新显示内容,周期是 UPDATETIME ms
函数功能：按钮等快速响应的LCD处理，跳屏
入口：
返回：
********************************************************************************/
void Dis_Jump_Para(void) 
{
#ifdef DIS_PARA_JUMP_EN
   PROTO_DI modipara;
   if(modipara=Get_Para_Modi_DI())   //显示参数修改，更新参数，并点亮液晶------PUCK
    {
      if(Ser_Support_Code(modipara))
      {
        if(DI_TIME EQ modipara)  //时/分/秒不跳屏
          return ;
        
        RESET_LOOP_DIS;
        START_LIGHT_ON;
        dispmode=modeC; 
        dispcursor = MINBITS;        
        dispcode.code=modipara;
        SET_HIGH_CODE_BIT;
        
        Sub_Vlist.exist=0;
        Sub_Vlist.subindex=0;
        Sub_Vlist.fmtindex=0; 
        Sub_Vlist.offset=0; 
        
        Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);   
        display(modeC, dispcode.code);
      }
    }
#endif
}
/********************************************************************************
函数功能：更新系统错误显示代码
入口：Errcode，国电规定的显示出错代码
********************************************************************************/
void SetOrClr_Err_Code(INT8U ErrCode,INT8U SetOrClr)
{
 #if SYS_ERR_DIS_EN >0
  INT8U Byte,Bit,i;
  if(ErrCode>=DIS_ERR_NUM)
    return ;
  
  
  Byte=ErrCode/8;
  Bit=ErrCode%8;
  if(SetOrClr)
  {
    if(GET_BIT(Sys_Err_Info.ErrCode[Byte],Bit) EQ 0)
      Sys_Err_Info.ErrNum++;
    SET_BIT(Sys_Err_Info.ErrCode[Byte],Bit);
 
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //远程费控表     
    for(i=0;i<MAX_DIS_METER_DELAYE_NUM;i++)
    {
      if(CONST_DIS_DELAY_ITEM[i] EQ ErrCode)
      {
        Sys_Err_Info.DelayDis=1; 
        Sec_Timer_Delay.Var=Sec_Timer_Pub;
        break ;
      }        
    }
#endif
    
    for(i=0;i<MAX_DIS_METER_FAULT_NUM;i++)
    {
      if(CONST_DIS_FAULT_ITEM[i] EQ ErrCode)
      {
        Sys_Err_Info.FaultDis=1;
        Sys_Err_Info.FaultCtrl=1;
        return ;
      }        
    }
  }
  else
  {
    if(GET_BIT(Sys_Err_Info.ErrCode[Byte],Bit))
      Sys_Err_Info.ErrNum--;    
    CLR_BIT(Sys_Err_Info.ErrCode[Byte],Bit);    
    if(Sys_Err_Info.ErrNum EQ 0xff)
      Sys_Err_Info.ErrNum=0;
    
    for(i=0;i<MAX_DIS_METER_FAULT_NUM;i++)
    {
      Byte=CONST_DIS_FAULT_ITEM[i]/8;
      Bit=CONST_DIS_FAULT_ITEM[i]%8;
      if(GET_BIT(Sys_Err_Info.ErrCode[Byte],Bit)) //故障信息存在
      {
        break ;
      }        
    }
    
    if(i>=MAX_DIS_METER_FAULT_NUM)  //故障信息不存在
    {
        Sys_Err_Info.FaultDis=0;
        Sys_Err_Info.FaultCtrl=0;        
    }
    
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //远程费控表     
    for(i=0;i<MAX_DIS_METER_DELAYE_NUM;i++)
    {
      if(CONST_DIS_DELAY_ITEM[i] EQ ErrCode)
      {
        Sys_Err_Info.DelayDis=0;        
      }        
    }
#endif
    
  }
  
  
#endif
}
