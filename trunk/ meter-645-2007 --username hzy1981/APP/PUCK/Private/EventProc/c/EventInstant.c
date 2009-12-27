#define EVENTINSTANT_C
#include "Pub_PUCK.h"
/*
typedef struct
{
  INT32U Qual_Up_Vol[3];//Խ�ϸ����޵�ѹֵ,0-2�ֱ��ʾA-B-C��
  INT32U Qual_Low_Vol[3];//Խ�ϸ����޵�ѹֵ
  
  INT32U Over_Vol[3];//��ѹ�����޵�ѹֵ
}S_Event_Vol_Cur;
����ӱ 17:25:37
EXT S_Event_Vol_Cur Event_Vol_Cur;
����ӱ 17:26:00
Over_Vol[3] �����
*/



typedef struct
{
  STORA_DI Data_DI;
  INT8U Data_Len;
  void *Data_Dst;
}CONST_EVENT_PARA;


CONST CONST_EVENT_PARA  Const_Event_Proper[]={
  {DI_LOSSVOLT_U_UP,2,(void *)(&EventInsParaVar.LossVolt_U_Up)},
  {DI_LOSSVOLT_U_DOWN,2,(void *)(&EventInsParaVar.LossVolt_U_Down)},
  {DI_LOSSVOLT_I_DOWN,3,(void *)(&EventInsParaVar.LossVolt_I_Down)},
  {DI_LOSSVOLT_TIME,1,(void *)(&EventInsParaVar.LossVolt_Time)},
  
  {DI_DOWNVOLT_U_UP,2,(void *)(&EventInsParaVar.DownVolt_U_Up)},
  {DI_DOWNVOLT_TIME,1,(void *)(&EventInsParaVar.DownVolt_Time)},
  
  {DI_UPVOLT_U_DOWN,2,(void *)(&EventInsParaVar.UpVolt_U_Down)},
  {DI_UPVOLT_U_TIME,1,(void *)(&EventInsParaVar.UpwnVolt_Time)},  

  {DI_CUTPARSE_U_UP,2,(void *)(&EventInsParaVar.CutParse_U_Up)},
  {DI_CUTPARSE_I_UP,3,(void *)(&EventInsParaVar.CutParse_I_Up)},
  {DI_CUTPARSE_TIME,1,(void *)(&EventInsParaVar.CutParse_Time)},
  
  
  {DI_VOLT_NOEVEN_UP,2,(void *)(&EventInsParaVar.Volt_NoEven_Up)},
  {DI_VOLT_NOEVEN_TIME,1,(void *)(&EventInsParaVar.Volt_NoEven_Time)},
  
  
  {DI_CURR_NOEVEN_UP,2,(void *)(&EventInsParaVar.Curr_NoEven_Up)},
  {DI_CURR_NOEVEN_TIME,1,(void *)(&EventInsParaVar.Curr_NoEven_Time)},
  
  
  {DI_LOSSCURR_U_DOWN,2,(void *)(&EventInsParaVar.LossCurr_U_Down)},
  {DI_LOSSCURR_I_UP,3,(void *)(&EventInsParaVar.LossCurr_I_Up)},
  {DI_LOSSCURR_I_DOWN,3,(void *)(&EventInsParaVar.LossCurr_I_Down)},
  {DI_LOSSCURR_TIME,1,(void *)(&EventInsParaVar.LossCurr_Time)},
  
  
  {DI_UPCURR_I_DOWN,2,(void *)(&EventInsParaVar.UpCurr_I_Down)},
  {DI_UPCURR_TIME,1,(void *)(&EventInsParaVar.UpCurr_Time)},
  
  
  {DI_CUTCURRE_U_DOWN,2,(void *)(&EventInsParaVar.CutCurre_U_Down)},
  {DI_CUTCURR_I_UP,3,(void *)(&EventInsParaVar.CutCurr_I_Up)},
  {DI_CUTCURR_TIME,1,(void *)(&EventInsParaVar.CutCurr_Time)},
  
  {DI_NEGCURR_ACPOW_DOWN,3,(void *)(&EventInsParaVar.NegCurr_Acpow_Down)},
  {DI_NEGCURR_TIME,1,(void *)(&EventInsParaVar.NegCurr_Time)},
  
  
  {DI_OVERLOAD_ACPOW_DOWN,3,(void *)(&EventInsParaVar.OverLoad_AcPow_Down)},
  {DI_OVERLOAD_TIME,1,(void *)(&EventInsParaVar.OverLoad_Time)},
  
  
  {DI_OVERDE_ACPOW_DOWN,3,(void *)(&EventInsParaVar.OverDe_Acpow_Down)},
  {DI_OVERDE_ACPOW_UP,3,(void *)(&EventInsParaVar.OverDe_Reacpow_Down)},
  {DI_OVERDE_TIME,1,(void *)(&EventInsParaVar.OverDe_Time)},
    
    
  {DI_DOWNPF_I_DOWN,2,(void *)(&EventInsParaVar.DownPf_I_Down)},  
  {DI_DOWNPF_TIME,1,(void *)(&EventInsParaVar.DownPf_Time)},
  
  
  {DI_CURR_NO1EVEN_I_UP,2,(void *)(&EventInsParaVar.Curr_No1Even_I_Up)},
  {DI_CURR_NO1EVEN_TIME,1,(void *)(&EventInsParaVar.Curr_No1Even_Time)},
  
  {DI_START_VOLT,1,(void *)(&EventInsParaVar.Start_Volt)},  
};


