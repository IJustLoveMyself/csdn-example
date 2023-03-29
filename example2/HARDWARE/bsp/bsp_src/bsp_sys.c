/*
 * @******************************************************************************: 
 * @Description: GD32F470 SYS模块配置源文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-02-02 16:31:34
 * @LastEditors: gxf
 * @LastEditTime: 2023-02-17 15:56:41
 * @==============================================================================: 
 */

 

#include "bsp_sys.h"
#include "AMConfig.h"


/**
 * @******************************************************************************: 
 * @func: [nvic_configuration]
 * @description: 中断优先级配置
 * @note: 
 * @author: gxf
 * @return [*]
 * @==============================================================================: 
 */
void nvic_configuration(void){
  /* 配置为组2 */
  nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
  nvic_irq_enable(SysTick_IRQn,0,0);
  nvic_irq_enable(CAN0_RX0_IRQn,0,1);
  nvic_irq_enable(CAN1_RX1_IRQn,0,2);
  nvic_irq_enable(TIMER1_IRQn,0,1);
	nvic_irq_enable(TIMER2_IRQn,0,2);
  nvic_irq_enable(USART0_IRQn,1,0);   
  nvic_irq_enable(USART1_IRQn,1,1);
  nvic_irq_enable(USART2_IRQn,1,1);
  nvic_irq_enable(UART3_IRQn,1,1);
  nvic_irq_enable(UART4_IRQn,1,1);
  nvic_irq_enable(USART5_IRQn,1,1);
  nvic_irq_enable(UART6_IRQn,1,1);
  nvic_irq_enable(UART7_IRQn,1,1); 
  nvic_irq_enable(EXTI0_IRQn,2,1);
  nvic_irq_enable(EXTI1_IRQn,2,1);
}
