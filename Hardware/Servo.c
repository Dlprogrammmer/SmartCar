#include "stm32f10x.h"                  // Device header
void Servo_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=0;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period =999;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler =1439;		//PSC
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	//初始化TIM1
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity =  TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_Cmd(TIM3 , ENABLE);
}  
void Servo_left(void)
{
	TIM_SetCompare1(TIM3,32);    
	delay_ms(900);
}
void Servo_right(void)
{
	 TIM_SetCompare1(TIM3,130);    
	delay_ms(900);
}
void Servo_front(void)
{
	TIM_SetCompare1(TIM3,80); //舵机向左 
	delay_ms(900);
}
void Servo_Stop(void)
{
	TIM_SetCompare1(TIM3,80); //舵机向左 
	delay_ms(900);
}