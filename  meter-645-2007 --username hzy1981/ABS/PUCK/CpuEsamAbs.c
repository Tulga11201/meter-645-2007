#define CPU_ESAM_ABS_C
#include "Pub_PUCK.h"

#if PREPAID_METER>0

#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

void Pay_Uart_Send(INT8U *txbuf,INT16U txnum)
{
 
  if(Curr_Media_Status.Uart_Type EQ PAY_CPU_CARD)
    Debug_Print("--------Send To CPU_CARD-------->");
  else
    Debug_Print("--------Send To ESAM------------>");
  
  //DEBUG_BUF_PRINT(txbuf,txnum,PRINT_HEX,30);
  
  WAITFOR_DRV_MS_TIMEOUT(1)
  for(;txnum>0;)
  {               
    TXD3 = *txbuf;
    txbuf++;
    txnum--;    
    while((SSR12 & SAU_DATA_STORED));
    WAITFOR_DRV_MS_TIMEOUT(1)
  }
  
  Uart_Pay_Ready();
}
/**********************************************************************************
函数功能：共享串口操作
入口：
          Cpu_Esam------------非0-----表示打开 CPU_ESAM; 0---------表示打开485口

**********************************************************************************/ 
void Open_Pay_Uart(INT8U Cpu_Esam)
{
  if(Cpu_Esam)
  {
    //PU1_bit.no4=1; //接收上拉
    Open_Channel_PUCK(PAY_UART,BAUD_CPU_ESAM,SAU_PARITY_EVEN);
  }
  else
    Open_Channel_PUCK(PAY_UART,Chanel_Para[PAY_UART].Baud,SAU_PARITY_EVEN); 
}

/**********************************************************************************
函数功能：释放 CPU_CARD 所需资源

**********************************************************************************/ 
void Realse_Local_Pay_Source(void)
{
    Cpu_Esam_Hard_Operate(PAY_CPU_CARD,CPU_ESAM_DRV_POWER_OFF);
    Cpu_Esam_Hard_Operate(PAY_ESAM,CPU_ESAM_DRV_POWER_OFF);
    Open_Pay_Uart(0);
    Curr_Media_Status.Uart_Type=PAY_NONE;
    SET_STRUCT_SUM(Curr_Media_Status);
}
#endif


/**********************************************************************************
函数功能：转换显示代码

**********************************************************************************/ 
INT8U Convert_Dis_Code(void)
{
    
  if(Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr)
        return DIS_CERTI_ERR;           //10-------认证错误
 
  if(Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr)
        return DIS_CERTI_ERR;             //10-------认证错误
  
  if(Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err)
        return DIS_CERTI_ERR;           //10-------认证错误
   
  if(Card_Error_State.CardErrorState.Esam_Extern_Auth_Err)  
       return DIS_CUR_VERY_NOEVEN;   //11-------ESAM验证失败
                        
  if(Card_Error_State.CardErrorState.MeterIdErr)
        return DIS_GUEST_ID_ERR;        //12-------ESAM验证失败
  
  if(Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR)
        return DIS_CHARGE_NUM_ERR;    //13-------充值次数错误
  
  if(Card_Error_State.CardErrorState.MoneyLimitErr)
        return DIS_BUY_TOO_ENOUGH;    //14-------购电超囤积
  
  if(Card_Error_State.CardErrorState.CPU_Para_Card_Version_Err)
       return DIS_CUR_PARA_CARD_INVALID;      //15-------现场参数设置卡对本表已经失效
  
  if(Card_Error_State.CardErrorState.Password_Key_Updata_ERR)
        return DIS_CUR_MODI_KEY_ERR;   //16-------修改密钥错误
    
  if(Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err)
        return DIS_NO_LEAD_KEY_ERR;    //17-------未按铅封键
   
  if(Card_Error_State.CardErrorState.CPU_CARD_LOSE)
        return DIS_CPU_CARD_LOSE_ERR;            //18-------提前拔卡
  
  if(Card_Error_State.CardErrorState.Meter_Id_Set_Card_Id_Is_FULL_Err)
      return DIS_CUR_MODI_METER_ERR;   //19-------修改表号卡满（该卡无空余表号分配）
  
  
  if(Card_Error_State.CardErrorState.Password_Count_Number_Is_Zero_Err)
        return DIS_CUR_KEY_CARD0_ERR;    //20---------修改密钥卡次数为0
  
  
  if(Card_Error_State.CardErrorState.CardIdErr)
        return DIS_METER_REGISTERD_ERR;    //21-------表计已开户（开户卡插入已经开过户的表计）
  
  
  if(Card_Error_State.CardErrorState.CARD_STATE_ERR)
        return DIS_METER_NO_REGIST_ERR;     //22------------表计未开户（用户卡插入还未开过户的表计）
  
  
  if(Card_Error_State.CardErrorState.CPU_CARD_CARD_ATR_ERR)
        return DIS_NOKNOWED_CARD_ERR;       //23------------卡损坏或不明类型卡（如反插卡，插铁片等）

  
  //DIS_LOW_VOLT_ERR                      //24--------------表计电压过低（此时表计操作IC卡可能会导致表计复位或损害IC卡）
  
  if(Card_Error_State.CardErrorState.CPU_CARD_DATA_HEAD_ERR || 
     Card_Error_State.CardErrorState.CPU_CARD_DATA_END_ERR  || 
     Card_Error_State.CardErrorState.CPU_CARD_DATA_CHECK_ERR || 
     Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR )
    return DIS_CARD_FILED_FORMAT_ERR;             //25--------------卡文件格式不合法（包括帧头错，帧尾错，效验错）
  
  if(Card_Error_State.CardErrorState.CardKindErr)
        return DIS_CARD_TYPE_ERR;            //26--------------卡类型错
  if(Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR)
        return DIS_CARD_TYPE_ERR;          //26--------------卡类型错
   
  if(Card_Error_State.CardErrorState.CPU_NEW_CARD_INI_ERR)
        return DIS_CARD_REGISTERD_ERR;    //27--------------已经开过户的新开户卡（新开户卡回写区有数据）
    
  if(Card_Error_State.CardErrorState_INT32U)
        return DIS_OTHER_ERR;            //28--------------其他错误（卡片选择文件错，读文件错，些文件错等）
  
  return OK;
}

