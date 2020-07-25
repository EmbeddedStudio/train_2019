#ifndef __LED_H
#define	__LED_H


#include "stm32f10x.h"


/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
// R-红色
#define LED_R_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define LED_R_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED_R_GPIO_PIN		  GPIO_Pin_5			        /* 连接到SCL时钟线的GPIO */

// G-绿色
#define LED_G_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define LED_G_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED_G_GPIO_PIN		  GPIO_Pin_0			        /* 连接到SCL时钟线的GPIO */

// B-蓝色
#define LED_B_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define LED_B_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED_B_GPIO_PIN		  GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 使用标准的固件库控制IO*/
#define LED_R(a)	if (a)	\
					GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LED_G(a)	if (a)	\
					GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LED_B(a)	if (a)	\
					GPIO_SetBits(LED_B_GPIO_PORT,LED_B_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_B_GPIO_PORT,LED_B_GPIO_PIN)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态


/* 定义控制IO的宏 */
#define LED_R_TOGGLE		 digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_R_OFF		   digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_R_ON			   digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LED_G_TOGGLE		 digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_OFF		   digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_G_ON			   digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LED_B_TOGGLE		 digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_OFF		   digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_B_ON			   digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)

/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
					LED_R_ON;\
					LED_G_OFF\
					LED_B_OFF

//绿
#define LED_GREEN		\
					LED_R_OFF;\
					LED_G_ON\
					LED_B_OFF

//蓝
#define LED_BLUE	\
					LED_R_OFF;\
					LED_G_OFF\
					LED_B_ON

					
//黄(红+绿)					
#define LED_YELLOW	\
					LED_R_ON;\
					LED_G_ON\
					LED_B_OFF
//紫(红+蓝)
#define LED_PURPLE	\
					LED_R_ON;\
					LED_G_OFF\
					LED_B_ON

//青(绿+蓝)
#define LED_CYAN \
					LED_R_OFF;\
					LED_G_ON\
					LED_B_ON
					
//白(红+绿+蓝)
#define LED_WHITE	\
					LED_R_ON;\
					LED_G_ON\
					LED_B_ON
					
//黑(全部关闭)
#define LED_RGBOFF	\
					LED_R_OFF;\
					LED_G_OFF\
					LED_B_OFF

void LED_GPIO_Configuration(void);

#endif /* __LED_H */
