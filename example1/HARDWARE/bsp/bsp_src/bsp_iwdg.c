/**
  ******************************************************************************
  * @file    bsp_iwdg.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人看门狗的底层文件
 ==============================================================================
  */
#include "bsp_iwdg.h"
#include "XiaoyuanConfig.h"
#include "gd32f4xx_fwdgt.h"


/**
  * @brief  看门狗初始化  
  * @param  None
  * @retval None
  */
void FWDG_Init(void)
{
	fwdgt_write_enable();
	fwdgt_config(500, FWDGT_PSC_DIV32);
	fwdgt_write_disable();
}

/**
  * @brief  喂狗 
  * @param  None
  * @retval None
  */
void FWDG_Feed(void)
{
	fwdgt_counter_reload();
}
