/*
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2021-12-20 15:43:44
 * @LastEditors: gxf
 * @LastEditTime: 2022-01-17 15:25:59
 */
/**
  ******************************************************************************
  * @file    md_nuc.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人底盘与NUC通讯文件
 ==============================================================================
 */
#ifndef __MD_NUC_H
#define __MD_NUC_H
#include "gd32f4xx.h" 
#define PROTOCAL_DATA_SIZE		25 	
#define PROTOCAL_HEADER		    0XFEFEFEFE
#define PROTOCAL_END	        0XDD

/* 发送数据结构体 */
typedef struct {
  unsigned int header;
  float speed_left;
  float speed_right;
  float voltage;
  char  energency;
  char  soc;
  char  driverstate;
  char  chargeflag;
  char  manual_charge;
  char  peripherals_connect;
  char  auto_charge;
  char  fall_sensor_state;
  unsigned char end;	
} __attribute__((__packed__)) SendData_t;
/* 接收数据结构体 */
typedef struct {
  unsigned int header;
  float speed_left;
  float speed_right;
  float reserve;
  char  reserve0;
  char  reserve1;
  char  motordisable;
  char  reserve2;
  char  reserve3;
  unsigned char  fault_reset;
  unsigned char  resetmcu;
  unsigned char  stopcmd;
  unsigned char  end;	
} __attribute__((__packed__)) RecvData_t;

typedef union{
  unsigned char buffer[PROTOCAL_DATA_SIZE];
  SendData_t s;
  RecvData_t r;
} Protocal_t;
/* NUC 数据结构体 其实就是接收结构体的简化版本 */
typedef struct{
  float speed_left;
  float speed_right;
  char  motordisable;	
  unsigned char  fault_reset;
  unsigned char  resetmcu;
  unsigned char  stopcmd;
  unsigned char  fall_sensor;
  unsigned int   nucHeartbeatCnt;
} nuc_t;

u8 is_nuc_connect(void);
void send_to_nuc(void);
void recv_from_nuc(void);
void nuc_moudle_init(void);
void nuc_count_add(void);
void nuc_recv_isr(void);
nuc_t getNUCInfo(void);

#endif
