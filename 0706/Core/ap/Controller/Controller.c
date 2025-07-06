/*
 * Controller.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#include "Controller.h"

static void Controller_CheckEventMode();

void Controller_Init()
{
	TimeWatch_Init();
	StopWatch_Init();
	Distance_Init();
	TempHumid_Excute();
}

void Controller_Excute()
{
	eModeState_t state = Model_GetModeState();

	switch(state){
	case S_TIMEWATCH_MODE:
		TimeWatch_Excute();
		break;
	case S_STOPWATCH_MODE:
		StopWatch_Excute();
		break;
	case S_DISTANCE_MODE:
		Distance_Excute();
		break;
	case S_TEMP_HUMID_MODE:
		TempHumid_Excute();
		break;
	default:
		break;
	}
	Controller_CheckEventMode();
}


void Controller_CheckEventMode()
{
	osEvent evt = osMessageGet(modeEventMsgBox, 0);
	uint16_t evtState;

	if(evt.status == osEventMessage){
		evtState = evt.value.v;
		if (evtState != EVENT_MODE){
			return;
		}
		eModeState_t state = Model_GetModeState();
		if(state == S_TIMEWATCH_MODE){
			Model_SetModeState(S_STOPWATCH_MODE);
			stopWatch_t *pStopWatchData = osMailAlloc(stopWatchDataMailBox, 0);
			memcpy(pStopWatchData, &stopWatchData, sizeof(stopWatch_t));
			osMailPut(stopWatchDataMailBox, pStopWatchData);
		}else if (state == S_STOPWATCH_MODE){
			Model_SetModeState(S_DISTANCE_MODE);
		}  else if (state == S_DISTANCE_MODE){
			Model_SetModeState(S_TEMP_HUMID_MODE);
		} else if (state == S_TEMP_HUMID_MODE){
			Model_SetModeState(S_TIMEWATCH_MODE);
			timeWatch_t *ptimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(ptimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, ptimeWatchData);
		}
	}
}
