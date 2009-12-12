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
    
    signed char Min_Power_Err;  //单位1/10000
    signed char Max_Power_Err;  //单位1/10000
    
    signed char Min_Angle_Err;
    signed char Max_Angle_Err;
    
    signed char Min_Volt_Err;
    signed char Max_Volt_Err;
    
    signed char Min_Curr_Err;
    signed char Max_Curr_Err;
    
    INT8U Cal_Status; //0：待校表；1：校表中；2：校表完成：
    INT8U Cal_Item;  //1------校功率A；2------校功率B；3------校功率C；
                     //4------校相角A；5------校相角B；6------校相角C；
                     //7------校相角A；8------校相角B；9------校相角C；
                     //10------校相角A；11------校相角B；12------校相角C；
                    //注：校表状态最好用宏，因为后期电压电流点环境可能不一样。
    INT8U I_Spec;
    INT8U V_Spec;
    
    INT8U P_Spec;
    
    
    INT32U Ac_Pul_Con; 
    INT32U ReAc_Pul_Con; 
    
    INT32U Power_Value[3];  //单位:0.0001kW;
    INT32U Angle_Value[3];  //单位:0.01度;
    INT32U Volt_Value[3];   //单位:0.0001V;	
    INT32U Curr_Value[3];   //单位:0.0001A;
    
    INT8U  Clr_Para;        //0xD3:表示清除参数.其他状态无效.清参数后可一致保持 0XD3状态,表自动识别是否再清除.
    INT8U Tail;
  }CAL_DATA_PACK;	  //主台下发的校表数据大包


#if CAL_METER_TYPE >= SELF_CAL_TYPE 

  CAL_METER_EXT  CAL_DATA_PACK Cal_Proc_Status; 
    
    
  typedef struct
  {
    INT8U Cal_First:1;     //0----第一次校表;1------
    INT8U Cal_OK:1;        //当前校表项目是否校正
    INT8U Cal_Times:6;     //当前项目校表次数
  }CAL_SPEC_INFO;
  
  typedef struct
  {
    INT8U Cal_Status;
    CAL_SPEC_INFO Cal_Info[CAL_ITEM_NUM];     //校表具体信息
    INT32U Para_Reg[CAL_ITEM_NUM];
    INT8U Clr_Para;  
    INT8U CS[CS_BYTES];
  }CAL_STATUS_STRU;	  //主台下发的校表数据大包
  CAL_METER_EXT  CAL_STATUS_STRU  Real_Cal_Status;
  
  INT8U Set_Cal_Com_Data(INT8U *Src,INT8U SrcLen);
  void Self_Cal_Proc(void);
  INT8U Get_self_Cal_Status(void);
  #define CHECK_CAL_STATUS ((Get_self_Cal_Status()%3 ==0)?0:1)   //是否处于校表状态
#else
  #define Set_Cal_Com_Data(Src,SrcLen)   0
  #define Self_Cal_Proc()                ;
  #define Get_self_Cal_Status()          0
  #define CHECK_CAL_STATUS               0  //是否处于校表状态
#endif


  
#endif
