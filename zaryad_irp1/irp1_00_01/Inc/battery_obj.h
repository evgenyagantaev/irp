/*
 * battery.h
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#ifndef INC_BATTERY_OBJ_H_
#define INC_BATTERY_OBJ_H_

#include "stdint.h"

static int32_t battery_voltage = 0;     			// milivolts
static int32_t battery_temperature = 0; 			// celsius * 100
static int32_t battery_current = 0;     			// miliamperes
static int32_t battery_remaining_capacity = 0;     	// miliamperes hours
static int32_t battery_charge_level = 0;  	    	// percents

static int temperature_buffer[3];
#define BATTERY_TEMPERATURE_CONTROL_PERIOD 60

uint32_t temperature_period_start_get();
uint32_t temperature_period_start_set(uint32_t period_start);
int *battery_temperature_buffer_get();

#define CHARGE_ON 1
#define CHARGE_OFF 0
#define DISCHARGE_ON 1
#define DISCHARGE_OFF 0


static int charge_flag = 0;
static int discharge_flag = 0;
static int load_flag = 0;

#define IDLE_STATE 0
#define CHARGING_STATE 1
#define CHARGED_STATE 2
#define DISCHARGING_STATE 3
#define LOAD_STATE 4
#define CTC_CHARGING_STATE 5
#define CTC_CHARGED_STATE 6
#define CTC_DISCHARGING_STATE 7
#define CTC_DISCHARGED_STATE 8
#define CTC_RECHARGING_STATE 9
#define CTC_RECHARGED_STATE 10
#define CTC_COMPLETE_STATE 11

static int battery_state = IDLE_STATE;

int battery_state_get();
int battery_state_set(int state);


int get_charge_flag();
int get_discharge_flag();
int get_load_flag();
void set_charge_flag(int flag);
void set_discharge_flag(int flag);
void set_load_flag(int flag);



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
int32_t battery_remaining_capacity_get();
int32_t battery_voltage_set(int32_t voltage);
int32_t battery_temperature_set(int32_t temperature);
int32_t battery_current_set(int32_t current);
int32_t battery_remaining_capacity_set();



#endif /* INC_BATTERY_OBJ_H_ */
