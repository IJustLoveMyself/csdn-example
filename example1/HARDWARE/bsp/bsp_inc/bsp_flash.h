/**
  ******************************************************************************
  * @file    md_flash.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人flash接口文档
 ==============================================================================
 */
#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_
#include "gd32f4xx.h" 

#define FLASH_BASE_ADDR       0x080000000  /* FLASH 的基地址 */
#define FLASH_ALLSIZE         521*1024     /* FLASH 的大小   */

uint8_t flash_read8(uint32_t faddr);
uint16_t flash_read16(uint32_t faddr);
uint32_t flash_read32(uint32_t faddr);
void flash_erase_sector(uint32_t sector);
void flash_erase_sector_multiple(uint32_t start,uint32_t end);
void flash_write32(uint32_t WriteAddr,uint32_t WriteData);
void flash_write16(uint32_t WriteAddr,uint16_t WriteData);
void flash_write8(uint32_t WriteAddr,uint8_t WriteData);
void flash_write16_multiple(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);
void flash_write8_multiple(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
void flash_read8_multiple(uint32_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);
#endif