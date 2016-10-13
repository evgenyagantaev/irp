/*
 * spi_pipe.h
 *
 *  Created on: Aug 31, 2016
 *      Author: root
 */

#ifndef INC_SPI_PIPE_H_
#define INC_SPI_PIPE_H_

#include "stdint.h"

#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3

#define COMMAND_CHARGE_ON			0x25
#define COMMAND_CHARGE_OFF			0x26
#define COMMAND_DISCHARGE_ON		0x27
#define COMMAND_DISCHARGE_OFF		0x28

#define COMMAND_GET_VOLTAGE			0x29
#define COMMAND_GET_TEMPERATURE		0x30
#define COMMAND_GET_CURRENT			0x31
#define COMMAND_GET_CAPACITY		0x32
#define COMMAND_SET_CAPACITY		0x32

#define COMMAND_LOAD_ON				0x33
#define COMMAND_LOAD_OFF			0x34

#define COMMAND_GET_CHARGE_LEVEL	0x35

#define COMMAND_KTC_ON				0x36
#define COMMAND_KTC_OFF				0x37

void spi_pipe_send_command(uint16_t command, int channel);
int spi_pipe_receive_data(uint16_t *data, int channel);  // returns quote (0x0022)

void spi_pipe_transmit(uint8_t byte);

#endif /* INC_SPI_PIPE_H_ */
