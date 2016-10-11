/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery_obj.h"

int32_t battery_voltage_get()
{
	return battery_voltage;
}
int32_t battery_temperature_get()
{
	return battery_temperature;
}
int32_t battery_current_get()
{
	return battery_current;
}
int32_t battery_remaining_capacity_get()
{
	return battery_remaining_capacity;
}
int32_t battery_voltage_set(int32_t voltage)
{
	battery_voltage = voltage;

	return battery_voltage;
}
int32_t battery_temperature_set(int32_t temperature)
{
	battery_temperature = temperature;

	return battery_temperature;
}
int32_t battery_current_set(int32_t current)
{
	battery_current = current;

	return battery_current;
}
int32_t battery_remaining_capacity_set(int32_t remaining_capacity)
{
	battery_remaining_capacity = remaining_capacity;

	return battery_remaining_capacity;
}


int get_charge_flag()
{
	return charge_flag;
}
int get_discharge_flag()
{
	return discharge_flag;
}
int get_load_flag()
{
	return load_flag;
}
void set_charge_flag(int flag)
{
	charge_flag = flag;
}
void set_discharge_flag(int flag)
{
	discharge_flag = flag;
}
void set_load_flag(int flag)
{
	load_flag = flag;
}