#define EVENT_PARA_NUM  (sizeof(Const_Event_Proper)/sizeof(CONST_EVENT_PARA))
  
/***********************************************************************
�������ܣ���ʼ����ȡĳ���¼�����
��ڣ���
���ڣ���
***********************************************************************/
void Init_One_Event_Para(INT32U Data_DI)
{
  INT8U i,temp[4];  
  
  for(i=0;i<EVENT_PARA_NUM;i++)
  {
    if(Const_Event_Proper[i].Data_DI EQ Data_DI)
    {
      if(Read_Storage_Data_PUCK(Const_Event_Proper[i].Data_DI,temp,Const_Event_Proper[i].Data_Len))
      {
         switch(Const_Event_Proper[i].Data_Len)
        {
        case 1:
          *((INT8U *)Const_Event_Proper[i].Data_Dst)=Bcd2Hex(temp,Const_Event_Proper[i].Data_Len);
          break;
        case 2:
          *((INT16U *)Const_Event_Proper[i].Data_Dst)=Bcd2Hex(temp,Const_Event_Proper[i].Data_Len);
          break;
        case 3:
          *((INT32U *)Const_Event_Proper[i].Data_Dst)=(INT32U)(Bcd2Hex(temp,Const_Event_Proper[i].Data_Len)&0x00FFFFFF);
          break;
        case 4:
          *((INT32U *)Const_Event_Proper[i].Data_Dst)=Bcd2Hex(temp,Const_Event_Proper[i].Data_Len);
          break; 
        }   
      }
      SET_STRUCT_SUM(EventInsParaVar);
      return ;
    }
  }
}

/***********************************************************************
�������ܣ���ʼ����ȡ˲̬�ֵ�ȫ������
��ڣ���
���ڣ���
***********************************************************************/
void Init_Event_Instant_Para(void)
{
  INT8U i,temp[4];  
  
  for(i=0;i<EVENT_PARA_NUM;i++)
  {
    if(Read_Storage_Data_PUCK(Const_Event_Proper[i].Data_DI,temp,Const_Event_Proper[i].Data_Len))
    {
      switch(Const_Event_Proper[i].Data_Len)
      {
      case 1:
        *((INT8U *)Const_Event_Proper[i].Data_Dst)=Bcd2Hex(temp,Const_Event_Proper[i].Data_Len);
        break;
      case 2:
        *((INT16U *)Const_Event_Proper[i].Data_Dst)=Bcd2Hex(temp,Const_Event_Proper[i].Data_Len);
        break;
      case 3:
          *((INT32U *)Const_Event_Proper[i].Data_Dst)=(INT32U)(Bcd2Hex(temp,Const_Event_Proper[i].Data_Len)&0x00FFFFFF);
          break;
      case 4:
          *((INT32U *)Const_Event_Proper[i].Data_Dst)=Bcd2Hex(temp,Const_Event_Proper[i].Data_Len);
          break; 
      }
    }
  }
  
  SET_STRUCT_SUM(EventInsParaVar);
  
}

/***********************************************************************
�������ܣ����ж����е�ѹ�Ƿ�С����ڲ���
��ڣ�IsVoltNeg----------------------�ǲ������������
���ڣ�0-----------��С����ڲ�����1-------------��С����ڲ���
***********************************************************************/
INT8U Check_Max_Volt_Below(FP32S BelowValue)
{
  FP32S temp;
  
  temp=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C);
  temp/=UNIT_V;
  if(temp<BelowValue)        //���е�ѹ����������ѹ, ���е�ѹ������AUXIL_POWER_RATIO*Unʱ������Ϊ�Ǹ�����Դ
     return 1;  
  
  return 0;
}
/***********************************************************************
�������ܣ������¼�����ǰ����
��ڣ�IsVoltNeg----------------------�ǲ������������
���ڣ�0-----------�����¼���Ҫ��һ����飻1-------------�����¼�����Ϊ����
�����ѹ������70%Un��
����
***********************************************************************/
INT8U Check_Power_Grid_Event(INT8U IsVoltNeg)
{
  FP32S temp;
  
  if(Get_Sys_Status()!=SYS_NORMAL)
    return 1;
  
  if(IsVoltNeg EQ 0 && SEQ_ERR_CHK_GRID && Read_Event_Status(ID_EVENT_VOLT_NEG_SEQ))  //�����������¼��ж�:�������ˣ������¼�������
    return 1;
  
  if(Check_Max_Volt_Below(Get_Un()*EventInsParaVar.Start_Volt/100.0)) //���е�ѹ����������ѹ, ���е�ѹ������AUXIL_POWER_RATIO*Unʱ������Ϊ�Ǹ�����Դ
     return 1;
  
  temp=Measu_InstantData_ToPub_PUCK.Volt.A+Measu_InstantData_ToPub_PUCK.Volt.B+Measu_InstantData_ToPub_PUCK.Volt.C;
  temp/=UNIT_V;
  if(temp<Get_Un()*EventInsParaVar.Start_Volt/100.0)   //(���е�ѹ֮��)<����ѹ   
    return 1;
  
  return 0;
}

