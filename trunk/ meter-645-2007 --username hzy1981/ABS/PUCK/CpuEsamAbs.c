#define CPU_ESAM_ABS_C
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P0"
#endif


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
�������ܣ������ڲ���
��ڣ�
          Cpu_Esam------------��0-----��ʾ�� CPU_ESAM; 0---------��ʾ��485��

**********************************************************************************/ 
void Open_Pay_Uart(INT8U Cpu_Esam)
{
  if(Cpu_Esam)
  {
    //PU1_bit.no4=1; //��������
    Open_Channel_PUCK(PAY_UART,BAUD_CPU_ESAM,SAU_PARITY_EVEN);
  }
  else
    Open_Channel_PUCK(PAY_UART,Chanel_Para[PAY_UART].Baud,SAU_PARITY_EVEN); 
}

/**********************************************************************************
�������ܣ��ͷ� CPU_CARD ������Դ

**********************************************************************************/ 
void Realse_Local_Pay_Source(void)
{
    Cpu_Esam_Hard_Operate(PAY_CPU_CARD,CPU_ESAM_DRV_POWER_OFF);
    Cpu_Esam_Hard_Operate(PAY_ESAM,CPU_ESAM_DRV_POWER_OFF);
    Open_Pay_Uart(0);
    Curr_Media_Status.Uart_Type=PAY_NONE;
    SET_STRUCT_SUM(Curr_Media_Status);
}
/*********************************************************************************
�������ܣ�ת����ʾ����

**********************************************************************************/ 
/*
INT8U Convert_Dis_Code(void)
{
    
  if(Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr)
        return DIS_CERTI_ERR;           //10-------��֤����
 
  if(Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr)
        return DIS_CERTI_ERR;             //10-------��֤����
  
  if(Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err)
        return DIS_CERTI_ERR;           //10-------��֤����
   
  if(Card_Error_State.CardErrorState.Esam_Extern_Auth_Err)  
       return DIS_CUR_VERY_NOEVEN;   //11-------ESAM��֤ʧ��

  if(Card_Error_State.CardErrorState.MeterIdErr)
        return DIS_GUEST_ID_ERR;        //12-------ESAM��֤ʧ��
  
  if(Card_Error_State.CardErrorState.CARD_BUY_COUNT_ERR)
        return DIS_CHARGE_NUM_ERR;    //13-------��ֵ��������
  
  if(Card_Error_State.CardErrorState.MoneyLimitErr)
        return DIS_BUY_TOO_ENOUGH;    //14-------���糬�ڻ�
  
  if(Card_Error_State.CardErrorState.CPU_Para_Card_Version_Err)
       return DIS_CUR_PARA_CARD_INVALID;      //15-------�ֳ��������ÿ��Ա����Ѿ�ʧЧ
  
  if(Card_Error_State.CardErrorState.Password_Key_Updata_ERR)
        return DIS_CUR_MODI_KEY_ERR;   //16-------�޸���Կ����
    
  if(Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err)
        return DIS_NO_LEAD_KEY_ERR;    //17-------δ��Ǧ���
   
  if(Card_Error_State.CardErrorState.CPU_CARD_LOSE)
        return DIS_CPU_CARD_LOSE_ERR;            //18-------��ǰ�ο�
  
  if(Card_Error_State.CardErrorState.Meter_Id_Set_Card_Id_Is_FULL_Err)
      return DIS_CUR_MODI_METER_ERR;   //19-------�޸ı�ſ������ÿ��޿����ŷ��䣩
  
  
  if(Card_Error_State.CardErrorState.Password_Count_Number_Is_Zero_Err)
        return DIS_CUR_KEY_CARD0_ERR;    //20---------�޸���Կ������Ϊ0
  
  
  if(Card_Error_State.CardErrorState.CardIdErr)
        return DIS_METER_REGISTERD_ERR;    //21-------����ѿ����������������Ѿ��������ı�ƣ�
  
  
  if(Card_Error_State.CardErrorState.CARD_STATE_ERR)
        return DIS_METER_NO_REGIST_ERR;     //22------------���δ�������û������뻹δ�������ı�ƣ�
  
  
  if(Card_Error_State.CardErrorState.CPU_CARD_CARD_ATR_ERR)
        return DIS_NOKNOWED_CARD_ERR;       //23------------���𻵻������Ϳ����練�忨������Ƭ�ȣ�

  
  //DIS_LOW_VOLT_ERR                      //24--------------��Ƶ�ѹ���ͣ���ʱ��Ʋ���IC�����ܻᵼ�±�Ƹ�λ����IC����
  
  if(Card_Error_State.CardErrorState.CPU_CARD_DATA_HEAD_ERR || 
     Card_Error_State.CardErrorState.CPU_CARD_DATA_END_ERR  || 
     Card_Error_State.CardErrorState.CPU_CARD_DATA_CHECK_ERR || 
     Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR )
    return DIS_CARD_FILED_FORMAT_ERR;             //25--------------���ļ���ʽ���Ϸ�������֡ͷ��֡β��Ч���
  
  if(Card_Error_State.CardErrorState.CardKindErr)
        return DIS_CARD_TYPE_ERR;            //26--------------�����ʹ�
  if(Card_Error_State.CardErrorState.BUY_CARD_KIND_ERR)
        return DIS_CARD_TYPE_ERR;          //26--------------�����ʹ�
   
  if(Card_Error_State.CardErrorState.CPU_NEW_CARD_INI_ERR)
        return DIS_CARD_REGISTERD_ERR;    //27--------------�Ѿ����������¿��������¿�������д�������ݣ�
    
  if(Card_Error_State.CardErrorState_INT32U)
        return DIS_OTHER_ERR;            //28--------------�������󣨿�Ƭѡ���ļ������ļ���Щ�ļ���ȣ�
  
  return OK;
}
*/ 
#endif
/**********************************************************************************
�������ܣ�CPU���л�����
��ڣ�
          Cpu_Esam------------��0-----��ʾ�� CPU_ESAM; 0---------��ʾ��485��

**********************************************************************************/ 
void Dis_Card_Result(INT8U Ok_Flag,INT8U Result)
{
  Mult_List temp_list={0};
  char temp[10]={0};
  
  SetOnDevice_PUCK(S_DUKA);
  if(Ok_Flag) //�����ɹ�
  {
    SetOnDevice_PUCK(S_CHENGGONG);
    
    switch(GetCardKind())
    {
       
      case GWFAR_MOD_METERID_CARD:
        temp_list.exist=MULIT_EXSIT;
        temp_list.len=4;
        temp_list.subindex=1;
        temp_list.fmtindex=9;
        temp_list.offset=2;        
        lcd_data(PDI_METER_ID, "########|",temp_list);   //��ŵ�8λ
        break;
      default:
        SetOnDevice_PUCK(S_DANGQIAN);
        SetOnDevice_PUCK(S_SHENGYU);
        SetOnDevice_PUCK(S_DIAN);
        if(PREPAID_MODE EQ PREPAID_ENG)  //������Ԥ����
        {
          SetOnDevice_PUCK(S_LIANG);
          //��ʾʣ����.......
          lcd_data(0x00900100, "XXXXX#.##|kWh",temp_list);   //��ǰʣ�����
        }
        else                                //�����Ԥ����
        {
          SetOnDevice_PUCK(S_FEI);
          //��ʾʣ����.......
          lcd_data(0x00900200, "XXXXXXX#.##|yuan",temp_list);   //��ǰʣ����
        }            
        
        lcd_thismonth(1); ///< "����",
        lcd_Pre_Pay (1,1);              ///< ��ʾ"Ԥ��������"
        break;
    }
    UpdataLcdShow();
  }
  else
  {
    if(Card_Error_State.CardErrorState.MoneyLimitErr)  //�ڻ�
      SetOnDevice_PUCK(S_TUNJI);
    
    SetOnDevice_PUCK(S_SHIBAI);
    strcpy(temp,"ERR-");
    temp[4]=Result/10+'0';
    temp[5]=Result%10+'0';
    temp[6]=0;
    Main_Dis_Info(temp);
  }
}
/**********************************************************************************
�������ܣ�CPU���л�����
��ڣ�
          Cpu_Esam------------��0-----��ʾ�� CPU_ESAM; 0---------��ʾ��485��

**********************************************************************************/ 
void CPU_Card_Main_Proc(void)
{

#if PREPAID_METER>0 && (PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  INT8U Result,Ok_Flag; 
  if(JUDGE_CPU_INSERT)  //�忨����
  {
    if(Curr_Media_Status.LastStus EQ CARD_IN)  //�����ǲ���״̬��û�аγ�
      return ;
    
    if((Curr_Media_Status.Media_Type EQ PAY_NONE) && CHECK_STRUCT_SUM(Curr_Media_Status))
    {
      if(JUDGE_CPU_INSERT EQ 0)  //��ǰ�ǰο�״̬������
        return;
      
      Curr_Media_Status.LastStus=CARD_IN;
      ENABLE_BEEP_ALARM;
      Turn_Light_On();
      Curr_Media_Status.Media_Type=PAY_CPU_CARD;
      SET_STRUCT_SUM(Curr_Media_Status);
      Light_Mode=LIGHT_ON_CARD;
      //SetOnDevice_PUCK(S_DUKA);
      //SetOnDevice_PUCK(S_ZHONG);
      //UpdataLcdShow();        
      
      Ok_Flag=1;
      if(Check_Max_Volt_Below(Get_Un()*0.7))   //��ѹ̫�ͣ��������
        Ok_Flag=0;

      Result=ICcardMain();
      
      /*  ���Լ��㶨
      if(INOP_INSERT_FIRSETUSERCARD_ERR)  //�ظ�����,����
      {
        Ok_Flag=0;
      }
      */
      
      if(Ok_Flag && Result)   //�����ɹ�
      {
        Port_Out_Pub(INTER_ID_ALARM_BEEP,300);  //��1��
        Clr_Err_Code(DIS_CERTI_ERR);
        Clr_Err_Code(DIS_CUR_MODI_KEY_ERR);
      }
      else
      {
        Port_Out_Pub(INTER_ID_ALARM_BEEP,1000);  //��3��
        //strcpy(temp,"FAILED");
      }
      //Main_Dis_Info(temp);
      //OS_TimeDly_Sec(1);//1s˯��
      
      if(Ok_Flag EQ 0)           //��ѹ̫�ͣ��������
        Result=DIS_LOW_VOLT_ERR;
      else
      {
        Ok_Flag=Result;
        Result=Convert_Dis_Code();
      }

      Clear_Ext_Dog();    //����������CPU�ⲿ���Ź�
      Dis_Card_Result(Ok_Flag,Result);
      CLR_LIGHT_ON;      
      
      Sys_Err_Info.DisIndex=0;
      Port_Out_Pub(INTER_ID_ALARM_BEEP,300);
      Curr_Media_Status.Media_Type=PAY_NONE;
      SET_STRUCT_SUM(Curr_Media_Status);
      Realse_Local_Pay_Source();
      
      OS_TimeDly_Sec(1);//1s˯��
      
      RESET_LOOP_DIS;
      dispmode = modeA;        
      OS_TimeDly_Sec(1);
    }
  }
  else
  {
    Curr_Media_Status.LastStus=CARD_OUT;
    SET_STRUCT_SUM(Curr_Media_Status);
  }
#endif
}

