/*
 * motorSpeed.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef AP_INC_MOTORSPEED_H_
#define AP_INC_MOTORSPEED_H_

#include "stm32f4xx_hal.h"
#include "Motor.h"
#include "tim.h"

void MotorSpeed_Init();
void MotorSpeed_RunStateMachine();


#endif /* AP_INC_MOTORSPEED_H_ */
