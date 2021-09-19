/*
 * EXTI_private.h
 *
 * Created: 9/2/2021 9:41:29 AM
 *  Author: Karim Essam
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define 	SREG 	 (*(volatile u8*)(0x5F))
#define 	MCUCR 	 (*(volatile u8*)(0x55))
#define 	MCUCSR 	 (*(volatile u8*)(0x54))
#define 	GICR 	 (*(volatile u8*)(0x5B))
#define 	GIFR 	 (*(volatile u8*)(0x5A))


#define EXTI_VECTOR_ISR_EXTI0		__vector_1
#define EXTI_VECTOR_ISR_EXTI1		__vector_2
#define EXTI_VECTOR_ISR_EXTI2		__vector_3


void EXTI_VECTOR_ISR_EXTI0() __attribute__((signal,used));
void EXTI_VECTOR_ISR_EXTI1() __attribute__((signal,used));
void EXTI_VECTOR_ISR_EXTI2() __attribute__((signal,used));

void (*EXTI_voidCallBacks[3])(void) = {0,0,0};

#endif /* EXTI_PRIVATE_H_ */