

#include "Pub_PUCK.h"

#define    MeasuProc_PUCK
#include   "MeasuProc.h"


/**********************************************************************************
�������ܣ��ж��Ƿ�����У���¼�
��ڣ���
���ڣ�0/1
**********************************************************************************/
INT8U Get_Cal_Exsit(void)
{
  if(Check_Meter_Factory_Status() EQ 0)//��ǰ���ǹ���״̬���Ƴ�
    return 0;
  
  if(CHECK_STRUCT_VAR(Cal_Proc_Status))
    return 1;
  
#ifdef ID_EVENT_ADJUST_MEASU
  if(Read_Event_Status(ID_EVENT_ADJUST_MEASU))   //ȷʵ��ҪУ�����δУ�꣬�Ҵ��ڳ���ģʽ
    return 1;
#endif
  
  return 0;
}
/**********************************************************************************
�������ܣ���ȡ���ѹ
��ڣ���
���ڣ����ѹ����λ����
**********************************************************************************/
FP32S Get_Un(void)
{  
  INT8U U_Spec;

  U_Spec=Get_SysVolt_Mode();
  return (U_CONST[U_Spec]);
}
/**********************************************************************************
�������ܣ���ȡ�����
��ڣ���
���ڣ����������λ����
**********************************************************************************/
FP32S Get_In(void)
{  
  INT8U I_Spec;

  I_Spec=Get_SysCurr_Mode();
  return (I_CONST[I_Spec]);
}

/**********************************************************************************
�������ܣ���ȡ������
��ڣ���
���ڣ����������λ����
**********************************************************************************/
FP32S Get_Imax(void)
{  
  INT8U I_Spec;

  I_Spec=Get_SysCurr_Mode();
  return (I_MAX_CONST[I_Spec]);
}
/**********************************************************************************
�������ܣ���ȡ��������
��ڣ���
���ڣ�������������λ����
**********************************************************************************/
FP32S Get_Start_Current(void)
{  
  INT8U I_Spec;

  I_Spec=Get_SysCurr_Mode();
  return ((FP32S)I_CONST[I_Spec]/I_START_RATIO);
}

/**********************************************************************************
�������ܣ���ȡ��������
��ڣ���
���ڣ���������
**********************************************************************************/
FP32S Get_Start_Power(void)
{  
  INT8U U_Spec,I_Spec;
  FP32S P;
  
  U_Spec=Get_SysVolt_Mode();
  I_Spec=Get_SysCurr_Mode();  
  
  P=(U_CONST[U_Spec]*I_CONST[I_Spec]/I_START_RATIO)*1000; //ת���� 0.000001kW=0.001w
  
  return P;
}
/**********************************************************************************
�������ܣ���ȡ����й�����/�޹�����
��ڣ���
���ڣ���λ��0.0001kw���� 0.0001kvar
//���ѹ�£�1.2Imax�������������
**********************************************************************************/
INT32U Get_Max_Power(void)
{  

  //return (INT32U)(Get_Un()*Get_Un()*U_RATE*I_RATE*10);  //0.1w ����0.1var
  return (INT32U)(Get_Un()*Get_Imax()*POWER_EXCEED_RATE*10);  //0.1w ����0.1var
}
/**********************************************************************************
�������ܣ�������ڼ���������ۼ����ݵļĴ���
��ڣ���
���ڣ�
**********************************************************************************/
void Clr_Energ_Accu(void)
{
   mem_set((void *)(&Pri_TempMeasuVar),
            0x00,
            sizeof(Pri_TempMeasuVar),
            (void *)(&Pri_TempMeasuVar),
            sizeof(Pri_TempMeasuVar));
    SET_STRUCT_SUM(Pri_TempMeasuVar);
    
#ifdef MEASURE_VAR_BAK_EN 
    mem_set((void *)(&Pri_TempMeasuVarBak1),
            0x00,
            sizeof(Pri_TempMeasuVarBak1),
            (void *)(&Pri_TempMeasuVarBak1),
            sizeof(Pri_TempMeasuVarBak1));
    SET_STRUCT_SUM(Pri_TempMeasuVarBak1);
  
      mem_set((void *)(&Pri_TempMeasuVarBak2),
            0x00,
            sizeof(Pri_TempMeasuVarBak2),
            (void *)(&Pri_TempMeasuVarBak2),
            sizeof(Pri_TempMeasuVarBak2));
    SET_STRUCT_SUM(Pri_TempMeasuVarBak2); 
#endif
    
    
    mem_set((void *)(&Energ_Err_Clr),
            0x00,
            sizeof(Energ_Err_Clr),
            (void *)(&Energ_Err_Clr),
            sizeof(Energ_Err_Clr));
    INIT_STRUCT_VAR(Energ_Err_Clr);  //��ͷβ����
    
    /*
    mem_set((void *)(&Cal_Proc_Status),
            0x00,
            sizeof(Cal_Proc_Status),
            (void *)(&Cal_Proc_Status),
            sizeof(Cal_Proc_Status));
    INIT_STRUCT_VAR(Cal_Proc_Status);  //��ͷβ����
    */
    
}
/**********************************************************************************
�������ܣ���ʼ���ڴ�
��ڣ���
���ڣ���
**********************************************************************************/
void Init_Private_Ram(void)
{
    mem_set((INT8U *)(&RstCtrlStatus),0x00,sizeof(RstCtrlStatus),(INT8U *)(&RstCtrlStatus),sizeof(RstCtrlStatus));  
    SET_STRUCT_SUM(RstCtrlStatus);


    mem_set((void *)(&MeasuPara_CS),0x00,sizeof(MeasuPara_CS),(void *)(&MeasuPara_CS),sizeof(MeasuPara_CS));  
    SET_STRUCT_SUM(MeasuPara_CS);
    
    mem_set((void *)(&MeasuStatusMode),\
            0x00,\
            sizeof(MeasuStatusMode),\
           (void *)(&MeasuStatusMode),\
             sizeof(MeasuStatusMode));
    SET_STRUCT_SUM(MeasuStatusMode);

  mem_set((void *)(&Pri_TempIntantVar),\
         0x00,\
         sizeof(Pri_TempIntantVar),\
         (void *)(&Pri_TempIntantVar),\
          sizeof(Pri_TempIntantVar));
  SET_STRUCT_SUM(Pri_TempIntantVar);
  
  
  mem_set((void *)(&Curr_Under_Istart),
          0x00,\
          sizeof(Curr_Under_Istart),\
         (void *)(&Curr_Under_Istart),\
          sizeof(Curr_Under_Istart));
  SET_STRUCT_SUM(Curr_Under_Istart);  
    
    
  mem_set((void *)(&Curr_1_Per_100),
          0x00,\
          sizeof(Curr_1_Per_100),\
         (void *)(&Curr_1_Per_100),\
          sizeof(Curr_1_Per_100));
  SET_STRUCT_SUM(Curr_1_Per_100);

  mem_set((void *)(&Curr_In_6_13x5),
          0x00,
          sizeof(Curr_In_6_13x5),\
         (void *)(&Curr_In_6_13x5),
         sizeof(Curr_In_6_13x5));
   SET_STRUCT_SUM(Curr_In_6_13x5);

  mem_set((void *)(&Curr_6_13x5_Slipe),
          0x00,
          sizeof(Curr_6_13x5_Slipe),
          (void *)(&Curr_6_13x5_Slipe),
          sizeof(Curr_6_13x5_Slipe));
  SET_STRUCT_SUM(Curr_6_13x5_Slipe);

  mem_set((void *)(&SpecChange_CurrFlag),
          0x00,
          sizeof(SpecChange_CurrFlag),
          (void *)(&SpecChange_CurrFlag),
          sizeof(SpecChange_CurrFlag));
  SET_STRUCT_SUM(SpecChange_CurrFlag);

  Clr_Energ_Accu();
 

  mem_set((INT8U *)(&Pri_MeasuStatVar),\
          0x00,\
           sizeof(Pri_MeasuStatVar),\
        (void *)(&Pri_MeasuStatVar),\
          sizeof(Pri_MeasuStatVar));
  SET_STRUCT_SUM(Pri_MeasuStatVar);

}
/**********************************************************************************
�������ܣ���ʼ���ڴ�
��ڣ���
���ڣ���
**********************************************************************************/
void Init_Public_Ram(void)
{
    mem_set((void *)(&Measu_Status_Mode_ToPub_PUCK),0x00,sizeof(Measu_Status_Mode_ToPub_PUCK),(void *)(&Measu_Status_Mode_ToPub_PUCK),sizeof(Measu_Status_Mode_ToPub_PUCK));
    SET_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);

    mem_set((void *)(&Measu_InstantData_ToPub_PUCK),0x00,sizeof(Measu_InstantData_ToPub_PUCK),(void *)(&Measu_InstantData_ToPub_PUCK),sizeof(Measu_InstantData_ToPub_PUCK));
    SET_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);

    mem_set((void *)(&Measu_Energ_ToPub_PUCK),0x00,sizeof(Measu_Energ_ToPub_PUCK),(void *)(&Measu_Energ_ToPub_PUCK),sizeof(Measu_Energ_ToPub_PUCK));
    SET_STRUCT_SUM(Measu_Energ_ToPub_PUCK);
  
    mem_set((void *)(&Measu_Sign_InstantData_PUCK),0x00,sizeof(Measu_Sign_InstantData_PUCK),(void *)(&Measu_Sign_InstantData_PUCK),sizeof(Measu_Sign_InstantData_PUCK));
    SET_STRUCT_SUM(Measu_Sign_InstantData_PUCK);
    
#ifdef VOLTANGLE_EN
  if(Pri_MeasuStatVar.ParaInit)
    mem_set(&App_VoltAngle_Struct,0x00,sizeof(App_VoltAngle_Struct),(void *)(&App_VoltAngle_Struct),sizeof(App_VoltAngle_Struct));
    SET_STRUCT_SUM(App_VoltAngle_Struct);
#endif
}
/**********************************************************************************
�������ܣ���ʼ������SRAM
��ڣ���
���ڣ���
**********************************************************************************/	
void Init_Measure_Ram(void)  //��Ҫ��Init_Low_Power_Proc()�����
{  
  Init_Interr_Sram();
  Init_Public_Ram();
  Init_Private_Ram();
  Init_All_Loss_Sram();  //��ʼ��ȫʧѹ
  Clr_All_Event_Sram();
}
/**********************************************************************************
�������ܣ���ȡ331����341��ʽ��������˫�������峣����񣬵�ѹ��񣬵������
��ڣ�Flag-------1:��ʼ����0---------------������
���ڣ���
**********************************************************************************/	
INT8U GetSysModeProc(void)
{
#ifdef SYS_MEASU_MARCO
  MeasuSysMode.ParseMode=SYS_PARSE_SPEC;
  MeasuSysMode.T_FH=SYS_THF_SPEC;
  MeasuSysMode.P_Spec=SYS_PULSE_TYPE;
  MeasuSysMode.V_Spec=SYS_VOLT_SPEC;
  MeasuSysMode.I_Spec=SYS_CURR_SPEC;
#else
  INT8U Flag;
  INT8U temp[3];
      
  //Flag=Read_Storage_Data_PUCK(DI_MODE1,temp,1);  //T_FHģʽ��
  MeasuSysMode.T_FH=TH_MODE;//GET_BIT(temp[0],6);        //T_FHģʽ��
  
  Flag=Read_Storage_Data_PUCK(DI_P_U_I_SPEC,temp,3);   
  MeasuSysMode.P_Spec=temp[2];
  MeasuSysMode.V_Spec=temp[1];
  MeasuSysMode.I_Spec=temp[0];
  
  if(MeasuSysMode.P_Spec>PULSE_TYPE2) //���ݳ��ޣ�����Ĭ�ϲ���
  {
    MeasuSysMode.P_Spec=DEFAULT_PULSE_SPEC;
    Debug_Print("Measure_Error----->MeasuSysMode.P_Spec Get Failed!");  
  }
  
  if(MeasuSysMode.V_Spec>VOLT_3380)   //���ݳ��ޣ�����Ĭ�ϲ���
  {
    MeasuSysMode.P_Spec=DEFAULT_VOLT_SPEC;
    Debug_Print("Measure_Error----->MeasuSysMode.V_Spec Get Failed!");  
  }
 
  if(MeasuSysMode.I_Spec>CURR_30_100)  //���ݳ��ޣ�����Ĭ�ϲ���
  {
    MeasuSysMode.I_Spec=DEFAULT_CURR_SPEC;
    Debug_Print("Measure_Error----->MeasuSysMode.I_Spec Get Failed!");  
  }


  if((MeasuSysMode.V_Spec==VOLT_3100)||(MeasuSysMode.V_Spec==VOLT_3380))
   MeasuSysMode.ParseMode=PARSE_331;
  else
   MeasuSysMode.ParseMode=PARSE_341;
 #endif 
  

  SET_STRUCT_SUM(MeasuSysMode);
  return Flag;  
}
/**********************************************************************************
�������ܣ���ȡ���������峣��
��ڣ���
���ڣ�
**********************************************************************************/
INT32U Get_Sys_Pulse(void)
{  
  INT8U PulseSpec,U_Spec,I_Spec;
  PulseSpec=Get_SysPulse_Mode();
  U_Spec=Get_SysVolt_Mode();
  I_Spec=Get_SysCurr_Mode();
  return(PULSE_CONST[PulseSpec][U_Spec][I_Spec]);
}


/**********************************************************************************
�������ܣ������ڿ�����ʼ���ڴ棬��ʼ����У������޹صĲ���
��ڣ���
���ڣ���
**********************************************************************************/
INT8U Init_Para(void)
{
  INT8U Flag;
 
  Flag=GetSysModeProc();        //��ȡϵͳ331/341ģʽ�֣���ѹ����������峣�����
  if(!Flag)
    Debug_Print("Measure_Error----->System Mode Para Get Failed!"); 
 
  Flag=Get_Pulse_Para();        //���޹����峣�����������������
  if(!Flag)
    Debug_Print("Measure_Error----->Pulse Para Get Failed!");
  return Flag;
}
/**********************************************************************************
�������ܣ�����A/B/C/��������ֵ:1~4
��ڣ���
���ڣ���
**********************************************************************************/
void	RefreshQuadrant(void)
{
  
  if((CHECK_STRUCT_SUM(Pri_MeasuStatVar)==0) || (CHECK_STRUCT_SUM(Pri_TempIntantVar)==0))
    ASSERT_FAILED();  
  
  Pri_TempIntantVar.Quadrant.A=GetQuadrant(Pri_MeasuStatVar.A_APwrDir,Pri_MeasuStatVar.A_RPwrDir);
  Pri_TempIntantVar.Quadrant.B=GetQuadrant(Pri_MeasuStatVar.B_APwrDir,Pri_MeasuStatVar.B_RPwrDir);
  Pri_TempIntantVar.Quadrant.C=GetQuadrant(Pri_MeasuStatVar.C_APwrDir,Pri_MeasuStatVar.C_RPwrDir);
  Pri_TempIntantVar.Quadrant.Sum=GetQuadrant(Pri_MeasuStatVar.SUM_APwrDir,Pri_MeasuStatVar.SUM_RPwrDir); 
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
}	

/**********************************************************************************
�������ܣ���ȡ����2��ĵ�ѹ�н�
��ڣ���
���ڣ�1------------��ȡ�ɹ���0-----------��ȡʧ��
**********************************************************************************/	
INT8U  GetVoltAngle_PUCK(void)
{
#ifdef VOLTANGLE_EN
  INT8U Flag,Reg;
  INT32U *Ptr,CurData;
  FP32S   temp;  
  
  Ptr=&(App_VoltAngle_Struct.AB);
  for(Reg=REG_R_AB_ANGLE;Reg<=REG_R_BC_ANGLE;Reg++,Ptr++)
  {
    Flag=Measu_RdAndCompData_3Times(Reg,(INT8U *)&CurData);  //��ȡ�н�
    if(!Flag)
      return 0;
    temp=(FP32S)CurData/8192;
    *Ptr=(INT32U)temp;
  }
#endif 
  return 1;
}

