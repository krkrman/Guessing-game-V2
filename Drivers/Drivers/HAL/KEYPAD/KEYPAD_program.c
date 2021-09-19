/*
 * KEYPAD_program.c
 *
 * Created: 9/13/2021 8:20:09 AM
 *  Author: Karim Essam
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "KEYPAD_interface.h"

static void reInitRows(Keypad_t* keypad)
{
	for(int rowIndex = 0 ; rowIndex < keypad->rows ; rowIndex++)
		DIO_voidSetPinValue(keypad->rowPins[rowIndex] , keypad->rowPorts[rowIndex] , HIGH);
}

static s8 checkKeys(Keypad_t* keypad , u8 rowIndex)
{
	for (int colIndex = 0 ; colIndex < keypad->columns ; colIndex++ )
	{
		if (DIO_u8GetPinValue(keypad->columnPins[colIndex] , keypad->columnPorts[colIndex]) == 0)
			return keypad->map[rowIndex][colIndex];
	}
	return -1;
}

void KEYPAD_voidInit(Keypad_t* keypad){
	for(int rowIndex = 0 ; rowIndex < keypad->rows ; rowIndex++){
		DIO_voidSetPinDirection(keypad->rowPins[rowIndex] , keypad->rowPorts[rowIndex] , OUTPUT);
		DIO_voidSetPinValue(keypad->rowPins[rowIndex] , keypad->rowPorts[rowIndex] , HIGH);
	}
	
	for(int colIndex = 0 ; colIndex < keypad->columns ; colIndex++)
		DIO_voidSetPinDirection(keypad->columnPins[colIndex] , keypad->columnPorts[colIndex] , INPUT_PULL_UP);
}

s8 KEYPAD_u8GetKey(Keypad_t* keypad)
{
	for (int rowIndex = 0 ; rowIndex< keypad->rows;rowIndex++)
	{
		reInitRows(keypad);
		DIO_voidSetPinValue(keypad->rowPins[rowIndex] , keypad->rowPorts[rowIndex] , LOW);
		s8 characterPressed = checkKeys(keypad , rowIndex);
		if (characterPressed != (s8)-1)
		{
			// to block the code till user let the button
			while (checkKeys(keypad , rowIndex) != (s8)-1);
			
			return characterPressed;
		}
	}
	return -1;
}

