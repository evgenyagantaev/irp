/*
 * eeprom_storage_obj.h
 *
 *  Created on: Nov 6, 2016
 *      Author: root
 */

#ifndef INC_EEPROM_STORAGE_OBJ_H_
#define INC_EEPROM_STORAGE_OBJ_H_

#include "stdint.h"


#define EEPROM_MARK 0x12345678
#define EEPROM_BASE_ADDRESS 0x08080000
#define EEPROM_MARK_ADDRESS 0x08080000
#define EEPROM_DISCHCAP_ADDRESS 0x08080004
#define EEPROM_REMCAP_ADDRESS 0x08080008

#define EEPROM_DEFAULT_DISCHCAP 12000
#define EEPROM_DEFAULT_REMCAP 12000

// ***** EEPROM STORAGE MAP *****

// base address 0x0808 0000
// addr 0x0000 0000 priznak togo, chto v eeprom uzhe ran'she pisali kakie-to znacheniya (0x0123 4567)
// addr 0x0000 0004 razryadnaya emkost' (zapisyvaetsya po okonchanii polnogo razryada)
// addr 0x0000 0008 ostatochnaya emkost' (obnovlyaetsya raz v 10 minut)


void eeprom_write_mark();
void eeprom_clear_mark();
uint32_t eeprom_read_mark();
void eeprom_write_discharge_capacity(uint32_t discharge_capaciy);
uint32_t eeprom_read_discharge_capacity();
void eeprom_write_remaining_capacity(uint32_t remaining_capaciy);
uint32_t eeprom_read_remaining_capacity();


#endif /* INC_EEPROM_STORAGE_OBJ_H_ */
