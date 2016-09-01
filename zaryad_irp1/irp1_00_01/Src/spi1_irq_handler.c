/*
 * spi1_irq_handler.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include "spi1_irq_handler.h"
#include "message_queue.h"


void SPI1_IRQHandler(void)
{
	int i;

	uint16_t spi1_in_data;

	if((SPI1->SR & SPI_SR_RXNE) != 0)
	{
		// disable spi1 rxne interrupt
		SPI1->CR2 &= ~SPI_CR2_RXNEIE;   // disable rxne interrupt
		// stop systick timer
		SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;

		// read from spi data register
		spi1_in_data = SPI1->DR;

		// parse command **********************************************

		if(spi1_in_data == MSG_GET_BATT_VOLTAGE) // get battery voltage
		{
			int i = 0;
		}
		else if(spi1_in_data == MSG_GET_BATT_CURRENT) // get battery current
		{
			int i = 0;
		}
		else if(spi1_in_data == MSG_GET_BATT_TEMPERATURE) // get battery temperature
		{
			int i = 0;
		}
		else
		{
			int i = 0;
		}

		//*************************************************************

		// enable spi1 rxne interrupt
		SPI1->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
		// start systick timer
		SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;
	}
}
