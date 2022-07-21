/**
  ******************************************************************************
  * @file    md_flash.h
  * @author  gxf
  * @version V0.0.1
  * @date    2021.09.06
  * @brief   小远机器人flash接口文档
  * GD32F407的flash最大为3072K，包含了8个16K、2个64K、14个128K、4个256K扇区
  * 我们使用的是GD32F407VET6，flash为512K
 ==============================================================================
 */
#include "bsp_flash.h"

/**
 * *****************************************************
 *扇区0~扇区3   每个扇区16KB  16KB*4
 *扇区4         64KB
 *扇区5~扇区11  每个扇区128KB 128KB*7
 *扇区12~扇区15 每个扇区16KB  16KB*4
 *扇区16        64KB
 *扇区17~扇区23 每个扇区128KB 128KB*7
 *扇区24~扇区27 每个扇区256KB 256KB*4
 *
 *GD32F407VET6的扇区是扇区0~扇区7 
 * *****************************************************
 */

/* flash的扇形区编号 */
uint32_t sectorbuf[28]={CTL_SECTOR_NUMBER_0, CTL_SECTOR_NUMBER_1, CTL_SECTOR_NUMBER_2, CTL_SECTOR_NUMBER_3, CTL_SECTOR_NUMBER_4, CTL_SECTOR_NUMBER_5,
                        CTL_SECTOR_NUMBER_6, CTL_SECTOR_NUMBER_7, CTL_SECTOR_NUMBER_8, CTL_SECTOR_NUMBER_9, CTL_SECTOR_NUMBER_10,CTL_SECTOR_NUMBER_11,
                        CTL_SECTOR_NUMBER_12,CTL_SECTOR_NUMBER_13,CTL_SECTOR_NUMBER_14,CTL_SECTOR_NUMBER_15,CTL_SECTOR_NUMBER_16,CTL_SECTOR_NUMBER_17,
                        CTL_SECTOR_NUMBER_18,CTL_SECTOR_NUMBER_19,CTL_SECTOR_NUMBER_20,CTL_SECTOR_NUMBER_21,CTL_SECTOR_NUMBER_22,CTL_SECTOR_NUMBER_23,
                        CTL_SECTOR_NUMBER_24,CTL_SECTOR_NUMBER_25,CTL_SECTOR_NUMBER_26,CTL_SECTOR_NUMBER_27};


/**
 * [flash_read8 description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 读取指定地址的8位数据
 * @note     [description]
 * @param    faddr         [description] 目标地址
 * @return                 [description] 目标地址的数据
 */
uint8_t flash_read8(uint32_t faddr)
{
  return *(uint8_t*)faddr; 
}
/**
 * [flash_read16 description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 读取指定地址的16位数据
 * @note     [description] 目标地址必须为2的倍数
 * @param    faddr         [description] 目标地址 
 * @return                 [description] 目标地址的数据
 */
uint16_t flash_read16(uint32_t faddr)
{
  return *(uint16_t*)faddr; 
}

/**
 * [flash_read32 description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 读取指定地址的32位数据
 * @note     [description] 目标地址必须为4的倍数
 * @param    faddr         [description] 目标地址
 * @return                 [description] 目标地址的数据
 */
uint32_t flash_read32(uint32_t faddr)
{
  return *(uint32_t*)faddr; 
}
 
//擦除指定的Sector
//Sector 取值 0~30
/**
 * [flahs_erase_sector description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 擦除指定编号的扇区
 * @note     [description]
 * @param    sector        [description] 扇区编号 0~27
 */
void flash_erase_sector(uint32_t sector)
{ 
  /* 解锁 */
  fmc_unlock();	
  fmc_sector_erase(sectorbuf[sector]);
  /* 上锁 */
  fmc_lock();
}

/**
 * [flash_erase_sector_multiple description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 擦除多个连续的扇区
 * @note     [description]
 * @param    start         [description] 起始扇区的编号
 * @param    end           [description] 结束扇区的编号
 */
void flash_erase_sector_multiple(uint32_t start,uint32_t end)
{ 
  uint16_t i = 0;
  /* 解锁 */
  fmc_unlock();	
  for(i=start;i<=end;i++){
    fmc_sector_erase(sectorbuf[i]);
  }
  /* 上锁 */
  fmc_lock();
}

