/*
 * @******************************************************************************: 
 * @Description: GD32F470 系统时钟模块配置头文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-02-02 16:31:34
 * @LastEditors: gxf
 * @LastEditTime: 2023-02-02 17:58:22
 * @==============================================================================: 
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