/**********************************************************************************
�������ܣ�
��ڣ�
���ڣ� 
**********************************************************************************/ 
INT8U Wait_For_Pay_Uart_Data(INT16U RdDstLen,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen)
{
#if PREPAID_METER>0
  
  INT16U i;
  
  if(pDst>pDstStart+MaxDstLen)
  {
    ASSERT_FAILED();  
    return CPU_ESAM_DRV_FUZZY_ERR;
  }
  
  //д���ݺ�ESAM/CPU����ʱ ��ʱ��
  //1.14583 ms:1byte
  for(i=0;i<RdDstLen*10;i++)
  {
    Clr_Ext_Inter_Dog(); 
    WAITFOR_DRV_MS_TIMEOUT(5)
    if(Pay_Uart_Rec_Len>=RdDstLen)
      break;
  } 
    
  
  if((JUDGE_CPU_INSERT EQ 0)&& (Curr_Media_Status.Uart_Type EQ PAY_CPU_CARD))  //��ǰ�ο�
  {
    return CPU_ESAM_DRV_OUT_ERR;
  }

  //if(Pay_Uart_Rec_Len>=RdDstLen)
  //{
    mem_cpy((void *)(pDst),(void *)(Pay_Uart_Rec_Buf),RdDstLen,(void *)(pDstStart),MaxDstLen);
    Uart_Pay_Ready();
    
    if(Curr_Media_Status.Uart_Type EQ PAY_CPU_CARD)
        Debug_Print("<--------Rec From CPU_CARD--------");
      else
        Debug_Print("<--------Rec From ESAM------------");
    DEBUG_BUF_PRINT((INT8U *)pDst,RdDstLen,PRINT_HEX,30); 
    
    return CPU_ESAM_DRV_OK;
  //}
  //else
  //  return CPU_ESAM_DRV_RECLEN_ERR;  
#else
  return CPU_ESAM_DRV_OK;
#endif 
}

