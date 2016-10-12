/*
 * spi1_transceiver.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include "spi1_transceiver.h"
#include "spi.h"


void spi1_send_data(uint32_t data)
{
	uint16_t in_data;
	uint16_t out_buffer;

	out_buffer = data >> 16;
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
