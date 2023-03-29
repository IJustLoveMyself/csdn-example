/*
 * @******************************************************************************: 
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2023-03-14 19:15:12
 * @LastEditors: gxf
 * @LastEditTime: 2023-03-28 14:33:03
 * @==============================================================================: 
 */
#ifndef _MD_ETHER_H_
#define _MD_ETHER_H_
#include "gd32f4xx.h" 

#define Ethercat_SPI        SPI3

void ethercat_timer_init(void);
void ethercat_gpio_init(void);
void ethercat_sync0_init(void);
void ethercat_sync1_init(void);
void ethercat_pdi_init(void);
u8 spi_data_rw(u8 data);

#endif