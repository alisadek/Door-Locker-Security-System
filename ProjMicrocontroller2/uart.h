/*******************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Created on: Jan 18, 2020
 *
 * Description: Header file for UART driver.
 *
 * Author: Ali Sadek
 *
 *******************************************************************/



#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/******************************************************************************
 *
 * Function Name: receiveByte
 *
 * Function Prototype: char UART_receiveByte(void)
 *
 * Description: Function receives a byte through UART.
 *
 *Arguments: None
 *
 *Return type: char
 *Return : the value of UDR
 *
 *******************************************************************************/
char UART_receiveByte(void);

/******************************************************************************
 *
 * Function Name: sendByte
 *
 * Function Prototype: void UART_sendByte(uint8 data)
 *
 * Description: Function sends a byte through UART.
 *
 *Arguments:
 *uint8 a_data: contains the byte that will be sent.
 *
 *******************************************************************************/
void UART_sendByte(uint8 data);


void UART_init(void);
void UART_receiveString(char *Str);

/******************************************************************************
 *
 * Function Name: UART_sendString
 *
 * Function Prototype: void UART_sendString(const char *Str)
 *
 * Description: Sends a string through UART.
 *
 *Arguments: const char *a_Str
 *
 *
 *******************************************************************************/
void UART_sendString(const char *Str);

#endif /* UART_H_ */
