/*
 * TimeWatch.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "TimeWatch.h"
#include <stdint.h>
#include <stdio.h>
#include "string.h"

timeWatch_t timeWatchData;

static void TimeWatch_Normal();
static void TimeWatch_ModifyHour();
static void TimeWatch_ModifyMin();
static void TimeWatch_ModifySec();


void TimeWatch_Init()
{
	timeWatchData.hour = 12;
	timeWatchData.min  = 0;
	timeWatchData.sec  = 0;
	timeWatchData.msec = 0;

	timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
	memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
	osMailPut(timeWatchDataMailBox, pTimeWatchData);
}



void TimeWatch_Excute(){
	eTimeWatchState_t state = Model_GetTimeWatchState();

	switch(state){
	case S_TIMEWATCH_NORMAL:
		TimeWatch_Normal();
		break;
	case S_TIMEWATCH_MODIFY_HOUR:
		TimeWatch_ModifyHour();
		break;
	case S_TIMEWATCH_MODIFY_MIN:
		TimeWatch_ModifyMin();
		break;
	case S_TIMEWATCH_MODIFY_SEC:
		TimeWatch_ModifySec();
		break;
	default:
		break;
	}
}

void TimeWatch_IncTimeCallBack()
{
	if (timeWatchData.msec <= 1000-1){
		timeWatchData.msec++;
		return;
	}
	timeWatchData.msec = 0;

	if (timeWatchData.sec <= 60-1)
	{
		timeWatchData.sec++;
		return;
	}
	timeWatchData.sec = 0;

	if(timeWatchData.min <= 60-1)
	{
		timeWatchData.min++;
		return;
	}
	timeWatchData.min = 0;

	if(timeWatchData.hour <= 24-1)
	{
		timeWatchData.hour++;
		return;
	}
	timeWatchData.hour = 0;

}

void TimeWatch_Normal(){
	static uint16_t prevMsec =0;
	if (prevMsec == timeWatchData.msec){
		return;
	}

	prevMsec = timeWatchData.msec;
	timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
	memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
	osMailPut(timeWatchDataMailBox, pTimeWatchData);

	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if(evt.status == osEventMessage){
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY){
			Model_SetTimeWatchState(S_TIMEWATCH_MODIFY_HOUR);
		}

	}
}

void TimeWatch_ModifyHour(){
	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if(evt.status == osEventMessage){
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY){
			Model_SetTimeWatchState(S_TIMEWATCH_MODIFY_MIN);
		}
		else if(evtState == EVENT_TIME_SET){
			timeWatchData.hour++;
			if(timeWatchData.hour == 24){
				timeWatchData.hour =0;
			}
			timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, pTimeWatchData);
		}
	}

}

void TimeWatch_ModifyMin(){
	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if(evt.status == osEventMessage){
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY){
			Model_SetTimeWatchState(S_TIMEWATCH_MODIFY_SEC);
		}
		else if(evtState == EVENT_TIME_SET){
			timeWatchData.min++;
			if(timeWatchData.min == 60){
				timeWatchData.min =0;
			}

			timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, pTimeWatchData);
		}
	}
}

void TimeWatch_ModifySec(){
	osEvent evt = osMessageGet(timeWatchEventMsgBox, 0);
	uint16_t evtState;

	if(evt.status == osEventMessage){
		evtState = evt.value.v;

		if (evtState == EVENT_TIME_MODIFY){
			Model_SetTimeWatchState(S_TIMEWATCH_NORMAL);
		}
		else if(evtState == EVENT_TIME_SET){
			timeWatchData.sec = 0;
			timeWatchData.msec = 0;
			timeWatch_t *pTimeWatchData = osMailAlloc(timeWatchDataMailBox, 0);
			memcpy(pTimeWatchData, &timeWatchData, sizeof(timeWatch_t));
			osMailPut(timeWatchDataMailBox, pTimeWatchData);
		}
	}
}
