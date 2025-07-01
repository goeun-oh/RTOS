/*
 * sound.h
 *
 *  Created on: Jun 26, 2025
 *      Author: kccistc
 */

#ifndef AP_INC_SOUND_H_
#define AP_INC_SOUND_H_

#include "buzzer.h"
#include "stm32f4xx_hal.h"
#include "tim.h"

void Sound_Init();
void Sound_PowerOn();
void Sound_PowerOff();
void Sound_ChangeMode();
void Sound_Alarm();

#endif /* AP_INC_SOUND_H_ */
