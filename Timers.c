/**************************************************************************************************
Version History:
v1.0.0	2023-09-11	Craig Comberbach	Compiler: XC16 v2.00
 * 
v0.3.0	2013-08-29  Craig Comberbach	Compiler: C30 v3.31
 * Added Change Timer Trigger function to allow the timer to be enabled/disabled on the fly
 * Added functionality to allow polling of timers
 * Added functionality to allow changing the timer period on the fly
 * Timer initialization has been made more generic, it is now done through a single function
 *BUG FIX* Timers now round properly when they are auto-magically setting the period register
v0.2.0	2013-08-08  Craig Comberbach	Compiler: C30 v3.31
 * Prescaler, Postscaler and Period Registers are all handled auto-magically on Timers 1/2/3/4
 * 	-This requires knowledge of the speed of the system clock (FOSC)
 * 	-The code optimizes for a period register that has the finest resolution
v0.1.0	2013-08-08  Craig Comberbach	Compiler: C30
 * Timers 1-4 initialization and interrupts are implemented for the PIC24F08KL200 chip
 * 	-Timer 3 is broken into two initializations, a gated and a standard function. I hope to combine these in the future
 * Interrupts are enabled and the function pointer are only set if the pointer sent is not a null pointer
 * Sentinels are setup to check the validity of the arguments sent to the initialize routines
 * Added PRx values to initialization, they are set to their default max (I want to handle them auto-magically along with pre/post scalers in the future
v0.0.0	2013-07-20  Craig Comberbach	Compiler: C30 v3.31
 * First version
**************************************************************************************************/
/*************    Header Files    ***************/
#include <stdint.h>
#include "Config.h"
#include "Timers.h"

/*************Semantic  Versioning***************/
#if TIMERS_MAJOR != 1
	#error "Timers.c has had a change that loses some previously supported functionality"
#elif TIMERS_MINOR != 0
	#error "Timers.c has new features that this code may benefit from"
#elif TIMERS_PATCH != 0
	#error "Timers.c has had a bug fix, you should check to see that we weren't relying on a bug for functionality"
#endif

/*************   Magic  Numbers   ***************/
#define NULL_POINTER	(void*)0

/*************    Enumeration     ***************/
enum TIMER_STATE
{
	STOPPED = 0,
	RUNNING = 1
};

/***********  Structure Definitions  ************/
/***********State Machine Definitions************/
/*************  Global Variables  ***************/
static struct timer_definition
{
	enum AVAILABLE_TIMERS timerUsed;
	uint32_t period;
	enum TIMER_UNITS units;
	void (*interruptFunction)(void);
} self[NUMBER_OF_TIMERS];

const uint16_t prescaleOptions[] = {1,8,64,256};

/*************Function  Prototypes***************/
uint16_t Determine_Prescaler(uint16_t period, enum TIMER_UNITS units);
uint16_t Determine_Period_Register(uint16_t prescaler, uint16_t period, enum TIMER_UNITS units);
void Change_Timer_State(enum TIMER_DEFINITIONS timer, enum TIMER_STATE state);

#if defined __PIC24F08KL200__
	void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void);
	//Timer 4 does not exist
#elif defined __PIC24F16KA101__
	void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void);
	//Timer 4 does not exist
#elif defined PLACE_MICROCHIP_PART_NAME_HERE
	void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void);
	void __attribute__ ((interrupt, no_auto_psv)) _T4Interrupt(void);
#endif
	
/************* Main Body Of Code  ***************/
void Initialize_Timers(void)
{
	uint8_t timer;
	
	for(timer = 0; timer < NUMBER_OF_TIMERS; timer++)
	{
		self[timer].interruptFunction = NULL_POINTER;
		self[timer].period = 0;
		self[timer].timerUsed = 0;
		self[timer].units = 0;
	}

	return;
}
	
