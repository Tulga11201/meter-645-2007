#define     MeasuBase_PUCK
#include    "Pub_PUCK.h"

#if REDEF_FILE_LINE_EN > 0
#line  __LINE__ "A6"
#endif

/**********************************************************************************
void Measu_Ic_Delay(void)
{    
  asm("nop"); 
  asm("nop"); 
  asm("nop");  
}
**********************************************************************************/

/**********************************************************************************
�������ܣ�����������/�����ӳ���
��ڣ�    ��������/�����Ĵ�����ַ
���ڣ�    ��������/����,ʵ��Ϊ3�ֽڣ����ֽ�����
11.0592�£�����SCLKƵ�ʣ�һ���ܲ�175k����
**********************************************************************************/
INT32U Measu_RdData(INT8U Reg)
{
  INT8U i,j,temp[3];
  INT32U ReturData;
  
  MEASU_IC_DELAY;
  MEASU_CS_1;
  MEASU_CLK_0;
  MEASU_CS_0;
  
  for(i=0;i<=7;i++)
  {
    MEASU_CLK_1;
    if((Reg&0x80))
      MEASU_DOUT_1;   
    else   
      MEASU_DOUT_0;
    
    MEASU_IC_DELAY;
    
    MEASU_CLK_0;
    Reg<<=1;  
  }  
  //MEASU_DOUT_0;  //���ݷ�������ݶ˿ڱ�֤ȷ���ĵ͵�ƽ----------PUCK
   MEASU_IC_DELAY;                      //SCLKƵ�ʵ���200k()�����صȴ���Ƶ�ʴ���200k���ȴ�3us      
  
  temp[0]=temp[1]=temp[2]=0;
  for(i=0;i<3;i++)
  {
    for(j=0;j<=7;j++)
    {
      MEASU_CLK_1;
      MEASU_IC_DELAY;
      if(MEASU_DIN_STAT)
      {
        if(MEASU_DIN_STAT)
          temp[2-i]=temp[2-i]|0x01;     
      }
      MEASU_CLK_0;
      if(j!=7)
        temp[2-i]<<=1;
    }
  }
  //WAITFOR_DRV_CYCLE_TIMEOUT(10);
  MEASU_CS_1;
  
  ReturData=(INT32U)temp[0]+(INT32U)temp[1]*256+(INT32U)temp[2]*65536;  //�س�3�ֽ�
  ReturData=ReturData&0x00FFFFFF;
  return(ReturData);
}

