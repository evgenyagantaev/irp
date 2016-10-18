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
#include "switch_obj.h"


static int temperature_buffer[3];
static uint32_t charger_frozen_seconds = 0;

static int drop_charge_current_on = 0;
static uint32_t drop_charge_period_start = 0;

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

		if((battery_state == CHARGED_STATE) && get_charge_flag())
		{
			// drop charge regime
			if(drop_charge_current_on) // current on
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_PERIOD) // it's time to switch current off
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 0;
					// switch off
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				}
			}
			else // no current, idle period
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_iDLE_PERIOD) // it's time to switch current on
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 1;
					// switch on
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
				}
			}

		}
		//*********************************************************************************************

		if(battery_state == CTC_CHARGING_STATE)
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
				battery_state_set(CTC_CHARGED_STATE);
			}
		}

		if((battery_state == CTC_CHARGED_STATE) && get_charge_flag())
		{
			// drop charge regime
			if(drop_charge_current_on) // current on
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_PERIOD) // it's time to switch current off
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 0;
					// switch off
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				}
			}
			else // no current, idle period
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_iDLE_PERIOD) // it's time to switch current on
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 1;
					// switch on
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
				}
			}

		}


		//*********************************************************************************************

		if(battery_state == CTC_RECHARGING_STATE)
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
				battery_state_set(CTC_RECHARGED_STATE);
			}
		}

		if((battery_state == CTC_RECHARGED_STATE) && get_charge_flag())
		{
			// drop charge regime
			if(drop_charge_current_on) // current on
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_PERIOD) // it's time to switch current off
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 0;
					// switch off
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				}
			}
			else // no current, idle period
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_iDLE_PERIOD) // it's time to switch current on
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 1;
					// switch on
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
				}
			}

		}


		//*********************************************************************************************
		if(battery_state == DISCHARGING_STATE)
		{
			// check discharge cancel voltage criterion
			if(battery_voltage_get() <= DISCHARGE_CRITICAL_VOLTAGE)
			{
				// turn off discharge
				switch_discharge_off();
			}
		}

		if(battery_state == CTC_DISCHARGING_STATE)
		{
			// check discharge cancel voltage criterion
			if(battery_voltage_get() <= DISCHARGE_CRITICAL_VOLTAGE)
			{
				// turn off discharge
				switch_discharge_off();
				battery_state_set(CTC_DISCHARGED_STATE);
			}
		}









		if(battery_state == LOAD_STATE)
		{
			// check discharge cancel voltage criterion
			if(battery_voltage_get() <= DISCHARGE_CRITICAL_VOLTAGE)
			{
				// turn off load
				switch_load_off();
			}
		}

		if(battery_state == CTC_CHARGED_STATE)
		{

		}
	}
}

