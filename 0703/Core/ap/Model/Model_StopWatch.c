/*
 * Model.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */


#include <Model_StopWatch.h>

static eStopWatchState_t stopWatchState = S_STOPWATCH_STOP;

osMessageQId stopWatchEventMsgBox;
osMessageQDef(stopWatchEventQueue, 16, uint16_t);

osMailQId stopWatchDataMailBox;
osMailQDef(stopWatchDataQueue, 4, stopWatch_t);

void Model_StopWatchInit()
{
	stopWatchEventMsgBox = osMessageCreate(osMessageQ(stopWatchEventQueue), NULL);
	stopWatchDataMailBox = osMailCreate(osMailQ(stopWatchDataQueue), NULL);
}

// getter setter
void Model_SetStopWatchState (eStopWatchState_t state)
{
	stopWatchState = state;
}

eStopWatchState_t Model_GetStopWatchState()
{
	return stopWatchState;
}
