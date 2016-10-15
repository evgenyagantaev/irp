/*
 * battery_charge_controller.h
 *
 *  Created on: Oct 15, 2016
 *      Author: root
 */

#ifndef INC_BATTERY_CHARGE_CONTROLLER_H_
#define INC_BATTERY_CHARGE_CONTROLLER_H_


#define CRITICAL_CHARGE_VOLTAGE 36000
#define CRITICAL_CHARGE_TEMPERATURE 4500
#define CRITICAL_CHARGE_TEMPERATURE_SPEED 100




void battery_charge_control_task();


#endif /* INC_BATTERY_CHARGE_CONTROLLER_H_ */
