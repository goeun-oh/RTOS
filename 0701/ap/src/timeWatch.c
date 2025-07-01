/*
 * timeWatch.c
 *
 *  Created on: Jun 23, 2025
 *      Author: rhoblack
 */


#include "timeWatch.h"

static watch_t timeWatch = {TIME_WATCH, 12,0,0,0};

void TimeWatch_IncTimeCallBack()
{
	if (timeWatch.msec < 1000-1) {
		timeWatch.msec++;
		return;
	}
	timeWatch.msec = 0;

	if (timeWatch.sec < 60-1) {
		timeWatch.sec++;
		return;
	}
	timeWatch.sec = 0;

	if (timeWatch.min < 60-1) {
		timeWatch.min++;
		return;
	}
	timeWatch.min = 0;

	if (timeWatch.hour < 24-1) {
		timeWatch.hour++;
		return;
	}
	timeWatch.hour = 0;
}

void TimeWatch_Excute()
{
	Presenter_OutData(timeWatch);

//	FND_WriteData(timeWatch.hour*100 + timeWatch.min);
//
//	FND_WriteDp(FND_DP_1000|FND_DP_10|FND_DP_1, FND_DP_OFF);
//
//	if (timeWatch.msec < 500) {
//		FND_WriteDp(FND_DP_100, FND_DP_ON);
//	}
//	else {
//		FND_WriteDp(FND_DP_100, FND_DP_OFF);
//	}
}
