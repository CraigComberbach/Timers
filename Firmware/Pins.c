/**************************************************************************************************
Authours:				Craig Comberbach
Target Hardware:		PIC24F
Chip resources used:	Gives direct access to every single pin
Code assumptions:
Purpose:				Read the Thermistor inputs

Version History:
v0.0.1	2013-07-21  Craig Comberbach
	Compiler: XC16 v1.11	IDE: MPLABx 1.70	Tool: ICD3	Computer: Intel Core2 Quad CPU 2.40 GHz, 5 GB RAM, Windows 7 64 bit Home Premium SP1
	Retooled everything to use existing macro names for each pin/function
	Processor names now either enable or disable pins
		-Disabled pins return a 0 indicating it was an invalid choice
		-Enabled pins are have the Latch then the TriState registers set (Specifically in that order) before returning a 1 indicating the pin was valid
	Added in the Open Drain register to initialization as well
v0.0.0	2013-07-20  Craig Comberbach
	Compiler: XC16 v1.11	IDE: MPLABx 1.70	Tool: ICD3	Computer: Intel Core2 Quad CPU 2.40 GHz, 5 GB RAM, Windows 7 64 bit Home Premium SP1
	First version
**************************************************************************************************/
/*************    Header Files    ***************/
#include "Project Setup.h"
#include "Pins.h"

/************* Semantic Versioning***************/
/************Arbitrary Functionality*************/
/*************   Magic  Numbers   ***************/
/*************    Enumeration     ***************/
enum
{
	PortA,
	PortB,
};

enum
{
	Rx0,
	Rx1,
	Rx2,
	Rx3,
	Rx4,
	Rx5,
	Rx6,
	Rx7,
	Rx8,
	Rx9,
	Rx10,
	Rx11,
	Rx12,
	Rx13,
	Rx14,
	Rx15
};

/***********State Machine Definitions************/
/*************  Global Variables  ***************/
/*************Function  Prototypes***************/
/************* Device Definitions ***************/
/************* Module Definitions ***************/
/************* Other  Definitions ***************/

