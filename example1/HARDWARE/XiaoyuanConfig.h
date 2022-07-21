/**
  ******************************************************************************
  * @file    XiaoyuanConfig.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人底层配置文件
 ==============================================================================
 */


#ifndef __XIAOYUANCONFIG_H
#define __XIAOYUANCONFIG_H
	
#include "gd32f4xx.h"

/**
 * ****************************************************************************
 * 控制板软件版本信息
 * ****************************************************************************
 */
#define SOFTWARE_VERSION                   "V1.0.0"       /* 当前软件版本 */
#define HARDWARE_VERSION                   "V1.0.0"       /* 当前硬件版本 */
/**
 * ****************************************************************************
 * Module 配置，用于配置模块
 * ****************************************************************************
 */


#define LOG_USART	                         USART0    /* LOG 信息输出串口 */
#define PRINTF_USART	                     USART0    /* LOG 信息输出串口 */

#define TASK_TIMER                         TIMER1    /* 任务所用定时器为定时器1 */


/**
 * ****************************************************************************
 * 日志输出配置
 * ****************************************************************************
 */
#define LOG_BUF_SIZE                       200   /* 每条日志输出的缓存区的大小 */
#define LOG_BY_USART                       1     /* 通过串口输出日志 */
#define LOG_BY_NET                         0     /* 通过网络输出日志 */
#define LOG_OUTPUT                         1     /* 日志输出 1：允许 0：禁止 */
#define LOG_OUTPUT_LEVEL                   0     /* 日志输出等级：大于或等于该等级的日志可以输出 */
#define LOG_CONTENT_LEVEL                  0     /* 日志输出是否包含等级名称 1：包含 0：不包含 */ 
#define LOG_CONTENT_TAG                    0     /* 日志输出是否包含标签名称 1：包含 0：不包含 */ 
#define LOG_CONTENT_FILE                   0     /* 日志输出是否包含文件名称 1：包含 0：不包含 */ 
#define LOG_CONTENT_FUNC                   0     /* 日志输出是否包含函数名称 1：包含 0：不包含 */ 
#define LOG_CONTENT_LINE                   0     /* 日志输出是否包含行号名称 1：包含 0：不包含 */ 
/**
 * ****************************************************************************
 * BSP 配置，用于底层文件
 * ****************************************************************************
 */


/* USART 端口配置
   总共右6个串口 其中 USART0、 USART5 挂在APB2上
   USART1、 USART2、 USART3、 USART4 挂在APB1上
*/

/* USART0 配置 管脚PA9、PA10、波特率115200 8数据位、1停止位、无奇偶校验位 */
#define USART0_BAUDRATE                    115200  

#define USART0_RX_GPIO_PORT                GPIOA
#define USART0_RX_GPIO_CLK                 RCU_GPIOA
#define USART0_RX_PIN                      GPIO_PIN_10


#define USART0_TX_GPIO_PORT                GPIOA
#define USART0_TX_GPIO_CLK                 RCU_GPIOA
#define USART0_TX_PIN                      GPIO_PIN_9


/* USART1 配置 管脚PA2、PA3、波特率115200*/
#define USART1_BAUDRATE                    115200  

#define USART1_RX_GPIO_PORT                GPIOD
#define USART1_RX_GPIO_CLK                 RCU_GPIOD
#define USART1_RX_PIN                      GPIO_PIN_6


#define USART1_TX_GPIO_PORT                GPIOD
#define USART1_TX_GPIO_CLK                 RCU_GPIOD
#define USART1_TX_PIN                      GPIO_PIN_5


/* USART2 配置 管脚PB10、PB11、波特率115200 8数据位、1停止位、无奇偶校验位 
   USART2 作为 SBUS数据的接收引脚
   SBUS 的通信协议：1起始位+8数据位+偶校验位+2停止位 波特率100K 但是实际设置的时候
   需要设置2停止位可以正常接收数据
*/
#define USART2_BAUDRATE                    100000  

#define USART2_RX_GPIO_PORT                GPIOD
#define USART2_RX_GPIO_CLK                 RCU_GPIOD
#define USART2_RX_PIN                      GPIO_PIN_9

#define USART2_TX_GPIO_PORT                GPIOB
#define USART2_TX_GPIO_CLK                 RCU_GPIOB
#define USART2_TX_PIN                      GPIO_PIN_10

/* USART3 配置 管脚PC10、PC11、波特率115200 8数据位、1停止位、无奇偶校验位 */
#define USART3_BAUDRATE                    115200  

#define USART3_RX_GPIO_PORT                GPIOC
#define USART3_RX_GPIO_CLK                 RCU_GPIOC
#define USART3_RX_PIN                      GPIO_PIN_11

#define USART3_TX_GPIO_PORT                GPIOC
#define USART3_TX_GPIO_CLK                 RCU_GPIOC
#define USART3_TX_PIN                      GPIO_PIN_10


/* USART4 配置 管脚PC12、PD2、波特率115200 8数据位、1停止位、无奇偶校验位 */
#define USART4_BAUDRATE                    115200  

#define USART4_RX_GPIO_PORT                GPIOD
#define USART4_RX_GPIO_CLK                 RCU_GPIOD
#define USART4_RX_PIN                      GPIO_PIN_2

#define USART4_TX_GPIO_PORT                GPIOC
#define USART4_TX_GPIO_CLK                 RCU_GPIOC
#define USART4_TX_PIN                      GPIO_PIN_12


/* USART5 配置 管脚PC6、PC7、波特率115200 8数据位、1停止位、无奇偶校验位 */
#define USART5_BAUDRATE                    115200  

#define USART5_RX_GPIO_PORT                GPIOC
#define USART5_RX_GPIO_CLK                 RCU_GPIOC
#define USART5_RX_PIN                      GPIO_PIN_7

#define USART5_TX_GPIO_PORT                GPIOC
#define USART5_TX_GPIO_CLK                 RCU_GPIOC
#define USART5_TX_PIN                      GPIO_PIN_6


/*   CAN 口配置 CAN的输入频率为42M
 *  1000  ：1M波特率
 *  500   ：500K波特率 
 *  250   ：250K波特率
 *  125   ：125K波特率 
 */



/* CAN0配置 PB8 RX PB9 TX */

#define CAN0_BAUDRATE                      500  
#define CAN0_RX_PIN                        GPIO_PIN_8
#define CAN0_TX_PIN                        GPIO_PIN_9
#define CAN0_TX_GPIO_PORT                  GPIOB
#define CAN0_RX_GPIO_PORT                  GPIOB
#define CAN0_TX_GPIO_CLK                   RCU_GPIOB
#define CAN0_RX_GPIO_CLK                   RCU_GPIOB

/* CAN1配置 PB5 RX PB6 TX*/

#define CAN1_BAUDRATE                      500  
#define CAN1_RX_PIN                	       GPIO_PIN_5
#define CAN1_TX_PIN                        GPIO_PIN_6
#define CAN1_TX_GPIO_PORT                  GPIOB
#define CAN1_RX_GPIO_PORT                  GPIOB
#define CAN1_TX_GPIO_CLK                   RCU_GPIOB
#define CAN1_RX_GPIO_CLK                   RCU_GPIOB

/* 定时器配置 定时器的输入时钟频率为168M*/
/* 定时器1配置 重装值1000 预分频系数168 1ms一次中断 */
#define TIM1_ARR                           1000    /* 自动重装值 */
#define TIM1_PSC                           168     /* 预分频系数 */

/* 中断重映射 */
#define timeisr                            TIMER1_IRQHandler     /* task 的轮询定时器映射到定时器1中断 */
#endif






