/*
 * ext_power_obj.c
 *
 *  Created on: Sep 11, 2016
 *      Author: root
 */

#include "ext_power_obj.h"
#include "adc.h"





extern ADC_HandleTypeDef hadc;


int32_t ext_pow_get_voltage()
{
    return vdc1;
}
void ext_pow_set_status(uint8_t status)
{
    external_power_status = status;
}
int ext_pow_get_status()
{
    return external_power_status;
}


void extpow_measure_voltage()
{
	static uint32_t counter;
	counter++;


	ADC_ChannelConfTypeDef sConfig;

	// Select Channel 0 to be converted (VDC1)
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	sConfig.Channel = ADC_CHANNEL_1 | ADC_CHANNEL_2;
	sConfig.Rank = ADC_RANK_NONE;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	//***
	HAL_ADC_Start(&hadc);
	if(HAL_ADC_PollForConversion(&hadc, 1000) != HAL_OK)
	{
		//Error_Handler();
	}
	uint32_t adc_ch0 = HAL_ADC_GetValue(&hadc);
	vdc1 = adc_ch0 * 3300 * 25 / 4096;
	HAL_ADC_Stop(&hadc);
	//***************************************************************************
	// Select Channel 1 to be converted (VDC2)
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	sConfig.Channel = ADC_CHANNEL_0 | ADC_CHANNEL_2;
	sConfig.Rank = ADC_RANK_NONE;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	//***
	HAL_ADC_Start(&hadc);
	if(HAL_ADC_PollForConversion(&hadc, 1000) != HAL_OK)
	{
		//Error_Handler();
	}
	uint32_t adc_ch1 = HAL_ADC_GetValue(&hadc);
	vdc2 = adc_ch1 * 3300 * 25 / 4096;
	HAL_ADC_Stop(&hadc);
	//***************************************************************************
	// Select Channel 2 to be converted (VDCA)
	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	sConfig.Channel = ADC_CHANNEL_0 | ADC_CHANNEL_1;
	sConfig.Rank = ADC_RANK_NONE;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	//***
	HAL_ADC_Start(&hadc);
	if(HAL_ADC_PollForConversion(&hadc, 1000) != HAL_OK)
	{
		//Error_Handler();
	}
	uint32_t adc_ch2 = HAL_ADC_GetValue(&hadc);
	vdca = adc_ch2 * 3300 * 25 / 4096;
	HAL_ADC_Stop(&hadc);
}
