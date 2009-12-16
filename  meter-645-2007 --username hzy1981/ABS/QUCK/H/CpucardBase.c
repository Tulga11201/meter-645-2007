#include "MyIncludesAll.h"
#undef Debug_Print
//#define Debug_Print(...)
#define Debug_Print _Debug_Print

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// ��ʱ_64us��64us //      
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
/*"��ԭ����ǰ���õظ��Ƶ�Ŀ������"*/
void My_memcpyRev(unsigned char *to,unsigned char *from,unsigned char len){	
	unsigned char i;	
	for(i=0;i<len;i++)
		*(to+i)=*(from+len-1-i);
}
//ASSERT_FAILED();
/*******************************************************************************/	
/*"������ǰ����"*/
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
//����0��ȣ� ����1���ڣ� ����2С��
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
/*" �жϷ��ر�־�ĺϷ��� "*/    
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
void CPU_ESAM_CARD_Control(INT8U Direct)//����ѡ�� �Ƿ���esam����cpu��
{
   CommunicationPortMode=Direct;

}


/*"**************************************************************************"*/
/*"�ڲ���֤��CPU��0x0088,ESAM��0x80fa;p1:Ϊ0ʱ����,Ϊ1ʱ���ܣ�p2:��Կ��ʶ��"*/                 
/*"addressΪ��Ҫ���ܵ������׵�ַ"*/                                                                                
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
/*"�ⲿ��֤��p2:��Կ��ʶ��, addressΪ��Ҫ���ܵ������׵�ַ"*/
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
/*"cpu�����ļ�ѡ�� :3f01 "*/
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
/*"���������ļ���ins=0xb0,         ������¼�ļ���ins=0xb2"*/                                                          
/*"ȡ�������ins=0x84,?            ȡ��Ӧ���ݣ�ins=0xc0"*/             
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
/*"�޸Ķ������ļ���ins=0xd6   ׷�Ӽ�¼�ļ�,ins=0xe2    �޸ļ�¼ ,ins=0xdc "*/
/*"���ӻ��޸���Կ:ins=0xd4    ��ins=0x32         �ۿins=0x30  "*/
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
// �жϿ��Ƿ��� //
INT8U Check_CPU_Occur(void)
    {
        if(JUDGE_CPU_INSERT)//������
        {
          return OK;
        }else{//��������
          return ERR;
        }
    }

/////////////////////////////////////////////////////////////////// 
// ���ա��ж�CPU����λӦ���ź� //
unsigned char Cpucard_Atr(void){
	unsigned char Length;

        

	CPU_ESAM_CARD_Control(CPU);
	if(Check_CPU_Occur() )			
	{      
                ASSERT_FAILED(); 
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return ERR;
	}
     
        //�临λ��
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
        //���ﲻ��Ҫ���࣬ ��ȡ��e���� û�з��࣬ ��cpu���ж�ȡҲû�з��࣬ ����ֻ���ж��Ƿ���Ȼ����
        
	mem_cpy(cpucard_number,receive_send_buffer+Length-8,8,cpucard_number,sizeof(cpucard_number));//���8ΪΪ��ɢ
	return OK;    
  
}
/////////////////////////////////////////////////////////////////////////// 
//���ա��ж�SAM����λӦ���ź�//                                                                  
unsigned char Esamcard_Atr(void){
        
	//�ж��Ƿ񿨴���
	CPU_ESAM_CARD_Control(ESAM);
        /*
	if(Check_CPU_Occur()){
                ASSERT_FAILED();
		Card_Error_State.CardErrorState.CPU_CARD_LOSE=1;
		return ERR;
	}*/
        //�临λ��
        if(CPU_ESAM_DRV_OK != Cpu_Esam_All_Operate(CommunicationPortMode,CPU_ESAM_DRV_RST_COOL,
                                receive_send_buffer,receive_send_buffer,Length_receive_send_buffer ))
        {
            	ASSERT_FAILED();
                Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;
        }
        //�жϽ��յ�����
	if((receive_send_buffer[0]!=0x3b)||
	(receive_send_buffer[2]!=0)||(receive_send_buffer[3]!=0)){
		Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR=1;
		return ERR;  
	}  
	
	return OK;  
	}
///////////////////////////////////////////////////////////////// 
// �ļ�����CPU_Card_Driver //
// Order_Head������ͷ�� //// ������CLA  INS  P1  P2  //

