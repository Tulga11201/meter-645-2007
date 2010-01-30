#define AUTHORITY_C
#include "Includes.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "H18"
#endif

CONST S_PSW_Map PSW_Map[]=
{
	{PSW_FAC_PARA, PSW_FACTORY}, //工厂参数
	{PSW_RD_ONLY,  PSW_NULL},//只读参数，没有写权限
	{PSW_SET_PSW0, PSW_0},  //0级密码权限
	{PSW_SET_PSW1, PSW_1},  //1级密码权限
	{PSW_SET_PSW2, PSW_2},  //2级密码权限
	{PSW_SET_PSW3, PSW_3},  //3级密码权限
	{PSW_SET_PSW4, PSW_4},  //4级密码权限
	{PSW_SET_PSW5, PSW_5},  //5级密码权限
	{PSW_SET_PSW6, PSW_6},  //6级密码权限
	{PSW_SET_PSW7, PSW_7},  //7级密码权限
	{PSW_SET_PSW8, PSW_8},  //8级密码权限
	{PSW_SET_PSW9, PSW_9},  //9级密码权限
	
	//{PSW_ADJ_TIME, PSW_0},   //广播校时
	{PSW_SET_DATE, PSW_4},   //设置日期
	{PSW_SET_TIME, PSW_4},  //设置时间
	{PSW_CLR_ALL,  PSW_2},   //数据总清,就是电表清0
	//{PSW_CLR_DATA, PSW_0},  //清需量、过程、电压合格率
	{PSW_SET_ENSTART, PSW_0},   //设置底度数
	{PSW_SET_PARA,    PSW_4},  //设置普通参数(其他参数)
};

//网络表模块使用的固定密码
CONST INT8U Net_Meter_Psw[] = {0x04, 0x11, 0x22, 0x33};

//返回某数据标志对应的写权限密码等级，PSW_NULL表示不具备写权限
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
//检查表计内部的跳线是否跳上了
INT8U Check_Meter_Factory_Status()
{
  if(Get_Meter_Hard_Mode() != MODE_FAC)
  {
    return 0;
  }  //非工厂状态
  else
  {
    return 1;
  }  //工厂状态  

}

//检查是否能否输出调试信息
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

//检查表计是否处于编程状态，是的返回1，否则返回0
INT8U Check_Meter_Prog_Status()
{
  //return 1;//test
  return Check_Prog_Status();
}

//判断当前处于工厂或者编程状态
//只要是出于工厂或者编程两种状态之一，就返回1，否则返回0
INT8U Check_Meter_Prog_Fac_Status()
{
   if(Check_Meter_Prog_Status() || Check_Meter_Factory_Status())
     return 1;
   else
     return 0;
}

//检查设置通信地址的案件是否按下，按下返回1，否则返回0
INT8U Check_Set_ADDR_Key()
{
  return Check_MeterAddr_Status();
}

//检查清除数据的权限,要处于工厂状态或者编程状态，权限标志
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

//设置权限标志
void Set_Authority_Flag()
{
  INT8U Re;
  
  TRACE();
  
  //设置用户的密码级别
  Re = CHECK_STRUCT_SUM(User_Authority_Flag); 
  ASSERT(1 EQ Re); 
  User_Authority_Flag.Flag = AUTHORITY_FLAG; //权限标志，增加安全性
  SET_STRUCT_SUM(User_Authority_Flag); 
}

