/*
 * time_management_task.c
 *
 *  Created on: Aug 31, 2016
 *      Author: root
 */

#include "time_management_task.h"
#include "stm32l0xx_hal.h"
#include "gpio.h"

#include "coulombcounter_obj.h"

#include "usart.h"


void time_management_task()
{
	//char message[64];
	//sprintf((char *)message, "time_management_task\r\n");
	//HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

    uint32_t current_tick = HAL_GetTick();
    if(current_tick >= (frozen_systick + 1000))
    {
        frozen_systick = current_tick;
        seconds_tick++;
        // toggle led
        //HAL_GPIO_TogglePin(GPIOA, power_led_green_out_Pin);

        // fit coulombmeter
        fit_coulombmeter();

    }

}

uint32_t time_manager_get_seconds()
{
    return seconds_tick;
}