/***********************************************************************
�������ܣ���ȡʧѹ˲ʱ״̬��
��ڣ���
���ڣ���
�����ࣨ���ࣩ����ϵͳ�У�ĳ�ฺ�ɵ���������������������ѹ��·�ĵ�ѹ���ڵ��ܱ�αȵ�ѹ��78��ʱ���ҳ���ʱ�����60�룬���ֹ�����Ϊʧѹ
***********************************************************************/
#ifdef ID_EVENT_A_LOSS_VOLT
void Check_Loss_Volt(void)
{ 
  INT8U i;
  volatile INT32U *Volt,*Curr;
  
  for(i=0;i<3;i++)
  {    
    Volt=&Measu_InstantData_ToPub_PUCK.Volt.A+i;
    Curr=&Measu_InstantData_ToPub_PUCK.Curr.A+i;
    if(((FP32S)(*Curr)/UNIT_A)>=((FP32S)EventInsParaVar.LossVolt_I_Down/10000.0))
    {
      if(((FP32S)(*Volt)/UNIT_V)<=((FP32S)EventInsParaVar.LossVolt_U_Up/10.0))  //����
        Set_Event_Instant(ID_EVENT_A_LOSS_VOLT+i);    //ʧѹ
      
      if(((FP32S)(*Volt)/UNIT_V)>=((FP32S)EventInsParaVar.LossVolt_U_Down/10.0))  //����
        Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT+i);    //ʧѹ�ָ�
    }
    else
       Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT+i);    //ʧѹ�ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT); 
}
#endif

/***********************************************************************
�������ܣ���ȡǷѹ˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_VOLT_LESS
void Check_Down_Volt(void)
{
  INT8U i;
  volatile INT32U *Volt;
  
  for(i=0;i<3;i++)
  {
    Volt=&Measu_InstantData_ToPub_PUCK.Volt.A+i;
    if(((FP32S)(*Volt)/UNIT_V)<=((FP32S)EventInsParaVar.DownVolt_U_Up/10.0))
      Set_Event_Instant(ID_EVENT_A_VOLT_LESS+i);    //Ƿѹ
    else
      Clr_Event_Instant(ID_EVENT_A_VOLT_LESS+i);    //Ƿѹ�ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_VOLT_LESS);  
}
#endif
/***********************************************************************
�������ܣ���ȡ��ѹ˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_VOLT_OVERLOAD
void Check_Up_Volt(void)
{
  INT8U i;
  volatile INT32U *Volt;
  
  for(i=0;i<3;i++)
  {
    Volt=&Measu_InstantData_ToPub_PUCK.Volt.A+i;
    if(((FP32S)(*Volt)/UNIT_V)>=((FP32S)EventInsParaVar.UpVolt_U_Down/10.0))
      Set_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD+i);    //��ѹ
    else
      Clr_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD+i);    //��ѹ�ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  
}
#endif

/***********************************************************************
�������ܣ���ȡ����˲ʱ״̬��
��ڣ���
���ڣ���
�оݣ���ѹС������ѹ������С����������  
***********************************************************************/
#ifdef ID_EVENT_A_LOSS_PARSE
void Check_Loss_Parse(void)
{
  INT8U i;
  volatile INT32U *Volt,*Curr;
  
  for(i=0;i<3;i++)
  {    
    Volt=&Measu_InstantData_ToPub_PUCK.Volt.A+i;
    Curr=&Measu_InstantData_ToPub_PUCK.Curr.A+i;
    if(((FP32S)(*Volt)/UNIT_V)<=((FP32S)EventInsParaVar.CutParse_U_Up/10.0))
    {
      if(((FP32S)(*Curr)/UNIT_A)<=((FP32S)EventInsParaVar.CutParse_I_Up/10000.0))  //����
        Set_Event_Instant(ID_EVENT_A_LOSS_PARSE+i);    //����
      else
        Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE+i);    //����ָ�
    }
    else
        Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE+i);    //����ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  
}
#endif
/***********************************************************************
�������ܣ���ȡ��ѹ��ƽ��״̬��
������������£�B ���ѹ/�����������㡣
***********************************************************************/
#ifdef ID_EVENT_VOLT_NO_EVEN
void Check_Volt_NoEven(void)
{
  INT8U Flag;
  FP32S tempmax,tempmin,tempeven,NoEvenRate;
  INT32U B_volt;
  

  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)
  {
    B_volt=0;
  }
  else
  {
    B_volt=Measu_InstantData_ToPub_PUCK.Volt.B;
  }
  
  //--------------------------------------��ѹ��ƽ��------------------------------------------
  tempmax=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,B_volt,Measu_InstantData_ToPub_PUCK.Volt.C);
  
  if(Flag==PARSE_331) //331�µ���С��ѹ�� A��C֮��ѡ��
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.C);
  else
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,B_volt,Measu_InstantData_ToPub_PUCK.Volt.C);
    
  tempeven=((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A+B_volt+Measu_InstantData_ToPub_PUCK.Volt.C)/3.0;
  

  NoEvenRate=(tempmax-tempmin)/tempeven;
  if(NoEvenRate >=EventInsParaVar.Volt_NoEven_Up/10000.0)
  {
    Set_Event_Instant(ID_EVENT_VOLT_NO_EVEN);  //��ѹ��ƽ�ⷢ��
    if((INT16U)(NoEvenRate*100)>Not_Even_Data_PUCK.Volt_Not_Even)
    {
      DIS_PD_INT;  //�ص����ж�
      Not_Even_Data_PUCK.Volt_Not_Even=(INT16U)(NoEvenRate*10000);
      //if(Not_Even_Data_PUCK.Volt_Not_Even>100)
      //  Not_Even_Data_PUCK.Volt_Not_Even=100;
      SET_STRUCT_SUM(Not_Even_Data_PUCK);
      EN_PD_INT; //�������ж�
    }
  }
  
  if(NoEvenRate <EventInsParaVar.Volt_NoEven_Up/10000.0)
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NO_EVEN);  //��ѹ��ƽ�����
    DIS_PD_INT;  //�ص����ж�
    Not_Even_Data_PUCK.Volt_Not_Even=0;
    SET_STRUCT_SUM(Not_Even_Data_PUCK);
    EN_PD_INT; //�������ж�
  }  
}
#endif
/***********************************************************************
�������ܣ���ȡ������ƽ��״̬��
������������£�B ���ѹ/�����������㡣
***********************************************************************/
#ifdef ID_EVENT_CURR_NO_EVEN
void Check_Curr_NoEven(void)
{
  INT8U Flag;
  FP32S tempmax,tempmin,tempeven,NoEvenRate;
  INT32U B_Curr;
  

  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)
  {
    B_Curr=0;    
  }
  else
  {
    B_Curr=Measu_InstantData_ToPub_PUCK.Curr.B;    
  } 
  //--------------------------------------������ƽ��------------------------------------------
  tempmax=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(Flag==PARSE_331) //331�µ���С������ A��C֮��ѡ��
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.C);
  else
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(tempmax<=(Get_Start_Current()*UNIT_A*5))  //����������5��
  {
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //������ƽ�����
    if(Not_Even_Data_PUCK.Curr_Not_Even!=0)
    {
      DIS_PD_INT;  //�ص����ж�
      Not_Even_Data_PUCK.Curr_Not_Even=0;
      SET_STRUCT_SUM(Not_Even_Data_PUCK);
      EN_PD_INT; //�������ж�      
    }
    return ;
  }
  tempeven=((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A+B_Curr+Measu_InstantData_ToPub_PUCK.Curr.C)/3.0;
  
  NoEvenRate=(tempmax-tempmin)/tempeven;
  if(NoEvenRate>=EventInsParaVar.Curr_NoEven_Up/10000.0)
  {
    Set_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //������ƽ�ⷢ��
    if((INT16U)(NoEvenRate*100)>Not_Even_Data_PUCK.Curr_Not_Even)
    {
      DIS_PD_INT;  //�ص����ж�
      Not_Even_Data_PUCK.Curr_Not_Even=(INT16U)(NoEvenRate*10000);
      //if(Not_Even_Data_PUCK.Curr_Not_Even>100)
      //  Not_Even_Data_PUCK.Curr_Not_Even=100;
      SET_STRUCT_SUM(Not_Even_Data_PUCK);
      EN_PD_INT; //�������ж�
    }
  }
  
  if(NoEvenRate < EventInsParaVar.Curr_NoEven_Up/10000.0)
  {
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //������ƽ�����
    DIS_PD_INT;  //�ص����ж�
    Not_Even_Data_PUCK.Curr_Not_Even=0;
    SET_STRUCT_SUM(Not_Even_Data_PUCK);
    EN_PD_INT; //�������ж�
  }  
}
#endif

