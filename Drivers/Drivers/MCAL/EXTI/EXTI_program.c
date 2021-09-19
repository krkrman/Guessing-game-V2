/*
 * EXTI_program.c
 *
 * Created: 9/2/2021 9:30:57 AM
 *  Author: Karim Essam
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "../DIO/DIO_interface.h"

void EXTI_voidInit(enum InterruptPin_t interruptPin , enum TriggerType_t triggerType , enum InputType_t inputType){
	
	//global interrupt enable
	SET_BIT(SREG,7);
	switch(interruptPin)
	{
		case INT0:
			//external0 interrupt enable
			SET_BIT(GICR,6);
			if (inputType == INPUT)
			{
				DIO_voidSetPinDirection(INT0_PIN , INPUT);
			}else {
				DIO_voidSetPinDirection(INT0_PIN , INPUT_PULL_UP);
			}
			DIO_voidSetPinDirection(INT0_PIN , INPUT);
			//set interrupt type
			if(triggerType==FALLING_EDGE)
			{
				CLR_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);
			}
			else if(triggerType==RISING_EDGE)
			{
				SET_BIT(MCUCR,0);
				SET_BIT(MCUCR,1);
			}
			else if(triggerType==ANY_LOGICAL_CHANGE)
			{
				SET_BIT(MCUCR,0);
				CLR_BIT(MCUCR,1);
			}
			else if(triggerType==LOW_LEVEL)
			{
				CLR_BIT(MCUCR,0);
				CLR_BIT(MCUCR,1);
			}
			break;
		case INT1:
			//external1 interrupt enable
			SET_BIT(GICR,7);
			if (inputType == INPUT)
			{
				DIO_voidSetPinDirection(INT1_PIN , INPUT);
				}else {
				DIO_voidSetPinDirection(INT1_PIN , INPUT_PULL_UP);
			}
			//set interrupt type

			if(triggerType==FALLING_EDGE)
			{
				CLR_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);
			}
			else if(triggerType==RISING_EDGE)
			{
				SET_BIT(MCUCR,2);
				SET_BIT(MCUCR,3);
			}
			else if(triggerType==ANY_LOGICAL_CHANGE)
			{
				SET_BIT(MCUCR,2);
				CLR_BIT(MCUCR,3);
			}
			else if(triggerType==LOW_LEVEL)
			{
				CLR_BIT(MCUCR,2);
				CLR_BIT(MCUCR,3);
			}
			break;
		case INT2:
			SET_BIT(GICR,5);
			if (inputType == INPUT)
			{
				DIO_voidSetPinDirection(INT2_PIN , INPUT);
			}else {
				DIO_voidSetPinDirection(INT2_PIN , INPUT_PULL_UP);
			}
			if (triggerType == FALLING_EDGE)
			{
				CLR_BIT(MCUCSR , 6);
			} else
			{
				SET_BIT(MCUCSR , 6);
			}
			break;
		}
}

void EXTI_voidEnableInterrupt(enum InterruptPin_t interruptPin){
	switch(interruptPin)
	{
		case INT0:
			SET_BIT(GICR,6);
			break;
		case INT1:
			SET_BIT(GICR,7);
			break;
		case INT2:
			SET_BIT(GICR , 5);
			break;
	}

}

void EXTI_voidDisableInterrupt(enum InterruptPin_t interruptPin){
	switch(interruptPin)
	{
		case INT0:
		CLR_BIT(GICR,6);
		break;
		case INT1:
		CLR_BIT(GICR,7);
		break;
		case INT2:
		CLR_BIT(GICR , 5);
		break;
	}
}

void EXTI_voidSetCallbackFunction(enum InterruptPin_t interruptPin ,void(*CallBack)(void))
{
	if(interruptPin > INT2)
	return;
	EXTI_voidCallBacks[interruptPin] = CallBack;
}

void EXTI_VECTOR_ISR_EXTI0(void){
	
	if(EXTI_voidCallBacks[0] != 0){
		EXTI_voidCallBacks[0]();
	}
}

void EXTI_VECTOR_ISR_EXTI1(void){
	
	if(EXTI_voidCallBacks[1] != 0){
		EXTI_voidCallBacks[1]();
	}
}

void EXTI_VECTOR_ISR_EXTI2(void){
	if(EXTI_voidCallBacks[2] != 0){
		EXTI_voidCallBacks[2]();
	}
}