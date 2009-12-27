#define EVENTINSTANT_C
#include "Pub_PUCK.h"
/*
typedef struct
{
  INT32U Qual_Up_Vol[3];//越合格上限电压值,0-2分别表示A-B-C相
  INT32U Qual_Low_Vol[3];//越合格下限电压值
  
  INT32U Over_Vol[3];//电压超上限电压值
}S_Event_Vol_Cur;
黄智颖 17:25:37
EXT S_Event_Vol_Cur Event_Vol_Cur;
黄智颖 17:26:00
Over_Vol[3] 是你的
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
函数功能：初始化获取某个事件参数
入口：无
出口：无
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
函数功能：初始化获取瞬态字的全部参数
入口：无
出口：无
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
函数功能：电判断所有电压是否小于入口参数
入口：IsVoltNeg----------------------是不是逆相序调用
出口：0-----------不小于入口参数；1-------------均小于入口参数
***********************************************************************/
INT8U Check_Max_Volt_Below(FP32S BelowValue)
{
  FP32S temp;
  
  temp=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C);
  temp/=UNIT_V;
  if(temp<BelowValue)        //所有电压都低于零界电压, 所有电压都低于AUXIL_POWER_RATIO*Un时，被认为是辅助电源
     return 1;  
  
  return 0;
}
/***********************************************************************
函数功能：电网事件发生前提检查
入口：IsVoltNeg----------------------是不是逆相序调用
出口：0-----------所有事件需要近一步检查；1-------------所有事件可视为结束
三相电压均低于70%Un；
或者
***********************************************************************/
INT8U Check_Power_Grid_Event(INT8U IsVoltNeg)
{
  FP32S temp;
  
  if(Get_Sys_Status()!=SYS_NORMAL)
    return 1;
  
  if(IsVoltNeg EQ 0 && SEQ_ERR_CHK_GRID && Read_Event_Status(ID_EVENT_VOLT_NEG_SEQ))  //不是逆相序事件判定:逆相序了，所有事件都结束
    return 1;
  
  if(Check_Max_Volt_Below(Get_Un()*EventInsParaVar.Start_Volt/100.0)) //所有电压都低于零界电压, 所有电压都低于AUXIL_POWER_RATIO*Un时，被认为是辅助电源
     return 1;
  
  temp=Measu_InstantData_ToPub_PUCK.Volt.A+Measu_InstantData_ToPub_PUCK.Volt.B+Measu_InstantData_ToPub_PUCK.Volt.C;
  temp/=UNIT_V;
  if(temp<Get_Un()*EventInsParaVar.Start_Volt/100.0)   //(所有电压之和)<零界电压   
    return 1;
  
  return 0;
}

