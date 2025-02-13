#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx.h"

#define LED_RED_GPIO_PIN    GPIO_Pin_6
#define LED_RED_GPIO_PORT   GPIOF
#define LED_RED_GPIO_CLK    RCC_AHB1Periph_GPIOF

#define LED_GREEN_GPIO_PIN    GPIO_Pin_7
#define LED_GREEN_GPIO_PORT   GPIOF
#define LED_GREEN_GPIO_CLK    RCC_AHB1Periph_GPIOF

#define LED_BLUE_GPIO_PIN    GPIO_Pin_8
#define LED_BLUE_GPIO_PORT   GPIOF
#define LED_BLUE_GPIO_CLK    RCC_AHB1Periph_GPIOF

#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED_BLUE_GPIO_PORT,LED_BLUE_GPIO_PIN);\
					else		\
					GPIO_ResetBits(LED_BLUE_GPIO_PORT,LED_BLUE_GPIO_PIN)

#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)
#define LED1_OFF			digitalHi(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)
#define LED1_ON				digitalLo(LED_RED_GPIO_PORT,LED_RED_GPIO_PIN)

#define LED2_TOGGLE		digitalToggle(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)
#define LED2_OFF			digitalHi(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)
#define LED2_ON				digitalLo(LED_GREEN_GPIO_PORT,LED_GREEN_GPIO_PIN)

#define LED3_TOGGLE		digitalToggle(LED_BLUE_GPIO_PORT,LED_BLUE_GPIO_PIN)
#define LED3_OFF			digitalHi(LED_BLUE_GPIO_PORT,LED_BLUE_GPIO_PIN)
#define LED3_ON				digitalLo(LED_BLUE_GPIO_PORT,LED_BLUE_GPIO_PIN)

//红
#define LED_RED  \
					LED1_ON;\
					LED2_OFF;\
					LED3_OFF

//绿
#define LED_GREEN		\
					LED1_OFF;\
					LED2_ON;\
					LED3_OFF

//蓝
#define LED_BLUE	\
					LED1_OFF;\
					LED2_OFF;\
					LED3_ON

					
//黄(红+绿)					
#define LED_YELLOW	\
					LED1_ON;\
					LED2_ON;\
					LED3_OFF
//紫(红+蓝)
#define LED_PURPLE	\
					LED1_ON;\
					LED2_OFF;\
					LED3_ON

//青(绿+蓝)
#define LED_CYAN \
					LED1_OFF;\
					LED2_ON;\
					LED3_ON
					
//白(红+绿+蓝)
#define LED_WHITE	\
					LED1_ON;\
					LED2_ON;\
					LED3_ON
					
//黑(全部关闭)
#define LED_RGBOFF	\
					LED1_OFF;\
					LED2_OFF;\
					LED3_OFF		




void LED_GPIO_Config(void);


#endif