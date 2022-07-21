/**
  ******************************************************************************
  * @file    md_task.h
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人任务控制
 ==============================================================================
 */

#ifndef _MD_TASK_H_
#define _MD_TASK_H_
#include "gd32f4xx.h" 

typedef enum{
  Run,                              /* 表示当前任务需要执行 */
  Suppend,                          /* 表示任务在挂起,等待轮询 */
  Stop                              /* 表示任务退出轮询 */
} task_s;

/* 任务结构体 */
typedef struct listnode{
  u8 id;                            /* 任务ID 用户添加的id>0 每个任务id不同*/
  u32 timedelay;                    /* 任务的延时时间 */
  u32 timecnt;                      /* 任务时间计数 */
  void (*func)();                   /* 任务函数 */
  task_s state;                     /* 任务状态 */
  struct listnode *next;            /* 上一个节点的地址 */
  struct listnode *prev;            /* 下一个节点的地址 */
} taskHandle_t;

void task_init(void);
void task_start(void);
void task_scheduler(void);
void task_change_state(u8 id,task_s state);
void task_create(void(*func)(),u32 delay,u8 id);
#endif
