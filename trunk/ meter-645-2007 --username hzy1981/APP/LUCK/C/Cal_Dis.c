
#define CAL_DIS_C
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "L5"
#endif

void Dis_Cal_Volt_Curr(void)
{
  //以下显示校表失败下的电压电流故障信息
    if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A/UNIT_V>=Get_Un()*0.3)
      SetOnDevice_PUCK(S_Ua);
    if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.B/UNIT_V>=Get_Un()*0.3)
      SetOnDevice_PUCK(S_Ub);
    if((FP32S)Measu_InstantData_ToPub_PUCK.Volt.C/UNIT_V>=Get_Un()*0.3)
      SetOnDevice_PUCK(S_Uc);
    
    if((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A/UNIT_A>=Get_In()*0.05)
    {
      SetOnDevice_PUCK(S_Ia);
      if(Measu_Status_Mode_ToPub_PUCK.A_APwrDir)
        SetOnDevice_PUCK(S_Ia_);      
    }
    if((FP32S)Measu_InstantData_ToPub_PUCK.Curr.B/UNIT_A>=Get_In()*0.05)
    {
      SetOnDevice_PUCK(S_Ib);
      if(Measu_Status_Mode_ToPub_PUCK.B_APwrDir)
        SetOnDevice_PUCK(S_Ib_);    
    }
    if((FP32S)Measu_InstantData_ToPub_PUCK.Curr.C/UNIT_A>=Get_In()*0.05)
    {
      SetOnDevice_PUCK(S_Ic);
      if(Measu_Status_Mode_ToPub_PUCK.C_APwrDir)
        SetOnDevice_PUCK(S_Ic_);
    }
}


void Cal_Dis_Proc(void)
{
  
#if CAL_METER_TYPE >= SELF_CAL_TYPE
  INT8U i,item;
  static INT8U dotnum=0;
    
  
  
  if(LCD_Loop_Ms10Timr.Var!=Ms10_Timer_Pub)
  {
    LCD_Loop_Num.Var+=(Ms10_Timer_Pub-LCD_Loop_Ms10Timr.Var);
    LCD_Loop_Ms10Timr.Var=Ms10_Timer_Pub;
    if(LCD_Loop_Num.Var<UPDATETIME/10)
      return ;
    LCD_Loop_Num.Var=TASK_RUN_TIME/10;
  }
  
    
  mem_set((INT8U *)Temp_Buf_PUCK,0x00,sizeof(Temp_Buf_PUCK),(INT8U *)Temp_Buf_PUCK,sizeof(Temp_Buf_PUCK));
  
  
  if(Real_Cal_Status.Cal_Status EQ 2)//校表成功
  {
    Turn_Light_On();
    strcpy((char *)Temp_Buf_PUCK,"SUCCEED ");
    Dis_Cal_Volt_Curr();
    Main_Dis_Info((char *)Temp_Buf_PUCK);
    return ;
  }
  
  if(Real_Cal_Status.Cal_Status EQ 1 && Cal_Proc_Status.Cal_Status EQ 2)//校表失败
  {
    Turn_Light_Off();    
   
    item=CAL_A_POWER;
    for(i=CAL_A_POWER;i<=CAL_C_CURR;i++)
    {
      if(Real_Cal_Status.Cal_Info[i].Cal_OK EQ 0)   //当前项失败
      {
        item=i;
        break;
      }
    }    
    strcpy((char *)Temp_Buf_PUCK,"CAL---");
    Temp_Buf_PUCK[6]=Real_Cal_Status.Cal_Info[item].Cal_Times/10+'0';
    Temp_Buf_PUCK[7]=Real_Cal_Status.Cal_Info[item].Cal_Times%10+'0';
    
    Code_Dis_Info((char *)Temp_Buf_PUCK);
    
    SetOnLED8Device_PUCK(N_LED(18),item/10+'0');
    SetOnLED8Device_PUCK(N_LED(19),item%10+'0');
    strcpy((char *)Temp_Buf_PUCK," FAILED");
    
    Dis_Cal_Volt_Curr();    
    Main_Dis_Info((char *)Temp_Buf_PUCK);
    return ;
  }
  
 
  item=Cal_Proc_Status.Cal_Item;    
  if(item EQ 0)          //校表暂停
  {
    
    Turn_Light_On();
    //显示主窗口
#ifdef LCD_MIN_8    
    strcpy((char *)Temp_Buf_PUCK,"  PAUSE ");
    Code_Dis_Info((char *)Temp_Buf_PUCK);
    
    strcpy((char *)Temp_Buf_PUCK,"   CAL  ");
    Main_Dis_Info((char *)Temp_Buf_PUCK);
#else  
    for(i=3;i<=12;i++)
      SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-3]); 
#endif
    Dis_Cal_Volt_Curr();
    return ;
  }
  
  
  
  strcpy((char *)Temp_Buf_PUCK,"CAL ");
  if(Cal_Proc_Status.Cal_Status EQ 1)   //校表进行中
  {
    if(Real_Cal_Status.Cal_Info[item].Cal_OK)  //当前校正ok
      strcpy((char *)(Temp_Buf_PUCK+4),"GOOD");
    else
    {
       //获取校表 item
      Temp_Buf_PUCK[4]=item/10+'0';
      Temp_Buf_PUCK[5]=item%10+'0';
    }
  } 
    
  
//显示主窗口
#ifdef LCD_MIN_8  
  for(i=2;i<=9;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-2]);
#else  
  for(i=3;i<=12;i++)
    SetOnLED8Device_PUCK(N_LED(i),Temp_Buf_PUCK[i-3]); 
#endif
  
//显示校表项目
#if LCD_PROPERTY==LCD_SD_ZXW ||  LCD_PROPERTY==LCD_GW_ZXW 
    SetOnLED8Device_PUCK(N_LED(18),item/10+'0');
    SetOnLED8Device_PUCK(N_LED(19),item%10+'0');
#else
    SetOnLED8Device_PUCK(N_LED(20),item/10+'0');
    SetOnLED8Device_PUCK(N_LED(21),item%10+'0');
  
#endif
  
//显示进度条  -----次数
  dotnum++;  
#if LCD_PROPERTY==LCD_SD_ZXW ||  LCD_PROPERTY==LCD_GW_ZXW 
  if(dotnum>=8)
    dotnum=0;
  for(i=0;i<=dotnum;i++)
  {
    switch(i)
    {
      case 6:
        SetOnLED8Device_PUCK(N_LED(16),Real_Cal_Status.Cal_Info[item].Cal_Times/10+'0');
         break;
      case 7:
        SetOnLED8Device_PUCK(N_LED(17),Real_Cal_Status.Cal_Info[item].Cal_Times%10+'0'); 
        break;
      default:
        SetOnLED8Device_PUCK(N_LED(10+i),'-');
        break;
    }
  }
  
#else
  if(dotnum>=7)
    dotnum=0;
    for(i=0;i<=dotnum;i++)    
      SetOnLED8Device_PUCK(N_LED(14+i),'-');
#endif
  
  Dis_Cal_Volt_Curr();
  UpdataLcdShow(); 
  
#endif
}

