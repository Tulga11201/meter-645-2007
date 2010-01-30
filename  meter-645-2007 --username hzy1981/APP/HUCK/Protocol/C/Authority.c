#define AUTHORITY_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H18"
#endif

CONST S_PSW_Map PSW_Map[]=
{
	{PSW_FAC_PARA, PSW_FACTORY}, //��������
	{PSW_RD_ONLY,  PSW_NULL},//ֻ��������û��дȨ��
	{PSW_SET_PSW0, PSW_0},  //0������Ȩ��
	{PSW_SET_PSW1, PSW_1},  //1������Ȩ��
	{PSW_SET_PSW2, PSW_2},  //2������Ȩ��
	{PSW_SET_PSW3, PSW_3},  //3������Ȩ��
	{PSW_SET_PSW4, PSW_4},  //4������Ȩ��
	{PSW_SET_PSW5, PSW_5},  //5������Ȩ��
	{PSW_SET_PSW6, PSW_6},  //6������Ȩ��
	{PSW_SET_PSW7, PSW_7},  //7������Ȩ��
	{PSW_SET_PSW8, PSW_8},  //8������Ȩ��
	{PSW_SET_PSW9, PSW_9},  //9������Ȩ��
	
	//{PSW_ADJ_TIME, PSW_0},   //�㲥Уʱ
	{PSW_SET_DATE, PSW_4},   //��������
	{PSW_SET_TIME, PSW_4},  //����ʱ��
	{PSW_CLR_ALL,  PSW_2},   //��������,���ǵ����0
	//{PSW_CLR_DATA, PSW_0},  //�����������̡���ѹ�ϸ���
	{PSW_SET_ENSTART, PSW_0},   //���õ׶���
	{PSW_SET_PARA,    PSW_4},  //������ͨ����(��������)
};

//�����ģ��ʹ�õĹ̶�����
CONST INT8U Net_Meter_Psw[] = {0x04, 0x11, 0x22, 0x33};

//����ĳ���ݱ�־��Ӧ��дȨ������ȼ���PSW_NULL��ʾ���߱�дȨ��
INT8U Get_PSW_Flag_Map_Level(INT8U PSW_Flag)
{
	INT8U i;
  
	TRACE();
	for(i = 0; i < S_NUM(PSW_Map); i ++)
	{
		if(PSW_Map[i].PSW_Flag EQ PSW_Flag)
			return PSW_Map[i].PSW_Level;
	}
	return PSW_NULL;

}


//extern const S_Protocol_Data_Info Protocol_Data[];
//������ڲ��������Ƿ�������
INT8U Check_Meter_Factory_Status()
{
  if(Get_Meter_Hard_Mode() != MODE_FAC)
  {
    return 0;
  }  //�ǹ���״̬
  else
  {
    return 1;
  }  //����״̬  

}

