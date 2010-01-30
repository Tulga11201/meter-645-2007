#include "DrvPub.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "B4"
#endif


#ifdef I2C_SOFT_EPP_EN
//#pragma pack(1)
typedef struct
{ 
  INT8U   EppType:5;
  INT8U   Single:1;               //字节地址为1个字节
  INT8U   BitFill:2;              //高字节地址在器件地址中所占的 bit 位数
  INT16U  PageSize;               //页内字节数
  INT32U  MaxSize;                //IC最大字节数
  INT8U   PageDlyFlg:1;           //写页内延时标志
  INT8U   PageDelay:7;            //跨页内延时时间：ms
}CONST_EPPROM_SOFT;

#define MAX_EPPROM_TYPE  (M24512+1)

CONST CONST_EPPROM_SOFT  Const_Epprom_Soft[MAX_EPPROM_TYPE]={
  {M2401,1,0,8,EPP_2401_SIZE,1,8},
  {M2402,1,0,8,EPP_2402_SIZE,1,8},
  {M2404,1,1,16,EPP_2404_SIZE,1,8},
  {M2408,1,2,16,EPP_2408_SIZE,0,0},
  {M2416,1,3,16,EPP_24016_SIZE,0,1},   //铁电
  {M2432,0,0,32,EPP_24032_SIZE,0,0},
  {M2464,0,0,32,EPP_24064_SIZE,0,1},   //铁电
  {M24128,0,0,64,EPP_240128_SIZE,0,0},
  {M24256,0,0,64,EPP_240256_SIZE,1,8},
  {M24512,0,0,128,EPP_240512_SIZE,1,8}
};
//#pragma pack()


/**********************************************************************************
地址序列：从器件地址＋高字节地址(可选)＋低字节地址
24C01/2:  1 0 1 0 A2  A1 A0 R/W
24C04:    1 0 1 0 A2  A1 a8 R/W        器件地址包含了高地址的a8：      2^8=256， 实际将512字节分为2大页，每大页256字节
24C08:    1 0 1 0 A2  a9 a8 R/W        器件地址包含了高地址的a9a8：    2^10=1024，实际将1024字节为4大页，每大页256字节
24C16:    1 0 1 0 a10 a9 a8 R/W        器件地址包含了高地址的a10a9a8： 2^11=2048，实际将2048字节为8大页，每大页256字节
24C32～24C256：   1 0 1 0 A2 A1 A0 R/W +AddrH+AddrL

**********************************************************************************/

/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
注意：地址操作范围：65536字节(64k)
**********************************************************************************/   
INT8U Write_Soft_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT16U size,INT8U Type,INT8U *Src)
{
    INT16U WrNum;
    INT16U Page;
    INT8U AddrH,AddrL;
    INT8U OkFlag;
    
    OkFlag=1;
    if(size==0)                                        OkFlag=0;
    if(Type>MAX_EPPROM_TYPE)                           OkFlag=0;
    if(size>Const_Epprom_Soft[Type].MaxSize)           OkFlag=0;
    if(SubAddr>Const_Epprom_Soft[Type].MaxSize)        OkFlag=0;  
    if((size+SubAddr)>Const_Epprom_Soft[Type].MaxSize) OkFlag=0;
    
    if(OkFlag EQ 0)
    {
      ASSERT_FAILED();
      Debug_Print("Write Data Exceed Limited,Addr=%d,size=%d,Maxsize=%d",SubAddr,size,Const_Epprom_Soft[Type].MaxSize); 
      return 0;
    }
    
#ifdef SOFT_I2C_ENV
    if(setjmp(Soft_I2c_Env.Env)==0)
    {
#endif     
    I2cSoft_EnWp(VirtualID,0); //IIC_HARD_WP_EN;       //开启写操作
    
    WAITFOR_DRV_CYCLE_TIMEOUT(100);
    WrNum=0;
    AddrH=(INT8U)(SubAddr/256);
    AddrL=(INT8U)(SubAddr%256);
    do{
        OkFlag=I2cSoft_Start(VirtualID);	
        Page=AddrL+WrNum; 
        if(Const_Epprom_Soft[Type].Single) //地址为一个字节的器件------PUCK
        {
          if(Const_Epprom_Soft[Type].BitFill==0) //此器件地址是固定的
             OkFlag&I2cSoft_Send_Byte(VirtualID,SlvAdr);
          else                                 //从器件地址根据高字节修改
            OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr|Get_Modi_Value(((SubAddr+WrNum)/256)));   //从器件地址修改，并下发
        }
        else
        {
          OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr); 
          OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrH+(Page>>8));      
        }       
        
        OkFlag&=I2cSoft_Send_Byte(VirtualID,(Page&0x00FF)) ;	
        do
        {
           OkFlag&=I2cSoft_Send_Byte(VirtualID,*Src); 					
           Src++;WrNum++;
        }while((WrNum<size)&&(((AddrL+WrNum)&(Const_Epprom_Soft[Type].PageSize-1))!=0));
        
        OkFlag&=I2cSoft_Stop(VirtualID);
        if(Const_Epprom_Soft[Type].PageDlyFlg)
          WAITFOR_DRV_MS_TIMEOUT(Const_Epprom_Soft[Type].PageDelay)
        else
          WAITFOR_DRV_CYCLE_TIMEOUT(100)  //没有延时标志，延时100个nop
        }while(WrNum<size);
        
    I2cSoft_EnWp(VirtualID,1);//IIC_HARD_WP_DIS;     //置WP口线为高，禁止写--------PUCK
