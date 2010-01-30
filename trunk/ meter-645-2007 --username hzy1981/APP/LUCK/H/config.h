
/**
 * @file config.h
 *     { comment block }
 * @brief
 *     { brief description @ref config.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:40
 * @note
 *     { paragraph where a note can be entered. }
 */

#ifndef __CONFIG__
#define __CONFIG__

#define  MAXCOUNT   (sizeof(table) / sizeof(scrn_t))
#define  DIVERS     DI_METER_SOFTWARE_VERSION
#define  MADDR0     DI_METER_ADDR0
#define  MADDR1     DI_METER_ADDR1



// screen element.
typedef struct {
    u32 total     : 1; ///< "��",
    u32 phase     : 4; ///< "A/B/C/N��",
    u32 voltage   : 1; ///< "��ѹ",
    u32 current   : 1; ///< "����",
    u32 positive  : 1; ///< mode4.bit4 ? "����" : "����";
    
    u32 negative  : 1; ///< mode4.bit4 ? "���" : "����";
    u32 reactive  : 1; ///< "�޹�",
    u32 active    : 1; ///< "�й�",
    u32 power     : 1; ///< "����",
    u32 factor    : 1; ///< "����",
    u32 angle     : 1; ///< "���",
    u32 energy    : 1; ///< "����",
    u32 demand    : 1; ///< "����",
    
    u32 time      : 1; ///< "ʱ��",
    u32 charge    : 1; ///< "���",
    u32 lostvolt  : 1; ///< "ʧѹ",
    u32 lostcurt  : 1; ///< "ʧ��",
    u32 periods   : 1; ///< "ʱ��",
    u32 feerate   : 1; ///< "����",    
    u32 thismonth : 1; ///< "��ǰ",
    u32 yuan      : 1; ///< "Ԫ",
    
    u32 shenyu    : 1; ///< "ʣ��", 
    u32 lastmonth : 1; ///< ��ʾ"��XX��",
    u32 assemble  : 2; ///< "�޹���Ϸ�ʽ1 or 2", mode4.bit7 ? ����"��ʱ��" : ����"˳ʱ��";    
    u32 jine      : 1; ///< "���",
    u32 jieti     : 1; //����
    u32 dianjia   : 1; //���  
    u32 lasttime  : 1; ///< ��ʾ"��XX��",  
    
    u16 quadrant  : 3; ///< "XX����",    
    u16 tariff    : 4; ///< ��ʾ"����Tx",      
    u16 times     : 3; //XX
    u16 res       : 6; ///Ԥ��4 bits  ��XX
    
} elem_t;

#define GROUP_NO            0
#define GROUP_TARIFF        1      //����������
#define GROUP_SETTLE        2      //����������
#define GROUP_PHASE         4      //���������
#define GROUP_HARMO         8      //��г����������
#define GROUP_TIMES         16      //ǰ n ��
#define GROUP_DATE          32     //���������յȼ�����
#define GROUP_LOAD_DATA     6      //�����������

#define MAX_GROUP_NUM   8


#define MAX_TARIFF          63     //��������
#define MAX_SETTLE          12     //��������
#define MAX_PHASE           3      //������
#define MAX_HARMO           21     //���г������
#define MAX_PASSW           9      //�������ȼ�����
#define MAX_DATE            254     //��󹫹����յȼ�����
#define MAX_LOAD_DATA       6     //��󸺺��������



#define NO_BYTE_POS   0xff

typedef struct { 
    INT8U    GroupFlag;      //ͬ�����ݼ��ϱ�ʶ
    INT8U    BytePos;        //ͬ���ڱ�ʶƫ��
}GroupTypeStr;

typedef struct {        /// screen element.
    //code_t      code;       //Cģʽ�µ���ʾȫ�����룬����-----PUCK
    item_t      item;       //Cģʽ�µ��������------PUCK
    GroupTypeStr   GroupType[2];
    const char* frmt;    
    elem_t      elem;
} scrn_t;

