/******************************************************************************
 *
 * Module: Micro-Controller 1
 *
 * File Name: doorlocker_mc1.c
 *
 * Description: Source file for micro-controller 1 of Door Locker System
 *
 * Author: Ali Sadek
 *
 *******************************************************************************/
#include "doorlocker_mc1.h"



static char key, g_enteredPass[MAXPASSLENGTH], g_reEnteredPass[MAXPASSLENGTH], g_savedPass[MAXPASSLENGTH];
static uint8 g_passLength, g_pass2Length;

/******************************************************************************
 *
 * Function Name: setPassword
 *
 * Function Prototype: void setPassword(void);
 *
 * Description: This function is used to set a new password, it takes in the input
 * from the user.
 *
 *******************************************************************************/

void setPassword(void)
{
	uint8 i=1;
	g_passLength=1;

	LCD_clearScreen();
	LCD_displayString("Enter New Pass");
	LCD_goToRowColumn(1,0);

	key=KeyPad_getPressedKey();
	_delay_ms(50);
	if(key>='0' && key <= '9')
	{
		LCD_displayCharacter('*');
		g_enteredPass[0] = key;
	}
	while (key>='0' && key <= '9')
	{
		key= KeyPad_getPressedKey();
		_delay_ms(50);
		LCD_displayCharacter('*');
		g_enteredPass[i] = key;
		i++;
		g_passLength++;
	}
	if(key == '=')
	{
		LCD_clearScreen();
		confirmSetPassword();
	}
}


/******************************************************************************
 *
 * Function Name: confirmSetPassword
 *
 * Function Prototype: void confirmSetPassword(void);
 *
 * Description: This function is used to verify the new password, it takes in the input
 * from the user and compares it to the previous input from (setPassword) function,
 * it stores the input in saved password and sends it to Micro-Controller 2 in case of
 * success, and allows user to retry for 2 more times in case of failure.
 *
 *******************************************************************************/

void confirmSetPassword(void)
{
	uint8 i,j;
	i=1;
	g_pass2Length=1;

	LCD_goToRowColumn(0,0);
	LCD_displayString("Re-Enter Pass");
	LCD_goToRowColumn(1,0);

	key=KeyPad_getPressedKey();
	_delay_ms(50);
	if(key>='0' && key <= '9')
	{
		LCD_displayCharacter('*');
		g_reEnteredPass[0] = key;
	}
	while (key>='0' && key <= '9')
	{
		key= KeyPad_getPressedKey();
		_delay_ms(50);
		LCD_displayCharacter('*');
		g_reEnteredPass[i] = key;
		i++;
		g_pass2Length++;
	}
	/*When user presses "=" the password is compared against the one entered last before*/

	if (key == '=')
	{
		if(verifyPass(g_enteredPass, g_reEnteredPass, g_pass2Length)==SUCCESS)
		{
			j=0;
			LCD_clearScreen();
			LCD_goToRowColumn(0,0);
			LCD_displayString("New Pass Set");

			while(g_reEnteredPass[j]!= '\0')
			{
				g_savedPass[j] = g_reEnteredPass[j]; /*Stores the new Password*/
				j++;
			}

			g_reEnteredPass[i] = '#'; /*add the "#" to be able to send string through UART*/
			UART_sendString(g_reEnteredPass); /*Sends the password to MC2 to be stored in EEPROM*/
			UART_sendByte(g_pass2Length); /*Sends the pass length to MC2 for proper storing in EEPROM*/
			Step2(); /*Proceed to step 2*/
		}
		else
		{
			LCD_clearScreen();
			LCD_goToRowColumn(0,0);
			LCD_displayString("Fail");
			_delay_ms(500);
			setPassword();  /*Retry entering password in case of Failure*/
		}
	}
}

/******************************************************************************
 *
 * Function Name: verifyPass
 *
 * Function Prototype: char verifyPass(char *pass1, char *pass2, uint8 passLength)
 *
 * Description: This function is used to compare any two passwords against each other
 * and returns SUCCESS (1) in case both passwords are the same and returns
 * FAILURE(0) in case of failure.
 * 
 * Arguments:
 * 
 * 1-char *a_pass1: the first password entered that we check against.
 * 
 * 2-char *a_pass2: the second password entered that we want to check.
 * 
 * 3-uint8 a_passLength: the length of the seconds entered password.
 *
 *******************************************************************************/
char verifyPass(char *a_pass1, char *a_pass2, uint8 a_passLength)
{
	uint8 i=0;
	while(i < a_passLength)
	{
		if(a_pass1[i] == a_pass2[i])
		{
			i++;
		}
		else
		{
			return FAIL;
		}

	}
	return SUCCESS;
}

