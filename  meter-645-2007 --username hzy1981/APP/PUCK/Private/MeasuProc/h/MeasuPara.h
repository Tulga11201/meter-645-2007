#ifndef EEPROM_VAR
#define EEPROM_VAR


#ifndef EEPROM_PUCK
#define EEPROM_PUCK_EXT  extern volatile
#else
#define EEPROM_PUCK_EXT volatile
#endif



#define  CS_IC_EPPROM_GEIFAILED   0   //-------内卡CS和IC的CS均获取失败
#define  CS_IC_GET_FAILED         1   //---------计量IC参数获取失败，CS无效；
#define  CS_EPPROM_GET_FAILED     2   //-----内卡参数获取失败，CS无效；
#define  CS_IC_EPPROM_NO_EQUAL    4   //------CS均获取成功，但是2者不相等,以内卡为准！
#define  CS_IC_EPPROM_EQUAL       5   //-------内卡CS和IC的CS均获取成功,CS也想等




#define CAL_MEASU_OVER   0x55 //MeasuIC校表完成标志

#define PARA_SRAM  0
#define PARA_FLASH 1



//#define      DI_MEASU_PARA  _SDI_ADJ_METER_PARA

//扩充的5个模式字
#define      DI_MODE1 SDI_MODEWORD_1        //TF/TH--bit6
#define      DI_MODE2 SDI_MODEWORD_2        //TF/TH--bit6
#define      DI_MODE3 SDI_MODEWORD_3        //TF/TH--bit6
#define      DI_MODE4 SDI_MODEWORD_4        //TF/TH--bit6
#define      DI_MODE5 SDI_MODEWORD_5        //TF/TH--bit6


#define      DI_TIME                  0x04000102       //时分秒

#define      DI_STEP_SCHEME           0x0E01000B   //阶梯电价方案:返回1个字节，1表示第一套，2表示第二套

#define      DI_DATE_WEEK             0x04000101          //日期及星期(其中0代表星期天)

#define      DI_AC_POWER_SUM    0x02030000   //有功功率－合相
#define      DI_AC_POWER_A      0x02030100   //有功功率－A
#define      DI_AC_POWER_B      0x02030200   //有功功率－B
#define      DI_AC_POWER_C      0x02030300   //有功功率－C


#define      DI_REAC_POWER_SUM    0x02040000   //有功功率－合相
#define      DI_REAC_POWER_A      0x02040100   //有功功率－A
#define      DI_REAC_POWER_B      0x02040200   //有功功率－B
#define      DI_REAC_POWER_C      0x02040300   //有功功率－C

/*
#define      DI_LOSS_VOLT_DATA     0x0EA00000   //总失压期间累计数据：
#define      DI_LOSS_VOLT_DATA_A   0x0EA00001   //总失压期间累计数据：-----A
#define      DI_LOSS_VOLT_DATA_B   0x0EA00002   //总失压期间累计数据：-----B
#define      DI_LOSS_VOLT_DATA_C   0x0EA00003   //总失压期间累计数据：-----C

#define      DI_LOSS_VOLT_START   0x0EA10000   //最近一次失压起始日期时间
#define      DI_LOSS_VOLT_END     0x0EA10001   //最近一次失压结束日期
*/
#define      DI_P_U_I_SPEC   _SDI_ADJ_METER_PUL_VOL_CUR_SPEC   //脉冲常数规格，电压规格，电流规格：3字节

#define      DI_CAL_STATUS   _SDI_ADJ_METER_PARA_STATUS  //0------待校表；1------校表中；2------校表完成：

#define      DI_POWER_A_0   _SDI_ADJ_METER_A_POW   //功率0增益参数:3字节
#define      DI_POWER_B_0   (DI_POWER_A_0+1)   //功率0增益参数:3字节
#define      DI_POWER_C_0   (DI_POWER_A_0+2)   //功率0增益参数:3字节

#define      DI_ANGLE_A_0   _SDI_ADJ_METER_A_PHASE   //相位0增益参数:3字节
#define      DI_ANGLE_B_0   (DI_ANGLE_A_0+1)   //相位0增益参数:3字节
#define      DI_ANGLE_C_0   (DI_ANGLE_A_0+2)   //相位0增益参数:3字节

