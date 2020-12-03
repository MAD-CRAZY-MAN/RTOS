#include "stm32f1xx.h"
#include "key.h"

uint8_t is_key_pressed(int n)
{
	GPIO_PinState state = GPIO_PIN_SET;
	
	if (n == KEY_LEFT)
	{
		state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
	}
	else if (n == KEY_CENTER)
	{
		state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
	}
	else if (n == KEY_RIGHT)
	{
		state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
	}	
	
	if (state == GPIO_PIN_RESET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