/**********************************************************************************
函数功能：CPU卡切换处理
入口：
          Cpu_Esam------------非0-----表示打开 CPU_ESAM; 0---------表示打开485口

**********************************************************************************/ 
void CPU_Card_Main_Proc(void)
{

#if PREPAID_METER>0
  INT8U Result,Flag;
  char temp[10];
  

  if(PREPAID_LOCAL_REMOTE !=PREPAID_LOCAL)
     return ;
  
  if(JUDGE_CPU_INSERT)  //插卡处理
  {
      if((Curr_Media_Status.Media_Type EQ PAY_NONE) && CHECK_STRUCT_SUM(Curr_Media_Status))
      {
        if(JUDGE_CPU_INSERT EQ 0)  //当前是拔卡状态，干扰
        return;
        
        ENABLE_BEEP_ALARM;
        Curr_Media_Status.Media_Type=PAY_CPU_CARD;
        SET_STRUCT_SUM(Curr_Media_Status);
        Light_Mode=LIGHT_ON_CARD;
        SetOnDevice_PUCK(S_DUKA);
        SetOnDevice_PUCK(S_ZHONG);
        Main_Dis_Info("In CARD");
        Turn_Light_On();
        
        Flag=0;
        if(Check_Max_Volt_Below(Get_Un()*0.7))   //电压太低，不能买电
          Flag=1;

        Result=ICcardMain();        
        if(Result)
        {
          Port_Out_Pub(INTER_ID_ALARM_BEEP,300);  //叫1秒
          strcpy(temp,"SUCCEED");
        }
        else
        {
          Port_Out_Pub(INTER_ID_ALARM_BEEP,1000);  //叫3秒
          strcpy(temp,"FAILED");
        }
        Main_Dis_Info(temp);
        OS_TimeDly_Sec(1);//1s睡眠
        
        if(Flag)           //电压太低，不能买电
          Result=DIS_LOW_VOLT_ERR;
        else
          Result=Convert_Dis_Code(); 
        while(JUDGE_CPU_INSERT)
        {
          Turn_Light_On();
          OS_TimeDly_Ms(100);
          Clear_Ext_Dog();    //最快的任务：清CPU外部看门狗
          Clear_Task_Dog();   //清任务看门狗
          
          SetOnDevice_PUCK(S_DUKA);
          if(Result EQ OK) //操作成功
          {
            SetOnDevice_PUCK(S_CHENGGONG);
            SetOnDevice_PUCK(S_DANGQIAN);
            SetOnDevice_PUCK(S_SHENGYU);
            SetOnDevice_PUCK(S_DIAN);          
            if(PREPAID_MODE EQ PREPAID_ENG)  //电量型预付费
            {
              SetOnDevice_PUCK(S_LIANG);              
              //显示剩余电费.......
              lcd_data(0x00900100, "XXXXX#.##|kWh");   //当前剩余电量
            }
            else                                //电费型预付费
            {
              SetOnDevice_PUCK(S_FEI); 
              //显示剩余电费.......
              lcd_data(0x00900200, "XXXXXXX#.##|yuan");   //当前剩余金额   
            }            
            
            lcd_thismonth(1); ///< "本月",
            lcd_Pre_Pay (1,1);              ///< 显示"预付费类容",  
            UpdataLcdShow();
          }
          else
          {
            if(Card_Error_State.CardErrorState.MoneyLimitErr)  //囤积
              SetOnDevice_PUCK(S_TUNJI);
            
            SetOnDevice_PUCK(S_SHIBAI);
            strcpy(temp,"ERR: ");
            temp[5]=Result/10+'0';
            temp[6]=Result%10+'0';
            Main_Dis_Info(temp);                        
          }          
          
        }
        Realse_Local_Pay_Source();
      }
  }
  else                //拔卡处理
  {
    if((Curr_Media_Status.Media_Type EQ PAY_CPU_CARD) && CHECK_STRUCT_SUM(Curr_Media_Status))  //原先已插卡
    {
       if(JUDGE_CPU_INSERT)  //当前是插卡状态，干扰
        return;
        
        Sys_Err_Info.DisIndex=0;
        Main_Dis_Info("OUT CARD");
        Port_Out_Pub(INTER_ID_ALARM_BEEP,500);
        Curr_Media_Status.Media_Type=PAY_NONE;
        SET_STRUCT_SUM(Curr_Media_Status);
        Realse_Local_Pay_Source();
        OS_TimeDly_Sec(1);//1s睡眠
        START_LOOP_DIS;
        dispmode = modeA;
    }
  }
#endif
}

