#define  FAR_DEAL_CTRL_0X33_C_
 
#include "MyIncludesAll.h"



#undef Debug_Print
#define Debug_Print(...)
//#define Debug_Print _Debug_Print

//远程认证命令接口(控制码为03)
//pSrc表示远程帧的数据域， 长度为645帧中L段的值
//SrcLen表示数据域长度
//pDst表示经过处理后返回的数据域  存放的长度为645协议定义的L段的值的长度
//*pLen表示返回的数据长度
//pDst_Start和DstLen一起限定pDst和返回的数据长度
//1成功， 0失败，
INT8U Esam_Remote_Auth(INT8U *pSrc, INT8U SrcLen, INT8U *pDst, INT8U *pLen, INT8U *pDst_Start, INT16U DstLen){
        //定义局部变量
        INT8U  ret;
        INT32U  Far_Auth_Day_Follow;
        INT8U DataTemp[4];
        INT32U Temp;
        //INT8U DataTemp[5];
        
        OS_Mutex_Pend(PUB_BUF_SEM_ID);//使用缓冲：Pub_Buf0
        OS_Mutex_Pend(PUB_BUF0_SEM_ID); //使用信号量，以便使用缓冲
        //错误状态字清0， 因为每个功能的开始都是从身份认证开始的 ，其实这里不清0也可以
	Far_Security_Auth_Err_Info.intd=0;
        Card_Error_State.CardErrorState_INT32U=0;	
        
        // 判断身份认证有效时间是否过了，如果过了，ID_Ins_Counter就赋值为0
        Far_Identity_Auth_Ok_Flag=!Chk_Pay_Time_Arrive();
        //IT_STRUCT_VAR(_Far_Identity_Auth_Ok_Flag);
        if(Far_Identity_Auth_Ok_Flag EQ 0)
        {
           Reset_Pay_Timer(0);
        }
        
        //初始化：FarPrePayment.ID_Ins_Counter
        Read_Storage_Data(_SDI_INVALID_COUNTS_AllOW ,&FarPrePayment.ID_Ins_Counter,&FarPrePayment.ID_Ins_Counter, 1) ;
        if(FarPrePayment.ID_Ins_Counter != 0 )//判断是否需要更新ID_Ins_Counter ，
        {//Cur_Time0.Date
          DataTemp[0 ]=Cur_Time1.Year;
          DataTemp[ 1]=Cur_Time1.Month;
          DataTemp[ 2]=Cur_Time1.Date;
          DataTemp[ 3]=Cur_Time1.Hour;
          Read_Storage_Data(_SDI_FAR_AUTH_DAY_FOLLOW ,(INT8U *)&Far_Auth_Day_Follow, (INT8U *)&Far_Auth_Day_Follow, 4) ;
          //Get_Array_Time(T_BCD, DataTemp,DataTemp, 5);//从黄工那里得到5个字节的当前时间bcd编码，DataTemp[0]开始分别为：分，时，日，月年，没必要反相了
          if( memcmp( DataTemp,(INT8U *)&Far_Auth_Day_Follow,4 ) != 0 )//判断日期有没有变更
          {
            //Far_Auth_Day_Follow=Cur_Time1.Date;
            mem_cpy((INT8U *)&Far_Auth_Day_Follow,DataTemp,4,(INT8U *)&Far_Auth_Day_Follow,4);
            Write_Storage_Data(_SDI_FAR_AUTH_DAY_FOLLOW ,&Far_Auth_Day_Follow, 4);
            FarPrePayment.ID_Ins_Counter  =0;
	    Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, &FarPrePayment.ID_Ins_Counter, 1);
          }
        }
        mem_cpy(&Temp,pSrc,4,&Temp,4);
        //判断是否已经通过 身份验证，或者数据标示为请求安全认证
	if( ( Far_Identity_Auth_Ok_Flag== 1 ) || ( Temp EQ 0x70000FF  && FarPrePayment.ID_Ins_Counter<15 ) )
        {
           ret=Far_Deal_Order_0x03(pSrc,SrcLen);//  就是进行身份验证
        }else{
                ASSERT_FAILED();
		ret=ERR;
		IDENTITY_AUTH_ERR_DEFINE = 1; 
	}
        ///0x33类型函数执行成功 //// //返回1成功，移交数据给huck
	if(ret  EQ OK){
                  mem_cpy(pDst,pSrc,4,pDst_Start,DstLen);// 是有特殊的含义的， 意味着下层的函数，只要管N1N2---Nm   即可
	          mem_cpy(pDst+4, FarPaidBuff ,FarPrePayment.Far_SendLen,pDst,DstLen);
                  FarPrePayment.Far_SendLen+=4;//这里加4 是有特殊的含义的， 意味着下层的函数，只要管N1N2---Nm 的长度即可
                  *pLen = FarPrePayment.Far_SendLen;
                  OS_Mutex_Post(PUB_BUF0_SEM_ID);
                  OS_Mutex_Post(PUB_BUF_SEM_ID);
		  return  1;
	}
        //假如不成功/判断操作结果//返回0失败，清除，全局变量值，移交数据给huck
        mem_set((INT8U *)&Far_Identity_Auth_Data,0x00,sizeof(struct Far_Identity_Authentication_Define),(INT8U *)&Far_Identity_Auth_Data,sizeof(struct Far_Identity_Authentication_Define) );
        //准备发送 安全错误状态字//mem_set
	if(( Far_Security_Auth_Err_Info.intd & 0xFFFE ) != 0 )
        {
           Far_Security_Auth_Err_Info.intd &= 0xFFFE;
        }else{
            OTHER_ERR_DEFINE =1;
        }
	mem_cpy( pDst, (unsigned char *)&Far_Security_Auth_Err_Info.intd, 2,pDst_Start,DstLen);
        FarPrePayment.Far_SendLen=2;
        pLen=&FarPrePayment.Far_SendLen;

        OS_Mutex_Post(PUB_BUF0_SEM_ID);
        OS_Mutex_Post(PUB_BUF_SEM_ID);
	return  0;  
}
//////// 0x33类型的函数，的数据域的入口参数数据都为除去数据标示和操作者代码的 数据域，
//出口都为：也不要管数据标示，的直接存放在FarPaidBuff,发送的长度放在：FarPrePayment.Far_SendLen
  const struct Far_645_Frame_Flag_0x03  Far_645_Frame_Flag_0x03_List[]={
	0xFF,0x01,0x80,0x07,16,Far_Deal_078001FF,//数据回抄
        
	0x01,0x02,0x81,0x07,8,Far_Deal_07810201,//状态查询，读数据，剩余金额等
	0xFF,0x02,0x81,0x07,8,Far_Deal_078102FF,//同上

	0xFF,0x00,0x00,0x07,32,Far_Deal_070000FF,//身份验证 

	0xFF,0x01,0x00,0x07,14,Far_Deal_070001FF,//身份认证时效设置
	0x01,0x02,0x00,0x07,8,Far_Deal_07000201,//身份认证失效
	0xFF,0x02,0x00,0x07,8,Far_Deal_070002FF,//同上
//
	0xFF,0x01,0x01,0x07,30,Far_Deal_070101FF,//开户

	0xFF,0x02,0x01,0x07,30,Far_Deal_070102FF,//充值

	0xFF,0x01,0x02,0x07,48,Far_Deal_070201FF,//参数密钥更新
	0xFF,0x02,0x02,0x07,48,Far_Deal_070202FF,//控制命令密钥更新 
	0xFF,0x03,0x02,0x07,48,Far_Deal_070203FF,//远程身份认证密钥更新
	};
