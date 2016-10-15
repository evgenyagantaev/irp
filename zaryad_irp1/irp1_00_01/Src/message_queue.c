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
		uint8_t return_data = message_queue[0];
		//shift message_queue
		int i;
		for(i=0; i<(message_index); i++)
			message_queue[i] = message_queue[i+1];
		message_index--;

		return return_data;
	}
	else
		return 255;
}

int get_message_index()
{
	return message_index;
}
