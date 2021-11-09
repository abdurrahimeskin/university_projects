#include "LPC407x_8x_177x_8x.h"

#include "Library/GPIO.h"
#include "Library/Joystick.h"
#include "Library/PWM.h"
#include "Library/LED.h"
#include "Library/Ultrasonic.h"
#include "Library/Timer.h"
#include "Library/Parameters.h"
#include "Library/Wait.h"


#include <time.h>
#include <stdio.h>


uint32_t old1,new1,count1,speed1,old2,new2,count2,speed2 = 0;
uint64_t start_t=0;
int TURN_LEFT_FLAG,TURN_RIGHT_FLAG,BACKWARD_FLAG,FORWARD_FLAG =0;
int isFirst=0;
int isRightOpen,isLeftOpen = 0;
void Motor_Init(){
IN1_1 &=~(7);
IN2_1 &=~(7);
IN1_2 &=~(7);
IN2_2 &=~(7);
PORT1->DIR|=(1<<20)|(1<<23)|(1<<24);
PORT0->DIR|=(1<<21);

}

void init() {
	
	PWM_Init();
	
	Joystick_Init();
	
	Motor_Init();
	
	speed_init();
	
	Timer_Init();
	
	
}

void motor_forward(){
	GPIO_PIN_Write(PORT1, (1<<24), LOW); 			// IN1_1 = 1
	GPIO_PIN_Write(PORT1, (1<<23), HIGH); 		// IN2_1 = 0
	GPIO_PIN_Write(PORT1, (1<<20), LOW); 			// IN1_2 = 1
	GPIO_PIN_Write(PORT0, (1<<21), HIGH); 		// IN2_2 = 0
	
	PWM_Write(5,ROBOT_SPEED,1);
	PWM_Write(6,ROBOT_SPEED,1);
	
}
void motor_backward(){
	GPIO_PIN_Write(PORT1, (1<<24), HIGH); 			// IN1_1 = 0
	GPIO_PIN_Write(PORT1, (1<<23), LOW); 		// IN2_1 = 1
	GPIO_PIN_Write(PORT1, (1<<20), HIGH); 			// IN1_2 = 0
	GPIO_PIN_Write(PORT0, (1<<21), LOW); 		// IN2_2 = 1
	
	PWM_Write(5,ROBOT_SPEED,1);
	PWM_Write(6,ROBOT_SPEED,1);
	
}

void motor_ccw(){
	
	GPIO_PIN_Write(PORT1, (1<<24), LOW); 			// IN1_1 = 1
	GPIO_PIN_Write(PORT1, (1<<23), HIGH); 		// IN2_1 = 0
	GPIO_PIN_Write(PORT1, (1<<20), HIGH); 			// IN1_2 = 1
	GPIO_PIN_Write(PORT0, (1<<21), LOW); 		// IN2_2 = 0
	
	PWM_Write(5,ROBOT_SPEED,1);
	PWM_Write(6,ROBOT_SPEED,1);
	
}

void motor_cw(){

	GPIO_PIN_Write(PORT1, (1<<24), HIGH); 			// IN1_1 = 1
	GPIO_PIN_Write(PORT1, (1<<23), LOW); 		// IN2_1 = 0
	GPIO_PIN_Write(PORT1, (1<<20), LOW); 			// IN1_2 = 1
	GPIO_PIN_Write(PORT0, (1<<21), HIGH); 		// IN2_2 = 0
	
	PWM_Write(5,ROBOT_SPEED,1);
	PWM_Write(6,ROBOT_SPEED,1);
	
}
void motor_stop(){
	PWM_Write(6,ROBOT_SPEED,1);
	GPIO_PIN_Write(PORT1, (1<<24), LOW); 			// IN1_1 = 0
	GPIO_PIN_Write(PORT1, (1<<23), LOW); 		// IN2_1 = 0
	GPIO_PIN_Write(PORT1, (1<<20), LOW); 			// IN1_2 = 0
	GPIO_PIN_Write(PORT0, (1<<21), LOW); 		// IN2_2 = 0
	
	PWM_Write(5,ROBOT_SPEED,1);
	
}

void speed_calc1(){

	if(TIMER3->CR0!=old1){
		new1=TIMER3->CR0;
		count1 ++;
		if(count1%2==0){
			if(count1>2){
				speed1 = new1 - old1;
			}
			TIMER3->CCR|=(1<<0);
			TIMER3->CCR&=~(1<<1);
		}else{
		
		TIMER3->CCR|=(1<<1);
		TIMER3->CCR&=~(1<<0);
		
		}
	old1=new1;
	}
	if((count1/2)>ROTATION_NUMBER_FOR_90_DEGREE&&TURN_RIGHT_FLAG == 1){
		TURN_RIGHT_FLAG = 0;
		PORT1->PIN &= ~(1<<2);
		PORT1->PIN  &= ~ (1<<3);
		PORT1->PIN  &= ~ (1<<5);
		PORT1->PIN  &= ~ (1<<6);
		
		motor_stop();
	}
}

