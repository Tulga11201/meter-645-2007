#define DATA_SPEC_C
#include <includes.h>

//Ԥ����һЩ����������
INT16U Get_Freeze_Data(PROTO_DI DI,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT16U Len;
  
  *pErr=NO_ERR;
  if(0xEF00==DI)
  {
    Len=Get_Period_Freeze_Data((S_Freeze_Data *)&Freeze_Data[0],(INT8U *)pDst,(INT8U *)pDst,DstLen);
    ASSERT(A_WARNING,Len==127);
    return Len-5;
  }
  else if(0xEF02==DI)
  {
    Len=Get_Period_Freeze_Data((S_Freeze_Data *)&Freeze_Data[1],(INT8U *)pDst,(INT8U *)pDst,DstLen);
    ASSERT(A_WARNING,Len==149);
    return Len-5;
  }

  return 0;
}

//pSrc��ָ���ʱ���ǰBef_Mon���µ�ʱ��,���ص�ʱ��ŵ�pDst��
//ǰ�����µ�ʱ����㲻������Ȼ��Ϊ��׼�ģ������Խ���ʱ���Ϊ�·ֽ��ߵ�
void Calc_HIS_Data_Time(S_HEX_Time *pSrc,INT8U Bef_Mon,S_HEX_Time *pDst)
{
  //S_HEX_Time Temp_Time;
  //if(pSrc->Time[T_MIN])
  //���ҵ�pSrc���µĶ���ʱ���
  Get_Next_Freeze_Time(pSrc,pDst);
  Time_Dec(pDst,Bef_Mon,UNIT_MON,pDst);//���µĶ���ʱ���

}

//��������й�����
void Calc_Active_Comm_Energy(S_Energy *pEnergy)
{
  INT8U Re;
  INT8U i;
  
  Re=CHECK_STRUCT_SUM(Mode_Word);
  ASSERT(A_WARNING,1==Re);//��ҪCheck_Data_Avail()����ֹGet_DLT645_Data����
  
  Re=Check_STRUCT_Sum(pEnergy,sizeof(S_Energy),pEnergy->CS,sizeof(pEnergy->CS));
  ASSERT(A_WARNING,1==Re);
  
  if(GET_BIT(Mode_Word.Mode[1].Byte,2))//�й���=��+��
  {
    for(i=0;i<=MAX_RATES;i++)//���й��Լ��ַ����й�
      pEnergy->Pos_Active[i]=pEnergy->Pos_Active[i]+pEnergy->Neg_Active[i];

    for(i=0;i<3;i++)//�����й�
      pEnergy->Phase_Pos_Active[i]=pEnergy->Phase_Pos_Active[i]+pEnergy->Phase_Neg_Active[i];

    Set_STRUCT_Sum(pEnergy,sizeof(S_Energy),pEnergy->CS,sizeof(pEnergy->CS));
  }
}

//������ֵ��������еĸ��������
INT8U Calc_Reac_Comm_Energy(INT8U Type,S_Energy *pEnergy,INT8U Rate,void *pDst,void *pDst_Start,INT8U DstLen)
{
  INT32S S_Data=0;
  INT8U i;
  INT8U Re;
  
  Re=CHECK_STRUCT_SUM(Mode_Word);
  ASSERT(A_WARNING,1==Re);//��ҪCheck_Data_Avail()����ֹGet_DLT645_Data����
  
  if(POS_REACTIVE==Type)//����޹�1��Ҳ���������޹�
  {
    for(i=0;i<4;i++)//��1-4�����������
    {
      if(GET_BIT(Mode_Word.Mode[5].Byte,i))//�����޲������ 
      {
        if(GET_BIT(Mode_Word.Mode[5].Byte,4+i)==0)//��
          S_Data+=pEnergy->Quad_Reactive[i][Rate];
        else
          S_Data-=pEnergy->Quad_Reactive[i][Rate];
      }
    }
  }
  else if(NEG_REACTIVE==Type)//����޹�2,Ҳ���Ƿ���
  {
    for(i=0;i<4;i++)//��1-4�����������
    {
      if(GET_BIT(Mode_Word.Mode[6].Byte,i))//�����޲������ 
      {
        if(GET_BIT(Mode_Word.Mode[6].Byte,4+i)==0)//��
          S_Data+=pEnergy->Quad_Reactive[i][Rate];
        else
          S_Data-=pEnergy->Quad_Reactive[i][Rate];
      }
    }    
  }
  else if(PHASE_A_POS_REACTIVE==Type || PHASE_B_POS_REACTIVE==Type || PHASE_C_POS_REACTIVE==Type)//ABC��������޹�1
  {
    for(i=0;i<4;i++)//��1-4�����������
    {
      if(GET_BIT(Mode_Word.Mode[5].Byte,i))//�����޲������ 
      {
        if(GET_BIT(Mode_Word.Mode[5].Byte,4+i))//��
          S_Data+=pEnergy->Phase_Quad_Reactive[Type-PHASE_A_POS_REACTIVE][i];
        else
          S_Data-=pEnergy->Phase_Quad_Reactive[Type-PHASE_A_POS_REACTIVE][i];
      }
    }    
  }
  else if(PHASE_A_NEG_REACTIVE==Type || PHASE_B_NEG_REACTIVE==Type || PHASE_C_NEG_REACTIVE==Type)//ABC��������޹�2
  {
    for(i=0;i<4;i++)//��1-4�����������
    {
      if(GET_BIT(Mode_Word.Mode[6].Byte,i))//�����޲������ 
      {
        if(GET_BIT(Mode_Word.Mode[6].Byte,4+i))//��
          S_Data+=pEnergy->Phase_Quad_Reactive[Type-PHASE_A_NEG_REACTIVE][i];
        else
          S_Data-=pEnergy->Phase_Quad_Reactive[Type-PHASE_A_NEG_REACTIVE][i];
      }
    }    
  }
  mem_cpy(pDst,&S_Data,sizeof(S_Data),pDst,DstLen);
  return 4;  
}

//����׼645�ĵ�ǰ����ʷ�������������ݵ�DIת��Ϊ�Լ������DI
//���ǽ� 0x9XXX��0xAXXX��0xBXXXת��Ϊ0x6XXX��0x7XXX��0x8XXX
INT16U Convert_645_HIS_DI(PROTO_DI DI,INT8U *pErr)
{
  INT16U TempDI;
  
  *pErr=NO_ERR;
  
  TempDI=0;
  if((DI & 0xF000)==0x9000)//������
    TempDI|=0x6000;
  else if((DI & 0xF000)==0xA000)//������
    TempDI|=0x7000;
  else if((DI & 0xF000)==0xB000)//������ʱ��
    TempDI|=0x8000;
  else
  {
    *pErr=PROTOCOL_DI_ERR;
    return 0;
  }
  
  TempDI|=(DI & 0x0C00)>>2;//ʱ��
  switch((DI & 0x03F0)>>4)//��������
  {
  case 0x01://�����й�
    TempDI|=0x0000;
    break;
  case 0x02://�����й�
    TempDI|=0x0020;
    break;
  case 0x11://����޹�1,�����޹�
    TempDI|=0x0010;
    break;
  case 0x12://����޹�2,�����޹�
    TempDI|=0x0030;
    break;
  case 0x13://һ�����޹�
    TempDI|=0x0040;
    break;
  case 0x14://�������޹�
    TempDI|=0x0050;
    break;
  case 0x15://�������޹�
    TempDI|=0x0060;
    break;
  case 0x16://�������޹�
    TempDI|=0x0070;
    break;
  default:
    *pErr=PROTOCOL_DI_ERR;
    return 0;
  }
  TempDI|=(DI & 0x000F);//���ʺ�
  return TempDI; 
  
}

