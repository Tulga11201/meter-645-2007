#define MEASULIB_PUCK
#include "Pub_PUCK.h"
#include   "MeasuLib.h"


/******************************文件功能*********************************************
文件功能：计量库函数，包括：

***********************************************************************************/
/**********************************************************************************/
void Delayn10MS(INT32U n)
{
  INT32U i;
  for(i=0;i<n;i++)
  {
    WAITFOR_DRV_MS_TIMEOUT(10);
  }
}

/**********************************************************************************
函数功能：清除计量所有电能寄存器内容,电能初值为0
入口： 无   
出口： 1---------成功;
       0---------失败;
**********************************************************************************/
INT8U Clr_Energ_Reg_PwrOn(void)
{
  INT8U i,Flag,temp[4];
  
  //读A、B、C及合相有功电能，无功电能，清电能寄存器数据-------------------------------PUCK
  for(i=REG_R_AENERG_CLR;i<=REG_R_SUMENERG_CLR;i++)
  {
    Flag=Measu_RdAndCompData_3Times(i,temp);
    if(Flag==0)
      break;
  }
  return  Flag;
}  

/**********************************************************************************
函数功能：硬件复位
入口：    
LastData-----参数寄存器地址
LastPara-------参数
出口： 1---------SIG软硬件信号都正确,复位成功;
       0---------SIG软硬件信号任何一个不对,复位失败;
**********************************************************************************/
INT8U MeasuIC_HardRst(void)
{
  INT8U i,flag;
  INT32U temp;
  
  //CLOSE_MEASU_PWR;
  //SYS_TimeDly_Ms(200);                  //延时200ms
  OPEN_MEASU_PWR;
  SYS_TimeDly_Ms(20);            //延时200ms 
  for(i=0;i<5;i++)
  {
    MEASU_RST_0;
    SYS_TimeDly_Ms(10);           //原则上延时25us即可！
    MEASU_RST_1;
    SYS_TimeDly_Ms(10);            //原则上复位后500us才能操作SPI
    if(!MEASU_SIG_STAT)          //判断SIG脚是否为0，若是，则表示正常------------------PUCK  
    {
      //SYS_TimeDly_Ms(10);           //延时10mS
      flag=Measu_RdAndCompData_3Times(REG_R_SIG,(INT8U *)&temp);
           
      if((flag==0)||(temp==0xffffff))
      {
        continue;
      }
      if(GET_BIT(temp,7))        //判断Sflag.7状态是否为1，若是，则表示正常------------------PUCK
      {
        Debug_Print("MeasuIC Reset Ok,SIG=0X%lx!",temp);  
        return 1;
      }
      SYS_TimeDly_Ms(50);            //延时50mS
    }
    else
    {
      SYS_TimeDly_Ms(50);               //延时50mS
    }    
  }
  MeasuStatusMode.HardRstErr=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return  0;
}
/**********************************************************************************
函数功能： 清除上电校表请求字
入口：   void
出口： 1-------表示需要校表；0--------------表示不需要校表
**********************************************************************************/
void Clr_Cal_Requst(void)
{
  INT8U Flag,i;
  INT32U temp;
  
  for(i=0;i<3;i++)
  {
    Flag=Measu_RdAndCompData_3Times(REG_R_ENFLAG,(INT8U *)&temp);
    if((Flag==0)||(temp==0xffffff))  //避免状态寄存器读错后，对电能的影响，此值不可能都为0xffffff
    continue;
    
    if(GET_BIT(temp,16)==0)           //判断Sflag.16状态是否为1，若是，则表示校表请求
      return ;
  }
}
/**********************************************************************************
函数功能：对计量芯片的para和内卡para比对，重新装载参数
入口：    
出口：1----------装载成功 
**********************************************************************************/
INT8U Load_MeasureIC_Para(void)
{
  INT8U Flag;
  
  Flag=Load_All_Para_To_IC();      
  if(Flag)                     //写入成功
  {
    //Clr_Energ_Reg_PwrOn();    //清除电能寄存器
    Pri_MeasuStatVar.MeasuIntOk=1;   //计量芯片初始化完成，进入正常计量流程
    Init_Pulse_Port(1);
    SET_STRUCT_SUM(Pri_MeasuStatVar);
    Debug_Print("Write To IC Para Succeed!");
    Clr_Cal_Requst();
  }
  else
  {
    MeasuStatusMode.Retry=1;   //计量芯片参数写错误重试
    SET_STRUCT_SUM(MeasuStatusMode);
    Debug_Print("Write To IC Para Failed,Waiting For Retry!");
  }
  return Flag;  
}
/**********************************************************************************
函数功能：上电初始化MeasuIC
入口：    
LastData-----参数寄存器地址
LastPara-------参数
出口： 表示复位成功;返回0：表示复位失败
**********************************************************************************/
INT8U InitMeasuAfterPwrOn(void)
{
  INT8U Flag;
  
  Flag=MeasuIC_HardRst();
  if(!Flag)     //硬件复位失败
  {
    Beep_For_Measu_Alarm_PUCK(MEASU_RESET_ERR);
    Debug_Print("Measure_Error----->Hard Reset Error After Power On!");
    return 0;
  }
  
  //Flag=Clr_Energ_Reg_PwrOn();    //如果硬件可靠复位，芯片内部自行清除，此句可以屏蔽
  Flag=Load_MeasureIC_Para();
  Clr_Energ_Accu();   //清除用于计算电能增量的寄存器
  return Flag;
}
/**********************************************************************************
函数功能：复位计量芯片,并重置计量参数
入口：    
LastData-----参数寄存器地址
LastPara-------参数
出口： 表示复位成功;返回0：表示复位失败
**********************************************************************************/
void Init_Measure_IC(void)
{
  InitMeasuAfterPwrOn();
  SET_STRUCT_SUM(Pri_MeasuStatVar);
}
/**********************************************************************************
函数功能：检查SIG引脚状态以及校表参数校验和是否正确
入口：无
出口：1-------状态正常;0--------状态异常
**********************************************************************************/
INT8U ChkMeasuICWorkStatus(void)
{
  INT8U i,num;

  if(MEASU_SIG_STAT) //正常
    return MEASU_NO_ERR;
  
  for(i=0,num=0;i<5;i++)  //连续读5次
  {
    SYS_TimeDly_Ms(10);
    if(!MEASU_SIG_STAT)      //异常
      num++;
  }
  
  if(num<=2)   //5次中有3次以上是正常的
     return MEASU_NO_ERR;

  Debug_Print("Measure_Error----->MeasuIC Hard SIG_Signal=0!"); 
  MeasuStatusMode.Retry=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return MEASU_SIGN_ERR; 
}
/**********************************************************************************
函数功能：获取当前 331/341模式字
入口：无
出口：331/341模式字
**********************************************************************************/
INT8U Get_SysParse_Mode(void)
{ 
  if(MeasuSysMode.ParseMode<=PARSE_341)
    return MeasuSysMode.ParseMode;
  
  ASSERT_FAILED();
  return DEFAULT_PARSE_SPEC;
}

