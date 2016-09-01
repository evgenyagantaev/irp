/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery.h"

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
