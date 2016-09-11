/*
 * ext_pow_control_task.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "ext_pow_control_task.h"
#include "ext_power_obj.h"
#include "gpio.h"

void ext_pow_control_task()
{
	extpow_measure_voltage();
	uint32_t ext_pow_voltage = ext_pow_get_voltage();

	if(ext_pow_voltage > HIGH_THRESHOLD)
	{
		ext_pow_set_status(2); // more
		// power red led on
		HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
	}
	else if(ext_pow_voltage < LOW_THRESHOLD)
	{
		ext_pow_set_status(1); // less
		// power red led on
		HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
	}
	else // everything ok
	{
		ext_pow_set_status(0); // norma
		// power green led on
		HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_SET);
	}
}
