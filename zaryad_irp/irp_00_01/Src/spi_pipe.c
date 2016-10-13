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


void spi_pipe_send_command(uint16_t command, int channel)
{
	uint16_t chipselect_mask[] = {chipsel1_out_Pin, chipsel2_out_Pin, chipsel3_out_Pin, chipsel4_out_Pin};

	uint16_t in_data;
	// chipsel low
	GPIOB->BRR = chipselect_mask[channel];
	spi_short_delay();
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = command;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	in_data = SPI2->DR;
	spi_short_delay();
	// chipsel high
	GPIOB->BSRR = chipselect_mask[channel];
}


int spi_pipe_receive_data(uint32_t *data, int channel)  // returns quote (0x0022)
{
	uint16_t chipselect_mask[] = {chipsel1_out_Pin, chipsel2_out_Pin, chipsel3_out_Pin, chipsel4_out_Pin};

	uint16_t receive_buffer;
	*data = 0;

	// chipsel low
	GPIOB->BRR = chipselect_mask[channel];
	spi_short_delay();
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0x5555;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	receive_buffer = SPI2->DR;		// msb
	*data += ((uint32_t)receive_buffer << 16);
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0x5555;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	receive_buffer = SPI2->DR;		// lsb
	*data += (uint32_t)receive_buffer;

	// receive quote *****************************
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0x5555;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	receive_buffer = SPI2->DR;		// quote (must be equal 0x0022)

	spi_short_delay();
	// chipsel high
	GPIOB->BSRR = chipselect_mask[channel];
}



