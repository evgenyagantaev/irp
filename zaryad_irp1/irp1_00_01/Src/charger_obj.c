/*
 * charger_obj.c
 *
 *  Created on: Oct 16, 2016
 *      Author: root
 */

#include "charger_obj.h"
#include "time_management_task.h"
#include "battery_obj.h"
#include "gpio.h"
#include "switch_obj.h"

#include "coulombcounter_obj.h"

#include "usart.h"
static char charger_message[64];

static int temperature_buffer[3];
static uint32_t charger_frozen_seconds = 0;

static int drop_charge_current_on = 0;
static uint32_t drop_charge_period_start = 0;

static int voltage_derivative = 0;
static int voltage_deriv_max = 0;
static int voltage_local_max = 0;

static int32_t critical_capacity_threshold = 12000;

void charger_control_task()
{
	//char message[64];
	//sprintf((char *)message, "charger_control_task\r\n");
	//HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

	uint32_t current_seconds = time_manager_get_seconds();

	if(current_seconds - charger_frozen_seconds >= CHARGE_CONTROL_PERIOD)
	{
		charger_frozen_seconds = current_seconds;

		int battery_state = battery_state_get();


		//***************************************************************************************
		if(battery_state == CHARGING_STATE)
		{

			int stop_charge_flag = charger_check_criterions();

			if(stop_charge_flag)
			{
				// stop charge, switch to drop charging
				HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				battery_state_set(CHARGED_STATE);
				// tune capacity
				coulombmeter_set(discharge_capacity_get());
			}
		}// end if(battery_state == CHARGING_STATE) *********************************************
		if(battery_state == CTC_CHARGING_STATE)
		{

			int stop_charge_flag = charger_check_criterions();

			if(stop_charge_flag)
			{
				// stop charge, switch to drop charging
				HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				battery_state_set(CTC_CHARGED_STATE);
				// tune capacity
				coulombmeter_set(discharge_capacity_get());
			}

		}// end if(battery_state == CTC_CHARGING_STATE) **********************************************
		//*********************************************************************************************
		if(battery_state == CTC_RECHARGING_STATE)
		{
			int stop_charge_flag = charger_check_criterions();

			if(stop_charge_flag)
			{
				// stop charge, switch to drop charging
				HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				battery_state_set(CTC_RECHARGED_STATE);
				// tune capacity
				coulombmeter_set(discharge_capacity_get());
			}

		}// end if(battery_state == CTC_RECHARGING_STATE)  ************************************



		//*************************************************************************************
		//*************************************************************************************
		//*************************************************************************************
		//*************************************************************************************
		//*************************************************************************************
		//*************************************************************************************
		//*************************************************************************************
		//*************************************************************************************

		if(((battery_state==CHARGED_STATE) || (battery_state==CTC_CHARGED_STATE) || (battery_state==CTC_RECHARGED_STATE)) && get_charge_flag())
		{
			// drop charge regime
			if(drop_charge_current_on) // current on
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_PERIOD) // it's time to switch current off
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 0;
					// switch off
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_RESET);
				}
			}
			else // no current, idle period
			{
				if(current_seconds - drop_charge_period_start >= DROP_CHARGE_iDLE_PERIOD) // it's time to switch current on
				{
					drop_charge_period_start = current_seconds;
					drop_charge_current_on = 1;
					// switch on
					HAL_GPIO_WritePin(GPIOB, ch_out_Pin, GPIO_PIN_SET);
				}
			}

		}
		//*********************************************************************************************


		//*********************************************************************************************
		if(battery_state == DISCHARGING_STATE)
		{
			// check discharge cancel voltage criterion
			if(battery_voltage_get() <= DISCHARGE_CRITICAL_VOLTAGE)
			{
				// turn off discharge
				switch_discharge_off();
			}
		}

		if(battery_state == CTC_DISCHARGING_STATE)
		{
			// check discharge cancel voltage criterion
			if(battery_voltage_get() <= DISCHARGE_CRITICAL_VOLTAGE)
			{
				// turn off discharge
				switch_discharge_off();
				battery_state_set(CTC_DISCHARGED_STATE);
				// save calculated discharge capacity counter
				discharge_capacity_set(get_discharge_cap_meter());
				// save discharge capacity in eeprom
				eeprom_write_mark();
				eeprom_write_discharge_capacity((int32_t)get_discharge_cap_meter());
				// calculate and set critical pumped in capacity threshold
				double recharge_value = 1.5 * discharge_capacity_get();
				set_critical_capacity_threshold((int32_t)recharge_value);
			}
		}


		/*
		if(battery_state == LOAD_STATE)
		{
			char message[64];
			sprintf((char *)message, "check discharge\r\n");
			HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);

			// check discharge cancel voltage criterion
			if(battery_voltage_get() <= DISCHARGE_CRITICAL_VOLTAGE)
			{
				// turn off load
				switch_load_off();
			}
		}
		*/

		if(battery_state == CTC_CHARGED_STATE)
		{

		}
	}
}


