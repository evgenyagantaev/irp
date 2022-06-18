/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery_control_task.h"

#include "tim.h"

extern TIM_HandleTypeDef htim2;


void battery_control_task()
{
	// ***** read battery state *****

	/* Disable SysTick Interrupt */
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

	// Enable tim2 interrupt
	TIM2->DIER |= TIM_DIER_UIE;
	// start tim2
	HAL_TIM_Base_Start(&htim2);



	// stop tim2
	HAL_TIM_Base_Stop(&htim2);
	// disable tim2 interrupt
	TIM2->DIER &= ~TIM_DIER_UIE;

	/* Enable SysTick Interrupt */
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}