/**
 * [flash_write16_multiple description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 向指定地址写入指定长度的数据，每个数据长度是16位
 * @note     [description]
 * @param    WriteAddr     [description] 要写入数据的flash地址
 * @param    pBuffer       [description] 数据的源地址
 * @param    NumToWrite    [description] 要写入的长度
 */
void flash_write16_multiple(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite)	
{	
  uint16_t i;
  if(WriteAddr<FLASH_BASE_ADDR||(WriteAddr>=FLASH_BASE_ADDR+FLASH_ALLSIZE))return;//非法地址
  fmc_unlock();
  for(i=0;i<NumToWrite;i++)
  {
    fmc_halfword_program(WriteAddr,pBuffer[i]);
    /* 16位的数据，下次写入地址要加2 */
    WriteAddr+=2;
  }  				   
  fmc_lock();
}

/**
 * [flash_write8_multiple description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 向指定地址写入指定长度的数据，每个数据长度是8位
 * @note     [description]
 * @param    WriteAddr     [description] 要写入数据的flash地址
 * @param    pBuffer       [description] 数据的源地址
 * @param    NumToWrite    [description] 要写入的长度
 */
void flash_write8_multiple(uint32_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)	
{	
  uint16_t i;
  if(WriteAddr<FLASH_BASE_ADDR||(WriteAddr>=FLASH_BASE_ADDR+FLASH_ALLSIZE))return;//非法地址
  fmc_unlock();	
  for(i=0;i<NumToWrite;i++)
  {
    fmc_byte_program(WriteAddr,pBuffer[i]);
    WriteAddr++;
  }  				   
  fmc_lock();
}

/**
 * [flash_write16 description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 向指定地址写入数据
 * @note     [description]
 * @param    WriteAddr     [description] 写入地址
 * @param    WriteData     [description] 要写入的数据,数据的长度是16位
 */
void flash_write16(uint32_t WriteAddr,uint16_t WriteData)
{	
  if(WriteAddr<FLASH_BASE_ADDR||(WriteAddr>=FLASH_BASE_ADDR+FLASH_ALLSIZE))return;//非法地址
  fmc_unlock();
  fmc_halfword_program(WriteAddr,WriteData);
  fmc_lock();
}

/**
 * [flash_write32 description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 向指定地址写入数据
 * @note     [description]
 * @param    WriteAddr     [description] 写入地址
 * @param    WriteData     [description] 要写入的数据,数据的长度是32位
 */
void flash_write32(uint32_t WriteAddr,uint32_t WriteData)	
{	
	if(WriteAddr<FLASH_BASE_ADDR||(WriteAddr>=FLASH_BASE_ADDR+FLASH_ALLSIZE))return;//非法地址
	fmc_unlock();	
	fmc_word_program(WriteAddr,WriteData);
	fmc_lock();
}

/**
 * [flash_write8 description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description] 向指定地址写入数据
 * @note     [description]
 * @param    WriteAddr     [description] 写入地址
 * @param    WriteData     [description] 要写入的数据,数据的长度是8位
 */
void flash_write8(uint32_t WriteAddr,uint8_t WriteData)	
{	
  if(WriteAddr<FLASH_BASE_ADDR||(WriteAddr>=FLASH_BASE_ADDR+FLASH_ALLSIZE))return;//非法地址
  fmc_unlock();
  fmc_byte_program(WriteAddr,WriteData);				   
  fmc_lock();
}

/**
 * [flash_read8_multiple description]
 * @author Gxf
 * @dateTime 2021-10-28
 * @brief    [description]
 * @note     [description]
 * @param    ReadAddr      [description] 从指定地址开始读出指定长度的数据到目标地址
 * @param    pBuffer       [description] 存储数据的目标地址
 * @param    NumToRead     [description] 要读取的数据的长度
 */
void flash_read8_multiple(uint32_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)   	
{
  uint16_t i;
  for(i=0;i<NumToRead;i++)
  {
    pBuffer[i]=flash_read8(ReadAddr);//读取1个字节.
    ReadAddr++;
  }
}

