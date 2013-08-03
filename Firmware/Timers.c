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
#include "Timers.h"

/************* Semantic Versioning***************/
/************Arbitrary Functionality*************/
/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
/***********State Machine Definitions*************/
/*************  Global Variables  ***************/
void (*TMR1_interruptFunction)(void) = (void *)0;
void (*TMR2_interruptFunction)(void) = (void *)0;
void (*TMR3_interruptFunction)(void) = (void *)0;
void (*TMR4_interruptFunction)(void) = (void *)0;

/*************Function  Prototypes***************/
void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void);
void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void);
void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void);
void __attribute__ ((interrupt, no_auto_psv)) _T4Interrupt(void);

/************* Device Definitions ***************/
/************* Module Definitions ***************/
/************* Other  Definitions ***************/

int Initialize_TMR1(int prescale, void (*interruptFunction)(void))
{
	#if defined __PIC24F08KL200__
		//Timer1 Control Register
		T1CONbits.TCS	= 0;		//0 = Internal clock (FOSC/2)
//		T1CONbits.TSYNC	=			//Not used because TCS = 0
		T1CONbits.TCKPS	= prescale;	//Timer1 Input Clock Prescale Select bits (0 = 1:1, 1 = 1:8, 2 = 1:64, 3 = 1:256)
		T1CONbits.TGATE	= 0;		//0 = Gated time accumulation is disabled
//		T1CONbits.T1ECS	=			//Not valid because TCS = 0
		T1CONbits.TSIDL	= 0;		//0 = Continue module operation in Idle mode
		T1CONbits.TON	= 1;		//1 = Starts 16-bit Timer1
	#elif defined PLACE_MICROCHIP_PART_NAME_HERE
		return 0;//Timer2 does not exist on this chip, as such, this function call has failed
	#else
		#warning "This timer1 is not setup for this chip"
	#endif

	//Setup the function to call in the interrupt routine
	TMR1_interruptFunction = interruptFunction;//It is valid

	//Success
	return 1;
}

int Initialize_TMR2(int prescale, int postscale, void (*interruptFunction)(void))
{
	#if defined __PIC24F08KL200__
		//Timer2 Control Register
		T2CONbits.T2OUTPS	= postscale;//Timer2 Output Postscale Select bits (0 = 1:1, 1 = 1:2, 2 = 1:3,... 15 = 1:16)
		T2CONbits.T2CKPS	= prescale;	//Timer2 Clock Prescale Select bits (0 = 1:1, 1 = 1:4, 2 = 1:16, 3 = Undefined)
		T2CONbits.TON		= 1;		//1 = Timer2 is on
	#elif defined PLACE_MICROCHIP_PART_NAME_HERE
		return 0;//Timer2 does not exist on this chip, as such, this function call has failed
	#else
		#warning "This timer1 is not setup for this chip"
	#endif

	//Setup the function to call in the interrupt routine
	TMR2_interruptFunction = interruptFunction;

	//Success
	return 1;
}

int Initialize_TMR3(void (*interruptFunction)(void))
{
	#if defined __PIC24F08KL200__
	#elif defined PLACE_MICROCHIP_PART_NAME_HERE
		return 0;//Timer3 does not exist on this chip, as such, this function call has failed
	#else
		#warning "This timer1 is not setup for this chip"
	#endif

	//Setup the function to call in the interrupt routine
	TMR3_interruptFunction = interruptFunction;

	//Success
	return 1;
}

int Initialize_TMR4(int prescale, int postscale, void (*interruptFunction)(void))
{
	#if defined __PIC24F08KL200__
		return 0;//Timer4 does not exist on this chip, as such, this function call has failed
	#elif define PLACE_MICROCHIP_PART_NAME_HERE
		//Timer4 Control Register
		T4CONbits.T4OUTPS	= postscale;//Timer4 Output Postscale Select bits (0 = 1:1, 1 = 1:2, 2 = 1:3,... 15 = 1:16)
		T4CONbits.T4CKPS	= prescale;	//Timer4 Clock Prescale Select bits (0 = 1:1, 1 = 1:4, 2 = 1:16, 3 = Undefined)
		T4CONbits.TON		= 1;		//1 = Timer4 is on
	#else
		#warning "This timer1 is not setup for this chip"
	#endif

	//Setup the function to call in the interrupt routine
	TMR4_interruptFunction = interruptFunction;

	//Success
	return 1;
}

/*
 TODO - Create functions to Set PR1/2/3/4
 TODO - Create functions to turn On/Off each timer
 TODO - Add to each timer the control bits to enable interrupts if they are nessecary
 */

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	(*TMR1_interruptFunction)();//Run the associated function

	//Return to where we left off
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	(*TMR2_interruptFunction)();//Run the associated function

	//Return to where we left off
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void)
{
	(*TMR3_interruptFunction)();//Run the associated function

	//Return to where we left off
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T4Interrupt(void)
{
	(*TMR4_interruptFunction)();//Run the associated function

	//Return to where we left off
	return;
}
