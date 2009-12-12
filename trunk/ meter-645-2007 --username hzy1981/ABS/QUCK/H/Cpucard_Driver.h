
/*"**********************************************************************************"*/
/*" I/O��Ԥ���壬��ͬ��MCU���ܲ�һ�� "*/
#ifndef CPUCARD_DRIVER_H__
#define CPUCARD_DRIVER_H__

#undef EXT
#ifdef CPUCARD_DRIVER_C_
#define EXT   
#else
#define EXT extern   
#endif


/*"**********************************************************************************"*/
/*" Ԥ���嶨��,�й���CPU�ײ�����Ĵ��� "*/
//#define CARD_BUFFER_LENGTH 1
#define FAR_COMM         PAY_FAR          
#define CPU              PAY_CPU_CARD
#define ESAM             PAY_ESAM
//define ZB_COMM          3

#define ERR              0xFF
#define OK               0x00

#define RESET_RECEIVE_DATA_LENGTH    11
#define ESAM_BUFFER_FILE_LENGTH      0x30       /*" ֻ����ESAM��д�ļ���0x30���ֽ� "*/
#define ESAM_TEMP_FILE_LENGTH        0x41
 
/*"**********************************************************************************"*/
/*" CPU��״̬�ֶ��� "*/
#define Read_Binary      0xb0    /*"��CPU�����������ļ�"*/ 
#define Read_Record      0xb2    /*"��CPU������¼�ļ�"*/                  
#define Get_Challenge    0x84    /*"��CPU��ȡ�����"*/              
#define Get_Response     0xc0    /*"��CPU��ȡ��Ӧ����"*/

#define Update_Binary    0xd6    //�޸Ķ������ļ� 
#define Append_Record    0xe2    //���Ӽ�¼               
#define Update_Record    0xdc    //�޸ļ�¼         
#define Write_Key        0xd4    //���ӻ��޸���Կ   
#define Increase         0x32    //���                      
#define Decrease         0x30    //�ۿ�   

/*"**********************************************************************************"*/

//void select_communication_port(unsigned char); /*" ѡ��UART��ָ��λ�� "*/


unsigned char Cpucard_Esamcard_Internal_Auth(void);   
                                               /*" �ڲ���֤ "*/
                                               /*" FF��ʾ������Ӧ��00��ʾ��ȷ��Ӧ "*/
unsigned char Cpucard_External_Auth(void);     /*" CPU���ⲿ��֤ "*/
                                               /*" FF��ʾ������Ӧ��00��ʾ��ȷ��Ӧ "*/
unsigned char Esamcard_External_Auth(void);    /*" ESAM���ⲿ��֤ "*/
                                               /*" FF��ʾ������Ӧ��00��ʾ��ȷ��Ӧ "*/
unsigned char Esam_Remain_Money_Dec(void);
unsigned char Get_File_Data(unsigned char,unsigned char,unsigned char,unsigned char,unsigned char * );
unsigned char CPU_Counter_Dec(unsigned char ,unsigned char );
unsigned char Esam_Safe_Password_Updata(unsigned char ,unsigned char  ,unsigned char );
unsigned char PassWord_Updata(unsigned char);
INT8U Remain_Money_Moneybag_To_Cpu(void);
unsigned char Cpu_File_Updata(unsigned char Cpu_File_Name,
								    unsigned char Esam_File_Name,
							   		unsigned char Cpu_Start_Addr,
							   		unsigned char Esam_Start_Addr,
							   		unsigned char Updata_Data_L);
unsigned char Esam_File_Updata(unsigned char Cpu_File_Name,
									unsigned char Esam_File_Name,
							   		unsigned char Cpu_Start_Addr,
							   		unsigned char Esam_Start_Addr,
							   		unsigned char Updata_Data_L,
							   		unsigned char * Data_Output_Point) ;

unsigned char Updata_Esam_Return_File(unsigned char Order_Kind);//cpu�� �����д�ļ� 
void Deal_Run_Inf_Data(unsigned char * Source_Point,unsigned char Mode);
unsigned char Read_Esam_Moneybag_File(unsigned char * Moneybag_Data_Point);
unsigned char Remain_Money_Moneybag_Add(unsigned char File_Name,unsigned char Offset,
		unsigned char * Remain_Money_Point);
unsigned char Remain_Money_Moneybag_Init(void);
/*"************ **********************************************************************"*/
#define Length_receive_send_buffer   350
#define Length_Card_WR_Buff   350
#define Length_AppleBuffer   350
#define Length_FarPaidBuff   350
#define receive_send_buffer ((INT8U *)&Pub_Buf0[0])  
#define  Card_WR_Buff       ((INT8U *)&Pub_Buf0[350])
#define  AppleBuffer        ((INT8U *)Pub_Buf)
#define  FarPaidBuff        ((INT8U *)&Pub_Buf[350])
/*"**********************************************************************************"*/
/*" �ⲿ�������� "*/
//////////////
#endif

