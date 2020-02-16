/******************************************************************************
 *
 * Module: Timer 1
 *
 * File Name: timer1.h
 *
 * Description: Header file for timer1.
 *
 * Author: Ali Sadek
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

/*******************************************************************************
 *                      Included Files                                         *
 *******************************************************************************/
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 * Structure that contains the settings of the clock:
 *
 * NO_CLOCK: Timer is OFF
 * F_CPU: Timer Clock equal to the CPU clock
 * F_CPU8: Timer Clock equal F_CPU/8
 * F_CPU64: Timer Clock equal F_CPU/64
 * F_CPU256: Timer Clock equal F_CPU/256
 * F_CPU1024: Timer Clock equal F_CPU/1024
 *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU8,F_CPU64,F_CPU256,F_CPU1024
}timer1_clock;


/*******************************************************************************
 * Sets the Compare Mode:
 *
 * COM1_NORMAL_MODE: Normal port operation, OC1A/OC1B disconnected.
 * COM1_TOGGLE_MODE: Sets Timer to Toggle mode
 * COM1_CTC_MODE: Clear Timer On Compare Mode
 * COM1_SET_MODE: Set Timer on Compare mode
 *
 *******************************************************************************/


typedef enum
{
	COM1_NORMAL_MODE, COM1_TOGGLE_MODE, COM1_CTC_MODE, COM1_SET_MODE
}timer1_compare_mode;


/*******************************************************************************
 * Sets the Interrupt Mode:
 *
 * TIMER1_NO_INTERRUPT: No interrupt
 * TIMER1_OVF: Interrupt triggered when timer overflows
 * TIMER1_OCB: Interrupt triggered when Timer reaches value of OCB
 * TIMER1_OCA: Interrupt triggered when Timer reaches value of OCA
 *
 *******************************************************************************/

typedef enum
{
	TIMER1_NO_INTERRUPT ,TIMER1_OVF, TIMER1_OCB, TIMER1_OCA
}timer1_mode;

/*******************************************************************************
 * Configuration of Timer1
 *******************************************************************************/

typedef struct
{
	timer1_clock T1_clk;
	timer1_compare_mode T1_cmp_mode;
	timer1_mode T1_mode;
	uint16 T1_startValue;
	uint16 T1_compareValue;
}Timer1_ConfigType;

/******************************************************************************
 *
 * Function Name: timerONSeconds
 *
 * Function Prototype: void timerONSeconds(uint8 seconds)
 *
 * Description: Configures that timer in Clear output on Compare mode in channel A
 * and sets the clock to F_CPU/1024 and takes the number of seconds the timer will
 * tick before triggering an interrupt.
 *
 * Arguments:
 *
 * a_seconds: the number of seconds the timer will tick before triggering an interrupt
 *
 *******************************************************************************/
void timerONSeconds(uint8 seconds);

/******************************************************************************
 *
 * Function Name: timer1_init
 *
 * Function Prototype: void timer1_init(const Timer1_ConfigType *timer1_config_ptr)
 *
 * Description: Initializes timer1, it enables the global interrupts, sets the
 * pre-scaler required for the clock, sets the starting value and the compare value,
 * also sets the mode of operation of the timer.
 *
 * Arguments:
 *
 * const Timer1_ConfigType *timer1_config_ptr:  Pointer of type Timer1_ConfigType
 * which contains the configuration of timer1.
 *
 *******************************************************************************/
void timer1_init(const Timer1_ConfigType *timer1_config_ptr);


/******************************************************************************
 *
 * Function Name: Timer1_setCallBack
 *
 * Function Prototype: void Timer1_setCallBack(void(*Ptr2Func)(void))
 *
 * Description: Sets the call back function that the timer will return to after
 * interrupt.
 *
 * Arguments:
 *
 * void(*Ptr2Func)(void): a pointer to the function to be called after interrupt.
 *
 *******************************************************************************/
void Timer1_setCallBack(void(*Ptr2Func)(void));


#endif /* TIMER1_H_ */
