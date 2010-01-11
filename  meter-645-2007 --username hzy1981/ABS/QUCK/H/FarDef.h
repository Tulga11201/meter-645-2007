
#ifndef FAR_DEF_H_
#define FAR_DEF_H_

#undef EXT
#ifdef FAR_DEAL_CTRL_0X33_C_
#define EXT
#else
#define EXT extern
#endif 
//-----------------------------------------------------------------------------
  INT8U Far_Deal_070000FF(INT8U * Data_Point );
  INT8U Far_Deal_Order_0x03(INT8U * Data_Point ,INT8U Source_Length);
struct Far_Read_070000FF_Format_In
	{
	INT8U cryptograph1[8];								/*"密文1"*/
	INT8U	random_number1[8];							/*"随机数1"*/
	INT8U disperse_gene[8];								/*"分散因子"*/
	};
#define LENGTH_FAR_READ_070000FF_FORMAT_IN  sizeof( struct Far_Read_070000FF_Format_In )
//-----------------------------------------------------------------------------
struct Far_Read_070000FF_Format_Out
	{
	INT8U	random_number2[4];							/*"随机数2"*/
	INT8U	esam_serial_number[8];						/*"ESAM序列号"*/	
	};
#define LENGTH_FAR_READ_070000FF_FORMAT_OUT  sizeof( struct Far_Read_070000FF_Format_Out )

typedef void (* Event_Spec_Deal)(INT8U *);
typedef INT8U  (* Event_Spec_Deal_R)(INT8U *);
struct Far_645_Frame_0x03
	{
	INT8U Data_ID[4];
//	INT8U PassWord[4];
	INT8U Do_man[4];
	};
#define LENGTH_FAR_645_FRAME_0X03      sizeof(struct Far_645_Frame_0x03)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Far_645_Frame_Flag_0x03
	{
	INT8U Data_ID[4];
	INT8U Source_Length;				/*" =数据长度+4(ID)+4(操作者代码) "*/
	Event_Spec_Deal_R Far_645_Order_0x03;    /*" 事件处理函数 "*/
	};
#define LENGTH_FAR_645_FRAME_FLAG_0X03   sizeof(struct Far_645_Frame_Flag_0x03)
//-----------------------------------------------------------------------------
#define LENGTH_FAR_645_FRAME_FLAG_LIST_0X03     sizeof(Far_645_Frame_Flag_0x03_List)
 


#endif