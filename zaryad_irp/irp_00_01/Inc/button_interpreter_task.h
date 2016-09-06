/*
 * button_interpreter_task.h
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#ifndef INC_BUTTON_INTERPRETER_TASK_H_
#define INC_BUTTON_INTERPRETER_TASK_H_

#include "stdint.h"

#define COMMAND_CHARGE_ON		0x25
#define COMMAND_CHARGE_OFF		0x26
#define COMMAND_DISCHARGE_ON	0x27
#define COMMAND_DISCHARGE_OFF	0x28


static int command_sent;    //
static int interpreter_state;

void button_interpreter_task();
void send_command(uint16_t command);

#endif /* INC_BUTTON_INTERPRETER_TASK_H_ */
