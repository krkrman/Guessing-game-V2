/*
 * TIMER0_program.c
 *
 * Created: 9/2/2021 1:03:37 PM
 *  Author: Karim Essam
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/CLOCK/CLOCK_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "TIMER0_private.h"
#include "TIMER0_interface.h"

void TIMER0_voidInit(enum TIMER0_Mode mode, u8 channelMode,enum TIMER0_Prescalar prescalar,  u8 preload)
{
	OCR0_REG = 0;
	TCNT0_REG = preload;
	// clear interrupt
	CLR_BIT(TIMSK_REG , 6);
	CLR_BIT(TIMSK_REG , 7);
	
	TCCR0_REG = (GET_BIT(mode , 0)<<6) | (GET_BIT(mode , 1) << 3) | (channelMode << 4) | (prescalar);	
		
	storedPrescalar = prescalar;
	storedPreload = preload;
	isSoftwarePWMMode = 0;
};
u8 TIMER0_u8GetCounter(void){
	return TCNT0_REG;
}
void TIMER0_voidSetCounterValue(u8 counterValue)
{
	TCNT0_REG = counterValue;
}
void TIMER0_voidStart(void){
	TCCR0_REG |= storedPrescalar;
}
void TIMER0_voidStop(void){
	CLR_BIT(TCCR0_REG , 0);
	CLR_BIT(TCCR0_REG , 1);
	CLR_BIT(TCCR0_REG , 2);
}
//DutyCycle will be a number between 0=>100%
void TIMER0_voidSetDutyCycle(f32 dutyCycle)
{
	u8 OCR_value = dutyCycle*255.0/100.0;
	OCR0_REG = dutyCycle;
}

//Sets CTC Frequency
void TIMER0_voidSetFrequency(f32 frequency)
{
	if(storedPrescalar > 5 && storedPrescalar == 0)
		return;
	u32 cpuFrequency = CLOCK_u32GetSystemClock();
	OCR0_REG = cpuFrequency/(2*frequency*prescalarArray[storedPrescalar-1]) -1;	 
}
u8 TIMER0_u8CheckFlag(enum TIMER0_Interrupt interrupt)
{
	return GET_BIT(TIFR_REG , interrupt);
}

void TIMER0_voidClearFlag(enum TIMER0_Interrupt interrupt)
{
	SET_BIT(TIFR_REG , interrupt);
}

void TIMER0_voidEnableInterrupt(enum TIMER0_Interrupt interrupt)
{
	SET_BIT(TIMSK_REG , interrupt);
	SET_BIT(SREG_REG , 7);
}
void TIMER0_voidDisableInterrupt(enum TIMER0_Interrupt interrupt){
	CLR_BIT(TIMSK_REG , interrupt);
}
void TIMER0_voidSetCallBack(enum TIMER0_Interrupt interrupt, void(*callBack)(void))
{
	if (interrupt > 1)
		return;
	TIMER0_callBacks[interrupt] = callBack;
};
void TIMER0_voidSoftwarePWM(u8 port , u8 pin , u8 dutyCycle)
{
	DIO_voidSetPinDirection(pin , port , OUTPUT);
	SoftwarePWM_PORT = port;
	SoftwarePWM_PIN = pin;
	SoftwarePWM_dutyCycle = dutyCycle;
	OCR0_REG = 100;
	isSoftwarePWMMode = 1;
	TIMER0_voidEnableInterrupt(TIMER0_INTERRUPT_COMPARE);
}
void TIMER0_ISR_VECTOR_OVERFLOW(void){
	if(TIMER0_callBacks[0] != 0){
		TIMER0_callBacks[0]();
	}
	SET_BIT(TIFR_REG,0);
	TCNT0_REG = storedPreload;
}

void TIMER0_ISR_VECTOR_COMPARE(void){
	if (isSoftwarePWMMode)
	{
		SoftwarePWM_counter++;
		if (SoftwarePWM_counter >= SoftwarePWM_dutyCycle )
		{
			DIO_voidSetPinValue(SoftwarePWM_PIN , SoftwarePWM_PORT , LOW);
		}
		if (SoftwarePWM_counter >= 100)
		{
			DIO_voidSetPinValue(SoftwarePWM_PIN , SoftwarePWM_PORT , HIGH);
			SoftwarePWM_counter = 0;
		}
	}
	else 
	{
		if(TIMER0_callBacks[1] != 0){
			TIMER0_callBacks[1]();
		}
	}
	SET_BIT(TIFR_REG,1);
}