#if PREPAID_METER>0
/**********************************************************************************
函数功能：
入口：
出口： 
**********************************************************************************/ 
INT8U Wait_For_Pay_Uart_Data(INT16U RdDstLen,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen)
{

  INT16U i;
  
  if(pDst>pDstStart+MaxDstLen)
  {
    ASSERT_FAILED();  
    return CPU_ESAM_DRV_FUZZY_ERR;
  }
  
  //写数据后，ESAM/CPU的延时 延时：
  //1.14583 ms:1byte
  for(i=0;i<RdDstLen*10;i++)
  {
    Clr_Ext_Inter_Dog(); 
    WAITFOR_DRV_MS_TIMEOUT(5)
    if(Pay_Uart_Rec_Len>=RdDstLen)
      break;
  } 
    
  
  if((JUDGE_CPU_INSERT EQ 0)&& (Curr_Media_Status.Uart_Type EQ PAY_CPU_CARD))  //提前拔卡
  {
    return CPU_ESAM_DRV_OUT_ERR;
  }

  if(Pay_Uart_Rec_Len>=RdDstLen)
  {   
    mem_cpy((void *)(pDst),(void *)(Pay_Uart_Rec_Buf),RdDstLen,(void *)(pDstStart),MaxDstLen);
    Uart_Pay_Ready();
    
    if(Curr_Media_Status.Uart_Type EQ PAY_CPU_CARD)
        Debug_Print("<--------Rec From CPU_CARD--------");
      else
        Debug_Print("<--------Rec From ESAM------------");
    //DEBUG_BUF_PRINT((INT8U *)pDst,RdDstLen,PRINT_HEX,30); 
    
    return CPU_ESAM_DRV_OK;
  }
  else
    return CPU_ESAM_DRV_RECLEN_ERR;    
  
  //return CPU_ESAM_DRV_OK;  
}
/**********************************************************************************
函数功能：对 CPU卡,ESAM的底层操作,包括OPERATE_RST_COOL等.
入口：
          Type------------CPU卡,ESAM的类型;
          Operate---------表对 CPU卡,ESAM的操作动作类型,如 OPERATE_RST_COOL 等;
          pDst------------对 CPU卡,ESAM的操作后,获取的数据内容放置缓冲区; 
                          对于 PAY_CPU_CARD的冷复位，返回8字节的离散因子。
                          对于其他介质的其他类型操作，暂无返回数据，后期按需增加。
          pDstStart-------对 CPU卡,ESAM的操作后,获取的数据内容放置缓冲区头地址,与pDst,MaxDstLen一起限定越界. 
          MaxDstLen-------pDstStart目标缓冲区的数据最大长度.
出口： CPU,ESAM操作宏.
**********************************************************************************/ 
INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen)
{
  INT8U Flag;
   
  if(pDst>pDstStart+MaxDstLen)
  {
    ASSERT_FAILED();
    return CPU_ESAM_DRV_FUZZY_ERR;
  }
  
  if((Curr_Media_Status.Uart_Type !=Type) && IS_CPU_ESAM_CPU_ESAM_DRV(Type))  //当前操作是 CPU/ESAM类型，前次操作类型不一样
  {
    if(IS_CPU_ESAM_CPU_ESAM_DRV(Curr_Media_Status.Uart_Type) EQ 0)  //前次操作不是 CPU/ESAM类型,串口初始化
      Open_Pay_Uart(1);
    Curr_Media_Status.Uart_Type=Type;
    SET_STRUCT_SUM(Curr_Media_Status);    
    Switch_Uart_To_Pay(Type);
  }
    
  
  Uart_Pay_Ready();
  
  if(Cpu_Esam_Hard_Operate(Type,Operate) EQ 0)
    ASSERT_FAILED();
  
  if(CPU_ESAM_DRV_RST_COOL EQ Operate)  //CPU卡冷复位,需要得到 卡号和分散因子
  {
    switch(Type)
    {
      case PAY_CPU_CARD:
      case PAY_ESAM:
        Flag=Wait_For_Pay_Uart_Data(13,pDst,pDstStart,MaxDstLen);
        if(Flag != CPU_ESAM_DRV_OK)
          return Flag;
        
        if((pDst[0]!=0x3B)||(pDst[1]!=0x69)||(pDst[2]!=0x00)||(pDst[3]!=0x00)||(pDst[4]!=0x41))
          return CPU_ESAM_DRV_DATA_ERR;        
      break;

    }    
  }
  
  /*
  if(CPU_ESAM_DRV_POWER_OFF EQ Operate)
  {
    Curr_Media_Status.Uart_Type=PAY_NONE;
    SET_STRUCT_SUM(Curr_Media_Status);  
    
    PM1_bit.no3=0;P1_bit.no3=0;
    PM1_bit.no4=0;P1_bit.no4=0;
    PM5_bit.no1=0;P5_bit.no1=0;
    Switch_Uart_To_Pay(PAY_CPU_CARD);
  }
  */
  
  return CPU_ESAM_DRV_OK;
}

