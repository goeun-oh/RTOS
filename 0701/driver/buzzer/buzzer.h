/*
 * buzzer.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_BUZZER_BUZZER_H_
#define DRIVER_BUZZER_BUZZER_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

void Buzzer_Init(TIM_HandleTypeDef *htim, uint32_t channel);

void Buzzer_SetFreq(uint32_t freq);

void Buzzer_Start();

void Buzzer_Stop();

#endif /* DRIVER_BUZZER_BUZZER_H_ */
