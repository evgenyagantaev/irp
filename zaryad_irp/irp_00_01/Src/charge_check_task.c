/*
 * charge_check_task.c
 *
 *  Created on: Jul 5, 2022
 *      Author: agant
 */


extern int express_charging;
extern uint32_t seconds_tick;
extern uint battery_type;

void charge_check_task()
{
	static int expr_charging_started = 0;

	static express_charging_start_moment = 0;

	if(express_charging)
	{
		if(!expr_charging_started)
		{
			expr_charging_started = 1;

			// start express charging
			if(battery_type == 21)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin, GPIO_PIN_SET);
			}
			else if(battery_type == 42)
			{
				HAL_GPIO_WritePin(GPIOB, express_charge1_Pin | express_charge2_Pin, GPIO_PIN_SET);
			}

			express_charging_start_moment = seconds_tick;
		}
		else // started yet
		{

		}
	}
}