/***********************************************************************
�������ܣ���ȡʧ��˲ʱ״̬��
��ڣ���
���ڣ���
�����๩��ϵͳ�У������ѹ���ڵ��ܱ���ٽ��ѹ�������������һ�������С���������������������߸��ɵ�������5����������������Ĺ�����
***********************************************************************/
#ifdef ID_EVENT_A_LOSS_CURR
void Check_Loss_Curr(void)
{
  INT8U i,Flag;
  volatile INT32U *Volt,*Curr;
      
  for(i=0;i<3;i++)
  {    
    Volt=&Measu_InstantData_ToPub_PUCK.Volt.A+i;
    Curr=&Measu_InstantData_ToPub_PUCK.Curr.A+i;
    Flag=0;
    if(((FP32S)(*Volt)/UNIT_V)>=((FP32S)EventInsParaVar.LossCurr_U_Down/10.0))  // ʧ���¼���ѹ�������� 
    {
      if(((FP32S)(*Curr)/UNIT_A)<=((FP32S)EventInsParaVar.LossCurr_I_Up/10000.0))   //��ǰ��С�� ʧ���¼������������� 
      {        
          switch(i)             //������ɵ������� ʧ���¼�������������
          {
            case 0:
              if(((FP32S)(*(Curr+1))/UNIT_A)>=((FP32S)EventInsParaVar.LossCurr_I_Down/10000.0)||\
                 ((FP32S)(*(Curr+2))/UNIT_A)>=((FP32S)EventInsParaVar.LossCurr_I_Down/10000.0))
                  Flag=1;
              break;
              
            case 1:
              if((((FP32S)*(Curr-1))/UNIT_A)>=((FP32S)EventInsParaVar.LossCurr_I_Down/10000.0)||\
                 ((FP32S)(*(Curr+1))/UNIT_A)>=((FP32S)EventInsParaVar.LossCurr_I_Down/10000.0))
                  Flag=1;
              break;
              
            case 2:
              if(((FP32S)(*(Curr-1))/UNIT_A)>=((FP32S)EventInsParaVar.LossCurr_I_Down/10000.0)||\
                 ((FP32S)(*(Curr-2))/UNIT_A)>=((FP32S)EventInsParaVar.LossCurr_I_Down/10000.0))
                  Flag=1;
              break;            
          }
      }        
    }
    if(Flag)
        Set_Event_Instant(ID_EVENT_A_LOSS_CURR+i);    //ʧ��
      else
        Clr_Event_Instant(ID_EVENT_A_LOSS_CURR+i);    //ʧ���ָ�   
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR); 
}
#endif

