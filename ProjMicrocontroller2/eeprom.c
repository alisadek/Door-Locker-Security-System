/*******************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.c
 *
 * Created on: Jan 18, 2020
 *
 * Description: Source file for eeprom driver.
 *
 * Author: Ali Sadek
 *
 *******************************************************************/
#include "i2c.h"
#include "eeprom.h"



void EEPROM_init(const twi_config *i2c_config_ptr)
{
	/* just initialize the I2C(TWI) module inside the MC */
	TWI_Init(i2c_config_ptr);
}

void EEPROM_writeString(uint16 memLocation, const uint8 *Str)
{
	uint8 i=0;
	while(Str[i]!= '\0')
	{

		EEPROM_writeByte(memLocation, Str[i]);
		memLocation++;
		i++;
		_delay_ms(1000);
	}
	EEPROM_writeByte(memLocation, '\0');
		_delay_ms(1000);

}
void EEPROM_readString(uint16 memLocation, char *Str, uint8 strLength)
{
	uint8 i=0;
	while(i<5)
	{

		EEPROM_readByte(memLocation, &Str[i]);
		memLocation++;
		i++;
		_delay_ms(1000);
	}
}
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	TWI_Start();
	if (TWI_Get_Status() != TW_START)
		return ERROR;

	TWI_Write((uint8)((0xA0) | ((u16addr & 0x0700) >> 7)));
	if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address */
	TWI_Write((uint8)(u16addr));
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_Write(u8data);
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_Stop();
	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	TWI_Start();
	if (TWI_Get_Status() != TW_START)
		return ERROR;

	TWI_Write((uint8)((0xA0) |((u16addr & 0x0700) >> 7)));
	if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return ERROR;

	TWI_Write((uint8)(u16addr));
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_Start();
	if (TWI_Get_Status() != TW_REP_START)
		return ERROR;

	TWI_Write((uint8)((0xA1) |((u16addr & 0x0700) >> 7)));
	if (TWI_Get_Status() != TW_MT_SLA_R_ACK)
		return ERROR;

	*u8data = TWI_Read_With_NACK();
	if (TWI_Get_Status() != TW_MR_DATA_NACK)
		return ERROR;

	TWI_Stop();
	return SUCCESS;
}
