#define DEMAND_C
#include "Includes.h"

//#define Ex_Max_Demand PD_Save_Data.Exceed_Max_Demand

/*
�����͵�ѹͳ�Ƶ������ݶ�����������
1 ������ɺ󣬽���ǰ���ݴ洢��������ȫ��дΪ0����ʾ��ǰ������������Ϊ�գ���δд�뵱�£��µ�һ�£�������
2 ����ʱ��㣬���Զ�������������ܵ�������(ʵ����Ӧ�ò����ܳ�����)
3 ����ڶ�������ϸ�λ�ˣ���ô�����󣬶�ȡ��ǰ������ȫΪ0�����Ჹ����������������˲������̣����ڿ��Զ���ǰ����ʷ���ݣ����Ի��ǲ��Ჹ��
4 ����ڶ���ǰһ�̸�λ�ˣ���������Ȼ�ᰴ����ʷ���ݽ��ж��ᡣ
5 ����ڶ���Ĺ����и�λ��, ���ݲ����γ�У���, ��ǰ����Ҳû������Ϊ0�������ϵ���ǻᲹ��
*/

//��ʼ��������ز���
void Read_Demand_Para_From_Rom()
{
  INT16U Len;

  TRACE();
  //��ȡ��������
  Len = Read_Storage_Data(SDI_DEMAND_PERIOD, (INT8U *) &Demand_Para.Period, (INT8U *) &Demand_Para.Period, 1);
  ASSERT(1 EQ Len);
  Demand_Para.Period = Bcd2Hex_Byte(Demand_Para.Period);
  //��ȡ��������ʱ��
  Len = Read_Storage_Data(SDI_DEMAND_SLID, (INT8U *) &Demand_Para.Slide_Time, (INT8U *) &Demand_Para.Slide_Time, 1);
  ASSERT(1 EQ Len);
  Demand_Para.Slide_Time = Bcd2Hex_Byte(Demand_Para.Slide_Time);

  SET_STRUCT_SUM(Demand_Para);
}

//������������Ƿ�Ϸ�
void Check_Demand_Para_Avail()
{
  INT8U Re;

  TRACE();

  Re = CHECK_STRUCT_SUM(Demand_Para);//��������
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Read_Demand_Para_From_Rom();
  }
}

/*
//��ȡINT24U����
INT32U Get_INT24U_Data(S_INT24U *pData)
{
  INT32U Data;
  
  Data = 0;
  mem_cpy(&Data, pData -> Data, sizeof(pData -> Data), &Data, sizeof(Data));
  return Data;
}

//����INT24U����
void Set_INT24U_Data(S_INT24U *pData, INT32U Data)
{
  if((Data & 0xFF000000) != 0) 
  {
    ASSERT_FAILED();
    return;
  }
  
  mem_cpy(pData -> Data, &Data, sizeof(pData -> Data), pData -> Data, sizeof(pData -> Data));
  return;
}
*/

//���ĳһ��������Ԫ����
void Clr_Demand_Unit(INT8U Index)
{
  INT8U i;

  TRACE();

  if(Index >= S_NUM(Demand_Accu.Phase_Accu[0].Pos_Active))
  {
    ASSERT_FAILED();
    return;
  }

  //������ۼ�
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    /*
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Pos_Active[Index] , 0);//�����й�15�������ۼӵ�Ԫ, ��λ0.0001kw
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Neg_Active[Index] , 0);//�����й�15�������ۼӵ�Ԫ, ��λ0.0001kw
    
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Pos_Apparent[Index] , 0);//�����й�15�������ۼӵ�Ԫ, ��λ0.0001kw
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Neg_Apparent[Index] , 0);//�����й�15�������ۼӵ�Ԫ, ��λ0.0001kw
    
    //Demand_Accu.Phase_Accu[i].Comb_Reactive1[Index] = 0;//�����޹�15�������ۼӵ�Ԫ, ��λ0.0001kvar
    //Demand_Accu.Phase_Accu[i].Comb_Reactive2[Index] = 0;//�����޹�15�������ۼӵ�Ԫ, ��λ0.0001kvar
    
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[0][Index] , 0);//�������޹�15�������ۼӵ�Ԫ
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[1][Index] , 0);//�������޹�15�������ۼӵ�Ԫ
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[2][Index] , 0);//�������޹�15�������ۼӵ�Ԫ
    Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[i].Quad_Reactive[3][Index] , 0);//�������޹�15�������ۼӵ�Ԫ
    */
    Demand_Accu.Phase_Accu[i].Pos_Active[Index] = 0;
    Demand_Accu.Phase_Accu[i].Neg_Active[Index] = 0;
    Demand_Accu.Phase_Accu[i].Pos_Apparent[Index] = 0;
    Demand_Accu.Phase_Accu[i].Neg_Apparent[Index] = 0;
    Demand_Accu.Phase_Accu[i].Quad_Reactive[0][Index] = 0; 
    Demand_Accu.Phase_Accu[i].Quad_Reactive[1][Index] = 0; 
    Demand_Accu.Phase_Accu[i].Quad_Reactive[2][Index] = 0; 
    Demand_Accu.Phase_Accu[i].Quad_Reactive[3][Index] = 0;     
    SET_STRUCT_SUM(Demand_Accu.Phase_Accu[i]);
  }

  //�������ʱ��ͳ��
  Demand_Accu.Accu_Stat.Counts[Index] = 0;
  Demand_Accu.Accu_Stat.Mins[Index] = 0;
  SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
}

//��������ۼӵ�Ԫ����ȷ��
void Check_Demand_Accu()
{
  INT8U i;

  TRACE();

  if(CHECK_STRUCT_SUM(Demand_Accu.Accu_Stat) EQ 0)//Counts����Mins�������������, ���ۼӵ�ԪҲӦ�����
  {
    ASSERT_FAILED();
    Clr_Demand_Accu();
  }
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    if(CHECK_STRUCT_SUM(Demand_Accu.Phase_Accu[i]) EQ 0)
    {
      ASSERT_FAILED();
      mem_set((void *) &Demand_Accu.Phase_Accu[i], 0, sizeof(Demand_Accu.Phase_Accu), (void *) &Demand_Accu, sizeof(Demand_Accu));
      SET_STRUCT_SUM(Demand_Accu.Phase_Accu[i]);
    }

    if(CHECK_STRUCT_SUM(Demand_Accu.Phase_Cur[i]) EQ 0)
    {
      ASSERT_FAILED();
      mem_set((void *) &Demand_Accu.Phase_Cur[i], 0, sizeof(Demand_Accu.Phase_Cur), (void *) &Demand_Accu, sizeof(Demand_Accu));
      SET_STRUCT_SUM(Demand_Accu.Phase_Cur[i]);
    }
  }
}

//������������ۼӵ�Ԫ
void Clr_Demand_Accu()
{
  INT8U i;
  
  TRACE();
  
  Debug_Print("Clear Demand Accu!!!");
  for(i = 0; i < MAX_PERIOD_SLIDE_RATIO; i ++)
    Clr_Demand_Unit(i);
  
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    mem_set((void *)&Demand_Accu.Phase_Cur[i], 0, sizeof(Demand_Accu.Phase_Cur[i]), \
            (void *)&Demand_Accu.Phase_Cur[0], sizeof(Demand_Accu.Phase_Cur));
    SET_STRUCT_SUM(Demand_Accu.Phase_Cur[i]);
  }
}

//��鹦���Ƿ��� 
void Check_Power_Reverse()
{
  INT8U Re;
  static S_Int8U Power_Direct = {CHK_BYTE, 0x00, CHK_BYTE};
  
  Re = CHECK_STRUCT_VAR(Power_Direct);
  if(Re EQ 0)
    ASSERT_FAILED();
  
  if(Read_Event_Status(ID_EVENT_SUM_NEG_CURR) EQ 1) //��ǰ������
  {
    if(Power_Direct.Var EQ 0) //֮ǰ �� �����
    {
      Power_Direct.Var = 1;
      Debug_Print("Power Direct changed, Neg!");
      Clr_Demand_Accu();
    }
  }
  else
  {
    if(Power_Direct.Var EQ 1)
    {
      Power_Direct.Var = 0;
      Debug_Print("Power Direct changed, Pos!");
      Clr_Demand_Accu();
    } 
  }
}

