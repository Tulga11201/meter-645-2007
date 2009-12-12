#ifndef CAL_METER_VAR
#define CAL_METER_VAR


#ifndef CAL_METER_C
#define CAL_METER_EXT  extern volatile
#else
#define CAL_METER_EXT volatile
#endif




#define CAL_NONE      0

#define CAL_A_POWER   1
#define CAL_A_ANGLE   2

#define CAL_B_POWER   3
#define CAL_B_ANGLE   4

#define CAL_C_POWER   5
#define CAL_C_ANGLE   6


#define CAL_A_VOLT    7
#define CAL_B_VOLT    8
#define CAL_C_VOLT    9


#define CAL_A_CURR   10
#define CAL_B_CURR   11
#define CAL_C_CURR   12

#define CAL_ITEM_NUM (CAL_C_CURR+1)
      
  typedef struct
  {
    INT8U Head;  
    
    signed char Min_Power_Err;  //��λ1/10000
    signed char Max_Power_Err;  //��λ1/10000
    
    signed char Min_Angle_Err;
    signed char Max_Angle_Err;
    
    signed char Min_Volt_Err;
    signed char Max_Volt_Err;
    
    signed char Min_Curr_Err;
    signed char Max_Curr_Err;
    
    INT8U Cal_Status; //0����У��1��У���У�2��У����ɣ�
    INT8U Cal_Item;  //1------У����A��2------У����B��3------У����C��
                     //4------У���A��5------У���B��6------У���C��
                     //7------У���A��8------У���B��9------У���C��
                     //10------У���A��11------У���B��12------У���C��
                    //ע��У��״̬����ú꣬��Ϊ���ڵ�ѹ�����㻷�����ܲ�һ����
    INT8U I_Spec;
    INT8U V_Spec;
    
    INT8U P_Spec;
    
    
    INT32U Ac_Pul_Con; 
    INT32U ReAc_Pul_Con; 
    
    INT32U Power_Value[3];  //��λ:0.0001kW;
    INT32U Angle_Value[3];  //��λ:0.01��;
    INT32U Volt_Value[3];   //��λ:0.0001V;	
    INT32U Curr_Value[3];   //��λ:0.0001A;
    
    INT8U  Clr_Para;        //0xD3:��ʾ�������.����״̬��Ч.��������һ�±��� 0XD3״̬,���Զ�ʶ���Ƿ������.
    INT8U Tail;
  }CAL_DATA_PACK;	  //��̨�·���У�����ݴ��


#if CAL_METER_TYPE >= SELF_CAL_TYPE 

  CAL_METER_EXT  CAL_DATA_PACK Cal_Proc_Status; 
    
    
  typedef struct
  {
    INT8U Cal_First:1;     //0----��һ��У��;1------
    INT8U Cal_OK:1;        //��ǰУ����Ŀ�Ƿ�У��
    INT8U Cal_Times:6;     //��ǰ��ĿУ�����
  }CAL_SPEC_INFO;
  
  typedef struct
  {
    INT8U Cal_Status;
    CAL_SPEC_INFO Cal_Info[CAL_ITEM_NUM];     //У�������Ϣ
    INT32U Para_Reg[CAL_ITEM_NUM];
    INT8U Clr_Para;  
    INT8U CS[CS_BYTES];
  }CAL_STATUS_STRU;	  //��̨�·���У�����ݴ��
  CAL_METER_EXT  CAL_STATUS_STRU  Real_Cal_Status;
  
  INT8U Set_Cal_Com_Data(INT8U *Src,INT8U SrcLen);
  void Self_Cal_Proc(void);
  INT8U Get_self_Cal_Status(void);
  #define CHECK_CAL_STATUS ((Get_self_Cal_Status()%3 ==0)?0:1)   //�Ƿ���У��״̬
#else
  #define Set_Cal_Com_Data(Src,SrcLen)   0
  #define Self_Cal_Proc()                ;
  #define Get_self_Cal_Status()          0
  #define CHECK_CAL_STATUS               0  //�Ƿ���У��״̬
#endif


  
#endif
