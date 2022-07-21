/*
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2022-02-06 16:41:11
 * @LastEditors: gxf
 * @LastEditTime: 2022-02-07 11:56:12
 */
#include "md_lwip.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/dhcp.h"
#include "tcpip.h"
#include "ethernetif.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
extern xSemaphoreHandle g_rx_semaphore;
struct netif g_mynetif;

/**
 * @description: LWIP 协议栈初始化
 * @author: gxf
 * @param {*}
 * @return {*}
 */
 
void lwip_stack_init(void)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

    /* create tcp_ip stack thread */
    tcpip_init( NULL, NULL );

    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);

    netif_add(&g_mynetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

    /* registers the default network interface */
    netif_set_default(&g_mynetif);

    /* when the netif is fully configured this function must be called */
    netif_set_up(&g_mynetif);
    netif_set_link_up(&g_mynetif);
}

/**
 * @description: 以太网中断
 * @author: gxf
 * @param {*}
 * @return {*}
 */
void ENET_IRQHandler(void)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    /* 接收中断 */
    if(SET == enet_interrupt_flag_get(ENET_DMA_INT_FLAG_RS)){ 
        /* 发送信号量给lwip的底层接收 */
        xSemaphoreGiveFromISR(g_rx_semaphore, &xHigherPriorityTaskWoken);
    }

    /* clear the enet DMA Rx interrupt pending bits */
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_RS_CLR);
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_NI_CLR);

    /* switch tasks if necessary */
    if(pdFALSE != xHigherPriorityTaskWoken){
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}