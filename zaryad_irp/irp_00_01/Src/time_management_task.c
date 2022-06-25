/*
 * time_management_task.c
 *
 *  Created on: Aug 31, 2016
 *      Author: root
 */

#include "time_management_task.h"
#include "stm32l0xx_hal.h"
#include "gpio.h"


void time_management_task()
{
    uint32_t current_tick = HAL_GetTick();
    if(current_tick >= (frozen_systick + 1000))
    {
        frozen_systick = current_tick;
        seconds_tick++;
        // toggle led
        //HAL_GPIO_TogglePin(GPIOA, SVD123_anodes_Pin);
    }

}

uint32_t time_manager_get_seconds()
{
    return seconds_tick;
}
