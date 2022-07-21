/**
  ******************************************************************************
  * @file    md_canopen.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人canopen配置文件
 ==============================================================================
 */
#include "gd32f4xx.h"
#ifndef __MD_CANOPEN_H
#define __MD_CANOPEN_H

/* CANOPEN 的报文ID */
#define RSDO_Message                          0x0600  /* 板子向驱动器发送的SDO的CAN ID */
#define TSDO_Message                          0x0580  /* 驱动器向板子回复的SDO的CAN ID */
#define TPDO1_Message                         0x0180  /* 驱动器向板子发送TPDO1的报文的ID */
#define TPDO2_Message                         0x0280  /* 驱动器向板子发送TPDO2的报文的ID */
#define TPDO3_Message                         0x0380  /* 驱动器向板子发送TPDO3的报文的ID */
#define TPDO4_Message                         0x0480  /* 驱动器向板子发送TPDO4的报文的ID */
#define RPDO1_Message                         0x0200  /* 驱动器向板子发送TPDO1的报文的ID */
#define RPDO2_Message                         0x0300  /* 驱动器向板子发送TPDO2的报文的ID */
#define RPDO3_Message                         0x0400  /* 驱动器向板子发送TPDO3的报文的ID */
#define RPDO4_Message                         0x0500  /* 驱动器向板子发送TPDO4的报文的ID */
#define NMT_Master                            0x0000  /* 板子向驱动器发送的NMT管理的报文ID */
#define NMT_Slaver                            0x0700  /* 驱动器向板子发送的NMT管理的报文ID */

/* CANOPEN 命令字 */

#define  Writefourbyte  	                  0x23  /* 写4字节内容命令字 */
#define  Writethreebyte 	                  0x27  /* 写3字节内容命令字 */
#define  Writetwobyte   	                  0x2B  /* 写2字节内容命令字 */
#define  Writeonebyte   	                  0x2F  /* 写1字节内容命令字 */
#define  Readbyte       	                  0x40  /* 读取对象命令字 */

/* 驱动器状态字 驱动上电后进入Switch On Disable状态*/

#define  NoReadyToSwitchOn                    0x00   
#define  SwitchOnDisabled                     0x40   
#define  ReadyToSwitchOn                      0x21   
#define  SwitchOn                             0x23   
#define  OperationEnable                      0x27   
#define  QuickStopActive                      0x07   
#define  FaultReactionAction                  0x0F   
#define  Fault                                0x08


/* 速度模式配置 */
u16 write_flag_of_synchronous_200F_00(u16 node,u8 data);
u16 write_modes_of_operation_6060_00(u16 node,char data);
u16 write_profile_acceleration_6083_00(u16 node,u32 data);
u16 write_profile_acceleration_6083_01(u16 node,u32 data);
u16 write_profile_acceleration_6083_02(u16 node,u32 data);
u16 write_profile_deceleration_6084_00(u16 node,u32 data);
u16 write_profile_deceleration_6084_01(u16 node,u32 data);
u16 write_profile_deceleration_6084_02(u16 node,u32 data);
u16 write_quick_deceleration_6085_00(u16 node,u32 data);
u16 write_quick_deceleration_6085_01(u16 node,u32 data);
u16 write_quick_deceleration_6085_02(u16 node,u32 data);
u16 write_profile_speed_60FF_00(u16 node,int data);
u16 write_profile_speed_60FF_01(u16 node,int data);
u16 write_profile_speed_60FF_02(u16 node,int data);
u16 write_profile_speed_60FF_03(u16 node,int data);
u16 wtite_offline_protect_2000_00(u16 node,u16 data);
u16 write_speed_smooth_2018_00(u16 node,u16 data);
u16 write_speed_smooth_2018_01(u16 node,u16 data);
u16 write_speed_smooth_2018_02(u16 node,u16 data);
u16 write_halt_set_605D_00(u16 node,u16 data);
u16 write_overload_factor_2012_00(u16 node,u16 data);
u16 write_overload_factor_2012_01(u16 node,u16 data);
u16 write_overload_factor_2012_02(u16 node,u16 data);
u16 write_rated_current_2014_00(u16 node,u16 data);
u16 write_rated_current_2014_01(u16 node,u16 data);
u16 write_rated_current_2014_02(u16 node,u16 data);
u16 write_max_current_2015_00(u16 node,u16 data);
u16 write_max_current_2015_01(u16 node,u16 data);
u16 write_max_current_2015_02(u16 node,u16 data);
u16 write_overload_time_2016_00(u16 node,u16 data);
u16 write_overload_time_2016_01(u16 node,u16 data);
u16 write_overload_time_2016_02(u16 node,u16 data);

u16 write_controlword_6040_00(u16 node,u16 data);
u16 read_statusword_6041_00(u16 node);

/* TPDO0 通信参数配置 */
u16 write_TPDO0_1800_01(u16 node,u32 data);
u16 write_TPDO0_1800_02(u16 node,u16 data);
u16 write_TPDO0_1800_05(u16 node,u16 data);

/* TPDO0 映射参数配置 */
u16 write_TPDO0_1A00_00(u16 node,u8 data);
u16 write_TPDO0_1A00_01(u16 node,u32 data);
u16 write_TPDO0_1A00_02(u16 node,u32 data);

/* TPDO1 通信参数配置 */
u16 write_TPDO1_1801_01(u16 node,u32 data);
u16 write_TPDO1_1801_02(u16 node,u16 data);
u16 write_TPDO1_1801_05(u16 node,u16 data);

/* TPDO1 映射参数配置 */
u16 write_TPDO1_1A01_00(u16 node,u8 data);
u16 write_TPDO1_1A01_01(u16 node,u32 data);
u16 write_TPDO1_1A01_02(u16 node,u32 data);

/* NMT 参数配置 */
u16 write_NMT_heartbeat_1017_00(u16 node,u16 data);
u16 write_NMT_cmd(u8 data);

#endif
