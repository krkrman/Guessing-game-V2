/*
 * TIMER1_private.h
 *
 * Created: 9/7/2021 2:10:57 PM
 *  Author: Karim Essam
 */ 


#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

//Timer 1 Stuff
#define TCCR1A_REG				(*(volatile u8*	)0x4F)
#define TCCR1B_REG				(*(volatile u8*	)0x4E)
#define TCNT1_REG				(*(volatile u16*)0x4C)
#define ICR1_REG				(*(volatile u16*)0x46)
#define OCR1B_REG				(*(volatile u16*)0x48)
#define OCR1A_REG				(*(volatile u16*)0x4A)
#define TIMSK_REG				(*(volatile u8*)0x59)
#define TIFR_REG				(*(volatile u8*)0x58)

//for GIE
#define SREG_REG 			(*(volatile u8*)(0x5F))

#define TIMER1_ISR_VECTOR_OVERFLOW		__vector_9
#define TIMER1_ISR_VECTOR_COMPAREA		__vector_7
#define TIMER1_ISR_VECTOR_COMPAREB		__vector_8
#define TIMER1_ISR_VECTOR_CAPTURE			__vector_6

void TIMER1_ISR_VECTOR_CAPTURE(void)	__attribute__((signal,used));
void TIMER1_ISR_VECTOR_COMPAREA(void)	__attribute__((signal,used));
void TIMER1_ISR_VECTOR_COMPAREB(void)	__attribute__((signal,used));
void TIMER1_ISR_VECTOR_OVERFLOW(void)	__attribute__((signal,used));

void (*TIMER1_callBacks[3])(void) = {0,0,0};

void (*TIMER1_captureCallBack)(u16 CaptureValue) = 0;

u8 overflowCounter = 0;

u8 TIMER1_storedPrescalar = 0;
u16 TIMER1_storedPreload = 0;
u16 TIMER1_prescalarArray[5] = {1,8,64,256,1024};




#endif /* TIMER1_PRIVATE_H_ */