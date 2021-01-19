/*
 * battery_measurement_task.c
 *
 *  Created on: Sep 11, 2016
 *      Author: root
 */

#include "battery_measurement_task.h"
#include "i2c_lowlevel.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "battery_obj.h"
#include "charge_level_detector_obj.h"

#include "coulombcounter_obj.h"
#include "switch_obj.h"

static int averaging_counter = 0;
static int32_t battery_voltage_integral = 0;
static int32_t current_integral = 0;
static int32_t temperature_integral = 0;


void battery_measurement_task()
{
	char message[64];

	//uint16_t version;
	//uint16_t configuration;
	uint16_t vbatt;
	int16_t current;
	int16_t temperature;
	//int16_t rem_cap;

	uint8_t data_l, data_h;

	averaging_counter++;

	// debug
	/*
	// read version (0x00ac)
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x21); //version register 0x21 contains 0xac
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	version = (((uint16_t)data_h)<<8) + (uint16_t)data_l;
	sprintf((char *)message, "version = 0x%x \r\n", version);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	// debug
	// read configuration
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x1d); //configuration register 0x1d
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	configuration = (((uint16_t)data_h)<<8) + (uint16_t)data_l;
	sprintf((char *)message, "configuration = 0x%x \r\n", configuration);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
	//*/

	// read vbatt
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	//i2c_send_byte(0x09); //Vcell register
	i2c_send_byte(0x19); //Vcell register
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
	battery_voltage_integral += Vcell_mv;

	if (averaging_counter >= AVERAGING_PERIOD)
	{
		Vcell_mv = battery_voltage_integral/AVERAGING_PERIOD;
		battery_voltage_set(Vcell_mv);
		battery_voltage_integral = 0;
		sprintf((char *)message, "%13ld", Vcell_mv);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

		// check if voltage below the low level
		if(Vcell_mv < 20000)
		{
			// turn off load
			sprintf((char *)message, "Vyrubaem nagruzku!!!");
			HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			switch_load_off();
			// reset remaining capacity
			coulombmeter_set(0.0);
		}

		if(Vcell_mv < 20000)
		//if(Vcell_mv < 21000)
		//if(Vcell_mv < 21500)
		//if(Vcell_mv < 22000)
		//if(Vcell_mv < 22500)
		{
			switch_onbat2_off();
		}
		//else if(Vcell_mv > 24000)
		//else if(Vcell_mv > 24000)
		//else if(Vcell_mv > 24500)
		else if(Vcell_mv > 25000)
		//else if(Vcell_mv > 25500)
		{
			switch_onbat2_on();
		}

	}

	// read current
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	//i2c_send_byte(0x0a); //current register
	i2c_send_byte(0x0b); //current register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	current = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Current = 1.5625e-6/2.5e-3 * current;
	int32_t current_ma = (int32_t)(Current * 1000);
	current_integral += current_ma;

	if (averaging_counter >= AVERAGING_PERIOD)
	{
		current_ma = current_integral/AVERAGING_PERIOD;
		battery_current_set(current_ma);
		current_integral = 0;
		sprintf((char *)message, "%13ld", current_ma);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	}


	// read temperature
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	//i2c_send_byte(0x08); //temperature register
	i2c_send_byte(0x16); //temperature register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	temperature = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Temperature = temperature * 0.0039;
	int32_t temperature_mult_100 = (int32_t)(Temperature * 100);
	temperature_integral += temperature_mult_100;

	if (averaging_counter >= AVERAGING_PERIOD)
	{
		temperature_mult_100 = temperature_integral/AVERAGING_PERIOD;
		battery_temperature_set(temperature_mult_100);
		temperature_integral = 0;
		sprintf((char *)message, "%13ld", temperature_mult_100);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	}

	/*
	// read capacity
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x0f); //remaining capacity register
	//i2c_send_byte(0x18); //full capacity register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	rem_cap = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Rem_cap = rem_cap * 3.0;
	int32_t rem_cap_mah = (int32_t)Rem_cap;

	if (averaging_counter >= AVERAGING_PERIOD)
	{
		battery_remaining_capacity_set(rem_cap_mah);
		sprintf((char *)message, "%13d\r\n", rem_cap_mah);
		HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
	}
	//*/


	int32_t rem_cap_mah = coulombmeter_get();

	if (averaging_counter >= AVERAGING_PERIOD)
	{
		battery_remaining_capacity_set(rem_cap_mah);
		sprintf((char *)message, "%13ld\r\n", rem_cap_mah);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	}


	if (averaging_counter >= AVERAGING_PERIOD)
		averaging_counter = 0;

	charge_level_detect();
}