/**********************************************************************************
�������ܣ�д���������ӳ���
��ڣ�    
ParaReg-------------���������Ĵ�����ַ
paradata_����-------��������
���ڣ�    ��
**********************************************************************************/
void Measu_WrData(INT8U ParaReg,INT32U paradata)
{
  INT8U para[3];
  INT8U i,j;
  
  MEASU_IC_DELAY;
  para[2]=*((INT8U *)&paradata);     //����ֽ�
  para[1]=*((INT8U *)&paradata+1);   //�м��ֽ�
  para[0]=*((INT8U *)&paradata+2);   //����ֽ�
  
  MEASU_CS_1;
  MEASU_CLK_0;
  MEASU_CS_0;
  for(i=0;i<=7;i++)
  {
    MEASU_CLK_1;
    if((ParaReg&0x80))
      MEASU_DOUT_1;
    else 
      MEASU_DOUT_0;
    
    MEASU_IC_DELAY;
    
    MEASU_CLK_0;
    ParaReg<<=1;  
  }
  //MEASU_DOUT_0;  //���ݷ�������ݶ˿ڱ�֤ȷ���ĵ͵�ƽ----------PUCK
  
  for(i=0;i<3;i++)
  {
    for(j=0;j<=7;j++)
    {
      MEASU_CLK_1;
      if((para[i]&0x80))
        MEASU_DOUT_1;
      else
        MEASU_DOUT_0;
      
      MEASU_IC_DELAY;
      
      MEASU_CLK_0;
      para[i]<<=1;
    }
  }
  
  //MEASU_DOUT_0;  //���ݷ�������ݶ˿ڱ�֤ȷ���ĵ͵�ƽ----------PUCK
  
  MEASU_CS_1;
}
/**********************************************************************************
�������ܣ������ݱȽ�
��ڣ�    
LastData-----�����Ĵ�����ַ
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_RdCompData(INT32U LastData)
{ 
  if(Measu_RdData(REG_R_LASTRD) EQ LastData)
    return 1;

  return 0;
}
/**********************************************************************************
�������ܣ������������Ƚ�
��ڣ�    
ParaReg-----�����Ĵ�����ַ
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_RdParaAndCompData(INT8U ParaReg,INT8U DstBuf[])
{
  INT32U TempData1,TempData2;
  
  TempData1=Measu_RdData(ParaReg);
  TempData2=Measu_RdData(ParaReg);
  
  if(TempData1!=TempData2)
    return 0;
  
  mem_cpy(DstBuf,(INT8U *)(&TempData1),4,DstBuf,4);    //DstBufǿ��ת������������ܻ�����⣬��mem_cpy
  return 1;

}
/**********************************************************************************
�������ܣ�д���ݱȽ�
��ڣ�    
ParaReg-----�����Ĵ�����ַ
WrData-------����
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_WrAndCompData(INT8U ParaReg,INT32U WrData)
{
  INT32U tempdata;
  
  WrData=WrData&0x00ffffff;
  Measu_WrData(ParaReg,WrData);
  tempdata=Measu_RdData(REG_R_LASTWR);
  if(tempdata==WrData)
    return 1;
   
  return 0;
}
/**********************************************************************************
�������ܣ������ݣ����Ƚ�
��ڣ�    
ParaReg-----�����Ĵ�����ַ
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_RdAndCompData(INT8U ParaReg,INT8U DstBuf[])
{
  INT8U  Flag;
  INT32U TempData;
  

  TempData=Measu_RdData(ParaReg);
  Flag=Measu_RdCompData(TempData);
  
  if(!Flag)
    return 0;
  
  mem_cpy(DstBuf,(INT8U *)(&TempData),4,DstBuf,4);    //DstBufǿ��ת������������ܻ�����⣬��mem_cpy
  return Flag;

}

/**********************************************************************************
�������ܣ������������Ƚ�3��
��ڣ�    
ParaReg-----�����Ĵ�����ַ
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_RdAndCompData_3Times(INT8U ParaReg,INT8U DstBuf[])
{
  INT8U  i,Flag;
 
  if(ParaReg>MAX_MEASU_RD_REG)
  {
    //mem_set(DstBuf,0x00,4,DstBuf,4);    
    return 0;
  }
    
  for(i=0;i<3;i++)
  {
    Flag=Measu_RdAndCompData(ParaReg,DstBuf);
    /*if(Flag&&((DstBuf[0]!=0xff)||(DstBuf[1]!=0xff)||(DstBuf[2]!=0xff)))
      return 1;
    if(Flag&&(DstBuf[0]==0xff)&&(DstBuf[1]==0xff)&&(DstBuf[2]==0xff))
    {
      //Debug_Print("Measure_Error----->SPI Rd Data Compare Err,Reg=%d,RD=0xffffff,Read Aganin After 153ms",ParaReg);
      SYS_TimeDly_Ms(153);    //�������ٵ�153������ٶ�
    }*/
    if(Flag)
      return 1;
    OS_TimeDly_Ms(10);  //����10������ٶ�
  }    
  
  Debug_Print("Measure_Error----->Read Data Compare Error With 3 Times,Reg=0x%x!",ParaReg);
  MeasuStatusMode.RdCsErr=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return 0;
}
/**********************************************************************************
�������ܣ�д���ݣ����Ƚ�3��
��ڣ�    
LastData-----�����Ĵ�����ַ
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_WrAndCompData_3Times(INT8U ParaReg,INT32U WrData)
{
  INT8U  Flag,i;   
  for(i=0;i<3;i++)
  {
    Flag=Measu_WrAndCompData(ParaReg,WrData);
    if(Flag)
      return 1;
  }
  Debug_Print("Write Para Compare Error With 3 Times,Reg=0x%x\n",ParaReg); 
  MeasuStatusMode.WrCsErr=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return 0;

}
/**********************************************************************************
�������ܣ������������Ƚ�
��ڣ�    
ParaReg-----�����Ĵ�����ַ
���ڣ� 1------��ʾ�ȶ���ȷ��0---------�ȶԴ���
**********************************************************************************/
INT8U Measu_RdAndCompPara_3Times(INT8U ParaReg,INT8U DstBuf[])
{
  INT8U  i,Flag;
 
  EnMeasuPara();
  
  for(i=0;i<3;i++)
  {
    Flag=Measu_RdParaAndCompData(ParaReg,DstBuf);
    /*if(Flag&&((DstBuf[0]!=0xff)||(DstBuf[1]!=0xff)||(DstBuf[2]!=0xff)))
    {
      EnMeasuData();
      return 1;
    }
    if(Flag&&(DstBuf[0]==0xff)&&(DstBuf[1]==0xff)&&(DstBuf[2]==0xff))
    {
      Debug_Print("Measure_Error----->SPI Rd Para Compare Err,Reg=%d,RD=0xffffff,Read Aganin After 153ms",ParaReg);
      SYS_TimeDly_Ms(153);    //�������ٵ�153������ٶ�
    }*/
    if(Flag)
    {
      EnMeasuData();
      return 1;
    }
    OS_TimeDly_Ms(10);  //����10������ٶ�
  }    
  
  EnMeasuData();
  Debug_Print("Measure_Error----->Read Para Compare Error With 3 Times,Reg=0x%x!",ParaReg);  
  MeasuStatusMode.RdCsErr=1;
  SET_STRUCT_SUM(MeasuStatusMode);
  return 0;
}
