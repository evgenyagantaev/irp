/*
 * spi1_transceiver.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include "spi1_transceiver.h"
#include "spi.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>

//debug
static int counter = 0;
extern UART_HandleTypeDef huart1;


void spi1_send_data(uint32_t data)
{
	//debug
	char message[64];

	uint16_t in_data;
	uint16_t out_buffer;

	// clean rx buffer
	if ((SPI1->SR & SPI_SR_RXNE) != RESET );
		in_data = SPI1->DR;

	//debug
	counter++;
	sprintf(message, "%d: data = 0x%x\r\n", counter, data);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	out_buffer = (uint16_t)(data >> 16);
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = out_buffer;
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR;

	out_buffer = (uint16_t)data;
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = out_buffer;
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR;

	// send quote ***************************
	out_buffer = 0x0022;
	// wait for spi transmitter readiness
	while ((SPI1->SR & SPI_SR_TXE) == RESET );
	SPI1->DR = out_buffer;
	// wait while a transmission complete
	while ((SPI1->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI1->DR;

}