/**********************************************************************************
函数功能：获取电压通道ADC增益倍数
入口：无
出口：电压通道ADC增益倍数
**********************************************************************************/
INT32U Get_Volt_Adj_Rate(void)
{  
  
   if(Get_SysParse_Mode()==PARSE_331)    //331模式下电压通道ADC增益选择为2倍
    return V_GAIN_RATE2;
                       
    //341模式下电压通道ADC增益选择为1倍
    return V_GAIN_RATE1;
}

/**********************************************************************************
函数功能：获取失压阀值
入口：无
出口：失压阀值
**********************************************************************************/
INT32U Get_FailVolt_Para(void)
{  
  if(Get_SysParse_Mode()==PARSE_331)    //331模式下
    return 0x00190000;
                       
    //341模式下
   return 0x00068000;
}
/**********************************************************************************
函数功能：获取当前 电压规格模式字
入口：无
出口：电压模式字
**********************************************************************************/
INT8U Get_SysVolt_Mode(void)
{  
  if(MeasuSysMode.V_Spec<=VOLT_3380)
    return MeasuSysMode.V_Spec;
  
  ASSERT_FAILED(); 
  return DEFAULT_VOLT_SPEC;
}

/**********************************************************************************
函数功能：获取当前 电流规格模式字
入口：无
出口：电流模式字
**********************************************************************************/
INT8U Get_SysCurr_Mode(void)
{
  if(MeasuSysMode.I_Spec<=CURR_30_100)
    return MeasuSysMode.I_Spec;
  
  ASSERT_FAILED();
  return DEFAULT_CURR_SPEC;
}
/**********************************************************************************
函数功能：获取当前脉冲常数模式字
入口：无
出口：331/341模式字
**********************************************************************************/
INT8U Get_SysPulse_Mode(void)
{  
  if(MeasuSysMode.P_Spec<=PULSE_TYPE2)
    return MeasuSysMode.P_Spec;
  
  ASSERT_FAILED();
  return DEFAULT_PULSE_SPEC;
}

