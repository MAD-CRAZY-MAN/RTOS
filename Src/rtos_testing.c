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


/*
uint32_t k = 0;
int gA, gB;
void vTaskCode(void * pvParameters)
{
	for(;;)
	{
		Uart_Printf("gA : %d \r\n", gA++);
		vTaskDelay(1000);
	}
}

void vTaskCode2(void * pvParameters)
{
	for(;;)
	{
		Uart_Printf("gB : %d\r\n", gB++);
		for(int k=0;k <0x1000000;k++);
	}
}
*/
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)
void vApplicationIdleHook()
{__nop();
}
int gTickCount;
int gA, gB;

SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xSemaphore2;
TaskHandle_t xTaskB;
/*
void TimerCallbackFunc1(TimerHandle_t xTimerHandle)
{
	led_toggle(0);
}

void TimerCallbackFunc2(TimerHandle_t xTimerHandle)
{
	led_toggle(1);
}
*/
typedef struct Message
{
	uint32_t tick;
	uint32_t value;
}message_t;

QueueHandle_t xQueue;

void queue_init()
{
	xQueue = xQueueCreate(8, sizeof(int));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	uint32_t message = 1;
	BaseType_t xHigherPriorityTaskWoken=pdFALSE;
	xQueueSendFromISR(xQueue, &message, &xHigherPriorityTaskWoken);
	message++;
	if(xHigherPriorityTaskWoken)
	{
		taskYIELD();
	}
}

void TASK_A(void *p)
{
	for(;;)
	{
		__NOP();
	}
}

void TASK_B(void *p)
{
	uint32_t msg;
	for(;;)
	{
		xQueueReceive(xQueue, &msg, (uint32_t)-1);
		Uart_Printf("%d\r\n", msg);
		__NOP();
	}
}



void start_freertos_testing(void)
{/*
	xSemaphoreUart = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphoreUart);
	*/
	queue_init();
	/*
	unsigned int timer_id = 1;
	TimerHandle_t handle1 = xTimerCreate("TIMER_FUC_0",
																			100,
																			pdTRUE,
																			(void *)timer_id,
																			TimerCallbackFunc1);
	xTimerStart(handle1, timer_id);
	timer_id =2;

	TimerHandle_t handle2 = xTimerCreate("TIMER_FUC_1",
																			1000,
																			pdTRUE,
																			(void *)timer_id,
																			TimerCallbackFunc2);
	xTimerStart(handle2, timer_id);																			
		*/																						
	xTaskCreate(TASK_A,
								"TASK_A",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY+1,
                NULL );

	xTaskCreate(TASK_B,
								"TASK_B",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY+1,
                 &xTaskB);	
/*
  xTaskCreate(TASK_C,
								"TASK_C",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );	*/

	vTaskStartScheduler();
}
