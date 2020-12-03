#include "stm32f1xx.h"
#include <string.h>
#include <stdarg.h>

extern UART_HandleTypeDef huart1;

void Uart_SendByte(char c) 
{
	while ((USART1->SR & UART_FLAG_TXE)==0); 
	USART1->DR = c;
}

void Uart_Printf(const char *fmt, ...) 
{
	va_list ap;
	char string[64];

	va_start(ap, fmt);
	vsprintf(string, fmt, ap);
  
	/*
	* do not use HAL_UART_Transmit in FreeRTOS testing
	* data can not be transmitted in this function in case of HAL_UART_STATE_BUSY_TX
	* HAL_UART_STATE_READY must be set before transmitting new string.
	* HAL_UART_STATE_READY will be set after transmitting the string completely.
	*/
	//HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), (uint32_t)-1);
	
	for (int k=0; k<strlen(string); k++)
	{
		Uart_SendByte(string[k]);
	}

	va_end(ap);
}
