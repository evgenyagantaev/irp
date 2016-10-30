/*
 * coulombcounter_obj.c
 *
 *  Created on: Oct 30, 2016
 *      Author: root
 */

#include "coulombcounter_obj.h"
#include "battery_obj.h"


static double coulombmeter = 5000.0;
static double discharge_capacity = 12000.0;


void fit_coulombmeter()
{
	int battery_state = battery_state_get();
	if(!(battery_state==CHARGED_STATE || battery_state==CTC_CHARGED_STATE || battery_state==CTC_RECHARGED_STATE))
		coulombmeter += (double)(battery_current_get()) * COULOMB_RATIO;
}

int32_t coulombmeter_get()
{
	return (int32_t)coulombmeter;
}

void coulombmeter_set(double value)
{
	coulombmeter = value;
}


double discharge_capacity_get()
{
	return discharge_capacity;
}
void discharge_capacity_set(double value)
{
	discharge_capacity = value;
}
