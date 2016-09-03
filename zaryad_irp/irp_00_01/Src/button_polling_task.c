/*
 * button_polling_task.c
 *
 *  Created on: Sep 3, 2016
 *      Author: root
 */

#include "button_polling_task.h"
#include "button.h"
#include "gpio.h"


void button_polling_task()
{
	if(HAL_GPIO_ReadPin(ctc_onoff_button_exti15_GPIO_Port, ctc_onoff_button_exti15_Pin) == GPIO_PIN_RESET)
	{
		//button pressed
		if(!button_press_timer_on)
		{
			//remember the moment when we firstly detected button pressed
			button_set_press_start(HAL_GetTick());
			button_press_timer_on = 1;
		}
		else //button_press_timer_on == 0
		{
			// check how long is button pressed
			if((HAL_GetTick() - button_get_press_start()) >= 2000)
			{
				// long press detected
				if(button_get_long_status() == 0)
				{
					button_set_long_status(1);
				}
			}
			else if((HAL_GetTick() - button_get_press_start()) >= 300)
			{
				// short press detected
				if(button_get_long_status() == 0)
				{
					button_set_short_status(1);
				}
			}
		}
	}
	else
	{
		button_press_timer_on = 0;
	}
}
