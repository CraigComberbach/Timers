#ifndef TIMERS_H
#define	TIMERS_H

/************* Semantic Versioning***************/
#define TIMERS_MAJOR	0
#define TIMERS_MINOR	1
#define TIMERS_PATCH	0

/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
/***********State Machine Definitions************/
/*************Function  Prototypes***************/
/**
 * Initializes Timer 1
 * @param prescale Clock prescaler\
 * 0 = 1:1\
 * 1 = 1:8\
 * 2 = 1:64\
 * 3 = 1:256\
 * @param interruptFunction The function that will be called when the timer expires, it should be a function pointer that has the format of "void Some_Function(void)"\
 * Sending a null pointer "(void *)0" is acceptable, this would be done if you did not want a function to be called during the interrupt
 * @return 1 = everything was verified and the timer has been properly initialized\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Initialize_TMR1(int prescale, void (*interruptFunction)(void));

/**
 * Initializes Timer 2
 * @param prescale Clock prescaler\
 * 0 = 1:1\
 * 1 = 1:4\
 * 2 = 1:16\
 * 3 = Undefined
 * @param postscale Clock postscalar\
 * 0 = 1:1\
 * 1 = 1:2\
 * 2 = 1:3\
 * ...\
 * 15 = 1:16
 * @param interruptFunction The function that will be called when the timer expires, it should be a function pointer that has the format of "void Some_Function(void)"\
 * Sending a null pointer "(void *)0" is acceptable, this would be done if you did not want a function to be called during the interrupt
 * @return 1 = everything was verified and the timer has been properly initialized\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Initialize_TMR2(int prescale, int postscale, void (*interruptFunction)(void));

/**
 * Initializes Timer 3 as a standard timer
 * @param prescale Clock prescaler\
 * 0 = 1:1\
 * 1 = 1:2\
 * 2 = 1:4\
 * 3 = 1:8
 * @param interruptFunction The function that will be called when the timer expires, it should be a function pointer that has the format of "void Some_Function(void)"\
 * Sending a null pointer "(void *)0" is acceptable, this would be done if you did not want a function to be called during the interrupt
 * @return 1 = everything was verified and the timer has been properly initialized\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Initialize_TMR3_As_Timer(int prescale, void (*interruptFunction)(void));

/**
 * Initializes Timer 3 as a gated timer
 * @param prescale Clock prescaler\
 * 0 = 1:1\
 * 1 = 1:2\
 * 2 = 1:4\
 * 3 = 1:8
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
int Initialize_TMR3_As_Gated_Timer(int prescale, int gateSource, int mode, int triggerPolarity, void (*interruptFunction)(void));


/**
 * Initializes Timer 4
 * @param prescale Clock prescaler\
 * 0 = 1:1\
 * 1 = 1:4\
 * 2 = 1:16\
 * 3 = Undefined
 * @param postscale Clock postscalar\
 * 0 = 1:1\
 * 1 = 1:2\
 * 2 = 1:3\
 * ...\
 * 15 = 1:16
 * @param interruptFunction The function that will be called when the timer expires, it should be a function pointer that has the format of "void Some_Function(void)"\
 * Sending a null pointer "(void *)0" is acceptable, this would be done if you did not want a function to be called during the interrupt
 * @return 1 = everything was verified and the timer has been properly initialized\
 * 0 = Something failed, either an argument sent was out of range or the timer is unavailable on the current chip
 */
int Initialize_TMR4(int prescale, int postscale, void (*interruptFunction)(void));

#endif	/* TIMERS_H */
