
/**                                                                                                
 * @file interface.h                                                                                    
 *     { comment block }
 * @brief                                                                                           
 *     { brief description @ref interface.cpp }                                                                              
 * @author li.yao (nardoo@sohu.com)                                                                                  
 * @version v1.00                                                                               
 * @date 05/29/2008 08:40                                                                                   
 * @note 
 *     { paragraph where a note can be entered. }                                                   
 */                                                                                                 


#ifndef __INTERFACE__
#define __INTERFACE__

#define  MAXDLEN  32  //��ʾ��������ַ���Ŀ

#define  MODE_A_B_BITS        (-1)          //A/Bģʽ�¹����ʾ
#define  MINBITS              0             //Cģʽ�µ���С��ʾ��꣬��������ʾ




#if LCD_PROPERTY==LCD_SD_ZXW  ||  LCD_PROPERTY==LCD_GW_ZXW 
  #define  SET_HIGH_CODE_BIT         //��ʾ�������λ����,�����
  #define  MAXBITS              8             //Cģʽ�µ������ʾ���
#else
  #define  SET_HIGH_CODE_BIT   dispcode.bit7=0    //��ʾ�������λ����
  #define  MAXBITS              7             //Cģʽ�µ������ʾ���
#endif


#define  LEFTBITS             (MAXBITS-1)   //Cģʽ�µ���С��ʾ���
#define  RIGHTBITS            (MINBITS+1)    //Cģʽ�µ������ʾ���



typedef signed   char      s8;  ///< unsigned  8 bit quantity.
typedef unsigned char      u8;  ///< unsigned  8 bit quantity.
typedef unsigned short     u16; ///< unsigned 16 bit quantity.
typedef signed   short     s16; ///< signed   16 bit quantity.
typedef unsigned long      u32; ///< unsigned 32 bit quantity.
typedef signed   long      s32; ///< signed   32 bit quantity.
//typedef _ULonglong         u64; ///< unsigned 64 bit quantity.
//typedef _Longlong          s64; ///< signed   64 bit quantity.

#define TRUE 1
#define FALSE 0
typedef  u8 bool;



/// mode element.
typedef struct {
    u8 bit0 : 1; ///< mode2.bit0 ? "ͣ��ʱ��" : "��ǰʱ��";
    u8 bit1 : 1; ///< mode4.bit1 ? "�澯��ʾ" : "�澯�ر�";
    u8 bit2 : 1; ///< mode3.bit2 ? ʧѹ��־"��˸" : "��ʧ";
    u8 bit3 : 1; ///< mode4.bit3 ? "��λ��0" : "��λ����0";
    u8 bit4 : 1; ///< mode4.bit4 ? "����", "���" : "����", "����";
    u8 bit5 : 1; ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
    u8 bit6 : 1; ///< mode8.bit6 ? ���������� : ��������
    u8 bit7 : 1; ///< mode4.bit7 ? "��ʱ��" : "˳ʱ��";
} mode_t;

/// status element.
typedef union 
{
    struct 
    {
        u32 loss_volt_a   : 1; ///< ʧѹ A ��˸
        u32 loss_volt_b   : 1; ///< ʧѹ B ��˸
        u32 loss_volt_c   : 1; ///< ʧѹ C ��˸
        
        u32 cut_volt_a   : 1; ///< ����A: ��ʧ
        u32 cut_volt_b   : 1; ///< ����A: ��ʧ
        u32 cut_volt_c   : 1; ///< ����A: ��ʧ
        
        u32 over_volt_a   : 1; ///< ��ѹ(Ua)
        u32 over_volt_b   : 1; ///< ��ѹ(Ub)
        u32 over_volt_c   : 1; ///< ��ѹ(Uc)
        
        u32 down_volt_a   : 1; ///< Ƿѹ(Ua)
        u32 down_volt_b   : 1; ///< Ƿѹ(Ub)
        u32 down_volt_c   : 1; ///< Ƿѹ(Uc)
        
        u32 loss_cur_a    : 1; ///< ʧ�� A
        u32 loss_cur_b    : 1; ///< ʧ�� B
        u32 loss_cur_c    : 1; ///< ʧ�� C
        
        u32 loss_cut_a    : 1; ///< ���� A��С����������
        u32 loss_cut_b    : 1; ///< ���� B��С����������
        u32 loss_cut_c    : 1; ///< ���� C��С����������
        
        u32 cur_rers_a    : 1; ///< ���������� A
        u32 cur_rers_b    : 1; ///< ���������� B
        u32 cur_rers_c    : 1; ///< ���������� C
          
        u32 cell_low1     : 1; ///< ʱ�ӵ�ص͵�ѹ
        u32 cell_low2     : 1; ///< �͹��ĵ�ص͵�ѹ
        u32 cell_low3     : 1; ///< Ԥ��
        
        u32 stat_communi  : 4; ///< ͨ��״̬(RS1,RS2,����)(����)
        
        u32 volt_reverse  : 1; ///< ��ѹ"������"(��˸)
        u32 curr_reverse  : 1; ///< ����"������"(��˸)
        u32 event_warning : 1; ///< �¼��澯(��˸)
        u32 switch_opened : 1; ///< ��̼���(����)
        
        
        u32 fac_status    : 1; ///< ����(����)
        u32 jumper_short  : 1; ///< ���߶̽�(����)
        u32 reset_demand  : 1; ///< ������λ(����)        
        u32 signal_scale  : 3; ///< ͨѶģ���ź�ǿ��ָʾ(����)
        u32 status_tariff : 4; ///< ��ʾ��ǰ���ʣ�"��, ��, ƽ, ��, T5, ...Tx",
        
        u32 meter_locked  : 1; ///< �������(����)
        u32 status_online : 1; ///< ͨѶģ������ָʾ(����)
        u32  num_tariff   : 1; //��ʾ����ʱ��1����ʱ�Σ�2����ʱ�� 
        u32  CalMeter     : 1; //У���¼�
        u32  SetpScheme   : 2; //��۷�����1��2
        u32  SetpRate     : 2; //��ۣ�1��4
        
        u32  BuyFee       : 1; //�빺��
        u32  TouZhi       : 1; //͸֧
        u32  reserved     : 12; //Ԥ��        
    };
    struct 
    {
        u32 bit1maps; //< �¼�״̬λͼ
        u32 bit2maps; //< �¼�״̬λͼ
    };    
} stat_t;


