#define TEST_DATA_TRANS_C
#include "includes.h"

INT8U Test_Buf[500];
/*
//�����ṹ��
typedef struct 
{
	//INT8U Time[5];//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��
	S_HEX_Time Time;//����ʱ���,��ʱ���ڶ���ʱ����Ϊ����ʱ��

	INT32U  Pos_Active[MAX_RATES+1];//���Լ��ַ��������й�,��λС��,��λKWh����ͬ
	INT32U  Neg_Active[MAX_RATES+1];//���Լ��ַ��ʷ����й�

	INT32U  Quad_Reactive[4][MAX_RATES+1];//�����޷ַ����޹�

	INT32U  Phase_Pos_Active[3];//���������й�
	INT32U  Phase_Neg_Active[3];//���෴���й�

	INT32U Phase_Quad_Reactive[3][4];//�����������޹�

	INT32U  Phase_AH[3];//������AH

	INT32U  CopperLoss[4];//��ABCͭ��
	INT32U  IronLoss[4];  //��ABC����
	INT32U  TransErr[4];  //��ABC���������

	//INT32U  Phase_Reactive[3][4];//������������޹�

	INT8U   CS[CS_BYTES];//����Ĳ���Ҫ���浽Flash��

	//���²����Ǹ�������������ã�����Ҫ���浽Flash��EERom��
	//INT32U Pos_Reactive[MAX_RATES+1];//���Լ��ַ��������޹�
	//INT32U Neg_Reactive[MAX_RATES+1];

}S_Energy;
*/

/*
#pragma optimize=none
INT8U Test_Get_DLT645_Data()
{
	INT32U i;
	INT16U Len;
	INT8U Re;

	for(i = 0; i < MAX_RATES; i ++)
	{
		Cur_Energy.Pos_Active[i] = i*111111;
		Cur_Energy.Neg_Active[i] = i*11111;

		Cur_Energy.Quad_Reactive[0][i] = i*1;
		Cur_Energy.Quad_Reactive[1][i] = i*11;
		Cur_Energy.Quad_Reactive[2][i] = i*111;
		Cur_Energy.Quad_Reactive[3][i] = i*1111;
	}

	for(i = 0; i < 3; i ++)
	{
		Cur_Energy.Phase_Pos_Active[i] = i*111111;
		Cur_Energy.Phase_Neg_Active[i] = i*11111;
		
		Cur_Energy.Phase_Quad_Reactive[i][0] = i*1;
		Cur_Energy.Phase_Quad_Reactive[i][1] = i*11;
		Cur_Energy.Phase_Quad_Reactive[i][2] = i*111;
		Cur_Energy.Phase_Quad_Reactive[i][3] = i*1111;
	}

	Energy_Comb_Word.Active = 0xFF;
	Energy_Comb_Word.Reactive[0] = 0xFF;
	Energy_Comb_Word.Reactive[1] = 0xFF;

	Multi_Rate_Para.Rates = 4;
	Re = 1;
	//����й��ܷ���1
	Len = Get_DLT645_Data(0x0000FF00, Test_Buf, Test_Buf, sizeof(Test_Buf));
	//Re &= ASSERT(Test_Buf[0] EQ 0x22 && Test_Buf[1] EQ 0x22 && Test_Buf[2] EQ 0x01 && Test_Buf[3] EQ 0);
    //����޹�1����2
	Len = Get_DLT645_Data(0x00030200, Test_Buf, Test_Buf, sizeof(Test_Buf));
	ASSERT(Test_Buf[0] EQ 0x22 && Test_Buf[1] EQ 0x22 && Test_Buf[2] EQ 0x01 && Test_Buf[3] EQ 0);
	//����޹�2����5
	Len = Get_DLT645_Data(0x00040500, Test_Buf, Test_Buf, sizeof(Test_Buf));
	//Re &= ASSERT(Test_Buf[0] EQ 0x22 && Test_Buf[1] EQ 0x22 && Test_Buf[2] EQ 0x01 && Test_Buf[3] EQ 0);

	//�����й��ܷ���1
	Len = Get_DLT645_Data(0x00010100, Test_Buf, Test_Buf, sizeof(Test_Buf));
	//Re &= ASSERT(Test_Buf[0] EQ 0x11 && Test_Buf[1] EQ 0x11 && Test_Buf[2] EQ 0x01 && Test_Buf[3] EQ 0);
	//�����й��ܷ���2
	Len = Get_DLT645_Data(0x00020200, Test_Buf, Test_Buf, sizeof(Test_Buf));
	//Re &= ASSERT(Test_Buf[0] EQ 0x22 && Test_Buf[1] EQ 0x22 && Test_Buf[2] EQ 0x00 && Test_Buf[3] EQ 0);

	return 1;
}
*/