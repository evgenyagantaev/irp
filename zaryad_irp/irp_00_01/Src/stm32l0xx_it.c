/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"

/* External variables --------------------------------------------------------*/

extern TIM_HandleTypeDef htim2;

extern uint32_t global_debug_counter;
extern uint voltage;

extern uint64_t usec10tick;

/******************************************************************************/
/*            Cortex-M0+ Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

//EXTI4_15_IRQHandler

void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_EXTI_Callback(ctc_onoff_button_exti15_Pin);
}


void TIM2_IRQHandler(void)
{
	// clear it
	(&htim2)->Instance->SR = ~TIM_IT_UPDATE;

	usec10tick++;

	/*
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();

	counter++;

	if(counter % 1000 == 0)
	{
		voltage++;
	}
	*/
}
