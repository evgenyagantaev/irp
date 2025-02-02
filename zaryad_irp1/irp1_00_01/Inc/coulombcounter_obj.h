/*
 * coulombcounter_obj.h
 *
 *  Created on: Oct 30, 2016
 *      Author: root
 */

#ifndef INC_COULOMBCOUNTER_OBJ_H_
#define INC_COULOMBCOUNTER_OBJ_H_

#include "stdint.h"

static const double coulomb_ratio = 1.0/3600.0;

#define COULOMB_RATIO coulomb_ratio

#define REMCAP_SAVING_PERIOD 600 // seconds

void fit_coulombmeter();
int32_t coulombmeter_get();
void coulombmeter_set(double value);
double discharge_capacity_get();
void discharge_capacity_set();

void set_discharge_cap_meter(double value);
double get_discharge_cap_meter();

#endif /* INC_COULOMBCOUNTER_OBJ_H_ */
