
/*=======Test Runner Used To Run Each Test Below=====*/
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}


/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

#include "i2c_lowlevel.h"
#include "charge_level_detector_obj.h"

#include "battery_measurement_task.h"
#include "time_management_task.h"
#include "message_interpreter_task.h"
#include "charger_obj.h"
#include "eeprom_storage_obj.h"

// here code to test
//#include "ProductionCode.h"

/* Private variables ---------------------------------------------------------*/

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
SPI_HandleTypeDef hspi1;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
// here are test functions
extern void test_some_function(void);


/*=======Test Reset Option=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


/* Private function prototypes -----------------------------------------------*/


int main(void)
{

    /* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	// enable spi1
	SPI1->CR1 |= SPI_CR1_SPE;
	// enable spi1 rxne interrupt
	SPI1->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
	//debug*********************
	SPI1->DR = 0xabcd;
	//debug*********************
	//MX_I2C1_Init();
	MX_USART1_UART_Init();
	MX_TIM2_Init();
	MX_TIM21_Init();
	MX_TIM22_Init();


    // here are tests
    //UnityBegin("test_code_template.c");
    //RUN_TEST(test_some_function, 15);

	// ***** EEPROM STORAGE MAP *****
	// base address 0x0808 0000
	// addr 0x0000 0000 priznak togo, chto v eeprom uzhe ran'she pisali kakie-to znacheniya (0x0123 4567)
	// addr 0x0000 0004 razryadnaya emkost' (zapisyvaetsya po okonchanii polnogo razryada)
	// addr 0x0000 0008 ostatochnaya emkost' (obnovlyaetsya raz v 10 minut)

	//eeprom_write_mark();
	//eeprom_mark = eeprom_read_mark();
	//eeprom_clear_mark();
	//eeprom_mark = eeprom_read_mark();

	// configure max
	write_configuration(0x2250);
	//HAL_Delay(7000);
	uint32_t eeprom_mark = eeprom_read_mark();
	if(eeprom_mark == EEPROM_MARK) // there are data in eeprom
	{
		// read discharge capacity
		discharge_capacity_set((double)eeprom_read_discharge_capacity());
		// read coulombmeter (remaining capacity)
		coulombmeter_set((double)eeprom_read_remaining_capacity());
	}
	else
	{
		initial_charge_level_estimation();
	}

	charge_level_detector_init();


    while(1)
    {
    	battery_measurement_task();
    	time_management_task();
    	message_interpreter_task();
    	charger_control_task();

    }
    //return (UnityEnd());
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