//��ȡ��ʷ�ĵ�ѹͳ������
INT16U Get_HIS_VolStat_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT8U Bef_Mon,i;//ǰ��������
  INT16U Len;
  S_HEX_Time Temp_Time;
  S_VolStat *pSrc;
  
  //������ʷ��ѹͳ������
  if(DI>=0xB220 && DI<=0xB224)
  {
    if(DI>=0xB222 && DI<=0xB224)//��1-3��
    {
      Bef_Mon=(INT8U)(DI-0xB221);//��ǰ�������ݣ�
      Calc_HIS_Data_Time((S_HEX_Time *)&Cur_Time0,Bef_Mon,&Temp_Time);
      Len=Read_HIS_Data(HIS_VOLSTAT_DATA,&Temp_Time,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
      if(sizeof(S_VolStat)!=Len || NO_ERR!=*pErr)//û�ж�����
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read_HIS_Data return len=%d,Err_Flag=%d",Len,*pErr);
        mem_set((void *)Pub_Buf,0,sizeof(S_VolStat),(void *)Pub_Buf,sizeof(Pub_Buf));
      } 
      
      pSrc=(S_VolStat *)Pub_Buf;
    }
    else if(DI==0xB221)//����    
      pSrc=&Cur_VolStat;
    else if(DI==0xB220)//������
      pSrc=&Total_VolStat;
    
    //�����ѹ�������
    for(i=0;i<3;i++)
    {
      Hex2Bcd(pSrc->Total_Time[0],pDst+i*12,4,pDst_Start,DstLen);//�����ʱ��
      Hex2Bcd(pSrc->Upper_Time[0],pDst+i*12+4,4,pDst_Start,DstLen);//����ʱ��
      Hex2Bcd(pSrc->Lower_Time[0],pDst+i*12+8,4,pDst_Start,DstLen);//����ʱ��
    }
    *pErr=NO_ERR;
    return 36;
  }
  //��ѹ�ϸ�������,����->��3��
  else if((DI>=0xE501 && DI<=0xE503) ||\
          (DI>=0xE511 && DI<=0xE513) ||\
          (DI>=0xE521 && DI<=0xE523) ||\
          (DI>=0xE531 && DI<=0xE533))
  {
    Bef_Mon=((DI & 0x00F0)>>4);

    if(Bef_Mon==0)//����
      pSrc=(S_VolStat *)Pub_Buf;
    else
    {
      //Time_Dec((S_HEX_Time *)&Cur_Time0,Bef_Mon,UNIT_MON,(S_HEX_Time *)&Temp_Time);//��ʱ����ǰ����Bef_Mon����
      Calc_HIS_Data_Time((S_HEX_Time *)&Cur_Time0,Bef_Mon,&Temp_Time);
      Len=Read_HIS_Data(HIS_VOLSTAT_DATA,&Temp_Time,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
      if(sizeof(S_VolStat)!=Len || NO_ERR!=*pErr)//û�ж�����
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read_HIS_Data return len=%d,Err_Flag=%d",Len,*pErr);
        mem_set((void *)Pub_Buf,0,sizeof(S_VolStat),(void *)Pub_Buf,sizeof(Pub_Buf));
      }
      
      pSrc=(S_VolStat *)Pub_Buf;      
    }
    
    i=(DI & 0x000F)-1;//A\B\C��������0-2
    
    Hex2Bcd(pSrc->Qual[i],pDst,3,pDst_Start,DstLen);    
    *pErr=NO_ERR;
    return 3;    
  }
  return 0;
}

