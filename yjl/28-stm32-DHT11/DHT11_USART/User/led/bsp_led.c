#include "bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Configuration(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( LED_R_GPIO_CLK | LED_G_GPIO_CLK | LED_B_GPIO_CLK, ENABLE);
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED_R_GPIO_PIN;	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStructure);

		/* 关闭所有led灯	*/
		GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
		
		/* 关闭所有led灯	*/
		GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);	 
    
    /* 关闭所有led灯	*/
		GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	// 断言错误时执行的代码
	LED_R_ON;
}








