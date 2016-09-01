/*
 * external_power.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "external_power.h"


int32_t ext_pow_set_voltage(int32_t voltage)
{
    external_power_voltage = voltage;

    return external_power_voltage;
}
int32_t ext_pow_get_voltage()
{
    return external_power_voltage;
}
uint8_t ext_pow_set_status(uint8_t status)
{
    external_power_status = status;

    return external_power_status;
}
uint8_t ext_pow_get_status()
{
    return external_power_status;
}
