/*
 * message_queue.h
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#ifndef INC_MESSAGE_QUEUE_H_
#define INC_MESSAGE_QUEUE_H_

#include "stdint.h"

#define MESSAGE_QUEUE_LENGTH 64

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

#define COMMAND_GET_BATTERY_STATE	0x38

#define COMMAND_CTC_DISCHARGE_ON	0x39
#define COMMAND_CTC_RECHARGE_ON		0x40


static uint8_t message_queue[MESSAGE_QUEUE_LENGTH];
static int message_index;

uint8_t message_push(uint8_t message);
uint8_t message_pop();
int get_message_index();

#endif /* INC_MESSAGE_QUEUE_H_ */
