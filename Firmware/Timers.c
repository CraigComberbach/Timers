/**************************************************************************************************
Authours:				Craig Comberbach
Target Hardware:		PIC24F
Chip resources used:	All available Timers
Code assumptions:
Purpose:				Allow access and control over the available timers. This includes handling intialization, temporary disabling/reenabling, interrupt control, and any other functionality

Version History:
v0.3.0	2013-08-29  Craig Comberbach
	Compiler: C30 v3.31	IDE: MPLABx 1.80	Tool: RealICE	Computer: Intel Xeon CPU 3.07 GHz, 6 GB RAM, Windows 7 64 bit Professional SP1
 	Added Change Timer Trigger function to allow the timer to be enabled/disabled on the fly
	Added functionality to allow polling of timers
	Added functionality to allow changing the timer period on the fly
	Timer initialization has been made more generic, it is now done through a single function
	*BUG FIX* Timers now round properly when they are are auto-magically setting the period register
v0.2.0	2013-08-08  Craig Comberbach
	Compiler: C30 v3.31	IDE: MPLABx 1.85	Tool: ICD3	Computer: Intel Core2 Quad CPU 2.40 GHz, 5 GB RAM, Windows 7 64 bit Home Premium SP1
	Prescaler, Postscaler and Period Registers are all handled auto-magically on Timers 1/2/3/4
		-This requires knowledge of the speed of the system clock (FOSC)
		-The code optimizes for a period register that has the finest resolution
v0.1.0	2013-08-08  Craig Comberbach
	Compiler: C30 v3.31	IDE: MPLABx 1.85	Tool: ICD3	Computer: Intel Core2 Quad CPU 2.40 GHz, 5 GB RAM, Windows 7 64 bit Home Premium SP1
	Timers 1-4 initialization and interrupts are implemented for the PIC24F08KL200 chip
		-Timer 3 is broken into two initializations, a gated and a standard function. I hope to combine these in the future
	Interrupts are enabled and the function pointer are only set if the pointer sent is not a null pointer
	Sentinels are setup to check the validity of the arguments sent to the initialize routines
	Added PRx values to initialization, they are set to their default max (I want to handle them auto-magically along with pre/post scalers in the future
v0.0.0	2013-07-20  Craig Comberbach
	Compiler: C30 v3.31	IDE: MPLABx 1.80	Tool: RealICE	Computer: Intel Xeon CPU 3.07 GHz, 6 GB RAM, Windows 7 64 bit Professional SP1
	First version
**************************************************************************************************/
/*************    Header Files    ***************/
#include "Config.h"
#include "Timers.h"

/************* Semantic Versioning***************/
#if TIMERS_MAJOR != 0
	#error "Timers.c has had a change that loses some previously supported functionality"
#elif TIMERS_MINOR != 3
	#error "Timers.c has new features that this code may benefit from"
#elif TIMERS_PATCH != 0
	#error "Timers.c has had a bug fix, you should check to see that we weren't relying on a bug for functionality"
#endif

/************Arbitrary Functionality*************/
/*************   Magic  Numbers   ***************/
#define MIN_PERIOD_NS (1000000000/(FOSC_HZ/2))	//Period of the instruction clock pulse in nanoseconds

/*************    Enumeration     ***************/
/***********State Machine Definitions*************/
/*************  Global Variables  ***************/
void (*TMR1_interruptFunction)(void) = (void *)0;
void (*TMR2_interruptFunction)(void) = (void *)0;
void (*TMR3_interruptFunction)(void) = (void *)0;
void (*TMR4_interruptFunction)(void) = (void *)0;

/*************Function  Prototypes***************/

#if defined __PIC24F08KL200__
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

/************* Device Definitions ***************/
/************* Module Definitions ***************/
/************* Other  Definitions ***************/