/******************************************************************************
 *
 * Function Name: Step2
 *
 * Function Prototype: void Step2(void)
 *
 * Description: This is the seconds stage of the door locker system where the
 * the password is set and user gets to choose to open door or change the password
 * 
 * Arguments: None
 * 
 *******************************************************************************/

void Step2(void)
{
	LCD_clearScreen();
	LCD_goToRowColumn(0,0);
	LCD_displayString("* : Open Door");
	LCD_goToRowColumn(1,0);
	LCD_displayString("+ : Change Pass");

	key = KeyPad_getPressedKey();
	_delay_ms(50);
	if(key == '*')
	{
		openDoor();
	}
	else if (key == '+')
	{
		changePass();
	}
}


/******************************************************************************
 *
 * Function Name: openDoor
 *
 * Function Prototype: void openDoor(void)
 *
 * Description: This function prompts user to enter password and checks it against the saved
 * password from the previous stage, in case of success , it opens the door by rotating the
 * motor Clockwise for 15 seconds.
 *
 * In case of failure it prompts the user to try again for two times, if the user fails to
 * enter the correct password more than 3 times total, it turns of the buzzer for 60 seconds.
 *
 * Arguments: None
 *
 *******************************************************************************/

void openDoor(void)
{
	uint8 i = 1, trialCount = 0, passTrialLength;
	char passTrial[MAXPASSLENGTH];

	while(trialCount < MAX_ALLOWED_TRIALS)
	{
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString("Enter Password");
		LCD_goToRowColumn(1,0);

		key=KeyPad_getPressedKey();
		_delay_ms(50);
		if(key>='0' && key <= '9')
		{
			LCD_displayCharacter('*');
			passTrial[0] = key;
		}
		while (key>='0' && key <= '9')
		{
			key= KeyPad_getPressedKey();
			_delay_ms(50);
			LCD_displayCharacter('*');
			passTrial[i] = key;
			i++;
			passTrialLength++;
		}

		if (key == '=')
		{
			if (verifyPass(g_savedPass,passTrial, passTrialLength) == SUCCESS)
			{
				trialCount=0;
				rotateMotorCW(15); /*Rotates the motor clock-wise for 15 seconds to open door*/
				LCD_clearScreen();
				LCD_displayString("Opening Door...");
				_delay_ms(1500);
				LCD_clearScreen();
				LCD_displayString("Door is now Open");
				_delay_ms(500);
				LCD_clearScreen();

				LCD_displayString("*: Lock Door");
				LCD_goToRowColumn(1,0);
				LCD_displayString("+: Change Pass");

				key=KeyPad_getPressedKey();
				_delay_ms(50);

				if(key == '*')
				{
					rotateMotorCCW(15);
					LCD_clearScreen();
					LCD_displayString("Locking Door...");
					_delay_ms(1500);
					LCD_clearScreen();
					LCD_displayString("Door Locked!");
					_delay_ms(500);
					Step2();
				}
				else if(key == '+')
				{
					changePass(); /*User proceeds to change password*/
				}
			}
			else
			{
				LCD_clearScreen();
				LCD_goToRowColumn(0,0);
				LCD_displayString("PW Incorrect!");
				_delay_ms(100);
				trialCount++;
			}
		}
	}
	buzzerON(60);
}

/******************************************************************************
 *
 * Function Name: rotateMotorCW
 *
 * Function Prototype: void rotateMotorCW(uint8 a_seconds)
 *
 * Description: Function rotates the motor clock-wise for the number of seconds
 * input to the function.
 *
 * Arguments:
 * uint8 seconds: is the number of seconds the motor will rotate.
 *
 *******************************************************************************/
void rotateMotorCW(uint8 a_seconds)
{
	Timer1_setCallBack(stopMotor);
	timerONSeconds(a_seconds); /*turns on the timer for amount of seconds input*/
	DDRD = (1 << PD2) | (1 << PD3);
	SET_BIT(PORTD, PD2);
	CLEAR_BIT(PORTD,PD3);
}


/******************************************************************************
 *
 * Function Name: rotateMotorCCW
 *
 * Function Prototype: void rotateMotorCCW(uint8 a_seconds)
 *
 * Description: Function rotates the motor counter-clock-wise for the number of seconds
 * input to the function.
 *
 * Arguments:
 * uint8 seconds: is the number of seconds the motor will rotate.
 *
 *******************************************************************************/

void rotateMotorCCW(uint8 a_seconds)
{
	Timer1_setCallBack(stopMotor);
	timerONSeconds(a_seconds);
	DDRD = (1 << PD2) | (1 << PD3);
	SET_BIT(PORTD, PD3);
	CLEAR_BIT(PORTD,PD2);
}


