/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery_control_task.h"

#include "tim.h"

extern TIM_HandleTypeDef htim2;

extern uint32_t global_debug_counter;
extern uint voltage;

extern uint64_t usec10tick;


void battery_control_task()
{
	// ***** read battery state *****


	//DEBUG!!!
	static uint64_t usec10tick_frozen;
	usec10tick_frozen = usec10tick;
	static uint32_t frozen_systick;
	uint32_t current_systick = HAL_GetTick();

	if(current_systick >= (frozen_systick + 1000))
	{
		frozen_systick = current_systick;
		//*
		// Disable SysTick Interrupt
		SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

		// Enable tim2 interrupt
		TIM2->DIER |= TIM_DIER_UIE;
		// start tim2
		HAL_TIM_Base_Start(&htim2);

		while((usec10tick - usec10tick_frozen) < 100){};

		// stop tim2
		HAL_TIM_Base_Stop(&htim2);
		// disable tim2 interrupt
		TIM2->DIER &= ~TIM_DIER_UIE;

		// Enable SysTick Interrupt
		SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

		global_debug_counter++;

		if(global_debug_counter % 2 == 0)
			voltage++;

		//*/
	}


}
