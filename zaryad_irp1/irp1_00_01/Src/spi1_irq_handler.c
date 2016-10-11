/*
 * spi1_irq_handler.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include "spi1_irq_handler.h"
#include "message_queue.h"
#include "gpio.h"
#include "battery.h"


void SPI1_IRQHandler(void)
{
	int i;

	uint16_t spi1_in_data;
	uint16_t spi1_out_buffer;

	if((SPI1->SR & SPI_SR_RXNE) != 0)
	{
		// disable spi1 rxne interrupt
		//SPI1->CR2 &= ~SPI_CR2_RXNEIE;   // disable rxne interrupt
		// stop systick timer
		//SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;

		// read from spi data register
		spi1_in_data = SPI1->DR;

		// parse command **********************************************

		if(spi1_in_data == COMMAND_GET_VOLTAGE) // get battery voltage
		{
			spi1_send_data(battery_voltage_get());
		}
		else if(spi1_in_data == COMMAND_GET_CURRENT) // get battery current
		{
			spi1_send_data(battery_current_get());
		}
		else if(spi1_in_data == COMMAND_GET_TEMPERATURE) // get battery temperature
		{
			spi1_send_data(battery_temperature_get());
		}
		else if(spi1_in_data == COMMAND_CHARGE_ON) //
		{
			HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
		}
		else if(spi1_in_data == COMMAND_CHARGE_OFF) //
		{
			HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
		}
		else if(spi1_in_data == COMMAND_DISCHARGE_ON) //
		{
			HAL_GPIO_WritePin(GPIOB, disch_out_Pin, GPIO_PIN_SET);
		}
		else if(spi1_in_data == COMMAND_DISCHARGE_OFF) //
		{
			HAL_GPIO_WritePin(GPIOB, disch_out_Pin, GPIO_PIN_RESET);
		}
		else if(spi1_in_data == COMMAND_LOAD_ON) //
		{
			HAL_GPIO_WritePin(GPIOA, on_bat2_out_Pin, GPIO_PIN_SET);
			HAL_Delay(700);
			HAL_GPIO_WritePin(GPIOA, on_bat1_out_Pin, GPIO_PIN_SET);
		}
		else if(spi1_in_data == COMMAND_LOAD_OFF) //
		{
			HAL_GPIO_WritePin(GPIOA, on_bat2_out_Pin, GPIO_PIN_RESET);
			HAL_Delay(700);
			HAL_GPIO_WritePin(GPIOA, on_bat1_out_Pin, GPIO_PIN_RESET);
		}
		else
		{
			int i = 0;
		}

		//*************************************************************

		// enable spi1 rxne interrupt
		//SPI1->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
		// start systick timer
		//SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;
	}
}
