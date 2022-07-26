/**
  ******************************************************************************
  * @file    md_app.c
  * @author  gxf
  * @version V1.0.0
  * @date    2021.09.06
  * @brief   小远机器人初始化文档
 ==============================================================================
 */
#include "XiaoyuanConfig.h"
#include "bsp_can.h"
#include "bsp_iwdg.h"
#include "bsp_sys.h"
#include "bsp_systick.h"
#include "bsp_time.h"
#include "bsp_uart.h"
#include "bsp_gpio.h"
#include "bsp_enet.h"
#include "md_log.h"


#include "md_lwip.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#define INIT_TASK_PRIO   ( tskIDLE_PRIORITY + 1 )
#define LED_TASK_PRIO    ( tskIDLE_PRIORITY + 2 )


 
void tcp_client_task(void *arg);
void init_task(void * pvParameters);
static void online_inspection(void);
static void key_detection(void);
static void app_init(void);


/**
 * [bsp_init description]
 * @author Gxf
 * @dateTime 2021-10-13
 * @brief    [description] 底层硬件初始化
 * @note     [description]
 */
void bsp_init(void)
{
//  sysTick_init();
  nvic_configuration();
  bsp_can0_init();
  bsp_can1_init();
  bsp_gpio_init();
	bsp_usart0_init();
  bsp_usart1_init();
  bsp_usart2_init();
  bsp_usart3_init();
  bsp_usart4_init();
  bsp_usart5_init();
//  bsp_time1_init();
}

/**
 * [module_init description]
 * @author Gxf
 * @dateTime 2021-10-13
 * @brief    [description] 用户模块初始化
 * @note     [description]
 */
void module_init(void)
{
 app_init(); 
}

/**
 * [app_init description]
 * @author Gxf
 * @dateTime 2021-10-13
 * @brief    [description] 用于添加任务
 * @note     [description]
 */
static void app_init(void)
{
  xTaskCreate(init_task, "INIT", configMINIMAL_STACK_SIZE * 2, NULL, INIT_TASK_PRIO, NULL);
}



/*!
    \brief      init task
    \param[in]  pvParameters not used
    \param[out] none
    \retval     none
*/
void init_task(void * pvParameters)
{
    
    /* configure ethernet (GPIOs, clocks, MAC, DMA) */ 
    enet_system_setup();

    /* initilaize the LwIP stack */
    lwip_stack_init();


    /* start toogle LED task every 250ms */
    xTaskCreate(tcp_client_task, "tcp", DEFAULT_THREAD_STACKSIZE, NULL, LED_TASK_PRIO, NULL);
   
    for( ;; ){
        vTaskDelete(NULL);
    }
}

u8 sendbuf[1460];
void tcp_client_task(void *arg)
{
	  u32 count = 0;
    int  ret, recvnum, sockfd = -1;
    int tcp_port = 7321;
    struct sockaddr_in svr_addr, clt_addr;
    char buf[100];
    ip_addr_t ipaddr;
    memset(sendbuf,0,1460);
    IP4_ADDR(&ipaddr, IP_S_ADDR0, IP_S_ADDR1, IP_S_ADDR2, IP_S_ADDR3);

    /* set up address to connect to */
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(tcp_port);
    svr_addr.sin_addr.s_addr = ipaddr.addr;

    clt_addr.sin_family = AF_INET;
    clt_addr.sin_port = htons(tcp_port);
    clt_addr.sin_addr.s_addr = htons(INADDR_ANY);

    while(1){
        vTaskDelay(1000);
        /* create the socket */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd < 0){
               continue;
        }

        ret = bind(sockfd, (struct sockaddr *)&clt_addr, sizeof(clt_addr));
        if(ret < 0){ 
            lwip_close(sockfd);
            sockfd = -1;
            continue;
        }

        /* connect */
        ret = connect(sockfd, (struct sockaddr *)&svr_addr, sizeof(svr_addr));
        if(ret < 0){
            lwip_close(sockfd);
            sockfd = -1;
            continue;
        }

        while(-1 != sockfd){
            /* reveive packets, and limit a reception to MAX_BUF_SIZE bytes */
//            recvnum = recv(sockfd, buf, 50, 0);
//            if(recvnum <= 0){
//                lwip_close(sockfd);
//                sockfd = -1;
//                break;
//            }
					 count++;
					sendbuf[0] = count&0xFF;
					sendbuf[1] = (count>>8)&0xFF;
					sendbuf[2] = (count>>16)&0xFF;
					sendbuf[3] = (count>>24)&0xFF;
            send(sockfd, sendbuf, 1460, 0);  
					  vTaskDelay(10);
					  
        }

        lwip_close(sockfd);
        sockfd = -1;
    }
}


