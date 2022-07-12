/*
 * charge_check_task.c
 *
 *  Created on: Jul 5, 2022
 *      Author: agant
 */

#include <stdint.h>
#include "gpio.h"

extern int express_charging;
extern uint32_t seconds_tick;
extern uint32_t battery_type;

volatile int express_charging_start_moment = 0;

void charge_check_task()
{
	static int expr_charging_started = 0;

	static express_charging_start_moment = 0;

	if(express_charging)
	{
		if(!expr_charging_started)
		{
			expr_charging_started = 1;

			// start express charging
			if(battery_type == 42)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_SET);
			}
			else if(battery_type == 21)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin | express_charge2_Pin, GPIO_PIN_SET);
			}

			express_charging_start_moment = seconds_tick;
		}
		else // started yet
		{

		}
	}
	else // express charging is turned off
	{
		if(expr_charging_started)
		{
			expr_charging_started = 0;

			// start express charging
			if(battery_type == 21)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_RESET);
			}
			else if(battery_type == 42)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin | express_charge2_Pin, GPIO_PIN_RESET);
			}

		}
		else // finished yet
		{

		}
	}
}
