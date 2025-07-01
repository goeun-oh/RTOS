/*
 * Motor.c
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#include "Motor.h"

static TIM_HandleTypeDef *hmotorTim;
static uint32_t motorTimChannel;

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel)
{
	hmotorTim = htim;
	motorTimChannel = channel;
}

void Motor_SetFreq(uint32_t freq)
{
	__HAL_TIM_SET_AUTORELOAD(&htim1, 1000000/freq - 1);	// PWM 주기 설정
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000000/freq/2 - 1); // 50% duty 유지
}

void Motor_SetPower(uint8_t percent)
{
	if (percent > 100) percent = 100;

	uint32_t arr = __HAL_TIM_GET_AUTORELOAD(hmotorTim);
	uint32_t ccr = (arr + 1) * percent / 100;

	__HAL_TIM_SET_COMPARE(hmotorTim, motorTimChannel, ccr);
}



void Motor_Start()
{
	HAL_TIM_PWM_Start(hmotorTim, motorTimChannel);
}

void Motor_Stop()
{
	HAL_TIM_PWM_Stop(hmotorTim, motorTimChannel);
}
