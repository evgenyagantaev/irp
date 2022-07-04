/*
 * alarm_task.c
 *
 *  Created on: Jun 30, 2022
 *      Author: agant
 */
#include "main.h"
#include "gpio.h"

extern int alarm;
extern uint battery_type;
extern int turn_off_display;
extern uint16_t values[];
extern int presentation_complete;

void alarm_task()
{
	static uint32_t frozen_seconds_tick = 0;

	if (presentation_complete)
	{
		if(seconds_tick > frozen_seconds_tick)
		{
			uint max_index = (battery_type == 42) ? 12 : 10;

			for(int i=0; i<8; i++)
			{
				if(values[i] <= 29)
					alarm = 1;
			}

			for(int i=8; i<max_index; i++)
			{
				int temperature = values[i] / 10 - 273;
				if((temperature < -30) || (temperature > 50))
					alarm = 1;
			}
		}

		if(alarm)
		{
			// turn off display
			GPIOA->BRR = ind_7_seg_1_Pin;
			GPIOA->BRR = ind_7_seg_2_Pin;
			GPIOA->BRR = ind_7_seg_4_Pin;
			GPIOA->BRR = ind_7_seg_8_Pin;

			// light emergency led
			HAL_GPIO_WritePin(GPIOA, SVD3_6_catode_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, SVD2_5_catode_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, SVD1_4_catode_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(GPIOA, SVD3_6_catode_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);

			while(1)
			{
				HAL_Delay(500);
			}
		}
	}
}
