#include "MyIncludesAll.h"
#undef Debug_Print
//#define Debug_Print(...)
#define Debug_Print _Debug_Print

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// 延时_64us个64us //      
void My_Memcpy(INT8U *pDst,INT8U *pSrc,INT8U length){
   INT8U i;   
   for(i=0;i<length;i++)
   {
      *pDst=*pSrc;
      pDst++;
      pSrc++;
   }

}
//
/*"将原数据前后倒置地复制到目标数据"*/
void My_memcpyRev(unsigned char *to,unsigned char *from,unsigned char len){	
	unsigned char i;	
	for(i=0;i<len;i++)
		*(to+i)=*(from+len-1-i);
}
//ASSERT_FAILED();
/*******************************************************************************/	
/*"将数据前后倒置"*/
void Reverse_data(unsigned char *data, unsigned int len)
	{
	unsigned char c_temp;
	unsigned char *pc_temp;
	unsigned int i;
	
	pc_temp=data;
	pc_temp+=len-1;
	for(i=0;i<len/2;i++)
		{
		c_temp=*data;
		*data=*pc_temp;
		*pc_temp=c_temp;
		data++;
		pc_temp--;
		}
	}
//返回0相等， 返回1大于， 返回2小于
unsigned char My_Memcmp(unsigned char *to,unsigned char *from,unsigned char lc)
    {	
    unsigned char count,flag;
    flag=0;
    for(count=0;count<lc;count++)
        {
       
        if( *(to+count) > *(from+count) )
            {
            flag=1;//
            break;
            }
        else if( *(to+count) < *(from+count) )
            {
            flag=2;
            break;
            }
        } 
    return(flag); 
    }
/*" 判断返回标志的合法性 "*/    
unsigned char Judge_Return_Flag(void)
    {
    if(Card_Error_State.CardErrorState_INT32U)
        {
        return ERR;
        }
    /*
    if(Check_CPU_Occur())			
        {
        ASSERT_FAILED();
        Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
        return ERR;
        }*/
    return OK;
    }
//
void CPU_ESAM_CARD_Control(INT8U Direct)//方向选择， 是发给esam还是cpu卡
{
   CommunicationPortMode=Direct;

}


/*"**************************************************************************"*/
/*"内部认证，CPU卡0x0088,ESAM卡0x80fa;p1:为0时加密,为1时解密；p2:密钥标识号"*/                 
/*"address为需要加密的数据首地址"*/                                                                                
unsigned char Internal_Auth(unsigned char cla,unsigned char ins,unsigned char t_p1,
              unsigned char t_p2,unsigned char lc,unsigned char *address)
    {
	unsigned char Order_Head[4];

	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,lc,address,0,CommunicationPortMode,0)== OK )
		return OK;
        ASSERT_FAILED();
	Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR=1;
        return ERR;
    }

/*"**************************************************************************"*/
/*"外部认证，p2:密钥标识号, address为需要解密的数据首地址"*/
unsigned char External_Auth(unsigned char t_p2,unsigned char lc,unsigned char *address)
    {
	unsigned char Order_Head[4];

	Order_Head[0] = 0x00;
	Order_Head[1] = 0x82;
	Order_Head[2] = 0x00;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver((const unsigned char *)Order_Head,lc,address,0,CommunicationPortMode,0)== OK )
		return OK;
        ASSERT_FAILED();
	Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR=1;
        return ERR;
    }

//**************************************************************************
/*"cpu卡：文件选择 :3f01 "*/
unsigned char Select_File(unsigned char t_p1,unsigned char date1,unsigned char date2)
    {
		unsigned char Order_Head[4];
		unsigned char W_Data[2];
		
		Order_Head[0] = 0;
		Order_Head[1] = 0xa4;
		Order_Head[2] = 0;
		Order_Head[3] = 0;
		W_Data[0] = date1;
		W_Data[1] = date2;
		if( CPU_Card_Driver((const unsigned char *)Order_Head,2,W_Data,0,CommunicationPortMode,0)== OK )
			return OK;
    ASSERT_FAILED();   test();          
    Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR=1;
    return ERR;
    }
/*"**************************************************************************"*/
/*"读二进制文件，ins=0xb0,         读出记录文件，ins=0xb2"*/                                                          
/*"取随机数，ins=0x84,?            取响应数据，ins=0xc0"*/             
unsigned char Read(unsigned char cla,unsigned char ins,unsigned char t_p1,
                   unsigned char t_p2,unsigned char len)
    {     
	unsigned char Order_Head[4];

	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver( ( const unsigned char * )Order_Head,0,0,len,CommunicationPortMode,0)== OK )
		return OK;
         ASSERT_FAILED();test();
         Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR=1;
          return ERR; 	
    }
    
