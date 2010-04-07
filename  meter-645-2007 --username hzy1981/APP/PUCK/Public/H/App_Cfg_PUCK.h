
#ifndef APP_CFG_PUCK
#define APP_CFG_PUCK

#define TH_MODE     0   //˫����
#define TF_MODE     1   //������

#define PARSE_331    0
#define PARSE_341    1

#define PULSE_TYPE1  0
#define PULSE_TYPE2  1

#define VOLT_3100    0
#define VOLT_3220    1
#define VOLT_3577    2
#define VOLT_3380    3

#define CURR_1x5_6   0
#define CURR_1_2     1
#define CURR_5_10    2
#define CURR_10_40   3
#define CURR_0x3_1x2 4
#define CURR_5_6     5
#define CURR_15_60   6
#define CURR_20_80   7
#define CURR_5_20   8
#define CURR_30_100   9

#define CAL_MEASU_OVER   0x55 //MeasuICУ����ɱ�־

#define PARA_SRAM  0
#define PARA_FLASH 1

#define MEASU_PARA_START  (REG_W_START&0x7F)
#define MEASU_PARA_CURSTART  (REG_W_ISTART&0x7F)
#define MEASU_PARA_ISTART (REG_W_ISTART&0x7F)
#define MEASU_PARA_PULSE  (REG_W_PULSE&0x7F)
#define MEASU_PARA_ENMODE (REG_W_ENMODE&0x7F)
#define MEASU_PARA_VGAIN  (REG_W_VGAIN&0x7F)
#define MEASU_PARA_CS       0x40   //���CS��λ��



#define MEASURE_ERROR_STATICS_EN //�������򿪼�������ͳ�ƣ�ͬʱ������Ӧ�� Sram��Դ��Flash��Դ
#define OS_DEBG_EN       //OS���ܴ� ��

//#define MEASURE_VAR_BAK_EN       //������ʹ�ܵ��ܱ����ı���
//#define MEASU_ANGLE_RD           //�������Ƕ���7022�������رգ����Լ����,����رոú꣬�Ƕ��Լ���
#define DRV_TEST_EN             //����:ʹ���������Թ���
//#define CONFLICT_TAB_CHKEN     //����������ñ��Ƿ��ͻ



//�������ú�
#define CHANNEL_FAST_EN           //��򿪣�ͨ��ͨ��������Ӧ


                   
#define LOSS_VOLT_ONLY           //�ж����ݣ�ʧѹֻ�ж���ѹ��������޹�
#define LOSS_CURR_ONLY           //�ж����ݣ�ʧ��ֻ�ж������������ƽ�����޹�
                             //ͨ�ð汾
//#define MULTI_LOSS_VOLT_EN       //�����ж�����򿪣�ʧѹ�����ж�����رգ������ж�
//#define MULTI_LOSS_CURR_EN       //�����ж�����򿪣�ʧ�������ж�(AB,AC,BC)����رգ������ж���ע�⣺ȫʧ��/A /B/Cʧ��Ϊ�����¼�


//�����������ú�
#define DEFAULT_PULSE_SPEC  PULSE_TYPE2
#define DEFAULT_VOLT_SPEC   VOLT_3220
#define DEFAULT_CURR_SPEC   CURR_1x5_6
#define DEFAULT_TFH_SPEC    TH_MODE
#if DEFAULT_VOLT_SPEC==VOLT_3220 || DEFAULT_VOLT_SPEC==VOLT_3577
  #define DEFAULT_PARSE_SPEC  PARSE_341
#else
  #define DEFAULT_PARSE_SPEC  PARSE_331
#endif
#define DEFAULT_AC_PULSE        6400
#define DEFAULT_REAC_PULSE      6400


//LCD����
#define LCD_NORMAL           0         //ͨ��Һ��
#define LCD_JS_ZXW           1         //����Һ��---������
#define LCD_JS_JX            2         //����Һ��---����
#define LCD_SD_ZXW           3         //ɽ��Һ��---������(����ǰһ��Һ��)
#define LCD_GW_ZXW           4         //����Һ��---������
#define LCD_EASY_GZL         5         //��Һ��---��׿��


#define DRV_SIMU_DS3231    0//�꿪������DS3231�����ģ�⹦�ܣ��رգ���IIC��Ӳ������
#define DRV_SIMU_RX8025    1
#define DRV_SIMU_RX8025T   2
#define DRV_SIMU_RV3029C2  3



#define MEASU_7028A        0
#define MEASU_7022B        1
#define MEASU_7022C        2



#define ALL_LOSS_SOFT              0  //ȫʧѹȫ��ͨ�������ʵ��
#define ALL_LOSS_HARD_SINGLE       1  //ȫʧѹͨ��Ӳ���������������ʵ��
#define ALL_LOSS_HARD_MULTI        2  //ȫʧѹͨ��Ӳ����������Ӳ����ʵ��

//----------------------------------------��Ӳ���������----------------------------------------------
//��ť����
#undef  LEFT_KEY_EN                       //��򿪣�ʹ����ť
#undef  NEAR_IRDA_EN                      //��򿪣�ʹ����������
#undef  RIGHT_KEY_EN                      //��򿪣�ʹ���Ұ�ť
#undef  DIS_PARA_JUMP_EN                  //��򿪣�ʹ�ܲ����޸�����

#define MEASU_IC_TYPE       MEASU_7022B
#define LCD_PROPERTY        LCD_GW_ZXW

#define FM_ROM_FM16_EN                    //�� FM16����

#define DRV_HARD_DS3231    0              //1:3231Ӳ��I2C����;0:Ӳ��I2C�ر� 

#define MEASU_BAKPWR_NEW_EN                    //��:ʹ���µ�7022�󱸵�Դ��ʽ

