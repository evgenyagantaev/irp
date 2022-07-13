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

extern int express_charging;
extern uint32_t express_charging_start_moment;
extern int norm_charging;
extern uint32_t norm_charging_start_moment;

static uint32_t alarm_suspect_moment = 0;

#define EXPRESS_CHARGING_TIMEOUT 45
#define ALARM_DROP_TIMEOUT 120

void alarm_task()
{
	static uint32_t frozen_seconds_tick = 0;
	static int cumulative_alarm = 0;

	if (presentation_complete)
	{
		if(seconds_tick > frozen_seconds_tick)
		{
			uint max_index = (battery_type == 42) ? 12 : 10;

			int aux = 0;

			for(int i=0; i<8; i++)
			{
				if(values[i] <= 29)
					aux = 1;
			}

			for(int i=8; i<max_index; i++)
			{
				int temperature = values[i] / 10 - 273;
				if((temperature < -30) || (temperature > 50))
					aux = 1;
			}

			cumulative_alarm += aux;
			if(aux)
			{
				alarm_suspect_moment = seconds_tick;
			}
			if((seconds_tick - alarm_suspect_moment) > ALARM_DROP_TIMEOUT)
			{
				cumulative_alarm = 0;
			}
			if(cumulative_alarm > 2)
			{
				alarm = 1;
			}


			// check express charging timeout
			if(((seconds_tick - express_charging_start_moment) > EXPRESS_CHARGING_TIMEOUT) && express_charging)
			{
				alarm = 1;
			}

			if(((seconds_tick - norm_charging_start_moment) > EXPRESS_CHARGING_TIMEOUT) && norm_charging)
			{
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

			//turn off charging		>>>>>>>>>>>>
			HAL_GPIO_WritePin(GPIOB, express_charge2_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOC, norm_charge1_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOC, norm_charge2_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
			//*****
			HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_RESET);
			HAL_Delay(500);
			//*****
			HAL_GPIO_WritePin(GPIOB, express_charge2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, norm_charge1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, norm_charge2_Pin, GPIO_PIN_RESET);
			//turn off charging		<<<<<<<<<<<<<

			while(1)
			{
				HAL_Delay(500);
			}
		}
	}
}
