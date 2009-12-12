#ifndef PROTO_DI_H
#define PROTO_DI_H
/*
//EXT volatile S_Prog_Flag Prog_Flag;//编程标识字
////定义扩充的DI,扩充的数据标识都以0x01开始,如果该数据存储在ROM中，则Data_Para_Storage中也定义该数据项//
//以下数据全部从当前ram里面取，以免和读取存储数据冲突
#define DI_REG_CKC                 _PDI_REG_CKC                
#define DI_REG_CSC                 _PDI_REG_CSC                
                          
#define DI_LOW_VOL                 _PDI_LOW_VOL                
#define DI_CURRENT_QUADRANT        _PDI_CURRENT_QUADRANT       
#define DI_METER_PERIPHERY         _PDI_METER_PERIPHERY        
#define DI_MODULE_STATUS           _PDI_MODULE_STATUS          
#define DI_POWER_DOWN_TIME         _PDI_POWER_DOWN_TIME        
                         
#define DI_METER_ADDR0             _PDI_METER_ADDR0            
#define DI_METER_ADDR1             _PDI_METER_ADDR1            
#define DI_METER_ADDR2             _PDI_METER_ADDR2            
                        
#define DI_COMM_BAUD0              _PDI_COMM_BAUD0             
#define DI_COMM_BAUD1              _PDI_COMM_BAUD1             
#define DI_COMM_BAUD2              _PDI_COMM_BAUD2             
                          
#define DI_METER_SOFTWARE_VERSION  _PDI_METER_SOFTWARE_VERSION 
#define DI_METER_SPECIFI           _PDI_METER_SPECIFI          
                          
								   ///一下数据是为负荷曲线增加,不要再確P菔俏汉汕咴黾?不要再
#define DI_ACTIVE_DIRECT           _PDI_ACTIVE_DIRECT          
#define DI_REACTIVE_DIRECT         _PDI_REACTIVE_DIRECT        
                         
								   //#define _DI_ACTIVE_DIRECT        _Pe _DI_ACTIVE_DIRECT       
								   //#define _DI_REACTIVE_DIRECT      _Pe _DI_REACTIVE_DIRECT     
                        
//#define DI_REACTIVE_ALL            _PDI_REACTIVE_ALL           
//#define DI_REACTIVE_A              _PDI_REACTIVE_A             
//#define DI_REACTIVE_B              _PDI_REACTIVE_B             
//#define DI_REACTIVE_C              _PDI_REACTIVE_C             
                          
#define DI_CUR_TIME                _PDI_CUR_TIME               
                        
#define DI_ACTIVE_DEMAND           _PDI_ACTIVE_DEMAND          
#define DI_REACTIVE_DEMAND         _PDI_REACTIVE_DEMAND        
                         
#define _DI_TOTAL_AH               _P_DI_TOTAL_AH              
#define _DI_A_AH                   _P_DI_A_AH                  
#define _DI_B_AH                   _P_DI_B_AH                  
#define _DI_C_AH                   _P_DI_C_AH                  
                          
#define DI_TOTAL_AH                _PDI_TOTAL_AH               
#define DI_A_AH                    _PDI_A_AH                   
#define DI_B_AH                    _PDI_B_AH                   
#define DI_C_AH                    _PDI_C_AH                   
                          
#define DI_A_VOL                   _PDI_A_VOL                  
#define DI_B_VOL                   _PDI_B_VOL                  
#define DI_C_VOL                   _PDI_C_VOL                  
                        
#define DI_A_CUR                   _PDI_A_CUR                  
#define DI_B_CUR                   _PDI_B_CUR                  
#define DI_C_CUR                   _PDI_C_CUR                  
                       
#define DI_A_ANGLE                 _PDI_A_ANGLE                
#define DI_B_ANGLE                 _PDI_B_ANGLE                
#define DI_C_ANGLE                 _PDI_C_ANGLE                
#define DI_SUM_ANGLE               _PDI_SUM_ANGLE              
                       
#define DI_PROG_FLAG0              _PDI_PROG_FLAG0             
#define DI_PROG_FLAG1              _PDI_PROG_FLAG1             
                         
#define DI_ERR_TIME                _PDI_ERR_TIME               
#define DI_ERR_ROM                 _PDI_ERR_ROM                
                         
#define DI_CUR_DEMAND              _PDI_CUR_DEMAND             
#define DI_CLR_DEMAND_WAY          _PDI_CLR_DEMAND_WAY         
#define DI_ADJ_FLAG                _PDI_ADJ_FLAG               
#define DI_NULL_1BYTE              _PDI_NULL_1BYTE             
                         
#define DI_EVENT_VOL               _PDI_EVENT_VOL              
                          
#define DI_ALL_LOSS_VOL_START_TIME _PDI_ALL_LOSS_VOL_START_TIME
#define DI_ALL_LOSS_VOL_END_TIME   _PDI_ALL_LOSS_VOL_END_TIME  
                          
#define DI_EVENT_TIME              _PDI_EVENT_TIME             
                          
//#define DI_A_VOL_1                 _PDI_A_VOL_1                
//#define DI_B_VOL_1                 _PDI_B_VOL_1                
//#define DI_C_VOL_1                 _PDI_C_VOL_1                
                         
//#define DI_A_CUR_3                 _PDI_A_CUR_3                
//#define DI_B_CUR_3                 _PDI_B_CUR_3                
//#define DI_C_CUR_3                 _PDI_C_CUR_3                
                          
#define DI_PROG_TIME               _PDI_PROG_TIME              
                                
#define DI_BROAD_ADJ_TIME          _PDI_BROAD_ADJ_TIME         
                         
#define DI_EXTNED_START            _PDI_EXTNED_START        
*/								   
#endif
								   
