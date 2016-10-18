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
			// check if ctc charged state is realized
			channel_states_get(states);

			int i;
			int result = 0;
			for(i=0; i<4; i++)
			{
				if(states[i] == CTC_CHARGED)
					result++;
			}
			if(result == 4)
			{
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 0);
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 1);
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 2);
				spi_pipe_send_command(COMMAND_CTC_DISCHARGE_ON, 3);
			}
		}

	}



}
