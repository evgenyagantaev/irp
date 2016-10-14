/*
 * spi1_irq_handler.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include <battery_obj.h>
#include "spi1_irq_handler.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

//debug
static int counter = 0;
extern UART_HandleTypeDef huart1;


void SPI1_IRQHandler(void)
{
	char message[64];
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
		//debug
		if(spi1_in_data == 0x25)
			i++;
		message_push((uint8_t)spi1_in_data);

		//debug
		counter++;
		sprintf(message, "%d: spi data = 0x%x\r\n", counter, spi1_in_data);
		HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);



		// enable spi1 rxne interrupt
		//SPI1->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
		// start systick timer
		//SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;
	}
}
