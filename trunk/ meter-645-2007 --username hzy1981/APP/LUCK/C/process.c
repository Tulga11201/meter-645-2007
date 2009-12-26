
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



extern PROTO_DI Set_ParaModi_Proc(PROTO_DI ModiDI);
extern unsigned char Ser_Support_Code(item_t code);
/*
//���¶���������ڵĳ�����
CONST CONST_PORT_STATUS  S_Dis_Err_Code[]=
{
  DIS_N0_ERR,DIS_CTRL_LOOP_ERR,DIS_ESAM_ERR,DIS_MEM_ERR,DIS_RTC_ERR,DIS_RTCBAT_LOW,
  DIS_POWER_EXCEED_ERR,DIS_CUR_VERY_NOEVEN_ERR,DIS_VOLT_EXCEED_ERR,DIS_PF_EXCEED_ERR,DIS_DEMAND_EXCEED_ERR
};
*/

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
            break;
        case DOWN_KEY_VALUE:
            //���طѿأ�����ʾ���������Ϣ;Զ�̷ѿأ��˺������᷵�����������Ϣ
            if(Get_Prepaid_Status() EQ PREPAID_MONEY_OVERDRAFT)
              DIS_BEEP_ALARM;
          
            dispback();  //�Ϸ�---------------PUCK
            Refresh_Sleep_Countr(1);
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
   
   if((LOOP_SEC_TIMER_DIFF>2*CYCLE)&& (poweroff() EQ 0) && modeBtoA())// Bģʽ�£���2��ѭ�����ں�û�а������£�����Aģʽ����ȡAģʽ�µ���Ϣ--------PUCK
      RESET_LOOP_DIS;
  
   if((LOOP_SEC_TIMER_DIFF>120)&&modeCtoA())   // Cģʽ�£���2���Ӻ��ް������£�����Aģʽ����ȡAģʽ�µ���Ϣ--------PUCK
      RESET_LOOP_DIS;

   
   if (LIGHT_SEC_TIMER_DIFF== 0) 
   {
     if(poweroff()||Chk_Light_Condition())      //������������ѹ������75%Unʱ���رձ���
        lcdlight(FALSE);
     else                   //�ǵ�������£��򿪱���
        lcdlight(TRUE);
   }
   
   if(LIGHT_SEC_TIMER_DIFF!=0)
   {
      //����/ʣ���� < ������� ��ʾģʽ��ʾģʽ
     if((Light_Mode EQ LIGHT_ON_IRDA ||  Light_Mode EQ LIGHT_ON_MONEY)&& LIGHT_SEC_TIMER_DIFF>IRDA_LIGHT_ON_TIME) 
     {
       //Light_Mode=LIGHT_ON_NONE;
       CLR_LIGHT_ON;     
       lcdlight(FALSE);
     }
     
     //��ť/�忨
     if((Light_Mode EQ LIGHT_ON_CARD || Light_Mode EQ LIGHT_ON_KEY) && (LIGHT_SEC_TIMER_DIFF>KEY_LIGHT_ON_TIME))
     {
#if SYS_ERR_DIS_EN >0
       //Sys_Err_Info.LoopDis=0;
#endif  
       //Light_Mode=LIGHT_ON_NONE;
       CLR_LIGHT_ON;     
       lcdlight(FALSE);
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
  INT8U Byte,Bit;
  if(ErrCode>=DIS_ERR_NUM)
    return ;
  
  
  Byte=ErrCode/8;
  Bit=ErrCode%8;
  if(SetOrClr)
  {
    if(GET_BIT(Sys_Err_Info.ErrCode[Byte],Bit) EQ 0)
      Sys_Err_Info.ErrNum++;
    SET_BIT(Sys_Err_Info.ErrCode[Byte],Bit);
    
  }
  else
  {
    if(GET_BIT(Sys_Err_Info.ErrCode[Byte],Bit))
      Sys_Err_Info.ErrNum--;    
    CLR_BIT(Sys_Err_Info.ErrCode[Byte],Bit);    
    if(Sys_Err_Info.ErrNum EQ 0xff)
      Sys_Err_Info.ErrNum=0;
    
  }
#endif
}

void ReNew_Err_Code(INT8U ErrCode)
{
  SetOrClr_Err_Code(ErrCode,1);
}


void Clr_Err_Code(INT8U ErrCode)
{
  SetOrClr_Err_Code(ErrCode,0);
}