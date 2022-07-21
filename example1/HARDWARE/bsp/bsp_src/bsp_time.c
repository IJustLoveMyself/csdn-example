/**
  ******************************************************************************
  * @file    bsp_time.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人定时器操作的底层文件
 ==============================================================================
  * 初始化设置中SYSCLK = 168M
  * ***************************************************************************
  */


#include "bsp_time.h"
#include "XiaoyuanConfig.h"
/**
  * @brief  定时器1初始化
  * @param  None
  * @retval None
  */
void bsp_time1_init(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);
  
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); //四倍频，定时器1的时钟来自 APB1 = AHB/4 AHB=SYS,所以定时器的时钟就是168M

    timer_deinit(TIMER1);

    /* TIMER1 配置 */
    timer_initpara.prescaler         = TIM1_ARR;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = TIM1_PSC;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1; 
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara); 
    timer_interrupt_enable(TIMER1,TIMER_INT_UP);   //使能定时器1的中断 优先级在nvic_configuration中设置

    timer_enable(TIMER1); 						 
}
