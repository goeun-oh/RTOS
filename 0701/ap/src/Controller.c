/*
 * Controller.c
 *
 *  Created on: Jun 24, 2025
 *      Author: rhoblack
 */
#include "Controller.h"


typedef enum {S_TIME_WATCH, S_STOP_WATCH} watchModeState_t;

void Controller_Mode();


static watchModeState_t modeState = TIME_WATCH;

static button_t btnWatch = {0};

void Controller_Excute()
{
	Controller_Mode();
}


void Controller_Mode()
{
	if(isQueEmpty(&btnQue)){
		return;
	}
	deQue(&btnQue, &btnWatch);

	switch(modeState)
	{
	case S_TIME_WATCH:
		if (btnWatch.id == BTN_MODE) {
			modeState = S_STOP_WATCH;
		}
		TimeWatch_Excute(&btnWatch);
		break;
	case S_STOP_WATCH:
		if (btnWatch.id == BTN_MODE) {
			modeState = S_TIME_WATCH;
		}
		StopWatch_Excute(&btnWatch);
		break;
	}
}
