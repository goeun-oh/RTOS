/*
 * Listener.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#include "Listener.h"

Button_Handler_t hbtnMode;

static void Listener_CheckButton();

void Listener_Init()
{
	Button_Init(&hbtnMode, GPIOB, GPIO_PIN_5);
	Listener_TimeWatchInit();
	Listener_StopWatchInit();
	Listener_DistanceInit();
	Listener_TempHumidInit();
}

void Listener_Excute()
{
	eModeState_t state=Model_GetModeState();

	switch(state){
	case S_TIMEWATCH_MODE:
		Listener_TimeWatchExcute();
		break;
	case S_STOPWATCH_MODE:
		Listener_StopWatchExcute();
		break;
	case S_DISTANCE_MODE:
		Listener_DistanceExcute();
		break;
	case S_TEMP_HUMID_MODE:
		Listener_TempHumidExcute();
		break;
	default:
		break;
	}
	Listener_CheckButton();
}


void Listener_CheckButton()
{
	if (Button_GetState(&hbtnMode) == ACT_RELEASED){
		osMessagePut(modeEventMsgBox, EVENT_MODE, 0);
	}
}
