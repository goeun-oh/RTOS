/*
 * sound.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#include "sound.h"

void Sound_Init(){
	Buzzer_Init(&htim3, TIM_CHANNEL_1);
}
//전원을 딱 켰을 때 소리가 나게하고 싶다.
void Sound_PowerOn(){
	Buzzer_SetFreq(261);
	Buzzer_Start();
	HAL_Delay(100);
	Buzzer_SetFreq(330);
	HAL_Delay(100);
	Buzzer_SetFreq(392);
	HAL_Delay(100);
	Buzzer_SetFreq(523);
	HAL_Delay(100);
	Buzzer_Stop();

}

void Sound_PowerOff(){

}

// mode가 변경될 때 나오는 소리
void Sound_ChangeMode(){

}


void Sound_Alarm(){

}
