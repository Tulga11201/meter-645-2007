#include "Pub_PUCK.h"
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the Port I/O.
**
**  Parameters:
**	Mode:0----------表示normal下的初始化；1---------------表示resume下的初始化；2-------------表示sleep下的初始化
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_Init(INT32U Mode )
{
  switch(Mode)
  {
  case SYS_NORMAL:  //正常模式下的IO初始化
        //数据口初始化
        P0 = 0;
	P1 = 0;
	P2_bit.no0=1; P2_bit.no2=1; P2_bit.no4=1; P2_bit.no5=0;        
        P4_bit.no2=1; P4_bit.no3=1; P4_bit.no5=1; P4_bit.no7=1;
        P6_bit.no4=1; P6_bit.no5=1; P6_bit.no6=1; P6_bit.no7=1;        
	P8=0;        
	P11=0;
	P14=0;        
        P15_bit.no0=1; P15_bit.no1=1; P15_bit.no3=0;P15_bit.no4=0; P15_bit.no5=0; P15_bit.no6=0;
        
        //模式寄存器初始化
        PM0_bit.no5=0; 
        //PM0_bit.no2=0;PM0_bit.no3=0;   //P0_2~P0_3 UART1  －－－09－04－16，因版本不同，可能悬空，在串口中初始化
        PM0|=PM0_DEFAULT;
        
        
        PM1_bit.no0=0; PM1_bit.no5=0;        
        PM2_bit.no0=0; PM2_bit.no2=0;  PM2_bit.no4=0; PM2_bit.no5=0; 
        
        PM3|=PM3_DEFAULT;
        PM3_bit.no0=0;             //P3_0  IC_FAIL －－－09－04－16
        
        PM4_bit.no2=0; PM4_bit.no3=0;  PM4_bit.no5=0;
        PM5_bit.no0=0; PM5_bit.no1=0;PM5_bit.no2=0;
        PM5_bit.no3=1; //P5_3-----CPU卡插入检测
        PM5_bit.no4=0;  //WDI
        
        PM7_bit.no0=0; 
        LARGE_TOOGLE_OFF_SET;   //将常闭的关闭
        LARGE_TOOGLE_ON_SET;
        //LARGE_TOOGLE_ON_CLR;  
        
        PM7_bit.no5=0;   //按钮共用，且为NC，设定为输出，09－04－05
        PM8_bit.no0=0; 
        PM8_bit.no1=0; 
        PM8_bit.no2=0; 
        PM8_bit.no3=0; 
        PM8_bit.no4=0;  
        PM8_bit.no6=0;    //上电后，强行关闭液晶电源
        PM8_bit.no7=0;    //CPU卡时钟
        PM11_bit.no0=1;  //关闭远红外，防止灯光等误进入
        PM11|=PM11_DEFAULT;
        PM12|=PM12_DEFAULT;
        
        PM13_bit.no1=0;   //跳闸指示灯
	PM13|=PM13_DEFAULT;        
        PM14_bit.no2=0; PM14_bit.no5=0; PM14|=PM14_DEFAULT;        
        PM15_bit.no2=0; PM15_bit.no3=0; PM15_bit.no4=0; PM15_bit.no5=0; PM15_bit.no6=0; PM15_bit.no7=0;   
	ADPC = PORT_ADPC_16DIO;
     break;
  case SYS_RESUME:  //唤醒模式下的IO口初始化
    Init_All_IO_Resume(Ext_Device_Stat.Status);
    break;
  case SYS_SLEEP:  //sleep模式下的IO口初始化
    Init_All_IO_Sleep();
    break;
  }
    
}




