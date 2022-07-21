/*
 * @Description: 以太网模块头文件
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2022-02-05 22:07:32
 * @LastEditors: gxf
 * @LastEditTime: 2022-02-06 16:43:03
 */

#ifndef __BSP_ENET_H
#define __BSP_ENET_H



/* 使用RMII模式 */
#define RMII_MODE  // user have to provide the 50 MHz clock by soldering a 50 MHz oscillator
//#define MII_MODE

/* clock the PHY from external 25MHz crystal (only for MII mode) */
#ifdef  MII_MODE
#define PHY_CLOCK_MCO
#endif
#endif