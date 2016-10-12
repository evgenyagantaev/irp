/*
 * button_interpreter_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "button_interpreter_task.h"
#include "button.h"

#include "spi.h"
#include "spi_pipe.h"
#include "gpio.h"


void button_interpreter_task()
{
	if(!button_get_state()) // button is not pressed
	{
		// check if button was pressed and this press is not served yet
		if(button_get_short_status() || button_get_long_status())
		{
			// clear flags
			button_set_short_status(0);
			button_set_long_status(0);

			// check state and commit actions
			if(interpreter_state == 0)
			{
				// charge on
				spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL0);
				spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL1);
				spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL2);
				spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL3);
			}
			else if(interpreter_state == 1)
			{
				// charge off
				spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL0);
				spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL1);
				spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL2);
				spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL3);
			}
			else if(interpreter_state == 2)
			{
				// discharge on
				spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL0);
				spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL1);
				spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL2);
				spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL3);
			}
			else if(interpreter_state == 3)
			{
				// discharge off
				spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL0);
				spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL1);
				spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL2);
				spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL3);
			}
			interpreter_state++;
			if(interpreter_state >= 4)
				interpreter_state = 0;
		}
	}
}





