/////////0x33类型函数中转站,  
unsigned char Far_Deal_Order_0x03(unsigned char * Data_Point ,unsigned char Source_Length)
{
	unsigned char i;

	for( i=0;i<S_NUM(Far_645_Frame_Flag_0x03_List);i++ )
        {
	   if(memcmp(Data_Point, (INT8U *)Far_645_Frame_Flag_0x03_List[i].Data_ID, 4) EQ 0) 
		break;
	}
	if( i EQ S_NUM(Far_645_Frame_Flag_0x03_List) )
        {
             ASSERT_FAILED();
             return ERR;
        }
       // 长度不对 //
	if( Source_Length != Far_645_Frame_Flag_0x03_List[i].Source_Length )
        {
            ASSERT_FAILED();
            return ERR;		
        }	
	if( Far_645_Frame_Flag_0x03_List[i].Far_645_Order_0x03 !=0 )
        {
                //Data_Point+LENGTH_FAR_645_FRAME_0X03 为除去数据标示和操作者代码的 数据域
		if( Far_645_Frame_Flag_0x03_List[i].Far_645_Order_0x03(Data_Point+8) EQ OK )
			return OK;
	}
        ASSERT_FAILED();
	return ERR;
}
 /*"**************************************************************************"*/
/*"  身份认证 "*/
/*"  支持070000FF  "*/
/*" Data_Point:入:8+8+8：Data_Point。 数据内容为："密文1  随机数1 分散因子*/
/*"            出:4+8 放在FarPaidBuff中"*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
unsigned char Far_Deal_070000FF(unsigned char * Data_Point )
{     
     
        INT16U ValidTimeTemp;
        ///esam复位
	if( (Esamcard_Atr() )!=OK )
        { 
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;
       } 
       mem_cpy(esam_number,receive_send_buffer+5,8,esam_number,8);
       CPU_ESAM_CARD_Control(ESAM);
	if( Select_File(0,0x3F,0) != OK )
        {
                ASSERT_FAILED();
                Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;
	}	
	///开始远程身份认证
	if(Far_Esamcard_Internal_Auth(Data_Point)==OK)
        {
		if( Read(0,Get_Challenge,0,0,4) != OK )
                {
                        ASSERT_FAILED();
			OTHER_ERR_DEFINE =1;
			return ERR;
		}
                //组装要发送的数据
		My_memcpyRev(FarPaidBuff,receive_send_buffer,4);    //转移随机数2//
		My_memcpyRev(FarPaidBuff+4,esam_number,8);     //转移ESAM序列号//
		FarPrePayment.Far_SendLen=12;//不要管数据标示的长度，在上面会自动加4
                //FarPrePayment.Far_SendLen=0;//不要管数据标示的长度，在上面会自动加4
                //身份认证有效时长初始化 
		Far_Identity_Auth_Ok_Flag=1;	
		if(Far_Read_Esam(04,Read_Binary,0x80+ESAM_PARA_INF_FILE,IDENTITY_AUTH_TIME_ESAM, 2, 0)!=OK)
                {
                   ASSERT_FAILED();
                   return ERR;
                }
                Reverse_data((unsigned char *) &receive_send_buffer[0],2);
                //ValidTimeTemp=Bcd2Hex((unsigned char *)&ValidTimeTemp , 2);
                ValidTimeTemp=Bcd2Hex((unsigned char *) &receive_send_buffer[0], 2);
                if(ValidTimeTemp EQ 0 )
                {
                   ValidTimeTemp=5;
                }
                Reset_Pay_Timer(ValidTimeTemp*60);// Reset_Pay_Timer(0);
		return OK;
	}
        ASSERT_FAILED();
	IDENTITY_AUTH_ERR_DEFINE = 1;
	return ERR;
}
///
unsigned char Far_Read_Esam(unsigned char cla,unsigned char ins,unsigned char t_p1,
              unsigned char t_p2,unsigned char lc,unsigned char *address)
{
	unsigned char Order_Head[4];

	My_memcpyRev( Card_WR_Buff, (unsigned char *)&Far_Identity_Auth_Data.Instruction.random_number1[4], 4);
        //
	*(Card_WR_Buff+4)=0x04;
	*(Card_WR_Buff+5)=0xd6;
	*(Card_WR_Buff+6)=0x86;	//guding
	if( ins == Read_Record )
		*(Card_WR_Buff+7)=0;		//guding
	else
		*(Card_WR_Buff+7)=t_p2;
	Card_WR_Buff[8]=lc+12;	//data+mac+disperse_gene
	My_memcpyRev(Card_WR_Buff+9, (unsigned char *)&Far_Identity_Auth_Data.Instruction.disperse_gene[0], 8);
        //明文+mac+离散读
	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,0x11,Card_WR_Buff,0,CommunicationPortMode,lc+4)!= OK )
	{
                  ASSERT_FAILED();
		  OTHER_ERR_DEFINE =1;
	          return ERR;
	}

	return OK;
}
///
/*"**************************************************************************"*/
/*" 写ESAM卡 ，带MAC  写"*/
unsigned char Far_Write_Esam(unsigned char cla,unsigned char ins,unsigned char t_p1,
			unsigned char t_p2,unsigned char lc,unsigned char *address,unsigned char Flag )
{
	unsigned char i;   
	unsigned char Order_Head[4];
       // INT8U  MyMac[4];
 
	CPU_ESAM_CARD_Control(ESAM);

	if( Flag )
	{        //针对密钥信息数据，前面4个字节为mac 后4个为数据 ，    
                  //然后在主站信息来了后，写数据时，要反转mac，数据，又要把mac和数据的位置交换的情况
		My_memcpyRev( Card_WR_Buff , address,lc+4);
	}
	else
	{
                //一般情况下，前面为数据， 后面为mac  
		My_memcpyRev( Card_WR_Buff, address,lc);
		My_memcpyRev(Card_WR_Buff+lc, address+lc,4);
        }

	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,lc+4,Card_WR_Buff,0,CommunicationPortMode,0)!= OK ){
		ESAM_AUTH_ERR_DEFINE =1;
		FarPrePayment.ID_Ins_Counter++;
                Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, &FarPrePayment.ID_Ins_Counter, 1);
		if((FarPrePayment.ID_Ins_Counter %3)==0 ||  FarPrePayment.ID_Ins_Counter >=15){
                        Reset_Pay_Timer(0);
			Far_Identity_Auth_Ok_Flag=0;
	                Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,receive_send_buffer,receive_send_buffer,Length_receive_send_buffer );

		}
                ASSERT_FAILED();
		return ERR;
	}
        FarPrePayment.ID_Ins_Counter  =0;
	Write_Storage_Data(_SDI_INVALID_COUNTS_AllOW, &FarPrePayment.ID_Ins_Counter, 1);
	return OK;
}
unsigned char Far_Esamcard_Internal_Auth(unsigned char *Point)   //远程系统身份认证//
	{
	My_memcpyRev(Card_WR_Buff+110, Point, 8);       //"转移密文1//  
	My_memcpyRev(Card_WR_Buff+100, Point+8, 8);    //"转移随机数1//   
	My_memcpyRev(Card_WR_Buff+1, Point+16, 8);     //转分散因子1//  

	CPU_ESAM_CARD_Control(ESAM);      //"串口通向ESAM卡"//
	Internal_Auth(0x80,0xfa,0,3,8,Card_WR_Buff+1); //分散//
	if( Judge_Return_Flag() )
        {
          ASSERT_FAILED();
           return ERR;
        }
		

	Internal_Auth(0x80,0xfa,0,0,8,Card_WR_Buff+100); //得到ESAM加密随机数 //
	if( Judge_Return_Flag() )
        {
           ASSERT_FAILED();
           return ERR;
        }
		

	if(My_Memcmp(Card_WR_Buff+110,receive_send_buffer,8))  {
                ASSERT_FAILED();
		return ERR;      
	}
        //对整个Far_Identity_Auth_Data进行初始化，而不是部分，使用时需要反相
	My_Memcpy((unsigned char *)&Far_Identity_Auth_Data.Instruction.cryptograph1[0], Point, sizeof(struct Authentication_Instruction));
	return OK;  /*"内部认证结束"*/  
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*"**************************************************************************"*/
/*" 数据回抄"*/
/*" 支持07800101,078001FF "*/
/*" Data_Point:入:8字节数据回抄标识 "*/
/*"            出:8字节数据回抄标识+回抄的数据+MAC "*/
/*"**************************************************************************"*/
struct Far_Read_078001FF_Format
	{
	unsigned int	Data_Length;
	unsigned int	Data_Start_Addr;
	unsigned int	File;
	unsigned int	Name;
	};

unsigned char Far_Deal_078001FF(unsigned char *Data_Point ){
	struct Far_Read_078001FF_Format	 Far_Read_078001FF_Format;
	unsigned char Offset;
        mem_cpy(&Far_Read_078001FF_Format,Data_Point,sizeof(struct Far_Read_078001FF_Format),&Far_Read_078001FF_Format,sizeof(Far_Read_078001FF_Format));

	if( (unsigned char)(Far_Read_078001FF_Format.File) == 0x01 ){
		if( (unsigned char)(Far_Read_078001FF_Format.Data_Start_Addr )== 0x00 )
			Offset = 0x01;
		else
			Offset = 0x03;
		if(Far_Read_Esam(                                       0x04,Read_Record,Offset,
							                                    0x0C,
					   (unsigned char)(Far_Read_078001FF_Format.Data_Length), 
						              			 Data_Point)!=OK)
                {
                    ASSERT_FAILED();
                    return ERR;  
                }
			
	}
	else{
/*"04b082（83，84，86）+ P2(偏移地址)＋11+4字节随机数1+04d686+00+LC+8字节分散因子。
LC是所要读取的明文数据＋MAC+分散因子的总长度，它是1字节的十六进制数。"*/

		if(Far_Read_Esam(0x04,Read_Binary,0x80+(unsigned char)(Far_Read_078001FF_Format.File),
											 (unsigned char)(Far_Read_078001FF_Format.Data_Start_Addr),
											 (unsigned char)(Far_Read_078001FF_Format.Data_Length), 
											 Data_Point)!=OK)
                {
                   ASSERT_FAILED();
                   return ERR;
                }
			
	}
        //组装发送的数据域，不管数据标示，/////////0x33类型函数中转站, 0x33类型的函数，的数据域的入口参数数据都为除去数据标示和操作者代码的 数据域，
//出口都为：也不要管数据标示，的直接存放在FarPaidBuff
        mem_cpy(FarPaidBuff,Data_Point,8,FarPaidBuff,Length_FarPaidBuff);//8字节数据回抄标识
	My_memcpyRev( FarPaidBuff+8,receive_send_buffer,((unsigned char)(Far_Read_078001FF_Format.Data_Length)) );
	My_memcpyRev( FarPaidBuff+8+((unsigned char)(Far_Read_078001FF_Format.Data_Length)),receive_send_buffer+((unsigned char)(Far_Read_078001FF_Format.Data_Length)), 4);
	FarPrePayment.Far_SendLen = 8+((unsigned char)(Far_Read_078001FF_Format.Data_Length))+4;

	
//	My_memcpyRev( far_data_p+14,receive_send_buffer,((unsigned char)(Far_Read_078001FF_Format->Data_Length)) );
//	My_memcpyRev( far_data_p+14+((unsigned char)(Far_Read_078001FF_Format->Data_Length)),receive_send_buffer+((unsigned char)(Far_Read_078001FF_Format->Data_Length)), 4);
//	Co.c.len = ((unsigned char)(Far_Read_078001FF_Format->Data_Length))+4;
	return OK;
	}

/*"**************************************************************************"*/
/*" 查询状态"*/
/*" 支持07810201 "*AppointTrasfPortBuff*/
/*" Data_Point:入:无 "*/
/*"            出:数据格式见下 FarPaidBuff,FarPrePayment.Far_SendLen"*/
/*"**************************************************************************"*/
struct Far_Read_07810201_Format
	{
	unsigned long	Remain_Money;
	unsigned char	Remain_Money_Mac[4];
	unsigned long	Buy_Count;
	unsigned char	Buy_Count_MAC[4];
	unsigned char Client_ID[6];
	unsigned char Password_Info[4];
	};
#define LENGTH_FAR_READ_07810201_FORMAT  sizeof( struct Far_Read_07810201_Format )
//-----------------------------------------------------------------------------
unsigned char Far_Deal_07810201(unsigned char *Data_Point )
{
	struct Far_Read_07810201_Format	 Far_Read_07810201_Format;
        //mem_cpy(&Far_Read_07810201_Format,Data_Point,sizeof(Far_Read_07810201_Format),&Far_Read_07810201_Format,sizeof(Far_Read_07810201_Format));
	//Esam_Remain_Money_Dec();
        //组装剩余金额文件
	if(Far_Read_Esam(0x04,Read_Record,1,0x0c,4,0)!=OK)
        {
          ASSERT_FAILED();
          return ERR;
        }
		
	My_memcpyRev((unsigned char *)&(Far_Read_07810201_Format.Remain_Money), receive_send_buffer,4);
	My_memcpyRev((unsigned char *)&(Far_Read_07810201_Format.Remain_Money_Mac[0]), receive_send_buffer+4,4);
	//组装购电次数
	if(Far_Read_Esam(0x04,Read_Record,3,0x0c,4,0)!=OK)
		return ERR;
	My_memcpyRev((unsigned char *)&(Far_Read_07810201_Format.Buy_Count), receive_send_buffer,4);
	My_memcpyRev((unsigned char *)&(Far_Read_07810201_Format.Buy_Count_MAC[0]), receive_send_buffer+4,4);
        //组装客户编号
	if( Get_File_Data(ESAM,ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,6,(unsigned char *)&(Far_Read_07810201_Format.Client_ID[0])) != OK )
		return ERR;

	Reverse_data((unsigned char *)&(Far_Read_07810201_Format.Client_ID[0]),6);
	//组装远程密钥信息
	if( Get_File_Data(ESAM,ESAM_FAR_PASSWORD_INF_FILE,0,4,(unsigned char *)&(Far_Read_07810201_Format.Password_Info[0])) != OK )
		return ERR;

	Reverse_data((unsigned char *)&(Far_Read_07810201_Format.Password_Info[0]),4); 
        
        mem_cpy(FarPaidBuff,(INT8U *)&Far_Read_07810201_Format,sizeof(struct Far_Read_07810201_Format),FarPaidBuff,Length_FarPaidBuff);
	FarPrePayment.Far_SendLen= LENGTH_FAR_READ_07810201_FORMAT;
	
	return OK;
}
/*"**************************************************************************"*/
/*" 查询状态"*/
/*" 支持078102FF "*/
/*" Data_Point:入:无 "*/
/*"            出:数据格式见下 "*/
/*"**************************************************************************"*/
unsigned  char Far_Deal_078102FF(unsigned char * Data_Point )
	{
	return Far_Deal_07810201(Data_Point);
	}
/*"**************************************************************************"*/
/*" 身份认证时效设置"*/
/*" 支持070001FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出:0字节 "*/ 
struct Far_Deal_070001FF_format
	{
	unsigned int Identity_Limit;
	unsigned char Identity_Limit_Mac[4];
	};
#define LENGTH_FAR_DEAL_070001FF_FORMAT      sizeof(struct Far_Deal_070001FF_format)
//-----------------------------------------------------------------------------
unsigned char Far_Deal_070001FF(unsigned char * Data_Point ){
        INT16U ValidTimeTemp;
	struct Far_Deal_070001FF_format   Far_Deal_070001FF_format;
	mem_cpy(&Far_Deal_070001FF_format,Data_Point,sizeof(Far_Deal_070001FF_format),&Far_Deal_070001FF_format,sizeof(Far_Deal_070001FF_format));
//	Reverse_data((unsigned char *)&(Far_Deal_070001FF_format->Identity_Limit),2)
//	Reverse_data((uns igned char *)&(Far_Deal_070001FF_format->Identity_Limit_Mac[0]),4)

	if( Far_Deal_070001FF_format.Identity_Limit == 0 )
        {
            return ERR;
        }
	//把 从主站传来的认证时效值 写到esam中去
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_PARA_INF_FILE,IDENTITY_AUTH_TIME_ESAM,0x02,Data_Point,0)!=OK)
        {
                ASSERT_FAILED();
		return ERR;
	}//
        //读取esam中的认证时效值，
	if(Far_Read_Esam(04,Read_Binary,0x80+ESAM_PARA_INF_FILE,IDENTITY_AUTH_TIME_ESAM, 2, 0)!=OK)
        {
           ASSERT_FAILED();
           return ERR;
        }
        Reverse_data((unsigned char *) &receive_send_buffer[0],2);	
        
        ValidTimeTemp=Bcd2Hex((unsigned char *) &receive_send_buffer[0], 2);
        if(ValidTimeTemp EQ 0 )
        { 
            ValidTimeTemp=5;
        }
        //设置 认证时效
        Reset_Pay_Timer(ValidTimeTemp*60);
	FarPrePayment.Far_SendLen  = 0;
	
	return OK;
}//
///////////////
/*"**************************************************************************"*/
/*" 身份认证失效"*/
/*" 支持07000201 "*/
/*" Data_Point:入:无数据"*/
/*"            出:数据格式见下 "FarPaidBuff,FarPrePayment.Far_SendLen*/
//-----------------------------------------------------------------------------
struct Far_Deal_07000201_format
	{
	unsigned char Client_ID[6];
	unsigned long	Remain_Money;
	unsigned long	Buy_Count;
	unsigned char Password_Info[4];
	};
