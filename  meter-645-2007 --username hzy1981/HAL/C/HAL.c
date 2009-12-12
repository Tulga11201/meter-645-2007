#define HAL_C
#include "Includes.h"
#include "windows.h"


void Put_Char(OS_INT8U Chr)
{
	fprintf(pDebug_File,"%c",Chr);
	printf("%c",Chr);
	
}
OS_INT8U Debug_Out_Public_Puck(OS_INT8U *Srcbuf,OS_INT16U Src_Len)
{
	INT8U i;
	
	for(i=0;i<Src_Len;i++)
		Put_Char(*(Srcbuf+i));

	return 1;
}

void Clear_CPU_Dog()    //清CPU内部看门狗
{
  ;
}

void  Clear_Ext_Dog()    //清CPU外部看门狗
{
  ;

}


//得到某个EEROM对应的文件名
void Get_Rom_File_Name(INT8U ROM_ID,INT8U FileName[])
{
  memcpy(FileName,"EEROM_",6);
  FileName[6]=ROM_ID+0x30;
  memcpy(FileName+7,".bin",4);
  FileName[11]='\0';
}

//写某个EEROM
INT8U Write_EEROM(INT8U ROM_ID,INT16U Off,void *pSrc,INT16U SrcLen)
{
	FILE *p;
	char FileName[20];

	Get_Rom_File_Name(ROM_ID,FileName);

	p=fopen(FileName,"r+b");
	if(p!=NULL)
	{
	  if(fseek(p,Off,SEEK_SET)==0)
	  {
		if(fwrite(pSrc,1,SrcLen,p)==SrcLen)
		{
			fclose(p);
			return 1;
		}
	  }
	  fclose(p);
	}
	ASSERT(0);
	return 0;
}

//读取某个EEROM
INT8U Read_EEROM(INT8U ROM_ID,INT16U Off,INT16U Len,void *pDst,void *pDst_Start,INT16U DstLen)
{
	FILE *p;
	char FileName[20];
	
	Get_Rom_File_Name(ROM_ID,FileName);
	
	p=fopen(FileName,"rb");
	if(p!=NULL)
	{
		if(fseek(p,Off,SEEK_SET)==0)
		{
			if(fread(pDst,1,Len,p)==Len)
			{
				fclose(p);
				return 1;
			}
		}
	    fclose(p);
	}
	ASSERT(0);
	return 0;
}

INT8U EEROM_Temp[40000];
void Init_EEROM()
{
	INT8U *p,i;
	INT32U Len;
	FILE *pFile;
	INT8U FileName[20];
	const INT32U EERom_Size[6]={ROM0_SIZE,ROM1_SIZE,ROM2_SIZE,ROM3_SIZE,ROM4_SIZE,ROM5_SIZE};
 
  p=EEROM_Temp;
  memset(p,0xFF,40000);
  for(i=0;i<sizeof(EERom_Size)/sizeof(EERom_Size[0]);i++)
  {
	  Get_Rom_File_Name(i,FileName);
      if(fopen(FileName,"r")==NULL)//没有找到文件
	  {
		  if((pFile=fopen(FileName,"wb"))!=NULL)
		  {
			 Len=0;
			 while(1)
			 {
			   if(Len+4000<EERom_Size[i])
               {
				   fwrite(p,1,4000,pFile);
			       Len+=4000;
			   }
			   else
			   {
				   fwrite(p,1,EERom_Size[i]-Len,pFile);
			       break;                  
			   }
			 }
             fclose(pFile);
		  }
	  }
  }
  //delete(p);
}

/*
pBCD_Time->Sec=Temp[0];
pBCD_Time->Min=Temp[1];
pBCD_Time->Hour=Temp[2];
pBCD_Time->Week=Temp[3];
pBCD_Time->Date=Temp[4];
pBCD_Time->Month=Temp[5];
pBCD_Time->Year=Temp[6];
*/

INT8U Read_ExtRTC_PUCK(INT8U Dst[],INT8U Len)
{
	/*
	SYSTEMTIME st = {0}; 
	GetLocalTime(&st);//获得当前本地时间 
	GetSystemTime(&st);//这一个是获得格林威治时间，一般不用 
	
	附SYSTEMTIME结构常用成员说明 
		st.wYear;年 
		st.wMonth;月 
		st.wDay;日 
		st.wHour;时 
		st.wMinute;分 
		st.wSecond;秒 
st.wDayOfWeek;星期几
*/
	SYSTEMTIME st = {0}; 
	GetLocalTime(&st);//获得当前本地时间 
	Dst[0]=Hex2Bcd_Byte((INT8U)st.wSecond);
	Dst[1]=Hex2Bcd_Byte((INT8U)st.wMinute);
	Dst[2]=Hex2Bcd_Byte((INT8U)st.wHour);
	Dst[3]=Hex2Bcd_Byte((INT8U)st.wDayOfWeek);
	Dst[4]=Hex2Bcd_Byte((INT8U)st.wDay);
	Dst[5]=Hex2Bcd_Byte((INT8U)st.wMonth);
	Dst[6]=Hex2Bcd_Byte((INT8U)(st.wYear-2000));
  return 1;
}

