/*
 * Listener_StopWatch.c
 *
 *  Created on: Jul 3, 2025
 *      Author: kccistc
 */

#include "Listener_StopWatch.h"

Button_Handler_t hbtnRunStop;
Button_Handler_t hbtnClear;
static void Listener_StopWatch_CheckButton();

void Listener_StopWatchInit()
{
	Button_Init(&hbtnRunStop, GPIOB, GPIO_PIN_3);
	Button_Init(&hbtnClear, GPIOA, GPIO_PIN_10);
}

void Listener_StopWatchExcute()
{
	Listener_StopWatch_CheckButton();
}

void Listener_StopWatch_CheckButton()
{
	if (Button_GetState(&hbtnRunStop) == ACT_PUSHED)
	{
		osMessagePut(stopWatchEventMsgBox, EVENT_RUN_STOP, 0);
	}
	else if (Button_GetState(&hbtnClear) == ACT_PUSHED)
	{
		osMessagePut(stopWatchEventMsgBox, EVENT_CLEAR, 0);
	}
}
