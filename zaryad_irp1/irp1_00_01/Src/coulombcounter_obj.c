/*
 * coulombcounter_obj.c
 *
 *  Created on: Oct 30, 2016
 *      Author: root
 */

#include "coulombcounter_obj.h"



static double coulombmeter = 5000.0;


void fit_coulombmeter()
{
	coulombmeter += (double)(battery_current_get()) * COULOMB_RATIO;
}

int32_t coulombmeter_get()
{
	return (int32_t)coulombmeter;
}
