/**
  ******************************************************************************
  * @file    md_powerboard.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人控制板与电源板通讯模块
 ==============================================================================
 */

#ifndef _MD_BOARD_H_
#define _MD_BOARD_H_
#include "gd32f4xx.h" 

#define POWERBUFSIZE 12
#define POWERHEADER  0xFEFEFEFE
#define POWEREND     0xDD

#define SwitchReserve24          0x01               /* 24V预留电源开关 */
#define SwitchNUC                0x02               /* NUC电源开关 */
#define SwitchAndriod            0x04               /* 安卓板电源开关 */
#define SwitchOther12            0x08               /* 12V供电预留开关包含雷达，路由器等 */
#define SwitchMotor              0x10               /* 电机供电的开关 */ 
#define SwitchReserve5           0x20               /* 5V供电控制开关 */
#define SwitchCharge             0x40               /* 自动充电控制开关 */

typedef struct 
{
  u8 reserve_24_bit0 :1;        /* 电源控制板中24v预留电源开关 */
  u8 ncu_19_bit1     :1;        /* 电源控制板中19vNUC电源开关 */
  u8 andriod_12_bit2 :1;        /* 电源控制板中12v安卓电源开关 */
  u8 other_12_bit3   :1;        /* 电源控制板中12v其他电源开关 */
  u8 motor_24_bit4   :1;        /* 电源控制板中24v电机电源开关 */
  u8 reserve_5_bit5  :1;        /* 电源控制板中5v预留电源开关 */
  u8 charge_auto_bit6:1;        /* 电源控制板中自动充电开关 */
  u8 reserve         :1;        /* 预留 */
}__attribute__((__packed__)) power_t;

typedef union{
  power_t switch_bit;
  u8      switch_byte;
}__attribute__((__packed__)) power_u;

/* 发送数据结构体 */
typedef struct 
{
  u32     header;
  power_u switch_control;
  u8      reserve1;
  u8      reserve2;
  float   reserve3;
  u8      end;
}__attribute__((__packed__)) powerboard_s_t;

/* 接收数据结构体 */
typedef struct 
{
  u32     header;
  power_u switch_state;
  u8      reserve;
  u8      charge_state;
  float   voltage;
  u8      end;
}__attribute__((__packed__)) powerboard_r_t;

typedef union 
{
  u8             buffer[POWERBUFSIZE];
  powerboard_s_t send;
  powerboard_r_t recv;	
} powerpacket_u;

typedef struct{
  u8    switch_state;
  float voltage;
  u8    charge_state;             /* 充电是否连接 */
  int   powerBoardHeartbeatCnt;
} powerboardinfo_t;

u8 get_charge_state(void);
void set_switch(u8 switchctr,u8 cmd);
void powerboard_count_add(void);
u8 is_powerboard_connect(void);
powerboardinfo_t getPowerboardinfo(void);
void powerboard_recv_isr(void);
#endif
