/*******************************************************************
 *
 * Module: EEPROM
 *
 * File Name: eeprom.h
 *
 * Created on: Jan 18, 2020
 *
 * Description: Header file for eeprom driver.
 *
 * Author: Ali Sadek
 *
 *******************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"

#define ERROR 0
#define SUCCESS 1

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);
void EEPROM_init(const twi_config *i2c_config_ptr);
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);
void EEPROM_writeString(uint16 memLocation, const uint8 *Str);
void EEPROM_readString(uint16 memLocation, char *Str, uint8 strLength);

#endif /* EEPROM_H_ */