//��ȡ��ǰ->��HIS_ENERGY_DATA_MONTHS����ʷ����
INT16U Get_HIS_Energy_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr)
{
  INT8U *pSrc,Bef_Mon,Comm_Flag;//Comm_Flag��ʾ����޹���־��1��ʾ������޹�����
  INT32U Data;
  INT32S S_Data;//�з�����
  S_HEX_Time Temp_Time;
  INT16U Len;

  //��ȡ��0->��HIS_ENERGY_DATA_MONTHS�µ�������
  Comm_Flag=0;
  if((DI & 0xF000)==0x6000) //|| (DI & 0xF000)==0x7000 || (DI & 0xF000)==0x8000)
  {
    if(ASSERT(A_WARNING,((DI & 0x0F00)>>8)<=HIS_ENERGY_DATA_MONTHS &&\
                        ((DI & 0x00F0)>>4)<=7 &&\
                        (DI & 0x000F)<=MAX_RATES))
    {
      *pErr=PROTOCOL_DI_ERR;
      return 0;
    }
    //////////////////////��ROM�ж�ȡ��ʷ�������ݡ����RAM�ж�ȡ��ǰ����////////////////////
    Bef_Mon=(INT8U)((DI & 0x0F00)>>8);//��ǰ�������ݣ�
    //Time_Dec((S_HEX_Time *)&Cur_Time0,Bef_Mon,UNIT_MON,(S_HEX_Time *)&Temp_Time);//��ʱ����ǰ����Bef_Mon����
    //����ʷ����
    if(Bef_Mon!=0)//�Ǳ���
    {
      Calc_HIS_Data_Time((S_HEX_Time *)&Cur_Time0,Bef_Mon,&Temp_Time);
      Len=Read_HIS_Data(HIS_ENERGY_DATA,&Temp_Time,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
      if(ENERGY_SAVE_SIZE!=Len || NO_ERR!=*pErr)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read_HIS_Data return len=%d,Err_Flag=%d",Len,*pErr);
        if(NO_ERR==*pErr)
          *pErr=PROTOCOL_DATA_ERR;
        return 0;
      }
      pSrc=(INT8U *)Pub_Buf;
    }
    else//��ǰ���ݣ�ֱ�Ӵ��ڴ���ȡ
    {
      mem_cpy((void *)Pub_Buf,(void *)&Cur_Energy,sizeof(Cur_Energy),(void *)Pub_Buf,sizeof(Pub_Buf));
      pSrc=(INT8U *)Pub_Buf;
    }
    
    Calc_Active_Comm_Energy((S_Energy *)pSrc);//��������й�
      
    switch(((DI & 0x00F0)>>4))
    {
      case 0:
        pSrc+=S_OFF(S_Energy,Pos_Active[0]);//�����й�
        break;
      case 1:
        Calc_Reac_Comm_Energy(POS_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));//����޹�1
        Comm_Flag=1;
        break;
      case 2:
        pSrc+=S_OFF(S_Energy,Neg_Active[0]);//�����й�
        break;
      case 3:
        Calc_Reac_Comm_Energy(NEG_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));//����޹�2
        Comm_Flag=1;
        break;
      case 4:
        pSrc+=S_OFF(S_Energy,Quad_Reactive[0][0]);//һ�����޹�
        break;
      case 5:
        pSrc+=S_OFF(S_Energy,Quad_Reactive[3][0]);//�������޹�
        break;
      case 6:
        pSrc+=S_OFF(S_Energy,Quad_Reactive[1][0]);//�������޹�
        break;
      case 7:
        pSrc+=S_OFF(S_Energy,Quad_Reactive[2][0]);//�������޹�
        break;
      default:
        *pErr=PROTOCOL_DI_ERR;
        return 0;
    }
    if(0==Comm_Flag)
      pSrc+=(DI & 0x000F)*4;//�������ƫ��
  }
  ///////////////////////������ʷ��������////////////////////
  else if((DI & 0xFF00)==0xE700 && ((DI & 0x00F0)>>4)<=HIS_ENERGY_DATA_MONTHS)
  {
    Bef_Mon=(INT8U)((DI & 0x00F0)>>4);//��ǰ�������ݣ�
    
    if(Bef_Mon==0)//����
    {
      mem_cpy((void *)Pub_Buf,(void *)&Cur_Energy,sizeof(Cur_Energy),(void *)Pub_Buf,sizeof(Pub_Buf));
      pSrc=(INT8U *)Pub_Buf;
    }
    else//�Ǳ���
    {
      Calc_HIS_Data_Time((S_HEX_Time *)&Cur_Time0,Bef_Mon,&Temp_Time);
      Len=Read_HIS_Data(HIS_ENERGY_DATA,&Temp_Time,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
      if(ENERGY_SAVE_SIZE!=Len || NO_ERR!=*pErr)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read_HIS_Data return len=%d,Err_Flag=%d",Len,*pErr);
        if(NO_ERR==*pErr)
          *pErr=PROTOCOL_DATA_ERR;
        return 0;
      }
      
      pSrc=(INT8U *)Pub_Buf;      
    }

    Calc_Active_Comm_Energy((S_Energy *)pSrc);//��������й�
    
    switch(DI & 0x000F)
    {
    case 1:
      pSrc+=S_OFF(S_Energy,Phase_Pos_Active[0]);//A������
      break;
    case 2:
      pSrc+=S_OFF(S_Energy,Phase_Pos_Active[1]);//B������
      break;
    case 3:
      pSrc+=S_OFF(S_Energy,Phase_Pos_Active[2]);//C������
      break;
    case 4:
      Calc_Reac_Comm_Energy(PHASE_A_POS_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));////A������
      Comm_Flag=1;
      break;
    case 5:
      Calc_Reac_Comm_Energy(PHASE_B_POS_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));////B������
      Comm_Flag=1;
      break;
    case 6:
      Calc_Reac_Comm_Energy(PHASE_C_POS_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));////C������
      Comm_Flag=1;
      break;
    case 7:
      pSrc+=S_OFF(S_Energy,Phase_Neg_Active[0]);//A�෴��
      break;
    case 8:
      pSrc+=S_OFF(S_Energy,Phase_Neg_Active[1]);//B�෴��
      break;
    case 9:
      pSrc+=S_OFF(S_Energy,Phase_Neg_Active[2]);//C�෴��
      break;
    case 0x0A:
      Calc_Reac_Comm_Energy(PHASE_A_NEG_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));////A�෴��
      Comm_Flag=1;
      break;
    case 0x0B:
      Calc_Reac_Comm_Energy(PHASE_B_NEG_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));////B�෴��
      Comm_Flag=1;
      break;
    case 0x0C:
      Calc_Reac_Comm_Energy(PHASE_C_NEG_REACTIVE,(S_Energy *)pSrc,(INT8U)(DI & 0x000F),&S_Data,&S_Data,sizeof(S_Data));////C�෴��
      Comm_Flag=1;
      break;
    default:
      *pErr=PROTOCOL_DI_ERR;
      return 0;
    }    
  }
  
  ////////////////////////////////������ת��ΪBCD��///////////////////////////////////////////  
  if(FOR_DISP==Data_Flag && 3==Get_Energy_Disp_Digs())//��ʾ����С��λ��Ϊ3
  {
    if(0==Comm_Flag)//�����޹���ϵ�������
    {
      mem_cpy(&Data,pSrc,4,&Data,sizeof(Data));//Data=*(INT32U *)pSrc;
      Hex2Bcd(Data,pDst,4,pDst_Start,DstLen);//ת����BCD��
    }
    else
      S_Hex2Bcd(S_Data,pDst,4,pDst_Start,DstLen);
  }
  else//��ʾ��Э��С��λһ��,����2λ
  {
    if(0==Comm_Flag)//�����޹���ϵ�������
    {
      mem_cpy(&Data,pSrc,4,&Data,sizeof(Data));
      Data=Data/10;//ԭ������3λС����Э������2λ����/10
      Hex2Bcd(Data,pDst,4,pDst_Start,DstLen);//ת����BCD��      
    }
    else
    {
      S_Data=S_Data/10;
      S_Hex2Bcd(S_Data,pDst,4,pDst_Start,DstLen);//ת����BCD��      );
    }
  }
  *pErr=NO_ERR;
  return 4;
}

