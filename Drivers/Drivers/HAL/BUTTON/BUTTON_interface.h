/*
 * BUTTON_interface.h
 *
 * Created: 9/1/2021 9:42:20 PM
 *  Author: Karim Essam
 */ 


#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"

typedef enum {PULL_UP , PULL_DOWN , INTERNAL_PULL_UP}ButtonConnection_t;
typedef struct{
	u8 pin;
	DIO_PORT_t port;
	ButtonConnection_t 	buttonConnection;
}Button_t;
void BUTTON_voidInit(Button_t* button);
u8 BUTTON_u8isPressed(Button_t* button);

#endif /* BUTTON_INTERFACE_H_ */