int Initialize_Timer(enum TIMERS_AVAILABLE timer, int time, enum TIMER_UNITS units, void (*interruptFunction)(void))
{
	//Find & Update the correct timer
	switch(timer)
	{
		case 0://Timer1
			//Change what the prescale and period register should be
			if(Change_Timer_Time(TIMER1, time, units) == 0)
				return 0;//Time out of range

			#if defined __PIC24F08KL200__
				//Timer1 Period Register
//				PR1			=		//Taken Care of elsewhere

				//Timer1 Control Register
				T1CONbits.TCS	= 0;	//0 = Internal clock (FOSC/2)
//				T1CONbits.TSYNC	=		//Not used because TCS = 0
//				T1CONbits.TCKPS	=		//Taken Care of else where
				T1CONbits.TGATE	= 0;	//0 = Gated time accumulation is disabled
//				T1CONbits.T1ECS	=		//Not valid because TCS = 0
				T1CONbits.TSIDL	= 0;	//0 = Continue module operation in Idle mode
				T1CONbits.TON	= 1;	//1 = Starts 16-bit Timer1

				//Only setup the interrupts if we have a valid function pointer
				if(interruptFunction)//Check for null pointer
				{
					TMR1_interruptFunction = interruptFunction;//Setup the function to call in the interrupt routine
					IEC0bits.T1IE = 1;//Enable the interrupt
				}
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				return 0;//Timer1 does not exist on this chip, as such, this function call has failed
			#else
				#warning "Timer1 is not setup for this chip"
			#endif

			//Success
			return 1;
		case 1://Timer2
			//Determine what the prescale and period register should be
			if(Change_Timer_Time(TIMER2, time, units) == 0)
				return 0;//Time out of range

			#if defined __PIC24F08KL200__
				//Timer2 Period Register
//				PR2					=		//Taken Care of elsewhere

				//Timer2 Control Register
//				T2CONbits.T2OUTPS	=		//Taken Care of elsewhere
//				T2CONbits.T2CKPS	=		//Taken Care of elsewhere
				T2CONbits.TON		= 1;	//1 = Timer2 is on

				//Only setup the interrupts if we have a valid function pointer
				if(interruptFunction)//Check for null pointer
				{
					TMR2_interruptFunction = interruptFunction;//Setup the function to call in the interrupt routine
					IEC0bits.T2IE = 1;//Enable the interrupt
				}
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				return 0;//Timer2 does not exist on this chip, as such, this function call has failed
			#else
				#warning "Timer2 is not setup for this chip"
			#endif

			//Success
			return 1;
		case 2://Timer3
			//Determine Prescaler and Period Register
			if(Change_Timer_Time(TIMER3, time, units) == 0)
				return 0;//Time out of range

			#if defined __PIC24F08KL200__
				//Timer3 Gate Control Register
				//Note it is recommended in the spec sheet to intialize this register before T3CON
				T3GCONbits.TMR3GE		= 0;	//Default: 0 = Timer counts regardless of the Timer3 gate function
				T3GCONbits.T3GPOL		= 0;	//Default: 0 = Timer gate is active-low (Timer3 counts when the gate is low)
				T3GCONbits.T3GTM		= 0;	//Default: 0 = Timer Gate Toggle mode is disabled and toggle flip-flop is cleared
				T3GCONbits.T3GSPM		= 0;	//Default: 0 = Timer Gate Single Pulse mode is disabled
				T3GCONbits.T3GGO		= 0;	//Default: 0 = Timer gate single pulse acquisition has completed or has not been started
//				T3GCONbits.T3GVAL				//Timer Gate Current State bit
				T3GCONbits.T3GSS		= 0;	//Timer Gate Source Select bits (0 = T3G input pin, 1 = TMR2 to match PR2 output, 2 = Comparator 1 output, 3 = Comparator 2 output)

				//Timer3 Control Register
				T3CONbits.TMR3CS		= 1;	//Clock Source Select bits, 1 = Instruction Clock (Fosc/2)
//				T3CONbits.T3CKPS		=		//Taken Care of elsewhere
				T3CONbits.T3OSCEN		= 1;	//SOSC (Secondary Oscillator) is used as a clock source
//				T3CONbits.NOT_T3SYNC	=		//When TMR3CS = 0x: This bit is ignored; Timer3 uses the internal clock.
				T3CONbits.TMR3ON		= 1;	//1 = Enables Timer

				//Only setup the interrupts if we have a valid function pointer
				if(interruptFunction)//Check for null pointer
				{
					TMR3_interruptFunction = interruptFunction;//Setup the function to call in the interrupt routine
					IEC0bits.T3IE = 1;//Enable the interrupt
				}
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				return 0;//Timer3 does not exist on this chip, as such, this function call has failed
			#else
				#warning "Timer3 is not setup for this chip"
			#endif

			//Success
			return 1;
		case 3://Timer4
			#if defined __PIC24F08KL200__
				return 0;//Timer4 does not exist on this chip, as such, this function call has failed
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				//Determine what the prescale and period register should be
				if(Change_Timer_Time(TIMER4, time, units) == 0)
					return 0;//Time out of range

				//Timer4 Period Register
//				PR4					=		//Taken Care of elsewhere

				//Timer4 Control Register
//				T4CONbits.T4OUTPS	=		//Taken Care of elsewhere
//				T4CONbits.T4CKPS	=		//Taken Care of elsewhere
				T4CONbits.TON		= 1;	//1 = Timer4 is on

				//Only setup the interrupts if we have a valid function pointer
				if(interruptFunction)//Check for null pointer
				{
					TMR4_interruptFunction = interruptFunction;//Setup the function to call in the interrupt routine
					IEC1bits.T1IE = 1;//Enable the interrupt
				}
			#else
				#warning "Timer4 is not setup for this chip"
			#endif

			//Success
			return 1;
		default:
			return 0;//Timer is out of range
	}

	//How did I get here?
	return 0;
}

