/*
 * @Description: 
 * @Version: v1.0.0
 * @Autor: gxf
 * @Date: 2022-02-06 16:32:04
 * @LastEditors: gxf
 * @LastEditTime: 2022-02-06 16:33:06
 */
#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__


#include "lwip/err.h"
#include "lwip/netif.h"

err_t ethernetif_init(struct netif *netif);
void ethernetif_input( void * pvParameters );

#endif 