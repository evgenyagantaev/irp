/*
 * external_power.h
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#ifndef INC_EXTERNAL_POWER_H_
#define INC_EXTERNAL_POWER_H_

#include "stdint.h"

static int32_t external_power_voltage; // milivolts
static uint8_t external_power_status;  // 0 - norma, 1 - less, 2 - more.

int32_t ext_pow_set_voltage(int32_t voltage);
int32_t ext_pow_get_voltage();
uint8_t ext_pow_set_status(uint8_t status);
uint8_t ext_pow_get_status();

#endif /* INC_EXTERNAL_POWER_H_ */
