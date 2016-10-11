/*
 * time_management_task.h
 *
 *  Created on: Aug 31, 2016
 *      Author: root
 */

#ifndef INC_TIME_MANAGEMENT_TASK_H_
#define INC_TIME_MANAGEMENT_TASK_H_

#include "stdint.h"

static uint32_t frozen_systick;
static uint32_t seconds_tick;


void time_management_task();
uint32_t time_manager_get_seconds();

#endif /* INC_TIME_MANAGEMENT_TASK_H_ */
