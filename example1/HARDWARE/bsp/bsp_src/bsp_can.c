/**
  ******************************************************************************
  * @file    bsp_can.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人CAN总线操作的底层文件
 ==============================================================================
  * 初始化设置中SYSCLK = 168M
  * APB1的时钟是系统时钟的四分之一
  * ***************************************************************************
  */
#include "XiaoyuanConfig.h"
#include "bsp_can.h"


/**
  * @brief   CAN1初始化
  * @param   None
  * @retval  None
  */
void bsp_can0_init(void)
{
    /* enable can clock */
    rcu_periph_clock_enable(RCU_CAN0);
    rcu_periph_clock_enable(CAN0_RX_GPIO_CLK);
    rcu_periph_clock_enable(CAN0_TX_GPIO_CLK);
  
    /* 设置CAN1 TX */
    gpio_output_options_set(CAN0_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, CAN0_TX_PIN); 
    gpio_mode_set(CAN0_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CAN0_TX_PIN); 
    gpio_af_set(CAN0_TX_GPIO_PORT, GPIO_AF_9, CAN0_TX_PIN);
    /* 设置CAN1 RX */
    gpio_output_options_set(CAN0_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, CAN0_RX_PIN); 
    gpio_mode_set(CAN0_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CAN0_RX_PIN); 
    gpio_af_set(CAN0_RX_GPIO_PORT, GPIO_AF_9, CAN0_RX_PIN);
   
    can_parameter_struct can_parameter;
    can_filter_parameter_struct can_filter;

    /* 初始化CAN1 */
    can_deinit(CAN0); 
  
    /* 是否使能时间触发功能 */
    can_parameter.time_triggered = DISABLE;
    /* 是否使用自动离线管理 使用自动离线管理可以在节点出错离线后适时自动恢复，不需要软件干预 */   
    can_parameter.auto_bus_off_recovery = DISABLE;
    /* 是否使用自动唤醒功能 (ENABLE/DISABLE)，使能自动唤醒功能后它会在监测到总线活动后自动唤醒 */    
    can_parameter.auto_wake_up = DISABLE;
    /* 是否使用自动重传功能 (ENABLE/DISABLE)，使用自动重传功能时，会一直发送报文直到成功为止 */
    can_parameter.no_auto_retrans = DISABLE;
    /* 是否使用锁定接收 FIFO(ENABLE/DISABLE)，锁定接收 FIFO 后，若FIFO溢出时会丢弃新数据，否则
       在 FIFO 溢出时以新数据覆盖旧数据 */ 
    can_parameter.rec_fifo_overwrite = DISABLE;
    /* 设置发送报文的优先级判定方法 (ENABLE/DISABLE)，使能时，以报文存入发送邮箱的先后顺序来发送，
       否则按照报文 ID 的优先级来发送 */
    can_parameter.trans_fifo_order = ENABLE;
    /* 正常工作模式 */  
    can_parameter.working_mode = CAN_NORMAL_MODE;
    /* 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq 一般为1*/   
    can_parameter.resync_jump_width  = CAN_BT_SJW_1TQ;  
    /* Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq 一般大于CAN_BS2*/
    can_parameter.time_segment_1  = CAN_BT_BS1_7TQ; 
    /* Tbs2范围CAN_BS2_1tq ~  CAN_BS2_8tq */
    can_parameter.time_segment_2  = CAN_BT_BS2_6TQ;
    /* CAN波特率 = 42M/(swj+tbs1+tbs1)/Prescaler*/
    switch(CAN0_BAUDRATE){
      /* 1M 波特率 */
      case 1000:
        can_parameter.prescaler=3;
        break;
      /* 500K 波特率 */
      case 500:
        can_parameter.prescaler=6;
        break;
      case 250:
      /* 250K 波特率 */        
        can_parameter.prescaler=12;
        break;
      case 125:
      /* 125K 波特率 */        
        can_parameter.prescaler=24;
        break;
    }
    can_init(CAN0, &can_parameter);  //初始化CAN0
    
    /* 配置过滤器 */
    /* CAN0 过滤器0 */
    can_filter.filter_number = 0;

    /* 配置过滤器32位掩码模式 */    
    can_filter.filter_mode        = CAN_FILTERMODE_MASK; 
    can_filter.filter_bits        = CAN_FILTERBITS_32BIT;
    /* 接收所有数据，不过滤 */
    can_filter.filter_list_high   = 0x0000; 
    can_filter.filter_list_low    = 0x0000; 
    can_filter.filter_mask_high   = 0x0000;
    can_filter.filter_mask_low    = 0x0000;
    can_filter.filter_fifo_number = CAN_FIFO0;
    can_filter.filter_enable      = ENABLE;
    can_filter_init(&can_filter);
    
    can_interrupt_enable(CAN0, CAN_INT_RFNE0);     
  
}

