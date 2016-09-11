/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery.h"


int get_charge_flag(int channel)
{
	return charge_flag[channel];
}
int get_discharge_flag(int channel)
{
	return discharge_flag[channel];
}

void set_charge_flag(int flag, int channel)
{
	charge_flag[channel] = flag;
}
void set_discharge_flag(int flag, int channel)
{
	discharge_flag[channel] = flag;
}
