/*
 * eeprom_storage_obj.c
 *
 *  Created on: Nov 6, 2016
 *      Author: root
 */

#include "eeprom_storage_obj.h"
#include "stm32l0xx_hal.h"

#include "usart.h"
#include <stdio.h>
#include <string.h>

//debug


void eeprom_write_mark()
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_Erase(EEPROM_MARK_ADDRESS);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, EEPROM_MARK_ADDRESS, EEPROM_MARK);
	HAL_FLASHEx_DATAEEPROM_Lock();
}
void eeprom_clear_mark()
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_Erase(EEPROM_MARK_ADDRESS);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, EEPROM_MARK_ADDRESS, 0x00000000);
	HAL_FLASHEx_DATAEEPROM_Lock();
	HAL_UART_Transmit(&huart1, "EEPROM clean!\r\n", strlen("EEPROM clean!\r\n"), 500);
}
uint32_t eeprom_read_mark()
{
	uint32_t return_data = *((uint32_t *)0x08080000);
	//return *((uint32_t *)EEPROM_MARK_ADDRESS);
	return return_data;
}

void eeprom_write_discharge_capacity(int32_t discharge_capaciy)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_Erase(EEPROM_DISCHCAP_ADDRESS);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, EEPROM_DISCHCAP_ADDRESS, discharge_capaciy);
	HAL_FLASHEx_DATAEEPROM_Lock();
}
int32_t eeprom_read_discharge_capacity()
{
	return *(EEPROM_DISCHCAP_ADDRESS);
}
void eeprom_write_remaining_capacity(int32_t remaining_capaciy)
{
	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_Erase(EEPROM_REMCAP_ADDRESS);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, EEPROM_REMCAP_ADDRESS, remaining_capaciy);
	HAL_FLASHEx_DATAEEPROM_Lock();
}
int32_t eeprom_read_remaining_capacity()
{
	return *(EEPROM_REMCAP_ADDRESS);
}
