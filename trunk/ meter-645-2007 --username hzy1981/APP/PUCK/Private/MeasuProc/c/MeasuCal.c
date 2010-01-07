
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
  PROTO_DI Cal_Para_ID;                 //需要写入计量参数到 epprom 的 标识
  volatile signed char    *Min_Err;
  volatile signed char    *Max_Err;
  volatile INT32U   *Meter_Data_Src;     //表计数据源
  volatile INT32U   *Compu_Data_Src;      //台体数据源
  INT8U    Unit;
  INT8U    Coffi;
  INT8U    Cal_Measu_Num;               //计量芯片对应的实际参数个数
  INT8U    Cal_Reg_ID[MAX_REG_NUM];                //正常工作下，闲置时的电平值； 
}CONST_CAL_PARA_INFO;

//以下对所有输出口的抽象定义
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
函数原型：void Check_Real_Cal_End(void)
功能：获取实际的校表状态

**********************************************************************************/	
INT8U Check_Real_Cal_End(void)
{
  INT8U i;
  
  if(CHECK_STRUCT_SUM(Real_Cal_Status) EQ 0)
    return 0;
  
  for(i=CAL_A_POWER;i<=CAL_C_CURR;i++)
  {
    if(Real_Cal_Status.Cal_Info[i].Cal_OK EQ 0)   //校当前项
      return 0;
  }
  
  return 1;  
}