//����Ƿ��ܷ����������Ϣ
INT8U Check_Debug_En()
{
  if(Get_Meter_Hard_Mode() EQ MODE_RUN)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//������Ƿ��ڱ��״̬���ǵķ���1�����򷵻�0
INT8U Check_Meter_Prog_Status()
{
  //return 1;//test
  return Check_Prog_Status();
}

//�жϵ�ǰ���ڹ������߱��״̬
//ֻҪ�ǳ��ڹ������߱������״̬֮һ���ͷ���1�����򷵻�0
INT8U Check_Meter_Prog_Fac_Status()
{
   if(Check_Meter_Prog_Status() || Check_Meter_Factory_Status())
     return 1;
   else
     return 0;
}

//�������ͨ�ŵ�ַ�İ����Ƿ��£����·���1�����򷵻�0
INT8U Check_Set_ADDR_Key()
{
  return Check_MeterAddr_Status();
}

//���������ݵ�Ȩ��,Ҫ���ڹ���״̬���߱��״̬��Ȩ�ޱ�־
INT8U Check_Clear_Data_Authority()
{
  if((Check_Meter_Prog_Status() EQ 0 && Check_Meter_Factory_Status() EQ 0) || \
     CHECK_STRUCT_VAR(User_Authority_Flag) EQ 0 || \
     CHECK_STRUCT_SUM(User_Authority_Flag) EQ 0 || \
     User_Authority_Flag.Flag != AUTHORITY_FLAG)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

//����Ȩ�ޱ�־
void Set_Authority_Flag()
{
  INT8U Re;
  
  TRACE();
  
  //�����û������뼶��
  Re = CHECK_STRUCT_SUM(User_Authority_Flag); 
  ASSERT(1 EQ Re); 
  User_Authority_Flag.Flag = AUTHORITY_FLAG; //Ȩ�ޱ�־�����Ӱ�ȫ��
  SET_STRUCT_SUM(User_Authority_Flag); 
}

void Clear_Authority_Flag()
{
  User_Authority_Flag.Flag = 0; //Ȩ�ޱ�־�����Ӱ�ȫ��
  SET_STRUCT_SUM(User_Authority_Flag);   
}

void Check_Module_Set_Meter_Status()
{
  INT8U Re;
  
  Re = CHECK_STRUCT_SUM(Module_Set_Meter_Status);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    Module_Set_Meter_Status.Set_En_Mins = 0;
    SET_STRUCT_SUM(Module_Set_Meter_Status);
  }  
  
}

//�����������ݵ��û�Ȩ��
INT8U Get_Net_Meter_User_Authority(INT8U Ctrl_Code, INT8U *pSrc, INT8U SrcLen, INT8U *pSpec_Flag)
{
  PROTO_DI PDI;
  
  Check_Module_Set_Meter_Status();
  
  *pSpec_Flag = 0; //��Ҫ���⴦��ı�־
  
  if(Ctrl_Code EQ C_SET_DATA)//д������Ҫ���⴦��
  {
    mem_cpy(&PDI, pSrc, 4, &PDI, sizeof(PDI));//����PDI    
    if(PDI EQ 0x0EA20000 || PDI EQ 0x0EA20001) //дģ��ͨ��״̬���ߴ�дʹ��
    {
      *pSpec_Flag = 1; //�Ѿ����⴦���˵�
      
      if(memcmp(pSrc + 4, Net_Meter_Psw, 4) EQ 0)//�̶�����
        return PSW_4;//  *pSpec_Flag = 1; //�Ѿ����⴦���˵� 
    }
    //else if(Module_Set_Meter_Status.Set_En_Mins > 0) //���߱�4��Ȩ��
      //return PSW_4;
  } 
  
  return PSW_10;
}

//��ȡ��ǰ���û�Ȩ��,Ҳ��������,������͵����ݲ���Ҫ���룬��ֱ�ӷ���Ȩ��PSW_0
INT8U Get_User_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Posi;//���������ݻ����е���ʼλ��
  INT8U Level;//��ǰ���뼶��
  PROTO_DI PDI;
  
#if NET_METER != NONET_METER //����������Ȩ�޿���
  INT8U Spec_Flag, PSW_Flag;
#endif  

  //��ʱ���� test
  if(Check_Meter_Factory_Status())//�������������ˣ��߱�����Ȩ��
    return PSW_FACTORY;
  
////////////////////////////////////
#if NET_METER != NONET_METER //����������Ȩ�޿���
  if(Ch EQ CHANEL_MOUDEL) 
  {
    PSW_Flag = Get_Net_Meter_User_Authority(Ctrl_Code, pSrc, SrcLen, &Spec_Flag);
    if(Spec_Flag > 0) //���⴦���˵�
      return PSW_Flag;
  }
#endif                           
///////////////////////////////////   
  
//���¶�û�����ϱ�������  
  if(Ctrl_Code EQ C_READ_DATA || Ctrl_Code EQ C_READ_FOLLOW_DATA || Ctrl_Code EQ C_READ_ADDR)
  {
    mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));//�����룬������Ȩ��
    if((PDI & 0xFFFFFF00) EQ 0x04000C00)
      return PSW_NULL;
    
    return PSW_0;//����Ҫ���������£���Ϊ�߱���0������
  }
  else if(Ctrl_Code EQ C_SET_DATA)//д����
  {
    if(Check_Meter_Prog_Status() EQ 0)//û�д��ڱ��״̬�����߱��κ�дȨ��
    {
      //*pErr=PROTOCOL_AUTH_ERR;
      return PSW_NULL;
    }
    /*
    //���ó�ʼ���������ģʽ�ֲ�������������
    mem_cpy(&PDI, pSrc, 4, &PDI, sizeof(PDI));
    if((PDI & 0xFFFFFF00) EQ 0x0E000300 && SET_ENERGY_EN EQ 0)
    {
      return PSW_NULL;
    }*/
    
    Level=pSrc[4];//���뼶��
    Posi=5;//���뿪ʼλ��
  }
  else if(Ctrl_Code EQ C_ADJUST_TIME)//�㲥Уʱ
  {
      return PSW_0;//����Ҫ���������£���Ϊ�߱���0������
  }
  else if(Ctrl_Code EQ C_SET_ADDR)//���ñ��ַ����Ҫ����Ȩ�ޣ�ֻ��Ҫ����ĳ������
  {
    if(Check_Meter_Prog_Status() EQ 0)//����û�а��£�����Ȩ�޴�
      return PSW_NULL;
    else 
      return PSW_0;//����Ҫ���������£���Ϊ�߱���0������
  }
  else if(Ctrl_Code EQ C_FREEZE_DATA)
  {
    return PSW_0; 
  }
  else if(Ctrl_Code EQ C_SET_COM_BAUD)//����ͨ�Ų�����
  {
    return PSW_0;//����Ҫ����
  }
  else if(Ctrl_Code EQ C_SET_PSW)//�޸�����
  { 
    if(Check_Meter_Prog_Status() EQ 0)//û�д��ڱ��״̬�����߱��κ�дȨ��
      return PSW_NULL;
    
    Level=pSrc[4];//�������4�ֽھ������뼶��
    Posi=5;    
  }
  else if(Ctrl_Code EQ C_CLR_ALL ||\
          Ctrl_Code EQ C_CLR_DEMAND ||\
          Ctrl_Code EQ C_CLR_EVENT)
  {
    if(Check_Meter_Prog_Status() EQ 0)//û�д��ڱ��״̬�����߱��κ�дȨ��
      return PSW_NULL;
    
    if(Ctrl_Code EQ C_CLR_ALL && METER_CLR_EN EQ 0) //��ֹ������0
      return PSW_NULL;
    
    Level=pSrc[0];
    Posi=1;         
  }
  else if(Ctrl_Code EQ C_CTRL) //����
  {
    Level=pSrc[0];
    Posi=1;    
  }
  else if(Ctrl_Code EQ C_PORT) //�๦�ܶ�������
  {
    return PSW_0; //����Ҫ���� 
  }
  else if(Ctrl_Code EQ C_REMOTE_AUTH) //Զ�������֤
  {
    return PSW_0; //����Ҫ���� 
  }
  else
  {
   return PSW_NULL;
  }
  //���뼶����0-9֮�������ȷ��
  if(Level>9)
  {
    //*pErr=PROTOCOL_PSW_ERR;//�������
    return PSW_10;
  }
  
  //�Ƚ������Ƿ���ͬ
  if(memcmp(pSrc+Posi,(void *)Cur_PSW.PSW[Level],3)!=0)
  {
    //*pErr=PROTOCOL_PSW_ERR;//�������
    return PSW_10;
  }
  return Level + 1; //PSW_0 -> 1, PSW_9 ->10
}

