/*
 * LCD_private.h
 *
 * Created: 9/6/2021 2:49:09 PM
 *  Author: Karim Essam
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_



#define		FUNC_SET 	0x30

#define		 CLR_DISPLAY				0x01

#define		 INCREMENT_CURSORMOVE		0x06

#define		DISPLAY_OFF_CURSOR_OFF			 0x08
#define		DISPLAY_ON_CURSOR_ON			 0x0E
#define		DISPLAY_ON_CURSOR_OFF			 0x0C
#define		DISPLAY_ON_CURSOR_BLINKING       0x08

#define		CURSOR_AT_HOME					 0x80
#define		SHIFT_ENTIRE_DISPLAY_LEFT		 0X18
#define		SHIFT_ENTIRE_DISPLAY_RIGHT		 0X1C

#define		MOVE_CURSOR_LEFT_ONE_CHAR		 0x10
#define		MOVE_CURSOR_RIGHT_ONE_CHAR		 0x14

#define		EIGHT_BIT_MODE	0
#define		FOUR_BIT_MODE	1

#define LCD_INSTRUCTION_SET_DDRAM_ADDR(ADDR)			((1<<7)|(ADDR&0x7F))

u8 PYPositions[4] = {0,64,20,84};


#endif /* LCD_PRIVATE_H_ */