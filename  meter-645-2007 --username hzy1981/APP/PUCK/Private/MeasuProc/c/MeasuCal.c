
#define  CAL_METER_C
#include "Pub_PUCK.h"

#undef Debug_Print
//#define Debug_Print(...)
#define Debug_Print _Debug_Print


#if CAL_METER_TYPE >= SELF_CAL_TYPE 

#define	PAI		3.14159265
#define MAX_REG_NUM    5
typedef struct
{
  PROTO_DI Cal_Para_ID;                 //��Ҫд����������� epprom �� ��ʶ
  volatile signed char    *Min_Err;
  volatile signed char    *Max_Err;
  volatile INT32U   *Meter_Data_Src;     //�������Դ
  volatile INT32U   *Compu_Data_Src;      //̨������Դ
  INT8U    Unit;
  INT8U    Coffi;
  INT8U    Cal_Measu_Num;               //����оƬ��Ӧ��ʵ�ʲ�������
  INT8U    Cal_Reg_ID[MAX_REG_NUM];                //���������£�����ʱ�ĵ�ƽֵ�� 
}CONST_CAL_PARA_INFO;

//���¶���������ڵĳ�����
CONST CONST_CAL_PARA_INFO  Const_Cal_Para_Info[]={
  {0},
  
  {DI_POWER_A_0,&Cal_Proc_Status.Min_Power_Err,&Cal_Proc_Status.Max_Power_Err,&(Pri_TempIntantVar.AcPower.A),&(Cal_Proc_Status.Power_Value[0]),
                100,40,2,{REG_W_PGAIN_A0,REG_W_PGAIN_A1,0,0,0}}, 
  {DI_ANGLE_A_0,&Cal_Proc_Status.Min_Angle_Err,&Cal_Proc_Status.Max_Angle_Err,&(Pri_TempIntantVar.Angle.A),&(Cal_Proc_Status.Angle_Value[0]),
                1,1,5,{REG_W_PHSREG_A0,REG_W_PHSREG_A1,REG_W_PHSREG_A2,REG_W_PHSREG_A3,REG_W_PHSREG_A4}},
    
  {DI_POWER_B_0,&Cal_Proc_Status.Min_Power_Err,&Cal_Proc_Status.Max_Power_Err,&(Pri_TempIntantVar.AcPower.B),&(Cal_Proc_Status.Power_Value[1]),
                100,40,2,{REG_W_PGAIN_B0,REG_W_PGAIN_B1,0,0,0}},
  {DI_ANGLE_B_0,&Cal_Proc_Status.Min_Angle_Err,&Cal_Proc_Status.Max_Angle_Err,&(Pri_TempIntantVar.Angle.B),&(Cal_Proc_Status.Angle_Value[1]),
                1,1,5,{REG_W_PHSREG_B0,REG_W_PHSREG_B1,REG_W_PHSREG_B2,REG_W_PHSREG_B3,REG_W_PHSREG_B4}},
    
  {DI_POWER_C_0,&Cal_Proc_Status.Min_Power_Err,&Cal_Proc_Status.Max_Power_Err,&(Pri_TempIntantVar.AcPower.C),&(Cal_Proc_Status.Power_Value[2]),
                100,40,2,{REG_W_PGAIN_C0,REG_W_PGAIN_C1,0,0,0}},  
  {DI_ANGLE_C_0,&Cal_Proc_Status.Min_Angle_Err,&Cal_Proc_Status.Max_Angle_Err,&(Pri_TempIntantVar.Angle.C),&(Cal_Proc_Status.Angle_Value[2]),
                1,1,5,{REG_W_PHSREG_C0,REG_W_PHSREG_C1,REG_W_PHSREG_C2,REG_W_PHSREG_C3,REG_W_PHSREG_C4}},
  
  {DI_U_GAIN_A,&Cal_Proc_Status.Min_Volt_Err,&Cal_Proc_Status.Max_Volt_Err,&(Pri_TempIntantVar.Volt.A),&(Cal_Proc_Status.Volt_Value[0]),
                1,1,1,{REG_W_UGAIN_A,0,0,0,0}},
  {DI_U_GAIN_B,&Cal_Proc_Status.Min_Volt_Err,&Cal_Proc_Status.Max_Volt_Err,&(Pri_TempIntantVar.Volt.B),&(Cal_Proc_Status.Volt_Value[1]),
                1,1,1,{REG_W_UGAIN_B,0,0,0,0}},
  {DI_U_GAIN_C,&Cal_Proc_Status.Min_Volt_Err,&Cal_Proc_Status.Max_Volt_Err,&(Pri_TempIntantVar.Volt.C),&(Cal_Proc_Status.Volt_Value[2]),
                1,1,1,{REG_W_UGAIN_C,0,0,0,0}},
  
  {DI_I_GAIN_A,&Cal_Proc_Status.Min_Curr_Err,&Cal_Proc_Status.Max_Curr_Err,&(Pri_TempIntantVar.Curr.A),&(Cal_Proc_Status.Curr_Value[0]),
                1,1,1,{REG_W_IGAIN_A,0,0,0,0}},
  {DI_I_GAIN_B,&Cal_Proc_Status.Min_Curr_Err,&Cal_Proc_Status.Max_Curr_Err,&(Pri_TempIntantVar.Curr.B),&(Cal_Proc_Status.Curr_Value[1]),
                1,1,1,{REG_W_IGAIN_B,0,0,0,0}},
  {DI_I_GAIN_C,&Cal_Proc_Status.Min_Curr_Err,&Cal_Proc_Status.Max_Curr_Err,&(Pri_TempIntantVar.Curr.C),&(Cal_Proc_Status.Curr_Value[2]),
                1,1,1,{REG_W_IGAIN_C,0,0,0,0}},
};

