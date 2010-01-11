
#ifndef CPUCARD_BASE_H__
#define CPUCARD_BASE_H__
/**********************************************************************************
函数功能：对 CPU卡,ESAM的底层操作,包括OPERATE_RST_COOL等.
入口：
          Type------------CPU卡,ESAM的类型;
          Operate---------表对 CPU卡,ESAM的操作动作类型,如 OPERATE_RST_COOL 等;
          pDst------------对 CPU卡,ESAM的操作后,获取的数据内容放置缓冲区; 
                          对于 PAY_CPU_CARD的冷复位，返回8字节的离散因子。
                          对于其他介质的其他类型操作，暂无返回数据，后期按需增加。
          pDstStart-------对 CPU卡,ESAM的操作后,获取的数据内容放置缓冲区头地址,与pDst,MaxDstLen一起限定越界. 
          MaxDstLen-------pDstStart目标缓冲区的数据最大长度.
出口： CPU,ESAM操作宏.
**********************************************************************************/ 
INT8U Convert_Dis_Code(void);
INT8U GetCardKind(void);
#define GetCardKind() (CardType)
//INT8U Cpu_Esam_All_Operate(INT8U Type,INT8U Operate,INT8U *pDst,INT8U *pDstStart,INT16U MaxDstLen);
 void PrintErrState(void );
void My_Memcpy(INT8U *pDst,INT8U *pSrc,INT8U length);
/*"将原数据前后倒置地复制到目标数据"*/
void My_memcpyRev(INT8U *to,INT8U *from,INT8U len);
/*"将数据前后倒置"*/
void Reverse_data(INT8U *data, INT16U len);
INT8U Judge_Return_Flag(void);
INT8U My_Memcmp(INT8U *to,INT8U *from,INT8U lc);// if(My_Memcmp(receive_send_buffer+110,receive_send_buffer,8))  
void CPU_ESAM_CARD_Control(INT8U Direct);//方向选择， 是发给esam还是cpu卡

INT8U Internal_Auth(INT8U,INT8U,INT8U,INT8U,INT8U,INT8U *);
                                               /*" 内部命令，不公开 "*/
INT8U External_Auth(INT8U ,INT8U ,INT8U *);
                                               /*" 内部命令，不公开 "*/
INT8U Select_File(INT8U ,INT8U ,INT8U );
                                               /*" 文件选择命令，用于选择ESAM或CPU卡中的某个文件 "*/
                                               /*" 参数有待讨论 "*/
INT8U Read(INT8U ,INT8U ,INT8U ,INT8U ,INT8U );
                                               /*" 内部命令，不公开 "*/
INT8U Write(INT8U,INT8U,INT8U,INT8U,INT8U,INT8U *);
                                               /*" 内部命令，不公开 "*/

/*"**************************************************************************"*/
/*" 功能：CPU卡底层读写函数 "*/
/*" 文件名：CPU_Card_Driver "*/
/*" Order_Head：命令头域 "*/
/*" 包括：CLA  INS  P1  P2  "*/
/*" Length_LC：写数据长度   "*/
/*" W_Data：写数据 "*/
/*" Length_LE: 读数据长度 "*/
/*" Change_Door: 读写通道 ESAM还是CPU "*/
/*" Spec_Length_LE: 特殊的 后续数据帧长度,0:表示无特殊长度，直接取61 XX,"*/
/*" 非0表示为特殊后续数据帧，不取61 XX "*/
INT8U  CPU_Card_Driver(const INT8U *Order_Head,
						     INT8U Length_LC,
			                             INT8U *W_Data,
			                             INT8U Length_LE,
			                             INT8U Change_Door,
			                             INT8U Spec_Length_LE);
/*"**************************************************************************"*/
/*" 判断卡是否在 "*/
#define Check_Cpu_Card_Out() ((JUDGE_CPU_INSERT)?(OK):(ERR))
/*"**********************************************************************************"*/

/*"**************************************************************************"*/
/*" 接收、判断CPU卡复位应答信号 "*/
INT8U Cpucard_Reset(void);
	
/*"**************************************************************************"*/
/*"接收、判断SAM卡复位应答信号"*/                                                                  
INT8U Esamcard_Reset(void);

INT8U  WhenCardInsertedInitPrePayData(void);//上电从e方读取数据到全局变量
 

#endif
