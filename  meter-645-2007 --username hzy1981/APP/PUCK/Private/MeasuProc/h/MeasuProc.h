#ifndef Proc_h
#define Proc_h


//#undef MeasuProc_PUCK_EXT
#ifndef MeasuProc_PUCK
#define MeasuProc_PUCK_EXT  extern
#else
#define MeasuProc_PUCK_EXT
#endif



#define MEASU_LIMITED_EN                //�꿪�������ж�����Խ����
//#define Measu_VOLTANGLE_EN          //�꿪������ȡ����2��ĵ�ѹ�н�
#define LITTLE_CURR_ADJ          //�꿪����С��������������
#define POWER_FACTOR_ADJ          //�꿪�����������ز���������

#define MAX_RST_MEASU_IC_TIMES 12

typedef struct
{ 
  INT16U MeasErrCountr;
  INT16U LimitErrCountr;
  INT16U RstMeasCountr;
  INT16U RstLimiCountr;
  INT8U CS[CS_BYTES]; 
}RST_MEASUIC_STRUC;
MeasuProc_PUCK_EXT volatile RST_MEASUIC_STRUC RstCtrlStatus;  


typedef struct
{
  INT8U Head;
  INT8U AcEgErr[4];
  INT8U ReAcEgErr[4];
  INT8U PQSEgErr[4];
  INT8U Tail;
}ENERG_ERR;

MeasuProc_PUCK_EXT volatile ENERG_ERR Energ_Err_Clr;  

typedef struct
{  
  INT8U A;
  INT8U B;
  INT8U C;
  INT8U CS[CS_BYTES]; 
}MEASU_RAM;  //��ʱ��Ҫ�ı���


/*
MeasuProc_PUCK_EXT volatile MEASU_RAM  PDeal_CurrFlag;          //����С������(1%In)����15mA����,��Ҫ�Թ�������У��
MeasuProc_PUCK_EXT volatile MEASU_RAM  Setup_CurrFlag;          //λ��С���������־:��[6,13.5]mA�����־
MeasuProc_PUCK_EXT volatile MEASU_RAM  Change_CurrFlag;         //��������˳�С���������־:��[6,13.5]mA
*/

MeasuProc_PUCK_EXT volatile MEASU_RAM  Curr_Under_Istart;     //λ��С������(0,0.1%In)
MeasuProc_PUCK_EXT volatile MEASU_RAM  Curr_1_Per_100;       //λ��С������[0,1%In)����15mA����,��Ҫ�Թ�������У��
MeasuProc_PUCK_EXT volatile MEASU_RAM  Curr_1P100_Bad;       //[0.1%In,6)����15mA����,��Ҫ�Թ�������У��
MeasuProc_PUCK_EXT volatile MEASU_RAM  Curr_In_6_13x5;       //λ��С���������־:��[6,13.5]mA�����־
MeasuProc_PUCK_EXT volatile MEASU_RAM  Curr_6_13x5_Slipe;    //��������˳�С���������־:��[6,13.5]mA


MeasuProc_PUCK_EXT volatile MEASU_RAM  SpecChange_CurrFlag;     //С��������µ��������־�仯���Ƚ��鷳

