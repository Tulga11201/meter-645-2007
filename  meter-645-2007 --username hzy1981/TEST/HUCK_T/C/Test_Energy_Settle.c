#define TEST_ENERGY_C
#include "includes.h"

INT8U Test_Get_Next_Settle_Time()
{
	INT8U Re;

	S_HEX_Time Src_Time;
	S_HEX_Time Dst_Time;

	Re=1;

	Settle_Time.Time_D_H[0][0]=0x10;
	Settle_Time.Time_D_H[0][1]=0x10;

	Settle_Time.Time_D_H[1][0]=0x15;
	Settle_Time.Time_D_H[1][1]=0x15;

	Settle_Time.Time_D_H[2][0]=0x20;
	Settle_Time.Time_D_H[2][1]=0x20;
	SET_STRUCT_SUM(Settle_Time);
//09年1月1日0时的前后结算日
	Src_Time.Time[T_MIN]=0;
	Src_Time.Time[T_HOUR]=0;
	Src_Time.Time[T_DATE]=0x01;
	Src_Time.Time[T_MONTH]=0x01;
	Src_Time.Time[T_YEAR]=0x09;
	SET_STRUCT_SUM(Src_Time);


	Get_Last_Settle_Time(&Src_Time,&Dst_Time,&Dst_Time,sizeof(Dst_Time));
	if(!(Dst_Time.Time[T_HOUR]==20 && Dst_Time.Time[T_DATE]==20 &&\
	     Dst_Time.Time[T_MONTH]==12 && Dst_Time.Time[T_YEAR]==8))
	{
		OS_ASSERT(0);
		Re=0;
	}

	Get_Next_Settle_Time(&Src_Time,&Dst_Time,&Dst_Time,sizeof(Dst_Time));
	if(!(Dst_Time.Time[T_HOUR]==10 && Dst_Time.Time[T_DATE]==10 &&\
		Dst_Time.Time[T_MONTH]==1 && Dst_Time.Time[T_YEAR]==9))
	{
		OS_ASSERT(0);
		Re=0;
	}
//09年1月15日15时的前后结算日
	Src_Time.Time[T_MIN]=0;
	Src_Time.Time[T_HOUR]=22;
	Src_Time.Time[T_DATE]=22;
	Src_Time.Time[T_MONTH]=0x01;
	Src_Time.Time[T_YEAR]=0x09;
	SET_STRUCT_SUM(Src_Time);

	Get_Last_Settle_Time(&Src_Time,&Dst_Time,&Dst_Time,sizeof(Dst_Time));
	if(!(Dst_Time.Time[T_HOUR]==20 && Dst_Time.Time[T_DATE]==20 &&\
		Dst_Time.Time[T_MONTH]==1 && Dst_Time.Time[T_YEAR]==9))
	{
		OS_ASSERT(0);
		Re=0;
	}	
	
	Get_Next_Settle_Time(&Src_Time,&Dst_Time,&Dst_Time,sizeof(Dst_Time));
	if(!(Dst_Time.Time[T_HOUR]==10 && Dst_Time.Time[T_DATE]==10 &&\
		Dst_Time.Time[T_MONTH]==2 && Dst_Time.Time[T_YEAR]==9))
	{
		OS_ASSERT(0);
		Re=0;
	}
	
	return Re;
}

INT8U Test_Settle_Settle_Data()
{
	INT8U i;
	//S_HEX_Time TempTime;

	Init_Clock(SYS_NORMAL);
	Read_Storage_Data(SDI_MONTH_SETTLE_DAY1,(void *)Settle_Time.Time_D_H[0],(void *)Settle_Time.Time_D_H[0],sizeof(Settle_Time.Time_D_H[0]));
	Read_Storage_Data(SDI_MONTH_SETTLE_DAY2,(void *)Settle_Time.Time_D_H[1],(void *)Settle_Time.Time_D_H[1],sizeof(Settle_Time.Time_D_H[1]));
	Read_Storage_Data(SDI_MONTH_SETTLE_DAY3,(void *)Settle_Time.Time_D_H[2],(void *)Settle_Time.Time_D_H[2],sizeof(Settle_Time.Time_D_H[2]));
	Settle_Energy_Data((S_HEX_Time *)&Cur_Time0);

	for(i=0;i<MAX_ENERGY_SETTLE_NUM;i++)
	{
		if(sizeof(Cur_Energy)!=Read_His_Energy_Data(i,(void *)&Cur_Energy,(void *)&Cur_Energy,sizeof(Cur_Energy)))
			return 0;
	}
	return 1;
}
#undef TEST_ENERGY_C