#include "DrvPub.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "B3"
#endif


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
}CONST_EPPROM_HARD;

#define MAX_EPPROM_TYPE  (M24512+1)

CONST CONST_EPPROM_HARD  Const_Epprom_Hard[MAX_EPPROM_TYPE]={
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
函数功能：
入口：
出口：1----------------成功；0----------------失败
注意：地址操作范围：65536字节(64k)
**********************************************************************************/   
INT8U Write_Hard_EEPROM(INT8U SlvAdr,INT16U SubAddr,INT16U size,INT8U Type,INT8U *Src)
{
    INT16U WrNum;
    INT16U Page;
    INT8U AddrH,AddrL;
    INT8U OkFlag;
    
    OkFlag=1;
    
    if(size==0)                                        OkFlag=0;
    if(Type>MAX_EPPROM_TYPE)                           OkFlag=0;
    if(size>Const_Epprom_Hard[Type].MaxSize)           OkFlag=0;
    if(SubAddr>Const_Epprom_Hard[Type].MaxSize)        OkFlag=0;    
    if((size+SubAddr)>Const_Epprom_Hard[Type].MaxSize) OkFlag=0;
    
    
    if(OkFlag EQ 0)
    {
      ASSERT_FAILED();
      Debug_Print("Write Data Exceed Limited,Addr=%d,size=%d,Maxsize=%d",SubAddr,size,Const_Epprom_Hard[Type].MaxSize); 
      return 0;
    }
    
    IICE0=1;               //打开II2C操作时钟，因有可能会关闭-----------PUCK
#ifdef HARD_I2C_ENV
    if(setjmp(Hard_I2c_Env.Env)==0)
    {
#endif
    IIC_HARD_WP_EN;       //开启写操作
    WAITFOR_DRV_CYCLE_TIMEOUT(100);
    WrNum=0;
    AddrH=(INT8U)(SubAddr/256);
    AddrL=(INT8U)(SubAddr%256);
    do{
        OkFlag=I2cStartCondition();	
        Page=AddrL+WrNum; 
        if(Const_Epprom_Hard[Type].Single) //地址为一个字节的器件------PUCK
        {
          if(Const_Epprom_Hard[Type].BitFill==0) //此器件地址是固定的
            OkFlag&=I2cPutAddress(SlvAdr); 
          else                                 //从器件地址根据高字节修改
            OkFlag&=I2cPutAddress(SlvAdr|Get_Modi_Value(((SubAddr+WrNum)/256)));   //从器件地址修改，并下发
        }
        else
        {
          OkFlag&=I2cPutAddress(SlvAdr); 
          OkFlag&=I2cPutData(AddrH+(Page>>8));          
        }       
        
        OkFlag&=I2cPutData((Page&0x00FF)) ;	
        do
        {
           OkFlag&=I2cPutData(*Src); 					
           Src++;WrNum++;
        }while((WrNum<size)&&(((AddrL+WrNum)&(Const_Epprom_Hard[Type].PageSize-1))!=0));
        
        I2cStopCondition();
        if(Const_Epprom_Hard[Type].PageDlyFlg)
          WAITFOR_DRV_MS_TIMEOUT(Const_Epprom_Hard[Type].PageDelay)
        else
          WAITFOR_DRV_CYCLE_TIMEOUT(100)  //没有延时标志，延时100个nop
        }while(WrNum<size);
        IIC_HARD_WP_DIS;     //置WP口线为高，禁止写--------PUCK
#ifdef HARD_I2C_ENV
    return 1;
    }
   else
#else
   if(!OkFlag)
#endif
   {
      IIC_HARD_WP_DIS;     //置WP口线为高，禁止写--------PUCK
      I2cReset();
      OkFlag=0;
   }
    return OkFlag;
}


/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
**********************************************************************************/
INT8U Read_Hard_Func_EEPROM( INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
{
    INT8U NackData;
    INT8U AddrH,AddrL,OkFlag;
     
    AddrH=(INT8U)(SubAddr/256);
    AddrL=(INT8U)(SubAddr%256);
  
#ifdef HARD_I2C_ENV
   if(setjmp(Hard_I2c_Env.Env)==0)
   { 
#endif    
    
    IICE0 = 1;  //打开II2C操作时钟，因有可能会关闭-----------PUCK
    WAITFOR_DRV_CYCLE_TIMEOUT(50);
    OkFlag=I2cStartCondition();
    OkFlag&=I2cPutAddress(SlvAdr);
    
    if(Const_Epprom_Hard[Type].Single==0) 
      OkFlag&=I2cPutData(AddrH);
    OkFlag&=I2cPutData(AddrL);
    I2cStart();   //产生起始条件------------PUCK
    OkFlag&=I2cPutData(SlvAdr|0x1);  //读操作-----------PUCK
    for(;size>0;size--)
    {
      OkFlag&=I2cGetDataAckSet(Dst);
       Dst++;
    }	  
    OkFlag&=I2cGetDataNackSet(&NackData); 
    I2cStopCondition();
#ifdef HARD_I2C_ENV
    return 1;
   }
   else
#else
    if(!OkFlag)
#endif
    {
      I2cReset();
      OkFlag=0;
    }
    return OkFlag;
}

/**********************************************************************************
函数功能：
入口：
出口：1----------------成功；0----------------失败
注意：地址操作范围：65536字节(64k)
**********************************************************************************/
INT8U Read_Hard_EEPROM( INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst)
{
  INT8U Flag;
  INT16U addr,bytes,tempsize;
  Flag=1;
  
  if(size==0)                                        Flag=0;
  if(Type>MAX_EPPROM_TYPE)                           Flag=0;
  if(size>Const_Epprom_Hard[Type].MaxSize)           Flag=0;
  if(SubAddr>Const_Epprom_Hard[Type].MaxSize)        Flag=0;   
  if((size+SubAddr)>Const_Epprom_Hard[Type].MaxSize) Flag=0;
  
  if(Flag EQ 0)
  {
    ASSERT_FAILED();
    Debug_Print("Read Data Exceed Limited,Addr=%d,size=%d,Maxsize=%d",SubAddr,size,Const_Epprom_Hard[Type].MaxSize); 
    return 0;
  }
  
   if((Const_Epprom_Hard[Type].Single)&&(Const_Epprom_Hard[Type].BitFill))
   {
      bytes=0;
      Flag=1;
      tempsize=size;
      
      for(addr=SubAddr;addr<SubAddr+size;)
      {
        if(Const_Epprom_Hard[Type].BitFill>=(addr/256)) //当前器件页数>=操作的页号，才有意义
        {          
          if(((addr+tempsize)/256)!=(addr/256))  //跨页
            bytes=(addr/256+1)*256-addr;  //当前需要写的字节数                      
          else                                   //同页
            bytes=tempsize;
              
          Flag&=Read_Hard_Func_EEPROM(SlvAdr|Get_Modi_Value(addr/256),addr,Type,bytes,Dst);
          addr+=bytes;
          Dst+=bytes;
          tempsize-=bytes;          
        }
        else
        {
          ASSERT_FAILED();  //存储器地址溢出,不准乱操作了
          return 0;
        }
      }
   }
   else
     Flag=Read_Hard_Func_EEPROM(SlvAdr,SubAddr,Type,size,Dst);
  
     return Flag; 
}