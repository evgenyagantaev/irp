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

int32_t battery_voltage_get();
int32_t battery_temperature_get();
int32_t battery_current_get();
int32_t battery_voltage_set(int32_t voltage);
int32_t battery_temperature_set(int32_t temperature);
int32_t battery_current_set(int32_t current);



#endif /* INC_BATTERY_H_ */