static const scrn_t table[] = {
/***********************************��ǰ/�����ܵ���---����ʺͽ�������أ���/����xx****************************************************/
   {0x00000000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{   // ����й��ܵ���
                                         .active    = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .energy    = 1,}},
                                         
                                           
   {0x00010000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",   {    // �����й��ܵ���
                                         .positive  = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .active    = 1,
                                         .energy    = 1,}},                                      
    
    
   {0x00020000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",   {    // �����й��ܵ���
                                         .negative  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}},
                                           
   {0x00030000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // �����޹�(���1)������
                                         .positive  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .assemble  = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
    
    {0x00040000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // �����޹�(���2)������
                                         .negative  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .assemble  = 2,
                                         .reactive  = 1,
                                         .energy    = 1,}},
                                           
    {0x00050000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // I�����޹�����
                                         .quadrant  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
    
    {0x00060000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // II�����޹�����
                                         .quadrant  = 2,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
                                           
    {0x00070000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // III�����޹�����
                                         .quadrant  = 3,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},
    
    {0x00080000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {    // IV�����޹�����
                                         .quadrant  = 4,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .reactive  = 1,
                                         .energy    = 1,}},                                          
                                           
    {0x00090000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {    // ���������ܵ���
                                         .positive  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .energy    = 1,}},
    
    {0x000A0000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {    // ���������ܵ���
                                          .negative  = 1,
                                          .total     = 1,
                                          .thismonth = 1,
                                          .energy    = 1,}}, 
    /*
    {0x00800000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // �����ܵ���
                                        .negative  = 1,
                                        .total     = 1,
                                        .energy    = 1,}}, 
    
    {0x00810000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // �����й������ܵ���
                                         .positive  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}}, 
                                               
    {0x00820000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // �����й������ܵ���
                                         .negative  = 1,
                                         .total     = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}}, 
    
    {0x00830000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // �����й�г���ܵ���
                                         .positive  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}}, 
                                               
    {0x00840000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // �����й�г���ܵ���
                                         .negative  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}},                                            
                                          
    {0x00850000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ͭ���й��ܵ��ܲ�����
                                         .negative  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}}, 
    {0x00860000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // �����й��ܵ��ܲ�����
                                         .negative  = 1,
                                         .active    = 1,
                                         .thismonth = 1,
                                         .total     = 1,
                                         .energy    = 1,}},
                                                                                            
 */                                                                                          
/***********************************A�൱ǰ/�Ͻ����յ���---���������أ���ǰ/��x�ν�����****************************************************/
    {0x00150000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // ��ǰ/��x�����������й�����
                                         .phase     = 1,
                                         .positive  = 1,
                                         .thismonth = 1,
                                         .active    = 1,
                                         .energy    = 1,}},

    {0x00160000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // ��ǰ/��x�����շ����й�����
                                           .phase     = 1,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},                                           

    {0x00170000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x����������޹�1����
                                           .phase     = 1,
                                           .assemble  = 1,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},
     
    {0x00180000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {  // ��ǰ/��x����������޹�2����
                                           .phase     = 1,
                                           .assemble  = 2,
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 

    {0x00190000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������1�����޹�����
                                           .phase     = 1,
                                           .thismonth = 1,
                                           .quadrant  = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},                                           


    {0x001A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������2�����޹�����
                                           .phase     = 1, 
                                           .quadrant  = 2,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},   
 
    {0x001B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������3�����޹�����
                                           .phase     = 1, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 
                                           
    {0x001C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������4�����޹�����
                                           .phase     = 1, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},      
     
     
    {0x001D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // ��ǰ/��x�������������ڵ���
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x001E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // ��ǰ/��x�����շ������ڵ���
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},       
    /* 
    {0x00940000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ��ǰ/��x�����ܵ���
                                           .phase  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},  
                                           
    {0x00950000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ��ǰ/��x�����й������ܵ���
                                           .phase     = 1, 
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .energy    = 1,}}, 
     
    {0x00960000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {   // ��ǰ/��x�����й������ܵ���
                                           .phase     = 1, 
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .energy    = 1,}}, 
    
    {0x00970000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��x�����й�г���ܵ���
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                               
    {0x00980000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��x�����й�г���ܵ���
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
        
     
    {0x00990000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��xͭ���й��ܵ��ܲ�����
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x009A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��x�����й��ܵ��ܲ�����
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},     
*/
/***********************************B�����---���������أ���ǰ/��x�ν�����****************************************************/
    {0x00290000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // ��ǰ/��x�����������й�����
                                           .phase     = 2,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},

    {0x002A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // ��ǰ/��x�����շ����й�����
                                           .phase     = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},                                           

    {0x002B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x����������޹�1����
                                           .phase     = 2,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},
     
    {0x002C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {  // ��ǰ/��x����������޹�2����
                                           .phase     = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 

    {0x002D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������1�����޹�����
                                           .phase     = 2, 
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},                                           


    {0x002E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������2�����޹�����
                                           .phase     = 2, 
                                           .quadrant  = 2,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},   
 
    {0x002F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������3�����޹�����
                                           .phase     = 2, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00300000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������4�����޹�����
                                           .phase     = 2, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},      
     
     
    {0x00310000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // ��ǰ/��x�������������ڵ���
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00320000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // ��ǰ/��x�����շ������ڵ���
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},       
    /* 
    {0x00A80000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ��ǰ/��x�����ܵ���
                                           .phase  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},  
                                           
    {0x00A90000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ��ǰ/��x�����й������ܵ���
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
     
    {0x00AA0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {   // ��ǰ/��x�����й������ܵ���
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
    
    {0x00AB0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // ��ǰ/��x�����й�г���ܵ���
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                               
    {0x00AC0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��x�����й�г���ܵ���
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
    
    
    
    {0x00AD0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��xͭ���й��ܵ��ܲ�����
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00AE0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // ��ǰ/��x�����й��ܵ��ܲ�����
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},     
     
   */  
/***********************************C�����---���������أ���ǰ/��x�ν�����****************************************************/
    {0x003D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // ��ǰ/��x�����������й�����
                                           .phase     = 3,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},

    {0x003E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", { // ��ǰ/��x�����շ����й�����
                                           .phase     = 3,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .energy    = 1,}},                                           

    {0x003F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x����������޹�1����
                                           .phase     = 3,
                                           .assemble  = 1,
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},
     
    {0x00400000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", {  // ��ǰ/��x����������޹�2����
                                           .phase     = 3,
                                           .assemble  = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}}, 

    {0x00410000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������1�����޹�����
                                           .phase     = 3, 
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},                                           


    {0x00420000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������2�����޹�����
                                           .phase     = 3, 
                                           .quadrant  = 2,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},   
 
    {0x00430000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������3�����޹�����
                                           .phase     = 3, 
                                           .quadrant  = 3,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00440000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kvarh", { // ��ǰ/��x������4�����޹�����
                                           .phase     = 3, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .energy    = 1,}},      
     
     
    {0x00450000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // ��ǰ/��x�������������ڵ���
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00460000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kVAh", {  // ��ǰ/��x�����շ������ڵ���
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},       
     
    /*
    {0x00BC0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ��ǰ/��x�����ܵ���
                                           .phase  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},  
                                           
    {0x00BD0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {    // ��ǰ/��x�����й������ܵ���
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
     
    {0x00BE0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{   // ��ǰ/��x�����й������ܵ���
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
    
    {0x00BF0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // ��ǰ/��x�����й�г���ܵ���
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                               
    {0x00C00000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // ��ǰ/��x�����й�г���ܵ���
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
    
    
    {0x00C10000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh",{  // ��ǰ/��xͭ���й��ܵ��ܲ�����
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}}, 
                                           
    {0x00C20000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "XXXXX#.##|kWh", {  // ��ǰ/��x�����й��ܵ��ܲ�����
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .energy    = 1,}},                                           
                                           
     */           
/***********************************��ǰ/�����й�����������ʱ��---����ʺͽ�������أ���/����xx****************************************************/
    {0x01010000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // �����й����������ʱ��
                                           .positive  = 1,
                                           .active    = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
    {0x01020000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // �����й����������ʱ��
                                           .negative  = 1,
                                           .thismonth = 1,
                                            .total     = 1,
                                           .active    = 1,
                                           .demand    = 1,}},
                                           
    {0x01030000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // ����޹�1���������ʱ��
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .total     = 1,
                                           .assemble  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
                                           
    {0x01040000,{{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|",{   // ����޹�2���������ʱ��
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .total     = 1,
                                           .assemble  = 2,                                           
                                           .reactive  = 1,
                                           .demand    = 1,}},

    {0x01050000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // I�����޹����������ʱ��
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .total     = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
    
    {0x01060000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // II�����޹����������ʱ��
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
    {0x01070000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // III�����޹����������ʱ��
                                           .quadrant  = 3,
                                           .reactive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
    
    {0x01080000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // IV�����޹����������ʱ��
                                           .quadrant  = 4,
                                           .reactive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},  
                                           
    {0x01090000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // �������������������ʱ��
                                           .positive  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
    
    {0x010A0000, {{.GroupFlag=GROUP_TARIFF,.BytePos=1},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {    // �������������������ʱ��
                                           .negative  = 1,
                                           .total     = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 


/***********************************A�൱ǰ/�Ͻ������������������ʱ��---���������أ���ǰ/��x�ν�����****************************************************
    {0x01150000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x�����������й��������������ʱ��
                                           .phase     = 1,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},

    {0x01160000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x�����շ����й��������������ʱ��
                                           .phase     = 1,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},                                           

    {0x01170000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x����������޹�1�������������ʱ��
                                           .phase     = 1,
                                           .assemble  = 1,
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
     
    {0x01180000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // ��ǰ/��x����������޹�2�������������ʱ��
                                           .phase     = 1,
                                           .assemble  = 2,
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 

    {0x01190000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������1�����޹��������������ʱ��
                                           .phase     = 1, 
                                           .quadrant  = 1,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},                                           


    {0x011A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������2�����޹��������������ʱ��
                                           .phase     = 1, 
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},   
 
    {0x011B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������3�����޹��������������ʱ��
                                           .phase     = 1, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 
                                           
    {0x011C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������4�����޹��������������ʱ��
                                           .phase     = 1, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},      
     
     
    {0x011D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // ��ǰ/��x���������������������������ʱ��
                                           .phase     = 1, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
                                           
    {0x011E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // ��ǰ/��x�����շ��������������������ʱ��
                                           .phase     = 1, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
***********************************B�൱ǰ/�Ͻ������������������ʱ��---���������أ���ǰ/��x�ν�����****************************************************
    {0x01290000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x�����������й��������������ʱ��
                                           .phase     = 2,
                                           .positive  = 1,
                                           .active    = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},

    {0x012A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x�����շ����й��������������ʱ��
                                           .phase     = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},                                           

    {0x012B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x����������޹�1�������������ʱ��
                                           .phase     = 2,
                                           .assemble  = 1,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
     
    {0x012C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // ��ǰ/��x����������޹�2�������������ʱ��
                                           .phase     = 2,
                                           .assemble  = 2,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 

    {0x012D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������1�����޹��������������ʱ��
                                           .phase     = 2, 
                                           .quadrant  = 1,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},                                           


    {0x012E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������2�����޹��������������ʱ��
                                           .phase     = 2, 
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},   
 
    {0x012F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������3�����޹��������������ʱ��
                                           .phase     = 2, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01300000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������4�����޹��������������ʱ��
                                           .phase     = 2, 
                                           .quadrant  = 4,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},      
     
     
    {0x01310000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // ��ǰ/��x���������������������������ʱ��
                                           .phase     = 2, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01320000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "##:##:##:##|tmXXXXX#.##|kVA", {  // ��ǰ/��x�����շ��������������������ʱ��
                                           .phase     = 2, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},                                                         


                                           
***********************************C�൱ǰ/�Ͻ������������������ʱ��---���������أ���ǰ/��x�ν�����****************************************************
    {0x013D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x�����������й��������������ʱ��
                                           .phase     = 3,
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},

    {0x013E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x�����շ����й��������������ʱ��
                                           .phase     = 3,
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .active    = 1,
                                           .demand    = 1,}},                                           

    {0x013F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x����������޹�1�������������ʱ��
                                           .phase     = 3,
                                           .assemble  = 1,
                                           .thismonth = 1,
                                           .positive  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},
     
    {0x01400000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // ��ǰ/��x����������޹�2�������������ʱ��
                                           .phase     = 3,
                                           .assemble  = 2,
                                           .thismonth = 1,
                                           .negative  = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 

    {0x01410000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������1�����޹��������������ʱ��
                                           .phase     = 3, 
                                           .quadrant  = 1,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},                                           


    {0x01420000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������2�����޹��������������ʱ��
                                           .phase     = 3, 
                                           .quadrant  = 2,
                                           .reactive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},   
 
    {0x01430000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������3�����޹��������������ʱ��
                                           .phase     = 3, 
                                           .quadrant  = 3,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01440000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", { // ��ǰ/��x������4�����޹��������������ʱ��
                                           .phase     = 3, 
                                           .quadrant  = 4,
                                           .thismonth = 1,
                                           .reactive  = 1,
                                           .demand    = 1,}},      
     
     
    {0x01450000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // ��ǰ/��x���������������������������ʱ��
                                           .phase     = 3, 
                                           .positive  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}}, 
                                           
    {0x01460000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "#|", {  // ��ǰ/��x�����շ��������������������ʱ��
                                           .phase     = 3, 
                                           .negative  = 1,
                                           .thismonth = 1,
                                           .demand    = 1,}},
                                           
***************************************************/  

/***********************************************************����****************************************************/                                         
                                           
    {_PDI_A_VOL, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.##|V",      {    // A���ѹ��2λС����3���ֽ�,HUCK����
                                           .phase     = 1, 
                                           .voltage   = 1,}},
    
    {_PDI_B_VOL, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.##|V",      {    // B���ѹ��2λС����3���ֽ�,HUCK����
                                           .phase     = 2, 
                                           .voltage   = 1,}},
                                           
    {_PDI_C_VOL, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.##|V",      {    // C���ѹ��2λС����3���ֽ�,HUCK����
                                           .phase     = 3, 
                                           .voltage   = 1,}},                                              

    {_PDI_A_CUR, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|A",    {    // A�������4λС����4���ֽ�,HUCK����
                                           .phase     = 1, 
                                           .current   = 1,}},

    {_PDI_B_CUR, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|A",    {    // B�������4λС����4���ֽ�,HUCK����
                                           .phase     = 2,    
                                           .current   = 1,}},
                                           
    {_PDI_C_CUR, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|A",    {    // C�������4λС����4���ֽ�,HUCK����
                                           .phase     = 3, 
                                           .current   = 1,}},
                                           
    {0x02030000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "XXX#.####|kW",  {    // �й�����
                                           .active    = 1,
                                           .total     = 1,
                                           .power     = 1,}},
    
    {0x02040000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "XXX#.####|kvar",  {   //�޹�����
                                           .reactive  = 1,
                                           .total     = 1,
                                           .power     = 1,}},
    
    {0x02050000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "XXX#.####|kVA",   {   // ���ڹ���
                                           .total     = 1, 
                                           .power     = 1,}},
    
    {0x02060000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "X#.###|",          {    // ����������
                                           .total     = 1,
                                           .factor    = 1,}},
    
    {_PDI_A_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // A ��ǣ�2λС����3���ֽ�,HUCK����
                                           .phase     = 1, 
                                           .angle     = 1,}},
  

    {_PDI_B_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // B ��ǣ�2λС����3���ֽ�,HUCK����
                                           .phase     = 2, 
                                           .angle     = 1,}},
                                           
    {_PDI_C_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // C ��ǣ�2λС����3���ֽ�,HUCK����
                                           .phase     = 3, 
                                           .angle     = 1,}},
                                           
    {_PDI_SUM_ANGLE, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.##|o",        {    // �����
                                           .total     = 1, 
                                           .angle     = 1,}},                                           
    /*                                       
    {0x02080100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // ��ѹ����ʧ���
                                           .phase     = 1,}},
    {0x02080200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // ��ѹ����ʧ���
                                           .phase     = 2,}},
    {0x02080300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // ��ѹ����ʧ���
                                           .phase     = 3,}},
    
    {0x02090100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // ��������ʧ���
                                           .phase     = 1,}},                                                       
                                           
    {0x02090200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // ��������ʧ���
                                           .phase     = 2,}},                
                                           
    {0x02090300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",        {    // ��������ʧ���
                                           .phase     = 3,}},                    
                                                                  
    {0x160000, 0x020A0100, {{.GroupFlag=GROUP_HARMO,.BytePos=0},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "X#.##|",        {    // ��ѹг������
                                           .voltage     = 1,}},
    
    {0x160000, 0x020B0100, {{.GroupFlag=GROUP_HARMO,.BytePos=0},{.GroupFlag=GROUP_PHASE,.BytePos=1}}, "X#.##|",        {    // ����г������
                                           .current     = 1,}},   
    
    
    {0x02800001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",    {    // ���ߵ���
                                           .current   = 1,}}, 
                                           
    */
    {0x02800002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|Hz",     {.total     = 0,}}, // ��ǰƵ��
    
    {0x02800003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",    {.total     = 1,    // һ�����й���ƽ������
                                           .active    = 1, 
                                           .power     = 1,}},
                                           
    {0x02800004, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",    {.thismonth     = 1,    // ��ǰ�й�����
                                           .active    = 1, 
                                           .demand     = 1,}},
   
    {0x02800005, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kvar",    {.thismonth    = 1,    // ��ǰ�޹�����
                                           .reactive    = 1, 
                                           .demand     = 1,}},
  
    {0x02800006, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kVA",    {.thismonth    = 1,    // ��ǰ��������
                                           .demand     = 1,}},
  
    //{0x02800007, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|",    {.total     =0}},     //�����¶�
  
    {0x02800008, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|V",   {.total     =0}},   //ʱ�ӵ�ص�ѹ(�ڲ�)

  
    {0x02800009, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|V",   {.total     =0}},    //�����ص�ѹ(�ⲿ)
  
    {0x0280000A, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXXXX#|",  {.total     =0}},   // �ڲ���ع���ʱ��
    
    
    

/*                                        
    {0x03020000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x03030000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x03040000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ������ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x03050000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //ȫʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    
*/  
    {0x03060000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //������Դʧ���ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
                                           
/*                                      
    {0x03070000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x03080000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x03090000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},                                       
    {0x030A0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x030B0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x030C0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},                                       
    {0x030D0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x030E0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x030F0000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#####|",      {    //A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},                                      
                                           
*/                                         

    {0x03110000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",       {    //�����ܴ�����3�ֽ�
                                           .total     = 0,}},
                                           
    {0x03110001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",      {    //��n�ε��緢��ʱ�̣�����ʱ��
                                           .total     = 0,}},
                                           
    {0x03300000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //����ܴ���,��3�ֽ�
                                           .total     = 0,}},
   
    {0x03300001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",      {    //����1�Σ���̼�¼��
                                           .total     = 0,}},
                                           
                                           
    {0x03300100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��������ܴ���,��3�ֽ�
                                           .total     = 0,}},
                                           
    {0x03300200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //���������ܴ���,��3�ֽ�
                                           .total     = 0,}},

    {0x03300300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�¼������ܴ���(�������弰������),��3�ֽ�
                                           .total     = 0,}},
                                           
    
    {0x03300400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    // Уʱ�ܴ���,��3�ֽ�
                                           .total     = 0,}},                                        
                                           
    {0x03300500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //ʱ�α����ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //ʱ�������ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�����ձ���ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�ڼ��ձ���ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�й���Ϸ�ʽ����ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�޹���Ϸ�ʽ1����ܴ�����3�ֽ�
                                           .total     = 0,}},                                       
    {0x03300B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�޹���Ϸ�ʽ2����ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //�����ձ���ܴ�����3�ֽ�
                                           .total     = 0,}},
