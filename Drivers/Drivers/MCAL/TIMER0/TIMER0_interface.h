/*
 * TIMER0_interface.h
 *
 * Created: 9/2/2021 1:02:26 PM
 *  Author: Karim Essam
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

enum TIMER0_Mode{TIMER0_NORMAL_MODE , TIMER0_PHASE_CORRECT_PWM , TIMER0_CTC_MODE , TIMER0_FAST_PWM};
enum TIMER0_CTC{TIMER0_CTC_DISCONNECT,TIMER0_CTC_TOG,TIMER0_CTC_CLR,TIMER0_CTC_SET};
enum TIMER0_PhaseCorrectPWM{TIMER0_PCPWM_DIS,TIMER0_PCPWM_NON_INVERT=2,TIMER0_PCPWM_INVERT};
enum TIMER0_FAST_PWM{TIMER0_FPWM_DIS,TIMER0_FPWM_NON_INVERT=2,TIMER0_FPWM_INVERT};
enum TIMER0_Prescalar{TIMER0_NO_PRESCALAR , TIMER0_PRESCALAR_1 , TIMER0_PRESCALAR_8 , TIMER0_PRESCALAR_64 , TIMER0_PRESCALAR_256,TIMER0_PRESCALAR_1024,TIMER0_COUNTER_T0_FALLING_EDGE , TIMER0_COUNTER_T0_RISING_EDGE};
enum TIMER0_Interrupt{TIMER0_INTERRUPT_OVERFLOW,TIMER0_INTERRUPT_COMPARE};

// for fastPWM => frequency = cpuFrequency/(prescalar*256)
// for phaseCorrectPWM => frequency = cpuFrequency/(prescalar*512)
// for overflow => preload = (Time * cpuFrequency ) / prescalar
// channel mode is not used with normal mode
void TIMER0_voidInit(enum TIMER0_Mode mode, u8 channelMode,enum TIMER0_Prescalar prescalar,  u8 preload);
u8 TIMER0_u8GetCounter(void);
void TIMER0_voidSetCounterValue(u8 counterValue);
void TIMER0_voidStart(void);
void TIMER0_voidStop(void);
//dutyCycle will be a number between 0=>100%
// for PWM modes
// for fastPWM => frequency = cpuFrequency/(prescalar*256)
// for phaseCorrectPWM => frequency = cpuFrequency/(prescalar*512)
void TIMER0_voidSetDutyCycle(f32 dutyCycle);
// Sets CTC Frequency
// OCR0_REG = cpuFrequency/(2*frequency*prescalarArray[storedPrescalar-1]) -1;
//should not exceed 255
void TIMER0_voidSetFrequency(f32 frequency);
void TIMER0_voidEnableInterrupt(enum TIMER0_Interrupt);
void TIMER0_voidDisableInterrupt(enum TIMER0_Interrupt);
void TIMER0_voidSetCallBack(enum TIMER0_Interrupt, void(*callBack)(void));
u8 TIMER0_u8CheckFlag(enum TIMER0_Interrupt);
void TIMER0_voidClearFlag(enum TIMER0_Interrupt interrupt);
void TIMER0_voidSoftwarePWM(u8 port , u8 pin , u8 dutyCycle);

#endif /* TIMER0_INTERFACE_H_ */