/**********************************************************************************
�������ܣ��ж��Ƿ������������
��ڣ���
���ڣ���
**********************************************************************************/
INT8U Judge_I_Start(void)
{
  INT32U MaxI;
  
  if(CHECK_STRUCT_SUM(Pri_TempIntantVar)==0)
    ASSERT_FAILED();
  
  
  MaxI=Get_Max_Num(Pri_TempIntantVar.Curr.A,Pri_TempIntantVar.Curr.B,Pri_TempIntantVar.Curr.C);
  if((FP32S)MaxI>=(Get_Start_Current()*UNIT_A))  //������������������
  return 1;
  
  return 0;    
}
/**********************************************************************************
�������ܣ�����,A,B,C�����
��ڣ���
���ڣ���
**********************************************************************************/
void	GetAllAngel_PUCK(void)
{
  INT8U Flag;
  
  Flag=Get_SysCurr_Mode();
  if(Judge_I_Start())  //������������������
  { 
    //A��
    Pri_TempIntantVar.Angle.A=GetAngle(Pri_TempIntantVar.Quadrant.A,Pri_TempIntantVar.ReacPower.A,Pri_TempIntantVar.AcPower.A,REG_R_ANGLE_A);
    if((FP32S)Pri_TempIntantVar.Curr.A<=(Get_Start_Current()*UNIT_A))   //A�������С����������ʱ�������ǿ����Ϊ0	
      Pri_TempIntantVar.Angle.A=0;
    
    //B��
    Pri_TempIntantVar.Angle.B=GetAngle(Pri_TempIntantVar.Quadrant.B,Pri_TempIntantVar.ReacPower.B,Pri_TempIntantVar.AcPower.B,REG_R_ANGLE_B);
    if((FP32S)Pri_TempIntantVar.Curr.B<=(Get_Start_Current()*UNIT_A))   //B�������С����������ʱ�������ǿ����Ϊ0	
      Pri_TempIntantVar.Angle.B=0;    

    //C��
    Pri_TempIntantVar.Angle.C=GetAngle(Pri_TempIntantVar.Quadrant.C,Pri_TempIntantVar.ReacPower.C,Pri_TempIntantVar.AcPower.C,REG_R_ANGLE_C);
    if((FP32S)Pri_TempIntantVar.Curr.C<=(Get_Start_Current()*UNIT_A))   //C�������С����������ʱ�������ǿ����Ϊ0	
      Pri_TempIntantVar.Angle.C=0;
    
    //����
    Pri_TempIntantVar.Angle.Sum=GetAngle(Pri_TempIntantVar.Quadrant.Sum,Pri_TempIntantVar.ReacPower.Sum,Pri_TempIntantVar.AcPower.Sum,REG_R_ANGLE_SUM);
  }                           
  else  //������С����������
  {
    //���з��������С����������ʱ���������ǿ����Ϊ0
    Pri_TempIntantVar.Angle.A=0;
    Pri_TempIntantVar.Angle.B=0;
    Pri_TempIntantVar.Angle.C=0;
    Pri_TempIntantVar.Angle.Sum=0;
  }
  
  Flag=Get_SysParse_Mode();
  if(Flag==PARSE_331)    //331ģʽ�� B���ѹ�����н�Ϊ0
    Pri_TempIntantVar.Angle.B=0;
  
   SET_STRUCT_SUM(Pri_TempIntantVar);
}

/**********************************************************************************
�������ܣ��й����޹����ʷ�����
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U Get_PQ_PowerDir_PUCK(void)
{
  INT8U Flag;
  INT32U RdData;
  INT8U *Ptr;
  
  Flag=Measu_RdAndCompData_3Times(REG_R_PQ_DIR,(INT8U *)&RdData);
  if(!Flag)
  {
    Debug_Print("Measure_Error----->Get PQ_Direction Error!");  
    return MEASU_RD3TIMES_ERR;
  }
  
  if(CHECK_STRUCT_SUM(Pri_MeasuStatVar)==0)
    ASSERT_FAILED();
  
  Ptr=(INT8U *)(&Pri_MeasuStatVar);
  Ptr++;
  mem_cpy(Ptr, (INT8U *)(&RdData),1,Ptr,1);
  
  SET_STRUCT_SUM(Pri_MeasuStatVar);
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ������ܵ��������������ܹ������������ݹ��ʷ��������ֵ������õ������͡�
          ע�����ǰ����õ���ȷ�õ����ʷ���
��ڣ�    PowerFlag-------���޹����ʷ��� 
          ParseFlag-------1��ʾ�޹���0��ʾ�й�
          Data------------���޹�����
         PowerOrEnerg-----���ʻ��ǵ��ܱ�־---0:����;1:����
���ڣ�1------------��ȡ�����ɹ���0-----------��ȡʧ��
**********************************************************************************/	
INT32U GetSumEngeOrPowerValue(INT8U PowerFlag,INT8U ParseFlag,MEASU_DATA Data,INT8U PowerOrEnerg)
{
  INT8U THF_Spec;
  INT32U PlusEnerg,NegaEnerg;
  
  PlusEnerg=0;
  NegaEnerg=0;

  //A��
  if(GET_BIT(PowerFlag,4*ParseFlag))
    NegaEnerg+=Data.A;
  else
    PlusEnerg+=Data.A;
  
  //B��
  if(GET_BIT(PowerFlag,1+4*ParseFlag))
    NegaEnerg+=Data.B;
  else
    PlusEnerg+=Data.B;
  
  //C��
   if(GET_BIT(PowerFlag,2+4*ParseFlag))
    NegaEnerg+=Data.C;
  else
    PlusEnerg+=Data.C;
  
  THF_Spec=Get_SysTHF_Mode();   
  if((PowerOrEnerg)&&(THF_Spec==TF_MODE))    //������ǵ��ܣ������ǵ�����
  {
    return (PlusEnerg+NegaEnerg);    
  }

  //���ʰ��մ����ͣ�˫��������������
  if(PlusEnerg>=NegaEnerg)
     return (PlusEnerg-NegaEnerg);
  else
     return (NegaEnerg-PlusEnerg); 
 
}

/**********************************************************************************
�������ܣ�����
��ڣ�    INT8U Clr_Energ_Reg(INT8U EngReg,INT8U Protect)
���ڣ�
**********************************************************************************/	
#define MAX_ENERG_ERR_TIME 3
INT8U Energ_Err_Reg_Proc(INT8U EngReg,INT8U Protect)
{
  INT8U Index;
  
  if(Protect !=0x9e)  //����һ�£���ֹ���룡
    return 0;
  /*
  if(CHECK_STRUCT_VAR(Energ_Err_Clr)) //ͷβ����
  {
    mem_set((void *)(&Energ_Err_Clr),
            0x00,
            sizeof(Energ_Err_Clr),
            (void *)(&Energ_Err_Clr),
            sizeof(Energ_Err_Clr));
    INIT_STRUCT_VAR(Energ_Err_Clr);
    ASSERT_FAILED(); 
  }
  */
  
  if(EngReg>=REG_R_A_P_ENERG && EngReg<=REG_R_SUM_P_ENERG)  //�й�
  {
    Index=EngReg-REG_R_A_P_ENERG;
    if(Energ_Err_Clr.AcEgErr[Index]>=MAX_ENERG_ERR_TIME)
    {
      Energ_Err_Clr.AcEgErr[Index]=0;
      return 1;      
    }
    Energ_Err_Clr.AcEgErr[Index]++;
    return 0;
  }
  
  if(EngReg>=REG_R_A_Q_ENERG && EngReg<=REG_R_SUM_Q_ENERG)  //�޹�
  {
    Index=EngReg-REG_R_A_Q_ENERG;
    if(Energ_Err_Clr.ReAcEgErr[Index]>=MAX_ENERG_ERR_TIME)
    {
      Energ_Err_Clr.ReAcEgErr[Index]=0;
      return 1;      
    }
    Energ_Err_Clr.ReAcEgErr[Index]++;
    return 0;
  }
  
  if(EngReg>=REG_R_A_PQS_ENERG && EngReg<=REG_R_SUM_PQS_ENERG)  //����
  {
    if(EngReg<=REG_R_C_PQS_ENERG)     //����
      Index=EngReg-REG_R_A_PQS_ENERG;
    else                              //����
      Index=3;
    
    if(Energ_Err_Clr.PQSEgErr[Index]>=MAX_ENERG_ERR_TIME)
    {
      Energ_Err_Clr.PQSEgErr[Index]=0;
      return 1;      
    }
    Energ_Err_Clr.PQSEgErr[Index]++;
    return 0;
  }  
  return 0;
}
/**********************************************************************************
�������ܣ����ܻ�ȡ��ȷ��������ܴ��������
��ڣ�    INT8U Energ_OK_Reg_Proc(INT8U EngReg,INT8U Protect)
���ڣ�
**********************************************************************************/	
void Energ_OK_Reg_Proc(INT8U EngReg,INT8U Protect)
{
 
  if(Protect !=0xE9)  //����һ�£���ֹ���룡
    return ;
  
  if(EngReg>=REG_R_A_P_ENERG && EngReg<=REG_R_SUM_P_ENERG)  //�й�
  {
      Energ_Err_Clr.AcEgErr[EngReg-REG_R_A_P_ENERG]=0;  
    return ;
  }
  
  if(EngReg>=REG_R_A_Q_ENERG && EngReg<=REG_R_SUM_Q_ENERG)  //�й�
  {
     Energ_Err_Clr.ReAcEgErr[EngReg-REG_R_A_Q_ENERG]=0;  
    return ;
  }
  
  if(EngReg>=REG_R_A_PQS_ENERG && EngReg<=REG_R_SUM_PQS_ENERG)  //����
  {
    if(EngReg<=REG_R_C_PQS_ENERG)     //����
    {
      Energ_Err_Clr.PQSEgErr[EngReg-REG_R_A_PQS_ENERG]=0;
    }
    else                              //����
    {
      Energ_Err_Clr.PQSEgErr[3]=0;
    }
  }  
}
/**********************************************************************************
�������ܣ�����ĳ���������
��ڣ���
���ڣ�0------------��ȡ�����ɹ���1--------------��ȡʧ��
**********************************************************************************/	
INT8U  GetEnergChangeValue_PerOne(INT8U EngReg,INT8U FlowFlag,volatile INT32U *CurrEnerg,volatile INT32U *LastEnerg,volatile INT32U *ChangEnerg,INT32U Power,INT32U Curr)
{
  INT8U Flag;
  INT32U LastData,ChangData,RdData;
  FP32S CurData;
   
   
  Flag=Measu_RdAndCompData_3Times(EngReg,(INT8U *)&RdData);  //��ȡ����
  if(!Flag)
    return MEASU_RD3TIMES_ERR;
    
  CurData=Get_Sys_Pulse();
  
  if(CurData==0)
    return MEASU_PUL_SPEC_ERR;
  
  CurData=UNIT_KWH_KVAR/CurData;  
  CurData=(FP32S)RdData*CurData;
  LastData=*LastEnerg;   //ȡ���ϴ�ֵ
  
  if(FlowFlag && CurData<=LastData)  //���
  {
    *CurrEnerg=(INT32U)CurData;
    *LastEnerg=(INT32U)CurData; 
    Debug_Print("Measure_Info----->Energy OverFlow:LastData=0x%lx,CurData=0x%lx,Chang=0x%lx",LastData,(INT32U)CurData,*ChangEnerg); 
    ChangData=(INT32U)((FP32S)0x1000000*UNIT_KWH_KVAR/Get_Sys_Pulse()+CurData-LastData); //��������
#ifdef MEASU_LIMITED_EN 
    if(ChangData>=MAX_ENG_RATE*Get_Un()*Get_In())   //�����������˴ε�����������
    {
      *ChangEnerg=0;
       Debug_Print("Measure_Error----->LastData=0x%lx,CurData=0x%lx,RdData=0x%lx,Energ Change Over Limited!",LastData,CurData,RdData);       
       return  MEASU_ENERG_FLOW_ERR;
    }
    else
      *ChangEnerg=ChangData;
#endif    
    return MEASU_NO_ERR;
  }
  
  
  if((INT32U)CurData>LastData) //���ζ����ĵ���>�ϴζ����ĵ���,˵���е��ܵ���------------PUCK
  {
    ChangData=(INT32U)(CurData-LastData);  //�ó������Ĳ���--------------PUCK
    
#ifdef MEASU_LIMITED_EN 
    if(ChangData>=MAX_ENG_RATE*Get_Un()*Get_In())   //�����������˴ε��������������������ݲ�������
    {
      /**CurrEnerg=(INT32U)CurData;
      *LastEnerg=(INT32U)CurData;
      *ChangEnerg=0;
      */ 
      Debug_Print("Measure_Error----->Energ Change Over Limited:LastData=%ld,CurData=%ld,RdData=0x%lx!",LastData,CurData,RdData);  
            
      return  MEASU_ACCU_FLOW_ERR;
    }
#endif

     LastData=(INT32U)CurData;      //�����ϴε���ֵ------------------PUCK
  }
  else if(CurData<LastData) //���ܵ��ߣ����߷�תʱ���ֶ����������½��룬�˴ζ�����------------PUCK
  {
    Debug_Print("Measure_Error----->Energ Reversed:LastData=%ld,CurData=%ld,RdData=%lx!",LastData,(INT32U)CurData,RdData);
    //*CurrEnerg=(INT32U)CurData;
    //*LastEnerg=(INT32U)CurData;   //�����ϴε���ֵ,���Ȿ���ܱ��ϴ�С------------------PUCK
    
    //09��09��24������-------------------PUCK
    
    if(Energ_Err_Reg_Proc(EngReg,0x9e))  //���� MAX_ENERG_ERR_TIME �ζ����ĵ��ܶ����ߣ�������ܼĴ�����
    {
      *CurrEnerg=0;
      *LastEnerg=0;   //�����ϴε���ֵ,���Ȿ���ܱ��ϴ�С------------------PUCK
      *ChangEnerg=0;
      Measu_RdData(EngReg+0x13);
      Measu_RdData(EngReg+0x13);
      Measu_RdData(EngReg+0x13);
      Debug_Print("Measure_Error----->Clear Energ Reg,Energ Loss!");
    }
    

    return MEASU_ENR_REDUCE_ERR;
  }
  else                                   //���ζ����ĵ��ܣ��ϴζ����ĵ��ܣ�˵�����ܵ���Ϊ0------------PUCK
  {
    ChangData=0;
  }
  /*
  2009��11��28�գ��ڽ������δ˴��룬�����ͻ����������ټƣ�
  if(EngReg>=REG_R_A_P_ENERG && EngReg<=REG_R_SUM_P_ENERG)  //�й�
  {
    if(ChangData>0)
    {
      if(Power<(INT32U)Get_Start_Power()/2)     //����С��������һ��
      {
        if((EngReg!=REG_R_SUM_P_ENERG && Curr <(INT32U)Get_Start_Current()/2) ||(EngReg==REG_R_SUM_P_ENERG)) //����:���ʺ͵���С��������һ��;����:����С��������һ��
        {
          *CurrEnerg=0;
          *LastEnerg=0;
          *ChangEnerg=0;
          Measu_RdData(EngReg+0x13);
          Measu_RdData(EngReg+0x13);
          Measu_RdData(EngReg+0x13);
          Debug_Print("Measure_Error----->Energ Changed With Creep Status,Reg=%d,Power=%ld,Curr=%ld",EngReg,Power,Curr);
          return MEASU_CREEP_ENERG_ADD;
        }
      }
    }    
  }
  */
  *CurrEnerg=(INT32U)CurData;
  *LastEnerg=LastData;
  *ChangEnerg=ChangData;
  
  Energ_OK_Reg_Proc(EngReg,0XE9);
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ���������й����޹����������ݵ�ǰ���ʷ��򣬵�ǰ���ܺ��ϴε��ܲ�ֵ���
��ڣ���
���ڣ�1------------��ȡ�����ɹ���0-----------��ȡʧ��
**********************************************************************************/	
INT8U GetParseEnergChangeValue_PUCK(void)
{
  INT8U Flag,i;
  INT32U EnergFlow;  
  
#ifdef MEASURE_ERROR_STATICS_EN
    INT32U LastValue;
#endif
    
  if(CHECK_STRUCT_SUM(Pri_TempMeasuVar)==0)
    ASSERT_FAILED(); 
  
  Flag=Measu_RdAndCompData_3Times(REG_R_ENFLAG,(INT8U *)&EnergFlow);  //��ȡ���ܼĴ�������״̬:�����־
  if((!Flag)||(EnergFlow==0xffffff)) //����״̬�Ĵ�������󣬶Ե��ܵ�Ӱ�죬��ֵ�����ܶ�Ϊ0xffffff
  {
    return MEASU_RD3TIMES_ERR;
  }
  
  if(GET_BIT(EnergFlow,16))           //�ж�Sflag.16״̬�Ƿ�Ϊ1�����ǣ����ʾУ������
  {
    MeasuStatusMode.CalReqstErr=1;   //У������
    SET_STRUCT_SUM(MeasuStatusMode);
    Debug_Print("Measure_Error----->Measu Cal Request During In Measure Circle");  
    return MEASU_CAL_ERR;
  }
  
  MeasuStatusMode.CalReqstErr=0;   //У������
  SET_STRUCT_SUM(MeasuStatusMode);
  //����3���ȡ����/�����й��������������
  for(i=0;i<4;i++)
  {
#ifdef MEASURE_ERROR_STATICS_EN   
    LastValue=*((&Pri_TempMeasuVar.AcEnerg.A)+i);
#endif
    
    Flag=GetEnergChangeValue_PerOne(REG_R_A_P_ENERG+i,GET_BIT(EnergFlow,i),(&Pri_TempMeasuVar.AcEnerg.A)+i,(&Pri_TempMeasuVar.Last_AcEnerg.A)+i,\
                                   (&Pri_TempMeasuVar.Change_AcEnerg.A)+i,*((&Pri_TempIntantVar.AcPower.A)+i),*((&Pri_TempIntantVar.Curr.A)+i));
#ifdef MEASURE_ERROR_STATICS_EN
    if(Get_Cal_Exsit() EQ 0)   //�����ϱ��¼�ʱ�����ǹ���״̬ʱ�������ж�2�ߵļ���ͣ�����̫��
    {
      if(*((&Pri_TempMeasuVar.Change_AcEnerg.A)+i)!=0)  //�е�������
      {
        if(*((&Pri_TempIntantVar.AcPower.A)+i)<(INT32U)Get_Start_Power()/2)  //С����
        {
          if((i!=3 && *((&Pri_TempIntantVar.Curr.A)+i) <(INT32U)Get_Start_Current()/2) ||(i==3)) //���ʺ͵���ͬʱС��������һ��,�����޵���
          {
            Measure_Err_Info.AcFlag=Flag;
            Measure_Err_Info.LastValue=LastValue;
            Measure_Err_Info.CurrValue=*((&Pri_TempMeasuVar.AcEnerg.A)+i);
            Measure_Err_Info.ChangeValue=*((&Pri_TempMeasuVar.Change_AcEnerg.A)+i);
            Debug_Print("Measure_Error----->Energ Changed With Creep Status Out Function!");
            Debug_Print("Power=%ld,Curr=%ld",*((&Pri_TempIntantVar.AcPower.A)+i),*((&Pri_TempIntantVar.Curr.A)+i));
            SET_STRUCT_SUM(Measure_Err_Info);
          }
        }
      }
      }
#endif
    
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get Ac_Energe Change Error,Index=%d",i);  
      SET_STRUCT_SUM(Pri_TempMeasuVar);  
      return Flag;
    }
  }
 
  //����3���ȡ����/�����޹��������������
  for(i=0;i<4;i++)
  {
    Flag=GetEnergChangeValue_PerOne(REG_R_A_Q_ENERG+i,GET_BIT(EnergFlow,4+i),(&Pri_TempMeasuVar.ReacEnerg.A)+i,(&Pri_TempMeasuVar.Last_ReacEnerg.A)+i,\
                                   (&Pri_TempMeasuVar.Change_ReacEnerg.A)+i,*((&Pri_TempIntantVar.ReacPower.A)+i),*((&Pri_TempIntantVar.Curr.A)+i));
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get Reac_Energe Change Error,Index=%d",i); 
      SET_STRUCT_SUM(Pri_TempMeasuVar);  
      return Flag;
    }
  }
  
