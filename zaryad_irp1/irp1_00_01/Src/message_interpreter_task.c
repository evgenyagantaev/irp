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

#include "usart.h"


void message_interpreter_task()
{
	//char message[64];
	//sprintf((char *)message, "message_interpreter_task\r\n");
	//AL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

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
			char message[64];
			sprintf((char *)message, "command load off\r\n");
			HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

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
			switch_charge_off();
			switch_ktc_discharge_on();
		}
		else if(message == COMMAND_CTC_RECHARGE_ON) //
		{
			switch_ktc_recharge_on();
		}
		else
		{
			int i = 0;
		}

		//************************************************************* COMMAND_CLEAN_EEPROM
	}
}