//��ȡ��ʷ��������
//DI���ݱ�ʶ
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�����ֵ���Ⱥ�pDst
//Data_Flag��ʾ�Ƿ����ʾ
//pErr�����ʶ��,������Ϊ0ʱ��
//���ض�ȡ�������ݳ���
INT16U Get_HIS_Demand_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr)
{
  INT8U *pSrc,Bef_Mon,Re,Rate;
  INT32U Off,Data;
  S_HEX_Time Temp_Time;
  INT16U Len;
  //��ȡ��0->��HIS_ENERGY_DATA_MONTHS�µ�������
  if((DI & 0xF000)==0x7000 || (DI & 0xF000)==0x8000)
  {
    if((DI & 0xF000)==0x7000 || (DI & 0xF000)==0x8000)
    {
      if(ASSERT(A_WARNING,((DI & 0x0F00)>>8)<=HIS_DEMAND_DATA_MONTHS &&\
                          ((DI & 0x00F0)>>4)<=7 &&\
                          (DI & 0x000F)<=MAX_RATES))
      {
        *pErr=PROTOCOL_DI_ERR;
        return 0;
      }
    }
/*
    if((DI & 0xF000)==0x7000)
      Storage_DI=HIS_DEMAND;//����
    else
      Storage_DI=HIS_DEMAND_TIME;//����ʱ��
*/    
    //////////////////////��ROM�ж�ȡ��ʷ�������ݡ����RAM�ж�ȡ��ǰ����////////////////////
    
    Bef_Mon=(INT8U)((DI & 0x0F00)>>8);//��ǰ�������ݣ�
    Rate=(INT8U)(DI & 0x000F);//��ȡ�ĸ����ʵ�����?

    //Time_Dec((S_HEX_Time *)&Cur_Time0,Bef_Mon,UNIT_MON,(S_HEX_Time *)&Temp_Time);//��ʱ����ǰ����Bef_Mon����

    //����ʷ����
    if(Bef_Mon!=0)//�Ǳ���
    {
      Calc_HIS_Data_Time((S_HEX_Time *)&Cur_Time0,Bef_Mon,&Temp_Time);
      Len=Read_Demand_HIS_Data(Rate,&Temp_Time,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
      if(ONE_DEMAND_SAVE_SIZE!=Len || NO_ERR!=*pErr)
      {
        DEBUG_PRINT(HUCK,DEBUG_0,"Read_Demand_HIS_Data return len=%d,Err_Flag=%d",Len,*pErr);
        //û�ж�������Ĭ������Ϊ0������ʱ��ҲΪ0
        mem_set((void *)Pub_Buf,0,sizeof(S_One_Demand),(void *)Pub_Buf,sizeof(Pub_Buf));
      }
      pSrc=(INT8U *)Pub_Buf;
    }
    else//��ǰ����
    {
      if(Rate!=Cur_Demand.Rate && Rate!=0)//�ǵ�ǰ����Ҳ���ܣ������ݲ���RAM�ڴ���
      {
        Off=DEMAND_RATE_OFF(Rate);
        //�ȶ�ȡ��ǰ��������������ȡ�������ȡ��ǰ��������������
        Len=Read_Storage_Data_Fix_Len(CUR_DEMAND,Off,ONE_DEMAND_SAVE_SIZE,\
                                      (void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
        if(ASSERT(A_WARNING,0!=Len && NO_ERR==*pErr))
        {
          //���洢��û�ж���������ݴ洢��
          Len=Read_Storage_Data_Fix_Len(CUR_DEMAND_BAK,Off,ONE_DEMAND_SAVE_SIZE,\
                                        (void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr);
          if(ASSERT(A_WARNING,0!=Len && NO_ERR==*pErr))
          {
            //û�ж�������Ĭ������Ϊ0������ʱ��ҲΪ0
            mem_set((void *)Pub_Buf,0,sizeof(S_One_Demand),(void *)Pub_Buf,sizeof(Pub_Buf));
          }
        }
        pSrc=(INT8U *)Pub_Buf;
        
        //�������������ʱ�䲻���ϣ���Ĭ�Ϸ����������Ϊ0,��������ʱ��ҲΪ0
        if(((S_One_Demand *)pSrc)->Time.Time[T_YEAR]!=Temp_Time.Time[T_YEAR] ||\
           ((S_One_Demand *)pSrc)->Time.Time[T_MONTH]!=Temp_Time.Time[T_MONTH])
        {
          //û�ж�������Ĭ������Ϊ0������ʱ��ҲΪ0
           mem_set((void *)pSrc,0,sizeof(S_One_Demand),(void *)pSrc,sizeof(S_One_Demand));
        }
      }
      else if(Rate==0)//����������������ڴ���
      {
        mem_cpy((void *)Pub_Buf,(INT8U *)&Cur_Demand.Demand[0],sizeof(S_One_Demand),(void *)Pub_Buf,sizeof(Pub_Buf));
        pSrc=(INT8U *)Pub_Buf;//������������
      }
      else//��ǰ������������Ҳ���ڴ���
      {
        mem_cpy((void *)Pub_Buf,(INT8U *)&Cur_Demand.Demand[1],sizeof(S_One_Demand),(void *)Pub_Buf,sizeof(Pub_Buf));
        pSrc=(INT8U *)Pub_Buf;//������������        
      }
    }


    if((DI & 0xF000)==0x7000)//��������
    {
      switch(((DI & 0x00F0)>>4))
      {
      case 0:
        pSrc+=S_OFF(S_One_Demand,Pos_Active);//�����й�
        break;
      case 1:
        pSrc+=S_OFF(S_One_Demand,Pos_Reactive);//����޹�1
        break;
      case 2:
        pSrc+=S_OFF(S_One_Demand,Neg_Active);//�����й�
        break;
      case 3:
        pSrc+=S_OFF(S_One_Demand,Neg_Reactive);//����޹�2
        break;
      case 4:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive);//һ�����޹�
        break;
      case 5:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive[3]);//�������޹�
        break;
      case 6:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive[1]);//�������޹�
        break;
      case 7:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive[2]);//�������޹�
        break;
      default:
        *pErr=PROTOCOL_DI_ERR;
        return 0;
      }      
      //pSrc+=(DI & 0x000F)*4;//�������ƫ��    
    }
    else//����ʱ������
    {
      switch(((DI & 0x00F0)>>4))
      {
      case 0:
        pSrc+=S_OFF(S_One_Demand,Pos_Active_Time[0]);//�����й�
        break;
      case 1:
        pSrc+=S_OFF(S_One_Demand,Pos_Reactive_Time[0]);//����޹�1
        break;
      case 2:
        pSrc+=S_OFF(S_One_Demand,Neg_Active_Time[0]);//�����й�
        break;
      case 3:
        pSrc+=S_OFF(S_One_Demand,Neg_Reactive_Time[0]);//����޹�2
        break;
      case 4:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive_Time[0][0]);//һ�����޹�
        break;
      case 5:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive_Time[3][0]);//�������޹�
        break;
      case 6:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive_Time[1][0]);//�������޹�
        break;
      case 7:
        pSrc+=S_OFF(S_One_Demand,Quad_Reactive_Time[2][0]);//�������޹�
        break;
      default:
        *pErr=PROTOCOL_DI_ERR;
        return 0;
      }       
    }
  }
   
  ////////////////////////////////������ת��ΪBCD��///////////////////////////////////////////  
  if((DI & 0xF000)==0x7000)//��������
  {
    mem_cpy(&Data,pSrc,4,&Data,sizeof(Data));
    Hex2Bcd(Data,pDst,3,pDst_Start,DstLen);//ת����BCD��

    *pErr=NO_ERR;
    return 3;    
    
  }
  else//����ʱ��
  {
    Re=CHECK_STRUCT_SUM(Mode_Word);
    if(ASSERT(A_WARNING,0!=Re))
      Check_Data_Avail();
    
    if(Mode_Word.Mode[7].Bit.Bit6==0)//����ģʽ���ж������Ƿ����
    {
      mem_cpy(pDst,pSrc,5,pDst_Start,DstLen);
      *pErr=NO_ERR;
      return 5;
    }
    else
    {
      mem_cpy(pDst,pSrc,4,pDst_Start,DstLen);
      *pErr=NO_ERR;
      return 4;
    }
  }  
}
//DI�����ǽڼ�����0xC411->0xC41D����0xCC11->0xCC1D
//*pDstĿ�껺����
//*pDst_StartĿ�껺��������ʼ��ַ
//DstLen��*pDst_Startһ������*pDst
//ע��:�ú����ڲ�ʹ����Pub_Buf����
//�����ⲿ����OS_Sem_Pend��OS_Sem_Post��������
INT16U Get_Holiday_Spec_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  if(DI>=0xC411 && DI<=0xC41D)
  {
    if(Read_Storage_Data(0xC41F,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr)==45)
    {
      mem_cpy(pDst,(INT8U *)Pub_Buf+(DI-0xC411)*3,3,pDst_Start,DstLen);
      return 3;
    }
    else
    {
      if(NO_ERR==*pErr)
        *pErr=PROTOCOL_DATA_ERR;        
      return 0;
    }
  }
  else if(DI>=0xCC11 && DI<=0xCC1D)
  {
    if(Read_Storage_Data(0xCC1F,(void *)Pub_Buf,(void *)Pub_Buf,sizeof(Pub_Buf),pErr)==45)
    {
      mem_cpy(pDst,(INT8U *)Pub_Buf+(DI-0xCC11)*3,3,pDst_Start,DstLen);
      return 3;
    }
    else
    {
      if(NO_ERR==*pErr)
        *pErr=PROTOCOL_DATA_ERR;        
      return 0;
    }   
  }  
  *pErr=PROTOCOL_DI_ERR;        
  return 0; 
}
/*
  {0xB710,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1117,SPEC_CUMU_EVENT},	
  {0xB720,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1116,SPEC_CUMU_EVENT},
  {0xB730,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1114,SPEC_CUMU_EVENT},
  {0xB740,DI_EQU_NULL,1,1,PSW_RD_ONLY,S_RAM,(void *)0,0,4,S_INTU,0,4,0x1115,SPEC_CUMU_EVENT},
*/
//���ĳ��DI��Ӧ���¼��������Ƿ���RAM��?
//�������ֻ���0xB71X,0xB72X,0xB73X,0xB74X
INT8U Check_Cumu_Event_Data_In_Ram(PROTO_DI DI)
{
  switch(DI)
  {
    //ʧѹ
    case 0xB710://A��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_A_LOSS_VOLT)?1:0);
    case 0xB711://B��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_B_LOSS_VOLT)?1:0);
    case 0xB712://C��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_C_LOSS_VOLT)?1:0);
    case 0xB713://AB��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_AB_LOSS_VOLT)?1:0);
    case 0xB714://AC��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_AC_LOSS_VOLT)?1:0);
    case 0xB715://BC��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_BC_LOSS_VOLT)?1:0);
    case 0xB716://ABC��ʧѹ
      return ((Event_Cumu.Event_Flag.Loss_Vol_Flag_Bak==ID_EVENT_ABC_LOSS_VOLT)?1:0);
    //ʧ��
    case 0xB720://A��ʧ��
      return ((Event_Cumu.Event_Flag.Loss_Cur_Flag_Bak==ID_EVENT_A_LOSS_CURR)?1:0);
    case 0xB721://B��ʧ��
      return ((Event_Cumu.Event_Flag.Loss_Cur_Flag_Bak==ID_EVENT_B_LOSS_CURR)?1:0);
    case 0xB722://C��ʧ��
      return ((Event_Cumu.Event_Flag.Loss_Cur_Flag_Bak==ID_EVENT_C_LOSS_CURR)?1:0);
    case 0xB723://AB��ʧ��
      return ((Event_Cumu.Event_Flag.Loss_Cur_Flag_Bak==ID_EVENT_AB_LOSS_CURR)?1:0);
    case 0xB724://AC��ʧ��
      return ((Event_Cumu.Event_Flag.Loss_Cur_Flag_Bak==ID_EVENT_AC_LOSS_CURR)?1:0);
    case 0xB725://BC��ʧ��
      return ((Event_Cumu.Event_Flag.Loss_Cur_Flag_Bak==ID_EVENT_BC_LOSS_CURR)?1:0);
      //����,�����ݳ�פ�ڴ�
    case 0xB730://�ܷ���
    case 0xB731://A�෴��
    case 0xB732://B�෴��
    case 0xB733://C�෴��
      return 1;
      //����,�����ݳ�פ�ڴ�
    case 0xB740://A�����
    case 0xB741://B�����
    case 0xB742://C�����
      return 1;
    default:
      break;
  }
  return 0;
}