#if APP_ENERG_EN >0 //��PQS���ڵ��ܱ�
  //����3���ȡ�������ڵ����������������
  for(i=0;i<3;i++)
  {
    Flag=GetEnergChangeValue_PerOne(REG_R_A_PQS_ENERG+i,GET_BIT(EnergFlow,4+i),(&Pri_TempMeasuVar.AppEnerg.A)+i,(&Pri_TempMeasuVar.Last_AppEnerg.A)+i,\
                                   (&Pri_TempMeasuVar.Change_AppEnerg.A)+i,*((&Pri_TempIntantVar.ReacPower.A)+i),*((&Pri_TempIntantVar.Curr.A)+i));
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get App_Energe Change Error,Index=%d",i);  
      SET_STRUCT_SUM(Pri_TempMeasuVar);  
      return Flag;
    }
  }
  //����1���ȡ�������ڵ����������������
  i=3;
  Flag=GetEnergChangeValue_PerOne(REG_R_SUM_PQS_ENERG,GET_BIT(EnergFlow,4+i),(&Pri_TempMeasuVar.AppEnerg.A)+i,(&Pri_TempMeasuVar.Last_AppEnerg.A)+i,\
                                   (&Pri_TempMeasuVar.Change_AppEnerg.A)+i,*((&Pri_TempIntantVar.ReacPower.A)+i),*((&Pri_TempIntantVar.Curr.A)+i));
  if(Flag!=MEASU_NO_ERR)
  {
    Debug_Print("Measure_Error----->Get App_Sum_Energe Change Error");  
    SET_STRUCT_SUM(Pri_TempMeasuVar);  
    return Flag;
  }
  
#endif 
  
  
  SET_STRUCT_SUM(Pri_TempMeasuVar);  
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ���������й����޹����������ݷ��๦�ʷ��򣬷������������TH/TFģʽ�����
��ڣ���
���ڣ�1------------��ȡ�����ɹ���0-----------��ȡʧ��
**********************************************************************************
INT8U GetSumEnergChangeValue_PUCK(void)
{
  INT8U PowerFlag;
  //���»�ȡ���й�����/�޹�����  
  PowerFlag=*(INT8U *)(&MeasuStatVar+2);    //���ʷ���
  Pri_TempMeasuVar.Change_AcEnerg.Sum=GetSumEngeOrPowerValue(PowerFlag,0,Pri_TempMeasuVar.Change_AcEnerg,1);
  Pri_TempMeasuVar.Change_ReacEnerg.Sum=GetSumEngeOrPowerValue(PowerFlag,1,Pri_TempMeasuVar.Change_ReacEnerg,1);
  return 1;
}
**********************************************************************************/	

/**********************************************************************************
�������ܣ���ȡĳ���ѹ��Чֵ��
��ڣ�
           Reg----------�Ĵ�����ַ
           VoltData------------Ŀ�껺����  
���ڣ�1----------��ȡ�ɹ���0----------��ȡʧ��
**********************************************************************************/	
INT8U GetVoltValue_PerOne(INT8U Reg,volatile INT32U *VoltData)
{
  INT8U volatile Flag;
  INT32U volatile RdData;
  FP32S  ResultData;

  
  Flag=Measu_RdAndCompData_3Times(Reg,(INT8U *)&RdData);
  if(!Flag)
      return MEASU_RD3TIMES_ERR;
      
  if(RdData>=0x00800000)
  {
    Debug_Print("Measure_Error----->Get Volt Error,RdData=0x%lx",RdData);  
    return MEASU_VOLT_ERR;
  }

  ResultData=(FP32S)RdData*(FP32S)UNIT_V/pow(2,13);
  RdData=(INT32U)ResultData;
  *VoltData=RdData;    
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ���ȡĳ�������Чֵ��
��ڣ�
           Reg----------�Ĵ�����ַ
           UorIflag-----------0����ѹ��1----����
           DstBuf------------Ŀ�껺����  
���ڣ�1----------��ȡ�ɹ���0----------��ȡʧ��
**********************************************************************************/	
INT8U GetCurrValue_PerOne(INT8U Reg,volatile INT32U *LastCur,volatile INT32U *CurrCur)
{
  INT8U volatile Flag,ParseSpec,ISpec;
  INT32U volatile RdData;
  INT32U LastData;
  FP32S  ResultData;

   
   LastData=*CurrCur;   //����ǰ��ֵ��Ϊ�ϴε�ֵ���棡
   
   Flag=Measu_RdAndCompData_3Times(Reg,(INT8U *)&RdData);
   if(!Flag)
     return MEASU_RD3TIMES_ERR;
      
   if(RdData>=0x00800000)
   {
     Debug_Print("Measure_Error----->Get Curr Error,RdData=0x%lx",RdData);  
     return MEASU_CURR_ERR;
   }
      
   ResultData=(FP32S)RdData*(FP32S)UNIT_A/pow(2,13);
   ISpec=Get_SysCurr_Mode();
   ResultData/=I_RATE_CONST[ISpec];        

   *LastCur=LastData;
   *CurrCur=(INT32U)ResultData;
   return MEASU_NO_ERR;      
}
/**********************************************************************************
�������ܣ���ȡA/B/C�ĵ�ѹ/������Чֵ��
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U GetVoltCurrValue_PUCK(void)
{
  INT8U Flag,i;
  
  if((CHECK_STRUCT_SUM(Pri_TempIntantVar)==0) ||(CHECK_STRUCT_SUM(Pri_TempMeasuVar)==0))
    ASSERT_FAILED();
  
  //��ȡ��ѹ+�����ѹ  
  for(i=0;i<4;i++)
  {
    if(3!=i)
      Flag=GetVoltValue_PerOne(REG_R_A_U+i,&(Pri_TempIntantVar.Volt.A)+i);
    else
      Flag=GetVoltValue_PerOne(REG_R_SUM_U,&(Pri_TempIntantVar.Volt.Sum));
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get Volt Error,Index=%d",i);
      SET_STRUCT_SUM(Pri_TempIntantVar);
      SET_STRUCT_SUM(Pri_TempMeasuVar);  
      return Flag;
    }    
  }
  
  //��ȡ�������+������� 
  for(i=0;i<4;i++)
  {
    Flag=GetCurrValue_PerOne(REG_R_A_I+i,(&Pri_TempMeasuVar.Last_Curr.A)+i,(&Pri_TempIntantVar.Curr.A)+i);
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get Curr Error,Index=%d",i); 
      SET_STRUCT_SUM(Pri_TempIntantVar);
      SET_STRUCT_SUM(Pri_TempMeasuVar);  
      return Flag;
    }   
  }
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
  SET_STRUCT_SUM(Pri_TempMeasuVar);  
  return MEASU_NO_ERR;      
}
/**********************************************************************************
�������ܣ�ÿ��ȡ�¶ȡ�
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U GetTemp_PUCK(void)
{
#if EXT_RTC_TYPE==DRV_SIMU_DS3231 || DRV_HARD_DS3231==1
  INT8U Flag;  
  static INT8U Cnt=65;
  INT8U temp[2];
  INT16S temp16s;
  
  if(Get_Cal_Exsit())   //�����ϱ��¼�ʱ�����ǹ���״̬ʱ�����ж�2�ߵļ���ͣ�����̫��
    return MEASU_NO_ERR;
  
  Cnt++;
  if(Cnt<65)    
    return MEASU_NO_ERR;
  
  Cnt=0;
  
  Flag=Read_EXT_RTC_Buf(0x11,2,temp);
  if(!Flag)
   return MEASU_TEMP_GET_ERR;
  
  Flag=temp[0];temp[0]=temp[1];temp[1]=Flag;
  temp16s=(*(INT16S *)temp);
  
  Pri_TempIntantVar.Temprate=(INT16S)(temp16s*0.390625);  //��λ:0.01��
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
#endif
  
  return MEASU_NO_ERR;
  //
}
/**********************************************************************************
�������ܣ���������๦�ʣ������й����ʡ������޹����ʡ��������ڹ���
��ڣ��� 
���ڣ���
**********************************************************************************/	
INT8U GetSumPowerValue_PerOne(void)
{
  INT8U PowerFlag;
  
  PowerFlag=*(INT8U *)(&Pri_MeasuStatVar+1);
  
  //�����й�
  Pri_TempIntantVar.AcPower.Sum=GetSumEngeOrPowerValue(PowerFlag,0,Pri_TempIntantVar.AcPower,0);
  
 //�����޹�
  Pri_TempIntantVar.ReacPower.Sum=GetSumEngeOrPowerValue(PowerFlag,1,Pri_TempIntantVar.ReacPower,0);
  
  //Measu_InstantData_ToPub_PUCK.AppPower.Sum=Measu_InstantData_ToPub_PUCK.AppPower.A+Measu_InstantData_ToPub_PUCK.AppPower.B+Measu_InstantData_ToPub_PUCK.AppPower.C;
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ���ȡ����
��ڣ�
      PowerReg--------���ʼĴ���
      SumFlag-------���ʱ�־,1------����;0--------���๦�ʣ�
      SFlag-------���ڹ��ʱ�־,1------���ڹ��ʱ�־;0--------�������ڹ��ʱ�־��
���ڣ�
**********************************************************************************/	
INT8U GetPowerValue_PerOne(INT8U PowerReg,INT8U SumFlag,volatile INT32U *CurrPower,INT8U SFlag)
{
  INT8U Flag;
  INT32U RdData,PulseConst;
  FP32S Result,temp;
  
  Flag=Measu_RdAndCompData_3Times(PowerReg,(INT8U *)&RdData);
  if(!Flag)
     return MEASU_RD3TIMES_ERR;
  
  
  PulseConst=Get_Sys_Pulse();
  
  //SOURCE CODE  125 5001 
  //�й�����λΪk,0.000001kw=0.001w/var������оƬ���ĵ�λ��w/var��3200/256*1000=12500;3200/64*1000=50000;
  if(SumFlag==1)  //����
  {
    temp=3.2/64*UNIT_KW_KAR;
  }
  else
  {
    temp=3.2/256*UNIT_KW_KAR;
  }
  if(RdData>0x00800000)
  {
    if(SFlag)  //���ڹ��ʲ�����Ϊ��
    {
      Debug_Print("Measure_Error----->App Power Is Negative,ReadValue=0x%lx",RdData);  
      return MEASU_POWER_ERR;
    }
    Result=(FP32S)(0x1000000-RdData)*temp;
    Result/=(FP32S)PulseConst;
  }
  else if(RdData==0x00800000)
  {
    Result=0;
  }
  else
  {
    Result=(FP32S)RdData*temp;
    Result/=(FP32S)PulseConst;
  }

  *CurrPower=(INT32U)Result;
    return MEASU_NO_ERR;   
}
/**********************************************************************************
�������ܣ���ȡA/B/C/�����й�����,�޹�����,���ڹ���,����С�����µĹ��ʷ�������С����ֵ��
��ڣ���
���ڣ�1---------�ɹ���0-----------ʧ��
**********************************************************************************/	
INT8U GetAllPowerValue_PUCK(void)
{
  INT8U Flag,i;

  if(CHECK_STRUCT_SUM(Pri_TempIntantVar)==0)
    ASSERT_FAILED(); 
  
 //A���й�����,�޹�����,���ڹ���
   for(i=0;i<3;i++)
   {
    Flag=GetPowerValue_PerOne(REG_R_A_AP+4*i,0,(&(Pri_TempIntantVar.AcPower.A)+4*i),i/2);
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get A_Power Error,Inde=%d",i);  
      SET_STRUCT_SUM(Pri_TempIntantVar);
      return Flag;
    }      
   } 

 
 //B���й�����,�޹�����,���ڹ���
   for(i=0;i<3;i++)
   {
    Flag=GetPowerValue_PerOne(REG_R_B_AP+4*i,0,(&(Pri_TempIntantVar.AcPower.B)+4*i),i/2);
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get B_Power Error,Inde=%d",i); 
      SET_STRUCT_SUM(Pri_TempIntantVar);
      return Flag;
    }      
   }   


 //C���й�����,�޹�����,���ڹ���
   for(i=0;i<3;i++)
   {
      Flag=GetPowerValue_PerOne(REG_R_C_AP+4*i,0,(&(Pri_TempIntantVar.AcPower.C)+4*i),i/2);
      if(Flag!=MEASU_NO_ERR)
      {
        Debug_Print("Measure_Error----->Get C_Power Error,Inde=%d",i); 
        SET_STRUCT_SUM(Pri_TempIntantVar);
        return Flag;
      }      
   } 

    
 //�����й�/�޹�/���ڹ���
 for(i=0;i<3;i++)
 {
    Flag=GetPowerValue_PerOne(REG_R_SUM_AP+4*i,1,(&(Pri_TempIntantVar.AcPower.Sum)+4*i),i/2);
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get Sum_Power Error,Inde=%d",i);  
      SET_STRUCT_SUM(Pri_TempIntantVar);
      return Flag;
    }      
 }  
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ��๦������
��ڣ�
      PowerReg----------���������Ĵ���
���ڣ�MEASU_NO_ERR---------�ɹ���-----------ʧ��
**********************************************************************************/	
INT8U GetPowerFactorValue_PerOne(INT8U Reg,volatile INT32U *DstPower)
{
  INT8U Flag;
  INT32U volatile RdData;
  FP32S Result;
  
  Flag=Measu_RdAndCompData_3Times(Reg,(INT8U *)&RdData);
  if(!Flag)
    return MEASU_RD3TIMES_ERR;
  
  //��λΪ1,ʵ����0.0000001,������1000000��ϵ����1000000/2^23=31250/262144=1/8.388608������0.000001
  if(RdData>0x00800000)
    Result=((FP32S)0x01000000-(FP32S)RdData);
  else
    Result=(FP32S)RdData;    
  
  Result=Result*UNIT_FACTOR/pow(2,23);
    
  *DstPower=(INT32U)Result;
  return MEASU_NO_ERR;      
}
/**********************************************************************************
�������ܣ���ȡA/B/C/����Ĺ���������
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U GetAllPowerFactorValue_PUCK(void)
{
  INT8U Flag,i;
  INT32U volatile *Ptr;
  
  if(CHECK_STRUCT_SUM(Pri_TempIntantVar)==0)
    ASSERT_FAILED();
  
  for(i=0;i<4;i++,Ptr++)
  {    
    Flag=GetPowerFactorValue_PerOne(REG_R_A_PF+i,&(Pri_TempIntantVar.PFactor.A)+i);
    if(Flag!=MEASU_NO_ERR)
    {
      Debug_Print("Measure_Error----->Get Power Factor Err,Index=%d!",i); 
      SET_STRUCT_SUM(Pri_TempIntantVar);
      return Flag;
    }
  }   
  SET_STRUCT_SUM(Pri_TempIntantVar);
  return MEASU_NO_ERR;      
}
/**********************************************************************************
�������ܣ���ȡ��Ƶ�ʡ�
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U GetFreqValue_PUCK(void)
{
  INT8U Flag;
  INT32U RdData;
  FP32S Result;
  
  Flag=Measu_RdAndCompData_3Times(REG_R_SUM_FREQ,(INT8U *)&RdData);
  if(!Flag)
      return MEASU_RD3TIMES_ERR;
  
  if(RdData>=0x00800000)
  {
      Debug_Print("Measure_Error----->Get Frequecy Err,Value too much(Value=0x%lx)",RdData);  
      return MEASU_FREQU_ERR;
  }
  
  if(CHECK_STRUCT_SUM(Pri_TempIntantVar)==0)
    ASSERT_FAILED();
  
  Result=(FP32S)RdData*UNIT_HZ/pow(2,13);
  
  //ע��:��Ҫ���Ӹ�ʽת������,����ʱ��!
  //add code ......................
  Pri_TempIntantVar.Freq.A=(INT32U)Result;
  Pri_TempIntantVar.Freq.B=(INT32U)Result;
  Pri_TempIntantVar.Freq.C=(INT32U)Result; 
  Pri_TempIntantVar.Freq.Sum=(INT32U)Result; 
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ��������״̬�֡�ע��ֻ�е��������⹦����Ҫͨ��������ʹ�ܿ��ƼĴ���EnDtIorder���俪��
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U GetSeqErrFlagValue_PUCK(void)
{
  INT8U Flag;
  INT32U RdData;
  
  Flag=Measu_RdAndCompData_3Times(REG_R_SIG,(INT8U *)&RdData);
  if(!Flag)
    return MEASU_RD3TIMES_ERR;
  
  if(CHECK_STRUCT_SUM(Pri_MeasuStatVar)==0)
    ASSERT_FAILED();
  
  /*
  if(RdData>=0x00800000)
    return 0;
  */  
  
  if(GET_BIT(RdData,7))  //SIG�ź�Ϊ�ߣ��쳣
  {
    Debug_Print("Measure_Error----->MeasuIC SIG_Signal=0��RdData=0x%lx!",RdData); 
    return MEASU_SIGN_ERR;
  }
  
  Pri_MeasuStatVar.V_SeqErr=(GET_BIT(RdData,3))?1:0;
  Pri_MeasuStatVar.I_SeqErr=(GET_BIT(RdData,4))?1:0;
  
  Pri_MeasuStatVar.A_Creep=(GET_BIT(RdData,9))?1:0;
  Pri_MeasuStatVar.B_Creep=(GET_BIT(RdData,10))?1:0;
  Pri_MeasuStatVar.C_Creep=(GET_BIT(RdData,11))?1:0;
  
  SET_STRUCT_SUM(Pri_MeasuStatVar);
  return MEASU_NO_ERR;
}
/**********************************************************************************
�������ܣ���������У��
��ڣ���
���ڣ���
**********************************************************************************/										 											 
void Power_Factor_Modi_PUCK(void)
{
#ifdef  POWER_FACTOR_ADJ

  INT8U i,U_Spec;
  
  if(CHECK_STRUCT_SUM(Pri_TempIntantVar)==0)
    ASSERT_FAILED();
  
  U_Spec=Get_SysVolt_Mode();
  
  for(i=0;i<3;i++)   //���๦������
  {
    if(*(&(Pri_TempIntantVar.Volt.A)+i)<LITTLE_VOLT[U_Spec])
      *(&(Pri_TempIntantVar.PFactor.A)+i)=0;
    if(*(&(Pri_TempIntantVar.Curr.A)+i)<=(Get_Start_Current()*UNIT_A))   //ֻҪ�е���
      *(&(Pri_TempIntantVar.PFactor.A)+i)=UNIT_FACTOR;
  }  
  
  //���๦������
  //��ѹ��С����С��ѹ������������0��
  if(Get_Max_Num(Pri_TempIntantVar.Volt.A,Pri_TempIntantVar.Volt.B,Pri_TempIntantVar.Volt.C)<LITTLE_VOLT[U_Spec])
    Pri_TempIntantVar.PFactor.Sum=0;
  
  //������С������������ѹ������������1��
  if(Get_Max_Num(Pri_TempIntantVar.Curr.A,Pri_TempIntantVar.Curr.B,Pri_TempIntantVar.Curr.C)<=(Get_Start_Current()*UNIT_A))
    Pri_TempIntantVar.PFactor.Sum=UNIT_FACTOR;
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
  
#endif  
}        
/**********************************************************************************
С����,����ر�־
**********************************************************************************/	
void Set_Little_Cur_Flag(void)
{
#ifdef LITTLE_CURR_ADJ
  INT8U I_Spec,ParseSpec,i;
  volatile INT32U *Ptr32,*LastCur;
  
  if(CHECK_STRUCT_SUM(Pri_TempIntantVar)==0)
   ASSERT_FAILED(); 
  
  I_Spec=Get_SysCurr_Mode();
  for(i=0;i<3;i++)
  {
    Ptr32=&(Pri_TempIntantVar.Curr.A)+i;
    LastCur=&(Measu_InstantData_ToPub_PUCK.Curr.A)+i;
    if(*Ptr32<=CUR_1_PER_100[I_Spec])  //[0,15]mA
    {
       *(&Curr_1_Per_100.A+i)=1;
       
       if(*Ptr32<=(Get_Start_Current()*UNIT_A))          //С�����������ģ�[0,0.1%In)mA����[0��0.75mA]
         *(&Curr_Under_Istart.A+i)=1;
       else
         *(&Curr_Under_Istart.A+i)=0; 
       
       if((*Ptr32>=(Get_Start_Current()*UNIT_A))&&(*Ptr32<=Current_down_setup[I_Spec]))   //[0.1%In,6]mA
         *(&Curr_1P100_Bad.A+i)=1;
       else
         *(&Curr_1P100_Bad.A+i)=0;
          
       if((*Ptr32>Current_down_setup[I_Spec])&&(*Ptr32<Current_up_setup[I_Spec]))  //(6,13.5)mA�����ε���
       {
          *(&Curr_In_6_13x5.A+i)=1;
          if((*LastCur>=Current_down_setup[I_Spec])&&(*LastCur<=Current_up_setup[I_Spec]))  //�ϴε�����Ҳ��(6,13.5)mA����
            *(&Curr_6_13x5_Slipe.A+i)=0;   //һֱ���� (6,13.5)mA����
          else
            *(&Curr_6_13x5_Slipe.A+i)=1;   //�ոս��� (6,13.5)mA����
       }
       else                                                                              //[13.5,15]mA�����ε������˳�(6,13.5)mA����
       {
         *(&Curr_In_6_13x5.A+i)=0;
         if((*LastCur>Current_down_setup[I_Spec])&&(*LastCur<Current_up_setup[I_Spec]))   //�ϴε�������(6,13.5)mA����
            *(&Curr_6_13x5_Slipe.A+i)=1;   //���˳�(6,13.5)mA����
         else
           *(&Curr_6_13x5_Slipe.A+i)=0;    //һֱ���� (6,13.5)mA����֮��
       }
    }
    else                                                                
    {
      *(&Curr_Under_Istart.A+i)=0; 
      *(&Curr_1_Per_100.A+i)=0;   //(15,max]mA
      *(&Curr_1P100_Bad.A+i)=0;
      *(&Curr_In_6_13x5.A+i)=0;
      *(&Curr_6_13x5_Slipe.A+i)=0;
    }
  }
  
  ParseSpec=Get_SysParse_Mode();
  if(ParseSpec==PARSE_331)
    Curr_1_Per_100.B=0; 
  
  SET_STRUCT_SUM(Pri_TempIntantVar);
  SET_STRUCT_SUM(Curr_1_Per_100);
  SET_STRUCT_SUM(Curr_In_6_13x5);
  SET_STRUCT_SUM(Curr_6_13x5_Slipe);  
#endif
}
/**********************************************************************************
�������ܣ���С�����£��Ե������й����ʣ��޹����ʣ����ڹ��ʣ�������У��
��ڣ���
���ڣ���
**********************************************************************************/									 											 
void Power_Volt_Curr_Modi_PUCK(void)
{
  INT8U Flag,i;
  INT8U U_Spec,I_Spec;
  INT32U TempCurr;
  FP32S tempPQS,temp;
  
  Flag=CHECK_STRUCT_SUM(Pri_TempMeasuVar);
  Flag&=CHECK_STRUCT_SUM(Pri_TempIntantVar);
  Flag&=CHECK_STRUCT_SUM(Pri_MeasuStatVar);
  Flag&=CHECK_STRUCT_SUM(Curr_1_Per_100);
  Flag&=CHECK_STRUCT_SUM(Curr_1_Per_100);
  
  if(Flag EQ 0)
    ASSERT_FAILED();
  
  U_Spec=Get_SysVolt_Mode();
  I_Spec=Get_SysCurr_Mode();
  
  /*
  for(i=0;i<4;i++)  //������������Ĵ���
  {
    if(*(&Curr_1_Per_100.A+i)==1 && *(&Curr_Under_Istart.A+i)==1)   //С�������Ҵ��� 0.1Ib����
    {
      ;//  *(&(Pri_TempIntantVar.Curr.A)+i)=0;   //С������������ǿ�ƽ�������0
    }
  }
  
  for(i=0;i<4;i++)  //������������Ĵ���
  {
    if(*(&Curr_1_Per_100.A+i)==1 && *(&Curr_1P100_Bad.A+i)==1)   //С�������Ҵ���[0.1%In,6]mA����
    {
      ;//  *(&(Pri_TempIntantVar.Curr.A)+i)=0;   //С������������ǿ�ƽ�������0
    }
  }
  

    
  for(i=0;i<4;i++)  //������������Ĵ���
  {
    if(*(&Curr_1_Per_100.A+i)==1 && *(&Curr_In_6_13x5.A+i)==1  && *(&Curr_6_13x5_Slipe.A+i)==1)   //С�������ս��� [6,13.5]mA����
    {
      ;//  *(&(Pri_TempIntantVar.Curr.A)+i)=8;   //
    }
  }
  
  */
    
  for(i=0;i<3;i++)
  {
    if(*(&Curr_1_Per_100.A+i)==1)
    {
      //С��������£�����P Q������ڹ���
      TempCurr=*(&Pri_TempIntantVar.Curr.A+i); //����ȡ��������� 09-02-05
      temp=pow(*(&Pri_TempIntantVar.AcPower.A+i),2);
      tempPQS=temp+pow(*(&Pri_TempIntantVar.ReacPower.A+i),2);
      tempPQS=sqrt(tempPQS);
      *(&Pri_TempIntantVar.AppPower.A+i)=(INT32U)tempPQS;
      
      if(*(&Pri_TempIntantVar.Volt.A+i)>=LITTLE_VOLT[U_Spec])  //�е�ѹ����С����
      {
        tempPQS=tempPQS/1000;    //ת�ɵ�λ��w 
        TempCurr=(INT32U)((tempPQS/((FP32S)(*(&Pri_TempIntantVar.Volt.A+i))/(FP32S)UNIT_V))*(FP32S)UNIT_A);     //��ѹ�Ѿ�ȷ��>0,�������
        if(TempCurr>Current_threshold_reset[I_Spec])   //����ĵ��������������ĵ�������0
          TempCurr=0;
        *(&(Pri_TempIntantVar.Curr.A)+i)=TempCurr; //���µ��� -----09-04-19  PUCK      
      }
      if(*(&Curr_In_6_13x5.A+i)==1)
      ;     
    
      if(TempCurr<=(Get_Start_Current()*UNIT_A))//�����������ڣ��С��޹�����,���ʷ���
      {
        *(&Pri_TempIntantVar.AppPower.A+i)=0;
        *(&Pri_TempIntantVar.ReacPower.A+i)=0;
        if(i==0)
          Pri_MeasuStatVar.A_APwrDir=Pri_MeasuStatVar.A_RPwrDir=0;
        if(i==1)
          Pri_MeasuStatVar.B_APwrDir=Pri_MeasuStatVar.B_RPwrDir=0;
        if(i==2)
          Pri_MeasuStatVar.C_APwrDir=Pri_MeasuStatVar.C_RPwrDir=0;
      }      
    }
  }
  
  
   
 //С��������£������й����ʣ������޹����ʣ��������ڹ�������
 if((Curr_1_Per_100.A)||(Curr_1_Per_100.B)||(Curr_1_Per_100.C))
 {
   if((Pri_MeasuStatVar.A_APwrDir==0)&&(Pri_MeasuStatVar.B_APwrDir==0)&&(Pri_MeasuStatVar.C_APwrDir==0))
    Pri_MeasuStatVar.SUM_APwrDir=0;
   
   if((Pri_MeasuStatVar.A_RPwrDir==0)&&(Pri_MeasuStatVar.B_RPwrDir==0)&&(Pri_MeasuStatVar.C_RPwrDir==0))
    Pri_MeasuStatVar.SUM_RPwrDir=0;
   
   Flag=GetSumPowerValue_PerOne();  
   if(Flag!=MEASU_NO_ERR)
   {
      Debug_Print("Measure_Error----->Get Ac/Reac/App_Power_Sum Error Under Tiny Current!");  
   }
  }
   
  SET_STRUCT_SUM(Curr_1_Per_100);
  SET_STRUCT_SUM(Pri_MeasuStatVar);
  SET_STRUCT_SUM(Pri_TempIntantVar);
  SET_STRUCT_SUM(Pri_TempMeasuVar);
}

