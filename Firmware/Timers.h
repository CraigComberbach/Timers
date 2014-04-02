#ifndef TIMERS_H
#define	TIMERS_H

/************* Semantic Versioning***************/
#define TIMERS_LIBRARY

/*************   Magic  Numbers   ***************/
#define NO_TIMER_INTERRUPT	(void*)0
#define TIMER_ON	1
#define TIMER_OFF	0

/*************    Enumeration     ***************/
enum TIMERS_AVAILABLE
{
	#if defined __PIC24F08KL200__
		TIMER1,
		TIMER2,
		TIMER3,
	#elif defined PLACE_MICROCHIP_PART_NAME_HERE
		TIMER1,
		TIMER2,
		TIMER3,
		TIMER4,
	#else
		#warning "This chip is not setup for timers yet"
	#endif
	NUMBER_OF_AVAILABLE_TIMERS
};

enum TIMER_UNITS
{
	SECONDS,
	MILLI_SECONDS,
	MICRO_SECONDS,
	NANO_SECONDS,
	TICKS
};

/***********  Structure Definitions  ************/
struct TIMER_DEFINITION
{
	enum TIMERS_AVAILABLE timer;
	char resolution;
	char numberOfPrescalers;
	int prescaler[4];//Unused prescalers need to be non-zero
	char numberOfPostscalers;
	int postscaler[16];//Unused postscalers need to be non-zero
};

/***********State Machine Definitions************/
/*************Function  Prototypes***************/
/**
 * Initializes the specified timer to have a set period
 * @param timer The target timer, use the enum TIMERS_AVAILABLE
 * @param time The length of time it takes the timer to expire
 * @param units The units to use (S, mS, uS, nS). Use the enum TIMER_UNITS to correctly specify
 * @param interruptFunction The function that will be called when the timer expires, it should be a function pointer that has the format of "void Some_Function(void)"\
 * Sending a null pointer "(void *)0" is acceptable, this would be done if you did not want a function to be called during the interrupt
 * @return 1 = everything was verified and the timer has been properly initialized\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Initialize_Timer(enum TIMERS_AVAILABLE timer, int time, enum TIMER_UNITS units, void (*interruptFunction)(void));

/**
 * Initializes Timer 3 as a gated timer
 * @param time The length of time it takes the timer to expire
 * @param units The units to use (S, mS, uS, nS). Use the enum TIMER_UNITS to correctly specify
 * @param gateSource What source causes the gate to open and close\
 * 0 = T3G input pin\
 * 1 = TMR2 to match PR2 output\
 * 2 = Comparator 1 output\
 * 3 = Comparator 2 output
 * @param mode How the timer accumulates\
 * 0 = Timer Gate Single Pulse mode is disabled <---- I believe this means it stop-starts every time a pulse occurs, giving the total amount of time the gate was open\
 * 1 = Timer Gate Single Pulse mode is enabled <---- I believe this means it auto-resets every time a new pulse starts, giving the total amount of time the pulse lasted
 * @param triggerPolarity On which edge should the trigger occur\
 * 0 = Active Low\
 * 1 = Active High
 * @param interruptFunction The function that will be called when the timer expires, it should be a function pointer that has the format of "void Some_Function(void)"\
 * Sending a null pointer "(void *)0" is acceptable, this would be done if you did not want a function to be called during the interrupt
 * @return 1 = everything was verified and the timer has been properly initialized\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Initialize_TMR3_As_Gated_Timer(int time, enum TIMER_UNITS units, int gateSource, int mode, int triggerPolarity, void (*interruptFunction)(void));

/**
 * This function will turn on or off a specified timer
 * @param timer The target timer, use the enum TIMERS_AVAILABLE
 * @param newState The state that the timer should be changed to\
 * 1 = Enabled\
 * 0 = Disabled
 * @return 1 = The timer was succefully changed\
 * 0 = Either the timer was out of range or the new state was invalid
 */
int Change_Timer_Trigger(enum TIMERS_AVAILABLE timer, int newState);

/**
 * Allows the reading of the timer value
 * @param timer The target timer, use the enum TIMERS_AVAILABLE
 * @param timeUnits The units to use (S, mS, uS, nS). Use the enum TIMER_UNITS to correctly specify
 * @return The current timer value in the units specified
 */
int Current_Timer(enum TIMERS_AVAILABLE timer, enum TIMER_UNITS units);

/**
 * Allow the lengthening or shortening of the timers length
 * @param timer The target timer, use the enum TIMERS_AVAILABLE
 * @param time The desired length of time it takes the timer to expire
 * @param units The units to use (S, mS, uS, nS). Use the enum TIMER_UNITS to correctly specify
 * @return 1 = everything was verified and the timer has been properly setup\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Change_Timer_Period(struct TIMER_DEFINITION timer, unsigned long time, enum TIMER_UNITS units);

#endif	/* TIMERS_H */
