#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "md_task.h"
#include "md_app.h"
#include "FreeRTOS.h"
#include "task.h"
int main(void)
{ 
	bsp_init();
	module_init();
	// while(1)
	// {	
    // task_start();
 	// }
    vTaskStartScheduler();

    while(1){
    }
}