/**********************************************************************************
函数功能：获取TH和TF模式字
入口：无
出口：TH_MODE/TF_MODE模式字
**********************************************************************************/
INT8U Get_SysTHF_Mode(void)
{
  if(MeasuSysMode.T_FH<=TF_MODE)
    return MeasuSysMode.T_FH;
  
  ASSERT_FAILED();
  return DEFAULT_TFH_SPEC;
}

/**********************************************************************************
函数功能：获取视在电能参数
入口：无
出口：
**********************************************************************************/
INT32U Get_App_Mode(void)
{
  return APP_ENERG_MODE;
}
/**********************************************************************************
函数功能：根据331/341和TF/TH模式字来决定MeasuIC合相能量累加寄存器；
入口：无
出口：
        ENERG_SUM_MODE0-------341绝对和加；331代数和
        ENERG_SUM_MODE1--------341代数和加；331绝对
**********************************************************************************/
INT32U GetEnergSumMode(void)
{
  INT8U THF_Spec,ParseMode;
  INT32U WrPara;
  
  THF_Spec=Get_SysTHF_Mode();
  ParseMode=Get_SysParse_Mode();
   
     
  if(THF_Spec==TF_MODE)    //单方向
  {
    if(ParseMode==PARSE_341)    //341绝对和加；331代数和
      WrPara=ENERG_SUM_MODE0;
    else                        //341代数和加；331绝对和
      WrPara=ENERG_SUM_MODE1;
  }
  else                   //双方向    
  {
    if(ParseMode==PARSE_341)    //341代数和加；331绝对和
      WrPara=ENERG_SUM_MODE1;
    else                        //341绝对和加；331代数和
      WrPara=ENERG_SUM_MODE0;
  }
  return WrPara;
}

