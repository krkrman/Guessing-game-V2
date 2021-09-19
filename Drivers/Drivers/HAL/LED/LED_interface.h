/*
 * LED_interface.h
 *
 * Created: 9/1/2021 9:31:46 PM
 *  Author: Karim Essam
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

typedef struct {
	u8 pin;
	DIO_PORT_t port;	
}LED_t;
void LED_voidInit(LED_t* led);
void LED_voidTurnOn(LED_t* led);
void LED_voidTurnOff(LED_t* led);
void LED_voidToggle(LED_t* led);

#endif /* LED_INTERFACE_H_ */