/***********************************************************************
�������ܣ���ȡ����˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_OVER_CURR
void Check_Up_Curr(void)
{
  INT8U i;
  volatile INT32U *Curr;
  
  for(i=0;i<3;i++)
  {
    Curr=&Measu_InstantData_ToPub_PUCK.Curr.A+i;
    if(((FP32S)(*Curr)/UNIT_A)>=((FP32S)EventInsParaVar.UpCurr_I_Down/10.0))
      Set_Event_Instant(ID_EVENT_A_OVER_CURR+i);    //����
    else
      Clr_Event_Instant(ID_EVENT_A_OVER_CURR+i);    //�����ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_OVER_CURR);  
}
#endif

/***********************************************************************
�������ܣ���ȡ����˲ʱ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_CUT_CURR
void Check_Cut_Curr(void)
{
  INT8U i;
  volatile INT32U *Volt,*Curr;
  
  
  for(i=0;i<3;i++)
  {    
    Volt=&Measu_InstantData_ToPub_PUCK.Volt.A+i;
    Curr=&Measu_InstantData_ToPub_PUCK.Curr.A+i;
    if(((FP32S)(*Volt)/UNIT_V)>=((FP32S)EventInsParaVar.CutCurre_U_Down/10.0))
    {
      if(((FP32S)(*Curr)/UNIT_A)<=((FP32S)EventInsParaVar.CutCurr_I_Up/10000.0))  //����
        Set_Event_Instant(ID_EVENT_A_CUT_CURR+i);    //����
      else
        Clr_Event_Instant(ID_EVENT_A_CUT_CURR+i);    //�����ָ�
    }
    else
        Clr_Event_Instant(ID_EVENT_A_CUT_CURR+i);    //�����ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_CUT_CURR);    
   
}
#endif

/***********************************************************************
�������ܣ���ȡ���������¼�˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_NEG_CURR
void Check_Neg_Curr(void)
{
  
  INT8U i,Flag;
  volatile INT32U *Acpower;
  
  for(i=0;i<3;i++)
  {
    Flag=1;
    switch(i)
    {
      case 0:
        if(Measu_Status_Mode_ToPub_PUCK.A_APwrDir EQ 0)
          Flag=0;
        break;
      
      case 1:
        if(Measu_Status_Mode_ToPub_PUCK.B_APwrDir EQ 0)
          Flag=0;
        break;
     
      case 2:
        if(Measu_Status_Mode_ToPub_PUCK.C_APwrDir EQ 0)
          Flag=0;
        break;
    }
    
    Acpower=&Measu_InstantData_ToPub_PUCK.AcPower.A+i;
    if(((FP32S)(*Acpower)/UNIT_KW_KAR)<((FP32S)EventInsParaVar.NegCurr_Acpow_Down/10000.0))  //����������
      Flag=0;    
    
    if(Flag)
      Set_Event_Instant(ID_EVENT_A_NEG_CURR+i);   //���������¼�
    else
      Clr_Event_Instant(ID_EVENT_A_NEG_CURR+i);    //���������¼��ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_A_NEG_CURR);   
}
#endif

/***********************************************************************
�������ܣ���ȡ�����¼�˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_A_POWER_EXCEED
void Check_Power_Exceed(void)
{  
  INT8U i;
  volatile INT32U *Acpower;
  
  for(i=0;i<3;i++)
  {    
    Acpower=&Measu_InstantData_ToPub_PUCK.AcPower.A+i;
    if(((FP32S)(*Acpower)/UNIT_KW_KAR)>=((FP32S)EventInsParaVar.OverLoad_AcPow_Down/10000.0))
      Set_Event_Instant(ID_EVENT_A_POWER_EXCEED+i);   //�����¼�
    else
      Clr_Event_Instant(ID_EVENT_A_POWER_EXCEED+i);    //�����¼��ָ�
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_POWER_EXCEED);   
}
#endif


/***********************************************************************
�������ܣ���ȡ��������-�¼�˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_POS_ACT_DEMAND_EXCEED
void Check_Demand_Exceed(void)
{  
  INT8U i,j;
  
  //�����й���������
  if(Measu_InstantData_ToPub_PUCK.Quadrant.Sum EQ QUADRANT1 || Measu_InstantData_ToPub_PUCK.Quadrant.Sum EQ QUADRANT4)
  {
    if(CUR_POS_ACT_DEMAND>=EventInsParaVar.OverDe_Acpow_Down)
      Set_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);   //�����й���������
    else
      Clr_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);    //�����й��������޻ָ�
    
    Clr_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);    //�����й��������޻ָ�  
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);    //�����й��������޻ָ�
    
    //�����й���������
    if(CUR_NEG_ACT_DEMAND>=EventInsParaVar.OverDe_Acpow_Down)
      Set_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);   //�����й���������
    else
      Clr_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);    //�����й��������޻ָ�    
  }
 
   //��ǰ1�� 4���� �޹���������
  for(i=0;i<4;i++)
  {    
    if(i+1 EQ Measu_InstantData_ToPub_PUCK.Quadrant.Sum)  //��ǰ�����޹�����
    {
      if(Demand_Accu.Phase_Cur[0].Quad_Reactive[i]>=(EventInsParaVar.OverDe_Reacpow_Down))
        Set_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED+i);   //��ǰ1�� 4���� �޹���������
      else
        Clr_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED+i);    //��ǰ1�� 4���� �޹������ָ�      

      for(j=0;(j<4)&&(j!=i);j++)
        Clr_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED+j);    //��ǰ1�� 4���� �޹������ָ�      
    }
    
  }
}
#endif

/***********************************************************************
�������ܣ���ȡ�������ز�ƽ��˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_CUR_VERY_NOEVEN
void Check_Cur_Very_Noeven(void)
{
  INT8U Flag;
  FP32S tempmax,tempmin,tempeven,NoEvenRate;
  INT32U B_Curr;
  

  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)
  {
    B_Curr=0;    
  }
  else
  {
    B_Curr=Measu_InstantData_ToPub_PUCK.Curr.B;    
  } 
  //--------------------------------------������ƽ��------------------------------------------
  tempmax=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(Flag==PARSE_331) //331�µ���С������ A��C֮��ѡ��
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.C);
  else
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(tempmax<=(Get_Start_Current()*UNIT_A*5))  //����������5��
  {
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //������ƽ�����
    return ;
  }
  
  tempeven=((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A+B_Curr+Measu_InstantData_ToPub_PUCK.Curr.C)/3;
  
  NoEvenRate=(tempmax-tempmin)/tempeven;
  if(NoEvenRate >=EventInsParaVar.Curr_No1Even_I_Up/10000.0)
    Set_Event_Instant(ID_CUR_VERY_NOEVEN);  //�������ز�ƽ�ⷢ��
  else
    Clr_Event_Instant(ID_CUR_VERY_NOEVEN);  //�������ز�ƽ�����
  
}
#endif
/***********************************************************************
�������ܣ��ܹ�������������
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_ALL_FACTOR_LOW
void Check_Sum_Factor_Low(void)
{
   if((FP32S)Measu_InstantData_ToPub_PUCK.PFactor.Sum/UNIT_FACTOR<=((FP32S)EventInsParaVar.DownPf_I_Down/1000.0)) 
      Set_Event_Instant(ID_EVENT_ALL_FACTOR_LOW);    //�ܹ�������������
    else
      Clr_Event_Instant(ID_EVENT_ALL_FACTOR_LOW);    //�ܹ������������޻ָ�  
}
#endif
/***********************************************************************
�������ܣ���ȡʧѹ�仯״̬��
��ڣ���
���ڣ���
***********************************************************************/
#if ID_EVENT_LOSS_VOL>0
void Get_Loss_Volt_Change(void)
{
 Get_Change_Status(Meter_Run_Status.Volt_LossMiss.Byte,4,ID_EVENT_LOSS_VOL,&Loss_Volt_Change); 
}
#endif

