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

extern uint8_t battery_address;
extern int read_battery_flag;
extern int new_battery_data_available;
extern uint16_t battery_value;


void battery_control_task()
{

	uint counter = 0;
	while(1)
	{
		if (read_battery_flag)
		{
			// drop flag;
			//read_battery_flag = 0;

			// ***** read battery state *****

			// Disable SysTick Interrupt
			SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

			// Enable tim2 interrupt
			TIM2->DIER |= TIM_DIER_UIE;
			// start tim2
			HAL_TIM_Base_Start(&htim2);

			uint64_t usec10tick_gross_timeout_frozen = usec10tick;
			int not_read_battery_data_yet = 1;

			uint8_t saved_lsb_value = 0xff;
			uint lsb_read_aatempts_counter = 0;

			while (not_read_battery_data_yet && ((usec10tick - usec10tick_gross_timeout_frozen) < 500000)) // 5 sec timeout
			{
				lsb_read_aatempts_counter++;

				send_brake();
				send_restore();
				//send_byte(0x14);

				//>>>>> send command
				uint8_t aux = battery_address;

				for(int i=0; i<8; i++)
				{
					if((aux & (uint8_t)1) == 0)
					{
						GPIOB->BRR = bat_data_out_Pin;
						uint64_t usec10tick_frozen = usec10tick;
						while((usec10tick - usec10tick_frozen) < 13){};
						GPIOB->BSRR = bat_data_out_Pin;
						if(i<7)
							while((usec10tick - usec10tick_frozen) < 20){};
					}
					else
					{
						GPIOB->BRR = bat_data_out_Pin;
						uint64_t usec10tick_frozen = usec10tick;
						while((usec10tick - usec10tick_frozen) < 3){};
						GPIOB->BSRR = bat_data_out_Pin;
						if(i<7)
							while((usec10tick - usec10tick_frozen) < 20){};
					}

					aux =  aux >> 1;
				}
				// command sent <<<<<

				//uint16_t data = receive_word();


				aux = 1;
				uint8_t data = 0xff;

				//*
				int index = 0;
				int no_timeout = 1;
				while((index < 8) && (no_timeout))
				{
					uint64_t usec10tick_frozen = usec10tick;
					// wait for low level
					while(((GPIOB->IDR & bat_data_out_Pin) != (uint32_t)GPIO_PIN_RESET) && (no_timeout))
					{
						if((usec10tick - usec10tick_frozen) > 23)
							no_timeout = 0;
					}


					if (no_timeout)
					{
						usec10tick_frozen = usec10tick;
						//wait for high level
						while(((GPIOB->IDR & bat_data_out_Pin) == (uint32_t)GPIO_PIN_RESET) && (no_timeout))
						{
							if((usec10tick - usec10tick_frozen) > 23)
								no_timeout = 0;
						}


						if (no_timeout)
						{
							uint64_t duration = usec10tick - usec10tick_frozen;

							if(duration <= 8)  // received 1
							{
								data += aux;
							}
							aux = aux << 1;

							index++;
						}
						else
							data = 0xff;
					}
					else
						data = 0xff;
				}
				//*/

				if(saved_lsb_value != 0xff)
				{
					if(saved_lsb_value == data)
						not_read_battery_data_yet = 0;
				}

				saved_lsb_value = data;

				// rise bat_data_out_Pin
				GPIOB->BSRR = bat_data_out_Pin;

				uint64_t usec10tick_frozen = usec10tick;
				// wait 1 msec
					while((usec10tick - usec10tick_frozen) < 100){};

			}// end while (not_read_battery_data_yet && ((usec10tick - usec10tick_gross_timeout_frozen) < 500000))

			if(not_read_battery_data_yet) // timeout occur
			{
				battery_value = 0xffff;
			}
			else
			{
				/*
				///////////////////////// SECOND (MSB) BYTE read
				uint64_t usec10tick_gross_timeout_frozen = usec10tick;
				int not_read_battery_data_yet = 1;

				uint8_t saved_msb_value = 0xff;

				while (not_read_battery_data_yet && ((usec10tick - usec10tick_gross_timeout_frozen) < 500000)) // 5 sec timeout
				{

					send_brake();
					send_restore();
					//send_byte(0x14);

					uint8_t aux = battery_address + 1;

					for(int i=0; i<8; i++)
					{
						if((aux & (uint8_t)1) == 0)
						{
							GPIOB->BRR = bat_data_out_Pin;
							uint64_t usec10tick_frozen = usec10tick;
							while((usec10tick - usec10tick_frozen) < 13){};
							GPIOB->BSRR = bat_data_out_Pin;
							if(i<7)
								while((usec10tick - usec10tick_frozen) < 20){};
						}
						else
						{
							GPIOB->BRR = bat_data_out_Pin;
							uint64_t usec10tick_frozen = usec10tick;
							while((usec10tick - usec10tick_frozen) < 3){};
							GPIOB->BSRR = bat_data_out_Pin;
							if(i<7)
								while((usec10tick - usec10tick_frozen) < 20){};
						}

						aux =  aux >> 1;
					}

					//uint16_t data = receive_word();


					aux = 1;
					uint8_t data = 0;

					//*
					int index = 0;
					int no_timeout = 1;
					while((index < 8) && (no_timeout))
					{
						uint64_t usec10tick_frozen = usec10tick;
						// wait for low level
						while(((GPIOB->IDR & bat_data_out_Pin) != (uint32_t)GPIO_PIN_RESET) && (no_timeout))
						{
							if((usec10tick - usec10tick_frozen) > 23)
								no_timeout = 0;
						}


						if (no_timeout)
						{
							usec10tick_frozen = usec10tick;
							//wait for high level
							while(((GPIOB->IDR & bat_data_out_Pin) == (uint32_t)GPIO_PIN_RESET) && (no_timeout))
							{
								if((usec10tick - usec10tick_frozen) > 23)
									no_timeout = 0;
							}


							if (no_timeout)
							{
								uint64_t duration = usec10tick - usec10tick_frozen;

								if(duration <= 8)  // received 1
								{
									data += aux;
								}
								aux = aux << 1;

								index++;
							}
							else
								data = 0xff;
						}
						else
							data = 0xff;
					}


					if(saved_msb_value != 0xff)
					{
						if(saved_msb_value == data)
							not_read_battery_data_yet = 0;
					}

					saved_msb_value = data;

					// rise bat_data_out_Pin
					GPIOB->BSRR = bat_data_out_Pin;

					uint64_t usec10tick_frozen = usec10tick;
					// wait 1 msec
						while((usec10tick - usec10tick_frozen) < 100){};

				}// end while (not_read_battery_data_yet && ((usec10tick - usec10tick_gross_timeout_frozen) < 500000))

				if(not_read_battery_data_yet) // timeout occur
				{
					battery_value = 0xffff;
				}
				else
				{
					battery_value = (((uint16_t)saved_msb_value) << 8) + saved_lsb_value;
				}
				//*/

				///////////////////////// SECOND (MSB) BYTE read <<<<<

			}// end (not_read_battery_data_yet) // timeout occur

			new_battery_data_available = 1;

			counter++;

			// stop tim2
			HAL_TIM_Base_Stop(&htim2);
			// disable tim2 interrupt
			TIM2->DIER &= ~TIM_DIER_UIE;

			// Enable SysTick Interrupt
			SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;


		}// end if (read_battery_flag)

	}// end while(1)


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
