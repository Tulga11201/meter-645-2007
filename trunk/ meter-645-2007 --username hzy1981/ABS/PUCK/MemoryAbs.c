#define MEM_ABS_PUCK
#include "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "P3"
#endif

/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
**********************************************************************************/ 
INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen)
{
  INT8U Flag;
  
  if((INT8U *)pDst<(INT8U *)pDst_Start || (INT8U *)pDst_Start+RD_Len > (INT8U *)pDst_Start+DstLen)
  ASSERT_FAILED();
  
  Flag=0;
  switch(MemNo)
  {
  case PHY_MEM0:
    Flag=Read_EEPROM_Dvice_PUCK(ID_MEM_IIC_U14,Offset,RD_Len,pDst);
    break;  
  case PHY_MEM1:
    Flag=Read_EEPROM_Dvice_PUCK(ID_MEM_IIC_U10,Offset,RD_Len,pDst);
    break; 
    
  case PHY_MEM2:
   Flag=Read_EEPROM_Dvice_PUCK(ID_MEM_IIC_U11,Offset,RD_Len,pDst);
   break;   
    
  case PHY_MEM3:
    Flag=Read_EEPROM_Dvice_PUCK(ID_MEM_IIC_U12,Offset,RD_Len,pDst);
   break;
    
  case PHY_MEM4:
#ifdef FM_ROM_FM16_EN
   Flag=Read_EEPROM_Dvice_PUCK(ID_MEM_FM24C16,Offset,RD_Len,pDst); 
#else
   Flag=Read_EEPROM_Dvice_PUCK(ID_MEM_IIC_U15,Offset,RD_Len,pDst);
#endif  
   break;  
  
  case PHY_MEM5:
  if(JUDGE_POWER_OFF)  //掉电了
    return 0;
     
   Flag=flash_read_abs(Offset,pDst,RD_Len); 
   break;  
   
  default:

    break;  
  }
  
  if(!Flag)
  {
    Debug_Print("Memory Read Error:ID=%d,Offset=0x%lx,RD_Len=%d",MemNo,Offset,RD_Len);
    //ReNew_Err_Code(DIS_MEM_ERR);
  }
  
  return Flag; 
}

/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
**********************************************************************************/ 
INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen)
{
  INT8U Flag;
  
  Flag=0;
  switch(MemNo)
  {
  case PHY_MEM0:
    Flag=Write_EEPROM_Dvice_PUCK(ID_MEM_IIC_U14,Offset,SrcLen,pSrc);
    break;  
  case PHY_MEM1:
    Flag=Write_EEPROM_Dvice_PUCK(ID_MEM_IIC_U10,Offset,SrcLen,pSrc);
    break; 
    
  case PHY_MEM2:
   Flag=Write_EEPROM_Dvice_PUCK(ID_MEM_IIC_U11,Offset,SrcLen,pSrc);
   break;   
    
  case PHY_MEM3:
    Flag=Write_EEPROM_Dvice_PUCK(ID_MEM_IIC_U12,Offset,SrcLen,pSrc);
   break;
    
  case PHY_MEM4:   
#ifdef FM_ROM_FM16_EN
   Flag=Write_EEPROM_Dvice_PUCK(ID_MEM_FM24C16,Offset,SrcLen,pSrc);
#else
   Flag=Write_EEPROM_Dvice_PUCK(ID_MEM_IIC_U15,Offset,SrcLen,pSrc);
#endif 
   
   
   break;  
  
  case PHY_MEM5: 
   if(JUDGE_POWER_OFF)  //掉电了
    return 0;
   Flag=flash_writ_abs(Offset,pSrc,SrcLen);
   break;
   
  default:         //默认
   break;      
  }
  
  if(!Flag)
  {
    Debug_Print("Memory Write Error:ID=%d",MemNo);
    //ReNew_Err_Code(DIS_MEM_ERR);
  }
  return Flag; 
}