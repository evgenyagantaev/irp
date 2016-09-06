/*
 * button_interpreter_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "button_interpreter_task.h"
#include "button.h"

#include "spi.h"
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
				send_command(COMMAND_CHARGE_ON);
			}
			else if(interpreter_state == 1)
			{
				// charge on
				send_command(COMMAND_CHARGE_OFF);
			}
			else if(interpreter_state == 2)
			{
				// charge on
				send_command(COMMAND_DISCHARGE_ON);
			}
			else if(interpreter_state == 3)
			{
				// charge on
				send_command(COMMAND_DISCHARGE_OFF);
			}
			interpreter_state++;
			if(interpreter_state >= 4)
				interpreter_state = 0;
		}
	}
}

void send_command(uint16_t command)
{
	uint16_t in_data;
	// chipsel low
	GPIOB->BRR = (chipsel1_out_Pin | chipsel2_out_Pin | chipsel3_out_Pin | chipsel4_out_Pin);
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = command;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR;
	// chipsel high
	GPIOB->BSRR = (chipsel1_out_Pin | chipsel2_out_Pin | chipsel3_out_Pin | chipsel4_out_Pin);
	spi_short_delay();
}



















