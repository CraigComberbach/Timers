#ifndef TIMERS_H
#define	TIMERS_H

/************* Semantic Versioning***************/
#define TIMERS_MAJOR	0
#define TIMERS_MINOR	0
#define TIMERS_PATCH	0

/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
enum TIMERS
{
	TIMER1,	//TMR1
	TIMER2,	//TMR2
	TIMER3,	//TMR3
	TIMER4	//TMR4
};

/***********State Machine Definitions************/
/*************Function  Prototypes***************/
int Initialize_TMR1(int TCKPS, void (*interruptFunction)(void));
int Initialize_TMR2(int TCKPS, void (*interruptFunction)(void));
int Initialize_TMR3(int TCKPS, void (*interruptFunction)(void));
int Initialize_TMR4(int TCKPS, void (*interruptFunction)(void));

#endif	/* TIMERS_H */

