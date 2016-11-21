/*
 * switch_obj.c
 *
 *  Created on: Oct 11, 2016
 *      Author: root
 */

#include "switch_obj.h"
#include "gpio.h"
#include "battery_obj.h"
#include "charger_obj.h"
#include "coulombcounter_obj.h"
#include "eeprom_storage_obj.h"


void switch_charge_on()
{
	reset_voltage_local_max();
	HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
	set_charge_flag(1);
	battery_state_set(CHARGING_STATE);
	// calculate and set critical pumped in capacity threshold
	int32_t coulombmeter = coulombmeter_get();
	int32_t current_discharge = (int32_t)discharge_capacity_get() - coulombmeter;
	if(current_discharge > 0)
	{
		double recharge_value = 1.5 * (double)current_discharge;
		set_critical_capacity_threshold(coulombmeter + (int32_t)recharge_value);
	}
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
	if(battery_state_get() == CHARGING_STATE)
	{
		reset_voltage_local_max();
		battery_state_set(CTC_CHARGING_STATE);
	}
	else if(battery_state_get() == CHARGED_STATE)
		battery_state_set(CTC_CHARGED_STATE);
}
void switch_ktc_off()
{
	HAL_GPIO_WritePin(GPIOB, disch_out_Pin, GPIO_PIN_RESET);
	set_discharge_flag(0);
	battery_state_set(CHARGING_STATE);
}

void switch_ktc_discharge_on()
{

	HAL_GPIO_WritePin(GPIOB, disch_out_Pin, GPIO_PIN_SET);
	set_discharge_flag(1);
	battery_state_set(CTC_DISCHARGING_STATE);
	// reset discharge capacity counter
	set_discharge_cap_meter(0.0);
}

void switch_ktc_recharge_on()
{
	reset_voltage_local_max();
	HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
	set_charge_flag(1);
	battery_state_set(CTC_RECHARGING_STATE);
	//reset coulombmeter
	coulombmeter_set(0.0);
}
