
#define CPUCARD_DRIVER_C_
#include "MyIncludesAll.h"


#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

   
/*"**************************************************************************"*/
unsigned char Cpucard_Esamcard_Internal_Auth(void)   /*"内部认证"*/
    {
    
    if(Check_CPU_Occur())			
    {
        ASSERT_FAILED();   
        Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
        return ERR;
    } 
    CPU_ESAM_CARD_Control(CPU);
    //
    Debug_Print(" 从cpu卡得到8字节随机数" );
    if( Read(0,Get_Challenge,0,0,8) != OK )
		return ERR;

    My_Memcpy(receive_send_buffer+50,receive_send_buffer,8);

    Debug_Print("对8字节随机数加密 得到k1 " );
    if( Internal_Auth(0,0x88,0,1,8,receive_send_buffer+50) != OK )
	return ERR;
    
    My_Memcpy( receive_send_buffer+60,receive_send_buffer,8 );
    Debug_Print("利用离散生产密钥" );
    CPU_ESAM_CARD_Control(ESAM);
    if(Internal_Auth(0x80,0xfa,0,1,8,cpucard_number)){
        return ERR;
    }
    if( Judge_Return_Flag() )
	    return ERR;
    Debug_Print("加密8字节随机数 ，得到k2" );
    Internal_Auth(0x80,0xfa,0,0,8,receive_send_buffer+50);
    if( Judge_Return_Flag() )
	    return ERR;

    CPU_ESAM_CARD_Control(CPU);
    Debug_Print("比较k1和k2" );
    if(My_Memcmp(receive_send_buffer+60,receive_send_buffer,8))  
        {
        Card_Error_State.CardErrorState.CpuCardInternlAuthenticationErr=1;
        ASSERT_FAILED();
        return ERR;      
        }  
    return OK;  /*"内部认证结束"*/  
    }

/*"**************************************************************************"*/
unsigned char Cpucard_External_Auth(void)
    {

    if(Check_CPU_Occur())			
        {
         ASSERT_FAILED();
        Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
        return ERR;
        }
    CPU_ESAM_CARD_Control(CPU);    /*"串口通向CPU卡。 "*/  
    Debug_Print("从cpu卡得到8字节随机数" );
    Read(0,Get_Challenge,0,0,8);  /*"取CPU卡随即数 "*/ 
    if( Judge_Return_Flag() )
    {
     ASSERT_FAILED();  
     return ERR;
    }
	   
    
    My_Memcpy(receive_send_buffer+150,receive_send_buffer,8);  /*"转移随机数 "*/  
    CPU_ESAM_CARD_Control(ESAM);   /*"串口通向ESAM卡"*/
    Debug_Print("esam 利用离散 生成密钥 " );
    Internal_Auth(0x80,0xfa,0,2,8,cpucard_number);      /*"加密ESAM随机数"*/
    if( Judge_Return_Flag() )
	    return ERR;
   Debug_Print("esam利用密钥加密随机数 得到k1 " );
    Internal_Auth(0x80,0xfa,0,0,8,receive_send_buffer+150);
    if( Judge_Return_Flag() )
	    return ERR;
   Debug_Print(" cpu卡 利用 k1 做外部认证，" );
    CPU_ESAM_CARD_Control(CPU);    /*"串口通向CPU卡"*/
    My_Memcpy(receive_send_buffer+100,receive_send_buffer,8);     /*"转移随机数"*/      

    if( External_Auth(2,8,receive_send_buffer+100) != OK )
    	{
        ASSERT_FAILED();  test();
	Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr=1;
	return ERR;
    	}
    if( Judge_Return_Flag() )
    {
      ASSERT_FAILED();
      return ERR;
    }
	    

    return OK;  /*"CPU卡外部认证结束"*/                                  
  }
    
