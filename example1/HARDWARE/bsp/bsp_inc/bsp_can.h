/**
  ******************************************************************************
  * @file    bsp_can.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人CAN总线操作的底层文件
 ==============================================================================
 */


#ifndef __BSP_CAN_H
#define __BSP_CAN_H
#include "gd32f4xx.h"
#include <stdio.h>
void bsp_can0_init(void);
void bsp_can1_init(void);
u8 can0_send_msg(u8* msg,u8 len);	
u8 can1_send_msg(u8* msg,u8 len);
#endif
