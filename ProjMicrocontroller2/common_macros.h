/*
 * common_macros.h
 *
 *  Created on: Dec 27, 2019
 *      Author: aly_s
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG_NAME, PIN_NUM) ((REG_NAME)|= ((1)<<(PIN_NUM)))
#define CLEAR_BIT(REG_NAME, PIN_NUM) ((REG_NAME)&=~((1)<<(PIN_NUM)))
#define TOGGLE_BIT(REG_NAME, PIN_NUM) ((REG_NAME)^= ((1)<<(PIN_NUM)))
#define BIT_IS_SET(REG_NAME, PIN_NUM) ((REG_NAME)&(1<<(PIN_NUM)))
#define BIT_IS_CLEAR(REG_NAME, PIN_NUM) (!((REG_NAME)&(1<<(PIN_NUM))))


#endif /* COMMON_MACROS_H_ */
