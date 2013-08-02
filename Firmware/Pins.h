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
/**
 * Add the names of the pins here. Enumeration starts with Port A Pin 0 and increments from there.
 * The numbers assume each port has 16 pins (most don't) and that there are no skipped ports (A, then B, then C, etc)
 */
enum PIN_NAMES
{
	ra0 = 0,	//RA0
	ra1 = 1,	//RA1
	ra2 = 2,	//RA2
	ra3 = 3,	//RA3
	ra4 = 4,	//RA4
	ra5 = 5,	//RA5
	ra6 = 6,	//RA6
	rb4 = 20,	//RB4
	rb8 = 24,	//RB8
	rb9 = 25,	//RB9
	rb14 = 30,	//RB14
	rb15 = 31,	//RB15
};

/***********State Machine Definitions************/
/*************Function  Prototypes***************/
/**
 * Sets up each individual pin (LAT, ODC & TRIS registers)
 * @param pinName Specifies the pin from the project specific definition of PIN_NAMES
 * @param latch The desired state of the LAT register (1 = High, 0 = Low)
 * @param odc The desired state of the ODC register (1 = Open Drain, 0 = Push Pull)
 * @param tris The desired state of the TRIS register (1 = Input, 0 = Output)
 * @return Returns a 1 if the selections were all valid and the change was made\
 * Returns a 0 if the selections were invalid, no changes were made
 * @Note Enabling Analog or other capabilities are done in the respective module files and overrides any settings done here
 */
int Initialize_Pin(enum PIN_NAMES pinName, int latch, int odc, int tris);

#endif	/* PINS_H */

