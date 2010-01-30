#define CHANNEL_C
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "A2"
#endif

/********************************************************************************

*********************************************************************************/
INT32U Get_Baud_Spec(INT8U PortId,INT8U Baud)
{
  if(GET_BIT(Baud,0x01))
    return 600;
  
  if(GET_BIT(Baud,0x02))
    return 1200;
      
  if(GET_BIT(Baud,0x03))
    return 2400;
  
  if(GET_BIT(Baud,0x04))
    return 4800;
  
  if(GET_BIT(Baud,0x05))
    return 9600;
  
  if(GET_BIT(Baud,0x06))
    return 19200;
  
  
  if(PortId EQ CHANEL_IRDA)  //����Ĭ��
    return BAUD_IRDA_DEFAULT;
  
  //����485Ĭ��
  return BAUD_485_DEFAULT;
}

/********************************************************************************
����ԭ�ͣ�void Get_Buad_Para(void)
���ܣ���ʼ������ͨ��
*********************************************************************************/
void Get_Buad_Para(void)
{
  INT16U Len;
  INT8U temp;
  
  temp=0;
  Len=Read_Storage_Data(DI_CHANEL_485_1,&temp,&temp,1);
  if(Len !=1)
  {
    ASSERT_FAILED();    
  }
  Chanel_Para[CHANEL_485_1].Baud=Get_Baud_Spec(CHANEL_485_1,temp);
  SET_STRUCT_SUM(Chanel_Para[CHANEL_485_1]);
      
  temp=0;
  Len=Read_Storage_Data(DI_CHANEL_485_2,&temp,&temp,1);
  if(Len !=1)
  {
    ASSERT_FAILED();    
  }
  Chanel_Para[CHANEL_485_2].Baud=Get_Baud_Spec(CHANEL_485_2,temp);
  SET_STRUCT_SUM(Chanel_Para[CHANEL_485_2]);  
}

/********************************************************************************
����ԭ�ͣ�void Init_All_Channel(void)
���ܣ���ʼ������ͨ��
*********************************************************************************/
void Init_All_Channel(void)
{
  Get_Buad_Para();  
  Open_Channel_PUCK(CHANEL_IRDA,Chanel_Para[CHANEL_IRDA].Baud,SAU_PARITY_EVEN);    
  Open_Channel_PUCK(CHANEL_485_1,Chanel_Para[CHANEL_485_1].Baud,SAU_PARITY_EVEN);    
  Open_Channel_PUCK(CHANEL_485_2,Chanel_Para[CHANEL_485_2].Baud,SAU_PARITY_EVEN);
  
#ifdef CHANEL_MOUDEL
  if(BAUD_MOUDLE)        //�ز���GPRS��
    Chanel_Para[CHANEL_MOUDEL].Baud=BAUD_MOUDLE;
  else                   //Զ�̷ѿر�
    Chanel_Para[CHANEL_MOUDEL].Baud=Chanel_Para[CHANEL_485_2].Baud;
    
  SET_STRUCT_SUM(Chanel_Para[CHANEL_MOUDEL]);
  Open_Channel_PUCK(CHANEL_MOUDEL,Chanel_Para[CHANEL_MOUDEL].Baud,SAU_PARITY_EVEN); 
#endif
}

