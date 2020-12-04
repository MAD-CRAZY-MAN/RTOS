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

void TimerCallbackFunc(TimerHandle_t xTimerHandle)
{
	led_toggle(1);
}
/*
typedef struct Message
{
	uint32_t tick;
	uint32_t value;
}message_t;

QueueHandle_t xQueue;

void queue_init()
{
	xQueue = xQueueCreate(8, sizeof(message_t));
}*/
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if(GPIO_PIN == GPIO_PIN_0)
	{
		eTaskState state = eTaskGetState(xTaskA);
		Uart_Printf("%d \r\n", state);
		
		xSemaphoreGiveFromISR(xSemaphore, NULL);
		
		state = eTaskGetState(xTaskA);
		Uart_Printf("%d \r\n", state);
		
		Uart_Printf("EXTI-0 interrupt \r\n");
	}
	else if (GPIO_PIN == GPIO_PIN_1)
	{
		xSemaphoreGiveFromISR(xSemaphore2, NULL);
		Uart_Printf("EXTI-1 interrupt \r\n");
	}
}*/

void TASK_A(void *p)
{
	for(;;)
	{
		vTaskDelay((uint32_t)-1);
	}
}
/*
void TASK_B(void *p)
{
	
	for(;;)
	{
		uint32_t count = ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		Uart_Printf("count: %d\r\n", count);
	}
}*/



void start_freertos_testing(void)
{/*
	xSemaphoreUart = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphoreUart);
	*/
	//queue_init();
	unsigned int timer_id = 0;
	TimerHandle_t handle = xTimerCreate("TIMER_FUC_0",
																			1000,
																			pdTRUE,
																			(void *)timer_id,
																			TimerCallbackFunc);
xTimerStart(handle, timer_id);																			
																								
	/*	  xTaskCreate(TASK_A,
								"TASK_A",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );

	xTaskCreate(TASK_B,
								"TASK_B",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY+1,
                 &xTaskB);	

  xTaskCreate(TASK_C,
								"TASK_C",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );	*/

	vTaskStartScheduler();
}
