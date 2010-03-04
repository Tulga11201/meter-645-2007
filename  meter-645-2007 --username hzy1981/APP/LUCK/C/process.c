
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
1:���ڵ��ܱ�������쳣��ʾ���쳣һ�������轫�Զ�ѭ����ʾ������ͣ��Һ�����̶���ʾ�ù����쳣���롣���������쳣ֻ��һ������ʱ��Һ�����̶���ʾ�ù������쳣���롣���������쳣�м���ͬʱ����ʱ�����չ������쳣�������˳��ѭ����ʾ����ʾ���Ϊѭ��ʱ�䣬���԰���һ�����������쳣������ʾ������ѭ����ʾ������ް���ʱ��60S�󣬷��ع������쳣�����Զ�ѭ����ʾ��
2:�����¼����쳣��ʾ��һ��������Ҫ��ѭ����ʾ�ĵ�һ�������¼����쳣���롣���¼����쳣����ֻ��һ������ʱ����ѭ����ʾ�ĵ�һ��������¼����쳣���롣���¼����쳣�����м���ͬʱ����ʱ����ѭ����ʾ�ĵ�һ��ǰ���յ���˳�����ȫ���������¼����쳣���룬��ʾ���Ϊѭ��ʱ�䡣ͨ���������԰��Է�����ȫ���쳣���롣
3:����CUP���쳣��ʾ����CPU����������з������쳣��Ҫ��CPU����������������ʾ�����CPU���󷵻��Զ�ѭ����ʾ�������طѿر���иù��ܣ�
4:Զ�̷ѿأ�err10��err16��ʾ����
*/

#if DIS_METER_FAULT_EN >0
  CONST INT8U CONST_DIS_FAULT_ITEM[]=
  {DIS_CTRL_LOOP_ERR,DIS_ESAM_ERR,DIS_MEM_ERR,DIS_RTCBAT_LOW,DIS_RTC_ERR  
  };
  #define MAX_DIS_METER_FAULT_NUM (sizeof(CONST_DIS_FAULT_ITEM)/sizeof(INT8U))
  #define DIS_FAULT_SEC_TIME CYCLE
  #define DIS_FAULT_SJMP_SEC 60
#endif

  
  
  
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //Զ�̷ѿر�
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
�������ܣ��ж��Ƿ���ѭ��ģʽ
��ڣ�
���أ�
    Aģʽ
