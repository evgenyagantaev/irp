/*
 * button_polling_task.c
 *
 *  Created on: Sep 3, 2016
 *      Author: root
 */

#include "button_polling_task.h"
#include "button.h"
#include "gpio.h"

extern int presentation_complete;

extern int svd1_light;
extern int svd2_light;
extern int svd3_light;
extern int svd4_light;
extern int svd5_light;
extern int svd6_light;

extern uint32_t seconds_tick;

extern int express_charging;
extern uint32_t express_charging_start_moment;
extern int norm_charging;
extern uint32_t norm_charging_start_moment;
extern int discharging;


void button_polling_task()
{
	static uint32_t frozen_seconds_tick = 0;

	if(seconds_tick > frozen_seconds_tick)
	{
		if (presentation_complete)
		{
			//*********** express charge button *********************************
			if((GPIOA->IDR & SVD2_5_catode_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
			}
			else
			{
				if((GPIOB->IDR & batton_input_Pin) == (uint32_t)GPIO_PIN_RESET)
				{
					// turn on led
					svd5_light = 1;
					// turn on express charging
					express_charging = 1;
					express_charging_start_moment = seconds_tick;
				}
			}
			//********************************************************************


			//*********** norm charge button *********************************
			if((GPIOA->IDR & SVD1_4_catode_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
			}
			else
			{
				if((GPIOB->IDR & batton_input_Pin) == (uint32_t)GPIO_PIN_RESET)
				{
					// turn on led
					svd4_light = 1;
					// turn on express charging
					norm_charging = 1;
					norm_charging_start_moment = seconds_tick;
				}
			}
			//********************************************************************


			//*********** discharge button *********************************
			if((GPIOA->IDR & SVD3_6_catode_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
			}
			else
			{
				if((GPIOB->IDR & batton_input_Pin) == (uint32_t)GPIO_PIN_RESET)
				{
					// turn on led
					svd5_light = 0;
					svd4_light = 0;
					svd6_light = 1;
					// turn on discharging
					if(express_charging || norm_charging)
					{
						express_charging = 0;
						norm_charging = 0;
					}
					else
					{
						discharging = 1;
					}
				}
			}
			//********************************************************************



			//*********** stop button ********************************************
			if((GPIOB->IDR & stop_button_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
				// turn off led
				svd5_light = 0;
				svd4_light = 0;
				svd6_light = 0;
				// turn off express charging
				express_charging = 0;
				norm_charging = 0;
				discharging = 0;

			}

		}// if (presentation_complete)

	}// if(seconds_tick > frozen_seconds_tick)

}
