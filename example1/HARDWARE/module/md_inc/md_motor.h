/**
  ******************************************************************************
  * @file    md_motor.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人电机配置文件
 ==============================================================================
 */

#ifndef __MD_MOTOR_H
#define __MD_MOTOR_H

#include "gd32f4xx.h"
/* 电机的node ID */
#define DriverID                               1
#define LeftMotor                              1
#define RightMotor                             2

typedef struct {
    u16 send;
    u16 receive;
}_INDEX;

typedef struct {
    u16 index_6041_00[2];                      /* 存放左右电机的状态值 */
    u8  nmtstate[2];                           /* 存放nmt状态 */
}_DATA; 

typedef struct {
  short         leftCurrentSpeedRPM;                    /* 左轮当前速度，单位rpm/min */
  short         leftTargetSpeedRPM;                     /* 左轮目标速度，单位rpm/min */ 
  float         leftCurrentSpeedMS;                     /* 左轮当前速度，单位m/s */ 
  short         rightCurrentSpeedRPM;                   /* 右轮当前速度，单位rpm/min */
  short         rightTargetSpeedRPM;                    /* 右轮目标速度，单位rpm/min */
  float         rightCurrentSpeedMS;                    /* 右轮当前速度，单位m/s */
  unsigned int  DriverHeartbeatCnt;                     /* 驱动器心跳计数 */
  unsigned char driverstate;                            /* 驱动器状态:
                                                         * bit0: 1:左边驱动器使能，0：左边驱动器未使能
                                                         * bit1: 1:左边驱动器报错，0：左边驱动器未报错
                                                         * bit2: 1:右边驱动器使能，0：右边驱动器未使能
                                                         * bit3: 1:右边驱动器报错，0：右边驱动器未报错*/
} driverinfo_t;

void motor_init(void);
driverinfo_t getMachineinfo(void);
u8 is_driver_connect(void);
void driver_count_add(void);
void quick_stop(void);
void motor_fault_reset(void);
void motor_control(void);
void driver_detection(void);
#endif