INT8U Write_ExtRTC_PUCK(INT8U Src[])
{
	return 1;
}

INT8U Read_InterRTC_PUCK(INT8U Dst[],INT8U Len)
{
	SYSTEMTIME st = {0}; 
	GetLocalTime(&st);//获得当前本地时间 
	Dst[0]=Hex2Bcd_Byte((INT8U)st.wSecond);
	Dst[1]=Hex2Bcd_Byte((INT8U)st.wMinute);
	Dst[2]=Hex2Bcd_Byte((INT8U)st.wHour);
	Dst[3]=Hex2Bcd_Byte((INT8U)st.wDayOfWeek);
	Dst[4]=Hex2Bcd_Byte((INT8U)st.wDay);
	Dst[5]=Hex2Bcd_Byte((INT8U)st.wMonth);
	Dst[6]=Hex2Bcd_Byte((INT8U)(st.wYear-2000));

    return 1;
}

INT8U Write_InterRTC_PUCK(INT8U Src[])
{
	return 1;
}

INT8U Read_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pDst,INT16U RD_Len,void *pDst_Start,INT16U DstLen)
{
   ASSERT((INT8U *)pDst>=(INT8U *)pDst_Start && (INT8U *)pDst+RD_Len<=(INT8U *)pDst_Start+DstLen);
   return Read_EEROM(MemNo,Offset,RD_Len,pDst,pDst_Start,DstLen);
}

INT8U Write_PHY_Mem_PUCK(INT8U MemNo,INT32U Offset,void *pSrc,INT16U SrcLen)
{
	return Write_EEROM(MemNo,Offset,pSrc,SrcLen);
}

INT8U Check_Protocol_Data_Storage()
{

	return 1;
}

//
void Init_Debug_Info_File()
{
	//if(fopen("D:\Debug_Info.txt","r")==NULL)//没有找到文件
	//{
	if((pDebug_File=fopen(DEBUG_FILE_NAME,"wb"))!=NULL)
	{
		fprintf(pDebug_File,"////////////////////");
		//fclose(pFile);
	}
	else
		ASSERT(0);
	  //}

}

/*
typedef struct
{
INT32U Chang_Plus_AcEnerg[4];            //A/B/C/SUM各元件正向有功增量:单位:0.01wh
INT32U Chang_Nega_AcEnerg[4];            //A/B/C/SUM各元件反向有功增量:单位:0.01wh

  //INT32U Chang_Plus_ReacEnerg[4];          //A/B/C/SUM各元件正向无功增量(无功组合1):单位:0.01warh  
  //INT32U Chang_Nega_ReacEnerg[4];          //A/B/C/SUM各元件反向无功增量(无功组合2):单位:0.01warh
  
	INT32U Chang_Quad_ReacEnerg[4][4];       //A/B/C/SUM各元件四象限无功增量,Chang_Quad_ReacEnerg[1][2]表示B向3象限无功
	
	  INT32U Add_AmpaHour[3];                 //AH累计:0.0001As,累计量
	  INT32U Add_CopperLoss[4];		  //A,B,C,sum铜损,单位为0.0000001kA2s,累计量
	  INT32U Add_IronLoss[4];		  //A,B,C,sum铁损,单位为0.0000001KV2s，累计量
	  INT32U Add_GenaralErr[4];		  //A,B,C,sum合成误差,单位:0.01*tgFA*s,累计量
	  INT8U CS[CS_BYTES];
}MEASU_ENERG;  
*/
INT16U Get_Measu_AcculateData_PUCK(INT8U ID,void *DstReal,void *Dst_Start,INT16U DstLen,INT16U DstMaxLen)
{

	
	mem_cpy(DstReal,(void *)(&Measu_Energ_ToPub_PUCK),sizeof(MEASU_ENERG),DstReal,DstMaxLen);
	

	return sizeof(MEASU_ENERG);  
}

