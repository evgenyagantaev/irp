/* Includes ------------------------------------------------------------------*/
#define VERSION   "Version = 1.1.4"


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

#define BQ27541_ADDRESS_WRITE 0xaa
#define BQ27541_ADDRESS_READ 0xab

extern I2C_HandleTypeDef hi2c1;

// global variables
volatile int do_loop = 1;
volatile int usart_new_char_received = 0;
volatile char new_char;

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
    //MX_I2C1_Init();



    HAL_Delay(100);

    char message[256];

    sprintf((char *)message, "MKU\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	sprintf((char *)message, VERSION);
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
	sprintf((char *)message, ";\r\n\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

	uint8_t multiplexors_addresses[] = {0xe0, 0xe8, 0xe2}; // 11100000, 11101000, 11100010
	uint8_t channel_indexes[] = {0x02, 0x03, 0x01, 0x00};
	uint8_t success[12];

	/*
	for(int i=0; i<2; i++)
	{
		HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
	//*/

	HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_SET);

	for(int i=0; i<4; i++)
	{
		uint8_t channel_select_value = 0x04 + channel_indexes[i];

		for(uint8_t j=0; j<3; j++)
		{
			uint8_t mult_address = multiplexors_addresses[j];

			uint8_t ack_nack;
			// reset bus
			i2c_send_STOP();
			i2c_send_START();
			ack_nack = i2c_send_byte(0xff);
			i2c_send_STOP();
			//**************
			// select multiplexor and channel
			i2c_send_START();
			ack_nack = i2c_send_byte(mult_address);							// 1
 			ack_nack = i2c_send_byte(channel_select_value);					// 1
			i2c_send_STOP();
			//************************************************

			HAL_Delay(30);

			sprintf((char *)message, "\r\n#%d--->\r\n", i * 3 + j + 1);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			sprintf((char *)message, "BEFORE...\r\n");
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			success[i * 3 + j] = 1;
			uint16_t dev_type = read_device_type_bq27541();
			if(dev_type != 0x541) success[i * 3 + j] = 0;
			sprintf((char *)message, "device type = 0x%x\r\n", dev_type);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			float temperature = read_temperature_bq27541();
			sprintf((char *)message, "temperature = %d\r\n", (int)temperature);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			uint16_t version = get_hw_version_bq27541();
			sprintf((char *)message, "hardware version = 0x%x\r\n", dev_type);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			HAL_GPIO_WritePin(GPIOA, program_led_Pin, GPIO_PIN_RESET);
			sprintf((char *)message, "PROGRAMMING...\r\n", dev_type);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			set_hdq_mode();

			/*
			do_loop = 1; // volatile
			int counter = 0;
			while(do_loop && counter < 1000)
			{
				counter++;
				ack_nack = i2c_send_byte(0x55);
			}
			//*/

			HAL_GPIO_WritePin(GPIOA, program_led_Pin, GPIO_PIN_SET);
			sprintf((char *)message, "AFTER...\r\n");
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

			dev_type = read_device_type_bq27541();
			if(dev_type == 0x541) success[i * 3 + j] = 0;
			sprintf((char *)message, "device type = 0x%x\r\n", dev_type);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			temperature = read_temperature_bq27541();
			sprintf((char *)message, "temperature = %d\r\n", (int)temperature);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			version = get_hw_version_bq27541();
			sprintf((char *)message, "hardware version = 0x%x\r\n\r\n", dev_type);
			//HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);


			// reset bus
			i2c_send_STOP();
			i2c_send_START();
			ack_nack = i2c_send_byte(0xff);
			i2c_send_STOP();
			//**************
			// deselect all channels
			i2c_send_START();
			ack_nack = i2c_send_byte(mult_address);
			ack_nack = i2c_send_byte(0x00);
			i2c_send_STOP();

		}
	}

	HAL_GPIO_WritePin(GPIOA, program_led_Pin|ok_led_Pin|error_led_Pin, GPIO_PIN_RESET);

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(success[i*3 + j])
			{
				sprintf((char *)message, "+++   ");
				HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			}
			else
			{
				sprintf((char *)message, "XXX   ");
				HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);
			}
		}
		sprintf((char *)message, "\r\n");
		HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

	}


	sprintf((char *)message, "\r\n\r\n*********************************************************************\r\n\r\n");
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen((const char *)message), 500);

	// main scheduler loop
	while(1)
	{

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