#define LENGTH_FAR_DEAL_07000201_FORMAT      sizeof(struct Far_Deal_07000201_format)
unsigned char Far_Deal_07000201(unsigned char * Data_Point ){
	struct Far_Deal_07000201_format   Far_Deal_07000201_format;

	//mem_cpy(&Far_Deal_07000201_format,Data_Point,sizeof(Far_Deal_07000201_format),&Far_Deal_07000201_format,sizeof(Far_Deal_07000201_format));
	// 从esam取出剩余金额数据
	if(Far_Read_Esam(0x04,Read_Record,1,0x0c,4,0)!=OK)
		return ERR;
	My_memcpyRev((unsigned char *)&(Far_Deal_07000201_format.Remain_Money), receive_send_buffer,4);
	//从esam中取出购电次数数据
	if(Far_Read_Esam(0x04,Read_Record,3,0x0c,4,0)!=OK)
		return ERR;
	My_memcpyRev((unsigned char *)&(Far_Deal_07000201_format.Buy_Count), receive_send_buffer,4);
        //得到客户编号数据
	if( Get_File_Data(ESAM,ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,6,(unsigned char *)&(Far_Deal_07000201_format.Client_ID[0])) != OK )
		return ERR;
 
	Reverse_data((unsigned char *)&(Far_Deal_07000201_format.Client_ID[0]),6);
	//得到密钥信息
	if( Get_File_Data(ESAM,ESAM_FAR_PASSWORD_INF_FILE,0,4,(unsigned char *)&(Far_Deal_07000201_format.Password_Info[0])) != OK )
		return ERR;

	Reverse_data((unsigned char *)&(Far_Deal_07000201_format.Password_Info[0]),4);
        //把 身份认证时效清0 ， 身份认证标志位清0
	Far_Identity_Auth_Ok_Flag=0;
        Reset_Pay_Timer(0);
        mem_cpy(FarPaidBuff,&Far_Deal_07000201_format,sizeof(Far_Deal_07000201_format),FarPaidBuff,Length_FarPaidBuff);
        //esam下电
	Cpu_Esam_All_Operate(ESAM,CPU_ESAM_DRV_POWER_OFF,receive_send_buffer,receive_send_buffer,Length_receive_send_buffer );
//	cpucard_serial_release();
	FarPrePayment.Far_SendLen= sizeof(struct Far_Deal_07000201_format);
	//Co.c.len = LENGTH_FAR_DEAL_07000201_FORMAT;
	return OK;
}
/*"**************************************************************************"*/
/*" 身份认证失效"*/
/*" 支持07000201 "*/
/*" Data_Point:入:wu"*/
/*"            出:数据格式见下 "*/
//-----------------------------------------------------------------------------
unsigned char Far_Deal_070002FF(unsigned char * Data_Point )
	{
	return Far_Deal_07000201(Data_Point);
	}


