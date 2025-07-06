/*
 * Presenter_TimeWatch.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "Presenter_TimeWatch.h"
#include <stdio.h>

static void Presenter_TimeWatch_FND(timeWatch_t timeWatchData);
static void Presenter_TimeWatch_LCD(timeWatch_t timeWatchData);
static void Presenter_State(eTimeWatchState_t state);

void Presenter_TimeWathInit(){

}

void Presenter_TimeWatchExcute(){
	timeWatch_t timeWatchData;
	timeWatch_t *pTimeWatchData;
	eTimeWatchState_t state = Model_GetTimeWatchState();
	osEvent evt = osMailGet(timeWatchDataMailBox, 0);
	if (evt.status == osEventMail) {
		pTimeWatchData = evt.value.p;
		memcpy(&timeWatchData, pTimeWatchData, sizeof(timeWatch_t));
		osMailFree(timeWatchDataMailBox, pTimeWatchData);
		Presenter_TimeWatch_FND(timeWatchData);
		Presenter_TimeWatch_LCD(timeWatchData);
		Presenter_State(state);
	}
}


void Presenter_TimeWatch_FND(timeWatch_t timeWatchData){
	FND_WriteData((timeWatchData.hour) *100 +  timeWatchData.min);

	if (timeWatchData.msec <500) {
		FND_WriteDp(FND_DP_100,FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_100, FND_DP_OFF);
	}
}

void Presenter_TimeWatch_LCD(timeWatch_t timeWatchData){
	char str[30];
	sprintf(str, "TimeWatch");
	LCD_writeStringXY(0, 0, str);

	if (timeWatchData.msec <500){
		sprintf(str, "%02d:%02d:%02d       ",
				timeWatchData.hour, timeWatchData.min, timeWatchData.sec);
	} else{
		sprintf(str, "%02d %02d %02d       ",
						timeWatchData.hour, timeWatchData.min, timeWatchData.sec);
	}
	LCD_writeStringXY(1, 0, str);
}

void Presenter_State(eTimeWatchState_t state)
{
	switch (state) {
		case S_TIMEWATCH_NORMAL:
			LCD_writeStringXY(0, 11, "NORMAL  ");
			break;
		case S_TIMEWATCH_MODIFY_HOUR:
			LCD_writeStringXY(0, 11, "MODIFY HOUR   ");
			break;
		case S_TIMEWATCH_MODIFY_MIN:
			LCD_writeStringXY(0, 11, "MODIFY MIN");
			break;
		case S_TIMEWATCH_MODIFY_SEC:
			LCD_writeStringXY(0, 11, "MODIFY SEC");
			break;
		default:
			break;
	}
}
