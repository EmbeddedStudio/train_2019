#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_dht11.h"
#include "bsp_usart.h"
#include "core_delay.h"

int main(void)
{
	DHT11_Data_TypeDef      DHT11_Data;
	LED_GPIO_Configuration();            /* ��ʼ�� LED */
	LED_GREEN;
	
	USART_Configuration();               /* ��ʼ�����ڣ�ͨ�����ڴ�ӡ���� */
	printf("\r\n DHT11 ��ʪ�ȴ���������ʵ�� \r\n");
	
	DHT11_Init();                        /* ��ʼ�� DHT11 ���� */
	while(1)
	{
		if(DHT11_Read_temperature_humidity(& DHT11_Data) == SUCCESS)
		{
			printf("\r\n ��ʪ�ȶ�ȡ�ɹ�\r\n");
			printf("\r\n �¶ȣ� %d.%d C��",DHT11_Data.temperature_int,DHT11_Data.temperature_deci);
			printf("\r\n ʪ�ȣ� %d.%d%%",DHT11_Data.humidity_int,DHT11_Data.humidity_deci);
		}
		else
		{
			printf("\r\n ��ʪ�ȶ�ȡʧ�ܣ�ʵ��ʧ�� \r\n");
			LED_RED;
		}
		
		Delay_ms(2000);                   /* ÿ 2 ���ӡһ������ */
	}			
}