#ifdef SOFT_I2C_ENV
    return 1;
    }
   else
#else
   if(!OkFlag)
#endif
   {
      I2cSoft_EnWp(VirtualID,1);//IIC_HARD_WP_DIS;     //置WP口线为高，禁止写--------PUCK
      I2cSoft_Reset(VirtualID);
      OkFlag=0;
   }
    return OkFlag;
}


/**********************************************************************************
函数功能：iic总线上读数据:8bits,并给出ACK回应，最后一字节，给出NACK回应
入口：
出口：1-------------成功；0----------失败
**********************************************************************************/ 
INT8U I2cSoft_Read_nByteS(INT8U Id,INT16U Len,INT8U *Dst)
{
  INT8U i,OkFlag;
  OkFlag=1;
  for(i=0;i<Len-1;i++)           //前Len字节，接收，并ACK回应
  {
      OkFlag&=I2cSoft_Read_Byte(Id,Dst+i);
      OkFlag&=I2cSoft_Send_N_Ack(Id,0);
  }   
  OkFlag&=I2cSoft_Read_Byte(Id,Dst+Len-1);  //最后1字节，接收，并NACK回应
  OkFlag&=I2cSoft_Send_N_Ack(Id,1);
  return OkFlag;
}


/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
**********************************************************************************/
INT8U Read_Soft_Func_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
{
    INT8U AddrH,AddrL,OkFlag;
     
    AddrH=(INT8U)(SubAddr/256);
    AddrL=(INT8U)(SubAddr%256);
  
#ifdef SOFT_I2C_ENV
   if(setjmp(Soft_I2c_Env.Env)==0)
   { 
#endif    
    
    WAITFOR_DRV_CYCLE_TIMEOUT(50);
    OkFlag=I2cSoft_Start(VirtualID);
    OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr);
    
    if(Const_Epprom_Soft[Type].Single==0) 
      OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrH);
     
    OkFlag&=I2cSoft_Send_Byte(VirtualID,AddrL);
    I2cSoft_Start(VirtualID);   //产生起始条件------------PUCK
    OkFlag&=I2cSoft_Send_Byte(VirtualID,SlvAdr|0x1);  //读操作-----------PUCK
    OkFlag&=I2cSoft_Read_nByteS(VirtualID,size,Dst);
    OkFlag&=I2cSoft_Stop(VirtualID);
#ifdef SOFT_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cSoft_Reset(VirtualID);
      OkFlag=0;
    }
    return OkFlag;
}

/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
#注意：地址操作范围：65536字节(64k)
**********************************************************************************/
INT8U Read_Soft_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
{
  INT8U Flag;
  INT16U addr,bytes,tempsize;
  Flag=1;
  
  if(size==0)                                        Flag=0;
  if(Type>MAX_EPPROM_TYPE)                           Flag=0;
  if(size>Const_Epprom_Soft[Type].MaxSize)           Flag=0;
  if(SubAddr>Const_Epprom_Soft[Type].MaxSize)        Flag=0;   
  if((size+SubAddr)>Const_Epprom_Soft[Type].MaxSize) Flag=0;
  
  if(Flag EQ 0)
  {
    ASSERT_FAILED();
    Debug_Print("Read Data Exceed Limited,Addr=%d,size=%d,Maxsize=%d",SubAddr,size,Const_Epprom_Soft[Type].MaxSize); 
    return 0;
  }
  
   if((Const_Epprom_Soft[Type].Single)&&(Const_Epprom_Soft[Type].BitFill))
   {
      bytes=0;
      Flag=1;
      tempsize=size;
      
      for(addr=SubAddr;addr<SubAddr+size;)
      {         
          if(((addr+tempsize)/256)!=(addr/256))  //跨页
            bytes=(addr/256+1)*256-addr;  //当前需要写的字节数                      
          else                                   //同页
            bytes=tempsize;
              
          Flag&=Read_Soft_Func_EEPROM(VirtualID,SlvAdr|Get_Modi_Value(addr/256),addr,Type,bytes,Dst);
          addr+=bytes;
          Dst+=bytes;
          tempsize-=bytes; 
      }
   }
   else
     Flag=Read_Soft_Func_EEPROM(VirtualID,SlvAdr,SubAddr,Type,size,Dst);
  
     return Flag; 
}

#endif