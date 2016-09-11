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
				send_command(COMMAND_CHARGE_ON, 0);
			}
			else if(interpreter_state == 1)
			{
				// charge on
				send_command(COMMAND_CHARGE_OFF, 0);
			}
			else if(interpreter_state == 2)
			{
				// charge on
				send_command(COMMAND_DISCHARGE_ON, 0);
			}
			else if(interpreter_state == 3)
			{
				// charge on
				send_command(COMMAND_DISCHARGE_OFF, 0);
			}
			interpreter_state++;
			if(interpreter_state >= 4)
				interpreter_state = 0;
		}
	}
}





