/*"**************************************************************************"*/
/*" 开户"*/
/*" 支持070101FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出:无数据"FarPrePayment.Far_SendLen*/
//-----------------------------------------------------------------------------
struct Far_Deal_070101FF_format
	{
	unsigned long	Remain_Money;//正常顺序的，判断时不要反转
	unsigned long	Buy_Count;//正常顺序的
	unsigned char BagMoney_Mac[4];//正常顺序的
	unsigned char Client_ID[6];//  因为传过来的是反得顺序表   中一  直保存的是正常顺序
	unsigned char Client_ID_Mac[4];//
	};
#define LENGTH_FAR_DEAL_070101FF_FORMAT      sizeof(struct Far_Deal_070101FF_format)
unsigned char Far_Deal_070101FF(unsigned char * Data_Point )
{
	struct Far_Deal_070101FF_format  Far_Deal_070101FF_format;
	struct Moneybag_Data Moneybag_Data;

	mem_cpy(&Far_Deal_070101FF_format,Data_Point,sizeof(Far_Deal_070101FF_format),&Far_Deal_070101FF_format,sizeof(Far_Deal_070101FF_format));
	
        C_Read_Storage_Data( _SDI_PREPAID_RUN_STATUS, &Pre_Payment_Para.Meter_Run_State ,  &Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State)  );    
     	if( Pre_Payment_Para.Meter_Run_State!=MeterRunState_Test_0 )
		return ERR;
        //读钱包文件并反相
	if( Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data) != OK )
		return ERR;
        // 判断购电次数
	if( Far_Deal_070101FF_format.Buy_Count != (Moneybag_Data.Buy_Count+1))
	{
		BUY_COUNT_ERR_DEFINE=1 ;
		return ERR;
	}
        //这个 函数会自动反相数据然后写到esam，但是数据本身不会反转
	CPU_ESAM_CARD_Control(ESAM);
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,0x06,(Far_Deal_070101FF_format.Client_ID),0)!=OK)
        {
           ASSERT_FAILED();
           return ERR;
        }
	//判断本次购电的囤积门限、、//
	if( Check_Buy_Money_Exceed_Limit(Far_Deal_070101FF_format.Remain_Money) )
	{
                ASSERT_FAILED();
		BUY_MONEY_OVER_ERR_DEFINE=1;
		return ERR;
	}

	Reverse_data((unsigned char *)&(Far_Deal_070101FF_format.Remain_Money),4);
	Reverse_data((unsigned char *)&(Far_Deal_070101FF_format.Buy_Count),4);
	Reverse_data((unsigned char *)&(Far_Deal_070101FF_format.BagMoney_Mac[0]),4);
	if( Write(0x84,Increase,0x01,0x0C,0x0C,((unsigned char *)&Far_Deal_070101FF_format.Remain_Money))!=OK)
	{
            ASSERT_FAILED();  
	    return ERR;
	}
	Reverse_data((INT8U *)&(Far_Deal_070101FF_format.Remain_Money),4);
	Reverse_data((unsigned char *)&(Far_Deal_070101FF_format.Buy_Count),4);
        //剩余金额必须保持 更新， 这个变量，在后面的扣款中会用到
        //mem_cpy((INT8U*)&Moneybag_Data.Remain_Money,(INT8U *)&(Far_Deal_070101FF_format.Remain_Money),4,(INT8U)&Moneybag_Data.Remain_Money,4);
        Meter_Money_And_Count_Updata(Far_Deal_070101FF_format.Remain_Money,Far_Deal_070101FF_format.Buy_Count );
	
        //这个全局变量必须更新 后面会用到,这里客户编号使用被反相了两次， 所这里使用正常顺序到e方
	My_memcpyRev(Pre_Payment_Para.UserID,Far_Deal_070101FF_format.Client_ID,6);
	Write_Storage_Data(SDI_CUTOMER_ID , Pre_Payment_Para.UserID , 6);
	Pre_Payment_Para.Meter_Run_State=0x03;
	Write_Storage_Data(_SDI_PREPAID_RUN_STATUS  ,&Pre_Payment_Para.Meter_Run_State , 1);
        //告诉黄工，修改了 数据
        Card_Set_Para_Notice();
        FarPrePayment.Far_SendLen=0;            
	return OK;
}
///////////
/*"**************************************************************************"*/
/*" 充值"*/
/*" 支持070102FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出: 0 "FarPrePayment.Far_SendLen*/
//-----------------------------------------------------------------------------

