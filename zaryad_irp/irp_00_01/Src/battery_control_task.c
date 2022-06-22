/*
 * battery.c
 *
 *  Created on: Aug 24, 2016
 *      Author: root
 */

#include "battery_control_task.h"
#include "hdq_pipe.h"
#include "main.h"
#include "tim.h"

extern TIM_HandleTypeDef htim2;

extern uint32_t global_debug_counter;
extern uint voltage;

extern uint64_t usec10tick;


void battery_control_task()
{
	// ***** read battery state *****

	// Disable SysTick Interrupt
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

	// Enable tim2 interrupt
	TIM2->DIER |= TIM_DIER_UIE;
	// start tim2
	HAL_TIM_Base_Start(&htim2);


	while(1)
	{
		send_brake();
		send_restore();
		send_byte(0x14);

		//uint16_t data = receive_word();


		// rise bat_data_out_Pin
		GPIOB->BSRR = bat_data_out_Pin;

		uint64_t usec10tick_frozen = usec10tick;
		// wait 400 usec
		while((usec10tick - usec10tick_frozen) < 400){};


		/*
		send_brake();
		send_restore();
		send_byte(0x15);

		uint16_t aux = receive_word();

		data += (aux << 8);


		// rise bat_data_out_Pin
		GPIOB->BSRR = bat_data_out_Pin;
		usec10tick_frozen = usec10tick;
		// wait 400 usec
		while((usec10tick - usec10tick_frozen) < 40){};
		*/

	}


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

int hdq_wait_for_brake()
{
	// wait for low level
	while((GPIOB->IDR & bat_data_in_Pin) != (uint32_t)GPIO_PIN_RESET){};
	uint64_t usec10tick_frozen = usec10tick;
	//wait for high level
	while((GPIOB->IDR & bat_data_in_Pin) == (uint32_t)GPIO_PIN_RESET){};
	uint64_t duration = usec10tick - usec10tick_frozen;

	if(duration >= 19)
		return 0;
	else
		return -1;
}

uint8_t hdq_read_byte()
{
	while(!hdq_wait_for_brake()){};

	
}
