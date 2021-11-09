#include "Timer.h"
#include "PWM.h"

void speed_init(){
	uint32_t a;
	PORT0->DIR&=~(1<<23)|(1<<4);
	
	a=IOCON_MOTOR_SPEED_1;
	a &= ~(1 << 2);
	a |=(1<<1)|(1<<0);
	IOCON_MOTOR_SPEED_1=a;
	
	a=IOCON_MOTOR_SPEED_2;
	a &= ~(1 << 2);
	a |=(1<<1)|(1<<0);
	IOCON_MOTOR_SPEED_2=a;
}

void Timer_Init(){
	PCONP|=(1<<22)|(1<<23);
	TIMER3->CTCR&=~(3);
	TIMER2->CTCR&=~(3);
	TIMER3->TCR&=~(1<<0);
	TIMER3->TCR|=(1<<1);
	TIMER2->TCR&=~(1<<0);
	TIMER2->TCR|=(1<<1);
	TIMER3->PR=(PERIPHERAL_CLOCK_FREQUENCY/1000000);
	TIMER2->PR=(PERIPHERAL_CLOCK_FREQUENCY/1000000);
	
	TIMER3->CCR|=(1<<0);
	TIMER2->CCR|=(1<<0);
	TIMER3->CCR&=~(1<<1);
	TIMER2->CCR&=~(1<<1);
	
	TIMER3->TCR&=~(1<<1);
	TIMER3->TCR|=(1<<0);
	TIMER2->TCR&=~(1<<1);
	TIMER2->TCR|=(1<<0);
}