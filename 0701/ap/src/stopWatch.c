/*
 * stopWatch.c
 *
 *  Created on: Jun 23, 2025
 *      Author: rhoblack
 */

#include "stopWatch.h"

typedef enum {STOP, RUN, CLEAR}stopWatchState_t;

extern inputData_TypeDef controlData;
static stopWatchState_t stopWatchState = STOP;
static watch_t stopWatch = {STOP_WATCH, 12, 0, 0, 0};

void StopWatch_IncTimeCallBack()
{
	if (stopWatchState == RUN) {
		StopWatch_IncTime();
	}
}

void StopWatch_IncTime()
{
	if (stopWatch.msec < 1000-1) {
		stopWatch.msec++;
		return;
	}
	stopWatch.msec = 0;

	if (stopWatch.sec < 60-1) {
		stopWatch.sec++;
		return;
	}
	stopWatch.sec = 0;

	if (stopWatch.min < 60-1) {
		stopWatch.min++;
		return;
	}
	stopWatch.min = 0;

	if (stopWatch.hour < 24-1) {
		stopWatch.hour++;
		return;
	}
	stopWatch.hour = 0;
}

button_t btnWatch = {0};

void StopWatch_Excute(button_t btnWatch)
{
	switch (stopWatchState)
	{
	case STOP:
		StopWatch_Stop(&btnWatch);
		break;
	case RUN:
		StopWatch_Run(&btnWatch);
		break;
	case CLEAR:
		StopWatch_Clear(&btnWatch);
		break;
	}
	if(isQueFull(&stopWatchQue)){
		return;
	}
	enQue(&stopWatchQue, &stopWatch);
}

void StopWatch_Stop(button_t btnWatch)
{

	if (btnWatch.id == BTN_RUN_STOP) {
		stopWatchState = RUN;
	}
	else if (btnWatch.id == BTN_CLEAR) {
		stopWatchState = CLEAR;
	}
	//FND_WriteData((stopWatch.min % 10 * 1000) + (stopWatch.sec * 10) + (stopWatch.msec/100));
}

void StopWatch_Run(button_t btnWatch)
{
	if (btnWatch.id == BTN_RUN_STOP) {
		stopWatchState = STOP;
	}

//	FND_WriteData((stopWatch.min % 10 * 1000) + (stopWatch.sec * 10) + (stopWatch.msec/100));
//
//	FND_WriteDp(FND_DP_100|FND_DP_1, FND_DP_OFF);
//
//	if (stopWatch.msec%100 < 50) {
//		FND_WriteDp(FND_DP_10, FND_DP_ON);
//	}
//	else {
//		FND_WriteDp(FND_DP_10, FND_DP_OFF);
//	}
//
//	if (stopWatch.msec < 500) {
//		FND_WriteDp(FND_DP_1000, FND_DP_ON);
//	}
//	else {
//		FND_WriteDp(FND_DP_1000, FND_DP_OFF);
//	}
}

void StopWatch_Clear()
{
	stopWatchState = STOP;
	stopWatch.msec = 0;
	stopWatch.sec = 0;
	stopWatch.min = 0;
	stopWatch.hour = 0;

	//FND_WriteData((stopWatch.min % 10 * 1000) + (stopWatch.sec * 10) + (stopWatch.msec/100));
}






