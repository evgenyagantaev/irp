/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "adc.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

#include "spi_pipe.h"
#include "ext_power_obj.h"
#include "seven_segment_display.h"



/* Private variables ---------------------------------------------------------*/

uint8_t battery_address = 14;

extern UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;

#define VERSION "0.0.6"

extern ADC_HandleTypeDef hadc;

uint32_t global_debug_counter = 0;
uint voltage = 0;

uint64_t usec10tick = 0;


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void test_leds(void);


/* Private function prototypes -----------------------------------------------*/


int main(void)
{
    //const uint16_t cs_pin[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};

    //char message[128];

    /* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    //MX_LPUART1_UART_Init();
    //MX_USART1_UART_Init();
    //MX_SPI2_Init();
    // enable spi2
    //SPI2->CR1 |= SPI_CR1_SPE;
    //MX_ADC_Init();
    MX_TIM2_Init();
    //MX_TIM21_Init();
    //MX_TIM22_Init();



    HAL_Delay(1000);
    test_leds();


    /* Disable SysTick Interrupt */
	//SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

	// Enable tim2 interrupt
	//TIM2->DIER |= TIM_DIER_UIE;
	// start tim2
	//HAL_TIM_Base_Start(&htim2);


    // main scheduler loop
    while(1)
    {

    	//ext_pow_control_task();
		time_management_task();
		//button_polling_task();
		//button_interpreter_task();
		//charge_check_task();
		battery_control_task();
		//ctc_controller_task();
		seven_segment_display(voltage);

        //int_adc_measure_task();

    }


}
/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_LPUART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


void test_leds(void)
{
	const int DELAY = 150;
	//while(1)
	{


		//*
		HAL_GPIO_WritePin(GPIOA, SVD3_6_catode_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin|ind_7_seg_2_Pin|ind_7_seg_4_Pin|ind_7_seg_8_Pin, GPIO_PIN_SET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin|ind_7_seg_2_Pin|ind_7_seg_4_Pin|ind_7_seg_8_Pin, GPIO_PIN_SET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, SVD3_6_catode_Pin, GPIO_PIN_RESET);



		HAL_GPIO_WritePin(GPIOA, SVD2_5_catode_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin|ind_7_seg_2_Pin|ind_7_seg_4_Pin|ind_7_seg_8_Pin, GPIO_PIN_SET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin|ind_7_seg_2_Pin|ind_7_seg_4_Pin|ind_7_seg_8_Pin, GPIO_PIN_SET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, SVD2_5_catode_Pin, GPIO_PIN_RESET);


		HAL_GPIO_WritePin(GPIOA, SVD1_4_catode_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin|ind_7_seg_2_Pin|ind_7_seg_4_Pin|ind_7_seg_8_Pin, GPIO_PIN_SET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_RESET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin|ind_7_seg_2_Pin|ind_7_seg_4_Pin|ind_7_seg_8_Pin, GPIO_PIN_SET);
		HAL_Delay(DELAY);
		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_RESET);

		HAL_GPIO_WritePin(GPIOA, SVD1_4_catode_Pin, GPIO_PIN_RESET);
		//*/

		HAL_GPIO_WritePin(GPIOA, SVD3_6_catode_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SVD2_5_catode_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SVD1_4_catode_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SVD123_anodes_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, SVD456_anodes_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ind_7_seg_8_Pin, GPIO_PIN_SET);

	}


}


/**
  * @brief EXTI line detection callback.
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //static int odd_even = 0;

    if(GPIO_Pin == ctc_onoff_button_exti15_Pin)
    {
        HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);

        while(HAL_GPIO_ReadPin(GPIOA, ctc_onoff_button_exti15_Pin) == GPIO_PIN_RESET)
        {
        	//...
        }

        HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

    }

}
