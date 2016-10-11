/*
 * spi1_irq_handler.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include <battery_obj.h>
#include "spi1_irq_handler.h"



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
		message_push((uint8_t)spi1_in_data);



		// enable spi1 rxne interrupt
		//SPI1->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
		// start systick timer
		//SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;
	}
}
