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
static int button_is_pressed;

void button_initialization();
int button_get_short_status();
int button_get_long_status();
int button_get_state();  // get state of button (is pressed or not)
void button_set_short_status(int status);
void button_set_long_status(int status);
void button_set_state(int state); //set state (1 - is pressed, 0 - is not pressed)

#endif /* INC_BUTTON_H_ */
