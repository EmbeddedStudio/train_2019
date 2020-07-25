#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_dht11.h"
#include "bsp_usart.h"
#include "core_delay.h"

int main(void)
{
	DHT11_Data_TypeDef      DHT11_Data;
	LED_GPIO_Configuration();            /* 初始化 LED */
	LED_GREEN;
	
	USART_Configuration();               /* 初始化串口，通过串口打印数据 */
	printf("\r\n DHT11 温湿度传感器测试实验 \r\n");
	
	DHT11_Init();                        /* 初始化 DHT11 引脚 */
	while(1)
	{
		if(DHT11_Read_temperature_humidity(& DHT11_Data) == SUCCESS)
		{
			printf("\r\n 温湿度读取成功\r\n");
			printf("\r\n 温度： %d.%d C°",DHT11_Data.temperature_int,DHT11_Data.temperature_deci);
			printf("\r\n 湿度： %d.%d%%",DHT11_Data.humidity_int,DHT11_Data.humidity_deci);
		}
		else
		{
			printf("\r\n 温湿度读取失败，实验失败 \r\n");
			LED_RED;
		}
		
		Delay_ms(2000);                   /* 每 2 秒打印一次数据 */
	}			
}