//ͨ��Э���ȡ��Լ����,�ۼ��¼����ݵĶ�ȡ
INT16U Get_Cumu_Event_Data(PROTO_DI DI,void *pDst,void *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT8U *p;
  STORA_DI Storage_DI;
  S_Multi_Data *pData;
  INT16U Len=0;
  
  *pErr=NO_ERR;
  if(0xB743==DI)//ȫʧѹ���⴦��
  {
    Hex2Bcd(Event_Cumu.Phase_Loss_Vol[8].Time,pDst,4,pDst_Start,DstLen);
    Hex2Bcd(Event_Cumu.Phase_Loss_Vol[8].Counts,(INT8U *)pDst+4,2,pDst_Start,DstLen);
    return 6;
  }
  else if(0xB744==DI)//ȫʧ�����⴦��
  {
    Hex2Bcd(Event_Cumu.Phase_Loss_Cur[7].Time,pDst,4,pDst_Start,DstLen);
    Hex2Bcd(Event_Cumu.Phase_Loss_Cur[7].Counts,(INT8U *)pDst+4,2,pDst_Start,DstLen);
    return 6;    
  }
  
  OS_Sem_Pend(PUB_BUF0_SEM_ID); //����Ĳ��ֲ������� return��һ��Ҫ��OS_Sem_Post
  if(Check_Cumu_Event_Data_In_Ram(DI))//���ڴ���?
  {
    //���ڴ��е����ݻ�ȡ������ʼλ��
    switch(DI)
    {
    case 0xB710://A��ʧѹ
    case 0xB711://B��ʧѹ
    case 0xB712://C��ʧѹ
    case 0xB713://ABʧѹ
    case 0xB714://ACʧѹ
    case 0xB715://BCʧѹ
    case 0xB716://ABCʧѹ
      p=(INT8U *)&Event_Cumu.Loss_Vol;
      break;
    //ʧ��
    case 0xB720://A��ʧ��
    case 0xB721://B��ʧ��
    case 0xB722://C��ʧ��
    case 0xB723://AB��ʧ��
    case 0xB724://AC��ʧ��
    case 0xB725://BC��ʧ��
      p=(INT8U *)&Event_Cumu.Loss_Cur;
      break;
      //����,�����ݳ�פ�ڴ�
    case 0xB730://�ܷ���
      p=(INT8U *)&Event_Cumu.Phase_Reverse[0];
      break;      
    case 0xB731://A�෴��
      p=(INT8U *)&Event_Cumu.Phase_Reverse[1];
      break;
    case 0xB732://B�෴��
      p=(INT8U *)&Event_Cumu.Phase_Reverse[2];
      break;
    case 0xB733://C�෴��
      p=(INT8U *)&Event_Cumu.Phase_Reverse[3];
      break;
    //����,�����ݳ�פ�ڴ�
    case 0xB740://A�����
      p=(INT8U *)&Event_Cumu.Phase_Break[0];
      break;
    case 0xB741://B�����
      p=(INT8U *)&Event_Cumu.Phase_Break[1];
      break;
    case 0xB742://C�����
      p=(INT8U *)&Event_Cumu.Phase_Break[2];
      break;
    default:
      *pErr=EVENT_ID_ERR;
      break;
    }
  }
  else//���ݲ����ڵ�ǰ�ڴ���,��Ҫ��ROM�ж���ͳ������
  {
    //��Ҫ��ROM�ж�ȡ����
    switch(DI)
    {
    case 0xB710://A��ʧѹ
      Storage_DI=_A_LOSS_VOL;
      break;
    case 0xB711://B��ʧѹ
      Storage_DI=_B_LOSS_VOL;
      break;
    case 0xB712://C��ʧѹ
      Storage_DI=_C_LOSS_VOL;
      break;
    case 0xB713://ABʧѹ
      Storage_DI=_AB_LOSS_VOL;
      break;
    case 0xB714://ACʧѹ
      Storage_DI=_AC_LOSS_VOL;
      break;
    case 0xB715://BCʧѹ
      Storage_DI=_BC_LOSS_VOL;
      break;
    case 0xB716://ABCʧѹ
      Storage_DI=_ABC_LOSS_VOL;
      break;
      
    //ʧ��
    case 0xB720://A��ʧ��
      Storage_DI=_A_LOSS_CUR;
      break;
    case 0xB721://B��ʧ��
      Storage_DI=_B_LOSS_CUR;
      break;
    case 0xB722://C��ʧ��
      Storage_DI=_C_LOSS_CUR;
      break;      
    case 0xB723://AB��ʧ��
      Storage_DI=_AB_LOSS_CUR;
      break;
    case 0xB724://AC��ʧ��
      Storage_DI=_AC_LOSS_CUR;
      break;
    case 0xB725://BC��ʧ��
      Storage_DI=_BC_LOSS_CUR;
      break;
    default:
      *pErr=EVENT_ID_ERR;
      break;
      //�����Ŀ϶����ڴ���
    }
    if(NO_ERR==*pErr)
    {
      if(Read_Storage_Data(Storage_DI,(void *)Pub_Buf0,(void *)Pub_Buf0,sizeof(Pub_Buf0),pErr) && NO_ERR==*pErr)
        p=(INT8U *)Pub_Buf0;
      else 
      {
        ASSERT(A_WARNING,0);
        if(*pErr==NO_ERR)
          *pErr=EVENT_DATA_ERR;
      }
    }
  }
  
  if(*pErr==NO_ERR)
  {
    pData=(S_Multi_Data *)0;//�������ݶ�Ӧ�ĸ�ʽ
    switch(DI)
    {
    case 0xB710://A��ʧѹ
    case 0xB711://B��ʧѹ
    case 0xB712://C��ʧѹ
    case 0xB713://ABʧѹ
    case 0xB714://ACʧѹ
    case 0xB715://BCʧѹ
      //case 0xB716://ABCʧѹ
      pData=(S_Multi_Data *)&Loss_Vol_Data;
      break;
    //ʧ��
    case 0xB720://A��ʧ��
    case 0xB721://B��ʧ��
    case 0xB722://C��ʧ��
    case 0xB723://AB��ʧ��
    case 0xB724://AC��ʧ��
    case 0xB725://BC��ʧ��
      pData=(S_Multi_Data *)&Loss_Cur_Data;
      break;
      //����,�����ݳ�פ�ڴ�
    case 0xB730://�ܷ���
    case 0xB731://A�෴��
    case 0xB732://B�෴��
    case 0xB733://C�෴��
      pData=(S_Multi_Data *)&Phase_Reverse_Data;
      break;
    case 0xB740://A�����
    case 0xB741://B�����
    case 0xB742://C�����
      pData=(S_Multi_Data *)&Phase_Break;
      break;
    default:
      *pErr=PROTOCOL_DI_ERR;
      break;
   }
   if(*pErr==NO_ERR && pData!=(S_Multi_Data *)0)
     Len=Get_Multi_Item_Data(p,pData,pDst,pDst_Start,DstLen);
   else
     ASSERT(A_WARNING,0);
  }
  OS_Sem_Post(PUB_BUF0_SEM_ID);
  return Len; 
}