/********************************************************************************
����ԭ�ͣ�INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U len)
�������ܣ���ĳͨ����������
��ڲ�����Channl,ͨ����
          Srcbuf�����͵�������ʼ��ַ 
          Src_Len,Դ���ݵĳ���
���ڲ�����1�����ͳɹ���0������ʧ��
*********************************************************************************/
INT8U  Send_HostData_Public_Puck(INT8U Channl,INT8U *Srcbuf,INT16U Src_Len)
{
  INT8U Flag;
  
  /*645һ����С���ܵ���10�ֽ�
  Flag=ASSERT(Src_Len>=10);
  if(Flag)
    return 0;
  */
  
  Flag=Channel_DataSend_PUCK(Channl,Srcbuf,Src_Len);  
  return Flag;
}
/********************************************************************************
����ԭ�ͣ�INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len)
�������ܣ�����Կڷ�������
��ڲ�����
          Srcbuf�����͵�������ʼ��ַ 
          Src_Len,Դ���ݵĳ���
���ڲ�����1�����ͳɹ���0������ʧ��
*********************************************************************************/
INT8U  Debug_Out_Public_Puck(INT8U *Srcbuf,INT16U Src_Len)
{
 INT8U Flag;
 Flag=Channel_DataSend_PUCK(CHANEL_DEBG,Srcbuf,Src_Len);  
  return Flag;
}
/********************************************************************************
����ԭ�ͣ�INT8U  Debug_Out_Puts_Puck(INT8S *Srcbuf)
�������ܣ�����Կڷ����ִ�
��ڲ�����Channl,ͨ����
          Srcbuf�����͵�������ʼ��ַ 
���ڲ�����1�����ͳɹ���0������ʧ��
*********************************************************************************/
INT8U  Debug_Out_Puts_Puck(INT8S *Srcbuf)
{
 INT8U Flag;
 Flag=Channel_DataSend_PUCK(CHANEL_DEBG,(INT8U *)Srcbuf,strlen((char *)Srcbuf));  
  return Flag;
}
/********************************************************************************
����ԭ�ͣ�void DataRec_Monitor_PUCK(void)
���ܣ���ȡ����ͨ����645����

*********************************************************************************/
void Channel_Data_Proc_PUCK(INT32U Status)
{
  INT8U i;

  if(Get_Main_Init_Flag() EQ  MAIN_INITING)  //�������ʼ��δ���
    return ;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
  {      
      Channel_DataReceive_PUCK(i,Status);     
  }
  Remote_Key_Proc();   //resumeģʽ�£������Թ���
}

void Debug_Channel_Switch(INT32U Mode)
{    
  if((Check_Debug_En()==1)&&(Chanel_Para[CHANEL_IRDA].Baud!=BAUD_DEBG))  //���ÿ��л������Կ�
  {
    Chanel_Para[CHANEL_DEBG].Baud=BAUD_DEBG;
    Open_Channel_PUCK(CHANEL_DEBG,BAUD_DEBG,SAU_PARITY_NONE);
    
    Debug_Out_Puts_Puck("\r\nPUCK:Switch To Debug CHannel!");
    
    //DIS_UART0_REC;        //����ģʽ�£��ر�UART0�ڵĽ��գ������жϣ�����shell
    SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]);
  }
  else
  {
    if((Check_Debug_En()==0)&&(Chanel_Para[CHANEL_IRDA].Baud!=BAUD_IRDA))  //���ÿ��л���������
    {
      if(SYS_NORMAL==Mode)
      {        
        Chanel_Para[CHANEL_IRDA].Baud=BAUD_IRDA;
        Open_Channel_PUCK(CHANEL_IRDA,BAUD_IRDA,SAU_PARITY_EVEN);
        SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]); 
        return ;
      }
      if(SYS_RESUME==Mode &&Check_Resume_Source(IRAD_RESUME)) //���⻽��ģʽ
      {
        if(IRDA_READ_METER_EN)   //��key�Ѿ������£����⻽�ѣ�HUCK������� Init_ExtDevice_PUCK()���Ժ���ڵĳ�ʼ��
        {          
          if((Resume_Src.Src_Flag&(IRAD_RESUME|KEY_RESUME))==(IRAD_RESUME|KEY_RESUME))  //ͬʱ����2������Դ
          {
            if((Key_WkUP_Ms_Timr-Irda_WkUP_Ms_Timr<=1000) || (Irda_WkUP_Ms_Timr-Key_WkUP_Ms_Timr<=1000))   //�Ȱ�ť�������;�����Ⱥ����ť����ʱ�����ĳһ��Χ�ڣ����У�
            {
              Resume_Src.Src_Flag&=(INT8U)(~IRAD_RESUME);  //������⻽��Դ
              mem_set((void *)(&Irda_Wake_Ctrl),0,sizeof(Irda_Wake_Ctrl),\
               (void *)(&Irda_Wake_Ctrl),sizeof(Irda_Wake_Ctrl));   
              STOP_IR_DECODE;       //�� START_IR_DECODE ����
              START_IRDA_WAKE; 
              return ;
            }            
          }
          /**/
          //Switch_Main_Osc(RUN_MODE);      //���Ѻ����ڲ������л����ⲿ����
          //IRDA_FAR_REC_EN;              //������տ���
          BAK_POWER_FOR_IRDA;            //Զ�����Դ�ɵ͹��ĵ�ع���;
          OS_TimeDly_Ms(200);   //200ms˯��
          //Debug_Out_Public_Puck("\r\nPUCK:Switch To IRDA CHannel!",30);
          Chanel_Para[CHANEL_IRDA].Baud=BAUD_IRDA;
          SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]); 
          Open_Channel_PUCK(CHANEL_IRDA,BAUD_IRDA,SAU_PARITY_EVEN);
          if(0==INTER_DECODE_EN)  //��resumeģʽ�µĺ��⻽�ѣ�ֹͣ���ѣ���������(Sleepģʽ�µĻ��ѣ��Ѵ���)
          {
            STOP_FAST_TIMER;
            if(RESUME_REMOTER_EN)   //ң������       
              START_IR_DECODE;       //�����£�����ʹ�ú���ң����
            STOP_IRDA_WAKE;           //ȷ���Ѿ����ѣ��Ժ�رջ��ѽŵ��жϣ��� START_IR_DECODE ����
          }
        }
      }
    }  
  } 
}
/********************************************************************************
����ԭ�ͣ�void Channel_Switch_PUCK(INT32U Mode)
���ܣ�ͨ�����л������ݹ���״̬�����״̬���������ڵ����á�

*********************************************************************************/
void Channel_Switch_PUCK(INT32U Mode)
{ 
  if(CHANEL_DEBG==CHANEL_IRDA)
  {
     Debug_Channel_Switch(Mode);
  }  
}
/********************************************************************************
����ԭ�ͣ�void Monitor_Para_Modi_PUCK(void)
���ܣ������в�������ά��������������ͨ�����¼��ȡ�

*********************************************************************************/
void Para_Modi_Monitor_PUCK(void)
{
  PROTO_DI temp;

  while(Get_Para_Modify(&temp))
  {
    Debug_Print("Para Modified In Channel Task:0x%lx",temp);
    switch(temp)
    {
      case DI_CHANEL_485_1:  //��һ·485�����޸�
      case DI_CHANEL_485_2:   //�ڶ�·485�����޸�
          Init_All_Channel();
          Debug_Print("CHANEL_485_1/CHANEL_485_2 Baud Changed");
      break; 
      default:   //���²������Ż�
      if((temp>=NUMBMODEA)&&(temp<=NUMBMODEB))
        lcdinit();                              //Һ�����������޸�  
        break;
    }    
  }   
}