struct Far_Deal_070102FF_format
	{
	unsigned long	Remain_Money;//传过来的为正常顺序 比较实，不要反相
	unsigned long	Buy_Count;//传过来的为正常顺序 比较实，不要反相
	unsigned char BagMoney_Mac[4];//传过来的为正常顺序 比较实，不要反相
	unsigned char Client_ID[6];//传过来的为正常顺序 比较实， 要反相，因为，表中保存的反得, 保存反相后的
	unsigned char Client_ID_Mac[4];//传过来的为正常顺序 比较实， 要反相
	};
#define LENGTH_FAR_DEAL_070102FF_FORMAT      sizeof(struct Far_Deal_070102FF_format)
unsigned char Far_Deal_070102FF(unsigned char * Data_Point )
{
	struct Far_Deal_070102FF_format    Far_Deal_070102FF_format;
	struct Moneybag_Data Moneybag_Data;
        
        C_Read_Storage_Data( _SDI_PREPAID_RUN_STATUS, &Pre_Payment_Para.Meter_Run_State ,  &Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State)  ); 
	if( Pre_Payment_Para.Meter_Run_State!=MeterRunState_Run_3 ) 	
        {
           ASSERT_FAILED();
           return ERR;
        }
		
        // 读ESAM钱包文件剩余电费和购电次数 并反相
	if( Read_Esam_Moneybag_File((unsigned char *)&Moneybag_Data) != OK )
        {
           ASSERT_FAILED();
           return ERR;
        }
	mem_cpy(&Far_Deal_070102FF_format,Data_Point,sizeof(Far_Deal_070102FF_format),&Far_Deal_070102FF_format,sizeof(Far_Deal_070102FF_format));
	
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Client_ID[0]),6);
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Client_ID_Mac[0]),4);
        // 比较客户编号， 在e方中 
        C_Read_Storage_Data( SDI_CUTOMER_ID, Pre_Payment_Para.UserID,  Pre_Payment_Para.UserID,sizeof(Pre_Payment_Para.UserID)  ); 
	if( My_Memcmp(Pre_Payment_Para.UserID,&Far_Deal_070102FF_format.Client_ID[0],6) != 0 )
        {
                ASSERT_FAILED();
		CLIENT_ID_ERR_DEFINE = 1;
		return ERR;
	}

	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Client_ID[0]),6);
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Client_ID_Mac[0]),4);
         
	CPU_ESAM_CARD_Control(ESAM);
        //???这个为什么要更新客户编号到esam，而不更新e方的
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_PARA_INF_FILE,CLIENT_ID_ESAM,0x06,(Far_Deal_070102FF_format.Client_ID),0)!=OK)
        {
          ASSERT_FAILED();
          return ERR;
        }
		
 
	if( Far_Deal_070102FF_format.Buy_Count == Moneybag_Data.Buy_Count)
        {
                ASSERT_FAILED();
		REPEAT_INCREASE_ERR_DEFINE = 1;
		return ERR;
	}
	
	if( Far_Deal_070102FF_format.Buy_Count != (Moneybag_Data.Buy_Count+1))
        {
                ASSERT_FAILED();
		BUY_COUNT_ERR_DEFINE = 1;
		return ERR;
	}

	//判断本次购电的囤积门限 //
	if( Check_Buy_Money_Exceed_Limit(Far_Deal_070102FF_format.Remain_Money) )
        {
                ASSERT_FAILED();
		BUY_MONEY_OVER_ERR_DEFINE=1;
		return ERR;
	}

	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Remain_Money),4);
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Buy_Count),4);
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.BagMoney_Mac[0]),4);
        //判断完毕，开始正式充值
	if( Write(0x84,Increase,0x01,0x0C,0x0C,((unsigned char *)&Far_Deal_070102FF_format.Remain_Money))!=OK)
        {
                ASSERT_FAILED();
		return ERR;
	}
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Remain_Money),4);
	Reverse_data((unsigned char *)&(Far_Deal_070102FF_format.Buy_Count),4);
	Meter_Money_And_Count_Updata(Far_Deal_070102FF_format.Remain_Money,Far_Deal_070102FF_format.Buy_Count );
