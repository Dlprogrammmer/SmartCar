#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include "Serial.h"
extern int g_USART1_FLAG1;
u8 USART_RX_BUF[255];     //接收缓冲,最大USART_REC_LEN个字节.
 //接收状态
//bit15，    接收完成标志
//bit14，    接收到0x0d
 //bit13~0，  接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记  
void Serial_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

 void USART1_IRQHandler(void)                    //串口1中断服务程序
 {
    u8 Res;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
        {
        Res =USART_ReceiveData(USART1); //读取接收到的数据
            if(Res == 'A') g_USART1_FLAG1 = 1 ; //根据接受的数据 置为标志位
            if(Res == 'B')g_USART1_FLAG1 = 2 ;
        if((USART_RX_STA&0x8000)==0)//接收未完成
            {
            if(USART_RX_STA&0x4000)//接收到了0x0d
                {
                if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
                else USART_RX_STA|=0x8000;  //接收完成了 
                }
            else //还没收到0X0D
                {   
                if(Res==0x0d)USART_RX_STA|=0x4000;
                else
                    {
                    USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
                    USART_RX_STA++;
                    if(USART_RX_STA>(255-1))USART_RX_STA=0;//接收数据错误,重新开始接收      
                    }        
                }
            }            
     } 
 } 