/********************************************************************************
����ԭ�ͣ�void Init_All_UART(void)
���ܣ���ʼ������ͨ��
*********************************************************************************/
void Init_All_UART(INT32U Mode)
{
  INT8U i;
  switch(Mode)
  {
  case SYS_NORMAL:
    Init_DebugChanel_PUCK(0);         //���Կڳ�ʼ��
    Init_All_Channel();
    break;
    
  case SYS_RESUME:    //ֻ�����Ǻ��⡢��ť������⻽�ѣ��������Ѳ������˺���----------PUCK
    Get_Buad_Para();
    for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
    {
      if(i!=CHANEL_IRDA)   //���Ǻ����ڣ�ͳͳ�ر�
        Close_Channel_PUCK(i); 
      else             //�ǵ��Կ�
        Init_DebugChanel_PUCK(1);
    }
    //���Ѻ�ĺ�����л�����channel�����У����ݺ��Ⳮ��ģʽ���л�  
    break;    
  case SYS_SLEEP:
   //�ر����д���
    for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
      Close_Channel_PUCK(i);   //�ر�ȫ������------------PUCK
    Chanel_Para[CHANEL_IRDA].Baud=0;  //������Ⲩ���ʣ��Ա��ڻ��Ѻ󣬸ÿڵ����³�ʼ��
    SET_STRUCT_SUM(Chanel_Para[CHANEL_IRDA]); 
    break;
    
  }
}

