/*
 * ADC_private.h
 *
 * Created: 9/15/2021 2:17:32 PM
 *  Author: Karim Essam
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX_REG	*((volatile u8*)0x27)
#define ADCSRA_REG	*((volatile u8*)0x26)
#define SFIOR_REG	*((volatile u8*)0x50)
#define ADCL_REG	*((volatile u8*)0x24)
#define ADCH_REG	*((volatile u8*)0x25)
// this will take the highest and lowest registers together in case you take the right left in the adc
// because it is 16-bits
#define ADCHL_REG	*((volatile u16*)0x24)
//for GIE
#define SREG_REG 			(*(volatile u8*)(0x5F))

#define ADC_ISR_VECTOR		__vector_16
void ADC_ISR_VECTOR(void)	__attribute__((signal,used));

void (*ADC_callback)(u16) = 0;

u8 adcMode = 0;
#endif /* ADC_PRIVATE_H_ */