#include "i2c_lowlevel.h"
#include "gpio.h"

static inline void pause_1250_usec(void)
{
	volatile int i;
	for(i=0; i<2800; i++);
}

static inline void pause_250_usec(void)
{
	volatile int i;
	for(i=0; i<560; i++);
}

static inline void pause_1000_usec(void)
{
	pause_250_usec();
	pause_250_usec();
	pause_250_usec();
	pause_250_usec();
}

static inline void pause_2000_usec(void)
{
	pause_1000_usec();
	pause_1000_usec();
}



static inline void i2c_scl_low()
{
	GPIOB->BRR = GPIO_PIN_6;
}

static inline void i2c_scl_high()
{
	GPIOB->BSRR = GPIO_PIN_6;
}

static inline void i2c_sda_low()
{
	GPIOB->BRR = GPIO_PIN_7;
}

static inline void i2c_sda_high()
{
	GPIOB->BSRR = GPIO_PIN_7;
}

void i2c_clock_period()
{
	i2c_scl_low();
	pause_2000_usec();
	i2c_scl_high();
	pause_2000_usec();
}

static inline void i2c_send_START(void)
{
	pause_1000_usec();
	i2c_sda_low();
	pause_1000_usec();
}

static inline void i2c_send_START_REPEAT(void)
{
	i2c_sda_high();
	pause_1000_usec();
	i2c_scl_high();
	pause_1000_usec();
	i2c_sda_low();
	pause_1000_usec();
}

// returns 1 if ack and 0 if nack
uint8_t i2c_send_byte(uint8_t byte_to_send)
{
	uint8_t shift_register = byte_to_send;
	const uint8_t mask = 0x80;   // 1000 0000

	int i;
	for(i=0; i<8; i++)
	{
		if(shift_register & mask) // send 1
		{
			i2c_scl_low();
			pause_1000_usec();
			i2c_sda_high();
			pause_1000_usec();
			i2c_scl_high();
			pause_2000_usec();
		}
		else // send 0
		{
			i2c_scl_low();
			pause_1000_usec();
			i2c_sda_low();
			pause_1000_usec();
			i2c_scl_high();
			pause_2000_usec();
		}

		shift_register <<= 1;
	}
	uint8_t ack_nack = i2c_wait_ACK_NACK();

	return ack_nack;
}

// returns 1 if ack and 0 if nack
uint8_t i2c_wait_ACK_NACK(void)
{
	uint8_t return_value;
	GPIO_InitTypeDef GPIO_InitStruct;

	i2c_scl_low();
	i2c_sda_high();
	pause_2000_usec();
	i2c_scl_high();

	// read sda pin state
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) == GPIO_PIN_RESET) // ack detected
		return_value = 1; // ack
	else
		return_value = 0; // nack
	pause_1000_usec();
	pause_1000_usec();
	i2c_scl_low();
	i2c_sda_low();
	pause_2000_usec();
	// sda low, scl low, ready for STOP signal (make scl high then pause then sda high)

	return return_value;

}

static inline void i2c_send_STOP(void)
{
	i2c_scl_high();
	pause_1000_usec();
	i2c_sda_high();
	pause_1000_usec();

	// i2c bus returned in idle state
}

// parameter 1: 0 if we want nack, 1 if we want ack
uint8_t i2c_receive_byte(uint8_t *byte_to_save_in, uint8_t ack_nack)
{
	uint8_t return_value = 0;
	GPIO_InitTypeDef GPIO_InitStruct;

	i2c_scl_low();
	pause_1000_usec();
	i2c_sda_high();
	pause_1000_usec();
	int i;
	for(i=0; i<8; i++)
	{
		i2c_scl_high();
		pause_1000_usec();
		return_value <<= 1;
		//read sda pin state
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) != GPIO_PIN_RESET) // 1 detected
			return_value +=1;
		pause_1000_usec();
		i2c_scl_low();
		pause_2000_usec();
	}

	if(ack_nack)
		i2c_send_ACK();
	else
		i2c_send_NACK();
	//i2c_send_STOP();

	*byte_to_save_in = return_value;

	return return_value;
}

static inline void i2c_send_ACK(void)
{
	i2c_sda_low();
	pause_1000_usec();
	i2c_scl_high();
	pause_2000_usec();
	i2c_scl_low();
	pause_2000_usec();
	// scl low, sda low, ready for STOP signal
}

static inline void i2c_send_NACK(void)
{
	i2c_sda_high();
	pause_250_usec();
	i2c_scl_high();
	pause_1250_usec();
	i2c_scl_low();
	pause_250_usec();
	i2c_sda_low();
	pause_1000_usec();
	// scl low, sda low, ready for STOP signal
}

uint16_t read_status()
{
	uint16_t return_value = 0;
	uint8_t data_l, data_h = 0;

	i2c_send_START();
	i2c_send_byte(max17047_address);  			// write command
	i2c_send_byte(0x04);						// register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();

	return_value = (((uint16_t)data_h)<<8) + data_l;
}

void test_slave_on_bus()
{
	uint16_t version;
	uint16_t configuration;
	uint16_t vbatt;
	int16_t current;
	int16_t temperature;

	uint8_t data_l, data_h;
	/*
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_STOP();
	//*/

	// read version (0x00ac)
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x21); //version register 0x21 contains 0xac
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	version = (((uint16_t)data_h)<<8) + (uint16_t)data_l;

	// read configuration
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x1d); //configuration register 0x1d
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	configuration = (((uint16_t)data_h)<<8) + (uint16_t)data_l;

	// read vbatt
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x09); //Vcell register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	vbatt = (((uint16_t)data_h)<<8) + (uint16_t)data_l;
	vbatt >>= 3;
	double Vcell = ((vbatt * 0.625) * 8.0)/1000.0;

	// read current
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x0a); //current register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	current = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Current = current;

	// read temperature
	i2c_send_START();
	i2c_send_byte(max17047_address);  	// write command
	i2c_send_byte(0x08); //temperature register
	i2c_send_STOP();
	i2c_send_START();
	i2c_send_byte(max17047_address + 0x01);  	// read command
	i2c_receive_byte(&data_l, 1); // ack
	i2c_receive_byte(&data_h, 0); // nack
	i2c_send_STOP();
	temperature = (int16_t)((((uint16_t)data_h)<<8) + (uint16_t)data_l);
	double Temperature = temperature * 0.0039;




}










