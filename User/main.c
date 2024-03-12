#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Bluetooth.h"
#include "TB6612.h"
#include "sys.h"
int g_USART1_FLAG1 = 0;
int g_USART3_FLAG1 =0; 
int main(void)
{
	OLED_Init();
	OLED_Clear();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"HelloWorld!");
	OLED_ShowNum(2,1,12345,5);
	OLED_ShowSignedNum(2,7,-66,2);
	OLED_ShowHexNum(3,1,0xAA55,4);
	OLED_ShowBinNum(4,1,0xAA55,16);
	while(1)
	{
	if(g_USART3_FLAG1 == 1)  //前进
	{
		g_USART3_FLAG1=0;
        Forward();
        delay_ms(500);
    }
    if(g_USART3_FLAG1 == 2)  //向右
    {
		g_USART3_FLAG1=0;
        Rightward();
        delay_ms(500);
     }
	if(g_USART3_FLAG1 ==3)  //向左
    {
		g_USART3_FLAG1=0;
        Leftward();
        delay_ms(500);
    }
    if(g_USART3_FLAG1 ==4)  //向后
    {
		g_USART3_FLAG1=0;
        
        delay_ms(500);
    }
    if(g_USART3_FLAG1 ==5)  //停止
	{
        g_USART3_FLAG1=0;
        AIN1=0;
        AIN2=0;
        BIN1=0;
        BIN2=0;
        delay_ms(500);
     }
	}
}