/**********************************************************************************
�������ܣ����ʷ���У��
��ڣ���
���ڣ���
**********************************************************************************/										 											 
void Power_Direc_Modi_PUCK(void)
{
  INT8U ParseMode;
  FP32S P,Q;
  
  if(CHECK_STRUCT_SUM(Pri_MeasuStatVar)==0)
    ASSERT_FAILED();
  
  ParseMode=Get_SysParse_Mode();
  
  P=Get_Start_Power();
  Q=P;

  if(ParseMode==PARSE_331)        //331
  { 
    if((FP32S)Pri_TempIntantVar.AcPower.Sum<P) //����С�� ��������
      Pri_MeasuStatVar.SUM_APwrDir=0;         //���й���������
    if((FP32S)Pri_TempIntantVar.ReacPower.Sum<Q)//����С�� ��������
      Pri_MeasuStatVar.SUM_RPwrDir=0;         //���޹���������
  }
  else                             //341
  {   
    if(Pri_TempIntantVar.AcPower.Sum<(1.5L*P))//����С�� ��������
      Pri_MeasuStatVar.SUM_APwrDir=0;          //���й��������� 
    if(Pri_TempIntantVar.ReacPower.Sum<(1.5L*Q))//����С�� ��������
      Pri_MeasuStatVar.SUM_RPwrDir=0;         //���޹���������
  }
  
  if((FP32S)Pri_TempIntantVar.AcPower.A<P)//����С�� ��������
    Pri_MeasuStatVar.A_APwrDir=0;         //A���й��������� 
  if((FP32S)Pri_TempIntantVar.ReacPower.A<Q)//����С�� ��������
    Pri_MeasuStatVar.A_RPwrDir=0;        //A���޹���������
  
  if((FP32S)Pri_TempIntantVar.AcPower.B<P)//����С�� ��������
    Pri_MeasuStatVar.B_APwrDir=0;       //B���й���������
  if((FP32S)Pri_TempIntantVar.ReacPower.B<Q)//����С�� ��������
    Pri_MeasuStatVar.B_RPwrDir=0;       //B���޹���������
  
  if((FP32S)Pri_TempIntantVar.AcPower.C<P)//����С�� ��������
    Pri_MeasuStatVar.C_APwrDir=0;       //C���й���������
  if((FP32S)Pri_TempIntantVar.ReacPower.C<Q)//����С�� ��������
    Pri_MeasuStatVar.C_RPwrDir=0;       //C���޹���������
  SET_STRUCT_SUM(Pri_MeasuStatVar);
}