//�����ۼӼ���, ÿ�����һ�θú���
//�ú�����ÿ�������ۼӵ�Ԫ�����ۼӣ������ݵ�ǰʱ������Ƿ����һ������
void Demand_Accumu()
{
  INT8U i, j, k, Quad, Re;
  INT32U Active,React, Apparent;

  TRACE();

  Re = CHECK_STRUCT_SUM(Demand_Para);
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Check_Demand_Accu();

  if(Demand_Para.Slide_Time EQ 0)//��֤Demand_Accu.Slide_Time != 0
  {
    ASSERT_FAILED();
    Demand_Para.Slide_Time = 1;
    SET_STRUCT_SUM(Demand_Para);
  }

  //�ж��������ںͻ���ʱ��������������
  if(!((Demand_Para.Period % Demand_Para.Slide_Time EQ 0 && \
  Demand_Para.Period / Demand_Para.Slide_Time >= 1 && \
  Demand_Para.Period / Demand_Para.Slide_Time <= MAX_PERIOD_SLIDE_RATIO)))
  {
    //���������������Ĭ��Ϊ1���ӻ���ʱ���15������������
    ASSERT_FAILED();
    Debug_Print("Demand_Para error");
    Demand_Para.Slide_Time = 1;
    Demand_Para.Period = MAX_PERIOD_SLIDE_RATIO; 
    SET_STRUCT_SUM(Demand_Para);
  }

  Check_Power_Reverse(); //��鹦���Ƿ������򣬻������������ۼӵ�Ԫ
  
  Re = 1;
  Re &= CHECK_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);
  Re &= CHECK_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);
  ASSERT(1 EQ Re);
  if(1 EQ Re)
  {
    //��ÿ����������(�����ۼӵ�Ԫ)�����ۼ�
    for(i = 0; i < MAX_PERIOD_SLIDE_RATIO && i < Demand_Para.Period / Demand_Para.Slide_Time; i++)
    {
      for(j = 0; j < DEMAND_ACCU_PHASE_NUM; j ++)//�ֱ���ܡ�A��B��C�����ۼӼ���
      {
        if(j EQ 0)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.Sum;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.Sum / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.Sum / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.Sum / POWER_DATA_RATIO;
        }
        else if(j EQ 1)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.A;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.A / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.A / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.A / POWER_DATA_RATIO;
        }
        else if(j EQ 2)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.B;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.B / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.B / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.B / POWER_DATA_RATIO;
        }
        else if(j EQ 3)
        {
          Quad = Measu_InstantData_ToPub_PUCK.Quadrant.C;
          React = Measu_InstantData_ToPub_PUCK.ReacPower.C / POWER_DATA_RATIO;
          Active = Measu_InstantData_ToPub_PUCK.AcPower.C / POWER_DATA_RATIO;
          Apparent = Measu_InstantData_ToPub_PUCK.AppPower.C / POWER_DATA_RATIO;
        }

      //�й� 
      if(Measu_Status_Mode_ToPub_PUCK.SUM_APwrDir EQ POWER_DIRECT_N)//�����й�����
      {
        /*
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Active[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Active[i], Data + Active); //�����й�
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Apparent[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Pos_Apparent[i], Data + Apparent); //��������
        */
        Demand_Accu.Phase_Accu[j].Pos_Active[i] += Active;
        Demand_Accu.Phase_Accu[j].Pos_Apparent[i] += Apparent; 
      }
      else//�����й�
      {
        /*
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Active[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Active[i],Data + Active); //�����й�
        Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Apparent[i]);
        Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Neg_Apparent[i], Data + Apparent); //��������
        */
        Demand_Accu.Phase_Accu[j].Neg_Active[i] += Active;
        Demand_Accu.Phase_Accu[j].Neg_Apparent[i] += Apparent;
        
      }

//���뱣֤ QUADRANT1->QUADRANT4�������!!!!        
#if QUADRANT2!=QUADRANT1+1 || QUADRANT3!=QUADRANT2+1 || QUADRANT4!=QUADRANT3+1
#error "QUADRANT macro define error!"
#endif     
      for(k = 0; k < 4; k ++)
      {
        if(Quad EQ (QUADRANT1 + k)) //��ǰ���ڵڼ�����?
        {
          /*
          Data = Get_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i]);
          Set_INT24U_Data((S_INT24U *)&Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i], Data + React); //��������
          */
          Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] += React;
          break;
        }
      }
      
      if(k EQ 4 && NO_QUADRANT != Quad)
        ASSERT_FAILED();      
        //------------------��������޹��������������޹�-------------
      /*
        for(k = 0; k < 4; k ++)
        {
          if(Quad EQ (QUADRANT1 + k)) //��ǰ���ڵڼ�����?
          {
            Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] += React;
            //����޹�1
            if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2))//�ӣ�
              Demand_Accu.Phase_Accu[j].Comb_Reactive1[i] += React;
            else if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2 + 1))//����
              Demand_Accu.Phase_Accu[j].Comb_Reactive1[i] += React;
          
            //����޹�2        
            if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2))//�ӣ�
              Demand_Accu.Phase_Accu[j].Comb_Reactive2[i] += React;
            else if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2 + 1))//����
              Demand_Accu.Phase_Accu[j].Comb_Reactive2[i] += React;  
            
            break;
          }    
        }
        
        if(k EQ 4 && NO_QUADRANT != Quad)
          ASSERT_FAILED();
        */
      
        SET_STRUCT_SUM(Demand_Accu.Phase_Accu[j]);
      }


      Demand_Accu.Accu_Stat.Counts[i] ++;
      SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
    }
  }


}

//��ǰ�������ݵ�����
void Demand_Generate()//��������
{
  INT8U Re;
  INT16U Counts,Mins;
  static S_Int8U Min_Bak =  {CHK_BYTE, 0xFF, CHK_BYTE};
  INT8U i,j,k;
  
  //ÿ���������Ƿ��˳�����ʱ��
  Re = CHECK_STRUCT_VAR(Min_Bak);
  ASSERT(1 EQ Re);
  if(Min_Bak.Var != Cur_Time0.Time[T_MIN])
  {
    Min_Bak.Var = Cur_Time0.Time[T_MIN];  
    Mins = (INT16U) Cur_Time0.Time[T_HOUR] * 60 + (INT16U) Cur_Time0.Time[T_MIN];

    if(Demand_Para.Period != 0 && (Mins % Demand_Para.Period) EQ 0)//�������ڵ�
    {
      Set_Event_Instant(ID_DEMAND_ARRIVE);//��������
      Port_Out_Pub(EXT_ID_DEMAND,85);
      Debug_Print("Demand Period Arrived!!!");
    }

    //ÿ��һ������ʱ���һ������, ������ǻ������ڣ������һ������ʵ�Ԫ����֤���Ἴ��
    Counts = 0;
    i = 0;

    //����ʱ�䣡=0
    if(Demand_Para.Slide_Time EQ 0)
    {
      ASSERT_FAILED();
      Demand_Para.Slide_Time = 1;
    }

    for(j = 0; j < MAX_PERIOD_SLIDE_RATIO && j < (Demand_Para.Period / Demand_Para.Slide_Time); j ++)
    {
      if(Demand_Accu.Accu_Stat.Counts[j] >= 30) //�����߹���30s,����Ϊ������1����
        Demand_Accu.Accu_Stat.Mins[j]++;//���Ӽ���
      
      if(Counts < Demand_Accu.Accu_Stat.Counts[j])//�ҵ���ǰ�������������Ǹ���Ԫ��������
      {
        i = j;
        Counts = Demand_Accu.Accu_Stat.Counts[j];
      }
    }

    if(Demand_Para.Slide_Time != 0 && (Mins % Demand_Para.Slide_Time) EQ 0)//�������ڵ�, ������ʱ�䵽
    {
      if(Counts != 0)
      {
        //����ƽ��ֵ��Ҳ��������
        //if(Counts>=(INT32U)Demand_Para.Period*(60-10))//��ֹ�ڲ����������ƫ��ʼ�ȥ10S
        if(Demand_Accu.Accu_Stat.Mins[i] >= (INT32U) Demand_Para.Period)
        {
          Set_Event_Instant(ID_SLIP_ARRIVE);//��������
          Port_Out_Pub(EXT_ID_SLIPE,85);      
          Debug_Print("Demand Slide Arrived!!!, Unit %d,Mins=%d,Counts=%d",i,Demand_Accu.Accu_Stat.Mins[i],Counts);
      
          for(j = 0; j < DEMAND_ACCU_PHASE_NUM; j ++)
          {
            //�������й�����
            Demand_Accu.Phase_Cur[j].Pos_Active = Demand_Accu.Phase_Accu[j].Pos_Active[i] / Counts;
            Demand_Accu.Phase_Cur[j].Neg_Active = Demand_Accu.Phase_Accu[j].Neg_Active[i] / Counts; 
            //��������������
            Demand_Accu.Phase_Cur[j].Pos_Apparent = Demand_Accu.Phase_Accu[j].Pos_Apparent[i] / Counts;
            Demand_Accu.Phase_Cur[j].Neg_Apparent = Demand_Accu.Phase_Accu[j].Neg_Apparent[i] / Counts;
            //����޹�1��2����
            //Demand_Accu.Phase_Cur[j].Comb_Reactive1 = Demand_Accu.Phase_Accu[j].Comb_Reactive1[i] / Counts;
            //Demand_Accu.Phase_Cur[j].Comb_Reactive2 = Demand_Accu.Phase_Accu[j].Comb_Reactive2[i] / Counts;
            //�������޹�����
            for(k = 0; k < 4; k ++)
              Demand_Accu.Phase_Cur[j].Quad_Reactive[k] = Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] / Counts;

            Demand_Accu.Phase_Cur[j].Comb_Reactive1 = 0;
            Demand_Accu.Phase_Cur[j].Comb_Reactive2 = 0;
            for(k = 0; k < 4; k ++)
            {
              //if(Quad EQ (QUADRANT1 + k)) //��ǰ���ڵڼ�����?
              //{
                //Demand_Accu.Phase_Accu[j].Quad_Reactive[k][i] += React;
                //����޹�1
                if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2))//�ӣ�
                  Demand_Accu.Phase_Cur[j].Comb_Reactive1 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];
                else if(GET_BIT(Energy_Comb_Word.Reactive[0],k*2 + 1))//����
                  Demand_Accu.Phase_Cur[j].Comb_Reactive1 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];
              
                //����޹�2        
                if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2))//�ӣ�
                  Demand_Accu.Phase_Cur[j].Comb_Reactive2 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];
                else if(GET_BIT(Energy_Comb_Word.Reactive[1],k*2 + 1))//����
                  Demand_Accu.Phase_Cur[j].Comb_Reactive2 += Demand_Accu.Phase_Cur[j].Quad_Reactive[k];  
              //}    
            }
        
            SET_STRUCT_SUM(Demand_Accu.Phase_Cur[j]);
          }
  
          Mins = Demand_Accu.Accu_Stat.Mins[i];
  
          //���ù����ۼӵ�Ԫ��0      
          Clr_Demand_Unit(i);
          
          //��ӡ������ص�����Ϣ
          Debug_Print("------Demand Update-----");
          Debug_Print("The  %dth Unit make demand, Mins= %d, Counts= %d", i, Mins, Counts);
          Debug_Print("Demand:Pos_Act= %ld", Demand_Accu.Phase_Cur[0].Pos_Active);
          Debug_Print("Demand:Neg_Act= %ld", Demand_Accu.Phase_Cur[0].Neg_Active);
          Debug_Print("Demand:Pos_App= %ld", Demand_Accu.Phase_Cur[0].Pos_Apparent);
          Debug_Print("Demand:Neg_App= %ld", Demand_Accu.Phase_Cur[0].Neg_Apparent); 
          Debug_Print("Demand:Quad1= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[0]);
          Debug_Print("Demand:Quad2= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[1]);
          Debug_Print("Demand:Quad3= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[2]);
          Debug_Print("Demand:Quad4= %ld", Demand_Accu.Phase_Cur[0].Quad_Reactive[3]);          
          Debug_Print("Demand:Comb_Reactive1= %ld", Demand_Accu.Phase_Cur[0].Comb_Reactive1);
          Debug_Print("Demand:Comb_Reactive2= %ld", Demand_Accu.Phase_Cur[0].Comb_Reactive2);
        }
        else
          Clr_Demand_Unit(i);//��ʱӦ���Ǹ��ϵ�׶�
      }
    }
    
    //for(j = 0; j < MAX_PERIOD_SLIDE_RATIO && j < (Demand_Para.Period / Demand_Para.Slide_Time); j ++)
      //Demand_Accu.Accu_Stat.Mins[j]++;//���Ӽ���
    
    SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
  }  
  
}

