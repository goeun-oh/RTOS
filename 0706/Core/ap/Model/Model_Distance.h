/*
 * Model_Distance.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_MODEL_MODEL_DISTANCE_H_
#define AP_MODEL_MODEL_DISTANCE_H_

#include <stdint.h>
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

typedef enum {EVENT_START}eDistanceEvent_t;
typedef enum {S_START, S_IDLE}eDistanceState_t;
typedef struct{
   GPIO_TypeDef *Trig_GPIOx;
   uint16_t Trig_pinNum;
   GPIO_TypeDef *Echo_GPIOx;
   uint16_t Echo_pinNum;
	int distance;
}distance_t;

extern osMessageQId distanceEventMsgBox;
extern osMailQId distanceDataMailBox;

void Model_DistanceInit();
void Model_SetDistanceState (eDistanceState_t state);
eDistanceState_t Model_GetDistanceState();

#endif /* AP_MODEL_MODEL_DISTANCE_H_ */
