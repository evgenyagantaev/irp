/*
 * charge_level_detector_obj.c
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#include "charge_level_detector_obj.h"
#include "i2c_lowlevel.h"
#include "battery_obj.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "time_management_task.h"


void charge_level_detector_init()
{
	uint8_t data_l, data_h;

	// measure temperature
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x08); //temperature register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	int16_t temperature = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Temperature = temperature * 0.0039;
	int32_t temperature_mult_100 = (int32_t)(Temperature * 100);
	//battery_temperature_set(temperature_mult_100);
	//sprintf((char *)message, "temperature x 100 C = %d\r\n", temperature_mult_100);
	//HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	int *temperature_buffer = battery_temperature_buffer_get();

	temperature_buffer[0] = temperature_buffer[1] = temperature_buffer[2] = temperature_mult_100;
	temperature_period_start_set(time_manager_get_seconds());
}


void charge_level_detect()
{
	uint32_t voltage = battery_voltage_get();
	if((voltage <= 32000) && (voltage > VOLTAGE_LOW_THRESHOLD))
	{
		if(voltage < VOLTAGE_HIGH_THRESHOLD)
			charge_level = (uint32_t)((double)(voltage - VOLTAGE_LOW_THRESHOLD)/(double)VOLTAGE_SPAN * 100.0);
		else
			charge_level = 100;
	}
	else
	{
		charge_level = 0;
	}

	char message[64];
	sprintf((char *)message, "CHARGE LEVEL = %d   VOLTAGE = %d\r\n", charge_level, voltage);
	//HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

}

uint32_t charge_level_get()
{
	//debug
	//charge_level = 97;

	return charge_level;
}
void charge_level_set(uint32_t level)
{
	charge_level = level;
}