/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P15 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP15Output( BOOL initialValue )
{
	if( initialValue )
	{
		P1 |= Pn5_OUTPUT_1;
	}
	else
	{
		P1 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM1 &= PMn5_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P20 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP20Output( BOOL initialValue )
{
	if( initialValue )
	{
		P2 |= Pn0_OUTPUT_1;
	}
	else
	{
		P2 &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM2 &= PMn0_CHANGE_OUTPUT;
}


void PORT_ChangeP10Output( BOOL initialValue )
{
	if( initialValue )
	{
		P1 |= Pn0_OUTPUT_1;
	}
	else
	{
		P1 &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM1 &= PMn0_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P21 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP21Output( BOOL initialValue )
{
	if( initialValue )
	{
		P2 |= Pn1_OUTPUT_1;
	}
	else
	{
		P2 &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM2 &= PMn1_CHANGE_OUTPUT;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P22 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP22Output( BOOL initialValue )
{
	if( initialValue )
	{
		P2 |= Pn2_OUTPUT_1;
	}
	else
	{
		P2 &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM2 &= PMn2_CHANGE_OUTPUT;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P23 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP23Output( BOOL initialValue )
{
	if( initialValue )
	{
		P2 |= Pn3_OUTPUT_1;
	}
	else
	{
		P2 &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM2 &= PMn3_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P24 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP24Output( BOOL initialValue )
{
	if( initialValue )
	{
		P2 |= Pn4_OUTPUT_1;
	}
	else
	{
		P2 &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PM2 &= PMn4_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P25 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP25Output( BOOL initialValue )
{
	if( initialValue )
	{
		P2 |= Pn5_OUTPUT_1;
	}
	else
	{
		P2 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM2 &= PMn5_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P51 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP51Output( BOOL initialValue )
{
	if( initialValue )
	{
		P5 |= Pn1_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM5 &= PMn1_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P53 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP53Output( BOOL initialValue )
{
	if( initialValue )
	{
		P5 |= Pn3_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM5 &= PMn3_CHANGE_OUTPUT;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P54 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP54Output( BOOL initialValue )
{
	if( initialValue )
	{
		P5 |= Pn4_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~Pn4_OUTPUT_1;
	}
	//PM5 &= PMn4_CHANGE_OUTPUT;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P55 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP55Output( BOOL initialValue )
{
	if( initialValue )
	{
		P5 |= Pn5_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM5 &= PMn5_CHANGE_OUTPUT;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P56 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP56Output( BOOL initialValue )
{
	if( initialValue )
	{
		P5 |= Pn6_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PM5 &= PMn6_CHANGE_OUTPUT;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P57 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP57Output( BOOL initialValue )
{
	if( initialValue )
	{
		P5 |= Pn7_OUTPUT_1;
	}
	else
	{
		P5 &= (UCHAR)~Pn7_OUTPUT_1;
	}
	PM5 &= PMn7_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P64 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP05Output( BOOL initialValue )
{
	if( initialValue )
	{
		P0 |= Pn5_OUTPUT_1;
	}
	else
	{
		P0 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM0 &= PMn5_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P64 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP64Output( BOOL initialValue )
{
     P6_bit.no4=initialValue;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P65 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP65Output( BOOL initialValue )
{
  P6_bit.no5=initialValue;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P66 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP66Output( BOOL initialValue )
{
    P6_bit.no6=initialValue;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P67 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP67Output( BOOL initialValue )
{
   P6_bit.no7=initialValue;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P70 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP70Output( BOOL initialValue )
{
	if( initialValue )
	{
		P7 |= Pn0_OUTPUT_1;
	}
	else
	{
		P7 &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM7 &= PMn0_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P80 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP80Output( BOOL initialValue )
{
  P8_bit.no0=initialValue;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P81 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP81Output( BOOL initialValue )
{
   P8_bit.no1=initialValue;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P82 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP82Output( BOOL initialValue )
{
    P8_bit.no2=initialValue;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P83 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP83Output( BOOL initialValue )
{
    P8_bit.no3=initialValue;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P84 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP84Output( BOOL initialValue )
{
	/*if( initialValue )
	{
		P8 |= Pn4_OUTPUT_1;
	}
	else
	{
		P8 &= (UCHAR)~Pn4_OUTPUT_1;
	}*/
	//PM8 &= PMn4_CHANGE_OUTPUT;
        P8_bit.no4=initialValue;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P85 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP85Output( BOOL initialValue )
{
	if( initialValue )
	{
		P8 |= Pn5_OUTPUT_1;
	}
	else
	{
		P8 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM8 &= PMn5_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P86 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP86Output( BOOL initialValue )
{
	if( initialValue )
	{
		P8 |= Pn6_OUTPUT_1;
	}
	else
	{
		P8 &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PM8 &= PMn6_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P110 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP110Output( BOOL initialValue )
{
	if( initialValue )
	{
		P11 |= Pn0_OUTPUT_1;
	}
	else
	{
		P11 &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM11 &= PMn0_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P111 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP111Output( BOOL initialValue )
{
	if( initialValue )
	{
		P11 |= Pn1_OUTPUT_1;
	}
	else
	{
		P11 &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM11 &= PMn1_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P130 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP130Output( BOOL initialValue )
{
	if( initialValue )
	{
		P13 |= Pn0_OUTPUT_1;
	}
	else
	{
		P13 &= (UCHAR)~Pn0_OUTPUT_1;
	}
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P142 to output mode by software.
**
**  Parameters:
**	enableNch :	N-ch enable or not
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP142Output( BOOL enableNch, BOOL initialValue )
{
        P14_bit.no2=initialValue;
        
	if( enableNch )
	{
		POM14 |= POMn2_Nch_ON;
	}
	else
	{
		POM14 &= (UCHAR)~POMn2_Nch_ON;
	}
	//PM14 &= PMn2_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P145 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP145Output( BOOL initialValue )
{
	if( initialValue )
	{
		P14 |= Pn5_OUTPUT_1;
	}
	else
	{
		P14 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM14 &= PMn5_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P150 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP150Output( BOOL initialValue )
{
  P15_bit.no0=initialValue;
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P151 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP151Output( BOOL initialValue )
{
  P15_bit.no1=initialValue;

}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P152 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP152Output( BOOL initialValue )
{
	if( initialValue )
	{
		P15 |= Pn2_OUTPUT_1;
	}
	else
	{
		P15 &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM15 &= PMn2_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P153 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP153Output( BOOL initialValue )
{
	if( initialValue )
	{
		P15 |= Pn3_OUTPUT_1;
	}
	else
	{
		P15 &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM15 &= PMn3_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P154 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP154Output( BOOL initialValue )
{
	if( initialValue )
	{
		P15 |= Pn4_OUTPUT_1;
	}
	else
	{
		P15 &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PM15 &= PMn4_CHANGE_OUTPUT;
}



/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P155 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP155Output( BOOL initialValue )
{
	if( initialValue )
	{
		P15 |= Pn5_OUTPUT_1;
	}
	else
	{
		P15 &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM15 &= PMn5_CHANGE_OUTPUT;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P156 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP156Output( BOOL initialValue )
{
	if( initialValue )
	{
		P15 |= Pn6_OUTPUT_1;
	}
	else
	{
		P15 &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PM15 &= PMn6_CHANGE_OUTPUT;
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P151 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP131Output( BOOL initialValue )
{        
   P13_bit.no1=initialValue;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function changes P151 to output mode by software.
**
**  Parameters:
**	initialValue :	initial output 1 or 0
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP157Output( BOOL initialValue )
{
  P15_bit.no7=initialValue;

}