/*******************************��������ʱ������*************************************/
typedef struct
{
   MEASU_DATA AcEnerg;            //�����й����ܣ�A/B/C/SUM:��λ:0.01wh
   //MEASU_DATA AcEnReg;            //��ǰ�������й����ܼĴ���ֵ
   
   MEASU_DATA ReacEnerg;          //���� �޹����ܣ�A/B/C/SUM;
   //MEASU_DATA ReacEnReg;          //��ǰ�������޹����ܼĴ���ֵ
   
   MEASU_DATA Last_AcEnerg;       //�ϴ��й����ܣ�A/B/C/SUM;
   MEASU_DATA Last_ReacEnerg;     //�ϴ��޹����ܣ�A/B/C/SUM��
   MEASU_DATA Change_AcEnerg;     //��ǰ�й�����������A/B/C/SUM;
   MEASU_DATA Change_ReacEnerg;   //��ǰ�޹�����������A/B/C/SUM��
   
#if APP_ENERG_EN >0 //��PQS���ڵ��ܱ�
   MEASU_DATA AppEnerg;          //�������ڵ��ܣ�A/B/C/SUM;
   MEASU_DATA Last_AppEnerg;     //��ǰ���ڵ���������A/B/C/SUM;
   MEASU_DATA Change_AppEnerg;   //��ǰ���ڵ���������A/B/C/SUM��
#endif  
   
   MEASU_DATA Last_Curr;         //�ϴε���:XXXXXXXX UNIT:0.0001A	
   INT8U CS[CS_BYTES];
}MEASU_TEMP;
MeasuProc_PUCK_EXT volatile MEASU_TEMP  Pri_TempMeasuVar;

#ifdef MEASURE_VAR_BAK_EN
  MeasuProc_PUCK_EXT volatile MEASU_TEMP  Pri_TempMeasuVarBak1;
  MeasuProc_PUCK_EXT volatile MEASU_TEMP  Pri_TempMeasuVarBak2;
#endif


#ifdef Measu_VOLTANGLE_EN
typedef struct
{
  INT32U AB;      //AB��ѹ�н�
  INT32U AC;      //AC��ѹ�н�
  INT32U BC;      //BC��ѹ�н�
}Measu_ANGLE;   //MeasuIC˲ʱ����������:�н�
#endif

#ifdef  MeasuProc_PUCK

#define U_START_RATIO        85     //�ٽ��ѹ��0.5*Un

#define I_START_RATIO        1000   //�����/���������ı���:1/1000*In
#define I_START_RATIO_HALF   2000   //�����/���������ı���

//#define P_START_RATIO   2000   //�����й��ʱ���
//#define Q_START_RATIO   2000   //�����޹��ʱ���


/*
//���ܱ�����ϵ����--------------------------PUCK
MeasuProc_PUCK_EXT const INT32U power_const[2][4][8]=
{
      125,125,625,625,125,625,625,625,
      625,625,625,625,125,625,625,625,
      125,125,625,625,125,625,625,625,
      625,625,625,625,125,625,1250,1250,
      
      //0020,0020,0050,0125,0005,0050,0250,0250,
      0x0014,0x0014,0x0032,0x007d,0x0005,0x0032,0x00fa,0x00fa,
      //0050,0050,0125,0250,0010,0125,0500,0500,
      0x0032,0x0032,0x007d,0x00fa,0x000a,0x007d,0x01f4,0x01f4,
      //0010,0010,0050,0100,0004,0050,0100,0200,
      0x000a,0x000a,0x0032,0x0064,0x0004,0x0032,0x0064,0x00c8,
      //0100,0050,0250,0500,0020,0125,1000,1000
      0x0064,0x0032,0x00fa,0x01f4,0x0014,0x007d,0x03e8,0x03e8      
};
MeasuProc_PUCK_EXT const INT32U power_const11[4][8]=
{
      6,6,12,6,24,12,2,2,
      12,12,6,2,12,6,1,1,
      12,12,12,6,32,12,6,3,
      6,12,2,1,6,2,1,1
};
*/
////////////////////////////////////////////////////////////////////////////////////////////////////