/*"**************************************************************************"*/
unsigned char Esamcard_External_Auth(void)
	{                  
	if(Check_CPU_Occur())			
		{
                ASSERT_FAILED();   
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return ERR;
		}


	CPU_ESAM_CARD_Control(ESAM);   /*"串口通向ESAM卡"*/
  
	Read(0,Get_Challenge,0,0,8);
	if( Judge_Return_Flag() )
        {
          ASSERT_FAILED();
          return ERR;
        }
		
  
	CPU_ESAM_CARD_Control(CPU);   /*"串口通向CPU卡"*/
	My_Memcpy(receive_send_buffer+100,receive_send_buffer,8);     /*"转移随机数"*/  
    
	Internal_Auth(0,0x88,0,2,8,receive_send_buffer+100);
	if( Judge_Return_Flag() )
		return ERR;
  
	CPU_ESAM_CARD_Control(ESAM);   /*"串口通向ESAM卡"*/
	My_Memcpy(receive_send_buffer+100,receive_send_buffer,8);     /*"转移随机数"*/  

	My_Memcpy(receive_send_buffer+108,cpucard_number,8);

	if( External_Auth(1,0x10,receive_send_buffer+100) != OK )
		{
                ASSERT_FAILED();  
		Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr=1;
		return ERR;
		}
	if( Judge_Return_Flag() )
        {
          ASSERT_FAILED();
          return ERR;
        }
	return OK;  /*"ESAM卡外部认证结束"*/        
	}

/*"**************************************************************************"*/
/*" 功能：钱包文件剩余电费读出给CPU卡 "*///1,0   3,4
unsigned char Remain_Money_Moneybag_To_Cpu_Step(unsigned char Rec_Addr,unsigned char Rec_Offset)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];

	  Debug_Print("从cpu卡得到4字节随机数  " );//821C48C29000
	CPU_ESAM_CARD_Control(CPU);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
        {
          ASSERT_FAILED();
          return ERR;
        }
		
       //04B2010C11 + RAND +04D6820008 1ED01F5FEAF7B53C
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xD6;
	temp_buffer_2[6]=0x82;
	temp_buffer_2[7]=Rec_Offset;//0,4
	temp_buffer_2[8]=0x08;/*" 6字节为0x0A,4字节为0x08 "*/

	My_Memcpy(temp_buffer_2+9,cpucard_number,8);
	CPU_ESAM_CARD_Control(ESAM);
         Debug_Print(" 明文 + mac  + 离散， 读esam  返回 钱包和mac " );//00000000573A712C9000
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB2;
	Order_Head[2] = Rec_Addr;//1,3
	Order_Head[3] = 0x0C;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x11,temp_buffer_2,0,CommunicationPortMode,0x08)!= OK )/*" 6字节为0x0A,4字节为0x08 "*/
		return ERR;
         //04D6820008 +XX
	CPU_ESAM_CARD_Control(CPU);
	My_Memcpy(temp_buffer_2,receive_send_buffer,0x08);/*" 6字节为0x0A,4字节为0x08 "*/
         Debug_Print(" 明文 + mac 写cpu卡  " );
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x82;
	Order_Head[3] = Rec_Offset;//0,4
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x08,temp_buffer_2,0,CommunicationPortMode,0)!= OK )/*" 6字节为0x0A,4字节为0x08 "*/
        {
          Debug_Print(" 明文 + mac 写cpu卡  写失败 " );
          ASSERT_FAILED();
          return ERR;
        }
		

    return OK;
	}

/*"**************************************************************************"*/
/*" 功能：钱包文件剩余电费或购电次数初始化 "*/
/*" Length_LE: 读数据长度 "*/
unsigned char Remain_Money_Moneybag_Step(unsigned char Rec_Addr,unsigned char Rec_Offset)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];
	
	CPU_ESAM_CARD_Control(ESAM);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
       return ERR;

	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xDC;
	temp_buffer_2[6]=Rec_Addr;
	temp_buffer_2[7]=0x0C;
//	temp_buffer_2[8]=0x10;
	temp_buffer_2[8]=0x08;
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x82;
	Order_Head[3] = Rec_Offset;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,9,temp_buffer_2,0,CommunicationPortMode,0x08)!= OK )
		return ERR;

	CPU_ESAM_CARD_Control(ESAM);
//	My_Memcpy(temp_buffer_2,cpucard_number,8);
//	My_Memcpy(temp_buffer_2+8,receive_send_buffer,0x08);
	My_Memcpy(temp_buffer_2,receive_send_buffer,0x08);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xDC;
	Order_Head[2] = Rec_Addr;
	Order_Head[3] = 0x0C;
//	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x10,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x08,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;
	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：钱包文件初始化 "*/