void speed_calc2(){

	if(TIMER2->CR0!=old2){
		new2=TIMER2->CR0;
		count2 ++;
		if(count2%2==0){
			if(count2>2){
				speed2 = new2 - old2;
			}
			TIMER2->CCR|=(1<<0);
			TIMER2->CCR&=~(1<<1);
		}else{
		
		TIMER2->CCR|=(1<<1);
		TIMER2->CCR&=~(1<<0);
		
		}
	old2=new2;
	}
	if((count2/2)>ROTATION_NUMBER_FOR_90_DEGREE&&TURN_LEFT_FLAG == 1){
		TURN_LEFT_FLAG = 0;
	  PORT1->PIN &= ~(1<<2);
		PORT1->PIN  &= ~ (1<<3);
		PORT1->PIN  &= ~ (1<<5);
		PORT1->PIN  &= ~ (1<<6);
		motor_stop();
	}
}
	

void update() {
	speed_calc1();
	speed_calc2();
	
	if(TURN_RIGHT_FLAG){
				int i =0;
				if(isRightOpen){
					wait(250);
					uint32_t value=PORT1->PIN;
					value &= ~ (1<<2);
					value  &= ~ (1<<3);
					value  &= ~ (1<<5);
					value  &= ~ (1<<6);
					PORT1->PIN=value;
					isRightOpen = 0;
				}else{
					wait(250);
					uint32_t value=PORT1->PIN;
					value |= (1<<3);
					value  &= ~ (1<<2);
					value  |= (1<<6);
					value  &= ~ (1<<5);
					PORT1->PIN=value;
					isRightOpen = 1;
				}		
			
	}
		if(TURN_LEFT_FLAG){
				int i =0;
				if(isLeftOpen){
					wait(250);
					uint32_t value=PORT1->PIN;
					value &= ~ (1<<2);
					value  &= ~ (1<<3);
					value  &= ~ (1<<5);
					value  &= ~ (1<<6);
					PORT1->PIN=value;
					isLeftOpen = 0;
				}else{
					wait(250);
					uint32_t value=PORT1->PIN;
					value |= (1<<2);
					value  &= ~ (1<<3);
					value  |= (1<<5);
					value  &= ~ (1<<6);
					PORT1->PIN=value;
					isLeftOpen = 1;
				}		
			
	}

	if (Joystick_Up_Pressed()) {
		isFirst =1;
		
		TURN_LEFT_FLAG = 0;
		TURN_RIGHT_FLAG = 0;
		FORWARD_FLAG = 1;
		BACKWARD_FLAG = 0;
		uint32_t value=PORT1->PIN;
		value |= (1<<2);
		value  |= (1<<3);
		value  &= ~ (1<<5);
		value  &= ~ (1<<6);
		PORT1->PIN=value;
		motor_forward();
		
	}
	else if (Joystick_Center_Pressed()) {
		isFirst =1;
		TURN_LEFT_FLAG = 0;
		TURN_RIGHT_FLAG = 0;
		FORWARD_FLAG = 0;
		BACKWARD_FLAG = 0;
	
		uint32_t value=PORT1->PIN;
		value &= ~ (1<<2);
		value  &= ~ (1<<3);
		value  &= ~ (1<<5);
		value  &= ~ (1<<6);
		PORT1->PIN=value;
		motor_stop();
		
	}
	else if (Joystick_Left_Pressed()) {
		
		
		if(isFirst!=0){
		isLeftOpen = 1;
		TURN_LEFT_FLAG = 1;
		TURN_RIGHT_FLAG = 0;
		FORWARD_FLAG = 0;
		BACKWARD_FLAG = 0;
		
		uint32_t value=PORT1->PIN;
		value |= (1<<2);
		value  &= ~ (1<<3);
		value  |= (1<<5);
		value  &= ~ (1<<6);
		PORT1->PIN=value;
		
		count1=0;
		count2=0;
		motor_ccw();
		}
	}
	else if (Joystick_Down_Pressed()) {
		if(isFirst!=0){
		TURN_LEFT_FLAG = 0;
		TURN_RIGHT_FLAG = 0;
		FORWARD_FLAG = 0;
		BACKWARD_FLAG = 1;
	
		uint32_t value=PORT1->PIN;
		value &= ~ (1<<2);
		value  &= ~ (1<<3);
		value  |= (1<<5);
		value  |= (1<<6);
		PORT1->PIN=value;
		motor_backward();
	}	
	}
	else if (Joystick_Right_Pressed()) {
		
		isRightOpen = 1;
		isFirst =1;
		TURN_LEFT_FLAG = 0;
		TURN_RIGHT_FLAG = 1;
		FORWARD_FLAG = 0;
		BACKWARD_FLAG = 0;
		uint32_t value=PORT1->PIN;
		value &= ~ (1<<2);
		value  |=  (1<<3);
		value  &= ~ (1<<5);
		value  |= (1<<6);
		PORT1->PIN=value;
		count1=0;
		count2=0;
		motor_cw();
		
		
	}
	
}

int main() {
	init();
	motor_stop();
	while(1) {
		update();
	}
}