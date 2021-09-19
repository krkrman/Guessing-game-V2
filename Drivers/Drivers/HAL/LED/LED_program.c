/*
 * LED_program.c
 *
 * Created: 9/1/2021 9:30:28 PM
 *  Author: Karim Essam
 */ 
#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_interface.h"

void LED_voidInit(LED_t* led){
	DIO_voidSetPinDirection(led->pin , led->port , OUTPUT);
}
void LED_voidTurnOn(LED_t* led){
	DIO_voidSetPinValue(led->pin , led->port , HIGH);	
}
void LED_voidTurnOff(LED_t* led){
	DIO_voidSetPinValue(led->pin , led->port , LOW);
}

void LED_voidToggle(LED_t* led){
	DIO_voidTogglePinValue(led->pin , led->port);
}