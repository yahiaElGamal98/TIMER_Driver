/*
 * TIMERS.c
 *
 * Created: 1/4/2022 8:23:01 PM
 *  Author: No. 01
 */

#include "TIMERS.h"
#include "Registers.h"

void TIMER_callBack(void(*ISR) (void))
{
	TIMERCALLBACK=ISR;
}
void __vector_10(void)
{
	if(TIMERCALLBACK!=NULL)
	{
		TIMERCALLBACK();
	}
}
void __vector_5(void)
{
	if(TIMERCALLBACK!=NULL)
	{
		TIMERCALLBACK();
	}
}
void __vector_4(void)
{
	if(TIMERCALLBACK!=NULL)
	{
		TIMERCALLBACK();
	}
}
void __vector_11(void)
{
	if(TIMERCALLBACK!=NULL)
	{
		TIMERCALLBACK();
	}
}

void TIMER_start(ST_TIMER_config_t* configurations,uint8_t ticks)
{
	if(TIMER_0==configurations->timer)
	{
		//initialize prescaling and start timer
		switch(configurations->prescaling)
		{
			case(T0_NO_PRESCALING): TCCR0=T0_NO_PRESCALING;break;
			case(T0_PRESCALING_8): TCCR0=T0_PRESCALING_8;break;
			case(T0_PRESCALING_64): TCCR0=T0_PRESCALING_64;break;
			case(T0_PRESCALING_256): TCCR0=T0_PRESCALING_256;break;
			case(T0_PRESCALING_1024): TCCR0=T0_PRESCALING_1024;break;
			default: break;
		}
		//initialize mode and starting (NORMAL MODE) OR comparing ticks (CTC MODE)
		switch(configurations->mode)
		{
			case(CTC): OCR0=ticks;TCCR0|= HIGH<<3;break;
			case(NORMAL):TCNT0=ticks;break;
			default:break;
		}
	}
	else if(TIMER_2==configurations->timer) //same procedure as above if timer 2 is chosen
	{
		switch(configurations->prescaling)
		{
		case(T2_NO_PRESCALING): TCCR2=T2_NO_PRESCALING;break;
		case(T2_PRESCALING_8): TCCR2=T2_PRESCALING_8;break;
		case(T2_PRESCALING_32): TCCR2=T2_PRESCALING_32;break;
		case(T2_PRESCALING_64): TCCR2=T2_PRESCALING_64;break;
		case(T2_PRESCALING_128): TCCR2=T2_PRESCALING_128;break;
		case(T2_PRESCALING_256): TCCR2=T2_PRESCALING_256;break;
		case(T2_PRESCALING_1024): TCCR2=T2_PRESCALING_1024;break;
		default: break;
	}
	switch(configurations->mode)
	{
		case(CTC): OCR2=ticks;TCCR2|= HIGH<<3;break;
		case(NORMAL):TCNT2=ticks;break;
		default:break;
	}
	}
	
}
void TIMER_stop(ST_TIMER_config_t* configurations)
{
	//stop the clock
		if(TIMER_0==configurations->timer)
		{
			TCCR0=LOW;
		}
		else if(TIMER_2==configurations->timer)
		{
			TCCR2=LOW;
		}
}
void TIMER_read(uint8_t timer, uint8_t *value)
{
	//reading values inside the timer data register
	if(TIMER_0==timer)
	{
		*value=TCNT0;
	}
	else if(TIMER_2==timer)
	{
		*value=TCNT2;
	}
	else
	{
		*value=NULL;
	}
}
void TIMER_interruptEnable(uint8_t timer,uint8_t mode)
{
	//enable global interrupts
	SREG|=HIGH<<GLOBAL_INTERRUPT_ENABLE;
	//enable whichever interrupt needed
	if(TIMER_0==timer)
	{
		switch(mode)
		{
			case(NORMAL):TIMSK=HIGH<<NORMAL_TIMER0;
			case(CTC):TIMSK=HIGH<<CTC_TIMER0;
		}
	}
	else if(TIMER_2==timer)
	{
		switch(mode)
		{
			case(NORMAL):TIMSK=HIGH<<NORMAL_TIMER2;
			case(CTC):TIMSK=HIGH<<CTC_TIMER2;
		}
	}
}
void TIMER_readInterruptFlag(ST_TIMER_config_t configurations, uint8_t *val)
{
	if(TIMER_0==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):*val=(TIFR&(HIGH<<NORMAL_TIMER0))>>NORMAL_TIMER0;
			case(CTC):*val=(TIFR&(HIGH<<CTC_TIMER0))>>CTC_TIMER0;
		}
	}
	else if(TIMER_2==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):*val=(TIFR&(HIGH<<NORMAL_TIMER2))>>NORMAL_TIMER2;
			case(CTC):*val=(TIFR&(HIGH<<CTC_TIMER2))>>CTC_TIMER2;
		}
	}
}
void TIMER_clearInterruptFlag(ST_TIMER_config_t configurations)
{
	if(TIMER_0==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):TIFR=HIGH<<NORMAL_TIMER0;
			case(CTC):TIFR=HIGH<<CTC_TIMER0;
		}
	}
	else if(TIMER_2==configurations.timer)
	{
		switch(configurations.mode)
		{
			case(NORMAL):TIFR=HIGH<<NORMAL_TIMER2;
			case(CTC):TIFR=HIGH<<CTC_TIMER2;
		}
	}
}

 
