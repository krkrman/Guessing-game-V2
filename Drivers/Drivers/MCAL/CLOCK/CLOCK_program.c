/*
 * CLOCK_program.c
 *
 * Created: 9/1/2021 9:06:55 PM
 *  Author: Karim Essam
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "CLOCK_interface.h"
#include "CLOCK_config.h"


void CLOCK_voidDelayMS(u32 ms){
	register u32 Ticks = (CLOCK_SYSTEM_FREQUENCY/7000)*ms - 10;
	while(Ticks--)
	__asm__ volatile("NOP");
}

u32 CLOCK_u32GetSystemClock(void){
	return CLOCK_SYSTEM_FREQUENCY;
}