/*" Length_LE: 读数据长度 "*/
unsigned char Remain_Money_Moneybag_Init(void)
	{
        //读取cpu卡钱包文件， 设置esam的钱包文件
	if( Remain_Money_Moneybag_Step(1,0) !=OK )
		return ERR;
       
	if( Remain_Money_Moneybag_Step(3,4) != OK )
		return ERR;
    return OK;
	}
/*"**************************************************************************"*/
/*" 功能：剩余电费钱包文件读到ESAM数据回抄卡 "*/
unsigned char Remain_Money_Moneybag_To_Cpu()
	{
	if( Remain_Money_Moneybag_To_Cpu_Step(1,0) !=OK )
		return ERR;
	if( Remain_Money_Moneybag_To_Cpu_Step(3,4) != OK )
		return ERR;
	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：读ESAM钱包文件剩余电费和购电次数 "*/
unsigned char Read_Esam_Moneybag_File(unsigned char * Moneybag_Data_Point)
	{	
  
	CPU_ESAM_CARD_Control(ESAM);
        
	if(Read(0,0xb2,0x01,0x0C,0x04)!=OK) 
		return ERR; 
	My_memcpyRev(Moneybag_Data_Point,receive_send_buffer,4);
	if(Read(0,0xb2,0x03,0x0c,0x04)!=OK)
       	return ERR; 
	My_memcpyRev(Moneybag_Data_Point+4,receive_send_buffer,4);
	return OK;  
	}

/*"**************************************************************************"*/
/*" 功能：ESAM钱包文件剩余电费扣除函数 "*/
/*" 电量走字的时候用 "*/
/*" Flag=0走字的时候调用，Flag＝1上电或掉电的时候调用 "*/
//unsigned long Reamin_Money_ESAM;
unsigned long Reamin_Money_ESAM_Dec_Time;
void Esam_Remain_Money_Do(unsigned char Flag)
	{
	}

/*"**************************************************************************"*/
/*" 功能：钱包文件剩余电费累加 "*/
/*" 新卡和购电卡用 "*/               // 2,0,0 ,           1,4,0
unsigned char Remain_Money_Moneybag_Add(unsigned char File_Name,unsigned char Offset,
		unsigned char * Remain_Money_Point)
	{
	unsigned char  temp_buffer_2[30],Order_Head[4];

	//从esam得到4byte随机数
	CPU_ESAM_CARD_Control(ESAM);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
		return ERR;
        ///明文+mac读 cpu卡文件 ，计算mac 
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x84;
	temp_buffer_2[5]=0x32;
	temp_buffer_2[6]=0x01;
	temp_buffer_2[7]=0x0c;
	temp_buffer_2[8]=0x0C;
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+File_Name;
	Order_Head[3] = Offset;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,9,temp_buffer_2,0,CommunicationPortMode,0x0C)!= OK )
		return ERR;
        
	if( Remain_Money_Point != 0 )//判断要不要把从cpu卡读出的数据输出到缓冲，因为给电表使用所以反相
		{
		My_memcpyRev(Remain_Money_Point,receive_send_buffer,4);
		My_memcpyRev(Remain_Money_Point+4,receive_send_buffer+4,4);
		}
	else{//esam钱包文件充值   明文+mac  充值
                  
		CPU_ESAM_CARD_Control(ESAM);
		My_Memcpy(temp_buffer_2,receive_send_buffer,0x0C);
		Order_Head[0] = 0x84;
		Order_Head[1] = 0x32;
		Order_Head[2] = 0x01;
		Order_Head[3] = 0x0C;
		if( CPU_Card_Driver((const unsigned char *)Order_Head,0x0C,temp_buffer_2,0,CommunicationPortMode,0)!= OK )/*" 6字节为0x18,4字节为0x14 "*/
			return ERR;
	}
           return OK;
	}