/***********************************************************************
函数功能：获取失压瞬时状态字
入口：无
出口：无
在三相（或单相）供电系统中，某相负荷电流大于启动电流，但电压线路的电压低于电能表参比电压的78％时，且持续时间大于60秒，此种工况称为失压
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
      if(((FP32S)(*Volt)/UNIT_V)<=((FP32S)EventInsParaVar.LossVolt_U_Up/10.0))  //上限
        Set_Event_Instant(ID_EVENT_A_LOSS_VOLT+i);    //失压
      
      if(((FP32S)(*Volt)/UNIT_V)>=((FP32S)EventInsParaVar.LossVolt_U_Down/10.0))  //下限
        Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT+i);    //失压恢复
    }
    else
       Clr_Event_Instant(ID_EVENT_A_LOSS_VOLT+i);    //失压恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_LOSS_VOLT); 
}
#endif

/***********************************************************************
函数功能：获取欠压瞬时状态字
入口：无
出口：无
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
      Set_Event_Instant(ID_EVENT_A_VOLT_LESS+i);    //欠压
    else
      Clr_Event_Instant(ID_EVENT_A_VOLT_LESS+i);    //欠压恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_VOLT_LESS);  
}
#endif
/***********************************************************************
函数功能：获取过压瞬时状态字
入口：无
出口：无
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
      Set_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD+i);    //过压
    else
      Clr_Event_Instant(ID_EVENT_A_VOLT_OVERLOAD+i);    //过压恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_VOLT_OVERLOAD);  
}
#endif

/***********************************************************************
函数功能：获取断相瞬时状态字
入口：无
出口：无
判据：电压小于零界电压，电流小于启动电流  
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
      if(((FP32S)(*Curr)/UNIT_A)<=((FP32S)EventInsParaVar.CutParse_I_Up/10000.0))  //上限
        Set_Event_Instant(ID_EVENT_A_LOSS_PARSE+i);    //断相
      else
        Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE+i);    //断相恢复
    }
    else
        Clr_Event_Instant(ID_EVENT_A_LOSS_PARSE+i);    //断相恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_LOSS_PARSE);  
}
#endif
/***********************************************************************
函数功能：获取电压不平衡状态字
三相三线情况下，B 相电压/流不加入运算。
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
  
  //--------------------------------------电压不平衡------------------------------------------
  tempmax=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,B_volt,Measu_InstantData_ToPub_PUCK.Volt.C);
  
  if(Flag==PARSE_331) //331下的最小电压在 A和C之间选择
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.C);
  else
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,B_volt,Measu_InstantData_ToPub_PUCK.Volt.C);
    
  tempeven=((FP32S)Measu_InstantData_ToPub_PUCK.Volt.A+B_volt+Measu_InstantData_ToPub_PUCK.Volt.C)/3.0;
  

  NoEvenRate=(tempmax-tempmin)/tempeven;
  if(NoEvenRate >=EventInsParaVar.Volt_NoEven_Up/10000.0)
  {
    Set_Event_Instant(ID_EVENT_VOLT_NO_EVEN);  //电压不平衡发生
    if((INT16U)(NoEvenRate*100)>Not_Even_Data_PUCK.Volt_Not_Even)
    {
      DIS_PD_INT;  //关掉电中断
      Not_Even_Data_PUCK.Volt_Not_Even=(INT16U)(NoEvenRate*10000);
      //if(Not_Even_Data_PUCK.Volt_Not_Even>100)
      //  Not_Even_Data_PUCK.Volt_Not_Even=100;
      SET_STRUCT_SUM(Not_Even_Data_PUCK);
      EN_PD_INT; //开掉电中断
    }
  }
  
  if(NoEvenRate <EventInsParaVar.Volt_NoEven_Up/10000.0)
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NO_EVEN);  //电压不平衡结束
    DIS_PD_INT;  //关掉电中断
    Not_Even_Data_PUCK.Volt_Not_Even=0;
    SET_STRUCT_SUM(Not_Even_Data_PUCK);
    EN_PD_INT; //开掉电中断
  }  
}
#endif
/***********************************************************************
函数功能：获取电流不平衡状态字
三相三线情况下，B 相电压/流不加入运算。
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
  //--------------------------------------电流不平衡------------------------------------------
  tempmax=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(Flag==PARSE_331) //331下的最小电流在 A和C之间选择
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.C);
  else
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(tempmax<=(Get_Start_Current()*UNIT_A*5))  //启动电流的5倍
  {
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //电流不平衡结束
    if(Not_Even_Data_PUCK.Curr_Not_Even!=0)
    {
      DIS_PD_INT;  //关掉电中断
      Not_Even_Data_PUCK.Curr_Not_Even=0;
      SET_STRUCT_SUM(Not_Even_Data_PUCK);
      EN_PD_INT; //开掉电中断      
    }
    return ;
  }
  tempeven=((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A+B_Curr+Measu_InstantData_ToPub_PUCK.Curr.C)/3.0;
  
  NoEvenRate=(tempmax-tempmin)/tempeven;
  if(NoEvenRate>=EventInsParaVar.Curr_NoEven_Up/10000.0)
  {
    Set_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //电流不平衡发生
    if((INT16U)(NoEvenRate*100)>Not_Even_Data_PUCK.Curr_Not_Even)
    {
      DIS_PD_INT;  //关掉电中断
      Not_Even_Data_PUCK.Curr_Not_Even=(INT16U)(NoEvenRate*10000);
      //if(Not_Even_Data_PUCK.Curr_Not_Even>100)
      //  Not_Even_Data_PUCK.Curr_Not_Even=100;
      SET_STRUCT_SUM(Not_Even_Data_PUCK);
      EN_PD_INT; //开掉电中断
    }
  }
  
  if(NoEvenRate < EventInsParaVar.Curr_NoEven_Up/10000.0)
  {
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //电流不平衡结束
    DIS_PD_INT;  //关掉电中断
    Not_Even_Data_PUCK.Curr_Not_Even=0;
    SET_STRUCT_SUM(Not_Even_Data_PUCK);
    EN_PD_INT; //开掉电中断
  }  
}
#endif

/***********************************************************************
函数功能：获取失流瞬时状态字
入口：无
出口：无
在三相供电系统中，三相电压大于电能表的临界电压，三相电流中任一相或两相小于启动电流，且其他相线负荷电流大于5％额定（基本）电流的工况。
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
    if(((FP32S)(*Volt)/UNIT_V)>=((FP32S)EventInsParaVar.LossCurr_U_Down/10.0))  // 失流事件电压触发下限 
    {
      if(((FP32S)(*Curr)/UNIT_A)<=((FP32S)EventInsParaVar.LossCurr_I_Up/10000.0))   //当前项小于 失流事件电流触发上限 
      {        
          switch(i)             //其他项负荷电流大于 失流事件电流触发下限
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
        Set_Event_Instant(ID_EVENT_A_LOSS_CURR+i);    //失流
      else
        Clr_Event_Instant(ID_EVENT_A_LOSS_CURR+i);    //失流恢复   
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_LOSS_CURR); 
}
#endif

/***********************************************************************
函数功能：获取过流瞬时状态字
入口：无
出口：无
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
      Set_Event_Instant(ID_EVENT_A_OVER_CURR+i);    //过流
    else
      Clr_Event_Instant(ID_EVENT_A_OVER_CURR+i);    //过流恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_OVER_CURR);  
}
#endif

/***********************************************************************
函数功能：获取断流瞬时状态字
入口：无
出口：无
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
      if(((FP32S)(*Curr)/UNIT_A)<=((FP32S)EventInsParaVar.CutCurr_I_Up/10000.0))  //上限
        Set_Event_Instant(ID_EVENT_A_CUT_CURR+i);    //断流
      else
        Clr_Event_Instant(ID_EVENT_A_CUT_CURR+i);    //断流恢复
    }
    else
        Clr_Event_Instant(ID_EVENT_A_CUT_CURR+i);    //断流恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_CUT_CURR);    
   
}
#endif

/***********************************************************************
函数功能：获取潮流反向事件瞬态字
入口：无
出口：无
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
    if(((FP32S)(*Acpower)/UNIT_KW_KAR)<((FP32S)EventInsParaVar.NegCurr_Acpow_Down/10000.0))  //不满足条件
      Flag=0;    
    
    if(Flag)
      Set_Event_Instant(ID_EVENT_A_NEG_CURR+i);   //潮流反向事件
    else
      Clr_Event_Instant(ID_EVENT_A_NEG_CURR+i);    //潮流反向事件恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_A_NEG_CURR);   
}
#endif

/***********************************************************************
函数功能：获取过载事件瞬态字
入口：无
出口：无
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
      Set_Event_Instant(ID_EVENT_A_POWER_EXCEED+i);   //过载事件
    else
      Clr_Event_Instant(ID_EVENT_A_POWER_EXCEED+i);    //过载事件恢复
  }

  if(Get_SysParse_Mode()==PARSE_331)
    Clr_Event_Instant(ID_EVENT_B_POWER_EXCEED);   
}
#endif


/***********************************************************************
函数功能：获取需量超限-事件瞬态字
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_POS_ACT_DEMAND_EXCEED
void Check_Demand_Exceed(void)
{  
  INT8U i,j;
  
  //正向有功需量超限
  if(Measu_InstantData_ToPub_PUCK.Quadrant.Sum EQ QUADRANT1 || Measu_InstantData_ToPub_PUCK.Quadrant.Sum EQ QUADRANT4)
  {
    if(CUR_POS_ACT_DEMAND>=EventInsParaVar.OverDe_Acpow_Down)
      Set_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);   //正向有功需量超限
    else
      Clr_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);    //正向有功需量超限恢复
    
    Clr_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);    //反向有功需量超限恢复  
  }
  else
  {
    Clr_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);    //正向有功需量超限恢复
    
    //反向有功需量超限
    if(CUR_NEG_ACT_DEMAND>=EventInsParaVar.OverDe_Acpow_Down)
      Set_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);   //反向有功需量超限
    else
      Clr_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);    //反向有功需量超限恢复    
  }
 
   //当前1～ 4象限 无功需量超限
  for(i=0;i<4;i++)
  {    
    if(i+1 EQ Measu_InstantData_ToPub_PUCK.Quadrant.Sum)  //当前象限无功需量
    {
      if(Demand_Accu.Phase_Cur[0].Quad_Reactive[i]>=(EventInsParaVar.OverDe_Reacpow_Down))
        Set_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED+i);   //当前1～ 4象限 无功需量超限
      else
        Clr_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED+i);    //当前1～ 4象限 无功需量恢复      

      for(j=0;(j<4)&&(j!=i);j++)
        Clr_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED+j);    //当前1～ 4象限 无功需量恢复      
    }
    
  }
}
#endif

/***********************************************************************
函数功能：获取电流严重不平衡瞬态字
入口：无
出口：无
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
  //--------------------------------------电流不平衡------------------------------------------
  tempmax=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(Flag==PARSE_331) //331下的最小电流在 A和C之间选择
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.C);
  else
    tempmin=Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,B_Curr,Measu_InstantData_ToPub_PUCK.Curr.C);
  
  if(tempmax<=(Get_Start_Current()*UNIT_A*5))  //启动电流的5倍
  {
    Clr_Event_Instant(ID_EVENT_CURR_NO_EVEN);  //电流不平衡结束
    return ;
  }
  
  tempeven=((FP32S)Measu_InstantData_ToPub_PUCK.Curr.A+B_Curr+Measu_InstantData_ToPub_PUCK.Curr.C)/3;
  
  NoEvenRate=(tempmax-tempmin)/tempeven;
  if(NoEvenRate >=EventInsParaVar.Curr_No1Even_I_Up/10000.0)
    Set_Event_Instant(ID_CUR_VERY_NOEVEN);  //电流严重不平衡发生
  else
    Clr_Event_Instant(ID_CUR_VERY_NOEVEN);  //电流严重不平衡结束
  
}
#endif
/***********************************************************************
函数功能：总功率因数超下限
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_ALL_FACTOR_LOW
void Check_Sum_Factor_Low(void)
{
   if((FP32S)Measu_InstantData_ToPub_PUCK.PFactor.Sum/UNIT_FACTOR<=((FP32S)EventInsParaVar.DownPf_I_Down/1000.0)) 
      Set_Event_Instant(ID_EVENT_ALL_FACTOR_LOW);    //总功率因数超下限
    else
      Clr_Event_Instant(ID_EVENT_ALL_FACTOR_LOW);    //总功率因数超下限恢复  
}
#endif
/***********************************************************************
函数功能：获取失压变化状态字
入口：无
出口：无
***********************************************************************/
#if ID_EVENT_LOSS_VOL>0
void Get_Loss_Volt_Change(void)
{
 Get_Change_Status(Meter_Run_Status.Volt_LossMiss.Byte,4,ID_EVENT_LOSS_VOL,&Loss_Volt_Change); 
}
#endif

