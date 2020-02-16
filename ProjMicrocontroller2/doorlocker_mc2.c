/******************************************************************************
 *
 * Module: Micro-Controller 2
 *
 * File Name: doorlocker_mc2.c
 *
 * Description: Source file for micro-controller 2 of Door Locker System
 *
 * Author: Ali Sadek
 *
 *******************************************************************************/
#define MAX_PASS_LENGTH 16
#include "doorlocker_mc2.h"

static char g_savedPass[MAX_PASS_LENGTH];
static uint8 passwordLength;


/******************************************************************************
 *
 * Function Name: storeNewPassword
 *
 * Function Prototype: void storeNewPassword(void);
 *
 * Description: This function is used to receive the new password from MC 1 and
 * store it in EEPROM.
 *
 *Arguments: None.
 *
 *******************************************************************************/
void storeNewPassword(void)
{
	UART_receiveString(g_savedPass);
	passwordLength = UART_receiveByte();

	EEPROM_writeString(PASS_STORE_LOCATION, g_savedPass);
	_delay_ms(1000);

	/*stores the length of the password in EEPROM to be retrieved the next time*/
	EEPROM_writeByte(PASS_LENGTH_LOCATION, passwordLength);
	_delay_ms(1000);

	/******************************************************************************
	 * stores a byte in EEPROM to tell the MC next time that a pw is already stored
	 *
	 * the value of PASS_EXISTS can be changed to start from first stage if needed
	 * ***************************************************************************/
	EEPROM_writeByte(PASS_CHECK_LOCATION, PASS_EXISTS);
	_delay_ms(1000);
}

/******************************************************************************
 *
 * Function Name: main
 *
 * Function Prototype: int main (void)
 *
 * Description: the main function of micro-controller2 of the door locker
 *
 *It Initializes the UART and EEPROM.
 *
 *It looks for a byte in EEPROM to know if there's a stored password
 *
 * If a pass is stored, it sends a byte to MC1 confirming that a pw is stored
 * in EEPROM.
 *
 * In case of first time, it sends a byte to MC1 to take a new Password from user
 *
 *
 * Arguments: None
 *
 *******************************************************************************/
int main (void)
{
	uint8 passExistsFlag=0;

	UART_init();
	twi_config TWI_Configuration = {0x02, 0b00000010, TWI_PRESCALER_1};
	EEPROM_init(&TWI_Configuration);

	EEPROM_readByte(PASS_CHECK_LOCATION, &passExistsFlag); /*checks if a password is stored*/
	_delay_ms(1000);
	UART_sendByte(M2_READY); /*syncs UART with MC1*/
	if(passExistsFlag != PASS_EXISTS)
	{
		UART_sendByte(FIRST_TIME);
		storeNewPassword();
	}
	else
	{
		UART_sendByte(NOT_FIRST_TIME);
		EEPROM_readByte(PASS_LENGTH_LOCATION, &passwordLength);
		_delay_ms(1000);

		UART_sendByte(passwordLength);
		EEPROM_readString(PASS_STORE_LOCATION, g_savedPass, passwordLength);
		_delay_ms(1000);

		g_savedPass[passwordLength] = '#'; /* adds "#" to the end of string to be able to send through UART*/
		UART_sendString(g_savedPass);
	}




	while(1)
	{
		uint8 stage =0;
		stage=UART_receiveByte();

		/*checks if user tries to change password on second Micro-controller to store it in EEPROM*/
		if (stage == CHANGE_PASS)
		{
			storeNewPassword();
		}
	}

}
