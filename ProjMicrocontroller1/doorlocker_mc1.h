/******************************************************************************
 *
 * Module: Micro-Controller 1
 *
 * File Name: doorlocker_mc1.h
 *
 * Description: Header file for micro-controller 1 of Door Locker System
 *
 * Author: Ali Sadek
 *
 *******************************************************************************/

#ifndef DOORLOCKER_MC1_H_
#define DOORLOCKER_MC1_H_

/*******************************************************************************
 *                      Included Files                                         *
 *******************************************************************************/

#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer1.h"
#include <string.h>

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define SUCCESS 1
#define FAIL 0

#define OPEN 1
#define CLOSED 0

/*Used to confirm that UART is Ready*/
#define M2_READY 0x10

/*Maximum Pass Length Allowed due to LCD Screen*/
#define MAXPASSLENGTH 16

/*Maximum number of trials allowed before buzzer is turned on*/
#define MAX_ALLOWED_TRIALS 3

/*Stage Check bytes*/

#define FIRST_TIME 0x12
#define NOT_FIRST_TIME 0x11

/*Sent to MC2 when a new password is set and should be stored in EEPROM*/
#define CHANGE_PASS 0x77

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


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
void confirmSetPassword(void);

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

void setPassword(void);

/******************************************************************************
 *
 * Function Name: Step2
 *
 * Function Prototype: void Step2(void)
 *
 * Description: This is the second stage of the door locker system where the
 * the password is set and user gets to choose to open door or change the password
 *
 * Arguments: None
 *
 *******************************************************************************/
void Step2(void);

/******************************************************************************
 *
 * Function Name: Step3
 *
 * Function Prototype: void Step3(void)
 *
 * Description: This is the third stage of the door locker system where the
 * the door is open and user gets to choose to lock the door or change the
 * password.
 *
 * Arguments: None
 *
 *******************************************************************************/
void Step3(void);

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

void openDoor(void);

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
void rotateMotorCW(uint8 seconds);

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
void rotateMotorCCW(uint8 seconds);

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

void stopMotor(void);

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
void changePass(void);

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
void buzzerON(uint8 seconds);

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
void buzzerOFF (void);

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
char verifyPass(char *pass1, char *pass2, uint8 passLength);


#endif /* DOORLOCKER_MC1_H_ */