//��ǰ���޹����������ɴ����ŵ�����
void Sign_Demand_Generate()
{
  INT8U i;
  
  if(Measu_Sign_InstantData_PUCK.Curr.Sum >0)//��ǰ����Ϊ��
  {
    Sign_Demand.Active = (INT32S)Demand_Accu.Phase_Cur[0].Pos_Active;
    Sign_Demand.Apparent = (INT32S)Demand_Accu.Phase_Cur[0].Pos_Apparent;    
  }
  else
  {
    Sign_Demand.Active = 0 - (INT32S)Demand_Accu.Phase_Cur[0].Neg_Active;
    Sign_Demand.Apparent = 0 - (INT32S)Demand_Accu.Phase_Cur[0].Neg_Apparent;  
  }
  
  //��ǰ����
  i = Measu_InstantData_ToPub_PUCK.Quadrant.Sum;
  if(i EQ QUADRANT1)
    i = 0;
  else if(i EQ QUADRANT2)
    i = 1;
  else if(i EQ QUADRANT3)
    i = 2;
  else
    i = 3;
  
  if(GET_BIT(Energy_Comb_Word.Reactive[0],i*2) ||\
     GET_BIT(Energy_Comb_Word.Reactive[0],i*2 + 1))//��ǰ����������޹�1�������޹�?
    Sign_Demand.Reactive = (INT32S)Demand_Accu.Phase_Cur[0].Comb_Reactive1;
  else if(GET_BIT(Energy_Comb_Word.Reactive[1],i*2) ||\
          GET_BIT(Energy_Comb_Word.Reactive[1],i*2 + 1))//��ǰ����������޹�2�������޹�?
    Sign_Demand.Reactive = 0 - (INT32S)Demand_Accu.Phase_Cur[0].Comb_Reactive2;
  else
    Sign_Demand.Reactive = 0;
}

/*
//����������0����, �ڸ�λʱ���øú���
//����ʱ��Ҫ�������ۼ��м䵥Ԫ���ݶ�Ϊ����
void Demand_Accu_Clear()
{
  INT8U i;

  TRACE();

  mem_set((void *) &Demand_Accu, 0, sizeof(Demand_Accu), (void *) &Demand_Accu, sizeof(Demand_Accu));
  INIT_STRUCT_VAR(Demand_Accu);
  
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM; i ++)
  {
    SET_STRUCT_SUM(Demand_Accu.Phase_Accu[i]);
    SET_STRUCT_SUM(Demand_Accu.Phase_Cur[i]);
  }

  SET_STRUCT_SUM(Demand_Accu.Accu_Stat);
}

//������0����ڲ���pTime��ʾ�����ʱ���, һ���ǵ�ǰʱ��
//��������Ҫ���ݸ�ʱ�������´��������ݶ����ʱ��
void Demand_Clear(S_HEX_Time* pTime)
{
  //Demand_Accu_Clear();//���ۼ�, ���µ������һ��Ҫ���ۼ�?
  TRACE();

  mem_set((void *) &Cur_Demand, 0, sizeof(Cur_Demand), (void *) &Cur_Demand, sizeof(Cur_Demand));//������
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);
  SET_STRUCT_SUM(Cur_Demand);
}
*/

//�����ϵ�ʱ�Ĵ�����Ҫ�ǵ����˯��ʱ������һ����������ʱ�Ĵ���
//�����ϵ�ʱ���øú��������Խ�Sleep_Secsֵ����һ�����ֵ
//����
void PowerOn_Demand_Proc()
{
  /*
  if(Check_Rst_Flag() EQ SOFT_RST)//����������λ��������м��ۼӵ�Ԫ
    Demand_Accu_Init(0);
  else
  {
    //�˴���Ҫ���˯��ʱ��������, ����ΪDemand_Accu_Init����ڲ���
    Demand_Accu_Init(0xFFFFFFFF);//�ϵ�������ۼӵ�Ԫ
  }
  */
  TRACE();

  Clr_Demand_Accu();
}

//�����ۼӵ�Ԫ��ʼ��
//Sleep_Secs��ʾ������һ�������ۼ��Ѿ��߹��˶೤ʱ��
/*
void Demand_Accu_Init(INT32U Sleep_Secs)
{
  INT32U Period;
  INT8U Re, i;
   
  Re=CHECK_STRUCT_SUM(Demand_Para);
  if(ASSERT(Re>0))
  Check_Data_Avail();
  
  Period=(INT32U)(Demand_Para.Period)*60;//������������
  
  if(Sleep_Secs>=Period)//����ʱ�䳬��һ���������ڣ���Ҫ������������0
  {
  Demand_Accu_Clear();
  }
  else
  {   
  Re=CHECK_STRUCT_SUM(Mode_Word);
  //ģʽ��У����Ƿ���ȷ
  if(ASSERT(0 != Re))
  Check_Data_Avail();

  //���������������Ļ����������ۼӵ�Ԫ
  if(Mode_Word.Mode[2].Bit.Bit3 EQ 0)//��������������
  {
  Demand_Accu_Clear();//���м��ۼ�
  }
  else
  {
  Re=Check_Demand_Accu();
  if(ASSERT(0 != Re))
   Demand_Accu_Clear();
  else
  {
  Re=CHECK_STRUCT_SUM(Demand_Para);
  if(ASSERT(1 EQ Re))
    Check_Data_Avail();
    
  for(i=0;i<MAX_PERIOD_SLIDE_RATIO;i++)//�˴��д��ģ���Ҫ�ǿ���������³����Ƿ�����
  {
    Demand_Accu.Accu_Stat.Counts[i] += Sleep_Secs;
    
    //�Ƚ�ÿ���м䵥Ԫ�ļ���������ü���������һ���������ڵ�ʱ�䣬����Ϊ
    //��ͣ���ڼ䣬���м䵥Ԫ�������һ��
    //+2��Ϊ�˷�ֹ���ֵ�����ϵ�������һ����Ԫ�ĳ�����������, �ϵ�ʱ�俿��������ʱ��
    //0-------------------------15
    //    |pd    |po
    //������������׳����жϴ���, �������2����, ȷ���ڵ����ڼ����һ������
    if(Demand_Accu.Accu_Stat.Counts[i]>=((INT32U)Demand_Para.Period+2)*60)//�����ڼ�϶�����һ������
    {
    Demand_Accu.Accu_Stat.Counts[i]=Demand_Accu.Accu_Stat.Counts[i]-(INT32U)Demand_Para.Period*60;
    Demand_Accu.Phase_Accu[0].Pos_Active[i]=0;//���м䵥Ԫ
    Demand_Accu.Phase_Accu[0].Neg_Active[i]=0;
    Demand_Accu.Phase_Accu[0].Comb_Reactive1[i]=0;
    Demand_Accu.Phase_Accu[0].Comb_Reactive2[i]=0;
    //Demand_Accu.Init_Flag[i]=1;//��ʼ����־
    }
  }
  SET_STRUCT_SUM(Demand_Accu);
  }
  }
  }
}
*/

//�������ڵ��ۼ�
void Demand_Counts_Init()
{
  INT8U i;

  TRACE();

  for(i = 0; i < MAX_PERIOD_SLIDE_RATIO; i++)
  {
    Demand_Accu.Accu_Stat.Counts[i] = (INT16U) Demand_Para.Slide_Time * 60 * i;//ÿ�������ۼ��м䵥Ԫ�ĸ����ۼ� 
  }
}

