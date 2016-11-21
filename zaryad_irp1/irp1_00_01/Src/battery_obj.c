/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery_obj.h"
#include "time_management_task.h"

#include "i2c_lowlevel.h"


static uint32_t temperature_period_start = 0;
static int32_t battery_live_voltage = 0;


int32_t battery_voltage_get()
{
	return battery_voltage;
}
int32_t battery_live_voltage_get()
{
	uint16_t vbatt;

	uint8_t data_l, data_h;

	// read vbatt
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x09); //Vcell register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	vbatt = (((uint16_t)data_h)<<8) + (uint16_t)data_l;
	vbatt >>= 3;
	double Vcell = ((vbatt * 0.625) * 8.0);
	int32_t Vcell_mv = (int32_t)Vcell;

	battery_live_voltage = Vcell_mv;

	return Vcell_mv;
}
void battery_live_voltage_set(int32_t voltage)
{
	battery_live_voltage = voltage;
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
	// shift temperature buffer
	uint32_t current_seconds = time_manager_get_seconds();

	if((current_seconds - temperature_period_start) >= BATTERY_TEMPERATURE_CONTROL_PERIOD)
	{
		temperature_period_start = current_seconds;

		temperature_buffer[0] = temperature_buffer[1];
		temperature_buffer[1] = temperature_buffer[2];
		temperature_buffer[2] = temperature;
	}

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

int battery_state_get()
{
	return battery_state;
}
int battery_state_set(int state)
{
	battery_state = state;
	return battery_state;
}

uint32_t temperature_period_start_get()
{
	return temperature_period_start;
}
uint32_t temperature_period_start_set(uint32_t period_start)
{
	temperature_period_start = period_start;
	return temperature_period_start;
}

int *battery_temperature_buffer_get()
{
	return temperature_buffer;
}
