/*
 * button.h
 *
 *  Created on: Sep 3, 2016
 *      Author: root
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

static int button_short_press_detected;
static int button_long_press_detected;

void button_initialization();
int button_get_short_status();
int button_get_long_status();
void button_set_short_status(int status);
void button_set_long_status(int status);

#endif /* INC_BUTTON_H_ */
