/*
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2022-02-02 18:22:37
 * @LastEditors: gxf
 * @LastEditTime: 2022-02-07 09:08:55
 */
/**
  ******************************************************************************
  * @file    bsp_sys.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人系统文件
 ==============================================================================
  */
 

#include "bsp_sys.h"
#include "XiaoyuanConfig.h"

/**
  * @brief  配置中断的硬件优先级
  * @param  None
  * @retval None
  */
void nvic_configuration(void){
  /* 配置为组4 freertos必须设置成组4 由于FreeRTOSCONFIG.h的配置，
  优先级要低于5，中断才能使用FreeRTOS的API函数，另外优先级低于5的中断才能被屏蔽
  systick\pendsv 的中断优先级在port.c文件中已经被定义了
  */
  nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);  
  nvic_irq_enable(CAN0_RX0_IRQn,5,0);
  nvic_irq_enable(CAN1_RX1_IRQn,5,0);
  nvic_irq_enable(TIMER1_IRQn,6,0);
  nvic_irq_enable(USART0_IRQn,6,0);   
  nvic_irq_enable(USART1_IRQn,6,0);
  nvic_irq_enable(USART2_IRQn,6,0);
  nvic_irq_enable(UART3_IRQn,6,0);
  nvic_irq_enable(UART4_IRQn,6,0);
  nvic_irq_enable(USART5_IRQn,6,0); 
  nvic_irq_enable(ENET_IRQn, 5, 0);
}
