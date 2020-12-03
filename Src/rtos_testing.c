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
TaskHandle_t xTaskA;

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
}
int tick = 0;
void TASK_A(void *p)
{
	while(1)
	{
		uint32_t a0, a1, a2, a3;
						
		a3 = (tick / 1) % 10;
		a2 = (tick / 10) % 10;
		a1 = (tick / 100) % 10;
		a0 = (tick / 1000) % 10;
		
		display_number(0, a0);
		vTaskDelay(5);
		
		display_number(1, a1);
		vTaskDelay(5);
		
		display_number(2, a2);
		vTaskDelay(5);

		display_number(3, a3);
		vTaskDelay(5);
	}
}



void TASK_B(void *p)
{
	int start = 0;
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphore2= xSemaphoreCreateBinary();
	while(1)
	{
		if(	xSemaphoreTake(xSemaphore, 100) == pdTRUE)
		{
			start = start ^ 1;
		}
		if(xSemaphoreTake(xSemaphore2, 0) == pdTRUE)
		{
			tick = 0;
		}
		if(start)
		{
			tick = tick + 1;
		}
		
		//vTaskDelay(1000);
	}	
	
}
/*
void TASK_C(void *p)
{
	char *c = "vTask_C is now executing. \r\n";
	unsigned int k = 0;
	while(1)
	{
		//xSemaphoreTake(xSemaphoreUart, portMAX_DELAY);
		k=0;
		//xSemaphoreGive(xSemaphoreUart);
		while(c[k])
		{
			Uart_Printf("%c", c[k]);
			k = k+1;
			vTaskDelay(10);
		}
		vTaskDelay(1000);
	}
}*/
	
/*
void vTaskCode(void * pvParameters)
{
	for(;;)
	{
		taskENTER_CRITICAL();
		vTaskDelay(5000);
		__NOP();
		taskEXIT_CRITICAL();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if(GPIO_PIN == GPIO_PIN_0)
	{
		led_toggle(LED_1);
	}
}
*/
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if (GPIO_PIN == GPIO_PIN_0)
	{
		gTickCount = 0;
		Uart_Printf("EXTI-0 interrupt. \r\n");
	}
}
static void vTaskCode(void * pvParameters)
{
	while(1)
	{
		//taskENTER_CRITICAL();
		gTickCount = gTickCount + 1;
		//taskENTER_CRITICAL();
		if((gTickCount % 1000) == 0)
		{
			Uart_Printf("%d \r\n", gTickCount / 1000);
		}
		vTaskDelay(1);
	}
}
*/
/*
void vTaskCode(void * pvParameters)
{
	for(;;)
	{
		if (is_key_pressed(KEY_LEFT))
		{
			Uart_Printf("LEFT KEY PESSED \r\n");
		}
		else if (is_key_pressed(KEY_CENTER))
		{
			Uart_Printf("CENTER KEY PESSED \r\n");
		}
		else if (is_key_pressed(KEY_RIGHT))
		{
			Uart_Printf("RIGHT KEY PESSED \r\n");
		}
	}
}

void vTaskCode2(void * pvParameters)
{
	for(;;)
	{
		if ((k%5)==0)
		{
			static uint32_t n = 0;
			led_off_all();
			led_on(LED_0 + n);
			n = (n + 1) % 8;
		}	
	}
}

void vTaskCode3(void * pvParameters)
{
	uint32_t sec = 0;
	for(;;)
	{
		uint32_t tick;
		uint32_t a0, a1, a2, a3;
		
		tick = xTaskGetTickCount();
		a3 = (tick / 10) % 10;
		a2 = (tick / 100) % 10;
		a1 = (tick / 1000) % 10;
		a0 = (tick / 10000) % 10;
		
		display_number(0, a0);
		vTaskDelay(5);
		
		display_number(1, a1);
		vTaskDelay(5);
		
		display_number(2, a2);
		vTaskDelay(5);

		display_number(3, a3);
		vTaskDelay(5);
	}
}

void vTaskCode4(void * pvParameters)
{
	for(;;)
	{
				if ((k%10) == 0)
		{
			Uart_Printf("CDS Value : %d \r\n", get_cds_value());	
		}
		
		k = k + 1;	
		}	
}*/


void start_freertos_testing(void)
{/*
	xSemaphoreUart = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphoreUart);
	*/
	
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
                 NULL);	
/*
  xTaskCreate(TASK_C,
								"TASK_C",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );	
	xTaskCreate(vTaskCode,
								"vTaskCode",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );    
	

		xTaskCreate(vTaskCode2,
								"vTaskCode2",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY+1,
                NULL );    */
	
	/*
		xTaskCreate(vTaskCode3,
								"vTaskCode3",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );    
		xTaskCreate(vTaskCode4,
								"vTaskCode4",       
								configMINIMAL_STACK_SIZE, 
								NULL,    
								tskIDLE_PRIORITY,
                NULL );    */
	
	vTaskStartScheduler();
}
