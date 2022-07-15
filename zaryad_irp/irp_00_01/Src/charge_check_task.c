/*
 * charge_check_task.c
 *
 *  Created on: Jul 5, 2022
 *      Author: agant
 */

#include <stdint.h>
#include "gpio.h"

extern int svd1_light;
extern int svd2_light;
extern int svd3_light;
extern int svd4_light;
extern int svd5_light;
extern int svd6_light;


extern int express_charging;
extern int norm_charging;
extern int discharging;
extern uint32_t seconds_tick;
extern uint32_t battery_type;

volatile int express_charging_start_moment = 0;
volatile int norm_charging_start_moment = 0;
volatile int discharging_start_moment = 0;

void charge_check_task()
{
	static int expr_charging_started = 0;
	static int norm_charging_started = 0;
	static int discharging_started = 0;

	if(express_charging)
	{
		if(!expr_charging_started)
		{
			expr_charging_started = 1;

			// turn off display
			GPIOA->BRR = ind_7_seg_1_Pin;
			GPIOA->BRR = ind_7_seg_2_Pin;
			GPIOA->BRR = ind_7_seg_4_Pin;
			GPIOA->BRR = ind_7_seg_8_Pin;


			// start express charging
			if(battery_type == 42)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_SET);
			}
			else if(battery_type == 21)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge2_Pin, GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_SET);
			}

			express_charging_start_moment = seconds_tick;
		}
		else // started yet
		{
			if((GPIOB->IDR & express_charge_finish_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
				express_charging = 0;
			}

		}
	}
	else if(norm_charging)
	{
		if(!norm_charging_started)
		{
			norm_charging_started = 1;

			// turn off display
			GPIOA->BRR = ind_7_seg_1_Pin;
			GPIOA->BRR = ind_7_seg_2_Pin;
			GPIOA->BRR = ind_7_seg_4_Pin;
			GPIOA->BRR = ind_7_seg_8_Pin;


			// start norm charging
			if(battery_type == 42)
			{
				HAL_GPIO_WritePin(GPIOC, norm_charge1_Pin, GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_RESET);
			}
			else if(battery_type == 21)
			{
				HAL_GPIO_WritePin(GPIOC, norm_charge2_Pin, GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_RESET);
			}

			norm_charging_start_moment = seconds_tick;
		}

		else // started yet
		{
			if((GPIOB->IDR & express_charge_finish_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
				norm_charging = 0;
			}

		}
	}
	else if(discharging)
	{
		if(!discharging_started)
		{
			discharging_started = 1;

			// turn off display
			GPIOA->BRR = ind_7_seg_1_Pin;
			GPIOA->BRR = ind_7_seg_2_Pin;
			GPIOA->BRR = ind_7_seg_4_Pin;
			GPIOA->BRR = ind_7_seg_8_Pin;


			// start discharging
			if(battery_type == 42)
			{
				HAL_GPIO_WritePin(GPIOA, discharge1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, discharge2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, fans_Pin, GPIO_PIN_SET);
			}
			else if(battery_type == 21)
			{
				HAL_GPIO_WritePin(GPIOA, discharge1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, discharge2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, fans_Pin, GPIO_PIN_SET);
			}

			discharging_start_moment = seconds_tick;
		}
		else // started yet
		{
		}
	}
	else // express/norm charging/discharging is turned off
	{
		if(expr_charging_started || norm_charging_started)
		{
			expr_charging_started = 0;
			norm_charging_started = 0;

			// turn off leds
			svd5_light = 0;
			svd4_light = 0;

			// turn off display
			GPIOA->BRR = ind_7_seg_1_Pin;
			GPIOA->BRR = ind_7_seg_2_Pin;
			GPIOA->BRR = ind_7_seg_4_Pin;
			GPIOA->BRR = ind_7_seg_8_Pin;


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

		}
		else if(discharging_started)
		{
			discharging_started = 0;

			// turn off led
			svd6_light = 0;

			HAL_GPIO_WritePin(GPIOA, discharge1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, discharge2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, fans_Pin, GPIO_PIN_RESET);
		}
		else // finished yet
		{

		}
	}
}