//������������Ϣ
void Clear_PSW_Err_Info()
{
  DIS_PD_INT;
  
  mem_set((void *)&PSW_Err_Info,0,sizeof(PSW_Err_Info),(void *)&PSW_Err_Info,sizeof(PSW_Err_Info));
  INIT_STRUCT_VAR(PSW_Err_Info);
  SET_STRUCT_SUM(PSW_Err_Info);
  SET_STRUCT_SUM(Event_Data);
  
  EN_PD_INT;
}

//����޸�ĳ��������Ҫ��Ȩ��
INT8U Get_P_Data_Info_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen)//INT16U DI)
{
  INT8U PSW_Flag;
  PROTO_DI PDI;

  TRACE();

  //�Ȼ��������ݵ�������
  if(Ctrl_Code EQ C_READ_DATA || Ctrl_Code EQ C_READ_FOLLOW_DATA || Ctrl_Code EQ C_READ_ADDR)
  {
    return PSW_10;//��ȡ���ݺͺ������ݲ���Ҫ���룬���Ĭ�Ϸ�������10,��͵ȼ�
  }
  else if(Ctrl_Code EQ C_SET_DATA)
  {
    PDI = 0;
    mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));//DI=*(INT16U *)pSrc;
    PSW_Flag = Get_P_Data_PSW_Level(PDI);

    return PSW_Flag;
  }
  else if(Ctrl_Code EQ C_ADJUST_TIME)//�㲥Уʱ
  {
    return PSW_10;//��Ϊ����Ҫ���룬���Ը���һ����ͼ�����(���ж��û�����ʱ���һ���ϸ߼�����) 
  }
  else if(Ctrl_Code EQ C_SET_ADDR)
  {
    return PSW_10; //����ַ����Ϊ����Ҫ���룬���Ը���һ����ͼ�����(���ж��û�����ʱ���һ���ϸ߼�����) 
  }
  else if(Ctrl_Code EQ C_SET_COM_BAUD)
  {
    return PSW_10; //�貨���ʣ���Ϊ����Ҫ���룬���Ը���һ����ͼ�����   
  }
  else if(Ctrl_Code EQ C_SET_PSW)
  {
    return *(pSrc + 8) + 1;//�޸ĸ�������Ҫ�����뼶��Ҳ���Ǳ��޸ĵ�����ļ���
  }
  else if(Ctrl_Code EQ C_CLR_ALL)//����
  {
    return PSW_2;
  }
  else if(Ctrl_Code EQ C_CLR_EVENT)//���¼�
  {
    return PSW_2;
  }
  else if(Ctrl_Code EQ C_CLR_DEMAND)//�����������
  {
    return PSW_4;
  }
  else if(Ctrl_Code EQ C_CTRL) //Զ�̿��ƣ���Ҫ2������
  {
    return PSW_2; 
  }
  else if(Ctrl_Code EQ C_PORT) //�๦�ܶ���
  {
    return PSW_10; 
  }
  else if(Ctrl_Code EQ C_REMOTE_AUTH)
  {
    return PSW_10; 
  }
  return PSW_0;//���0-9������Ȩ�޶�û�����ø����Ĭ��Ϊ0���������
}

