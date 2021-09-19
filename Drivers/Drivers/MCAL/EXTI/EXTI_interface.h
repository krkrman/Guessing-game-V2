/*
 * EXTI_interface.h
 *
 * Created: 9/2/2021 9:30:38 AM
 *  Author: Karim Essam
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

enum InterruptPin_t {INT0 , INT1 , INT2};
enum TriggerType_t {LOW_LEVEL,ANY_LOGICAL_CHANGE,FALLING_EDGE,RISING_EDGE};
enum InputType_t{INPUT , INTERNAL_PULL_UP};
	
void EXTI_voidInit(enum InterruptPin_t interruptPin , enum TriggerType_t triggerType , enum InputType_t inputType);
void EXTI_voidEnableInterrupt(enum InterruptPin_t interruptPin);
void EXTI_voidDisableInterrupt(enum InterruptPin_t interruptPin); 
void EXTI_voidSetCallbackFunction(enum InterruptPin_t interruptPin ,void(*CallBack)(void));

#endif /* EXTI_INTERFACE_H_ */