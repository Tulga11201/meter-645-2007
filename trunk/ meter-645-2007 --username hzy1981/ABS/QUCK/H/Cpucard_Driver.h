
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

//void select_communication_port(INT8U); /*" 选择UART口指向位置 "*/


INT8U Cpucard_Esamcard_Internal_Auth(void);   
                                               /*" 内部认证 "*/
                                               /*" FF表示错误响应，00表示正确响应 "*/
INT8U Cpucard_External_Auth(void);     /*" CPU卡外部认证 "*/
                                               /*" FF表示错误响应，00表示正确响应 "*/
INT8U Esamcard_External_Auth(void);    /*" ESAM卡外部认证 "*/
                                               /*" FF表示错误响应，00表示正确响应 "*/
INT8U Esam_Remain_Money_Dec(void);
INT8U Get_File_Data(INT8U,INT8U,INT8U,INT8U,INT8U * );
INT8U CPU_Counter_Dec(INT8U ,INT8U );
INT8U Esam_Safe_Password_Updata(INT8U ,INT8U  ,INT8U );
INT8U PassWord_Updata(INT8U);
INT8U Remain_Money_Moneybag_To_Cpu(void);
INT8U Cpu_File_Updata(INT8U Cpu_File_Name,
								    INT8U Esam_File_Name,
							   		INT8U Cpu_Start_Addr,
							   		INT8U Esam_Start_Addr,
							   		INT8U Updata_Data_L);
INT8U Esam_File_Updata(INT8U Cpu_File_Name,
									INT8U Esam_File_Name,
							   		INT8U Cpu_Start_Addr,
							   		INT8U Esam_Start_Addr,
							   		INT8U Updata_Data_L,
							   		INT8U * Data_Output_Point) ;

INT8U Updata_Esam_Return_File(INT8U Order_Kind);//cpu卡 处理回写文件 
void Deal_Run_Inf_Data(INT8U * Source_Point,INT8U Mode);
INT8U Read_Esam_Moneybag_File(INT8U * Moneybag_Data_Point);
INT8U Remain_Money_Moneybag_Add(INT8U File_Name,INT8U Offset,
		INT8U * Remain_Money_Point);
INT8U Remain_Money_Moneybag_Init(void);
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