/**********************************************************************************        
�������ܣ�С������������
��ڣ���
���ڣ���

void TinyCurrDisProc_PUCK(void)
{
  INT32U volatile *LastPtr,*CurPtr;
  INT32U temp,TempData;
  INT8U i;
  
  i=CHECK_STRUCT_SUM(Pri_TempMeasuVar);
  ASSERT(1==i);  
  
  
  LastPtr=&(Pri_TempMeasuVar.Last_Curr.A);
  CurPtr=&(Pri_TempIntantVar.Curr.A);
  
  for(i=0;i<3;i++)  //A/B/C�����������
  {
    temp=LastPtr[i];
    if(temp!=0)  //�ϴζ�ȡ������Ϊ0
    {    
      TempData=CurPtr[i]/temp;
      if(TempData>100)  //���������������ǰ�����������ϴε�100����ʵ�ʵ���=0
      {
        LastPtr[i]=CurPtr[i];
        CurPtr[i]=0;      
      }
      else            //����������������ǰ�����������ϴε�����������
      {
        LastPtr[i]=CurPtr[i];
      }
    }
    else             //�ϴζ�ȡ����Ϊ0
    {
      if(CurPtr[i]>=100)  //��������������ϴζ�ȡ����Ϊ0����ǰ��ȡ�ĵ�������10mA
      {
         LastPtr[i]=CurPtr[i];
         //CurPtr[i]=0; 
      }
      else                //���������������ϴζ�ȡ����Ϊ0����ǰ��ȡ�ĵ���С��10mA
      {
        LastPtr[i]=CurPtr[i];
      }
    }
  }
 SET_STRUCT_SUM(Pri_TempMeasuVar);
 SET_STRUCT_SUM(Pri_TempIntantVar);
}
**********************************************************************************/	
/**********************************************************************************
�������ܣ�С��������������,ʹ֮��С��������¼�������
��ڣ���
���ڣ���

void Modi_StartCurr_TinyCurr(void)
{
  INT8U Flag;
  
  Flag=CHECK_STRUCT_SUM(Curr_6_13x5_Slipe);
  Flag&=CHECK_STRUCT_SUM(Curr_In_6_13x5);
  ASSERT(1==Flag); 
  
  if((Curr_6_13x5_Slipe.A==1)||(Curr_6_13x5_Slipe.B==1)||(Curr_6_13x5_Slipe.C==1))
  {
    EnMeasuCal();
    if((Curr_In_6_13x5.A==1)||(Curr_In_6_13x5.B==1)||(Curr_In_6_13x5.C==1))
    {
      Flag=Measu_WrAndCompData_3Times(REG_W_ISTART,0);
      if(Flag)
        Debug_Print("Clear StartCurr Para OK In Little Curr!");
      else
        Debug_Print("Clear StartCurr Para Failed In Little Curr!");
    }
    else   
    {
      //Flag=Check_MeasuParaBuf_Sum3();
      //Flag&=Measu_WrAndCompData_3Times(REG_W_ISTART,Measu_ParaBuf[MEASU_PARA_CURSTART]);
      if(Flag)
      {
        Debug_Print("Restore StartCurr Para Succeed In Little Curr!");  
      }
      else
        Debug_Print("Restore StartCurr Para Failed In Little Curr!");  
    }
    DisMeasuCal();

    if(Flag)  //���ò��ɹ����´λ�Ҫ��������
    {
      Curr_6_13x5_Slipe.A=0;
      Curr_6_13x5_Slipe.B=0;
      Curr_6_13x5_Slipe.C=0;
    }
  }
  SET_STRUCT_SUM(Curr_6_13x5_Slipe);
}
**********************************************************************************/	
/**********************************************************************************
�������ܣ�ÿ���7022���ݣ��õ���ǰ��˲ʱ����
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U  GetMeasuData_PerSec(void)
{
  INT8U Flag;
    
  Flag=ChkMeasuICWorkStatus();  //���SIG�ź�
  if(Flag!=MEASU_NO_ERR)
    return Flag;
  
  Flag=CheckBothCs();           //������оƬCS��EPPROM cs�Ƿ����
  if(Flag!=MEASU_NO_ERR)
    return Flag;   
  
  Flag=GetTemp_PUCK();           //��ȡ�¶�
  if(Flag!=MEASU_NO_ERR)
    return Flag;   
  
    
  Flag=GetVoltCurrValue_PUCK();          //��ȡA/B/C�ĵ�ѹ/������Чֵ��25ms
  if(Flag!=MEASU_NO_ERR)
    return Flag;  
  Set_Little_Cur_Flag();                //С����,����ر�־-----------------------PUCK
  
  //OS_TimeDly_Ms(20); 
  
  Flag=Get_PQ_PowerDir_PUCK();           //�й����޹����ʷ�����
  if(Flag!=MEASU_NO_ERR)
    return Flag;
  
  
  //OS_TimeDly_Ms(20); 
  
  Flag=GetAllPowerValue_PUCK();         //��ȡA/B/C/�����й�����,�޹�����,���ڹ���.30ms
  if(Flag!=MEASU_NO_ERR)
    return Flag;  
  
  Flag=GetAllPowerFactorValue_PUCK();   //��ȡA/B/C/����Ĺ�������.16ms
  if(Flag!=MEASU_NO_ERR)
    return Flag;  
  
  Flag=GetFreqValue_PUCK();             //��ȡ��Ƶ��
  if(Flag!=MEASU_NO_ERR)
    return Flag;
  
  Flag=GetSeqErrFlagValue_PUCK();       //��������ʾ
  if(Flag!=MEASU_NO_ERR)
    return Flag;
  
  Power_Volt_Curr_Modi_PUCK();        //С�����¹��ʡ���ѹ����������-----------------------PUCK   
  Power_Factor_Modi_PUCK();           //������������-----------------------PUCK  
  Power_Direc_Modi_PUCK();            //���ʷ�������-----------------------PUCK
  
  //OS_TimeDly_Ms(20);   
   RefreshQuadrant();                 //��������   
   GetAllAngel_PUCK();                //��ȡ��,A,B,C�ĵ�ѹ�������
  
   Flag=GetParseEnergChangeValue_PUCK();  //��ȡУ�������־�������й����޹�����.24ms
   if(Flag!=MEASU_NO_ERR)
    return Flag;
   
  
  //OS_TimeDly_Ms(20); 
   
 
#ifdef Measu_VOLTANGLE_EN
   GetVoltAngle_PUCK();               //��ȡ����2��ĵ�ѹ�н�
#endif

  Self_Cal_Proc();
  return MEASU_NO_ERR;  
}

/**********************************************************************************
�������ܣ����7022�������ޣ���7022����ת�������ύӦ�ò�
��ڣ���
���ڣ�MEASU_NO_ERR-------��ȡ�ɹ���----------��ȡʧ��
**********************************************************************************/						
INT8U ChkPowerLimitAndConvertData(void)
{
  INT32U Flag,ParseSpec,temp;
  INT8U i;
  INT32U volatile *PtrSrc,*PtrDst;
  
  
  /*************************���´���˲ʱ����********************************/
  Flag=CHECK_STRUCT_SUM(Pri_TempIntantVar);
  Flag&=CHECK_STRUCT_SUM(Pri_MeasuStatVar);
  if(Flag EQ 0)
  ASSERT_FAILED();

  Flag=MEASU_NO_ERR;
  ParseSpec=Get_SysParse_Mode();
  
  //�й����ʣ��޹����ʣ����ڹ��ʣ�4*3=12
  PtrSrc=&(Pri_TempIntantVar.AcPower.A);
  PtrDst=&(Measu_InstantData_ToPub_PUCK.AcPower.A);
  for(i=0;i<12;i++) 
  {
    if((i==3)||(i==7)||(i==11))
      temp=3;
    else
      temp=1;
    if(PtrSrc[i]<temp*MAX_POWER_RATE*Get_Un()*Get_In() || Get_Cal_Exsit())  //У��״̬�£����������߼���
      PtrDst[i]=PtrSrc[i];
    else 
      Flag=MEASU_DATA_LOGIC_ERR;
  }
  
  //��ѹ��4��
  PtrSrc=&(Pri_TempIntantVar.Volt.A);
  PtrDst=&(Measu_InstantData_ToPub_PUCK.Volt.A);
  for(i=0;i<4;i++)
  {
    if(3==i &&Pri_MeasuStatVar.V_SeqErr)  //��ѹ������
    {
      PtrDst[i]=PtrSrc[i];
      break;
    }      
    if(PtrSrc[i]<MAX_U_RATE*Get_Un()|| Get_Cal_Exsit())  //У��״̬�£����������߼���
      PtrDst[i]=PtrSrc[i];
    else 
      Flag=MEASU_DATA_LOGIC_ERR;
  } 
  
  if(ParseSpec EQ PARSE_331)//331ģʽ��
  {
    if(Get_Cal_Exsit() EQ 0)   //û�����ϱ��¼�
      PtrDst[1]=0;
  }
  
  //������4��;  
  PtrSrc=&(Pri_TempIntantVar.Curr.A);
  PtrDst=&(Measu_InstantData_ToPub_PUCK.Curr.A);
  for(i=0;i<4;i++)
  {
    if(PtrSrc[i]<MAX_I_RATE*Get_In() || Get_Cal_Exsit())  //У��״̬�£����������߼���
      PtrDst[i]=PtrSrc[i];
    else 
      Flag=MEASU_DATA_LOGIC_ERR;
    
    //if(PtrSrc[i]<=Current_zero[I_Spec])
    //  PtrDst[i]=0;
  } 
  
  
  //�¶ȣ�
  Measu_InstantData_ToPub_PUCK.Temprate=Pri_TempIntantVar.Temprate;
  
  //����������4�Ƶ�ʣ�4����ޣ�4��нǣ�4�
   mem_cpy((void *)(&(Measu_InstantData_ToPub_PUCK.PFactor.A)),\
                   (void *)(&(Pri_TempIntantVar.PFactor.A)),sizeof(MEASU_DATA)*3+sizeof(MEASUFLAG),\
                   (void *)(&(Measu_InstantData_ToPub_PUCK.PFactor.A)),\
                    sizeof(MEASU_DATA)*3+sizeof(MEASUFLAG));
  
   /*************************���´���״̬����********************************/ 
   //ע�� DataRecFlg����COPY
  mem_cpy((void *)(&Measu_Status_Mode_ToPub_PUCK), (void *)(&Pri_MeasuStatVar),sizeof(Pri_MeasuStatVar),(void *)(&Measu_Status_Mode_ToPub_PUCK),sizeof(Measu_Status_Mode_ToPub_PUCK));
  
  
  //�ύӦ�ò㣺A/B/C/��������ָʾ��
  mem_cpy((void *)(&Measu_InstantData_ToPub_PUCK.Quadrant),\
          (void *)(&Pri_TempIntantVar.Quadrant),\
          sizeof(MEASUFLAG),
          (void *)(&Measu_InstantData_ToPub_PUCK.Quadrant),\
          sizeof(MEASUFLAG));
  
  SET_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);
  SET_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  
  return Flag;
}
/**********************************************************************************
�������ܣ���ȡ�з�������
��ڣ���
���ڣ�MEASU_NO_ERR-------��ȡ�ɹ���----------��ȡʧ��
**********************************************************************************/						
void Get_Sign_Instant_Data(void)
{
  //��ȡ�з��ŵ��й�����
  //��ȡ�з��ŵĹ�������
  //��ȡ�з��ŵĵ���
  if(Measu_InstantData_ToPub_PUCK.Quadrant.A>=QUADRANT2 && Measu_InstantData_ToPub_PUCK.Quadrant.A<=QUADRANT3)
  {
    Measu_Sign_InstantData_PUCK.AcPower.A=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AcPower.A;
    Measu_Sign_InstantData_PUCK.AppPower.A=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AppPower.A;
    Measu_Sign_InstantData_PUCK.PFactor.A=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.PFactor.A;
    Measu_Sign_InstantData_PUCK.Curr.A=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.Curr.A;
  }
  else
  {
    Measu_Sign_InstantData_PUCK.AcPower.A=Measu_InstantData_ToPub_PUCK.AcPower.A;
    Measu_Sign_InstantData_PUCK.AppPower.A=Measu_InstantData_ToPub_PUCK.AppPower.A;
    Measu_Sign_InstantData_PUCK.PFactor.A=Measu_InstantData_ToPub_PUCK.PFactor.A;
    Measu_Sign_InstantData_PUCK.Curr.A=Measu_InstantData_ToPub_PUCK.Curr.A;
  }
  
  if(Measu_InstantData_ToPub_PUCK.Quadrant.B>=QUADRANT2 && Measu_InstantData_ToPub_PUCK.Quadrant.B<=QUADRANT3)
  {
    Measu_Sign_InstantData_PUCK.AcPower.B=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AcPower.B;
    Measu_Sign_InstantData_PUCK.AppPower.B=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AppPower.B;
    Measu_Sign_InstantData_PUCK.PFactor.B=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.PFactor.B;
    Measu_Sign_InstantData_PUCK.Curr.B=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.Curr.B;
  }
  else
  {
    Measu_Sign_InstantData_PUCK.AcPower.B=Measu_InstantData_ToPub_PUCK.AcPower.B;
    Measu_Sign_InstantData_PUCK.AppPower.B=Measu_InstantData_ToPub_PUCK.AppPower.B;
    Measu_Sign_InstantData_PUCK.PFactor.B=Measu_InstantData_ToPub_PUCK.PFactor.B;
    Measu_Sign_InstantData_PUCK.Curr.B=Measu_InstantData_ToPub_PUCK.Curr.B;
  }
 
  if(Measu_InstantData_ToPub_PUCK.Quadrant.C>=QUADRANT2 && Measu_InstantData_ToPub_PUCK.Quadrant.C<=QUADRANT3)
  {
    Measu_Sign_InstantData_PUCK.AcPower.C=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AcPower.C;
    Measu_Sign_InstantData_PUCK.AppPower.C=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AppPower.C;
    Measu_Sign_InstantData_PUCK.PFactor.C=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.PFactor.C;
    Measu_Sign_InstantData_PUCK.Curr.C=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.Curr.C;
  }
  else
  {
    Measu_Sign_InstantData_PUCK.AcPower.C=Measu_InstantData_ToPub_PUCK.AcPower.C;
    Measu_Sign_InstantData_PUCK.AppPower.C=Measu_InstantData_ToPub_PUCK.AppPower.C;
    Measu_Sign_InstantData_PUCK.PFactor.C=Measu_InstantData_ToPub_PUCK.PFactor.C;
    Measu_Sign_InstantData_PUCK.Curr.C=Measu_InstantData_ToPub_PUCK.Curr.C;
  }
  
  
  if(Measu_InstantData_ToPub_PUCK.Quadrant.Sum>=QUADRANT2 && Measu_InstantData_ToPub_PUCK.Quadrant.Sum<=QUADRANT3)
  {
    Measu_Sign_InstantData_PUCK.AcPower.Sum=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AcPower.Sum;
    Measu_Sign_InstantData_PUCK.AppPower.Sum=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.AppPower.Sum;
    Measu_Sign_InstantData_PUCK.PFactor.Sum=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.PFactor.Sum;
    Measu_Sign_InstantData_PUCK.Curr.Sum=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.Curr.Sum;
  }
  else
  {
    Measu_Sign_InstantData_PUCK.AcPower.Sum=Measu_InstantData_ToPub_PUCK.AcPower.Sum;
    Measu_Sign_InstantData_PUCK.AppPower.Sum=Measu_InstantData_ToPub_PUCK.AppPower.Sum;
    Measu_Sign_InstantData_PUCK.PFactor.Sum=Measu_InstantData_ToPub_PUCK.PFactor.Sum;
    Measu_Sign_InstantData_PUCK.Curr.Sum=Measu_InstantData_ToPub_PUCK.Curr.Sum;
  }
  //��ȡ�з��ŵ��޹�����  
  if(Measu_InstantData_ToPub_PUCK.Quadrant.A>=QUADRANT3 && Measu_InstantData_ToPub_PUCK.Quadrant.A<=QUADRANT4)
    Measu_Sign_InstantData_PUCK.ReacPower.A=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.ReacPower.A;
  else
    Measu_Sign_InstantData_PUCK.ReacPower.A=Measu_InstantData_ToPub_PUCK.ReacPower.A;
  
   if(Measu_InstantData_ToPub_PUCK.Quadrant.B>=QUADRANT3 && Measu_InstantData_ToPub_PUCK.Quadrant.B<=QUADRANT4)
    Measu_Sign_InstantData_PUCK.ReacPower.B=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.ReacPower.B;
  else
    Measu_Sign_InstantData_PUCK.ReacPower.B=Measu_InstantData_ToPub_PUCK.ReacPower.B;
  
   if(Measu_InstantData_ToPub_PUCK.Quadrant.C>=QUADRANT3 && Measu_InstantData_ToPub_PUCK.Quadrant.C<=QUADRANT4)
    Measu_Sign_InstantData_PUCK.ReacPower.C=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.ReacPower.C;
  else
    Measu_Sign_InstantData_PUCK.ReacPower.C=Measu_InstantData_ToPub_PUCK.ReacPower.C;
  
   if(Measu_InstantData_ToPub_PUCK.Quadrant.Sum>=QUADRANT3 && Measu_InstantData_ToPub_PUCK.Quadrant.Sum<=QUADRANT4)
    Measu_Sign_InstantData_PUCK.ReacPower.Sum=(-1)*(INT32S)Measu_InstantData_ToPub_PUCK.ReacPower.Sum;
  else
    Measu_Sign_InstantData_PUCK.ReacPower.Sum=Measu_InstantData_ToPub_PUCK.ReacPower.Sum;
   
  
  Measu_Sign_InstantData_PUCK.Temprate=Measu_InstantData_ToPub_PUCK.Temprate;
  SET_STRUCT_SUM(Measu_Sign_InstantData_PUCK);
 
}
/**********************************************************************************
�������ܣ�������˲ʱ�����ύӦ�ò�
��ڣ���
���ڣ���
**********************************************************************************/	
void GetMeasInstantData_PerSec(void)
{
  INT8U Flag;

  Flag=ChkPowerLimitAndConvertData();
  if(Flag!=MEASU_NO_ERR)
  {   
    Pri_MeasuStatVar.DataRecFlg=0;
    SET_STRUCT_SUM(Pri_MeasuStatVar);
    RstCtrlStatus.RstLimiCountr++;
    RstCtrlStatus.LimitErrCountr++;
    Debug_Print("Measure_Error----->In GetAppInstant(),ErrCode=%d,LimitErrCountr=%d,MeasErrCountrs=%d,Rst=%d",Flag,RstCtrlStatus.LimitErrCountr,RstCtrlStatus.MeasErrCountr,RstCtrlStatus.RstLimiCountr);
    Measure_Error_Statics(Flag,0);
    
    if(RstCtrlStatus.RstLimiCountr>=MAX_RST_MEASU_IC_TIMES)
    { 
      Measure_Error_Statics(Flag,1);  
      Beep_For_Measu_Alarm_PUCK(Flag);    
      Debug_Print("Measure_Error----->MeasuIC Error Count OverLimited,Reset Measure IC..........");
      InitMeasuAfterPwrOn();
      RstCtrlStatus.RstLimiCountr=0;
    }
  }
  else
  {
    Pri_MeasuStatVar.DataRecFlg=1;
    SET_STRUCT_SUM(Pri_MeasuStatVar);
    RstCtrlStatus.RstLimiCountr=0;
    Get_Sign_Instant_Data();
  } 
  SET_STRUCT_SUM(RstCtrlStatus);
}
/**********************************************************************************
�������ܣ��������ۼ������ύӦ�ò㣬ÿ���ۼ��м����Ԫ����/�޹����ۼ�ֵ���������޹����ۼ�ֵ����/���޹����ۼ�ֵ�ȡ�
��ڣ���
���ڣ���
**********************************************************************************/	
void	GetMeasAccmuData_PerSec(void)
{
  INT8U  i,temp1;
  INT8U volatile *Ptr;
  INT32U volatile *Ptr1,*Ptr2,*Ptr3,*Ptr4;
  INT32U CopperLoss,IronLoss,GeneralErr,temp,temp0;
  
  
  temp1=CHECK_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  temp1&=CHECK_STRUCT_SUM(Pri_TempMeasuVar);
  temp1&=CHECK_STRUCT_SUM(Measu_Energ_ToPub_PUCK);
  if(!temp1)
    ASSERT_FAILED(); 
  
 //Clr_Energ_Accu();   //������ڼ�����������ļĴ���,�������� 0.006��ʵ�顣
 
  //��ȡA/B/C/�������й�������
  Ptr=&(Measu_InstantData_ToPub_PUCK.Quadrant.A);
  Ptr1=&(Pri_TempMeasuVar.Change_AcEnerg.A);
  for(i=0;i<=3;i++)
  {
    temp=Ptr1[i];  //��ǰ��Ԫ���й�����  
    if(Ptr[i]>QUADRANT4)
    {
      Debug_Print("Measure_Error----->Quadrant OverFolw While Getting Acpower Energ!"); 
      break;
    }
    if((Ptr[i]==QUADRANT1)||(Ptr[i]==QUADRANT4))	 //�ۼ�A/B/C/�������й������м䵥Ԫ
    {
        Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[i]+=temp;
    }      
    else				      		//�ۼ���/A/B/C�����й������м䵥Ԫ
    {
        Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[i]+=temp;
    }
  }  

#if APP_ENERG_EN >0 //��PQS���ڵ��ܱ�
  //��ȡA/B/C/��������������
  Ptr=&(Measu_InstantData_ToPub_PUCK.Quadrant.A);
  Ptr1=&(Pri_TempMeasuVar.Change_AppEnerg.A);
  for(i=0;i<=3;i++)
  {
    temp=Ptr1[i];  //��ǰ��Ԫ���й�����  
    if(Ptr[i]>QUADRANT4)
    {
      Debug_Print("Measure_Error----->Quadrant OverFolw While Getting Acpower Energ!"); 
      break;
    }
    if((Ptr[i]==QUADRANT1)||(Ptr[i]==QUADRANT4))	 //�ۼ�A/B/C/�������й������м䵥Ԫ
    {
        Measu_Energ_ToPub_PUCK.Chang_Plus_PQSEnerg[i]+=temp;
    }      
    else				      		//�ۼ���/A/B/C�����й������м䵥Ԫ
    {
        Measu_Energ_ToPub_PUCK.Chang_Nega_PQSEnerg[i]+=temp;
    }
  }  
#endif
  
  //��ȡA/B/C/���������޹�����;��ȡA/B/C/�������޹�����
  Ptr=&(Measu_InstantData_ToPub_PUCK.Quadrant.A);
  Ptr1=&(Pri_TempMeasuVar.Change_ReacEnerg.A);  
  for(i=0;i<=3;i++)
  {
    temp1=Ptr[i];  //��ǰ����
    temp=Ptr1[i];  //��ǰ��Ԫ���޹�����   
    if(temp1>QUADRANT4)
    {
      Debug_Print("Measure_Error----->Quadrant OverFolw While Getting Reacpower Energ!"); 
      break;
    }
    Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[i][temp1-QUADRANT1]+=temp;  //��Ԫ��4�����޹���1~4��1��Ϊƫ��
    
    //Measu_Energ_ToPub_PUCK.Chang_Plus_ReacEnerg[i]+=temp*GET_BIT(MeasuSysMode.RG1_Spec,temp1-QUADRANT1);   //��Ԫ�������޹���������޹�1,ֻ����ӣ����������
    //Measu_Energ_ToPub_PUCK.Chang_Nega_ReacEnerg[i]+=temp*GET_BIT(MeasuSysMode.RG2_Spec,temp1-QUADRANT1);   //��Ԫ�������޹���������޹�2,ֻ����ӣ����������    
  }  
  
   //�ۼ�A/B/C�లʱֵ�м䵥Ԫ����λΪ0.0001����.��
  Ptr4=&(Measu_InstantData_ToPub_PUCK.Curr.A);
  for(i=0;i<=2;i++)
  {
    temp=Ptr4[i];
    Measu_Energ_ToPub_PUCK.Add_AmpaHour[i]+=(INT32U)((FP32S)temp/UNIT_A*UNIT_AS);      //��ʱ:��λ��0.0001An.s
    Measu_Energ_ToPub_PUCK.Add_AmpaHour[3]+=(INT32U)((FP32S)temp/UNIT_A*UNIT_AS);      //����
  }
  //�ۼ�A/B/C��ͭ������ͻ������ϳ�����м䵥Ԫ
  Ptr1=&(Measu_InstantData_ToPub_PUCK.AcPower.A);
  Ptr2=&(Measu_InstantData_ToPub_PUCK.ReacPower.A);
  Ptr3=&(Measu_InstantData_ToPub_PUCK.Volt.A);
  Ptr4=&(Measu_InstantData_ToPub_PUCK.Curr.A);
  
  for(i=0;i<=2;i++)
  {
    temp=Ptr4[i];
    CopperLoss=(INT32U)(((FP32S)temp/UNIT_A)*((FP32S)temp/UNIT_A)*UNIT_KA2S);   //ͭ��:��λΪ 0.0000001kA2s
    Measu_Energ_ToPub_PUCK.Add_CopperLoss[i]+=CopperLoss;
    
    temp0=Ptr3[i];
    IronLoss=(INT32U)(((FP32S)temp0/UNIT_V)*((FP32S)temp0/UNIT_V)*UNIT_MV2S);   //����:��λΪ 0.00000001MV2s
    Measu_Energ_ToPub_PUCK.Add_IronLoss[i]+=IronLoss;
    
    if(Ptr1[i]==0)
      GeneralErr=(INT32U)((FP32S)UNIT_TGFAS*Ptr2[i]/UNIT_KWH_KVAR);            //�й�����Ϊ0��ȡ�޹�����
    else
    {
      temp0=Ptr2[i];
      GeneralErr=(INT32U)(((FP32S)UNIT_TGFAS*temp0)/Ptr1[i]);	//ȡ=��λ*�޹�����/�й�����,��λΪ0.01*tgFA*s
    }
    if(GeneralErr>5800)		       //89�ȸ���
      GeneralErr=UNIT_TGFAS*58;
    
    Measu_Energ_ToPub_PUCK.Add_GenaralErr[i]+=GeneralErr;
    
    Measu_Energ_ToPub_PUCK.Add_CopperLoss[3]+=CopperLoss;      //����
    Measu_Energ_ToPub_PUCK.Add_IronLoss[3]+=IronLoss;          //����
    Measu_Energ_ToPub_PUCK.Add_GenaralErr[3]+=GeneralErr;       //����
  } 
  
  //����ʱ���С��޹�������0
  mem_set((void *)&Pri_TempMeasuVar.Change_AcEnerg,0,\
                 sizeof(Pri_TempMeasuVar.Change_AcEnerg)*2,\
                 (void *)&Pri_TempMeasuVar.Change_AcEnerg,\
                 sizeof(Pri_TempMeasuVar.Change_AcEnerg)*2);
  SET_STRUCT_SUM(Pri_TempMeasuVar);
  SET_STRUCT_SUM(Measu_Energ_ToPub_PUCK);
}