//����������ʱ����
void PSW_Timer_Proc()
{
  INT8U Re;
  INT8U Modi_Flag;
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int32U Sec_Bak={CHK_BYTE,0x0,CHK_BYTE};
  
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;
  
  if(Check_Meter_Factory_Status() && PSW_Err_Info.Lock_Mins > 0)//�ڹ���״̬���������
  {
    Clear_PSW_Err_Info(); //��ʱӦ����PSW_Err_Info.Set_En_Mins = 0
    Clr_Event_Instant(ID_EVENT_METER_LOCK);//�����¼�������Һ���ϵ�����־
  }
  
  Modi_Flag = 0;
  
  if(Min_Bak.Var!=Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var=Cur_Time0.Time[T_MIN];
    
    Re=CHECK_STRUCT_SUM(PSW_Err_Info);
    if(1 != Re ||
       PSW_Err_Info.Err_Counts > MAX_AUTHU_ERR_COUNTS ||\
       PSW_Err_Info.Lock_Mins > AUTHU_ERR_LOCK_MINS)
    {
      ASSERT_FAILED(); 
      Clear_PSW_Err_Info();
    }
    
    DIS_PD_INT;
    
    if(PSW_Err_Info.Lock_Mins>0)//����ʱ��ݼ�
    {
      Set_Event_Instant(ID_EVENT_METER_LOCK);  //�������¼�����
      PSW_Err_Info.Lock_Mins--;
      if(PSW_Err_Info.Lock_Mins EQ 0)
      {
        PSW_Err_Info.Err_Counts=0;//����������0
        Clr_Event_Instant(ID_EVENT_METER_LOCK);
      }
      Modi_Flag = 1;
    }
/*    
    if(PSW_Err_Info.Clr_Err_Counts_Mins>0)//1440���Ӻ��������Զ���0
    {
      PSW_Err_Info.Clr_Err_Counts_Mins--;
      if(PSW_Err_Info.Clr_Err_Counts_Mins EQ 0)
        PSW_Err_Info.Err_Counts=0;
      
      Modi_Flag = 1;
    }
*/    
    if(PSW_Err_Info.Set_En_Mins>0)//�������ù���ʱ��
    {
      PSW_Err_Info.Set_En_Mins--;
      Modi_Flag = 1;
    }
    
    if(Modi_Flag EQ 1)
    {
      SET_STRUCT_SUM(PSW_Err_Info);
      SET_STRUCT_SUM(Event_Data);
    }
    
    EN_PD_INT;
//--------------ģ�������ʹ��------------
    Check_Module_Set_Meter_Status();   
    
    if(Module_Set_Meter_Status.Set_En_Mins > 0)
    {
      Module_Set_Meter_Status.Set_En_Mins --;
      SET_STRUCT_SUM(Module_Set_Meter_Status);
    }
  }
} 

//��������Ƿ�����
INT8U Check_PSW_Lock()
{
  TRACE();

  if(PSW_Err_Info.Set_En_Mins > 0)
    return 0;
  
  if(PSW_Err_Info.Lock_Mins > 0)
  {
    Debug_Print("PSW Locked:Err Counts = %d, Lock Mins:%d", PSW_Err_Info.Err_Counts, PSW_Err_Info.Lock_Mins);
    return 1;
  }
  else
    return 0;
}

