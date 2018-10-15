/*
 * button_interpreter_task.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "button_interpreter_task.h"
#include "button.h"
#include "ext_power_obj.h"

#include "spi.h"
#include "spi_pipe.h"
#include "gpio.h"

#include "ctc_controller_obj.h"

static int ktc_on_flag = 0;


void button_interpreter_task()
{
	if(!button_get_state()) // button is not pressed
	{
		// check if button was pressed and this press is not served yet
		if(button_get_short_status() || button_get_long_status())
		{

			// check voltage
			//***************************************************************
			int external_power_voltage = ext_pow_get_voltage();

			if((external_power_voltage>=40000) && (external_power_voltage<=55000))
			{
				// CTC diapazon
				//*
				if(button_get_long_status)
				{
					// clear flags
					button_set_short_status(0);
					button_set_long_status(0);

					if(ktc_on_flag) // ktc is on, we switch it off
					{
						// send command ktc off
						// turn off ktc in all channels
						spi_pipe_send_command(COMMAND_KTC_OFF, 0);
						spi_pipe_send_command(COMMAND_KTC_OFF, 1);
						spi_pipe_send_command(COMMAND_KTC_OFF, 2);
						spi_pipe_send_command(COMMAND_KTC_OFF, 3);
						// charge on
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL0);
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL1);
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL2);
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL3);

						// turn off ktc led
						HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_RESET);

						ktc_on_flag = 0;

						ctc_set_stage(CTC_JUST_INACTIVATED);
					}
					else
					{
						// send command ktc on
						// turn on ktc in all channels
						spi_pipe_send_command(COMMAND_KTC_ON, 0);
						spi_pipe_send_command(COMMAND_KTC_ON, 1);
						spi_pipe_send_command(COMMAND_KTC_ON, 2);
						spi_pipe_send_command(COMMAND_KTC_ON, 3);

						// turn off green ktc led
						HAL_GPIO_WritePin(GPIOA, ctc_led_green_out_Pin, GPIO_PIN_RESET);
						// turn on ktc led
						HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_SET);

						ktc_on_flag = 1;

						ctc_set_stage(CTC_JUST_ACTIVATED);
					}
				}
				//*/

			}
			else if((external_power_voltage>30000) && (external_power_voltage<40000))
			{
				// debug diapazon

				// debug**************************************************
				// check state and commit actions
				//*
				// clear flags
				button_set_short_status(0);
				button_set_long_status(0);

				// enter in debug mode only if pb4 pin = 0 (i.e. set debug mode jumper)
				if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET)
				{
					if(interpreter_state == 0)
					{
						// charge on
						spi_pipe_send_command(COMMAND_CLEAN_EEPROM, CHANNEL0);
						spi_pipe_send_command(COMMAND_CLEAN_EEPROM, CHANNEL1);
						spi_pipe_send_command(COMMAND_CLEAN_EEPROM, CHANNEL2);
						spi_pipe_send_command(COMMAND_CLEAN_EEPROM, CHANNEL3);
					}
					if(interpreter_state == 1)
					{
						// charge on
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL0);
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL1);
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL2);
						spi_pipe_send_command(COMMAND_CHARGE_ON, CHANNEL3);
					}
					else if(interpreter_state == 2)
					{
						// charge off
						spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL0);
						spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL1);
						spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL2);
						spi_pipe_send_command(COMMAND_CHARGE_OFF, CHANNEL3);
					}
					else if(interpreter_state == 3)
					{
						// discharge on
						spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL0);
						spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL1);
						spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL2);
						spi_pipe_send_command(COMMAND_DISCHARGE_ON, CHANNEL3);
					}
					else if(interpreter_state == 4)
					{
						// discharge off
						spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL0);
						spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL1);
						spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL2);
						spi_pipe_send_command(COMMAND_DISCHARGE_OFF, CHANNEL3);
					}
					interpreter_state++;
					if(interpreter_state >= 5)
						interpreter_state = 0;
					//*/
					// debug**************************************************
				}

			}
		}
	}
}





