//	if( Far_Write_Esam(0x04,Update_Binary,0x82,0x05,0x06,(Far_Deal_070102FF_format->Client_ID))!=OK)
//		{
//		return ERR;
//		}
	FarPrePayment.Far_SendLen = 0;
	return OK;
}
///////////
/*"**************************************************************************"*/
/*" 密钥更新"*/
/*" 支持070201FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出:无，  FarPrePayment.Far_SendLen=0"*/
//-----------------------------------------------------------------------------
struct Far_Deal_070201FF_format
	{
	unsigned char PassWord_Inf[8];//4个字节密钥信息， 4个字节mac
//	unsigned char PassWord_Inf_Mac[4];
	unsigned char PassWord[32];
	};
#define LENGTH_FAR_DEAL_070201FF_FORMAT      sizeof(struct Far_Deal_070201FF_format)
unsigned char Far_PassWord_Updata(unsigned char * Data_Point,unsigned char PassWord_ID )
{
	struct Far_Deal_070201FF_format   Far_Deal_070201FF_format;
	unsigned char PassWord_Inf[4];//本地的esam的远程密钥信息文件

	mem_cpy(&Far_Deal_070201FF_format,Data_Point,sizeof(Far_Deal_070201FF_format),&Far_Deal_070201FF_format,sizeof(Far_Deal_070201FF_format)); 
	if(OK != Get_File_Data(ESAM,ESAM_FAR_PASSWORD_INF_FILE,0,4,&PassWord_Inf[0])){
            ASSERT_FAILED();
            return ERR;
        }
         
   
	Reverse_data(Far_Deal_070201FF_format.PassWord_Inf,8);
        //假如要更新的密钥不为 控制密钥，  主站传过来的数据密钥信息前4个字节不为0 
	if( PassWord_ID!=2 ||  ( Far_Deal_070201FF_format.PassWord_Inf[0] !=0 || Far_Deal_070201FF_format.PassWord_Inf[1] !=0 ||
		Far_Deal_070201FF_format.PassWord_Inf[2] !=0 || Far_Deal_070201FF_format.PassWord_Inf[3] !=0 ) )
	{
                //密钥标示要对， 密钥更新方式要为远程， 密钥版本应该比esam中的大
		if( Far_Deal_070201FF_format.PassWord_Inf[2] !=PassWord_ID || 
			 Far_Deal_070201FF_format.PassWord_Inf[1] != 1 ||
			 Far_Deal_070201FF_format.PassWord_Inf[3] <= PassWord_Inf[3] )
                {
                  ASSERT_FAILED();
                  return ERR;
                }
			
	}
	Reverse_data(Far_Deal_070201FF_format.PassWord_Inf,8);
	
	CPU_ESAM_CARD_Control(ESAM);
	Reverse_data((unsigned char *)&(Far_Deal_070201FF_format.PassWord[0]),32);
	if( Write(0x84,Write_Key,0x01,0xFF,0x20,(Far_Deal_070201FF_format.PassWord))!=OK)
		{
                ASSERT_FAILED();  
		return ERR;
		}
	if( Far_Write_Esam(0x04,Update_Binary,0x80+ESAM_FAR_PASSWORD_INF_FILE,0x00,0x04,(Far_Deal_070201FF_format.PassWord_Inf),0xFF)!=OK)  
        {      
                ASSERT_FAILED();
		return ERR;
	}
	FarPrePayment.Far_SendLen=0;
	return OK;
}
/*"**************************************************************************"*/
/*" 控制命令密钥更新 "*/
/*" 支持070202FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出:数据格式见下 "*/
//-----------------------------------------------------------------------------
unsigned char Far_Deal_070201FF(unsigned char * Data_Point )
	{
	return Far_PassWord_Updata(Data_Point,2);
	}
