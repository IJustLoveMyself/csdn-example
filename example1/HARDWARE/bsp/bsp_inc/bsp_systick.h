/**
  ******************************************************************************
  * @file    bsp_systick.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人滴答定时器操作的底层文件
 ==============================================================================
  */
 
#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H
#include "gd32f4xx.h"
#include "stdio.h"  
void sysTick_init(void);  
void delay_us(u32 nTime);
void delay_ms(u32 nTime);
void TimingDelay_Decrement(void);
#endif
