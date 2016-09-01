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