/***********************************************************************
函数功能：获取失流变化状态字
入口：无
出口：无
***********************************************************************/
#if  ID_EVENT_LOSS_CUR>0
void Get_Loss_Curr_Change(void)
{
  Get_Change_Status(Meter_Run_Status.Meter_Stat3.Byte,4,ID_EVENT_LOSS_CUR,&Loss_Curr_Change); 
}
#endif
/***********************************************************************
函数功能：获取电流反向变化状态字
入口：无
出口：无
***********************************************************************/
#if ID_EVENT_NEG_CUR>0
void Get_Curr_Neg_Change(void)
{ 
  Get_Change_Status(Meter_Run_Status.Meter_Stat2.Byte,0,ID_EVENT_NEG_CUR,&Curr_Neg_Change);  
}
#endif

/***********************************************************************
函数功能：获取电压电流逆相序瞬态字
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_VOLT_NEG_SEQ
void Check_Volt_Curr_Seq(void)
{

  if(Check_Power_Grid_Event(1))
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //电压相序正确，事件结束
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //电流相序正确，事件结束
    return ;
  }
  
  if(Measu_Status_Mode_ToPub_PUCK.V_SeqErr)
    Set_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //电压相序错
  else
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //电压相序正确
 
  if(Measu_Status_Mode_ToPub_PUCK.I_SeqErr)
    Set_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //电流相序错
  else
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //电流相序正确
  
    
  //电压逆相序，还需判定最小电压  
  if((FP32S)Get_Min_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C)<=UNIT_V*Get_Un()*0.6)  //最小电压需>=10％Un
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //电压相序清除
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //电流相序错
  }
  
  /*
  //电流逆相序，还需判定最小电流  
  if((FP32S)Get_Min_Num(Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B,Measu_InstantData_ToPub_PUCK.Curr.C)<=UNIT_A*Get_Un()*0.004)
  {
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //电流相序错
  }
  */
    
  //331表ABC失压时，不判逆相序
  if(Get_SysParse_Mode()==PARSE_331)  //331不判逆相序
  {
    Clr_Event_Instant(ID_EVENT_VOLT_NEG_SEQ); //电压相序清除
    Clr_Event_Instant(ID_EVENT_CUR_NEG_SEQ);  //电流相序错
  }  
}
#endif

