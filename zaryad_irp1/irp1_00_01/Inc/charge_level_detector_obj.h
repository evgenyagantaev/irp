/*
 * charge_level_detector_obj.h
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#ifndef INC_CHARGE_LEVEL_DETECTOR_OBJ_H_
#define INC_CHARGE_LEVEL_DETECTOR_OBJ_H_

#include "stdint.h"

#define TEMPERATURE_TIME_INTERVAL 120 // sec
#define VOLTAGE_HIGH_THRESHOLD 28500 // mV
#define VOLTAGE_LOW_THRESHOLD 23000 // mV

static const int VOLTAGE_SPAN = VOLTAGE_HIGH_THRESHOLD - VOLTAGE_LOW_THRESHOLD;

static uint32_t charge_level; // percents



void charge_level_detector_init();

uint32_t charge_level_get();
void charge_level_set(uint32_t level);

void charge_level_detect();
void initial_charge_level_estimation();


#endif /* INC_CHARGE_LEVEL_DETECTOR_OBJ_H_ */
