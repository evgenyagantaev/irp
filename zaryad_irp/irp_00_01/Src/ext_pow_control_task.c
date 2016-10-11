/*
 * ext_pow_control_task.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "ext_pow_control_task.h"
#include "ext_power_obj.h"
#include "gpio.h"
#include "spi_pipe.h"

//debug
#include "string.h"
#include "usart.h"

void ext_pow_control_task()
{
	uint32_t current_tick = HAL_GetTick();
	if(current_tick >= (ext_pow_frozen_systick + 10))
	{
		ext_pow_frozen_systick = current_tick;

		extpow_measure_voltage();
		uint32_t ext_pow_voltage = ext_pow_get_voltage();

		//debug
		char message[64];
		sprintf(message, "%ldI%ld\r\n", ext_pow_voltage, ext_pow_voltage);
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);

		if(ext_pow_voltage > HIGH_THRESHOLD)
		{
			if(ext_pow_voltage_state != 0)
			{
				ext_pow_voltage_state = 0;

				ext_pow_set_status(2); // more
				// power red led on
				HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
				// turn off charge
				send_command(COMMAND_CHARGE_OFF, CHANNEL0);
				send_command(COMMAND_CHARGE_OFF, CHANNEL1);
				send_command(COMMAND_CHARGE_OFF, CHANNEL2);
				send_command(COMMAND_CHARGE_OFF, CHANNEL3);
				// turn off load
				send_command(COMMAND_LOAD_OFF, CHANNEL0);
				send_command(COMMAND_LOAD_OFF, CHANNEL1);
				send_command(COMMAND_LOAD_OFF, CHANNEL2);
				send_command(COMMAND_LOAD_OFF, CHANNEL3);
				// turn off red charge led
				HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_RESET);
			}

		}
		else if((ext_pow_voltage < LOW_CHARGE_THRESHOLD) && (ext_pow_voltage >= LOW_LOAD_THRESHOLD))
		{
			if(ext_pow_voltage_state != 1)
			{
				ext_pow_voltage_state = 1;

				ext_pow_set_status(1); // less
				// power red led on
				HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
				// turn off load
				send_command(COMMAND_LOAD_OFF, CHANNEL0);
				send_command(COMMAND_LOAD_OFF, CHANNEL1);
				send_command(COMMAND_LOAD_OFF, CHANNEL2);
				send_command(COMMAND_LOAD_OFF, CHANNEL3);
				// turn off charge
				send_command(COMMAND_CHARGE_OFF, CHANNEL0);
				send_command(COMMAND_CHARGE_OFF, CHANNEL1);
				send_command(COMMAND_CHARGE_OFF, CHANNEL2);
				send_command(COMMAND_CHARGE_OFF, CHANNEL3);
				// turn off red charge led
				HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_RESET);

			}
		}
		else if(ext_pow_voltage < LOW_LOAD_THRESHOLD)
		{
			if(ext_pow_voltage_state != 2)
			{
				ext_pow_voltage_state = 2;

				ext_pow_set_status(1); // less
				// power red led on
				HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
				// turn off charge
				send_command(COMMAND_CHARGE_OFF, CHANNEL0);
				send_command(COMMAND_CHARGE_OFF, CHANNEL1);
				send_command(COMMAND_CHARGE_OFF, CHANNEL2);
				send_command(COMMAND_CHARGE_OFF, CHANNEL3);
				// turn off red charge led
				HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_RESET);
				HAL_Delay(2000);
				// turn on load
				send_command(COMMAND_LOAD_ON, CHANNEL0);
				send_command(COMMAND_LOAD_ON, CHANNEL1);
				send_command(COMMAND_LOAD_ON, CHANNEL2);
				send_command(COMMAND_LOAD_ON, CHANNEL3);
			}
		}
		else // everything ok
		{
			if(ext_pow_voltage_state != 3)
			{
				ext_pow_voltage_state = 3;

				ext_pow_set_status(0); // norma
				// power green led on
				HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_SET);
				// turn off load
				send_command(COMMAND_LOAD_OFF, CHANNEL0);
				send_command(COMMAND_LOAD_OFF, CHANNEL1);
				send_command(COMMAND_LOAD_OFF, CHANNEL2);
				send_command(COMMAND_LOAD_OFF, CHANNEL3);
				HAL_Delay(2000);
				// turn on charge
				send_command(COMMAND_CHARGE_ON, CHANNEL0);
				send_command(COMMAND_CHARGE_ON, CHANNEL1);
				send_command(COMMAND_CHARGE_ON, CHANNEL2);
				send_command(COMMAND_CHARGE_ON, CHANNEL3);
				// turn on red charge led
				HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_SET);
			}
		}
	}
}
