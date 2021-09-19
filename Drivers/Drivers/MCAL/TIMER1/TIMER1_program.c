/*
 * TIMER1_program.c
 *
 *  Created: 9/7/2021 2:11:46 PM
 *  Author: Karim Essam
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/CLOCK/CLOCK_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "TIMER1_private.h"
#include "TIMER1_interface.h"

void TIMER1_voidInit(enum TIMER1_Prescalar prescalar, enum TIMER1_Mode mode, u8 channelAMode,u8 channelBMode, u16 preload)
{
	TCCR1A_REG = 0;
	TCCR1B_REG = 0;
	TCNT1_REG = 0;
	OCR1A_REG = 0;
	OCR1B_REG = 0;
	ICR1_REG = 0;
	
	TCCR1A_REG = (GET_BIT(mode , 0)) | (GET_BIT(mode , 1) << 1) |  (channelAMode << 6)|  (channelBMode << 4);
	TCCR1B_REG = (GET_BIT(mode , 2)<<3) | (GET_BIT(mode , 3)<<4) | (prescalar);
	TCNT1_REG = preload;
	TIMER1_storedPreload = preload;
	TIMER1_storedPrescalar = prescalar;
};

u16	TIMER1_u16GetCounter(void)
{
	return TCNT1_REG;
}
void TIMER1_voidSetCounter(u16 counterValue)
{
	TCNT1_REG = counterValue;
}

void TIMER1_voidStart(void)
{
	TCCR1B_REG |= TIMER1_storedPreload;
}

void TIMER1_voidStop(void)
{
	CLR_BIT(TCCR1B_REG , 0);
	CLR_BIT(TCCR1B_REG , 1);
	CLR_BIT(TCCR1B_REG , 2);
}

void TIMER1_voidSetDutyCycle(enum TIMER1ChannelID channel,f32 dutyCycle)
{
	u8 OCR_value = dutyCycle*65535.0/100.0;
	if (channel == TIMER1_CHANNEL_A)
	{
		OCR1A_REG = OCR_value;	
	} else 
	{
		OCR1B_REG = OCR_value;
	}
}

void TIMER1_voidSetFrequency(enum TIMER1ChannelID channel, f32 frequency)
{
	u32 cpuFrequency = CLOCK_u32GetSystemClock();
	u16 OCR_value = (f32)cpuFrequency/(2.0*frequency*(f32)TIMER1_prescalarArray[TIMER1_storedPrescalar-1]) -1;
	if (channel == TIMER1_CHANNEL_A)
	{
		OCR1A_REG = OCR_value;
	} else
	{
		OCR1B_REG = OCR_value;
	}
};

void TIMER1_voidEnableInterrupt(enum TIMER1_Interrupt interrupt)
{
	// to clear interrupt
	SET_BIT(TIFR_REG,interrupt);
	// to enable it
	SET_BIT(TIMSK_REG,interrupt);
	SET_BIT(SREG_REG , 7);
}
void TIMER1_voidDisableInterrupt(enum TIMER1_Interrupt interrupt)
{
	CLR_BIT(TIFR_REG,interrupt);
};
void TIMER1_voidSetCallBack(enum TIMER1_Interrupt interrupt, void *callBack)
{
	if (interrupt < TIMER1_INTERRUPT_CAPTURE)
	{
		TIMER1_callBacks[interrupt - 2] = (void (*)(void))callBack;
	}else 
	{
		TIMER1_captureCallBack = (void (*)(u16))callBack;
	}
};

f32 MTIM1_f32GetPulseDuration(enum TIMER1InputPulseType pulse);
f32 MTIM1_f32GetSignalFrequency(void);

void MTIM1_voidStartTickMeasure(void);
u32  MTIM1_u32GetElapsedTicks(void);
u16 MTIM1_u16GetDivision(void);

void TIMER1_ISR_VECTOR_COMPAREA(void){
	if(TIMER1_callBacks[2] != 0)
	TIMER1_callBacks[2]();
}
void TIMER1_ISR_VECTOR_COMPAREB(void){
	if(TIMER1_callBacks[1] != 0)
	TIMER1_callBacks[1]();
}
void TIMER1_ISR_VECTOR_OVERFLOW(void){
	overflowCounter++;
	if(TIMER1_callBacks[0] != 0)
		TIMER1_callBacks[0]();
	TCNT1_REG = TIMER1_storedPreload;
}
void TIM1_ISR_VECTOR_CAPTURE(void){
	if(TIMER1_captureCallBack != 0)
		TIMER1_captureCallBack(ICR1_REG);
}