/**********************************************************************************
函数功能：更新A/B/C/合相象限值
入口：无
出口：1/2/3/4：象限
注： P-----横坐标；Q-------纵坐标，逆时针方向：1/2/3/4。
**********************************************************************************/
INT8U	GetQuadrant(INT8U AcpowerDir,INT8U ReacPowerDir)
{	
  if(AcpowerDir==ReacPowerDir)      //1或者3象限
  {
    if(AcpowerDir==0)     //P+ Q+
      return QUADRANT1;
    else                  //P- Q-
      return QUADRANT3;    
  }
  else
  {
    if(AcpowerDir==0)     //P+ Q-
      return QUADRANT4;
    else                  //P- Q+
      return QUADRANT2;     
  }  
}
/**********************************************************************************
函数功能：根据象限，无功功率，有功功率，算出电压电流实际夹角
入口：无
出口：真实角度
**********************************************************************************/
INT32U	GetAngle(INT8U Quadrant,INT32U Reacower,INT32U ActiPower,INT8U Reg)
{	
  FP32S Dgree;
  
#ifdef MEASU_ANGLE_RD 
  INT8U Flag;
  INT32U Angle;
#endif

#ifdef MEASU_ANGLE_RD
    Flag=Measu_RdAndCompData_3Times(Reg,(INT8U *)&Angle);
    if(Flag==0)
    return 0;
    Dgree=(FP32S)Angle*0.001366;  //注意单位：UNIT_DEGREE
#else
    if(ActiPower<=5)  //防止除0溢出，0.005w,启动功率：0.33w
      Dgree=0L;
    else
    {
      Dgree=atan((FP32S)Reacower/ActiPower);
      Dgree=(Dgree*180*UNIT_DEGREE)/PAI;	//单位0.01度，角度不是从寄存器取出，是自己算出的
    }
#endif    
  switch(Quadrant)
  {
  case QUADRANT1:				//第1象限
    break;
  case QUADRANT2:				//第2象限
    Dgree=18000-Dgree;
    break;	
  case QUADRANT3:				//第3象限
    Dgree=18000+Dgree;
    break;	
  default:			        //第4象限
    Dgree=36000-Dgree;
    break;
  }
  return (INT32U)Dgree;
}
/**********************************************************************************
函数功能：根据校表字，校表内容，校表
入口：
       Code-----------校表指令
       Para3----------校表内容
       ParaLen-------校表数据字节长度
出口：1------------成功；0-----------------失败
**********************************************************************************/
INT8U CalibMeterProc_PUCK(INT16U Code,INT8U Para[],INT8U ParaLen)
{
   return 1;
}
/**********************************************************************************
函数功能：获取IC的参数校验和

出口：1---------读成功，读比较正确;0--------表示失败
**********************************************************************************/
INT8U Get_IC_ParaSum3(INT32U *Cs)
{
  INT32U Sum;
  INT8U Flag;
  
  Flag=Measu_RdAndCompData_3Times(REG_R_SUM,(INT8U *)&Sum);     //读IC校表参数的校验和
  if(Flag==0)
  {
    Debug_Print("Measure_Error----->Get IC Cs Failed!"); 
    return 0;
  }
  
  *Cs=Sum;  
  return 1;
}
/**********************************************************************************
函数功能：获取实际用的部分默认参数的校验和
**********************************************************************************/
INT8U Get_User_All_ParaSum3(INT32U *Cs)
{
  INT8U i,Flag,temp[3];
  INT32U Sum;
  
  Flag=1;
  for(Sum=0,i=1;i<IC_PARA_NUM;i++)
  {
    if(InitMeasuPara[i].ParaFlag==DEFA_TYPE)
      Sum+=InitMeasuPara[i].Para;
    if(InitMeasuPara[i].ParaFlag==SPEC_TYPE)
      Sum+=InitMeasuPara[i].FuncPtr();
    if(InitMeasuPara[i].ParaFlag==ADJU_TYPE)
    {
      Flag=Read_Storage_Data_PUCK(InitMeasuPara[i].Di,temp,3);
      ASSERT(1==Flag); 
      Sum+=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
    }
  }
  if(!Flag)
    return 0;
  
  *Cs=(Sum&0xffffff);
  return 1;  
}
/**********************************************************************************
函数功能：获取高频脉冲输出
入口：无
出口：高频脉冲常熟设置
**********************************************************************************/
INT32U Get_HighPulse_Const(void)
{  
  INT32U temp;
  INT8U U_spec,I_spec;
  
  U_spec=Get_SysVolt_Mode();
  I_spec=Get_SysCurr_Mode();
  
  temp=HighPulseConst[U_spec][I_spec];

  if((INT32U)temp<0x04)
  {
    Debug_Print("Measure_Error----->Hight Pulse Const < 0x04");
    temp=0x04;
  }
  
  if((INT32U)temp>0x0D00)
  {
    Debug_Print("Measure_Error----->Hight Pulse Const > 0x0d00");
    temp=0x0D00;
  }
  
  return  (((INT32U)temp)&0xFFFFFF);
}

/**********************************************************************************
函数功能：获取启动电流常数
入口：无
出口：
**********************************************************************************/
INT32U Get_Istart_Const(void)
{
  INT8U I_Spec;
  I_Spec=Get_SysCurr_Mode();
  return (Startup_Current[I_Spec]);  
}

/**********************************************************************************
函数功能：获取Iregion4
入口：无
出口：

INT32U Get_Iregion4(void)
{
  FP32S temp;
  
  temp=0.648*I_REGION_AREA*Get_In()*pow(2,23);
  
  return ((INT32U)temp&0XFFFFFF);  
}
**********************************************************************************/





