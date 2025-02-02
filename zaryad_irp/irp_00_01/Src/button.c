/*
 * button.c
 *
 *  Created on: Sep 3, 2016
 *      Author: root
 */

#include "button.h"

static int button_short_press_detected;
static int button_long_press_detected;

void button_initialization()
{
	button_set_short_status(0);
	button_set_long_status(0);
}
int button_get_short_status()
{
	return button_short_press_detected;
}
int button_get_long_status()
{
	return button_long_press_detected;
}
void button_set_short_status(int status)
{
	button_short_press_detected = status;
}
void button_set_long_status(int status)
{
	button_long_press_detected = status;
}

int button_get_state()  // get state of button (is pressed or not)
{
	return button_is_pressed;
}

void button_set_state(int state) //set state (1 - is pressed, 0 - is not pressed)
{
	button_is_pressed = state;
}





