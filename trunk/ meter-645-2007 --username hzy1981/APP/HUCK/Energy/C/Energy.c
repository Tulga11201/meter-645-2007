#define ENERGY_C
#include "Includes.h"

//extern void Event_Energy_Cumu(MEASU_ENERG *pEnergy);
volatile MEASU_ENERG Accu_Energy;
extern void Prepaid_Proc(MEASU_ENERG* pEnergy);
//�����ڴ��Ƿ�����磬��������POWER_ON���򷵻�RESET
//��鵱ǰ���ϵ绹�Ǹ�λ, ʵ���ϸú������ж��ڴ��е������ڸ�λ���Ƿ��б仯�����Ƿ����˵���֮��
//�ϵ緵��POWER_ON, ��λ����RESET
//�ú������Power_On_Flag.Flag[]�ǲ���ÿ������0x55
INT8U Check_Rst_Flag()
{
  INT8U i, Re;

  static S_Int32U Flag = {CHK_BYTE, 0x55, CHK_BYTE};//0x55��ʾ��һ�ν���ú���, 0xAA��ʾ���ǵ�һ�ν���, ����ֵ��ʾ����, ��¼�Ƿ����ϵ���һ�ν���ú���
  static S_Int32U Power_Flag = {CHK_BYTE, SOFT_RST, CHK_BYTE};//��λ���ϵ��־

  TRACE();
  Re = CHECK_STRUCT_VAR(Flag);
  ASSERT(1 EQ Re);

  if(0x55 EQ Flag.Var)//��һ�ν���ú���
  {
    Flag.Var = 0xAA;//��0xAA���Ժ��ٵ��øú����Ͳ����ٽ����������
    Power_Flag.Var = SOFT_RST;//Ĭ���Ǹ�λ
    for(i = 0; i < S_NUM(Power_On_Flag.Flag); i++)
    {
      if(Power_On_Flag.Flag[i] != 0x55)//��һ������0x55˵�����ϵ�
      {
        Power_Flag.Var = POWER_ON_RST;
        break;
      }
    }
    //Power_Flag EQ RESET����Power_On_Flag��У�����ȷ, ��Ϊ����λ
    if(Power_Flag.Var EQ SOFT_RST && CHECK_STRUCT_SUM(Power_On_Flag))
      Power_Flag.Var = SOFT_RST;
    else
      Power_Flag.Var = POWER_ON_RST;

    //Power_On_Flag.Flag���ó�0x55���´θ�λ���ϵ�ɲ鿴�ñ�־
    mem_set((void *) Power_On_Flag.Flag, 0x55, sizeof(Power_On_Flag.Flag), (void *) Power_On_Flag.Flag, sizeof(Power_On_Flag.Flag));
    SET_STRUCT_SUM(Power_On_Flag);

    return Power_Flag.Var;
  }
  else if(0xAA EQ Flag.Var)//�Ѿ����ǵ�һ�ν���ú���
  {
    Re = CHECK_STRUCT_VAR(Power_Flag);
    ASSERT(1 EQ Re);

    if(Power_Flag.Var EQ SOFT_RST || Power_Flag.Var EQ POWER_ON_RST)
      return Power_Flag.Var;
    else
    {
      ASSERT_FAILED();
      return POWER_ON_RST;
    }
  }
  else
  {
    ASSERT_FAILED();
    return POWER_ON_RST;
  }
}

//�����������ĺϷ���
void Check_Energy_Para_Avil()
{
  INT8U Re;

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Mode_Word);
  Re &= CHECK_STRUCT_SUM(Mode_Word);
  
  Re &= CHECK_STRUCT_VAR(Energy_Comb_Word);
  Re &= CHECK_STRUCT_SUM(Energy_Comb_Word);
  Re &= CHECK_STRUCT_VAR(_Date_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Date_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_VAR(_Year_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Year_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_VAR(_Rate_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Rate_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_VAR(_Step_Scheme_Switch_Time);
  Re &= CHECK_STRUCT_SUM(Step_Scheme_Switch_Time);

  Re &= CHECK_STRUCT_VAR(Multi_Rate_Para);
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);
  Re &= CHECK_STRUCT_VAR(Year_Table);
  Re &= CHECK_STRUCT_SUM(Year_Table);
  Re &= CHECK_STRUCT_VAR(Date_Table);
  Re &= CHECK_STRUCT_SUM(Date_Table);

  Re &= CHECK_STRUCT_SUM(Cur_Scheme);
  Re &= CHECK_STRUCT_VAR(Cur_Scheme);
  
  Re &= CHECK_STRUCT_SUM(Prepaid_Para);
  Re &= CHECK_STRUCT_VAR(Prepaid_Para);
  Re &= CHECK_STRUCT_VAR(Rate_Scheme_Para);
  Re &= CHECK_STRUCT_SUM(Rate_Scheme_Para);
  Re &= CHECK_STRUCT_VAR(Step_Scheme_Para);
  Re &= CHECK_STRUCT_SUM(Step_Scheme_Para);
  
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Read_Energy_Para_From_Rom();
  }//���¶�ȡ��������!!

  //�жϷ�����Ϣͷ����Ҫ�����棬��ΪRead_Energy_Para��������ͷβ
  Re = CHECK_STRUCT_VAR(Cur_Rate_Info);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  Check_Multi_Rate_Para();//��鸴���ʲ����ĺϷ���
  Check_Prepaid_Para();
  Check_Cur_Scheme_Info();
}

//�������������߼��ԣ�������֮
void Check_Energy_Para()
{
	TRACE();
}

//��ȡ��ǰ����
void Read_Cur_Scheme_From_Rom()
{
  INT8U Len;
  //INT8U Temp[5];
  
  TRACE();

  Len = Read_Storage_Data(_SDI_CUR_SCHEME, (void *) &Cur_Scheme, (void *) &Cur_Scheme, sizeof(Cur_Scheme));  
  if(Len EQ 0)
  {
    ASSERT_FAILED();
    //mem_cpy(&Cur_Scheme, Def_Cur_Scheme, sizeof(Def_Cur_Scheme), &Cur_Scheme, sizeof(Cur_Scheme));
  }
  
  INIT_STRUCT_VAR(Cur_Scheme); 
  SET_STRUCT_SUM(Cur_Scheme);
  
  Check_Cur_Scheme_Info();
}


//��ROM�ռ��ж�ȡģʽ��
void Read_Mode_Word()
{

   INT8U i;
   INT16U Len;
   //STORA_DI SDI = SDI_MODEWORD_1;
   
   //��ȡģʽ��1-5
   for(i = 0; i < 5; i++)
   {
     //�����ȡģʽ��ʧ���������Ĭ�ϵ�ģʽ��
     Len = Read_Storage_Data(SDI_MODEWORD_1 + i, (INT8U *)&Mode_Word.Mode[i], (INT8U *) Mode_Word.Mode, sizeof(Mode_Word.Mode));
     ASSERT(1 EQ Len);
   }

  INIT_STRUCT_VAR(Mode_Word);
  SET_STRUCT_SUM(Mode_Word);
  
  Read_Energy_Comb_Word(); //��ȡ���޹����ģʽ��
}