//�������ʱ�ã��������������,��֪��ô�ó�����
//ע�⣺���Ϳ������
/*
MeasuProc_PUCK_EXT const FP32S power_r_maxvalue[4][10]=
{
      
      0x0014000000,0x0014000000,0x0032000000,0x00fa000000,0x0005000000,0x0014000000,0x00fa000000,0x00fa000000,0x0032000000,0x00fa000000,
      
      0x0032000000,0x0032000000,0x0064000000,0x01f4000000,0x000a000000,0x0032000000,0x01f4000000,0x01f4000000,0x007d000000,0x01f4000000,
      
      0x000a000000,0x000a000000,0x0014000000,0x00c8000000,0x0004000000,0x000a000000,0x00c8000000,0x00c8000000,0x0032000000,0x00c8000000,
      
      0x0064000000,0x0064000000,0x00c8000000,0x03e8000000,0x0014000000,0x0064000000,0x03e8000000,0x03e8000000,0x00fa000000,0x03e8000000
};

MeasuProc_PUCK_EXT const FP32S power_r_maxvalue1[4][10]=
{
      
      0x0014D55555,0x0014D55555,0x0034155555,0x0138800000,0x0005355555,0x0014D55555,0x0138800000,0x0138800000,0x0034155555,0x0138800000,
      
      0x0034155555,0x0034155555,0x00682AAAAA,0x0271000000,0x000A6AAAAA,0x0034155555,0x0271000000,0x0271000000,0x00682AAAAA,0x0271000000,
      
      0x000A6AAAAA,0x000A6AAAAA,0x0014D55555,0x00D0555555,0x0003E80000,0x000A6AAAAA,0x00D0555555,0x00D0555555,0x0034155555,0x00D0555555,
      
      0x00682AAAAA,0x00682AAAAA,0x00D0555555,0x04E2000000,0x0014D55555,0x00682AAAAA,0x04E2000000,0x04E2000000,0x0138800000,0x04E2000000
};
*/


//���峣�����
MeasuProc_PUCK_EXT const INT32U PULSE_CONST[2][4][10]=    //���峣����񡢵�ѹ������
{
      //048000,  048000,  019200,  003200,  192000,  048000,  003200,  003200,  019200,  003200,
        0x00bb80,0x00bb80,0x004b00,0x000c80,0x02ee00,0x00bb80,0x000c80,0x000c80,0x004b00,0x000c80,
      //019200,  019200,  009600,  001600,  096000,  019200,  001600,  001600,  009600,  001600,
        0x004b00,0x004b00,0x002580,0x000640,0x017700,0x004b00,0x000640,0x000640,0x002580,0x000640,
      //096000,  096000,  048000,  04800,   256000,  096000,  04800,   004800,  019200,  004800,
        0x017700,0x017700,0x00bb80,0x0012c0,0x03e800,0x017700,0x0012c0,0x0012c0,0x004b00,0x0012c0,
      //09600,   09600,   004800,  00800,   048000,  009600,  00800,   00800,   003200,  00800
        0x002580,0x002580,0x0012c0,0x000320,0x00bb80,0x002580,0x000320,0x000320,0x000c80,0x000320,
      
      //050000,  050000,  020000,  004000,  200000,  050000,  004000,  004000,  020000,  004000,
        0x009C40,0x00c350,0x004e20,0x000fa0,0x030d40,0x00c350,0x000fa0,0x000fa0,0x004e20,0x000fa0,
      //020000,  020000,  010000,  001800,  100000,  020000,  002000,  002000,  008000,  002000,
        0x004e20,0x004e20,0x002710,0x000708,0x0186a0,0x004e20,0x0007d0,0x0007d0,0x001f40,0x0007d0,
      //100000,  100000,  050000,  005000,  250000,  100000,  005000,  005000,  020000,  005000,
        0x0186a0,0x0186a0,0x00c350,0x001388,0x03d090,0x0186a0,0x001388,0x001388,0x004e20,0x001388,
      //010000,  010000,  005000,  001000,  050000,  010000,  001000,  001000,  004000,  001000
        0x002710,0x002710,0x001388,0x0003e8,0x00c350,0x002710,0x0003e8,0x0003e8,0x000fa0,0x0003e8   
};

//��ѹ���: 331,3��100V	;   341��3��220V;  341��3��57.7V;     331,3��380V
MeasuProc_PUCK_EXT const FP32S U_CONST[4]=
{
      100,220,57.7,380
};

