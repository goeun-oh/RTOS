/*
 * Presenter_StopWatch.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#include "Presenter_StopWatch.h"

void Presenter_StopWathInit()
{

}
static void Presenter_State(eStopWatchState_t state);
void Presenter_StopWatchExcute()
{
	static stopWatch_t StopWatchData;
	stopWatch_t *pStopWatchData;

	osEvent evt = osMailGet(stopWatchDataMailBox, 0);
	if (evt.status == osEventMail) {
		pStopWatchData = evt.value.p;
		memcpy(&StopWatchData, pStopWatchData, sizeof(stopWatch_t));
		osMailFree(stopWatchDataMailBox, pStopWatchData);
		Presenter_StopWatch_FND(StopWatchData);
		Presenter_StopWatch_LCD(StopWatchData);
		Presenter_State(Model_GetStopWatchState());
	}
}

void Presenter_StopWatch_FND(stopWatch_t StopWatchData)
{
	FND_WriteData((StopWatchData.min %10) *1000 + StopWatchData.sec *10 + (StopWatchData.msec/100)%10);
	if (StopWatchData.msec%100 <50) {
		FND_WriteDp(FND_DP_10,FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_10, FND_DP_OFF);
	}
	if (StopWatchData.msec <500) {
		FND_WriteDp(FND_DP_1000,FND_DP_ON);
	}
	else {
		FND_WriteDp(FND_DP_1000, FND_DP_OFF);
	}
}

void Presenter_StopWatch_LCD(stopWatch_t StopWatchData)
{
	char str[30];
	if (StopWatchData.msec <500){
		sprintf(str, "%02d:%02d:%02d:%02d      ",
				StopWatchData.hour, StopWatchData.min, StopWatchData.sec, StopWatchData.msec/10);
	}else{
		sprintf(str, "%02d %02d %02d %02d      ",
						StopWatchData.hour, StopWatchData.min, StopWatchData.sec, StopWatchData.msec/10);
	}
	LCD_writeStringXY(1, 0, str);
}

void Presenter_State(eStopWatchState_t state)
{
	switch (state) {
		case S_STOPWATCH_STOP:
			LCD_writeStringXY(0, 11, "STOP  ");
			break;
		case S_STOPWATCH_RUN:
			LCD_writeStringXY(0, 11, "RUN   ");
			break;
		case S_STOPWATCH_CLEAR:
			LCD_writeStringXY(0, 11, "CLEAR");
			break;
	}
}
