#ifndef __AMCONFIG_H
#define __AMCONFIG_H
	
#include "gd32f4xx.h"

/* 定时器4配置 定时器的输入时钟频率为200M*/
/* 定时器4配置 重装值1000 预分频值199+1 1ms一次中断 用于Ethercat */
#define TIM4_CAR                           1000     /* 自动重装值 */
#define TIM4_PSC                           199      /* 预分频系数 */


/* SPI3 配置 主机模式，全双工，8位帧格式，传输高位在前，空闲时位低电平，对第一个时钟边沿采样 */

#define SPI3_CS_GPIO                         GPIO_PIN_4               /* SPI3 CS信号引脚定义*/
#define SPI3_CS_GPIO_PORT                    GPIOE                    /* SPI3 CS信号端口定义*/
#define SPI3_CS_GPIO_CLK                     RCU_GPIOE                /* SPI3 CS信号端口时钟定义*/

#define SPI3_MISO_GPIO                       GPIO_PIN_5               /* SPI3 MISO信号引脚定义*/
#define SPI3_MISO_GPIO_PORT                  GPIOE                    /* SPI3 MISO信号端口定义*/
#define SPI3_MISO_GPIO_CLK                   RCU_GPIOE                /* SPI3 MISO信号端口时钟定义*/

#define SPI3_MOSI_GPIO                       GPIO_PIN_6               /* SPI3 MOSI信号引脚定义*/
#define SPI3_MOSI_GPIO_PORT                  GPIOE                    /* SPI3 MOSI信号端口定义*/
#define SPI3_MOSI_GPIO_CLK                   RCU_GPIOE                /* SPI3 MOSI信号端口时钟定义*/

#define SPI3_SCK_GPIO                        GPIO_PIN_2               /* SPI3 SCK信号引脚定义*/
#define SPI3_SCK_GPIO_PORT                   GPIOE                    /* SPI3 SCK信号端口定义*/
#define SPI3_SCK_GPIO_CLK                    RCU_GPIOE                /* SPI3 SCK信号端口时钟定义*/




#endif






