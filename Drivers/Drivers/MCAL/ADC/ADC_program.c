/*
 * ADC_program.c
 *
 * Created: 9/15/2021 2:17:55 PM
 *  Author: Karim Essam
 */ 

#include "ADC_interface.h"
#include "ADC_private.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO_interface.h"

void ADC_voidInit(ADC_Mode_t mode,ADC_AutoTrigger_t triggerSource, ADC_Prescalar_t prescalar)
{
	 ADCSRA_REG = (mode<<5) | (prescalar) | (3<<6);
	 SFIOR_REG = (triggerSource << 5);
	 // select right adjusted
	 CLR_BIT(ADMUX_REG , 5);
	 SET_BIT(REFS0 , 6);
	 adcMode = mode;
}

u16 ADC_u16ReadChannel(ADC_ChannelID_t channel)
{
	DIO_voidSetPinDirection(channel , PORTA , INPUT);
	//select channel
	ADMUX_REG |= channel;
	// start conversion
	SET_BIT(ADCSRA_REG , ADSC);
	if (mode == ADC_MODE_SINGLE_CONVERSION)
	{
		while(GET_BIT(ADCSRA_REG , ADSC));
			return ADCHL_REG;
	}else {
		return ADCHL_REG;
	}
}

void ADC_voidEnableInterruptWithCallback(enum ADC_ChannelID_t channel , void (*callback)(u16))
{
	//enable ADC interrupt
	SET_BIT(ADCSRA_REG , 3);
	// enable GIE
	SET_BIT(SREG,7);
	ADC_callback = callback;
};

void ADC_ISR_VECTOR(void)
{
	if (ADC_callback != 0)
	{
		ADC_callback(ADCHL_REG);
	}
}