/**********************************************************************************
函数功能：
出口：
注意：
**********************************************************************************/
void Cal_Reg_Write(INT8U Reg,INT8U Reg1ast,INT8U Num,INT32U CalData)
{
  INT8U i;
  
  if(Measu_WrAndCompData_3Times(Reg,CalData)==0)
    ASSERT_FAILED();
  
  for(i=0;i<Num;i++)  //对后续的补偿寄存器写
  {
    if(Measu_WrAndCompData_3Times(Reg1ast+i,CalData)==0)
      ASSERT_FAILED();
  }
}     
/**********************************************************************************
函数功能：将校表用的某一个参数写入计量芯片
出口：1---------写成功，;0--------写失败
注意：所有的校表参数都是3个字节！
**********************************************************************************/
void Load_Adj_OnePara_To_IC(PROTO_DI TempDI)
{
  INT8U Reg;
  //FD32S err;
  
  INT32U CalData;
  INT8U Rdflag;
  INT8U temp[3];
  
  if(Check_Meter_Factory_Status() EQ 0)//当前不是工厂状态则推出
    return ;
  
  if((TempDI<DI_POWER_A_0)||(TempDI>_SDI_ADJ_METER_CLR))
    return ;
  
  Rdflag=Read_Storage_Data_PUCK(TempDI,temp,3);
  if(!Rdflag)
    ASSERT_FAILED(); 
  CalData=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
  CalData=(INT32U)(CalData&0x00ffffff);
  Debug_Print("Measure_Info----->Cal_Meter DI=0x%lx,CalData=0x%lx",TempDI,CalData);
  
  EnMeasuCal();                             //校表数据写使能
  if((TempDI>=_SDI_ADJ_METER_A_POW)&&(TempDI<=_SDI_ADJ_METER_C_POW))     //功率增益参数
  {
    Reg=REG_W_PGAIN_A0+(INT8U)(TempDI-_SDI_ADJ_METER_A_POW);
    Cal_Reg_Write(Reg,Reg+3,1,CalData);
  }
  
  if((TempDI>=_SDI_ADJ_METER_A_PHASE)&&(TempDI<=_SDI_ADJ_METER_C_PHASE)) //相位增益参数
  {
    Reg=REG_W_PHSREG_A0+(INT8U)(TempDI-_SDI_ADJ_METER_A_PHASE)*5;
    Cal_Reg_Write(Reg,Reg+1,4,CalData);
  }
  
  if((TempDI>=_SDI_ADJ_METER_A_VOL)&&(TempDI<=_SDI_ADJ_METER_C_VOL))     //电压参数
  {
     Reg=REG_W_UGAIN_A+(INT8U)(TempDI-_SDI_ADJ_METER_A_VOL);
     Cal_Reg_Write(Reg,0,0,CalData);
   }


  if((TempDI>=_SDI_ADJ_METER_A_CUR)&&(TempDI<=_SDI_ADJ_METER_C_CUR))    //电流参数
  {
     Reg=REG_W_IGAIN_A+(INT8U)(TempDI-_SDI_ADJ_METER_A_CUR); 
     Cal_Reg_Write(Reg,0,0,CalData);
 }
  //更新校验和，用于比对
  DisMeasuCal(); 
  
}
/**********************************************************************************
函数功能：将使用的校表参数写入计量芯片
出口：1---------写成功，;0--------写失败
**********************************************************************************/
INT8U Load_Spec_ADJ_Para_To_IC(void)
{
  INT8U i,Rdflag,Wrflag,temp[3],Flag;
  INT32U para,CS;
  
  CS=0;
  EnMeasuCal();                             //校表数据写使能
  Debug_Print("Measure_Info----->Load Epprom Para To Measure IC........");
  for(Flag=1,i=1;i<IC_PARA_NUM;i++)
  {
    if(InitMeasuPara[i].ParaFlag==DEFA_TYPE)
    {
      CS+=InitMeasuPara[i].Para;
      continue;
    }
    if(InitMeasuPara[i].ParaFlag==SPEC_TYPE)
      para=InitMeasuPara[i].FuncPtr();
    if(InitMeasuPara[i].ParaFlag==ADJU_TYPE)
    {
      Rdflag=Read_Storage_Data_PUCK(InitMeasuPara[i].Di,temp,3);
      if(Rdflag EQ 0)
        ASSERT_FAILED(); 
      para=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
      Flag&=Rdflag;
    }
     Wrflag=Measu_WrAndCompData_3Times(i|0x80,para);
     if(Wrflag EQ 0)
        ASSERT_FAILED(); 
     Flag&=Wrflag;
     CS+=para;
  }
  
  DisMeasuCal();
  MeasuPara_CS.EppRom_Cs=CS&0xffffff;  //一次性写入
  SET_STRUCT_SUM(MeasuPara_CS);
  
  OS_TimeDly_Ms(200);  //for Cs Refresh
  Clear_All_Dog();
  OS_TimeDly_Ms(200);  //for Cs Refresh
  Clear_All_Dog();
  OS_TimeDly_Ms(150);  //for Cs Refresh
  Clear_All_Dog();
  
  if(Flag && Get_IC_ParaSum3(&CS))
  {
    if(CS==MeasuPara_CS.EppRom_Cs)
    {
      MeasuPara_CS.IC_Cs=CS;
      SET_STRUCT_SUM(MeasuPara_CS);  
      return 1;
    }
  }
  return 0;
}
/**********************************************************************************
函数功能：将MeasuIC校表数据寄存器的内容恢复到上电初始值；初始化与校表参数相关的参数
          EPROM中的校表参数同步改变
入口：无
出口：1---------恢复成功；0-----------恢复失败
**********************************************************************************/
INT8U Load_All_Para_To_IC(void)
{
  INT8U Flag;
  INT32U Cs;
  
  Flag=0;
  
  EnMeasuCal();
  ClrMeasuCal();     //将校表数据寄存器的内容恢复到上电初始值,CS不变的!
  DisMeasuCal();
  
  
  Flag=Measu_RdAndCompData_3Times(REG_R_SUM,(INT8U *)&Cs);     //读7022中校表参数的校验和
  if(Flag==0)
  {
    MeasuStatusMode.Retry=1;
    SET_STRUCT_SUM(MeasuStatusMode);
    return 0;
  }
  
  if((Get_SysParse_Mode()==PARSE_341) && (Cs!=CHKSUM_INIT_341))  //不是上电时候的CS
  {
    Debug_Print("Measure_Info----->Measure_IC Para Data(341) !=Default Value!");
    Measure_Error_Statics(Flag,1);
    Beep_For_Measu_Alarm_PUCK(MEASU_CS_ERR);
  }
  
  if((Get_SysParse_Mode()==PARSE_331) && (Cs!=CHKSUM_INIT_331)) //不是上电时候的CS
  {
    Debug_Print("Measure_Info----->Measure_IC Para Data(331) !=Default Value!");
    Measure_Error_Statics(Flag,1);
    Beep_For_Measu_Alarm_PUCK(MEASU_CS_ERR);
  }
  Flag=Load_Spec_ADJ_Para_To_IC();
  
  if(Flag==1)
  {
    Debug_Print("Measure_Info----->All Cal Para Write Succeed!");
    return 1;  
  }
  if(Flag==0)
  {
    MeasuStatusMode.Retry=1;
    SET_STRUCT_SUM(MeasuStatusMode);
    Debug_Print("Measure_Error----->Load Spec&&Adj Para Failed!");
    Beep_For_Measu_Alarm_PUCK(MEASU_CS_ERR);
    return 0;
  }
  return 0;
}

