
#define LCD_MAIN_C
#include "Pub_Puck.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "L2"
#endif
/********************************************************************************
PUCK:
�������ܣ�����ȡ�����޸�DI������������־
��ڣ�
���أ�
********************************************************************************/
void Set_Para_Modi_DI(PROTO_DI Di)
{
#ifdef DIS_PARA_JUMP_EN  
  INT8U i;
  for(i=0;i<MAX_MODI_NUM;i++)
  {
    if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
       ASSERT_FAILED();     
    if(Para_Dis_Var.Para_Modi[i]==0)
    {
      Para_Dis_Var.Para_Modi[i]=Di;
      Para_Dis_Var.Flag=1;
      SET_STRUCT_SUM(Para_Dis_Var);
      return ;
    }     
  }
#endif
}
/********************************************************************************
PUCK:
�������ܣ���ȡ�����޸�DI
��ڣ�
���أ�
********************************************************************************/
PROTO_DI Get_Para_Modi_DI(void)
{
  PROTO_DI  temp=0;
  
#ifdef DIS_PARA_JUMP_EN
  INT8U i; 
  
  if(Para_Dis_Var.Flag==0)
    return 0;
    
  for(i=0;i<MAX_MODI_NUM;i++)
  {
    if(Para_Dis_Var.Para_Modi[i]!=0)
    {
      if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
        ASSERT_FAILED();
      temp=Para_Dis_Var.Para_Modi[i];
      Para_Dis_Var.Para_Modi[i]=0;
      SET_STRUCT_SUM(Para_Dis_Var);      
      break;
    }  
  }  
#endif  
  return temp;
}
/********************************************************************************
PUCK:
�������ܣ���ȡ�����޸�DI
��ڣ�
���أ�
********************************************************************************/
INT8U Get_Para_Modi_Flag(void)
{
#ifdef DIS_PARA_JUMP_EN
  if(Para_Dis_Var.Flag)
  {
    if(CHECK_STRUCT_SUM(Para_Dis_Var)==0)
      ASSERT_FAILED();
    Para_Dis_Var.Flag=0;
    SET_STRUCT_SUM(Para_Dis_Var);
    return 1;
  }
#endif
    return 0; 
}
/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/

void LCD_Task_Monitor(void)
{
  if(Get_Sys_Status()==SYS_SLEEP)//������˯�ߵ�����£������κ����� 
  {
    Task_Sleep();
  }
   
  if(Get_Sys_Status()==SYS_RESUME)
  {
    if((dispmode EQ modeA && Sleep_Sec_Countr.Var>MODE_A_NUM) ||   //ѭ��ģʽ
       (dispmode EQ modeB && (Sec_Timer_Pub-Sleep_Sec_Countr.Var>=30)) )   //����ģʽ
    {

        Debug_Print("Lcd Task Enter To Sleep!");            
        Task_Sleep();         
        //�����ˣ����³�ʼ��
        dispmode = modeA;
        dispoffset = -1;   
        START_LOOP_DIS;
        Refresh_Sleep_Countr(0);    
    
    
    }
  }  
}

/*
���ܱ��ڴ�����������£��ɲ��ð������忨�Ȳ����������⣬������û�а������忨�Ȳ���60���رա�
���ܱ�Ҳ�ɲ��ú���ͨ�ŷ�ʽ�������⣬�����ڵ��ܱ�2���Զ��������ں�رա�
���ܱ���ͣ��״̬�£���֧�ֱ����������ͨ�������ͷǰ�����ʽ������⡢�ɼ���仯���ȷ�ʽ����LCD��ʾ��
LCD��ʾ�Ĺر�ʱ��Ϊ���ް�������ʱ���Զ�ѭ��һ�����ں�ر�LCD:�����Ҫ�޸Ĵ��룡����������������
�а�������ʱ���԰�������������30s���Զ��ر�LCD��
*/
/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/
void LCD_Init_PUCK(void)  //LCD��ʾ��ʼ���������ٶ���Ҫ
{
  FillAllScreen();
  if(Get_Sys_Status()==SYS_NORMAL)
  {
    Init_Event_Instant_Para();
    
     Check_Loss_Volt();
     Check_Loss_Curr();
     Check_Volt_Curr_Seq();
     Check_Loss_Parse();
     Check_Neg_Curr();
     Check_Cut_Curr();
  }
   //һ�����룬˵�������ѻ�������ģʽ,�����ϵ���߰�ť���⻽��,Һ���ĳ�ʼ���Ѿ���Init_ExtDevice_PUCK()���
  if((Get_Sys_Status()==SYS_NORMAL) || (Check_Resume_Source(IRAD_RESUME|KEY_RESUME)))
  {
    Initial();
    Refresh_Sleep_Countr(0);
  }
}
/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/

void LCD_Dis_Switch (void)  //10ms����һ��
{
  if(Get_self_Cal_Status()) //У��״̬
  {
    Cal_Dis_Proc();   
  }
  else
  {
    if(Pause_Dis_Event())   //ʱ�����ͣ��ʾ
    {
      Key_Fast_LCD_Proc();  //���Դ���
      Loop_Dis_LCD_Proc();  //ѭ�Դ���
    }
    /*
    Key_Fast_LCD_Proc();  //���Դ���
    Loop_Dis_LCD_Proc();  //ѭ�Դ���
    */
  }
}
/********************************************************************************
PUCK:
�������ܣ�
��ڣ�
���أ�
********************************************************************************/

void LCD_main_LUCK (void)  //10ms����һ��
{
  LCD_Task_Monitor();   //����ģʽ���
  Dis_Jump_Para();      //������ʾ  
  LCD_Dis_Switch();
  Init_LCD_Loop();
}

/*
ͣ����ʾ
��ͣ���Һ����ʾ�Զ��رգ�
��Һ����ʾ�رպ󣬿��ð�����������ʽ����Һ����ʾ�����Ѻ����޲������Զ�ѭ����ʾһ���ر���ʾ��
������ʾ��������30���ر���ʾ��
�����Ľ��͡�
ͣ����������󣬵��ܱ��ɵ�ع��磨���и�����Դ�ĵ��ܱ���⣩��Ϊ���͹��ģ��˹�����Һ����ʾӦ
�Զ��رգ������ð����������ǽӴ���ʽ�����ڲ��򿪱��������£���ͨ�����Ⳮ�������������һ���ַ�����
��Һ����ʾ����г�����Ҫ��������⣩�����ܱ����Ѻ��Զ�ѭ����ʾһ��󣬻򰴼���ʾ��������30���
Һ����ʾӦ�Զ��رա�
*/