void Clear_Authority_Flag()
{
  User_Authority_Flag.Flag = 0; //权限标志，增加安全性
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

//检查网络表数据的用户权限
INT8U Get_Net_Meter_User_Authority(INT8U Ctrl_Code, INT8U *pSrc, INT8U SrcLen, INT8U *pSpec_Flag)
{
  PROTO_DI PDI;
  
  Check_Module_Set_Meter_Status();
  
  *pSpec_Flag = 0; //需要特殊处理的标志
  
  if(Ctrl_Code EQ C_SET_DATA)//写数据需要特殊处理
  {
    mem_cpy(&PDI, pSrc, 4, &PDI, sizeof(PDI));//复制PDI    
    if(PDI EQ 0x0EA20000 || PDI EQ 0x0EA20001) //写模块通信状态或者打开写使能
    {
      *pSpec_Flag = 1; //已经特殊处理了的
      
      if(memcmp(pSrc + 4, Net_Meter_Psw, 4) EQ 0)//固定密码
        return PSW_4;//  *pSpec_Flag = 1; //已经特殊处理了的 
    }
    //else if(Module_Set_Meter_Status.Set_En_Mins > 0) //最多具备4级权限
      //return PSW_4;
  } 
  
  return PSW_10;
}

//获取当前的用户权限,也就是密码,如果发送的数据不需要密码，则直接返回权限PSW_0
INT8U Get_User_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen)
{
  INT8U Posi;//密码在数据缓冲中的起始位置
  INT8U Level;//当前密码级别
  PROTO_DI PDI;
  
#if NET_METER != NONET_METER //用于网络表的权限控制
  INT8U Spec_Flag, PSW_Flag;
#endif  

  //暂时屏蔽 test
  if(Check_Meter_Factory_Status())//表内跳线跳上了，具备超级权限
    return PSW_FACTORY;
  
////////////////////////////////////
#if NET_METER != NONET_METER //用于网络表的权限控制
  if(Ch EQ CHANEL_MOUDEL) 
  {
    PSW_Flag = Get_Net_Meter_User_Authority(Ctrl_Code, pSrc, SrcLen, &Spec_Flag);
    if(Spec_Flag > 0) //特殊处理了的
      return PSW_Flag;
  }
#endif                           
///////////////////////////////////   
  
//以下都没有条上表内跳线  
  if(Ctrl_Code EQ C_READ_DATA || Ctrl_Code EQ C_READ_FOLLOW_DATA || Ctrl_Code EQ C_READ_ADDR)
  {
    mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));//读密码，返回无权限
    if((PDI & 0xFFFFFF00) EQ 0x04000C00)
      return PSW_NULL;
    
    return PSW_0;//不需要密码的情况下，认为具备了0级密码
  }
  else if(Ctrl_Code EQ C_SET_DATA)//写数据
  {
    if(Check_Meter_Prog_Status() EQ 0)//没有处于编程状态，不具备任何写权限
    {
      //*pErr=PROTOCOL_AUTH_ERR;
      return PSW_NULL;
    }
    /*
    //设置初始电量，如果模式字不允许则不能设置
    mem_cpy(&PDI, pSrc, 4, &PDI, sizeof(PDI));
    if((PDI & 0xFFFFFF00) EQ 0x0E000300 && SET_ENERGY_EN EQ 0)
    {
      return PSW_NULL;
    }*/
    
    Level=pSrc[4];//密码级别
    Posi=5;//密码开始位置
  }
  else if(Ctrl_Code EQ C_ADJUST_TIME)//广播校时
  {
      return PSW_0;//不需要密码的情况下，认为具备了0级密码
  }
  else if(Ctrl_Code EQ C_SET_ADDR)//设置表地址不需要密码权限，只需要按下某个按键
  {
    if(Check_Meter_Prog_Status() EQ 0)//按键没有按下，返回权限错
      return PSW_NULL;
    else 
      return PSW_0;//不需要密码的情况下，认为具备了0级密码
  }
  else if(Ctrl_Code EQ C_FREEZE_DATA)
  {
    return PSW_0; 
  }
  else if(Ctrl_Code EQ C_SET_COM_BAUD)//设置通信波特率
  {
    return PSW_0;//不需要密码
  }
  else if(Ctrl_Code EQ C_SET_PSW)//修改密码
  { 
    if(Check_Meter_Prog_Status() EQ 0)//没有处于编程状态，不具备任何写权限
      return PSW_NULL;
    
    Level=pSrc[4];//数据域第4字节就是密码级别
    Posi=5;    
  }
  else if(Ctrl_Code EQ C_CLR_ALL ||\
          Ctrl_Code EQ C_CLR_DEMAND ||\
          Ctrl_Code EQ C_CLR_EVENT)
  {
    if(Check_Meter_Prog_Status() EQ 0)//没有处于编程状态，不具备任何写权限
      return PSW_NULL;
    
    if(Ctrl_Code EQ C_CLR_ALL && METER_CLR_EN EQ 0) //禁止出厂清0
      return PSW_NULL;
    
    Level=pSrc[0];
    Posi=1;         
  }
  else if(Ctrl_Code EQ C_CTRL) //控制
  {
    Level=pSrc[0];
    Posi=1;    
  }
  else if(Ctrl_Code EQ C_PORT) //多功能端子设置
  {
    return PSW_0; //不需要密码 
  }
  else if(Ctrl_Code EQ C_REMOTE_AUTH) //远程身份认证
  {
    return PSW_0; //不需要密码 
  }
  else
  {
   return PSW_NULL;
  }
  //密码级别在0-9之间才是正确的
  if(Level>9)
  {
    //*pErr=PROTOCOL_PSW_ERR;//密码错误
    return PSW_10;
  }
  
  //比较密码是否相同
  if(memcmp(pSrc+Posi,(void *)Cur_PSW.PSW[Level],3)!=0)
  {
    //*pErr=PROTOCOL_PSW_ERR;//密码错误
    return PSW_10;
  }
  return Level + 1; //PSW_0 -> 1, PSW_9 ->10
}

