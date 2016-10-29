/*
 * ctc_controller_obj.c
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#include "ctc_controller_obj.h"
#include "stdint.h"
#include "time_management_task.h"
#include "time_management_task.h"
#include "spi_pipe.h"
#include "gpio.h"


static int ctc_stage = CTC_INACTIVE;

static uint32_t ctc_frozen_seconds = 0;

uint32_t states[4];


// regime ctc ustanavlivaetsya "snaruzhi" interpretatorom nazhatiya knopki

void ctc_set_stage(int stage)
{
	ctc_stage = stage;
}


void ctc_controller_task()
{
	uint32_t current_seconds = time_manager_get_seconds();

	if(current_seconds > (ctc_frozen_seconds + CTC_CONTROL_PERIOD))
	{
		ctc_frozen_seconds = current_seconds;

		if(ctc_stage != CTC_INACTIVE)
		{
			uint32_t states[4];
			channel_states_get(states);

			// check if ctc charged state is realized
			int i;
			int result = 0;
			for(i=0; i<4; i++)
			{
				if(states[i] == CTC_CHARGED_STATE)
					result++;
			}
			if(result == 4)
			{
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 0);
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 1);
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 2);
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 3);
			}

			// check if ctc discharged state is realized
			result = 0;
			for(i=0; i<4; i++)
			{
				if(states[i] == CTC_DISCHARGED_STATE)
					result++;
			}
			if(result == 4)
			{
				spi_pipe_send_command(COMMAND_CTC_RECHARGE_ON, 0);
				spi_pipe_send_command(COMMAND_CTC_RECHARGE_ON, 1);
				spi_pipe_send_command(COMMAND_CTC_RECHARGE_ON, 2);
				spi_pipe_send_command(COMMAND_CTC_RECHARGE_ON, 3);

				// turn on "charging" red led
				GPIOA->BSRR = charge_led_red_out_Pin;
			}

			// check if ctc recharged (complete) state is realized
			result = 0;
			for(i=0; i<4; i++)
			{
				if(states[i] == CTC_RECHARGED_STATE)
					result++;
			}
			if(result == 4)
			{
				// ctc complete *************************
				// turn on green led
				// turn off ktc red led
				HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_RESET);
				// turn on ktc green led
				HAL_GPIO_WritePin(GPIOA, ctc_led_green_out_Pin, GPIO_PIN_SET);
				// turn off "charging" red led
				GPIOA->BRR = charge_led_red_out_Pin;
				// turn on charge ok green led
				HAL_GPIO_WritePin(GPIOA, chargeOK_led_green_out_Pin, GPIO_PIN_SET);
				ctc_stage = CTC_INACTIVE;
			}
		}

	}



}
