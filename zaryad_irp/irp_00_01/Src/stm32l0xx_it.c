/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"

#include "stdio.h"
#include "string.h"

#include "usart.h"

/* External variables --------------------------------------------------------*/

extern TIM_HandleTypeDef htim2;

extern uint32_t global_debug_counter;
extern uint voltage;

extern uint64_t usec10tick;

extern int recycling_mode;
extern int recycling_length;
extern int recycling_hint;

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
	//HAL_GPIO_EXTI_Callback(ctc_onoff_button_exti15_Pin);
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

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
	uint32_t isrflags   = USART1->ISR;
	uint32_t cr1its     = USART1->CR1;
	uint32_t errorflags;

	static char buffer[64];
	static int index = 0;

	uint16_t usart_data;

	/* If no error occurs */
	errorflags = (isrflags & (uint32_t)(USART_ISR_PE | USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE));
	if (errorflags == RESET)
	{
		/* UART in mode Receiver ---------------------------------------------------*/
		 if (((isrflags & USART_ISR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
		{
			usart_data = (uint16_t) USART1->RDR;
			char last_received_simbol = (char)usart_data;
			buffer[index] = last_received_simbol;

			if(last_received_simbol == '\n' || last_received_simbol == '\r')
			{
				buffer[index + 1] = 0;
				index = 0;

				recycling_mode = 0;
				recycling_length = 0;
				recycling_hint = 0;
				sscanf(buffer, "%d %d %d\r\n", &recycling_mode, &recycling_length, &recycling_hint);
			}
			else
			{
				index++;
			}

		}
	}
	else // some errors
	{
		// clear error flags
		uint32_t aux;
		aux = USART1->ISR;
		aux = USART1->RDR;
		UNUSED(aux);
	}
}