/**********************************************************************************
�������ܣ���ȡ�����ۼ���,��HUCK����
��ڣ�
ID----ֻ��HUCK��Ч��
DstReal----Ŀ�껺������ʵ�ʵ�ַ��
Dst_Start----Ŀ�껺�������ʼ��ַ��
DstLen----Ŀ�껺����ʵ�����ݳ���
DstMaxLen----Ŀ�껺����������ݳ���
���ڣ�0����ȡʧ�ܣ���0��ʵ�ʵ����ݳ��ȣ���MEASU_ENERG�ۼ����ݸ�Dst
ע�⣺Dst��У���û�д���
**********************************************************************************/	
INT16U Get_Measu_AcculateData_PUCK(INT8U ID,void *DstReal,void *Dst_Start,INT16U DstLen,INT16U DstMaxLen)
{
  INT8U i,j;
  INT32U tempmod;
  
  //ֻ��HUCK����Ȩ�޷���
  if(ID!=HUCK)
    return 0;
  
  if(DstLen > sizeof(MEASU_ENERG))
    ASSERT_FAILED();
  
  if((INT8U *)DstReal<(INT8U *)Dst_Start || (INT8U *)DstReal+DstLen > (INT8U *)Dst_Start+DstMaxLen)
    ASSERT_FAILED();
  
  if(CHECK_STRUCT_SUM(Measu_Energ_ToPub_PUCK)==0)
    ASSERT_FAILED();
  
  mem_cpy(DstReal,(void *)(&Measu_Energ_ToPub_PUCK),sizeof(MEASU_ENERG),DstReal,DstMaxLen);
  
  for(i=0;i<4;i++)   //��ȡ���ࡢ���������й�����
  {
    tempmod=Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[i]%ENERGY_RATIO;  
    Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[i]=tempmod; 
  }
  
  for(i=0;i<4;i++)  //��ȡ���ࡢ���෴���й�����
  {
    tempmod=Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[i]%ENERGY_RATIO;
    Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[i]=tempmod;    
  }
  
  /*
  for(i=0;i<4;i++)
  {
    tempmod=Measu_Energ_ToPub_PUCK.Chang_Plus_ReacEnerg[i]%ENERGY_RATIO;
    Measu_Energ_ToPub_PUCK.Chang_Plus_ReacEnerg[i]=tempmod;    
  }
  
  for(i=0;i<4;i++)
  {
    tempmod=Measu_Energ_ToPub_PUCK.Chang_Nega_ReacEnerg[i]%ENERGY_RATIO;
    Measu_Energ_ToPub_PUCK.Chang_Nega_ReacEnerg[i]=tempmod;    
  }
  */
 
  for(i=0;i<4;i++)   //��ȡ���ࡢ����4�����޹�����
  {
    for(j=0;j<4;j++)
    {
      tempmod=Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[i][j]%ENERGY_RATIO;
      Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[i][j]=tempmod;
    }
  }
  
#if APP_ENERG_EN >0 //��PQS���ڵ��ܱ�
  for(i=0;i<4;i++)   //��ȡ���ࡢ�����������ڵ���
  {
    tempmod=Measu_Energ_ToPub_PUCK.Chang_Plus_PQSEnerg[i]%ENERGY_RATIO;  
    Measu_Energ_ToPub_PUCK.Chang_Plus_PQSEnerg[i]=tempmod; 
  }
  
  for(i=0;i<4;i++)  //��ȡ���ࡢ���෴�����ڵ���
  {
    tempmod=Measu_Energ_ToPub_PUCK.Chang_Nega_PQSEnerg[i]%ENERGY_RATIO;
    Measu_Energ_ToPub_PUCK.Chang_Nega_PQSEnerg[i]=tempmod;    
  }
#endif
  
  for(i=0;i<4;i++)   //��ȡ��ʱ�ۼ�
  {
    tempmod=Measu_Energ_ToPub_PUCK.Add_AmpaHour[i]%AH_RATIO;
    Measu_Energ_ToPub_PUCK.Add_AmpaHour[i]=tempmod;    
  }

  for(i=0;i<4;i++)  //��ȡͭ���ۼ�
  {
    tempmod=Measu_Energ_ToPub_PUCK.Add_CopperLoss[i]%COPPERLOSS_RATIO;
    Measu_Energ_ToPub_PUCK.Add_CopperLoss[i]=tempmod;    
  }
  
  for(i=0;i<4;i++)   //��ȡ�����ۼ�
  {
    tempmod=Measu_Energ_ToPub_PUCK.Add_IronLoss[i]%IRONLOSS_RATIO;
    Measu_Energ_ToPub_PUCK.Add_IronLoss[i]=tempmod;    
  }
  
    
  for(i=0;i<4;i++)    //��ȡ�ϳ�����ۼ�
  {
    tempmod=Measu_Energ_ToPub_PUCK.Add_GenaralErr[i]%TRANSERR_RATIO;
    Measu_Energ_ToPub_PUCK.Add_GenaralErr[i]=tempmod;    
  }
 SET_STRUCT_SUM(Measu_Energ_ToPub_PUCK);
 return sizeof(MEASU_ENERG);  
}

/**********************************************************************************
�������ܣ�ÿ���MeasuIC��������
��ڣ���
���ڣ���
**********************************************************************************/	
void Deal_PerSec_Main(void)
{
  INT8U Flag;
  
  Flag=GetMeasuData_PerSec(); 
  if(Flag!=MEASU_NO_ERR)
  {
    Pri_MeasuStatVar.DataRecFlg=0;
    SET_STRUCT_SUM(Pri_MeasuStatVar);    
    RstCtrlStatus.RstMeasCountr++;
    RstCtrlStatus.MeasErrCountr++;
    Debug_Print("Measure_Error----->In Deal_PerSec_Main(),ErrCode=%d,LimitErrCountr=%d,MeasErrCountrs=%d,Rst=%d",Flag,RstCtrlStatus.LimitErrCountr,RstCtrlStatus.MeasErrCountr,RstCtrlStatus.RstMeasCountr);
    Measure_Error_Statics(Flag,0);

    if(RstCtrlStatus.RstMeasCountr>=MAX_RST_MEASU_IC_TIMES)
    { 
      Measure_Error_Statics(Flag,1);
      Beep_For_Measu_Alarm_PUCK(Flag);
      Debug_Print("Measure_Error----->MeasuIC Error Count OverLimited,Reset Measure IC..........");
      InitMeasuAfterPwrOn(); 
      RstCtrlStatus.RstMeasCountr=0;      
    }
  }
  else
  {
    Pri_MeasuStatVar.DataRecFlg=1;
    SET_STRUCT_SUM(Pri_MeasuStatVar);
    RstCtrlStatus.RstMeasCountr=0;
  }
  SET_STRUCT_SUM(RstCtrlStatus);
}

/**********************************************************************************
�������ܣ�ÿ����м��Ԫ�ش���
��ڣ���
���ڣ���
ע�⣺�˺����ǶԼ������ݵķ����������ݷ���ʱ���������ó���ǰ������˯�ߵȡ�
**********************************************************************************/	
void Deal_MeasAppData_PerSec_Main(void)
{
  GetMeasInstantData_PerSec();        //��ȡ˲ʱ�����ݺ�״̬��
  GetMeasAccmuData_PerSec();        //��ȡ�ۼ�������
 
  //Check_Voltage_Threshold();	/*"ֻ���������е���ߵ�ѹ����75��Unʱ�ŵ�������"*/
}

/**********************************************************************************
�������ܣ����������ص�����Sram����(ֻ�Ա��ݵ�Sram������Ч)
��ڣ���
���ڣ���
**********************************************************************************/	
void ReCorrect_Instant_Sram(void)
{
#ifdef MEASURE_VAR_BAK_EN
  INT8U Flag;
    

  Flag=CHECK_STRUCT_SUM(Pri_TempMeasuVarBak1);
  if(Flag==0)  //Pri_TempMeasuVarBak1�д�����
  {
    Flag=CHECK_STRUCT_SUM(Pri_TempMeasuVarBak2);
    if(Flag==0)  //Pri_TempMeasuVarBak2�д�����
    {
      Debug_Print("Measure_Error----->Struct CS Error Pri_TempMeasuVar&&Bak1&&Bak2!");
    }
    else                          //Pri_TempMeasuVarBak2��ȷ,��������2��
    {
      mem_cpy((void *)(&(Pri_TempMeasuVar)),(void *)(&(Pri_TempMeasuVarBak2)),sizeof(Pri_TempMeasuVarBak2),\
                   (void *)(&(Pri_TempMeasuVar)),sizeof(Pri_TempMeasuVar));
             
      mem_cpy((void *)(&(Pri_TempMeasuVarBak1)),(void *)(&(Pri_TempMeasuVarBak2)),sizeof(Pri_TempMeasuVarBak2),\
                   (void *)(&(Pri_TempMeasuVarBak1)),sizeof(Pri_TempMeasuVarBak1));  
      }          
  }
  else                         //Pri_TempMeasuVarBak1��ȷ,��������2��
  {
    mem_cpy((void *)(&(Pri_TempMeasuVar)),(void *)(&(Pri_TempMeasuVarBak1)),sizeof(Pri_TempMeasuVarBak1),\
                   (void *)(&(Pri_TempMeasuVar)),sizeof(Pri_TempMeasuVar));
             
    mem_cpy((void *)(&(Pri_TempMeasuVarBak2)),(void *)(&(Pri_TempMeasuVarBak1)),sizeof(Pri_TempMeasuVarBak1),\
                   (void *)(&(Pri_TempMeasuVarBak2)),sizeof(Pri_TempMeasuVarBak2));  
  } 
#endif
}
/**********************************************************************************
�������ܣ����������ص�����Sram����(ֻ�Ա��ݵ�Sram������Ч)
��ڣ���
���ڣ���
**********************************************************************************/	
void ReCorrect_Energ_Sram(void)
{
#ifdef MEASURE_VAR_BAK_EN  
  INT8U Flag;
  Flag=CHECK_STRUCT_SUM(Measu_Energ_ToPub_Bak);
  if(Flag==0)  //����Ҳ�����˴���
  {
      Debug_Print("Measure_Error----->Struct CS Error Measu_Energ_ToPub_PUCK&&Bak!");
  }
  else     //�����޴����ñ��ݸ���
  {
    mem_cpy((void *)(&(Measu_Energ_ToPub_PUCK)),(void *)(&(Measu_Energ_ToPub_Bak)),sizeof(Measu_Energ_ToPub_Bak),\
                   (void *)(&(Measu_Energ_ToPub_PUCK)),sizeof(Measu_Energ_ToPub_PUCK));             
  }  
#endif
}
/**********************************************************************************
�������ܣ����������������нṹ���У���
��ڣ���
���ڣ���
**********************************************************************************/	
void Check_ALL_Sram_Sum(void)
{
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(RstCtrlStatus);  
  Re&=CHECK_STRUCT_SUM(Sys_Pulse_Var);
  Re&=CHECK_STRUCT_SUM(Curr_1_Per_100);
  Re&=CHECK_STRUCT_SUM(Curr_6_13x5_Slipe);
  Re&=CHECK_STRUCT_SUM(Curr_In_6_13x5);
  Re&=CHECK_STRUCT_SUM(SpecChange_CurrFlag);
  Re&=CHECK_STRUCT_SUM(MeasuStatusMode);
  Re&=CHECK_STRUCT_SUM(Pri_MeasuStatVar);
  Re&=CHECK_STRUCT_SUM(Pri_TempIntantVar);
  Re&=CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);
  Re&=CHECK_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  Re&=CHECK_STRUCT_SUM(MeasuPara_CS);
  Re&=CHECK_STRUCT_VAR(Energ_Err_Clr);  
  
  if(Re EQ 0)
    ASSERT_FAILED();
  
  
  if(CHECK_STRUCT_SUM(Measu_Energ_ToPub_PUCK)==0)
  {
    ASSERT_FAILED();  //CS����
      ReCorrect_Energ_Sram();
  }
#ifdef MEASURE_VAR_BAK_EN
  else                          //������ȷ
  {
    mem_cpy((void *)(&(Measu_Energ_ToPub_Bak)),(void *)(&(Measu_Energ_ToPub_PUCK)),sizeof(Measu_Energ_ToPub_PUCK),\
                   (void *)(&(Measu_Energ_ToPub_Bak)),sizeof(Measu_Energ_ToPub_Bak));  
  }
#endif
    
  
  
  if(CHECK_STRUCT_SUM(Pri_TempMeasuVar)==0)
  {
    ASSERT_FAILED();  //CS����
    ReCorrect_Instant_Sram();
  }
#ifdef MEASURE_VAR_BAK_EN
  else                          //������ȷ      
  {
      mem_cpy((void *)(&(Pri_TempMeasuVarBak1)),(void *)(&(Pri_TempMeasuVar)),sizeof(Pri_TempMeasuVar),\
                   (void *)(&(Pri_TempMeasuVarBak1)),sizeof(Pri_TempMeasuVarBak1)); 
      mem_cpy((void *)(&(Pri_TempMeasuVarBak2)),(void *)(&(Pri_TempMeasuVar)),sizeof(Pri_TempMeasuVar),\
                   (void *)(&(Pri_TempMeasuVarBak2)),sizeof(Pri_TempMeasuVarBak2)); 
  }