/**********************************************************************************/
INT8U Find_Fram_Exist(INT8U *Src,INT16U MaxDstLen)
{
  INT16U i,j;
  for(i=0;i<MaxDstLen;i++)
  {
     if((Src[i] EQ 0x3B)&&(Src[i+1] EQ 0x69)&&(Src[i+2] EQ 0x00)&&(Src[i+3] EQ 0x00)&&(Src[i+4] EQ 0x41))  
     {
       for(j=0;j<13;j++)
         Src[j]=Src[j+i];
       return 1;    
     }
  }
  return 0;  
}
/**********************************************************************************
�������ܣ��� CPU��,ESAM�ĵײ����,����OPERATE_RST_COOL��.
��ڣ�
          Type------------CPU��,ESAM������;
          Operate---------��� CPU��,ESAM�Ĳ�����������,�� OPERATE_RST_COOL ��;
          pDst------------�� CPU��,ESAM�Ĳ�����,��ȡ���������ݷ��û�����; 
                          ���� PAY_CPU_CARD���临λ������8�ֽڵ���ɢ���ӡ�
                          �����������ʵ��������Ͳ��������޷������ݣ����ڰ������ӡ�
          pDstStart-------�� CPU��,ESAM�Ĳ�����,��ȡ���������ݷ��û�����ͷ��ַ,��pDst,MaxDstLenһ���޶�Խ��. 
          MaxDstLen-------pDstStartĿ�껺������������󳤶�.
���ڣ� CPU,ESAM������.
**********************************************************************************/ 
INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen)
{
#if PREPAID_METER>0
  
  INT8U Flag;
   
  if(pDst>pDstStart+MaxDstLen)
  {
    ASSERT_FAILED();
    return CPU_ESAM_DRV_FUZZY_ERR;
  }
  
  if((Curr_Media_Status.Uart_Type !=Type) && IS_CPU_ESAM_CPU_ESAM_DRV(Type))  //��ǰ������ CPU/ESAM���ͣ�ǰ�β������Ͳ�һ��
  {
    if(IS_CPU_ESAM_CPU_ESAM_DRV(Curr_Media_Status.Uart_Type) EQ 0)  //ǰ�β������� CPU/ESAM����,���ڳ�ʼ��
      Open_Pay_Uart(1);
    Curr_Media_Status.Uart_Type=Type;
    SET_STRUCT_SUM(Curr_Media_Status);    
    Switch_Uart_To_Pay(Type);
  }
    
  
  Uart_Pay_Ready();
  
  if(Cpu_Esam_Hard_Operate(Type,Operate) EQ 0)
    ASSERT_FAILED();
  
  if(CPU_ESAM_DRV_RST_COOL EQ Operate)  //CPU���临λ,��Ҫ�õ� ���źͷ�ɢ����
  {
    switch(Type)
    {
      case PAY_CPU_CARD:
      case PAY_ESAM:
        Flag=Wait_For_Pay_Uart_Data(25,pDst,pDstStart,MaxDstLen);
        if(Flag != CPU_ESAM_DRV_OK)
          return Flag;
        
        if(Find_Fram_Exist(pDst,MaxDstLen) EQ 0)
          return CPU_ESAM_DRV_DATA_ERR;        
      break;

    }    
  }
#endif
  
  return CPU_ESAM_DRV_OK;  
}