void HAL_Init()
{
	INT8U i;

	Init_EEROM();//初始化EEROM
	Init_Debug_Info_File();
	
	memset((void *)&Measu_Status_Mode_ToPub_PUCK,0,sizeof(Measu_Status_Mode_ToPub_PUCK));
    Measu_Status_Mode_ToPub_PUCK.DataRecFlg = 1;
	SET_STRUCT_SUM(Measu_Status_Mode_ToPub_PUCK);
///////////////////////////////////////////////////////////////
	for(i = 0; i < 4; i ++)
	{
		if(i < 3)
		  Measu_Energ_ToPub_PUCK.Add_AmpaHour[i] = 0;

		Measu_Energ_ToPub_PUCK.Add_CopperLoss[i] = 0;
		Measu_Energ_ToPub_PUCK.Add_GenaralErr[i] = 0;
	    Measu_Energ_ToPub_PUCK.Add_IronLoss[i] = 0;

		Measu_Energ_ToPub_PUCK.Chang_Plus_AcEnerg[i] = 100;
		Measu_Energ_ToPub_PUCK.Chang_Nega_AcEnerg[i] = 100;

	    Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[0][i] = 100;
		Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[1][i] = 100;
		Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[2][i] = 100;
	    Measu_Energ_ToPub_PUCK.Chang_Quad_ReacEnerg[3][i] = 100;		
	}
	SET_STRUCT_SUM(Measu_Energ_ToPub_PUCK);
////////////////////////////////////////////////////////////////
/*
typedef struct
{
	MEASU_DATA AcPower;       //有功功率:UNIT:0.000001kW
	MEASU_DATA ReacPower;     //无功功率:UNIT:0.000001kvar
	MEASU_DATA AppPower;      //视在功率:UNIT:0.000001kva
	MEASU_DATA Volt;          //电压有效值：无合相 UNIT:0.0001V
	MEASU_DATA Curr;          //电流有效值: UNIT:0.0001A	
	MEASU_DATA PFactor;       //功率因数: UNIT:0.000001
	MEASU_DATA Freq;          //频率:UNIT:0.000001Hz
	MEASUFLAG  Quadrant;      //各相象限：QUADRANT1～QUADRANT4代表1～4象限。
	MEASU_DATA Angle;         //电压电流夹角：UINT:0.01度
	INT32U     Temprate;      //温度
	INT8U CS[CS_BYTES];
	}MEASU_INSTANT;   //MeasuIC瞬时量计量数据
*/
	Measu_InstantData_ToPub_PUCK.AcPower.A=100000;
	Measu_InstantData_ToPub_PUCK.AcPower.B=100000;
	Measu_InstantData_ToPub_PUCK.AcPower.C=100000;
	Measu_InstantData_ToPub_PUCK.AcPower.Sum=100000;

	Measu_InstantData_ToPub_PUCK.ReacPower.A=100000;
	Measu_InstantData_ToPub_PUCK.ReacPower.B=100000;
	Measu_InstantData_ToPub_PUCK.ReacPower.C=100000;
	Measu_InstantData_ToPub_PUCK.ReacPower.Sum=100000;

	Measu_InstantData_ToPub_PUCK.AppPower.A=100000;
	Measu_InstantData_ToPub_PUCK.AppPower.B=100000;
	Measu_InstantData_ToPub_PUCK.AppPower.C=100000;
	Measu_InstantData_ToPub_PUCK.AppPower.Sum=100000;

	Measu_InstantData_ToPub_PUCK.Volt.A=2200000;
	Measu_InstantData_ToPub_PUCK.Volt.B=2200000;
	Measu_InstantData_ToPub_PUCK.Volt.C=2200000;
	Measu_InstantData_ToPub_PUCK.Volt.Sum=2200000;

	Measu_InstantData_ToPub_PUCK.Quadrant.A=QUADRANT1;
	Measu_InstantData_ToPub_PUCK.Quadrant.B=QUADRANT1;
	Measu_InstantData_ToPub_PUCK.Quadrant.C=QUADRANT1;
	Measu_InstantData_ToPub_PUCK.Quadrant.Sum=QUADRANT1;

	SET_STRUCT_SUM(Measu_InstantData_ToPub_PUCK);

}

void count_1ms(void)
{ 
	static INT8U num1=0,Ms_Timer=0;
	
	Ms_Timer_Pub++;
	
	Ms_Timer++;
	if(Ms_Timer>=OS_MS_PER_TICK)
	{
		Ms_Timer=0;    
		OS_Tick_Hook();
	}
	
	num1++;
	if(num1>=10)
	{
		Ms10_Timer_Pub++;
		num1=0;
	}  
    
	//Num++;
	//if(Num>=MS_HOOK_NUM)
	//{
		//ExtPort_xMs_Hook();
		//Num=0;
	//}     
}

INT8U Check_Event_End(INT8U Event_ID)
{
	return 1;
}
#undef HAL_C
