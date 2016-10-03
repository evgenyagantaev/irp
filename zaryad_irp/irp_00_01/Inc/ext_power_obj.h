/*
 * ext_power_obj.h
 *
 *  Created on: Sep 11, 2016
 *      Author: root
 */

#ifndef INC_EXT_POWER_OBJ_H_
#define INC_EXT_POWER_OBJ_H_

#include "stdint.h"

static const int LOW_LOAD_THRESHOLD = 30000;
static const int LOW_CHARGE_THRESHOLD = 40000;
static const int HIGH_THRESHOLD = 55000;

static uint32_t vdc1; // milivolts
static uint32_t vdc2; // milivolts
static uint32_t vdca; // milivolts

#define NORM 0
#define LOW 1
#define HIGH 2


static int external_power_status = 0;  // 0 - norma, 1 - less, 2 - more.

int ext_pow_set_voltage(int32_t voltage);
int32_t ext_pow_get_voltage();
void ext_pow_set_status(uint8_t status);
int ext_pow_get_status();

void extpow_measure_voltage();

#endif /* INC_EXT_POWER_OBJ_H_ */
