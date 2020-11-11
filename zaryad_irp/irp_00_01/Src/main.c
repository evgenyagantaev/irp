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



// here code to test
//#include "ProductionCode.h"

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;

int ctc_on_flag = 0;
int ctc_button_press_counter = 0;

//int onbat2_on_off = 0;

extern ADC_HandleTypeDef hadc;

#define GET_CHARGE 0x0021
#define STOP_CHARGING 0x0022
#define GET_STATE 0x0023
#define START_CHARGING 0x0025

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
    MX_LPUART1_UART_Init();
    MX_USART1_UART_Init();
    MX_SPI2_Init();
    // enable spi2
    SPI2->CR1 |= SPI_CR1_SPE;
    MX_ADC_Init();
    MX_TIM2_Init();
    MX_TIM21_Init();
    MX_TIM22_Init();



    //power_led_red_out_Pin|power_led_green_out_Pin|charge_led_red_out_Pin|chargeOK_led_green_out_Pin
    //                          |ctc_led_red_out_Pin|ctc_led_green_out_Pin|charge100_led_green_out_Pin|charge75_led_green_out_Pin
    //                          |charge50_led_green_out_Pin|charge25_led_green_out_Pin

	// vkluchenie **********************************
    HAL_Delay(1000);
    //HAL_GPIO_WritePin(GPIOB, relei_control_out_Pin, GPIO_PIN_SET); // relei on
    test_leds();
    // check if button is pressed
    if(HAL_GPIO_ReadPin(ctc_onoff_button_exti15_GPIO_Port, ctc_onoff_button_exti15_Pin) == GPIO_PIN_RESET)
    {
    	HAL_UART_Transmit(&huart1, (uint8_t *)"Button pressed!\r\n", strlen("Button pressed!\r\n"), 500);
    	HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, chargeOK_led_green_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, ctc_led_green_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, charge100_led_green_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, charge75_led_green_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, charge50_led_green_out_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, charge25_led_green_out_Pin, GPIO_PIN_SET);
		HAL_Delay(5000);
    	// clean eeprom
    	spi_pipe_send_command(COMMAND_CLEAN_EEPROM, 0);
		spi_pipe_send_command(COMMAND_CLEAN_EEPROM, 1);
		spi_pipe_send_command(COMMAND_CLEAN_EEPROM, 2);
		spi_pipe_send_command(COMMAND_CLEAN_EEPROM, 3);
		HAL_UART_Transmit(&huart1, (uint8_t *)"EEPROM clean!\r\n", strlen("EEPROM clean!\r\n"), 500);

		HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, chargeOK_led_green_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, ctc_led_green_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, charge100_led_green_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, charge75_led_green_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, charge50_led_green_out_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, charge25_led_green_out_Pin, GPIO_PIN_RESET);


    }
    HAL_Delay(2000);

    HAL_UART_Transmit(&huart1, (uint8_t *)"Hello!\r\n", strlen("Hello!\r\n"), 500);
    HAL_Delay(1000);

    //ADC_ChannelConfTypeDef sConfig;
    int i;
    for(i=0; i<10; i++)
    {
    	extpow_measure_voltage();
    	ext_pow_get_voltage();
    }

    // main scheduler loop
    while(1)
    {
		//*
    	ext_pow_control_task();
		time_management_task();
		button_polling_task();
		button_interpreter_task();
		charge_check_task();
		battery_control_task();
		ctc_controller_task();
		//*/

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
	HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, power_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge_led_red_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, chargeOK_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, chargeOK_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, ctc_led_red_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, ctc_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, ctc_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge100_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge100_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge75_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge75_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge50_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge50_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge25_led_green_out_Pin, GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOA, charge25_led_green_out_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
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
        	HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin|power_led_green_out_Pin|charge_led_red_out_Pin|chargeOK_led_green_out_Pin
        	                          |ctc_led_red_out_Pin|ctc_led_green_out_Pin|charge100_led_green_out_Pin|charge75_led_green_out_Pin
        	                          |charge50_led_green_out_Pin|charge25_led_green_out_Pin, GPIO_PIN_RESET);
        	long i, j;
        	for(i=0;i<500000;i++)
        		j = i;
        	HAL_GPIO_WritePin(GPIOA, power_led_red_out_Pin, GPIO_PIN_SET);
        	for(i=0;i<500000;i++)
        		j = i;
        	i = j;
        }

        HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

    }

}