/**
  * @brief   CAN1初始化
  * @param   None
  * @retval  None
  */
void bsp_can1_init(void)
{
    /* 使能时钟，GD32的CAN0的时钟必须开启，不然CAN1不进中断 */
    rcu_periph_clock_enable(RCU_CAN0);
    rcu_periph_clock_enable(RCU_CAN1);
    rcu_periph_clock_enable(CAN1_RX_GPIO_CLK);
    rcu_periph_clock_enable(CAN1_TX_GPIO_CLK);
	
    /* 设置CAN1 TX */
    gpio_output_options_set(CAN1_TX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, CAN1_TX_PIN); 
    gpio_mode_set(CAN1_TX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CAN1_TX_PIN); 
    gpio_af_set(CAN1_TX_GPIO_PORT, GPIO_AF_9, CAN1_TX_PIN);
    /* 设置CAN1 RX */
    gpio_output_options_set(CAN1_RX_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, CAN1_RX_PIN); 
    gpio_mode_set(CAN1_RX_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CAN1_RX_PIN); 
    gpio_af_set(CAN1_RX_GPIO_PORT, GPIO_AF_9, CAN1_RX_PIN);
   
    can_parameter_struct can_parameter;
    can_filter_parameter_struct can_filter;

    /* 初始化CAN1 */
    can_deinit(CAN1); 
  
 	  /* 是否使能时间触发功能 */
   	can_parameter.time_triggered = DISABLE;
   	/* 是否使用自动离线管理 使用自动离线管理可以在节点出错离线后适时自动恢复，不需要软件干预 */   
  	can_parameter.auto_bus_off_recovery = DISABLE;
  	/* 是否使用自动唤醒功能 (ENABLE/DISABLE)，使能自动唤醒功能后它会在监测到总线活动后自动唤醒 */	  
  	can_parameter.auto_wake_up = DISABLE;
  	/* 是否使用自动重传功能 (ENABLE/DISABLE)，使用自动重传功能时，会一直发送报文直到成功为止 */
  	can_parameter.no_auto_retrans = DISABLE;
  	/* 是否使用锁定接收 FIFO(ENABLE/DISABLE)，锁定接收 FIFO 后，若FIFO溢出时会丢弃新数据，否则
  	   在 FIFO 溢出时以新数据覆盖旧数据 */	
  	can_parameter.rec_fifo_overwrite = DISABLE;
  	/* 设置发送报文的优先级判定方法 (ENABLE/DISABLE)，使能时，以报文存入发送邮箱的先后顺序来发送，
  	   否则按照报文 ID 的优先级来发送 */
  	can_parameter.trans_fifo_order = ENABLE;
  	/* 正常工作模式 */	
  	can_parameter.working_mode = CAN_NORMAL_MODE;
  	/* 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq 一般为1*/	 
  	can_parameter.resync_jump_width  = CAN_BT_SJW_1TQ;	
  	/* Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq 一般大于CAN_BS2*/
  	can_parameter.time_segment_1  = CAN_BT_BS1_7TQ; 
  	/* Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq */
  	can_parameter.time_segment_2  = CAN_BT_BS2_6TQ;
  	/* CAN波特率 = 42M/(swj+tbs1+tbs1)/Prescaler*/
  	switch(CAN1_BAUDRATE){
  		/* 1M 波特率 */
  		case 1000:
  			can_parameter.prescaler=3;
  			break;
  		/* 500K 波特率 */
  		case 500:
  			can_parameter.prescaler=6;
  			break;
  		case 250:
  		/* 250K 波特率 */  			
  			can_parameter.prescaler=12;
  			break;
  		case 125:
  		/* 125K 波特率 */  			
  			can_parameter.prescaler=24;
  			break;
  	}
  	can_init(CAN1, &can_parameter);  //初始化CAN1
    
    /* 配置过滤器 */
    /* CAN1 过滤器15 CAN1的过滤器编号要从15开始，不然无法进中断*/
    can_filter.filter_number = 15;

    /* 配置过滤器32位掩码模式 */    
    can_filter.filter_mode        = CAN_FILTERMODE_MASK; 
    can_filter.filter_bits        = CAN_FILTERBITS_32BIT;
    /* 接收所有数据，不过滤 */
    can_filter.filter_list_high   = 0x0000; 
    can_filter.filter_list_low    = 0x0000; 
    can_filter.filter_mask_high   = 0x0000;
    can_filter.filter_mask_low    = 0x0000;
    can_filter.filter_fifo_number = CAN_FIFO1;
    can_filter.filter_enable      = ENABLE;
    can_filter_init(&can_filter);
    
    can_interrupt_enable(CAN1, CAN_INT_RFNE1);     
  
}   
 