#endif
  
  Check_Pulse();   //������峣���Ƿ����ô���,�����ⱨ��
  
  
  if((FP32S)Measu_InstantData_ToPub_PUCK.AcPower.Sum/UNIT_KW_KAR>=5.5*3*Get_Un()*Get_In()/1000)  //�����Ѿ�Խ��
  {
    Sys_Pulse_Var.Pulse_Width=40;
    SET_STRUCT_SUM(Sys_Pulse_Var);
  }    
}
/********************************************************************************
����ԭ�ͣ�void Monitor_Para_Modi_PUCK(void)
���ܣ������в�������ά��������������ͨ�����¼��ȡ�

*********************************************************************************/
void MeasuPara_Modi_PUCK(void)
{
  PROTO_DI temp;
  
  while(Get_Para_Modify(&temp))
  {
    Debug_Print("Para Modified In Measure Task:0x%lx",temp);
    switch(temp)
    {
      case DI_MODE1:   //ע��DI_TFHģʽ�ָı�󣬱���Լ���оƬ��λ����һ��
      case DI_P_U_I_SPEC:
        Init_Para();                //��ʼ����У������޹صĲ���
        Init_Measure_IC();          //��λ����оƬ,�����ü�������
#ifdef ID_EVENT_ADJUST_MEASU       
        Set_Event_Instant(ID_EVENT_ADJUST_MEASU);  //У���¼�
#endif  
       break;
       
      case DI_AC_PULSE:      
      case DI_REAC_PULSE:
      case DI_PULSE_WIDTH:  
        Get_Pulse_Para();   //�������޹����峣������Ƶϵ�����������,��У���޹أ�������У���¼�
       break;
    
    case  DI_CLR_PARA:     //����
        Init_Para();                //��ʼ����У������޹صĲ���
        Init_Measure_IC();
      break;
      
#if SEC_MULTI_PORT>0  //�������Ǹ��϶���      
    case SDI_OUTPUT_MODE:  
    Init_Sec_Pulse();
    break;
#endif    
      
    default:
#if CAL_METER_TYPE >= SELF_CAL_TYPE 
      if((temp>=DI_POWER_A_0)&&(temp<=DI_I_GAIN_C))  //У����������޸�
      {
        Load_Adj_OnePara_To_IC(temp);
        
#ifdef ID_EVENT_ADJUST_MEASU       
        Set_Event_Instant(ID_EVENT_ADJUST_MEASU);  //У���¼�
#endif  
      }
#endif 
      if(JUDGE_IS_EVENT_PARA(temp))
      {
        Init_One_Event_Para(temp);        
      }
      break;
    }    
  }   
}
/**********************************************************************************
�������ܣ���ӡ�����������,��ͬ������
��ڣ���
���ڣ���
**********************************************************************************/	
void DebugOutMeasuData(void)
{
  static INT8U Num=0;
  Num++;
  if(Num<240)
    return ;
  
  Num=0;
  Debug_Print("|------------------------Measure_Instant_Data------------------------|");
  OS_TimeDly_Ms(10);
  Debug_Print("|               Item           A         B         C     Total       |");
  OS_TimeDly_Ms(10);
  Debug_Print("|    AcPower(0.001w)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.AcPower.A,Measu_InstantData_ToPub_PUCK.AcPower.B,Measu_InstantData_ToPub_PUCK.AcPower.C,Measu_InstantData_ToPub_PUCK.AcPower.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|ReacPower(0.001var)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.ReacPower.A,Measu_InstantData_ToPub_PUCK.ReacPower.B,Measu_InstantData_ToPub_PUCK.ReacPower.C,Measu_InstantData_ToPub_PUCK.ReacPower.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|  AppPower(0.001vA)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.AppPower.A,Measu_InstantData_ToPub_PUCK.AppPower.B,Measu_InstantData_ToPub_PUCK.AppPower.C,Measu_InstantData_ToPub_PUCK.AppPower.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|       Volt(0.0001)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C,Measu_InstantData_ToPub_PUCK.Volt.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|       Curr(0.0001)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B,Measu_InstantData_ToPub_PUCK.Curr.C,Measu_InstantData_ToPub_PUCK.Curr.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|  PFactor(0.000001)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.PFactor.A,Measu_InstantData_ToPub_PUCK.PFactor.B,Measu_InstantData_ToPub_PUCK.PFactor.C,Measu_InstantData_ToPub_PUCK.PFactor.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|        Angle(0.01)   %9ld,%9ld,%9ld,%9ld       |",Measu_InstantData_ToPub_PUCK.Angle.A,Measu_InstantData_ToPub_PUCK.Angle.B,Measu_InstantData_ToPub_PUCK.Angle.C,Measu_InstantData_ToPub_PUCK.Angle.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|     Freq(0.000001)   %9ld,%9ld,%9ld                 |",Measu_InstantData_ToPub_PUCK.Freq.A,Measu_InstantData_ToPub_PUCK.Freq.B,Measu_InstantData_ToPub_PUCK.Freq.C,Measu_InstantData_ToPub_PUCK.Freq.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|           Quadrant   %9d,%9d,%9d,%9d       |",Measu_InstantData_ToPub_PUCK.Quadrant.A,Measu_InstantData_ToPub_PUCK.Quadrant.B,Measu_InstantData_ToPub_PUCK.Quadrant.C,Measu_InstantData_ToPub_PUCK.Quadrant.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|--------------------------------------------------------------------|"); 
  
  OS_TimeDly_Ms(10);
  Debug_Print("|-----------------------------Measure_Para---------------------------|");
  OS_TimeDly_Ms(10);
  Debug_Print("| ParseMode=%d(PARSE_331/PARSE_341)                                   |",MeasuSysMode.ParseMode);
  OS_TimeDly_Ms(10);
  Debug_Print("| P_Spec=%d(PULSE_TYPE1/PULSE_TYPE2)                                  |",MeasuSysMode.P_Spec);
  OS_TimeDly_Ms(10);
  Debug_Print("| V_Spec=%d(3*100/3*220/3*57.70/3*380)                                |",MeasuSysMode.V_Spec);
  OS_TimeDly_Ms(10);
  Debug_Print("| I_Spec=%d(1.5_6/1_2/5_10/10_40/0.3_1.2/5_6/15_60/20_80/5_20/30_100  |",MeasuSysMode.I_Spec);
  OS_TimeDly_Ms(10);
  Debug_Print("| TF/TH=%d(TH/TF)                                                     |",MeasuSysMode.T_FH);
  OS_TimeDly_Ms(10);
  Debug_Print("| AcPulseConst=%8ld, ReacPulseConst=%8ld,                    |",Sys_Pulse_Var.Ac_Pulse,Sys_Pulse_Var.Rea_Pulse);
  OS_TimeDly_Ms(10);
  Debug_Print("|--------------------------------------------------------------------|"); 

  
  Debug_Print("|-------------------------Measure_Status_Data------------------------|");
  OS_TimeDly_Ms(10);
  Debug_Print("|               Item           A         B         C     Total       |");
  OS_TimeDly_Ms(10);
  Debug_Print("|      AcEnerg_Value   %9ld,%9ld,%9ld,%9ld       |",Pri_TempMeasuVar.AcEnerg.A,Pri_TempMeasuVar.AcEnerg.B,Pri_TempMeasuVar.AcEnerg.C,Pri_TempMeasuVar.AcEnerg.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|    ReacEnerg_Value   %9ld,%9ld,%9ld,%9ld       |",Pri_TempMeasuVar.ReacEnerg.A,Pri_TempMeasuVar.ReacEnerg.B,Pri_TempMeasuVar.ReacEnerg.C,Pri_TempMeasuVar.ReacEnerg.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|--------------------------------------------------------------------|"); 
  
  Print_Measure_Err_Info();
  /*
  Debug_Print("AcPower(0.001w):%ld,%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.AcPower.A,Measu_InstantData_ToPub_PUCK.AcPower.B,Measu_InstantData_ToPub_PUCK.AcPower.C,Measu_InstantData_ToPub_PUCK.AcPower.Sum);
  Debug_Print("ReacPower(0.001var):%ld,%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.ReacPower.A,Measu_InstantData_ToPub_PUCK.ReacPower.B,Measu_InstantData_ToPub_PUCK.ReacPower.C,Measu_InstantData_ToPub_PUCK.ReacPower.Sum);
  Debug_Print("AppPower(0.001vA):%ld,%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.AppPower.A,Measu_InstantData_ToPub_PUCK.AppPower.B,Measu_InstantData_ToPub_PUCK.AppPower.C,Measu_InstantData_ToPub_PUCK.AppPower.Sum);
  
  Debug_Print("Volt(0.0001):%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.Volt.A,Measu_InstantData_ToPub_PUCK.Volt.B,Measu_InstantData_ToPub_PUCK.Volt.C);
  Debug_Print("Curr(0.0001):%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.Curr.A,Measu_InstantData_ToPub_PUCK.Curr.B,Measu_InstantData_ToPub_PUCK.Curr.C);
  Debug_Print("PFactor(0.000001):%ld,%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.PFactor.A,Measu_InstantData_ToPub_PUCK.PFactor.B,Measu_InstantData_ToPub_PUCK.PFactor.C,Measu_InstantData_ToPub_PUCK.PFactor.Sum);
  
  Debug_Print("Angle(0.01):%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.Angle.A,Measu_InstantData_ToPub_PUCK.Angle.B,Measu_InstantData_ToPub_PUCK.Angle.C);
  Debug_Print("Freq(0.000001):%ld,%ld,%ld",Measu_InstantData_ToPub_PUCK.Freq.A,Measu_InstantData_ToPub_PUCK.Freq.B,Measu_InstantData_ToPub_PUCK.Freq.C,Measu_InstantData_ToPub_PUCK.Freq.Sum);
  Debug_Print("Quadrant:%d,%d,%d,%d",Measu_InstantData_ToPub_PUCK.Quadrant.A,Measu_InstantData_ToPub_PUCK.Quadrant.B,Measu_InstantData_ToPub_PUCK.Quadrant.C,Measu_InstantData_ToPub_PUCK.Quadrant.Sum);

  Debug_Print("Chang_Plus_AcEnerg(0.001Wh):%ld,%ld,%ld,%ld",Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[0],Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[1],Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[2],Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[3]);
  Debug_Print("Chang_Nega_AcEnerg(0.001Wh):%ld,%ld,%ld,%ld",Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[0],Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[1],Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[2],Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[3]);
  
  Debug_Print("Chang_Quad_ReacEnerg_1(0.001Wh):%ld,%ld,%ld,%ld",Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[0][0],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[1][0],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[2][0],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[3][0]);
  Debug_Print("Chang_Quad_ReacEnerg_2(0.001Wh):%ld,%ld,%ld,%ld",Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[0][1],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[1][1],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[2][1],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[3][1]);
  Debug_Print("Chang_Quad_ReacEnerg_3(0.001Wh):%ld,%ld,%ld,%ld",Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[0][2],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[1][2],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[2][2],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[3][2]);
  Debug_Print("Chang_Quad_ReacEnerg_4(0.001Wh):%ld,%ld,%ld,%ld",Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[0][3],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[1][3],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[2][3],Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[3][3]);
 */
}
/**********************************************************************************
�������ܣ���ӡ��������ͳ����Ϣ
��ڣ���
���ڣ���
**********************************************************************************/	
void Print_Measure_Err_Info(void)
{
#ifdef  MEASURE_ERROR_STATICS_EN
  
  INT16U i;
  
  if(CHECK_STRUCT_SUM(Measure_Err_Info)==0)
  {
    mem_set((INT8U *)(&Measure_Err_Info),0x00,sizeof(Measure_Err_Info),(INT8U *)(&Measure_Err_Info),sizeof(Measure_Err_Info));
    SET_STRUCT_SUM(Measure_Err_Info);
    return ;
  }
  

  Debug_Print("|---------------------Measure Error Statis Info----------------------|");
  Debug_Print("|          Error_Code              Error_Num        ResetNum         |");
  Debug_Print("|                 %3d                                    %3d         |",Measure_Err_Info.AcFlag,Measure_Err_Info.ResetNum);
  Debug_Print("|           %9ld(Last)       %9ld(Curr)  %9ld(Change) |",Measure_Err_Info.LastValue,Measure_Err_Info.CurrValue,Measure_Err_Info.ChangeValue);
  
  for(i=MEASU_NO_ERR+1;i<=MAX_MEASU_ERR;i++)
  {
   OS_TimeDly_Ms(10);  
   Debug_Print("|                 %3d                   %3d                          |",i,Measure_Err_Info.Num[i]);
  }
 
  Debug_Print("|--------------------------------------------------------------------|"); 
  
  Debug_Print("|-------------------------Measure_Status_Data------------------------|");
  Debug_Print("|               Item           A         B         C     Total       |");
  OS_TimeDly_Ms(10);
  Debug_Print("|      AcEnerg_Value   %9ld,%9ld,%9ld,%9ld       |",Pri_TempMeasuVar.AcEnerg.A,Pri_TempMeasuVar.AcEnerg.B,Pri_TempMeasuVar.AcEnerg.C,Pri_TempMeasuVar.AcEnerg.Sum);
  OS_TimeDly_Ms(10);
  Debug_Print("|    ReacEnerg_Value   %9ld,%9ld,%9ld,%9ld       |",Pri_TempMeasuVar.ReacEnerg.A,Pri_TempMeasuVar.ReacEnerg.B,Pri_TempMeasuVar.ReacEnerg.C,Pri_TempMeasuVar.ReacEnerg.Sum);

  Debug_Print("|--------------------------------------------------------------------|"); 
  
#endif
}
/**********************************************************************************
�������ܣ���������ͳ��
��ڣ���
���ڣ���
**********************************************************************************/	
void Measure_Error_Statics(INT8U Code,INT8U RstFlag)
{
#ifdef  MEASURE_ERROR_STATICS_EN
  
  if(CHECK_STRUCT_SUM(Measure_Err_Info)==0)
  {
    mem_set((INT8U *)(&Measure_Err_Info),0x00,sizeof(Measure_Err_Info),(INT8U *)(&Measure_Err_Info),sizeof(Measure_Err_Info)); 
    SET_STRUCT_SUM(Measure_Err_Info);
  }
  
  if(MEASU_NO_ERR==Code || Code>MAX_MEASU_ERR)  //�޴���,���ߴ�����볬��
    return ;
  
  if(RstFlag)
  {
    Measure_Err_Info.ResetNum++;
    //Set_Event_Instant(ID_MEASURE_ERROR);  //�Լ���оƬҪ��λ������һ�μ�������
  }
  
  Measure_Err_Info.Num[Code]++;

  SET_STRUCT_SUM(Measure_Err_Info);
  Print_Measure_Err_Info();
#endif
}

//#pragma optimize = none
/**********************************************************************************
�������ܣ�������оƬ��epprom��У����Ƿ���ȷ
��ڣ���
���ڣ���
**********************************************************************************/	
INT8U CheckBothCs(void)
{
  INT32U CS_IC;
  INT8U Flag;
  
  if(Get_Cal_Exsit())   //�����ϱ��¼�ʱ�����ǹ���״̬ʱ�����ж�2�ߵļ���ͣ�����̫��
    return MEASU_NO_ERR;
  
  Flag=Get_IC_ParaSum3(&CS_IC);
  if(!Flag)      //ȡУ��ʹ�����ȡһ��
  {
    Flag=Get_IC_ParaSum3(&CS_IC);
    if(!Flag)     //ȡУ��ʹ�����ȡһ��
    {
      ASSERT_FAILED();  
      MeasuStatusMode.Retry=1;   //����оƬ����д��������
      SET_STRUCT_SUM(MeasuStatusMode);
      return MEASU_CS_ERR;
    }
  }
  
  if( (CS_IC!=MeasuPara_CS.IC_Cs) || (CS_IC!=MeasuPara_CS.EppRom_Cs) )
  {
    Debug_Print("Measure_Error----->CS Error:0x%lx",CS_IC);  
    MeasuStatusMode.Retry=1;   //����оƬ����д��������
    SET_STRUCT_SUM(MeasuStatusMode);
    return MEASU_CS_ERR;    
  }  
  return   MEASU_NO_ERR;
}

/**********************************************************************************
�������ܣ��ϵ����У��״̬������ʾ
��ڣ���
���ڣ���
**********************************************************************************/	 
void Check_Cal_Status(void)
{
  INT8U Flag,temp;
  
  Flag=Read_Storage_Data_PUCK(DI_CAL_STATUS,&temp,1);  //0����У��1��У���У�2��У����ɣ�
  if(0==Flag)
  {
    ASSERT_FAILED();
    return ;
  }
  if(temp<=1)   //У���¼�����������У����δ�ɹ���   //У���¼�����������У����δ�ɹ���)   //У���¼�����������У����δ�ɹ���
  {    
    for(temp = 0; temp < 3; temp++)
    {
      Main_Dis_Info("CAL ERR");
      Beep_For_Para();
      Clear_All_Dog();
      OS_TimeDly_Ms(200);
    }
  }
}
/**********************************************************************************
�������ܣ���������������
��ڣ�Flag-------1:��ʼ����0---------------������
���ڣ���
**********************************************************************************/	
void Init_Measu_PUCK(void)
{
  
  GetSysModeProc();   //�͹�������Ҫ��ȡ�������
  Get_Curr_Rate();    //��ȡ�͹�������Ҫ�ĵ����������
  
  if(Get_Sys_Status()!=SYS_NORMAL) //ֻ��������ģʽ�£��ų�ʼ����������
    return ;        
   
  Get_Port_Out_Mode();
  Get_Pulse_Para();           //������ز�����ʼ��
  Check_Cal_Status();
  Init_Measure_IC(); 
  Deal_PerSec_Main();
  //GetVoltCurrValue_PUCK();
  GetMeasInstantData_PerSec();   //��ȡ˲ʱ�����ݺ�״̬��
}

/**********************************************************************************
�������ܣ���������������
��ڣ�Flag-------1:��ʼ����0---------------������
���ڣ���
**********************************************************************************/	
void Measu_Main_Puck(INT8U Flag)
{
  
  if(Get_Sys_Status()!=SYS_NORMAL)  //ֻ��������Դ��������£��������ִ��
  {
    while(1)
     Task_Sleep();   
  }
  if(Get_Sys_Status()!=SYS_NORMAL) //ֻ��������ģʽ�£������¼��Ĵ���
    return ;
        
  if(Flag && 0==Pri_MeasuStatVar.MeasuIntOk)  //һ�����룬˵�������ѻ�������ģʽ
  {
   Init_Para();           //������ز�����ʼ��
   Init_Measure_IC();
   return ; 
  }
  else //����ÿ�����һ��
  {   
    //Read_Ext_RTC_Status();          //����ʱ�ӵ��ȶ���
    Check_ALL_Sram_Sum();             //������˽/����У���
    Deal_PerSec_Main();                //�����оƬȡ����
    //Modi_StartCurr_TinyCurr();
    Deal_MeasAppData_PerSec_Main();   //����������ת��������,�ڼ����ݸ��£��������ó�����
    MeasuPara_Modi_PUCK();
    DebugOutMeasuData();
  }
}

/**********************************************************************************

**********************************************************************************/	
void Measu_Event_Main(void)
{
  
  static INT32U Sec_Bak=0xFFFFFFFF;  
  if(Sec_Bak==Sec_Timer_Pub)//ʱ�����һ��
      return ;
  
  Measu_Main_Puck(0);
  Event_main_PUCK(0); 
  Sec_Bak=Sec_Timer_Pub;  
}
