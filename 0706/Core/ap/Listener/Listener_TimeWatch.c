/*
 * Listener_TimeWatch.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "Listener_TimeWatch.h"
Button_Handler_t hbtnTimeModify;
Button_Handler_t hbtnTimeSet;

static void Listener_TimeWatch_CheckButton();

void Listener_TimeWatchInit(){
	Button_Init(&hbtnTimeModify, GPIOB, GPIO_PIN_3);
	Button_Init(&hbtnTimeSet, GPIOA, GPIO_PIN_10);
}

void Listener_TimeWatchExcute(){
	Listener_TimeWatch_CheckButton();
}

void Listener_TimeWatch_CheckButton(){
	if (Button_GetState(&hbtnTimeModify) == ACT_RELEASED)
	{
		osMessagePut(timeWatchEventMsgBox, EVENT_TIME_MODIFY, 0);
	}
	else if (Button_GetState(&hbtnTimeSet) == ACT_RELEASED)
	{
		osMessagePut(timeWatchEventMsgBox, EVENT_TIME_SET, 0);
	}
}

