/* Includes ------------------------------------------------------------------*/
#define VERSION   "Version = 0.0.1"
int D_VERSION = 1;


#include "stm32l0xx_hal.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#include "main.h"



/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

int main(void)
{

    /* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    //MX_LPUART1_UART_Init();
    MX_USART1_UART_Init();
    //MX_SPI2_Init();
    // enable spi2
    //SPI2->CR1 |= SPI_CR1_SPE;
    //MX_ADC_Init();
    MX_TIM2_Init();
    //MX_TIM21_Init();
    //MX_TIM22_Init();



    HAL_Delay(1000);

    char message[64];

    sprintf((char *)message, "Hello! This is MKU Eureca;\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	sprintf((char *)message, VERSION);
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	sprintf((char *)message, ";\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);



    // main scheduler loop
    while(1)
    {
    	HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_RESET);
    	HAL_Delay(500);
    	HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_SET);
    	HAL_Delay(500);

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





/**
  * @brief EXTI line detection callback.
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //static int odd_even = 0;

	/*
    if(GPIO_Pin == ctc_onoff_button_exti15_Pin)
    {
        HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);

        while(HAL_GPIO_ReadPin(GPIOA, ctc_onoff_button_exti15_Pin) == GPIO_PIN_RESET)
        {
        	//...
        }

        HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

    }
    */

}
