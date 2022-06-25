/*
 * int_adc_measure_task.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "stm32l0xx_hal.h"
#include "adc.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

#include "int_adc_measure_task.h"
#include "battery_control_task.h"

extern uint8_t addresses[];
extern uint8_t battery_address;
extern uint16_t battery_value;
extern uint voltage;
extern int turn_off_display;
extern int D_VERSION;

void int_adc_measure_task()
{

	static int address_index = 0;
	static uint32_t frozen_seconds_tick = 0;

	static int version_displayed = 0;
	static int step = 0;


	if(seconds_tick > frozen_seconds_tick)
	{
		frozen_seconds_tick = seconds_tick;

		if(!version_displayed)
		{
			if(step == 0)
			{
				turn_off_display = 1;
				step++;
			}
			else if(step == 1)
			{
				turn_off_display = 0;
				voltage = D_VERSION;
				step++;
			}
			else if(step == 2)
			{
				turn_off_display = 1;
				version_displayed = 1;
			}
		}
		else
		{
			if(seconds_tick % 3 == 2)
			{
				turn_off_display = 1;
			}
			else if(seconds_tick % 3 == 0)
			{
				turn_off_display = 0;

				battery_address = addresses[address_index];
				address_index++;
				if(address_index > 11)
					address_index = 0;

				//turn off display
				GPIOA->BRR = SVD1_4_catode_Pin;
				GPIOA->BRR = SVD2_5_catode_Pin;
				GPIOA->BRR = SVD3_6_catode_Pin;

				battery_control_task();
				if(battery_value != 0xffff)
					voltage = battery_value / 10;
				else
					voltage =0;
			}

		}
	}

}
