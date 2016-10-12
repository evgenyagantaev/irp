/*
 * charge_level_detector_obj.h
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#ifndef INC_CHARGE_LEVEL_DETECTOR_OBJ_H_
#define INC_CHARGE_LEVEL_DETECTOR_OBJ_H_

#define TEMPERATURE_TIME_INTERVAL 120 // sec
#define VOLTAGE_HIGH_THRESHOLD 26000 // mV
#define VOLTAGE_LOW_THRESHOLD 20000 // mV

static const int VOLTAGE_SPAN = VOLTAGE_HIGH_THRESHOLD - VOLTAGE_LOW_THRESHOLD;

static uint32_t charge_level; // percents

static int pred_pred_temperature;
static int pred_temperature;
static int charge_detector_temperature;

void charge_level_detector_init();

int charge_level_get();
void charge_level_set(int level);

void charge_detector_temperature_set(int temperature);
void charge_level_detect();


#endif /* INC_CHARGE_LEVEL_DETECTOR_OBJ_H_ */
