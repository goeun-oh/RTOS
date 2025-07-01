/*
 * Model_Watch.h
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */

#ifndef AP_INC_MODEL_WATCH_H_
#define AP_INC_MODEL_WATCH_H_
#include "stm32f4xx_hal.h"
#include "my_queue.h"
enum {TIME_WATCH, STOP_WATCH};
enum {NO_CONTROL,BTN_MODE, BTN_RUN_STOP, BTN_CLEAR};

typedef struct {
	uint8_t id;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint16_t msec;
}watch_t;

typedef struct{
	uint8_t id;
}button_t;


extern Que_TypeDef btnQue;
extern Que_TypeDef stopWatchQue;
#endif /* AP_INC_MODEL_WATCH_H_ */
