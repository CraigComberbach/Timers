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

int Initialize_TMR3_As_Gated_Timer(int prescale, void (*interruptFunction)(void))
{
	#if defined __PIC24F08KL200__
		//Timer3 Gate Control Register
		//Note it is recommended in the spec sheet to intialize this register before T3CON
		T3GCONbits.TMR3GE		= 0;	//Default: If TMR3ON = 0, this bit is enabled
		T3GCONbits.T3GPOL		= 0;	//Default: 0 = Timer gate is active-low (Timer3 counts when the gate is low)
		T3GCONbits.T3GTM		= 0;	//Default: 0 = Timer Gate Toggle mode is disabled and toggle flip-flop is cleared
		T3GCONbits.T3GSPM		= 0;	//Default: 0 = Timer Gate Single Pulse mode is disabled
		T3GCONbits.T3GGO		= 0;	//Default: 0 = Timer gate single pulse acquisition has completed or has not been started
//		T3GCONbits.T3GVAL				//Timer Gate Current State bit
		T3GCONbits.T3GSS		= 0;	//Default: Timer Gate Source Select bits (0 = T3G input pin, 1 = TMR2 to match PR2 output, 2 = Comparator 1 output, 3 = Comparator 2 output)

		//Timer3 Control Register
		T3CONbits.TMR3CS		= 1;		//Clock Source Select bits, 1 = Instruction Clock (Fosc/2)
		T3CONbits.T3CKPS		= prescale;	//Timer3 Input Clock Prescale Select bits (0 = 1:1, 1 = 1:2, 2 = 1:4, 3 = 1:8)
		T3CONbits.T3OSCEN		= 1;		//SOSC (Secondary Oscillator) is used as a clock source
//		T3CONbits.NOT_T3SYNC	=			//When TMR3CS = 0x: This bit is ignored; Timer3 uses the internal clock.
		T3CONbits.TMR3ON		= 1;		//1 = Enables Timer
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
