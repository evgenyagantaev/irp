/*
 * message_interpreter_task.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */
#include "message_interpreter_task.h"
#include "message_queue.h"
#include "charge_level_detector_obj.h"

void message_interpreter_task()
{
	if(message_index > 0)
	{
		uint8_t message = message_pop();

		// parse command **********************************************

		if(message == COMMAND_GET_VOLTAGE) // get battery voltage
		{
			spi1_send_data(battery_voltage_get());
		}
		else if(message == COMMAND_GET_CURRENT) // get battery current
		{
			spi1_send_data(battery_current_get());
		}
		else if(message == COMMAND_GET_TEMPERATURE) // get battery temperature
		{
			spi1_send_data(battery_temperature_get());
		}
		else if(message == COMMAND_GET_CHARGE_LEVEL) // get battery temperature
		{
			spi1_send_data(charge_level_get());
		}
		else if(message == COMMAND_CHARGE_ON) //
		{
			switch_charge_on();
		}
		else if(message == COMMAND_CHARGE_OFF) //
		{
			switch_charge_off();
		}
		else if(message == COMMAND_DISCHARGE_ON) //
		{
			switch_discharge_on();
		}
		else if(message == COMMAND_DISCHARGE_OFF) //
		{
			switch_discharge_off();
		}
		else if(message == COMMAND_LOAD_ON) //
		{
			switch_load_on();
		}
		else if(message == COMMAND_LOAD_OFF) //
		{
			switch_load_off();
		}
		else
		{
			int i = 0;
		}

		//*************************************************************
	}
}