//�������: 1.5(6)A	1(2)A	5(10)A	10(40)A	0.3(1.2)A 5(6)	15(60)	20(80)	5(20)A	30(100) A
MeasuProc_PUCK_EXT const FP32S I_CONST[10]=
{
      1.5,1,5,10,0.3,5,15,20,5,30
};

//�������: 1.5(6)A	1(2)A	5(10)A	10(40)A	0.3(1.2)A 5(6)	15(60)	20(80)	5(20)A	30(100) A
MeasuProc_PUCK_EXT const FP32S I_MAX_CONST[10]=
{
      6,2,10,40,1.2,6,60,80,20,100
};


#define AUXIL_POWER_RATIO 0.2 
#define POWER_EXCEED_RATE  1.2                 //���ʳ��ޱ���

#define U_RATE      ((INT32U)3)             //����ѹ����:ԭ����Ϊ2�����ǵ�δУ��ʱ�����ݳ��ޣ�09��08��01---------------PUCK
#define I_RATE      ((INT32U)11)             //����������

#define	MAX_U_RATE	(U_RATE*UNIT_V)  	 //��ѹ���������λ��0.0001 V
#define	MAX_I_RATE	(I_RATE*UNIT_A)  	 //�������������λ��0.0001 A
#define	MAX_POWER_RATE	(U_RATE*I_RATE*1000)  	 //�������������λ��0.000001 kW,0.001W
#define	MAX_ENG_RATE	(U_RATE*I_RATE*100)  	 //�������������λ��0.00001 kwh,0.01wh


#define	EXCEED_POWER_RATE	(UNIT_V*UNIT_A*100*5)  	 //����Max���ʵı���:5��,������4��


MeasuProc_PUCK_EXT const INT32U I_RATE_CONST[10]={64,64,32,4,256,64,4,4,16,4};


MeasuProc_PUCK_EXT const INT32U LITTLE_VOLT[4]={5*2000,11*2000,3*2000,(INT32U)19*2000};

MeasuProc_PUCK_EXT const INT32U Current_down_setup[10]={15*4,15*4,30*4,167*4,3*4,15*4,167*4,167*4,50*4,167*4};  //��λ��0.1mA
//MeasuProc_PUCK_EXT const INT32U Current_up_setup[10]={15*9,15*9,30*9,167*9,3*9,15*9,167*9,167*9,50*9,167*9};   //��λ��0.1mA
MeasuProc_PUCK_EXT const INT32U Current_up_setup[10]={10*9,10*9,30*9,167*9,3*9,15*9,167*9,167*9,50*9,167*9};   //��λ��0.1mA

MeasuProc_PUCK_EXT const INT32U Current_zero[10]={12,8,40,160,3,12,240,320,40,480};       //��λ��0.1mA 

MeasuProc_PUCK_EXT const INT32U CUR_1_PER_100[10]={150,150,300,1000,30,150,1500,2000,500,3000};       //��λ��0.1mA��1%Ib
MeasuProc_PUCK_EXT const INT32U Current_threshold_reset[10]={200,200,400,1350,40,200,2000,2700,700,4000};  //��λ��0.1mA


MeasuProc_PUCK_EXT const INT32U cur_break_value[10]={80,80,157,930,16,80,930,930,267,930};                  //��λ��0.1mA
MeasuProc_PUCK_EXT const INT32U Current_threshold[10]={125,125,125,1350,25,125,1350,1350,420,1350};             //��λ��0.1mA
MeasuProc_PUCK_EXT const INT32U Current_threshold_up[10]={1500,1000,5000,10000,300,5000,15000,20000,5000,30000}; //��λ��0.1mA

#endif

INT8U LoadAllDefauEpromAndMeasuIC(void);
INT8U CopyEpromParaToMeasuIC(void);
INT8U Load_MeasureIC_Para(void);
void Init_Measure_IC(void);
INT8U CheckBothCs(void);
#endif
