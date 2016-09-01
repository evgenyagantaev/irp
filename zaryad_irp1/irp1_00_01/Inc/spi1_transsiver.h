/*
 * spi1_transsiver.h
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#ifndef INC_SPI1_TRANSSIVER_H_
#define INC_SPI1_TRANSSIVER_H_

#include "stdint.h"

uint8_t spi1_read_message();
uint8_t spi1_send_data(uint8_t *data, int length);

#endif /* INC_SPI1_TRANSSIVER_H_ */