/**
  * @brief   CAN0 发送
  * @param   msg 要发送的数组地址
  * @param   len 要发送的数据长度
  * @retval  0 成功 1 失败
  */
u8 can0_send_msg(u8* msg,u8 len)
{ 
  u8 mbox;
  u16 i=0;
  can_trasnmit_message_struct TxMessage;
  TxMessage.tx_sfid = 0x12;  // 标准ID
  TxMessage.tx_efid = 0x12;  // 扩展ID 
  TxMessage.tx_ff   = CAN_FF_STANDARD;       // 标准帧 tx_ff: CAN_FF_STANDARD, CAN_FF_EXTENDED
  TxMessage.tx_ft   = CAN_FT_DATA;           // 数据帧 CAN_FT_DATA, CAN_FT_REMOTE
  TxMessage.tx_dlen = len;                   // 数据长度
  for(i=0;i<len;i++)
  TxMessage.tx_data[i]=msg[i];                 
  mbox= can_message_transmit(CAN0, &TxMessage);   
  i=0;
  while((can_transmit_states(CAN0, mbox)!=CAN_TRANSMIT_OK)&&(i<0XFFF))i++;  
  if(i>=0XFFF)return 1;
  return 0;   
}



/**
  * @brief   CAN1 发送
  * @param   msg 要发送的数组地址
  * @param   len 要发送的数据长度
  * @retval  0 成功 1 失败
  */
u8 can1_send_msg(u8* msg,u8 len)
{ 
  u8 mbox;
  u16 i=0;
  can_trasnmit_message_struct TxMessage;
  TxMessage.tx_sfid = 0x12;  // 标准ID
  TxMessage.tx_efid = 0x12;  // 扩展ID 
  TxMessage.tx_ff   = CAN_FF_STANDARD;       // 标准帧 tx_ff: CAN_FF_STANDARD, CAN_FF_EXTENDED
  TxMessage.tx_ft   = CAN_FT_DATA;           // 数据帧 CAN_FT_DATA, CAN_FT_REMOTE
  TxMessage.tx_dlen = len;                   // 数据长度
  for(i=0;i<len;i++)
  TxMessage.tx_data[i]=msg[i];                 
  mbox= can_message_transmit(CAN1, &TxMessage);   
  i=0;
  while((can_transmit_states(CAN1, mbox)!=CAN_TRANSMIT_OK)&&(i<0XFFF))i++; 
  if(i>=0XFFF)return 1;
  return 0;   
}