/*"**************************************************************************"*/
/*"修改二进制文件，ins=0xd6   追加记录文件,ins=0xe2    修改记录 ,ins=0xdc "*/
/*"增加或修改密钥:ins=0xd4    存款：ins=0x32         扣款：ins=0x30  "*/
unsigned char Write(unsigned char cla,unsigned char ins,unsigned char t_p1,
                    unsigned char t_p2,unsigned char lc,unsigned char *address){
    
	unsigned char Order_Head[4];

	Order_Head[0] = cla;
	Order_Head[1] = ins;
	Order_Head[2] = t_p1;
	Order_Head[3] = t_p2;
	if( CPU_Card_Driver( (const unsigned char *)Order_Head,lc,address,0,CommunicationPortMode,0)== OK )
		return OK;
        ASSERT_FAILED();
	Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR=1;
	return ERR; 	
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 判断卡是否在 //
INT8U Check_CPU_Occur(void)
    {
        if(JUDGE_CPU_INSERT)//卡存在
        {
          return OK;
        }else{//卡不存在
          return ERR;
        }
    }

/////////////////////////////////////////////////////////////////// 
// 接收、判断CPU卡复位应答信号 //
unsigned char Cpucard_Atr(void){
	unsigned char Length;

        

	CPU_ESAM_CARD_Control(CPU);
	if(Check_CPU_Occur() )			
	{      
                ASSERT_FAILED(); 
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return ERR;
	}
     
        //冷复位，
        if(CPU_ESAM_DRV_OK != Cpu_Esam_All_Operate(CommunicationPortMode,CPU_ESAM_DRV_RST_COOL,receive_send_buffer,receive_send_buffer, Length_receive_send_buffer    )   ) 
        {  
                
            	ASSERT_FAILED();
                Card_Error_State.CardErrorState.CPU_CARD_CARD_ATR_ERR=1;
		return ERR;
        }

        Length  = receive_send_buffer[1];
	Length &=0x0F;
	Length +=4;
        ///
	if(  (receive_send_buffer[0]!=0x3b)||
	     (receive_send_buffer[2]!=0)|| 
             (receive_send_buffer[3]!=0)  ){
		Card_Error_State.CardErrorState.CPU_CARD_CARD_ATR_ERR=1;
		return ERR;  
	}
        //这里不需要反相， 存取的e方中 没有反相， 从cpu卡中读取也没有反相， 并且只是判断是否相等或不相等
        
	mem_cpy(cpucard_number,receive_send_buffer+Length-8,8,cpucard_number,sizeof(cpucard_number));//最后8为为离散
	return OK;    
  
}
/////////////////////////////////////////////////////////////////////////// 
//接收、判断SAM卡复位应答信号//                                                                  
unsigned char Esamcard_Atr(void){
        
	//判断是否卡存在
	CPU_ESAM_CARD_Control(ESAM);
        /*
	if(Check_CPU_Occur()){
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return ERR;
	}*/
        //冷复位，
        if(CPU_ESAM_DRV_OK != Cpu_Esam_All_Operate(CommunicationPortMode,CPU_ESAM_DRV_RST_COOL,
                                receive_send_buffer,receive_send_buffer,Length_receive_send_buffer ))
        {
            	ASSERT_FAILED();
                Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;
        }
        //判断接收的数据
	if((receive_send_buffer[0]!=0x3b)||
	(receive_send_buffer[2]!=0)||(receive_send_buffer[3]!=0)){
		Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;  
	}  
	
	return OK;  
	}
///////////////////////////////////////////////////////////////// 
// 文件名：CPU_Card_Driver //
// Order_Head：命令头域 //// 包括：CLA  INS  P1  P2  //

// Length_LC：写数据长度   //
// W_Data：写数据 //
// Length_LE: 读数据长度 //
// Change_Door: 读写通道 ESAM还是CPU //
// Spec_Length_LE: 特殊的后续数据帧长度,0:表示无特殊长度，直接取61 XX,//
// 非0表示为特殊后续数据帧，不取61 XX //#define WRITE_CPU_ESAM      0
//#define READ_CPU_ESAM       1
//对于lc+data 类型的命令，如果Spec_Length_LE为0该函数结束后，receive_send_buffer存放的是sw0和sw1
//对于lc+data 类型的命令，如果Spec_Length_LE不为0，该函数结束后，receive_send_buffer存放的是receive_send_buffer+sw0和sw1
//对于le  类型的命令， 如果Spec_Length_LE为0   该函数结束后， receive_send_buffer 存放的是 le+sw0和sw1 
//对于le  类型的命令， 如果Spec_Length_LE不为0   该函数结束后， receive_send_buffer 存放的是 Spec_Length_LE +sw0和sw1
//注意：W_Data 和receive_send_buffer  不能为同一个地址  两个地址之间至少相差350间隔
unsigned char CPU_Card_Driver(const unsigned char *Order_Head,
						     unsigned char Length_LC,
			                             unsigned char *W_Data,
			                             unsigned char Length_LE,
			                             unsigned char Change_Door,
			                             unsigned char Spec_Length_LE){
	unsigned char i;
        INT8U Command_Temp[5];
        INT8U Length_Le_Temp;
        //判断 形参数数是否正确
        if(   (  ( 0 !=Length_LC )&&( 0 !=Length_LE)    ) 
           || (  (Length_LC EQ 0)&& (Length_LE EQ 0) )
          )
        {
               ASSERT_FAILED();
               return ERR;         
        }
        //组装数据
        mem_cpy(Command_Temp,(INT8U *)Order_Head,4,Command_Temp,4);
	if( Length_LC !=0 )
		Command_Temp[4]=Length_LC;
	else if( Length_LE !=0 )
		Command_Temp[4]=Length_LE;
	else
		Command_Temp[4]=0;
        //分两种情况计算命令中要接收的长度 ：lc=0 但是le不为0(lc+data类型的命令)    lc不为0但是le为0（le类型的命令）
        if( (0 != Length_LE) && (Length_LC EQ 0) ){
                Length_Le_Temp=1+Length_LE+2;
        }else{
                Length_Le_Temp=1;
        }
        //发命令头和LC或LE给cpu卡Pre_Payment_Para
        if(CPU_ESAM_DRV_OK !=  Cpu_Esam_Comm_Proc(Change_Door,// 方向，是发给 esam ，还是cpu卡
                          Command_Temp,// 要发送的数据
                          4+1,//发送的数据长度 ， 包括  命令头4字节， 1个长度为， 要发送的数据长度
                          READ_CPU_ESAM,//告诉彭总，是不是要写e方，之后等待接收两个字节, 两个宏可以随便选的，写的宏时间长一点
                          Length_Le_Temp,//要接收的长度
                          receive_send_buffer,// pDst  接收的数据缓冲
                          receive_send_buffer,// pDst_Start
                          Length_receive_send_buffer))//pDst length
         
        {
               ASSERT_FAILED();
               return ERR; 
        }
        //判断从cpu卡接收的1个数据  是否和 命令头的ins  相等
        if(  receive_send_buffer[0]!=*(Order_Head+1) )
	{
          ASSERT_FAILED();
	  return ERR;
	}      
        //如果有lc不等于0 发数据位W_Data
         if( ( Length_LC !=0)&& (Length_LE  EQ 0 ) ){
            //发送数据或不发数据  然后接收数据      
            if(CPU_ESAM_DRV_OK !=  Cpu_Esam_Comm_Proc(Change_Door,// 方向，是发给 esam ，还是cpu卡
                          W_Data,// 要发送的数据
                          Length_LC,//发送的数据长度 ， 包括  命令头4字节， 1个长度为， 要发送的数据长度
                          WRITE_CPU_ESAM,////告诉彭总，是不是要写e方，之后等待接收两个字节
                          2,//要接收的长度
                          receive_send_buffer,// pDst  接收的数据缓冲
                          receive_send_buffer,// pDst_Start
                          Length_receive_send_buffer)//pDst length
             ){
                   ASSERT_FAILED();
                   return ERR; 
           }         
         }else if( (0 != Length_LE)&& (Length_LC EQ 0) ){
           //挤掉缓冲的第一个字节//不能移动缓冲Length_LE+2
             //这里不能使用Length_receive_send_buffer-1 而是用Length_LE+2, 因为我再以后的函数中使用了缓冲存放数据
             mem_cpy(&receive_send_buffer[0],&receive_send_buffer[1] ,Length_LE+2,&receive_send_buffer[0],Length_receive_send_buffer);  
         }else{
                   ASSERT_FAILED();
                   return ERR;       
         }
       //判读是否还要发命令接收， 特别对待 00 c0命令
	if(receive_send_buffer[0+Length_LE]==0x61)
	{
		if( *(Order_Head+1)!= Get_Response )
		{
	        	if( Spec_Length_LE!=0 )
				i = Spec_Length_LE;
			else
				i = receive_send_buffer[1+Length_LE];
	        	if(	Read(0,Get_Response,0,0,i )==OK ) 
	       	    	        return OK;
		        else
				return ERR;
		}
		else
			return OK;
	}
	else if((receive_send_buffer[0+Length_LE]==0x90)&&(receive_send_buffer[1+Length_LE]==0))
		return OK; 
	return ERR;
}


//可能要反相，所以 在这个函数中外包一层
INT16U C_Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen){
  if( Read_Storage_Data( SDI, pDst,  pDst, DstLen ) ){
   
    return 1;  
    
  }else{
   ASSERT_FAILED();
   return 0;
  }
       
}
//
INT8U  WhenCardInsertedInitPrePayData(void) { //上电从e方读取数据到全局变量
     //用户编号, 数据长度为6//在卡户卡流程中，是直接读取卡中的值，和直接读出e方中的值，两者相比较，  然后写的时候也是一样的 直接读出来，直接写发哦e方
     //在远程通讯中 ，进程开户操作的时，剩余金额，购电次数，是正常顺序，客户编号，和软件上的相反， 
 // 当开户的时候，是反相客户编号后再写到esam的    写到e方中的为正常顺序
  //当数据查询时，从esam中读出来的数据为反相后再反相 后 才得到正常顺序   ，再发给主站
     //  当充值的时候，是先反相主站的客户编号后再与e方中的客户编号相比较的
      //由此可以看出,主站来的数据是正常顺序，把数据给esam要反相顺序，  然而给 e方用正常顺序
    //除去　客户编号外，　客户编号从主站来时反是的顺序，写到ｅ方中要反相  发给主站要用反得顺序
     C_Read_Storage_Data( SDI_CUTOMER_ID, Pre_Payment_Para.UserID,  Pre_Payment_Para.UserID,sizeof(Pre_Payment_Para.UserID)  ); 
     //如果是读写运行状态
     //SDI参数填充_SDI_PREPAID_RUN_STATUS， 数据长度为1
     C_Read_Storage_Data( _SDI_PREPAID_RUN_STATUS, &Pre_Payment_Para.Meter_Run_State ,  &Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State)  );    
     //如果是写离散因子
     //SDI填充 _SDI_DISCRETE_INFO, 数据长度为8 
     C_Read_Storage_Data( _SDI_DISCRETE_INFO, &cpucard_number[0], &cpucard_number[0], sizeof( cpucard_number));    
     //密钥类型,密钥下装卡， 还是密钥恢复卡
     //_SDI_PREPAID_PSW_KIND, 数据长度为1     
     C_Read_Storage_Data( _SDI_PREPAID_PSW_KIND, &Pre_Payment_Para.PassWord_Kind,  &Pre_Payment_Para.PassWord_Kind,1);  
     //取表号  
     C_Read_Storage_Data( SDI_METER_ID, &Pre_Payment_Para.BcdMeterID,  &Pre_Payment_Para.BcdMeterID,6); 
    //现场参数设置卡版本号  
     C_Read_Storage_Data(_SDI_PREPAID_PARA_CARD_VER,&Pre_Payment_Para.Para_Card_Version, &Pre_Payment_Para.Para_Card_Version, 4) ;
     
     //Pre_Payment_Para.Remain_Money_Hoard_Limit=Get_Money_Hoard_Limit();
     //Pre_Payment_Para.Buy_Count=Get_Buy_Eng_Counts();//从黄工那里获得购电次数，
     Card_Error_State.CardErrorState_INT32U=0x00000000;
     //mem_cpy(Pre_Payment_Para.BcdMeterID,&a,6,Pre_Payment_Para.BcdMeterID,6);
     CardType=0x00;//卡类型 购电卡， 参数预置卡。。。
     Meter_Ins_Flag=0;
     Dir_Return_Flag = 0;
     Para_Updata_Flag=0;
     INIT_STRUCT_VAR(_Far_Pre_Payment_Para);
     INIT_STRUCT_VAR(_Pre_Payment_Para);
     SET_STRUCT_SUM(Pre_Payment_Para);
     return 1;
}

