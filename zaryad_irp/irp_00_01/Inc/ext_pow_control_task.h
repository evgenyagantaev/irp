/*
 * void ext_pow_control_task.h
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#ifndef INC_EXT_POW_CONTROL_TASK_H_
#define INC_EXT_POW_CONTROL_TASK_H_

#include "stdint.h"

static uint32_t ext_pow_frozen_systick;
static int ext_pow_voltage_state = -1;

void ext_pow_control_task();

#endif /* INC_EXT_POW_CONTROL_TASK_H_ */
