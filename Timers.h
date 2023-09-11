#ifndef TIMERS_H
#define	TIMERS_H

/***********Add to config file header************/
/*
	//Timer Driver Library
	#define TIMERS_MAJOR 0
	#define TIMERS_MINOR 3
	#define TIMERS_PATCH 0
*/

/*
enum TIMER_DEFINITIONS
{
	TIMER_TIMER1,
	TIMER_TIMER2,
	TIMER_TIMER3,
	NUMBER_OF_AVAILABLE_TIMERS
};
*/

/***************Add to config file***************/
//#ifndef TIMERS_LIBRARY
//	#error "You need to include the Timer Control Driver Library for this code to compile"
//#endif

/*************Semantic  Versioning***************/
#define TIMERS_DRIVER

/*************   Magic  Numbers   ***************/
#define NO_TIMER_INTERRUPT	(void*)0
#define TIMER_ON	1
#define TIMER_OFF	0

/*************    Enumeration     ***************/
enum TIMER_UNITS
{
	SECONDS,
	MILLI_SECONDS,
	MICRO_SECONDS,
	NANO_SECONDS,
	TICKS
};

enum AVAILABLE_TIMERS
{
	TIMER1,
	TIMER2,
	TIMER3,
	NUMBER_OF_PHYSICAL_TIMERS
};

/***********State Machine Definitions************/
/*************Function  Prototypes***************/
void Initialize_Timers(void);
void Setup_Timer(enum TIMER_DEFINITIONS timerName, enum AVAILABLE_TIMERS timerUsed, uint32_t period, enum TIMER_UNITS units, void (*interruptFunction)(void));
void Timer_Start(enum TIMER_DEFINITIONS timerName);
void Timer_Pause(enum TIMER_DEFINITIONS timerName);
void Timer_End(enum TIMER_DEFINITIONS timerName);
//void Timer_Change_Period(...);
//void Timer_Change_Frequency(...);
//inline uint16_t Timer_Current_Ticks(enum TIMER_DEFINITIONS timerName);
//uint16_t Timer_Current_Time(enum TIMER_DEFINITIONS, ...);

#endif	/* TIMERS_H */