bool ModeABLoop(void)
{
  if((dispmode== modeA)||(dispmode==modeB))
    return LoopFlag;
  
  return 0;  
}
********************************************************************************/
/********************************************************************************
PUCK:
�������ܣ�Aģʽ�µķ���(����ģʽ�²��߱��Զ���������)
��ڣ�
���أ�
    Aģʽ
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
    lcdshow(dispmode,dispoffset);  //��ȡAģʽ�£���Ӧ��ʾ���ľ�����ʾԪ����Ϣ-----------PUCK
    return(TRUE);
}

/********************************************************************************
PUCK:���ƣ�ֻ���Cģʽ��Ч
�������ܣ����ƣ����� dispcursor(Cģʽ)
��ڣ�
���أ�
********************************************************************************/
void dispright(void) 
{
  if (dispmode != modeC) //�л���Cģʽ�����״̬��ʼ��---------PUCK
  {
      dispcursor = RIGHTBITS;
      dispmode = modeC;
      dispcode.code = 0;
      Sub_Vlist.subindex=0;
      Sub_Vlist.exist=0;
  }
  if (dispcursor > MINBITS)  //������ƣ���1����Ϊ��ʾ�Ǵ��ҵ���-------------PUCK
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
PUCK:���ƣ�ֻ���Cģʽ��Ч
�������ܣ����ƣ����� dispcursor(Cģʽ)
��ڣ�
���أ�
********************************************************************************/
void displeft(void) 
{
  if (dispmode != modeC)  //�л���Cģʽ�����״̬��ʼ��---------PUCK
  {
      dispcursor = LEFTBITS;
      dispmode = modeC;
      dispcode.code = 0;
      Sub_Vlist.subindex=0;
      Sub_Vlist.exist=0;
  }
  if (dispcursor < MAXBITS) //������ƣ���1����Ϊ��ʾ�Ǵ��ҵ���-------------PUCK
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





// ���ݺ�����յİ���ֵ���д���
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
            Key_Fast_LCD_Proc(AB_KEY_VALUE);  //0x10������A����ʾ��0x1F������B����ʾ
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
     lcdinit();  //��ʾ������ʼ��----------PUCK
    //��ʾsram������ʼ��----------PUCK
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
    INIT_STRUCT_VAR(Sys_Err_Info);  //��ͷβ����
#endif   
}
/********************************************************************************
�������ܣ�����Ƿ�رձ���
��ڣ�
���أ�
********************************************************************************/
INT8U Chk_Light_Condition(void)
{
  FP32S temp;  
  temp=Get_Max_Num(Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C);
  temp/=UNIT_V;
  if(temp<Get_Un()*(FP32S)0.75)  //˵�������ѹ������75%Un
    return 1;  
  return 0;
}
/********************************************************************************
�������ܣ����µ͹����¼�����
��ڣ�
���أ�Flag-----0�������1-------���¼�����
********************************************************************************/
void Refresh_Sleep_Countr(INT8U Flag)
{         
  if(Get_Sys_Status()==SYS_RESUME)
  {
    if(dispmode EQ modeA) //ѭ��ģʽ
    {
      if(Flag)
        Sleep_Sec_Countr.Var++; 
      else
        Sleep_Sec_Countr.Var=0;
      return ;
    }  
    
    if(dispmode EQ modeB) //����ģʽ
    { 
      Sleep_Sec_Countr.Var=Sec_Timer_Pub;  
    }
  }
  else
  {
    if(dispmode EQ modeA) //ѭ��ģʽ
      Sleep_Sec_Countr.Var=0;
    
    if(dispmode EQ modeB) //����ģʽ
      Sleep_Sec_Countr.Var=Sec_Timer_Pub;
  }
}

INT8U Judge_Mask_Dis(void)
{
  //ȫ����ʾ20����:138�귭ת1��
  if(Sec_Timer_Pub<=20 && (Get_Sys_Status()==SYS_NORMAL))  //����ģʽ�£�20����ȫ����ʾ
    return 1;
  
  if(poweroff())  //���������
    return 1;
  
  if((Key_Value_Pub.Key.Bit.UpKey)||(Key_Value_Pub.Key.Bit.DownKey))
    return 1;  
  
  return 0;  
}

/********************************************************************************
�������ܣ���������Ϣ:ֻ��ͨ����ť��������
��ڣ�
���أ�1-----------------�е�������ʾ��0---------------�޵�������ʾ��
********************************************************************************/
INT8U Dis_Meter_Fault(void) 
{
#if DIS_METER_FAULT_EN EQ 0   //����ʾ������
  return 0;
#else
  char temp[10]={0};
  INT8U id,i,flag;
  
  //if(UP_COVER_STATUS EQ 0)
  //  ReNew_Err_Code(DIS_CTRL_LOOP_ERR);
  
  if(DOWN_COVER_STATUS)
    ReNew_Err_Code(DIS_MEM_ERR);
  
   //ȫ����ʾ20����:138�귭ת1��
  
  if(Sys_Err_Info.FaultDis EQ 0)
    return 0;
  
  if(Judge_Mask_Dis())
    return 0;
    
  if((Sys_Err_Info.FaultCtrl EQ 0) && (Sec_Timer_Pub-Sec_Timer_Default.Var<DIS_FAULT_SJMP_SEC))
    return 0;
  
  if((Sys_Err_Info.FaultCtrl) && (Sec_Timer_Pub-Sec_Timer_Default.Var<CYCLE))       //����ģʽ�µ�ѭ��
    return 1;
  
  if((Sys_Err_Info.FaultCtrl EQ 0) && (Sec_Timer_Pub-Sec_Timer_Default.Var>=DIS_FAULT_SJMP_SEC)) //��ť���л�������ģʽ
  {
    Sys_Err_Info.FaultCtrl=1;
  }
  
  flag=0;
  for(i=0;i<MAX_DIS_METER_FAULT_NUM;i++)
  {
    id=CONST_DIS_FAULT_ITEM[i];
    if(GET_BIT(Sys_Err_Info.ErrCode[id/8],id%8))  //�ҵ���ʾ�Ĵ��������
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
�������ܣ������ϻ����¼���ʾ:ͨ����ť���������߶�ʱ����
��ڣ�
���أ�1-----------------�е�������ʾ��0---------------�޵�������ʾ��
********************************************************************************/
INT8U Dis_Meter_Delay(void) 
{
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //Զ�̷ѿر�
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
    if(GET_BIT(Sys_Err_Info.ErrCode[id/8],id%8))  //�ҵ���ʾ�Ĵ��������
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
�������ܣ���ť���������ʾ����
��ڣ�
���أ�
********************************************************************************/
void  Clr_Dis_Err_Key(void)
{
  
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //Զ�̷ѿر�  
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
PUCK:������ʾ����,������ UPDATETIME ms
�������ܣ���ť�ȿ�����Ӧ��LCD����
��ڣ�
���أ�
********************************************************************************/
void Key_Fast_LCD_Proc(void) 
{
  INT8U KeyValue;
  KeyValue=Get_MeterKey_PUCK(LUCK);
  
  if((KeyValue<MIN_KEY_VALUE)||(KeyValue>MAX_KEY_VALUE))
    return ;
  
  Light_Mode=LIGHT_ON_KEY;   //��ǰ��ʾģʽΪ��ť��ʾ
  
  switch(KeyValue)    //���»�ȡ�������ʾԪ����Ϣ------------PUCK
  {
        case UP_KEY_VALUE :
            //���طѿأ�����ʾ���������Ϣ;Զ�̷ѿأ��˺������᷵�����������Ϣ
            if(Get_Prepaid_Status() EQ PREPAID_MONEY_OVERDRAFT)
              DIS_BEEP_ALARM;
          
            dispnext();  //�·�---------------PUCK
            Refresh_Sleep_Countr(1);
            Clr_Dis_Err_Key();
            break;
        case DOWN_KEY_VALUE:
            //���طѿأ�����ʾ���������Ϣ;Զ�̷ѿأ��˺������᷵�����������Ϣ
            if(Get_Prepaid_Status() EQ PREPAID_MONEY_OVERDRAFT)
              DIS_BEEP_ALARM;
          
            dispback();  //�Ϸ�---------------PUCK
            Refresh_Sleep_Countr(1);
            Clr_Dis_Err_Key();
            break;
            
        case LEFT_KEY_VALUE :
            //Debug_Print("LeftKey Pressed!");
            if(poweroff())  //��������£��˼���������
              break;
            displeft();  //����---------------PUCK
            break;
        case RIGHT_KEY_VALUE :
            //Debug_Print("RightKey Pressed!");
            if(poweroff()) //��������£��˼���������
              break;
            dispright();  //����----------------PUCK
            break;
        
        case AB_KEY_VALUE :   //ABģʽ�л�----------------PUCK
            //Debug_Print("AB Mode Switch Key Pressed!");
            modeBorA();
            break;
              
        case A_KEY_VALUE :   //ģʽ�л���A----------------PUCK
            //09-02-09 PUCK Add: modeAtoB
            dispmode = modeA;
            dispcursor = MODE_A_B_BITS;
            dispoffset = 0;
            lcdshow(dispmode, dispoffset);
            break;
            
        case B_KEY_VALUE :   //ģʽ�л���B----------------PUCK
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
  screen(dispmode, dispcursor);  //ˢ��----------PUCK
  LCD_Loop_Ms10Timr.Var=Ms10_Timer_Pub;
  LCD_Loop_Num.Var=0;
  RESET_LOOP_DIS;
  
#if SYS_ERR_DIS_EN >0
  Sys_Err_Info.LoopDis=1;  
#endif   
}

/********************************************************************************
PUCK:������ʾ����,������ UPDATETIME ms
�������ܣ�ѭ�Ե�������ʾ����
��ڣ�
���أ�
********************************************************************************/
INT8U Dis_Meter_System_Err(void)
{
 #if SYS_ERR_DIS_EN >0
  char temp[10]={0};
  INT8U i,Flag;
  
  if(poweroff())  //���������
    return 0;
  
  //Sys_Err_Info.ErrNum=3;  Sys_Err_Info.ErrCode[0]=4;  Sys_Err_Info.ErrCode[1]=1;  Sys_Err_Info.ErrCode[4]=1;
    
  if(CHECK_STRUCT_VAR(Sys_Err_Info) EQ 0 || Sys_Err_Info.ErrNum>DIS_ERR_NUM)
   ASSERT_FAILED();
  
  if(Sys_Err_Info.ErrNum && Sys_Err_Info.LoopDis EQ 0)  //�д����Ҳ���Ѳ�Բ���ʾ
  {
    dispoffset=-1;    //����ʾ���ڵ�һ�������
    if(LOOP_SEC_TIMER_DIFF>=CYCLE)     //Ѳ�Դ���������Ϣ
    {  
      Flag=0;
      for(i=Sys_Err_Info.DisIndex+1;i<DIS_ERR_NUM;i++)
      {
        if(GET_BIT(Sys_Err_Info.ErrCode[i/8],i%8))  //�ҵ���ʾ�Ĵ��������
        {
          Sys_Err_Info.DisIndex=i;  
          Flag=1;
          break; 
        }
      }
      
      if(!Flag)   //��ǰ��ʾ���Ѿ����������,����ѭ��ģʽ
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
PUCK:ѭ��ʾ���
�������ܣ�
��ڣ�
���أ�
********************************************************************************/
void Dis_Meter_Loop(void)
{
  
#if SYS_ERR_DIS_EN >0      //�Ѿ���ʾ��������ˣ������Լ������ʾ
   if(Sys_Err_Info.ErrNum && dispoffset EQ MODE_A_NUM-1)  //ѭ�����ˣ�������������ʾ
   {
     Sys_Err_Info.LoopDis=0;
     return ;
   }
#endif 
     
   if((LOOP_SEC_TIMER_DIFF>CYCLE)&&disproll()) // Aģʽ�£���1�����ں�û�а������£���ȡAģʽ�µ���ʾ��Ϣ--------PUCK
   {
     RESET_LOOP_DIS;
     Refresh_Sleep_Countr(1);
   }
   
   //if((LOOP_SEC_TIMER_DIFF>2*CYCLE)&& (poweroff() EQ 0) && modeBtoA())// Bģʽ�£���2��ѭ�����ں�û�а������£�����Aģʽ����ȡAģʽ�µ���Ϣ--------PUCK
   if((LOOP_SEC_TIMER_DIFF>=KEY_JUMP_LOOP_TIME)&& (poweroff() EQ 0) && modeBtoA())// Bģʽ�£���2��ѭ�����ں�û�а������£�����Aģʽ����ȡAģʽ�µ���Ϣ--------PUCK
      RESET_LOOP_DIS;
  
   if((LOOP_SEC_TIMER_DIFF>ALL_JUMP_LOOP_TIME)&&modeCtoA())   // Cģʽ�£���2���Ӻ��ް������£�����Aģʽ����ȡAģʽ�µ���Ϣ--------PUCK
      RESET_LOOP_DIS;

   
   if (LIGHT_SEC_TIMER_DIFF== 0) 
   {
     if(poweroff()||Chk_Light_Condition())      //������������ѹ������75%Unʱ���رձ���
        Turn_Light_Off();
     else                   //�ǵ�������£��򿪱���
        Turn_Light_On();
   }
   
   if(LIGHT_SEC_TIMER_DIFF!=0)
   {
      //����/ʣ���� < ������� ��ʾģʽ��ʾģʽ
     if((Light_Mode EQ LIGHT_ON_IRDA ||  Light_Mode EQ LIGHT_ON_MONEY)&& LIGHT_SEC_TIMER_DIFF>IRDA_LIGHT_ON_TIME) 
     {
       //Light_Mode=LIGHT_ON_NONE;
       CLR_LIGHT_ON;     
       Turn_Light_Off();
     }
     
     //��ť/�忨
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
    if((dispmode EQ modeA && Sleep_Sec_Countr.Var>MODE_A_NUM) && dispoffset EQ 0)   //ѭ��ģʽ
      return ;
  }
   
   screen(dispmode, dispcursor);  //ˢ��----------PUCK
}
/********************************************************************************
PUCK:������ʾ����,������ UPDATETIME ms
�������ܣ�ѭ�Ե�������ʾ����
��ڣ�
���أ�
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
  
  //ȫ����ʾ20����:138�귭ת1��
  if(Sec_Timer_Pub<=20 && (Get_Sys_Status()==SYS_NORMAL))  //����ģʽ�£�20����ȫ����ʾ
    return ;
  
  if(Dis_Meter_System_Err() EQ 0)
    Dis_Meter_Loop();   
}

/********************************************************************************
PUCK:������ʾ����,������ UPDATETIME ms
�������ܣ���ť�ȿ�����Ӧ��LCD��������
��ڣ�
���أ�
********************************************************************************/
void Dis_Jump_Para(void) 
{
#ifdef DIS_PARA_JUMP_EN
   PROTO_DI modipara;
   if(modipara=Get_Para_Modi_DI())   //��ʾ�����޸ģ����²�����������Һ��------PUCK
    {
      if(Ser_Support_Code(modipara))
      {
        if(DI_TIME EQ modipara)  //ʱ/��/�벻����
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
�������ܣ�����ϵͳ������ʾ����
��ڣ�Errcode������涨����ʾ�������
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
 
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //Զ�̷ѿر�     
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
      if(GET_BIT(Sys_Err_Info.ErrCode[Byte],Bit)) //������Ϣ����
      {
        break ;
      }        
    }
    
    if(i>=MAX_DIS_METER_FAULT_NUM)  //������Ϣ������
    {
        Sys_Err_Info.FaultDis=0;
        Sys_Err_Info.FaultCtrl=0;        
    }
    
#if (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE))  //Զ�̷ѿر�     
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