/*"**************************************************************************"*/
/*" 功能：得到Esam或CPU文件中信息 "*/
/*" 数据拜访顺序为高位在低字节 "*/
unsigned char Get_File_Data(unsigned char Door,unsigned char File,unsigned char Offset,
							unsigned char Length,unsigned char * Point)
	{
	CPU_ESAM_CARD_Control(Door);
	if( Read(0,Read_Binary,0x80+File,Offset,Length) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
		
	if( Door==ESAM )
		My_Memcpy(Point,receive_send_buffer,Length);
	else
		My_memcpyRev(Point,receive_send_buffer,Length);
	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：Esam其他文件更新 "*/
/*" Cpu_File_Name: "*/
/*" Esam_File_Name: "*/
/*" Cpu_Start_Addr: "*/
/*" Esam_Start_Addr: "*/
/*" Updata_Data_L: "*///01  02   0404 02//01 02 0a 0a 05
unsigned char Esam_File_Updata(unsigned char Cpu_File_Name,
									unsigned char Esam_File_Name,
							   		unsigned char Cpu_Start_Addr,
							   		unsigned char Esam_Start_Addr,
							   		unsigned char Updata_Data_L,
							   		unsigned char * Data_Output_Point)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];
	unsigned char Head_Length;

	//得到随机数
         Debug_Print("/得到随机数 "  );
	CPU_ESAM_CARD_Control(ESAM);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
		return ERR;
        //明文+mac读cpu卡二进制文件
         Debug_Print("/明文+mac读cpu卡二进制文件 "  );
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xD6;
	temp_buffer_2[6]=0x80+Esam_File_Name;//2
	temp_buffer_2[7]=Esam_Start_Addr;//4
	temp_buffer_2[8]=Updata_Data_L+4;// 这里规定了从cpu卡读几个字节，为什么要加4,是因为写esam的时候还要加上4字节mac，
	if( Meter_Ins_Flag == 0xFF ){
		Head_Length = 0x11;
		temp_buffer_2[9] = 0x00;
		temp_buffer_2[10] = 0x00;
		My_Memcpy(&temp_buffer_2[11], Pre_Payment_Para.BcdMeterID,6);
	}
	else
		Head_Length = 0x09;
	
	CPU_ESAM_CARD_Control(CPU);

	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+Cpu_File_Name;//1
	Order_Head[3] = Cpu_Start_Addr;//4
	if( CPU_Card_Driver( (const unsigned char *)Order_Head,Head_Length,temp_buffer_2,0,CommunicationPortMode,Updata_Data_L+4)!= OK )
		return ERR;
        //明为+mac  写esam 二进制文件 
         Debug_Print("明为+mac  写esam 二进制文件 "  );
	CPU_ESAM_CARD_Control(ESAM);
        //经过上面的步骤后 存放在receive_send_buffer 缓冲的数据长度为：Updata_Data_L+4个，因为调用CPU_Card_Driver函数的时候
        //不能CPU_Card_Driver函数的参数W_Data 和receive_send_buffer  不能为同一个缓冲，要换一个缓冲来调用CPU_Card_Driver
        //所以要用一个大的缓冲但是不能用temp_buffer_2，他太小了，并且Card_WR_Buff在下面的流程中被Data_Output_Point
        //用来存放数据 ，所以还要一个比较大的缓冲，(INT8U *)Pub_Buf0 
        mem_cpy( AppleBuffer,receive_send_buffer,Updata_Data_L+4,AppleBuffer,Length_AppleBuffer);
	if( Data_Output_Point!=0 )
		My_Memcpy(Data_Output_Point,receive_send_buffer,Updata_Data_L);
        
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x80+Esam_File_Name;//2
	Order_Head[3] = Esam_Start_Addr;//4
	if( CPU_Card_Driver((const unsigned char *)Order_Head,Updata_Data_L+4, AppleBuffer,0,CommunicationPortMode,0)!= OK )
		return ERR;
        
	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：CPU卡其他文件更新 "*/
/*" Cpu_File_Name: "*/
/*" Esam_File_Name: "*/
/*" Cpu_Start_Addr: "*/
/*" Esam_Start_Addr: "*/
/*" Updata_Data_L: "*///04,03,0,0,240 费率1文件更新 
unsigned char Cpu_File_Updata(unsigned char Cpu_File_Name,
								    unsigned char Esam_File_Name,
							   		unsigned char Cpu_Start_Addr,
							   		unsigned char Esam_Start_Addr,
							   		unsigned char Updata_Data_L)
	{
	unsigned char temp_buffer_2[30],Order_Head[4];

	Debug_Print(" 开始cpu卡文件更新 cpu卡文件标示：%d esam文件标示:%d    ",Cpu_File_Name,Esam_File_Name  );
         Debug_Print("  //得到随机数    "  );//0084000004 B72B44369000  Debug_Print(" "  );
	CPU_ESAM_CARD_Control(CPU);
	if(Read(0,Get_Challenge,0,0,4)!=OK)
		return ERR;
       
	temp_buffer_2[0]=receive_send_buffer[0];   
	temp_buffer_2[1]=receive_send_buffer[1];
	temp_buffer_2[2]=receive_send_buffer[2];
	temp_buffer_2[3]=receive_send_buffer[3];
	temp_buffer_2[4]=0x04;
	temp_buffer_2[5]=0xD6;
	temp_buffer_2[6]=0x80+Cpu_File_Name;
	temp_buffer_2[7]=Cpu_Start_Addr;
	temp_buffer_2[8]=Updata_Data_L+4;//这里规定了从cpu卡读几个字节，为什么要加4,是因为写esam的时候还要加上4字节mac，
        //04B0830011 71DDD3FD +  04D68200+changdu 1ED01F5FEAF7B53C
	My_Memcpy(temp_buffer_2+9,cpucard_number,8);
         Debug_Print("  // 明文+ mac +离散  读取esam  二进制文件     "  );//
	CPU_ESAM_CARD_Control(ESAM);
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xB0;
	Order_Head[2] = 0x80+Esam_File_Name;//2
	Order_Head[3] = Esam_Start_Addr;
	if( CPU_Card_Driver( (const unsigned char *)Order_Head,0x11,temp_buffer_2,0,CommunicationPortMode,Updata_Data_L+4)!= OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
        //04D68300 changdu +shuju
        Debug_Print("   明文+mac写 cpu卡  Updata_Data_L+4:%d ",Updata_Data_L+4  );
       //经过上面的步骤后 存放在receive_send_buffer 缓冲的数据长度为：Updata_Data_L+4个，因为调用CPU_Card_Driver函数的时候
        //不能CPU_Card_Driver函数的参数W_Data 和receive_send_buffer  不能为同一个缓冲，要换一个缓冲来调用CPU_Card_Driver
        //所以要用一个大的缓冲但是不能用temp_buffer_2，他太小了，并且Card_WR_Buff在下面的流程中被Data_Output_Point
        //用来存放数据 ，所以还要一个比较大的缓冲，:(INT8U *)Pub_Buf0
	CPU_ESAM_CARD_Control(CPU);
        mem_cpy( AppleBuffer,receive_send_buffer,Updata_Data_L+4, AppleBuffer,700);
	Order_Head[0] = 0x04;
	Order_Head[1] = 0xD6;
	Order_Head[2] = 0x80+Cpu_File_Name;//3
	Order_Head[3] = Cpu_Start_Addr;//
	if( CPU_Card_Driver((const unsigned char *)Order_Head,Updata_Data_L+4,AppleBuffer,0,CommunicationPortMode,0)!= OK )
        {
          ASSERT_FAILED();
          return ERR; 
        }

	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：CPU卡计数器文件更新 "*/
/*" CPU_File_Name: "*/
/*" CPU_Counter_Length: "*/
/*"计数器减一8030001404+00000001 "*/
unsigned char CPU_Counter_Dec(unsigned char CPU_File_Name,unsigned char CPU_Counter_Length)
	{
	unsigned char Order_Head[4];
	
	CPU_ESAM_CARD_Control(CPU);
	Order_Head[0] = 0;
	Order_Head[1] = 0;
	Order_Head[2] = 0;
	Order_Head[3] = 1;
	if(Write(0x80,0x30,00,CPU_File_Name,CPU_Counter_Length,Order_Head)!=OK)
        {
        
          ASSERT_FAILED();
          return ERR;
        }
		

	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：密钥更新 "*/
/*"801a1e0108+0000+ 表号 "*/
/*"801a1e0208+0000+表号"*/
/*"801a1e0608+0000+表号"*/
/*"801a1e0708+0000+表号"*/
/*"bfe6000203010300"*/               
/*"bfe6000203010500"*/
/*"bfe6000203010900"*/
/*"bfe6000203010a00"*/
/*"84d401ff20+ DATA"*/               
/*"84d401ff20+ DATA"*/
/*"84d401ff20+ DATA"*/
/*"84d401ff20+ DATA"*/
unsigned char Esam_Safe_Password_Updata(unsigned char Password_Addr,
											    unsigned char Password_Off,
											    unsigned char Card_ID)
	{
	unsigned char Order_Head[4],temp_buffer_2[32];
	unsigned char i;

	CPU_ESAM_CARD_Control(CPU);
	Order_Head[0] = 0x80;
	Order_Head[1] = 0x1A;
	Order_Head[2] = 0x1E;
	Order_Head[3] = Password_Addr;
	temp_buffer_2[0] = 0;
	temp_buffer_2[1] = 0;//
	My_Memcpy(temp_buffer_2+2,Pre_Payment_Para.BcdMeterID  ,6); 
	if( Card_ID==GWFAR_RES_PASSWORD_CARD )
		{
		for( i=0;i<8;i++ )
			temp_buffer_2[i] = 0;
		temp_buffer_2[7] = 1;
		}
	if( CPU_Card_Driver((const unsigned char *)Order_Head,8,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	Order_Head[0] = 0xBF;
	Order_Head[1] = 0xE6;
	Order_Head[2] = 0x00;
	Order_Head[3] = 0x02;

	temp_buffer_2[0] = 0x01;
	temp_buffer_2[1] = Password_Off;
	temp_buffer_2[2] = 0x00;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,3,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	My_Memcpy(temp_buffer_2,receive_send_buffer,0x20); 

	CPU_ESAM_CARD_Control(ESAM);
	Order_Head[0] = 0x84;
	Order_Head[1] = 0xD4;
	Order_Head[2] = 0x01;
	Order_Head[3] = 0xFF;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x20,temp_buffer_2,0,CommunicationPortMode,0)!= OK )
		return ERR;

	return OK;
	}
/*"**************************************************************************"*/
/*" 功能：密钥更新 "*/
unsigned char PassWord_Updata(unsigned char Card_ID)
	{
	unsigned char i;
	
	if( Esam_Safe_Password_Updata(1,3,Card_ID) != OK )
        {
          ASSERT_FAILED();
          return ERR;
        }
		
	if( Esam_Safe_Password_Updata(2,5,Card_ID) != OK )
		return ERR;
	if( Esam_Safe_Password_Updata(6,9,Card_ID) != OK )
		return ERR;
	if( Esam_Safe_Password_Updata(7,0x0A,Card_ID) != OK )
		return ERR;

	CPU_ESAM_CARD_Control(CPU);
	if( Read(0x00,Read_Binary,0x83,0x04,0x80 ) != OK )
		return ERR;

	My_Memcpy(Card_WR_Buff,receive_send_buffer,0x80); 
	
	CPU_ESAM_CARD_Control(ESAM);
	for(i=0;i<3;i++)
		{
		if(Write(0x84,0xd4,1,0xff,0x20,&Card_WR_Buff[32*i])!=OK)
			{
                          ASSERT_FAILED();
			  Card_Error_State.CardErrorState.Password_Key_Updata_ERR=1;
			  return ERR; 
			}
		} 
	
	for(i=3;i<4;i++)
		{
		if(Write(0x84,0xd4,1,0x00,0x20,&Card_WR_Buff[32*i])!=OK)
			{ 
                         ASSERT_FAILED(); 
			 Card_Error_State.CardErrorState.Password_Key_Updata_ERR=1;
			 return ERR; 
			}
		} 
	return OK;
	}


//-----------------------------------------------------------------
//根据电表信息，更新esam返写文件 "
unsigned char Updata_Esam_Return_File(unsigned char Order_Kind)
{
        //缓冲清0， 因为缓冲中有的数据 在下面的流程中并不会覆盖，  但是又想要设置为0
        mem_set(Card_WR_Buff,0x00,sizeof(LENGTH_RUN_INF_DATA)+6,Card_WR_Buff,Length_Card_WR_Buff);
	
	Card_WR_Buff[0] = 0x68;
	Card_WR_Buff[1] = Order_Kind;//卡类型
	Card_WR_Buff[2] = 0;
	Card_WR_Buff[3] = LENGTH_RUN_INF_DATA;//这个地方减去1 是因为 字节对齐问题，在该结构体前插入了一个无用的字节
        //从esam 以及电能表中读取数据  
	Deal_Run_Inf_Data(Card_WR_Buff+4,0x80);//加4 是因为 传给的地址 为 除去 0x68头段 ，卡类型段，长度段  的地址
	//LENGTH_RUN_INF_DATA+4-1 是因为 该地址为 效验和段， Cal_Add_CS为计算效验和函数，第一个地址为卡类型段地址，，第二个为除去头尾及效验和段长度 再减去 插入的无用字节
	Card_WR_Buff[LENGTH_RUN_INF_DATA+4-1] = Cal_Add_CS(Card_WR_Buff+1,LENGTH_RUN_INF_DATA-1+3);//倒数最后一个为效验位
	Card_WR_Buff[LENGTH_RUN_INF_DATA+5-1] = 0x16;//结束标志// 减去， 是因为多了一个无用字节
	
	CPU_ESAM_CARD_Control(ESAM);
        //写esam  
	if( Write(0,Update_Binary,0x80+ESAM_RUN_INF_FILE,0,LENGTH_RUN_INF_DATA+6,Card_WR_Buff) != OK )
		return ERR;
	return OK;
}
//------------------------------------------------------------------
/*"Mode:函数调用模式，1：写调用，0：读调用 "*/
/*"BIT7 :1：写调用，0：读调用 "*/
/*"BIT0~BIT6 表示更新第几梯度 "*/
/*"Source_Point：写调用模式下，为数据来源。 "*/
/*"读调用模式下，为数据去处 "*/
/*"处理以下数据结构中的数据 "*/
/*"需要使用receive_send_buffer做缓冲 "*/
// 回写数据,给用户卡，ESAM用 //
//struct Run_Inf_Data
//	{	
//	unsigned char User_Kind;					/*" 用户类型 "*/
//	unsigned char Current_CT[3];				/*" 电流互感器变比 "*/
//	unsigned char Voltage_PT[3];				/*" 电压互感器变比 "*/	
//	unsigned char Meter_ID[6];					/*" 表号 "*/
//	unsigned char Client_ID[6];				/*" 客户编号 "*/
//	unsigned long Remain_Money;				/*" 剩余金额 "*/
//	unsigned long Buy_Count;					/*" 购电次数 "*/
//	unsigned long Low_Zero_Money;				/*" 过零金额 "*/
//	unsigned char Password_Info[4];			/*" 密钥信息，包括：状态，方式，条数，版本 "*/
//	unsigned char Unlawful_Card_Count[3];		/*" 非法卡插入次数 "*/
//	unsigned char Return_DT[5];				/*" 返写日期时间 "*/
//	};
//#define LENGTH_RUN_INF_DATA  sizeof(struct Run_Inf_Data)
//当为esam回抄卡时 和 用户卡 时使用
void Deal_Run_Inf_Data(unsigned char * Source_Point,unsigned char Mode)
{
	struct Run_Inf_Data  Run_Inf_Data;
        INT32U CurrMeter_MoneyCount;
        
        INT32U Temp ;
        INT8U  DataTemp[5];
	//Run_Inf_Data = (struct Run_Inf_Data *)Source_Point;
        mem_cpy(&Run_Inf_Data,Source_Point, sizeof(struct Run_Inf_Data),&Run_Inf_Data, sizeof(struct Run_Inf_Data));
          
//" 用户编号，表号，用户类型"
        
        My_memcpyRev(&Run_Inf_Data.Client_ID[0],Pre_Payment_Para.UserID,6);
        My_memcpyRev(&Run_Inf_Data.Meter_ID[0],Pre_Payment_Para.BcdMeterID,6);
        Run_Inf_Data.User_Kind=CardType;
 ///剩余电费  //这个地方要改
        CurrMeter_MoneyCount=Get_Left_Money();
 	My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Remain_Money),(INT8U *)&(CurrMeter_MoneyCount),4);
// 购电次数 //这个地方要改
        CurrMeter_MoneyCount=Get_Buy_Eng_Counts();
	My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Buy_Count),(unsigned char *)&(CurrMeter_MoneyCount),4);
//  过零电费//这个地方可能会出问题
        Temp=Get_Overdraft_Money();
        Hex2Bcd(Temp, DataTemp,4,DataTemp,4);//从黄工哪里得到INT32U的hex型的 透支金额，并转换为4个字节的BCD码
 	My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Low_Zero_Money),DataTemp,4);
