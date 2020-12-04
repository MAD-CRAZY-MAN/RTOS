#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "key.h"
#include "led.h"
#include "cds.h"
#include "fnd.h"
#include "uart.h"
#include "stm32f10x.h"
#include "semphr.h"
#include "timers.h"
/*
*
*/

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)
void vApplicationIdleHook()
{__nop();
}

TaskHandle_t xTaskA, xTaskB, xTaskC, xTaskD;

QueueHandle_t xQueue1, xQueue2;
void queue_init()
{
	xQueue1 = xQueueCreate(8, sizeof(int));
	xQueue2 = xQueueCreate(8, sizeof(int));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if(GPIO_PIN == GPIO_PIN_0)
	{
		vTaskNotifyGiveFromISR (xTaskA, NULL);
	}
	else if(GPIO_PIN_1)
	{
			Uart_Printf("interrupt\r\n");
	}
}

void TASK_A(void *p)//cds
{
	uint32_t value;
	uint32_t start = 0;
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;
	for(;;)
	{
		if(ulTaskNotifyTake(pdTRUE, 100))
		{start = start ^ 1;
		}
		if(start)
		{
		value = get_cds_value();	
		xQueueSendFromISR(xQueue1, &value, &xHigherPriorityTaskWoken);
		xQueueSendFromISR(xQueue2, &value, &xHigherPriorityTaskWoken);
		xTaskNotifyGive(xTaskD);
		}
	}
}

void TASK_B(void *p)//uart
{
	uint32_t msg;
	for(;;)
	{
		xQueueReceive(xQueue1, &msg, (uint32_t)-1);
		Uart_Printf("uart cds: %d\r\n", msg);
	}
}

void TASK_C(void *p)//fnd
{
		uint32_t msg;
	for(;;)
	{
		xQueueReceive(xQueue2, &msg, (uint32_t)0);
	
		uint32_t a0, a1, a2, a3;
		
		a3 = (msg / 10) % 10;
		a2 = (msg / 100) % 10;
		a1 = (msg / 1000) % 10;
		a0 = (msg / 10000) % 10;
		
		display_number(0, a0);
		vTaskDelay(5); //block
		
		display_number(1, a1);
		vTaskDelay(5);
		
		display_number(2, a2);
		vTaskDelay(5);

		display_number(3, a3);
		vTaskDelay(5);
	}
}

void TASK_D(void *p)
{
	for(;;)
	{
		ulTaskNotifyTake(pdTRUE, -1);
		led_on(LED_0);
		vTaskDelay(50);
		led_off(LED_0);
	}
}


void TASK_E(TimerHandle_t xTimerHandle)//led timer 1ms
{
	for(;;)
	{
		led_toggle(LED_1);
		vTaskDelay(1000);
	}
}


void start_freertos_testing(void)
{
	queue_init();
	
	unsigned int timer_id = 1;
	TimerHandle_t handle1 = xTimerCreate("TIMER_FUC_0",
																			100,
																			pdTRUE,
																			(void *)timer_id,
																			TASK_E);
	xTimerStart(handle1, timer_id);
																																				
	xTaskCreate(TASK_A,
								"TASK_A",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                &xTaskA );

	xTaskCreate(TASK_B,
								"TASK_B",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                &xTaskB);	

  xTaskCreate(TASK_C,
								"TASK_C",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                &xTaskC );
	xTaskCreate(TASK_D,
								"TASK_D",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                &xTaskD );


	vTaskStartScheduler();
}