//�ִ��¼���¼���ݵĶ�ȡ
INT16U Get_MultiTimes_Event_Data(PROTO_DI DI,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U *pErr)
{
  INT16U i,Len;
  STORA_DI Storage_DI;
  
  //��ȡ���ݵ�Index
  *pErr=NO_ERR;
  i=Get_Event_Data_Index_From_DI(DI);
  if(NULL_2BYTES==i)
    return 0;
  
  if(Event_Data_Info[i].Storage_Num==1)//ONE_RECORD_EVENT)
    return Read_Storage_Data(Event_Data_Info[i].Storage_DI,pDst,pDst_Start,DstLen,pErr);
  else
  {
    //�ȶ������һ���¼��Ĵ洢DI��Storage_DI
    Len=Read_Storage_Data(Event_Data_Info[i].Last_Storage_DI,pDst,pDst_Start,DstLen,pErr);
    if(ASSERT(A_WARNING,Len==sizeof(STORA_DI) && *pErr==NO_ERR)) //û�ж�ȡ���ϴη����¼��ļ�¼
    {
      *pErr=EVENT_DATA_ERR;
      return 0;
    }
    else
      mem_cpy(&Storage_DI,pDst,4,&Storage_DI,sizeof(Storage_DI));//Storage_DI=*(INT32U *)pDst;//��ȡ����4���ֽ����ϴδ洢�¼��Ĵ洢DI
    //Storage_DI��Ϊ�����һ�δ洢���ݵ�DI
    if(!(Storage_DI>=Event_Data_Info[i].Storage_DI &&\
      Storage_DI<Event_Data_Info[i].Storage_DI+Event_Data_Info[i].Storage_Num))
    {
      *pErr=EVENT_DATA_ERR;
      return 0;
    }
    
    if(Event_Data_Info[i].Storage_Num>10)
    {
      DI=Event_Data_Info[i].Storage_DI+Bcd2Hex_Byte((INT8U)(DI & 0xFF))-Bcd2Hex_Byte((INT8U)(Event_Data_Info[i].Storage_DI) & 0xFF);
      //DI=(DI & 0xFF00)+Bcd2Hex_Byte((INT8U)(DI & 0xFF));//��λ�ֽ�ת��Ϊ
    }
    //DIת��������ڼ��ε��¼�����?
    //Proto_DI�����һ�ε�DI
    if(DI>=Event_Data_Info[i].Storage_DI && DI<Event_Data_Info[i].Storage_DI+Event_Data_Info[i].Storage_Num)
      DI=DI-Event_Data_Info[i].Storage_DI;
    else
    {
      *pErr=PROTOCOL_DI_ERR;
      return 0;
    }
    
    if((Storage_DI-DI)<Event_Data_Info[i].Storage_DI)
      Storage_DI=Event_Data_Info[i].Storage_Num+Storage_DI-DI;
    else
      Storage_DI=Storage_DI-DI;
    
    return Read_Storage_Data(Storage_DI,pDst,pDst_Start,DstLen,pErr);
  }
}
//��ȡ645���������������Ҫ���⴦������Ҫ�ǵ�����������������ʱ���
//DI���ݱ�ʶ��
//pPara��ڲ�������Ҫ��S_HEX_Time���Ͳ���������ʷʱ��
//pDstĿ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س���
//Data_Flag,FOR_DISP��FOR_COMM����ʾ�ú����ṩ����ʾ����ͨ��
//��������1��ʾ��ȡ�ɹ�
//��������0��NO_ERR==*pErr��ʾ�����ݲ�������������
//��������0��*pErr!=NO_ERR��ʾ������������������,���ǻ�ȡ�д���
INT16U Get_DLT645_Spec_Single_Data(PROTO_DI DI,INT8U Spec_Flag,void *pPara,INT8U ParaLen,INT8U *pDst,INT8U *pDst_Start,INT16U DstLen,INT8U Data_Flag,INT8U *pErr)
{
  INT16U Len;
  *pErr=NO_ERR;
  INT32U Temp;

  //������������������ʱ��������
  //��0x9xxx,0xAxxx��0xBxxxӳ�䵽0x6xxx��0x7xxx��0x8xxx��ȥ
  if(((DI & 0xF000)==0x9000 || (DI & 0xF000)==0xA000 || (DI & 0xF000)==0xB000) &&\
    ((DI & 0x0C00)==0x0000 || (DI & 0x0C00)==0x0400 || (DI & 0x0C00)==0x0800) &&\
    ((DI & 0x0300)==0x0000 || (DI & 0x0300)==0x0100))
  {
    //DEBUG_PRINT(HUCK,DEBUG_0,"Get_Spec_Data Bef_Convert DI=%x\r\n",DI);
    DI=Convert_645_HIS_DI(DI,pErr);//ת����0x6000��0x7000��0x8000
    if(*pErr!=NO_ERR)
    {
      *pErr=PROTOCOL_DI_ERR;
      return 0;
    }
  }
  
  //��ȡ����->��HIS_ENERGY_DATA_MONTHS����ʷ����
  if((DI & 0xF000)==0x6000 ||\
    ((DI & 0xFF00)==0xE700 && ((DI & 0x00F0)>>4)<=HIS_ENERGY_DATA_MONTHS))//�������
  { 
    //DEBUG_PRINT(HUCK,DEBUG_0,"Get_HIS_Energy_Data DI=%x\r\n",DI);
    Len=Get_HIS_Energy_Data(DI,pDst,pDst_Start,DstLen,Data_Flag,pErr);
    if(ASSERT(A_WARNING,Len>0))
    {
      *pErr=PROTOCOL_DATA_ERR;
      return 0;
    }
    else
    {
      *pErr=NO_ERR;
      return Len;      
    }
  }
  else if((DI & 0xF000)==0x7000 || (DI & 0xF000)==0x8000)//��ʷ����
  { 
    //DEBUG_PRINT(HUCK,DEBUG_0,"Get_HIS_Demand_Data DI=%x\r\n",DI);
    Len=Get_HIS_Demand_Data(DI,pDst,pDst_Start,DstLen,Data_Flag,pErr);
    if(ASSERT(A_WARNING,Len>0))
    {
      *pErr=PROTOCOL_DATA_ERR;
      return 0;
    }
    else
    {
      *pErr=NO_ERR;
      return Len;      
    }
  }
  else if((DI>=0xC411 && DI<=0xC41D) || (DI>=0xCC11 && DI<=0xCC1D))//�ڼ������⴦��,���׷��ʷ�����ǰ1-13���ڼ�����Ҫ���⴦��
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Get_Holiday_Spec_Data DI=%x\r\n",DI);
    Len=Get_Holiday_Spec_Data(DI,pDst,pDst_Start,DstLen,pErr);      
    if(ASSERT(A_WARNING,Len>0))
    {
      *pErr=PROTOCOL_DATA_ERR;
      return 0;
    }
    else
    {
      *pErr=NO_ERR;
      return Len;      
    }
  }
  else if((DI>=0xB220 && DI<=0xB224) || (DI>=0xE501 && DI<=0xE533))//������ʷ��ѹͳ������
  {
    DEBUG_PRINT(HUCK,DEBUG_0,"Get_HIS_VolStat_Data DI=%x\r\n",DI);
    Len=Get_HIS_VolStat_Data(DI,pDst,pDst_Start,DstLen,pErr);      
    if(ASSERT(A_WARNING,Len>0))
    {
      *pErr=PROTOCOL_DATA_ERR;
      return 0;
    }
    else
    {
      *pErr=NO_ERR;
      return Len;     
    } 
  }
  else if(DI_ACTIVE_DIRECT==DI || DI_REACTIVE_DIRECT==DI)  //����������Ҫ�����޹���������
  {
    if(DI==DI_ACTIVE_DIRECT)
     *(INT8U *)pDst=(Meter_Run_Status.Meter_Stat2.Byte & 0x0F);
    else if(DI==DI_REACTIVE_DIRECT)
     *(INT8U *)pDst=(Meter_Run_Status.Meter_Stat2.Byte & 0xF0)>>4; 
    *pErr=NO_ERR;
    return 1;
  }
  else if(DI>=0xD110 && DI<=0xD115)  //����������
  {
    Len=Read_Load_Data(DI,(INT8U *)pPara,ParaLen,pDst,pDst_Start,DstLen,pErr);
    return Len;
  }
  else if(DI_CUR_TIME==DI)//��ǰBCDʱ��
  {
    ASSERT(A_WARNING,pDst>=pDst_Start && pDst+5<=pDst_Start+DstLen);
    //�˴�����ֱ�Ӷ�ȡ�ڲ�ʱ�ӣ���Ϊ�ϵ紦�����ǰ�¼�ʱ�Ὣ����ǰʱ�临�Ƶ�Cur_Time1
    *(INT8U *)pDst=Cur_Time1.Min;//Hex2Bcd_Byte(Cur_Time0.Time[T_MIN);
    *((INT8U *)pDst+1)=Cur_Time1.Hour;//Hex2Bcd_Byte(Cur_Time0.Time[T_HOUR);
    *((INT8U *)pDst+2)=Cur_Time1.Date;//Hex2Bcd_Byte(Cur_Time0.Time[T_DATE);
    *((INT8U *)pDst+3)=Cur_Time1.Month;//Hex2Bcd_Byte(Cur_Time0.Time[T_MONTH);
    *((INT8U *)pDst+4)=Cur_Time1.Year;//Hex2Bcd_Byte(Cur_Time0.Time[T_YEAR);
    return 5;
  }
  else if(DI_EVENT_TIME==DI)//�¼�����BCDʱ��
  {
    ASSERT(A_WARNING,pDst>=pDst_Start && pDst+5<=pDst_Start+DstLen);
    //�˴�����ֱ�Ӷ�ȡ�ڲ�ʱ�ӣ���Ϊ�ϵ紦�����ǰ�¼�ʱ�Ὣ����ǰʱ�临�Ƶ�Cur_Time1
    *(INT8U *)pDst=Event_Cumu.Event_Time.Min;//Hex2Bcd_Byte(Cur_Time0.Time[T_MIN);
    *((INT8U *)pDst+1)=Event_Cumu.Event_Time.Hour;//Hex2Bcd_Byte(Cur_Time0.Time[T_HOUR);
    *((INT8U *)pDst+2)=Event_Cumu.Event_Time.Date;//Hex2Bcd_Byte(Cur_Time0.Time[T_DATE);
    *((INT8U *)pDst+3)=Event_Cumu.Event_Time.Month;//Hex2Bcd_Byte(Cur_Time0.Time[T_MONTH);
    *((INT8U *)pDst+4)=Event_Cumu.Event_Time.Year;//Hex2Bcd_Byte(Cur_Time0.Time[T_YEAR);
    return 5;
  }
  else if(0xC010==DI || 0xC011==DI)//���ں�ʱ����Ϊ�ڵ͹��ĵ�����£���Ҫ���⴦��
  {
    //����״̬�£�ͨ���ڲ�ʱ��ˢ�µ�ǰʱ��
    //if(Get_Sys_Status()==SYS_RESUME)
    Get_Time_From_INTER_RTC((S_BCD_Time *)&Cur_Time1);
    
    if(0xC010==DI)
    {
      mem_cpy(pDst,(void *)&Cur_Time1.Week,4,pDst_Start,DstLen);
      return 4;
    }
    else
    {
      mem_cpy(pDst,(void *)&Cur_Time1.Sec,3,pDst_Start,DstLen);
      return 3;
    }
  }
  else if(Spec_Flag==SPEC_CUMU_EVENT)//�ۼ��¼���¼
  {
    return Get_Cumu_Event_Data(DI,pDst,pDst_Start,DstLen,pErr);
  }
  else if(0xB7A0==DI)//����״̬��
  {
    Hex2Bcd(PSW_Err_Info.Lock_Mins,(INT8U *)pDst,3,pDst_Start,DstLen);
    *((INT8U *)pDst+3)=Hex2Bcd_Byte(PSW_Err_Info.Err_Times);
    return 4;
  }
  else if(0xC046==DI)//������״̬��
  {
    Len=0;
    if(CH_IRAD==Cur_Comm_Ch.Ch)//���Ⲩ���ʹ̶�Ϊ0x01
    {
      *pDst=0x01;
      Len=1;
    }
    else if(CH_RS485_1==Cur_Comm_Ch.Ch)
      Len=Read_Storage_Data(DI_COMM_BAUD0,pDst,pDst_Start,DstLen,pErr);
    else if(CH_RS485_2==Cur_Comm_Ch.Ch)
      Len=Read_Storage_Data(DI_COMM_BAUD1,pDst,pDst_Start,DstLen,pErr);
    
    return Len;
  }
  else if(0xB214==DI)
  {
    Len=Read_Storage_Data(0xB214,&Temp,&Temp,sizeof(Temp),pErr);
    Hex2Bcd(Temp,pDst,3,pDst_Start,DstLen);
    return Len;  
  }
  *pErr=NO_ERR;//�������������ͬʱҲû�д���
  return 0;  
}


