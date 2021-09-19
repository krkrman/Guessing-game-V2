/*
 * utility.h
 *
 * Created: 9/14/2021 2:22:01 PM
 *  Author: Karim Essam
 */ 


#ifndef UTILITY_H_
#define UTILITY_H_

/*
	to generate a random number

*/
u8 UTILITY_generateRandomNumber(u8 lower , u8 upper);

void UTILITY_f32ToString(char* str, f32 d, u8 n);

u16 UTILITY_stringToInt(u8* str);


#endif /* UTILITY_H_ */