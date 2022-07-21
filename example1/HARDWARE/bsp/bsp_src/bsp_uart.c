/**
  ******************************************************************************
  * @file    bsp_uart.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人串口操作的底层文件
 ==============================================================================
 */

#include "XiaoyuanConfig.h"
#include "gd32f4xx.h"
#include "gd32f4xx_usart.h"
#include "gd32f4xx_gpio.h"
#include "bsp_uart.h"
/**
  * @brief  串口0初始化
  * @param  None
  * @retval None
  */

void bsp_usart0_init()
{
	/* 使能RX时钟 */
	rcu_periph_clock_enable( USART0_RX_GPIO_CLK);

	/* 使能TX时钟 */
	rcu_periph_clock_enable( USART0_TX_GPIO_CLK);

	/* 使能串口1时钟 */
	rcu_periph_clock_enable(RCU_USART0);

	/* 设置TX管脚的复用功能 */
	gpio_af_set(USART0_TX_GPIO_PORT, GPIO_AF_7, USART0_TX_PIN);

	/* 设置RX管脚的复用功能 */
	gpio_af_set(USART0_RX_GPIO_PORT, GPIO_AF_7, USART0_RX_PIN);

	/* 配置TX管脚 复用模式、上拉*/
	gpio_mode_set(USART0_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART0_TX_PIN);
	gpio_output_options_set(USART0_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART0_TX_PIN);

	/* 配置RX管脚 复用模式、上拉*/
	gpio_mode_set(USART0_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART0_RX_PIN);
	gpio_output_options_set(USART0_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART0_RX_PIN);

	/* USART 配置 8数据位、1停止位、无奇偶校验位 */
	usart_deinit(USART0);
	usart_baudrate_set(USART0,USART0_BAUDRATE); 
	usart_parity_config(USART0,USART_PM_NONE); 
	usart_word_length_set(USART0,USART_WL_8BIT);
	usart_stop_bit_set(USART0, USART_STB_1BIT);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE); 
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	usart_enable(USART0);	
}


/**
  * @brief  串口1初始化
  * @param  None
  * @retval None
  */
void bsp_usart1_init()
{
	/* 使能RX时钟 */
	rcu_periph_clock_enable( USART1_RX_GPIO_CLK);

	/* 使能TX时钟 */
	rcu_periph_clock_enable( USART1_TX_GPIO_CLK);

	/* 使能串口1时钟 */
	rcu_periph_clock_enable(RCU_USART1);

	/* 设置TX管脚的复用功能 */
	gpio_af_set(USART1_TX_GPIO_PORT, GPIO_AF_7, USART1_TX_PIN);

	/* 设置RX管脚的复用功能 */
	gpio_af_set(USART1_RX_GPIO_PORT, GPIO_AF_7, USART1_RX_PIN);

	/* 配置TX管脚 复用模式、上拉*/
	gpio_mode_set(USART1_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART1_TX_PIN);
	gpio_output_options_set(USART1_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART1_TX_PIN);

	/* 配置RX管脚 复用模式、上拉*/
	gpio_mode_set(USART1_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART1_RX_PIN);
	gpio_output_options_set(USART1_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART1_RX_PIN);

	/* USART 配置 8数据位、1停止位、无奇偶校验位 */
	usart_deinit(USART1);
	usart_baudrate_set(USART1,USART1_BAUDRATE); 
	usart_parity_config(USART1,USART_PM_NONE); 
	usart_word_length_set(USART1,USART_WL_8BIT);
	usart_stop_bit_set(USART1, USART_STB_1BIT);
	usart_receive_config(USART1, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART1, USART_TRANSMIT_ENABLE); 
	usart_interrupt_enable(USART1, USART_INT_RBNE);
	usart_enable(USART1);
}

/**
  * @brief  串口2初始化
  * @param  None
  * @retval None
  */
void bsp_usart2_init()
{
	/* 使能RX时钟 */
	rcu_periph_clock_enable( USART2_RX_GPIO_CLK);

	/* 使能TX时钟 */
	rcu_periph_clock_enable( USART2_TX_GPIO_CLK);

	/* 使能串口1时钟 */
	rcu_periph_clock_enable(RCU_USART2);

	/* 设置TX管脚的复用功能 */
	gpio_af_set(USART2_TX_GPIO_PORT, GPIO_AF_7, USART2_TX_PIN);

	/* 设置RX管脚的复用功能 */
	gpio_af_set(USART2_RX_GPIO_PORT, GPIO_AF_7, USART2_RX_PIN);

	/* 配置TX管脚 复用模式、上拉*/
	gpio_mode_set(USART2_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART2_TX_PIN);
	gpio_output_options_set(USART2_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART2_TX_PIN);

	/* 配置RX管脚 复用模式、上拉*/
	gpio_mode_set(USART2_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART2_RX_PIN);
	gpio_output_options_set(USART2_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART2_RX_PIN);

	/* USART 配置 8数据位、2停止位、偶校验位 */
	usart_deinit(USART2);
	usart_baudrate_set(USART2,USART2_BAUDRATE); 
	usart_parity_config(USART2,USART_PM_EVEN); 
	usart_word_length_set(USART2,USART_WL_8BIT);
	usart_stop_bit_set(USART2, USART_STB_2BIT);
	usart_receive_config(USART2, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART2, USART_TRANSMIT_ENABLE); 
	usart_interrupt_enable(USART2, USART_INT_RBNE);
	usart_enable(USART2);
}
/**
  * @brief  串口3初始化
  * @param  None
  * @retval None
  */
