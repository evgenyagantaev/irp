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
#define CHARGE_CRITICAL_VOLTAGE 36000
#define CHARGE_CRITICAL_TEMPERATURE_SPEED 100
#define DISCHARGE_CRITICAL_VOLTAGE 26000

#define DROP_CHARGE_PERIOD 4
#define DROP_CHARGE_iDLE_PERIOD 24



void charger_control_task();

#endif /* INC_CHARGER_OBJ_H_ */
