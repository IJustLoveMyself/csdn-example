/**
  ******************************************************************************
  * @file    bsp_systick.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人滴答定时器操作的底层文件
 ==============================================================================
  * 初始化设置中SYSCLK = 168M
  * ****************************************************************************
  */
#include "bsp_systick.h"
#include "XiaoyuanConfig.h"

static volatile u32 TimingDelay;
 
/**
  * @brief  滴答定时器初始化
  * @param  None
  * @retval None
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
  * @brief  延时 单位us
  * @param  nTime 延时nTime us
  * @retval None
  */
void delay_us(u32 nTime)
{ 
  TimingDelay = nTime;  

  while(TimingDelay != 0);
}

/**
  * @brief  延时 单位ms
  * @param  nTime 延时nTime ms
  * @retval None
  */
void delay_ms(u32 nTime)
{ 
  TimingDelay = nTime*1000;  

  while(TimingDelay != 0);
}

/**
  * @brief  计算延时节拍 需要在 SysTick_Handler() 中调用
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

