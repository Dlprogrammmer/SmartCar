#include "stm32f10x.h"
void TCRT5000_Init(void) //IO初始化
{ 
GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTB时钟
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
 //重映射配置关闭JTAG-DP 启用SW-DP从而可以使用PA15 PB3 PB4一些宏定义，利用函数读取电平 
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA15  设置成下拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.15
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_4|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //  设置成下拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB 5 4 3
 }