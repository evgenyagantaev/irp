/*
 * battery_measurement_task.c
 *
 *  Created on: Sep 11, 2016
 *      Author: root
 */

#include "battery_measurement_task.h"
#include "i2c_lowlevel.h"
#include "usart.h"


void battery_measurement_task()
{
	char message[64];

	uint16_t version;
	uint16_t configuration;
	uint16_t vbatt;
	int16_t current;
	int16_t temperature;
	int16_t rem_cap;

	uint8_t data_l, data_h;

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
	int32_t Vcell_mv = (uint32_t)Vcell;
	battery_voltage_set(Vcell_mv);
	sprintf((char *)message, "Vcell = %d mV\r\n", Vcell_mv);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	// read current
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x0a); //current register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	current = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Current = 1.5625e-6/2.5e-3 * current;
	int32_t current_ma = (uint32_t)(Current * 1000);
	battery_current_set(current_ma);
	sprintf((char *)message, "Current = %d mA\r\n", current_ma);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	// read temperature
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x08); //temperature register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	temperature = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Temperature = temperature * 0.0039;
	int32_t temperature_mult_100 = (int32_t)(Temperature * 100);
	battery_temperature_set(temperature_mult_100);
	sprintf((char *)message, "temperature x 100 C = %d\r\n", temperature_mult_100);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	// read capacity
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x0f); //remaining capacity register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	rem_cap = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Rem_cap = rem_cap * 0.5;
	int32_t rem_cap_mah = (int32_t)Rem_cap;
	sprintf((char *)message, "remaining capacity = %d mAh\r\n", rem_cap_mah);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	sprintf((char *)message, "******************************************\r\n");
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
}
