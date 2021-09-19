/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../UTILITY/utility.h"

#include "LCD_private.h"
#include "LCD_interface.h"
#include "LCD_config.h"

#define F_CPU 1000000UL
#include "util/delay.h"

static u8 isInitFinished = 0;
void LCD_voidInit(void)
{
	DIO_voidSetPinDirection(LCD_RS,OUTPUT);
	DIO_voidSetPinDirection(LCD_RW,OUTPUT);
	DIO_voidSetPinDirection(LCD_E,OUTPUT);
	#if MODE == EIGHT_BIT_MODE
		DIO_voidSetPortDirection(LCD_8_BIT_DATA_PORT , OUTPUT);
		
	#else
		DIO_voidSetPinDirection(LCD_4_BIT_DATA_D4,OUTPUT);
		DIO_voidSetPinDirection(LCD_4_BIT_DATA_D5,OUTPUT);
		DIO_voidSetPinDirection(LCD_4_BIT_DATA_D6,OUTPUT);
		DIO_voidSetPinDirection(LCD_4_BIT_DATA_D7,OUTPUT);

	#endif
	
	_delay_ms(40);
	LCD_voidSendCommand(FUNC_SET);
	_delay_ms(2);
	LCD_voidSendCommand(FUNC_SET);
	_delay_ms(2);
	LCD_voidSendCommand(FUNC_SET);
	_delay_ms(2);
	LCD_voidSendCommand(0b00100000);
	_delay_ms(2);
	isInitFinished = 1;
	LCD_voidSendCommand(DISPLAY_ON_CURSOR_OFF);
	LCD_voidSendCommand(INCREMENT_CURSORMOVE);
	LCD_voidSendCommand(CLR_DISPLAY);
	LCD_voidSendCommand(CURSOR_AT_HOME);
}
void LCD_voidSendChar(char Copy_u8Data)
{
	DIO_voidSetPinValue(LCD_RS,HIGH);
	DIO_voidSetPinValue(LCD_RW,LOW);
	
	#if MODE == EIGHT_BIT_MODE
		DIO_voidSetPortValue(LCD_8_BIT_DATA_PORT,Copy_u8Data);
		//set clock
		DIO_voidSetPinValue(LCD_E,HIGH);
		_delay_ms(2);
		DIO_voidSetPinValue(LCD_E,LOW);
		_delay_ms(2);
	#else
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D4 , GET_BIT(Copy_u8Data, 4));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D5 , GET_BIT(Copy_u8Data, 5));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D6 , GET_BIT(Copy_u8Data, 6));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D7 , GET_BIT(Copy_u8Data, 7));
	
		//set clock
		DIO_voidSetPinValue(LCD_E,HIGH);
		_delay_ms(2);
		DIO_voidSetPinValue(LCD_E,LOW);
		_delay_ms(2);
		
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D4 , GET_BIT(Copy_u8Data, 0));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D5 , GET_BIT(Copy_u8Data, 1));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D6 , GET_BIT(Copy_u8Data, 2));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D7 , GET_BIT(Copy_u8Data, 3));
		
		//set clock
		DIO_voidSetPinValue(LCD_E,HIGH);
		_delay_ms(2);
		DIO_voidSetPinValue(LCD_E,LOW);
		_delay_ms(2);
		
		
		
	#endif
	
}
void LCD_voidSendCommand(u8 Copy_u8Command)
{	
	//send command
	DIO_voidSetPinValue(LCD_RS,LOW);
	DIO_voidSetPinValue(LCD_RW,LOW);

	#if MODE == EIGHT_BIT_MODE
		DIO_voidSetPortValue(LCD_8_BIT_DATA_PORT,Copy_u8Command);
		//set clock
		DIO_voidSetPinValue(LCD_E,HIGH);
		_delay_ms(2);
		DIO_voidSetPinValue(LCD_E,LOW);
		_delay_ms(2);
		
	#else
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D4 , GET_BIT(Copy_u8Command, 4));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D5 , GET_BIT(Copy_u8Command, 5));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D6 , GET_BIT(Copy_u8Command, 6));
		DIO_voidSetPinValue(LCD_4_BIT_DATA_D7 , GET_BIT(Copy_u8Command, 7));
		
		//set clock
		DIO_voidSetPinValue(LCD_E,HIGH);
		_delay_ms(2);
		DIO_voidSetPinValue(LCD_E,LOW);
		_delay_ms(2);
		
		if (isInitFinished)
		{
			DIO_voidSetPinValue(LCD_4_BIT_DATA_D4 , GET_BIT(Copy_u8Command, 0));
			DIO_voidSetPinValue(LCD_4_BIT_DATA_D5 , GET_BIT(Copy_u8Command, 1));
			DIO_voidSetPinValue(LCD_4_BIT_DATA_D6 , GET_BIT(Copy_u8Command, 2));
			DIO_voidSetPinValue(LCD_4_BIT_DATA_D7 , GET_BIT(Copy_u8Command, 3));
			
			//set clock
			DIO_voidSetPinValue(LCD_E,HIGH);
			_delay_ms(2);
			DIO_voidSetPinValue(LCD_E,LOW);
			_delay_ms(2);
		}
	#endif
	
}
void LCD_voidSendString(char* PtrStrig)
{
	u8 Local_u8Couter ;
	for(Local_u8Couter=0; PtrStrig[Local_u8Couter]!=0;Local_u8Couter++)		
	/* Send each char of string till the NULL */
	{		
			LCD_voidSendChar(PtrStrig[Local_u8Couter]);
	}
}
void LCD_voidClear()
{
	LCD_voidSendCommand (CLR_DISPLAY);	     	/* clear display */
	LCD_voidSendCommand (CURSOR_AT_HOME);		/* cursor at home position */
}	
void LCD_voidSetCursorPosition(u8 x_position, u8 y_position)
{
	u8 address;
	if (y_position < 2 && x_position < 16)
	{
		address = (y_position * 0x40) + x_position;
		SET_BIT(address , 7);
		LCD_voidSendCommand(address);
	}
}

void LCD_voidSendNumber(f32 floatNumber , u8 numbersAfterPoint)
{
	char c[50]; //size of the number
	UTILITY_f32ToString(c , floatNumber , numbersAfterPoint);
	LCD_voidSendString(c);
}

