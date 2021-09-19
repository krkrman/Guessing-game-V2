/*
 * Drivers.c
 *
 * Created: 9/1/2021 9:00:12 PM
 * Author : Karim Essam
 */ 
#include "MCAL/DIO/DIO_interface.h"
#include "LIB/STD_TYPES.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/KEYPAD/KEYPAD_interface.h"
#include "UTILITY/utility.h"
#define F_CPU 1000000
#include <util/delay.h>

u8 counter = 0;
u8 randomNumber = 0;

void showResult(void){
	LCD_voidClear();
	LCD_voidSendString("your number is:");
	LCD_voidSendNumber(counter , 0);
	_delay_ms(2000);
	LCD_voidClear();
	LCD_voidSendString("Real number is:");
	LCD_voidSendNumber(randomNumber , 0);
	_delay_ms(2000);
	LCD_voidClear();
	if (counter == (u8)0)
	{
		LCD_voidSendString("choose a number pls");
	}else if (counter > 15)
	{
		LCD_voidSendString("number between 1:15");
	}
	else if (counter == randomNumber)
	{
		LCD_voidSendString("You Won");
	}else 
	{
		LCD_voidSendString("You Lost");
	}
	_delay_ms(2000);
	LCD_voidClear();
	LCD_voidSendString("Guess another number:");
	counter = 0;
	randomNumber = UTILITY_generateRandomNumber(1 , 15);
}

int main(void)
{ 	
	Keypad_t keyPad;
	randomNumber = UTILITY_generateRandomNumber(1 , 15);
	keyPad.rows = 4;
	keyPad.columns = 4;
	u8 rowPins[4];
	u8 rowPorts[4];

	u8 columnPins[4];
	u8 columnPorts[4];

	for (int i = 0; i < 4 ;i++)
	{
		rowPins[i] = i;
		rowPorts[i] = PORTC;
		columnPins[i] = i+4;
		columnPorts[i] = PORTC;
	}
	keyPad.rowPins = rowPins;
	keyPad.columnPins = columnPins;
	keyPad.rowPorts = rowPorts;
	keyPad.columnPorts = columnPorts;
	
	u8 map[4][4] = 
	{{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}};
	keyPad.map = map;
	
	
	KEYPAD_voidInit(&keyPad);
	LCD_voidInit();
	LCD_voidSendString("Guess a number: ");
	u8 stringNumber[5];
	u8 c = 0;
	while(1){
		s8 charater = KEYPAD_u8GetKey(&keyPad);
		if (charater != (s8)-1 && charater != '=')
		{
			stringNumber[c++] = (u8)charater;
			stringNumber[c] = '\0';

			counter = (u8)atoi(stringNumber);
			
			LCD_voidClear();
			LCD_voidSendNumber((f32)counter , 0);
		} else if (charater == '=')
		{
			showResult();
			c=0;
		}
	}	
}

