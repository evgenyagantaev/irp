/*
 * message_interpreter_task.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */
#include "message_interpreter_task.h"
#include "message_queue.h"
#include "charge_level_detector_obj.h"
#include "switch_obj.h"
#include "spi1_transceiver.h"
#include "battery_obj.h"

void message_interpreter_task()
{
	if(get_message_index() > 0)
	{
		uint8_t message = message_pop();

		// parse command **********************************************

		if(message == COMMAND_CHARGE_ON) //
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
		else if(message == COMMAND_KTC_ON) //
		{
			switch_ktc_on();
		}
		else if(message == COMMAND_KTC_OFF) //
		{
			switch_ktc_off();
		}
		else if(message == COMMAND_CTC_DISCHARGE_ON) //
		{
			switch_ktc_discharge_on();
		}
		else
		{
			int i = 0;
		}

		//*************************************************************
	}
}