/* 
    {0x03300D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //������ܴ�����3�ֽ�
                                           .total     = 0,}},
    {0x03300E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //����ť���ܴ�����3�ֽ�
                                           .total     = 0,}}, 
*/

  /*************************************************************�α���*******************************************************************/ 

#if LCD_PROPERTY==LCD_SD_ZXW  ||  LCD_PROPERTY==LCD_GW_ZXW 
    {0x04000101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "###### ?#|",    {.time      = 1,}}, // ��ǰ�����ܴ�(��:��:�� ��)
#else
    {0x04000101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "#20###### ?#|",    {.time      = 1,}}, // ��ǰ�����ܴ�(��:��:�� ��)
#endif

    {0x04000102, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##:##|",         {.time      = 1,}}, // ʱ��(ʱ:��:��)
    {0x04000103, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",               {.total     = 0,}}, // �����������
    {0x04000104, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",               {.total     = 0,}}, // ����ʱ��
    {0x04000105, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",             {.total     = 0,}}, // ������
    {0x04000106, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 1,}}, // ����ʱ�����л�ʱ��(�꣺�£��գ�ʱ����)
    {0x04000107, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 1,}}, // ������ʱ�����л�ʱ��(�꣺�£��գ�ʱ����)
    
    //Ԥ������չ�� 04000108
    {0x04000108, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 0,}}, // ���׷��ʵ���л�ʱ��(�꣺�£��գ�ʱ����)
    {0x04000109, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.time      = 0,}}, // ���׽����л�ʱ��(�꣺�£��գ�ʱ����)
    
    
    {0x04000201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, //��ʱ����
    {0x04000202, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, //��ʱ�α���
    {0x04000203, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // ��ʱ����
    {0x04000204, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // ������
    {0x04000205, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",    {.total   = 0,}}, // ����������
    //{0x04000206, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // г����Ŀ
    {0x04000207, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total   = 0,}}, // ������
   
    {0x04000301, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //�Զ�ѭ����ʾ����
    {0x04000302, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //�Զ�ѭ����ʾʱ��
    {0x04000303, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //��ʾ����С��λ
    {0x04000304, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, // ��ʾ����(�������)С��λ
    {0x04000305, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total     = 0,}}, //����ѭ����ʾ����
    {0x04000306, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {.total     = 0,}}, // �������������
    {0x04000307, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {.total     = 0,}}, //��ѹ���������
    
    {0x04000401, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //ͨ�ŵ�ַ
    {0x04000402, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //���
    
    {0x04000403, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //�ʲ��������(ASCII��)
    {0x04000404, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //���ѹ(ASCII��)
    {0x04000405, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //�����(ASCII��)
    {0x04000406, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //������(ASCII��)
    {0x04000407, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",  {.total      = 0,}}, //�й�׼ȷ�ȵȼ�(ASCII��)
    {0x04000408, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",  {.total      = 0,}}, //�޹�׼ȷ�ȵȼ�(ASCII��)
    
    {0x04000409, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",    {.total      = 0,}}, //����й�����
    {0x0400040A, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",    {.total      = 0,}}, //����޹�����
    
    {0x0400040B, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //����ͺ�(ASCII��)
    {0x0400040C, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //��������(ASCII��)
    {0x0400040D, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //Э��汾��(ASCII��)
    {0x0400040E, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",          {.total      = 0,}}, //�ͻ����

/*
    {0x04000501, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��1
    {0x04000502, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��2
    {0x04000503, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��3
    {0x04000504, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��4
    {0x04000505, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��5
    {0x04000506, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��6
    {0x04000507, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "####|",   {.total      = 0,}}, //�������״̬��7
 
    {0x04000601, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}}, //�й���Ϸ�ʽ������
    {0x04000602, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}}, //�޹���Ϸ�ʽ1������
    {0x04000603, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}}, //�޹���Ϸ�ʽ2������
    
    
    
*/    
   
    {0x04000701, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //Զ���Ⲩ����
    {0x04000702, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //�������Ⲩ����
    {0x04000703, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //ͨ�ſ�1������
    {0x04000704, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //ͨ�ſ�2������
    {0x04000705, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXX##|",   {.total      = 0,}}, //ͨ�ſ�3������
    
    {0x04000801, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //������������
    {0x04000802, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //�����ղ��õ���ʱ�α��
    
    {0x04000901, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //��������ģʽ��
    {0x04000902, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //��ʱ��������ģʽ��
    {0x04000903, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //˲ʱ��������ģʽ��
    {0x04000904, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //Լ����������ģʽ��
    {0x04000905, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //���㶳������ģʽ��
    {0x04000906, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}}, //�ն�������ģʽ��
    
    
   
    {0x04000A01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##:##:##|tm",   {.total      = 0,}}, //�������߼�¼��ʼʱ��
    {0x04000A02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //��1�ฺ�����߼�¼���ʱ��
    {0x04000A03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //��2�ฺ�����߼�¼���ʱ��
    {0x04000A04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //��3�ฺ�����߼�¼���ʱ��
    {0x04000A05, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //��4�ฺ�����߼�¼���ʱ��
    {0x04000A06, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //��5�ฺ�����߼�¼���ʱ��
    {0x04000A07, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}}, //��6�ฺ�����߼�¼���ʱ��
    
    {0x04000B01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|tm",   {.total      = 0,}}, //ÿ�µ�1������
    {0x04000B02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|tm",   {.total      = 0,}}, //ÿ�µ�2������
    {0x04000B03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|tm",   {.total      = 0,}}, //ÿ�µ�3������
 
 /*
    {0x04000D01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A���ѹ����ϵ��
                             .phase     = 1, 
                            .total      = 0,}}, 
    {0x04000D02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A���������ϵ��
                             .phase     = 1, 
                            .total      = 0,}}, 
    {0x04000D03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A���ѹͭ��ϵ��
                             .phase     = 1, 
                            .total      = 0,}}, 
    {0x04000D04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //A�����ͭ��ϵ��
                             .phase     = 1, 
                            .total      = 0,}}, 
                            
    {0x04000D05, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B���ѹ����ϵ��
                             .phase     = 2, 
                            .total      = 0,}}, 
    {0x04000D06, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B���������ϵ��
                             .phase     = 2, 
                            .total      = 0,}}, 
    {0x04000D07, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B���ѹͭ��ϵ��
                             .phase     = 2, 
                            .total      = 0,}}, 
    {0x04000D08, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //B�����ͭ��ϵ��
                             .phase     = 2, 
                            .total      = 0,}},   
    {0x04000D09, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C���ѹ����ϵ��
                             .phase     = 3, 
                            .total      = 0,}}, 
    {0x04000D0A, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C���������ϵ��
                             .phase     = 3, 
                            .total      = 0,}}, 
    {0x04000D0B, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C���ѹͭ��ϵ��
                             .phase     = 3, 
                            .total      = 0,}}, 
    {0x04000D0C, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|",   {       //C�����ͭ��ϵ��
                             .phase     = 3, 
                            .total      = 0,}},                        

*/
    {0x04000E01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",  {.total    = 0,}},  //�����й���������
    {0x04000E02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW", {.total    = 0,}},  //�����й���������		
    {0x04000E03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#0|V",   {.total      = 0,}}, //��ѹ����
    {0x04000E04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#0|V",   {.total      = 0,}}, //��ѹ����
    
    {0x04000F01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //��������1��ֵ
    {0x04000F02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //��������2��ֵ
    {0x04000F03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //�ڻ�������ֵ
    {0x04000F04, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",   {.total      = 0,}}, //͸֧������ֵ
    
    {0x04001001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //�������1��ֵ
    {0x04001002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //�������2��ֵ
    {0x04001003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //͸֧�����ֵ
    {0x04001004, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //�ڻ������ֵ
    {0x04001005, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|yuan",   {.total      = 0,}}, //��բ��������ֵ
    
    {0x04001101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.voltage      = 0,}}, //�������������1
    {0x04001201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|",   {.total      = 0,}}, //���㶳����ʼʱ��
    {0x04001202, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}},  //���㶳��ʱ����
    {0x04001203, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##:##|",   {.total      = 0,}}, //�ն���ʱ��
    
    {0x04001301, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}},  //����ͨ�����߼��ź�ǿ��ָʾ
    
    {0x04001401, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}},  //��բ��ʱʱ�䣨NNNNΪ��բǰ�澯ʱ�䣩
    {0x04001402, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#|",   {.total      = 0,}},  //��բ��ʱʱ�䣨NNNNΪ��բͨ��ǰ�澯ʱ�䣩

    {0x04010000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}},              "|",   {.total      = 0,}},  //��1��ʱ��������
    {0x04010001, {{.GroupFlag=GROUP_DATE,.BytePos=0},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //��1�׵�n��ʱ�α����ݣ�
    
    {0x04020000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}},              "|",   {.total      = 0,}}, //��2��ʱ��������
    {0x04020001, {{.GroupFlag=GROUP_DATE,.BytePos=0},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //��2�׵�n��ʱ�α����ݣ�
    
    {0x04030001, {{.GroupFlag=GROUP_DATE,.BytePos=0},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}},  //��1�����������ڼ���ʱ�α��

    {0x04050101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //��һ�׷��ʵ��1~63
    {0x04050201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //�ڶ��׷��ʵ��1~63
    
    
    {0x04060101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //��һ�׵�1����ֵ
    {0x04060201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //��һ�׽��ݵ��1
    {0x04060101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //�ڶ��׵�1����ֵ
    {0x04060201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_SETTLE,.BytePos=0}}, "|",   {.total      = 0,}},  //�ڶ��׽��ݵ��1
    
    {0x04800001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //��������汾��(ASCII��)
    {0x04800002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //����Ӳ���汾��(ASCII��)
    {0x04800003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",   {.total      = 0,}}, //���ұ��(ASCII��)
    
    {0x04090101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //ʧѹ�¼���ѹ��������
    {0x04090102, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //ʧѹ�¼���ѹ��������
    {0x04090103, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",   {.total      = 0,}}, //ʧѹ�¼�������������
    {0x04090104, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //ʧѹ�¼��ж���ʱʱ��
    
    {0x04090201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //Ƿѹ�¼���ѹ��������
    {0x04090202, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //Ƿѹ�¼��ж���ʱʱ��
    
    {0x04090301, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //��ѹ�¼���ѹ��������
    {0x04090302, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //��ѹ�¼��ж���ʱʱ��
    
    {0x04090401, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //�����¼���ѹ��������
    {0x04090402, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //�����¼���ѹ��������
    {0x04090403, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //�����¼��ж���ʱʱ��
    
    {0x04090501, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",   {.total      = 0,}}, //��ѹ��ƽ������ֵ
    {0x04090502, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //��ѹ��ƽ�����ж���ʱʱ��
    
    
    {0x04090601, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|V",   {.total      = 0,}}, //������ƽ������ֵ
    {0x04090602, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //������ƽ�����ж���ʱʱ��



    {0x04090701, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //ʧ���¼���ѹ��������
    {0x04090702, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",   {.total      = 0,}}, //ʧ���¼���ѹ��������
    {0x04090703, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|A",   {.total      = 0,}}, //ʧ���¼�������������
    {0x04090704, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //ʧ���¼��ж���ʱʱ��

    {0x04090801, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X##.#|A",   {.total      = 0,}}, //�����¼�������������
    {0x04090802, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}},  //�����¼��ж���ʱʱ��

    {0x04090901, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //�����¼���ѹ��������
    {0x04090902, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //�����¼�������������
    {0x04090903, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //�����¼��ж���ʱʱ��
    
    {0x04090A01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",   {.total      = 0,}}, //���������¼��й����ʴ�������
    {0x04090A02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}},  //���������¼��ж���ʱʱ��
    
    {0x04090B01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",   {.total      = 0,}}, //�����¼��й����ʴ�������
    {0x04090B02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}},  //�����¼��ж���ʱʱ��
    
    
    {0x04090C01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //��ѹ��������
    {0x04090C02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#.#|V",   {.total      = 0,}}, //��ѹ��������
    
    
    {0x04090D01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kW",   {.total      = 0,}}, //�й����������¼�������������
    {0x04090D02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.####|kvar",   {.total      = 0,}}, //�޹����������¼�������������
    {0x04090D03, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //���������¼��ж���ʱʱ��
    
    {0x04090E01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.###|",   {.total      = 0,}}, //�ܹ������������޷�ֵ
    {0x04090E02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //�ܹ��������������ж���ʱʱ��
    
    
    {0x04090F01, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#.##|",   {.total      = 0,}}, //�������ز�ƽ����ֵ
    {0x04090F02, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "X#|",      {.total      = 0,}}, //�������ز�ƽ�ⴥ����ʱʱ��
    
    
    {DI_START_VOLT, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XX#|",   {.total      = 0,}}, //�ٽ��ѹ ��
    
    
/*************************************************************�������ݱ�ʶ�����*******************************************************************/ 
/*
    {0x05000001, {{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //��n�ζ�ʱ����ʱ��,YYMMDDhhmm,5�ֽ�
    {0x05010001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //��1�ζ�ʱ����ʱ��,YYMMDDhhmm,5�ֽ�
    {0x05010002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //��2�ζ�ʱ����ʱ��,YYMMDDhhmm,5�ֽ�
    {0x05010003, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //��3�ζ�ʱ����ʱ��,YYMMDDhhmm,5�ֽ�
    {0x05020001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //����ʱ�����л�ʱ��,YYMMDDhhmm,5�ֽ�
    {0x05030001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //��1��������ʱ�α��л�ʱ��,YYMMDDhhmm,5�ֽ�
    {0x05030002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",   {.total      = 0,}}, //��2��������ʱ�α��л�ʱ��,YYMMDDhhmm,5�ֽ�
*/   
 
/*************************************************************��չ���ݱ���**************************************************************************/
  /*
    {PDI_CUR_RATE_SCHEME,        {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //��ǰ��ʱ������
    {PDI_CUR_YEAR_PERIOD,        {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //��ǰ��ʱ����
    {PDI_CUR_DATE_TABLE_SCHEME,  {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //��ǰ��ʱ�α���
    {PDI_CUR_DATE_TABLE,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //��ǰ��ʱ�α��
    {PDI_CUR_DATE_PERIOD,        {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},         //��ǰ��ʱ�κ�
    {PDI_CUR_RATE,               {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "X#|",   {.total      = 0,}},          //��ǰ����
   
    {SDI_MODEWORD_1,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //��չģʽ��1
    {SDI_MODEWORD_2,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //��չģʽ��2
    {SDI_MODEWORD_3,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //��չģʽ��3
    {SDI_MODEWORD_4,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //��չģʽ��4
    {SDI_MODEWORD_5,         {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "BBBBBBBB|",   {.total      = 0,}},         //��չģʽ��5
*/

    {_SDI_ADJ_METER_PARA_STATUS,      {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "##|",   {.total      = 0,}},       //����״̬��������
    {DI_P_U_I_SPEC,      {{.GroupFlag=GROUP_NO,},{.GroupFlag=GROUP_NO}}, "######|",   {.total      = 0,}},               //���峣����񡢵�ѹ��񡢵������




    {PDI_CUR_POS_ACTIVE_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kW",    {.thismonth     = 1,    // ��ǰ�����й�����
                                           .positive  = 1,
                                           .active    = 1, 
                                           .demand    = 1,}},

    {PDI_CUR_NEG_ACTIVE_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kW",    {.thismonth     = 1,    // ��ǰ�����й�����
                                           .negative  = 1,
                                           .active    = 1, 
                                           .demand    = 1,}},
                                           
    {PDI_CUR_COMB1_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //��ǰ����޹�1����
                                           .positive  = 1,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                           
   
    {PDI_CUR_COMB2_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //��ǰ����޹�2����
                                           .negative  = 1,
                                           .reactive  = 1, 
                                           .demand    = 1,}},
   
    {PDI_CUR_QUAD1_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //��ǰ��һ�����޹�����
                                           .quadrant  = 1,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        


    {PDI_CUR_QUAD2_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //��ǰ�ڶ������޹�����
                                           .quadrant  = 2,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        
                                           
    {PDI_CUR_QUAD3_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //��ǰ���������޹�����
                                           .quadrant  = 3,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        
                                                                                      
    {PDI_CUR_QUAD4_REAC_DEMAND, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|kvar",    {.thismonth     = 1,    //��ǰ���������޹�����
                                           .quadrant  = 4,
                                           .reactive  = 1, 
                                           .demand    = 1,}},                                        
                                                                                     
                                           
/*************************************************************��չ���ݱ���:Ԥ����**********************************************************************/
    
   {0x00900100,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //��ǰ��ʣ�����
                                         .thismonth  = 1,
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x00900101,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //��ǰ��͸֧����
                                         .thismonth  = 1,
                                         .energy     = 1,}},
   {0x00900200,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{      //��ǰ��ʣ����
                                         .thismonth  = 1,
                                         .shenyu     = 1,
                                         .jine     = 1,}},
   {0x00900201,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{      //��ǰ��͸֧���
                                         .thismonth  = 1,
                                         .jine     = 1,}},
                                         
   {0x000B0000,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //��ǰ������������й����ۼ��õ���
                                         .thismonth  = 0,}},
                                         
   {0x000B0001,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{      //��1������������й����ۼ��õ���
                                         .thismonth  = 0,}},
                                                                        
   {0x0280000B,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{      //��ǰ���ݵ��
                                         .thismonth  = 1,
                                         .jieti     = 1,
                                         .dianjia   = 1,}},
                                         
                                         
   {0x03320101,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",{      //��1��10�ι�������
                                         .lasttime  = 1}},   
   {0x03320201,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXX#|",{          //��1��10�δι�����ܹ������
                                         .lasttime  = 1}},                                       
   {0x03320301,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��1��10�ι�����
                                         .lasttime      = 1,  
                                         .energy     = 1,}},
   
   {0x03320401,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��1��10�ι���ǰʣ�����
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x03320501,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��1��10�ι����ʣ�����
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x03320601,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��1��10�ι�����ۼƹ�����
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .energy     = 1,}},
                                         
                                         
   {0x03330101,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "##.##.##.##:##|tm",{      //��1��10�ι�������
                                         .lasttime      = 1}},                                          
     
   {0x03330201,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXX#|",{          //��1��10�δι�����ܹ������
                                          .lasttime      = 1,  
                                          .thismonth  = 1}},   
                                         
   {0x03330301,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //��1��10�ι�����
                                         .lasttime      = 1,  
                                         .jine     = 1,}},   
   
   {0x03330401,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //��1��10�ι���ǰʣ����
                                         .lasttime      = 1,  
                                         .shenyu     = 1,
                                         .jine     = 1,}},                                          
   {0x03330501,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //��1��10�ι����ʣ����
                                         .lasttime      = 1,   
                                         .shenyu     = 1,
                                         .energy     = 1,}},
   {0x03330601,{{.GroupFlag=GROUP_TIMES,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //��1��10�ι�����ۼƹ�����
                                         .lasttime      = 1,     
                                         .shenyu     = 1,
                                         .energy     = 1,}},      
                                         
   {0x00900200,{{.GroupFlag=GROUP_NO,.BytePos=0},{.GroupFlag=GROUP_NO}}, "XXXXXXX#.##|yuan",{          //��ǰʣ����
                                         .lasttime      = 1,     
                                         .shenyu     = 1,
                                         .jine     = 1,}},  
                                         
   
   {PDI_CUR_RATE1_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����ʵ��
                                         .thismonth    = 1,  
                                         .tariff       = 1,  
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},  
   {PDI_CUR_RATE2_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����ʵ��
                                         .thismonth    = 1,  
                                         .tariff       = 2,                                          
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},                                       
   {PDI_CUR_RATE3_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰƽ���ʵ��
                                         .thismonth    = 1,  
                                         .tariff       = 3,                                         
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},       
   {PDI_CUR_RATE4_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ�ȷ��ʵ��
                                         .thismonth    = 1,  
                                         .tariff       = 4, 
                                         .feerate      = 1,  
                                         .dianjia     = 1,}},       
                                         
   {PDI_CUR_STEP1_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����1���
                                         .thismonth  = 1,                                    
                                         .jieti      = 1, 
                                         .times      = 1, 
                                         .dianjia     = 1,}},  
   {PDI_CUR_STEP2_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����2���
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 2, 
                                         .dianjia     = 1,}},                                        
   {PDI_CUR_STEP3_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����3���
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 3, 
                                         .dianjia     = 1,}},  
   {PDI_CUR_STEP4_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����4���
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 4, 
                                         .dianjia     = 1,}},
    
   {PDI_CUR_STEP5_FEE,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXX#.####|yuan",{          //��ǰ����5���
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,    
                                         .times      = 5, 
                                         .dianjia     = 1,}},
                                         
   {PDI_CUR_STEP1_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��ǰ����1����
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,  
                                         .times      = 1, 
                                         .energy     = 1,}},  
   {PDI_CUR_STEP2_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��ǰ����2����
                                         .thismonth  = 1,                                    
                                         .jieti      = 1,  
                                         .times      = 2, 
                                         .energy     = 1,}},                                        
   {PDI_CUR_STEP3_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��ǰ����3����
                                         .thismonth  = 1,       
                                         .jieti      = 1,   
                                         .times      = 3, 
                                         .energy     = 1,}},  
   {PDI_CUR_STEP4_ENG,{{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#.##|kWh",{          //��ǰ����4����
                                         .thismonth  = 1,       
                                         .jieti      = 1,   
                                         .times      = 4, 
                                         .energy     = 1,}},                                      
                                         
                                         
 //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------- �¼���¼��ʧѹ���ݿ�-----------------------------------------------------------
    
    
    {0x10000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ��ʧѹ�ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x10000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ��ʧѹ���ۼ�ʱ��
                                           .total     = 0,}},    
                 
    {0x10000101, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",      {    //���1��ʧѹ����ʱ��
                                           .total     = 0,}},
    {0x10000201, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "|",      {    //���1��ʧѹ����ʱ��
                                           .total     = 0,}},                                            
  
    {0x10000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��ʧѹ����ʱ��
                                           .lasttime     = 1}}, 
    {0x10000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A��ʧѹ����ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},
    {0x10000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},

/*
    {0x10000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x10000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x10000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x10000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x10000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��ʧѹ����ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x10000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��ʧѹ����ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x10000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��ʧѹ����ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x10000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x10000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��ʧѹ����ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x10000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x10001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x10001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��ʧѹ����ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x10001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��ʧѹ����ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x10001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��ʧѹ����ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x10001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x10001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��ʧѹ����ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x10001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x10001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x10001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x10001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��ʧѹ����ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x10001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��ʧѹ����ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x10001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��ʧѹ����ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x10001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x10002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��ʧѹ����ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x10002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��ʧѹ�ڼ��ܰ�ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x10002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��ʧѹ�ڼ�A�లʱ��
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x10002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��ʧѹ�ڼ�B�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x10002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��ʧѹ�ڼ�C�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
*/    
    {0x10002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��ʧѹ����ʱ��
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                        
    {0x10002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x10002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},  
/*
    {0x10002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x10002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹ����ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x10002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x10002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x10002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x10002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x10002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x10002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x10003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x10003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧѹ����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x10003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧѹʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
                                   
//----------------------------------------------------------- �¼���¼��Ƿѹ���ݿ�-----------------------------------------------------------
                                          
    {0x11000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C��Ƿѹ�ܴ���
                                          .total     = 0,}},
                                          
    {0x11000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C��Ƿѹ���ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x11000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��Ƿѹ����ʱ��
                                           .lasttime     = 1}}, 
    {0x11000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A��Ƿѹ����ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                        
    {0x11000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x11000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x11000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x11000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x11000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x11000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x11000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x11000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x11000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x11000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x11001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x11001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x11001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x11001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x11001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x11001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x11001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x11001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x11001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x11001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x11001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x11001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x11001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x11002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x11002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��Ƿѹ�ڼ��ܰ�ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x11002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��Ƿѹ�ڼ�A�లʱ��
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x11002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��Ƿѹ�ڼ�B�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x11002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C��Ƿѹ�ڼ�C�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
    {0x11002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��Ƿѹ����ʱ��
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                           
    {0x11002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ�������й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x11002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ�̷����й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x11002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x11002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹ����ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x11002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x11002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x11002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x11002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x11002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x11002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x11003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x11003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��Ƿѹ����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x11003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��Ƿѹʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
                                          
//----------------------------------------------------------- �¼���¼����ѹ���ݿ�-----------------------------------------------------------
                                          
    {0x12000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C���ѹ�ܴ���
                                          .total     = 0,}},
                                          
    {0x12000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C���ѹ���ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x12000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C���ѹ����ʱ��
                                           .lasttime     = 1}}, 
    {0x12000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A���ѹ����ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x12000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x12000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x12000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���ѹ����ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x12000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���ѹ����ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x12000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���ѹ����ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x12000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x12000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���ѹ����ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x12000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x12001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���ѹ����ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x12001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���ѹ����ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x12001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���ѹ����ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x12001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x12001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���ѹ����ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x12001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x12001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x12001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x12001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���ѹ����ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x12001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���ѹ����ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x12001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���ѹ����ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x12001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x12002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���ѹ����ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x12002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C���ѹ�ڼ��ܰ�ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x12002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C���ѹ�ڼ�A�లʱ��
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x12002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C���ѹ�ڼ�B�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x12002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C���ѹ�ڼ�C�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
    {0x12002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C���ѹ����ʱ��
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                           
    {0x12002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ�������й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x12002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ�̷����й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x12002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x12002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹ����ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x12002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x12002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x12002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x12002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x12002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x12002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x12003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x12003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���ѹ����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x12003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���ѹʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
                                       
 //----------------------------------------------------------- �¼���¼���������ݿ�-----------------------------------------------------------
                                          
    {0x13000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C������ܴ���
                                          .total     = 0,}},
                                          
    {0x13000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//A/B/C��������ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x13000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C����෢��ʱ��
                                           .lasttime     = 1}}, 
    {0x13000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A����෢��ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x13000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x13000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x13000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C����෢��ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x13000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C����෢��ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x13000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C����෢��ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x13000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x13000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C����෢��ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x13000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x13001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C����෢��ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x13001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C����෢��ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x13001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C����෢��ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x13001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C����෢��ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x13001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C����෢��ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x13001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C����෢��ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x13001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x13001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C����෢��ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x13001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C����෢��ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x13001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C����෢��ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x13001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C����෢��ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x13001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C����෢��ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x13002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C����෢��ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
                                           
    {0x12002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C���ѹ�ڼ��ܰ�ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x13002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C������ڼ�A�లʱ��
                                           .lasttime     = 1,
                                           .total     = 1   }},
    {0x13002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C������ڼ�B�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 1   }},                                
    {0x13002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|Ah",  {//��1��10�� A/B/C������ڼ�C�లʱ��
                                           .lasttime     = 1,
                                           .phase     = 2   }},                             
    {0x13002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��������ʱ��
                                           .lasttime     = 1,
                                           .phase     = 3   }},
                                           
    {0x13002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ�������й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x13002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ�̷����й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x13002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��������ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x13002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��������ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x13002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x13002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x13002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x13002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x13002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x13002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x13003200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x13003300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x13003500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                          
  //----------------------------------------------------------- �¼���¼����ѹ������-----------------------------------------------------------
                                          
    {0x14000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//��ѹ�������ܴ���
                                          .total     = 0,}},
                                          
    {0x14000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//��ѹ���������ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x14000100, {{.GroupFlag=GROUP_NO,.BytePos=0},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ��ѹ��������ʱ��
                                           .lasttime     = 1}}, 
    {0x14000200, {{.GroupFlag=GROUP_NO,.BytePos=0},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ�������й��ܵ���
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ�̷����й��ܵ���
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x14000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x14000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x14000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
   {0x14000A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14000C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x14000E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14000F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14001000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x14001200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ��ѹ���������ʱ��
                                           .lasttime     = 1}}, 
    {0x14001300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x14001500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x14001600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x14001700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14001900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x14001B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14001D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14001E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x14001F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14002000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ���������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x14002100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x14002200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ���������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                    
    //-----------------------------------------------------------  �¼���¼������������----------------------------------------------------------- 
                                          
    {0x15000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�����������ܴ���
                                          .total     = 0,}},
                                          
    {0x15000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�������������ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x15000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ������������ʱ��
                                           .lasttime     = 1}}, 
    {0x15000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x15000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x15000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x15000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x15000A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15000C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x15000E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15000F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15001000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x15001200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� �������������ʱ��
                                           .lasttime     = 1}}, 
    {0x15001300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x15001500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x15001600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x15001700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15001900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
   {0x15001B00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001C00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15001D00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15001E00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x15001F00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15002000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �������������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x15002100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x15002200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �������������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
   //-----------------------------------------------------------  �¼���¼����ѹ��ƽ��----------------------------------------------------------- 
                                          
    {0x16000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//��ѹ��ƽ���ܴ���
                                          .total     = 0,}},
                                          
    {0x16000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//��ѹ��ƽ�����ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x16000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��
                                           .lasttime     = 1}}, 
    {0x16000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x16000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x16000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x16000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�ⷢ��ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x16001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.##",  {//��1��10�� ��ѹ��ƽ�����ƽ����
                                           .lasttime     = 1}}, 
    
    {0x16001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ��ѹ��ƽ�����ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x16001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x16001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x16001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x16001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x16002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��ѹ��ƽ�����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x16002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x16002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��ѹ��ƽ�����ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},


//-----------------------------------------------------------  �¼���¼��������ƽ��----------------------------------------------------------- 
                                          
    {0x17000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//������ƽ���ܴ���
                                          .total     = 0,}},
                                          
    {0x17000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//������ƽ�����ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x17000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ������ƽ�ⷢ��ʱ��
                                           .lasttime     = 1}}, 
    {0x17000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x17000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x17000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x17000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
   {0x17000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x17000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�ⷢ��ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�ⷢ��ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x17001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.##",  {//��1��10�� ������ƽ�����ƽ����
                                           .lasttime     = 1}}, 
    
    {0x17001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ������ƽ�����ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x17001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x17001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x17001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x17001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x17001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x17002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ������ƽ�����ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x17002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x17002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ������ƽ�����ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},



  //----------------------------------------------------------- �¼���¼��ʧ�����ݿ�-----------------------------------------------------------
    {0x18000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ��ʧ���ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x18000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ��ʧ�����ۼ�ʱ��
                                           .total     = 0,}},    
                 
                                          
     
    {0x18000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��ʧ������ʱ��
                                           .lasttime     = 1}}, 
    {0x18000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A��ʧ������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x18000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x18000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x18000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��ʧ������ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x18000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��ʧ������ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x18000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��ʧ������ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x18000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x18000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��ʧ������ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x18000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x18001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��ʧ������ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x18001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��ʧ������ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x18001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��ʧ������ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x18001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x18001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��ʧ������ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x18001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x18001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x18001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x18001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C��ʧ������ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x18001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C��ʧ������ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x18001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C��ʧ������ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x18001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x18002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C��ʧ������ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
    
    {0x18002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C��ʧ������ʱ��
                                           .lasttime     = 1}}, 
                                                                                  
                                           
    {0x18002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ�������й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x18002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ�̷����й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x18002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x18002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ������ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x18002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x18002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ��ʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ��ʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x18002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x18002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ��ʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x18002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ��ʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x18002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x18002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��ʧ������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x18003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ��ʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x18003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C��ʧ��ʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    
  //----------------------------------------------------------- �¼���¼���������ݿ�-----------------------------------------------------------
    {0x19000001, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ������ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x19000002, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ��������ۼ�ʱ��
                                           .total     = 0,}},    
                 
                                          
     
    {0x19000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C���������ʱ��
                                           .lasttime     = 1}}, 
    {0x19000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A���������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x19000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x19000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x19000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���������ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x19000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���������ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x19000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���������ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x19000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x19000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���������ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x19000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x19001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���������ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x19001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���������ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x19001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���������ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x19001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x19001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���������ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x19001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x19001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x19001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x19001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���������ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x19001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���������ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x19001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���������ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x19001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x19002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���������ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
    
    {0x19002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C���������ʱ��
                                           .lasttime     = 1}}, 
                                                                                  
                                           
    {0x19002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ�������й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x19002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ�̷����й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x19002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x19002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x19002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x19002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x19002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x19002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x19002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x19002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x19002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x19003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x19003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                        
                                          
                                          
    
  //----------------------------------------------------------- �¼���¼���������ݿ�-----------------------------------------------------------
    {0x1A000101, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ������ܴ��������ۼ�ʱ��
                                           .total     = 0,}},
    {0x1A000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_NO}}, "XXXXX#|",      {    //��/A/B/C ��������ۼ�ʱ��
                                           .total     = 0,}},    
                 
                                          
     
    {0x1A000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C���������ʱ��
                                           .lasttime     = 1}}, 
    {0x1A000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C��A���������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1A000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1A000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1A000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���������ʱ��A���ѹ
                                          .lasttime     = 1,
                                          .phase     = 1, 
                                          .voltage   = 1,}},
                                           
    {0x1A000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���������ʱ��A�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x1A000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���������ʱ��A���й�����
                                           .lasttime     = 1,
                                            .phase    = 1, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x1A000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ��A���޹�����
                                           .lasttime     = 1,
                                           .phase     = 1,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x1A000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���������ʱ��A�๦������
                                           .lasttime     = 1,
                                           .phase     = 1, 
                                           .factor    = 1,}},
                                           
    {0x1A000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1A001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���������ʱ��B���ѹ
                                          .lasttime     = 1,
                                          .phase     = 2, 
                                          .voltage   = 1,}},
                                           
    {0x1A001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���������ʱ��B�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x1A001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���������ʱ��B���й�����
                                           .lasttime     = 1,
                                            .phase    = 2, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x1A001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ��B���޹�����
                                           .lasttime     = 1,
                                           .phase     = 2,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x1A001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���������ʱ��B�๦������
                                           .lasttime     = 1,
                                           .phase     = 2, 
                                           .factor    = 1,}},
                                           
                                           
    {0x1A001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1A001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1A001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� A/B/C���������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1A001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XX#.##|V",  {//��1��10�� A/B/C���������ʱ��C���ѹ
                                          .lasttime     = 1,
                                          .phase     = 3, 
                                          .voltage   = 1,}},
                                           
    {0x1A001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|A",  {//��1��10�� A/B/C���������ʱ��C�����
                                           .lasttime     = 1,
                                           .current   = 1,}},
                                           
    {0x1A001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kW",  {//��1��10�� A/B/C���������ʱ��C���й�����
                                           .lasttime     = 1,
                                            .phase    = 3, 
                                           .active    = 1,
                                           .power     = 1,}},
                                      
    {0x1A001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ��C���޹�����
                                           .lasttime     = 1,
                                           .phase     = 3,   
                                           .reactive  = 1,
                                           .power     = 1,}},
                                           
    {0x1A002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "X#.###|",  {//��1��10�� A/B/C���������ʱ��C�๦������
                                           .lasttime     = 1,
                                           .phase     = 3, 
                                           .factor    = 1,}},
    
    {0x1A002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� A/B/C���������ʱ��
                                           .lasttime     = 1}}, 
                                                                                  
                                           
    {0x1A002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ�������й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                  
    {0x1A002300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ�̷����й��ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},                                         
    {0x1A002400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�1�ܵ���
                                          .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                     
    {0x1A002500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C���������ʱ������޹�2�ܵ���
                                           .total     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},   
                                          
    {0x1A002600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x1A002700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��A������޹�1����
                                           .phase     = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��A������޹�2����
                                           .phase    = 1, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
                                          
    {0x1A002A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x1A002B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��B������޹�1����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A002D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��B������޹�2����
                                           .phase    = 2, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},  
    {0x1A002E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},        
                                          
    {0x1A002F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� A/B/C���������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .active    = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A003000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��C������޹�1����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},     
                                          
    {0x1A003100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXX#.####|kvarh",  {//��1��10�� A/B/C�����ʱ��C������޹�2����
                                           .phase    = 3, 
                                          .lasttime     = 1,
                                          .reactive  = 1,
                                          .energy    = 1,}},                                        
                                          
                                          
   //----------------------------------------------------------- �¼���¼����������-----------------------------------------------------------
                                          
    {0x1B000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//���������ܴ���
                                          .total     = 0,}},
                                          
    {0x1B000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�����������ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x1B000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ����������ʱ��
                                           .lasttime     = 1}}, 
    {0x1B000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1B000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1B000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1B000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ����������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ����������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x1B001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� �����������ʱ��
                                           .lasttime     = 1}}, 
    {0x1B001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1B001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1B001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1B001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1B001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �����������ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1B002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1B002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �����������ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
   //----------------------------------------------------------- �¼���¼������-----------------------------------------------------------
                                          
    {0x1C000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�����ܴ���
                                          .total     = 0,}},
                                          
    {0x1C000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�������ۼ�ʱ��
                                          .total     = 0,}},                                         
   
   
   
    {0x1C000100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ���ط���ʱ��
                                           .lasttime     = 1}}, 
    {0x1C000200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C000400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1C000500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1C000600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C000800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C000A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C000C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1C000E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C000F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ط���ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C001000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ط���ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
                                          
                                          
    {0x1C001200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ���ؽ���ʱ��
                                           .lasttime     = 1}}, 
    {0x1C001300, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ�������й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001400, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ�̷����й��ܵ���
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C001500, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ������޹�1�ܵ���
                                           .lasttime    = 1,
                                           .phase     = 1,}},                                       
    {0x1C001600, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ������޹�2�ܵ���
                                          .lasttime     = 1,
                                          .total     = 0}},                                       
       
    {0x1C001700, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ��A�������й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001800, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ��A�෴���й�����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C001900, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ��A������޹�1����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001A00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ��A������޹�2����
                                          .phase     = 1, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1C001B00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ��B�������й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001C00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ��B�෴���й�����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C001D00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ��B������޹�1����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C001E00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ��B������޹�2����
                                          .phase     = 2, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                           
    {0x1C001F00, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ��C�������й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C002000, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ���ؽ���ʱ��C�෴���й�����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},

    {0x1C002100, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ��C������޹�1����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1C002200, {{.GroupFlag=GROUP_PHASE,.BytePos=2},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ���ؽ���ʱ��C������޹�2����
                                          .phase     = 3, 
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},                                       
                                          
                                          
                                          
                                          
   //----------------------------------------------------------- �¼���¼����բ-----------------------------------------------------------
                                          
    {0x1D000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//��բ�ܴ���
                                          .total     = 0,}},
                                          
       
    {0x1D000100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ��բ����ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x1D000200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "########|",  {//��1��10�� ��բ����ʱ�����ߴ���
                                           .lasttime     = 1}},   
                                                                               
    {0x1D000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��բ����ʱ�������й��ܵ���
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1D000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��բ����ʱ�̷����й��ܵ���
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1D000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�1�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1D000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�2�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 2,}}, 
                                                                             
       
    {0x1D000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�3�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 3,}}, 
                                           
    {0x1D000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�4�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 1,}},                                         
   
   //----------------------------------------------------------- �¼���¼����բ-----------------------------------------------------------
                                          
    {0x1E000001, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//��բ�ܴ���
                                          .total     = 0,}},
                                          
       
    {0x1E000100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� ��բ����ʱ��
                                           .lasttime     = 1}}, 
                                           
    {0x1E000200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "########|",  {//��1��10�� ��բ����ʱ�����ߴ���
                                           .lasttime     = 1}},   
                                                                               
    {0x1E000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��բ����ʱ�������й��ܵ���
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1E000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� ��բ����ʱ�̷����й��ܵ���
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1E000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�1�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1E000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�2�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 2,}}, 
                                                                             
       
    {0x1E000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�3�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 3,}}, 
                                           
    {0x1E000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� ��բ����ʱ�̵�4�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                           
   //----------------------------------------------------------- �¼���¼���ܹ�������������-----------------------------------------------------------
                                          
    {0x1F000000, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�ܹ��������������ܴ���
                                          .total     = 0,}},
                                          
    {0x1F000002, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_NO}}, "XXXXX#|",  {//�ܹ����������������ۼ�ʱ��
                                          .total     = 0,}},
                                          
    {0x1F000100, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� �ܹ������������޷���ʱ��
                                           .lasttime     = 1}}, 
                                           
                                                                               
    {0x1F000200, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �ܹ������������޷���ʱ�������й��ܵ���
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1F000300, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �ܹ������������޷���ʱ�̷����й��ܵ���
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1F000400, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �ܹ������������޷���ʱ�̵�1�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1F000500, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �ܹ������������޷���ʱ�̵�2�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 2,}}, 
    
    {0x1F000600, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "##.##.##.##:##|",  {//��1��10�� �ܹ������������޽���ʱ��
                                           .lasttime     = 1}}, 
                                           
       
    {0x1F000700, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �ܹ������������޽���ʱ�������й��ܵ���
                                          .lasttime     = 1,
                                          .positive  = 1,
                                          .energy    = 1,}},
    {0x1F000800, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kWh",  {//��1��10�� �ܹ������������޽���ʱ�̷����й��ܵ���
                                          .lasttime     = 1,
                                          .negative  = 1,
                                          .energy    = 1,}},
                                          
    {0x1F000900, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �ܹ������������޽���ʱ�̵�1�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 1,}},  
                                                                                
    {0x1F000A00, {{.GroupFlag=GROUP_NO},{.GroupFlag=GROUP_TIMES,.BytePos=0}}, "XXXXX#.##|kvarh",  {//��1��10�� �ܹ������������޽���ʱ�̵�2�����޹���
                                           .lasttime    = 1,
                                           .quadrant = 2,}},   

   */
};

#endif