#define      DI_U_GAIN_A    _SDI_ADJ_METER_A_VOL   //电压增益校正:3字节
#define      DI_U_GAIN_B    (DI_U_GAIN_A+1)   //电压增益校正:3字节
#define      DI_U_GAIN_C    (DI_U_GAIN_A+2)   //电压增益校正:3字节

#define      DI_I_GAIN_A    _SDI_ADJ_METER_A_CUR   //电流增益校正:3字节
#define      DI_I_GAIN_B    (DI_I_GAIN_A+1)   //电流增益校正:3字节
#define      DI_I_GAIN_C    (DI_I_GAIN_A+2)   //电流增益校正:3字节

#define      DI_CLR_PARA    _SDI_ADJ_METER_CLR  //1------校表参数清零(实际是将CEE0~CEED的值变为0，不是恢复默认值)；2------内卡参数清零；3------内卡数据清零；其他：预留。


typedef struct
{  
  INT32U IC_Cs;
  INT32U EppRom_Cs;
  INT8U CS[CS_BYTES]; 
}CS_STRUCT;  //临时需要的变量


EEPROM_PUCK_EXT CS_STRUCT  MeasuPara_CS; 

//以下组成系统的规格(建议：软件版本号码中最好含有以下3项，清晰产品规格)
#define SYS_PULSE_TYPE  PULSE_TYPE2
#define SYS_VOLT_SPEC   VOLT_3220
#define SYS_CURR_SPEC   CURR_1x5_6
#define SYS_THF_SPEC    TH_MODE         //双方向


#if (SYS_VOLT_SPEC==VOLT_3100)||(SYS_VOLT_SPEC==VOLT_3577)
   #define SYS_PARSE_SPEC  PARSE_331
#else
   #define SYS_PARSE_SPEC  PARSE_341
#endif


//#define SYS_MEASU_MARCO   //宏开启，参数取自以上5个宏；关闭，参数取自变量


//上电/复位后校表数据校验寄存器内容
#define CHKSUM_INIT_341    0x043d03
#define CHKSUM_INIT_331    0x16bd03

//上电/复位后校表数据失压阈值寄存器内容
#define LOSSV_INIT_341     0x1068000
#define LOSSV_INIT_331     0x1190000

#if SYS_PARSE_SPEC==PARSE_331
  #define LOSSV_INIT_PARA LOSSV_INIT_331
#else
 #define LOSSV_INIT_PARA LOSSV_INIT_341
#endif


#define Get_SysTHF_Mode() TH_MODE    //双方向


EEPROM_PUCK_EXT  INT8U Measu_ParaWrFlag;

INT8U Get_Buf_MulitByte_Sum(INT8U *Src,INT16U SrcLen,INT8U ByteGroup,INT8U *Dst,INT8U DstLen);
INT8U Chk_IC_User_ParaSum(void);
INT32U Get_MeasuParaBuf_Sum3(void);
INT8U Check_MeasuParaBuf_Sum3(void);
INT8U Load_All_Para_To_IC(void);
INT32U Get_Max_Num(INT32U X,INT32U Y,INT32U Z);

INT8U Get_SysParse_Mode(void);
INT8U Get_SysPulse_Mode(void);
INT8U Get_SysVolt_Mode(void);
INT32U Get_FailVolt_Para(void);
INT8U Get_SysCurr_Mode(void);
INT32U	GetAngle(INT8U Quadrant,INT32U Reacower,INT32U ActiPower,INT8U Reg);
INT8U	GetQuadrant(INT8U AcpowerDir,INT8U ReacPowerDir);
INT8U MeasuIC_HardRst(void);

FP32S Sqrt_Cal(float x);
INT8U InitMeasuAfterPwrOn(void);
void Clr_Cal_Requst(void);
INT8U ChkMeasuICWorkStatus(void);
void Refresh_MeasuParaBuf(void);
INT8U Read_Storage_Data_PUCK(INT32U DI,void *pDst,INT16U DstLen);
INT8U Get_IC_ParaSum3(INT32U *Cs);
INT8U Get_User_All_ParaSum3(INT32U *Cs);
void PrintParaComp(void);
#endif