//��鹦���Ƿ�Խ��
void Demand_Check_Exceed_Limit()
{
  INT8U i;
  INT8U Re;
  INT8U Exceed_Flag, Event_ID;
  //INT32U Demand_Limit;

   
  Re = CHECK_STRUCT_SUM(Demand_Exceed_Limit);
  
  DIS_PD_INT;
  
  if(1 != Re)//ASSERT(1  EQ  Re))
  {
    ASSERT_FAILED();

    mem_set((void *) &Demand_Exceed_Limit, 0, sizeof(Demand_Exceed_Limit), (void *) &Demand_Exceed_Limit, sizeof(Demand_Exceed_Limit));
    SET_STRUCT_SUM(Demand_Exceed_Limit);
    SET_STRUCT_SUM(Event_Data);  
  }
  
  Exceed_Flag = 0;
  //Demand_Limit = POS_ACT_DEMAND_LIMIT;
  //�����й���������
  //if(Demand_Accu.Phase_Cur[0].Pos_Active > Demand_Limit)//�й����������޷���
  if(Read_Event_Status(ID_EVENT_POS_ACT_DEMAND_EXCEED))
  {
    if(Demand_Exceed_Limit.Pos_Active_Flag EQ 0)
    {
      Debug_Print("Pos_Active Demand Exceed Occur: %ld", Demand_Accu.Phase_Cur[0].Pos_Active);
      //Set_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);//�¼�������־

      Demand_Exceed_Limit.Pos_Active.Var = 0;//Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_set((INT8U *) Demand_Exceed_Limit.Pos_Active.Time, 0, sizeof(Demand_Exceed_Limit.Pos_Active.Time),\
              (INT8U *) Demand_Exceed_Limit.Pos_Active.Time, sizeof(Demand_Exceed_Limit.Pos_Active.Time)); 
      
      Demand_Exceed_Limit.Pos_Active_Flag = 1;
      Exceed_Flag = 1;      
    }
      
    if(Demand_Accu.Phase_Cur[0].Pos_Active > Demand_Exceed_Limit.Pos_Active.Var)
    {
      Demand_Exceed_Limit.Pos_Active.Var = Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_cpy((INT8U *) Demand_Exceed_Limit.Pos_Active.Time, (INT8U *) Cur_Time2.Time, sizeof(Cur_Time2.Time),\
              (INT8U *) Demand_Exceed_Limit.Pos_Active.Time, sizeof(Demand_Exceed_Limit.Pos_Active.Time));
      
      Exceed_Flag = 1;
    }
  }
  else //�й�����Խ���޻ָ�
  {
    if(Demand_Exceed_Limit.Pos_Active_Flag EQ 1)
    {
      //�����¼�����
      Debug_Print("Pos_Active Demand Exceed End: %ld", Demand_Accu.Phase_Cur[0].Pos_Active);
      
      //Clr_Event_Instant(ID_EVENT_POS_ACT_DEMAND_EXCEED);//�¼�������־
     
      Demand_Exceed_Limit.Pos_Active_Flag = 0;
      Exceed_Flag = 1;
    }
  }

  //Demand_Limit = NEG_ACT_DEMAND_LIMIT;
  //�����й�����������
  if(Read_Event_Status(ID_EVENT_NEG_ACT_DEMAND_EXCEED))//�����й����������޷���
  {
    if(Demand_Exceed_Limit.Neg_Active_Flag EQ 0)
    {
      Debug_Print("Neg_Active Demand Exceed Occur: %ld", Demand_Accu.Phase_Cur[0].Neg_Active);
      //Set_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);//�¼�������־;//�¼�������־

      Demand_Exceed_Limit.Neg_Active.Var = 0;//Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_set((INT8U *) Demand_Exceed_Limit.Neg_Active.Time, 0, sizeof(Demand_Exceed_Limit.Neg_Active.Time),\
              (INT8U *) Demand_Exceed_Limit.Neg_Active.Time, sizeof(Demand_Exceed_Limit.Neg_Active.Time));
      
      Demand_Exceed_Limit.Neg_Active_Flag = 1;      
      Exceed_Flag = 1;      
    }
    
    if(Demand_Accu.Phase_Cur[0].Neg_Active > Demand_Exceed_Limit.Neg_Active.Var)
    {
      Demand_Exceed_Limit.Neg_Active.Var = Demand_Accu.Phase_Cur[0].Neg_Active;
      mem_cpy((INT8U *) Demand_Exceed_Limit.Neg_Active.Time, (INT8U *) Cur_Time2.Time, sizeof(Cur_Time2.Time),\
              (INT8U *) Demand_Exceed_Limit.Neg_Active.Time, sizeof(Demand_Exceed_Limit.Neg_Active.Time));
     
      Exceed_Flag = 1;    
    }
  } 
  else //�����й�����Խ���޻ָ�
  {
    if(Demand_Exceed_Limit.Neg_Active_Flag EQ 1)
    {
      Debug_Print("Neg_Active Demand Exceed End: %ld", Demand_Accu.Phase_Cur[0].Neg_Active);
      
      //Clr_Event_Instant(ID_EVENT_NEG_ACT_DEMAND_EXCEED);//�¼�������־;//�¼�������־

      Demand_Exceed_Limit.Neg_Active_Flag = 0;
      Exceed_Flag = 1;     
    }
  }

  //Demand_Limit = QUAD_REA_DEMAND_LIMIT;
  //�������޹�����Խ��
  for(i = 0; i < 4; i ++)
  {    
    if(i EQ 0)//�¼�������־
      Event_ID = ID_EVENT_Q1_REAC_DEMAND_EXCEED;
    else if(i EQ 1)
      Event_ID = ID_EVENT_Q2_REAC_DEMAND_EXCEED;
    else if(i EQ 2)
      Event_ID = ID_EVENT_Q3_REAC_DEMAND_EXCEED;
    else
      Event_ID = ID_EVENT_Q4_REAC_DEMAND_EXCEED;

    if(Read_Event_Status(Event_ID))//�޹����������޷���
    {
      if(Demand_Exceed_Limit.Quad_Reac_Flag[i] EQ 0)
      {
        Debug_Print("Quad%d_Reactive Demand Exceed End: %ld", i + 1, Demand_Accu.Phase_Cur[0].Quad_Reactive[i]);

        Demand_Exceed_Limit.Quad_Reactive[i].Var = 0;//Demand_Accu.Phase_Cur[0].Pos_Active;
        mem_set((INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, 0, sizeof(Demand_Exceed_Limit.Quad_Reactive[i].Time),\
                (INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, sizeof(Demand_Exceed_Limit.Quad_Reactive[i].Time));
        
        Demand_Exceed_Limit.Quad_Reac_Flag[i] = 1;
        Exceed_Flag = 1;
      }
        
      if(Demand_Accu.Phase_Cur[0].Quad_Reactive[i] > Demand_Exceed_Limit.Quad_Reactive[i].Var)
      {
        Demand_Exceed_Limit.Quad_Reactive[i].Var = Demand_Accu.Phase_Cur[0].Quad_Reactive[i];
        mem_cpy((INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, (INT8U *) Cur_Time2.Time, sizeof(Cur_Time2.Time),\
                (INT8U *) Demand_Exceed_Limit.Quad_Reactive[i].Time, sizeof(Demand_Exceed_Limit.Quad_Reactive[i].Time));

        Exceed_Flag = 1;
      }
    }
    else //�޹�����Խ���޻ָ�
    {
      if(Demand_Exceed_Limit.Quad_Reac_Flag[i] EQ 1)
      {
        Debug_Print("Quad%d_Reactive Demand Exceed End: %ld", i + 1, Demand_Accu.Phase_Cur[0].Quad_Reactive[i]);
/*        
        if(i EQ 0)//�¼�������־
          Clr_Event_Instant(ID_EVENT_Q1_REAC_DEMAND_EXCEED);
        else if(i EQ 1)
          Clr_Event_Instant(ID_EVENT_Q2_REAC_DEMAND_EXCEED);
        else if(i EQ 2)
          Clr_Event_Instant(ID_EVENT_Q3_REAC_DEMAND_EXCEED);
        else if(i EQ 3)
          Clr_Event_Instant(ID_EVENT_Q4_REAC_DEMAND_EXCEED);
*/
            
        Demand_Exceed_Limit.Quad_Reac_Flag[i] = 0;
        
        Exceed_Flag = 1;
      }   
    }
  }

  if(Exceed_Flag EQ 1)
  {
    SET_STRUCT_SUM(Demand_Exceed_Limit);
    SET_STRUCT_SUM(Event_Data);
  }
  
  EN_PD_INT;
}

//��鵱ǰ�����Ƿ����������
void Demand_Check_Max()
{
  INT8U i,j,Re, Max_Flag;
  INT8U TempTime[5];
  
  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Time0);//��鵱ǰ�����ۼӵ�Ԫ
  Re &= CHECK_STRUCT_SUM(Cur_Demand);//��鵱ǰ����
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��ǰ���������Ϣ 
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);//��鸴������ز���

  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }
  
  Re = CHECK_STRUCT_VAR(Demand_Rate_Mins);
  if(Re EQ 0)
    ASSERT_FAILED();

  Check_Demand_Accu();//��鵱ǰ�����ۼӵ�Ԫ
  
  if(Demand_Rate_Mins.Min_Bak != Cur_Time0.Time[T_MIN])
  {
    Demand_Rate_Mins.Min_Bak = Cur_Time0.Time[T_MIN];
    Demand_Rate_Mins.Mins ++; //�ڵ�ǰ�������ߵķ�����
    if(Demand_Rate_Mins.Rate_Bak != Cur_Rate_Info.Rate) //�����˷����л�
    {
      Demand_Rate_Mins.Rate_Bak = Cur_Rate_Info.Rate; 
      Demand_Rate_Mins.Mins = 0;
    }
  }
  
  Max_Flag = 0;//�ñ�־Ϊ1��ʾ������һ���������

  //�����й�������������䷢��ʱ��
  DIS_PD_INT;//������������ʱ�ص����ж�
  for(i = 0; i < 2; i++)
  {
    if(i EQ 1) //���㵱ǰ���ʵ������������Ҫ�ڵ�ǰ���ʻ�����������һ����������
    {
      if(Demand_Rate_Mins.Mins < Demand_Para.Period)
        break;
    }
    
    //�õ���ǰBCDʱ��
    //Hex2Bcd_Buf((void *)Cur_Time0.Time, sizeof(Cur_Time0.Time), TempTime, TempTime, sizeof(TempTime));
    mem_cpy(TempTime, (INT8U *) &Cur_Time2.Time[1], 5, TempTime, sizeof(TempTime));
    //��ǰ�����ȸ��������������
    //�����й����������䷢��ʱ��
    if(Demand_Accu.Phase_Cur[0].Pos_Active > Cur_Demand.Demand[i].Pos_Active.Var)
    {
      Cur_Demand.Demand[i].Pos_Active.Var = Demand_Accu.Phase_Cur[0].Pos_Active;
      mem_cpy((void *) Cur_Demand.Demand[i].Pos_Active.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //�����й�������������䷢��ʱ��  
    if(Demand_Accu.Phase_Cur[0].Neg_Active > Cur_Demand.Demand[i].Neg_Active.Var)
    {
      Cur_Demand.Demand[i].Neg_Active.Var = Demand_Accu.Phase_Cur[0].Neg_Active;
      mem_cpy((void *) Cur_Demand.Demand[i].Neg_Active.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }

    //�����������������䷢��ʱ��
    if(Demand_Accu.Phase_Cur[0].Pos_Apparent > Cur_Demand.Demand[i].Pos_Apparent.Var)
    {
      Cur_Demand.Demand[i].Pos_Apparent.Var = Demand_Accu.Phase_Cur[0].Pos_Apparent;
      mem_cpy((void *) Cur_Demand.Demand[i].Pos_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //��������������������䷢��ʱ��  
    if(Demand_Accu.Phase_Cur[0].Neg_Apparent > Cur_Demand.Demand[i].Neg_Apparent.Var)
    {
      Cur_Demand.Demand[i].Neg_Apparent.Var = Demand_Accu.Phase_Cur[0].Neg_Apparent;
      mem_cpy((void *) Cur_Demand.Demand[i].Neg_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    
    //�������޹�����
    for(j = 0; j < 4; j ++)
    {
      if(Demand_Accu.Phase_Cur[0].Quad_Reactive[j] > Cur_Demand.Demand[i].Quad_Reactive[j].Var)
      {
        Cur_Demand.Demand[i].Quad_Reactive[j].Var = Demand_Accu.Phase_Cur[0].Quad_Reactive[j];
        mem_cpy((void *) Cur_Demand.Demand[i].Quad_Reactive[j].Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
        SET_STRUCT_SUM(Cur_Demand);
        Max_Flag = 1;
      }      
    }
    
    //�����޹�������������䷢��ʱ��  
    if(Demand_Accu.Phase_Cur[0].Comb_Reactive1 > Cur_Demand.Demand[i].Comb_Reactive1.Var)
    {
      Cur_Demand.Demand[i].Comb_Reactive1.Var = Demand_Accu.Phase_Cur[0].Comb_Reactive1;
      mem_cpy((void *) Cur_Demand.Demand[i].Comb_Reactive1.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    } 
    //�����޹�������������䷢��ʱ�� 
    if(Demand_Accu.Phase_Cur[0].Comb_Reactive2 > Cur_Demand.Demand[i].Comb_Reactive2.Var)
    {
      Cur_Demand.Demand[i].Comb_Reactive2.Var = Demand_Accu.Phase_Cur[0].Comb_Reactive2;
      mem_cpy((void *) Cur_Demand.Demand[i].Comb_Reactive2.Time, TempTime, 5, (void *) Cur_Demand.Demand, sizeof(Cur_Demand.Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
  }       
   EN_PD_INT;//�������ж�

  //������һ�������������
  if(Max_Flag EQ 1)
  {
    Debug_Print("Demand max data generated");
    //Save_Cur_Demand_PD_Data(); 
  }
}

//�����������ݵ������
void Phase_Demand_Check_Max()
{
#if  DEMAND_ACCU_PHASE_NUM > 1
  
  INT8U i, j, Re, Max_Flag;
  INT8U TempTime[5];

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Time0);//��鵱ǰ�����ۼӵ�Ԫ
  Re &= CHECK_STRUCT_SUM(Cur_Demand);//��鵱ǰ����
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);//��ǰ���������Ϣ 
  Re &= CHECK_STRUCT_SUM(Multi_Rate_Para);//��鸴������ز���

  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  Check_Demand_Accu();//��鵱ǰ�����ۼӵ�Ԫ

  Max_Flag = 0;//�ñ�־Ϊ1��ʾ������һ���������

  //�����й�������������䷢��ʱ��
  mem_cpy(TempTime, (INT8U *) &Cur_Time2.Time[1], 5, TempTime, sizeof(TempTime));
    
  DIS_PD_INT;//������������ʱ�ص����ж�
  for(i = 0; i < DEMAND_ACCU_PHASE_NUM-1; i++)
  {
    //�õ���ǰBCDʱ��
    //��ǰ�����ȸ��������������
    //�����й����������䷢��ʱ��
    if(Demand_Accu.Phase_Cur[i+1].Pos_Active > Cur_Demand.Phase_Demand[i].Pos_Active.Var)
    {
      Cur_Demand.Phase_Demand[i].Pos_Active.Var = Demand_Accu.Phase_Cur[i+1].Pos_Active;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Pos_Active.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //�����й�������������䷢��ʱ��  
    if(Demand_Accu.Phase_Cur[i+1].Neg_Active > Cur_Demand.Phase_Demand[i].Neg_Active.Var)
    {
      Cur_Demand.Phase_Demand[i].Neg_Active.Var = Demand_Accu.Phase_Cur[i+1].Neg_Active;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Neg_Active.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }

    //�����������������䷢��ʱ��
    if(Demand_Accu.Phase_Cur[i+1].Pos_Apparent > Cur_Demand.Phase_Demand[i].Pos_Apparent.Var)
    {
      Cur_Demand.Phase_Demand[i].Pos_Apparent.Var = Demand_Accu.Phase_Cur[i+1].Pos_Apparent;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Pos_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
    //��������������������䷢��ʱ��  
    if(Demand_Accu.Phase_Cur[i+1].Neg_Apparent > Cur_Demand.Phase_Demand[i].Neg_Apparent.Var)
    {
      Cur_Demand.Phase_Demand[i].Neg_Apparent.Var = Demand_Accu.Phase_Cur[i+1].Neg_Apparent;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Neg_Apparent.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }    
    //�������޹�����
    for(j = 0; j < 4; j ++)
    {
      if(Demand_Accu.Phase_Cur[i+1].Quad_Reactive[j] > Cur_Demand.Phase_Demand[i].Quad_Reactive[j].Var)
      {
        Cur_Demand.Phase_Demand[i].Quad_Reactive[j].Var = Demand_Accu.Phase_Cur[i+1].Quad_Reactive[j];
        mem_cpy((void *) Cur_Demand.Phase_Demand[i].Quad_Reactive[j].Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
        SET_STRUCT_SUM(Cur_Demand);
        Max_Flag = 1;
      }      
    }
    
    //�����޹�������������䷢��ʱ��  
    if(Demand_Accu.Phase_Cur[i+1].Comb_Reactive1 > Cur_Demand.Phase_Demand[i].Comb_Reactive1.Var)
    {
      Cur_Demand.Phase_Demand[i].Comb_Reactive1.Var = Demand_Accu.Phase_Cur[i+1].Comb_Reactive1;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Comb_Reactive1.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    } 
    //�����޹�������������䷢��ʱ�� 
    if(Demand_Accu.Phase_Cur[i+1].Comb_Reactive2 > Cur_Demand.Phase_Demand[i].Comb_Reactive2.Var)
    {
      Cur_Demand.Phase_Demand[i].Comb_Reactive2.Var = Demand_Accu.Phase_Cur[i+1].Comb_Reactive2;
      mem_cpy((void *) Cur_Demand.Phase_Demand[i].Comb_Reactive2.Time, TempTime, 5, (void *) Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
      SET_STRUCT_SUM(Cur_Demand);
      Max_Flag = 1;
    }
  }       
   EN_PD_INT;//�������ж�

  //������һ�������������
  if(Max_Flag EQ 1)
  {
    Debug_Print("Phase_Demand max data generated");
    //Save_Cur_Demand_PD_Data(); 
  }  
#endif  
}

//��������, ����ÿ���ۼ�������Ԫ���Լ��뵱ǰ��������Ƚϣ��������ֵ 
void Demand_Proc()
{
  INT8U Re;
  static S_Int32U Sec_Timer = {CHK_BYTE, 0x00, CHK_BYTE};

  Re = CHECK_STRUCT_VAR(Sec_Timer);
  ASSERT(1 EQ Re);

  if(Sec_Timer_Pub EQ Sec_Timer.Var)//ʱ�仹û���߹�1S���ú���ֻ����1S����һ�����������
    return;

  Sec_Timer.Var = Sec_Timer_Pub;//�����������

  Demand_Accumu();//ÿ��������ۼ��Լ�ÿ���ӵĵ�ǰ��������, �Լ�ÿ���������ڵ�������� 
  Demand_Generate();//��������
  Sign_Demand_Generate();//��ǰ�������ɣ��з������͵�ǰ����
  Demand_Check_Rate_Change();//��鵱ǰ�����Ƿ������޸ģ�����޸�����Ҫ���¶�ȡ��ǰ���ʵ���������
  Demand_Check_Max();//��鵱ǰ�����Ƿ����������
  Phase_Demand_Check_Max();//��������������ֵ
  Demand_Check_Exceed_Limit();//����Ƿ�������Խ��
  Calc_1Min_Aver_AcPower();//����һ����ƽ������
  Clr_Demand_Manul_Chk();//�ֶ��������ļ��
}

//���浱ǰ��������
void Save_Cur_Demand_Data()
{
  INT8U Re;

  Debug_Print("Save Cur Demand Data!");
  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 EQ Re)
  {
    //���������������
    Write_Demand_Phase_Data(_SDI_CUR_DEMAND, (void *) &Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
    //��������������
    Write_Demand_Rate_Data(_SDI_CUR_DEMAND, 0, (void *) &Cur_Demand.Demand[0], sizeof(Cur_Demand.Demand[0]));
    //����ַ�������
    if(Cur_Demand.Rate != 0)
      Write_Demand_Rate_Data(_SDI_CUR_DEMAND, Cur_Demand.Rate, (void *) &Cur_Demand.Demand[1], sizeof(Cur_Demand.Demand[1]));
    else
      ASSERT_FAILED();
  }
  else
  {
    ASSERT_FAILED();
  }
}

//���浱ǰ������������
void Save_Cur_Demand_Bak_Data()
{
  INT8U Re;

  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 EQ Re)
  {
    Write_Demand_Phase_Data(_SDI_CUR_DEMAND_BAK, (void *) &Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
    Write_Demand_Rate_Data(_SDI_CUR_DEMAND_BAK, 0, (void *) &Cur_Demand.Demand[0], sizeof(Cur_Demand.Demand[0]));
    Write_Demand_Rate_Data(_SDI_CUR_DEMAND_BAK, Cur_Demand.Rate, (void *) &Cur_Demand.Demand[1], sizeof(Cur_Demand.Demand[1]));
  }
  else
  {
    ASSERT_FAILED();
  }
}

//���浱ǰ������������
void Save_Cur_Demand_PD_Data()
{
  INT8U Re;

  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 EQ Re)//����������ݵ�У��ͣ�У��ʹ��������´�ROM�ж�ȡ
  {
    //mem_cpy((void *)Cur_Demand.Time, (void *)Cur_Time0.Time, sizeof(Cur_Time0.Time), (void *)Cur_Demand.Time, sizeof(Cur_Demand.Time));
    Re = Write_Storage_Data(_SDI_CUR_DEMAND_PD, (void *) &Cur_Demand, sizeof(S_Demand));
    ASSERT(1 EQ Re);
  }
  else
  {
    ASSERT_FAILED();
  }
}

/*
//����ǰ�����������õ�SDIָ��������洢�ռ�
void Save_Cur_Demand_Data_To(STORA_DI SDI)
{
  INT8U i;

  Write_Demand_Time(SDI, (void *) &Cur_Demand.Demand[0].Time);
  //Write_Demand_Time(_SDI_CUR_DEMAND_BAK, (void *)&Cur_Demand.Demand[0].Time);

  Write_Demand_Phase_Data(SDI, (void *) &Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
  //Write_Demand_Phase_Data(_SDI_CUR_DEMAND_BAK, (void *)&Cur_Demand.Phase_Demand, sizeof(Cur_Demand.Phase_Demand));
  //���������ʵ�����������0
  for(i = 0; i <= MAX_RATES; i ++)
  {
    Cur_Demand.Rate = i;
    SET_STRUCT_SUM(Cur_Demand);

    Write_Demand_Rate_Data(SDI, i, (void *) &Cur_Demand.Demand[0], sizeof(Cur_Demand.Demand[0]));
  }

  //mem_set((void *)&Cur_Demand, 0, sizeof(Cur_Demand), (void *)&Cur_Demand, sizeof(Cur_Demand)); 
  Cur_Demand.Rate = 0;
  SET_STRUCT_SUM(Cur_Demand.Demand[0]);
  SET_STRUCT_SUM(Cur_Demand.Demand[1]);

  //INIT_STRUCT_VAR(Cur_Demand);
  //SET_DATA_READY_FLAG(Cur_Demand);

  SET_STRUCT_SUM(Cur_Demand);  
  //Save_Cur_Demand_PD_Data();  
}
*/

//���õ�ǰĬ������
//��������ʱ������ΪpTime
void Set_Def_Cur_Demand_Data(S_HEX_Time *pTime)
{
  //S_HEX_Time TempTime;
  
  Debug_Print("Set Def Cur Demand Data, Time:");
  Print_HEX_Time(pTime);
  //mem_set(&TempTime, 0, sizeof(TempTime), &TempTime, sizeof(TempTime));
  //SET_STRUCT_SUM(TempTime);
  //mem_cpy(&TempTime, (void *)&Cur_Time0, sizeof(Cur_Time0), &TempTime, sizeof(TempTime));
  
  Reset_Demand_Ram_Data();
  //��ǰ�����洢����ʱ������Ϊ0������ʱ��Ϊ��ǰ�������ݻ�û������
  Reset_Demand_Rom_Data(_SDI_CUR_DEMAND, pTime);
  Reset_Demand_Rom_Data(_SDI_CUR_DEMAND_BAK, pTime);

  Save_Cur_Demand_PD_Data();
}

//�ֶ��嵱ǰ����
void Manul_Clr_Demand_Data()
{
  DISP_CLR_DATA_INFO;
  Set_Def_Cur_Demand_Data((S_HEX_Time *)&Cur_Time0);
}

//����Ĭ�ϵ���������
void Set_Def_Demand_Data()
{
  INT8U i;
  S_HEX_Time TempTime;
  STORA_DI SDI;

  //Clear_Cur_Demand_Ram_Data();

  //���õ�ǰ��������
  //Save_Cur_Demand_Data_To(_SDI_CUR_DEMAND);
  //Save_Cur_Demand_Data_To(_SDI_CUR_DEMAND_BAK);
  Set_Def_Cur_Demand_Data((S_HEX_Time *)&Cur_Time0);

  //mem_set(&TempTime, 0, sizeof(TempTime), &TempTime, sizeof(TempTime));
  //SET_STRUCT_SUM(TempTime);

  Get_N_Last_Settle_Time(MAX_DEMAND_SETTLE_NUM, (S_HEX_Time *) &Cur_Time0, &TempTime, &TempTime, sizeof(TempTime));
  SDI = _SDI_SETTLE_DEMAND_DATA;  
  //������ʷ��������
  for(i = 0; i < MAX_DEMAND_SETTLE_NUM; i ++)
  {
    if(Cmp_Time(&TempTime, (S_HEX_Time *) &Cur_Time0) != TIME_AFT)
    {
      Debug_Print("Set Def Demand His Data, Time:");
      Print_HEX_Time((S_HEX_Time *) &TempTime);  
     
      INC_DEMAND_SETTLE_DI(SDI);
      Reset_Demand_Rom_Data(SDI, &TempTime); 
    }
    Get_Next_Settle_Time(&TempTime, &TempTime, &TempTime, sizeof(TempTime));
  }
  Write_Storage_Data(_SDI_LAST_SETTLE_DEMAND_DI, &SDI, sizeof(SDI));
  Settle_Demand_FF_Data(0);
}

//��ȡ���ڵ�ǰ�����洢���е��ܻ�ַ�����������
//Rate:��Ҫ��ȡ�������ķ���, 0��ʾ��
//pDst:Ŀ�껺����
//pDst_Start��DstLenһ���޶�pDst�ͷ��س��ȵķ�Χ
//����ֵ:��ȡ���ݳ���, ��ȡʧ�ܷ���0���ɹ�����sizeof(S_One_Demand)
INT16U Read_Cur_Demand_Rate_Data(INT8U Rate, void* pDst, void* pDst_Start, INT16U DstLen)
{
  INT16U Off;

  Off = DEMAND_RATE_DATA_OFF(Rate);
  //�ȶ�ȡ��ǰ�洢��
  if(Read_Storage_Data_Fix_Len(_SDI_CUR_DEMAND, Off, sizeof(S_One_Demand), pDst, pDst_Start, DstLen) != sizeof(S_One_Demand))
  {
    Debug_Print("Read _SDI_CUR_DEMAND CurRate data error");
    //�ٶ�ȡ���ݴ洢��
    OS_TimeDly_Ms(500);
    if(Read_Storage_Data_Fix_Len(_SDI_CUR_DEMAND_BAK, Off, sizeof(S_One_Demand), pDst, pDst_Start, DstLen) != sizeof(S_One_Demand))
    {
      //�ò�����Ĭ�ϲ�����, ʵ���ϲ���������������
      Debug_Print("Read _SDI_CUR_DEMAND_BAK Rate  % d data Error", Rate);
      //������еı��������ݶ�û����������Ϊ�ǵ�һ���ϵ磬������0
      return 0;
    }
  }
  return sizeof(S_One_Demand);
}

//������������Ƿ�Ϸ�
INT8U Check_Demand_Data(S_Demand* pDemand)
{
  INT8U i, Re;
  //INT8U Temp[5] = {0, 0, 0, 0, 0};

  Re = 1;
  Re &= ((pDemand -> Head EQ CHK_BYTE && pDemand -> Tail EQ CHK_BYTE) ? 1 : 0);  
  Re &= Check_STRUCT_Sum(pDemand, sizeof(S_Demand), pDemand -> CS, sizeof(pDemand -> CS));
  Re &= (pDemand -> Data_Ready_Flag EQ DATA_READY) ? 1 : 0;  
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    return 0;
  }

  if(pDemand->Rate EQ 0 || pDemand->Rate > MAX_RATES)
  {
    ASSERT_FAILED();
    return 0;
  }

  for(i = 0; i < 2; i ++)
  {
    if(Check_BCD_Data(pDemand->Demand[i].Pos_Apparent.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Neg_Apparent.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Pos_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Neg_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Demand[i].Comb_Reactive1.Time, 5) != 1 ||\
       Check_BCD_Data(pDemand->Demand[i].Comb_Reactive2.Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[0].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[1].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[2].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Demand[i].Quad_Reactive[3].Time, 5) !=1) 
    {
      ASSERT_FAILED();
      return 0;
    }
  }
  //
  for(i = 0; i < 3; i ++)
  {
    if(Check_BCD_Data(pDemand->Phase_Demand[i].Pos_Apparent.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Phase_Demand[i].Neg_Apparent.Time, 5) != 1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Pos_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Phase_Demand[i].Neg_Active.Time, 5) != 1 || \
       Check_BCD_Data(pDemand->Phase_Demand[i].Comb_Reactive1.Time, 5) != 1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Comb_Reactive2.Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[0].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[1].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[2].Time, 5) !=1 ||\
       Check_BCD_Data(pDemand->Phase_Demand[i].Quad_Reactive[3].Time, 5) !=1) 
    {
      ASSERT_FAILED();
      return 0;
    }
  }       
       
  return 1;
}

//��ROM�ж�����ǰ��������
void Read_Demand_Data_From_Rom()
{
  INT8U Re, Rate, i;
  S_Demand* p;

  //�ȶ�ȡ����洢������
  //�ٶ���ͨ����
  //��������������
  Re = CHECK_STRUCT_SUM(Cur_Rate_Info);
  if(1 != Re)//ASSERT(0 != Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  OS_Mutex_Pend(PUB_BUF0_SEM_ID); 
  p = (S_Demand *) Pub_Buf0;
  if(Read_Storage_Data(_SDI_CUR_DEMAND_PD, p, p, sizeof(Pub_Buf0)) != sizeof(Cur_Demand) || \
     Check_Demand_Data((S_Demand *) p) EQ 0)
  {
    Debug_Print("Read _SDI_CUR_DEMAND_PD data error");
    OS_TimeDly_Ms(500);
    //��ȡ�ܺ͵�ǰ��������
    for(i = 0; i < 2; i ++)
    {
      if(i EQ 0)
        Rate = 0;//��������ʱƫ��Ϊ0
      else
        Rate = Cur_Rate_Info.Rate;//����ʱ���ݷ��ʼ���ƫ��

      p -> Rate = Cur_Rate_Info.Rate;
      //�ӵ�ǰ��������ȡ��ǰ���ܷ��ʵ���������
      if(Read_Cur_Demand_Rate_Data(Rate, (void *) &p->Demand[i], (void *) &p->Demand[i], sizeof(S_One_Demand)) != sizeof(S_One_Demand))
      {
        Debug_Print("Read _SDI_CUR_DEMAND Rate  % d data error", Rate);
        mem_set((void *) &p->Demand[i], 0, sizeof(p->Demand[i]), (void *) &p->Demand[i], sizeof(p->Demand[i]));
      }
    }
  }


  if(Check_Demand_Data((S_Demand *) p) EQ 0)
  {
    ASSERT_FAILED();
    mem_set(p, 0, sizeof(Cur_Demand), p, sizeof(Pub_Buf0));
  }       

  DIS_PD_INT;//����Cur_Demand����ǰ�ص����ж�
  mem_cpy((void *) &Cur_Demand, p, sizeof(Cur_Demand), (void *) &Cur_Demand, sizeof(Cur_Demand));
  INIT_STRUCT_VAR(Cur_Demand);
  SET_DATA_READY_FLAG(Cur_Demand);
  SET_STRUCT_SUM(Cur_Demand);              
  EN_PD_INT;

  OS_Mutex_Post(PUB_BUF0_SEM_ID);  
  //SET_STRUCT_SUM(Cur_Demand); 
  //���µ�ǰ�洢���ͱ��ݴ洢����������������Ҫ�õ��������������Ҫ��֤�������������ݸ���
  if(Check_Sys_Status() EQ SYS_NORMAL) //��ѹ��������²Ž���д����
  {
    Save_Cur_Demand_Data();
    Save_Cur_Demand_Bak_Data();
  }
}


//����ĳ���������ݵ�ʱ����
void Set_One_Demand_Time(S_One_Demand* pSrc, S_HEX_Time* pTime)
{
  mem_cpy(&(pSrc->Time), pTime, sizeof(S_HEX_Time), &(pSrc->Time), sizeof(pSrc->Time));
  Set_STRUCT_Sum(pSrc, sizeof(S_One_Demand), pSrc->CS, sizeof(pSrc->CS));
}

//������鵱ǰ�����Ƿ����˱仯������仯�ˣ��������ǰ���ʵ��������ֵ
void Demand_Check_Rate_Change()
{
  INT8U Re;

  Re = 1;
  Re &= CHECK_STRUCT_SUM(Cur_Rate_Info);
  Re &= Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 != Re)//ASSERT(1 EQ Re))
  {
    ASSERT_FAILED();
    Check_Data_Avail();
  }

  if(Cur_Rate_Info.Rate != Cur_Demand.Rate)//�����Ѿ������仯��
  {
    Debug_Print("Rate_Changed! %d->%d,Save Old Rate Demand && Read New Rate Demand",\
                                Cur_Demand.Rate, Cur_Rate_Info.Rate);
    Save_Cur_Demand_Data();//�Ƚ�Cur_Demand���ݱ�������
    Save_Cur_Demand_Bak_Data();

    //���¸��ݵ�ǰ���ʶ�ȡ��������

    
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    //�����÷ַ�������
    if(Read_Cur_Demand_Rate_Data(Cur_Rate_Info.Rate, (void *) Pub_Buf0, (void *) Pub_Buf0, sizeof(Pub_Buf0)) != sizeof(S_One_Demand))
    {
      mem_set((void *) Pub_Buf0, 0, sizeof(S_One_Demand), (void *) Pub_Buf0, sizeof(Pub_Buf0));
    }
    
    DIS_PD_INT;
    mem_cpy((void *) &Cur_Demand.Demand[1], (void *)Pub_Buf0, sizeof(S_One_Demand),(void *) &Cur_Demand.Demand[1], sizeof(Cur_Demand.Demand[1])); 
    SET_STRUCT_SUM(Cur_Demand.Demand[1]);
    Cur_Demand.Rate = Cur_Rate_Info.Rate;
    SET_STRUCT_SUM(Cur_Demand);
    EN_PD_INT;
    
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
    
    Save_Cur_Demand_PD_Data();//���µ���洢������������
    //Clr_Demand_Accu();//�������ۼӵ�Ԫ
  }
}

//��鵱ǰ�������ݵ���Ч��
void Check_Demand_Data_Avail()
{
  INT8U Re;

  Re = Check_Demand_Data((S_Demand *) &Cur_Demand);
  if(1 != Re)//ASSERT(1 EQ Re))//����������ݵ�У��ͣ�У��ʹ��������´�ROM�ж�ȡ
  {
    ASSERT_FAILED();
    Read_Demand_Data_From_Rom();
  }

  Check_Demand_Accu();
}

//������������䷢��ʱ��, ������ֻ�嵱������
void Clear_Cur_Demand_Data()
{
  Set_Clear_Data_Result(0);
  if(Check_Clear_Data_Authority() EQ 0)
    return;

  if(CLEAR_DEMAND_FLAG != Check_Clear_Data_Flag())
    return;

  Debug_Print("Clear_Cur_Demand_Data!!!"); 
  
  DISP_CLR_DATA_INFO;
  Set_Def_Cur_Demand_Data((S_HEX_Time *)&Cur_Time0);
  
  Set_Clear_Data_Result(1);
}

//�����е���������, �������º�ǰHIS_ENERGY_DATA_MONTHS����
void Clear_Demand_Data()
{
  if(Check_Clear_Data_Authority() EQ 0)
  {
    return;
  }

  Debug_Print("Clear_Demand_Data!!!"); 
  if(CLEAR_DEMAND_FLAG != Check_Clear_Data_Flag() && CLEAR_ALL_FLAG != Check_Clear_Data_Flag())
  {
    return;
  }
  DISP_CLR_DATA_INFO;
  
  Set_Def_Demand_Data();
  /*
  INT8U i, j;
  INT8U Re;
  INT32U Off;
  //��ǰ0-HIS_ENERGY_DATA_MONTHS�µ�����ȫ����0
  //�����״̬���û�Ȩ��״̬
  if(Check_Meter_Prog_Status() EQ 0 ||\
     CHECK_STRUCT_SUM(User_Authority_Flag) EQ 0 ||\
     User_Authority_Flag.Flag != AUTHORITY_FLAG)
    return;
  //��������־
  Re=1;
  Re&=CHECK_STRUCT_SUM(User_Authority_Flag);
  Re&=CHECK_STRUCT_SUM(Clear_Flag);
  if(ASSERT(1 EQ Re))
    Check_Data_Avail();
  mem_set((void *)&Cur_Demand, 0, sizeof(Cur_Demand), (void *)&Cur_Demand, sizeof(Cur_Demand));
  //��ǰ0-HIS_ENERGY_DATA_MONTHS�µ�����
  for(i=0;i<=HIS_DEMAND_DATA_MONTHS;i++)
  {
    //Debug_Print("Clear Freeze Demand Data, Time: % d- % d- % d  % d: % d", Time.Time[T_YEAR], Time.Time[T_MONTH], Time.Time[T_DATE], Time.Time[T_HOUR], Time.Time[T_MIN]);
    //�ϸ��жϣ���ֹ�������ܵ�����
    if(Check_Meter_Prog_Status() EQ 0 || 1 != Re ||\
     AUTHORITY_FLAG != User_Authority_Flag.Flag ||\
     CLEAR_DEMAND_FLAG != Clear_Flag.Flag)
    return;
    for(j=0;j<MAX_RATES;j++)
    {
    Off=DEMAND_RATE_DATA_OFF(i);//ֱ��д��ʷ���ݴ洢������
    Write_Storage_Data_Fix_Len(_SDI_SETTLE_DEMAND_DATA+i, Off, (void *)&Cur_Demand.Demand[0], sizeof(S_One_Demand));
    }
  }
  Clear_Demand_Data();//���嵱������
  */
}



//����洢��������
void PowerDown_Save_Demand_Data()
{
  Save_Cur_Demand_PD_Data();
}

//��ӡʱ��
void Debug_Print_Time(INT8U Time[])
{
  INT8U i;

  OS_Debug_Print("  ");
  for(i = 0; i < 5; i++)
  {
    if(Time[4 - i] < 10)
      OS_Debug_Print("0");

    OS_Debug_Print("%x", Time[4 - i]);
    if(i EQ 0 || i EQ 1)
      OS_Debug_Print("-");
    else if(i EQ 2)
      OS_Debug_Print(" ");
    else if(i EQ 3)
      OS_Debug_Print(":");
  }
  //OS_Debug_Print(" "); 
}

void Get_Print_Name(INT8U Dst[], INT8U Dst_Start, INT16U DstLen)
{
}

//������������ģʽ0�����1������
INT8U Get_Demand_Run_Mode()
{
  if(Demand_Para.Period EQ Demand_Para.Slide_Time)
    return 1;
  else
    return 0;
}

//�����ǰ������Ϣ
void Debug_Print_Cur_Demand_Info()
{
  static S_Int8U Min = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Counts ={CHK_BYTE, 0, CHK_BYTE};
  INT8U i, Re, Temp[5];
  S_One_Demand* p;

  if(Check_Debug_En() EQ 0)//�ǹ���״̬����ӡ
    return;

  if(Cur_Time0.Time[T_MIN] EQ Min.Var)//ÿ����ִ��һ�θú���
    return;

  Re = 1;
  Re &= CHECK_STRUCT_VAR(Min);
  //ASSERT(1 EQ Re);
  Re &= CHECK_STRUCT_VAR(Counts);
  ASSERT(1 EQ Re);

  Min.Var = Cur_Time0.Time[T_MIN];
  Counts.Var++;
  if(Counts.Var >= 5)//ÿ��5���Ӵ�ӡһ�ε�ǰ����ֵ
  {
    Counts.Var = 0;

    Clr_Ext_Inter_Dog();
    Debug_Print("|----------------------------------------Max_Demand------------------------------------|"); 
    Debug_Print("| Rate Pos_Act Neg_Act Pos_Rea Neg_Rea Quad0_R Quad1_R Quad2_R Quad3_R Pos_App Neg_App |");

    for(i = 0; i < 5; i ++)
    {
      if(i EQ 0 || i EQ 1)
      {
        if(i EQ 0)
        {
          Temp[0] = ' ';//0x30 + i/10;
          Temp[1] = '0';
        }
        else
        {
          if(Cur_Demand.Rate >= 10)
            Temp[0] = '0' + Cur_Demand.Rate / 10;
          else
            Temp[0] = ' ';

          Temp[1] = '0' + Cur_Demand.Rate % 10;
        }
        p = (S_One_Demand *) &Cur_Demand.Demand[i];
      }
      else
      {
        Temp[0] = ' ';
        Temp[1] = 'A' + i - 2; 
        p = (S_One_Demand *) &Cur_Demand.Phase_Demand[i - 2];
      }

      Temp[2] = 0;
      Debug_Print("|   %s %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld %7ld |",\
            Temp, p->Pos_Active.Var, p->Neg_Active.Var, p->Comb_Reactive1.Var, p->Comb_Reactive2.Var,\
            p->Quad_Reactive[0].Var, p->Quad_Reactive[1].Var, p->Quad_Reactive[2].Var, p->Quad_Reactive[3].Var,\
            p->Pos_Apparent.Var, p->Neg_Apparent.Var);
    }
    Debug_Print("|--------------------------------------------------------------------------------------|");

    OS_TimeDly_Ms(50);
    Clr_Ext_Inter_Dog();
    Debug_Print("|---------------------------------------------Demand_Time_0--------------------------------------------|"); 
    Debug_Print("| Rate      Pos_Active      Neg_Active      Pos_Reacti      Neg_Reacti      Pos_Appare      Neg_Appare |");

    for(i = 0; i < 5; i ++)
    {
      if(i EQ 0 || i EQ 1)
      {
        if(i EQ 0)
        {
          Temp[0] = ' ';//0x30 + i/10;
          Temp[1] = '0';
        }
        else
        {
          if(Cur_Demand.Rate >= 10)
            Temp[0] = '0' + Cur_Demand.Rate / 10;
          else
            Temp[0] = ' ';

          Temp[1] = '0' + Cur_Demand.Rate % 10;
        }
        p = (S_One_Demand *) &Cur_Demand.Demand[i];
      }
      else
      {
        Temp[0] = ' ';
        Temp[1] = 'A' + i - 2; 
        p = (S_One_Demand *) &Cur_Demand.Phase_Demand[i - 2];
      }

      Temp[2] = 0;
      Debug_Print("|   %s", Temp);
      Debug_Print_Time((INT8U *) p->Pos_Active.Time);
      Debug_Print_Time((INT8U *) p->Neg_Active.Time);
      Debug_Print_Time((INT8U *) p->Comb_Reactive2.Time);
      Debug_Print_Time((INT8U *) p->Comb_Reactive2.Time);
      Debug_Print_Time((INT8U *) p->Pos_Apparent.Time);
      Debug_Print_Time((INT8U *) p->Neg_Apparent.Time);
      OS_Debug_Print(" |");
    }
    Debug_Print("|------------------------------------------------------------------------------------------------------|");


    Clr_Ext_Inter_Dog();
    Debug_Print("|------------------------------Demand_Time_1---------------------------|"); 
    Debug_Print("| Rate     Quad0_Reati     Quad1_Reati     Quad2_Reati     Quad3_Reati |");

    for(i = 0; i < 5; i ++)
    {
      if(i EQ 0 || i EQ 1)
      {
        if(i EQ 0)
        {
          Temp[0] = ' ';//0x30 + i/10;
          Temp[1] = '0';
        }
        else
        {
          if(Cur_Demand.Rate >= 10)
            Temp[0] = '0' + Cur_Demand.Rate / 10;
          else
            Temp[0] = ' ';

          Temp[1] = '0' + Cur_Demand.Rate % 10;
        }
        p = (S_One_Demand *) &Cur_Demand.Demand[i];
      }
      else
      {
        Temp[0] = ' ';
        Temp[1] = 'A' + i - 2; 
        p = (S_One_Demand *) &Cur_Demand.Phase_Demand[i - 2];
      }

      Debug_Print("|   %s", Temp);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[0].Time);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[1].Time);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[2].Time);
      Debug_Print_Time((INT8U *) p->Quad_Reactive[3].Time);
      OS_Debug_Print(" |");
    }    
    Debug_Print("|----------------------------------------------------------------------|");
  }
}

//����һ����ƽ���й�����
void Calc_1Min_Aver_AcPower()
{
  //static S_Int32U Sec_Bak = {CHK_BYTE, 0, CHK_BYTE};
  static S_Int8U Min_Bak = {CHK_BYTE, 0, CHK_BYTE};
  INT8U Re;
  
  Re = 1;
  //Re &= CHECK_STRUCT_VAR(Sec_Bak);
  Re &= CHECK_STRUCT_VAR(Min_Bak);
  Re &= CHECK_STRUCT_VAR(AcPower_1Min_Aver);
  
  ASSERT(Re EQ 1);
  
  if(Min_Bak.Var EQ Cur_Time1.Min)
  {
    AcPower_1Min_Aver.Accu_Power += Measu_InstantData_ToPub_PUCK.AcPower.Sum;
    AcPower_1Min_Aver.Counts ++;
  }
  else
  {
    Min_Bak.Var = Cur_Time1.Min;
    
    if(AcPower_1Min_Aver.Counts > 50)
      AcPower_1Min_Aver.Aver_Power = ((AcPower_1Min_Aver.Accu_Power /100) / AcPower_1Min_Aver.Counts); 
    
    AcPower_1Min_Aver.Accu_Power = 0;
    AcPower_1Min_Aver.Counts = 0;
  }
  
}

//��ȡһ����ƽ���й�����
INT32U Get_One_Min_AcPower_Aver()
{
  
 return  AcPower_1Min_Aver.Aver_Power;
}

void Clr_Demand_Manul_Chk()
{
  //static S_Int8U Clr_Flag = {CHK_BYTE, 0, CHK_BYTE};
  
  //�ֶ��������¼�������?
  if(Check_Demand_Key_Press() EQ 1)
  {
    //if(Clr_Flag.Var EQ 0)
    {      
      Debug_Print("Clr_Demand_Manul!");
      Set_Event_Instant(ID_EVENT_CLR_DEMAND_MAN);
      Wait_Event_Data_Proc_End(ID_EVENT_CLR_DEMAND_MAN);
      Manul_Clr_Demand_Data(); //�ֶ��嵱ǰ����  
    }
  }
  //else
    //Clr_Flag.Var = 0;
}

/*
//�������޴���
void Demand_Exceed_Limit_Proc()
{
  INT8U i;

  if(0)//�����й�����������
  {
  if(Demand_Accu.Phase_Cur[0].Pos_Active > Ex_Max_Demand.Pos_Active.Var)
  {
  Ex_Max_Demand.Pos_Active.Var = Demand_Accu.Phase_Cur[0].Pos_Active;
  Get_BCD_Time((S_BCD_Time *)&Cur_Time1,  (INT8U *)Ex_Max_Demand.Pos_Active.Time,  \
  (INT8U *)Ex_Max_Demand.Pos_Active.Time,  sizeof(Ex_Max_Demand.Pos_Active.Time));
  }
  }
  else
  {
  mem_set((void *)&Ex_Max_Demand.Pos_Active,  \
  0, \
  sizeof(Ex_Max_Demand.Pos_Active), \
  (void *)&Ex_Max_Demand.Pos_Active, \
  sizeof(Ex_Max_Demand.Pos_Active));
  }

  if(0)//�����й���������
  {
  if(Demand_Accu.Phase_Cur[0].Neg_Active > Ex_Max_Demand.Neg_Active.Var)
  {
  Ex_Max_Demand.Neg_Active.Var = Demand_Accu.Phase_Cur[0].Neg_Active;
  Get_BCD_Time((S_BCD_Time *)&Cur_Time1,  (INT8U *)Ex_Max_Demand.Neg_Active.Time,  \
  (INT8U *)Ex_Max_Demand.Neg_Active.Time,  sizeof(Ex_Max_Demand.Neg_Active.Time));
  }
  }
  else
  {
  mem_set((void *)&Ex_Max_Demand.Neg_Active,  \
  0, \
  sizeof(Ex_Max_Demand.Neg_Active), \
  (void *)&Ex_Max_Demand.Neg_Active, \
  sizeof(Ex_Max_Demand.Neg_Active));
  }

  //�������޹���������
  for(i = 0; i < 4; i ++)
  {
  
  if(0)//
  {
  if(Demand_Accu.Phase_Cur[0].Quad_Reactive[i] > Ex_Max_Demand.Quad_Reactive[i].Var)
  {
  Ex_Max_Demand.Quad_Reactive[i].Var = Demand_Accu.Phase_Cur[0].Quad_Reactive[i];
  Get_BCD_Time((S_BCD_Time *)&Cur_Time1,  (INT8U *)Ex_Max_Demand.Quad_Reactive[i].Time,  \
    (INT8U *)Ex_Max_Demand.Quad_Reactive[i].Time,  sizeof(Ex_Max_Demand.Quad_Reactive[i].Time));
  }
  }
  else
  {
  mem_set((void *)&Ex_Max_Demand.Quad_Reactive[i],  \
  0, \
  sizeof(Ex_Max_Demand.Quad_Reactive[i]), \
  (void *)&Ex_Max_Demand.Quad_Reactive[i], \
  sizeof(Ex_Max_Demand.Quad_Reactive[i]));
  }
  }
}
*/
/*
INT8U OS_Assert_Hook()
{
   INT8U Re;

  Assert_Info.On_Off_Flag =0;
   if(Check_Demand_Data((S_Demand *)&Cur_Demand) EQ 0)
   Re =0;
   else
   Re =1;
  Assert_Info.On_Off_Flag =0xFF;
  return Re;
}
*/
#undef DEMAND_C
