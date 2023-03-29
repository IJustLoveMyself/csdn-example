/*
 * @******************************************************************************: 
 * @Description: GD32F470 系统时钟模块配置源文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-02-02 16:31:34
 * @LastEditors: gxf
 * @LastEditTime: 2023-02-17 20:56:02
 * @==============================================================================: 
 */

#include "bsp_systick.h"
#include "AMConfig.h"
static volatile u32 TimingDelay;
static volatile u32 iwdgcnt = 200000; 

/**
 * @******************************************************************************: 
 * @func: [sysTick_init]
 * @description: 滴答定时器初始化
 * @note: 
 * @author: gxf
 * @return [*]
 * @==============================================================================: 
 */
void sysTick_init(void)
{
  /* SystemFrequency / 1000    1ms中断一次
   * SystemFrequency / 1000000 1us中断一次
   */
  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    
    while (1);
  }
}

/**
 * @******************************************************************************: 
 * @func: [delay_us]
 * @description: 延时 单位us
 * @note: 
 * @author: gxf
 * @param [u32] nTime 延时nTime us
 * @return [*]
 * @==============================================================================: 
 */
void delay_us(u32 nTime)
{ 
  TimingDelay = nTime;  

  while(TimingDelay != 0);
}


/**
 * @******************************************************************************: 
 * @func: [delay_ms]
 * @description: 延时 单位ms 
 * @note: 
 * @author: gxf
 * @param [u32] nTime 延时nTime ms
 * @return [*]
 * @==============================================================================: 
 */
void delay_ms(u32 nTime)
{ 
  TimingDelay = nTime*1000;  

  while(TimingDelay != 0);
}


/**
 * @******************************************************************************: 
 * @func: [TimingDelay_Decrement]
 * @description: 计算延时节拍 需要在 SysTick_Handler() 中调用 
 * @note: 
 * @author: gxf
 * @return [*]
 * @==============================================================================: 
 */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

