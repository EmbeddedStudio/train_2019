#ifndef _BSP_DHT11_H
#define _BSP_DHT11_H

#include "stm32f10x.h"
#include "stdio.h"
#include "bsp_delay.h"

#define           DHT11_Data_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define           DHT11_Data_GPIO_CLK                RCC_APB2Periph_GPIOB
#define           DHT11_Data_GPIO_PORT               GPIOB
#define           DHT11_Data_GPIO_PIN                GPIO_Pin_9

/* �����궨�� */
#define           DHT11_Dout_1                 GPIO_SetBits(DHT11_Data_GPIO_PORT, DHT11_Data_GPIO_PIN)             /* Data �����øߵ�ƽ */
#define           DHT11_Dout_0                 GPIO_ResetBits(DHT11_Data_GPIO_PORT, DHT11_Data_GPIO_PIN)           /* Data �����õ͵�ƽ */

#define           DHT11_Dout_IN()              GPIO_ReadInputDataBit(DHT11_Data_GPIO_PORT, DHT11_Data_GPIO_PIN)    /* ����״̬ */

typedef struct
{
	uint8_t humidity_deci;                     // ʪ��С��λ
	uint8_t humidity_int;                      // ʪ������λ
	
	uint8_t temperature_deci;                  // �¶�С��λ
	uint8_t temperature_int;                   // �¶�����λ
	
	uint8_t check_sum;                         // ����У��
	
}DHT11_Data_TypeDef;

/* �������� */
void DHT11_Init(void);
uint8_t DHT11_Read_temperature_humidity(DHT11_Data_TypeDef  *DHT11_Data);

#endif /* _BSP_DHT11_H*/


