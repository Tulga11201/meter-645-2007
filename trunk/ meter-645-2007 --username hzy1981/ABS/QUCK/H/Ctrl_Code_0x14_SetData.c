#include "MyIncludesAll.h"

/*"**************************************************************************"*/
/*" ��һ�����Զ��д������"*/
/*" ֧�ֱ�3 "*/
/*" Data_Point:��:ָ��L DI0 DI1 DI2 DI3...... "*/
/*"            ��:���ݸ�ʽ���� "*/
/*" ��������ȷ �������ݸ�ʽת������ͨд���ݸ�ʽ�����ú���д����"*/
/*" ����������ֱ�Ӵ����˳�"*/
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
	0x08,0x01,0x00,0x04, 0x02,TRIFF_SWITCH_TIME_ESAM,0x05,   /*"���׷�ʱ���ʵ���л�ʱ��"*/
	0x06,0x03,0x00,0x04, 0x02,CURRENT_CT_ESAM,0x03,   /*"�������������"*/
	0x07,0x03,0x00,0x04, 0x02,VOLTAGE_PT_ESAM,0x03,   /*"��ѹ���������"*/
	0x0E,0x04,0x00,0x04, 0x02,CLIENT_ID_ESAM,0x06,   /*"�ͻ����"*/
	0x01,0x10,0x00,0x04, 0x02,REMAIN_MONEY_ALARM1_LIMIT_ESAM,0x04,   /*"�������1��ֵ"*/
	0x02,0x10,0x00,0x04, 0x02,REMAIN_MONEY_ALARM2_LIMIT_ESAM,0x04,   /*"�������2��ֵ"*/
	0x01,0x01,0x05,0x04, 0x03,TRIFF_CPU,0x04,   /*"��һ�׷���1"*/
	0x02,0x01,0x05,0x04, 0x03,TRIFF_CPU+4,0x04,   /*"��һ�׷���2"*/
	0x03,0x01,0x05,0x04, 0x03,TRIFF_CPU+8,0x04,   /*"��һ�׷���3"*/
	0x04,0x01,0x05,0x04, 0x03,TRIFF_CPU+12,0x04,   /*"��һ�׷���4"*/
	0x01,0x02,0x05,0x04, 0x04,TRIFF_CPU,0x04,   /*"�ڶ��׷���1"*/
	0x02,0x02,0x05,0x04, 0x04,TRIFF_CPU+4,0x04,   /*"�ڶ��׷���2"*/
	0x03,0x02,0x05,0x04, 0x04,TRIFF_CPU+8,0x04,   /*"�ڶ��׷���3"*/
	0x04,0x02,0x05,0x04, 0x04,TRIFF_CPU+12,0x04,   /*"�ڶ��׷���4"*/
};
#define LENGTH_FAR_DEAL_PARA_LIST_T1              sizeof(Far_Deal_Para_List_T1 )
//-----------------------------------------------------------------------------
//�õ�����+mac ��esam�������� ,pSrcΪ�����ݱ�ʾ��ʼ�����ݣ�  SrcLenΪ���ݳ��� �� 645֡��L�ֶε�ֵ
//����Ҫ���߻ƹ�  �޸�esam������ 
INT8U Set_Esam_Para(  INT8U *pSrc, INT8U SrcLen)
{//һ�������޸�
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
        //�鿴 �����֤��Чʱ����û�е�
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
        //���Ȳ��� //  SrcLen  Ӧ�� �� ����ʵ�ʳ��ȣ�+4�ֽ�mac  +12 �ֽ� ���ݱ�ʾ�����룬�����ߴ��룬   ���
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
			pSrc+LENGTH_FAR_645_FRAME_T1+4,0)!=OK)//����Ϊƫ��16���ֽڼ�ʵ������ΪN1N2...Nm
	{
            ASSERT_FAILED();
            return 0;
	}
	return 1;
}

/*"**************************************************************************"*/
/*" �ڶ������Զ��д������"*/
/*" ֧�ֱ�A5 "*/
/*" Data_Point:��:ָ��L DI0 DI1 DI2 DI3...... "*/
/*"            ��:���ݸ�ʽ���� "*/
/*" ��������ȷ �������ݸ�ʽת������ͨд���ݸ�ʽ�����ú���д����"*/
/*" ����������ֱ�Ӵ����˳�"*/
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
	unsigned char Source_Length;				/*"�������ݳ���"*/
	unsigned char TX_Length;					/*"ʵ�����ݳ���"*/
	};
