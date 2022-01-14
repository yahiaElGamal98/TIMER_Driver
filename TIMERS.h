/*
 * TIMERS.h
 *
 * Created: 1/4/2022 5:22:34 PM
 * Author: No. 01
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_
#include "STD_types.h"
#include "Registers.h"

/*****HIGH AND LOW bits******/
#define HIGH 1
#define LOW 0
#define NULL '\0'
/*******MACROS FOR CHOOSING NORMAL AND CTC MODES (CONFIGURATION STRUCT)*******/
#define NORMAL 0
#define CTC 1
/****MACROS FOR CONFIGURATION BITS****************************/
#define NORMAL_TIMER0 0
#define CTC_TIMER0  1
#define NORMAL_TIMER2 6
#define CTC_TIMER2 7
/******MACROS FOR CHOOSING WHICH TIMER (CONFIGURATION STRUCT)*****************/
#define TIMER_0 0
#define TIMER_2 2
/********TIMER 0 PRESCALING MACROS (CONFIGURATION STRUCT)************************/
#define T0_NO_PRESCALING 1
#define T0_PRESCALING_8 2
#define T0_PRESCALING_64 3
#define T0_PRESCALING_256 4
#define T0_PRESCALING_1024 5
/*********TIMER 2 PRESCALING MACROS**********************/
#define T2_NO_PRESCALING 1
#define T2_PRESCALING_8 2
#define T2_PRESCALING_32 3
#define T2_PRESCALING_64 4
#define T2_PRESCALING_128 5
#define T2_PRESCALING_256 6
#define T2_PRESCALING_1024 7
/************GLOBAL INTERRUPT ENABLE BIT************************/
#define GLOBAL_INTERRUPT_ENABLE 7

/***********VECTOR TABLE*************/

void __vector_4(void) __attribute__((signal,used)); //TMR2 compare match ISR
void __vector_5(void) __attribute__((signal,used));	//TMR2 OVF ISR
void __vector_10(void) __attribute__((signal,used)); //TMR0 Compare match ISR
void __vector_11(void) __attribute__((signal,used)); //TMR0 OVF ISR
/*********CALL BACK FUNCTIONS FOR ISRs (VECTORS)*********************/
void TIMER_callBack(void(*ISR) (void));

void static (*TIMERCALLBACK) (void);
/*****CONFIGURATION STRUCT FOR TIMER, TAKES THE PREDEFINED MACROS which were labeled ->(CONFIGURATION STRUCT) above*******************/
typedef struct ST_TIMER_config_t
{
	uint8_t timer;
	uint8_t mode;
	uint8_t prescaling;	
}ST_TIMER_config_t;

//TIMERS APIs
//Place the config file and the starting ticks. In normal mode starting ticks will be in TCNTx, in CTC it will be placed in OCRx register.   
void TIMER_start(ST_TIMER_config_t* configurations,uint8_t ticks); 
//Place whichever configuration timer you need to stop counting.
void TIMER_stop(ST_TIMER_config_t* configurations);
//read the value inside the timer register and place it in value.
void TIMER_read(uint8_t timer,uint8_t *value);
//Enable global interrupts and the one of the pre-configured timer
void TIMER_interruptEnable(uint8_t timer, uint8_t mode);
//IN THIS FUNCTION THE USER IMPLEMENTS WHAT HE NEEDS TO BE DONE INSIDE THE INTERRUPTS
void TIMER_interruptFunction(void);
void TIMER_readInterruptFlag(ST_TIMER_config_t configurations, uint8_t *val);
void TIMER_clearInterruptFlag(ST_TIMER_config_t configurations);


#endif /* TIMERS_H_ */