/***********************************************************************
函数功能：判断是否是工厂模式
入口：无
出口：无
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
函数功能：判断编程开关是否打开
入口：无
出口：无
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
  
    
  if(Key_Value_Pub.Key.Bit.PrgKey)  //编程了
  {
     Set_Event_Instant(ID_EVENT_PRGKEY_ON);
#if NET_METER == CARRIER_METER   //载波表,根据编程，将载波set置低，实现按钮复用
     EN_CARRIER_SET_ADDR;
#endif
     
     if(Prg_Key_Status.PrgKeyTime>=PRG_KEY_TIME)//PRG_KEY_TIME)  //PRG_KEY_TIME分钟
     {
       Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
       Key_Value_Pub.Key.Bit.PrgKey=0;          //清除编程状态字
       DIS_PD_INT;  //关掉电中断
       Prg_Key_Status.PrgKeyTime=0;
       SET_STRUCT_SUM(Prg_Key_Status);
       EN_PD_INT; //开掉电中断
       Min_Timer=0;
     }
     else
     {
       if(Prg_Key_Status.PrgKeyTime EQ 0) //刚开始就进入编程状态
       {
         DIS_PD_INT;  //关掉电中断
         Prg_Key_Status.PrgKeyTime=1;
         SET_STRUCT_SUM(Prg_Key_Status);
         EN_PD_INT; //开掉电中断
       }
       
       Min_Timer++;
       if(Min_Timer>=60)  //不能每秒都关掉电中断，太频繁！
       {
         Min_Timer-=60;
         DIS_PD_INT;  //关掉电中断
         Prg_Key_Status.PrgKeyTime++;
         SET_STRUCT_SUM(Prg_Key_Status);
         EN_PD_INT; //开掉电中断
       }
     }
  }
  else
  {
#if NET_METER == CARRIER_METER   //载波表,根据编程，将载波set置高，实现按钮复用
      DIS_CARRIER_SET_ADDR;
#endif
      Clr_Event_Instant(ID_EVENT_PRGKEY_ON);
      Min_Timer=0;
  }
}
#endif

/***********************************************************************
函数功能：判断手动清需量按钮是否打开
入口：无
出口：无
事件发生判据：按下 PRESS_KEY_SEC 秒以上后松开，为一次清需量按钮事件发生。
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


 if(Read_Event_Status(ID_EVENT_PRGKEY_ON) &&(Inter_Up_Key_STATUS EQ 0)&&(Inter_Down_Key_STATUS EQ 0))  //编程下，按上下翻按钮 3秒，手动清需量
 {
   ClrNum++;
   if(ClrNum>=PRESS_KEY_SEC)  //按钮长按
     ClrNum=PRESS_KEY_SEC;
 }
 else                     //按钮松开
 {
   if(ClrNum<PRESS_KEY_SEC)  //按钮松开,且上次按了不到 PRESS_KEY_SEC秒
    ClrNum=0;
   else
    ClrNum=PRESS_KEY_SEC+1;
 }
 
 if(ClrNum>PRESS_KEY_SEC)
 {
   Set_Event_Instant(ID_CLR_DEMAND_KEY);
   ClrNum=0;   
 //清需量按钮事件发生，认为清需量事件发生
 //Set_Event_Instant(ID_EVENT_CLR_DEMAND_MAN);   //在事件流程中清除，因为：DoubleFlag=0
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
函数功能：判断手动清需量按钮是否
入口：无
出口：1---------------手动清需量按钮按下，待清需量事件处理。

***********************************************************************/
INT8U Check_Demand_Key_Press(void)
{  
  if(Clr_Demand_Key.Status  EQ CLR_DEMD_KEY_PRESS)
  { 
    if(CHECK_STRUCT_SUM(Clr_Demand_Key) EQ 0)  //数据对，校验和不对
    {
      Clr_Demand_Key.Status=0;
      SET_STRUCT_SUM(Clr_Demand_Key);
      return 0;  
    }
    //数据对，校验和也对
    Clr_Demand_Key.Status=0;
    SET_STRUCT_SUM(Clr_Demand_Key);
    return 1;    
  }
  return 0;  
}
/***********************************************************************
函数功能：判断设置表地址开关是否打开
入口：无
出口：无
***********************************************************************/
#ifdef ID_METER_ADDR_EN
void Check_MeterAddr_Key(void)
{
  if(Inter_Down_Key_STATUS)                  //设置表地址按钮
    Clr_Event_Instant(ID_METER_ADDR_EN);
  else
    Set_Event_Instant(ID_METER_ADDR_EN);  
}
#endif
/***********************************************************************
函数功能：判断上盖是否打开
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_UP_COVER_OPEN
void Check_UpCover(void)
{
  if(Get_Sys_Status()!=SYS_NORMAL || UP_COVER_STATUS)    //VCC
  {
    Clr_Event_Instant(ID_EVENT_UP_COVER_OPEN);
    return ;
  }
  
  if(UP_COVER_STATUS EQ 0)   //UP_COVER_STATUS,1-----按下去,表示表盖是盖上;0-----表示表盖拿下
  {
    Set_Event_Instant(ID_EVENT_UP_COVER_OPEN);
  }
}
#endif
/***********************************************************************
函数功能：判断后盖(铅封)是否打开
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_UP_COVER_OPEN
void Check_DownCover(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL || DOWN_COVER_STATUS ==0)    //VCC
 {   
    Clr_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
    
    return ;
 }
 
  if(DOWN_COVER_STATUS)  //正常情况下是按下去的,此盖是安装在后盖上的
  {
    Set_Event_Instant(ID_EVENT_DOWN_COVER_OPEN);
  }
}
#endif
/***********************************************************************
函数功能：判断铅封是否打开
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_LEAD_COVER_OPEN
void Check_LeadCover(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL || LEAD_COVER_STATUS ==0)    //VCC
 {
    Clr_Event_Instant(ID_EVENT_LEAD_COVER_OPEN);    
    return ;
 }
 
  if(LEAD_COVER_STATUS)  //正常情况下是按下去的,此盖是安装在后盖上的
  {
    Set_Event_Instant(ID_EVENT_LEAD_COVER_OPEN); 
  }
}
#endif
/***********************************************************************
函数功能：获取时钟电池欠压状态字
入口：无
出口：无
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
函数功能：获取低功耗电池欠压状态字
入口：无
出口：无
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
函数功能：获取AB切换模式按钮
入口：无
出口：无
***********************************************************************/
#ifdef ID_EVENT_AB_FUNC_KEY
void Check_AB_Func_Key(void)
{
 if(Get_Sys_Status()!=SYS_NORMAL)    //VCC
 {
    Clr_Event_Instant(ID_EVENT_AB_FUNC_KEY);
    return ;
 }
 
  if((Inter_Up_Key_STATUS==1)&&(Inter_Down_Key_STATUS==1))  //没有按钮按下
    Clr_Event_Instant(ID_EVENT_AB_FUNC_KEY);
  else                         //有一个按钮按下
    Set_Event_Instant(ID_EVENT_AB_FUNC_KEY);  
}
#endif
/********************************************************************************
函数原型：
功能：检测系统时钟故障

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
函数原型：
功能：跳闸合闸事件执行,并LED指示当前的状态
SwitchFlag--------0拉闸，非0，合闸
*********************************************************************************/
void Excute_Toogle(INT8U SwitchFlag)
{
  //if(PREPAID_EN EQ 0)  //无预付费功能，跳闸、跳闸 LED 指示、跳闸 LCD指示 均不点亮。
  //  return ;
  
  if(SwitchFlag)
  {
      Port_Out_Pub(EXT_ID_TOGGLE,PORT_END);      //合闸
      
      //大继电器，脉冲方式
      Port_Out_Pub(INTER_ID_RELAY_ON,LARGE_RELAY_PULSE_WD);
      return ;

  }
  else
  {
    //大继电器，脉冲方式
    Port_Out_Pub(INTER_ID_RELAY_OFF,LARGE_RELAY_PULSE_WD);
    
    if(Get_Toogle_Out() EQ PULSE_MODE)
    {
      Port_Out_Pub(EXT_ID_TOGGLE,APP_TOOGLE_PORT_PULSE_WD);           //脉冲跳闸
    }
    else      
      Port_Out_Pub(EXT_ID_TOGGLE,PORT_START);           //电平跳闸    
    
  }
}
/********************************************************************************
函数原型：
功能：上电后初始化合闸拉闸状态。
      跳闸合闸事件执行,并LED指示当前的状态
*********************************************************************************/
void Init_Toggle_Status(void)
{
  //Remote_Ctrl_Status.Switch_Status = SWITCH_ON;
  //INIT_STRUCT_VAR(Remote_Ctrl_Status);
}
