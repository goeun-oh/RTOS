/*
 * Motor.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef DRIVER_MOTOR_MOTOR_H_
#define DRIVER_MOTOR_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "tim.h"

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void Motor_SetFreq(uint32_t freq);
void Motor_Start();
void Motor_Stop();
void Motor_SetPower(uint8_t percent);
#endif /* DRIVER_MOTOR_MOTOR_H_ */
