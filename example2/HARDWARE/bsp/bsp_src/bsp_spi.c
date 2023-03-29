/*
 * @******************************************************************************: 
 * @Description: spi驱动头文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-02-14 10:51:44
 * @LastEditors: gxf
 * @LastEditTime: 2023-03-28 14:34:59
 * @==============================================================================: 
 */


#include "bsp_spi.h"
#include "AMConfig.h"

/**
 * @******************************************************************************: 
 * @func: [bsp_spi3_init]
 * @description: SPI3 初始化
 * @note: 
 * @author: gxf
 * @return [*]
 * @==============================================================================: 
 */
void bsp_spi3_init(void)
{
    spi_parameter_struct spi_init_struct;

    rcu_periph_clock_enable(SPI3_CS_GPIO_CLK);
    rcu_periph_clock_enable(SPI3_MISO_GPIO_CLK);
    rcu_periph_clock_enable(SPI3_MOSI_GPIO_CLK);
    rcu_periph_clock_enable(SPI3_SCK_GPIO_CLK);
    rcu_periph_clock_enable(RCU_SPI3);
    
    /* MISO 引脚配置*/
    gpio_mode_set(SPI3_MISO_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI3_MISO_GPIO);
    gpio_output_options_set(SPI3_MISO_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, SPI3_MISO_GPIO);
    gpio_af_set(SPI3_MISO_GPIO_PORT, GPIO_AF_5, SPI3_MISO_GPIO);
    
    /* MOSI 引脚配置 */
    gpio_mode_set(SPI3_MOSI_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI3_MOSI_GPIO);
    gpio_output_options_set(SPI3_MOSI_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, SPI3_MOSI_GPIO);
    gpio_af_set(SPI3_MOSI_GPIO_PORT, GPIO_AF_5, SPI3_MOSI_GPIO);
    /* SCK 引脚配置*/
    gpio_mode_set(SPI3_SCK_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, SPI3_SCK_GPIO);
    gpio_output_options_set(SPI3_SCK_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_25MHZ, SPI3_SCK_GPIO);
    gpio_af_set(SPI3_SCK_GPIO_PORT, GPIO_AF_5, SPI3_SCK_GPIO);

    /* CS 引脚配置 */
    gpio_mode_set(SPI3_CS_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI3_CS_GPIO);
    gpio_output_options_set(SPI3_CS_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI3_CS_GPIO);
    gpio_output_options_set(SPI3_CS_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI3_CS_GPIO);
    gpio_bit_set(SPI3_CS_GPIO_PORT,SPI3_CS_GPIO);

    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;       /* 全双工*/
    spi_init_struct.device_mode          = SPI_MASTER;                     /* 主机模式*/
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;             /* 8位帧格式*/
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;        /* 时钟相位极性，空闲时为高电平，第二个时钟边沿进行采样 */
    spi_init_struct.nss                  = SPI_NSS_SOFT;                   /* 软件NSS */ 
    spi_init_struct.prescale             = SPI_PSC_32;                     /* 时钟32分频 */
    spi_init_struct.endian               = SPI_ENDIAN_MSB;                 /* 高位在前 */
    spi_init(SPI3, &spi_init_struct);

    /* 使能SPI */
    spi_enable(SPI3);
}