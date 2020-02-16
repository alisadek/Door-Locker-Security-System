/*******************************************************************
 *
 * Module: Two Wired Interface
 *
 * File Name: i2c.h
 *
 * Created on: Jan 18, 2020
 *
 * Description: Header file for i2c driver.
 *
 * Author: Ali Sadek
 *
 *******************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"


#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave



typedef enum
{
	TWI_PRESCALER_1, TWI_PRESCALER_4, TWI_PRESCALER_16, TWI_PRESCALER_64
}twi_prescaler;

typedef struct
{
	uint8 bitRate;
	uint8 slave_address;
	twi_prescaler i2c_prescaler;
}twi_config;

uint8 TWI_Get_Status(void);
uint8 TWI_Read_With_ACK(void);
uint8 TWI_Read_With_NACK(void);
void TWI_Write(uint8 data);
void TWI_Stop(void);
void TWI_Start(void);
void TWI_Init(const twi_config *config_ptr);


#endif /* I2C_H_ */
