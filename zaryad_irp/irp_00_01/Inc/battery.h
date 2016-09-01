/*
 * battery.h
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_

#include "stdint.h"

static int32_t battery_voltage;     // milivolts
static int32_t battery_temperature; // celsius * 100
static int32_t battery_current;     // miliamperes



void battery_main_charge_start();
void battery_main_charge_stop();
void battery_drop_charge_start();
void battery_drop_charge_stop();
void battery_charge_stop();
void battery_discharge_start();
void battery_discharge_stop();
void battery_load_on();
void battery_load_off();

void battery_voltage_get();
void battery_temperature_get();
void battery_current_get();



#endif /* INC_BATTERY_H_ */
