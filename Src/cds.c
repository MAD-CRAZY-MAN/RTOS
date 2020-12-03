#include "stm32f1xx.h"
#include "cds.h"

extern ADC_HandleTypeDef hadc1;

uint32_t get_cds_value()
{
	return HAL_ADC_GetValue(&hadc1);
}