// Length_LC��д���ݳ���   //
// W_Data��д���� //
// Length_LE: �����ݳ��� //
// Change_Door: ��дͨ�� ESAM����CPU //
// Spec_Length_LE: ����ĺ�������֡����,0:��ʾ�����ⳤ�ȣ�ֱ��ȡ61 XX,//
// ��0��ʾΪ�����������֡����ȡ61 XX //#define WRITE_CPU_ESAM      0
//#define READ_CPU_ESAM       1
//����lc+data ���͵�������Spec_Length_LEΪ0�ú���������receive_send_buffer��ŵ���sw0��sw1
//����lc+data ���͵�������Spec_Length_LE��Ϊ0���ú���������receive_send_buffer��ŵ���receive_send_buffer+sw0��sw1
//����le  ���͵���� ���Spec_Length_LEΪ0   �ú��������� receive_send_buffer ��ŵ��� le+sw0��sw1 
//����le  ���͵���� ���Spec_Length_LE��Ϊ0   �ú��������� receive_send_buffer ��ŵ��� Spec_Length_LE +sw0��sw1
//ע�⣺W_Data ��receive_send_buffer  ����Ϊͬһ����ַ  ������ַ֮���������350���
unsigned char CPU_Card_Driver(const unsigned char *Order_Head,
						     unsigned char Length_LC,
			                             unsigned char *W_Data,
			                             unsigned char Length_LE,
			                             unsigned char Change_Door,
			                             unsigned char Spec_Length_LE){
	unsigned char i;
        INT8U Command_Temp[5];
        INT8U Length_Le_Temp;
        //�ж� �β������Ƿ���ȷ
        if(   (  ( 0 !=Length_LC )&&( 0 !=Length_LE)    ) 
           || (  (Length_LC EQ 0)&& (Length_LE EQ 0) )
          )
        {
               ASSERT_FAILED();
               return ERR;         
        }
        //��װ����
        mem_cpy(Command_Temp,(INT8U *)Order_Head,4,Command_Temp,4);
	if( Length_LC !=0 )
		Command_Temp[4]=Length_LC;
	else if( Length_LE !=0 )
		Command_Temp[4]=Length_LE;
	else
		Command_Temp[4]=0;
        //�������������������Ҫ���յĳ��� ��lc=0 ����le��Ϊ0(lc+data���͵�����)    lc��Ϊ0����leΪ0��le���͵����
        if( (0 != Length_LE) && (Length_LC EQ 0) ){
                Length_Le_Temp=1+Length_LE+2;
        }else{
                Length_Le_Temp=1;
        }
        //������ͷ��LC��LE��cpu��Pre_Payment_Para
        if(CPU_ESAM_DRV_OK !=  Cpu_Esam_Comm_Proc(Change_Door,// �����Ƿ��� esam ������cpu��
                          Command_Temp,// Ҫ���͵�����
                          4+1,//���͵����ݳ��� �� ����  ����ͷ4�ֽڣ� 1������Ϊ�� Ҫ���͵����ݳ���
                          READ_CPU_ESAM,//�������ܣ��ǲ���Ҫдe����֮��ȴ����������ֽ�, ������������ѡ�ģ�д�ĺ�ʱ�䳤һ��
                          Length_Le_Temp,//Ҫ���յĳ���
                          receive_send_buffer,// pDst  ���յ����ݻ���
                          receive_send_buffer,// pDst_Start
                          Length_receive_send_buffer))//pDst length
         
        {
               ASSERT_FAILED();
               return ERR; 
        }
        //�жϴ�cpu�����յ�1������  �Ƿ�� ����ͷ��ins  ���
        if(  receive_send_buffer[0]!=*(Order_Head+1) )
	{
          ASSERT_FAILED();
	  return ERR;
	}      
        //�����lc������0 ������λW_Data
         if( ( Length_LC !=0)&& (Length_LE  EQ 0 ) ){
            //�������ݻ򲻷�����  Ȼ���������      
            if(CPU_ESAM_DRV_OK !=  Cpu_Esam_Comm_Proc(Change_Door,// �����Ƿ��� esam ������cpu��
                          W_Data,// Ҫ���͵�����
                          Length_LC,//���͵����ݳ��� �� ����  ����ͷ4�ֽڣ� 1������Ϊ�� Ҫ���͵����ݳ���
                          WRITE_CPU_ESAM,////�������ܣ��ǲ���Ҫдe����֮��ȴ����������ֽ�
                          2,//Ҫ���յĳ���
                          receive_send_buffer,// pDst  ���յ����ݻ���
                          receive_send_buffer,// pDst_Start
                          Length_receive_send_buffer)//pDst length
             ){
                   ASSERT_FAILED();
                   return ERR; 
           }         
         }else if( (0 != Length_LE)&& (Length_LC EQ 0) ){
           //��������ĵ�һ���ֽ�//�����ƶ�����Length_LE+2
             //���ﲻ��ʹ��Length_receive_send_buffer-1 ������Length_LE+2, ��Ϊ�����Ժ�ĺ�����ʹ���˻���������
             mem_cpy(&receive_send_buffer[0],&receive_send_buffer[1] ,Length_LE+2,&receive_send_buffer[0],Length_receive_send_buffer);  
         }else{
                   ASSERT_FAILED();
                   return ERR;       
         }
       //�ж��Ƿ�Ҫ��������գ� �ر�Դ� 00 c0����
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


//����Ҫ���࣬���� ��������������һ��
INT16U C_Read_Storage_Data(STORA_DI SDI, void* pDst, void* pDst_Start, INT16U DstLen){
  if( Read_Storage_Data( SDI, pDst,  pDst, DstLen ) ){
   
    return 1;  
    
  }else{
   ASSERT_FAILED();
   return 0;
  }
       
}
//
INT8U  WhenCardInsertedInitPrePayData(void) { //�ϵ��e����ȡ���ݵ�ȫ�ֱ���
     //�û����, ���ݳ���Ϊ6//�ڿ����������У���ֱ�Ӷ�ȡ���е�ֵ����ֱ�Ӷ���e���е�ֵ��������Ƚϣ�  Ȼ��д��ʱ��Ҳ��һ���� ֱ�Ӷ�������ֱ��д��Ŷe��
     //��Զ��ͨѶ�� �����̿���������ʱ��ʣ������������������˳�򣬿ͻ���ţ�������ϵ��෴�� 
 // ��������ʱ���Ƿ���ͻ���ź���д��esam��    д��e���е�Ϊ����˳��
  //�����ݲ�ѯʱ����esam�ж�����������Ϊ������ٷ��� �� �ŵõ�����˳��   ���ٷ�����վ
     //  ����ֵ��ʱ�����ȷ�����վ�Ŀͻ���ź�����e���еĿͻ������Ƚϵ�
      //�ɴ˿��Կ���,��վ��������������˳�򣬰����ݸ�esamҪ����˳��  Ȼ���� e��������˳��
    //��ȥ���ͻ�����⣬���ͻ���Ŵ���վ��ʱ���ǵ�˳��д���巽��Ҫ����  ������վҪ�÷���˳��
     C_Read_Storage_Data( SDI_CUTOMER_ID, Pre_Payment_Para.UserID,  Pre_Payment_Para.UserID,sizeof(Pre_Payment_Para.UserID)  ); 
     //����Ƕ�д����״̬
     //SDI�������_SDI_PREPAID_RUN_STATUS�� ���ݳ���Ϊ1
     C_Read_Storage_Data( _SDI_PREPAID_RUN_STATUS, &Pre_Payment_Para.Meter_Run_State ,  &Pre_Payment_Para.Meter_Run_State,sizeof(Pre_Payment_Para.Meter_Run_State)  );    
     //�����д��ɢ����
     //SDI��� _SDI_DISCRETE_INFO, ���ݳ���Ϊ8 
     C_Read_Storage_Data( _SDI_DISCRETE_INFO, &cpucard_number[0], &cpucard_number[0], sizeof( cpucard_number));    
     //��Կ����,��Կ��װ���� ������Կ�ָ���
     //_SDI_PREPAID_PSW_KIND, ���ݳ���Ϊ1     
     C_Read_Storage_Data( _SDI_PREPAID_PSW_KIND, &Pre_Payment_Para.PassWord_Kind,  &Pre_Payment_Para.PassWord_Kind,1);  
     //ȡ���  
     C_Read_Storage_Data( SDI_METER_ID, &Pre_Payment_Para.BcdMeterID,  &Pre_Payment_Para.BcdMeterID,6); 
    //�ֳ��������ÿ��汾��  
     C_Read_Storage_Data(_SDI_PREPAID_PARA_CARD_VER,&Pre_Payment_Para.Para_Card_Version, &Pre_Payment_Para.Para_Card_Version, 4) ;
     
     //Pre_Payment_Para.Remain_Money_Hoard_Limit=Get_Money_Hoard_Limit();
     //Pre_Payment_Para.Buy_Count=Get_Buy_Eng_Counts();//�ӻƹ������ù��������
     Card_Error_State.CardErrorState_INT32U=0x00000000;
     //mem_cpy(Pre_Payment_Para.BcdMeterID,&a,6,Pre_Payment_Para.BcdMeterID,6);
     CardType=0x00;//������ ���翨�� ����Ԥ�ÿ�������
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
     Debug_Print("   ����״̬��Ϊ0"  );
     return;
  }
  if(Card_Error_State.CardErrorState. CardKindErr ){
     Debug_Print(" �����ʹ����翨�� ����Ԥ�ÿ�����������Ƿ����������   "  );
  }
    if( Card_Error_State.CardErrorState. MeterIdErr){
     Debug_Print("  ��Ų�ƥ�䣬����Ƿ����������   "  );
  }
    if( Card_Error_State.CardErrorState.CardIdErr ){
     Debug_Print(" �û�������󵱱����˺����� ��δ�����������  �û���Ŵ���  ����Ƿ����������   "  );
  }
    if( Card_Error_State.CardErrorState.CpuCardExternlAuthenticationErr ){
     Debug_Print(" �ⲿ��֤��  ����Ƿ����������   "  );
  }
    if( Card_Error_State.CardErrorState. CpuCardInternlAuthenticationErr){
     Debug_Print(" �ڲ���֤�� �������֤������Ƿ����������   "  );
  }
    if( Card_Error_State.CardErrorState.CARD_STATE_ERR ){
     Debug_Print("  ����״̬���빺�翨������  "  );
  }
    if( Card_Error_State.CardErrorState. BUY_CARD_KIND_ERR){
     Debug_Print("   ���翨�����ʹ� ������������������û�ҵ��Լ�.����״̬ ���� �������� ����Ƿ����������  "  );
  }
    if(Card_Error_State.CardErrorState. CARD_BUY_COUNT_ERR ){
     Debug_Print("   �����������  ����Ƿ���������� "  );
  }
    if(  Card_Error_State.CardErrorState.Cpu_Card_Li_San_Yin_Zi_Err){
     Debug_Print("  ��ɢ���Ӵ��ˣ� ����Ƿ����������   "  );
  }
    if( Card_Error_State.CardErrorState.MoneyLimitErr ){
     Debug_Print("  ʣ���� + ��ֵ��Ѵ��� ʣ�� �������  "  );
  }
    if( Card_Error_State.CardErrorState.EsamUpdataErr ){
     Debug_Print(" esam���´���   "  );
  }
    if( Card_Error_State.CardErrorState.OperationTimeOutErr ){
     Debug_Print("   ����Ԥ��ʱ���� "  );
  }
    if( Card_Error_State.CardErrorState.CPU_CARD_CARD_ATR_ERR ){
     Debug_Print("  ��Ƭ��λ��  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_CARD_ESAM_ATR_ERR ){
     Debug_Print("  ESAM��λ��  "  );
  }
    if(Card_Error_State.CardErrorState.CPU_CARD_LOSE  ){
     Debug_Print("  ��ǰ�ο�  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_CARD_DATA_HEAD_ERR ){
     Debug_Print("   ������68ͷ�� "  );
  }
    if(  Card_Error_State.CardErrorState.CPU_CARD_DATA_END_ERR){
     Debug_Print(" ������16β��   "  );
  }
    if(Card_Error_State.CardErrorState. CPU_CARD_DATA_CHECK_ERR ){
     Debug_Print("   ������Ч��� "  );
  }
    if(  Card_Error_State.CardErrorState.CPU_CARD_COMM_DELAY_ERR){
     Debug_Print("  CPU�����մ�  "  );
  }
    if( Card_Error_State.CardErrorState.Password_Key_Updata_ERR ){
     Debug_Print("  ��Կ���´�  "  );
  }
    if( Card_Error_State.CardErrorState.Meter_Not_Prog_Status_Err ){
     Debug_Print("  δ����̼�  "  );
  }
    if( Card_Error_State.CardErrorState.Meter_Id_Set_Card_Id_Is_FULL_Err ){
     Debug_Print("  ������ÿ����������  "  );
  }
    if(Card_Error_State.CardErrorState. Password_Count_Number_Is_Zero_Err ){
     Debug_Print("   ��Կ���޸Ĵ���Ϊ����� "  );
  }
    if(Card_Error_State.CardErrorState.Password_State_Err  ){
     Debug_Print("  ��Կ��״̬����  "  );
  }
    if(Card_Error_State.CardErrorState.ESAM_DO_ERR  ){
     Debug_Print("  ESAM��������  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_Para_Card_Version_Err){
     Debug_Print("  �������ÿ��汾��������������  "  );
  }
    if( Card_Error_State.CardErrorState.CPU_NEW_CARD_INI_ERR ){
     Debug_Print("  �Ѿ������Ŀ������ظ���δ��ǰδ������  "  );
  }
    if( Card_Error_State.CardErrorState. ReadWriteE2romErr){
     Debug_Print("  ��дE������  "  );
  }

}

