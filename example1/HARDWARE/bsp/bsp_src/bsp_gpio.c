/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人GPIO初始化文件
 ==============================================================================
  */

/**
 * 12V传感器输入引脚 PE7、PE8、PE9、PE10、PE11
 * 按键输入引脚 PD12、PD13
 * 红外传感器输入引脚 PC1、PC2
 * 12V供电接口控制引脚 PE2 高电平输出
 * 5V供电接口控制引脚 PE3  高电平输出
 * 3.3V供电接口控制引脚 PE4 高电平输出
 * 3.3V信号转换为12V、24V 输出引脚 PA3-12V PA4-12V PA4-24V PA6-24V 
 */

#include "bsp_gpio.h"
#include "gd32f4xx_gpio.h"
void bsp_gpio_init(void)
{
  /* 防跌落红外传感器输入引脚 浮空输入*/
  rcu_periph_clock_enable(RCU_GPIOE);
  gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_7); 	
  gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_8);
  gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_9); 	
  gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_10);  	
  gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_11); 
  /* 按键引脚 浮空输入*/
  rcu_periph_clock_enable(RCU_GPIOD);
  gpio_mode_set(GPIOD, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_12);   
  gpio_mode_set(GPIOD, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_13);  
  /* 控制板12V、5V、3.3V供电接口控制引脚 */
  rcu_periph_clock_enable(RCU_GPIOE);
  gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_2);   
  gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_3);
  gpio_mode_set(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4); 
  gpio_bit_set(GPIOE, GPIO_PIN_2);
  gpio_bit_set(GPIOE, GPIO_PIN_3);
  gpio_bit_set(GPIOE, GPIO_PIN_4);
  /* 控制板12V、24V控制信号输出引脚 */
  rcu_periph_clock_enable(RCU_GPIOA);
  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_3);   
  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_4);
  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_5); 
  gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLDOWN,GPIO_PIN_6);
  gpio_bit_reset(GPIOA, GPIO_PIN_3);
  gpio_bit_reset(GPIOA, GPIO_PIN_4);
  gpio_bit_reset(GPIOA, GPIO_PIN_5);
  gpio_bit_reset(GPIOA, GPIO_PIN_6);
}