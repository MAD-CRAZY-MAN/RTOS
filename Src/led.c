#include "stm32f1xx.h"
#include "led.h"

void led_on(int n)
{
	if (n == LED_0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}
	else if (n == LED_1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	else if (n == LED_2)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	else if (n == LED_3)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	}
	else if (n == LED_4)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	}
	else if (n == LED_5)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
	}
	else if (n == LED_6)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
	}
	else if (n == LED_7)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	}
}

void led_off(int n)
{
	if (n == LED_0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	}
	else if (n == LED_1)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	}
	else if (n == LED_2)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else if (n == LED_3)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	}
	else if (n == LED_4)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	}
	else if (n == LED_5)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
	}
	else if (n == LED_6)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else if (n == LED_7)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	}
}

void led_toggle(int n)
{
	if (n == LED_0)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
	else if (n == LED_1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
	}
	else if (n == LED_2)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
	}
	else if (n == LED_3)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
	}
	else if (n == LED_4)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
	}
	else if (n == LED_5)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
	}
	else if (n == LED_6)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
	}
	else if (n == LED_7)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);
	}
}

void led_off_all()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_SET);
}

void led_on_all()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_RESET);
}

