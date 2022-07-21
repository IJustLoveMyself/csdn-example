/**
  ******************************************************************************
  * @file    md_cmd.h
  * @author  gxf
  * @version V0.0.1
  * @date    2021.09.06
  * @brief   小远机器人命令接口文档
 ==============================================================================
 */

#ifndef _MD_CMD_H_
#define _MD_CMD_H_
#include "gd32f4xx.h" 

typedef struct{
  unsigned int   header;
  unsigned char  cmd;
  unsigned int   data;
  unsigned short checksum;
  unsigned char  end;
} __attribute__((__packed__)) _cmd_t ;

typedef union{
  unsigned char buf[12];
  _cmd_t recv
} _cmd_u;


#endif