//�����������ȵĴ���
void PSW_Lock_Proc()
{
  INT8U Re;

  if(PSW_Err_Info.Err_Counts < MAX_AUTHU_ERR_COUNTS)
  {
    Re = CHECK_STRUCT_SUM(PSW_Err_Info); 
    ASSERT(1 EQ Re); 

    DIS_PD_INT;
    
    PSW_Err_Info.Err_Counts ++ ; 
    if(PSW_Err_Info.Err_Counts >= MAX_AUTHU_ERR_COUNTS)
    {
      PSW_Err_Info.Set_En_Mins = 0; //дʹ��ʱ��
      PSW_Err_Info.Lock_Mins = AUTHU_ERR_LOCK_MINS; //����AUTHU_ERR_LOCK_MINS����
      Set_Event_Instant(ID_EVENT_METER_LOCK);   //�������¼�����
    }
    
    SET_STRUCT_SUM(PSW_Err_Info);
    SET_STRUCT_SUM(Event_Data);
    
    EN_PD_INT;
  }

  Debug_Print("User do not have the authority!");
}

//��������ʹ�ܴ���
void PSW_Set_En_Proc()
{
  DIS_PD_INT;
  
  PSW_Err_Info.Set_En_Mins = SET_EN_MINS;
  PSW_Err_Info.Lock_Mins = 0;
  PSW_Err_Info.Err_Counts = 0;
  SET_STRUCT_SUM(PSW_Err_Info);
  SET_STRUCT_SUM(Event_Data);
  
  EN_PD_INT;
}

//��鵱ǰ�û�Ȩ���Ƿ�ͨ��
INT8U Check_User_Authurity(INT8U User_PSW, INT8U Data_PSW)
{
  INT8U Re;
  
  if(Data_PSW EQ PSW_10) //������,����ҪȨ�޼��
    return 1;
  
  if(Data_PSW EQ PSW_FACTORY) //��Ҫ����״̬�Ĳ����������ڹ���״̬�����жϲ�����
  {
    if(Check_Meter_Factory_Status() EQ 0)
      return 0;
  }
  
  Re = CHECK_STRUCT_SUM(PSW_Err_Info);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    Clear_PSW_Err_Info();
  }
  
  //д����
  if(PSW_Err_Info.Set_En_Mins > 0) //����д!
    return 1;  
  else if(PSW_Err_Info.Lock_Mins > 0)//��ֹд��
    return 0;

  //û��дʹ�ܣ�Ҳû�н�ֹд
  if(User_PSW > Data_PSW)
  {
    PSW_Lock_Proc(); //����������
    return 0;
  }
  else
  {
    PSW_Set_En_Proc(); //дʹ�ܴ��� 
    return 1;
  }
  
}

//������������ĸ����,����1��2��3�ֱ��ʾ1��2��3������
INT8U Check_Data_Type(PROTO_DI PDI)
{
  PROTO_DI TempPDI;
  
  TempPDI = (PDI & 0xFFFFFF00);
  
  if(PDI EQ 0x04000108 || PDI EQ 0x04000306 || PDI EQ 0x04000307 || PDI EQ 0x0400040E ||\
     PDI EQ 0x04001001 || PDI EQ 0x04001002 || TempPDI EQ 0x04050100 || TempPDI EQ 0x04050200)
    return 1;
  else if(PDI EQ 0x04000106 || PDI EQ 0x04000107 || PDI EQ 0x04000109 || (PDI >= 0x04000201 && PDI <= 0x04000205) ||\
          PDI EQ 0x04000207 || PDI EQ 0x04000801 || PDI EQ 0x04000802 || (PDI >= 0x04000B01 && PDI <= 0x04000B03) ||\
          PDI EQ 0x04001004 || PDI EQ 0x04001005 || TempPDI EQ 0x04010000 || TempPDI EQ 0x04020000 || TempPDI EQ 0x004030000 ||\
          TempPDI EQ 0x04060000 || TempPDI EQ 0x04060100 || TempPDI EQ 0x04060200 || TempPDI EQ 0x04060300)
    return 2;
  else
    return 3;
}

//����Ƿ���ʱ���������ʱ�α�����
INT8U Check_Year_Date_Table_Data(PROTO_DI PDI)
{
  PROTO_DI TempPDI;
  
  TempPDI = (PDI & 0xFFFFFF00);
  if(TempPDI EQ 0x04010000 || TempPDI EQ 0x04020000)
    return 1;
  else
    return 0;
}

#undef AUTHORITY_C
