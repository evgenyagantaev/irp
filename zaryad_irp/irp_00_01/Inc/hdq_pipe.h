/*
 * hdq_pipe.h
 *
 *  Created on: Jun 21, 2022
 *      Author: agant
 */

#ifndef INC_HDQ_PIPE_H_
#define INC_HDQ_PIPE_H_

#include "main.h"

void send_brake();
void send_restore();
void send_byte(uint8_t data);
uint16_t receive_word();


#endif /* INC_HDQ_PIPE_H_ */
