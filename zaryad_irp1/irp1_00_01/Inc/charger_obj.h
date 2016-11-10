/*
 * charger_obj.h
 *
 *  Created on: Oct 16, 2016
 *      Author: root
 */

#ifndef INC_CHARGER_OBJ_H_
#define INC_CHARGER_OBJ_H_

#define CHARGE_CONTROL_PERIOD 2

#define CHARGE_CRITICAL_TEMPERATURE 4500
#define CHARGE_CRITICAL_VOLTAGE 34000
#define CHARGE_CRITICAL_TEMPERATURE_SPEED 100
#define DISCHARGE_CRITICAL_VOLTAGE 27000

#define DROP_CHARGE_PERIOD 4
#define DROP_CHARGE_iDLE_PERIOD 24

#define LOW_CHECK_CHARGE_VOLTAGE_THRESHOLD 28000	// 28 V
#define VOLTAGE_DELTA_U 30	// 100 mV



void charger_control_task();

int charger_check_criterions();

void reset_voltage_local_max();

#endif /* INC_CHARGER_OBJ_H_ */
