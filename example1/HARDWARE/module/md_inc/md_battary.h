/*
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2021-12-20 15:43:44
 * @LastEditors: gxf
 * @LastEditTime: 2022-01-18 18:34:29
 */
/**
  ******************************************************************************
  * @file    md_battary.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人电池配置文件
 ==============================================================================
 */

#ifndef __MD_BATTARY_H
#define __MD_BATTARY_H
#include "gd32f4xx.h"

#define BATTARY_ID              0x182c1860  //电池ID

typedef struct{
  char          soc;                                    /* 电池SOC   */
  u32           voltage;                                  /* 电池电压 mv*/
  char          bms_chargestate;                        /* BMS反应的充电状态 */
  u32           bms_current;                            /* 电流的大小 ma*/
  unsigned int  batteryHearbeatCnt;                     /* 电池心跳计数 */	
}battaryinfo_t;

typedef enum{
  Init=1,
  Charging,
  Full
}sta_e;

void battery_info_query(void);
u8 is_battary_connect(void);
battaryinfo_t getBattaryInfo(void);
void battary_count_add(void);
void charge_management(void);
void battery_can_data(can_receive_message_struct rxmessage);
#endif
