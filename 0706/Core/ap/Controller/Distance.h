/*
 * Distance.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_CONTROLLER_DISTANCE_H_
#define AP_CONTROLLER_DISTANCE_H_

#include <stdint.h>
#include "Model_Distance.h"
#include "cmsis_os.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
extern distance_t distanceData;

void Distance_Init();
void Distance_Excute();

#endif /* AP_CONTROLLER_DISTANCE_H_ */