int Initialize_Pin(enum PIN_NAMES pinName, int latch, int openDrain, int tris)
{
	int port, pin;

	//Determine pin and port
	port = pinName / 16;
	pin = pinName % 16;

	//Range checking
	if((latch != 0) && (latch != 1))
		return 0;
	if((tris != 0) && (tris != 1))
		return 0;
	if((openDrain != 0) && (openDrain != 1))
		return 0;

	//Now that we are through the gauntlet, it's time for assignment
	switch(port)
	{
		case PortA:
			switch(pin)
			{
				case Rx0:
					#if defined __PIC24F08KL200__
						LATAbits.LATA0 = latch;
						ODCAbits.ODA0 = openDrain;
						TRISAbits.TRISA0 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx1:
					#if defined __PIC24F08KL200__
						LATAbits.LATA1 = latch;
						ODCAbits.ODA1 = openDrain;
						TRISAbits.TRISA1 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx2:
					#if defined __PIC24F08KL200__
						LATAbits.LATA2 = latch;
						ODCAbits.ODA2 = openDrain;
						TRISAbits.TRISA2 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx3:
					#if defined __PIC24F08KL200__
						LATAbits.LATA3 = latch;
						ODCAbits.ODA3 = openDrain;
						TRISAbits.TRISA3 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx4:
					#if defined __PIC24F08KL200__
						LATAbits.LATA4 = latch;
						ODCAbits.ODA4 = openDrain;
						TRISAbits.TRISA4 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx5:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA5 = latch;
						ODCAbits.ODA5 = openDrain;
						TRISAbits.TRISA5 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx6:
					#if defined __PIC24F08KL200__
						LATAbits.LATA6 = latch;
						ODCAbits.ODA6 = openDrain;
						TRISAbits.TRISA6 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx7:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA7 = latch;
						ODCAbits.ODA7 = openDrain;
						TRISAbits.TRISA7 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx8:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA8 = latch;
						ODCAbits.ODA8 = openDrain;
						TRISAbits.TRISA8 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx9:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA9 = latch;
						ODCAbits.ODA9 = openDrain;
						TRISAbits.TRISA9 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx10:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA10 = latch;
						ODCAbits.ODA10 = openDrain;
						TRISAbits.TRISA10 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx11:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA11 = latch;
						ODCAbits.ODA11 = openDrain;
						TRISAbits.TRISA11 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx12:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA12 = latch;
						ODCAbits.ODA12 = openDrain;
						TRISAbits.TRISA12 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx13:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA13 = latch;
						ODCAbits.ODA13 = openDrain;
						TRISAbits.TRISA13 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx14:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA14 = latch;
						ODCAbits.ODA14 = openDrain;
						TRISAbits.TRISA14 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx15:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATAbits.LATA15 = latch;
						ODCAbits.ODA15 = openDrain;
						TRISAbits.TRISA15 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				default:
					return 0;//Only a math error can get to here
			}
			return 0;//How did I get here?
		case PortB:
			switch(pin)
			{
				case Rx0:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB0 = latch;
						ODCBbits.ODB0 = openDrain;
						TRISBbits.TRISB0 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx1:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB1 = latch;
						ODCBbits.ODB1 = openDrain;
						TRISBbits.TRISB1 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx2:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB2 = latch;
						ODCBbits.ODB2 = openDrain;
						TRISBbits.TRISB2 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx3:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB3 = latch;
						ODCBbits.ODB3 = openDrain;
						TRISBbits.TRISB3 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx4:
					#if defined __PIC24F08KL200__
						LATBbits.LATB4 = latch;
						ODCBbits.ODB4 = openDrain;
						TRISBbits.TRISB4 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx5:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB5 = latch;
						ODCBbits.ODB5 = openDrain;
						TRISBbits.TRISB5 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx6:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB6 = latch;
						ODCBbits.ODB6 = openDrain;
						TRISBbits.TRISB6 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx7:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB7 = latch;
						ODCBbits.ODB7 = openDrain;
						TRISBbits.TRISB7 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx8:
					#if defined __PIC24F08KL200__
						LATBbits.LATB8 = latch;
						ODCBbits.ODB8 = openDrain;
						TRISBbits.TRISB8 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx9:
					#if defined __PIC24F08KL200__
						LATBbits.LATB9 = latch;
						ODCBbits.ODB9 = openDrain;
						TRISBbits.TRISB9 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx10:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB10 = latch;
						ODCBbits.ODB10 = openDrain;
						TRISBbits.TRISB10 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx11:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB11 = latch;
						ODCBbits.ODB11 = openDrain;
						TRISBbits.TRISB11 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx12:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB12 = latch;
						ODCBbits.ODB12 = openDrain;
						TRISBbits.TRISB12 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx13:
					#if defined PLACE_MICROCHIP_PART_NAME_HERE
						LATBbits.LATB13 = latch;
						ODCBbits.ODB13 = openDrain;
						TRISBbits.TRISB13 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx14:
					#if defined __PIC24F08KL200__
						LATBbits.LATB14 = latch;
						ODCBbits.ODB14 = openDrain;
						TRISBbits.TRISB14 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				case Rx15:
					#if defined __PIC24F08KL200__
						LATBbits.LATB15 = latch;
						ODCBbits.ODB15 = openDrain;
						TRISBbits.TRISB15 = tris;
						return 1;//This pin exists and the change was successful
					#else
						return 0;//This pin does not exist
					#endif
				default:
					return 0;//Only a math error can get to here
			}
			return 0;//How did I get here?

		default:
			return 0;//Port does not exist
	}

	//We should never get here!
	return 0;//Failure
}

int Write_Pin(enum PIN_NAMES pinName, int newLatch)
{

}

int Read_Pin(enum PIN_NAMES pinName)
{

}
