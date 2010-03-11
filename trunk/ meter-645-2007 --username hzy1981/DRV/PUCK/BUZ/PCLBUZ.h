/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for 78K0R/Kx3
**  16-Bit Single-Chip Microcontrollers
**
**  Copyright(C) NEC Electronics Corporation 2002 - 2010
**  All rights reserved by NEC Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  NEC Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	PCLBUZ.h
**  Abstract :	This file implements device driver for PCLBUZ module.
**  APIlib :	Applilet2 for 78K0R/Kx3 V2.30 [18 Oct. 2007]
**
**  Device :	uPD78F1166_A0
**
**  Compiler :	IAR_C
**
**  Creation date:	2010-3-11
**  
*******************************************************************************
*/
#ifndef _MDPCLBUZ_
#define _MDPCLBUZ_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/*
	Clock Output Selection Register (CKSn)
*/
/* PCLBUZn output enable/disable specification (PCLOEn) */
#define	PCLBUZ_OUTPUT_ENABLE_BIT	0x10	/* clock division circuit operation	enabled. PCL output enabled. */
#define	PCLBUZ_OUTPUT_DISABLE_BIT	0x00	/* clock division circuit operation	stopped. PCL fixed to low level. */
/* PCLBUZn output clock selection(CSELn, CCSn2, CCSn1, CCSn0) */
#define PCLBUZ_OUTCLK_CLR			0x0f	/* for clear bits */
#define PCLBUZ_OUTCLK_fMAIN0		0x00	/* fMAIN */
#define PCLBUZ_OUTCLK_fMAIN1		0x01	/* fMAIN/2 */
#define PCLBUZ_OUTCLK_fMAIN2		0x02	/* fMAIN/2^2 */
#define PCLBUZ_OUTCLK_fMAIN3		0x03	/* fMAIN/2^3 */
#define PCLBUZ_OUTCLK_fMAIN4		0x04	/* fMAIN/2^4 */
#define PCLBUZ_OUTCLK_fMAIN5		0x05	/* fMAIN/2^11 */
#define PCLBUZ_OUTCLK_fMAIN6		0x06	/* fMAIN/2^12 */
#define PCLBUZ_OUTCLK_fMAIN7		0x07	/* fMAIN/2^13 */
#define PCLBUZ_OUTCLK_fSUB0			0x08	/* fSUB */
#define PCLBUZ_OUTCLK_fSUB1			0x09	/* fSUB/2 */
#define PCLBUZ_OUTCLK_fSUB2			0x0A	/* fSUB/2^2 */
#define PCLBUZ_OUTCLK_fSUB3			0x0B	/* fSUB/2^3 */
#define PCLBUZ_OUTCLK_fSUB4			0x0C	/* fSUB/2^4 */
#define PCLBUZ_OUTCLK_fSUB5			0x0D	/* fSUB/2^5 */
#define PCLBUZ_OUTCLK_fSUB6			0x0E	/* fSUB/2^6 */
#define PCLBUZ_OUTCLK_fSUB7			0x0F	/* fSUB/2^7 */

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
enum PCLBUZclock {MAINCLOCK, MAIN2, MAIN4, MAIN8, MAIN16, MAIN2048, MAIN4096, MAIN8192, SUBCLOCK, SUB2, SUB4, SUB8, SUB16, SUB32, SUB64, SUB128 };

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void PCLBUZ0_Init( void );
void PCLBUZ0_Start( void );
void PCLBUZ0_Stop( void );
void PCLBUZ1_Init( void );
void PCLBUZ1_Start( void );
void PCLBUZ1_Stop( void );

#define INIT_IC_CLK      PCLBUZ0_Init
#define START_IC_CLK     PCLBUZ0_Start
#define STOP_IC_CLK      PCLBUZ0_Stop

#define INIT_ESAM_CLK    PCLBUZ1_Init
#define START_ESAM_CLK   PCLBUZ1_Start
#define STOP_ESAM_CLK    PCLBUZ1_Stop

/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */
#endif