// returns 1 if some of criterions is valid, 0 otherwise
int charger_check_criterions()
{
	int stop_charge_flag = 0;

	// check temperature criterion
	int *temperature_buffer = battery_temperature_buffer_get();

	if (time_manager_get_seconds() >= 120) // check initial pause
	{
		// check critical temperature criterion
		if(temperature_buffer[2] >= CHARGE_CRITICAL_TEMPERATURE)
		{
			//debug
			sprintf((char *)charger_message, "STOP CHARGE (critical temperature) -> %7d\r\n", temperature_buffer[2]);
			HAL_UART_Transmit(&huart1, charger_message, strlen((const char *)charger_message), 500);

			// stop charge, switch to drop charging
			stop_charge_flag = 1;
		}
		else // no critical temperature
		{
			// check voltage threshold
			int32_t voltage = battery_voltage_get();
			if(voltage >= LOW_CHECK_CHARGE_VOLTAGE_THRESHOLD)
			{
				// check critical voltage criterion
				if (voltage > CHARGE_CRITICAL_VOLTAGE)
				{
					//debug
					sprintf((char *)charger_message, "STOP CHARGE (critical voltage) -> %7d\r\n", voltage);
					HAL_UART_Transmit(&huart1, charger_message, strlen((const char *)charger_message), 500);

					// stop charge, switch to drop charging
					stop_charge_flag = 1;
				}
				else // no critical voltage
				{
					// check temperature growth speed criterion
					if(
						(temperature_buffer[1] > temperature_buffer[0]) &&
						(temperature_buffer[2] > temperature_buffer[1]) &&
						((temperature_buffer[2] - temperature_buffer[0]) >= CHARGE_CRITICAL_TEMPERATURE_SPEED)
					  )
					{
						//debug
						sprintf((char *)charger_message, "STOP CHARGE (temperature speed) -> %7d %7d %7d\r\n", temperature_buffer[0], temperature_buffer[1], temperature_buffer[2]);
						HAL_UART_Transmit(&huart1, charger_message, strlen((const char *)charger_message), 500);

						// stop charge, switch to drop charging
						stop_charge_flag = 1;
					}
					else // no temperature growth
					{
						// check delta U criterion
						if(voltage >= voltage_local_max)
							voltage_local_max = voltage;
						if((voltage_local_max - voltage) >= VOLTAGE_DELTA_U)
						{
							//debug
							sprintf((char *)charger_message, "STOP CHARGE (delta U) -> %7d %7d\r\n", voltage_local_max, voltage);
							HAL_UART_Transmit(&huart1, charger_message, strlen((const char *)charger_message), 500);

							// stop charge, switch to drop charging
							stop_charge_flag = 1;
						}
						else // no critical delta U
						{
							// check pumped in capacity criterion
							double current_coulombmeter = coulombmeter_get();
							if(current_coulombmeter >= critical_capacity_threshold)
							{
								//debug
								sprintf((char *)charger_message, "STOP CHARGE (capacity) -> %7d %7d\r\n", (int32_t)current_coulombmeter, critical_capacity_threshold);
								HAL_UART_Transmit(&huart1, charger_message, strlen((const char *)charger_message), 500);

								// stop charge, switch to drop charging
								stop_charge_flag = 1;
							}
						}
					}
				}// end if (voltage > CHARGE_CRITICAL_VOLTAGE)
			}// end if(voltage >= LOW_CHECK_CHARGE_VOLTAGE_THRESHOLD)
		}// end else // no critical temperature

	}// end if (time_manager_get_seconds() >= 120) // check initial pause
	//*****************************************************

	return stop_charge_flag;
}

void reset_voltage_local_max()
{
	int32_t voltage = battery_voltage_get();
	voltage_local_max = voltage;
}


void set_critical_capacity_threshold(int32_t value)
{
	critical_capacity_threshold = value;
}
