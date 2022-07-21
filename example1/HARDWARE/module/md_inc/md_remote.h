/**
  ******************************************************************************
  * @file    md_remote.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人底盘与遥控手柄通讯文件
 ==============================================================================
 */

#ifndef _MD_REMOTE_H_
#define _MD_REMOTE_H_
#include "gd32f4xx.h" 
typedef struct
{
  uint16_t ch1;
  uint16_t ch2;
  uint16_t ch3;
  uint16_t ch4;
  uint16_t ch5;
  uint16_t ch6;
  uint16_t ch7;
  uint16_t ch8;
  uint16_t ch9;
  uint16_t ch10;
  uint16_t ch11;
  uint16_t ch12;
  uint16_t ch13;
  uint16_t ch14;
  uint16_t ch15;
  uint16_t ch16;
  uint8_t  sbusflag;
} sbus_t;

void unpacket_sbus(u8 *buf);
void sbus_recv_isr(void);
void remote_data_process(void);
#endif
