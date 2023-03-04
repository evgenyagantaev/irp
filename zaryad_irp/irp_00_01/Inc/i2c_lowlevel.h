#ifndef INC_I2C_LOWLEVEL_H_
#define INC_I2C_LOWLEVEL_H_

#include "stdint.h"

#define max17047_address  0x6c //0110110 << 1

int i2c_configuration(void);

//*
void pause_1250_usec(void);
void pause_250_usec(void);

void i2c_scl_low();
void i2c_scl_high();
void i2c_sda_low();
void i2c_sda_high();



void i2c_send_START(void);
void i2c_send_STOP(void);

void i2c_send_ACK(void);
void i2c_send_NACK(void);

uint8_t i2c_wait_ACK_NACK(void);
//*/

void i2c_clock_period();

void write_configuration(uint16_t configuration);

uint8_t i2c_send_byte(uint8_t byte_to_send);
uint8_t i2c_receive_byte(uint8_t *byte_to_save_in, uint8_t ack_nack);

uint16_t read_status();
uint16_t read_device_type_bq27541();
float read_temperature_bq27541();
void test_slave_on_bus();

#endif /* INC_I2C_LOWLEVEL_H_ */