/**********************************************************************************
函数功能：
入口：无
出口：
**********************************************************************************/
void PrintParaComp(void)
{
  INT8U Flag,temp[3],i;
  INT32U paraic,para;
  
  for(i=1;i<IC_PARA_NUM;i++)
  {
    Flag=Measu_RdAndCompPara_3Times(i,temp);
    if(!Flag)
    ASSERT_FAILED();
    
    paraic=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
    
    if(InitMeasuPara[i].ParaFlag==DEFA_TYPE)
    {
      if(paraic!=InitMeasuPara[i].Para)
      Debug_Print("Measure_Error-----Reg=%d,Rd=0x%lx,Real=0x%lx",i,paraic,(InitMeasuPara[i].Para&0xffffff)); 
    }
    
    if(InitMeasuPara[i].ParaFlag==SPEC_TYPE)
    {
      if(paraic!=InitMeasuPara[i].FuncPtr())
      Debug_Print("Measure_Error-----Reg=%d,Rd=0x%lx,Real=0x%lx",i,paraic,InitMeasuPara[i].FuncPtr()); 
    }
    
    if(InitMeasuPara[i].ParaFlag==ADJU_TYPE)
    {
      Flag=Read_Storage_Data_PUCK(InitMeasuPara[i].Di,temp,3);
      if(!Flag)
        ASSERT_FAILED();
      para=(INT32U)(temp[2]*65536L+temp[1]*256L+temp[0]);
      if(paraic!=para)
      Debug_Print("Measure_Error-----Reg=%d,Rd=0x%lx,Real=%0xlx",i,paraic,para); 
    }
  }
}

