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


void button_polling_task()
{
	static uint32_t frozen_seconds_tick = 0;

	if(seconds_tick > frozen_seconds_tick)
	{
		if (presentation_complete)
		{
			if((GPIOA->IDR & SVD2_5_catode_Pin) == (uint32_t)GPIO_PIN_RESET)
			{
				GPIOA->BSRR = SVD2_5_catode_Pin;

				if((GPIOB->IDR & batton_input_Pin) == (uint32_t)GPIO_PIN_RESET)
				{
					// turn on led
					svd5_light = 1;
				}
				GPIOA->BRR = SVD2_5_catode_Pin;
			}
			else
			{
				if((GPIOB->IDR & batton_input_Pin) == (uint32_t)GPIO_PIN_RESET)
				{
					// turn on led
					svd5_light = 1;
				}
			}
		}

	}

}