void PrintErrState(void ){
 
  if(Card_Error_State.CardErrorState_INT32U EQ 0 )
  {
     Debug_Print("   错误状态字为0"  );
     return;
  }
  if(Card_Error_State.CardErrorState. CardKindErr ){
     Debug_Print(" 卡类型错（购电卡， 参数预置卡。。）计入非法卡插入次数   "  );
  }
    if( Card_Error_State.CardErrorState. MeterIdErr){
     Debug_Print("  表号不匹配，计入非法卡插入次数   "  );
  }
    if( Card_Error_State.CardErrorState.CardIdErr ){
     Debug_Print(" 用户号码错误当表开户了后会出现 表未开户不会出现  用户编号错误  计入非法卡插入次数   "  );
  }
    if( Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr ){
     Debug_Print(" 外部认证错  计入非法卡插入次数   "  );
  }
    if( Card_Error_State.CardErrorState. CpuCardInternlAuthenticationErr){
     Debug_Print(" 内部认证， 即身份验证。计入非法卡插入次数   "  );
  }
    if( Card_Error_State.CardErrorState.CARD_STATE_ERR ){
     Debug_Print("  开户状态插入购电卡，补卡  "  );
  }
    if( Card_Error_State.CardErrorState. BUY_CARD_KIND_ERR){
     Debug_Print("   购电卡卡类型错 补卡，开户卡。类型没找到以及.卡户状态 插入 开户卡， 计入非法卡插入次数  "  );
  }
    if(Card_Error_State.CardErrorState. CARD_BUY_COUNT_ERR ){
     Debug_Print("   购电次数错误  计入非法卡插入次数 "  );
  }
    if(  Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err){
     Debug_Print("  离散因子错了， 计入非法卡插入次数   "  );
  }
    if( Card_Error_State.CardErrorState.MoneyLimitErr ){
     Debug_Print("  剩余电费 + 充值电费大于 剩余 金额门限  "  );
  }
    if( Card_Error_State.CardErrorState.EsamUpdataErr ){
     Debug_Print(" esam更新错误   "  );
  }
    if( Card_Error_State.CardErrorState.OperationTimeOutErr ){
     Debug_Print("   超过预定时间了 "  );
  }
    if( Card_Error_State.CardErrorState.CPU_CARD_CARD_ATR_ERR ){
     Debug_Print("  卡片复位错  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR ){
     Debug_Print("  ESAM复位错  "  );
  }
    if(Card_Error_State.CardErrorState.CPU_CARD_LOSE  ){
     Debug_Print("  提前拔卡  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_CARD_DATA_HEAD_ERR ){
     Debug_Print("   数据区68头错 "  );
  }
    if(  Card_Error_State.CardErrorState.CPU_CARD_DATA_END_ERR){
     Debug_Print(" 数据区16尾错   "  );
  }
    if(Card_Error_State.CardErrorState. CPU_CARD_DATA_CHECK_ERR ){
     Debug_Print("   数据区效验错 "  );
  }
    if(  Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR){
     Debug_Print("  CPU卡接收错  "  );
  }
    if( Card_Error_State.CardErrorState.Password_Key_Updata_ERR ){
     Debug_Print("  密钥更新错  "  );
  }
    if( Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err ){
     Debug_Print("  未按编程键  "  );
  }
    if( Card_Error_State.CardErrorState.Meter_Id_Set_Card_Id_Is_FULL_Err ){
     Debug_Print("  表号设置卡表号满错误  "  );
  }
    if(Card_Error_State.CardErrorState. Password_Count_Number_Is_Zero_Err ){
     Debug_Print("   密钥卡修改次数为零错误 "  );
  }
    if(Card_Error_State.CardErrorState.Password_State_Err  ){
     Debug_Print("  密钥卡状态错误  "  );
  }
    if(Card_Error_State.CardErrorState.ESAM_DO_ERR  ){
     Debug_Print("  ESAM操作错误  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_Para_Card_Version_Err){
     Debug_Print("  参数设置卡版本错误或计数器到零  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_NEW_CARD_INI_ERR ){
     Debug_Print("  已经插过表的开户卡重复插未当前未开户表  "  );
  }
    if( Card_Error_State.CardErrorState. ReadWriteE2romErr){
     Debug_Print("  读写E方错误  "  );
  }

}

