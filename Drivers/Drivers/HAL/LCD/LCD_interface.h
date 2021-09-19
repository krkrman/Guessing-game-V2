/*
*Author     : Moustafa ElGafry
*Date       : 30 SEP 2020
*Version    : V01
*/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_voidInit(void);
void LCD_voidSendChar( char Copy_u8Data);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendString(char* PtrStrig);
void LCD_voidSendNumber(f32 floatNumber, u8 numbersAfterPoint);
void LCD_voidClear();
void LCD_voidSetCursorPosition(u8 x_position, u8 y_position);

#endif