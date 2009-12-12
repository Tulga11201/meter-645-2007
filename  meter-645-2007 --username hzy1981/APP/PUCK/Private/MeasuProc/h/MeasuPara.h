#ifndef EEPROM_VAR
#define EEPROM_VAR


#ifndef EEPROM_PUCK
#define EEPROM_PUCK_EXT  extern volatile
#else
#define EEPROM_PUCK_EXT volatile
#endif



#define  CS_IC_EPPROM_GEIFAILED   0   //-------�ڿ�CS��IC��CS����ȡʧ��
#define  CS_IC_GET_FAILED         1   //---------����IC������ȡʧ�ܣ�CS��Ч��
#define  CS_EPPROM_GET_FAILED     2   //-----�ڿ�������ȡʧ�ܣ�CS��Ч��
#define  CS_IC_EPPROM_NO_EQUAL    4   //------CS����ȡ�ɹ�������2�߲����,���ڿ�Ϊ׼��
#define  CS_IC_EPPROM_EQUAL       5   //-------�ڿ�CS��IC��CS����ȡ�ɹ�,CSҲ���




#define CAL_MEASU_OVER   0x55 //MeasuICУ����ɱ�־

#define PARA_SRAM  0
#define PARA_FLASH 1



//#define      DI_MEASU_PARA  _SDI_ADJ_METER_PARA

//�����5��ģʽ��
#define      DI_MODE1 SDI_MODEWORD_1        //TF/TH--bit6
#define      DI_MODE2 SDI_MODEWORD_2        //TF/TH--bit6
#define      DI_MODE3 SDI_MODEWORD_3        //TF/TH--bit6
#define      DI_MODE4 SDI_MODEWORD_4        //TF/TH--bit6
#define      DI_MODE5 SDI_MODEWORD_5        //TF/TH--bit6


#define      DI_TIME                  0x04000102       //ʱ����

#define      DI_STEP_SCHEME           0x0E01000B   //���ݵ�۷���:����1���ֽڣ�1��ʾ��һ�ף�2��ʾ�ڶ���

#define      DI_DATE_WEEK             0x04000101          //���ڼ�����(����0����������)

#define      DI_AC_POWER_SUM    0x02030000   //�й����ʣ�����
#define      DI_AC_POWER_A      0x02030100   //�й����ʣ�A
#define      DI_AC_POWER_B      0x02030200   //�й����ʣ�B
#define      DI_AC_POWER_C      0x02030300   //�й����ʣ�C


#define      DI_REAC_POWER_SUM    0x02040000   //�й����ʣ�����
#define      DI_REAC_POWER_A      0x02040100   //�й����ʣ�A
#define      DI_REAC_POWER_B      0x02040200   //�й����ʣ�B
#define      DI_REAC_POWER_C      0x02040300   //�й����ʣ�C

/*
#define      DI_LOSS_VOLT_DATA     0x0EA00000   //��ʧѹ�ڼ��ۼ����ݣ�
#define      DI_LOSS_VOLT_DATA_A   0x0EA00001   //��ʧѹ�ڼ��ۼ����ݣ�-----A
#define      DI_LOSS_VOLT_DATA_B   0x0EA00002   //��ʧѹ�ڼ��ۼ����ݣ�-----B
#define      DI_LOSS_VOLT_DATA_C   0x0EA00003   //��ʧѹ�ڼ��ۼ����ݣ�-----C

#define      DI_LOSS_VOLT_START   0x0EA10000   //���һ��ʧѹ��ʼ����ʱ��
#define      DI_LOSS_VOLT_END     0x0EA10001   //���һ��ʧѹ��������
*/
#define      DI_P_U_I_SPEC   _SDI_ADJ_METER_PUL_VOL_CUR_SPEC   //���峣����񣬵�ѹ��񣬵������3�ֽ�

#define      DI_CAL_STATUS   _SDI_ADJ_METER_PARA_STATUS  //0------��У��1------У���У�2------У����ɣ�

#define      DI_POWER_A_0   _SDI_ADJ_METER_A_POW   //����0�������:3�ֽ�
#define      DI_POWER_B_0   (DI_POWER_A_0+1)   //����0�������:3�ֽ�
#define      DI_POWER_C_0   (DI_POWER_A_0+2)   //����0�������:3�ֽ�

#define      DI_ANGLE_A_0   _SDI_ADJ_METER_A_PHASE   //��λ0�������:3�ֽ�
#define      DI_ANGLE_B_0   (DI_ANGLE_A_0+1)   //��λ0�������:3�ֽ�
#define      DI_ANGLE_C_0   (DI_ANGLE_A_0+2)   //��λ0�������:3�ֽ�

#define      DI_U_GAIN_A    _SDI_ADJ_METER_A_VOL   //��ѹ����У��:3�ֽ�
#define      DI_U_GAIN_B    (DI_U_GAIN_A+1)   //��ѹ����У��:3�ֽ�
#define      DI_U_GAIN_C    (DI_U_GAIN_A+2)   //��ѹ����У��:3�ֽ�

#define      DI_I_GAIN_A    _SDI_ADJ_METER_A_CUR   //��������У��:3�ֽ�
#define      DI_I_GAIN_B    (DI_I_GAIN_A+1)   //��������У��:3�ֽ�
#define      DI_I_GAIN_C    (DI_I_GAIN_A+2)   //��������У��:3�ֽ�

#define      DI_CLR_PARA    _SDI_ADJ_METER_CLR  //1------У���������(ʵ���ǽ�CEE0~CEED��ֵ��Ϊ0�����ǻָ�Ĭ��ֵ)��2------�ڿ��������㣻3------�ڿ��������㣻������Ԥ����


typedef struct
{  
  INT32U IC_Cs;
  INT32U EppRom_Cs;
  INT8U CS[CS_BYTES]; 
}CS_STRUCT;  //��ʱ��Ҫ�ı���


EEPROM_PUCK_EXT CS_STRUCT  MeasuPara_CS; 

//�������ϵͳ�Ĺ��(���飺����汾��������ú�������3�������Ʒ���)
#define SYS_PULSE_TYPE  PULSE_TYPE2
#define SYS_VOLT_SPEC   VOLT_3220
#define SYS_CURR_SPEC   CURR_1x5_6
#define SYS_THF_SPEC    TH_MODE         //˫����


#if (SYS_VOLT_SPEC==VOLT_3100)||(SYS_VOLT_SPEC==VOLT_3577)
   #define SYS_PARSE_SPEC  PARSE_331
#else
   #define SYS_PARSE_SPEC  PARSE_341
#endif


//#define SYS_MEASU_MARCO   //�꿪��������ȡ������5���ꣻ�رգ�����ȡ�Ա���


//�ϵ�/��λ��У������У��Ĵ�������
#define CHKSUM_INIT_341    0x043d03
#define CHKSUM_INIT_331    0x16bd03

//�ϵ�/��λ��У������ʧѹ��ֵ�Ĵ�������
#define LOSSV_INIT_341     0x1068000
#define LOSSV_INIT_331     0x1190000

#if SYS_PARSE_SPEC==PARSE_331
  #define LOSSV_INIT_PARA LOSSV_INIT_331
#else
 #define LOSSV_INIT_PARA LOSSV_INIT_341
#endif


#define Get_SysTHF_Mode() TH_MODE    //˫����


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
