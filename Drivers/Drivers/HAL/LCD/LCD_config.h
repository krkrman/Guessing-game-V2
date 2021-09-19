/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H
/*
Select control pins connection as shown:
									0,PORTA
									1,PORTA
									2,PORTA	
										.
										.
										.
										.
*/
#define 	LCD_RS 			5,PORTD	
#define 	LCD_RW			6,PORTD
#define 	LCD_E			7,PORTD
/*
select data pins connection 
*/
#define 	LCD_8_BIT_DATA_PORT		PORTB
#define 	LCD_4_BIT_DATA_D4		4,PORTB
#define 	LCD_4_BIT_DATA_D5		5,PORTB
#define 	LCD_4_BIT_DATA_D6		6,PORTB
#define 	LCD_4_BIT_DATA_D7		7,PORTB

#define		MODE	FOUR_BIT_MODE



#endif