/***********************************************************************
�������ܣ���ȡʧ���仯״̬��
��ڣ���
���ڣ���
***********************************************************************/
#if  ID_EVENT_LOSS_CUR>0
void Get_Loss_Curr_Change(void)
{
  Get_Change_Status(Meter_Run_Status.Meter_Stat3.Byte,4,ID_EVENT_LOSS_CUR,&Loss_Curr_Change); 
}
#endif
/***********************************************************************
�������ܣ���ȡ��������仯״̬��
��ڣ���
���ڣ���
***********************************************************************/
#if ID_EVENT_NEG_CUR>0
void Get_Curr_Neg_Change(void)
{ 
  Get_Change_Status(Meter_Run_Status.Meter_Stat2.Byte,0,ID_EVENT_NEG_CUR,&Curr_Neg_Change);  
}
#endif

/***********************************************************************
�������ܣ���ȡ��ѹ����������˲̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_VOLT_NEG_SEQ
void Check_Volt_Curr_Seq(void)
{

  if(Check_Power_Grid_Event(1))
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ������ȷ���¼�����
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //����������ȷ���¼�����
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.V_SeqErr)
    Set_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ�����
  else
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ������ȷ
 
  if(Measu_Status_Mode_ToPub_PUCK.I_SeqErr)
    Set_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //���������
  else
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //����������ȷ
  
    
  //��ѹ�����򣬻����ж���С��ѹ  
  if((FP32S)Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C)<=UNIT_V*Get_Un()*0.6)  //��С��ѹ��>=10��Un
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ�������
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //���������
  }
  
  /*
  //���������򣬻����ж���С����  
  if((FP32S)Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B,Measu_InstantData_ToPub_PUCK.Curr.C)<=UNIT_A*Get_Un()*0.004)
  {
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //���������
  }
  */
    
  //331��ABCʧѹʱ������������
  if(Get_SysParse_Mode()==PARSE_331)  //331����������
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //��ѹ�������
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //���������
  }  
}
#endif

