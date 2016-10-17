/*
 * ctc_controller_obj.c
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#include "ctc_controller_obj.h"
#include "stdint.h"
#include "time_management_task.h"


static int ctc_stage = CTC_INACTIVE;

static uint32_t ctc_frozen_seconds = 0;




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
	}



}
