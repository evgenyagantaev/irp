/*
 * coulombcounter_obj.c
 *
 *  Created on: Oct 30, 2016
 *      Author: root
 */

#include "coulombcounter_obj.h"
#include "battery_obj.h"
#include "eeprom_storage_obj.h"
#include "time_management_task.h"


static double coulombmeter = 5000.0;
static double discharge_capacity = 12000.0;
static double discharge_cap_meter = 0;

static coulombmeter_frozen_seconds = 0;

void set_discharge_cap_meter(double value)
{
	discharge_cap_meter = value;
}

double get_discharge_cap_meter()
{
	return discharge_cap_meter;
}

void fit_coulombmeter()
{
	int battery_state = battery_state_get();
	if(!(battery_state==CHARGED_STATE || battery_state==CTC_CHARGED_STATE || battery_state==CTC_RECHARGED_STATE))
		coulombmeter += (double)(battery_current_get()) * COULOMB_RATIO;
	// count discharge_capacity
	if(battery_state == CTC_DISCHARGING_STATE)
		discharge_cap_meter += (double)(-battery_current_get()) * COULOMB_RATIO;
	// save current remaining capacity in eeprom
	uint32_t current_seconds = time_manager_get_seconds();
	if((current_seconds - coulombmeter_frozen_seconds) >= REMCAP_SAVING_PERIOD)
	{
		coulombmeter_frozen_seconds = current_seconds;
		eeprom_write_remaining_capacity((int32_t)coulombmeter);
	}
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