//��ȡ��ʱ�����л�ʱ��
void Read_Year_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //��ȡ��ʱ�����л�ʱ��
  Len = Read_Storage_Data(SDI_YEAR_SCHE_CHG_TIME, (INT8U *) Year_Scheme_Switch_Time.Time, (INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  if(5 != Len)
  {
    ASSERT_FAILED();
    Debug_Print("Read Year_Scheme_Switch_Time Error"); 
    //Ĭ���л�ʱ�̣�ȫ��0xFF
    mem_cpy((INT8U *) Year_Scheme_Switch_Time.Time, (void *) Def_04000106, 5,\
			(INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Year_Scheme_Switch_Time.Time, 5) EQ 1)//ȷʵ��BCDʱ������,���������ȫFF(Ĭ�ϲ���)
  {
    Bcd2Hex_Buf((INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time), (INT8U *) Year_Scheme_Switch_Time.Time, (INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  }
  else //Ĭ���л�ʱ�̣�ȫ��0xFF
  {
    mem_cpy((INT8U *) Year_Scheme_Switch_Time.Time, (void *) Def_04000106, 5,\
			(INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
  }

  INIT_STRUCT_VAR(_Year_Scheme_Switch_Time);
  SET_STRUCT_SUM(Year_Scheme_Switch_Time);
}

//��ȡ��ʱ�α��л�ʱ��
void Read_Date_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //��ȡ������ʱ�α��л�ʱ��
  Len = Read_Storage_Data(SDI_DATE_SCHE_CHG_TIME, (INT8U *) Date_Scheme_Switch_Time.Time, (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  if(5 != Len)//ASSERT(5 EQ Len))
  {
    ASSERT_FAILED();
    Debug_Print("Read Date_Scheme_Switch_Time Error");
    //ʹ��Ĭ�ϵ�������ʱ�α�ʱ��,����0xFF
    mem_cpy((INT8U *) Date_Scheme_Switch_Time.Time, (void *) Def_04000107, 5,\
	    (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Date_Scheme_Switch_Time.Time, 5) EQ 1)//ȷʵ��BCDʱ������, ���������ȫFF(Ĭ�ϲ���)
  {
    Bcd2Hex_Buf((INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time), (INT8U *) Date_Scheme_Switch_Time.Time, \
                (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  }
  else
  {
    mem_cpy((INT8U *) Date_Scheme_Switch_Time.Time, (void *) Def_04000107, 5,\
	    (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
  }

  INIT_STRUCT_VAR(_Date_Scheme_Switch_Time);  
  SET_STRUCT_SUM(Date_Scheme_Switch_Time);
}

//��ȡ���ʷ����л�ʱ��
void Read_Rate_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //��ȡ�������ʷ����л�ʱ��
  Len = Read_Storage_Data(SDI_RATE_SCHE_CHG_TIME, (INT8U *) Rate_Scheme_Switch_Time.Time, (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  if(5 != Len)//ASSERT(5 EQ Len))
  {
    ASSERT_FAILED();
    Debug_Print("Read Rate_Scheme_Switch_Time Error");
    //ʹ��Ĭ�ϵ����������л�ʱ��,����0xFF
    mem_cpy((INT8U *) Rate_Scheme_Switch_Time.Time, (void *) Def_04000108, 5,\
	    (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Rate_Scheme_Switch_Time.Time, 5) EQ 1)//ȷʵ��BCDʱ������, ���������ȫFF(Ĭ�ϲ���)
  {
    Bcd2Hex_Buf((INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time), (INT8U *) Rate_Scheme_Switch_Time.Time, \
                (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  }
  else
  {
    mem_cpy((INT8U *) Rate_Scheme_Switch_Time.Time, (void *) Def_04000108, 5,\
	    (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
  }
  
  INIT_STRUCT_VAR(_Rate_Scheme_Switch_Time);
  SET_STRUCT_SUM(Rate_Scheme_Switch_Time);
}

//��ȡ���ݷ����л�ʱ��
void Read_Step_Scheme_Switch_Time()
{
  INT16U Len;

  TRACE();

  //��ȡ������ʱ�α��л�ʱ��
  Len = Read_Storage_Data(SDI_STEP_SCHE_CHG_TIME, (INT8U *) Step_Scheme_Switch_Time.Time, (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  if(5 != Len)//ASSERT(5 EQ Len))
  {
    ASSERT_FAILED();
    Debug_Print("Read Step_Scheme_Switch_Time Error");
    //ʹ��Ĭ�ϵ����������л�ʱ��,����0xFF
    mem_cpy((INT8U *) Step_Scheme_Switch_Time.Time, (void *) Def_04000109, 5,\
	    (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  }

  if(Check_BCD_Data((INT8U *) Step_Scheme_Switch_Time.Time, 5) EQ 1)//ȷʵ��BCDʱ������, ���������ȫFF(Ĭ�ϲ���)
  {
    Bcd2Hex_Buf((INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time), (INT8U *) Step_Scheme_Switch_Time.Time, \
                (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  }
  else
  {
    mem_cpy((INT8U *) Step_Scheme_Switch_Time.Time, (void *) Def_04000109, 5,\
	    (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
  }
  
  INIT_STRUCT_VAR(_Step_Scheme_Switch_Time);
  SET_STRUCT_SUM(Step_Scheme_Switch_Time);
}

#if SCHEME_SWITCH_MODE == 0
/*
//���㵱ǰӦ��ʹ�õķ��ʷ���, ���Flag EQ CALC_ROM�����´�ROM�ж�ȡ�������㵫ǰ�ķ��ʷ���
//ͬʱ������ʷ����������л��������ڲ������л���صĴ���
// ��ǰӦ�ò��������ʷ����򷵻�YEAR_SCHEME0, ���򷵻�YEAR_SCHEME1
//�ú�������Ҫ�������ж��Ƿ���������л�
//���ʷ����л��Ļ�����Year_Scheme_Changed_Proc������ش���
INT8U Calc_Cur_Year_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  if(CALC_ROM EQ Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    Read_Multi_Rate_Para(); //�ȶ�ȡ������ز��� 
    Read_Year_Scheme_Switch_Time();
  }

  //����ڴ�����ر�������ȷ��
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//���Cur_Time0ʱ��
  Re &= CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re &= CHECK_STRUCT_SUM(Year_Scheme_Switch_Time);//�������л�ʱ��
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(YEAR_TABLE_SWITCH_EN EQ 1)//�Ƿ������л����ʷ���?
  {
    if(_Check_HEX_Time((INT8U *) Year_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Year_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re != TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
        Scheme = YEAR_SCHEME1;//��ǰӦ���ø����ʷ���
      else
        Scheme = YEAR_SCHEME0;
    }
    else//�����������£�Ĭ��ʹ���׷��ʷ���0
    {
      Scheme = YEAR_SCHEME0;
    }
  }
  else
    Scheme = YEAR_SCHEME0; 

  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�, �������
  if(Cur_Rate_Info.Year_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Year_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Year_Scheme_Changed_Proc();//��ʱ�������л�����
    
    Calc_Cur_Date_Scheme(CALC_ROM);
    
    if(Cur_Scheme.Year_Scheme != Scheme)
    {
      Debug_Print("Cur_Year_Scheme Changed!");
      Cur_Scheme.Year_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_YEAR_TABLE_SWITCH_FREEZE, EVENT_OCCUR);      
    }
  }
  return Scheme;
}

//���㵱ǰ��ʱ�α���
//Flag EQ CALC_ROM��ʾ��ROM�ж�ȡ����ǿ���ж�һ�ε�ǰ�׷���
//Flag EQ CALC_RAM��ʾʹ���ڴ��в�������һ���жϵ�ǰ����
INT8U Calc_Cur_Date_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //��ȡ������ʱ�α��л�ʱ��
  if(CALC_ROM EQ Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    Read_Date_Scheme_Switch_Time();
  }

  //����ڴ�����ر�������ȷ��
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//���Cur_Time0ʱ��
  Re &= CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re &= CHECK_STRUCT_SUM(Date_Scheme_Switch_Time);//���������ʱ�α��л�ʱ��
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(DATE_TABLE_SWITCH_EN EQ 1)//�Ƿ������л���ʱ�α���?
  {
    if(_Check_HEX_Time((INT8U *) Date_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Date_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re != TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
        Scheme = DATE_SCHEME1;//��ǰӦ���ø����ʷ���
      else
        Scheme = DATE_SCHEME0;
    }
    else//�����������£�Ĭ��ʹ���׷��ʷ���0
    {
      Scheme = DATE_SCHEME0;
    }
  }
  else
    Scheme = DATE_SCHEME0;

  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�, �������
  if(Cur_Rate_Info.Date_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Date_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Date_Scheme_Changed_Proc();//���ʷ����л�����
    
    if(Cur_Scheme.Date_Scheme != Scheme)
    {
      Debug_Print("Cur_Date_Scheme Changed!");
      Cur_Scheme.Date_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_DATE_TABLE_SWITCH_FREEZE, EVENT_OCCUR);      
    }
  }
  return Scheme;
}
*/
#else
//���㵱ǰӦ��ʹ�õķ��ʷ���, ���Flag EQ CALC_ROM�����´�ROM�ж�ȡ�������㵫ǰ�ķ��ʷ���
//ͬʱ������ʷ����������л��������ڲ������л���صĴ���
// ��ǰӦ�ò��������ʷ����򷵻�YEAR_SCHEME0, ���򷵻�YEAR_SCHEME1
//�ú�������Ҫ�������ж��Ƿ���������л�
//���ʷ����л��Ļ�����Year_Scheme_Changed_Proc������ش���
INT8U Calc_Cur_Year_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  if(CALC_ROM EQ Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    Read_Year_Scheme_Switch_Time(); //��ȡ��ʱ���л�ʱ��
  }

  //����ڴ�����ر�������ȷ��
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//���Cur_Time0ʱ��
  Re &= CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re &= CHECK_STRUCT_SUM(Year_Scheme_Switch_Time);//�������л�ʱ��
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Year_Scheme;
  
  if(YEAR_TABLE_SWITCH_EN EQ 1)//�Ƿ������л���ʱ������?
  {
    if(_Check_HEX_Time((INT8U *) Year_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Year_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re != TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
      {
        if(Cur_Scheme.Year_Scheme_Time EQ BEF_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ����ǰ,����뷢��һ���л�
        {
          if(Cur_Scheme.Year_Scheme EQ YEAR_SCHEME1)
            Scheme = YEAR_SCHEME0;
          else
            Scheme = YEAR_SCHEME1;
          
          Cur_Scheme.Year_Scheme_Time = AFT_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //����ʱ���л�ʱ����0
          mem_set((INT8U *) Year_Scheme_Switch_Time.Time, 0, sizeof(Year_Scheme_Switch_Time.Time),\
                  (INT8U *) Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Year_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_YEAR_SCHE_CHG_TIME, (INT8U *)Year_Scheme_Switch_Time.Time, sizeof(Year_Scheme_Switch_Time.Time));          
        }
      }
      else
      {
        //�л�ʱ����ǰ��?
        if(Cur_Scheme.Year_Scheme_Time EQ AFT_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ���Ժ�,����뷢��һ���л�
        {  
          Cur_Scheme.Year_Scheme_Time = BEF_SWITCH_TIME;//��ǰ���л�ʱ����ǰ��
          SET_STRUCT_SUM(Cur_Scheme); 
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
        }       
      }
    }
  }

  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�, �������
  if(Cur_Rate_Info.Year_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Year_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Year_Scheme_Changed_Proc();//��ʱ�������л�����
    
    Calc_Cur_Date_Scheme(CALC_ROM);
    
    if(Cur_Scheme.Year_Scheme != Scheme)
    {
      Debug_Print("Cur_Year_Scheme Changed!");
      Cur_Scheme.Year_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_YEAR_TABLE_SWITCH_FREEZE, EVENT_OCCUR);      
    }    
  }
  return Scheme;
}

//���㵱ǰ��ʱ�α���
//Flag EQ CALC_ROM��ʾ��ROM�ж�ȡ����ǿ���ж�һ�ε�ǰ�׷���
//Flag EQ CALC_RAM��ʾʹ���ڴ��в�������һ���жϵ�ǰ����
INT8U Calc_Cur_Date_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //��ȡ������ʱ�α��л�ʱ��
  if(CALC_ROM EQ Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    Read_Date_Scheme_Switch_Time();
  }

  //����ڴ�����ر�������ȷ��
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//���Cur_Time0ʱ��
  Re &= CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re &= CHECK_STRUCT_SUM(Date_Scheme_Switch_Time);//���������ʱ�α��л�ʱ��
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Date_Scheme;
  
  if(DATE_TABLE_SWITCH_EN EQ 1)//�Ƿ������л���ʱ�α���?
  {
    if(_Check_HEX_Time((INT8U *) Date_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Date_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re != TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
      {
        if(Cur_Scheme.Date_Scheme_Time EQ BEF_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ����ǰ,����뷢��һ���л�
        {
          if(Cur_Scheme.Date_Scheme EQ DATE_SCHEME1)
            Scheme = DATE_SCHEME0;
          else
            Scheme = DATE_SCHEME1;
          
          Cur_Scheme.Date_Scheme_Time = AFT_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //����ʱ�α��л�ʱ����0
          mem_set((INT8U *) Date_Scheme_Switch_Time.Time, 0, sizeof(Date_Scheme_Switch_Time.Time),\
                  (INT8U *) Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Date_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_DATE_SCHE_CHG_TIME, (INT8U *)Date_Scheme_Switch_Time.Time, sizeof(Date_Scheme_Switch_Time.Time));
        }
      }
      else
      {
        //�л�ʱ����ǰ��?
        if(Cur_Scheme.Date_Scheme_Time EQ AFT_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ���Ժ�,����뷢��һ���л�
        {
          Cur_Scheme.Date_Scheme_Time = BEF_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));         
        }      
      }
    }
  }

  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�, �������
  if(Cur_Rate_Info.Date_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Date_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Date_Scheme_Changed_Proc();//���ʷ����л�����
    
    if(Cur_Scheme.Date_Scheme != Scheme)
    {
      Debug_Print("Cur_Date_Scheme Changed!");
      Cur_Scheme.Date_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_DATE_TABLE_SWITCH_FREEZE, EVENT_OCCUR);
    }
  }
  return Scheme;
}

//���㵱ǰ���ʷ���
INT8U Calc_Cur_Rate_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //��ȡ������ʱ�α��л�ʱ��
  if(CALC_ROM EQ Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    Read_Rate_Scheme_Switch_Time();
  }

  //����ڴ�����ر�������ȷ��
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//���Cur_Time0ʱ��
  Re &= CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re &= CHECK_STRUCT_SUM(Rate_Scheme_Switch_Time);//���������ʱ�α��л�ʱ��
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Rate_Scheme;
  
  if(RATE_SCH_SWITCH_EN EQ 1)//�Ƿ������л���ʱ�α���?
  {
    if(_Check_HEX_Time((INT8U *) Rate_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Rate_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re != TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
      {
        if(Cur_Scheme.Rate_Scheme_Time EQ BEF_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ����ǰ,����뷢��һ���л�
        {
          if(Cur_Scheme.Rate_Scheme EQ RATE_SCHEME1)
            Scheme = RATE_SCHEME0;
          else
            Scheme = RATE_SCHEME1;
          
          Cur_Scheme.Rate_Scheme_Time = AFT_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //�����ʷ����л�ʱ����0
          mem_set((INT8U *) Rate_Scheme_Switch_Time.Time, 0, sizeof(Rate_Scheme_Switch_Time.Time),\
                  (INT8U *) Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Rate_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_RATE_SCHE_CHG_TIME, (INT8U *)Rate_Scheme_Switch_Time.Time, sizeof(Rate_Scheme_Switch_Time.Time));
          
        }
      }
      else
      {
        //�л�ʱ����ǰ��?
        if(Cur_Scheme.Rate_Scheme_Time EQ AFT_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ���Ժ�,����뷢��һ���л�
        {
          Cur_Scheme.Rate_Scheme_Time = BEF_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));          
        }      
      }
    }
  }

  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�, �������
  if(Cur_Rate_Info.Rate_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Rate_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Rate_Scheme_Changed_Proc();//���ʷ����л�����
    
    if(Cur_Scheme.Rate_Scheme != Scheme)
    {
      Debug_Print("Cur_Rate_Scheme Changed!");
      Cur_Scheme.Rate_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_RATE_SCH_SWITCH_FREEZE, EVENT_OCCUR);      
    }
  }
  return Scheme; 
}

//���㵱ǰ���ݷ���
INT8U Calc_Cur_Step_Scheme(INT8U Flag)
{
  INT8U Re, Scheme;

  TRACE();

  //��ȡ�������ݷ����л�ʱ��
  if(CALC_ROM EQ Flag)//��ʾ��ROM�����¶�ȡ������ݣ����м���
  {
    Read_Step_Scheme_Switch_Time();
  }

  //����ڴ�����ر�������ȷ��
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *) &Cur_Time0);//���Cur_Time0ʱ��
  Re &= CHECK_STRUCT_SUM(Mode_Word);//���ģʽ���Ƿ���������л�
  Re &= CHECK_STRUCT_SUM(Step_Scheme_Switch_Time);//������׽����л�ʱ��
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��鵱ǰ������Ϣ
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Scheme = Cur_Scheme.Step_Scheme;
  
  if(STEP_SCH_SWITCH_EN EQ 1)//�Ƿ������л���ʱ�α���?
  {
    if(_Check_HEX_Time((INT8U *) Step_Scheme_Switch_Time.Time))
    {
      Re = Cmp_Time((S_HEX_Time *) &Cur_Time0, (S_HEX_Time *) &Step_Scheme_Switch_Time);//��ǰʱ���Ƿ��ڷ����л�ʱ��֮��?
      if(Re != TIME_BEF)//��ǰʱ���ڷ��ʷ����л�ʱ��֮��
      {
        if(Cur_Scheme.Step_Scheme_Time EQ BEF_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ����ǰ,����뷢��һ���л�
        {
          if(Cur_Scheme.Step_Scheme EQ STEP_SCHEME1)
            Scheme = STEP_SCHEME0;
          else
            Scheme = STEP_SCHEME1;
          
          Cur_Scheme.Step_Scheme_Time = AFT_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
          
          //���ݷ����л�ʱ����0
          mem_set((INT8U *) Step_Scheme_Switch_Time.Time, 0, sizeof(Step_Scheme_Switch_Time.Time),\
                  (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
          SET_STRUCT_SUM(Step_Scheme_Switch_Time);
          
          Write_Storage_Data(SDI_STEP_SCHE_CHG_TIME, (INT8U *) Step_Scheme_Switch_Time.Time, sizeof(Step_Scheme_Switch_Time.Time));
        }
      }
      else
      {
        //�л�ʱ����ǰ��?
        if(Cur_Scheme.Step_Scheme_Time EQ AFT_SWITCH_TIME)//ǰһ�ε��ж�ʱ�����л�ʱ���Ժ�,����뷢��һ���л�
        {
          Cur_Scheme.Step_Scheme_Time = BEF_SWITCH_TIME;//��ǰ���л�ʱ���Ժ���
          SET_STRUCT_SUM(Cur_Scheme);
          Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));          
        }      
      }
    }
  }

  //�͵�ǰʹ�õķ��ʷ�����һ�£�Ӧ���л����ʷ���
  //ʹ��ROM�в���������ʷ���ʱ��ǿ����Ϊ������һ�η����л�, �������
  if(Cur_Rate_Info.Step_Scheme != Scheme || CALC_ROM EQ Flag)
  {
    Cur_Rate_Info.Step_Scheme = Scheme;
    SET_STRUCT_SUM(Cur_Rate_Info); 
    Step_Scheme_Changed_Proc();//���ʷ����л�����
    
    if(Cur_Scheme.Step_Scheme != Scheme)
    {
      Debug_Print("Cur_Step_Scheme Changed!");
      Cur_Scheme.Step_Scheme = Scheme;
      SET_STRUCT_SUM(Cur_Scheme);
      Write_Storage_Data(_SDI_CUR_SCHEME, (void *)&Cur_Scheme, sizeof(Cur_Scheme));
      Event_Data_Proc(ID_EVENT_STEP_SCH_SWITCH_FREEZE, EVENT_OCCUR);
    }
  }
  return Scheme; 
}
#endif

extern CONST S_Cur_Scheme Def_SDI_CUR_SCHEME;

void Check_Cur_Scheme_Info()
{
  if((Cur_Scheme.Year_Scheme != YEAR_SCHEME0 && Cur_Scheme.Year_Scheme != YEAR_SCHEME1) ||\
     (Cur_Scheme.Date_Scheme != DATE_SCHEME0 && Cur_Scheme.Date_Scheme != DATE_SCHEME1) ||\
     (Cur_Scheme.Rate_Scheme != RATE_SCHEME0 && Cur_Scheme.Rate_Scheme != RATE_SCHEME1) ||\
     (Cur_Scheme.Step_Scheme != STEP_SCHEME0 && Cur_Scheme.Step_Scheme != STEP_SCHEME1) ||\
     (Cur_Scheme.Year_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Year_Scheme_Time != AFT_SWITCH_TIME) ||\
     (Cur_Scheme.Date_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Date_Scheme_Time != AFT_SWITCH_TIME) ||\
     (Cur_Scheme.Rate_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Rate_Scheme_Time != AFT_SWITCH_TIME) ||\
     (Cur_Scheme.Step_Scheme_Time != BEF_SWITCH_TIME && Cur_Scheme.Step_Scheme_Time != AFT_SWITCH_TIME))  
  {
    ASSERT_FAILED();
    mem_cpy((INT8U *)&Cur_Scheme, (INT8U *) &Def_SDI_CUR_SCHEME, sizeof(S_Cur_Scheme),\
            (INT8U *)&Cur_Scheme, sizeof(Cur_Scheme));
    INIT_STRUCT_VAR(Cur_Scheme);
    SET_STRUCT_SUM(Cur_Scheme); 
    Write_Storage_Data(_SDI_CUR_SCHEME, (void *) &Cur_Scheme, sizeof(Cur_Scheme));
  }
  
}

/*
typedef struct
{
  INT8U Year_Period; //��ʱ����
  INT8U Date_Table;  //��ʱ�α���
  INT8U Date_Period; //��ʱ����
  INT8U Rates;    //������
  INT8U Holidays; //�ڼ�����
  INT8U WeekRest_DataTable;//������ʹ�õ�ʱ�α��
  INT8U WeekRest_Status;  //������״̬��
  
  INT8U CS[CS_BYTES];
}S_Multi_Rate_Para;//�����ʲ���
*/

//��鸴���ʲ���
void Check_Multi_Rate_Para()
{
  TRACE();

  //������
  if(!(Multi_Rate_Para.Rates <= MAX_RATES && Multi_Rate_Para.Rates >0))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Rates = 4;
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //��ʱ����
  if(!(Multi_Rate_Para.Year_Period <= MAX_YEAR_PERIODS && Multi_Rate_Para.Year_Period > 0))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Year_Period = 1; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //��ʱ�α���
  if(!(Multi_Rate_Para.Date_Table <= MAX_DATE_TABLES && Multi_Rate_Para.Date_Table > 0))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Date_Table = 1; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //��ʱ����
  if(!(Multi_Rate_Para.Date_Period <= MAX_DATE_PERIODS))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Date_Period = 4; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
  //�ڼ�����
  if(!(Multi_Rate_Para.Holidays <= MAX_YEAR_HOLIDAYS))
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Holidays = 0; 
    SET_STRUCT_SUM(Multi_Rate_Para);
  }
}

//���Ԥ���Ѳ����Ϸ���
void Check_Prepaid_Para()
{
  TRACE();

  if(Prepaid_Para.Step_Num > PREPAID_MAX_STEP)
  {
    ASSERT_FAILED();
    Prepaid_Para.Step_Num = PREPAID_MAX_STEP;
    SET_STRUCT_SUM(Prepaid_Para);
  }
  
  if(Prepaid_Para.PT_Ratio EQ 0)
  {
    Prepaid_Para.PT_Ratio = 1;
    SET_STRUCT_SUM(Prepaid_Para);
  }
  
  if(Prepaid_Para.CT_Ratio EQ 0)
  {
    Prepaid_Para.CT_Ratio = 1;
    SET_STRUCT_SUM(Prepaid_Para);
  }
}

//��ȡ��������ز���
void Read_Multi_Rate_Para()
{
  INT16U Len;
  
  //�׷��ʷ�������
  Len = S_OFF(S_Multi_Rate_Para, WeekRest_DataTable);
  Read_Multi_Storage_Data(SDI_YEAR_PERIOD_NUM, 6, (void *) &Multi_Rate_Para.Year_Period, (void *) &Multi_Rate_Para, Len);

  if(Read_Storage_Data(SDI_WEEK_REST_DAY, (void *) &Multi_Rate_Para.WeekRest_Status, (void *) &Multi_Rate_Para.WeekRest_Status, 1) != 1)
    ASSERT_FAILED();

  if(Read_Storage_Data(SDI_WEEK_REST_DATE_TABLE, (void *) &Multi_Rate_Para.WeekRest_DataTable, (void *) &Multi_Rate_Para.WeekRest_DataTable, 1) != 1)
    ASSERT_FAILED();
  
  Len = S_OFF(S_Multi_Rate_Para, WeekRest_Status);//������״̬��ǰ������ҪBCD->HEX
  Bcd2Hex_Buf((void *) &Multi_Rate_Para, S_OFF(S_Multi_Rate_Para, WeekRest_Status), (void *) &Multi_Rate_Para, (void *) &Multi_Rate_Para, sizeof(Multi_Rate_Para));
  
  INIT_STRUCT_VAR(Multi_Rate_Para);
  SET_STRUCT_SUM(Multi_Rate_Para);

  Check_Multi_Rate_Para();//��鸴���ʲ����ĺϷ���  
  
}

//��ȡ�������ز���
//Year_Scheme��ʾ���ʷ�����, ΪYEAR_SCHEME0����YEAR_SCHEME1
void Read_Year_Table_Para(INT8U Year_Scheme)
{
  INT16U Len;
  PROTO_DI SDI;

  TRACE();

  if(!(YEAR_SCHEME0 EQ Year_Scheme || YEAR_SCHEME1 EQ Year_Scheme))
  {
    ASSERT_FAILED();
    Year_Scheme = YEAR_SCHEME0;
  }
  
  if(YEAR_SCHEME0 EQ Year_Scheme)//ʹ�õ�һ�׷��ʷ���
  {
    SDI = SDI_SCHE1_YEAR_TABLE;
  }
  else//�ڶ���
  {
    SDI = SDI_SCHE2_YEAR_TABLE;
  }

  //��ȡ��ʱ�������
  if(Read_Storage_Data(SDI, (void *) Year_Table.MDN, (void *) Year_Table.MDN, sizeof(Year_Table.MDN)) != MAX_YEAR_PERIODS * 3)
	ASSERT_FAILED();

  Len = S_OFF(S_Year_Table, CS);
  Bcd2Hex_Buf((void *) &Year_Table, Len, (void *) &Year_Table, (void *) &Year_Table, Len);
  
  INIT_STRUCT_VAR(Year_Table);
  SET_STRUCT_SUM(Year_Table);
}

//���ڼ�������ʱ���ʱ�������, ��ʱ��ʱ���, ���ؽ��Ϊ����
//���ڼ�����ʱ�����������ʱ���, Time0-Time1���ú�����������ʱ������Ѱ�ҵ�ǰʱ���ʱ��
//���Time0��ʡ��Time1֮ǰ����ô�����Time0+12*31-Time1
//Time0[0]��ʾ��, Time0[1]��ʾ��, Time1��ʾ������Time0��ͬ
INT16U Year_Period_Dec(INT8U Time0[], INT8U Time1[])
{
  INT16U Days[2];

  TRACE();

  ASSERT((Time0[0] < 32 && Time0[0] > 0 && Time0[1] < 13 && Time0[1] > 0) &&\
	     (Time1[0] < 32 && Time1[0] > 0 && Time1[1] < 13 && Time1[1] > 0));//�ж����������ĸ�ʽ

  Days[0] = (INT16U) (Time0[1]) * 31 + (INT16U) (Time0[0]);
  Days[1] = (INT16U) (Time1[1]) * 31 + (INT16U) (Time1[0]);

  if(Days[0] < Days[1])
  {
    return Days[0] + 12 * 31 - Days[1];
  }
  else
  {
    return Days[0] - Days[1];
  }
}

//��ʱ��ʱ���, ����Ϊ������
//���ڼ�����ʱ�α��������ʱ���, Time0-Time1, ���Time0��Time1֮ǰ����ô�����
//Time0+24*60-Time1
//Time0[0]��ʾ�֣�Time0[1]��ʾʱ��Time1��ʾ������Time0��ͬ
INT16U Date_Period_Dec(INT8U Time0[], INT8U Time1[])
{
  INT16U Mins[2];

  TRACE();

  //��ʱ���ݱ���Ϸ�
  ASSERT((Time0[0] < 60 && Time0[1] < 24) && (Time1[0] < 60 && Time1[1] < 24));//�ж����������ĸ�ʽ

  Mins[0] = (INT16U) (Time0[1]) * 60 + (INT16U) (Time0[0]);
  Mins[1] = (INT16U) (Time1[1]) * 60 + (INT16U) (Time1[0]);

  if(Mins[0] < Mins[1])
  {
    return Mins[0] + 24 * 60 - Mins[1];
  }
  else
  {
    return Mins[0] - Mins[1];
  }
}

//��鵱ǰ�Ƿ��ǽڼ���
//�ú�����Ҫ���ڴ��ж����ڼ��ձ����бȽ�, һ��ÿ�յ��øú���һ��
//����0��ʾ���ǽڼ��գ�����>0��ʾ�ǽڼ��գ�ͬʱ����ֵ�����ǵڶ��ٸ��ڼ��գ�*pDate_Table_Index������ʱ�α��
INT8U Check_Today_Holiday(INT8U* pDate_Table_Index)
{
  INT8U Num, Re, i;
  INT16U Len;
  INT8U Temp[10];

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(Multi_Rate_Para.Holidays > MAX_YEAR_HOLIDAYS)
  {
    ASSERT_FAILED();
    Multi_Rate_Para.Holidays = MAX_YEAR_HOLIDAYS;
    SET_STRUCT_SUM(Multi_Rate_Para);
  }

  Num = Multi_Rate_Para.Holidays;

  for(i = 0; i < Num; i ++)
  {
    Len = Read_Storage_Data(0x04030001 + i, Temp, Temp, sizeof(Temp));
    if(Len EQ 4)
    {
      Bcd2Hex_Buf(Temp, Len, Temp, Temp, sizeof(Temp));
      if(Cur_Time0.Time[T_MONTH] EQ Temp[2] && \
         Cur_Time0.Time[T_DATE] EQ Temp[1])
      {
        *pDate_Table_Index = Temp[0];//�ڼ��ղ��õ���ʱ�α��
        return i + 1;
      }
    }
  }
  return 0;
}

//���㵱ǰӦ��ʹ�õ���ʱ�α��, ���Flag EQ CALC_ROM��ǿ���ж�һ�ε�ǰ����ʱ�α��
//�����ʱ�α�ű仯�ˣ�����ǰ��ʱ�α����Date_Table��
INT8U Cal_Cur_Date_Table(INT8U Flag)
{
  INT8U i, Re;//Data_IndexΪʹ�õ���ʱ�α������
  INT8U Date_Table_Flag;//1��ʾ�ҵ���ʱ�α��
  INT16U Min = 0xFFFF;//��Сֵ, ����һ������ֵ
  INT16U Dec;//��
  static S_HEX_Time Last_Chk_Time = {{0, 0, 0, 0, 0}, 0, {0 ^ ((INT8U) CHK_CS_BYTES)}};
  static S_Int8U Date_Table_Index = {CHK_BYTE, 1, CHK_BYTE};

  TRACE();

  //�ڵ�ǰ�ڼ����в����Ƿ��ǽڼ���?
  //ʱ�䷢���˱仯������Flag��־ΪCALC_ROM��ʾǿ���ж�һ��
  //ÿ��ֻ�����������һ��, ����CALC_ROM EQ Flagʱ���������
  Re = CHECK_STRUCT_SUM(Last_Chk_Time);
  if(Last_Chk_Time.Time[T_DATE] != Cur_Time0.Time[T_DATE] || \
     Last_Chk_Time.Time[T_MONTH] != Cur_Time0.Time[T_MONTH] || \
     Last_Chk_Time.Time[T_YEAR] != Cur_Time0.Time[T_YEAR] || \
     CALC_ROM EQ Flag)//���ջ���CALC_ROM����������жϵ����Ƿ�ڼ���, ÿ��ֻ��һ�Σ�����CALC_ROM��������ж�
  {
    Re = 1;
    Re &= CHECK_STRUCT_SUM(Cur_Time0);//��ǰʱ��
    Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);//��ǰ�����ʲ���
    Re &= CHECK_STRUCT_SUM(Year_Table);//��ʱ����
    Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��ǰ������Ϣ

    if(1 != Re)//ASSERT(0 != Re))
    {
      ASSERT_FAILED();
      Check_Data_Avail();
    }
    
    Date_Table_Flag = 0;

    //���ǵ���ʱ�䣬������жϱ�֤ÿ��ֻ����ú���һ��
    mem_cpy(&Last_Chk_Time, (void *) &Cur_Time0, sizeof(Cur_Time0), &Last_Chk_Time, sizeof(Last_Chk_Time));

    //���жϵ�ǰ�Ƿ��ǽڼ���
    Re = Check_Today_Holiday(&Date_Table_Index.Var);//����>0��ʶ��ʾ�ǽڼ���
    if(Re > 0)//
    {
      Date_Table_Flag = 1;// EQ 1��ʾ�ҵ���ʱ�α���������
      Cur_Rate_Info.Date_Flag = HOLIDAY;
      Cur_Rate_Info.Holiday_Index = Re;
    }

    //���ǹ������գ��Ƿ���������?
    if(0 EQ Date_Table_Flag)
    {
      if(GET_BIT(Multi_Rate_Para.WeekRest_Status, Cur_Time0.Week) EQ 0)//Ϊ0��ʾ������������
      {
        Date_Table_Index.Var = Multi_Rate_Para.WeekRest_DataTable;//��������ʱ�α��
        Date_Table_Flag = 1;// EQ 1��ʾ�ҵ���ʱ�α���������    
        Cur_Rate_Info.Date_Flag = WEEK_REST_DAY;
      }
    }

    //���ǹ������գ�Ҳ���������գ�����ʱ�����в���
    if(0 EQ Date_Table_Flag)
    {
      Cur_Rate_Info.Date_Flag = NORMAL_DAY;//����һ��ƽ�������ӣ��Ȳ��ǽڼ��գ�Ҳ����������
      for(i = 0; i < Multi_Rate_Para.Year_Period && i < MAX_YEAR_PERIODS; i++)
      {
        //�ա���������ȷ
        if(Year_Table.MDN[i][1] >= 1 && Year_Table.MDN[i][1] <= 31 &&\
           Year_Table.MDN[i][2] >= 1 && Year_Table.MDN[i][2] <= 12)
        {
          Dec = Year_Period_Dec((INT8U *) &Cur_Time0.Time[T_DATE], (INT8U *) &Year_Table.MDN[i][1]);//���㵱ǰʱ�����ʱ������ĳ��ʱ���ʱ���
          if(Dec < Min)//Ѱ��ʱ�����С��һ����Ϊ�ǵ�ǰ��ʱ��
          {
            Date_Table_Index.Var = Year_Table.MDN[i][0];//��ʱ�α�����
            Date_Table_Flag = 1;
            Cur_Rate_Info.Year_Period = i + 1;//��ʱ����
            Min = Dec;
          }
        }
      }
    }

    //û�еõ����ʵ���ʱ�α�ţ������1ʱ�α�
    if(!(1 EQ Date_Table_Flag && \
      Date_Table_Index.Var > 0 && \
      Date_Table_Index.Var <= Multi_Rate_Para.Date_Table && \
      Date_Table_Index.Var <= MAX_DATE_TABLES))
    {
      ASSERT_FAILED();
      Date_Table_Index.Var = 1;
    }
    
    //�ж�ʱ�α���Ƿ����仯, �仯�������¶�ȡʱ�α����, ����ǿ����Ϊ��ʱ�η����˱仯�Ļ�Ҳ���¶�ȡ
    if(Cur_Rate_Info.Date_Table != Date_Table_Index.Var || CALC_ROM EQ Flag)//��ǰʱ�α�ŷ����仯��
    {
      Debug_Print("Date Table Changed, %d-->%d", Cur_Rate_Info.Date_Table, Date_Table_Index.Var);
      Cur_Rate_Info.Date_Table = Date_Table_Index.Var;//��ʱ�α�������
      SET_STRUCT_SUM(Cur_Rate_Info);    
      Read_Date_Table_Para(Cur_Rate_Info.Date_Scheme, Date_Table_Index.Var);//��ȡ��ǰʱ�α������Date_Table�� 
    }
  }
  return Cur_Rate_Info.Date_Table;//Date_Table_Index;
}

//��ȡDate_Scheme����ʱ�α�����Date_Table_Index��ʱ�α�Date_Table�ṹ�������
void Read_Date_Table_Para(INT8U Date_Scheme, INT8U Date_Table_Index)
{
  INT8U Re;
  INT16U Len;

  TRACE();

  Re = CHECK_STRUCT_SUM(Date_Table);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(DATE_SCHEME0 != Date_Scheme && DATE_SCHEME1 != Date_Scheme)
  {
    ASSERT_FAILED();
    Date_Scheme = DATE_SCHEME0;
  }

  if(Date_Table_Index EQ 0 || Date_Table_Index > MAX_DATE_TABLES)
  {
    ASSERT_FAILED();
    Date_Table_Index = 1;
  }

  Len = 0;
  if(Date_Scheme EQ DATE_SCHEME0)
  {
    Len = Read_Storage_Data(SDI_SCHE1_DATE_TABLE1 + (Date_Table_Index - 1), (INT8U *) Date_Table.HMN, (INT8U *) Date_Table.HMN, sizeof(Date_Table.HMN));
  }
  else
  {
    Len = Read_Storage_Data(SDI_SCHE2_DATE_TABLE1 + (Date_Table_Index - 1), (INT8U *) Date_Table.HMN, (INT8U *) Date_Table.HMN, sizeof(Date_Table.HMN));
  }

  //��ʱ�α�����ת��Ϊhex��
  Bcd2Hex_Buf((void *) &Date_Table, S_OFF(S_Date_Table, CS), (void *) &Date_Table, (void *) &Date_Table, S_OFF(S_Date_Table, CS));
  if(MAX_DATE_PERIODS * 3 != Len)
  {
    ASSERT_FAILED();
  }

  INIT_STRUCT_VAR(Date_Table);
  SET_STRUCT_SUM(Date_Table);
}

//��ȡ���ʷ�������,Scheme��ʾ���ʷ���
void Read_Rate_Scheme_Para(INT8U Scheme)
{
  STORA_DI SDI;
  INT8U Re;
  INT8U i;
  
  if(Scheme EQ RATE_SCHEME0)
    SDI = SDI_RATE_SCHEME0_0;
  else if(Scheme EQ RATE_SCHEME1)
    SDI = SDI_RATE_SCHEME1_0;
  else
    ASSERT_FAILED();
  
  Re = CHECK_STRUCT_SUM(Multi_Rate_Para);
  if(Re EQ 0)
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
  
  for(i = 0; i < MAX_RATES ; i++)
  {
    Read_Storage_Data(SDI + i, (INT8U *)&Rate_Scheme_Para.Fee[i], (INT8U *)&Rate_Scheme_Para, sizeof(Rate_Scheme_Para)); 
    Rate_Scheme_Para.Fee[i] = Bcd2Hex((INT8U *)&Rate_Scheme_Para.Fee[i], 4);
  }
  
  INIT_STRUCT_VAR(Rate_Scheme_Para);
  SET_STRUCT_SUM(Rate_Scheme_Para);
}

//��ȡ���ݵ�۷���
void Read_Step_Scheme_Para(INT8U Scheme)
{
  STORA_DI SDI0,SDI1;
  INT8U i;
  
  if(Scheme EQ STEP_SCHEME0)
  {
    SDI0 = SDI_STEP_SCHEME0_ENG;
    SDI1 = SDI_STEP_SCHEME0_MONEY;
  }
  else if(Scheme EQ STEP_SCHEME1)
  {
    SDI0 = SDI_STEP_SCHEME1_ENG;
    SDI1 = SDI_STEP_SCHEME1_MONEY;
  }
  else
    ASSERT_FAILED();
  
  //��ȡ������
  
  for(i = 0; i <PREPAID_MAX_STEP ; i++)
  {
    Read_Storage_Data(SDI0 + i, (INT8U *)&Step_Scheme_Para.Step_Energy[i], (INT8U *)&Step_Scheme_Para, sizeof(Step_Scheme_Para)); 
    Step_Scheme_Para.Step_Energy[i] = Bcd2Hex((INT8U *)&Step_Scheme_Para.Step_Energy[i], 4);
  }
  
  for(i = 0; i <PREPAID_MAX_STEP + 1; i++)
  {
    Read_Storage_Data(SDI1 + i, (INT8U *)&Step_Scheme_Para.Step_Fee[i], (INT8U *)&Step_Scheme_Para, sizeof(Step_Scheme_Para)); 
    Step_Scheme_Para.Step_Fee[i] = Bcd2Hex((INT8U *)&Step_Scheme_Para.Step_Fee[i], 4);
  }  
  
  INIT_STRUCT_VAR(Step_Scheme_Para);
  SET_STRUCT_SUM(Step_Scheme_Para);  
  
}

//���㵱ǰӦ��ʹ�õķ��ʱ��
//��Ҫ�Ǵӵ�ǰ��ʱ�α����ҵ���ǰ���ʺ�
INT8U Calc_Cur_Rate(INT8U Flag)
{
  INT8U Rate, Re;//Data_IndexΪʹ�õ���ʱ�α������
  INT16U Min = 0xFFFF, i;
  INT16U Dec;
  INT8U Period;//��ʱ�κ�

  TRACE();

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Time0);
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);

  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }//������ݵ���Ч��

  Period = Cur_Rate_Info.Date_Period;
  //�����ʱ�α�ŷ����仯�������¶�ȡ��Date_Table������
  //�׷��ʷ��������仯��ʱ�򣬻�ǿ���л�Date_Table
  //ƽʱ������ʵ�ʱ��ֻ��ÿ�����һ��Date_Table
  Cal_Cur_Date_Table(CALC_RAM);
  //�˴�û����Flag������CALC_RAM����Ϊ��Flag EQ CACL_ROMʱ��֮ǰ�϶�������Calc_Cur_Year_Scheme(CACL_ROM)���������Ѿ�����ʱ�α�����˴���

  //����ʱ�α����ҵ�ǰ����
  Rate = 0;
  Min = 0xFFFF;//��һ������ֵ
  for(i = 0; i < Multi_Rate_Para.Date_Period && i < MAX_DATE_PERIODS; i++)
  {
    if(Date_Table.HMN[i][1] < 60 && Date_Table.HMN[i][2] < 24)//ʱ�����ݱ�����ȷ�Ų������
    {
      Dec = Date_Period_Dec((INT8U *) &Cur_Time0.Time[T_MIN], (INT8U *) &Date_Table.HMN[i][1]);
      if(Dec < Min)
      {
        Rate = Date_Table.HMN[i][0];//����
        Cur_Rate_Info.Date_Period = i + 1;//��ʱ�κ�
        Min = Dec;
      }
    }
  }

  if(!(Rate <= MAX_RATES && Rate <= Multi_Rate_Para.Rates && Rate > 0))//���ʺŴ�Ĭ��ʹ�÷���1
  {
    ASSERT_FAILED();
    Rate = 1;
  }

  if(Cur_Rate_Info.Rate != Rate || CALC_ROM EQ Flag)//��Ҫ�л�������
  {
    Cur_Rate_Info.Rate = Rate;
    SET_STRUCT_SUM(Cur_Rate_Info);//���溯����CHECK_STRUCT_SUMŶ
    Rate_Changed_Proc();//�����л���ش���
  }

  if(Period != Cur_Rate_Info.Date_Period)
  {
    Set_Event_Instant(ID_PARSE_SWITCH);
    Port_Out_Pub(EXT_ID_PARSE,85);
    Debug_Print("Date Period Switch!!!");    
  }//ʱ���л�

  SET_STRUCT_SUM(Cur_Rate_Info);  
  return Rate;//���ط��ʺ�
}
/*
typedef struct
{
  INT32U Chang_Plus_AcEnerg[4];      //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
  INT32U Chang_Nega_AcEnerg[4];      //A/B/C/SUM��Ԫ�������й�����:��λ:0.01wh
  
  //INT32U Chang_Plus_ReacEnerg[4];    //A/B/C/SUM��Ԫ�������޹�����(�޹����1):��λ:0.01warh  
  //INT32U Chang_Nega_ReacEnerg[4];    //A/B/C/SUM��Ԫ�������޹�����(�޹����2):��λ:0.01warh
  
  INT32U Chang_Quad_ReacEnerg[4][4];   //A/B/C/SUM��Ԫ���������޹�����, Chang_Quad_ReacEnerg[1][2]��ʾB��3�����޹�
  
  INT32U Add_AmpaHour[3];       //AH�ۼ�:0.0001As, �ۼ���
  INT32U Add_CopperLoss[4];   //A, B, C, sumͭ��, ��λΪ0.0000001kA2s, �ۼ���
  INT32U Add_IronLoss[4];     //A, B, C, sum����, ��λΪ0.0000001KV2s���ۼ���
  INT32U Add_GenaralErr[4];   //A, B, C, sum�ϳ����, ��λ:0.01*tgFA*s, �ۼ���
  INT8U CS[CS_BYTES];
}MEASU_ENERG; 
*/
//����ۻ����������Ƿ���ȷ
INT8U Check_Cumulative_Energy_Data(MEASU_ENERG* pEnergy)
{
  INT8U Re, i, j;

  TRACE();

  Re = Check_STRUCT_Sum(pEnergy, sizeof(MEASU_ENERG), pEnergy->CS, sizeof(pEnergy->CS));
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    return 0;
  }

  for(i = 0; i < 4; i++)
  {
    if(pEnergy->Chang_Plus_AcEnerg[i] >= (INT32U) MAX_ACTIVE_INC * ENERGY_RATIO || \
       pEnergy->Chang_Nega_AcEnerg[i] >= (INT32U) MAX_ACTIVE_INC * ENERGY_RATIO)
    {
      ASSERT_FAILED();
      return 0;
    }
    else
    {
      for(j = 0; j < 4; j++)
      {
        if(pEnergy->Chang_Quad_ReacEnerg[i][j] >= (INT32U) MAX_REACTIVE_INC * ENERGY_RATIO)
        {
          ASSERT_FAILED();
          return 0;
        }
      }
    }
  }

  return 1;
}

//�����������Ƿ�����
INT8U Check_Energy_Data_Inc()
{
  INT8U i;
  INT32U Temp;

  TRACE();

#if USE_ENERGY_RAM_BAK > 0  
  //�����й�����
  if(Cur_Energy.Pos_Active[0] >= Cur_Energy_Bak.Pos_Active[0])
  {
    Temp = Cur_Energy.Pos_Active[0] - Cur_Energy_Bak.Pos_Active[0];
    if(Temp > MAX_ACTIVE_INC)//��������
    {
      //Debug_Print("Pos Energy Data Inc too much:%ld", Temp);
      ASSERT_FAILED();
      return 0;
    }
  }
  else//��������
  {
    ASSERT_FAILED();
    //Debug_Print("Pos Energy Data Dec!");
    return 0;
  }

  //�����й�����
  if(Cur_Energy.Neg_Active[0] >= Cur_Energy_Bak.Neg_Active[0])
  {
    Temp = Cur_Energy.Neg_Active[0] - Cur_Energy_Bak.Neg_Active[0];
    if(Temp > MAX_ACTIVE_INC)//��������
    {
      //Debug_Print("Neg Energy Data Inc too much:%ld", Temp);
      ASSERT_FAILED();
      return 0;
    }
  }
  else//��������
  {
    ASSERT_FAILED();
    //Debug_Print("Neg Energy Data Dec!");
    return 0;
  }

  //�������޹�
  for(i = 0; i < 4; i++)
  {
    if(Cur_Energy.Quad_Reactive[i][0] >= Cur_Energy_Bak.Quad_Reactive[i][0])
    {
      Temp = Cur_Energy.Quad_Reactive[i][0] - Cur_Energy_Bak.Quad_Reactive[i][0];
      if(Temp > MAX_REACTIVE_INC)//��������
      {
        //Debug_Print("Quad %d Reactive Energy Data Inc too much:%ld", i, Temp);
        ASSERT_FAILED();
        return 0;
      }
    }
    else//��������
    {
      ASSERT_FAILED();
      //Debug_Print("Quad %d Reactive Energy Data Dec!", i);
      return 0;
    }

    //����������й� for (i = 0; i < 3; i++)

  }
  {
    //�����й�
    if(Cur_Energy.Phase_Pos_Active[i] >= Cur_Energy_Bak.Phase_Pos_Active[i])
    {
      Temp = Cur_Energy.Phase_Pos_Active[i] - Cur_Energy_Bak.Phase_Pos_Active[i];
      if(Temp > MAX_ACTIVE_INC)//��������
      {
        //Debug_Print("Phase %c Pos_Active Energy Data Inc too much:%d", 'A' + i, Temp);
        ASSERT_FAILED();
        return 0;
      }
    }
    else//��������
    {
      ASSERT_FAILED();
      //Debug_Print("Phase %c Pos_Active Energy Data Dec!", 'A' + i);
      return 0;
    }

    //�����й�
    if(Cur_Energy.Phase_Neg_Active[i] >= Cur_Energy_Bak.Phase_Neg_Active[i])
    {
      Temp = Cur_Energy.Phase_Neg_Active[i] - Cur_Energy_Bak.Phase_Neg_Active[i];
      if(Temp > MAX_REACTIVE_INC)//��������
      {
        //Debug_Print("Phase %c Neg_Active Energy Data Inc too much:%ld", 'A' + i, Temp);
        ASSERT_FAILED();
        return 0;
      }
    }
    else//��������
    {
      ASSERT_FAILED();
      //Debug_Print("Phase %c Neg_Active Energy Data Dec!", 'A' + i);
      return 0;
    }
  }
  return 1;
#else
  i=0;
  Temp=0;
  (void)i;
  (void)Temp;
  return 1;
#endif  
}

#pragma optimize=none
//��ǰ�����ۼ�
void Cur_Energy_Cumu(MEASU_ENERG* pEnergy)
{
  INT8U Rate;
  INT8U i, j;

  
  TRACE();

  Rate = Cur_Rate_Info.Rate;//Get_Using_Rate();//��ǰʹ�÷���
  //��֤��ǰ����������ȷ��, ���������������������Ĭ��ʹ�÷���1
  if(!(Rate > 0 && Rate <= Multi_Rate_Para.Rates && Rate <= MAX_RATES))
  {
    ASSERT_FAILED();
    Rate = 1;
  }
  //�����й��ۼ�  
  Cur_Energy.Pos_Active[0] += (pEnergy->Chang_Plus_AcEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Pos_Active[Rate] += (pEnergy->Chang_Plus_AcEnerg[3] / ENERGY_RATIO);

  //��ǰ�������ڵ���
  Cur_Energy.Prepaid_Info.Month_Pos_Act += (pEnergy->Chang_Plus_AcEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Prepaid_Info.Month_Neg_Act += (pEnergy->Chang_Nega_AcEnerg[3] / ENERGY_RATIO);
  
  //�����й��ۼ�
  Cur_Energy.Neg_Active[0] += (pEnergy->Chang_Nega_AcEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Neg_Active[Rate] += (pEnergy->Chang_Nega_AcEnerg[3] / ENERGY_RATIO);

#if APP_ENERG_EN >0     
  //���������ۼ�  
  Cur_Energy.Pos_Apparent[0] += (pEnergy->Chang_Plus_PQSEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Pos_Apparent[Rate] += (pEnergy->Chang_Plus_PQSEnerg[3] / ENERGY_RATIO);
  //���������ۼ�
  Cur_Energy.Neg_Apparent[0] += (pEnergy->Chang_Nega_PQSEnerg[3] / ENERGY_RATIO);
  Cur_Energy.Neg_Apparent[Rate] += (pEnergy->Chang_Nega_PQSEnerg[3] / ENERGY_RATIO);
#endif
  
  
  //�������޹��ۼ�
  for(i = 0; i < 4; i++)
  {
    Cur_Energy.Quad_Reactive[i][0] += pEnergy->Chang_Quad_ReacEnerg[3][i] / ENERGY_RATIO;    
    Cur_Energy.Quad_Reactive[i][Rate] += pEnergy->Chang_Quad_ReacEnerg[3][i] / ENERGY_RATIO;
  }

  //�������޹�
  for(i = 0; i < 3; i++)
  {
    Cur_Energy.Phase_Pos_Active[i] += (pEnergy->Chang_Plus_AcEnerg[i] / ENERGY_RATIO);
    Cur_Energy.Phase_Neg_Active[i] += (pEnergy->Chang_Nega_AcEnerg[i] / ENERGY_RATIO);

#if APP_ENERG_EN >0     
    Cur_Energy.Phase_Pos_Apparent[i] += (pEnergy->Chang_Plus_PQSEnerg[i] / ENERGY_RATIO);
    Cur_Energy.Phase_Neg_Apparent[i] += (pEnergy->Chang_Nega_PQSEnerg[i] / ENERGY_RATIO);    
#endif
    
    for(j = 0; j < 4; j++)//���������޷ֱ����
      Cur_Energy.Phase_Quad_Reactive[i][j] += pEnergy->Chang_Quad_ReacEnerg[i][j] / ENERGY_RATIO;
  }

  //���ల��ʱ
  for(i = 0; i < 3; i++)
  {
    Cur_Energy.Phase_AH[i + 1] += (pEnergy->Add_AmpaHour[i] / AH_RATIO);
    Cur_Energy.CopperLoss[i + 1] += (pEnergy->Add_CopperLoss[i] / COPPERLOSS_RATIO);    
    Cur_Energy.IronLoss[i + 1] += (pEnergy->Add_IronLoss[i] / IRONLOSS_RATIO);
    
    Cur_Energy.TransErr[i + 1] += (pEnergy->Add_GenaralErr[i] / TRANSERR_RATIO);
  }
  //��AH
  Cur_Energy.Phase_AH[0] += (pEnergy->Add_AmpaHour[3] / AH_RATIO); 
  //��ͭ��  
  Cur_Energy.CopperLoss[0] += (pEnergy->Add_CopperLoss[3] / COPPERLOSS_RATIO);
  //������  
  Cur_Energy.IronLoss[0] += (pEnergy->Add_IronLoss[3] / IRONLOSS_RATIO);
  //�ܺϳ����
  Cur_Energy.TransErr[0] += (pEnergy->Add_GenaralErr[3] / TRANSERR_RATIO);

  SET_STRUCT_SUM(Cur_Energy);
}
//�ۼӵ���
void Cumulative_Energy()
{
  static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  MEASU_ENERG* pEnergy;
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_VAR(Sec_Bak);
  ASSERT(1 EQ Re);

  //��֤ÿ��Ž���һ�θú���
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
  {
    return;
  }
  else
  {
    Sec_Bak.Var = Sec_Timer_Pub;
  } 

  Re = 1;
  Re &= Check_Energy_Data((S_Energy *) &Cur_Energy);
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
/*
  OS_Mutex_Pend(TRANS_BUF_SEM_ID);

  Get_Measu_AcculateData_PUCK(HUCK, (void *) Trans_Temp_Buf, (void *) Trans_Temp_Buf, sizeof(MEASU_ENERG), sizeof(Trans_Temp_Buf));
  pEnergy = (MEASU_ENERG *) Trans_Temp_Buf;
  
  Re = CHECK_STRUCT_VAR(_Trans_Temp_Buf);
  ASSERT(1 EQ Re);
  
  Re = Check_Cumulative_Energy_Data(pEnergy);
  ASSERT(1 EQ Re);
  if(1 EQ Re)//pEnergyָ������ݺϷ�
  {
    DIS_PD_INT;//�ص����ж�
    Cur_Energy_Cumu(pEnergy); //��ǰ�����ۼ� 

    if(PREPAID_EN > 0)
      Prepaid_Proc(pEnergy); //Ԥ���Ѵ���
    
    Energy_Cumu_Counts.Var++; //�����ۼӴ�������
    EN_PD_INT;//�������ж�
  }
  
  OS_Mutex_Post(TRANS_BUF_SEM_ID);
*/
  Get_Measu_AcculateData_PUCK(HUCK, (void *) &Accu_Energy, (void *) &Accu_Energy, sizeof(Accu_Energy), sizeof(Accu_Energy));
  pEnergy = (MEASU_ENERG *) &Accu_Energy;
  
  Re = Check_Cumulative_Energy_Data(pEnergy);
  ASSERT(1 EQ Re);
  if(1 EQ Re)//pEnergyָ������ݺϷ�
  {
    DIS_PD_INT;//�ص����ж�
    
    if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)//����Ԥ���ѲŽ���Ԥ���ѽ���
      Prepaid_Proc(pEnergy); //Ԥ���Ѵ���    
    
    Cur_Energy_Cumu(pEnergy); //��ǰ�����ۼ� 
    
    Energy_Cumu_Counts.Var++; //�����ۼӴ�������
    EN_PD_INT;//�������ж�
  }
  
  Check_Energy_Data_Inc();//�����������Ƿ�Ϸ�

  #if USE_ENERGY_RAM_BAK > 0//�����ݱ��ݵ�Cur_Energy_Bak������
  mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy_Bak), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
  #endif
}

//��鸴���ʵ������ݷַ��ʵ������Ƿ�����ܵ���
INT8U Check_Multi_Rate_Data(INT32U Data[])
{
  INT16U i;
  INT32U Sum;

  TRACE();

  Sum = 0;
  for(i = 1; i <= MAX_RATES; i++)
  {
    Sum += Data[i];
  }
  if(Sum EQ Data[0])
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//�����������Ƿ�Ϸ���ȷ
//����1��ʾ������ȷ, 0��ʾ�����д�
INT8U Check_Energy_Data(S_Energy* pEnergy)
{
  INT8U Re = 1;

  TRACE();

  Re &= (pEnergy->Head EQ CHK_BYTE && pEnergy->Tail EQ CHK_BYTE) ? 1 : 0;  
  Re &= Check_STRUCT_Sum(pEnergy, sizeof(S_Energy), pEnergy->CS, sizeof(pEnergy->CS));
  Re &= (pEnergy->Data_Ready_Flag EQ DATA_READY) ? 1 : 0;
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    return 0;
  }

  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Pos_Active));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Neg_Active));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Neg_Active));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[0]));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[1]));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[2]));
  Re &= Check_Multi_Rate_Data((INT32U *) (pEnergy->Quad_Reactive[3]));
  Re &= Check_STRUCT_Sum(pEnergy, sizeof(S_Energy), pEnergy->CS, sizeof(pEnergy->CS));  
  
  if(0 EQ Re)
  {
    ASSERT_FAILED();
  }
  return Re;
}

//���ȫ�ֹ���buf�Ƿ�Ϸ�
void Check_Pub_Var_Avail()
{
  INT8U Re;
  
  Re = 1;
  Re &= CHECK_STRUCT_VAR(_Pub_Buf);
  Re &= CHECK_STRUCT_VAR(_Pub_Buf0);
  Re &= CHECK_STRUCT_VAR(Pub_Timer);
  Re &= CHECK_STRUCT_VAR(_Trans_Temp_Buf);
  
  ASSERT(1 EQ Re);
}

//��鵱ǰ��������������, �������ݴ���
void Check_Energy_Data_Avail()//��鵱ǰ�������������ݵ���ȷ��, �� = ��
{
  INT8U Re;
  static S_Flag Energy_Err_Flag = {0, {0}};

  //Energy_Err_Flag������¼���������Ƿ��������󣨷ַ��ʺͣ� = �ܣ�, ����Ѿ���������û�о���ɹ�
  //��ñ�־��1����ʶ�����ɹ�, �Ӷ��´ν���ú������ٽ��о�����, ��ֹ�ظ����ϵľ��������

  //��鵱ǰ����, ͬʱ���ַ����Ƿ�����ܣ��Լ�У���
  //���ַ����Ƿ������ʱ������ڴ������ݲ��ԣ����ȡROM�����ݣ�������������ݻ�����
  //��Ĭ�ϸôεĴ���, �Ժ��ٽ��м�飬��ʱEnergy_Err_Flag EQ 1
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(0 EQ Re)
  {
    ASSERT_FAILED();
    #if USE_ENERGY_RAM_BAK > 0 //�ú�Ϊ1��ʾ������Cur_Energy_Bak������ΪCur_Energy���ڴ汸��
    Debug_Print("Cur_Energy Data Error, Copy from Cur_Energy_Bak Data");
    Re = Check_Energy_Data((S_Energy *) &Cur_Energy_Bak);//ʹ���ڴ汸�ݵ���
    if(1 EQ Re)//Cur_Energy_Bak�е�������ȷ
    {
      Debug_Print("Copy Cur_Energy_Bak Data to Cur_Energy");//��Cur_Energy_Bak�е����ݸ��Ƶ�Cur_Energy��
      mem_cpy((void *) &Cur_Energy, (void *) &Cur_Energy_Bak, sizeof(Cur_Energy), (void *) &Cur_Energy, sizeof(Cur_Energy));
    }
    else//Cur_Energy_Bak�����ݲ���ȷ�������ֱ�Ӵ�rom�ж�ȡ����
    {
      Debug_Print("Cur_Energy_Bak Data Error, Read_Energy_Data_From_Rom");
      Read_Energy_Data_From_Rom(); 
      Re = Check_Energy_Data((S_Energy *) &Cur_Energy);//ROM�е�����Ҳ���ԵĻ�����ȫû�а취�ˣ�Ĭ���������, ��Energy_Err_Flag = 1
      if(0 EQ Re)
        Energy_Err_Flag.Flag = 1;//��ʾ����û�гɹ�
      SET_STRUCT_SUM(Energy_Err_Flag);//ͬʱҲ�ɾ��������CHECK_STRUCT_SUM(Energy_Err_Flag) != 1
    }
    #else
    ASSERT_FAILED();
    Debug_Print("Cur_Energy Data Error, Read_Energy_Data_From_Rom");
    Read_Energy_Data_From_Rom(); 
    Re = Check_Energy_Data((S_Energy *) &Cur_Energy);//ROM�е�����Ҳ���ԵĻ�����ȫû�а취�ˣ�Ĭ���������, ��Energy_Err_Flag = 1
    if(0 EQ Re)
      Energy_Err_Flag.Flag = 1;//��ʾ����û�гɹ�
    SET_STRUCT_SUM(Energy_Err_Flag);//ͬʱҲ�ɾ��������CHECK_STRUCT_SUM(Energy_Err_Flag) != 1
    #endif
  }
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Data()
{
  INT8U Re;
  
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//����ʱ���øú����������������
void Save_Cur_Energy_PD_Data()
{
  INT8U Re;
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(0 EQ Re)//�ж�Cur_Energy�е������Ƿ���ȷ������ȷ�����Cur_Energy_Bak�е����ݣ�����������ݶ�����ȷ���򲻴�
  {
    ASSERT_FAILED();
    #if USE_ENERGY_RAM_BAK > 0
    Re = Check_Energy_Data((S_Energy *) &Cur_Energy_Bak);
    if(1 EQ Re)
      mem_cpy((S_Energy *) &Cur_Energy, (S_Energy *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak), (S_Energy *) &Cur_Energy, sizeof(Cur_Energy));
    else
    {
      ASSERT_FAILED();
      return;
    }
    #else
    return;
    #endif
  }
  Re = Write_Storage_Data(_SDI_CUR_ENERGY_PD, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
  if(1 != Re)
  {
    ASSERT_FAILED();
  }
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Bak0_Data()
{
  INT8U Re;

  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY_BAK0, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);  
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Bak1_Data()
{
  INT8U Re;

  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY_BAK1, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);  
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//���浱ǰ�������������ݣ������̶�ʱ���øú������������
void Save_Cur_Energy_Bak2_Data()
{
  INT8U Re;
  Re = Check_Energy_Data((S_Energy *) &Cur_Energy);
  if(1 EQ Re)
  {
    Re = Write_Storage_Data(_SDI_CUR_ENERGY_BAK2, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
    ASSERT(1 EQ Re);  
    //OS_TimeDly_Ms(100);
  }
  else
  {
    ASSERT_FAILED();
  }
}

//����Ĭ�ϵĹ�������ͽ��
void Set_Def_Prepaid_Buy_Counts_Money()
{
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts = 0;
  Cur_Energy.Prepaid_Info.Total_Prepaid_Money = 0;

  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts = 0;
  Cur_Energy.Prepaid_Info.Total_Prepaid_Energy = 0;  
}

//����Ĭ�ϵĵ�������
void Set_Def_Energy_Data()
{
  INT8U i;
  S_HEX_Time TempTime;
  STORA_DI SDI;
  INT32U Temp_Counts, Temp_Money;
  //���ؿ�bak_up
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  {
    if(PREPAID_MODE EQ PREPAID_MONEY) //�����
    {
      Temp_Counts = Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts;
      Temp_Money = Cur_Energy.Prepaid_Info.Total_Prepaid_Money;
    }
    else
    {
      Temp_Counts = Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts;
      Temp_Money = Cur_Energy.Prepaid_Info.Total_Prepaid_Energy;      
    }
  }
  
  Debug_Print("Set Def Energy Data");
  mem_set((void *) &Cur_Energy, 0, sizeof(Cur_Energy), (void *) &Cur_Energy, sizeof(Cur_Energy));
  //SET_STRUCT_SUM(Cur_Energy);

  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL)
  {
    if(PREPAID_MODE EQ PREPAID_MONEY) //�����
    {
      Cur_Energy.Prepaid_Info.Total_Prepaid_Money_Counts = Temp_Counts;
      Cur_Energy.Prepaid_Info.Total_Prepaid_Money = Temp_Money;
    }
    else
    {
      Cur_Energy.Prepaid_Info.Total_Prepaid_Energy_Counts = Temp_Counts;
      Cur_Energy.Prepaid_Info.Total_Prepaid_Energy =Temp_Money;      
    }
  }
  
  INIT_STRUCT_VAR(Cur_Energy);
  SET_DATA_READY_FLAG(Cur_Energy);
  SET_STRUCT_SUM(Cur_Energy);

  Prepaid_Clr_Month_Eng_Money((S_HEX_Time *) &Cur_Time0);
  
  #if USE_ENERGY_RAM_BAK EQ 1
  mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
  SET_STRUCT_SUM(Cur_Energy_Bak);
  #endif
  
  Save_Cur_Energy_PD_Data();
  Save_Cur_Energy_Data();
  Save_Cur_Energy_Bak0_Data();  
  Save_Cur_Energy_Bak1_Data();  
  Save_Cur_Energy_Bak2_Data();

  Get_N_Last_Settle_Time(MAX_ENERGY_SETTLE_NUM, (S_HEX_Time *) &Cur_Time0, &TempTime, &TempTime, sizeof(TempTime));
  SDI = _SDI_SETTLE_ENERGY_DATA;

  for(i = 0; i < MAX_ENERGY_SETTLE_NUM; i ++)
  {
    if(Cmp_Time(&TempTime, (S_HEX_Time *) &Cur_Time0) != TIME_AFT)
    {
      Debug_Print("Set Def Energy His Data, Time:");
      Print_HEX_Time((S_HEX_Time *) &TempTime);

      mem_cpy((void *) &Cur_Energy.Time, &TempTime, sizeof(TempTime), \
              (void *) &Cur_Energy.Time, sizeof(Cur_Energy.Time));
      SET_STRUCT_SUM(Cur_Energy);

      INC_ENERGY_SETTLE_DI(SDI);
      Write_Storage_Data(SDI, (void *) &Cur_Energy, sizeof(Cur_Energy));
    }
    Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
  }

  Write_Storage_Data(_SDI_LAST_SETTLE_ENERGY_DI, &SDI, sizeof(SDI));
  
  Settle_Energy_FF_Data(0);
//--------------------------------------�ͼ�ר�ã���ʽ����ȥ��-------------------
  if(PREPAID_EN > 0 && PREPAID_LOCAL_REMOTE EQ PREPAID_LOCAL) //���طѿر��Ԥ�õ������
  {
    if(Check_Meter_Factory_Status())
    {
      if(PREPAID_MODE EQ PREPAID_MONEY)
        Cur_Energy.Prepaid_Info.Left_Money = 200000; //��200Ԫʣ����
      else
        Cur_Energy.Prepaid_Info.Left_Energy = 200000; //��200��ʣ�����
      SET_STRUCT_SUM(Cur_Energy);
     
      #if USE_ENERGY_RAM_BAK EQ 1
      mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak));
      SET_STRUCT_SUM(Cur_Energy_Bak);
      #endif
    
      Save_Cur_Energy_PD_Data();
      Save_Cur_Energy_Data();
    }
  }
//------------------------------------------------------------------  
}

//ÿ��һ��ʱ���Զ����浱ǰ����������������ʱ�������
void Period_Save_Cur_Data()
{
  DECLARE_BUF_TYPE(INT8U, 6, S_Bak_Hour);
  static S_Bak_Hour Bak_Hour =  {CHK_BYTE, {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, CHK_BYTE};
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U Re;

  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(1 EQ Re);

  Re = CHECK_STRUCT_SUM(Cur_Time0);
  if(0 EQ Re)
  {
    ASSERT_FAILED();
  }

  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])//ÿ�����ж�һ��
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];

    if(Min_Bak.Var EQ 0)//����Ϊ0������²�����!��Ϊ���ʱ�̿������¶���ʱ�̣���ʱ��Ӧ�ô����������������
      return;

    Re = CHECK_STRUCT_VAR(Bak_Hour);
    ASSERT(1 EQ Re);

    SET_STRUCT_TIME(Cur_Energy, Cur_Time0);
    SET_STRUCT_TIME(Cur_Demand.Demand[0], Cur_Time0);
    SET_STRUCT_TIME(Cur_Demand.Demand[1], Cur_Time0);
    SET_STRUCT_SUM(Cur_Demand);
    SET_STRUCT_TIME(Cur_VolStat, Cur_Time0);

    //ÿ��Сʱ�����������, �����ݴ����������
    if(Cur_Time0.Time[T_MIN] EQ 17 || Cur_Time0.Time[T_MIN] EQ 47)
    {
      Debug_Print("Every 30 Mins Save_Cur_Energy_Demand_PD_Data");
      Save_Cur_Energy_PD_Data();
      Save_Cur_Demand_PD_Data();
    }

    //ÿ2Сʱ��������, �����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR] % 2 EQ 1 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[0])
    {
      Debug_Print("Every 2 Hour Save_Cur_Energy_Demand_Data");
      Bak_Hour.Buf[0] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Data();
      Save_Cur_Demand_Data();
    }

    //ÿ6Сʱ����һ�ε����������ݵ����ݵ�DI��, �����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR] % 6 EQ 0 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[1])
    {
      Debug_Print("Every 2 Hours Save_Cur_Energy_Bak0_Data && Save_Cur_Demand_Bak_Data");
      Bak_Hour.Buf[1] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak0_Data();
      Save_Cur_Demand_Bak_Data();
    }

    //ÿ8Сʱ����һ�ε����������ݵ����ݵ�DI��, �����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR] % 8 EQ 1 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[2])
    {
      Debug_Print("Every 8 Hours Save_Cur_Energy_Bak1_Data && Period_Save_RTC_BatTime");
      Bak_Hour.Buf[2] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak1_Data();
      Period_Save_RTC_BatTime(); //ʱ�ӵ�ع���ʱ��
    }

    //ÿ12Сʱ����һ�ε����������ݵ����ݵ�DI��, ��Ϊ��������DataFlash��, ���12Сʱ��һ��
    if(Cur_Time0.Time[T_HOUR] % 12 EQ 2 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[3])
    {
      Debug_Print("Every 12 hours Save_Cur_Energy_Bak2_Data");
      Bak_Hour.Buf[3] = Cur_Time0.Time[T_HOUR];
      Save_Cur_Energy_Bak2_Data();
    }

    //ÿ3Сʱ�����ѹͳ�Ƶ�������, �����ݴ����������
    if(Cur_Time0.Time[T_HOUR] % 3 EQ 0 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[4])
    {
      Debug_Print("Every 3 hours Save_Cur_VolStat_PD_Data && Save_LoadData_Index");
      Bak_Hour.Buf[4] = Cur_Time0.Time[T_HOUR];    
      Save_Cur_VolStat_PD_Data();
      Save_LoadData_Index();
    }

    //ÿ4Сʱ�����ѹͳ������, �Լ�����������������, �����ݴ����EEROM��
    if(Cur_Time0.Time[T_HOUR] % 4 EQ 0 && Cur_Time0.Time[T_HOUR] != Bak_Hour.Buf[5])
    {
      Debug_Print("Every 4 hours Save_Cur_VolStat_Data && Save_LoadData_Index_Bak");
      Bak_Hour.Buf[5] = Cur_Time0.Time[T_HOUR];    
      Save_Cur_VolStat_Data();
      Save_LoadData_Index_Bak();
    }
  }
}

//���ʷ����л�����, ��Ҫ�����¶�ȡ���ֲ���
//New_Scheme, ��ʾ�л����÷��ʷ���
//New_Scheme EQ YEAR_SCHEME0����New_Scheme EQ YEAR_SCHEME1
//�ú�������Ҫ�����Ǹ����׷��ʷ�����ز���
void Year_Scheme_Changed_Proc()
{
  INT8U Re;

  Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(!(Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0 || Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME1))
  {
    ASSERT_FAILED();
    Cur_Rate_Info.Year_Scheme = YEAR_SCHEME0;//Ĭ��ʹ�������ʷ���
    SET_STRUCT_SUM(Cur_Rate_Info);
  }
  Debug_Print("Year_Scheme Changed! Use Scheme:%s", (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?"0":"1");

  Read_Year_Table_Para(Cur_Rate_Info.Year_Scheme);//�Ӵ洢���ж�ȡ��ǰ���ʷ�����صĲ��� 
}

//������ʱ�η��������л�ʱ�Ĵ���
void Date_Scheme_Changed_Proc()
{
  Cal_Cur_Date_Table(CALC_ROM);//���¼���ʱ�α��, �������¶�ȡ��ʱ�α������Date_Table�� 
}

//���ʷ����л���������Ԥ����
void Rate_Scheme_Changed_Proc()
{ 
  Read_Rate_Scheme_Para(Cur_Rate_Info.Rate_Scheme);
}

//���׽��ݷ����л�
void Step_Scheme_Changed_Proc()
{
  Read_Step_Scheme_Para(Cur_Rate_Info.Step_Scheme);  
}

//�����л�����
void Rate_Changed_Proc()
{
  INT8U Re;

  Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Debug_Print("Rate Changed! Use %dth Rate", Cur_Rate_Info.Rate);
}

//���㵱ǰ���ʷ����ͷ��ʣ��Լ��Ƿ��������л���������������л�
//�����´�rom�ж�ȡ��ز�����
void Check_Cur_Rate()
{
  S_Int32U static Sec = {CHK_BYTE, 0, CHK_BYTE};
  S_Int8U  static Min = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;  

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Time_Modify_Flag);
  ASSERT(1 EQ Re);
  
  //ʱ��ÿ�߹�1S�����г������ִ��
  if(Sec.Var EQ Sec_Timer_Pub)
  {
    return;
  }
  else
  {
    Sec.Var = Sec_Timer_Pub;
  }

  if(Min.Var != Cur_Time0.Time[T_MIN] || Time_Modify_Flag.Var EQ 1)//ÿ��һ���ӽ���һ�����������
  {
    Time_Modify_Flag.Var = 0;
    Min.Var = Cur_Time0.Time[T_MIN];
    //��鵱ǰ������Ϣ
    Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
    if(1 != Re)//ASSERT(0 != Re))
    {
      ASSERT_FAILED();
      Check_Data_Avail();
    }
    
    //���㵱ǰӦ��ʹ�õķ��ʷ���, �жϵ�ǰ�׷��ʷ�������������������л�������¸����ʲ���Multi_Rate_Para, �Լ����µ�ǰ��ʱ�α�   

    Calc_Cur_Year_Scheme(CALC_RAM);//���㵱ǰ��ʱ������
    Calc_Cur_Date_Scheme(CALC_RAM);//���㵱ǰ��ʱ�α���
    Calc_Cur_Rate(CALC_RAM);//���㵱ǰӦ��ʹ�õķ���
    Calc_Cur_Rate_Scheme(CALC_RAM); //���㵱ǰ��ʱ���ʷ���(Ԥ����)
    Calc_Cur_Step_Scheme(CALC_RAM); //���㵱ǰ���ݷ���(Ԥ����)
  }
}
/*
//��������õ���,Ԥ�����ü�����ݵ��ʱ��
void Clear_Prepaid_Month_Eng()
{
 // if(pTime -> Time[T_DATE] EQ Bcd2Hex_Byte(Settle_Time.Time_D_H[0][1]) &&\
  //   pTime -> Time[T_HOUR] EQ Bcd2Hex_Byte(Settle_Time.Time_D_H[0][0]))
  {
    Cur_Energy.Prepaid_Info.Month_Pos_Act = 0;  
    SET_STRUCT_SUM(Cur_Energy);
  }
}
*/
/*
//ÿ�³����ն��ᴦ��
void Month_Data_Freeze()
{
  INT8U Re;
  static S_Int8U Hour_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  S_HEX_Time TempTime;
  
  //��֤ÿСʱֻ����һ��
  Re = CHECK_STRUCT_VAR(Hour_Bak);
  ASSERT(1 EQ Re);
  
  if(Hour_Bak.Var EQ Cur_Time0.Time[T_HOUR])
  return;
  else
  Hour_Bak.Var = Cur_Time0.Time[T_HOUR];
  
  Re = 1;
  Re &= Check_HEX_Time((S_HEX_Time *)&Cur_Time0);
  Re &= CHECK_STRUCT_SUM(Data_Freeze_Time);
  if(ASSERT(1 EQ Re))
  Check_Data_Avail();
  
  //ʱ�����ݲ���BCD��
  //Re = C((INT8U *)(Data_Freeze_Time.DDHH), 2);
  //Re = CHECK_STRUCT_SUM(Data_Freeze_Time);
  //if(ASSERT(1 EQ Re))
  //Check_Data_Avail();
  
  //����Զ�����ʱ�����ô���
  if(ASSERT(Data_Freeze_Time.DDHH[0] <= 23))
  {
  Data_Freeze_Time.DDHH[0] = 0;
  SET_STRUCT_SUM(Data_Freeze_Time);
  }
  if(ASSERT(Data_Freeze_Time.DDHH[1] >= 1 &&\
      Data_Freeze_Time.DDHH[1] <= 31))
  {
  Data_Freeze_Time.DDHH[1] = 1;
  SET_STRUCT_SUM(Data_Freeze_Time);
  }
  
  //�ж϶�����ʱ���Ƿ���
  if(Cur_Time0.Time[T_HOUR] EQ Data_Freeze_Time.DDHH[0] &&\
   Cur_Time0.Time[T_DATE] EQ Data_Freeze_Time.DDHH[1])
  {
  Debug_Print("----------Month Data Freeze Start!----------");
  //��ȡ���¶���ʱ���
  Get_NowMonth_Freeze_Time((S_HEX_Time *)&Cur_Time0, &TempTime);//��ֱֹ��ʹ��Cur_Time0�����ķ������

  //����Ҫ��������ݵ�ʱ������Ϊ����ʱ���
  SET_STRUCT_TIME(Cur_Energy, TempTime);
  SET_STRUCT_TIME(Cur_Demand.Demand[0], TempTime);
  SET_STRUCT_TIME(Cur_Demand.Demand[1], TempTime);
  SET_STRUCT_SUM(Cur_Demand);
  SET_STRUCT_TIME(Cur_VolStat, TempTime);
  
  Settle_Energy_Data(&TempTime);//�����������
  Settle_Demand_Data(&TempTime);//������������
  Settle_VolStat_Data(&TempTime);//�����ѹͳ������

  }
}
*/

/*
//��ȡ�����ղ���
void Read_Settle_Para_From_Rom()
{
  INT8U i;
  INT16U Len;

  for(i = 0; i < 3; i ++)
  {
  Len = Read_Storage_Data(0x04000B01 + i, (INT8U *)Settle_Time.Time_D_H[i], (INT8U *)Settle_Time.Time_D_H, sizeof(Settle_Time.Time_D_H));
  ASSERT(Len EQ 2);
  }
}
*/

//���pTime�Ƿ�Ϊ��������������ʱ��
INT8U Check_Eng_Settle_Time(S_BCD_Time *pTime)
{
  INT8U i;
  //ÿ�µ����������Ľ���
  for(i = 0; i < 3 ; i ++)
  {
    if(pTime -> Hour EQ Settle_Time.Time_D_H[i][0] && \
       pTime -> Date EQ Settle_Time.Time_D_H[i][1] && \
       pTime -> Min EQ 0)
    {
      return 1;
    }
  }

  return 0;
}

void Settle_Data()
{
  INT8U Re;
  static S_Int8U Min_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  S_HEX_Time TempTime;

  //��֤ÿСʱֻ����һ��
  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(1 EQ Re);

  if(Min_Bak.Var EQ Cur_Time1.Min)
  {
    return;
  }
  else
  {
    Min_Bak.Var = Cur_Time1.Min;
  }

  Re = 1;
  Re &= Check_BCD_Time((S_BCD_Time *) &Cur_Time1);
  Re &= CHECK_STRUCT_SUM(Settle_Time);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  //��ѹͳ�����ݵĽ�����ÿ��1��0ʱ
  Convert_BCD_2_HEX_Time((S_BCD_Time *) &Cur_Time1, &TempTime);//��ǰHEXʱ��

  if(Check_Eng_Settle_Time((S_BCD_Time *) &Cur_Time1))
  {
    Settle_Prepaid_Month_Eng(&TempTime); 
    Settle_Energy_Data(&TempTime);
    Settle_Demand_Data(&TempTime);
    Settle_VolStat_Data(&TempTime);
  }
}

//��ʼ����������
void Read_Energy_Data_From_Rom()
{
  //INT8U Err = NO_ERR;
  S_Energy* p;

  //�ȶ�ȡ����洢������
  //�ٶ���ͨ����
  //��������������
  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  p = (S_Energy *) Pub_Buf0;

  if(Read_Storage_Data(_SDI_CUR_ENERGY_PD, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
     Check_Energy_Data((S_Energy *) p) != 1)
  {
    //��Ҫ��֤�洢��У�����ȷ�����ݱ�����ȷ����Ϊ��ȡ�ɹ�
    Debug_Print("Read _SDI_CUR_ENERGY_PD data error");
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data(_SDI_CUR_ENERGY, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
       Check_Energy_Data((S_Energy *) p) != 1)
    {
      Debug_Print("Read _SDI_CUR_ENERGY data error");
      OS_TimeDly_Ms(500);
      if(Read_Storage_Data(_SDI_CUR_ENERGY_BAK0, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
         Check_Energy_Data((S_Energy *) p) != 1)
      {
        Debug_Print("Read _SDI_CUR_ENERGY_BAK0 data error");
        OS_TimeDly_Ms(500);
        if(Read_Storage_Data(_SDI_CUR_ENERGY_BAK1, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
           Check_Energy_Data((S_Energy *) p) != 1)
        {
          Debug_Print("Read _SDI_CUR_ENERGY_BAK1 data error");
          if(Read_Storage_Data(_SDI_CUR_ENERGY_BAK2, p, p, sizeof(Pub_Buf0)) != ENERGY_SAVE_SIZE || \
             Check_Energy_Data((S_Energy *) p) != 1)
          {
            Debug_Print("Read _SDI_CUR_ENERGY_BAK2 data error");
            mem_set(p, 0, sizeof(Cur_Energy), p, sizeof(Pub_Buf0));
            Write_Storage_Data(_SDI_CUR_ENERGY_BAK2, p, ENERGY_SAVE_SIZE);
          }
          Write_Storage_Data(_SDI_CUR_ENERGY_BAK1, p, ENERGY_SAVE_SIZE);
        }
        Write_Storage_Data(_SDI_CUR_ENERGY_BAK0, p, ENERGY_SAVE_SIZE);
      }  
      Write_Storage_Data(_SDI_CUR_ENERGY, p, ENERGY_SAVE_SIZE);
    }
    Write_Storage_Data(_SDI_CUR_ENERGY_PD, p, ENERGY_SAVE_SIZE);
  }       

   DIS_PD_INT;
  mem_cpy((void *) &Cur_Energy, p, sizeof(Cur_Energy), (void *) &Cur_Energy, sizeof(Cur_Energy));
  INIT_STRUCT_VAR(Cur_Energy);  
  SET_DATA_READY_FLAG(Cur_Energy);
  SET_STRUCT_SUM(Cur_Energy);

  #if USE_ENERGY_RAM_BAK > 0
  mem_cpy((void *) &Cur_Energy_Bak, (void *) &Cur_Energy, sizeof(Cur_Energy_Bak), (void *) &Cur_Energy_Bak, sizeof(Cur_Energy_Bak)); 
  #endif
            
   EN_PD_INT;

  OS_Mutex_Post(PUB_BUF0_SEM_ID);
}
//�ú�����Ҫ��ΪҺ����ʾ��һ��׼������������
//��������̻������¶���Щ����
void Read_Energy_Data_Para_For_Show()
{
  INT8U Rst_Flag;  

  //��ȡ����ʱ�洢�ĵ�������, û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  Rst_Flag = Check_Rst_Flag();
  if(Rst_Flag EQ POWER_ON_RST || Check_Energy_Data((S_Energy *) &Cur_Energy) EQ 0)//��Դ�ϵ����У��ʹ��������¶������ȡROM�е�����
  {
    Debug_Print("PowerOn Read Energy Data");
    Read_Energy_Data_From_Rom();
  }

  Read_Mode_Word();//��ȡģʽ�֣����ڼ��������й���ģʽ��
  //������ʾС��λ��
  /*
  if(Read_Storage_Data(0xC115, (void *)(&Disp_Digs.Energy_Digs), (void *)(&Disp_Digs.Energy_Digs), 1) != 1 || Err != NO_ERR)
    Debug_Print("Read 0xC125 Para Err");    
  Disp_Digs.Energy_Digs = Bcd2Hex_Byte(Disp_Digs.Energy_Digs);
  SET_STRUCT_SUM(Disp_Digs);
  */
}



//���籣��������������ݵ�
//�˺�����Ϊ�ǵ���洢�����û����ʱ����
void PowerDown_Save_Energy_Data()
{
  //�������ʱ�洢�ĵ�������, û�ж�ȡ�ɹ����ȡ���ݴ洢������ 
  Write_Storage_Data(_SDI_CUR_ENERGY_PD, (void *) (&Cur_Energy), ENERGY_SAVE_SIZE);
}

//�������
void PowerDown_Save_Data()
{
  PowerDown_Save_Energy_Data();//�����������
  PowerDown_Save_Demand_Data();//������������
  PowerDown_Save_VolStat_Data(); //�����ѹͳ������
}

#pragma optimize = none
//����ǰ������Ϣ�ȴ�ӡ����
void Debug_Print_Cur_Energy_Info()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Counts = {CHK_BYTE, 0, CHK_BYTE};
  INT8U i, Re;

  if(Check_Debug_En() EQ 0)//�ǹ���״̬����ӡ
    return;

  if(Cur_Time0.Time[T_MIN] EQ Min.Var)//ÿ����ִ��һ�θú���
  {
    return;
  }

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  Re &= CHECK_STRUCT_VAR(Counts);
  ASSERT(1 EQ Re);

  Min.Var = Cur_Time0.Time[T_MIN];

  Clr_Ext_Inter_Dog();
  Debug_Print("----------Cur_Rate_Info-----------");
  Debug_Print("Cur_Time:%d-%d-%d %d:%d, Week:%d", Cur_Time0.Time[T_YEAR], Cur_Time0.Time[T_MONTH],\
    Cur_Time0.Time[T_DATE], Cur_Time0.Time[T_HOUR], Cur_Time0.Time[T_MIN], Cur_Time0.Week);
  Debug_Print("Cur Year Scheme:%s", (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?"0":"1");
  Debug_Print("Cur Date Scheme:%s", (Cur_Rate_Info.Date_Scheme EQ DATE_SCHEME0)?"0":"1");
  Debug_Print("Cur Rate:%d", Cur_Rate_Info.Rate);

  if(Cur_Rate_Info.Date_Flag EQ HOLIDAY)
  {
    Debug_Print("Today is Holiday, Holiday_Index = %d", Cur_Rate_Info.Holiday_Index);
  }
  else if(Cur_Rate_Info.Date_Flag EQ WEEK_REST_DAY)
  {
    Debug_Print("Today is Week_Rest_Day");
  }
  else if(Cur_Rate_Info.Date_Flag EQ NORMAL_DAY)
  {
    Debug_Print("Today is Normal_Day, Year_Peirod = %d", Cur_Rate_Info.Year_Period);
  }
  else
  {
    Debug_Print("Today Date_Flag Err");
  }

  //��ǰ��ʱ�α�ź͵�ǰ��ʱ��
  Debug_Print("Cur Date_Table:%d Date_Period:%d", \
  Cur_Rate_Info.Date_Table, Cur_Rate_Info.Date_Period);
  //��ǰ�����й���
  Debug_Print("Cur_Pos_Active:%ld", Cur_Energy.Pos_Active[0]);

  Counts.Var++;
  if(Counts.Var >= 5)//ÿ��5���Ӵ�ӡһ�ε�ǰ����ֵ
  {
    Counts.Var = 0;

    Clr_Ext_Inter_Dog();
    Debug_Print("|-----------------------------Total_Energy-------------------------|"); 
    Debug_Print("| Rate Pos_Activ Neg_Activ Quad0_Rea Quad1_Rea Quad2_Rea Quad3_Rea |");
    for(i = 0; i <= Multi_Rate_Para.Rates; i++)
    {
      Debug_Print("|   %2d %9ld %9ld %9ld %9ld %9ld %9ld |", i, Cur_Energy.Pos_Active[i], Cur_Energy.Neg_Active[i],\
                   Cur_Energy.Quad_Reactive[0][i], Cur_Energy.Quad_Reactive[1][i], Cur_Energy.Quad_Reactive[2][i], Cur_Energy.Quad_Reactive[3][i]);
    }

    //��ӡ�������
    Debug_Print("|------------------------------------------------------------------|"); 

    OS_TimeDly_Ms(50);

    Clr_Ext_Inter_Dog();  
    Debug_Print("|-----------------------------Phase_Energy-------------------------|"); 
    Debug_Print("| Phas Pos_Activ Neg_Activ Quad0_Rea Quad1_Rea Quad2_Rea Quad3_Rea |");

    for(i = 0; i < 3; i++)
    {
      Debug_Print("|    %c %9ld %9ld %9ld %9ld %9ld %9ld |", (INT8S) ('A' + i), Cur_Energy.Phase_Pos_Active[i], Cur_Energy.Phase_Neg_Active[i],\
                  Cur_Energy.Phase_Quad_Reactive[i][0], Cur_Energy.Phase_Quad_Reactive[i][1],\
                  Cur_Energy.Phase_Quad_Reactive[i][2], Cur_Energy.Phase_Quad_Reactive[i][3]);
    }
    Debug_Print("|------------------------------------------------------------------|");
  }
}

//��ʼ��������������ز���
void Read_Energy_Para_From_Rom()
{
  Read_Mode_Word();//��ȡģʽ��
  
  Read_Settle_Para_From_Rom(); //��ȡ����ʱ�� 
  Read_Cur_Scheme_From_Rom(); //��ȡ֮ǰ����ʱ�������ʱ�α��
  Read_Multi_Rate_Para(); //�ȶ�ȡ������ز��� 
  Read_Prepaid_Para_From_Rom(); //��ȡԤ���Ѳ���
  
  //Read_Scheme_Rate_Para();//
  //���²��ֶ�ȡ�׷�����ز���, ��ȡ��Multi_Rate_Para, Year_Table��Holiday_Table

  Calc_Cur_Year_Scheme(CALC_ROM);//���㵱ǰ��ʱ������, CALC_ROM��־��ʾ��ROM�ж�ȡ���������ж�
  OS_TimeDly_Ms(100);
  //Calc_Cur_Year_Scheme(CALC_ROM)�ڲ������Calc_Cur_Date_Scheme(CALC_ROM),��˴˴�����Ҫ
  //Calc_Cur_Date_Scheme(CALC_ROM);//���㵱ǰʹ�õ���ʱ�α���
  //OS_TimeDly_Ms(100);
  Calc_Cur_Rate(CALC_ROM);//���㵱ǰӦ��ʹ�õķ���
  OS_TimeDly_Ms(100);
  Calc_Cur_Rate_Scheme(CALC_ROM); //���㵱ǰ���ʷ�����Ԥ�����ã�
  OS_TimeDly_Ms(100);
  Calc_Cur_Step_Scheme(CALC_ROM); //���㵱ǰ�ݶ�(Ԥ������)
}


void Clear_All_Data()
{
  DISP_CLR_DATA_INFO;
  
  Set_Def_Energy_Data();
  Set_Def_Demand_Data();
}

//��ȡ��ǰ������Ϣ
//���ص�pDst��
//pDst[0] ��ǰ����ʱ������ 0Ϊ��һ�ף�1Ϊ�ڶ���
//pDst[1] ��ǰ��ʱ��
//pDst[2] ��ǰ������ʱ�η���,0Ϊ��һ�ף�1Ϊ�ڶ���
//pDst[3] ��Ǯ��ʱ�α��
//pDst[4] ��ǰ��ʱ�κ�
//pDst[5] ��ǰ����
//pDst[6] ��ǰ���ʷ���,0��ʾ��һ��,1Ϊ�ڶ���
//pDst[7] ��ǰ���ݷ���,0Ϊ��һ�ף�1Ϊ�ڶ���
//pDst[8] ��ǰ���ݺ�, ��1��ʼ��
//pDst[9] ��ǰ������-�������(00��Ԥ����,01������Ԥ���ѱ�,02�����Ԥ���ѱ�)
//pDst[10] ��ǰΪ��ʱ�Ʒѻ��߱��ؼƷ�? 0��ʾ��ʱ��1��ʾ����, 2��ʾ��ϵ��
//pDst[11] ��ǰΪ���ػ���Զ��Ԥ���� 0��ʾ���أ�1��ʾԶ��
//�������ݶ���BCD��
//����ֵ��ʾ�������ݳ���
INT8U Get_Cur_Rate_Info(INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  //TRACE();
  
  if(!(pDst >= pDst_Start && pDst + 12 <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  
  *pDst = (Cur_Rate_Info.Year_Scheme EQ YEAR_SCHEME0)?0:1; //��ǰ��ʱ������
  Hex2Bcd(Cur_Rate_Info.Year_Period, pDst + 1, 1, pDst_Start, DstLen); //��ǰ��ʱ����
  *(pDst + 2) = (Cur_Rate_Info.Date_Scheme EQ DATE_SCHEME0)?0:1; //��ǰ��ʱ�α���
  Hex2Bcd(Cur_Rate_Info.Date_Table, pDst + 3, 1, pDst_Start, DstLen); //��ǰ��ʱ�α��
  Hex2Bcd(Cur_Rate_Info.Date_Period, pDst + 4, 1, pDst_Start, DstLen); //��ǰ��ʱ�κ�
  Hex2Bcd(Cur_Rate_Info.Rate, pDst + 5, 1, pDst_Start, DstLen); //��ǰ����
  *(pDst + 6) = (Cur_Rate_Info.Rate_Scheme EQ RATE_SCHEME0)?0:1; //��ǰ���ʷ���(Ԥ����)
  *(pDst + 7) = (Cur_Rate_Info.Step_Scheme EQ STEP_SCHEME0)?0:1; //��ǰ���ݷ���(Ԥ����)
  *(pDst + 8) = PREPAID_STEP_NO; //��ǰ���ݺ�
  
  if(PREPAID_EN EQ 0) //��Ԥ���ѱ�
    *(pDst + 9) = 0x00;
  else if(PREPAID_MODE EQ ENERGY_MODE) //������Ԥ����
    *(pDst + 9) = 0x01;
  else
    *(pDst + 9) = 0x02; //�����Ԥ����
  
  //��ʱ�Ʒѻ��߱��ؼƷ�? 0��ʾ��ʱ��1��ʾ����, 2��ʾ��ϵ��
  *(pDst + 10) = PREPAID_MONEY_MODE;
  //���ػ���Զ��Ԥ���� 0��ʾ���أ�1��ʾԶ��
  *(pDst + 11) = PREPAID_LOCAL_REMOTE;
  
  return 12;
}

//���ĳ�����Ƿ��ǵ���������ز���
INT8U Check_Energy_Proc_Para(PROTO_DI PDI)
{
  if((PDI & 0xFFFFFF00) EQ 0x10000200)//У�����
    return 0;
  else if(PDI EQ 0x0EA20000 || PDI EQ 0x0EA20001 || PDI EQ 0x0EA20002)//ģ���������
    return 0;
  
  return 1;
}

/*
typedef struct
{
  INT32U Energy;  //���˹������
  INT32U Money;   //���˹�����
  
  INT32U Bef_Buy_Energy; //���˹���Ǯ����
  INT32U Bef_Buy_Money;  //���˹���Ǯ���
}S_Cur_Prepaid; //���˹�����Ϣ
*/



//�������Ƿ����޸�
void Check_Energy_Para_Modified()
{
  PROTO_DI PDI;
  INT8U Re;
  static S_Int32U Sec_Bak0 = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int32U Sec_Bak = {CHK_BYTE, 0xFF, CHK_BYTE};
  static S_Int8U Count = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Init_Para_Flag = {CHK_BYTE, 0, CHK_BYTE};

  if(Sec_Bak0.Var EQ Sec_Timer_Pub)//ÿ��Ž�����һ��
  {
    return;
  }

  Sec_Bak0.Var = Sec_Timer_Pub;
  Re = 1;
  Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Count);
  Re &= CHECK_STRUCT_VAR(Init_Para_Flag);
  ASSERT(1 EQ Re);

  OS_TimeDly_Ms(20);
  //�����ù��Ĳ����������  
  while(Get_Para_Modify(&PDI) EQ 1)
  {
    if(Check_Energy_Proc_Para(PDI))//����ǵ�ǰ������صĲ�������Ҫ���³�ʼ������
    {
      Init_Para_Flag.Var = 1;//��Ҫ���³�ʼ������ 
      Sec_Bak.Var = Sec_Timer_Pub;//���ʱ��    
      Count.Var = 0;//���¿�ʼ����, 10S�����޲������������³�ʼ��������ز���
    }
  }

  //�Ƿ���Ҫ���³�ʼ��?
  if(1 EQ Init_Para_Flag.Var && Sec_Bak.Var != Sec_Timer_Pub)
  {
    Sec_Bak.Var = Sec_Timer_Pub;
    Count.Var++;//�����
  }

  //�޸ĵ�ǰ������ز�����10S�����³�ʼ������
  if(Count.Var >= 2 && 1 EQ Init_Para_Flag.Var)
  {
    //�����˵�����ز���
    Init_Para_Flag.Var = 0;
    Count.Var = 0;
    Refresh_Para_From_Rom();//���½�
  }
}

//��ʼ��������������صĲ���
void Init_Energy_Demand_Ram_Para()
{
  //��ʼ���ź���

  //��ʼ��������Ϣ
  mem_set((void *) &Cur_Rate_Info, 0, sizeof(Cur_Rate_Info), (void *) &Cur_Rate_Info, sizeof(Cur_Rate_Info));
  INIT_STRUCT_VAR(Cur_Rate_Info);
  SET_STRUCT_SUM(Cur_Rate_Info);//������Ϣ
  //��ʼ����ʱ�α�
  mem_set((void *) &Date_Table, 0, sizeof(Date_Table), (void *) &Date_Table, sizeof(Date_Table));
  SET_STRUCT_SUM(Date_Table);//��ʱ�α�

  //��ʼ�������޸ı�־
  //Clear_Flag.Flag = CLEAR_END_FLAG;//�����־, ����������ȵı�־
  //SET_STRUCT_SUM(Clear_Flag);

  //����ȫ�ֻ�������ͷβ�����ֽ�
  INIT_STRUCT_VAR(_Pub_Buf);
  INIT_STRUCT_VAR(_Pub_Buf0);
  INIT_STRUCT_VAR(Pub_Timer);
  Energy_Cumu_Counts.Var = 0; //�����ۼӴ���, �����Գ�����
  INIT_STRUCT_VAR(Energy_Cumu_Counts);

  Chk_Data_Flag.Chk_Flag = 0;
  SET_STRUCT_SUM(Chk_Data_Flag);
}

//��ȡ��ǰ�����й��ܵ���
INT32U Get_Pos_Act_Eng()
{
  return Cur_Energy.Pos_Active[0]; 
}


#undef ENERGY_C
