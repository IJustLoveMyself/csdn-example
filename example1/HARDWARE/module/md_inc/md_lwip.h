/*
 * @Description: LWIP模块头文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2022-02-06 16:42:04
 * @LastEditors: gxf
 * @LastEditTime: 2022-02-07 13:53:28
 */
#ifndef _MD_LWIP_H_
#define _MD_LWIP_H_
#include "gd32f4xx.h" 

//#define USE_DHCP       /* enable DHCP, if disabled static address is used */

/* MAC地址*/
#define MAC_ADDR0   2
#define MAC_ADDR1   0xA
#define MAC_ADDR2   0xF
#define MAC_ADDR3   0xE
#define MAC_ADDR4   0xD
#define MAC_ADDR5   6
 
/* 本机静态IP设置 */
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   0
#define IP_ADDR3   100

/* 远程IP地址 */
#define IP_S_ADDR0   192
#define IP_S_ADDR1   168
#define IP_S_ADDR2   0
#define IP_S_ADDR3   110

/* 掩码 */
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* 网关 */
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   0
#define GW_ADDR3   1  


void lwip_stack_init(void);
#endif