/***********************************************************************
�������ܣ��ж��Ƿ��ǹ���ģʽ
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_FAC_ON
void Check_Fac_Status(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL)
  {
    Clr_Event_Instant(ID_EVENT_FAC_ON);
    return ;
  }
  if(Get_Meter_Hard_Mode()==MODE_FAC)
    Set_Event_Instant(ID_EVENT_FAC_ON);
  else
    Clr_Event_Instant(ID_EVENT_FAC_ON);  
}
#endif

/***********************************************************************
�������ܣ��жϱ�̿����Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_PRGKEY_ON
void Check_Prg_Key(void)
{
  static INT8U Min_Timer=0;
  
  if(Get_Sys_Status()!=SYS_NORMAL)   //VCC
  {
    Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
    return ;
  }
  
    
  if(Key_Value_Pub.Key.Bit.PrgKey)  //�����
  {
     Set_Event_Instant(ID_EVENT_PRGKEY_ON);
#if NET_METER == CARRIER_METER   //�ز���,���ݱ�̣����ز�set�õͣ�ʵ�ְ�ť����
     EN_CARRIER_SET_ADDR;
#endif
     
     if(Prg_Key_Status.PrgKeyTime>=PRG_KEY_TIME)//PRG_KEY_TIME)  //PRG_KEY_TIME����
     {
       Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
       Key_Value_Pub.Key.Bit.PrgKey=0;          //������״̬��
       DIS_PD_INT;  //�ص����ж�
       Prg_Key_Status.PrgKeyTime=0;
       SET_STRUCT_SUM(Prg_Key_Status);
       EN_PD_INT; //�������ж�
       Min_Timer=0;
     }
     else
     {
       if(Prg_Key_Status.PrgKeyTime EQ 0) //�տ�ʼ�ͽ�����״̬
       {
         DIS_PD_INT;  //�ص����ж�
         Prg_Key_Status.PrgKeyTime=1;
         SET_STRUCT_SUM(Prg_Key_Status);
         EN_PD_INT; //�������ж�
       }
       
       Min_Timer++;
       if(Min_Timer>=60)  //����ÿ�붼�ص����жϣ�̫Ƶ����
       {
         Min_Timer-=60;
         DIS_PD_INT;  //�ص����ж�
         Prg_Key_Status.PrgKeyTime++;
         SET_STRUCT_SUM(Prg_Key_Status);
         EN_PD_INT; //�������ж�
       }
     }
  }
  else
  {
#if NET_METER == CARRIER_METER   //�ز���,���ݱ�̣����ز�set�øߣ�ʵ�ְ�ť����
      DIS_CARRIER_SET_ADDR;
#endif
      Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
      Min_Timer=0;
  }
}
#endif

/***********************************************************************
�������ܣ��ж��ֶ���������ť�Ƿ��
��ڣ���
���ڣ���
�¼������оݣ����� PRESS_KEY_SEC �����Ϻ��ɿ���Ϊһ����������ť�¼�������
***********************************************************************/
#define PRESS_KEY_SEC 3
void Check_ClrDemand_Key(void)
{
  static INT8U ClrNum=0;

 
 if(Get_Sys_Status()!=SYS_NORMAL)    //VCC
 {
    Clr_Event_Instant(ID_CLR_DEMAND_KEY);
    return ;
 }


 if(Read_Event_Status(ID_EVENT_PRGKEY_ON) &&(Inter_Up_Key_STATUS EQ 0)&&(Inter_Down_Key_STATUS EQ 0))  //����£������·���ť 3�룬�ֶ�������
 {
   ClrNum++;
   if(ClrNum>=PRESS_KEY_SEC)  //��ť����
     ClrNum=PRESS_KEY_SEC;
 }
 else                     //��ť�ɿ�
 {
   if(ClrNum<PRESS_KEY_SEC)  //��ť�ɿ�,���ϴΰ��˲��� PRESS_KEY_SEC��
    ClrNum=0;
   else
    ClrNum=PRESS_KEY_SEC+1;
 }
 
 if(ClrNum>PRESS_KEY_SEC)
 {
   Set_Event_Instant(ID_CLR_DEMAND_KEY);
   ClrNum=0;   
 //��������ť�¼���������Ϊ�������¼�����
 //Set_Event_Instant(ID_EVENT_CLR_DEMAND_MAN);   //���¼��������������Ϊ��DoubleFlag=0
   Clr_Demand_Key.Status=CLR_DEMD_KEY_PRESS;
   SET_STRUCT_SUM(Clr_Demand_Key);
 }
 else
 {   
   Clr_Event_Instant(ID_CLR_DEMAND_KEY);
   //Clr_Event_Instant(ID_EVENT_CLR_DEMAND_MAN);
 }
}
/***********************************************************************
�������ܣ��ж��ֶ���������ť�Ƿ�
��ڣ���
���ڣ�1---------------�ֶ���������ť���£����������¼�����

***********************************************************************/
INT8U Check_Demand_Key_Press(void)
{  
  if(Clr_Demand_Key.Status  EQ CLR_DEMD_KEY_PRESS)
  { 
    if(CHECK_STRUCT_SUM(Clr_Demand_Key) EQ 0)  //���ݶԣ�У��Ͳ���
    {
      Clr_Demand_Key.Status=0;
      SET_STRUCT_SUM(Clr_Demand_Key);
      return 0;  
    }
    //���ݶԣ�У���Ҳ��
    Clr_Demand_Key.Status=0;
    SET_STRUCT_SUM(Clr_Demand_Key);
    return 1;    
  }
  return 0;  
}
/***********************************************************************
�������ܣ��ж����ñ��ַ�����Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_METER_ADDR_EN
void Check_MeterAddr_Key(void)
{
  if(Inter_Down_Key_STATUS)                  //���ñ��ַ��ť
    Clr_Event_Instant(ID_METER_ADDR_EN);
  else
    Set_Event_Instant(ID_METER_ADDR_EN);  
}
#endif
/***********************************************************************
�������ܣ��ж��ϸ��Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_UP_COVER_OPEN
void Check_UpCover(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL || UP_COVER_STATUS)    //VCC
  {
    Clr_Event_Instant(ID_EVENT_UP_COVER_OPEN);
    return ;
  }
  
  if(UP_COVER_STATUS EQ 0)   //UP_COVER_STATUS,1-----����ȥ,��ʾ����Ǹ���;0-----��ʾ�������
  {
    Set_Event_Instant(ID_EVENT_UP_COVER_OPEN);
  }
}
#endif
/***********************************************************************
�������ܣ��жϺ��(Ǧ��)�Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_UP_COVER_OPEN
void Check_DownCover(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL || DOWN_COVER_STATUS ==0)    //VCC
 {   
    Clr_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
    
    return ;
 }
 
  if(DOWN_COVER_STATUS)  //����������ǰ���ȥ��,�˸��ǰ�װ�ں���ϵ�
  {
    Set_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
  }
}
#endif
/***********************************************************************
�������ܣ��ж�Ǧ���Ƿ��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_LEAD_COVER_OPEN
void Check_LeadCover(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL || LEAD_COVER_STATUS ==0)    //VCC
 {
    Clr_Event_Instant(ID_EVENT_LEAD_COVER_OPEN);    
    return ;
 }
 
  if(LEAD_COVER_STATUS)  //����������ǰ���ȥ��,�˸��ǰ�װ�ں���ϵ�
  {
    Set_Event_Instant(ID_EVENT_LEAD_COVER_OPEN); 
  }
}
#endif
/***********************************************************************
�������ܣ���ȡʱ�ӵ��Ƿѹ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_RTC_BAT_LOW
void Check_RTCBat_Low(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL || RTC_BAT_LOW)
  {
    Clr_Event_Instant(ID_EVENT_RTC_BAT_LOW);
    return ;
  }
  if(RTC_BAT_LOW==0)
    Set_Event_Instant(ID_EVENT_RTC_BAT_LOW);  
}
#endif
/***********************************************************************
�������ܣ���ȡ�͹��ĵ��Ƿѹ״̬��
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_LOWPWR_BAT_LOW
void Check_LPWBat_Low(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL|| LOWCOST_BAT_LOW)
  {
    Clr_Event_Instant(ID_EVENT_LOWPWR_BAT_LOW);
    return ;
  }
  
  if(LOWCOST_BAT_LOW==0)
    Set_Event_Instant(ID_EVENT_LOWPWR_BAT_LOW);  
}
#endif
/***********************************************************************
�������ܣ���ȡAB�л�ģʽ��ť
��ڣ���
���ڣ���
***********************************************************************/
#ifdef ID_EVENT_AB_FUNC_KEY
void Check_AB_Func_Key(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL)    //VCC
 {
    Clr_Event_Instant(ID_EVENT_AB_FUNC_KEY);
    return ;
 }
 
  if((Inter_Up_Key_STATUS==1)&&(Inter_Down_Key_STATUS==1))  //û�а�ť����
    Clr_Event_Instant(ID_EVENT_AB_FUNC_KEY);
  else                         //��һ����ť����
    Set_Event_Instant(ID_EVENT_AB_FUNC_KEY);  
}
#endif
/********************************************************************************
����ԭ�ͣ�
���ܣ����ϵͳʱ�ӹ���

*********************************************************************************/
#ifdef ID_EVENT_OSC_ERR
void Monitor_Meter_System_Osc(void)
{
  if(SYS_NORMAL==Sys_Status.Status)
  {
    if(CSC!=0x01 ||CKC!=0x38)
    {
      Beep_Only_Alarm_PUCK();
      Debug_Print("MCU Osc System Error:MSTOP=%d,HIOSTOP=%d,XTSTOP=%d",MSTOP,HIOSTOP,XTSTOP);  
      Set_Event_Instant(ID_EVENT_OSC_ERR); 
      return ;
    }
    Clr_Event_Instant(ID_EVENT_OSC_ERR);
    return ;
  }
  
  if(CSC!=0x01 ||CKC!=(0x38|RSUME_CLOCK_DIV))
  {
    Beep_Only_Alarm_PUCK();
    Debug_Print("MCU Osc System Error:MSTOP=%d,HIOSTOP=%d,XTSTOP=%d",MSTOP,HIOSTOP,XTSTOP);  
    Set_Event_Instant(ID_EVENT_OSC_ERR); 
    return ;
  }
  Clr_Event_Instant(ID_EVENT_OSC_ERR);
}
#endif
/********************************************************************************
����ԭ�ͣ�
���ܣ���բ��բ�¼�ִ��,��LEDָʾ��ǰ��״̬
SwitchFlag--------0��բ����0����բ
*********************************************************************************/
void Excute_Toogle(INT8U SwitchFlag)
{
  //if(PREPAID_EN EQ 0)  //��Ԥ���ѹ��ܣ���բ����բ LED ָʾ����բ LCDָʾ ����������
  //  return ;
  
  if(SwitchFlag)
  {
      Port_Out_Pub(EXT_ID_TOGGLE,PORT_END);      //��բ
      
      //��̵��������巽ʽ
      Port_Out_Pub(INTER_ID_RELAY_ON,LARGE_RELAY_PULSE_WD);
      return ;

  }
  else
  {
    //��̵��������巽ʽ
    Port_Out_Pub(INTER_ID_RELAY_OFF,LARGE_RELAY_PULSE_WD);
    
    if(Get_Toogle_Out() EQ PULSE_MODE)
    {
      Port_Out_Pub(EXT_ID_TOGGLE,APP_TOOGLE_PORT_PULSE_WD);           //������բ
    }
    else      
      Port_Out_Pub(EXT_ID_TOGGLE,PORT_START);           //��ƽ��բ    
    
  }
}
/********************************************************************************
����ԭ�ͣ�
���ܣ��ϵ���ʼ����բ��բ״̬��
      ��բ��բ�¼�ִ��,��LEDָʾ��ǰ��״̬
*********************************************************************************/
void Init_Toggle_Status(void)
{
  //Remote_Ctrl_Status.Switch_Status = SWITCH_ON;
  //INIT_STRUCT_VAR(Remote_Ctrl_Status);
}
