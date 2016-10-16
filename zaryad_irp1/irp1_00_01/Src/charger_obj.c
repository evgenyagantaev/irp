/*
 * charger_obj.c
 *
 *  Created on: Oct 16, 2016
 *      Author: root
 */

#include "charger_obj.h"
#include "time_management_task.h"
#include "battery_obj.h"
#include "gpio.h"


static int temperature_buffer[3];
static uint32_t charger_frozen_seconds = 0;

void charger_control_task()
{
	uint32_t current_seconds = time_manager_get_seconds();

	if(current_seconds - charger_frozen_seconds >= CHARGE_CONTROL_PERIOD)
	{
		charger_frozen_seconds = current_seconds;

		int battery_state = battery_state_get();

		if(battery_state == CHARGING_STATE)
		{
			// check temperature criterion
			int *temperature_buffer = battery_temperature_buffer_get();

			if(
				(temperature_buffer[2] >= CHARGE_CRITICAL_TEMPERATURE) ||
				(
					(temperature_buffer[1] > temperature_buffer[0]) &&
					(temperature_buffer[2] > temperature_buffer[1]) &&
					((temperature_buffer[2] - temperature_buffer[0]) >= CHARGE_CRITICAL_TEMPERATURE_SPEED)
				)
			  )
			{
				// stop charge, switch to drop charging
				HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				battery_state_set(CHARGED_STATE);
			}
		}
	}
}

