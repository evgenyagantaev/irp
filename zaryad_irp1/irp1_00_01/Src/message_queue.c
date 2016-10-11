/*
 * message_queue.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include "message_queue.h"



uint8_t message_push(uint8_t message)
{
	if(message_index < MESSAGE_QUEUE_LENGTH)
	{
		message_queue[message_index] = message;
		message_index++;

		return message_queue[message_index - 1];
	}
	else
		return 255;
}



uint8_t message_pop()
{
	if(message_index > 0)
	{
		message_index--;
		return message_queue[message_index];
	}
	else
		return 255;
}
