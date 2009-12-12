
#ifndef FAR_DEF_H_
#define FAR_DEF_H_

#undef EXT
#ifdef FAR_DEAL_CTRL_0X33_C_
#define EXT
#else
#define EXT extern
#endif 
//-----------------------------------------------------------------------------
  unsigned char Far_Deal_070000FF(unsigned char * Data_Point );
  unsigned char Far_Deal_Order_0x03(unsigned char * Data_Point ,unsigned char Source_Length);
struct Far_Read_070000FF_Format_In
	{
	unsigned char cryptograph1[8];								/*"����1"*/
	unsigned char	random_number1[8];							/*"�����1"*/
	unsigned char disperse_gene[8];								/*"��ɢ����"*/
	};
#define LENGTH_FAR_READ_070000FF_FORMAT_IN  sizeof( struct Far_Read_070000FF_Format_In )
//-----------------------------------------------------------------------------
struct Far_Read_070000FF_Format_Out
	{
	unsigned char	random_number2[4];							/*"�����2"*/
	unsigned char	esam_serial_number[8];						/*"ESAM���к�"*/	
	};
#define LENGTH_FAR_READ_070000FF_FORMAT_OUT  sizeof( struct Far_Read_070000FF_Format_Out )

typedef void (* Event_Spec_Deal)(unsigned char *);
typedef unsigned char  (* Event_Spec_Deal_R)(unsigned char *);
struct Far_645_Frame_0x03
	{
	unsigned char Data_ID[4];
//	unsigned char PassWord[4];
	unsigned char Do_man[4];
	};
#define LENGTH_FAR_645_FRAME_0X03      sizeof(struct Far_645_Frame_0x03)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Far_645_Frame_Flag_0x03
	{
	unsigned char Data_ID[4];
	unsigned char Source_Length;				/*" =���ݳ���+4(ID)+4(�����ߴ���) "*/
	Event_Spec_Deal_R Far_645_Order_0x03;    /*" �¼������� "*/
	};
#define LENGTH_FAR_645_FRAME_FLAG_0X03   sizeof(struct Far_645_Frame_Flag_0x03)
//-----------------------------------------------------------------------------
#define LENGTH_FAR_645_FRAME_FLAG_LIST_0X03     sizeof(Far_645_Frame_Flag_0x03_List)
 


#endif