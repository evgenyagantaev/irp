/*
 * charge_level_detector_obj.c
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#include "charge_level_detector_obj.h"
#include "i2c_lowlevel.h"


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

	pred_pred_temperature = pred_temperature = charge_detector_temperature = temperature_mult_100;
}

void charge_detector_temperature_set(int temperature)
{
	pred_pred_temperature = pred_temperature;
	pred_temperature = charge_detector_temperature;
	charge_detector_temperature = temperature;
}















