/*
 * Model.h
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#ifndef AP_MODEL_MODEL_STOPWATCH_H_
#define AP_MODEL_MODEL_STOPWATCH_H_
#include <stdint.h>
#include "cmsis_os.h"

typedef enum {S_STOPWATCH_STOP, S_STOPWATCH_RUN, S_STOPWATCH_CLEAR} eStopWatchState_t;
typedef enum {EVENT_RUN_STOP, EVENT_CLEAR}eStopWatchEvent_t;

typedef struct{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint16_t msec;
}stopWatch_t;

extern osMessageQId stopWatchEventMsgBox;
extern osMailQId stopWatchDataMailBox;

void Model_StopWatchInit();
void Model_SetStopWatchState (eStopWatchState_t state);
eStopWatchState_t Model_GetStopWatchState();

#endif /* AP_MODEL_MODEL_STOPWATCH_H_ */
