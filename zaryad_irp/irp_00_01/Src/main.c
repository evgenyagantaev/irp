/* Includes ------------------------------------------------------------------*/
#define VERSION   "Version = 0.0.1"
int D_VERSION = 1;


#include "stm32l0xx_hal.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "i2c.h"
#include "i2c_lowlevel.h"

#include <setjmp.h>
#include <stdio.h>
#include <string.h>

#include "main.h"

#define CONTROL_CMD 0x00
#define SEALED_CMD 0x20
#define UNLOCK_CMD 0x22
#define WRITE_EXT_DATA_CMD 0x4A
#define DATA_BLOCK_CMD 0x40
#define LOCK_CMD 0x21
#define EXIT_CMD 0x02

extern I2C_HandleTypeDef hi2c1;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

// Send an I2C command to the bq27541
void bq27541_send_i2c_cmd(uint8_t cmd)
{
    // Wait for the I2C bus to be ready
    while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY);

    // Send the command over the I2C interface
    HAL_I2C_Master_Transmit(&hi2c1, 0x55, &cmd, 1, HAL_MAX_DELAY);
}

// Write data bytes to the EDB using the DataBlock() command
void bq27541_write_edb_data(uint8_t *data, uint8_t length)
{
    // Send the DataBlock() command with the appropriate length
    bq27541_send_i2c_cmd(DATA_BLOCK_CMD | length);

    // Write the data bytes to the EDB
    HAL_I2C_Master_Transmit(&hi2c1, 0x55, data, length, HAL_MAX_DELAY);
}

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
    //MX_I2C1_Init();



    HAL_Delay(1000);

    char message[64];

    sprintf((char *)message, "Hello! This is MKU Eureca;\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	sprintf((char *)message, VERSION);
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	sprintf((char *)message, ";\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

	// Put the bq27541 into Configuration mode
	bq27541_send_i2c_cmd(CONTROL_CMD);

	// Enter the Sealed state
	bq27541_send_i2c_cmd(SEALED_CMD);

	// Unlock the device
	bq27541_send_i2c_cmd(UNLOCK_CMD);

	// Write the HDQ configuration data to the EDB
	uint8_t hdq_data[] = {
	    0x00, 0x1C, 0x04, 0x0C, 0x00, 0x06, 0x00, 0x02,
	    0x3C, 0x40, 0x64, 0x07, 0x40, 0x07, 0x60, 0x05,
	    0x1E, 0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00,
	    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	bq27541_write_edb_data(hdq_data, sizeof(hdq_data));

	// Lock the device
	bq27541_send_i2c_cmd(LOCK_CMD);

	// Exit the Configuration mode
	bq27541_send_i2c_cmd(EXIT_CMD);

	// Switch the bq27541 to HDQ mode
	bq27541_send_i2c_cmd(WRITE_EXT_DATA_CMD);
	uint8_t hdq_mode[] = {0x02};  // HDQ mode enabled
	bq27541_write_edb_data(hdq_mode, sizeof(hdq_mode));

	// Put the bq27541 into Configuration mode again
	bq27541_send_i2c_cmd(CONTROL_CMD);

	// Enter the Sealed state
	bq27541_send_i2c_cmd(SEALED_CMD);

	// Lock the device
	bq27541_send_i2c_cmd(LOCK_CMD);

	// Exit the Configuration mode
	bq27541_send_i2c_cmd(EXIT_CMD);

    // main scheduler loop
    while(1)
    {
    	//HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_RESET);
    	//HAL_Delay(500);
    	//HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_SET);
    	//HAL_Delay(500);

    	uint8_t data = 0x55;

    	i2c_send_byte(data);

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
