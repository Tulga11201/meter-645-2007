/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for 78K0R/Kx3
**  16-Bit Single-Chip Microcontrollers
**
**  Copyright(C) NEC Electronics Corporation 2002 - 2008
**  All rights reserved by NEC Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  NEC Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	Int_user.c
**  Abstract :	This file implements device driver for INT module.
**  APIlib :	Applilet2 for 78K0R/Kx3 V2.30 [18 Oct. 2007]
**
**  Device :	uPD78F1166_A0
**
**  Compiler :	IAR_C
**
**  Creation date:	2008-6-10
**  
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/

/* Start user code for include definition. Do not edit comment generated here */
/* End user code for include definition. Do not edit comment generated here */
#include "Pub_PUCK.h"
/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTP0 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTP0_vect
__interrupt void MD_INTP0(void)
{
	/* Start user code. Do not edit comment generated here */
          Inter_CF2();
	/* End user code. Do not edit comment generated here */
}

#pragma vector = INTP1_vect
__interrupt void MD_INTP1(void)
{
	/* Start user code. Do not edit comment generated here */
           //INT_1HZ();
	/* End user code. Do not edit comment generated here */
}

#pragma vector = INTP3_vect
__interrupt void MD_INTP3(void)
{
	/* Start user code. Do not edit comment generated here */

	/* End user code. Do not edit comment generated here */
}

#pragma vector = INTP4_vect
__interrupt void MD_INTP4(void)
{
	/* Start user code. Do not edit comment generated here */
           POWER_DOWN();
	/* End user code. Do not edit comment generated here */
}

#pragma vector = INTP5_vect
__interrupt void MD_INTP5(void)
{
	/* Start user code. Do not edit comment generated here */
        IR_Decode_Proc();
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTP6 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/


#ifdef LOW_COST_HARD_EN           //Level：0表示开启soft时钟
  #pragma vector = INTP2_vect
  __interrupt void MD_INTP2(void)
  {
          /* Start user code. Do not edit comment generated here */
             Inter_CF1();
          /* End user code. Do not edit comment generated here */
  }

  #pragma vector = INTP6_vect
  __interrupt void MD_INTP6(void)
  {
          /* Start user code. Do not edit comment generated here */
          //   Inter_CF1();
          /* End user code. Do not edit comment generated here */
  }
#else
 #pragma vector = INTP2_vect
  __interrupt void MD_INTP2(void)
  {
          /* Start user code. Do not edit comment generated here */
           //  Inter_CF1();
          /* End user code. Do not edit comment generated here */
  }
  #pragma vector = INTP6_vect
  __interrupt void MD_INTP6(void)
  {
          /* Start user code. Do not edit comment generated here */
             Inter_CF1();
          /* End user code. Do not edit comment generated here */
  }
#endif


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTP10 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/


#pragma vector = INTP7_vect
__interrupt void MD_INTP7(void)
{
	/* Start user code. Do not edit comment generated here */
           //Inter_ALL_LOSS();
          INT_1HZ();
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTP8 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTP8_vect
__interrupt void MD_INTP8(void)
{
	/* Start user code. Do not edit comment generated here */
          Inter_Down_Key();
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTP9 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTP9_vect
__interrupt void MD_INTP9(void)
{
	/* Start user code. Do not edit comment generated here */

	/* End user code. Do not edit comment generated here */
}



#pragma vector = INTP10_vect
__interrupt void MD_INTP10(void)
{
	/* Start user code. Do not edit comment generated here */
           Inter_Prg_Key();

	/* End user code. Do not edit comment generated here */
}


#pragma vector = INTP11_vect
__interrupt void MD_INTP11(void)
{
	/* Start user code. Do not edit comment generated here */

       Irda_Wake_Up();

	/* End user code. Do not edit comment generated here */
}


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTKR interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
#pragma vector = INTKR_vect
__interrupt void MD_INTKR(void)
{
	/* Start user code. Do not edit comment generated here */
       INT8U key_flag=P7;

    
       if((key_flag&0x02)==0 && PM7_bit.no1==1)//KR1,,清需量/左按钮
       {
          Inter_Left_Key();
       }
       if((key_flag&0x04)==0 && PM7_bit.no2==1)//KR2,选择/右按钮
       {
          Inter_Right_Key();       
       }
       if((key_flag&0x08)==0 && PM7_bit.no3==1)//KR3
       {
          Inter_Up_Key();
       }

       
       
       /* End user code. Do not edit comment generated here */
}


/* Start adding user code. Do not edit comment generated here */

/* End user code adding. Do not edit comment generated here */


