/******************************************************************************
 *
 * Module: Micro-Controller 2
 *
 * File Name: doorlocker_mc2.h
 *
 * Description: Header file for Micro-controller 2 of Door Locker System
 *
 * Author: Ali Sadek
 *
 *******************************************************************************/


#ifndef DOORLOCKER_MC2_H_
#define DOORLOCKER_MC2_H_

/*******************************************************************************
 *                      Included Files                                         *
 *******************************************************************************/
#include "i2c.h"
#include "uart.h"
#include "lcd.h"
#include <string.h>
#include "eeprom.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/


/*Used to confirm that UART is Ready*/
#define M2_READY 0x10

/*Stage Check Bytes*/
#define FIRST_TIME 0x12
#define NOT_FIRST_TIME 0x11

/*EEPROM storage locations*/

#define PASS_STORE_LOCATION 0x0004
#define PASS_CHECK_LOCATION 0x0019
#define PASS_LENGTH_LOCATION 0x0030

/*Used to check if a pass already exists, can be changed to start from stage 1 if needed */
#define PASS_EXISTS 0x12

/*Sent by MC1 when a new password is set and should be stored in EEPROM*/
#define CHANGE_PASS 0x77

#endif /* DOORLOCKER_MC2_H_ */
