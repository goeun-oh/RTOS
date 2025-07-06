/*
 * TimeWatch.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kccistc
 */

#ifndef AP_CONTROLLER_TIMEWATCH_H_
#define AP_CONTROLLER_TIMEWATCH_H_

#include "cmsis_os.h"
#include "Model_Watch.h"

typedef struct{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
	uint16_t msec;
}timeWatch_t;

extern timeWatch_t timeWatchData;
void TimeWatch_Init();
void TimeWatch_Excute();
void TimeWatch_IncTimeCallBack();


#endif /* AP_CONTROLLER_TIMEWATCH_H_ */
