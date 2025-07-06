/*
 * Listener_Distance.c
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */


#include "Listener_Distance.h"

Button_Handler_t hbtnStart;

static void Listener_Distance_CheckButton();

void Listener_DistanceInit(){
	Button_Init(&hbtnStart, GPIOB, GPIO_PIN_3);
}

void Listener_DistanceExcute(){
	Listener_Distance_CheckButton();
}

void Listener_Distance_CheckButton()
{
	if (Button_GetState(&hbtnStart) == ACT_PUSHED)
	{
		osMessagePut(distanceEventMsgBox, EVENT_START, 0);
	}
}
