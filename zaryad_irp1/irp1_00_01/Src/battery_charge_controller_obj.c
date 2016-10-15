/*
 * buttery_charge_controller.c
 *
 *  Created on: Oct 15, 2016
 *      Author: root
 */

#include <battery_charge_controller_obj.h>
#include "battery_obj.h"


static int pred_pred_temperature;
static int pred_temperature;
static int charge_detector_temperature;


void battery_charge_control_task()
{
	if(get_charge_flag())
	{
		// check full charge


	}
}




