/*
 * BUTTON_program.c
 *
 * Created: 9/1/2021 9:43:34 PM
 *  Author: Karim Essam
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "BUTTON_interface.h"


void BUTTON_voidInit(Button_t* button){
	if (button->buttonConnection == INTERNAL_PULL_UP)
	{
		DIO_voidSetPinDirection(button->pin , button->port , INPUT_PULL_UP);
	}else {
		DIO_voidSetPinDirection(button->pin  , button->port , INPUT);
	}
}
u8 BUTTON_u8isPressed(Button_t* button){
	if (button->buttonConnection == PULL_DOWN)
	{
		return DIO_u8GetPinValue(button->pin  , button->port);
	} else {
		return !DIO_u8GetPinValue(button->pin  , button->port);
	}
}
