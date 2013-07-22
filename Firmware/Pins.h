#ifndef PINS_H
#define	PINS_H

/************* Semantic Versioning***************/
#define PINS_MAJOR	0
#define PINS_MINOR	1
#define PINS_PATCH	0

/*************   Magic  Numbers   ***************/
#define LOW			0
#define HIGH		1
#define OUTPUT		0
#define INPUT		1
#define PUSH_PULL	0
#define OPEN_DRAIN	1

/*************    Enumeration     ***************/
enum PIN_NAMES
{
	ra0 = 0,
	ra1 = 1,
	ra2 = 2,
	ra3 = 3,
	ra4 = 4,
	ra5 = 5,
	ra6 = 6,
	rb4 = 20,
	rb8 = 24,
	rb9 = 25,
	rb14 = 30,
	rb15 = 31,
};

/***********State Machine Definitions************/
/*************Function  Prototypes***************/
/**
 * Sets up each individual pin (LAT, ODC & TRIS registers)
 * @param pinName Specifies the pin from the project specific definition of PIN_NAMES
 * @param latch The desired state of the LAT register (1 = High, 0 = Low)
 * @param openDrain The desired state of the ODC register (1 = Open Drain, 0 = Push Pull)
 * @param tris The desired state of the TRIS register (1 = Input, 0 = Output)
 * @return Returns a 1 if the selections were all valid and the change was made\
 * Returns a 0 if the selections were invalid, no changes were made
 * @Note Enabling Analog or other capabilities are done in the respective module files and overrides any settings done here
 */
int Initialize_Pin(enum PIN_NAMES pinName, int latch, int openDrain, int tris);

#endif	/* PINS_H */

