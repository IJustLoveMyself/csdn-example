/**
  ******************************************************************************
  * @file    bsp_uart.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人串口操作的底层文件
 ==============================================================================
 */

#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stdio.h"	
#include <stdbool.h>

void bsp_usart0_init(void);
void bsp_usart1_init(void);
void bsp_usart2_init(void);
void bsp_usart3_init(void);
void bsp_usart4_init(void);
void bsp_usart5_init(void);

#endif