/********************************************************************************
����ԭ�ͣ�void Init_DebugChanel_PUCK(INT8U FacFlag)
���ܣ���ʼ�����Կ�ͨ��
FacFlag-----1:��Ҫ�ж�����״̬��0--------����Ҫ
*********************************************************************************/
void Init_DebugChanel_PUCK(INT8U FacFlag)
{
  /*if(JUDGE_POWER_OFF)  //������
    return ;
  */
  if(CHANEL_DEBG==CHANEL_IRDA)
  {       
    if(FacFlag)         //��Ҫ�ж�����״̬
    {
      if(Check_Debug_En())  //�ǹ���״̬��ӡ)
      {
        Chanel_Para[CHANEL_DEBG].Baud=BAUD_DEBG;
        SET_STRUCT_SUM(Chanel_Para[CHANEL_DEBG]); 
        Open_Channel_PUCK(CHANEL_DEBG,BAUD_DEBG,SAU_PARITY_NONE); 
      }
    }
    else               //����Ҫ�ж�����״̬     
    {
      Chanel_Para[CHANEL_DEBG].Baud=BAUD_DEBG;
      SET_STRUCT_SUM(Chanel_Para[CHANEL_DEBG]); 
      Open_Channel_PUCK(CHANEL_DEBG,BAUD_DEBG,SAU_PARITY_NONE); 
    }
  }  
}
/********************************************************************************
����ԭ�ͣ�void Close_DebugChanel_PUCK(INT8U FacFlag)
���ܣ���ʼ�����Կ�ͨ��
FacFlag-----1:��Ҫ�ж�����״̬��0--------����Ҫ
*********************************************************************************/
void Close_DebugChanel_PUCK(INT8U FacFlag)
{
  if(CHANEL_DEBG==CHANEL_IRDA)
  {
    Chanel_Para[CHANEL_DEBG].Baud=0;
    SET_STRUCT_SUM(Chanel_Para[CHANEL_DEBG]);    
    if(FacFlag)         //��Ҫ�ж�����״̬
    {
      if(Check_Debug_En()==0)  //���ǹ���״̬���رյ��Կ�
        Close_Channel_PUCK(CHANEL_DEBG); 
    }
    else               //����Ҫ�ж�����״̬     
        Close_Channel_PUCK(CHANEL_DEBG); 
  }  
}
/**********************************************************************************
�������ܣ����ͨ�Ų����ṹ���У���
��ڣ���
���ڣ���
**********************************************************************************/	
void Check_Channel_ParaCS(void)
{
  INT8U i,Flag;
  
  Flag=0;
  
  for(i=CHANEL_MIN;i<=CHANEL_MAX;i++)
  {
    Flag=CHECK_STRUCT_SUM(Chanel_Para[i]); 
    ASSERT(1==Flag);
    if(!Flag)
    Debug_Print("Channel_Error----->Channel_Para Struct CS Error In Channel Proc!");
  }

  Flag=CHECK_STRUCT_VAR(S_Buf_PUCK);
  ASSERT(1==Flag);
}

/**********************************************************************************
�������ܣ�
��ڣ���
���ڣ���
**********************************************************************************/	
void Init_Channel_Sram(void)
{
#ifdef CHANNEL_FAST_EN
  INIT_STRUCT_VAR(Rec_Frame_Status);
#endif
}
/********************************************************************************
����ԭ�ͣ�void Channel_Main_PUCK(INT8U Flag)
�������ܣ�ͨ��ͨ������������
*********************************************************************************/
void Channel_Main_PUCK(INT8U Flag)  //10ms����һ��
{
  static volatile S_Int32U Sec_Timer_Bak={CHK_BYTE,0xFFFFFFFF,CHK_BYTE};
  INT32U Status;
  
  Status=Get_Sys_Status();
  if(Status==SYS_SLEEP) //ֻ��������ģʽ�£������¼��Ĵ���
    return ;
  
  if(Flag)
  {
    Init_Channel_Sram();
    return ;
  }
  
  Channel_Data_Proc_PUCK(Status);  //10ms����һ��  
  if(Sec_Timer_Bak.Var!=Sec_Timer_Pub)  //����ģʽ�£�1���һ��
  {
    if(Status==SYS_NORMAL)
    {
      Para_Modi_Monitor_PUCK();   //1s
      Check_Channel_ParaCS();    //1s
      Check_LCDVar_Cs();    //1s��һ��
    }
    Channel_Switch_PUCK(Status);     //1s 
    Sec_Timer_Bak.Var=Sec_Timer_Pub;
  }
}
