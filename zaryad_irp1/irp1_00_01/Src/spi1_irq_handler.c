/*
 * spi1_irq_handler.c
 *
 *  Created on: Aug 26, 2016
 *      Author: root
 */

#include "battery_obj.h"
#include "charge_level_detector_obj.h"
#include "spi1_irq_handler.h"
#include "message_queue.h"
#include "eeprom_storage_obj.h"

#include "usart.h"
#include <stdio.h>
#include <string.h>

//debug
static int counter = 0;
extern UART_HandleTypeDef huart1;
static uint32_t data_to_send;


void SPI1_IRQHandler(void)
{
	char message[64];
	int i;

	uint16_t spi1_in_data;
	uint16_t spi1_out_buffer;
	uint16_t in_data;
	uint16_t out_buffer;
	uint32_t data = 0xaabbccdd;

	if((SPI1->SR & SPI_SR_RXNE) != 0)
	{
		// disable spi1 rxne interrupt
		//SPI1->CR2 &= ~SPI_CR2_RXNEIE;   // disable rxne interrupt
		// stop systick timer
		//SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk;

		// read from spi data register
		spi1_in_data = SPI1->DR;
		uint16_t message = spi1_in_data;

		// parse command **********************************************
		if(message == COMMAND_GET_VOLTAGE) // get battery voltage
		{
			spi1_send_data(battery_voltage_get());
		}
		else if(message == COMMAND_GET_CURRENT) // get battery current
		{
			spi1_send_data(battery_current_get());
		}
		else if(message == COMMAND_GET_TEMPERATURE) // get battery temperature
		{
			spi1_send_data(battery_temperature_get());
		}
		else if(message == COMMAND_GET_CHARGE_LEVEL) // get charge level (msb)
		{
			data_to_send = charge_level_get();
			SPI1->DR = (uint16_t)(data_to_send >> 16);
		}
		else if(message == COMMAND_GET_BATTERY_STATE) // get battery state (msb)
		{
			data_to_send = battery_state_get();
			SPI1->DR = (uint16_t)(data_to_send >> 16);
		}
		else if(message == COMMAND_LOAD_ON) // get battery state (msb)
		{
			HAL_GPIO_WritePin(GPIOA, on_bat2_out_Pin, GPIO_PIN_SET);
			drop_message_queue();
			message_push((uint8_t)spi1_in_data);
		}
		else if(message == COMMAND_CLEAN_EEPROM) //
		{
			eeprom_clear_mark();
		}
		else if(message == 0x5555) // lsb
		{
			SPI1->DR = (uint16_t)(data_to_send);
		}
		else if(message == 0x5757) // quote
		{
			SPI1->DR = 0x0022;
		}
		else
			message_push((uint8_t)spi1_in_data);


		//debug
		counter++;
		//sprintf(message, "%d: spi data = 0x%x\r\n", counter, spi1_in_data);
		//HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);



		// enable spi1 rxne interrupt
		//SPI1->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
		// start systick timer
		//SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk;
	}
}
