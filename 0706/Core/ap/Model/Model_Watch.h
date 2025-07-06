/*
 * Model_Watch.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_MODEL_MODEL_WATCH_H_
#define AP_MODEL_MODEL_WATCH_H_

#include "cmsis_os.h"
#include "TimeWatch.h"


typedef enum{
	S_TIMEWATCH_NORMAL,
	S_TIMEWATCH_MODIFY_HOUR,
	S_TIMEWATCH_MODIFY_MIN,
	S_TIMEWATCH_MODIFY_SEC
}eTimeWatchState_t;

typedef enum {EVENT_TIME_MODIFY, EVENT_TIME_SET}eTimeWatchEvent_t;

extern osMessageQId timeWatchEventMsgBox;


extern osMailQId timeWatchDataMailBox;
void Model_TimeWatchInit();
void Model_SetTimeWatchState(eTimeWatchState_t state);
eTimeWatchState_t Model_GetTimeWatchState();

#endif /* AP_MODEL_MODEL_WATCH_H_ */