#define LENGTH_FAR_DEAL_PARA_FLAG_T2      sizeof( struct Far_Deal_Para_Flag_T2 )
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const struct Far_Deal_Para_Flag_T2 Far_Deal_Para_List_T2[] = 
	{
	0x06,0x01,0x00,0x04,16,0x05,        /*"����ʱ�����л�ʱ��"*/
	0x07,0x01,0x00,0x04,16,0x05,        /*"������ʱ�α��л�ʱ��"*/
	0x09,0x01,0x00,0x04,16,0x05,        /*"�����ݶ��л�ʱ��"*/
	0x01,0x02,0x00,0x04,16,0x01,        /*"��ʱ����p��14"*/
	0x02,0x02,0x00,0x04,16,0x01,        /*"��ʱ�α���q��8"*/
	0x03,0x02,0x00,0x04,16,0x01,        /*"��ʱ����(ÿ���л���) m��14"*/
	0x04,0x02,0x00,0x04,16,0x01,        /*"������k��63"*/
	0x05,0x02,0x00,0x04,16,0x02,        /*"����������n��254"*/
	0x07,0x02,0x00,0x04,16,0x01,        /*"�ݶ���"*/
	0x01,0x08,0x00,0x04,16,0x01,        /*"������������"*/
	0x02,0x08,0x00,0x04,16,0x01,        /*"�����ղ��õ���ʱ�α��"*/
	0x01,0x0B,0x00,0x04,16,0x02,        /*"ÿ�µ�1������"*/
	0x02,0x0B,0x00,0x04,16,0x02,        /*"ÿ�µ�2������"*/
	0x03,0x0B,0x00,0x04,16,0x02,        /*"ÿ�µ�3������"*/
	0x04,0x10,0x00,0x04,16,0x04,        /*"�ڻ������ֵ"*/
	0x05,0x10,0x00,0x04,16,0x04,        /*"��բ��������ֵ"*/
//	0x00,0x00,0x01,0x04,48,42,        /*"��һ��ʱ��������"*/
//	0x00,0x00,0x02,0x04,48,42,        /*"�ڶ���ʱ��������"*/
	};
#define LENGTH_FAR_DEAL_PARA_LIST_T2              sizeof(Far_Deal_Para_List_T2 )
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/*"���DL/T645-2007 ���๦�ܵ��ܱ�ͨ��Э�顷�������ļ������ݱ�ʶ��DI2��Ϊ���֣�����DI2ģ5�Ľ�����жϲ����ĸ����������ļ���"*/
/*"���ݱ�ʶDI2ģ5 = 0�����ò��������ļ�1��"*/
/*"���ݱ�ʶDI2ģ5 = 1�����ò��������ļ�2��"*/
/*"���ݱ�ʶDI2ģ5 = 2�����ò��������ļ�3��"*/
/*"���ݱ�ʶDI2ģ5 = 3�����ò��������ļ�4��"*/
/*"���ݱ�ʶDI2ģ5 = 4�����ò��������ļ�5��"*/
const unsigned char Data_ID_Offset[]=
{0x09,0x10,0x11,0x12,0x13};
//-----------------------------------------------------------------------------
//д����ʱ��esamȨ���жϺ����Ľ���
//pSrc��ʾͨ��Э���е�lc�ֶκ��������
//SrcLen��ʾlc �ֶε�ֵ
//pDst��Ž��ܺ������ �� ����Ҫ�����ݱ�ʾ֮��Ķ�����
//pDst_StartĿ�껺����ʼ��ַ
//DstLen ���߻ƹ� ���ܺ�����ݳ��ȣ�
//����ֵ Ȩ����ȷ�ҽ��ܳɹ�����1�����򷵻�0
//ע�⣺�ú��������pSrc��pDst������ͬһ��ַ��
INT8U  Esam_Auth_Check(  INT8U *pSrc, INT16U SrcLen, INT8U * DstLen)
{//���������޸�
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
        //�鿴 �����֤��Чʱ����û�е�
        Far_Identity_Auth_Ok_Flag=!Chk_Pay_Time_Arrive();
        //  �����֤ûͨ�������������
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
	//645Э���ж���� L�ֶεĳ��� ��Ӧ�� �� ���еĶ�������ĵĳ��� + 4 �ֽ�mac + 12�ֽ� ���ݱ�ʾ�����룬�����ߴ��� ���
	if(  SrcLen  != (Far_Deal_Para_Flag_T2.Source_Length+16) )
        {
           ASSERT_FAILED();
           return 0;		
        }	
 	i = *(DataPdi+2 );
	i%=5;
	j = Data_ID_Offset[i];
        //��N1N2....Nm д��esam��ȥ
	if( Far_Write_Esam(0x04,Update_Binary,0x80+j,0x00,Far_Deal_Para_Flag_T2.Source_Length,pSrc+LENGTH_FAR_645_FRAME_T2+4,0)!=OK){
		 ASSERT_FAILED();
                 return 0;  
	}
        ////�����ܺ�����ݶ�ȡ  �ŵ�pDst��ȥd
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
        
	*DstLen=Far_Deal_Para_Flag_T2.TX_Length +12;//����ֻҪ���߻ƹ� ���ܺ������ ʵ�ʳ��ȼ��ɣ� ��Ҫ��������
        return 1;
} 
///////////////
 