/*
 * internal_adc.h
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#ifndef INC_INTERNAL_ADC_H_
#define INC_INTERNAL_ADC_H_

#include "stdint.h"

int32_t int_adc_measure_ch0(); // returns voltage in milivolts
int32_t int_adc_measure_ch1(); // returns voltage in milivolts
int32_t int_adc_measure_ch2(); // returns voltage in milivolts

#endif /* INC_INTERNAL_ADC_H_ */
