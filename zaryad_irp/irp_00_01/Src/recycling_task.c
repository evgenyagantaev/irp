#include "main.h"

#include <stdio.h>
#include <string.h>

#include "usart.h"

// volatile; may be changed in usart interrupt procedure
int recycling_mode = 0;
int recycling_length = 0;
int recycling_hint = 0;

extern uint battery_type;

extern int norm_charging;
extern int discharging;

extern uint32_t seconds_tick;

extern int no_bad_cell_voltage;
extern int battery_voltage;

int recycling_charging = 0;
int recycling_discharging = 0;
int stop_button_imitation = 0;


void recycling_task()
{
	static char message[64];

	static int state = 0;
	static int current_cycle = 0;

	static uint32_t recycling_discharging_start_moment;
	static uint32_t recycling_discharge_duration;
	// DEBUG
	static uint32_t recycling_charging_debug_start_moment;

	static uint32_t one_minute_pause_start_moment;

	if(state == 0)   // idle
	{
		if(recycling_mode > 0)
		{
			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			int percentage;
			if(recycling_mode == 1)
				percentage = 50;
			else
				percentage = 95;
			sprintf((char *)message, "Start recycling process: %d cycles, mode %d%%\r\n", recycling_length, percentage);
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "Battery type: %d\r\n", battery_type);
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);


			current_cycle = recycling_hint;

			state = 1; // just starting recycling
		}
	}
	else if(state == 1)   // starting
	{
		current_cycle++;

		if(current_cycle <= recycling_length)
		{
			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "Start cycle: %d \r\n", current_cycle);
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);


			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "Discharging: ... \r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			state = 2; // discharging

			recycling_discharging_start_moment = seconds_tick;
			if(recycling_mode == 1)
			{
				//recycling_discharge_duration = 9000;
				recycling_discharge_duration = 60;
			}
			else if(recycling_mode == 2)
			{
				//recycling_discharge_duration = 17100;
				recycling_discharge_duration = 120;
			}
			else if(recycling_mode == 0)
			{
				state = 0; // return to idle
			}


			// here turn on discharging
			recycling_discharging = 1;


		}
		else  // all cycles are over
		{
			// here print the message that recycling is complete
			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "Recycling complete.\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);


			recycling_mode = 0;
			recycling_length = 0;
			recycling_hint = 0;

			state = 0; // idle
		}
	}
	else if(state == 2)   // start next cycle discharging
	{

		state = 3;

	}
	else if(state == 3)   // discharging
	{
		// here check the conditions of the discharge
		if(   (seconds_tick - recycling_discharging_start_moment > recycling_discharge_duration) ||
			  (no_bad_cell_voltage && (battery_voltage < 24500))   )
		{
			// here turn off discharge
			stop_button_imitation = 1;

			one_minute_pause_start_moment = seconds_tick;

			sprintf((char *)message, "Pause 1 min\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			state = 4; // 1 minute pause
		}
	}
	else if(state == 4)   // 1 minute pause
	{
		if(seconds_tick - one_minute_pause_start_moment > 60)
		{
			sprintf((char *)message, "\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "Charging: ... \r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			// here turn on charging
			//DEBUG
			recycling_charging_debug_start_moment = seconds_tick;
			recycling_charging = 1;

			state = 5; // charging
		}

	}
	else if(state == 5)   // charging
	{
		// here check the conditions of charging completion
		//DEBUG >>>>>>>>>>
		//if(seconds_tick - recycling_charging_debug_start_moment > 60)
		if((norm_charging == 0) && (recycling_charging == 0))
		{
			// charging is turned off automatically
			// but imitate stop button, just in case
			stop_button_imitation = 1;


			// if satisfy, go to 1 minute pause
			one_minute_pause_start_moment = seconds_tick;

			sprintf((char *)message, "Pause 1 min\r\n");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			state = 6; // 1 minute pause
		}
	}
	else if(state == 6)   // 1 minute pause
	{
		if(seconds_tick - one_minute_pause_start_moment > 60)
		{
			state = 1; // go to the next cycle
		}

	}


}
