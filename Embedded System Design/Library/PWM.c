#include "PWM.h"
#include "GPIO.h"
#include "Parameters.h"
void PWM_Init() {
	//Change the function of the pin in here:
	uint32_t a;
	PCONP |= 1 << 5;
	
	a=LED1_FL;
	a &= ~(7);
	LED1_FL=a;
	
	a=LED2_FR;
	a &= ~(7);
	LED2_FR=a;
	
	a=LED3_BL;
a &= ~(7);
	LED3_BL=a;
	
	a=LED4_BR;
a &= ~(7);
	LED4_BR=a;
	
	a=ENA;
	a &= ~(1 << 2);
	a |=(1<<1)|(1<<0);
	ENA=a;
	
	a=ENB;
	a &= ~(1 << 2);
	a |=(1<<1)|(1<<0);
	ENB=a;
	
	PORT1->DIR|=(1<<5)|(1<<6)|(1<<2)|(1<<3)|(1<<7)|(1<<11);
	
	//Enable PWM output for corresponding pin.
	PWM0 -> PCR |= (1 << 9 | 1 << 10 | 1 << 11 | 1 << 12 | 1 << 13 | 1 << 14);
	
	//Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWM0 -> TCR |= (1 << 1);
	//PWM0->PR=0;
	PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * 20 * 1000;
	
	//Reset TC, when MR0 matches TC.
	PWM0 -> MCR |= (1 << 1);
	
	//Enable PWM Match 0 Latch.
	PWM0 -> LER |= (1 << 0);
	
	//Enable Counter and PWM and Clear Reset on the PWM
	PWM0 -> TCR |= (1 << 0 | 1 << 3);
	PWM0 -> TCR &= ~(1 << 1);

	
	
	PWM_Write(5,0,1);
	PWM_Write(6,0,1);
}

void PWM_Write(uint32_t leds,uint32_t T_ON,uint32_t freqLED) {	
	uint32_t dutyCycle;
	if(T_ON > 100) {
		T_ON = 100;
	}
	dutyCycle =(PWM0 -> MR0 * T_ON) / 100;
	
	if (dutyCycle == PWM0->MR0) {
		dutyCycle--;
	}
	if(leds==1){
		PWM0-> MR1=dutyCycle;
	}
	else if(leds==2){
		PWM0-> MR2=dutyCycle;
	}
	else if(leds==3){
		PWM0-> MR3=dutyCycle;
	}
	else if(leds==4){
		PWM0-> MR4=dutyCycle;
	}
	else if(leds==5){
		PWM0-> MR5=dutyCycle*freqLED;
	}
	else if(leds==6){
		PWM0-> MR6=dutyCycle*freqLED;
	}
	
	
	//Enable PWM Match Register Latch.
	PWM0 -> LER |= (1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6);
}

void LED_Blink(uint32_t freqLED) {
	//Write a formula that changes the MR0 register value for a given parameter.
	PWM0 -> MR0 = (PERIPHERAL_CLOCK_FREQUENCY)/freqLED;
	
	//Enable PWM Match Register Latch for MR0.
	PWM0 -> LER |= (1 << 0);
}
