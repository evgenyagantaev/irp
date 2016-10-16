/*
 * switch_obj.c
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#include "switch_obj.h"
#include "gpio.h"
#include "battery_obj.h"


void switch_charge_on()
{
	HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
	set_charge_flag(1);
	battery_state_set(CHARGING_STATE);
}
void switch_charge_off()
{
	HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
	set_charge_flag(0);
	battery_state_set(IDLE_STATE);
}
void switch_discharge_on()
{
	HAL_GPIO_WritePin(GPIOB, disch_out_Pin, GPIO_PIN_SET);
	set_discharge_flag(1);
	battery_state_set(DISCHARGING_STATE);
}
void switch_discharge_off()
{
	HAL_GPIO_WritePin(GPIOB, disch_out_Pin, GPIO_PIN_RESET);
	set_discharge_flag(0);
	battery_state_set(IDLE_STATE);
}
void switch_load_on()
{
	HAL_GPIO_WritePin(GPIOA, on_bat2_out_Pin, GPIO_PIN_SET);
	HAL_Delay(700);
	HAL_GPIO_WritePin(GPIOA, on_bat1_out_Pin, GPIO_PIN_SET);
	set_load_flag(1);
	battery_state_set(LOAD_STATE);
}
void switch_load_off()
{
	HAL_GPIO_WritePin(GPIOA, on_bat2_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(700);
	HAL_GPIO_WritePin(GPIOA, on_bat1_out_Pin, GPIO_PIN_RESET);
	set_load_flag(0);
	battery_state_set(IDLE_STATE);
}
void switch_ktc_on()
{
	battery_state_set(CTC_CHARGING_STATE);
}
void switch_ktc_off()
{
	battery_state_set(IDLE_STATE);
}

