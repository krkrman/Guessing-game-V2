/*
 * TIMER1_interface.h
 *
 * Created: 9/7/2021 2:11:11 PM
 *  Author: Karim Essam
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


enum TIMER1_Prescalar{NO_PRESCALAR , PRESCALAR_1 , PRESCALAR_8 , PRESCALAR_64 , PRESCALAR_256,PRESCALAR_1024,COUNTER_T0_FALLING_EDGE , COUNTER_T0_RISING_EDGE};

enum TIMER1_Mode{	
	MODE_NORMAL,
	MODE_PHASE_CORRECT_PWM_8BIT,
	MODE_PHASE_CORRECT_PWM_9BIT,
	MODE_PHASE_CORRECT_PWM_10BIT,
	MODE_CTC,
	MODE_FAST_PWM_8BIT,
	MODE_FAST_PWM_9BIT,
	MODE_FAST_PWM_10BIT,
	MODE_PHASE_CORRECT_FPWM_TOP_CAPT,
	MODE_PHASE_CORRECT_FPWM_TOP_COMPAREA,
	MODE_PHASE_CORRECT_PWM_TOP_CAPTURE,
	MODE_PHASE_CORRECT_PWM_TOP_COMPAREA,
	MODE_CTC_TOP_CAPTURE,
	MODE_FAST_PWM_TOP_CAPTURE=14,
	MODE_FAST_PWM_TOP_COMPARE
	};

enum TIMER1_CTC{TIMER1_CTC_DIS,TIMER1_CTC_TOG,TIMER1_CTC_CLR,TIMER1_CTC_SET};
enum TIMER1_PhaseCorrectPWM{TIMER1_PCPWM_DIS,TIMER1_PCPWM_NON_INVERT=2,TIMER1_PCPWM_INVERT};
enum TIMER1_FastPWM{TIMER1_FPWM_DIS,TIMER1_FPWM_NON_INVERT=2,TIMER1_FPWM_INVERT};
enum TIMER1_Interrupt{TIMER1_INTERRUPT_OVERFLOW=2,TIMER1_INTERRUPT_COMPAREB,TIMER1_INTERRUPT_COMPAREA,TIMER1_INTERRUPT_CAPTURE};

enum TIMER1ChannelID{TIMER1_CHANNEL_A,TIMER1_CHANNEL_B};
enum TIMER1InputPulseType{TIMER1_PULSE_LOW,TIMER1_PULSE_HIGH};

// for fastPWM => frequency = cpuFrequency/(prescalar*256)
// for phaseCorrectPWM => frequency = cpuFrequency/(prescalar*512)
// for overflow => preload = (Time * cpuFrequency ) / prescalar
// channel mode is not used with normal mode
void	TIMER1_voidInit(enum TIMER1_Prescalar clockSource, enum TIMER1_Mode mode, u8 channelAMode,u8 channelBMode, u16 preload);
u16		TIMER1_u16GetCounter(void);
void	TIMER1_voidSetCounter(u16 CounterValue);
void	TIMER1_voidStart(void);
void	TIMER1_voidStop(void);
//DutyCycle will be a number between 0=>100%
// for PWM modes
// for fastPWM => frequency = cpuFrequency/(prescalar*256)
// for phaseCorrectPWM => frequency = cpuFrequency/(prescalar*512)
void TIMER1_voidSetDutyCycle(enum TIMER1ChannelID Channel,f32 DutyCycle);
//Sets CTC Frequency
// OCR1_REG = cpuFrequency/(2*frequency*prescalarArray[storedPrescalar-1]) -1;
//should not exceed 65655
void	TIMER1_voidSetFrequency(enum TIMER1ChannelID Channel, f32 Frequency);
void	TIMER1_voidEnableInterrupt(enum TIMER1_Interrupt Interrupt);
void	TIMER1_voidDisableInterrupt(enum TIMER1_Interrupt Interrupt);
void	TIMER1_voidSetCallBack(enum TIMER1_Interrupt Interrupt, void *CallBack);


f32 MTIM1_f32GetPulseDuration(enum TIMER1InputPulseType Pulse);
f32 MTIM1_f32GetSignalFrequency(void);

void MTIM1_voidStartTickMeasure(void);
u32  MTIM1_u32GetElapsedTicks(void);
u16 MTIM1_u16GetDivision(void);


#endif /* TIMER1_INTERFACE_H_ */