/******************************************************************************
 *
 * Function Name: stopMotor
 *
 * Function Prototype: void stopMotor(void)
 *
 * Description: Function stops the motor from rotating.
 *
 * Arguments: None
 *
 *******************************************************************************/


void stopMotor(void)
{
	CLEAR_BIT(PORTD,PD2);
	CLEAR_BIT(PORTD,PD3);
}

/******************************************************************************
 *
 * Function Name: changePass
 *
 * Function Prototype: void changePass(void)
 *
 * Description: This function allows user to change the password, it firsts
 * takes an input password from the user to compare it against the old password.
 * in case of success the user proceeds to setting a new password.
 *
 * In case of more than three failures, buzzer is turn on for 60 seconds.
 *
 * Arguments: None
 *
 *******************************************************************************/

void changePass(void)
{
	char  passTrial[16], passTrialLength, trialCount=0;
	uint8 i=1;
	while(trialCount < MAX_ALLOWED_TRIALS)
	{
		LCD_clearScreen();
		LCD_goToRowColumn(0,0);
		LCD_displayString("Enter Old PW");
		LCD_goToRowColumn(1,0);

		/*get input from user to compare against stored password*/

		key= KeyPad_getPressedKey();
		_delay_ms(50);
		if(key>='0' && key <= '9')
		{
			LCD_displayCharacter('*');
			passTrial[0] = key;
		}

		while (key>='0' && key <= '9')
		{
			key= KeyPad_getPressedKey();
			_delay_ms(50);
			LCD_displayCharacter('*');
			passTrial[i] = key;
			i++;
			passTrialLength++;
		}


		if (key == '=')
		{
			if(verifyPass(g_savedPass,passTrial, passTrialLength)==SUCCESS)
			{
				trialCount=0;
				UART_sendByte(CHANGE_PASS); /*sends byte to MC2 to change pw stored in EEPROM*/
				setPassword(); /*User proceeds to set a new Password*/
			}
			else
			{
				LCD_clearScreen();
				LCD_goToRowColumn(0,0);
				LCD_displayString("PW Incorrect!");
				trialCount++;
			}
		}
	}

	buzzerON(60); /*turns on the buzzer for 60 seconds*/
}

/******************************************************************************
 *
 * Function Name: buzzerON
 *
 * Function Prototype: void buzzerON (uint8 a_seconds)
 *
 * Description: Function turns the buzzer on for the input number of seconds.
 *
 * Arguments:
 * uint8 seconds: is the number of seconds the buzzer will stay on.
 *
 *******************************************************************************/
void buzzerON(uint8 a_seconds)
{
	LCD_clearScreen();
	LCD_displayString("INTRUDER ALERT!");
	Timer1_setCallBack(buzzerOFF);
	timerONSeconds(a_seconds);
	DDRD = (1 << PD4) | (1 << PD5);
	SET_BIT(PORTD, PD4);
	CLEAR_BIT(PORTD,PD5);
}

/******************************************************************************
 *
 * Function Name: buzzerOFF
 *
 * Function Prototype: void buzzerOFF(void)
 *
 * Description: Function turns the buzzer off and takes the user back to step 2
 *
 * Arguments: None
 *
 *******************************************************************************/

void buzzerOFF (void)
{
	CLEAR_BIT(PORTD,PD5);
	CLEAR_BIT(PORTD, PD4);
	Step2();
}


/******************************************************************************
 *
 * Function Name: main
 *
 * Function Prototype: int main (void)
 *
 * Description: the main function of micro-controller1 of the door locker
 * contains the initializing of UART and LCD.
 *
 * It receives a byte from MC2 to check if the system is running for the first time
 * or already has a stored password.
 *
 * In case of first time, user proceeds to set a new password.
 *
 * Otherwise, it proceeds directly to step 2.
 *
 * Arguments: None
 *
 *******************************************************************************/

int main (void)
{
	uint8 stage_check;

	UART_init();
	LCD_init();

	LCD_displayString("Door Locker");
	_delay_ms(500);

	while(UART_receiveByte() != M2_READY){}; /*Processor waits to sync UART with second MC*/
	stage_check = UART_receiveByte(); /*checks if a password is already stored in eeprom on other MC*/

	if(stage_check == FIRST_TIME)
	{
		LCD_clearScreen();
		LCD_displayString("Welcome");
		_delay_ms(500);
		setPassword();
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("Welcome Back");
		_delay_ms(500);
		g_passLength = UART_receiveByte(); /*receives the length of stored pass from second MC*/
		UART_receiveString(g_savedPass); /*receives password stored in eeprom by seconds MC*/
		Step2(); /*user proceeds to seconds stage*/
	}
	while(1)
	{


	}
}
