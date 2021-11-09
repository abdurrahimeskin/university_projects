#ifndef PWM_H
#define PWM_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"
#include "SystemStructures.h"

typedef struct
{
  volatile	uint32_t IR;
  volatile	uint32_t TCR;
  volatile	uint32_t TC;
  volatile	uint32_t PR;
  volatile	uint32_t PC;
  volatile	uint32_t MCR;
  volatile	uint32_t MR0;
  volatile	uint32_t MR1;
  volatile	uint32_t MR2;
  volatile	uint32_t MR3;
  volatile	uint32_t CCR;
  volatile  uint32_t CR0;
  volatile  uint32_t CR1;
  volatile  uint32_t CR2;
  volatile  uint32_t CR3;
						uint32_t RESERVED0;
  volatile	uint32_t MR4;
  volatile	uint32_t MR5;
  volatile	uint32_t MR6;
  volatile	uint32_t PCR;
  volatile	uint32_t LER;
						uint32_t RESERVED1[7];
  volatile	uint32_t CTCR;
} PWM_TypeDef;

//0x00000000 is a dummy value, write the correct address
#define IOCON_LED_ADDRESS_1	0x4002C088	//P1_2(P30)
#define IOCON_LED_ADDRESS_2	0x4002C08C	//P1_3(P29)
#define IOCON_LED_ADDRESS_3	0x4002C098	//P1_6(P27)
#define IOCON_LED_ADDRESS_4	0x4002C094	//P1_5(P28)

#define IOCON_MOTOR_ADDRESS_IN1_1	0x4002C0E0	//P1_24(P5)
#define IOCON_MOTOR_ADDRESS_IN2_1	0x4002C0DC	//P1_23(P6)
#define IOCON_MOTOR_ADDRESS_IN1_2	0x4002C0D0	//P1_20(P7)
#define IOCON_MOTOR_ADDRESS_IN2_2	0x4002C054	//P0_21(P8)
	
#define IN1_1 *((volatile uint32_t*)(IOCON_MOTOR_ADDRESS_IN1_1))
#define IN1_2 *((volatile uint32_t*)(IOCON_MOTOR_ADDRESS_IN1_2))
#define IN2_1 *((volatile uint32_t*)(IOCON_MOTOR_ADDRESS_IN2_1))
#define IN2_2 *((volatile uint32_t*)(IOCON_MOTOR_ADDRESS_IN2_2))

#define LED1_FL	*((volatile uint32_t*)(IOCON_LED_ADDRESS_1))
#define LED2_FR	*((volatile uint32_t*)(IOCON_LED_ADDRESS_2))
#define LED3_BL	*((volatile uint32_t*)(IOCON_LED_ADDRESS_3))
#define LED4_BR *((volatile uint32_t*)(IOCON_LED_ADDRESS_4))

#define IOCON_EN_ADDRESS_A	0x4002C09C	//P1.7(P26)
#define IOCON_EN_ADDRESS_B	0x4002C0AC	//P1.11(P25)

	
#define ENA	*((volatile uint32_t*)(IOCON_EN_ADDRESS_A))
#define ENB	*((volatile uint32_t*)(IOCON_EN_ADDRESS_B))

#define IOCON_MOTOR_SPEED_ADDRESS_1	0x4002C05C
#define IOCON_MOTOR_SPEED_1	*((volatile uint32_t*)(IOCON_MOTOR_SPEED_ADDRESS_1))

#define IOCON_MOTOR_SPEED_ADDRESS_2	0x4002C010
#define IOCON_MOTOR_SPEED_2	*((volatile uint32_t*)(IOCON_MOTOR_SPEED_ADDRESS_2))

#define PWM0_BASE	0x40014000
#define PWM1_BASE	0x40018000

#define PWM0	((PWM_TypeDef*) PWM0_BASE)
#define PWM1	((PWM_TypeDef*) PWM1_BASE)

void PWM_Init(void);
void LED_Blink(uint32_t freqLED);
void PWM_Write(uint32_t leds,uint32_t T_ON,uint32_t freqLED);

#endif
