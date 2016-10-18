/*
 * charge_check_task..h
 *
 *  Created on: Oct 12, 2016
 *      Author: root
 */

#ifndef INC_CHARGE_CHECK_TASK_H_
#define INC_CHARGE_CHECK_TASK_H_

#include "stdint.h"

#define QUOTE_OK 0x0022

void channel_states_get(uint32_t *ref_states);
void charge_check_task();

#endif /* INC_CHARGE_CHECK_TASK_H_ */
