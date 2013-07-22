/**************************************************************************************************
Authours:				Craig Comberbach
Target Hardware:		PIC24F
Chip resources used:	A2D Module
Code assumptions:
Purpose:				Read the Thermistor inputs

Version History:
v0.0.0	2013-07-20  Craig Comberbach
	Compiler: C30 v3.31	IDE: MPLABx 1.80	Tool: RealICE	Computer: Intel Xeon CPU 3.07 GHz, 6 GB RAM, Windows 7 64 bit Professional SP1
	First version
**************************************************************************************************/
/*************    Header Files    ***************/
#include "Project Setup.h"

/************* Semantic Versioning***************/
/************Arbitrary Functionality*************/
/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
/***********State Machine Definitions*************/
/*************  Global Variables  ***************/
/*************Function  Prototypes***************/
void Initialize_TMR1(void);
void Initialize_TMR2(void);
void Initialize_TMR3(void);
void Initialize_TMR4(void);

/************* Device Definitions ***************/
/************* Module Definitions ***************/
/************* Other  Definitions ***************/

void Initialize_TMR1(void)
{
	//TODO - Write TMR1 Initialize
	//Timer1 Control Register
	T1CONbits.TCS	= 0;//0 = Internal clock (FOSC/2)
//	T1CONbits.TSYNC	= Not used because TCS = 0

//	T1CONbits.TCKPS	= ;//TODO - Finish this one

	T1CONbits.TGATE	= 0;//0 = Gated time accumulation is disabled
//	T1CONbits.T1ECS	= Not valid because TCS = 0
	T1CONbits.TSIDL	= 0;//0= Continue module operation in Idle mode
	T1CONbits.TON	= 1;//1 = Starts 16-bit Timer1

	return;
}

void Initialize_TMR2(void)
{
	//TODO - Write TMR2 Initialize
	return;
}

void Initialize_TMR3(void)
{
	//TODO - Write TMR3 Initialize
	return;
}

void Initialize_TMR4(void)
{
	//TODO - Write TMR4 Initialize
	return;
}
