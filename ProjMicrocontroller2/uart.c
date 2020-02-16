/***********************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Created on: Jan 18, 2020
 *
 * Description: Source file for UART driver.
 *
 * Author: Ali Sadek
 *
 ***********************************************************/


#include "uart.h"

void UART_init(void)
{
	/* U2X = 1 - Double the USART transmission speed*/
	SET_BIT(UCSRA, U2X);

	/* Enable The receiver and transmitter */
	UCSRB = (1 << RXEN) | (1 << TXEN);

	/* UCSZ0 =1 and UCSZ1 =1 UCSZ2 =0 - 8-bit (character size) in a frame */
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);

	UBRRH= 0;

	/* UBBRL=13 for 9600kb/s Baud Rate */
	UBRRL = 103;

}

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
void UART_sendByte(uint8 a_data)
{
	while (BIT_IS_CLEAR(UCSRA, UDRE)){}
	UDR = a_data;
}

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
char UART_receiveByte(void)
{
	while (BIT_IS_CLEAR(UCSRA, RXC)){};
	return UDR;
}

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
void UART_sendString(const char *a_Str)
{
	uint8 i = 0;
	while(a_Str[i] != '\0')
	{
		UART_sendByte(a_Str[i]);
		i++;
	}
}

void UART_receiveString(char *Str)
{
	uint8 i = 0;
	Str[i] = UART_receiveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}
	Str[i] = '\0';
}
