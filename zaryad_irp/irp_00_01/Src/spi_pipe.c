/*
 * spi_pipe.c
 *
 *  Created on: Aug 31, 2016
 *      Author: root
 */

#include "spi_pipe.h"
#include "spi.h"

#include "usart.h"
#include <stdio.h>
#include <string.h>

//debug
static int counter = 0;
extern UART_HandleTypeDef huart1;


void spi_pipe_transmit(uint8_t byte)
{
    spi2_write_byte(byte);
}


void spi_pipe_send_command(uint16_t command, int channel)
{
	uint16_t chipselect_mask[] = {chipsel1_out_Pin, chipsel2_out_Pin, chipsel3_out_Pin, chipsel4_out_Pin};
	uint16_t in_data;

	// clean rx buffer
	if ((SPI2->SR & SPI_SR_RXNE) != RESET );
		in_data = SPI2->DR;


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

	//HAL_Delay(5);
}


int spi_pipe_receive_data(uint32_t *data, int channel)  // returns quote (0x0022)
{
	//debug
	char message[64];

	uint16_t chipselect_mask[] = {chipsel1_out_Pin, chipsel2_out_Pin, chipsel3_out_Pin, chipsel4_out_Pin};

	uint16_t receive_buffer;
	uint32_t data_buffer = 0;

	// clean rx buffer
	if ((SPI2->SR & SPI_SR_RXNE) != RESET );
		receive_buffer = SPI2->DR;

	// chipsel low
	GPIOB->BRR = chipselect_mask[channel];
	spi_short_delay();
	//********************************************
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0x5555;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	receive_buffer = SPI2->DR;		// msb
	data_buffer += (((uint32_t)receive_buffer) << 16);
	// chipsel high
	GPIOB->BSRR = chipselect_mask[channel];
	//***********************************************

	HAL_Delay(5);

	// chipsel low
	GPIOB->BRR = chipselect_mask[channel];
	spi_short_delay();
	//********************************************
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0x5757;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	receive_buffer = SPI2->DR;		// lsb
	data_buffer += (uint32_t)receive_buffer;
	HAL_Delay(5);
	// chipsel high
	GPIOB->BSRR = chipselect_mask[channel];
	//***********************************************
	*data = data_buffer;

	HAL_Delay(5);

	//debug
	counter++;
	sprintf(message, "%d: data = 0x%x\r\n", counter, data_buffer);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	// receive quote *****************************

	// chipsel low
	GPIOB->BRR = chipselect_mask[channel];
	spi_short_delay();
	//********************************************
	// wait for spi transmitter readiness
	while ((SPI2->SR & SPI_SR_TXE) == RESET );
	SPI2->DR = 0x5959;
	// wait while a transmission complete
	while ((SPI2->SR & SPI_SR_RXNE) == RESET );
	receive_buffer = SPI2->DR;		// quote (must be equal 0x0022)


	sprintf(message, "%d: quote = 0x%x\r\n", counter, receive_buffer);
	HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	spi_short_delay();
	// chipsel high
	GPIOB->BSRR = chipselect_mask[channel];
	//***********************************************

	return receive_buffer;
}



