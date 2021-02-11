#ifndef _BSP_DHT11_H
#define _BSP_DHT11_H

#include "stm32f10x.h"
#include "stdio.h"
#include "bsp_delay.h"

#define           DHT11_Data_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define           DHT11_Data_GPIO_CLK                RCC_APB2Periph_GPIOB
#define           DHT11_Data_GPIO_PORT               GPIOB
#define           DHT11_Data_GPIO_PIN                GPIO_Pin_9

/* 函数宏定义 */
#define           DHT11_Dout_1                 GPIO_SetBits(DHT11_Data_GPIO_PORT, DHT11_Data_GPIO_PIN)             /* Data 引脚置高电平 */
#define           DHT11_Dout_0                 GPIO_ResetBits(DHT11_Data_GPIO_PORT, DHT11_Data_GPIO_PIN)           /* Data 引脚置低电平 */

#define           DHT11_Dout_IN()              GPIO_ReadInputDataBit(DHT11_Data_GPIO_PORT, DHT11_Data_GPIO_PIN)    /* 输入状态 */

typedef struct
{
	uint8_t humidity_deci;                     // 湿度小数位
	uint8_t humidity_int;                      // 湿度整数位
	
	uint8_t temperature_deci;                  // 温度小数位
	uint8_t temperature_int;                   // 温度整数位
	
	uint8_t check_sum;                         // 数据校验
	
}DHT11_Data_TypeDef;

/* 函数声明 */
void DHT11_Init(void);
uint8_t DHT11_Read_temperature_humidity(DHT11_Data_TypeDef  *DHT11_Data);

#endif /* _BSP_DHT11_H*/


