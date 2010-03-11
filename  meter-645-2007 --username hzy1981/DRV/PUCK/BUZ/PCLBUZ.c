
#include "DrvPub.h"


/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the PCLBUZ0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PCLBUZ0_Init( void )	
{
	PCLOE0 = 0;		/* PCLBUZ0 output disable */
	/* PCLBUZ0 pin setting */
	PM14 &= ~0x1;
	P14 &= ~0x1;
	CKS0 &= ~PCLBUZ_OUTCLK_CLR;
	CKS0 |= PCLBUZ_OUTCLK_fMAIN2;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the PCLBUZ0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PCLBUZ0_Start( void )
{
	 PCLOE0 = 1;		/* PCLBUZ0 output enable */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the PCLBUZ0 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PCLBUZ0_Stop( void )
{
	PCLOE0 = 0;		/* PCLBUZ0 output disable */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the PCLBUZ1 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PCLBUZ1_Init( void )	
{
	PCLOE1 = 0;		/* PCLBUZ1 output disable */
	/* PCLBUZ1 pin setting */
	PM14 &= ~0x2;
	P14 &= ~0x2;
	CKS1 &= ~PCLBUZ_OUTCLK_CLR;
	CKS1 |= PCLBUZ_OUTCLK_fMAIN2;
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the PCLBUZ1 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PCLBUZ1_Start( void )
{
	 PCLOE1 = 1;		/* PCLBUZ1 output enable */
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the PCLBUZ1 module.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void PCLBUZ1_Stop( void )
{
	PCLOE1 = 0;		/* PCLBUZ1 output disable */
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