//���ýڼ��յ����⴦��
INT8U Set_Spec_Holiday_Data(PROTO_DI DI,INT8U *pSrc,INT8U SrcLen,INT8U *pErr)
{
  //PROTO_DI DI;
  INT8U Re;
  
  Re=0;
  if(ASSERT(A_WARNING,SrcLen==3))
  {
    *pErr=PROTOCOL_DATA_ERR;        
    return 0;
  }

  if(DI>=0xC411 && DI<=0xC41D)
  {
    OS_Sem_Pend(PUB_BUF0_SEM_ID);//�ȶ���C41F,�޸ĺ�������д��
    if(Read_Storage_Data(0xC41F,(void *)Pub_Buf0,(void *)Pub_Buf0,sizeof(Pub_Buf0),pErr)==45)
    {
      mem_cpy((INT8U *)Pub_Buf0+(DI-0xC411)*3,pSrc,3,(void *)Pub_Buf0,sizeof(Pub_Buf0));
      *pErr=Write_Storage_Data(0xC41F,(void *)Pub_Buf0,45);
      if(NO_ERR==*pErr)
        Re=1;
      else
        Re=0;
    }
    else
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Read_Storage_Data 0x%x error,Err=%d",DI,*pErr);
      if(NO_ERR==*pErr)
        *pErr=PROTOCOL_DI_ERR;        
      Re=0;
    }
    OS_Sem_Post(PUB_BUF0_SEM_ID);
    return Re;
  }
  else if(DI>=0xCC11 && DI<=0xCC1D)
  {
    OS_Sem_Pend(PUB_BUF0_SEM_ID);//�ȶ���CC1F,�޸ĺ�������д��
    if(Read_Storage_Data(0xCC1F,(void *)Pub_Buf0,(void *)Pub_Buf0,sizeof(Pub_Buf0),pErr)==45)
    {
      mem_cpy((INT8U *)Pub_Buf0+(DI-0xCC11)*3,pSrc,3,(void *)Pub_Buf0,sizeof(Pub_Buf0));
      *pErr=Write_Storage_Data(0xCC1F,(void *)Pub_Buf0,45);
      if(NO_ERR==*pErr)
        Re=1;
      else
        Re=0;
    }
    else
    {
      DEBUG_PRINT(HUCK,DEBUG_0,"Read_Storage_Data 0x%x error,Err=%d",DI,*pErr);
      if(NO_ERR==*pErr)
        *pErr=PROTOCOL_DI_ERR;        
      Re=0;
    }
    OS_Sem_Post(PUB_BUF0_SEM_ID);
    return Re;
  }
  
  //���ݱ�ʶ���������������ʶ
  *pErr=NO_ERR;        
  Re=0;      

  return Re;
}

