/*
 * seven_segment_display.c
 *
 *  Created on: 18 июн. 2022 г.
 *      Author: root
 */

#include "seven_segment_display.h"
#include "stm32l0xx_hal.h"
#include "gpio.h"

extern int turn_off_display;

extern int svd1_light;
extern int svd2_light;
extern int svd3_light;
extern int svd4_light;
extern int svd5_light;
extern int svd6_light;


void seven_segment_display(uint number)
{
	static uint lightened_digit = 0;
	static uint32_t frozen_systick;
	uint32_t current_systick = HAL_GetTick();

	if(turn_off_display)
	{
		//turn off display
		GPIOA->BRR = SVD1_4_catode_Pin;
		GPIOA->BRR = SVD2_5_catode_Pin;
		GPIOA->BRR = SVD3_6_catode_Pin;
	}
	else
	{
		if(current_systick >= (frozen_systick + 7)) // 7 ms on every digit
		{
			frozen_systick = current_systick;
			lightened_digit = (lightened_digit + 1) % 3;
		}

		uint aux;

		if(lightened_digit == 0)
		{
			aux = ((uint)(number/1000)) * 1000;
			aux = number - aux;
			aux = (uint)(aux/100);
		}
		else if(lightened_digit == 1)
		{
			aux = ((uint)(number/100)) * 100;
			aux = number - aux;
			aux = (uint)(aux/10);
		}
		else if(lightened_digit == 2)
		{
			aux = ((uint)(number/10)) * 10;
			aux = number - aux;
		}

		GPIOA->BRR = SVD1_4_catode_Pin;
		GPIOA->BRR = SVD2_5_catode_Pin;
		GPIOA->BRR = SVD3_6_catode_Pin;


		GPIOA->BSRR = ind_7_seg_1_Pin;
		GPIOA->BSRR = ind_7_seg_2_Pin;
		GPIOA->BSRR = ind_7_seg_4_Pin;
		GPIOA->BSRR = ind_7_seg_8_Pin;
		if(((uint)1 & aux) > 0)
			GPIOA->BRR = ind_7_seg_1_Pin;
		if((((uint)1 << 1) & aux) > 0)
			GPIOA->BRR = ind_7_seg_2_Pin;
		if((((uint)1 << 2) & aux) > 0)
			GPIOA->BRR = ind_7_seg_4_Pin;
		if((((uint)1 << 3) & aux) > 0)
			GPIOA->BRR = ind_7_seg_8_Pin;

		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_RESET);

		if(lightened_digit == 0)
		{
			GPIOA->BSRR = SVD3_6_catode_Pin;
			if(svd3_light)
				HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);
			if(svd6_light)
				HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_SET);
		}
		else if(lightened_digit == 1)
		{
			GPIOA->BSRR = SVD2_5_catode_Pin;
			if(svd2_light)
				HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);
			if(svd5_light)
				HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_SET);
		}
		else if(lightened_digit == 2)
		{
			GPIOA->BSRR = SVD1_4_catode_Pin;
			if(svd1_light)
				HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);
			if(svd4_light)
				HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_SET);
		}

	}


}