/**********************************************************************************
�������ܣ��� CPU��,ESAM��ͨ�����ݲ���,������д��.
��ڣ�
          Type------------CPU��,ESAM������;
          Srcbuf----------�� CPU��,ESAM���͵����ݰ�,�� ��ȡESAM���������;
          SrcLen----------�� CPU��,ESAM���͵����ݳ���
          RdOrWr----------�� CPU��,ESAM���͵������Ƕ���������д��������������� WRITE_CPU_ESAM���� READ_CPU_ESAM
          RdDstLen------�� CPU��,ESAM�Ĳ������,ϣ����ȡ�����ݳ���;
          pDst------------�� CPU��,ESAM�Ĳ�����,��ȡ���������ݷ��û�����;          
          pDstStart-------�� CPU��,ESAM�Ĳ�����,��ȡ���������ݷ��û�����ͷ��ַ,��pDst,MaxDstLenһ���޶�Խ��. 
          MaxDstLen-------pDstStartĿ�껺������������󳤶�.
���ڣ� CPU,ESAM������.
**********************************************************************************/ 
INT8U Cpu_Esam_Comm_Proc(INT8U Type,INT8U *Srcbuf,INT16U SrcLen,INT8U RdOrWr,INT8U RdDstLen,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen)
{
#if PREPAID_METER>0
  if(pDst>pDstStart+MaxDstLen || RdDstLen>MaxDstLen || Type>MAX_CPU_ESAM_TYPE)
  {
    ASSERT_FAILED();
    return CPU_ESAM_DRV_FUZZY_ERR;
  }
  
  if((Curr_Media_Status.Uart_Type !=Type) && IS_CPU_ESAM_CPU_ESAM_DRV(Type))  //��ǰ������ CPU/ESAM���ͣ�ǰ�β������Ͳ�һ��
  {
    if(IS_CPU_ESAM_CPU_ESAM_DRV(Curr_Media_Status.Uart_Type) EQ 0)  //ǰ�β������� CPU/ESAM����,���ڳ�ʼ��
      Open_Pay_Uart(1);
    Curr_Media_Status.Uart_Type=Type;
    SET_STRUCT_SUM(Curr_Media_Status);    
    Switch_Uart_To_Pay(Type);
  }
  
  Pay_Uart_Send(Srcbuf,SrcLen); 
  Clr_Ext_Inter_Dog(); 
  return Wait_For_Pay_Uart_Data(RdDstLen,pDst,pDstStart,MaxDstLen);
  
#else
  return CPU_ESAM_DRV_OK; 
#endif
}