void Setup_Timer(enum TIMER_DEFINITIONS timerName, enum AVAILABLE_TIMERS timerUsed, uint32_t period, enum TIMER_UNITS units, void (*interruptFunction)(void))
{
	if((timerName < NUMBER_OF_TIMERS) && (timerUsed < NUMBER_OF_PHYSICAL_TIMERS))
	{
		self[timerName].timerUsed = timerUsed;
		self[timerName].period = period;
		self[timerName].units = units;
		self[timerName].interruptFunction = interruptFunction;
		
		switch(timerUsed)
		{
			case TIMER1:
				if(interruptFunction != NULL_POINTER)
				{
					IEC0bits.T1IE = 1;
				}
				else
				{
					IEC0bits.T1IE = 0;
				}
				
				T1CONbits.TON = 0;
				T1CONbits.TSIDL = 0;
				T1CONbits.TGATE = 0;
				T1CONbits.TSYNC = 0;
				T1CONbits.TCKPS = Determine_Prescaler(period, units);
				T1CONbits.TCS = 0;
				
				PR1 = Determine_Period_Register(T1CONbits.TCKPS, period, units);

				break;
			case TIMER2:
				if(interruptFunction != NULL_POINTER)
				{
					IEC0bits.T2IE = 1;
				}
				else
				{
					IEC0bits.T2IE = 0;
				}
				
				T2CONbits.TON = 0;
				T2CONbits.TSIDL = 0;
				T2CONbits.TGATE = 0;
				T2CONbits.T32 = 0;
				T2CONbits.TCKPS = Determine_Prescaler(period, units);
				T2CONbits.TCS = 0;
				
				PR2 = Determine_Period_Register(T2CONbits.TCKPS, period, units);
					
				break;
			case TIMER3:
				if(interruptFunction != NULL_POINTER)
				{
					IEC0bits.T3IE = 1;
				}
				else
				{
					IEC0bits.T3IE = 0;
				}
				
				T3CONbits.TON = 0;
				T3CONbits.TSIDL = 0;
				T3CONbits.TGATE = 0;
				T3CONbits.TCKPS = Determine_Prescaler(period, units);
				T3CONbits.TCS = 0;
				
				PR3 = Determine_Period_Register(T3CONbits.TCKPS, period, units);
				
				break;
			default:
				break;
		}
	}
	
	return;
}

uint16_t Determine_Prescaler(uint16_t period, enum TIMER_UNITS units)
{
	uint32_t periodTimer = (period % 1000) * FCY_Hz;
	int16_t prescaler;

	switch(units)
	{
		case SECONDS:
			break;
		case MILLI_SECONDS:
			periodTimer /= 1000;
			break;
		case MICRO_SECONDS:
			periodTimer /= 1000000;
			break;
		case NANO_SECONDS:
			periodTimer /= 1000000000;
			break;
		case TICKS:
			break;
		default:
			return 0;//Invalid units
	}
	
	for(prescaler = 0; prescaler < sizeof(prescaleOptions); prescaler++)
	{
		if((periodTimer/prescaleOptions[prescaler]) < UINT16_MAX)
		{
			return prescaler;
		}
	}
	
	return prescaler - 1;
}

uint16_t Determine_Period_Register(uint16_t prescaler, uint16_t period, enum TIMER_UNITS units)
{
	uint32_t periodRegister = (period % 1000) * FCY_Hz;

	switch(units)
	{
		case SECONDS:
			break;
		case MILLI_SECONDS:
			periodRegister /= 1000;
			break;
		case MICRO_SECONDS:
			periodRegister /= 1000000;
			break;
		case NANO_SECONDS:
			periodRegister /= 1000000000;
			break;
		case TICKS:
			break;
		default:
			return 0;//Invalid units
	}
	periodRegister += prescaleOptions[prescaler] / 2;	//Rounding
	periodRegister /= prescaleOptions[prescaler];

	return (uint16_t) periodRegister;
}

void Change_Timer_State(enum TIMER_DEFINITIONS timer, enum TIMER_STATE state)
{
	switch(self[timer].timerUsed)
	{
		case TIMER1:
			T1CONbits.TON = state;
			break;
		case TIMER2:
			T2CONbits.TON = state;
			break;
		case TIMER3:
			T3CONbits.TON = state;
			break;
		default:
			break;
	}
}

void Timer_Start(enum TIMER_DEFINITIONS timerName)
{
	Change_Timer_State(timerName, RUNNING);
	return;
}

void Timer_Pause(enum TIMER_DEFINITIONS timerName)
{
	Change_Timer_State(timerName, STOPPED);
	return;
}

void Timer_End(enum TIMER_DEFINITIONS timerName)
{
	Setup_Timer(0, timerName, 0, 0, NULL_POINTER);
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	TMR1 = 0;
	IFS0bits.T1IF = 0;
	self[TIMER1].interruptFunction();

	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	TMR2 = 0;
	IFS0bits.T2IF = 0;
	self[TIMER2].interruptFunction();
	
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void)
{
	TMR3 = 0;
	IFS0bits.T3IF = 0;
	self[TIMER3].interruptFunction();

	return;
}