/**********************************************************************************
����ԭ�ͣ�void Check_Real_Cal_End(void)
���ܣ���ȡʵ�ʵ�У��״̬

**********************************************************************************/	
INT8U Check_Real_Cal_End(void)
{
  INT8U i;
  
  if(CHECK_STRUCT_SUM(Real_Cal_Status) EQ 0)
    return 0;
  
  for(i=CAL_A_POWER;i<=CAL_C_CURR;i++)
  {
    if(Real_Cal_Status.Cal_Info[i].Cal_OK EQ 0)   //У��ǰ��
      return 0;
  }
  
  return 1;  
}

/**********************************************************************************
����ԭ�ͣ�void Get_self_Cal_Status(INT8U *Src,INT8U SrcLen)
���ܣ���ȡУ��״̬
0-------------------------����У��״̬;
1-------------------------��У��״̬,��û�н���У������;
2-------------------------��У��״̬,�ѽ���У������;
3-------------------------����У��״̬,У���Ѿ����;
**********************************************************************************/	
INT8U Get_self_Cal_Status(void)
{
  
  if(Check_Meter_Factory_Status() EQ 0)//��ǰ���ǹ���״̬���Ƴ�
    return 0;
  
  //���û�յ���̨֡,����;
  if(CHECK_STRUCT_VAR(Cal_Proc_Status) EQ 0)
    return 0;
  
  //���峣��������Ϊ0
  if(Cal_Proc_Status.Ac_Pul_Con EQ 0)
    return 0;
  
  //�޹����峣��
  if(Cal_Proc_Status.ReAc_Pul_Con EQ 0)
    return 0;
  
  
  //У��״̬
  if(Cal_Proc_Status.Cal_Status EQ 0)
    return 1;
  
  //ʵ���Ƿ�У�����
  if(Check_Real_Cal_End())
    return 3;
  
  //У��״̬�Ƿ���λ
  if(Cal_Proc_Status.Cal_Status EQ 1)
    return 2;
  
  
  if(Real_Cal_Status.Cal_Status EQ 1)
    return 2; 
    
  return 3; 
}
/**********************************************************************************
����ԭ�ͣ�void Set_Cal_Com_Data(INT8U *Src,INT8U SrcLen)
���ܣ�����У���ͨ������

**********************************************************************************/	
INT8U Set_Cal_Com_Data(INT8U *Src,INT8U SrcLen)
{
  INT8U Err;
  
  if(SrcLen !=sizeof(Cal_Proc_Status) || Check_Meter_Factory_Status() EQ 0)//��ǰ���ǹ���״̬���Ƴ�
  {
    ASSERT_FAILED();
    return 0;
  }
    
  mem_cpy((void *)(&Cal_Proc_Status),Src,SrcLen,(void *)(&Cal_Proc_Status),sizeof(Cal_Proc_Status));
  //�������������жϴ������
  Err=0;
  if(CHECK_STRUCT_VAR(Cal_Proc_Status) EQ 0)
    Err=1;
  //У����Ŀ����
  if(Cal_Proc_Status.Cal_Item>=CAL_ITEM_NUM)
    Err=1;   
  
   //���峣��������Ϊ0
  if(Cal_Proc_Status.Ac_Pul_Con EQ 0)
    Err=1; 
  
  //�޹����峣��
  if(Cal_Proc_Status.ReAc_Pul_Con EQ 0)
    Err=1; 
  
  if(Err)
  {
    mem_set((void *)(&Cal_Proc_Status),0,sizeof(Cal_Proc_Status),\
               (void *)(&Cal_Proc_Status),sizeof(Cal_Proc_Status));   
    return 0;
  }
  
  //��ʼ�� Real_Cal_Status
  SET_STRUCT_SUM(Real_Cal_Status); 
  return 1;
}
/**********************************************************************************
����ԭ�ͣ�void Self_Cal_Para_Proc(void)
���ܣ�У������Զ�ʶ��,�����´���

**********************************************************************************/	
void Self_Cal_Para_Proc(void)
{
  INT8U temp[4];

  
  if(Get_self_Cal_Status()  EQ 0)  //����У��״̬�������Ͳ��ܽ�������
    return ;
  
  //��Ҫ���ݱ��ƻ������� Set_Cal_Com_Data û������
  if(CHECK_STRUCT_SUM(Real_Cal_Status) EQ 0)
    return ;
    
  
  //����У��״̬
  if(CHECK_STRUCT_SUM(Real_Cal_Status))
  {
    if(Cal_Proc_Status.Cal_Status EQ 1 && Real_Cal_Status.Cal_Status EQ 0) //У��ʼ
    {
      Real_Cal_Status.Cal_Status=1;
      SET_STRUCT_SUM(Real_Cal_Status); 
      
      if(Write_Storage_Data(DI_CAL_STATUS,(INT8U *)(&Real_Cal_Status.Cal_Status),1) EQ 0)
        ASSERT_FAILED();
    }
    
    if(Real_Cal_Status.Cal_Status EQ 1) //У����-------->У�����
    {
       if(Check_Real_Cal_End())  // Get_self_Cal_Status() EQ 3) //У�����
       {
          Real_Cal_Status.Cal_Status=2;
          //Real_Cal_Status.Clr_Para=0;
          SET_STRUCT_SUM(Real_Cal_Status); 
          if(Write_Storage_Data(DI_CAL_STATUS,(INT8U *)(&Real_Cal_Status.Cal_Status),1) EQ 0)
            ASSERT_FAILED(); 
       }
    }    
  }
  
  
  //����У��״̬�� �����Ͳ��ܽ������̣�����У���Ѿ������ˣ�
  if(CHECK_CAL_STATUS EQ 0)
    return ;
  
  
  //�ж�: �Ƿ�������У�����
  if((Real_Cal_Status.Clr_Para EQ 0)&&(Cal_Proc_Status.Clr_Para EQ 0xD3))  //��Ҫ���Ʋ�����
  {
     Real_Cal_Status.Clr_Para=0XD3;
     SET_STRUCT_SUM(Real_Cal_Status); 
     Set_Def_Adj_Para();  //У���������.
     
     if(Check_Meter_Factory_Status())//��ǰ�ǹ���״̬���ٴ�ȷ�ϣ�����һ��
     {
       temp[2]=Cal_Proc_Status.P_Spec;
       temp[1]=Cal_Proc_Status.V_Spec;
       temp[0]=Cal_Proc_Status.I_Spec;     
       if(Write_Storage_Data(DI_P_U_I_SPEC,temp,3) EQ 0)  //����д��
          ASSERT_FAILED();
        

        //�����峣��ת���� BCD��,���ڴ洢.
        Hex2Bcd(Cal_Proc_Status.Ac_Pul_Con,temp,4,temp,4);      
        if(Write_Storage_Data(DI_AC_PULSE,temp,3) EQ 0)     //д��
          ASSERT_FAILED();
        
        //�����峣��ת���� BCD��,���ڴ洢.
        Hex2Bcd(Cal_Proc_Status.ReAc_Pul_Con,temp,4,temp,4);      
        if(Write_Storage_Data(DI_REAC_PULSE,temp,3) EQ 0)   //д��
          ASSERT_FAILED();
     }
     Init_Para();                //��ʼ����У������޹صĲ���
     Init_Measure_IC();          //��λ����оƬ,�����ü�������
     OS_TimeDly_Ms(100);  //for Cs Refresh  
  }
}
/**********************************************************************************
�������ܣ����ݲ�ͬ�����ͣ���ȡ��ǰ�����ֵ=(����ֵ-��ʵֵ)/��ʵֵ
���ڣ�
    (��ֵ-̨��ֵ)/ ̨��ֵ������/̨��)-1
**********************************************************************************/
//Ҫ���ǲ��ǵ�һ�����,���� Err_New
INT32U Get_Err_Reg(INT8U Item,INT8U *Result)
{
  FP32S err_run,Err_Formula,Err_Obj,Measu,err_orig;
  INT32U Reg_Value;
  INT8U sign;

  if(CHECK_STRUCT_SUM(Pri_TempIntantVar) EQ 0)
    ASSERT_FAILED();
  
  if(Item<CAL_A_POWER || Item>CAL_C_CURR)
  {
    ASSERT_FAILED();
    *Result=0;
    return 0;
  }
  
  if(Real_Cal_Status.Cal_Info[Item].Cal_OK EQ 1)  //��У�ɹ�
  {
    *Result=0;
    return 0;
  }   
    
  Measu=(FP32S)(*Const_Cal_Para_Info[Item].Meter_Data_Src); 
  if(Measu >= -0.00001 && Measu <= 0.0001)   //У���Ӧ������ʱ����Ӧ�����ݲ�����Ϊ0.
  {
    ASSERT_FAILED();
    *Result=0;
    return 0;
  }
  

  err_orig=Measu/(((FP32S)(*Const_Cal_Para_Info[Item].Compu_Data_Src))*Const_Cal_Para_Info[Item].Unit)-1; //��ǰ�����ԭʼʵ�����
  
  if(err_orig>=(FP32S)(*Const_Cal_Para_Info[Item].Min_Err)/10000.0 && err_orig<=(FP32S)(*Const_Cal_Para_Info[Item].Max_Err)/10000.0)  //�ж������
  {
    Real_Cal_Status.Cal_Info[Item].Cal_OK=1;  //��ǰ��ĿУ���ɹ�
    SET_STRUCT_SUM(Real_Cal_Status);
    *Result=0;
    return 0;        
  }
  
 
  
  Reg_Value=0;
  Err_Obj=(*Const_Cal_Para_Info[Item].Min_Err+*Const_Cal_Para_Info[Item].Max_Err)/20000.0;          //ʵ�ʵ�����յ�
  err_run=Measu/(((FP32S)(*Const_Cal_Para_Info[Item].Compu_Data_Src))*Const_Cal_Para_Info[Item].Unit*(1+Err_Obj))-1; //��ǰ�����ʵ�����
  
  if(err_run>=-0.99998 && err_run <=-1.0001)   //��ֹ Err_Formula��ĸΪ0
  {
    ASSERT_FAILED();
    *Result=0;
    return 0;
  }
  
  if(Real_Cal_Status.Cal_Info[Item].Cal_First EQ 0)//��һ��У��
  {
   if(Item EQ CAL_A_ANGLE || Item EQ CAL_B_ANGLE || Item EQ CAL_C_ANGLE )   //��λУ��
      Err_Formula=acos((1+err_run)*0.5)-PAI/3;
    else
      Err_Formula=-1*(err_run/(1+err_run));
    
    if(Err_Formula>=0)
      Reg_Value=(INT32U)(Err_Formula*pow(2,23));
    else
      Reg_Value=(INT32U)(Err_Formula*pow(2,23)+pow(2,24));
  }
  else
  {
    err_run=(err_run)/Const_Cal_Para_Info[Item].Coffi;  //�������
    
    if(Item EQ CAL_A_ANGLE || Item EQ CAL_B_ANGLE || Item EQ CAL_C_ANGLE )   //��λУ��
      Err_Formula=(acos((1+err_run)*0.5)-PAI/3); 
    else
      Err_Formula=-1*(err_run/(1+err_run));
    
    if(Err_Formula<=0)
      Err_Formula=-1*Err_Formula;    
    Reg_Value=(INT32U)(Err_Formula*pow(2,23));  //ȡ����ֵ
    
    sign=0;
    if((Item EQ CAL_A_ANGLE)||(Item EQ CAL_B_ANGLE)||(Item EQ CAL_C_ANGLE))  //��λУ��
    {
      if(err_orig<*Const_Cal_Para_Info[Item].Min_Err/10000.0)
        sign=1;
    }
    else
    {
      if(err_orig>*Const_Cal_Para_Info[Item].Max_Err/10000.0)
        sign=1;      
    }
    
    if(sign)
      Reg_Value=(INT32U)(Real_Cal_Status.Para_Reg[Item]-Reg_Value+pow(2,24));
    else
      Reg_Value=Real_Cal_Status.Para_Reg[Item]+Reg_Value;  
  }
 
  *Result=1;
  return (INT32U)(Reg_Value&0x00FFFFFF);
}
/**********************************************************************************
�������ܣ����ݵ�ǰ���,�ó�д�����оƬ�Ĵ����Ĳ���
���ڣ����

**********************************************************************************/
void Self_Cal_Err_Proc(void)
{ 
  INT8U i,j,Flag;
  INT32U Cla_Reg_Data;
  
  if(Get_self_Cal_Status() !=2)
    return ;
  
  
   //��Ҫ���ݱ��ƻ������� Set_Cal_Com_Data û������
  if(CHECK_STRUCT_SUM(Real_Cal_Status) EQ 0)
    return ;
  
  if((Cal_Proc_Status.Cal_Item<CAL_A_POWER) || (Cal_Proc_Status.Cal_Item>CAL_C_CURR))
    return ;
  
  
  if((Cal_Proc_Status.Cal_Item>=CAL_A_POWER) && (Cal_Proc_Status.Cal_Item<=CAL_C_ANGLE))
  {
    Cla_Reg_Data=Get_Err_Reg(Cal_Proc_Status.Cal_Item,&Flag);
    if(Flag EQ 0)  //�쳣��������д��
      return ;
    
    EnMeasuCal();                             //У������дʹ��
    //���¼�������
    Real_Cal_Status.Para_Reg[Cal_Proc_Status.Cal_Item]=Cla_Reg_Data;
    for(i=0;i<Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Cal_Measu_Num;i++)  //�����еĲ����Ĵ���д
    {
      if(Check_Meter_Factory_Status())//��ǰ�ǹ���״̬���ٴ�ȷ�ϣ�����һ��
      {
         if(Measu_WrAndCompData_3Times(Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Cal_Reg_ID[i],Cla_Reg_Data) EQ 0)
           ASSERT_FAILED();
      }
    }
    
    if(Check_Meter_Factory_Status())//��ǰ�ǹ���״̬���ٴ�ȷ�ϣ�����һ��
    {
      //����epprom �ļ�������
      if(Write_Storage_Data(Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Cal_Para_ID,&Cla_Reg_Data,3) EQ 0)
        ASSERT_FAILED();
    }
    Real_Cal_Status.Cal_Info[Cal_Proc_Status.Cal_Item].Cal_First=1;
    Real_Cal_Status.Cal_Info[Cal_Proc_Status.Cal_Item].Cal_Times++;
    SET_STRUCT_SUM(Real_Cal_Status);  
  
    Debug_Print("Cal_Info----->Cal_Item=%d,Cal_Times=%d,Real_Data=%ld,Meter_Data=%ld",
                             Cal_Proc_Status.Cal_Item,Real_Cal_Status.Cal_Info[Cal_Proc_Status.Cal_Item].Cal_Times,
                             *Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Compu_Data_Src,
                             *Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Meter_Data_Src);
    
  }
  else
  {
    EnMeasuCal();                             //У������дʹ��
    for(i=CAL_A_VOLT;i<=CAL_C_CURR;i++)
    {
      Cla_Reg_Data=Get_Err_Reg(i,&Flag);
      if(Flag EQ 0)  //�쳣��������д��
      continue ; 
      
      Real_Cal_Status.Para_Reg[i]=Cla_Reg_Data;
      for(j=0;j<Const_Cal_Para_Info[i].Cal_Measu_Num;j++)  //�����еĲ����Ĵ���д
      {
          if(Check_Meter_Factory_Status())//��ǰ�ǹ���״̬���ٴ�ȷ�ϣ�����һ��
          {
            if(Measu_WrAndCompData_3Times(Const_Cal_Para_Info[i].Cal_Reg_ID[j],Cla_Reg_Data) EQ 0)
              ASSERT_FAILED();
          }
      }
      //����epprom �ļ�������
      if(Check_Meter_Factory_Status())//��ǰ�ǹ���״̬���ٴ�ȷ�ϣ�����һ��
      {
        if(Write_Storage_Data(Const_Cal_Para_Info[i].Cal_Para_ID,&Cla_Reg_Data,3) EQ 0)
          ASSERT_FAILED();
      }
    
      Real_Cal_Status.Cal_Info[i].Cal_First=1;
      Real_Cal_Status.Cal_Info[i].Cal_Times++;
      SET_STRUCT_SUM(Real_Cal_Status);  
  
      Debug_Print("Cal_Info----->Cal_Item=%d,Cal_Times=%d,Real_Data=%ld,Meter_Data=%ld",
                             i,Real_Cal_Status.Cal_Info[i].Cal_Times,
                             *Const_Cal_Para_Info[i].Compu_Data_Src,
                             *Const_Cal_Para_Info[i].Meter_Data_Src);
      
    }    
  }
  
  DisMeasuCal();  
  //OS_TimeDly_Ms(300);  //for Cs Refresh  
}
/**********************************************************************************
����ԭ�ͣ�void Set_Self_Cal_Item(void)
���ܣ����ñ��У��״̬

**********************************************************************************/	
void Self_Cal_Proc(void)
{  
  Self_Cal_Para_Proc();
  Self_Cal_Err_Proc(); 
}
#endif