/*
typedef enum {
    none = 0x00, 
    key1 = 0x01, 
    key2 = 0x02, 
    key3 = 0x04,
    key4 = 0x08,
    key5 = 0x10,
} pkey_t;
*/
typedef enum {
    modeA, modeB, modeC,
} type_t;

// ��ȡ����ֵ
u8 getpkey (void);

// ����Һ������
void lcdlight (u8 stat);

// �ж��Ƿ�ͣ��
bool poweroff (void);

// �ж��Ƿ�Ϊʵʱ����
bool rtvalue (item_t item);

// ������ʼ��
void lcdinit (void);

// A������ʱ��
s16 rolltime ();

// ��ȡЭ����������
s16 getdata (item_t id, void* buff, void* start, s16 maxlen);
// id    : ��Ӧ���ݵı�ʶ��
// buff  : ���뻺����׵�ַ
// start : ����������ʼ��ַ
// maxlen: ���뻺�����󳤶�
// return: ����д���ʵ�ʳ���

// ������ʾԪ�أ�������ʾ������Ҫ��˸��
void lcd_total     (u8 flg); ///< "��",
void lcd_phase     (u8 flg); ///< "A/B/C��",
void lcd_voltage   (u8 flg); ///< "��ѹ",
void lcd_current   (u8 flg); ///< "����",
void lcd_positive  (u8 flg); ///< mode4.bit4 ? "����" : "����";
void lcd_negative  (u8 flg); ///< mode4.bit4 ? "���" : "����";
void lcd_reactive  (u8 flg); ///< "�޹�",
void lcd_active    (u8 flg); ///< "�й�",
void lcd_power     (u8 flg); ///< "����",
void lcd_factor    (u8 flg); ///< "����",
void lcd_angle     (u8 flg); ///< "���",
void lcd_energy    (u8 flg); ///< "����",
void lcd_demand    (u8 flg); ///< "����",
void lcd_time      (u8 flg); ///< "ʱ��",
void lcd_charge    (u8 flg); ///< "���",
void lcd_lostvolt  (u8 flg); ///< "ʧѹ",
void lcd_lostcurt  (u8 flg); ///< "ʧ��",
void lcd_periods   (u8 flg); ///< "ʱ��",
void lcd_feerate   (u8 flg); ///< "����", 
void lcd_thismonth (u8 flg); ///< "����",
void lcd_lastmonth (u8 flg); ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
void lcd_lasttime (u8 flg); ///< ��xx��
void lcd_times     (u8 flg); ///< ��xx
void lcd_assemble  (u8 flg); ///< "�޹���Ϸ�ʽ1 or 2",
void lcd_quadrant  (u8 flg); ///< "XX����",
void lcd_tariff    (u8 flg); ///< ��ʾ"����Tx",
void lcd_times     (u8 flg); ///< ��ʾ"��XX��",
void lcd_jieti     (u8 flg); ///< ����
void lcd_dianjia   (u8 flg); ///���
void lcd_value (const char* s);

// �����ʾ���ݵ�����
void lcd_data (item_t item, const char* frmt);

// �����ʾ���������
void lcd_code (code_t user, code_t code, curs_t curs,u8 SubCurs,u8 changeFlag,code_t changecode);

// �����ʾ����������
void lcd_mode (u8 type);

// ��ʾ����������
void lcd_update (void);

// �����ʾ�¼�״̬
void lcd_events (void);

u8 Modi_Item(item_t item,item_t *Dst);


#endif