void bsp_usart3_init()
{
	/* 使能RX时钟 */
	rcu_periph_clock_enable( USART3_RX_GPIO_CLK);

	/* 使能TX时钟 */
	rcu_periph_clock_enable( USART3_TX_GPIO_CLK);

	/* 使能串口1时钟 */
	rcu_periph_clock_enable(RCU_UART3);

	/* 设置TX管脚的复用功能 */
	gpio_af_set(USART3_TX_GPIO_PORT, GPIO_AF_8, USART3_TX_PIN);

	/* 设置RX管脚的复用功能 */
	gpio_af_set(USART3_RX_GPIO_PORT, GPIO_AF_8, USART3_RX_PIN);

	/* 配置TX管脚 复用模式、上拉*/
	gpio_mode_set(USART3_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART3_TX_PIN);
	gpio_output_options_set(USART3_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART3_TX_PIN);

	/* 配置RX管脚 复用模式、上拉*/
	gpio_mode_set(USART3_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART3_RX_PIN);
	gpio_output_options_set(USART3_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART3_RX_PIN);

	/* USART 配置 8数据位、1停止位、无奇偶校验位 */
	usart_deinit(UART3);
	usart_baudrate_set(UART3,USART3_BAUDRATE); 
	usart_parity_config(UART3,USART_PM_NONE); 
	usart_word_length_set(UART3,USART_WL_8BIT);
	usart_stop_bit_set(UART3, USART_STB_1BIT);
	usart_receive_config(UART3, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART3, USART_TRANSMIT_ENABLE); 
	usart_interrupt_enable(UART3, USART_INT_RBNE);
	usart_enable(UART3);

}
 /**
  * @brief  串口4初始化
  * @param  None
  * @retval None
  */
void bsp_usart4_init()
{
	/* 使能RX时钟 */
	rcu_periph_clock_enable( USART4_RX_GPIO_CLK);

	/* 使能TX时钟 */
	rcu_periph_clock_enable( USART4_TX_GPIO_CLK);

	/* 使能串口1时钟 */
	rcu_periph_clock_enable(RCU_UART4);

	/* 设置TX管脚的复用功能 */
	gpio_af_set(USART4_TX_GPIO_PORT, GPIO_AF_8, USART4_TX_PIN);

	/* 设置RX管脚的复用功能 */
	gpio_af_set(USART4_RX_GPIO_PORT, GPIO_AF_8, USART4_RX_PIN);

	/* 配置TX管脚 复用模式、上拉*/
	gpio_mode_set(USART4_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART4_TX_PIN);
	gpio_output_options_set(USART1_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART1_TX_PIN);

	/* 配置RX管脚 复用模式、上拉*/
	gpio_mode_set(USART4_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART4_RX_PIN);
	gpio_output_options_set(USART4_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART4_RX_PIN);

	/* USART 配置 8数据位、1停止位、无奇偶校验位 */
	usart_deinit(UART4);
	usart_baudrate_set(UART4,USART4_BAUDRATE); 
	usart_parity_config(UART4,USART_PM_NONE); 
	usart_word_length_set(UART4,USART_WL_8BIT);
	usart_stop_bit_set(UART4, USART_STB_1BIT);
	usart_receive_config(UART4, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART4, USART_TRANSMIT_ENABLE); 
	usart_interrupt_enable(UART4, USART_INT_RBNE);
	usart_enable(UART4);

}
 /**
  * @brief  串口5初始化
  * @param  None
  * @retval None
  */
void bsp_usart5_init()
{
	/* 使能RX时钟 */
	rcu_periph_clock_enable( USART5_RX_GPIO_CLK);

	/* 使能TX时钟 */
	rcu_periph_clock_enable( USART5_TX_GPIO_CLK);

	/* 使能串口1时钟 */
	rcu_periph_clock_enable(RCU_USART5);

	/* 设置TX管脚的复用功能 */
	gpio_af_set(USART5_TX_GPIO_PORT, GPIO_AF_8, USART5_TX_PIN);

	/* 设置RX管脚的复用功能 */
	gpio_af_set(USART5_RX_GPIO_PORT, GPIO_AF_8, USART5_RX_PIN);

	/* 配置TX管脚 复用模式、上拉*/
	gpio_mode_set(USART5_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART5_TX_PIN);
	gpio_output_options_set(USART5_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART5_TX_PIN);

	/* 配置RX管脚 复用模式、上拉*/
	gpio_mode_set(USART5_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,USART5_RX_PIN);
	gpio_output_options_set(USART5_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,USART5_RX_PIN);

	/* USART 配置 8数据位、1停止位、无奇偶校验位 */
	usart_deinit(USART5);
	usart_baudrate_set(USART5,USART5_BAUDRATE); 
	usart_parity_config(USART5,USART_PM_NONE); 
	usart_word_length_set(USART5,USART_WL_8BIT);
	usart_stop_bit_set(USART5, USART_STB_1BIT);
	usart_receive_config(USART5, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART5, USART_TRANSMIT_ENABLE); 
	usart_interrupt_enable(USART5, USART_INT_RBNE);
	usart_enable(USART5);

}


/* 重定向c库函数printf到串口DEBUG_USART，重定向后可使用printf函数 */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(PRINTF_USART, (uint8_t)ch);
    while(RESET == usart_flag_get(PRINTF_USART, USART_FLAG_TBE));
    return ch;
}