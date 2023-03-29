/*
 * @******************************************************************************: 
 * @Description: GD32F470 定时器模块配置源文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-02-02 16:31:34
 * @LastEditors: gxf
 * @LastEditTime: 2023-02-14 15:06:11
 * @==============================================================================: 
 */

#include "bsp_time.h"
#include "AMConfig.h"

/*****************************
 * 系统时钟200M AHB=SYSCLK APB2=AHB/2 APB1=AHB/4
 * 定时器1、2、3、4、5、6、11、12、13挂在APB1上
 * 定时器0、7、8、9、10 挂在APB2上 
 * 
 * 定时器0，7为高级定时器
 * 定时器1，2，3，4为通用定时器L0
 * 定时器8，11为通用定时器L1
 * 定时器9，10，12，13为通用定时器L2
 * 定时器5，6为基本定时器
******************************/

/**
 * @******************************************************************************: 
 * @func: [bsp_time4_init]
 * @description: 定时器4初始化
 * @note: 
 * @author: gxf
 * @return [*]
 * @==============================================================================: 
 */
void bsp_time4_init(void)
{
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER4);
  
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); //四倍频，定时器1的时钟来自 APB1 = AHB/4 AHB=SYS,所以定时器的时钟就是200M

    timer_deinit(TIMER4);

    /* TIMER1 配置 */
    timer_initpara.prescaler         = TIM4_PSC;             /* 预分频值，计数时钟=定时器时钟/(PSC+1) */
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;   /* 无对齐模式*/
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;     /* 向上计数 */
    timer_initpara.period            = TIM4_CAR;             /* 自动重装值 */
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;     /* 时钟分频，规定定时器时钟与死区时间和数字滤波采样时钟之间的系数*/
    timer_initpara.repetitioncounter = 0;                    /* 中断的产生频率，计数器溢出N+1次后产生中断*/
    timer_init(TIMER4,&timer_initpara); 
    timer_interrupt_enable(TIMER4,TIMER_INT_UP);   

    timer_enable(TIMER4); 						 
}