/*"**************************************************************************"*/
/*"参数密钥更新"*/
/*" 支持070202FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出:数据格式见下 "*/
//-----------------------------------------------------------------------------
unsigned char Far_Deal_070202FF(unsigned char * Data_Point )
	{
	return Far_PassWord_Updata(Data_Point,1);
	}
/*"**************************************************************************"*/
/*"远程身份认证密钥更新"*/
/*" 支持070203FF "*/
/*" Data_Point:入:数据格式见下 "*/
/*"            出:数据格式见下 "*/
//-----------------------------------------------------------------------------
unsigned char Far_Deal_070203FF(unsigned char * Data_Point )
	{
	return Far_PassWord_Updata(Data_Point,3);
	}

//控制命令解密， 645帧的L字段 固定长度为 28 ， 解密后的实际 数据长度为8， 这部分全部由黄工管，我只管解密
INT8U Esam_Decrypt(INT8U *pSrc, INT16U SrcLen)
{
  
  CPU_ESAM_CARD_Control(ESAM);
  if( Select_File(0,0x3F,0) != OK )
  {
      ASSERT_FAILED();
      Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
      return 0;
  }
  //查看 身份认证有效时间有没有到
  Far_Identity_Auth_Ok_Flag=!Chk_Pay_Time_Arrive();
  if(Far_Identity_Auth_Ok_Flag != 1)
  {
           Reset_Pay_Timer(0);
           ASSERT_FAILED();
           return 0;
  }  
  if(28 !=  (SrcLen) )
  {
     ASSERT_FAILED();
     return 0;
  }  
  Reverse_data( pSrc+8,20);       
  if( Write(0x04,0xD6,0x88,0x00,0x14,pSrc+8 )==OK){
           if( Read(0,Read_Binary,0x88,0,8) == OK ){
		My_Memcpy(pSrc + 8,receive_send_buffer, 8);
	   }else{
              return 0;
           }
  }else
  {
        ASSERT_FAILED();
	ESAM_AUTH_ERR_DEFINE=1;
        return 0;
  }
  return 1;
}
//
INT16U GetSecurity_Auth_Err_Info(void)
{
  
      INT16U Temp;
      if(( Far_Security_Auth_Err_Info.intd & 0xFFFE ) != 0 )
		Far_Security_Auth_Err_Info.intd &= 0xFFFE;
      else{
            OTHER_ERR_DEFINE =1;
      }
      Temp=Far_Security_Auth_Err_Info.intd;
      return Temp;
    
}
//判断是否 远程身份有效， 给别人调
//返回1  处于，  0 不处于
INT8U Check_Remote_Prog_Status()
{
  if(Chk_Pay_Time_Arrive())
  {
     return 0;
  }else{
     return 1;
  }

}
////////////////
 