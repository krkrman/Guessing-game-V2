/*
 * TIMER0_private.h
 *
 * Created: 9/2/2021 1:01:56 PM
 *  Author: Karim Essam
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

//Timer 0 Stuff
#define TCCR0_REG			(*(volatile u8*)0x53)
#define TCNT0_REG			(*(volatile u8*)0x52)
#define OCR0_REG			(*(volatile u8*)0x5C)

//for interrupt
#define TIMSK_REG			(*(volatile u8*)0x59)
#define TIFR_REG			(*(volatile u8*)0x58)
//for GIE
#define SREG_REG 			(*(volatile u8*)(0x5F))

u8 storedPrescalar = 0;
u8 storedPreload = 0;
u16 prescalarArray[] = {1 , 8 , 64 , 256 , 1024};
	
#define TIMER0_ISR_VECTOR_OVERFLOW			__vector_11
#define TIMER0_ISR_VECTOR_COMPARE			__vector_10


void TIMER0_ISR_VECTOR_OVERFLOW(void)	__attribute__((signal,used));
void TIMER0_ISR_VECTOR_COMPARE(void)	__attribute__((signal,used));

void (*TIMER0_callBacks[2])(void) = {0,0};
	
u8 isSoftwarePWMMode = 0;
u8 SoftwarePWM_PORT = 0;
u8 SoftwarePWM_PIN = 0; 

u8 SoftwarePWM_counter = 0;
u8 SoftwarePWM_dutyCycle = 0;

#endif /* TIMER0_PRIVATE_H_ */