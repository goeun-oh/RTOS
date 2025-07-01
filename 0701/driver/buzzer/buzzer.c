/*
 * buzzer.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */


#include "buzzer.h"

static TIM_HandleTypeDef *hbuzzerTim;
static uint32_t buzzerTimChannel;


void Buzzer_Init(TIM_HandleTypeDef *htim, uint32_t channel){
	hbuzzerTim = htim;
	buzzerTimChannel = channel;
}

void Buzzer_SetFreq(uint32_t freq){
	if(freq <100) freq =100; //가청 주파수가 20~20kHz
	else if (freq > 10000) freq = 10000;

	__HAL_TIM_SET_AUTORELOAD(&htim3, 1000000/freq -1); //ARR 변경, 음높이 변화함
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (100000/freq/2) -1); //CCR 변경, Duty cycle 항상 50%로
}


void Buzzer_Start(){
	HAL_TIM_PWM_Start(hbuzzerTim, buzzerTimChannel);
}

void Buzzer_Stop(){
	HAL_TIM_PWM_Stop(hbuzzerTim, buzzerTimChannel);

}