int Initialize_TMR3_As_Gated_Timer(int time, enum TIMER_UNITS units, int gateSource, int mode, int triggerPolarity, void (*interruptFunction)(void))
{
	//Range checking
	if((gateSource < 0) || (gateSource > 3))
		return 0;//Out of range
	if((mode < 0) || (mode > 1))
		return 0;//Out of range
	if((triggerPolarity < 0) || (triggerPolarity > 1))
		return 0;//Out of range

	//Determine Prescaler and Period Register
	if(Change_Timer_Time(TIMER3, time, units) == 0)
		return 0;//Time out of range

	#if defined __PIC24F08KL200__
		//Timer3 Gate Control Register
		//Note it is recommended in the spec sheet to intialize this register before T3CON
		T3GCONbits.TMR3GE		= 1;				//1 = Timer counting is controlled by the Timer3 gate function
		T3GCONbits.T3GPOL		= triggerPolarity;	//Gate Polarity bit (0 = Active Low, 1 = Active High)
		T3GCONbits.T3GTM		= 1;				//1 = Timer Gate Toggle mode is enabled
		T3GCONbits.T3GSPM		= mode;				//Gate Toggle Mode (0 = Timer Gate Single Pulse mode is disabled, 1 = Timer Gate Single Pulse mode is enabled and is controlling Timer3 gate)
		T3GCONbits.T3GGO		= 1;				//1 = Timer Gate Single Pulse mode is enabled and is controlling Timer3 gate
//		T3GCONbits.T3GVAL							//Timer Gate Current State bit
		T3GCONbits.T3GSS		= gateSource;		//Timer Gate Source Select bits (0 = T3G input pin, 1 = TMR2 to match PR2 output, 2 = Comparator 1 output, 3 = Comparator 2 output)

		//Timer3 Control Register
		T3CONbits.TMR3CS		= 1;				//Clock Source Select bits, 1 = Instruction Clock (Fosc/2)
//		T3CONbits.T3CKPS		=					//Taken Care of elsewhere
		T3CONbits.T3OSCEN		= 1;				//SOSC (Secondary Oscillator) is used as a clock source
//		T3CONbits.NOT_T3SYNC	=					//When TMR3CS = 0x: This bit is ignored; Timer3 uses the internal clock.
		T3CONbits.TMR3ON		= 1;				//1 = Enables Timer

		//Only setup the interrupts if we have a valid function pointer
		if(interruptFunction)//Check for null pointer
		{
			TMR3_interruptFunction = interruptFunction;//Setup the function to call in the interrupt routine
			IEC0bits.T3IE = 1;//Enable the interrupt
		}
	#elif defined PLACE_MICROCHIP_PART_NAME_HERE
		return 0;//Timer3 does not exist on this chip, as such, this function call has failed
	#else
		#warning "Timer3 is not setup for this chip"
	#endif

	//Success
	return 1;
}