//�ж��Ƿ�Ӧ�����⴦���������
INT8U Set_Spec_Data_Proc(PROTO_DI DI,INT8U *pSrc,INT8U SrcLen)
{
  S_BCD_Time TempTime;
  INT8U Err;
  INT32U Temp;
  
  //DI=*(INT16U *)pSrc;  //�ڼ������⴦��,���׷��ʷ�����ǰ1-13���ڼ�����Ҫ���⴦��
  if((DI>=0xC411 && DI<=0xC41D) || (DI>=0xCC11 && DI<=0xCC1D))
  {
    if(Set_Spec_Holiday_Data(DI,pSrc,SrcLen,&Err)==1)
      return NO_ERR;
    else
    {
       return PROTOCOL_DI_ERR;      
    }
  } 
  else if(DI==0xCEEE)//У����0
  {
    //if(*pSrc==0)
     Set_Def_Adj_Para(); 
     return NO_ERR;
  }
  else if(DI==0xC010)//����
  {
    mem_cpy(&TempTime,(void *)&Cur_Time1,sizeof(Cur_Time1),&TempTime,sizeof(TempTime));
    TempTime.Week=*pSrc;
    TempTime.Date=*(pSrc+1);
    TempTime.Month=*(pSrc+2);
    TempTime.Year=*(pSrc+3);
    SET_STRUCT_SUM(TempTime);
    if(Set_Time_To_EXT_RTC(&TempTime))
    {
      Set_Time_To_INTER_RTC(&TempTime);
      return NO_ERR;
    }
    return ADJ_TIME_ERR;
  }
  else if(DI==0xC011)//ʱ��
  {
    mem_cpy(&TempTime,(void *)&Cur_Time1,sizeof(Cur_Time1),&TempTime,sizeof(TempTime));
    TempTime.Sec=*pSrc;
    TempTime.Min=*(pSrc+1);
    TempTime.Hour=*(pSrc+2);
    SET_STRUCT_SUM(TempTime);
    if(Set_Time_To_EXT_RTC(&TempTime))
    {
      Set_Time_To_INTER_RTC(&TempTime);
      return NO_ERR;
    }
    return ADJ_TIME_ERR;        
  }
  else if(DI==0xB214)
  {
    Temp=Bcd2Hex(pSrc,3);
    return Write_Storage_Data(0xB214,&Temp,sizeof(Temp));
  }

  //*pErr=NO_ERR;//*pErr==NO_ERR�ҷ��ؽ����0��ʾ��������������
  return PROTOCOL_DI_ERR;
}

#undef DATA_SPEC_C