//清除密码错误信息
void Clear_PSW_Err_Info()
{
  DIS_PD_INT;
  
  mem_set((void *)&PSW_Err_Info,0,sizeof(PSW_Err_Info),(void *)&PSW_Err_Info,sizeof(PSW_Err_Info));
  INIT_STRUCT_VAR(PSW_Err_Info);
  SET_STRUCT_SUM(PSW_Err_Info);
  SET_STRUCT_SUM(Event_Data);
  
  EN_PD_INT;
}

//检查修改某个数据需要的权限
INT8U Get_P_Data_Info_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen)//INT16U DI)
{
  INT8U PSW_Flag;
  PROTO_DI PDI;

  TRACE();

  //先获得这个数据的密码标记
  if(Ctrl_Code EQ C_READ_DATA || Ctrl_Code EQ C_READ_FOLLOW_DATA || Ctrl_Code EQ C_READ_ADDR)
  {
    return PSW_10;//读取数据和后续数据不需要密码，因此默认返回密码10,最低等级
  }
  else if(Ctrl_Code EQ C_SET_DATA)
  {
    PDI = 0;
    mem_cpy(&PDI, pSrc, sizeof(PDI), &PDI, sizeof(PDI));//DI=*(INT16U *)pSrc;
    PSW_Flag = Get_P_Data_PSW_Level(PDI);

    return PSW_Flag;
  }
  else if(Ctrl_Code EQ C_ADJUST_TIME)//广播校时
  {
    return PSW_10;//因为不需要密码，所以给出一个最低级密码(在判断用户密码时会给一个较高级密码) 
  }
  else if(Ctrl_Code EQ C_SET_ADDR)
  {
    return PSW_10; //设表地址，因为不需要密码，所以给出一个最低级密码(在判断用户密码时会给一个较高级密码) 
  }
  else if(Ctrl_Code EQ C_SET_COM_BAUD)
  {
    return PSW_10; //设波特率，因为不需要密码，所以给出一个最低级密码   
  }
  else if(Ctrl_Code EQ C_SET_PSW)
  {
    return *(pSrc + 8) + 1;//修改该数据需要的密码级别，也就是被修改的密码的级别
  }
  else if(Ctrl_Code EQ C_CLR_ALL)//总清
  {
    return PSW_2;
  }
  else if(Ctrl_Code EQ C_CLR_EVENT)//清事件
  {
    return PSW_2;
  }
  else if(Ctrl_Code EQ C_CLR_DEMAND)//最大需量清零
  {
    return PSW_4;
  }
  else if(Ctrl_Code EQ C_CTRL) //远程控制，需要2级密码
  {
    return PSW_2; 
  }
  else if(Ctrl_Code EQ C_PORT) //多功能端子
  {
    return PSW_10; 
  }
  else if(Ctrl_Code EQ C_REMOTE_AUTH)
  {
    return PSW_10; 
  }
  return PSW_0;//如果0-9级密码权限都没有设置该项，则默认为0级密码可设
}