int Change_Timer_Trigger(enum TIMERS_AVAILABLE timer, int newState)
{
	//Range check
	if((timer < 0 ) || (timer >= NUMBER_OF_AVAILABLE_TIMERS))
		return 0;//Out of range
	if((newState != TIMER_ON) && (newState != TIMER_OFF))
		return 0;//Out of range

	switch(timer)
	{
		case 0:
			T1CONbits.TON = newState;
			break;
		case 1:
			T2CONbits.TON = newState;
			break;
		case 2:
			T3CONbits.TMR3ON = newState;
			break;
		case 3:
			#if defined __PIC24F08KL200__
				return 0;//Timer4 does not exist on this chip, as such, this function call has failed
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				T4CONbits.TON = newState;
			#else
				#warning "Timer4 is not setup for this chip"
			#endif
			break;
		default:
			return 0;//How did we get here?
	}

	//Success
	return 1;
}

int Current_Timer(enum TIMERS_AVAILABLE timer, enum TIMER_UNITS units)
{
	long time;

	//Range check
	if((timer < 0 ) || (timer >= NUMBER_OF_AVAILABLE_TIMERS))
		return 0;//Out of range

	//Determine which timer to read
	switch(timer)
	{
		case 0:
			//Apply prescalar
			switch(T1CONbits.TCKPS)
			{
				case 0://1:1
					time = TMR1 * 1 * MIN_PERIOD_NS;
					break;
				case 1://1:8
					time = TMR1 * 8 * MIN_PERIOD_NS;
					break;
				case 2://1:64
					time = TMR1 * 64 * MIN_PERIOD_NS;
					break;
				case 3://1:256
					time = TMR1 * 256 * MIN_PERIOD_NS;
					break;
			}

			//Apply units modifier and return finished value
			switch(units)
			{
				case SECONDS:
					time /= 1000000000;
				case MILLI_SECONDS:
					time /= 1000000;
				case MICRO_SECONDS:
					time /= 1000;
				case NANO_SECONDS:
					time /= 1;
				case TICKS:
					time = time;
					break;
				default:
					return 0;//Invalid units
			}

			//Return the adjusted time in the requested time units
			return (int)time;
		case 1:
			//Apply prescalar and postscalar
			switch(T2CONbits.T2CKPS)
			{
				case 0://1:1
					time = TMR2 * 1 * MIN_PERIOD_NS * (T2CONbits.T2OUTPS + 1);
					break;
				case 1://1:4
					time = TMR2 * 4 * MIN_PERIOD_NS * (T2CONbits.T2OUTPS + 1);
					break;
				case 2://1:16
					time = TMR2 * 16 * MIN_PERIOD_NS * (T2CONbits.T2OUTPS + 1);
					break;
			}			

			//Apply units modifier and return finished value
			switch(units)
			{
				case SECONDS:
					time /= 1000000000;
				case MILLI_SECONDS:
					time /= 1000000;
				case MICRO_SECONDS:
					time /= 1000;
				case NANO_SECONDS:
					time /= 1;
				case TICKS:
					time = time;
					break;
				default:
					return 0;//Invalid units
			}

			//Return the adjusted time in the requested time units
			return (int)time;
		case 2:
			//Apply prescalar
			switch(T3CONbits.TCKPS)
			{
				case 0://1:1
					time = TMR3 * 1 * MIN_PERIOD_NS;
					break;
				case 1://1:2
					time = TMR3 * 2 * MIN_PERIOD_NS;
					break;
				case 2://1:4
					time = TMR3 * 4 * MIN_PERIOD_NS;
					break;
				case 3://1:8
					time = TMR3 * 8 * MIN_PERIOD_NS;
					break;
			}

			//Apply units modifier and return finished value
			switch(units)
			{
				case SECONDS:
					time /= 1000000000;
				case MILLI_SECONDS:
					time /= 1000000;
				case MICRO_SECONDS:
					time /= 1000;
				case NANO_SECONDS:
					time /= 1;
				case TICKS:
					time = time;
					break;
				default:
					return 0;//Invalid units
			}

			//Return the adjusted time in the requested time units
			return (int)time;
		case 3:
			#if defined __PIC24F08KL200__
				return 0;//Timer4 does not exist on this chip, as such, this function call has failed
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				//Apply prescalar and postscalar
				switch(T4CONbits.T4CKPS)
				{
					case 0://1:1
						time = TMR4 * 1 * MIN_PERIOD_NS * (T4CONbits.T4OUTPS + 1);
						break;
					case 1://1:4
						time = TMR4 * 4 * MIN_PERIOD_NS * (T4CONbits.T4OUTPS + 1);
						break;
					case 2://1:16
						time = TMR4 * 16 * MIN_PERIOD_NS * (T4CONbits.T4OUTPS + 1);
						break;
				}

				//Apply units modifier and return finished value
				switch(units)
				{
					case SECONDS:
						time /= 1000000000;
					case MILLI_SECONDS:
						time /= 1000000;
					case MICRO_SECONDS:
						time /= 1000;
					case NANO_SECONDS:
						time /= 1;
					case TICKS:
						time;
						break;
					default:
						return 0;//Invalid units
				}

				//Return the adjusted time in the requested time units
				return (int)time;
			#else
				#warning "Timer4 is not setup for this chip"
			#endif
		default:
			return 0;//How did we get here?
	}

	//No seriously, how did we get here!
	return 0;
}

