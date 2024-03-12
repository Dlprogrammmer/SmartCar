#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "TB6612.h"
void  Motor_Init(uint16_t arr,uint16_t psc)
{
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period =arr;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	//初始化TIM1通道1
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	//初始化TIM1通道4
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	TIM_Cmd(TIM1 , ENABLE);
	//使能高级定时器
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
void Forward(void)
{
	AIN1=1;
	AIN2=0;
	BIN1=1;
	BIN2=0;
	TIM_SetCompare1(TIM1,500);
	TIM_SetCompare4(TIM1,500);
}
void Backward(void)
{
	AIN1=0;
	AIN2=1;
	BIN1=0;
	BIN2=1;
	TIM_SetCompare1(TIM1,500);
	TIM_SetCompare4(TIM1,500);
}
void Rightward(void)
{
	AIN1=1;
	AIN2=0;
	BIN1=0;
	BIN2=1;
	TIM_SetCompare1(TIM1,500);
	TIM_SetCompare4(TIM1,500);
}
void Leftward(void)
{
	AIN1=0;
	AIN2=1;
	BIN1=1;
	BIN2=0;
	TIM_SetCompare1(TIM1,500);
	TIM_SetCompare4(TIM1,500);
}