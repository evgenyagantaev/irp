/*
 * battery_control_task.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery_control_task.h"
#include "battery.h"
#include "ext_power_obj.h"
#include "time_management_task.h"
#include "spi_pipe.h"
#include "gpio.h"

static uint32_t frozen_seconds;

void battery_control_task()
{

	// URGENT ACTIONS ****************************************************


	// check external power first
	int external_power_status = ext_pow_get_status();
	if(external_power_status != NORM) // something wrong
	{
		// check if we already turned everything off
		if(!emergency_turn_off_flag)
		{
			// turn off charge and discharge in all channels
			send_command(COMMAND_CHARGE_OFF, 0);
			send_command(COMMAND_CHARGE_OFF, 1);
			send_command(COMMAND_CHARGE_OFF, 2);
			send_command(COMMAND_CHARGE_OFF, 3);
			send_command(COMMAND_DISCHARGE_OFF, 0);
			send_command(COMMAND_DISCHARGE_OFF, 1);
			send_command(COMMAND_DISCHARGE_OFF, 2);
			send_command(COMMAND_DISCHARGE_OFF, 3);
			// change batteries status
			set_charge_flag(CHARGE_OFF, 0);
			set_charge_flag(CHARGE_OFF, 1);
			set_charge_flag(CHARGE_OFF, 2);
			set_charge_flag(CHARGE_OFF, 3);
			set_discharge_flag(DISCHARGE_OFF, 0);
			set_discharge_flag(DISCHARGE_OFF, 1);
			set_discharge_flag(DISCHARGE_OFF, 2);
			set_discharge_flag(DISCHARGE_OFF, 3);

			// turn off charge leds
			HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, chargeOK_led_green_out_Pin, GPIO_PIN_RESET);

			emergency_turn_off_flag = 1;
		}
	}
	else // external power supply ok
	{
		emergency_turn_off_flag = 0;

		// NORMAL PERIODICAL ACTIONS *************************************************

		uint32_t current_seconds = time_manager_get_seconds();

		if(current_seconds > frozen_seconds)
		{
			frozen_seconds = current_seconds;

		}
	}


}
