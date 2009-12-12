#ifndef AUTHORITY_H
#define AUTHORITY_H

#undef EXT
#ifdef AUTHORITY_C
#define EXT 
#else
#define EXT extern 
#endif

#define MAX_AUTHU_ERR_COUNTS 3   //�������������
#define AUTHU_ERR_LOCK_MINS 1440 //�����������ʱ��
#define SET_EN_MINS    0       //������ȷʹ��дʱ��

#define C_REMOTE_AUTH 0x03 //Զ����֤
#define C_ADJUST_TIME      0x08//001000//�㲥Уʱ
#define C_READ_DATA    0x11//0lO001//������
#define C_READ_FOLLOW_DATA 0x12//10010//����������
#define C_READ_ADDR    0x13//100l1//��ͨ�ŵ�ַ
#define C_SET_DATA     0x14//10100//д����
#define C_SET_ADDR     0x15//10101//дͨ�ŵ�ַ
#define C_FREEZE_DATA      0x16//10110//��������
#define C_SET_COM_BAUD     0x17//10111//����ͨ������
#define C_SET_PSW      0x18//11000//�޸�����
#define C_CLR_DEMAND   0x19//11001//�����������
#define C_CLR_ALL      0x1A//11010//�������
#define C_CLR_EVENT    0x1B//110ll//�¼�����
#define C_CTRL         0x1C //��������
#define C_PORT         0x1D //�๦�ܶ������

//���ݵ������־
#define PSW_NULL  0xFF//û����������,����ֻ��
#define PSW_FACTORY 0//���������������ϲ������õĲ���
#define PSW_0 1  //0������
#define PSW_1 2  //1������
#define PSW_2 3  //2������
#define PSW_3 4  //3�����룬Э������δ��
#define PSW_4 5
#define PSW_5 6
#define PSW_6 7
#define PSW_7 8
#define PSW_8 9
#define PSW_9 10
#define PSW_10 11


//����������Ҫ����һ�������е����ݷ���
#define PSW_NULL_FLAG 0xFF

#define PSW_FAC_PARA  0   //��������
#define PSW_RD_ONLY   1   //ֻ��������û��дȨ��
#define PSW_SET_PSW0  2   //0������Ȩ��
#define PSW_SET_PSW1  3   //1������Ȩ��
#define PSW_SET_PSW2  4   //2������Ȩ��
#define PSW_SET_PSW3  5   //3������Ȩ��
#define PSW_SET_PSW4  6   //4������Ȩ��
#define PSW_SET_PSW5  7   //5������Ȩ��
#define PSW_SET_PSW6  8   //6������Ȩ��
#define PSW_SET_PSW7  9   //7������Ȩ��
#define PSW_SET_PSW8  10   //8������Ȩ��
#define PSW_SET_PSW9  11   //9������Ȩ��

#define PSW_ADJ_TIME  12   //�㲥Уʱ
#define PSW_SET_DATE  13   //��������
#define PSW_SET_TIME  14   //����ʱ��
#define PSW_CLR_ALL   15   //��������,���ǵ����0
#define PSW_CLR_DATA  16   //�����������̡���ѹ�ϸ���
#define PSW_SET_ENSTART 17   //���õ׶���
#define PSW_SET_PARA    18   //������ͨ����(��������)

//�û�Ȩ�ޱ�־��
typedef struct
{
    INT8U Head;
    INT32U Flag; 
    INT8U CS[CS_BYTES];
    INT8U Tail;
}S_User_Authority_Flag;

//�û�Ȩ�޿�����
typedef struct
{
    INT16U PSW[3];
    INT8U CS[CS_BYTES];//У���  
}S_User_Authority_Ctrl;//�û�Ȩ�޿�����

//��������Flag�����û�Ȩ�޿������е�λ�õ�ӳ���

typedef struct 
{
	INT8U PSW_Flag;  //���ݵ������־
	INT8U PSW_Level; //���ݵ�����ȼ�
}S_PSW_Map;

//��������Ȩ��״̬
typedef struct
{
    INT8U Head;
    INT8U PSW[10][3];//��ǰ��10�����룬ÿ������3���ֽ�
    INT8U CS[CS_BYTES];//У���
    INT8U Tail;
}S_PSW_Status;

typedef struct
{
  INT8U Set_En_Mins;
  INT8U CS[CS_BYTES];  
}S_Module_Set_Meter_Status;

EXT volatile S_User_Authority_Ctrl User_Authority_Ctrl;//�û�Ȩ�޿�����
EXT volatile S_PSW_Status Cur_PSW;
EXT volatile S_Module_Set_Meter_Status Module_Set_Meter_Status;
EXT volatile S_User_Authority_Flag User_Authority_Flag;

EXT INT8U Get_PSW_Flag_Map_Level(INT8U PSW_Flag);
EXT INT8U Check_Debug_En();
EXT INT8U Check_Set_ADDR_Key();
EXT INT8U Check_Clear_Data_Authority();
EXT INT8U Check_Meter_Factory_Status();
EXT INT8U Check_Meter_Prog_Status();
EXT INT8U Get_User_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen);
EXT INT8U Get_P_Data_Info_Authority(INT8U Ch, INT8U Ctrl_Code, INT8U* pSrc, INT8U SrcLen);
EXT void Clear_PSW_Err_Info();
EXT INT8U Check_PSW_Lock();
EXT void PSW_Lock_Proc();
EXT void PSW_Timer_Proc();
EXT INT8U Check_User_Authurity(INT8U User_PSW, INT8U Data_PSW);
EXT void Set_Authority_Flag();
EXT void Clear_Authority_Flag();
EXT INT8U Check_Data_Type(PROTO_DI PDI);
#endif
