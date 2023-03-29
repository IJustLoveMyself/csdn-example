/*
 * @******************************************************************************: 
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-03-14 19:15:27
 * @LastEditors: gxf
 * @LastEditTime: 2023-03-22 13:44:11
 * @==============================================================================: 
 */

#include "md_ethercat.h"
#include "bsp_time.h"
void ethercat_timer_init(void)
{
    bsp_time4_init();
}
void ethercat_gpio_init(void)
{
  rcu_periph_clock_enable(RCU_GPIOD); /* LED */
  gpio_mode_set(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP,GPIO_PIN_4);
  gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_4);
  gpio_bit_reset(GPIOD, GPIO_PIN_4);

  
  rcu_periph_clock_enable(RCU_GPIOB);/* KEY */
  gpio_mode_set(GPIOD, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_14);   
}
void ethercat_sync0_init(void)
{
    rcu_periph_clock_enable(RCU_SYSCFG);
    rcu_periph_clock_enable(RCU_GPIOC);
    gpio_mode_set(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_13);
    /* 外部中断配置 */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOC, EXTI_SOURCE_PIN13);
    exti_init(EXTI_13, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(EXTI_13); 
}

void ethercat_sync1_init(void)
{
    rcu_periph_clock_enable(RCU_SYSCFG);
    rcu_periph_clock_enable(RCU_GPIOF);
    gpio_mode_set(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_1);
    /* 外部中断配置 */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOF, EXTI_SOURCE_PIN1);
    exti_init(EXTI_1, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(EXTI_1); 
}
void ethercat_pdi_init(void)
{
    rcu_periph_clock_enable(RCU_SYSCFG);
    rcu_periph_clock_enable(RCU_GPIOE);
    gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,GPIO_PIN_3);
    /* 外部中断配置 */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOE, EXTI_SOURCE_PIN3);
    exti_init(EXTI_3, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(EXTI_3); 
}

u8 spi_data_rw(u8 data)
{
    u16 tmp;
    /* 等待发送缓冲区清空 */
    while(RESET == spi_i2s_flag_get(Ethercat_SPI,SPI_FLAG_TBE));
    /* 发送要写的寄存器地址 */
    spi_i2s_data_transmit(Ethercat_SPI,data);
    /* 等待接收完成 SPI收发一体的，必须等到接收完成才代表一次完整的发送完成*/
    while(RESET == spi_i2s_flag_get(Ethercat_SPI,SPI_FLAG_RBNE));
    /* 读取缓存取得值，清空缓存区，准备发送 */
    tmp = spi_i2s_data_receive(Ethercat_SPI);   
    return (u8)tmp;
}