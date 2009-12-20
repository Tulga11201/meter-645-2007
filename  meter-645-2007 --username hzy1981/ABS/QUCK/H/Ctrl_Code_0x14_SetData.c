#include "MyIncludesAll.h"

/*"**************************************************************************"*/
/*" 第一类参数远程写处理函数"*/
/*" 支持表3 "*/
/*" Data_Point:入:指向L DI0 DI1 DI2 DI3...... "*/
/*"            出:数据格式见下 "*/
/*" 如果结果正确 ，将数据格式转换成普通写数据格式，调用后续写处理"*/
/*" 如果结果错误，直接错误退出"*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Far_645_Frame_T1
	{
//	unsigned char Data_ID[4];
	unsigned char PassWord[4];
	unsigned char Do_man[4];
	};
#define LENGTH_FAR_645_FRAME_T1        sizeof(struct Far_645_Frame_T1 )
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Far_Deal_Para_Flag_T1
	{
	unsigned char Data_ID[4];
	unsigned char Esam_File;
	unsigned int  Esam_Offset;
	unsigned char Esam_Length;
	};
#define LENGTH_FAR_DEAL_PARA_FLAG_T1      sizeof(struct Far_Deal_Para_Flag_T1)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const struct Far_Deal_Para_Flag_T1 Far_Deal_Para_List_T1[] = {
	0x08,0x01,0x00,0x04, 0x02,TRIFF_SWITCH_TIME_ESAM,0x05,   /*"两套分时费率电价切换时间"*/
	0x06,0x03,0x00,0x04, 0x02,CURRENT_CT_ESAM,0x03,   /*"电流互感器变比"*/
	0x07,0x03,0x00,0x04, 0x02,VOLTAGE_PT_ESAM,0x03,   /*"电压互感器变比"*/
	0x0E,0x04,0x00,0x04, 0x02,CLIENT_ID_ESAM,0x06,   /*"客户编号"*/
	0x01,0x10,0x00,0x04, 0x02,REMAIN_MONEY_ALARM1_LIMIT_ESAM,0x04,   /*"报警金额1限值"*/
	0x02,0x10,0x00,0x04, 0x02,REMAIN_MONEY_ALARM2_LIMIT_ESAM,0x04,   /*"报警金额2限值"*/
	0x01,0x01,0x05,0x04, 0x03,TRIFF_CPU,0x04,   /*"第一套费率1"*/
	0x02,0x01,0x05,0x04, 0x03,TRIFF_CPU+4,0x04,   /*"第一套费率2"*/
	0x03,0x01,0x05,0x04, 0x03,TRIFF_CPU+8,0x04,   /*"第一套费率3"*/
	0x04,0x01,0x05,0x04, 0x03,TRIFF_CPU+12,0x04,   /*"第一套费率4"*/
	0x01,0x02,0x05,0x04, 0x04,TRIFF_CPU,0x04,   /*"第二套费率1"*/
	0x02,0x02,0x05,0x04, 0x04,TRIFF_CPU+4,0x04,   /*"第二套费率2"*/
	0x03,0x02,0x05,0x04, 0x04,TRIFF_CPU+8,0x04,   /*"第二套费率3"*/
	0x04,0x02,0x05,0x04, 0x04,TRIFF_CPU+12,0x04,   /*"第二套费率4"*/
};
#define LENGTH_FAR_DEAL_PARA_LIST_T1              sizeof(Far_Deal_Para_List_T1 )
//-----------------------------------------------------------------------------
//得到明文+mac 对esam进行设置 ,pSrc为从数据标示开始的数据，  SrcLen为数据长度 即 645帧中L字段的值
//不需要告诉黄工  修改esam参数， 
INT8U Set_Esam_Para(  INT8U *pSrc, INT8U SrcLen)
{//一类数据修改
        INT8U DataPdi[4];
        unsigned char i,j;
  
	struct Far_Deal_Para_Flag_T1  Far_Deal_Para_Flag_T1;
	struct Far_645_Frame_T1   Far_645_Frame_T1;
        // 
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
        mem_cpy(DataPdi,pSrc,4,DataPdi,4);
        
	if(FarPrePayment.ID_Ins_Counter >=15 )
        {    
             ASSERT_FAILED();
             return 0;
        }
        mem_cpy(&Far_645_Frame_T1,pSrc+4,sizeof(Far_645_Frame_T1),&Far_645_Frame_T1,sizeof(Far_645_Frame_T1)); 

	for( i=0;i<S_NUM(Far_Deal_Para_List_T1);i++ )
        {
                if(memcmp(&Far_Deal_Para_List_T1[i].Data_ID[0],&DataPdi[0],4) EQ 0 )
                {
                   break;
                }        
	}
	if( i EQ S_NUM(Far_Deal_Para_List_T1))
        {
            ASSERT_FAILED();
            return 0;
        }
        //长度不对 //  SrcLen  应该 和 数据实际长度，+4字节mac  +12 字节 数据标示，密码，操作者代码，   相等
	if( SrcLen != (Far_Deal_Para_List_T1[i].Esam_Length+16) )
        {
            ASSERT_FAILED();
            return 0;		
        }
			
	for( j=0;j<LENGTH_FAR_DEAL_PARA_FLAG_T1;j++ )
		*(((unsigned char *)(&Far_Deal_Para_Flag_T1))+j) = *(((const unsigned char *)&Far_Deal_Para_List_T1[i])+j);

	if(Far_Write_Esam(0x04,Update_Binary,0x80+Far_Deal_Para_Flag_T1.Esam_File,
			(unsigned char)Far_Deal_Para_Flag_T1.Esam_Offset,
			Far_Deal_Para_Flag_T1.Esam_Length,
			pSrc+LENGTH_FAR_645_FRAME_T1+4,0)!=OK)//这里为偏移16个字节即实际数据为N1N2...Nm
	{
            ASSERT_FAILED();
            return 0;
	}
	return 1;
}

