/*
 * int_adc_measure_task.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "presentation_adc_measure_task.h"
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
extern uint battery_type;

void presentation_adc_measure_task()
{

	static int address_index = 0;
	static uint32_t frozen_seconds_tick = 0;

	static int version_displayed = 0;
	static int step = 0;


	if (!presentation_complete)
	{
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
				if(seconds_tick % 2 == 1)
				{
					if(address_index > 11)
					{
						presentation_complete = 1;

						if(values[10] == 0) // TS3 != 0K
						{
							//8lia21
							svd2_light = 1;
							battery_type = 21;
						}
						else
						{
							//8lia42
							svd1_light = 1;
							battery_type = 42;
						}

						voltage = 0;
						for(int i=0; i<8; i++)
							voltage += values[i];
						voltage /= 100;
					}
					else
					{
						turn_off_display = 1;
					}

				}
				else if(seconds_tick % 2 == 0)
				{
					turn_off_display = 0;

					battery_address = addresses[address_index];

					//turn off display
					GPIOA->BRR = SVD1_4_catode_Pin;
					GPIOA->BRR = SVD2_5_catode_Pin;
					GPIOA->BRR = SVD3_6_catode_Pin;

					battery_control_task();
					if(battery_value != 0xffff)
						voltage = battery_value;
					else
						voltage = 0;

					if(address_index > 7)
					{

						if(voltage > 0)
						{
							values[address_index] = voltage/10 -273;
							voltage = (voltage/10 -273) * 10;
						}
						else
						{
							values[address_index] = 0;
						}
					}
					else
					{
						values[address_index] = voltage;
						voltage += 50;
						voltage /= 100;
					}

					address_index++;

				}// end if(seconds_tick % 3 == 2)

			}// end if(!version_displayed)

		}// end if(seconds_tick > frozen_seconds_tick)

	}// end if (!complete)

}//void presentation_adc_measure_task()