//  CT  //
        Read_Storage_Data(SDI_CURR_TRANS_RATIO, DataTemp, DataTemp, 4);//   从黄工那里电流互感器变比  
	My_memcpyRev( ( unsigned char *)&(Run_Inf_Data.Current_CT),(unsigned char *)DataTemp,3);//只要3个字节因为esam中为3个字节
    //  PT  //电压互感变化
        Read_Storage_Data(SDI_VOLT_TRANS_RATIO, DataTemp, DataTemp, 4);//  从黄工那里电压互感变化
	My_memcpyRev((unsigned char *)&(Run_Inf_Data.Voltage_PT),(unsigned char *)DataTemp,3);
         //" 从esam中得到密钥信息 // 
	Get_File_Data(ESAM,ESAM_PASSWORD_INF_FILE,0,4,Run_Inf_Data.Password_Info);
        // 非法卡插入次数 "//
        Read_Storage_Data (  _SDI_INVALID_CARD_COUNTS, &Temp, &Temp, 4  );//     
        
        Hex2Bcd(Temp, DataTemp,3,DataTemp,3);//
        My_memcpyRev( (unsigned char *)&(Run_Inf_Data.Unlawful_Card_Count[0]),(unsigned char *)DataTemp,3);
        //" 返写日期时间 "//
        DataTemp[0 ]=Cur_Time1.Year;
        DataTemp[ 1]=Cur_Time1.Month;
        DataTemp[ 2]=Cur_Time1.Date;
        DataTemp[ 3]=Cur_Time1.Hour;
        DataTemp[ 4]=Cur_Time1.Min;        
        mem_cpy(  &Run_Inf_Data.Return_DT[0] ,DataTemp,5, &Run_Inf_Data.Return_DT[0],5 );
        //把更新了的  数据 复制到 函数实参数(INT8U *)&Run_Inf_Data + 1 是应为考虑到该结构体的字节对齐问题，在其添加了一个多余的字 
        mem_cpy( Source_Point,((INT8U *)&Run_Inf_Data) + 1, sizeof(struct Run_Inf_Data) - 1,Source_Point, Length_Card_WR_Buff-4 );   
}
unsigned char Esam_Remain_Money_Dec(void)
{
	unsigned char Order_Head[4];
	struct Moneybag_Data Moneybag_Data;
        INT32U MeterRemainMoney;
        MeterRemainMoney=Get_Left_Money();
       // Debug_Print("//从esam 读取 钱包文件 ，4字节， 并反相，  " );
  	Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data);
        //与表中的 钱包金额 比较， 并相减 得到差额
	if( MeterRemainMoney>0 )
        {
		if( MeterRemainMoney<=Moneybag_Data.Remain_Money )
			Moneybag_Data.Remain_Money -= MeterRemainMoney;
		else
			Moneybag_Data.Remain_Money = 0;
			
	}
        
        if(Moneybag_Data.Remain_Money EQ 0)
        {
           return OK;
        }
        //mem_cpy(Order_Head,(INT8U *)&Moneybag_Data.Remain_Money,4,Order_Head,4);
        //Debug_Print(" 对esam进行扣款操作，扣款值为： %x  %x  %x  %x", Order_Head[ 3], Order_Head[ 2], Order_Head[1 ], Order_Head[0 ]  );
        //Debug_Print(" // 对esam进行扣款操作  操作前 对 差额反相 " );
   
	if(Moneybag_Data.Remain_Money>0)
        {
		Reverse_data((unsigned char *)&Moneybag_Data.Remain_Money,4);
             //    Debug_Print(" 从esam得到的购电金额反相后为：%lx",Moneybag_Data.Remain_Money );
		Order_Head[0] = 0x80;
		Order_Head[1] = 0x30;
		Order_Head[2] = 0x00;
		Order_Head[3] = 0x0C;
		if( CPU_Card_Driver((const unsigned char *)&Order_Head[0],4,(unsigned char *)&Moneybag_Data.Remain_Money,0,CommunicationPortMode,0)!= OK )
                {
                   ASSERT_FAILED();
                   return ERR;
                }
			
	}
        //Debug_Print("//查看扣款后从esam 读取 钱包文件 ，4字节， 并反相，  " );
  	//Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data);
        //mem_cpy(Order_Head,(INT8U *)&Moneybag_Data,4,Order_Head,4);
        //Debug_Print(" 从esam卡得到的购电金额为： %x  %x  %x  %x", Order_Head[ 3], Order_Head[ 2], Order_Head[1 ], Order_Head[0 ]  );
	
         return OK;
}