/*"**************************************************************************"*/
/*" 第二类参数远程写处理函数"*/
/*" 支持表A5 "*/
/*" Data_Point:入:指向L DI0 DI1 DI2 DI3...... "*/
/*"            出:数据格式见下 "*/
/*" 如果结果正确 ，将数据格式转换成普通写数据格式，调用后续写处理"*/
/*" 如果结果错误，直接错误退出"*/
/*"**************************************************************************"*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Far_645_Frame_T2
	{
//	unsigned char Length;
//	unsigned char Data_ID[4];
	unsigned char PassWord[4];
	unsigned char Do_man[4];
	};
#define LENGTH_FAR_645_FRAME_T2        sizeof(struct Far_645_Frame_T2 )
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Far_Deal_Para_Flag_T2
	{
	unsigned char Data_ID[4];
	unsigned char Source_Length;				/*"密文数据长度"*/
	unsigned char TX_Length;					/*"实际数据长度"*/
	};
#define LENGTH_FAR_DEAL_PARA_FLAG_T2      sizeof( struct Far_Deal_Para_Flag_T2 )
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const struct Far_Deal_Para_Flag_T2 Far_Deal_Para_List_T2[] = 
	{
	0x06,0x01,0x00,0x04,16,0x05,        /*"两套时区表切换时间"*/
	0x07,0x01,0x00,0x04,16,0x05,        /*"两套日时段表切换时间"*/
	0x09,0x01,0x00,0x04,16,0x05,        /*"两套梯度切换时间"*/
	0x01,0x02,0x00,0x04,16,0x01,        /*"年时区数p≤14"*/
	0x02,0x02,0x00,0x04,16,0x01,        /*"日时段表数q≤8"*/
	0x03,0x02,0x00,0x04,16,0x01,        /*"日时段数(每日切换数) m≤14"*/
	0x04,0x02,0x00,0x04,16,0x01,        /*"费率数k≤63"*/
	0x05,0x02,0x00,0x04,16,0x02,        /*"公共假日数n≤254"*/
	0x07,0x02,0x00,0x04,16,0x01,        /*"梯度数"*/
	0x01,0x08,0x00,0x04,16,0x01,        /*"周休日特征字"*/
	0x02,0x08,0x00,0x04,16,0x01,        /*"周休日采用的日时段表号"*/
	0x01,0x0B,0x00,0x04,16,0x02,        /*"每月第1结算日"*/
	0x02,0x0B,0x00,0x04,16,0x02,        /*"每月第2结算日"*/
	0x03,0x0B,0x00,0x04,16,0x02,        /*"每月第3结算日"*/
	0x04,0x10,0x00,0x04,16,0x04,        /*"囤积金额限值"*/
	0x05,0x10,0x00,0x04,16,0x04,        /*"合闸允许金额限值"*/
//	0x00,0x00,0x01,0x04,48,42,        /*"第一套时区表数据"*/
//	0x00,0x00,0x02,0x04,48,42,        /*"第二套时区表数据"*/
	};
