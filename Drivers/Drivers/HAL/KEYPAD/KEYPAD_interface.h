/*
 * KEYPAD_interface.h
 *
 * Created: 9/13/2021 8:19:46 AM
 *  Author: Karim Essam
 */ 


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define  maxNumOfCols 4
typedef struct{
	u8 rows;
	u8 columns;
	u8* rowPins;
	DIO_PORT_t* rowPorts;
	u8* columnPins;
	DIO_PORT_t* columnPorts;
	u8 (*map)[maxNumOfCols]; // this is the 2 dimen array of the buttons
}Keypad_t;

/*********************************************************************
* DESCRIPTION : a function used to Initialize a keypad
* PARAMETERS  : Keypad_t structure.
* Return Value: Void.
***********************************************************************/
void KEYPAD_voidInit(Keypad_t* keypad);

/*********************************************************************
* DESCRIPTION : a function used to get the pressed key
* PARAMETERS  : Keypad_t structure.
* Return Value: it will return the pressed character. if nothing pressed , it will return -1.
***********************************************************************/
s8 KEYPAD_u8GetKey(Keypad_t* keypad);


#endif /* KEYPAD_INTERFACE_H_ */