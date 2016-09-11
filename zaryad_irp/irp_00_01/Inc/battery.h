/*
 * battery.h
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_

#include "stdint.h"

static int32_t battery_voltage[] = {0,0,0,0};     // milivolts
static int32_t battery_temperature[] = {0,0,0,0}; // celsius * 100
static int32_t battery_current[] = {0,0,0,0};     // miliamperes

#define CHARGE_ON 1
#define CHARGE_OFF 0
#define DISCHARGE_ON 1
#define DISCHARGE_OFF 0


static int charge_flag[] = {0,0,0,0};
static int discharge_flag[] = {0,0,0,0};
int get_charge_flag(int channel);
int get_discharge_flag(int channel);
void set_charge_flag(int flag, int channel);
void set_discharge_flag(int flag, int channel);


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