#define LENGTH_FAR_DEAL_PARA_LIST_T2              sizeof(Far_Deal_Para_List_T2 )
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*"軩L/T645-2007 《多功能电能表通信协议》及备案文件中数据标识的DI2作为区分，利用DI2模5的结果，判断采用哪个参数更新文件。"*/
/*"标识DI2模5 = 0：采用参数更新文件1；"*/
/*"标识DI2模5 = 1：采用参数更新文件2；"*/
/*"标识DI2模5 = 2：采用参数更新文件3；"*/
/*"标识DI2模5 = 3：采用参数更新文件4；"*/
/*"标识DI2模5 = 4：采用参数更新文件5。"*/
const unsigned char Data_ID_Offset[]=
{0x09,0x10,0x11,0x12,0x13};
//-----------------------------------------------------------------------------
//写数据时的esam权限判断和密文解密
//pSrc表示通信协议中的lc字段后面的数据
//SrcLen表示lc 字段的值
//pDst存放解密后的数据 ， ，不要管数据标示之类的东西，
//pDst_Start目标缓冲起始地址
//DstLen 告诉黄工 解密后的数据长度，
//返回值 权限正确且解密成功返回1，否则返回0
//注意：该函数传入的pSrc和pDst可能是同一地址。
INT8U  Esam_Auth_Check(  INT8U *pSrc, INT16U SrcLen, INT8U * DstLen)
{//二类数据修改
        INT8U i,j,Block_Flag;
	//INT8U Length; 
        INT8U DataPdi[4];
	struct Far_Deal_Para_Flag_T2  Far_Deal_Para_Flag_T2;
	//struct Far_645_Frame_T2    Far_645_Frame_T2;
	unsigned char ID_a,ID_b,ID_c,ID_d;
        
        CPU_ESAM_CARD_Control(ESAM);
        if( Select_File(0,0x3F,0) != OK )
        {
            ASSERT_FAILED();
            Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
            return 0;
        }
        //查看 身份认证有效时间有没有到
        Far_Identity_Auth_Ok_Flag=!Chk_Pay_Time_Arrive();
        //  身份验证没通过，不允许操作
        if(Far_Identity_Auth_Ok_Flag != 1)
        {
            Reset_Pay_Timer(0);
            ASSERT_FAILED();
            return 0;
        }

	if( FarPrePayment.ID_Ins_Counter >=15 )
        {
              ASSERT_FAILED();
              return 0;
        }
        
        mem_cpy(DataPdi,pSrc,4,DataPdi,4);
                
	//Far_645_Frame_T2 = (struct Far_645_Frame_T2  *)(pSrc+4);
	ID_a = *(DataPdi+3 );
	ID_b = *(DataPdi+2 );
	ID_c = *(DataPdi+1 );
	ID_d = *(DataPdi+0 );
	Block_Flag = 0x00;
	for( i=0;i<S_NUM(Far_Deal_Para_List_T2);i++ ){
              if(memcmp(&Far_Deal_Para_List_T2[i].Data_ID[0],&DataPdi[0],4) EQ 0 ){
                   break;
              }    
	}
	if( i  EQ  S_NUM(Far_Deal_Para_List_T2) ){
		Far_Deal_Para_Flag_T2.Source_Length = 16;
		Far_Deal_Para_Flag_T2.Data_ID[0] = *(DataPdi+0 );
		Far_Deal_Para_Flag_T2.Data_ID[1] = *(DataPdi+1 );
		Far_Deal_Para_Flag_T2.Data_ID[2] = *(DataPdi+2 );
		Far_Deal_Para_Flag_T2.Data_ID[3] = *(DataPdi+3 );
//		if( ( *(ID_Point+0 )>=1 && *(ID_Point+0 )<=8 ) && (*(ID_Point+1 )==0) && ((*(ID_Point+2 )==1) || (*(ID_Point+2 )==2)) )
//			Far_Deal_Para_Flag_T2.TX_Length = 3;
		if( ( *(DataPdi+0 )>=1 && *(DataPdi+0 )<=0xFE ) && (*(DataPdi+1 )==0) && (*(DataPdi+2 )==3)  )
			Far_Deal_Para_Flag_T2.TX_Length = 4;
		else if( ( *(DataPdi+0 )<=0x05 ) && (*(DataPdi+1 )<=3) && (*(DataPdi+2 )==6)  )
			Far_Deal_Para_Flag_T2.TX_Length = 4;
// 0x04010000~0x04010008                  0x04020000~0x04020008
		else if(   ID_a==0x04 &&  ( ID_b>=0x01 || ID_b<=0x02 ) && ID_c==0x00 && ID_d<=0x08 ){
			Block_Flag = 0xFF;
			Far_Deal_Para_Flag_T2.TX_Length = 42;
			Far_Deal_Para_Flag_T2.Source_Length = 48;
		}else{
                   ASSERT_FAILED();
                   return 0;
                }	
	}
	else{
		for( j=0;j<LENGTH_FAR_DEAL_PARA_FLAG_T2;j++ )
			*(((unsigned char *)(&Far_Deal_Para_Flag_T2))+j) = *(((const unsigned char *)&Far_Deal_Para_List_T2[i])+j);
	}
	//645协议中定义的 L字段的长度 ，应该 和 表中的定义的密文的长度 + 4 字节mac + 12字节 数据标示，密码，操作者代码 相等
	if(  SrcLen  != (Far_Deal_Para_Flag_T2.Source_Length+16) )
        {
           ASSERT_FAILED();
           return 0;		
        }	
 	i = *(DataPdi+2 );
	i%=5;
	j = Data_ID_Offset[i];
        //把N1N2....Nm 写到esam中去
	if( Far_Write_Esam(0x04,Update_Binary,0x80+j,0x00,Far_Deal_Para_Flag_T2.Source_Length,pSrc+LENGTH_FAR_645_FRAME_T2+4,0)!=OK){
		 ASSERT_FAILED();
                 return 0;  
	}
        ////将解密后的数据读取  放到pDst中去d
	if( Read(0x00, Read_Binary, 0x80+j, 0x00, Far_Deal_Para_Flag_T2.TX_Length+5) != OK )
        {
          ASSERT_FAILED();
          return 0;
        }
		

	Reverse_data(receive_send_buffer+1,4);
	if( My_Memcmp(receive_send_buffer+1,Far_Deal_Para_Flag_T2.Data_ID,4) != 0 )
        {  
          ASSERT_FAILED();
          return 0;
        }  
		
	if( Block_Flag == 0 )
		My_memcpyRev(pSrc + 12, receive_send_buffer+5, Far_Deal_Para_Flag_T2.TX_Length);
	else{
		for( i=0;i<14;i++ ){
			My_memcpyRev(pSrc + 12 +i*3, receive_send_buffer+5+i*3, 3);
		}
	}
        
	*DstLen=Far_Deal_Para_Flag_T2.TX_Length +12;//这里只要告诉黄工 解密后的数据 实际长度即可， 不要管其他的
        return 1;
} 
///////////////
 