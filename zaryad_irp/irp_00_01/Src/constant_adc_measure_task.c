/*
 * int_adc_measure_task.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "constant_adc_measure_task.h"
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

#include "battery_control_task.h"

extern uint8_t addresses[];
extern uint16_t values[];
extern uint8_t battery_address;
extern uint16_t battery_value;
extern uint voltage;
extern int turn_off_display;
extern int D_VERSION;

extern int svd1_light;
extern int svd2_light;
extern int svd3_light;
extern int svd4_light;
extern int svd5_light;
extern int svd6_light;

extern int presentation_complete;

void constant_adc_measure_task()
{

	static uint32_t frozen_seconds_tick = 0;

	if (presentation_complete)
	{
		if(seconds_tick > frozen_seconds_tick)
		{
			frozen_seconds_tick = seconds_tick;

			uint battery_voltage = 0;

			for(int i=0; i<8; i++)
			{
				battery_address = addresses[i];

				battery_control_task();
				if(battery_value != 0xffff)
					voltage = battery_value;
				else
					voltage = 0;

				voltage /= 100;
				values[i] = voltage;
				battery_voltage += voltage;

			}// end for(int i=0; i<8; i++)

			voltage = battery_voltage;

		}// end if(seconds_tick > frozen_seconds_tick)

	}// end if (presentation_complete)

}//void constant_adc_measure_task()
