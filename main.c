/*
 * TIMERS.c
 *
 * Created: 1/4/2022 5:06:40 PM
 * Author : No. 01
 */ 
#include "TIMERS.h"
/**PLACE THE NEEDED INTERRUPT COUNTS HERE TO REACH YOUR NEEDED TIME***********/
#define  NEEDED_CTC_INTERRUPTS_1 130
#define  NEEDED_CTC_INTERRUPTS_2 75
#define  NEEDED_CTC_MATCHES_1 130
#define  NEEDED_CTC_MATCHES_2 75
#define NEEDED_TICKS 125
/**FLAGS FOR INTERRUPT FUNCTION FUNCTIONALITY**/
uint16_t gu16_counter=0;
uint8_t gu8_flag=LOW;
/**CONFIGURE THE TIMER HERE**/
ST_TIMER_config_t config ={TIMER_2,CTC,T2_PRESCALING_256};


int main(void)
{
    /* Replace with your application code */
	uint8_t u8_value=0;
	TIMER_start(&config,NEEDED_TICKS);
	PORTB_DIR=HIGH<<4;
	//TIMER_interruptEnable(config.timer,config.mode); //Activate if interrupt functionality is needed
	//TIMER_callBack(&TIMER_interruptFunction);  //Activate if interrupt functionality is needed
    while (1) 
    {/****COMMENT OUT THE CODE BELOW IN THE WHILE (1) TO TRY INTERRUPTS*******/
		if(LOW==gu8_flag)
		{
			while (u8_value==0)
			{
				TIMER_readInterruptFlag(config,&u8_value);
			}
			u8_value=0;
			gu16_counter++;
			TIMER_clearInterruptFlag(config);
			if(gu16_counter==NEEDED_CTC_MATCHES_1)
			{
				PORTB_DATA=HIGH<<4;
				gu8_flag=HIGH;
				gu16_counter=0;
			}
		}
		else if(HIGH==gu8_flag)
		{
			while (u8_value==0)
			{
				TIMER_readInterruptFlag(config,&u8_value);
			}
			u8_value=0;
			gu16_counter++;
			TIMER_clearInterruptFlag(config);
			if(gu16_counter==NEEDED_CTC_MATCHES_2)
			{
				PORTB_DATA&=~(HIGH<<4);
				gu8_flag=LOW;
				gu16_counter=0;
			}
		}

    }
}

/*******INTERRUPT FUNCTION IF INTERRUPTS ARE ACTIVATED**************/
void TIMER_interruptFunction(void)
{
	/* Replace with your INTERRUPT FUNCTIONALITY code */
	if(LOW==gu8_flag)	//IF LED TURNED OFF
	{
		gu16_counter++; //increment counter
		if(NEEDED_CTC_INTERRUPTS_1==gu16_counter) //if it reached the calculated number needed to turn on the LED
		{
			PORTB_DATA=HIGH<<4;	//turn on the LED 
			gu16_counter=0; //reset counter
			gu8_flag=HIGH;	//LED TURNED ON FLAG
		}
	}
	else
	{
		gu16_counter++;	//increment counter
		if(NEEDED_CTC_INTERRUPTS_2==gu16_counter)	//if it reached the calculated number needed to turn off the LED
		{
			PORTB_DATA=LOW;	//turn off the LED
			gu16_counter=0;	//reset counter
			gu8_flag=LOW;	//LED is now turned off
		}
	}
	
}
