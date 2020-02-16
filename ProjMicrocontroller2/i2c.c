/*******************************************************************
 *
 * Module: Two Wired Interface
 *
 * File Name: i2c.c
 *
 * Created on: Jan 18, 2020
 *
 * Description: Source file for i2c driver.
 *
 * Author: Ali Sadek
 *
 *******************************************************************/
#include "i2c.h"

void TWI_Init(const twi_config *config_ptr)
{
	TWBR = (config_ptr -> bitRate);
	TWSR = (config_ptr -> i2c_prescaler);
	TWAR = (config_ptr -> slave_address);
	TWCR = (1 << TWEN);
}

void TWI_Start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT)){};
}

void TWI_Stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_Write(uint8 data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_Read_With_ACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT)){};
	return TWDR;
}

uint8 TWI_Read_With_NACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT)){}
	return TWDR;
}

uint8 TWI_Get_Status(void)
{
	uint8 status;
	status = (TWSR & 0xF8);
	return status;
}
