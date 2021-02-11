#include "bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Configuration(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED_R_GPIO_CLK | LED_G_GPIO_CLK | LED_B_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_R_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStructure);

		/* �ر�����led��	*/
		GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
		
		/* �ر�����led��	*/
		GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);	 
    
    /* �ر�����led��	*/
		GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
}

void assert_failed(uint8_t* file, uint32_t line)
{
	// ���Դ���ʱִ�еĴ���
	LED_R_ON;
}