/**********************************************************************************
函数功能：对 CPU卡,ESAM的通信数据操作,包括读写等.
入口：
          Type------------CPU卡,ESAM的类型;
          Srcbuf----------对 CPU卡,ESAM发送的数据包,如 读取ESAM购电次数等;
          SrcLen----------对 CPU卡,ESAM发送的数据长度
          RdOrWr----------对 CPU卡,ESAM发送的数据是读操作还是写操作，函数入口用 WRITE_CPU_ESAM或者 READ_CPU_ESAM
          RdDstLen------对 CPU卡,ESAM的操作后的,希望获取的数据长度;
          pDst------------对 CPU卡,ESAM的操作后,获取的数据内容放置缓冲区;          
          pDstStart-------对 CPU卡,ESAM的操作后,获取的数据内容放置缓冲区头地址,与pDst,MaxDstLen一起限定越界. 
          MaxDstLen-------pDstStart目标缓冲区的数据最大长度.
出口： CPU,ESAM操作宏.
**********************************************************************************/ 
INT8U Cpu_Esam_Comm_Proc(INT8U Type,INT8U *Srcbuf,INT16U SrcLen,INT8U RdOrWr,INT8U RdDstLen,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen)
{
  
  if(pDst>pDstStart+MaxDstLen || RdDstLen>MaxDstLen || Type>MAX_CPU_ESAM_TYPE)
  {
    ASSERT_FAILED();
    return CPU_ESAM_DRV_FUZZY_ERR;
  }
  
  if((Curr_Media_Status.Uart_Type !=Type) && IS_CPU_ESAM_CPU_ESAM_DRV(Type))  //当前操作是 CPU/ESAM类型，前次操作类型不一样
  {
    if(IS_CPU_ESAM_CPU_ESAM_DRV(Curr_Media_Status.Uart_Type) EQ 0)  //前次操作不是 CPU/ESAM类型,串口初始化
      Open_Pay_Uart(1);
    Curr_Media_Status.Uart_Type=Type;
    SET_STRUCT_SUM(Curr_Media_Status);    
    Switch_Uart_To_Pay(Type);
  }
  
  Pay_Uart_Send(Srcbuf,SrcLen); 
  Clr_Ext_Inter_Dog(); 
  return Wait_For_Pay_Uart_Data(RdDstLen,pDst,pDstStart,MaxDstLen);

}

#endif