//密码锁定计时处理
void PSW_Timer_Proc()
{
  INT8U Re;
  INT8U Modi_Flag;
  static S_Int8U Min_Bak={CHK_BYTE,0xFF,CHK_BYTE};
  static S_Int32U Sec_Bak={CHK_BYTE,0x0,CHK_BYTE};
  
  if(Sec_Bak.Var EQ Sec_Timer_Pub)
    return;
  
  Sec_Bak.Var = Sec_Timer_Pub;
  
  if(Check_Meter_Factory_Status() && PSW_Err_Info.Lock_Mins > 0)//在工厂状态清除密码锁
  {
    Clear_PSW_Err_Info(); //此时应该是PSW_Err_Info.Set_En_Mins = 0
    Clr_Event_Instant(ID_EVENT_METER_LOCK);//解锁事件，消除液晶上的锁标志
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
    
    if(PSW_Err_Info.Lock_Mins>0)//锁定时间递减
    {
      Set_Event_Instant(ID_EVENT_METER_LOCK);  //密码锁事件发生
      PSW_Err_Info.Lock_Mins--;
      if(PSW_Err_Info.Lock_Mins EQ 0)
      {
        PSW_Err_Info.Err_Counts=0;//锁定次数清0
        Clr_Event_Instant(ID_EVENT_METER_LOCK);
      }
      Modi_Flag = 1;
    }
/*    
    if(PSW_Err_Info.Clr_Err_Counts_Mins>0)//1440分钟后错误次数自动清0
    {
      PSW_Err_Info.Clr_Err_Counts_Mins--;
      if(PSW_Err_Info.Clr_Err_Counts_Mins EQ 0)
        PSW_Err_Info.Err_Counts=0;
      
      Modi_Flag = 1;
    }
*/    
    if(PSW_Err_Info.Set_En_Mins>0)//开放设置功能时间
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
//--------------模块设参数使能------------
    Check_Module_Set_Meter_Status();   
    
    if(Module_Set_Meter_Status.Set_En_Mins > 0)
    {
      Module_Set_Meter_Status.Set_En_Mins --;
      SET_STRUCT_SUM(Module_Set_Meter_Status);
    }
  }
} 

//检查密码是否锁死
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

//对密码锁死等的处理
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
      PSW_Err_Info.Set_En_Mins = 0; //写使能时间
      PSW_Err_Info.Lock_Mins = AUTHU_ERR_LOCK_MINS; //锁定AUTHU_ERR_LOCK_MINS分钟
      Set_Event_Instant(ID_EVENT_METER_LOCK);   //密码锁事件发生
    }
    
    SET_STRUCT_SUM(PSW_Err_Info);
    SET_STRUCT_SUM(Event_Data);
    
    EN_PD_INT;
  }

  Debug_Print("User do not have the authority!");
}

//密码设置使能处理
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

//检查当前用户权限是否通过
INT8U Check_User_Authurity(INT8U User_PSW, INT8U Data_PSW)
{
  INT8U Re;
  
  if(Data_PSW EQ PSW_10) //读数据,不需要权限检查
    return 1;
  
  if(Data_PSW EQ PSW_FACTORY) //需要工厂状态的参数，必须在工厂状态，该判断不可少
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
  
  //写数据
  if(PSW_Err_Info.Set_En_Mins > 0) //允许写!
    return 1;  
  else if(PSW_Err_Info.Lock_Mins > 0)//禁止写！
    return 0;

  //没有写使能，也没有禁止写
  if(User_PSW > Data_PSW)
  {
    PSW_Lock_Proc(); //进行锁处理
    return 0;
  }
  else
  {
    PSW_Set_En_Proc(); //写使能处理 
    return 1;
  }
  
}

//检查数据属于哪个类别,返回1、2、3分别表示1、2、3类数据
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

//检查是否是时区表或者是时段表数据
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