/**********************************************************************************
函数原型：void Get_self_Cal_Status(INT8U *Src,INT8U SrcLen)
功能：获取校表状态
0-------------------------不是校表状态;
1-------------------------是校表状态,但没有进入校表流程;
2-------------------------是校表状态,已进入校表流程;
3-------------------------不是校表状态,校表已经完成;
**********************************************************************************/	
INT8U Get_self_Cal_Status(void)
{
  
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
    return 0;
  
  //如果没收到主台帧,返回;
  if(CHECK_STRUCT_VAR(Cal_Proc_Status) EQ 0)
    return 0;
  
  //脉冲常数不可能为0
  if(Cal_Proc_Status.Ac_Pul_Con EQ 0)
    return 0;
  
  //无功脉冲常数
  if(Cal_Proc_Status.ReAc_Pul_Con EQ 0)
    return 0;
  
  
  //校表状态
  if(Cal_Proc_Status.Cal_Status EQ 0)
    return 1;
  
  //实际是否校正完成
  if(Check_Real_Cal_End())
    return 3;
  
  //校表状态是否置位
  if(Cal_Proc_Status.Cal_Status EQ 1)
    return 2;
  
  
  if(Real_Cal_Status.Cal_Status EQ 1)
    return 2; 
    
  return 3; 
}
/**********************************************************************************
函数原型：void Set_Cal_Com_Data(INT8U *Src,INT8U SrcLen)
功能：设置校表的通信数据

**********************************************************************************/	
INT8U Set_Cal_Com_Data(INT8U *Src,INT8U SrcLen)
{
  INT8U Err;
  
  if(SrcLen !=sizeof(Cal_Proc_Status) || Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
  {
    ASSERT_FAILED();
    return 0;
  }
    
  mem_cpy((void *)(&Cal_Proc_Status),Src,SrcLen,(void *)(&Cal_Proc_Status),sizeof(Cal_Proc_Status));
  //以下增加数据判断错误代码
  Err=0;
  if(CHECK_STRUCT_VAR(Cal_Proc_Status) EQ 0)
    Err=1;
  //校表项目错误
  if(Cal_Proc_Status.Cal_Item>=CAL_ITEM_NUM)
    Err=1;   
  
   //脉冲常数不可能为0
  if(Cal_Proc_Status.Ac_Pul_Con EQ 0)
    Err=1; 
  
  //无功脉冲常数
  if(Cal_Proc_Status.ReAc_Pul_Con EQ 0)
    Err=1; 
  
  if(Err)
  {
    mem_set((void *)(&Cal_Proc_Status),0,sizeof(Cal_Proc_Status),\
               (void *)(&Cal_Proc_Status),sizeof(Cal_Proc_Status));   
    return 0;
  }
  
  //初始化 Real_Cal_Status
  SET_STRUCT_SUM(Real_Cal_Status); 
  return 1;
}
/**********************************************************************************
函数原型：void Self_Cal_Para_Proc(void)
功能：校表参数自动识别,并更新处理

**********************************************************************************/	
void Self_Cal_Para_Proc(void)
{
  INT8U temp[4];

  
  if(Get_self_Cal_Status()  EQ 0)  //不是校表状态：根本就不能进入流程
    return ;
  
  //重要数据被破坏；或者 Set_Cal_Com_Data 没被调用
  if(CHECK_STRUCT_SUM(Real_Cal_Status) EQ 0)
    return ;
    
  
  //设置校表状态
  if(CHECK_STRUCT_SUM(Real_Cal_Status))
  {
    if(Cal_Proc_Status.Cal_Status EQ 1 && Real_Cal_Status.Cal_Status EQ 0) //校表开始
    {
      Real_Cal_Status.Cal_Status=1;
      SET_STRUCT_SUM(Real_Cal_Status); 
      
      if(Write_Storage_Data(DI_CAL_STATUS,(INT8U *)(&Real_Cal_Status.Cal_Status),1) EQ 0)
        ASSERT_FAILED();
    }
    
    if(Real_Cal_Status.Cal_Status EQ 1) //校表中-------->校表完成
    {
       if(Check_Real_Cal_End())  // Get_self_Cal_Status() EQ 3) //校表完成
       {
          Real_Cal_Status.Cal_Status=2;
          //Real_Cal_Status.Clr_Para=0;
          SET_STRUCT_SUM(Real_Cal_Status); 
          if(Write_Storage_Data(DI_CAL_STATUS,(INT8U *)(&Real_Cal_Status.Cal_Status),1) EQ 0)
            ASSERT_FAILED(); 
       }
    }    
  }
  
  
  //不是校表状态： 根本就不能进入流程，或者校表已经结束了！
  if(CHECK_CAL_STATUS EQ 0)
    return ;
  
  
  //判定: 是否清除表计校表参数
  if((Real_Cal_Status.Clr_Para EQ 0)&&(Cal_Proc_Status.Clr_Para EQ 0xD3))  //需要清表计参数了
  {
     Real_Cal_Status.Clr_Para=0XD3;
     SET_STRUCT_SUM(Real_Cal_Status); 
     Set_Def_Adj_Para();  //校表参数清零.
     
     if(Check_Meter_Factory_Status())//当前是工厂状态，再次确认，保险一点
     {
       temp[2]=Cal_Proc_Status.P_Spec;
       temp[1]=Cal_Proc_Status.V_Spec;
       temp[0]=Cal_Proc_Status.I_Spec;     
       if(Write_Storage_Data(DI_P_U_I_SPEC,temp,3) EQ 0)  //重新写入
          ASSERT_FAILED();
        

        //将脉冲常数转换成 BCD码,用于存储.
        Hex2Bcd(Cal_Proc_Status.Ac_Pul_Con,temp,4,temp,4);      
        if(Write_Storage_Data(DI_AC_PULSE,temp,3) EQ 0)     //写入
          ASSERT_FAILED();
        
        //将脉冲常数转换成 BCD码,用于存储.
        Hex2Bcd(Cal_Proc_Status.ReAc_Pul_Con,temp,4,temp,4);      
        if(Write_Storage_Data(DI_REAC_PULSE,temp,3) EQ 0)   //写入
          ASSERT_FAILED();
     }
     Init_Para();                //初始化与校表参数无关的参数
     Init_Measure_IC();          //复位计量芯片,并重置计量参数
     OS_TimeDly_Ms(100);  //for Cs Refresh  
  }
}
/**********************************************************************************
函数功能：根据不同的类型，获取当前的误差值=(测量值-真实值)/真实值
出口：
    (表值-台体值)/ 台体值＝（表/台体)-1
**********************************************************************************/
//要考虑不是第一次情况,更新 Err_New
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
  
  if(Real_Cal_Status.Cal_Info[Item].Cal_OK EQ 1)  //已校成功
  {
    *Result=0;
    return 0;
  }   
    
  Measu=(FP32S)(*Const_Cal_Para_Info[Item].Meter_Data_Src); 
  if(Measu >= -0.00001 && Measu <= 0.0001)   //校相对应的数据时，对应的数据不可能为0.
  {
    ASSERT_FAILED();
    *Result=0;
    return 0;
  }
  

  err_orig=Measu/(((FP32S)(*Const_Cal_Para_Info[Item].Compu_Data_Src))*Const_Cal_Para_Info[Item].Unit)-1; //当前算出的原始实际误差
  
  if(err_orig>=(FP32S)(*Const_Cal_Para_Info[Item].Min_Err)/10000.0 && err_orig<=(FP32S)(*Const_Cal_Para_Info[Item].Max_Err)/10000.0)  //判定误差限
  {
    Real_Cal_Status.Cal_Info[Item].Cal_OK=1;  //当前项目校正成功
    SET_STRUCT_SUM(Real_Cal_Status);
    *Result=0;
    return 0;        
  }
  
 
  
  Reg_Value=0;
  Err_Obj=(*Const_Cal_Para_Info[Item].Min_Err+*Const_Cal_Para_Info[Item].Max_Err)/20000.0;          //实际的误差终点
  err_run=Measu/(((FP32S)(*Const_Cal_Para_Info[Item].Compu_Data_Src))*Const_Cal_Para_Info[Item].Unit*(1+Err_Obj))-1; //当前算出的实际误差
  
  if(err_run>=-0.99998 && err_run <=-1.0001)   //防止 Err_Formula分母为0
  {
    ASSERT_FAILED();
    *Result=0;
    return 0;
  }
  
  if(Real_Cal_Status.Cal_Info[Item].Cal_First EQ 0)//第一次校正
  {
   if(Item EQ CAL_A_ANGLE || Item EQ CAL_B_ANGLE || Item EQ CAL_C_ANGLE )   //相位校正
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
    err_run=(err_run)/Const_Cal_Para_Info[Item].Coffi;  //修正误差
    
    if(Item EQ CAL_A_ANGLE || Item EQ CAL_B_ANGLE || Item EQ CAL_C_ANGLE )   //相位校正
      Err_Formula=(acos((1+err_run)*0.5)-PAI/3); 
    else
      Err_Formula=-1*(err_run/(1+err_run));
    
    if(Err_Formula<=0)
      Err_Formula=-1*Err_Formula;    
    Reg_Value=(INT32U)(Err_Formula*pow(2,23));  //取绝对值
    
    sign=0;
    if((Item EQ CAL_A_ANGLE)||(Item EQ CAL_B_ANGLE)||(Item EQ CAL_C_ANGLE))  //相位校正
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
函数功能：根据当前误差,得出写入计量芯片寄存器的参数
出口：误差

**********************************************************************************/
void Self_Cal_Err_Proc(void)
{ 
  INT8U i,j,Flag;
  INT32U Cla_Reg_Data;
  
  if(Get_self_Cal_Status() !=2)
    return ;
  
  
   //重要数据被破坏；或者 Set_Cal_Com_Data 没被调用
  if(CHECK_STRUCT_SUM(Real_Cal_Status) EQ 0)
    return ;
  
  if((Cal_Proc_Status.Cal_Item<CAL_A_POWER) || (Cal_Proc_Status.Cal_Item>CAL_C_CURR))
    return ;
  
  
  if((Cal_Proc_Status.Cal_Item>=CAL_A_POWER) && (Cal_Proc_Status.Cal_Item<=CAL_C_ANGLE))
  {
    Cla_Reg_Data=Get_Err_Reg(Cal_Proc_Status.Cal_Item,&Flag);
    if(Flag EQ 0)  //异常，不需再写！
      return ;
    
    EnMeasuCal();                             //校表数据写使能
    //更新计量参数
    Real_Cal_Status.Para_Reg[Cal_Proc_Status.Cal_Item]=Cla_Reg_Data;
    for(i=0;i<Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Cal_Measu_Num;i++)  //对所有的补偿寄存器写
    {
      if(Check_Meter_Factory_Status())//当前是工厂状态，再次确认，保险一点
      {
         if(Measu_WrAndCompData_3Times(Const_Cal_Para_Info[Cal_Proc_Status.Cal_Item].Cal_Reg_ID[i],Cla_Reg_Data) EQ 0)
           ASSERT_FAILED();
      }
    }
    
    if(Check_Meter_Factory_Status())//当前是工厂状态，再次确认，保险一点
    {
      //更新epprom 的计量参数
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
    EnMeasuCal();                             //校表数据写使能
    for(i=CAL_A_VOLT;i<=CAL_C_CURR;i++)
    {
      Cla_Reg_Data=Get_Err_Reg(i,&Flag);
      if(Flag EQ 0)  //异常，不需再写！
      continue ; 
      
      Real_Cal_Status.Para_Reg[i]=Cla_Reg_Data;
      for(j=0;j<Const_Cal_Para_Info[i].Cal_Measu_Num;j++)  //对所有的补偿寄存器写
      {
          if(Check_Meter_Factory_Status())//当前是工厂状态，再次确认，保险一点
          {
            if(Measu_WrAndCompData_3Times(Const_Cal_Para_Info[i].Cal_Reg_ID[j],Cla_Reg_Data) EQ 0)
              ASSERT_FAILED();
          }
      }
      //更新epprom 的计量参数
      if(Check_Meter_Factory_Status())//当前是工厂状态，再次确认，保险一点
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
函数原型：void Set_Self_Cal_Item(void)
功能：设置表的校表状态

**********************************************************************************/	
void Self_Cal_Proc(void)
{  
  Self_Cal_Para_Proc();
  Self_Cal_Err_Proc(); 
}
#endif
