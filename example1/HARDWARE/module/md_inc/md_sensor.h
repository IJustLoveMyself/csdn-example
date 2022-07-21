/**
  ******************************************************************************
  * @file    md_sensor.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人传感器控制
 ==============================================================================
 */

#ifndef _MD_SENSOR_H_
#define _MD_SENSOR_H_
#include "gd32f4xx.h" 

 

#define STA_DISTANCE_L    520  /* 传感器的标准值 */
#define STA_DISTANCE_M    520  /* 传感器的标准值 */
#define STA_DISTANCE_R    500  /* 传感器的标准值 */

#define Sensor_Fall_1     0
#define Sensor_Fall_2     0
#define Sensor_Fall_3     0
#define Sensor_Fall_4     0

typedef struct{
  u8  Header;
  u8  Mask;
  u8  Reserved1;
  u8  ID;
  u32 SysTime;
  u8  Dis1;
  u8  Dis2;
  u8  Dis3;
  u8  DisStatus;
  u16 SignalStrength;
  u8  Reserved2;
  u8  SumCheck;	
} __attribute__((__packed__)) tof_t;


typedef union{
  tof_t TOFData;
  unsigned char buffer[16];
} tof_t_u;

typedef struct{
  u32 distance;
  u16 signalstrength;
} tofinfo_t;
void tof_polling(void);
u8 getfallflag(void);
void setfallflag(u8 flag);
void tof_recv_isr(void);
#endif
