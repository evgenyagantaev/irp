/*
 * spi_pipe.c
 *
 *  Created on: Aug 31, 2016
 *      Author: root
 */

#include "spi_pipe.h"
#include "spi.h"


void spi_pipe_transmit(uint8_t byte)
{
    spi2_write_byte(byte);
}


void send_command(uint16_t command, int channel)
{
	uint16_t chipselect_mask[] = {chipsel1_out_Pin, chipsel2_out_Pin, chipsel3_out_Pin, chipsel4_out_Pin};

	uint16_t in_data;
	// chipsel low
	GPIOB->BRR = chipselect_mask[channel];
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = command;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR;
	// chipsel high
	GPIOB->BSRR = chipselect_mask[channel];
	spi_short_delay();
}