int Change_Timer_Time(enum TIMERS_AVAILABLE timer, int time, enum TIMER_UNITS units)
{
	unsigned long targetTime;
	unsigned long periodRegister;
	unsigned long prescale;
	unsigned long postscale;

	//Determine the target time in nS
	switch(units)
	{
		case SECONDS:
			targetTime = time * 1000000000;//Change to the appropriate resolution
			break;
		case MILLI_SECONDS:
			targetTime = time * 1000000;//Change to the appropriate resolution
			break;
		case MICRO_SECONDS:
			targetTime = time * 1000;//Change to the appropriate resolution
			break;
		case NANO_SECONDS:
			targetTime = time * 1;//Change to the appropriate resolution
			break;
		case TICKS:
			targetTime = time;//Change to the appropriate resolution
			break;
		default:
			return 0;//Invalid units
	}

	//Determine & Set the period, prescalar and postscalar of the timer
	switch(timer)
	{
		case 0://Timer 1
			//Determine Prescaler and Period Register - Attempt to minimize the prescalar to retain resolution
			prescale = targetTime;		//Assign time to beat
			prescale /= 0xFFFF;			//Divide by a maxed out period register
			prescale /= MIN_PERIOD_NS;	//Divide by the minimum period
			if(prescale == 0)
			{
				prescale = 0;//1:1
				periodRegister = targetTime;
				periodRegister /= 1 * MIN_PERIOD_NS;//Divide by prescaler and the miniumum period
			}
			else if((prescale > 0) && (prescale <= 8))
			{
				prescale = 1;//1:8
				periodRegister = targetTime;
				periodRegister /= 8 * MIN_PERIOD_NS;//Divide by prescaler and the miniumum period
			}
			else if((prescale > 8) && (prescale <= 64))
			{
				prescale = 2;//1:64
				periodRegister = targetTime;
				periodRegister /= 64 * MIN_PERIOD_NS;//Divide by prescaler and the miniumum period
			}
			else if((prescale > 64) && (prescale <= 256))
			{
				prescale = 3;//1:256
				periodRegister = targetTime;
				periodRegister /= 256 * MIN_PERIOD_NS;//Divide by prescaler and the miniumum period
			}
			else
				return 0;//Out of range with a maxed out prescalar AND period register

			//Make it official
			PR1 = periodRegister;		//The value to trigger an interrupt at
			T1CONbits.TCKPS	= prescale;	//Timer1 Input Clock Prescale Select bits (0 = 1:1, 1 = 1:8, 2 = 1:64, 3 = 1:256)
			return 1;//Success
		case 1://Timer 2
			//Determine postscaler and Period Register - Attempt to minimize the postscalar to retain resolution
			postscale = targetTime;		//Assign time to beat
			postscale /= 0xFF;			//Divide by a maxed out period register
			postscale /= 16;			//Divide by a maxed out prescaler
			postscale /= MIN_PERIOD_NS;	//Divide by the minimum period
			postscale++;				//Add one to get the correct post scalar

			//Range check
			if(postscale > 16)
				return 0;//Out of range with a maxed out postscalar AND prescalar AND period register

			//Determine Prescaler and Period Register - Attempt to minimize the prescalar to retain resolution
			prescale = targetTime;		//Assign time to beat
			prescale /= 0xFF;			//Divide by a maxed out period register
			prescale /= MIN_PERIOD_NS;	//Divide by the minimum period
			prescale /= postscale;		//Divide by already determined postscale value
			if(prescale == 0)
			{
				prescale = 0;//1:1
				periodRegister = targetTime;
				periodRegister /= 1 * MIN_PERIOD_NS * postscale;//Divide by prescaler, postscaler, and the miniumum period
			}
			else if((prescale > 0) && (prescale <= 4))
			{
				prescale = 1;//1:4
				periodRegister = targetTime;
				periodRegister /= 4 * MIN_PERIOD_NS * postscale;//Divide by prescaler, postscaler, and the miniumum period
			}
			else if((prescale > 4) && (prescale <= 16))
			{
				prescale = 2;//1:16
				periodRegister = targetTime;
				periodRegister /= 16 * MIN_PERIOD_NS * postscale;//Divide by prescaler, postscaler, and the miniumum period
			}
			else
				return 0;//Something went wrong, we should be in range...?

			//Make it official
			PR2					= periodRegister;	//The value to trigger an interrupt at
			T2CONbits.T2OUTPS	= postscale;		//Timer2 Output Postscale Select bits (0 = 1:1, 1 = 1:2, 2 = 1:3,... 15 = 1:16)
			T2CONbits.T2CKPS	= prescale;			//Timer2 Output Prescale Select bits (0 = 1, 1 = 4, 2 = 16, 3 = undefined)

			return 1;//Success
		case 2://Timer 3
			//Determine Prescaler - Attempt to minimize the prescalar to retain resolution
			Change_Timer_Time(TIMER3, time, units);
			prescale = targetTime;		//Assign time to beat
			prescale /= MIN_PERIOD_NS;	//Divide by the minimum period
			if(prescale == 0)
				prescale = 0;//1:1
			else if((prescale > 0) && (prescale <= 2))
				prescale = 1;//1:2
			else if((prescale > 2) && (prescale <= 4))
				prescale = 2;//1:4
			else if((prescale > 4) && (prescale <= 8))
				prescale = 3;//1:8
			else
				return 0;//Out of range with a maxed out prescalar AND period register

			//Make it official
			T3CONbits.T3CKPS = prescale;	//Timer3 Input Clock Prescale Select bits (0 = 1:1, 1 = 1:2, 2 = 1:4, 3 = 1:8)

			return 1;//Success
		case 3://Timer 4
			#if defined __PIC24F08KL200__
				return 0;//Timer4 does not exist on this chip, as such, this function call has failed
			#elif defined PLACE_MICROCHIP_PART_NAME_HERE
				//Determine postscaler and Period Register - Attempt to minimize the postscalar to retain resolution
				postscale = targetTime;		//Assign time to beat
				postscale /= 0xFF;			//Divide by a maxed out period register
				postscale /= 16;			//Divide by a maxed out prescaler
				postscale /= MIN_PERIOD_NS;	//Divide by the minimum period
				postscale++;				//Add one to get the correct post scalar

				//Range check
				if(postscale > 16)
					return 0;//Out of range with a maxed out postscalar AND prescalar AND period register

				//Determine Prescaler and Period Register - Attempt to minimize the prescalar to retain resolution
				prescale = targetTime;		//Assign time to beat
				prescale /= 0xFF;			//Divide by a maxed out period register
				prescale /= MIN_PERIOD_NS;	//Divide by the minimum period
				prescale /= postscale;		//Divide by already determined postscale value
				if(prescale == 0)
				{
					prescale = 0;//1:1
					periodRegister = targetTime;
					periodRegister /= 1 * MIN_PERIOD_NS * postscale;//Divide by prescaler, postscaler, and the miniumum period
				}
				else if((prescale > 0) && (prescale <= 4))
				{
					prescale = 1;//1:4
					periodRegister = targetTime;
					periodRegister /= 4 * MIN_PERIOD_NS * postscale;//Divide by prescaler, postscaler, and the miniumum period
				}
				else if((prescale > 4) && (prescale <= 16))
				{
					prescale = 2;//1:16
					periodRegister = targetTime;
					periodRegister /= 16 * MIN_PERIOD_NS * postscale;//Divide by prescaler, postscaler, and the miniumum period
				}
				else
					return 0;//Something went wrong, we should be in range...?

				//Make it official
				PR4					= periodRegister;	//The value to trigger an interrupt at
				T4CONbits.T4OUTPS	= postscale;		//Timer4 Output Postscale Select bits (0 = 1:1, 1 = 1:2, 2 = 1:3,... 15 = 1:16)
				T4CONbits.T4CKPS	= prescale;			//Timer4 Clock Prescale Select bits (0 = 1:1, 1 = 1:4, 2 = 1:16, 3 = Undefined)

				return 1;//Success
			#else
				#warning "Timer4 is not setup for this chip"
			#endif
		default:
			return 0;//Invalid Timer
	}

	//How did we get here?
	return 0;
}

void __attribute__ ((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	IFS0bits.T1IF = 0;
	TMR1_interruptFunction();//Run the associated function

	//Return to where we left off
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T2Interrupt(void)
{
	IFS0bits.T2IF = 0;
	TMR2_interruptFunction();//Run the associated function

	//Return to where we left off
	return;
}

void __attribute__ ((interrupt, no_auto_psv)) _T3Interrupt(void)
{
	IFS0bits.T3IF = 0;
	TMR3_interruptFunction();//Run the associated function

	//Return to where we left off
	return;
}

#if defined __PIC24F08KL200__
	//Timer 4 does not exist
#elif defined PLACE_MICROCHIP_PART_NAME_HERE
	void __attribute__ ((interrupt, no_auto_psv)) _T4Interrupt(void)
	{

		IFS0bits.T4IF = 0;
		TMR4_interruptFunction();//Run the associated function

		//Return to where we left off
		return;
	}
#endif
