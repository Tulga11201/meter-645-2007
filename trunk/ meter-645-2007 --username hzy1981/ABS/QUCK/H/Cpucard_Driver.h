
/*"**********************************************************************************"*/
/*" I/O口预定义，不同的MCU可能不一样 "*/
#ifndef CPUCARD_DRIVER_H__
#define CPUCARD_DRIVER_H__

#undef EXT
#ifdef CPUCARD_DRIVER_C_
#define EXT   
#else
#define EXT extern   
#endif


/*"**********************************************************************************"*/
/*" 预定义定义,有关于CPU底层操作的错误 "*/
//#define CARD_BUFFER_LENGTH 1
#define FAR_COMM         PAY_FAR          
#define CPU              PAY_CPU_CARD
#define ESAM             PAY_ESAM
//define ZB_COMM          3

#define ERR              0xFF
#define OK               0x00

#define RESET_RECEIVE_DATA_LENGTH    11
#define ESAM_BUFFER_FILE_LENGTH      0x30       /*" 只利用ESAM返写文件的0x30个字节 "*/
#define ESAM_TEMP_FILE_LENGTH        0x41
 
/*"**********************************************************************************"*/
/*" CPU卡状态字定义 "*/
#define Read_Binary      0xb0    /*"从CPU卡读二进制文件"*/ 
#define Read_Record      0xb2    /*"从CPU卡读记录文件"*/                  
#define Get_Challenge    0x84    /*"从CPU卡取随机数"*/              
#define Get_Response     0xc0    /*"从CPU卡取响应数据"*/

#define Update_Binary    0xd6    //修改二进制文件 
#define Append_Record    0xe2    //增加记录               
#define Update_Record    0xdc    //修改记录         
#define Write_Key        0xd4    //增加或修改密钥   
#define Increase         0x32    //存款                      
#define Decrease         0x30    //扣款   

/*"**********************************************************************************"*/

//void select_communication_port(unsigned char); /*" 选择UART口指向位置 "*/


unsigned char Cpucard_Esamcard_Internal_Auth(void);   
                                               /*" 内部认证 "*/
                                               /*" FF表示错误响应，00表示正确响应 "*/
unsigned char Cpucard_External_Auth(void);     /*" CPU卡外部认证 "*/
                                               /*" FF表示错误响应，00表示正确响应 "*/
unsigned char Esamcard_External_Auth(void);    /*" ESAM卡外部认证 "*/
                                               /*" FF表示错误响应，00表示正确响应 "*/
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

unsigned char Updata_Esam_Return_File(unsigned char Order_Kind);//cpu卡 处理回写文件 
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
/*" 外部变量定义 "*/
//////////////
#endif