#define LOW_COST_HARD_EN                         //�򿪣��ͳɱ�Ӳ����ESAM_CLOCK,CPU_CLOCK,CF1,���⻽��Ӳ��

#ifdef LOW_COST_HARD_EN
  #define RST_IC_7X6_EN
  #define EXT_RTC_TYPE       DRV_SIMU_RX8025T  //DRV_SIMU_DS3231 DRV_SIMU_RX8025T  DRV_SIMU_RV3029C2
  #define ALL_LOSS_TYPE      ALL_LOSS_SOFT       //��򿪣��� Ӳ����ȫʧѹ�������رգ�ͨ�����ȫʧѹ
  #undef  DOWN_COVER_ERR                         //��:����Ӹô���
#else
  #undef RST_IC_7X6_EN
  #define EXT_RTC_TYPE       DRV_SIMU_DS3231  //DRV_SIMU_DS3231 DRV_SIMU_RX8025T  DRV_SIMU_RV3029C2
  #define ALL_LOSS_TYPE      ALL_LOSS_HARD_SINGLE       //��򿪣��� Ӳ����ȫʧѹ�������رգ�ͨ�����ȫʧѹ
  #define DOWN_COVER_ERR                         //��:����Ӹô���
#endif

//----------------------------------------�빦���������----------------------------------------------
//#define ALL_LOSS_DIS_U                    //�� :ȫʧѹ���������Ѻ���˸��ѹ
//#define REMOTER_FUNC_EN                       //��ң��������
#define I_ORDER_CHK_EN             0         //1:����������ʹ�ܣ�0���������������ֹ
#define DIS_METER_FAULT_EN         1         //1:��������ʾʹ�ܣ�0�������ϲ���ʾ



//���һ���������ã������塢ʱ�Ρ�����������
//1:�������º꣬��Const_Port_Status[]�е�MultiFlagΪ0����1���岻һ����
//2������ Const_Port_Status[]�е� MultiFlagΪ0����1
//3:����������������3��һ���ӹ��ã�������ʹ�����ã�MultiFlag��0(Ϊ1��Port_Out_Pub�����У����� END��)��SEC_MULTI_PORT��1��
#define SEC_MULTI_PORT 1          //0�������岻�Ǹ��϶��ӣ�1���������Ǹ��϶���(���ã�
#define MULTI_3_PORT   2          //0�����Ǹ��϶��ӣ�1���Ǹ��϶��ӣ����������岻���ã�2�Ǹ��϶��ӣ����������干�ã�
#define SEC_OUT_POWER_ON   1      //1:�ϵ�����������壻0���ϵ�����ģʽ�־����Ƿ����������

//��ʾ���ϵͳ�������
#define SYS_ERR_DIS_EN          1 //0----------���ϵͳ�������رգ�1----------���ϵͳ��������
#define HARD_ERR_BEEP           0 //1��򿪣�Ӳ����������led����������������λ���Լ�ʱ�򱨾�,0�ر�

//---------------------------------------------------------------------------------------------------
#define HT1623    0
#define BL55076   1

#if LCD_PROPERTY==LCD_NORMAL
    #define LCD_DRV_CHIP HT1623   
    #include "APP_LCD_Pub.h"
#endif

#if LCD_PROPERTY==LCD_JS_ZXW
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_JS_ZXW.h"
#endif

#if LCD_PROPERTY==LCD_JS_JX
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_JS_JX.h"
#endif

#if LCD_PROPERTY==LCD_SD_ZXW
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_SD_ZXW.h"
#endif

#if LCD_PROPERTY==LCD_GW_ZXW
    #define LCD_DRV_CHIP HT1623 
    #include "APP_LCD_Pub_GW_ZXW.h"
#endif

#if LCD_PROPERTY==LCD_EASY_GZL
    #define LCD_DRV_CHIP BL55076    
    #include "APP_LCD_LIB_GZL.h"
#endif


//Һ�������ڵ� 8 �ַ���������
#if LCD_PROPERTY >= LCD_SD_ZXW  //ֻ��8��8��Һ��     
   #define LCD_MIN_8              // �꿪������ʾ����Ϊ8��LED_8�� LCDƬ��
   #undef  DIS_ITEM_BYTE_4        //�꿪������ʾ��Ŀ����4�ֽ����ã�������5�ֽ�����
#else
   #undef LCD_MIN_8              // �꿪������ʾ����Ϊ8��LED_8�� LCDƬ��
   #undef DIS_ITEM_BYTE_4       //�꿪������ʾ��Ŀ����4�ֽ����ã�������5�ֽ�����
#endif



//��������
#if ((NET_METER EQ CARRIER_METER)||(NET_METER EQ GPRS_METER))//�ز���GPRS��
  #define UART1_EN 
#elif (PREPAID_EN && (PREPAID_LOCAL_REMOTE EQ PREPAID_REMOTE)) //��ģ���Զ�̷ѿر�
  #define UART1_EN 
#else
  #undef  UART1_EN
#endif

//�ڲ�ʱ�ӵ�ع���ʱ������
#define BAT_RUN_TIME_PWROFF       1   //ͳ�Ƶ����RTC����ʱ��
#define BAT_RUN_TIME_PWRON        2   //ͳ���ϵ�����RTC����ʱ��

#define BAT_RUN_TIME     (BAT_RUN_TIME_PWROFF | BAT_RUN_TIME_PWRON)         //ͳ��RTC����ʱ��

#define COMPUTER_CAL_TYPE       1  //֧����̨���У��
#define SELF_CAL_TYPE           2  //����Զ�У��
#define ALL_CAL_TYPE            3  //֧��2��У��

#define CAL_METER_TYPE ALL_CAL_TYPE


#endif
